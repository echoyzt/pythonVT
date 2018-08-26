/******************************************************************************
* Copyright (C) 2014, �Ϻ�΢����װ�����޹�˾
* All rights reserved.
* ��Ʒ�� : SSB 530/10
* ������� : EC
* ģ������ : EC4T
* �ļ����� : EC4T_tc.h
* ��Ҫ���� : EC����ⲿ�ӿ����ݶ���
* ��ʷ��¼ : 
* �汾   ����        ����     ����
* 1.0    2014-08-18  ������   �½���
******************************************************************************/

#ifndef EC4T_TC_H
#define EC4T_TC_H


///////////////////////////////////////////////////////////////////////////////
//                                ͷ�ļ�����
///////////////////////////////////////////////////////////////////////////////

#include <smee.h>
#include <smee_project.h>


///////////////////////////////////////////////////////////////////////////////
//                                  �궨��
///////////////////////////////////////////////////////////////////////////////

/* �������׼��Ǹ��� */
#define EC4T_MAX_NR_SUBSTRATE_MARKS     50
#define EC4A_MAPPING_SCAN_NUM               40

///////////////////////////////////////////////////////////////////////////////
//                                 ö�ٶ���
///////////////////////////////////////////////////////////////////////////////

/* ���λ�� */
typedef enum
{
    EC4T_MARK_LOCATION_MIN = 0,
    EC4T_MARK_LOCATION_WS_FIDUCIAL, /* ����̨��׼���� */
    EC4T_MARK_LOCATION_SUBSTRATE,   /* ������ */
    EC4T_MARK_LOCATION_MAX
} EC4T_MARK_LOCATION_ENUM;


///////////////////////////////////////////////////////////////////////////////
//                               ���ݽṹ����
///////////////////////////////////////////////////////////////////////////////
typedef struct  
{
	xy_vect      RM1_pos; /*���λ��*/
	xy_vect      RM2_pos;
	SMEE_DOUBLE matching_rate;
	SMEE_CHAR template_file[EC4A_MAX_FILE_NAME_SIZE];     /* ��ģ���ģ���ļ��� */
}EC4T_RETI_ALIGN_SPC_STRUCT;

typedef struct
{
    SMEE_BOOL do_auto_focus;                            /* �Ƿ����Զ����� */
    SMEE_BOOL perform_vert_compensation;             /* ��׼�������� */
    SMEE_DOUBLE vert_compensation;                   /* ��׼���򲹳��� */
    SMEE_DOUBLE matching_rate;                            /* ���ʶ��ƥ��� */
	SMEE_CHAR template_file[EC4A_MAX_FILE_NAME_SIZE];     /* ���ģ���ļ��� */
} EC4T_WA_ALIGN_RECIPE_STRUCT;



/* ����������ߵĽ�� */
typedef struct
{
    xy_vect aim_pos;    /* ��Ƭ��׼CCDĿ��λ�� */
    SMEE_DOUBLE matching_rate;
} EC4T_UPDATE_WA_BASELINE_RESULT_STRUCT;


/* ����ͬ����ߵĽ�� */
typedef struct
{
    SMEE_DOUBLE matching_rate_in_ccd; /* ͬ���׼�����CCD�е�ƥ��� */
    xy_vect mark_pos_in_ccd;     /* ͬ���׼�����CCD�е�����λ�� */
} EC4T_UPDATE_TTL_BASELINE_RESULT_STRUCT;


/* �����׼��� */
typedef struct
{
    xy_vect mark_pos_in_ccd;        /* �����CCD�е�����λ�� */
    xy_vect mark_pos_in_wzcs;       /* �����WZCS�µ�λ�� */
    SMEE_DOUBLE match_rate;         /* ���ƥ��� */
    xyrz_vect align_pos;            /* ��Ƕ�׼λ�� */
    xyrz_vect ws_meas_pos;          /* ����̨����λ�� */
    xy_vect mark_offset_in_wscs;    /* ���λ��ƫ��(WSCS) */
} EC4T_WA_ALIGN_RESULT_STRUCT;

/* ͬ����ʶ�𴦷� */
typedef struct
{
    SMEE_BOOL search_enabled;   /* �Ƿ�ִ������ */
    SMEE_INT32 filler1;
    SMEE_DOUBLE matching_rate;  /* ���ʶ��ƥ��� */
	SMEE_CHAR template_file[EC4A_MAX_FILE_NAME_SIZE];	  /* ���ģ���ļ��� */
} EC4T_ALIGN_RECIPE_STRUCT;

/* ͬ���׼��� */
typedef struct
{
    xy_vect mark_pos_in_ccd;        /* �����CCD�е�����λ�� */
    xy_vect mark_pos_in_wzcs;       /* �����WZCS�µ�λ�� */
    SMEE_DOUBLE match_rate;         /* ���ƥ��� */
    xyrz_vect align_pos;            /* ��׼λ�� */
    xyrz_vect rs_meas_pos;          /* ��ģ̨����λ�� */
    xyrz_vect ws_meas_pos;          /* ����̨����λ�� */
    xy_vect mark_offset_in_rzcs;    /* ���λ��ƫ��(RZCS) */
    xy_vect mark_offset_in_wscs;    /* ���λ��ƫ��(WSCS) */
} EC4T_TTL_ALIGN_RESULT_STRUCT;

typedef struct
{
    xy_vect sStartPos;
    xy_vect sEndPos;
    SMEE_UINT32 uiSpotValid;
    SMEE_INT32 ifiller;
}EC4T_SCAN_PARAM_STRUCT;

typedef struct
{
    SMEE_INT32 iScanNum;
    EC4T_SCAN_PARAM_STRUCT sScanRoute[EC4A_MAPPING_SCAN_NUM];
}EC4T_MAPPING_ROUTE_STRUCT;

#endif /* EC4T_TC_H */

