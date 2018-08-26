/*******************************************************************************
* Copyright (C) 2011, �Ϻ�΢����װ�����޹�˾
* All rights reserved.
* ��Ʒ�� :   
* ������� :
* ģ������ :
* �ļ����� : smee_station.h
* ��Ҫ���� : ���ļ������˹���վ�Ļ�������
* ��ʷ��¼ :
* �汾      ����        ����    ����
* 1.0    2011-7-7      ë����   �½�
* 1.1    2011-9-8      ë����   ������������޸�
* 1.2    2011-9-30     ë����   �޸ı���淶
* 1.3    2011-10-19    ë����   ������Ŀ����������޸�
* 1.4    2011-12-06    ë����   ���ݲ��ž���������޸�smee_machine.h��Ϊsmee_station.h
******************************************************************************/

#ifndef SMEE_STATION_H_
#define SMEE_STATION_H_

/*--------------------------------- �������Ͷ���-----------------------------*/
/* �������;�����ʹ��CPU��ָ����ö���Ϊ��ͬƽ̨�������Ҫ���� */

/* ����������ͺ�ֻ�ܶ��嵽Makefile�� */
/* ���崦�������� */
#define SMEE_SPARCB     0
#define SMEE_PPC        1
#define SMEE_X86_32     2
#define SMEE_SPARCB_64  3
#define SMEE_PPC_64     4
#define SMEE_X86_64     5

#define SMEE_SPARCB_32  SMEE_SPARCB
#define SMEE_PPC_32     SMEE_PPC


/*! \brief 
* \~chinese ���δ��Makefile�ж���Ŀ������ͣ�Ĭ�϶���Ŀ���Ϊsparcb���͡�
* \~english target Machine. */
#ifndef TARGET_MACHINE
/*NOTE!: PLEASE CHANGE THE DEFINATION VALUE TO YOUR PLATFORM*/
/*ע�⣺ ����������Makefile��Ԥ���壬�����ȷ���˴�������������ڻ�����������ȫƥ��*/
#define TARGET_MACHINE  SMEE_SPARCB_32
#endif

/*�����*/
/* OS definition ����ϵͳ����, ��ӦCOMPILE_OS��*/
/* ����ϵͳ������ϵͳ���������͵�ʹ�ã��ö���Ϊ��ͬƽ̨�������Ҫ���� */
#define SUN32_OS        0
#define VXWORKS32_OS    1
#define WIN32_OS        2
#define SUN64_OS        3
#define VXWORKS64_OS    4
#define WIN64_OS        5
#define LINUX32_OS      6
#define LINUX64_OS      7

/*! \brief
* \~chinese ���δ��Makefile�ж���Ŀ�����ϵͳ��Ĭ�϶���ΪSolaris��
* \~english compile OS. */
#ifndef COMPILE_OS
/*NOTE!: PLEASE CHANGE THE DEFINATION VALUE TO YOUR PLATFORM*/
/*ע�⣺ ����������Makefile��Ԥ���壬�����ȷ���˴�������������ڻ�����������ȫƥ��*/
#define COMPILE_OS SUN32_OS
#endif

/*Checking between Macro TARGET_MACHINE and COMPILE_OS*/
#if TARGET_MACHINE == SMEE_PPC && COMPILE_OS != VXWORKS32_OS
    #error "TARGET_MACHINE(SMEE_PPC) must match COMPILE_OS(VXWORKS32_OS)."
#elif TARGET_MACHINE == SMEE_PPC_64 && (COMPILE_OS != VXWORKS32_OS || COMPILE_OS != VXWORKS64_OS)
    #error "TARGET_MACHINE(SMEE_PPC_64) must match COMPILE_OS(VXWORKS32_OS or VXWORKS64_OS)."
#elif TARGET_MACHINE == SMEE_SPARCB && COMPILE_OS != SUN32_OS
    #error "TARGET_MACHINE(SMEE_SPARCB) must match COMPILE_OS(SUN32_OS)."
#elif TARGET_MACHINE == SMEE_SPARCB_64 && (COMPILE_OS != SUN32_OS || COMPILE_OS != SUN64_OS)
    #error "The TARGET_MACHINE(SMEE_SPARCB_64) must match COMPILE_OS(SUN32_OS or SUN64_OS)."
#endif

/* ����������ͺ�ֻ�����ڴ����� */
/*������, ��ӦTARGET_OS��*/
#define  SUN_OS         0
#define  VXWORKS_OS     1
#define  WIN_OS         2
#define  LINUX_OS       3

#if COMPILE_OS == SUN32_OS || COMPILE_OS == SUN64_OS
#define TARGET_OS SUN_OS
#elif COMPILE_OS == VXWORKS32_OS || COMPILE_OS == VXWORKS64_OS
#define TARGET_OS VXWORKS_OS
#elif COMPILE_OS == WIN32_OS || COMPILE_OS == WIN64_OS
#define TARGET_OS WIN_OS
#elif COMPILE_OS == LINUX32_OS || COMPILE_OS == LINUX64_OS
#define TARGET_OS LINUX_OS
#endif

#if TARGET_MACHINE == SMEE_SPARCB_32 || TARGET_MACHINE == SMEE_PPC_32 || TARGET_MACHINE == SMEE_SPARCB_64 || TARGET_MACHINE == SMEE_PPC_64
/* ���Ŀ���Ϊsparcb��PPC��������ֽ�˳�� */
#define SMEE_BIG_ENDIAN
#elif TARGET_MACHINE == SMEE_X86_32 ||  TARGET_MACHINE == SMEE_X86_64
/* ���Ŀ���ΪX86 32λ��������С�ֽ�˳�� */
#define SMEE_LITTLE_ENDIAN
#endif

/* 
	Ϊ����ʹ��
	����������Ͷ��������Makefile�ж����Զ��� 
*/
#define MASTER_MACHINE  1
#define SLAVE_MACHINE   0
/*! \brief �궨�� ����1���ӣ�0����*/
#ifndef HOST_MACHINE
    #define HOST_MACHINE MASTER_MACHINE/*0*/
#endif


#endif
