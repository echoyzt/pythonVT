/******************************************************************************
* Copyright (C) 2014, 上海微电子装备有限公司
* All rights reserved.
* 产品号 : SSB 530/10
* 所属组件 : EC
* 模块名称 : EC4T
* 文件名称 : EC4T_tc.h
* 概要描述 : EC组件外部接口数据定义
* 历史记录 : 
* 版本   日期        作者     内容
* 1.0    2014-08-18  王彦麟   新建。
******************************************************************************/

#ifndef EC4T_TC_H
#define EC4T_TC_H


///////////////////////////////////////////////////////////////////////////////
//                                头文件包含
///////////////////////////////////////////////////////////////////////////////

#include <smee.h>
#include <smee_project.h>


///////////////////////////////////////////////////////////////////////////////
//                                  宏定义
///////////////////////////////////////////////////////////////////////////////

/* 最大基板对准标记个数 */
#define EC4T_MAX_NR_SUBSTRATE_MARKS     50
#define EC4A_MAPPING_SCAN_NUM               40

///////////////////////////////////////////////////////////////////////////////
//                                 枚举定义
///////////////////////////////////////////////////////////////////////////////

/* 标记位置 */
typedef enum
{
    EC4T_MARK_LOCATION_MIN = 0,
    EC4T_MARK_LOCATION_WS_FIDUCIAL, /* 工件台基准版标记 */
    EC4T_MARK_LOCATION_SUBSTRATE,   /* 基板标记 */
    EC4T_MARK_LOCATION_MAX
} EC4T_MARK_LOCATION_ENUM;


///////////////////////////////////////////////////////////////////////////////
//                               数据结构定义
///////////////////////////////////////////////////////////////////////////////
typedef struct  
{
	xy_vect      RM1_pos; /*标记位置*/
	xy_vect      RM2_pos;
	SMEE_DOUBLE matching_rate;
	SMEE_CHAR template_file[EC4A_MAX_FILE_NAME_SIZE];     /* 掩模标记模板文件名 */
}EC4T_RETI_ALIGN_SPC_STRUCT;

typedef struct
{
    SMEE_BOOL do_auto_focus;                            /* 是否做自动调焦 */
    SMEE_BOOL perform_vert_compensation;             /* 对准补偿开关 */
    SMEE_DOUBLE vert_compensation;                   /* 对准垂向补偿量 */
    SMEE_DOUBLE matching_rate;                            /* 标记识别匹配度 */
	SMEE_CHAR template_file[EC4A_MAX_FILE_NAME_SIZE];     /* 标记模板文件名 */
} EC4T_WA_ALIGN_RECIPE_STRUCT;



/* 更新离轴基线的结果 */
typedef struct
{
    xy_vect aim_pos;    /* 硅片对准CCD目标位置 */
    SMEE_DOUBLE matching_rate;
} EC4T_UPDATE_WA_BASELINE_RESULT_STRUCT;


/* 更新同轴基线的结果 */
typedef struct
{
    SMEE_DOUBLE matching_rate_in_ccd; /* 同轴基准标记在CCD中的匹配度 */
    xy_vect mark_pos_in_ccd;     /* 同轴基准标记在CCD中的像素位置 */
} EC4T_UPDATE_TTL_BASELINE_RESULT_STRUCT;


/* 离轴对准结果 */
typedef struct
{
    xy_vect mark_pos_in_ccd;        /* 标记在CCD中的像素位置 */
    xy_vect mark_pos_in_wzcs;       /* 标记在WZCS下的位置 */
    SMEE_DOUBLE match_rate;         /* 标记匹配度 */
    xyrz_vect align_pos;            /* 标记对准位置 */
    xyrz_vect ws_meas_pos;          /* 工件台测量位置 */
    xy_vect mark_offset_in_wscs;    /* 标记位置偏移(WSCS) */
} EC4T_WA_ALIGN_RESULT_STRUCT;

/* 同轴标记识别处方 */
typedef struct
{
    SMEE_BOOL search_enabled;   /* 是否执行搜索 */
    SMEE_INT32 filler1;
    SMEE_DOUBLE matching_rate;  /* 标记识别匹配度 */
	SMEE_CHAR template_file[EC4A_MAX_FILE_NAME_SIZE];	  /* 标记模板文件名 */
} EC4T_ALIGN_RECIPE_STRUCT;

/* 同轴对准结果 */
typedef struct
{
    xy_vect mark_pos_in_ccd;        /* 标记在CCD中的像素位置 */
    xy_vect mark_pos_in_wzcs;       /* 标记在WZCS下的位置 */
    SMEE_DOUBLE match_rate;         /* 标记匹配度 */
    xyrz_vect align_pos;            /* 对准位置 */
    xyrz_vect rs_meas_pos;          /* 掩模台测量位置 */
    xyrz_vect ws_meas_pos;          /* 工件台测量位置 */
    xy_vect mark_offset_in_rzcs;    /* 标记位置偏移(RZCS) */
    xy_vect mark_offset_in_wscs;    /* 标记位置偏移(WSCS) */
} EC4T_TTL_ALIGN_RESULT_STRUCT;

typedef struct
{
    xy_vect sStartPos;
    xy_vect sEndPos;
    SMEE_UINT32 uiSpotValid;
    SMEE_INT32 ifiller;
}EC4T_SCAN_PARAM_STRUCT;

typedef struct
{
    SMEE_INT32 iScanNum;
    EC4T_SCAN_PARAM_STRUCT sScanRoute[EC4A_MAPPING_SCAN_NUM];
}EC4T_MAPPING_ROUTE_STRUCT;

#endif /* EC4T_TC_H */

