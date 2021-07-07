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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hilink.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "uart.h"
#include "user_config.h"
#include "gpio.h"
#include "hw_timer.h"

/******************************************************************************
 * FunctionName : user_rf_cal_sector_set
 * Description  : SDK just reversed 4 sectors, used for rf init data and paramters.
 *                We add this function to force users to set rf cal sector, since
 *                we don't know which sector is free in user's application.
 *                sector map for last several sectors : ABCCC
 *                A : rf cal
 *                B : rf init data
 *                C : sdk parameters
 * Parameters   : none
 * Returns      : rf cal sector
*******************************************************************************/
uint32 user_rf_cal_sector_set(void)
{
    flash_size_map size_map = system_get_flash_size_map();
    uint32 rf_cal_sec = 0;

    switch (size_map) {
        case FLASH_SIZE_4M_MAP_256_256:
            rf_cal_sec = 128 - 5;
            break;

        case FLASH_SIZE_8M_MAP_512_512:
            rf_cal_sec = 256 - 5;
            break;

        case FLASH_SIZE_16M_MAP_512_512:
        case FLASH_SIZE_16M_MAP_1024_1024:
            rf_cal_sec = 512 - 5;
            break;

        case FLASH_SIZE_32M_MAP_512_512:
        case FLASH_SIZE_32M_MAP_1024_1024:
            rf_cal_sec = 1024 - 5;
            break;
        case FLASH_SIZE_64M_MAP_1024_1024:
            rf_cal_sec = 2048 - 5;
            break;
        case FLASH_SIZE_128M_MAP_1024_1024:
            rf_cal_sec = 4096 - 5;
            break;
        default:
            rf_cal_sec = 0;
            break;
    }

    return rf_cal_sec;
}
/******************************************************************************
 * FunctionName : user_init
 * Description  : entry of user application, init user function here
 * Parameters   : none
 * Returns      : none
*******************************************************************************/

void parse_task(void* param)
{
	HILINK_EnableProcessDelErrCode(1);                //离线模式下删除设备，设备连接路由后，自动变成待配网模式
	while(1)
	{
		if(!is_arry_equal(g_receive_data,g_receive_data_old,sizeof(g_receive_data)/sizeof(uint8)))//Lidongdong add @2021-2-5 begin.
		{
			if(Check_Receive_num(g_receive_data,buf_idx))      //judge the accuracy of receive data
				{   
				  if(intelligentFlag==false)          //下发智能模式的数据部分手动操作，不用接受到的数据。
				  {
					  uart0_rec_data_trans();         //once receive the data,put the parse data to the send function
				  }
				  uart0_rec_data_parse();             //解析数据，赋值给全局变量		
			      memcpy( g_receive_data_old, g_receive_data, sizeof( g_receive_data ) ); //赋值给上一次的数组以便比较。
				}
		}
		vTaskDelay(3000);
	}
	
}



void user_init(void)
{
	
	GPIO_ConfigTypeDef GPIO_ConfigInit; //初始化结构体
	
	GPIO_ConfigInit.GPIO_Pin = GPIO_Pin_5;  //GPIO5
	GPIO_ConfigInit.GPIO_Mode = GPIO_Mode_Output; //输出模式
	GPIO_ConfigInit.GPIO_Pullup = GPIO_PullUp_DIS; //不选择上拉
	GPIO_ConfigInit.GPIO_IntrType = GPIO_PIN_INTR_DISABLE; //失能中断
	
	gpio_config(&GPIO_ConfigInit);          //初始化GPIO结构体
	gpio_output_conf(GPIO_Pin_5,0,GPIO_Pin_5,0);//GPIO5输出高电平
	uart_init_new();//74800bps
	hw_timer_init();//初始化硬件定时器
    //hw_timer_set_func(test_timer);
    //hw_timer_arm(1000000,1);
    printf("SDK version:%s\n", system_get_sdk_version());
	hilink_main();
	xTaskCreate(parse_task, "parse_task", 1024, NULL, 3, NULL);
}

