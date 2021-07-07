/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2018-2019. All rights reserved.
 * Description: ģ��ϵͳ��������ͷ�ļ�
 * Notes: ���ļ��еĽӿ���Ҫ�����ṩ������������ʹ�ã�Ϊ��ǰ����ݣ������Ͻӿ��ݲ������±���淶����.
 */
#ifndef HILINK_OSADAPTER_H
#define HILINK_OSADAPTER_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HILINK_OK
#define HILINK_OK 0
#endif
#ifndef HILINK_ERROR
#define HILINK_ERROR (-1)
#endif
#define IP_LIST_LEN    40

typedef void* hilink_mutex_t;

typedef enum {
    NW_DISCONNECTED = 0, /* �������ӶϿ� */
    NW_CONNECTED    = 1  /* ���������� */
} network_state_t;

typedef enum {
    HILINK_SOCKET_READABLE = 1,
    HILINK_SOCKET_WRITEABLE = 2,
    HILINK_SOCKET_EXCEPTION = 4
} HiLinkSocketState;

/* HiLink Socket������ */
typedef enum {
    HILINK_SOCKET_NO_ERROR               = 0,
    HILINK_SOCKET_NULL_PTR               = -1,
    HILINK_SOCKET_CREAT_UDP_FD_FAILED    = -2,
    HILINK_SOCKET_SEND_UDP_PACKET_FAILED = -3,
    HILINK_SOCKET_READ_UDP_PACKET_FAILED = -4,
    HILINK_SOCKET_TCP_CONNECTING         = -5,
    HILINK_SOCKET_TCP_CONNECT_FAILED     = -6,
    HILINK_SOCKET_SEND_TCP_PACKET_FAILED = -7,
    HILINK_SOCKET_READ_TCP_PACKET_FAILED = -8,
    HILINK_SOCKET_REMOVE_UDP_FD_FAILED   = -9,
    HILINK_SOCKET_SELECT_TIMEOUT         = -10,
    HILINK_SOCKET_SELECT_ERROR           = -11
} hilink_socket_error_t;

/*
 * ��ȡԶ��������
 * ����0-�ɹ�, ����-ʧ��
 */
int hilink_gethostbyname(const char *hostname, char ipList[][IP_LIST_LEN], int num);
/*
 * ��ȡϵͳʱ��
 * ����0�ɹ�����������ʧ��
 */
int hilink_gettime(unsigned long *ms);

/*
 * �����ַ����ĳ���
 * ע�⣺
 *    1�������ַ����е�'\0'��ֹͣ���㳤��
 *    2��src�ַ����뱣֤��'\0'��β
 */
unsigned int hilink_strlen(const char *src);

/*
 * �Ƚ������ַ���str1��str2
 * ����0��ʾstr1��str2���, С��0��ʾstr1 С�� str2, ���ش���0��ʾstr1 ���� str2
 */
int hilink_strncmp(const char *str1, const char *str2, unsigned int len);

/*
 * ���ַ���str�в����ַ�ch
 * ����NULL��ʾû�в��ҵ��ַ�, ��NULL��ʾָ��ch��ָ��
 */
char *hilink_strchr(const char *str, int ch);

/*
 * ���ַ���str����������ַ�ch
 * ����NULL��ʾû�в��ҵ��ַ�, ��NULL��ʾָ��ch��ָ��
 */
char *hilink_strrchr(const char *str, char ch);

/*
 * ���ַ���ת����int��������
 * ����int��������
 */
int hilink_atoi(const char *str);

/*
 * �����������ֽ���ת�����ֽ���
 * ���������ֽ�������
 */
unsigned short hilink_htons(unsigned short hs);

/*
 * �����������ֽ���ת�����ֽ���
 * ���������ֽ�������
 */
unsigned short hilink_ntohs(unsigned short ns);

/*
 * ���ַ�����ʽ��json���ݽ���Ϊjson�ṹ�����͵�����
 * ����NULL-����ʧ��,��NULL-�����ɹ�������ֵΪjson�ṹ��ָ��
 */
void *hilink_json_parse(const char *value);

/*
 * ��ȡjson�ṹ���е��ַ���value
 * ����NULL-��ȡʧ��,��NULL-��ȡ�ɹ�������ֵΪ�ַ���value�׵�ַ
 */
char *hilink_json_get_string_value(const void *object, const char *name, unsigned int *len);

/*
 * ��ȡjson�ṹ���е���ֵvalue
 * ����0-�ɹ�,-1-ʧ��
 */
int hilink_json_get_number_value(const void *object, const char *name, int *value);

/*
 * ��ȡjson�ṹ���е�object
 * ����NULL-����ʧ��,��NULL-�����ɹ�������ֵΪjson object�ṹ��ָ��
 */
void *hilink_json_get_object(const void *object, const char *name);

/*
 * ��ȡjson�ṹ���е�arrayԪ��
 * ����NULL-����ʧ��, ��NULL-�����ɹ�������ֵΪjson object�ṹ��ָ��
 */
void *hilink_json_get_arrayitem(const void *array, int item);

/*
 * ��ȡjson�ṹ���е�array�Ĵ�С
 * ����Ԫ������
 */
int hilink_json_get_arraysize(const void *array);

/* �ͷ�json�ṹ����ռ�õĿռ� */
void hilink_json_delete(void *object);

/* json�������ַ���������0 */
void hilink_json_clear_all_string(void *object);

/*
 * ����ϵͳ����, ����0�ɹ������ط�0ʧ��
 * ע�⣺Contiki OS ��֧�ָýӿ�,�������ȼ� level:mbed OS �̶���0,���� OS ֧���������ȼ�, ���弰ȡֵ����:
 * ���ȼ�4��TASK_PRIORITY_LOW, ���ȼ�3��TASK_PRIORITY_MIDDLE, ���ȼ�2��TASK_PRIORITY_HIGH
 */
int hilink_task_create(const void *handle, const void *taskName, int level,
    unsigned long stackLen, void *taskFunction, void *param);

/* �������� */
void hilink_task_delete(const void *handle, const void *taskName);

/*
 * ϵͳsleep, �ó�CPU
 * ����0�ɹ�����0ʧ��
 * ע�⣺1��Contiki OS ��֧�ָýӿ�
 *       2����esp8266�ϸ�ʱ����С��λΪ10ms
 */
int hilink_msleep(unsigned long ms);

/*
 * ����UDPͨѶ�׽���
 * ����С��0���ͳ������ش��ڻ����0 UDP�׽���fd
 */
int hilink_udp_new(unsigned short lport);

/* �ر�UDPͨѶ�׽��� */
void hilink_udp_remove(int fd);

/*
 * UDP��������
 * ����С��0���ͳ������ش��ڵ���0ʵ�ʷ��͵��ֽ���
 */
int hilink_udp_send(int fd, const unsigned char *buf, unsigned short len,
    const char *rip, unsigned short port);

/*
 * UDP��ȡ����
 * ����С�ڻ����0��ȡ�������ش���0ʵ�ʽ��յ����ݳ���
 */
int hilink_udp_read(int fd, unsigned char *buf, unsigned short len,
    char *rip, unsigned short ripLen, unsigned short *port);

/*
 * ����TCP����
 * ����С��0ʧ�ܣ����ش��ڻ����0 TCP�׽���
 */
int hilink_tcp_connect(const char *dst, unsigned short port);

/*
 * TCP����״̬��ȡ
 * ����0������������������ʧ��
 */
int hilink_tcp_state(int fd);

/* �Ͽ�TCP���� */
void hilink_tcp_disconnect(int fd);

/*
 * TCP��������
 * ����С��0���ͳ������ش��ڻ����0ʵ�ʷ��͵��ֽ���
 */
int hilink_tcp_send(int fd, const unsigned char *buf, unsigned short len);

/*
 * TCP��ȡ����
 * ����С�ڻ����0��ȡ�������ش���0ʵ�ʶ�ȡ���ֽ���
 */
int hilink_tcp_read(int fd, unsigned char *buf, unsigned short len);

/*
 * �ڴ�����
 * ����NULL �ڴ�����ʧ��, ��NULL �ɹ�����������ڴ�ָ��
 * ע���ڴ治��ʹ��ʱ, ��ʹ��hilink_free�ͷ�
 */
void *hilink_malloc(unsigned int size);

/*
 * �ڴ��ͷ�
 * ע��ptָ����ڴ���Ϊhilink_malloc������ڴ�
 */
void hilink_free(void *pt);

/*
 * ����Դ�����������ݵ�Ŀ�Ļ�����
 * ����0-�ɹ�, ��0-ʧ��
 * ע��: 1��ȷ��count <= dest��ָ����ڴ������С
 *       2��ȷ��dest��srcָ����ڴ�û���ص�����
 */
int hilink_memcmp(const void *buf1, const void *buf2, unsigned int len);

/*
 * ����Ŀ�Ļ�����Ϊ�ض�ֵ
 * ����0-�ɹ�, ��0-ʧ��
 * ע�����ȷ��count <= dest��ָ����ڴ������С
 */
int hilink_memset_s(void *dest, unsigned int destMax, int c, unsigned int count);

/*
 * ����Դ�����������ݵ�Ŀ�Ļ�����
 * ����0-�ɹ�, ��0-ʧ��
 * ע��: 1��ȷ��count <= dest��ָ����ڴ������С
 *       2��ȷ��dest��srcָ����ڴ�û���ص�����
 */
int hilink_memcpy_s(void *dest, unsigned int destMax, const void *src, unsigned int count);

/*
 * ����ָ�����ȵ�Դ�ַ�����Ŀ�Ļ�����
 * ����0-�ɹ�, ��0-ʧ��
 * ע�⣺ȷ��strDest��ָ�ڴ�ռ��㹻���ɿ������ַ�����
 */
int hilink_strncpy_s(char *strDest, unsigned int destMax, const char *strSrc, unsigned int count);

/*
 * ��ָ�����ȵ�Դ�ַ������ӵ�Ŀ���ַ�������
 * ����0-�ɹ�, ��0-ʧ��
 * ע�⣺ȷ��strDest��ָ�ڴ�ռ��㹻����strDestԭ���ַ���׷�ӵ�strSrc�ַ�����
 */
int hilink_strncat_s(char *strDest, unsigned int destMax, const char *strSrc, unsigned int count);

/*
 * �����ݸ�ʽ�������Ŀ�Ļ�����
 * ����-1-ʧ��, ����-ʵ��д��strDest���ֽ���
 * ע�⣺strDestҪ���㹻�Ŀռ����ɸ�ʽ�����ַ�����
 */
int hilink_sprintf_s(char *strDest, unsigned int destMax, const char *format, ...);

/*
 * �����ݰ���ָ�����ȸ�ʽ�������Ŀ�Ļ�����
 * ����-1-ʧ��, ����-��д��strDest���ֽ���
 */
int hilink_snprintf_s(char *strDest, unsigned int destMax, unsigned int count, const char *format, ...);

/*
 * ����������
 * ����HILINK_OK�ɹ�, HILINK_ERRORʧ��
 */
int hilink_mutex_create(hilink_mutex_t *mutex);

/*
 * ��ȡ������
 * ����HILINK_OK�ɹ�, HILINK_ERRORʧ��
 */
int hilink_mutex_lock(hilink_mutex_t *mutex);

/*
 * �ͷŻ�����
 * ����HILINK_OK�ɹ�, HILINK_ERRORʧ��
 */
int hilink_mutex_unlock(hilink_mutex_t *mutex);

/*
 * ���ٻ�����
 * ����HILINK_OK�ɹ�, HILINK_ERRORʧ��
 */
int hilink_mutex_destroy(hilink_mutex_t *mutex);

/*
 * Hilink SDK�ⲿ�����Ϣ��¼�ӿ�
 * �ýӿ��Ѿ������ṩ������������ʹ�ã�Ϊ��ǰ����ݣ��ݲ������±���淶����
 */
void hilink_diagnosis_record_ex(int errCode);

/*
 * ��ʽ������ַ���
 * ����ֵС��0ʧ��, ����ֵ����ʵ��������ֽ���
 */
int hilink_printf(const char *format, ...);

/*
 * ��ȡ�������ʧ��ʱ�Ĵ�����errno
 * �����������������
 */
int HiLinkGetNetWorkErrno(int fd);

#ifdef __cplusplus
}
#endif

#endif /* HILINK_OSADAPTER_H */

