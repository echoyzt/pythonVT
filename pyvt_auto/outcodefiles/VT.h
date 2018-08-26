
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
    //线程执行函数参数打包结构体
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
        QWidget * getSideWidget( void ); //连接导航页面,供外部使用
        static void execute(void * param);
        private slots:
            // 侧栏页面选择函数
            void switchFuncPageSlot(int pageIndex);
            //关闭所有页面
            void closeWindowSlot();
            void outputLogSlot(int flag,const QString title,const QString text);
            void peformFuncSlot(int funcCode);
            void disableLogoutButtonSlot();//线程开始禁用logout按钮
            void enableLogoutButtonSlot();//线程结束启用logout按钮
    private:
        QHash<int, QWidget*> m_FunctionPageHash;
        VTCategory * m_pCategory;
        VTGeneral  *m_VTGeneral;
        SMEE::PerformFunctionThread * m_Thread_p;
    signals:
        void errorLogSignal(const QString systemName, const QString description, const int exceptionCode);
        /* - true	线程开始,OIMA界面logout进入锁定状态
         * - false	线程结束,OIMA界面logout解除锁定状态
         */
        void lockLogout (bool flags);
    };
    //VT侧栏界面类
    class VTCategory : public QWidget, public Ui::VTCategory
    {
        Q_OBJECT
    public:
        VTCategory(QWidget * parent = 0);
        ~VTCategory();
    private:
        QButtonGroup * m_ButtonGroup_p ; //侧栏按钮组对象指针
    
    signals:
        void closeWindowSignal();
        void buttonClicked(int index);
    private slots:
    void disableCloseButtonSlot();//线程开始禁用close按钮
    void enableCloseButtonSlot();//线程结束启用close按钮
    };
    #endif
    