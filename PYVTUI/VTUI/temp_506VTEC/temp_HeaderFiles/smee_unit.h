/*******************************************************************************
* Copyright (C) 2011, �Ϻ�΢����װ�����޹�˾
* All rights reserved.
* ��Ʒ�� :   
* ������� :
* ģ������ :
* �ļ����� : smee_unit.h
* ��Ҫ���� : ���ļ������˻�����λ���ͼ��䵥λת����
* ��ʷ��¼ :
* �汾      ����        ����    ����
* 1.0    2011-7-7      ë����   �½�
* 1.1    2011-9-8      ë����   ������������޸�
* 1.2    2011-9-30     ë����   �޸ı���淶
* 1.3    2011-10-19    ë����   ������Ŀ����������޸�
* 1.4    2012-02-22    ë����   ����ѭ��ˮ������λΪ(L/MIN)
******************************************************************************/

#ifndef SMEE_UNIT_H_
#define SMEE_UNIT_H_

#include "smee_type.h"

/* PI */
#define SMEE_PI 3.1415926535897932385

/* ��λת��,SI��ʾ���ʵ�λ */
/* ���ȵ�λ*/
/* �� <-> Ƥ�� */
#define SMEE_SI_TO_PM(v)  ( ((SMEE_LDOUBLE)(v)) * 1.0e12 )
#define SMEE_PM_TO_SI(v)  ( ((SMEE_LDOUBLE)(v)) * 1.0e-12 )

/* �� <-> ���� */
#define SMEE_SI_TO_NM(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e9 )
#define SMEE_NM_TO_SI(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e-9 )

/* �� <-> ΢�� */
#define SMEE_SI_TO_UM(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e6 )
#define SMEE_UM_TO_SI(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e-6 )

/* �� <-> ���� */
#define SMEE_SI_TO_MM(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e3 )
#define SMEE_MM_TO_SI(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e-3 )


/* �ٶȵ�λ */
/* ��/�� <-> ����/���� */
#define SMEE_SI_TO_NM_PER_MS(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e6 )
#define SMEE_NM_PER_MS_TO_SI(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e-6 )

/* Ƶ�� */
/* ���� <-> ǧ���� */
#define SMEE_SI_TO_KHZ(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e-3 )
#define SMEE_KHZ_TO_SI(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e3 )

/* ���� <-> �׺��� */
#define SMEE_SI_TO_MHZ(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e-6 )
#define SMEE_MHZ_TO_SI(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e6 )



/* �Ƕȵ�λ */
/* ���� <-> ������ */
#define SMEE_SI_TO_MRAD(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e3 )
#define SMEE_MRAD_TO_SI(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e-3 )

/* ���� <-> ΢���� */
#define SMEE_SI_TO_URAD(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e6 )
#define SMEE_URAD_TO_SI(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e-6 )

/* ���� <-> �ɻ��� */
#define SMEE_SI_TO_NRAD(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e9 )
#define SMEE_NRAD_TO_SI(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e-9 )

/* ���� <-> �� */
#define SMEE_SI_TO_DEGREE(v)  ( ((SMEE_DOUBLE)(v)) * 180.0 / SMEE_PI )
#define SMEE_DEGREE_TO_SI(v)  ( ((SMEE_DOUBLE)(v)) * SMEE_PI / 180.0 )



/* ������λ */
/* ����Joules <-> uJoules */
#define SMEE_SI_TO_UJ(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e6 )
#define SMEE_UJ_TO_SI(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e-6 )

/* ����/ƽ���� <-> ����/ƽ������ */
#define SMEE_SI_TO_MJCM(v)  ( ((SMEE_DOUBLE)(v)) * 0.1 )
#define SMEE_MJCM_TO_SI(v)  ( ((SMEE_DOUBLE)(v)) * 10.0 )

/* ��/ƽ���� <-> ����/ƽ������ */
#define SMEE_SI_TO_MWCM(v)  ( ((SMEE_DOUBLE)(v)) * 0.1 )
#define SMEE_MWCM_TO_SI(v)  ( ((SMEE_DOUBLE)(v)) * 10.0 )



/* �¶ȵ�λ */
/* K <-> Celsius���� */
#define SMEE_SI_TO_CELSIUS(v)  ( ((SMEE_DOUBLE)(v)) - 273.15 )
#define SMEE_CELSIUS_TO_SI(v)  ( ((SMEE_DOUBLE)(v)) + 273.15 )



/* ʱ�䵥λ */
/* �� <-> ���� */
#define SMEE_SI_TO_MS(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e3 )
#define SMEE_MS_TO_SI(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e-3 )

/* �� <-> ΢�� */
#define SMEE_SI_TO_US(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e6 )
#define SMEE_US_TO_SI(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e-6 )

/* �� <-> ���� */
#define SMEE_SI_TO_MINUTE(v)  ( ((SMEE_DOUBLE)(v)) / 60.0 )
#define SMEE_MINUTE_TO_SI(v)  ( ((SMEE_DOUBLE)(v)) * 60.0 )

/* �� <-> Сʱ */
#define SMEE_SI_TO_HOUR(v)  ( ((SMEE_DOUBLE)(v)) / 3600.0 )
#define SMEE_HOUR_TO_SI(v)  ( ((SMEE_DOUBLE)(v)) * 3600.0 )

/* �� <-> �� */
#define SMEE_SI_TO_DAY(v)  ( ((SMEE_DOUBLE)(v)) / 86400.0 )
#define SMEE_DAY_TO_SI(v)  ( ((SMEE_DOUBLE)(v)) * 86400.0 )


/* ѹ����λ */
/* ��˹�� <-> BAR */
#define SMEE_SI_TO_BAR(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e-5 )
#define SMEE_BAR_TO_SI(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e5 )

/* ��˹�� <-> PSI */
#define SMEE_SI_TO_PSI(v)  ( ((SMEE_DOUBLE)(v)) * 145.0 * 1.0e-6 )
#define SMEE_PSI_TO_SI(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e6 / 145.0 )


/* 1 <-> ppm */
#define SMEE_SI_TO_PPM(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e6 )
#define SMEE_PPM_TO_SI(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e-6 )


/* 1 <-> %, �ٷֱ� */
#define SMEE_SI_TO_PCT(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e2 )
#define SMEE_PCT_TO_SI(v)  ( ((SMEE_DOUBLE)(v)) * 1.0e-2 )

/*ѭ��ˮ������λΪ(L/MIN),*/
/* ������/�� <-> ��/ÿ���� */
#define SMEE_SI_TO_LPM(v)   ( ((SMEE_DOUBLE)(v)) * 1.0e3 * 60.0)      
#define SMEE_LPM_TO_SI(v)   ( ((SMEE_DOUBLE)(v)) * 1.0e-3 / 60.0)

#endif
