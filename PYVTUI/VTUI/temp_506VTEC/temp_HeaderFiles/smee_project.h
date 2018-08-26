/*******************************************************************************
* Copyright (C) 2011, �Ϻ�΢����װ�����޹�˾
* All rights reserved.
* ��Ʒ��   : SSB300
* ������� :
* ģ������ :
* �ļ����� : smee_project.h
* ��Ҫ���� : ��SSB��Ʒ��ص�ͨ�����ݽṹ
*            ���ǵ����ݶ���ķ�����,���ļ��ж���Ĳ����������ͻ�곣��������SMEE����淶
* ��ʷ��¼ :
* �汾     ��  ��     ��  ��    ��  ��
* V2.0   2017.08.24   ¬����  �ſ�ID���ȵ�88�ֽ�,����SEMI��׼��������
* V1.2	 2016.07.13	  ��С��  ����Ĭ�ϳ�ʱʱ�䶨��
* v1.1   2014.11.23   ��С��  ������ģ�����ض���
* v1.0   2014.11.07   ��С��  �޸�ssb300.hΪsmee_project.h;ɾ�����ֲ��õ�����
******************************************************************************/
#ifndef SMEE_PROJECT_H_
#define SMEE_PROJECT_H_

// LOT
#define MAX_LOT_ID          88  // LOT ID�ַ������鳤��
#define MIN_LOT_ID_LENGTH    1  // LOT ID��������(������'\0')
#define MAX_LOT_ID_LENGTH   80  // LOT ID��������(������'\0')

#define MAX_WAF_NR_PER_LOT  25  // ��һLOT���ܹ�����Ĺ�Ƭ��Ŀ����
#define MAX_RET_NR_PER_LOT  6   // ��һLOTʹ����ģ��Ŀ����


// ͼ��IMAGE
#define MAX_IMG_NR_PER_LOT    24  // ��һLOTʹ��ͼ����Ŀ����
#define MAX_FLD_NR_PER_IMG  1000  // ��һͼ���Ӧ��Ƭ�ϵ��عⳡ��Ŀ����

#define MAX_IMAGE_ID          88  // ͼ��ID�ַ������鳤��
#define MIN_IMG_ID_LENGTH      4  // ͼ��ID��������(������'\0')
#define MAX_IMG_ID_LENGTH     12  // ͼ��ID��������(������'\0')



// ��ģRETICLE
#define MIN_RET_PORT_NBR        1  //��С��ģPOD����
#define MAX_RET_PORT_NBR        2  //�����ģPOD����
#define MAX_RET_BOX_SLOT_NBR    6  // ��ģ�в���Ŀ����

#define MAX_RETICLE_ID         88  // ��ģID�ַ������鳤��
#define MIN_RET_ID_LENGTH       1  // ��ģID��������(������'\0')
#define MAX_RET_ID_LENGTH      64  // ��ģID��������(������'\0')

#define MAX_RET_POD_ID         88  // ��ģPOD ID�ַ������鳤��
#define MIN_RET_POD_ID_LENGTH   1  // ��ģPOD ID��������(������'\0')
#define MAX_RET_POD_ID_LENGTH  64  // ��ģPOD ID��������(������'\0')

// ��ƬWAFER
#define MIN_WAF_PORT_NBR           1   // PORT��Ŀ����
#define MAX_WAF_PORT_NBR           3   // PORT��Ŀ����

#define MAX_WAF_CAR_SLOT_NBR       25  // ��Ƭ�в���Ŀ


#define MAX_WAF_CARRIER_ID         88  // ��Ƭ��ID�ַ������鳤��
#define MIN_WAF_CARRIER_ID_LENGTH   1  // ��Ƭ��ID��������(������'\0')
#define MAX_WAF_CARRIER_ID_LENGTH  80  // ��Ƭ��ID��������(������'\0')

#define MAX_WAFER_ID       88  // ��ƬID�ַ������鳤��
#define MIN_WAF_ID_LENGTH   1  // ��ƬID��������(������'\0')
#define MAX_WAF_ID_LENGTH  80  // ��ƬID��������(������'\0')



// ������PROTECTION RING
#define MAX_RING_ID         64  // ������ID�ַ������鳤��
#define MIN_RING_ID_LENGTH   8  // ������ID��������(������'\0')
#define MAX_RING_ID_LENGTH  24  // ������ID��������(������'\0')



// ��Ƭ���
#define MAX_WAFER_MARK_NUM 100  // ��Ƭ�����Ŀ

//����Ĭ�ϳ�ʱʱ���ض���
#ifndef DEFAULT_TIMEOUT
	#define DEFAULT_TIMEOUT		0x7FFFFFFF  // Ĭ�ϳ�ʱʱ��
#endif


typedef enum
{
    SMEE_SUBSTRATE_SIZE_MIN = 0,
    SMEE_WAFER_2_INCH,  // 2���Ƭ
    SMEE_WAFER_3_INCH,  // 3���Ƭ 
    SMEE_WAFER_4_INCH,  // 4���Ƭ
    SMEE_WAFER_5_INCH,  // 5���Ƭ
    SMEE_WAFER_6_INCH,  // 6���Ƭ
    SMEE_WAFER_8_INCH,  // 8���Ƭ
    SMEE_WAFER_12_INCH, // 12���Ƭ
    SMEE_WAFER_18_INCH, // 18���Ƭ
    SMEE_SUBSTRATE_SIZE_MAX
}SMEE_SUBSTRATE_SIZE_ENUM; // ���׳ߴ�

typedef enum
{
    SMEE_WAFER_TYPE_MIN = 0,
    SMEE_WAFER_NOTCH,       // notch wafer
    SMEE_WAFER_FLAT,        // flat wafer
    SMEE_WAFER_DOUBLE_FLAT, // ˫ƽ�߹�Ƭ
    SMEE_WAFER_NONE,        // ��ȱ�ڹ�Ƭ
    SMEE_WAFER_TYPE_MAX
}SMEE_WAFER_TYPE_ENUM; // ��Ƭ����

typedef enum
{
    SMEE_ALIGN_TYPE_MIN = 0,
    SMEE_ALIGN_NONE,   // �����ж�׼
    SMEE_ALIGN_TTL,    // ͬ���׼ Through Lens Alignment
    SMEE_ALIGN_OA,     // �����׼ Off-axis Alignment
    SMEE_ALIGN_WBA,    // ͸��ʽ�����׼ Backside Transmission Alignment
    SMEE_ALIGN_DT,     // ����ʽ�����׼ Backside Reflection Alignment
    SMEE_ALIGN_TYPE_MAX
}SMEE_ALIGN_TYPE_ENUM;// ��׼����


typedef enum
{
    SMEE_ALGORITHM_TYPE_MIN            = -1,// Ǩ�����л�������
    SMEE_ALGORITHM_GRAY_CORR           = 0, // ���� GrayCorr
                                            // GCM: Gray Correlation Match
                                            // �Ҷ������ƥ���㷨
    SMEE_ALGORITHM_EDGE_MAX_I          = 1, // ���� EdgeMaxI
                                            // EMM: Edge Max Correlation Match(TypeI)
                                            // ��Ե���������ƥ���㷨
    SMEE_ALGORITHM_EDGE_MAX_II         = 2, // ���� EdgeMaxII
                                            // EMM: Edge Max Correlation Match(TypeII)
                                            // ��Ե���������ƥ���㷨
    SMEE_ALGORITHM_EDGE_MAX_ENHANCED   = 3, // ���� EdgeMaxEnhanced
                                            // EME: Edge Max Correlation Match(Enhanced)
                                            // ��ǿ�ͱ�Ե���������ƥ���㷨
    SMEE_ALGORITHM_EDGE_CORR           = 4, // ���� EdgeCorr
                                            // ECM: Edge Correlation Match
                                            // ��Ե�����ƥ���㷨
    SMEE_ALGORITHM_TEXTURE_CORR        = 5, // ���� TextureCorr
                                            // TCM: Texture Correlation Match
                                            // ���������ƥ���㷨
    SMEE_ALGORITHM_LASER_MARK_LOCATION = 6, // ���� LaserMarkLocation
                                            // LML: laser mark location 
                                            // �û��������㷨
    SMEE_ALGORITHM_REGION_GRAY_CORR    = 7, // ���� RegionGrayCorr
                                            // RGM: Region Gray Match
                                            // ����Ҷ������ƥ��
    SMEE_ALGORITHM_GRAY_CORR_II        = 8, // ���� GrayCorrII
                                            // GCM: Gray Correlation Match(Type II)
                                            // �Ҷ������ƥ���㷨
    SMEE_ALGORITHM_TYPE_MAX            = 100
}SMEE_ALGORITHM_TYPE_ENUM;// �㷨����


// ��������ö��
typedef enum
{
    SMEE_SURFACE_TYPE_MIN = 0,
    SMEE_SURFACE_POLISH_ONE_SIDE,    // ����ʯ����Ƭ
    SMEE_SURFACE_POLISH_BOTH_SIDE,   // ����ʯ˫��Ƭ
    SMEE_SURFACE_WAFER,              // ��Ƭ
    SMEE_SURFACE_CUSTOMIZE_1,        // �Զ�������1
    SMEE_SURFACE_CUSTOMIZE_2,        // �Զ�������2
    SMEE_SURFACE_TYPE_MAX
} SMEE_SURFACE_TYPE_ENUM;

#endif /* SMEE_PROJECT_H_ */

