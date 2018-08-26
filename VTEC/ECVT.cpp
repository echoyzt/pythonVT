/**************************************************************************
* Copyright (C) 2011, 上海微电子装备有限公司
* All rights reserved.
* 产品号 : SS B500/10M
* 所属组件 : EC
* 模块名称 : ECVT
* 文件名称 : ECVT.cpp
* 概要描述 : ECVT源文件
* 历史记录 :
* 版本    日期         作者        内容
* 1.0     
**************************************************************************/


#include "ECVT.h"


//构造主界面
ECVT::ECVT(QWidget *parent):Widget(parent)
{
	setupUi(this);
	m_Thread_p = new SMEE::PerformFunctionThread(this);

	m_FunctionPageHash.clear();

	m_ECVTCategory = new ECVTCategory(this);//创建一个导航栏对象,用于返回到VT主页面。主页面负责导航栏的打开和关闭

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
//槽函数
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

				//接口返回之前，禁止用户执行close操作
				connect(m_Thread_p, SIGNAL(doFuncStartedSignal()), m_ECVTCategory, SLOT(disableCloseButtonSlot()));
				connect(m_Thread_p, SIGNAL(doFuncFinishedSignal()), m_ECVTCategory, SLOT(enableCloseButtonSlot()));

				//接口返回之前，禁止用户执行logout操作
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


//接受信息的槽
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

//线程开始禁用OIMA中的logout按钮
void ECVT::disableLogoutButtonSlot()
{
	
	emit lockLogout(true);
}

//线程结束启用OIMA中的logout按钮
void ECVT::enableLogoutButtonSlot()
{
	
	emit lockLogout(false);
}


//导航界面构造
ECVTCategory::ECVTCategory(QWidget *parent) 
:QWidget(parent)
{
	setupUi(this);

	m_ButtonGroup_p = new QButtonGroup(this);//创建按钮组

	m_ButtonGroup_p->addButton(btn_general,ECVT_GENERAL_PAGE);
	/*m_ButtonGroup_p->addButton(btn_application,ECVT_APPLICATION_PAGE);*/
	m_ButtonGroup_p->addButton(btn_maintenance,ECVT_MIANTENANCE_PAGE);
	m_ButtonGroup_p->setExclusive(true);

	btn_general->setChecked(true);

	////绑接界面切换 信号和槽函数。
	connect(m_ButtonGroup_p,SIGNAL(buttonClicked(int)),this,SIGNAL(buttonClicked(int)));	

	connect (btn_close, SIGNAL (clicked()), this, SIGNAL (closeWindowSignal()));
}

ECVTCategory::~ECVTCategory()
{
	////////销毁侧栏按钮组对象。
	if(m_ButtonGroup_p != NULL)
	{
		delete m_ButtonGroup_p;
		m_ButtonGroup_p = NULL;
	}
}


//线程开始禁用close按钮
void ECVTCategory::disableCloseButtonSlot()
{
	
	btn_close->setEnabled(false);
}

//线程结束启用close按钮
void ECVTCategory::enableCloseButtonSlot()
{
	
	btn_close->setEnabled(true);
}


