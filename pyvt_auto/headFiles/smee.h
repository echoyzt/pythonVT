/*******************************************************************************
* Copyright (C) 2011, �Ϻ�΢����װ�����޹�˾
* All rights reserved.
* ��Ʒ�� :   
* ������� :
* ģ������ :
* �ļ����� : smee.h
* ��Ҫ���� : ���ļ��ܵİ�����SMEE������ͨ�����Ͷ��塣
* ��ʷ��¼ :
* �汾      ����        ����    ����
* 1.0    2011-7-7      ë����   �½�
* 1.1    2011-9-8      ë����   ������������޸�
* 1.2    2011-9-30     ë����   �޸ı���淶
* 1.3    2011-10-19    ë����   ������Ŀ����������޸�
* 1.4    2012-2-28     ë����   �����ܽ����ķ���������Ӻ�IN��OUT�Լ�INOUT���ظ������ж�
******************************************************************************/
#ifndef SMEE_H_
#define SMEE_H_

#include "smee_station.h"
#include "smee_type.h"
#include "smee_unit.h"

/* �������������ڱ�ʾ������� */
#ifndef IN 
    #define IN 
#endif
/* �������������ڱ�ʾ������� */
#ifndef OUT 
    #define OUT
#endif 
/* �������������ڱ�ʾ������������������� */
#ifndef INOUT
    #define INOUT
#endif


/*! ���庯������ֵOK */
#ifndef OK
    #define OK              0
#endif

/* ��δ����NULLʱ������NULL */
#ifndef NULL
    #define NULL        0
#endif

/* ��ȡ��ǰ�ĺ�����*/
#if TARGET_OS == SUN32_OS || TARGET_OS == VXWORKS32_OS || TARGET_OS == SUN64_OS || TARGET_OS == VXWORKS64_OS || TARGET_OS == LINUX32_OS || TARGET_OS == LINUX64_OS
/* ����ͳһ�ĺ������� */
#ifdef __cplusplus
#define __SMEE_FUNC__  (char*)__PRETTY_FUNCTION__
#else
    #define __SMEE_FUNC__  (char*)__func__
#endif
#elif TARGET_OS == WIN32_OS || TARGET_OS == WIN64_OS
/* ����ͳһ�ĺ������� */
    #define __SMEE_FUNC__  __FUNCTION__
#endif


/* �ӿں����޶���ǰ׺ */
#if TARGET_OS == SUN32_OS || TARGET_OS == VXWORKS32_OS || TARGET_OS == SUN64_OS || TARGET_OS == VXWORKS64_OS || TARGET_OS == LINUX32_OS || TARGET_OS == LINUX64_OS
    #ifdef  __cplusplus
        #define SMEE_EXPORT extern "C"
    #else
    /*! \brief
    * \~chinese ������ϵͳ��SUN��VxWorks�ұ������ΪCʱ�������ⲿ�ӿڵ��޶�����
    * \~english When OS is Solaris or VxWorks, and program language is C,
    define export directive as extern. */
        #define SMEE_EXPORT extern
    #endif

    #define SMEE_VAR_EXPORT 
#elif TARGET_OS == WIN32_OS || TARGET_OS == WIN64_OS
    #ifdef __cplusplus
        /*! \brief
        * \~chinese ������ϵͳ��WIN32�ұ������ΪC++ʱ�������ⲿ�ӿڵ��޶�����
        * \~english When OS is WIN32, and program language is C++, define export
        directive as extern "C" __declspec (dllexport). */
        #define SMEE_EXPORT extern "C" __declspec ( dllexport )
        #define SMEE_IMPORT extern "C" __declspec ( dllimport )
    #else
    /*! \brief
    * \~chinese ������ϵͳ��WIN32�ұ������ΪC+ʱ�������ⲿ�ӿڵ��޶�����
    * \~english When OS is WIN32, and program language is C, define export
    directive as __declspec (dllexport). */
        #define SMEE_EXPORT extern __declspec ( dllexport )
        #define SMEE_IMPORT extern __declspec ( dllimport )
    #endif

    #define SMEE_VAR_EXPORT __declspec ( dllexport )
#endif

#endif
