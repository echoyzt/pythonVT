/*******************************************************************************
* Copyright (C) 2011, �Ϻ�΢����װ�����޹�˾
* All rights reserved.
* ��Ʒ�� :   
* ������� :
* ģ������ :
* �ļ����� : smee_type.h
* ��Ҫ���� : ���ļ������˻���C/C++���ԵĻ�������
* ��ʷ��¼ :
* �汾      ����        ����    ����
* 1.0    2011-7-7      ë����   �½�
* 1.1    2011-9-8      ë����   ������������޸�
* 1.2    2011-9-30     ë����   �޸ı���淶
* 1.3    2011-10-19    ë����   ������Ŀ����������޸�
******************************************************************************/

#ifndef SMEE_TYPE_H_
#define SMEE_TYPE_H_

/*=============================================================================*/
/**
*  @����: 2009-11-26
*
*  @���¶��岻ͬ�������ĺ꣬���Ի������ͽ��з�װ��
*  
*
*  @�������͵ı߽�ֵ�������£�
*    - SMEE_CHAR_MIN
*    - SMEE_CHAR_MAX
*    - SMEE_UCHAR_MAX
*    - SMEE_SHRT_MIN
*    - SMEE_SHRT_MAX
*    - SMEE_USHRT_MAX
*    - SMEE_INT_MIN
*    - SMEE_INT_MAX
*    - SMEE_UINT_MAX
*    - SMEE_LONG_MIN
*    - SMEE_LONG_MAX
*    - SMEE_ULONG_MAX
*    - SMEE_LLONG_MIN
*    - SMEE_LLONG_MAX
*    - SMEE_ULLONG_MAX
*
*  @�������͵ĳߴ綨������:
*    - SMEE_SIZEOF_CHAR
*    - SMEE_SIZEOF_WCHAR
*    - SMEE_SIZEOF_SHORT
*    - SMEE_SIZEOF_INT
*    - SMEE_SIZEOF_LONG
*    - SMEE_SIZEOF_LONG_LONG
*    - SMEE_SIZEOF_VOID_P
*    - SMEE_SIZEOF_FLOAT
*    - SMEE_SIZEOF_DOUBLE
*    - SMEE_SIZEOF_LONG_DOUBLE
*
*   @�������ͷ�װ�������£�
*    - SMEE_USHORT16 (Ϊ�Ժ�ͳһʹ��  ����ʹ��SMEE_UINT16�����)
*    - SMEE_INT8
*    - SMEE_UINT8
*    - SMEE_INT16
*    - SMEE_UINT16
*    - SMEE_INT32
*    - SMEE_UINT32
*    - SMEE_INT64
*    - SMEE_UINT64
*
*
*/
/*=============================================================================*/
#include "smee_station.h"

#define SMEE_CHAR_BIT   8                   /* max # of bits in a ��char�� */
#define SMEE_CHAR_MIN   (-128)              /* min value of a ��signed char�� */
#define SMEE_CHAR_MAX   127                 /* max value of a ��signed char�� */
#define SMEE_SHRT_MIN   (-32768)            /* min value of a ��short int�� */
#define SMEE_SHRT_MAX   32767               /* max value of a ��short int�� */
#define SMEE_USHRT_MAX  65535               /* max value of ��unsigned short int�� */
#define SMEE_INT_MIN    (-2147483647-1)     /* min value of an ��int�� */
#define SMEE_INT_MAX    2147483647          /* max value of an ��int�� */
#define SMEE_UINT_MAX   4294967295U         /* max value of an ��unsigned int�� */
#define SMEE_LONG_MIN   (-2147483647L-1L)
#define SMEE_LONG_MAX   2147483647L         /* max value of a ��long int�� */
#define SMEE_ULONG_MAX  4294967295UL        /* max value of ��unsigned long int�� */
#define SMEE_LLONG_MIN  (-9223372036854775807LL-1LL)
#define SMEE_LLONG_MAX  9223372036854775807LL
#define SMEE_ULLONG_MAX 18446744073709551615ULL

#define SMEE_INT8_MAX (127)
#define SMEE_INT16_MAX (32767)
#define SMEE_INT32_MAX (2147483647)
#define SMEE_INT64_MAX (9223372036854775807LL)
#define SMEE_INT8_MIN (-128)
#define SMEE_INT16_MIN (-32767-1)
#define SMEE_INT32_MIN (-2147483647-1)
#define SMEE_INT64_MIN (-9223372036854775807LL-1)

#define SMEE_UINT8_MAX (255U)
#define SMEE_UINT16_MAX (65535U)
#define SMEE_UINT32_MAX (4294967295U)
#define SMEE_UINT64_MAX (18446744073709551615ULL)

#define  SMEE_SIZEOF_CHAR               1
#define  SMEE_SIZEOF_SHORT              2
#define  SMEE_SIZEOF_INT                4
#define  SMEE_SIZEOF_LLONG              8
#define  SMEE_SIZEOF_DOUBLE             8

#if TARGET_OS == SUN32_OS || TARGET_OS == VXWORKS32_OS
#define  SMEE_SIZEOF_LONG               4
#define  SMEE_SIZEOF_VOID_P             4
#elif TARGET_OS == SUN64_OS || TARGET_OS == VXWORKS64_OS
#define  SMEE_SIZEOF_LONG               8
#define  SMEE_SIZEOF_VOID_P             8
#endif

#if TARGET_MACHINE == SMEE_SPARCB_32 || TARGET_MACHINE == SMEE_SPARCB_64
#define  SMEE_SIZEOF_LONG_DOUBLE        16
#elif TARGET_MACHINE == SMEE_X86_32 || TARGET_MACHINE == SMEE_X86_64
#define  SMEE_SIZEOF_LONG_DOUBLE        12
#endif

typedef char                        SMEE_CHAR;
typedef char                        SMEE_INT8;
typedef unsigned char               SMEE_UINT8;
typedef short                       SMEE_INT16;
typedef unsigned short              SMEE_UINT16;
typedef int                         SMEE_INT32;
typedef unsigned int                SMEE_UINT32;
typedef long long                   SMEE_INT64;
typedef unsigned long long          SMEE_UINT64;
typedef float                       SMEE_FLOAT;
typedef double                      SMEE_DOUBLE;
typedef long double                 SMEE_LDOUBLE;
typedef unsigned long               SMEE_ULONG32;
typedef char*                       SMEE_STRING;
typedef long                        SMEE_LONG;
typedef void                        *SMEE_LPVOID;

typedef SMEE_UINT8                  SMEE_BYTE;
typedef SMEE_UINT32                 SMEE_SIZE;
typedef SMEE_INT32                  SMEE_KEY;
typedef SMEE_INT32                  SMEE_GID;//process group id
typedef SMEE_INT32                  SMEE_MODE;//file perms
typedef SMEE_LONG                   SMEE_OFF;//offset
typedef SMEE_LONG                   SMEE_TIME_T;//time_t

typedef SMEE_INT32 SMEE_BOOL;
#define SMEE_TRUE 1
#define SMEE_FALSE 0

/*
Ϊ��ʹ��ƽ̨��������ͳһ����������Ļ����꿪���⣬
���潫����һ��ȫ���Ժ꣬�����ƽ̨������ͬ�����Ʋ�ͬ��ϵͳ�����ͱ������ͣ�
�������ԱӦע�������д������ϸ�ʹ�����к궨�壬�����Ƿ�ͳһ��ϵͳ��������
*/

/* Other different in different platform */
#if TARGET_OS==WIN_OS
    typedef SMEE_ULONG32    SMEE_TIMER_ID;
    typedef SMEE_LPVOID     SMEE_HANDLE;
    typedef SMEE_HANDLE     SMEE_TID;
    typedef SMEE_HANDLE     SMEE_FD;
    typedef SMEE_UINT32     SMEE_SOCKET;
    typedef SMEE_HANDLE     SMEE_PID;
    typedef SMEE_HANDLE     SMEE_SEM_ID;
    typedef SMEE_INT32      SMEE_DWORD;
#elif   TARGET_OS==SUN_OS || TARGET_OS == LINUX_OS
    typedef SMEE_INT32      SMEE_TIMER_ID;
    typedef SMEE_UINT32     SMEE_TID;
    typedef SMEE_INT32      SMEE_HANDLE;
    typedef SMEE_INT32      SMEE_FD;
    typedef SMEE_INT32      SMEE_SOCKET;
    typedef SMEE_INT32      SMEE_PID;
    typedef SMEE_INT32      SMEE_SEM_ID; 
    typedef SMEE_INT32      SMEE_DWORD;
#elif   TARGET_OS==VXWORKS_OS
    typedef SMEE_LPVOID     SMEE_TIMER_ID;
    typedef SMEE_UINT32     SMEE_TID;
    typedef SMEE_INT32      SMEE_HANDLE;
    typedef SMEE_INT32      SMEE_FD;
    typedef SMEE_INT32      SMEE_SOCKET;
    typedef SMEE_INT32      SMEE_PID;
    typedef SMEE_LPVOID     SMEE_SEM_ID;
    typedef SMEE_INT32      SMEE_DWORD;
#endif

#if TARGET_OS==WIN_OS
    #define SMEE_INVALID_PID        NULL
    #define SMEE_INVALID_SEM_ID     (SMEE_SEM_ID)0
    #define SMEE_INVALID_SHM_ID     NULL
    #define SMEE_INVALLD_TID        NULL
    #define SMEE_INVALID_SOCKET     SMEE_UINT32(~0)
    #define SMEE_INVALID_TIMER_ID   (SMEE_INT32)(-1)
    #define SMEE_INVALID_FD         NULL
    #define SMEE_INVALID_HANDLE_VALUE (SMEE_INT32)(-1)
#elif TARGET_OS==SUN_OS || TARGET_OS == LINUX_OS
    #define SMEE_INVALID_PID        (SMEE_INT32)(-1)
    #define SMEE_INVALID_SEM_ID     (SMEE_INT32)(-1)     
    #define SMEE_INVALID_SHM_ID     (SMEE_INT32)(-1)
    #define SMEE_INVALLD_TID        SMEE_UINT32(~0)
    #define SMEE_INVALID_SOCKET     (SMEE_INT32)(-1)
    #define SMEE_INVALID_TIMER_ID   (SMEE_INT32)(-1)
    #define SMEE_INVALID_FD         (SMEE_INT32)(-1)
    #define SMEE_INVALID_HANDLE_VALUE (SMEE_INT32)(-1)
#elif TARGET_OS==VXWORKS_OS
    #define SMEE_INVALID_PID        (SMEE_INT32)(-1)
    #define SMEE_INVALID_SEM_ID     (SMEE_SEM_ID)0
    #define SMEE_INVALID_SHM_ID     (SMEE_INT32)(-1)
    #define SMEE_INVALLD_TID        SMEE_UINT32(~0)
    #define SMEE_INVALID_SOCKET     (SMEE_INT32)(-1)
    #define SMEE_INVALID_TIMER_ID   NULL
    #define SMEE_INVALID_FD         (SMEE_INT32)(-1)
    #define SMEE_INVALID_HANDLE_VALUE (SMEE_INT32)(-1)
#endif

#define SMEE_SOCKET_ERROR ((SMEE_INT32)-1)
#define SMEE_WAIT_FOREVER ((SMEE_INT32)-1)
#define SMEE_MAX_FILE_NAME_SIZE    0x80

/*---------------------------- ����������ݽṹ ----------------------------*/

/* XY ƽ���ڵ����� */
typedef struct
{
    SMEE_DOUBLE x;
    SMEE_DOUBLE y;
} xy_vect;

/* XZ ƽ���ڵ����� */
typedef struct
{
    SMEE_DOUBLE x;
    SMEE_DOUBLE z;
} xz_vect;

/* YZ ƽ���ڵ����� */
typedef struct
{
    SMEE_DOUBLE y;
    SMEE_DOUBLE z;
} yz_vect;

/* XYZ ��ά���� */
typedef struct
{
    SMEE_DOUBLE x;
    SMEE_DOUBLE y;
    SMEE_DOUBLE z;
} xyz_vect;

/* ZRxRy ���� */
typedef struct
{
    SMEE_DOUBLE z;
    SMEE_DOUBLE rx;
    SMEE_DOUBLE ry;
} zrxry_vect;

/* RxRy ���� */
typedef struct
{
    SMEE_DOUBLE rx;
    SMEE_DOUBLE ry;
} rxry_vect;

/* XYRz ���� */
typedef struct
{
    SMEE_DOUBLE x;
    SMEE_DOUBLE y;
    SMEE_DOUBLE rz;
} xyrz_vect;

/* XYRzZRxRy ���� */
typedef struct
{
    SMEE_DOUBLE x;
    SMEE_DOUBLE y;
    SMEE_DOUBLE rz;
    SMEE_DOUBLE z;
    SMEE_DOUBLE rx;
    SMEE_DOUBLE ry;
} xyrzzrxry_vect;


#endif
