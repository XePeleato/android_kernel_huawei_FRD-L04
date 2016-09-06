

#ifndef __CNAS_HSD_FSM_SWITCH_ON_TBL_H__
#define __CNAS_HSD_FSM_SWITCH_ON_TBL_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "NasFsm.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
extern NAS_STA_STRU                                         g_astCnasHsdSwitchOnStaTbl[];

/*****************************************************************************
  3 �궨��
*****************************************************************************/
#define CNAS_HSD_GetSwitchOnStaTbl()                        (g_astCnasHsdSwitchOnStaTbl)

/*****************************************************************************
  4 ö�ٶ���
*****************************************************************************/

enum CNAS_HSD_SWITCH_ON_STA_ENUM
{
    /* ����״̬������ʼ״̬ */
    CNAS_HSD_SWITCH_ON_STA_INIT                             = 0x00,

    /* ������ʼ������,�ȴ���ȡ���ļ��Ļظ���Ϣ */
    CNAS_HSD_SWITCH_ON_STA_WAIT_CARD_FILE_CNF               = 0x01,

    /* ������ʼ������,�ȴ�CAS�����ظ�ȷ����Ϣ */
    CNAS_HSD_SWITCH_ON_STA_WAIT_CAS_START_CNF               = 0x02,

    /* ������ʼ������,�ȴ�HSM�����ظ�ȷ����Ϣ */
    CNAS_HSD_SWITCH_ON_STA_WAIT_HSM_START_CNF               = 0x03,

    /* ������ʼ������,�ȴ�EHSM�����ظ�ȷ����Ϣ */
    CNAS_HSD_SWITCH_ON_STA_WAIT_EHSM_START_CNF              = 0x04,

    /* ������ʼ������,�ȴ�HLU�����ظ�ȷ����Ϣ */
    CNAS_HSD_SWITCH_ON_STA_WAIT_HLU_START_CNF               = 0x05,

    /* ������ʼ������,�ȴ�HRM�����ظ�ȷ����Ϣ */
    CNAS_HSD_SWITCH_ON_STA_WAIT_HRM_START_CNF               = 0x06,

    CNAS_HSD_SWITCH_ON_STA_BUTT
};
typedef VOS_UINT32 CNAS_HSD_SWITCH_ON_STA_ENUM_UINT32;

/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
extern VOS_UINT32 CNAS_HSD_GetSwitchOnStaTblSize(VOS_VOID);

extern NAS_FSM_DESC_STRU * CNAS_HSD_GetSwitchOnFsmDescAddr(VOS_VOID);

#endif



#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of CnasHsdFsmSwitchOnTbl.h */