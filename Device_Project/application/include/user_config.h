/*
 * ESPRSSIF MIT License
 *
 * Copyright (c) 2015 <ESPRESSIF SYSTEMS (SHANGHAI) PTE LTD>
 *
 * Permission is hereby granted for use on ESPRESSIF SYSTEMS ESP8266 only, in which case,
 * it is free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef __USER_CONFIG_H__
#define __USER_CONFIG_H__

#endif

#define BYTE_1 (1<<0)
#define BYTE_2 (1<<1)
#define BYTE_3 (1<<2)
#define BYTE_4 (1<<3)
#define BYTE_5 (1<<4)
#define BYTE_6 (1<<5)
<<<<<<< HEAD
#define BYTE_7 (1<<6)
#define BYTE_8 (1<<7)


typedef struct 
{
	bool g_refrigerateSwitch;         //模式设定 0x03 速冷模式
	bool g_freezeSwitch;              //模式设定 0x04 速冻模式
	bool g_intelligentSwitch;         //模式设定 0x01 智能模式
	bool g_coolingSwitch;             //冷藏开关 
	int g_refrigerator_temp_target;   //冷藏室设置温度
	int g_refrigerator_temp_current;  //冷藏室当前温度
	int g_freezer_temp_target;        //冷冻室设置温度
	int g_freezer_temp_current;       //冷冻室当前温度
	int g_VariableRoom1_temp_current; //变温室当前温度
	int g_variableTemper_state_target;//变温室设置温度
	bool refrigerator_fault_flag;     //冷藏传感器故障
	bool variable_fault;              //变温传感器故障
	bool freezer_fault;               //冷冻传感器故障
	bool environmentTemper_fault;     //环温传感器故障
	bool defrostSensor_fault;         //化霜传感器故障
	bool conmunication_fault;         //通信故障
	bool refrigerDoor_overtime_fault; //冷藏门开超时
	bool fans_fault;                  //风门堵转
	bool humiditySensor_fault;        //湿度传感器故障
	bool defrost_fault;               //化霜故障
	bool normal;                      //无故障情况，正常
=======
#define BYTE_7 (1<<5)
#define BYTE_8 (1<<7)

typedef struct 
{
	bool g_refrigerateSwitch;        //模式设定 0x03 速冷模式
	bool g_freezeSwitch;             //模式设定 0x04 速冻模式
	bool g_intelligentSwitch;        //模式设定 0x01 智能模式
	bool g_coolingSwitch;            //冷藏开关 
	int g_refrigerator_temp_target;  //冷藏室设置温度
	int g_refrigerator_temp_current; //冷藏室当前温度
	int g_freezer_temp_target;       //冷冻室设置温度
	int g_freezer_temp_current;      //冷冻室当前温度
	int g_VariableRoom1_temp_target; //变温设定温度
>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
	//todo
} DevInfo;

extern uint8 g_send_data[13];
<<<<<<< HEAD
extern uint8 g_receive_data[23];
extern uint8 g_receive_data_old[23];
extern DevInfo g_dev_info;
//extern bool hilink_restore_factory_flag;
extern bool Waiting_connected_Flag;
extern bool connected_Flag;
extern bool intelligentFlag;
extern char inConfig;	
extern char user_flash_message;                   
extern uint8 wait_connected[5];
extern uint8 buf_idx;
=======
extern uint8 g_receive_data[22];
extern uint8 g_receive_data_old[22];
extern DevInfo g_dev_info;

>>>>>>> d8fec011c7d87fcd256ca3b294bfba1cf829f3ae
/*
typedef enum
{
	NORMAL_MODE = 0,
	SMART_MODE = ,	
	HOLIDAY_MODE,
	SUPER_FRZ_MODE,
	SUPER_REF_MODE,
	MUTE_MODE
}
*/