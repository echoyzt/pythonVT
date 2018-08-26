/******************************************************************************
* Copyright (C) 2014, �Ϻ�΢����װ�����޹�˾
* All rights reserved. 
* ��Ʒ�� : SSB 530/10
* ������� : EC
* ģ������ : EC4A
* �ļ����� : EC4A_if.h
* ��Ҫ���� : EC������ⲿ�ӿڶ���
* ��ʷ��¼ : 
* �汾   ����        ����      ����
* 1.0    2014-08-18  ������    �½���
******************************************************************************/ 

#ifndef EC4A_IF_H
#define EC4A_IF_H


///////////////////////////////////////////////////////////////////////////////
//                                ͷ�ļ�����
///////////////////////////////////////////////////////////////////////////////

#include "EC4A_tc.h"
#include "SM4A_tc.h"
#include "TR4A_tc.h"


///////////////////////////////////////////////////////////////////////////////
//                              �ӿ�����
///////////////////////////////////////////////////////////////////////////////

/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_initialize>
{
<InterfaceType>: FUNCTION<Blocking/NonbBlocking/Fcn>
<Parameters>
IN:     notype  none <TRACE_ON> <����:��>
OUT:    notype  none <TRACE_ON> <����:��>
INOUT:  notype  none <TRACE_ON> <����:��>
<Timeout>:      60
<Server>:       Default
<Returns>:      OK
                EC4A_SYSTEM_ERROR
<Description>:      �����ʼ���ӿڣ��������ݳ�ʼ����״̬����ʼ����
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
IN: notype  none <TRACE_ON> <����:��>
OUT:    notype  none <TRACE_ON> <����:��>
INOUT:  notype  none <TRACE_ON> <����:��>
<Timeout>:      60
<Server>:       Default
<Returns>:      OK
                EC4A_SYSTEM_ERROR
<Description>:      �����ֹ
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
IN: notype  none <TRACE_OFF> <����:��>
OUT:    EC4A_STATUS_STRUCT *status <TRACE_ON> <����:EC�ڲ�״̬>
INOUT:  notype  none <TRACE_OFF> <����:��>
<Timeout>:      60
<Server>:       Default
<Returns>:      OK
                EC4A_SYSTEM_ERROR
                EC4A_PARAMETER_ERROR
<Description>:      ��ȡ����ڲ�״̬
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
IN: notype  none <TRACE_OFF> <����:��>
OUT:    SMEE_BOOL *initialized <TRACE_ON> <����:�Ƿ��ʼ��>
OUT:    SM4A_DRIVER_STATE_ENUM * driver_state <TRACE_ON> <����:ECϵͳ״̬>
INOUT:  notype  none <TRACE_OFF> <����:��>
<Timeout>:      60
<Server>:       Default
<Returns>:      OK
                EC4A_SYSTEM_ERROR
                EC4A_PARAMETER_ERROR
<Description>:  ��ȡ���������״̬
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
IN: notype  none <TRACE_ON> <����:��>
OUT:    notype  none <TRACE_ON> <����:��>
INOUT:  notype  none <TRACE_ON> <����:��>
<Timeout>:      60
<Server>:       Default
<Returns>:      OK
                EC4A_SYSTEM_ERROR
<Description>:  ��ȡ�ⲿ����
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4A_import_dependence_data ();


/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_update_mc>
{
<InterfaceType>: FUNCTION<Blocking>
<Parameters>
IN: notype  none <TRACE_ON> <����:��>
OUT:    notype  none <TRACE_ON> <����:��>
INOUT:  notype  none <TRACE_ON> <����:��>
<Timeout>:      60
<Server>:       Default
<Returns>:      OK
                EC4A_SYSTEM_ERROR
<Description>:  ���»���������ECû�л�������������Ϊ��
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4A_update_mc ();


/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_set_sim_mode>
{
<InterfaceType>: FUNCTION<Blocking>
<Parameters>
IN: TR4A_SIM_MODE sim_mode <TRACE_ON> <����:��>
IN: TR4A_TRACE_MODE trace_mode <TRACE_ON> <����:��>
IN: TR4A_REQ_MODE data_mode <TRACE_ON> <����:��>
OUT:    notype  none <TRACE_ON> <����:��>
INOUT:  notype  none <TRACE_ON> <����:��>
<Timeout>:      60
<Server>:       Default
<Returns>:      OK
                EC4A_SYSTEM_ERROR
                EC4A_ILLEGAL_CALL_ERROR
                EC4A_PARAMETER_ERROR
<Description>:  ���÷���ģʽ
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
IN: notype  none <TRACE_ON> <����:��>
OUT:    TR4A_SIM_MODE *sim_mode <TRACE_ON> <����:��>
OUT:    TR4A_TRACE_MODE *trace_mode <TRACE_ON> <����:��>
OUT:    TTR4A_REQ_MODE *data_mode <TRACE_ON> <����:��>
INOUT:  notype  none <TRACE_ON> <����:��>
<Timeout>:      60
<Server>:       Default
<Returns>:      OK
                EC4A_SYSTEM_ERROR
                EC4A_PARAMETER_ERROR
<Description>:  ��ȡ����ģʽ
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
IN: EC4A_LOT_DATA_STRUCT *lot_data_p <TRACE_ON> <����:������>
OUT:SMEE_INT32 *nr_of_reticles		<TRACE_ON> <����:��ģ����>
OUT:EC4A_IMAGE_ROUTE_STRUCT image_route[MAX_RET_NR_PER_LOT] <TRACE_ON> <����:ͼ��˳��>
INOUT:  notype  none <TRACE_ON> <����:��>
<Timeout>:      180
<Server>:       Default
<Returns>:      OK
                EC4A_ILLEGAL_CALL_ERROR
                EC4A_SYSTEM_ERROR
<Description>: ��ʼlot��
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
IN: notype  none <TRACE_ON> <����:��>
OUT:    notype  none <TRACE_ON> <����:��>
INOUT:  notype  none <TRACE_ON> <����:��>
<Timeout>:      60
<Server>:       Default
<Returns>:      OK
                EC4A_ILLEGAL_CALL_ERROR
                EC4A_SYSTEM_ERROR
<Description>:  ��ֹlot 
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4A_finish_lot ();


/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_measure_substrate>
{
<InterfaceType>: FUNCTION<Blocking/NonbBlocking/Fcn/Trigger>
<Parameters>
IN: SMEE_INT32 substrate_index <TRACE_ON> <����:�������>
IN: SMEE_BOOL first_substrate <TRACE_ON> <����:�Ƿ������е�һ������>
OUT:   EC4A_ALIGN_RECIPE_STRUCT *wafer_result <TRACE_ON> <����:�����������>
OUT:    notype none <TRACE_OFF> <����:��>
INOUT:  notype  none <TRACE_ON> <����:��>
<Timeout>:      1800
<Server>:       Default
<Returns>:      OK
                EC4A_ILLEGAL_CALL_ERROR
                EC4A_SYSTEM_ERROR
<Description>: ��������
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
IN: EC4A_measure_substrate_done_sb  proc <TRACE_ON> <����:��>
IN: void * context_p <TRACE_OFF> <����:��������>
OUT: SMEE_INT32 *handle_p <TRACE_ON> <����:���ľ��>
INOUT:  notype  none <TRACE_ON> <����:��>
<Timeout>:      60
<Server>:       Default
<Returns>:      OK
                EC4A_ILLEGAL_CALL_ERROR
                EC4A_PARAMETER_ERROR
                EC4A_SYSTEM_ERROR
<Description>:  ��ɲ��������¼����Ľӿ�
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
IN: SMEE_INT32  handle <TRACE_ON> <����:���ľ��>
OUT: notype none <TRACE_ON> <����:��>
INOUT:  notype  none <TRACE_ON> <����:��>
<Timeout>:      60
<Server>:       Default
<Returns>:      OK
                EC4A_ILLEGAL_CALL_ERROR
                EC4A_SYSTEM_ERROR
<Description>:  ��ɲ��������¼������Ľӿ�
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4A_measure_substrate_done_unsubscribe (
    IN SMEE_INT32 handle );

/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_get_measure_substrate_result>
{
<InterfaceType>:   FUNCTION<Blocking>
<Parameters>
IN:  notype  none <TRACE_ON> <����:��>
OUT: EC4A_SUBSTRATE_LOG_STRUCT  *measure_result <TRACE_ON> <����:��ƽ���>
INOUT:  notype  none <TRACE_ON> <����:��>
<Timeout>:      60
<Server>:       Default
<Returns>:      OK
                EC4A_ILLEGAL_CALL_ERROR
                EC4A_PARAMETER_ERROR
                EC4A_SYSTEM_ERROR
<Description>:  ��ȡ����������
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4A_get_measure_substrate_result (
    OUT EC4A_SUBSTRATE_LOG_STRUCT  *measure_result);


/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_expose_image>
{
<InterfaceType>: FUNCTION<Blocking/NonbBlocking/Fcn/Trigger>
<Parameters>
IN: SMEE_CHAR image_id[EC4A_IMAGE_ID_LEN] <TRACE_ON> <����:ͼ��id>
OUT:   EC4A_FIELD_LOG_STRUCT field_result[MAX_FLD_NR_PER_IMG]  <TRACE_OFF> <����:ͼ���ع���>
OUT:  EC4A_IMAGE_STATE_ENUM *image_state  <TRACE_OFF> <����:���ع�״̬>
INOUT:  notype  none <TRACE_ON> <����:��>
<Timeout>:      3600
<Server>:       Default
<Returns>:      OK
                EC4A_ILLEGAL_CALL_ERROR
                EC4A_SYSTEM_ERROR
<Description>:  �ع�ͼ��
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
IN: EC4A_IMAGE_LOG_STRUCT  result <TRACE_OFF><����:��׼���>
IN: EC4A_FIELD_LOG_STRUCT expose_result[MAX_FLD_NR_PER_IMG]<TRACE_OFF><����:ͼ���ع���ɽ��>
IN: EC4A_IMAGE_STATE_ENUM image_state <TRACE_OFF><����:ͼ����>
IN: EC4A_image_done_sb  proc <TRACE_ON> <����:��>
IN: void * context_p <TRACE_OFF> <����:��������>
OUT: SMEE_INT32 *handle_p <TRACE_ON> <����:���ľ��>
INOUT:  notype  none <TRACE_ON> <����:��>
<Timeout>:      60
<Server>:       Default
<Returns>:      OK
                EC4A_ILLEGAL_CALL_ERROR
                EC4A_PARAMETER_ERROR
                EC4A_SYSTEM_ERROR
<Description>:  ͼ���ع�����¼����Ľӿ�
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
IN: SMEE_INT32  handle <TRACE_ON> <����:���ľ��>
OUT: notype none <TRACE_ON> <����:��>
INOUT:  notype  none <TRACE_ON> <����:��>
<Timeout>:      60
<Server>:       Default
<Returns>:      OK
                EC4A_ILLEGAL_CALL_ERROR
                EC4A_SYSTEM_ERROR
<Description>:  ͼ���ع�����¼������Ľӿ�
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4A_image_done_unsubscribe (
    IN SMEE_INT32 handle );

/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_get_image_result>
{
<InterfaceType>:   FUNCTION<Blocking>
<Parameters>
IN:  notype  none <TRACE_ON> <����:��>
OUT: EC4A_IMAGE_LOG_STRUCT  *align_result <TRACE_ON> <����:��׼���>
INOUT:  notype  none <TRACE_ON> <����:��>
<Timeout>:      60
<Server>:       Default
<Returns>:      OK
                EC4A_ILLEGAL_CALL_ERROR
                EC4A_SYSTEM_ERROR
<Description>:  ��ȡ��׼���
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4A_get_image_result (OUT EC4A_IMAGE_LOG_STRUCT  *align_result);


/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_abort_lot>
{
<InterfaceType>: FUNCTION<Blocking>
<Parameters>
IN: SMEE_INT32  notype none <TRACE_OFF> <����:��>
OUT: notype none <TRACE_OFF> <����:��>
INOUT:  notype  none <TRACE_OFF> <����:��>
<Timeout>:      60
<Server>:       ECXE_MAIN
<Returns>:      OK
                EC4A_SYSTEM_ERROR
<Description>:  �û���ֹabort�ع�
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4A_abort_lot ();


/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_wafer_align_begin_sb>
{
<InterfaceType>:    EVENT<>
<Parameters>
    IN:             EC4A_wafer_align_begin_sb    proc     <TRACE_ON> <����:��>
    OUT:            SMEE_INT32                      *handle_p   <TRACE_ON> <����:���>
    INOUT:         void                          *context_p <TRACE_ON> <����:��>
<Timeout>:          60
<Server>:           Default
<Returns>:          OK
                    EC4A_SYSTEM_ERROR
<Description>:      ֪ͨ�ͻ���OILO��ʼ��ͼ����
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
IN: SMEE_INT32  handle <TRACE_ON> <����:���ľ��>           
OUT: notype none <TRACE_ON> <����:��>
INOUT:  notype  none <TRACE_ON> <����:��>
<Timeout>:      60
<Server>:       Default
<Returns>:      OK
                EC4A_ILLEGAL_CALL_ERROR
                EC4A_SYSTEM_ERROR
<Description>:֪ͨOILO��ʼ��ͼȡ������
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4A_wafer_align_begin_unsubscribe(
    IN SMEE_INT32                       handle);


/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_mark_align_begin_subscribe>
{
<InterfaceType>:    EVENT<>
<Parameters>
    IN:             EC4A_mark_align_begin_sb    proc     <TRACE_ON> <����:��>
    OUT:            SMEE_INT32                      *handle_p   <TRACE_ON> <����:���>
    INOUT:         void                          *context_p <TRACE_ON> <����:��>
<Timeout>:          60
<Server>:           ECXE_MAIN
<Returns>:          OK
                    EC4A_SYSTEM_ERROR
<Description>:      ֪ͨ�ͻ���OIAL����׼���ͺͶ�׼id��ע�ắ����
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
IN: SMEE_INT32  handle <TRACE_ON> <����:���ľ��>           
OUT: notype none <TRACE_ON> <����:��>
INOUT:  notype  none <TRACE_ON> <����:��>
<Timeout>:      60
<Server>:       ECXE_MAIN
<Returns>:      OK
                EC4A_ILLEGAL_CALL_ERROR
                EC4A_SYSTEM_ERROR
<Description>: ��ǿ�ʼȡ�����Ľӿ�    
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4A_mark_align_begin_unsubscribe(
    IN SMEE_INT32                       handle);


/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_mark_align_end_subscribe>
{
<InterfaceType>:    EVENT<>
<Parameters>
    IN:              EC4A_mark_align_end_sb    proc<TRACE_ON> <����:��׼id>
    OUT:          SMEE_INT32   *handle_p  <TRACE_ON> <����:��>
    INOUT:          void    *context_p  <TRACE_ON> <����:��>
<Timeout>:          60
<Server>:           ECXE_MAIN
<Returns>:          OK
                    EC4A_SYSTEM_ERROR
<Description>:      ֪ͨOIAL����׼���ͺͶ�׼id��ƥ��ȡ�ע�ắ����
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
IN: SMEE_INT32  handle <TRACE_ON> <����:���ľ��>           
OUT: notype none <TRACE_ON> <����:��>
INOUT:  notype  none <TRACE_ON> <����:��>
<Timeout>:      60
<Server>:       ECXE_MAIN
<Returns>:      OK
                EC4A_ILLEGAL_CALL_ERROR
                EC4A_SYSTEM_ERROR
<Description>: ��ǽ���ȡ�����Ľӿ�    
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4A_mark_align_end_unsubscribe(IN SMEE_INT32 handle);

/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_ui_massage_event_subscribe>
{
<InterfaceType>:    EVENT<>
<Parameters>
IN: EC4A_ui_massage_event_sb  proc <TRACE_ON> <����:��>
IN: void * context_p <TRACE_OFF> <����:��������>
OUT: SMEE_INT32 *handle_p <TRACE_ON> <����:���ľ��>
INOUT:  notype  none <TRACE_ON> <����:��>
<Timeout>:      60
<Server>:       Default
<Returns>:      OK
                EC4A_ILLEGAL_CALL_ERROR
                EC4A_PARAMETER_ERROR
                EC4A_SYSTEM_ERROR
<Description>:  �û���Ϣ�¼����ĺͷ����Ľӿڡ�
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
IN: SMEE_INT32  handle <TRACE_ON> <����:���ľ��>           
OUT: notype none <TRACE_ON> <����:��>
INOUT:  notype  none <TRACE_ON> <����:��>
<Timeout>:      60
<Server>:       Default
<Returns>:      OK
                EC4A_ILLEGAL_CALL_ERROR
                EC4A_SYSTEM_ERROR
<Description>:  �û���Ϣ�¼����Ľӿ�    
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4A_ui_message_event_unsubscribe (
    IN SMEE_INT32 handle );

/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_save_align_offset_event_subscribe>
{
<InterfaceType>:    EVENT<>
<Parameters>
IN: EC4A_save_align_offset_event_sb  proc <TRACE_ON> <����:��>
IN: void * context_p <TRACE_OFF> <����:��������>
OUT: SMEE_INT32 *handle_p <TRACE_ON> <����:���ľ��>
INOUT:  notype  none <TRACE_ON> <����:��>
<Timeout>:      60
<Server>:       Default
<Returns>:      OK
                EC4A_ILLEGAL_CALL_ERROR
                EC4A_PARAMETER_ERROR
                EC4A_SYSTEM_ERROR
<Description>:  �����׼ƫ���¼����ĺͷ����Ľӿڡ�
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
IN: SMEE_INT32  handle <TRACE_ON> <����:���ľ��>           
OUT: notype none <TRACE_ON> <����:��>
INOUT:  notype  none <TRACE_ON> <����:��>
<Timeout>:      60
<Server>:       Default
<Returns>:      OK
                EC4A_ILLEGAL_CALL_ERROR
                EC4A_SYSTEM_ERROR
<Description>:  �����׼ƫ���¼�ȡ�����Ľӿ�    
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4A_save_align_offset_event_unsubscribe (
    IN SMEE_INT32 handle );


/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_exposure_begin_subscribe>
{
<InterfaceType>:    EVENT<>
<Parameters>
IN: EC4A_exposure_begin_sb  proc <TRACE_ON> <����:��>
IN: void * handle_p <TRACE_OFF> <����:��������>                
OUT: notype  none <TRACE_ON> <����:��>
INOUT: void *context_p <TRACE_ON> <����:���ľ��>
<Timeout>:      60
<Server>:       ECXE_MAIN
<Returns>:      OK
                EC4A_ILLEGAL_CALL_ERROR
                EC4A_PARAMETER_ERROR
                EC4A_SYSTEM_ERROR
<Description>:  ���ع⿪ʼ�¼����Ľӿ�  
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
IN: SMEE_INT32  handle <TRACE_ON> <����:���ľ��>           
OUT: notype none <TRACE_ON> <����:��>
INOUT:  notype  none <TRACE_ON> <����:��>
<Timeout>:      60
<Server>:       ECXE_MAIN
<Returns>:      OK
                EC4A_ILLEGAL_CALL_ERROR
                EC4A_PARAMETER_ERROR
                EC4A_SYSTEM_ERROR
<Description>:  ���ع⿪ʼ�¼�ȡ�����Ľӿ�  
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4A_exposure_begin_unsubscribe(IN SMEE_INT32 handle);

/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_exposure_end_subscribe>
{
<InterfaceType>:    EVENT<>
<Parameters>
IN: EC4A_exposure_end_sb  proc <TRACE_ON> <����:��>
IN: void * context_p <TRACE_OFF> <����:��������>                
OUT: SMEE_INT32 *handle_p <TRACE_ON> <����:���ľ��>
INOUT:  notype  none <TRACE_ON> <����:��>
<Timeout>:      60
<Server>:       Default
<Returns>:      OK
                EC4A_ILLEGAL_CALL_ERROR
                EC4A_PARAMETER_ERROR
                EC4A_SYSTEM_ERROR
<Description>:  ���ع�����¼����Ľӿ�  
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
IN: SMEE_INT32  handle <TRACE_ON> <����:���ľ��>           
OUT: notype none <TRACE_ON> <����:��>
INOUT:  notype  none <TRACE_ON> <����:��>
<Timeout>:      60
<Server>:       Default
<Returns>:      OK
                EC4A_ILLEGAL_CALL_ERROR
                EC4A_PARAMETER_ERROR
                EC4A_SYSTEM_ERROR
<Description>:  ���ع�����¼�ȡ�����Ľӿ�  
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4A_exposure_end_unsubscribe(IN SMEE_INT32 handle);

/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_field_done_subscribe>
{
<InterfaceType>:    EVENT<>
<Parameters>
IN: EC4A_exposure_end_sb  proc <TRACE_ON> <����:��>
IN: void * context_p <TRACE_OFF> <����:��������>                
OUT: SMEE_INT32 *handle_p <TRACE_ON> <����:���ľ��>
INOUT:  notype  none <TRACE_ON> <����:��>
<Timeout>:      60
<Server>:       Default
<Returns>:      OK
                EC4A_ILLEGAL_CALL_ERROR
                EC4A_PARAMETER_ERROR
                EC4A_SYSTEM_ERROR
<Description>:  ���ع�����¼����Ľӿ�  
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
IN: SMEE_INT32  handle <TRACE_ON> <����:���ľ��>           
OUT: notype none <TRACE_ON> <����:��>
INOUT:  notype  none <TRACE_ON> <����:��>
<Timeout>:      60
<Server>:       Default
<Returns>:      OK
                EC4A_ILLEGAL_CALL_ERROR
                EC4A_PARAMETER_ERROR
                EC4A_SYSTEM_ERROR
<Description>:  ���ع�����¼�ȡ�����Ľӿ�  
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4A_field_done_unsubscribe(IN SMEE_INT32 handle);


/******************************************************************************
INTERFACE <SMEE_INT32 EC4A_get_substrate_loading_offset_for_retry>
{
<InterfaceType>:   FUNCTION<Blocking>
<Parameters>
IN:  notype  none <TRACE_ON> <����:��>
OUT: xyrz_vect loading_offset <TRACE_ON> <����:��Ƭ�ϰ�ƫ��>
INOUT:  notype  none <TRACE_ON> <����:��>
<Timeout>:      60
<Server>:       Default
<Returns>:      OK
                EC4A_ILLEGAL_CALL_ERROR
                EC4A_SYSTEM_ERROR
<Description>:  LOT���Ի�ȡ��Ƭ�ϰ�ƫ��
}
******************************************************************************/
SMEE_EXPORT SMEE_INT32 EC4A_get_substrate_loading_offset_for_retry(
    OUT xyrz_vect *loading_offset);

SMEE_EXPORT SMEE_INT32 EC4A_no_param(void);

#endif /* EC4A_IF_H */

