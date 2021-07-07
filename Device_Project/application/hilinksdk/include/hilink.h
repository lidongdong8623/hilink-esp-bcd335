/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2018-2019. All rights reserved.
 * Description: HiLink�����̿�ܼ���ͷ�ļ�
 * Create: 2018-06-22
 */
#ifndef _HILINK_H_
#define _HILINK_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*
 * HiLink SDK���Խṹ�壬�����߿���ͨ��HILINK_GetSdkAttr�鿴��ǰϵͳ������ֵ��ͨ��HILINK_SetSdkAttr�����µ�����ֵ��
 * ע��: 1) ��ͨ�豸��̬�������豸��̬�����߳�����ջ��С�������߸��ݲ�Ʒ��̬���������ö�Ӧ��Ʒ��̬������ֵ���ɣ�
 *       2) ʹ��HiLink SDK�����ܹ�ʱ����Ҫ����������������ջ��С�����������ջ��С
 *       3) ���������δע���������ӿ�rebootSoftware��Ӳ�����ӿ�rebootHardware��ʹ��HiLink SDKĬ��ʵ�ֽӿ�(Ӳ����)��
 */
typedef struct {
    unsigned long monitorTaskStackSize;    /* �������ջ��С�������߸��ݾ������������Ĭ��Ϊ1024�ֽ� */
    unsigned long deviceMainTaskStackSize; /* ��ͨ�豸��̬��HiLink SDK����������ջ��С�������߸��ݾ���������� */
    unsigned long bridgeMainTaskStackSize; /* �����豸��̬��HiLink SDK����������ջ��С�������߸��ݾ���������� */
    unsigned long otaCheckTaskStackSize;   /* HiLink OTA��������汾����ջ��С�������߸��ݾ���������� */
    unsigned long otaUpdateTaskStackSize;  /* HiLink OTA��������ջ��С�������߸��ݾ���������� */
    int (*rebootSoftware)(void);           /* �쳣�����������ӿڣ���Ӱ��Ӳ��״̬������û�ע�ᣬ����ʹ�ô˽ӿ� */
    int (*rebootHardware)(void);           /* �쳣����Ӳ�����ӿڣ�Ӱ��Ӳ��״̬������û�û��ע����������ʹ�ô˽ӿ����� */
} HILINK_SdkAttr;

/*
 * HiLink SDK��ں���
 * ����0��ʾ�ɹ�������-1��ʾʧ��
 */
int hilink_main(void);

/* ��ȡ��ǰ�豸״̬��������״̬�������ƶˡ����ߡ����ߵ� */
int hilink_get_devstatus(void);

/*
 * ������ֱ�ӵ��øýӿ�����豸�ָ���������
 * ����0��ʾ�ָ������ɹ�,����-1��ʾ�ָ�����ʧ��
 * �ýӿڻ����ûָ�������־�����óɹ���������ssid�˺���Ϣ��������ģ��
 */
int hilink_restore_factory_settings(void);

/*
 * ��ȡ�洢��Flash���û�������Ϣ
 * ����len��ʾ�û���Ҫ��ȡ��������Ϣ����
 * ����config��ʾ�û���ȡ��������Ϣ����
 * ����0��ʾ��ȡ�ɹ�������-1��ʾ��ȡʧ��
 * config���ڴ����ͳ�ʼ���ɵ��������;�û��ɻ�ȡ��������Ϣ��󳤶�Ϊ32�ֽ�
 * ע��:1����Ҫ��hilink_main��ʼ��֮��ʹ��
 *      2������û��洢�����ַ��������û���֤�洢���ַ������Ȳ�����31�ֽڣ���֤Ԥ���ַ���������
 */
int HilinkGetUserConfig(unsigned short len, char *config);

/*
 * �����û�������Ϣ��flash
 * ����config��ʾ�û�������Ϣ
 * ����len��ʾ�û�������Ϣ����
 * ����0��ʾ���óɹ�������-1��ʾ����ʧ��
 * ��Ϣд��Ϊ���Ǹ��£�ÿ��д��ǰ����վɵ�����;�û��ɴ洢��������Ϣ��󳤶�Ϊ32�ֽ�
 * ע��:1����Ҫ��hilink_main��ʼ��֮��ʹ��
 *      2������û��洢�����ַ��������û���֤�洢���ַ������Ȳ�����31�ֽڣ���֤Ԥ���ַ���������
 */
int HilinkSetUserConfig(const char *config, unsigned short len);

typedef struct {
    unsigned short year;
    unsigned char month;
    unsigned char day;
    unsigned char hour;
    unsigned char min;
    unsigned char sec;
    unsigned short ms;
    /* bit0��λ��ʾ����һ, �Դ�����, ������Ϊbit6��λ, bit7������ */
    unsigned char w_day;
} stHILINK_TIME_INFO, *pstHILINK_TIME_INFO;

/* ʱ���ַ�����󳤶� */
#define TIME_ZONE_STR_MAX_LEN 64

/*
 * ʱ��ͬ��ģ���ȡ����������Ϣ
 * ����0��ʾ�ɹ������ط�0��ʾʧ��
 */
int hilink_get_local_time_info(pstHILINK_TIME_INFO p_time_info);

/*
 * ʱ��ͬ��ģ���ȡ��ǰUTCʱ���ʱ����Ϣ
 * ����0��ʾ�ɹ������ط�0��ʾʧ��
 */
int hilink_get_utc_time_ms(unsigned long long *p_time_ms, char *time_zone, unsigned int len);

/*
 * ʱ��ͬ��ģ���ȡ��ǰUTC������Ϣ
 * ����0��ʾ�ɹ������ط�0��ʾʧ��
 */
int hilink_get_utc_time_info(pstHILINK_TIME_INFO p_time_info);

/*
 * ʱ��ͬ��ģ��ת��msΪ����
 * ����0��ʾ�ɹ������ط�0��ʾʧ��
 */
int hilink_convert_time(unsigned long long time_ms, pstHILINK_TIME_INFO p_time_info);

/*
 * �豸����ʱ�������App��ɾ�����豸�� �ƶ˻���豸�·�Errcode=5��Errcode=6�����롣
 * �ýӿ�����ʹ��SDK�����ƶ��·���Errcode=5��Errcode=6�����롣
 * enableΪ0��ʾSDK�������ƶ��·���Errcode=5��Errcode=6�����룬��ʱSDK��������豸��ע����Ϣ��
 * ��Ҫ�û��ֶ�Ӳ���ָ��������ã��豸�������½�������״̬��
 * enableΪ��0��ʾSDK�����ƶ��·���Errcode=5��Errcode=6�����룬��ʱSDK������豸��ע����Ϣ�����½�������״̬
 * Ĭ��enableΪ0
 */
void HILINK_EnableProcessDelErrCode(int enable);

/*
 * ��ȡSoftAp����PIN��
 * ����ֵΪ8λ����PIN��,����-1��ʾʹ��HiLink SDK��Ĭ��PIN��
 * �ýӿ����豸������ʵ��
 */
int HiLinkGetPinCode(void);

/*
 * HiLink SDK�ⲿ�����Ϣ��¼�ӿ�
 * �ýӿ��Ѿ������ṩ������������ʹ�ã�Ϊ��ǰ����ݣ��ݲ������±���淶����
 */
void hilink_diagnosis_record_ex(int errCode);

/*
 * �ϱ�report��������״̬���ýӿ�Ϊͬ���ӿ�
 * �����ֶ�״̬�����ı������ϱ�����ƽ̨(������ƽ̨ʱ)����HiLink����(����HiLink����ʱ)
 * svcId��ʾ����ID
 * payload��ʾjson��ʽ����
 * len��ʾpayload����
 * taskId��ʾ���øýӿڵ��̵߳�id
 * ����0��ʾ����״̬�ϱ��ɹ�������-1��ʾ����״̬�ϱ�ʧ��
 * �ýӿ��Ѿ������ṩ������������ʹ�ã�Ϊ��ǰ����ݣ��ݲ������±���淶����
 */
int hilink_report_char_state(const char *svcId, const char *payload, unsigned int len, int taskId);

/*
 * �ϱ�����״̬���ýӿ�Ϊ�첽�ӿ�
 * �����ֶ�״̬�����ı������ϱ�����ƽ̨(������ƽ̨ʱ)����HiLink����(����HiLink����ʱ)
 * svcId��ʾ����ID
 * payloadΪjson��ʽ����
 * len��ʾpayload����
 * ����0��ʾ����״̬�ϱ��ɹ�������-1��ʾ����״̬�ϱ�ʧ��
 * �ýӿ��Ѿ������ṩ������������ʹ�ã�Ϊ��ǰ����ݣ��ݲ������±���淶����
 */
int hilink_upload_char_state(const char *svcId, const char *payload, unsigned int len);

/* ����HiLink SDK���ԣ�����0��ʾ���óɹ�����������ʧ�� */
int HILINK_SetSdkAttr(HILINK_SdkAttr sdkAttr);

/* ��ѯHiLink SDK���� */
HILINK_SdkAttr *HILINK_GetSdkAttr(void);

/*
 * ������Ҫʵ�ִ˽ӿ�ʵ��license��д�룬д��flashλ�û���д���ļ��ɳ��Ҿ�����
 * ������Ҫ��֤���ݻ��ƣ���ֹͻȻ�ϵ絼��license��Ϣ��ʧ�����license��Ϣ��ʧ����
 * �޷��������豸���豸��������ʹ�á�
 * ִ�гɹ�����0��ִ��ʧ�ܷ���-1
 */
int HILINK_WriteLicense(const unsigned char *license, unsigned int len);

/*
 * ������Ҫʵ�ִ˽ӿ�ʵ��license��ȡ����ȡflashλ�û���д���ļ��ɳ��Ҿ�����
 * ִ�гɹ�����0��ִ��ʧ�ܷ���-1
 */
int HILINK_ReadLicense(unsigned char *license, unsigned int len);

/*
 * ��ѯ�豸�Ƿ��ѱ�ע��
 * ���ط�0����ע�᣻����0��δע�᣻
 */
int HILINK_IsRegister(void);

/*
 * ����HiLink SDK������Ϣ����·������linux��android�汾����
 * pathΪ·����Ϣ������·�����Ȳ�����127��
 * ����0�����óɹ������ط�0������ʧ�ܡ�
 * ע��: ��linux��androidϵͳ�޴˽ӿ�ʵ��
 */
int HILINK_SetConfigInfoPath(const char *path);

/*
 * ��ѯHiLink SDK������Ϣ����·������linux��android�汾����
 * pathΪ����·���Ļ�������lenΪ���������ȣ�
 * ����0����ȡ�ɹ������ط�0����ȡʧ�ܡ�
 * ע��: ��linux��androidϵͳ�޴˽ӿ�ʵ��
 */
int HILINK_GetConfigInfoPath(char *path, unsigned int len);

/*
 * ��ѯ��ǰ�豸�����Ա�ʶ��
 * ����0Ϊ�������豸������1Ϊ�����豸
 */
int HILINK_IsSensitiveDevice(void);

/* ���̵��øýӿڻ�ȡ�����ṹ�� */
const void *HILINK_GetVoiceContext(void);

/*
 * �豸���ڴ��û�ʶ��״̬ʱ֪ͨ�û�: ����Ϊ��������������2s.
 * ����enable��ʾʶ��״̬,1Ϊ��ʼ����������,0Ϊ��������������.
 * ע��: �������豸�����߻���ʵ��,����hi3861ģ��ʹ��.
 */
void HILINK_SetNanIdentifyStatus(int enable);

/*
 * ����WIFI��ȫ����Ĺ���
 * ����power:��ʾ��ȫ�����Ӧ�ķ���ͨ������,��ֵ���ܵ���-70db;
 * ��Ҫ��֤�տڹ���С�ڵ���-65dBm,������ʵ�豸������.
 * ����ֵ:0��ʾ���óɹ�,-1��ʾ����ʧ��.
 * ע��: �������豸�����߻��̵��ã�����hi3861ģ��ʹ��.
 */
int HILINK_SetSafeDistancePower(char power);

/*
 * �����Ƿ�ʹ��PKI����
 * ����enable:��ʾʹ�ܻ��ǲ�ʹ��,��1��ʾʹ��,��0��ʾ��ʹ��
 * ע��: (1)�������豸�����߻��̵���,����֧��PKI���Ե�ģ��ʹ��
 *       (2)������Ʒ���Ʒʹ��,�Ѿ����õĲ�Ʒ���°汾���ܿ���
 *       (3)����������ʱ,���ȷ����������Ӧ�Ĳ�������
 */
void HILINK_EnablePkiVerify(int enable);

/*
 * ����ģʽ��ʹ��Ԥ��PKI֤��ģʽ, ʹ�ܺ����ͨ��AT����д��֤��
 * ע��: �������豸�����߻��̵���,����hi3861ģ��ʹ��.
 */
int HILINK_EnableFactoryPkiMode(void);

/*
 * ��ȡ�豸�����ͺţ����ȹ̶������ֽ�
 * subProdIdΪ�������ͺŵĻ�������lenΪ�������ĳ���
 * �����Ʒ���������ͺţ����������ֽ����ͺţ�����'\0'����, ����0
 * û�ж������ͺţ��򷵻�-1
 * �ýӿ����豸������ʵ��
 */
int HILINK_GetSubProdId(char *subProdId, int len);

/*
 * ��ȡ�豸�������ǿ���źŷ��书��ǿ�ȣ���ǿ��λ�õ�ȷ���Լ����ʲ��Է�
 * ��������hilink��֤wifi�������ֹ������ü����Է���ָ���ĵ���powerΪ����
 * ����λdbm�������豸�������ǿ�ź�ǿ��ֵ��������̲���ʹ��wifi�������ֹ�
 * �ܣ��ӿ�ֱ�ӷ�-1��sdk�Ͳ���wifi�������ֵĳ�ʼ���������Ҫʹ��wifi����
 * ���֣���ӿڷ���0��power���ض�Ӧ�Ĺ���ֵ��power����Чֵ����<=20dbm����
 * ���ӿڷ���0����power����20����Ҳ����wifi�������ֵĳ�ʼ�������ܲ�����
 */
int HILINK_GetDevSurfacePower(char *power);

/*
 * ���ʹ��˫���ݹ��ܣ���ֱ������ƶ�ע����Ϣ���ݴ洢��ַ��ʱ����Ϣ���ݴ洢��ַ��wifi�˺����뱸�ݴ洢��ַ
 * ����0��ʾ���óɹ���-1��ʾ����ʧ��
 * ע�⣺1) ������Ϣ��ַ�ɷֱ�洢���������������ڵ���0�������������0����ʾ˫�����иò�����Ӧ����Ϣ�����б��ݱ��棻
 *          ÿ�������洢��ַ����4k����(hi3861����)�����������������������ص���
 *       2) hi3861ģ��ע����Ϣ���ٷ���2k�洢�ռ䣬ʱ�������Ϣ���ٷ���3k�洢�ռ䣻wifi��Ϣ���ٷ���1k�洢�ռ䣻
 *          ����ģ�鰴��4k��С�����䡣
 *       3) ESP32��MTK7682ģ��wifi�˺���Ϣ��ϵͳ���棬�����б��ݣ�wifiInfoAddr����ֱ�Ӵ���0
 *       4) ESP8266ģ��wifi�˺���Ϣ��ϵͳ���棬ע����Ϣ����ϵͳ�Դ���˫���ݹ��ܣ������������������ֱ�Ӵ���0
 *       5) LPB130ģ��wifi�˺���Ϣ��ϵͳ���棬�ò�������ֱ�Ӵ���0,�ڸú����д���ĸ���������ַΪ�����0x000D4000��ƫ�Ƶ�ַ��
 *       6) RTL8711AMΪ���豸��������ʱ������ܣ�timeInfoAddr����ֱ�Ӵ���0��
 */
int HILINK_SetBakAddr(unsigned long regInfoAddr, unsigned long timeInfoAddr, unsigned long wifiInfoAddr);
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* _HILINK_H_ */
