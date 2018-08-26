
    /**************************************************************************
    * Copyright (C) 2018, �Ϻ�΢����װ�����޹�˾
    * All rights reserved.
    * ��Ʒ�� : SS B500/10M
    * ������� : EC
    * ģ������ : ECVT
    * �ļ����� : ECVT.cpp
    * ��Ҫ���� : ECVTԴ�ļ�
    * ��ʷ��¼ :
    * �汾    ����         ����        ����
    * 1.0     2018-06-02            yzt
    **************************************************************************/
    
    #include "VT.h"
    //����������
    VT::VT(QWidget *parent):Widget(parent)
    {
        setupUi(this);
        m_Thread_p = new SMEE::PerformFunctionThread(this);
        m_FunctionPageHash.clear();
        m_pCategory = new VTCategory(this);//����һ������������,���ڷ��ص�VT��ҳ�档��ҳ�渺�𵼺����Ĵ򿪺͹ر�
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
    //�ۺ���
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
                    //�ӿڷ���֮ǰ����ֹ�û�ִ��close����
                    connect(m_Thread_p, SIGNAL(doFuncStartedSignal()), m_%sVTCategory, SLOT(disableCloseButtonSlot()));
                    connect(m_Thread_p, SIGNAL(doFuncFinishedSignal()), m_%sVTCategory, SLOT(enableCloseButtonSlot()));
                    //�ӿڷ���֮ǰ����ֹ�û�ִ��logout����
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
    //������Ϣ�Ĳ�
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
    //�߳̿�ʼ����OIMA�е�logout��ť
    void VT::disableLogoutButtonSlot()
    {
        emit lockLogout(true);
    }
    //�߳̽�������OIMA�е�logout��ť
    void VT::enableLogoutButtonSlot()
    {
        emit lockLogout(false);
    }
    //�������湹��
    VTCategory::VTCategory(QWidget *parent)
    :QWidget(parent)
    {
        setupUi(this);
        m_ButtonGroup_p = new QButtonGroup(this);//������ť��
    m_ButtonGroup_p->addButton(btn_general,GENERAL_PAGE);m_ButtonGroup_p->addButton(btn_maintenance,MAINTENANCE_PAGE);
        m_ButtonGroup_p->setExclusive(true);
        btn_general->setChecked(true);
        ////��ӽ����л� �źźͲۺ�����
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
    //�߳̿�ʼ����close��ť
    void VTCategory::disableCloseButtonSlot()
    {
        btn_close->setEnabled(false);
    }
    //�߳̽�������close��ť
    void VTCategory::enableCloseButtonSlot()
    {
        btn_close->setEnabled(true);
    }
    