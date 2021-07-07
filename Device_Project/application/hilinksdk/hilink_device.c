/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2018-2020. All rights reserved.
 * Description: �豸���ܽӿڶ���
 * Notes: ���ļ����ݿ����߹��ܶ����Զ�����, ��Ҫ����������ʵ�֡�
 */
#include <stdlib.h>
#include <string.h>
#include "esp_common.h"
#include "hilink_device.h"
#include "uart.h"
#include "user_config.h"
<<<<<<< HEAD
#include "hw_timer.h"
extern uint8 g_send_data[13];             //WIFI����>MCU���ڷ������� Add by wangshuqiang @2021-2-18
extern uint8 g_receive_data[23];          //MCU����>WIFI���ڽ�������
extern uint8 g_receive_data_old[23];      //���ڽ��նԱ�����
extern DevInfo g_dev_info;       
char inConfig = 0x00;	                  //falsh��һ�ֽڣ������������֮ǰ������״̬
char user_flash_message = 0x00;           //�����жϵ���ǰ�Ƿ��Ѿ��������
bool intelligentFlag = false;             //����ģʽ��־λ
void wait_connecting(void)                //�������ص�����             
{   
    uint8 wait_connected[5] = {0x8D,0x01,0x55,0xAA,0x8D};
	uart0_send_data(wait_connected,sizeof(wait_connected));
}

void success_login(void)                  //������ɻص�����
{
	uint8 Wifi_connected_success[5] = {0x8D,0x02,0x55,0xAA,0x8E};
	uart0_send_data(Wifi_connected_success,sizeof(Wifi_connected_success));
}
void reconnected(void)                    //�����ص�����
{
	uint8 Wifi_reconnected[5] = {0x8D,0x03,0x55,0xAA,0x8F};	
	uart0_send_data(Wifi_reconnected,sizeof(Wifi_reconnected)); //������������
}
void net_close(void)                      //�ر�����ص�����
{
	uint8 Wifi_close[5] = {0x8D,0x05,0x55,0xAA,0x91};
	uart0_send_data(Wifi_close,sizeof(Wifi_close));//10���ӳ�ʱ���ͣ��ر�wifi��
}
=======


extern uint8 g_send_data[13];             //WIFI����>MCU���ڷ������� Add by wangshuqiang @2021-2-18
extern uint8 g_receive_data[22];          //MCU����>WIFI���ڽ�������
extern uint8 g_receive_data_old[22];      //���ڽ��նԱ�����
extern DevInfo g_dev_info;

>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
/*
 * ����: ��ȡ�豸��ذ汾��
 * ����: firmwareVer - �̼��汾
 *       softwareVer - ����汾
 *       hardwareVer - Ӳ���汾
 * ����: ��
 * ע��: HiLink�ڲ����ú���, �����޸�
 */
int getDeviceVersion(char **firmwareVer, char **softwareVer, char **hardwareVer)
{
    *firmwareVer = FIRMWARE_VER;
    *softwareVer = SOFTWARE_VER;
    *hardwareVer = HARDWARE_VER;
    return HILINK_RET_SUCCESS;
}

<<<<<<< HEAD
void caculate_check_num(unsigned char *arrayA,int len)
{
	int i;
	short int temp = 0; 
	for(i = 0;i < len - 1 ; i++)
	{
		//uart0_send_data(arrayA,1);
		temp = *arrayA + temp;
		arrayA = arrayA + 1;
	}
    *arrayA = (uint8)(temp & 0x00FF);
	//uart0_send_data(arrayA,1);
}

=======
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
/*
 * ����: SDK֪ͨ�豸״̬, �����߰���ʵ���յ���״̬��Ĵ���
 * ����: status - �豸��ǰ״̬
 * ����: ��
 * ע��: �˺����ɿ����߸��ݲ�Ʒҵ��ѡ����ʵ��
 */
void hilink_notify_devstatus(int status)
{
    switch (status) {
        case HILINK_M2M_CLOUD_OFFLINE:
            /* �豸���ƶ����ӶϿ�, ���ڴ˴����ʵ�� */
            break;
        case HILINK_M2M_CLOUD_ONLINE:
            /* �豸�����ƶ˳ɹ�, ���ڴ˴����ʵ�� */
<<<<<<< HEAD
			hw_timer_set_func(success_login);
			hw_timer_arm(500000,1);
			inConfig = 0x01;                  
			HilinkSetUserConfig(&inConfig,1);//��0x01д��flash�������Ѿ�������� add by wangshuqiang 2021-3-29
=======
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
            break;
        case HILINK_M2M_LONG_OFFLINE:
            /* �豸���ƶ����ӳ�ʱ��Ͽ�, ���ڴ˴����ʵ�� */
            break;
        case HILINK_M2M_LONG_OFFLINE_REBOOT:
            /* �豸���ƶ����ӳ�ʱ��Ͽ����������, ���ڴ˴����ʵ�� */
            break;
        case HILINK_UNINITIALIZED:
            /* HiLink�߳�δ����, ���ڴ˴����ʵ�� */
            break;
        case HILINK_LINK_UNDER_AUTO_CONFIG:
            /* �豸��������ģʽ, ���ڴ˴����ʵ�� */
<<<<<<< HEAD
			hw_timer_set_func(wait_connecting);
			hw_timer_arm(500000,1);
            break;
        case HILINK_LINK_CONFIG_TIMEOUT:
            /* �豸����10���ӳ�ʱ״̬, ���ڴ˴����ʵ�� */
			hw_timer_set_func(net_close);
			hw_timer_arm(500000,1);
            break;
        case HILINK_LINK_CONNECTTING_WIFI:
            /* �豸��������·����, ���ڴ˴����ʵ�� */
			HilinkGetUserConfig(1,&user_flash_message);  //��flash�ж�ȡ�Ƿ�֮ǰ�������
				if(user_flash_message==0x01)
				{
					hw_timer_set_func(reconnected);
			        hw_timer_arm(500000,1);
				}
				else 
				printf("A8\r\n");
=======
            break;
        case HILINK_LINK_CONFIG_TIMEOUT:
            /* �豸����10���ӳ�ʱ״̬, ���ڴ˴����ʵ�� */
            break;
        case HILINK_LINK_CONNECTTING_WIFI:
            /* �豸��������·����, ���ڴ˴����ʵ�� */
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
            break;
        case HILINK_LINK_CONNECTED_WIFI:
            /* �豸�Ѿ�����·����, ���ڴ˴����ʵ�� */
            break;
        case HILINK_M2M_CONNECTTING_CLOUD:
            /* �豸���������ƶ�, ���ڴ˴����ʵ�� */
            break;
        case HILINK_M2M_CLOUD_DISCONNECT:
            /* �豸��·���������ӶϿ�, ���ڴ˴����ʵ�� */
            break;
        default:
            break;
    }
}

/*
 * ����: SDK֪ͨģ������, �����߰���ʵ�ָ�����������ǰ�Ĵ���
 * ����: flag 0-��ʾHiLink SDK �߳̿��Ź�����ģ������; 1-��ʾAppɾ���豸����ģ������
 * ����: 0-����ɹ�,ϵͳ��������,ʹ��Ӳ����;1-����ɹ�,ϵͳ��������,ʹ��������(�������ӿ���Ҫ������ǰ���䲢ע��);��ֵ-����ʧ��,ϵͳ��������
 * ע��: 1) ��APPɾ���豸����ģ������ʱ, �豸��������ط���0, ����ᵼ��ɾ���豸�쳣;
 *       2) �˺����ɿ�����ʵ��
 */
int hilink_process_before_restart(int flag)
{
    /* HiLink SDK�߳̿��Ź���ʱ����ģ������ */
    if (flag == HILINK_REBOOT_WATCHDOG) {
        /* ʵ��ģ������ǰ�Ĳ���(��:����ϵͳ״̬��), �������ɹ���ɺ󷵻�0�������� */
<<<<<<< HEAD
        return 0;
=======
        return -1;
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
    }
    /* APPɾ���豸����ģ������ */
    else if (flag == HILINK_REBOOT_DEVDELETE) {
        /* ʵ��ģ������ǰ�Ĳ���(��:����ϵͳ״̬��) */
        return 0;
    }
    /* �����쳣 */
    else {
        return -1;
    }
}

/*
 * ����: ��ȡ�豸PIN��
 * ����: ��
 * ����: int ��������PIN���-1
 * ע��: ���豸�����Զ���PIN��, ��������8λ����PIN��(��13572468);
 *       ���豸����Ĭ��PIN��, ��������-1.
 */
int HiLinkGetPinCode(void)
{
    /* �ɿ�����ʵ��, ���豸PIN�뷵�� */
<<<<<<< HEAD
    return -1;
=======

   // return 88888888;//Add by lidongdong  @2021-01-21
    return -1;//Add by lidongdong  @2021-01-21
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
}

/*
 * ����: ��ȡ�豸SN��
 * ����: unsigned int len �޶�SN��󳤶�Ϊ39�ֽ�
 * ����: ��
 * ע��: ���snָ����ַ�������Ϊ0ʱ��ʹ���豸mac��ַ��Ϊsn
 */
void HilinkGetDeviceSn(unsigned int len, char *sn)
{
    /* �ɿ�����ʵ��, ���豸SN�Ÿ������ */
<<<<<<< HEAD
	//char str[] = "Hi-Huawei-Smart Home-1211SB";  // Add by wangshuqiang @2021-2-18
    //memcpy(sn, str, strlen(str));
=======
    char str[] = "Hi-Huawei-Smart Home-1211SY";  // Add by wangshuqiang @2021-2-18
    memcpy(sn, str, strlen(str));

>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
    return;
}

/* ------------------------ �����ƶ��·��ķ������(PUT)���� ------------------------ */
/*
 * ����: ����refrigerateSwitch����Ŀ�������
 * ����: on - on���Ե�ֵ
 * ����: HILINK_OK - �����ɹ�, �豸״̬�Ѹı�
 *       HILINK_ERR - ����ʧ��, �豸״̬δ�ı�
 *       HILINK_PROCESSING - ���ڲ�����, �豸״̬��δ�ı�
 * ע��: 1) ����HILINK_PROCESSING��ʾ�豸���ڽ����첽����, ����������豸״̬�ı�,
 *          ��Ҫ��������report�ӿڽ��������״̬�ϱ���App;
 *       2) �˺����ɿ�����ʵ��.
 */
int handle_refrigerateSwitch_cmd(bool *on)
{
    /* ʵ�ֶ�on���Ե��޸� */
    if (on != NULL) {                               //ȷ��onָ��ָ������ַ����ֹ*on���ֲ���Ԥ֪���� Add by wangshuqiang @2021-2-18
        /* ���ڴ˴�ʵ���豸״̬�ı�Ĳ��� */        //Add by lidongdong  @2021-02-5 begin.
<<<<<<< HEAD
			g_dev_info.g_refrigerateSwitch = *on;
			if(*on)
			{
				 g_send_data[1] = 0x03;                 //�·�����Ϊ 1 -> ����ģʽ Add by wangshuqiang @2021-2-18
			}
			else
			{
				g_send_data[1] = 0x00;                 //�·�����Ϊ 0 -> Ĭ���ֶ�ģʽ Add by wangshuqiang @2021-2-18
			}
		}
	caculate_check_num(g_send_data,sizeof(g_send_data));//calculate check_num and send out add by wangshuqiang 2021-3-22
	uart0_send_data(g_send_data,sizeof(g_send_data));                         //��������·������־λ
	if(*on)
	{
		report_freezeSwitch_state(false);
		report_intelligentSwitch_state(false);
	}
	else ;
    //report_faultDetection_state(false,108); 
=======
		if(*on)
		{
			 g_send_data[1] = 0x03;                 //�·�����Ϊ 1 -> ����ģʽ Add by wangshuqiang @2021-2-18
       	}
		else
	         g_send_data[1] = 0x00;                 //�·�����Ϊ 0 -> Ĭ���ֶ�ģʽ Add by wangshuqiang @2021-2-18
		}
    //printf("Lidongdong:handle_refrigerateSwitch_cmd uart0_send_data()\r\n");    //Lidongdong add @2021-1-27.
	uart0_send_data(g_send_data,sizeof(g_send_data));//Add by lidongdong  @2021-02-5 end.
    //printf(" [Test wangshuqiang   hahhaha ] bit->1   data -> %02X",g_send_data[1]);    
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
    /* ��ͬ�������ı��豸״̬, ״̬�ı��, ����HILINK_OK */
    /* ���첽�����ı��豸״̬, �˴�����HILINK_PROCESSING, ��״̬�ı�������ϱ���״̬ */
    return HILINK_OK;
}

/*
 * ����: ����freezeSwitch����Ŀ�������
 * ����: on - on���Ե�ֵ
 * ����: HILINK_OK - �����ɹ�, �豸״̬�Ѹı�
 *       HILINK_ERR - ����ʧ��, �豸״̬δ�ı�
 *       HILINK_PROCESSING - ���ڲ�����, �豸״̬��δ�ı�
 * ע��: 1) ����HILINK_PROCESSING��ʾ�豸���ڽ����첽����, ����������豸״̬�ı�,
 *          ��Ҫ��������report�ӿڽ��������״̬�ϱ���App;
 *       2) �˺����ɿ�����ʵ��.
 */
int handle_freezeSwitch_cmd(bool *on)
<<<<<<< HEAD
{	
    /* ʵ�ֶ�on���Ե��޸� */
    if (on != NULL) {
        /* ���ڴ˴�ʵ���豸״̬�ı�Ĳ��� */        //Add by lidongdong  @2021-02-5 begin.
		g_dev_info.g_freezeSwitch = *on;
=======
{
    /* ʵ�ֶ�on���Ե��޸� */
    if (on != NULL) {
        /* ���ڴ˴�ʵ���豸״̬�ı�Ĳ��� */        //Add by lidongdong  @2021-02-5 begin.
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
		if(*on)
			g_send_data[1] = 0x04;                  //1 -> �����ٶ�ģʽ 0 -> Ĭ���ֶ�ģʽ Add by wangshuqiang @2021-2-18
		else
			g_send_data[1] = 0x00;
    }
<<<<<<< HEAD
	caculate_check_num(g_send_data,sizeof(g_send_data));//calculate check_num and send out add by wangshuqiang 2021-3-22
	uart0_send_data(g_send_data,sizeof(g_send_data));
	if(*on)
	{
		report_refrigerateSwitch_state(false);
		report_intelligentSwitch_state(false);
	}
	else ;
=======
	uart0_send_data(g_send_data,sizeof(g_send_data));//Add by lidongdong  @2021-02-5 end.
    //printf(" [Test wangshuqiang   hahhaha ] bit->1   data -> %02X",g_send_data[1]);
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
    /* ��ͬ�������ı��豸״̬, ״̬�ı��, ����HILINK_OK */
    /* ���첽�����ı��豸״̬, �˴�����HILINK_PROCESSING, ��״̬�ı�������ϱ���״̬ */
    return HILINK_OK;
}

/*
 * ����: ����intelligentSwitch����Ŀ�������
 * ����: on - on���Ե�ֵ
 * ����: HILINK_OK - �����ɹ�, �豸״̬�Ѹı�
 *       HILINK_ERR - ����ʧ��, �豸״̬δ�ı�
 *       HILINK_PROCESSING - ���ڲ�����, �豸״̬��δ�ı�
 * ע��: 1) ����HILINK_PROCESSING��ʾ�豸���ڽ����첽����, ����������豸״̬�ı�,
 *          ��Ҫ��������report�ӿڽ��������״̬�ϱ���App;
 *       2) �˺����ɿ�����ʵ��.
 */
int handle_intelligentSwitch_cmd(bool *on)
{
    /* ʵ�ֶ�on���Ե��޸� */
<<<<<<< HEAD
        if (on!= NULL) {
        /* ���ڴ˴�ʵ���豸״̬�ı�Ĳ��� */        //Add by lidongdong  @2021-02-5 begin.
		    g_dev_info.g_intelligentSwitch = *on;
			if(*on)
			{   
			  intelligentFlag==true;         //������ģʽ��־λΪtrueʱ���·�����ĳЩ�ֽ��ֶ�д�룬�����ý��ܵ�����
			  g_send_data[0]  = g_receive_data[0];      //�����븳ֵ
			  g_send_data[1]  = 0x01;      //// 1 -> ��������ģʽ 0 -> Ĭ���ֶ�ģʽ Add by wangshuqiang @2021-2-18	
			  g_send_data[2]  = 0x6E;	    //����趨��ֵ
			  g_send_data[3]  = 0x6E;	    //�����趨��ֵ
			  g_send_data[4]  = 0x40;	    //�䶳�趨��ֵ
			  g_send_data[10] = g_receive_data[19];     //�����趨��ֵ
			}
			else 
				g_send_data[1] = 0x00;
        }
	caculate_check_num(g_send_data,sizeof(g_send_data));//calculate check_num and send out add by wangshuqiang 2021-3-22
	uart0_send_data(g_send_data,sizeof(g_send_data));
	intelligentFlag = false;
	if(*on)
	{
		report_refrigerateSwitch_state(false);
		report_freezeSwitch_state(false);
	}
	else ;
=======
    if (on!= NULL) {
        /* ���ڴ˴�ʵ���豸״̬�ı�Ĳ��� */        //Add by lidongdong  @2021-02-5 begin.
		if(*on)
			g_send_data[1] = 0x01;                  // 1 -> ��������ģʽ 0 -> Ĭ���ֶ�ģʽ Add by wangshuqiang @2021-2-18
		else 
			g_send_data[1] = 0x00;
    }
	uart0_send_data(g_send_data,sizeof(g_send_data));//Add by lidongdong  @2021-02-5 end.
	//printf(" [Test wangshuqiang   hahhaha ] bit->1   data -> %02X",g_send_data[1]);
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
    /* ��ͬ�������ı��豸״̬, ״̬�ı��, ����HILINK_OK */
    /* ���첽�����ı��豸״̬, �˴�����HILINK_PROCESSING, ��״̬�ı�������ϱ���״̬ */
    return HILINK_OK;
}

/*
 * ����: ����refrigerator����Ŀ�������
 * ����: target - target���Ե�ֵ
 * ����: HILINK_OK - �����ɹ�, �豸״̬�Ѹı�
 *       HILINK_ERR - ����ʧ��, �豸״̬δ�ı�
 *       HILINK_PROCESSING - ���ڲ�����, �豸״̬��δ�ı�
 * ע��: 1) ����HILINK_PROCESSING��ʾ�豸���ڽ����첽����, ����������豸״̬�ı�,
 *          ��Ҫ��������report�ӿڽ��������״̬�ϱ���App;
 *       2) �˺����ɿ�����ʵ��.
 */
int handle_refrigerator_cmd(int *target)
<<<<<<< HEAD
{	
    /* ʵ�ֶ�target���Ե��޸� */
    if (target != NULL) {
		g_dev_info.g_refrigerator_temp_target = *target;
		g_send_data[2] = (char)((*target)*2+100);   //��App�·��Ŀ����¶���ֵ������ʽת��Ϊ����ͨ����ֵ��ǿ��ת��Ϊ�ַ�����ֵ Add by wangshuqiang @2021-2-18
		/* ���ڴ˴�ʵ���豸״̬�ı�Ĳ��� */
    }
	//report_refrigerator_state(*target,g_dev_info.g_refrigerator_temp_current);
    caculate_check_num(g_send_data,sizeof(g_send_data));//calculate check_num and send out add by wangshuqiang 2021-3-22
	uart0_send_data(g_send_data,sizeof(g_send_data));
=======
{
    /* ʵ�ֶ�target���Ե��޸� */
    if (target != NULL) {
		g_send_data[2] = (char)((*target)*2+100);   //��App�·��Ŀ����¶���ֵ������ʽת��Ϊ����ͨ����ֵ��ǿ��ת��Ϊ�ַ�����ֵ Add by wangshuqiang @2021-2-18
        /* ���ڴ˴�ʵ���豸״̬�ı�Ĳ��� */
    }
	uart0_send_data(g_send_data,sizeof(g_send_data));//Add by lidongdong  @2021-02-5 end.
	//printf(" [Test wangshuqiang   hahhaha ] bit->2   data -> %02X",g_send_data[2]);
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
    /* ��ͬ�������ı��豸״̬, ״̬�ı��, ����HILINK_OK */
    /* ���첽�����ı��豸״̬, �˴�����HILINK_PROCESSING, ��״̬�ı�������ϱ���״̬ */
    return HILINK_OK;
}

/*
 * ����: ����freezer����Ŀ�������
 * ����: target - target���Ե�ֵ
 * ����: HILINK_OK - �����ɹ�, �豸״̬�Ѹı�
 *       HILINK_ERR - ����ʧ��, �豸״̬δ�ı�
 *       HILINK_PROCESSING - ���ڲ�����, �豸״̬��δ�ı�
 * ע��: 1) ����HILINK_PROCESSING��ʾ�豸���ڽ����첽����, ����������豸״̬�ı�,
 *          ��Ҫ��������report�ӿڽ��������״̬�ϱ���App;
 *       2) �˺����ɿ�����ʵ��.
 */
int handle_freezer_cmd(int *target)
<<<<<<< HEAD
{	
    /* ʵ�ֶ�target���Ե��޸� */
   if (target != NULL) {
        /* ���ڴ˴�ʵ���豸״̬�ı�Ĳ��� */
		g_dev_info.g_freezer_temp_target = *target;
		g_send_data[4] = (char)((*target)*2+100);  //��App�·��Ŀ����¶���ֵ������ʽת��Ϊ����ͨ����ֵ��ǿ��ת��Ϊ�ַ�����ֵ Add by wangshuqiang @2021-2-18
    }
	caculate_check_num(g_send_data,sizeof(g_send_data));//calculate check_num and send out add by wangshuqiang 2021-3-22
	uart0_send_data(g_send_data,sizeof(g_send_data));
=======
{
    /* ʵ�ֶ�target���Ե��޸� */
    if (target != NULL) {
        /* ���ڴ˴�ʵ���豸״̬�ı�Ĳ��� */
		g_send_data[4] = (char)((*target)*2+100);  //��App�·��Ŀ����¶���ֵ������ʽת��Ϊ����ͨ����ֵ��ǿ��ת��Ϊ�ַ�����ֵ Add by wangshuqiang @2021-2-18
    }
	uart0_send_data(g_send_data,sizeof(g_send_data));
	//printf(" [Test wangshuqiang   hahhaha ] bit->2   data -> %02X",g_send_data[4]);
     //printf16(g_send_data,sizeof(g_send_data));
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
    /* ��ͬ�������ı��豸״̬, ״̬�ı��, ����HILINK_OK */
    /* ���첽�����ı��豸״̬, �˴�����HILINK_PROCESSING, ��״̬�ı�������ϱ���״̬ */
    return HILINK_OK;
}

/*
 * ����: ����coolingSwitch����Ŀ�������
 * ����: coolingSwitch - coolingSwitch���Ե�ֵ
 * ����: HILINK_OK - �����ɹ�, �豸״̬�Ѹı�
 *       HILINK_ERR - ����ʧ��, �豸״̬δ�ı�
 *       HILINK_PROCESSING - ���ڲ�����, �豸״̬��δ�ı�
 * ע��: 1) ����HILINK_PROCESSING��ʾ�豸���ڽ����첽����, ����������豸״̬�ı�,
 *          ��Ҫ��������report�ӿڽ��������״̬�ϱ���App;
 *       2) �˺����ɿ�����ʵ��.
 */
<<<<<<< HEAD
int handle_coolingSwitch_cmd(bool *coolingSwitch)
{	
    /* ʵ�ֶ�coolingSwitch���Ե��޸� */
     if (coolingSwitch != NULL) {
        /* ���ڴ˴�ʵ���豸״̬�ı�Ĳ��� */
		g_dev_info.g_coolingSwitch = *coolingSwitch;
		if(*coolingSwitch)                        //1 -> ��ؿ� 0 -> ��ع� Add by wangshuqiang @2021-2-20
			g_send_data[10] = 0x80;
		else
		{
			g_send_data[10] = 0x00;
			g_send_data[2]  = 0x74;               //�Զ��壬����ؿ��عر�ʱ�������ʾ�¶�λ8�� Add by wangshuqiang @2021-5-18
		}
    }
	caculate_check_num(g_send_data,sizeof(g_send_data));//calculate check_num and send out add by wangshuqiang 2021-3-22
	uart0_send_data(g_send_data,sizeof(g_send_data));
=======

int handle_coolingSwitch_cmd(bool *coolingSwitch)
{
    /* ʵ�ֶ�coolingSwitch���Ե��޸� */
    if (coolingSwitch != NULL) {
        /* ���ڴ˴�ʵ���豸״̬�ı�Ĳ��� */
		if(*coolingSwitch)                        //1 -> ��ؿ� 0 -> ��ع� Add by wangshuqiang @2021-2-20
		{
			g_send_data[10] = 0x40;               //Ĭ�ϵ�ʮ���ֽڵ�7λʼ��Ϊ1  Add by wangshuqiang @2021-2-20
		}
		else
			g_send_data[10] = 0xC0;
    }
	uart0_send_data(g_send_data,sizeof(g_send_data));
	//printf(" [Test wangshuqiang   hahhaha ] bit->2   data -> %02X",g_send_data[10]);

>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
    /* ��ͬ�������ı��豸״̬, ״̬�ı��, ����HILINK_OK */
    /* ���첽�����ı��豸״̬, �˴�����HILINK_PROCESSING, ��״̬�ı�������ϱ���״̬ */
    return HILINK_OK;
}
<<<<<<< HEAD

/*
 * ����: ����variableTemper����Ŀ�������
=======
/*
 * ����: ����variableMode����Ŀ�������
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
 * ����: target - target���Ե�ֵ
 * ����: HILINK_OK - �����ɹ�, �豸״̬�Ѹı�
 *       HILINK_ERR - ����ʧ��, �豸״̬δ�ı�
 *       HILINK_PROCESSING - ���ڲ�����, �豸״̬��δ�ı�
 * ע��: 1) ����HILINK_PROCESSING��ʾ�豸���ڽ����첽����, ����������豸״̬�ı�,
 *          ��Ҫ��������report�ӿڽ��������״̬�ϱ���App;
 *       2) �˺����ɿ�����ʵ��.
 */
<<<<<<< HEAD
int handle_variableTemper_cmd(int *target)
{	
    /* ʵ�ֶ�target���Ե��޸� */
    if (target != NULL) {
        /* ���ڴ˴�ʵ���豸״̬�ı�Ĳ��� */
		g_dev_info.g_variableTemper_state_target = *target;
		g_send_data[3] = (char)((*target)*2+100);
    }
    caculate_check_num(g_send_data,sizeof(g_send_data));//calculate check_num and send out add by wangshuqiang 2021-3-22
	uart0_send_data(g_send_data,sizeof(g_send_data));
=======
int handle_variableMode_cmd(int *target)
{
    /* ʵ�ֶ�target���Ե��޸� */
    if (target != NULL) {
        /* ���ڴ˴�ʵ���豸״̬�ı�Ĳ��� */
    }
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
    /* ��ͬ�������ı��豸״̬, ״̬�ı��, ����HILINK_OK */
    /* ���첽�����ı��豸״̬, �˴�����HILINK_PROCESSING, ��״̬�ı�������ϱ���״̬ */
    return HILINK_OK;
}

/* ------------------------ �����ƶ��·��ķ����ѯ(GET)���� ------------------------ */
/*
 * ����: ����refrigerateSwitch�����״̬��ѯ����
 * ����: on - on���Ե�ֵ
 * ����: 0-�ɹ�, ��0-ʧ��
 * ע��: �˺����ɿ�����ʵ��
 */
int get_refrigerateSwitch_state(bool *on)
{
<<<<<<< HEAD
	
    /* �ɿ�����ʵ��, ��refrigerateSwitch��������Ե�ǰֵ������� */
	if(on != NULL)
	{
		*on = g_dev_info.g_refrigerateSwitch;  //���յĴ�����ֵ��Ӧλ�������󣬽�״̬��ֵ��ָ��ָ�����ݵȴ���ȡ Add by wangshuqiang @2021-2-18
	}
=======
	*on = g_dev_info.g_refrigerateSwitch;      //���յĴ�����ֵ��Ӧλ�������󣬽�״̬��ֵ��ָ��ָ�����ݵȴ���ȡ Add by wangshuqiang @2021-2-18
    /* �ɿ�����ʵ��, ��refrigerateSwitch��������Ե�ǰֵ������� */
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
    return HILINK_RET_SUCCESS;
}

/*
 * ����: ����freezeSwitch�����״̬��ѯ����
 * ����: on - on���Ե�ֵ
 * ����: 0-�ɹ�, ��0-ʧ��
 * ע��: �˺����ɿ�����ʵ��
 */
int get_freezeSwitch_state(bool *on)
<<<<<<< HEAD
{	
    /* �ɿ�����ʵ��, ��freezeSwitch��������Ե�ǰֵ������� */
	if(on != NULL)
	{
	  *on = g_dev_info.g_freezeSwitch;          //�䶳ģʽ״̬��ֵ����  Add by wangshuqiang @2021-2-20
	}
=======
{
    /* �ɿ�����ʵ��, ��freezeSwitch��������Ե�ǰֵ������� */
	*on = g_dev_info.g_freezeSwitch;          //�䶳ģʽ״̬��ֵ����  Add by wangshuqiang @2021-2-20
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
    return HILINK_RET_SUCCESS;
}

/*
 * ����: ����intelligentSwitch�����״̬��ѯ����
 * ����: on - on���Ե�ֵ
 * ����: 0-�ɹ�, ��0-ʧ��
 * ע��: �˺����ɿ�����ʵ��
 */
int get_intelligentSwitch_state(bool *on)
<<<<<<< HEAD
{	
    /* �ɿ�����ʵ��, ��intelligentSwitch��������Ե�ǰֵ������� */
	if(on != NULL)
	{
	  *on = g_dev_info.g_intelligentSwitch;     //����ģʽ״̬��ֵ����  Add by wangshuqiang @2021-2-20
	}
=======
{
	*on = g_dev_info.g_intelligentSwitch;     //����ģʽ״̬��ֵ����  Add by wangshuqiang @2021-2-20
    /* �ɿ�����ʵ��, ��intelligentSwitch��������Ե�ǰֵ������� */
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
    return HILINK_RET_SUCCESS;
}

/*
 * ����: ����refrigerator�����״̬��ѯ����
 * ����: target - target���Ե�ֵ
 *       current - current���Ե�ֵ
 * ����: 0-�ɹ�, ��0-ʧ��
 * ע��: �˺����ɿ�����ʵ��
 */
int get_refrigerator_state(int *target, int *current)
<<<<<<< HEAD
{	
    /* �ɿ�����ʵ��, ��refrigerator��������Ե�ǰֵ������� */
	if(target != NULL)
	{ 
       *target = g_dev_info.g_refrigerator_temp_target;       //������趨��ֵ�뵱ǰ״̬��ֵ����  Add by wangshuqiang @2021-2-20  
	}
	if(current != NULL)
	{	
       *current = g_dev_info.g_refrigerator_temp_current;
	}
=======
{
    /* �ɿ�����ʵ��, ��refrigerator��������Ե�ǰֵ������� */
	*target = g_dev_info.g_refrigerator_temp_target;       //������趨��ֵ�뵱ǰ״̬��ֵ����  Add by wangshuqiang @2021-2-20    
	*current = g_dev_info.g_refrigerator_temp_current;
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
    return HILINK_RET_SUCCESS;
}

/*
 * ����: ����freezer�����״̬��ѯ����
 * ����: target - target���Ե�ֵ
 *       current - current���Ե�ֵ
 * ����: 0-�ɹ�, ��0-ʧ��
 * ע��: �˺����ɿ�����ʵ��
 */
int get_freezer_state(int *target, int *current)
<<<<<<< HEAD
{	
    /* �ɿ�����ʵ��, ��freezer��������Ե�ǰֵ������� */
	if(target != NULL)
	{
		*target = g_dev_info.g_freezer_temp_target;            //�䶳���趨��ֵ�뵱ǰ״̬��ֵ����  Add by wangshuqiang @2021-2-20
	}
	if(current != NULL)
	{
	    *current = g_dev_info.g_freezer_temp_current;
	}
=======
{
    /* �ɿ�����ʵ��, ��freezer��������Ե�ǰֵ������� */
	*target = g_dev_info.g_freezer_temp_target;            //�䶳���趨��ֵ�뵱ǰ״̬��ֵ����  Add by wangshuqiang @2021-2-20
	*current = g_dev_info.g_freezer_temp_current;
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
    return HILINK_RET_SUCCESS;
}

/*
 * ����: ����coolingSwitch�����״̬��ѯ����
 * ����: coolingSwitch - coolingSwitch���Ե�ֵ
 * ����: 0-�ɹ�, ��0-ʧ��
 * ע��: �˺����ɿ�����ʵ��
 */
int get_coolingSwitch_state(bool *coolingSwitch)
<<<<<<< HEAD
{	
    /* �ɿ�����ʵ��, ��coolingSwitch��������Ե�ǰֵ������� */
	if(coolingSwitch != NULL)
	{
	    *coolingSwitch = g_dev_info.g_coolingSwitch;           //��ؿ���״̬��ֵ����  Add by wangshuqiang @2021-2-20
	}
=======
{
    /* �ɿ�����ʵ��, ��coolingSwitch��������Ե�ǰֵ������� */
	*coolingSwitch = g_dev_info.g_coolingSwitch;           //��ؿ���״̬��ֵ����  Add by wangshuqiang @2021-2-20
	//printf("[TEST wangshuqiang   %d\r\n]",g_dev_info.g_coolingSwitch);
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
    return HILINK_RET_SUCCESS;
}

/*
<<<<<<< HEAD
 * ����: ����variableTemper�����״̬��ѯ����
=======
 * ����: ����variableMode�����״̬��ѯ����
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
 * ����: target - target���Ե�ֵ
 * ����: 0-�ɹ�, ��0-ʧ��
 * ע��: �˺����ɿ�����ʵ��
 */
<<<<<<< HEAD
int get_variableTemper_state(int *target)
{	
    /* �ɿ�����ʵ��, ��variableTemper��������Ե�ǰֵ������� */
	if(target != NULL)
	{
	    *target = g_dev_info.g_variableTemper_state_target;
	}
=======
int get_variableMode_state(int *target)
{
    /* �ɿ�����ʵ��, ��variableMode��������Ե�ǰֵ������� */

>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
    return HILINK_RET_SUCCESS;
}

/*
 * ����: ����VariableRoom1�����״̬��ѯ����
 * ����: current - current���Ե�ֵ
 * ����: 0-�ɹ�, ��0-ʧ��
 * ע��: �˺����ɿ�����ʵ��
 */
int get_VariableRoom1_state(int *current)
<<<<<<< HEAD
{	
    /* �ɿ�����ʵ��, ��VariableRoom1��������Ե�ǰֵ������� */
	if(current != NULL)
	{
	    *current = g_dev_info.g_VariableRoom1_temp_current;
	}
=======
{
    /* �ɿ�����ʵ��, ��VariableRoom1��������Ե�ǰֵ������� */
	*current = g_dev_info.g_VariableRoom1_temp_target;    //�����ҵ�ǰ״̬��ֵ����  Add by wangshuqiang @2021-2-20
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
    return HILINK_RET_SUCCESS;
}

/*
 * ����: ��ȡfaultDetection����״̬��App
 * ����: status - �Ƿ��⵽������߹���
 *       code - ���ϴ�����
 * ����: 0-�ɹ�, ��0-ʧ��
 * ע��: �˺����ṩ�������ߵ���
 */
int get_faultDetection_state(bool *status, int *code)
{
    /* �ɿ�����ʵ��, ������faultDetection���Ե�ǰֵ������� */
    return HILINK_RET_SUCCESS;
}

/*
 * ����: ��ȡ�豸�����ͺţ����ȹ̶������ֽ�
 * ����: subProdIdΪ�������ͺŵĻ�������lenΪ�������ĳ���
 * ����: int ��������0��-1
<<<<<<< HEAD
 * ע��: �����Ʒ���������ͺţ����������ֽ����ͺţ�����' '����, ����0;
=======
 * ע��: �����Ʒ���������ͺţ����������ֽ����ͺţ�����' '����, ����0;
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
 *       û�ж������ͺţ��򷵻�-1.
 */
int HILINK_GetSubProdId(char *subProdId, int len)
{
    return -1;
}

int HILINK_GetDevSurfacePower(char *power)
{
    return -1;
}
