
    /**************************************************************************
    * Copyright (C) 2018, �Ϻ�΢����װ�����޹�˾
    * All rights reserved.
    * ��Ʒ�� : SS B500/10M
    * ������� : EC
    * ģ������ : ECVT
    * �ļ����� : ECVT.h
    * ��Ҫ���� : ECVTͷ�ļ�
    * ��ʷ��¼ :
    * �汾    ����         ����        ����
    * ??       2018-03-22           yzt         ����
    **************************************************************************/
    
    #ifndef _ECVT_H_
    #define _ECVT_H_
    #include <QButtonGroup>
    #include "smee.h"
    #include "Widget.h"
    #include "ui_ECVT.h"
    #include "ui_ECVTCategory.h"
    #include "PerformFunctionThread.h"
    #include <TR4A_tc.h>
    # include "ECVTMaintenance.h"+'
'# include "ECVTGeneral.h"+'
'
    typedef enum
    {
        ECVT_MIN_PAGE = 0  , 
    ECVT_MAINTENANCE_PAGE,+'
'ECVT_GENERAL_PAGE,+'
'
     ECVT_MAX_PAGE
    }ECVT_FUNC_PAGE_ENUM;
    //�߳�ִ�к�����������ṹ��
    typedef struct
    {
        QObject * executor;
        int pageIndex;
        int funcCode;
    } ECVT_PERFORM_FUNC_PARAM_STRUCT;
    class ECVT;
    class ECVTCategory;
    class PerformFunctionThread;
    class ECVT : public SMEE::Widget, public  Ui::ECVT
    {
        Q_OBJECT
    public:
        ECVT(QWidget *parent = 0);
        virtual ~ECVT();
        QWidget * getSideWidget( void ); //���ӵ���ҳ��,���ⲿʹ��
        static void execute(void * param);
        private slots:
            // ����ҳ��ѡ����
            void switchFuncPageSlot(int pageIndex);
            //�ر�����ҳ��
            void closeWindowSlot();
            void outputLogSlot(int flag,const QString title,const QString text);
            void peformFuncSlot(int funcCode);
            void disableLogoutButtonSlot();//�߳̿�ʼ����logout��ť
            void enableLogoutButtonSlot();//�߳̽�������logout��ť
    private:
        QHash<int, QWidget*> m_FunctionPageHash;
        ECVTCategory * m_ECVTCategory;
        ECVTGeneral  *m_ECVTGeneral;
        SMEE::PerformFunctionThread * m_Thread_p;
    signals:
        void errorLogSignal(const QString systemName, const QString description, const int exceptionCode);
        /* - true	�߳̿�ʼ,OIMA����logout��������״̬
         * - false	�߳̽���,OIMA����logout�������״̬
         */
        void lockLogout (bool flags);
    };
    //ECVT����������
    class ECVTCategory : public QWidget, public Ui::ECVTCategory
    {
        Q_OBJECT
    public:
        ECVTCategory(QWidget * parent = 0);
        virtual ~ECVTCategory();
    signals:
        void closeWindowSignal();
        void buttonClicked(int index);
    private slots:
    void disableCloseButtonSlot();//�߳̿�ʼ����close��ť
    void enableCloseButtonSlot();//�߳̽�������close��ť
    private:
        QButtonGroup * m_ButtonGroup_p ; //������ť�����ָ��
    };
    #endif
    