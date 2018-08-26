#include "ECVTMaintenance.h"
ECVTMaintenance::ECVTMaintenance(QWidget *parent)
	:SMEE::Widget(parent), m_func((ECVT_MAINTENANCE_FUNCTION_CODE_ENUM)(-1))
{
	setupUi(this);
	SwichButtonG = new QButtonGroup;//创建按钮组
	SwichButtonG->addButton(EC4T_do_global_level_on_substrate_qpb,(int)EC4T_DO_GLOBAL_LEVEL_ON_SUBSTRATE);
	SwichButtonG->addButton(EC4T_do_global_level_on_ws_fiducial_qpb,(int)EC4T_DO_GLOBAL_LEVEL_ON_WS_FIDUCIAL);
	SwichButtonG->addButton(EC4T_reticle_align_qpb,(int)EC4T_RETICLE_ALIGN);
	SwichButtonG->addButton(EC4T_TTL_align_qpb,(int)EC4T_TTL_ALIGN);
	SwichButtonG->addButton(EC4T_search_focus_qpb,(int)EC4T_SEARCH_FOCUS);
	SwichButtonG->addButton(EC4T_set_ws_position_all_by_fls_qpb,(int)EC4T_SET_WS_POSITION_ALL_BY_FLS);
	SwichButtonG->addButton(EC4T_wa_align_qpb,(int)EC4T_WA_ALIGN);
	SwichButtonG->addButton(EC4T_substrate_align_qpb,(int)EC4T_SUBSTRATE_ALIGN);
	SwichButtonG->addButton(EC4T_update_ttl_baseline_qpb,(int)EC4T_UPDATE_TTL_BASELINE);
	SwichButtonG->addButton(EC4T_update_wa_baseline_qpb,(int)EC4T_UPDATE_WA_BASELINE);
	SwichButtonG->setExclusive(true);
    connect(
    	SwichButtonG,
     	SIGNAL(buttonClicked(int)),
    	this,
    	SLOT(performButtonClickedSlot(int)));
}
ECVTMaintenance::~ECVTMaintenance(){}
void ECVTMaintenance::disablePerformButtonSlot()
{
    int i;
    for (i=ECVT_MAINTENANCE_FUNCTION_CODE_MIN+1; i <ECVT_MAINTENANCE_FUNCTION_CODE_MAX; i++)
    {
        if (SwichButtonG->button(i))
        {
            SwichButtonG->button(i)->setEnabled(false);
        }
    }
}
void ECVTMaintenance::enablePerformButtonSlot()
{
    int i;
    for (i=ECVT_MAINTENANCE_FUNCTION_CODE_MIN+1; i < ECVT_MAINTENANCE_FUNCTION_CODE_MAX; i++)
    {
        if (SwichButtonG->button(i))
        {
            SwichButtonG->button(i)->setEnabled(true);
        }
    }
    updateWindowData();
}
        
//****************传递信息********************************************************************************************
void ECVTMaintenance::m_log(int flag,const QString title,const QString text)
{
    emit send_log(flag,title,text);
}
void ECVTMaintenance::outputStart( QString fun_name)
{
    m_log(OK,QString("ECVT"),QString("%1 start.").arg(fun_name));
}
    
void ECVTMaintenance::outputEnd( QString fun_name,int rtn)
{
    if(rtn == OK)
    {
        m_log(OK,QString("ECVT"),QString("%1 success.").arg(fun_name));
    }
    else
    {
        m_log(rtn,QString("ECVT"),QString("%1 failed.  Error Code:0x%2").arg(fun_name).arg(rtn, 0, 16));
    }
}  
void ECVTMaintenance::performFunction(int funcCode)
{
	switch(funcCode)
	{
        case EC4T_DO_GLOBAL_LEVEL_ON_SUBSTRATE:
            m_exec_EC4T_do_global_level_on_substrate();
            break;
        
        case EC4T_DO_GLOBAL_LEVEL_ON_WS_FIDUCIAL:
            m_exec_EC4T_do_global_level_on_ws_fiducial();
            break;
        
        case EC4T_RETICLE_ALIGN:
            m_exec_EC4T_reticle_align();
            break;
        
        case EC4T_TTL_ALIGN:
            m_exec_EC4T_TTL_align();
            break;
        
        case EC4T_SEARCH_FOCUS:
            m_exec_EC4T_search_focus();
            break;
        
        case EC4T_SET_WS_POSITION_ALL_BY_FLS:
            m_exec_EC4T_set_ws_position_all_by_fls();
            break;
        
        case EC4T_WA_ALIGN:
            m_exec_EC4T_wa_align();
            break;
        
        case EC4T_SUBSTRATE_ALIGN:
            m_exec_EC4T_substrate_align();
            break;
        
        case EC4T_UPDATE_TTL_BASELINE:
            m_exec_EC4T_update_ttl_baseline();
            break;
        
        case EC4T_UPDATE_WA_BASELINE:
            m_exec_EC4T_update_wa_baseline();
            break;
        default:
			break;
	}
}
//刷新界面数据
void ECVTMaintenance::updateWindowData()//slot
{
    switch (m_func)
    {
	case EC4T_DO_GLOBAL_LEVEL_ON_SUBSTRATE:
		break;
	case EC4T_DO_GLOBAL_LEVEL_ON_WS_FIDUCIAL:
		break;
	case EC4T_RETICLE_ALIGN:
		break;
	case EC4T_TTL_ALIGN:
		break;
	case EC4T_SEARCH_FOCUS:
		break;
	case EC4T_SET_WS_POSITION_ALL_BY_FLS:
		break;
	case EC4T_WA_ALIGN:
		break;
	case EC4T_SUBSTRATE_ALIGN:
		break;
	case EC4T_UPDATE_TTL_BASELINE:
		break;
	case EC4T_UPDATE_WA_BASELINE:
		break;
	default:
		break;
	}
}
void ECVTMaintenance::param_range_check() 
	{
	}
void ECVTMaintenance::performButtonClickedSlot(int button_id)
	{ 
		switch (button_id)
		{
			case (int)EC4T_DO_GLOBAL_LEVEL_ON_SUBSTRATE:
				m_func=EC4T_DO_GLOBAL_LEVEL_ON_SUBSTRATE;
				emit performFuncSignal(button_id);
				break;
			case (int)EC4T_DO_GLOBAL_LEVEL_ON_WS_FIDUCIAL:
				m_func=EC4T_DO_GLOBAL_LEVEL_ON_WS_FIDUCIAL;
				emit performFuncSignal(button_id);
				break;
			case (int)EC4T_RETICLE_ALIGN:
				m_func=EC4T_RETICLE_ALIGN;
				emit performFuncSignal(button_id);
				break;
			case (int)EC4T_TTL_ALIGN:
				m_func=EC4T_TTL_ALIGN;
				emit performFuncSignal(button_id);
				break;
			case (int)EC4T_SEARCH_FOCUS:
				m_func=EC4T_SEARCH_FOCUS;
				emit performFuncSignal(button_id);
				break;
			case (int)EC4T_SET_WS_POSITION_ALL_BY_FLS:
				m_func=EC4T_SET_WS_POSITION_ALL_BY_FLS;
				emit performFuncSignal(button_id);
				break;
			case (int)EC4T_WA_ALIGN:
				m_func=EC4T_WA_ALIGN;
				emit performFuncSignal(button_id);
				break;
			case (int)EC4T_SUBSTRATE_ALIGN:
				m_func=EC4T_SUBSTRATE_ALIGN;
				emit performFuncSignal(button_id);
				break;
			case (int)EC4T_UPDATE_TTL_BASELINE:
				m_func=EC4T_UPDATE_TTL_BASELINE;
				emit performFuncSignal(button_id);
				break;
			case (int)EC4T_UPDATE_WA_BASELINE:
				m_func=EC4T_UPDATE_WA_BASELINE;
				emit performFuncSignal(button_id);
				break;
			default:
				m_func=button_id;
				emit performFuncSignal(button_id);
				break;
		}
	}
void ECVTMaintenance::m_exec_EC4T_do_global_level_on_substrate()
	{       
        int error_code = OK;
        int num = 0;
        QString func_name = "EC4T_do_global_level_on_substrate";
        //输出信息到输出栏
        outputStart(func_name);
		u_param.param_EC4T_do_global_level_on_substrate.do_global_level = EC4T_do_global_level_on_substrate_do_global_level_qckb->isChecked();
		//执行函数
		error_code = EC4T_do_global_level_on_substrate(
				u_param.param_EC4T_do_global_level_on_substrate.do_global_level,
				u_param.param_EC4T_do_global_level_on_substrate.do_mapping,
				u_param.param_EC4T_do_global_level_on_substrate.substrate_spec,
				u_param.param_EC4T_do_global_level_on_substrate.substrate_thickness,
				u_param.param_EC4T_do_global_level_on_substrate.user_focus_offset,
				u_param.param_EC4T_do_global_level_on_substrate.global_middle_point,
				u_param.param_EC4T_do_global_level_on_substrate.mapping_route,
				u_param.param_EC4T_do_global_level_on_substrate.level_result_p);
		//更新界面
		outputEnd(func_name,error_code);
	}
void ECVTMaintenance::m_exec_EC4T_do_global_level_on_ws_fiducial()
	{       
        int error_code = OK;
        int num = 0;
        QString func_name = "EC4T_do_global_level_on_ws_fiducial";
        //输出信息到输出栏
        outputStart(func_name);
		u_param.param_EC4T_do_global_level_on_ws_fiducial.substrate_thickness = (SMEE_UM_TO_SI)(EC4T_do_global_level_on_ws_fiducial_substrate_thickness_qlb->value());
		//执行函数
		error_code = EC4T_do_global_level_on_ws_fiducial(
				u_param.param_EC4T_do_global_level_on_ws_fiducial.substrate_thickness,
				u_param.param_EC4T_do_global_level_on_ws_fiducial.user_focus_offset,
				u_param.param_EC4T_do_global_level_on_ws_fiducial.level_result_p,
				u_param.param_EC4T_do_global_level_on_ws_fiducial.substrate_cuniform_p);
		//更新界面
		outputEnd(func_name,error_code);
	}
void ECVTMaintenance::m_exec_EC4T_reticle_align()
	{       
        int error_code = OK;
        int num = 0;
        QString func_name = "EC4T_reticle_align";
        //输出信息到输出栏
        outputStart(func_name);
		u_param.param_EC4T_reticle_align.align_spec.RM1_pos.x = (SMEE_MM_TO_SI)(EC4T_reticle_align_align_spec_RM1_pos_x_qlb->value());
		//执行函数
		error_code = EC4T_reticle_align(
				u_param.param_EC4T_reticle_align.align_spec,
				u_param.param_EC4T_reticle_align.ttl_baseline_result_p,
				u_param.param_EC4T_reticle_align.cora_result_p,
				u_param.param_EC4T_reticle_align.fira_result_p);
		//更新界面
		outputEnd(func_name,error_code);
	}
void ECVTMaintenance::m_exec_EC4T_TTL_align()
	{       
        int error_code = OK;
        int num = 0;
        QString func_name = "EC4T_TTL_align";
        //输出信息到输出栏
        outputStart(func_name);
		u_param.param_EC4T_TTL_align.mark_norminal_pos.x = (SMEE_MM_TO_SI)(EC4T_TTL_align_mark_norminal_pos_x_qlb->value());
		//执行函数
		error_code = EC4T_TTL_align(
				u_param.param_EC4T_TTL_align.mark_norminal_pos,
				u_param.param_EC4T_TTL_align.ttl_align_recipe,
				u_param.param_EC4T_TTL_align.align_result_p);
		//更新界面
		outputEnd(func_name,error_code);
	}
void ECVTMaintenance::m_exec_EC4T_search_focus()
	{       
        int error_code = OK;
        int num = 0;
        QString func_name = "EC4T_search_focus";
        //输出信息到输出栏
        outputStart(func_name);
		u_param.param_EC4T_search_focus.align_type = SMEE_ALIGN_TYPE_ENUM (EC4T_search_focus_align_type_qcb->currintIndex());
		//执行函数
		error_code = EC4T_search_focus(
				u_param.param_EC4T_search_focus.align_type,
				u_param.param_EC4T_search_focus.ePlateType,
				u_param.param_EC4T_search_focus.ws_pos,
				u_param.param_EC4T_search_focus.z_search_range,
				u_param.param_EC4T_search_focus.focused_ws_pos_p,
				u_param.param_EC4T_search_focus.focused_fls_z_p);
		//更新界面
		outputEnd(func_name,error_code);
	}
void ECVTMaintenance::m_exec_EC4T_set_ws_position_all_by_fls()
	{       
        int error_code = OK;
        int num = 0;
        QString func_name = "EC4T_set_ws_position_all_by_fls";
        //输出信息到输出栏
        outputStart(func_name);
		u_param.param_EC4T_set_ws_position_all_by_fls.substrate_spec = SMEE_SUBSTRATE_SIZE_ENUM (EC4T_set_ws_position_all_by_fls_substrate_spec_qcb->currintIndex());
		//执行函数
		error_code = EC4T_set_ws_position_all_by_fls(
				u_param.param_EC4T_set_ws_position_all_by_fls.substrate_spec,
				u_param.param_EC4T_set_ws_position_all_by_fls.wafer_pos,
				u_param.param_EC4T_set_ws_position_all_by_fls.ws_expect_tilt,
				u_param.param_EC4T_set_ws_position_all_by_fls.level_result_p);
		//更新界面
		outputEnd(func_name,error_code);
	}
void ECVTMaintenance::m_exec_EC4T_wa_align()
	{       
        int error_code = OK;
        int num = 0;
        QString func_name = "EC4T_wa_align";
        //输出信息到输出栏
        outputStart(func_name);
		u_param.param_EC4T_wa_align.align_type = SMEE_ALIGN_TYPE_ENUM (EC4T_wa_align_align_type_qcb->currintIndex());
		//执行函数
		error_code = EC4T_wa_align(
				u_param.param_EC4T_wa_align.align_type,
				u_param.param_EC4T_wa_align.wafer_size,
				u_param.param_EC4T_wa_align.mark_nominal_pos,
				u_param.param_EC4T_wa_align.oa_align_recipe,
				u_param.param_EC4T_wa_align.align_result_p);
		//更新界面
		outputEnd(func_name,error_code);
	}
void ECVTMaintenance::m_exec_EC4T_substrate_align()
	{       
        int error_code = OK;
        int num = 0;
        QString func_name = "EC4T_substrate_align";
        //输出信息到输出栏
        outputStart(func_name);
		u_param.param_EC4T_substrate_align.align_type = SMEE_ALIGN_TYPE_ENUM (EC4T_substrate_align_align_type_qcb->currintIndex());
		//执行函数
		error_code = EC4T_substrate_align(
				u_param.param_EC4T_substrate_align.align_type,
				u_param.param_EC4T_substrate_align.wafer_size,
				u_param.param_EC4T_substrate_align.nr_marks,
				u_param.param_EC4T_substrate_align.mark_norminal_positions[EC4T_MAX_NR_SUBSTRATE_MARKS],
				u_param.param_EC4T_substrate_align.oa_align_recipe,
				u_param.param_EC4T_substrate_align.update_oa_baseline_result_p,
				u_param.param_EC4T_substrate_align.align_result_p);
		//更新界面
		outputEnd(func_name,error_code);
	}
void ECVTMaintenance::m_exec_EC4T_update_ttl_baseline()
	{       
        int error_code = OK;
        int num = 0;
        QString func_name = "EC4T_update_ttl_baseline";
        //输出信息到输出栏
        outputStart(func_name);
		//执行函数
		error_code = EC4T_update_ttl_baseline(				u_param.param_EC4T_update_ttl_baseline.ttl_baseline_result_p);
		//更新界面
		outputEnd(func_name,error_code);
	}
void ECVTMaintenance::m_exec_EC4T_update_wa_baseline()
	{       
        int error_code = OK;
        int num = 0;
        QString func_name = "EC4T_update_wa_baseline";
        //输出信息到输出栏
        outputStart(func_name);
		u_param.param_EC4T_update_wa_baseline.align_type = SMEE_ALIGN_TYPE_ENUM (EC4T_update_wa_baseline_align_type_qcb->currintIndex());
		//执行函数
		error_code = EC4T_update_wa_baseline(
				u_param.param_EC4T_update_wa_baseline.align_type,
				u_param.param_EC4T_update_wa_baseline.oa_baseline_result_p);
		//更新界面
		outputEnd(func_name,error_code);
	}
