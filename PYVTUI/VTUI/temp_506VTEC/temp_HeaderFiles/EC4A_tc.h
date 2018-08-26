/******************************************************************************
* Copyright (C) 2014, 上海微电子装备有限公司
* All rights reserved.
* 产品号 : SSB 530/10
* 所属组件 : EC
* 模块名称 : EC4A
* 文件名称 : EC4A_tc.h
* 概要描述 : EC组件外部接口数据定义
* 历史记录 :
* 版本   日期        作者     内容
* 1.0    2014-08-18  王彦麟   新建。
******************************************************************************/

#ifndef EC4A_TC_H
#define EC4A_TC_H


///////////////////////////////////////////////////////////////////////////////
//                                头文件包含
///////////////////////////////////////////////////////////////////////////////

#include <ADAE.h>
#include <smee.h>
#include <smee_project.h>


///////////////////////////////////////////////////////////////////////////////
//                                错误码定义
///////////////////////////////////////////////////////////////////////////////

/* <ErrBegin> */

/* EC进程出现异常错误 */
#define  EC4A_SYSTEM_ERROR          0x45430100

/* 参数错误 */
#define  EC4A_PARAMETER_ERROR       0x45430101

/* 非法调用错误 */
#define  EC4A_ILLEGAL_CALL_ERROR    0x45430102

/* 重试错误 */
#define  EC4A_RETRY_ERROR    0x45430103


/* <ErrEnd> */


///////////////////////////////////////////////////////////////////////////////
//                                  宏定义
///////////////////////////////////////////////////////////////////////////////

/* 图像 ID 名称的最长个数 */
#define EC4A_IMAGE_ID_LEN           MAX_IMAGE_ID

/* 一个lot中最多的图像个数 */
#define EC4A_MAX_IMAGES_NR          MAX_IMG_NR_PER_LOT

/* 曝光场最大个数 */
#define EC4A_MAX_EXPOSURES_NR       MAX_FLD_NR_PER_IMG

/* 掩模 ID 长度 */
#define EC4A_MAX_RETICLE_ID         MAX_RETICLE_ID

/* 带相对路径文件名长度限制，包括结尾的'\0' */
#define EC4A_MAX_FILE_NAME_SIZE     0x80

/* 工件全场对准最大标记数，需要和 AL 同步 */
#define EC4A_MAX_ALIGN_MARK         MAX_WAFER_MARK_NUM

/* 最大区域个数 */
#define EC4A_MAX_NR_ZONES           9

/* 每个区域最大标记个数 */
#define EC4A_MAX_MARK_NR_PER_ZONE     12

/*每个区域最大曝光场个数*/
#define EC4A_MAX_EXPOSURE_NR_PER_ZONE     12

/* 栅格多项式系数个数 */
#define EC4A_NR_GRID_COEFS          10

/* EC消息长度,包括结尾的'\0 */
#define EC4A_MAX_MSG_SIZE  0x200

#define EC4A_RETICLE_MARKS_NUM 2

#define EC4A_MAX_UPDATE_BASELINE_NUM 3

///////////////////////////////////////////////////////////////////////////////
//                                 枚举定义
///////////////////////////////////////////////////////////////////////////////


/* 调平模式枚举 */
typedef enum
{
    EC4A_LEVEL_MODE_MIN = 0,
    EC4A_LEVEL_MODE_GLOBAL,            /* 全场调焦调平 */
    EC4A_LEVEL_MODE_GLOBAL_FLS,        /* 全场调焦逐场调平 */
    EC4A_LEVEL_MODE_FLS,               /* 逐场调焦调平 */
    EC4A_LEVEL_MODE_MAPPING,           /* Mapping */
    EC4A_LEVEL_MODE_SIMPLE_MAPPING,    /* Simple Mapping */
    EC4A_LEVEL_MODE_MAX
} EC4A_LEVEL_MODE_ENUM;


/* 路径规划设置 */
typedef enum
{
    EC4A_CALC_ROUTE_OPT_MIN = 0,
    EC4A_CALC_ROUTE_OPT_CUSTOM,     /* 用户指定 */
    EC4A_CALC_ROUTE_OPT_STANDARD,   /* 标准路径 */
    EC4A_CALC_ROUTE_OPT_OPTIMIZE,   /* 优化路径 */
    EC4A_CALC_ROUTE_OPT_MAX
} EC4A_CALC_ROUTE_OPT_ENUM;


/* 工件全场精对准要求 */
typedef enum
{
    EC4A_FIWA_REQ_MIN = 0,
    EC4A_FIWA_REQ_PRECISION_PREFERED,   /* 精度优先，所有标记对准成功 */
    EC4A_FIWA_REQ_ROBUST_PREFERED,      /* 容错优先，3个或以上标记识别成功 */
    EC4A_FIWA_REQ_BALANCED,             /* 两者兼顾，标记个数/2，或3个以上标记识别成功，取二者的最大值 */
	EC4A_FIWA_REQ_USER_DEFINE, 			/* 用户自定义*/
	EC4A_FIWA_REQ_MAX
} EC4A_FINE_SUBSTRATE_ALIGN_REQ_ENUM;


/* 工件对准方法 */
typedef enum
{
    EC4A_WA_METHOD_MIN = 0,
    EC4A_WA_METHOD_GLOBAL,           /* 全场对准 */
    EC4A_WA_METHOD_HYBRID,           /* 混合对准 */
    EC4A_WA_METHOD_MAX
} EC4A_WA_METHOD_ENUM;

/*  标记对准阶段枚举     */
typedef enum
{
    EC4A_ALIGNMENT_PHASE_MIN = 0, /* 枚举最小值 */
    EC4A_COARSE_AND_FINE_PHASE,   /* 粗对准和精对准阶段 */
    EC4A_COARSE_PHASE,            /* 粗对准阶段 */
    EC4A_FINE_PHASE,              /* 精对准阶段 */
    EC4A_ALIGNMENT_PHASE_MAX      /* 枚举最大值 */
} EC4A_ALIGNMENT_PHASE_ENUM;

typedef enum
{
    EC4A_AFBT_MIN = 0,
    EC4A_AFBT_ABORT_LOT, // 直接终止批生产
	EC4A_AFBT_REJECT_WAFER,// 硅片作废片处理
    EC4A_AFBT_MANUAL_ALIGN,//手动对准
    EC4A_AFBT_RETRY,//重试
    EC4A_AFBT_MAX
}EC4A_ALIGN_FAILE_LOT_TREAT_ENUM;// 对准失败后批处理策略

/* EC内部状态枚举 */
typedef enum
{
    EC4A_ST_STATUS_MIN = 0,
    EC4A_ST_STATUS_IDLE,            /* 空闲 */
    EC4A_ST_STATUS_TERMINATE,       /* 终止 */
    EC4A_ST_STATUS_START_LOT,       /* 开始批 */
    EC4A_ST_STATUS_START_SUBSTRATE, /* 开始工件 */
    EC4A_ST_STATUS_MAX
} EC4A_ST_STATUS_ENUM;


/* 离轴对准CCD */
typedef enum
{
    EC4A_OA_CCD_MIN = 0,
    EC4A_OA_CCD_FRONT,      /* 离轴对准正面CCD */
    EC4A_OA_CCD_BACK,       /* 离轴对准背面CCD */
    EC4A_OA_CCD_MAX
} EC4A_OA_CCD_ENUM;


typedef enum
{
    EC4A_FIELD_STATE_MIN = 0,
    EC4A_FIELD_NONE,   // 未处理
    EC4A_FIELD_EXPOSED,// 曝光成功
    EC4A_FIELD_FAILED, // 曝光失败
    EC4A_FIELD_STATE_MAX
}EC4A_FIELD_STATE_ENUM;// 曝光场状态信息

typedef enum
{
    EC4A_IMAGE_STATE_MIN = 0,
    EC4A_IMAGE_NONE,   // 图像未进行曝光操作
    EC4A_IMAGE_FULL,   // 图像完全曝光
    EC4A_IMAGE_FAILED, // 图像曝光失败
    EC4A_IMAGE_STATE_MAX
}EC4A_IMAGE_STATE_ENUM;// 硅片曝光状态信息

//滤波片工作模式enum
typedef enum
{
    EC4A_FILTER_MODE_MIN = 0,
    EC4A_FILTER_MODE_GHI,    //默认工作模式GHI三线
    EC4A_FILTER_MODE_GH,     //GH线工作模式
    EC4A_FILTER_MODE_I,      //I线工作模式
    EC4A_FILTER_MODE_MAX
}EC4A_FILTER_MODE_ENUM;

typedef enum
{
    EC4A_DOSE_CONTROL_MODE_MIN = 0,
    EC4A_DOSE_CONTROL_BY_TIME,  // 时间控制 by time
    EC4A_DOSE_CONTROL_BY_ENERGY,// 剂量控制 by energy
    EC4A_DOSE_CONTROL_MODE_MAX
}EC4A_DOSE_CONTROL_MODE_ENUM;// 曝光剂量控制模式

typedef enum
{
    EC4A_FINE_WAFER_ALIGN_MODE_MIN = 0,
    EC4A_FINE_BASIC_MODE,  // 基本模式 (basic mode)
    EC4A_FINE_ENHANCE_MODE,// 增强模式 (enhance mode)
    EC4A_FINE_WAFER_ALIGN_MODE_MAX
}EC4A_FINE_WAFER_ALIGN_MODE_ENUM; // 硅片全场精对准方式 fine wafer alignment

typedef enum
{
    EC4A_MARK_PREF_MIN = 0,
    EC4A_MARK_PREF_PREFERED,            /* 首选标记 */
    EC4A_MARK_PREF_BACKUP,              /* 备用标记 */
    EC4A_MARK_PREF_MAX
} EC4A_MARK_PREF_ENUM;

typedef enum
{
    EC4A_CHCK_WS_CHUCK_PARTICLE_MIN = 0,
    EC4A_NO_CHECK,            /* 不进行颗粒度检测*/
    EC4A_CHECK,              /* 检测，但是不一定弹出界面 */
	EC4A_FORCE_CHECK,        /* 检测，并且必须弹出界面 */
    EC4A_CHCK_WS_CHUCK_PARTICLE_MAX
} EC4A_CHECK_WS_CHUCK_PARTICLE_ENUM;

///////////////////////////////////////////////////////////////////////////////
//                                结构体定义
///////////////////////////////////////////////////////////////////////////////

/* EC内部状态结构体 */
typedef struct
{
    EC4A_ST_STATUS_ENUM status;  /* EC内部状态 */
    SMEE_INT32 filler1;
} EC4A_STATUS_STRUCT;


/* 硅片标记识别处方 */
typedef struct
{
    SMEE_BOOL do_auto_focus;                            /* 是否做自动调焦 */
    SMEE_BOOL perform_vert_compensation;             /* 对准补偿开关 */
    SMEE_DOUBLE vert_compensation;                   /* 对准垂向补偿量 */
	SMEE_BOOL specify_algorithm;						/* 是否指定对准算法 */
	SMEE_ALGORITHM_TYPE_ENUM algorithm_type;			 /* 算法类型 */
	SMEE_BOOL use_align_alg_param;						/* 是否使用用户自定义的算法高级参数 */
    SMEE_INT32 filler;
	SMEE_CHAR align_alg_param_file_name[SMEE_MAX_FILE_NAME_SIZE]; /* 算法高级参数文件名（不带路径，带扩展名） */
    SMEE_DOUBLE matching_rate;                            /* 标记识别匹配度 */
	SMEE_CHAR template_file[EC4A_MAX_FILE_NAME_SIZE];     /* 标记模板文件名 */
} EC4A_ALIGN_RECIPE_STRUCT;


typedef struct
{
    SMEE_INT32 mark_id;     /* 标记标识 */
    SMEE_INT32 zone_id;     /* 区域标识 */
	EC4A_ALIGNMENT_PHASE_ENUM   mark_align_usage; /*标记对准阶段*/
    EC4A_MARK_PREF_ENUM preference;/*标记优先属性*/
    xy_vect mark_position;  /* 标记位置 */
} EC4A_SUBSTRATE_MARK_DATA_STRUCT;

/*掩模标记数据*/
typedef struct  
{
	xy_vect RM1;//掩模标记1  
	xy_vect RM2;//掩模标记2
}EC4A_RETICLE_MARK_DATA_STRUCT; 

/* Interfield Correction 场间 */
typedef struct
{
    xy_vect translation;         /* 平移误差校正值 */
    SMEE_DOUBLE rotation;        /* 旋转角度误差校正值 */
    SMEE_DOUBLE magnification;   /* 放大倍率误校正值 */
    SMEE_DOUBLE asy_rotation;    /* 非对称旋转角度误差校正值 */
    SMEE_DOUBLE asy_magn;        /* 非对称放大倍率误差校正值 */
} EC4A_INTERFIELD_CORR_STRUCT;


/* 工件对准策略 */
typedef struct
{
	SMEE_ALIGN_TYPE_ENUM  WA_CCD_type;				/* 对准使用的CCD*/
	EC4A_OA_CCD_ENUM OA_CCD;						/*对准方向-正面 背面*/
	SMEE_BOOL is_matching_overlay;                      /* 是否是匹配套刻 */    
	SMEE_INT32 nr_of_valid_fWA_marks;		/*用户指定的精对准标记有效个数*/
	EC4A_ALIGN_FAILE_LOT_TREAT_ENUM  align_fail_lot_treat;/* 对准失败处理*/
	SMEE_BOOL is_force_mark_training;                   /* 是否强制标记模板学习 */
	SMEE_BOOL is_do_manual_align;                       /* 是否执行手动对准 */
	EC4A_FINE_SUBSTRATE_ALIGN_REQ_ENUM fWA_requirement;                 /* 工件全场精对准要求 */
	SMEE_INT32 nr_wafer_marks;                          /* 工件对准标记个数 */
    SMEE_BOOL perform_precise_wafer_alignment;   // 是否高精度硅片对准    
    EC4A_FINE_WAFER_ALIGN_MODE_ENUM fine_wafer_alignment;//硅片全场精对准方式 fine wafer alignment
    SMEE_BOOL adjust_mvs_brightness;                       /* 是否调整对准CCD电压 */
    SMEE_DOUBLE mvs_brightness;                            /* 对准CCD电压 */
	EC4A_SUBSTRATE_MARK_DATA_STRUCT wafer_marks[MAX_WAFER_MARK_NUM]; /* 工件对准标记 */
	EC4A_ALIGN_RECIPE_STRUCT coarse_mark_recipe;  /* 粗对准标记识别处方 */	
	EC4A_ALIGN_RECIPE_STRUCT fine_mark_recipe;  /* 精对准标记识别处方 */	
	EC4A_INTERFIELD_CORR_STRUCT layer_correction;            /* 层制造误差修正 */
} EC4A_ALIGN_STRATEGY_STRUCT;

typedef struct
{
    SMEE_BOOL filter_enable;            //滤波器使能
	SMEE_BOOL ina_enable;               //照明数值孔径使能
	SMEE_BOOL pna_enable;               //物镜NA 使能
    EC4A_FILTER_MODE_ENUM filter_mode;  //滤波器使能模式
    SMEE_DOUBLE ina_value;              //照明数值孔径数值
    SMEE_DOUBLE pna_value;              //物镜NA 值
}EC4A_ILLUMINATION_MODE_STRUCT;


/* 曝光数据 */
typedef struct
{
    SMEE_INT32 exposure_id;     /* 曝光场序号 */
    SMEE_INT32 zone_id;         /* 区域ID，仅用于HA对准 */
    SMEE_DOUBLE dose;           /* 曝光剂量 */
    zrxry_vect focus_offset;    /* 场离焦量位置 */
    xy_vect field_position;           /* 场在工件上的位置 */
} EC4A_EXPOSURE_DATA_STRUCT;

typedef struct  
{
    SMEE_INT32   nr_of_marks; /*标记个数*/
    SMEE_INT32   filler;
    SMEE_UINT32   mark_id[EC4A_MAX_ALIGN_MARK]; /*标记索引*/
}EC4A_MARK_INDEX_STRUCT;

typedef struct
{
    SMEE_INT32 zone_id;     /* 区域标识（与 Index 相同） */
	SMEE_INT32 filler;
    xy_vect zone_center;            /* 区域位置（中心点坐标） */
    xy_vect zone_size;           /* 区域尺寸 */
    EC4A_MARK_INDEX_STRUCT zone_marks;
} EC4A_ZONE_ALIGN_STRUCT;


/* 图像数据 */
typedef struct
{
    SMEE_CHAR image_id[EC4A_IMAGE_ID_LEN];                  /* Image ID */
    
    /* (整数0-9，大写字母A-Z,以及7个特殊字符% + / $ .-以及空格，长度【12-64】 位不含结束符 ) */
    SMEE_CHAR reticle_id[EC4A_MAX_RETICLE_ID];              /* Reticle ID ( 掩模版标识 ) */
    xy_vect image_center;                                   /* 图像中心在掩模上的位置 */
    xy_vect image_size;                                     /* 图像大小 (wafer level) */
    xy_vect image_shift;                                    /* 图像平移 */
    SMEE_BOOL specify_mask_win;             /* 是否由用户指定 Mask Window */
    SMEE_INT32 filler;
    xy_vect win_size;                                       /* VS窗口大小 */
    xy_vect win_center;                                     /* VS窗口中心 */
    SMEE_DOUBLE reticle_trans_factor;                       /* 掩模透过率 */
    xyrz_vect reticle_pre_align_offset;                     /*掩模上片偏差*/
	EC4A_RETICLE_MARK_DATA_STRUCT reticle_marks;				/*掩模标记位置*/
    EC4A_CALC_ROUTE_OPT_ENUM calc_option;                   /* 路径规划方式 */
    EC4A_DOSE_CONTROL_MODE_ENUM dose_mode;					/*剂量控制模式*/
    SMEE_UINT32 nr_zones;                               /* 区域个数 */
    SMEE_INT32 nr_of_exposures;                             /* 曝光场数 */
    EC4A_ZONE_ALIGN_STRUCT zones[EC4A_MAX_NR_ZONES];          /* 区域数据 */
    EC4A_EXPOSURE_DATA_STRUCT exposure[EC4A_MAX_EXPOSURES_NR];   /* 工件上曝光场的详细描述 */
} EC4A_IMAGE_DATA_STRUCT;


/* EC的lot数据 */
typedef struct
{
    SMEE_INT32 lot_id;                      /* lot的id */
    SMEE_BOOL alignment_optimize;          /* 对准优化 */
    SMEE_BOOL global_level_optimize;       /* 全局调平优化 */
	EC4A_CHECK_WS_CHUCK_PARTICLE_ENUM check_WS_chuck_particle;		/*工件台颗粒度检测界面*/
	SMEE_DOUBLE global_lvl_base_angle;
	EC4A_ILLUMINATION_MODE_STRUCT ill_mode;		/*照明工作模式*/
    SMEE_DOUBLE substrate_reflect_factor;   /* 工件反射率 */
    xyrz_vect substrate_load_offset;                /*基底上片偏差*/
    SMEE_DOUBLE focus_edge_clearance;       /* <default>0.0<unit>m<range>[-0.19,0.19]<description>工件边缘清除量 */
    SMEE_DOUBLE substrate_thickness;        /* <default>0.0<unit>m<range>[-0.000575,0.001225]<description>工件厚度补偿量 */
    SMEE_DOUBLE glc_UserFocusOffset;        /* 全局调平用户离焦量 */
    SMEE_BOOL perform_exposure;             /* 是否执行实际曝光，TRUE则曝光分系统不出光 (ECUI可修改,默认TRUE) */
	EC4A_WA_METHOD_ENUM substrate_align_method; 			/* 对准模式 */
    SMEE_SUBSTRATE_SIZE_ENUM substrate_size;    /* <default>1<unit><range><description>片类型 */
	SMEE_BOOL is_CGC;									/*是否使用CGC模型*/
    SMEE_CHAR CGC_model[SMEE_MAX_FILE_NAME_SIZE];
    EC4A_ALIGN_STRATEGY_STRUCT strategy;       /* 对准策略 */
    SMEE_DOUBLE wafer_TPV;  /*硅片面型PV阈值*/
	SMEE_DOUBLE wafer_LPV;    /*硅片面型sigma阈值*/
    EC4A_LEVEL_MODE_ENUM level_mode;                      /* 曝光场的调平方式 */
    SMEE_INT32 nr_of_images;                /* 批内图像个数 */
    EC4A_IMAGE_DATA_STRUCT image[EC4A_MAX_IMAGES_NR];   /* 每个image的参数 */	
} EC4A_LOT_DATA_STRUCT;

typedef struct
{
    xy_vect mark_pos; //标记位置
    xyrzzrxry_vect exp_pos;//标记对准期望位置
    SMEE_BOOL align_valid;//对准结果是否有效
    SMEE_BOOL is_searched;//对准过程中是否使用了搜索
    xyrz_vect measure_pos;  //工件台的测量位置
    xy_vect wafer_aim_pos;// 硅片标记目标位置
    xy_vect  mark_pos_in_CCD; //标记在CCD中的位置
    xy_vect align_dev;//对准偏差
    SMEE_DOUBLE match_rate;//标记匹配率
}EC4A_MARK_MEASURE_RESULT_STRUCT;


typedef struct
{
    SMEE_INT32 nr_of_marks;
    SMEE_BOOL result_valid;
    EC4A_MARK_MEASURE_RESULT_STRUCT mark_data[EC4A_MAX_ALIGN_MARK];
}EC4A_MARK_CLUSTER_MEASURE_RESULT_STRUCT;

/* 描述：掩模对准数据*/
typedef struct
{    
    SMEE_BOOL pos_valid; /* 描述：是否为有效对准*/     
    SMEE_INT32 filler;
    xy_vect mark_pos; /* 描述：基准板标记名义位置 单位：m*/    
    xyrz_vect RS_exp_pos;/* 描述：掩模台期望位置 单位：无*/  
    xyrz_vect WS_exp_pos;/* 描述：工件台期望位置 单位：无*/  
    xy_vect mark_in_CCD;/* 描述：对准后的目标位置 单位：m/rad*/    
    xy_vect align_dev_in_WZCS;/* 描述：在WZCS下的对准偏差 单位：m*/   
    SMEE_DOUBLE match_rate; /* 描述： 标记匹配度， 单位：无*/
}EC4A_RET_DATA_STRUCT;


typedef struct
{
    EC4A_RET_DATA_STRUCT  reti_coarse_align_data[EC4A_RETICLE_MARKS_NUM];/* 描述：掩模粗对准数据 */
    EC4A_RET_DATA_STRUCT  reti_fine_align_data[EC4A_RETICLE_MARKS_NUM];/* 描述：掩模精对准数据 */
}EC4A_RETICLE_MEASURE_DATA_STRUCT;


typedef struct
{
    EC4A_MARK_CLUSTER_MEASURE_RESULT_STRUCT coarse_align_data;
    EC4A_MARK_CLUSTER_MEASURE_RESULT_STRUCT fine_align_data;
}EC4A_SUBSTRATE_ALIGN_MEASURE_RESULT_STRUCT;


typedef struct
{
    SMEE_INT32 substrate_index;
    SMEE_BOOL is_mapping;	
    SMEE_BOOL glc_result_validate; /* 全局调平结果有效 */
	SMEE_BOOL mapping_validate;  /*mapping是否有效 ，如果无效，LO做废片处理*/
    ADAE_timestamp level_point_stable;  // 第一个全局调平点水平向稳定对应的系统时刻
    ADAE_timestamp global_level_end;    // 全局调平结束系统时刻
    ADAE_timestamp mapping_start;
    ADAE_timestamp mapping_end;
    zrxry_vect global_level_result; // 全局调平结果    
    SMEE_DOUBLE current_TPV;   /*硅片面型PV值*/
    SMEE_DOUBLE current_LPV;   /*硅片面型sigma值*/
	SMEE_BOOL find_bad_area; /*是否存在坏区域*/
    SMEE_BOOL valid_wafer;   /*是否达标的片子*/
}EC4A_SUBSTRATE_LOG_STRUCT; // lot报告硅片相关部分

/* 掩模粗对准结果 */
typedef struct
{
    xy_vect rcs_to_rscs_trans;      /* 掩模相对于掩模台平移 */
    SMEE_DOUBLE rcs_to_rscs_rot;    /* 掩模相对于掩模台旋转 */
    SMEE_DOUBLE rcs_to_rscs_mag;    /* 掩模相对于掩模台缩放 */
} EC4A_COARSE_RETICLE_ALIGN_RESULT_STRUCT;

/* 掩模精对准结果 */
typedef struct
{
    xy_vect rcs_to_wzcs_trans;      /* 掩模相对于工件台零位平移 */
    SMEE_DOUBLE rcs_to_wzcs_rot;    /* 掩模相对于工件台零位旋转 */
    SMEE_DOUBLE rcs_to_wzcs_mag;    /* 掩模相对于工件台零位缩放 */
} EC4A_FINE_RETICLE_ALIGN_RESULT_STRUCT;

/* 工件(或离轴基线)对准结果 */
typedef struct  
{
    xy_vect wcs_to_wscs_trans;                      /* 工件坐标系相对于工件台坐标系平移 */
    SMEE_DOUBLE wcs_to_wscs_rot;                    /* 工件坐标系相对于工件台坐标系旋转 */
    SMEE_DOUBLE wcs_to_wscs_othro;                  /* 工件坐标系相对于工件台坐标系非正交 */
    SMEE_DOUBLE wcs_to_wscs_mag_x;                  /* 工件坐标系相对于工件台坐标系 X 向缩放 */
    SMEE_DOUBLE wcs_to_wscs_mag_y;                  /* 工件坐标系相对于工件台坐标系 Y 向缩放 */
    SMEE_DOUBLE grid_coef_x[EC4A_NR_GRID_COEFS];    /* X 向栅格系数 */
    SMEE_DOUBLE grid_coef_y[EC4A_NR_GRID_COEFS];    /* Y 向栅格系数 */
} EC4A_ALIGN_MODEL_RESULT_STRUCT;


/* 区域对准结果 */
typedef struct
{
    SMEE_INT32 nr_zones;            /* 区域个数 */
    SMEE_INT32 filler;
    EC4A_ALIGN_MODEL_RESULT_STRUCT zone_align_results[EC4A_MAX_NR_ZONES];   /* 区域对准结果 */
} EC4A_ZONE_ALIGN_RESULT_STRUCT;

/* 描述：基准板 标记对准数据*/
typedef struct
{   
    SMEE_ALIGN_TYPE_ENUM align_type; /* 描述： 对准类型*/  
    xy_vect FM_pos;      /* 描述：基准板标记名义位置 单位：m*/   
    xy_vect ref_pos; /* 描述：参考位置 单位：m*/  
    xyrz_vect rs_exp_pos;/* 描述： 掩模台期望位置 单位：无*/  
    xyrzzrxry_vect ws_exp_pos;  /* 描述： 工件台期望位置 单位：无*/   
    xy_vect aim_pos; /* 描述：对准后的目标位置 单位：m/rad*/   
    SMEE_DOUBLE match_rate; /* 描述： 标记匹配度， 单位：无*/
}EC4A_FM_DATA_STRUCT;

typedef struct
{
    EC4A_FM_DATA_STRUCT  ttl_FM_data;/* 描述：同轴基线数据 */
    EC4A_FM_DATA_STRUCT  wfr_align_data[EC4A_MAX_UPDATE_BASELINE_NUM];/* 描述：基片基线数据*/
}EC4A_FM_MEASURE_DATA_STRUCT;


typedef struct
{
	SMEE_CHAR image_id[MAX_IMAGE_ID]; // 图像ID,[4,12]个字符
    SMEE_INT32 nr_exposed_success;                      /*曝光成功个数[0,100]*/
    SMEE_INT32 nr_exposed_failed;                      /*曝光失败个数*/
    EC4A_IMAGE_STATE_ENUM image_state;              /* 曝光状态*/
    SMEE_BOOL is_reject;                            /*是否废弃当前片*/
	SMEE_BOOL cora_model_validate;             /* 掩膜粗对准模型有效 */
	SMEE_BOOL fira_model_validate;             /* 掩膜精对准模型有效 */
	SMEE_BOOL hapa_model_validate;             /* 区域对准模型有效 */
	SMEE_BOOL cowa_model_validate;             /* 硅片粗对准模型有效 */
	SMEE_BOOL fiwa_model_validate;             /* 硅片精对准模型有效 */	
    SMEE_INT32 is_retry; /* 硅片对准超限LO需要retry */	
    SMEE_DOUBLE rot_retry;/*retry的时候，硅片对准和掩模对准超限的旋转*/
	EC4A_COARSE_RETICLE_ALIGN_RESULT_STRUCT CORA_result;         /* 掩膜粗对准结果 */
	EC4A_FINE_RETICLE_ALIGN_RESULT_STRUCT FIRA_result;         /* 掩膜精对准结果 */
	EC4A_ALIGN_MODEL_RESULT_STRUCT COWA_result;         /* 粗对准结果 */
	EC4A_ZONE_ALIGN_RESULT_STRUCT FIWA_result; /* 精对准对准结果，如果区域个数为1，则为精对准 */
	EC4A_SUBSTRATE_ALIGN_MEASURE_RESULT_STRUCT alignment_data; /*硅片对准数据*/
    EC4A_RETICLE_MEASURE_DATA_STRUCT reticle_alignment_data;/*掩模对准数据*/
    EC4A_FM_MEASURE_DATA_STRUCT fm_alignment_data;
	ADAE_timestamp image_begin;/* 图像处理开始时刻*/
	ADAE_timestamp wafer_coarse_alignment_begin_time;/*硅片粗 对准开始时刻*/
	ADAE_timestamp wafer_coarse_alignment_end_time;  /*硅片粗对准结束时刻*/
	ADAE_timestamp wafer_fine_alignment_begin_time;/*硅片精 对准开始时刻*/
	ADAE_timestamp wafer_fine_alignment_end_time;  /*硅片精 对准结束时刻  */  
	ADAE_timestamp reticle_coarse_align_start_time;   /* 掩膜粗对准开始时间 */
	ADAE_timestamp reticle_coarse_align_end_time;     /* 掩膜粗对准结束时间 */
	ADAE_timestamp reticle_fine_align_start_time;   /* 掩膜精对准开始时间 */
	ADAE_timestamp reticle_fine_align_end_time;     /* 掩膜精对准结束时间 */	
}EC4A_IMAGE_LOG_STRUCT; 


/* 曝光场曝光完成事件参数 */
typedef struct
{    
	SMEE_CHAR image_id[MAX_IMAGE_ID]; // 图像ID,[4,12]个字符
    SMEE_INT32 origin_index;
    EC4A_FIELD_STATE_ENUM field_state; // 曝光场状态
    xy_vect field_position; // 曝光场位置(硅片坐标系)
 	EC4A_DOSE_CONTROL_MODE_ENUM dose_mode;//剂量控制模式
 	SMEE_INT32 field_index;
	//曝光位置
    xyrz_vect exp_ws_hor_pos; // 水平位置(期望,工件台坐标系)
    zrxry_vect exp_ws_ver_pos;// 垂向位置(期望,工件台坐标系)
    xyrz_vect act_ws_hor_pos; // 水平位置(实际,工件台坐标系)
    zrxry_vect act_ws_ver_pos;// 垂向位置(实际,工件台坐标系)

	
     // 照明参数
    SMEE_DOUBLE exp_dose;	//下发剂量
    SMEE_DOUBLE real_exp_dose; // 实际剂量
    SMEE_DOUBLE real_exp_time; // 实际曝光时间
    
    ADAE_timestamp hor_move_begin; // 工件台水平向运动开始时刻
    ADAE_timestamp hor_move_end;   // 工件台水平向运动结束时刻
    ADAE_timestamp vert_move_begin;// 工件台水平向运动开始时刻
    ADAE_timestamp vert_move_end;  // 工件台水平向运动结束时刻
    ADAE_timestamp expose_begin;// 曝光开始时刻
    ADAE_timestamp expose_end;  // 曝光结束时刻

    //FS测量值
    SMEE_BOOL bZinvalid;          //测量z 是否有效
    SMEE_BOOL bRXinvalid;         //测量rx 是否有效
    SMEE_BOOL bRYinvalid;         //测量ry 是否有效
    SMEE_BOOL filler1;
    zrxry_vect sfocus;            //FS测量值
} EC4A_FIELD_LOG_STRUCT;

/* 图像集数据定义 */
typedef struct
{  
    SMEE_CHAR image_id[EC4A_IMAGE_ID_LEN];  /* 该掩模上图像ID */
	SMEE_INT32 expo_nr;		
    SMEE_INT32 filler;/*该图像的曝光数*/
	xy_vect exp_center[MAX_FLD_NR_PER_IMG];						/*曝光场中心位置*/
}EC4A_EXPO_INFO_STRUCT;


/* 图像集数据定义 */
typedef struct
{
    SMEE_CHAR reticle_id[EC4A_MAX_RETICLE_ID];  /* 图像所在掩模ID */
    SMEE_INT32 nr_of_images; /* 该掩模上图像个数 */
    SMEE_INT32 zfiller;    
    EC4A_EXPO_INFO_STRUCT expo_info[EC4A_MAX_IMAGES_NR];  /* 该掩模上图像ID */
}EC4A_IMAGE_ROUTE_STRUCT;

typedef struct
{
    SMEE_CHAR message[EC4A_MAX_MSG_SIZE]; // 事件消息
}EC4A_UI_MESSAGE_EVENT_STRUCT;// 界面消息结构体

/* 场曝光开始事件通知参数 */
typedef struct
{
    EC4A_DOSE_CONTROL_MODE_ENUM dose_mode;// 剂量控制模式
    SMEE_INT32 field_index;         //规划后场序号，从0开始
    SMEE_DOUBLE dose;             // 曝光剂量
    xy_vect field_position;  // 曝光场位置(硅片坐标系)
    zrxry_vect vert_position;//垂向位置
} EC4A_EXPOSURE_BEGIN_STRUCT;


/* 场曝光结束事件通知参数 */
typedef struct
{
    xy_vect field_position;  // 曝光场位置(硅片坐标系)
} EC4A_EXPOSURE_END_STRUCT;

typedef struct
{
	SMEE_BOOL update_loading_offset;
	SMEE_BOOL update_vert_compensation;
    SMEE_BOOL update_mvs_voltage;
    SMEE_INT32 filler;
	xyrz_vect loading_offset;
	SMEE_DOUBLE vert_compensation;
    SMEE_DOUBLE mvs_voltage;
}EC4A_SAVE_ALIGNMENT_OFFSET_EVENT_STRUCT;

typedef struct
{
    SMEE_INT32 nr_marks;
    SMEE_INT32 filler;
    SMEE_DOUBLE coarse_matching_rate;
    SMEE_DOUBLE fine_matching_rate;
    EC4A_SUBSTRATE_MARK_DATA_STRUCT wafer_marks[MAX_WAFER_MARK_NUM];
}EC4A_WAFER_AILGN_BEGIN_STRUCT;

#endif /* EC4A_TC_H */

