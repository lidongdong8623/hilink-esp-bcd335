/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2018-2020. All rights reserved.
 * Description: 设备功能接口声明
 * Notes: 本文件根据开发者功能定义自动生成, 需要开发者适配实现。
 */
#ifndef HILINK_DEVICE_H
#define HILINK_DEVICE_H

/* ----------------------------- 供开发者修改的宏定义 ----------------------------- */
/* 开发者根据实际产品版本信息自行修改 */
#define FIRMWARE_VER "1.0.0"
#define SOFTWARE_VER "1.0.0"
#define HARDWARE_VER "1.0.0"

/* ----------------- HiLink产品模型参数宏定义, 自动生成, 请勿修改 ----------------- */
/* 设备基本信息 */
#define PRODUCT_ID "211S"
#define DEVICE_TYPE "08A"
#define MANUAFACTURER "a70"
#define DEVICE_MODEL "BCD-335"

/* 请确保设备类型英文名和厂商英文名长度之和不超过17字节 */
#define DEVICE_TYPE_NAME "Fridge"
#define MANUAFACTURER_NAME "AUCMA"

/* 通信协议类型: WIFI */
#define PROTOCOL_TYPE 1

/* 系统类型定义 */
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

/* HiLink函数预定义返回值 */
#ifndef HILINK_RET_SUCCESS
#define HILINK_RET_SUCCESS 0
#endif
#ifndef HILINK_RET_ERROR
#define HILINK_RET_ERROR -88
#endif

/* PUT命令控制接口返回值 */
#ifndef HILINK_OK
#define HILINK_OK 0
#endif
#ifndef HILINK_ERR
#define HILINK_ERR (-1)
#endif
#ifndef HILINK_PROCESSING
#define HILINK_PROCESSING (-111)
#endif

/* HiLink SDK通知开发者模组重启原因 */
#define HILINK_REBOOT_WATCHDOG 0
#define HILINK_REBOOT_DEVDELETE 1

/* HiLink SDK通知开发者设备状态 */
#define HILINK_M2M_CLOUD_OFFLINE 0       /* 设备与云端连接断开(版本向前兼容) */
#define HILINK_M2M_CLOUD_ONLINE 1        /* 设备连接云端成功, 处于正常工作态(版本向前兼容) */
#define HILINK_M2M_LONG_OFFLINE 2        /* 设备与云端连接长时间断开(版本向前兼容) */
#define HILINK_M2M_LONG_OFFLINE_REBOOT 3 /* 设备与云端连接长时间断开后进行重启(版本向前兼容) */
#define HILINK_UNINITIALIZED 4           /* HiLink线程未启动 */
#define HILINK_LINK_UNDER_AUTO_CONFIG 5  /* 设备处于配网模式 */
#define HILINK_LINK_CONFIG_TIMEOUT 6     /* 设备处于10分钟超时状态 */
#define HILINK_LINK_CONNECTTING_WIFI 7   /* 设备正在连接路由器 */
#define HILINK_LINK_CONNECTED_WIFI 8     /* 设备已经连上路由器 */
#define HILINK_M2M_CONNECTTING_CLOUD 9   /* 设备正在连接云端 */
#define HILINK_M2M_CLOUD_DISCONNECT 10   /* 设备与路由器的连接断开 */

/* 设备序列号最大长度 */
#define MAX_SN_LENGTH 40

/* ------------------------- HiLink内部调用函数，请勿修改 ------------------------- */
/* 获取当前设备版本号 */
int getDeviceVersion(char **firmwareVer, char **softwareVer, char **hardwareVer);
/* 获取BI参数接口函数 */
char *hilink_get_auto_bi_rsa_cipher(void);
/* 获取AC参数接口函数 */
unsigned char *hilink_get_auto_ac(void);

/* ----------------------------- 需要开发者实现的函数 ----------------------------- */
/* SDK通知设备状态, 开发者按需实现收到各状态后的处理 */
void hilink_notify_devstatus(int status);
/* SDK通知模组重启, 开发者按需实现各场景下重启前的处理 */
int hilink_process_before_restart(int flag);
/* SDK获取设备SN号, 开发者按需返回设备SN号 */
void HilinkGetDeviceSn(unsigned int len, char *sn);

/* ------------------------ 处理云端下发的服务控制(PUT)命令 ------------------------ */
int handle_refrigerateSwitch_cmd(bool *on);
int handle_freezeSwitch_cmd(bool *on);
int handle_intelligentSwitch_cmd(bool *on);
int handle_refrigerator_cmd(int *target);
int handle_freezer_cmd(int *target);
int handle_coolingSwitch_cmd(bool *coolingSwitch);
int handle_variableMode_cmd(int *target);

/* ------------------------ 处理云端下发的服务查询(GET)命令 ------------------------ */
int get_refrigerateSwitch_state(bool *on);
int get_freezeSwitch_state(bool *on);
int get_intelligentSwitch_state(bool *on);
int get_refrigerator_state(int *target, int *current);
int get_freezer_state(int *target, int *current);
int get_coolingSwitch_state(bool *coolingSwitch);
int get_variableMode_state(int *target);
int get_VariableRoom1_state(int *current);
int get_faultDetection_state(bool *status, int *code);

/* -------------------------- 上报(REPORT)服务状态到云端 --------------------------- */
/*
 * 功能: 上报refrigerateSwitch服务状态给APP
 * 参数: on - on属性的值
 * 返回: int：0-成功，非0-失败
 * 注意: 此函数由开发者调用
 */
int report_refrigerateSwitch_state(bool on);

/*
 * 功能: 上报freezeSwitch服务状态给APP
 * 参数: on - on属性的值
 * 返回: int：0-成功，非0-失败
 * 注意: 此函数由开发者调用
 */
int report_freezeSwitch_state(bool on);

/*
 * 功能: 上报intelligentSwitch服务状态给APP
 * 参数: on - on属性的值
 * 返回: int：0-成功，非0-失败
 * 注意: 此函数由开发者调用
 */
int report_intelligentSwitch_state(bool on);

/*
 * 功能: 上报refrigerator服务状态给APP
 * 参数: target - target属性的值
 *       current - current属性的值
 * 返回: int：0-成功，非0-失败
 * 注意: 此函数由开发者调用
 */
int report_refrigerator_state(int target, int current);

/*
 * 功能: 上报freezer服务状态给APP
 * 参数: target - target属性的值
 *       current - current属性的值
 * 返回: int：0-成功，非0-失败
 * 注意: 此函数由开发者调用
 */
int report_freezer_state(int target, int current);

/*
 * 功能: 上报coolingSwitch服务状态给APP
 * 参数: coolingSwitch - coolingSwitch属性的值
 * 返回: int：0-成功，非0-失败
 * 注意: 此函数由开发者调用
 */
int report_coolingSwitch_state(bool coolingSwitch);

/*
 * 功能: 上报variableMode服务状态给APP
 * 参数: target - target属性的值
 * 返回: int：0-成功，非0-失败
 * 注意: 此函数由开发者调用
 */
int report_variableMode_state(int target);

/*
 * 功能: 上报VariableRoom1服务状态给APP
 * 参数: current - current属性的值
 * 返回: int：0-成功，非0-失败
 * 注意: 此函数由开发者调用
 */
int report_VariableRoom1_state(int current);

/*
 * 功能: 上报report_faultDetection_state服务状态给APP
 * 参数: status - 是否检测到错误或者故障
 *       code - 故障错误码
 * 返回: int：0-成功，非0-失败
 * 注意: 此函数由设备厂商调用
 */
int report_faultDetection_state(bool status, int code);

#endif /* HILINK_DEVICE_H */
