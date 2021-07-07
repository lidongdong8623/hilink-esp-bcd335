/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2018-2020. All rights reserved.
 * Description: HiLink SDK???????????
 * Notes: ???????????????????????????, ??????????????
 */
#include "hilink_device.h"
#include <stdlib.h>
#include "hilink_log.h"
#include "hilink_osadapter.h"

#define M2M_NO_ERROR 0
#define M2M_SVC_RPT_CREATE_PAYLOAD_ERR -201

typedef struct
{
    const char *sn;     /* ?υτ|·????SN??, ?????|?(0,40] */
    const char *prodId; /* ?υτHiLink?????, ?????|?(0,5] */
    const char *model;  /* ?υτ???, ?????|?(0,32] */
    const char *dev_t;  /* ?υτ????, ?????|?(0,4] */
    const char *manu;   /* ?υτ??????, ?????|?(0,4] */
    const char *mac;    /* ?υτMAC???, ???32??? */
    const char *hiv;    /* ?υτHiLink§???·?, ?????|?(0,32] */
    const char *fwv;    /* ?υτ????·?, ?????|?[0,64] */
    const char *hwv;    /* ?υτ????·?, ?????|?[0,64] */
    const char *swv;    /* ?υτ?????·?, ?????|?[0,64] */
    const int prot_t;   /* ?υτ§???????, ????|?[1,3] */
} dev_info_t;

/* ???: ?υτ????????????????????????????????17??? */
typedef struct
{
    const char *devTypeName; /* ?υτ??????????? */
    const char *manuName;    /* ??????????? */
} DevNameEn;

typedef struct
{
    const char *st;     /* ????????, ?????|?(0,32] */
    const char *svc_id; /* ????ID, ?????|?(0,64] */
} svc_info_t;

/* ?υτ??????? */
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
    PROTOCOL_TYPE};

/* ?υτ???????, ?????????????????????????????17??? */
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

/* ?υτ??????????????????? */
#define DTYPE_BOOL 0
#define DTYPE_INT 1
#define DTYPE_STRING 2
#define DTYPE_ENUM 3
#define DTYPE_ARRAY 4

/* ?υτ????????????????? */
#define OPR_REPORT 0x01
#define OPR_GET 0x02
#define OPR_PUT 0x04

/* ??§???json??????? */
#ifndef INVALID_PACKET
#define INVALID_PACKET -87
#endif

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
    const SRV_PROPERTY_S *props; /* ?????§?? */
} SRV_INFO_S;

/* ?υτ????Service???????? */
#define SRV_IDX_REFRIGERATESWITCH 0
#define SRV_IDX_FREEZESWITCH 1
#define SRV_IDX_INTELLIGENTSWITCH 2
#define SRV_IDX_REFRIGERATOR 3
#define SRV_IDX_FREEZER 4
#define SRV_IDX_COOLINGSWITCH 5
#define SRV_IDX_VARIABLETEMPER 6
#define SRV_IDX_VARIABLEROOM1 7
/* ?υτ??????????? */
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
#define REFRIGERATOR_PROP_COUNT 2
#define REFRIGERATOR_TARGET_IDX 0
#define REFRIGERATOR_CURRENT_IDX 1
const SRV_PROPERTY_S refrigerator_props[REFRIGERATOR_PROP_COUNT] = {
    {"target", DTYPE_INT, OPR_GET | OPR_PUT | OPR_REPORT},
    {"current", DTYPE_INT, OPR_GET | OPR_REPORT}};

/* ????freezer???? */
#define FREEZER_PROP_COUNT 2
#define FREEZER_TARGET_IDX 0
#define FREEZER_CURRENT_IDX 1
const SRV_PROPERTY_S freezer_props[FREEZER_PROP_COUNT] = {
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

/* ?υτ???????§?? */
const SRV_INFO_S services[SRV_TOTAL_COUNT] = {
    {"refrigerateSwitch", "refrigerateSwitch", REFRIGERATESWITCH_PROP_COUNT, refrigerateSwitch_props},
    {"freezeSwitch", "freezeSwitch", FREEZESWITCH_PROP_COUNT, freezeSwitch_props},
    {"intelligentSwitch", "intelligentSwitch", INTELLIGENTSWITCH_PROP_COUNT, intelligentSwitch_props},
    {"refrigerator", "refrigerator", REFRIGERATOR_PROP_COUNT, refrigerator_props},
    {"freezer", "freezer", FREEZER_PROP_COUNT, freezer_props},
    {"coolingSwitch", "coolingSwitch", COOLINGSWITCH_PROP_COUNT, coolingSwitch_props},
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
            return i;
        }
    }
    return -1;
}

/* ??????? BI???? */
char *hilink_get_auto_bi_rsa_cipher(void)
{
    return bi_rsacipher;
}

/* ??????? AC???? */
unsigned char *hilink_get_auto_ac(void)
{
    return A_C;
}

/* ?§Ψ???????????§α??????? */
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
            return true;
        }
    }
    return false;
}

/* HiLink??????????(PUT)??? */
int hilink_put_char_state(const char *svcId, const char *payload, unsigned int len)
{
    int err = M2M_NO_ERROR;
    if (svcId == NULL)
    {
        hilink_error("svcId null err\r\n");
        return M2M_SVC_RPT_CREATE_PAYLOAD_ERR;
    }

    if (payload == NULL)
    {
        hilink_error("payload null err\r\n");
        return M2M_SVC_RPT_CREATE_PAYLOAD_ERR;
    }

    /* ????JSON???? */
    void *jsonObj = hilink_json_parse(payload);
    if (jsonObj == NULL)
    {
        hilink_error("json parse failed, svcId[%s]\r\n", svcId);
        return INVALID_PACKET;
    }

    /* ???????id????????????? */
    int svcIdx = getServiceIndex(svcId);
    if (svcIdx < 0 || svcIdx >= SRV_TOTAL_COUNT)
    {
        hilink_json_delete(jsonObj);
        hilink_error("svcId %s unknown\r\n", svcId);
        return M2M_SVC_RPT_CREATE_PAYLOAD_ERR;
    }

    hilink_debug("start process PUT cmd, svcId[%s]\r\n", svcId);
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
        hilink_json_delete(jsonObj);
    }

    hilink_debug("end process PUT cmd, svcId[%s], ret[%d]\r\n", svcId, err);
    return err;
}

/* HiLink?????????(GET)??? */
int hilink_get_char_state(const char *svcId, const char *in, unsigned int inLen, char **out, unsigned int *outLen)
{
    int err = M2M_NO_ERROR;
    if (svcId == NULL)
    {
        hilink_error("svcId null err\r\n");
        return M2M_SVC_RPT_CREATE_PAYLOAD_ERR;
    }

    /* ??????????????§Φ????? */
    int svcIdx = getServiceIndex(svcId);
    if (svcIdx < 0 || svcIdx >= SRV_TOTAL_COUNT)
    {
        hilink_error("svcId %s unknown\r\n", svcId);
        return M2M_SVC_RPT_CREATE_PAYLOAD_ERR;
    }

    hilink_debug("start process GET cmd, svcId[%s]\r\n", svcId);
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
    }
    hilink_debug("end process GET cmd, svcId[%s], ret[%d]\r\n", svcId, err);
    return err;
}

/* HiLink?υτ?????(REPORT)?????????????????? */
/* ???refrigerateSwitch?????? */
int report_refrigerateSwitch_state(bool on)
{
    hilink_debug("start report refrigerateSwitch service state\r\n");
    int err = M2M_NO_ERROR;
    int outLen = 0;
    char out[20];
    (void)hilink_memset_s(out, sizeof(char) * 20, 0, sizeof(char) * 20);

    /* ?????JSON???? */
    outLen = hilink_sprintf_s(out, 20, "{\"on\":%d}", on);
    /* ?????????????? */
    err = hilink_report_char_state(services[SRV_IDX_REFRIGERATESWITCH].id, out, outLen);
    hilink_debug("end report refrigerateSwitch service state, ret[%d]\r\n", err);
    return err;
}

/* ???freezeSwitch?????? */
int report_freezeSwitch_state(bool on)
{
    hilink_debug("start report freezeSwitch service state\r\n");
    int err = M2M_NO_ERROR;
    int outLen = 0;
    char out[20];
    (void)hilink_memset_s(out, sizeof(char) * 20, 0, sizeof(char) * 20);

    /* ?????JSON???? */
    outLen = hilink_sprintf_s(out, 20, "{\"on\":%d}", on);
    /* ?????????????? */
    err = hilink_report_char_state(services[SRV_IDX_FREEZESWITCH].id, out, outLen);
    hilink_debug("end report freezeSwitch service state, ret[%d]\r\n", err);
    return err;
}

/* ???intelligentSwitch?????? */
int report_intelligentSwitch_state(bool on)
{
    hilink_debug("start report intelligentSwitch service state\r\n");
    int err = M2M_NO_ERROR;
    int outLen = 0;
    char out[20];
    (void)hilink_memset_s(out, sizeof(char) * 20, 0, sizeof(char) * 20);

    /* ?????JSON???? */
    outLen = hilink_sprintf_s(out, 20, "{\"on\":%d}", on);
    /* ?????????????? */
    err = hilink_report_char_state(services[SRV_IDX_INTELLIGENTSWITCH].id, out, outLen);
    hilink_debug("end report intelligentSwitch service state, ret[%d]\r\n", err);
    return err;
}

/* ???refrigerator?????? */
int report_refrigerator_state(int target, int current)
{
    hilink_debug("start report refrigerator service state\r\n");
    int err = M2M_NO_ERROR;
    int outLen = 0;
    char out[51];
    (void)hilink_memset_s(out, sizeof(char) * 51, 0, sizeof(char) * 51);

    /* ?????JSON???? */
    outLen = hilink_sprintf_s(out, 51, "{\"target\":%d, \"current\":%d}", target, current);
    /* ?????????????? */
    err = hilink_report_char_state(services[SRV_IDX_REFRIGERATOR].id, out, outLen);
    hilink_debug("end report refrigerator service state, ret[%d]\r\n", err);
    return err;
}

/* ???freezer?????? */
int report_freezer_state(int target, int current)
{
    hilink_debug("start report freezer service state\r\n");
    int err = M2M_NO_ERROR;
    int outLen = 0;
    char out[51];
    (void)hilink_memset_s(out, sizeof(char) * 51, 0, sizeof(char) * 51);

    /* ?????JSON???? */
    outLen = hilink_sprintf_s(out, 51, "{\"target\":%d, \"current\":%d}", target, current);
    /* ?????????????? */
    err = hilink_report_char_state(services[SRV_IDX_FREEZER].id, out, outLen);
    hilink_debug("end report freezer service state, ret[%d]\r\n", err);
    return err;
}

/* ???coolingSwitch?????? */
int report_coolingSwitch_state(bool coolingSwitch)
{
    hilink_debug("start report coolingSwitch service state\r\n");
    int err = M2M_NO_ERROR;
    int outLen = 0;
    char out[31];
    (void)hilink_memset_s(out, sizeof(char) * 31, 0, sizeof(char) * 31);

    /* ?????JSON???? */
    outLen = hilink_sprintf_s(out, 31, "{\"coolingSwitch\":%d}", coolingSwitch);
    /* ?????????????? */
    err = hilink_report_char_state(services[SRV_IDX_COOLINGSWITCH].id, out, outLen);
    hilink_debug("end report coolingSwitch service state, ret[%d]\r\n", err);
    return err;
}

/* ???variableTemper?????? */
int report_variableTemper_state(int target)
{
    hilink_debug("start report variableTemper service state\r\n");
    int err = M2M_NO_ERROR;
    int outLen = 0;
    char out[24];
    (void)hilink_memset_s(out, sizeof(char) * 24, 0, sizeof(char) * 24);

    /* ?????JSON???? */
    outLen = hilink_sprintf_s(out, 24, "{\"target\":%d}", target);
    /* ?????????????? */
    err = hilink_report_char_state(services[SRV_IDX_VARIABLETEMPER].id, out, outLen);
    hilink_debug("end report variableTemper service state, ret[%d]\r\n", err);
    return err;
}

/* ???VariableRoom1?????? */
int report_VariableRoom1_state(int current)
{
    hilink_debug("start report VariableRoom1 service state\r\n");
    int err = M2M_NO_ERROR;
    int outLen = 0;
    char out[25];
    (void)hilink_memset_s(out, sizeof(char) * 25, 0, sizeof(char) * 25);

    /* ?????JSON???? */
    outLen = hilink_sprintf_s(out, 25, "{\"current\":%d}", current);
    /* ?????????????? */
    err = hilink_report_char_state(services[SRV_IDX_VARIABLEROOM1].id, out, outLen);
    hilink_debug("end report VariableRoom1 service state, ret[%d]\r\n", err);
    return err;
}
