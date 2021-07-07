/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2018-2020. All rights reserved.
 * Description: �豸���ܽӿ�����
 * Notes: ���ļ����ݿ����߹��ܶ����Զ�����, ��Ҫ����������ʵ�֡�
 */
#ifndef HILINK_DEVICE_H
#define HILINK_DEVICE_H

/* ----------------------------- ���������޸ĵĺ궨�� ----------------------------- */
/* �����߸���ʵ�ʲ�Ʒ�汾��Ϣ�����޸� */
<<<<<<< HEAD
#define FIRMWARE_VER "1.0.0"      
#define SOFTWARE_VER "1.0.0"      
#define HARDWARE_VER "1.0.0"      
=======
#define FIRMWARE_VER "1.0.0"
#define SOFTWARE_VER "1.0.0"
#define HARDWARE_VER "1.0.0"
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae

/* ----------------- HiLink��Ʒģ�Ͳ����궨��, �Զ�����, �����޸� ----------------- */
/* �豸������Ϣ */
#define PRODUCT_ID "211S"
#define DEVICE_TYPE "08A"
<<<<<<< HEAD
#define MANUAFACTURER "377"
#define DEVICE_MODEL "BCD-335WPGX"
=======
#define MANUAFACTURER "a70"
#define DEVICE_MODEL "BCD-335"
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae

/* ��ȷ���豸����Ӣ�����ͳ���Ӣ��������֮�Ͳ�����17�ֽ� */
#define DEVICE_TYPE_NAME "Fridge"
#define MANUAFACTURER_NAME "AUCMA"

/* ͨ��Э������: WIFI */
#define PROTOCOL_TYPE 1

/* ϵͳ���Ͷ��� */
#ifndef bool
#define bool int
#endif
#ifndef true
#define true 1
#endif
#ifndef false
#define false 0
#endif
#ifndef NULL
#define NULL 0
#endif

/* HiLink����Ԥ���巵��ֵ */
#ifndef HILINK_RET_SUCCESS
#define HILINK_RET_SUCCESS 0
#endif
#ifndef HILINK_RET_ERROR
#define HILINK_RET_ERROR -88
#endif

/* PUT������ƽӿڷ���ֵ */
#ifndef HILINK_OK
#define HILINK_OK 0
#endif
#ifndef HILINK_ERR
#define HILINK_ERR (-1)
#endif
#ifndef HILINK_PROCESSING
#define HILINK_PROCESSING (-111)
#endif

/* HiLink SDK֪ͨ������ģ������ԭ�� */
#define HILINK_REBOOT_WATCHDOG 0
#define HILINK_REBOOT_DEVDELETE 1

/* HiLink SDK֪ͨ�������豸״̬ */
#define HILINK_M2M_CLOUD_OFFLINE 0       /* �豸���ƶ����ӶϿ�(�汾��ǰ����) */
#define HILINK_M2M_CLOUD_ONLINE 1        /* �豸�����ƶ˳ɹ�, ������������̬(�汾��ǰ����) */
#define HILINK_M2M_LONG_OFFLINE 2        /* �豸���ƶ����ӳ�ʱ��Ͽ�(�汾��ǰ����) */
#define HILINK_M2M_LONG_OFFLINE_REBOOT 3 /* �豸���ƶ����ӳ�ʱ��Ͽ����������(�汾��ǰ����) */
#define HILINK_UNINITIALIZED 4           /* HiLink�߳�δ���� */
#define HILINK_LINK_UNDER_AUTO_CONFIG 5  /* �豸��������ģʽ */
#define HILINK_LINK_CONFIG_TIMEOUT 6     /* �豸����10���ӳ�ʱ״̬ */
#define HILINK_LINK_CONNECTTING_WIFI 7   /* �豸��������·���� */
#define HILINK_LINK_CONNECTED_WIFI 8     /* �豸�Ѿ�����·���� */
#define HILINK_M2M_CONNECTTING_CLOUD 9   /* �豸���������ƶ� */
#define HILINK_M2M_CLOUD_DISCONNECT 10   /* �豸��·���������ӶϿ� */

/* �豸���к���󳤶� */
#define MAX_SN_LENGTH 40

/* ------------------------- HiLink�ڲ����ú����������޸� ------------------------- */
/* ��ȡ��ǰ�豸�汾�� */
int getDeviceVersion(char **firmwareVer, char **softwareVer, char **hardwareVer);
/* ��ȡBI�����ӿں��� */
char *hilink_get_auto_bi_rsa_cipher(void);
/* ��ȡAC�����ӿں��� */
unsigned char *hilink_get_auto_ac(void);

/* ----------------------------- ��Ҫ������ʵ�ֵĺ��� ----------------------------- */
/* SDK֪ͨ�豸״̬, �����߰���ʵ���յ���״̬��Ĵ��� */
void hilink_notify_devstatus(int status);
/* SDK֪ͨģ������, �����߰���ʵ�ָ�����������ǰ�Ĵ��� */
int hilink_process_before_restart(int flag);
/* SDK��ȡ�豸SN��, �����߰��践���豸SN�� */
void HilinkGetDeviceSn(unsigned int len, char *sn);

/* ------------------------ �����ƶ��·��ķ������(PUT)���� ------------------------ */
int handle_refrigerateSwitch_cmd(bool *on);
int handle_freezeSwitch_cmd(bool *on);
int handle_intelligentSwitch_cmd(bool *on);
int handle_refrigerator_cmd(int *target);
int handle_freezer_cmd(int *target);
int handle_coolingSwitch_cmd(bool *coolingSwitch);
<<<<<<< HEAD
int handle_variableTemper_cmd(int *target);
=======
int handle_variableMode_cmd(int *target);
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae

/* ------------------------ �����ƶ��·��ķ����ѯ(GET)���� ------------------------ */
int get_refrigerateSwitch_state(bool *on);
int get_freezeSwitch_state(bool *on);
int get_intelligentSwitch_state(bool *on);
int get_refrigerator_state(int *target, int *current);
int get_freezer_state(int *target, int *current);
int get_coolingSwitch_state(bool *coolingSwitch);
<<<<<<< HEAD
int get_variableTemper_state(int *target);
=======
int get_variableMode_state(int *target);
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
int get_VariableRoom1_state(int *current);
int get_faultDetection_state(bool *status, int *code);

/* -------------------------- �ϱ�(REPORT)����״̬���ƶ� --------------------------- */
/*
 * ����: �ϱ�refrigerateSwitch����״̬��APP
 * ����: on - on���Ե�ֵ
 * ����: int��0-�ɹ�����0-ʧ��
 * ע��: �˺����ɿ����ߵ���
 */
int report_refrigerateSwitch_state(bool on);

/*
 * ����: �ϱ�freezeSwitch����״̬��APP
 * ����: on - on���Ե�ֵ
 * ����: int��0-�ɹ�����0-ʧ��
 * ע��: �˺����ɿ����ߵ���
 */
int report_freezeSwitch_state(bool on);

/*
 * ����: �ϱ�intelligentSwitch����״̬��APP
 * ����: on - on���Ե�ֵ
 * ����: int��0-�ɹ�����0-ʧ��
 * ע��: �˺����ɿ����ߵ���
 */
int report_intelligentSwitch_state(bool on);

/*
 * ����: �ϱ�refrigerator����״̬��APP
 * ����: target - target���Ե�ֵ
 *       current - current���Ե�ֵ
 * ����: int��0-�ɹ�����0-ʧ��
 * ע��: �˺����ɿ����ߵ���
 */
int report_refrigerator_state(int target, int current);

/*
 * ����: �ϱ�freezer����״̬��APP
 * ����: target - target���Ե�ֵ
 *       current - current���Ե�ֵ
 * ����: int��0-�ɹ�����0-ʧ��
 * ע��: �˺����ɿ����ߵ���
 */
int report_freezer_state(int target, int current);

/*
 * ����: �ϱ�coolingSwitch����״̬��APP
 * ����: coolingSwitch - coolingSwitch���Ե�ֵ
 * ����: int��0-�ɹ�����0-ʧ��
 * ע��: �˺����ɿ����ߵ���
 */
int report_coolingSwitch_state(bool coolingSwitch);

/*
<<<<<<< HEAD
 * ����: �ϱ�variableTemper����״̬��APP
=======
 * ����: �ϱ�variableMode����״̬��APP
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
 * ����: target - target���Ե�ֵ
 * ����: int��0-�ɹ�����0-ʧ��
 * ע��: �˺����ɿ����ߵ���
 */
<<<<<<< HEAD
int report_variableTemper_state(int target);
=======
int report_variableMode_state(int target);
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae

/*
 * ����: �ϱ�VariableRoom1����״̬��APP
 * ����: current - current���Ե�ֵ
 * ����: int��0-�ɹ�����0-ʧ��
 * ע��: �˺����ɿ����ߵ���
 */
int report_VariableRoom1_state(int current);

/*
 * ����: �ϱ�report_faultDetection_state����״̬��APP
 * ����: status - �Ƿ��⵽������߹���
 *       code - ���ϴ�����
 * ����: int��0-�ɹ�����0-ʧ��
 * ע��: �˺������豸���̵���
 */
int report_faultDetection_state(bool status, int code);

<<<<<<< HEAD
void caculate_check_num(unsigned char *arrayA,int len);

=======
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
#endif /* HILINK_DEVICE_H */
