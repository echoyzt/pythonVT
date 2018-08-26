/*******************************************************************************
* Copyright (C) 2009, �Ϻ�΢����װ�����޹�˾
* All rights reserved.
* ��Ʒ�� : ADAE
* ������� : TR
* ģ������ : libTR4A
* �ļ����� : TR4A_tc.h
* ��Ҫ���� :
* ��ʷ��¼ :
* �汾      ����        ����		����
* V1.0      2008-08-30	sucb		1�������ĵ���
*******************************************************************************/

#ifndef		__TR4A_TC_H__
#define		__TR4A_TC_H__

#include "smee.h"
#include "ADAE.h"


/* ������궨�� */
#define TR4A_SYSTEM_ERR					0x54520000					/*ϵͳ����*/
#define TR4A_TIMEOUT_ERR				0x54520001					/*��ʱ����*/
#define TR4A_PARAMETER_ERR				0x54520002					/*��������*/
#define TR4A_ILLEGAL_CALL_ERR			0x54520003		           /*�Ƿ�����*/
#define TR4A_NOT_INITIALIZED_ERR		0x54520004					/*TRδ��ʼ������*/
#define TR4A_NOT_TERMINATED_ERR			0x54520005					/*TRδ��ֹ*/
#define TR4A_SERVER_NOT_LISTENING_ERR	0x54520006					/*����δ����*/
#define TR4A_BUFF_ERR					0x54520007					/*�������*/
#define TR4A_INVALID_FORMAT_ERR         0x54520008					/*��ʽ����*/



/*== Type definitions =======================================================*/

/*����ģʽö��*/
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

/*����ģʽö��*/
typedef enum
{
	TR4A_TRACE_MODE_MIN = -1,
	TR4A_TRACE_DISABLED,
	TR4A_TRACE_INT,
	TR4A_TRACE_EXT,
	TR4A_TRACE_INT_EXT,
	TR4A_TRACE_REAL_TIME,     //��ʱ��ʹ��
	TR4A_INT_REAL,            
	TR4A_EXT_REAL,            
	TR4A_TRACE_INT_EXT_REAL,  
	TR4A_TRACE_MODE_MAX
} TR4A_TRACE_MODE_ENUM;

/*����ע��ģʽö��*/
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
