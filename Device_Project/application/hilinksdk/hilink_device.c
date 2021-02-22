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


extern uint8 g_send_data[13];             //WIFI����>MCU���ڷ������� Add by wangshuqiang @2021-2-18
extern uint8 g_receive_data[22];          //MCU����>WIFI���ڽ�������
extern uint8 g_receive_data_old[22];      //���ڽ��նԱ�����
extern DevInfo g_dev_info;

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
            break;
        case HILINK_LINK_CONFIG_TIMEOUT:
            /* �豸����10���ӳ�ʱ״̬, ���ڴ˴����ʵ�� */
            break;
        case HILINK_LINK_CONNECTTING_WIFI:
            /* �豸��������·����, ���ڴ˴����ʵ�� */
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
        return -1;
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

   // return 88888888;//Add by lidongdong  @2021-01-21
    return -1;//Add by lidongdong  @2021-01-21
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
    char str[] = "Hi-Huawei-Smart Home-1211SY";  // Add by wangshuqiang @2021-2-18
    memcpy(sn, str, strlen(str));

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
{
    /* ʵ�ֶ�on���Ե��޸� */
    if (on != NULL) {
        /* ���ڴ˴�ʵ���豸״̬�ı�Ĳ��� */        //Add by lidongdong  @2021-02-5 begin.
		if(*on)
			g_send_data[1] = 0x04;                  //1 -> �����ٶ�ģʽ 0 -> Ĭ���ֶ�ģʽ Add by wangshuqiang @2021-2-18
		else
			g_send_data[1] = 0x00;
    }
	uart0_send_data(g_send_data,sizeof(g_send_data));//Add by lidongdong  @2021-02-5 end.
    //printf(" [Test wangshuqiang   hahhaha ] bit->1   data -> %02X",g_send_data[1]);
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
    if (on!= NULL) {
        /* ���ڴ˴�ʵ���豸״̬�ı�Ĳ��� */        //Add by lidongdong  @2021-02-5 begin.
		if(*on)
			g_send_data[1] = 0x01;                  // 1 -> ��������ģʽ 0 -> Ĭ���ֶ�ģʽ Add by wangshuqiang @2021-2-18
		else 
			g_send_data[1] = 0x00;
    }
	uart0_send_data(g_send_data,sizeof(g_send_data));//Add by lidongdong  @2021-02-5 end.
	//printf(" [Test wangshuqiang   hahhaha ] bit->1   data -> %02X",g_send_data[1]);
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
{
    /* ʵ�ֶ�target���Ե��޸� */
    if (target != NULL) {
		g_send_data[2] = (char)((*target)*2+100);   //��App�·��Ŀ����¶���ֵ������ʽת��Ϊ����ͨ����ֵ��ǿ��ת��Ϊ�ַ�����ֵ Add by wangshuqiang @2021-2-18
        /* ���ڴ˴�ʵ���豸״̬�ı�Ĳ��� */
    }
	uart0_send_data(g_send_data,sizeof(g_send_data));//Add by lidongdong  @2021-02-5 end.
	//printf(" [Test wangshuqiang   hahhaha ] bit->2   data -> %02X",g_send_data[2]);
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
{
    /* ʵ�ֶ�target���Ե��޸� */
    if (target != NULL) {
        /* ���ڴ˴�ʵ���豸״̬�ı�Ĳ��� */
		g_send_data[4] = (char)((*target)*2+100);  //��App�·��Ŀ����¶���ֵ������ʽת��Ϊ����ͨ����ֵ��ǿ��ת��Ϊ�ַ�����ֵ Add by wangshuqiang @2021-2-18
    }
	uart0_send_data(g_send_data,sizeof(g_send_data));
	//printf(" [Test wangshuqiang   hahhaha ] bit->2   data -> %02X",g_send_data[4]);
     //printf16(g_send_data,sizeof(g_send_data));
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

    /* ��ͬ�������ı��豸״̬, ״̬�ı��, ����HILINK_OK */
    /* ���첽�����ı��豸״̬, �˴�����HILINK_PROCESSING, ��״̬�ı�������ϱ���״̬ */
    return HILINK_OK;
}
/*
 * ����: ����variableMode����Ŀ�������
 * ����: target - target���Ե�ֵ
 * ����: HILINK_OK - �����ɹ�, �豸״̬�Ѹı�
 *       HILINK_ERR - ����ʧ��, �豸״̬δ�ı�
 *       HILINK_PROCESSING - ���ڲ�����, �豸״̬��δ�ı�
 * ע��: 1) ����HILINK_PROCESSING��ʾ�豸���ڽ����첽����, ����������豸״̬�ı�,
 *          ��Ҫ��������report�ӿڽ��������״̬�ϱ���App;
 *       2) �˺����ɿ�����ʵ��.
 */
int handle_variableMode_cmd(int *target)
{
    /* ʵ�ֶ�target���Ե��޸� */
    if (target != NULL) {
        /* ���ڴ˴�ʵ���豸״̬�ı�Ĳ��� */
    }
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
	*on = g_dev_info.g_refrigerateSwitch;      //���յĴ�����ֵ��Ӧλ�������󣬽�״̬��ֵ��ָ��ָ�����ݵȴ���ȡ Add by wangshuqiang @2021-2-18
    /* �ɿ�����ʵ��, ��refrigerateSwitch��������Ե�ǰֵ������� */
    return HILINK_RET_SUCCESS;
}

/*
 * ����: ����freezeSwitch�����״̬��ѯ����
 * ����: on - on���Ե�ֵ
 * ����: 0-�ɹ�, ��0-ʧ��
 * ע��: �˺����ɿ�����ʵ��
 */
int get_freezeSwitch_state(bool *on)
{
    /* �ɿ�����ʵ��, ��freezeSwitch��������Ե�ǰֵ������� */
	*on = g_dev_info.g_freezeSwitch;          //�䶳ģʽ״̬��ֵ����  Add by wangshuqiang @2021-2-20
    return HILINK_RET_SUCCESS;
}

/*
 * ����: ����intelligentSwitch�����״̬��ѯ����
 * ����: on - on���Ե�ֵ
 * ����: 0-�ɹ�, ��0-ʧ��
 * ע��: �˺����ɿ�����ʵ��
 */
int get_intelligentSwitch_state(bool *on)
{
	*on = g_dev_info.g_intelligentSwitch;     //����ģʽ״̬��ֵ����  Add by wangshuqiang @2021-2-20
    /* �ɿ�����ʵ��, ��intelligentSwitch��������Ե�ǰֵ������� */
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
{
    /* �ɿ�����ʵ��, ��refrigerator��������Ե�ǰֵ������� */
	*target = g_dev_info.g_refrigerator_temp_target;       //������趨��ֵ�뵱ǰ״̬��ֵ����  Add by wangshuqiang @2021-2-20    
	*current = g_dev_info.g_refrigerator_temp_current;
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
{
    /* �ɿ�����ʵ��, ��freezer��������Ե�ǰֵ������� */
	*target = g_dev_info.g_freezer_temp_target;            //�䶳���趨��ֵ�뵱ǰ״̬��ֵ����  Add by wangshuqiang @2021-2-20
	*current = g_dev_info.g_freezer_temp_current;
    return HILINK_RET_SUCCESS;
}

/*
 * ����: ����coolingSwitch�����״̬��ѯ����
 * ����: coolingSwitch - coolingSwitch���Ե�ֵ
 * ����: 0-�ɹ�, ��0-ʧ��
 * ע��: �˺����ɿ�����ʵ��
 */
int get_coolingSwitch_state(bool *coolingSwitch)
{
    /* �ɿ�����ʵ��, ��coolingSwitch��������Ե�ǰֵ������� */
	*coolingSwitch = g_dev_info.g_coolingSwitch;           //��ؿ���״̬��ֵ����  Add by wangshuqiang @2021-2-20
	//printf("[TEST wangshuqiang   %d\r\n]",g_dev_info.g_coolingSwitch);
    return HILINK_RET_SUCCESS;
}

/*
 * ����: ����variableMode�����״̬��ѯ����
 * ����: target - target���Ե�ֵ
 * ����: 0-�ɹ�, ��0-ʧ��
 * ע��: �˺����ɿ�����ʵ��
 */
int get_variableMode_state(int *target)
{
    /* �ɿ�����ʵ��, ��variableMode��������Ե�ǰֵ������� */

    return HILINK_RET_SUCCESS;
}

/*
 * ����: ����VariableRoom1�����״̬��ѯ����
 * ����: current - current���Ե�ֵ
 * ����: 0-�ɹ�, ��0-ʧ��
 * ע��: �˺����ɿ�����ʵ��
 */
int get_VariableRoom1_state(int *current)
{
    /* �ɿ�����ʵ��, ��VariableRoom1��������Ե�ǰֵ������� */
	*current = g_dev_info.g_VariableRoom1_temp_target;    //�����ҵ�ǰ״̬��ֵ����  Add by wangshuqiang @2021-2-20
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
 * ע��: �����Ʒ���������ͺţ����������ֽ����ͺţ�����' '����, ����0;
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
