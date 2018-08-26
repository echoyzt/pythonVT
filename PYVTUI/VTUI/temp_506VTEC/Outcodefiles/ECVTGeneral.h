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
       SMEE_ALIGN_TYPE_ENUM align_type;
       EC4T_UPDATE_WA_BASELINE_RESULT_STRUCT oa_baseline_result_p;
    }param_EC4T_update_wa_baseline;
}ECVT_GENERAL_PARAM_UNION;
        
typedef enum
{
    ECVT_GENERAL_FUNCTION_CODE_MIN = 0,
    EC4T_UPDATE_WA_BASELINE,
    ECVT_GENERAL_FUNCTION_CODE_MAX
}ECVT_GENERAL_FUNCTION_CODE_ENUM; 
        
class ECVTGeneral:public SMEE::Widget, private Ui::ECVTGeneral
{
Q_OBJECT
public:
    ECVTGeneral(QWidget * parent = 0);
    ~ECVTGeneral();
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
        
    void m_exec_EC4T_update_wa_baseline();signals:
    void send_log(int flag,const QString title,const QString text);
    void performFuncSignal(int funcCode);
private:
    ECVT_GENERAL_FUNCTION_CODE_ENUM m_func;
    ECVT_GENERAL_PARAM_UNION u_param;
    QButtonGroup  *SwichButtonG ; //侧栏按钮组对象指针 
    };
#endif
        