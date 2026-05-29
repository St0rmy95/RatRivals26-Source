// INFGameMainUnitInfoBar.cpp: implementation of the CINFGameMainUnitInfoBar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "INFGameMainUnitInfoBar.h"
#include "INFGameMainMiniMap.h" 			// 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������
#include "AtumApplication.h"
#include "INFImage.h"
#include "GameDataLast.h"
#include "ShuttleChild.h"
#include "CharacterChild.h"				// 2005-07-21 by ispark
#include "ClientParty.h"				// 2012-10-17 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������
#include "SceneData.h"
#include "D3DHanFont.h"
#include "Background.h"
#include "AtumDatabase.h"
#include "dxutil.h"
#include "PkNormalTimer.h"
#include "QuestData.h"
#include "INFGameMain.h"
#include "INFWindow.h"
#include "INFWeaponInfo.h"
#include "INFGameMainChat.h"
#include "INFGroupManager.h"		// 2011. 10. 10 by jskim UI�ý��� ����
#include "INFGroupImage.h"		// 2011. 10. 10 by jskim UI�ý��� ����
#include "INFGameMainWisperChat.h"	// 2014-12-09 by jwLee �ý��� �޼���â Ȱ��ȭ ���¿��� ���콺 ������ �ڿ��ִ� �������̽� �̺�Ʈ �߻� ���ϵ��� ����

#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	#define GAMEMAIN_GAGE_EXP_LENGTH					219//110// ����

	#define GAMEMAIN_BACK_GAGE_UP_SIZE_X				179
	#define GAMEMAIN_BACK_GAGE_UP_SIZE_Y				48

	#define GAMEMAIN_BACK_MINIMAP_SIZE_X				145
	#define GAMEMAIN_BACK_MINIMAP_SIZE_Y				69
	#define GAMEMAIN_BACK_MINIMAP_START_X				(g_pD3dApp->GetBackBufferDesc().Width - GAMEMAIN_BACK_MINIMAP_SIZE_X)
	#define GAMEMAIN_BACK_MINIMAP_START_Y				0

	#define GAMEMAIN_BACK_UP_SIZE_Y						22	// ȭ�� ���
	//#define GAMEMAIN_BACK_DOWN_SIZE_Y					39	// ȭ�� �ϴ�
	#define GAMEMAIN_BACK_DOWN_START_Y					(g_pD3dApp->GetBackBufferDesc().Height - GAMEMAIN_BACK_DOWN_SIZE_Y)

	#define GAMEMAIN_EXP_GAGE_START_X					((g_pD3dApp->GetBackBufferDesc().Width - 219)/2)
	#define GAMEMAIN_EXP_GAGE_START_Y					(GAMEMAIN_BACK_DOWN_START_Y - 9)

	#define GAMEMAIN_UNIT_POS_START_X					(g_pD3dApp->GetBackBufferDesc().Width - 30)
	#define GAMEMAIN_UNIT_POS_START_Y					5

	//#define GAMEMAIN_BACK_GAGE_EXP_START_X				((g_pD3dApp->GetBackBufferDesc().Width - 234)/2)
	#define GAMEMAIN_BACK_GAGE_EXP_START_Y				(g_pD3dApp->GetBackBufferDesc().Height - m_pImgMainExpBack->GetImgSize().y)		// 2011. 10. 10 by jskim UI�ý��� ����

	#define GAMEMAIN_STRING_FUEL_START_X				163*HIDPI_COEFF

	#define GAMEMAIN_STRING_EXP_START_X					g_pD3dApp->GetBackBufferDesc().Width / 2

	// ��Ʈ�� ��ġ ����
	#define GAMEMAIN_NEW_STRING_HP_START_X				17*HIDPI_COEFF
	#define GAMEMAIN_NEW_STRING_HP_START_Y				80*HIDPI_COEFF
	#define GAMEMAIN_GAGE_HP_UP_START_X					28*HIDPI_COEFF
	#define GAMEMAIN_GAGE_HP_UP_START_Y					90 *HIDPI_COEFF
	#define GAMEMAIN_NEW_STRING_MAX_HP_START_Y			104*HIDPI_COEFF
	#define GAMEMAIN_NEW_STRING_DP_START_Y				80*HIDPI_COEFF
	#define GAMEMAIN_GAGE_DP_UP_START_X					133*HIDPI_COEFF
	#define GAMEMAIN_GAGE_DP_UP_START_Y					90*HIDPI_COEFF
	#define GAMEMAIN_NEW_STRING_MAX_DP_START_X			108*HIDPI_COEFF
	#define GAMEMAIN_NEW_STRING_MAX_DP_START_Y			104*HIDPI_COEFF
	#define GAMEMAIN_GAGE_SP_UP_START_X					130*HIDPI_COEFF
	#define GAMEMAIN_GAGE_SP_UP_START_Y					50*HIDPI_COEFF
	#define GAMEMAIN_NEW_STRING_MAX_SP_START_Y			70*HIDPI_COEFF


	// ���� ������ ���� ����
/* Unused
	#define GAMEMAIN_GAGE_HP_START_X					15
	#define GAMEMAIN_GAGE_HP_START_Y					29
	#define GAMEMAIN_GAGE_DP_START_X					83
	#define GAMEMAIN_GAGE_DP_START_Y					33
	#define GAMEMAIN_GAGE_SP_START_X					120
	#define GAMEMAIN_GAGE_SP_START_Y					22
	#define GAMEMAIN_GAGE_BOOSTER_START_X				9
	#define GAMEMAIN_GAGE_BOOSTER_START_Y				25
	#define GAMEMAIN_GAGE_FUEL_START_X					6
	#define GAMEMAIN_GAGE_FUEL_START_Y					5
*/
	#define GAMEMAIN_VOICECHAT_X						(g_pD3dApp->GetBackBufferDesc().Width-32)
	#define GAMEMAIN_VOICECHAT_Y						(156)
	#define GAMEMAIN_VOICECHAT_W						26
	#define GAMEMAIN_VOICECHAT_H						26


	// SPEED ��Ʈ�� ���� ����
	#define SPEED_STRING_START_X						80*HIDPI_COEFF
	#define SPEED_STRING_START_Y						105*HIDPI_COEFF
	#define SPEED_STRING_WIDTH							19
	#define SPEED_STRING_HEIGHT							17

	// ���̸� ���� ����
	#define GAME_MAP_NAME_RENDER_X						(g_pD3dApp->GetBackBufferDesc().Width-30)
	#define GAME_MAP_NAME_RENDER_Y						4
	#define GAME_MAP_NAME_TEXT_COLOR					RGB(200,200,200)
	#define GAME_UNIT_POS_COLOR							RGB(200,200,200)

	// ���̴� ��ġ ����
	#define RADER_CENTER_POS_X							(g_pD3dApp->GetBackBufferDesc().Width-75)	
	#define RADER_CENTER_POS_Y							82 + 16
	#define RADER_RADIUS								64

	#define GAME_EVENT_BASICPOS_X						242
	#define GAME_EVENT_BASICPOS_Y						32

	// 2006-03-07 by ispark, �� ���� ��ġ ����
	#if defined(LANGUAGE_ENGLISH) || defined(LANGUAGE_VIETNAM)|| defined(LANGUAGE_THAI)// 2008-04-30 by bhsohn �±� ���� �߰�
		#define GAMEMAIN_STRING_FUEL_START_Y				72*HIDPI_COEFF//
		#define GAMEMAIN_STRING_EXP_START_Y					g_pD3dApp->GetBackBufferDesc().Height - 14*HIDPI_COEFF//11)
		#define GAMEMAIN_NEW_STRING_MAX_HP_START_X			25*HIDPI_COEFF//21
		#define GAMEMAIN_NEW_STRING_DP_START_X				112//114
		#define GAMEMAIN_NEW_STRING_MAX_SP_START_X			80*HIDPI_COEFF//130
		#define GAMEMAIN_EVENT_FONT_Y						2
	#else
		#define GAMEMAIN_STRING_FUEL_START_Y				72
		#define GAMEMAIN_STRING_EXP_START_Y					g_pD3dApp->GetBackBufferDesc().Height - 12//11)
		#define GAMEMAIN_NEW_STRING_MAX_HP_START_X			25//21
		#define GAMEMAIN_NEW_STRING_DP_START_X				112//114
		#define GAMEMAIN_NEW_STRING_MAX_SP_START_X			80//130
		#define GAMEMAIN_EVENT_FONT_Y						2//0
	#endif


	#define INFOMAIN_GIFT_ICON_X				75		// 2012-08-14 by mspark, ����Ʈ ������ ��ġ ���� - ���� 70���� 75�� ����
	#define INFOMAIN_GIFT_CITY_ICON_Y			130
	#define INFOMAIN_GIFT_FIELD_ICON_Y			176		// 2012-08-14 by mspark, ����Ʈ ������ ��ġ ���� - ���� 89���� 176���� ����

	// 2008-03-25 by dgwoo ���� ���� ��ư.
	#define MOTHERSHIP_BUTTON_X					(nBoldPosX+nBalonWidth)
	#define MOTHERSHIP_BUTTON_Y					(nBoldPosY)
															 
#else
#define GAMEMAIN_GAGE_EXP_LENGTH					219//110// ����

#define GAMEMAIN_BACK_GAGE_UP_SIZE_X				179
#define GAMEMAIN_BACK_GAGE_UP_SIZE_Y				48

#define GAMEMAIN_BACK_MINIMAP_SIZE_X				145
#define GAMEMAIN_BACK_MINIMAP_SIZE_Y				69
#define GAMEMAIN_BACK_MINIMAP_START_X				(g_pD3dApp->GetBackBufferDesc().Width - GAMEMAIN_BACK_MINIMAP_SIZE_X)
#define GAMEMAIN_BACK_MINIMAP_START_Y				0

#define GAMEMAIN_BACK_UP_SIZE_Y						22	// ȭ�� ���
#define GAMEMAIN_BACK_DOWN_SIZE_Y					39	// ȭ�� �ϴ�
#define GAMEMAIN_BACK_DOWN_START_Y					(g_pD3dApp->GetBackBufferDesc().Height - GAMEMAIN_BACK_DOWN_SIZE_Y)

#define GAMEMAIN_EXP_GAGE_START_X					((g_pD3dApp->GetBackBufferDesc().Width - 219)/2)
#define GAMEMAIN_EXP_GAGE_START_Y					(GAMEMAIN_BACK_DOWN_START_Y - 9)

#define GAMEMAIN_UNIT_POS_START_X					(g_pD3dApp->GetBackBufferDesc().Width - 30)
#define GAMEMAIN_UNIT_POS_START_Y					5

#define GAMEMAIN_BACK_GAGE_EXP_START_X				((g_pD3dApp->GetBackBufferDesc().Width - 234)/2)
#define GAMEMAIN_BACK_GAGE_EXP_START_Y				(GAMEMAIN_BACK_DOWN_START_Y - 12)

#define GAMEMAIN_STRING_FUEL_START_X				22

#define GAMEMAIN_STRING_EXP_START_X					((g_pD3dApp->GetBackBufferDesc().Width)/2 - 35)

// ��Ʈ�� ��ġ ����
#define GAMEMAIN_NEW_STRING_HP_START_X				17
#define GAMEMAIN_NEW_STRING_HP_START_Y				80
#define GAMEMAIN_GAGE_HP_UP_START_X					21
#define GAMEMAIN_GAGE_HP_UP_START_Y					92
#define GAMEMAIN_NEW_STRING_MAX_HP_START_Y			104
#define GAMEMAIN_NEW_STRING_DP_START_Y				80
#define GAMEMAIN_GAGE_DP_UP_START_X					114
#define GAMEMAIN_GAGE_DP_UP_START_Y					92
#define GAMEMAIN_NEW_STRING_MAX_DP_START_X			108
#define GAMEMAIN_NEW_STRING_MAX_DP_START_Y			104
#define GAMEMAIN_GAGE_SP_UP_START_X					130
#define GAMEMAIN_GAGE_SP_UP_START_Y					50
#define GAMEMAIN_NEW_STRING_MAX_SP_START_Y			62


// ���� ������ ���� ����

#define GAMEMAIN_GAGE_HP_START_X					15
#define GAMEMAIN_GAGE_HP_START_Y					29
#define GAMEMAIN_GAGE_DP_START_X					83
#define GAMEMAIN_GAGE_DP_START_Y					29
#define GAMEMAIN_GAGE_SP_START_X					120
#define GAMEMAIN_GAGE_SP_START_Y					22
#define GAMEMAIN_GAGE_BOOSTER_START_X				9
#define GAMEMAIN_GAGE_BOOSTER_START_Y				21
#define GAMEMAIN_GAGE_FUEL_START_X					6
#define GAMEMAIN_GAGE_FUEL_START_Y					5
#define GAMEMAIN_VOICECHAT_X						(g_pD3dApp->GetBackBufferDesc().Width-32)
#define GAMEMAIN_VOICECHAT_Y						(156)
#define GAMEMAIN_VOICECHAT_W						26
#define GAMEMAIN_VOICECHAT_H						26


// SPEED ��Ʈ�� ���� ����
#define SPEED_STRING_START_X						80	
#define SPEED_STRING_START_Y						90
#define SPEED_STRING_WIDTH							19
#define SPEED_STRING_HEIGHT							17

// ���̸� ���� ����
#define GAME_MAP_NAME_RENDER_X						(g_pD3dApp->GetBackBufferDesc().Width-30)
#define GAME_MAP_NAME_RENDER_Y						4
#define GAME_MAP_NAME_TEXT_COLOR					RGB(200,200,200)
#define GAME_UNIT_POS_COLOR							RGB(200,200,200)

// ���̴� ��ġ ����
#define RADER_CENTER_POS_X							(g_pD3dApp->GetBackBufferDesc().Width-75)	
#define RADER_CENTER_POS_Y							82 + 16
#define RADER_RADIUS								64

#define GAME_EVENT_BASICPOS_X						192
#define GAME_EVENT_BASICPOS_Y						32

// 2006-03-07 by ispark, �� ���� ��ġ ����
#if defined(LANGUAGE_ENGLISH) || defined(LANGUAGE_VIETNAM)|| defined(LANGUAGE_THAI)// 2008-04-30 by bhsohn �±� ���� �߰�
#define GAMEMAIN_STRING_FUEL_START_Y				3//5
#define GAMEMAIN_STRING_EXP_START_Y					(GAMEMAIN_BACK_DOWN_START_Y - 13)//11)
#define GAMEMAIN_NEW_STRING_MAX_HP_START_X			25//21
#define GAMEMAIN_NEW_STRING_DP_START_X				112//114
#define GAMEMAIN_NEW_STRING_MAX_SP_START_X			135//130
#define GAMEMAIN_EVENT_FONT_Y						2
#else
#define GAMEMAIN_STRING_FUEL_START_Y				3//5
#define GAMEMAIN_STRING_EXP_START_Y					(GAMEMAIN_BACK_DOWN_START_Y - 13)//11)
#define GAMEMAIN_NEW_STRING_MAX_HP_START_X			25//21
#define GAMEMAIN_NEW_STRING_DP_START_X				112//114
#define GAMEMAIN_NEW_STRING_MAX_SP_START_X			135//130
#define GAMEMAIN_EVENT_FONT_Y						2//0
#endif


#define INFOMAIN_GIFT_ICON_X				70
#define INFOMAIN_GIFT_CITY_ICON_Y			130
#define INFOMAIN_GIFT_FIELD_ICON_Y			89

// 2008-03-25 by dgwoo ���� ���� ��ư.
#define MOTHERSHIP_BUTTON_X					(nBoldPosX+nBalonWidth)
#define MOTHERSHIP_BUTTON_Y					(nBoldPosY)
#endif

	// 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������
	#define RESTCOUNT_STRING_WIDTH				24
	#define RESTCOUNT_STRING_HEIGHT				22
	
	#define RESTCOUNT_SCALE_DEFAULT				0.8f
	#define RESTCOUNT_SCALE_MAX					1.2f

	#define KILLCOUNT_STRING_WIDTH				24
	#define KILLCOUNT_STRING_HEIGHT				22

	#define KILLCOUNT_SCALE_DEFAULT				0.8f
	#define KILLCOUNT_SCALE_MAX					1.2f
	#define KILLCOUNT_SCALE_DECREASE			0.035f

	#define KILLCOUNT2_STRING_WIDTH				29
	#define KILLCOUNT2_STRING_HEIGHT			32

	#define BONUS_EXP_RATE_POS_X				243
	#define BONUS_EXP_RATE_POS_Y				78

	#define BONUS_EXP_RATE_TEXT_POS_X			233
	#define BONUS_EXP_RATE_TEXT_POS_Y			88
	#define BONUS_EXP_RATE_TEXT_LINE_HEIGHT		22

	#define RESTKILLCOUNT_BASE_POS_X			87			// 2012-11-16 by mspark, ��ī�� ��� ǥ�� ������ - ���� 77���� 87�� ����	
	#define RESTKILLCOUNT_BASE_POS_Y			333	
	#define RESTKILLCOUNT_BASE_HEIGHT_SIZE		10	
	#define RESTKILLCOUNT_MOVE_HAPPYHOUR		34

	#define	RESTCOUNT_MAX_POSNUM				4
	#define	RESTCOUNT_MAX_COUNT					9999
	#define RESTCOUNT_BACK_POS_X				32	
	#define RESTCOUNT_BACK_POS_Y				4	
	#define RESTCOUNT_TEXT_POS_X				13	
	#define RESTCOUNT_TEXT_POS_Y				1	

	#define	KILLCOUNT_MAX_POSNUM				3
	#define	KILLCOUNT_MAX_COUNT					300
	#define	KILLCOUNT_SHOW_HIGHLIGHT_COUNT		290
	#define KILLCOUNT_BACK_POS_X				32	
	#define KILLCOUNT_BACK_POS_Y				4	
	#define KILLCOUNT_TEXT_POS_X				15	
	#define KILLCOUNT_TEXT_POS_Y				1	
	#define KILLCOUNT_TEXT_POS_Y				1	


	#define KILLCOUNT2_EFF_POS_X				55	
	#define KILLCOUNT2_EFF_POS_Y				25	
	#define KILLCOUNT2_TEXT_POS_X				15	
	#define KILLCOUNT2_TEXT_POS_Y				3	
	#define KILLCOUNT2_EFF_MAX_ALPHA			230
	#define KILLCOUNT2_EFF_ALPHA_CREASE			7
	#define KILLCOUNT2_SCALE					1.0f
	#define KILLCOUNT2_EFF_MAX_BLENK_COUNT		6

	#define BONUS_EXP_RATE_POPUP_RECT_LEFT		230
	#define BONUS_EXP_RATE_POPUP_RECT_TOP		78
	#define BONUS_EXP_RATE_POPUP_RECT_RIGHT		130
	#define BONUS_EXP_RATE_POPUP_RECT_BOTTOM	22	
	// 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������

	// 2012-11-16 by mspark, ��ī�� ��� ǥ�� ������
	#define RESTKILLCOUNT_BUTTON_BASE_POS_X			15
	#define RESTKILLCOUNT_BUTTON_BASE_POS_Y			333	
	#define RESTKILLCOUNT_BUTTON_BASE_HEIGHT_SIZE	10

	#define RESTKILLCOUNT_BUTTON_WIDTH			10
	#define RESTKILLCOUNT_BUTTON_HEIGHT			28

	#define	RESTCOUNT_IMAGE_POS_LIMIT			145
	#define	KILLCOUNT_IMAGE_POS_LIMIT			130
	#define	RESTKILLCOUNT_IMAGE_MOVE_VALUE		10
	// end 2012-11-16 by mspark, ��ī�� ��� ǥ�� ������

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CINFGameMainUnitInfoBar::CINFGameMainUnitInfoBar(CAtumNode* pParent)
{
	m_pParent = pParent;
	m_bRestored = FALSE;
	m_bWarning = FALSE;
	m_v2RaderCenter.x = RADER_CENTER_POS_X;
	m_v2RaderCenter.y = RADER_CENTER_POS_Y;
	m_v2MousePt.x = g_pD3dApp->GetBackBufferDesc().Width/2;
	m_v2MousePt.y = g_pD3dApp->GetBackBufferDesc().Height/2;


#ifndef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����// 	
	m_pImgBackPixel[GAMEMAIN_BACK_UP_PIXEL] = NULL;
	m_pImgBackPixel[GAMEMAIN_BACK_DOWN_PIXEL] = NULL;

	m_pImgBackMinimap = NULL;
#endif
	m_pFontUnitPosInfo = NULL;
	m_fWarningTime = 0;

	memset(m_fGageRate, 0x00, sizeof(float)*GAMEMAIN_GAGE_NUMBER);
	memset(m_pFontGageInfo, 0x00, sizeof(DWORD)*GAMEMAIN_GAGE_LINE_NUMBER);
	memset(m_szGageInfo, 0x00, GAMEMAIN_GAGE_LINE_NUMBER*GAMEMAIN_GAGE_LINE_LENGTH);
//	memset(m_pButtonShowHide, 0x00, sizeof(DWORD)*2*BUTTON_STATE_NUMBER);

	m_nButtonState = BUTTON_STATE_NORMAL;

	// 2004-12-08 by jschoi
	m_pImgMainGageBack = NULL;
	m_pImgMainExpBack = NULL;
	m_pImgMainExpBar = NULL;
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	m_pImgMainExpBar1 = NULL;
#endif
	m_pImgMainSpeedNum = NULL;
	m_pImgMainMinus = NULL;
	m_pImgMainWarning = NULL;
	m_pImgGeneralPremiumCard = NULL;

	// 2009. 03. 16 by ckPark ����� ���� �߰�

	m_bPremiumToolTip = FALSE;

	// end 2009. 03. 16 by ckPark ����� ���� �߰�

	m_pImgSuperPremiumCard = NULL;
	m_pImgHappyHourEvent = NULL;
	m_pImgPCHappyHourEvent = NULL;
	// 2010. 06. 08 by jskim Ȩ�����̾� UI �۾�
	m_pImgPCHomePremiumEvent = NULL;
	//end 2010. 06. 08 by jskim Ȩ�����̾� UI �۾�
	m_pImgVoiceChatIcon = NULL;
	int i;
	for(i = 0; i < GAMEMAIN_EVENT_RECOVERY_MAX; i++)
	{
		m_pImgEventRecovery[i] = NULL;
	}
	for( i = 0; i < GIFT_ICON_IMG_COUNT; i++)
	{
		m_pImgGiftIcon[i] = NULL;
	}

	memset(m_pImgMainGageHP,0x00,sizeof(DWORD)*GAMEMAIN_GAGE_HP_MAX_GRADE);
	memset(m_pImgMainGageDP,0x00,sizeof(DWORD)*GAMEMAIN_GAGE_DP_MAX_GRADE);
	memset(m_pImgMainGageSP,0x00,sizeof(DWORD)*GAMEMAIN_GAGE_SP_MAX_GRADE);
	memset(m_pImgMainGageBooster,0x00,sizeof(DWORD)*GAMEMAIN_GAGE_BOOSTER_MAX_GRADE);
	memset(m_pImgMainGageFuel,0x00,sizeof(DWORD)*GAMEMAIN_GAGE_FUEL_MAX_GRADE);
	memset(m_pImgMainIconFuel,0x00,sizeof(DWORD)*2);
	
	m_pFontMapName = NULL;
	m_pFontCurrentEvent = NULL;
	m_pFontEventHappyHour = NULL;
	m_pFontEventRecovery = NULL;
	m_pFontDecaToolTip = NULL;							// 2013-07-15 by ssjung ĳ���� ��ī�� �ູ, ��� ���� ���� ǥ��
	m_bRenderEvent = FALSE;
	m_nHappyHourX = 0;
	m_nHappyHourY = 0;
	m_bRenderEventRecovery = FALSE;
	
	// 2007-11-01 by bhsohn ���� �ƿ�� �̺�Ʈ ó�� ��� ����
	//m_BHappyHourEvent = 0x00;
	m_byHappyHourInfluence = 0x00;
	m_bPcBangHappyHour = FALSE;
	// end 2007-11-01 by bhsohn ���� �ƿ�� �̺�Ʈ ó�� ��� ����

	m_bMemberPCBang = FALSE;	
	// 2010. 06. 08 by jskim Ȩ�����̾� UI �۾�
	m_pMemberPremiumEvent = FALSE;
	//end 2010. 06. 08 by jskim Ȩ�����̾� UI �۾�

	// 2007-11-01 by bhsohn ���� �ƿ�� �̺�Ʈ ó�� ��� ����
	memset(&m_HappyEventInfo, 0x00, sizeof(EVENT_INFO));				//���� ����
	memset(&m_HappyEventAllInfluInfo, 0x00, sizeof(EVENT_INFO));		// ��ü ����
	memset(&m_PCHappyEventInfo, 0x00, sizeof(EVENT_INFO));				// pc�� 
	m_bHappyHourAllInfluence = FALSE;

	m_vecGiftMsg.clear();
	m_fGiftTime = 0.0f;

	// 2008-05-21 by bhsohn ����, ������ ���� �ƿ�� �߰�
	m_bMotherHappyHour = FALSE;
	memset(&m_MotherShipEventInfo, 0x00, sizeof(EVENT_INFO));

	m_bItemHappyHour = FALSE;
	memset(&m_ItemEventInfo, 0x00, sizeof(EVENT_INFO));
	// end 2008-05-21 by bhsohn ����, ������ ���� �ƿ�� �߰�

	// 2008-10-20 by bhsohn VOIP ���� ����
	m_pImgVoiceSPKIcon = NULL;
	
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	m_pGageBarInfo = NULL;
#endif
	
	// 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������
	m_pImgBonusExpRate = NULL;
	m_pImgRestCount = NULL;
	m_pImgKillCount = NULL;
	m_pImgKillCount2 = NULL;
	m_pImgKillEff	 = NULL;
	m_pGroupImgRestCountBack = NULL;
	m_pGroupImgKillCountBack = NULL;


	m_bChangeKillCount = false;
	m_fKillCountScale = KILLCOUNT_SCALE_DEFAULT;
	m_nKillCount = 0;
	m_nRestCount = 0;

	m_bRenderBonusExpRateText = FALSE;
	m_nPartyRate = 0;
	m_nFriendRate = 0;
	m_nGuildRate = 0;
	
	m_bCompleteKillCount = false;
	m_nCompleteKillCountBlank = 0;
	m_nCompleteKillCountAlpha = 0;
	// end 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������

// 2012-11-16 by mspark, ��ī�� ��� ǥ�� ������
#ifdef S_BONUSEXPSYSTEM_RENEWAL
	m_pImgRestCountOnBtn = NULL;
	m_pImgRestCountOffBtn = NULL;
	m_pImgKillCountOnBtn = NULL;
	m_pImgKillCountOffBtn = NULL;

	m_nStateRestCountOnBtn = BUTTON_STATE_NORMAL;
	m_nStateRestCountOffBtn = BUTTON_STATE_NORMAL;
	m_nStateKillCountOnBtn = BUTTON_STATE_NORMAL;
	m_nStateKillCountOffBtn = BUTTON_STATE_NORMAL;

	m_nRestCountPosX = 0;
	m_nRestCountPosY = 0;
	m_nKillCountPosX = 0;
	m_nKillCountPosY = 0;

	m_bCheckRestCountON = true;
	m_bCheckKillCountON = true;

	m_bCheckRestCountBtnClick = false;

	m_fPlusRestCountPosX = 0;
	m_fPlusKillCountPosX = 0;

	// 2013-07-15 by ssjung ĳ���� ��ī�� �ູ, ��� ���� ���� ǥ��
	m_bRestCountToolTip = FALSE;
	m_bKillCountToolTip = FALSE;
	// end 2013-07-15 by ssjung ĳ���� ��ī�� �ູ, ��� ���� ���� ǥ��

#endif
// end 2012-11-16 by mspark, ��ī�� ��� ǥ�� ������
}

CINFGameMainUnitInfoBar::~CINFGameMainUnitInfoBar()
{
#ifndef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	SAFE_DELETE(m_pImgBackPixel[GAMEMAIN_BACK_UP_PIXEL]);
	SAFE_DELETE(m_pImgBackPixel[GAMEMAIN_BACK_DOWN_PIXEL]);

	SAFE_DELETE(m_pImgBackMinimap);
#endif
	SAFE_DELETE(m_pFontUnitPosInfo);

	int i=0;
	for(i=0;i<GAMEMAIN_GAGE_LINE_NUMBER;i++)
	{
		SAFE_DELETE(m_pFontGageInfo[i]);
	}	

//	for(i=0;i<BUTTON_STATE_NUMBER;i++)
//	{
//		SAFE_DELETE(m_pButtonShowHide[0][i]);
//		SAFE_DELETE(m_pButtonShowHide[1][i]);
//	}

	// 2004-12-08 by jschoi
	SAFE_DELETE(m_pImgMainGageBack);
	SAFE_DELETE(m_pImgMainExpBack);
	SAFE_DELETE(m_pImgMainExpBar);
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	SAFE_DELETE(m_pImgMainExpBar1);
#endif
	SAFE_DELETE(m_pImgMainSpeedNum);
	SAFE_DELETE(m_pImgMainMinus);
	SAFE_DELETE(m_pImgMainWarning);
	SAFE_DELETE(m_pImgGeneralPremiumCard);
	SAFE_DELETE(m_pImgSuperPremiumCard);
	SAFE_DELETE(m_pImgHappyHourEvent);
	SAFE_DELETE(m_pImgPCHappyHourEvent);
	// 2010. 06. 08 by jskim Ȩ�����̾� UI �۾�
	SAFE_DELETE(m_pImgPCHomePremiumEvent);
	//end 2010. 06. 08 by jskim Ȩ�����̾� UI �۾�
	SAFE_DELETE(m_pImgVoiceChatIcon);
	for(i = 0; i < GAMEMAIN_EVENT_RECOVERY_MAX; i++)
	{
		SAFE_DELETE(m_pImgEventRecovery[i]);
	}
	for(i = 0; i < GIFT_ICON_IMG_COUNT; i++)
	{
		SAFE_DELETE(m_pImgGiftIcon[i]);
	}
	for(i=0;i<GAMEMAIN_GAGE_HP_MAX_GRADE;i++)
	{
		SAFE_DELETE(m_pImgMainGageHP[i]);
		SAFE_DELETE(m_pImgMainGageDP[i]);
		SAFE_DELETE(m_pImgMainGageSP[i]);
	}
	for(i=0;i<GAMEMAIN_GAGE_BOOSTER_MAX_GRADE;i++)
	{
		SAFE_DELETE(m_pImgMainGageBooster[i]);
	}
	for(i=0;i<GAMEMAIN_GAGE_FUEL_MAX_GRADE;i++)
	{
		SAFE_DELETE(m_pImgMainGageFuel[i]);
	}
	for(i=0;i<2;i++)
	{
		SAFE_DELETE(m_pImgMainIconFuel[i]);
	}

	SAFE_DELETE(m_pFontMapName);
	SAFE_DELETE(m_pFontCurrentEvent);
	SAFE_DELETE(m_pFontEventHappyHour);
	SAFE_DELETE(m_pFontEventRecovery);
	SAFE_DELETE(m_pFontDecaToolTip);						// 2013-07-15 by ssjung ĳ���� ��ī�� �ູ, ��� ���� ���� ǥ��
	m_vecGiftMsg.clear();
					  
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	SAFE_DELETE( m_pGageBarInfo );																  
#endif

	// 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������
	SAFE_DELETE(m_pImgBonusExpRate);
	SAFE_DELETE(m_pImgRestCount);
	SAFE_DELETE(m_pImgKillCount);
	SAFE_DELETE(m_pImgKillCount2);
	SAFE_DELETE(m_pImgKillEff);
	SAFE_DELETE(m_pGroupImgRestCountBack);
	SAFE_DELETE(m_pGroupImgKillCountBack);
	// end 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������

// 2012-11-16 by mspark, ��ī�� ��� ǥ�� ������
#ifdef S_BONUSEXPSYSTEM_RENEWAL
	SAFE_DELETE(m_pImgRestCountOnBtn);
	SAFE_DELETE(m_pImgRestCountOffBtn);
	SAFE_DELETE(m_pImgKillCountOnBtn);
	SAFE_DELETE(m_pImgKillCountOffBtn);
#endif
// end 2012-11-16 by mspark, ��ī�� ��� ǥ�� ������
}

void CINFGameMainUnitInfoBar::UpdateAllGage()
{

	SetHP((float)g_pShuttleChild->m_myShuttleInfo.CurrentHP, (float)g_pShuttleChild->m_myShuttleInfo.HP);
	SetDP((float)g_pShuttleChild->m_myShuttleInfo.CurrentDP, (float)g_pShuttleChild->m_myShuttleInfo.DP);
	SetBURN((float)g_pShuttleChild->m_fCurrentBURN, (float)g_pShuttleChild->m_fBURN);
	SetSP((float)g_pShuttleChild->m_myShuttleInfo.CurrentSP, (float)g_pShuttleChild->m_myShuttleInfo.SP);
	SetEP((float)g_pShuttleChild->m_myShuttleInfo.CurrentEP, (float)g_pShuttleChild->m_myShuttleInfo.EP);
	SetSpeed( g_pShuttleChild->m_fShuttleSpeed, 
			g_pShuttleChild->m_fRealShuttleSpeedMin, 
			g_pShuttleChild->m_fRealShuttleSpeedBoosterOn );
}

void CINFGameMainUnitInfoBar::SetHP(float fCurrent, float fMax)
{
	if(fMax< fCurrent)
		fCurrent = fMax;
	wsprintf(m_szGageInfo[GAMEMAIN_NEW_STRING_HP], STRMSG_C_INTERFACE_0022);//"������"
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	wsprintf(m_szGageInfo[GAMEMAIN_GAGE_HP_UP], "%4d/", (int)fCurrent);
	wsprintf(m_szGageInfo[GAMEMAIN_NEW_STRING_MAX_HP], "%d", (int)fMax);
#else
	wsprintf(m_szGageInfo[GAMEMAIN_GAGE_HP_UP], "%4d", (int)fCurrent);
	wsprintf(m_szGageInfo[GAMEMAIN_NEW_STRING_MAX_HP], "/%d", (int)fMax);
#endif
	m_fGageRate[GAMEMAIN_GAGE_HP_UP] = fCurrent/fMax;
}

void CINFGameMainUnitInfoBar::SetDP(float fCurrent, float fMax)
{
	if(fMax< fCurrent)
		fCurrent = fMax;
	wsprintf(m_szGageInfo[GAMEMAIN_NEW_STRING_DP], STRMSG_C_INTERFACE_0023);//"����"
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	wsprintf(m_szGageInfo[GAMEMAIN_GAGE_DP_UP], "%d/", (int)fCurrent);
	wsprintf(m_szGageInfo[GAMEMAIN_NEW_STRING_MAX_DP], "%d", (int)fMax);
#else
	wsprintf(m_szGageInfo[GAMEMAIN_GAGE_DP_UP], "%d", (int)fCurrent);
	wsprintf(m_szGageInfo[GAMEMAIN_NEW_STRING_MAX_DP], "/%d", (int)fMax);
#endif
	m_fGageRate[GAMEMAIN_GAGE_DP_UP] = fCurrent/fMax;
}

void CINFGameMainUnitInfoBar::SetBURN(float fCurrent, float fMax)
{
	m_fGageRate[GAMEMAIN_GAGE_BURN_UP] = fCurrent/fMax;
}

void CINFGameMainUnitInfoBar::SetSP(float fCurrent, float fMax)
{
	if(fMax< fCurrent)
		fCurrent = fMax;
	wsprintf(m_szGageInfo[GAMEMAIN_GAGE_SP_UP], "%4d/", (int)fCurrent);
	wsprintf(m_szGageInfo[GAMEMAIN_NEW_STRING_MAX_SP], "%4d", (int)fMax);
	m_fGageRate[GAMEMAIN_GAGE_SP_UP] = fCurrent/fMax;
}

void CINFGameMainUnitInfoBar::SetEP(float fCurrent, float fMax)
{
	if(fMax< fCurrent)
		fCurrent = fMax;
	wsprintf(m_szGageInfo[GAMEMAIN_GAGE_EP_UP], "%d/%d", (int)fCurrent, (int)fMax);
	m_fGageRate[GAMEMAIN_GAGE_EP_UP] = fCurrent/fMax;
}

void CINFGameMainUnitInfoBar::SetEXP(float fExp)
{
	// 2006-02-07 by ispark
	fExp = min(99.99f, fExp);
	fExp = max(0.00f, fExp);
#if _RAT_RANK_SYSTEM
	int PlayerFame = g_pShuttleChild->m_myShuttleInfo.Propensity;

	SRANK_SYSTEM pRANK_SYSTEM;
	SRANK_DATA pRANK_DATA = pRANK_SYSTEM.GetRankByFame(PlayerFame);

#endif

	if (g_pShuttleChild->m_myShuttleInfo.Level == CHARACTER_MAX_LEVEL)
	{
#if _RAT_RANK_SYSTEM
		sprintf(m_szGageInfo[GAMEMAIN_GAGE_EXP_UP], "\\m[%s\\m] \\wLevel \\c%d", pRANK_DATA.Name.c_str(), g_pShuttleChild->m_myShuttleInfo.Level);
#else
		sprintf(m_szGageInfo[GAMEMAIN_GAGE_EXP_UP], "Level %d", g_pShuttleChild->m_myShuttleInfo.Level);
#endif
	}
	else
	{
#if _RAT_RANK_SYSTEM
		sprintf(m_szGageInfo[GAMEMAIN_GAGE_EXP_UP], "\\m[%s\\m] \\wLv.\\c%d \\e%5.1f%%", pRANK_DATA.Name.c_str(), g_pShuttleChild->m_myShuttleInfo.Level, fExp);
#else
		sprintf(m_szGageInfo[GAMEMAIN_GAGE_EXP_UP], "Lv.%d  %5.2f%%", g_pShuttleChild->m_myShuttleInfo.Level, fExp);
#endif
	}
	m_fGageRate[GAMEMAIN_GAGE_EXP_UP] = fExp/100.0f;
}

void CINFGameMainUnitInfoBar::SetSpeed(float fCurrent, float fMin, float fMax)
{
	if(fMin > 0)
	{
		fMin = 0;// �ּ� ���� 0���� �Ѵ�.������ ��츦 ����ؼ� �� ���� ����Ѵ�.
	}
	m_fGageRate[GAMEMAIN_GAGE_SPEED_UP] = (fCurrent-fMin)/(fMax-fMin);
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFGameMainUnitInfoBar::SetHappyHourEvent(BOOL bStart)
/// \brief		�̺�Ʈ ���� �����ܵ��� ��ġ�� �������ִ� �Լ�.
/// \author		dgwoo
/// \date		2007-01-25 ~ 2007-01-25
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMainUnitInfoBar::SetHappyHourEventIconPos()
{
	// ���Ǿƿ� �̺�Ʈ.
	if(g_pD3dApp->GetTestServerFlag() == FALSE)
	{
		m_nHappyHourX = g_pD3dApp->GetBackBufferDesc().Width - GAME_EVENT_BASICPOS_X;
	}
	else
	{
		m_nHappyHourX = g_pD3dApp->GetBackBufferDesc().Width - 120;
	}
	// PC�� ������.
	m_nPCHappyHourX = g_pD3dApp->GetBackBufferDesc().Width - 64;
}

HRESULT CINFGameMainUnitInfoBar::InitDeviceObjects()
{
	ASSERT_ASSERT(m_pGameData);
	// 2011. 10. 10 by jskim UI�ý��� ����	  
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	DataHeader *pDataHeader;
// 	DataHeader *pDataHeader = m_pGameData->Find("mnupbkpx");
// 	m_pImgBackPixel[GAMEMAIN_BACK_UP_PIXEL] = new CINFImage;
// 	m_pImgBackPixel[GAMEMAIN_BACK_UP_PIXEL]->InitDeviceObjects(pDataHeader->m_pData, pDataHeader->m_DataSize);
// 
// 	pDataHeader = m_pGameData->Find("mndnbkpx");
// 	m_pImgBackPixel[GAMEMAIN_BACK_DOWN_PIXEL] = new CINFImage;
// 	m_pImgBackPixel[GAMEMAIN_BACK_DOWN_PIXEL]->InitDeviceObjects(pDataHeader->m_pData, pDataHeader->m_DataSize);
 	pDataHeader = g_pGameMain->m_GruopImagemanager->FindResource("Gage");
	m_pGageBarInfo = g_pGameMain->m_GruopImagemanager->GetGroupImage( pDataHeader );
	m_pGageBarInfo->InitDeviceObjects( g_pD3dApp->m_pImageList );

// 	pDataHeader = m_pGameData->Find("mnMinibk");
// 	m_pImgBackMinimap = new CINFImageEx;
// 	m_pImgBackMinimap->InitDeviceObjects( pDataHeader, g_pD3dApp->m_pImageList );				  
#else													   
	DataHeader *pDataHeader = m_pGameData->Find("mnupbkpx");
	m_pImgBackPixel[GAMEMAIN_BACK_UP_PIXEL] = new CINFImageEx;
	m_pImgBackPixel[GAMEMAIN_BACK_UP_PIXEL]->InitDeviceObjects(pDataHeader);

	pDataHeader = m_pGameData->Find("mndnbkpx");
	m_pImgBackPixel[GAMEMAIN_BACK_DOWN_PIXEL] = new CINFImageEx;
	m_pImgBackPixel[GAMEMAIN_BACK_DOWN_PIXEL]->InitDeviceObjects(pDataHeader);

	pDataHeader = m_pGameData->Find("mnMinibk");
	m_pImgBackMinimap = new CINFImageEx;
	m_pImgBackMinimap->InitDeviceObjects(pDataHeader);
#endif

	char buf[64];
	int i=0;
	for(i=0;i<GAMEMAIN_GAGE_LINE_NUMBER;i++)
	{
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
		m_pFontGageInfo[i] = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()), 7 * HIDPI_COEFF, D3DFONT_ZENABLE, TRUE, 256 * HIDPI_COEFF, 32 * HIDPI_COEFF);
#else
		m_pFontGageInfo[i] = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()), 8, D3DFONT_ZENABLE, TRUE, 256, 32);
#endif
		m_pFontGageInfo[i]->InitDeviceObjects(g_pD3dDev) ;
	}	
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	// 2014-11-15 by shchoi ��ǥ ��Ʈ �׵θ� �߰�
	//m_pFontUnitPosInfo = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()), 7, D3DFONT_ZENABLE, FALSE, 256, 32);
	m_pFontUnitPosInfo = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()), 7 * HIDPI_COEFF, D3DFONT_ZENABLE, TRUE, 256 * HIDPI_COEFF, 32 * HIDPI_COEFF);
	// end 2014-11-15 by shchoi ��ǥ ��Ʈ �׵θ� �߰�
#else																										
	m_pFontUnitPosInfo = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()), 8, D3DFONT_ZENABLE, FALSE, 256, 32);
#endif

	m_pFontUnitPosInfo->InitDeviceObjects(g_pD3dDev) ;
//	for(i=0;i<BUTTON_STATE_NUMBER;i++)
//	{
//		wsprintf( buf, "mnShow%02d", i);
//		pDataHeader = m_pGameData->Find(buf);
//		m_pButtonShowHide[GAMEMAIN_BUTTON_SHOW][i] = new CINFImage;
//		m_pButtonShowHide[GAMEMAIN_BUTTON_SHOW][i]->InitDeviceObjects(pDataHeader->m_pData, pDataHeader->m_DataSize);
//		wsprintf( buf, "mnHide%02d", i);
//		pDataHeader = m_pGameData->Find(buf);
//		m_pButtonShowHide[GAMEMAIN_BUTTON_HIDE][i] = new CINFImage;
//		m_pButtonShowHide[GAMEMAIN_BUTTON_HIDE][i]->InitDeviceObjects(pDataHeader->m_pData, pDataHeader->m_DataSize);
//	}

	// 2004-12-08 by jschoi
	pDataHeader = m_pGameData->Find("MainGB");
	m_pImgMainGageBack = new CINFImageEx;
	m_pImgMainGageBack->InitDeviceObjects( pDataHeader );

	pDataHeader = m_pGameData->Find("expbac");
	m_pImgMainExpBack = new CINFImageEx;
	m_pImgMainExpBack->InitDeviceObjects( pDataHeader );

	pDataHeader = m_pGameData->Find("expbar");
	m_pImgMainExpBar = new CINFImageEx;
	m_pImgMainExpBar->InitDeviceObjects( pDataHeader );
													 
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	pDataHeader = m_pGameData->Find("expbar1");
	m_pImgMainExpBar1 = new CINFImageEx;
	m_pImgMainExpBar1->InitDeviceObjects( pDataHeader );										  
#endif

	pDataHeader = m_pGameData->Find("speedm");
	m_pImgMainSpeedNum = new CINFImageEx;
	m_pImgMainSpeedNum->InitDeviceObjects( pDataHeader );

	pDataHeader = m_pGameData->Find("sMin");
	m_pImgMainMinus = new CINFImageEx;
	m_pImgMainMinus->InitDeviceObjects( pDataHeader );

	pDataHeader = m_pGameData->Find("warn");
	m_pImgMainWarning = new CINFImageEx;
	m_pImgMainWarning->InitDeviceObjects( pDataHeader );

	pDataHeader = m_pGameData->Find("capri");
	m_pImgGeneralPremiumCard = new CINFImageEx;
	m_pImgGeneralPremiumCard->InitDeviceObjects( pDataHeader );

	pDataHeader = m_pGameData->Find("caspri");
	m_pImgSuperPremiumCard = new CINFImageEx;
	m_pImgSuperPremiumCard->InitDeviceObjects( pDataHeader );
	
	pDataHeader = m_pGameData->Find("ehapp_h");
	m_pImgHappyHourEvent = new CINFImageEx;
	m_pImgHappyHourEvent->InitDeviceObjects( pDataHeader );
	
	pDataHeader = m_pGameData->Find("epchapp");
	m_pImgPCHappyHourEvent = new CINFImageEx;
	m_pImgPCHappyHourEvent->InitDeviceObjects( pDataHeader );
	
	// 2010. 06. 08 by jskim Ȩ�����̾� UI �۾�
	pDataHeader = m_pGameData->Find("home_pre");
	m_pImgPCHomePremiumEvent = new CINFImageEx;
	m_pImgPCHomePremiumEvent->InitDeviceObjects( pDataHeader );
	//end 2010. 06. 08 by jskim Ȩ�����̾� UI �۾�

	pDataHeader = m_pGameData->Find("spkicon");
	m_pImgVoiceSPKIcon = new CINFImageEx;
	m_pImgVoiceSPKIcon->InitDeviceObjects( pDataHeader );

	if(m_pImgVoiceChatIcon == NULL)
	{
		// 2008-10-20 by bhsohn VOIP ���� ����
//		m_pImgVoiceChatIcon = new CINFImageBtn;
//		m_pImgVoiceChatIcon->InitDeviceObjects("voiceicon");
		pDataHeader = m_pGameData->Find("voiceicon");
		m_pImgVoiceChatIcon = new CINFImageEx;
		m_pImgVoiceChatIcon->InitDeviceObjects( pDataHeader );
	}
	

	for(i=0;i<GAMEMAIN_GAGE_HP_MAX_GRADE;i++)
	{
		wsprintf( buf, "ene%02d", i);
		pDataHeader = m_pGameData->Find(buf);
		m_pImgMainGageHP[i] = new CINFImageEx;
		m_pImgMainGageHP[i]->InitDeviceObjects( pDataHeader );

		wsprintf( buf, "she%02d", i);
		pDataHeader = m_pGameData->Find(buf);
		m_pImgMainGageDP[i] = new CINFImageEx;
		m_pImgMainGageDP[i]->InitDeviceObjects( pDataHeader );

		wsprintf( buf, "skil%02d", i);
		pDataHeader = m_pGameData->Find(buf);
		m_pImgMainGageSP[i] = new CINFImageEx;
		m_pImgMainGageSP[i]->InitDeviceObjects( pDataHeader );	
	}

	for(i=0;i<GAMEMAIN_GAGE_BOOSTER_MAX_GRADE;i++)
	{
		wsprintf( buf, "Bost%02d", i);
		pDataHeader = m_pGameData->Find(buf);
		m_pImgMainGageBooster[i] = new CINFImageEx;
		m_pImgMainGageBooster[i]->InitDeviceObjects( pDataHeader );	
	}

	for(i=0;i<GAMEMAIN_GAGE_FUEL_MAX_GRADE;i++)
	{
		wsprintf( buf, "fue%02d", i);
		pDataHeader = m_pGameData->Find(buf);
		m_pImgMainGageFuel[i] = new CINFImageEx;
		m_pImgMainGageFuel[i]->InitDeviceObjects( pDataHeader );	
	}

	for(i=0;i<2;i++)
	{
		wsprintf( buf, "fuelG%02d", i);
		pDataHeader = m_pGameData->Find(buf);
		m_pImgMainIconFuel[i] = new CINFImageEx;
		m_pImgMainIconFuel[i]->InitDeviceObjects( pDataHeader );	
	}

	for(i = 0; i < GAMEMAIN_EVENT_RECOVERY_MAX; i++)
	{
		if(m_pImgEventRecovery)
		{
			wsprintf( buf, "growth%d", i+1);
			pDataHeader = m_pGameData->Find(buf);
			if(pDataHeader)
			{
				m_pImgEventRecovery[i] = new CINFImageEx;
				m_pImgEventRecovery[i]->InitDeviceObjects( pDataHeader );
			}
		}
	}
	for(i=0;i<GIFT_ICON_IMG_COUNT;i++)
	{
		wsprintf( buf, "gift%02d", i);
		pDataHeader = m_pGameData->Find(buf);
		m_pImgGiftIcon[i] = new CINFImageEx;
		m_pImgGiftIcon[i]->InitDeviceObjects( pDataHeader );	
	}
	
	// 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������
#ifdef S_BONUSEXPSYSTEM_RENEWAL
	if(m_pImgBonusExpRate == NULL)
	{
		pDataHeader = m_pGameData->Find("bonus_e");
		m_pImgBonusExpRate = new CINFImageEx;
		m_pImgBonusExpRate->InitDeviceObjects( pDataHeader );
	}
 	if(m_pImgRestCount == NULL)
 	{
 		pDataHeader = m_pGameData->Find("rest_num");
 		m_pImgRestCount = new CINFImageEx;
 		m_pImgRestCount->InitDeviceObjects( pDataHeader );
 	}
	if(m_pImgKillCount == NULL)
	{
		pDataHeader = m_pGameData->Find("kill_num");
		m_pImgKillCount = new CINFImageEx;
		m_pImgKillCount->InitDeviceObjects( pDataHeader );
 	}
	if(m_pImgKillCount2 == NULL)
	{
		pDataHeader = m_pGameData->Find("kill_num2");
		m_pImgKillCount2 = new CINFImageEx;
		m_pImgKillCount2->InitDeviceObjects( pDataHeader );
	}
	if(m_pImgKillEff == NULL)
	{
		pDataHeader = m_pGameData->Find("kill_e");
		m_pImgKillEff = new CINFImageEx;
		m_pImgKillEff->InitDeviceObjects( pDataHeader );
	}


	if(m_pGroupImgRestCountBack == NULL)
	{
		pDataHeader = g_pGameMain->m_GruopImagemanager->FindResource( "restexp" );
		m_pGroupImgRestCountBack = g_pGameMain->m_GruopImagemanager->GetGroupImage( pDataHeader );
		m_pGroupImgRestCountBack->InitDeviceObjects( g_pD3dApp->m_pImageList );
	}
	if(m_pGroupImgKillCountBack == NULL)
	{
		pDataHeader = g_pGameMain->m_GruopImagemanager->FindResource( "killcount" );
		m_pGroupImgKillCountBack = g_pGameMain->m_GruopImagemanager->GetGroupImage( pDataHeader );
		m_pGroupImgKillCountBack->InitDeviceObjects( g_pD3dApp->m_pImageList );
	}
#endif // S_BONUSEXPSYSTEM_RENEWAL
	// end 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������

// 2012-11-16 by mspark, ��ī�� ��� ǥ�� ������
#ifdef S_BONUSEXPSYSTEM_RENEWAL
	char szUpBtn[30] = {'\0', }, szDownBtn[30] = {'\0', }, szSelBtn[30] = {'\0', }, szDisBtn[30] = {'\0', };
	wsprintf(szUpBtn, "kill_on3");
	wsprintf(szDownBtn, "kill_on1");
	wsprintf(szSelBtn, "kill_on0");
	wsprintf(szDisBtn, "kill_on2");

	if(NULL == m_pImgRestCountOnBtn)
	{
		m_pImgRestCountOnBtn= new CINFImageBtn;		
		m_pImgRestCountOnBtn->InitDeviceObjects(szUpBtn, szDownBtn, szSelBtn, szDisBtn,"STRTOOLTIP22");
	}

	if(NULL == m_pImgKillCountOnBtn)
	{
		m_pImgKillCountOnBtn= new CINFImageBtn;		
		m_pImgKillCountOnBtn->InitDeviceObjects(szUpBtn, szDownBtn, szSelBtn, szDisBtn,"STRTOOLTIP22");
	}

	wsprintf(szUpBtn, "kill_off3");
	wsprintf(szDownBtn, "kill_off1");
	wsprintf(szSelBtn, "kill_off0");
	wsprintf(szDisBtn, "kill_off2");
	
	if(NULL == m_pImgRestCountOffBtn)
	{
		m_pImgRestCountOffBtn= new CINFImageBtn;		
		m_pImgRestCountOffBtn->InitDeviceObjects(szUpBtn, szDownBtn, szSelBtn, szDisBtn,"STRTOOLTIP23");
	}
	
	if(NULL == m_pImgKillCountOffBtn)
	{
		m_pImgKillCountOffBtn= new CINFImageBtn;		
		m_pImgKillCountOffBtn->InitDeviceObjects(szUpBtn, szDownBtn, szSelBtn, szDisBtn,"STRTOOLTIP23");
	}
#endif
// end 2012-11-16 by mspark, ��ī�� ��� ǥ�� ������

	
	m_pFontMapName = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9 * HIDPI_COEFF, D3DFONT_ZENABLE,  TRUE,512 * HIDPI_COEFF,32 * HIDPI_COEFF);
	m_pFontMapName->InitDeviceObjects(g_pD3dDev);

	m_pFontCurrentEvent = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9 * HIDPI_COEFF, D3DFONT_ZENABLE,  TRUE,512 * HIDPI_COEFF,32 * HIDPI_COEFF);
	m_pFontCurrentEvent->InitDeviceObjects(g_pD3dDev);
	
	m_pFontEventHappyHour = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9 * HIDPI_COEFF, D3DFONT_ZENABLE,  TRUE,512 * HIDPI_COEFF,32 * HIDPI_COEFF);
	m_pFontEventHappyHour->InitDeviceObjects(g_pD3dDev);
	
	m_pFontEventRecovery = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9 * HIDPI_COEFF, D3DFONT_ZENABLE,  TRUE,512 * HIDPI_COEFF,32 * HIDPI_COEFF);
	m_pFontEventRecovery->InitDeviceObjects(g_pD3dDev);

	m_pFontDecaToolTip = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9 * HIDPI_COEFF, D3DFONT_ZENABLE,  TRUE,1024 * HIDPI_COEFF,32 * HIDPI_COEFF);				// 2013-07-15 by ssjung ĳ���� ��ī�� �ູ, ��� ���� ���� ǥ��
	m_pFontDecaToolTip->InitDeviceObjects(g_pD3dDev);

	return S_OK;
}

HRESULT CINFGameMainUnitInfoBar::RestoreDeviceObjects()
{
	if(!m_bRestored)
	{
#ifndef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
		m_pImgBackPixel[GAMEMAIN_BACK_UP_PIXEL]->RestoreDeviceObjects();
		m_pImgBackPixel[GAMEMAIN_BACK_DOWN_PIXEL]->RestoreDeviceObjects();
		m_pImgBackMinimap->RestoreDeviceObjects();
#endif
		m_pFontUnitPosInfo->RestoreDeviceObjects();
		int i=0;
		for(i=0;i<GAMEMAIN_GAGE_LINE_NUMBER;i++)
		{
			m_pFontGageInfo[i]->RestoreDeviceObjects() ;
		}		
		
//		for(i=0;i<BUTTON_STATE_NUMBER;i++)
//		{
//			m_pButtonShowHide[0][i]->RestoreDeviceObjects();
//			m_pButtonShowHide[1][i]->RestoreDeviceObjects();
//		}

		// 2004-12-08 by jschoi
		m_pImgMainGageBack->RestoreDeviceObjects();
		m_pImgMainExpBack->RestoreDeviceObjects();
		m_pImgMainExpBar->RestoreDeviceObjects();
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
		m_pImgMainExpBar1->RestoreDeviceObjects(); 
#endif
		m_pImgMainSpeedNum->RestoreDeviceObjects();
		m_pImgMainMinus->RestoreDeviceObjects();
		m_pImgMainWarning->RestoreDeviceObjects();
		m_pImgGeneralPremiumCard->RestoreDeviceObjects();
		m_pImgSuperPremiumCard->RestoreDeviceObjects();
		m_pImgHappyHourEvent->RestoreDeviceObjects();
		m_pImgPCHappyHourEvent->RestoreDeviceObjects();
		// 2010. 06. 08 by jskim Ȩ�����̾� UI �۾�
		m_pImgPCHomePremiumEvent->RestoreDeviceObjects();
		//end 2010. 06. 08 by jskim Ȩ�����̾� UI �۾�
		m_pImgVoiceChatIcon->RestoreDeviceObjects();
		m_pImgVoiceSPKIcon->RestoreDeviceObjects();
		//m_pImgVoiceChatIcon->SetBtnPosition(GAMEMAIN_VOICECHAT_X,GAMEMAIN_VOICECHAT_Y);
		for(i = 0; i < GAMEMAIN_EVENT_RECOVERY_MAX; i++)
		{
			if(m_pImgEventRecovery[i])
				m_pImgEventRecovery[i]->RestoreDeviceObjects();
		}
		for(i = 0; i < GIFT_ICON_IMG_COUNT; i++)
		{
			if(m_pImgGiftIcon[i])
				m_pImgGiftIcon[i]->RestoreDeviceObjects();
		}
		for(i=0;i<GAMEMAIN_GAGE_HP_MAX_GRADE;i++)
		{
			m_pImgMainGageHP[i]->RestoreDeviceObjects();
			m_pImgMainGageDP[i]->RestoreDeviceObjects();
			m_pImgMainGageSP[i]->RestoreDeviceObjects();	
		}

		for(i=0;i<GAMEMAIN_GAGE_BOOSTER_MAX_GRADE;i++)
		{
			m_pImgMainGageBooster[i]->RestoreDeviceObjects();	
		}

		for(i=0;i<GAMEMAIN_GAGE_FUEL_MAX_GRADE;i++)
		{
			m_pImgMainGageFuel[i]->RestoreDeviceObjects();	
		}
		
		for(i=0;i<2;i++)
		{
			m_pImgMainIconFuel[i]->RestoreDeviceObjects();
		}

		if(m_pFontMapName)
	         m_pFontMapName->RestoreDeviceObjects();

		if(m_pFontCurrentEvent)
			m_pFontCurrentEvent->RestoreDeviceObjects();
		if(m_pFontEventHappyHour)
			m_pFontEventHappyHour->RestoreDeviceObjects();
		if(m_pFontEventRecovery)
			m_pFontEventRecovery->RestoreDeviceObjects();		
		if(m_pFontDecaToolTip)							
			m_pFontDecaToolTip->RestoreDeviceObjects();						// 2013-07-15 by ssjung ĳ���� ��ī�� �ູ, ��� ���� ���� ǥ��
			

		// 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������
#ifdef S_BONUSEXPSYSTEM_RENEWAL
		if(m_pImgBonusExpRate)
			m_pImgBonusExpRate->RestoreDeviceObjects();
		if(m_pImgRestCount)
			m_pImgRestCount->RestoreDeviceObjects();
		if(m_pImgKillCount)
			m_pImgKillCount->RestoreDeviceObjects();
		if(m_pImgKillCount2)
			m_pImgKillCount2->RestoreDeviceObjects();
		if(m_pImgKillEff)
			m_pImgKillEff->RestoreDeviceObjects();
		if(m_pGroupImgRestCountBack)
			m_pGroupImgRestCountBack->RestoreDeviceObjects();	  
		if(m_pGroupImgKillCountBack)
			m_pGroupImgKillCountBack->RestoreDeviceObjects();	
#endif //S_BONUSEXPSYSTEM_RENEWAL
		// 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������

// 2012-11-16 by mspark, ��ī�� ��� ǥ�� ������
#ifdef S_BONUSEXPSYSTEM_RENEWAL
		if(m_pImgRestCountOnBtn)
		{
			m_pImgRestCountOnBtn->RestoreDeviceObjects();			
		}
		if(m_pImgRestCountOffBtn)
		{
			m_pImgRestCountOffBtn->RestoreDeviceObjects();
		}
		if(m_pImgKillCountOnBtn)
		{
			m_pImgKillCountOnBtn->RestoreDeviceObjects();
		}
		if(m_pImgKillCountOffBtn)
		{
			m_pImgKillCountOffBtn->RestoreDeviceObjects();
		}
#endif
// end 2012-11-16 by mspark, ��ī�� ��� ǥ�� ������


		m_bRestored = TRUE;
	}
	return S_OK;
}

HRESULT CINFGameMainUnitInfoBar::InvalidateDeviceObjects()
{
	if(m_bRestored)
	{
#ifndef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
		m_pImgBackPixel[GAMEMAIN_BACK_UP_PIXEL]->InvalidateDeviceObjects();
		m_pImgBackPixel[GAMEMAIN_BACK_DOWN_PIXEL]->InvalidateDeviceObjects();
		m_pImgBackMinimap->InvalidateDeviceObjects();
#endif
		m_pFontUnitPosInfo->InvalidateDeviceObjects();
		int i=0;
		for(i=0;i<GAMEMAIN_GAGE_LINE_NUMBER;i++)
		{
			m_pFontGageInfo[i]->InvalidateDeviceObjects() ;
		}
//		for(i=0;i<BUTTON_STATE_NUMBER;i++)
//		{
//			m_pButtonShowHide[0][i]->InvalidateDeviceObjects();
//			m_pButtonShowHide[1][i]->InvalidateDeviceObjects();
//		}

		// 2004-12-08 by jschoi
		m_pImgMainGageBack->InvalidateDeviceObjects();
		m_pImgMainExpBack->InvalidateDeviceObjects();
		m_pImgMainExpBar->InvalidateDeviceObjects();
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
		m_pImgMainExpBar1->InvalidateDeviceObjects();
#endif
		m_pImgMainSpeedNum->InvalidateDeviceObjects();
		m_pImgMainMinus->InvalidateDeviceObjects();
		m_pImgMainWarning->InvalidateDeviceObjects();
		m_pImgGeneralPremiumCard->InvalidateDeviceObjects();
		m_pImgSuperPremiumCard->InvalidateDeviceObjects();
		m_pImgHappyHourEvent->InvalidateDeviceObjects();
		m_pImgPCHappyHourEvent->InvalidateDeviceObjects();
		// 2010. 06. 08 by jskim Ȩ�����̾� UI �۾�
		m_pImgPCHomePremiumEvent->InvalidateDeviceObjects();
		//end 2010. 06. 08 by jskim Ȩ�����̾� UI �۾�
		m_pImgVoiceChatIcon->InvalidateDeviceObjects();
		m_pImgVoiceSPKIcon->InvalidateDeviceObjects();
		for(i = 0; i < GAMEMAIN_EVENT_RECOVERY_MAX; i++)
		{
			if(m_pImgEventRecovery[i])
				m_pImgEventRecovery[i]->InvalidateDeviceObjects();
		}
		for(i = 0; i < GIFT_ICON_IMG_COUNT; i++)
		{
			if(m_pImgGiftIcon[i])
				m_pImgGiftIcon[i]->InvalidateDeviceObjects();
		}
		for(i=0;i<GAMEMAIN_GAGE_HP_MAX_GRADE;i++)
		{
			m_pImgMainGageHP[i]->InvalidateDeviceObjects();
			m_pImgMainGageDP[i]->InvalidateDeviceObjects();
			m_pImgMainGageSP[i]->InvalidateDeviceObjects();	
		}

		for(i=0;i<GAMEMAIN_GAGE_BOOSTER_MAX_GRADE;i++)
		{
			m_pImgMainGageBooster[i]->InvalidateDeviceObjects();	
		}

		for(i=0;i<GAMEMAIN_GAGE_FUEL_MAX_GRADE;i++)
		{
			m_pImgMainGageFuel[i]->InvalidateDeviceObjects();	
		}
		
		for(i=0;i<2;i++)
		{
			m_pImgMainIconFuel[i]->InvalidateDeviceObjects();
		}

		if(m_pFontMapName )
			m_pFontMapName->InvalidateDeviceObjects();

		if(m_pFontCurrentEvent)
			m_pFontCurrentEvent->InvalidateDeviceObjects();
		if(m_pFontEventHappyHour)
			m_pFontEventHappyHour->InvalidateDeviceObjects();
		if(m_pFontEventRecovery)
			m_pFontEventRecovery->InvalidateDeviceObjects();		
		if(m_pFontDecaToolTip)
			m_pFontDecaToolTip->InvalidateDeviceObjects();				// 2013-07-15 by ssjung ĳ���� ��ī�� �ູ, ��� ���� ���� ǥ��

#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
		if(m_pGageBarInfo)
			m_pGageBarInfo->InvalidateDeviceObjects();											  
#endif

		// 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������
#ifdef S_BONUSEXPSYSTEM_RENEWAL
		if(m_pImgBonusExpRate)
			m_pImgBonusExpRate->InvalidateDeviceObjects();
		if(m_pImgRestCount)
			m_pImgRestCount->InvalidateDeviceObjects();
		if(m_pImgKillCount)
			m_pImgKillCount->InvalidateDeviceObjects();
		if(m_pImgKillCount2)
			m_pImgKillCount2->InvalidateDeviceObjects();
		if(m_pImgKillEff)
			m_pImgKillEff->InvalidateDeviceObjects();
			
		if(m_pGroupImgRestCountBack)
			m_pGroupImgRestCountBack->InvalidateDeviceObjects();
		if(m_pGroupImgKillCountBack)
			m_pGroupImgKillCountBack->InvalidateDeviceObjects();
#endif //S_BONUSEXPSYSTEM_RENEWAL
		// 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������

// 2012-11-16 by mspark, ��ī�� ��� ǥ�� ������
#ifdef S_BONUSEXPSYSTEM_RENEWAL
		if(m_pImgRestCountOnBtn)
		{
			m_pImgRestCountOnBtn->InvalidateDeviceObjects();			
		}
		if(m_pImgRestCountOffBtn)
		{
			m_pImgRestCountOffBtn->InvalidateDeviceObjects();
		}
		if(m_pImgKillCountOnBtn)
		{
			m_pImgKillCountOnBtn->InvalidateDeviceObjects();
		}
		if(m_pImgKillCountOffBtn)
		{
			m_pImgKillCountOffBtn->InvalidateDeviceObjects();
		}
#endif
// end 2012-11-16 by mspark, ��ī�� ��� ǥ�� ������

		m_bRestored = FALSE;
	}
	return S_OK;
}

HRESULT CINFGameMainUnitInfoBar::DeleteDeviceObjects()
{
#ifndef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	m_pImgBackPixel[GAMEMAIN_BACK_UP_PIXEL]->DeleteDeviceObjects();
	m_pImgBackPixel[GAMEMAIN_BACK_DOWN_PIXEL]->DeleteDeviceObjects();
	m_pImgBackMinimap->DeleteDeviceObjects();
#endif
	m_pFontUnitPosInfo->DeleteDeviceObjects();

#ifndef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	SAFE_DELETE(m_pImgBackPixel[GAMEMAIN_BACK_UP_PIXEL]);
	SAFE_DELETE(m_pImgBackPixel[GAMEMAIN_BACK_DOWN_PIXEL]);
	SAFE_DELETE(m_pImgBackMinimap);
#endif
	SAFE_DELETE(m_pFontUnitPosInfo);

	int i=0;
	for(i=0;i<GAMEMAIN_GAGE_LINE_NUMBER;i++)
	{
		m_pFontGageInfo[i]->DeleteDeviceObjects() ;
		SAFE_DELETE(m_pFontGageInfo[i]);
	}	

//	for(i=0;i<BUTTON_STATE_NUMBER;i++)
//	{
//		m_pButtonShowHide[0][i]->DeleteDeviceObjects();
//		m_pButtonShowHide[1][i]->DeleteDeviceObjects();
//		SAFE_DELETE(m_pButtonShowHide[0][i]);
//		SAFE_DELETE(m_pButtonShowHide[1][i]);
//	}

	// 2004-12-08 by jschoi
	m_pImgMainGageBack->DeleteDeviceObjects();
	SAFE_DELETE(m_pImgMainGageBack);
	m_pImgMainExpBack->DeleteDeviceObjects();
	SAFE_DELETE(m_pImgMainExpBack);
	m_pImgMainExpBar->DeleteDeviceObjects();
	SAFE_DELETE(m_pImgMainExpBar);
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	m_pImgMainExpBar1->DeleteDeviceObjects();
	SAFE_DELETE(m_pImgMainExpBar1);																  
#endif
	m_pImgMainSpeedNum->DeleteDeviceObjects();
	SAFE_DELETE(m_pImgMainSpeedNum);
	m_pImgMainMinus->DeleteDeviceObjects();
	SAFE_DELETE(m_pImgMainMinus);
	for(i=0;i<GAMEMAIN_GAGE_HP_MAX_GRADE;i++)
	{
		m_pImgMainGageHP[i]->DeleteDeviceObjects();
		SAFE_DELETE(m_pImgMainGageHP[i]);
		m_pImgMainGageDP[i]->DeleteDeviceObjects();
		SAFE_DELETE(m_pImgMainGageDP[i]);
		m_pImgMainGageSP[i]->DeleteDeviceObjects();	
		SAFE_DELETE(m_pImgMainGageSP[i]);
	}

	for(i=0;i<GAMEMAIN_GAGE_BOOSTER_MAX_GRADE;i++)
	{
		m_pImgMainGageBooster[i]->DeleteDeviceObjects();	
		SAFE_DELETE(m_pImgMainGageBooster[i]);
	}

	for(i=0;i<GAMEMAIN_GAGE_FUEL_MAX_GRADE;i++)
	{
		m_pImgMainGageFuel[i]->DeleteDeviceObjects();	
		SAFE_DELETE(m_pImgMainGageFuel[i]);
	}

	for(i=0;i<2;i++)
	{
		m_pImgMainIconFuel[i]->DeleteDeviceObjects();
		SAFE_DELETE(m_pImgMainIconFuel[i]);
	}

	if(m_pFontMapName ) 
	{
		m_pFontMapName->DeleteDeviceObjects() ;
		SAFE_DELETE(m_pFontMapName ) ; 
	}

	if(m_pFontCurrentEvent)
	{
		m_pFontCurrentEvent->DeleteDeviceObjects() ;
		SAFE_DELETE(m_pFontCurrentEvent ) ; 
	}

	if(m_pFontEventHappyHour)
	{
		m_pFontEventHappyHour->DeleteDeviceObjects() ;
		SAFE_DELETE(m_pFontEventHappyHour ) ; 
	}
	if(m_pFontEventRecovery)
	{
		m_pFontEventRecovery->DeleteDeviceObjects();
		SAFE_DELETE(m_pFontEventRecovery);
	}
	if(m_pFontDecaToolTip)
	{
		m_pFontDecaToolTip->DeleteDeviceObjects();						// 2013-07-15 by ssjung ĳ���� ��ī�� �ູ, ��� ���� ���� ǥ��
		SAFE_DELETE(m_pFontDecaToolTip);
	}
	for(i = 0; i < GAMEMAIN_EVENT_RECOVERY_MAX; i++)
	{
		if(m_pImgEventRecovery[i])
		{
			m_pImgEventRecovery[i]->DeleteDeviceObjects();
			SAFE_DELETE(m_pImgEventRecovery[i]);
		}
	}
	for(i = 0; i < GIFT_ICON_IMG_COUNT; i++)
	{
		if(m_pImgGiftIcon[i])
		{
			m_pImgGiftIcon[i]->DeleteDeviceObjects();
			SAFE_DELETE(m_pImgGiftIcon[i]);
		}
	}	
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	m_pGageBarInfo->DeleteDeviceObjects();
	SAFE_DELETE(m_pGageBarInfo);																  
#endif
	
	// 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������
#ifdef S_BONUSEXPSYSTEM_RENEWAL
	if(m_pImgRestCount)
	{
		m_pImgRestCount->DeleteDeviceObjects();
		SAFE_DELETE(m_pImgRestCount);
	}

	if(m_pImgKillCount)
	{
		m_pImgKillCount->DeleteDeviceObjects();
		SAFE_DELETE(m_pImgKillCount);
	}
	if(m_pImgKillCount2)
	{
		m_pImgKillCount2->DeleteDeviceObjects();
		SAFE_DELETE(m_pImgKillCount2);
	}
	if(m_pImgKillEff)
	{
		m_pImgKillEff->DeleteDeviceObjects();
		SAFE_DELETE(m_pImgKillEff);
	}
	if(m_pGroupImgRestCountBack)
	{
		m_pGroupImgRestCountBack->DeleteDeviceObjects();
		SAFE_DELETE(m_pGroupImgRestCountBack);
	}
	if(m_pGroupImgKillCountBack)
	{
		m_pGroupImgKillCountBack->DeleteDeviceObjects();
		SAFE_DELETE(m_pGroupImgKillCountBack);
	}
#endif //S_BONUSEXPSYSTEM_RENEWAL
	// 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������

// 2012-11-16 by mspark, ��ī�� ��� ǥ�� ������
#ifdef S_BONUSEXPSYSTEM_RENEWAL
	if(m_pImgRestCountOnBtn)
	{
		m_pImgRestCountOnBtn->DeleteDeviceObjects();
		SAFE_DELETE(m_pImgRestCountOnBtn);
	}
	if(m_pImgRestCountOffBtn)
	{
		m_pImgRestCountOffBtn->DeleteDeviceObjects();
		SAFE_DELETE(m_pImgRestCountOffBtn);
	}
	if(m_pImgKillCountOnBtn)
	{
		m_pImgKillCountOnBtn->DeleteDeviceObjects();
		SAFE_DELETE(m_pImgKillCountOnBtn);
	}
	if(m_pImgKillCountOffBtn)
	{
		m_pImgKillCountOffBtn->DeleteDeviceObjects();
		SAFE_DELETE(m_pImgKillCountOffBtn);
	}
#endif
// end 2012-11-16 by mspark, ��ī�� ��� ǥ�� ������


	return S_OK;
}


void CINFGameMainUnitInfoBar::Render()//RenderCityUpInfo() ���� ���� �ڵ� ��� : ������ �����Ұ�
{
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
// 2011. 10. 10 by jskim UI�ý��� ����
// 	// down window - �Ʒ� ���
// 	m_pImgBackPixel[GAMEMAIN_BACK_DOWN_PIXEL]->Move(0, GAMEMAIN_BACK_DOWN_START_Y);
// 	m_pImgBackPixel[GAMEMAIN_BACK_DOWN_PIXEL]->SetScale(g_pD3dApp->GetBackBufferDesc().Width, GAMEMAIN_BACK_DOWN_SIZE_Y);
// 	m_pImgBackPixel[GAMEMAIN_BACK_DOWN_PIXEL]->Render();
// 	
// 	// �������� ��Ÿ ���� �������� ���Ѵ�
// 	if(g_pD3dApp->m_dwGameState == _SHOP)
// 		return;
// 
// 	// up window - ���� ���
// 	m_pImgBackPixel[GAMEMAIN_BACK_UP_PIXEL]->Move(GAMEMAIN_BACK_GAGE_UP_SIZE_X, 0);
// 	m_pImgBackPixel[GAMEMAIN_BACK_UP_PIXEL]->SetScale(g_pD3dApp->GetBackBufferDesc().Width-GAMEMAIN_BACK_GAGE_UP_SIZE_X-GAMEMAIN_BACK_MINIMAP_SIZE_X,GAMEMAIN_BACK_UP_SIZE_Y);
// 	m_pImgBackPixel[GAMEMAIN_BACK_UP_PIXEL]->Render();
// 	
// 	 
// 	// ���� ���
	POINT BGPos = m_pGageBarInfo->GetFindControlTargetofMinPos("MainGB");
 	m_pImgMainGageBack->Move(BGPos.x * HIDPI_COEFF + GAMEMAIN_POS_X,BGPos.y * HIDPI_COEFF + GAMEMAIN_POS_Y);
	m_pImgMainGageBack->SetScale(HIDPI_COEFF, HIDPI_COEFF);
 	m_pImgMainGageBack->Render();
// 
// 	// ����ġ ���
 	m_pImgMainExpBack->Move( 0 , GAMEMAIN_BACK_GAGE_EXP_START_Y );
	m_pImgMainExpBack->SetScale( g_pD3dApp->GetBackBufferDesc().Width, 1 );
 	m_pImgMainExpBack->Render();
// 
 	RenderMainGage();
// 
 	RenderSpeed();
// 
// 	// minimap back
//  	m_pImgBackMinimap->Move(GAMEMAIN_BACK_MINIMAP_START_X, GAMEMAIN_BACK_MINIMAP_START_Y);
//  	m_pImgBackMinimap->Render();
// 
// 	// gage string
 	RenderGageString();
// 	
 	const UINT nMapPosX = g_pD3dApp->GetBackBufferDesc().Width - 110;
 	const UINT nMapPosY = 20;
 	RenderMapPosition(nMapPosX,nMapPosY);
 
 	UINT nStartX = g_pD3dApp->GetBackBufferDesc().Width;
 	UINT nStartY = 4;
 
	MAP_INFO* mapname = g_pDatabase->GetMapInfo(g_pShuttleChild->m_myShuttleInfo.MapChannelIndex.MapIndex);
 	if(mapname)
 	{
 		nStartX -= (strlen(mapname->MapName)*6*HIDPI_COEFF + 30* HIDPI_COEFF);
 		ShowMapNameTitle(nStartX,nStartY);
 	}
 
 	nStartX -= 110;
 	RenderCurrentEvent(nStartX, nStartY);		//���� �������̳� PK���� ������.
	// 2013-03-26 by bhsohn ����� ������ ĳ�ü� ��ư�� ���Ǿƿ� �ΰ� �ڿ� ����
//	RenderPremiumCard(FALSE);					// �Ϲ�
	// END 2013-03-26 by bhsohn ����� ������ ĳ�ü� ��ư�� ���Ǿƿ� �ΰ� �ڿ� ����
	RenderHappyHourEvent(FALSE);
	RenderEventRecovery();						// 2006-04-24 by ispark, �̺�Ʈ ȸ����
	// 2013-03-21 by bhsohn ���Ǿƿ� ��Ʈ�� ���� ���� ���� ó��
//	RenderStringBar();							// 2006-06-08 by ispark, �̺�Ʈ ����
	// END 2013-03-21 by bhsohn ���Ǿƿ� ��Ʈ�� ���� ���� ���� ó��
	RenderGiftIcon(FALSE);
	// end 2011. 10. 10 by jskim UI�ý��� ����					
#else
	// down window - �Ʒ� ���
	m_pImgBackPixel[GAMEMAIN_BACK_DOWN_PIXEL]->Move(0, GAMEMAIN_BACK_DOWN_START_Y);
	m_pImgBackPixel[GAMEMAIN_BACK_DOWN_PIXEL]->SetScale(g_pD3dApp->GetBackBufferDesc().Width, GAMEMAIN_BACK_DOWN_SIZE_Y);
	m_pImgBackPixel[GAMEMAIN_BACK_DOWN_PIXEL]->Render();
	
	// �������� ��Ÿ ���� �������� ���Ѵ�
	if(g_pD3dApp->m_dwGameState == _SHOP)
		return;

	// up window - ���� ���
	m_pImgBackPixel[GAMEMAIN_BACK_UP_PIXEL]->Move(GAMEMAIN_BACK_GAGE_UP_SIZE_X, 0);
	m_pImgBackPixel[GAMEMAIN_BACK_UP_PIXEL]->SetScale(g_pD3dApp->GetBackBufferDesc().Width-GAMEMAIN_BACK_GAGE_UP_SIZE_X-GAMEMAIN_BACK_MINIMAP_SIZE_X,GAMEMAIN_BACK_UP_SIZE_Y);
	m_pImgBackPixel[GAMEMAIN_BACK_UP_PIXEL]->Render();
	
	
	// ���� ���
	m_pImgMainGageBack->Move(0,0);
	m_pImgMainGageBack->Render();

	// ����ġ ���
	m_pImgMainExpBack->Move(GAMEMAIN_BACK_GAGE_EXP_START_X,GAMEMAIN_BACK_GAGE_EXP_START_Y);
	m_pImgMainExpBack->Render();

	RenderMainGage();

	RenderSpeed();

	// minimap back
	m_pImgBackMinimap->Move(GAMEMAIN_BACK_MINIMAP_START_X, GAMEMAIN_BACK_MINIMAP_START_Y);
	m_pImgBackMinimap->Render();

	// gage string
	RenderGageString();
	
	const UINT nMapPosX = g_pD3dApp->GetBackBufferDesc().Width - 110;
	const UINT nMapPosY = 20;
	RenderMapPosition(nMapPosX,nMapPosY);

	UINT nStartX = g_pD3dApp->GetBackBufferDesc().Width;
	UINT nStartY = 4;

	MAP_INFO* mapname = g_pDatabase->GetMapInfo(g_pShuttleChild->m_myShuttleInfo.MapChannelIndex.MapIndex);
	if(mapname)
	{
		nStartX -= (strlen(mapname->MapName)*6 + 30);
		ShowMapNameTitle(nStartX,nStartY);
	}

	nStartX -= 110;
	RenderCurrentEvent(nStartX, nStartY);		//���� �������̳� PK���� ������.


	RenderPremiumCard(FALSE);					// �Ϲ�
	RenderHappyHourEvent(FALSE);
	RenderEventRecovery();						// 2006-04-24 by ispark, �̺�Ʈ ȸ����
	RenderStringBar();							// 2006-06-08 by ispark, �̺�Ʈ ����
	RenderGiftIcon(FALSE);
#endif
	// 2006-04-25 by ispark, ���� �ƿ�� ��Ʈ���� �Լ� ������ �Ű��.	

	// 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������
#ifdef S_BONUSEXPSYSTEM_RENEWAL

	if(g_pGameMain && g_pGameMain->m_pMiniMap && 
		(g_pGameMain->m_pMiniMap->IsRenderBigMap()))
	{
		RenderRestKillCount(false);
	}
	else
	{
		RenderRestKillCount(true);
	}

	RenderBonusExpRate();
#endif // S_BONUSEXPSYSTEM_RENEWAL
	// 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������
}
void CINFGameMainUnitInfoBar::RenderGiftIcon(BOOL i_bCity)
{
	if(m_vecGiftMsg.size())
	{	
// 2008-05-19 by dgwoo ���� �������̽� ��ġ ����.
//		if(i_bCity)
//			m_nGiftY = g_pD3dApp->GetBackBufferDesc().Height - INFOMAIN_GIFT_CITY_ICON_Y;
//		else
			m_nGiftY = g_pD3dApp->GetBackBufferDesc().Height - INFOMAIN_GIFT_FIELD_ICON_Y;
//		if(g_pD3dApp->m_bCharacter && !g_pGround->m_bBazaar)
//			m_nGiftY -= GAME_EVENT_BASICPOS_Y;
		m_ptGift = m_pImgGiftIcon[0]->GetImgSize();
		m_nGiftY -= m_ptGift.y;
		m_nGiftX = g_pD3dApp->GetBackBufferDesc().Width - INFOMAIN_GIFT_ICON_X;
		// ������ ó��.(0.7�ʿ� �ѹ���)
		m_fGiftTime += g_pD3dApp->GetElapsedTime();
		float ftime = m_fGiftTime * 10;
		ftime = (int)ftime % 14;
		if(ftime > 7)
		{
			m_pImgGiftIcon[0]->Move(m_nGiftX, m_nGiftY);
			m_pImgGiftIcon[0]->Render();
		}
		else
		{
			m_pImgGiftIcon[1]->Move(m_nGiftX, m_nGiftY);
			m_pImgGiftIcon[1]->Render();
		}
	}	

}
void CINFGameMainUnitInfoBar::HideRender()
{
	// up window - ���� ���
#ifndef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	m_pImgBackPixel[GAMEMAIN_BACK_UP_PIXEL]->Move(GAMEMAIN_BACK_GAGE_UP_SIZE_X, 0);
	m_pImgBackPixel[GAMEMAIN_BACK_UP_PIXEL]->SetScale(g_pD3dApp->GetBackBufferDesc().Width-GAMEMAIN_BACK_GAGE_UP_SIZE_X-GAMEMAIN_BACK_MINIMAP_SIZE_X,GAMEMAIN_BACK_UP_SIZE_Y);
	m_pImgBackPixel[GAMEMAIN_BACK_UP_PIXEL]->Render();
#endif
	
	// 2004-12-08 by jschoi 
	// ���� ���
	m_pImgMainGageBack->Move(0,0);
	m_pImgMainGageBack->Render();

	RenderMainGage(FALSE);

	RenderSpeed();

	// minimap back
#ifndef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	m_pImgBackMinimap->Move(GAMEMAIN_BACK_MINIMAP_START_X, GAMEMAIN_BACK_MINIMAP_START_Y);
	m_pImgBackMinimap->Render();
#endif

	// gage string
	RenderGageString(FALSE);

	const UINT nMapPosX = g_pD3dApp->GetBackBufferDesc().Width - 110;
	const UINT nMapPosY = 20;
	RenderMapPosition(nMapPosX,nMapPosY);

	UINT nStartX = g_pD3dApp->GetBackBufferDesc().Width;
	UINT nStartY = 4;

	MAP_INFO* mapname = g_pDatabase->GetMapInfo(g_pShuttleChild->m_myShuttleInfo.MapChannelIndex.MapIndex);
	if(mapname)
	{
		nStartX -= (strlen(mapname->MapName)*6 + 30);
		ShowMapNameTitle(nStartX,nStartY);
	}

	nStartX -= 110;
	RenderCurrentEvent(nStartX, nStartY);
	
}

void CINFGameMainUnitInfoBar::RenderCityUpInfo()
{
	// up window
#ifndef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	m_pImgBackPixel[GAMEMAIN_BACK_UP_PIXEL]->Move(GAMEMAIN_BACK_GAGE_UP_SIZE_X, 0);
	m_pImgBackPixel[GAMEMAIN_BACK_UP_PIXEL]->SetScale(g_pD3dApp->GetBackBufferDesc().Width - GAMEMAIN_BACK_GAGE_UP_SIZE_X,GAMEMAIN_BACK_UP_SIZE_Y);
	m_pImgBackPixel[GAMEMAIN_BACK_UP_PIXEL]->Render();
	// down window - �Ʒ� ���
	m_pImgBackPixel[GAMEMAIN_BACK_DOWN_PIXEL]->Move(0, GAMEMAIN_BACK_DOWN_START_Y);
	m_pImgBackPixel[GAMEMAIN_BACK_DOWN_PIXEL]->SetScale(g_pD3dApp->GetBackBufferDesc().Width, GAMEMAIN_BACK_DOWN_SIZE_Y);
	m_pImgBackPixel[GAMEMAIN_BACK_DOWN_PIXEL]->Render();
#endif
	
	// 2004-12-08 by jschoi 
	// ���� ���
	m_pImgMainGageBack->Move(0,0);
	m_pImgMainGageBack->Render();

	// ����ġ ���
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	m_pImgMainExpBack->Move( 0, GAMEMAIN_BACK_GAGE_EXP_START_Y);
#else 
	m_pImgMainExpBack->Move(GAMEMAIN_BACK_GAGE_EXP_START_X,GAMEMAIN_BACK_GAGE_EXP_START_Y);
#endif
	m_pImgMainExpBack->Render();

	RenderMainGage();

	RenderSpeed();

	// gage string
	RenderGageString();


	UINT nStartX = g_pD3dApp->GetBackBufferDesc().Width;
	UINT nStartY = 4;


	// ���̸� ǥ��
	MAP_INFO* mapname = g_pDatabase->GetMapInfo(g_pShuttleChild->m_myShuttleInfo.MapChannelIndex.MapIndex);
	if(mapname)
	{
		nStartX -= (strlen(mapname->MapName)*6 + 30);
		ShowMapNameTitle(nStartX,nStartY);
	}

	// 2005-02-18 by jschoi - Premium Card Render
	RenderPremiumCard(TRUE);	// ����
	// Render HappyHour
	RenderHappyHourEvent(TRUE);
	// 2006-08-29 by dgwoo RenderTextEvent
	RenderTextHappyHourEvent();
	// 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������
#ifdef S_BONUSEXPSYSTEM_RENEWAL
	RenderBonusExpRate();
#endif // S_BONUSEXPSYSTEM_RENEWAL
	// end 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������
}

///////////////////////////////////////////////////////////////////////////////
/// \class		void CINFGameMainUnitInfoBar::RenderTextHappyHourEvent()
/// \brief		���Ǿƿ� �̺�Ʈ ���� �ؽ�Ʈ�� ��´�.
///
/// \author		dgwoo
/// \version	
/// \date		2006-08-29 ~ 2006-08-29
/// \warning	
///////////////////////////////////////////////////////////////////////////////
void CINFGameMainUnitInfoBar::RenderTextHappyHourEvent()
{

	int Height = 0;
	int leng = 0;
	vector<string>::iterator itU = m_vecEventHappyHour.begin();
	while (itU != m_vecEventHappyHour.end())
	{
		if(strlen((char*)(*itU).c_str())>leng)
		{
			leng = strlen((char*)(*itU).c_str());
		}
		itU++;
	}
	leng = leng*6.5;

	if(m_bRenderEvent == TRUE)
	{
		int nIdex = 0;
		vector<string>::iterator it = m_vecEventHappyHour.begin();
		while (it != m_vecEventHappyHour.end())
		{
			g_pGameMain->RenderPopUpWindowImage(m_nHappyHourX, m_nHappyHourY-20-(nIdex*20), leng, 1);
			m_pFontEventHappyHour->DrawText(m_nHappyHourX, m_nHappyHourY-20-(nIdex*20), GUI_FONT_COLOR_Y, (char*)(*it).c_str());
			
			it++;
			nIdex++;
		}
	}
}

// 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������
void CINFGameMainUnitInfoBar::RenderBonusExpRate()
{
#ifdef S_BONUSEXPSYSTEM_RENEWAL
	int nBonusExpX = g_pD3dApp->GetBackBufferDesc().Width - BONUS_EXP_RATE_POS_X;
	int nBonusExpY = g_pD3dApp->GetBackBufferDesc().Height - BONUS_EXP_RATE_POS_Y;
			
	m_pImgBonusExpRate->Move(nBonusExpX, nBonusExpY);
	m_pImgBonusExpRate->Render();
	if(m_bRenderBonusExpRateText)
	{
		RenderBonusExpRateText();
	}
#endif // S_BONUSEXPSYSTEM_RENEWAL
}
void CINFGameMainUnitInfoBar::RenderBonusExpRateText()
{
#ifdef S_BONUSEXPSYSTEM_RENEWAL
	int nBonusExpX = g_pD3dApp->GetBackBufferDesc().Width - BONUS_EXP_RATE_TEXT_POS_X;
	int nBonusExpY = g_pD3dApp->GetBackBufferDesc().Height - BONUS_EXP_RATE_TEXT_POS_Y;

	char strExpRate[3][256];
	// 2012-10-17 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������
	double fRate = 0.0f;
	sprintf(strExpRate[0],STRMSG_C_121013_0001,(double)m_nPartyRate);
	sprintf(strExpRate[1],STRMSG_C_121013_0002,(double)m_nGuildRate);
	fRate = ((double)m_nFriendRate)/10.0;
	sprintf(strExpRate[2],STRMSG_C_121013_0003,fRate);
	// end 2012-10-17 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������
	int nMaxLineLength = 0,i;
	for(i = 0 ; i < 3 ; i++)
	{
		int temp = strlen(strExpRate[i]);
		nMaxLineLength	= max(nMaxLineLength,temp);
	}
	
	// 2014-12-30 by jwLee Bonus Exp ���� �� ���̵��� ����
	int nMoveBonusExpX = BONUS_EXP_RATE_TEXT_POS_X - (nMaxLineLength * 6.0f);
	if (nMoveBonusExpX < 0)
	{
		nBonusExpX += nMoveBonusExpX;
	}
	// end 2014-12-30 by jwLee Bonus Exp ���� �� ���̵��� ����

	for(i = 0 ; i < 3 ; i++)
	{
		// 2014-12-30 by jwLee Bonus Exp ���� �� ���̵��� ����
		//g_pGameMain->RenderPopUpWindowImage(nBonusExpX, nBonusExpY-(BONUS_EXP_RATE_TEXT_LINE_HEIGHT * i), nMaxLineLength * 6.5f, 1);
		g_pGameMain->RenderPopUpWindowImage(nBonusExpX, nBonusExpY-(BONUS_EXP_RATE_TEXT_LINE_HEIGHT * i), nMaxLineLength * 6.0f, 1);
		// end 2014-12-30 by jwLee Bonus Exp ���� �� ���̵��� ����
		m_pFontEventHappyHour->DrawText(nBonusExpX, nBonusExpY-(BONUS_EXP_RATE_TEXT_LINE_HEIGHT * i) - 2, GUI_FONT_COLOR_Y, strExpRate[i]);

	}
#endif //S_BONUSEXPSYSTEM_RENEWAL
}
void CINFGameMainUnitInfoBar::RenderRestKillCount(BOOL bIsMinimap)
{
#ifdef S_BONUSEXPSYSTEM_RENEWAL
	int nRestCount = m_nRestCount;
	int nKillCount = m_nKillCount;

	int nMaxNum;
	UINT nPosX,nPosY,nNum;
	UINT nMapPosX;
 	UINT nMapPosY;

	nMapPosX = g_pD3dApp->GetBackBufferDesc().Width - RESTKILLCOUNT_BASE_POS_X;
	nMapPosY = RESTKILLCOUNT_BASE_POS_Y;

	// �޽� ����ġ ī��Ʈ
	if(nRestCount != 0)
	{
		// �ڸ��� ���
		nMaxNum = GetMaxSize(nRestCount);
		if(nMaxNum > RESTCOUNT_MAX_POSNUM)
		{
			nMaxNum = RESTCOUNT_MAX_POSNUM;
			nRestCount = RESTCOUNT_MAX_COUNT;
		}

		// ��� ����
		//nPosX = nMapPosX - RESTCOUNT_MAX_POSNUM*RESTCOUNT_STRING_WIDTH*RESTCOUNT_SCALE_DEFAULT + RESTCOUNT_BACK_POS_X;
		nPosX = nMapPosX - RESTCOUNT_MAX_POSNUM*RESTCOUNT_STRING_WIDTH*RESTCOUNT_SCALE_DEFAULT + RESTCOUNT_BACK_POS_X + m_fPlusRestCountPosX;	// 2012-11-16 by mspark, ��ī�� ��� ǥ�� ������
		nPosY = nMapPosY - RESTCOUNT_BACK_POS_Y;

		m_pGroupImgRestCountBack->Move(nPosX,nPosY);
		m_pGroupImgRestCountBack->Render();		

		// ���� ����
		//nPosX = nMapPosX - nMaxNum*RESTCOUNT_STRING_WIDTH*RESTCOUNT_SCALE_DEFAULT + RESTCOUNT_TEXT_POS_X;
		nPosX = nMapPosX - nMaxNum*RESTCOUNT_STRING_WIDTH*RESTCOUNT_SCALE_DEFAULT + RESTCOUNT_TEXT_POS_X + m_fPlusRestCountPosX;	// 2012-11-16 by mspark, ��ī�� ��� ǥ�� ������
		nPosY = nMapPosY + RESTCOUNT_TEXT_POS_Y;

		while(nMaxNum > 0)
		{
			nNum = CutOffFirstNumber(nRestCount,nMaxNum);
			m_pImgRestCount->Move(nPosX,nPosY);
			m_pImgRestCount->SetRect(nNum*RESTCOUNT_STRING_WIDTH,0,(nNum+1)*RESTCOUNT_STRING_WIDTH,RESTCOUNT_STRING_HEIGHT);	
			m_pImgRestCount->SetScale(RESTCOUNT_SCALE_DEFAULT,RESTCOUNT_SCALE_DEFAULT);
			m_pImgRestCount->Render();		
			nPosX += RESTCOUNT_STRING_WIDTH*RESTCOUNT_SCALE_DEFAULT; 
			nMaxNum--;
		}

		// 2012-11-16 by mspark, ��ī�� ��� ǥ�� ������
		m_nRestCountPosX  = g_pD3dApp->GetBackBufferDesc().Width - RESTKILLCOUNT_BUTTON_BASE_POS_X;
		m_nRestCountPosY  = nMapPosY - RESTCOUNT_BACK_POS_Y;
		
		if(m_bCheckRestCountON)
		{
			m_pImgRestCountOffBtn->SetBtnPosition(m_nRestCountPosX,m_nRestCountPosY);
			m_pImgRestCountOffBtn->Render();
		}
		else
		{
			m_pImgRestCountOnBtn->SetBtnPosition(m_nRestCountPosX,m_nRestCountPosY);
			m_pImgRestCountOnBtn->Render();
		}
		// end 2012-11-16 by mspark, ��ī�� ��� ǥ�� ������

		// ųī��Ʈ���� ���� ó��
		nMapPosY += RESTCOUNT_STRING_HEIGHT + RESTKILLCOUNT_BASE_HEIGHT_SIZE;
	}	

	// ų ī��Ʈ
	if(nKillCount != 0)
	{
		// �ڸ��� ���
		nMaxNum = GetMaxSize(nKillCount);
		if(nMaxNum > KILLCOUNT_MAX_POSNUM)
		{
			nMaxNum = KILLCOUNT_MAX_POSNUM;
			nKillCount = KILLCOUNT_MAX_COUNT;
		}
		
		// ��� ���� ��ġ ���
		//nPosX = nMapPosX - RESTCOUNT_MAX_POSNUM*RESTCOUNT_STRING_WIDTH*KILLCOUNT_SCALE_DEFAULT + KILLCOUNT_BACK_POS_X;
		nPosX = nMapPosX - RESTCOUNT_MAX_POSNUM*RESTCOUNT_STRING_WIDTH*KILLCOUNT_SCALE_DEFAULT + KILLCOUNT_BACK_POS_X + m_fPlusKillCountPosX;	// 2012-11-16 by mspark, ��ī�� ��� ǥ�� ������
		nPosY = nMapPosY - KILLCOUNT_BACK_POS_Y;
		
		// 300 ī��Ʈ ���� ���� ���� ó��
		if(m_bCompleteKillCount && m_nCompleteKillCountBlank < KILLCOUNT2_EFF_MAX_BLENK_COUNT)
		{
			// ������ ����Ʈ ����
			m_pImgKillEff->Move(nPosX-KILLCOUNT2_EFF_POS_X,nPosY-KILLCOUNT2_EFF_POS_Y);
			m_pImgKillEff->SetColor(D3DCOLOR_ARGB(m_nCompleteKillCountAlpha,255,255,255));
			m_pImgKillEff->Render();		

			if(m_nCompleteKillCountBlank == KILLCOUNT2_EFF_MAX_BLENK_COUNT-1) // ų ī��Ʈ�� ������� ���� ������� �Ѵ�.
			{
				m_pGroupImgKillCountBack->SetColor(D3DCOLOR_ARGB(m_nCompleteKillCountAlpha,255,255,255));
			}
			// ��� ����
			m_pGroupImgKillCountBack->Move(nPosX,nPosY);
			m_pGroupImgKillCountBack->Render();		


			// ���� ����
			nKillCount = KILLCOUNT_MAX_COUNT;
			//nPosX = nMapPosX - nMaxNum*KILLCOUNT2_STRING_WIDTH + KILLCOUNT2_TEXT_POS_X;
			nPosX = nMapPosX - nMaxNum*KILLCOUNT2_STRING_WIDTH + KILLCOUNT2_TEXT_POS_X + m_fPlusKillCountPosX;	// 2012-11-16 by mspark, ��ī�� ��� ǥ�� ������
			nPosY = nMapPosY - KILLCOUNT2_TEXT_POS_Y;

			while(nMaxNum > 0)
			{
				nNum = CutOffFirstNumber(nKillCount,nMaxNum);
				m_pImgKillCount2->Move(nPosX,nPosY);
				m_pImgKillCount2->SetColor(D3DCOLOR_ARGB(m_nCompleteKillCountAlpha,255,255,255));
				m_pImgKillCount2->SetRect(nNum*KILLCOUNT2_STRING_WIDTH,0,(nNum+1)*KILLCOUNT2_STRING_WIDTH,KILLCOUNT2_STRING_HEIGHT);	
				if(m_nCompleteKillCountBlank == KILLCOUNT2_EFF_MAX_BLENK_COUNT-1)
				{
					m_pImgKillCount2->SetColor(D3DCOLOR_ARGB(m_nCompleteKillCountAlpha,255,255,255));
				}
				m_pImgKillCount2->Render();		
				nPosX += KILLCOUNT2_STRING_WIDTH; 
				nMaxNum--;
			}
		}
		// 300 �̸��϶��� ���� ���� ó��
 		else if(!m_bCompleteKillCount)
 		{
			// ��� ����
			m_pGroupImgKillCountBack->Move(nPosX,nPosY);
			m_pGroupImgKillCountBack->SetColor(D3DCOLOR_ARGB(255,255,255,255));
			m_pGroupImgKillCountBack->Render();		

			// ���� ����
			//nPosX = nMapPosX - nMaxNum*RESTCOUNT_STRING_WIDTH*m_fKillCountScale + KILLCOUNT_TEXT_POS_X;
			nPosX = nMapPosX - nMaxNum*RESTCOUNT_STRING_WIDTH*m_fKillCountScale + KILLCOUNT_TEXT_POS_X + m_fPlusKillCountPosX;	// 2012-11-16 by mspark, ��ī�� ��� ǥ�� ������
			nPosY = nMapPosY + KILLCOUNT_TEXT_POS_Y;
			
			while(nMaxNum > 0)
			{
				nNum = CutOffFirstNumber(nKillCount,nMaxNum);
				m_pImgKillCount->Move(nPosX,nPosY);
				m_pImgKillCount->SetRect(nNum*RESTCOUNT_STRING_WIDTH,0,(nNum+1)*RESTCOUNT_STRING_WIDTH,RESTCOUNT_STRING_HEIGHT);	
				m_pImgKillCount->SetScale(m_fKillCountScale,m_fKillCountScale);
				m_pImgKillCount->Render();		
				nPosX += RESTCOUNT_STRING_WIDTH*m_fKillCountScale; 
				nMaxNum--;
			}
		}

		// 2012-11-16 by mspark, ��ī�� ��� ǥ�� ������
		m_nKillCountPosX  = g_pD3dApp->GetBackBufferDesc().Width - RESTKILLCOUNT_BUTTON_BASE_POS_X;
		m_nKillCountPosY  = nMapPosY - RESTCOUNT_BACK_POS_Y;
		
		if(m_bCheckKillCountON)
		{
			m_pImgKillCountOffBtn->SetBtnPosition(m_nKillCountPosX,m_nKillCountPosY);
			m_pImgKillCountOffBtn->Render();
		}
		else
		{
			m_pImgKillCountOnBtn->SetBtnPosition(m_nKillCountPosX,m_nKillCountPosY);
			m_pImgKillCountOnBtn->Render();
		}
		// end 2012-11-16 by mspark, ��ī�� ��� ǥ�� ������
	}	
#endif //S_BONUSEXPSYSTEM_RENEWAL
}
// end 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������


void CINFGameMainUnitInfoBar::RenderGageString(BOOL bShowAll)
{
	if(m_szGageInfo[GAMEMAIN_GAGE_HP_UP])
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	{					

// 2011. 10. 10 by jskim UI�ý��� ����
// 		m_pFontGageInfo[GAMEMAIN_NEW_STRING_HP]->DrawText( GAMEMAIN_NEW_STRING_HP_START_X, 
// 														GAMEMAIN_NEW_STRING_HP_START_Y,
// 														GUI_FONT_COLOR,
// 														m_szGageInfo[GAMEMAIN_NEW_STRING_HP],0L);
		SIZE size = m_pFontGageInfo[GAMEMAIN_GAGE_HP_UP]->GetStringSize(m_szGageInfo[GAMEMAIN_GAGE_HP_UP]);
		m_pFontGageInfo[GAMEMAIN_GAGE_HP_UP]->DrawText( (INT)(GAMEMAIN_GAGE_HP_UP_START_X - ( size.cx / 2 ) ), 
														GAMEMAIN_GAGE_HP_UP_START_Y,
														GUI_FONT_COLOR,
														m_szGageInfo[GAMEMAIN_GAGE_HP_UP],0L);
		size = m_pFontGageInfo[GAMEMAIN_NEW_STRING_MAX_HP]->GetStringSize(m_szGageInfo[GAMEMAIN_NEW_STRING_MAX_HP]);
		m_pFontGageInfo[GAMEMAIN_NEW_STRING_MAX_HP]->DrawText(  (INT)(GAMEMAIN_GAGE_HP_UP_START_X - ( size.cx / 2 ) ), 
														GAMEMAIN_GAGE_HP_UP_START_Y + 10*HIDPI_COEFF,
														GUI_FONT_COLOR,
														m_szGageInfo[GAMEMAIN_NEW_STRING_MAX_HP],0L);
	}

	if(m_szGageInfo[GAMEMAIN_GAGE_DP_UP])
	{
// 		m_pFontGageInfo[GAMEMAIN_NEW_STRING_DP]->DrawText( GAMEMAIN_NEW_STRING_DP_START_X, 
// 														GAMEMAIN_NEW_STRING_DP_START_Y,
// 														GUI_FONT_COLOR,
// 														m_szGageInfo[GAMEMAIN_NEW_STRING_DP],0L);
		SIZE size = m_pFontGageInfo[GAMEMAIN_GAGE_DP_UP]->GetStringSize(m_szGageInfo[GAMEMAIN_GAGE_DP_UP]);
		m_pFontGageInfo[GAMEMAIN_GAGE_DP_UP]->DrawText( (INT)(GAMEMAIN_GAGE_DP_UP_START_X - ( size.cx / 2 ) ), 
														GAMEMAIN_GAGE_DP_UP_START_Y,
														GUI_FONT_COLOR,
														m_szGageInfo[GAMEMAIN_GAGE_DP_UP],0L);
		size = m_pFontGageInfo[GAMEMAIN_NEW_STRING_MAX_DP]->GetStringSize(m_szGageInfo[GAMEMAIN_NEW_STRING_MAX_DP]);
		m_pFontGageInfo[GAMEMAIN_NEW_STRING_MAX_DP]->DrawText( (INT)(GAMEMAIN_GAGE_DP_UP_START_X - ( size.cx / 2 ) ), 
														GAMEMAIN_GAGE_DP_UP_START_Y + 10*HIDPI_COEFF,
														GUI_FONT_COLOR,
														m_szGageInfo[GAMEMAIN_NEW_STRING_MAX_DP],0L);
	}

	if(m_szGageInfo[GAMEMAIN_GAGE_SP_UP])
	{
// 		m_pFontGageInfo[GAMEMAIN_GAGE_SP_UP]->DrawText( GAMEMAIN_GAGE_SP_UP_START_X, 
// 														GAMEMAIN_GAGE_SP_UP_START_Y,
// 														GUI_FONT_COLOR,
// 														m_szGageInfo[GAMEMAIN_GAGE_SP_UP],0L);	
		SIZE size = m_pFontGageInfo[GAMEMAIN_GAGE_SP_UP]->GetStringSize(m_szGageInfo[GAMEMAIN_GAGE_SP_UP]);
		m_pFontGageInfo[GAMEMAIN_GAGE_SP_UP]->DrawText( (INT)( GAMEMAIN_NEW_STRING_MAX_SP_START_X - ( size.cx /2 ) ), 
														GAMEMAIN_NEW_STRING_MAX_SP_START_Y,
														GUI_FONT_COLOR,
														m_szGageInfo[GAMEMAIN_GAGE_SP_UP],0L);
		size = m_pFontGageInfo[GAMEMAIN_NEW_STRING_MAX_SP]->GetStringSize(m_szGageInfo[GAMEMAIN_NEW_STRING_MAX_SP]);
		m_pFontGageInfo[GAMEMAIN_NEW_STRING_MAX_SP]->DrawText( (INT)( GAMEMAIN_NEW_STRING_MAX_SP_START_X - ( size.cx /2 ) ), 
														GAMEMAIN_NEW_STRING_MAX_SP_START_Y + 10 * HIDPI_COEFF,
														GUI_FONT_COLOR,
														m_szGageInfo[GAMEMAIN_NEW_STRING_MAX_SP],0L);
	}

	if(m_szGageInfo[GAMEMAIN_GAGE_EP_UP])
	{
		SIZE size = m_pFontGageInfo[GAMEMAIN_GAGE_EP_UP]->GetStringSize(m_szGageInfo[GAMEMAIN_GAGE_EP_UP]);
		m_pFontGageInfo[GAMEMAIN_GAGE_EP_UP]->DrawText( (INT)( GAMEMAIN_STRING_FUEL_START_X - ( size.cx / 2 ) ), 
														GAMEMAIN_STRING_FUEL_START_Y,
														GUI_FONT_COLOR,
														m_szGageInfo[GAMEMAIN_GAGE_EP_UP],0L);
	}	

	if(	bShowAll &&
		m_szGageInfo[GAMEMAIN_GAGE_EXP_UP])
	{
		SIZE size = m_pFontGageInfo[GAMEMAIN_GAGE_EXP_UP]->GetStringSize(m_szGageInfo[GAMEMAIN_GAGE_EXP_UP]);
		m_pFontGageInfo[GAMEMAIN_GAGE_EXP_UP]->DrawText( (INT)( GAMEMAIN_STRING_EXP_START_X - ( size.cx / 2 ) ), 
														GAMEMAIN_STRING_EXP_START_Y,
														GUI_FONT_COLOR,
														m_szGageInfo[GAMEMAIN_GAGE_EXP_UP],0L);
	}
// end 2011. 10. 10 by jskim UI�ý��� ���� 
#else
	{
		m_pFontGageInfo[GAMEMAIN_NEW_STRING_HP]->DrawText( GAMEMAIN_NEW_STRING_HP_START_X, 
														GAMEMAIN_NEW_STRING_HP_START_Y,
														GUI_FONT_COLOR,
														m_szGageInfo[GAMEMAIN_NEW_STRING_HP],0L);		
		m_pFontGageInfo[GAMEMAIN_GAGE_HP_UP]->DrawText( GAMEMAIN_GAGE_HP_UP_START_X, 
														GAMEMAIN_GAGE_HP_UP_START_Y,
														GUI_FONT_COLOR,
														m_szGageInfo[GAMEMAIN_GAGE_HP_UP],0L);
		m_pFontGageInfo[GAMEMAIN_NEW_STRING_MAX_HP]->DrawText( GAMEMAIN_NEW_STRING_MAX_HP_START_X, 
														GAMEMAIN_NEW_STRING_MAX_HP_START_Y,
														GUI_FONT_COLOR,
														m_szGageInfo[GAMEMAIN_NEW_STRING_MAX_HP],0L);
	}
	if(m_szGageInfo[GAMEMAIN_GAGE_DP_UP])
	{
		m_pFontGageInfo[GAMEMAIN_NEW_STRING_DP]->DrawText( GAMEMAIN_NEW_STRING_DP_START_X, 
														GAMEMAIN_NEW_STRING_DP_START_Y,
														GUI_FONT_COLOR,
														m_szGageInfo[GAMEMAIN_NEW_STRING_DP],0L);		
		m_pFontGageInfo[GAMEMAIN_GAGE_DP_UP]->DrawText( GAMEMAIN_GAGE_DP_UP_START_X, 
														GAMEMAIN_GAGE_DP_UP_START_Y,
														GUI_FONT_COLOR,
														m_szGageInfo[GAMEMAIN_GAGE_DP_UP],0L);
		m_pFontGageInfo[GAMEMAIN_NEW_STRING_MAX_DP]->DrawText( GAMEMAIN_NEW_STRING_MAX_DP_START_X, 
														GAMEMAIN_NEW_STRING_MAX_DP_START_Y,
														GUI_FONT_COLOR,
														m_szGageInfo[GAMEMAIN_NEW_STRING_MAX_DP],0L);
	}

	if(m_szGageInfo[GAMEMAIN_GAGE_SP_UP])
	{
		m_pFontGageInfo[GAMEMAIN_GAGE_SP_UP]->DrawText( GAMEMAIN_GAGE_SP_UP_START_X, 
														GAMEMAIN_GAGE_SP_UP_START_Y,
														GUI_FONT_COLOR,
														m_szGageInfo[GAMEMAIN_GAGE_SP_UP],0L);		
		m_pFontGageInfo[GAMEMAIN_NEW_STRING_MAX_SP]->DrawText( GAMEMAIN_NEW_STRING_MAX_SP_START_X, 
														GAMEMAIN_NEW_STRING_MAX_SP_START_Y,
														GUI_FONT_COLOR,
														m_szGageInfo[GAMEMAIN_NEW_STRING_MAX_SP],0L);
	}

	if(m_szGageInfo[GAMEMAIN_GAGE_EP_UP])
	{
		m_pFontGageInfo[GAMEMAIN_GAGE_EP_UP]->DrawText( GAMEMAIN_STRING_FUEL_START_X, 
														GAMEMAIN_STRING_FUEL_START_Y,
														GUI_FONT_COLOR,
														m_szGageInfo[GAMEMAIN_GAGE_EP_UP],0L);
	}	

	if(	bShowAll &&
		m_szGageInfo[GAMEMAIN_GAGE_EXP_UP])
	{
		m_pFontGageInfo[GAMEMAIN_GAGE_EXP_UP]->DrawText( GAMEMAIN_STRING_EXP_START_X, 
														GAMEMAIN_STRING_EXP_START_Y,
														GUI_FONT_COLOR,
														m_szGageInfo[GAMEMAIN_GAGE_EXP_UP],0L);
	}
#endif
}


void CINFGameMainUnitInfoBar::Tick()
{
	const float RENDER_TIME = 0.5f;
	SetSpeed(g_pShuttleChild->m_fShuttleSpeed, 
			g_pShuttleChild->m_fRealShuttleSpeedMin, 
			g_pShuttleChild->m_fRealShuttleSpeedBoosterOn );
	m_fWarningTime += g_pD3dApp->GetElapsedTime();
	if(m_fWarningTime > RENDER_TIME)
	{
		m_bWarning = !m_bWarning;
		m_fWarningTime -= RENDER_TIME;
	}	
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	g_pGameMain->m_pWeaponInfo->Tick();		// 2011. 10. 10 by jskim UI�ý��� ����				  
#endif
	// 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������
#ifdef S_BONUSEXPSYSTEM_RENEWAL
	if(m_bChangeKillCount)
	{
		m_fKillCountScale -= KILLCOUNT_SCALE_DECREASE;
		if(m_fKillCountScale <= KILLCOUNT_SCALE_DEFAULT)
		{
			m_fKillCountScale = KILLCOUNT_SCALE_DEFAULT;
			m_bChangeKillCount = false;
		}
	}	
	if(m_bCompleteKillCount)
	{
		if(m_nCompleteKillCountBlank < KILLCOUNT2_EFF_MAX_BLENK_COUNT)
		{
			if((m_nCompleteKillCountBlank%2) == 0) // ¦���϶� ���İ� ���
			{
				if(m_nCompleteKillCountAlpha > KILLCOUNT2_EFF_MAX_ALPHA - KILLCOUNT2_EFF_ALPHA_CREASE)
				{
					m_nCompleteKillCountAlpha = KILLCOUNT2_EFF_MAX_ALPHA;
					m_nCompleteKillCountBlank++;
				}
				else
				{
					m_nCompleteKillCountAlpha += KILLCOUNT2_EFF_ALPHA_CREASE;
				}
			}
			else								// Ȧ���϶� ���İ� �϶�
			{
				if(((int)m_nCompleteKillCountAlpha) < 0 + KILLCOUNT2_EFF_ALPHA_CREASE)
				{
					m_nCompleteKillCountAlpha = 0;
					m_nCompleteKillCountBlank++;
				}
				else
				{
					m_nCompleteKillCountAlpha -= KILLCOUNT2_EFF_ALPHA_CREASE;
				}
			}
		}
		else	// 300 ų ī��Ʈ ǥ�� ���� ����.
		{
			m_fKillCountScale = KILLCOUNT_SCALE_DEFAULT;
			m_bCompleteKillCount = false;
			if(m_nKillCount == KILLCOUNT_MAX_COUNT)
			{
				m_nKillCount = 0;
			}
		}
	}

#endif // S_BONUSEXPSYSTEM_RENEWAL
	// end 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������

// 2012-11-16 by mspark, ��ī�� ��� ǥ�� ������
#ifdef S_BONUSEXPSYSTEM_RENEWAL
	if(m_bCheckRestCountBtnClick)
	{
		RestCountImageOnOff();
	}

	if(m_bCheckKillCountBtnClick)
	{
		KillCountImageOnOff();
	}
#endif
// end 2012-11-16 by mspark, ��ī�� ��� ǥ�� ������
}

int CINFGameMainUnitInfoBar::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if(WndProcCity(uMsg, wParam, lParam) == INF_MSGPROC_BREAK )
		return INF_MSGPROC_BREAK;
	
	switch(uMsg)
	{
	case WM_LBUTTONDOWN:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);

			if(pt.x > m_nGiftX &&
				pt.x < m_nGiftX + m_ptGift.x &&
				pt.y > m_nGiftY &&
				pt.y < m_nGiftY + m_ptGift.y)
			{
				CreateMsgBox();
				return INF_MSGPROC_BREAK;
			}

			// 2014-01-28 by ymjoo VoIP ��� ����
#ifndef C_REMOVE_VOIP_YMJOO
			if(g_pGameMain->GetVoiceType() != VOICE_NONE &&
				pt.x > GAMEMAIN_VOICECHAT_X &&
				pt.x < GAMEMAIN_VOICECHAT_X + GAMEMAIN_VOICECHAT_W &&
				pt.y > GAMEMAIN_VOICECHAT_Y &&
				pt.y < GAMEMAIN_VOICECHAT_Y + GAMEMAIN_VOICECHAT_H)
			{
				g_pGameMain->m_pChat->ShowVoiceChatControl(TRUE);
				return INF_MSGPROC_BREAK;
			}
#endif
			// END 2014-01-28 by ymjoo VoIP ��� ����

// 2012-11-16 by mspark, ��ī�� ��� ǥ�� ������
#ifdef S_BONUSEXPSYSTEM_RENEWAL
			if(m_nRestCount != 0 && (g_pShuttleChild->m_bUnitStop || g_pD3dApp->m_bCharacter))		// 2013-07-15 by ssjung ĳ���� ��ī�� �ູ, ��� ���� ���� ǥ��
			{
				if(m_bCheckRestCountON)
				{
					if(TRUE == m_pImgRestCountOffBtn->OnLButtonDown(pt))
					{						
						return  INF_MSGPROC_BREAK;
					}
				}
				else
				{
					if(TRUE == m_pImgRestCountOnBtn->OnLButtonDown(pt))
					{						
						return  INF_MSGPROC_BREAK;
					}
				}
			}
			if(m_nKillCount != 0 && (g_pShuttleChild->m_bUnitStop || g_pD3dApp->m_bCharacter))		// 2013-07-15 by ssjung ĳ���� ��ī�� �ູ, ��� ���� ���� ǥ��
			{
				if(m_bCheckKillCountON)
				{
					if(TRUE == m_pImgKillCountOffBtn->OnLButtonDown(pt))
					{						
						return  INF_MSGPROC_BREAK;
					}
				}
				else
				{
					if(TRUE == m_pImgKillCountOnBtn->OnLButtonDown(pt))
					{						
						return  INF_MSGPROC_BREAK;
					}
				}
			}		
#endif
// end 2012-11-16 by mspark, ��ī�� ��� ǥ�� ������
		}
		break;
	case WM_MOUSEMOVE:
		{
			POINT pt;
			int x,y;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			if(pt.x > GAMEMAIN_VOICECHAT_X &&
				pt.x < GAMEMAIN_VOICECHAT_X + GAMEMAIN_VOICECHAT_W &&
				pt.y > GAMEMAIN_VOICECHAT_Y &&
				pt.y < GAMEMAIN_VOICECHAT_Y + GAMEMAIN_VOICECHAT_H)
			{// ���������� ���� ǥ��.
				char szTemp[128];
				memset(szTemp,0x00,128);
				switch(g_pGameMain->GetVoiceType())
				{
				case VOICE_ONE:
					{
						sprintf(szTemp,STRMSG_C_080519_0113);
					}
					break;
				case VOICE_PARTY:
					{
						sprintf(szTemp,STRMSG_C_080519_0110);
					}
					break;
				case VOICE_GUILD:
					{
						sprintf(szTemp,STRMSG_C_080519_0111);
					}
					break;
				default:
					{
						g_pGameMain->SetToolTip(0,0,NULL);
					}
					break;
				}
				g_pGameMain->SetToolTip(pt.x,pt.y,szTemp);
			}
			else
			{
				g_pGameMain->SetToolTip(0,0,NULL);
			}


			// 2007-11-01 by bhsohn ���� �ƿ�� �̺�Ʈ ó�� ��� ����
			//if(m_BHappyHourEvent)
			if(IsHappyHourEvent())
			{
				m_bRenderEvent = FALSE;
				
				int x,y;
				if(g_pD3dApp->GetTestServerFlag() == FALSE)
				{
					x = g_pD3dApp->GetBackBufferDesc().Width - GAME_EVENT_BASICPOS_X;
				}
				else
				{
					x = g_pD3dApp->GetBackBufferDesc().Width -120;
				}
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
				y = g_pD3dApp->GetBackBufferDesc().Height - 74;
				// 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������
#ifdef S_BONUSEXPSYSTEM_RENEWAL
				y -= RESTKILLCOUNT_MOVE_HAPPYHOUR;
#endif // S_BONUSEXPSYSTEM_RENEWAL
				// end 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������
//				if(g_pD3dApp->m_bCharacter && !g_pGround->m_bBazaar)
//					y -= GAME_EVENT_BASICPOS_Y;

				if( pt.x > x &&
					pt.x < x + 130 && pt.y > y && pt.y < y + 22)
				{
					m_bRenderEvent = TRUE;
				}
#else
				y = g_pD3dApp->GetBackBufferDesc().Height - 54;
#ifdef S_BONUSEXPSYSTEM_RENEWAL
				y -= RESTKILLCOUNT_MOVE_HAPPYHOUR;
#endif // S_BONUSEXPSYSTEM_RENEWAL

//				if(g_pD3dApp->m_bCharacter && !g_pGround->m_bBazaar)
//					y -= GAME_EVENT_BASICPOS_Y;

				if( pt.x > x &&
					pt.x < x + 120 && pt.y > y && pt.y < y + 12)
				{
					m_bRenderEvent = TRUE;
				}
#endif
			}
	// 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������
#ifdef S_BONUSEXPSYSTEM_RENEWAL
			//int x,y;
			RECT BonusExpRateRect;
			BonusExpRateRect.left = g_pD3dApp->GetBackBufferDesc().Width - BONUS_EXP_RATE_POPUP_RECT_LEFT;
			BonusExpRateRect.top = g_pD3dApp->GetBackBufferDesc().Height - BONUS_EXP_RATE_POPUP_RECT_TOP;
			BonusExpRateRect.right = BonusExpRateRect.left + BONUS_EXP_RATE_POPUP_RECT_RIGHT;
			BonusExpRateRect.bottom = BonusExpRateRect.top + BONUS_EXP_RATE_POPUP_RECT_BOTTOM;

			if( BonusExpRateRect.left < pt.x  && pt.x < BonusExpRateRect.right && 
				// 2014-12-09 by jwLee �ý��� �޼���â Ȱ��ȭ ���¿��� ���콺 ������ �ڿ��ִ� �������̽� �̺�Ʈ �߻� ���ϵ��� ����
				//BonusExpRateRect.top < pt.y && pt.y < BonusExpRateRect.bottom)
#if defined(C_SYSTEMMSG_BACK_INF_NO_MOUSE_EVENT)	// 2015-04-07 by jwlee C_SYSTEMMSG_BACK_INF_NO_MOUSE_EVENT ������ �߰�
				// 2015-05-13 by jwlee �ý��� �޼���â Ȱ��ȭ ���¿��� ���Ǿƿ�, ���ʽ� EXP, ĳ�ü� �̺�Ʈ �߻� ���ϵ��� ����
//				BonusExpRateRect.top < pt.y && pt.y < BonusExpRateRect.bottom && !g_pGameMain->m_pChat->m_pSystemMsgW->GetInterface())
				BonusExpRateRect.top < pt.y && pt.y < BonusExpRateRect.bottom && (!g_pGameMain->m_pChat->m_pSystemMsgW->GetInterface() || !g_pGameMain->m_pChat->m_pSystemMsgW->m_bShowChatBox))
				// end 2015-05-13 by jwlee �ý��� �޼���â Ȱ��ȭ ���¿��� ���Ǿƿ�, ���ʽ� EXP, ĳ�ü� �̺�Ʈ �߻� ���ϵ��� ����
#else
				BonusExpRateRect.top < pt.y && pt.y < BonusExpRateRect.bottom)
#endif
				// end 2014-12-09 by jwLee �ý��� �޼���â Ȱ��ȭ ���¿��� ���콺 ������ �ڿ��ִ� �������̽� �̺�Ʈ �߻� ���ϵ��� ����
			{
				m_bRenderBonusExpRateText = TRUE;
				// 2012-10-17 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������
				if(g_pShuttleChild && g_pShuttleChild->m_pClientParty)
				{
					m_nPartyRate = (CAtumSJ::GetPartyBonusExpWeight(g_pShuttleChild->m_pClientParty->GetInSameMapPartyMemberCount()+1)-1.0f) * 100.0f;
				}
				// end 2012-10-17 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������
			}
			else
			{
				m_bRenderBonusExpRateText = FALSE;
			}
#endif // S_BONUSEXPSYSTEM_RENEWAL
	// end 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������

			
			if(TRUE == g_bEventRecovery)
			{
				m_bRenderEventRecovery = FALSE;		
				{
					int nAddY = 100;
#ifndef S_BONUSEXPSYSTEM_RENEWAL				
					nAddY -= RESTKILLCOUNT_MOVE_HAPPYHOUR;
#endif
					if(!g_pD3dApp->m_bCharacter)
						nAddY+=30;

					x = g_pD3dApp->GetBackBufferDesc().Width - 200;
					y = g_pD3dApp->GetBackBufferDesc().Height - nAddY;
				}			
// end 2013-04-09 by ssjung ������� ���� �߻��ϴ� ��ġ�� ���� �׸��� ���콺 �����Ͱ� ���� �� �� �� �ֵ��� ����


				if(g_pD3dApp->m_bCharacter && !g_pGround->m_bBazaar)
					y -= GAME_EVENT_BASICPOS_Y;

				if( pt.x > x &&
					pt.x < x + 44 && pt.y > y && pt.y < y + 20)
				{
					m_bRenderEventRecovery = TRUE;
				}
			}

// 2012-11-16 by mspark, ��ī�� ��� ǥ�� ������
#ifdef S_BONUSEXPSYSTEM_RENEWAL
			y = RESTKILLCOUNT_BASE_POS_Y - RESTCOUNT_BACK_POS_Y;
			if(m_nRestCount != 0 && (g_pShuttleChild->m_bUnitStop || g_pD3dApp->m_bCharacter))		// 2013-07-15 by ssjung ĳ���� ��ī�� �ູ, ��� ���� ���� ǥ��
			{
				if(m_bCheckRestCountON)
				{
// 2013-07-15 by ssjung ĳ���� ��ī�� �ູ, ��� ���� ���� ǥ��
#ifdef C_DECA_TOOLTIP
					m_bRestCountToolTip = FALSE;
					x = g_pD3dApp->GetBackBufferDesc().Width - (RESTCOUNT_IMAGE_POS_LIMIT + RESTKILLCOUNT_BUTTON_WIDTH);
					if( pt.x > x &&
						pt.x < x + RESTCOUNT_IMAGE_POS_LIMIT - RESTKILLCOUNT_BUTTON_WIDTH 
						&& pt.y > y && pt.y < y + RESTKILLCOUNT_BUTTON_HEIGHT)
					{
						m_bRestCountToolTip = TRUE;
					}
#endif
// end 2013-07-15 by ssjung ĳ���� ��ī�� �ູ, ��� ���� ���� ǥ��
					m_pImgRestCountOffBtn->OnMouseMove(pt);
				}
				else
				{
					m_pImgRestCountOnBtn->OnMouseMove(pt);
				}
				y += RESTCOUNT_STRING_HEIGHT + RESTKILLCOUNT_BASE_HEIGHT_SIZE;
			}
// 2013-07-15 by ssjung ĳ���� ��ī�� �ູ, ��� ���� ���� ǥ��
			if(m_nKillCount != 0 && (g_pShuttleChild->m_bUnitStop || g_pD3dApp->m_bCharacter))
			{
				if(m_bCheckKillCountON)
				{
#ifdef C_DECA_TOOLTIP
						m_bKillCountToolTip = FALSE;
						x = g_pD3dApp->GetBackBufferDesc().Width - (KILLCOUNT_IMAGE_POS_LIMIT + RESTKILLCOUNT_BUTTON_WIDTH);
						if( pt.x > x &&	pt.x < x + KILLCOUNT_IMAGE_POS_LIMIT - RESTKILLCOUNT_BUTTON_WIDTH 
							&& pt.y > y && pt.y < y + RESTKILLCOUNT_BUTTON_HEIGHT)
						{
							m_bKillCountToolTip = TRUE;
						}
#endif
// end 2013-07-15 by ssjung ĳ���� ��ī�� �ູ, ��� ���� ���� ǥ��
					m_pImgKillCountOffBtn->OnMouseMove(pt);
				}
				else
				{
					m_pImgKillCountOnBtn->OnMouseMove(pt);
				}				
			}			
#endif
// end 2012-11-16 by mspark, ��ī�� ��� ǥ�� ������
		}
		break;
		case WM_LBUTTONUP:
			{
				POINT pt;
				pt.x = LOWORD(lParam);
				pt.y = HIWORD(lParam);
				CheckMouseReverse(&pt);

// 2012-11-16 by mspark, ��ī�� ��� ǥ�� ������
#ifdef S_BONUSEXPSYSTEM_RENEWAL
				if(m_nRestCount != 0 && (g_pShuttleChild->m_bUnitStop || g_pD3dApp->m_bCharacter))		// 2013-07-15 by ssjung ĳ���� ��ī�� �ູ, ��� ���� ���� ǥ��
				{
					if(m_bCheckRestCountON)
					{
						if(TRUE == m_pImgRestCountOffBtn->OnLButtonUp(pt))
						{
							m_bCheckRestCountON = !m_bCheckRestCountON;
							m_bCheckRestCountBtnClick = true;
						}
					}
					else
					{
						if(TRUE == m_pImgRestCountOnBtn->OnLButtonUp(pt))
						{
							m_bCheckRestCountON = !m_bCheckRestCountON;
							m_bCheckRestCountBtnClick = true;
						}
					}
				}
				if(m_nKillCount != 0 && (g_pShuttleChild->m_bUnitStop || g_pD3dApp->m_bCharacter))			// 2013-07-15 by ssjung ĳ���� ��ī�� �ູ, ��� ���� ���� ǥ��
				{
					if(m_bCheckKillCountON)
					{
						if(TRUE == m_pImgKillCountOffBtn->OnLButtonUp(pt))
						{
							m_bCheckKillCountON = !m_bCheckKillCountON;
							m_bCheckKillCountBtnClick = true;
						}
					}
					else
					{
						if(TRUE == m_pImgKillCountOnBtn->OnLButtonUp(pt))
						{
							m_bCheckKillCountON = !m_bCheckKillCountON;
							m_bCheckKillCountBtnClick = true;
						}
					}
				}				
#endif
// end 2012-11-16 by mspark, ��ī�� ��� ǥ�� ������
		}
		break;
	}
	
	return INF_MSGPROC_NORMAL;
}

int CINFGameMainUnitInfoBar::WndProcCity(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_MOUSEMOVE:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			m_v2MousePt.x = pt.x;
			m_v2MousePt.y = pt.y;
			m_bRenderEvent = FALSE;
			
			// 2007-11-01 by bhsohn ���� �ƿ�� �̺�Ʈ ó�� ��� ����
			//if(m_BHappyHourEvent)
			if(IsHappyHourEvent())
			{
				int x,y;
				if(g_pD3dApp->GetTestServerFlag() == FALSE)
				{
					x = CHAT_MENU_CASH_START_X -177;
				}
				else
				{
					x = g_pD3dApp->GetBackBufferDesc().Width -177;
				}
				y = g_pD3dApp->GetBackBufferDesc().Height - 99;

				if( pt.x > x &&
					pt.x < x + 120 && pt.y > y && pt.y < y + 12)
				{
					m_bRenderEvent = TRUE;
				}
				
			}


			// 2009. 03. 16 by ckPark ����� ���� �߰�
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
			int	x	= g_pD3dApp->GetBackBufferDesc().Width - 104;
			int	y	= g_pD3dApp->GetBackBufferDesc().Height - 52 - GAME_EVENT_BASICPOS_Y;
#else
			int	x	= g_pD3dApp->GetBackBufferDesc().Width - 64;
			int	y	= g_pD3dApp->GetBackBufferDesc().Height - 82

			if(g_pD3dApp->m_bCharacter && !g_pGround->m_bBazaar)
				y -= GAME_EVENT_BASICPOS_Y;
#endif
			if(m_bMemberPCBang)
			{
				POINT	pt = m_pImgGeneralPremiumCard->GetImgSize();
				y -= pt.y;
			}

			RECT membership;
			membership.left		= x;
			membership.top		= y;
			membership.right	= x + m_pImgGeneralPremiumCard->GetImgSize().x;
			membership.bottom	= y + m_pImgGeneralPremiumCard->GetImgSize().y;

			// 2014-12-09 by jwLee �ý��� �޼���â Ȱ��ȭ ���¿��� ���콺 ������ �ڿ��ִ� �������̽� �̺�Ʈ �߻� ���ϵ��� ����
 			//if(PtInRect(&membership, pt))
#if defined(C_SYSTEMMSG_BACK_INF_NO_MOUSE_EVENT)	// 2015-04-07 by jwlee C_SYSTEMMSG_BACK_INF_NO_MOUSE_EVENT ������ �߰�
			// 2015-05-13 by jwlee �ý��� �޼���â Ȱ��ȭ ���¿��� ���Ǿƿ�, ���ʽ� EXP, ĳ�ü� �̺�Ʈ �߻� ���ϵ��� ����
//			if(PtInRect(&membership, pt) && !g_pGameMain->m_pChat->m_pSystemMsgW->GetInterface())
			if(PtInRect(&membership, pt) && (!g_pGameMain->m_pChat->m_pSystemMsgW->GetInterface() || !g_pGameMain->m_pChat->m_pSystemMsgW->m_bShowChatBox))
			// end 2015-05-13 by jwlee �ý��� �޼���â Ȱ��ȭ ���¿��� ���Ǿƿ�, ���ʽ� EXP, ĳ�ü� �̺�Ʈ �߻� ���ϵ��� ����
#else
			if(PtInRect(&membership, pt))
#endif
			// end 2014-12-09 by jwLee �ý��� �޼���â Ȱ��ȭ ���¿��� ���콺 ������ �ڿ��ִ� �������̽� �̺�Ʈ �߻� ���ϵ��� ����
				m_bPremiumToolTip = TRUE;
			else
				m_bPremiumToolTip = FALSE;

			// end 2009. 03. 16 by ckPark ����� ���� �߰�
		}
		break;
	case WM_LBUTTONDOWN:
		{
		}
		break;
	case WM_LBUTTONUP:
		{
		}
		break;
	}
	return INF_MSGPROC_NORMAL;
}

void CINFGameMainUnitInfoBar::RenderMainGage(BOOL bShowAll)
{
	UINT i;
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	POINT Pos = { 0, 0 };
	if(m_fGageRate[GAMEMAIN_GAGE_HP_UP]>0)
	{
		i = m_fGageRate[GAMEMAIN_GAGE_HP_UP]*GAMEMAIN_GAGE_HP_MAX_GRADE;
		if(i>=GAMEMAIN_GAGE_HP_MAX_GRADE){i--;}
		
		i = min(i, GAMEMAIN_GAGE_HP_MAX_GRADE-1); // 2013-06-17 by bhsohn ü�°����� �޸� ���� ����

		if(i > 0)
		{
			Pos = m_pGageBarInfo->GetFindControlTargetofMinPos("ene00");		// 2011. 10. 10 by jskim UI�ý��� ����
			m_pImgMainGageHP[i]->Move( (GAMEMAIN_POS_X + Pos.x) * HIDPI_COEFF, (GAMEMAIN_POS_Y + Pos.y) * HIDPI_COEFF);
			m_pImgMainGageHP[i]->SetScale(HIDPI_COEFF, HIDPI_COEFF);
			m_pImgMainGageHP[i]->Render();
		}
	}
	if(m_fGageRate[GAMEMAIN_GAGE_DP_UP]>0)
	{
		i = m_fGageRate[GAMEMAIN_GAGE_DP_UP]*GAMEMAIN_GAGE_DP_MAX_GRADE;
		if(i>=GAMEMAIN_GAGE_DP_MAX_GRADE){i--;}

		i = min(i, GAMEMAIN_GAGE_DP_MAX_GRADE-1); // 2013-06-17 by bhsohn ü�°����� �޸� ���� ����

		if(i > 0)
		{
			Pos = m_pGageBarInfo->GetFindControlTargetofMinPos("she00");		// 2011. 10. 10 by jskim UI�ý��� ����
			m_pImgMainGageDP[i]->Move( (GAMEMAIN_POS_X + Pos.x) * HIDPI_COEFF, (GAMEMAIN_POS_Y + Pos.y) * HIDPI_COEFF);
			m_pImgMainGageDP[i]->SetScale(HIDPI_COEFF, HIDPI_COEFF);
			m_pImgMainGageDP[i]->Render();
		}
	}
	if(m_fGageRate[GAMEMAIN_GAGE_SP_UP]>0)
	{
		i = m_fGageRate[GAMEMAIN_GAGE_SP_UP]*GAMEMAIN_GAGE_SP_MAX_GRADE;
		if(i>=GAMEMAIN_GAGE_SP_MAX_GRADE){i--;}

		i = min(i, GAMEMAIN_GAGE_SP_MAX_GRADE-1); // 2013-06-17 by bhsohn ü�°����� �޸� ���� ����

		if(i > 0)
		{
			Pos = m_pGageBarInfo->GetFindControlTargetofMinPos("skil00");		// 2011. 10. 10 by jskim UI�ý��� ����
			m_pImgMainGageSP[i]->Move((GAMEMAIN_POS_X + Pos.x) * HIDPI_COEFF, (GAMEMAIN_POS_Y + Pos.y) * HIDPI_COEFF);
			m_pImgMainGageSP[i]->SetScale(HIDPI_COEFF, HIDPI_COEFF);
			m_pImgMainGageSP[i]->Render();
		}
	}
	if(m_fGageRate[GAMEMAIN_GAGE_BURN_UP]>0)
	{
		i = m_fGageRate[GAMEMAIN_GAGE_BURN_UP]*GAMEMAIN_GAGE_BOOSTER_MAX_GRADE;
		if(i>=GAMEMAIN_GAGE_BOOSTER_MAX_GRADE){i--;}

		i = min(i, GAMEMAIN_GAGE_BOOSTER_MAX_GRADE-1); // 2013-06-17 by bhsohn ü�°����� �޸� ���� ����

		Pos = m_pGageBarInfo->GetFindControlTargetofMinPos("Bost00");		// 2011. 10. 10 by jskim UI�ý��� ����
		m_pImgMainGageBooster[i]->Move((GAMEMAIN_POS_X + Pos.x) * HIDPI_COEFF, (GAMEMAIN_POS_Y + Pos.y) * HIDPI_COEFF);
		m_pImgMainGageBooster[i]->SetScale(HIDPI_COEFF, HIDPI_COEFF);
		m_pImgMainGageBooster[i]->Render();
	}
	if(m_fGageRate[GAMEMAIN_GAGE_EP_UP]>0)
	{
		i = m_fGageRate[GAMEMAIN_GAGE_EP_UP]*GAMEMAIN_GAGE_FUEL_MAX_GRADE;
		if(i>=GAMEMAIN_GAGE_FUEL_MAX_GRADE){i--;}

		i = min(i, GAMEMAIN_GAGE_FUEL_MAX_GRADE-1); // 2013-06-17 by bhsohn ü�°����� �޸� ���� ����

		Pos = m_pGageBarInfo->GetFindControlTargetofMinPos("fue00");		// 2011. 10. 10 by jskim UI�ý��� ����
		m_pImgMainGageFuel[i]->Move((GAMEMAIN_POS_X + Pos.x) * HIDPI_COEFF, (GAMEMAIN_POS_Y + Pos.y) * HIDPI_COEFF);
		m_pImgMainGageFuel[i]->SetScale(HIDPI_COEFF, HIDPI_COEFF);
		m_pImgMainGageFuel[i]->Render();
	}
	if(m_fGageRate[GAMEMAIN_GAGE_EP_UP]>0.2f || !m_bWarning)
	{

		Pos = m_pGageBarInfo->GetFindControlTargetofMinPos("fuelG00");		// 2011. 10. 10 by jskim UI�ý��� ����
		m_pImgMainIconFuel[0]->Move((GAMEMAIN_POS_X + Pos.x) * HIDPI_COEFF, (GAMEMAIN_POS_Y + Pos.y) * HIDPI_COEFF);
		m_pImgMainIconFuel[0]->SetScale(HIDPI_COEFF, HIDPI_COEFF);
		m_pImgMainIconFuel[0]->Render();
	}
	else
	{
		Pos = m_pGageBarInfo->GetFindControlTargetofMinPos("fuelG00"); 		// 2011. 10. 10 by jskim UI�ý��� ����
		m_pImgMainIconFuel[1]->Move((GAMEMAIN_POS_X + Pos.x) * HIDPI_COEFF, (GAMEMAIN_POS_Y + Pos.y) * HIDPI_COEFF);
		m_pImgMainIconFuel[1]->SetScale(HIDPI_COEFF, HIDPI_COEFF);
		m_pImgMainIconFuel[1]->Render();
	}
	if(VOICE_NONE != g_pGameMain->GetVoiceType())
	{
		if(g_pGameMain->GetVOIPSpeaking())
		{
			m_pImgVoiceSPKIcon->Move(GAMEMAIN_VOICECHAT_X,GAMEMAIN_VOICECHAT_Y);
			m_pImgVoiceSPKIcon->Render();
		}
		else
		{
			m_pImgVoiceChatIcon->Move(GAMEMAIN_VOICECHAT_X,GAMEMAIN_VOICECHAT_Y);
			m_pImgVoiceChatIcon->Render();
		}		
	}


	// 2008-05-29 by dgwoo ���� �������̽� ���� ��ȹ.
// 2011. 10. 10 by jskim UI�ý��� ����
	Pos = m_pGageBarInfo->GetFindControlTargetofMinPos("firstweapon"); 		
	g_pGameMain->m_pWeaponInfo->RenderLeftWeapon( Pos.x, Pos.y );  // 1�� ����
	Pos = m_pGageBarInfo->GetFindControlTargetofMinPos("secondweapon"); 
	g_pGameMain->m_pWeaponInfo->RenderRightWeapon( Pos.x, Pos.y ); // 2�� ����
	
	//--------------------------------------------------------------------------//
	if(	bShowAll &&
		m_fGageRate[GAMEMAIN_GAGE_EXP_UP]>0)
	{
		m_pImgMainExpBar->Move( 0, GAMEMAIN_BACK_GAGE_EXP_START_Y );
		m_pImgMainExpBar->SetRect(0,0, (float)( g_pD3dApp->GetBackBufferDesc().Width * m_fGageRate[GAMEMAIN_GAGE_EXP_UP] ), g_pD3dApp->GetBackBufferDesc().Height);

		m_pImgMainExpBar->Render();
// 2011-12-08 by jhahn EP4 Ʈ���� ���� UI ����
		m_pImgMainExpBar1->Move( (int)( g_pD3dApp->GetBackBufferDesc().Width * m_fGageRate[GAMEMAIN_GAGE_EXP_UP] ), GAMEMAIN_BACK_GAGE_EXP_START_Y );
//end 2011-12-08 by jhahn EP4 Ʈ���� ���� UI ����
		m_pImgMainExpBar1->Render();
	}
	if(m_fGageRate[GAMEMAIN_GAGE_HP_UP]<0.35f && m_bWarning)
	{ 
		Pos = m_pGageBarInfo->GetFindControlTargetofMinPos("ene00");
		m_pImgMainWarning->Move((GAMEMAIN_POS_X + 2 + Pos.x)* HIDPI_COEFF, (GAMEMAIN_POS_Y + Pos.y)* HIDPI_COEFF);
		m_pImgMainWarning->SetScale(HIDPI_COEFF, HIDPI_COEFF);
		m_pImgMainWarning->Render();
	}	   
#else
	if(m_fGageRate[GAMEMAIN_GAGE_HP_UP]>0)
	{
		i = m_fGageRate[GAMEMAIN_GAGE_HP_UP]*GAMEMAIN_GAGE_HP_MAX_GRADE;
		if(i>=GAMEMAIN_GAGE_HP_MAX_GRADE){i--;}

		if(i > 0)
		{
			m_pImgMainGageHP[i]->Move(GAMEMAIN_GAGE_HP_START_X, GAMEMAIN_GAGE_HP_START_Y);
			m_pImgMainGageHP[i]->Render();
		}
	}
	if(m_fGageRate[GAMEMAIN_GAGE_DP_UP]>0)
	{
		i = m_fGageRate[GAMEMAIN_GAGE_DP_UP]*GAMEMAIN_GAGE_DP_MAX_GRADE;
		if(i>=GAMEMAIN_GAGE_DP_MAX_GRADE){i--;}

		if(i > 0)
		{
			m_pImgMainGageDP[i]->Move(GAMEMAIN_GAGE_DP_START_X, GAMEMAIN_GAGE_DP_START_Y);
			m_pImgMainGageDP[i]->Render();
		}
	}
	if(m_fGageRate[GAMEMAIN_GAGE_SP_UP]>0)
	{
		i = m_fGageRate[GAMEMAIN_GAGE_SP_UP]*GAMEMAIN_GAGE_SP_MAX_GRADE;
		if(i>=GAMEMAIN_GAGE_SP_MAX_GRADE){i--;}

		if(i > 0)
		{
			m_pImgMainGageSP[i]->Move(GAMEMAIN_GAGE_SP_START_X, GAMEMAIN_GAGE_SP_START_Y);
			m_pImgMainGageSP[i]->Render();
		}
	}
	if(m_fGageRate[GAMEMAIN_GAGE_BURN_UP]>0)
	{
		i = m_fGageRate[GAMEMAIN_GAGE_BURN_UP]*GAMEMAIN_GAGE_BOOSTER_MAX_GRADE;
		if(i>=GAMEMAIN_GAGE_BOOSTER_MAX_GRADE){i--;}
		m_pImgMainGageBooster[i]->Move(GAMEMAIN_GAGE_BOOSTER_START_X, GAMEMAIN_GAGE_BOOSTER_START_Y);
		m_pImgMainGageBooster[i]->SetScale(1.125,1.125);
		m_pImgMainGageBooster[i]->Render();
	}
	if(m_fGageRate[GAMEMAIN_GAGE_EP_UP]>0)
	{
		i = m_fGageRate[GAMEMAIN_GAGE_EP_UP]*GAMEMAIN_GAGE_FUEL_MAX_GRADE;
		if(i>=GAMEMAIN_GAGE_FUEL_MAX_GRADE){i--;}
		m_pImgMainGageFuel[i]->Move(GAMEMAIN_GAGE_FUEL_START_X,GAMEMAIN_GAGE_FUEL_START_Y);
		m_pImgMainGageFuel[i]->Render();
	}
	if(m_fGageRate[GAMEMAIN_GAGE_EP_UP]>0.2f || !m_bWarning)
	{
		m_pImgMainIconFuel[0]->Move(GAMEMAIN_GAGE_FUEL_START_X,GAMEMAIN_GAGE_FUEL_START_Y);
		m_pImgMainIconFuel[0]->Render();
	}
	else
	{
		m_pImgMainIconFuel[1]->Move(GAMEMAIN_GAGE_FUEL_START_X,GAMEMAIN_GAGE_FUEL_START_Y);
		m_pImgMainIconFuel[1]->Render();
	}
	if(VOICE_NONE != g_pGameMain->GetVoiceType())
	{
		if(g_pGameMain->GetVOIPSpeaking())
		{
			m_pImgVoiceSPKIcon->Move(GAMEMAIN_VOICECHAT_X,GAMEMAIN_VOICECHAT_Y);
			m_pImgVoiceSPKIcon->Render();
		}
		else
		{
			m_pImgVoiceChatIcon->Move(GAMEMAIN_VOICECHAT_X,GAMEMAIN_VOICECHAT_Y);
			m_pImgVoiceChatIcon->Render();
		}		
	}


	// 2008-05-29 by dgwoo ���� �������̽� ���� ��ȹ.
	g_pGameMain->m_pWeaponInfo->RenderLeftWeapon();
	g_pGameMain->m_pWeaponInfo->RenderRightWeapon();

	//--------------------------------------------------------------------------//
	



	if(	bShowAll &&
		m_fGageRate[GAMEMAIN_GAGE_EXP_UP]>0)
	{
		m_pImgMainExpBar->Move(GAMEMAIN_EXP_GAGE_START_X, GAMEMAIN_EXP_GAGE_START_Y);
		m_pImgMainExpBar->SetRect(0,0,GAMEMAIN_GAGE_EXP_LENGTH*m_fGageRate[GAMEMAIN_GAGE_EXP_UP],9);
		m_pImgMainExpBar->Render();
	}
	if(m_fGageRate[GAMEMAIN_GAGE_HP_UP]<0.35f && m_bWarning)
	{
		m_pImgMainWarning->Move(GAMEMAIN_GAGE_HP_START_X+2, GAMEMAIN_GAGE_HP_START_Y);
		m_pImgMainWarning->Render();
	}
#endif
}
// end 2011. 10. 10 by jskim UI�ý��� ����
void CINFGameMainUnitInfoBar::RenderSpeed()
{
	// 2005-05-31 by jschoi - ���� ���� �߷� ����
//	int nSpeed = (int)g_pShuttleChild->m_fShuttleSpeed;
	// 2005-12-12 by ispark, ĳ���� ���¿����� ������... 0
	int nSpeed = 0;
	if(g_pD3dApp->m_bCharacter && !g_pGround->m_bBazaar)
		nSpeed = 0;
	else
	{
		// 2010. 05. 17 by jskim A��� ���� �ӵ� 1 ���� ���� ����
		//nSpeed = (int)(g_pShuttleChild->m_fShuttleSpeed - g_pShuttleChild->m_fTempGravity);
		//nSpeed = (int)((g_pShuttleChild->m_fShuttleSpeed - g_pShuttleChild->m_fTempGravity) + 1);
		//end. 05. 17 by jskim A��� ���� �ӵ� 1 ���� ���� ����
		nSpeed = (int)((g_pShuttleChild->m_fShuttleSpeed - g_pShuttleChild->m_fTempGravity));

		if ( g_pShuttleChild->m_fShuttleSpeed > .0f )
			nSpeed += 1;
	}


	int nMaxNum = GetMaxSize(nSpeed);
	if(nMaxNum > 3)
	{
		nMaxNum = 3;
		nSpeed = 999;
	}
	UINT nPosX,nPosY,nNum;
	nPosX = SPEED_STRING_START_X - nMaxNum*8;
	nPosY = SPEED_STRING_START_Y;

	if(nSpeed < 0)
	{
		nPosX -= 7;
		m_pImgMainMinus->Move(nPosX,nPosY);
		m_pImgMainMinus->Render();		
		nPosX += 10;
		nSpeed = abs(nSpeed);
	}

	while(nMaxNum > 0)
	{
		nNum = CutOffFirstNumber(nSpeed,nMaxNum);
		m_pImgMainSpeedNum->Move(nPosX,nPosY);
		m_pImgMainSpeedNum->SetRect(nNum*SPEED_STRING_WIDTH,0,(nNum+1)*SPEED_STRING_WIDTH,SPEED_STRING_HEIGHT);	
		m_pImgMainSpeedNum->Render();		
		nPosX += 16; 
		nMaxNum--;
	}
}

int CINFGameMainUnitInfoBar::GetMaxSize(int nNum)
{
	int nMaxSize = 0;
	int nNumber = abs(nNum);
	if(nNumber >= 1000)
	{
		nMaxSize = 4;
	}
	else if(nNumber >= 100)
	{
		nMaxSize = 3;
	}
	else if(nNumber >= 10)
	{
		nMaxSize = 2;
	}
	else
	{
		nMaxSize = 1;
	}
	return nMaxSize;
}

int CINFGameMainUnitInfoBar::CutOffFirstNumber(int& nNum,int nMaxNum)
{
	int nResult = 0;
	// 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������
	if(nMaxNum == 4)
	{
		nResult = nNum/1000;
		nNum = nNum%1000;
		return nResult;
	}
	// 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������
	else if(nMaxNum == 3)
	{
		nResult = nNum/100;
		nNum = nNum%100;
		return nResult;
	}
	else if(nMaxNum == 2)
	{
		nResult = nNum/10;
		nNum = nNum%10;
		return nResult;
	}
	else if(nMaxNum == 1)
	{
		return nNum;
	}
	return 0;
}

void CINFGameMainUnitInfoBar::ShowMapNameTitle(UINT x, UINT y)
{
	char buf[256];
	memset(buf, 0x00, 256);
	MAP_INFO* mapname = g_pDatabase->GetMapInfo(g_pShuttleChild->m_myShuttleInfo.MapChannelIndex.MapIndex);
	if(mapname)
	{
		strncpy(buf, mapname->MapName, sizeof(mapname->MapName));
		wsprintf(buf, "%s(%d)", mapname->MapName,g_pShuttleChild->m_myShuttleInfo.MapChannelIndex.ChannelIndex);
		m_pFontMapName->DrawText(x + 12 , y-3, GAME_MAP_NAME_TEXT_COLOR, buf);
	}
}

void CINFGameMainUnitInfoBar::RenderMapPosition(UINT x, UINT y)
{
	char buf[64];
	int nHeightPerTile;

	if(IS_SPACE_MAP_INDEX(g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.MapChannelIndex.MapIndex) == TRUE)
	{
		nHeightPerTile = (g_pD3dApp->m_pShuttleChild->m_vPos.y-g_pGround->m_projectInfo.fWaterHeight+ALTITUDE_SAPCE_ALTITUDE)/TILE_SIZE;
	}
	else
	{
		nHeightPerTile = (g_pD3dApp->m_pShuttleChild->m_vPos.y-g_pGround->m_projectInfo.fWaterHeight)/TILE_SIZE;
	}

	wsprintf(buf, "X:%3d Y:%3d H:%2d",(int)(g_pD3dApp->m_pShuttleChild->m_vPos.x/TILE_SIZE),
								 (int)(g_pD3dApp->m_pShuttleChild->m_vPos.z/TILE_SIZE),
								 nHeightPerTile);

	m_pFontUnitPosInfo->DrawText( x + 30 , y-4, GAME_UNIT_POS_COLOR, buf, 0L);
}

BOOL CINFGameMainUnitInfoBar::RenderCurrentEvent(UINT x, UINT y)
{
	if(g_pShuttleChild->IsWarpGateZone())
	{
		return FALSE;
	}
	
	if(	g_pShuttleChild && 
		g_pShuttleChild->m_pPkNormalTimer && 
		g_pShuttleChild->m_pPkNormalTimer->IsCityWar())
	{
		m_pFontCurrentEvent->DrawText(x, y, GUI_FONT_COLOR_YM, STRMSG_C_INTERFACE_0024);//"���������� ������"
		return TRUE;	// ���������� ��
	}

#if _RAT_FFA
	if (g_pShuttleChild && (IsPkEnableMap(g_pShuttleChild->m_myShuttleInfo.MapChannelIndex.MapIndex) || MAP_INFLUENCE_PVP_ALL == g_pD3dApp->GetMyShuttleMapInfo()->MapInfluenceType))
	{
		if (g_pShuttleChild &&
			IsPkEnableMap(g_pShuttleChild->m_myShuttleInfo.MapChannelIndex.MapIndex))
		{
			m_pFontCurrentEvent->DrawText(x + 20, y, RGB(255, 54, 0), STRMSG_C_INTERFACE_0025);
		}

		if (g_pShuttleChild &&
			MAP_INFLUENCE_PVP_ALL == g_pD3dApp->GetMyShuttleMapInfo()->MapInfluenceType)
		{
			m_pFontCurrentEvent->DrawText(x + 20, y + 50, RGB(255, 0, 0), "All PVP Area");

		}
		return TRUE;

	}
#else
	if (g_pShuttleChild &&
		IsPkEnableMap(g_pShuttleChild->m_myShuttleInfo.MapChannelIndex.MapIndex))
	{
		m_pFontCurrentEvent->DrawText(x + 20, y, RGB(255, 54, 0), STRMSG_C_INTERFACE_0025);//"PK ���� ����"
		return TRUE;	// PK ���� ��
	}
#endif

	return FALSE;	// �ƹ��� �̺�Ʈ�� ����.
}

BOOL CINFGameMainUnitInfoBar::IsRenderMapName()
{
	float fRadius;
	fRadius = D3DXVec2Length(&(m_v2MousePt - m_v2RaderCenter));
	if(fRadius > RADER_RADIUS)
	{
		return TRUE;
	}
	return FALSE;
}

void CINFGameMainUnitInfoBar::RenderPremiumCard(BOOL bIsCity)
{
	int x,y;
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	x = g_pD3dApp->GetBackBufferDesc().Width - 104;
#else
	x = g_pD3dApp->GetBackBufferDesc().Width - 64;
#endif

//	if(bIsCity)
//		y = g_pD3dApp->GetBackBufferDesc().Height - 107;
//	else
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
		y = g_pD3dApp->GetBackBufferDesc().Height - 52 - GAME_EVENT_BASICPOS_Y;

// 	if(g_pD3dApp->m_bCharacter && !g_pGround->m_bBazaar)
// 		y -= GAME_EVENT_BASICPOS_Y;
#else
		y = g_pD3dApp->GetBackBufferDesc().Height - 82;

	if(g_pD3dApp->m_bCharacter && !g_pGround->m_bBazaar)
		y -= GAME_EVENT_BASICPOS_Y;

	if(m_bMemberPCBang)
	{
		POINT	pt = m_pImgGeneralPremiumCard->GetImgSize();
		y -= pt.y;
	}
#endif

	// 2006-07-05 by ispark, �����̾� ���� ����
	if(g_pD3dApp->GetPrimiumCardInfo()->nCardItemNum1)
	{
		m_pImgGeneralPremiumCard->Move(x,y);
		m_pImgGeneralPremiumCard->Render();

		// 2009. 03. 16 by ckPark ����� ���� �߰�

		if(m_bPremiumToolTip)
		{
			char szBuff[MAX_PATH];
			int curSec	= GetServerDateTime().GetTimeInSeconds();
			int	endSec	= g_pD3dApp->GetPrimiumCardInfo()->atumTimeExpireTime1.GetTimeInSeconds();

			int leftDay		= (endSec - curSec) / 86400;
			int leftHour	= (endSec - curSec) % 86400 / 3600;
			int leftMin		= (endSec - curSec) % 86400 % 3600 / 60;

			if(leftDay <= 0 && leftHour <= 0 && leftMin <= 100)
				sprintf(szBuff, STRMSG_C_090316_0302, leftMin);			// "[����� �ܿ��ð�] 00�� ����"
			else
				sprintf(szBuff, STRMSG_C_090316_0301, leftDay, leftHour);	// "[����� �ܿ��ð�] 00�� 00�ð� ����"

			POINT	drawPt;
			SIZE	strSize = m_pFontEventRecovery->GetStringSize(szBuff);
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
			drawPt.x	= g_pD3dApp->GetBackBufferDesc().Width - strSize.cx;
#else
			drawPt.x	= x - strSize.cx;
#endif
			drawPt.y	= y - strSize.cy;

			g_pGameMain->RenderPopUpWindowImage(drawPt.x, drawPt.y + strSize.cy * 0.1f, strSize.cx, 1);
			m_pFontEventRecovery->DrawText(drawPt.x, drawPt.y, GUI_FONT_COLOR_Y, szBuff);
		}

		// end 2009. 03. 16 by ckPark ����� ���� �߰�
	}

}

void CINFGameMainUnitInfoBar::RenderHappyHourEvent(BOOL bIsCity)
{
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	if(IsHappyHourEvent())
	{	
		m_nHappyHourY = g_pD3dApp->GetBackBufferDesc().Height - 77;
	// 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������
#ifdef S_BONUSEXPSYSTEM_RENEWAL
		m_nHappyHourY -= RESTKILLCOUNT_MOVE_HAPPYHOUR;
#endif // S_BONUSEXPSYSTEM_RENEWAL
	// end 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������

	
		m_pImgHappyHourEvent->Move(m_nHappyHourX, m_nHappyHourY);
		m_pImgHappyHourEvent->Render();
	}
	
	// 2010. 06. 08 by jskim Ȩ�����̾� UI �۾�
 	if(m_pMemberPremiumEvent)
 	{
		m_nPCHappyHourY = g_pD3dApp->GetBackBufferDesc().Height - 122;
		m_pImgPCHomePremiumEvent->Move(m_nPCHappyHourX - 277,m_nPCHappyHourY + 41);
		m_pImgPCHomePremiumEvent->Render();
	}
	//end 2010. 06. 08 by jskim Ȩ�����̾� UI �۾�
 	else if(m_bMemberPCBang)
 	{
		m_nPCHappyHourY = g_pD3dApp->GetBackBufferDesc().Height - 122;

		m_pImgPCHappyHourEvent->Move(m_nPCHappyHourX - 277,m_nPCHappyHourY + 37);	// 2012-03-29 by mspark, ����PC�� �̹��� ��ġ ���� - ���� 41���� 37�� ����
		m_pImgPCHappyHourEvent->Render();		
	}
#else
	// 2007-11-01 by bhsohn ���� �ƿ�� �̺�Ʈ ó�� ��� ����
	//if(m_BHappyHourEvent)
	if(IsHappyHourEvent())
	{	
// 2008-05-19 by dgwoo ���� �������̽� ��ġ ����.
//		if(bIsCity)
//			m_nHappyHourY = g_pD3dApp->GetBackBufferDesc().Height - 99;
//		else
			m_nHappyHourY = g_pD3dApp->GetBackBufferDesc().Height - 57;
//		if(g_pD3dApp->m_bCharacter && !g_pGround->m_bBazaar)
//			m_nHappyHourY -= GAME_EVENT_BASICPOS_Y;

		m_pImgHappyHourEvent->Move(m_nHappyHourX, m_nHappyHourY);
		m_pImgHappyHourEvent->Render();
	}

	// 2010. 06. 08 by jskim Ȩ�����̾� UI �۾�
	if(m_pMemberPremiumEvent)
	{
		m_nPCHappyHourY = g_pD3dApp->GetBackBufferDesc().Height - 87;
		m_pImgPCHomePremiumEvent->Move(m_nPCHappyHourX,m_nPCHappyHourY);
		m_pImgPCHomePremiumEvent->Render();
	}
	//end 2010. 06. 08 by jskim Ȩ�����̾� UI �۾�
	else if(m_bMemberPCBang)
	{
// 2008-05-19 by dgwoo ���� �������̽� ��ġ ����.
//		if(bIsCity)
//			m_nPCHappyHourY = g_pD3dApp->GetBackBufferDesc().Height - 107;
//		else
			m_nPCHappyHourY = g_pD3dApp->GetBackBufferDesc().Height - 82;
		
//		if(g_pD3dApp->m_bCharacter && !g_pGround->m_bBazaar)
//			m_nPCHappyHourY -= GAME_EVENT_BASICPOS_Y;
		
		m_pImgPCHappyHourEvent->Move(m_nPCHappyHourX,m_nPCHappyHourY);
		m_pImgPCHappyHourEvent->Render();		
	}
#endif
}

void CINFGameMainUnitInfoBar::RenderEventRecovery()
{
	if(TRUE == g_bEventRecovery)
	{
		int nCount = ((int)(g_fEventRecoveryRate * 100.0f) / 5.0f) - 1;
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
		int nEventX = g_pD3dApp->GetBackBufferDesc().Width - 196 ;
		int nEventY = g_pD3dApp->GetBackBufferDesc().Height - 102;	// 2012-08-14 by mspark, �̺�Ʈ ȸ���� �̹��� ��ġ ���� - ���� 94���� 102�� ����
#else
		int nEventX = g_pD3dApp->GetBackBufferDesc().Width - 105;
		int nEventY = g_pD3dApp->GetBackBufferDesc().Height - 83;
#endif
	// 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������
#ifdef S_BONUSEXPSYSTEM_RENEWAL
		nEventY -= RESTKILLCOUNT_MOVE_HAPPYHOUR;
#endif // S_BONUSEXPSYSTEM_RENEWAL
	// end 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������
// 2008-05-19 by dgwoo ���� �������̽� ��ġ ����.
//		if(g_pD3dApp->m_bCharacter && !g_pGround->m_bBazaar)
//			nEventY -= GAME_EVENT_BASICPOS_Y;

		// 2009. 08. 21 by ckPark �̺�Ʈ ȸ���� �ܰ� ���� ����
		if( nCount > GAMEMAIN_EVENT_RECOVERY_MAX - 1 )
			nCount = GAMEMAIN_EVENT_RECOVERY_MAX - 1;
		if( nCount < 0 )
			nCount = 0;
		// end 2009. 08. 21 by ckPark �̺�Ʈ ȸ���� �ܰ� ���� ����

		if(m_pImgEventRecovery[nCount])
		{
			m_pImgEventRecovery[nCount]->Move(nEventX, nEventY);
			m_pImgEventRecovery[nCount]->Render();
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFGameMainUnitInfoBar::RenderStringBar()
/// \brief		�̺�Ʈ ����
/// \author		ispark
/// \date		2006-06-08 ~ 2006-06-08
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMainUnitInfoBar::RenderStringBar()
{
	// 2007-11-01 by bhsohn ���� �ƿ�� �̺�Ʈ ó�� ��� ����
	//if(m_BHappyHourEvent)
	if(IsHappyHourEvent())
	{
		// 2006-04-25 by ispark, ���콺 ��ġ�϶� �����ִ� ��Ʈ��
		if(m_bRenderEvent == TRUE)
		{
			// 2006-04-24 by ispark, ����
//			int Height = 0;
			int nRenderX = 0;
			int leng = 0;
			vector<string>::iterator itU = m_vecEventHappyHour.begin();
			while (itU != m_vecEventHappyHour.end())
			{
				int nlengTemp = 0;
				nlengTemp = m_pFontEventHappyHour->GetStringSize((char*)(*itU).c_str()).cx;
//				if(strlen((char*)(*itU).c_str())>leng)
				if(nlengTemp > leng)
				{
					leng = nlengTemp + 10;
//					leng = strlen((char*)(*itU).c_str());
				}
				itU++;
			}
//			leng = leng*6.5;
			nRenderX = m_nHappyHourX + 10;
			if(nRenderX + leng > g_pD3dApp->GetBackBufferDesc().Width)
			{
				nRenderX = g_pD3dApp->GetBackBufferDesc().Width - leng;
			}

			int nIdex = 0;
			vector<string>::iterator it = m_vecEventHappyHour.begin();
			while (it != m_vecEventHappyHour.end())
			{
				g_pGameMain->RenderPopUpWindowImage(nRenderX, m_nHappyHourY-20-(nIdex*20), leng, 1);
				m_pFontEventHappyHour->DrawText(nRenderX, m_nHappyHourY-20-(nIdex*20)-GAMEMAIN_EVENT_FONT_Y, GUI_FONT_COLOR_Y, (char*)(*it).c_str());
				
				it++;
				nIdex++;
			}

		}
	}	

	if(TRUE == g_bEventRecovery)
	{
		int nEventX = g_pD3dApp->GetBackBufferDesc().Width - 88;
		int nEventY = g_pD3dApp->GetBackBufferDesc().Height - 83;
// 2008-05-19 by dgwoo ���� �������̽� ��ġ ����.
//		if(g_pD3dApp->m_bCharacter && !g_pGround->m_bBazaar)
//			nEventY -= GAME_EVENT_BASICPOS_Y;

		if(TRUE == m_bRenderEventRecovery)
		{
			char buf[128] = {0,};

			// 2009. 08. 21 by ckPark �̺�Ʈ ȸ���� �ܰ� ���� ����
			if( g_fEventRecoveryRate > 0.25f )
				g_fEventRecoveryRate = 0.25f;
			if( g_fEventRecoveryRate < 0.0f )
				g_fEventRecoveryRate = 0.0f;
			// end 2009. 08. 21 by ckPark �̺�Ʈ ȸ���� �ܰ� ���� ����			

			sprintf(buf, STRMSG_C_060424_0002, (int)(g_fEventRecoveryRate * 100.0f));
			int leng = m_pFontEventRecovery->GetStringSize(buf).cx + 10;
			if(nEventX + leng > g_pD3dApp->GetBackBufferDesc().Width)
			{
				nEventX = g_pD3dApp->GetBackBufferDesc().Width - leng;
			}
			g_pGameMain->RenderPopUpWindowImage(nEventX, nEventY-13, leng, 1);
			m_pFontEventRecovery->DrawText(nEventX, nEventY-GAMEMAIN_EVENT_FONT_Y-13, GUI_FONT_COLOR_Y, buf);
		}
	}

// 2013-07-15 by ssjung ĳ���� ��ī�� �ູ, ��� ���� ���� ǥ��
#ifdef C_DECA_TOOLTIP
	int nY = RESTKILLCOUNT_BASE_POS_Y - RESTCOUNT_BACK_POS_Y;
	if(m_bRestCountToolTip)
		DecaToolTipFunction(TRUE, nY);
	
	if(m_bKillCountToolTip)
	{
		if(m_nRestCount)
			nY += (RESTCOUNT_STRING_HEIGHT*2 + RESTKILLCOUNT_BASE_HEIGHT_SIZE + RESTCOUNT_BACK_POS_Y + 13);
		DecaToolTipFunction(FALSE, nY);
	}
#endif
// end 2013-07-15 by ssjung ĳ���� ��ī�� �ູ, ��� ���� ���� ǥ��
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CINFGameMainUnitInfoBar::IsHappyHourEvent()
/// \brief		
/// \author		// 2007-11-01 by bhsohn ���� �ƿ�� �̺�Ʈ ó�� ��� ����
/// \date		2007-07-04 ~ 2007-07-04
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CINFGameMainUnitInfoBar::IsHappyHourEvent()
{	
	CHARACTER myShuttleInfo = g_pShuttleChild->GetMyShuttleInfo();
	if(m_bPcBangHappyHour)
	{
		return TRUE;
	}
	else if(TRUE == m_bHappyHourAllInfluence)
	{
		return TRUE;
	}	
	else if(COMPARE_INFLUENCE(m_byHappyHourInfluence, myShuttleInfo.InfluenceType))
	{
		return TRUE;
	}	
	// 2008-05-21 by bhsohn ����, ������ ���� �ƿ�� �߰�
	else if(m_bMotherHappyHour || m_bItemHappyHour)
	{
		return TRUE;
	}
	// end 2008-05-21 by bhsohn ����, ������ ���� �ƿ�� �߰�
	
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CINFGameMainUnitInfoBar::IsHappyHourEvent()
/// \brief		
/// \author		// 2007-11-01 by bhsohn ���� �ƿ�� �̺�Ʈ ó�� ��� ����
/// \date		2007-07-04 ~ 2007-07-04
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CINFGameMainUnitInfoBar::IsHappyHourPcBang()
{
	return m_bPcBangHappyHour;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFGameMainUnitInfoBar::SetHappyHourInfluence(BYTE byInfluence)
/// \brief		
/// \author		// 2007-11-01 by bhsohn ���� �ƿ�� �̺�Ʈ ó�� ��� ����
/// \date		2007-07-04 ~ 2007-07-04
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMainUnitInfoBar::SetHappyHourInfluence(BOOL bLevelup, BOOL bHappyHour, MSG_FC_INFO_GET_HAPPY_HOUR_EVENT_INFO_OK* pMsg)
{
	BYTE byInfluence = pMsg->byInfluenceType4;

	CHARACTER myShuttleInfo = g_pShuttleChild->GetMyShuttleInfo();
	
	// �� ���º� ���� �ƿ�� ����
	EVENT_INFO* pEventInfo = NULL;
	BOOL bAllInfluence = FALSE;
	if(byInfluence == INFLUENCE_TYPE_ALL_MASK)
	{
		bAllInfluence = TRUE;
		pEventInfo = &m_HappyEventAllInfluInfo;
	}
	else if(COMPARE_INFLUENCE(byInfluence, myShuttleInfo.InfluenceType))
	{
		pEventInfo = &m_HappyEventInfo;		
	}
	else
	{
		return;
	}	
	// ���� �ʱ�ȭ	
	memset(pEventInfo, 0x00, sizeof(EVENT_INFO));

	if(bHappyHour)
	{		
		if(bAllInfluence)
		{
			m_bHappyHourAllInfluence = TRUE;			
		}
		else
		{
			m_byHappyHourInfluence = byInfluence;

		}
		// ��ü ���� ���� �ƿ� ����
		SetHappyHourInfo(bLevelup, pMsg, pEventInfo);
	}
	else
	{
		if(bAllInfluence)
		{
			m_bHappyHourAllInfluence = FALSE;			
		}
		else
		{
			m_byHappyHourInfluence  = 0;		
		}		
	}

	// ���� �ƿ�� ���� ���� 
	UpdateHappyHourTooltip();
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFGameMainUnitInfoBar::SetHappyHourInfo(BYTE byInfluence)
/// \brief		
/// \author		// 2007-11-01 by bhsohn ���� �ƿ�� �̺�Ʈ ó�� ��� ����
/// \date		2007-07-04 ~ 2007-07-04
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMainUnitInfoBar::SetHappyHourInfo(BOOL bLevelup, MSG_FC_INFO_GET_HAPPY_HOUR_EVENT_INFO_OK* pMsg, EVENT_INFO* pEventInfo)
{
	char szNotice[1024];
	memset(szNotice, 0x00, 1024);
	
	
	if(pMsg->fEXPRate2 > 0.0f)
	{		
		if(!bLevelup) // �������� �ƴҋ��� ä�ÿ� ǥ�� // 2008-03-14 by bhsohn �������� ���� ���Ǿƿ�� ó��
		{
			sprintf(szNotice, STRMSG_C_EVENT_0003,(pMsg->fEXPRate2)*100);//"���� ����ġ %.0f%% ����"
			g_pGameMain->CreateChatChild(szNotice ,COLOR_SYSTEM);			
		}
		
		pEventInfo->fEXPRate = (pMsg->fEXPRate2);		
	}
	if(pMsg->fDropRareRate2 > 0.0f)
	{
		if(!bLevelup) // �������� �ƴҋ��� ä�ÿ� ǥ�� // 2008-03-14 by bhsohn �������� ���� ���Ǿƿ�� ó��
		{
			sprintf(szNotice, STRMSG_C_EVENT_0004,(pMsg->fDropRareRate2)*100);//"���� �ɼ� ������ ��� Ȯ�� %.0f%% ����"
			g_pGameMain->CreateChatChild(szNotice ,COLOR_SYSTEM);	
		}
		
		pEventInfo->fDropRareRate = (pMsg->fDropRareRate2) ;
		
	}
	if(pMsg->fEXPRepairRate2 > 0.0f )
	{
		if(!bLevelup) // �������� �ƴҋ��� ä�ÿ� ǥ�� // 2008-03-14 by bhsohn �������� ���� ���Ǿƿ�� ó��
		{
			sprintf(szNotice, STRMSG_C_EVENT_0005,(pMsg->fEXPRepairRate2)*100);//"�׾��� ��� �г�Ƽ %.0f%% ����"
			g_pGameMain->CreateChatChild(szNotice ,COLOR_SYSTEM);	
		}
		
		pEventInfo->fEXPRepairRate = (pMsg->fEXPRepairRate2) ;		
	}
	if(pMsg->fDropItemRate2 > 0.0f )
	{
		if(!bLevelup) // �������� �ƴҋ��� ä�ÿ� ǥ�� // 2008-03-14 by bhsohn �������� ���� ���Ǿƿ�� ó��
		{
			sprintf(szNotice, STRMSG_C_EVENT_0006,(pMsg->fDropItemRate2)*100);//"������ ����� %.0f%% ����"
			g_pGameMain->CreateChatChild(szNotice ,COLOR_SYSTEM);	
		}
		
		pEventInfo->fDropItemRate = (pMsg->fDropItemRate2);

	}
	if(pMsg->fSPIRate2 > 0.0f )
	{
		if(!bLevelup) // �������� �ƴҋ��� ä�ÿ� ǥ�� // 2008-03-14 by bhsohn �������� ���� ���Ǿƿ�� ó��
		{
			sprintf(szNotice, STRMSG_C_EVENT_0007,(pMsg->fSPIRate2)*100);//"���Ƿ� %.0f%% ����"
			g_pGameMain->CreateChatChild(szNotice ,COLOR_SYSTEM);	
		}
		
		pEventInfo->fSPIRate = (pMsg->fSPIRate2);
		
	}
	if(pMsg->fWarPointRate2 > 0.0f )
	{// ���� ����Ʈ.
		if(!bLevelup) // �������� �ƴҋ��� ä�ÿ� ǥ�� // 2008-03-14 by bhsohn �������� ���� ���Ǿƿ�� ó��
		{
			sprintf(szNotice, STRMSG_C_070626_0100,(pMsg->fWarPointRate2)*100);//"���� ����Ʈ %d%% ����"
			g_pGameMain->CreateChatChild(szNotice ,COLOR_SYSTEM);	
		}
		
		pEventInfo->fWarPointRate = (pMsg->fWarPointRate2);
		
	}	

	// 2013-08-22 by bhsohn ���Ǿƿ� ������ 
#ifdef SC_RENEWER_HAPPY_HOUR_BHSOHN_BCKIM
	if(pMsg->fHPRecoveryRate > 0.0f)
	{
		if(!bLevelup) 
		{
			sprintf(szNotice, STRMSG_C_130822_0001,(pMsg->fHPRecoveryRate*100.0f));
			g_pGameMain->CreateChatChild(szNotice ,COLOR_SYSTEM);	
		}
		
		pEventInfo->fHPRecoveryRate		= pMsg->fHPRecoveryRate;				// HPȸ����
	}
	if(pMsg->fSHDRecoveryRate > 0.0f)
	{
		if(!bLevelup) 
		{
			sprintf(szNotice, STRMSG_C_130822_0002,(pMsg->fSHDRecoveryRate*100.0f));
			g_pGameMain->CreateChatChild(szNotice ,COLOR_SYSTEM);	
		}
		
		pEventInfo->fSHDRecoveryRate	= pMsg->fSHDRecoveryRate;				// ���� ȸ����
	}
	if(pMsg->fSPRecoveryRate > 0.0f)
	{
		if(!bLevelup) 
		{
			sprintf(szNotice, STRMSG_C_130822_0003,(pMsg->fSPRecoveryRate*100.0f));
			g_pGameMain->CreateChatChild(szNotice ,COLOR_SYSTEM);	
		}
		
		pEventInfo->fSPRecoveryRate		= pMsg->fSPRecoveryRate;				// SP ȸ����
	}
	if(pMsg->fWeaponEnchantRate > 0.0f)
	{
		if(!bLevelup) 
		{
			sprintf(szNotice, STRMSG_C_130822_0004,(pMsg->fWeaponEnchantRate*100.0f));
			g_pGameMain->CreateChatChild(szNotice ,COLOR_SYSTEM);	
		}
		pEventInfo->fWeaponEnchantRate	= pMsg->fWeaponEnchantRate;				// ����� ��þƮ ����Ȯ��
	}
	if(pMsg->fArmorEnchantRate > 0.0f)
	{
		if(!bLevelup) 
		{
			sprintf(szNotice, STRMSG_C_130822_0005,(pMsg->fArmorEnchantRate*100.0f));
			g_pGameMain->CreateChatChild(szNotice ,COLOR_SYSTEM);	
		}
		
		pEventInfo->fArmorEnchantRate	= pMsg->fArmorEnchantRate;				// �Ƹӷ� ��þƮ ����Ȯ��
	}
	if(pMsg->fETCItemEnchantRate > 0.0f)
	{
		if(!bLevelup) 
		{
			sprintf(szNotice, STRMSG_C_130822_0006,(pMsg->fETCItemEnchantRate*100.0f));
			g_pGameMain->CreateChatChild(szNotice ,COLOR_SYSTEM);	
		}
		pEventInfo->fETCItemEnchantRate	= pMsg->fETCItemEnchantRate;			// Etc ��þƮ ����Ȯ��
	}
	if(pMsg->fSPIDiscountRate > 0.0f)
	{
		if(!bLevelup) 
		{
			sprintf(szNotice, STRMSG_C_130822_0007,(pMsg->fSPIDiscountRate*100.0f));
			g_pGameMain->CreateChatChild(szNotice ,COLOR_SYSTEM);	
		}
		pEventInfo->fSPIDiscountRate	= pMsg->fSPIDiscountRate;				// SPI���� ������ ������
	}
	if(pMsg->fWPDiscountRate > 0.0f)
	{
		if(!bLevelup) 
		{
			sprintf(szNotice, STRMSG_C_130822_0008,(pMsg->fWPDiscountRate*100.0f));
			g_pGameMain->CreateChatChild(szNotice ,COLOR_SYSTEM);	
		}
		
		pEventInfo->fWPDiscountRate		= pMsg->fWPDiscountRate;				// WP���� ������ ������
	}	
#endif
	// END 2013-08-22 by bhsohn ���Ǿƿ� ������ 

	if(!bLevelup) // �������� �ƴҋ��� ä�ÿ� ǥ�� // 2008-03-14 by bhsohn �������� ���� ���Ǿƿ�� ó��
	{
		g_pGameMain->CreateChatChild(STRMSG_C_EVENT_0008 ,COLOR_SYSTEM);//"���� �ð� �ǽñ� �ٶ��ϴ�. ^^"	
	}

	
}

void CINFGameMainUnitInfoBar::UpdateHappyHourTooltip()
{
	char szNotice[1024];
	memset(szNotice, 0x00, 1024);
	float fTmp = 0.0f;

	// 2013-08-22 by bhsohn ���Ǿƿ� ������
	EVENT_INFO	struAllHappyHourInfo;
	memset(&struAllHappyHourInfo, 0x00, sizeof(EVENT_INFO));
	// END 2013-08-22 by bhsohn ���Ǿƿ� ������

	{
		// 2008-05-21 by bhsohn ����, ������ ���� �ƿ�� �߰�
		//fTmp = m_HappyEventInfo.fEXPRate+m_HappyEventAllInfluInfo.fEXPRate+m_PCHappyEventInfo.fEXPRate;
		fTmp = m_HappyEventInfo.fEXPRate+m_HappyEventAllInfluInfo.fEXPRate+m_PCHappyEventInfo.fEXPRate
				+m_MotherShipEventInfo.fEXPRate+m_ItemEventInfo.fEXPRate;

		struAllHappyHourInfo.fEXPRate = fTmp; // 2013-08-22 by bhsohn ���Ǿƿ� ������

		if(fTmp > 0)
		{
			sprintf(szNotice, STRMSG_C_EVENT_0003,(fTmp)*100);//"���� ����ġ %.0f%% ����"
			m_vecEventHappyHour.push_back(szNotice);
		}
	}
	{
		// 2008-05-21 by bhsohn ����, ������ ���� �ƿ�� �߰�
		//fTmp = m_HappyEventInfo.fDropRareRate +m_HappyEventAllInfluInfo.fDropRareRate+m_PCHappyEventInfo.fDropRareRate;
		fTmp = m_HappyEventInfo.fDropRareRate +m_HappyEventAllInfluInfo.fDropRareRate+m_PCHappyEventInfo.fDropRareRate
				+m_MotherShipEventInfo.fDropRareRate+m_ItemEventInfo.fDropRareRate;

		struAllHappyHourInfo.fDropRareRate = fTmp; // 2013-08-22 by bhsohn ���Ǿƿ� ������
		if(fTmp)
		{
			sprintf(szNotice, STRMSG_C_EVENT_0004,(fTmp)*100);//"���� �ɼ� ������ ��� Ȯ�� %.0f%% ����"
			m_vecEventHappyHour.push_back(szNotice);
		}
		
	}

	{
		// 2008-05-21 by bhsohn ����, ������ ���� �ƿ�� �߰�
		//fTmp = m_HappyEventInfo.fEXPRepairRate +m_HappyEventAllInfluInfo.fEXPRepairRate+m_PCHappyEventInfo.fEXPRepairRate;
		fTmp = m_HappyEventInfo.fEXPRepairRate +m_HappyEventAllInfluInfo.fEXPRepairRate+m_PCHappyEventInfo.fEXPRepairRate
				+m_MotherShipEventInfo.fEXPRepairRate+m_ItemEventInfo.fEXPRepairRate;

		struAllHappyHourInfo.fEXPRepairRate = fTmp; // 2013-08-22 by bhsohn ���Ǿƿ� ������

		// �г�Ƽ�� 100%�� ������ ����. 
		if(fTmp > 1.0f)
		{
			fTmp = 1.0f;
		}
		
		if(fTmp > 0)
		{
			sprintf(szNotice, STRMSG_C_EVENT_0005,(fTmp)*100);//"�׾��� ��� �г�Ƽ %.0f%% ����"
			m_vecEventHappyHour.push_back(szNotice);
		}
	}

	{
		// 2008-05-21 by bhsohn ����, ������ ���� �ƿ�� �߰�
		//fTmp = m_HappyEventInfo.fDropItemRate +m_HappyEventAllInfluInfo.fDropItemRate+m_PCHappyEventInfo.fDropItemRate;
		fTmp = m_HappyEventInfo.fDropItemRate +m_HappyEventAllInfluInfo.fDropItemRate+m_PCHappyEventInfo.fDropItemRate
				+m_MotherShipEventInfo.fDropItemRate+m_ItemEventInfo.fDropItemRate;

		struAllHappyHourInfo.fDropItemRate = fTmp; // 2013-08-22 by bhsohn ���Ǿƿ� ������

		if(fTmp>0)
		{
			sprintf(szNotice, STRMSG_C_EVENT_0006,(fTmp)*100);//"������ ����� %.0f%% ����"
			m_vecEventHappyHour.push_back(szNotice);
		}
	}

	{
		// 2008-05-21 by bhsohn ����, ������ ���� �ƿ�� �߰�
		//fTmp = m_HappyEventInfo.fSPIRate +m_HappyEventAllInfluInfo.fSPIRate+m_PCHappyEventInfo.fSPIRate;
		fTmp = m_HappyEventInfo.fSPIRate +m_HappyEventAllInfluInfo.fSPIRate+m_PCHappyEventInfo.fSPIRate
				+m_MotherShipEventInfo.fSPIRate+m_ItemEventInfo.fSPIRate;

		struAllHappyHourInfo.fSPIRate = fTmp; // 2013-08-22 by bhsohn ���Ǿƿ� ������

		if(fTmp > 0)
		{
			sprintf(szNotice, STRMSG_C_EVENT_0007,(fTmp)*100);//"���Ƿ� %.0f%% ����"
			m_vecEventHappyHour.push_back(szNotice);
		}
	}

	{
		// 2008-05-21 by bhsohn ����, ������ ���� �ƿ�� �߰�
		//fTmp = m_HappyEventInfo.fWarPointRate +m_HappyEventAllInfluInfo.fWarPointRate+m_PCHappyEventInfo.fWarPointRate;
		fTmp = m_HappyEventInfo.fWarPointRate +m_HappyEventAllInfluInfo.fWarPointRate+m_PCHappyEventInfo.fWarPointRate
				+m_MotherShipEventInfo.fWarPointRate +m_ItemEventInfo.fWarPointRate;

		struAllHappyHourInfo.fWarPointRate = fTmp; // 2013-08-22 by bhsohn ���Ǿƿ� ������

		if(fTmp >0)
		{
			sprintf(szNotice, STRMSG_C_070626_0100,(fTmp)*100);//"���Ƿ� %.0f%% ����"
			m_vecEventHappyHour.push_back(szNotice);
		}
	}
	
	// 2013-08-22 by bhsohn ���Ǿƿ� ������ 	
#ifdef SC_RENEWER_HAPPY_HOUR_BHSOHN_BCKIM
	{
		// HPȸ����
		fTmp = m_HappyEventInfo.fHPRecoveryRate +m_HappyEventAllInfluInfo.fHPRecoveryRate+m_PCHappyEventInfo.fHPRecoveryRate
				+m_MotherShipEventInfo.fHPRecoveryRate +m_ItemEventInfo.fHPRecoveryRate;

		struAllHappyHourInfo.fHPRecoveryRate = fTmp; // 2013-08-22 by bhsohn ���Ǿƿ� ������

		if(fTmp >0)
		{
			sprintf(szNotice, STRMSG_C_130822_0001,(fTmp)*100.0f);
			m_vecEventHappyHour.push_back(szNotice);
		}
		
	}
	{
		// ���� ȸ����
		fTmp = m_HappyEventInfo.fSHDRecoveryRate +m_HappyEventAllInfluInfo.fSHDRecoveryRate+m_PCHappyEventInfo.fSHDRecoveryRate
				+m_MotherShipEventInfo.fSHDRecoveryRate +m_ItemEventInfo.fSHDRecoveryRate;		

		struAllHappyHourInfo.fSHDRecoveryRate = fTmp; // 2013-08-22 by bhsohn ���Ǿƿ� ������

		if(fTmp >0)
		{
			sprintf(szNotice, STRMSG_C_130822_0002,(fTmp)*100.0f);
			m_vecEventHappyHour.push_back(szNotice);
		}
	}

	{
		// SP ȸ����
		fTmp = m_HappyEventInfo.fSPRecoveryRate +m_HappyEventAllInfluInfo.fSPRecoveryRate+m_PCHappyEventInfo.fSPRecoveryRate
				+m_MotherShipEventInfo.fSPRecoveryRate +m_ItemEventInfo.fSPRecoveryRate;		

		struAllHappyHourInfo.fSPRecoveryRate = fTmp; // 2013-08-22 by bhsohn ���Ǿƿ� ������

		if(fTmp >0)
		{
			sprintf(szNotice, STRMSG_C_130822_0003,(fTmp)*100.0f);
			m_vecEventHappyHour.push_back(szNotice);
		}
	}
	{
		// ����� ��þƮ ����Ȯ��
		fTmp = m_HappyEventInfo.fWeaponEnchantRate +m_HappyEventAllInfluInfo.fWeaponEnchantRate+m_PCHappyEventInfo.fWeaponEnchantRate
				+m_MotherShipEventInfo.fWeaponEnchantRate +m_ItemEventInfo.fWeaponEnchantRate;		

		struAllHappyHourInfo.fWeaponEnchantRate = fTmp; // 2013-08-22 by bhsohn ���Ǿƿ� ������

		if(fTmp >0)
		{
			sprintf(szNotice, STRMSG_C_130822_0004,(fTmp)*100.0f);
			m_vecEventHappyHour.push_back(szNotice);
		}
	}
	{
		// �Ƹӷ� ��þƮ ����Ȯ��
		fTmp = m_HappyEventInfo.fArmorEnchantRate +m_HappyEventAllInfluInfo.fArmorEnchantRate+m_PCHappyEventInfo.fArmorEnchantRate
				+m_MotherShipEventInfo.fArmorEnchantRate +m_ItemEventInfo.fArmorEnchantRate;		

		struAllHappyHourInfo.fArmorEnchantRate = fTmp; // 2013-08-22 by bhsohn ���Ǿƿ� ������

		if(fTmp >0)
		{
			sprintf(szNotice, STRMSG_C_130822_0005,(fTmp)*100.0f);
			m_vecEventHappyHour.push_back(szNotice);
		}
	}
	{
		// Etc ��þƮ ����Ȯ��
		fTmp = m_HappyEventInfo.fETCItemEnchantRate +m_HappyEventAllInfluInfo.fETCItemEnchantRate+m_PCHappyEventInfo.fETCItemEnchantRate
				+m_MotherShipEventInfo.fETCItemEnchantRate +m_ItemEventInfo.fETCItemEnchantRate;		
		
		struAllHappyHourInfo.fETCItemEnchantRate = fTmp; // 2013-08-22 by bhsohn ���Ǿƿ� ������

		if(fTmp >0)
		{
			sprintf(szNotice, STRMSG_C_130822_0006,(fTmp)*100.0f);
			m_vecEventHappyHour.push_back(szNotice);
		}
	}
	{
		// SPI���� ������ ������
		fTmp = m_HappyEventInfo.fSPIDiscountRate +m_HappyEventAllInfluInfo.fSPIDiscountRate+m_PCHappyEventInfo.fSPIDiscountRate
				+m_MotherShipEventInfo.fSPIDiscountRate +m_ItemEventInfo.fSPIDiscountRate;		

		struAllHappyHourInfo.fSPIDiscountRate = fTmp; // 2013-08-22 by bhsohn ���Ǿƿ� ������

		if(fTmp >0)
		{
			sprintf(szNotice, STRMSG_C_130822_0007,(fTmp)*100.0f);
			m_vecEventHappyHour.push_back(szNotice);
		}
	}
	{
		// WP���� ������ ������
		fTmp = m_HappyEventInfo.fWPDiscountRate +m_HappyEventAllInfluInfo.fWPDiscountRate+m_PCHappyEventInfo.fWPDiscountRate
				+m_MotherShipEventInfo.fWPDiscountRate +m_ItemEventInfo.fWPDiscountRate;	
		
		struAllHappyHourInfo.fWPDiscountRate = fTmp; // 2013-08-22 by bhsohn ���Ǿƿ� ������

		if(fTmp >0)
		{
			sprintf(szNotice, STRMSG_C_130822_0008,(fTmp)*100.0f);
			m_vecEventHappyHour.push_back(szNotice);
		}
	}	
	if(g_pGameMain)
	{
		g_pGameMain->SetAllHappyHourInfo(&struAllHappyHourInfo);
	}
#endif
	// END 2013-08-22 by bhsohn ���Ǿƿ� ������ 
	
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFGameMainUnitInfoBar::SetHappyHourPcBang(BOOL bPcBang)
/// \brief		
/// \author		// 2007-11-01 by bhsohn ���� �ƿ�� �̺�Ʈ ó�� ��� ����
/// \date		2007-07-04 ~ 2007-07-04
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMainUnitInfoBar::SetHappyHourPcBang(BOOL bLevelup, BOOL bPcBang, MSG_FC_INFO_GET_HAPPY_HOUR_EVENT_INFO_OK* pMsg)
{
	m_bPcBangHappyHour = bPcBang;

	char szNotice[1024];
	memset(szNotice, 0x00, 1024);
	memset(&m_PCHappyEventInfo,0x00,sizeof(EVENT_INFO));
	
	if(m_bPcBangHappyHour)
	{
		SetHappyHourInfo(bLevelup, pMsg, &m_PCHappyEventInfo);
	}	

	// ���� �ƿ�� ���� ���� 
	UpdateHappyHourTooltip();
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFGameMainUnitInfoBar::SetHappyHourMotherShip(BOOL bPcBang)
/// \brief		// ���� ���� �ƿ��
/// \author		// 2008-05-21 by bhsohn ����, ������ ���� �ƿ�� �߰�
/// \date		2008-05-21 ~ 2008-05-21
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMainUnitInfoBar::SetHappyHourMotherShip(BOOL bLevelup, BOOL bStart, MSG_FC_INFO_GET_HAPPY_HOUR_EVENT_INFO_OK* pMsg)
{
	m_bMotherHappyHour = bStart;

	char szNotice[1024];
	memset(szNotice, 0x00, 1024);
	memset(&m_MotherShipEventInfo,0x00,sizeof(EVENT_INFO));
	
	if(m_bMotherHappyHour)
	{
		SetHappyHourInfo(bLevelup, pMsg, &m_MotherShipEventInfo);
	}	

	// ���� �ƿ�� ���� ���� 
	UpdateHappyHourTooltip();
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFGameMainUnitInfoBar::SetHappyHourItem(BOOL bPcBang)
/// \brief		������ ���� �ƿ��
/// \author		// 2008-05-21 by bhsohn ����, ������ ���� �ƿ�� �߰�
/// \date		2008-05-21 ~ 2008-05-21
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMainUnitInfoBar::SetHappyHourItem(BOOL bLevelup, BOOL bStart, MSG_FC_INFO_GET_HAPPY_HOUR_EVENT_INFO_OK* pMsg)
{
	m_bItemHappyHour = bStart;

	char szNotice[1024];
	memset(szNotice, 0x00, 1024);
	memset(&m_ItemEventInfo,0x00,sizeof(EVENT_INFO));
	
	if(m_bItemHappyHour)
	{
		SetHappyHourInfo(bLevelup, pMsg, &m_ItemEventInfo);
	}	

	// ���� �ƿ�� ���� ���� 
	UpdateHappyHourTooltip();
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFGameMainUnitInfoBar::InitHappyHourInfo()
/// \brief		
/// \author		// 2007-11-01 by bhsohn ���� �ƿ�� �̺�Ʈ ó�� ��� ����
/// \date		2007-11-01 ~ 2007-11-01
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMainUnitInfoBar::InitHappyHourInfo()
{
	m_vecEventHappyHour.clear(); // ���� ���� �ʱ�ȭ

	memset(&m_HappyEventInfo, 0x00, sizeof(EVENT_INFO));				//���� ����
	memset(&m_HappyEventAllInfluInfo, 0x00, sizeof(EVENT_INFO));		// ��ü ����
	memset(&m_PCHappyEventInfo, 0x00, sizeof(EVENT_INFO));				// pc�� 
	
	m_bHappyHourAllInfluence = FALSE;
	m_byHappyHourInfluence = 0x00;
	m_bPcBangHappyHour = FALSE;

	// 2008-05-21 by bhsohn ����, ������ ���� �ƿ�� �߰�
	m_bMotherHappyHour = FALSE;
	memset(&m_MotherShipEventInfo, 0x00, sizeof(EVENT_INFO));

	m_bItemHappyHour = FALSE;
	memset(&m_ItemEventInfo, 0x00, sizeof(EVENT_INFO));
	// end 2008-05-21 by bhsohn ����, ������ ���� �ƿ�� �߰�

}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFGameMainUnitInfoBar::AddGiftMsg(UINT i_NotifyMsgUID,UINT i_CharacterUID,char * NotifyString)
/// \brief		���� �޽����� �߰��Ѵ�.
/// \author		dgwoo
/// \date		2007-11-28 ~ 2007-11-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMainUnitInfoBar::AddGiftMsg(UINT i_nNotifyMsgUID,UINT i_nCharacterUID,char * i_cNotifyString)
{
	GIFT_NOTIFY_MSG stGiftMsg;
	stGiftMsg.NotifyMsgUID = i_nNotifyMsgUID;
	stGiftMsg.CharacterUID = i_nCharacterUID;
	memcpy(stGiftMsg.NotifyMsgString,i_cNotifyString,SIZE_MAX_NOTIFY_MSG_STRING);
	m_vecGiftMsg.push_back(stGiftMsg);
	g_pGameMain->CreateChatChild(STRMSG_C_071129_0100 ,COLOR_ITEM);	
	m_fGiftTime = 0.0f;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFGameMainUnitInfoBar::CreateMsgBox()
/// \brief		�޽��� �ڽ��� ����.
/// \author		dgwoo
/// \date		2007-11-28 ~ 2007-11-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMainUnitInfoBar::CreateMsgBox()
{
	if(m_vecGiftMsg.size())
	{
		vector<GIFT_NOTIFY_MSG>::iterator it = m_vecGiftMsg.begin();
		g_pGameMain->m_pInfWindow->AddMsgBox(it->NotifyMsgString,_Q_GIFT_ITEM_RING_IN,0,0,0,it->NotifyMsgUID);	
	}
}
void CINFGameMainUnitInfoBar::DeleteGiftMsg()
{
	if(m_vecGiftMsg.size())
	{
		vector<GIFT_NOTIFY_MSG>::iterator it = m_vecGiftMsg.begin();
		m_vecGiftMsg.erase(it);
	}
	else
	{
		m_fGiftTime = 0.0f;
	}
}

// 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������
void CINFGameMainUnitInfoBar::SetRestCount(INT nRestCount)
{
	m_nRestCount = nRestCount;
}
void CINFGameMainUnitInfoBar::SetKillCount(INT nKillCount)
{
	m_nKillCount = nKillCount;
	if(m_nKillCount == KILLCOUNT_MAX_COUNT)
	{
		m_bCompleteKillCount = true;
		m_nCompleteKillCountBlank = 0;
		m_nCompleteKillCountAlpha = 0;
		m_fKillCountScale = KILLCOUNT2_SCALE;
	}
	else if(m_nKillCount > KILLCOUNT_SHOW_HIGHLIGHT_COUNT)
	{
		m_bChangeKillCount = true;
		m_fKillCountScale = KILLCOUNT_SCALE_MAX;
	}

}
void CINFGameMainUnitInfoBar::SetBonusExpRate(INT nPartyRate,INT nFriendRate,INT nGuildRate)
{
//	m_fPartyRate = fPartyRate;
	m_nFriendRate = nFriendRate;
	m_nGuildRate = nGuildRate;
}
// 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������

// 2012-11-16 by mspark, ��ī�� ��� ǥ�� ������
void CINFGameMainUnitInfoBar::RestCountImageOnOff()
{
	if(!m_bCheckRestCountON && m_fPlusRestCountPosX <= RESTCOUNT_IMAGE_POS_LIMIT)
	{
		m_fPlusRestCountPosX = m_fPlusRestCountPosX + RESTKILLCOUNT_IMAGE_MOVE_VALUE;
	}
	else if(m_bCheckRestCountON && m_fPlusRestCountPosX > 0)
	{
		m_fPlusRestCountPosX = m_fPlusRestCountPosX - RESTKILLCOUNT_IMAGE_MOVE_VALUE;
	}
}

void CINFGameMainUnitInfoBar::KillCountImageOnOff()
{
	if(!m_bCheckKillCountON && m_fPlusKillCountPosX <= KILLCOUNT_IMAGE_POS_LIMIT)
	{
		m_fPlusKillCountPosX = m_fPlusKillCountPosX + RESTKILLCOUNT_IMAGE_MOVE_VALUE;
	}
	else if(m_bCheckKillCountON && m_fPlusKillCountPosX > 0)
	{
		m_fPlusKillCountPosX = m_fPlusKillCountPosX - RESTKILLCOUNT_IMAGE_MOVE_VALUE;
	}
}
// end 2012-11-16 by mspark, ��ī�� ��� ǥ�� ������


// 2013. 04. 04 by ssjung ���ʽ� EXP , �ɹ��� �� ���콺�� ������ ���� �� �ý��� �޽����� ǥ�� ���ϰ� ����
BOOL CINFGameMainUnitInfoBar::GetRenderBonusExpRateTextOnOff()
{
	return m_bRenderBonusExpRateText;
}
BOOL CINFGameMainUnitInfoBar::GetRenderPremiumToolTipTextOnOff()
{
	return m_bPremiumToolTip;
}
// 2013. 04. 04 by ssjung ���ʽ� EXP, ����� �� ���콺�� ������ ���� �� �ý��� �޽����� ǥ�� ���ϰ� ����

// 2014-12-08 by shchoi �ѱ��� ��ī�� �ູ, ��� ���� ���� ǥ�� // 2013-07-15 by ssjung ĳ���� ��ī�� �ູ, ��� ���� ���� ǥ��
void CINFGameMainUnitInfoBar::DecaToolTipFunction(BOOL nMode, int nY)	//TRUE�� ��ī�� �ູ FALSE�� ��ī�� ��� 
{
#ifdef C_DECA_TOOLTIP
	char buf[128] = {0,};
	int nX = g_pD3dApp->GetBackBufferDesc().Width;
	
	if(nMode)
		sprintf(buf,STRMSG_C_130627_0001);	//"\\g��ī�� �ູ\\g ��� ����� ������ 35%%�� �߰� ����ġ�� ���޵˴ϴ�. �ູ�� �α׾ƿ� ���¿��� ȸ���˴ϴ�."

	else
		sprintf(buf,STRMSG_C_130627_0002);	//"\\e��ī�� ���\\e ���͸� 300���� óġ�� ��� ����ġ 35%% ���� �������� ȹ���� �� �ֽ��ϴ�."

	int leng = m_pFontDecaToolTip->GetStringSize(buf).cx + 10;
	if(nX + leng > g_pD3dApp->GetBackBufferDesc().Width)
	{
		nX = g_pD3dApp->GetBackBufferDesc().Width - leng;
	}
	g_pGameMain->RenderPopUpWindowImage(nX, nY-13, leng, 1);
	m_pFontDecaToolTip->DrawText(nX, nY-GAMEMAIN_EVENT_FONT_Y-13, GUI_FONT_COLOR_W, buf);
#endif
}
// 2014-12-08 by shchoi �ѱ��� ��ī�� �ູ, ��� ���� ���� ǥ�� // end 2013-07-15 by ssjung ĳ���� ��ī�� �ູ, ��� ���� ���� ǥ��