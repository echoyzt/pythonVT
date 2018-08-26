#include "ECVTGeneral.h"
ECVTGeneral::ECVTGeneral(QWidget *parent)
	:SMEE::Widget(parent), m_func((ECVT_GENERAL_FUNCTION_CODE_ENUM)(-1))
{
	setupUi(this);
	SwichButtonG = new QButtonGroup;//������ť��
	SwichButtonG->addButton(EC4A_get_status_qpb,(int)EC4A_GET_STATUS);
	SwichButtonG->addButton(EC4A_get_sim_mode_qpb,(int)EC4A_GET_SIM_MODE);
	SwichButtonG->addButton(EC4A_set_sim_mode_qpb,(int)EC4A_SET_SIM_MODE);
	SwichButtonG->setExclusive(true);
    connect(
    	SwichButtonG,
     	SIGNAL(buttonClicked(int)),
    	this,
    	SLOT(performButtonClickedSlot(int)));
}
ECVTGeneral::~ECVTGeneral(){}
void ECVTGeneral::disablePerformButtonSlot()
{
    int i;
    for (i=ECVT_GENERAL_FUNCTION_CODE_MIN+1; i <ECVT_GENERAL_FUNCTION_CODE_MAX; i++)
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
    for (i=ECVT_GENERAL_FUNCTION_CODE_MIN+1; i < ECVT_GENERAL_FUNCTION_CODE_MAX; i++)
    {
        if (SwichButtonG->button(i))
        {
            SwichButtonG->button(i)->setEnabled(true);
        }
    }
    updateWindowData();
}
        
//****************������Ϣ********************************************************************************************
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
void ECVTGeneral::performFunction(int funcCode)
{
	switch(funcCode)
	{
        case EC4A_GET_STATUS:
            m_exec_EC4A_get_status();
            break;
        
        case EC4A_GET_SIM_MODE:
            m_exec_EC4A_get_sim_mode();
            break;
        
        case EC4A_SET_SIM_MODE:
            m_exec_EC4A_set_sim_mode();
            break;
        default:
			break;
	}
}
//ˢ�½�������
void ECVTGeneral::updateWindowData()//slot
{
    switch (m_func)
    {
	case EC4A_GET_STATUS:
	EC4A_get_status_init_flag_ptr_qle->setText(QString("%1").arg(u_param.param_EC4A_get_status.init_flag_ptr);
		break;
	case EC4A_GET_SIM_MODE:
	EC4A_get_sim_mode_sim_mode_ptr_qle->setText(QString("%1").arg(u_param.param_EC4A_get_sim_mode.sim_mode_ptr);
		break;
	case EC4A_SET_SIM_MODE:
		break;
	default:
		break;
	}
}
void ECVTGeneral::param_range_check() 
	{
	}
void ECVTGeneral::performButtonClickedSlot(int button_id)
	{ 
		switch (button_id)
		{
			case (int)EC4A_GET_STATUS:
				m_func=EC4A_GET_STATUS;
				emit performFuncSignal(button_id);
				break;
			case (int)EC4A_GET_SIM_MODE:
				m_func=EC4A_GET_SIM_MODE;
				emit performFuncSignal(button_id);
				break;
			case (int)EC4A_SET_SIM_MODE:
				m_func=EC4A_SET_SIM_MODE;
				emit performFuncSignal(button_id);
				break;
			default:
				m_func=button_id;
				emit performFuncSignal(button_id);
				break;
		}
	}
void ECVTGeneral::m_exec_EC4A_get_status()
	{       
        int error_code = OK;
        int num = 0;
        QString func_name = "EC4A_get_status";
        //�����Ϣ�������
        outputStart(func_name);
		//ִ�к���
		error_code = EC4A_get_status(				u_param.param_EC4A_get_status.status);
		//���½���
		outputEnd(func_name,error_code);
	}
void ECVTGeneral::m_exec_EC4A_get_sim_mode()
	{       
        int error_code = OK;
        int num = 0;
        QString func_name = "EC4A_get_sim_mode";
        //�����Ϣ�������
        outputStart(func_name);
		//ִ�к���
		error_code = EC4A_get_sim_mode(
				u_param.param_EC4A_get_sim_mode.sim_mode,
				u_param.param_EC4A_get_sim_mode.trace_mode,
				u_param.param_EC4A_get_sim_mode.data_mode);
		//���½���
		outputEnd(func_name,error_code);
	}
void ECVTGeneral::m_exec_EC4A_set_sim_mode()
	{       
        int error_code = OK;
        int num = 0;
        QString func_name = "EC4A_set_sim_mode";
        //�����Ϣ�������
        outputStart(func_name);
		u_param.param_EC4A_set_sim_mode.sim_mode = TR4A_SIM_MODE_ENUM(EC4A_set_sim_mode_sim_mode_qcb->currintIndex());
		//ִ�к���
		error_code = EC4A_set_sim_mode(
				u_param.param_EC4A_set_sim_mode.sim_mode,
				u_param.param_EC4A_set_sim_mode.trace_mode,
				u_param.param_EC4A_set_sim_mode.data_mode);
		//���½���
		outputEnd(func_name,error_code);
	}
