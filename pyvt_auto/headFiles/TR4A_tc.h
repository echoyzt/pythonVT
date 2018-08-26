/*******************************************************************************
* Copyright (C) 2009, 上海微电子装备有限公司
* All rights reserved.
* 产品号 : ADAE
* 所属组件 : TR
* 模块名称 : libTR4A
* 文件名称 : TR4A_tc.h
* 概要描述 :
* 历史记录 :
* 版本      日期        作者		内容
* V1.0      2008-08-30	sucb		1、创建文档。
*******************************************************************************/

#ifndef		__TR4A_TC_H__
#define		__TR4A_TC_H__

#include "smee.h"
#include "ADAE.h"


/* 错误码宏定义 */
#define TR4A_SYSTEM_ERR					0x54520000					/*系统错误*/
#define TR4A_TIMEOUT_ERR				0x54520001					/*超时错误*/
#define TR4A_PARAMETER_ERR				0x54520002					/*参数错误*/
#define TR4A_ILLEGAL_CALL_ERR			0x54520003		           /*非法调用*/
#define TR4A_NOT_INITIALIZED_ERR		0x54520004					/*TR未初始化错误*/
#define TR4A_NOT_TERMINATED_ERR			0x54520005					/*TR未终止*/
#define TR4A_SERVER_NOT_LISTENING_ERR	0x54520006					/*服务未监听*/
#define TR4A_BUFF_ERR					0x54520007					/*缓存错误*/
#define TR4A_INVALID_FORMAT_ERR         0x54520008					/*格式错误*/



/*== Type definitions =======================================================*/

/*仿真模式枚举*/
typedef enum
{
	TR4A_SIM_MODE_MIN = -1,
	TR4A_SIM_DISABLED,  // simulation mode disabled
	TR4A_SIM_MODE_1,    // external simulation mode
	TR4A_SIM_MODE_2,    // internal simulation mode
	TR4A_SIM_MODE_3,	// 
	TR4A_SIM_MODE_4,	//test mode for testing
	TR4A_SIM_MODE_MAX
} TR4A_SIM_MODE_ENUM;

/*跟踪模式枚举*/
typedef enum
{
	TR4A_TRACE_MODE_MIN = -1,
	TR4A_TRACE_DISABLED,
	TR4A_TRACE_INT,
	TR4A_TRACE_EXT,
	TR4A_TRACE_INT_EXT,
	TR4A_TRACE_REAL_TIME,     //暂时不使用
	TR4A_INT_REAL,            
	TR4A_EXT_REAL,            
	TR4A_TRACE_INT_EXT_REAL,  
	TR4A_TRACE_MODE_MAX
} TR4A_TRACE_MODE_ENUM;

/*数据注入模式枚举*/
typedef enum
{
	TR4A_REQ_MODE_MIN = -1,  
	TR4A_REQ_DISABLED,
	TR4A_REQ_INT_INPUT,
	TR4A_REQ_INT_OUTPUT,
	TR4A_REQ_INT_INOUT,
	TR4A_REQ_EXT_INPUT,
	TR4A_REQ_EXT_OUTPUT,
	TR4A_REQ_EXT_INOUT,
	TR4A_REQ_INT_EXT_INPUT,
	TR4A_REQ_INT_EXT_OUTPUT,
	TR4A_REQ_INT_EXT_INOUT,
	TR4A_REQ_MODE_MAX
} TR4A_REQ_MODE_ENUM;



#endif /*_TR4A_TC_H_*/
