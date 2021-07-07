/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2018-2020. All rights reserved.
 * Description: HiLink SDK��־��ӡ�ӿ�ͷ�ļ�
 * Notes: ���ļ����ṩ�ⲿʹ��, Ϊ��֤������, �ӿں����Ͷ����ݲ����ձ�̹淶�޸�
 */
#ifndef HILINK_LOG_H
#define HILINK_LOG_H

#include "hilink_typedef.h"
#include "hilink_osadapter.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef ENABLE_LOG

typedef enum {
    LOG_LVL_INVALID = -1, /* ����CodeDex����, �벻Ҫ�ô�ֵ */
    LOG_LVL_MIN     = 0,
    LOG_LVL_EMERG   = 0, /* �ǳ�����, ϵͳ������ */
    LOG_LVL_ALERT   = 1, /* ��������, ����������ȡ��ʩ */
    LOG_LVL_CRIT    = 2, /* �������� */
    LOG_LVL_ERR     = 3, /* ���󼶱� */
    LOG_LVL_WARN    = 4, /* �澯���� */
    LOG_LVL_NOTICE  = 5, /* ֪ͨ���� */
    LOG_LVL_INFO    = 6, /* ��Ϣ���� */
    LOG_LVL_DEBUG   = 7, /* ���Լ��� */
    LOG_LVL_MAX     = LOG_LVL_DEBUG
} debug_level_t;

bool log_is_print(debug_level_t level);
void set_log_level(debug_level_t level);

#define hilink_data(...) \
    do { \
        hilink_printf(__VA_ARGS__); \
    } while (0)

#define hilink_debug(...) \
    do { \
        if (log_is_print(LOG_LVL_DEBUG)) { \
            hilink_printf("%s() %d, ",  __func__, __LINE__); \
            hilink_printf(__VA_ARGS__); \
        } \
    } while (0)

#define hilink_info(...) \
    do { \
        if (log_is_print(LOG_LVL_INFO)) { \
            hilink_printf("%s() %d, ",  __func__, __LINE__); \
            hilink_printf(__VA_ARGS__); \
        } \
    } while (0)

#define hilink_notice(...) \
    do { \
        if (log_is_print(LOG_LVL_NOTICE)) { \
            hilink_printf("%s() %d, ",  __func__, __LINE__); \
            hilink_printf(__VA_ARGS__); \
        } \
    } while (0)

#define hilink_warning(...) \
    do { \
        if (log_is_print(LOG_LVL_WARN)) { \
            hilink_printf("%s() %d, ",  __func__, __LINE__); \
            hilink_printf(__VA_ARGS__); \
        } \
    } while (0)

#define hilink_error(...) \
    do { \
        if (log_is_print(LOG_LVL_ERR)) { \
            hilink_printf("%s() %d, ",  __func__, __LINE__); \
            hilink_printf(__VA_ARGS__); \
        } \
    } while (0)

#define hilink_critical(...) \
    do { \
        if (log_is_print(LOG_LVL_CRIT)) { \
            hilink_printf("%s() %d, ",  __func__, __LINE__); \
            hilink_printf(__VA_ARGS__); \
        } \
    } while (0)

#define hilink_alert(...) \
    do { \
        if (log_is_print(LOG_LVL_ALERT)) { \
            hilink_printf("%s() %d, ", __func__, __LINE__); \
            hilink_printf(__VA_ARGS__); \
        } \
    } while (0)

#define hilink_emerg(...) \
    do { \
        if (log_is_print(LOG_LVL_EMERG)) { \
            hilink_printf("%s() %d, ",  __func__, __LINE__); \
            hilink_printf(__VA_ARGS__); \
        } \
    } while (0)

#else

#define hilink_data(...)
#define hilink_debug(...)
#define hilink_info(...)
#define hilink_notice(...)
#define hilink_warning(...)
#define hilink_error(...)
#define hilink_critical(...)
#define hilink_alert(...)
#define hilink_emerg(...)

#endif /* ENABLE_LOG */

#ifdef __cplusplus
}
#endif

#endif /* HILINK_LOG_H */
