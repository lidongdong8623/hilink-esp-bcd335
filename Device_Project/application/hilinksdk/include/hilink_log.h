/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2018-2020. All rights reserved.
 * Description: HiLink SDK日志打印接口头文件
 * Notes: 本文件已提供外部使用, 为保证兼容性, 接口和类型定义暂不按照编程规范修改
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
    LOG_LVL_INVALID = -1, /* 消除CodeDex警告, 请不要用此值 */
    LOG_LVL_MIN     = 0,
    LOG_LVL_EMERG   = 0, /* 非常紧急, 系统不可用 */
    LOG_LVL_ALERT   = 1, /* 紧急级别, 必须立即采取措施 */
    LOG_LVL_CRIT    = 2, /* 致命级别 */
    LOG_LVL_ERR     = 3, /* 错误级别 */
    LOG_LVL_WARN    = 4, /* 告警级别 */
    LOG_LVL_NOTICE  = 5, /* 通知级别 */
    LOG_LVL_INFO    = 6, /* 信息级别 */
    LOG_LVL_DEBUG   = 7, /* 调试级别 */
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
