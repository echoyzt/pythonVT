
    #ifndef _VT_H_
    #define _VT_H_
    #include <QButtonGroup>
    #include "smee.h"
    #include "Widget.h"
    #include "ui_VT.h"
    #include "ui_ECVTCategory.h"
    #include "PerformFunctionThread.h"
    #include <TR4A_tc.h>
    # include "VTEC.h"+'
'# include "VTEC.h"+'
'
    typedef enum
    {
        FUN_MIN_PAGE = 0  , 
    GENERAL_PAGE,+'
'MAINTENANCE_PAGE,+'
'
     FUNC_PAGE_MAX
    }FUNC_PAGE_ENUM;
    //�߳�ִ�к�����������ṹ��
    typedef struct
    {
        QObject * executor;
        int pageIndex;
        int funcCode;
    }PERFORM_FUNC_PARAM_STRUCT;
    class VT;
    class VTCategory;
    class PerformFunctionThread;
    class VT : public SMEE::Widget, public  Ui::VT
    {
        Q_OBJECT
    public:
        VT(QWidget *parent = 0);
        ~VT();
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
        VTCategory * m_pCategory;
        VTGeneral  *m_VTGeneral;
        SMEE::PerformFunctionThread * m_Thread_p;
    signals:
        void errorLogSignal(const QString systemName, const QString description, const int exceptionCode);
        /* - true	�߳̿�ʼ,OIMA����logout��������״̬
         * - false	�߳̽���,OIMA����logout�������״̬
         */
        void lockLogout (bool flags);
    };
    //VT����������
    class VTCategory : public QWidget, public Ui::VTCategory
    {
        Q_OBJECT
    public:
        VTCategory(QWidget * parent = 0);
        ~VTCategory();
    private:
        QButtonGroup * m_ButtonGroup_p ; //������ť�����ָ��
    
    signals:
        void closeWindowSignal();
        void buttonClicked(int index);
    private slots:
    void disableCloseButtonSlot();//�߳̿�ʼ����close��ť
    void enableCloseButtonSlot();//�߳̽�������close��ť
    };
    #endif
    