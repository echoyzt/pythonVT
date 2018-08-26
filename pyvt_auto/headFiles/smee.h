/*******************************************************************************
* Copyright (C) 2011, 上海微电子装备有限公司
* All rights reserved.
* 产品号 :   
* 所属组件 :
* 模块名称 :
* 文件名称 : smee.h
* 概要描述 : 该文件总的包括了SMEE各方面通用类型定义。
* 历史记录 :
* 版本      日期        作者    内容
* 1.0    2011-7-7      毛明辉   新建
* 1.1    2011-9-8      毛明辉   根据评审意见修改
* 1.2    2011-9-30     毛明辉   修改编码规范
* 1.3    2011-10-19    毛明辉   根据项目经理反馈意见修改
* 1.4    2012-2-28     毛明辉   根据周金明的反馈意见增加宏IN、OUT以及INOUT的重复定义判断
******************************************************************************/
#ifndef SMEE_H_
#define SMEE_H_

#include "smee_station.h"
#include "smee_type.h"
#include "smee_unit.h"

/* 函数声明中用于表示输入参数 */
#ifndef IN 
    #define IN 
#endif
/* 函数声明中用于表示输出参数 */
#ifndef OUT 
    #define OUT
#endif 
/* 函数声明中用于表示既是输入又是输出参数 */
#ifndef INOUT
    #define INOUT
#endif


/*! 定义函数返回值OK */
#ifndef OK
    #define OK              0
#endif

/* 当未定义NULL时，定义NULL */
#ifndef NULL
    #define NULL        0
#endif

/* 获取当前的函数名*/
#if TARGET_OS == SUN32_OS || TARGET_OS == VXWORKS32_OS || TARGET_OS == SUN64_OS || TARGET_OS == VXWORKS64_OS || TARGET_OS == LINUX32_OS || TARGET_OS == LINUX64_OS
/* 定义统一的函数名宏 */
#ifdef __cplusplus
#define __SMEE_FUNC__  (char*)__PRETTY_FUNCTION__
#else
    #define __SMEE_FUNC__  (char*)__func__
#endif
#elif TARGET_OS == WIN32_OS || TARGET_OS == WIN64_OS
/* 定义统一的函数名宏 */
    #define __SMEE_FUNC__  __FUNCTION__
#endif


/* 接口函数限定符前缀 */
#if TARGET_OS == SUN32_OS || TARGET_OS == VXWORKS32_OS || TARGET_OS == SUN64_OS || TARGET_OS == VXWORKS64_OS || TARGET_OS == LINUX32_OS || TARGET_OS == LINUX64_OS
    #ifdef  __cplusplus
        #define SMEE_EXPORT extern "C"
    #else
    /*! \brief
    * \~chinese 当操作系统是SUN或VxWorks且编程语言为C时，定义外部接口的限定符。
    * \~english When OS is Solaris or VxWorks, and program language is C,
    define export directive as extern. */
        #define SMEE_EXPORT extern
    #endif

    #define SMEE_VAR_EXPORT 
#elif TARGET_OS == WIN32_OS || TARGET_OS == WIN64_OS
    #ifdef __cplusplus
        /*! \brief
        * \~chinese 当操作系统是WIN32且编程语言为C++时，定义外部接口的限定符。
        * \~english When OS is WIN32, and program language is C++, define export
        directive as extern "C" __declspec (dllexport). */
        #define SMEE_EXPORT extern "C" __declspec ( dllexport )
        #define SMEE_IMPORT extern "C" __declspec ( dllimport )
    #else
    /*! \brief
    * \~chinese 当操作系统是WIN32且编程语言为C+时，定义外部接口的限定符。
    * \~english When OS is WIN32, and program language is C, define export
    directive as __declspec (dllexport). */
        #define SMEE_EXPORT extern __declspec ( dllexport )
        #define SMEE_IMPORT extern __declspec ( dllimport )
    #endif

    #define SMEE_VAR_EXPORT __declspec ( dllexport )
#endif

#endif
