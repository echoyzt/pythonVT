/******************************************************************************
* Copyright (C) 2014, �Ϻ�΢����װ�����޹�˾
* All rights reserved.
* ��Ʒ�� : SSB 530/10
* ������� : EC
* ģ������ : EC4A
* �ļ����� : EC4A_tc.h
* ��Ҫ���� : EC����ⲿ�ӿ����ݶ���
* ��ʷ��¼ :
* �汾   ����        ����     ����
* 1.0    2014-08-18  ������   �½���
******************************************************************************/

#ifndef EC4A_TC_H
#define EC4A_TC_H


///////////////////////////////////////////////////////////////////////////////
//                                ͷ�ļ�����
///////////////////////////////////////////////////////////////////////////////

#include <ADAE.h>
#include <smee.h>
#include <smee_project.h>


///////////////////////////////////////////////////////////////////////////////
//                                �����붨��
///////////////////////////////////////////////////////////////////////////////

/* <ErrBegin> */

/* EC���̳����쳣���� */
#define  EC4A_SYSTEM_ERROR          0x45430100

/* �������� */
#define  EC4A_PARAMETER_ERROR       0x45430101

/* �Ƿ����ô��� */
#define  EC4A_ILLEGAL_CALL_ERROR    0x45430102

/* ���Դ��� */
#define  EC4A_RETRY_ERROR    0x45430103


/* <ErrEnd> */


///////////////////////////////////////////////////////////////////////////////
//                                  �궨��
///////////////////////////////////////////////////////////////////////////////

/* ͼ�� ID ���Ƶ������ */
#define EC4A_IMAGE_ID_LEN           MAX_IMAGE_ID

/* һ��lot������ͼ����� */
#define EC4A_MAX_IMAGES_NR          MAX_IMG_NR_PER_LOT

/* �عⳡ������ */
#define EC4A_MAX_EXPOSURES_NR       MAX_FLD_NR_PER_IMG

/* ��ģ ID ���� */
#define EC4A_MAX_RETICLE_ID         MAX_RETICLE_ID

/* �����·���ļ����������ƣ�������β��'\0' */
#define EC4A_MAX_FILE_NAME_SIZE     0x80

/* ����ȫ����׼�����������Ҫ�� AL ͬ�� */
#define EC4A_MAX_ALIGN_MARK         MAX_WAFER_MARK_NUM

/* ���������� */
#define EC4A_MAX_NR_ZONES           9

/* ÿ����������Ǹ��� */
#define EC4A_MAX_MARK_NR_PER_ZONE     12

/*ÿ����������عⳡ����*/
#define EC4A_MAX_EXPOSURE_NR_PER_ZONE     12

/* դ�����ʽϵ������ */
#define EC4A_NR_GRID_COEFS          10

/* EC��Ϣ����,������β��'\0 */
#define EC4A_MAX_MSG_SIZE  0x200

#define EC4A_RETICLE_MARKS_NUM 2

#define EC4A_MAX_UPDATE_BASELINE_NUM 3

///////////////////////////////////////////////////////////////////////////////
//                                 ö�ٶ���
///////////////////////////////////////////////////////////////////////////////


/* ��ƽģʽö�� */
typedef enum
{
    EC4A_LEVEL_MODE_MIN = 0,
    EC4A_LEVEL_MODE_GLOBAL,            /* ȫ��������ƽ */
    EC4A_LEVEL_MODE_GLOBAL_FLS,        /* ȫ�������𳡵�ƽ */
    EC4A_LEVEL_MODE_FLS,               /* �𳡵�����ƽ */
    EC4A_LEVEL_MODE_MAPPING,           /* Mapping */
    EC4A_LEVEL_MODE_SIMPLE_MAPPING,    /* Simple Mapping */
    EC4A_LEVEL_MODE_MAX
} EC4A_LEVEL_MODE_ENUM;


/* ·���滮���� */
typedef enum
{
    EC4A_CALC_ROUTE_OPT_MIN = 0,
    EC4A_CALC_ROUTE_OPT_CUSTOM,     /* �û�ָ�� */
    EC4A_CALC_ROUTE_OPT_STANDARD,   /* ��׼·�� */
    EC4A_CALC_ROUTE_OPT_OPTIMIZE,   /* �Ż�·�� */
    EC4A_CALC_ROUTE_OPT_MAX
} EC4A_CALC_ROUTE_OPT_ENUM;


/* ����ȫ������׼Ҫ�� */
typedef enum
{
    EC4A_FIWA_REQ_MIN = 0,
    EC4A_FIWA_REQ_PRECISION_PREFERED,   /* �������ȣ����б�Ƕ�׼�ɹ� */
    EC4A_FIWA_REQ_ROBUST_PREFERED,      /* �ݴ����ȣ�3�������ϱ��ʶ��ɹ� */
    EC4A_FIWA_REQ_BALANCED,             /* ���߼�ˣ���Ǹ���/2����3�����ϱ��ʶ��ɹ���ȡ���ߵ����ֵ */
	EC4A_FIWA_REQ_USER_DEFINE, 			/* �û��Զ���*/
	EC4A_FIWA_REQ_MAX
} EC4A_FINE_SUBSTRATE_ALIGN_REQ_ENUM;


/* ������׼���� */
typedef enum
{
    EC4A_WA_METHOD_MIN = 0,
    EC4A_WA_METHOD_GLOBAL,           /* ȫ����׼ */
    EC4A_WA_METHOD_HYBRID,           /* ��϶�׼ */
    EC4A_WA_METHOD_MAX
} EC4A_WA_METHOD_ENUM;

/*  ��Ƕ�׼�׶�ö��     */
typedef enum
{
    EC4A_ALIGNMENT_PHASE_MIN = 0, /* ö����Сֵ */
    EC4A_COARSE_AND_FINE_PHASE,   /* �ֶ�׼�;���׼�׶� */
    EC4A_COARSE_PHASE,            /* �ֶ�׼�׶� */
    EC4A_FINE_PHASE,              /* ����׼�׶� */
    EC4A_ALIGNMENT_PHASE_MAX      /* ö�����ֵ */
} EC4A_ALIGNMENT_PHASE_ENUM;

typedef enum
{
    EC4A_AFBT_MIN = 0,
    EC4A_AFBT_ABORT_LOT, // ֱ����ֹ������
	EC4A_AFBT_REJECT_WAFER,// ��Ƭ����Ƭ����
    EC4A_AFBT_MANUAL_ALIGN,//�ֶ���׼
    EC4A_AFBT_RETRY,//����
    EC4A_AFBT_MAX
}EC4A_ALIGN_FAILE_LOT_TREAT_ENUM;// ��׼ʧ�ܺ����������

/* EC�ڲ�״̬ö�� */
typedef enum
{
    EC4A_ST_STATUS_MIN = 0,
    EC4A_ST_STATUS_IDLE,            /* ���� */
    EC4A_ST_STATUS_TERMINATE,       /* ��ֹ */
    EC4A_ST_STATUS_START_LOT,       /* ��ʼ�� */
    EC4A_ST_STATUS_START_SUBSTRATE, /* ��ʼ���� */
    EC4A_ST_STATUS_MAX
} EC4A_ST_STATUS_ENUM;


/* �����׼CCD */
typedef enum
{
    EC4A_OA_CCD_MIN = 0,
    EC4A_OA_CCD_FRONT,      /* �����׼����CCD */
    EC4A_OA_CCD_BACK,       /* �����׼����CCD */
    EC4A_OA_CCD_MAX
} EC4A_OA_CCD_ENUM;


typedef enum
{
    EC4A_FIELD_STATE_MIN = 0,
    EC4A_FIELD_NONE,   // δ����
    EC4A_FIELD_EXPOSED,// �ع�ɹ�
    EC4A_FIELD_FAILED, // �ع�ʧ��
    EC4A_FIELD_STATE_MAX
}EC4A_FIELD_STATE_ENUM;// �عⳡ״̬��Ϣ

typedef enum
{
    EC4A_IMAGE_STATE_MIN = 0,
    EC4A_IMAGE_NONE,   // ͼ��δ�����ع����
    EC4A_IMAGE_FULL,   // ͼ����ȫ�ع�
    EC4A_IMAGE_FAILED, // ͼ���ع�ʧ��
    EC4A_IMAGE_STATE_MAX
}EC4A_IMAGE_STATE_ENUM;// ��Ƭ�ع�״̬��Ϣ

//�˲�Ƭ����ģʽenum
typedef enum
{
    EC4A_FILTER_MODE_MIN = 0,
    EC4A_FILTER_MODE_GHI,    //Ĭ�Ϲ���ģʽGHI����
    EC4A_FILTER_MODE_GH,     //GH�߹���ģʽ
    EC4A_FILTER_MODE_I,      //I�߹���ģʽ
    EC4A_FILTER_MODE_MAX
}EC4A_FILTER_MODE_ENUM;

typedef enum
{
    EC4A_DOSE_CONTROL_MODE_MIN = 0,
    EC4A_DOSE_CONTROL_BY_TIME,  // ʱ����� by time
    EC4A_DOSE_CONTROL_BY_ENERGY,// �������� by energy
    EC4A_DOSE_CONTROL_MODE_MAX
}EC4A_DOSE_CONTROL_MODE_ENUM;// �ع��������ģʽ

typedef enum
{
    EC4A_FINE_WAFER_ALIGN_MODE_MIN = 0,
    EC4A_FINE_BASIC_MODE,  // ����ģʽ (basic mode)
    EC4A_FINE_ENHANCE_MODE,// ��ǿģʽ (enhance mode)
    EC4A_FINE_WAFER_ALIGN_MODE_MAX
}EC4A_FINE_WAFER_ALIGN_MODE_ENUM; // ��Ƭȫ������׼��ʽ fine wafer alignment

typedef enum
{
    EC4A_MARK_PREF_MIN = 0,
    EC4A_MARK_PREF_PREFERED,            /* ��ѡ��� */
    EC4A_MARK_PREF_BACKUP,              /* ���ñ�� */
    EC4A_MARK_PREF_MAX
} EC4A_MARK_PREF_ENUM;

typedef enum
{
    EC4A_CHCK_WS_CHUCK_PARTICLE_MIN = 0,
    EC4A_NO_CHECK,            /* �����п����ȼ��*/
    EC4A_CHECK,              /* ��⣬���ǲ�һ���������� */
	EC4A_FORCE_CHECK,        /* ��⣬���ұ��뵯������ */
    EC4A_CHCK_WS_CHUCK_PARTICLE_MAX
} EC4A_CHECK_WS_CHUCK_PARTICLE_ENUM;

///////////////////////////////////////////////////////////////////////////////
//                                �ṹ�嶨��
///////////////////////////////////////////////////////////////////////////////

/* EC�ڲ�״̬�ṹ�� */
typedef struct
{
    EC4A_ST_STATUS_ENUM status;  /* EC�ڲ�״̬ */
    SMEE_INT32 filler1;
} EC4A_STATUS_STRUCT;


/* ��Ƭ���ʶ�𴦷� */
typedef struct
{
    SMEE_BOOL do_auto_focus;                            /* �Ƿ����Զ����� */
    SMEE_BOOL perform_vert_compensation;             /* ��׼�������� */
    SMEE_DOUBLE vert_compensation;                   /* ��׼���򲹳��� */
	SMEE_BOOL specify_algorithm;						/* �Ƿ�ָ����׼�㷨 */
	SMEE_ALGORITHM_TYPE_ENUM algorithm_type;			 /* �㷨���� */
	SMEE_BOOL use_align_alg_param;						/* �Ƿ�ʹ���û��Զ�����㷨�߼����� */
    SMEE_INT32 filler;
	SMEE_CHAR align_alg_param_file_name[SMEE_MAX_FILE_NAME_SIZE]; /* �㷨�߼������ļ���������·��������չ���� */
    SMEE_DOUBLE matching_rate;                            /* ���ʶ��ƥ��� */
	SMEE_CHAR template_file[EC4A_MAX_FILE_NAME_SIZE];     /* ���ģ���ļ��� */
} EC4A_ALIGN_RECIPE_STRUCT;


typedef struct
{
    SMEE_INT32 mark_id;     /* ��Ǳ�ʶ */
    SMEE_INT32 zone_id;     /* �����ʶ */
	EC4A_ALIGNMENT_PHASE_ENUM   mark_align_usage; /*��Ƕ�׼�׶�*/
    EC4A_MARK_PREF_ENUM preference;/*�����������*/
    xy_vect mark_position;  /* ���λ�� */
} EC4A_SUBSTRATE_MARK_DATA_STRUCT;

/*��ģ�������*/
typedef struct  
{
	xy_vect RM1;//��ģ���1  
	xy_vect RM2;//��ģ���2
}EC4A_RETICLE_MARK_DATA_STRUCT; 

/* Interfield Correction ���� */
typedef struct
{
    xy_vect translation;         /* ƽ�����У��ֵ */
    SMEE_DOUBLE rotation;        /* ��ת�Ƕ����У��ֵ */
    SMEE_DOUBLE magnification;   /* �Ŵ�����У��ֵ */
    SMEE_DOUBLE asy_rotation;    /* �ǶԳ���ת�Ƕ����У��ֵ */
    SMEE_DOUBLE asy_magn;        /* �ǶԳƷŴ������У��ֵ */
} EC4A_INTERFIELD_CORR_STRUCT;


/* ������׼���� */
typedef struct
{
	SMEE_ALIGN_TYPE_ENUM  WA_CCD_type;				/* ��׼ʹ�õ�CCD*/
	EC4A_OA_CCD_ENUM OA_CCD;						/*��׼����-���� ����*/
	SMEE_BOOL is_matching_overlay;                      /* �Ƿ���ƥ���׿� */    
	SMEE_INT32 nr_of_valid_fWA_marks;		/*�û�ָ���ľ���׼�����Ч����*/
	EC4A_ALIGN_FAILE_LOT_TREAT_ENUM  align_fail_lot_treat;/* ��׼ʧ�ܴ���*/
	SMEE_BOOL is_force_mark_training;                   /* �Ƿ�ǿ�Ʊ��ģ��ѧϰ */
	SMEE_BOOL is_do_manual_align;                       /* �Ƿ�ִ���ֶ���׼ */
	EC4A_FINE_SUBSTRATE_ALIGN_REQ_ENUM fWA_requirement;                 /* ����ȫ������׼Ҫ�� */
	SMEE_INT32 nr_wafer_marks;                          /* ������׼��Ǹ��� */
    SMEE_BOOL perform_precise_wafer_alignment;   // �Ƿ�߾��ȹ�Ƭ��׼    
    EC4A_FINE_WAFER_ALIGN_MODE_ENUM fine_wafer_alignment;//��Ƭȫ������׼��ʽ fine wafer alignment
    SMEE_BOOL adjust_mvs_brightness;                       /* �Ƿ������׼CCD��ѹ */
    SMEE_DOUBLE mvs_brightness;                            /* ��׼CCD��ѹ */
	EC4A_SUBSTRATE_MARK_DATA_STRUCT wafer_marks[MAX_WAFER_MARK_NUM]; /* ������׼��� */
	EC4A_ALIGN_RECIPE_STRUCT coarse_mark_recipe;  /* �ֶ�׼���ʶ�𴦷� */	
	EC4A_ALIGN_RECIPE_STRUCT fine_mark_recipe;  /* ����׼���ʶ�𴦷� */	
	EC4A_INTERFIELD_CORR_STRUCT layer_correction;            /* ������������� */
} EC4A_ALIGN_STRATEGY_STRUCT;

typedef struct
{
    SMEE_BOOL filter_enable;            //�˲���ʹ��
	SMEE_BOOL ina_enable;               //������ֵ�׾�ʹ��
	SMEE_BOOL pna_enable;               //�ﾵNA ʹ��
    EC4A_FILTER_MODE_ENUM filter_mode;  //�˲���ʹ��ģʽ
    SMEE_DOUBLE ina_value;              //������ֵ�׾���ֵ
    SMEE_DOUBLE pna_value;              //�ﾵNA ֵ
}EC4A_ILLUMINATION_MODE_STRUCT;


/* �ع����� */
typedef struct
{
    SMEE_INT32 exposure_id;     /* �عⳡ��� */
    SMEE_INT32 zone_id;         /* ����ID��������HA��׼ */
    SMEE_DOUBLE dose;           /* �ع���� */
    zrxry_vect focus_offset;    /* ���뽹��λ�� */
    xy_vect field_position;           /* ���ڹ����ϵ�λ�� */
} EC4A_EXPOSURE_DATA_STRUCT;

typedef struct  
{
    SMEE_INT32   nr_of_marks; /*��Ǹ���*/
    SMEE_INT32   filler;
    SMEE_UINT32   mark_id[EC4A_MAX_ALIGN_MARK]; /*�������*/
}EC4A_MARK_INDEX_STRUCT;

typedef struct
{
    SMEE_INT32 zone_id;     /* �����ʶ���� Index ��ͬ�� */
	SMEE_INT32 filler;
    xy_vect zone_center;            /* ����λ�ã����ĵ����꣩ */
    xy_vect zone_size;           /* ����ߴ� */
    EC4A_MARK_INDEX_STRUCT zone_marks;
} EC4A_ZONE_ALIGN_STRUCT;


/* ͼ������ */
typedef struct
{
    SMEE_CHAR image_id[EC4A_IMAGE_ID_LEN];                  /* Image ID */
    
    /* (����0-9����д��ĸA-Z,�Լ�7�������ַ�% + / $ .-�Լ��ո񣬳��ȡ�12-64�� λ���������� ) */
    SMEE_CHAR reticle_id[EC4A_MAX_RETICLE_ID];              /* Reticle ID ( ��ģ���ʶ ) */
    xy_vect image_center;                                   /* ͼ����������ģ�ϵ�λ�� */
    xy_vect image_size;                                     /* ͼ���С (wafer level) */
    xy_vect image_shift;                                    /* ͼ��ƽ�� */
    SMEE_BOOL specify_mask_win;             /* �Ƿ����û�ָ�� Mask Window */
    SMEE_INT32 filler;
    xy_vect win_size;                                       /* VS���ڴ�С */
    xy_vect win_center;                                     /* VS�������� */
    SMEE_DOUBLE reticle_trans_factor;                       /* ��ģ͸���� */
    xyrz_vect reticle_pre_align_offset;                     /*��ģ��Ƭƫ��*/
	EC4A_RETICLE_MARK_DATA_STRUCT reticle_marks;				/*��ģ���λ��*/
    EC4A_CALC_ROUTE_OPT_ENUM calc_option;                   /* ·���滮��ʽ */
    EC4A_DOSE_CONTROL_MODE_ENUM dose_mode;					/*��������ģʽ*/
    SMEE_UINT32 nr_zones;                               /* ������� */
    SMEE_INT32 nr_of_exposures;                             /* �عⳡ�� */
    EC4A_ZONE_ALIGN_STRUCT zones[EC4A_MAX_NR_ZONES];          /* �������� */
    EC4A_EXPOSURE_DATA_STRUCT exposure[EC4A_MAX_EXPOSURES_NR];   /* �������عⳡ����ϸ���� */
} EC4A_IMAGE_DATA_STRUCT;


/* EC��lot���� */
typedef struct
{
    SMEE_INT32 lot_id;                      /* lot��id */
    SMEE_BOOL alignment_optimize;          /* ��׼�Ż� */
    SMEE_BOOL global_level_optimize;       /* ȫ�ֵ�ƽ�Ż� */
	EC4A_CHECK_WS_CHUCK_PARTICLE_ENUM check_WS_chuck_particle;		/*����̨�����ȼ�����*/
	SMEE_DOUBLE global_lvl_base_angle;
	EC4A_ILLUMINATION_MODE_STRUCT ill_mode;		/*��������ģʽ*/
    SMEE_DOUBLE substrate_reflect_factor;   /* ���������� */
    xyrz_vect substrate_load_offset;                /*������Ƭƫ��*/
    SMEE_DOUBLE focus_edge_clearance;       /* <default>0.0<unit>m<range>[-0.19,0.19]<description>������Ե����� */
    SMEE_DOUBLE substrate_thickness;        /* <default>0.0<unit>m<range>[-0.000575,0.001225]<description>������Ȳ����� */
    SMEE_DOUBLE glc_UserFocusOffset;        /* ȫ�ֵ�ƽ�û��뽹�� */
    SMEE_BOOL perform_exposure;             /* �Ƿ�ִ��ʵ���ع⣬TRUE���ع��ϵͳ������ (ECUI���޸�,Ĭ��TRUE) */
	EC4A_WA_METHOD_ENUM substrate_align_method; 			/* ��׼ģʽ */
    SMEE_SUBSTRATE_SIZE_ENUM substrate_size;    /* <default>1<unit><range><description>Ƭ���� */
	SMEE_BOOL is_CGC;									/*�Ƿ�ʹ��CGCģ��*/
    SMEE_CHAR CGC_model[SMEE_MAX_FILE_NAME_SIZE];
    EC4A_ALIGN_STRATEGY_STRUCT strategy;       /* ��׼���� */
    SMEE_DOUBLE wafer_TPV;  /*��Ƭ����PV��ֵ*/
	SMEE_DOUBLE wafer_LPV;    /*��Ƭ����sigma��ֵ*/
    EC4A_LEVEL_MODE_ENUM level_mode;                      /* �عⳡ�ĵ�ƽ��ʽ */
    SMEE_INT32 nr_of_images;                /* ����ͼ����� */
    EC4A_IMAGE_DATA_STRUCT image[EC4A_MAX_IMAGES_NR];   /* ÿ��image�Ĳ��� */	
} EC4A_LOT_DATA_STRUCT;

typedef struct
{
    xy_vect mark_pos; //���λ��
    xyrzzrxry_vect exp_pos;//��Ƕ�׼����λ��
    SMEE_BOOL align_valid;//��׼����Ƿ���Ч
    SMEE_BOOL is_searched;//��׼�������Ƿ�ʹ��������
    xyrz_vect measure_pos;  //����̨�Ĳ���λ��
    xy_vect wafer_aim_pos;// ��Ƭ���Ŀ��λ��
    xy_vect  mark_pos_in_CCD; //�����CCD�е�λ��
    xy_vect align_dev;//��׼ƫ��
    SMEE_DOUBLE match_rate;//���ƥ����
}EC4A_MARK_MEASURE_RESULT_STRUCT;


typedef struct
{
    SMEE_INT32 nr_of_marks;
    SMEE_BOOL result_valid;
    EC4A_MARK_MEASURE_RESULT_STRUCT mark_data[EC4A_MAX_ALIGN_MARK];
}EC4A_MARK_CLUSTER_MEASURE_RESULT_STRUCT;

/* ��������ģ��׼����*/
typedef struct
{    
    SMEE_BOOL pos_valid; /* �������Ƿ�Ϊ��Ч��׼*/     
    SMEE_INT32 filler;
    xy_vect mark_pos; /* ��������׼��������λ�� ��λ��m*/    
    xyrz_vect RS_exp_pos;/* ��������ģ̨����λ�� ��λ����*/  
    xyrz_vect WS_exp_pos;/* ����������̨����λ�� ��λ����*/  
    xy_vect mark_in_CCD;/* ��������׼���Ŀ��λ�� ��λ��m/rad*/    
    xy_vect align_dev_in_WZCS;/* ��������WZCS�µĶ�׼ƫ�� ��λ��m*/   
    SMEE_DOUBLE match_rate; /* ������ ���ƥ��ȣ� ��λ����*/
}EC4A_RET_DATA_STRUCT;


typedef struct
{
    EC4A_RET_DATA_STRUCT  reti_coarse_align_data[EC4A_RETICLE_MARKS_NUM];/* ��������ģ�ֶ�׼���� */
    EC4A_RET_DATA_STRUCT  reti_fine_align_data[EC4A_RETICLE_MARKS_NUM];/* ��������ģ����׼���� */
}EC4A_RETICLE_MEASURE_DATA_STRUCT;


typedef struct
{
    EC4A_MARK_CLUSTER_MEASURE_RESULT_STRUCT coarse_align_data;
    EC4A_MARK_CLUSTER_MEASURE_RESULT_STRUCT fine_align_data;
}EC4A_SUBSTRATE_ALIGN_MEASURE_RESULT_STRUCT;


typedef struct
{
    SMEE_INT32 substrate_index;
    SMEE_BOOL is_mapping;	
    SMEE_BOOL glc_result_validate; /* ȫ�ֵ�ƽ�����Ч */
	SMEE_BOOL mapping_validate;  /*mapping�Ƿ���Ч �������Ч��LO����Ƭ����*/
    ADAE_timestamp level_point_stable;  // ��һ��ȫ�ֵ�ƽ��ˮƽ���ȶ���Ӧ��ϵͳʱ��
    ADAE_timestamp global_level_end;    // ȫ�ֵ�ƽ����ϵͳʱ��
    ADAE_timestamp mapping_start;
    ADAE_timestamp mapping_end;
    zrxry_vect global_level_result; // ȫ�ֵ�ƽ���    
    SMEE_DOUBLE current_TPV;   /*��Ƭ����PVֵ*/
    SMEE_DOUBLE current_LPV;   /*��Ƭ����sigmaֵ*/
	SMEE_BOOL find_bad_area; /*�Ƿ���ڻ�����*/
    SMEE_BOOL valid_wafer;   /*�Ƿ����Ƭ��*/
}EC4A_SUBSTRATE_LOG_STRUCT; // lot�����Ƭ��ز���

/* ��ģ�ֶ�׼��� */
typedef struct
{
    xy_vect rcs_to_rscs_trans;      /* ��ģ�������ģ̨ƽ�� */
    SMEE_DOUBLE rcs_to_rscs_rot;    /* ��ģ�������ģ̨��ת */
    SMEE_DOUBLE rcs_to_rscs_mag;    /* ��ģ�������ģ̨���� */
} EC4A_COARSE_RETICLE_ALIGN_RESULT_STRUCT;

/* ��ģ����׼��� */
typedef struct
{
    xy_vect rcs_to_wzcs_trans;      /* ��ģ����ڹ���̨��λƽ�� */
    SMEE_DOUBLE rcs_to_wzcs_rot;    /* ��ģ����ڹ���̨��λ��ת */
    SMEE_DOUBLE rcs_to_wzcs_mag;    /* ��ģ����ڹ���̨��λ���� */
} EC4A_FINE_RETICLE_ALIGN_RESULT_STRUCT;

/* ����(���������)��׼��� */
typedef struct  
{
    xy_vect wcs_to_wscs_trans;                      /* ��������ϵ����ڹ���̨����ϵƽ�� */
    SMEE_DOUBLE wcs_to_wscs_rot;                    /* ��������ϵ����ڹ���̨����ϵ��ת */
    SMEE_DOUBLE wcs_to_wscs_othro;                  /* ��������ϵ����ڹ���̨����ϵ������ */
    SMEE_DOUBLE wcs_to_wscs_mag_x;                  /* ��������ϵ����ڹ���̨����ϵ X ������ */
    SMEE_DOUBLE wcs_to_wscs_mag_y;                  /* ��������ϵ����ڹ���̨����ϵ Y ������ */
    SMEE_DOUBLE grid_coef_x[EC4A_NR_GRID_COEFS];    /* X ��դ��ϵ�� */
    SMEE_DOUBLE grid_coef_y[EC4A_NR_GRID_COEFS];    /* Y ��դ��ϵ�� */
} EC4A_ALIGN_MODEL_RESULT_STRUCT;


/* �����׼��� */
typedef struct
{
    SMEE_INT32 nr_zones;            /* ������� */
    SMEE_INT32 filler;
    EC4A_ALIGN_MODEL_RESULT_STRUCT zone_align_results[EC4A_MAX_NR_ZONES];   /* �����׼��� */
} EC4A_ZONE_ALIGN_RESULT_STRUCT;

/* ��������׼�� ��Ƕ�׼����*/
typedef struct
{   
    SMEE_ALIGN_TYPE_ENUM align_type; /* ������ ��׼����*/  
    xy_vect FM_pos;      /* ��������׼��������λ�� ��λ��m*/   
    xy_vect ref_pos; /* �������ο�λ�� ��λ��m*/  
    xyrz_vect rs_exp_pos;/* ������ ��ģ̨����λ�� ��λ����*/  
    xyrzzrxry_vect ws_exp_pos;  /* ������ ����̨����λ�� ��λ����*/   
    xy_vect aim_pos; /* ��������׼���Ŀ��λ�� ��λ��m/rad*/   
    SMEE_DOUBLE match_rate; /* ������ ���ƥ��ȣ� ��λ����*/
}EC4A_FM_DATA_STRUCT;

typedef struct
{
    EC4A_FM_DATA_STRUCT  ttl_FM_data;/* ������ͬ��������� */
    EC4A_FM_DATA_STRUCT  wfr_align_data[EC4A_MAX_UPDATE_BASELINE_NUM];/* ��������Ƭ��������*/
}EC4A_FM_MEASURE_DATA_STRUCT;


typedef struct
{
	SMEE_CHAR image_id[MAX_IMAGE_ID]; // ͼ��ID,[4,12]���ַ�
    SMEE_INT32 nr_exposed_success;                      /*�ع�ɹ�����[0,100]*/
    SMEE_INT32 nr_exposed_failed;                      /*�ع�ʧ�ܸ���*/
    EC4A_IMAGE_STATE_ENUM image_state;              /* �ع�״̬*/
    SMEE_BOOL is_reject;                            /*�Ƿ������ǰƬ*/
	SMEE_BOOL cora_model_validate;             /* ��Ĥ�ֶ�׼ģ����Ч */
	SMEE_BOOL fira_model_validate;             /* ��Ĥ����׼ģ����Ч */
	SMEE_BOOL hapa_model_validate;             /* �����׼ģ����Ч */
	SMEE_BOOL cowa_model_validate;             /* ��Ƭ�ֶ�׼ģ����Ч */
	SMEE_BOOL fiwa_model_validate;             /* ��Ƭ����׼ģ����Ч */	
    SMEE_INT32 is_retry; /* ��Ƭ��׼����LO��Ҫretry */	
    SMEE_DOUBLE rot_retry;/*retry��ʱ�򣬹�Ƭ��׼����ģ��׼���޵���ת*/
	EC4A_COARSE_RETICLE_ALIGN_RESULT_STRUCT CORA_result;         /* ��Ĥ�ֶ�׼��� */
	EC4A_FINE_RETICLE_ALIGN_RESULT_STRUCT FIRA_result;         /* ��Ĥ����׼��� */
	EC4A_ALIGN_MODEL_RESULT_STRUCT COWA_result;         /* �ֶ�׼��� */
	EC4A_ZONE_ALIGN_RESULT_STRUCT FIWA_result; /* ����׼��׼���������������Ϊ1����Ϊ����׼ */
	EC4A_SUBSTRATE_ALIGN_MEASURE_RESULT_STRUCT alignment_data; /*��Ƭ��׼����*/
    EC4A_RETICLE_MEASURE_DATA_STRUCT reticle_alignment_data;/*��ģ��׼����*/
    EC4A_FM_MEASURE_DATA_STRUCT fm_alignment_data;
	ADAE_timestamp image_begin;/* ͼ����ʼʱ��*/
	ADAE_timestamp wafer_coarse_alignment_begin_time;/*��Ƭ�� ��׼��ʼʱ��*/
	ADAE_timestamp wafer_coarse_alignment_end_time;  /*��Ƭ�ֶ�׼����ʱ��*/
	ADAE_timestamp wafer_fine_alignment_begin_time;/*��Ƭ�� ��׼��ʼʱ��*/
	ADAE_timestamp wafer_fine_alignment_end_time;  /*��Ƭ�� ��׼����ʱ��  */  
	ADAE_timestamp reticle_coarse_align_start_time;   /* ��Ĥ�ֶ�׼��ʼʱ�� */
	ADAE_timestamp reticle_coarse_align_end_time;     /* ��Ĥ�ֶ�׼����ʱ�� */
	ADAE_timestamp reticle_fine_align_start_time;   /* ��Ĥ����׼��ʼʱ�� */
	ADAE_timestamp reticle_fine_align_end_time;     /* ��Ĥ����׼����ʱ�� */	
}EC4A_IMAGE_LOG_STRUCT; 


/* �عⳡ�ع�����¼����� */
typedef struct
{    
	SMEE_CHAR image_id[MAX_IMAGE_ID]; // ͼ��ID,[4,12]���ַ�
    SMEE_INT32 origin_index;
    EC4A_FIELD_STATE_ENUM field_state; // �عⳡ״̬
    xy_vect field_position; // �عⳡλ��(��Ƭ����ϵ)
 	EC4A_DOSE_CONTROL_MODE_ENUM dose_mode;//��������ģʽ
 	SMEE_INT32 field_index;
	//�ع�λ��
    xyrz_vect exp_ws_hor_pos; // ˮƽλ��(����,����̨����ϵ)
    zrxry_vect exp_ws_ver_pos;// ����λ��(����,����̨����ϵ)
    xyrz_vect act_ws_hor_pos; // ˮƽλ��(ʵ��,����̨����ϵ)
    zrxry_vect act_ws_ver_pos;// ����λ��(ʵ��,����̨����ϵ)

	
     // ��������
    SMEE_DOUBLE exp_dose;	//�·�����
    SMEE_DOUBLE real_exp_dose; // ʵ�ʼ���
    SMEE_DOUBLE real_exp_time; // ʵ���ع�ʱ��
    
    ADAE_timestamp hor_move_begin; // ����̨ˮƽ���˶���ʼʱ��
    ADAE_timestamp hor_move_end;   // ����̨ˮƽ���˶�����ʱ��
    ADAE_timestamp vert_move_begin;// ����̨ˮƽ���˶���ʼʱ��
    ADAE_timestamp vert_move_end;  // ����̨ˮƽ���˶�����ʱ��
    ADAE_timestamp expose_begin;// �ع⿪ʼʱ��
    ADAE_timestamp expose_end;  // �ع����ʱ��

    //FS����ֵ
    SMEE_BOOL bZinvalid;          //����z �Ƿ���Ч
    SMEE_BOOL bRXinvalid;         //����rx �Ƿ���Ч
    SMEE_BOOL bRYinvalid;         //����ry �Ƿ���Ч
    SMEE_BOOL filler1;
    zrxry_vect sfocus;            //FS����ֵ
} EC4A_FIELD_LOG_STRUCT;

/* ͼ�����ݶ��� */
typedef struct
{  
    SMEE_CHAR image_id[EC4A_IMAGE_ID_LEN];  /* ����ģ��ͼ��ID */
	SMEE_INT32 expo_nr;		
    SMEE_INT32 filler;/*��ͼ����ع���*/
	xy_vect exp_center[MAX_FLD_NR_PER_IMG];						/*�عⳡ����λ��*/
}EC4A_EXPO_INFO_STRUCT;


/* ͼ�����ݶ��� */
typedef struct
{
    SMEE_CHAR reticle_id[EC4A_MAX_RETICLE_ID];  /* ͼ��������ģID */
    SMEE_INT32 nr_of_images; /* ����ģ��ͼ����� */
    SMEE_INT32 zfiller;    
    EC4A_EXPO_INFO_STRUCT expo_info[EC4A_MAX_IMAGES_NR];  /* ����ģ��ͼ��ID */
}EC4A_IMAGE_ROUTE_STRUCT;

typedef struct
{
    SMEE_CHAR message[EC4A_MAX_MSG_SIZE]; // �¼���Ϣ
}EC4A_UI_MESSAGE_EVENT_STRUCT;// ������Ϣ�ṹ��

/* ���ع⿪ʼ�¼�֪ͨ���� */
typedef struct
{
    EC4A_DOSE_CONTROL_MODE_ENUM dose_mode;// ��������ģʽ
    SMEE_INT32 field_index;         //�滮����ţ���0��ʼ
    SMEE_DOUBLE dose;             // �ع����
    xy_vect field_position;  // �عⳡλ��(��Ƭ����ϵ)
    zrxry_vect vert_position;//����λ��
} EC4A_EXPOSURE_BEGIN_STRUCT;


/* ���ع�����¼�֪ͨ���� */
typedef struct
{
    xy_vect field_position;  // �عⳡλ��(��Ƭ����ϵ)
} EC4A_EXPOSURE_END_STRUCT;

typedef struct
{
	SMEE_BOOL update_loading_offset;
	SMEE_BOOL update_vert_compensation;
    SMEE_BOOL update_mvs_voltage;
    SMEE_INT32 filler;
	xyrz_vect loading_offset;
	SMEE_DOUBLE vert_compensation;
    SMEE_DOUBLE mvs_voltage;
}EC4A_SAVE_ALIGNMENT_OFFSET_EVENT_STRUCT;

typedef struct
{
    SMEE_INT32 nr_marks;
    SMEE_INT32 filler;
    SMEE_DOUBLE coarse_matching_rate;
    SMEE_DOUBLE fine_matching_rate;
    EC4A_SUBSTRATE_MARK_DATA_STRUCT wafer_marks[MAX_WAFER_MARK_NUM];
}EC4A_WAFER_AILGN_BEGIN_STRUCT;

#endif /* EC4A_TC_H */

