/*********************************************************************
* Copyright (C) 2008, �Ϻ�΢����װ�����޹�˾
* All rights reserved.
* �� Ʒ �� : ADAE
* ������� : GF
* ģ������ : None
* �ļ����� : ADAE.h
* ��Ҫ���� : ADAE����ͷ�ļ����ṩ��ƽ̨���Ͷ����Լ����ú궨��
* ��ʷ��¼ :
* �汾       ����          ����        ����
*  1.0       2008-11-14    buxj        1������
*  1.1       2010-11-22    maomh	   1�����LINUX��ص����Ͷ���
**********************************************************************/
#ifndef __ADAE_H__
#define __ADAE_H__


#include "smee.h"


/****************************C�����ض��壬Ϊ�˱��ּ���************************************/
typedef		SMEE_INT32              ADAE_INT32;
typedef		SMEE_INT64              ADAE_INT64;
typedef		SMEE_FLOAT              ADAE_DOUBLE32;
typedef		SMEE_DOUBLE             ADAE_DOUBLE64;
typedef		SMEE_UINT16             ADAE_UINT16;
typedef		SMEE_UINT32             ADAE_UINT32;
typedef		SMEE_UINT8              ADAE_BYTE;
typedef		SMEE_LPVOID             ADAE_PVOID;
typedef		SMEE_UINT32             ADAE_SIZE;
typedef		SMEE_INT32              ADAE_KEY;
typedef		SMEE_INT32              ADAE_GID;             //process group id
typedef		SMEE_INT32              ADAE_MODE;            //file perms
typedef		unsigned long           ADAE_ULONG32;
typedef		char*                   ADAE_STRING;
typedef		long                    ADAE_LONG;
typedef		ADAE_LONG               ADAE_OFF;             //offset
typedef		ADAE_LONG               ADAE_TIME_T;          //time_t


/********************************ϵͳ���Ͷ���*********************************************/
#if     TARGET_OS == WIN_OS
        typedef ADAE_ULONG32           ADAE_TIMER_ID;
        typedef ADAE_PVOID             ADAE_HANDLE;
        typedef ADAE_HANDLE            ADAE_TID;
        typedef ADAE_INT32             ADAE_FD;
        typedef ADAE_UINT32            ADAE_SOCKET;
        typedef ADAE_ULONG32           ADAE_PID;
        typedef ADAE_HANDLE            ADAE_SEM_ID;

#elif   TARGET_OS == SUN_OS 
        typedef ADAE_INT32             ADAE_TIMER_ID;
        typedef ADAE_UINT32            ADAE_TID;
        typedef ADAE_INT32             ADAE_HANDLE;
        typedef ADAE_INT32             ADAE_FD;
        typedef ADAE_INT32             ADAE_SOCKET;
        typedef ADAE_INT32             ADAE_PID;
        typedef ADAE_INT32             ADAE_SEM_ID; 

#elif   TARGET_OS == VXWORKS_OS
        typedef ADAE_PVOID             ADAE_TIMER_ID;
        typedef ADAE_UINT32            ADAE_TID;
        typedef ADAE_INT32             ADAE_HANDLE;
        typedef ADAE_INT32             ADAE_FD;
        typedef ADAE_INT32             ADAE_SOCKET;
        typedef ADAE_INT32             ADAE_PID;
        typedef ADAE_PVOID             ADAE_SEM_ID;   

#elif   TARGET_OS == LINUX_OS 
        typedef ADAE_PVOID             ADAE_TIMER_ID;
        typedef ADAE_ULONG32           ADAE_TID;
        typedef ADAE_INT32             ADAE_HANDLE;
        typedef ADAE_INT32             ADAE_FD;
        typedef ADAE_INT32             ADAE_SOCKET;
        typedef ADAE_INT32             ADAE_PID;
        typedef ADAE_INT32             ADAE_SEM_ID; 
#endif


/*********************************������ЧID����******************************************/
#if     TARGET_OS == WIN_OS
        #define ADAE_INVALID_PID        (NULL)
		#define ADAE_INVALID_SEM_ID     (ADAE_SEM_ID)(0)
		#define ADAE_INVALID_SHM_ID     (NULL)
		#define ADAE_INVALLD_TID        (NULL)
		#define ADAE_INVALID_SOCKET     (ADAE_UINT32)(~0)
		#define ADAE_INVALID_TIMER_ID   (ADAE_UINT32)(~0)       //ADAE_TIMER_ID��unsigned long, ��֮�ȽϵĲ�Ӧ���Ǹ���
		#define ADAE_INVALID_FD         (NULL)
		#define ADAE_MAX_FILENAME_SIZE  (256)

#elif   TARGET_OS == SUN_OS
		#define ADAE_INVALID_PID        (-1)
		#define ADAE_INVALID_SEM_ID     (-1)      
		#define ADAE_INVALID_SHM_ID     (-1)
		#define ADAE_INVALLD_TID        (ADAE_UINT32)(~0)
		#define ADAE_INVALID_SOCKET     (int)(-1)
		#define ADAE_INVALID_TIMER_ID   (-1)
		#define ADAE_INVALID_FD         (-1)

#elif	TARGET_OS == VXWORKS_OS
		#define ADAE_INVALID_PID        (-1)
		#define ADAE_INVALID_SEM_ID     (ADAE_SEM_ID)(0)
		#define ADAE_INVALID_SHM_ID     (-1)
		#define ADAE_INVALLD_TID        (ADAE_UINT32)(~0)
		#define ADAE_INVALID_SOCKET     (int)(-1)
		#define ADAE_INVALID_TIMER_ID   (NULL)
		#define ADAE_INVALID_FD         (-1)

#elif	TARGET_OS == LINUX_OS
		#define ADAE_INVALID_PID        (-1)
		#define ADAE_INVALID_SEM_ID     (-1)      
		#define ADAE_INVALID_SHM_ID     (-1)
		#define ADAE_INVALLD_TID        (ADAE_UINT32)(~0)
		#define ADAE_INVALID_SOCKET     (int)(-1)
		#define ADAE_INVALID_TIMER_ID   (NULL)
		#define ADAE_INVALID_FD         (-1)
#endif


/***************************ʱ��ṹ�壬IO�Լ�TM��ģ��ʹ��***************************/
typedef struct {
    ADAE_LONG tm_sec;    //��
    ADAE_LONG tm_usec;   //΢��
} ADAE_TIME_VALUE;

typedef ADAE_TIME_VALUE ADAE_timestamp;   //ʱ���


/********************************IPC ��ض���****************************************/
#define ADAE_IPC_CREAT		(0001000)       /* create entry if key doesn't exist */
#define ADAE_IPC_EXCL		(0002000)       /* fail if key exists */
#define ADAE_SHM_R			(0400)          /* read permission */
#define ADAE_SHM_W			(0200)          /* write permission */


/*********************************�ļ����*******************************************/
/* 
 * file access flag--include IPC(sharememory��semaphore)��
 * file *include normal file��searial file��socket etc 
 */
#define ADAE_RD				(0x00)
#define ADAE_WR				(0x01)
#define ADAE_RDWR			(0x02)
#define ADAE_CREATE			(0x100)
#define ADAE_APPEND			(0x08)

/* 
 * file mode
 */
#define	ADAE_S_IRWXU		(0000700)		/* read, write, execute: owner */
#define	ADAE_S_IRUSR		(0000400)		/* read permission: owner */
#define	ADAE_S_IWUSR		(0000200)		/* write permission: owner */
#define	ADAE_S_IXUSR		(0000100)		/* execute permission: owner		*/
#define	ADAE_S_IRWXG		(0000070)		/* read, write, execute: group		*/
#define	ADAE_S_IRGRP		(0000040)		/* read permission: group		*/
#define	ADAE_S_IWGRP		(0000020)		/* write permission: group		*/
#define	ADAE_S_IXGRP		(0000010)		/* execute permission: group		*/
#define	ADAE_S_IRWXO		(0000007)		/* read, write, execute: other		*/
#define	ADAE_S_IROTH		(0000004)		/* read permission: other		*/
#define	ADAE_S_IWOTH		(0000002)		/* write permission: other		*/
#define	ADAE_S_IXOTH		(0000001)		/* execute permission: other	*/

/*
 * file state flag
 */
#define ADAE_R_OK			(04)
#define ADAE_W_OK			(02)
#define ADAE_X_OK			(01)
#define ADAE_F_OK			(00)


/***************************** Global FUNC Declare *******************************/
/*
 * �����ã���SMEE_DEBUGģʽ���������������
 */
SMEE_EXPORT void ADAE_debug(const char* format_msg,...);

/*
 * ���õ���־��¼��������־������־�ļ���
 */
SMEE_EXPORT void ADAE_logging(int iErcode, const char* fname, int line, 
							  const char* format_msg,...);


#endif  /* __ADAE_H__ */

