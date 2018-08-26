/******************************************************************************
* Copyright (C) 2014, 上海微电子装备有限公司
* All rights reserved.
* 产品号 : SSB 530/10
* 所属组件 : EC
* 模块名称 : EC4T
* 文件名称 : EC4T_if.h
* 概要描述 : EC组件的外部接口定义
* 历史记录 : 
* 版本   日期        作者     内容
* 1.0    2014-08-18  王彦麟   新建。
******************************************************************************/

#ifndef EC4T_IF_H
#define EC4T_IF_H


///////////////////////////////////////////////////////////////////////////////
//                                头文件包含
///////////////////////////////////////////////////////////////////////////////

#include "EC4A_tc.h"
#include "EC4T_tc.h"


///////////////////////////////////////////////////////////////////////////////
//                              接口声明
///////////////////////////////////////////////////////////////////////////////

/******************************************************************************
INTERFACE <SMEE_INT32 EC4T_do_global_level_on_substrate>
{
<InterfaceType>: FUNCTION<Blocking>
<Parameters>
    IN:    SMEE_BOOL do_global_level  <TRACE_ON><描述:是否做全局调平>
    IN:    SMEE_BOOL do_mapping <TRACE_ON><描述:是否做mapping>
    IN:    SMEE_SUBSTRATE_SIZE_ENUM substrate_spec  <TRACE_ON><描述:工件规格>
    IN:    SMEE_DOUBLE substrate_thickness          <TRACE_ON><描述:工件厚度>
    IN:    SMEE_DOUBLE user_focus_offset            <TRACE_ON><描述:用户离焦量>
    IN:    xy_vect global_middle_point              <TRACE_ON><描述:单点调平点>
    IN:    EC4T_MAPPING_ROUTE_STRUCT *mapping_route            <TRACE_ON><描述:mapping路径>
    OUT:   SMEE_DOUBLE *level_result_p              <TRACE_ON><描述:全局调平结果>
    INOUT: notype  none                             <TRACE_ON><描述:无>
<Timeout>: 60
<Server>:  Default
<Returns>: OK
           EC4A_SYSTEM_ERROR
           EC4A_ILLEGAL_CALL_ERROR
           EC4A_PARAMETER_ERROR
<Description>: 对工件进行指定点进行全局调平。
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4T_do_global_level_on_substrate (
        IN SMEE_BOOL do_global_level,
        IN SMEE_BOOL do_mapping,
        IN SMEE_SUBSTRATE_SIZE_ENUM substrate_spec,
        IN SMEE_DOUBLE substrate_thickness,
        IN SMEE_DOUBLE user_focus_offset,
        IN xy_vect global_middle_point,
        IN EC4T_MAPPING_ROUTE_STRUCT *mapping_route,
        OUT zrxry_vect *level_result_p );


/******************************************************************************
INTERFACE <SMEE_INT32 EC4T_do_global_level_on_ws_fiducial>
{
<InterfaceType>: FUNCTION<Blocking>
<Parameters>
    IN:    SMEE_DOUBLE substrate_thickness  <TRACE_ON><描述:工件厚度>
    IN:    SMEE_DOUBLE user_focus_offset    <TRACE_ON><描述:用户离焦量>
    OUT:   zrxry_vect *level_result_p       <TRACE_ON><描述:调平结果>
    OUT:   zrxry_vect *substrate_cuniform_p <TRACE_ON><描述:工件楔形>
    INOUT: notype  none                     <TRACE_ON><描述:无>
<Timeout>: 60
<Server>:  Default
<Returns>: OK
           EC4A_SYSTEM_ERROR
           EC4A_ILLEGAL_CALL_ERROR
           EC4A_PARAMETER_ERROR
<Description>: 对工件台基准版指定点进行全局调平。
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4T_do_global_level_on_ws_fiducial (
    IN SMEE_DOUBLE substrate_thickness,
    IN SMEE_DOUBLE user_focus_offset,
    OUT zrxry_vect *level_result_p,
    OUT zrxry_vect *substrate_cuniform_p );


/******************************************************************************
INTERFACE <SMEE_INT32 EC4T_set_ws_position_all_by_fls>
{
<InterfaceType>: FUNCTION<Blocking>
<Parameters>
    IN:    SMEE_SUBSTRATE_SIZE_ENUM substrate_spec  <TRACE_ON><描述:工件类型>
    IN:    xy_vect wafer_pos                        <TRACE_ON><描述:工件水平向名义位置>
    IN:    zrxry_vect ws_expect_tilt                <TRACE_ON><描述:工件台垂向期望位置>
    OUT:   zrxry_vect *level_result_p               <TRACE_ON><描述:全局调平结果>
    INOUT: notype  none                             <TRACE_ON><描述:无>
<Timeout>: 60
<Server>:  Default
<Returns>: OK
           EC4A_SYSTEM_ERROR
           EC4A_ILLEGAL_CALL_ERROR
<Description>: 工件台垂向定位。
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4T_set_ws_position_all_by_fls (
    IN SMEE_SUBSTRATE_SIZE_ENUM substrate_spec,
    IN xy_vect wafer_pos,
    IN zrxry_vect ws_expect_tilt,
    OUT zrxry_vect *level_result_p );


/******************************************************************************
INTERFACE <SMEE_INT32 EC4T_substrate_align>
{
<InterfaceType>: FUNCTION<Blocking>
<Parameters>
    IN:    SMEE_UINT32 nr_marks                                                 <TRACE_ON><描述:标记个数>
    IN:    xy_vect mark_norminal_positions[EC4T_MAX_NR_SUBSTRATE_MARKS]         <TRACE_ON><描述:标记名义位置>
    IN:    EC4T_WA_ALIGN_RECIPE_STRUCT oa_align_recipe                          <TRACE_ON><描述:离轴对准处方>
    OUT:   EC4T_UPDATE_WA_BASELINE_RESULT_STRUCT *update_oa_baseline_result_p   <TRACE_OFF><描述:水平向模型结果>
    OUT:   EC4A_ALIGN_MODEL_RESULT_STRUCT *align_result_p                               <TRACE_OFF><描述:水平向模型结果>
    INOUT: notype  none                                                         <TRACE_ON><描述:无>
<Timeout>: 600
<Server>:  Default
<Returns>: OK
           EC4A_SYSTEM_ERROR
           EC4A_ILLEGAL_CALL_ERROR
           EC4A_PARAMETER_ERROR
<Description>: 执行离轴更新基线、基板对准、根据输入的执行次数实现多次精对准。
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4T_substrate_align (
    IN SMEE_ALIGN_TYPE_ENUM align_type,    
	IN SMEE_SUBSTRATE_SIZE_ENUM wafer_size,
    IN SMEE_UINT32 nr_marks,
    IN xy_vect mark_norminal_positions[EC4T_MAX_NR_SUBSTRATE_MARKS],
    IN EC4T_WA_ALIGN_RECIPE_STRUCT oa_align_recipe,
    OUT EC4T_UPDATE_WA_BASELINE_RESULT_STRUCT *update_oa_baseline_result_p,
    OUT EC4A_ALIGN_MODEL_RESULT_STRUCT *align_result_p );


/******************************************************************************
INTERFACE <SMEE_INT32 EC4T_reticle_align>
{
<InterfaceType>: FUNCTION<Blocking>
<Parameters>
    IN:    EC4T_RETI_ALIGN_SPC_STRUCT align_spec                          <TRACE_ON><描述:对准规格>
    OUT:   EC4T_UPDATE_TTL_BASELINE_RESULT_STRUCT *ttl_baseline_result_p   <TRACE_OFF><描述:同轴基线更新结果>
    OUT:   EC4A_COARSE_RETICLE_ALIGN_RESULT_STRUCT*cora_result_p    <TRACE_OFF><描述:掩模粗对准结果>
    OUT:   EC4A_FINE_RETICLE_ALIGN_RESULT_STRUCT *fira_result_p    <TRACE_OFF><描述:掩模精对准结果>
    INOUT: notype  none                             <TRACE_ON><描述:无>
<Timeout>: 600
<Server>:  Default
<Returns>: OK
           EC4A_SYSTEM_ERROR
           EC4A_ILLEGAL_CALL_ERROR
           EC4A_PARAMETER_ERROR
<Description>: 同轴基线更新、掩模粗对准、掩模精对准。
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4T_reticle_align (IN EC4T_RETI_ALIGN_SPC_STRUCT align_spec,
    OUT EC4T_UPDATE_TTL_BASELINE_RESULT_STRUCT *ttl_baseline_result_p,
    OUT EC4A_COARSE_RETICLE_ALIGN_RESULT_STRUCT *cora_result_p,
    OUT EC4A_FINE_RETICLE_ALIGN_RESULT_STRUCT *fira_result_p );


/******************************************************************************
INTERFACE <SMEE_INT32 EC4T_search_OA_focus>
{
<InterfaceType>: FUNCTION<Blocking>
<Parameters>
    IN:    EC4T_MARK_LOCATION_ENUM mark_location    <TRACE_ON><描述:标记位置>
    IN:    xyrzzrxry_vect ws_pos                    <TRACE_ON><描述:搜索时的工件台期望位置>
    IN:    SMEE_DOUBLE z_search_range               <TRACE_ON><描述:搜索范围>
    OUT:   zrxry_vect *focused_ws_pos_p             <TRACE_ON><描述:同轴CCD最佳焦面时的工件台位置>
    OUT:   SMEE_DOUBLE *focused_fls_z_p             <TRACE_ON><描述:CCD清晰度最优时的FLS测量值>
    INOUT: notype  none                             <TRACE_ON><描述:无>
<Timeout>: 180
<Server>:  Default
<Returns>: OK
           EC4A_SYSTEM_ERROR
           EC4A_ILLEGAL_CALL_ERROR
           EC4A_PARAMETER_ERROR
<Description>: 通过上下运动工件台，获取每个CCD最佳焦面时的工件台位置。
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4T_search_focus (IN SMEE_ALIGN_TYPE_ENUM align_type,
	IN SMEE_SUBSTRATE_SIZE_ENUM ePlateType,
    IN xyrzzrxry_vect ws_pos,
    IN SMEE_DOUBLE z_search_range,
    OUT zrxry_vect *focused_ws_pos_p,
    OUT SMEE_DOUBLE *focused_fls_z_p );


/******************************************************************************
INTERFACE <SMEE_INT32 EC4T_offaxes_align>
{
<InterfaceType>: FUNCTION<Blocking>
<Parameters>
    IN:    SMEE_ALIGN_TYPE_ENUM align_type                     <TRACE_ON><描述:对准类型>
    IN:    SMEE_SUBSTRATE_SIZE_ENUM wafer_size                 <TRACE_ON><描述:标记尺寸>
    IN:    xy_vect mark_nominal_pos                     <TRACE_ON><描述:标记位置>
    IN:    EC4T_WA_ALIGN_RECIPE_STRUCT *oa_align_recipe <TRACE_OFF><描述:离轴对准处方>
    OUT:   EC4T_ALIGN_RESULT_STRUCT *align_result_p     <TRACE_OFF><描述:离轴对准结果>
    INOUT: notype  none                                 <TRACE_ON><描述:无>
<Timeout>: 300
<Server>:  Default
<Returns>: OK
           EC4A_SYSTEM_ERROR
           EC4A_ILLEGAL_CALL_ERROR
           EC4A_PARAMETER_ERROR
<Description>: 离轴对准。
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4T_wa_align (IN SMEE_ALIGN_TYPE_ENUM align_type,
	IN SMEE_SUBSTRATE_SIZE_ENUM wafer_size,
    IN xy_vect mark_nominal_pos,
    IN EC4T_WA_ALIGN_RECIPE_STRUCT oa_align_recipe,
    OUT EC4T_WA_ALIGN_RESULT_STRUCT *align_result_p );


/******************************************************************************
INTERFACE <SMEE_INT32 EC4T_TTL_align>
{
<InterfaceType>: FUNCTION<Blocking>
<Parameters>
    IN:    xy_vect mark_norminal_pos                        <TRACE_ON><描述:标记名义位置>
    IN:    EC4T_ALIGN_RECIPE_STRUCT ttl_align_recipe    <TRACE_OFF><描述:对准处方>
    OUT:   EC4T_TTL_ALIGN_RESULT_STRUCT *align_result_p     <TRACE_ON><描述:对准结果>
    INOUT: notype  none                                     <TRACE_ON><描述:无>
<Timeout>: 60
<Server>:  Default
<Returns>: OK
           EC4A_SYSTEM_ERROR
           EC4A_ILLEGAL_CALL_ERROR
           EC4A_PARAMETER_ERROR
<Description>: 同轴对准。
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4T_TTL_align (
    IN xy_vect mark_norminal_pos,
    IN EC4T_ALIGN_RECIPE_STRUCT ttl_align_recipe,
    OUT EC4T_TTL_ALIGN_RESULT_STRUCT *align_result_p );


/******************************************************************************
INTERFACE <SMEE_INT32 EC4T_update_wa_baseline>
{
<InterfaceType>: FUNCTION<Blocking>
<Parameters>
    IN:    notype none                                                 <TRACE_ON><描述:无>
    OUT:   EC4T_UPDATE_WA_BASELINE_RESULT_STRUCT *oa_baseline_result_p <TRACE_ON><描述:同轴基准标记在CCD中的像素位置>
    INOUT: notype none                                                 <TRACE_ON><描述:无>
<Timeout>: 60
<Server>:  Default
<Returns>: OK
           EC4A_SYSTEM_ERROR
           EC4A_ILLEGAL_CALL_ERROR
           EC4A_PARAMETER_ERROR
<Description>: 更新离轴基线，并获取离轴CCD参考位置。
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4T_update_wa_baseline (IN SMEE_ALIGN_TYPE_ENUM align_type,
    OUT EC4T_UPDATE_WA_BASELINE_RESULT_STRUCT *oa_baseline_result_p );


/******************************************************************************
INTERFACE <SMEE_INT32 EC4T_update_ttl_baseline>
{
<InterfaceType>:    FUNCTION<Blocking>
<Parameters>
    IN:     notype none                                                     <TRACE_ON><描述:无>
    OUT:    EC4T_UPDATE_TTL_BASELINE_RESULT_STRUCT *ttl_baseline_result_p   <TRACE_ON><描述:同轴基准标记在CCD中的像素位置>
    INOUT:  notype none                                                     <TRACE_ON><描述:无>
<Timeout>:  60
<Server>:   Default
<Returns>:  OK
            EC4A_SYSTEM_ERROR
            EC4A_ILLEGAL_CALL_ERROR
            EC4A_PARAMETER_ERROR
<Description>: 更新同轴基线，并获取同轴基准标记在CCD中的像素位置。
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4T_update_ttl_baseline (
    OUT EC4T_UPDATE_TTL_BASELINE_RESULT_STRUCT *ttl_baseline_result_p );


#endif /* EC4T_IF_H */

