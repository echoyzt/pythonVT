/******************************************************************************
* Copyright (C) 2014, �Ϻ�΢����װ�����޹�˾
* All rights reserved.
* ��Ʒ�� : SSB 530/10
* ������� : EC
* ģ������ : EC4T
* �ļ����� : EC4T_if.h
* ��Ҫ���� : EC������ⲿ�ӿڶ���
* ��ʷ��¼ : 
* �汾   ����        ����     ����
* 1.0    2014-08-18  ������   �½���
******************************************************************************/

#ifndef EC4T_IF_H
#define EC4T_IF_H


///////////////////////////////////////////////////////////////////////////////
//                                ͷ�ļ�����
///////////////////////////////////////////////////////////////////////////////

#include "EC4A_tc.h"
#include "EC4T_tc.h"


///////////////////////////////////////////////////////////////////////////////
//                              �ӿ�����
///////////////////////////////////////////////////////////////////////////////

/******************************************************************************
INTERFACE <SMEE_INT32 EC4T_do_global_level_on_substrate>
{
<InterfaceType>: FUNCTION<Blocking>
<Parameters>
    IN:    SMEE_BOOL do_global_level  <TRACE_ON><����:�Ƿ���ȫ�ֵ�ƽ>
    IN:    SMEE_BOOL do_mapping <TRACE_ON><����:�Ƿ���mapping>
    IN:    SMEE_SUBSTRATE_SIZE_ENUM substrate_spec  <TRACE_ON><����:�������>
    IN:    SMEE_DOUBLE substrate_thickness          <TRACE_ON><����:�������>
    IN:    SMEE_DOUBLE user_focus_offset            <TRACE_ON><����:�û��뽹��>
    IN:    xy_vect global_middle_point              <TRACE_ON><����:�����ƽ��>
    IN:    EC4T_MAPPING_ROUTE_STRUCT *mapping_route            <TRACE_ON><����:mapping·��>
    OUT:   SMEE_DOUBLE *level_result_p              <TRACE_ON><����:ȫ�ֵ�ƽ���>
    INOUT: notype  none                             <TRACE_ON><����:��>
<Timeout>: 60
<Server>:  Default
<Returns>: OK
           EC4A_SYSTEM_ERROR
           EC4A_ILLEGAL_CALL_ERROR
           EC4A_PARAMETER_ERROR
<Description>: �Թ�������ָ�������ȫ�ֵ�ƽ��
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
    IN:    SMEE_DOUBLE substrate_thickness  <TRACE_ON><����:�������>
    IN:    SMEE_DOUBLE user_focus_offset    <TRACE_ON><����:�û��뽹��>
    OUT:   zrxry_vect *level_result_p       <TRACE_ON><����:��ƽ���>
    OUT:   zrxry_vect *substrate_cuniform_p <TRACE_ON><����:����Ш��>
    INOUT: notype  none                     <TRACE_ON><����:��>
<Timeout>: 60
<Server>:  Default
<Returns>: OK
           EC4A_SYSTEM_ERROR
           EC4A_ILLEGAL_CALL_ERROR
           EC4A_PARAMETER_ERROR
<Description>: �Թ���̨��׼��ָ�������ȫ�ֵ�ƽ��
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
    IN:    SMEE_SUBSTRATE_SIZE_ENUM substrate_spec  <TRACE_ON><����:��������>
    IN:    xy_vect wafer_pos                        <TRACE_ON><����:����ˮƽ������λ��>
    IN:    zrxry_vect ws_expect_tilt                <TRACE_ON><����:����̨��������λ��>
    OUT:   zrxry_vect *level_result_p               <TRACE_ON><����:ȫ�ֵ�ƽ���>
    INOUT: notype  none                             <TRACE_ON><����:��>
<Timeout>: 60
<Server>:  Default
<Returns>: OK
           EC4A_SYSTEM_ERROR
           EC4A_ILLEGAL_CALL_ERROR
<Description>: ����̨����λ��
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
    IN:    SMEE_UINT32 nr_marks                                                 <TRACE_ON><����:��Ǹ���>
    IN:    xy_vect mark_norminal_positions[EC4T_MAX_NR_SUBSTRATE_MARKS]         <TRACE_ON><����:�������λ��>
    IN:    EC4T_WA_ALIGN_RECIPE_STRUCT oa_align_recipe                          <TRACE_ON><����:�����׼����>
    OUT:   EC4T_UPDATE_WA_BASELINE_RESULT_STRUCT *update_oa_baseline_result_p   <TRACE_OFF><����:ˮƽ��ģ�ͽ��>
    OUT:   EC4A_ALIGN_MODEL_RESULT_STRUCT *align_result_p                               <TRACE_OFF><����:ˮƽ��ģ�ͽ��>
    INOUT: notype  none                                                         <TRACE_ON><����:��>
<Timeout>: 600
<Server>:  Default
<Returns>: OK
           EC4A_SYSTEM_ERROR
           EC4A_ILLEGAL_CALL_ERROR
           EC4A_PARAMETER_ERROR
<Description>: ִ��������»��ߡ������׼�����������ִ�д���ʵ�ֶ�ξ���׼��
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
    IN:    EC4T_RETI_ALIGN_SPC_STRUCT align_spec                          <TRACE_ON><����:��׼���>
    OUT:   EC4T_UPDATE_TTL_BASELINE_RESULT_STRUCT *ttl_baseline_result_p   <TRACE_OFF><����:ͬ����߸��½��>
    OUT:   EC4A_COARSE_RETICLE_ALIGN_RESULT_STRUCT*cora_result_p    <TRACE_OFF><����:��ģ�ֶ�׼���>
    OUT:   EC4A_FINE_RETICLE_ALIGN_RESULT_STRUCT *fira_result_p    <TRACE_OFF><����:��ģ����׼���>
    INOUT: notype  none                             <TRACE_ON><����:��>
<Timeout>: 600
<Server>:  Default
<Returns>: OK
           EC4A_SYSTEM_ERROR
           EC4A_ILLEGAL_CALL_ERROR
           EC4A_PARAMETER_ERROR
<Description>: ͬ����߸��¡���ģ�ֶ�׼����ģ����׼��
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
    IN:    EC4T_MARK_LOCATION_ENUM mark_location    <TRACE_ON><����:���λ��>
    IN:    xyrzzrxry_vect ws_pos                    <TRACE_ON><����:����ʱ�Ĺ���̨����λ��>
    IN:    SMEE_DOUBLE z_search_range               <TRACE_ON><����:������Χ>
    OUT:   zrxry_vect *focused_ws_pos_p             <TRACE_ON><����:ͬ��CCD��ѽ���ʱ�Ĺ���̨λ��>
    OUT:   SMEE_DOUBLE *focused_fls_z_p             <TRACE_ON><����:CCD����������ʱ��FLS����ֵ>
    INOUT: notype  none                             <TRACE_ON><����:��>
<Timeout>: 180
<Server>:  Default
<Returns>: OK
           EC4A_SYSTEM_ERROR
           EC4A_ILLEGAL_CALL_ERROR
           EC4A_PARAMETER_ERROR
<Description>: ͨ�������˶�����̨����ȡÿ��CCD��ѽ���ʱ�Ĺ���̨λ�á�
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
    IN:    SMEE_ALIGN_TYPE_ENUM align_type                     <TRACE_ON><����:��׼����>
    IN:    SMEE_SUBSTRATE_SIZE_ENUM wafer_size                 <TRACE_ON><����:��ǳߴ�>
    IN:    xy_vect mark_nominal_pos                     <TRACE_ON><����:���λ��>
    IN:    EC4T_WA_ALIGN_RECIPE_STRUCT *oa_align_recipe <TRACE_OFF><����:�����׼����>
    OUT:   EC4T_ALIGN_RESULT_STRUCT *align_result_p     <TRACE_OFF><����:�����׼���>
    INOUT: notype  none                                 <TRACE_ON><����:��>
<Timeout>: 300
<Server>:  Default
<Returns>: OK
           EC4A_SYSTEM_ERROR
           EC4A_ILLEGAL_CALL_ERROR
           EC4A_PARAMETER_ERROR
<Description>: �����׼��
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
    IN:    xy_vect mark_norminal_pos                        <TRACE_ON><����:�������λ��>
    IN:    EC4T_ALIGN_RECIPE_STRUCT ttl_align_recipe    <TRACE_OFF><����:��׼����>
    OUT:   EC4T_TTL_ALIGN_RESULT_STRUCT *align_result_p     <TRACE_ON><����:��׼���>
    INOUT: notype  none                                     <TRACE_ON><����:��>
<Timeout>: 60
<Server>:  Default
<Returns>: OK
           EC4A_SYSTEM_ERROR
           EC4A_ILLEGAL_CALL_ERROR
           EC4A_PARAMETER_ERROR
<Description>: ͬ���׼��
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
    IN:    notype none                                                 <TRACE_ON><����:��>
    OUT:   EC4T_UPDATE_WA_BASELINE_RESULT_STRUCT *oa_baseline_result_p <TRACE_ON><����:ͬ���׼�����CCD�е�����λ��>
    INOUT: notype none                                                 <TRACE_ON><����:��>
<Timeout>: 60
<Server>:  Default
<Returns>: OK
           EC4A_SYSTEM_ERROR
           EC4A_ILLEGAL_CALL_ERROR
           EC4A_PARAMETER_ERROR
<Description>: ����������ߣ�����ȡ����CCD�ο�λ�á�
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4T_update_wa_baseline (IN SMEE_ALIGN_TYPE_ENUM align_type,
    OUT EC4T_UPDATE_WA_BASELINE_RESULT_STRUCT *oa_baseline_result_p );


/******************************************************************************
INTERFACE <SMEE_INT32 EC4T_update_ttl_baseline>
{
<InterfaceType>:    FUNCTION<Blocking>
<Parameters>
    IN:     notype none                                                     <TRACE_ON><����:��>
    OUT:    EC4T_UPDATE_TTL_BASELINE_RESULT_STRUCT *ttl_baseline_result_p   <TRACE_ON><����:ͬ���׼�����CCD�е�����λ��>
    INOUT:  notype none                                                     <TRACE_ON><����:��>
<Timeout>:  60
<Server>:   Default
<Returns>:  OK
            EC4A_SYSTEM_ERROR
            EC4A_ILLEGAL_CALL_ERROR
            EC4A_PARAMETER_ERROR
<Description>: ����ͬ����ߣ�����ȡͬ���׼�����CCD�е�����λ�á�
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4T_update_ttl_baseline (
    OUT EC4T_UPDATE_TTL_BASELINE_RESULT_STRUCT *ttl_baseline_result_p );


#endif /* EC4T_IF_H */

