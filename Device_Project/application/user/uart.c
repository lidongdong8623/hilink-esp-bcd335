/*
 * ESPRSSIF MIT License
 *
 * Copyright (c) 2015 <ESPRESSIF SYSTEMS (SHANGHAI) PTE LTD>
 *
 * Permission is hereby granted for use on ESPRESSIF SYSTEMS ESP8266 only, in which case,
 * it is free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include "esp_common.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "hilink_device.h"
#include "uart.h"
#include "user_config.h"
#include "hilink.h"
#include "hilink_osadapter.h"
#define FUNC_U0CTS    4
#define FUNC_U0RTS    4


enum {
    UART_EVENT_RX_CHAR,
    UART_EVENT_MAX
};

typedef struct _os_event_ {
    uint32 event;
    uint32 param;
} os_event_t;

uint8 g_receive_data[23] = {0};        //串口数据接受数组
uint8 g_receive_data_old[23] = {0};	   //串口数据接受对比数组
uint8 g_send_data[13] = {0xAA};        //串口发送数组
DevInfo g_dev_info = {
      false,
	  false,
	  false,
	  false,
	  0,0,0,0,0,0,
	  false,
	  false,
	  false,
	  false,
	  false,
	  false,
	  false,
	  false,
	  false,
	  false,
	   true
};                                    //状态参数结构体
uint8 Wifi_clean_config[5] = {0x8D,0x01,0x55,0xAA,0x8D};//直接向主控板发送慢闪协议。            
bool hilink_restore_factory_flag = false; //恢复出厂设置标志位，false -> 不需要恢复  true -> 回复出厂设置
uint8 buf_idx = 0;
 

xTaskHandle xUartTaskHandle;
xQueueHandle xQueueUart;


LOCAL STATUS
uart_tx_one_char(uint8 uart, uint8 TxChar)
{
    while (true) {
        uint32 fifo_cnt = READ_PERI_REG(UART_STATUS(uart)) & (UART_TXFIFO_CNT << UART_TXFIFO_CNT_S);

        if ((fifo_cnt >> UART_TXFIFO_CNT_S & UART_TXFIFO_CNT) < 126) {
            break;
        }
    }

    WRITE_PERI_REG(UART_FIFO(uart) , TxChar);
    return OK;
}

LOCAL void
uart1_write_char(char c)
{
    if (c == '\n') {
        uart_tx_one_char(UART1, '\r');
        uart_tx_one_char(UART1, '\n');
    } else if (c == '\r') {
    } else {
        uart_tx_one_char(UART1, c);
    }
}

LOCAL void
uart0_write_char(char c)
{
    if (c == '\n') {
        uart_tx_one_char(UART0, '\r');
        uart_tx_one_char(UART0, '\n');
    } else if (c == '\r') {
    } else {
        uart_tx_one_char(UART0, c);
    }
}

LOCAL void
uart_rx_intr_handler_ssc(void *arg)
{

    /* uart0 and uart1 intr combine togther, when interrupt occur, see reg 0x3ff20020, bit2, bit0 represents
      * uart1 and uart0 respectively
      */
    os_event_t e;
    portBASE_TYPE xHigherPriorityTaskWoken;

    uint8 RcvChar;
    uint8 uart_no = 0;

    if (UART_RXFIFO_FULL_INT_ST != (READ_PERI_REG(UART_INT_ST(uart_no)) & UART_RXFIFO_FULL_INT_ST)) {
        return;
    }

    RcvChar = READ_PERI_REG(UART_FIFO(uart_no)) & 0xFF;

    WRITE_PERI_REG(UART_INT_CLR(uart_no), UART_RXFIFO_FULL_INT_CLR);

    e.event = UART_EVENT_RX_CHAR;
    e.param = RcvChar;

    xQueueSendFromISR(xQueueUart, (void *)&e, &xHigherPriorityTaskWoken);
    portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
}

#if 0
LOCAL void
uart_config(uint8 uart_no, UartDevice *uart)
{
    if (uart_no == UART1) {
        PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U, FUNC_U1TXD_BK);
    } else {
        /* rcv_buff size if 0x100 */
        _xt_isr_attach(ETS_UART_INUM, uart_rx_intr_handler_ssc, NULL);
        PIN_PULLUP_DIS(PERIPHS_IO_MUX_U0TXD_U);
        PIN_FUNC_SELECT(PERIPHS_IO_MUX_U0TXD_U, FUNC_U0TXD);
    }

    uart_div_modify(uart_no, UART_CLK_FREQ / (uart->baut_rate));

    WRITE_PERI_REG(UART_CONF0(uart_no), uart->exist_parity
                   | uart->parity
                   | (uart->stop_bits << UART_STOP_BIT_NUM_S)
                   | (uart->data_bits << UART_BIT_NUM_S));

    //clear rx and tx fifo,not ready
    SET_PERI_REG_MASK(UART_CONF0(uart_no), UART_RXFIFO_RST | UART_TXFIFO_RST);
    CLEAR_PERI_REG_MASK(UART_CONF0(uart_no), UART_RXFIFO_RST | UART_TXFIFO_RST);

    if (uart_no == UART0) {
        //set rx fifo trigger
        WRITE_PERI_REG(UART_CONF1(uart_no),
                       ((0x01 & UART_RXFIFO_FULL_THRHD) << UART_RXFIFO_FULL_THRHD_S));
    } else {
        WRITE_PERI_REG(UART_CONF1(uart_no),
                       ((0x01 & UART_RXFIFO_FULL_THRHD) << UART_RXFIFO_FULL_THRHD_S));
    }

    //clear all interrupt
    WRITE_PERI_REG(UART_INT_CLR(uart_no), 0xffff);
    //enable rx_interrupt
    SET_PERI_REG_MASK(UART_INT_ENA(uart_no), UART_RXFIFO_FULL_INT_ENA);
}
#endif

LOCAL void
uart_task(void *pvParameters)
{
    os_event_t e;

    for (;;) {
        if (xQueueReceive(xQueueUart, (void *)&e, (portTickType)portMAX_DELAY)) {
            switch (e.event) {
                case UART_EVENT_RX_CHAR:
                    printf("%c", e.param);
                    break;

                default:
                    break;
            }
        }
    }

    vTaskDelete(NULL);
}

#if 0
void
uart_init(void)
{
    while (READ_PERI_REG(UART_STATUS(0)) & (UART_TXFIFO_CNT << UART_TXFIFO_CNT_S));

    while (READ_PERI_REG(UART_STATUS(1)) & (UART_TXFIFO_CNT << UART_TXFIFO_CNT_S));

    UART_ConfigTypeDef uart;

    uart.baut_rate    = BIT_RATE_74880;
    uart.data_bits    = UART_WordLength_8b;
    uart.flow_ctrl    = USART_HardwareFlowControl_None;
    // uart.exist_parity = PARITY_DIS;
    uart.parity       = USART_Parity_None;
    uart.stop_bits    = USART_StopBits_1;

    uart_config(UART0, &uart);
    uart_config(UART1, &uart);

    os_install_putc1(uart1_write_char);

    _xt_isr_unmask(1 << ETS_UART_INUM);

    xQueueUart = xQueueCreate(32, sizeof(os_event_t));

    xTaskCreate(uart_task, (uint8 const *)"uTask", 512, NULL, tskIDLE_PRIORITY + 2, &xUartTaskHandle);
}
#endif

//=================================================================

void
UART_SetWordLength(UART_Port uart_no, UART_WordLength len)
{
    SET_PERI_REG_BITS(UART_CONF0(uart_no), UART_BIT_NUM, len, UART_BIT_NUM_S);
}

void
UART_SetStopBits(UART_Port uart_no, UART_StopBits bit_num)
{
    SET_PERI_REG_BITS(UART_CONF0(uart_no), UART_STOP_BIT_NUM, bit_num, UART_STOP_BIT_NUM_S);
}

void
UART_SetLineInverse(UART_Port uart_no, UART_LineLevelInverse inverse_mask)
{
    CLEAR_PERI_REG_MASK(UART_CONF0(uart_no), UART_LINE_INV_MASK);
    SET_PERI_REG_MASK(UART_CONF0(uart_no), inverse_mask);
}

void
UART_SetParity(UART_Port uart_no, UART_ParityMode Parity_mode)
{
    CLEAR_PERI_REG_MASK(UART_CONF0(uart_no), UART_PARITY | UART_PARITY_EN);

    if (Parity_mode == USART_Parity_None) {
    } else {
        SET_PERI_REG_MASK(UART_CONF0(uart_no), Parity_mode | UART_PARITY_EN);
    }
}

void
UART_SetBaudrate(UART_Port uart_no, uint32 baud_rate)
{
    uart_div_modify(uart_no, UART_CLK_FREQ / baud_rate);
}

//only when USART_HardwareFlowControl_RTS is set , will the rx_thresh value be set.
void
UART_SetFlowCtrl(UART_Port uart_no, UART_HwFlowCtrl flow_ctrl, uint8 rx_thresh)
{
    if (flow_ctrl & USART_HardwareFlowControl_RTS) {
        PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDO_U, FUNC_U0RTS);
        SET_PERI_REG_BITS(UART_CONF1(uart_no), UART_RX_FLOW_THRHD, rx_thresh, UART_RX_FLOW_THRHD_S);
        SET_PERI_REG_MASK(UART_CONF1(uart_no), UART_RX_FLOW_EN);
    } else {
        CLEAR_PERI_REG_MASK(UART_CONF1(uart_no), UART_RX_FLOW_EN);
    }

    if (flow_ctrl & USART_HardwareFlowControl_CTS) {
        PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTCK_U, FUNC_UART0_CTS);
        SET_PERI_REG_MASK(UART_CONF0(uart_no), UART_TX_FLOW_EN);
    } else {
        CLEAR_PERI_REG_MASK(UART_CONF0(uart_no), UART_TX_FLOW_EN);
    }
}

void
UART_WaitTxFifoEmpty(UART_Port uart_no) //do not use if tx flow control enabled
{
    while (READ_PERI_REG(UART_STATUS(uart_no)) & (UART_TXFIFO_CNT << UART_TXFIFO_CNT_S));
}

void
UART_ResetFifo(UART_Port uart_no)
{
    SET_PERI_REG_MASK(UART_CONF0(uart_no), UART_RXFIFO_RST | UART_TXFIFO_RST);
    CLEAR_PERI_REG_MASK(UART_CONF0(uart_no), UART_RXFIFO_RST | UART_TXFIFO_RST);
}

void
UART_ClearIntrStatus(UART_Port uart_no, uint32 clr_mask)
{
    WRITE_PERI_REG(UART_INT_CLR(uart_no), clr_mask);
}

void
UART_SetIntrEna(UART_Port uart_no, uint32 ena_mask)
{
    SET_PERI_REG_MASK(UART_INT_ENA(uart_no), ena_mask);
}

void
UART_intr_handler_register(void *fn, void *arg)
{
    _xt_isr_attach(ETS_UART_INUM, fn, arg);
}

void
UART_SetPrintPort(UART_Port uart_no)
{
    if (uart_no == 1) {
        os_install_putc1(uart1_write_char);
    } else {
        os_install_putc1(uart0_write_char);
    }
}

void
UART_ParamConfig(UART_Port uart_no,  UART_ConfigTypeDef *pUARTConfig)
{
    if (uart_no == UART1) {
        PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U, FUNC_U1TXD_BK);
    } else {
        PIN_PULLUP_DIS(PERIPHS_IO_MUX_U0TXD_U);
        PIN_FUNC_SELECT(PERIPHS_IO_MUX_U0RXD_U, FUNC_U0RXD);
        PIN_FUNC_SELECT(PERIPHS_IO_MUX_U0TXD_U, FUNC_U0TXD);
    }

    UART_SetFlowCtrl(uart_no, pUARTConfig->flow_ctrl, pUARTConfig->UART_RxFlowThresh);
    UART_SetBaudrate(uart_no, pUARTConfig->baud_rate);

    WRITE_PERI_REG(UART_CONF0(uart_no),
                   ((pUARTConfig->parity == USART_Parity_None) ? 0x0 : (UART_PARITY_EN | pUARTConfig->parity))
                   | (pUARTConfig->stop_bits << UART_STOP_BIT_NUM_S)
                   | (pUARTConfig->data_bits << UART_BIT_NUM_S)
                   | ((pUARTConfig->flow_ctrl & USART_HardwareFlowControl_CTS) ? UART_TX_FLOW_EN : 0x0)
                   | pUARTConfig->UART_InverseMask);

    UART_ResetFifo(uart_no);
}

void
UART_IntrConfig(UART_Port uart_no,  UART_IntrConfTypeDef *pUARTIntrConf)
{

    uint32 reg_val = 0;
    UART_ClearIntrStatus(uart_no, UART_INTR_MASK);
    reg_val = READ_PERI_REG(UART_CONF1(uart_no)) & ((UART_RX_FLOW_THRHD << UART_RX_FLOW_THRHD_S) | UART_RX_FLOW_EN) ;

    reg_val |= ((pUARTIntrConf->UART_IntrEnMask & UART_RXFIFO_TOUT_INT_ENA) ?
                ((((pUARTIntrConf->UART_RX_TimeOutIntrThresh)&UART_RX_TOUT_THRHD) << UART_RX_TOUT_THRHD_S) | UART_RX_TOUT_EN) : 0);

    reg_val |= ((pUARTIntrConf->UART_IntrEnMask & UART_RXFIFO_FULL_INT_ENA) ?
                (((pUARTIntrConf->UART_RX_FifoFullIntrThresh)&UART_RXFIFO_FULL_THRHD) << UART_RXFIFO_FULL_THRHD_S) : 0);

    reg_val |= ((pUARTIntrConf->UART_IntrEnMask & UART_TXFIFO_EMPTY_INT_ENA) ?
                (((pUARTIntrConf->UART_TX_FifoEmptyIntrThresh)&UART_TXFIFO_EMPTY_THRHD) << UART_TXFIFO_EMPTY_THRHD_S) : 0);

    WRITE_PERI_REG(UART_CONF1(uart_no), reg_val);
    CLEAR_PERI_REG_MASK(UART_INT_ENA(uart_no), UART_INTR_MASK);
    SET_PERI_REG_MASK(UART_INT_ENA(uart_no), pUARTIntrConf->UART_IntrEnMask);
}

LOCAL void
uart0_rx_intr_handler(void *para)
{
	
   /* uart0 and uart1 intr combine togther, when interrupt occur, see reg 0x3ff20020, bit2, bit0 represents
    * uart1 and uart0 respectively
    */
    uint8 RcvChar;
    uint8 uart_no = UART0;//UartDev.buff_uart_no;
    uint8 fifo_len = 0;
    //uint8 buf_idx = 0;
    
    uint32 uart_intr_status = READ_PERI_REG(UART_INT_ST(uart_no)) ;

    while (uart_intr_status != 0x0) 
	{
        if (UART_FRM_ERR_INT_ST == (uart_intr_status & UART_FRM_ERR_INT_ST)) {
            //printf("FRM_ERR\r\n");
            WRITE_PERI_REG(UART_INT_CLR(uart_no), UART_FRM_ERR_INT_CLR);
        } else if (UART_RXFIFO_FULL_INT_ST == (uart_intr_status & UART_RXFIFO_FULL_INT_ST)) {        //接受full中断
            printf("full\r\n");
            fifo_len = (READ_PERI_REG(UART_STATUS(UART0)) >> UART_RXFIFO_CNT_S)&UART_RXFIFO_CNT;
            buf_idx = 0;

            while (buf_idx < fifo_len) {
                uart_tx_one_char(UART0, READ_PERI_REG(UART_FIFO(UART0)) & 0xFF);//send char to uart0
                buf_idx++;
            }

            WRITE_PERI_REG(UART_INT_CLR(UART0), UART_RXFIFO_FULL_INT_CLR);
        } else if (UART_RXFIFO_TOUT_INT_ST == (uart_intr_status & UART_RXFIFO_TOUT_INT_ST)) {        //接收超时中断
            fifo_len = (READ_PERI_REG(UART_STATUS(UART0)) >> UART_RXFIFO_CNT_S)&UART_RXFIFO_CNT;
            buf_idx = 0;
			//printf("\r\n");
            while (buf_idx < fifo_len) {
                //uart_tx_one_char(UART0, READ_PERI_REG(UART_FIFO(UART0)) & 0xFF);//send char to uart0
				RcvChar = READ_PERI_REG(UART_FIFO(uart_no)) & 0xFF;               //Lidongdong add @2021-1-27.
				g_receive_data[buf_idx] = RcvChar;                                //Lidongdong add @2021-1-27.g_receive_data：串口接收到的所有数据放在此数组
                buf_idx++;
            }
			
			//printf("0000new :\r\n");
			//printf16(g_receive_data,fifo_len);                                  //Lidongdong add @2021-1-27.
			//printf("000old :\r\n");
			//printf16(g_receive_data_old,fifo_len); //Lidongdong add @2021-1-27.
			if(g_receive_data[0] != 0x8D)                //如果串口下发命令标志位为真，则不回发主控数据。
			                                                                      //同时，对于主控回复的配网指令确定不回发
			    uart0_send_data(g_receive_data,buf_idx);           //send back the data to the MCU add by wangshuqiang 2021-3-11
			if(g_receive_data[0] == 0x8D)
				{
					if(
					(g_receive_data[1] == 0x01)||\
					(g_receive_data[1] == 0x02)||\
					(g_receive_data[1] == 0x03)||\
					(g_receive_data[1] == 0x04)||\
					(g_receive_data[1] == 0x05)
					)
					hw_timer_disarm();
				}
			//Lidongdong add @2021-2-5 end.
            WRITE_PERI_REG(UART_INT_CLR(UART0), UART_RXFIFO_TOUT_INT_CLR);
        } else if (UART_TXFIFO_EMPTY_INT_ST == (uart_intr_status & UART_TXFIFO_EMPTY_INT_ST)) {
            printf("empty\n\r");
            WRITE_PERI_REG(UART_INT_CLR(uart_no), UART_TXFIFO_EMPTY_INT_CLR);
            CLEAR_PERI_REG_MASK(UART_INT_ENA(UART0), UART_TXFIFO_EMPTY_INT_ENA);
        } else {
        }
        uart_intr_status = READ_PERI_REG(UART_INT_ST(uart_no)) ;
    }
	
}
void
printf16(uint8 *start, int len) {
	int i;
	for (i = 0; i < len; i++)
		printf(" %02X", start[i]);
	printf("\r\n");
}
/**
    串口发送函数  Add by wangshuqiang 2021-2-20
*/
void
uart0_send_data(uint8 *buf, int len)
{
	int n;
	for (n = 0; n < len ; n++)
	{
		uart_tx_one_char(UART0,buf[n]);
	}
}


/*
   串口接受数据对比函数 Add by wangshuqiang 2021-2-20
   
   Bug fixed by wangshuqiang @2021-2-23
   Bug describution:uart send data as 0x00,program can't enter the 'if' function;
   analysus reason :the function 'strlen' ended with '\0',while send 0x00,the function will stop 
                    to count before the byte '0x00', when the results keep true before 0x00,when it
                    comes to 0x00,it will quit the 'while' circulation,the final result will be True,the program won't enter 'if'.
   solution :change the function 'strlen' with 'sizeof'					
   
*/
bool 
is_arry_equal(uint8 *arrayA, uint8 *arrayB , int len)
{
	//printf("sizeof(arrayA)%d\n\r" ,sizeof(arrayA));
	bool arraysEqual = true ;
	int count = 0; //循环控制变量
	while (arraysEqual && count < len)   
	{                          
		if (arrayA[count] != arrayB[count])
			arraysEqual = false;
		count++;
	}
	return arraysEqual;
}


void
uart0_rec_data_parse()  //Lidongdong add @2021-1-27. 串口解析函数在此
{
	
	ETS_UART_INTR_DISABLE();							//解析时失能串口中断
	if(g_receive_data[0] == 0xAA)
	{
		if((g_receive_data[1] == 0x00) ||\
		  (g_receive_data[1] == 0x01)  ||\
		  (g_receive_data[1] == 0x03)  ||\
		  (g_receive_data[1] == 0x04))
		{  
		   if(g_receive_data[1] != g_receive_data_old[1])
			{
			    if(g_receive_data[1] == 0x00)             //手动模式
				{
					report_refrigerateSwitch_state(false);
					report_freezeSwitch_state(false);
					report_intelligentSwitch_state(false);
					
				}
				else if(g_receive_data[1] == 0x01)		  //智能模式
				{
					report_refrigerateSwitch_state(false);
					report_freezeSwitch_state(false);
					report_intelligentSwitch_state(true);
					
				}
				else if(g_receive_data[1] == 0x03)		  //速冷模式
				{
					report_refrigerateSwitch_state(true);
					report_freezeSwitch_state(false);
					report_intelligentSwitch_state(false);
					
				}
				else if(g_receive_data[1] == 0x04)		  //速冻模式
				{
					report_refrigerateSwitch_state(false);
					report_freezeSwitch_state(true);
					report_intelligentSwitch_state(false);
				}
		    }
			else ;
			if((g_receive_data[2] >= 0x68) && (g_receive_data[2] <= 0x76))       //冷藏设定 2 - 9 9对应主控板的OFF
			{
				if((g_receive_data[11] >= 0x00) && (g_receive_data[11] <= 0xC8)) //冷藏实际-50 - 50 	
				{
					if((g_receive_data[2] != g_receive_data_old[2])||(g_receive_data[11] != g_receive_data_old[11]))
					{
						g_dev_info.g_refrigerator_temp_current = ((int)g_receive_data[11] - 100)/2;
						//g_dev_info.g_refrigerator_temp_target  = ((int)g_receive_data[2] - 100)/2;
						report_refrigerator_state(((int)g_receive_data[2] - 100)/2,((int)g_receive_data[11] - 100)/2);
					}
					else ;
					if((g_receive_data[4] >= 0x34) && (g_receive_data[4] <= 0x46))  //冷冻设定-24 - -15
					{
						if((g_receive_data[13] >= 0x00) && (g_receive_data[13] <= 0xC8)) //冷冻实际 -50 - 50
						{
							if((g_receive_data[4] != g_receive_data_old[4])||(g_receive_data[13] != g_receive_data_old[13]))
							{
								g_dev_info.g_freezer_temp_current = ((int)g_receive_data[13] - 100)/2;
								//g_dev_info.g_freezer_temp_target  = ((int)g_receive_data[4] - 100)/2;
								report_freezer_state(((int)g_receive_data[4] - 100)/2,((int)g_receive_data[13] - 100)/2);
							}
							else ;
							if((g_receive_data[3] >= 0x60) && (g_receive_data[3] <= 0x6E))  //变温设定 -2 - 5
							{
								if(g_receive_data[3] != g_receive_data_old[3])
								{
									//g_dev_info.g_variableTemper_state_target = ((int)g_receive_data[3] - 100)/2;
									report_variableTemper_state(((int)g_receive_data[3] - 100)/2);
								}
						        else ;
								if((g_receive_data[14] >= 0x00) && (g_receive_data[14] <= 0xC8)) //变温实际 -50 - 50
								{
									if(g_receive_data[14] != g_receive_data_old[14])
									{
										g_dev_info.g_VariableRoom1_temp_current = ((int)g_receive_data[14] - 100)/2;
										report_VariableRoom1_state(((int)g_receive_data[14] - 100)/2);
									}
									else ;
									if(((g_receive_data[19]&BYTE_8)>>7)==1)
									{
										report_coolingSwitch_state(true);
									}
									else 
									{
										report_coolingSwitch_state(false);
									}
									if((g_receive_data[6] != g_receive_data_old[6])||(g_receive_data[7] != g_receive_data_old[7]))
									{
										if((g_receive_data[6])||(g_receive_data[7]&0x06))
										{
											if(g_receive_data[6]&0x01)
											   report_faultDetection_state(false,100);
											if(g_receive_data[6]&0x02)
											   report_faultDetection_state(false,101);
											if(g_receive_data[6]&0x04)
											   report_faultDetection_state(false,102);
											if(g_receive_data[6]&0x08)
											   report_faultDetection_state(false,103);
											if(g_receive_data[6]&0x10)
											   report_faultDetection_state(false,104);
											if(g_receive_data[6]&0x20)
											   report_faultDetection_state(false,105);
											if(g_receive_data[6]&0x40)
											   report_faultDetection_state(false,106);
											if(g_receive_data[6]&0x80)
											   report_faultDetection_state(false,107);
											if(g_receive_data[7]&0x02)
											   report_faultDetection_state(false,108);
											if(g_receive_data[7]&0x04)
											   report_faultDetection_state(false,200);
										}
										else
										{
											report_faultDetection_state(true,0);
										}
										
									}
									else ;
								}
								else 
								{
									;
								}
							}
							else
							{
								;
							}
						}
						else
						{
							;
						}
					}
					else
					{
						;
					}
				}
				else
				{
					;
				}
			}
			else
			{
				;
			}
		}
    	else
		{
			;
		}
	}
	else if(g_receive_data[0] == 0x8D)
	{
		if(g_receive_data[1] == 0x06)
		{
			uart0_send_data(Wifi_clean_config,sizeof(Wifi_clean_config));
			hilink_restore_factory_settings();      //恢复出厂设置接口
		}
		else
		{
			;
		}
	}
	else
	{
		;
	}
	ETS_UART_INTR_ENABLE();							//解析完成后使能串口中断
}
void 
uart0_rec_data_trans()
{
	if(g_receive_data[0] == 0xaa )                  //引导码 0xAA
    {
		  g_send_data[0]  = g_receive_data[0];      //引导码赋值
		  g_send_data[1]  = g_receive_data[1];      //模式赋值	
		  g_send_data[2]  = g_receive_data[2];	    //冷藏设定赋值
		  g_send_data[3]  = g_receive_data[3];	    //变温设定赋值
		  g_send_data[4]  = g_receive_data[4];	    //冷冻设定赋值
		  g_send_data[10] = g_receive_data[19];     //开关设定赋值
	}
	
}

bool Check_Receive_num(uint8 *arrayA,int len)
{
	short int temp = 0;
	unsigned int i=0;
	bool flag = false;
	for(i = 0;i < len-1; i++)
	{
		temp = arrayA[i] + temp;
	}
	temp = temp & 0x00FF;
	if(temp == arrayA[len-1])
		flag = true;
	else 
		flag = false;
	
	return flag;
}
void
uart_init_new(void)
{
    UART_WaitTxFifoEmpty(UART0);
    UART_WaitTxFifoEmpty(UART1);

    UART_ConfigTypeDef uart_config;
    uart_config.baud_rate    = BIT_RATE_9600;
    uart_config.data_bits     = UART_WordLength_8b;
    uart_config.parity          = USART_Parity_None;
    uart_config.stop_bits     = USART_StopBits_1;
    uart_config.flow_ctrl      = USART_HardwareFlowControl_None;
    uart_config.UART_RxFlowThresh = 120;
    uart_config.UART_InverseMask = UART_None_Inverse;
    UART_ParamConfig(UART0, &uart_config);

    UART_IntrConfTypeDef uart_intr;
    uart_intr.UART_IntrEnMask = UART_RXFIFO_TOUT_INT_ENA | UART_FRM_ERR_INT_ENA | UART_RXFIFO_FULL_INT_ENA | UART_TXFIFO_EMPTY_INT_ENA;
    uart_intr.UART_RX_FifoFullIntrThresh = 100;
    uart_intr.UART_RX_TimeOutIntrThresh = 2;
    uart_intr.UART_TX_FifoEmptyIntrThresh = 20;
    UART_IntrConfig(UART0, &uart_intr);

    //UART_SetPrintPort(UART0);
    UART_intr_handler_register(uart0_rx_intr_handler, NULL);
    ETS_UART_INTR_ENABLE();

    /*trans UART0 TX/RX to the CTS/RTS   add bywangshuqiang*/
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTCK_U, FUNC_U0CTS);//CONFIG MTCK PIN FUNC TO U0CTS
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDO_U, FUNC_U0RTS);//CONFIG MTDO PIN FUNC TO U0RTS
    SET_PERI_REG_MASK(0x3ff00028 , BIT2);//SWAP PIN : U0TXD<==>U0RTS(MTDO) , U0RXD<==>U0CTS(MTCK)
    /*
    UART_SetWordLength(UART0,UART_WordLength_8b);
    UART_SetStopBits(UART0,USART_StopBits_1);
    UART_SetParity(UART0,USART_Parity_None);
    UART_SetBaudrate(UART0,74880);
    UART_SetFlowCtrl(UART0,USART_HardwareFlowControl_None,0);
    */

}
