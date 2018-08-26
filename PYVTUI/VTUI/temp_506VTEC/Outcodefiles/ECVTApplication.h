/***********************************************************
* Copyright (C) 2018, 上海微电子装备有限公司
* All rights reserved.
* 产品号 : SS A600/20
* 所属组件 : EC
* 模块名称 : ECVT
* 文件名称 : ECVT.h
* 概要描述 :
* 历史记录 :
* 版本        日期                      作者          内容
*  ?          2018-08-08               yuzt            创建
**************************************************/
#ifndef _ECVT_EC_H_
#define _ECVT_EC_H_
#include "SMEE_Gui.h"
#include <QThread>
#include "ui_ECVTEC.h"      
        
#include "EC4A_if.h"
#include "EC4A_tc.h"
#include "EC4T_if.h"
#include "EC4T_tc.h"
//*******输入输出参数联合体定义************************/
typedef union
{
 struct
    {
       EC4A_STATUS_STRUCT status;
    }param_EC4A_get_status;
}ECVT_APPLICATION_PARAM_UNION;
        
typedef enum
{
    ECVT_APPLICATION_FUNCTION_CODE_MIN = 0,
    EC4A_GET_STATUS,
    ECVT_APPLICATION_FUNCTION_CODE_MAX
}ECVT_APPLICATION_FUNCTION_CODE_ENUM; 
        
class ECVTApplication:public SMEE::Widget, private Ui::ECVTApplication
{
Q_OBJECT
public:
    ECVTApplication(QWidget * parent = 0);
    ~ECVTApplication();
    void performFunction(int funcCode);
public slots:
    //禁止界面全部按钮
    void disablePerformButtonSlot();
    //使能所有按钮
    void enablePerformButtonSlot();
protected slots:
    //刷新界面数据
    void updateWindowData();
    //按钮对应的槽
    void performButtonClickedSlot(int button_id);
    private:
    //信息输出栏
    void m_log( int flag,const QString title ,const QString text);
    void outputStart( QString fun_name);
    void outputEnd( QString fun_name,int rtn);
    //执行接口函数
        
    void m_exec_EC4A_get_status();signals:
    void send_log(int flag,const QString title,const QString text);
    void performFuncSignal(int funcCode);
private:
    ECVT_APPLICATION_FUNCTION_CODE_ENUM m_func;
    ECVT_APPLICATION_PARAM_UNION u_param;
    QButtonGroup  *SwichButtonG ; //侧栏按钮组对象指针 
    };
#endif
        