/*******************************************************************************
* Copyright (C) 2011, 上海微电子装备有限公司
* All rights reserved.
* 产品号 :   
* 所属组件 :
* 模块名称 :
* 文件名称 : smee_station.h
* 概要描述 : 该文件定义了工作站的机器类型
* 历史记录 :
* 版本      日期        作者    内容
* 1.0    2011-7-7      毛明辉   新建
* 1.1    2011-9-8      毛明辉   根据评审意见修改
* 1.2    2011-9-30     毛明辉   修改编码规范
* 1.3    2011-10-19    毛明辉   根据项目经理反馈意见修改
* 1.4    2011-12-06    毛明辉   根据部门经理反馈意见修改smee_machine.h改为smee_station.h
******************************************************************************/

#ifndef SMEE_STATION_H_
#define SMEE_STATION_H_

/*--------------------------------- 机器类型定义-----------------------------*/
/* 机器类型决定了使用CPU的指令集，该定义为不同平台编译的重要区别 */

/* 下面机器类型宏只能定义到Makefile中 */
/* 定义处理器类型 */
#define SMEE_SPARCB     0
#define SMEE_PPC        1
#define SMEE_X86_32     2
#define SMEE_SPARCB_64  3
#define SMEE_PPC_64     4
#define SMEE_X86_64     5

#define SMEE_SPARCB_32  SMEE_SPARCB
#define SMEE_PPC_32     SMEE_PPC


/*! \brief 
* \~chinese 如果未在Makefile中定义目标机类型，默认定义目标机为sparcb类型。
* \~english target Machine. */
#ifndef TARGET_MACHINE
/*NOTE!: PLEASE CHANGE THE DEFINATION VALUE TO YOUR PLATFORM*/
/*注意： 若不打算在Makefile里预定义，则必须确保此处定义与编译所在机器的类型完全匹配*/
#define TARGET_MACHINE  SMEE_SPARCB_32
#endif

/*编译宏*/
/* OS definition 操作系统定义, 对应COMPILE_OS宏*/
/* 操作系统决定了系统函数及类型的使用，该定义为不同平台编译的重要区别 */
#define SUN32_OS        0
#define VXWORKS32_OS    1
#define WIN32_OS        2
#define SUN64_OS        3
#define VXWORKS64_OS    4
#define WIN64_OS        5
#define LINUX32_OS      6
#define LINUX64_OS      7

/*! \brief
* \~chinese 如果未在Makefile中定义目标操作系统，默认定义为Solaris。
* \~english compile OS. */
#ifndef COMPILE_OS
/*NOTE!: PLEASE CHANGE THE DEFINATION VALUE TO YOUR PLATFORM*/
/*注意： 若不打算在Makefile里预定义，则必须确保此处定义与编译所在机器的类型完全匹配*/
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

/* 下面机器类型宏只能用于代码中 */
/*开发宏, 对应TARGET_OS宏*/
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
/* 如果目标机为sparcb或PPC，定义大字节顺序 */
#define SMEE_BIG_ENDIAN
#elif TARGET_MACHINE == SMEE_X86_32 ||  TARGET_MACHINE == SMEE_X86_64
/* 如果目标机为X86 32位机，定义小字节顺序 */
#define SMEE_LITTLE_ENDIAN
#endif

/* 
	为将来使用
	下面机器类型定义宏代码和Makefile中都可以定义 
*/
#define MASTER_MACHINE  1
#define SLAVE_MACHINE   0
/*! \brief 宏定义 主（1）从（0）机*/
#ifndef HOST_MACHINE
    #define HOST_MACHINE MASTER_MACHINE/*0*/
#endif


#endif
