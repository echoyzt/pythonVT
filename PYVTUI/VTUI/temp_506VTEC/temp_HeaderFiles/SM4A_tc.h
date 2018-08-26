/*****************************************************************************
* Copyright (C) 2009, �Ϻ�΢����װ�����޹�˾
* All rights reserved. 
* ��Ʒ�� : ADAE 
* ������� : SM
* ģ������ : SM4A
* �ļ����� : SM4A_tc.h      
* ��ʷ��¼ : 
* �汾      ����         ����       ����
* 1.0       2009-06-24    ë����		����ӿ�
*****************************************************************************/

#ifndef _SM4A_TC_H
#define _SM4A_TC_H
#include <ADAE.h>

/*********************SM GENEARAL*************************************/
#define SM_SYSTEM_NAME_LEN 15			/*����SYSTEM������󳤶�*/
#define SM_HOST_NAME_LEN 31				/*����HOST������󳤶�*/
#define SM_JOB_NAME_LEN 35				/*����JOB������󳤶�*/
#define	SM_MODULE_NAME_LEN 35			/*����MODULE������󳤶�*/
#define	SM_TASK_NAME_LEN 35				/*����TASK������󳤶�*/
#define	SM_OPTION_NAME_LEN 35			/*����OPTION������󳤶�*/

#define SM_MAX_NR_OF_HOSTS 16			/*����HOST�����Ŀ*/
#define SM_MAX_NR_OF_JOBS 150			/*����JOB�����Ŀ*/
#define SM_MAX_NR_OF_TASKS 500			/*����TASK�����Ŀ*/
#define SM_MAX_SERVERS 300				/*����SERVER�����Ŀ*/
#define SM_MAX_SERVERS_OF_JOB 16		/*����ÿ�����SERVER�����Ŀ*/
#define SM_MAX_MODULES 64				/*����MODULES�����Ŀ*/
#define SM_MAX_OPTIONS 16				/*����OPTIONS�����Ŀ*/
#define SM_MAX_SEQ 64					/*������ͬһ����վ��ƽ̨ͬʱ���������Ŀ*/
#define SM4A_MAX_DIRVERS 100			/*����Driver�����Ŀ*/
#define SM4A_DRIVER_NAME_LENGTH 7		/*�����������ֳ���*/

/***************************error_code**********************************/
#define SM4A_CONST_BASE					0x534D0000
#define SM4A_SYSTEM_ERR          		SM4A_CONST_BASE               /* 0x534D0000:ϵͳ���󣬴��󽫱���¼�ڴ�����־�� */
#define SM4A_TIMEOUT_ERR                (SM4A_CONST_BASE + 0x001)     /* 0x534D0001:��ʱ���� */
#define SM4A_ILLEGAL_STATION_ERR        (SM4A_CONST_BASE + 0x002)     /* 0x534D0002:�Ƿ��Ĺ���վid */
#define SM4A_ILLEGAL_DRIVER_ERR         (SM4A_CONST_BASE + 0x003)     /* 0x534D0003 */
#define SM4A_JOB_NOT_STARTED_ERR        (SM4A_CONST_BASE + 0x004)     /* 0x534D0004:��ҵû������ */
#define SM4A_JOB_ALREADY_START_ERR      (SM4A_CONST_BASE + 0x005)     /* 0x534D0005:��ҵ�ѱ����� */
#define SM4A_TASK_NOT_STARTED_ERR       (SM4A_CONST_BASE + 0x006)     /* 0x534D0006:����û������ */
#define SM4A_TASK_ALREADY_START_ERR     (SM4A_CONST_BASE + 0x007)     /* 0x534D0007:�����ѱ����� */
#define SM4A_NO_MEMORY_ERR              (SM4A_CONST_BASE + 0x008)     /* 0x534D0008:����ģ��ʱ�ڴ治�� */
#define SM4A_DC_INIT_FAILED_ERR         (SM4A_CONST_BASE + 0x009)     /* 0x534D0009 */
#define SM4A_TERMINATION_FAILED_ERR     (SM4A_CONST_BASE + 0x00A)     /* 0x534D000A */
#define SM4A_NO_SUCH_FILE_ERR           (SM4A_CONST_BASE + 0x00B)     /* 0x534D000B */
#define SM4A_PARSER_ERR					(SM4A_CONST_BASE + 0x00C)     /* 0x534D000C */
#define SM4A_FILE_NOT_FOUND_ERR         (SM4A_CONST_BASE + 0x00D)     /* 0x534D000D */
#define SM4A_FILE_LAYOUT_ERR			(SM4A_CONST_BASE + 0x00E)     /* 0x534D000E */
#define SM4A_OUT_PARAM_ERR				(SM4A_CONST_BASE + 0x00F)     /* 0x534D000F */
#define SM4A_INITIALIZATION_FAILED_ERR  (SM4A_CONST_BASE + 0x010)     /* 0x534D0010 */
#define SM4A_SEND_SLAVE_FAILED_ERR      (SM4A_CONST_BASE + 0x011)     /* 0x534D0011 */
#define SM4A_PARAMETER_ERR				(SM4A_CONST_BASE + 0x012)	  /*��������*/
#define SM4A_NO_SUCH_JOB_ERR			(SM4A_CONST_BASE + 0x013)	  /*û����������ҵ*/
#define SM4A_NO_SUCH_TASK_ERR			(SM4A_CONST_BASE + 0x014)	  /*û������������*/

#define SM4A_NO_SUCH_DRIVER_ERR			(SM4A_CONST_BASE + 0x015)	  /*û������������*/
#define SM4A_CIRTICAL_DATA_CHANGED_ERR	(SM4A_CONST_BASE + 0x016)	  /*�ؼ����ݷ����仯,�ô��������ڹؼ����ݱ仯,��Ҫ���ý�EH_reportʹ��*/
#define SM4A_DRIVER_DISABLED_ERR        (SM4A_CONST_BASE + 0x017)     /* Driver id is known to this SM but it is disabled */
#define SM4A_DRIVER_UNKNOWN_ERR         (SM4A_CONST_BASE + 0x018)     /* Driver id is unknown to this SM */
#define SM4A_INITIALIZATION_ERR         (SM4A_CONST_BASE + 0x019)     /* ��ʼ������ʧ�� */
#define SM4A_TERMINATION_ERR			(SM4A_CONST_BASE + 0x01A)     /* ��ֹ����ʧ�� */

#define SM4A_DRIVER_END					"End_drv"
#define SM4A_ALL_DRIVERS				"All_drv"

/*ö�٣�����״̬*/
typedef enum
{
	SM4A_BOOT_MIN = -1,
	SM4A_NOT_BOOTED,            /*û����*/
	SM4A_BUSY_BOOTING,          /*��������*/      
	SM4A_BOOTED,				/*������*/
	SM4A_BOOT_MAX
} SM4A_BOOT_STATUS_ENUM;

/*ö�٣���ҵ״̬*/
typedef enum
{
	SM4A_JOB_START_MIN = -1,
	SM4A_JOB_STARTED,       /*������*/
	SM4A_JOB_NOT_STARTED,	/*δ����*/
	SM4A_JOB_START_MAX
} SM4A_JOB_STATUS_ENUM;

/*ö�٣�����״̬*/
typedef enum
{
	SM4A_TASK_START_MIN = -1,
	SM4A_TASK_STARTED,       /*������*/
	SM4A_TASK_NOT_STARTED,	/*δ����*/
	SM4A_TASK_START_MAX
} SM4A_TASK_STATUS_ENUM;

/*������ʽ*/
typedef enum 
{
	SM4A_IMPORTANCE_MIN = -1,
	SM4A_EXPLICIT,			/*��ȫ����*/
	SM4A_IF_NECESSARY,		/*��������*/
	SM4A_IMPORTANCE_MAX
} SM4A_IMPORTANCE_ENUM;

/*SM�����ȡ������״̬*/
typedef enum 
{
	SM4A_DRIVER_STATUS_MIN = -1,
	SM4A_START_INITIALIZATION,			/*��ʼ��ʼ��*/
	SM4A_READY_INITIALIZATION,			/*��ʼ�����*/
	SM4A_START_RETRY_INITIALIZATION,	/*�ٴο�ʼ��ʼ��*/
	SM4A_READY_RETRY_INITIALIZATION,	/*�ٴγ�ʼ�����*/
	SM4A_FAILED_INITIALIZATION,			/*��ʼ��ʧ��*/
	SM4A_WAITING_INITIALIZATION,		/*�ȴ���ʼ��*/
	SM4A_START_TERMINATION,				/*��ʼ��ֹ*/
	SM4A_READY_TERMINATION,				/*��ֹ���*/
	SM4A_START_RETRY_TERMINATION,		/*�ٴο�ʼ��ֹ*/
	SM4A_READY_RETRY_TERMINATION,		/*�ٴ���ֹ���*/
	SM4A_FAILED_TERMINATION,			/*��ֹʧ��*/
	SM4A_DRIVER_STATUS_MAX
} SM4A_DRIVER_STATUS_ENUM;

/*ϵͳ����״̬*/
typedef enum 
{
	SM4A_DRIVER_STATE_MIN = -1,
	SM4A_IDLE,				/*�ѳ�ʼ��*/
	SM4A_TERMINATED,        /*����ֹ*/
	SM4A_BUSY,				/*����״̬*/ 
	SM4A_DRIVER_STATE_MAX
} SM4A_DRIVER_STATE_ENUM;

/*������Ϣö��*/
typedef enum 
{
	SM4A_DRIVER_INFO_MIN = -1,
	SM4A_DRIVER_ENABLED,             /*������*/
	SM4A_DRIVER_DISABLED,            /*��������*/
	SM4A_DRIVER_INFO_MAX
} SM4A_DRIVER_INFO_ENUM;

/*ʱ����ṹ*/
typedef struct 
{
	int				node_id;		/*����վid*/
	SMEE_BOOL		host_present;	/*����վ��Ϣ*/
	ADAE_TIME_VALUE  timestamp;		/*ʱ���*/
} SM4A_NODE_TIMESTAMP_STRUCT;

/*���ݽṹ������״̬*/
typedef struct
{
	SM4A_BOOT_STATUS_ENUM   boot_status;
	SMEE_BOOL               host_present;
} SM4A_HOST_STATUS_STRUCT;

/*��������*/
typedef char SM4A_DRIVER_NAME[SM4A_DRIVER_NAME_LENGTH+1];

/*��ʼ��/��ֹʱ��������״̬�ṹ��*/
typedef struct
{
	SM4A_DRIVER_NAME		driver_names;	/*��������*/
	SM4A_DRIVER_STATUS_ENUM	driver_status;	/*����״̬*/
	int ifiller;
} SM4A_WAIT_STATUS_STRUCT; 

/*��ȡ����״̬�ṹ��*/
typedef struct
{
	SM4A_DRIVER_NAME		driver_names;	/*��������*/
	SM4A_DRIVER_STATE_ENUM	driver_status;	/*����״̬*/
	int error_code;							/*����״̬��ȡ���*/
} SM4A_GET_STATUS_STRUCT; 

/*���ݽṹ������վ��Ϣ*/
typedef struct
{
	SMEE_BOOL	host_present;							/*����HOST�Ƿ�������*/
	int			host_id;								/*����HOST��ID��*/
	char		host_name[SM_HOST_NAME_LEN+1];			/*����HOST������*/
	char		host_ip[SM_HOST_NAME_LEN+1];			/*����HOST��IP*/
} SM4A_HOST_INFO_STRUCT;

#endif /*_SM4A_TC_H*/
