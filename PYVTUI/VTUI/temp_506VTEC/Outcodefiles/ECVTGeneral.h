/***********************************************************
* Copyright (C) 2018, �Ϻ�΢����װ�����޹�˾
* All rights reserved.
* ��Ʒ�� : SS A600/20
* ������� : EC
* ģ������ : ECVT
* �ļ����� : ECVT.h
* ��Ҫ���� :
* ��ʷ��¼ :
* �汾        ����                      ����          ����
*  ?          2018-08-08               yuzt            ����
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
//*******����������������嶨��************************/
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
    //��ֹ����ȫ����ť
    void disablePerformButtonSlot();
    //ʹ�����а�ť
    void enablePerformButtonSlot();
protected slots:
    //ˢ�½�������
    void updateWindowData();
    //��ť��Ӧ�Ĳ�
    void performButtonClickedSlot(int button_id);
    private:
    //��Ϣ�����
    void m_log( int flag,const QString title ,const QString text);
    void outputStart( QString fun_name);
    void outputEnd( QString fun_name,int rtn);
    //ִ�нӿں���
        
    void m_exec_EC4T_update_wa_baseline();signals:
    void send_log(int flag,const QString title,const QString text);
    void performFuncSignal(int funcCode);
private:
    ECVT_GENERAL_FUNCTION_CODE_ENUM m_func;
    ECVT_GENERAL_PARAM_UNION u_param;
    QButtonGroup  *SwichButtonG ; //������ť�����ָ�� 
    };
#endif
        