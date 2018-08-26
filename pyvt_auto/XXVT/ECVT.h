
    /**************************************************************************
    * Copyright (C) 2018, 上海微电子装备有限公司
    * All rights reserved.
    * 产品号 : SS B500/10M
    * 所属组件 : EC
    * 模块名称 : ECVT
    * 文件名称 : ECVT.h
    * 概要描述 : ECVT头文件
    * 历史记录 :
    * 版本    日期         作者        内容
    * ??       2018-03-22           yzt         创建
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
    //线程执行函数参数打包结构体
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
        ECVTCategory * m_ECVTCategory;
        ECVTGeneral  *m_ECVTGeneral;
        SMEE::PerformFunctionThread * m_Thread_p;
    signals:
        void errorLogSignal(const QString systemName, const QString description, const int exceptionCode);
        /* - true	线程开始,OIMA界面logout进入锁定状态
         * - false	线程结束,OIMA界面logout解除锁定状态
         */
        void lockLogout (bool flags);
    };
    //ECVT侧栏界面类
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
    void disableCloseButtonSlot();//线程开始禁用close按钮
    void enableCloseButtonSlot();//线程结束启用close按钮
    private:
        QButtonGroup * m_ButtonGroup_p ; //侧栏按钮组对象指针
    };
    #endif
    