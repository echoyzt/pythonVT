/*******************************************************************************
* Copyright (C) 2011, 上海微电子装备有限公司
* All rights reserved.
* 产品号   : SSB300
* 所属组件 :
* 模块名称 :
* 文件名称 : smee_project.h
* 概要描述 : 与SSB产品相关的通用数据结构
*            考虑到数据定义的方便性,该文件中定义的部分数据类型或宏常数不遵守SMEE编码规范
* 历史记录 :
* 版本     日  期     作  者    内  容
* V2.0   2017.08.24   卢剑涛  放宽ID长度到88字节,参照SEMI标准修正上限
* V1.2	 2016.07.13	  卜小建  增加默认超时时间定义
* v1.1   2014.11.23   卜小建  增加掩模版库相关定义
* v1.0   2014.11.07   卜小建  修改ssb300.h为smee_project.h;删除部分不用的内容
******************************************************************************/
#ifndef SMEE_PROJECT_H_
#define SMEE_PROJECT_H_

// LOT
#define MAX_LOT_ID          88  // LOT ID字符串数组长度
#define MIN_LOT_ID_LENGTH    1  // LOT ID长度下限(不包括'\0')
#define MAX_LOT_ID_LENGTH   80  // LOT ID长度上限(不包括'\0')

#define MAX_WAF_NR_PER_LOT  25  // 任一LOT中能够处理的硅片数目限制
#define MAX_RET_NR_PER_LOT  6   // 任一LOT使用掩模数目限制


// 图像IMAGE
#define MAX_IMG_NR_PER_LOT    24  // 任一LOT使用图像数目限制
#define MAX_FLD_NR_PER_IMG  1000  // 任一图像对应硅片上的曝光场数目限制

#define MAX_IMAGE_ID          88  // 图像ID字符串数组长度
#define MIN_IMG_ID_LENGTH      4  // 图像ID长度下限(不包括'\0')
#define MAX_IMG_ID_LENGTH     12  // 图像ID长度上限(不包括'\0')



// 掩模RETICLE
#define MIN_RET_PORT_NBR        1  //最小掩模POD个数
#define MAX_RET_PORT_NBR        2  //最大掩模POD个数
#define MAX_RET_BOX_SLOT_NBR    6  // 掩模盒槽数目上限

#define MAX_RETICLE_ID         88  // 掩模ID字符串数组长度
#define MIN_RET_ID_LENGTH       1  // 掩模ID长度下限(不包括'\0')
#define MAX_RET_ID_LENGTH      64  // 掩模ID长度上限(不包括'\0')

#define MAX_RET_POD_ID         88  // 掩模POD ID字符串数组长度
#define MIN_RET_POD_ID_LENGTH   1  // 掩模POD ID长度下限(不包括'\0')
#define MAX_RET_POD_ID_LENGTH  64  // 掩模POD ID长度上限(不包括'\0')

// 硅片WAFER
#define MIN_WAF_PORT_NBR           1   // PORT数目下限
#define MAX_WAF_PORT_NBR           3   // PORT数目上限

#define MAX_WAF_CAR_SLOT_NBR       25  // 硅片盒槽数目


#define MAX_WAF_CARRIER_ID         88  // 硅片盒ID字符串数组长度
#define MIN_WAF_CARRIER_ID_LENGTH   1  // 硅片盒ID长度下限(不包括'\0')
#define MAX_WAF_CARRIER_ID_LENGTH  80  // 硅片盒ID长度上限(不包括'\0')

#define MAX_WAFER_ID       88  // 硅片ID字符串数组长度
#define MIN_WAF_ID_LENGTH   1  // 硅片ID长度下限(不包括'\0')
#define MAX_WAF_ID_LENGTH  80  // 硅片ID长度上限(不包括'\0')



// 保护环PROTECTION RING
#define MAX_RING_ID         64  // 保护环ID字符串数组长度
#define MIN_RING_ID_LENGTH   8  // 保护环ID长度下限(不包括'\0')
#define MAX_RING_ID_LENGTH  24  // 保护环ID长度上限(不包括'\0')



// 硅片标记
#define MAX_WAFER_MARK_NUM 100  // 硅片标记数目

//新增默认超时时间重定义
#ifndef DEFAULT_TIMEOUT
	#define DEFAULT_TIMEOUT		0x7FFFFFFF  // 默认超时时间
#endif


typedef enum
{
    SMEE_SUBSTRATE_SIZE_MIN = 0,
    SMEE_WAFER_2_INCH,  // 2寸硅片
    SMEE_WAFER_3_INCH,  // 3寸硅片 
    SMEE_WAFER_4_INCH,  // 4寸硅片
    SMEE_WAFER_5_INCH,  // 5寸硅片
    SMEE_WAFER_6_INCH,  // 6寸硅片
    SMEE_WAFER_8_INCH,  // 8寸硅片
    SMEE_WAFER_12_INCH, // 12寸硅片
    SMEE_WAFER_18_INCH, // 18寸硅片
    SMEE_SUBSTRATE_SIZE_MAX
}SMEE_SUBSTRATE_SIZE_ENUM; // 基底尺寸

typedef enum
{
    SMEE_WAFER_TYPE_MIN = 0,
    SMEE_WAFER_NOTCH,       // notch wafer
    SMEE_WAFER_FLAT,        // flat wafer
    SMEE_WAFER_DOUBLE_FLAT, // 双平边硅片
    SMEE_WAFER_NONE,        // 无缺口硅片
    SMEE_WAFER_TYPE_MAX
}SMEE_WAFER_TYPE_ENUM; // 硅片类型

typedef enum
{
    SMEE_ALIGN_TYPE_MIN = 0,
    SMEE_ALIGN_NONE,   // 不进行对准
    SMEE_ALIGN_TTL,    // 同轴对准 Through Lens Alignment
    SMEE_ALIGN_OA,     // 离轴对准 Off-axis Alignment
    SMEE_ALIGN_WBA,    // 透射式背面对准 Backside Transmission Alignment
    SMEE_ALIGN_DT,     // 反射式背面对准 Backside Reflection Alignment
    SMEE_ALIGN_TYPE_MAX
}SMEE_ALIGN_TYPE_ENUM;// 对准类型


typedef enum
{
    SMEE_ALGORITHM_TYPE_MIN            = -1,// 迁就现有机器常数
    SMEE_ALGORITHM_GRAY_CORR           = 0, // 界面 GrayCorr
                                            // GCM: Gray Correlation Match
                                            // 灰度相关性匹配算法
    SMEE_ALGORITHM_EDGE_MAX_I          = 1, // 界面 EdgeMaxI
                                            // EMM: Edge Max Correlation Match(TypeI)
                                            // 边缘最优相关性匹配算法
    SMEE_ALGORITHM_EDGE_MAX_II         = 2, // 界面 EdgeMaxII
                                            // EMM: Edge Max Correlation Match(TypeII)
                                            // 边缘最优相关性匹配算法
    SMEE_ALGORITHM_EDGE_MAX_ENHANCED   = 3, // 界面 EdgeMaxEnhanced
                                            // EME: Edge Max Correlation Match(Enhanced)
                                            // 增强型边缘最优相关性匹配算法
    SMEE_ALGORITHM_EDGE_CORR           = 4, // 界面 EdgeCorr
                                            // ECM: Edge Correlation Match
                                            // 边缘相关性匹配算法
    SMEE_ALGORITHM_TEXTURE_CORR        = 5, // 界面 TextureCorr
                                            // TCM: Texture Correlation Match
                                            // 纹理相关性匹配算法
    SMEE_ALGORITHM_LASER_MARK_LOCATION = 6, // 界面 LaserMarkLocation
                                            // LML: laser mark location 
                                            // 用户激光打标算法
    SMEE_ALGORITHM_REGION_GRAY_CORR    = 7, // 界面 RegionGrayCorr
                                            // RGM: Region Gray Match
                                            // 区域灰度相关性匹配
    SMEE_ALGORITHM_GRAY_CORR_II        = 8, // 界面 GrayCorrII
                                            // GCM: Gray Correlation Match(Type II)
                                            // 灰度相关性匹配算法
    SMEE_ALGORITHM_TYPE_MAX            = 100
}SMEE_ALGORITHM_TYPE_ENUM;// 算法类型


// 物料面型枚举
typedef enum
{
    SMEE_SURFACE_TYPE_MIN = 0,
    SMEE_SURFACE_POLISH_ONE_SIDE,    // 蓝宝石单抛片
    SMEE_SURFACE_POLISH_BOTH_SIDE,   // 蓝宝石双抛片
    SMEE_SURFACE_WAFER,              // 硅片
    SMEE_SURFACE_CUSTOMIZE_1,        // 自定义面型1
    SMEE_SURFACE_CUSTOMIZE_2,        // 自定义面型2
    SMEE_SURFACE_TYPE_MAX
} SMEE_SURFACE_TYPE_ENUM;

#endif /* SMEE_PROJECT_H_ */

