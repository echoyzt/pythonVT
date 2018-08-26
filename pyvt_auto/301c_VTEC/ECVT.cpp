/**************************************************************************
* Copyright (C) 2011, �Ϻ�΢����װ�����޹�˾
* All rights reserved.
* ��Ʒ�� : SS B500/10M
* ������� : EC
* ģ������ : ECVT
* �ļ����� : ECVT.cpp
* ��Ҫ���� : ECVTԴ�ļ�
* ��ʷ��¼ :
* �汾    ����         ����        ����
* 1.0     
**************************************************************************/


#include "ECVT.h"


//����������
ECVT::ECVT(QWidget *parent):Widget(parent)
{
	setupUi(this);
	m_Thread_p = new SMEE::PerformFunctionThread(this);

	m_FunctionPageHash.clear();

	m_ECVTCategory = new ECVTCategory(this);//����һ������������,���ڷ��ص�VT��ҳ�档��ҳ�渺�𵼺����Ĵ򿪺͹ر�

	switchFuncPageSlot(ECVT_GENERAL_PAGE);
	connect (m_ECVTCategory, SIGNAL (closeWindowSignal()), this, SLOT (closeWindowSlot()));
	connect (m_ECVTCategory, SIGNAL (buttonClicked(int)), this, SLOT (switchFuncPageSlot(int)));
}

ECVT::~ECVT()
{

}
QWidget * ECVT::getSideWidget( void ) 
{ 
	return m_ECVTCategory; 
}

void ECVT::peformFuncSlot(int funcCode)
{
	//printf("WSVT::peformFuncSlot <<\n");
	bool result = true;
	

	if(NULL != m_Thread_p)
	{
		ECVT_PERFORM_FUNC_PARAM_STRUCT * param;
		param = new ECVT_PERFORM_FUNC_PARAM_STRUCT;

		param->executor = ECVT_StackWidget->currentWidget();
		param->pageIndex = m_FunctionPageHash.key(ECVT_StackWidget->currentWidget());
		param->funcCode = funcCode;
		result = m_Thread_p->performFunctionStart(ECVT::execute, param);

		if(!result)
		{
			delete param;
		}
	}
	//printf("WSVT::peformFuncSlot >> \n");
}

void ECVT::execute(void * param)
{
	//printf("WSVT::execute << \n");
	ECVT_PERFORM_FUNC_PARAM_STRUCT * param_p;
	param_p = (ECVT_PERFORM_FUNC_PARAM_STRUCT *)param;
	switch(param_p->pageIndex)
	{
	case ECVT_GENERAL_PAGE:
		ECVTGeneral * generalPage;
		generalPage = qobject_cast<ECVTGeneral *>(param_p->executor);
		if(NULL != generalPage)
		{
			generalPage->performFunction(param_p->funcCode);
		}
		break;
	//case ECVT_APPLICATION_PAGE:
	//	ECVTApplication * applicationPage;
	//	applicationPage = qobject_cast<ECVTApplication *>(param_p->executor);
	//	if(NULL != applicationPage)
	//	{
	//		applicationPage->performFunction(param_p->funcCode);
	//	}
	//	break;
	case ECVT_MIANTENANCE_PAGE:
		ECVTMaintenance *maintenance;
		maintenance = qobject_cast<ECVTMaintenance *>(param_p->executor);
		if(NULL != maintenance)
		{
			maintenance->performFunction(param_p->funcCode);
		}
		break;
	default:
		break;
	}

	delete param_p;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//�ۺ���
void ECVT::switchFuncPageSlot(int pageIndex)
{
	if(pageIndex >= ECVT_MIN_PAGE && pageIndex < ECVT_MAX_PAGE)
	{
		if(!m_FunctionPageHash.contains(pageIndex))
		{
			switch(pageIndex)
			{
			case ECVT_GENERAL_PAGE:
				m_FunctionPageHash[pageIndex] = new ECVTGeneral;
				break;
			/*case ECVT_APPLICATION_PAGE:
				m_FunctionPageHash[pageIndex] = new ECVTApplication;
				break;*/
			case ECVT_MIANTENANCE_PAGE:
				m_FunctionPageHash[pageIndex] = new ECVTMaintenance;
				break;
			default:
				break;
			}

			if(NULL != m_FunctionPageHash[pageIndex])
			{
				connect(m_FunctionPageHash[pageIndex], SIGNAL(send_log(int,const QString,const QString)),
					this, SLOT(outputLogSlot(int,const QString,const QString)));

				connect(m_FunctionPageHash[pageIndex], SIGNAL(performFuncSignal(int)), this, SLOT(peformFuncSlot(int)));

				connect(m_Thread_p, SIGNAL(doFuncStartedSignal()), m_FunctionPageHash[pageIndex], SLOT(disablePerformButtonSlot()));
				connect(m_Thread_p, SIGNAL(doFuncFinishedSignal()), m_FunctionPageHash[pageIndex], SLOT(enablePerformButtonSlot()));

				//�ӿڷ���֮ǰ����ֹ�û�ִ��close����
				connect(m_Thread_p, SIGNAL(doFuncStartedSignal()), m_ECVTCategory, SLOT(disableCloseButtonSlot()));
				connect(m_Thread_p, SIGNAL(doFuncFinishedSignal()), m_ECVTCategory, SLOT(enableCloseButtonSlot()));

				//�ӿڷ���֮ǰ����ֹ�û�ִ��logout����
				connect(m_Thread_p, SIGNAL(doFuncStartedSignal()), this, SLOT(disableLogoutButtonSlot()));
				connect(m_Thread_p, SIGNAL(doFuncFinishedSignal()), this, SLOT(enableLogoutButtonSlot()));

				
				ECVT_StackWidget->insertWidget(pageIndex,m_FunctionPageHash[pageIndex]);
			}
			else
			{
				QMessageBox::warning(this, 
					QString("Switch Page"), 
					QString("ECVT create function page(%1) failed!").arg(pageIndex));

				return;
			}
		}

		ECVT_StackWidget->setCurrentWidget(m_FunctionPageHash[pageIndex]);
	}
}


void ECVT::closeWindowSlot()
{
	/*QMessageBox::StandardButton button;
	button = QMessageBox::question(this, 
		QString("Question"), 
		QString("Are you sure to exit?"), 
		QMessageBox::Ok|QMessageBox::Cancel);

	if(button == QMessageBox::Ok)
	{*/
		m_FunctionPageHash.clear();

		close();
	//}
}


//������Ϣ�Ĳ�
void ECVT::outputLogSlot(int flag,const QString title,const QString text)
{
	if (flag == OK)
	{
		ECVT_Output->normal(title,text);
	}else
	{
		emit errorLogSignal(QObject::tr("VTEC", "VTEC"), text, flag);
		ECVT_Output->error(title,text);
	}
}

//�߳̿�ʼ����OIMA�е�logout��ť
void ECVT::disableLogoutButtonSlot()
{
	
	emit lockLogout(true);
}

//�߳̽�������OIMA�е�logout��ť
void ECVT::enableLogoutButtonSlot()
{
	
	emit lockLogout(false);
}


//�������湹��
ECVTCategory::ECVTCategory(QWidget *parent) 
:QWidget(parent)
{
	setupUi(this);

	m_ButtonGroup_p = new QButtonGroup(this);//������ť��

	m_ButtonGroup_p->addButton(btn_general,ECVT_GENERAL_PAGE);
	/*m_ButtonGroup_p->addButton(btn_application,ECVT_APPLICATION_PAGE);*/
	m_ButtonGroup_p->addButton(btn_maintenance,ECVT_MIANTENANCE_PAGE);
	m_ButtonGroup_p->setExclusive(true);

	btn_general->setChecked(true);

	////��ӽ����л� �źźͲۺ�����
	connect(m_ButtonGroup_p,SIGNAL(buttonClicked(int)),this,SIGNAL(buttonClicked(int)));	

	connect (btn_close, SIGNAL (clicked()), this, SIGNAL (closeWindowSignal()));
}

ECVTCategory::~ECVTCategory()
{
	////////���ٲ�����ť�����
	if(m_ButtonGroup_p != NULL)
	{
		delete m_ButtonGroup_p;
		m_ButtonGroup_p = NULL;
	}
}


//�߳̿�ʼ����close��ť
void ECVTCategory::disableCloseButtonSlot()
{
	
	btn_close->setEnabled(false);
}

//�߳̽�������close��ť
void ECVTCategory::enableCloseButtonSlot()
{
	
	btn_close->setEnabled(true);
}


