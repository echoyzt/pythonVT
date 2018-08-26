/**************************************************************************
* Copyright (C) 2008, 上海微电子装备有限公司
* All rights reserved.
* 产品号 : SS A600/20
* 所属组件 : EC
* 模块名称 : ECVT
* 文件名称 : ECVT.h
* 概要描述 :
* 历史记录 :
* 版本    日期         作者        内容

**************************************************************************/
#include "SpinBoxAgent.h"
#ifndef _ECVT_MAINTENANCE_H_
#define _ECVT_MAINTENANCE_H_
#include "EC4A_if.h"
#include "EC4T_if.h"
#include "SMEE_Gui.h"
#include <QtGui>
#include <QThread>
#include "ui_ECVTMaintenance.h"

using namespace SMEE;

//*******输入输出参数联合体定义************************************************/
typedef union
{
	struct 
	{ 
	     SMEE_BOOL do_global_level;
         SMEE_BOOL do_mapping;
         SMEE_SUBSTRATE_SIZE_ENUM substrate_spec;
         SMEE_DOUBLE substrate_thickness;
         SMEE_DOUBLE user_focus_offset;
         xy_vect global_middle_point;
         //EC4T_MAPPING_ROUTE_STRUCT *mapping_route;
		 EC4T_MAPPING_ROUTE_STRUCT  mapping_route;
		 //zrxry_vect* level_result_p;
         zrxry_vect level_result_p;
	}param_EC4T_do_global_level_on_substrate;
	 
	struct 
	{ 
	SMEE_DOUBLE substrate_thickness;
	SMEE_DOUBLE user_focus_offset;
	zrxry_vect level_result_p;
	zrxry_vect substrate_cuniform_p;
	}param_EC4T_do_global_level_on_ws_fiducial;
	 
	struct 
	{ 
	SMEE_SUBSTRATE_SIZE_ENUM substrate_spec;
	xy_vect wafer_pos;
	zrxry_vect ws_expect_tilt;
	zrxry_vect level_result_p;
	}param_EC4T_set_ws_position_all_by_fls;
	 
	struct 
	{ 
	SMEE_ALIGN_TYPE_ENUM align_type;
	SMEE_SUBSTRATE_SIZE_ENUM wafer_size;
	SMEE_UINT32 nr_marks;
	xy_vect mark_norminal_positions[EC4T_MAX_NR_SUBSTRATE_MARKS];
	EC4T_WA_ALIGN_RECIPE_STRUCT oa_align_recipe;
	EC4T_UPDATE_WA_BASELINE_RESULT_STRUCT update_oa_baseline_result_p;
	EC4A_ALIGN_MODEL_RESULT_STRUCT align_result_p;
	}param_EC4T_substrate_align;
	 
	struct 
	{ 
	EC4T_RETI_ALIGN_SPC_STRUCT align_spec;
	EC4T_UPDATE_TTL_BASELINE_RESULT_STRUCT ttl_baseline_result_p;
	EC4A_COARSE_RETICLE_ALIGN_RESULT_STRUCT cora_result_p;
	EC4A_FINE_RETICLE_ALIGN_RESULT_STRUCT fira_result_p;
	}param_EC4T_reticle_align;
	 
	struct 
	{ 
	SMEE_ALIGN_TYPE_ENUM align_type;
	SMEE_SUBSTRATE_SIZE_ENUM ePlateType;
	xyrzzrxry_vect ws_pos;
	SMEE_DOUBLE z_search_range;
	zrxry_vect focused_ws_pos_p;
	SMEE_DOUBLE focused_fls_z_p;
	}param_EC4T_search_focus;
	 
	struct 
	{ 
	SMEE_ALIGN_TYPE_ENUM align_type;
	SMEE_SUBSTRATE_SIZE_ENUM wafer_size;
	xy_vect mark_nominal_pos;
	EC4T_WA_ALIGN_RECIPE_STRUCT oa_align_recipe;
	EC4T_WA_ALIGN_RESULT_STRUCT align_result_p;
	}param_EC4T_wa_align;
	 
	struct 
	{ 
	xy_vect mark_norminal_pos;
	EC4T_ALIGN_RECIPE_STRUCT ttl_align_recipe;
	EC4T_TTL_ALIGN_RESULT_STRUCT align_result_p;
	}param_EC4T_TTL_align;
	 
	struct 
	{ 
	SMEE_ALIGN_TYPE_ENUM align_type;
	EC4T_UPDATE_WA_BASELINE_RESULT_STRUCT oa_baseline_result_p;
	}param_EC4T_update_wa_baseline;
	 
	struct 
	{ 
	EC4T_UPDATE_TTL_BASELINE_RESULT_STRUCT ttl_baseline_result_p;
	}param_EC4T_update_ttl_baseline;
	 
}ECVT_Maintenance_PARAM_UNION;

typedef enum
{
	EC4T_MAINTENANCE_MIN,
    EC4T_DO_GLOBAL_LEVEL_ON_SUBSTRATE,
    EC4T_DO_GLOBAL_LEVEL_ON_WS_FIDUCIAL,
    EC4T_SET_WS_POSITION_ALL_BY_FLS,
    EC4T_SUBSTRATE_ALIGN,
    EC4T_RETICLE_ALIGN,
    EC4T_SEARCH_FOCUS,
    EC4T_WA_ALIGN,
    EC4T_TTL_ALIGN,
    EC4T_UPDATE_WA_BASELINE,
    EC4T_UPDATE_TTL_BASELINE,
	EC4T_MAINTENANCE_MAX
}MAIN_FUNCTION_CODE_ENUM;

class DoubleSpinBoxDelegate;
class GlobalSubstrateDelegate;

//************************************************************************
class ECVTMaintenance:public SMEE::Widget, private Ui::ECVTMaintenance
{
    Q_OBJECT

    public:
        ECVTMaintenance(QWidget * parent = 0);
        ~ECVTMaintenance();
		void performFunction(int funcCode);
    signals:
    	void send_log(int flag,const QString title,const QString text);
		void performFuncSignal(int funcCode);
	private:
        MAIN_FUNCTION_CODE_ENUM m_func;
        ECVT_Maintenance_PARAM_UNION u_param;
        QButtonGroup  *SwichButtonG ; //侧栏按钮组对象指针
		SpinBoxAgent *m_spinBoxAgent;
		
		DoubleSpinBoxDelegate *m_dpDelegateEx;
		GlobalSubstrateDelegate *m_globalDelegateEx;
        //信息输出栏
        void m_log( int flag,const QString title ,const QString text);
        void outputStart( QString fun_name);
        void outputEnd( QString fun_name,int rtn);
		string m_Datafile;
		string m_Datafile_2;
		string m_Datafile_3;
		string m_Datafile_4;


        //执行接口函数
        void m_exec_EC4T_do_global_level_on_substrate();
        void m_exec_EC4T_do_global_level_on_ws_fiducial();
        void m_exec_EC4T_set_ws_position_all_by_fls();
        void m_exec_EC4T_substrate_align();
        void m_exec_EC4T_reticle_align();
        void m_exec_EC4T_search_focus();
        void m_exec_EC4T_wa_align();
        void m_exec_EC4T_TTL_align();
        void m_exec_EC4T_update_wa_baseline();
        void m_exec_EC4T_update_ttl_baseline();

    public slots:

		//禁止界面全部按钮
		void disablePerformButtonSlot();

		//使能所有按钮
		void enablePerformButtonSlot();
        void do_global_level_on_substrate__scannum_slot();
		void substrate_align__nr_marks_slot();
		void Perform_FS4T_get_file_slot();
		void Perform_FS4T_get_file_2_slot();
		void Perform_FS4T_get_file_3_slot();
		void Perform_FS4T_get_file_4_slot();
	protected slots:

		//刷新界面数据
		void updateWindowData();

		//按钮对应的槽
		void performButtonClickedSlot(int button_id);


};

 #endif //_ECVT_MAINTENANCE_H_

///////////////////////////////////////////////////////////////////////////////
 #ifndef DELEGATE_H
 #define DELEGATE_H

 #include <QItemDelegate>
 #include <QModelIndex>
 #include <QObject>
 #include <QSize>
 #include <QSpinBox>


  class DoubleSpinBoxDelegate : public QItemDelegate
 {
     Q_OBJECT

 public:
     DoubleSpinBoxDelegate(QObject *parent = 0);

     QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                           const QModelIndex &index) const;

     void setEditorData(QWidget *editor, const QModelIndex &index) const;
     void setModelData(QWidget *editor, QAbstractItemModel *model,
                       const QModelIndex &index) const;

     void updateEditorGeometry(QWidget *editor,
         const QStyleOptionViewItem &option, const QModelIndex &index) const;
private:
 	SMEE::SpinBoxAgent* m_spinBoxAgent;
 };
 
 
  class GlobalSubstrateDelegate : public QItemDelegate
 {
     Q_OBJECT

 public:
     GlobalSubstrateDelegate(QObject *parent = 0);
     
     QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                           const QModelIndex &index) const;

     void setEditorData(QWidget *editor, const QModelIndex &index) const;
     void setModelData(QWidget *editor, QAbstractItemModel *model,
                       const QModelIndex &index) const;

     void updateEditorGeometry(QWidget *editor,
         const QStyleOptionViewItem &option, const QModelIndex &index) const;
 //private:
 //	SMEE::SpinBoxAgent* m_spinBoxAgent_1;
 };

 #endif 

