/*****************************************************************************
* Copyright (C) 2009, 上海微电子装备有限公司
* All rights reserved. 
* 产品号 : ADAE 
* 所属组件 : SM
* 模块名称 : SM4A
* 文件名称 : SM4A_tc.h      
* 历史记录 : 
* 版本      日期         作者       内容
* 1.0       2009-06-24    毛明辉		定义接口
*****************************************************************************/

#ifndef _SM4A_TC_H
#define _SM4A_TC_H
#include <ADAE.h>

/*********************SM GENEARAL*************************************/
#define SM_SYSTEM_NAME_LEN 15			/*定义SYSTEM名字最大长度*/
#define SM_HOST_NAME_LEN 31				/*定义HOST名字最大长度*/
#define SM_JOB_NAME_LEN 35				/*定义JOB名字最大长度*/
#define	SM_MODULE_NAME_LEN 35			/*定义MODULE名字最大长度*/
#define	SM_TASK_NAME_LEN 35				/*定义TASK名字最大长度*/
#define	SM_OPTION_NAME_LEN 35			/*定义OPTION名字最大长度*/

#define SM_MAX_NR_OF_HOSTS 16			/*定义HOST最大数目*/
#define SM_MAX_NR_OF_JOBS 150			/*定义JOB最大数目*/
#define SM_MAX_NR_OF_TASKS 500			/*定义TASK最大数目*/
#define SM_MAX_SERVERS 300				/*定义SERVER最大数目*/
#define SM_MAX_SERVERS_OF_JOB 16		/*定义每个组件SERVER最大数目*/
#define SM_MAX_MODULES 64				/*定义MODULES最大数目*/
#define SM_MAX_OPTIONS 16				/*定义OPTIONS最大数目*/
#define SM_MAX_SEQ 64					/*定义在同一工作站上平台同时启动最大数目*/
#define SM4A_MAX_DIRVERS 100			/*定义Driver最大数目*/
#define SM4A_DRIVER_NAME_LENGTH 7		/*定义驱动名字长度*/

/***************************error_code**********************************/
#define SM4A_CONST_BASE					0x534D0000
#define SM4A_SYSTEM_ERR          		SM4A_CONST_BASE               /* 0x534D0000:系统错误，错误将被记录在错误日志中 */
#define SM4A_TIMEOUT_ERR                (SM4A_CONST_BASE + 0x001)     /* 0x534D0001:超时错误 */
#define SM4A_ILLEGAL_STATION_ERR        (SM4A_CONST_BASE + 0x002)     /* 0x534D0002:非法的工作站id */
#define SM4A_ILLEGAL_DRIVER_ERR         (SM4A_CONST_BASE + 0x003)     /* 0x534D0003 */
#define SM4A_JOB_NOT_STARTED_ERR        (SM4A_CONST_BASE + 0x004)     /* 0x534D0004:作业没被启动 */
#define SM4A_JOB_ALREADY_START_ERR      (SM4A_CONST_BASE + 0x005)     /* 0x534D0005:作业已被启动 */
#define SM4A_TASK_NOT_STARTED_ERR       (SM4A_CONST_BASE + 0x006)     /* 0x534D0006:任务没被启动 */
#define SM4A_TASK_ALREADY_START_ERR     (SM4A_CONST_BASE + 0x007)     /* 0x534D0007:任务已被启动 */
#define SM4A_NO_MEMORY_ERR              (SM4A_CONST_BASE + 0x008)     /* 0x534D0008:下载模块时内存不够 */
#define SM4A_DC_INIT_FAILED_ERR         (SM4A_CONST_BASE + 0x009)     /* 0x534D0009 */
#define SM4A_TERMINATION_FAILED_ERR     (SM4A_CONST_BASE + 0x00A)     /* 0x534D000A */
#define SM4A_NO_SUCH_FILE_ERR           (SM4A_CONST_BASE + 0x00B)     /* 0x534D000B */
#define SM4A_PARSER_ERR					(SM4A_CONST_BASE + 0x00C)     /* 0x534D000C */
#define SM4A_FILE_NOT_FOUND_ERR         (SM4A_CONST_BASE + 0x00D)     /* 0x534D000D */
#define SM4A_FILE_LAYOUT_ERR			(SM4A_CONST_BASE + 0x00E)     /* 0x534D000E */
#define SM4A_OUT_PARAM_ERR				(SM4A_CONST_BASE + 0x00F)     /* 0x534D000F */
#define SM4A_INITIALIZATION_FAILED_ERR  (SM4A_CONST_BASE + 0x010)     /* 0x534D0010 */
#define SM4A_SEND_SLAVE_FAILED_ERR      (SM4A_CONST_BASE + 0x011)     /* 0x534D0011 */
#define SM4A_PARAMETER_ERR				(SM4A_CONST_BASE + 0x012)	  /*参数错误*/
#define SM4A_NO_SUCH_JOB_ERR			(SM4A_CONST_BASE + 0x013)	  /*没有这样的作业*/
#define SM4A_NO_SUCH_TASK_ERR			(SM4A_CONST_BASE + 0x014)	  /*没有这样的任务*/

#define SM4A_NO_SUCH_DRIVER_ERR			(SM4A_CONST_BASE + 0x015)	  /*没有这样的驱动*/
#define SM4A_CIRTICAL_DATA_CHANGED_ERR	(SM4A_CONST_BASE + 0x016)	  /*关键数据发生变化,该错误码用于关键数据变化,需要配置进EH_report使用*/
#define SM4A_DRIVER_DISABLED_ERR        (SM4A_CONST_BASE + 0x017)     /* Driver id is known to this SM but it is disabled */
#define SM4A_DRIVER_UNKNOWN_ERR         (SM4A_CONST_BASE + 0x018)     /* Driver id is unknown to this SM */
#define SM4A_INITIALIZATION_ERR         (SM4A_CONST_BASE + 0x019)     /* 初始化驱动失败 */
#define SM4A_TERMINATION_ERR			(SM4A_CONST_BASE + 0x01A)     /* 终止驱动失败 */

#define SM4A_DRIVER_END					"End_drv"
#define SM4A_ALL_DRIVERS				"All_drv"

/*枚举：启动状态*/
typedef enum
{
	SM4A_BOOT_MIN = -1,
	SM4A_NOT_BOOTED,            /*没启动*/
	SM4A_BUSY_BOOTING,          /*正在启动*/      
	SM4A_BOOTED,				/*已启动*/
	SM4A_BOOT_MAX
} SM4A_BOOT_STATUS_ENUM;

/*枚举：作业状态*/
typedef enum
{
	SM4A_JOB_START_MIN = -1,
	SM4A_JOB_STARTED,       /*已启动*/
	SM4A_JOB_NOT_STARTED,	/*未启动*/
	SM4A_JOB_START_MAX
} SM4A_JOB_STATUS_ENUM;

/*枚举：任务状态*/
typedef enum
{
	SM4A_TASK_START_MIN = -1,
	SM4A_TASK_STARTED,       /*已启动*/
	SM4A_TASK_NOT_STARTED,	/*未启动*/
	SM4A_TASK_START_MAX
} SM4A_TASK_STATUS_ENUM;

/*启动方式*/
typedef enum 
{
	SM4A_IMPORTANCE_MIN = -1,
	SM4A_EXPLICIT,			/*完全启动*/
	SM4A_IF_NECESSARY,		/*快速启动*/
	SM4A_IMPORTANCE_MAX
} SM4A_IMPORTANCE_ENUM;

/*SM组件获取的驱动状态*/
typedef enum 
{
	SM4A_DRIVER_STATUS_MIN = -1,
	SM4A_START_INITIALIZATION,			/*开始初始化*/
	SM4A_READY_INITIALIZATION,			/*初始化完成*/
	SM4A_START_RETRY_INITIALIZATION,	/*再次开始初始化*/
	SM4A_READY_RETRY_INITIALIZATION,	/*再次初始化完成*/
	SM4A_FAILED_INITIALIZATION,			/*初始化失败*/
	SM4A_WAITING_INITIALIZATION,		/*等待初始化*/
	SM4A_START_TERMINATION,				/*开始终止*/
	SM4A_READY_TERMINATION,				/*终止完成*/
	SM4A_START_RETRY_TERMINATION,		/*再次开始终止*/
	SM4A_READY_RETRY_TERMINATION,		/*再次终止完成*/
	SM4A_FAILED_TERMINATION,			/*终止失败*/
	SM4A_DRIVER_STATUS_MAX
} SM4A_DRIVER_STATUS_ENUM;

/*系统驱动状态*/
typedef enum 
{
	SM4A_DRIVER_STATE_MIN = -1,
	SM4A_IDLE,				/*已初始化*/
	SM4A_TERMINATED,        /*已终止*/
	SM4A_BUSY,				/*生产状态*/ 
	SM4A_DRIVER_STATE_MAX
} SM4A_DRIVER_STATE_ENUM;

/*驱动信息枚举*/
typedef enum 
{
	SM4A_DRIVER_INFO_MIN = -1,
	SM4A_DRIVER_ENABLED,             /*能运行*/
	SM4A_DRIVER_DISABLED,            /*不能运行*/
	SM4A_DRIVER_INFO_MAX
} SM4A_DRIVER_INFO_ENUM;

/*时间戳结构*/
typedef struct 
{
	int				node_id;		/*工作站id*/
	SMEE_BOOL		host_present;	/*工作站信息*/
	ADAE_TIME_VALUE  timestamp;		/*时间戳*/
} SM4A_NODE_TIMESTAMP_STRUCT;

/*数据结构：主机状态*/
typedef struct
{
	SM4A_BOOT_STATUS_ENUM   boot_status;
	SMEE_BOOL               host_present;
} SM4A_HOST_STATUS_STRUCT;

/*驱动名称*/
typedef char SM4A_DRIVER_NAME[SM4A_DRIVER_NAME_LENGTH+1];

/*初始化/终止时返回驱动状态结构体*/
typedef struct
{
	SM4A_DRIVER_NAME		driver_names;	/*驱动名称*/
	SM4A_DRIVER_STATUS_ENUM	driver_status;	/*驱动状态*/
	int ifiller;
} SM4A_WAIT_STATUS_STRUCT; 

/*获取驱动状态结构体*/
typedef struct
{
	SM4A_DRIVER_NAME		driver_names;	/*驱动名称*/
	SM4A_DRIVER_STATE_ENUM	driver_status;	/*驱动状态*/
	int error_code;							/*驱动状态获取结果*/
} SM4A_GET_STATUS_STRUCT; 

/*数据结构：工作站信息*/
typedef struct
{
	SMEE_BOOL	host_present;							/*定义HOST是否已配置*/
	int			host_id;								/*定义HOST的ID号*/
	char		host_name[SM_HOST_NAME_LEN+1];			/*定义HOST的名字*/
	char		host_ip[SM_HOST_NAME_LEN+1];			/*定义HOST的IP*/
} SM4A_HOST_INFO_STRUCT;

#endif /*_SM4A_TC_H*/
