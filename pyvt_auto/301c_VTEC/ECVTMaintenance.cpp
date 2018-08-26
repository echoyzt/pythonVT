/**************************************************************************
* Copyright (C) 2008, 上海微电子装备有限公司
* All rights reserved.
* 产品号 : SS A600/20
* 所属组件 : EC
* 模块名称 : ECVT
* 文件名称 : ECVT.cpp
* 概要描述 :
* 历史记录 :
* 版本    日期         作者        内容

**************************************************************************/

#include "ECVTMaintenance.h"

ECVTMaintenance::ECVTMaintenance(QWidget *parent)
    :SMEE::Widget(parent), m_func((MAIN_FUNCTION_CODE_ENUM)(-1))
{
    setupUi(this);

    SwichButtonG = new QButtonGroup;//创建按钮组
    SwichButtonG->addButton(EC4T_do_global_level_on_substrate_qpb,(int)EC4T_DO_GLOBAL_LEVEL_ON_SUBSTRATE);
    SwichButtonG->addButton(EC4T_do_global_level_on_ws_fiducial_qpb,(int)EC4T_DO_GLOBAL_LEVEL_ON_WS_FIDUCIAL);
    SwichButtonG->addButton(EC4T_set_ws_position_all_by_fls_qpb,(int)EC4T_SET_WS_POSITION_ALL_BY_FLS);
    SwichButtonG->addButton(EC4T_substrate_align_qpb,(int)EC4T_SUBSTRATE_ALIGN);
    SwichButtonG->addButton(EC4T_reticle_align_qpb,(int)EC4T_RETICLE_ALIGN);
    SwichButtonG->addButton(EC4T_search_focus_qpb,(int)EC4T_SEARCH_FOCUS);
    SwichButtonG->addButton(EC4T_wa_align_qpb,(int)EC4T_WA_ALIGN);
    SwichButtonG->addButton(EC4T_TTL_align_qpb,(int)EC4T_TTL_ALIGN);
    SwichButtonG->addButton(EC4T_update_wa_baseline_qpb,(int)EC4T_UPDATE_WA_BASELINE);
    SwichButtonG->addButton(EC4T_update_ttl_baseline_qpb,(int)EC4T_UPDATE_TTL_BASELINE);
    SwichButtonG->setExclusive(true);
    connect(
    	SwichButtonG,
     	SIGNAL(buttonClicked(int)),
    	this,
    	SLOT(performButtonClickedSlot(int)));	

		connect(
		EC4T_do_global_level_on_substrate__scannum_qsb,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(do_global_level_on_substrate__scannum_slot()));
		
	    connect(EC4T_substrate_align__nr_marks_qsb,
		SIGNAL(valueChanged(int)),
		this,SLOT(substrate_align__nr_marks_slot()));

	substrate_align__nr_marks_slot();
    /***************代理*******************/
	m_dpDelegateEx = new DoubleSpinBoxDelegate;
	TW_Sub_Align->setItemDelegate(m_dpDelegateEx);
	
	
	m_globalDelegateEx = new GlobalSubstrateDelegate;
    TW_Global_Substrate->setItemDelegate(m_globalDelegateEx);
	
	
	
	for(int i=0;i<TW_Global_Substrate->columnCount();i++)
	{
		TW_Global_Substrate->setColumnWidth(i,120);
		
	}
	
	for(int i=0;i<TW_Sub_Align->columnCount();i++)
	{
		TW_Sub_Align->setColumnWidth(i,180);
		TW_Get_grid_cof->setColumnWidth(i,180);
	}
	
	
	//初始化新增行
	for(int j= 0;j < 1;j++)
	  {
		   QTableWidgetItem* cell_pp = NULL;
	       TW_Global_Substrate->insertRow(TW_Global_Substrate->rowCount());
		    cell_pp = new QTableWidgetItem(tr("0.000000"));
			TW_Global_Substrate->setItem(0, 0, cell_pp);

			cell_pp = new QTableWidgetItem(tr("0.000000"));
			TW_Global_Substrate->setItem(0, 1, cell_pp);

			cell_pp = new QTableWidgetItem(tr("0.000000"));
			TW_Global_Substrate->setItem(0, 2, cell_pp);

			cell_pp = new QTableWidgetItem(tr("0.000000"));
			TW_Global_Substrate->setItem(0, 3, cell_pp);
			
			cell_pp = new QTableWidgetItem(tr("0"));
			TW_Global_Substrate->setItem(0, 4, cell_pp);

	  }  
	//输入范围限定。
    m_spinBoxAgent = new SMEE::SpinBoxAgent("VTEC_Maintenance",this);
	param_range_check();
	

	TW_Get_grid_cof->setEditTriggers(QAbstractItemView::NoEditTriggers);


	connect(
		toolButton,
		SIGNAL(clicked()),
		this,
		SLOT(Perform_FS4T_get_file_slot()));
	connect(
		toolButton_2,
		SIGNAL(clicked()),
		this,
		SLOT(Perform_FS4T_get_file_2_slot()));
	connect(
		toolButton_3,
		SIGNAL(clicked()),
		this,
		SLOT(Perform_FS4T_get_file_3_slot()));
	connect(
		toolButton_4,
		SIGNAL(clicked()),
		this,
		SLOT(Perform_FS4T_get_file_4_slot()));
  
	//EC4T_search_focus__align_type_qcb->setCurrentIndex(2);
	//EC4T_wa_align__align_type_qcb->setCurrentIndex(2);
	//EC4T_substrate_align__align_type_qcb->setCurrentIndex(2);
	//EC4T_update_wa_baseline__align_type_qcb->setCurrentIndex(2);
}
void ECVTMaintenance::param_range_check()
{
	m_spinBoxAgent->RegisterSpinBox(EC4T_do_global_level_on_substrate__scannum_qsb,"EC4T_do_global_level_on_substrate__scannum");
	m_spinBoxAgent->RegisterSpinBox(EC4T_substrate_align__nr_marks_qsb,"EC4T_substrate_align__nr_marks");
	m_spinBoxAgent->RegisterSpinBox(EC4T_substrate_align__oa_align_recipe_matching_rate_qdsb,"oa_align_recipe_matching_rate");
}
void ECVTMaintenance::Perform_FS4T_get_file_slot()
{
	QString fileName = QFileDialog::getOpenFileName(this
		,tr("Open File"), "./SMEE"
		, tr("*.bmp")); 
    
	if (!fileName.isEmpty() && fileName != "")
		{ 
			if(fileName.contains("SMEE/"))
			{
				//fileDir1 = currentName.mid(0,currentName.indexOf("SMEE/"));
			   fileName = fileName.mid(fileName.indexOf("SMEE/") + 5);
			}
			else
			{
				fileName = fileName.mid(0,fileName.size());
			}
			  EC4T_reticle_align__align_spec_template_file_qle->setText(fileName);	

		}
	
	else
	{
	  MessageBox::critical(this, "Error", "File name empty.", MessageBox::Ok, 
			MessageBox::NoButton);
	  EC4T_reticle_align__align_spec_template_file_qle->setText("");
	}


	/*if(fileName.isEmpty())
	{
		EC4T_reticle_align__align_spec_template_file_qle->setText("");
		m_Datafile = "";
	}
	else
	{
		m_Datafile = fileName.toStdString();

		EC4T_reticle_align__align_spec_template_file_qle->setText(fileName);
		EC4T_reticle_align__align_spec_template_file_qle->setToolTip(fileName);
	}*/
}
void ECVTMaintenance::Perform_FS4T_get_file_2_slot()
{
	QString fileName = QFileDialog::getOpenFileName(this
		,tr("Open File"), "./SMEE"
		, tr("*.bmp")); 

     if (!fileName.isEmpty() && fileName != "")
		{ 
			if(fileName.contains("SMEE/"))
			{
				//fileDir1 = currentName.mid(0,currentName.indexOf("SMEE/"));
			   fileName = fileName.mid(fileName.indexOf("SMEE/") + 5);
			}
			else
			{
				fileName = fileName.mid(0,fileName.size());
			}
			  EC4T_TTL_align__ttl_align_recipe_template_file_qle->setText(fileName);	

		}
	
	else
	{
	  MessageBox::critical(this, "Error", "File name empty.", MessageBox::Ok, 
		MessageBox::NoButton);
	  EC4T_TTL_align__ttl_align_recipe_template_file_qle->setText("");
	}


	/*if(fileName.isEmpty())
	{
		EC4T_TTL_align__ttl_align_recipe_template_file_qle->setText("");
		m_Datafile_2 = "";
	}
	else
	{
		m_Datafile_2 = fileName.toStdString();

		EC4T_TTL_align__ttl_align_recipe_template_file_qle->setText(fileName);
		EC4T_TTL_align__ttl_align_recipe_template_file_qle->setToolTip(fileName);
	}*/
}
void ECVTMaintenance::Perform_FS4T_get_file_3_slot()
{
	QString fileName = QFileDialog::getOpenFileName(this
		,tr("Open File"), "./SMEE"
		, tr("*.bmp")); 

 
	if (!fileName.isEmpty() && fileName != "")
		{ 
			if(fileName.contains("SMEE/"))
			{
				//fileDir1 = currentName.mid(0,currentName.indexOf("SMEE/"));
			   fileName = fileName.mid(fileName.indexOf("SMEE/") + 5);
			}
			else
			{
				fileName = fileName.mid(0,fileName.size());
			}
			  EC4T_wa_align__oa_align_recipe_template_file_qle->setText(fileName);	

		}
	
	else
	{
		MessageBox::critical(this, "Error", "File name empty.", MessageBox::Ok, 
			MessageBox::NoButton);
	  EC4T_wa_align__oa_align_recipe_template_file_qle->setText("");
	}


	/*if(fileName.isEmpty())
	{
		EC4T_wa_align__oa_align_recipe_template_file_qle->setText("");
		m_Datafile_3 = "";
	}
	else
	{
		m_Datafile_3 = fileName.toStdString();

		EC4T_wa_align__oa_align_recipe_template_file_qle->setText(fileName);
		EC4T_wa_align__oa_align_recipe_template_file_qle->setToolTip(fileName);
	}*/
}
void ECVTMaintenance::Perform_FS4T_get_file_4_slot()
{
	QString fileName = QFileDialog::getOpenFileName(this
		,tr("Open File"), "./SMEE"
		, tr("*.bmp")); 


	if (!fileName.isEmpty() && fileName != "")
		{ 
			if(fileName.contains("SMEE/"))
			{
				//fileDir1 = currentName.mid(0,currentName.indexOf("SMEE/"));
			   fileName = fileName.mid(fileName.indexOf("SMEE/") + 5);
			}
			else
			{
				fileName = fileName.mid(0,fileName.size());
			}
			  EC4T_substrate_align__oa_align_recipe_template_file_qle->setText(fileName);	

		}
	
	else
		{
			MessageBox::critical(this, "Error", "File name empty.", MessageBox::Ok, 
			MessageBox::NoButton);
			EC4T_substrate_align__oa_align_recipe_template_file_qle->setText("");
		}

	/*if(fileName.isEmpty())
	{
		EC4T_substrate_align__oa_align_recipe_template_file_qle->setText("");
		m_Datafile_4 = "";
	}
	else
	{
		m_Datafile_4 = fileName.toStdString();

		EC4T_substrate_align__oa_align_recipe_template_file_qle->setText(fileName);
		EC4T_substrate_align__oa_align_recipe_template_file_qle->setToolTip(fileName);
	}*/
}
ECVTMaintenance::~ECVTMaintenance()
{
   
}

void ECVTMaintenance::substrate_align__nr_marks_slot()
{
	int newRowId = 0;

	int nrOfImages = EC4T_substrate_align__nr_marks_qsb->value();

	int rowToInsert = nrOfImages - TW_Sub_Align->rowCount();

	if (rowToInsert > 0)
	{
		while (rowToInsert > 0)
		{ 
			TW_Sub_Align->insertRow(TW_Sub_Align->rowCount());

			newRowId = TW_Sub_Align->rowCount() - 1;

			// 初始化新增行
			QTableWidgetItem* cell_p = NULL;
			cell_p = new QTableWidgetItem(tr("0.000000"));
			TW_Sub_Align->setItem(newRowId, 0, cell_p);

			cell_p = new QTableWidgetItem(tr("0.000000"));
			TW_Sub_Align->setItem(newRowId, 1, cell_p);

			rowToInsert--;
		}
	}
	else
	{
		while (rowToInsert < 0)
		{
			TW_Sub_Align->removeRow(TW_Sub_Align->rowCount()-1);

			rowToInsert++;
		}
	}
}


void ECVTMaintenance::do_global_level_on_substrate__scannum_slot()
{
	int newRowId = 0;

	int nrOfImages = EC4T_do_global_level_on_substrate__scannum_qsb->value();
	

	int rowToInsert = nrOfImages - TW_Global_Substrate->rowCount();

	if (rowToInsert > 0 )
	{
		while (rowToInsert > 0 )
		{ 
	       if(TW_Global_Substrate->rowCount() < 40)
		   {
			TW_Global_Substrate->insertRow(TW_Global_Substrate->rowCount());

			newRowId = TW_Global_Substrate->rowCount() - 1;

			// 初始化新增行
			QTableWidgetItem* cell_p = NULL;
			cell_p = new QTableWidgetItem(tr("0.000000"));
			TW_Global_Substrate->setItem(newRowId, 0, cell_p);

			cell_p = new QTableWidgetItem(tr("0.000000"));
			TW_Global_Substrate->setItem(newRowId, 1, cell_p);
			
			cell_p = new QTableWidgetItem(tr("0.000000"));
			TW_Global_Substrate->setItem(newRowId, 2, cell_p);
			
			cell_p = new QTableWidgetItem(tr("0.000000"));
			TW_Global_Substrate->setItem(newRowId, 3, cell_p);
			
			cell_p = new QTableWidgetItem(tr("0"));
			TW_Global_Substrate->setItem(newRowId, 4, cell_p);
		   }
			rowToInsert--;
		   	
		}
	}
	else
	{
		while (rowToInsert < 0)
		{
			TW_Global_Substrate->removeRow(TW_Global_Substrate->rowCount()-1);

			rowToInsert++;
		}
	}
}
void ECVTMaintenance::disablePerformButtonSlot()
{
	int i;
	for (i=EC4T_MAINTENANCE_MIN+1; i < EC4T_MAINTENANCE_MAX; i++)
	{
		if(SwichButtonG->button(i))
		{
			SwichButtonG->button(i)->setEnabled(false);
		}
	}
}

void ECVTMaintenance::enablePerformButtonSlot()
{
	int i;
	for (i=EC4T_MAINTENANCE_MIN+1; i < EC4T_MAINTENANCE_MAX; i++)
	{
		if(SwichButtonG->button(i))
		{
			SwichButtonG->button(i)->setEnabled(true);
		}
	}
	updateWindowData();
}

//刷新界面数据
void ECVTMaintenance::updateWindowData()//slot
{
	switch (m_func)
	{
	case EC4T_DO_GLOBAL_LEVEL_ON_SUBSTRATE:
        EC4T_do_global_level_on_substrate__level_result_p_z_qle->setText(QString("%1").arg(SMEE_SI_TO_MM(u_param.param_EC4T_do_global_level_on_substrate.level_result_p.z),0,'f',3));
        EC4T_do_global_level_on_substrate__level_result_p_rx_qle->setText(QString("%1").arg(SMEE_SI_TO_MRAD(u_param.param_EC4T_do_global_level_on_substrate.level_result_p.rx),0,'f',3));
        EC4T_do_global_level_on_substrate__level_result_p_ry_qle->setText(QString("%1").arg(SMEE_SI_TO_MRAD(u_param.param_EC4T_do_global_level_on_substrate.level_result_p.ry),0,'f',3)); 
    	break;
        //输出信息到输出栏
	case EC4T_DO_GLOBAL_LEVEL_ON_WS_FIDUCIAL:
        EC4T_do_global_level_on_ws_fiducial__level_result_p_z_qle->setText(QString("%1").arg(SMEE_SI_TO_MM(u_param.param_EC4T_do_global_level_on_ws_fiducial.level_result_p.z),0,'f',3));
        EC4T_do_global_level_on_ws_fiducial__level_result_p_rx_qle->setText(QString("%1").arg(SMEE_SI_TO_MRAD(u_param.param_EC4T_do_global_level_on_ws_fiducial.level_result_p.rx),0,'f',3));
        EC4T_do_global_level_on_ws_fiducial__level_result_p_ry_qle->setText(QString("%1").arg(SMEE_SI_TO_MRAD(u_param.param_EC4T_do_global_level_on_ws_fiducial.level_result_p.ry),0,'f',3));
        EC4T_do_global_level_on_ws_fiducial__substrate_cuniform_p_z_qle->setText(QString("%1").arg(SMEE_SI_TO_MM(u_param.param_EC4T_do_global_level_on_ws_fiducial.substrate_cuniform_p.z),0,'f',3));
        EC4T_do_global_level_on_ws_fiducial__substrate_cuniform_p_rx_qle->setText(QString("%1").arg(SMEE_SI_TO_MRAD(u_param.param_EC4T_do_global_level_on_ws_fiducial.substrate_cuniform_p.rx),0,'f',3));
        EC4T_do_global_level_on_ws_fiducial__substrate_cuniform_p_ry_qle->setText(QString("%1").arg(SMEE_SI_TO_MRAD(u_param.param_EC4T_do_global_level_on_ws_fiducial.substrate_cuniform_p.ry),0,'f',3));
    	break;
        //输出信息到输出栏
	case EC4T_SET_WS_POSITION_ALL_BY_FLS:
        EC4T_set_ws_position_all_by_fls__level_result_p_z_qle->setText(QString("%1").arg(SMEE_SI_TO_MM(u_param.param_EC4T_set_ws_position_all_by_fls.level_result_p.z),0,'f',3));
        EC4T_set_ws_position_all_by_fls__level_result_p_rx_qle->setText(QString("%1").arg(SMEE_SI_TO_MRAD(u_param.param_EC4T_set_ws_position_all_by_fls.level_result_p.rx),0,'f',3));
        EC4T_set_ws_position_all_by_fls__level_result_p_ry_qle->setText(QString("%1").arg(SMEE_SI_TO_MRAD(u_param.param_EC4T_set_ws_position_all_by_fls.level_result_p.ry),0,'f',3));
    	break;
        //输出信息到输出栏
	case EC4T_SUBSTRATE_ALIGN:
        EC4T_substrate_align__update_oa_baseline_result_p_aim_pos_x_qle->setText(QString("%1").arg(u_param.param_EC4T_substrate_align.update_oa_baseline_result_p.aim_pos.x,0,'f',3));
        EC4T_substrate_align__update_oa_baseline_result_p_aim_pos_y_qle->setText(QString("%1").arg(u_param.param_EC4T_substrate_align.update_oa_baseline_result_p.aim_pos.y,0,'f',3));
        /*EC4T_substrate_align__align_result_p_error_code_qle->setText(QString("%1").arg(u_param.param_EC4T_substrate_align.align_result_p.error_code));*/
        EC4T_substrate_align__align_result_p_wcs_to_wscs_trans_x_qle->setText(QString("%1").arg(SMEE_SI_TO_MM(u_param.param_EC4T_substrate_align.align_result_p.wcs_to_wscs_trans.x),0,'f',3));
        EC4T_substrate_align__align_result_p_wcs_to_wscs_trans_y_qle->setText(QString("%1").arg(SMEE_SI_TO_MM(u_param.param_EC4T_substrate_align.align_result_p.wcs_to_wscs_trans.y),0,'f',3));
        EC4T_substrate_align__align_result_p_wcs_to_wscs_rot_qle->setText(QString("%1").arg(SMEE_SI_TO_MRAD(u_param.param_EC4T_substrate_align.align_result_p.wcs_to_wscs_rot),0,'f',3));
        EC4T_substrate_align__align_result_p_wcs_to_wscs_othro_qle->setText(QString("%1").arg(SMEE_SI_TO_MRAD(u_param.param_EC4T_substrate_align.align_result_p.wcs_to_wscs_othro),0,'f',3));
        EC4T_substrate_align__align_result_p_wcs_to_wscs_mag_x_qle->setText(QString("%1").arg(SMEE_SI_TO_PPM(u_param.param_EC4T_substrate_align.align_result_p.wcs_to_wscs_mag_x),0,'f',3));
        EC4T_substrate_align__align_result_p_wcs_to_wscs_mag_y_qle->setText(QString("%1").arg(SMEE_SI_TO_PPM(u_param.param_EC4T_substrate_align.align_result_p.wcs_to_wscs_mag_y),0,'f',3));

		TW_Get_grid_cof->setRowCount(EC4A_NR_GRID_COEFS);
		for(int i=0;i<EC4A_NR_GRID_COEFS;i++)
		{
			QTableWidgetItem *item0 = new QTableWidgetItem;
			item0->setText(QString("%1").arg(u_param.param_EC4T_substrate_align.align_result_p.grid_coef_x[i]));
			TW_Get_grid_cof->setItem(i,0,item0);

			QTableWidgetItem *item1 = new QTableWidgetItem;
			item1->setText(QString("%1").arg(u_param.param_EC4T_substrate_align.align_result_p.grid_coef_y[i]));
			TW_Get_grid_cof->setItem(i,1,item1);
		}
		break;
        //输出信息到输出栏
	case EC4T_RETICLE_ALIGN:
        EC4T_reticle_align__ttl_baseline_result_p_AE_ref_pos_x_qle->setText(QString("%1").arg(SMEE_SI_TO_MM(u_param.param_EC4T_reticle_align.ttl_baseline_result_p.mark_pos_in_ccd.x),0,'f',3));
        EC4T_reticle_align__ttl_baseline_result_p_AE_ref_pos_y_qle->setText(QString("%1").arg(SMEE_SI_TO_MM(u_param.param_EC4T_reticle_align.ttl_baseline_result_p.mark_pos_in_ccd.y),0,'f',3));
        /*EC4T_reticle_align__cora_result_p_error_code_qle->setText(QString("%1").arg(u_param.param_EC4T_reticle_align.cora_result_p.error_code));*/
        EC4T_reticle_align__cora_result_p_rcs_to_rscs_trans_x_qle->setText(QString("%1").arg(SMEE_SI_TO_MM(u_param.param_EC4T_reticle_align.cora_result_p.rcs_to_rscs_trans.x),0,'f',3));
        EC4T_reticle_align__cora_result_p_rcs_to_rscs_trans_y_qle->setText(QString("%1").arg(SMEE_SI_TO_MM(u_param.param_EC4T_reticle_align.cora_result_p.rcs_to_rscs_trans.y),0,'f',3));
        EC4T_reticle_align__cora_result_p_rcs_to_rscs_rot_qle->setText(QString("%1").arg(SMEE_SI_TO_MRAD(u_param.param_EC4T_reticle_align.cora_result_p.rcs_to_rscs_rot),0,'f',3));
        EC4T_reticle_align__cora_result_p_rcs_to_rscs_mag_qle->setText(QString("%1").arg(SMEE_SI_TO_PPM(u_param.param_EC4T_reticle_align.cora_result_p.rcs_to_rscs_mag),0,'f',3));
        /*EC4T_reticle_align__fira_result_p_error_code_qle->setText(QString("%1").arg(u_param.param_EC4T_reticle_align.fira_result_p.error_code));*/
        EC4T_reticle_align__fira_result_p_rcs_to_wzcs_trans_x_qle->setText(QString("%1").arg(SMEE_SI_TO_MM(u_param.param_EC4T_reticle_align.fira_result_p.rcs_to_wzcs_trans.x),0,'f',3));
        EC4T_reticle_align__fira_result_p_rcs_to_wzcs_trans_y_qle->setText(QString("%1").arg(SMEE_SI_TO_MM(u_param.param_EC4T_reticle_align.fira_result_p.rcs_to_wzcs_trans.y),0,'f',3));
        EC4T_reticle_align__fira_result_p_rcs_to_wzcs_rot_qle->setText(QString("%1").arg(SMEE_SI_TO_MRAD(u_param.param_EC4T_reticle_align.fira_result_p.rcs_to_wzcs_rot),0,'f',3));
        EC4T_reticle_align__fira_result_p_rcs_to_wzcs_mag_qle->setText(QString("%1").arg(SMEE_SI_TO_PPM(u_param.param_EC4T_reticle_align.fira_result_p.rcs_to_wzcs_mag),0,'f',3));
    	break;
        //输出信息到输出栏
	case EC4T_SEARCH_FOCUS:
        EC4T_search_focus__focused_ws_pos_p_z_qle->setText(QString("%1").arg(SMEE_SI_TO_MM(u_param.param_EC4T_search_focus.focused_ws_pos_p.z),0,'f',3));
        EC4T_search_focus__focused_ws_pos_p_rx_qle->setText(QString("%1").arg(SMEE_SI_TO_MRAD(u_param.param_EC4T_search_focus.focused_ws_pos_p.rx),0,'f',3));
        EC4T_search_focus__focused_ws_pos_p_ry_qle->setText(QString("%1").arg(SMEE_SI_TO_MRAD(u_param.param_EC4T_search_focus.focused_ws_pos_p.ry),0,'f',3));
        EC4T_search_focus__focused_fls_z_p_qle->setText(QString("%1").arg(SMEE_SI_TO_MM(u_param.param_EC4T_search_focus.focused_fls_z_p),0,'f',3));
    	break;
        //输出信息到输出栏
	case EC4T_WA_ALIGN:
        EC4T_wa_align__align_result_p_mark_pos_in_ccd_x_qle->setText(QString("%1").arg(u_param.param_EC4T_wa_align.align_result_p.mark_pos_in_ccd.x,0,'f',3));
        EC4T_wa_align__align_result_p_mark_pos_in_ccd_y_qle->setText(QString("%1").arg(u_param.param_EC4T_wa_align.align_result_p.mark_pos_in_ccd.y,0,'f',3));
        EC4T_wa_align__align_result_p_mark_pos_in_wzcs_x_qle->setText(QString("%1").arg(SMEE_SI_TO_MM(u_param.param_EC4T_wa_align.align_result_p.mark_pos_in_wzcs.x),0,'f',3));
        EC4T_wa_align__align_result_p_mark_pos_in_wzcs_y_qle->setText(QString("%1").arg(SMEE_SI_TO_MM(u_param.param_EC4T_wa_align.align_result_p.mark_pos_in_wzcs.y),0,'f',3));
        EC4T_wa_align__align_result_p_match_rate_qle->setText(QString("%1").arg(u_param.param_EC4T_wa_align.align_result_p.match_rate*100,0,'f',3));
        EC4T_wa_align__align_result_p_align_pos_x_qle->setText(QString("%1").arg(SMEE_SI_TO_MM(u_param.param_EC4T_wa_align.align_result_p.align_pos.x),0,'f',3));
        EC4T_wa_align__align_result_p_align_pos_y_qle->setText(QString("%1").arg(SMEE_SI_TO_MM(u_param.param_EC4T_wa_align.align_result_p.align_pos.y),0,'f',3));
        EC4T_wa_align__align_result_p_align_pos_rz_qle->setText(QString("%1").arg(SMEE_SI_TO_MM(u_param.param_EC4T_wa_align.align_result_p.align_pos.rz),0,'f',3));
        EC4T_wa_align__align_result_p_ws_meas_pos_x_qle->setText(QString("%1").arg(SMEE_SI_TO_MM(u_param.param_EC4T_wa_align.align_result_p.ws_meas_pos.x),0,'f',3));
        EC4T_wa_align__align_result_p_ws_meas_pos_y_qle->setText(QString("%1").arg(SMEE_SI_TO_MM(u_param.param_EC4T_wa_align.align_result_p.ws_meas_pos.y),0,'f',3));
        EC4T_wa_align__align_result_p_ws_meas_pos_rz_qle->setText(QString("%1").arg(SMEE_SI_TO_MM(u_param.param_EC4T_wa_align.align_result_p.ws_meas_pos.rz),0,'f',3));
        EC4T_wa_align__align_result_p_mark_offset_in_wscs_x_qle->setText(QString("%1").arg(SMEE_SI_TO_MM(u_param.param_EC4T_wa_align.align_result_p.mark_offset_in_wscs.x),0,'f',3));
        EC4T_wa_align__align_result_p_mark_offset_in_wscs_y_qle->setText(QString("%1").arg(SMEE_SI_TO_MM(u_param.param_EC4T_wa_align.align_result_p.mark_offset_in_wscs.y),0,'f',3));
    	break;
        //输出信息到输出栏
	case EC4T_TTL_ALIGN:
        EC4T_TTL_align__align_result_p_mark_pos_in_ccd_x_qle->setText(QString("%1").arg(u_param.param_EC4T_TTL_align.align_result_p.mark_pos_in_ccd.x,0,'f',3));
        EC4T_TTL_align__align_result_p_mark_pos_in_ccd_y_qle->setText(QString("%1").arg(u_param.param_EC4T_TTL_align.align_result_p.mark_pos_in_ccd.y,0,'f',3));
        EC4T_TTL_align__align_result_p_mark_pos_in_wzcs_x_qle->setText(QString("%1").arg(SMEE_SI_TO_MM(u_param.param_EC4T_TTL_align.align_result_p.mark_pos_in_wzcs.x),0,'f',3));
        EC4T_TTL_align__align_result_p_mark_pos_in_wzcs_y_qle->setText(QString("%1").arg(SMEE_SI_TO_MM(u_param.param_EC4T_TTL_align.align_result_p.mark_pos_in_wzcs.y),0,'f',3));
        EC4T_TTL_align__align_result_p_match_rate_qle->setText(QString("%1").arg(u_param.param_EC4T_TTL_align.align_result_p.match_rate*100,0,'f',3));
        EC4T_TTL_align__align_result_p_align_pos_x_qle->setText(QString("%1").arg(SMEE_SI_TO_MM(u_param.param_EC4T_TTL_align.align_result_p.align_pos.x),0,'f',3));
        EC4T_TTL_align__align_result_p_align_pos_y_qle->setText(QString("%1").arg(SMEE_SI_TO_MM(u_param.param_EC4T_TTL_align.align_result_p.align_pos.y),0,'f',3));
        EC4T_TTL_align__align_result_p_align_pos_rz_qle->setText(QString("%1").arg(SMEE_SI_TO_MRAD(u_param.param_EC4T_TTL_align.align_result_p.align_pos.rz),0,'f',3));
        EC4T_TTL_align__align_result_p_rs_meas_pos_x_qle->setText(QString("%1").arg(SMEE_SI_TO_MM(u_param.param_EC4T_TTL_align.align_result_p.rs_meas_pos.x),0,'f',3));
        EC4T_TTL_align__align_result_p_rs_meas_pos_y_qle->setText(QString("%1").arg(SMEE_SI_TO_MM(u_param.param_EC4T_TTL_align.align_result_p.rs_meas_pos.y),0,'f',3));
        EC4T_TTL_align__align_result_p_rs_meas_pos_rz_qle->setText(QString("%1").arg(SMEE_SI_TO_MM(u_param.param_EC4T_TTL_align.align_result_p.rs_meas_pos.rz),0,'f',3));
        EC4T_TTL_align__align_result_p_ws_meas_pos_x_qle->setText(QString("%1").arg(SMEE_SI_TO_MM(u_param.param_EC4T_TTL_align.align_result_p.ws_meas_pos.x),0,'f',3));
        EC4T_TTL_align__align_result_p_ws_meas_pos_y_qle->setText(QString("%1").arg(SMEE_SI_TO_MM(u_param.param_EC4T_TTL_align.align_result_p.ws_meas_pos.y),0,'f',3));
        EC4T_TTL_align__align_result_p_ws_meas_pos_rz_qle->setText(QString("%1").arg(SMEE_SI_TO_MM(u_param.param_EC4T_TTL_align.align_result_p.ws_meas_pos.rz),0,'f',3));
        EC4T_TTL_align__align_result_p_mark_offset_in_rzcs_x_qle->setText(QString("%1").arg(SMEE_SI_TO_MM(u_param.param_EC4T_TTL_align.align_result_p.mark_offset_in_rzcs.x),0,'f',3));
        EC4T_TTL_align__align_result_p_mark_offset_in_rzcs_y_qle->setText(QString("%1").arg(SMEE_SI_TO_MM(u_param.param_EC4T_TTL_align.align_result_p.mark_offset_in_rzcs.y),0,'f',3));
        EC4T_TTL_align__align_result_p_mark_offset_in_wscs_x_qle->setText(QString("%1").arg(SMEE_SI_TO_MM(u_param.param_EC4T_TTL_align.align_result_p.mark_offset_in_wscs.x),0,'f',3));
        EC4T_TTL_align__align_result_p_mark_offset_in_wscs_y_qle->setText(QString("%1").arg(SMEE_SI_TO_MM(u_param.param_EC4T_TTL_align.align_result_p.mark_offset_in_wscs.y),0,'f',3));
    	break;
        //输出信息到输出栏
	case EC4T_UPDATE_WA_BASELINE:
        EC4T_update_wa_baseline__oa_baseline_result_p_aim_pos_x_qle->setText(QString("%1").arg(u_param.param_EC4T_update_wa_baseline.oa_baseline_result_p.aim_pos.x,0,'f',3));
        EC4T_update_wa_baseline__oa_baseline_result_p_aim_pos_y_qle->setText(QString("%1").arg(u_param.param_EC4T_update_wa_baseline.oa_baseline_result_p.aim_pos.y,0,'f',3));
    	break;
        //输出信息到输出栏
	case EC4T_UPDATE_TTL_BASELINE:
       // EC4T_update_ttl_baseline__ttl_baseline_result_p_AE_ref_pos_x_qle->setText(QString("%1").arg(SMEE_SI_TO_MM(u_param.param_EC4T_update_ttl_baseline.ttl_baseline_result_p.AE_ref_pos.x),0,'f',3));
        //EC4T_update_ttl_baseline__ttl_baseline_result_p_AE_ref_pos_y_qle->setText(QString("%1").arg(SMEE_SI_TO_MM(u_param.param_EC4T_update_ttl_baseline.ttl_baseline_result_p.AE_ref_pos.y),0,'f',3));
    	EC4T_update_ttl_baseline__ttl_baseline_result_p_Mark_pos_x_qle->setText(QString("%1").arg(u_param.param_EC4T_update_ttl_baseline.ttl_baseline_result_p.mark_pos_in_ccd.x,0,'f',3));
		EC4T_update_ttl_baseline__ttl_baseline_result_p_Mark_pos_y_qle->setText(QString("%1").arg(u_param.param_EC4T_update_ttl_baseline.ttl_baseline_result_p.mark_pos_in_ccd.y,0,'f',3));                            
		EC4T_update_ttl_baseline__ttl_baseline_result_p_Match_rate_qle->setText(QString("%1").arg((u_param.param_EC4T_update_ttl_baseline.ttl_baseline_result_p.matching_rate_in_ccd)*100,0,'f',3));
	
		
		break;
        //输出信息到输出栏
	default:
		break;
	}
}
//****************传递信息********************************************************************************************
void ECVTMaintenance::m_log(int flag,const QString title,const QString text)
{
	emit send_log(flag,title,text);
}
void ECVTMaintenance::outputStart( QString fun_name)
{
	m_log(OK,QString("ECVT"),QString("%1 start.").arg(fun_name));
}

void ECVTMaintenance::outputEnd( QString fun_name,int rtn)
{
	if(rtn == OK)
	{
		m_log(OK,QString("ECVT"),QString("%1 success.").arg(fun_name));
	}
	else
	{
		m_log(rtn,QString("ECVT"),QString("%1 failed.  Error Code:0x%2").arg(fun_name).arg(rtn, 0, 16));
	}
}

//----------------------------------
void ECVTMaintenance::performButtonClickedSlot(int button_id)
{
	switch (button_id)
	{
	case (int)EC4T_DO_GLOBAL_LEVEL_ON_SUBSTRATE:
	if(m_spinBoxAgent->CheckIsValid(EC4T_do_global_level_on_substrate__scannum_qsb))
	{
		m_func=EC4T_DO_GLOBAL_LEVEL_ON_SUBSTRATE;
    	emit performFuncSignal(button_id);
	}
	else
		{
			SMEE::MessageBox::critical(this,"Error","The red value is out of range.");
		}
    	break;
	case (int)EC4T_DO_GLOBAL_LEVEL_ON_WS_FIDUCIAL:
		m_func=EC4T_DO_GLOBAL_LEVEL_ON_WS_FIDUCIAL;
    	emit performFuncSignal(button_id);
    	break;
	case (int)EC4T_SET_WS_POSITION_ALL_BY_FLS:
		m_func=EC4T_SET_WS_POSITION_ALL_BY_FLS;
    	emit performFuncSignal(button_id);
    	break;
	case (int)EC4T_SUBSTRATE_ALIGN:
		if( m_spinBoxAgent->CheckIsValid(EC4T_substrate_align__nr_marks_qsb) &&
			m_spinBoxAgent->CheckIsValid(EC4T_substrate_align__oa_align_recipe_matching_rate_qdsb) )
		{
			m_func=EC4T_SUBSTRATE_ALIGN;
			emit performFuncSignal(button_id);
		}
		else
		{
			SMEE::MessageBox::critical(this,"Error","The red value is out of range.");
		}
    	break;
	case (int)EC4T_RETICLE_ALIGN:
		m_func=EC4T_RETICLE_ALIGN;
    	emit performFuncSignal(button_id);
    	break;
	case (int)EC4T_SEARCH_FOCUS:
		m_func=EC4T_SEARCH_FOCUS;
    	emit performFuncSignal(button_id);
    	break;
	case (int)EC4T_WA_ALIGN:
		m_func=EC4T_WA_ALIGN;
    	emit performFuncSignal(button_id);
    	break;
	case (int)EC4T_TTL_ALIGN:
		m_func=EC4T_TTL_ALIGN;
    	emit performFuncSignal(button_id);
    	break;
	case (int)EC4T_UPDATE_WA_BASELINE:
		m_func=EC4T_UPDATE_WA_BASELINE;
    	emit performFuncSignal(button_id);
    	break;
	case (int)EC4T_UPDATE_TTL_BASELINE:
		m_func=EC4T_UPDATE_TTL_BASELINE;
    	emit performFuncSignal(button_id);
    	break;
	default:
		break;
	}
}
void ECVTMaintenance::performFunction(int funcCode)
{
    switch(funcCode)
    {
    case EC4T_DO_GLOBAL_LEVEL_ON_SUBSTRATE:
        m_exec_EC4T_do_global_level_on_substrate();
        break;
    case EC4T_DO_GLOBAL_LEVEL_ON_WS_FIDUCIAL:
        m_exec_EC4T_do_global_level_on_ws_fiducial();
        break;
    case EC4T_SET_WS_POSITION_ALL_BY_FLS:
        m_exec_EC4T_set_ws_position_all_by_fls();
        break;
    case EC4T_SUBSTRATE_ALIGN:
        m_exec_EC4T_substrate_align();
        break;
    case EC4T_RETICLE_ALIGN:
        m_exec_EC4T_reticle_align();
        break;
    case EC4T_SEARCH_FOCUS:
        m_exec_EC4T_search_focus();
        break;
    case EC4T_WA_ALIGN:
        m_exec_EC4T_wa_align();
        break;
    case EC4T_TTL_ALIGN:
        m_exec_EC4T_TTL_align();
        break;
    case EC4T_UPDATE_WA_BASELINE:
        m_exec_EC4T_update_wa_baseline();
        break;
    case EC4T_UPDATE_TTL_BASELINE:
        m_exec_EC4T_update_ttl_baseline();
        break;
    default:
        //m_ecvt->m_log(QString("ERROR!Can't find corresponding func code."));
        break;
    }
}

void ECVTMaintenance::m_exec_EC4T_do_global_level_on_substrate()
{
    int error_code = OK;
	int num = 0;

	QString func_name = "EC4T_do_global_level_on_substrate";
	//输出信息到输出栏
	outputStart(func_name);
	   u_param.param_EC4T_do_global_level_on_substrate.do_global_level = EC4T_do_global_level_on_substrate_global_level_qckb->isChecked();
	 u_param.param_EC4T_do_global_level_on_substrate.do_mapping = EC4T_do_global_level_on_substrate_mapping_qckb->isChecked();
	
    //获取输入参数
    switch(EC4T_do_global_level_on_substrate__substrate_spec_qcb->currentIndex())
    {
    case 0:
    u_param.param_EC4T_do_global_level_on_substrate.substrate_spec = SMEE_WAFER_2_INCH;
        break;
    case 1:
    u_param.param_EC4T_do_global_level_on_substrate.substrate_spec = SMEE_WAFER_3_INCH;
        break;
    case 2:
    u_param.param_EC4T_do_global_level_on_substrate.substrate_spec = SMEE_WAFER_4_INCH;
        break;
    case 3:
    u_param.param_EC4T_do_global_level_on_substrate.substrate_spec = SMEE_WAFER_5_INCH;
        break;
    case 4:
    u_param.param_EC4T_do_global_level_on_substrate.substrate_spec = SMEE_WAFER_6_INCH;
        break;
    case 5:
    u_param.param_EC4T_do_global_level_on_substrate.substrate_spec = SMEE_WAFER_8_INCH;
        break;
    case 6:
    u_param.param_EC4T_do_global_level_on_substrate.substrate_spec = SMEE_WAFER_12_INCH;
        break;
    case 7:
    u_param.param_EC4T_do_global_level_on_substrate.substrate_spec = SMEE_WAFER_18_INCH;
        break;
    default:
        //m_log(QString("EC4T_do_global_level_on_substrate: Enum Parameter Error!"));
        break;
    }
    u_param.param_EC4T_do_global_level_on_substrate.substrate_thickness = SMEE_UM_TO_SI(EC4T_do_global_level_on_substrate__substrate_thickness_qdsb->value());
    u_param.param_EC4T_do_global_level_on_substrate.user_focus_offset = SMEE_UM_TO_SI(EC4T_do_global_level_on_substrate__user_focus_offset_qdsb->value());
    //u_param.param_EC4T_do_global_level_on_substrate.nr_level_points = EC4T_do_global_level_on_substrate__nr_level_points_qsb->value();
    u_param.param_EC4T_do_global_level_on_substrate.global_middle_point.x = SMEE_MM_TO_SI(EC4T_do_global_level_on_substrate__middle_point_x_qdsb->value());
    u_param.param_EC4T_do_global_level_on_substrate.global_middle_point.y = SMEE_MM_TO_SI(EC4T_do_global_level_on_substrate__middle_point_y_qdsb->value());   
    u_param.param_EC4T_do_global_level_on_substrate.mapping_route.iScanNum = EC4T_do_global_level_on_substrate__scannum_qsb->value();
	 
	 num = (u_param.param_EC4T_do_global_level_on_substrate.mapping_route.iScanNum>EC4A_MAPPING_SCAN_NUM)?
				EC4A_MAPPING_SCAN_NUM:u_param.param_EC4T_do_global_level_on_substrate.mapping_route.iScanNum;
	//TW_Global_Substrate
	
	
	   
	for(int m = 0; m < num; m++)
	{
		QTableWidgetItem* cell_p = NULL;
		//cell_p = new QTableWidgetItem;
		
		 cell_p = TW_Global_Substrate->item(m, 0);
		 u_param.param_EC4T_do_global_level_on_substrate.mapping_route.sScanRoute[m].sStartPos.x =SMEE_MM_TO_SI (cell_p->text().toDouble());
	   
	      cell_p = TW_Global_Substrate->item(m, 1);
		 u_param.param_EC4T_do_global_level_on_substrate.mapping_route.sScanRoute[m].sStartPos.y = SMEE_MM_TO_SI(cell_p->text().toDouble());
   
         cell_p = TW_Global_Substrate->item(m, 2);
		 u_param.param_EC4T_do_global_level_on_substrate.mapping_route.sScanRoute[m].sEndPos.x = SMEE_MM_TO_SI(cell_p->text().toDouble());
	
	     cell_p = TW_Global_Substrate->item(m, 3);
		 u_param.param_EC4T_do_global_level_on_substrate.mapping_route.sScanRoute[m].sEndPos.y = SMEE_MM_TO_SI(cell_p->text().toDouble());
		
		 cell_p = TW_Global_Substrate->item(m, 4);
		 u_param.param_EC4T_do_global_level_on_substrate.mapping_route.sScanRoute[m].uiSpotValid = cell_p->text().toInt(); 
	     
	}
	
	
	//执行函数
	
    error_code = EC4T_do_global_level_on_substrate(
	    u_param.param_EC4T_do_global_level_on_substrate.do_global_level, 
		u_param.param_EC4T_do_global_level_on_substrate.do_mapping, 
	
		u_param.param_EC4T_do_global_level_on_substrate.substrate_spec, 
		u_param.param_EC4T_do_global_level_on_substrate.substrate_thickness, 
		u_param.param_EC4T_do_global_level_on_substrate.user_focus_offset, 
		
		u_param.param_EC4T_do_global_level_on_substrate.global_middle_point,
	    &u_param.param_EC4T_do_global_level_on_substrate.mapping_route,
		
		//u_param.param_EC4T_do_global_level_on_substrate.nr_level_points, 
		&u_param.param_EC4T_do_global_level_on_substrate.level_result_p);
	

    //更新界面
   outputEnd(func_name,error_code);  
}

void ECVTMaintenance::m_exec_EC4T_do_global_level_on_ws_fiducial()
{
    int error_code = OK;

	QString func_name = "EC4T_do_global_level_on_ws_fiducial";
	//输出信息到输出栏
	outputStart(func_name);
    //获取输入参数
    u_param.param_EC4T_do_global_level_on_ws_fiducial.substrate_thickness = SMEE_UM_TO_SI(EC4T_do_global_level_on_ws_fiducial__substrate_thickness_qdsb->value());
    u_param.param_EC4T_do_global_level_on_ws_fiducial.user_focus_offset = SMEE_UM_TO_SI(EC4T_do_global_level_on_ws_fiducial__user_focus_offset_qdsb->value());

    //执行函数
    error_code = EC4T_do_global_level_on_ws_fiducial(
		u_param.param_EC4T_do_global_level_on_ws_fiducial.substrate_thickness, 
		u_param.param_EC4T_do_global_level_on_ws_fiducial.user_focus_offset, 
		&u_param.param_EC4T_do_global_level_on_ws_fiducial.level_result_p, 
		&u_param.param_EC4T_do_global_level_on_ws_fiducial.substrate_cuniform_p);

    //更新界面
    outputEnd(func_name,error_code);
}

void ECVTMaintenance::m_exec_EC4T_set_ws_position_all_by_fls()
{
    int error_code = OK;

	QString func_name = "EC4T_set_ws_position_all_by_fls";
	//输出信息到输出栏
	outputStart(func_name);
    //获取输入参数
    switch(EC4T_set_ws_position_all_by_fls__substrate_spec_qcb->currentIndex())
    {
    case 0:
    u_param.param_EC4T_set_ws_position_all_by_fls.substrate_spec = SMEE_WAFER_2_INCH;
        break;
    case 1:
    u_param.param_EC4T_set_ws_position_all_by_fls.substrate_spec = SMEE_WAFER_3_INCH;
        break;
    case 2:
    u_param.param_EC4T_set_ws_position_all_by_fls.substrate_spec = SMEE_WAFER_4_INCH;
        break;
    case 3:
    u_param.param_EC4T_set_ws_position_all_by_fls.substrate_spec = SMEE_WAFER_5_INCH;
        break;
    case 4:
    u_param.param_EC4T_set_ws_position_all_by_fls.substrate_spec = SMEE_WAFER_6_INCH;
        break;
    case 5:
    u_param.param_EC4T_set_ws_position_all_by_fls.substrate_spec = SMEE_WAFER_8_INCH;
        break;
    case 6:
    u_param.param_EC4T_set_ws_position_all_by_fls.substrate_spec = SMEE_WAFER_12_INCH;
        break;
    case 7:
    u_param.param_EC4T_set_ws_position_all_by_fls.substrate_spec = SMEE_WAFER_18_INCH;
        break;
    default:
        //m_log(QString("EC4T_set_ws_position_all_by_fls: Enum Parameter Error!"));
        break;
    }
    u_param.param_EC4T_set_ws_position_all_by_fls.wafer_pos.x = SMEE_MM_TO_SI(EC4T_set_ws_position_all_by_fls__wafer_pos_x_qdsb->value());
    u_param.param_EC4T_set_ws_position_all_by_fls.wafer_pos.y = SMEE_MM_TO_SI(EC4T_set_ws_position_all_by_fls__wafer_pos_y_qdsb->value());
    u_param.param_EC4T_set_ws_position_all_by_fls.ws_expect_tilt.z = SMEE_MM_TO_SI(EC4T_set_ws_position_all_by_fls__ws_expect_tilt_z_qdsb->value());
    u_param.param_EC4T_set_ws_position_all_by_fls.ws_expect_tilt.rx = SMEE_MRAD_TO_SI(EC4T_set_ws_position_all_by_fls__ws_expect_tilt_rx_qdsb->value());
    u_param.param_EC4T_set_ws_position_all_by_fls.ws_expect_tilt.ry = SMEE_MRAD_TO_SI(EC4T_set_ws_position_all_by_fls__ws_expect_tilt_ry_qdsb->value());

    //执行函数
    error_code = EC4T_set_ws_position_all_by_fls(
		u_param.param_EC4T_set_ws_position_all_by_fls.substrate_spec, 
		u_param.param_EC4T_set_ws_position_all_by_fls.wafer_pos, 
		u_param.param_EC4T_set_ws_position_all_by_fls.ws_expect_tilt,
		&u_param.param_EC4T_set_ws_position_all_by_fls.level_result_p);

    //更新界面
    outputEnd(func_name,error_code);
}

void ECVTMaintenance::m_exec_EC4T_substrate_align()
{
	int num = 0; 
    int error_code = OK;
	QTableWidgetItem *item = NULL;

	QString func_name = "EC4T_substrate_align";
	//输出信息到输出栏
	outputStart(func_name);
    //获取输入参数
    switch(EC4T_substrate_align__align_type_qcb->currentIndex())
    {
    case 0:
    u_param.param_EC4T_substrate_align.align_type = SMEE_ALIGN_OA;
        break;
    case 1:
    u_param.param_EC4T_substrate_align.align_type = SMEE_ALIGN_WBA;
        break;
    case 2:
    u_param.param_EC4T_substrate_align.align_type = SMEE_ALIGN_DT;
        break;
    case 3:
    u_param.param_EC4T_substrate_align.align_type = SMEE_ALIGN_NONE;
        break;
    case 4:
    u_param.param_EC4T_substrate_align.align_type = SMEE_ALIGN_TTL;
        break;
    default:
        //m_log(QString("EC4T_substrate_align: Enum Parameter Error!"));
        break;
    }
    switch(EC4T_substrate_align__wafer_size_qcb->currentIndex())
    {
    case 0:
    u_param.param_EC4T_substrate_align.wafer_size = SMEE_WAFER_2_INCH;
        break;
    case 1:
    u_param.param_EC4T_substrate_align.wafer_size = SMEE_WAFER_3_INCH;
        break;
    case 2:
    u_param.param_EC4T_substrate_align.wafer_size = SMEE_WAFER_4_INCH;
        break;
    case 3:
    u_param.param_EC4T_substrate_align.wafer_size = SMEE_WAFER_5_INCH;
        break;
    case 4:
    u_param.param_EC4T_substrate_align.wafer_size = SMEE_WAFER_6_INCH;
        break;
    case 5:
    u_param.param_EC4T_substrate_align.wafer_size = SMEE_WAFER_8_INCH;
        break;
    case 6:
    u_param.param_EC4T_substrate_align.wafer_size = SMEE_WAFER_12_INCH;
        break;
    case 7:
    u_param.param_EC4T_substrate_align.wafer_size = SMEE_WAFER_18_INCH;
        break;
    default:
        //m_log(QString("EC4T_substrate_align: Enum Parameter Error!"));
        break;
    }
    u_param.param_EC4T_substrate_align.nr_marks = EC4T_substrate_align__nr_marks_qsb->value();
	num = (u_param.param_EC4T_substrate_align.nr_marks>EC4T_MAX_NR_SUBSTRATE_MARKS)?EC4T_MAX_NR_SUBSTRATE_MARKS:u_param.param_EC4T_substrate_align.nr_marks;
	for(int i=0;i<num;i++)
	{
		item = TW_Sub_Align->item(i,0);
		u_param.param_EC4T_substrate_align.mark_norminal_positions[i].x = SMEE_MM_TO_SI(item->text().toDouble());

		item = TW_Sub_Align->item(i,1);
		u_param.param_EC4T_substrate_align.mark_norminal_positions[i].y = SMEE_MM_TO_SI(item->text().toDouble());
	}
  //printf("x = %g\n",u_param.param_EC4T_substrate_align.mark_norminal_positions[0].x);
	u_param.param_EC4T_substrate_align.oa_align_recipe.do_auto_focus = EC4T_substrate_align__oa_align_recipe_do_auto_focus_qckb->isChecked();
    u_param.param_EC4T_substrate_align.oa_align_recipe.perform_vert_compensation = EC4T_substrate_align__oa_align_recipe_perform_vert_compensation_qckb->isChecked();
    u_param.param_EC4T_substrate_align.oa_align_recipe.vert_compensation = SMEE_UM_TO_SI(EC4T_substrate_align__oa_align_recipe_vert_compensation_qdsb->value());
    u_param.param_EC4T_substrate_align.oa_align_recipe.matching_rate = EC4T_substrate_align__oa_align_recipe_matching_rate_qdsb->value()/100;
    memcpy(u_param.param_EC4T_substrate_align.oa_align_recipe.template_file,EC4T_substrate_align__oa_align_recipe_template_file_qle->text().toAscii(),sizeof(SMEE_CHAR)*EC4A_MAX_FILE_NAME_SIZE);

    //执行函数
    error_code = EC4T_substrate_align(
		u_param.param_EC4T_substrate_align.align_type, 
		u_param.param_EC4T_substrate_align.wafer_size, 
		u_param.param_EC4T_substrate_align.nr_marks, 
		u_param.param_EC4T_substrate_align.mark_norminal_positions, 
		u_param.param_EC4T_substrate_align.oa_align_recipe,
		&u_param.param_EC4T_substrate_align.update_oa_baseline_result_p, 
		&u_param.param_EC4T_substrate_align.align_result_p);

    //更新界面
    outputEnd(func_name,error_code);
}

void ECVTMaintenance::m_exec_EC4T_reticle_align()
{
    int error_code = OK;

	QString func_name = "EC4T_reticle_align";
	//输出信息到输出栏
	outputStart(func_name);
    //获取输入参数
    u_param.param_EC4T_reticle_align.align_spec.RM1_pos.x = SMEE_MM_TO_SI(EC4T_reticle_align__align_spec_RM1_pos_x_qdsb->value());
    u_param.param_EC4T_reticle_align.align_spec.RM1_pos.y = SMEE_MM_TO_SI(EC4T_reticle_align__align_spec_RM1_pos_y_qdsb->value());
    u_param.param_EC4T_reticle_align.align_spec.RM2_pos.x = SMEE_MM_TO_SI(EC4T_reticle_align__align_spec_RM2_pos_x_qdsb->value());
    u_param.param_EC4T_reticle_align.align_spec.RM2_pos.y = SMEE_MM_TO_SI(EC4T_reticle_align__align_spec_RM2_pos_y_qdsb->value());
    u_param.param_EC4T_reticle_align.align_spec.matching_rate = EC4T_reticle_align__align_spec_matching_rate_qdsb->value()/100;
    memcpy(u_param.param_EC4T_reticle_align.align_spec.template_file,EC4T_reticle_align__align_spec_template_file_qle->text().toAscii(),sizeof(SMEE_CHAR)*EC4A_MAX_FILE_NAME_SIZE);

    //执行函数
    error_code = EC4T_reticle_align(
		u_param.param_EC4T_reticle_align.align_spec, 
		&u_param.param_EC4T_reticle_align.ttl_baseline_result_p, 
		&u_param.param_EC4T_reticle_align.cora_result_p, 
		&u_param.param_EC4T_reticle_align.fira_result_p);

    //更新界面
    outputEnd(func_name,error_code);
}

void ECVTMaintenance::m_exec_EC4T_search_focus()
{
    int error_code = OK;

	QString func_name = "EC4T_search_focus";
	//输出信息到输出栏
	outputStart(func_name);
    //获取输入参数
    switch(EC4T_search_focus__align_type_qcb->currentIndex())
    {
    /*case 0:
    u_param.param_EC4T_search_focus.align_type = SMEE_ALIGN_NONE;
        break;
    case 1:
    u_param.param_EC4T_search_focus.align_type = SMEE_ALIGN_TTL;
        break;*/
    case 0:
    u_param.param_EC4T_search_focus.align_type = SMEE_ALIGN_OA;
        break;
    case 1:
    u_param.param_EC4T_search_focus.align_type = SMEE_ALIGN_WBA;
        break;
    case 2:
    u_param.param_EC4T_search_focus.align_type = SMEE_ALIGN_DT;
        break;
    default:
        //m_log(QString("EC4T_search_focus: Enum Parameter Error!"));
        break;
    }
    switch(EC4T_search_focus__ePlateType_qcb->currentIndex())
    {
    case 0:
    u_param.param_EC4T_search_focus.ePlateType = SMEE_WAFER_2_INCH;
        break;
    case 1:
    u_param.param_EC4T_search_focus.ePlateType = SMEE_WAFER_3_INCH;
        break;
    case 2:
    u_param.param_EC4T_search_focus.ePlateType = SMEE_WAFER_4_INCH;
        break;
    case 3:
    u_param.param_EC4T_search_focus.ePlateType = SMEE_WAFER_5_INCH;
        break;
    case 4:
    u_param.param_EC4T_search_focus.ePlateType = SMEE_WAFER_6_INCH;
        break;
    case 5:
    u_param.param_EC4T_search_focus.ePlateType = SMEE_WAFER_8_INCH;
        break;
    case 6:
    u_param.param_EC4T_search_focus.ePlateType = SMEE_WAFER_12_INCH;
        break;
    case 7:
    u_param.param_EC4T_search_focus.ePlateType = SMEE_WAFER_18_INCH;
        break;
    default:
        //m_log(QString("EC4T_search_focus: Enum Parameter Error!"));
        break;
    }
    u_param.param_EC4T_search_focus.ws_pos.x = SMEE_MM_TO_SI(EC4T_search_focus__ws_pos_x_qdsb->value());
    u_param.param_EC4T_search_focus.ws_pos.y = SMEE_MM_TO_SI(EC4T_search_focus__ws_pos_y_qdsb->value());
    u_param.param_EC4T_search_focus.ws_pos.rz = SMEE_MRAD_TO_SI(EC4T_search_focus__ws_pos_rz_qdsb->value());
    u_param.param_EC4T_search_focus.ws_pos.z = SMEE_MM_TO_SI(EC4T_search_focus__ws_pos_z_qdsb->value());
    u_param.param_EC4T_search_focus.ws_pos.rx = SMEE_MRAD_TO_SI(EC4T_search_focus__ws_pos_rx_qdsb->value());
    u_param.param_EC4T_search_focus.ws_pos.ry = SMEE_MRAD_TO_SI(EC4T_search_focus__ws_pos_ry_qdsb->value());
    u_param.param_EC4T_search_focus.z_search_range = SMEE_MM_TO_SI(EC4T_search_focus__z_search_range_qdsb->value());

    //执行函数
    error_code = EC4T_search_focus(
		u_param.param_EC4T_search_focus.align_type, 
		u_param.param_EC4T_search_focus.ePlateType,
		u_param.param_EC4T_search_focus.ws_pos, 
		u_param.param_EC4T_search_focus.z_search_range, 
		&u_param.param_EC4T_search_focus.focused_ws_pos_p,
		&u_param.param_EC4T_search_focus.focused_fls_z_p);

    //更新界面
    outputEnd(func_name,error_code);
}

void ECVTMaintenance::m_exec_EC4T_wa_align()
{
    int error_code = OK;

	QString func_name = "EC4T_wa_align";
	//输出信息到输出栏
	outputStart(func_name);
    //获取输入参数
    switch(EC4T_wa_align__align_type_qcb->currentIndex())
    {
    /*case 0:
    u_param.param_EC4T_wa_align.align_type = SMEE_ALIGN_NONE;
        break;
    case 1:
    u_param.param_EC4T_wa_align.align_type = SMEE_ALIGN_TTL;
        break;*/
    case 0:
    u_param.param_EC4T_wa_align.align_type = SMEE_ALIGN_OA;
        break;
    case 1:
    u_param.param_EC4T_wa_align.align_type = SMEE_ALIGN_WBA;
        break;
    case 2:
    u_param.param_EC4T_wa_align.align_type = SMEE_ALIGN_DT;
        break;
    default:
        //m_log(QString("EC4T_wa_align: Enum Parameter Error!"));
        break;
    }
    switch(EC4T_wa_align__wafer_size_qcb->currentIndex())
    {
    case 0:
    u_param.param_EC4T_wa_align.wafer_size = SMEE_WAFER_2_INCH;
        break;
    case 1:
    u_param.param_EC4T_wa_align.wafer_size = SMEE_WAFER_3_INCH;
        break;
    case 2:
    u_param.param_EC4T_wa_align.wafer_size = SMEE_WAFER_4_INCH;
        break;
    case 3:
    u_param.param_EC4T_wa_align.wafer_size = SMEE_WAFER_5_INCH;
        break;
    case 4:
    u_param.param_EC4T_wa_align.wafer_size = SMEE_WAFER_6_INCH;
        break;
    case 5:
    u_param.param_EC4T_wa_align.wafer_size = SMEE_WAFER_8_INCH;
        break;
    case 6:
    u_param.param_EC4T_wa_align.wafer_size = SMEE_WAFER_12_INCH;
        break;
    case 7:
    u_param.param_EC4T_wa_align.wafer_size = SMEE_WAFER_18_INCH;
        break;
    default:
        //m_log(QString("EC4T_wa_align: Enum Parameter Error!"));
        break;
    }
    u_param.param_EC4T_wa_align.mark_nominal_pos.x = SMEE_MM_TO_SI(EC4T_wa_align__mark_nominal_pos_x_qdsb->value());
    u_param.param_EC4T_wa_align.mark_nominal_pos.y = SMEE_MM_TO_SI(EC4T_wa_align__mark_nominal_pos_y_qdsb->value());
    u_param.param_EC4T_wa_align.oa_align_recipe.do_auto_focus = EC4T_wa_align__oa_align_recipe_do_auto_focus_qckb->isChecked();
    u_param.param_EC4T_wa_align.oa_align_recipe.perform_vert_compensation = EC4T_wa_align__oa_align_recipe_perform_vert_compensation_qckb->isChecked();
    u_param.param_EC4T_wa_align.oa_align_recipe.vert_compensation = SMEE_UM_TO_SI(EC4T_wa_align__oa_align_recipe_vert_compensation_qdsb->value());
    u_param.param_EC4T_wa_align.oa_align_recipe.matching_rate = EC4T_wa_align__oa_align_recipe_matching_rate_qdsb->value()/100;
    memcpy(u_param.param_EC4T_wa_align.oa_align_recipe.template_file,EC4T_wa_align__oa_align_recipe_template_file_qle->text().toAscii(),sizeof(SMEE_CHAR)*EC4A_MAX_FILE_NAME_SIZE);

    //执行函数
    error_code = EC4T_wa_align(
		u_param.param_EC4T_wa_align.align_type, 
		u_param.param_EC4T_wa_align.wafer_size, 
		u_param.param_EC4T_wa_align.mark_nominal_pos,
		u_param.param_EC4T_wa_align.oa_align_recipe,
		&u_param.param_EC4T_wa_align.align_result_p);

    //更新界面
    outputEnd(func_name,error_code);
}

void ECVTMaintenance::m_exec_EC4T_TTL_align()
{
    int error_code = OK;

	QString func_name = "EC4T_TTL_align";
	//输出信息到输出栏
	outputStart(func_name);
    //获取输入参数
    u_param.param_EC4T_TTL_align.mark_norminal_pos.x = SMEE_MM_TO_SI(EC4T_TTL_align__mark_norminal_pos_x_qdsb->value());
    u_param.param_EC4T_TTL_align.mark_norminal_pos.y = SMEE_MM_TO_SI(EC4T_TTL_align__mark_norminal_pos_y_qdsb->value());
    u_param.param_EC4T_TTL_align.ttl_align_recipe.search_enabled = EC4T_TTL_align__ttl_align_recipe_search_enabled_qckb->isChecked();
    u_param.param_EC4T_TTL_align.ttl_align_recipe.matching_rate = EC4T_TTL_align__ttl_align_recipe_matching_rate_qdsb->value()/100;
    memcpy(u_param.param_EC4T_TTL_align.ttl_align_recipe.template_file,EC4T_TTL_align__ttl_align_recipe_template_file_qle->text().toAscii(),sizeof(SMEE_CHAR)*EC4A_MAX_FILE_NAME_SIZE);

    //执行函数
    error_code = EC4T_TTL_align(
		u_param.param_EC4T_TTL_align.mark_norminal_pos, 
		u_param.param_EC4T_TTL_align.ttl_align_recipe, 
		&u_param.param_EC4T_TTL_align.align_result_p);

    //更新界面
    outputEnd(func_name,error_code);
}

void ECVTMaintenance::m_exec_EC4T_update_wa_baseline()
{
    int error_code = OK;

	QString func_name = "EC4T_update_wa_baseline";
	//输出信息到输出栏
	outputStart(func_name);
    //获取输入参数
    switch(EC4T_update_wa_baseline__align_type_qcb->currentIndex())
    {
    case 0:
    u_param.param_EC4T_update_wa_baseline.align_type = SMEE_ALIGN_OA;
        break;
    case 1:
    u_param.param_EC4T_update_wa_baseline.align_type = SMEE_ALIGN_WBA;
        break;
    case 2:
    u_param.param_EC4T_update_wa_baseline.align_type = SMEE_ALIGN_DT;
        break;
    case 3:
    u_param.param_EC4T_update_wa_baseline.align_type = SMEE_ALIGN_NONE;
        break;
    case 4:
    u_param.param_EC4T_update_wa_baseline.align_type = SMEE_ALIGN_TTL;
        break;
    default:
        //m_log(QString("EC4T_update_wa_baseline: Enum Parameter Error!"));
        break;
    }

    //执行函数
    error_code = EC4T_update_wa_baseline(
		u_param.param_EC4T_update_wa_baseline.align_type, 
		&u_param.param_EC4T_update_wa_baseline.oa_baseline_result_p);

    //更新界面
    outputEnd(func_name,error_code);
}

void ECVTMaintenance::m_exec_EC4T_update_ttl_baseline()
{
    int error_code = OK;

	QString func_name = "EC4T_update_ttl_baseline";
	//输出信息到输出栏
	outputStart(func_name);
    //获取输入参数

    //执行函数
    error_code = EC4T_update_ttl_baseline(&u_param.param_EC4T_update_ttl_baseline.ttl_baseline_result_p);

    //更新界面
    outputEnd(func_name,error_code);
}


//////////////////////////////////////////////////////////////////////////////
DoubleSpinBoxDelegate::DoubleSpinBoxDelegate(QObject *parent)
     : QItemDelegate(parent)
 {
	 m_spinBoxAgent = new SMEE::SpinBoxAgent("VTEC_Delegate",NULL);
 }

QWidget *DoubleSpinBoxDelegate::createEditor(QWidget *parent,
     const QStyleOptionViewItem & /*option */,
     const QModelIndex & index ) const
{	
	Q_UNUSED(index);

	SMEE::DoubleSpinBox *editor = new SMEE::DoubleSpinBox(parent);

	editor->setMinimumHeight( 0 );
    editor->setMinimumWidth( 0 );
    editor->setMaximumHeight( 1000 );
    editor->setMaximumWidth( 1000 );
	editor->setDecimals(6);
	editor->setSingleStep(0.000001);

	return editor;
 }

void DoubleSpinBoxDelegate::setEditorData(QWidget *editor,
                                     const QModelIndex &index) const
 {
	 double value = index.model()->data(index, Qt::DisplayRole).toDouble();

	 SMEE::DoubleSpinBox *spinBox = static_cast<SMEE::DoubleSpinBox*>(editor);
	 spinBox->setValue(value);

 }

void DoubleSpinBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                    const QModelIndex &index) const
 {
	 SMEE::DoubleSpinBox *spinBox = static_cast<SMEE::DoubleSpinBox*>(editor);
	 spinBox->interpretText();
	 double value = spinBox->value();

	 double minValue = m_spinBoxAgent->GetMinValue(spinBox);	
	 if(minValue > value)
	 {
		 //小于最小值
		value = minValue;	
	 }
	 else 
	 {
		 double maxValue = m_spinBoxAgent->GetMaxValue(spinBox);	
		 if(maxValue < value)
		 {
			value = maxValue;	
		 }
	 }
	 QString value1 = QString::number(value,'g',15);

	 model->setData(index, value1, Qt::EditRole);

 }

void DoubleSpinBoxDelegate::updateEditorGeometry(QWidget *editor,
     const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
 {
     editor->setGeometry(option.rect);
 }

 
 //////////////////////////////////////////////////////////////////////////////

 GlobalSubstrateDelegate::GlobalSubstrateDelegate(QObject *parent):QItemDelegate(parent)
{
   //m_spinBoxAgent = new SMEE::SpinBoxAgent("AEVT_Application",parent);
    //m_spinBoxAgent_1 = new SMEE::SpinBoxAgent("TW_Global_Substrate Delegate",NULL);
}

 //GlobalSubstrateDelegate::~GlobalSubstrateDelegate()
//{

	 /*if(NULL != get_both_mark_current_pos )
	{
	   delete get_both_mark_current_pos;
       get_both_mark_current_pos = NULL;
	}*/
//}

QWidget * GlobalSubstrateDelegate::createEditor(QWidget *parent, 
                                                      const QStyleOptionViewItem &/*option*/ ,
		                                              const QModelIndex &index) const
{
	Q_UNUSED(index);
	switch(index.column())
	{
		case 0:
		{
			SMEE::DoubleSpinBox* editor = new SMEE::DoubleSpinBox(parent);
			editor->setMinimumWidth( 120 );
            editor->setMaximumHeight( 120);
			editor->setRange(-999999,999999);
				editor->setDecimals(6); 
			//editor->setToolTip("[2e-32, 2e32]");
			return editor;
		}
		break;
		case 1:
		{
			SMEE::DoubleSpinBox* editor = new SMEE::DoubleSpinBox(parent);
			editor->setMinimumWidth( 120 );
            editor->setMaximumHeight( 120);
			editor->setRange(-999999,999999);
				editor->setDecimals(6); 
			//editor->setToolTip("[2e-32, 2e32]");
			return editor;
		}
		break;
		case 2:
		{
			SMEE::DoubleSpinBox* editor = new SMEE::DoubleSpinBox(parent);
			editor->setMinimumWidth( 120 );
            editor->setMaximumHeight( 120);
			editor->setRange(-999999,999999);
			editor->setDecimals(6); 
			//editor->setToolTip("[2e-32, 2e32]");
			return editor;
		}
		break;
		case 3:
		{
			SMEE::DoubleSpinBox* editor = new SMEE::DoubleSpinBox(parent);
			editor->setMinimumWidth( 120 );
            editor->setMaximumHeight( 120);
			editor->setRange(-999999,999999);
				editor->setDecimals(6); 
			//editor->setToolTip("[2e-32, 2e32]");
			return editor;
		}
		break;
		
		case 4:
		{
			SMEE::SpinBox* editor = new SMEE::SpinBox(parent);
			editor->setMinimumWidth( 120 );
            editor->setMaximumHeight( 120);
			editor->setRange(-999999,999999);
				//editor->setDecimals(0); 
			//editor->setToolTip("[2e-32, 2e32]");
			return editor;
		}
		break;
		
		
		default:
		return NULL;
		break;
	}

}

 void GlobalSubstrateDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const

 {
	 double value = 0;

	switch(index.column())
	{
		case 0:
		{
			value = index.model()->data(index, Qt::DisplayRole).toDouble();
			SMEE::DoubleSpinBox *spinBox = static_cast<SMEE::DoubleSpinBox*>(editor);
			spinBox->setValue(value);
			break;
		}
		
		case 1:
		{
			value = index.model()->data(index, Qt::DisplayRole).toDouble();
			SMEE::DoubleSpinBox *spinBox = static_cast<SMEE::DoubleSpinBox*>(editor);
			spinBox->setValue(value);
			break;
		}
	    case 2:
		{
			value = index.model()->data(index, Qt::DisplayRole).toDouble();
			SMEE::DoubleSpinBox *spinBox = static_cast<SMEE::DoubleSpinBox*>(editor);
			spinBox->setValue(value);
			break;
		}
		
		case 3:
		{
			value = index.model()->data(index, Qt::DisplayRole).toDouble();
			SMEE::DoubleSpinBox *spinBox = static_cast<SMEE::DoubleSpinBox*>(editor);
			spinBox->setValue(value);
			break;
		}
		
		case 4:
		{
			int value1 = 0;
			value1 = index.model()->data(index, Qt::DisplayRole).toInt();
			SMEE::SpinBox *spinBox = static_cast<SMEE::SpinBox*>(editor);
			spinBox->setValue(value1);
			break;
		}
		
		default:
		break;

	}     
	  
 }


 void GlobalSubstrateDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
		const QModelIndex &index) const
 {
	 switch(index.column())
	{
	case 0:
		{
			SMEE::DoubleSpinBox *spinBox = static_cast<SMEE::DoubleSpinBox*>(editor);
			spinBox->interpretText();
			QString value = QString::number(spinBox->value(),'f',6);//15是精确度

			
			model->setData(index, value, Qt::EditRole);
			break;
		}
	case 1:
		{
			SMEE::DoubleSpinBox *spinBox = static_cast<SMEE::DoubleSpinBox*>(editor);
			spinBox->interpretText();
			QString value = QString::number(spinBox->value(),'f',6);//15是精确度

			
			model->setData(index, value, Qt::EditRole);
			break;
		}
	case 2:
		{
			SMEE::DoubleSpinBox *spinBox = static_cast<SMEE::DoubleSpinBox*>(editor);
			spinBox->interpretText();
			QString value = QString::number(spinBox->value(),'f',6);//15是精确度

			
			model->setData(index, value, Qt::EditRole);
			break;
		} 
		
		case 3:
		{
			SMEE::DoubleSpinBox *spinBox = static_cast<SMEE::DoubleSpinBox*>(editor);
			spinBox->interpretText();
			QString value = QString::number(spinBox->value(),'f',6);//15是精确度

			
			model->setData(index, value, Qt::EditRole);
			break;
		}
		
		case 4:
		{   
		    
			SMEE::SpinBox *spinBox = static_cast<SMEE::SpinBox*>(editor);
			spinBox->interpretText();
			QString value = QString::number(spinBox->value());

			
			model->setData(index, value, Qt::EditRole);
			break;
		}
		
		
	default:
		break;

	} 
	  
 }

 void GlobalSubstrateDelegate::updateEditorGeometry(QWidget *editor,
		const QStyleOptionViewItem &option, const QModelIndex &) const
 {
      editor->setGeometry(option.rect);
 
 }
 