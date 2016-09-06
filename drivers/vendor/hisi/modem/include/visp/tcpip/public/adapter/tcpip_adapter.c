

/*
һ���ɲü���������˵��
          ����Ŀ�ģ���Ʒ������������������VISP��ģ��Ĳü���
          ���亯���б���TCPIP_RegAllAppInfo:
                        ���Ƽ�ֱ���޸ĸú������������tcpip_adapter.h�е�˵��.
                        TCPIP_GetMaxSockNum:
                        ��������Ʒ�޸�,�����������û�����Vtcpip_sock.h�е�VRP_FD_SETSIZE�꣬���Ըú���������Ϊ�ⲿ����.
                        VISP_InitTCPIPStack:
                        VISP��������������Ʒ�����޸Ĵ˺���, ��������Ԥ���ô�����VISP���Ӻ���ע�ᴦ����.
*/

#ifdef  __cplusplus
extern "C" {
#endif
#include "tcpip/public/tcpip_basetype.h"
#include "tcpip/public/tcpip_id.h"
#include "tcpip/public/vrpvos/mbuf.h"
#include "tcpip/public/tcpip_sock.h"
#include "tcpip/public/tcpip_pub_api.h"

#include "tcpip_adapter.h"
#include "tcpip/vrrp/include/vrrp_api.h"
#include "tcpip/public/tcpip_pub.h"
#include "tcpip/public/tcpip_hdr.h"
#include "tcpip/public/tcpip_config.h"
#ifdef WIN32
/*lint -e322*/
/*lint -e7*/
#include "sim_ha/sim_ha.h"
/*lint +e7*/
/*lint +e322*/
#endif

extern LONG vos_printf(const CHAR *fmt, ...);

/* BFD NPģʽ���ã�������Э��ջ֮ǰ���� */
ULONG g_ulVttBfdNpMode = 0;
/****************************************************************************
*    Func Name: TCPIP_RegAllAppInfo()
* Date Created: 2004-7-7
*       Author: zhany hong yan(19316)
*  Description: VISP ���ע�ắ��
*       Output: ��
*       Return: ��
*      Caution: �����û���Ҫֱ���޸ı�������
*               ��Ҫ��������ü������޸���������ע��ꡣ
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2004-7-7  zhany hong yan(19316)         Creat the first version.
*
*******************************************************************************/
VOID TCPIP_RegAllAppInfo()
{
    ULONG ulErrCode = 0;

    /*��ʼ���������*/
#if(TCPIP_COMP_INITIAL == VRP_YES)
    {
        extern ULONG COMP_Init();
        if (COMP_Init())
        {
            (VOID)vos_printf("\n\rcomponent initial error");
        }
    }
#endif

#if(TCPIP_COMP_REGISTER_ETH == VRP_YES)
    {
        extern ULONG ETHARP_RegApp();
        ulErrCode = ETHARP_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }
#endif

#if(TCPIP_COMP_REGISTER_PPP == VRP_YES)
    {
        extern ULONG PPP_RegApp();
        ulErrCode = PPP_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }
#endif

    {
        extern ULONG IP_PP4_RegApp();
        ulErrCode = IP_PP4_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }

    {
        extern ULONG IP_AM4_RegApp();
        ulErrCode = IP_AM4_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }


    {
        extern ULONG SFIB_RegApp();
        ulErrCode = SFIB_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }

#if(TCPIP_COMP_REGISTER_SESSION == VRP_YES)
    {
        extern ULONG DIST_IP_RegApp();
        ulErrCode  = DIST_IP_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rsession component register error");
        }
    }
#endif

    /*IPv6 Initialization (Should before IFNET).*/
#if(TCPIP_COMP_REGISTER_IPV6 == VRP_YES)
    {
        extern ULONG IP6_SOCK6_RegApp();
        ulErrCode = IP6_SOCK6_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }

    {
        extern ULONG SFIB6_RegApp();
        ulErrCode = SFIB6_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }

    {   /* IPv6 Potocol Processing Manager */
        extern ULONG IPv6_PPMNG_RegApp();
        ulErrCode = IPv6_PPMNG_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }

    {   /* IPv6 ND */
        extern ULONG IPv6_ND_RegApp();
        ulErrCode = IPv6_ND_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }

    {   /* IPv6 Addr */
        extern ULONG IPv6_Addr_RegApp();
        ulErrCode = IPv6_Addr_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }

    {   /* ICMPv6 */
        extern ULONG IPv6_ICMP6_RegApp();
        ulErrCode = IPv6_ICMP6_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }


    {   /* IPv6 PMTU */
        extern ULONG IPv6_PMTU_RegApp();
        ulErrCode = IPv6_PMTU_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }

    {   /* UDP6 */
        extern ULONG IPv6_UDP6_RegApp();
        ulErrCode = IPv6_UDP6_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }

    {   /* Rawip6 */
        extern ULONG IPv6_RAWIP6_RegApp();
        ulErrCode = IPv6_RAWIP6_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }

    {   /* TCP6 */
        extern ULONG IPv6_TCP6_RegApp();
        ulErrCode = IPv6_TCP6_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }

    /* ע��DHCP6C��� */
#if (TCPIP_COMP_REGISTER_DHCP6C == VRP_YES)
    {
        extern ULONG DHCP6C_RegApp(VOID);

        ulErrCode = DHCP6C_RegApp();
        if (VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error for DHCP6C");
        }
    }
#endif

    /* ע��DHCP6R��� */
#if (TCPIP_COMP_REGISTER_DHCP6R == VRP_YES)
    {
        extern ULONG DHCP6R_RegApp(VOID);

        ulErrCode = DHCP6R_RegApp();
        if (VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error for DHCP6R");
        }
    }
#endif

#endif /*TCPIP_COMP_REGISTER_IPV6*/

    {
        extern ULONG IP4_SOCK4_RegApp();
        ulErrCode = IP4_SOCK4_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }

#if (TCPIP_COMP_REGISTER_TCP4 == VRP_YES)
    {
        extern ULONG IP4_TCP4_SH_RegApp();
        ulErrCode = IP4_TCP4_SH_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }
#endif

    {
        extern ULONG IP4_RIP4_RegApp();
        ulErrCode = IP4_RIP4_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }

#if (TCPIP_COMP_REGISTER_UDP4 == VRP_YES)
    {
        extern ULONG IP4_UDP4_RegApp();
        ulErrCode = IP4_UDP4_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }
#endif

    {
        extern ULONG IP_ICMP_RegApp();
        ulErrCode = IP_ICMP_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }

#if (TCPIP_COMP_REGISTER_OAM3AH == VRP_YES)
        {
            extern ULONG OAM_3AH_RegApp();
            ulErrCode = OAM_3AH_RegApp();
            if (VOS_OK != ulErrCode)
            {
                (VOID)vos_printf("\n\rcomponent register error");
            }
        }
#endif

/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
#if(TCPIP_COMP_REGISTER_VRF == VRP_YES)
    {
        extern ULONG VRF_Sh_RegApp();
        ulErrCode = VRF_Sh_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (void)vos_printf("\n\rcomponent register error");
        }
    }
#endif
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

/* Begin:VISP1.7C03 VRF6 */
#if(TCPIP_COMP_REGISTER_VRF6 == VRP_YES)
    {
        extern ULONG VRF6_Sh_RegApp();
        ulErrCode = VRF6_Sh_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (void)vos_printf("\n\rcomponent register error");
        }
    }
#endif
/* End: VISP1.7C03 VRF6 */
    {
        extern ULONG IF_Sh_RegApp();
        ulErrCode = IF_Sh_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }

#if(TCPIP_COMP_REGISTER_PING == VRP_YES)
    {
        extern ULONG PING_RegApp();
        ulErrCode = PING_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }
#endif

#if(TCPIP_COMP_REGISTER_DNSC == VRP_YES)
    {
        extern ULONG DNSC_RegApp();
        ulErrCode = DNSC_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }
#endif

#if(TCPIP_COMP_REGISTER_DHCP4C == VRP_YES)
    {
        extern ULONG DHCP4C_RegApp();
        ulErrCode = DHCP4C_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }
#endif

#if(TCPIP_COMP_REGISTER_ACL4 == VRP_YES)
    {
        extern ULONG ACL_SH_Init();

        ulErrCode = ACL_SH_Init();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rFire wall Initialize Error");
        }
    }
#endif


#if(TCPIP_COMP_REGISTER_ACL6 == VRP_YES)
    {
        extern ULONG ACL6_SH_Init();

        ulErrCode = ACL6_SH_Init();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rACL6 Initialize Error");
        }
    }
#endif



#if(TCPIP_COMP_REGISTER_TRACEROUTE == VRP_YES)
    {
        extern ULONG TRACERT_RegApp();
        ulErrCode = TRACERT_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }
#endif

#if(TCPIP_COMP_REGISTER_IPHC == VRP_YES)
    {
        extern ULONG IPHC_RegApp();
        ulErrCode = IPHC_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }
#endif

#if(TCPIP_COMP_REGISTER_PPPOECLIENT == VRP_YES)
    {
        extern ULONG PPPOE_Client_RegApp();
        ulErrCode = PPPOE_Client_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }
#endif

#if(TCPIP_COMP_REGISTER_MP == VRP_YES)
    {
        extern ULONG MP_RegApp();
        ulErrCode = MP_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }
#endif

    /* ע��PPPMUX��� */
#if (TCPIP_COMP_REGISTER_PPPMUX == VRP_YES)
    {
        extern ULONG PPPMUX_RegApp();
        ulErrCode = PPPMUX_RegApp();
        if (VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }
#endif

    /*ע��NSR�������*/
#if (TCPIP_COMP_REGISTER_NSR == VRP_YES)
    {
        extern ULONG NSR_RegApp();
        ulErrCode = NSR_RegApp();
        if (VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rNSR component register error");
        }
    }
#endif

    /* ע��TRUNK��� */
#if (TCPIP_COMP_REGISTER_TRUNK == VRP_YES)
    {
        extern ULONG TRUNK_RegApp();
        ulErrCode = TRUNK_RegApp();
        if (VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }
#endif

    /* ע��DHCP4 Relay��� */
#if(TCPIP_COMP_REGISTER_DHCP4R == VRP_YES)
    {
        extern ULONG DHCP4R_RegApp();
        ulErrCode = DHCP4R_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rDHCP4R register error");
        }
    }
#endif

    /* ע��PPPoE Server��� */
#if (TCPIP_COMP_REGISTER_POES == VRP_YES)
    {
        extern ULONG POES_RegApp();
        ulErrCode = POES_RegApp();
        if (VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }
#endif

    /* ע��IPSec��� */
#if (TCPIP_COMP_REGISTER_IPSEC == VRP_YES)
    {
        extern ULONG IPSEC_RegApp();
        ulErrCode = IPSEC_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error for IPSEC");
        }

    }
#endif

    /* ע��IKEv1��� */
#if (TCPIP_COMP_REGISTER_IKEV1 == VRP_YES)
    {
        extern ULONG IKEV1_SH_RegApp();

        /*B107-Merging-IKELIB*/
        extern VOID IKEv1_GetAppInfo(struct tagAPP_INIT_INFO * pstIKEv1AppInfo);
        extern VOID (*pfIKEv1_GetAppInfo)(struct tagAPP_INIT_INFO *pstIKEv1AppInfo);

        /*Get the IKEv1 application information from Core through this function
            pointer*/
        pfIKEv1_GetAppInfo = IKEv1_GetAppInfo;

        ulErrCode = IKEV1_SH_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error for IKEV1");
        }

    }
#endif

    /* ע��IKEv2��� */
#if (TCPIP_COMP_REGISTER_IKEV2 == VRP_YES)
    {
        extern ULONG IKEV2_SH_RegApp();

        /*B107-Merging-IKELIB*/
        extern VOID IKEv2_GetAppInfo(struct tagAPP_INIT_INFO * pstIKEv2AppInfo);
        extern VOID (*pfIKEv2_GetAppInfo)(struct tagAPP_INIT_INFO *pstIKEv2AppInfo);

        pfIKEv2_GetAppInfo = IKEv2_GetAppInfo;

        ulErrCode = IKEV2_SH_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error for IKEV2");
        }

    }
#endif

#if (TCPIP_COMP_REGISTER_OSICP == VRP_YES)
    {
        extern ULONG OSICP_RegApp();
        ulErrCode = OSICP_RegApp();
        if (VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }
#endif

#if (TCPIP_COMP_REGISTER_OAM1AG == VRP_YES)
    {
        extern ULONG OAM_1AG_RegApp();
        ulErrCode = OAM_1AG_RegApp();
        if (VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }
#endif

#if (TCPIP_COMP_REGISTER_IGMP == VRP_YES)
    {
        extern ULONG IGMP_RegApp();
        ulErrCode = IGMP_RegApp();
        if (VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }
#endif

/* IPOA Init should after am4 */
#if(TCPIP_COMP_REGISTER_IPOA == VRP_YES)
            {
                extern VOID IPoA_Init( VOID );
                (VOID)IPoA_Init();
            }
#endif

#if(TCPIP_COMP_REGISTER_VLAN == VRP_YES)
            {
                extern ULONG ETHVLAN_SH_Init();
                ulErrCode = ETHVLAN_SH_Init();
                if(VOS_OK != ulErrCode)
                {
                    (VOID)vos_printf("\n\rVlan init error");
                }
            }
#endif

/*����DCLBASE */
#if(TCPIP_COMP_REGISTER_DCLBASE == VRP_YES)
                {
                    extern ULONG dclbase_init();
                    ulErrCode = dclbase_init();
                    if(VOS_OK != ulErrCode)
                    {
                        (VOID)vos_printf("\n\rDCLBase init error");
                    }
                }

/*����RIP */
#if(TCPIP_COMP_REGISTER_RIP == VRP_YES)
                {
                    extern ULONG RIP_Global_Init();
                    ulErrCode = RIP_Global_Init();
                    if(VOS_OK != ulErrCode)
                    {
                        (VOID)vos_printf("\n\rRIP init error");
                    }
                }
#endif
/*����OSPF */
#if(TCPIP_COMP_REGISTER_OSPF == VRP_YES)
                {
                    extern ULONG ospf_vrpadp_init();
                    ulErrCode = ospf_vrpadp_init();
                    if(VOS_OK != ulErrCode)
                    {
                        (VOID)vos_printf("\n\rOSPF init error");
                    }
                }

/*OSPF NSR����NSR�����Ƿ񱻲ü������NSR���ü���OSPF NSRҲ����Ч*/
#if (TCPIP_COMP_REGISTER_NSR == VRP_YES)
  {
      extern VOID NSR_OSPF_Adapt_Init();
      NSR_OSPF_Adapt_Init();
  }
#endif

#endif

#endif

#if(TCPIP_COMP_REGISTER_VLINK == VRP_YES)
                {
                    extern VOID VLINK_Module_Init();
                    VLINK_Module_Init();
                }
#endif

#if (TCPIP_COMP_REGISTER_L2IF == VRP_YES)
    {
        extern ULONG L2IF_RegApp();
        ulErrCode = L2IF_RegApp();
        if (VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rl2if component register error");
        }
    }
#endif

#if (TCPIP_COMP_REGISTER_VRRP == VRP_YES)
    {
        extern ULONG VRRP_RegApp();
        ulErrCode = VRRP_RegApp();
        if (VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rVRRP component register error");
        }
#if (TCPIP_COMP_REGISTER_BFD == VRP_YES)
        /* ���Ҫ֧�ֻ���BFD�ļ�������,Ҫ��VRRPģ������ע�������BFD�ĳ�ʼ��֮ǰ��� */
        {
            extern VRRP_GETBFDSESSIONSTATE g_pfVrrpTrackBfdGetSessionState;
            extern ULONG BFD_GetSessionState(ULONG ulSessionID, ULONG ulVrfIndex, ULONG *pstState);

            g_pfVrrpTrackBfdGetSessionState = BFD_GetSessionState;
        }
#endif
    }
#endif

#if (TCPIP_COMP_REGISTER_SYNCE == VRP_YES)
        {
            extern ULONG SyncE_RegApp();
            ulErrCode = SyncE_RegApp();
            if (VOS_OK != ulErrCode)
            {
                (VOID)vos_printf("\n\SyncE component register error");
            }
        }
#endif

#if(TCPIP_COMP_REGISTER_POLICYRT == VRP_YES)
    {    /* CHANDRA */
        extern ULONG PolicyRt_Sh_RegApp();

        ulErrCode = PolicyRt_Sh_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rPolicyRt component register Error");
        }
    }
#endif


#if (TCPIP_COMP_REGISTER_ATK == VRP_YES)
    {
        extern ULONG ATK_RegApp(VOID);
        ulErrCode = ATK_RegApp();
        if (VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\Atk component register error");
        }
    }
#endif
    return;
}

/****************************************************************************
*    Func Name: TCPIP_RegAllAppInfo()
* Date Created: 2004-7-7
*       Author: liangjicheng
*  Description: VISP �ɲü�ģ��(�����)��ʼ��
                VISP�ڲ�һЩģ�����������������ע���(TCPIP_RegAllAppInfo)
                ��Entry�����س�ʼ����
                V1R7C02����ģ��û�������������Ȼ֧�ֲü�����Щģ���ʼ������
                ����ĳЩģ��ĳ�ʼ������˽����˽ӿ��������ģ��ļ��ó�ʼ��
*       Output: ��
*       Return: ��
*       Call  : VISP_InitTCPIPStack
*      Caution: Call After TCPIP_SystemEntry
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-1-14  liangjicheng      Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_InitNonComponentModule()
{
    ULONG ulRet = VOS_OK;

        /* BFD���Գ�ʼ��,�����û���Ҫ�����Ƿ�֧��NP���벻ͬ�Ĳ���
         * 0-��֧��NP
         * 1-֧����NP:NP������������
         * 2-֧��ȫNP:NP����NP����
         */
#if (TCPIP_COMP_REGISTER_BFD == VRP_YES)
    {
        extern ULONG BFD_Shell_Init(ULONG ulNpMode);
        /* ���֧��NP�Ļ�,��Ҫ�ڵ��ó�ʼ������֮�����֮��ע��NP֪ͨ����
         * (���ú���BFD_PPI_HookRegisterע��)
         * ���ܷ��ڽ�Զ�ط�,���������ڳ�ʼ��֮��ܾý����Ự��ʱ������ע��
         * Υ�ߺ���Ը� */
        ulRet = BFD_Shell_Init(0);
        if (VOS_OK != ulRet)
        {
            (VOID)vos_printf("\n\rBfd Init Error");
        }

#if (TCPIP_COMP_REGISTER_TRUNK == VRP_YES)
        {
            extern ULONG (*g_pfTrunkPortChangeNotifyBfd)(ULONG, ULONG);
            extern ULONG BFD_TrunkPortEventNotify(ULONG ulPortEvent, ULONG ulPortIfIndex);

            g_pfTrunkPortChangeNotifyBfd = BFD_TrunkPortEventNotify;
        }
#endif
#if (TCPIP_COMP_REGISTER_BFDEXT == VRP_YES)
        {
            extern ULONG Extern_BFD_Shell_Init(VOID);
            ulRet = Extern_BFD_Shell_Init();
            if (VOS_OK != ulRet)
            {
                (VOID)vos_printf("\n\rBfd EXT Init Error");
            }
        }
#endif
    }
#endif

#if((TCPIP_COMP_REGISTER_ACL4 == VRP_YES)\
        && (TCPIP_COMP_REGISTER_ACLFW == VRP_YES))
    {
        extern ULONG ACLFW_Init(ULONG ulRegPri);
        ulRet = ACLFW_Init(3);

        if (ulRet != VOS_OK)
        {
            (VOID)vos_printf("\n\r ACLFW Init Error(%#x)", ulRet);
            return ulRet;
        }
    }
#endif

/* mstp��shell��ʼ�������ڶ������ģ��,����Ҫ�������VISP TCPIP_SystemEntry��ʼ��֮����� */
#if (TCPIP_COMP_REGISTER_MSTP == VRP_YES)
    {
        extern ULONG MSTP_Shell_Init();
        ulRet = MSTP_Shell_Init();
        if (VOS_OK != ulRet)
        {
            (VOID)vos_printf("\n\rMSTP Init Error(%#x)", ulRet);
            return ulRet;
        }
    }
#endif

/* EAPģ���ʼ��, ������IFNETģ���ʼ��֮�� */
#if (TCPIP_COMP_REGISTER_EAP == VRP_YES)
    {
        extern LONG IPSI_EAP_shellInit();
        ulRet = IPSI_EAP_shellInit();
        if (VOS_OK != ulRet)
        {
            (VOID)vos_printf("\n\rEAP Init Error(%#x)", ulRet);
            return ulRet;
        }
    }
#endif

#if(TCPIP_COMP_REGISTER_ETH == VRP_YES)
    {
#if(TCPIP_COMP_REGISTER_ARPGUARD == VRP_YES)
        {
            extern ULONG ARP_Guard_Init();
            ulRet = ARP_Guard_Init();
            if(VOS_OK != ulRet)
            {
                (VOID)vos_printf("\n\rcomponent register error");
                return ulRet;
            }
        }
#endif
    }
#endif

#if (TCPIP_COMP_REGISTER_LLDP == VRP_YES)
    {
        extern ULONG LLDP_Shell_Init(VOID);
        ulRet = LLDP_Shell_Init();
        if (VOS_OK != ulRet)
        {
            (VOID)vos_printf("\n\rLLDP Init Error");
            return ulRet;
        }
    }
#endif

    return ulRet;
}

/****************************************************************************
*    Func Name: TCPIP_GetMaxSockNum()
* Date Created: 2004-7-7
*       Author: zhany hong yan(19316)
*  Description: ��ȡ��Ʒ���õ����Socket��
*       Output: ��
*       Return: ���õ����Socket��
*      Caution: ��Ʒ�����޸Ĵ˺�����
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2004-7-7  zhany hong yan(19316)         Creat the first version.
*  2006-6-16 X36317                        �޸Ķ��û����õ�VRP_FD_SETSIZE�Ϸ��Լ��.
*
*******************************************************************************/
ULONG TCPIP_GetMaxSockNum()
{
    ULONG ulValue = VRP_FD_SETSIZE;
    /*����û����õ�VRP_FD_SETSIZEֵ����32������������ȡĬ��ֵ32*/
    if ((ulValue & 0x0000001f) || (ulValue > VRP_FD_SETSIZE))
    {
        ulValue = 32; /*ע:#define EXPANDNUM 32*/
    }
    return ulValue;
}

/****************************************************************************
*    Func Name: VISP_InitTCPIPStack()
* Date Created: 2004-7-7
*       Author: zhany hong yan(19316)
*  Description: VISPЭ��ջ��ʼ������
*       Output: ��
*       Return: VOS_ERR:ʧ��
*               0:�ɹ�
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2004-7-7  zhany hong yan(19316)         Creat the first version.
*  2008-10-31  liangjicheng                 �޸�����˵��
*
*******************************************************************************/
ULONG VISP_InitTCPIPStack()
{
    (VOID)vos_printf("\r\nDOPRA IP Version: %s", DOPRA_VISP_VERSION);
    (VOID)vos_printf("\r\nDOPRA IP HA Tag: %s", TCPIP_HA_VERSION);
    /***********************************************************************************
    Step1��
    ���ݲ�Ʒ��Ҫ���޸��ļ�����������ü����ú꣬
    ����Ҫ�ü�ĳ�����ֻҪ����Ӧ�ĺ궨������ΪVRP_NO��
    ��ο�<VRPV500R002 VISP������ĿЭ��ջ��ά���ɲü�����Ӧ��ָ����.doc>
    ************************************************************************************/

    /***********************************************************************************
    Step2��
    ���ݲ�Ʒ��Ҫ��ע�����ģ���Hook������
    ************************************************************************************/


    /***********************************************************************************
    Step2��
    ���ݲ�Ʒ��Ҫ������VISPԤ���ò��� ���������������Ĭ��ֵ��
    ����˵����ο�<VRPV500R002 VISP������Ŀ����Ԥ����ָ����.doc>
    ************************************************************************************/
    /*TCPIP_Set_PreConfigPara(SFIB4_CFG_ROUTE_BALANCE, xxx);*/   /*����ƽ��·��ģʽ*/
    /*TCPIP_Set_PreConfigPara(TCP4_CFG_NEED_CACHE, xxx);    */   /*����TCP�Ƿ񻺴���һ���ͳ��ӿ���Ϣ*/
    /*TCPIP_Set_PreConfigPara(SKT_TASK_SOCK_PRIO, xxx);     */   /*����VISP SockRun�������ȼ�*/
    /*TCPIP_Set_PreConfigPara(xxx, xxx);                    */   /*����*/
    (VOID)TCPIP_Set_PreConfigPara(SKT_TASK_SOCK_PRIO, 175);   /*����VISP SockRun�������ȼ���SYSPRI��ͬ,Ϊ175*/

    (VOID)TCPIP_Set_PreConfigPara(PTP_IPV6_ENABLE, 1);
    (VOID)TCPIP_Set_PreConfigPara(SYNCE_DEFAULT_QL, 8); /*Ĭ��ֵSSU-B*/

    /*ȡ��NSR���Ԥ���ú�,��������ʱ����*/
    
    /***********************************************************************************
    Step3��
    ����VISPЭ��ջ��
    ***********************************************************************************/
    if (TCPIP_SystemEntry() != VOS_OK)
    {
        return VOS_ERR;
    }

    /*��ʼ��һЩ�ɼ��õķ����ģ��-After System Init*/
    if (TCPIP_InitNonComponentModule() != VOS_OK)
    {
        return VOS_ERR;
    }

    if (TCPIP_HDR_Init(0,0) != VOS_OK)
    {
        (VOID)vos_printf("init the health failed!!");
        return VOS_ERR;
    }

        /* PTPЭ���ʼ��ʱ������socket������VISP��ģ���ʼ���ɹ� */
#if (TCPIP_COMP_REGISTER_PTP == VRP_YES)
    {
        ULONG ulErrCode;
        extern ULONG PTP_Shell_Init(ULONG ulFlag);

        ulErrCode = PTP_Shell_Init(1); /*����event��Ϣsocket*/
        if (VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\r\nComponent(PTP) register error: %u",ulErrCode);
            return VOS_ERR;
        }
    }
#endif

    /***********************************************************************************
    �������������VISPЭ��ջ�ĳ�ʼ��(�����������ؽӿ�)��
    ETH/PPP�ӿ����Ʒ����Ҫʱ��̬������
    ***********************************************************************************/
    return 0;
}

/*******************************************************************************
*    Func Name: TCPIP_ProductLock
* Date Created: 2009-2-20
*       Author: luoagaowei
*  Description: ��Ʒ����ʵ�ֵ��� For SGSN Only
*        Input: VOID
*       Output:
*       Return: VOID
*      Caution: Important points if any
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-2-20  luoagaowei         Creat the first version.
*
*******************************************************************************/
VOID TCPIP_ProductLock(VOID)
{
    return;
}

/*******************************************************************************
*    Func Name: TCPIP_ProductUnLock
* Date Created: 2009-2-20
*       Author: luoagaowei
*  Description: ��Ʒ����ʵ�ֵ��� For SGSN Only
*        Input: VOID
*       Output:
*       Return: VOID
*      Caution: Important points if any
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-2-20  luoagaowei         Creat the first version.
*
*******************************************************************************/
VOID TCPIP_ProductUnLock(VOID)
{
    return;
}

/***************************************************************************************
*
* ����������ǲ�Ʒ��������ģ�
*
* ��Ʒ�ھ���Ӧ��VISPʱ����������Ӧ�����亯���������������ӣ�лл��
*
****************************************************************************************/

#ifdef  __cplusplus
}
#endif
