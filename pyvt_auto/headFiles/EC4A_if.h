/******************************************************************************
* Copyright (C) 2014, 上海微电子装备有限公司
* All rights reserved. 
* 产品号 : SSB 530/10
* 所属组件 : EC
* 模块名称 : EC4A
* 文件名称 : EC4A_if.h
* 概要描述 : EC组件的外部接口定义
* 历史记录 : 
* 版本   日期        作者      内容
* 1.0    2014-08-18  王彦麟    新建。
******************************************************************************/ 

#ifndef EC4A_IF_H
#define EC4A_IF_H


///////////////////////////////////////////////////////////////////////////////
//                                头文件包含
///////////////////////////////////////////////////////////////////////////////

#include "EC4A_tc.h"
#include "SM4A_tc.h"
#include "TR4A_tc.h"


///////////////////////////////////////////////////////////////////////////////
//                              接口声明
///////////////////////////////////////////////////////////////////////////////

/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_initialize>
{
<InterfaceType>: FUNCTION<Blocking/NonbBlocking/Fcn>
<Parameters>
IN:     notype  none <TRACE_ON> <描述:无>
OUT:    notype  none <TRACE_ON> <描述:无>
INOUT:  notype  none <TRACE_ON> <描述:无>
<Timeout>:      60
<Server>:       Default
<Returns>:      OK
                EC4A_SYSTEM_ERROR
<Description>:      组件初始化接口，包括数据初始化，状态机初始化等
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4A_initialize ();

SMEE_EXPORT SMEE_INT32 EC4A_initialize_req ();
SMEE_EXPORT SMEE_INT32 EC4A_initialize_wait (
    IN SMEE_INT32 timeout );

typedef void (* EC4A_initialize_cb)(
    IN SMEE_INT32 error_code,
    IN void *context_p );
SMEE_EXPORT SMEE_INT32 EC4A_initialize_fcn (
    IN EC4A_initialize_cb proc,
    INOUT void *context_p );


/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_terminate>
{
<InterfaceType>: FUNCTION<Blocking/NonbBlocking/Fcn>
<Parameters>
IN: notype  none <TRACE_ON> <描述:无>
OUT:    notype  none <TRACE_ON> <描述:无>
INOUT:  notype  none <TRACE_ON> <描述:无>
<Timeout>:      60
<Server>:       Default
<Returns>:      OK
                EC4A_SYSTEM_ERROR
<Description>:      组件终止
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4A_terminate ();

SMEE_EXPORT SMEE_INT32 EC4A_terminate_req ();
SMEE_EXPORT SMEE_INT32 EC4A_terminate_wait (
    IN SMEE_INT32 timeout );

typedef void (* EC4A_terminate_cb)(
    IN SMEE_INT32 error_code,
    IN void *context_p );
SMEE_EXPORT SMEE_INT32 EC4A_terminate_fcn (
    IN EC4A_terminate_cb proc,
    INOUT void *context_p );


/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_get_status>
{
<InterfaceType>: FUNCTION<Blocking/NonbBlocking/Fcn>
<Parameters>
IN: notype  none <TRACE_OFF> <描述:无>
OUT:    EC4A_STATUS_STRUCT *status <TRACE_ON> <描述:EC内部状态>
INOUT:  notype  none <TRACE_OFF> <描述:无>
<Timeout>:      60
<Server>:       Default
<Returns>:      OK
                EC4A_SYSTEM_ERROR
                EC4A_PARAMETER_ERROR
<Description>:      获取组件内部状态
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4A_get_status (
    OUT EC4A_STATUS_STRUCT *status );

SMEE_EXPORT SMEE_INT32 EC4A_get_status_req ();
SMEE_EXPORT SMEE_INT32 EC4A_get_status_wait (
    IN SMEE_INT32 timeout, 
    OUT EC4A_STATUS_STRUCT *status );

typedef void (* EC4A_get_status_cb)(
    IN EC4A_STATUS_STRUCT status,
    IN SMEE_INT32 error_code,
    IN void *context_p );
SMEE_EXPORT SMEE_INT32 EC4A_get_status_fcn (
    IN EC4A_get_status_cb proc,
    INOUT void *context_p );


/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_get_state>
{
<InterfaceType>: FUNCTION<Blocking/NonbBlocking/Fcn>
<Parameters>
IN: notype  none <TRACE_OFF> <描述:无>
OUT:    SMEE_BOOL *initialized <TRACE_ON> <描述:是否初始化>
OUT:    SM4A_DRIVER_STATE_ENUM * driver_state <TRACE_ON> <描述:EC系统状态>
INOUT:  notype  none <TRACE_OFF> <描述:无>
<Timeout>:      60
<Server>:       Default
<Returns>:      OK
                EC4A_SYSTEM_ERROR
                EC4A_PARAMETER_ERROR
<Description>:  获取组件的驱动状态
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4A_get_state (
    OUT SMEE_BOOL *initialized,
    OUT SM4A_DRIVER_STATE_ENUM *driver_state);

SMEE_EXPORT SMEE_INT32 EC4A_get_state_req ();
SMEE_EXPORT SMEE_INT32 EC4A_get_state_wait (
    IN SMEE_INT32 timeout, 
    OUT SMEE_BOOL *initialized,
    OUT SM4A_DRIVER_STATE_ENUM *driver_state );

typedef void (* EC4A_get_state_cb)(
    IN SMEE_BOOL initialized,
    IN SM4A_DRIVER_STATE_ENUM driver_state,
    IN SMEE_INT32 error_code,
    IN void *context_p );
SMEE_EXPORT SMEE_INT32 EC4A_get_state_fcn (
    IN EC4A_get_state_cb proc,
    INOUT void *context_p );


/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_import_dependence_data>
{
<InterfaceType>: FUNCTION<Blocking>
<Parameters>
IN: notype  none <TRACE_ON> <描述:无>
OUT:    notype  none <TRACE_ON> <描述:无>
INOUT:  notype  none <TRACE_ON> <描述:无>
<Timeout>:      60
<Server>:       Default
<Returns>:      OK
                EC4A_SYSTEM_ERROR
<Description>:  读取外部数据
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4A_import_dependence_data ();


/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_update_mc>
{
<InterfaceType>: FUNCTION<Blocking>
<Parameters>
IN: notype  none <TRACE_ON> <描述:无>
OUT:    notype  none <TRACE_ON> <描述:无>
INOUT:  notype  none <TRACE_ON> <描述:无>
<Timeout>:      60
<Server>:       Default
<Returns>:      OK
                EC4A_SYSTEM_ERROR
<Description>:  更新机器常数，EC没有机器常数，函数为空
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4A_update_mc ();


/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_set_sim_mode>
{
<InterfaceType>: FUNCTION<Blocking>
<Parameters>
IN: TR4A_SIM_MODE sim_mode <TRACE_ON> <描述:无>
IN: TR4A_TRACE_MODE trace_mode <TRACE_ON> <描述:无>
IN: TR4A_REQ_MODE data_mode <TRACE_ON> <描述:无>
OUT:    notype  none <TRACE_ON> <描述:无>
INOUT:  notype  none <TRACE_ON> <描述:无>
<Timeout>:      60
<Server>:       Default
<Returns>:      OK
                EC4A_SYSTEM_ERROR
                EC4A_ILLEGAL_CALL_ERROR
                EC4A_PARAMETER_ERROR
<Description>:  设置仿真模式
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4A_set_sim_mode (
    IN TR4A_SIM_MODE_ENUM sim_mode, 
    IN TR4A_TRACE_MODE_ENUM trace_mode, 
    IN TR4A_REQ_MODE_ENUM data_mode );


/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_get_sim_mode>
{
<InterfaceType>: FUNCTION<Blocking>
<Parameters>
IN: notype  none <TRACE_ON> <描述:无>
OUT:    TR4A_SIM_MODE *sim_mode <TRACE_ON> <描述:无>
OUT:    TR4A_TRACE_MODE *trace_mode <TRACE_ON> <描述:无>
OUT:    TTR4A_REQ_MODE *data_mode <TRACE_ON> <描述:无>
INOUT:  notype  none <TRACE_ON> <描述:无>
<Timeout>:      60
<Server>:       Default
<Returns>:      OK
                EC4A_SYSTEM_ERROR
                EC4A_PARAMETER_ERROR
<Description>:  获取仿真模式
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4A_get_sim_mode (
    OUT TR4A_SIM_MODE_ENUM *sim_mode,
    OUT TR4A_TRACE_MODE_ENUM *trace_mode,
    OUT TR4A_REQ_MODE_ENUM *data_mode );


/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_start_lot>
{
<InterfaceType>: FUNCTION<Blocking/NonbBlocking/Fcn/Trigger>
<Parameters>
IN: EC4A_LOT_DATA_STRUCT *lot_data_p <TRACE_ON> <描述:批数据>
OUT:SMEE_INT32 *nr_of_reticles		<TRACE_ON> <描述:掩模个数>
OUT:EC4A_IMAGE_ROUTE_STRUCT image_route[MAX_RET_NR_PER_LOT] <TRACE_ON> <描述:图像顺序>
INOUT:  notype  none <TRACE_ON> <描述:无>
<Timeout>:      180
<Server>:       Default
<Returns>:      OK
                EC4A_ILLEGAL_CALL_ERROR
                EC4A_SYSTEM_ERROR
<Description>: 开始lot。
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4A_start_lot (
    IN EC4A_LOT_DATA_STRUCT *lot_data,
    OUT SMEE_INT32 *nr_of_reticles,
    OUT EC4A_IMAGE_ROUTE_STRUCT image_route[MAX_RET_NR_PER_LOT]);

SMEE_EXPORT SMEE_INT32 EC4A_start_lot_req (
    IN EC4A_LOT_DATA_STRUCT *lot_data );
SMEE_EXPORT SMEE_INT32 EC4A_start_lot_wait (
    IN SMEE_INT32 timeout,
    OUT SMEE_INT32 *nr_of_reticles,
    OUT EC4A_IMAGE_ROUTE_STRUCT image_route[MAX_RET_NR_PER_LOT]);

typedef void (* EC4A_start_lot_cb)(
	IN SMEE_INT32 nr_of_reticles,
    IN EC4A_IMAGE_ROUTE_STRUCT image_route[MAX_RET_NR_PER_LOT],
    IN SMEE_INT32 error_code,
    IN void *context_p );
SMEE_EXPORT SMEE_INT32 EC4A_start_lot_fcn (
    IN EC4A_LOT_DATA_STRUCT *lot_data,
    IN EC4A_start_lot_cb proc,
    INOUT void *context_p );

SMEE_EXPORT SMEE_INT32 EC4A_start_lot_trig (
    IN EC4A_LOT_DATA_STRUCT *lot_data );


/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_finish_lot>
{
<InterfaceType>: FUNCTION<Blocking>
<Parameters>
IN: notype  none <TRACE_ON> <描述:无>
OUT:    notype  none <TRACE_ON> <描述:无>
INOUT:  notype  none <TRACE_ON> <描述:无>
<Timeout>:      60
<Server>:       Default
<Returns>:      OK
                EC4A_ILLEGAL_CALL_ERROR
                EC4A_SYSTEM_ERROR
<Description>:  终止lot 
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4A_finish_lot ();


/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_measure_substrate>
{
<InterfaceType>: FUNCTION<Blocking/NonbBlocking/Fcn/Trigger>
<Parameters>
IN: SMEE_INT32 substrate_index <TRACE_ON> <描述:基板序号>
IN: SMEE_BOOL first_substrate <TRACE_ON> <描述:是否是批中第一个基板>
OUT:   EC4A_ALIGN_RECIPE_STRUCT *wafer_result <TRACE_ON> <描述:工件测量结果>
OUT:    notype none <TRACE_OFF> <描述:无>
INOUT:  notype  none <TRACE_ON> <描述:无>
<Timeout>:      1800
<Server>:       Default
<Returns>:      OK
                EC4A_ILLEGAL_CALL_ERROR
                EC4A_SYSTEM_ERROR
<Description>: 测量工件
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4A_measure_substrate (
    IN SMEE_INT32 substrate_index,
    IN SMEE_BOOL  first_substrate,
    OUT EC4A_SUBSTRATE_LOG_STRUCT *measure_result);

SMEE_EXPORT SMEE_INT32 EC4A_measure_substrate_req (
    IN SMEE_INT32 substrate_index,
    IN SMEE_BOOL  first_substrate);
SMEE_EXPORT SMEE_INT32 EC4A_measure_substrate_wait (
    IN SMEE_INT32 timeout,
    OUT EC4A_SUBSTRATE_LOG_STRUCT *measure_result);

typedef void (* EC4A_measure_substrate_cb)(
	IN EC4A_SUBSTRATE_LOG_STRUCT measure_result,
    IN SMEE_INT32 error_code,
    IN void *context_p );
SMEE_EXPORT SMEE_INT32 EC4A_measure_substrate_fcn (
    IN SMEE_INT32 substrate_index,
    IN SMEE_BOOL  first_substrate,
    IN EC4A_measure_substrate_cb proc,
    INOUT void *context_p );

SMEE_EXPORT SMEE_INT32 EC4A_measure_substrate_trig(
    IN SMEE_INT32 substrate_index,
    IN SMEE_BOOL  first_substrate);

/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_measure_substrate_done_subscribe>
{
<InterfaceType>:    EVENT<>
<Parameters>
IN: EC4A_measure_substrate_done_sb  proc <TRACE_ON> <描述:无>
IN: void * context_p <TRACE_OFF> <描述:环境参数>
OUT: SMEE_INT32 *handle_p <TRACE_ON> <描述:订阅句柄>
INOUT:  notype  none <TRACE_ON> <描述:无>
<Timeout>:      60
<Server>:       Default
<Returns>:      OK
                EC4A_ILLEGAL_CALL_ERROR
                EC4A_PARAMETER_ERROR
                EC4A_SYSTEM_ERROR
<Description>:  完成测量基板事件订阅接口
}
******************************************************************************/
typedef void (*EC4A_measure_substrate_done_sb)(
    IN SMEE_INT32 error_code,
    IN void *context_p );
SMEE_EXPORT SMEE_INT32 EC4A_measure_substrate_done_subscribe (
    IN EC4A_measure_substrate_done_sb proc,
    OUT SMEE_INT32 *handle_p,
    INOUT void *context_p );




/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_measure_substrate_done_unsubscribe>
{
<InterfaceType>:    EVENT<>
<Parameters>
IN: SMEE_INT32  handle <TRACE_ON> <描述:订阅句柄>
OUT: notype none <TRACE_ON> <描述:无>
INOUT:  notype  none <TRACE_ON> <描述:无>
<Timeout>:      60
<Server>:       Default
<Returns>:      OK
                EC4A_ILLEGAL_CALL_ERROR
                EC4A_SYSTEM_ERROR
<Description>:  完成测量基板事件反订阅接口
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4A_measure_substrate_done_unsubscribe (
    IN SMEE_INT32 handle );

/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_get_measure_substrate_result>
{
<InterfaceType>:   FUNCTION<Blocking>
<Parameters>
IN:  notype  none <TRACE_ON> <描述:无>
OUT: EC4A_SUBSTRATE_LOG_STRUCT  *measure_result <TRACE_ON> <描述:调平结果>
INOUT:  notype  none <TRACE_ON> <描述:无>
<Timeout>:      60
<Server>:       Default
<Returns>:      OK
                EC4A_ILLEGAL_CALL_ERROR
                EC4A_PARAMETER_ERROR
                EC4A_SYSTEM_ERROR
<Description>:  获取测量基板结果
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4A_get_measure_substrate_result (
    OUT EC4A_SUBSTRATE_LOG_STRUCT  *measure_result);


/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_expose_image>
{
<InterfaceType>: FUNCTION<Blocking/NonbBlocking/Fcn/Trigger>
<Parameters>
IN: SMEE_CHAR image_id[EC4A_IMAGE_ID_LEN] <TRACE_ON> <描述:图像id>
OUT:   EC4A_FIELD_LOG_STRUCT field_result[MAX_FLD_NR_PER_IMG]  <TRACE_OFF> <描述:图像曝光结果>
OUT:  EC4A_IMAGE_STATE_ENUM *image_state  <TRACE_OFF> <描述:场曝光状态>
INOUT:  notype  none <TRACE_ON> <描述:无>
<Timeout>:      3600
<Server>:       Default
<Returns>:      OK
                EC4A_ILLEGAL_CALL_ERROR
                EC4A_SYSTEM_ERROR
<Description>:  曝光图像
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4A_expose_image (
    IN SMEE_CHAR image_id[EC4A_IMAGE_ID_LEN],
    IN SMEE_BOOL is_new_reticle,
    OUT EC4A_IMAGE_LOG_STRUCT *align_result,
    OUT EC4A_FIELD_LOG_STRUCT expose_result[MAX_FLD_NR_PER_IMG]);

typedef void (* EC4A_expose_image_cb)(
    IN EC4A_IMAGE_LOG_STRUCT align_result,
    IN EC4A_FIELD_LOG_STRUCT expose_result[MAX_FLD_NR_PER_IMG],
    IN SMEE_INT32 error_code,
    IN void *context_p );
SMEE_EXPORT SMEE_INT32 EC4A_expose_image_fcn (
    IN SMEE_CHAR image_id[EC4A_IMAGE_ID_LEN],
    IN SMEE_BOOL is_new_reticle,
    IN EC4A_expose_image_cb proc,
    INOUT void *context_p );

SMEE_EXPORT SMEE_INT32 EC4A_expose_image_trig (
    IN SMEE_CHAR image_id[EC4A_IMAGE_ID_LEN],
    IN SMEE_BOOL is_new_reticle);

/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_image_done_subscribe>
{
<InterfaceType>:    EVENT<>
<Parameters>
IN: EC4A_IMAGE_LOG_STRUCT  result <TRACE_OFF><描述:对准结果>
IN: EC4A_FIELD_LOG_STRUCT expose_result[MAX_FLD_NR_PER_IMG]<TRACE_OFF><描述:图像曝光完成结果>
IN: EC4A_IMAGE_STATE_ENUM image_state <TRACE_OFF><描述:图像结果>
IN: EC4A_image_done_sb  proc <TRACE_ON> <描述:无>
IN: void * context_p <TRACE_OFF> <描述:环境参数>
OUT: SMEE_INT32 *handle_p <TRACE_ON> <描述:订阅句柄>
INOUT:  notype  none <TRACE_ON> <描述:无>
<Timeout>:      60
<Server>:       Default
<Returns>:      OK
                EC4A_ILLEGAL_CALL_ERROR
                EC4A_PARAMETER_ERROR
                EC4A_SYSTEM_ERROR
<Description>:  图像曝光完成事件订阅接口
}
******************************************************************************/
typedef void (*EC4A_image_done_sb)(
    IN SMEE_INT32 error_code,
    IN void *context_p);
SMEE_EXPORT SMEE_INT32 EC4A_image_done_subscribe (
    IN EC4A_image_done_sb proc,
    OUT SMEE_INT32 *handle_p,
    INOUT void *context_p);


/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_image_done_unsubscribe>
{
<InterfaceType>:    EVENT<>
<Parameters>
IN: SMEE_INT32  handle <TRACE_ON> <描述:订阅句柄>
OUT: notype none <TRACE_ON> <描述:无>
INOUT:  notype  none <TRACE_ON> <描述:无>
<Timeout>:      60
<Server>:       Default
<Returns>:      OK
                EC4A_ILLEGAL_CALL_ERROR
                EC4A_SYSTEM_ERROR
<Description>:  图像曝光完成事件反订阅接口
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4A_image_done_unsubscribe (
    IN SMEE_INT32 handle );

/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_get_image_result>
{
<InterfaceType>:   FUNCTION<Blocking>
<Parameters>
IN:  notype  none <TRACE_ON> <描述:无>
OUT: EC4A_IMAGE_LOG_STRUCT  *align_result <TRACE_ON> <描述:对准结果>
INOUT:  notype  none <TRACE_ON> <描述:无>
<Timeout>:      60
<Server>:       Default
<Returns>:      OK
                EC4A_ILLEGAL_CALL_ERROR
                EC4A_SYSTEM_ERROR
<Description>:  获取对准结果
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4A_get_image_result (OUT EC4A_IMAGE_LOG_STRUCT  *align_result);


/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_abort_lot>
{
<InterfaceType>: FUNCTION<Blocking>
<Parameters>
IN: SMEE_INT32  notype none <TRACE_OFF> <描述:无>
OUT: notype none <TRACE_OFF> <描述:无>
INOUT:  notype  none <TRACE_OFF> <描述:无>
<Timeout>:      60
<Server>:       ECXE_MAIN
<Returns>:      OK
                EC4A_SYSTEM_ERROR
<Description>:  用户终止abort曝光
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4A_abort_lot ();


/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_wafer_align_begin_sb>
{
<InterfaceType>:    EVENT<>
<Parameters>
    IN:             EC4A_wafer_align_begin_sb    proc     <TRACE_ON> <描述:无>
    OUT:            SMEE_INT32                      *handle_p   <TRACE_ON> <描述:句柄>
    INOUT:         void                          *context_p <TRACE_ON> <描述:无>
<Timeout>:          60
<Server>:           Default
<Returns>:          OK
                    EC4A_SYSTEM_ERROR
<Description>:      通知客户端OILO开始画图订阅
}
******************************************************************************/
typedef void (*EC4A_wafer_align_begin_sb)(
    IN EC4A_WAFER_AILGN_BEGIN_STRUCT align_data,
    IN SMEE_INT32                       error_code,
    IN void	                            *context_p);

SMEE_EXPORT SMEE_INT32 EC4A_wafer_align_begin_subscribe(
    IN EC4A_wafer_align_begin_sb    proc,    
    OUT SMEE_INT32                      *handle_p,
    INOUT void                          *context_p);

/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_wafer_align_begin_unsubscribe>
{
<InterfaceType>:    EVENT<>
<Parameters>
IN: SMEE_INT32  handle <TRACE_ON> <描述:订阅句柄>           
OUT: notype none <TRACE_ON> <描述:无>
INOUT:  notype  none <TRACE_ON> <描述:无>
<Timeout>:      60
<Server>:       Default
<Returns>:      OK
                EC4A_ILLEGAL_CALL_ERROR
                EC4A_SYSTEM_ERROR
<Description>:通知OILO开始画图取消订阅
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4A_wafer_align_begin_unsubscribe(
    IN SMEE_INT32                       handle);


/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_mark_align_begin_subscribe>
{
<InterfaceType>:    EVENT<>
<Parameters>
    IN:             EC4A_mark_align_begin_sb    proc     <TRACE_ON> <描述:无>
    OUT:            SMEE_INT32                      *handle_p   <TRACE_ON> <描述:句柄>
    INOUT:         void                          *context_p <TRACE_ON> <描述:无>
<Timeout>:          60
<Server>:           ECXE_MAIN
<Returns>:          OK
                    EC4A_SYSTEM_ERROR
<Description>:      通知客户端OIAL，对准类型和对准id。注册函数。
}
******************************************************************************/
typedef void (*EC4A_mark_align_begin_sb)(
    IN EC4A_ALIGNMENT_PHASE_ENUM alignment_phase,
    IN SMEE_INT32                       align_id,
    IN SMEE_INT32                       error_code,
    IN void	                            *context_p);
SMEE_EXPORT SMEE_INT32 EC4A_mark_align_begin_subscribe(
    IN EC4A_mark_align_begin_sb    proc,    
    OUT SMEE_INT32                      *handle_p,
    INOUT void                          *context_p);

/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_mark_align_begin_unsubscribe>
{
<InterfaceType>:    EVENT<>
<Parameters>
IN: SMEE_INT32  handle <TRACE_ON> <描述:订阅句柄>           
OUT: notype none <TRACE_ON> <描述:无>
INOUT:  notype  none <TRACE_ON> <描述:无>
<Timeout>:      60
<Server>:       ECXE_MAIN
<Returns>:      OK
                EC4A_ILLEGAL_CALL_ERROR
                EC4A_SYSTEM_ERROR
<Description>: 标记开始取消订阅接口    
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4A_mark_align_begin_unsubscribe(
    IN SMEE_INT32                       handle);


/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_mark_align_end_subscribe>
{
<InterfaceType>:    EVENT<>
<Parameters>
    IN:              EC4A_mark_align_end_sb    proc<TRACE_ON> <描述:对准id>
    OUT:          SMEE_INT32   *handle_p  <TRACE_ON> <描述:无>
    INOUT:          void    *context_p  <TRACE_ON> <描述:无>
<Timeout>:          60
<Server>:           ECXE_MAIN
<Returns>:          OK
                    EC4A_SYSTEM_ERROR
<Description>:      通知OIAL，对准类型和对准id和匹配度。注册函数。
}
******************************************************************************/
typedef void (*EC4A_mark_align_end_sb)(IN EC4A_ALIGNMENT_PHASE_ENUM alignment_phase,
										IN SMEE_INT32  align_id,
                                        IN SMEE_DOUBLE  matching_rate,
                                        IN SMEE_INT32  error_code,
                                        IN void	      *context_p);
SMEE_EXPORT SMEE_INT32 EC4A_mark_align_end_subscribe(IN EC4A_mark_align_end_sb    proc,    
                                                  OUT SMEE_INT32   *handle_p,
                                                 INOUT void    *context_p);

/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_mark_align_end_unsubscribe>
{
<InterfaceType>:    EVENT<>
<Parameters>
IN: SMEE_INT32  handle <TRACE_ON> <描述:订阅句柄>           
OUT: notype none <TRACE_ON> <描述:无>
INOUT:  notype  none <TRACE_ON> <描述:无>
<Timeout>:      60
<Server>:       ECXE_MAIN
<Returns>:      OK
                EC4A_ILLEGAL_CALL_ERROR
                EC4A_SYSTEM_ERROR
<Description>: 标记结束取消订阅接口    
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4A_mark_align_end_unsubscribe(IN SMEE_INT32 handle);

/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_ui_massage_event_subscribe>
{
<InterfaceType>:    EVENT<>
<Parameters>
IN: EC4A_ui_massage_event_sb  proc <TRACE_ON> <描述:无>
IN: void * context_p <TRACE_OFF> <描述:环境参数>
OUT: SMEE_INT32 *handle_p <TRACE_ON> <描述:订阅句柄>
INOUT:  notype  none <TRACE_ON> <描述:无>
<Timeout>:      60
<Server>:       Default
<Returns>:      OK
                EC4A_ILLEGAL_CALL_ERROR
                EC4A_PARAMETER_ERROR
                EC4A_SYSTEM_ERROR
<Description>:  用户消息事件订阅和反订阅接口。
}
******************************************************************************/
typedef void (*EC4A_ui_message_event_sb)(
	IN EC4A_UI_MESSAGE_EVENT_STRUCT lot_event,
	IN SMEE_INT32 error_code,
	IN void *context_p );
SMEE_EXPORT SMEE_INT32 EC4A_ui_message_event_subscribe (
	IN	EC4A_ui_message_event_sb  proc,
	OUT SMEE_INT32	*handle_p,
	INOUT void	*context_p );

/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_ui_massage_event_unsubscribe>
{
<InterfaceType>:    EVENT<>
<Parameters>
IN: SMEE_INT32  handle <TRACE_ON> <描述:订阅句柄>           
OUT: notype none <TRACE_ON> <描述:无>
INOUT:  notype  none <TRACE_ON> <描述:无>
<Timeout>:      60
<Server>:       Default
<Returns>:      OK
                EC4A_ILLEGAL_CALL_ERROR
                EC4A_SYSTEM_ERROR
<Description>:  用户消息事件订阅接口    
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4A_ui_message_event_unsubscribe (
    IN SMEE_INT32 handle );

/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_save_align_offset_event_subscribe>
{
<InterfaceType>:    EVENT<>
<Parameters>
IN: EC4A_save_align_offset_event_sb  proc <TRACE_ON> <描述:无>
IN: void * context_p <TRACE_OFF> <描述:环境参数>
OUT: SMEE_INT32 *handle_p <TRACE_ON> <描述:订阅句柄>
INOUT:  notype  none <TRACE_ON> <描述:无>
<Timeout>:      60
<Server>:       Default
<Returns>:      OK
                EC4A_ILLEGAL_CALL_ERROR
                EC4A_PARAMETER_ERROR
                EC4A_SYSTEM_ERROR
<Description>:  保存对准偏差事件订阅和反订阅接口。
}
******************************************************************************/
typedef void (*EC4A_save_align_offset_event_sb)(
    IN EC4A_SAVE_ALIGNMENT_OFFSET_EVENT_STRUCT lot_event,
    IN SMEE_INT32 error_code,
    IN void *context_p );
SMEE_EXPORT SMEE_INT32 EC4A_save_align_offset_event_subscribe (
    IN  EC4A_save_align_offset_event_sb  proc,
    OUT SMEE_INT32  *handle_p,
    INOUT void  *context_p );

/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_save_align_offset_event_unsubscribe>
{
<InterfaceType>:    EVENT<>
<Parameters>
IN: SMEE_INT32  handle <TRACE_ON> <描述:订阅句柄>           
OUT: notype none <TRACE_ON> <描述:无>
INOUT:  notype  none <TRACE_ON> <描述:无>
<Timeout>:      60
<Server>:       Default
<Returns>:      OK
                EC4A_ILLEGAL_CALL_ERROR
                EC4A_SYSTEM_ERROR
<Description>:  保存对准偏差事件取消订阅接口    
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4A_save_align_offset_event_unsubscribe (
    IN SMEE_INT32 handle );


/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_exposure_begin_subscribe>
{
<InterfaceType>:    EVENT<>
<Parameters>
IN: EC4A_exposure_begin_sb  proc <TRACE_ON> <描述:无>
IN: void * handle_p <TRACE_OFF> <描述:环境参数>                
OUT: notype  none <TRACE_ON> <描述:无>
INOUT: void *context_p <TRACE_ON> <描述:订阅句柄>
<Timeout>:      60
<Server>:       ECXE_MAIN
<Returns>:      OK
                EC4A_ILLEGAL_CALL_ERROR
                EC4A_PARAMETER_ERROR
                EC4A_SYSTEM_ERROR
<Description>:  场曝光开始事件订阅接口  
}
******************************************************************************/
typedef void (*EC4A_exposure_begin_sb)(
    IN EC4A_EXPOSURE_BEGIN_STRUCT  expo_begin,
    IN SMEE_INT32 error_code,
    IN void *context_p );

SMEE_EXPORT SMEE_INT32 EC4A_exposure_begin_subscribe (
    IN EC4A_exposure_begin_sb proc,
    OUT SMEE_INT32 *handle_p,
    INOUT void *context_p );

/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_exposure_begin_unsubscribe>
{
<InterfaceType>:    EVENT<>
<Parameters>
IN: SMEE_INT32  handle <TRACE_ON> <描述:订阅句柄>           
OUT: notype none <TRACE_ON> <描述:无>
INOUT:  notype  none <TRACE_ON> <描述:无>
<Timeout>:      60
<Server>:       ECXE_MAIN
<Returns>:      OK
                EC4A_ILLEGAL_CALL_ERROR
                EC4A_PARAMETER_ERROR
                EC4A_SYSTEM_ERROR
<Description>:  场曝光开始事件取消订阅接口  
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4A_exposure_begin_unsubscribe(IN SMEE_INT32 handle);

/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_exposure_end_subscribe>
{
<InterfaceType>:    EVENT<>
<Parameters>
IN: EC4A_exposure_end_sb  proc <TRACE_ON> <描述:无>
IN: void * context_p <TRACE_OFF> <描述:环境参数>                
OUT: SMEE_INT32 *handle_p <TRACE_ON> <描述:订阅句柄>
INOUT:  notype  none <TRACE_ON> <描述:无>
<Timeout>:      60
<Server>:       Default
<Returns>:      OK
                EC4A_ILLEGAL_CALL_ERROR
                EC4A_PARAMETER_ERROR
                EC4A_SYSTEM_ERROR
<Description>:  场曝光结束事件订阅接口  
}
******************************************************************************/
typedef void (*EC4A_exposure_end_sb)(
    IN EC4A_EXPOSURE_END_STRUCT  exposure_en,
    IN SMEE_INT32 error_code,
    IN void *context_p );

SMEE_EXPORT SMEE_INT32 EC4A_exposure_end_subscribe (
    IN EC4A_exposure_end_sb proc,
    OUT SMEE_INT32 *handle_p,
    INOUT void *context_p );

/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_exposure_end_unsubscribe>
{
<InterfaceType>:    EVENT<>
<Parameters>
IN: SMEE_INT32  handle <TRACE_ON> <描述:订阅句柄>           
OUT: notype none <TRACE_ON> <描述:无>
INOUT:  notype  none <TRACE_ON> <描述:无>
<Timeout>:      60
<Server>:       Default
<Returns>:      OK
                EC4A_ILLEGAL_CALL_ERROR
                EC4A_PARAMETER_ERROR
                EC4A_SYSTEM_ERROR
<Description>:  场曝光结束事件取消订阅接口  
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4A_exposure_end_unsubscribe(IN SMEE_INT32 handle);

/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_field_done_subscribe>
{
<InterfaceType>:    EVENT<>
<Parameters>
IN: EC4A_exposure_end_sb  proc <TRACE_ON> <描述:无>
IN: void * context_p <TRACE_OFF> <描述:环境参数>                
OUT: SMEE_INT32 *handle_p <TRACE_ON> <描述:订阅句柄>
INOUT:  notype  none <TRACE_ON> <描述:无>
<Timeout>:      60
<Server>:       Default
<Returns>:      OK
                EC4A_ILLEGAL_CALL_ERROR
                EC4A_PARAMETER_ERROR
                EC4A_SYSTEM_ERROR
<Description>:  场曝光结束事件订阅接口  
}
******************************************************************************/
typedef void (*EC4A_field_done_sb)(
    IN EC4A_FIELD_LOG_STRUCT  field_en,
    IN SMEE_INT32 error_code,
    IN void *context_p );

SMEE_EXPORT SMEE_INT32 EC4A_field_done_subscribe (
    IN EC4A_field_done_sb proc,
    OUT SMEE_INT32 *handle_p,
    INOUT void *context_p );

/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_field_done_unsubscribe>
{
<InterfaceType>:    EVENT<>
<Parameters>
IN: SMEE_INT32  handle <TRACE_ON> <描述:订阅句柄>           
OUT: notype none <TRACE_ON> <描述:无>
INOUT:  notype  none <TRACE_ON> <描述:无>
<Timeout>:      60
<Server>:       Default
<Returns>:      OK
                EC4A_ILLEGAL_CALL_ERROR
                EC4A_PARAMETER_ERROR
                EC4A_SYSTEM_ERROR
<Description>:  场曝光结束事件取消订阅接口  
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4A_field_done_unsubscribe(IN SMEE_INT32 handle);


/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_get_substrate_loading_offset_for_retry>
{
<InterfaceType>:   FUNCTION<Blocking>
<Parameters>
IN:  notype  none <TRACE_ON> <描述:无>
OUT: xyrz_vect loading_offset <TRACE_ON> <描述:基片上板偏差>
INOUT:  notype  none <TRACE_ON> <描述:无>
<Timeout>:      60
<Server>:       Default
<Returns>:      OK
                EC4A_ILLEGAL_CALL_ERROR
                EC4A_SYSTEM_ERROR
<Description>:  LOT重试获取基片上板偏差
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4A_get_substrate_loading_offset_for_retry(
    OUT xyrz_vect *loading_offset);

SMEE_EXPORT SMEE_INT32 EC4A_no_param(void);

#endif /* EC4A_IF_H */

