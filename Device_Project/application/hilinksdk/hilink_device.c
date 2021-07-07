/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2018-2020. All rights reserved.
 * Description: 设备功能接口定义
 * Notes: 本文件根据开发者功能定义自动生成, 需要开发者适配实现。
 */
#include <stdlib.h>
#include <string.h>
#include "esp_common.h"
#include "hilink_device.h"
#include "uart.h"
#include "user_config.h"
<<<<<<< HEAD
#include "hw_timer.h"
extern uint8 g_send_data[13];             //WIFI——>MCU串口发送数组 Add by wangshuqiang @2021-2-18
extern uint8 g_receive_data[23];          //MCU——>WIFI串口接收数组
extern uint8 g_receive_data_old[23];      //串口接收对比数组
extern DevInfo g_dev_info;       
char inConfig = 0x00;	                  //falsh第一字节，用来保存掉电之前的配网状态
char user_flash_message = 0x00;           //用来判断掉电前是否已经配网完成
bool intelligentFlag = false;             //智能模式标志位
void wait_connecting(void)                //待配网回调函数             
{   
    uint8 wait_connected[5] = {0x8D,0x01,0x55,0xAA,0x8D};
	uart0_send_data(wait_connected,sizeof(wait_connected));
}

void success_login(void)                  //配网完成回调函数
{
	uint8 Wifi_connected_success[5] = {0x8D,0x02,0x55,0xAA,0x8E};
	uart0_send_data(Wifi_connected_success,sizeof(Wifi_connected_success));
}
void reconnected(void)                    //重连回调函数
{
	uint8 Wifi_reconnected[5] = {0x8D,0x03,0x55,0xAA,0x8F};	
	uart0_send_data(Wifi_reconnected,sizeof(Wifi_reconnected)); //发送重连数组
}
void net_close(void)                      //关闭网络回调函数
{
	uint8 Wifi_close[5] = {0x8D,0x05,0x55,0xAA,0x91};
	uart0_send_data(Wifi_close,sizeof(Wifi_close));//10分钟超时发送，关闭wifi灯
}
=======


extern uint8 g_send_data[13];             //WIFI——>MCU串口发送数组 Add by wangshuqiang @2021-2-18
extern uint8 g_receive_data[22];          //MCU——>WIFI串口接收数组
extern uint8 g_receive_data_old[22];      //串口接收对比数组
extern DevInfo g_dev_info;

>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
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

<<<<<<< HEAD
void caculate_check_num(unsigned char *arrayA,int len)
{
	int i;
	short int temp = 0; 
	for(i = 0;i < len - 1 ; i++)
	{
		//uart0_send_data(arrayA,1);
		temp = *arrayA + temp;
		arrayA = arrayA + 1;
	}
    *arrayA = (uint8)(temp & 0x00FF);
	//uart0_send_data(arrayA,1);
}

=======
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
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
<<<<<<< HEAD
			hw_timer_set_func(success_login);
			hw_timer_arm(500000,1);
			inConfig = 0x01;                  
			HilinkSetUserConfig(&inConfig,1);//将0x01写进flash，代表已经配网完成 add by wangshuqiang 2021-3-29
=======
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
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
<<<<<<< HEAD
			hw_timer_set_func(wait_connecting);
			hw_timer_arm(500000,1);
            break;
        case HILINK_LINK_CONFIG_TIMEOUT:
            /* 设备处于10分钟超时状态, 请在此处添加实现 */
			hw_timer_set_func(net_close);
			hw_timer_arm(500000,1);
            break;
        case HILINK_LINK_CONNECTTING_WIFI:
            /* 设备正在连接路由器, 请在此处添加实现 */
			HilinkGetUserConfig(1,&user_flash_message);  //从flash中读取是否之前完成配网
				if(user_flash_message==0x01)
				{
					hw_timer_set_func(reconnected);
			        hw_timer_arm(500000,1);
				}
				else 
				printf("A8\r\n");
=======
            break;
        case HILINK_LINK_CONFIG_TIMEOUT:
            /* 设备处于10分钟超时状态, 请在此处添加实现 */
            break;
        case HILINK_LINK_CONNECTTING_WIFI:
            /* 设备正在连接路由器, 请在此处添加实现 */
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
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
<<<<<<< HEAD
        return 0;
=======
        return -1;
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
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
<<<<<<< HEAD
    return -1;
=======

   // return 88888888;//Add by lidongdong  @2021-01-21
    return -1;//Add by lidongdong  @2021-01-21
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
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
<<<<<<< HEAD
	//char str[] = "Hi-Huawei-Smart Home-1211SB";  // Add by wangshuqiang @2021-2-18
    //memcpy(sn, str, strlen(str));
=======
    char str[] = "Hi-Huawei-Smart Home-1211SY";  // Add by wangshuqiang @2021-2-18
    memcpy(sn, str, strlen(str));

>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
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
    if (on != NULL) {                               //确保on指针指向具体地址，防止*on出现不可预知风险 Add by wangshuqiang @2021-2-18
        /* 请在此处实现设备状态改变的操作 */        //Add by lidongdong  @2021-02-5 begin.
<<<<<<< HEAD
			g_dev_info.g_refrigerateSwitch = *on;
			if(*on)
			{
				 g_send_data[1] = 0x03;                 //下发命令为 1 -> 速冷模式 Add by wangshuqiang @2021-2-18
			}
			else
			{
				g_send_data[1] = 0x00;                 //下发命令为 0 -> 默认手动模式 Add by wangshuqiang @2021-2-18
			}
		}
	caculate_check_num(g_send_data,sizeof(g_send_data));//calculate check_num and send out add by wangshuqiang 2021-3-22
	uart0_send_data(g_send_data,sizeof(g_send_data));                         //清除串口下发命令标志位
	if(*on)
	{
		report_freezeSwitch_state(false);
		report_intelligentSwitch_state(false);
	}
	else ;
    //report_faultDetection_state(false,108); 
=======
		if(*on)
		{
			 g_send_data[1] = 0x03;                 //下发命令为 1 -> 速冷模式 Add by wangshuqiang @2021-2-18
       	}
		else
	         g_send_data[1] = 0x00;                 //下发命令为 0 -> 默认手动模式 Add by wangshuqiang @2021-2-18
		}
    //printf("Lidongdong:handle_refrigerateSwitch_cmd uart0_send_data()\r\n");    //Lidongdong add @2021-1-27.
	uart0_send_data(g_send_data,sizeof(g_send_data));//Add by lidongdong  @2021-02-5 end.
    //printf(" [Test wangshuqiang   hahhaha ] bit->1   data -> %02X",g_send_data[1]);    
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
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
<<<<<<< HEAD
{	
    /* 实现对on属性的修改 */
    if (on != NULL) {
        /* 请在此处实现设备状态改变的操作 */        //Add by lidongdong  @2021-02-5 begin.
		g_dev_info.g_freezeSwitch = *on;
=======
{
    /* 实现对on属性的修改 */
    if (on != NULL) {
        /* 请在此处实现设备状态改变的操作 */        //Add by lidongdong  @2021-02-5 begin.
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
		if(*on)
			g_send_data[1] = 0x04;                  //1 -> 进入速冻模式 0 -> 默认手动模式 Add by wangshuqiang @2021-2-18
		else
			g_send_data[1] = 0x00;
    }
<<<<<<< HEAD
	caculate_check_num(g_send_data,sizeof(g_send_data));//calculate check_num and send out add by wangshuqiang 2021-3-22
	uart0_send_data(g_send_data,sizeof(g_send_data));
	if(*on)
	{
		report_refrigerateSwitch_state(false);
		report_intelligentSwitch_state(false);
	}
	else ;
=======
	uart0_send_data(g_send_data,sizeof(g_send_data));//Add by lidongdong  @2021-02-5 end.
    //printf(" [Test wangshuqiang   hahhaha ] bit->1   data -> %02X",g_send_data[1]);
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
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
<<<<<<< HEAD
        if (on!= NULL) {
        /* 请在此处实现设备状态改变的操作 */        //Add by lidongdong  @2021-02-5 begin.
		    g_dev_info.g_intelligentSwitch = *on;
			if(*on)
			{   
			  intelligentFlag==true;         //当智能模式标志位为true时，下发数据某些字节手动写入，不在用接受的数据
			  g_send_data[0]  = g_receive_data[0];      //引导码赋值
			  g_send_data[1]  = 0x01;      //// 1 -> 进入智能模式 0 -> 默认手动模式 Add by wangshuqiang @2021-2-18	
			  g_send_data[2]  = 0x6E;	    //冷藏设定赋值
			  g_send_data[3]  = 0x6E;	    //变温设定赋值
			  g_send_data[4]  = 0x40;	    //冷冻设定赋值
			  g_send_data[10] = g_receive_data[19];     //开关设定赋值
			}
			else 
				g_send_data[1] = 0x00;
        }
	caculate_check_num(g_send_data,sizeof(g_send_data));//calculate check_num and send out add by wangshuqiang 2021-3-22
	uart0_send_data(g_send_data,sizeof(g_send_data));
	intelligentFlag = false;
	if(*on)
	{
		report_refrigerateSwitch_state(false);
		report_freezeSwitch_state(false);
	}
	else ;
=======
    if (on!= NULL) {
        /* 请在此处实现设备状态改变的操作 */        //Add by lidongdong  @2021-02-5 begin.
		if(*on)
			g_send_data[1] = 0x01;                  // 1 -> 进入智能模式 0 -> 默认手动模式 Add by wangshuqiang @2021-2-18
		else 
			g_send_data[1] = 0x00;
    }
	uart0_send_data(g_send_data,sizeof(g_send_data));//Add by lidongdong  @2021-02-5 end.
	//printf(" [Test wangshuqiang   hahhaha ] bit->1   data -> %02X",g_send_data[1]);
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
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
<<<<<<< HEAD
{	
    /* 实现对target属性的修改 */
    if (target != NULL) {
		g_dev_info.g_refrigerator_temp_target = *target;
		g_send_data[2] = (char)((*target)*2+100);   //将App下发的控制温度数值经过公式转化为串口通信数值后强制转换为字符型数值 Add by wangshuqiang @2021-2-18
		/* 请在此处实现设备状态改变的操作 */
    }
	//report_refrigerator_state(*target,g_dev_info.g_refrigerator_temp_current);
    caculate_check_num(g_send_data,sizeof(g_send_data));//calculate check_num and send out add by wangshuqiang 2021-3-22
	uart0_send_data(g_send_data,sizeof(g_send_data));
=======
{
    /* 实现对target属性的修改 */
    if (target != NULL) {
		g_send_data[2] = (char)((*target)*2+100);   //将App下发的控制温度数值经过公式转化为串口通信数值后强制转换为字符型数值 Add by wangshuqiang @2021-2-18
        /* 请在此处实现设备状态改变的操作 */
    }
	uart0_send_data(g_send_data,sizeof(g_send_data));//Add by lidongdong  @2021-02-5 end.
	//printf(" [Test wangshuqiang   hahhaha ] bit->2   data -> %02X",g_send_data[2]);
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
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
<<<<<<< HEAD
{	
    /* 实现对target属性的修改 */
   if (target != NULL) {
        /* 请在此处实现设备状态改变的操作 */
		g_dev_info.g_freezer_temp_target = *target;
		g_send_data[4] = (char)((*target)*2+100);  //将App下发的控制温度数值经过公式转化为串口通信数值后强制转换为字符型数值 Add by wangshuqiang @2021-2-18
    }
	caculate_check_num(g_send_data,sizeof(g_send_data));//calculate check_num and send out add by wangshuqiang 2021-3-22
	uart0_send_data(g_send_data,sizeof(g_send_data));
=======
{
    /* 实现对target属性的修改 */
    if (target != NULL) {
        /* 请在此处实现设备状态改变的操作 */
		g_send_data[4] = (char)((*target)*2+100);  //将App下发的控制温度数值经过公式转化为串口通信数值后强制转换为字符型数值 Add by wangshuqiang @2021-2-18
    }
	uart0_send_data(g_send_data,sizeof(g_send_data));
	//printf(" [Test wangshuqiang   hahhaha ] bit->2   data -> %02X",g_send_data[4]);
     //printf16(g_send_data,sizeof(g_send_data));
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
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
<<<<<<< HEAD
int handle_coolingSwitch_cmd(bool *coolingSwitch)
{	
    /* 实现对coolingSwitch属性的修改 */
     if (coolingSwitch != NULL) {
        /* 请在此处实现设备状态改变的操作 */
		g_dev_info.g_coolingSwitch = *coolingSwitch;
		if(*coolingSwitch)                        //1 -> 冷藏开 0 -> 冷藏关 Add by wangshuqiang @2021-2-20
			g_send_data[10] = 0x80;
		else
		{
			g_send_data[10] = 0x00;
			g_send_data[2]  = 0x74;               //自定义，当冷藏开关关闭时，冷藏显示温度位8℃ Add by wangshuqiang @2021-5-18
		}
    }
	caculate_check_num(g_send_data,sizeof(g_send_data));//calculate check_num and send out add by wangshuqiang 2021-3-22
	uart0_send_data(g_send_data,sizeof(g_send_data));
=======

int handle_coolingSwitch_cmd(bool *coolingSwitch)
{
    /* 实现对coolingSwitch属性的修改 */
    if (coolingSwitch != NULL) {
        /* 请在此处实现设备状态改变的操作 */
		if(*coolingSwitch)                        //1 -> 冷藏开 0 -> 冷藏关 Add by wangshuqiang @2021-2-20
		{
			g_send_data[10] = 0x40;               //默认第十个字节第7位始终为1  Add by wangshuqiang @2021-2-20
		}
		else
			g_send_data[10] = 0xC0;
    }
	uart0_send_data(g_send_data,sizeof(g_send_data));
	//printf(" [Test wangshuqiang   hahhaha ] bit->2   data -> %02X",g_send_data[10]);

>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
    /* 若同步操作改变设备状态, 状态改变后, 返回HILINK_OK */
    /* 若异步操作改变设备状态, 此处返回HILINK_PROCESSING, 待状态改变后主动上报新状态 */
    return HILINK_OK;
}
<<<<<<< HEAD

/*
 * 功能: 处理variableTemper服务的控制命令
=======
/*
 * 功能: 处理variableMode服务的控制命令
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
 * 参数: target - target属性的值
 * 返回: HILINK_OK - 操作成功, 设备状态已改变
 *       HILINK_ERR - 操作失败, 设备状态未改变
 *       HILINK_PROCESSING - 正在操作中, 设备状态尚未改变
 * 注意: 1) 返回HILINK_PROCESSING表示设备正在进行异步操作, 待操作完成设备状态改变,
 *          需要主动调用report接口将变更的新状态上报给App;
 *       2) 此函数由开发者实现.
 */
<<<<<<< HEAD
int handle_variableTemper_cmd(int *target)
{	
    /* 实现对target属性的修改 */
    if (target != NULL) {
        /* 请在此处实现设备状态改变的操作 */
		g_dev_info.g_variableTemper_state_target = *target;
		g_send_data[3] = (char)((*target)*2+100);
    }
    caculate_check_num(g_send_data,sizeof(g_send_data));//calculate check_num and send out add by wangshuqiang 2021-3-22
	uart0_send_data(g_send_data,sizeof(g_send_data));
=======
int handle_variableMode_cmd(int *target)
{
    /* 实现对target属性的修改 */
    if (target != NULL) {
        /* 请在此处实现设备状态改变的操作 */
    }
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
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
<<<<<<< HEAD
	
    /* 由开发者实现, 将refrigerateSwitch服务的属性当前值赋予出参 */
	if(on != NULL)
	{
		*on = g_dev_info.g_refrigerateSwitch;  //接收的串口数值对应位解析出后，将状态赋值给指针指向内容等待拉取 Add by wangshuqiang @2021-2-18
	}
=======
	*on = g_dev_info.g_refrigerateSwitch;      //接收的串口数值对应位解析出后，将状态赋值给指针指向内容等待拉取 Add by wangshuqiang @2021-2-18
    /* 由开发者实现, 将refrigerateSwitch服务的属性当前值赋予出参 */
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
    return HILINK_RET_SUCCESS;
}

/*
 * 功能: 处理freezeSwitch服务的状态查询命令
 * 参数: on - on属性的值
 * 返回: 0-成功, 非0-失败
 * 注意: 此函数由开发者实现
 */
int get_freezeSwitch_state(bool *on)
<<<<<<< HEAD
{	
    /* 由开发者实现, 将freezeSwitch服务的属性当前值赋予出参 */
	if(on != NULL)
	{
	  *on = g_dev_info.g_freezeSwitch;          //冷冻模式状态赋值出参  Add by wangshuqiang @2021-2-20
	}
=======
{
    /* 由开发者实现, 将freezeSwitch服务的属性当前值赋予出参 */
	*on = g_dev_info.g_freezeSwitch;          //冷冻模式状态赋值出参  Add by wangshuqiang @2021-2-20
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
    return HILINK_RET_SUCCESS;
}

/*
 * 功能: 处理intelligentSwitch服务的状态查询命令
 * 参数: on - on属性的值
 * 返回: 0-成功, 非0-失败
 * 注意: 此函数由开发者实现
 */
int get_intelligentSwitch_state(bool *on)
<<<<<<< HEAD
{	
    /* 由开发者实现, 将intelligentSwitch服务的属性当前值赋予出参 */
	if(on != NULL)
	{
	  *on = g_dev_info.g_intelligentSwitch;     //智能模式状态赋值出参  Add by wangshuqiang @2021-2-20
	}
=======
{
	*on = g_dev_info.g_intelligentSwitch;     //智能模式状态赋值出参  Add by wangshuqiang @2021-2-20
    /* 由开发者实现, 将intelligentSwitch服务的属性当前值赋予出参 */
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
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
<<<<<<< HEAD
{	
    /* 由开发者实现, 将refrigerator服务的属性当前值赋予出参 */
	if(target != NULL)
	{ 
       *target = g_dev_info.g_refrigerator_temp_target;       //冷藏室设定数值与当前状态赋值出参  Add by wangshuqiang @2021-2-20  
	}
	if(current != NULL)
	{	
       *current = g_dev_info.g_refrigerator_temp_current;
	}
=======
{
    /* 由开发者实现, 将refrigerator服务的属性当前值赋予出参 */
	*target = g_dev_info.g_refrigerator_temp_target;       //冷藏室设定数值与当前状态赋值出参  Add by wangshuqiang @2021-2-20    
	*current = g_dev_info.g_refrigerator_temp_current;
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
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
<<<<<<< HEAD
{	
    /* 由开发者实现, 将freezer服务的属性当前值赋予出参 */
	if(target != NULL)
	{
		*target = g_dev_info.g_freezer_temp_target;            //冷冻室设定数值与当前状态赋值出参  Add by wangshuqiang @2021-2-20
	}
	if(current != NULL)
	{
	    *current = g_dev_info.g_freezer_temp_current;
	}
=======
{
    /* 由开发者实现, 将freezer服务的属性当前值赋予出参 */
	*target = g_dev_info.g_freezer_temp_target;            //冷冻室设定数值与当前状态赋值出参  Add by wangshuqiang @2021-2-20
	*current = g_dev_info.g_freezer_temp_current;
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
    return HILINK_RET_SUCCESS;
}

/*
 * 功能: 处理coolingSwitch服务的状态查询命令
 * 参数: coolingSwitch - coolingSwitch属性的值
 * 返回: 0-成功, 非0-失败
 * 注意: 此函数由开发者实现
 */
int get_coolingSwitch_state(bool *coolingSwitch)
<<<<<<< HEAD
{	
    /* 由开发者实现, 将coolingSwitch服务的属性当前值赋予出参 */
	if(coolingSwitch != NULL)
	{
	    *coolingSwitch = g_dev_info.g_coolingSwitch;           //冷藏开关状态赋值出参  Add by wangshuqiang @2021-2-20
	}
=======
{
    /* 由开发者实现, 将coolingSwitch服务的属性当前值赋予出参 */
	*coolingSwitch = g_dev_info.g_coolingSwitch;           //冷藏开关状态赋值出参  Add by wangshuqiang @2021-2-20
	//printf("[TEST wangshuqiang   %d\r\n]",g_dev_info.g_coolingSwitch);
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
    return HILINK_RET_SUCCESS;
}

/*
<<<<<<< HEAD
 * 功能: 处理variableTemper服务的状态查询命令
=======
 * 功能: 处理variableMode服务的状态查询命令
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
 * 参数: target - target属性的值
 * 返回: 0-成功, 非0-失败
 * 注意: 此函数由开发者实现
 */
<<<<<<< HEAD
int get_variableTemper_state(int *target)
{	
    /* 由开发者实现, 将variableTemper服务的属性当前值赋予出参 */
	if(target != NULL)
	{
	    *target = g_dev_info.g_variableTemper_state_target;
	}
=======
int get_variableMode_state(int *target)
{
    /* 由开发者实现, 将variableMode服务的属性当前值赋予出参 */

>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
    return HILINK_RET_SUCCESS;
}

/*
 * 功能: 处理VariableRoom1服务的状态查询命令
 * 参数: current - current属性的值
 * 返回: 0-成功, 非0-失败
 * 注意: 此函数由开发者实现
 */
int get_VariableRoom1_state(int *current)
<<<<<<< HEAD
{	
    /* 由开发者实现, 将VariableRoom1服务的属性当前值赋予出参 */
	if(current != NULL)
	{
	    *current = g_dev_info.g_VariableRoom1_temp_current;
	}
=======
{
    /* 由开发者实现, 将VariableRoom1服务的属性当前值赋予出参 */
	*current = g_dev_info.g_VariableRoom1_temp_target;    //变温室当前状态赋值出参  Add by wangshuqiang @2021-2-20
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
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
<<<<<<< HEAD
 * 注意: 如果产品定义有子型号，则填入两字节子型号，并以' '结束, 返回0;
=======
 * 注意: 如果产品定义有子型号，则填入两字节子型号，并以' '结束, 返回0;
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
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
