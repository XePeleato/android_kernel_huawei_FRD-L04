

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "PsTypeDef.h"
#include "NasMmcCtx.h"
#include "NasMmlLib.h"
#include "Nasrrcinterface.h"
#include "MmcGmmInterface.h"
#include "MmcMmInterface.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif
#include "NasMmcProcRegRslt.h"
#include "NasMmcProcNvim.h"
#include "NasMmcComFunc.h"
#include "NasMmcTimerMgmt.h"
#include "NasMmlMsgProc.h"
#include "NasMmcSndLmm.h"
#include "NasMmcSndGuAs.h"
#include "NasMmcFsmPlmnList.h"
#include "NasMmcFsmPLmnListTbl.h"
#include "NasMmcSndMscc.h"
#include "NasMmcSndGmm.h"
#include "NasMmcSndMm.h"
#include "NasMmcSndOm.h"
#include "NasMmcSndInternalMsg.h"
#include "NasMmcPlmnSelectionStrategy.h"
#include "NasMmcProcSuspend.h"
#include "NasMmlMsgProc.h"
#include "NasUtranCtrlInterface.h"

#include "MsccMmcInterface.h"
#include "NasMmcSndCss.h"

#include "NasUsimmApi.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_FSM_PLMN_LIST_C
/*****************************************************************************
  2 ȫ�ֱ���
*****************************************************************************/

/*****************************************************************************
  3 �궨��
*****************************************************************************/


/*lint -save -e958 */


VOS_UINT32  NAS_MMC_RcvTafPlmnListReq_PlmnList_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapStatus;

    /* ��ȡLTE����״̬ */
    enLteCapStatus = NAS_MML_GetLteCapabilityStatus();
#endif

    /* ���浱ǰ��ϢΪ״̬�������Ϣ */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);


    NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_USER_LIST_SRCH);



#if (FEATURE_ON == FEATURE_LTE)
    /* ����disable L�ı�� */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == enLteCapStatus)
     || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLteCapStatus))
    {
        NAS_MMC_SetPreLteDisableFlg_PlmnList(VOS_TRUE);
    }
    else
    {
        NAS_MMC_SetPreLteDisableFlg_PlmnList(VOS_FALSE);
    }
#endif

    /* �ж��Ƿ���Ҫanycell����,��Ҫ������anycell ������� */
    if (VOS_TRUE == NAS_MMC_IsNeedAnyCellSrch_PlmnList())
    {
        NAS_MMC_SetAnyCellSrchFlg_PlmnList(VOS_TRUE);
    }

    /* ��ʼ������б��ѵ�PLMN */
    NAS_MMC_InitAbortListSearchPlmn();

    /* �����û�LIST�������� */
    NAS_MMC_ProcUserPlmnListReq_PlmnList();

    return VOS_TRUE;
}



VOS_UINT32  NAS_MMC_RcvInterPlmnListReq_PlmnList_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_INTER_PLMN_LIST_REQ_STRU   *pstInternalMsg  = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapStatus;

    enLteCapStatus      = NAS_MML_GetLteCapabilityStatus();
#endif

    pstInternalMsg  = (NAS_MMC_INTER_PLMN_LIST_REQ_STRU *)pstMsg;

    /* ���浱ǰ��ϢΪ״̬�������Ϣ */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)
    /* ����disable L��� */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == enLteCapStatus)
     || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLteCapStatus))
    {
        NAS_MMC_SetPreLteDisableFlg_PlmnList(VOS_TRUE);
    }
    else
    {
        NAS_MMC_SetPreLteDisableFlg_PlmnList(VOS_FALSE);
    }
#endif

    /* ��ʼ������б��ѵ�PLMN */
    NAS_MMC_InitAbortListSearchPlmn();

    NAS_MMC_UpdateSearchedTypeByInterPlmnSearchInfo_PlmnList(pstInternalMsg->astInterPlmnSearchInfo);

    NAS_MMC_ProcInterListReq_PlmnList();
    return VOS_TRUE;
}




VOS_UINT32  NAS_MMC_RcvTiPeriodTryingUserPlmnListExpired_PlmnList_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapStatus;

    enLteCapStatus = NAS_MML_GetLteCapabilityStatus();
#endif

    /* ���浱ǰ��ϢΪ״̬�������Ϣ */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);




#if (FEATURE_ON == FEATURE_LTE)
    /* ����disable L��� */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == enLteCapStatus)
     || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLteCapStatus))
    {
        NAS_MMC_SetPreLteDisableFlg_PlmnList(VOS_TRUE);
    }
    else
    {
        NAS_MMC_SetPreLteDisableFlg_PlmnList(VOS_FALSE);
    }
#endif

    /* ��ʼ������б��ѵ�PLMN */
    NAS_MMC_InitAbortListSearchPlmn();

    /* �ж��Ƿ���Ҫanycell����,��Ҫ������anycell ������� */
    if (VOS_TRUE == NAS_MMC_IsNeedAnyCellSrch_PlmnList())
    {
        NAS_MMC_SetAnyCellSrchFlg_PlmnList(VOS_TRUE);
    }

    /* �����û�LIST�������� */
    NAS_MMC_ProcUserPlmnListReq_PlmnList();

    return VOS_TRUE;
}



VOS_UINT32  NAS_MMC_RcvTiPeriodTryingInterPlmnListExpired_PlmnList_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapStatus;

    enLteCapStatus = NAS_MML_GetLteCapabilityStatus();
#endif

    /* ���浱ǰ��ϢΪ״̬�������Ϣ */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);




#if (FEATURE_ON == FEATURE_LTE)

    /* ����disable L��� */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == enLteCapStatus)
     || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLteCapStatus))
    {
        NAS_MMC_SetPreLteDisableFlg_PlmnList(VOS_TRUE);
    }
    else
    {
        NAS_MMC_SetPreLteDisableFlg_PlmnList(VOS_FALSE);
    }
#endif

    /* ��ʼ������б��ѵ�PLMN */
    NAS_MMC_InitAbortListSearchPlmn();

    /* פ��̬��GTLģʽTDΪ��ģʱ��Ҫ֪ͨMM/GMM��������״̬ */
    if (VOS_TRUE == NAS_MMC_IsCurrentTdscdmaMode())
    {
        /* ��GMM��������ָʾ */
        NAS_MMC_SndGmmPlmnSchInit();

        /* ��MM��������ָʾ */
        NAS_MMC_SndMmPlmnSchInit();
    }

    /* ���ݲ�ͬ����ģʽ,����LIST��������Ǩ���ȴ��������״̬������������ʱ��*/
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_GetCurrNetRatType());

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvTafPlmnListReq_PlmnList_NonInit(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �õ�ǰ��Ϣ���µ�ǰ״̬�������Ϣ */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

    return VOS_TRUE;
}


VOS_VOID NAS_MMC_SndRslt_PlmnList(
    NAS_MMC_PLMN_LIST_RESULT_ENUM_UINT32                    enRslt,
    VOS_UINT8                                               ucNeedPlmnSearch,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstListInfo,
    NAS_MMC_PLMN_LIST_REG_RSLT_INFO_STRU                   *pstRegRsltInfo
)
{

    NAS_MMC_PLMN_LIST_SEARCH_SCENE_ENUM_UINT8               enPlmnListSearchScene;

    enPlmnListSearchScene   = NAS_MMC_GetPlmnListSearchScene_PlmnList(ucNeedPlmnSearch);

    NAS_MMC_SndPlmnListRslt(enRslt,ucNeedPlmnSearch,enPlmnListSearchScene,
                                pstListInfo,pstRegRsltInfo);
    return;
}

VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

    NAS_MMC_SndMsccListSearchCnfMsg_PlmnList();

    /* δ��ʼ��������ʱ�����б�Ϊ��,��¼��ǰע�ᵼ�µĺ���additionֵ��L1 MAIN��
       �յ���·�ͷź����additionֵ�����Ƿ񴥷����� */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());

    /*�˳�״̬��*/
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

    /* ����ID_MMC_MSCC_PLMN_LIST_ABORT_CNF */
    NAS_MMC_SndMsccPlmnListAbortCnf_PlmnList();

    /* δ��ʼ�������û���LIST������ʱ����ʱ����ʱ�����б�Ϊ��
       ��¼��ǰע�ᵼ�µĺ���additionֵ��L1 MAIN���յ���·�ͷź�
       ����additionֵ�����Ƿ񴥷����� */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());

    /* �˳�״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvGmmSignalingStatusInd_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����GMM�ϱ�����������ָʾ */
    NAS_MMC_ProcRrcConnRelInd_PlmnList();

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvMmRrConnInfoInd_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����MM�ϱ���RR�����ͷ�ָʾ */
    NAS_MMC_ProcRrcConnRelInd_PlmnList();

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvMmRrRelInd_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����MM�ϱ���MM�����ͷ�ָʾ */
    NAS_MMC_ProcRrcConnRelInd_PlmnList();

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvRrMmRelInd_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����RRC��·�ͷ����� */
    NAS_MMC_ProcRrcConnRelInd_PlmnList();

    return VOS_TRUE;
}



VOS_UINT32  NAS_MMC_RcvGmmTbfRelInd_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �ж�RRC�����Ƿ���� */
    if ( VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        /* ���ؼ����ȴ� */
        return VOS_TRUE;
    }

    /* ֹͣ�ȴ�RRC��·�ͷŶ�ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

    /* ��GAS����LIST��������,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);

    /* ��פ��̬֪ͨMM/GMM������ʼ */
    if (NAS_MMC_AS_CELL_NOT_CAMP_ON == NAS_MMC_GetAsCellCampOn())
    {
        /* ��GMM��������ָʾ */
        NAS_MMC_SndGmmPlmnSchInit();

        /* ��MM��������ָʾ */
        NAS_MMC_SndMmPlmnSchInit();

        /* ���ý�������״̬ */
        NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);
    }

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvGmmNetworkDetachInd_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMCGMM_NETWORK_DETACH_IND_STRU                         *pstDetachMsg = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    pstDetachMsg        = (MMCGMM_NETWORK_DETACH_IND_STRU *)pstMsg;

    /* ����Detach��� */
    enAdditionalAction = NAS_MMC_ProcGmmNetworkDetachInd(pstDetachMsg);

    /* AdditionalAction��Ч������PS����һ���Ķ������� */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_PlmnList(enAdditionalAction);
    }

#if   (FEATURE_ON == FEATURE_LTE)
        /* ��LMM����detach�����Ϣ */
    NAS_MMC_SndLmmMtDetachIndActionResultReq(pstDetachMsg->ulDetachType,
                                             (NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16)pstDetachMsg->ulDetachCause);
#endif

    /* ��Ǩ��״̬ */
    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvMmCsRegResultInd_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMMMC_CS_REG_RESULT_IND_STRU       *pstCsRegRslt = VOS_NULL_PTR;

    pstCsRegRslt = (MMMMC_CS_REG_RESULT_IND_STRU*)pstMsg;

    /* �ȴ�RRC��·�ͷ�ʱ���������ѡ���л��Լ�CCO����������ᷢ���ı䣬
       ״̬���˳����յ������ע������Ϣ����Ҫ�жϵ�ǰ������
       �����ı䣬�����ı�������ǰע���� */
    if ( pstCsRegRslt->enNetType != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    /* ����CS��ע���� */
    NAS_MMC_ProcCsRegRslt_PlmnList(pstCsRegRslt);

    /* ��Ǩ��״̬ */
    return VOS_TRUE;
}




VOS_UINT32  NAS_MMC_RcvGmmPsRegResultInd_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    GMMMMC_PS_REG_RESULT_IND_STRU      *pstPsRegRslt = VOS_NULL_PTR;

    pstPsRegRslt = (GMMMMC_PS_REG_RESULT_IND_STRU*)pstMsg;

    /* �ȴ�RRC��·�ͷ�ʱ���������ѡ���л��Լ�CCO����������ᷢ���ı䣬
       ״̬���˳����յ������ע������Ϣ����Ҫ�жϵ�ǰ������
       �����ı䣬�����ı�������ǰע���� */
    if ( pstPsRegRslt->enNetType != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    /* ����PS��ע����*/
    NAS_MMC_ProcPsRegRslt_PlmnList(pstPsRegRslt);

    /* ��Ǩ��״̬ */
    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvMmAbortInd_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMMMC_ABORT_IND_STRU               *pstMmAbortInd   = VOS_NULL_PTR;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_GU_ACTION_RSLT_INFO_STRU    stActionRslt;
#endif

    pstMmAbortInd = (MMMMC_ABORT_IND_STRU*)pstMsg;

    /* ���ԭ��ֵ��Ϊ#6���Ҳ�Ϊ#17��ֱ�ӷ��� */
    if ((NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME != pstMmAbortInd->enAbortCause)
     && (NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE != pstMmAbortInd->enAbortCause))
    {
        return VOS_TRUE;
    }

    /* ���ԭ��ֵ#6������CS AdditionΪAnycellפ�� */
    if (NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME == pstMmAbortInd->enAbortCause)
    {
        NAS_MMC_SetCsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL);
    }

#if (FEATURE_ON == FEATURE_LTE)

    /* ��LMM����ID_MMC_LMM_ACTION_RESULT_REQ */
    /* ����ActionRslt��Ϣ�����ΪCN_Rej,������Ϊ����NAS_MML_PROC_MM_ABORT����
       ����ͽ������CS��ԭ��ֵΪAbort����ԭ��ֵ */
    stActionRslt.enProcType     = NAS_MML_PROC_MM_ABORT;
    stActionRslt.enRegRst       = NAS_MML_REG_RESULT_CN_REJ;
    stActionRslt.enReqDomain    = NAS_MMC_REG_DOMAIN_CS;
    stActionRslt.enRstDomain    = NAS_MMC_REG_DOMAIN_CS;
    stActionRslt.enCnCause      = pstMmAbortInd->enAbortCause;
    stActionRslt.ulAttemptCount = 0x0;

    NAS_MMC_SndLmmRegActionResultReq(&stActionRslt);
#endif

    return VOS_TRUE;
}




VOS_UINT32  NAS_MMC_RcvRrMmSysInfoInd_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����WASϵͳ��Ϣ */
    NAS_MMC_ProcWasSysInfo_PlmnList(pstMsg);

    /* ��Ǩ��״̬ */
    return VOS_TRUE;
}



VOS_UINT32  NAS_MMC_RcvGrrMmSysInfoInd_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����յ�GAS��ϵͳ��Ϣ����ĿǰUtran��Enable��������Disable Utran */
    NAS_MMC_RcvGasSysInfoSetUtranCapabilityStatus();

    /* ����GASϵͳ��Ϣ */
    NAS_MMC_ProcGasSysInfo_PlmnList(pstMsg);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvRrMmSuspendInd_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_IND_ST             *pstSuspendMsg = VOS_NULL_PTR;

    pstSuspendMsg = (RRMM_SUSPEND_IND_ST*)pstMsg;

    /* ���ݲ�ͬ�Ĺ���ԭ��ֵ��������ͬ��״̬�� */
    switch (pstSuspendMsg->ucSuspendCause)
    {
        case MMC_SUSPEND_CAUSE_CELLRESELECT:
        case MMC_SUSPEND_CAUSE_REDIRECTION:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_CELLRESEL);
            NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                                     NAS_MML_GetSimPsRegStatus());
            break;

        case MMC_SUSPEND_CAUSE_PLMNSEARCH:
            /* ��WAS���͹���ʧ�� */
            NAS_MMC_SndAsSuspendRsp(RRC_NAS_SUSPEND_FAILURE, pstSuspendMsg->MsgHeader.ulSenderPid);

            /* ���·���״̬ */


            NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);

            /* ��Ҫ�����ͷ���· */
            NAS_MMC_SndMmRelReq();

            NAS_MMC_SndGmmRelReq();

            NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

            break;
        case MMC_SUSPEND_CAUSE_HANDOVER:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_HO);
            NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                                     NAS_MML_GetSimPsRegStatus());
            break;

        case MMC_SUSPEND_CAUSE_CELLCHANGE:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_CCO);
            NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                                     NAS_MML_GetSimPsRegStatus());
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmSuspendInd_PlmnList_WaitRrcConnRelInd:Unexpected suspend type!");
            break;
    }

    return VOS_TRUE;
}



VOS_UINT32  NAS_MMC_RcvMmcMmcSuspendRslt_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMCMMC_SUSPEND_RSLT_STRU       *pstSuspendRslt = VOS_NULL_PTR;

    NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                             NAS_MML_GetSimPsRegStatus());

    pstSuspendRslt  = (NAS_MMCMMC_SUSPEND_RSLT_STRU*)pstMsg;

    /* suspend ��ϵͳ��ѡ��� */
    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMmcMmcSuspendRslt_PlmnList_WaitRrcConnRelInd:SUSPEND COMPLETE!");

    /* ����״̬���˳���� ������Ӧ�Ĵ��� */
    if ( (NAS_MMC_SUSPEND_FAIL == pstSuspendRslt->enRslt)
      && (NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST != pstSuspendRslt->enFailCause))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMmcMmcSuspendRslt_PlmnList_WaitRrcConnRelInd:SUSPEND FAIL!");

        return VOS_TRUE;
    }

    /* ��ѡ��ǰ���뼼���Ѿ��ı䣬��Ҫ��ѡ��ʼ�������Ľ��뼼�����ȼ� */
 #if (FEATURE_ON == FEATURE_CSG)
    if (VOS_TRUE == NAS_MMC_IsCsgList_PlmnList())
    {
        NAS_MMC_InitCsgListSearchRatInfo_PlmnList();
    }
    else
 #endif
    {
        NAS_MMC_InitSearchRatInfo_PlmnList();
    }

    if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
    {
        /* ֹͣ������ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

        NAS_MMC_SndMsccPlmnListRejMsg_PlmnList();

        /* ����δ����LIST�������������������б�Ϊ�� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());


        /* �˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

#if (FEATURE_ON == FEATURE_LTE)

    /* �жϵ�ǰ����ģʽ */
    if ( NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        /* ��ǰ����RRC����,��GU��ϵͳ��LTE��,LTE��ʱ������������,
           MMC��ʱ��Ҫ�ȴ�L�µ�ע���� */

        /* ֹͣ������ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

        /* ����CSPS��AdditionalAction */
        NAS_MMC_SetCsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_BUTT);
        NAS_MMC_SetPsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_BUTT);

        NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();

        NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_PS);

#if (FEATURE_ON == FEATURE_IMS)
        NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_IMS);
#endif

        /* Ǩ��״̬���ȴ�EPSע���� */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_EPS_REG_IND);

        /* ����������ʱ�� */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_REG_IND, TI_NAS_MMC_WAIT_EPS_REG_IND_LEN);

        return VOS_TRUE;
    }
#endif

    /*  ��������������ӣ�������ȴ�  */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        return VOS_TRUE;
    }

    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

    /* ��ǰ���뼼������LIST��������,Ǩ��״̬������������ʱ�� */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_GetCurrNetRatType());

    /* ��פ��̬֪ͨMM/GMM������ʼ */
    if (NAS_MMC_AS_CELL_NOT_CAMP_ON == NAS_MMC_GetAsCellCampOn())
    {
        /* ��GMM��������ָʾ */
        NAS_MMC_SndGmmPlmnSchInit();

        /* ��MM��������ָʾ */
        NAS_MMC_SndMmPlmnSchInit();

        /* ���ý�������״̬ */
        NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

        return VOS_TRUE;
    }

    /* פ��̬��GTLģʽTDΪ��ģʱ��Ҫ֪ͨMM/GMM��������״̬ */
    if (VOS_TRUE == NAS_MMC_IsCurrentTdscdmaMode())
    {
        /* ��GMM��������ָʾ */
        NAS_MMC_SndGmmPlmnSchInit();

        /* ��MM��������ָʾ */
        NAS_MMC_SndMmPlmnSchInit();
    }

    return VOS_TRUE;

}


VOS_UINT32  NAS_MMC_RcvTiWaitRrcConnRelIndExpired_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitRrcConnRelIndExpired_PlmnList_WaitRrcConnRelInd Enter!");

    /* ����ҵ�񣬻ظ��б���ʧ�� */
    if (VOS_TRUE == NAS_MML_GetCsServiceExistFlg())
    {
        NAS_MMC_SndMsccPlmnListRejMsg_PlmnList();
    }
    else
    {
        NAS_MMC_StartPeriodTryingUserListSrchTimer_PlmnList();
    }


    /* ����δ��ʼ�������������������б�Ϊ�գ���Ҫ�����Գ��ԣ��˳�״̬������Ҫ�������� */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());


    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU                *pstAbortMsg = VOS_NULL_PTR;


    VOS_UINT32                          ulIsPrefbandListScene;
    VOS_UINT32                          ulIsFullbandListScene;

    ulIsPrefbandListScene = NAS_MMC_IsPrefBandListSearchScene_PlmnList();
    ulIsFullbandListScene = NAS_MMC_IsFullBandListSearchScene_PlmnList();

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU*)pstMsg;

    /* ��¼״̬���˳���� */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);


    /* ����ڵ�ϵͳ��Ϣʱ��,�յ�SUSPEND IND��Ϣ�����ϵ�ǰ״̬����������ϵͳ���� */
    if ( NAS_BuildEventType(WUEPS_PID_WRR, RRMM_SUSPEND_IND) == pstAbortMsg->ulEventType )
    {
        /* ֹͣ�ȴ�WASϵͳ��Ϣ�ı�����ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO);

        /* ����5S�����Գ��Զ�ʱ�� */
        if ( VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
        {
             /* CSҵ�����绰���������Ľ����list rej��Ҫ��ֹlist�ѣ�
                ��Ӧҵ�����AT�ڱ�list����ռ�ã��û��޷���������绰���ն��� */
            if (VOS_TRUE == NAS_MML_GetCsServiceExistFlg())
            {
                /* ����LIST REJ��MSCC */
                NAS_Mmc_SndMsccPlmnListRej();
            }
            else
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST, TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST_LEN);
            }
        }
#if (FEATURE_ON == FEATURE_CSG)
        else if (VOS_TRUE == NAS_MMC_IsCsgList_PlmnList())
        {
            /* CSҵ�����绰���������Ľ����list rej��Ҫ��ֹlist�ѣ�
                ��Ӧҵ�����AT�ڱ�list����ռ�ã��û��޷���������绰���ն��� */
            if (VOS_TRUE == NAS_MML_GetCsServiceExistFlg())
            {
                /* ����LIST REJ��MSCC */
                NAS_MMC_SndMsccCsgListSearchRej();
            }
            else
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH, TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH_LEN);
            }
        }
#endif
        else
        {
            /* prefband list �� fullband list������������Ҫ����TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST��ʱ�� */
            if ((VOS_FALSE == ulIsPrefbandListScene)
             && (VOS_FALSE == ulIsFullbandListScene))
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST, TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST_LEN);
            }
        }

        /* ����״̬��ʧ�ܵ��˳���� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼״̬���˳���� */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ��¼֪ͨMSCC������ */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU                *pstAbortMsg = VOS_NULL_PTR;


    VOS_UINT32                          ulIsPrefbandListScene;
    VOS_UINT32                          ulIsFullbandListScene;

    ulIsPrefbandListScene = NAS_MMC_IsPrefBandListSearchScene_PlmnList();
    ulIsFullbandListScene = NAS_MMC_IsFullBandListSearchScene_PlmnList();

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU*)pstMsg;

    /* ��¼״̬���˳���� */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);


    /* ����ڵ�ϵͳ��Ϣʱ��,�յ�SUSPEND IND��Ϣ�����ϵ�ǰ״̬����������ϵͳ���� */
    if ( NAS_BuildEventType(UEPS_PID_GAS, RRMM_SUSPEND_IND) == pstAbortMsg->ulEventType )
    {
        /* ֹͣ�ȴ�WASϵͳ��Ϣ�ı�����ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO);

        /* ����5S�����Գ��Զ�ʱ�� */
        if ( VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
        {
             /* CSҵ�����绰���������Ľ����list rej��Ҫ��ֹlist�ѣ�
                ��Ӧҵ�����AT�ڱ�list����ռ�ã��û��޷���������绰���ն��� */
            if (VOS_TRUE == NAS_MML_GetCsServiceExistFlg())
            {
                /* ����LIST REJ��MSCC */
                NAS_Mmc_SndMsccPlmnListRej();
            }
            else
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST, TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST_LEN);
            }
        }
#if (FEATURE_ON == FEATURE_CSG)
        else if (VOS_TRUE == NAS_MMC_IsCsgList_PlmnList())
        {
            /* CSҵ�����绰���������Ľ����list rej��Ҫ��ֹlist�ѣ�
                ��Ӧҵ�����AT�ڱ�list����ռ�ã��û��޷���������绰���ն��� */
            if (VOS_TRUE == NAS_MML_GetCsServiceExistFlg())
            {
                /* ����LIST REJ��MSCC */
                NAS_MMC_SndMsccCsgListSearchRej();
            }
            else
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH, TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH_LEN);
            }
        }
#endif
        else
        {
            /* prefband list �� fullband list������������Ҫ����TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST��ʱ�� */
            if ((VOS_FALSE == ulIsPrefbandListScene)
             && (VOS_FALSE == ulIsFullbandListScene))
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST, TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST_LEN);
            }
        }

        /* ����״̬��ʧ�ܵ��˳���� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼״̬���˳���� */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ��¼֪ͨMSCC������ */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvRrMmSysInfoInd_PlmnList_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ�ȴ�WASϵͳ��Ϣ�ı�����ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO);

    /* ����WASϵͳ��Ϣ */
    NAS_MMC_ProcWasSysInfo_PlmnList(pstMsg);

    /* ״̬���˳����Ϊ�� */
    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnList())
    {
        NAS_MMC_ProcFsmAbort_PlmnList();

        /* ����δ����LIST�������������������б�Ϊ�� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ���µ�ǰ�ȴ�CSPS��ע���� */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_CS);
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    /* Ǩ�Ƶ��ȴ�ע����״̬ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_CSPS_REG_IND);

    /* ����������ʱ�� */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND, TI_NAS_MMC_WAIT_CSPS_REG_IND_LEN);

    return VOS_TRUE;

}


VOS_UINT32  NAS_MMC_RcvGrrMmSysInfoInd_PlmnList_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����յ�GAS��ϵͳ��Ϣ����ĿǰUtran��Enable��������Disable Utran */
    NAS_MMC_RcvGasSysInfoSetUtranCapabilityStatus();

    /* ֹͣ�ȴ�GASϵͳ��Ϣ�ı�����ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO);

    /* ����GASϵͳ��Ϣ */
    NAS_MMC_ProcGasSysInfo_PlmnList(pstMsg);

    /* ״̬���˳����Ϊ�� */
    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnList())
    {
        NAS_MMC_ProcFsmAbort_PlmnList();

        /* ����δ����LIST�������������������б�Ϊ�� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ���µ�ǰ�ȴ�CSPS��ע���� */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_CS);
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    /* Ǩ�Ƶ��ȴ�ע����״̬ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_CSPS_REG_IND);

    /* ����������ʱ�� */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND, TI_NAS_MMC_WAIT_CSPS_REG_IND_LEN);

    return VOS_TRUE;
}



VOS_UINT32  NAS_MMC_RcvRrMmAreaLostInd_PlmnList_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ��ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO);

    NAS_MMC_SaveLastCampedPlmnWithRat(NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMcc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMnc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.enCampPlmnNetRat);


    /* ���פ��PLMN RAI LAC��Ϣ*/
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* ��ǰ�źŸ��� */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());


    /* �ϱ���Ӧ��CS/PS����״̬MSCC_MMC_SERVICE_STATUS_NO_SERVICE */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);
    NAS_MMC_UpdateRegStateSpecPlmnSearch();

    /* ״̬���˳����Ϊ�� */
    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnList())
    {
        NAS_MMC_ProcFsmAbort_PlmnList();

        /* ����δ����LIST�������������������б�Ϊ�� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
    {
        NAS_MMC_SndMsccPlmnListRejMsg_PlmnList();

        /* ����δ����LIST�������������������б�Ϊ�� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* ��WAS����LIST��������Ǩ��״̬���ȴ�WAS LIST�����ظ�״̬ ������������ʱ�� */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

    /* ��GMM��������ָʾ */
    NAS_MMC_SndGmmPlmnSchInit();

    /* ��MM��������ָʾ */
    NAS_MMC_SndMmPlmnSchInit();

    /* ���ý�������״̬ */
    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    return VOS_TRUE;
}



VOS_UINT32  NAS_MMC_RcvRrMmAreaLostInd_PlmnList_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ��ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO);

    NAS_MMC_SaveLastCampedPlmnWithRat(NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMcc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMnc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.enCampPlmnNetRat);


    /* ���פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* ��ǰ�źŸ��� */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());


    /* �ϱ���Ӧ��CS/PS����״̬MSCC_MMC_SERVICE_STATUS_NO_SERVICE */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);
    NAS_MMC_UpdateRegStateSpecPlmnSearch();

    if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
    {
        NAS_MMC_SndMsccPlmnListRejMsg_PlmnList();

        /* ����δ����LIST�������������������б�Ϊ�� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());


        /* �˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ״̬���˳����Ϊ�� */
    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnList())
    {
        NAS_MMC_ProcFsmAbort_PlmnList();

        /* ����δ����LIST�������������������б�Ϊ�� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ��GAS����LIST��������,Ǩ��״̬���ȴ�GAS LIST�����ظ�״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);

    /* ��GMM��������ָʾ */
    NAS_MMC_SndGmmPlmnSchInit();

    /* ��MM��������ָʾ */
    NAS_MMC_SndMmPlmnSchInit();

    /* ���ý�������״̬ */
    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvTiWaitWasSysInfoIndExpired_PlmnList_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitWasSysInfoIndExpired_PlmnList_WaitWasSysInfoInd Enter!");

    /* ���פ��PLMN RAI LAC��Ϣ*/
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* ����פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

    /* ���·���״̬ */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);
    NAS_MMC_UpdateRegStateSpecPlmnSearch();

    /* ״̬���˳����Ϊ�� */
    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnList())
    {
        NAS_MMC_ProcFsmAbort_PlmnList();

        /* ����δ����LIST�������������������б�Ϊ�� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ��WAS����LIST��������,Ǩ��״̬���ȴ�WAS LIST�����ظ�״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

    /* ��GMM��������ָʾ */
    NAS_MMC_SndGmmPlmnSchInit();

    /* ��MM��������ָʾ */
    NAS_MMC_SndMmPlmnSchInit();

    /* ���ý�������״̬ */
    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    return VOS_TRUE;
}



VOS_UINT32  NAS_MMC_RcvTiWaitGasSysInfoIndExpired_PlmnList_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitGasSysInfoIndExpired_PlmnList_WaitGasSysInfoInd Enter!");

    /* ���פ��PLMN RAI LAC��Ϣ*/
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* ����פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

    /* ���·���״̬ */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);
    NAS_MMC_UpdateRegStateSpecPlmnSearch();

    /* ״̬���˳����Ϊ�� */
    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnList())
    {
        NAS_MMC_ProcFsmAbort_PlmnList();

        /* ����δ����LIST�������������������б�Ϊ�� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ��GAS����LIST��������,Ǩ��״̬���ȴ�GAS LIST�����ظ�״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);

    /* ��GMM��������ָʾ */
    NAS_MMC_SndGmmPlmnSchInit();

    /* ��MM��������ָʾ */
    NAS_MMC_SndMmPlmnSchInit();

    /* ���ý�������״̬ */
    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    return VOS_TRUE;
}



VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

    NAS_MMC_SndMsccListSearchCnfMsg_PlmnList();

    /* δ��ʼ��������ʱ�����б�Ϊ��,��¼��ǰע�ᵼ�µĺ���additionֵ��L1 MAIN��
       �յ���·�ͷź����additionֵ�����Ƿ񴥷����� */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

    /* ����ID_MMC_MSCC_PLMN_LIST_ABORT_CNF */
    NAS_MMC_SndMsccPlmnListAbortCnf_PlmnList();

    /* δ��ʼ��������ʱ�����б�Ϊ��,��¼��ǰע�ᵼ�µĺ���additionֵ��L1 MAIN��
       �յ���·�ͷź����additionֵ�����Ƿ񴥷����� */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvGmmPsRegResultInd_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;
    GMMMMC_PS_REG_RESULT_IND_STRU                          *pstPsRegRslt = VOS_NULL_PTR;

    pstPsRegRslt = (GMMMMC_PS_REG_RESULT_IND_STRU*)pstMsg;

    /* �ȴ�RRC��·�ͷ�ʱ���������ѡ���л��Լ�CCO����������ᷢ���ı䣬
       ״̬���˳����յ������ע������Ϣ����Ҫ�жϵ�ǰ������
       �����ı䣬�����ı�������ǰע���� */
    if ( pstPsRegRslt->enNetType != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    /* ����PS��ע����*/
    NAS_MMC_ProcPsRegRslt_PlmnList(pstPsRegRslt);

    /* �����ǰ�ȴ�PS��ע���� */
    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    /* �Ƿ��Ѿ�����CS/PS��ע���� */
    if ( NAS_MMC_WAIT_REG_RESULT_IND_NULL != NAS_MMC_GetWaitRegRsltFlag_PlmnList())
    {
        return VOS_TRUE;
    }

    /* �������ȼ��Ƚϱ���ó�CS/PS�Ĵ������ȼ�����ת��Ϊ״̬����һ����Ϊ */
    enCsAdditionalAction = NAS_MMC_GetCsRegAdditionalAction_PlmnList();
    enPsAdditionalAction = NAS_MMC_GetPsRegAdditionalAction_PlmnList();
    enAdditionalAction   = NAS_MMC_GetPrioAddtionalAction(enCsAdditionalAction, enPsAdditionalAction);

    /* ���CS/PS��Ҫ��������ע�ᣬ��Ҫ�ڴ�״̬�����ȴ�ע���� */
    if (NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT == enAdditionalAction)
    {
        return VOS_TRUE;
    }

    /* ֹͣ�ȴ�ע�����ı�����ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

    if ( VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        /* Ǩ��״̬���ȴ�GU��RRC��·�ͷ� */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_RRC_CONN_REL_IND);

        /* ����������ʱ�� */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL, TI_NAS_MMC_WAIT_RRC_CONN_REL_LEN);

        return VOS_TRUE;
    }

    /* פ��̬��GTLģʽTDΪ��ģʱ��Ҫ֪ͨMM/GMM��������״̬ */
    if (VOS_TRUE == NAS_MMC_IsCurrentTdscdmaMode())
    {
        /* ��GMM��������ָʾ */
        NAS_MMC_SndGmmPlmnSchInit();

        /* ��MM��������ָʾ */
        NAS_MMC_SndMmPlmnSchInit();
    }

    /* ���ݵ�ǰ�Ľ���ģʽ������LIST��������,Ǩ��״̬������������ʱ�� */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_GetCurrNetRatType());

    return VOS_TRUE;
}



VOS_UINT32  NAS_MMC_RcvMmCsRegResultInd_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;
    MMMMC_CS_REG_RESULT_IND_STRU                           *pstCsRegRslt = VOS_NULL_PTR;

    pstCsRegRslt = (MMMMC_CS_REG_RESULT_IND_STRU*)pstMsg;

    /* �ȴ�RRC��·�ͷ�ʱ���������ѡ���л��Լ�CCO����������ᷢ���ı䣬
       ״̬���˳����յ������ע������Ϣ����Ҫ�жϵ�ǰ������
       �����ı䣬�����ı�������ǰע���� */
    if ( pstCsRegRslt->enNetType != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    /* ����CS��ע���� */
    NAS_MMC_ProcCsRegRslt_PlmnList(pstCsRegRslt);

    /* �����ǰ�ȴ�CS��ע���� */
    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_CS);

    /* �Ƿ��Ѿ�����CS/PS��ע���� */
    if ( NAS_MMC_WAIT_REG_RESULT_IND_NULL != NAS_MMC_GetWaitRegRsltFlag_PlmnList() )
    {
        return VOS_TRUE;
    }

    /* �������ȼ��Ƚϱ���ó�CS/PS�Ĵ������ȼ�����ת��Ϊ״̬����һ����Ϊ */
    enCsAdditionalAction = NAS_MMC_GetCsRegAdditionalAction_PlmnList();
    enPsAdditionalAction = NAS_MMC_GetPsRegAdditionalAction_PlmnList();
    enAdditionalAction   = NAS_MMC_GetPrioAddtionalAction(enCsAdditionalAction, enPsAdditionalAction);

    /* ���CS/PS��Ҫ��������ע�ᣬ��Ҫ�ڴ�״̬�����ȴ�ע���� */
    if (NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT == enAdditionalAction)
    {
        return VOS_TRUE;
    }

    /* ֹͣ�ȴ�ע�����ı�����ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

    if ( VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        /* Ǩ��״̬���ȴ�GU��RRC��·�ͷ� */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_RRC_CONN_REL_IND);

        /* ����������ʱ�� */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL, TI_NAS_MMC_WAIT_RRC_CONN_REL_LEN);

        return VOS_TRUE;
    }

    /* פ��̬��GTLģʽTDΪ��ģʱ��Ҫ֪ͨMM/GMM��������״̬ */
    if (VOS_TRUE == NAS_MMC_IsCurrentTdscdmaMode())
    {
        /* ��GMM��������ָʾ */
        NAS_MMC_SndGmmPlmnSchInit();

        /* ��MM��������ָʾ */
        NAS_MMC_SndMmPlmnSchInit();
    }

    /* ���ݵ�ǰ�Ľ���ģʽ������LIST��������,Ǩ��״̬������������ʱ�� */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_GetCurrNetRatType());

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvMmAbortInd_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMMMC_ABORT_IND_STRU               *pstMmAbortInd   = VOS_NULL_PTR;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_GU_ACTION_RSLT_INFO_STRU    stActionRslt;
#endif

    pstMmAbortInd = (MMMMC_ABORT_IND_STRU*)pstMsg;

    /* ���ԭ��ֵ��Ϊ#6���Ҳ�Ϊ#17��ֱ�ӷ��� */
    if ((NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME != pstMmAbortInd->enAbortCause)
     && (NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE != pstMmAbortInd->enAbortCause))
    {
        return VOS_TRUE;
    }

    /* ���ԭ��ֵ#6������CS AdditionΪAnycellפ�� */
    if (NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME == pstMmAbortInd->enAbortCause)
    {
        NAS_MMC_SetCsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL);
    }

#if (FEATURE_ON == FEATURE_LTE)

    /* ��LMM����ID_MMC_LMM_ACTION_RESULT_REQ */
    /* ����ActionRslt��Ϣ�����ΪCN_Rej,������Ϊ����NAS_MML_PROC_MM_ABORT����
       ����ͽ������CS��ԭ��ֵΪAbort����ԭ��ֵ */
    stActionRslt.enProcType     = NAS_MML_PROC_MM_ABORT;
    stActionRslt.enRegRst       = NAS_MML_REG_RESULT_CN_REJ;
    stActionRslt.enReqDomain    = NAS_MMC_REG_DOMAIN_CS;
    stActionRslt.enRstDomain    = NAS_MMC_REG_DOMAIN_CS;
    stActionRslt.enCnCause      = pstMmAbortInd->enAbortCause;
    stActionRslt.ulAttemptCount = 0x0;

    NAS_MMC_SndLmmRegActionResultReq(&stActionRslt);
#endif

    return VOS_TRUE;
}




VOS_UINT32  NAS_MMC_RcvGmmNetworkDetachInd_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMCGMM_NETWORK_DETACH_IND_STRU                         *pstDetachMsg = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;

    pstDetachMsg        = (MMCGMM_NETWORK_DETACH_IND_STRU *)pstMsg;

    /* ����Detach��� */
    enAdditionalAction = NAS_MMC_ProcGmmNetworkDetachInd(pstDetachMsg);

    /* AdditionalAction��Ч������PS����һ���Ķ������� */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_PlmnList(enAdditionalAction);
    }

    /* ���PS��ĵȴ���־ */
    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_PS);

#if   (FEATURE_ON == FEATURE_LTE)
    /* ��LMM����detach�����Ϣ */
    NAS_MMC_SndLmmMtDetachIndActionResultReq(pstDetachMsg->ulDetachType,
                                           (NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16)pstDetachMsg->ulDetachCause);
#endif

    /* ��Ҫ����ע��ʱ������Ҫִ�к����Ķ��� */
    if (NAS_MMC_GMM_NT_DETACH_REATTACH == pstDetachMsg->ulDetachType)
    {
        return VOS_TRUE;
    }

    /* δ����CS/PS�Ľ���������ȴ�ע���� */
    if (NAS_MMC_WAIT_REG_RESULT_IND_NULL != NAS_MMC_GetWaitRegRsltFlag_PlmnList())
    {
        return VOS_TRUE;
    }

    /* �������ȼ��Ƚϱ���ó�CS/PS�Ĵ������ȼ�����ת��Ϊ״̬����һ����Ϊ */
    enCsAdditionalAction = NAS_MMC_GetCsRegAdditionalAction_PlmnList();
    enPsAdditionalAction = NAS_MMC_GetPsRegAdditionalAction_PlmnList();
    enAdditionalAction   = NAS_MMC_GetPrioAddtionalAction(enCsAdditionalAction, enPsAdditionalAction);

    /* ���CS/PS��Ҫ��������ע�ᣬ��Ҫ�ڴ�״̬�����ȴ�ע���� */
    if (NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT == enAdditionalAction)
    {
        return VOS_TRUE;
    }

    /* ֹͣ�ȴ�ע�����ı�����ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

    if ( VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        /* Ǩ��״̬���ȴ�GU��RRC��·�ͷ� */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_RRC_CONN_REL_IND);

        /* ����������ʱ�� */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL, TI_NAS_MMC_WAIT_RRC_CONN_REL_LEN);

        return VOS_TRUE;
    }

    /* פ��̬��GTLģʽTDΪ��ģʱ��Ҫ֪ͨMM/GMM��������״̬ */
    if (VOS_TRUE == NAS_MMC_IsCurrentTdscdmaMode())
    {
        /* ��GMM��������ָʾ */
        NAS_MMC_SndGmmPlmnSchInit();

        /* ��MM��������ָʾ */
        NAS_MMC_SndMmPlmnSchInit();
    }

    /* ���ݵ�ǰ�Ľ���ģʽ������LIST��������,Ǩ��״̬������������ʱ�� */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_GetCurrNetRatType());

    return VOS_TRUE;
}



VOS_UINT32  NAS_MMC_RcvGmmServiceRequestResultInd_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    GMMMMC_SERVICE_REQUEST_RESULT_IND_STRU                 *pstServiceRsltInd = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;

    pstServiceRsltInd = (GMMMMC_SERVICE_REQUEST_RESULT_IND_STRU*)pstMsg;

    if (GMM_MMC_ACTION_RESULT_SUCCESS == pstServiceRsltInd->ulServiceSts)
    {
        /* ����PS��AdditionalAction */
        NAS_MMC_SetPsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON);
    }
    else
    {
        /* �������ʧ�ܣ�������ͬ�ܾ�ԭ��ֵ������PS additional Action */
        enAdditionalAction = NAS_MMC_ProcPsServiceRegFail(pstServiceRsltInd);

        /* AdditionalAction��Ч������PS����һ���Ķ������� */
        if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
        {
            NAS_MMC_SetPsRegAdditionalAction_PlmnList(enAdditionalAction);
        }
    }

    /* ���PS��ĵȴ���־ */
    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    /* ���ע������δ���룬�˳�����, �����ȴ� */
    if (NAS_MMC_WAIT_REG_RESULT_IND_NULL != NAS_MMC_GetWaitRegRsltFlag_PlmnList())
    {
        return VOS_TRUE;
    }

    /* �������ȼ��Ƚϱ���ó�CS/PS�Ĵ������ȼ�����ת��Ϊ״̬����һ����Ϊ */
    enCsAdditionalAction = NAS_MMC_GetCsRegAdditionalAction_PlmnList();
    enPsAdditionalAction = NAS_MMC_GetPsRegAdditionalAction_PlmnList();
    enAdditionalAction   = NAS_MMC_GetPrioAddtionalAction(enCsAdditionalAction, enPsAdditionalAction);

    /* ���CS/PS��Ҫ��������ע�ᣬ��Ҫ�ڴ�״̬�����ȴ�ע���� */
    if (NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT == enAdditionalAction)
    {
        return VOS_TRUE;
    }

    /* ֹͣ�ȴ�ע�����ı�����ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

    if ( VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        /* Ǩ��״̬���ȴ�GU��RRC��·�ͷ� */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_RRC_CONN_REL_IND);

        /* ����������ʱ�� */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL, TI_NAS_MMC_WAIT_RRC_CONN_REL_LEN);

        return VOS_TRUE;
    }

    /* פ��̬��GTLģʽTDΪ��ģʱ��Ҫ֪ͨMM/GMM��������״̬ */
    if (VOS_TRUE == NAS_MMC_IsCurrentTdscdmaMode())
    {
        /* ��GMM��������ָʾ */
        NAS_MMC_SndGmmPlmnSchInit();

        /* ��MM��������ָʾ */
        NAS_MMC_SndMmPlmnSchInit();
    }

    /* ���ݵ�ǰ�Ľ���ģʽ������LIST��������,Ǩ��״̬������������ʱ�� */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_GetCurrNetRatType());

    return VOS_TRUE;
}



VOS_UINT32 NAS_MMC_RcvAreaLostInd_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_AREA_LOST_IND_STRU            *pstAreaLostInd = VOS_NULL_PTR;

    pstAreaLostInd = (RRMM_AREA_LOST_IND_STRU*)pstMsg;
    NAS_MMC_SetSpecRatSearchedTypeByAreaLostInd_PlmnList(NAS_MML_GetCurrNetRatType(), pstAreaLostInd);

    /* ֹͣ�ȴ�ע������Ϣ�Ķ�ʱ��  */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

    NAS_MMC_SaveLastCampedPlmnWithRat(NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMcc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMnc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.enCampPlmnNetRat);


    /* �ϱ���Ӧ��CS/PS����״̬MSCC_MMC_SERVICE_STATUS_NO_SERVICE */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);
    NAS_MMC_UpdateRegStateSpecPlmnSearch();

    /* ���פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* ��ǰ�źŸ��� */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());


    /* ֪ͨMM/GMM���붪��,MM���ͷ�CSҵ�� */
    NAS_MMC_SndMmCoverageLostInd();
    NAS_MMC_SndGmmCoverageLostInd();

    if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
    {
        NAS_MMC_SndMsccPlmnListRejMsg_PlmnList();

        /* ����list����ʧ����Ϣ */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());
        /* �˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ��WAS/GAS����LIST��������,Ǩ��״̬���ȴ�WAS/GAS LIST�����ظ�״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_GetCurrNetRatType());

    /* ��GMM��������ָʾ */
    NAS_MMC_SndGmmPlmnSchInit();

    /* ��MM��������ָʾ */
    NAS_MMC_SndMmPlmnSchInit();

    /* ���ý�������״̬ */
    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvRrMmSysInfoInd_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
   /* ����WASϵͳ��Ϣ */
    NAS_MMC_ProcWasSysInfo_PlmnList(pstMsg);

    /* ���µ�ǰ�ȴ�CSPS��ע���� */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_CS);
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvGrrMmSysInfoInd_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����յ�GAS��ϵͳ��Ϣ����ĿǰUtran��Enable��������Disable Utran */
    NAS_MMC_RcvGasSysInfoSetUtranCapabilityStatus();

    /* ����GASϵͳ��Ϣ */
    NAS_MMC_ProcGasSysInfo_PlmnList(pstMsg);

    /* ���µ�ǰ�ȴ�CSPS��ע���� */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_CS);
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvRrMmSuspendInd_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_IND_ST             *pstSuspendMsg = VOS_NULL_PTR;

    pstSuspendMsg = (RRMM_SUSPEND_IND_ST*)pstMsg;

    /* ���ݲ�ͬ�Ĺ���ԭ��ֵ��������ͬ��״̬�� */
    switch (pstSuspendMsg->ucSuspendCause)
    {
        case MMC_SUSPEND_CAUSE_CELLRESELECT:
        case MMC_SUSPEND_CAUSE_REDIRECTION:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_CELLRESEL);
            NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                                     NAS_MML_GetSimPsRegStatus());
            break;

        case MMC_SUSPEND_CAUSE_PLMNSEARCH:

            /* �����㷢�͹���ʧ�� */
            NAS_MMC_SndAsSuspendRsp(RRC_NAS_SUSPEND_FAILURE, pstSuspendMsg->MsgHeader.ulSenderPid);

            /* ���·���״̬ */
            NAS_MMC_SetCsServiceStatus(NAS_MMC_NO_SERVICE);

            NAS_MMC_SetPsServiceStatus(NAS_MMC_NO_SERVICE);

            /* ��Ҫ�����ͷ���· */
            NAS_MMC_SndMmRelReq();

            NAS_MMC_SndGmmRelReq();

            NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

            /* Ǩ��״̬���ȴ�RRC��·�ͷ� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_RRC_CONN_REL_IND);

            /* ����������ʱ�� */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL, TI_NAS_MMC_WAIT_RRC_CONN_REL_LEN);

            break;
        case MMC_SUSPEND_CAUSE_HANDOVER:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_HO);
            NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                                     NAS_MML_GetSimPsRegStatus());
            break;

        case MMC_SUSPEND_CAUSE_CELLCHANGE:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_CCO);
            NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                                     NAS_MML_GetSimPsRegStatus());
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmSuspendInd_PlmnList_WaitCsPsRegRsltInd:Unexpected suspend type!");
            break;
    }

    return VOS_TRUE;
}




VOS_UINT32  NAS_MMC_RcvMmcMmcSuspendRslt_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��ѡ��ǰ���뼼���Ѿ��ı䣬��Ҫ���³�ʼ�������Ľ��뼼�����ȼ� */
#if (FEATURE_ON == FEATURE_CSG)
    if (VOS_TRUE == NAS_MMC_IsCsgList_PlmnList())
    {
        NAS_MMC_InitCsgListSearchRatInfo_PlmnList();
    }
    else
#endif
    {
        NAS_MMC_InitSearchRatInfo_PlmnList();
    }


    NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                             NAS_MML_GetSimPsRegStatus());

    if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
    {
        /* ֹͣ������ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

        NAS_MMC_SndMsccPlmnListRejMsg_PlmnList();

        /* ����δ����LIST�������������������б�Ϊ�� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());


        /* �˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

#if (FEATURE_ON == FEATURE_LTE)
    /* �жϵ�ǰ����ģʽ */
    if ( NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        /* ֹͣ������ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

        /* IDLE̬�´�GU��ϵͳ��LTE��,LTE�¿��ܷ���ע��򲻷���ע��
           �����MMC�ϱ�ע���� */
        /* ����CSPS��AdditionalAction */
        NAS_MMC_SetCsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_BUTT);
        NAS_MMC_SetPsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_BUTT);

        /* ���µ�ǰ�ȴ�EPS��ע���� */
        NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();

        NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_PS);

#if (FEATURE_ON == FEATURE_IMS)
        NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_IMS);
#endif

        /* Ǩ��״̬���ȴ�L�µ�EPSע���� */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_EPS_REG_IND);

        /* ����������ʱ�� */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_REG_IND, TI_NAS_MMC_WAIT_EPS_REG_IND_LEN);

        return VOS_TRUE;
    }
#endif

    /* �����ȴ�ע���� */
    return VOS_TRUE;
}



VOS_UINT32  NAS_MMC_RcvTiWaitCsPsRegRsltIndExpired_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitCsPsRegRsltIndExpired_PlmnList_WaitCsPsRegRsltInd Enter");

    /* ����ȴ�ע������� */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();

    /* ������������ �����ȴ�RRC�����ͷ� */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        /* Ǩ��״̬���ȴ�GU��RRC��·�ͷ� */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_RRC_CONN_REL_IND);

        /* ����������ʱ�� */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL, TI_NAS_MMC_WAIT_RRC_CONN_REL_LEN);

        return VOS_TRUE;
    }

    /* פ��̬��GTLģʽTDΪ��ģʱ��Ҫ֪ͨMM/GMM��������״̬ */
    if (VOS_TRUE == NAS_MMC_IsCurrentTdscdmaMode())
    {
        /* ��GMM��������ָʾ */
        NAS_MMC_SndGmmPlmnSchInit();

        /* ��MM��������ָʾ */
        NAS_MMC_SndMmPlmnSchInit();
    }

    /* ���ݵ�ǰ�Ľ���ģʽ������LIST��������,Ǩ��״̬������������ʱ�� */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_GetCurrNetRatType());

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvRrmmLimitServiceCampInd_PlmnList_WaitRrcConnRelInd(
        VOS_UINT32                          ulEventType,
        struct MsgCB                       *pstMsg
)
{
    return NAS_MMC_RcvRrmmLimitServiceCampInd_PlmnList(ulEventType, pstMsg);
}


VOS_UINT32  NAS_MMC_RcvRrmmLimitServiceCampInd_PlmnList_WaitCsPsRegRsltInd(
        VOS_UINT32                          ulEventType,
        struct MsgCB                       *pstMsg
)
{
    return NAS_MMC_RcvRrmmLimitServiceCampInd_PlmnList(ulEventType, pstMsg);
}


VOS_UINT32 NAS_MMC_RcvMsccImsVoiceCapInd_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* GU���յ�IMS VOICE�Ƿ����Ŀǰ�ݲ�����
       ������ϵͳ�������յ���IMS VOICE�Ƿ���õĳ������ڿ�������ϵͳ���µ�IMS VOICE
       ������,��ʱ��������disable Lģ��׼ȷ,�ݲ����Ǹó��� */

    return VOS_TRUE;
}



VOS_UINT32  NAS_MMC_RcvRrmmLimitServiceCampInd_PlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_LIMIT_SERVICE_CAMP_IND_STRU        *pstRrmmLimitCampOnMsg = VOS_NULL_PTR;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU    *pastIntraPlmnSrchInfo = VOS_NULL_PTR;
    NAS_MMC_PLMN_LIST_SEARCH_CTRL_STRU      *pstSearchRatInfo   = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU              *pstRatPrioList     = VOS_NULL_PTR;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU    *pstListInfo        = VOS_NULL_PTR;
    VOS_UINT8                                ucRatCnt;

    pstRrmmLimitCampOnMsg = (RRMM_LIMIT_SERVICE_CAMP_IND_STRU *)pstMsg;

    pstSearchRatInfo = NAS_MMC_GetSearchCtrlInfo_PlmnList();
    pstRatPrioList   = NAS_MML_GetMsPrioRatList();
    pstListInfo      = NAS_MMC_GetSearchedPlmnListInfo_PlmnList();

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

    pastIntraPlmnSrchInfo = (NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                                             sizeof(NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU) * NAS_MML_MAX_RAT_NUM);
    /* memory alloc fail */
    if (VOS_NULL_PTR == pastIntraPlmnSrchInfo)
    {
        return VOS_TRUE;
    }

    /* �����е�RAT������Ϊ�Ѿ����� */
    for (ucRatCnt = 0; ucRatCnt < pstRatPrioList->ucRatNum; ucRatCnt++)
    {
        pstListInfo[ucRatCnt].enRatType = pstSearchRatInfo[ucRatCnt].enRat;

        pstSearchRatInfo[ucRatCnt].ucSearchedFlag = VOS_TRUE;
    }

    /* ���������б� */
    NAS_MMC_UpdateSearchedPlmnListInfo_PlmnList(&(pstRrmmLimitCampOnMsg->stPlmnIdList));

    /* ��ת�����PLMN��Ϣ���浽���ر����� */
    PS_MEM_CPY(pastIntraPlmnSrchInfo, pstListInfo, sizeof(NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU) * NAS_MML_MAX_RAT_NUM);


    /* ɾ���б��н�ֹ��PLMN */
    NAS_MMC_DelForbPlmnFromAsSrchedPlmnList(pastIntraPlmnSrchInfo);

    /* �ֶ�����ģʽ��ɾ�����û�ָ����PLMN */
    NAS_MMC_DelNotUserSpecPlmnFromSrchedPlmnList(pastIntraPlmnSrchInfo);

    /* ��ά�ɲ���Ϣ���� */
    NAS_MMC_LogAsPlmnList(pastIntraPlmnSrchInfo);

    /* �û�LIST���� */
    if ( VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
    {
        /* �����������������������ϱ���MSCC */
        NAS_MMC_SndMsccPlmnListCnf_PlmnList();


        /* �˳�״̬�� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_SUCC,
                                VOS_TRUE,
                                pastIntraPlmnSrchInfo,
                                NAS_MMC_GetRegRsltInfo_PlmnList());
        NAS_MMC_FSM_QuitFsmL2();

        PS_MEM_FREE(WUEPS_PID_MMC, pastIntraPlmnSrchInfo);
        return VOS_TRUE;
    }

#if (FEATURE_ON == FEATURE_CSG)
    if (VOS_TRUE == NAS_MMC_IsCsgList_PlmnList())
    {
        /* �����������������������ϱ���MSCC */
        NAS_MMC_SndMsccCsgListSearchCnf_PlmnList();

        /* �˳�״̬�� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_SUCC,
                                VOS_TRUE,
                                pastIntraPlmnSrchInfo,
                                NAS_MMC_GetRegRsltInfo_PlmnList());
        NAS_MMC_FSM_QuitFsmL2();

        PS_MEM_FREE(WUEPS_PID_MMC, pastIntraPlmnSrchInfo);
        return VOS_TRUE;
    }
#endif


    /* ��Ҫ�������� */
    if (VOS_TRUE == NAS_MMC_IsExistAvailPlmnInSearchedPlmnList(pastIntraPlmnSrchInfo))
    {
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_SUCC,
                                VOS_TRUE,
                                pastIntraPlmnSrchInfo,
                                NAS_MMC_GetRegRsltInfo_PlmnList());


        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
    }

    PS_MEM_FREE(WUEPS_PID_MMC, pastIntraPlmnSrchInfo);

    return VOS_TRUE;
}



VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ�ȴ�WAS��������ı�����ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_LIST_CNF);

    /* ��¼״̬���˳���� */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ��WAS����ֹͣ��������,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatPlmnSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

    return VOS_TRUE;
}



VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ�ȴ�WAS��������ı�����ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_LIST_CNF);

    /* ��¼״̬���˳���� */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ����֪ͨMSCC�ظ���� */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    /* ��WAS����ֹͣ��������,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatPlmnSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvRrMmPlmnSrchCnf_PlmnList_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU          *pstPlmnSearchcnf = VOS_NULL_PTR;

    pstPlmnSearchcnf = (RRMM_PLMN_SEARCH_CNF_STRU*)pstMsg;

    /* ֹͣ�ȴ�WAS�����ظ��ı�����ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_LIST_CNF);

    /* ����PLMN LIST�Ľ�� */
    switch (pstPlmnSearchcnf->ulSearchRlt)
    {
        case RRC_PLMN_SEARCH_RLT_USER_LIST_REJ:
        case RRC_PLMN_SEARCH_RLT_USER_LIST:
        case RRC_PLMN_SEARCH_RLT_USER_LIST_FAIL:
        case RRC_PLMN_SEARCH_RLT_USER_LIST_NO_RF:

            NAS_MMC_ProcRrmmSearchCnf_UserPlmnListSearch_PlmnList(pstPlmnSearchcnf);
            break;

        case RRC_PLMN_SEARCH_RLT_INTER_LIST_REJ:
        case RRC_PLMN_SEARCH_RLT_INTER_LIST_FAIL:
        case RRC_PLMN_SEARCH_RLT_INTER_LIST_SUCC:
        case RRC_PLMN_SEARCH_RLT_INTER_LIST_NO_RF:
        case RRC_PLMN_SEARCH_RLT_INTER_LIST_PREF_BAND_REJ:
        case RRC_PLMN_SEARCH_RLT_INTER_LIST_PREF_BAND_FAIL:
        case RRC_PLMN_SEARCH_RLT_INTER_LIST_PREF_BAND_SUCC:
        case RRC_PLMN_SEARCH_RLT_INTER_LIST_PREF_BAND_NO_RF:

            NAS_MMC_ProcRrmmSearchCnf_InterPlmnListSearch_PlmnList(pstPlmnSearchcnf);
            break;

        default:
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmPlmnSrchCnf_PlmnList_WaitWasPlmnSearchCnf:UNEXPECTED SEARCH RSLT!!!");
            break;
    }

    return VOS_TRUE;
}



VOS_UINT32  NAS_MMC_RcvRrMmRelInd_PlmnList_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_REL_IND_STRU                  *pstRrmmRelIndMsg    = VOS_NULL_PTR;
    VOS_UINT32                          ulIsPrefbandListScene;
    VOS_UINT32                          ulIsFullbandListScene;

    ulIsPrefbandListScene = NAS_MMC_IsPrefBandListSearchScene_PlmnList();
    ulIsFullbandListScene = NAS_MMC_IsFullBandListSearchScene_PlmnList();

    pstRrmmRelIndMsg = (RRMM_REL_IND_STRU *)pstMsg;

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmRelInd_PlmnList_WaitWasPlmnSearchCnf Enter!");

    /* �����ж�ԭ��ֵ */

    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_LIST_CNF);

    if (RRC_REL_CAUSE_NO_RF == pstRrmmRelIndMsg->ulRelCause)
    {
        NAS_MMC_ProcNoRf_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

        return VOS_TRUE;
    }

    /* ����״̬���˳���� */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());

    /* ����5S�����Գ���LIST������ʱ�� */
    if ( VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
    {
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST, TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST_LEN);
    }
    else
    {
        /* prefband list �� fullband list������������Ҫ����TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST��ʱ�� */
        if ((VOS_FALSE == ulIsPrefbandListScene)
         && (VOS_FALSE == ulIsFullbandListScene))
        {
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST, TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST_LEN);
        }
    }

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();


    return VOS_TRUE;
}



VOS_UINT32  NAS_MMC_RcvRrMmSysInfoInd_PlmnList_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����פ����Ϣ����ת��ϵͳ��Ϣ */
    NAS_MMC_ProcWasSysInfo_PlmnList(pstMsg);

    /* ��Ǩ��״̬ */
    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvRrMmAreaLostInd_PlmnList_WaitAsPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_AREA_LOST_IND_STRU            *pstAreaLostInd = VOS_NULL_PTR;

    pstAreaLostInd = (RRMM_AREA_LOST_IND_STRU*)pstMsg;
    NAS_MMC_SetSpecRatSearchedTypeByAreaLostInd_PlmnList(NAS_MML_GetCurrNetRatType(), pstAreaLostInd);

    NAS_MMC_SaveLastCampedPlmnWithRat(NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMcc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMnc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.enCampPlmnNetRat);


     /* ���פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* ��ǰ�źŸ��� */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    /* ��MM/GMM/TAF�������������� */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();

    /* �ϱ���Ӧ��CS/PS����״̬MSCC_MMC_SERVICE_STATUS_NO_SERVICE */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);
    NAS_MMC_UpdateRegStateSpecPlmnSearch();

    /* ���·���״̬ */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );

    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    return VOS_TRUE;
}



VOS_UINT32 NAS_MMC_RcvMmCsRegResultInd_PlmnList_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMMMC_CS_REG_RESULT_IND_STRU       *pstCsRegRslt = VOS_NULL_PTR;

    pstCsRegRslt = (MMMMC_CS_REG_RESULT_IND_STRU*)pstMsg;

    /* �ȴ�RRC��·�ͷ�ʱ���������ѡ���л��Լ�CCO����������ᷢ���ı䣬
       ״̬���˳����յ������ע������Ϣ����Ҫ�жϵ�ǰ������
       �����ı䣬�����ı�������ǰע���� */
    if ( pstCsRegRslt->enNetType != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    /* ����CS��ע���� */
    NAS_MMC_ProcCsRegRslt_PlmnList(pstCsRegRslt);

    /* ��Ǩ��״̬ */
    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvGmmPsRegResultInd_PlmnList_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    GMMMMC_PS_REG_RESULT_IND_STRU      *pstPsRegRslt = VOS_NULL_PTR;

    pstPsRegRslt = (GMMMMC_PS_REG_RESULT_IND_STRU*)pstMsg;

    /* �ȴ�RRC��·�ͷ�ʱ���������ѡ���л��Լ�CCO����������ᷢ���ı䣬
       ״̬���˳����յ������ע������Ϣ����Ҫ�жϵ�ǰ������
       �����ı䣬�����ı�������ǰע���� */
    if ( pstPsRegRslt->enNetType != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    /* ����PS��ע����*/
    NAS_MMC_ProcPsRegRslt_PlmnList(pstPsRegRslt);

    /* ��Ǩ��״̬ */
    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvSearchedPlmnInfoInd_PlmnList_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SEARCHED_PLMN_INFO_IND_STRU   *pstSearchedPlmnInfoMsg = VOS_NULL_PTR;
    RRC_PLMN_ID_LIST_STRU              *pstRrcPlmnList         = VOS_NULL_PTR;
    VOS_UINT32                          ulIsNeedStopPlmnListFlg;
    NAS_MML_PLMN_WITH_RAT_STRU          stAbortPlmn;

    NAS_MEM_SET_S(&stAbortPlmn, sizeof(NAS_MML_PLMN_WITH_RAT_STRU), 0x0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    pstSearchedPlmnInfoMsg = (RRMM_SEARCHED_PLMN_INFO_IND_STRU *)pstMsg;

    pstRrcPlmnList = (RRC_PLMN_ID_LIST_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                   sizeof(RRC_PLMN_ID_LIST_STRU));

    if (VOS_NULL_PTR == pstRrcPlmnList)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvSearchedPlmnInfoInd_PlmnList_WaitWasPlmnSearchCnf:ERROR: Memory Alloc Error");
        return VOS_TRUE;
    }

    PS_MEM_SET(pstRrcPlmnList, 0x00, sizeof(RRC_PLMN_ID_LIST_STRU));

    ulIsNeedStopPlmnListFlg = VOS_FALSE;

    /* ����������plmnת����RRC_PLMN_ID_LIST_STRU��ʽ */
    NAS_MMC_ConvertRrmmSearchedPlmnToRrcPlmnList(pstSearchedPlmnInfoMsg, pstRrcPlmnList);

    /* ��ת����ʽ���plmn��Ϣ������Searched Plmn List�� */
    NAS_MMC_UpdateSearchedPlmnListInfo_PlmnList(pstRrcPlmnList);

    /* �ж��Ƿ���Ҫ��ϵ�ǰ��list�� */
    ulIsNeedStopPlmnListFlg = NAS_MMC_IsNeedStopPlmnListSearchRcvRrcSearchedPlmnInfoInd_PlmnList(pstSearchedPlmnInfoMsg, &stAbortPlmn);

    if (VOS_TRUE == ulIsNeedStopPlmnListFlg)
    {
        /* ���ݱ�����������ģʽ�����������ͱ�ʶ������syscfg:L->W->G����ǰ������W�����磬
           ��LģucPrefBandSearchedFlg��ucSpecSearchedFlg������������Ϊ�Ѿ�������,W G����Ϊδ������ */
        NAS_MMC_UpdateSearchedTypeStatusBySearchedPlmnInfoInd_PlmnList(pstSearchedPlmnInfoMsg);

        /* ������Ҫ��ϱ�־ucAbortBySearchedPlmnFlgΪtrue */
        NAS_MMC_SetAbortBySearchedPlmnFlg_PlmnList(VOS_TRUE);

        /* ��stAbortPlmn��¼��������ѡ��״̬���и���stAbortPlmn��MCC������������ */
        NAS_MMC_SetAbortListSearchPlmn(&stAbortPlmn);

        /* ֹͣ������ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_LIST_CNF);

        /* ����ֹͣ��������Ǩ״̬������ʱ�� */
        NAS_MMC_SndSpecRatPlmnSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);
    }

    PS_MEM_FREE(WUEPS_PID_MMC, pstRrcPlmnList);
    return VOS_TRUE;
}



VOS_UINT32 NAS_MMC_RcvSearchedPlmnInfoInd_PlmnList_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SEARCHED_PLMN_INFO_IND_STRU   *pstSearchedPlmnInfoMsg = VOS_NULL_PTR;
    RRC_PLMN_ID_LIST_STRU              *pstRrcPlmnList;
    VOS_UINT32                          ulIsNeedStopPlmnListFlg;
    NAS_MML_PLMN_WITH_RAT_STRU          stAbortPlmn;

    NAS_MEM_SET_S(&stAbortPlmn, sizeof(NAS_MML_PLMN_WITH_RAT_STRU), 0x0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    pstSearchedPlmnInfoMsg = (RRMM_SEARCHED_PLMN_INFO_IND_STRU *)pstMsg;

    pstRrcPlmnList = (RRC_PLMN_ID_LIST_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                   sizeof(RRC_PLMN_ID_LIST_STRU));

    if (VOS_NULL_PTR == pstRrcPlmnList)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvSearchedPlmnInfoInd_PlmnList_WaitGasPlmnSearchCnf:ERROR: Memory Alloc Error");
        return VOS_TRUE;
    }

    PS_MEM_SET(pstRrcPlmnList, 0x00, sizeof(RRC_PLMN_ID_LIST_STRU));

    ulIsNeedStopPlmnListFlg = VOS_FALSE;

    /* ����������plmnת����RRC_PLMN_ID_LIST_STRU��ʽ */
    NAS_MMC_ConvertRrmmSearchedPlmnToRrcPlmnList(pstSearchedPlmnInfoMsg, pstRrcPlmnList);

    /* ��ת����ʽ���plmn��Ϣ������Searched Plmn List�� */
    NAS_MMC_UpdateSearchedPlmnListInfo_PlmnList(pstRrcPlmnList);

    /* �ж��Ƿ���Ҫ��ϵ�ǰ��list�� */
    ulIsNeedStopPlmnListFlg = NAS_MMC_IsNeedStopPlmnListSearchRcvRrcSearchedPlmnInfoInd_PlmnList(pstSearchedPlmnInfoMsg, &stAbortPlmn);

    if (VOS_TRUE == ulIsNeedStopPlmnListFlg)
    {
        /* ���ݱ�����������ģʽ�����������ͱ�ʶ������syscfg:L->W->G����ǰ������W�����磬
           ��LģucPrefBandSearchedFlg��ucSpecSearchedFlg������������Ϊ�Ѿ�������,W G����Ϊδ������ */
        NAS_MMC_UpdateSearchedTypeStatusBySearchedPlmnInfoInd_PlmnList(pstSearchedPlmnInfoMsg);

        /* ������Ҫ��ϱ�־ucAbortBySearchedPlmnFlgΪtrue */
        NAS_MMC_SetAbortBySearchedPlmnFlg_PlmnList(VOS_TRUE);

        /* ��stAbortPlmn��¼��������ѡ��״̬���и���stAbortPlmn��MCC������������ */
        NAS_MMC_SetAbortListSearchPlmn(&stAbortPlmn);

        /* ֹͣ������ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_LIST_CNF);

        /* ����ֹͣ��������Ǩ״̬������ʱ�� */
        NAS_MMC_SndSpecRatPlmnSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);

    }

    PS_MEM_FREE(WUEPS_PID_MMC, pstRrcPlmnList);
    return VOS_TRUE;
}



VOS_UINT32  NAS_MMC_RcvTiWaitWasPlmnListCnfExpired_PlmnList_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{


    /* LIST���������У����������ϱ�RRMM_NOT_CAMP_ON����ʱ��Ҫ���ݵ�ǰפ��״̬����RAT��������� */
    if (NAS_MMC_AS_CELL_CAMP_ON == NAS_MMC_GetAsCellCampOn())
    {
        /* ������ģRAT��������� */

#if (FEATURE_ON == FEATURE_LTE)

        NAS_MMC_SetSearchedFlag_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

#endif

        NAS_MMC_SetSearchedFlag_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

        NAS_MMC_SetSearchedFlag_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);
    }
    else
    {
        /* ���µ�ǰRAT��������� */
        NAS_MMC_SetSearchedFlag_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);
    }

    /* ��WAS����ֹͣ��������,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatPlmnSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

    return VOS_TRUE;
}



VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ�ȴ�GAS��������ı�����ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_LIST_CNF);

    /* ��¼״̬���˳���� */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ��GAS����ֹͣ��������,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatPlmnSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ�ȴ�GAS��������ı�����ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_LIST_CNF);

    /* ��¼״̬���˳���� */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ����֪ͨMSCC�ظ���� */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    /* ��GAS����ֹͣ��������,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatPlmnSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvRrMmPlmnSrchCnf_PlmnList_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU          *pstPlmnSrchcnf = VOS_NULL_PTR;

    pstPlmnSrchcnf = (RRMM_PLMN_SEARCH_CNF_STRU*)pstMsg;

    /* ֹͣ�ȴ�GAS�����ظ��ı�����ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_LIST_CNF);

    /* ����PLMN LIST�Ľ�� */
    switch (pstPlmnSrchcnf->ulSearchRlt)
    {
        case RRC_PLMN_SEARCH_RLT_USER_LIST_REJ:
        case RRC_PLMN_SEARCH_RLT_USER_LIST:
        case RRC_PLMN_SEARCH_RLT_USER_LIST_FAIL:
        case RRC_PLMN_SEARCH_RLT_USER_LIST_NO_RF:

            NAS_MMC_ProcRrmmSearchCnf_UserPlmnListSearch_PlmnList(pstPlmnSrchcnf);
            break;


        case RRC_PLMN_SEARCH_RLT_INTER_LIST_REJ:
        case RRC_PLMN_SEARCH_RLT_INTER_LIST_FAIL:
        case RRC_PLMN_SEARCH_RLT_INTER_LIST_SUCC:
        case RRC_PLMN_SEARCH_RLT_INTER_LIST_NO_RF:
        case RRC_PLMN_SEARCH_RLT_INTER_LIST_PREF_BAND_REJ:
        case RRC_PLMN_SEARCH_RLT_INTER_LIST_PREF_BAND_FAIL:
        case RRC_PLMN_SEARCH_RLT_INTER_LIST_PREF_BAND_SUCC:
        case RRC_PLMN_SEARCH_RLT_INTER_LIST_PREF_BAND_NO_RF:

            NAS_MMC_ProcRrmmSearchCnf_InterPlmnListSearch_PlmnList(pstPlmnSrchcnf);
            break;

        default:
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmPlmnSrchCnf_PlmnList_WaitGasPlmnSearchCnf:UNEXPECTED SEARCH RSLT!!!");
            break;
    }

    return VOS_TRUE;
}



VOS_UINT32  NAS_MMC_RcvGrrMmSysInfoInd_PlmnList_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����յ�GAS��ϵͳ��Ϣ����ĿǰUtran��Enable��������Disable Utran */
    NAS_MMC_RcvGasSysInfoSetUtranCapabilityStatus();

    /* ����פ����Ϣ����ת��ϵͳ��Ϣ */
    NAS_MMC_ProcGasSysInfo_PlmnList(pstMsg);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvMmCsRegResultInd_PlmnList_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMMMC_CS_REG_RESULT_IND_STRU       *pstCsRegRslt = VOS_NULL_PTR;

    pstCsRegRslt = (MMMMC_CS_REG_RESULT_IND_STRU*)pstMsg;

    /* �ȴ�RRC��·�ͷ�ʱ���������ѡ���л��Լ�CCO����������ᷢ���ı䣬
       ״̬���˳����յ������ע������Ϣ����Ҫ�жϵ�ǰ������
       �����ı䣬�����ı�������ǰע���� */
    if ( pstCsRegRslt->enNetType != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    /* ����CS��ע���� */
    NAS_MMC_ProcCsRegRslt_PlmnList(pstCsRegRslt);

    /* ��Ǩ��״̬ */
    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvGmmPsRegResultInd_PlmnList_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    GMMMMC_PS_REG_RESULT_IND_STRU      *pstPsRegRslt = VOS_NULL_PTR;

    pstPsRegRslt = (GMMMMC_PS_REG_RESULT_IND_STRU*)pstMsg;

    /* �ȴ�RRC��·�ͷ�ʱ���������ѡ���л��Լ�CCO����������ᷢ���ı䣬
       ״̬���˳����յ������ע������Ϣ����Ҫ�жϵ�ǰ������
       �����ı䣬�����ı�������ǰע���� */
    if ( pstPsRegRslt->enNetType != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    /* ����PS��ע����*/
    NAS_MMC_ProcPsRegRslt_PlmnList(pstPsRegRslt);

    /* ��Ǩ��״̬ */
    return VOS_TRUE;
}



VOS_UINT32  NAS_MMC_RcvTiWaitGasPlmnListCnfExpired_PlmnList_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* LIST���������У����������ϱ�RRMM_NOT_CAMP_ON����ʱ��Ҫ���ݵ�ǰפ��״̬����RAT��������� */
    if (NAS_MMC_AS_CELL_CAMP_ON == NAS_MMC_GetAsCellCampOn())
    {
        /* ������ģRAT��������� */

#if (FEATURE_ON == FEATURE_LTE)

        NAS_MMC_SetSearchedFlag_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

#endif

        NAS_MMC_SetSearchedFlag_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

        NAS_MMC_SetSearchedFlag_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);
    }
    else
    {
        /* ���µ�ǰRAT��������� */
        NAS_MMC_SetSearchedFlag_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);
    }

    /* ��GAS����ֹͣ��������,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatPlmnSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);

    return VOS_TRUE;
}



VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼��Ҫ��ֹ��ǰ״̬����־ */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼��Ҫ��ֹ��ǰ״̬����־ */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ����֪ͨMSCC�ظ���� */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvRrMmSuspendCnf_PlmnList_WaitWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_CNF_ST                *pstRrmmSuspendCnf = VOS_NULL_PTR;

    pstRrmmSuspendCnf  = (RRMM_SUSPEND_CNF_ST*)pstMsg;

    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF);

    /* ��������ظ���� */
    NAS_MMC_ProcRrmmSuspendCnf_PlmnList(pstRrmmSuspendCnf);

    return VOS_TRUE;
}



VOS_UINT32  NAS_MMC_RcvTiWaitWasSuspendCnfExpired_PlmnList_WaitWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat      = NAS_MML_GetCurrNetRatType();

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitWasSuspendCnfExpired_PlmnList_WaitWasSuspendCnf: Timer Expired");

    /* ���ɻָ����ϣ���λ */

    if ( (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
      && (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat) )
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_WAS_SUSPEND_CNF_EXPIRED);
    }
    else
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_TD_SUSPEND_CNF_EXPIRED);
    }

    return VOS_TRUE;
}



VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼��Ҫ��ֹ��ǰ״̬����־ */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼��Ҫ��ֹ��ǰ״̬����־ */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ����֪ͨMSCC�ظ���� */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvRrMmSuspendCnf_PlmnList_WaitGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_CNF_ST                *pstRrmmSuspendCnf = VOS_NULL_PTR;

    pstRrmmSuspendCnf  = (RRMM_SUSPEND_CNF_ST*)pstMsg;

    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF);

    /* ��������ظ���� */
    NAS_MMC_ProcRrmmSuspendCnf_PlmnList(pstRrmmSuspendCnf);

    return VOS_TRUE;
}



VOS_UINT32  NAS_MMC_RcvTiWaitGasSuspendCnfExpired_PlmnList_WaitGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitGasSuspendCnfExpired_PlmnList_WaitGasSuspendCnf: Timer Expired");

    /* ���ɻָ����ϣ���λ */

    NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_GAS_SUSPEND_CNF_EXPIRED);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvRrMmPlmnSrchStopCnf_PlmnList_WaitWasPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF);

    /* ��������ֹͣ�ظ���� */
    NAS_MMC_ProcRrmmPlmnSearchStopCnf_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

    /* ��Ǩ��״̬ */
    return VOS_TRUE;
}



VOS_UINT32  NAS_MMC_RcvRrMmSysInfoInd_PlmnList_WaitWasPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����פ����Ϣ����ת��ϵͳ��Ϣ */
    NAS_MMC_ProcWasSysInfo_PlmnList(pstMsg);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitWasPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼��Ҫ��ֹ��ǰ״̬����־ */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortFsmMsg_PlmnList_WaitWasPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼��Ҫ��ֹ��ǰ״̬����־ */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ����֪ͨMSCC�ظ���� */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvRrMmPlmnSrchCnf_PlmnList_WaitWasPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU          *pstPlmnSrchCnf = VOS_NULL_PTR;

    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;
    VOS_UINT32                          ulIndex;

    pstPlmnSrchCnf = (RRMM_PLMN_SEARCH_CNF_STRU*)pstMsg;

    switch(pstPlmnSrchCnf->ulSearchRlt)
    {
        /* LIST�����ظ���ֹͣ�����Գ�,NO RFʱֱ���˳�LIST�������� */
        case RRC_PLMN_SEARCH_RLT_USER_LIST_NO_RF:
        case RRC_PLMN_SEARCH_RLT_INTER_LIST_NO_RF:
        case RRC_PLMN_SEARCH_RLT_INTER_LIST_PREF_BAND_NO_RF:

            /* ֹͣ������ʱ�� */
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF);

            NAS_MMC_ProcNoRf_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);
            return VOS_TRUE;

        /* ֻ���������ɹ�ʱ�Ž��д��� */
        case RRC_PLMN_SEARCH_RLT_USER_LIST:
        case RRC_PLMN_SEARCH_RLT_INTER_LIST_SUCC:
        case RRC_PLMN_SEARCH_RLT_INTER_LIST_PREF_BAND_SUCC:
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmPlmnSrchCnf_PlmnList_WaitWasPlmnSearchStopCnf: Unexpected List Search Result!");
            return VOS_TRUE;
    }

    /* LIST����������,��Ҫ���ݵ�ǰ�����Я�����Ѿ��������Ľ��뼼����Ϣ����RAT��������� */
    for ( ulIndex = 0; ulIndex < NAS_RRC_MAX_RAT_NUM; ulIndex++)
    {
        if ( RRC_NAS_RAT_LIST_SEARCH_CMPL == pstPlmnSrchCnf->astSearchRatInfo[ulIndex].enListSearchRlt)
        {
            /*��RRC�Ľ��뼼��ת����MML����ĸ�ʽ��Ȼ����� */
            NAS_MMC_ConvertRrcRatToNasFormat(pstPlmnSrchCnf->astSearchRatInfo[ulIndex].enRat, &enRat);

            NAS_MMC_InitSpecRatSearchedPlmnListInfo_PlmnList(enRat);

            NAS_MMC_SetSearchedFlag_PlmnList(enRat);

            NAS_MMC_SetSpecRatSearchedTypeByPlmnSearchCnfSucc_PlmnList(enRat, pstPlmnSrchCnf->ulSearchRlt);
        }
    }

    /* ��PLMN INFO IND��Я�������Ѹ��£��յ�PLMN CNF����CNFЯ��������Ϊ׼ */
    /* ���������б� */
    NAS_MMC_UpdateSearchedPlmnListInfo_PlmnList(&(pstPlmnSrchCnf->PlmnIdList));

    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF);

    /* ��������ֹͣ�ظ���� */
    NAS_MMC_ProcRrmmPlmnSearchStopCnf_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

    return VOS_TRUE;
}



VOS_UINT32  NAS_MMC_RcvRrMmRelInd_PlmnList_WaitWasPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulIsPrefbandListScene;
    VOS_UINT32                          ulIsFullbandListScene;

    ulIsPrefbandListScene = NAS_MMC_IsPrefBandListSearchScene_PlmnList();
    ulIsFullbandListScene = NAS_MMC_IsFullBandListSearchScene_PlmnList();

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmRelInd_PlmnList_WaitWasPlmnSearchStopCnf: ENTERED");

    /* �����ж�ԭ��ֵ */

    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF);

    /* ״̬���˳����Ϊ�� */
    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnList())
    {
        /* ��ǰ�û��б����� */
        if (VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
        {
            if ( VOS_TRUE == NAS_MMC_GetNotifyMsccFlag_PlmnList())
            {
                /* ��MSCC�ظ�ID_MMC_MSCC_PLMN_LIST_ABORT_CNF */
                NAS_MMC_SndMsccPlmnListAbortCnf_PlmnList();
            }
            else
            {
                /* ��MSCC�ظ�LIST������� */
                NAS_MMC_SndMsccPlmnListCnf_PlmnList();
            }
        }

        /* ����״̬��ABORT�˳���� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ����״̬���˳���� */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());

    /* ����5S�����Գ���LIST������ʱ�� */
    if ( VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
    {
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST, TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST_LEN);
    }
    else
    {
        /* prefband list �� fullband list������������Ҫ����TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST��ʱ�� */
        if ((VOS_FALSE == ulIsPrefbandListScene)
         && (VOS_FALSE == ulIsFullbandListScene))
        {
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST, TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST_LEN);
        }
    }

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvTiWaitWasStopCnfExpired_PlmnList_WaitWasPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitWasStopCnfExpired_PlmnList_WaitWasPlmnSearchStopCnf: Timer Expired");

    /* ��������ֹͣ�ظ���� */
    NAS_MMC_ProcRrmmPlmnSearchStopCnf_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitGasPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼��Ҫ��ֹ��ǰ״̬����־ */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvRrMmPlmnSrchStopCnf_PlmnList_WaitGasPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF);

    /* ��������ֹͣ�ظ���� */
    NAS_MMC_ProcRrmmPlmnSearchStopCnf_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);

    return VOS_TRUE;
}



VOS_UINT32  NAS_MMC_RcvGrrMmSysInfoInd_PlmnList_WaitGasPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����յ�GAS��ϵͳ��Ϣ����ĿǰUtran��Enable��������Disable Utran */
    NAS_MMC_RcvGasSysInfoSetUtranCapabilityStatus();

    /* ����פ����Ϣ����ת��ϵͳ��Ϣ */
    NAS_MMC_ProcGasSysInfo_PlmnList(pstMsg);

    return VOS_TRUE;
}



VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortFsmMsg_PlmnList_WaitGasPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼��Ҫ��ֹ��ǰ״̬����־ */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ����֪ͨMSCC�ظ���� */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvRrMmPlmnSrchCnf_PlmnList_WaitGasPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU          *pstPlmnSrchCnf = VOS_NULL_PTR;

    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;
    VOS_UINT32                          ulIndex;

    pstPlmnSrchCnf = (RRMM_PLMN_SEARCH_CNF_STRU*)pstMsg;

    switch(pstPlmnSrchCnf->ulSearchRlt)
    {
        /* LIST�����ظ���ֹͣ�����Գ�,NO RFʱֱ���˳�LIST�������� */
        case RRC_PLMN_SEARCH_RLT_USER_LIST_NO_RF:
        case RRC_PLMN_SEARCH_RLT_INTER_LIST_NO_RF:
        case RRC_PLMN_SEARCH_RLT_INTER_LIST_PREF_BAND_NO_RF:

            /* ֹͣ������ʱ�� */
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF);

            NAS_MMC_ProcNoRf_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);
            return VOS_TRUE;

        /*ֻ���������ɹ�ʱ�Ž��д��� */
        case RRC_PLMN_SEARCH_RLT_USER_LIST:
        case RRC_PLMN_SEARCH_RLT_INTER_LIST_SUCC:
        case RRC_PLMN_SEARCH_RLT_INTER_LIST_PREF_BAND_SUCC:
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmPlmnSrchCnf_PlmnList_WaitGasPlmnSearchStopCnf: Unexpected List Search Result!");
            return VOS_TRUE;
    }

    /* LIST����������,��Ҫ���ݵ�ǰ�����Я�����Ѿ��������Ľ��뼼����Ϣ����RAT��������� */
    for ( ulIndex = 0; ulIndex < NAS_RRC_MAX_RAT_NUM; ulIndex++)
    {
        if ( RRC_NAS_RAT_LIST_SEARCH_CMPL == pstPlmnSrchCnf->astSearchRatInfo[ulIndex].enListSearchRlt)
        {
            /*��RRC�Ľ��뼼��ת����MML����ĸ�ʽ��Ȼ����� */
            NAS_MMC_ConvertRrcRatToNasFormat(pstPlmnSrchCnf->astSearchRatInfo[ulIndex].enRat, &enRat);
            NAS_MMC_InitSpecRatSearchedPlmnListInfo_PlmnList(enRat);
            NAS_MMC_SetSearchedFlag_PlmnList(enRat);

            NAS_MMC_SetSpecRatSearchedTypeByPlmnSearchCnfSucc_PlmnList(enRat, pstPlmnSrchCnf->ulSearchRlt);
        }
    }

    /* ���������б� */
    NAS_MMC_UpdateSearchedPlmnListInfo_PlmnList(&(pstPlmnSrchCnf->PlmnIdList));

    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF);

    /* ��������ֹͣ�ظ���� */
    NAS_MMC_ProcRrmmPlmnSearchStopCnf_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);

    return VOS_TRUE;
}



VOS_UINT32  NAS_MMC_RcvTiWaitGasStopCnfExpired_PlmnList_WaitGasPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitGasStopCnfExpired_PlmnList_WaitGasPlmnSearchStopCnf: Timer Expired");

    /* ��������ֹͣ�ظ���� */
    NAS_MMC_ProcRrmmPlmnSearchStopCnf_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);

    return VOS_TRUE;
}


#if (FEATURE_ON == FEATURE_LTE)

VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND);

    NAS_MMC_SndMsccListSearchCnfMsg_PlmnList();

    /* δ��ʼ��������ʱ�����б�Ϊ��,��¼��ǰע�ᵼ�µĺ���additionֵ��L1 MAIN��
       �յ���·�ͷź����additionֵ�����Ƿ񴥷����� */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());

    /*�˳�״̬��*/
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND);

    /* ����ID_MMC_MSCC_PLMN_LIST_ABORT_CNF */
    NAS_MMC_SndMsccPlmnListAbortCnf_PlmnList();

    /* δ��ʼ��������ʱ�����б�Ϊ��,��¼��ǰע�ᵼ�µĺ���additionֵ��L1 MAIN��
       �յ���·�ͷź����additionֵ�����Ƿ񴥷����� */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());

    /*�˳�״̬��*/
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvLmmSuspendInd_PlmnList_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ���ݲ�ͬ�Ĺ���ԭ��ֵ,������ͬ��״̬�� */
    LMM_MMC_SUSPEND_IND_STRU           *pstLSuspendMsg  = VOS_NULL_PTR;

    pstLSuspendMsg = (LMM_MMC_SUSPEND_IND_STRU*)pstMsg;

    /* ���ݲ�ͬ�Ĺ���ԭ��ֵ��������ͬ��״̬�� */
    switch (pstLSuspendMsg->ulSysChngType)
    {
        case MMC_LMM_SUS_TYPE_RSL:
        case MMC_LMM_SUS_TYPE_REDIR:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_CELLRESEL);
            break;

        case MMC_LMM_SUS_TYPE_HO:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_HO);
            break;

        case MMC_LMM_SUS_TYPE_CCO:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_CCO);
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmSuspendInd_PlmnList_WaitEpsConnRelInd:Unexpected Suspend Type!");
            break;
    }

    if ( (MMC_LMM_SUS_TYPE_BUTT != pstLSuspendMsg->ulSysChngType)
      && (MMC_LMM_SUS_TYPE_CCO_REVERSE != pstLSuspendMsg->ulSysChngType))
    {
        NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                                 NAS_MML_GetSimPsRegStatus());
    }

    return VOS_TRUE;
}



VOS_UINT32  NAS_MMC_RcvLmmMmcStatusInd_PlmnList_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_STATUS_IND_STRU            *pstLmmStatusIndMsg = VOS_NULL_PTR;

    pstLmmStatusIndMsg  = ( LMM_MMC_STATUS_IND_STRU* )pstMsg;

    /* ����LMM������״̬ */
    switch (pstLmmStatusIndMsg->ulConnState)
    {
        case MMC_LMM_CONN_ESTING:
        case MMC_LMM_CONNECTED_SIG:

            NAS_MML_SetEpsSigConnStatusFlg(VOS_TRUE);
            break;

        case MMC_LMM_CONNECTED_DATA:

            NAS_MML_SetEpsServiceConnStatusFlg(VOS_TRUE);

            /* ֹͣ�ȴ�EPS��·�ͷŶ�ʱ�� */
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND);

            NAS_MMC_StartPeriodTryingUserListSrchTimer_PlmnList();

            /* ��ҵ��ʱ��δ����LIST�������ѵ��������б�Ϊ��,����״̬��ʧ�ܵ��˳���� */
            NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                     VOS_FALSE,
                                     NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                     NAS_MMC_GetRegRsltInfo_PlmnList());

            /* �˳�״̬�� */
            NAS_MMC_FSM_QuitFsmL2();

            return VOS_TRUE;

        case MMC_LMM_CONN_IDLE:

            NAS_MML_SetEpsSigConnStatusFlg(VOS_FALSE);
            NAS_MML_SetEpsServiceConnStatusFlg(VOS_FALSE);
            break;

        default:

            break;
    }

    /* �ж�RRC�����Ƿ���� */
    if ( VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        /* ���ؼ����ȴ� */
        return VOS_TRUE;
    }

    /* �ȴ�IMS��ע���� */
    if (NAS_MMC_WAIT_REG_RESULT_IND_NULL != NAS_MMC_GetWaitRegRsltFlag_PlmnList())
    {
        return VOS_TRUE;
    }

    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND);

    /* ��LMM����LIST��������,����פ��״̬Ϊ��פ��,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

    /* ��פ��̬֪ͨMM/GMM������ʼ */
    if (NAS_MMC_AS_CELL_NOT_CAMP_ON == NAS_MMC_GetAsCellCampOn())
    {
        /* ��GMM��������ָʾ */
        NAS_MMC_SndGmmPlmnSchInit();

        /* ��MM��������ָʾ */
        NAS_MMC_SndMmPlmnSchInit();

        NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);
    }

    return VOS_TRUE;

}



VOS_UINT32  NAS_MMC_RcvLmmSysInfoInd_PlmnList_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ProcLteSysInfo_PlmnList(pstMsg);

    NAS_MMC_SetCsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_BUTT);
    NAS_MMC_SetPsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_BUTT);


    return VOS_TRUE;
}



VOS_UINT32  NAS_MMC_RcvLmmAttachInd_PlmnList_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_ATTACH_IND_STRU                                *pstLmmAttachIndMsg = VOS_NULL_PTR;

    pstLmmAttachIndMsg  = (LMM_MMC_ATTACH_IND_STRU*)pstMsg;

    /* ��GMM��MMת��ע������Ϣ */
    NAS_MMC_SndMmLmmAttachInd(pstLmmAttachIndMsg);
    NAS_MMC_SndGmmLmmAttachInd(pstLmmAttachIndMsg);

    /* ����attach��� */
    NAS_MMC_ProcLmmAttachInd_PlmnList(pstLmmAttachIndMsg);

    /* L��ע����ɺ�IMSʱ֧��ʱ�ᷢ��IMSע��,��Ҫ����IMSע�����������Ƿ���Ҫ
       disable Lģ,��ʱ��Ҫ��һ���ȴ�IMS��ע���� */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();

#if (FEATURE_ON == FEATURE_IMS)
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_IMS);
#endif

    return VOS_TRUE;
}



VOS_UINT32  NAS_MMC_RcvLmmTauResultInd_PlmnList_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg;

    pstLmmTauIndMsg  = (LMM_MMC_TAU_RESULT_IND_STRU*)pstMsg;

    /* ��GMM��MMת��ע������Ϣ */
    NAS_MMC_SndMmLmmTauResultInd(pstLmmTauIndMsg);
    NAS_MMC_SndGmmLmmTauResultInd(pstLmmTauIndMsg);

    /* ����tau��� */
    NAS_MMC_ProcLmmTauResultInd_PlmnList(pstLmmTauIndMsg);

    /* L��ע����ɺ�IMSʱ֧��ʱ�ᷢ��IMSע��,��Ҫ����IMSע�����������Ƿ���Ҫ
       disable Lģ,��ʱ��Ҫ��һ���ȴ�IMS��ע���� */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();

#if (FEATURE_ON == FEATURE_IMS)
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_IMS);
#endif

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvLmmDetachInd_PlmnList_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_DETACH_IND_STRU                                *pstDetachMsg = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;

    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));
    pstDetachMsg        = (LMM_MMC_DETACH_IND_STRU*)pstMsg;

    /* ����DETACH��Ϣ��������һ������ */
    NAS_MMC_ProcLmmDetachInd(pstDetachMsg, &enCsAdditionalAction, &enPsAdditionalAction);

    /*����EPS����һ���Ķ�������*/
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enPsAdditionalAction)
    {
        NAS_MMC_SetPsRegAdditionalAction_PlmnList(enPsAdditionalAction);
    }

    /*����CS����һ���Ķ�������*/
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enCsAdditionalAction)
    {
        NAS_MMC_SetCsRegAdditionalAction_PlmnList(enCsAdditionalAction);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn())
    {
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);

        NAS_MMC_SndOmEquPlmn();

        /* ֪ͨCSS GEO��Ϣ */
        NAS_MMC_SndCssCurrGeoInd(VOS_TRUE, stSndEquPlmnInfo.ucEquPlmnNum, stSndEquPlmnInfo.astEquPlmnAddr);
    }

    return VOS_TRUE;
}



VOS_UINT32  NAS_MMC_RcvMmcMmcSuspendRslt_PlmnList_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                             NAS_MML_GetSimPsRegStatus());

    /* ��ѡ��ǰ���뼼���Ѿ��ı䣬��Ҫ���³�ʼ�������Ľ��뼼�����ȼ� */
 #if (FEATURE_ON == FEATURE_CSG)
    if (VOS_TRUE == NAS_MMC_IsCsgList_PlmnList())
    {
        NAS_MMC_InitCsgListSearchRatInfo_PlmnList();
    }
    else
 #endif
    {
        NAS_MMC_InitSearchRatInfo_PlmnList();
    }

    if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
    {
        /* ֹͣ������ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND);

        NAS_MMC_SndMsccPlmnListRejMsg_PlmnList();

        /* ����δ����LIST�������������������б�Ϊ�� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());


        /* �˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* �жϵ�ǰ����ģʽ */
    if ( NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        /* �жϵ�ǰ���������Ƿ���� */
        if ( VOS_TRUE == NAS_MML_IsRrcConnExist())
        {
            /* ���ؼ����ȴ� */
            return VOS_TRUE;
        }

        /* ֹͣ������ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND);

        /* ��L����LIST��������,״̬Ǩ�Ƶ�,����������ʱ�� */
        NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

        /* ��פ��̬֪ͨMM/GMM������ʼ */
        if (NAS_MMC_AS_CELL_NOT_CAMP_ON == NAS_MMC_GetAsCellCampOn())
        {
            /* ��GMM��������ָʾ */
            NAS_MMC_SndGmmPlmnSchInit();

            /* ��MM��������ָʾ */
            NAS_MMC_SndMmPlmnSchInit();

            NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);
        }

        return VOS_TRUE;
    }

    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND);

    /* ����CSPS��AdditionalAction */
    NAS_MMC_SetCsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_BUTT);
    NAS_MMC_SetPsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_BUTT);

    /* Ǩ��״̬���ȵ�CS/PSע���� */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_CS);
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    /* Ǩ�Ƶ��ȴ�ע����״̬ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_CSPS_REG_IND);

    /* ����������ʱ�� */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND, TI_NAS_MMC_WAIT_CSPS_REG_IND_LEN);

    return VOS_TRUE;

}


VOS_UINT32  NAS_MMC_RcvTiWaitEpsConnRelIndExpired_PlmnList_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitRrcConnRelIndExpired_PlmnList_WaitRrcConnRelInd Enter!");

    /* ����ҵ�񣬻ظ��б���ʧ�� */
    if (VOS_TRUE == NAS_MML_GetCsServiceExistFlg())
    {
        NAS_MMC_SndMsccPlmnListRejMsg_PlmnList();
    }
    else
    {
        NAS_MMC_StartPeriodTryingUserListSrchTimer_PlmnList();
    }

    /* ����δ��ʼ�������������������б�Ϊ�գ���Ҫ�����Գ��ԣ��˳�״̬������Ҫ�������� */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());


    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}



VOS_UINT32 NAS_MMC_RcvMsccImsVoiceCapInd_PlmnList_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU     *pstImsVoiceInd = VOS_NULL_PTR;
    VOS_UINT8                           ucWaitRegRsltFlag;

    ucWaitRegRsltFlag   = NAS_MMC_GetWaitRegRsltFlag_PlmnList();
    pstImsVoiceInd      = (MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU *)pstMsg;

    /* ����ڵȴ�IMS��ע�����Ŵ��� */
    if (NAS_MMC_WAIT_REG_RESULT_IND_IMS != (ucWaitRegRsltFlag & NAS_MMC_WAIT_REG_RESULT_IND_IMS))
    {
        return VOS_TRUE;
    }

    /* �����ǰ�յ�IMS VOICE����������� */
    if (VOS_TRUE != pstImsVoiceInd->ucRcvServiceChangeIndFlag)
    {
        return VOS_TRUE;
    }

    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_IMS);

    /* IMS������ʱ�ж��Ƿ���Ҫdisable LTE */
    if (VOS_FALSE  == pstImsVoiceInd->ucAvail)
    {
        if (VOS_TRUE == NAS_MMC_IsNeedDisableLte_ImsVoiceNotAvail())
        {
            NAS_MMC_SetCsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION);

            NAS_MML_DisableLteCommProc(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS,
                                       MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);

            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMsccImsVoiceCapInd_PlmnList_WaitEpsConnRelInd: MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE");
        }
    }

    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND);

    /* ��LMM����LIST��������,����פ��״̬Ϊ��פ��,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

    /* ��פ��̬֪ͨMM/GMM������ʼ */
    if (NAS_MMC_AS_CELL_NOT_CAMP_ON == NAS_MMC_GetAsCellCampOn())
    {
        /* ��GMM��������ָʾ */
        NAS_MMC_SndGmmPlmnSchInit();

        /* ��MM��������ָʾ */
        NAS_MMC_SndMmPlmnSchInit();

        NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);
    }

    return VOS_TRUE;
}




VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitEpsRegInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

    NAS_MMC_SndMsccListSearchCnfMsg_PlmnList();

    /* δ��ʼ��������ʱ�����б�Ϊ��,��¼��ǰע�ᵼ�µĺ���additionֵ��L1 MAIN��
       �յ���·�ͷź����additionֵ�����Ƿ񴥷����� */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitEpsRegInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

    /* ����ID_MMC_MSCC_PLMN_LIST_ABORT_CNF */
    NAS_MMC_SndMsccPlmnListAbortCnf_PlmnList();

    /* δ��ʼ��������ʱ�����б�Ϊ��,��¼��ǰע�ᵼ�µĺ���additionֵ��L1 MAIN��
       �յ���·�ͷź����additionֵ�����Ƿ񴥷����� */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvLmmSuspendInd_PlmnList_WaitEpsRegInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_SUSPEND_IND_STRU           *pstLSuspendMsg = VOS_NULL_PTR;
    MMC_SUSPEND_CAUSE_ENUM_UINT8        enSuspendCause;
    pstLSuspendMsg = (LMM_MMC_SUSPEND_IND_STRU*)pstMsg;

    /* Lģ�£�����ԭ������GU�²�ͬ��ת��һ�¹���ԭ���� */
    NAS_MMC_ConvertLmmSysChngTypeToMmcType(pstLSuspendMsg->ulSysChngType, &enSuspendCause);

    /* ���Ϊ��������ȷ, ������������ϵͳ��ѡ */
    if (MMC_SUSPEND_CAUSE_BUTT <= enSuspendCause)
    {
        NAS_MMC_SndLmmSuspendRsp(MMC_LMM_FAIL);
        return VOS_TRUE;
    }

    /* ���ݲ�ͬ�Ĺ���ԭ��ֵ��������ͬ��״̬�� */
    switch (enSuspendCause)
    {
        /* ���� С����ѡ ״̬�� */
        case MMC_SUSPEND_CAUSE_CELLRESELECT:
        case MMC_SUSPEND_CAUSE_REDIRECTION:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_CELLRESEL);
            NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                                     NAS_MML_GetSimPsRegStatus());
            break;

        /* ����HANDOVER״̬�� */
        case MMC_SUSPEND_CAUSE_HANDOVER:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_HO);
            NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                                     NAS_MML_GetSimPsRegStatus());

            break;

        /* ���� CCO״̬�� */
        case MMC_SUSPEND_CAUSE_CELLCHANGE:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_CCO);
            NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                                     NAS_MML_GetSimPsRegStatus());
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmSuspendInd_PlmnList_WaitEpsRegInd:Unexpected suspend type!");
            break;
    }

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvLmmSysInfoInd_PlmnList_WaitEpsRegInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ProcLteSysInfo_PlmnList(pstMsg);

    return VOS_TRUE;
}



VOS_UINT32  NAS_MMC_RcvLmmAttachInd_PlmnList_WaitEpsRegInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_ATTACH_IND_STRU                                *pstLmmAttachIndMsg = VOS_NULL_PTR;
    NAS_MML_LTE_UE_OPERATION_MODE_ENUM_UINT8                enUeOperationMode;

    enUeOperationMode   =  NAS_MML_GetLteUeOperationMode();
    pstLmmAttachIndMsg  = (LMM_MMC_ATTACH_IND_STRU*)pstMsg;

    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    /* LMM������δ�ظ�search cnfʱ�յ��û�detach ps����󣬺���������ע���mmc�ظ�attach result
       ΪMMC_LMM_ATT_RSLT_PS_ATT_NOT_ALLOW���������������MMC_LMM_ATT_TYPE_BUTT��
       MMC��Ҫ���ݵ�ǰue operation mode�������������¸�ֵ */
    if ((MMC_LMM_ATT_TYPE_BUTT == pstLmmAttachIndMsg->ulReqType)
     && (MMC_LMM_ATT_RSLT_PS_ATT_NOT_ALLOW == pstLmmAttachIndMsg->ulAttachRslt))
    {
        pstLmmAttachIndMsg->ulReqType = NAS_MMC_ConvertLmmAttachReqType(enUeOperationMode);
    }

    /* ��GMM��MMת��ע������Ϣ */
    NAS_MMC_SndMmLmmAttachInd(pstLmmAttachIndMsg);
    NAS_MMC_SndGmmLmmAttachInd(pstLmmAttachIndMsg);

    /* ����attach��� */
    NAS_MMC_ProcLmmAttachInd_PlmnList(pstLmmAttachIndMsg);

    if (NAS_MMC_WAIT_REG_RESULT_IND_NULL != NAS_MMC_GetWaitRegRsltFlag_PlmnList())
    {
        return VOS_TRUE;
    }

    /* ֹͣ�ȴ�ע�����ı�����ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

    if ( VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        if (VOS_TRUE == NAS_MMC_IsDisableLteNeedLocalReleaseEpsConn())
        {
            NAS_MMC_SndLmmRelReq();
        }

        /* Ǩ��״̬���ȴ�EPS����·�ͷ� */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_EPS_CONN_REL_IND);

        /* ����������ʱ�� */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);

        return VOS_TRUE;
    }

    /* ���ݵ�ǰ�Ľ���ģʽ������LIST��������,Ǩ��״̬������������ʱ�� */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

    return VOS_TRUE;
}



VOS_UINT32  NAS_MMC_RcvLmmTauResultInd_PlmnList_WaitEpsRegInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg = VOS_NULL_PTR;

    pstLmmTauIndMsg = (LMM_MMC_TAU_RESULT_IND_STRU*)pstMsg;

    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    /* ��GMM��MMת��ע������Ϣ */
    NAS_MMC_SndMmLmmTauResultInd(pstLmmTauIndMsg);
    NAS_MMC_SndGmmLmmTauResultInd(pstLmmTauIndMsg);

    /* ����tau��� */
    NAS_MMC_ProcLmmTauResultInd_PlmnList(pstLmmTauIndMsg);

    if (NAS_MMC_WAIT_REG_RESULT_IND_NULL != NAS_MMC_GetWaitRegRsltFlag_PlmnList())
    {
        return VOS_TRUE;
    }

    /* ֹͣ�ȴ�ע�����ı�����ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

    if ( VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        /*��SMS ONLY,disable LTE,��#18�б��У�ע��ɹ�����L�����ͷ�����*/
        if (VOS_TRUE == NAS_MMC_IsDisableLteNeedLocalReleaseEpsConn())
        {
            NAS_MMC_SndLmmRelReq();
        }

        /* Ǩ��״̬���ȴ�EPS����·�ͷ� */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_EPS_CONN_REL_IND);

        /* ����������ʱ�� */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);

        return VOS_TRUE;
    }

    /* ���ݵ�ǰ�Ľ���ģʽ������LIST��������,Ǩ��״̬������������ʱ�� */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvLmmMmcStatusInd_PlmnList_WaitEpsRegInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_STATUS_IND_STRU            *pstLmmStatusIndMsg = VOS_NULL_PTR;

    pstLmmStatusIndMsg = (LMM_MMC_STATUS_IND_STRU*)pstMsg;

    if ( VOS_FALSE == pstLmmStatusIndMsg->bitOpConnState)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmMmcStatusInd_PlmnList_WaitEpsRegInd:bitOpConnState IS VOS_FALSE");
        return VOS_TRUE;
    }

    /* ����LMM������״̬ */
    switch (pstLmmStatusIndMsg->ulConnState)
    {
        case MMC_LMM_CONN_ESTING:
        case MMC_LMM_CONNECTED_SIG:
            NAS_MML_SetEpsSigConnStatusFlg(VOS_TRUE);
            break;

        case MMC_LMM_CONNECTED_DATA:
            NAS_MML_SetEpsServiceConnStatusFlg(VOS_TRUE);

            /* ֹͣ������ʱ�� */
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

            NAS_MMC_StartPeriodTryingUserListSrchTimer_PlmnList();

            /* ����״̬��ʧ���˳��Ľ�� */
            NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

            /* �˳�״̬�� */
            NAS_MMC_FSM_QuitFsmL2();

            return VOS_TRUE;

        case MMC_LMM_CONN_IDLE:
            NAS_MML_SetEpsSigConnStatusFlg(VOS_FALSE);
            NAS_MML_SetEpsServiceConnStatusFlg(VOS_FALSE);
            break;

        default:

            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmMmcStatusInd_PlmnList_WaitEpsRegInd:Unexpected connection status!");

            break;
    }

    return VOS_TRUE;

}


VOS_UINT32  NAS_MMC_RcvLmmAreaLostInd_PlmnList_WaitEpsRegInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_AREA_LOST_IND_STRU                             *pstAreaLostInd = VOS_NULL_PTR;

    pstAreaLostInd = (LMM_MMC_AREA_LOST_IND_STRU*)pstMsg;
    NAS_MMC_SetSpecRatSearchedTypeByLmmAreaLostInd_PlmnList(NAS_MML_GetCurrNetRatType(), pstAreaLostInd);

    /* ֹͣ�ȴ�ע������Ϣ�Ķ�ʱ��  */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

    /* ���פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* ��ǰ�źŸ��� */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    /* ���·���״̬ �ϱ��޷���*/
    NAS_MMC_SetCsServiceStatus(NAS_MMC_NO_SERVICE);
    NAS_MMC_SetPsServiceStatus(NAS_MMC_NO_SERVICE);

    /* �����㷢��LIST��������,Ǩ��״̬���ȴ� LIST�����ظ�״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

    /* ��GMM��������ָʾ */
    NAS_MMC_SndGmmPlmnSchInit();

    /* ��MM��������ָʾ */
    NAS_MMC_SndMmPlmnSchInit();

    /* ���ý�������״̬ */
    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvLmmAreaLostInd_PlmnList_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_AREA_LOST_IND_STRU                             *pstAreaLostInd = VOS_NULL_PTR;

    pstAreaLostInd = (LMM_MMC_AREA_LOST_IND_STRU*)pstMsg;
    NAS_MMC_SetSpecRatSearchedTypeByLmmAreaLostInd_PlmnList(NAS_MML_GetCurrNetRatType(), pstAreaLostInd);

    /* ���פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* ��ǰ�źŸ��� */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    /* ���·���״̬ �ϱ��޷���*/
    NAS_MMC_SetCsServiceStatus(NAS_MMC_NO_SERVICE);
    NAS_MMC_SetPsServiceStatus(NAS_MMC_NO_SERVICE);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvLmmSysInfoInd_PlmnList_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ProcLteSysInfo_PlmnList(pstMsg);

    return VOS_TRUE;
}




VOS_UINT32  NAS_MMC_RcvLmmAttachInd_PlmnList_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_ATTACH_IND_STRU                                *pstLmmAttachIndMsg = VOS_NULL_PTR;

    pstLmmAttachIndMsg  = (LMM_MMC_ATTACH_IND_STRU*)pstMsg;

    /* ��GMM��MMת��ע������Ϣ */
    NAS_MMC_SndMmLmmAttachInd(pstLmmAttachIndMsg);
    NAS_MMC_SndGmmLmmAttachInd(pstLmmAttachIndMsg);

    /* ����attach��� */
    NAS_MMC_ProcLmmAttachInd_PlmnList(pstLmmAttachIndMsg);

    /* L��ע����ɺ�IMSʱ֧��ʱ�ᷢ��IMSע��,��Ҫ����IMSע�����������Ƿ���Ҫ
       disable Lģ,��ʱ��Ҫ��һ���ȴ�IMS��ע���� */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();

#if (FEATURE_ON == FEATURE_IMS)
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_IMS);
#endif

    return VOS_TRUE;
}



VOS_UINT32  NAS_MMC_RcvLmmTauResultInd_PlmnList_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg;

    pstLmmTauIndMsg  = (LMM_MMC_TAU_RESULT_IND_STRU*)pstMsg;

    /* ��GMM��MMת��ע������Ϣ */
    NAS_MMC_SndMmLmmTauResultInd(pstLmmTauIndMsg);
    NAS_MMC_SndGmmLmmTauResultInd(pstLmmTauIndMsg);

    /* ����tau��� */
    NAS_MMC_ProcLmmTauResultInd_PlmnList(pstLmmTauIndMsg);

    /* L��ע����ɺ�IMSʱ֧��ʱ�ᷢ��IMSע��,��Ҫ����IMSע�����������Ƿ���Ҫ
       disable Lģ,��ʱ��Ҫ��һ���ȴ�IMS��ע���� */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();

#if (FEATURE_ON == FEATURE_IMS)
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_IMS);
#endif

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvMsccImsVoiceCapInd_PlmnList_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU *pstImsVoiceInd = VOS_NULL_PTR;
    VOS_UINT8                           ucWaitRegRsltFlag;

    ucWaitRegRsltFlag   = NAS_MMC_GetWaitRegRsltFlag_PlmnList();
    pstImsVoiceInd      = (MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU *)pstMsg;

    /* ����ڵȴ�IMS��ע�����Ŵ��� */
    if (NAS_MMC_WAIT_REG_RESULT_IND_IMS != (ucWaitRegRsltFlag & NAS_MMC_WAIT_REG_RESULT_IND_IMS))
    {
        return VOS_TRUE;
    }

    /* �����ǰ�յ�IMS VOICE����������� */
    if (VOS_TRUE != pstImsVoiceInd->ucRcvServiceChangeIndFlag)
    {
        return VOS_TRUE;
    }

    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_IMS);

    /* IMS������ʱ�ж��Ƿ���Ҫdisable LTE */
    if (VOS_FALSE  == pstImsVoiceInd->ucAvail)
    {
        if (VOS_TRUE == NAS_MMC_IsNeedDisableLte_ImsVoiceNotAvail())
        {
            NAS_MMC_SetCsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION);

            NAS_MML_DisableLteCommProc(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS,
                                       MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);

            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMsccImsVoiceCapInd_PlmnList_WaitLmmPlmnSearchCnf: MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE");
        }
    }

    return VOS_TRUE;
}



VOS_UINT32  NAS_MMC_RcvMmcMmcSuspendRslt_PlmnList_WaitEpsRegInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��ѡ��ǰ���뼼���Ѿ��ı䣬��Ҫ���³�ʼ�������Ľ��뼼�����ȼ� */
 #if (FEATURE_ON == FEATURE_CSG)
    if (VOS_TRUE == NAS_MMC_IsCsgList_PlmnList())
    {
        NAS_MMC_InitCsgListSearchRatInfo_PlmnList();
    }
    else
 #endif
    {
        NAS_MMC_InitSearchRatInfo_PlmnList();
    }

    NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                             NAS_MML_GetSimPsRegStatus());

    if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
    {
        /* ֹͣ������ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

        NAS_MMC_SndMsccPlmnListRejMsg_PlmnList();

        /* ����δ����LIST�������������������б�Ϊ�� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* �жϵ�ǰ����ģʽ */
    if ( NAS_MML_NET_RAT_TYPE_LTE != NAS_MML_GetCurrNetRatType())
    {
        /* ֹͣ������ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

        /* ����CSPS��AdditionalAction */
        NAS_MMC_SetCsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_BUTT);
        NAS_MMC_SetPsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_BUTT);

        NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();
        NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_CS);
        NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_PS);

        /* Ǩ�Ƶ��ȴ�ע����״̬ */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_CSPS_REG_IND);

        /* ����������ʱ�� */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND, TI_NAS_MMC_WAIT_CSPS_REG_IND_LEN);

        return VOS_TRUE;
    }

    /* �����ȴ�ע���� */
    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvTiWaitEpsRegIndExpired_PlmnList_WaitEpsRegInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitEpsRegIndExpired_PlmnList_WaitEpsRegInd Enter");

    /* ����ȴ�ע������� */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();

    /* ������������ �����ȴ�EPS�����ͷ� */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        /* Ǩ��״̬���ȴ�EPS��·�ͷ� */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_EPS_CONN_REL_IND);

        /* ����������ʱ�� */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);

        return VOS_TRUE;
    }

    /* ���ݵ�ǰ�Ľ���ģʽ������LIST��������,Ǩ��״̬������������ʱ�� */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

    return VOS_TRUE;

}



VOS_UINT32 NAS_MMC_RcvMsccImsVoiceCapInd_PlmnList_WaitEpsRegInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU     *pstImsVoiceInd = VOS_NULL_PTR;
    VOS_UINT8                           ucWaitRegRsltFlag;

    ucWaitRegRsltFlag   = NAS_MMC_GetWaitRegRsltFlag_PlmnList();
    pstImsVoiceInd      = (MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU *)pstMsg;

    /* ����ڵȴ�PS��ע����������ȴ�PSע���� */
    if (NAS_MMC_WAIT_REG_RESULT_IND_PS == (ucWaitRegRsltFlag & NAS_MMC_WAIT_REG_RESULT_IND_PS))
    {
        return VOS_TRUE;
    }

    /* �����ǰ�յ�IMS VOICE����������� */
    if (VOS_TRUE != pstImsVoiceInd->ucRcvServiceChangeIndFlag)
    {
        return VOS_TRUE;
    }

    /* ����ȴ�ע������� */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();

    /* IMS������ʱ�ж��Ƿ���Ҫdisable LTE */
    if (VOS_FALSE  == pstImsVoiceInd->ucAvail)
    {
        if (VOS_TRUE == NAS_MMC_IsNeedDisableLte_ImsVoiceNotAvail())
        {
            NAS_MMC_SetCsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION);

            NAS_MML_DisableLteCommProc(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS,
                                       MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);

            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMsccImsVoiceCapInd_PlmnList_WaitEpsRegInd: MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE");
        }
    }

    /* ֹͣ�ȴ�ע�����ı�����ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        if (VOS_TRUE == NAS_MMC_IsDisableLteNeedLocalReleaseEpsConn())
        {
            NAS_MMC_SndLmmRelReq();
        }

        /* Ǩ��״̬���ȴ�EPS����·�ͷ� */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_EPS_CONN_REL_IND);

        /* ����������ʱ�� */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);

        return VOS_TRUE;
    }

    /* ���ݵ�ǰ�Ľ���ģʽ������LIST��������,Ǩ��״̬������������ʱ�� */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

    return VOS_TRUE;
}




VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ�ȴ�LMM��������ı�����ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_LIST_CNF);

    /* ��¼״̬���˳���� */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ��LMM����ֹͣ��������,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatPlmnSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvMmcTafPlmnListAbortReq_PlmnList_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ�ȴ�LMM��������ı�����ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_LIST_CNF);

    /* ��¼״̬���˳���� */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ����֪ͨMSCC�ظ���� */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    /* ��LMM����ֹͣ��������,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatPlmnSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvLmmPlmnSrchCnf_PlmnList_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_PLMN_SRCH_CNF_STRU         *pstLmmPlmnSrchcnf = VOS_NULL_PTR;

    pstLmmPlmnSrchcnf = (LMM_MMC_PLMN_SRCH_CNF_STRU*)pstMsg;

    /* ֹͣ�ȴ�LMM�����ظ��ı�����ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_LIST_CNF);

    /* �ж�LIST������� */
    switch (pstLmmPlmnSrchcnf->enRlst)
    {
        case MMC_LMM_PLMN_SRCH_RLT_USER_LIST_SUCC:
        case MMC_LMM_PLMN_SRCH_RLT_USER_LIST_REJ:
        case MMC_LMM_PLMN_SRCH_RLT_USER_LIST_NO_RF:

            NAS_MMC_ProcLmmSearchCnf_UserPlmnListSearch_PlmnList(pstLmmPlmnSrchcnf);
            break;

        case MMC_LMM_PLMN_SRCH_RLT_INTER_LIST_PREF_BAND_REJ:
        case MMC_LMM_PLMN_SRCH_RLT_INTER_LIST_PREF_BAND_FAIL:
        case MMC_LMM_PLMN_SRCH_RLT_INTER_LIST_PREF_BAND_SUCC:
        case MMC_LMM_PLMN_SRCH_RLT_INTER_LIST_PREF_BAND_NO_RF:
        case MMC_LMM_PLMN_SRCH_RLT_INTER_LIST_FULL_BAND_REJ:
        case MMC_LMM_PLMN_SRCH_RLT_INTER_LIST_FULL_BAND_FAIL:
        case MMC_LMM_PLMN_SRCH_RLT_INTER_LIST_FULL_BAND_SUCC:
        case MMC_LMM_PLMN_SRCH_RLT_INTER_LIST_FULL_BAND_NO_RF:

            NAS_MMC_ProcLmmSearchCnf_InterPlmnListSearch_PlmnList(pstLmmPlmnSrchcnf);
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmPlmnSrchCnf_PlmnList_WaitLmmPlmnSearchCnf: Unexpected List Search Result!");
            break;

    }

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvTiWaitLmmPlmnListCnfExpired_PlmnList_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* LIST���������У����������ϱ�RRMM_NOT_CAMP_ON����ʱ��Ҫ���ݵ�ǰפ��״̬����RAT��������� */
    if (NAS_MMC_AS_CELL_CAMP_ON == NAS_MMC_GetAsCellCampOn())
    {
        /* ������ģRAT��������� */
        NAS_MMC_SetSearchedFlag_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

        NAS_MMC_SetSearchedFlag_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

        NAS_MMC_SetSearchedFlag_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);
    }
    else
    {
        /* ���µ�ǰRAT��������� */
        NAS_MMC_SetSearchedFlag_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);
    }

    /* ��LMM����ֹͣ��������,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatPlmnSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

    return VOS_TRUE;
}



VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitLmmSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼��Ҫ��ֹ��ǰ״̬����־ */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortFsmMsg_PlmnList_WaitLmmSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼��Ҫ��ֹ��ǰ״̬����־ */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ����֪ͨMSCC�ظ���� */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvLmmSuspendCnf_PlmnList_WaitLmmSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_SUSPEND_CNF_STRU           *pstLmmSuspendCnf = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;

    VOS_UINT32                          ulNeedPlmnSearch;

    pstLmmSuspendCnf  = (LMM_MMC_SUSPEND_CNF_STRU*)pstMsg;

    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF);

    if ( MMC_LMM_FAIL  == pstLmmSuspendCnf->ulRst )
    {
        /* ���帴λ */
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_LMM_SUSPEND_FAILURE);

        return VOS_TRUE;
    }

    /* �ж�״̬���˳�����Ƿ�Ϊ�棬���Ϊ��*/
    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnList())
    {
        /* ���뼼������ΪBUTT����������ֱ��������ģ������������ */
        NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

        ulNeedPlmnSearch = VOS_FALSE;

        /*֪ͨMSCC�ظ����Ϊ��*/
        if ( VOS_TRUE == NAS_MMC_GetNotifyMsccFlag_PlmnList())
        {
            if (VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
            {
                /* ��MSCC�ظ�ID_MMC_MSCC_PLMN_LIST_ABORT_CNF */
                NAS_MMC_SndMsccPlmnListAbortCnf_PlmnList();
            }

            ulNeedPlmnSearch = VOS_TRUE;
        }
        else
        {
            if (VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
            {
                /* ��MSCC�ظ�LIST������� */
                NAS_MMC_SndMsccPlmnListCnf_PlmnList();
            }
        }

        /* ����״̬��ABORT���˳���� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                                (VOS_UINT8)ulNeedPlmnSearch,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ��ȡ������һ�����뼼�� */
    if ( VOS_FALSE == NAS_MMC_GetNextSearchingRat_PlmnList(&enRat))
    {
        /* �쳣��ӡ */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcRrmmSuspendCnf_PlmnList: Get next search rat fail.");

        /* ���뼼������ΪBUTT����������ֱ��������ģ������������ */
        NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

        /* �ϱ�LIST������� */
        NAS_MMC_SndMsccListSearchCnfMsg_PlmnList();

        /* ����״̬���˳���� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                          (VOS_UINT8)NAS_MMC_IsNeedPlmnSearch_PlmnList(),
                          NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                          NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ���ݻ�ȡ�Ľ��뼼�����õ�ǰ���뼼�� */
    NAS_MML_SetCurrNetRatType(enRat);

    /* ���¸�����ģʽ����LIST��������,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(enRat);

    return VOS_TRUE;
}



VOS_UINT32  NAS_MMC_RcvTiWaitLmmSuspendCnfExpired_PlmnList_WaitLmmSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitLmmSuspendCnfExpired_PlmnList_WaitLmmSuspendCnf: Timer Expired");

    /* ���ɻָ����ϣ���λ */
    NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_LMM_SUSPEND_CNF_EXPIRED);

    return VOS_TRUE;
}



VOS_UINT32  NAS_MMC_RcvLmmPlmnSrchStopCnf_PlmnList_WaitLmmPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF);


    /* ��������ֹͣ�ظ���� */
    NAS_MMC_ProcLmmPlmnSearchStopCnf_PlmnList();

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvLmmSearchedPlmnInfoInd_PlmnList_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_SEARCHED_PLMN_INFO_IND_STRU          *pstSearchedPlmnInfoMsg = VOS_NULL_PTR;
    RRC_PLMN_ID_LIST_STRU                        *pstRrcPlmnList;
    VOS_UINT32                                    ulIsNeedStopPlmnListFlg;
    NAS_MML_PLMN_WITH_RAT_STRU                    stAbortPlmn;

    NAS_MEM_SET_S(&stAbortPlmn, sizeof(NAS_MML_PLMN_WITH_RAT_STRU), 0x0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    pstSearchedPlmnInfoMsg = (LMM_MMC_SEARCHED_PLMN_INFO_IND_STRU *)pstMsg;

    pstRrcPlmnList = (RRC_PLMN_ID_LIST_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                   sizeof(RRC_PLMN_ID_LIST_STRU));

    if (VOS_NULL_PTR == pstRrcPlmnList)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmSearchedPlmnInfoInd_PlmnList_WaitLmmPlmnSearchCnf:ERROR: Memory Alloc Error");
        return VOS_TRUE;
    }

    PS_MEM_SET(pstRrcPlmnList, 0x00, sizeof(RRC_PLMN_ID_LIST_STRU));

    ulIsNeedStopPlmnListFlg = VOS_FALSE;

    /* ����������plmnת����RRC_PLMN_ID_LIST_STRU��ʽ */
    NAS_MMC_ConvertLmmSearchedPlmnToRrcPlmnList(pstSearchedPlmnInfoMsg, pstRrcPlmnList);

    /* ��ת����ʽ���plmn��Ϣ������Searched Plmn List�� */
    NAS_MMC_UpdateSearchedPlmnListInfo_PlmnList(pstRrcPlmnList);

    /* �ж��Ƿ���Ҫ��ϵ�ǰ��list�� */
    ulIsNeedStopPlmnListFlg = NAS_MMC_IsNeedStopPlmnListSearchRcvLmmSearchedPlmnInfoInd_PlmnList(pstSearchedPlmnInfoMsg, &stAbortPlmn);

    if (VOS_TRUE == ulIsNeedStopPlmnListFlg)
    {
        /* ���ݱ�����������ģʽ�����������ͱ�ʶ������syscfg:L->W->G����ǰ������W�����磬
           ��LģucPrefBandSearchedFlg��ucSpecSearchedFlg������������Ϊ�Ѿ�������,W G����Ϊδ������ */
        NAS_MMC_UpdateSearchedRatStatusByLmmSearchedPlmnInfoInd_PlmnList(pstSearchedPlmnInfoMsg);

        /* ������Ҫ��ϱ�־ucAbortBySearchedPlmnFlgΪtrue */
        NAS_MMC_SetAbortBySearchedPlmnFlg_PlmnList(VOS_TRUE);

        /* ��stAbortPlmn��¼��������ѡ��״̬���и���stAbortPlmn��MCC������������ */
        NAS_MMC_SetAbortListSearchPlmn(&stAbortPlmn);

        /* ֹͣ������ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_LIST_CNF);

        /* ����ֹͣ��������Ǩ״̬������ʱ�� */
        NAS_MMC_SndSpecRatPlmnSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

        PS_MEM_FREE(WUEPS_PID_MMC, pstRrcPlmnList);

        return VOS_TRUE;
    }

    PS_MEM_FREE(WUEPS_PID_MMC, pstRrcPlmnList);

    return VOS_TRUE;
}



VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitLmmPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��ABORT��־λ */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortFsmMsg_PlmnList_WaitLmmPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��ABORT��־λ */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ����֪ͨMSCC����ı�� */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}



VOS_UINT32  NAS_MMC_RcvLmmPlmnSrchCnf_PlmnList_WaitLmmPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_PLMN_SRCH_CNF_STRU         *pstLmmPlmnSrchCnf = VOS_NULL_PTR;
    RRC_PLMN_ID_LIST_STRU              *pstGuPlmnIdList;
    VOS_UINT32                          ulIndex;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNasRat;


    pstLmmPlmnSrchCnf = (LMM_MMC_PLMN_SRCH_CNF_STRU*)pstMsg;
    pstGuPlmnIdList   = (RRC_PLMN_ID_LIST_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                   sizeof(RRC_PLMN_ID_LIST_STRU));

    if (VOS_NULL_PTR == pstGuPlmnIdList)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmPlmnSrchCnf_PlmnList_WaitLmmPlmnSearchStopCnf:ERROR: Memory Alloc Error");
        return VOS_TRUE;
    }

    switch(pstLmmPlmnSrchCnf->enRlst)
    {
        /* LIST�����ظ���ֹͣ�����Գ�,NO RFʱֱ���˳�LIST�������� */
        case MMC_LMM_PLMN_SRCH_RLT_USER_LIST_NO_RF:
        case MMC_LMM_PLMN_SRCH_RLT_INTER_LIST_FULL_BAND_NO_RF:
        case MMC_LMM_PLMN_SRCH_RLT_INTER_LIST_PREF_BAND_NO_RF:
            /* ֹͣ������ʱ�� */
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF);

            PS_MEM_FREE(WUEPS_PID_MMC, pstGuPlmnIdList);
            NAS_MMC_ProcNoRf_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);
            return VOS_TRUE;

        /*ֻ���������ɹ�ʱ�Ž��д��� */
        case MMC_LMM_PLMN_SRCH_RLT_USER_LIST_SUCC:
        case MMC_LMM_PLMN_SRCH_RLT_INTER_LIST_FULL_BAND_SUCC:
        case MMC_LMM_PLMN_SRCH_RLT_INTER_LIST_PREF_BAND_SUCC:

            /* ���µ�RAT������� */
            for ( ulIndex = 0; ulIndex < MMC_LMM_MAX_RAT_NUM; ulIndex++)
            {
                if ( MMC_LMM_RAT_LIST_SEARCH_CMPL == pstLmmPlmnSrchCnf->astSearchRatInfo[ulIndex].enListSearchRlt)
                {
                    /* ��LMM��ʽRATת����NAS��ʽ */
                    NAS_MMC_ConvertLmmRatToNasFormat(pstLmmPlmnSrchCnf->astSearchRatInfo[ulIndex].enRat, &enNasRat);

                    NAS_MMC_InitSpecRatSearchedPlmnListInfo_PlmnList(enNasRat);

                    NAS_MMC_SetSearchedFlag_PlmnList(enNasRat);
                    NAS_MMC_SetSpecRatSearchedTypeByLmmPlmnSearchCnfSucc_PlmnList(enNasRat, pstLmmPlmnSrchCnf->enRlst);
                }
            }

            /*ת��L��ʽ�������б���ΪGU��ʽ��*/
            NAS_MMC_ConvertLmmPlmnIdListToGUFormat(&(pstLmmPlmnSrchCnf->stPlmnIdList), pstGuPlmnIdList);

            /*���������б�*/
            NAS_MMC_UpdateSearchedPlmnListInfo_PlmnList(pstGuPlmnIdList);

            PS_MEM_FREE(WUEPS_PID_MMC, pstGuPlmnIdList);


            /* ֹͣ������ʱ�� */
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF);


            /* ��������ֹͣ�ظ���� */
            NAS_MMC_ProcLmmPlmnSearchStopCnf_PlmnList();

            break;

            default:
                NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmPlmnSrchCnf_PlmnList_WaitLmmPlmnSearchStopCnf: Unexpected List Search Result!");
                PS_MEM_FREE(WUEPS_PID_MMC, pstGuPlmnIdList);
                return VOS_TRUE;
        }


    return VOS_TRUE;
}



VOS_UINT32  NAS_MMC_RcvTiWaitLmmStopCnfExpired_PlmnList_WaitLmmPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitLmmStopCnfExpired_PlmnList_WaitLmmPlmnSearchStopCnf: Timer Expired");

    /* ��������ֹͣ�ظ���� */
    NAS_MMC_ProcLmmPlmnSearchStopCnf_PlmnList();

    return VOS_TRUE;
}


#endif

/*********************************************************************************/
/*************************PLMN LIST��������***************************************/
/*********************************************************************************/

VOS_UINT32  NAS_MMC_IsUserPlmnList_PlmnList(VOS_VOID)
{
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg    = VOS_NULL_PTR;

   /* ����FSM ID��ȡ��FSM �����Ϣ */
    pstEntryMsg     = NAS_MMC_GetCurrFsmMsgAddr();

    if ( (ID_MSCC_MMC_PLMN_LIST_REQ == NAS_ExtractMsgNameFromEvtType(pstEntryMsg->ulEventType))
      || (TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST == NAS_ExtractMsgNameFromEvtType(pstEntryMsg->ulEventType)))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_VOID NAS_MMC_ProcFsmAbort_PlmnList(VOS_VOID)
{
    /* ��Ҫ��MSCC�ظ���� */
    if ( VOS_TRUE == NAS_MMC_GetNotifyMsccFlag_PlmnList())
    {
        if (VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
        {
            NAS_MMC_SndMsccPlmnListAbortCnf_PlmnList();
            return;
        }

#if (FEATURE_ON == FEATURE_CSG)
        if (VOS_TRUE == NAS_MMC_IsCsgList_PlmnList())
        {
            NAS_MMC_SndMsccCsgListAbortCnf_PlmnList();
        }
#endif
    }
    else
    {
        NAS_MMC_SndMsccListSearchCnfMsg_PlmnList();
    }

    return;
}


VOS_VOID NAS_MMC_SndMsccListSearchCnfMsg_PlmnList(VOS_VOID)
{
    if (VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
    {
        /* ������ͨLIST������� */
        NAS_MMC_SndMsccPlmnListCnf_PlmnList();
        return;
    }

#if (FEATURE_ON == FEATURE_CSG)
    if (VOS_TRUE == NAS_MMC_IsCsgList_PlmnList())
    {
        /* ����CSG LIST������� */
        NAS_MMC_SndMsccCsgListSearchCnf_PlmnList();
    }
#endif

    return;
}


VOS_VOID NAS_MMC_StartPeriodTryingUserListSrchTimer_PlmnList(VOS_VOID)
{

    if (VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
    {
        /* ����5S�����Գ���LIST������ʱ�� */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST, TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST_LEN);
        return;
    }


#if (FEATURE_ON == FEATURE_CSG)
    if (VOS_TRUE == NAS_MMC_IsCsgList_PlmnList())
    {
        /* ����5S�����Գ���CSG LIST������ʱ�� */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH, TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH_LEN);
    }
#endif

    return;
}




VOS_VOID NAS_MMC_SndMsccPlmnListRejMsg_PlmnList(VOS_VOID)
{
    if (VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
    {
        /* ����LIST REJ��MSCC */
        NAS_Mmc_SndMsccPlmnListRej();
        return;
    }

#if (FEATURE_ON == FEATURE_CSG)
    if (VOS_TRUE == NAS_MMC_IsCsgList_PlmnList())
    {
        /* ����CSG LIST REJ��MSCC */
        NAS_MMC_SndMsccCsgListSearchRej();
    }
#endif
    return;
}




VOS_UINT32  NAS_MMC_IsNeedAnyCellSrch_PlmnList(VOS_VOID)
{
    /* ����Ч�������Ҫ�ж���L1�Ƿ��Ѿ����й�anycell����
       ����Ѿ����й�anycell������LIST�����˳�����Ҫ�ظ�
       ����anycell����;����LIST���˳�����Ҫ����һ��anycell
       ���� */
    if (VOS_FALSE == NAS_MML_IsUsimStausValid())
    {
        /* RRC���Ӵ���˵��δ����������LIST����״̬����ȴ�RRC�����ͷ�
           RRC���Ӳ������ҽ�������״̬˵���Ѿ����й�������δ��� */
        if (VOS_TRUE == NAS_MML_IsRrcConnExist())
        {
            return VOS_TRUE;
        }

        if(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == NAS_MMC_GetSpecPlmnSearchState())
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_UINT32 NAS_MMC_IsPrefBandListSearchScene_PlmnList(VOS_VOID)
{
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg     = VOS_NULL_PTR;
    NAS_MMC_INTER_PLMN_LIST_REQ_STRU   *pstInternalMsg  = VOS_NULL_PTR;

    /* ����FSM ID��ȡ��FSM �����Ϣ */
    pstEntryMsg     = NAS_MMC_GetCurrFsmMsgAddr();

    if (MMCMMC_INTER_PLMN_LIST_REQ == NAS_ExtractMsgNameFromEvtType(pstEntryMsg->ulEventType))
    {
        pstInternalMsg  = (NAS_MMC_INTER_PLMN_LIST_REQ_STRU *)pstEntryMsg->aucEntryMsgBuffer;

        /* ��Ҫ��list prefband�ѵ��������� */
        if (NAS_MMC_PLMN_LIST_SEARCH_SCENE_PREFBAND_PLMN_SEARCH == pstInternalMsg->enListPlmnSearchScene)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_UINT32 NAS_MMC_IsNeedStopPlmnListSrchRcvSearchedPlmnInMaualMode_PLmnList(
    NAS_MML_PLMN_ID_STRU               *pstUserSpecPlmnId,
    NAS_MML_PLMN_ID_STRU               *pstCurrCampPlmnId,
    NAS_MML_PLMN_ID_STRU               *pstSearchedPlmnId
)
{
    /* ��ǰפ�����û�ָ�������� */
    if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstUserSpecPlmnId, pstCurrCampPlmnId))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedStopPlmnListSrchRcvSearchedPlmnInMaualMode_PLmnList: Current camp plmn is user spec plmn. ");

        /* ���������������û�ָ�����磬����� */
        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstUserSpecPlmnId, pstSearchedPlmnId))
        {
            NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedStopPlmnListSrchRcvSearchedPlmnInMaualMode_PLmnList: Searched plmn is user spec plmn. ");

            return VOS_FALSE;
        }

        /* ���������������û�ָ�������EPLMN����� */
        if (VOS_TRUE == NAS_MML_IsPlmnInEplmnList(pstSearchedPlmnId))
        {
            NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedStopPlmnListSrchRcvSearchedPlmnInMaualMode_PLmnList: Searched plmn is EPLMN. ");

            return VOS_TRUE;
        }

        return VOS_FALSE;
    }

    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedStopPlmnListSrchRcvSearchedPlmnInMaualMode_PLmnList: Current camp plmn is not user spec plmn. ");

    /* ��ǰδפ�����û�ָ��������,���������������û�ָ�������磬��� */
    if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstUserSpecPlmnId, pstSearchedPlmnId))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedStopPlmnListSrchRcvSearchedPlmnInMaualMode_PLmnList: Searched plmn is user spec plmn. ");

        return VOS_TRUE;
    }

    return VOS_FALSE;
}



VOS_UINT32 NAS_MMC_IsNeedStopPlmnListSrchRcvSearchedPlmnInAutoMode_PLmnList(
    NAS_MMC_ROAM_PLMN_INFO_STRU        *pstSearchedPlmnInfo,
    NAS_MMC_ROAM_PLMN_INFO_STRU        *pstCurrCampPlmnInfo,
    NAS_MML_LAI_STRU                   *pstLai,
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU  *pstDPlmnNPlmnCfgInfo
)
{
    VOS_UINT32                          ulIsCurrCampHplmn;
    VOS_UINT8                           ucSearchedPlmnPrio;
    VOS_UINT8                           ucCurrCampPlmnPrio;

    ulIsCurrCampHplmn        = VOS_FALSE;

    /* ����������������פ����������ͬ������� */
    if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&pstSearchedPlmnInfo->stPlmnWithRat.stPlmnId,
                                                       &pstCurrCampPlmnInfo->stPlmnWithRat.stPlmnId))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedStopPlmnListSrchRcvSearchedPlmnInAutoMode_PLmnList: Searched plmn MCC is equal to camp plmn MCC. ");

        return VOS_FALSE;
    }

    /* ������������ΪFPLMN,����� */
    if (NAS_MML_PLMN_FORBID_NULL != NAS_MML_GetLaiForbType(pstLai))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedStopPlmnListSrchRcvSearchedPlmnInAutoMode_PLmnList: Searched plmn is FPLMN. ");

        return VOS_FALSE;
    }

    /* ��������������NPLMN�б��У������ */
    if (VOS_TRUE == NAS_MMC_IsPlmnIdWithRatInSimPlmnWithRegDomainList(&pstSearchedPlmnInfo->stPlmnWithRat,
                      pstDPlmnNPlmnCfgInfo->usNplmnListNum, pstDPlmnNPlmnCfgInfo->astNPlmnList))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedStopPlmnListSrchRcvSearchedPlmnInAutoMode_PLmnList: Searched plmn is NPLMN. ");

        return VOS_FALSE;
    }

    /* ������HPLMN����� */
    if (VOS_TRUE == NAS_MML_ComparePlmnIdWithHplmn(&pstSearchedPlmnInfo->stPlmnWithRat.stPlmnId))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedStopPlmnListSrchRcvSearchedPlmnInAutoMode_PLmnList: Searched plmn is HPLMN. ");

        return VOS_TRUE;
    }

    /* ������RPLMN����� */
    if (VOS_TRUE == NAS_MMC_IsPlmnSameWithRplmn(&pstSearchedPlmnInfo->stPlmnWithRat.stPlmnId))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedStopPlmnListSrchRcvSearchedPlmnInAutoMode_PLmnList: Searched plmn is RPLMN. ");

        return VOS_TRUE;
    }

    /* ��������plmn�뵱ǰפ��plmn MCC��ͬ */
    if (VOS_FALSE == NAS_MML_IsPlmnMccBelongToTheSameCountry(pstCurrCampPlmnInfo->stPlmnWithRat.stPlmnId.ulMcc,
                                                             pstSearchedPlmnInfo->stPlmnWithRat.stPlmnId.ulMcc))
    {
        /* ��ͬMCC�ұ�������plmn��DPLMN/UPLMN/OPLMNʱ����� */
        if (VOS_TRUE == NAS_MMC_IsPlmnIdWithRatInSimPlmnWithRegDomainList(&pstSearchedPlmnInfo->stPlmnWithRat,
                        pstDPlmnNPlmnCfgInfo->usDplmnListNum, pstDPlmnNPlmnCfgInfo->astDPlmnList))
        {
            NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedStopPlmnListSrchRcvSearchedPlmnInAutoMode_PLmnList: Searched plmn is DPLMN. ");

            return VOS_TRUE;
        }

        if (VOS_TRUE == NAS_MMC_ComparePlmnIdWithRatWithUplmn(&pstSearchedPlmnInfo->stPlmnWithRat))
        {
            NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedStopPlmnListSrchRcvSearchedPlmnInAutoMode_PLmnList: Searched plmn is UPLMN. ");

            return VOS_TRUE;
        }

        if (VOS_TRUE == NAS_MMC_ComparePlmnIdWithRatWithOplmn(&pstSearchedPlmnInfo->stPlmnWithRat))
        {
            NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedStopPlmnListSrchRcvSearchedPlmnInAutoMode_PLmnList: Searched plmn is OPLMN. ");

            return VOS_TRUE;
        }



        return VOS_FALSE;
    }

    /* MCC��ͬʱ����ǰפ����RPLMN��HPLMNʱ������� */
    ulIsCurrCampHplmn = NAS_MML_ComparePlmnIdWithHplmn(&pstCurrCampPlmnInfo->stPlmnWithRat.stPlmnId);

    if ((VOS_TRUE == NAS_MMC_IsPlmnSameWithRplmn(&pstCurrCampPlmnInfo->stPlmnWithRat.stPlmnId))
      ||(VOS_TRUE == ulIsCurrCampHplmn))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedStopPlmnListSrchRcvSearchedPlmnInAutoMode_PLmnList: Current camp plmn is HPLMN or RPLMN. ");

        return VOS_FALSE;
    }


    /* ��ͬMCC��������plmn���ȼ����ڵ�ǰפ��plmnʱ����Ҫ��� */
    ucSearchedPlmnPrio = NAS_MMC_GetRoamPlmnPrio(pstSearchedPlmnInfo);
    ucCurrCampPlmnPrio = NAS_MMC_GetRoamPlmnPrio(pstCurrCampPlmnInfo);

    if (ucSearchedPlmnPrio > ucCurrCampPlmnPrio)
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedStopPlmnListSrchRcvSearchedPlmnInAutoMode_PLmnList: Searched plmn is superior to current camp plmn. ");

        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 NAS_MMC_IsNeedStopPlmnListSearchRcvRrcSearchedPlmnInfoInd_PlmnList(
    RRMM_SEARCHED_PLMN_INFO_IND_STRU   *pstSearchedPlmnInfoMsg,
    NAS_MML_PLMN_WITH_RAT_STRU         *pstAbortPlmn
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurrCampPlmnId    = VOS_NULL_PTR;
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstUserSpecPlmn      = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                                        stLai;
    NAS_MMC_ROAM_PLMN_INFO_STRU                             stSearchedPlmnInfo;
    NAS_MMC_ROAM_PLMN_INFO_STRU                             stCurrCampPlmnInfo;
    VOS_UINT32                                              ulIndex;
    VOS_UINT32                                              ulIsFullBandScene;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enNasRat;

    pstCurrCampPlmnId        = NAS_MML_GetCurrCampPlmnInfo();
    pstDPlmnNPlmnCfgInfo     = NAS_MMC_GetDPlmnNPlmnCfgInfo();
    pstUserSpecPlmn          = NAS_MMC_GetUserSpecPlmnId();
    ulIsFullBandScene        = NAS_MMC_IsFullBandListSearchScene_PlmnList();

    PS_MEM_SET(&stLai, 0x00, sizeof(NAS_MML_LAI_STRU));
    PS_MEM_SET(&stSearchedPlmnInfo, 0x00, sizeof(NAS_MMC_ROAM_PLMN_INFO_STRU));
    PS_MEM_SET(&stCurrCampPlmnInfo, 0x00, sizeof(NAS_MMC_ROAM_PLMN_INFO_STRU));

    stCurrCampPlmnInfo.stPlmnWithRat.stPlmnId.ulMcc = pstCurrCampPlmnId->stLai.stPlmnId.ulMcc;
    stCurrCampPlmnInfo.stPlmnWithRat.stPlmnId.ulMnc = pstCurrCampPlmnId->stLai.stPlmnId.ulMnc;
    stCurrCampPlmnInfo.stPlmnWithRat.enRat          = pstCurrCampPlmnId->enNetRatType;
    stCurrCampPlmnInfo.enNetStatus                  = NAS_MMC_NET_STATUS_SEARCHED_REGISTERED;
    stCurrCampPlmnInfo.enPlmnType                   = NAS_MMC_PLMN_TYPE_BUTT;
    stCurrCampPlmnInfo.aucLac[0]                    = NAS_MML_LAC_LOW_BYTE_INVALID;
    stCurrCampPlmnInfo.aucLac[1]                    = NAS_MML_LAC_HIGH_BYTE_INVALID;

    if (NAS_RRC_MAX_AVAILPLMN_NUM <= pstSearchedPlmnInfoMsg->ulAvailPlmnNum)
    {
        pstSearchedPlmnInfoMsg->ulAvailPlmnNum = NAS_RRC_MAX_AVAILPLMN_NUM;
    }

    /* ����pref band list������full band list��������� */
    if ((VOS_FALSE == NAS_MMC_IsPrefBandListSearchScene_PlmnList())
     && (VOS_FALSE == ulIsFullBandScene))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedStopPlmnListSearchRcvRrcSearchedPlmnInfoInd_PlmnList: is not pref band list or full band list scene");

        return VOS_FALSE;
    }

    /* ��ϲ���:
    1. �����������������NPLMN������FPLMN������Ҫ���
    2. ���������������Ȳ���NPLMNҲ����FPLMN���жϱ�������plmn�뵱ǰפ����plmn MCC�Ƿ���ͬ:
       �������ͬ���ұ�������plmn��RPLMN/HPLMN/DPLMN�е�һ��ʱ����Ҫ���;
       �����ͬ���ұ�������plmn���ȼ����ڵ�ǰפ��plmnʱ����Ҫ���
    3. �����������Ҫ���
    */

    for (ulIndex = 0; ulIndex < pstSearchedPlmnInfoMsg->ulAvailPlmnNum; ulIndex++)
    {
        /* ��������������ת��ΪNAS_MMC_ROAM_PLMN_INFO_STRU��ʽ */
        stSearchedPlmnInfo.stPlmnWithRat.stPlmnId.ulMcc = pstSearchedPlmnInfoMsg->astPlmnWithLacList[ulIndex].stPlmnId.ulMcc;
        stSearchedPlmnInfo.stPlmnWithRat.stPlmnId.ulMnc = pstSearchedPlmnInfoMsg->astPlmnWithLacList[ulIndex].stPlmnId.ulMnc;

        NAS_MMC_ConvertRrcRatToNasFormat(pstSearchedPlmnInfoMsg->astPlmnWithLacList[ulIndex].ulRat, &enNasRat);
        stSearchedPlmnInfo.stPlmnWithRat.enRat          = enNasRat;

        stSearchedPlmnInfo.enNetStatus = NAS_MMC_NET_STATUS_SEARCHED_EXIST;
        stSearchedPlmnInfo.enPlmnType  = NAS_MMC_PLMN_TYPE_BUTT;
        stSearchedPlmnInfo.aucLac[0]   = (pstSearchedPlmnInfoMsg->astPlmnWithLacList[ulIndex].usLac & 0xFF00) >> 8;
        stSearchedPlmnInfo.aucLac[1]   = (pstSearchedPlmnInfoMsg->astPlmnWithLacList[ulIndex].usLac & 0x00FF);

        stLai.stPlmnId         = stSearchedPlmnInfo.stPlmnWithRat.stPlmnId;
        stLai.enCampPlmnNetRat = stSearchedPlmnInfo.stPlmnWithRat.enRat;
        stLai.aucLac[0]        = stSearchedPlmnInfo.aucLac[0];
        stLai.aucLac[1]        = stSearchedPlmnInfo.aucLac[1];
        stLai.ucRac            = NAS_MML_RAC_INVALID;

        /* �ֶ�����ģʽ��������ж� */
        if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
        {

            if (VOS_TRUE == NAS_MMC_IsNeedStopPlmnListSrchRcvSearchedPlmnInMaualMode_PLmnList(&pstUserSpecPlmn->stPlmnId,
                                                                                               &pstCurrCampPlmnId->stLai.stPlmnId,
                                                                                               &stSearchedPlmnInfo.stPlmnWithRat.stPlmnId))
            {
                pstAbortPlmn->enRat             = stSearchedPlmnInfo.stPlmnWithRat.enRat;
                pstAbortPlmn->stPlmnId.ulMcc    = stSearchedPlmnInfo.stPlmnWithRat.stPlmnId.ulMcc;
                pstAbortPlmn->stPlmnId.ulMnc    = stSearchedPlmnInfo.stPlmnWithRat.stPlmnId.ulMnc;

                return VOS_TRUE;
            }

            continue;
        }

        /* �Զ�����ģʽ��������ж� */
        if (VOS_TRUE == NAS_MMC_IsNeedStopPlmnListSrchRcvSearchedPlmnInAutoMode_PLmnList(&stSearchedPlmnInfo,
                                                                                          &stCurrCampPlmnInfo,
                                                                                          &stLai,
                                                                                          pstDPlmnNPlmnCfgInfo))
        {
            pstAbortPlmn->enRat             = stSearchedPlmnInfo.stPlmnWithRat.enRat;
            pstAbortPlmn->stPlmnId.ulMcc    = stSearchedPlmnInfo.stPlmnWithRat.stPlmnId.ulMcc;
            pstAbortPlmn->stPlmnId.ulMnc    = stSearchedPlmnInfo.stPlmnWithRat.stPlmnId.ulMnc;

            return VOS_TRUE;
        }
        else
        {
            continue;
        }
    }

    return VOS_FALSE;
}


VOS_UINT32 NAS_MMC_IsFullBandListSearchScene_PlmnList(VOS_VOID)
{
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg     = VOS_NULL_PTR;
    NAS_MMC_INTER_PLMN_LIST_REQ_STRU   *pstInternalMsg  = VOS_NULL_PTR;

    /* ����FSM ID��ȡ��FSM �����Ϣ */
    pstEntryMsg     = NAS_MMC_GetCurrFsmMsgAddr();

    if (MMCMMC_INTER_PLMN_LIST_REQ == NAS_ExtractMsgNameFromEvtType(pstEntryMsg->ulEventType))
    {
        pstInternalMsg  = (NAS_MMC_INTER_PLMN_LIST_REQ_STRU *)pstEntryMsg->aucEntryMsgBuffer;

        /* ��Ҫ��list fullband�ѵ��������� */
        if (NAS_MMC_PLMN_LIST_SEARCH_SCENE_FULLBAND_PLMN_SEARCH == pstInternalMsg->enListPlmnSearchScene)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


NAS_MMC_PLMN_LIST_SEARCH_SCENE_ENUM_UINT8 NAS_MMC_GetPlmnListSearchScene_PlmnList(
    VOS_UINT8                                               ucNeedPlmnSearch
)
{
    NAS_MMC_PLMN_LIST_SEARCH_SCENE_ENUM_UINT8               enPlmnListSearchScene;
#if (FEATURE_ON == FEATURE_LTE)
        NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32           enLteCapStatus;

        enLteCapStatus        = NAS_MML_GetLteCapabilityStatus();
#endif

    enPlmnListSearchScene = NAS_MMC_PLMN_LIST_SEARCH_SCENE_BUTT;

    if (VOS_TRUE == NAS_MMC_IsPrefBandListSearchScene_PlmnList())
    {
        return NAS_MMC_PLMN_LIST_SEARCH_SCENE_PREFBAND_PLMN_SEARCH;
    }

    if (VOS_TRUE == NAS_MMC_IsFullBandListSearchScene_PlmnList())
    {
        return NAS_MMC_PLMN_LIST_SEARCH_SCENE_FULLBAND_PLMN_SEARCH;
    }

    /* �����Ҫ����������Ҫ������������ */
    if (VOS_TRUE == ucNeedPlmnSearch)
    {
        /* List��֮ǰLte û��disable����List��״̬���﷢��disable lte������������Ϊdisable lte */
#if (FEATURE_ON == FEATURE_LTE)
        if ((VOS_FALSE == NAS_MMC_GetPreLteDisableFlg_PlmnList())
         && ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == enLteCapStatus)
          || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLteCapStatus)))
        {
            enPlmnListSearchScene = NAS_MMC_PLMN_LIST_SEARCH_SCENE_DISABLE_LTE;
        }
#endif
        else
        {
            enPlmnListSearchScene = NAS_MMC_PLMN_LIST_SEARCH_SCENE_USER_LIST;
        }
    }

    return enPlmnListSearchScene;

}



VOS_VOID NAS_MMC_ProcCsRegRslt_PlmnList(
    MMMMC_CS_REG_RESULT_IND_STRU       *pstCsRegRsltInd
)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_GU_ACTION_RSLT_INFO_STRU                        stActionRslt;
#endif

    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo = VOS_NULL_PTR;
    pstDPlmnNPlmnCfgInfo  = NAS_MMC_GetDPlmnNPlmnCfgInfo();

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));



    if (MM_MMC_LU_RESULT_SUCCESS == pstCsRegRsltInd->enLuResult)
    {
        enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

        /* ����ע��������ע����Ϣ�� */
        NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_CS, NAS_MML_REG_FAIL_CAUSE_NULL);

        /* ����DPLMN NPLMN�б� */
        if (VOS_TRUE == NAS_MMC_IsRoam())
        {
            NAS_MMC_UpdateDPlmnNPlmnList(NAS_MML_GetCurrCampLai(), NAS_MMC_REG_DOMAIN_CS, NAS_MMC_MAX_CFG_DPLMN_NUM, &pstDPlmnNPlmnCfgInfo->usDplmnListNum, pstDPlmnNPlmnCfgInfo->astDPlmnList);
            NAS_MMC_DeleteDPlmnNPlmnList(NAS_MML_GetCurrCampLai(), NAS_MMC_REG_DOMAIN_CS, &pstDPlmnNPlmnCfgInfo->usNplmnListNum, pstDPlmnNPlmnCfgInfo->astNPlmnList);
            NAS_MMC_WriteSelfLearnDplmnNplmnToNvim(pstDPlmnNPlmnCfgInfo);

            NAS_MMC_LogDplmnNplmnList();
        }

        /* ��Hplmn��Rej Lai��Ϣ����� */
        NAS_MMC_ClearHplmnRejDomainInfo(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_CS);

        /* ע��ɹ�ʱ����Ҫɾ��ForbPlmn,ForbLa,ForbGprs����Ϣ */
        NAS_MMC_DelForbInfo_GuRegRsltSucc(NAS_MMC_REG_DOMAIN_CS);

        NAS_MMC_SetUserSpecPlmnRegisterStatus(VOS_TRUE);

        NAS_MMC_UpdateCsRegStateCsRegSucc();

        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_NORMAL_SERVICE);

#if   (FEATURE_ON == FEATURE_LTE)

        /* ��ǰSYSCFG��L����ʱ����Ҫ��LMM֪ͨ */
        /* ����ע��ʱ��֪ͨLMM��ʱLU�Ľ�� */
        if ((VOS_TRUE  == NAS_MML_IsRegFailCauseNotifyLmm(pstCsRegRsltInd->enRegFailCause))
         && (VOS_FALSE == pstCsRegRsltInd->ucIsComBined))
        {
            stActionRslt.enProcType     = NAS_MML_PROC_LAU;
            stActionRslt.enRegRst       = NAS_MML_REG_RESULT_SUCCESS;
            stActionRslt.enReqDomain    = NAS_MMC_REG_DOMAIN_CS;
            stActionRslt.enRstDomain    = NAS_MMC_REG_DOMAIN_CS;
            stActionRslt.enCnCause      = NAS_MML_REG_FAIL_CAUSE_NULL;
            stActionRslt.ulAttemptCount = 0;

            NAS_MMC_SndLmmRegActionResultReq(&stActionRslt);
        }
#endif

        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_CS, VOS_TRUE, pstCsRegRsltInd->enRegFailCause);
    }
    else
    {
        enAdditionalAction = NAS_MMC_ProcCsRegFail(MM_MMC_CS_REG_RESULT_IND,
                                                   pstCsRegRsltInd);

        if ( VOS_TRUE == NAS_MML_IsNetworkRegFailCause(pstCsRegRsltInd->enRegFailCause) )
        {
            /* ֻ�ڸ�������ʵ����������ʱ��Ÿ���ע����Ϣ�� */
            NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_CS, pstCsRegRsltInd->enRegFailCause);

            /* ����DPLMN NPLMN�б� */
            if (VOS_TRUE == NAS_MMC_IsRoam())
            {
                NAS_MMC_UpdateDPlmnNPlmnList(NAS_MML_GetCurrCampLai(), NAS_MMC_REG_DOMAIN_CS, NAS_MMC_MAX_CFG_NPLMN_NUM, &pstDPlmnNPlmnCfgInfo->usNplmnListNum, pstDPlmnNPlmnCfgInfo->astNPlmnList);
                NAS_MMC_DeleteDPlmnNPlmnList(NAS_MML_GetCurrCampLai(), NAS_MMC_REG_DOMAIN_CS, &pstDPlmnNPlmnCfgInfo->usDplmnListNum, pstDPlmnNPlmnCfgInfo->astDPlmnList);
                NAS_MMC_WriteSelfLearnDplmnNplmnToNvim(pstDPlmnNPlmnCfgInfo);

                NAS_MMC_LogDplmnNplmnList();
            }

        }

        NAS_MMC_UpdateUserSpecPlmnRegisterStatusWhenRegFail(pstCsRegRsltInd->enRegFailCause);

#if   (FEATURE_ON == FEATURE_LTE)

        /* С�� NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE�ľܾ�ԭ����UE���Է���ע���ԭ��ֵ����Ҫ֪ͨLMM */
        /* ����ע��ʱ��֪ͨLMM��ʱLU�Ľ�� */
        if ((VOS_TRUE  == NAS_MML_IsRegFailCauseNotifyLmm(pstCsRegRsltInd->enRegFailCause))
         && (VOS_FALSE == pstCsRegRsltInd->ucIsComBined))
        {
            /* ��ǰSYSCFG��L����ʱ����Ҫ��LMM֪ͨ */
            stActionRslt.enProcType     = NAS_MML_PROC_LAU;
            stActionRslt.enRegRst       = NAS_MML_REG_RESULT_FAILURE;
            stActionRslt.enReqDomain    = NAS_MMC_REG_DOMAIN_CS;
            stActionRslt.enRstDomain    = NAS_MMC_REG_DOMAIN_CS;
            stActionRslt.enCnCause      = pstCsRegRsltInd->enRegFailCause;
            stActionRslt.ulAttemptCount = pstCsRegRsltInd->ulLuAttemptCnt;

            NAS_MMC_SndLmmRegActionResultReq(&stActionRslt);
        }
#endif
    }


    /* AdditionalAction��Ч������CS����һ���Ķ������� */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
    {
        NAS_MMC_SetCsRegAdditionalAction_PlmnList(enAdditionalAction);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn())
    {
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndGuAsEquPlmnReq(&stSndEquPlmnInfo, NAS_MML_GetCurrNetRatType());
        NAS_MMC_SndOmEquPlmn();

        NAS_MMC_SndMsccEplmnInfoInd(&stSndEquPlmnInfo);

        /* ֪ͨCSS GEO��Ϣ */
        NAS_MMC_SndCssCurrGeoInd(VOS_TRUE, stSndEquPlmnInfo.ucEquPlmnNum, stSndEquPlmnInfo.astEquPlmnAddr);
    }

    return;
}


VOS_VOID NAS_MMC_ProcPsRegRslt_PlmnList(
    GMMMMC_PS_REG_RESULT_IND_STRU      *pstPsRegRsltInd
)
{
    NAS_MML_LAI_STRU                                       *pstLai         = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_GU_ACTION_RSLT_INFO_STRU                        stActionRslt;
    NAS_MML_PROC_TYPE_ENUM_U32                              enProcType;

    /* ת�����͸�L��proctype */
    enProcType = NAS_MML_PROC_BUTT;

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    NAS_MMC_ConverGmmActionTypeToMml(pstPsRegRsltInd->enGmmActionType, &enProcType);


    NAS_MMC_ConvertGmmRegDomainToMmcDomain(pstPsRegRsltInd->enReqDomain, &stActionRslt.enReqDomain);

    NAS_MMC_ConvertGmmRegDomainToMmcDomain(pstPsRegRsltInd->enRsltDomain, &stActionRslt.enRstDomain);



#endif
    pstLai              = NAS_MML_GetCurrCampLai();



    if (GMM_MMC_ACTION_RESULT_SUCCESS == pstPsRegRsltInd->enActionResult)
    {
        enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

        /* ����ע������Ϣ */
        NAS_MMC_SaveRegRsltCtx(GMM_MMC_PS_REG_RESULT_IND, pstPsRegRsltInd);

        /* ����ע��������ע����Ϣ�� */
        NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_PS, NAS_MML_REG_FAIL_CAUSE_NULL);

        NAS_MMC_ClearHplmnRejDomainInfo(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_PS);

        if (VOS_TRUE == NAS_MML_GetKeepCsForbInfoCfg())
        {
            /* ֻɾ��Forb GPRS PLMN��Ϣ��CS���FORB��Ϣ��Ȼ���� */
            NAS_MML_DelForbGprsPlmn(&(pstLai->stPlmnId));
        }
        else
        {
            /* ע��ɹ�ʱ����Ҫɾ��ForbPlmn,ForbLa,ForbGprs����Ϣ */
            NAS_MMC_DelForbInfo_GuRegRsltSucc(NAS_MMC_REG_DOMAIN_PS);
        }



        NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                                 NAS_MML_GetSimPsRegStatus());


        NAS_MMC_SetUserSpecPlmnRegisterStatus(VOS_TRUE);

        NAS_MMC_UpdatePsRegStatePsRegSucc();

        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_NORMAL_SERVICE);

#if   (FEATURE_ON == FEATURE_LTE)

            /* ��ǰSYSCFG��L����ʱ����Ҫ��LMM֪ͨ */
            /* �����̲�֪ͨ��LMM */
            if ( VOS_TRUE == NAS_MML_IsRegFailCauseNotifyLmm(pstPsRegRsltInd->enRegFailCause) )
            {
                stActionRslt.enProcType     = enProcType;
                stActionRslt.enRegRst       = NAS_MML_REG_RESULT_SUCCESS;
                stActionRslt.enCnCause      = NAS_MML_REG_FAIL_CAUSE_NULL;
                stActionRslt.ulAttemptCount = 0;

                NAS_MMC_SndLmmRegActionResultReq(&stActionRslt);
            }

#endif

        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_PS, VOS_TRUE, pstPsRegRsltInd->enRegFailCause);
    }
    else
    {
        enAdditionalAction = NAS_MMC_ProcPsRegFail(GMM_MMC_PS_REG_RESULT_IND,
                                                   pstPsRegRsltInd);

        if ( VOS_TRUE == NAS_MML_IsNetworkRegFailCause(pstPsRegRsltInd->enRegFailCause) )
        {
            /* ֻ�ڸ�������ʵ����������ʱ��Ÿ���ע����Ϣ�� */
            NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_PS, pstPsRegRsltInd->enRegFailCause);
        }

        NAS_MMC_UpdateUserSpecPlmnRegisterStatusWhenRegFail(pstPsRegRsltInd->enRegFailCause);

#if   (FEATURE_ON == FEATURE_LTE)

        /* С�� NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE�ľܾ�ԭ����UE���Է���ע���ԭ��ֵ����Ҫ֪ͨLMM */
        if ( VOS_TRUE == NAS_MML_IsRegFailCauseNotifyLmm(pstPsRegRsltInd->enRegFailCause) )
        {
            /* ��ǰSYSCFG��L����ʱ����Ҫ��LMM֪ͨ */
            stActionRslt.enProcType     = enProcType;
            stActionRslt.enRegRst       = NAS_MML_REG_RESULT_FAILURE;
            stActionRslt.enCnCause      = pstPsRegRsltInd->enRegFailCause;
            stActionRslt.ulAttemptCount = pstPsRegRsltInd->ulRegCounter;

            NAS_MMC_SndLmmRegActionResultReq(&stActionRslt);
        }
#endif
    }

    /* AdditionalAction��Ч������PS����һ���Ķ������� */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_PlmnList(enAdditionalAction);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn())
    {
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndGuAsEquPlmnReq(&stSndEquPlmnInfo, NAS_MML_GetCurrNetRatType());
        NAS_MMC_SndOmEquPlmn();

        NAS_MMC_SndMsccEplmnInfoInd(&stSndEquPlmnInfo);

        /* ֪ͨCSS GEO��Ϣ */
        NAS_MMC_SndCssCurrGeoInd(VOS_TRUE, stSndEquPlmnInfo.ucEquPlmnNum, stSndEquPlmnInfo.astEquPlmnAddr);
    }

    return;

}


VOS_UINT32  NAS_MMC_IsNeedPlmnSearch_PlmnList(VOS_VOID)
{
    VOS_UINT32                                              ulIsNormalService;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_UE_OPERATION_MODE_ENUM_UINT8                enLUeMode;
    NAS_MML_ADDITION_UPDATE_RSLT_INFO_ENUM_UINT8            enAdditionUpdateRslt;

    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enPsRegCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegCause;

    enPsRegCause            = NAS_MML_REG_FAIL_CAUSE_NULL;
    enCsRegCause            = NAS_MML_REG_FAIL_CAUSE_NULL;
#endif

    ulIsNormalService = NAS_MMC_IsNormalServiceStatus();

    /* ��ǰ����Ч��Ϊ���Ʒ��� */
    if ((VOS_TRUE == NAS_MML_IsUsimStausValid())
     && (VOS_FALSE == ulIsNormalService))
    {
        return VOS_TRUE;
    }

    /* ��ǰNAS��������δפ������ */
    if (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == NAS_MMC_GetSpecPlmnSearchState())
    {
        return VOS_TRUE;
    }

    /* �����Ҫanycell����,�򷵻�true */
    if (VOS_TRUE == NAS_MMC_GetAnyCellSrchFlg_PlmnList())
    {
        return VOS_TRUE;
    }

    /* ����ע�����Դ�ʱ,��PS����CSע��ʧ��#17,��Ҫ�������� */
    if (VOS_TRUE == NAS_MMC_IsSingleDomainRegFailNeedPlmnSrch(NAS_MSCC_PIF_SRVDOMAIN_CS))
    {
        return VOS_TRUE;
    }
    if (VOS_TRUE == NAS_MMC_IsSingleDomainRegFailNeedPlmnSrch(NAS_MSCC_PIF_SRVDOMAIN_PS))
    {
        return VOS_TRUE;
    }

#if (FEATURE_ON == FEATURE_LTE)

    enLUeMode            = NAS_MML_GetLteUeOperationMode();
    enAdditionUpdateRslt = NAS_MML_GetAdditionUpdateRslt();

    /* ��ǰ��ģL */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
    {
        return VOS_FALSE;
    }

    /* ��ǰ���뼼����ΪLTE */
    if (NAS_MML_NET_RAT_TYPE_LTE != NAS_MML_GetCurrNetRatType())
    {
        return VOS_FALSE;
    }

    /* ����CS/PS mode 1��IMS VOICE���� */
    if ((VOS_TRUE                              == NAS_MML_GetImsVoiceAvailFlg())
     || (NAS_MML_LTE_UE_OPERATION_MODE_CS_PS_1 != enLUeMode))

    {
        return VOS_FALSE;
    }

    /* addition update ieΪ"SMS ONLY"��"CSFB not preferred" */
    if (VOS_TRUE == NAS_MMC_IsNeedDisableL_CombinedRegSuccAdditionUpdateRslt(enAdditionUpdateRslt))
    {
        return VOS_TRUE;
    }

    /* ��ǰפ��������ԭ��ֵ#18�б��� */
    if (VOS_TRUE == NAS_MML_IsPlmnIdInCsDomainUnAvailPlmnList(NAS_MML_GetCurrCampPlmnId()))
    {
        return VOS_TRUE;
    }

    /* NAS_MMC_GetRegRsltAttemptCounterΪ5 */
    if (NAS_MML_MAX_PS_REG_FAIL_CNT == NAS_MMC_GetRegRsltAttemptCounter(NAS_MMC_GetRegRsltType()))
    {
        /* ��ȡ֮ǰע��ʧ�ܵ�ԭ��ֵ */
       NAS_MMC_GetDomainRegStatusInRegInfoList(NAS_MML_GetCurrCampPlmnId(),
                                               NAS_MML_NET_RAT_TYPE_LTE,
                                               &enCsRegCause,
                                               &enPsRegCause);

        if (NAS_MML_REG_FAIL_CAUSE_PROCEDURE_CONGESTION == enCsRegCause)
        {
            return NAS_MMC_IsNeedDisableL_RegFailCause22AttmptCntMaxTimes();
        }

        /* 24301_CR1884R4_(Rel-11)_C1-140658-C1-140643-C1-140393-C1-140368-C1-140004-24301-b90-TA-IMSVoPS-EPS-only
          TAU ACCEPT��EPS ONLY�ɹ�������ԭ��ֵΪ16,17��CS/PS1��DIABLE LTE����������
          persistent EPS bearer�Ƿ���ڣ���Ӧ24301 5.5.3.3.4.3�½�:
              #16 and #17:a UE operating in CS/PS mode 1 of operation with "IMS voice not available"
          and with a persistent EPS bearer context shall wait until the radio bearer
          associated with the persistent EPS bearer context has been released. When
          the radio bearer associated with the persistent EPS bearer context has been
          released and the UE is registered for EPS services only, operating in CS/PS
          mode 1 of operation with "IMS voice not available", then the UE shall attempt
          to select GERAN or UTRAN radio access technology and proceed with appropriate
          MM or GMM specific procedures and disable the E-UTRA capability (see subclause 4.5).
          ��CR��Э��汾���� */
        if (NAS_MML_REG_FAIL_CAUSE_MSC_UNREACHABLE == enCsRegCause)
        {
            return NAS_MMC_IsNeedDisableL_RegFailCause16AttmptCntMaxTimes();
        }

        if (NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE == enCsRegCause)
        {
            return NAS_MMC_IsNeedDisableL_RegFailCause17AttmptCntMaxTimes();
        }

        return VOS_TRUE;
    }

#endif


    return VOS_FALSE;
}


VOS_VOID    NAS_MMC_SortSearchedPlmnList_PlmnList(
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstPlmnSearchList,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstReportList
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              ulRatNum;

    /* ��ʼ���б� */
    PS_MEM_SET(pstReportList, 0x0, sizeof(NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU));

    /* ��ѡ���б�������HPLMN��EHPLMN */
    NAS_MMC_AddEHPlmnInPlmnSelectionList(pstReportList);

    /* ��ѡ���б�������UPLMN��OPLMN */
    NAS_MMC_AddUOPlmnInPlmnSelectionList(pstReportList);

    ulRatNum = NAS_MML_GetMsPrioRatList()->ucRatNum;

    /* ���¸����ȼ����б�״̬������ʣ�µĸߵ��������� */
    for(i = 0; i < ulRatNum; i++)
    {
        /* ���������Ҫ��ʣ�����粹�䵽�б� */

        NAS_MMC_UpdatePlmnListInPlmnSelectionList((&pstPlmnSearchList[i]),
                                                  pstReportList,
                                                  VOS_TRUE,
                                                  VOS_TRUE);
    }

    /*���¶Ըߵ����������������*/
    NAS_MMC_SortAvailPlmnInPlmnSelectionList(pstReportList);
}


VOS_VOID NAS_MMC_GetPlmnStatus_PlmnList(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    VOS_UINT8                          *pucStatus,
    VOS_UINT16                          usRaMode
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enOrigNetType;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbidPlmnInfo;
    NAS_MML_PLMN_ID_STRU               *pstCurPlmnId = VOS_NULL_PTR;

    /* ��ǰ�ڷ�פ��״̬�£�˫ģʱ���л�����һ��ģʽ�·����б�������
       ����פ��״̬�£��ڵ�ǰģʽ�¾Ϳ��԰�����ģʽ�µ�PLMN���������ϱ�������
       ����Ҫ������������ֱ��ȡRPLMN��RAT */
    if (NAS_MMC_AS_CELL_NOT_CAMP_ON == NAS_MMC_GetAsCellCampOn())
    {
        NAS_MMC_GetOrigenSearchRat_PlmnList(&enOrigNetType);
    }
    else
    {
        enOrigNetType = NAS_MML_GetCurrNetRatType();
    }

    /* ��ȡ��ֹ������Ϣ */
    pstForbidPlmnInfo = NAS_MML_GetForbidPlmnInfo();


    /* ��forbid plmn�б��� */
    if(VOS_TRUE == NAS_MML_IsBcchPlmnIdInDestSimPlmnList(pstPlmnId,
                                                  pstForbidPlmnInfo->ucForbPlmnNum,
                                                  pstForbidPlmnInfo->astForbPlmnIdList))
    {
        *pucStatus              = NAS_MSCC_PIF_PLMN_STATUS_FORBIDDEN;
    }
    else
    {
        *pucStatus              = NAS_MSCC_PIF_PLMN_STATUS_AVAILIBLE;
    }

    /*��PLMN���ڵ�ǰLAI��PLMNʱ,����Ϊ��״̬Ϊ��ǰ*/
    if (VOS_TRUE == NAS_MMC_IsNormalServiceStatus())
    {
        pstCurPlmnId = NAS_MML_GetCurrCampPlmnId();

        if ( (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstCurPlmnId, pstPlmnId))
            &&( usRaMode == enOrigNetType))
        {
            if (NAS_MSCC_PIF_PLMN_STATUS_FORBIDDEN != *pucStatus)
            {
                *pucStatus = NAS_MSCC_PIF_PLMN_STATUS_CURRENT;
            }
        }
    }

    return;
}


VOS_UINT32    NAS_MMC_BuildTafMmcPlmnListIndMsg_PlmnList(
    MMC_MSCC_PLMN_LIST_CNF_STRU          *pstSndTafMsg
)
{
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU  *pstReportList = VOS_NULL_PTR;
    VOS_UINT32                              i;
    VOS_UINT32                              j;

    NAS_MML_HPLMN_CFG_INFO_STRU            *pstHplmnCfgInfo = VOS_NULL_PTR;

    NAS_MML_DISABLED_RAT_PLMN_CFG_INFO_STRU                *pstDisabledRatPlmnCfg   = VOS_NULL_PTR;

    /* ��ȡ��ֹ���뼼����PLMN��Ϣ */
    pstDisabledRatPlmnCfg = NAS_MML_GetDisabledRatPlmnInfo();

    pstHplmnCfgInfo = NAS_MML_GetHplmnCfg();

    pstReportList   = (NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                                                           sizeof(NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU));
    if (VOS_NULL_PTR == pstReportList)
    {
        /* �쳣��ӡ */
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccPlmnListCnf_PlmnList: ALLOC MEM FAIL!");
        return VOS_FALSE;
    }

    PS_MEM_SET(pstSndTafMsg, 0, sizeof(MMC_MSCC_PLMN_LIST_CNF_STRU));
    pstSndTafMsg->MsgHeader.ulLength          = sizeof(MMC_MSCC_PLMN_LIST_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSndTafMsg->MsgHeader.ulMsgName         = ID_MMC_MSCC_PLMN_LIST_CNF;
    pstSndTafMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstSndTafMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndTafMsg->MsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstSndTafMsg->ulCnt                       = 0;

    /* ���������б��������� */
    NAS_MMC_SortSearchedPlmnList_PlmnList(NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                          pstReportList);

    /* ɾ���ظ���PLMN */
    NAS_MMC_DelDuplicatedPlmnWithRatInPlmnList(pstReportList);

    if (VOS_TRUE == pstHplmnCfgInfo->ucEhplmnSupportFlg)
    {
        if (NAS_MML_EHPLMN_PRESENT_IND_HIGHEST == NAS_MML_GetEHplmnPresentInd())
        {
            /* ���������ȼ���ߵ�EHPLMN,������EHPLMN��ɾ�� */
            NAS_MMC_DelLowPrioEHPlmn(pstReportList);
        }
    }

    /* ���ź�����б��е����������Ϣ�ṹ�� */
    for ( i = 0 ; i < pstReportList->usSearchPlmnNum; i++ )
    {
        /* �ж�PLMN�ں��������߲��ڰ����������ϱ� */
        if (VOS_TRUE == NAS_MML_IsPlmnIdForbiddenByWhiteBlackList(&(pstReportList->astPlmnSelectionList[i].stPlmnId)))
        {
            continue;
        }

        /* ɾ���ڽ�ֹ���뼼��������Ľ��뼼�� */
        NAS_MMC_DelPlmnSelectionRatInfoInDisabledPlmnWithForbiddenPeriodList(&(pstReportList->astPlmnSelectionList[i]),
                                                  pstDisabledRatPlmnCfg->ulDisabledRatPlmnNum,
                                                  pstDisabledRatPlmnCfg->astDisabledRatPlmnId);

        /* ɾ���ڽ�ֹRAT�б��еĽ��뼼�� */
        NAS_MMC_DeleteForbiddenRatInPlmnSeleInfo(&(pstReportList->astPlmnSelectionList[i]));

        /* ����������Ľ��뼼������Ϊ�㣬������ */
        if ( 0 == pstReportList->astPlmnSelectionList[i].ucRatNum )
        {
            continue;
        }

        /* ���ź������������PLMN�����ϱ���Ϣ�ṹ�� */
        for ( j = 0; j < pstReportList->astPlmnSelectionList[i].ucRatNum; j++)
        {
            if (( NAS_MMC_NET_STATUS_SEARCHED_EXIST == pstReportList->astPlmnSelectionList[i].astPlmnRatInfo[j].enNetStatus)
                && (pstSndTafMsg->ulCnt < NAS_MSCC_PIF_MAX_PLMN_CNT))
            {
                /* �Ѵ�PLMN���뵽�ϱ��б��� */
                pstSndTafMsg->aPlmnList[pstSndTafMsg->ulCnt].ulMcc
                                        = pstReportList->astPlmnSelectionList[i].stPlmnId.ulMcc;

                pstSndTafMsg->aPlmnList[pstSndTafMsg->ulCnt].ulMnc
                                        = pstReportList->astPlmnSelectionList[i].stPlmnId.ulMnc;

                pstSndTafMsg->aucRaMode[pstSndTafMsg->ulCnt]
                                        = pstReportList->astPlmnSelectionList[i].astPlmnRatInfo[j].enRatType;

                /* ��ȡ�б���ÿ��PLMN��״̬ */
                NAS_MMC_GetPlmnStatus_PlmnList((NAS_MML_PLMN_ID_STRU *)&(pstSndTafMsg->aPlmnList[pstSndTafMsg->ulCnt]),
                                               &(pstSndTafMsg->aucPlmnStatus[pstSndTafMsg->ulCnt]),
                                               pstSndTafMsg->aucRaMode[pstSndTafMsg->ulCnt]);

                pstSndTafMsg->ulCnt++;
            }
        }
    }

    /* �ڴ��ͷ� */
    PS_MEM_FREE(WUEPS_PID_MMC, pstReportList);

    return VOS_TRUE;
}



VOS_UINT32    NAS_MMC_BuildTafMmcPlmnListAbortCnfMsg_PlmnList(
    MMC_MSCC_PLMN_LIST_ABORT_CNF_STRU    *pstSndMsccMsg
)
{
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU  *pstReportList = VOS_NULL_PTR;
    VOS_UINT32                              i;
    VOS_UINT32                              j;

    pstReportList   = (NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                                                           sizeof(NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU));
    if (VOS_NULL_PTR == pstReportList)
    {
        /* �쳣��ӡ */
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_BuildTafMmcPlmnListAbortCnfMsg_PlmnList: ALLOC MEM FAIL!");
        return VOS_FALSE;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstReportList) + VOS_MSG_HEAD_LENGTH, 0, sizeof(NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU) - VOS_MSG_HEAD_LENGTH);
    pstSndMsccMsg->MsgHeader.ulLength          = sizeof(MMC_MSCC_PLMN_LIST_ABORT_CNF_STRU);
    pstSndMsccMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstSndMsccMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMsccMsg->MsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstSndMsccMsg->MsgHeader.ulMsgName         = ID_MMC_MSCC_PLMN_LIST_ABORT_CNF;
    pstSndMsccMsg->ulCnt                       = 0;

    /* ���������б��������� */
    NAS_MMC_SortSearchedPlmnList_PlmnList(NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                          pstReportList);

    /* ɾ���ظ���PLMN */
    NAS_MMC_DelDuplicatedPlmnWithRatInPlmnList(pstReportList);

    /* ���ź�����б��е����������Ϣ�ṹ�� */
    for ( i = 0 ; i < pstReportList->usSearchPlmnNum; i++ )
    {
        /* �ж�PLMN�ں��������߲��ڰ����������ϱ� */
         if (VOS_TRUE == NAS_MML_IsPlmnIdForbiddenByWhiteBlackList(&(pstReportList->astPlmnSelectionList[i].stPlmnId)))
         {
             continue;
         }

        /* ���ź������������PLMN�����ϱ���Ϣ�ṹ�� */
        for ( j = 0; j < pstReportList->astPlmnSelectionList[i].ucRatNum; j++)
        {
            if (( NAS_MMC_NET_STATUS_SEARCHED_EXIST == pstReportList->astPlmnSelectionList[i].astPlmnRatInfo[j].enNetStatus)
                && (pstSndMsccMsg->ulCnt < NAS_MSCC_PIF_MAX_PLMN_CNT))
            {
                /* �Ѵ�PLMN���뵽�ϱ��б��� */
                pstSndMsccMsg->aPlmnList[pstSndMsccMsg->ulCnt].ulMcc
                                        = pstReportList->astPlmnSelectionList[i].stPlmnId.ulMcc;

                pstSndMsccMsg->aPlmnList[pstSndMsccMsg->ulCnt].ulMnc
                                        = pstReportList->astPlmnSelectionList[i].stPlmnId.ulMnc;

                pstSndMsccMsg->aucRaMode[pstSndMsccMsg->ulCnt]
                                        = pstReportList->astPlmnSelectionList[i].astPlmnRatInfo[j].enRatType;

                /* ��ȡ�б���ÿ��PLMN��״̬ */
                NAS_MMC_GetPlmnStatus_PlmnList((NAS_MML_PLMN_ID_STRU *)&(pstSndMsccMsg->aPlmnList[pstSndMsccMsg->ulCnt]),
                                               &(pstSndMsccMsg->aucPlmnStatus[pstSndMsccMsg->ulCnt]),
                                               pstSndMsccMsg->aucRaMode[pstSndMsccMsg->ulCnt]);

                pstSndMsccMsg->ulCnt++;
            }
        }
    }

    /* �ڴ��ͷ� */
    PS_MEM_FREE(WUEPS_PID_MMC, pstReportList);

    return VOS_TRUE;
}


VOS_VOID NAS_MMC_SndMsccPlmnListCnf_PlmnList(VOS_VOID)
{
    MMC_MSCC_PLMN_LIST_CNF_STRU          *pstSndMsccMsg = VOS_NULL_PTR;

    pstSndMsccMsg   = (MMC_MSCC_PLMN_LIST_CNF_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                                              sizeof(MMC_MSCC_PLMN_LIST_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsccMsg)
    {
        /* �쳣��ӡ */
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccPlmnListCnf_PlmnList: ALLOC MEM FAIL!");
        return;
    }

    /* �����ϱ���Ϣ */
    if (VOS_TRUE != NAS_MMC_BuildTafMmcPlmnListIndMsg_PlmnList(pstSndMsccMsg))
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pstSndMsccMsg);
        return;
    }

    /* ��MSCC�����б��ѽ�� */
    NAS_MMC_SndMsccPlmnListInd(pstSndMsccMsg);

    /* OM �¼��ϱ� */
    if ( 0 == pstSndMsccMsg->ulCnt)
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
            VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_SUCCESS,
            VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);
    }

    PS_MEM_FREE(WUEPS_PID_MMC, pstSndMsccMsg);

    return;
}


VOS_VOID NAS_MMC_SndMsccPlmnListAbortCnf_PlmnList(VOS_VOID)
{
    MMC_MSCC_PLMN_LIST_ABORT_CNF_STRU  *pstSndMsccMsg = VOS_NULL_PTR;

    /* ��ȡ�����ȼ�����ĸ��� */
    pstSndMsccMsg   = (MMC_MSCC_PLMN_LIST_ABORT_CNF_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                                              sizeof(MMC_MSCC_PLMN_LIST_ABORT_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsccMsg)
    {
        /* �쳣��ӡ */
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccPlmnListAbortCnf_PlmnList: ALLOC MEM FAIL!");
        return;
    }

    /* �����ϱ���Ϣ */
    if (VOS_TRUE != NAS_MMC_BuildTafMmcPlmnListAbortCnfMsg_PlmnList(pstSndMsccMsg))
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pstSndMsccMsg);
        return;
    }

    /* ��MSCC�����б��ѽ�� */
    NAS_MMC_SndMsccPlmnListAbortCnf(pstSndMsccMsg);

    PS_MEM_FREE(WUEPS_PID_MMC, pstSndMsccMsg);

    return;
}


VOS_VOID NAS_MMC_SndSpecRatPlmnListReq_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    VOS_UINT32                          enIsPrefBandSrch;
    VOS_UINT32                          enIsFullBandSrch;
#if (FEATURE_ON == FEATURE_CSG)
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    enRatType = NAS_MML_GetCurrNetRatType();




    /*********************************** CSG LIST ***********************************/

    /* �����CSG�б������������csg�б����������� */
    if (VOS_TRUE == NAS_MMC_IsCsgList_PlmnList())
    {
        if ((NAS_MMC_AS_CELL_CAMP_ON == NAS_MMC_GetAsCellCampOn())
         || (NAS_MML_NET_RAT_TYPE_LTE == enRatType))
        {
            NAS_MMC_SndSpecRatCsgListSearchReq_PlmnList(enRatType);
            return;
        }

        /* gu�·�פ��̬��Ҫ����gu��lte������ */
        NAS_MMC_SndSpecRatCsgListSuspendReq_PlmnList(enRatType);
        return;
    }
#endif



    /*********************************** פ��̬��perf band list or full band list***********************************/

    enIsPrefBandSrch = NAS_MMC_IsPrefBandListSearchScene_PlmnList();
    enIsFullBandSrch = NAS_MMC_IsFullBandListSearchScene_PlmnList();


    NAS_NORMAL_LOG1(WUEPS_PID_MMC, "NAS_MMC_SndSpecRatPlmnListReq_PlmnList: Camp Staus is:", NAS_MMC_GetAsCellCampOn());

    /* pref band list��full band listҪ��һ������פ��̬����������ֱ�ӻظ��б���ʧ�� */
    if ( (NAS_MMC_AS_CELL_CAMP_ON == NAS_MMC_GetAsCellCampOn())
      && ((VOS_TRUE == enIsPrefBandSrch)
       || (VOS_TRUE == enIsFullBandSrch)) )
    {

        NAS_MMC_SndSpecRatInterPlmnListReq_PlmnList(enRat);

        return;
    }




    /***********************************��פ��̬��פ��̬��user list***********************************/

    NAS_MMC_SndSpecRatUserListReq_PlmnList(enRat);

    return;

}


VOS_VOID NAS_MMC_SndSpecRatInterPlmnListReq_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    switch (enRat)
    {
#if (FEATURE_LTE == FEATURE_ON)
        case NAS_MML_NET_RAT_TYPE_LTE:

            if (VOS_TRUE == NAS_MMC_IsPrefBandListSearchScene_PlmnList())
            {
                NAS_MMC_SndLmmPlmnListReq(MMC_LMM_PLMN_SRCH_INTER_LIST_PREF_BAND);
            }
            else
            {
                NAS_MMC_SndLmmPlmnListReq(MMC_LMM_PLMN_SRCH_INTER_LIST_FULL_BAND);
            }

            /* Ǩ��״̬���ȴ�LMM��LIST�����ظ� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_LMM_PLMN_SEARCH_CNF);

            /* ��������ʱ�� */
            if (NAS_MMC_AS_CELL_CAMP_ON == NAS_MMC_GetAsCellCampOn())
            {
                NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_SndSpecRatInterPlmnListReq_PlmnList: AS CELL IS ON CAMP. ");

                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_LIST_CNF, TI_NAS_MMC_CAMP_ON_WAIT_LMM_PLMN_LIST_CNF_LEN);
            }
            else
            {
                NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndSpecRatInterPlmnListReq_PlmnList: is not camp on");
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_LIST_CNF, TI_NAS_MMC_NOT_CAMP_ON_WAIT_LMM_PLMN_LIST_CNF_LEN);
            }

            break;
#endif
        case NAS_MML_NET_RAT_TYPE_WCDMA:

            if (VOS_TRUE == NAS_MMC_IsPrefBandListSearchScene_PlmnList())
            {
                NAS_MMC_SndAsPlmnListReq(WUEPS_PID_WRR, RRC_PLMN_SEARCH_INTER_LIST_PREF_BAND);
            }
            else
            {
                NAS_MMC_SndAsPlmnListReq(WUEPS_PID_WRR, RRC_PLMN_SEARCH_INTER_LIST);
            }

            /* Ǩ��״̬���ȴ�WAS��LIST�����ظ� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_WAS_PLMN_SEARCH_CNF);

            /* ��������ʱ�� */
            if (NAS_MMC_AS_CELL_CAMP_ON == NAS_MMC_GetAsCellCampOn())
            {
                NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_SndSpecRatInterPlmnListReq_PlmnList: AS CELL IS ON CAMP. ");

                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_PLMN_LIST_CNF, TI_NAS_MMC_CAMP_ON_WAIT_WAS_PLMN_LIST_CNF_LEN);
            }
            else
            {
                NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndSpecRatInterPlmnListReq_PlmnList: is not camp on");
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_PLMN_LIST_CNF, TI_NAS_MMC_NOT_CAMP_ON_WAIT_WAS_PLMN_LIST_CNF_LEN);
            }

            break;

        case NAS_MML_NET_RAT_TYPE_GSM:

            if (VOS_TRUE == NAS_MMC_IsPrefBandListSearchScene_PlmnList())
            {
                NAS_MMC_SndAsPlmnListReq(UEPS_PID_GAS, RRC_PLMN_SEARCH_INTER_LIST_PREF_BAND);
            }
            else
            {
                NAS_MMC_SndAsPlmnListReq(UEPS_PID_GAS, RRC_PLMN_SEARCH_INTER_LIST);
            }

            /* Ǩ��״̬���ȴ�GAS��LIST�����ظ� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_GAS_PLMN_SEARCH_CNF);

            /* ����������ʱ�� */
            if (NAS_MMC_AS_CELL_CAMP_ON == NAS_MMC_GetAsCellCampOn())
            {
                NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_SndSpecRatInterPlmnListReq_PlmnList: AS CELL IS ON CAMP. ");

                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_PLMN_LIST_CNF, TI_NAS_MMC_CAMP_ON_WAIT_GAS_PLMN_LIST_CNF_LEN);
            }
            else
            {
                NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndSpecRatInterPlmnListReq_PlmnList: is not camp on");
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_PLMN_LIST_CNF, TI_NAS_MMC_NOT_CAMP_ON_WAIT_GAS_PLMN_LIST_CNF_LEN);
            }

            break;

        default:

            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndSpecRatInterPlmnListReq_PlmnList: Unexpected Rat type!");

            break;

    }

    return;
}


VOS_VOID NAS_MMC_SndSpecRatUserListReq_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    switch (enRat)
    {
#if (FEATURE_LTE == FEATURE_ON)
        case NAS_MML_NET_RAT_TYPE_LTE:

            NAS_MMC_SndLmmPlmnListReq(MMC_LMM_PLMN_SRCH_USER_LIST);

            /* ĿǰL֧��פ��̬LIST����,�˴�������ʾ���µ�ǰ��פ��״̬,��
               ������Ϣ�ӿ�ID_LMM_MMC_NOT_CAMP_ON_INDָʾ */

            /* Ǩ��״̬���ȴ�LMM��LIST�����ظ� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_LMM_PLMN_SEARCH_CNF);

            /* ����������ʱ�� */
            if (NAS_MMC_AS_CELL_CAMP_ON == NAS_MMC_GetAsCellCampOn())
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_LIST_CNF, TI_NAS_MMC_CAMP_ON_WAIT_LMM_PLMN_LIST_CNF_LEN);
            }
            else
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_LIST_CNF, TI_NAS_MMC_NOT_CAMP_ON_WAIT_LMM_PLMN_LIST_CNF_LEN);
            }

            break;
#endif

        case NAS_MML_NET_RAT_TYPE_WCDMA:

            NAS_MMC_SndAsPlmnListReq(WUEPS_PID_WRR, RRC_PLMN_SEARCH_USER_LIST);

            /* Ǩ��״̬���ȴ�WAS��LIST�����ظ� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_WAS_PLMN_SEARCH_CNF);

            /* ����������ʱ�� */
            if (NAS_MMC_AS_CELL_CAMP_ON == NAS_MMC_GetAsCellCampOn())
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_PLMN_LIST_CNF, TI_NAS_MMC_CAMP_ON_WAIT_WAS_PLMN_LIST_CNF_LEN);
            }
            else
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_PLMN_LIST_CNF, TI_NAS_MMC_NOT_CAMP_ON_WAIT_WAS_PLMN_LIST_CNF_LEN);
            }

            break;

        case NAS_MML_NET_RAT_TYPE_GSM:

            NAS_MMC_SndAsPlmnListReq(UEPS_PID_GAS, RRC_PLMN_SEARCH_USER_LIST);

            /* Ǩ��״̬���ȴ�GAS��LIST�����ظ� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_GAS_PLMN_SEARCH_CNF);

            /* ����������ʱ�� */
            if (NAS_MMC_AS_CELL_CAMP_ON == NAS_MMC_GetAsCellCampOn())
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_PLMN_LIST_CNF, TI_NAS_MMC_CAMP_ON_WAIT_GAS_PLMN_LIST_CNF_LEN);
            }
            else
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_PLMN_LIST_CNF, TI_NAS_MMC_NOT_CAMP_ON_WAIT_GAS_PLMN_LIST_CNF_LEN);
            }

            break;
        default:

            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndSpecRatPlmnListReq_PlmnList Unexpected Rat type!");

            break;
    }
}


VOS_VOID NAS_MMC_SndSpecRatPlmnSearchStopReq_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    switch (enRat)
    {
#if (FEATURE_LTE == FEATURE_ON)
        case NAS_MML_NET_RAT_TYPE_LTE:

            /* ��LMM����ֹͣ�������� */
            NAS_MMC_SndLmmPlmnSrchStopReq();

            /* Ǩ��״̬���ȴ�LMM��ֹͣ�����ظ� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_LMM_PLMN_SEARCH_STOP_CNF);

            /* ����������ʱ�� */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF_LEN);

            break;
#endif

        case NAS_MML_NET_RAT_TYPE_WCDMA:

            /* ��WAS����ֹͣ�������� */
            NAS_MMC_SndAsPlmnSrchStopReq(WUEPS_PID_WRR);

            /* Ǩ��״̬���ȴ�WAS��ֹͣ�����ظ� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_WAS_PLMN_SEARCH_STOP_CNF);

            /* ����������ʱ�� */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF_LEN);

            break;

        case NAS_MML_NET_RAT_TYPE_GSM:

            /* ��GAS����ֹͣ�������� */
            NAS_MMC_SndAsPlmnSrchStopReq(UEPS_PID_GAS);

            /* Ǩ��״̬���ȴ�GAS��ֹͣ�����ظ� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_GAS_PLMN_SEARCH_STOP_CNF);

            /* ����������ʱ�� */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF_LEN);

            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndSpecRatPlmnSearchStopReq_PlmnList Unexpected Rat type!");

            break;
    }
}



VOS_VOID NAS_MMC_SndSpecRatSuspendReq_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    switch (enRat)
    {
#if (FEATURE_LTE == FEATURE_ON)
        case NAS_MML_NET_RAT_TYPE_LTE:

            /* ����פ��״̬ */
            NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
            NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

            NAS_MMC_SetAsAnyCampOn(VOS_FALSE);

            /* ��LMM���͹������� */
            NAS_MMC_SndLmmSuspendReq();

            /* Ǩ��״̬���ȴ�LMM�Ĺ���ظ� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_LMM_SUSPEND_CNF);

            /* ����������ʱ�� */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF, TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF_LEN);

            break;
#endif

        case NAS_MML_NET_RAT_TYPE_WCDMA:

            /* ����פ��״̬ */
            NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
            NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

            NAS_MMC_SetAsAnyCampOn(VOS_FALSE);

            /* ��WAS���͹������� */
            NAS_MMC_SndAsSuspendReq(WUEPS_PID_WRR);

            /* Ǩ��״̬���ȴ�WAS�Ĺ���ظ� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_WAS_SUSPEND_CNF);

            /* ����������ʱ�� */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF, TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF_LEN);

            break;

        case NAS_MML_NET_RAT_TYPE_GSM:

            /* ����פ��״̬ */
            NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
            NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

            NAS_MMC_SetAsAnyCampOn(VOS_FALSE);

            /* ��GAS���͹������� */
            NAS_MMC_SndAsSuspendReq(UEPS_PID_GAS);

            /* Ǩ��״̬���ȴ�GAS�Ĺ���ظ� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_GAS_SUSPEND_CNF);

            /* ����������ʱ�� */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF, TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF_LEN);

            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndSpecRatSuspendReq_PlmnList Unexpected Rat type!");

            break;
    }
}


VOS_VOID NAS_MMC_ProcRrmmSearchCnf_UserPlmnListSearch_PlmnList(
    RRMM_PLMN_SEARCH_CNF_STRU          *pstPlmnSrchCnf
)
{
    /* �ж�LIST������� */
    switch (pstPlmnSrchCnf->ulSearchRlt)
    {
        case RRC_PLMN_SEARCH_RLT_USER_LIST_REJ:

            /* ����5S�����Գ��Զ�ʱ�� */
            if ( VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
            {
                 /* CSҵ�����绰���������Ľ����list rej��Ҫ��ֹlist�ѣ�
                    ��Ӧҵ�����AT�ڱ�list����ռ�ã��û��޷���������绰���ն��� */
                if (VOS_TRUE == NAS_MML_GetCsServiceExistFlg())
                {
                    /* ����LIST REJ��MSCC */
                    NAS_Mmc_SndMsccPlmnListRej();
                }
                else
                {
                    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST, TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST_LEN);
                }
            }
            else
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST, TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST_LEN);
            }

            /* ����״̬��ʧ�ܵ��˳���� */
            NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                    VOS_FALSE,
                                    NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                    NAS_MMC_GetRegRsltInfo_PlmnList());

            /* �˳�״̬�� */
            NAS_MMC_FSM_QuitFsmL2();

            break;

       case RRC_PLMN_SEARCH_RLT_USER_LIST:

            /* ����PLMN LIST�����ɹ��Ľ�� */
            NAS_MMC_ProcPlmnListSucc_PlmnList(pstPlmnSrchCnf);

            break;

       case RRC_PLMN_SEARCH_RLT_USER_LIST_FAIL:
            if ( VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
            {
                /* ����LIST REJ��MSCC */
                NAS_Mmc_SndMsccPlmnListRej();
            }

            /* ����״̬��ʧ�ܵ��˳���� */
            NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                    VOS_FALSE,
                                    NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                    NAS_MMC_GetRegRsltInfo_PlmnList());

            /* �˳�״̬�� */
            NAS_MMC_FSM_QuitFsmL2();
            break;

       case RRC_PLMN_SEARCH_RLT_USER_LIST_NO_RF:

            NAS_MMC_ProcNoRf_PlmnList(NAS_MML_GetCurrNetRatType());

            break;

       default:

            /*�쳣��ӡ*/
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcRrmmSearchCnf_UserPlmnListSearch_PlmnList Unexpected List Result!");

            break;
    }

    return;
}


VOS_VOID NAS_MMC_ProcRrmmSearchCnf_InterPlmnListSearch_PlmnList(
    RRMM_PLMN_SEARCH_CNF_STRU          *pstPlmnSrchCnf
)
{
    switch (pstPlmnSrchCnf->ulSearchRlt)
    {
        case RRC_PLMN_SEARCH_RLT_INTER_LIST_REJ:
        case RRC_PLMN_SEARCH_RLT_INTER_LIST_FAIL:
        case RRC_PLMN_SEARCH_RLT_INTER_LIST_PREF_BAND_REJ:
        case RRC_PLMN_SEARCH_RLT_INTER_LIST_PREF_BAND_FAIL:

             /* ����״̬��ʧ�ܵ��˳���� */
             NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                     VOS_FALSE,
                                     NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                     NAS_MMC_GetRegRsltInfo_PlmnList());

             /* �˳�״̬�� */
             NAS_MMC_FSM_QuitFsmL2();

             break;

        case RRC_PLMN_SEARCH_RLT_INTER_LIST_SUCC:
        case RRC_PLMN_SEARCH_RLT_INTER_LIST_PREF_BAND_SUCC:

            NAS_MMC_ProcPlmnListSucc_PlmnList(pstPlmnSrchCnf);

            break;

        case RRC_PLMN_SEARCH_RLT_INTER_LIST_NO_RF:
        case RRC_PLMN_SEARCH_RLT_INTER_LIST_PREF_BAND_NO_RF:

            NAS_MMC_ProcNoRf_PlmnList(NAS_MML_GetCurrNetRatType());

            break;

        default:

             /*�쳣��ӡ*/
             NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcRrmmSearchCnf_InterPlmnListSearch_PlmnList Unexpected List Result!");

             break;
    }

    return;
}



VOS_VOID NAS_MMC_ProcPlmnListSucc_PlmnList(
    RRMM_PLMN_SEARCH_CNF_STRU          *pstPlmnSrchCnf
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;
    VOS_UINT32                          ulIndex;



    /* LIST����������,��Ҫ���ݵ�ǰ�����Я�����Ѿ�����
       ���Ľ��뼼����Ϣ����RAT��������� */
    for ( ulIndex = 0; ulIndex < NAS_RRC_MAX_RAT_NUM; ulIndex++)
    {
        if ( RRC_NAS_RAT_LIST_SEARCH_CMPL == pstPlmnSrchCnf->astSearchRatInfo[ulIndex].enListSearchRlt)
        {
            /*��RRC�Ľ��뼼��ת����MML����ĸ�ʽ��Ȼ����� */
            NAS_MMC_ConvertRrcRatToNasFormat(pstPlmnSrchCnf->astSearchRatInfo[ulIndex].enRat, &enRat);

            NAS_MMC_InitSpecRatSearchedPlmnListInfo_PlmnList(enRat);

            NAS_MMC_SetSearchedFlag_PlmnList(enRat);

            NAS_MMC_SetSpecRatSearchedTypeByPlmnSearchCnfSucc_PlmnList(enRat, pstPlmnSrchCnf->ulSearchRlt);
        }
    }

     /* ���������б� */
    NAS_MMC_UpdateSearchedPlmnListInfo_PlmnList(&(pstPlmnSrchCnf->PlmnIdList));

    /* LIST����������,RRC���ܳ�������,��ʱ��Ҫ��������״̬,�����˳�LIST�������ָ��
       ���� */
    if (NAS_MMC_AS_CELL_NOT_CAMP_ON == NAS_MMC_GetAsCellCampOn())
    {
        NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);
    }

    /* ��ȡ������һ��δ�����Ľ���ģʽ */
    if ( VOS_FALSE == NAS_MMC_GetNextSearchingRat_PlmnList(&enRat))
    {
       /* ������û�LIST����,��MSCC�ϱ���� */
       if ( VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
       {
           /* �����������������������ϱ���MSCC */
           NAS_MMC_SndMsccPlmnListCnf_PlmnList();
       }

       /* ����״̬���ɹ��˳��Ľ�� */
       NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_SUCC,
                               (VOS_UINT8)NAS_MMC_IsNeedPlmnSearch_PlmnList(),
                               NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                               NAS_MMC_GetRegRsltInfo_PlmnList());

       /* �˳�״̬�� */
       NAS_MMC_FSM_QuitFsmL2();

       return;
    }

    /* ��ǰ���뼼�����͹�������,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatSuspendReq_PlmnList(NAS_MML_GetCurrNetRatType());

    /* ��GMM��������ָʾ */
    NAS_MMC_SndGmmPlmnSchInit();

    /* ��MM��������ָʾ */
    NAS_MMC_SndMmPlmnSchInit();

    return;
}


VOS_VOID NAS_MMC_ProcRrmmSuspendCnf_PlmnList(
    RRMM_SUSPEND_CNF_ST                *pstRrmmSuspendCnf
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    VOS_UINT32                          ulNeedPlmnSearch;

    enCurRat      = NAS_MML_GetCurrNetRatType();

    if ( MMC_AS_SUSPEND_FAILURE  == pstRrmmSuspendCnf->ucResult )
    {
        /* ���帴λ */

        if ( (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
          && (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat) )
        {
            NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_WAS_SUSPEND_FAILURE);
        }
        else if ( NAS_MML_NET_RAT_TYPE_GSM == enCurRat )
        {
            NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_GAS_SUSPEND_FAILURE);
        }
        else if ( NAS_MML_NET_RAT_TYPE_LTE == enCurRat)
        {
            NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_LMM_SUSPEND_FAILURE);
        }
        else
        {
            NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_TD_SUSPEND_FAILURE);
        }

        return;
    }

    /* �ж�״̬���˳�����Ƿ�Ϊ�棬���Ϊ��*/
    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnList())
    {
        /* ���뼼������ΪBUTT����������ֱ��������ģ������������ */
        NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

        ulNeedPlmnSearch = VOS_FALSE;

        /* ��ǰ�û��б����� */
        if (VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
        {
            if ( VOS_TRUE == NAS_MMC_GetNotifyMsccFlag_PlmnList())
            {
                /* ��MSCC�ظ�ID_MMC_MSCC_PLMN_LIST_ABORT_CNF */
                NAS_MMC_SndMsccPlmnListAbortCnf_PlmnList();

                ulNeedPlmnSearch = VOS_TRUE;
            }
            else
            {
                /* ��MSCC�ظ�LIST������� */
                NAS_MMC_SndMsccPlmnListCnf_PlmnList();
            }
        }

        /* ����״̬��ABORT���˳���� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                                (VOS_UINT8)ulNeedPlmnSearch,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* ��ȡ������һ�����뼼�� */
    if ( VOS_FALSE == NAS_MMC_GetNextSearchingRat_PlmnList(&enRat))
    {
        /* �쳣��ӡ */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcRrmmSuspendCnf_PlmnList: Get next search rat fail.");

        /* ���뼼������ΪBUTT����������ֱ��������ģ������������ */
        NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

        /* ��ǰΪ�û�LIST���� */
        if ( VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
        {
            /* ��MSCC�ظ�ID_MMC_MSCC_PLMN_LIST_CNF */
            NAS_MMC_SndMsccPlmnListCnf_PlmnList();
        }

        /* ����״̬���˳���� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                (VOS_UINT8)NAS_MMC_IsNeedPlmnSearch_PlmnList(),
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* ���ݻ�ȡ�Ľ��뼼�����õ�ǰ���뼼�� */
    NAS_MML_SetCurrNetRatType(enRat);

    /* ���¸�����ģʽ����LIST��������,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(enRat);

}


VOS_VOID NAS_MMC_ProcRrcConnRelInd_PlmnList(VOS_VOID)
{
    VOS_UINT32                          ulCsServiceStatusFlg;

    ulCsServiceStatusFlg = NAS_MML_GetCsServiceExistFlg();

    /* һ������·�ͷź󣬵ȴ�����һ������ͷ�ָʾʱ���п����ͷŵ����Ϸ���ҵ��
       �˴���Ҫ�ж��Ƿ���ҵ����� */
    if ( VOS_TRUE == ulCsServiceStatusFlg )
    {
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

        NAS_MMC_SndMsccPlmnListRejMsg_PlmnList();

        /* ��ҵ��ʱ��δ����LIST�������ѵ��������б�Ϊ��,����״̬��ʧ�ܵ��˳���� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }
    else if ( VOS_TRUE == NAS_MML_IsRrcConnExist() )
    {
        /* ��������������ӣ�������ȴ����ȴ���ʱ֮���ټ������Է����б��� */
    }
    else
    {
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

        switch (NAS_MML_GetCurrNetRatType())
        {
            case NAS_MML_NET_RAT_TYPE_WCDMA:

                /* Ǩ��״̬���ȴ�was�����ϵͳ��Ϣ */
                NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_WAS_SYS_INFO_IND);

                /* ����������ʱ�� */
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO, TI_NAS_MMC_WAIT_WAS_SYS_INFO_LEN);

                break;
            case NAS_MML_NET_RAT_TYPE_GSM:

                /* Ǩ��״̬���ȴ�Gas�����ϵͳ��Ϣ */
                NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_GAS_SYS_INFO_IND);

                /* ����������ʱ�� */
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO, TI_NAS_MMC_WAIT_GAS_SYS_INFO_LEN);

                break;

            default:

            /*�쳣��ӡ*/
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcRrcConnel_PlmnList Unexpected Rat Type!");
            break;
        }
    }

    return;
}




VOS_VOID NAS_MMC_ProcRrmmPlmnSearchStopCnf_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNextRatType;

    VOS_UINT32                          ulNeedPlmnSearch;

    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnList())
    {
        ulNeedPlmnSearch = VOS_FALSE;

        /* ��ǰ�û��б����� */
        if (VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
        {
            if ( VOS_TRUE == NAS_MMC_GetNotifyMsccFlag_PlmnList())
            {
                /* ��MSCC�ظ�ID_MMC_MSCC_PLMN_LIST_ABORT_CNF */
                NAS_MMC_SndMsccPlmnListAbortCnf_PlmnList();

                ulNeedPlmnSearch = NAS_MMC_IsNeedPlmnSearch_PlmnList();
            }
            else
            {
                /* ��MSCC�ظ�LIST������� */
                NAS_MMC_SndMsccPlmnListCnf_PlmnList();
            }
        }

        /* ����״̬��ABORT�˳���� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                                (VOS_UINT8)ulNeedPlmnSearch,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* ��ȡ������һ��δ�����Ľ���ģʽ */
    if ( VOS_FALSE == NAS_MMC_GetNextSearchingRat_PlmnList(&enNextRatType))
    {
        /* �û�LIST���� */
        if ( VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
        {
            /* �����������������������ϱ���MSCC */
            NAS_MMC_SndMsccPlmnListCnf_PlmnList();
        }


        /* ��������յ�searched info indʱ������ϣ������б��ѳɹ�����Ҫ������������ѡ��״̬������ */
        if (VOS_TRUE == NAS_MMC_GetAbortBySearchedPlmnFlg_PlmnList())
        {

            NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_SUCC,
                                     VOS_TRUE,
                                     NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                     NAS_MMC_GetRegRsltInfo_PlmnList());
        }
        else
        {
            NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                    (VOS_UINT8)NAS_MMC_IsNeedPlmnSearch_PlmnList(),
                                    NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                    NAS_MMC_GetRegRsltInfo_PlmnList());

        }

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* ��ǰ���뼼�����͹�������,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatSuspendReq_PlmnList(enRatType);

    /* ��GMM��������ָʾ */
    NAS_MMC_SndGmmPlmnSchInit();

    /* ��MM��������ָʾ */
    NAS_MMC_SndMmPlmnSchInit();

    return;
}


VOS_VOID NAS_MMC_UpdateSearchedTypeFlgByCurrRatSearchedInfoInd_PlmnList(
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstNeedUpdateRatList
)
{
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8                    enRat;
    VOS_UINT32                                              j;

    /* list prefband�������� */
    if (VOS_TRUE == NAS_MMC_IsPrefBandListSearchScene_PlmnList())
    {
        /* ����ucPrefBandSearchedFlg��־ */
        for (j = 0; j < pstNeedUpdateRatList->ucRatNum; j++)
        {
            enRat = pstNeedUpdateRatList->aucRatPrio[j];
            NAS_MMC_SetHistorySearchedFlag_PlmnList(enRat, VOS_TRUE);
            NAS_MMC_SetPrefbandSearchedFlag_PlmnList(enRat, VOS_TRUE);
        }

        return;
    }

    /* list fullband�������� */
    if (VOS_TRUE == NAS_MMC_IsFullBandListSearchScene_PlmnList())
    {
        /* ����ucPrefBandSearchedFlg��־��ucSpecSearchedFlg��־ */
        for (j = 0; j < pstNeedUpdateRatList->ucRatNum; j++)
        {
            enRat = pstNeedUpdateRatList->aucRatPrio[j];
            NAS_MMC_SetHistorySearchedFlag_PlmnList(enRat, VOS_TRUE);
            NAS_MMC_SetPrefbandSearchedFlag_PlmnList(enRat, VOS_TRUE);
            NAS_MMC_SetFullbandSearchedFlag_PlmnList(enRat, VOS_TRUE);
        }

        return;
    }
}


VOS_VOID NAS_MMC_UpdateSearchedTypeStatusBySearchedPlmnInfoInd_PlmnList(
    RRMM_SEARCHED_PLMN_INFO_IND_STRU   *pstSearchedPlmnInfoMsg
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU                   *pstRatPrio          = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8               enRat;
    VOS_UINT32                                    i;
    VOS_UINT32                                    j;
    NAS_MML_PLMN_RAT_PRIO_STRU                    stNeedUpdateRatList;

    pstRatPrio          = NAS_MML_GetMsPrioRatList();
    NAS_MEM_SET_S(&stNeedUpdateRatList, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU), 0x00, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    for (j = 0; j < pstSearchedPlmnInfoMsg->ulAvailPlmnNum; j++)
    {
        /* ת��RRC��ʽ�Ľ��뼼�� */
        NAS_MMC_ConvertRrcRatToNasFormat(pstSearchedPlmnInfoMsg->astPlmnWithLacList[j].ulRat, &enRat);

        for (i = 0; i < pstRatPrio->ucRatNum; i++)
        {
            if (pstRatPrio->aucRatPrio[i] == enRat)
            {
                NAS_MMC_BuildNeedUpdateRatList_PlmnList(i, &stNeedUpdateRatList);
                NAS_MMC_UpdateSearchedTypeFlgByCurrRatSearchedInfoInd_PlmnList(&stNeedUpdateRatList);

                break;
            }
        }
     }

    return;
}



VOS_VOID NAS_MMC_BuildNeedUpdateRatList_PlmnList(
    VOS_UINT32                          ulIndex,
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstNeedUpdateRatList
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatPrio = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstRatPrio          = NAS_MML_GetMsPrioRatList();

    if (pstRatPrio->ucRatNum <= ulIndex)
    {
        /* �쳣��ӡ */
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_BuildNeedUpdateRatList_PlmnList: rat num fail!");
        return;
    }

    for (i = 0; i < ulIndex; i++)
    {
        pstNeedUpdateRatList->aucRatPrio[i] = pstRatPrio->aucRatPrio[i];
    }

    pstNeedUpdateRatList->ucRatNum = (VOS_UINT8)i;

    return;
}


#if (FEATURE_ON == FEATURE_LTE)

VOS_VOID NAS_MMC_ProcLmmPlmnSearchStopCnf_PlmnList(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNextRatType;

    VOS_UINT32                          ulNeedPlmnSearch;

    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnList())
    {
        ulNeedPlmnSearch = VOS_FALSE;

        /* ֪ͨMSCC�ظ����Ϊ�� */
        if ( VOS_TRUE == NAS_MMC_GetNotifyMsccFlag_PlmnList())
        {
            if (VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
            {
                /* ��MSCC�ظ�ID_MMC_MSCC_PLMN_LIST_ABORT_CNF */
                NAS_MMC_SndMsccPlmnListAbortCnf_PlmnList();
            }

            ulNeedPlmnSearch = NAS_MMC_IsNeedPlmnSearch_PlmnList();
        }
        else
        {
            /* ��MSCC�ظ�LIST������� */
            NAS_MMC_SndMsccListSearchCnfMsg_PlmnList();
        }

        /* ����״̬��ABORT�˳���� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                                (VOS_UINT8)ulNeedPlmnSearch,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* ��ȡ������һ��δ�����Ľ���ģʽ */
    if ( VOS_FALSE == NAS_MMC_GetNextSearchingRat_PlmnList(&enNextRatType))
    {
        /* ��MSCC�ظ�LIST������� */
        NAS_MMC_SndMsccListSearchCnfMsg_PlmnList();


        /* ��������յ�searched info indʱ������ϣ������б��ѳɹ�����Ҫ������������ѡ��״̬������ */
        if (VOS_TRUE == NAS_MMC_GetAbortBySearchedPlmnFlg_PlmnList())
        {

            NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_SUCC,
                                     VOS_TRUE,
                                     NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                     NAS_MMC_GetRegRsltInfo_PlmnList());
        }
        else
        {
            NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                     (VOS_UINT8)NAS_MMC_IsNeedPlmnSearch_PlmnList(),
                                     NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                     NAS_MMC_GetRegRsltInfo_PlmnList());

        }

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* ��ǰ���뼼�����͹�������,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatSuspendReq_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

    /* ��GMM��������ָʾ */
    NAS_MMC_SndGmmPlmnSchInit();

    /* ��MM��������ָʾ */
    NAS_MMC_SndMmPlmnSchInit();

    return;
}


VOS_VOID NAS_MMC_ProcLteSysInfo_PlmnList(
    struct MsgCB                       *pstLSysInfoInd
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8               enSpecPlmnSearchState;

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    /* �����ϵ�פ��������Ϣ */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    /* ����ϵͳ��Ϣ������MML��ȫ������ */
    NAS_MMC_UpdateNetworkInfo_LmmSysInfo(pstLSysInfoInd);

    /* ״̬����Ϊ��ǰ�Ѿ�פ�� */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* CBS�ϱ�*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_LTE);

    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);

    /*�����Ż���LTE�µ�С�������仯��LMM��ͨ��ϵͳ��Ϣ֪ͨMMC*/
    enSpecPlmnSearchState = NAS_MMC_GetSpecPlmnSearchState();

    if ((VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
     || (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == enSpecPlmnSearchState))
    {
        /* �����ϱ� */
        NAS_MMC_SndMsccSysInfo();
    }


    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STOP);

    /* ת��GMMϵͳ��Ϣ,��rabmʹ�� */
    NAS_MMC_SndGmmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstLSysInfoInd);
    NAS_MMC_SndMmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstLSysInfoInd);

    NAS_MMC_SndLmmLteSysInfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstLSysInfoInd);

    return;
}




VOS_UINT32 NAS_MMC_IsNeedStopPlmnListSearchRcvLmmSearchedPlmnInfoInd_PlmnList(
    LMM_MMC_SEARCHED_PLMN_INFO_IND_STRU          *pstLmmSearchedPlmnInfoMsg,
    NAS_MML_PLMN_WITH_RAT_STRU                   *pstAbortPlmn
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurrCampPlmnId    = VOS_NULL_PTR;
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstUserSpecPlmn      = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                                        stLai;
    NAS_MMC_ROAM_PLMN_INFO_STRU                             stSearchedPlmnInfo;
    NAS_MMC_ROAM_PLMN_INFO_STRU                             stCurrCampPlmnInfo;
    NAS_MML_PLMN_ID_STRU                                    stPlmn;
    VOS_UINT32                                              ulIndex;
    VOS_UINT32                                              ulIsFullBandScene;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enNasRat;

    pstCurrCampPlmnId                    = NAS_MML_GetCurrCampPlmnInfo();
    pstDPlmnNPlmnCfgInfo                 = NAS_MMC_GetDPlmnNPlmnCfgInfo();
    pstUserSpecPlmn                      = NAS_MMC_GetUserSpecPlmnId();
    ulIsFullBandScene                    = NAS_MMC_IsFullBandListSearchScene_PlmnList();

    PS_MEM_SET(&stLai, 0x00, sizeof(NAS_MML_LAI_STRU));
    PS_MEM_SET(&stSearchedPlmnInfo, 0x00, sizeof(NAS_MMC_ROAM_PLMN_INFO_STRU));
    PS_MEM_SET(&stCurrCampPlmnInfo, 0x00, sizeof(NAS_MMC_ROAM_PLMN_INFO_STRU));
    PS_MEM_SET(&stPlmn, 0x00, sizeof(NAS_MML_PLMN_ID_STRU));

    stCurrCampPlmnInfo.stPlmnWithRat.stPlmnId.ulMcc = pstCurrCampPlmnId->stLai.stPlmnId.ulMcc;
    stCurrCampPlmnInfo.stPlmnWithRat.stPlmnId.ulMnc = pstCurrCampPlmnId->stLai.stPlmnId.ulMnc;
    stCurrCampPlmnInfo.stPlmnWithRat.enRat          = pstCurrCampPlmnId->enNetRatType;
    stCurrCampPlmnInfo.enNetStatus                  = NAS_MMC_NET_STATUS_SEARCHED_REGISTERED;
    stCurrCampPlmnInfo.enPlmnType                   = NAS_MMC_PLMN_TYPE_BUTT;
    stCurrCampPlmnInfo.aucLac[0]                    = NAS_MML_LAC_LOW_BYTE_INVALID;
    stCurrCampPlmnInfo.aucLac[1]                    = NAS_MML_LAC_HIGH_BYTE_INVALID;

    if (LMM_MMC_MAX_SEARCHED_TAI_NUM <= pstLmmSearchedPlmnInfoMsg->ulTaiNum)
    {
        pstLmmSearchedPlmnInfoMsg->ulTaiNum = LMM_MMC_MAX_SEARCHED_TAI_NUM;
    }

    /* ����pref band list������full band list��������� */
    if ((VOS_FALSE == NAS_MMC_IsPrefBandListSearchScene_PlmnList())
     && (VOS_FALSE == ulIsFullBandScene))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedStopPlmnListSearchRcvLmmSearchedPlmnInfoInd_PlmnList: is not pref band list or full band list scene");
        return VOS_FALSE;
    }


    /* ��ϲ���:
    1. �����������������NPLMN������FPLMN������Ҫ���
    2. ���������������Ȳ���NPLMNҲ����FPLMN���жϱ�������plmn�뵱ǰפ����plmn MCC�Ƿ���ͬ:
       �������ͬ���ұ�������plmn��RPLMN/HPLMN/DPLMN�е�һ��ʱ����Ҫ���;
       �����ͬ���ұ�������plmn���ȼ����ڵ�ǰפ��plmnʱ����Ҫ���
    3. �����������Ҫ���
    */

    for (ulIndex = 0; ulIndex < pstLmmSearchedPlmnInfoMsg->ulTaiNum; ulIndex++)
    {
        /* ��������������ת��ΪNAS_MMC_ROAM_PLMN_INFO_STRU��ʽ */
        NAS_MMC_ConvertLmmPlmnToGUNasFormat(&pstLmmSearchedPlmnInfoMsg->stTaiList[ulIndex].stPlmnId, &stPlmn);
        NAS_MMC_ConvertLmmRatToNasFormat(pstLmmSearchedPlmnInfoMsg->stTaiList[ulIndex].enRat, &enNasRat);

        stSearchedPlmnInfo.stPlmnWithRat.stPlmnId.ulMcc = stPlmn.ulMcc;
        stSearchedPlmnInfo.stPlmnWithRat.stPlmnId.ulMnc = stPlmn.ulMnc;
        stSearchedPlmnInfo.stPlmnWithRat.enRat          = enNasRat;
        stSearchedPlmnInfo.enNetStatus                  = NAS_MMC_NET_STATUS_SEARCHED_EXIST;
        stSearchedPlmnInfo.enPlmnType                   = NAS_MMC_PLMN_TYPE_BUTT;
        stSearchedPlmnInfo.aucLac[0]                    = pstLmmSearchedPlmnInfoMsg->stTaiList[ulIndex].stTac.ucTac;
        stSearchedPlmnInfo.aucLac[1]                    = pstLmmSearchedPlmnInfoMsg->stTaiList[ulIndex].stTac.ucTacCnt;

        stLai.stPlmnId         = stSearchedPlmnInfo.stPlmnWithRat.stPlmnId;
        stLai.enCampPlmnNetRat = stSearchedPlmnInfo.stPlmnWithRat.enRat;
        stLai.aucLac[0]        = stSearchedPlmnInfo.aucLac[0];
        stLai.aucLac[1]        = stSearchedPlmnInfo.aucLac[1];
        stLai.ucRac            = NAS_MML_RAC_INVALID;

        /* �ֶ�����ģʽ��������ж� */
        if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
        {

            if (VOS_TRUE == NAS_MMC_IsNeedStopPlmnListSrchRcvSearchedPlmnInMaualMode_PLmnList(&pstUserSpecPlmn->stPlmnId,
                                                                                               &pstCurrCampPlmnId->stLai.stPlmnId,
                                                                                               &stSearchedPlmnInfo.stPlmnWithRat.stPlmnId))
            {
                pstAbortPlmn->enRat             = stSearchedPlmnInfo.stPlmnWithRat.enRat;
                pstAbortPlmn->stPlmnId.ulMcc    = stSearchedPlmnInfo.stPlmnWithRat.stPlmnId.ulMcc;
                pstAbortPlmn->stPlmnId.ulMnc    = stSearchedPlmnInfo.stPlmnWithRat.stPlmnId.ulMnc;

                return VOS_TRUE;
            }

            continue;
        }

        /* �������������ֹlte���Σ������ */
        if (VOS_TRUE == NAS_MMC_IsNeedDisableLteRoam(stPlmn.ulMcc))
        {
            continue;
        }

        /* �Զ�����ģʽ��������ж� */
        if (VOS_TRUE == NAS_MMC_IsNeedStopPlmnListSrchRcvSearchedPlmnInAutoMode_PLmnList(&stSearchedPlmnInfo,
                                                                                          &stCurrCampPlmnInfo,
                                                                                          &stLai,
                                                                                          pstDPlmnNPlmnCfgInfo))
        {
            pstAbortPlmn->enRat             = stSearchedPlmnInfo.stPlmnWithRat.enRat;
            pstAbortPlmn->stPlmnId.ulMcc    = stSearchedPlmnInfo.stPlmnWithRat.stPlmnId.ulMcc;
            pstAbortPlmn->stPlmnId.ulMnc    = stSearchedPlmnInfo.stPlmnWithRat.stPlmnId.ulMnc;

            return VOS_TRUE;
        }
        else
        {
            continue;
        }
    }

    return VOS_FALSE;
}



VOS_VOID NAS_MMC_UpdateSearchedRatStatusByLmmSearchedPlmnInfoInd_PlmnList(
    LMM_MMC_SEARCHED_PLMN_INFO_IND_STRU          *pstSearchedPlmnInfoMsg
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU                   *pstRatPrio          = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8               enRat;
    VOS_UINT32                                    i;
    VOS_UINT32                                    j;
    NAS_MML_PLMN_RAT_PRIO_STRU                    stNeedUpdateRatList;

    pstRatPrio          = NAS_MML_GetMsPrioRatList();
    NAS_MEM_SET_S(&stNeedUpdateRatList, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU), 0x00, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    for (j = 0; j < pstSearchedPlmnInfoMsg->ulTaiNum; j++)
    {
        /* ת��RRC��ʽ�Ľ��뼼�� */
        NAS_MMC_ConvertLmmRatToNasFormat(pstSearchedPlmnInfoMsg->stTaiList[j].enRat, &enRat);

        for (i = 0; i < pstRatPrio->ucRatNum; i++)
        {
            if (pstRatPrio->aucRatPrio[i] == enRat)
            {
                NAS_MMC_BuildNeedUpdateRatList_PlmnList(i, &stNeedUpdateRatList);
                NAS_MMC_UpdateSearchedTypeFlgByCurrRatSearchedInfoInd_PlmnList(&stNeedUpdateRatList);

                break;
            }
        }
     }

    return;
}

#endif


VOS_UINT32 NAS_MMC_IsNeedWaitRrcRel_PlmnList( VOS_VOID )
{
    VOS_UINT8                           ucCsSigConnStatusFlg;

    ucCsSigConnStatusFlg = NAS_MML_GetCsSigConnStatusFlg();

    /* ��ǰRRC���Ӳ����ڿ���ֱ�ӷ��� */
    if (VOS_FALSE == NAS_MML_IsRrcConnExist())
    {
        return VOS_FALSE;
    }

    /* ��ǰ����PSҵ��򻺴��psҵ�񵫲�����cs����������������RRC */
    if (VOS_FALSE == ucCsSigConnStatusFlg)
    {
        return VOS_FALSE;
    }

    /* ���������Ϊ������������,�����ȴ�RRC�ͷ��������� */
    return VOS_TRUE;

}


VOS_VOID NAS_MMC_ProcUserPlmnListReq_PlmnList(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus = VOS_NULL_PTR;

    enRatType     = NAS_MML_GetCurrNetRatType();
    pstConnStatus = NAS_MML_GetConnStatus();

    /* ����״̬�±���ϣ���ǰ���뼼��ΪBUTT */
    if ( NAS_MML_NET_RAT_TYPE_BUTT == NAS_MML_GetCurrNetRatType())
    {
       NAS_MMC_GetOrigenSearchRat_PlmnList(&enRatType);

       NAS_MML_SetCurrNetRatType(enRatType);
    }

    /* �ж��Ƿ���Ҫ�ȴ������ͷ� */
    if ( VOS_FALSE == NAS_MMC_IsNeedWaitRrcRel_PlmnList() )
    {
       /* ���ݲ�ͬ����ģʽ,����LIST��������Ǩ���ȴ��������״̬������������ʱ��*/
       NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_GetCurrNetRatType());

       /* ��פ��̬֪ͨMM/GMM������ʼ */
       if (NAS_MMC_AS_CELL_NOT_CAMP_ON == NAS_MMC_GetAsCellCampOn())
       {
            NAS_MMC_UpdateServiceStateSpecPlmnSearch();
            NAS_MMC_UpdateRegStateSpecPlmnSearch();

            if ((NAS_MML_NET_RAT_TYPE_WCDMA != enRatType)
             || (VOS_FALSE == pstConnStatus->ucRrcStatusFlg))
            {
                /* ��GMM��������ָʾ */
                NAS_MMC_SndGmmPlmnSchInit();

                /* ��MM��������ָʾ */
                NAS_MMC_SndMmPlmnSchInit();

                /* ���ý�������״̬ */
                NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

                return;
            }
       }

       /* פ��̬��GTLģʽTDΪ��ģʱ��Ҫ֪ͨMM/GMM��������״̬ */
       if ( (VOS_TRUE == NAS_MMC_IsCurrentTdscdmaMode())
         && (VOS_FALSE == pstConnStatus->ucRrcStatusFlg) )
       {
            /* ��GMM��������ָʾ */
            NAS_MMC_SndGmmPlmnSchInit();

            /* ��MM��������ָʾ */
            NAS_MMC_SndMmPlmnSchInit();

            /* ��ģ����������GUNAS���� */
            if (VOS_FALSE == NAS_MML_IsWcdmaOnlyMode(NAS_MML_GetMsPrioRatList()))
            {
                /* ���ý�������״̬ */
                NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);
            }
       }

       return;
    }

    /* ��Ҫ�ȴ������ͷ� */
    switch (NAS_MML_GetCurrNetRatType())
    {
#if (FEATURE_LTE == FEATURE_ON)
        case NAS_MML_NET_RAT_TYPE_LTE:

        /* L����EPS�������ӱ����ȴ�LMM�ͷ���·,
           ������GU��ʵ��һ�� */

        /* Ǩ��״̬���ȴ�LMM��EPS��·�ͷ� */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_EPS_CONN_REL_IND);

        /* ����������ʱ�� */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);

        break;
#endif

    case NAS_MML_NET_RAT_TYPE_WCDMA:
    case NAS_MML_NET_RAT_TYPE_GSM:

        /* Ǩ��״̬���ȴ�GU��RRC��·�ͷ� */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_RRC_CONN_REL_IND);

        /* ����������ʱ�� */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL, TI_NAS_MMC_WAIT_RRC_CONN_REL_LEN);

        break;

    default:
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcUserPlmnListReq_PlmnList Unexpected Rat type!");

        break;
    }

    return;
}


VOS_VOID NAS_MMC_ProcInterListReq_PlmnList(VOS_VOID)
{
    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus = VOS_NULL_PTR;

    pstConnStatus = NAS_MML_GetConnStatus();

   /* ���ݲ�ͬ����ģʽ,����LIST��������Ǩ���ȴ��������״̬������������ʱ��*/
   NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_GetCurrNetRatType());

   /* פ��̬��GTLģʽTDΪ��ģʱ��Ҫ֪ͨMM/GMM��������״̬ */
   if ( (VOS_TRUE == NAS_MMC_IsCurrentTdscdmaMode())
     && (VOS_FALSE == pstConnStatus->ucRrcStatusFlg) )
   {
        /* ��GMM��������ָʾ */
        NAS_MMC_SndGmmPlmnSchInit();

        /* ��MM��������ָʾ */
        NAS_MMC_SndMmPlmnSchInit();

        /* ��ģ����������GUNAS���� */
        if (VOS_FALSE == NAS_MML_IsWcdmaOnlyMode(NAS_MML_GetMsPrioRatList()))
        {
            /* ���ý�������״̬ */
            NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);
        }
   }

   return;

}



VOS_VOID NAS_MMC_UpdateSearchedTypeByInterPlmnSearchInfo_PlmnList(
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstInterPlmnSearchInfo
)
{
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo = VOS_NULL_PTR;
    VOS_UINT32                                              i;
    VOS_UINT32                                              j;

    pstSearchedPlmnListInfo = NAS_MMC_GetSearchedPlmnListInfo_PlmnList();

    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        for (j = 0; j < NAS_MML_MAX_RAT_NUM; j++)
        {
            if (pstInterPlmnSearchInfo[i].enRatType == pstSearchedPlmnListInfo[j].enRatType)
            {
                pstSearchedPlmnListInfo[j].stSearchedType = pstInterPlmnSearchInfo[i].stSearchedType;
                break;
            }
        }
    }

    return;

}


VOS_VOID NAS_MMC_ProcGasSysInfo_PlmnList(
    struct MsgCB                       *pstGSysInfoInd
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;

    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8                enSpecPlmnSearchState;
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;


    /* ��ȡLTE����״̬ */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
#endif

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* ����פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstGSysInfoInd, enLCapabilityStatus);
#endif

    /* �����ϵ�פ��������Ϣ */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    pstCurCsRestrictInfo    = NAS_MML_GetCsAcRestrictionInfo();
    pstCurPsRestrictInfo    = NAS_MML_GetPsAcRestrictionInfo();

    PS_MEM_CPY(&stOldCsRestrictInfo, pstCurCsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_CPY(&stOldPsRestrictInfo, pstCurPsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* ����ϵͳ��Ϣ������MML��ȫ������ */
    NAS_MMC_UpdateNetworkInfo_GasSysInfo(pstGSysInfoInd);

    /* פ��С���仯����������ʱ���ϱ�ϵͳ��Ϣ */
    enSpecPlmnSearchState = NAS_MMC_GetSpecPlmnSearchState();

    if ((VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
     || (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == enSpecPlmnSearchState))
    {
        /* �����ϱ� */
        NAS_MMC_SndMsccSysInfo();

    }

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STOP);

    /* פ��С���Ľ���������Ϣ�仯ʱ,֪ͨMSCCģ�鵱ǰ����������Ϣ */
    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldCsRestrictInfo, pstCurCsRestrictInfo))
    {
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_CS, pstCurCsRestrictInfo);
    }

    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldPsRestrictInfo, pstCurPsRestrictInfo))
    {
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_PS, pstCurPsRestrictInfo);
    }

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))
    /* CBS�ϱ�*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_GSM);
#endif

    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);

    /*ת��ϵͳ��Ϣ֪ͨ �� MM/GMM */
    NAS_MMC_SndMmGsmSysInfoInd (NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstGSysInfoInd);
    NAS_MMC_SndGmmGsmSysInfoInd (NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstGSysInfoInd);

#if (FEATURE_ON == FEATURE_LTE)

    NAS_MMC_SndLmmGsmSysInfoInd(pstGSysInfoInd);
#endif

    return;
}



VOS_VOID NAS_MMC_ProcWasSysInfo_PlmnList(
    struct MsgCB                       *pstWSysInfoInd
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;

    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8                enSpecPlmnSearchState;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;

    /* ��ȡLTE����״̬ */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
#endif

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* ����פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstWSysInfoInd,enLCapabilityStatus);
#endif

    /* �����ϵ�פ��������Ϣ */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    pstCurCsRestrictInfo    = NAS_MML_GetCsAcRestrictionInfo();
    pstCurPsRestrictInfo    = NAS_MML_GetPsAcRestrictionInfo();

    PS_MEM_CPY(&stOldCsRestrictInfo, pstCurCsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_CPY(&stOldPsRestrictInfo, pstCurPsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* ����ϵͳ��Ϣ������MML��ȫ������ */
    NAS_MMC_UpdateNetworkInfo_WasSysInfo(pstWSysInfoInd);

    /* פ��С���仯����������ʱ���ϱ�ϵͳ��Ϣ */
    enSpecPlmnSearchState = NAS_MMC_GetSpecPlmnSearchState();

    if ((VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
     || (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == enSpecPlmnSearchState))
    {
        /* �����ϱ� */
        NAS_MMC_SndMsccSysInfo();

    }

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STOP);

    /* פ��С���Ľ���������Ϣ�仯ʱ,֪ͨMSCCģ�鵱ǰ����������Ϣ */
    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldCsRestrictInfo, pstCurCsRestrictInfo))
    {
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_CS, pstCurCsRestrictInfo);
    }

    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldPsRestrictInfo, pstCurPsRestrictInfo))
    {
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_PS, pstCurPsRestrictInfo);
    }

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))
    /* CBS�ϱ�*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_WCDMA);
#endif

    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);

    /*ת��ϵͳ��Ϣ֪ͨ �� MM/GMM */
    NAS_MMC_SndMmWasSysInfoInd (NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstWSysInfoInd);
    NAS_MMC_SndGmmWasSysInfoInd (NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstWSysInfoInd);

#if (FEATURE_ON == FEATURE_LTE)

    NAS_MMC_SndLmmWcdmaSysInfoInd(pstWSysInfoInd);
#endif

    return;
}

#if (FEATURE_ON == FEATURE_LTE)

VOS_VOID NAS_MMC_ProcLmmSearchCnf_UserPlmnListSearch_PlmnList(
    LMM_MMC_PLMN_SRCH_CNF_STRU         *pstLmmPlmnSrchCnf
)
{
    switch(pstLmmPlmnSrchCnf->enRlst)
    {
        case MMC_LMM_PLMN_SRCH_RLT_USER_LIST_NO_RF:
            NAS_MMC_ProcNoRf_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);
            break;

        case MMC_LMM_PLMN_SRCH_RLT_USER_LIST_REJ:
            {
                /* ����5S�����Գ��Զ�ʱ��*/
                if ( VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
                {
                    /* CSҵ�����绰���������Ľ����list rej��Ҫ��ֹlist�ѣ�
                        ��Ӧҵ�����AT�ڱ�list����ռ�ã��û��޷���������绰���ն���
                        L���޷�֪����csҵ���Ƕ��ţ�ֻ�ܸ����Ƿ�ucEpsServiceConnStatusFlg���ж� */

                    /* L����������̬���Ի����б�������������CSҵ��ʱ��Ҫ�����ظ��б�����ʧ�� */
                    if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
                    {
                        /* ����LIST REJ��MSCC */
                        NAS_Mmc_SndMsccPlmnListRej();
                    }
                    else
                    {
                        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST, TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST_LEN);
                    }

                 }
                else
                {
                    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST, TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST_LEN);
                }

                /* ����״̬��ʧ���˳��Ľ�� */
                NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                        VOS_FALSE,
                                        NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                        NAS_MMC_GetRegRsltInfo_PlmnList());

                /* �˳�״̬�� */
                NAS_MMC_FSM_QuitFsmL2();
            }
            break;

        case MMC_LMM_PLMN_SRCH_RLT_USER_LIST_SUCC:

            NAS_MMC_ProcLmmPlmnListSucc_PlmnList(pstLmmPlmnSrchCnf);
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmSearchCnf_UserPlmnListSearch_PlmnList: Unexpected List Search Result!");
            break;
    }

    return;
}


VOS_VOID NAS_MMC_ProcLmmPlmnListSucc_PlmnList(
    LMM_MMC_PLMN_SRCH_CNF_STRU         *pstLmmPlmnSrchCnf
)
{
    VOS_UINT32                          ulIndex;
    RRC_PLMN_ID_LIST_STRU              *pstGuPlmnIdList;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNasRat;

    pstGuPlmnIdList   = (RRC_PLMN_ID_LIST_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                   sizeof(RRC_PLMN_ID_LIST_STRU));

    if (VOS_NULL_PTR == pstGuPlmnIdList)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmPlmnListSucc_PlmnList:ERROR: Memory Alloc Error");
        return;
    }


    /* ���µ�RAT������� */
    for ( ulIndex = 0; ulIndex < MMC_LMM_MAX_RAT_NUM; ulIndex++)
    {
        if ( MMC_LMM_RAT_LIST_SEARCH_CMPL == pstLmmPlmnSrchCnf->astSearchRatInfo[ulIndex].enListSearchRlt)
        {
            /* ��LMM RAT��ʽת��ΪNAS RAT��ʽ */
            NAS_MMC_ConvertLmmRatToNasFormat(pstLmmPlmnSrchCnf->astSearchRatInfo[ulIndex].enRat,
                                             &enNasRat);

            NAS_MMC_InitSpecRatSearchedPlmnListInfo_PlmnList(enNasRat);

            NAS_MMC_SetSearchedFlag_PlmnList(enNasRat);
            NAS_MMC_SetSpecRatSearchedTypeByLmmPlmnSearchCnfSucc_PlmnList(enNasRat, pstLmmPlmnSrchCnf->enRlst);
        }
    }

    /*ת��L��ʽ�������б���ΪGU��ʽ��*/
    NAS_MMC_ConvertLmmPlmnIdListToGUFormat(&(pstLmmPlmnSrchCnf->stPlmnIdList), pstGuPlmnIdList);

    /*���������б�*/
    NAS_MMC_UpdateSearchedPlmnListInfo_PlmnList(pstGuPlmnIdList);
    PS_MEM_FREE(WUEPS_PID_MMC, pstGuPlmnIdList);





    if (VOS_FALSE == NAS_MMC_GetNextSearchingRat_PlmnList(&enRat))
    {
        /* �ڲ��б��Ѳ��ϱ� */
        if ( VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
        {
            /* �����������������������ϱ���MSCC */
            NAS_MMC_SndMsccPlmnListCnf_PlmnList();
        }

        /* ����״̬���ɹ��˳��Ľ�� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_SUCC,
                                (VOS_UINT8)NAS_MMC_IsNeedPlmnSearch_PlmnList(),
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* ��LMM���͹�������,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatSuspendReq_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

    /* ��GMM��������ָʾ */
    NAS_MMC_SndGmmPlmnSchInit();

    /* ��MM��������ָʾ */
    NAS_MMC_SndMmPlmnSchInit();

    return;
}


VOS_VOID NAS_MMC_ProcLmmSearchCnf_InterPlmnListSearch_PlmnList(
    LMM_MMC_PLMN_SRCH_CNF_STRU         *pstLmmPlmnSrchCnf
)
{
    switch(pstLmmPlmnSrchCnf->enRlst)
    {
        case MMC_LMM_PLMN_SRCH_RLT_INTER_LIST_FULL_BAND_NO_RF:
        case MMC_LMM_PLMN_SRCH_RLT_INTER_LIST_PREF_BAND_NO_RF:

            NAS_MMC_ProcNoRf_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);
            break;

        case MMC_LMM_PLMN_SRCH_RLT_INTER_LIST_FULL_BAND_REJ:
        case MMC_LMM_PLMN_SRCH_RLT_INTER_LIST_FULL_BAND_FAIL:
        case MMC_LMM_PLMN_SRCH_RLT_INTER_LIST_PREF_BAND_REJ:
        case MMC_LMM_PLMN_SRCH_RLT_INTER_LIST_PREF_BAND_FAIL:

            /* ����״̬��ʧ���˳��Ľ�� */
            NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                    VOS_FALSE,
                                    NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                    NAS_MMC_GetRegRsltInfo_PlmnList());

            /* �˳�״̬�� */
            NAS_MMC_FSM_QuitFsmL2();
            break;

        case MMC_LMM_PLMN_SRCH_RLT_INTER_LIST_FULL_BAND_SUCC:
        case MMC_LMM_PLMN_SRCH_RLT_INTER_LIST_PREF_BAND_SUCC:

            NAS_MMC_ProcLmmPlmnListSucc_PlmnList(pstLmmPlmnSrchCnf);
            break;

        default:
            break;
    }

    return;
}


VOS_VOID  NAS_MMC_ProcLmmEpsOnlyTauResultInd_PlmnList(
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg
)
{
    VOS_UINT32                                              ulEquPlmnNum;
    MMC_LMM_PLMN_ID_STRU                                   *pstLmmEquPlmnList = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stLEplmnInfo;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enRegRsltCause;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;
    VOS_UINT8                                               ucSimCsRegStatus;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsRegAdditionalAction;

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    NAS_MMC_ConverTauResultToMMLCause(pstLmmTauIndMsg,&enRegRsltCause);

    if (MMC_LMM_TAU_RSLT_SUCCESS == pstLmmTauIndMsg->ulTauRst)
    {
        enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

        NAS_MMC_SaveRegRsltCtx(LMM_MMC_TAU_RESULT_IND, pstLmmTauIndMsg);


        /*ע��: ��Ҫ�ȸ���EPLMN LIST���ڴ���ע��״̬���ϱ�,��ΪNAS_MMC_UpdatePsRegStatePsRegSucc()�����л����EPLMN LIST�ϱ�ע��״̬ */
        /* ����EPLMN */
        if (VOS_TRUE == pstLmmTauIndMsg->bitOpEplmn)
        {
            ulEquPlmnNum        = pstLmmTauIndMsg->stEplmnList.ulPlmnNum;
            pstLmmEquPlmnList   = pstLmmTauIndMsg->stEplmnList.astEplmnList;

            NAS_MMC_ConvertLmmPlmnToGUNasPlmn(ulEquPlmnNum, pstLmmEquPlmnList, stLEplmnInfo.astEquPlmnAddr);

            /* ��EPLMN��Ϣ�������ڴ��� */
            NAS_MML_SaveEquPlmnList(ulEquPlmnNum, (stLEplmnInfo.astEquPlmnAddr));

            NAS_MMC_WriteEplmnNvim();
        }

        NAS_NORMAL_LOG(WUEPS_PID_MMC,"NAS_MMC_ProcLmmEpsOnlyTauResultInd_PlmnList: Update Reg state and Service state");
        NAS_MMC_UpdateServiceState_RegSucc(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_NORMAL_SERVICE);

        /* EPS����ע��ɹ�ʱ����Ҫɾ��ForbPlmn,ForbGprs����Ϣ */
        NAS_MMC_DelForbInfo_LmmAttRsltSucc(VOS_NULL_PTR, VOS_FALSE);

        /* �˴�����CS additionԭ��������TAU��EPS�ɹ�ʱ,LMM����T3411�ٴγ���TAU������,
           �û�Detach CS,LMM��ֱ�ӱ�TAU�ɹ�,���ٳ�������TAU */
        NAS_MMC_SetCsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON);

        /* ���CS����ע�����CS����Ч�����CSע��״̬ΪNAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
        ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();
        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (VOS_TRUE == ucSimCsRegStatus))
        {
            NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_EPS_ONLY_ATTACH);

            NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }

        /*ע��: ��Ҫ�ȸ���EPLMN LIST���ڴ���ע��״̬���ϱ�,��ΪNAS_MMC_UpdatePsRegStatePsRegSucc()�����л����EPLMN LIST�ϱ�ע��״̬ */

        NAS_MMC_UpdateGURegRlstRPlmnIdInNV();


        NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                                 NAS_MML_GetSimPsRegStatus());

        NAS_MMC_SetUserSpecPlmnRegisterStatus(VOS_TRUE);

        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_PS, VOS_TRUE, NAS_MML_REG_FAIL_CAUSE_NULL);
    }
    else if ((MMC_LMM_TAU_RSLT_FAILURE == pstLmmTauIndMsg->ulTauRst)
          && (VOS_FALSE == pstLmmTauIndMsg->bitOpAtmpCnt))
    {
        enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;

        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_PS, VOS_FALSE, NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);
    }
    else if (MMC_LMM_TAU_RSLT_T3402_RUNNING_EPS_ONLY_SUCC == pstLmmTauIndMsg->ulTauRst)
    {
        NAS_MMC_ProcCombinedEpsRegFailCauseT3402RunningEpsOnlySucc(LMM_MMC_TAU_RESULT_IND, pstLmmTauIndMsg,
                                          &enAdditionalAction, &enCsRegAdditionalAction);
    }
    else
    {
        enAdditionalAction = NAS_MMC_ProcEpsTauRegFail(LMM_MMC_TAU_RESULT_IND, pstLmmTauIndMsg);

        NAS_MMC_UpdateUserSpecPlmnRegisterStatusWhenRegFail(enRegRsltCause);
    }

    /* AdditionalAction��Ч������EPS����һ���Ķ������� */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_PlmnList(enAdditionalAction);
    }
    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn())
    {
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);

        NAS_MMC_SndOmEquPlmn();

        /* ֪ͨCSS GEO��Ϣ */
        NAS_MMC_SndCssCurrGeoInd(VOS_TRUE, stSndEquPlmnInfo.ucEquPlmnNum, stSndEquPlmnInfo.astEquPlmnAddr);
    }

    return;
}


VOS_VOID  NAS_MMC_ProcLmmTauResultInd_PlmnList(
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg
)
{
    switch (pstLmmTauIndMsg->ulReqType)
    {
        case MMC_LMM_COMBINED_TA_LA_UPDATING:
        case MMC_LMM_COMBINED_TA_LA_WITH_IMSI:
        case MMC_LMM_CS_PS_PERIODIC_UPDATING:

            /* ����lmm������tau��� */
            NAS_MMC_ProcLmmCombinedTauResultInd_PlmnList(pstLmmTauIndMsg);
            break;

        case MMC_LMM_TA_UPDATING:
        case MMC_LMM_PS_PERIODIC_UPDATING:
            if (VOS_TRUE == NAS_MML_GetEpsEmcAttachFlg())
            {
                /* ����LMM��EPS�����ATTACH���ϱ���TAU��� */
                NAS_MMC_ProcLmmEpsEmergencyTauResultInd_PlmnList(pstLmmTauIndMsg);
            }
            else
            {
                /* ����lmm�ķ�����tau��EPS onlyע��Ľ�� */
                NAS_MMC_ProcLmmEpsOnlyTauResultInd_PlmnList(pstLmmTauIndMsg);
            }
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmTauResultInd_PlmnList:Unexpected tau req type!");
            break;

    }

    return;
}


VOS_VOID  NAS_MMC_ProcLmmCombinedAttachInd_PlmnList(
    LMM_MMC_ATTACH_IND_STRU            *pstLmmAttachIndMsg
)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enPsRegRsltCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegRsltCause;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;

    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    enPsAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;
    enCsAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;

    NAS_MMC_ConverLmmCombinedAttachRsltToMMLCause(pstLmmAttachIndMsg,&enPsRegRsltCause, &enCsRegRsltCause);

    /* ���EPS�����ATTACH��־ */
    NAS_MML_SetEpsEmcAttachFlg(VOS_FALSE);

    switch (pstLmmAttachIndMsg->ulAttachRslt)
    {
        case MMC_LMM_ATT_RSLT_SUCCESS:
            NAS_MMC_ProcLmmCombinedAttachInd_AttRsltSucc(pstLmmAttachIndMsg,
                       enCsRegRsltCause, &enCsAdditionalAction, &enPsAdditionalAction);

            break;

        case MMC_LMM_ATT_RSLT_FAILURE:
            if (VOS_FALSE == pstLmmAttachIndMsg->bitOpAtmpCnt)
            {
                enPsAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
                enCsAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;

                NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, VOS_FALSE, NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);
            }
            else
            {
                NAS_MMC_ProcCombinedAttachEpsRegFail(LMM_MMC_ATTACH_IND, pstLmmAttachIndMsg,
                                      &enPsAdditionalAction, &enCsAdditionalAction);
            }
            break;

        case MMC_LMM_ATT_RSLT_ESM_FAILURE:
        case MMC_LMM_ATT_RSLT_MO_DETACH_FAILURE:
        case MMC_LMM_ATT_RSLT_MT_DETACH_FAILURE:
        case MMC_LMM_ATT_RSLT_T3402_RUNNING:
        case MMC_LMM_ATT_RSLT_TIMER_EXP:
        case MMC_LMM_ATT_RSLT_ACCESS_BAR:
        case MMC_LMM_ATT_RSLT_FORBID_PLMN:
        case MMC_LMM_ATT_RSLT_FORBID_TA_FOR_RPOS:
        case MMC_LMM_ATT_RSLT_FORBID_PLMN_FOR_GPRS:
        case MMC_LMM_ATT_RSLT_FORBID_TA_FOR_ROAMING:
        case MMC_LMM_ATT_RSLT_AUTH_REJ:
        case MMC_LMM_ATT_RSLT_PS_ATT_NOT_ALLOW:
            NAS_MMC_ProcCombinedAttachEpsRegFail(LMM_MMC_ATTACH_IND, pstLmmAttachIndMsg,
                                  &enPsAdditionalAction, &enCsAdditionalAction);
            break;

        case MMC_LMM_ATT_RSLT_CN_REJ:
            if ((VOS_TRUE == pstLmmAttachIndMsg->bitOpCnRslt)
             && (MMC_LMM_ATT_CN_RSLT_EPS_ONLY == pstLmmAttachIndMsg->ulCnRslt))
            {
                /* ��ATTACH��������Ϊ���ϣ�������Ӧ��ATTACH�������ΪEPS ONLY��
                   ��ԭ��ֵ��ΪЭ��24301 5.5.1.3.4.3�½����л���û��Я��ԭ��ֵ��
                   ��LMMͨ��ATTACH�����MMC_LMM_ATT_RSLT_CN_REJ֪ͨMMC��
                   ��Я����Ӧ��ATTACH�������͡�������Ӧ��ATTCH������͡�ԭ��ֵ��
                   ��Я��������ԭ����attach attempt counterֵ */
                NAS_MMC_ProcLmmCombinedAttachInd_AttRsltEpsOnlySucc(pstLmmAttachIndMsg,enCsRegRsltCause,
                                  &enCsAdditionalAction, &enPsAdditionalAction);
            }
            else
            {
                NAS_MMC_ProcCombinedAttachEpsRegFail(LMM_MMC_ATTACH_IND, pstLmmAttachIndMsg,
                                      &enPsAdditionalAction, &enCsAdditionalAction);
            }
            break;

        default:
            /* �쳣��ӡ */
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmCombinedAttachInd_PlmnList:Unexpected attach result!");
            enPsAdditionalAction = NAS_MMC_GetPsRegAdditionalAction_PlmnList();
            enCsAdditionalAction = NAS_MMC_GetCsRegAdditionalAction_PlmnList();
            break;

    }

    /* AdditionalAction��Ч������EPS����һ���Ķ������� */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enPsAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_PlmnList(enPsAdditionalAction);
    }

    /* AdditionalAction��Ч������CS����һ���Ķ������� */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enCsAdditionalAction )
    {
        NAS_MMC_SetCsRegAdditionalAction_PlmnList(enCsAdditionalAction);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn())
    {
        pstEquPlmnInfo       = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);

        NAS_MMC_SndOmEquPlmn();

        /* ֪ͨCSS GEO��Ϣ */
        NAS_MMC_SndCssCurrGeoInd(VOS_TRUE, stSndEquPlmnInfo.ucEquPlmnNum, stSndEquPlmnInfo.astEquPlmnAddr);
    }


    NAS_MMC_UpdateUserSpecPlmnRegisterStatus(enPsRegRsltCause);

    return;

}


VOS_VOID  NAS_MMC_ProcLmmCombinedTauResultInd_PlmnList(
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg
)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enPsRegRsltCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegRsltCause;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;

    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));
    enPsAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;
    enCsAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;

    NAS_MMC_ConverLmmCombinedTauRsltToMMLCause(pstLmmTauIndMsg, &enPsRegRsltCause, &enCsRegRsltCause);

    NAS_MMC_ProcLmmCombinedTauResult(pstLmmTauIndMsg, enCsRegRsltCause,
                                    &enPsAdditionalAction, &enCsAdditionalAction);


    /* AdditionalAction��Ч������EPS����һ���Ķ������� */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enPsAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_PlmnList(enPsAdditionalAction);
    }

    /* AdditionalAction��Ч������CS����һ���Ķ������� */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enCsAdditionalAction )
    {
        NAS_MMC_SetCsRegAdditionalAction_PlmnList(enCsAdditionalAction);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn())
    {
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);

        NAS_MMC_SndOmEquPlmn();

        /* ֪ͨCSS GEO��Ϣ */
        NAS_MMC_SndCssCurrGeoInd(VOS_TRUE, stSndEquPlmnInfo.ucEquPlmnNum, stSndEquPlmnInfo.astEquPlmnAddr);
    }


    NAS_MMC_UpdateUserSpecPlmnRegisterStatus(enPsRegRsltCause);

    return;
}


VOS_VOID  NAS_MMC_ProcLmmEpsOnlyAttachResultInd_PlmnList(
    LMM_MMC_ATTACH_IND_STRU            *pstLmmAttachIndMsg
)
{
    VOS_UINT32                                              ulEquPlmnNum;
    MMC_LMM_PLMN_ID_STRU                                   *pstLmmEquPlmnList = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stLEplmnInfo;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enRegRsltCause;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;

    VOS_UINT8                                               ucSimCsRegStatus;

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    NAS_MMC_ConverLmmAttachRsltToMMLCause(pstLmmAttachIndMsg, &enRegRsltCause);

    /* ���EPS�����ATTACH��־ */
    NAS_MML_SetEpsEmcAttachFlg(VOS_FALSE);

    if (MMC_LMM_ATT_RSLT_SUCCESS == pstLmmAttachIndMsg->ulAttachRslt)
    {
        enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

        NAS_MMC_SaveRegRsltCtx(LMM_MMC_ATTACH_IND, pstLmmAttachIndMsg);

        /*ע��: ��Ҫ�ȸ���EPLMN LIST���ڴ���ע��״̬���ϱ�,��ΪNAS_MMC_UpdatePsRegStatePsRegSucc()�����л����EPLMN LIST�ϱ�ע��״̬ */
        /* ����EPLMN */
        if ( VOS_TRUE == pstLmmAttachIndMsg->bitOpEplmn)
        {
            ulEquPlmnNum        = pstLmmAttachIndMsg->stEplmnList.ulPlmnNum;
            pstLmmEquPlmnList   = pstLmmAttachIndMsg->stEplmnList.astEplmnList;

            /* LMM PLMN ID��ʽת��ΪMMC��PLMN ID�ĸ�ʽ  */
            NAS_MMC_ConvertLmmPlmnToGUNasPlmn(ulEquPlmnNum, pstLmmEquPlmnList, (stLEplmnInfo.astEquPlmnAddr));

            /* ��EPLMN��Ϣ�������ڴ��� */
            NAS_MML_SaveEquPlmnList(ulEquPlmnNum, (stLEplmnInfo.astEquPlmnAddr));

            NAS_MMC_WriteEplmnNvim();
        }

        NAS_NORMAL_LOG(WUEPS_PID_MMC,"NAS_MMC_ProcLmmEpsOnlyAttachResultInd_PlmnList: Update Reg state and Service state");
        NAS_MMC_UpdateServiceState_RegSucc(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_NORMAL_SERVICE);

        /* EPS����ע��ɹ�ʱ����Ҫɾ��ForbPlmn,ForbGprs����Ϣ */
        NAS_MMC_DelForbInfo_LmmAttRsltSucc(VOS_NULL_PTR, NAS_MMC_IsEpsEmergencyAttachType(pstLmmAttachIndMsg->ulReqType));

        /* ���CS����ע�����CS����Ч�����CSע��״̬ΪNAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
        ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();
        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (VOS_TRUE == ucSimCsRegStatus))
        {
            NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_EPS_ONLY_ATTACH);

            NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }


        NAS_MMC_UpdateGURegRlstRPlmnIdInNV();


        NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                                 NAS_MML_GetSimPsRegStatus());



        NAS_MMC_SetUserSpecPlmnRegisterStatus(VOS_TRUE);

        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_PS, VOS_TRUE, NAS_MML_REG_FAIL_CAUSE_NULL);
    }
    else if ((MMC_LMM_ATT_RSLT_FAILURE == pstLmmAttachIndMsg->ulAttachRslt)
          && (VOS_FALSE == pstLmmAttachIndMsg->bitOpAtmpCnt))
    {
        enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;

        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_PS, VOS_FALSE, NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);
    }
    else
    {
        enAdditionalAction= NAS_MMC_ProcEpsAttachRegFail(LMM_MMC_ATTACH_IND, pstLmmAttachIndMsg);

        NAS_MMC_UpdateUserSpecPlmnRegisterStatusWhenRegFail(enRegRsltCause);
    }

    /* AdditionalAction��Ч������EPS����һ���Ķ������� */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_PlmnList(enAdditionalAction);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn())
    {
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);

        NAS_MMC_SndOmEquPlmn();

        /* ֪ͨCSS GEO��Ϣ */
        NAS_MMC_SndCssCurrGeoInd(VOS_TRUE, stSndEquPlmnInfo.ucEquPlmnNum, stSndEquPlmnInfo.astEquPlmnAddr);
    }

    return;
}



VOS_VOID  NAS_MMC_ProcLmmAttachInd_PlmnList(
    LMM_MMC_ATTACH_IND_STRU            *pstLmmAttachIndMsg
)
{
    switch (pstLmmAttachIndMsg->ulReqType)
    {
        case MMC_LMM_ATT_TYPE_COMBINED_EPS_IMSI:

            /* ����lmm������attach��� */
            NAS_MMC_ProcLmmCombinedAttachInd_PlmnList(pstLmmAttachIndMsg);
            break;

        case MMC_LMM_ATT_TYPE_EPS_ONLY:

            /* ����lmm�ķ�����attach��EPS onlyע��Ľ�� */
            NAS_MMC_ProcLmmEpsOnlyAttachResultInd_PlmnList(pstLmmAttachIndMsg);
            break;

        case MMC_LMM_ATT_TYPE_EPS_EMERGENCY:

            /* ����LMM��EPS�����ATTACH�Ľ�� */
            NAS_MMC_ProcLmmEpsEmergencyAttachInd_PlmnList(pstLmmAttachIndMsg);
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmAttachInd_PlmnList:Unexpected attach req type!");
            break;

    }

    return;
}


VOS_VOID  NAS_MMC_ProcLmmEpsEmergencyAttachInd_PlmnList(
    LMM_MMC_ATTACH_IND_STRU            *pstLmmAttachIndMsg
)
{
    VOS_UINT32                                              ulEquPlmnNum;
    MMC_LMM_PLMN_ID_STRU                                   *pstLmmEquPlmnList = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stLEplmnInfo;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enRegRsltCause;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;
    VOS_UINT8                                               ucSimCsRegStatus;

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    NAS_MMC_ConverLmmAttachRsltToMMLCause(pstLmmAttachIndMsg, &enRegRsltCause);

    /* ���EPS�����ATTACH��־ */
    NAS_MML_SetEpsEmcAttachFlg(VOS_FALSE);

    if (MMC_LMM_ATT_RSLT_SUCCESS == pstLmmAttachIndMsg->ulAttachRslt)
    {
        /* ����ATTACH�ɹ�������EPS�����ATTACH��־ */
        NAS_MML_SetEpsEmcAttachFlg(VOS_TRUE);

        enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

        NAS_MMC_SaveRegRsltCtx(LMM_MMC_ATTACH_IND, pstLmmAttachIndMsg);

        /*ע��: ��Ҫ�ȸ���EPLMN LIST���ڴ���ע��״̬���ϱ�,��ΪNAS_MMC_UpdatePsRegStatePsRegSucc()�����л����EPLMN LIST�ϱ�ע��״̬ */
        /* ����EPLMN */
        if ( VOS_TRUE == pstLmmAttachIndMsg->bitOpEplmn)
        {
            ulEquPlmnNum        = pstLmmAttachIndMsg->stEplmnList.ulPlmnNum;
            pstLmmEquPlmnList   = pstLmmAttachIndMsg->stEplmnList.astEplmnList;

            /* LMM PLMN ID��ʽת��ΪMMC��PLMN ID�ĸ�ʽ  */
            NAS_MMC_ConvertLmmPlmnToGUNasPlmn(ulEquPlmnNum, pstLmmEquPlmnList, (stLEplmnInfo.astEquPlmnAddr));

            /* ��EPLMN��Ϣ�������ڴ��� */
            NAS_MML_SaveEquPlmnList(ulEquPlmnNum, (stLEplmnInfo.astEquPlmnAddr));
        }

        /* ���CS����ע�����CS����Ч�����CSע��״̬ΪNAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
        ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();
        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (VOS_TRUE == ucSimCsRegStatus))
        {
            NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_EPS_ONLY_ATTACH);

            NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }

        NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                                 NAS_MML_GetSimPsRegStatus());

    }
    else if ((MMC_LMM_ATT_RSLT_FAILURE == pstLmmAttachIndMsg->ulAttachRslt)
          && (VOS_FALSE == pstLmmAttachIndMsg->bitOpAtmpCnt))
    {
        enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;

        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_PS, VOS_FALSE, NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);
    }
    else
    {
        enAdditionalAction= NAS_MMC_ProcEpsAttachRegFail(LMM_MMC_ATTACH_IND, pstLmmAttachIndMsg);

        NAS_MMC_UpdateUserSpecPlmnRegisterStatusWhenRegFail(enRegRsltCause);
    }

    /* AdditionalAction��Ч������EPS����һ���Ķ������� */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_PlmnList(enAdditionalAction);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn())
    {
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);

        NAS_MMC_SndOmEquPlmn();

        /* ֪ͨCSS GEO��Ϣ */
        NAS_MMC_SndCssCurrGeoInd(VOS_TRUE, stSndEquPlmnInfo.ucEquPlmnNum, stSndEquPlmnInfo.astEquPlmnAddr);
    }

    return;
}


VOS_VOID  NAS_MMC_ProcLmmEpsEmergencyTauResultInd_PlmnList(
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg
)
{
    VOS_UINT32                                              ulEquPlmnNum;
    MMC_LMM_PLMN_ID_STRU                                   *pstLmmEquPlmnList   = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stLEplmnInfo;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enRegRsltCause;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo      = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;
    VOS_UINT8                                               ucSimCsRegStatus;

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    NAS_MMC_ConverTauResultToMMLCause(pstLmmTauIndMsg,&enRegRsltCause);

    if (MMC_LMM_TAU_RSLT_SUCCESS == pstLmmTauIndMsg->ulTauRst)
    {
        enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;

        NAS_MMC_SaveRegRsltCtx(LMM_MMC_TAU_RESULT_IND, pstLmmTauIndMsg);

        /*ע��: ��Ҫ�ȸ���EPLMN LIST���ڴ���ע��״̬���ϱ�,��ΪNAS_MMC_UpdatePsRegStatePsRegSucc()�����л����EPLMN LIST�ϱ�ע��״̬ */
        /* ����EPLMN */
        if (VOS_TRUE == pstLmmTauIndMsg->bitOpEplmn)
        {
            ulEquPlmnNum        = pstLmmTauIndMsg->stEplmnList.ulPlmnNum;
            pstLmmEquPlmnList   = pstLmmTauIndMsg->stEplmnList.astEplmnList;

            NAS_MMC_ConvertLmmPlmnToGUNasPlmn(ulEquPlmnNum, pstLmmEquPlmnList, stLEplmnInfo.astEquPlmnAddr);

            /* ��EPLMN��Ϣ�������ڴ��� */
            NAS_MML_SaveEquPlmnList(ulEquPlmnNum, (stLEplmnInfo.astEquPlmnAddr));
        }

        /* �˴�����CS additionԭ��������TAU��EPS�ɹ�ʱ,LMM����T3411�ٴγ���TAU������,
           �û�Detach CS,LMM��ֱ�ӱ�TAU�ɹ�,���ٳ�������TAU */
        NAS_MMC_SetCsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON);

        /* ���CS����ע�����CS����Ч�����CSע��״̬ΪNAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
        ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();
        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (VOS_TRUE == ucSimCsRegStatus))
        {
            NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }

        NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                                 NAS_MML_GetSimPsRegStatus());

    }
    else if ((MMC_LMM_TAU_RSLT_FAILURE == pstLmmTauIndMsg->ulTauRst)
          && (VOS_FALSE == pstLmmTauIndMsg->bitOpAtmpCnt))
    {
        enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;

        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_PS, VOS_FALSE, NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);
    }
    else
    {
        enAdditionalAction = NAS_MMC_ProcEpsTauRegFail(LMM_MMC_TAU_RESULT_IND, pstLmmTauIndMsg);
    }

    /* AdditionalAction��Ч������EPS����һ���Ķ������� */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_PlmnList(enAdditionalAction);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn())
    {
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);

        NAS_MMC_SndOmEquPlmn();

        /* ֪ͨCSS GEO��Ϣ */
        NAS_MMC_SndCssCurrGeoInd(VOS_TRUE, stSndEquPlmnInfo.ucEquPlmnNum, stSndEquPlmnInfo.astEquPlmnAddr);
    }

    return;
}

#endif


VOS_VOID NAS_MMC_ProcNoRf_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat
)
{
    /* פ��̬ʱ,RRC֪ͨNAS��ǰLIST �������ΪNO RFʱ,����RRC������פ��̬,
       ����������;��פ��̬���� */
    if (NAS_MMC_AS_CELL_NOT_CAMP_ON == NAS_MMC_GetAsCellCampOn())
    {
        /* ��¼NO RF */
        NAS_MML_SetCurrRatRfAvailFlg(enCurRat, VOS_FALSE);

        /* ��MSCC֪ͨ��ǰNO RF��Ϣ  */
        NAS_MMC_SndMsccRfAvailInd(VOS_FALSE);

        /* ��RRM����ע�� */
        NAS_MMC_RegisterRrmResourceNtf(enCurRat, RRM_PS_TASK_TYPE_NAS_SEARCH);
    }

    NAS_MMC_SndMsccPlmnListRejMsg_PlmnList();


    /* ����״̬��ʧ�ܵ��˳���� */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_NO_RF_FAIL,
                             VOS_FALSE,
                             NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                             NAS_MMC_GetRegRsltInfo_PlmnList());

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return;
}


#if (FEATURE_ON == FEATURE_CSG)

VOS_UINT32  NAS_MMC_RcvMsccCsgListReq_PlmnList_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapStatus;

    /* ��ȡLTE����״̬ */
    enLteCapStatus = NAS_MML_GetLteCapabilityStatus();
#endif

    /* ���浱ǰ��ϢΪ״̬�������Ϣ */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)
        /* ����disable L�ı�� */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == enLteCapStatus)
     || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLteCapStatus))
    {
        NAS_MMC_SetPreLteDisableFlg_PlmnList(VOS_TRUE);
    }
    else
    {
        NAS_MMC_SetPreLteDisableFlg_PlmnList(VOS_FALSE);
    }
#endif

    /* ��ʼ������б��ѵ�PLMN */
    NAS_MMC_InitAbortListSearchPlmn();

    /* �ж��Ƿ���Ҫanycell����,��Ҫ������anycell ������� */
    if (VOS_TRUE == NAS_MMC_IsNeedAnyCellSrch_PlmnList())
    {
        NAS_MMC_SetAnyCellSrchFlg_PlmnList(VOS_TRUE);
    }

    /* �����û�LIST�������� */
    NAS_MMC_ProcUserCsgListReq_PlmnList();

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvTiPeriodTryingUserCsgListExpired_PlmnList_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapStatus;

    /* ��ȡLTE����״̬ */
    enLteCapStatus = NAS_MML_GetLteCapabilityStatus();
#endif

    /* ���浱ǰ��ϢΪ״̬�������Ϣ */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)
        /* ����disable L�ı�� */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == enLteCapStatus)
     || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLteCapStatus))
    {
        NAS_MMC_SetPreLteDisableFlg_PlmnList(VOS_TRUE);
    }
    else
    {
        NAS_MMC_SetPreLteDisableFlg_PlmnList(VOS_FALSE);
    }
#endif

    /* ��ʼ������б��ѵ�PLMN */
    NAS_MMC_InitAbortListSearchPlmn();

    /* �ж��Ƿ���Ҫanycell����,��Ҫ������anycell ������� */
    if (VOS_TRUE == NAS_MMC_IsNeedAnyCellSrch_PlmnList())
    {
        NAS_MMC_SetAnyCellSrchFlg_PlmnList(VOS_TRUE);
    }

    /* �����û�LIST�������� */
    NAS_MMC_ProcUserCsgListReq_PlmnList();

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvMsccCsgListAbortReq_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

    /* ����csg LIST ABORT CNF */
    NAS_MMC_SndMsccCsgListAbortCnf_PlmnList();

    /* δ��ʼ��������ʱ�����б�Ϊ��,��¼��ǰע�ᵼ�µĺ���additionֵ��L1 MAIN��
       �յ���·�ͷź����additionֵ�����Ƿ񴥷����� */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvMsccCsgListAbortReq_PlmnList_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼״̬���˳���� */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ��¼֪ͨMSCC������ */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvMsccCsgListAbortReq_PlmnList_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼״̬���˳���� */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ��¼֪ͨMSCC������ */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvCsgListAbortReq_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

    /* ����csg list abort cnf */
    NAS_MMC_SndMsccCsgListAbortCnf_PlmnList();

    /* δ��ʼ�������û���LIST������ʱ����ʱ����ʱ�����б�Ϊ��
       ��¼��ǰע�ᵼ�µĺ���additionֵ��L1 MAIN���յ���·�ͷź�
       ����additionֵ�����Ƿ񴥷����� */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());

    /* �˳�״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_VOID NAS_MMC_BuildReportCsgIdList_PlmnList(
    NAS_MSCC_PIF_PLMN_WITH_CSG_ID_INFO_STRU                *pstCsgIdInfoList
)
{
    VOS_UINT32                          ulServiceRslt;

    ulServiceRslt = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_OP_CSG);

    /* ����LTE-BTR-1-0770�������AT&T������EF Operator List����(Service n90����)��
    ֻ�ϱ�Operator List�е�CSG ID�����������EF Operator List(��������ڣ�����
    ��Ϊ�ղ���)������EFAD��ֵȷ���Ƿ��ϱ����е�CSG ID */
    if ((VOS_TRUE == NAS_MML_GetOnlyReportOperatorCsgListFlag())
      &&(PS_USIM_SERVICE_AVAILIABLE == ulServiceRslt))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_BuildReportCsgIdList_PlmnList: only report csg id in operator list");

        NAS_MMC_BuildReportCsgIdListInOperatorCsgList_PlmnList(pstCsgIdInfoList);
        return;
    }

    /* ��׼Э��ʵ�� */
    NAS_MMC_BuildReportCsgIdListAccordingCsgDisplayIndicator_PlmnList(pstCsgIdInfoList);

    return;
}


VOS_VOID NAS_MMC_BuildReportCsgIdListInOperatorCsgList_PlmnList(
    NAS_MSCC_PIF_PLMN_WITH_CSG_ID_INFO_STRU                *pstCsgIdInfoList
)
{
    VOS_UINT32                                              i;
    NAS_MML_PLMN_ID_STRU                                    stPlmnId;
    NAS_MML_PLMN_WITH_CSG_ID_STRU                           stPlmnCsgId;
    NAS_MMC_CSG_SEARCHED_PLMN_LIST_INFO_STRU               *pstCsgPlmnIdList = VOS_NULL_PTR;
    NAS_MML_CSG_ID_TYPE_ENUM_UINT8                          aenCsgIdType[NAS_MML_MAX_PLMN_CSG_ID_NUM]; /* ���ڰ��򱣴���Ӧ��CSG���� */

    /* �ֲ�������ʼ�� */
    stPlmnId.ulMcc             = NAS_MML_INVALID_MCC;
    stPlmnId.ulMnc             = NAS_MML_INVALID_MNC;
    stPlmnCsgId.stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    stPlmnCsgId.stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
    stPlmnCsgId.ulCsgId        = 0;
    PS_MEM_SET(aenCsgIdType,   NAS_MML_CSG_ID_TYPE_BUTT, NAS_MML_MAX_PLMN_CSG_ID_NUM);

    pstCsgPlmnIdList = NAS_MMC_GetCsgSearchedPlmnListInfo_PlmnList();

    /* �����ϱ��б���ԭ��Ϊ����Operator list��(�ǽ�ֹ)�����ϱ�˳��ΪRPLMN->HPLMN->OTHER PLMN��
    ��˳�򲢲����ǵ�ǰPLMN�Ǹ��������ǵ�������Ҳ����ȫ�������մ�˳��ԭ������ţ��п��ܵ�������
    ���ڸ�������ǰ�棬�����б�ʱ���ÿ���Խ����������Ϊ����״̬�������ı����������Ϊ35��������Խ�� */

    /* ��һ��ѭ���ȷ�RPLMN��CSG ID */
    for (i = 0; i < NAS_MML_MIN(pstCsgPlmnIdList->ulTotalPlmnNum, RRC_NAS_MAX_PLMN_CSG_ID_NUM); i++)
    {
        /* ȡ��iλ�õ�PLMN CSG ID����Ϊ��ȡCSG ID TYPE����� */
        stPlmnCsgId.stPlmnId.ulMcc = pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMcc;
        stPlmnCsgId.stPlmnId.ulMnc = pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMnc;
        stPlmnCsgId.ulCsgId        = pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stPlmnCsgIdWithRat.ulCsgId;

        /* ��������ѭ�������е�CSG ID������ʶ��������´�ѭ��ʱ�Ϳ�ֱ��ʹ�ñ��α���Ľ�� */
        aenCsgIdType[i] = NAS_MMC_GetCsgIdType_PlmnList(&stPlmnCsgId);

        /* �����Operator List�е�����RPLMN���ӵ��ϱ���MSCC���б���(��ֹ���Ȳ��ϱ�) */
        if ((NAS_MML_CSG_ID_TYPE_IN_OPERATOR_CSG_LIST_NOT_FOBIDDEN == aenCsgIdType[i])
          ||(NAS_MML_CSG_ID_TYPE_IN_ALLOWED_AND_OPERATOR_CSG_LIST == aenCsgIdType[i]))
        {
            stPlmnId.ulMcc = stPlmnCsgId.stPlmnId.ulMcc;
            stPlmnId.ulMnc = stPlmnCsgId.stPlmnId.ulMnc;

            if (VOS_TRUE == NAS_MMC_IsPlmnSameWithRplmn(&stPlmnId))
            {
                /* �����ϱ����CNF�б��� */
                NAS_MMC_AddCsgIdToListCnf_PlmnList(i, aenCsgIdType[i], pstCsgIdInfoList);

                /* �´�ѭ�����ٴ�����λ�õ�CSG ID */
                aenCsgIdType[i] = NAS_MML_CSG_ID_TYPE_BUTT;
            }
        }
    }

    /* �ڶ���ѭ����HPLMN��CSG ID */
    for (i = 0; i < NAS_MML_MIN(pstCsgPlmnIdList->ulTotalPlmnNum, RRC_NAS_MAX_PLMN_CSG_ID_NUM); i++)
    {
        /* �����Operator List������HPLMN�����ӵ��ϱ���MSCC���б���(��ֹ���Ȳ��ϱ�) */
        if ((NAS_MML_CSG_ID_TYPE_IN_OPERATOR_CSG_LIST_NOT_FOBIDDEN == aenCsgIdType[i])
          ||(NAS_MML_CSG_ID_TYPE_IN_ALLOWED_AND_OPERATOR_CSG_LIST == aenCsgIdType[i]))
        {
            stPlmnId.ulMcc = pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMcc;
            stPlmnId.ulMnc = pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMnc;

            if (VOS_TRUE == NAS_MML_ComparePlmnIdWithHplmn(&stPlmnId))
            {
                /* �����ϱ����CNF�б��� */
                NAS_MMC_AddCsgIdToListCnf_PlmnList(i, aenCsgIdType[i], pstCsgIdInfoList);

                /* �´�ѭ�����ٴ�����λ�õ�CSG ID */
                aenCsgIdType[i] = NAS_MML_CSG_ID_TYPE_BUTT;
            }
        }
    }

    /* ������ѭ��������PLMN��CSG ID */
    for (i = 0; i < NAS_MML_MIN(pstCsgPlmnIdList->ulTotalPlmnNum, RRC_NAS_MAX_PLMN_CSG_ID_NUM); i++)
    {
        /* �����Operator List�е����ӵ��ϱ���MSCC���б���(��ֹ���Ȳ��ϱ�) */
        if ((NAS_MML_CSG_ID_TYPE_IN_OPERATOR_CSG_LIST_NOT_FOBIDDEN == aenCsgIdType[i])
          ||(NAS_MML_CSG_ID_TYPE_IN_ALLOWED_AND_OPERATOR_CSG_LIST == aenCsgIdType[i]))
        {
            /* �����ϱ����CNF�б��� */
            NAS_MMC_AddCsgIdToListCnf_PlmnList(i, aenCsgIdType[i], pstCsgIdInfoList);

            /* �´�ѭ�����ٴ�����λ�õ�CSG ID */
            aenCsgIdType[i] = NAS_MML_CSG_ID_TYPE_BUTT;
        }
    }

    /* ��������operator list�Ĳ��ϱ� */
    return;
}


VOS_VOID NAS_MMC_BuildReportCsgIdListAccordingCsgDisplayIndicator_PlmnList(
    NAS_MSCC_PIF_PLMN_WITH_CSG_ID_INFO_STRU                *pstCsgIdInfoList
)
{
    VOS_UINT32                                              i;
    NAS_MML_CSG_ID_TYPE_ENUM_UINT8                          enCsgIdType;
    NAS_MML_PLMN_WITH_CSG_ID_STRU                           stPlmnCsgId;
    NAS_MMC_CSG_SEARCHED_PLMN_LIST_INFO_STRU               *pstCsgPlmnIdList = VOS_NULL_PTR;
    NAS_MML_CSG_ID_TYPE_ENUM_UINT8                          aenCsgIdType[NAS_MML_MAX_PLMN_CSG_ID_NUM]; /* ���ڰ��򱣴���Ӧ��CSG���� */

    /* �ֲ�������ʼ�� */
    enCsgIdType                = NAS_MML_CSG_ID_TYPE_BUTT;
    stPlmnCsgId.stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    stPlmnCsgId.stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
    stPlmnCsgId.ulCsgId        = 0;
    PS_MEM_SET(aenCsgIdType,   NAS_MML_CSG_ID_TYPE_BUTT, NAS_MML_MAX_PLMN_CSG_ID_NUM);

    pstCsgPlmnIdList = NAS_MMC_GetCsgSearchedPlmnListInfo_PlmnList();

    /* �����ϱ��б���ԭ��Ϊ������ָʾ������ʾ���ϱ�˳��ΪALLOWED LIST->OPERATOR LIST->AVAILABLE LIST��
    ��˳�򲢲����ǵ�ǰPLMN�Ǹ��������ǵ�������Ҳ����ȫ�������մ�˳��ԭ������ţ��п��ܵ�������
    ���ڸ�������ǰ�棬�����б�ʱ���ÿ���Խ����������Ϊ����״̬�������ı����������Ϊ35��������Խ�� */

    /* ����PLMN LIST״̬���������б������������CSG PLMN ID */
    for (i = 0; i < NAS_MML_MIN(pstCsgPlmnIdList->ulTotalPlmnNum, RRC_NAS_MAX_PLMN_CSG_ID_NUM); i++)
    {
        /* ��ʼ����ʱ����PLMN+CSG ID��ֵΪ��ǰ���ж�Ӧ���ֵ */
        stPlmnCsgId.stPlmnId.ulMcc = pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMcc;
        stPlmnCsgId.stPlmnId.ulMnc = pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMnc;
        stPlmnCsgId.ulCsgId        = pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stPlmnCsgIdWithRat.ulCsgId;

        /* ��ȡCSG ID���� */
        enCsgIdType  = NAS_MMC_GetCsgIdType_PlmnList(&stPlmnCsgId);

        /* �������ָʾ�����ϱ���ֱ��������CSG ID */
        if (VOS_TRUE != NAS_MMC_IsSpecCsgIdDisplayIndicatorNeedReport_PlmnList(&stPlmnCsgId, enCsgIdType))
        {
            /* ��Ӧ���鵥ԪaenCsgIdType[i] = NAS_MML_CSG_ID_TYPE_BUTT��Ҳ����û������ */
            continue;
        }

        /* ����ָʾ�����ϱ�������CSG ID���� */
        if (NAS_MML_MAX_PLMN_CSG_ID_NUM > i)
        {
            aenCsgIdType[i] = enCsgIdType;
        }
    }

    /* �������ϱ�MSCC���б�������Allowed List */
    for (i = 0; i < NAS_MML_MAX_PLMN_CSG_ID_NUM; i++)
    {
        if ((NAS_MML_CSG_ID_TYPE_IN_ALLOWED_CSG_LIST == aenCsgIdType[i])
          ||(NAS_MML_CSG_ID_TYPE_IN_ALLOWED_AND_OPERATOR_CSG_LIST == aenCsgIdType[i]))
        {
            /* �����ϱ����CNF�б��� */
            NAS_MMC_AddCsgIdToListCnf_PlmnList(i, aenCsgIdType[i], pstCsgIdInfoList);

            /* �´�ѭ�����ٴ�����λ�õ�CSG ID */
            aenCsgIdType[i] = NAS_MML_CSG_ID_TYPE_BUTT;
        }
    }

    /* �������ϱ�MSCC���б�������Operator List */
    for (i = 0; i < NAS_MML_MAX_PLMN_CSG_ID_NUM; i++)
    {
        if ((NAS_MML_CSG_ID_TYPE_IN_OPERATOR_CSG_LIST_NOT_FOBIDDEN == aenCsgIdType[i])
          ||(NAS_MML_CSG_ID_TYPE_IN_OPERATOR_CSG_LIST_FOBIDDEN == aenCsgIdType[i]))
        {
            /* �����ϱ����CNF�б��� */
            NAS_MMC_AddCsgIdToListCnf_PlmnList(i, aenCsgIdType[i], pstCsgIdInfoList);

            /* �´�ѭ�����ٴ�����λ�õ�CSG ID */
            aenCsgIdType[i] = NAS_MML_CSG_ID_TYPE_BUTT;
        }
    }

    /* �������ϱ�MSCC���б�������Available List */
    for (i = 0; i < NAS_MML_MAX_PLMN_CSG_ID_NUM; i++)
    {
        if (NAS_MML_CSG_ID_TYPE_NOT_IN_ALLOWED_AND_OPERATOR_CSG_LIST == aenCsgIdType[i])
        {
            /* �����ϱ����CNF�б��� */
            NAS_MMC_AddCsgIdToListCnf_PlmnList(i, aenCsgIdType[i], pstCsgIdInfoList);

            /* �´�ѭ�����ٴ�����λ�õ�CSG ID */
            aenCsgIdType[i] = NAS_MML_CSG_ID_TYPE_BUTT;
        }
    }

    return;
}


VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitWasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ�ȴ�WAS csg list��������ı�����ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_CSG_LIST_SEARCH_CNF);

    /* ��¼״̬���˳���� */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ����ֹͣ��������,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatCsgListSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvMsccCsgListAbortReq_PlmnList_WaitWasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ�ȴ�WAS csg list��������ı�����ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_CSG_LIST_SEARCH_CNF);

    /* ��¼״̬���˳���� */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ����֪ͨMSCC�ظ���� */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    /* ��WAS����ֹͣ��������,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatCsgListSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvRrMmCsgListSrchCnf_PlmnList_WaitWasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_CSG_LIST_SEARCH_CNF_STRU      *pstPlmnSearchcnf = VOS_NULL_PTR;

    pstPlmnSearchcnf = (RRMM_CSG_LIST_SEARCH_CNF_STRU*)pstMsg;

    /* ֹͣ�ȴ�WAS csg list�����ظ��ı�����ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_CSG_LIST_SEARCH_CNF);

    /* ����CSG LIST�Ľ�� */
    NAS_MMC_ProcRrmmCsgListSearchCnf_PlmnList(pstPlmnSearchcnf);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvRrMmRelInd_PlmnList_WaitWasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_REL_IND_STRU                  *pstRrmmRelIndMsg    = VOS_NULL_PTR;

    pstRrmmRelIndMsg = (RRMM_REL_IND_STRU *)pstMsg;

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmRelInd_PlmnList_WaitWasCsgListSearchCnf Enter!");

    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_CSG_LIST_SEARCH_CNF);

    if (RRC_REL_CAUSE_NO_RF == pstRrmmRelIndMsg->ulRelCause)
    {
        NAS_MMC_ProcNoRf_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

        return VOS_TRUE;
    }

    /* ����״̬���˳���� */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());

    /* ����5S�����Գ���CSG LIST������ʱ�� */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH, TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH_LEN);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvRrMmSysInfoInd_PlmnList_WaitWasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����פ����Ϣ����ת��ϵͳ��Ϣ */
    NAS_MMC_ProcWasSysInfo_PlmnList(pstMsg);

    /* ��Ǩ��״̬ */
    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvTiWaitWasCsgListCnfExpired_PlmnList_WaitWasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitWasCsgListCnfExpired_PlmnList_WaitWasCsgListSearchCnf: Timer Expired");
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_SetSearchedFlag_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);
#endif

    /* ��WAS����ֹͣ��������,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatCsgListSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvRrMmAreaLostInd_PlmnList_WaitAsCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_SaveLastCampedPlmnWithRat(NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMcc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMnc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.enCampPlmnNetRat);

    /* ���פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* ��ǰ�źŸ��� */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    /* ��MM/GMM/TAF�������������� */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();

    /* �ϱ���Ӧ��CS/PS����״̬MSCC_MMC_SERVICE_STATUS_NO_SERVICE */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);
    NAS_MMC_UpdateRegStateSpecPlmnSearch();

    /* ���·���״̬ */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );

    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvMmCsRegResultInd_PlmnList_WaitWasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMMMC_CS_REG_RESULT_IND_STRU       *pstCsRegRslt = VOS_NULL_PTR;

    pstCsRegRslt = (MMMMC_CS_REG_RESULT_IND_STRU*)pstMsg;

    /* �ȴ�RRC��·�ͷ�ʱ���������ѡ���л��Լ�CCO����������ᷢ���ı䣬
       ״̬���˳����յ������ע������Ϣ����Ҫ�жϵ�ǰ������
       �����ı䣬�����ı�������ǰע���� */
    if ( pstCsRegRslt->enNetType != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    /* ����CS��ע���� */
    NAS_MMC_ProcCsRegRslt_PlmnList(pstCsRegRslt);

    /* ��Ǩ��״̬ */
    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvGmmPsRegResultInd_PlmnList_WaitWasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    GMMMMC_PS_REG_RESULT_IND_STRU      *pstPsRegRslt = VOS_NULL_PTR;

    pstPsRegRslt = (GMMMMC_PS_REG_RESULT_IND_STRU*)pstMsg;

    /* �ȴ�RRC��·�ͷ�ʱ���������ѡ���л��Լ�CCO����������ᷢ���ı䣬
       ״̬���˳����յ������ע������Ϣ����Ҫ�жϵ�ǰ������
       �����ı䣬�����ı�������ǰע���� */
    if ( pstPsRegRslt->enNetType != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    /* ����PS��ע����*/
    NAS_MMC_ProcPsRegRslt_PlmnList(pstPsRegRslt);

    /* ��Ǩ��״̬ */
    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitGasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ�ȴ�GAS csg list��������ı�����ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_CSG_LIST_SEARCH_CNF);

    /* ��¼״̬���˳���� */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ��GAS����ֹͣ��������,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatCsgListSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvMsccCsgListAbortReq_PlmnList_WaitGasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ�ȴ�GAS csg list��������ı�����ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_CSG_LIST_SEARCH_CNF);

    /* ��¼״̬���˳���� */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ����֪ͨMSCC�ظ���� */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    /* ��GAS����ֹͣ��������,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatCsgListSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvRrMmCsgListSrchCnf_PlmnList_WaitGasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_CSG_LIST_SEARCH_CNF_STRU      *pstPlmnSrchcnf = VOS_NULL_PTR;

    pstPlmnSrchcnf = (RRMM_CSG_LIST_SEARCH_CNF_STRU*)pstMsg;

    /* ֹͣ�ȴ�GAS csg list�����ظ��ı�����ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_CSG_LIST_SEARCH_CNF);

    /* ����CSG LIST�Ľ�� */
    NAS_MMC_ProcRrmmCsgListSearchCnf_PlmnList(pstPlmnSrchcnf);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvGrrMmSysInfoInd_PlmnList_WaitGasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����յ�GAS��ϵͳ��Ϣ����ĿǰUtran��Enable��������Disable Utran */
    NAS_MMC_RcvGasSysInfoSetUtranCapabilityStatus();

    /* ����פ����Ϣ����ת��ϵͳ��Ϣ */
    NAS_MMC_ProcGasSysInfo_PlmnList(pstMsg);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvTiWaitGasCsgListCnfExpired_PlmnList_WaitGasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitGasCsgListCnfExpired_PlmnList_WaitGasCsgListSearchCnf: Timer Expired");
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_SetSearchedFlag_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);
#endif

    /* ��GAS����ֹͣ��������,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatCsgListSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvMmCsRegResultInd_PlmnList_WaitGasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMMMC_CS_REG_RESULT_IND_STRU       *pstCsRegRslt = VOS_NULL_PTR;

    pstCsRegRslt = (MMMMC_CS_REG_RESULT_IND_STRU*)pstMsg;

    /* �ȴ�RRC��·�ͷ�ʱ���������ѡ���л��Լ�CCO����������ᷢ���ı䣬
       ״̬���˳����յ������ע������Ϣ����Ҫ�жϵ�ǰ������
       �����ı䣬�����ı�������ǰע���� */
    if ( pstCsRegRslt->enNetType != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    /* ����CS��ע���� */
    NAS_MMC_ProcCsRegRslt_PlmnList(pstCsRegRslt);

    /* ��Ǩ��״̬ */
    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvGmmPsRegResultInd_PlmnList_WaitGasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    GMMMMC_PS_REG_RESULT_IND_STRU      *pstPsRegRslt = VOS_NULL_PTR;

    pstPsRegRslt = (GMMMMC_PS_REG_RESULT_IND_STRU*)pstMsg;

    /* �ȴ�RRC��·�ͷ�ʱ���������ѡ���л��Լ�CCO����������ᷢ���ı䣬
       ״̬���˳����յ������ע������Ϣ����Ҫ�жϵ�ǰ������
       �����ı䣬�����ı�������ǰע���� */
    if ( pstPsRegRslt->enNetType != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    /* ����PS��ע����*/
    NAS_MMC_ProcPsRegRslt_PlmnList(pstPsRegRslt);

    /* ��Ǩ��״̬ */
    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitCsgListWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼��Ҫ��ֹ��ǰ״̬����־ */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvMsccCsgListAbortReq_PlmnList_WaitCsgListWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼��Ҫ��ֹ��ǰ״̬����־ */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ����֪ͨMSCC�ظ���� */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvRrMmSuspendCnf_PlmnList_WaitCsgListWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_CNF_ST                *pstRrmmSuspendCnf = VOS_NULL_PTR;

    pstRrmmSuspendCnf  = (RRMM_SUSPEND_CNF_ST*)pstMsg;

    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF);

    /* ��������ظ���� */
    NAS_MMC_ProcRrmmCsgListSuspendCnf_PlmnList(pstRrmmSuspendCnf);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvTiWaitWasSuspendCnfExpired_PlmnList_WaitCsgListWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat      = NAS_MML_GetCurrNetRatType();

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitWasSuspendCnfExpired_PlmnList_WaitCsgListWasSuspendCnf: Timer Expired");

    /* ���ɻָ����ϣ���λ */

    if ( (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
      && (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat) )
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_WAS_SUSPEND_CNF_EXPIRED);
    }
    else
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_TD_SUSPEND_CNF_EXPIRED);
    }

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitCsgListGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼��Ҫ��ֹ��ǰ״̬����־ */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvMsccCsgListAbortReq_PlmnList_WaitCsgListGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼��Ҫ��ֹ��ǰ״̬����־ */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ����֪ͨMSCC�ظ���� */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvRrMmSuspendCnf_PlmnList_WaitCsgListGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_CNF_ST                *pstRrmmSuspendCnf = VOS_NULL_PTR;

    pstRrmmSuspendCnf  = (RRMM_SUSPEND_CNF_ST*)pstMsg;

    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF);

    /* ��������ظ���� */
    NAS_MMC_ProcRrmmCsgListSuspendCnf_PlmnList(pstRrmmSuspendCnf);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvTiWaitGasSuspendCnfExpired_PlmnList_WaitCsgListGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitGasSuspendCnfExpired_PlmnList_WaitCsgListGasSuspendCnf: Timer Expired");

    /* ���ɻָ����ϣ���λ */
    NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_GAS_SUSPEND_CNF_EXPIRED);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitGasCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼��Ҫ��ֹ��ǰ״̬����־ */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvRrMmPlmnSrchStopCnf_PlmnList_WaitGasCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF);

    /* ��������ֹͣ�ظ���� */
    NAS_MMC_ProcRrmmCsgListSearchStopCnf_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvGrrMmSysInfoInd_PlmnList_WaitGasCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����յ�GAS��ϵͳ��Ϣ����ĿǰUtran��Enable��������Disable Utran */
    NAS_MMC_RcvGasSysInfoSetUtranCapabilityStatus();

    /* ����פ����Ϣ����ת��ϵͳ��Ϣ */
    NAS_MMC_ProcGasSysInfo_PlmnList(pstMsg);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvMsccCsgListAbortFsmMsg_PlmnList_WaitGasCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼��Ҫ��ֹ��ǰ״̬����־ */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ����֪ͨMSCC�ظ���� */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvRrMmCsgListSrchCnf_PlmnList_WaitGasCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_CSG_SEARCHED_PLMN_LIST_INFO_STRU               *pstCsgPlmnIdList  = VOS_NULL_PTR;
    RRMM_CSG_LIST_SEARCH_CNF_STRU                          *pstPlmnSrchCnf = VOS_NULL_PTR;

    pstPlmnSrchCnf = (RRMM_CSG_LIST_SEARCH_CNF_STRU*)pstMsg;

    /* LIST�����ظ���ֹͣ�����Գ�,NO RFʱֱ���˳�LIST�������� */
    if (RRC_NAS_CSG_SEARCH_RLT_NO_RF == pstPlmnSrchCnf->enSearchRlt)
    {
        /* ֹͣ������ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF);

        NAS_MMC_ProcNoRf_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);

        return VOS_TRUE;
    }

     /*ֻ���������ɹ�ʱ�Ž��д��� */
    if (RRC_NAS_CSG_SEARCH_RLT_SUCC != pstPlmnSrchCnf->enSearchRlt)
    {
        return VOS_TRUE;
    }

    /* ����GU AS�ϱ����б��ѽ����״̬���������� */
    NAS_MMC_SaveRrmmCsgListSearchResult_PlmnList(pstPlmnSrchCnf);

    /* ����L�ѱ������� */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_InitSpecRatSearchedPlmnListInfo_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

    NAS_MMC_SetSpecRatSearchedTypeByPlmnSearchCnfSucc_PlmnList(NAS_MML_NET_RAT_TYPE_LTE, RRC_PLMN_SEARCH_RLT_USER_LIST);
    NAS_MMC_SetSearchedFlag_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);
#endif

    /* ����CSG���������ս��ˢ��״̬���������еĸߵ����������б� */
    pstCsgPlmnIdList = NAS_MMC_GetCsgSearchedPlmnListInfo_PlmnList();
    NAS_MMC_UpdateSearchedPlmnListInfoFromCsgSearchResult_PlmnList(pstCsgPlmnIdList);

    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF);

    /* ��������ֹͣ�ظ���� */
    NAS_MMC_ProcRrmmCsgListSearchStopCnf_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvTiWaitGasStopCnfExpired_PlmnList_WaitGasCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitGasStopCnfExpired_PlmnList_WaitGasCsgListSearchStopCnf: Timer Expired");

    /* ��������ֹͣ�ظ���� */
    NAS_MMC_ProcRrmmCsgListSearchStopCnf_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitWasCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼��Ҫ��ֹ��ǰ״̬����־ */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvRrMmPlmnSrchStopCnf_PlmnList_WaitWasCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF);

    /* ��������ֹͣ�ظ���� */
    NAS_MMC_ProcRrmmCsgListSearchStopCnf_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

    /* ��Ǩ��״̬ */
    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvRrMmSysInfoInd_PlmnList_WaitWasCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����פ����Ϣ����ת��ϵͳ��Ϣ */
    NAS_MMC_ProcWasSysInfo_PlmnList(pstMsg);
    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvCsgListAbortFsmMsg_PlmnList_WaitWasCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼��Ҫ��ֹ��ǰ״̬����־ */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ����֪ͨMSCC�ظ���� */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvRrMmCsgListSrchCnf_PlmnList_WaitWasCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_CSG_SEARCHED_PLMN_LIST_INFO_STRU               *pstCsgPlmnIdList  = VOS_NULL_PTR;
    RRMM_CSG_LIST_SEARCH_CNF_STRU                          *pstPlmnSrchCnf = VOS_NULL_PTR;

    pstPlmnSrchCnf = (RRMM_CSG_LIST_SEARCH_CNF_STRU*)pstMsg;

    /* LIST�����ظ���ֹͣ�����Գ�,NO RFʱֱ���˳�LIST�������� */
    if (RRC_NAS_CSG_SEARCH_RLT_NO_RF == pstPlmnSrchCnf->enSearchRlt)
    {
        /* ֹͣ������ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF);

        NAS_MMC_ProcNoRf_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

        return VOS_TRUE;
    }

     /*ֻ���������ɹ�ʱ�Ž��д��� */
    if (RRC_NAS_CSG_SEARCH_RLT_SUCC != pstPlmnSrchCnf->enSearchRlt)
    {
        return VOS_TRUE;
    }

    /* ����GU AS�ϱ����б��ѽ����״̬���������� */
    NAS_MMC_SaveRrmmCsgListSearchResult_PlmnList(pstPlmnSrchCnf);

    /* ����L�ѱ������� */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_InitSpecRatSearchedPlmnListInfo_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

    NAS_MMC_SetSpecRatSearchedTypeByPlmnSearchCnfSucc_PlmnList(NAS_MML_NET_RAT_TYPE_LTE, RRC_PLMN_SEARCH_RLT_USER_LIST);

    NAS_MMC_SetSearchedFlag_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);
#endif

    /* ����CSG���������ս��ˢ��״̬���������еĸߵ����������б� */
    pstCsgPlmnIdList = NAS_MMC_GetCsgSearchedPlmnListInfo_PlmnList();
    NAS_MMC_UpdateSearchedPlmnListInfoFromCsgSearchResult_PlmnList(pstCsgPlmnIdList);

    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF);

    /* ��������ֹͣ�ظ���� */
    NAS_MMC_ProcRrmmCsgListSearchStopCnf_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvRrMmRelInd_PlmnList_WaitWasCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmRelInd_PlmnList_WaitWasCsgListSearchStopCnf: ENTERED");

    /* �����ж�ԭ��ֵ */

    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF);

    /* ״̬���˳����Ϊ�� */
    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnList())
    {
        /* ��ǰ��csg�б����� */
        if ( VOS_TRUE == NAS_MMC_GetNotifyMsccFlag_PlmnList())
        {
            /* ��MSCC�ظ�csg LIST ABORT CNF */
            NAS_MMC_SndMsccCsgListAbortCnf_PlmnList();
        }
        else
        {
            /* ��MSCC�ظ�csg LIST������� */
            NAS_MMC_SndMsccCsgListSearchCnf_PlmnList();
        }

        /* ����״̬��ABORT�˳���� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ����״̬���˳���� */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());

    /* ����5S�����Գ���csg LIST������ʱ�� */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH, TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH_LEN);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvTiWaitWasStopCnfExpired_PlmnList_WaitWasCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitWasStopCnfExpired_PlmnList_WaitWasCsgListSearchStopCnf: Timer Expired");

    /* ��������ֹͣ�ظ���� */
    NAS_MMC_ProcRrmmCsgListSearchStopCnf_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_IsCsgList_PlmnList(VOS_VOID)
{
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg    = VOS_NULL_PTR;

    /* ����FSM ID��ȡ��FSM �����Ϣ */
    pstEntryMsg     = NAS_MMC_GetCurrFsmMsgAddr();

    if ( (ID_MSCC_MMC_CSG_LIST_SEARCH_REQ == NAS_ExtractMsgNameFromEvtType(pstEntryMsg->ulEventType))
      || (TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH == NAS_ExtractMsgNameFromEvtType(pstEntryMsg->ulEventType)))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_VOID NAS_MMC_SndMsccCsgListSearchCnf_PlmnList(VOS_VOID)
{
    MMC_MSCC_CSG_LIST_SEARCH_CNF_STRU  *pstCsgListSrchCnf = VOS_NULL_PTR;

    /* �����ϱ�������ڴ�ռ� */
    pstCsgListSrchCnf = (MMC_MSCC_CSG_LIST_SEARCH_CNF_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                    sizeof(MMC_MSCC_CSG_LIST_SEARCH_CNF_STRU));

    if (VOS_NULL_PTR == pstCsgListSrchCnf)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccCsgListSearchCnf_PlmnList:ERROR,Memory Alloc Error");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstCsgListSrchCnf) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_CSG_LIST_SEARCH_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstCsgListSrchCnf->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstCsgListSrchCnf->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstCsgListSrchCnf->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstCsgListSrchCnf->MsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstCsgListSrchCnf->MsgHeader.ulLength          = sizeof(MMC_MSCC_CSG_LIST_SEARCH_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstCsgListSrchCnf->MsgHeader.ulMsgName         = ID_MMC_MSCC_CSG_LIST_SEARCH_CNF;

    /* ���������ϱ�������CSG ID�������ϱ���CSG ID�б� */
    NAS_MMC_BuildReportCsgIdList_PlmnList(&(pstCsgListSrchCnf->stCsgIdInfo));

    /* ��MSCC����LIST CNF��Ϣ */
    NAS_MMC_SndMsccUserCsgListSearchCnf(pstCsgListSrchCnf);

    PS_MEM_FREE(WUEPS_PID_MMC, pstCsgListSrchCnf);

    return;
}


VOS_VOID NAS_MMC_SndMsccCsgListAbortCnf_PlmnList(VOS_VOID)
{
    MMC_MSCC_CSG_LIST_ABORT_CNF_STRU                      *pstCsgListAbortCnf = VOS_NULL_PTR;

    /* �����ϱ�������ڴ�ռ� */
    pstCsgListAbortCnf = (MMC_MSCC_CSG_LIST_ABORT_CNF_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                    sizeof(MMC_MSCC_CSG_LIST_ABORT_CNF_STRU));

    if (VOS_NULL_PTR == pstCsgListAbortCnf)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccCsgListAbortCnf_PlmnList:ERROR,Memory Alloc Error");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstCsgListAbortCnf) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_CSG_LIST_ABORT_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstCsgListAbortCnf->MsgHeader.ulLength          = sizeof(MMC_MSCC_CSG_LIST_ABORT_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstCsgListAbortCnf->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstCsgListAbortCnf->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstCsgListAbortCnf->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstCsgListAbortCnf->MsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstCsgListAbortCnf->MsgHeader.ulMsgName         = ID_MMC_MSCC_CSG_LIST_ABORT_CNF;

    /* ���������ϱ�������CSG ID�������ϱ���CSG ID�б� */
    NAS_MMC_BuildReportCsgIdList_PlmnList(&(pstCsgListAbortCnf->stCsgIdInfo));

    /* ��MSCC����LIST ABORT CNF��Ϣ */
    NAS_MMC_SndMsccUserCsgListAbortCnf(pstCsgListAbortCnf);

    PS_MEM_FREE(WUEPS_PID_MMC, pstCsgListAbortCnf);

    return;
}


VOS_VOID NAS_MMC_SndSpecRatCsgListSearchReq_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    switch (enRat)
    {
#if (FEATURE_LTE == FEATURE_ON)
        case NAS_MML_NET_RAT_TYPE_LTE:

            NAS_MMC_SndLmmCsgListSearchReq();

            /* Ǩ��״̬���ȴ�LMM��LIST�����ظ� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_CSG_LIST_STA_WAIT_LMM_CSG_LIST_SEARCH_CNF);

            /* ����������ʱ�� */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_CSG_LIST_SEARCH_CNF, TI_NAS_MMC_WAIT_LMM_CSG_LIST_SEARCH_CNF_LEN);
            break;
#endif

        case NAS_MML_NET_RAT_TYPE_WCDMA:
            NAS_MMC_SndAsCsgListSearchReq(WUEPS_PID_WRR);

            /* Ǩ��״̬���ȴ�WRR��CSG LIST�����ظ� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_CSG_LIST_STA_WAIT_WAS_CSG_LIST_SEARCH_CNF);

            /* ����������ʱ�� */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_CSG_LIST_SEARCH_CNF, TI_NAS_MMC_WAIT_WAS_CSG_LIST_SEARCH_CNF_LEN);

            break;

        case NAS_MML_NET_RAT_TYPE_GSM:
            NAS_MMC_SndAsCsgListSearchReq(UEPS_PID_GAS);

            /* Ǩ��״̬���ȴ�GAS��CSG LIST�����ظ� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_CSG_LIST_STA_WAIT_GAS_CSG_LIST_SEARCH_CNF);

            /* ����������ʱ�� */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_CSG_LIST_SEARCH_CNF, TI_NAS_MMC_WAIT_GAS_CSG_LIST_SEARCH_CNF_LEN);
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndSpecRatCsgListSearchReq_PlmnList Unexpected Rat type!");

            break;
    }

    return;
}

VOS_VOID NAS_MMC_ProcUserCsgListReq_PlmnList(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    enRatType     = NAS_MML_GetCurrNetRatType();

#if (FEATURE_LTE == FEATURE_ON)
    /* ����״̬�±���ϣ���ǰ���뼼��ΪBUTT */
    if( NAS_MML_NET_RAT_TYPE_BUTT == NAS_MML_GetCurrNetRatType())
    {
       enRatType = NAS_MML_NET_RAT_TYPE_LTE;
       NAS_MML_SetCurrNetRatType(enRatType);
    }
#endif

    /* ���³�ʼ��NAS_MMC_GetSearchCtrlInfo_PlmnList��ֻ��LTE���뼼�� */
    NAS_MMC_InitCsgListSearchRatInfo_PlmnList();

    /* �ж��Ƿ���Ҫ�ȴ������ͷ� */
    if ( VOS_FALSE == NAS_MMC_IsNeedWaitRrcRel_PlmnList() )
    {
        /* ���ݲ�ͬ����ģʽ,����LIST��������Ǩ���ȴ��������״̬������������ʱ��*/
        if ((NAS_MMC_AS_CELL_CAMP_ON == NAS_MMC_GetAsCellCampOn())
         || (NAS_MML_NET_RAT_TYPE_LTE == enRatType))
        {
            NAS_MMC_SndSpecRatCsgListSearchReq_PlmnList(enRatType);
            return;
        }

        /* gu�·�פ��̬��Ҫ����gu��lte������ */
        NAS_MMC_SndSpecRatCsgListSuspendReq_PlmnList(enRatType);

        return;
    }

    /* ��Ҫ�ȴ������ͷ� */
    switch (NAS_MML_GetCurrNetRatType())
    {
#if (FEATURE_LTE == FEATURE_ON)
        case NAS_MML_NET_RAT_TYPE_LTE:

        /* L����EPS�������ӱ����ȴ�LMM�ͷ���·,
           ������GU��ʵ��һ�� */

        /* Ǩ��״̬���ȴ�LMM��EPS��·�ͷ� */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_EPS_CONN_REL_IND);

        /* ����������ʱ�� */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);

        break;
#endif

    case NAS_MML_NET_RAT_TYPE_WCDMA:
    case NAS_MML_NET_RAT_TYPE_GSM:

        /* Ǩ��״̬���ȴ�GU��RRC��·�ͷ� */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_RRC_CONN_REL_IND);

        /* ����������ʱ�� */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL, TI_NAS_MMC_WAIT_RRC_CONN_REL_LEN);

        break;

    default:
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcUserPlmnListReq_PlmnList Unexpected Rat type!");

        break;
    }

    return;
}


VOS_VOID NAS_MMC_SndSpecRatCsgListSuspendReq_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    switch (enRat)
    {
#if (FEATURE_LTE == FEATURE_ON)
        case NAS_MML_NET_RAT_TYPE_LTE:

            /* Ŀǰֻ֧��LTE CSG,�����ڹ���lte�ĳ��� */
            break;
#endif

        case NAS_MML_NET_RAT_TYPE_WCDMA:

            /* ����פ��״̬ */
            NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
            NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

            NAS_MMC_SetAsAnyCampOn(VOS_FALSE);

            /* ��WAS���͹������� */
            NAS_MMC_SndAsSuspendReq(WUEPS_PID_WRR);

            /* Ǩ��״̬���ȴ�WAS�Ĺ���ظ� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_CSG_LIST_STA_WAIT_WAS_SUSPEND_CNF);

            /* ����������ʱ�� */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF, TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF_LEN);

            break;

        case NAS_MML_NET_RAT_TYPE_GSM:

            /* ����פ��״̬ */
            NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
            NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

            NAS_MMC_SetAsAnyCampOn(VOS_FALSE);

            /* ��GAS���͹������� */
            NAS_MMC_SndAsSuspendReq(UEPS_PID_GAS);

            /* Ǩ��״̬���ȴ�GAS�Ĺ���ظ� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_CSG_LIST_STA_WAIT_GAS_SUSPEND_CNF);

            /* ����������ʱ�� */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF, TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF_LEN);

            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndSpecRatCsgListSuspendReq_PlmnList Unexpected Rat type!");

            break;
    }
}


VOS_VOID NAS_MMC_SndSpecRatCsgListSearchStopReq_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    switch (enRat)
    {
#if (FEATURE_LTE == FEATURE_ON)
        case NAS_MML_NET_RAT_TYPE_LTE:

            /* ��LMM����ֹͣ�������� */
            NAS_MMC_SndLmmPlmnSrchStopReq();

            /* Ǩ��״̬���ȴ�LMM��ֹͣ�����ظ� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_CSG_LIST_STA_WAIT_LMM_CSG_LIST_SEARCH_STOP_CNF);

            /* ����������ʱ�� */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF_LEN);

            break;
#endif

        case NAS_MML_NET_RAT_TYPE_WCDMA:

            /* ��WAS����ֹͣ�������� */
            NAS_MMC_SndAsPlmnSrchStopReq(WUEPS_PID_WRR);

            /* Ǩ��״̬���ȴ�WAS��ֹͣ�����ظ� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_CSG_LIST_STA_WAIT_WAS_CSG_LIST_SEARCH_STOP_CNF);

            /* ����������ʱ�� */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF_LEN);

            break;

        case NAS_MML_NET_RAT_TYPE_GSM:

            /* ��GAS����ֹͣ�������� */
            NAS_MMC_SndAsPlmnSrchStopReq(UEPS_PID_GAS);

            /* Ǩ��״̬���ȴ�GAS��ֹͣ�����ظ� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_CSG_LIST_STA_WAIT_GAS_CSG_LIST_SEARCH_STOP_CNF);

            /* ����������ʱ�� */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF_LEN);

            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndSpecRatCsgListSearchStopReq_PlmnList Unexpected Rat type!");

            break;
    }
}


VOS_VOID NAS_MMC_ProcRrmmCsgListSearchSucc_PlmnList(
    RRMM_CSG_LIST_SEARCH_CNF_STRU      *pstPlmnSrchCnf
)
{
    NAS_MMC_CSG_SEARCHED_PLMN_LIST_INFO_STRU               *pstCsgPlmnIdList  = VOS_NULL_PTR;

    /* ����GU AS�ϱ����б��ѽ����״̬���������� */
    NAS_MMC_SaveRrmmCsgListSearchResult_PlmnList(pstPlmnSrchCnf);

    /* ����L�ѱ������� */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_InitSpecRatSearchedPlmnListInfo_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

    NAS_MMC_SetSpecRatSearchedTypeByPlmnSearchCnfSucc_PlmnList(NAS_MML_NET_RAT_TYPE_LTE, RRC_PLMN_SEARCH_RLT_USER_LIST);

    NAS_MMC_SetSearchedFlag_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);
#endif

    /* ����CSG���������ս��ˢ��״̬���������еĸߵ����������б� */
    pstCsgPlmnIdList = NAS_MMC_GetCsgSearchedPlmnListInfo_PlmnList();
    NAS_MMC_UpdateSearchedPlmnListInfoFromCsgSearchResult_PlmnList(pstCsgPlmnIdList);

    NAS_MMC_SndMsccCsgListSearchCnf_PlmnList();

    /* CSG LIST����������,RRC���ܳ�������,��ʱ��Ҫ��������״̬,�����˳�LIST�������ָ������ */
    if (NAS_MMC_AS_CELL_NOT_CAMP_ON == NAS_MMC_GetAsCellCampOn())
    {
        NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);
    }


    /* ����״̬���˳��Ľ�� */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_SUCC,
                            (VOS_UINT8)NAS_MMC_IsNeedPlmnSearch_PlmnList(),
                             NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                             NAS_MMC_GetRegRsltInfo_PlmnList());

    /* �˳�״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return;
}


VOS_VOID NAS_MMC_ProcRrmmCsgListSuspendCnf_PlmnList(
    RRMM_SUSPEND_CNF_ST                *pstRrmmSuspendCnf
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;
    VOS_UINT32                          ulNeedPlmnSearch;

    enCurRat      = NAS_MML_GetCurrNetRatType();

    if ( MMC_AS_SUSPEND_FAILURE  == pstRrmmSuspendCnf->ucResult )
    {
        /* ���帴λ */

        if ( (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
          && (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat) )
        {
            NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_WAS_SUSPEND_FAILURE);
        }
        else if ( NAS_MML_NET_RAT_TYPE_GSM == enCurRat )
        {
            NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_GAS_SUSPEND_FAILURE);
        }
        else if ( NAS_MML_NET_RAT_TYPE_LTE == enCurRat)
        {
            NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_LMM_SUSPEND_FAILURE);
        }
        else
        {
            NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_TD_SUSPEND_FAILURE);
        }

        return;
    }

    /* �ж�״̬���˳�����Ƿ�Ϊ�棬���Ϊ��*/
    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnList())
    {
        /* ���뼼������ΪBUTT����������ֱ��������ģ������������ */
        NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

        ulNeedPlmnSearch = VOS_FALSE;

        if ( VOS_TRUE == NAS_MMC_GetNotifyMsccFlag_PlmnList())
        {
            /* ��MSCC�ظ�ABORT_CNF */
            NAS_MMC_SndMsccCsgListAbortCnf_PlmnList();

            ulNeedPlmnSearch = VOS_TRUE;
        }
        else
        {
            /* ��MSCC�ظ�csg LIST������� */
            NAS_MMC_SndMsccCsgListSearchCnf_PlmnList();
        }

        /* ����״̬��ABORT���˳���� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                                (VOS_UINT8)ulNeedPlmnSearch,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* ��ȡ������һ�����뼼�� */
    if ( VOS_FALSE == NAS_MMC_GetNextSearchingRat_PlmnList(&enRat))
    {
        /* �쳣��ӡ */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcRrmmCsgListSuspendCnf_PlmnList: Get next search rat fail.");

        /* ���뼼������ΪBUTT����������ֱ��������ģ������������ */
        NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

        /* ��ǰΪ�û�LIST���� */
        if ( VOS_TRUE == NAS_MMC_IsCsgList_PlmnList())
        {
            /* ��MSCC�ظ�ID_MMC_MSCC_CSG_LIST_SEARCH_CNF */
            NAS_MMC_SndMsccCsgListSearchCnf_PlmnList();
        }

        /* ����״̬���˳���� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                (VOS_UINT8)NAS_MMC_IsNeedPlmnSearch_PlmnList(),
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* ���ݻ�ȡ�Ľ��뼼�����õ�ǰ���뼼�� */
    NAS_MML_SetCurrNetRatType(enRat);

    /* ���¸�����ģʽ����LIST��������,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(enRat);

}


VOS_VOID NAS_MMC_ProcRrmmCsgListSearchCnf_PlmnList(
    RRMM_CSG_LIST_SEARCH_CNF_STRU       *pstPlmnSrchCnf
)
{
    /* �ж�CSG LIST������� */
    switch (pstPlmnSrchCnf->enSearchRlt)
    {
        case RRC_NAS_CSG_SEARCH_RLT_REJ:

            /* ����5S�����Գ��Զ�ʱ�� */
            /* CSҵ�����绰���������Ľ����list rej��Ҫ��ֹlist�ѣ�
                ��Ӧҵ�����AT�ڱ�list����ռ�ã��û��޷���������绰���ն��� */
            if (VOS_TRUE == NAS_MML_GetCsServiceExistFlg())
            {
                /* ����LIST REJ��MSCC */
                NAS_MMC_SndMsccCsgListSearchRej();
            }
            else
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH, TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH_LEN);
            }

            /* ����״̬��ʧ�ܵ��˳���� */
            NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                    VOS_FALSE,
                                    NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                    NAS_MMC_GetRegRsltInfo_PlmnList());

            /* �˳�״̬�� */
            NAS_MMC_FSM_QuitFsmL2();

            break;

       case RRC_NAS_CSG_SEARCH_RLT_SUCC:

            /* ����CSG LIST�����ɹ��Ľ�� */
            NAS_MMC_ProcRrmmCsgListSearchSucc_PlmnList(pstPlmnSrchCnf);

            break;

       /* ���������̬�»ظ��ý����mmc��������5s�����Գ���csg list�Ѷ�ʱ����ֱ���ϱ�ʧ�� */
       case RRC_NAS_CSG_SEARCH_RLT_FAIL:

            /* ����LIST REJ��MSCC */
            NAS_MMC_SndMsccCsgListSearchRej();

            /* ����״̬��ʧ�ܵ��˳���� */
            NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                    VOS_FALSE,
                                    NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                    NAS_MMC_GetRegRsltInfo_PlmnList());

            /* �˳�״̬�� */
            NAS_MMC_FSM_QuitFsmL2();
            break;

       case RRC_NAS_CSG_SEARCH_RLT_NO_RF:
            NAS_MMC_ProcNoRf_PlmnList(NAS_MML_GetCurrNetRatType());
            break;

       default:

            /*�쳣��ӡ*/
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcRrmmCsgListSearchCnf_PlmnList Unexpected List Result!");

            break;
    }

    return;
}


VOS_VOID NAS_MMC_ProcRrmmCsgListSearchStopCnf_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNextRatType;
    VOS_UINT32                          ulNeedPlmnSearch;

    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnList())
    {
        ulNeedPlmnSearch = VOS_FALSE;

        if ( VOS_TRUE == NAS_MMC_GetNotifyMsccFlag_PlmnList())
        {
            /* ��MSCC�ظ�ABORT_CNF */
            NAS_MMC_SndMsccCsgListAbortCnf_PlmnList();

            ulNeedPlmnSearch = NAS_MMC_IsNeedPlmnSearch_PlmnList();
        }
        else
        {
            /* ��MSCC�ظ�csg LIST������� */
            NAS_MMC_SndMsccCsgListSearchCnf_PlmnList();
        }

        /* ����״̬��ABORT�˳���� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                                (VOS_UINT8)ulNeedPlmnSearch,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* ��ȡ������һ��δ�����Ľ���ģʽ */
    if ( VOS_FALSE == NAS_MMC_GetNextSearchingRat_PlmnList(&enNextRatType))
    {
        /* �����������������������ϱ���MSCC */
        NAS_MMC_SndMsccCsgListSearchCnf_PlmnList();

        /* ����״̬��ʧ���˳��Ľ�� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                (VOS_UINT8)NAS_MMC_IsNeedPlmnSearch_PlmnList(),
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* ��ǰ���뼼�����͹�������,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatCsgListSuspendReq_PlmnList(enRatType);

    /* ��GMM��������ָʾ */
    NAS_MMC_SndGmmPlmnSchInit();

    /* ��MM��������ָʾ */
    NAS_MMC_SndMmPlmnSchInit();

    return;
}


VOS_VOID NAS_MMC_SaveRrmmCsgListSearchResult_PlmnList(
    RRMM_CSG_LIST_SEARCH_CNF_STRU       *pstPlmnSrchCnf
)
{
    NAS_MMC_CSG_SEARCHED_PLMN_LIST_INFO_STRU               *pstCsgPlmnIdList = VOS_NULL_PTR;

    pstCsgPlmnIdList = NAS_MMC_GetCsgSearchedPlmnListInfo_PlmnList();

    /* �������ͱ������� */
    pstCsgPlmnIdList->ulTotalPlmnNum = NAS_MML_MIN(RRC_NAS_MAX_PLMN_CSG_ID_NUM,
                                        pstPlmnSrchCnf->stCsgListSearchedResult.ulTotalPlmnNum);

    pstCsgPlmnIdList->ulHighPlmnNum = NAS_MML_MIN(pstCsgPlmnIdList->ulTotalPlmnNum,
                                        pstPlmnSrchCnf->stCsgListSearchedResult.ulHighPlmnNum);

    /* ���������б� */
    PS_MEM_CPY(pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList,
                    pstPlmnSrchCnf->stCsgListSearchedResult.astCsgListSearchedPlmnInfoList,
                    (pstCsgPlmnIdList->ulTotalPlmnNum) * sizeof(RRMM_CSG_LIST_SEARCHED_PLMN_INFO_STRU));

    return;
}


NAS_MML_CSG_ID_TYPE_ENUM_UINT8 NAS_MMC_GetCsgIdType_PlmnList(
    NAS_MML_PLMN_WITH_CSG_ID_STRU      *pstPlmnCsgId
)
{
    /* ����Ǻ�С�����򲻴���CSG ID���ͣ�����BUTT */
    if (NAS_MML_INVALID_CSG_ID_VALUE == pstPlmnCsgId->ulCsgId)
    {
        return NAS_MML_CSG_ID_TYPE_BUTT;
    }

    /* �����Allowed List�� */
    if (VOS_TRUE == NAS_MML_IsCsgIdInAllowedCsgIdList(pstPlmnCsgId))
    {
        /* �����Operator List�� */
        if (VOS_TRUE == NAS_MML_IsCsgIdInOperatorCsgIdList(pstPlmnCsgId))
        {
            return NAS_MML_CSG_ID_TYPE_IN_ALLOWED_AND_OPERATOR_CSG_LIST;

        }

        return NAS_MML_CSG_ID_TYPE_IN_ALLOWED_CSG_LIST;
    }

    /* ����Allowed List�У�������Operator List�� */
    if (VOS_TRUE == NAS_MML_IsCsgIdInOperatorCsgIdList(pstPlmnCsgId))
    {
        /* �����ǰ���ڽ�ֹ״̬ */
        if (VOS_TRUE == NAS_MML_IsCsgIdInForbiddenCsgIdList(pstPlmnCsgId))
        {
            return NAS_MML_CSG_ID_TYPE_IN_OPERATOR_CSG_LIST_FOBIDDEN;
        }

        return NAS_MML_CSG_ID_TYPE_IN_OPERATOR_CSG_LIST_NOT_FOBIDDEN;
    }

    /* �����κ�һ���б��� */
    return NAS_MML_CSG_ID_TYPE_NOT_IN_ALLOWED_AND_OPERATOR_CSG_LIST;

}


VOS_UINT32 NAS_MMC_IsSpecCsgIdDisplayIndicatorNeedReport_PlmnList(
    NAS_MML_PLMN_WITH_CSG_ID_STRU      *pstPlmnCsgId,
    NAS_MML_CSG_ID_TYPE_ENUM_UINT8      enCsgIdType
)
{
    NAS_MML_CSG_ID_DISPLAY_INDICATOR_TYPE_ENUM_UINT8        ucCsgDisplayIndicator;

    ucCsgDisplayIndicator = NAS_MML_CSG_ID_DISPLAY_IND_BUTT;

    /* ���SERVICE n92�����ã���Ĭ��Ϊ�����ϱ� */
    if (PS_USIM_SERVICE_AVAILIABLE != NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_CSG_CTRL))
    {
        return VOS_TRUE;
    }

    /* SERVICE n92���ã����ݶ�Ӧ��CSG ID���ͣ����в�ͬ�Ĵ��� */
    switch (enCsgIdType)
    {
        case    NAS_MML_CSG_ID_TYPE_IN_ALLOWED_AND_OPERATOR_CSG_LIST:
        case    NAS_MML_CSG_ID_TYPE_IN_OPERATOR_CSG_LIST_NOT_FOBIDDEN:
        case    NAS_MML_CSG_ID_TYPE_IN_OPERATOR_CSG_LIST_FOBIDDEN:

                /* �����Operator List�У����������ϱ� */
                return VOS_TRUE;

        case    NAS_MML_CSG_ID_TYPE_IN_ALLOWED_CSG_LIST:
        case    NAS_MML_CSG_ID_TYPE_NOT_IN_ALLOWED_AND_OPERATOR_CSG_LIST:

                ucCsgDisplayIndicator = NAS_MMC_GetCsgDisplayIndicatorNotInOperatorCsgList_PlmnList(pstPlmnCsgId);

                if ((NAS_MML_CSG_ID_DISPLAY_INDICATOR_TYPE_DISPLAY_ALL_AVAILABLE_CSG_ID == ucCsgDisplayIndicator)
                  ||(NAS_MML_CSG_ID_DISPLAY_INDICATOR_TYPE_NOT_EXIST == ucCsgDisplayIndicator))
                {
                    /* �����ϱ��򲻴��ڶ��ϱ������������Ĭ�ϲ��ϱ� */
                    return VOS_TRUE;
                }

                break;

        default:
                /* CSG ID�����쳣�ģ�˵���Ǻ�С�����߳����������쳣��Ĭ��Ϊ���ϱ� */
                break;

    }

    return VOS_FALSE;
}


VOS_UINT8 NAS_MMC_GetCsgDisplayIndicatorNotInOperatorCsgList_PlmnList(
    NAS_MML_PLMN_WITH_CSG_ID_STRU      *pstPlmnCsgId
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulIndex;
    VOS_UINT8                           ucCsgDisplayIndicator;
    NAS_MML_PLMN_ID_STRU                stPlmnId;
    NAS_MML_PLMN_ID_STRU                stOperatorPlmnId;
    VOS_UINT8                           ucEfadIndicator;
    NAS_MML_PLMN_WITH_CSG_ID_LIST_STRU *pstOperatorCsgIdList = VOS_NULL_PTR;

    /* �ֲ�������ʼ�� */
    ulIndex                = 0;
    ucCsgDisplayIndicator  = 0;
    stPlmnId.ulMcc         = pstPlmnCsgId->stPlmnId.ulMcc;
    stPlmnId.ulMnc         = pstPlmnCsgId->stPlmnId.ulMnc;
    stOperatorPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    stOperatorPlmnId.ulMnc = NAS_MML_INVALID_MNC;

    ucEfadIndicator        = NAS_MML_GetCsgDisplayCtrlFlag();

    pstOperatorCsgIdList   = NAS_MML_GetOperatorCsgList();

    /* ����������CSG ID�Ƿ��������Ǻ�С����ֱ���ж�Ϊ���ϱ���
    ����ֻ�ϱ�Operator List�еģ�������Ȼ�����ϱ����� */
    if (NAS_MML_INVALID_CSG_ID_VALUE == pstPlmnCsgId->ulCsgId)
    {
        return NAS_MML_CSG_ID_DISPLAY_INDICATOR_TYPE_DISPLAY_ONLY_OPERATOR_CSG_ID;
    }

    /* ����Operator list��CSG ID������ʾָʾ�Ĵ���ԭ��:
    ���жϴ�CSG ID��PLMN�Ƿ���Operator list������ڣ�����PLMN���Ƿ��ж�Ӧ����ʾָʾ��
    �оͰ���ָʾ�ķ��أ�û�оͰ�EFAD���ļ�ָʾ���з��أ��������Operator list��ֱ�Ӱ�
    EFAD���ļ�ָʾ���з��أ�EFAD���ļ���������ڣ����ⲿӦ�ý�ulEfadIndicatorĬ�ϳ�ʼ��Ϊ�ϱ� */

    /* ��Operator List�в��ҵ�ǰPLMN */
    for (i = 0; i < pstOperatorCsgIdList->ulPlmnWithCsgIdListNum; i++)
    {
        stOperatorPlmnId.ulMcc = pstOperatorCsgIdList->astPlmnWithCsgIdInfo[i].stPlmnWithCsgId.stPlmnId.ulMcc;
        stOperatorPlmnId.ulMnc = pstOperatorCsgIdList->astPlmnWithCsgIdInfo[i].stPlmnWithCsgId.stPlmnId.ulMnc;

        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&stPlmnId,&stOperatorPlmnId))
        {
            ulIndex = i;
            break;
        }
    }

    /* PLMN����Operator List�У�ֱ�Ӱ�EFAD���ļ�ָʾ��Display Indicatorָʾ���з��� */
    if (i >= pstOperatorCsgIdList->ulPlmnWithCsgIdListNum)
    {
        return ucEfadIndicator;
    }

    /* ���PLMN��Operator List�У����ҵ���Ӧ��PLMN��λ��ulIndex��ȡ����Ӧ��indicator */
    ucCsgDisplayIndicator = pstOperatorCsgIdList->astPlmnWithCsgIdInfo[ulIndex].enCsgDisplayIndicator;

    /* ����Display Indicator */
    if ((NAS_MML_CSG_ID_DISPLAY_INDICATOR_TYPE_DISPLAY_ALL_AVAILABLE_CSG_ID == ucCsgDisplayIndicator)
      ||(NAS_MML_CSG_ID_DISPLAY_INDICATOR_TYPE_DISPLAY_ONLY_OPERATOR_CSG_ID == ucCsgDisplayIndicator))
    {
        /* ����Display Indicatorָʾ���з��� */
        return ucCsgDisplayIndicator;
    }

    /* ��������ڣ���EFAD���ļ�ָʾ��Display Indicatorָʾ���з��� */
    return ucEfadIndicator;

}


VOS_VOID NAS_MMC_AddCsgIdToListCnf_PlmnList(
    VOS_UINT32                                              ulIndex,
    NAS_MML_CSG_ID_TYPE_ENUM_UINT8                          enCsgIdType,
    NAS_MSCC_PIF_PLMN_WITH_CSG_ID_INFO_STRU                *pstCsgIdInfoList
)
{
    VOS_UINT32                                              ulReportListIndex;
    NAS_MML_PLMN_WITH_CSG_ID_STRU                           stPlmnWithCsgId;
    NAS_MMC_CSG_SEARCHED_PLMN_LIST_INFO_STRU               *pstCsgPlmnIdList = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_CSG_ID_LIST_STRU                     *pstOperatorList  = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_CSG_ID_LIST_STRU                     *pstAllowedCsgList  = VOS_NULL_PTR;
    VOS_UINT32                                              ulCsgIdInCsgListIndex;
    VOS_UINT32                                              ucHomeNodebNameIndication;

    /* �ҵ���ǰ�ѱ���λ�õ���һ��λ�� */
    ulReportListIndex              = pstCsgIdInfoList->ulPlmnWithCsgIdNum;

    /* ��ʼ����ʱ����PLMN ID�����ں����Ƚ�Operator listʹ�� */
    pstCsgPlmnIdList               = NAS_MMC_GetCsgSearchedPlmnListInfo_PlmnList();
    stPlmnWithCsgId.stPlmnId.ulMcc = pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[ulIndex].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMcc;
    stPlmnWithCsgId.stPlmnId.ulMnc = pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[ulIndex].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMnc;
    stPlmnWithCsgId.ulCsgId        = pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[ulIndex].stPlmnCsgIdWithRat.ulCsgId;

    /* ���ݺ������ulIndex���ҵ���Ӧ״̬���������б���Ĵ�CSG ID��������뵽��MSCC�ϱ���
    CSG ID LIST�У������λ��Ϊ����ǰ��MSCC�ϱ���CSG ID LIST���Ѵ��ڵ����һ��CSG ID����һ��λ�� */

    /* �б��Ѿ�����ֱ�ӷ��� */
    if (ulReportListIndex >= NAS_MSCC_PIF_MAX_PLMN_CSG_ID_NUM)
    {
        return;
    }

    /* ����PLMN */
    pstCsgIdInfoList->astPlmnWithCsgIdList[ulReportListIndex].stPlmnId.ulMcc
                    = pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[ulIndex].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMcc;
    pstCsgIdInfoList->astPlmnWithCsgIdList[ulReportListIndex].stPlmnId.ulMnc
                    = pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[ulIndex].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMnc;

    /* ����CSG ID */
    pstCsgIdInfoList->astPlmnWithCsgIdList[ulReportListIndex].ulCsgId
                    = pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[ulIndex].stPlmnCsgIdWithRat.ulCsgId;

    /* ������뼼�� */
    NAS_MMC_ConvertRrcRatToNasFormat(pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[ulIndex].stPlmnCsgIdWithRat.stPlmnWithRat.ulRat,
                    &pstCsgIdInfoList->astPlmnWithCsgIdList[ulReportListIndex].enRatType);

    /* ����CSG ID TYPE */
    pstCsgIdInfoList->astPlmnWithCsgIdList[ulReportListIndex].enPlmnWithCsgIdType
                    = NAS_MMC_ConvertMmlCsgIdTypeToMsccCsgIdType_PlmnList(enCsgIdType);

    /* ����HNB Name */
    pstCsgIdInfoList->astPlmnWithCsgIdList[ulReportListIndex].ucHomeNodeBNameLen
                    = NAS_MML_MIN(pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[ulIndex].stHomeNodeBName.ucHomeNodeBNameLen, NAS_MML_MAX_HOME_NODEB_NAME_LEN);
    PS_MEM_CPY(pstCsgIdInfoList->astPlmnWithCsgIdList[ulReportListIndex].aucHomeNodeBName,
                    pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[ulIndex].stHomeNodeBName.aucHomeNodeBName,
                    pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[ulIndex].stHomeNodeBName.ucHomeNodeBNameLen);

    pstOperatorList       = NAS_MML_GetOperatorCsgList();
    ulCsgIdInCsgListIndex = NAS_MML_GetCsgIdIndexInDestCsgIdList(&stPlmnWithCsgId, pstOperatorList->ulPlmnWithCsgIdListNum, pstOperatorList->astPlmnWithCsgIdInfo);

    /* ������Operator list�е������ֱ������CSG TYPEΪ0 */
    pstCsgIdInfoList->astPlmnWithCsgIdList[ulReportListIndex].ucCsgTypeLen = 0;
    PS_MEM_SET(pstCsgIdInfoList->astPlmnWithCsgIdList[ulReportListIndex].aucCsgType,
                                    0, NAS_MSCC_PIF_CSG_TYPE_LEN);

    /* Operator list���ҵ���Ӧ���λ������д��Ӧ��csg type */
    if (pstOperatorList->ulPlmnWithCsgIdListNum > ulCsgIdInCsgListIndex)
    {
        /* ATT ���� :
        1. Operator list�е�HNB indicator���ò�Ϊ0x00ʱ��
           ���operator list�д���HNB NAME,������ʾoperator list�е�HNB NAME;������ʾEONS NAME(hnb_len ����Ϊ0)
        2. Operator list�е�HNB indicator����Ϊ0x00ʱ�����SIB20/SIB9�е�HNB��Ч��������ʾSIB20/SIB9�е�HNB,
           ������ʾENOS NAME*/
        ucHomeNodebNameIndication = pstOperatorList->astPlmnWithCsgIdInfo[ulCsgIdInCsgListIndex].stHomeNodeBName.ucHomeNodebNameIndication;

        NAS_NORMAL_LOG1(WUEPS_PID_MMC, "NAS_MMC_AddCsgIdToListCnf_PlmnList,ucHomeNodebNameIndication is :",ucHomeNodebNameIndication);
        if (0x00 != ucHomeNodebNameIndication)
        {
            pstCsgIdInfoList->astPlmnWithCsgIdList[ulReportListIndex].ucHomeNodeBNameLen = 0;
            PS_MEM_SET(pstCsgIdInfoList->astPlmnWithCsgIdList[ulReportListIndex].aucHomeNodeBName,
                                            0, NAS_MSCC_PIF_MAX_HOME_NODEB_NAME_LEN);

            if (0 < pstOperatorList->astPlmnWithCsgIdInfo[ulCsgIdInCsgListIndex].stHomeNodeBName.ucHomeNodeBNameLen)
            {
                pstCsgIdInfoList->astPlmnWithCsgIdList[ulReportListIndex].ucHomeNodeBNameLen
                                = pstOperatorList->astPlmnWithCsgIdInfo[ulCsgIdInCsgListIndex].stHomeNodeBName.ucHomeNodeBNameLen;
                PS_MEM_CPY(pstCsgIdInfoList->astPlmnWithCsgIdList[ulReportListIndex].aucHomeNodeBName,
                       pstOperatorList->astPlmnWithCsgIdInfo[ulCsgIdInCsgListIndex].stHomeNodeBName.aucHomeNodeBName,
                       pstOperatorList->astPlmnWithCsgIdInfo[ulCsgIdInCsgListIndex].stHomeNodeBName.ucHomeNodeBNameLen);
            }
        }

        pstCsgIdInfoList->astPlmnWithCsgIdList[ulReportListIndex].ucCsgTypeLen
                      = NAS_MML_MIN(pstOperatorList->astPlmnWithCsgIdInfo[ulCsgIdInCsgListIndex].stCsgType.ucCsgTypeLen, NAS_MML_MAX_CSG_TYPE_LEN);

        PS_MEM_CPY(pstCsgIdInfoList->astPlmnWithCsgIdList[ulReportListIndex].aucCsgType,
                                pstOperatorList->astPlmnWithCsgIdInfo[ulCsgIdInCsgListIndex].stCsgType.aucCsgType,
                                pstOperatorList->astPlmnWithCsgIdInfo[ulCsgIdInCsgListIndex].stCsgType.ucCsgTypeLen);

        pstCsgIdInfoList->ulPlmnWithCsgIdNum++;
        return;
    }

    /* ����operator csg list������allowed csg list�в��Ҷ�Ӧ���λ����д��Ӧ��csg type */
    pstAllowedCsgList     = NAS_MML_GetAllowedCsgList();
    ulCsgIdInCsgListIndex = NAS_MML_GetCsgIdIndexInDestCsgIdList(&stPlmnWithCsgId, pstAllowedCsgList->ulPlmnWithCsgIdListNum, pstAllowedCsgList->astPlmnWithCsgIdInfo);

    if (pstAllowedCsgList->ulPlmnWithCsgIdListNum > ulCsgIdInCsgListIndex)
    {
        pstCsgIdInfoList->astPlmnWithCsgIdList[ulReportListIndex].ucCsgTypeLen
                      = NAS_MML_MIN(pstAllowedCsgList->astPlmnWithCsgIdInfo[ulCsgIdInCsgListIndex].stCsgType.ucCsgTypeLen, NAS_MML_MAX_CSG_TYPE_LEN);

        PS_MEM_CPY(pstCsgIdInfoList->astPlmnWithCsgIdList[ulReportListIndex].aucCsgType,
                                pstAllowedCsgList->astPlmnWithCsgIdInfo[ulCsgIdInCsgListIndex].stCsgType.aucCsgType,
                                pstAllowedCsgList->astPlmnWithCsgIdInfo[ulCsgIdInCsgListIndex].stCsgType.ucCsgTypeLen);
    }

    pstCsgIdInfoList->ulPlmnWithCsgIdNum++;
    return;
}


NAS_MSCC_PIF_PLMN_WITH_CSG_ID_TYPE_ENUM_UINT8 NAS_MMC_ConvertMmlCsgIdTypeToMsccCsgIdType_PlmnList(
    NAS_MML_CSG_ID_TYPE_ENUM_UINT8      enCsgIdType
)
{
    NAS_MSCC_PIF_PLMN_WITH_CSG_ID_TYPE_ENUM_UINT8    enMsccCsgIdType;

    switch(enCsgIdType)
    {
        case    NAS_MML_CSG_ID_TYPE_IN_ALLOWED_CSG_LIST:
        case    NAS_MML_CSG_ID_TYPE_IN_ALLOWED_AND_OPERATOR_CSG_LIST:

                enMsccCsgIdType = NAS_MSCC_PIF_CSG_ID_TYPE_IN_ALLOWED_CSG_LIST;
                break;

        case    NAS_MML_CSG_ID_TYPE_IN_OPERATOR_CSG_LIST_NOT_FOBIDDEN:

                enMsccCsgIdType = NAS_MSCC_PIF_CSG_ID_TYPE_IN_OPERATOR_CSG_LIST_NOT_FOBIDDEN;
                break;

        case    NAS_MML_CSG_ID_TYPE_IN_OPERATOR_CSG_LIST_FOBIDDEN:

                enMsccCsgIdType = NAS_MSCC_PIF_CSG_ID_TYPE_IN_OPERATOR_CSG_LIST_FOBIDDEN;
                break;

        case    NAS_MML_CSG_ID_TYPE_NOT_IN_ALLOWED_AND_OPERATOR_CSG_LIST:

                enMsccCsgIdType = NAS_MSCC_PIF_CSG_ID_TYPE_NOT_IN_ALLOWED_AND_OPERATOR_CSG_LIST;
                break;
        default:

                enMsccCsgIdType = NAS_MSCC_PIF_CSG_ID_TYPE_BUTT;
                break;

    }

    return enMsccCsgIdType;
}

#if (FEATURE_ON == FEATURE_LTE)

VOS_UINT32  NAS_MMC_RcvCsgListAbortReq_PlmnList_WaitEpsRegInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

    /* ����ID_MMC_MSCC_PLMN_LIST_ABORT_CNF */
    NAS_MMC_SndMsccCsgListAbortCnf_PlmnList();

    /* δ��ʼ��������ʱ�����б�Ϊ��,��¼��ǰע�ᵼ�µĺ���additionֵ��L1 MAIN��
       �յ���·�ͷź����additionֵ�����Ƿ񴥷����� */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

VOS_UINT32  NAS_MMC_RcvCsgListAbortReq_PlmnList_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND);

    /* ����ID_MMC_MSCC_PLMN_LIST_ABORT_CNF */
    NAS_MMC_SndMsccCsgListAbortCnf_PlmnList();

    /* δ��ʼ��������ʱ�����б�Ϊ��,��¼��ǰע�ᵼ�µĺ���additionֵ��L1 MAIN��
       �յ���·�ͷź����additionֵ�����Ƿ񴥷����� */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());

    /*�˳�״̬��*/
     NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitLmmCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ�ȴ�LMM��������ı�����ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_CSG_LIST_SEARCH_CNF);

    /* ��¼״̬���˳���� */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ��LMM����ֹͣ��������,Ǩ��NAS_MMC_PLMN_LIST_STA_WAIT_LMM_CSG_LIST_SEARCH_STOP_CNF״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatCsgListSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);
    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvMsccCsgListAbortReq_PlmnList_WaitLmmCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ�ȴ�LMM��������ı�����ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_CSG_LIST_SEARCH_CNF);

    /* ��¼״̬���˳���� */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ����֪ͨMSCC�ظ���� */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    /* ��LMM����ֹͣ��������,Ǩ��NAS_MMC_PLMN_LIST_STA_WAIT_LMM_CSG_LIST_SEARCH_STOP_CNF״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatCsgListSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvLmmCsgListSrchCnf_PlmnList_WaitLmmCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_CSG_LIST_SEARCH_CNF_STRU   *pstLmmCsgListSearchCnf = VOS_NULL_PTR;

    pstLmmCsgListSearchCnf = (LMM_MMC_CSG_LIST_SEARCH_CNF_STRU*)pstMsg;

    /* ����CSG LIST������� */
    NAS_MMC_ProcLmmCsgListSearchCnf_PlmnList(pstLmmCsgListSearchCnf);

    return VOS_TRUE;
}


VOS_VOID NAS_MMC_ProcLmmCsgListSearchCnf_PlmnList(
    LMM_MMC_CSG_LIST_SEARCH_CNF_STRU   *pstLmmCsgListSrchCnf
)
{

    /* �ж�CSG LIST������� */
    switch (pstLmmCsgListSrchCnf->enRlst)
    {
        case MMC_LMM_CSG_LIST_SRCH_RLT_NO_RF:

            /* ֹͣ�ȴ�LMM�����ظ��ı�����ʱ�� */
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_CSG_LIST_SEARCH_CNF);

            NAS_MMC_ProcNoRf_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);
            return;

        case MMC_LMM_CSG_LIST_SRCH_RLT_REJ:

            /* ֹͣ�ȴ�LMM�����ظ��ı�����ʱ�� */
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_CSG_LIST_SEARCH_CNF);

            if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
            {
                /* ����LIST REJ��MSCC */
                NAS_MMC_SndMsccCsgListSearchRej();
            }
            else
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH, TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST_LEN);
            }

            /* ����״̬��ʧ���˳��Ľ�� */
            NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                     VOS_FALSE,
                                     NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                     NAS_MMC_GetRegRsltInfo_PlmnList());

            /* �˳�״̬�� */
            NAS_MMC_FSM_QuitFsmL2();
            return;

        case MMC_LMM_CSG_LIST_SRCH_RLT_FAIL:

            /* ֹͣ�ȴ�LMM�����ظ��ı�����ʱ�� */
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_CSG_LIST_SEARCH_CNF);

            /* ����LIST REJ��MSCC */
            NAS_MMC_SndMsccCsgListSearchRej();

            /* ����״̬��ʧ���˳��Ľ�� */
            NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                     VOS_FALSE,
                                     NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                     NAS_MMC_GetRegRsltInfo_PlmnList());

            /* �˳�״̬�� */
            NAS_MMC_FSM_QuitFsmL2();
            return;

        case MMC_LMM_CSG_LIST_SRCH_RLT_SUCC:

            /* �����б���������������ϱ� */
            NAS_MMC_ProcLmmCsgListSearchSucc_PlmnList(pstLmmCsgListSrchCnf);
            return;

        default:

            /* �쳣��ӡ */
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmCsgListSearchCnf_PlmnList: Unexpected Csg List Search Result!");
            break;

    }

    /* һ�׶�ֻ֧����LTE����˲������ж�����ģ��ֱ���˳�״̬�� */
    return;

}


VOS_VOID NAS_MMC_ProcLmmCsgListSearchSucc_PlmnList(
    LMM_MMC_CSG_LIST_SEARCH_CNF_STRU   *pstLmmCsgListSrchCnf
)
{
    NAS_MMC_CSG_SEARCHED_PLMN_LIST_INFO_STRU               *pstCsgPlmnIdList  = VOS_NULL_PTR;

    /* ����LMM�ϱ����б��ѽ����״̬���������� */
    NAS_MMC_SaveLmmCsgListSearchResult_PlmnList(pstLmmCsgListSrchCnf);

    /* �ϱ���������ʱ��˵��LMM�Ѿ��ϱ�������������� */
    if (VOS_TRUE == pstLmmCsgListSrchCnf->ucCsgListResultCompleteFlag)
    {
        /* ֹͣ�ȴ�LMM�����ظ��ı�����ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_CSG_LIST_SEARCH_CNF);

        NAS_MMC_InitSpecRatSearchedPlmnListInfo_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

        NAS_MMC_SetSpecRatSearchedTypeByLmmPlmnSearchCnfSucc_PlmnList(NAS_MML_NET_RAT_TYPE_LTE, MMC_LMM_PLMN_SRCH_RLT_INTER_LIST_FULL_BAND_SUCC);

        /* ����L�ѱ������� */
        NAS_MMC_SetSearchedFlag_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

        /* ����CSG���������ս��ˢ��״̬���������еĸߵ����������б� */
        pstCsgPlmnIdList = NAS_MMC_GetCsgSearchedPlmnListInfo_PlmnList();
        NAS_MMC_UpdateSearchedPlmnListInfoFromCsgSearchResult_PlmnList(pstCsgPlmnIdList);

        NAS_MMC_SndMsccCsgListSearchCnf_PlmnList();

        /* CSG LIST����������,RRC���ܳ�������,��ʱ��Ҫ��������״̬,�����˳�LIST�������ָ������ */
        if (NAS_MMC_AS_CELL_NOT_CAMP_ON == NAS_MMC_GetAsCellCampOn())
        {
            NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);
        }

        /* ����״̬���˳��Ľ�� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_SUCC,
                                 (VOS_UINT8)NAS_MMC_IsNeedPlmnSearch_PlmnList(),
                                 NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                 NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

    }

    return;
}


VOS_VOID NAS_MMC_SaveLmmCsgListSearchResult_PlmnList(
    LMM_MMC_CSG_LIST_SEARCH_CNF_STRU   *pstLmmCsgListSrchCnf
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              ulSavePlmnNum;   /* ���ο��Ա����PLMN���� */
    NAS_MMC_CSG_SEARCHED_PLMN_LIST_INFO_STRU               *pstCsgPlmnIdList = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                                    stGUNasPlmn;
    MMC_LMM_PLMN_ID_STRU                                    stLMMPlmn;
    VOS_UINT32                                              ulTotalPlmnNum;

    /* LMM���ܻ������ϱ���ֹ1����Ϣ����˴˴������ۼӷ�ʽ���� */
    pstCsgPlmnIdList = NAS_MMC_GetCsgSearchedPlmnListInfo_PlmnList();
    ulTotalPlmnNum   = pstCsgPlmnIdList->ulTotalPlmnNum;


    /* �������������������ֻ��ʣ���λ�ý��б���(��ֹѭ������Խ��)��������Ͱ�LMMʵ���ϱ��������б���
    ����: ����35���Ѿ�������30�������LMM���ϱ���10�����Ǿ�ֻ����ǰ��5����ʣ�µĶ���*/
    if (NAS_MML_MAX_PLMN_CSG_ID_NUM < pstCsgPlmnIdList->ulTotalPlmnNum + pstLmmCsgListSrchCnf->stCsgListSearchedResult.ulTotalPlmnNum)
    {
        ulSavePlmnNum = NAS_MML_MAX_PLMN_CSG_ID_NUM - pstCsgPlmnIdList->ulTotalPlmnNum;
    }
    else
    {
        ulSavePlmnNum = pstLmmCsgListSrchCnf->stCsgListSearchedResult.ulTotalPlmnNum;
    }

    /* ��LMM�ϱ���CSG�б��ѽ�����棬ͬʱ��PLMNת����GU�ĸ�ʽ��ע�����ۼӱ��棬���α���Ҫ��������������һ��λ�ÿ�ʼ */
    for (i = pstCsgPlmnIdList->ulTotalPlmnNum; i < pstCsgPlmnIdList->ulTotalPlmnNum + ulSavePlmnNum; i++)
    {
        /* ������뼼�� */
        NAS_MMC_ConvertLmmRatToRrcFormat(pstLmmCsgListSrchCnf->stCsgListSearchedResult.astCsgListSearchedPlmnInfoList[i-ulTotalPlmnNum].stPlmnCsgIdWithRat.stPlmnWithRat.enPlmnRat,
              &pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stPlmnCsgIdWithRat.stPlmnWithRat.ulRat);

        /* ����CSG ID */
        pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stPlmnCsgIdWithRat.ulCsgId
                    = pstLmmCsgListSrchCnf->stCsgListSearchedResult.astCsgListSearchedPlmnInfoList[i-ulTotalPlmnNum].stPlmnCsgIdWithRat.ulCsgId;

        /* ����HNB Name */
        pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stHomeNodeBName.ucHomeNodeBNameLen
                    = NAS_MML_MIN(pstLmmCsgListSrchCnf->stCsgListSearchedResult.astCsgListSearchedPlmnInfoList[i-ulTotalPlmnNum].stHomeNodeBName.ucHomeNodeBNameLen, NAS_MML_MAX_HOME_NODEB_NAME_LEN);

        PS_MEM_CPY(pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stHomeNodeBName.aucHomeNodeBName,
                    pstLmmCsgListSrchCnf->stCsgListSearchedResult.astCsgListSearchedPlmnInfoList[i-ulTotalPlmnNum].stHomeNodeBName.aucHomeNodeBName,
                    pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stHomeNodeBName.ucHomeNodeBNameLen);

        /* ����lRscp */
        pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].lRscp
                    = pstLmmCsgListSrchCnf->stCsgListSearchedResult.astCsgListSearchedPlmnInfoList[i-ulTotalPlmnNum].lRscp;

        /* ת��������PLMN */

        /* ��ʼ����ʱ���� */
        PS_MEM_SET(&stGUNasPlmn, 0, sizeof(NAS_MML_PLMN_ID_STRU));
        PS_MEM_SET(&stLMMPlmn,   0, sizeof(MMC_LMM_PLMN_ID_STRU));

        /* ȡ��LMM��PLMN����ʱ���� */
        PS_MEM_CPY(stLMMPlmn.aucPlmnId,
                    pstLmmCsgListSrchCnf->stCsgListSearchedResult.astCsgListSearchedPlmnInfoList[i-ulTotalPlmnNum].stPlmnCsgIdWithRat.stPlmnWithRat.aucPlmnId,
                    MMC_LMM_PLMN_ID_LEN);

        /* ת��L��PLMN��GU�ĸ�ʽ */
        NAS_MMC_ConvertLmmPlmnToGUNasFormat(&stLMMPlmn, &stGUNasPlmn);

        /* ����PLMN */
        pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMcc = stGUNasPlmn.ulMcc;
        pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMnc = stGUNasPlmn.ulMnc;

    }

    /* ����PLMN���� */
    pstCsgPlmnIdList->ulTotalPlmnNum += ulSavePlmnNum;

    /* ��������ȼ�PLMN������ע�����LMM�ϱ���PLMNû��ȫ�����棬��ֻ����ʵ�ʱ���ĸ��� */
    pstCsgPlmnIdList->ulHighPlmnNum  += NAS_MML_MIN(pstLmmCsgListSrchCnf->stCsgListSearchedResult.ulHighPlmnNum, ulSavePlmnNum);

    return;

}


VOS_UINT32  NAS_MMC_RcvTiWaitLmmCsgListSrchCnfExpired_PlmnList_WaitLmmCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitLmmCsgListSrchCnfExpired_PlmnList_WaitLmmCsgListSearchCnf: Timer Expired");
    /* ���µ�ǰRAT��������� */
    NAS_MMC_SetSearchedFlag_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

    /* ��LMM����ֹͣ��������,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatCsgListSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvLmmAreaLostInd_PlmnList_WaitLmmCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_AREA_LOST_IND_STRU                             *pstAreaLostInd = VOS_NULL_PTR;

    pstAreaLostInd = (LMM_MMC_AREA_LOST_IND_STRU*)pstMsg;
    NAS_MMC_SetSpecRatSearchedTypeByLmmAreaLostInd_PlmnList(NAS_MML_GetCurrNetRatType(), pstAreaLostInd);

    /* ���פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* ��ǰ�źŸ��� */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    /* ���·���״̬ �ϱ��޷���*/
    NAS_MMC_SetCsServiceStatus(NAS_MMC_NO_SERVICE);
    NAS_MMC_SetPsServiceStatus(NAS_MMC_NO_SERVICE);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvLmmSysInfoInd_PlmnList_WaitLmmCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ProcLteSysInfo_PlmnList(pstMsg);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvLmmAttachInd_PlmnList_WaitLmmCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_ATTACH_IND_STRU                                *pstLmmAttachIndMsg = VOS_NULL_PTR;

    pstLmmAttachIndMsg  = (LMM_MMC_ATTACH_IND_STRU*)pstMsg;

    /* ��GMM��MMת��ע������Ϣ */
    NAS_MMC_SndMmLmmAttachInd(pstLmmAttachIndMsg);
    NAS_MMC_SndGmmLmmAttachInd(pstLmmAttachIndMsg);

    /* ����attach��� */
    NAS_MMC_ProcLmmAttachInd_PlmnList(pstLmmAttachIndMsg);

    /* L��ע����ɺ�IMSʱ֧��ʱ�ᷢ��IMSע��,��Ҫ����IMSע�����������Ƿ���Ҫ
       disable Lģ,��ʱ��Ҫ��һ���ȴ�IMS��ע���� */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();

#if (FEATURE_ON == FEATURE_IMS)
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_IMS);
#endif

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvLmmTauResultInd_PlmnList_WaitLmmCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg;

    pstLmmTauIndMsg  = (LMM_MMC_TAU_RESULT_IND_STRU*)pstMsg;

    /* ��GMM��MMת��ע������Ϣ */
    NAS_MMC_SndMmLmmTauResultInd(pstLmmTauIndMsg);
    NAS_MMC_SndGmmLmmTauResultInd(pstLmmTauIndMsg);

    /* ����tau��� */
    NAS_MMC_ProcLmmTauResultInd_PlmnList(pstLmmTauIndMsg);

    /* L��ע����ɺ�IMSʱ֧��ʱ�ᷢ��IMSע��,��Ҫ����IMSע�����������Ƿ���Ҫ
       disable Lģ,��ʱ��Ҫ��һ���ȴ�IMS��ע���� */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();

#if (FEATURE_ON == FEATURE_IMS)
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_IMS);
#endif

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvMsccImsVoiceCapInd_PlmnList_WaitLmmCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU *pstImsVoiceInd = VOS_NULL_PTR;
    VOS_UINT8                           ucWaitRegRsltFlag;

    ucWaitRegRsltFlag   = NAS_MMC_GetWaitRegRsltFlag_PlmnList();
    pstImsVoiceInd      = (MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU *)pstMsg;

    /* ����ڵȴ�IMS��ע�����Ŵ��� */
    if (NAS_MMC_WAIT_REG_RESULT_IND_IMS != (ucWaitRegRsltFlag & NAS_MMC_WAIT_REG_RESULT_IND_IMS))
    {
        return VOS_TRUE;
    }

    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_IMS);

    /* IMS������ʱ�ж��Ƿ���Ҫdisable LTE */
    if (VOS_FALSE  == pstImsVoiceInd->ucAvail)
    {
        if (VOS_TRUE == NAS_MMC_IsNeedDisableLte_ImsVoiceNotAvail())
        {
            NAS_MMC_SetCsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION);

            NAS_MML_DisableLteCommProc(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS,
                                       MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);

            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMsccImsVoiceCapInd_PlmnList_WaitLmmCsgListSearchCnf: MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE");
        }
    }

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitLmmCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��ABORT��־λ */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvMsccCsgListAbortFsmMsg_PlmnList_WaitLmmCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��ABORT��־λ */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ����֪ͨMSCC����ı�� */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvLmmCsgListSrchCnf_PlmnList_WaitLmmCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_CSG_LIST_SEARCH_CNF_STRU   *pstLmmCsgListsearchCnf = VOS_NULL_PTR;
    NAS_MMC_CSG_SEARCHED_PLMN_LIST_INFO_STRU               *pstCsgPlmnIdList  = VOS_NULL_PTR;

    pstLmmCsgListsearchCnf = (LMM_MMC_CSG_LIST_SEARCH_CNF_STRU*)pstMsg;

    /* LIST�����ظ���ֹͣ�����Գ�,NO RFʱֱ���˳�LIST�������� */
    if (MMC_LMM_CSG_LIST_SRCH_RLT_NO_RF == pstLmmCsgListsearchCnf->enRlst)
    {
        /* ֹͣ������ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF);

        NAS_MMC_ProcNoRf_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

        return VOS_TRUE;
    }

    /*ֻ���������ɹ�ʱ�Ž��д��� */
    if (MMC_LMM_CSG_LIST_SRCH_RLT_SUCC != pstLmmCsgListsearchCnf->enRlst)
    {
        return VOS_TRUE;
    }

    /* ����LMM�ϱ����б��ѽ����״̬���������� */
    NAS_MMC_SaveLmmCsgListSearchResult_PlmnList(pstLmmCsgListsearchCnf);

    /* �ϱ���������ʱ��˵��LMM�Ѿ��ϱ�������������� */
    if (VOS_TRUE == pstLmmCsgListsearchCnf->ucCsgListResultCompleteFlag)
    {
        /* ֹͣ������ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF);

        NAS_MMC_InitSpecRatSearchedPlmnListInfo_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

        NAS_MMC_SetSpecRatSearchedTypeByLmmPlmnSearchCnfSucc_PlmnList(NAS_MML_NET_RAT_TYPE_LTE, MMC_LMM_PLMN_SRCH_RLT_INTER_LIST_FULL_BAND_SUCC);

        /* ����L�ѱ������� */
        NAS_MMC_SetSearchedFlag_PlmnList(MMC_LMM_RAT_LTE);

        /* ����CSG���������ս��ˢ��״̬���������еĸߵ����������б� */
        pstCsgPlmnIdList = NAS_MMC_GetCsgSearchedPlmnListInfo_PlmnList();
        NAS_MMC_UpdateSearchedPlmnListInfoFromCsgSearchResult_PlmnList(pstCsgPlmnIdList);

        /* ��������ֹͣ�ظ���� */
        NAS_MMC_ProcLmmCsgListSearchStopCnf_PlmnList();
    }
    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvLmmPlmnSrchStopCnf_PlmnList_WaitLmmCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF);

    /* ��������ֹͣ�ظ���� */
    NAS_MMC_ProcLmmCsgListSearchStopCnf_PlmnList();

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvTiWaitLmmStopCnfExpired_PlmnList_WaitLmmCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitLmmStopCnfExpired_PlmnList_WaitLmmCsgListSearchStopCnf: Timer Expired");

    /* ��������ֹͣ�ظ���� */
    NAS_MMC_ProcLmmCsgListSearchStopCnf_PlmnList();

    return VOS_TRUE;
}



VOS_UINT32 NAS_MMC_RcvLmmAreaLostInd_PlmnList_WaitLmmCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ���פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* ��ǰ�źŸ��� */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    /* ���·���״̬ �ϱ��޷���*/
    NAS_MMC_SetCsServiceStatus(NAS_MMC_NO_SERVICE);
    NAS_MMC_SetPsServiceStatus(NAS_MMC_NO_SERVICE);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvLmmSysInfoInd_PlmnList_WaitLmmCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ProcLteSysInfo_PlmnList(pstMsg);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvLmmAttachInd_PlmnList_WaitLmmCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_ATTACH_IND_STRU                                *pstLmmAttachIndMsg = VOS_NULL_PTR;

    pstLmmAttachIndMsg  = (LMM_MMC_ATTACH_IND_STRU*)pstMsg;

    /* ��GMM��MMת��ע������Ϣ */
    NAS_MMC_SndMmLmmAttachInd(pstLmmAttachIndMsg);
    NAS_MMC_SndGmmLmmAttachInd(pstLmmAttachIndMsg);

    /* ����attach��� */
    NAS_MMC_ProcLmmAttachInd_PlmnList(pstLmmAttachIndMsg);

    /* L��ע����ɺ�IMSʱ֧��ʱ�ᷢ��IMSע��,��Ҫ����IMSע�����������Ƿ���Ҫ
       disable Lģ,��ʱ��Ҫ��һ���ȴ�IMS��ע���� */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();

#if (FEATURE_ON == FEATURE_IMS)
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_IMS);
#endif

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvLmmTauResultInd_PlmnList_WaitLmmCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg;

    pstLmmTauIndMsg  = (LMM_MMC_TAU_RESULT_IND_STRU*)pstMsg;

    /* ��GMM��MMת��ע������Ϣ */
    NAS_MMC_SndMmLmmTauResultInd(pstLmmTauIndMsg);
    NAS_MMC_SndGmmLmmTauResultInd(pstLmmTauIndMsg);

    /* ����tau��� */
    NAS_MMC_ProcLmmTauResultInd_PlmnList(pstLmmTauIndMsg);

    /* L��ע����ɺ�IMSʱ֧��ʱ�ᷢ��IMSע��,��Ҫ����IMSע�����������Ƿ���Ҫ
       disable Lģ,��ʱ��Ҫ��һ���ȴ�IMS��ע���� */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();

#if (FEATURE_ON == FEATURE_IMS)
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_IMS);
#endif

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvMsccImsVoiceCapInd_PlmnList_WaitLmmCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU *pstImsVoiceInd = VOS_NULL_PTR;
    VOS_UINT8                           ucWaitRegRsltFlag;

    ucWaitRegRsltFlag   = NAS_MMC_GetWaitRegRsltFlag_PlmnList();
    pstImsVoiceInd      = (MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU *)pstMsg;

    /* ����ڵȴ�IMS��ע�����Ŵ��� */
    if (NAS_MMC_WAIT_REG_RESULT_IND_IMS != (ucWaitRegRsltFlag & NAS_MMC_WAIT_REG_RESULT_IND_IMS))
    {
        return VOS_TRUE;
    }

    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_IMS);

    /* IMS������ʱ�ж��Ƿ���Ҫdisable LTE */
    if (VOS_FALSE  == pstImsVoiceInd->ucAvail)
    {
        if (VOS_TRUE == NAS_MMC_IsNeedDisableLte_ImsVoiceNotAvail())
        {
            NAS_MMC_SetCsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION);

            NAS_MML_DisableLteCommProc(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS,
                                       MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);

            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMsccImsVoiceCapInd_PlmnList_WaitLmmCsgListSearchStopCnf: MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE");
        }
    }

    return VOS_TRUE;
}


VOS_VOID NAS_MMC_ProcLmmCsgListSearchStopCnf_PlmnList(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNextRatType;

    VOS_UINT32                          ulNeedPlmnSearch;

    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnList())
    {
        ulNeedPlmnSearch = VOS_FALSE;

        /* ֪ͨMSCC�ظ����Ϊ�� */
        if ( VOS_TRUE == NAS_MMC_GetNotifyMsccFlag_PlmnList())
        {
            /* ��MSCC�ظ�ID_MMC_MSCC_PLMN_LIST_ABORT_CNF */
            NAS_MMC_SndMsccCsgListAbortCnf_PlmnList();

            ulNeedPlmnSearch = NAS_MMC_IsNeedPlmnSearch_PlmnList();
        }
        else
        {
            /* ��MSCC�ظ�LIST������� */
            NAS_MMC_SndMsccCsgListSearchCnf_PlmnList();
        }

        /* ����״̬��ABORT�˳���� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                                (VOS_UINT8)ulNeedPlmnSearch,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* ��ȡ������һ��δ�����Ľ���ģʽ */
    if ( VOS_FALSE == NAS_MMC_GetNextSearchingRat_PlmnList(&enNextRatType))
    {
        /* �����������������������ϱ���MSCC */
        NAS_MMC_SndMsccCsgListSearchCnf_PlmnList();

        /* ����״̬���ɹ��˳��Ľ�� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                 (VOS_UINT8)NAS_MMC_IsNeedPlmnSearch_PlmnList(),
                                 NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                 NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* ��ǰ���뼼�����͹�������,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatSuspendReq_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

    /* ��GMM��������ָʾ */
    NAS_MMC_SndGmmPlmnSchInit();

    /* ��MM��������ָʾ */
    NAS_MMC_SndMmPlmnSchInit();

    return;
}
#endif
#endif

/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



