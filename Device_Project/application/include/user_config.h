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
#define BYTE_7 (1<<5)
#define BYTE_8 (1<<7)

typedef struct 
{
	bool g_refrigerateSwitch;        //模式设定 0x03 速冷模式
	bool g_freezeSwitch;             //模式设定 0x04 速冻模式
	bool g_intelligentSwitch;        //模式设定 0x01 智能模式
	int g_refrigerator_temp_target;  //冷藏室设置温度
	int g_refrigerator_temp_current; //冷藏室当前温度
	int g_freezer_temp_target;       //冷冻室设置温度
	int g_freezer_temp_current;      //冷冻室当前温度
	//todo
} DevInfo;

extern uint8 g_send_data[19];
extern uint8 g_receive_data[22];
extern uint8 g_receive_data_old[22];
extern DevInfo g_dev_info;

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