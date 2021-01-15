/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2018-2020. All rights reserved.
 * Description: 设备功能接口定义
 * Notes: 本文件根据开发者功能定义自动生成, 需要开发者适配实现。
 */
#include "hilink_device.h"
#include <stdlib.h>

/*
 * 功能: 获取设备相关版本号
 * 参数: firmwareVer - 固件版本
 *       softwareVer - 软件版本
 *       hardwareVer - 硬件版本
 * 返回: 无
 * 注意: HiLink内部调用函数, 请勿修改
 */
int getDeviceVersion(char **firmwareVer, char **softwareVer, char **hardwareVer)
{
    *firmwareVer = FIRMWARE_VER;
    *softwareVer = SOFTWARE_VER;
    *hardwareVer = HARDWARE_VER;
    return HILINK_RET_SUCCESS;
}

/*
 * 功能: SDK通知设备状态, 开发者按需实现收到各状态后的处理
 * 参数: status - 设备当前状态
 * 返回: 无
 * 注意: 此函数由开发者根据产品业务选择性实现
 */
void hilink_notify_devstatus(int status)
{
    switch (status) {
        case HILINK_M2M_CLOUD_OFFLINE:
            /* 设备与云端连接断开, 请在此处添加实现 */
            break;
        case HILINK_M2M_CLOUD_ONLINE:
            /* 设备连接云端成功, 请在此处添加实现 */
            break;
        case HILINK_M2M_LONG_OFFLINE:
            /* 设备与云端连接长时间断开, 请在此处添加实现 */
            break;
        case HILINK_M2M_LONG_OFFLINE_REBOOT:
            /* 设备与云端连接长时间断开后进行重启, 请在此处添加实现 */
            break;
        case HILINK_UNINITIALIZED:
            /* HiLink线程未启动, 请在此处添加实现 */
            break;
        case HILINK_LINK_UNDER_AUTO_CONFIG:
            /* 设备处于配网模式, 请在此处添加实现 */
            break;
        case HILINK_LINK_CONFIG_TIMEOUT:
            /* 设备处于10分钟超时状态, 请在此处添加实现 */
            break;
        case HILINK_LINK_CONNECTTING_WIFI:
            /* 设备正在连接路由器, 请在此处添加实现 */
            break;
        case HILINK_LINK_CONNECTED_WIFI:
            /* 设备已经连上路由器, 请在此处添加实现 */
            break;
        case HILINK_M2M_CONNECTTING_CLOUD:
            /* 设备正在连接云端, 请在此处添加实现 */
            break;
        case HILINK_M2M_CLOUD_DISCONNECT:
            /* 设备与路由器的连接断开, 请在此处添加实现 */
            break;
        default:
            break;
    }
}

/*
 * 功能: SDK通知模组重启, 开发者按需实现各场景下重启前的处理
 * 参数: flag 0-表示HiLink SDK 线程看门狗触发模组重启; 1-表示App删除设备触发模组重启
 * 返回: 0-处理成功,系统可以重启,使用硬重启;1-处理成功,系统可以重启,使用软重启(软重启接口需要厂家提前适配并注册);负值-处理失败,系统不能重启
 * 注意: 1) 若APP删除设备触发模组重启时, 设备操作完务必返回0, 否则会导致删除设备异常;
 *       2) 此函数由开发者实现
 */
int hilink_process_before_restart(int flag)
{
    /* HiLink SDK线程看门狗超时触发模组重启 */
    if (flag == HILINK_REBOOT_WATCHDOG) {
        /* 实现模组重启前的操作(如:保存系统状态等), 待操作成功完成后返回0允许重启 */
        return -1;
    }
    /* APP删除设备触发模组重启 */
    else if (flag == HILINK_REBOOT_DEVDELETE) {
        /* 实现模组重启前的操作(如:保存系统状态等) */
        return 0;
    }
    /* 参数异常 */
    else {
        return -1;
    }
}

/*
 * 功能: 获取设备PIN码
 * 参数: 无
 * 返回: int 返回数字PIN码或-1
 * 注意: 若设备采用自定义PIN码, 则函数返回8位数字PIN码(如13572468);
 *       若设备采用默认PIN码, 则函数返回-1.
 */
int HiLinkGetPinCode(void)
{
    /* 由开发者实现, 将设备PIN码返回 */
    return -1;
}

/*
 * 功能: 获取设备SN号
 * 参数: unsigned int len 限定SN最大长度为39字节
 * 返回: 无
 * 注意: 输出sn指针的字符串长度为0时将使用设备mac地址作为sn
 */
void HilinkGetDeviceSn(unsigned int len, char *sn)
{
    /* 由开发者实现, 将设备SN号赋予出参 */
    return;
}

/* ------------------------ 处理云端下发的服务控制(PUT)命令 ------------------------ */
/*
 * 功能: 处理refrigerateSwitch服务的控制命令
 * 参数: on - on属性的值
 * 返回: HILINK_OK - 操作成功, 设备状态已改变
 *       HILINK_ERR - 操作失败, 设备状态未改变
 *       HILINK_PROCESSING - 正在操作中, 设备状态尚未改变
 * 注意: 1) 返回HILINK_PROCESSING表示设备正在进行异步操作, 待操作完成设备状态改变,
 *          需要主动调用report接口将变更的新状态上报给App;
 *       2) 此函数由开发者实现.
 */
int handle_refrigerateSwitch_cmd(bool *on)
{
    /* 实现对on属性的修改 */
    if (on != NULL) {
        /* 请在此处实现设备状态改变的操作 */
    }

    /* 若同步操作改变设备状态, 状态改变后, 返回HILINK_OK */
    /* 若异步操作改变设备状态, 此处返回HILINK_PROCESSING, 待状态改变后主动上报新状态 */
    return HILINK_OK;
}

/*
 * 功能: 处理freezeSwitch服务的控制命令
 * 参数: on - on属性的值
 * 返回: HILINK_OK - 操作成功, 设备状态已改变
 *       HILINK_ERR - 操作失败, 设备状态未改变
 *       HILINK_PROCESSING - 正在操作中, 设备状态尚未改变
 * 注意: 1) 返回HILINK_PROCESSING表示设备正在进行异步操作, 待操作完成设备状态改变,
 *          需要主动调用report接口将变更的新状态上报给App;
 *       2) 此函数由开发者实现.
 */
int handle_freezeSwitch_cmd(bool *on)
{
    /* 实现对on属性的修改 */
    if (on != NULL) {
        /* 请在此处实现设备状态改变的操作 */
    }

    /* 若同步操作改变设备状态, 状态改变后, 返回HILINK_OK */
    /* 若异步操作改变设备状态, 此处返回HILINK_PROCESSING, 待状态改变后主动上报新状态 */
    return HILINK_OK;
}

/*
 * 功能: 处理intelligentSwitch服务的控制命令
 * 参数: on - on属性的值
 * 返回: HILINK_OK - 操作成功, 设备状态已改变
 *       HILINK_ERR - 操作失败, 设备状态未改变
 *       HILINK_PROCESSING - 正在操作中, 设备状态尚未改变
 * 注意: 1) 返回HILINK_PROCESSING表示设备正在进行异步操作, 待操作完成设备状态改变,
 *          需要主动调用report接口将变更的新状态上报给App;
 *       2) 此函数由开发者实现.
 */
int handle_intelligentSwitch_cmd(bool *on)
{
    /* 实现对on属性的修改 */
    if (on != NULL) {
        /* 请在此处实现设备状态改变的操作 */
    }

    /* 若同步操作改变设备状态, 状态改变后, 返回HILINK_OK */
    /* 若异步操作改变设备状态, 此处返回HILINK_PROCESSING, 待状态改变后主动上报新状态 */
    return HILINK_OK;
}

/*
 * 功能: 处理refrigerator服务的控制命令
 * 参数: target - target属性的值
 * 返回: HILINK_OK - 操作成功, 设备状态已改变
 *       HILINK_ERR - 操作失败, 设备状态未改变
 *       HILINK_PROCESSING - 正在操作中, 设备状态尚未改变
 * 注意: 1) 返回HILINK_PROCESSING表示设备正在进行异步操作, 待操作完成设备状态改变,
 *          需要主动调用report接口将变更的新状态上报给App;
 *       2) 此函数由开发者实现.
 */
int handle_refrigerator_cmd(int *target)
{
    /* 实现对target属性的修改 */
    if (target != NULL) {
        /* 请在此处实现设备状态改变的操作 */
    }

    /* 若同步操作改变设备状态, 状态改变后, 返回HILINK_OK */
    /* 若异步操作改变设备状态, 此处返回HILINK_PROCESSING, 待状态改变后主动上报新状态 */
    return HILINK_OK;
}

/*
 * 功能: 处理freezer服务的控制命令
 * 参数: target - target属性的值
 * 返回: HILINK_OK - 操作成功, 设备状态已改变
 *       HILINK_ERR - 操作失败, 设备状态未改变
 *       HILINK_PROCESSING - 正在操作中, 设备状态尚未改变
 * 注意: 1) 返回HILINK_PROCESSING表示设备正在进行异步操作, 待操作完成设备状态改变,
 *          需要主动调用report接口将变更的新状态上报给App;
 *       2) 此函数由开发者实现.
 */
int handle_freezer_cmd(int *target)
{
    /* 实现对target属性的修改 */
    if (target != NULL) {
        /* 请在此处实现设备状态改变的操作 */
    }

    /* 若同步操作改变设备状态, 状态改变后, 返回HILINK_OK */
    /* 若异步操作改变设备状态, 此处返回HILINK_PROCESSING, 待状态改变后主动上报新状态 */
    return HILINK_OK;
}

/*
 * 功能: 处理coolingSwitch服务的控制命令
 * 参数: coolingSwitch - coolingSwitch属性的值
 * 返回: HILINK_OK - 操作成功, 设备状态已改变
 *       HILINK_ERR - 操作失败, 设备状态未改变
 *       HILINK_PROCESSING - 正在操作中, 设备状态尚未改变
 * 注意: 1) 返回HILINK_PROCESSING表示设备正在进行异步操作, 待操作完成设备状态改变,
 *          需要主动调用report接口将变更的新状态上报给App;
 *       2) 此函数由开发者实现.
 */
int handle_coolingSwitch_cmd(bool *coolingSwitch)
{
    /* 实现对coolingSwitch属性的修改 */
    if (coolingSwitch != NULL) {
        /* 请在此处实现设备状态改变的操作 */
    }

    /* 若同步操作改变设备状态, 状态改变后, 返回HILINK_OK */
    /* 若异步操作改变设备状态, 此处返回HILINK_PROCESSING, 待状态改变后主动上报新状态 */
    return HILINK_OK;
}

/*
 * 功能: 处理variableMode服务的控制命令
 * 参数: target - target属性的值
 * 返回: HILINK_OK - 操作成功, 设备状态已改变
 *       HILINK_ERR - 操作失败, 设备状态未改变
 *       HILINK_PROCESSING - 正在操作中, 设备状态尚未改变
 * 注意: 1) 返回HILINK_PROCESSING表示设备正在进行异步操作, 待操作完成设备状态改变,
 *          需要主动调用report接口将变更的新状态上报给App;
 *       2) 此函数由开发者实现.
 */
int handle_variableMode_cmd(int *target)
{
    /* 实现对target属性的修改 */
    if (target != NULL) {
        /* 请在此处实现设备状态改变的操作 */
    }

    /* 若同步操作改变设备状态, 状态改变后, 返回HILINK_OK */
    /* 若异步操作改变设备状态, 此处返回HILINK_PROCESSING, 待状态改变后主动上报新状态 */
    return HILINK_OK;
}

/* ------------------------ 处理云端下发的服务查询(GET)命令 ------------------------ */
/*
 * 功能: 处理refrigerateSwitch服务的状态查询命令
 * 参数: on - on属性的值
 * 返回: 0-成功, 非0-失败
 * 注意: 此函数由开发者实现
 */
int get_refrigerateSwitch_state(bool *on)
{
    /* 由开发者实现, 将refrigerateSwitch服务的属性当前值赋予出参 */
    return HILINK_RET_SUCCESS;
}

/*
 * 功能: 处理freezeSwitch服务的状态查询命令
 * 参数: on - on属性的值
 * 返回: 0-成功, 非0-失败
 * 注意: 此函数由开发者实现
 */
int get_freezeSwitch_state(bool *on)
{
    /* 由开发者实现, 将freezeSwitch服务的属性当前值赋予出参 */
    return HILINK_RET_SUCCESS;
}

/*
 * 功能: 处理intelligentSwitch服务的状态查询命令
 * 参数: on - on属性的值
 * 返回: 0-成功, 非0-失败
 * 注意: 此函数由开发者实现
 */
int get_intelligentSwitch_state(bool *on)
{
    /* 由开发者实现, 将intelligentSwitch服务的属性当前值赋予出参 */
    return HILINK_RET_SUCCESS;
}

/*
 * 功能: 处理refrigerator服务的状态查询命令
 * 参数: target - target属性的值
 *       current - current属性的值
 * 返回: 0-成功, 非0-失败
 * 注意: 此函数由开发者实现
 */
int get_refrigerator_state(int *target, int *current)
{
    /* 由开发者实现, 将refrigerator服务的属性当前值赋予出参 */
    return HILINK_RET_SUCCESS;
}

/*
 * 功能: 处理freezer服务的状态查询命令
 * 参数: target - target属性的值
 *       current - current属性的值
 * 返回: 0-成功, 非0-失败
 * 注意: 此函数由开发者实现
 */
int get_freezer_state(int *target, int *current)
{
    /* 由开发者实现, 将freezer服务的属性当前值赋予出参 */
    return HILINK_RET_SUCCESS;
}

/*
 * 功能: 处理coolingSwitch服务的状态查询命令
 * 参数: coolingSwitch - coolingSwitch属性的值
 * 返回: 0-成功, 非0-失败
 * 注意: 此函数由开发者实现
 */
int get_coolingSwitch_state(bool *coolingSwitch)
{
    /* 由开发者实现, 将coolingSwitch服务的属性当前值赋予出参 */
    return HILINK_RET_SUCCESS;
}

/*
 * 功能: 处理variableMode服务的状态查询命令
 * 参数: target - target属性的值
 * 返回: 0-成功, 非0-失败
 * 注意: 此函数由开发者实现
 */
int get_variableMode_state(int *target)
{
    /* 由开发者实现, 将variableMode服务的属性当前值赋予出参 */
    return HILINK_RET_SUCCESS;
}

/*
 * 功能: 处理VariableRoom1服务的状态查询命令
 * 参数: current - current属性的值
 * 返回: 0-成功, 非0-失败
 * 注意: 此函数由开发者实现
 */
int get_VariableRoom1_state(int *current)
{
    /* 由开发者实现, 将VariableRoom1服务的属性当前值赋予出参 */
    return HILINK_RET_SUCCESS;
}

/*
 * 功能: 获取faultDetection服务状态给App
 * 参数: status - 是否检测到错误或者故障
 *       code - 故障错误码
 * 返回: 0-成功, 非0-失败
 * 注意: 此函数提供给开发者调用
 */
int get_faultDetection_state(bool *status, int *code)
{
    /* 由开发者实现, 将服务faultDetection属性当前值赋予出参 */
    return HILINK_RET_SUCCESS;
}

/*
 * 功能: 获取设备的子型号，长度固定两个字节
 * 参数: subProdId为保存子型号的缓冲区，len为缓冲区的长度
 * 返回: int 返回数字0或-1
 * 注意: 如果产品定义有子型号，则填入两字节子型号，并以' '结束, 返回0;
 *       没有定义子型号，则返回-1.
 */
int HILINK_GetSubProdId(char *subProdId, int len)
{
    return -1;
}

int HILINK_GetDevSurfacePower(char *power)
{
    return -1;
}
