/**************************************************************************
* Copyright (C) 2008, �Ϻ�΢����װ�����޹�˾
* All rights reserved.
* ��Ʒ�� : SS A600/20
* ������� : EC
* ģ������ : ECVT
* �ļ����� : ECVT.h
* ��Ҫ���� :
* ��ʷ��¼ :
* �汾    ����         ����        ����

**************************************************************************/

#ifndef _ECVT_GENERAL_H_
#define _ECVT_GENERAL_H_
#include "EC4A_if.h"
//#include "EC4T_if.h"
#include "SMEE_Gui.h"
//#include <QtGui>
#include <QThread>
#include "ui_ECVTGeneral.h"

//*******����������������嶨��************************************************/
typedef union
{
	struct 
	{ 
	EC4A_STATUS_STRUCT status;
	}param_EC4A_get_status;
	 
	struct 
	{ 
	TR4A_SIM_MODE_ENUM sim_mode;
	TR4A_TRACE_MODE_ENUM trace_mode;
	TR4A_REQ_MODE_ENUM data_mode;
	}param_EC4A_set_sim_mode;
	 
	struct 
	{ 
	TR4A_SIM_MODE_ENUM sim_mode;
	TR4A_TRACE_MODE_ENUM trace_mode;
	TR4A_REQ_MODE_ENUM data_mode;
	}param_EC4A_get_sim_mode;
	 
}ECVT_General_PARAM_UNION;

typedef enum
{
	EC4A_GENERAL_FUNCTION_CODE_MIN = 0,
	EC4A_INITIALIZE,
	EC4A_TERMINATE,
	EC4A_GET_STATUS,
	EC4A_UPDATE_MC,
	EC4A_SET_SIM_MODE,
	EC4A_GET_SIM_MODE,
	EC4A_GENERAL_FUNCTION_CODE_MAX
}EC4A_GENERAL_FUNCTION_CODE_ENUM;
//************************************************************************
class ECVTGeneral:public SMEE::Widget, private Ui::ECVTGeneral
{
    Q_OBJECT

    public:
        ECVTGeneral(QWidget * parent = 0);
        ~ECVTGeneral();

		void performFunction(int funcCode);

	public slots:

		//��ֹ����ȫ����ť
		void disablePerformButtonSlot();

		//ʹ�����а�ť
		void enablePerformButtonSlot();
	protected slots:

		//ˢ�½�������
		void updateWindowData();

		//��ť��Ӧ�Ĳ�
		void performButtonClickedSlot(int button_id);
	
	private:
		//��Ϣ�����
		void m_log( int flag,const QString title ,const QString text);
		void outputStart( QString fun_name);
		void outputEnd( QString fun_name,int rtn);

		//ִ�нӿں���
		void m_exec_EC4A_initialize();
		void m_exec_EC4A_terminate();
		void m_exec_EC4A_get_status();
		void m_exec_EC4A_update_mc();
		void m_exec_EC4A_set_sim_mode();
		void m_exec_EC4A_get_sim_mode();

    signals:
    	void send_log(int flag,const QString title,const QString text);
		void performFuncSignal(int funcCode);
    private:

		EC4A_GENERAL_FUNCTION_CODE_ENUM m_func;
        ECVT_General_PARAM_UNION u_param;
        QButtonGroup  *SwichButtonG ; //������ť�����ָ��
        
};

#endif //_ECVT_GENERAL_H_

