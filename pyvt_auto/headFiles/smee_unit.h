/*******************************************************************************
* Copyright (C) 2011, 上海微电子装备有限公司
* All rights reserved.
* 产品号 :   
* 所属组件 :
* 模块名称 :
* 文件名称 : smee_unit.h
* 概要描述 : 该文件定义了基本单位类型及其单位转换。
* 历史记录 :
* 版本      日期        作者    内容
* 1.0    2011-7-7      毛明辉   新建
* 1.1    2011-9-8      毛明辉   根据评审意见修改
* 1.2    2011-9-30     毛明辉   修改编码规范
* 1.3    2011-10-19    毛明辉   根据项目经理反馈意见修改
* 1.4    2012-02-22    毛明辉   增加循环水流量单位为(L/MIN)
******************************************************************************/

#ifndef SMEE_UNIT_H_
#define SMEE_UNIT_H_

#include "smee_type.h"

/* PI */
#define SMEE_PI 3.1415926535897932385

/* 单位转换,SI表示国际单位 */
/* 长度单位*/
/* 米 <-> 皮米 */
#define SMEE_SI_TO_PM(v)  ( ((SMEE_LDOUBLE)(v)) * 1.0e12 )
#define SMEE_PM_TO_SI(v)  ( ((SMEE_LDOUBLE)(v)) * 1.0e-12 )

/* 米 <-> 纳米 */
#define SMEE_SI_TO_NM(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e9 )
#define SMEE_NM_TO_SI(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e-9 )

/* 米 <-> 微米 */
#define SMEE_SI_TO_UM(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e6 )
#define SMEE_UM_TO_SI(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e-6 )

/* 米 <-> 毫米 */
#define SMEE_SI_TO_MM(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e3 )
#define SMEE_MM_TO_SI(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e-3 )


/* 速度单位 */
/* 米/秒 <-> 纳米/毫秒 */
#define SMEE_SI_TO_NM_PER_MS(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e6 )
#define SMEE_NM_PER_MS_TO_SI(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e-6 )

/* 频率 */
/* 赫兹 <-> 千赫兹 */
#define SMEE_SI_TO_KHZ(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e-3 )
#define SMEE_KHZ_TO_SI(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e3 )

/* 赫兹 <-> 兆赫兹 */
#define SMEE_SI_TO_MHZ(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e-6 )
#define SMEE_MHZ_TO_SI(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e6 )



/* 角度单位 */
/* 弧度 <-> 毫弧度 */
#define SMEE_SI_TO_MRAD(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e3 )
#define SMEE_MRAD_TO_SI(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e-3 )

/* 弧度 <-> 微弧度 */
#define SMEE_SI_TO_URAD(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e6 )
#define SMEE_URAD_TO_SI(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e-6 )

/* 弧度 <-> 纳弧度 */
#define SMEE_SI_TO_NRAD(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e9 )
#define SMEE_NRAD_TO_SI(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e-9 )

/* 弧度 <-> 度 */
#define SMEE_SI_TO_DEGREE(v)  ( ((SMEE_DOUBLE)(v)) * 180.0 / SMEE_PI )
#define SMEE_DEGREE_TO_SI(v)  ( ((SMEE_DOUBLE)(v)) * SMEE_PI / 180.0 )



/* 能量单位 */
/* 焦耳Joules <-> uJoules */
#define SMEE_SI_TO_UJ(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e6 )
#define SMEE_UJ_TO_SI(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e-6 )

/* 焦耳/平方米 <-> 毫焦/平方厘米 */
#define SMEE_SI_TO_MJCM(v)  ( ((SMEE_DOUBLE)(v)) * 0.1 )
#define SMEE_MJCM_TO_SI(v)  ( ((SMEE_DOUBLE)(v)) * 10.0 )

/* 瓦/平方米 <-> 毫瓦/平方厘米 */
#define SMEE_SI_TO_MWCM(v)  ( ((SMEE_DOUBLE)(v)) * 0.1 )
#define SMEE_MWCM_TO_SI(v)  ( ((SMEE_DOUBLE)(v)) * 10.0 )



/* 温度单位 */
/* K <-> Celsius摄氏 */
#define SMEE_SI_TO_CELSIUS(v)  ( ((SMEE_DOUBLE)(v)) - 273.15 )
#define SMEE_CELSIUS_TO_SI(v)  ( ((SMEE_DOUBLE)(v)) + 273.15 )



/* 时间单位 */
/* 秒 <-> 毫秒 */
#define SMEE_SI_TO_MS(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e3 )
#define SMEE_MS_TO_SI(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e-3 )

/* 秒 <-> 微秒 */
#define SMEE_SI_TO_US(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e6 )
#define SMEE_US_TO_SI(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e-6 )

/* 秒 <-> 分钟 */
#define SMEE_SI_TO_MINUTE(v)  ( ((SMEE_DOUBLE)(v)) / 60.0 )
#define SMEE_MINUTE_TO_SI(v)  ( ((SMEE_DOUBLE)(v)) * 60.0 )

/* 秒 <-> 小时 */
#define SMEE_SI_TO_HOUR(v)  ( ((SMEE_DOUBLE)(v)) / 3600.0 )
#define SMEE_HOUR_TO_SI(v)  ( ((SMEE_DOUBLE)(v)) * 3600.0 )

/* 秒 <-> 天 */
#define SMEE_SI_TO_DAY(v)  ( ((SMEE_DOUBLE)(v)) / 86400.0 )
#define SMEE_DAY_TO_SI(v)  ( ((SMEE_DOUBLE)(v)) * 86400.0 )


/* 压力单位 */
/* 帕斯卡 <-> BAR */
#define SMEE_SI_TO_BAR(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e-5 )
#define SMEE_BAR_TO_SI(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e5 )

/* 帕斯卡 <-> PSI */
#define SMEE_SI_TO_PSI(v)  ( ((SMEE_DOUBLE)(v)) * 145.0 * 1.0e-6 )
#define SMEE_PSI_TO_SI(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e6 / 145.0 )


/* 1 <-> ppm */
#define SMEE_SI_TO_PPM(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e6 )
#define SMEE_PPM_TO_SI(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e-6 )


/* 1 <-> %, 百分比 */
#define SMEE_SI_TO_PCT(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e2 )
#define SMEE_PCT_TO_SI(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e-2 )

/*循环水流量单位为(L/MIN),*/
/* 立方米/秒 <-> 升/每分钟 */
#define SMEE_SI_TO_LPM(v)   ( ((SMEE_DOUBLE)(v)) * 1.0e3 * 60.0)      
#define SMEE_LPM_TO_SI(v)   ( ((SMEE_DOUBLE)(v)) * 1.0e-3 / 60.0)

#endif
