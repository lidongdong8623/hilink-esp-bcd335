/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2018-2020. All rights reserved.
<<<<<<< HEAD
 * Description: HiLink SDK???????????
 * Notes: ???????????????????????????, ??????????????
=======
 * Description: HiLink SDK控制处理流程
 * Notes: 本文件根据开发者功能定义自动生成, 若无必要无需修改。
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
 */
#include "hilink_device.h"
#include <stdlib.h>
#include "hilink_log.h"
#include "hilink_osadapter.h"

#define M2M_NO_ERROR 0
#define M2M_SVC_RPT_CREATE_PAYLOAD_ERR -201

<<<<<<< HEAD
typedef struct
{
    const char *sn;     /* ?蠀蟿|路????SN??, ?????|?(0,40] */
    const char *prodId; /* ?蠀蟿HiLink?????, ?????|?(0,5] */
    const char *model;  /* ?蠀蟿???, ?????|?(0,32] */
    const char *dev_t;  /* ?蠀蟿????, ?????|?(0,4] */
    const char *manu;   /* ?蠀蟿??????, ?????|?(0,4] */
    const char *mac;    /* ?蠀蟿MAC???, ???32??? */
    const char *hiv;    /* ?蠀蟿HiLink搂???路?, ?????|?(0,32] */
    const char *fwv;    /* ?蠀蟿????路?, ?????|?[0,64] */
    const char *hwv;    /* ?蠀蟿????路?, ?????|?[0,64] */
    const char *swv;    /* ?蠀蟿?????路?, ?????|?[0,64] */
    const int prot_t;   /* ?蠀蟿搂???????, ????|?[1,3] */
} dev_info_t;

/* ???: ?蠀蟿????????????????????????????????17??? */
typedef struct
{
    const char *devTypeName; /* ?蠀蟿??????????? */
    const char *manuName;    /* ??????????? */
} DevNameEn;

typedef struct
{
    const char *st;     /* ????????, ?????|?(0,32] */
    const char *svc_id; /* ????ID, ?????|?(0,64] */
} svc_info_t;

/* ?蠀蟿??????? */
=======
typedef struct {
    const char *sn;     /* 设备唯一标识SN号, 长度范围(0,40] */
    const char *prodId; /* 设备HiLink认证号, 长度范围(0,5] */
    const char *model;  /* 设备型号, 长度范围(0,32] */
    const char *dev_t;  /* 设备类型, 长度范围(0,4] */
    const char *manu;   /* 设备制造商, 长度范围(0,4] */
    const char *mac;    /* 设备MAC地址, 固定32字节 */
    const char *hiv;    /* 设备HiLink协议版本, 长度范围(0,32] */
    const char *fwv;    /* 设备固件版本, 长度范围[0,64] */
    const char *hwv;    /* 设备硬件版本, 长度范围[0,64] */
    const char *swv;    /* 设备软件版本, 长度范围[0,64] */
    const int prot_t;   /* 设备协议类型, 取值范围[1,3] */
} dev_info_t;

/* 注意: 设备类型英文名和厂商英文名长度之和不能超过17字节 */
typedef struct {
    const char *devTypeName; /* 设备类型英文名称 */
    const char *manuName;    /* 厂商英文名称 */
} DevNameEn;

typedef struct {
    const char *st;     /* 服务类型, 长度范围(0,32] */
    const char *svc_id; /* 服务ID, 长度范围(0,64] */
} svc_info_t;

/* 设备信息定义 */
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
dev_info_t dev_info = {
    "Device SN",
    PRODUCT_ID,
    DEVICE_MODEL,
    DEVICE_TYPE,
    MANUAFACTURER,
    "Device Mac",
    "1.0.0",
    "1.0.0",
    "1.0.0",
    "1.0.0",
<<<<<<< HEAD
    PROTOCOL_TYPE};

/* ?蠀蟿???????, ?????????????????????????????17??? */
DevNameEn g_devNameEn = {
    DEVICE_TYPE_NAME,
    MANUAFACTURER_NAME};

/* ???????? */
int gSvcNum = 8;
/* ??????????? */
svc_info_t gSvcInfo[] = {
    {"refrigerateSwitch", "refrigerateSwitch"},
    {"freezeSwitch", "freezeSwitch"},
    {"intelligentSwitch", "intelligentSwitch"},
    {"refrigerator", "refrigerator"},
    {"freezer", "freezer"},
    {"coolingSwitch", "coolingSwitch"},
    {"variableTemper", "variableTemper"},
    {"VariableRoom1", "VariableRoom1"}};

/* AC? */
unsigned char A_C[48] = {
    0x70, 0x4F, 0x62, 0x44, 0x53, 0x72, 0x78, 0x66, 0x32, 0x34, 0x59, 0x5E, 0x34, 0x46, 0x21, 0x6C,
    0xE0, 0x2B, 0x1F, 0xE2, 0x2E, 0x8E, 0x97, 0xFB, 0xCD, 0x67, 0x19, 0xB5, 0x4E, 0x59, 0xCB, 0xB6,
    0xB9, 0x9A, 0x09, 0xE5, 0x1D, 0x96, 0xAF, 0x27, 0x9A, 0xB4, 0xD1, 0x85, 0x98, 0xB5, 0x67, 0xF3};

/* BI? */
char *bi_rsacipher = "3A69EC5BF4E27E47D9648A894A54DD99260652408373E3394460ABA1C775D5695ECCC9028D831ECAF635C894DAAFCFE9476792CA7A46B5659D8D103D98E83342E09F58115BA1BEA1C5B893A69BBA4F4474FB65D0B78D0FA7DA2CA39E046B741B46E871C4FA3C7A7EA0BA7F966DD171846FE151838A41D9FAB2576271AEE9002E36DB5348C099C7D3349E32F092BE5DABD9FBA7B93B74105FB4E1B085653E38BF29F81F7755C8A101786EB39721FA4A484EF48B3D4149BE85DEB6FE815BC5F91F7166BEE8C73F0FC98AA4A7A5619BCC8CF0F3C2DE3BC56D8D5C0D101D8F0C31F8A68C0C74CFA8BADEA70F515CEC5238AAEEBA2E6ACBBADDDDDFD7E8C991D096A0";

/* ?蠀蟿??????????????????? */
=======
    PROTOCOL_TYPE
};

/* 设备名称定义, 请确保这两个英文名称长度之和不超过17字节 */
DevNameEn g_devNameEn = {
    DEVICE_TYPE_NAME,
    MANUAFACTURER_NAME
};

/* 服务数量 */
int gSvcNum = 8;
/* 服务信息定义 */
svc_info_t gSvcInfo[] = {
    { "refrigerateSwitch", "refrigerateSwitch" },
    { "freezeSwitch", "freezeSwitch" },
    { "intelligentSwitch", "intelligentSwitch" },
    { "refrigerator", "refrigerator" },
    { "freezer", "freezer" },
    { "coolingSwitch", "coolingSwitch" },
    { "variableMode", "variableMode" },
    { "VariableRoom1", "VariableRoom1" }
};

/* AC值 */
unsigned char A_C[48] = {
    0x70, 0x4F, 0x62, 0x44, 0x53, 0x72, 0x78, 0x66, 0x32, 0x34, 0x59, 0x5E, 0x34, 0x46, 0x21, 0x6C,
    0xE0, 0x2B, 0x1F, 0xE2, 0x2E, 0x8E, 0x97, 0xFB, 0xCD, 0x67, 0x19, 0xB5, 0x4E, 0x59, 0xCB, 0xB6,
    0xB9, 0x9A, 0x09, 0xE5, 0x1D, 0x96, 0xAF, 0x27, 0x9A, 0xB4, 0xD1, 0x85, 0x98, 0xB5, 0x67, 0xF3 
};

/* BI值 */
char *bi_rsacipher = "";

/* 设备服务属性数据类型定义 */
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
#define DTYPE_BOOL 0
#define DTYPE_INT 1
#define DTYPE_STRING 2
#define DTYPE_ENUM 3
#define DTYPE_ARRAY 4

<<<<<<< HEAD
/* ?蠀蟿????????????????? */
=======
/* 设备服务属性操作权限定义 */
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
#define OPR_REPORT 0x01
#define OPR_GET 0x02
#define OPR_PUT 0x04

<<<<<<< HEAD
/* ??搂???json??????? */
=======
/* 无效的json报文解析 */
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
#ifndef INVALID_PACKET
#define INVALID_PACKET -87
#endif

<<<<<<< HEAD
/* ????????????? */
typedef struct
{
    char *name;                /* ?????? */
    unsigned char type;        /* ???????? */
    unsigned char permissions; /* ??????? */
} SRV_PROPERTY_S;

/* ????????????? */
typedef struct
{
    char *id;                    /* ????ID, ????????????? */
    char *type;                  /* ???????? */
    int prop_count;              /* ????????? */
    const SRV_PROPERTY_S *props; /* ?????搂?? */
} SRV_INFO_S;

/* ?蠀蟿????Service???????? */
=======
/* 服务属性结构定义 */
typedef struct {
    char *name; /* 属性名 */
    unsigned char type; /* 数据类型 */
    unsigned char permissions; /* 操作权限 */
} SRV_PROPERTY_S;

/* 服务属性结构定义 */
typedef struct {
    char *id; /* 服务ID, 服务的字符串标识 */
    char *type; /* 服务类型 */
    int prop_count; /* 属性的数量 */
    const SRV_PROPERTY_S *props; /* 属性列表 */
} SRV_INFO_S;

/* 设备服务Service数组索引 */
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
#define SRV_IDX_REFRIGERATESWITCH 0
#define SRV_IDX_FREEZESWITCH 1
#define SRV_IDX_INTELLIGENTSWITCH 2
#define SRV_IDX_REFRIGERATOR 3
#define SRV_IDX_FREEZER 4
#define SRV_IDX_COOLINGSWITCH 5
<<<<<<< HEAD
#define SRV_IDX_VARIABLETEMPER 6
#define SRV_IDX_VARIABLEROOM1 7
/* ?蠀蟿??????????? */
#define SRV_TOTAL_COUNT 8

/* ????refrigerateSwitch???? */
#define REFRIGERATESWITCH_PROP_COUNT 1
#define REFRIGERATESWITCH_ON_IDX 0
const SRV_PROPERTY_S refrigerateSwitch_props[REFRIGERATESWITCH_PROP_COUNT] = {
    {"on", DTYPE_BOOL, OPR_GET | OPR_PUT | OPR_REPORT}};

/* ????freezeSwitch???? */
#define FREEZESWITCH_PROP_COUNT 1
#define FREEZESWITCH_ON_IDX 0
const SRV_PROPERTY_S freezeSwitch_props[FREEZESWITCH_PROP_COUNT] = {
    {"on", DTYPE_BOOL, OPR_GET | OPR_PUT | OPR_REPORT}};

/* ????intelligentSwitch???? */
#define INTELLIGENTSWITCH_PROP_COUNT 1
#define INTELLIGENTSWITCH_ON_IDX 0
const SRV_PROPERTY_S intelligentSwitch_props[INTELLIGENTSWITCH_PROP_COUNT] = {
    {"on", DTYPE_BOOL, OPR_GET | OPR_PUT | OPR_REPORT}};

/* ????refrigerator???? */
=======
#define SRV_IDX_VARIABLEMODE 6
#define SRV_IDX_VARIABLEROOM1 7
/* 设备服务的总数量 */
#define SRV_TOTAL_COUNT 8

/* 服务refrigerateSwitch定义 */
#define REFRIGERATESWITCH_PROP_COUNT 1
#define REFRIGERATESWITCH_ON_IDX 0
const SRV_PROPERTY_S refrigerateSwitch_props[REFRIGERATESWITCH_PROP_COUNT] = {
    { "on", DTYPE_BOOL, OPR_GET | OPR_PUT | OPR_REPORT }
};

/* 服务freezeSwitch定义 */
#define FREEZESWITCH_PROP_COUNT 1
#define FREEZESWITCH_ON_IDX 0
const SRV_PROPERTY_S freezeSwitch_props[FREEZESWITCH_PROP_COUNT] = {
    { "on", DTYPE_BOOL, OPR_GET | OPR_PUT | OPR_REPORT }
};

/* 服务intelligentSwitch定义 */
#define INTELLIGENTSWITCH_PROP_COUNT 1
#define INTELLIGENTSWITCH_ON_IDX 0
const SRV_PROPERTY_S intelligentSwitch_props[INTELLIGENTSWITCH_PROP_COUNT] = {
    { "on", DTYPE_BOOL, OPR_GET | OPR_PUT | OPR_REPORT }
};

/* 服务refrigerator定义 */
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
#define REFRIGERATOR_PROP_COUNT 2
#define REFRIGERATOR_TARGET_IDX 0
#define REFRIGERATOR_CURRENT_IDX 1
const SRV_PROPERTY_S refrigerator_props[REFRIGERATOR_PROP_COUNT] = {
<<<<<<< HEAD
    {"target", DTYPE_INT, OPR_GET | OPR_PUT | OPR_REPORT},
    {"current", DTYPE_INT, OPR_GET | OPR_REPORT}};

/* ????freezer???? */
=======
    { "target", DTYPE_INT, OPR_GET | OPR_PUT | OPR_REPORT },
    { "current", DTYPE_INT, OPR_GET | OPR_REPORT }
};

/* 服务freezer定义 */
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
#define FREEZER_PROP_COUNT 2
#define FREEZER_TARGET_IDX 0
#define FREEZER_CURRENT_IDX 1
const SRV_PROPERTY_S freezer_props[FREEZER_PROP_COUNT] = {
<<<<<<< HEAD
    {"target", DTYPE_INT, OPR_GET | OPR_PUT | OPR_REPORT},
    {"current", DTYPE_INT, OPR_GET | OPR_REPORT}};

/* ????coolingSwitch???? */
#define COOLINGSWITCH_PROP_COUNT 1
#define COOLINGSWITCH_COOLINGSWITCH_IDX 0
const SRV_PROPERTY_S coolingSwitch_props[COOLINGSWITCH_PROP_COUNT] = {
    {"coolingSwitch", DTYPE_BOOL, OPR_GET | OPR_PUT | OPR_REPORT}};

/* ????variableTemper???? */
#define VARIABLETEMPER_PROP_COUNT 1
#define VARIABLETEMPER_TARGET_IDX 0
const SRV_PROPERTY_S variableTemper_props[VARIABLETEMPER_PROP_COUNT] = {
    {"target", DTYPE_INT, OPR_GET | OPR_PUT | OPR_REPORT}};

/* ????VariableRoom1???? */
#define VARIABLEROOM1_PROP_COUNT 1
#define VARIABLEROOM1_CURRENT_IDX 0
const SRV_PROPERTY_S VariableRoom1_props[VARIABLEROOM1_PROP_COUNT] = {
    {"current", DTYPE_INT, OPR_GET | OPR_REPORT}};

/* ?蠀蟿???????搂?? */
=======
    { "target", DTYPE_INT, OPR_GET | OPR_PUT | OPR_REPORT },
    { "current", DTYPE_INT, OPR_GET | OPR_REPORT }
};

/* 服务coolingSwitch定义 */
#define COOLINGSWITCH_PROP_COUNT 1
#define COOLINGSWITCH_COOLINGSWITCH_IDX 0
const SRV_PROPERTY_S coolingSwitch_props[COOLINGSWITCH_PROP_COUNT] = {
    { "coolingSwitch", DTYPE_BOOL, OPR_GET | OPR_PUT | OPR_REPORT }
};

/* 服务variableMode定义 */
#define VARIABLEMODE_PROP_COUNT 1
#define VARIABLEMODE_TARGET_IDX 0
const SRV_PROPERTY_S variableMode_props[VARIABLEMODE_PROP_COUNT] = {
    { "target", DTYPE_ENUM, OPR_GET | OPR_PUT | OPR_REPORT }
};

/* 服务VariableRoom1定义 */
#define VARIABLEROOM1_PROP_COUNT 1
#define VARIABLEROOM1_CURRENT_IDX 0
const SRV_PROPERTY_S VariableRoom1_props[VARIABLEROOM1_PROP_COUNT] = {
    { "current", DTYPE_INT, OPR_GET | OPR_REPORT }
};

/* 设备服务总列表 */
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
const SRV_INFO_S services[SRV_TOTAL_COUNT] = {
    {"refrigerateSwitch", "refrigerateSwitch", REFRIGERATESWITCH_PROP_COUNT, refrigerateSwitch_props},
    {"freezeSwitch", "freezeSwitch", FREEZESWITCH_PROP_COUNT, freezeSwitch_props},
    {"intelligentSwitch", "intelligentSwitch", INTELLIGENTSWITCH_PROP_COUNT, intelligentSwitch_props},
    {"refrigerator", "refrigerator", REFRIGERATOR_PROP_COUNT, refrigerator_props},
    {"freezer", "freezer", FREEZER_PROP_COUNT, freezer_props},
    {"coolingSwitch", "coolingSwitch", COOLINGSWITCH_PROP_COUNT, coolingSwitch_props},
<<<<<<< HEAD
    {"variableTemper", "variableTemper", VARIABLETEMPER_PROP_COUNT, variableTemper_props},
    {"VariableRoom1", "VariableRoom1", VARIABLEROOM1_PROP_COUNT, VariableRoom1_props}};

/* ??????Service ID????????????? */
int getServiceIndex(const char *svc_id)
{
    int i = 0;
    for (i = 0; i < SRV_TOTAL_COUNT; i++)
    {
        if ((hilink_strlen(services[i].id) == hilink_strlen(svc_id)) &&
            (hilink_strncmp(svc_id, services[i].id, hilink_strlen(svc_id)) == 0))
        {
=======
    {"variableMode", "variableMode", VARIABLEMODE_PROP_COUNT, variableMode_props},
    {"VariableRoom1", "VariableRoom1", VARIABLEROOM1_PROP_COUNT, VariableRoom1_props}
};

/* 获取指定Service ID对应的数组下标 */
int getServiceIndex(const char *svc_id)
{
    int i = 0;
    for (i = 0; i < SRV_TOTAL_COUNT; i++) {
        if ((hilink_strlen(services[i].id) == hilink_strlen(svc_id)) &&
            (hilink_strncmp(svc_id, services[i].id, hilink_strlen(svc_id)) == 0)) {
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
            return i;
        }
    }
    return -1;
}

<<<<<<< HEAD
/* ??????? BI???? */
=======
/* 获取加密 BI参数 */
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
char *hilink_get_auto_bi_rsa_cipher(void)
{
    return bi_rsacipher;
}

<<<<<<< HEAD
/* ??????? AC???? */
=======
/* 获取加密 AC参数 */
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
unsigned char *hilink_get_auto_ac(void)
{
    return A_C;
}

<<<<<<< HEAD
/* ?搂唯???????????搂伪??????? */
bool hasValidProperty(bool *mask, int count)
{
    int i = 0;
    if (mask == NULL || count <= 0)
    {
        return false;
    }
    for (i = 0; i < count; i++)
    {
        if (mask[i] == true)
        {
=======
/* 判断掩码中是否有可用的入参 */
bool hasValidProperty(bool *mask, int count)
{
    int i = 0;
    if (mask == NULL || count <= 0) {
        return false;
    }
    for (i = 0; i < count; i++) {
        if (mask[i] == true) {
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
            return true;
        }
    }
    return false;
}

<<<<<<< HEAD
/* HiLink??????????(PUT)??? */
int hilink_put_char_state(const char *svcId, const char *payload, unsigned int len)
{
    int err = M2M_NO_ERROR;
    if (svcId == NULL)
    {
=======
/* HiLink云端控制命令(PUT)接口 */
int hilink_put_char_state(const char *svcId, const char *payload, unsigned int len)
{
    int err = M2M_NO_ERROR;
    if (svcId == NULL) {
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
        hilink_error("svcId null err\r\n");
        return M2M_SVC_RPT_CREATE_PAYLOAD_ERR;
    }

<<<<<<< HEAD
    if (payload == NULL)
    {
=======
    if (payload == NULL) {
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
        hilink_error("payload null err\r\n");
        return M2M_SVC_RPT_CREATE_PAYLOAD_ERR;
    }

<<<<<<< HEAD
    /* ????JSON???? */
    void *jsonObj = hilink_json_parse(payload);
    if (jsonObj == NULL)
    {
=======
    /* 解析JSON报文 */
    void *jsonObj = hilink_json_parse(payload);
    if (jsonObj == NULL) {
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
        hilink_error("json parse failed, svcId[%s]\r\n", svcId);
        return INVALID_PACKET;
    }

<<<<<<< HEAD
    /* ???????id????????????? */
    int svcIdx = getServiceIndex(svcId);
    if (svcIdx < 0 || svcIdx >= SRV_TOTAL_COUNT)
    {
=======
    /* 获取服务id对应的数组下标 */
    int svcIdx = getServiceIndex(svcId);
    if (svcIdx < 0 || svcIdx >= SRV_TOTAL_COUNT) {
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
        hilink_json_delete(jsonObj);
        hilink_error("svcId %s unknown\r\n", svcId);
        return M2M_SVC_RPT_CREATE_PAYLOAD_ERR;
    }

    hilink_debug("start process PUT cmd, svcId[%s]\r\n", svcId);
<<<<<<< HEAD
    switch (svcIdx)
    {
    case SRV_IDX_REFRIGERATESWITCH:
    {
        /* ????on???? */
        bool on;
        bool *on_p = NULL;
        if ((hilink_json_get_number_value(jsonObj, services[SRV_IDX_REFRIGERATESWITCH].props[REFRIGERATESWITCH_ON_IDX].name, &on) == 0) &&
            (on == 0 || on == 1))
        {
            on_p = &on;
        }

        err = handle_refrigerateSwitch_cmd(on_p);
        break;
    }
    case SRV_IDX_FREEZESWITCH:
    {
        /* ????on???? */
        bool on;
        bool *on_p = NULL;
        if ((hilink_json_get_number_value(jsonObj, services[SRV_IDX_FREEZESWITCH].props[FREEZESWITCH_ON_IDX].name, &on) == 0) &&
            (on == 0 || on == 1))
        {
            on_p = &on;
        }

        err = handle_freezeSwitch_cmd(on_p);
        break;
    }
    case SRV_IDX_INTELLIGENTSWITCH:
    {
        /* ????on???? */
        bool on;
        bool *on_p = NULL;
        if ((hilink_json_get_number_value(jsonObj, services[SRV_IDX_INTELLIGENTSWITCH].props[INTELLIGENTSWITCH_ON_IDX].name, &on) == 0) &&
            (on == 0 || on == 1))
        {
            on_p = &on;
        }

        err = handle_intelligentSwitch_cmd(on_p);
        break;
    }
    case SRV_IDX_REFRIGERATOR:
    {
        /* ????target???? */
        int target;
        int *target_p = NULL;
        if (hilink_json_get_number_value(jsonObj, services[SRV_IDX_REFRIGERATOR].props[REFRIGERATOR_TARGET_IDX].name, &target) == 0)
        {
            target_p = &target;
        }

        err = handle_refrigerator_cmd(target_p);
        break;
    }
    case SRV_IDX_FREEZER:
    {
        /* ????target???? */
        int target;
        int *target_p = NULL;
        if (hilink_json_get_number_value(jsonObj, services[SRV_IDX_FREEZER].props[FREEZER_TARGET_IDX].name, &target) == 0)
        {
            target_p = &target;
        }

        err = handle_freezer_cmd(target_p);
        break;
    }
    case SRV_IDX_COOLINGSWITCH:
    {
        /* ????coolingSwitch???? */
        bool coolingSwitch;
        bool *coolingSwitch_p = NULL;
        if ((hilink_json_get_number_value(jsonObj, services[SRV_IDX_COOLINGSWITCH].props[COOLINGSWITCH_COOLINGSWITCH_IDX].name, &coolingSwitch) == 0) &&
            (coolingSwitch == 0 || coolingSwitch == 1))
        {
            coolingSwitch_p = &coolingSwitch;
        }

        err = handle_coolingSwitch_cmd(coolingSwitch_p);
        break;
    }
    case SRV_IDX_VARIABLETEMPER:
    {
        /* ????target???? */
        int target;
        int *target_p = NULL;
        if (hilink_json_get_number_value(jsonObj, services[SRV_IDX_VARIABLETEMPER].props[VARIABLETEMPER_TARGET_IDX].name, &target) == 0)
        {
            target_p = &target;
        }

        err = handle_variableTemper_cmd(target_p);
        break;
    }
    default:
    { /* ???????ID */
        hilink_error("svcId %s invalid\r\n", svcId);
        break;
    }
    }

    if (jsonObj != NULL)
    {
=======
    switch (svcIdx) {
        case SRV_IDX_REFRIGERATESWITCH: {
            /* 解析on属性 */
            bool on;
            bool *on_p = NULL;
            if ((hilink_json_get_number_value(jsonObj, services[SRV_IDX_REFRIGERATESWITCH].props[REFRIGERATESWITCH_ON_IDX].name, &on) == 0) &&
                (on == 0 || on == 1)) {
                on_p = &on;
            }
            
            err = handle_refrigerateSwitch_cmd(on_p);
            break;
        }
        case SRV_IDX_FREEZESWITCH: {
            /* 解析on属性 */
            bool on;
            bool *on_p = NULL;
            if ((hilink_json_get_number_value(jsonObj, services[SRV_IDX_FREEZESWITCH].props[FREEZESWITCH_ON_IDX].name, &on) == 0) &&
                (on == 0 || on == 1)) {
                on_p = &on;
            }

            err = handle_freezeSwitch_cmd(on_p);
            break;
        }
        case SRV_IDX_INTELLIGENTSWITCH: {
            /* 解析on属性 */
            bool on;
            bool *on_p = NULL;
            if ((hilink_json_get_number_value(jsonObj, services[SRV_IDX_INTELLIGENTSWITCH].props[INTELLIGENTSWITCH_ON_IDX].name, &on) == 0) &&
                (on == 0 || on == 1)) {
                on_p = &on;
            }

            err = handle_intelligentSwitch_cmd(on_p);
            break;
        }
        case SRV_IDX_REFRIGERATOR: {
            /* 解析target属性 */
            int target;
            int *target_p = NULL;
            if (hilink_json_get_number_value(jsonObj, services[SRV_IDX_REFRIGERATOR].props[REFRIGERATOR_TARGET_IDX].name, &target) == 0) {
                target_p = &target;
            }

            err = handle_refrigerator_cmd(target_p);
            break;
        }
        case SRV_IDX_FREEZER: {
            /* 解析target属性 */
            int target;
            int *target_p = NULL;
            if (hilink_json_get_number_value(jsonObj, services[SRV_IDX_FREEZER].props[FREEZER_TARGET_IDX].name, &target) == 0) {
                target_p = &target;
            }

            err = handle_freezer_cmd(target_p);
            break;
        }
        case SRV_IDX_COOLINGSWITCH: {
            /* 解析coolingSwitch属性 */
            bool coolingSwitch;
            bool *coolingSwitch_p = NULL;
            if ((hilink_json_get_number_value(jsonObj, services[SRV_IDX_COOLINGSWITCH].props[COOLINGSWITCH_COOLINGSWITCH_IDX].name, &coolingSwitch) == 0) &&
                (coolingSwitch == 0 || coolingSwitch == 1)) {
                coolingSwitch_p = &coolingSwitch;
            }

            err = handle_coolingSwitch_cmd(coolingSwitch_p);
            break;
        }
        case SRV_IDX_VARIABLEMODE: {
            /* 解析target属性 */
            int target;
            int *target_p = NULL;
            if (hilink_json_get_number_value(jsonObj, services[SRV_IDX_VARIABLEMODE].props[VARIABLEMODE_TARGET_IDX].name, &target) == 0) {
                target_p = &target;
            }

            err = handle_variableMode_cmd(target_p);
            break;
        }
        default: { /* 非法服务ID */
            hilink_error("svcId %s invalid\r\n", svcId);
            break;
        }
    }

    if (jsonObj != NULL) {
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
        hilink_json_delete(jsonObj);
    }

    hilink_debug("end process PUT cmd, svcId[%s], ret[%d]\r\n", svcId, err);
    return err;
}

<<<<<<< HEAD
/* HiLink?????????(GET)??? */
int hilink_get_char_state(const char *svcId, const char *in, unsigned int inLen, char **out, unsigned int *outLen)
{
    int err = M2M_NO_ERROR;
    if (svcId == NULL)
    {
=======
/* HiLink云端查询命令(GET)接口 */
int hilink_get_char_state(const char *svcId, const char *in, unsigned int inLen, char **out, unsigned int *outLen)
{
    int err = M2M_NO_ERROR;
    if (svcId == NULL) {
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
        hilink_error("svcId null err\r\n");
        return M2M_SVC_RPT_CREATE_PAYLOAD_ERR;
    }

<<<<<<< HEAD
    /* ??????????????搂桅????? */
    int svcIdx = getServiceIndex(svcId);
    if (svcIdx < 0 || svcIdx >= SRV_TOTAL_COUNT)
    {
=======
    /* 获取服务在数组中的下标 */
    int svcIdx = getServiceIndex(svcId);
    if (svcIdx < 0 || svcIdx >= SRV_TOTAL_COUNT) {
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
        hilink_error("svcId %s unknown\r\n", svcId);
        return M2M_SVC_RPT_CREATE_PAYLOAD_ERR;
    }

    hilink_debug("start process GET cmd, svcId[%s]\r\n", svcId);
<<<<<<< HEAD
    switch (svcIdx)
    {
    case SRV_IDX_REFRIGERATESWITCH:
    {
        bool on = 0;
        err = get_refrigerateSwitch_state(&on);
        if (err == M2M_NO_ERROR)
        {
            /* ????????????????, ??????????????? */
            *outLen = 20;
            *out = (char *)hilink_malloc(*outLen);
            if (*out == NULL)
            {
                hilink_error("out buf malloc failed, svcId[%s]\r\n", svcId);
                break;
            }
            *outLen = hilink_sprintf_s(*out, *outLen, "{\"on\":%d}", on);
        }
        break;
    }
    case SRV_IDX_FREEZESWITCH:
    {
        bool on = 0;
        err = get_freezeSwitch_state(&on);
        if (err == M2M_NO_ERROR)
        {
            /* ????????????????, ??????????????? */
            *outLen = 20;
            *out = (char *)hilink_malloc(*outLen);
            if (*out == NULL)
            {
                hilink_error("out buf malloc failed, svcId[%s]\r\n", svcId);
                break;
            }
            *outLen = hilink_sprintf_s(*out, *outLen, "{\"on\":%d}", on);
        }
        break;
    }
    case SRV_IDX_INTELLIGENTSWITCH:
    {
        bool on = 0;
        err = get_intelligentSwitch_state(&on);
        if (err == M2M_NO_ERROR)
        {
            /* ????????????????, ??????????????? */
            *outLen = 20;
            *out = (char *)hilink_malloc(*outLen);
            if (*out == NULL)
            {
                hilink_error("out buf malloc failed, svcId[%s]\r\n", svcId);
                break;
            }
            *outLen = hilink_sprintf_s(*out, *outLen, "{\"on\":%d}", on);
        }
        break;
    }
    case SRV_IDX_REFRIGERATOR:
    {
        int target = 0;
        int current = 0;
        err = get_refrigerator_state(&target, &current);
        if (err == M2M_NO_ERROR)
        {
            /* ????????????????, ??????????????? */
            *outLen = 51;
            *out = (char *)hilink_malloc(*outLen);
            if (*out == NULL)
            {
                hilink_error("out buf malloc failed, svcId[%s]\r\n", svcId);
                break;
            }
            *outLen = hilink_sprintf_s(*out, *outLen, "{\"target\":%d, \"current\":%d}", target, current);
        }
        break;
    }
    case SRV_IDX_FREEZER:
    {
        int target = 0;
        int current = 0;
        err = get_freezer_state(&target, &current);
        if (err == M2M_NO_ERROR)
        {
            /* ????????????????, ??????????????? */
            *outLen = 51;
            *out = (char *)hilink_malloc(*outLen);
            if (*out == NULL)
            {
                hilink_error("out buf malloc failed, svcId[%s]\r\n", svcId);
                break;
            }
            *outLen = hilink_sprintf_s(*out, *outLen, "{\"target\":%d, \"current\":%d}", target, current);
        }
        break;
    }
    case SRV_IDX_COOLINGSWITCH:
    {
        bool coolingSwitch = 0;
        err = get_coolingSwitch_state(&coolingSwitch);
        if (err == M2M_NO_ERROR)
        {
            /* ????????????????, ??????????????? */
            *outLen = 31;
            *out = (char *)hilink_malloc(*outLen);
            if (*out == NULL)
            {
                hilink_error("out buf malloc failed, svcId[%s]\r\n", svcId);
                break;
            }
            *outLen = hilink_sprintf_s(*out, *outLen, "{\"coolingSwitch\":%d}", coolingSwitch);
        }
        break;
    }
    case SRV_IDX_VARIABLETEMPER:
    {
        int target = 0;
        err = get_variableTemper_state(&target);
        if (err == M2M_NO_ERROR)
        {
            /* ????????????????, ??????????????? */
            *outLen = 24;
            *out = (char *)hilink_malloc(*outLen);
            if (*out == NULL)
            {
                hilink_error("out buf malloc failed, svcId[%s]\r\n", svcId);
                break;
            }
            *outLen = hilink_sprintf_s(*out, *outLen, "{\"target\":%d}", target);
        }
        break;
    }
    case SRV_IDX_VARIABLEROOM1:
    {
        int current = 0;
        err = get_VariableRoom1_state(&current);
        if (err == M2M_NO_ERROR)
        {
            /* ????????????????, ??????????????? */
            *outLen = 25;
            *out = (char *)hilink_malloc(*outLen);
            if (*out == NULL)
            {
                hilink_error("out buf malloc failed, svcId[%s]\r\n", svcId);
                break;
            }
            *outLen = hilink_sprintf_s(*out, *outLen, "{\"current\":%d}", current);
        }
        break;
    }
    default:
    {
        *outLen = 3;
        *out = (char *)hilink_malloc(*outLen);
        if (*out == NULL)
        {
            hilink_error("out buf malloc failed, svcId[%s]\r\n", svcId);
            break;
        }
        *outLen = hilink_sprintf_s(*out, *outLen, "{}");
        break;
    }
=======
    switch (svcIdx) {
        case SRV_IDX_REFRIGERATESWITCH: {
            bool on = 0;
            err = get_refrigerateSwitch_state(&on);
            if (err == M2M_NO_ERROR) {
                /* 长度由工具自动计算, 内存申请会在外部释放 */
                *outLen = 20;
                *out = (char *)hilink_malloc(*outLen);
                if (*out == NULL) {
                    hilink_error("out buf malloc failed, svcId[%s]\r\n", svcId);
                    break;
                }
                *outLen = hilink_sprintf_s(*out, *outLen, "{\"on\":%d}", on);
            }
            break;
        }
        case SRV_IDX_FREEZESWITCH: {
            bool on = 0;
            err = get_freezeSwitch_state(&on);
            if (err == M2M_NO_ERROR) {
                /* 长度由工具自动计算, 内存申请会在外部释放 */
                *outLen = 20;
                *out = (char *)hilink_malloc(*outLen);
                if (*out == NULL) {
                    hilink_error("out buf malloc failed, svcId[%s]\r\n", svcId);
                    break;
                }
                *outLen = hilink_sprintf_s(*out, *outLen, "{\"on\":%d}", on);
            }
            break;
        }
        case SRV_IDX_INTELLIGENTSWITCH: {
            bool on = 0;
            err = get_intelligentSwitch_state(&on);
            if (err == M2M_NO_ERROR) {
                /* 长度由工具自动计算, 内存申请会在外部释放 */
                *outLen = 20;
                *out = (char *)hilink_malloc(*outLen);
                if (*out == NULL) {
                    hilink_error("out buf malloc failed, svcId[%s]\r\n", svcId);
                    break;
                }
                *outLen = hilink_sprintf_s(*out, *outLen, "{\"on\":%d}", on);
            }
            break;
        }
        case SRV_IDX_REFRIGERATOR: {
            int target = 0;
            int current = 0;
            err = get_refrigerator_state(&target, &current);
            if (err == M2M_NO_ERROR) {
                /* 长度由工具自动计算, 内存申请会在外部释放 */
                *outLen = 51;
                *out = (char *)hilink_malloc(*outLen);
                if (*out == NULL) {
                    hilink_error("out buf malloc failed, svcId[%s]\r\n", svcId);
                    break;
                }
                *outLen = hilink_sprintf_s(*out, *outLen, "{\"target\":%d, \"current\":%d}", target, current);
            }
            break;
        }
        case SRV_IDX_FREEZER: {
            int target = 0;
            int current = 0;
            err = get_freezer_state(&target, &current);
            if (err == M2M_NO_ERROR) {
                /* 长度由工具自动计算, 内存申请会在外部释放 */
                *outLen = 51;
                *out = (char *)hilink_malloc(*outLen);
                if (*out == NULL) {
                    hilink_error("out buf malloc failed, svcId[%s]\r\n", svcId);
                    break;
                }
                *outLen = hilink_sprintf_s(*out, *outLen, "{\"target\":%d, \"current\":%d}", target, current);
            }
            break;
        }
        case SRV_IDX_COOLINGSWITCH: {
            bool coolingSwitch = 0;
            err = get_coolingSwitch_state(&coolingSwitch);
            if (err == M2M_NO_ERROR) {
                /* 长度由工具自动计算, 内存申请会在外部释放 */
                *outLen = 31;
                *out = (char *)hilink_malloc(*outLen);
                if (*out == NULL) {
                    hilink_error("out buf malloc failed, svcId[%s]\r\n", svcId);
                    break;
                }
                *outLen = hilink_sprintf_s(*out, *outLen, "{\"coolingSwitch\":%d}", coolingSwitch);
            }
            break;
        }
        case SRV_IDX_VARIABLEMODE: {
            int target = 0;
            err = get_variableMode_state(&target);
            if (err == M2M_NO_ERROR) {
                /* 长度由工具自动计算, 内存申请会在外部释放 */
                *outLen = 24;
                *out = (char *)hilink_malloc(*outLen);
                if (*out == NULL) {
                    hilink_error("out buf malloc failed, svcId[%s]\r\n", svcId);
                    break;
                }
                *outLen = hilink_sprintf_s(*out, *outLen, "{\"target\":%d}", target);
            }
            break;
        }
        case SRV_IDX_VARIABLEROOM1: {
            int current = 0;
            err = get_VariableRoom1_state(&current);
            if (err == M2M_NO_ERROR) {
                /* 长度由工具自动计算, 内存申请会在外部释放 */
                *outLen = 25;
                *out = (char *)hilink_malloc(*outLen);
                if (*out == NULL) {
                    hilink_error("out buf malloc failed, svcId[%s]\r\n", svcId);
                    break;
                }
                *outLen = hilink_sprintf_s(*out, *outLen, "{\"current\":%d}", current);
            }
            break;
        }
        default: {
            *outLen = 3;
            *out = (char *)hilink_malloc(*outLen);
            if (*out == NULL) {
                hilink_error("out buf malloc failed, svcId[%s]\r\n", svcId);
                break;
            }
            *outLen = hilink_sprintf_s(*out, *outLen, "{}");
            break;
        }
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
    }
    hilink_debug("end process GET cmd, svcId[%s], ret[%d]\r\n", svcId, err);
    return err;
}

<<<<<<< HEAD
/* HiLink?蠀蟿?????(REPORT)?????????????????? */
/* ???refrigerateSwitch?????? */
=======
/* HiLink设备状态上报(REPORT)接口实现，供开发者调用 */
/* 上报refrigerateSwitch服务状态 */
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
int report_refrigerateSwitch_state(bool on)
{
    hilink_debug("start report refrigerateSwitch service state\r\n");
    int err = M2M_NO_ERROR;
    int outLen = 0;
    char out[20];
    (void)hilink_memset_s(out, sizeof(char) * 20, 0, sizeof(char) * 20);

<<<<<<< HEAD
    /* ?????JSON???? */
    outLen = hilink_sprintf_s(out, 20, "{\"on\":%d}", on);
    /* ?????????????? */
    err = hilink_report_char_state(services[SRV_IDX_REFRIGERATESWITCH].id, out, outLen);
=======
    /* 格式化JSON报文 */
    outLen = hilink_sprintf_s(out, 20, "{\"on\":%d}", on);
    /* 调用异步状态上报接口 */
    err = hilink_upload_char_state(services[SRV_IDX_REFRIGERATESWITCH].id, out, outLen);
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
    hilink_debug("end report refrigerateSwitch service state, ret[%d]\r\n", err);
    return err;
}

<<<<<<< HEAD
/* ???freezeSwitch?????? */
=======
/* 上报freezeSwitch服务状态 */
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
int report_freezeSwitch_state(bool on)
{
    hilink_debug("start report freezeSwitch service state\r\n");
    int err = M2M_NO_ERROR;
    int outLen = 0;
    char out[20];
    (void)hilink_memset_s(out, sizeof(char) * 20, 0, sizeof(char) * 20);

<<<<<<< HEAD
    /* ?????JSON???? */
    outLen = hilink_sprintf_s(out, 20, "{\"on\":%d}", on);
    /* ?????????????? */
    err = hilink_report_char_state(services[SRV_IDX_FREEZESWITCH].id, out, outLen);
=======
    /* 格式化JSON报文 */
    outLen = hilink_sprintf_s(out, 20, "{\"on\":%d}", on);
    /* 调用异步状态上报接口 */
    err = hilink_upload_char_state(services[SRV_IDX_FREEZESWITCH].id, out, outLen);
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
    hilink_debug("end report freezeSwitch service state, ret[%d]\r\n", err);
    return err;
}

<<<<<<< HEAD
/* ???intelligentSwitch?????? */
=======
/* 上报intelligentSwitch服务状态 */
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
int report_intelligentSwitch_state(bool on)
{
    hilink_debug("start report intelligentSwitch service state\r\n");
    int err = M2M_NO_ERROR;
    int outLen = 0;
    char out[20];
    (void)hilink_memset_s(out, sizeof(char) * 20, 0, sizeof(char) * 20);

<<<<<<< HEAD
    /* ?????JSON???? */
    outLen = hilink_sprintf_s(out, 20, "{\"on\":%d}", on);
    /* ?????????????? */
    err = hilink_report_char_state(services[SRV_IDX_INTELLIGENTSWITCH].id, out, outLen);
=======
    /* 格式化JSON报文 */
    outLen = hilink_sprintf_s(out, 20, "{\"on\":%d}", on);
    /* 调用异步状态上报接口 */
    err = hilink_upload_char_state(services[SRV_IDX_INTELLIGENTSWITCH].id, out, outLen);
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
    hilink_debug("end report intelligentSwitch service state, ret[%d]\r\n", err);
    return err;
}

<<<<<<< HEAD
/* ???refrigerator?????? */
=======
/* 上报refrigerator服务状态 */
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
int report_refrigerator_state(int target, int current)
{
    hilink_debug("start report refrigerator service state\r\n");
    int err = M2M_NO_ERROR;
    int outLen = 0;
    char out[51];
    (void)hilink_memset_s(out, sizeof(char) * 51, 0, sizeof(char) * 51);

<<<<<<< HEAD
    /* ?????JSON???? */
    outLen = hilink_sprintf_s(out, 51, "{\"target\":%d, \"current\":%d}", target, current);
    /* ?????????????? */
    err = hilink_report_char_state(services[SRV_IDX_REFRIGERATOR].id, out, outLen);
=======
    /* 格式化JSON报文 */
    outLen = hilink_sprintf_s(out, 51, "{\"target\":%d, \"current\":%d}", target, current);
    /* 调用异步状态上报接口 */
    err = hilink_upload_char_state(services[SRV_IDX_REFRIGERATOR].id, out, outLen);
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
    hilink_debug("end report refrigerator service state, ret[%d]\r\n", err);
    return err;
}

<<<<<<< HEAD
/* ???freezer?????? */
=======
/* 上报freezer服务状态 */
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
int report_freezer_state(int target, int current)
{
    hilink_debug("start report freezer service state\r\n");
    int err = M2M_NO_ERROR;
    int outLen = 0;
    char out[51];
    (void)hilink_memset_s(out, sizeof(char) * 51, 0, sizeof(char) * 51);

<<<<<<< HEAD
    /* ?????JSON???? */
    outLen = hilink_sprintf_s(out, 51, "{\"target\":%d, \"current\":%d}", target, current);
    /* ?????????????? */
    err = hilink_report_char_state(services[SRV_IDX_FREEZER].id, out, outLen);
=======
    /* 格式化JSON报文 */
    outLen = hilink_sprintf_s(out, 51, "{\"target\":%d, \"current\":%d}", target, current);
    /* 调用异步状态上报接口 */
    err = hilink_upload_char_state(services[SRV_IDX_FREEZER].id, out, outLen);
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
    hilink_debug("end report freezer service state, ret[%d]\r\n", err);
    return err;
}

<<<<<<< HEAD
/* ???coolingSwitch?????? */
=======
/* 上报coolingSwitch服务状态 */
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
int report_coolingSwitch_state(bool coolingSwitch)
{
    hilink_debug("start report coolingSwitch service state\r\n");
    int err = M2M_NO_ERROR;
    int outLen = 0;
    char out[31];
    (void)hilink_memset_s(out, sizeof(char) * 31, 0, sizeof(char) * 31);

<<<<<<< HEAD
    /* ?????JSON???? */
    outLen = hilink_sprintf_s(out, 31, "{\"coolingSwitch\":%d}", coolingSwitch);
    /* ?????????????? */
    err = hilink_report_char_state(services[SRV_IDX_COOLINGSWITCH].id, out, outLen);
=======
    /* 格式化JSON报文 */
    outLen = hilink_sprintf_s(out, 31, "{\"coolingSwitch\":%d}", coolingSwitch);
    /* 调用异步状态上报接口 */
    err = hilink_upload_char_state(services[SRV_IDX_COOLINGSWITCH].id, out, outLen);
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
    hilink_debug("end report coolingSwitch service state, ret[%d]\r\n", err);
    return err;
}

<<<<<<< HEAD
/* ???variableTemper?????? */
int report_variableTemper_state(int target)
{
    hilink_debug("start report variableTemper service state\r\n");
=======
/* 上报variableMode服务状态 */
int report_variableMode_state(int target)
{
    hilink_debug("start report variableMode service state\r\n");
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
    int err = M2M_NO_ERROR;
    int outLen = 0;
    char out[24];
    (void)hilink_memset_s(out, sizeof(char) * 24, 0, sizeof(char) * 24);

<<<<<<< HEAD
    /* ?????JSON???? */
    outLen = hilink_sprintf_s(out, 24, "{\"target\":%d}", target);
    /* ?????????????? */
    err = hilink_report_char_state(services[SRV_IDX_VARIABLETEMPER].id, out, outLen);
    hilink_debug("end report variableTemper service state, ret[%d]\r\n", err);
    return err;
}

/* ???VariableRoom1?????? */
=======
    /* 格式化JSON报文 */
    outLen = hilink_sprintf_s(out, 24, "{\"target\":%d}", target);
    /* 调用异步状态上报接口 */
    err = hilink_upload_char_state(services[SRV_IDX_VARIABLEMODE].id, out, outLen);
    hilink_debug("end report variableMode service state, ret[%d]\r\n", err);
    return err;
}

/* 上报VariableRoom1服务状态 */
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
int report_VariableRoom1_state(int current)
{
    hilink_debug("start report VariableRoom1 service state\r\n");
    int err = M2M_NO_ERROR;
    int outLen = 0;
    char out[25];
    (void)hilink_memset_s(out, sizeof(char) * 25, 0, sizeof(char) * 25);

<<<<<<< HEAD
    /* ?????JSON???? */
    outLen = hilink_sprintf_s(out, 25, "{\"current\":%d}", current);
    /* ?????????????? */
    err = hilink_report_char_state(services[SRV_IDX_VARIABLEROOM1].id, out, outLen);
    hilink_debug("end report VariableRoom1 service state, ret[%d]\r\n", err);
    return err;
}
=======
    /* 格式化JSON报文 */
    outLen = hilink_sprintf_s(out, 25, "{\"current\":%d}", current);
    /* 调用异步状态上报接口 */
    err = hilink_upload_char_state(services[SRV_IDX_VARIABLEROOM1].id, out, outLen);
    hilink_debug("end report VariableRoom1 service state, ret[%d]\r\n", err);
    return err;
}

>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
