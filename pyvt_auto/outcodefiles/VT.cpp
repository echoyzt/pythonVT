
    /**************************************************************************
    * Copyright (C) 2018, 上海微电子装备有限公司
    * All rights reserved.
    * 产品号 : SS B500/10M
    * 所属组件 : EC
    * 模块名称 : ECVT
    * 文件名称 : ECVT.cpp
    * 概要描述 : ECVT源文件
    * 历史记录 :
    * 版本    日期         作者        内容
    * 1.0     2018-06-02            yzt
    **************************************************************************/
    
    #include "VT.h"
    //构造主界面
    VT::VT(QWidget *parent):Widget(parent)
    {
        setupUi(this);
        m_Thread_p = new SMEE::PerformFunctionThread(this);
        m_FunctionPageHash.clear();
        m_pCategory = new VTCategory(this);//创建一个导航栏对象,用于返回到VT主页面。主页面负责导航栏的打开和关闭
        switchFuncPageSlot(GENERAL_PAGE);
        connecst (m_pCategory, SIGNAL (closeWindowSignal()), this, SLOT (closeWindowSlot()));
        connect (m_pCategory, SIGNAL (buttonClicked(int)), this, SLOT (switchFuncPageSlot(int)));
    }
    VT::~VT(){}
    QWidget * VT::getSideWidget( void ) 
    { 
        return m_pVTCategory; 
    }
    void VT::peformFuncSlot(int funcCode)
    {
        bool result = true;
        if(NULL != m_Thread_p)
        {
            PERFORM_FUNC_PARAM_STRUCT *param;
            param = new PERFORM_FUNC_PARAM_STRUCT;
            param->executor = VT_StackWidget->currentWidget();
            param->pageIndex = m_FunctionPageHash.key(VT_StackWidget->currentWidget());
            param->funcCode = funcCode;
            result = m_Thread_p->performFunctionStart(VT::execute, param);
            if(!result)
            {
                delete param;
            }
        }
    }
    void VT::execute(void *param)
    {
       
        PERFORM_FUNC_PARAM_STRUCT *param_p;
        param_p = (PERFORM_FUNC_PARAM_STRUCT *)param;
        switch(param_p->pageIndex)
        {
    
            case GENERAL_PAGE:
            VTGeneral *generalPage;
            generalPage = qobject_cast<VTGeneral *>(param_p->executor);
            if(NULL != generalPage)
            {
                generalPage->performFunction(param_p->funcCode);
            }
            break;
            
            case MAINTENANCE_PAGE:
            VTMaintenance *maintenancePage;
            maintenancePage = qobject_cast<VTMaintenance *>(param_p->executor);
            if(NULL != maintenancePage)
            {
                maintenancePage->performFunction(param_p->funcCode);
            }
            break;
            
    default:
        break;
    }
    delete param_p;
}   
    //槽函数
    void VT::switchFuncPageSlot(int pageIndex)
    {
        if(pageIndex >= FUNC_PAGE_MIN && pageIndex <= FUNC_PAGE_MAX)
        {
            if(!m_FunctionPageHash.contains(pageIndex))
            {
                switch(pageIndex)
                {
    
         case GENERAL_PAGE:
                    m_FunctionPageHash[pageIndex] = new VTGeneral;
                    break;
        
         case MAINTENANCE_PAGE:
                    m_FunctionPageHash[pageIndex] = new VTMaintenance;
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
                    connect(m_Thread_p, SIGNAL(doFuncStartedSignal()), m_%sVTCategory, SLOT(disableCloseButtonSlot()));
                    connect(m_Thread_p, SIGNAL(doFuncFinishedSignal()), m_%sVTCategory, SLOT(enableCloseButtonSlot()));
                    //接口返回之前，禁止用户执行logout操作
                    connect(m_Thread_p, SIGNAL(doFuncStartedSignal()), this, SLOT(disableLogoutButtonSlot()));
                    connect(m_Thread_p, SIGNAL(doFuncFinishedSignal()), this, SLOT(enableLogoutButtonSlot()));
                    VT_StackWidget->insertWidget(pageIndex,m_FunctionPageHash[pageIndex]);
                }
                else
                {
                    SMEE::MessageBox::warning(this, 
                        QString("Switch Page"), 
                        QString("%sVT create function page(%s) failed!").arg(pageIndex));
                    return;
                }
            }
            VT_StackWidget->setCurrentWidget(m_FunctionPageHash[pageIndex]);
        }
    }
    void VT::closeWindowSlot()
    {
        SMEE::MessageBox::StandardButton button;
        button = SMEE::MessageBox::question(this,
            QString("Question"),
            QString("Are you sure to exit?"),
            SMEE::MessageBox::Ok|SMEE::MessageBox::Cancel);
        if(button == SMEE::MessageBox::Ok)
        {
            m_FunctionPageHash.clear();
            close();
        }
    }
    //接受信息的槽
    void VT::outputLogSlot(int flag,const QString title,const QString text)
    {
        if (flag == OK)
        {
            VT_Output->normal(title,text);
        }else
        {
            emit errorLogSignal(QObject::tr("VT%s", "VT%s"), text, flag);
            VT_Output->error(title,text);
        }
    }
    //线程开始禁用OIMA中的logout按钮
    void VT::disableLogoutButtonSlot()
    {
        emit lockLogout(true);
    }
    //线程结束启用OIMA中的logout按钮
    void VT::enableLogoutButtonSlot()
    {
        emit lockLogout(false);
    }
    //导航界面构造
    VTCategory::VTCategory(QWidget *parent)
    :QWidget(parent)
    {
        setupUi(this);
        m_ButtonGroup_p = new QButtonGroup(this);//创建按钮组
    m_ButtonGroup_p->addButton(btn_general,GENERAL_PAGE);m_ButtonGroup_p->addButton(btn_maintenance,MAINTENANCE_PAGE);
        m_ButtonGroup_p->setExclusive(true);
        btn_general->setChecked(true);
        ////绑接界面切换 信号和槽函数。
        connect(m_ButtonGroup_p,SIGNAL(buttonClicked(int)),this,SIGNAL(buttonClicked(int)));	
        connect (btn_close, SIGNAL (clicked()), this, SIGNAL (closeWindowSignal()));
    }
    VTCategory::VTCategory()
    {
        if(m_ButtonGroup_p != NULL)
        {
            delete m_ButtonGroup_p;
            m_ButtonGroup_p = NULL;
        }
    }
    //线程开始禁用close按钮
    void VTCategory::disableCloseButtonSlot()
    {
        btn_close->setEnabled(false);
    }
    //线程结束启用close按钮
    void VTCategory::enableCloseButtonSlot()
    {
        btn_close->setEnabled(true);
    }
    