/**************************************************************************
* Copyright (C) 2008, 上海微电子装备有限公司
* All rights reserved.
* 产品号 : SS A600/20
* 所属组件 : EC
* 模块名称 : ECVT
* 文件名称 : ECVT.cpp
* 概要描述 :
* 历史记录 :
* 版本    日期         作者        内容

**************************************************************************/

#include "ECVTGeneral.h"

ECVTGeneral::ECVTGeneral(QWidget *parent)
    :SMEE::Widget(parent), m_func((EC4A_GENERAL_FUNCTION_CODE_ENUM)(-1))
{
    setupUi(this);

    SwichButtonG = new QButtonGroup;//创建按钮组
    SwichButtonG->addButton(EC4A_initialize_qpb,(int)EC4A_INITIALIZE);
    SwichButtonG->addButton(EC4A_terminate_qpb,(int)EC4A_TERMINATE);
    SwichButtonG->addButton(EC4A_get_status_qpb,(int)EC4A_GET_STATUS);
    SwichButtonG->addButton(EC4A_update_mc_qpb,(int)EC4A_UPDATE_MC);
    SwichButtonG->addButton(EC4A_set_sim_mode_qpb,(int)EC4A_SET_SIM_MODE);
    SwichButtonG->addButton(EC4A_get_sim_mode_qpb,(int)EC4A_GET_SIM_MODE);
    SwichButtonG->setExclusive(true);
    connect(
    	SwichButtonG,
     	SIGNAL(buttonClicked(int)),
    	this,
    	SLOT(performButtonClickedSlot(int)));	
}

ECVTGeneral::~ECVTGeneral()
{

}


void ECVTGeneral::disablePerformButtonSlot()
{
	int i;
	for (i=EC4A_GENERAL_FUNCTION_CODE_MIN+1; i < EC4A_GENERAL_FUNCTION_CODE_MAX; i++)
	{
		if (SwichButtonG->button(i))
		{
			SwichButtonG->button(i)->setEnabled(false);
		}
	}
}

void ECVTGeneral::enablePerformButtonSlot()
{
	int i;
	for (i=EC4A_GENERAL_FUNCTION_CODE_MIN+1; i < EC4A_GENERAL_FUNCTION_CODE_MAX; i++)
	{
		if (SwichButtonG->button(i))
		{
			SwichButtonG->button(i)->setEnabled(true);
		}
	}
	updateWindowData();
}

//刷新界面数据
void ECVTGeneral::updateWindowData()//slot
{
	switch (m_func)
	{
	case EC4A_INITIALIZE:
    	break;
        //输出信息到输出栏
	case EC4A_TERMINATE:
    	break;
        //输出信息到输出栏
	case EC4A_GET_STATUS:
        switch(u_param.param_EC4A_get_status.status.status)
        {
        case EC4A_ST_STATUS_IDLE:
        			EC4A_get_status__status_status_qle->setText("IDLE");
            break;
        case EC4A_ST_STATUS_TERMINATE:
        			EC4A_get_status__status_status_qle->setText("TERMINATED");
            break;
        case EC4A_ST_STATUS_START_LOT:
        			EC4A_get_status__status_status_qle->setText("START_LOT");
            break;
		 case EC4A_ST_STATUS_START_SUBSTRATE:
        			EC4A_get_status__status_status_qle->setText("START_SUBSTRATE");
            break;
		/* case EC4A_ST_STATUS_START_IMAGE:
        			EC4A_get_status__status_status_qle->setText("START_IMAGE");
            break;*/
        default:
        			EC4A_get_status__status_status_qle->setText("UNKNOWN");
            break;
        }
    	break;
        //输出信息到输出栏
	case EC4A_UPDATE_MC:
    	break;
        //输出信息到输出栏
	case EC4A_SET_SIM_MODE:
    	break;
        //输出信息到输出栏
	case EC4A_GET_SIM_MODE:
        switch(u_param.param_EC4A_get_sim_mode.sim_mode)
        {
        case TR4A_SIM_DISABLED:
			EC4A_set_sim_mode__sim_mode_qcb->setCurrentIndex(0);
            break;
        case TR4A_SIM_MODE_1:
			EC4A_set_sim_mode__sim_mode_qcb->setCurrentIndex(1);
            break;
        case TR4A_SIM_MODE_2:
			EC4A_set_sim_mode__sim_mode_qcb->setCurrentIndex(2);
            break;
		case TR4A_SIM_MODE_3:
			EC4A_set_sim_mode__sim_mode_qcb->setCurrentIndex(3);
            break;
        case TR4A_SIM_MODE_4:
			EC4A_set_sim_mode__sim_mode_qcb->setCurrentIndex(4);
            break;
        default:
			//EC4A_set_sim_mode__sim_mode_qcb->setCurrentIndex(-1);
            break;
        }
        switch(u_param.param_EC4A_get_sim_mode.trace_mode)
        {
        case TR4A_TRACE_DISABLED:
			EC4A_set_sim_mode__trace_mode_qcb->setCurrentIndex(0);
            break;
        case TR4A_TRACE_INT:
			EC4A_set_sim_mode__trace_mode_qcb->setCurrentIndex(1);
            break;
        case TR4A_TRACE_EXT:
			EC4A_set_sim_mode__trace_mode_qcb->setCurrentIndex(2);
            break;
        case TR4A_TRACE_INT_EXT:
			EC4A_set_sim_mode__trace_mode_qcb->setCurrentIndex(3);
            break;
		case TR4A_TRACE_REAL_TIME:
			EC4A_set_sim_mode__trace_mode_qcb->setCurrentIndex(4);
			break;
		case TR4A_INT_REAL:
			EC4A_set_sim_mode__trace_mode_qcb->setCurrentIndex(5);
			break;
		case TR4A_EXT_REAL:
			EC4A_set_sim_mode__trace_mode_qcb->setCurrentIndex(6);
			break;
		case TR4A_TRACE_INT_EXT_REAL:
			EC4A_set_sim_mode__trace_mode_qcb->setCurrentIndex(7);
			break;
        default:
			//EC4A_set_sim_mode__trace_mode_qcb->setCurrentIndex(-1);
            break;
        }
        switch(u_param.param_EC4A_get_sim_mode.data_mode)
        {
        case TR4A_REQ_DISABLED:
			EC4A_set_sim_mode__data_mode_qcb->setCurrentIndex(0);
            break;
        case TR4A_REQ_INT_INPUT:
			EC4A_set_sim_mode__data_mode_qcb->setCurrentIndex(1);
            break;
        case TR4A_REQ_INT_OUTPUT:
			EC4A_set_sim_mode__data_mode_qcb->setCurrentIndex(2);
            break;
        case TR4A_REQ_INT_INOUT:
			EC4A_set_sim_mode__data_mode_qcb->setCurrentIndex(3);
            break;
        case TR4A_REQ_EXT_INPUT:
			EC4A_set_sim_mode__data_mode_qcb->setCurrentIndex(4);
            break;
        case TR4A_REQ_EXT_OUTPUT:
			EC4A_set_sim_mode__data_mode_qcb->setCurrentIndex(5);
            break;
        case TR4A_REQ_EXT_INOUT:
			EC4A_set_sim_mode__data_mode_qcb->setCurrentIndex(6);
            break;
        case TR4A_REQ_INT_EXT_INPUT:
			EC4A_set_sim_mode__data_mode_qcb->setCurrentIndex(7);
            break;
        case TR4A_REQ_INT_EXT_OUTPUT:
			EC4A_set_sim_mode__data_mode_qcb->setCurrentIndex(8);
            break;
        case TR4A_REQ_INT_EXT_INOUT:
			EC4A_set_sim_mode__data_mode_qcb->setCurrentIndex(9);
            break;
        default:
			//EC4A_set_sim_mode__data_mode_qcb->setCurrentIndex(-1);
            break;
        }
    	break;
        //输出信息到输出栏
	default:
		break;
	}
}
//****************传递信息********************************************************************************************
void ECVTGeneral::m_log(int flag,const QString title,const QString text)
{
	emit send_log(flag,title,text);
}
void ECVTGeneral::outputStart( QString fun_name)
{
	m_log(OK,QString("ECVT"),QString("%1 start.").arg(fun_name));
}

void ECVTGeneral::outputEnd( QString fun_name,int rtn)
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

//----------------------------------
void ECVTGeneral::performButtonClickedSlot(int button_id)
{
	if (button_id > EC4A_GENERAL_FUNCTION_CODE_MIN && button_id < EC4A_GENERAL_FUNCTION_CODE_MAX)
	{
		m_func = EC4A_GENERAL_FUNCTION_CODE_ENUM(button_id);
		emit performFuncSignal(button_id);
	}
}
void ECVTGeneral::performFunction(int funcCode)
{
    switch(funcCode)
    {
    case EC4A_INITIALIZE:
        m_exec_EC4A_initialize();
        break;
    case EC4A_TERMINATE:
        m_exec_EC4A_terminate();
        break;
    case EC4A_GET_STATUS:
        m_exec_EC4A_get_status();
        break;
    case EC4A_UPDATE_MC:
        m_exec_EC4A_update_mc();
        break;
    case EC4A_SET_SIM_MODE:
        m_exec_EC4A_set_sim_mode();
        break;
    case EC4A_GET_SIM_MODE:
        m_exec_EC4A_get_sim_mode();
        break;
    default:
        //m_ecvt->m_log(QString("ERROR!Can't find corresponding func code."));
        break;
    }
}

void ECVTGeneral::m_exec_EC4A_initialize()
{
    int error_code = OK;

	QString func_name = "EC4A_initialize";
	//输出信息到输出栏
	outputStart(func_name);
    //获取输入参数

    //执行函数
    error_code = EC4A_initialize();

    //更新界面
    outputEnd(func_name,error_code);
}

void ECVTGeneral::m_exec_EC4A_terminate()
{
    int error_code = OK;

	QString func_name = "EC4A_terminate";
	//输出信息到输出栏
	outputStart(func_name);
    //获取输入参数

    //执行函数
    error_code = EC4A_terminate();

    //更新界面
    outputEnd(func_name,error_code);
}

void ECVTGeneral::m_exec_EC4A_get_status()
{
    int error_code = OK;

	QString func_name = "EC4A_get_status";
	//输出信息到输出栏
	outputStart(func_name);
    //获取输入参数

    //执行函数
    error_code = EC4A_get_status(&u_param.param_EC4A_get_status.status);

    //更新界面
    outputEnd(func_name,error_code);
}

void ECVTGeneral::m_exec_EC4A_update_mc()
{
    int error_code = OK;

	QString func_name = "EC4A_update_mc";
	//输出信息到输出栏
	outputStart(func_name);
    //获取输入参数

    //执行函数
    error_code = EC4A_update_mc();

    //更新界面
    outputEnd(func_name,error_code);
}

void ECVTGeneral::m_exec_EC4A_set_sim_mode()
{
    int error_code = OK;

	QString func_name = "EC4A_set_sim_mode";
	//输出信息到输出栏
	outputStart(func_name);
    //获取输入参数
    switch(EC4A_set_sim_mode__sim_mode_qcb->currentIndex())
    {
    case 0:
    u_param.param_EC4A_set_sim_mode.sim_mode = TR4A_SIM_DISABLED;
        break;
    case 1:
    u_param.param_EC4A_set_sim_mode.sim_mode = TR4A_SIM_MODE_1;
        break;
    case 2:
    u_param.param_EC4A_set_sim_mode.sim_mode = TR4A_SIM_MODE_2;
        break;
	case 3:
    u_param.param_EC4A_set_sim_mode.sim_mode = TR4A_SIM_MODE_3;
        break;
    case 4:
    u_param.param_EC4A_set_sim_mode.sim_mode = TR4A_SIM_MODE_4;
        break;
    default:
        //m_log(QString("EC4A_set_sim_mode: Enum Parameter Error!"));
        break;
    }
    switch(EC4A_set_sim_mode__trace_mode_qcb->currentIndex())
    {
    case 0:
    u_param.param_EC4A_set_sim_mode.trace_mode = TR4A_TRACE_DISABLED;
        break;
    case 1:
    u_param.param_EC4A_set_sim_mode.trace_mode = TR4A_TRACE_INT;
        break;
    case 2:
    u_param.param_EC4A_set_sim_mode.trace_mode = TR4A_TRACE_EXT;
        break;
    case 3:
    u_param.param_EC4A_set_sim_mode.trace_mode = TR4A_TRACE_INT_EXT;
        break;
	case 4:
	u_param.param_EC4A_set_sim_mode.trace_mode = TR4A_TRACE_REAL_TIME;
		break;
	case 5:
	u_param.param_EC4A_set_sim_mode.trace_mode = TR4A_INT_REAL;
		break;
	case 6:
	u_param.param_EC4A_set_sim_mode.trace_mode = TR4A_EXT_REAL;
		break;
	case 7:
	u_param.param_EC4A_set_sim_mode.trace_mode = TR4A_TRACE_INT_EXT_REAL;
		break;
    default:
        //m_log(QString("EC4A_set_sim_mode: Enum Parameter Error!"));
        break;
    }
    switch(EC4A_set_sim_mode__data_mode_qcb->currentIndex())
    {
    case 0:
    u_param.param_EC4A_set_sim_mode.data_mode = TR4A_REQ_DISABLED;
        break;
    case 1:
    u_param.param_EC4A_set_sim_mode.data_mode = TR4A_REQ_INT_INPUT;
        break;
    case 2:
    u_param.param_EC4A_set_sim_mode.data_mode = TR4A_REQ_INT_OUTPUT;
        break;
    case 3:
    u_param.param_EC4A_set_sim_mode.data_mode = TR4A_REQ_INT_INOUT;
        break;
    case 4:
    u_param.param_EC4A_set_sim_mode.data_mode = TR4A_REQ_EXT_INPUT;
        break;
    case 5:
    u_param.param_EC4A_set_sim_mode.data_mode = TR4A_REQ_EXT_OUTPUT;
        break;
    case 6:
    u_param.param_EC4A_set_sim_mode.data_mode = TR4A_REQ_EXT_INOUT;
        break;
    case 7:
    u_param.param_EC4A_set_sim_mode.data_mode = TR4A_REQ_INT_EXT_INPUT;
        break;
    case 8:
    u_param.param_EC4A_set_sim_mode.data_mode = TR4A_REQ_INT_EXT_OUTPUT;
        break;
    case 10:
    u_param.param_EC4A_set_sim_mode.data_mode = TR4A_REQ_INT_EXT_INOUT;
        break;
    default:
        //m_log(QString("EC4A_set_sim_mode: Enum Parameter Error!"));
        break;
    }

    //执行函数
    error_code = EC4A_set_sim_mode(u_param.param_EC4A_set_sim_mode.sim_mode, 
								u_param.param_EC4A_set_sim_mode.trace_mode, 
								u_param.param_EC4A_set_sim_mode.data_mode);

    //更新界面
    outputEnd(func_name,error_code);
}

void ECVTGeneral::m_exec_EC4A_get_sim_mode()
{
    int error_code = OK;

	QString func_name = "EC4A_get_sim_mode";
	//输出信息到输出栏
	outputStart(func_name);
    //获取输入参数

    //执行函数
    error_code = EC4A_get_sim_mode(&u_param.param_EC4A_get_sim_mode.sim_mode, 
								&u_param.param_EC4A_get_sim_mode.trace_mode, 
								&u_param.param_EC4A_get_sim_mode.data_mode);

    //更新界面
    outputEnd(func_name,error_code);
}

