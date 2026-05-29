// INFGameMainChat.cpp: implementation of the CINFGameMainChat class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "INFGameMainChat.h"
#include "INFGameMainWisperChat.h"
#include "AtumApplication.h"
#include "EnemyData.h"
#include "INFImage.h"
#include "D3DHanFont.h"
#include "GameDataLast.h"
#include "SceneData.h"
#include "ShuttleChild.h"
#include "CharacterChild.h"				// 2005-07-21 by ispark

// 2007-11-22 by bhsohn �Ʒ��� ���ռ���
#include "IMSocketManager.h"
//#include "IMSocket.h"

#include "Chat.h"
#include "FieldWinSocket.h"
#include "INFGameMain.h"
#include "INFWindow.h"
#include "INFCommunity.h"
#include "INFCommunityParty.h"
#include "INFCommunityGuild.h"
#include "INFCommunityReject.h"
#include "INFCommunityFriend.h"
#include "INFCommunityVOIP.h"
#include "Interface.h"
#include "INFTarget.h"
#include "AtumSound.h"
#include "ClientParty.h"
#include "ObjectChild.h"
#include "Skill.h"
#include "INFOtherCharInfo.h"
#include "dxutil.h"
#include "INFGameMainFAQ.h"
#include "INFCityBase.h"
#include "AtumDatabase.h"
#include "INFTrade.h"
#include "CInput.h"
#include "INFMotherShipManager.h"

#include "TutorialSystem.h"	// 2008-10-20 by bhsohn FAQ ��ü ���¿����� �Ⱥ��̰� ����

// 2010. 04. 09 by ckPark Ŭ���̾�Ʈ ���ö����� ���� �߰�
#include "LocalizeSetting.h"
// end 2010. 04. 09 by ckPark Ŭ���̾�Ʈ ���ö����� ���� �߰�

#include "CustomOptimizer.h"

// 2011. 10. 10 by jskim UI�ý��� ����
#include "INFImageList.h"
#include "INFImageEx.h"
#include "INFGroupImage.h"
#include "INFGroupManager.h"		  
// end 2011. 10. 10 by jskim UI�ý��� ����
#include "INFToolTip.h"			// 2011. 1. 12 by jskim UI �̹��� ��ư ���� ����

#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
// �߰� ���� ä��
	// ä�� â�κ��� CHAT_INPUT_WINDOW_X������ ��ġ�� ��������
	#define CHAT_WINDOW_X			2//25												// ä�� �Է�â 
	#define CHAT_WINDOW_Y			(g_pD3dApp->GetBackBufferDesc().Height - 34)//27)	// ä�� �Է�â
	//#define CHAT_WINDOW_W			210 
	//#define CHAT_WINDOW_H			22

	#define CHAT_INPUT_WINDOW_X			(CHAT_WINDOW_X+50)
	#define CHAT_INPUT_WINDOW_Y			(CHAT_WINDOW_Y)
	#define CHAT_INPUT_WINDOW_W			240
	#define CHAT_INPUT_WINDOW_H			20


	#define CHAT_CHATTAB_VIEW_FLAG_X	(CHAT_WINDOW_X+329)//329)						// ä��â �ִ�ȭ �̹���
	#define CHAT_CHATTAB_VIEW_FLAG_Y	(CHAT_WINDOW_Y)//-7)							// ä��â �ִ�ȭ �̹���
	#define CHAT_CHATTAB_VIEW_FLAG_W	15												// ä��â �ִ�ȭ �̹���
	#define CHAT_CHATTAB_VIEW_FLAG_H	21												// ä��â �ִ�ȭ �̹���

	#define CHAT_MENU_VIEW_X			(CHAT_WINDOW_X - 1)								// ä�� �޴� ���̱�
	#define CHAT_MENU_VIEW_Y			(CHAT_WINDOW_Y)								// ä�� �޴� ���̱�
	#define CHAT_MENU_VIEW_W			21												// ä�� �޴� ���̱�
	#define CHAT_MENU_VIEW_H			22												// ä�� �޴� ���̱�

	#define CHAT_MENU_LIST_START_X		(CHAT_WINDOW_X+10)							// ä�� �޴� ���� ��ġ
	#define CHAT_MENU_LIST_START_Y		(CHAT_WINDOW_Y-1)							// ä�� �޴� ���� ��ġ

	#define CHAT_MENU_LIST_W			150												// �޴� ����Ʈ ����
	#define CHAT_MENU_LIST_H			18												// �޴� ����Ʈ ����

	#define CHAT_NMENU_BUTTON_STATE_NOM	0		
	#define CHAT_NMENU_BUTTON_STATE_OVE	1
	#define CHAT_NMENU_BUTTON_STATE_PUH	2

	#define CHAT_CASH_BUTTON_STATE_NOM	3		
	#define CHAT_CASH_BUTTON_STATE_OVE	0
	#define CHAT_CASH_BUTTON_STATE_PUH	1

	#define CHAT_NFONT_START_LINE_X		5												// ä�� ������ ���� ����
	#define CHAT_NFONT_START_LINE_Y		(CHAT_FONT_START_Y-21)								// ä�� ������ ���� ����
	// ��Ÿ �޴� ����
	//#define CHAT_OTHER_MENU_VOIP		(CHAT_TAB_NUMBER)
	//#define CHAT_OTHER_MENU_FAQ			(CHAT_TAB_NUMBER+1)								// ��Ÿ FAQ �޴�
	//#define CHAT_OTHER_MENU_PAYITEM		(CHAT_TAB_NUMBER+2)								// ��Ÿ ���� ������

	#define CHAT_HELPDESK_STRLEN		280//50											// ���� ���ڸ���(�ȼ������� ����)

	#define CHAR_INF_CANDIDATE_POS_X	3
	#define CHAR_INF_CANDIDATE_POS_Y	(g_pD3dApp->GetBackBufferDesc().Height-35)

	#define CHAT_INPUT_LANGUAGE_X		(CHAT_WINDOW_X+21)//224
	#define CHAT_INPUT_LANGUAGE_Y		(CHAT_WINDOW_Y)
	#define CHAT_INPUT_LANGUAGE_WH		20

	// 2008-05-08 by dgwoo ä�� �ý��� ���� �ҽ� �߰�.
	#define CHAT_CHATMODE_Y				(CHAT_WINDOW_Y - 20)
	#define CHAT_CHATMODE_X				(CHAT_WINDOW_X)
	#define CHAT_CHATMODE_GAP			37

	#define CHAT_MACRO_W				(305)
	#define CHAT_MACRO_H				(223)
	#define CHAT_MACRO_BAR_W			(305)
	#define CHAT_MACRO_BAR_H			(27)
	#define CHAT_MACRO_INPUT_1_X		(m_nMacroX + 25)
	#define CHAT_MACRO_INPUT_1_Y		(m_nMacroY + 70)
	#define CHAT_MACRO_INPUT_2_X		(m_nMacroX + 25)
	#define CHAT_MACRO_INPUT_2_Y		(m_nMacroY + 101)
	#define CHAT_MACRO_INPUT_3_X		(m_nMacroX + 25)
	#define CHAT_MACRO_INPUT_3_Y		(m_nMacroY + 130)
	#define CHAT_MACRO_INPUT_W			(194)
	#define CHAT_MACRO_INPUT_H			(20)

	#define CHAT_MACRO_APPL_1_X			(m_nMacroX + 224)
	#define CHAT_MACRO_APPL_1_Y			(m_nMacroY + 68)
	#define CHAT_MACRO_APPL_2_X			(m_nMacroX + 224)
	#define CHAT_MACRO_APPL_2_Y			(m_nMacroY + 97)
	#define CHAT_MACRO_APPL_3_X			(m_nMacroX + 224)
	#define CHAT_MACRO_APPL_3_Y			(m_nMacroY + 126)
	#define CHAT_MACRO_APPL_GAP_Y		29

	#ifdef GAMEFORGE4D_CHAT_MACRO_OUTPUT_TIME
		#define CHAT_MACRO_OUTPUT_TIME		300.0f // 2013-07-30 by ssjung ���� ���� �� ��� ��ũ�� ������ 15�� ���� 5������ ����
	#else
		#define CHAT_MACRO_OUTPUT_TIME		15.0f // 2012-03-30 by isshin ��ũ�� �ý��� ���� ����- ��� ���� �ð�
	#endif

	#define CHAT_MACRO_OK_X				(m_nMacroX + 229)
	#define CHAT_MACRO_OK_Y				(m_nMacroY + 192)
	#define CHAT_MACRO_CANCEL_X			(m_nMacroX + 270)
	#define CHAT_MACRO_CANCEL_Y			(m_nMacroY + 192)

	#define VOICECHAT_BAR_W				305
	#define VOICECHAT_BAR_H				43

	#define VOICECHAT_PARTY_POS_X		(205 + m_nVCCPosX)
	#define VOICECHAT_PARTY_POS_Y		(46 + m_nVCCPosY)
	#define VOICECHAT_GUILD_POS_X		(205 + m_nVCCPosX)
	#define VOICECHAT_GUILD_POS_Y		(68 + m_nVCCPosY)
	#define VOICECHAT_CHATROOM_POS_X	(205 + m_nVCCPosX)
	#define VOICECHAT_CHATROOM_POS_Y	(90 + m_nVCCPosY)
	#define VOICECHAT_WHISPER_POS_X		(205 + m_nVCCPosX)
	#define VOICECHAT_WHISPER_POS_Y		(112 + m_nVCCPosY)

	#define VOICECHAT_INPUT_KEY_POS_X   (41 + m_nVCCPosX)
	#define VOICECHAT_INPUT_KEY_POS_Y   (150 + m_nVCCPosY)
	#define VOICECHAT_INPUT_FREE_POS_X  (41 + m_nVCCPosX)
	#define VOICECHAT_INPUT_FREE_POS_Y  (168 + m_nVCCPosY)

	#define VOICECHAT_SPK_POS_X			(m_nVCCPosX + 50)
	#define VOICECHAT_SPK_POS_Y			(m_nVCCPosY + 188)
	#define VOICECHAT_SPK_W				65
	#define VOICECHAT_SPK_CONTROL_TIME_GAP		0.25f

	#define VOICECHAT_INV_BTN_POS_X		(m_nVCCPosX + 168)
	#define VOICECHAT_INV_BTN_POS_Y		(m_nVCCPosY + 216)
	#define VOICECHAT_OK_BTN_POS_X		(m_nVCCPosX + 209)
	#define VOICECHAT_OK_BTN_POS_Y		(m_nVCCPosY + 216)
	#define VOICECHAT_CAN_BTN_POS_X		(m_nVCCPosX + 250)
	#define VOICECHAT_CAN_BTN_POS_Y		(m_nVCCPosY + 216)

	// 2008-08-18 by bhsohn ��ũ�� �߰� ����
	#define CHATMACRO_TRANSCHAT_COUNT	11

	#define  ENCODE_STRING "562C50434D0A4A5D2A47454E3841444E4F1B0115021B185C5552"		// 2011-11-01 by jhahn ��ȣȭ ó��
	#define  KEY_STRING		"!@#$%^&*@#$%^&*()yerijk0095634^%g"							// 2011-11-01 by jhahn ��ȣȭ ó��

// 2006-03-07 by ispark, �� ���� ��ġ ����
	#if defined(LANGUAGE_ENGLISH) || defined(LANGUAGE_VIETNAM)|| defined(LANGUAGE_THAI)// 2008-04-30 by bhsohn �±� ���� �߰�
		#define STRING_CULL ::StringCullingUserData_ToBlank
		#define STRING_CULL2 ::StringCullingUserData_ToBlank
		#define CHAT_STRING_LENGTH			(m_nChatBoxWidth - 11)
		#define FONT_INPUT_Y				CHAT_WINDOW_Y + 2
	#else
		#define STRING_CULL ::StringCullingUserDataEx
		#define STRING_CULL2 ::StringCullingUserDataEx
		//#define CHAT_STRING_LENGTH			((m_nChatBoxWidth-11)/CHAT_FONT_WIDTH_ENGLISH)
		#define CHAT_STRING_LENGTH			(m_nChatBoxWidth - 11)
		#define FONT_INPUT_Y				CHAT_WINDOW_Y + 2
	#endif
#else 
	// �߰� ���� ä��
// ä�� â�κ��� CHAT_INPUT_WINDOW_X������ ��ġ�� ��������
#define CHAT_WINDOW_X			3//25												// ä�� �Է�â 
#define CHAT_WINDOW_Y			(g_pD3dApp->GetBackBufferDesc().Height - 20)//27)	// ä�� �Է�â
//#define CHAT_WINDOW_W			210 
//#define CHAT_WINDOW_H			22

#define CHAT_INPUT_WINDOW_X			(CHAT_WINDOW_X+50)
#define CHAT_INPUT_WINDOW_Y			(CHAT_WINDOW_Y)
#define CHAT_INPUT_WINDOW_W			240
#define CHAT_INPUT_WINDOW_H			20


#define CHAT_CHATTAB_VIEW_FLAG_X	(CHAT_WINDOW_X+325)//329)						// ä��â �ִ�ȭ �̹���
#define CHAT_CHATTAB_VIEW_FLAG_Y	(CHAT_WINDOW_Y)//-7)							// ä��â �ִ�ȭ �̹���
#define CHAT_CHATTAB_VIEW_FLAG_W	15												// ä��â �ִ�ȭ �̹���
#define CHAT_CHATTAB_VIEW_FLAG_H	21												// ä��â �ִ�ȭ �̹���

#define CHAT_MENU_VIEW_X			(CHAT_WINDOW_X+3)											// ä�� �޴� ���̱�
#define CHAT_MENU_VIEW_Y			(CHAT_WINDOW_Y+2)		// ä�� �޴� ���̱�
#define CHAT_MENU_VIEW_W			21												// ä�� �޴� ���̱�
#define CHAT_MENU_VIEW_H			22												// ä�� �޴� ���̱�

#define CHAT_MENU_LIST_START_X		(CHAT_WINDOW_X+10)							// ä�� �޴� ���� ��ġ
#define CHAT_MENU_LIST_START_Y		(CHAT_WINDOW_Y-1)							// ä�� �޴� ���� ��ġ

#define CHAT_MENU_LIST_W			150												// �޴� ����Ʈ ����
#define CHAT_MENU_LIST_H			18												// �޴� ����Ʈ ����

#define CHAT_NMENU_BUTTON_STATE_NOM	0		
#define CHAT_NMENU_BUTTON_STATE_OVE	1
#define CHAT_NMENU_BUTTON_STATE_PUH	2

#define CHAT_CASH_BUTTON_STATE_NOM	3		
#define CHAT_CASH_BUTTON_STATE_OVE	0
#define CHAT_CASH_BUTTON_STATE_PUH	1

#define CHAT_NFONT_START_LINE_X		5												// ä�� ������ ���� ����
#define CHAT_NFONT_START_LINE_Y		(CHAT_FONT_START_Y-21)								// ä�� ������ ���� ����
// ��Ÿ �޴� ����
//#define CHAT_OTHER_MENU_VOIP		(CHAT_TAB_NUMBER)
//#define CHAT_OTHER_MENU_FAQ			(CHAT_TAB_NUMBER+1)								// ��Ÿ FAQ �޴�
//#define CHAT_OTHER_MENU_PAYITEM		(CHAT_TAB_NUMBER+2)								// ��Ÿ ���� ������

#define CHAT_HELPDESK_STRLEN		280//50											// ���� ���ڸ���(�ȼ������� ����)

#define CHAR_INF_CANDIDATE_POS_X	3
#define CHAR_INF_CANDIDATE_POS_Y	(g_pD3dApp->GetBackBufferDesc().Height-35)

#define CHAT_INPUT_LANGUAGE_X		(CHAT_WINDOW_X+21)//224
#define CHAT_INPUT_LANGUAGE_Y		(CHAT_WINDOW_Y+2)
#define CHAT_INPUT_LANGUAGE_WH		20

// 2008-05-08 by dgwoo ä�� �ý��� ���� �ҽ� �߰�.
#define CHAT_CHATMODE_Y				(CHAT_WINDOW_Y - 17)
#define CHAT_CHATMODE_X				(CHAT_WINDOW_X)
#define CHAT_CHATMODE_GAP			37

#define CHAT_MACRO_W				(305)
#define CHAT_MACRO_H				(223)
#define CHAT_MACRO_BAR_W			(305)
#define CHAT_MACRO_BAR_H			(27)
#define CHAT_MACRO_INPUT_1_X		(m_nMacroX + 25)
#define CHAT_MACRO_INPUT_1_Y		(m_nMacroY + 70)
#define CHAT_MACRO_INPUT_2_X		(m_nMacroX + 25)
#define CHAT_MACRO_INPUT_2_Y		(m_nMacroY + 101)
#define CHAT_MACRO_INPUT_3_X		(m_nMacroX + 25)
#define CHAT_MACRO_INPUT_3_Y		(m_nMacroY + 130)
#define CHAT_MACRO_INPUT_W			(194)
#define CHAT_MACRO_INPUT_H			(20)

#define CHAT_MACRO_APPL_1_X			(m_nMacroX + 224)
#define CHAT_MACRO_APPL_1_Y			(m_nMacroY + 68)
#define CHAT_MACRO_APPL_2_X			(m_nMacroX + 224)
#define CHAT_MACRO_APPL_2_Y			(m_nMacroY + 97)
#define CHAT_MACRO_APPL_3_X			(m_nMacroX + 224)
#define CHAT_MACRO_APPL_3_Y			(m_nMacroY + 126)
#define CHAT_MACRO_APPL_GAP_Y		29

#ifdef GAMEFORGE4D_CHAT_MACRO_OUTPUT_TIME
	#define CHAT_MACRO_OUTPUT_TIME		300.0f // 2013-07-30 by ssjung ���� ���� �� ��� ��ũ�� ������ 15�� ���� 5������ ����
#else
	#define CHAT_MACRO_OUTPUT_TIME		15.0f // 2012-03-30 by isshin ��ũ�� �ý��� ���� ����- ��� ���� �ð�
#endif

#define CHAT_MACRO_OK_X				(m_nMacroX + 209)
#define CHAT_MACRO_OK_Y				(m_nMacroY + 199)
#define CHAT_MACRO_CANCEL_X			(m_nMacroX + 250)
#define CHAT_MACRO_CANCEL_Y			(m_nMacroY + 199)

#define VOICECHAT_BAR_W				305
#define VOICECHAT_BAR_H				43

#define VOICECHAT_PARTY_POS_X		(198 + m_nVCCPosX)
#define VOICECHAT_PARTY_POS_Y		(46 + m_nVCCPosY)
#define VOICECHAT_GUILD_POS_X		(198 + m_nVCCPosX)
#define VOICECHAT_GUILD_POS_Y		(68 + m_nVCCPosY)
#define VOICECHAT_CHATROOM_POS_X	(198 + m_nVCCPosX)
#define VOICECHAT_CHATROOM_POS_Y	(90 + m_nVCCPosY)
#define VOICECHAT_WHISPER_POS_X		(198 + m_nVCCPosX)
#define VOICECHAT_WHISPER_POS_Y		(112 + m_nVCCPosY)

#define VOICECHAT_INPUT_KEY_POS_X   (41 + m_nVCCPosX)
#define VOICECHAT_INPUT_KEY_POS_Y   (150 + m_nVCCPosY)
#define VOICECHAT_INPUT_FREE_POS_X  (41 + m_nVCCPosX)
#define VOICECHAT_INPUT_FREE_POS_Y  (168 + m_nVCCPosY)

#define VOICECHAT_SPK_POS_X			(m_nVCCPosX + 62)
#define VOICECHAT_SPK_POS_Y			(m_nVCCPosY + 188)
#define VOICECHAT_SPK_W				65
#define VOICECHAT_SPK_CONTROL_TIME_GAP		0.25f

#define VOICECHAT_INV_BTN_POS_X		(m_nVCCPosX + 101)
#define VOICECHAT_INV_BTN_POS_Y		(m_nVCCPosY + 216)
#define VOICECHAT_OK_BTN_POS_X		(m_nVCCPosX + 209)
#define VOICECHAT_OK_BTN_POS_Y		(m_nVCCPosY + 216)
#define VOICECHAT_CAN_BTN_POS_X		(m_nVCCPosX + 250)
#define VOICECHAT_CAN_BTN_POS_Y		(m_nVCCPosY + 216)

	#define  ENCODE_STRING "562C50434D0A4A5D2A47454E3841444E4F1B0115021B185C5552"		// 2011-11-01 by jhahn ��ȣȭ ó��
	#define  KEY_STRING		"!@#$%^&*@#$%^&*()yerijk0095634^%g"							// 2011-11-01 by jhahn ��ȣȭ ó��

// 2008-08-18 by bhsohn ��ũ�� �߰� ����
#define CHATMACRO_TRANSCHAT_COUNT	11

// 2006-03-07 by ispark, �� ���� ��ġ ����
#if defined(LANGUAGE_ENGLISH) || defined(LANGUAGE_VIETNAM)|| defined(LANGUAGE_THAI)// 2008-04-30 by bhsohn �±� ���� �߰�
	#define STRING_CULL ::StringCullingUserData_ToBlank
	#define STRING_CULL2 ::StringCullingUserData_ToBlank
#define CHAT_STRING_LENGTH			(m_nChatBoxWidth - 11)
#define FONT_INPUT_Y				6
#else
#define STRING_CULL ::StringCullingUserDataEx
#define STRING_CULL2 ::StringCullingUserDataEx
//#define CHAT_STRING_LENGTH			((m_nChatBoxWidth-11)/CHAT_FONT_WIDTH_ENGLISH)
#define CHAT_STRING_LENGTH			(m_nChatBoxWidth - 11)
#define FONT_INPUT_Y				6
#endif

#endif
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// 2009. 02. 03 by ckPark ä��â �������̽� ũ�� ����
//CINFGameMainChat::CINFGameMainChat(CAtumNode* pParent)
CINFGameMainChat::CINFGameMainChat(CAtumNode* pParent, int nWidth, int nHeight)
// end 2009. 02. 03 by ckPark ä��â �������̽� ũ�� ����
{
	FLOG( "CINFGameMainChat(CAtumNode* pParent)" );

	m_pParent = pParent;

	int i=0, j=0;
	m_pGameData = NULL;

	for(i=0;i<9;i++)
	{
		m_pChatBox[i] = NULL;
	}
	for(i=0;i<3;i++)
	{
		m_pScrollLine[i] = NULL;
	}
	for(i=0;i<2;i++)
	{
		for(j=0;j<BUTTON_BOTH_STATE_NUMBER;j++)
		{
			m_pChatViewButton[i][j] = NULL;
			m_pImgWisperBtn[i][j] = NULL;
		}
	}

	m_pScrollButton = NULL;
	m_pChatShowImage = NULL;
//	m_nSizeMaxButtonstate = CHAT_BUTTON_NORMAL;
//	m_nSizeMinButtonstate = CHAT_BUTTON_NORMAL;
	m_nChatSizeBtnNormal  = BUTTON_BOTH_STATE_NORMAL;

	// 2009. 02. 03 by ckPark ä��â �������̽� ũ�� ����
// 	m_nChatBoxWidth		  = CHAT_CHATBOX_START_DEFAULT_MIN_X+100;
// 	m_nChatBoxHeight	  = CHAT_CHATBOX_START_DEFAULT_MIN_Y;

	if(nWidth <= 0 || nHeight <= 0)
	{
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
		m_nChatBoxWidth	  = CHAT_CHATBOX_START_DEFAULT_MIN_X+38;
#else							   
		m_nChatBoxWidth	  = CHAT_CHATBOX_START_DEFAULT_MIN_X+100;

#endif
		m_nChatBoxHeight  = CHAT_CHATBOX_START_DEFAULT_MIN_Y;
	}
	else
	{
		m_nChatBoxWidth	  = nWidth;
		m_nChatBoxHeight  = nHeight;
	}
	// end 2009. 02. 03 by ckPark ä��â �������̽� ũ�� ����


	m_nChatBoxYPos	  = 0;

	m_bLockSoundButton = FALSE;	
	m_bShowChatBox = FALSE;
	m_bWindowSizeMax = FALSE;
	m_bWindowSizeMin = FALSE;
	m_bLockHandle = FALSE;
	m_bScrollLock = FALSE;

	m_ptMouse.x = 0;
	m_ptMouse.y = 0;
	m_nTransChatCount = CHATMACRO_TRANSCHAT_COUNT;

	m_nCurrentTabIndex	  = CHAT_TAB_NORMAL;
	memset(&m_ArrChatTab, 0x00, sizeof(ChatTab_t));
	memset(&m_ArrChatTabMode, 0x00, sizeof(ChatTab_t)*CHAT_TAB_SAVE_COUNT);
	m_nCurrentRelScrollPosY			= m_nChatBoxHeight-CHATBOX_SCROLL_IMAGE_SIZE_HEIGHT;
	m_nCurrentRelScrollOldPosY		= m_nCurrentRelScrollPosY;

// by cmkwon
//	memset(m_nCurrentScrollHeight,0x00, CHAT_TAB_NUMBER*sizeof(int));	
	memset(m_strInputMessage, 0x00, sizeof(m_strInputMessage));

	// 2010. 04. 01 by ckPark ä��â �޸� �ʱ�ȭ ���� ����
	//memset(m_fTimeOfShowChat,0x00, CHAT_TAB_NUMBER*CHAT_NOT_SHOWBOX_LINE*sizeof(float));
	memset( m_fTimeOfShowChat, 0x00, CHAT_NOT_SHOWBOX_LINE * sizeof(float) );
	// end 2010. 04. 01 by ckPark ä��â �޸� �ʱ�ȭ ���� ����


//	m_nShowTimeChatType	=	0;

	// 2009-03-18 by bhsohn ä��â Ŀ�� �̵� �ý��� �߰�
	InitChatMsgBuff();
	// end 2009-03-18 by bhsohn ä��â Ŀ�� �̵� �ý��� �߰�
	
	m_pFontInput = NULL;	
	m_bChatMode = FALSE;
	m_vectorINFiGameMainWisperChatPtr.clear();
	m_pSystemMsgW						= NULL;
	m_nClickedWisperChatBoxVectorIndex = -1;
	m_nSmallWindowCount					= 0;

	m_nWisperBoxMinimumStatusInitPositionX = 0;
	m_nWisperBoxMinimumStatusInitPositionY = 0;

	memset(m_strMyMent,0x00, 1024);

	// ä�� ���� 2005.01.13 ydkim
	for(i=0; i<CHAT_MENULIST_NUMBER; i++)
		m_bChatCurrentSelect[i] = TRUE;	
//	m_bChatCurrentSelect[CHAT_TAB_NORMAL]	= TRUE;
//	m_bChatCurrentSelect[CHAT_TAB_SYSTEM]	= TRUE;
//	m_bChatCurrentSelect[CHAT_TAB_TRADE]	= FALSE;

	m_nSelectChatTab = CHAT_TAB_NORMAL;
	// 2014-07-01 by ymjoo DrawText ���� ���� �۾� (����)
#ifdef C_DRAWTEXT_UPGRADE_YMJOO
	for(i = 0 ; i < 10 ; ++i)
	{
		m_pFontGM[i] = NULL;
	}
	m_pFontInfl = NULL;
#else
	m_pFontGM = NULL;
#endif
	// END 2014-07-01 by ymjoo DrawText ���� ���� �۾� (����)
	memset(m_strInputGm, 0x00, 1024);
	memset(m_strInputInfluenceLeader, 0x00, 512);
	m_fTimeGm = 0.0f;
	m_fTimeInfluenceLeader = 0.0f;

	// �߰����� 2005.01.21
	for(i=0; i<CHAT_BUTTON_NUMBER3; i++)
	{
		m_pNChatFAQ[i] = NULL;								// ä�� FAQ��ư
		m_pNChatMenuView[i] = NULL;							// ä�� �޴� ���̱� ��ư
		m_pNChatVOIPStartMenu[i] = NULL;					// ä�� VOIP ���� ��ư
		m_pNChatVOIPEndMenu[i] = NULL;						// ä�� VOIP ���� ��ư
	}
#ifndef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	for(i=0; i<CHAT_BUTTON_NUMBER4; i++)
	{
		m_pNChatCash[i] = NULL;								// ä�� ä������ ��ư
 	}
#endif
// 2015-02-04 by jwLee �Ϻ� ĳ���� ����
#if defined(C_CASH_SHOP_NOT_USE_JWLEE)
#else
	for(i=0; i<CHAT_BUTTON_NUMBER4; i++)
	{
		m_pNChatCashView[i] = NULL;
	}
#endif
// end 2015-02-04 by jwLee �Ϻ� ĳ���� ����
	for(i=0; i<INPUT_LANGUAGE_END; i++)
	{
		m_pNChatInputLanguage[i] = NULL;					// ä�� �Է� ���
	}
	for(i=0; i<CHAT_MENULIST_NUMBER; i++)
	{
		m_pNChatMenu[i] = NULL;								// ä�� �޴� ����Ʈ
	}
	m_pNChatInput = NULL;									// ä�� �Է�â
	m_pNChatCheck = NULL;									// ä�� äũ��ũ	
	m_nMenuListButtonState = CHAT_NMENU_BUTTON_STATE_NOM;	// �޴�����Ʈ ��ư ����

	for(i=0; i<CHAT_OTHER_MENU_ALL; i++)
	{
		m_nOtherMenuList[i] = CHAT_NMENU_BUTTON_STATE_NOM;
	}
	m_bShowMacro = FALSE;
	for(i = 0; i < CHAT_MACRO_INPUT_COUNT ; i++)
	{
		m_pBtnChatMacro[i] = NULL;
	}
	m_bGuildQuick			= FALSE;
	m_bPartyQuick			= FALSE;
	m_pBtnGuildQuick		= NULL;
	m_pBtnPartyQuick		= NULL;
	m_pChatMacroBG			= NULL;
	m_pBtnMacroOK			= NULL;
	m_pBtnMacroCancel		= NULL;
	m_pBtnOption			= NULL;

	m_bShowMiniWisper		= TRUE;
	m_bShowMiniWisperUnder	= FALSE;

	m_nActMacro				= -1;
	m_nMacroX				= (g_pD3dApp->GetBackBufferDesc().Width - 305)/2;
	m_nMacroY				= 300;
	m_bMacroMove			= FALSE;
	m_nSendMacroNum			= 0;

	m_bMenuListUse = FALSE;
	m_bMenuList = FALSE;
	m_bCheckShopInfo =FALSE;
	m_bCashShopOpen = FALSE;
	m_nOtherCashList = CHAT_NMENU_BUTTON_STATE_NOM;	
	m_bCashButton = FALSE;
	m_nCashButtonGab = 0;
	m_bPKOptionFlag	 = TRUE;
	m_bTradeFlag	 = TRUE;
	m_bWindowMessageFlag = TRUE;
	m_bHelpDeskRender = FALSE;
	m_bSelectInputLanguage = FALSE;

	m_nVoiceMenu = 0;

	// by bhsohn 2007-03-12 China Working
	m_nChinaCnt = 0;
	m_nMSPYMode =  INPUT_LANGUAGE_CHINA;
	m_nChatMode = CHAT_TAB_ALLUSER;

	m_bShowVoiceChatControl		= FALSE;
	m_nVCCPosX					= (g_pD3dApp->GetBackBufferDesc().Width - 305)/2;
	m_nVCCPosY					= 320;
	m_nVolum					= 9999;
	m_pVoiceChatBG				= NULL;
	m_pBothParty				= NULL;
	m_pBothGuild				= NULL;
	m_pBothChat					= NULL;
	m_pImgSpkVolBar				= NULL;
	m_pImgRadioBtn[0]			= NULL;
	m_pImgRadioBtn[1]			= NULL;
	m_pBothWhisper				= NULL;
	m_pBtnVoiceChatInv			= NULL;
	m_pBtnVoiceChatOk			= NULL;
	m_pBtnVoiceChatCan			= NULL;
	m_bVCCMoving				= FALSE;
	
	// 2008-08-18 by bhsohn ��ũ�� �߰� ����
	m_bMacroIng = FALSE;	
	for(i = 0; i < CHAT_MACRO_INPUT_COUNT; i++)
	{
		memset(&m_sMacroStr[i], 0x00, sizeof(sCHATMACROSTRING));
	}
	memset(m_strTempMacro, 0x00, SIZE_MAX_CHAT_MESSAGE);
	// end 2008-08-18 by bhsohn ��ũ�� �߰� ����



	// 2008. 12. 29 by ckPark ä��â ����ȭ	

	// �� ä�� ���� �ʱ�ȭ
	for(i=0; i<MAX_GAME_MAIN_CHAT_LINE; ++i)
		m_pFontLine[i]	= NULL;

	// end 2008. 12. 29 by ckPark ä��â ����ȭ	
#ifndef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	m_pBtnChatBG = NULL;
#endif

	// 2012-10-31 by jhjang ������ �ʱ�ȭ �ڵ� �߰�
	for(i = 0 ; i < 9 ; i ++)
	{
		m_pBtnChatMode[i] = NULL;
	}
	// end 2012-10-31 by jhjang ������ �ʱ�ȭ �ڵ� �߰�
}

CINFGameMainChat::~CINFGameMainChat()
{
	FLOG( "~CINFGameMainChat()" );
	
	int i=0, j=0;

//	for(i=0;i<5;i++)
//	{
//		for(j=0;j<2;j++)
//		{
//			SAFE_DELETE(m_pTabButton[i][j]);
//		}
//	}
	for(i=0;i<9;i++)
	{
		SAFE_DELETE(m_pChatBox[i]);
	}
	for(i=0;i<3;i++)
	{
		SAFE_DELETE(m_pScrollLine[i]);
	}
	for(i=0;i<2;i++)
	{
		for(j=0;j<BUTTON_BOTH_STATE_NUMBER;j++)
		{
			SAFE_DELETE(m_pChatViewButton[i][j]);
			SAFE_DELETE(m_pImgWisperBtn[i][j]);
		}
	}

	SAFE_DELETE(m_pScrollButton);
	SAFE_DELETE(m_pFontInput);	
	SAFE_DELETE(m_pChatShowImage);

	vectorINFGameMainWisperChatPtr::iterator itt(m_vectorINFiGameMainWisperChatPtr.begin());
	while (itt != m_vectorINFiGameMainWisperChatPtr.end())
	{		
		SAFE_DELETE(*itt);
		itt++;
	}
	m_vectorINFiGameMainWisperChatPtr.clear();

	SAFE_DELETE(m_pSystemMsgW);
	
	vector<CD3DHanFont*>::iterator it = m_vecFontLine.begin();
	while(it != m_vecFontLine.end())
	{
		CD3DHanFont* pFont = *it;
		pFont->InvalidateDeviceObjects();
		pFont->DeleteDeviceObjects();
		delete pFont;
		pFont = NULL;
		it++;
	}
	m_vecFontLine.clear();
	// 2014-07-01 by ymjoo DrawText ���� ���� �۾� (����)
#ifdef C_DRAWTEXT_UPGRADE_YMJOO
	for(i = 0 ; i < 10 ; ++i)
	{
		SAFE_DELETE(m_pFontGM[i]);
	}
	SAFE_DELETE(m_pFontInfl);
#else
	SAFE_DELETE(m_pFontGM);
#endif
	// END 2014-07-01 by ymjoo DrawText ���� ���� �۾� (����)

	// �߰����� 2005.01.21
	for(i=0; i<CHAT_BUTTON_NUMBER3; i++)
	{
		SAFE_DELETE(m_pNChatFAQ[i]);								// ä�� FAQ��ư
		SAFE_DELETE(m_pNChatMenuView[i]);							// ä�� �޴� ���̱� ��ư
		SAFE_DELETE(m_pNChatVOIPStartMenu[i]);						// ä�� VOIP ���� ��ư
		SAFE_DELETE(m_pNChatVOIPEndMenu[i]);						// ä�� VOIP ���� ��ư
	}
#ifndef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	for(i=0; i<CHAT_BUTTON_NUMBER4; i++)
	{
		SAFE_DELETE(m_pNChatCash[i]);								// ä�� ä������ ��ư
	}
#endif
// 2015-02-04 by jwLee �Ϻ� ĳ���� ����
#if defined(C_CASH_SHOP_NOT_USE_JWLEE)
#else
	for(i=0; i<CHAT_BUTTON_NUMBER4; i++)
	{
		SAFE_DELETE(m_pNChatCashView[i]);
 	}
#endif
// end 2015-02-04 by jwLee �Ϻ� ĳ���� ����
	for(i=0; i<INPUT_LANGUAGE_END; i++)
	{
		SAFE_DELETE(m_pNChatInputLanguage[i]);						// ä�� �Է� ���
	}
	for(i=0; i<CHAT_MENULIST_NUMBER; i++)
	{
		SAFE_DELETE(m_pNChatMenu[i]);								// ä�� �޴� ����Ʈ
	}
	SAFE_DELETE(m_pNChatInput);									// ä�� �Է�â
	SAFE_DELETE(m_pNChatCheck);									// ä�� äũ��ũ

	for(i = 0; i < CHAT_MACRO_INPUT_COUNT ; i++)
	{
		SAFE_DELETE(m_pBtnChatMacro[i]);
	}
	SAFE_DELETE(m_pChatMacroBG);
	SAFE_DELETE(m_pBtnMacroOK);
	SAFE_DELETE(m_pBtnMacroCancel);
	SAFE_DELETE(m_pBtnOption);

	// 2008. 12. 29 by ckPark ä��â ����ȭ	
	
	// �� ä�� ���� ����
	for(i=0; i<MAX_GAME_MAIN_CHAT_LINE; ++i)
		SAFE_DELETE(m_pFontLine[i]);
		
	// end 2008. 12. 29 by ckPark ä��â ����ȭ	
#ifndef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	SAFE_DELETE( m_pBtnChatBG );
#endif
}

void CINFGameMainChat::InitChatData()
{
	vectorINFGameMainWisperChatPtr::iterator itt(m_vectorINFiGameMainWisperChatPtr.begin());
	while (itt != m_vectorINFiGameMainWisperChatPtr.end())
	{		
		SAFE_DELETE(*itt);
		itt++;
	}
	m_vectorINFiGameMainWisperChatPtr.clear();
	
	m_nCurrentTabIndex	  = CHAT_TAB_NORMAL;
	memset(&m_ArrChatTab, 0x00, sizeof(ChatTab_t));
	memset(&m_ArrChatTabMode, 0x00, sizeof(ChatTab_t)*CHAT_TAB_SAVE_COUNT);
	memset(m_fTimeOfShowChat,0x00, CHAT_NOT_SHOWBOX_LINE*sizeof(float));

}

void CINFGameMainChat::AddBuffer(int nType, char* strBuffer, DWORD dwColorType, char* szWisperToCharacterName, char *szWisperFromCharacterName)
{
	FLOG( "CINFGameMainChat::AddBuffer(int nType, char* strBuffer, DWORD dwColorType)");
	
	/////////////////////////////////////////////////////////////////////////////////////
	// ä�� �ý��� ���� 05.01.21
	// �⺻ Ÿ���� (�ý��� 4) ���� �Ѵ�
	// ���� ä�ð� �Ӽ� ���� 0 �Ϲ� äƼ���� �Ѵ�
	// �� �� ��Ÿ ���, ��Ƽ, �Ÿ� ä�õ� 
	int i=0;
	if(FALSE == this->IsValidTabIndex(nType)){						return;}

	// �Ӹ� ä��
	if(CHAT_TAB_NORMAL == nType || CHAT_TAB_CASH == nType)
	{
		for(i = CHAT_NOT_SHOWBOX_LINE - 1 ; i > 0;i--)
		{
			m_fTimeOfShowChat[i] = m_fTimeOfShowChat[i-1];
		}
		m_fTimeOfShowChat[0] = CHAT_TIME_OF_NOT_SHOW_BOX;
		if(m_bChatCurrentSelect[CHAT_TAB_NORMAL] == TRUE)
			m_ArrChatTab.PushChatLine(strBuffer, dwColorType,nType);
		m_ArrChatTabMode[CHAT_TAB_NORMAL].PushChatLine(strBuffer, dwColorType,nType);
	}
	else if(CHAT_TAB_PTOP == nType)
	{
		for(i = CHAT_NOT_SHOWBOX_LINE - 1 ; i > 0;i--)
		{
			m_fTimeOfShowChat[i] = m_fTimeOfShowChat[i-1];
		}
		m_fTimeOfShowChat[0] = CHAT_TIME_OF_NOT_SHOW_BOX;

		ProcessWisperChatAddLine(strBuffer, dwColorType, szWisperToCharacterName, szWisperFromCharacterName);
		m_ArrChatTab.PushChatLine(strBuffer, dwColorType,nType);
	}
	else if(CHAT_TAB_SOUND == nType)
	{
		for(i = CHAT_NOT_SHOWBOX_LINE - 1 ; i > 0;i--)
		{
			m_fTimeOfShowChat[i] = m_fTimeOfShowChat[i-1];
		}
		m_fTimeOfShowChat[0] = CHAT_TIME_OF_NOT_SHOW_BOX;

		if(m_bChatCurrentSelect[CHAT_TAB_SYSTEM] == TRUE)
			m_ArrChatTab.PushChatLine(strBuffer, dwColorType,nType);
		m_ArrChatTabMode[CHAT_TAB_SYSTEM].PushChatLine(strBuffer, dwColorType,nType);
	}
	else if(CHAT_TAB_SYSTEM == nType)
	{
		for(i = CHAT_NOT_SHOWBOX_LINE - 1 ; i > 0;i--)
		{
			m_pSystemMsgW->m_fTimeOfShowChat[i] = m_pSystemMsgW->m_fTimeOfShowChat[i-1];
		}
		m_pSystemMsgW->m_fTimeOfShowChat[0] = CHAT_TIME_OF_NOT_SHOW_BOX;

		m_pSystemMsgW->AddBuffer(strBuffer,dwColorType);

	}
	// 2008-08-14 by dgwoo �ŷ�ä�� ��ũ�� ��ȣ�� ����.
	else if(nType == CHAT_TAB_TRADE)
	{
		for(i = CHAT_NOT_SHOWBOX_LINE - 1 ; i > 0;i--)
		{
			m_fTimeOfShowChat[i] = m_fTimeOfShowChat[i-1];
		}
		m_fTimeOfShowChat[0] = CHAT_TIME_OF_NOT_SHOW_BOX;
		if(m_bChatCurrentSelect[nType] == TRUE)
			m_ArrChatTab.PushChatLine(strBuffer, dwColorType,nType);
		m_ArrChatTabMode[nType].PushChatLine(strBuffer, dwColorType,nType);
		// 2008-08-18 by bhsohn ��ũ�� �߰� ����
		if(m_bMacroIng)
		{
			if(m_nTransChatCount < CHATMACRO_TRANSCHAT_COUNT)
			{
				// ��ũ�� ���� ���� ���� ����
				m_nTransChatCount++;
			}
		}
	}
	else if(nType != CHAT_TAB_HELPDESK)
	{
		for(i = CHAT_NOT_SHOWBOX_LINE - 1 ; i > 0;i--)
		{
			m_fTimeOfShowChat[i] = m_fTimeOfShowChat[i-1];
		}
		m_fTimeOfShowChat[0] = CHAT_TIME_OF_NOT_SHOW_BOX;
		if(m_bChatCurrentSelect[nType] == TRUE)
			m_ArrChatTab.PushChatLine(strBuffer, dwColorType,nType);
		m_ArrChatTabMode[nType].PushChatLine(strBuffer, dwColorType,nType);
	}
	
	// GM��
	if(nType == CHAT_TAB_GAMEMASTER)
	{
		m_bHelpDeskRender = FALSE;
		memset(m_strInputGm, 0x00, 1024);
		strncpy(m_strInputGm, strBuffer, CHAT_STRING_SIZE_GM);
		// �ð� �ʱ�ȭ
		m_fTimeGm = CHAT_TIME_OF_NOT_SHOW_BOX_GM;
		
		for(i = CHAT_NOT_SHOWBOX_LINE - 1 ; i > 0;i--)
		{
			m_fTimeOfShowChat[i] = m_fTimeOfShowChat[i-1];
		}
		m_fTimeOfShowChat[0] = CHAT_TIME_OF_NOT_SHOW_BOX;
		m_ArrChatTab.PushChatLine(strBuffer, dwColorType,nType);
		for(int i = 0;i <CHAT_TAB_SAVE_COUNT ; i++)
		{
			if((i == CHAT_TAB_PARTY && g_pShuttleChild->m_pClientParty->IsParty() == TRUE) ||
				(i == CHAT_TAB_GUILD && g_pShuttleChild->GetMyShuttleInfo().GuildUniqueNumber != 0 ))

			m_ArrChatTabMode[i].PushChatLine(strBuffer, dwColorType,nType);
		}
	}
	else if(m_bChatCurrentSelect[CHAT_TAB_HELPDESK] == TRUE && nType == CHAT_TAB_HELPDESK)
	{
		m_bHelpDeskRender = TRUE;
		memset(m_strInputGm, 0x00, 1024);
//		strncpy(m_strInputGm, strBuffer, CHAT_STRING_SIZE_GM);
		// �ð� �ʱ�ȭ
		m_fTimeGm = CHAT_TIME_OF_NOT_SHOW_BOX_GM;

		strncpy(m_strInputGm, strBuffer, 1024);
	}
	// 2006-04-21 by ispark, �����ڿ�
	else if(nType == CHAT_TAB_INFLUENCE_LEADER)
	{
		memset(m_strInputInfluenceLeader, 0x00, 512);
		strncpy(m_strInputInfluenceLeader, strBuffer, CHAT_STRING_SIZE_GM);
		// �ð� �ʱ�ȭ
		m_fTimeInfluenceLeader = CHAT_TIME_OF_NOT_SHOW_BOX_GM;
		
		for(i = CHAT_NOT_SHOWBOX_LINE - 1 ; i > 0;i--)
		{
			m_fTimeOfShowChat[i] = m_fTimeOfShowChat[i-1];
		}
		m_fTimeOfShowChat[0] = CHAT_TIME_OF_NOT_SHOW_BOX;
		m_ArrChatTab.PushChatLine(strBuffer, dwColorType,nType);
		m_ArrChatTabMode[CHAT_TAB_WAR].PushChatLine(strBuffer, dwColorType,nType);
	}
	//
	//////////////////////////////////////////////////////////////////////////////////

	if(FALSE == m_bScrollLock)
	{
		ChatTab_t *pChatTab = GetChatTabMode();
		m_nCurrentRelScrollPosY = CHATBOX_IMAGE_GAB_HEITHT_TOP +
			pChatTab->GetScrollPositionWithRenderStartIndex(m_nChatBoxHeight-(CHATBOX_IMAGE_GAB_HEITHT_TOP+CHATBOX_SCROLL_IMAGE_SIZE_HEIGHT)
				, (m_nChatBoxHeight-CHATBOX_IMAGE_GAB_HEITHT_TOP)/CHAT_FONT_LINE_HEIGHT);
	}



	// 2008. 12. 29 by ckPark ä��â ����ȭ	
	// ���� �߰��� �ø��� ��Ʈ�� �ʱ�ȭ
	m_listCulledString.clear();
	// end 2008. 12. 29 by ckPark ä��â ����ȭ	
}

void CINFGameMainChat::ResetHanFontLine()
{
	FLOG( "CINFGameMainChat::ResetHanFontLine()" );
	vector<CD3DHanFont*>::iterator it = m_vecFontLine.begin();
	while(it != m_vecFontLine.end())
	{
		CD3DHanFont* pFont = *it;
		it++;
		pFont->InvalidateDeviceObjects();
		pFont->DeleteDeviceObjects();
		delete pFont;
		pFont = NULL;
	}
	m_vecFontLine.clear();

	int i; for(i=0;i<(CHAT_CHATBOX_START_DEFAULT_MAX_Y/CHAT_FONT_LINE_HEIGHT);i++)
	{
		CD3DHanFont* pFont = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE,TRUE,1024,32,FALSE,TRUE);	//	��Ʈ ���� 
		pFont->InitDeviceObjects(g_pD3dDev);
		pFont->RestoreDeviceObjects();
		
		//m_nChatBoxHeight - 18*2 - 30

		if(m_bShowChatBox) {
			pFont->SetUV(0.0f,0.0f,(float)(m_nChatBoxWidth - CHATBOX_IMAGE_GAB_WIDTH_BOTTOM)/1024.0f, 1.0f); }
		else {
			pFont->SetUV(0.0f,0.0f,1.0f, 1.0f); }
		m_vecFontLine.push_back(pFont);
	}
	float fTemp = 1.0f;
	for(i=0;i<CHAT_NOT_SHOWBOX_LINE;i++)
	{
		m_fTimeOfShowChat[i] = CHAT_TIME_OF_NOT_SHOW_BOX - fTemp*i;
	}
	for(i = 0; i < CHAT_TAB_CHATROOM ; i++)
	{
		if(NULL != m_pBtnChatMode[i])
		{
			m_pBtnChatMode[i]->RestoreDeviceObjects();	
		}
	}
	{
		if(NULL != m_pBtnGuildQuick)
		{
			m_pBtnGuildQuick->RestoreDeviceObjects();
		}
		if(NULL != m_pBtnPartyQuick)
		{
			m_pBtnPartyQuick->RestoreDeviceObjects();
		}
	}
}


HRESULT CINFGameMainChat::InitDeviceObjects()
{
	FLOG( "CINFGameMainChat::InitDeviceObjects()" );
	DataHeader	* pDataHeader ;
	char buf[16];

//	int i; for(i=0;i<5;i++)
//	{
//		for(int j=0;j<2;j++)
//		{
//			wsprintf(buf, "c_btn%d%d", i+1,j); 
//			m_pTabButton[i][j] = new CINFImage;
//			pDataHeader = FindResource(buf);
//			m_pTabButton[i][j]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;
//		}
//	}
// 2011. 10. 10 by jskim UI�ý��� ����
	int i; for(i=0;i<BUTTON_BOTH_STATE_NUMBER;i++)
	{
		m_pChatViewButton[0][i] = new CINFImageEx;
		wsprintf(buf, "c_hsbtn0%d",i);
		pDataHeader = FindResource(buf);
		m_pChatViewButton[0][i]->InitDeviceObjects( pDataHeader ) ;
		
		m_pChatViewButton[1][i] = new CINFImageEx;
		wsprintf(buf, "c_hsbtn1%d",i);
		pDataHeader = FindResource(buf);
		m_pChatViewButton[1][i]->InitDeviceObjects( pDataHeader ) ;

		m_pImgWisperBtn[0][i] = new CINFImageEx;
		wsprintf(buf, "wispbar0%d",i);
		pDataHeader = FindResource(buf);
		m_pImgWisperBtn[0][i]->InitDeviceObjects( pDataHeader ) ;
		
		m_pImgWisperBtn[1][i] = new CINFImageEx;
		wsprintf(buf, "wispbar1%d",i);
		pDataHeader = FindResource(buf);
		m_pImgWisperBtn[1][i]->InitDeviceObjects( pDataHeader ) ;
	}

	for(i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			m_pChatBox[i*3+j] = new CINFImageEx;
			wsprintf(buf, "c_c%d%d", i,j);
			pDataHeader = FindResource(buf);
			m_pChatBox[i*3+j]->InitDeviceObjects( pDataHeader ) ;			
		}
	}
	for(i=0;i<3;i++)
	{
		m_pScrollLine[i] = new CINFImageEx;
		wsprintf(buf, "c_s%d", i);
		pDataHeader = FindResource(buf);
		m_pScrollLine[i]->InitDeviceObjects( pDataHeader ) ;
	
	}
	m_pScrollButton = new CINFImageEx;
	pDataHeader = FindResource("c_scrlb");
	m_pScrollButton->InitDeviceObjects( pDataHeader ) ;
	
	m_pChatShowImage= new CINFImageEx;
	pDataHeader = FindResource("Chatmage");
	m_pChatShowImage->InitDeviceObjects( pDataHeader ) ;
	
	m_pFontInput = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,1024,32,TRUE);
	m_pFontInput->InitDeviceObjects(g_pD3dDev);
	
	// 2014-07-01 by ymjoo DrawText ���� ���� �۾� (����)
#ifdef C_DRAWTEXT_UPGRADE_YMJOO
	for(i = 0 ; i < 10 ; ++i)
	{
		m_pFontGM[i] = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()), 9, D3DFONT_ZENABLE, TRUE, 1024, 32);
		m_pFontGM[i]->InitDeviceObjects(g_pD3dDev);
	}
	m_pFontInfl = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()), 9, D3DFONT_ZENABLE, TRUE, 1024, 32);
	m_pFontInfl->InitDeviceObjects(g_pD3dDev);
#else
 	m_pFontGM = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,1024,32);
 	m_pFontGM->InitDeviceObjects(g_pD3dDev);
#endif
	// END 2014-07-01 by ymjoo DrawText ���� ���� �۾� (����)

	// �߰����� 2005.01.21
	for(i=0; i<CHAT_BUTTON_NUMBER3; i++)
	{
		m_pNChatFAQ[i] = new CINFImageEx;
		wsprintf(buf, "c_nfa%d", i);						// ä�� FAQ��ư
		pDataHeader = FindResource(buf);
		m_pNChatFAQ[i]->InitDeviceObjects( pDataHeader ) ;
		
		m_pNChatMenuView[i] = new CINFImageEx;
		wsprintf(buf, "c_nme%d", i);						// ä�� �޴� ���̱� ��ư
		pDataHeader = FindResource(buf);
		m_pNChatMenuView[i]->InitDeviceObjects( pDataHeader ) ;

		m_pNChatVOIPStartMenu[i] = new CINFImageEx;
		wsprintf(buf, "c_von%d", i);						// ä�� VOIP ���� �޴� ���̱� ��ư
		pDataHeader = FindResource(buf);
		m_pNChatVOIPStartMenu[i]->InitDeviceObjects( pDataHeader ) ;

		m_pNChatVOIPEndMenu[i] = new CINFImageEx;
		wsprintf(buf, "c_vof%d", i);						// ä��  VOIP ���� �޴� ���̱� ��ư
		pDataHeader = FindResource(buf);
		m_pNChatVOIPEndMenu[i]->InitDeviceObjects( pDataHeader ) ;
	}
	for(i=0; i<CHAT_BUTTON_NUMBER4; i++)
	{
#ifndef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
 		m_pNChatCash[i] = new CINFImageEx;
		wsprintf(buf, "c_nca%d", i);						// ä�� ä������ ��ư
		pDataHeader = FindResource(buf);
 		m_pNChatCash[i]->InitDeviceObjects( pDataHeader ) ;
#endif
// 2015-02-04 by jwLee �Ϻ� ĳ���� ����
#if defined(C_CASH_SHOP_NOT_USE_JWLEE)
#else
		// 2006-06-08 by ispark, ���� ���� ��ư ����
		m_pNChatCashView[i] = new CINFImageEx;
//		wsprintf(buf, "cc_sh%d", i);						// ä�� ä������ ��ư
		wsprintf(buf, "shbtn100%d", i);						
		pDataHeader = FindResource(buf);
		m_pNChatCashView[i]->InitDeviceObjects( pDataHeader ) ;
#endif
// end 2015-02-04 by jwLee �Ϻ� ĳ���� ����
	}

	for(i = 0; i <INPUT_LANGUAGE_END;i++)
	{
		m_pNChatInputLanguage[i] = new CINFImageEx;
		wsprintf(buf, "lang_%d", i+1);
		pDataHeader = FindResource(buf);
		m_pNChatInputLanguage[i]->InitDeviceObjects( pDataHeader );
	}
	for(i=0; i<CHAT_MENULIST_NUMBER; i++)
	{
		m_pNChatMenu[i] = new CINFImageEx;
		wsprintf(buf, "chat_li%d", i);						// ä�� �޴� ����Ʈ
		pDataHeader = FindResource(buf);
		m_pNChatMenu[i]->InitDeviceObjects( pDataHeader ) ;									
	}

	m_pNChatInput = new CINFImageEx;
	pDataHeader = FindResource("c_nbar");						// ä�� �Է�â
	m_pNChatInput->InitDeviceObjects( pDataHeader ) ;
	
	m_pNChatCheck = new CINFImageEx;
	pDataHeader = FindResource("c_nchk");						// ä�� äũ��ũ
	m_pNChatCheck->InitDeviceObjects( pDataHeader ) ;

	// 2007-08-07 by bhsohn ����Ŀ ������ �߰�
	//for(i=0; i<CHAT_TAB_NUMBER; i++)
	for(i=0; i<CHAT_MENULIST_NUMBER; i++)
	{
		m_bChatCurrentSelect[i] = g_pSOption->m_bChatCurrentSelect[i];
	}	
	m_bChatCurrentSelect[CHAT_TAB_SPEAKER] = g_pInterface->GetSpeakerMode();
	// end 2007-08-07 by bhsohn ����Ŀ ������ �߰�

	// 2008-05-08 by dgwoo ä�� �ý��� ���� �ҽ� �߰�.
	{
		char szButtonName[32];
		for(i = 0; i < CHAT_TAB_CHATROOM ; i++)
		{
			wsprintf(szButtonName, "cicon_li%d",i+1);
			if(NULL == m_pBtnChatMode[i])
			{
				m_pBtnChatMode[i] = new CINFImageBtn;
				m_pBtnChatMode[i]->EnableBtn(TRUE);
			}
			m_pBtnChatMode[i]->InitDeviceObjects(szButtonName);	
		}
		wsprintf(szButtonName,"Pquick");
		if(NULL == m_pBtnPartyQuick)
		{
			m_pBtnPartyQuick = new CINFImageBtn;
		}
		m_pBtnPartyQuick->InitDeviceObjects(szButtonName);
		wsprintf(szButtonName,"Gquick");
		if(NULL == m_pBtnGuildQuick)
		{
			m_pBtnGuildQuick = new CINFImageBtn;
		}
		m_pBtnGuildQuick->InitDeviceObjects(szButtonName);

		// Setting
		m_pBtnChatMode[0]->PushButton(TRUE);
		// �Ʒ���, ä�ù��� �⺻ ��Ȱ��ȭ.
//		m_pBtnChatMode[ChangeChatButtonNumber(CHAT_TAB_GUILD)]->EnableBtn(FALSE);
//		m_pBtnChatMode[ChangeChatButtonNumber(CHAT_TAB_PARTY)]->EnableBtn(FALSE);
		m_pBtnChatMode[ChangeChatButtonNumber(CHAT_TAB_ARENA)]->EnableBtn(FALSE);
		m_pBtnChatMode[ChangeChatButtonNumber(CHAT_TAB_CHATROOM)]->EnableBtn(FALSE);

		// 2008-11-24 by dgwoo �Ʒ��� ä�� �� Ȱ��ȭ �ȵǴ� ����
		CFieldWinSocket* pArenaFieldSocket = g_pD3dApp->m_pFieldWinSocket->GetArenaFieldWinSocket();
		if(pArenaFieldSocket)
		{
			// �Ʒ��� ���Ͽ� ����Ǿ������� 
			m_pBtnChatMode[ChangeChatButtonNumber(CHAT_TAB_ARENA)]->EnableBtn(TRUE);
		}
		// end 2008-11-24 by dgwoo �Ʒ��� ä�� �� Ȱ��ȭ �ȵǴ� ����

#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
		pDataHeader = g_pGameMain->m_GruopImagemanager->FindResource("macro");
		m_pChatMacroBG = g_pGameMain->m_GruopImagemanager->GetGroupImage(pDataHeader);
		m_pChatMacroBG->InitDeviceObjects( g_pD3dApp->m_pImageList );		

		if(NULL == m_pBtnMacroOK)
		{
			m_pBtnMacroOK = new CINFImageBtn;
		}
		m_pBtnMacroOK->InitDeviceObjects("oks0");
		if(NULL == m_pBtnMacroCancel)
		{
			m_pBtnMacroCancel = new CINFImageBtn;
		}
		m_pBtnMacroCancel->InitDeviceObjects("cans0");			 
#else
		if(NULL == m_pChatMacroBG)
		{
			m_pChatMacroBG = new CINFImageEx;
		}
		pDataHeader = FindResource("chatmacro");						
		m_pChatMacroBG->InitDeviceObjects( pDataHeader ) ;

		if(NULL == m_pBtnMacroOK)
		{
			m_pBtnMacroOK = new CINFImageBtn;
		}
		m_pBtnMacroOK->InitDeviceObjects("shlaok0");
		if(NULL == m_pBtnMacroCancel)
		{
			m_pBtnMacroCancel = new CINFImageBtn;
		}
		m_pBtnMacroCancel->InitDeviceObjects("shmcan0");
#endif		
		for(i = 0 ; i < CHAT_MACRO_INPUT_COUNT ; i++)
		{
			wsprintf(szButtonName, "macroappl");
			if(NULL == m_pBtnChatMacro[i])
			{
				m_pBtnChatMacro[i] = new CINFImageBtnBoth;
			}
			m_pBtnChatMacro[i]->InitDeviceObjects(szButtonName);
		}

		if(NULL == m_pBtnOption)
		{
			m_pBtnOption = new CINFImageBtn;
		}
		// 2011. 1. 12 by jskim UI �̹��� ��ư ���� ����
		//m_pBtnOption->InitDeviceObjects("copticon");
		m_pBtnOption->InitDeviceObjects("copticon","STRTOOLTIP99");
		// 2011. 1. 12 by jskim UI �̹��� ��ư ���� ����
	}
	// ���� �ɼ�.
	{
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
		if(NULL == m_pBtnVoiceChatInv)
		{
			m_pBtnVoiceChatInv = new CINFImageBtn;
		}
		// 2011. 1. 12 by jskim UI �̹��� ��ư ���� ����
		//m_pBtnVoiceChatInv->InitDeviceObjects("invs0");
		m_pBtnVoiceChatInv->InitDeviceObjects("invs0","STRTOOLTIP27");
		// end 2011. 1. 12 by jskim UI �̹��� ��ư ���� ����
		if(NULL == m_pBtnVoiceChatOk)
		{
			m_pBtnVoiceChatOk = new CINFImageBtn;
		}
		// 2011. 1. 12 by jskim UI �̹��� ��ư ���� ����
		//m_pBtnVoiceChatOk->InitDeviceObjects("oks0");
		m_pBtnVoiceChatOk->InitDeviceObjects("oks0","STRTOOLTIP40");
		// end 2011. 1. 12 by jskim UI �̹��� ��ư ���� ����
		if(NULL == m_pBtnVoiceChatCan)
		{
			m_pBtnVoiceChatCan = new CINFImageBtn;
		}
		// 2011. 1. 12 by jskim UI �̹��� ��ư ���� ����
		//m_pBtnVoiceChatCan->InitDeviceObjects("cans0");
		m_pBtnVoiceChatCan->InitDeviceObjects("cans0","STRTOOLTIP41");
		// end 2011. 1. 12 by jskim UI �̹��� ��ư ���� ����
		
		if(NULL == m_pBothParty)
		{
			m_pBothParty = new CINFImageBtnBoth;
		}
#else
		if(NULL == m_pBtnVoiceChatInv)
		{
			m_pBtnVoiceChatInv = new CINFImageBtn;
		}
		m_pBtnVoiceChatInv->InitDeviceObjects("voiceinv");
		if(NULL == m_pBtnVoiceChatOk)
		{
			m_pBtnVoiceChatOk = new CINFImageBtn;
		}
		m_pBtnVoiceChatOk->InitDeviceObjects("shlaok0");
		if(NULL == m_pBtnVoiceChatCan)
		{
			m_pBtnVoiceChatCan = new CINFImageBtn;
		}
		m_pBtnVoiceChatCan->InitDeviceObjects("shmcan0");

		if(NULL == m_pBothParty)
		{
			m_pBothParty = new CINFImageBtnBoth;
		}
#endif
		m_pBothParty->InitDeviceObjects("onoff");
		m_pBothParty->ChangeBoth(BUTTON_BOTH_BACK);
		if(NULL == m_pBothGuild)
		{
			m_pBothGuild = new CINFImageBtnBoth;
		}
		m_pBothGuild->InitDeviceObjects("onoff");
		m_pBothGuild->ChangeBoth(BUTTON_BOTH_BACK);
		if(NULL == m_pBothChat)
		{
			m_pBothChat = new CINFImageBtnBoth;
		}
		m_pBothChat->InitDeviceObjects("onoff");
		m_pBothChat->ChangeBoth(BUTTON_BOTH_BACK);
		if(NULL == m_pBothWhisper)
		{
			m_pBothWhisper = new CINFImageBtnBoth;
		}
		m_pBothWhisper->InitDeviceObjects("onoff");
		m_pBothWhisper->ChangeBoth(BUTTON_BOTH_BACK);

// 2011. 10. 10 by jskim UI�ý��� ����
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
		pDataHeader = g_pGameMain->m_GruopImagemanager->FindResource("voiceChat");
		m_pVoiceChatBG = g_pGameMain->m_GruopImagemanager->GetGroupImage(pDataHeader);
		m_pVoiceChatBG->InitDeviceObjects( g_pD3dApp->m_pImageList );
#else
		m_pVoiceChatBG = new CINFImageEx;
		pDataHeader = FindResource("voptBG");
		m_pVoiceChatBG->InitDeviceObjects( pDataHeader );
#endif
		m_pImgSpkVolBar = new CINFImageEx;
		pDataHeader = FindResource("scrl_b");
		m_pImgSpkVolBar->InitDeviceObjects( pDataHeader );
		m_pImgRadioBtn[0] = new CINFImageEx;
		pDataHeader = FindResource("radio_b");
		m_pImgRadioBtn[0]->InitDeviceObjects( pDataHeader );
		m_pImgRadioBtn[1] = new CINFImageEx;
		pDataHeader = FindResource("radio_a");
		m_pImgRadioBtn[1]->InitDeviceObjects( pDataHeader );
	}
	if(m_pSystemMsgW == NULL)
	{
		// 2008-06-20 by bhsohn EP3 �ɼǰ��� ó��
		//m_pSystemMsgW = new CINFSystemMsgWindow(this);
		int nStartX, nStartY, nWidth, nHeight;
		nStartX = nStartY = nWidth = nHeight = -1;		
		if(g_pD3dApp->IsOptionEtc(OPTION_RADIO_INTERFACE_POS))
		{
			float fWidth = (float)g_pD3dApp->GetBackBufferDesc().Width;
			float fHeight = (float)g_pD3dApp->GetBackBufferDesc().Height;

			stcuctRateRect stRateRect = g_pD3dApp->GetOptionInterfacePOS();
			if((stRateRect.fGameWidth == fWidth)
					&&(stRateRect.fGameHeight == fHeight))
			{
				nStartX = stRateRect.fRateX;
				nStartY = stRateRect.fRateY;
				nWidth	= stRateRect.fRateWidth;
				nHeight	= stRateRect.fRateHeight;
			}
			else
			{				
				float fRateWidth = (fWidth/stRateRect.fGameWidth);
				float fRateHeight = (fHeight/stRateRect.fGameHeight);
				if(fRateWidth == 0 )
				{					
					fRateWidth = 1;
				}
				if(fRateHeight == 0)
				{					
					fRateHeight = 1;
				}
				nStartX = (int)(stRateRect.fRateX*fRateWidth);
				nStartY = (int)(stRateRect.fRateY*fRateHeight);
				nWidth	= (int)(stRateRect.fRateWidth*fRateWidth);
				nHeight	= (int)(stRateRect.fRateHeight*fRateHeight);	
			}				
		}
		
		m_pSystemMsgW = new CINFSystemMsgWindow(this, nStartX, nStartY, nWidth, nHeight);
		m_pSystemMsgW->SetInterface(m_bChatCurrentSelect[CHAT_TAB_SYSTEM]);
		// end 2008-06-20 by bhsohn EP3 �ɼǰ��� ó��

		m_pSystemMsgW->SetGameData(m_pGameData);
		m_pSystemMsgW->InitDeviceObjects();
	}


	
	
	// 2008. 12. 29 by ckPark ä��â ����ȭ
	// �� ���� �ø� ��Ʈ�� ����
	for(i=0; i<MAX_GAME_MAIN_CHAT_LINE; ++i)
	{
		m_pFontLine[i] = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE,TRUE,1024,32,FALSE,TRUE);
		m_pFontLine[i]->InitDeviceObjects(g_pD3dDev);
		m_pFontLine[i]->RestoreDeviceObjects();

		if(m_bShowChatBox)
			m_pFontLine[i]->SetUV(0.0f,0.0f,(float)(m_nChatBoxWidth - CHATBOX_IMAGE_GAB_WIDTH_BOTTOM)/1024.0f, 1.0f);
		else
			m_pFontLine[i]->SetUV(0.0f,0.0f,1.0f, 1.0f);
	}

	// end 2008. 12. 29 by ckPark ä��â ����ȭ	
 #ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	pDataHeader = g_pGameMain->m_GruopImagemanager->FindResource("BGbox");
	m_pBtnChatBG = g_pGameMain->m_GruopImagemanager->GetGroupImage( pDataHeader );
#endif
	return S_OK ;
}

// 2007-08-07 by bhsohn ����Ŀ ������ �߰�
//int CINFGameMainChat::GetRealPos(int nPos)
//{
//	int nPosTab = CHAT_TAB_NUMBER-1;
//	switch(nPos)
//	{
//	case CHAT_TAB_SPEAKER:
//		{
//			nPosTab = CHAT_TAB_NUMBER-1;
//		}
//		break;
//	}
//	return nPosTab;
//}

HRESULT CINFGameMainChat::RestoreDeviceObjects()
{
	FLOG( "CINFGameMainChat::RestoreDeviceObjects()" );
//	int i; for(i=0;i<5;i++)
//	{
//		for(int j=0;j<2;j++)
//		{
//			m_pTabButton[i][j]->RestoreDeviceObjects();
//		}
//	}
	int i; for(i=0;i<9;i++)
	{
		m_pChatBox[i]->RestoreDeviceObjects();
	}
	for(i=0;i<3;i++)
	{
		m_pScrollLine[i]->RestoreDeviceObjects();
	}
	m_pScrollButton->RestoreDeviceObjects();
	m_pChatShowImage->RestoreDeviceObjects();
	for(i=0;i<BUTTON_BOTH_STATE_NUMBER;i++)
	{
		m_pChatViewButton[0][i]->RestoreDeviceObjects();
		m_pChatViewButton[1][i]->RestoreDeviceObjects();
		m_pImgWisperBtn[0][i]->RestoreDeviceObjects();
		m_pImgWisperBtn[1][i]->RestoreDeviceObjects();
	}

	m_pFontInput->RestoreDeviceObjects();	
	ResetHanFontLine();

	vectorINFGameMainWisperChatPtr::iterator it(m_vectorINFiGameMainWisperChatPtr.begin());
	while (it != m_vectorINFiGameMainWisperChatPtr.end())
	{
		(*it)->RestoreDeviceObjects();	
		it++;
	}
	m_pSystemMsgW->RestoreDeviceObjects();
	// 2014-07-01 by ymjoo DrawText ���� ���� �۾� (����)
#ifdef C_DRAWTEXT_UPGRADE_YMJOO
	for(i = 0 ; i < 10 ; ++i)
	{
		m_pFontGM[i]->RestoreDeviceObjects();
	}
	m_pFontInfl->RestoreDeviceObjects();
#else
	m_pFontGM->RestoreDeviceObjects();
#endif
	// END 2014-07-01 by ymjoo DrawText ���� ���� �۾� (����)

	// �߰����� 2005.01.21
	for(i=0; i<CHAT_BUTTON_NUMBER3; i++)
	{
		m_pNChatFAQ[i]->RestoreDeviceObjects();								// ä�� FAQ��ư
		m_pNChatMenuView[i]->RestoreDeviceObjects();						// ä�� �޴� ���̱� ��ư
		m_pNChatVOIPStartMenu[i]->RestoreDeviceObjects();
		m_pNChatVOIPEndMenu[i]->RestoreDeviceObjects();
	}
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
#else
	for(i=0; i<CHAT_BUTTON_NUMBER4; i++)
	{
		m_pNChatCash[i]->RestoreDeviceObjects();							// ä�� ä������ ��ư
 	}																							  
#endif
// 2015-02-04 by jwLee �Ϻ� ĳ���� ����
#if defined(C_CASH_SHOP_NOT_USE_JWLEE)
#else
	for(i=0; i<CHAT_BUTTON_NUMBER4; i++)
	{
		m_pNChatCashView[i]->RestoreDeviceObjects();
	}
#endif
// end 2015-02-04 by jwLee �Ϻ� ĳ���� ����
	for(i=0; i<INPUT_LANGUAGE_END; i++)
	{
		m_pNChatInputLanguage[i]->RestoreDeviceObjects();
	}
	for(i=0; i<CHAT_MENULIST_NUMBER; i++)
	{
		m_pNChatMenu[i]->RestoreDeviceObjects();							// ä�� �޴� ����Ʈ
	}
	m_pNChatInput->RestoreDeviceObjects();									// ä�� �Է�â
	m_pNChatCheck->RestoreDeviceObjects();									// ä�� äũ��ũ

	for(i = 0; i < CHAT_TAB_CHATROOM ; i++)
	{
		m_pBtnChatMode[i]->RestoreDeviceObjects();	
		m_pBtnChatMode[i]->SetBtnPosition(CHAT_CHATMODE_X + (CHAT_CHATMODE_GAP * i),CHAT_CHATMODE_Y);
	}

	m_pBtnGuildQuick->RestoreDeviceObjects();
	m_pBtnPartyQuick->RestoreDeviceObjects();
	

	m_pChatMacroBG->RestoreDeviceObjects();

	for(i = 0 ; i < CHAT_MACRO_INPUT_COUNT ; i++)
	{
		m_pBtnChatMacro[i]->RestoreDeviceObjects();
	}
	m_pBtnMacroOK->RestoreDeviceObjects();
	m_pBtnMacroCancel->RestoreDeviceObjects();
	m_pBtnOption->RestoreDeviceObjects();
	m_pBtnOption->SetBtnPosition(CHAT_OPTION_BUTTON_X,CHAT_OPTION_BUTTON_Y);


	{
		m_pBtnVoiceChatInv->RestoreDeviceObjects();
		m_pBtnVoiceChatOk->RestoreDeviceObjects();
		m_pBtnVoiceChatCan->RestoreDeviceObjects();

		m_pBothParty->RestoreDeviceObjects();
		m_pBothGuild->RestoreDeviceObjects();
		m_pBothChat->RestoreDeviceObjects();
		m_pBothWhisper->RestoreDeviceObjects();

		m_pVoiceChatBG->RestoreDeviceObjects();
		m_pImgSpkVolBar->RestoreDeviceObjects();
		m_pImgRadioBtn[0]->RestoreDeviceObjects();
		m_pImgRadioBtn[1]->RestoreDeviceObjects();

	}

	// 2007-11-05 by bhsohn ���� ������Ʈ üũ�� ó��
	// ��ü�� �����Ǳ� ���� ��� �۾��� �ִ´�.
	g_pD3dApp->m_pChat->ErrorInfoAllAddChat();


	
	// 2008. 12. 29 by ckPark ä��â ����ȭ	
	// �� ä�� ���� ����
	for(i=0; i<MAX_GAME_MAIN_CHAT_LINE; ++i)
		m_pFontLine[i]->RestoreDeviceObjects();

	// end 2008. 12. 29 by ckPark ä��â ����ȭ	

#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	m_pBtnChatBG->RestoreDeviceObjects();														  
#endif

	return S_OK ;
}

HRESULT CINFGameMainChat::DeleteDeviceObjects()
{
	FLOG( "CINFGameMainChat::DeleteDeviceObjects()" );
//	int i; for(i=0;i<5;i++)
//	{
//		for(int j=0;j<2;j++)
//		{
//			m_pTabButton[i][j]->DeleteDeviceObjects();
//			SAFE_DELETE(m_pTabButton[i][j]);
//		}
//	}
	int i; for(i=0;i<9;i++)
	{
		m_pChatBox[i]->DeleteDeviceObjects();
		SAFE_DELETE(m_pChatBox[i]);
	}
	for(i=0;i<3;i++)
	{
		m_pScrollLine[i]->DeleteDeviceObjects();
		SAFE_DELETE(m_pScrollLine[i]);
	}
	m_pScrollButton->DeleteDeviceObjects();
	m_pChatShowImage->DeleteDeviceObjects();
	SAFE_DELETE(m_pScrollButton);
	SAFE_DELETE(m_pChatShowImage);	
	for(i=0;i<BUTTON_BOTH_STATE_NUMBER;i++)
	{
		m_pChatViewButton[0][i]->DeleteDeviceObjects();
		m_pChatViewButton[1][i]->DeleteDeviceObjects();
		SAFE_DELETE(m_pChatViewButton[0][i]);
		SAFE_DELETE(m_pChatViewButton[1][i]);
		m_pImgWisperBtn[0][i]->DeleteDeviceObjects();
		m_pImgWisperBtn[1][i]->DeleteDeviceObjects();
		SAFE_DELETE(m_pImgWisperBtn[0][i]);
		SAFE_DELETE(m_pImgWisperBtn[1][i]);
	}

	m_pFontInput->DeleteDeviceObjects();
	SAFE_DELETE(m_pFontInput);	

	vectorINFGameMainWisperChatPtr::iterator it(m_vectorINFiGameMainWisperChatPtr.begin());
	while (it != m_vectorINFiGameMainWisperChatPtr.end())
	{
		(*it)->DeleteDeviceObjects();
		SAFE_DELETE(*it);
		it++;
	}
	m_vectorINFiGameMainWisperChatPtr.clear();

 	m_pSystemMsgW->DeleteDeviceObjects();
	SAFE_DELETE(m_pSystemMsgW);

	// 2014-07-01 by ymjoo DrawText ���� ���� �۾� (����)
#ifdef C_DRAWTEXT_UPGRADE_YMJOO
	for(i = 0 ; i < 10 ; ++i)
	{
		m_pFontGM[i]->DeleteDeviceObjects();
		SAFE_DELETE(m_pFontGM[i]);
	}
	m_pFontInfl->DeleteDeviceObjects();
	SAFE_DELETE(m_pFontInfl);
#else
 	m_pFontGM->DeleteDeviceObjects();
 	SAFE_DELETE(m_pFontGM);
#endif
	// END 2014-07-01 by ymjoo DrawText ���� ���� �۾� (����)

	// �߰����� 2005.01.21
	for(i=0; i<CHAT_BUTTON_NUMBER3; i++)
	{
		m_pNChatFAQ[i]->DeleteDeviceObjects();
		m_pNChatMenuView[i]->DeleteDeviceObjects();
		SAFE_DELETE(m_pNChatFAQ[i]);								// ä�� FAQ��ư
		SAFE_DELETE(m_pNChatMenuView[i]);								// ä�� �޴� ���̱� ��ư
		m_pNChatVOIPStartMenu[i]->DeleteDeviceObjects();
		m_pNChatVOIPEndMenu[i]->DeleteDeviceObjects();
		SAFE_DELETE(m_pNChatVOIPStartMenu[i]);
		SAFE_DELETE(m_pNChatVOIPEndMenu[i]);
	}
	for(i=0; i<CHAT_BUTTON_NUMBER4; i++)
	{
#ifndef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
		m_pNChatCash[i]->DeleteDeviceObjects();
		SAFE_DELETE(m_pNChatCash[i]);								// ä�� ä������ ��ư
#endif
// 2015-02-04 by jwLee �Ϻ� ĳ���� ����
#if defined(C_CASH_SHOP_NOT_USE_JWLEE)
#else
		m_pNChatCashView[i]->DeleteDeviceObjects();
		SAFE_DELETE(m_pNChatCashView[i]);
#endif
// end 2015-02-04 by jwLee �Ϻ� ĳ���� ����
	}
	for(i=0; i<INPUT_LANGUAGE_END; i++)
	{
		m_pNChatInputLanguage[i]->DeleteDeviceObjects();			// ä�� �Է� ���
		SAFE_DELETE(m_pNChatInputLanguage[i]);
	}
	for(i=0; i<CHAT_MENULIST_NUMBER; i++)
	{
		m_pNChatMenu[i]->DeleteDeviceObjects();
		SAFE_DELETE(m_pNChatMenu[i]);								// ä�� �޴� ����Ʈ
	}
	m_pNChatInput->DeleteDeviceObjects();
	SAFE_DELETE(m_pNChatInput);									// ä�� �Է�â
	m_pNChatCheck->DeleteDeviceObjects();
	SAFE_DELETE(m_pNChatCheck);									// ä�� äũ��ũ
	
	for(i = 0; i < CHAT_TAB_CHATROOM ; i++)
	{
		if(NULL != m_pBtnChatMode[i])
		{
			m_pBtnChatMode[i]->DeleteDeviceObjects();	
			SAFE_DELETE(m_pBtnChatMode[i]);
		}
	}
	m_pBtnPartyQuick->DeleteDeviceObjects();
	SAFE_DELETE(m_pBtnPartyQuick)
	m_pBtnGuildQuick->DeleteDeviceObjects();
	SAFE_DELETE(m_pBtnGuildQuick)

	m_pChatMacroBG->DeleteDeviceObjects();
	SAFE_DELETE(m_pChatMacroBG);

	for(i = 0 ; i < CHAT_MACRO_INPUT_COUNT ; i++)
	{
		m_pBtnChatMacro[i]->DeleteDeviceObjects();
		SAFE_DELETE(m_pBtnChatMacro[i]);
	}
	m_pBtnMacroOK->DeleteDeviceObjects();
	SAFE_DELETE(m_pBtnMacroOK);
	m_pBtnMacroCancel->DeleteDeviceObjects();
	SAFE_DELETE(m_pBtnMacroCancel);
	m_pBtnOption->DeleteDeviceObjects();
	SAFE_DELETE(m_pBtnOption);
	
	{
		m_pBtnVoiceChatInv->DeleteDeviceObjects();
		SAFE_DELETE(m_pBtnVoiceChatInv);
		m_pBtnVoiceChatOk->DeleteDeviceObjects();
		SAFE_DELETE(m_pBtnVoiceChatOk);
		m_pBtnVoiceChatCan->DeleteDeviceObjects();
		SAFE_DELETE(m_pBtnVoiceChatCan);

		m_pBothParty->DeleteDeviceObjects();
		SAFE_DELETE(m_pBothParty);
		m_pBothGuild->DeleteDeviceObjects();
		SAFE_DELETE(m_pBothGuild);
		m_pBothChat->DeleteDeviceObjects();
		SAFE_DELETE(m_pBothChat);
		m_pBothWhisper->DeleteDeviceObjects();
		SAFE_DELETE(m_pBothWhisper);

		m_pVoiceChatBG->DeleteDeviceObjects();
		SAFE_DELETE(m_pVoiceChatBG);
		m_pImgSpkVolBar->DeleteDeviceObjects();
		SAFE_DELETE(m_pImgSpkVolBar);
		m_pImgRadioBtn[0]->DeleteDeviceObjects();
		SAFE_DELETE(m_pImgRadioBtn[0]);
		m_pImgRadioBtn[1]->DeleteDeviceObjects();
		SAFE_DELETE(m_pImgRadioBtn[1]);

	}


	// 2008. 12. 29 by ckPark ä��â ����ȭ	
	// �� ä�� ���� ����
	for(i=0; i<MAX_GAME_MAIN_CHAT_LINE; ++i)
	{
		m_pFontLine[i]->DeleteDeviceObjects();
		SAFE_DELETE(m_pFontLine[i]);
	}

	// end 2008. 12. 29 by ckPark ä��â ����ȭ	
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	if( m_pBtnChatBG )
	{
		m_pBtnChatBG->DeleteDeviceObjects();
		SAFE_DELETE(m_pBtnChatBG);
	}
#endif
	return S_OK ;
}


HRESULT CINFGameMainChat::InvalidateDeviceObjects()
{
	FLOG( "CINFGameMainChat::InvalidateDeviceObjects()" );
//	int i; for(i=0;i<5;i++)
//	{
//		for(int j=0;j<2;j++)
//		{
//			m_pTabButton[i][j]->InvalidateDeviceObjects();
//		}
//	}
	int i; for(i=0;i<9;i++)
	{
		m_pChatBox[i]->InvalidateDeviceObjects();
	}
	for(i=0;i<3;i++)
	{
		m_pScrollLine[i]->InvalidateDeviceObjects();
	}
	m_pScrollButton->InvalidateDeviceObjects();

	m_pChatShowImage->InvalidateDeviceObjects();
	for(i=0;i<BUTTON_BOTH_STATE_NUMBER;i++)
	{
		m_pChatViewButton[0][i]->InvalidateDeviceObjects();
		m_pChatViewButton[1][i]->InvalidateDeviceObjects();
		m_pImgWisperBtn[0][i]->InvalidateDeviceObjects();
		m_pImgWisperBtn[1][i]->InvalidateDeviceObjects();
	}

	m_pFontInput->InvalidateDeviceObjects();
	// 2014-07-01 by ymjoo DrawText ���� ���� �۾� (����)
#ifdef C_DRAWTEXT_UPGRADE_YMJOO
	for(i = 0 ; i < 10 ; ++i)
	{
		m_pFontGM[i]->InvalidateDeviceObjects();
	}
	m_pFontInfl->InvalidateDeviceObjects();
#else
	m_pFontGM->InvalidateDeviceObjects();	
#endif
	// END 2014-07-01 by ymjoo DrawText ���� ���� �۾� (����)

	vector<CD3DHanFont*>::iterator it = m_vecFontLine.begin();
	while(it != m_vecFontLine.end())
	{
		CD3DHanFont* pFont = *it;
		it++;
		pFont->InvalidateDeviceObjects();
		pFont->DeleteDeviceObjects();
		delete pFont;
		pFont = NULL;
	}
	m_vecFontLine.clear();
	vectorINFGameMainWisperChatPtr::iterator itr(m_vectorINFiGameMainWisperChatPtr.begin());
	while (itr != m_vectorINFiGameMainWisperChatPtr.end())
	{
		(*itr)->InvalidateDeviceObjects();		
		itr++;
	}
	m_pSystemMsgW->InvalidateDeviceObjects();
	

	// �߰����� 2005.01.21
	for(i=0; i<CHAT_BUTTON_NUMBER3; i++)
	{
		m_pNChatFAQ[i]->InvalidateDeviceObjects();								// ä�� FAQ��ư
		m_pNChatMenuView[i]->InvalidateDeviceObjects();						// ä�� �޴� ���̱� ��ư
		m_pNChatVOIPStartMenu[i]->InvalidateDeviceObjects();
		m_pNChatVOIPEndMenu[i]->InvalidateDeviceObjects();
	}
#ifndef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	for(i=0; i<CHAT_BUTTON_NUMBER4; i++)
	{
		m_pNChatCash[i]->InvalidateDeviceObjects();							// ä�� ä������ ��ư
	}
#endif
// 2015-02-04 by jwLee �Ϻ� ĳ���� ����
#if defined(C_CASH_SHOP_NOT_USE_JWLEE)
#else
	for(i=0; i<CHAT_BUTTON_NUMBER4; i++)
	{
		m_pNChatCashView[i]->InvalidateDeviceObjects();
	}
#endif
// end 2015-02-04 by jwLee �Ϻ� ĳ���� ����

	for(i=0; i<INPUT_LANGUAGE_END; i++)
		m_pNChatInputLanguage[i]->InvalidateDeviceObjects();
	for(i=0; i<CHAT_MENULIST_NUMBER; i++)
	{
		m_pNChatMenu[i]->InvalidateDeviceObjects();							// ä�� �޴� ����Ʈ
	}
	m_pNChatInput->InvalidateDeviceObjects();									// ä�� �Է�â
	m_pNChatCheck->InvalidateDeviceObjects();									// ä�� äũ��ũ

	for(i = 0; i < CHAT_TAB_CHATROOM ; i++)
	{
		if(NULL != m_pBtnChatMode[i])
		{
			m_pBtnChatMode[i]->InvalidateDeviceObjects();	
		}
	}
	m_pBtnPartyQuick->InvalidateDeviceObjects();
	m_pBtnGuildQuick->InvalidateDeviceObjects();

	m_pChatMacroBG->InvalidateDeviceObjects();

	for(i = 0 ; i < CHAT_MACRO_INPUT_COUNT ; i++)
	{
		m_pBtnChatMacro[i]->InvalidateDeviceObjects();
	}
	m_pBtnMacroOK->InvalidateDeviceObjects();
	m_pBtnMacroCancel->InvalidateDeviceObjects();
	m_pBtnOption->InvalidateDeviceObjects();
	{
		m_pBtnVoiceChatInv->InvalidateDeviceObjects();
		m_pBtnVoiceChatOk->InvalidateDeviceObjects();
		m_pBtnVoiceChatCan->InvalidateDeviceObjects();

		m_pBothParty->InvalidateDeviceObjects();
		m_pBothGuild->InvalidateDeviceObjects();
		m_pBothChat->InvalidateDeviceObjects();
		m_pBothWhisper->InvalidateDeviceObjects();

		m_pVoiceChatBG->InvalidateDeviceObjects();
		m_pImgSpkVolBar->InvalidateDeviceObjects();
		m_pImgRadioBtn[0]->InvalidateDeviceObjects();
		m_pImgRadioBtn[1]->InvalidateDeviceObjects();

	}



	// 2008. 12. 29 by ckPark ä��â ����ȭ	
	// �� ä�� ���� ����
	for(i=0; i<MAX_GAME_MAIN_CHAT_LINE; ++i)
		m_pFontLine[i]->InvalidateDeviceObjects();
	// end 2008. 12. 29 by ckPark ä��â ����ȭ	

#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	if( m_pBtnChatBG )
	{
		m_pBtnChatBG->InvalidateDeviceObjects();
	}
#endif

	return S_OK ;
}

void CINFGameMainChat::TickMacro()
{
	if(m_bMacroIng)
	{
		int i;
		for(i = 0 ; i < CHAT_MACRO_INPUT_COUNT; i++)
		{
			if(m_nSendMacroNum == i)
			{
				if(m_sMacroStr[i].bAppl == TRUE)
				{
					// 2008-08-18 by bhsohn ��ũ�� �߰� ����
					if(m_sMacroStr[i].fTime >= 0)
					{
						m_sMacroStr[i].fTime -= g_pD3dApp->GetElapsedTime();
					}
					
					if((m_sMacroStr[i].fTime < 0))// &&(m_nTransChatCount >= CHATMACRO_TRANSCHAT_COUNT)) // 2012-03-30 by isshin ��ũ�� �ý��� ���� ���� - ��ũ�� ��� ����(�ð�����) ����
					{// ��ũ�� ��Ʈ�� ������.
						m_sMacroStr[i].fTime = CHAT_MACRO_OUTPUT_TIME;
						//send ��ũ�� ��Ʈ�� ������ ������.
						g_pD3dApp->m_pIMSocket->SendChat(T_IC_CHAT_SELL_ALL, g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.CharacterName, m_sMacroStr[i].strMacro );
						m_nTransChatCount = 0;
						//////////////////////////////////////////

						// ���� ������ �� ��ũ�� ��Ʈ�� ã��.
						int temp = i;
						temp++;
						if(temp >= CHAT_MACRO_INPUT_COUNT)
						{
							temp = 0;
						}
						for(int j = temp; j < CHAT_MACRO_INPUT_COUNT ; j++)
						{
							if(m_sMacroStr[j].bAppl == TRUE)
							{
								m_nSendMacroNum = j;
								break;
							}// 2012-03-30 by isshin ��ũ�� �ý��� ���� ���� - ��ũ�� 3�� �̼����� ��� ���� ����
							else if(m_sMacroStr[2].bAppl == FALSE)
							{
								m_nSendMacroNum	= 0;
							}// end 2012-03-30 by isshin ��ũ�� �ý��� ���� ���� - ��ũ�� 3�� �̼����� ��� ���� ����
						}
					}
					
				}
				else
				{
					// 2008-08-18 by bhsohn ��ũ�� �߰� ����
					m_nSendMacroNum++;
					if(m_nSendMacroNum >= CHAT_MACRO_INPUT_COUNT)
					{
						m_nSendMacroNum = 0;
					}
				}
			}
			
		}
	}
}
void CINFGameMainChat::Tick()
{
	FLOG( "CINFGameMainChat::Tick()" );
	if(!m_bChatMode)
	{
//		int i; for(i=0;i<CHAT_TAB_NUMBER;i++)
		{
			for(int j=0;j<CHAT_NOT_SHOWBOX_LINE;j++)
			{
				m_fTimeOfShowChat[j] -= g_pD3dApp->GetElapsedTime();
			}
		}
	}
	TickMacro();

	CINFGameMainWisperChat *pWisper = NULL;
	vectorINFGameMainWisperChatPtr::iterator it(m_vectorINFiGameMainWisperChatPtr.begin());
	while (it != m_vectorINFiGameMainWisperChatPtr.end())
	{
		pWisper = (*it); 
		(*it)->Tick();
		it++;		
	}
 	m_pSystemMsgW->Tick();

	if(m_fTimeGm > 0)
	{
		m_fTimeGm -= g_pD3dApp->GetElapsedTime();
	}
	if(m_fTimeInfluenceLeader > 0)
	{
		m_fTimeInfluenceLeader -= g_pD3dApp->GetElapsedTime();
	}
	// �������� ���������� �ö����� ��ٸ���
	if(m_bCheckShopInfo)
		CheckShopInfo();

	// by bhsohn 2007-03-12 China Working
}

struct sort_CINFGameMainWisperChat: binary_function<CINFGameMainWisperChat*, CINFGameMainWisperChat*, bool>
{
	bool operator()(CINFGameMainWisperChat *pWisper1, CINFGameMainWisperChat *pWisper2)
	{
        return pWisper1->m_nVectorIndex < pWisper2->m_nVectorIndex;	// ���� ���� ����
    };
};

void CINFGameMainChat::Render()
{
	FLOG( "CINFGameMainChat::Render()" );

	// ��Ƽ�� �����Ǵ��� ��ǥ ���� 
	if(g_pD3dApp->m_dwGameState == _CITY)
	{
		// �����̸� �������̽� ���̱�
// 2008-05-19 by dgwoo ���� �������̽� ��ġ ����.
//		m_nCashButtonGab = 45;
		m_nChatBoxYPos = g_pD3dApp->GetBackBufferDesc().Height - CHATBOX_CITY_SHOWCHATBOX_INIT_HEIGHT - m_nChatBoxHeight;
		g_pInterface->m_bShowInterface = TRUE;
	}
	else
	{
		if(g_pD3dApp->m_bCharacter == TRUE && !g_pD3dApp->m_bBazaar)
		{
// 2008-05-19 by dgwoo ���� �������̽� ��ġ ����.
//			m_nCashButtonGab = 32;
		}
		else
		{
			m_nCashButtonGab = 0;
		}
		m_nChatBoxYPos = g_pD3dApp->GetBackBufferDesc().Height - CHATBOX_FIELD_SHOWCHATBOX_INIT_HEIGHT - m_nChatBoxHeight;
	}

	// 2007-03-27 by bhsohn ������ ���� �������̽� ����
	// Ǯ��ũ���� ê�ڽ� ���߱�
//	if(!g_pInterface->m_bShowInterface&& m_bChatMode == TRUE)
//	{
//		m_pChatBox[4]->Move(CHAT_MENUBOX_START_X, CHAT_FONT_START_Y+CHAT_FONT_WIDTH_ENGLISH);
//		m_pChatBox[4]->SetScale(CHAT_MENUBOX_START_X+CHAT_INPUT_FONT_LENGTH, CHATBOX_IMAGE_GAB_HEITHT_TOP);
//		m_pChatBox[4]->Render();
//	}	
//	if(!g_pInterface->m_bShowInterface) m_bShowChatBox = FALSE;
//	if(m_bShowChatBox && g_pInterface->m_bShowInterface)
//	{
//		DrawChatWindow(CHAT_CHATBOX_START_X, m_nChatBoxYPos, m_nChatBoxWidth, m_nChatBoxHeight);
//	}
	// Ǯ��ũ���� ê�ڽ� ���߱�
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
#else
	if(!g_pInterface->m_bShowInterface&& m_bChatMode == TRUE && !g_pShuttleChild->IsObserverMode())
	{
		m_pChatBox[4]->Move(CHAT_MENUBOX_START_X, CHAT_FONT_START_Y+CHAT_FONT_WIDTH_ENGLISH);
		m_pChatBox[4]->SetScale(CHAT_MENUBOX_START_X+CHAT_INPUT_FONT_LENGTH, CHATBOX_IMAGE_GAB_HEITHT_TOP);
		m_pChatBox[4]->Render();
	}
#endif

	if(!g_pInterface->m_bShowInterface || g_pShuttleChild->IsObserverMode()) 
	{
		m_bShowChatBox = FALSE;
	}
	if(m_bShowChatBox && g_pInterface->m_bShowInterface && !g_pShuttleChild->IsObserverMode())
	{
		DrawChatWindow(CHAT_CHATBOX_START_X, m_nChatBoxYPos, m_nChatBoxWidth, m_nChatBoxHeight);
	}
	// end 2007-03-27 by bhsohn ������ ���� �������̽� ����
	
	// ä�� �ڽ� �޴� (�븻, �Ӹ�, ��Ƽ, ���, ����)
	if(g_pInterface->m_bShowInterface && !g_pShuttleChild->IsObserverMode())
	{
		// 2008-05-08 by dgwoo ä�� �ý��� ���� �ҽ� �߰�.
		int i;
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
		m_pBtnChatBG->Move(CHAT_CHATMODE_X,CHAT_CHATMODE_Y + 2);
		m_pBtnChatBG->Render();
#endif

		for(i = 0; i < CHAT_TAB_CHATROOM ; i++)
		{
			m_pBtnChatMode[i]->Render();	
		}
		m_pNChatInput->Move(CHAT_WINDOW_X, CHAT_WINDOW_Y);
		m_pNChatInput->Render();

		m_pBtnOption->Render();

		// �߰� ���� ä�� â
		m_pNChatMenuView[m_nMenuListButtonState]->Move(CHAT_MENU_VIEW_X, CHAT_MENU_VIEW_Y);
		m_pNChatMenuView[m_nMenuListButtonState]->Render();

		// 2006-03-16 by ispark
		int nSelectLanguage = g_pD3dApp->m_inputkey.GetInputLanguage() - 1;
		if(nSelectLanguage < 0)
			nSelectLanguage = 0;
		m_pNChatInputLanguage[nSelectLanguage]->Move(CHAT_INPUT_LANGUAGE_X, CHAT_INPUT_LANGUAGE_Y);
		m_pNChatInputLanguage[nSelectLanguage]->Render();

		m_pChatViewButton[m_bShowChatBox][m_nChatSizeBtnNormal]->Move(CHAT_CHATTAB_VIEW_FLAG_X,
			CHAT_CHATTAB_VIEW_FLAG_Y);
		m_pChatViewButton[m_bShowChatBox][m_nChatSizeBtnNormal]->Render();				// �ִ�ȭ

		
		// ä��â �ּ�ȭ
		if(m_bShowChatBox)
		{
// 2008-05-08 by dgwoo ä�� �ý��� ���� �ҽ� �߰�
//			m_pChatViewButton[CHAT_BOX_HIDE_IMAGE][m_nSizeMaxButtonstate]->Move(CHAT_CHATBOX_START_X+m_nChatBoxWidth-CHATBOX_IMAGE_GAB_MINIMIZE_WIDTH,
//				m_nChatBoxYPos + CHAT_MENUBOX_GAB_WIDTH);
//			m_pChatViewButton[CHAT_BOX_HIDE_IMAGE][m_nSizeMaxButtonstate]->Render();			// �ּ�ȭ 	
			
			// â ȭ�鿡 "ä��" ǥ�� 
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
			m_pChatShowImage->Move(CHAT_MENUBOX_START_X, m_nChatBoxYPos - CHAT_MENUBOX_GAB_WIDTH);
#else
			m_pChatShowImage->Move(CHAT_MENUBOX_START_X, m_nChatBoxYPos + CHAT_MENUBOX_GAB_WIDTH);
#endif
			m_pChatShowImage->Render();
		}	
	}

	if(m_bChatMode)
	{
		int nShowTemp = 0;
		
		// 2007-03-27 by bhsohn ������ ���� �������̽� ����
		//if(!g_pInterface->m_bShowInterface)
		if(!g_pInterface->m_bShowInterface || g_pShuttleChild->IsObserverMode())
		{
			nShowTemp = -25;
		}

		// 2009-03-18 by bhsohn ä��â Ŀ�� �̵� �ý��� �߰�
// 		char chatbuf[SIZE_MAX_CHAT_MESSAGE+2];
// 		memset(chatbuf,0x00,SIZE_MAX_CHAT_MESSAGE);
// 		strncpy(chatbuf,m_strInputMessage,SIZE_MAX_CHAT_MESSAGE);		
		
// 		chatbuf[strlen(m_strInputMessage)] = '_';
// 		chatbuf[strlen(m_strInputMessage)+1] = '\0';
//		m_pFontInput->SetTextureWidth(CHAT_MENUBOX_START_X+CHAT_INPUT_FONT_LENGTH);		
// 		m_pFontInput->SetTextureWidth(CHAT_INPUT_FONT_LENGTH);		
// 		m_pFontInput->DrawText(CHAT_FONT_START_X+nShowTemp,CHAT_FONT_START_Y + FONT_INPUT_Y,GUI_FONT_COLOR_Y,chatbuf, 0L);		
		RenderCursel(nShowTemp);		
		// end 2009-03-18 by bhsohn ä��â Ŀ�� �̵� �ý��� �߰�
	}	

	ChatTab_t *pCurChatTab = GetChatTabMode();
	if(0 >= pCurChatTab->m_nStoredLineCounts)
	{
	}
	else
	{
		if(m_bShowChatBox)
		{
			// ä��â Ȱ��ȭ ����
			int nMaxRenderLineCounts	= (m_nChatBoxHeight-CHATBOX_IMAGE_GAB_HEITHT_TOP)/CHAT_FONT_LINE_HEIGHT;
			int nRenderIndex			= pCurChatTab->m_nRenderStartIndex;
			int nRenderedLineCounts		= 0;
			int nLineCount = 1;
			
			// ���� ���� ������
			if(m_fTimeGm>0 && m_bHelpDeskRender == FALSE)
			{
				// 2007-08-07 by bhsohn ����Ŀ ������ �߰�
//				m_pFontGM->DrawText(CHAT_NFONT_START_LINE_X, 
//					m_nChatBoxYPos-15,
//					COLOR_CHAT_ALL,
//					m_strInputGm);
				// end 2007-08-07 by bhsohn ����Ŀ ������ �߰�
			}
			else if(m_fTimeGm>0 && m_bHelpDeskRender == TRUE)
			{
				vector<string> vectemp;
				// 2014-07-01 by ymjoo DrawText ���� ���� �۾� (����)
#ifdef C_DRAWTEXT_UPGRADE_YMJOO
				STRING_CULL2(m_strInputGm, CHAT_HELPDESK_STRLEN, &vectemp, m_pFontGM[9]);
#else
				STRING_CULL2(m_strInputGm, CHAT_HELPDESK_STRLEN, &vectemp, m_pFontGM);
#endif
				// END 2014-07-01 by ymjoo DrawText ���� ���� �۾� (����)
				int igm = 0;
				nLineCount = vectemp.size();
				
				for(igm = 0; igm < vectemp.size(); igm++)
				{
					// 2014-07-01 by ymjoo DrawText ���� ���� �۾� (����)
#ifdef C_DRAWTEXT_UPGRADE_YMJOO
					m_pFontGM[igm]->DrawText(CHAT_NFONT_START_LINE_X, m_nChatBoxYPos - (nLineCount * 15), COLOR_CHAT_ALL, (char*)vectemp[igm].c_str());
#else
					m_pFontGM->DrawText(CHAT_NFONT_START_LINE_X, m_nChatBoxYPos-(nLineCount * 15), COLOR_CHAT_ALL, (char*)vectemp[igm].c_str());
#endif
					// END 2014-07-01 by ymjoo DrawText ���� ���� �۾� (����)
					nLineCount--;
				}
				nLineCount = vectemp.size() + 1;
			}
// 2008-05-20 by dgwoo ���򸻰� ����ä���� �и�.
//			if(m_fTimeInfluenceLeader>0 && !(m_fTimeGm>0 && m_bHelpDeskRender == TRUE))
//			{
//				m_pFontGM->DrawText(CHAT_NFONT_START_LINE_X, m_nChatBoxYPos - 30, 
//					COLOR_INFLUENCE, 
//					m_strInputInfluenceLeader);
//			}
			if(m_fTimeInfluenceLeader>0)
			{
				// 2014-07-01 by ymjoo DrawText ���� ���� �۾� (����)
#ifdef C_DRAWTEXT_UPGRADE_YMJOO
				m_pFontInfl->DrawText(CHAT_NFONT_START_LINE_X, m_nChatBoxYPos - (nLineCount * 15), COLOR_INFLUENCE, m_strInputInfluenceLeader);
#else
 				m_pFontGM->DrawText(CHAT_NFONT_START_LINE_X, m_nChatBoxYPos - (nLineCount * 15), 
 					COLOR_INFLUENCE, 
 					m_strInputInfluenceLeader);
#endif
				// END 2014-07-01 by ymjoo DrawText ���� ���� �۾� (����)
			}
			
			//--------------------------------------------------------------------------//
			//   ä��â�� ��� �ٷΰ��� , �Ǵ� ���ܰ���â�� �ٷ� ���� �ִ� �������̽� ��ư. 

			if(g_pShuttleChild->GetMyShuttleInfo().GuildUniqueNumber == 0 &&
				m_nChatMode == CHAT_TAB_GUILD)
			{
				m_pBtnGuildQuick->SetBtnPosition(CHAT_NFONT_START_LINE_X
							, m_nChatBoxYPos+m_nChatBoxHeight - (CHAT_FONT_LINE_HEIGHT + CHAT_FONT_LINE_HEIGHT*(nRenderedLineCounts+1)));
				m_pBtnGuildQuick->Render();
			}
			else if(g_pShuttleChild->m_pClientParty->IsParty() == FALSE &&
				m_nChatMode == CHAT_TAB_PARTY)
			{
				m_pBtnPartyQuick->SetBtnPosition(CHAT_NFONT_START_LINE_X
							, m_nChatBoxYPos+m_nChatBoxHeight - (CHAT_FONT_LINE_HEIGHT + CHAT_FONT_LINE_HEIGHT*(nRenderedLineCounts+1)));
				m_pBtnPartyQuick->Render();
			}
			//--------------------------------------------------------------------------//

			


			// 2008. 12. 29 by ckPark ä��â ����ȭ	
// 			vector<CD3DHanFont*>::iterator it = m_vecFontLine.begin();
// 			while(it != m_vecFontLine.end())
// 			{
// 				CD3DHanFont* pFont = *it;
// 				
// 				///////////////////////////////////////////////////////////////////////////////
// 				//	1. ������ ���ٷ� Rendering �Ѵ�
// 				//	2. ������ ���ٷ� Rendering �Ѵ�
// 				// 2006-04-13 by ispark, ����
// 				int pFontTexWidth = pFont->GetStringSize(pCurChatTab->GetChatLine(nRenderIndex)).cx;
// //				if(pCurChatTab->ChatLineLength(nRenderIndex)*CHAT_FONT_WIDTH_ENGLISH <= m_nChatBoxWidth - 11)
// 				if(pFontTexWidth <= CHAT_STRING_LENGTH)
// 				{// ���ٷ� ������.
// 					// 2008-05-08 by dgwoo ä�� �ý��� ���� �ҽ� �߰�.
// //					if(m_nChatMode == CHAT_TAB_ALLUSER 
// //						|| m_nChatMode == pCurChatTab->GetType(nRenderIndex))
// 					{
// 						pFont->DrawText(CHAT_NFONT_START_LINE_X
// 							, m_nChatBoxYPos+m_nChatBoxHeight - (CHAT_FONT_LINE_HEIGHT + CHAT_FONT_LINE_HEIGHT*nRenderedLineCounts)
// 							, pCurChatTab->GetColorType(nRenderIndex)
// 							, pCurChatTab->GetChatLine(nRenderIndex)
// 							, 0L);
// 						nRenderedLineCounts++;
// 					}
// 					
// 				}
// 				else
// 				{// ���ٷ� ������.
// 					int nStrlen = pCurChatTab->ChatLineLength(nRenderIndex);
// 					vector<string> vecChatMessage;
// 					vecChatMessage.clear();
// 					STRING_CULL(pCurChatTab->GetChatLine(nRenderIndex), CHAT_STRING_LENGTH, &vecChatMessage, pFont);
// 
// 					for(int i = vecChatMessage.size() - 1; i >= 0; i--)
// 					{
// 						if(nMaxRenderLineCounts <= nRenderedLineCounts)
// 						{
// 							break;
// 						}
// 						char* ptemp = (char*)vecChatMessage[i].c_str();
// //						if(m_nChatMode == CHAT_TAB_ALLUSER 
// //							|| m_nChatMode == pCurChatTab->GetType(nRenderIndex))
// 						{
// 							pFont->DrawText(CHAT_NFONT_START_LINE_X
// 								, m_nChatBoxYPos+m_nChatBoxHeight - (CHAT_FONT_LINE_HEIGHT + CHAT_FONT_LINE_HEIGHT*nRenderedLineCounts)
// 								, pCurChatTab->GetColorType(nRenderIndex)
// 								, (char*)vecChatMessage[i].c_str()
// 								, 0L);
// 							nRenderedLineCounts++;
// 						}
// 						
// 					}
// 					vecChatMessage.clear();
// 				}
// 				
// 				if(nRenderIndex == pCurChatTab->m_nStoreEndIndex
// 					|| nMaxRenderLineCounts <= nRenderedLineCounts)
// 				{
// 					break;
// 				}
// 				
// 				
// 				nRenderIndex--;
// 				if(0 > nRenderIndex)
// 				{
// 					nRenderIndex = CHAT_BUFFER_NUMBER-1;
// 				}						
// 				it++;			
// 			}

			// ���� �ø� ��Ʈ���� �ʱ�ȭ ��ٸ� �ٽ� �����Ѵ�
			if( m_listCulledString.empty() )
				BuildCulledString();

			BOOL bBreak					= FALSE;	// ���� Ż�⺯��
			CulledStringListItor	end = m_listCulledString.end();
			for(CulledStringListItor it	= m_listCulledString.begin(); it != end && !bBreak; ++it)
			{
				// 2012-11-09 by bhsohn ä��â Null���� ���� ����
				if(it == end)
				{
//					DbgOut("it != end #1 \n");
					break;
				}
				// END 2012-11-09 by bhsohn ä��â Null���� ���� ����

				// �߷��� ��Ʈ�� ����(�ؿ��� ���� ���� ���̱� ������ reverse�� ��ȸ)
				std::vector< string >::reverse_iterator vEnd = (*it).rend();

				for(std::vector< string >::reverse_iterator vIt = (*it).rbegin(); vIt != vEnd && !bBreak; ++vIt)
				{
					// �ִ� ������ �ѵ� �Ѿ� �� �� ���� Ż��
					if(nMaxRenderLineCounts <= nRenderedLineCounts)
					{
						bBreak = TRUE;
						break;
					}
					// 2012-11-09 by bhsohn ä��â Null���� ���� ����
					if(vIt == vEnd)
					{
						bBreak = TRUE;
//						DbgOut("it != end #1 \n");
						break;
					}
					// END 2012-11-09 by bhsohn ä��â Null���� ���� ����
					
					// ������
					m_pFontLine[nRenderedLineCounts]->DrawText(CHAT_NFONT_START_LINE_X,
															   m_nChatBoxYPos + m_nChatBoxHeight
															   - (CHAT_FONT_LINE_HEIGHT + CHAT_FONT_LINE_HEIGHT * nRenderedLineCounts),
															   pCurChatTab->GetColorType(nRenderIndex),
															   (char*)( (*vIt).c_str() ),
															   0L);
					// ������ ���μ� ����
					nRenderedLineCounts++;
				}

				// ����� ���μ��� �Ѿ� �� ��� ���� Ż��
				if(nRenderIndex == pCurChatTab->m_nStoreEndIndex
				   || nMaxRenderLineCounts <= nRenderedLineCounts)
					bBreak = TRUE;
				
				// ����ť �ε��� ����
				if(0 > --nRenderIndex)
				   nRenderIndex = CHAT_BUFFER_NUMBER - 1;
			}

			// end 2008. 12. 29 by ckPark ä��â ����ȭ





		}
		else
		{
			// ä��â ��Ȱ��ȭ
			
			int nMaxRenderLineCounts	= CHAT_NOT_SHOWBOX_LINE;		
			int nRenderIndex			= pCurChatTab->m_nRenderStartIndex;
			int nRenderedLineCounts		= 0;
			int nChatHeightCity = 0;
			int nLineCount = 1;
			if(g_pD3dApp->m_dwGameState == _CITY)
			{
				nChatHeightCity = m_nChatBoxYPos+m_nChatBoxHeight;
			}
			else 
			{
				nChatHeightCity = CHAT_NFONT_START_LINE_Y;//CHAT_FONT_START_Y-10;		
			}
			
			// ���� ���� ������
			if(m_fTimeGm>0 && m_bHelpDeskRender == FALSE)
			{
				// 2007-08-07 by bhsohn ����Ŀ ������ �߰�
//				m_pFontGM->DrawText(CHAT_NFONT_START_LINE_X, 
//					nChatHeightCity - (CHAT_FONT_LINE_HEIGHT + CHAT_FONT_LINE_HEIGHT*7),
//					COLOR_CHAT_ALL,
//					m_strInputGm);
				// end 2007-08-07 by bhsohn ����Ŀ ������ �߰�
			}
			else if(m_fTimeGm>0 && m_bHelpDeskRender == TRUE)
			{
				vector<string> vectemp;
				// 2014-07-01 by ymjoo DrawText ���� ���� �۾� (����)
#ifdef C_DRAWTEXT_UPGRADE_YMJOO
				STRING_CULL2(m_strInputGm, CHAT_HELPDESK_STRLEN, &vectemp, m_pFontGM[9]);
#else
				STRING_CULL2(m_strInputGm, CHAT_HELPDESK_STRLEN, &vectemp, m_pFontGM);
#endif
				// END 2014-07-01 by ymjoo DrawText ���� ���� �۾� (����)
				int igm = 0;
				nLineCount = vectemp.size();
				
				for(igm = 0; igm < vectemp.size(); igm++)
				{
					// 2014-07-01 by ymjoo DrawText ���� ���� �۾� (����)
#ifdef C_DRAWTEXT_UPGRADE_YMJOO
					m_pFontGM[igm]->DrawText(CHAT_NFONT_START_LINE_X, m_nChatBoxYPos - (nLineCount * 15), COLOR_CHAT_ALL, (char*)vectemp[igm].c_str());
#else
					m_pFontGM->DrawText(CHAT_NFONT_START_LINE_X, m_nChatBoxYPos-(nLineCount * 15), COLOR_CHAT_ALL, (char*)vectemp[igm].c_str());
#endif
					// END 2014-07-01 by ymjoo DrawText ���� ���� �۾� (����)
					nLineCount--;
				}
				nLineCount = vectemp.size() +1;
			}
// 2008-05-20 by dgwoo ���򸻰� ����ä���� �и�.		
//			if(m_fTimeInfluenceLeader>0 && !(m_fTimeGm>0 && m_bHelpDeskRender == TRUE))
//			{
//				m_pFontGM->DrawText(CHAT_NFONT_START_LINE_X, 
//					nChatHeightCity - (CHAT_FONT_LINE_HEIGHT + CHAT_FONT_LINE_HEIGHT*8), 
//					COLOR_INFLUENCE, 
//					m_strInputInfluenceLeader);
//			}
			if(m_fTimeInfluenceLeader>0 )
			{
				// 2014-07-01 by ymjoo DrawText ���� ���� �۾� (����)
#ifdef C_DRAWTEXT_UPGRADE_YMJOO
				m_pFontInfl->DrawText(CHAT_NFONT_START_LINE_X, m_nChatBoxYPos - (nLineCount * 15), COLOR_INFLUENCE, m_strInputInfluenceLeader);
#else
 				m_pFontGM->DrawText(CHAT_NFONT_START_LINE_X, 
 					 m_nChatBoxYPos-(nLineCount * 15), 
 					COLOR_INFLUENCE, 
 					m_strInputInfluenceLeader);
#endif
				// END 2014-07-01 by ymjoo DrawText ���� ���� �۾� (����)
			}




			// 2008. 12. 29 by ckPark ä��â ����ȭ	
			// �Ϲ� ä��
// 			vector<CD3DHanFont*>::iterator it = m_vecFontLine.begin();
// 			while(it != m_vecFontLine.end())
// 			{
// 				if(m_fTimeOfShowChat[nRenderedLineCounts] < 0) 
// 				{
// 					break;
// 				}
// 
// 
// 				CD3DHanFont* pFont = *it;
// 				int nStrlen = pCurChatTab->ChatLineLength(nRenderIndex);
// 				vector<string> vecChatMessage;
// 				vecChatMessage.clear();
// 				STRING_CULL(pCurChatTab->GetChatLine(nRenderIndex), CHAT_STRING_LENGTH, &vecChatMessage, pFont);
// 
// 				for(int i = vecChatMessage.size() - 1; i >= 0; i--)
// 				{
// 					if(nMaxRenderLineCounts <= nRenderedLineCounts)
// 					{
// 						break;
// 					}
// 
// 					// 2008-05-08 by dgwoo ä�� �ý��� ���� �ҽ� �߰�.
// //					if(m_nChatMode == CHAT_TAB_ALLUSER 
// //						|| m_nChatMode == pCurChatTab->GetType(nRenderIndex))
// 					{
// 						pFont->DrawText(CHAT_NFONT_START_LINE_X					
// 							, nChatHeightCity/*CHAT_FONT_START_Y*/ - (CHAT_FONT_LINE_HEIGHT + CHAT_FONT_LINE_HEIGHT*nRenderedLineCounts)					
// 							, pCurChatTab->GetColorType(nRenderIndex)
// 							, (char*)vecChatMessage[i].c_str()
// 							, 0L);
// 						nRenderedLineCounts++;			
// 					}
// 					// 2008-05-08 by dgwoo ä�� �ý��� ���� �ҽ� �߰�.
// 
// 				}
// 				vecChatMessage.clear();
// //				pFont->DrawText(CHAT_NFONT_START_LINE_X					
// //					, nChatHeightCity/*CHAT_FONT_START_Y*/ - (CHAT_FONT_LINE_HEIGHT + CHAT_FONT_LINE_HEIGHT*nRenderedLineCounts)					
// //					, pCurChatTab->GetColorType(nRenderIndex)
// //					, pCurChatTab->GetChatLine(nRenderIndex)
// //					, 0L);
// 				
// 				if(nRenderIndex == pCurChatTab->m_nStoreEndIndex
// 					|| nMaxRenderLineCounts <= nRenderedLineCounts)
// 				{
// 					break;
// 				}
// 				
// 				nRenderIndex--;
// 				if(0 > nRenderIndex)
// 				{
// 					nRenderIndex = CHAT_BUFFER_NUMBER-1;
// 				}
// 				it++;			
// 			}
	
			// ���� �ø� ��Ʈ���� �ʱ�ȭ ��ٸ� �ٽ� �����Ѵ�
			if( m_listCulledString.empty() )
				BuildCulledString();
			
			BOOL bBreak					= FALSE;	// ���� Ż�⺯��
			CulledStringListItor	end = m_listCulledString.end();
			for(CulledStringListItor it	= m_listCulledString.begin(); it != end && !bBreak; ++it)
			{
				// �߷��� ��Ʈ�� ����(�ؿ��� ���� ���� ���̱� ������ reverse�� ��ȸ)
				std::vector< string >::reverse_iterator vEnd = (*it).rend();
				
				for(std::vector< string >::reverse_iterator vIt = (*it).rbegin(); vIt != vEnd && !bBreak; ++vIt)
				{
					// 2012-11-09 by bhsohn ä��â Null���� ���� ����
					if(vIt == vEnd )
					{
//						DbgOut("vIt == vEnd #1 \n");
						bBreak = TRUE;
						break;
					}
					// END 2012-11-09 by bhsohn ä��â Null���� ���� ����

					// �ִ� ������ �ѵ� �Ѿ� �� �� ���� Ż��
					if(nMaxRenderLineCounts <= nRenderedLineCounts)
					{
						bBreak = TRUE;
						break;
					}
					
					// ������
					m_pFontLine[nRenderedLineCounts]->DrawText(CHAT_NFONT_START_LINE_X,
															   m_nChatBoxYPos + m_nChatBoxHeight
															   - (CHAT_FONT_LINE_HEIGHT + CHAT_FONT_LINE_HEIGHT * nRenderedLineCounts),
															   pCurChatTab->GetColorType(nRenderIndex),
															   (char*)( (*vIt).c_str() ),
															   0L);
					// ������ ���μ� ����
					nRenderedLineCounts++;
				}
				
				// ����� ���μ��� �Ѿ� �� ��� ���� Ż��
				if(nRenderIndex == pCurChatTab->m_nStoreEndIndex
					|| nMaxRenderLineCounts <= nRenderedLineCounts)
					bBreak = TRUE;
				
				// ����ť �ε��� ����
				if(0 > --nRenderIndex)
					nRenderIndex = CHAT_BUFFER_NUMBER - 1;
			}

			// end 2008. 12. 29 by ckPark ä��â ����ȭ	





		}	
	}
	// 2008-07-10 by bhsohn �ý��� â �켱���� �߰�
 	//m_pSystemMsgW->Render();
	//RenderMacro();
	//RenderVoiceChatOption();
	

//	// �߰� ä�� ����Ʈ
//	if(m_bMenuListUse)	ViewChatMenuList();
	
	// ���� ������ ����
	// 2007-03-27 by bhsohn ������ ���� �������̽� ����
	//if(g_pD3dApp->GetTestServerFlag() == FALSE && g_pInterface->m_bShowInterface && g_pD3dApp->m_dwGameState != _SHOP)
	if(g_pD3dApp->GetTestServerFlag() == FALSE && !g_pShuttleChild->IsObserverMode()&& g_pInterface->m_bShowInterface && g_pD3dApp->m_dwGameState != _SHOP
		&& g_pD3dApp->GetArenaState() != ARENA_STATE_ARENA_GAMING )	// 2008-02-27 by bhsohn ���� �Ʒ��� ����
	{
		// 2007-10-18 by bhsohn ������ ĳ���� ������ ����
		// 2009-03-03 by bhsohn �Ϻ� ĳ�� ���� ��ư ǥ��
//#ifndef YEDANG_RELEASE
//#if defined(YEDANG_RELEASE) 
//#else
// 2015-02-04 by jwLee �Ϻ� ĳ���� ����
#if defined(C_CASH_SHOP_NOT_USE_JWLEE)
#else
		m_pNChatCashView[m_nOtherCashList]->Move(CHAT_MENU_CASH_START_X-3, CHAT_MENU_CASH_START_Y-m_nCashButtonGab);
		m_pNChatCashView[m_nOtherCashList]->Render();
#endif
// end 2015-02-04 by jwLee �Ϻ� ĳ���� ����
//#endif
	}
	
	// �ĺ�â ����Ʈ (IME)
	if(SET_MAIN_CHAT_CANDIDATE == g_nRenderCandidate)
		g_pD3dApp->RenderCandidate(CHAR_INF_CANDIDATE_POS_X, CHAR_INF_CANDIDATE_POS_Y);

	// 2007-05-21 by bhsohn China IME Working
	g_pD3dApp->RenderIMEType(CHAR_INF_CANDIDATE_POS_X, CHAR_INF_CANDIDATE_POS_Y);
}
///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-07-10 by bhsohn �ý��� â �켱���� �߰�
/// \date		2008-07-10 ~ 2008-07-10
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMainChat::RenderSystemMsg()
{
	if(m_pSystemMsgW)
	{
		m_pSystemMsgW->Render();
	}
}
void CINFGameMainChat::RenderVoiceChatOption()
{
	if(!m_bShowVoiceChatControl)
		return;
	m_pVoiceChatBG->Move(m_nVCCPosX, m_nVCCPosY);
	m_pVoiceChatBG->Render();

	m_pBothParty->SetBtnPosition(VOICECHAT_PARTY_POS_X,VOICECHAT_PARTY_POS_Y);
	m_pBothParty->Render();
	m_pBothGuild->SetBtnPosition(VOICECHAT_GUILD_POS_X,VOICECHAT_GUILD_POS_Y);
	m_pBothGuild->Render();
	m_pBothChat->SetBtnPosition(VOICECHAT_CHATROOM_POS_X,VOICECHAT_CHATROOM_POS_Y);
	m_pBothChat->Render();
	m_pBothWhisper->SetBtnPosition(VOICECHAT_WHISPER_POS_X,VOICECHAT_WHISPER_POS_Y);
	m_pBothWhisper->Render();

	if(m_nVoiceInput)
	{
		m_pImgRadioBtn[0]->Move(VOICECHAT_INPUT_KEY_POS_X,VOICECHAT_INPUT_KEY_POS_Y);
		m_pImgRadioBtn[0]->Render();
		m_pImgRadioBtn[1]->Move(VOICECHAT_INPUT_FREE_POS_X,VOICECHAT_INPUT_FREE_POS_Y);
		m_pImgRadioBtn[1]->Render();
	}
	else
	{
		m_pImgRadioBtn[1]->Move(VOICECHAT_INPUT_KEY_POS_X,VOICECHAT_INPUT_KEY_POS_Y);
		m_pImgRadioBtn[1]->Render();
		m_pImgRadioBtn[0]->Move(VOICECHAT_INPUT_FREE_POS_X,VOICECHAT_INPUT_FREE_POS_Y);
		m_pImgRadioBtn[0]->Render();
	}
	
	m_pImgSpkVolBar->Move(VOICECHAT_SPK_POS_X + m_nPosVolum,VOICECHAT_SPK_POS_Y);
	m_pImgSpkVolBar->Render();

	m_pBtnVoiceChatInv->SetBtnPosition(VOICECHAT_INV_BTN_POS_X,VOICECHAT_INV_BTN_POS_Y);
	m_pBtnVoiceChatInv->Render();
	m_pBtnVoiceChatOk->SetBtnPosition(VOICECHAT_OK_BTN_POS_X,VOICECHAT_OK_BTN_POS_Y);
	m_pBtnVoiceChatOk->Render();
	m_pBtnVoiceChatCan->SetBtnPosition(VOICECHAT_CAN_BTN_POS_X,VOICECHAT_CAN_BTN_POS_Y);
	m_pBtnVoiceChatCan->Render();
}

void CINFGameMainChat::DrawChatWindow(int x, int y, int cx, int cy)
{
	FLOG( "CINFGameMainChat::DrawChatWindow(int x, int y, int cx, int cy)" );
	
	m_pChatBox[0]->Move(x,y);
	m_pChatBox[0]->Render();

#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	int nPosX = x + m_pChatBox[0]->GetImgSize().x;
	int nImageSizeX = ( CHAT_CHATBOX_START_DEFAULT_MIN_X - m_pChatBox[0]->GetImgSize().x - m_pChatBox[2]->GetImgSize().x ) / 2;

	m_pChatBox[1]->Move( nPosX, y );
	m_pChatBox[1]->SetRect( 0, 0, nImageSizeX, m_pChatBox[1]->GetImgSize().y );
	m_pChatBox[1]->SetScale( 1, 1 );
	m_pChatBox[1]->Render();

	nPosX += nImageSizeX;
	m_pChatBox[1]->Move( nPosX, y );
  	m_pChatBox[1]->SetRect( nImageSizeX, 0,  nImageSizeX + 1 , m_pChatBox[1]->GetImgSize().y );
   	m_pChatBox[1]->SetScale( cx - nImageSizeX - nPosX, 1 );
   	m_pChatBox[1]->Render();

  	m_pChatBox[1]->Move( cx - nImageSizeX, y );
  	m_pChatBox[1]->SetRect( m_pChatBox[1]->GetImgSize().x - nImageSizeX, 0, m_pChatBox[1]->GetImgSize().x, m_pChatBox[1]->GetImgSize().y );
  	m_pChatBox[1]->SetScale( 1, 1 );
  	m_pChatBox[1]->Render();

	m_pChatBox[2]->Move(x + cx, y);
	m_pChatBox[2]->Render();

	m_pChatBox[3]->Move(x, y + m_pChatBox[0]->GetImgSize().y);
	m_pChatBox[3]->SetScale(1, (float)(cy - m_pChatBox[0]->GetImgSize().y) / m_pChatBox[3]->GetImgSize().y);
	m_pChatBox[3]->Render();

	m_pChatBox[4]->Move(x + m_pChatBox[3]->GetImgSize().x,  y + m_pChatBox[1]->GetImgSize().y);
	//m_pChatBox[4]->SetScale((cx-CHATBOX_IMAGE_GAB_WIDTH_MIDDLE-CHATBOX_IMAGE_GAB_WIDTH_MIDDLE)+CHATBOX_IMAGE_GAB_HEITHT_TOP, cy-CHATBOX_IMAGE_GAB_HEITHT_TOP);
	m_pChatBox[4]->SetRect( 0, 0, cx - m_pChatBox[3]->GetImgSize().x + m_pChatBox[2]->GetImgSize().x, cy - m_pChatBox[1]->GetImgSize().y );
	m_pChatBox[4]->Render();
	
	m_pChatBox[5]->Move(x + ( cx + m_pChatBox[2]->GetImgSize().x - m_pChatBox[5]->GetImgSize().x) , y + m_pChatBox[2]->GetImgSize().y );
	m_pChatBox[5]->SetScale(1,  (float)(cy - m_pChatBox[0]->GetImgSize().y) / m_pChatBox[3]->GetImgSize().y );
	m_pChatBox[5]->Render();
		
	m_pChatBox[6]->Move(x,y+cy);
	m_pChatBox[6]->Render();

	nPosX = x + m_pChatBox[6]->GetImgSize().x;
	nImageSizeX = ( CHAT_CHATBOX_START_DEFAULT_MIN_X - m_pChatBox[6]->GetImgSize().x - m_pChatBox[8]->GetImgSize().x ) / 2;
	
	m_pChatBox[7]->Move( nPosX, y + cy );
	m_pChatBox[7]->SetRect( 0, 0, nImageSizeX, m_pChatBox[7]->GetImgSize().y );
	m_pChatBox[7]->SetScale( 1, 1 );
	m_pChatBox[7]->Render();
	
	nPosX += nImageSizeX;
	m_pChatBox[7]->Move(nPosX, y + cy);
	m_pChatBox[7]->SetRect( nImageSizeX, 0, nImageSizeX + 1, m_pChatBox[7]->GetImgSize().y );
   	m_pChatBox[7]->SetScale( cx - nImageSizeX - nPosX, 1 );
   	m_pChatBox[7]->Render();
	
	m_pChatBox[7]->Move( cx - nImageSizeX, y + cy );
	m_pChatBox[7]->SetRect( m_pChatBox[1]->GetImgSize().x - nImageSizeX, 0, m_pChatBox[7]->GetImgSize().x, m_pChatBox[7]->GetImgSize().y );
	m_pChatBox[7]->SetScale( 1, 1 );
 	m_pChatBox[7]->Render();

	//m_pChatBox[7]->Move(x+m_pChatBox[6]->GetImgSize().x,y+cy);
	//m_pChatBox[7]->SetScale((float)(cx - m_pChatBox[0]->GetImgSize().x) / m_pChatBox[7]->GetImgSize().x, 1);
	//m_pChatBox[7]->Render();

	m_pChatBox[8]->Move(x+cx,y+cy);
	m_pChatBox[8]->Render();	   
#else					
	m_pChatBox[1]->Move(x+CHATBOX_IMAGE_GAB_WIDTH_TOP, y);
	m_pChatBox[1]->SetScale(cx-CHATBOX_IMAGE_GAB_WIDTH_TOP, 1);
	m_pChatBox[1]->Render();
	m_pChatBox[2]->Move(x+cx,y);
	m_pChatBox[2]->Render();

	m_pChatBox[3]->Move(x, y+CHATBOX_IMAGE_GAB_HEITHT_TOP);
	m_pChatBox[3]->SetScale(1, cy-CHATBOX_IMAGE_GAB_HEITHT_TOP);
	m_pChatBox[3]->Render();
	m_pChatBox[4]->Move(x+CHATBOX_IMAGE_GAB_WIDTH_MIDDLE, y+CHATBOX_IMAGE_GAB_HEITHT_TOP);
	m_pChatBox[4]->SetScale((cx-CHATBOX_IMAGE_GAB_WIDTH_MIDDLE-CHATBOX_IMAGE_GAB_WIDTH_MIDDLE)+CHATBOX_IMAGE_GAB_HEITHT_TOP, cy-CHATBOX_IMAGE_GAB_HEITHT_TOP);
	m_pChatBox[4]->Render();	
	m_pChatBox[5]->Move(x+(cx-CHATBOX_IMAGE_GAB_WIDTH_MIDDLE)+CHATBOX_IMAGE_GAB_HEITHT_TOP, y+CHATBOX_IMAGE_GAB_HEITHT_TOP);
	m_pChatBox[5]->SetScale(1, cy-CHATBOX_IMAGE_GAB_HEITHT_TOP);
	m_pChatBox[5]->Render();
		
	m_pChatBox[6]->Move(x,y+cy);
	m_pChatBox[6]->Render();
	m_pChatBox[7]->Move(x+CHATBOX_IMAGE_GAB_WIDTH_BOTTOM,y+cy);
	m_pChatBox[7]->SetScale(cx-CHATBOX_IMAGE_GAB_WIDTH_BOTTOM, 1);
	m_pChatBox[7]->Render();
	m_pChatBox[8]->Move(x+cx-CHATBOX_IMAGE_GAB_HEITHT_MIDDLE,y+cy);
	m_pChatBox[8]->Render();
#endif
	
	ChatTab_t * pChatTab = GetChatTabMode();
	if(m_nCurrentRelScrollPosY < CHATBOX_IMAGE_GAB_HEITHT_TOP)
	{
		m_nCurrentRelScrollPosY = CHATBOX_IMAGE_GAB_HEITHT_TOP;
		pChatTab->SetRenderStartIndexWithScrollPositon(m_nChatBoxHeight-(CHATBOX_IMAGE_GAB_HEITHT_TOP+CHATBOX_SCROLL_IMAGE_SIZE_HEIGHT)
			, m_nCurrentRelScrollPosY-CHATBOX_IMAGE_GAB_HEITHT_TOP);
	}
	else if(m_nCurrentRelScrollPosY > cy-CHATBOX_SCROLL_IMAGE_SIZE_HEIGHT)
	{
		m_nCurrentRelScrollPosY = cy-CHATBOX_SCROLL_IMAGE_SIZE_HEIGHT;
		pChatTab->SetRenderStartIndexWithScrollPositon(m_nChatBoxHeight-(CHATBOX_IMAGE_GAB_HEITHT_TOP+CHATBOX_SCROLL_IMAGE_SIZE_HEIGHT)
			, m_nCurrentRelScrollPosY-CHATBOX_IMAGE_GAB_HEITHT_TOP);
	}
	m_pScrollLine[CHAT_SELECT_IMAGE_1]->Move(cx+CHATBOX_SCROLLLINE_IMAGE_GAP_X
		, m_nChatBoxYPos+CHATBOX_IMAGE_GAB_WIDTH_TOP+CHATBOX_IMAGE_GAB_MINIMIZE_WIDTH);
	m_pScrollLine[CHAT_SELECT_IMAGE_1]->SetScale(1.0f, cy-CHATBOX_IMAGE_GAB_HEITHT_TOP-(CHATBOX_IMAGE_GAB_MINIMIZE_WIDTH*2));
	m_pScrollLine[CHAT_SELECT_IMAGE_1]->Render();
	m_pScrollButton->Move(cx+CHATBOX_SCROLL_IMAGE_GAP_X
		, m_nChatBoxYPos+m_nCurrentRelScrollPosY);

	m_pScrollButton->Render();
}
int CINFGameMainChat::WndProcWhisperChat(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	BOOL bSortFlag = FALSE;
	int nReted = 0;	
	CINFGameMainWisperChat *pWisper = NULL;
	vectorINFGameMainWisperChatPtr::iterator it(m_vectorINFiGameMainWisperChatPtr.begin());
	while (it != m_vectorINFiGameMainWisperChatPtr.end())
	{
		pWisper = (*it); 
		if(bSortFlag)
		{
			pWisper->m_nVectorIndex--;
			it++;
		}
		else
		{
			nReted = pWisper->WndProc(uMsg, wParam, lParam);
			switch(nReted)
			{
			case INF_MSGPROC_BREAK:
				{
					g_nRenderCandidate = SET_WHISPER_CHAT_CANDIDATE;
					return INF_MSGPROC_BREAK;
				}
			case INF_MSGPROC_CLOSE:
				{
					bSortFlag = TRUE;
					pWisper->InvalidateDeviceObjects();
					pWisper->DeleteDeviceObjects();
					SAFE_DELETE(pWisper);
					m_vectorINFiGameMainWisperChatPtr.erase(it);
					return INF_MSGPROC_BREAK;
				}
				break;
			default:
				{
					it++;
				}
			}
		}
	}
	if(bSortFlag)
	{					
		return INF_MSGPROC_BREAK;
	}
	return INF_MSGPROC_NORMAL;
}
int	CINFGameMainChat::WndProcVoiceOption(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if(FALSE == m_bShowVoiceChatControl)
	{
		return INF_MSGPROC_NORMAL;	
	}
	switch(uMsg)
	{
		case WM_MOUSEMOVE:
			{
				POINT pt;
				pt.x = LOWORD(lParam);
				pt.y = HIWORD(lParam);
				CheckMouseReverse(&pt);
				if(pt.x > m_nVCCPosX &&
					pt.x < m_nVCCPosX + m_pVoiceChatBG->GetImgSize().x &&
					pt.y > m_nVCCPosY &&
					pt.y < m_nVCCPosY + m_pVoiceChatBG->GetImgSize().y)
				{
					m_pBothParty->OnMouseMove(pt);
					m_pBothGuild->OnMouseMove(pt);
					m_pBothChat->OnMouseMove(pt);
					m_pBothWhisper->OnMouseMove(pt);
					m_pBtnVoiceChatInv->OnMouseMove(pt);
					m_pBtnVoiceChatOk->OnMouseMove(pt);
					m_pBtnVoiceChatCan->OnMouseMove(pt);
				}
				if(m_bVCCMoving)
				{
					m_nVCCPosX += (pt.x - m_ptVCCOldPos.x);
					m_nVCCPosY += (pt.y - m_ptVCCOldPos.y);
					if(m_nVCCPosX < 0)
						m_nVCCPosX = 0;
					else if(m_nVCCPosX > g_pD3dApp->GetBackBufferDesc().Width - VOICECHAT_BAR_W)
						m_nVCCPosX = g_pD3dApp->GetBackBufferDesc().Width - VOICECHAT_BAR_W;
					if(m_nVCCPosY < 0)
						m_nVCCPosY = 0;
					else if(m_nVCCPosY > g_pD3dApp->GetBackBufferDesc().Height - VOICECHAT_BAR_H)
						m_nVCCPosY = g_pD3dApp->GetBackBufferDesc().Height - VOICECHAT_BAR_H;
					m_ptVCCOldPos.x = pt.x;
					m_ptVCCOldPos.y = pt.y;

				}
				if(m_bVolumCon)
				{// ���� ũ�� ��Ʈ����.
					m_nPosVolum += (pt.x - m_ptOldVolumPos.x);
					if(m_nPosVolum > VOICECHAT_SPK_W)
					{
						m_nPosVolum = VOICECHAT_SPK_W;
					}else if(m_nPosVolum < 0)
					{
						m_nPosVolum = 0;
					}
					DWORD nVolum;
					float fVolum = ((float)m_nPosVolum/(float)VOICECHAT_SPK_W)*100.0f;
					nVolum = fVolum;				
					
					m_ptOldVolumPos = pt;
					SetVoiceChatVolum(nVolum);

				}
			}
			break;
		case WM_LBUTTONDOWN:
			{
				POINT pt;
				pt.x = LOWORD(lParam);
				pt.y = HIWORD(lParam);
				CheckMouseReverse(&pt);
				if(pt.x > m_nVCCPosX &&
					pt.x < m_nVCCPosX + m_pVoiceChatBG->GetImgSize().x &&
					pt.y > m_nVCCPosY &&
					pt.y < m_nVCCPosY + m_pVoiceChatBG->GetImgSize().y)
				{
					m_pBothParty->OnLButtonDown(pt);
					m_pBothGuild->OnLButtonDown(pt);
					m_pBothChat->OnLButtonDown(pt);
					m_pBothWhisper->OnLButtonDown(pt);
					m_pBtnVoiceChatInv->OnLButtonDown(pt);

					
					if(pt.x > m_nVCCPosX &&
						pt.x < m_nVCCPosX + VOICECHAT_BAR_W &&
						pt.y > m_nVCCPosY &&
						pt.y < m_nVCCPosY + VOICECHAT_BAR_H)
					{
						m_bVCCMoving = TRUE;
						m_ptVCCOldPos = pt;
					}

					if(m_pBtnVoiceChatOk->OnLButtonDown(pt))
					{
					}
					if(m_pBtnVoiceChatCan->OnLButtonDown(pt))
					{
					}
					if(pt.x > VOICECHAT_SPK_POS_X + m_nPosVolum &&
						pt.x < VOICECHAT_SPK_POS_X + m_nPosVolum + m_pImgSpkVolBar->GetImgSize().x &&
						pt.y > VOICECHAT_SPK_POS_Y &&
						pt.y < VOICECHAT_SPK_POS_Y + m_pImgSpkVolBar->GetImgSize().y
						&& (g_pGameMain->GetVoiceType() != VOICE_NONE))	// 2008-10-20 by bhsohn VOIP ���� ����
					{
						m_bVolumCon = TRUE;
						m_ptOldVolumPos = pt;
					}
					g_pInterface->SetWindowOrder(WNDVoiceWnd);

					return INF_MSGPROC_BREAK;
				}
			}
			break;
		case WM_LBUTTONUP:
			{
				POINT pt;
				pt.x = LOWORD(lParam);
				pt.y = HIWORD(lParam);
				CheckMouseReverse(&pt);
				m_bVCCMoving = FALSE;
				
				if(m_bVolumCon)
				{// ���� ũ�� ��Ʈ����.				
					if(m_nPosVolum > VOICECHAT_SPK_W)
					{
						m_nPosVolum = VOICECHAT_SPK_W;
					}else if(m_nPosVolum < 0)
					{
						m_nPosVolum = 0;
					}
					DWORD nVolum;
					float fVolum = ((float)m_nPosVolum/(float)VOICECHAT_SPK_W)*100.0f;
					nVolum = fVolum;				

					g_pGameMain->SetVoiceVolum(nVolum);				
					m_bVolumCon = FALSE;
				}
				if(pt.x > m_nVCCPosX &&
					pt.x < m_nVCCPosX + m_pVoiceChatBG->GetImgSize().x &&
					pt.y > m_nVCCPosY &&
					pt.y < m_nVCCPosY + m_pVoiceChatBG->GetImgSize().y)
				{
					if(m_pBothParty->OnLButtonDown(pt))
					{
						if(m_pBothParty->GetBoth() == BUTTON_BOTH_FRONT)
							EndVoiceParty();
						else
							SendVoiceParty();
					}
					if(m_pBothGuild->OnLButtonDown(pt))
					{
						if(m_pBothGuild->GetBoth() == BUTTON_BOTH_FRONT)
							EndVoiceGuild();
						else
							SendVoiceGuild();

					}
					if(m_pBothChat->OnLButtonDown(pt))
					{
//						m_pBothGuild->ChangeBoth(TRUE);
//						m_pBothParty->ChangeBoth(TRUE);
//						m_pBothWhisper->ChangeBoth(TRUE);
//						m_pBothChat->ChangeBoth();
					}
					if(m_pBothWhisper->OnLButtonDown(pt))
					{
						// 2008-10-20 by bhsohn VOIP ���� ����
//						m_pBothGuild->ChangeBoth(TRUE);
//						m_pBothChat->ChangeBoth(TRUE);
//						m_pBothParty->ChangeBoth(TRUE);
//						if(m_pBothWhisper->GetBoth() == BUTTON_BOTH_FRONT)
//						{
//							// ����ä�� ����.
//							SetVOIPExit();
//						}else
//						{
//							// 2008-07-15 by dgwoo ���⼱ on��ų�� ������ off�� �����ϴ�.
//							//OnSoundButtonClick();
//						}
						// 2009-01-19 by bhsohn VOIP 1:1��ȭ ���� �ȵǴ� ���� �ذ�
						SetVOIPExit();						
						// end 2009-01-19 by bhsohn VOIP 1:1��ȭ ���� �ȵǴ� ���� �ذ�
					}
					if(m_pBtnVoiceChatInv->OnLButtonUp(pt))
					{
						OnSoundButtonClick();
					}
					if(m_pBtnVoiceChatOk->OnLButtonUp(pt))
					{
						ShowVoiceChatControl(FALSE);
					}
					if(m_pBtnVoiceChatCan->OnLButtonUp(pt))
					{
						ShowVoiceChatControl(FALSE);
						// 2011. 1. 12 by jskim UI �̹��� ��ư ���� ����
						g_pInterface->m_pToolTip->m_bToolTipState = FALSE;
						// end 2011. 1. 12 by jskim UI �̹��� ��ư ���� ����
						//--------------------------------------------------------------------------//
	//					COPYDATASTRUCT	copyData;
	//					DWORD			nVolum = 0;
	//					memset(&copyData, 0x00, sizeof(COPYDATASTRUCT));
	//					AV_MSG_WM_COPYDATA voIP(_1to1Call, AV_MT_GET_SPK_VOLUME, 0);
	//					copyData.dwData = (DWORD)voIP;
	//					copyData.lpData = NULL;
	//					copyData.cbData = 0;
	//					::SendMessage(g_pD3dApp->m_VOIPState.m_hWndAtumVoIPClient, WM_COPYDATA, (WPARAM)g_pD3dApp->GetHwnd(), (LPARAM)&copyData);
						//--------------------------------------------------------------------------//
					}						
					return INF_MSGPROC_BREAK;
				}


			}
			break;
	}
	return INF_MSGPROC_NORMAL;	
}
int	CINFGameMainChat::WndProcMacro(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if(FALSE == m_bShowMacro)
	{
		return INF_MSGPROC_NORMAL;
	}
	int i;
	switch(uMsg)
	{
		case WM_MOUSEMOVE:
			{
				POINT pt;
				pt.x = LOWORD(lParam);
				pt.y = HIWORD(lParam);
				CheckMouseReverse(&pt);

				if(m_bMacroMove)
				{
					m_nMacroX += (pt.x - m_nMacroOldX);
					m_nMacroY += (pt.y - m_nMacroOldY);
					if(m_nMacroX < 0)
						m_nMacroX = 0;
					else if(m_nMacroX > g_pD3dApp->GetBackBufferDesc().Width - CHAT_MACRO_W)
						m_nMacroX = g_pD3dApp->GetBackBufferDesc().Width - CHAT_MACRO_W;
					if(m_nMacroY < 0)
						m_nMacroY = 0;
					else if(m_nMacroY > g_pD3dApp->GetBackBufferDesc().Height - CHAT_MACRO_H)
						m_nMacroY = g_pD3dApp->GetBackBufferDesc().Height - CHAT_MACRO_H;
					m_nMacroOldX = pt.x;
					m_nMacroOldY = pt.y;
				}

				for(i = 0; i < CHAT_MACRO_INPUT_COUNT ; i++)
				{
					m_pBtnChatMacro[i]->OnMouseMove(pt);
				}
				m_pBtnMacroOK->OnMouseMove(pt);
				m_pBtnMacroCancel->OnMouseMove(pt);

			}
			break;
		case WM_LBUTTONDOWN:
			{
				POINT pt;
				pt.x = LOWORD(lParam);
				pt.y = HIWORD(lParam);
				CheckMouseReverse(&pt);
				if(pt.x > m_nMacroX &&
					pt.x < m_nMacroX + m_pChatMacroBG->GetImgSize().x &&
					pt.y > m_nMacroY &&
					pt.y < m_nMacroY + m_pChatMacroBG->GetImgSize().y)
				{
					if(pt.x > m_nMacroX &&
						pt.x < m_nMacroX + CHAT_MACRO_BAR_W &&
						pt.y > m_nMacroY &&
						pt.y < m_nMacroY + CHAT_MACRO_BAR_H)
					{
						m_bMacroMove = TRUE;
						m_nMacroOldX = pt.x;
						m_nMacroOldY = pt.y;
					}

					for(i = 0; i < CHAT_MACRO_INPUT_COUNT ; i++)
					{
						m_pBtnChatMacro[i]->OnLButtonDown(pt);
					}
					m_pBtnMacroOK->OnLButtonDown(pt);
					m_pBtnMacroCancel->OnLButtonDown(pt);
					g_pInterface->SetWindowOrder(WNDMacroWnd);
					if(pt.x > m_nMacroX &&
						pt.x < m_nMacroX + CHAT_MACRO_W &&
						pt.y > m_nMacroY &&
						pt.y < m_nMacroY + CHAT_MACRO_H)
					{
						return INF_MSGPROC_BREAK;
					}
					
				}

			}
			break;
		case WM_LBUTTONUP:
			{
				POINT pt;
				pt.x = LOWORD(lParam);
				pt.y = HIWORD(lParam);
				CheckMouseReverse(&pt);
				m_nActMacro = -1;
				m_bMacroMove = FALSE;
				if(pt.x > m_nMacroX &&
					pt.x < m_nMacroX + CHAT_MACRO_BAR_W &&
					pt.y > m_nMacroY &&
					pt.y < m_nMacroY + CHAT_MACRO_BAR_H)
				{
					m_bMacroMove = FALSE;
					m_nMacroOldX = 0;
					m_nMacroOldX = 0;
				}

				for(i = 0; i < CHAT_MACRO_INPUT_COUNT ; i++)
				{
					if(m_pBtnChatMacro[i]->OnLButtonUp(pt))
					{
						if(strlen(m_strTempMacro) > 0)
						{
							m_pBtnChatMacro[i]->ChangeBoth();
							if(m_pBtnChatMacro[i]->GetBoth() == BUTTON_BOTH_FRONT)
							{
								m_sMacroStr[i].bAppl = FALSE;
							}
							else
							{
								m_sMacroStr[i].bAppl = TRUE;
								memcpy(m_sMacroStr[i].strMacro, m_strTempMacro,SIZE_MAX_CHAT_MESSAGE);
								m_sMacroStr[i].fTime = CHAT_MACRO_OUTPUT_TIME;
							}
						}
						return INF_MSGPROC_BREAK;
					}else if(pt.x > CHAT_MACRO_INPUT_1_X &&
						pt.x < CHAT_MACRO_INPUT_1_X + CHAT_MACRO_INPUT_W &&
						pt.y > CHAT_MACRO_INPUT_1_Y + (CHAT_MACRO_APPL_GAP_Y * i) &&
						pt.y < CHAT_MACRO_INPUT_1_Y + CHAT_MACRO_INPUT_H + (CHAT_MACRO_APPL_GAP_Y * i))
					{// �Է�â Ŭ���� 
						m_nActMacro = i;
						memset(m_strTempMacro,0x00,SIZE_MAX_CHAT_MESSAGE);
						//memset(g_pD3dApp->m_inputkey.m_full_str,0x00,SIZE_MAX_CHAT_MESSAGE);
						g_pD3dApp->CleanText();

						// 2009-03-18 by bhsohn ä��â Ŀ�� �̵� �ý��� �߰�
						InitChatMsgBuff();
						// end 2009-03-18 by bhsohn ä��â Ŀ�� �̵� �ý��� �߰�

						return INF_MSGPROC_BREAK;
					}

				}
				if(m_pBtnMacroOK->OnLButtonUp(pt))
				{
					StartMacro();
					m_bShowMacro = FALSE;
					g_pD3dApp->m_bChatMode = FALSE;
					return INF_MSGPROC_BREAK;
				}
				if(m_pBtnMacroCancel->OnLButtonUp(pt))
				{
					EndMacro();
					m_bShowMacro = FALSE;
					g_pD3dApp->m_bChatMode = FALSE;
					return INF_MSGPROC_BREAK;
				}


			}
			break;
	case WM_KEYDOWN:
		{
			if(m_nActMacro >= 0)
			{
				g_pD3dApp->m_bChatMode = TRUE;
				
				if(wParam == VK_ESCAPE)
				{
					if(m_nActMacro >= 0)
					{
						g_pD3dApp->m_bChatMode = FALSE;
						m_bChatMode = FALSE;
						g_pD3dApp->CleanText();
						
						// 2009-03-18 by bhsohn ä��â Ŀ�� �̵� �ý��� �߰�
						InitChatMsgBuff();
						// end 2009-03-18 by bhsohn ä��â Ŀ�� �̵� �ý��� �߰�

						memset(m_strTempMacro,0x00,SIZE_MAX_CHAT_MESSAGE);
						// 2007.04.24 by bhsohn China IME Working
						// 2009-01-12 by bhsohn Japan Working
#ifdef IS_USE_ONOFF_IME
//#ifdef LANGUAGE_CHINA	
						g_pD3dApp->m_inputkey.EnableIMEControl(g_pD3dApp->m_bChatMode);
#endif
						return INF_MSGPROC_BREAK;
					}
					return INF_MSGPROC_NORMAL;
				}
				// 2007.04.24 by bhsohn China IME Working
				// 2009-01-12 by bhsohn Japan Working
#ifdef IS_USE_ONOFF_IME
//#ifdef LANGUAGE_CHINA	
				g_pD3dApp->m_inputkey.EnableIMEControl(g_pD3dApp->m_bChatMode);
#endif
				// 2007-06-11 by bhsohn China IME Working
#ifdef LANGUAGE_CHINA			
				return g_pD3dApp->m_inputkey.OnIMEKeyDown(g_pD3dApp->GetHwnd(), uMsg, wParam, lParam);					
#endif
				// end 2007-06-11 by bhsohn China IME Working
				return INF_MSGPROC_NORMAL;
			}
		}
		break;
	case WM_IME_STARTCOMPOSITION:
	case WM_IME_NOTIFY:
	case WM_IME_COMPOSITION:
	case WM_INPUTLANGCHANGE:	
	case WM_IME_ENDCOMPOSITION:
	case WM_IME_SETCONTEXT:	
	case WM_CHAR:
		{
			if(m_nActMacro >= 0)
			{
				int bFlag = FALSE;

				if(INF_MSGPROC_BREAK == g_pD3dApp->m_inputkey.KeyMapping(g_pD3dApp->GetHwnd(), uMsg, wParam, lParam))
					bFlag = TRUE;
//				if(g_pD3dApp->m_inputkey.m_str_pos > 57-SIZE_MAX_CHARACTER_NAME)
				if(g_pD3dApp->m_inputkey.m_str_pos > SIZE_MAX_CHAT_MESSAGE-SIZE_MAX_CHARACTER_NAME)
				{
					g_pD3dApp->m_inputkey.m_str_pos = SIZE_MAX_CHAT_MESSAGE-SIZE_MAX_CHARACTER_NAME+1;
//					g_pD3dApp->m_inputkey.m_str_pos = 58-SIZE_MAX_CHARACTER_NAME;
					g_pD3dApp->m_inputkey.m_full_str[g_pD3dApp->m_inputkey.m_str_pos] = NULL;
				}
				if(strlen(g_pD3dApp->m_inputkey.m_full_str)!=0)
				{
					memset(m_strTempMacro,0x00,SIZE_MAX_CHAT_MESSAGE);
					if(wParam == 34 && g_pD3dApp->m_pShuttleChild->m_bOldPToPPos != 200 && g_pD3dApp->m_inputkey.m_str_pos == 1)
					{
						strncpy(g_pD3dApp->m_inputkey.m_full_str+1,
							g_pD3dApp->m_pShuttleChild->m_strChatPToP[g_pD3dApp->m_pShuttleChild->m_bOldPToPPos],
							strlen(g_pD3dApp->m_pShuttleChild->m_strChatPToP[g_pD3dApp->m_pShuttleChild->m_bOldPToPPos]));
						g_pD3dApp->m_inputkey.m_full_str[strlen(g_pD3dApp->m_pShuttleChild->m_strChatPToP[g_pD3dApp->m_pShuttleChild->m_bOldPToPPos])+1] = ' ';
						g_pD3dApp->m_inputkey.m_str_pos += strlen(g_pD3dApp->m_pShuttleChild->m_strChatPToP[g_pD3dApp->m_pShuttleChild->m_bOldPToPPos]) + 1;
					}
					// 2007-11-05 by dgwoo SIZE_MAX_CHAT_MESSAGE����� �Ѿ�� �齺���̽� �̺�Ʈ �߻�.
					strncpy(m_strTempMacro,g_pD3dApp->m_inputkey.m_full_str,strlen(g_pD3dApp->m_inputkey.m_full_str));
					if(strlen(g_pD3dApp->m_inputkey.m_full_str) >= SIZE_MAX_CHAT_MESSAGE)
					{
						keybd_event(VK_BACK, 0, KEYEVENTF_EXTENDEDKEY, 0);
					}

				}
				else
				{
					memset(m_strTempMacro,0x00,SIZE_MAX_CHAT_MESSAGE);
				}
				if(TRUE == bFlag)
					return INF_MSGPROC_BREAK;
			}
		}
		break;
	}
	return INF_MSGPROC_NORMAL;
}
int CINFGameMainChat::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	FLOG( "CINFGameMainChat::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)" );
		
	switch(uMsg)
	{	
	case WM_MOUSEWHEEL:
		{
			POINT pt;
			GetCursorPos(&pt);			
			ScreenToClient(g_pD3dApp->GetHwnd(), &pt);
			CheckMouseReverse(&pt);

			// 2007-03-27 by bhsohn ������ ���� �������̽� ����
			//if(g_pInterface->m_bShowInterface && g_pInterface->m_pTarget->GetShowTargetCodition() == FALSE)
			if(g_pInterface->m_bShowInterface && !g_pShuttleChild->IsObserverMode() && g_pInterface->m_pTarget->GetShowTargetCodition() == FALSE)
			{	
				if( m_bShowChatBox &&
					pt.x > CHAT_CHATBOX_START_X &&
					pt.x < CHAT_CHATBOX_START_X+m_nChatBoxWidth &&
					pt.y > m_nChatBoxYPos &&
					pt.y < m_nChatBoxYPos + m_nChatBoxHeight)
				{
					ChatTab_t *pChatTab = GetChatTabMode();
					if((int)wParam > 0)
					{
						pChatTab->DecreaseRenderStartIndex();
						m_nCurrentRelScrollPosY = CHATBOX_IMAGE_GAB_HEITHT_TOP +
							pChatTab->GetScrollPositionWithRenderStartIndex(m_nChatBoxHeight-(CHATBOX_IMAGE_GAB_HEITHT_TOP+CHATBOX_SCROLL_IMAGE_SIZE_HEIGHT)
							, (m_nChatBoxHeight-CHATBOX_IMAGE_GAB_HEITHT_TOP)/CHAT_FONT_LINE_HEIGHT);

						// 2008. 12. 29 by ckPark ä��â ����ȭ	
						m_listCulledString.clear();
						// end 2008. 12. 29 by ckPark ä��â ����ȭ	
						
						return INF_MSGPROC_BREAK;
					}
					else
					{
						pChatTab->IncreaseRenderStartIndex();
						m_nCurrentRelScrollPosY = CHATBOX_IMAGE_GAB_HEITHT_TOP +
							pChatTab->GetScrollPositionWithRenderStartIndex(m_nChatBoxHeight-(CHATBOX_IMAGE_GAB_HEITHT_TOP+CHATBOX_SCROLL_IMAGE_SIZE_HEIGHT)
							, (m_nChatBoxHeight-CHATBOX_IMAGE_GAB_HEITHT_TOP)/CHAT_FONT_LINE_HEIGHT);					

						// 2008. 12. 29 by ckPark ä��â ����ȭ	
						m_listCulledString.clear();
						// end 2008. 12. 29 by ckPark ä��â ����ȭ	
						
						return INF_MSGPROC_BREAK;
					}				
				}
			}
		}
		break;
	case WM_MOUSEMOVE:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);

			// 2007-03-27 by bhsohn ������ ���� �������̽� ����
			//if(g_pInterface->m_bShowInterface)
			if(g_pInterface->m_bShowInterface && !g_pShuttleChild->IsObserverMode())
			{
				if(pt.x > WISPERBOX_MINIMUM_WINDOW_BUTTON_X && 
					pt.x < WISPERBOX_MINIMUM_WINDOW_BUTTON_X + WISPERBOX_MINIMUM_WINDOW_WIDTH &&
					pt.y > WISPERBOX_MINIMUM_WINDOW_BUTTON_Y &&
					pt.y < WISPERBOX_MINIMUM_WINDOW_BUTTON_Y + WISPERBOX_MINIMUM_WINDOW_HEIGHT)
				{
					m_bShowMiniWisperUnder = TRUE;
				}
				else
				{
					m_bShowMiniWisperUnder = FALSE;
				}
				// �޴� ���� ���� ������
				if( g_pD3dApp->GetTestServerFlag() == FALSE &&
					g_pInterface->m_pTarget->GetShowTargetCodition() == FALSE &&
					g_pD3dApp->m_dwGameState != _SHOP
					&& g_pD3dApp->GetArenaState() != ARENA_STATE_ARENA_GAMING )	// 2008-02-27 by bhsohn ���� �Ʒ��� ����)
				{
					if( pt.x > CHAT_MENU_CASH_START_X-3 &&
						pt.x < CHAT_MENU_CASH_START_X+CHAT_MENU_CASH_START_W-3 && 
						pt.y > CHAT_MENU_CASH_START_Y-m_nCashButtonGab && 
						pt.y < CHAT_MENU_CASH_START_Y-m_nCashButtonGab+CHAT_MENU_CASH_START_H )
					{
						if(m_bCashButton)
							m_nOtherCashList	= CHAT_CASH_BUTTON_STATE_PUH;
						else
							m_nOtherCashList	= CHAT_CASH_BUTTON_STATE_OVE;
					}
					else
					{
						m_nOtherCashList	= CHAT_CASH_BUTTON_STATE_NOM;
					}
				}
				m_pBtnOption->OnMouseMove(pt);
				if(!m_bMenuListUse)
				{
					BOOL bMouse = FALSE;
					for(int i = 1; i <= CHAT_TAB_CHATROOM ; i++)
					{
						if(m_pBtnChatMode[i-1]->OnMouseMove(pt))
						{
							char strTemp[32];
							memset(strTemp,0x00,32);
							bMouse = TRUE;
							switch(i)
							{
								case CHAT_TAB_ALLUSER:
									memcpy(strTemp,STRMSG_C_080519_0100,32);
									break;
								case CHAT_TAB_NORMAL:
									memcpy(strTemp,STRMSG_C_080519_0101,32);
									break;
								case CHAT_TAB_WAR:
									memcpy(strTemp,STRMSG_C_080519_0102,32);
									break;
								case CHAT_TAB_TRADE:
									memcpy(strTemp,STRMSG_C_080519_0103,32);
									break;
								case CHAT_TAB_MAP:
									memcpy(strTemp,STRMSG_C_080519_0104,32);
									break;
								case CHAT_TAB_GUILD:
									memcpy(strTemp,STRMSG_C_080519_0105,32);
									break;
								case CHAT_TAB_PARTY:
									memcpy(strTemp,STRMSG_C_080519_0106,32);
									break;
								case CHAT_TAB_ARENA:
									memcpy(strTemp,STRMSG_C_080519_0107,32);
									break;
								case CHAT_TAB_CHATROOM:
									memcpy(strTemp,STRMSG_C_080519_0108,32);
									break;
							}
							g_pGameMain->SetToolTip(pt.x,pt.y,strTemp);
							
						}
					}
					if(bMouse)
					{
						return INF_MSGPROC_BREAK;
					}
					else
					{
						g_pGameMain->SetToolTip(0,0,NULL);
					}
				}
				


				// �޴� ����(FAQ, ���� ������)
				m_nVoiceMenu = 0;
//				if( m_bMenuListUse &&
//					g_pInterface->m_pTarget->GetShowTargetCodition() == FALSE)
//				{
//					for(int i=CHAT_TAB_NUMBER; i<CHAT_TAB_NUMBER+CHAT_OTHER_MENU_ALL; i++)
//					{
//						if( pt.x > CHAT_MENU_LIST_START_X &&
//							pt.x < CHAT_MENU_LIST_START_X+CHAT_MENU_LIST_W && 
//							pt.y > CHAT_MENU_LIST_START_Y-(CHAT_MENU_LIST_H*(i+1)) && 
//							pt.y < CHAT_MENU_LIST_START_Y-(CHAT_MENU_LIST_H*(i+1))+CHAT_MENU_LIST_H )
//						{
//							m_nOtherMenuList[i-CHAT_TAB_NUMBER] = CHAT_NMENU_BUTTON_STATE_OVE;
//
//							switch(i) 
//							{
//							case CHAT_OTHER_MENU_VOIP:
//								{
//									m_nVoiceMenu = 1;
//								}
//								break;
//							}
//						}
//						else
//						{
//							m_nOtherMenuList[i-CHAT_TAB_NUMBER] = CHAT_NMENU_BUTTON_STATE_NOM;
//						}
//						
//					}
//				}
				
				// �ּ�ȭ �κ� ���� 05.01.21
				if( pt.x > CHAT_CHATTAB_VIEW_FLAG_X &&
					pt.x < CHAT_CHATTAB_VIEW_FLAG_X+CHAT_CHATTAB_VIEW_FLAG_W && 
					pt.y > CHAT_CHATTAB_VIEW_FLAG_Y && pt.y < CHAT_CHATTAB_VIEW_FLAG_Y+CHAT_CHATTAB_VIEW_FLAG_H &&
					g_pInterface->m_pTarget->GetShowTargetCodition() == FALSE)
				{
					m_nChatSizeBtnNormal = BUTTON_BOTH_STATE_UP;
				}
				else
				{
					m_nChatSizeBtnNormal = BUTTON_BOTH_STATE_NORMAL;			
				}
				
				// ä�� �޴�����Ʈ ���� 05.01.21
				if( pt.x > CHAT_MENU_VIEW_X &&
					pt.x < CHAT_MENU_VIEW_X+CHAT_MENU_VIEW_W && 
					pt.y > CHAT_MENU_VIEW_Y && pt.y < CHAT_MENU_VIEW_Y+CHAT_MENU_VIEW_H &&
					g_pInterface->m_pTarget->GetShowTargetCodition() == FALSE)
				{
					if(m_bMenuList)
					{
						m_nMenuListButtonState = CHAT_NMENU_BUTTON_STATE_PUH;						
					}
					else if(m_nMenuListButtonState == CHAT_NMENU_BUTTON_STATE_NOM)
					{
						m_nMenuListButtonState = CHAT_NMENU_BUTTON_STATE_OVE;
					}
				}
				else
				{
					m_nMenuListButtonState = CHAT_NMENU_BUTTON_STATE_NOM;			
				}

				// �ִ�ȭ �κ� ����	
				if(	pt.x > CHAT_CHATBOX_START_X+m_nChatBoxWidth-CHATBOX_IMAGE_GAB_MINIMIZE_WIDTH &&
					pt.x < CHAT_CHATBOX_START_X+m_nChatBoxWidth-CHATBOX_IMAGE_GAB_MINIMIZE_WIDTH+CHATBOX_IMAGE_GAB_MINIMIZE_WIDTH &&
					pt.y > m_nChatBoxYPos + CHAT_MENUBOX_GAB_WIDTH &&
					pt.y < m_nChatBoxYPos + CHAT_MENUBOX_GAB_WIDTH+CHATBOX_IMAGE_GAB_MINIMIZE_HEIGHT &&
					g_pInterface->m_pTarget->GetShowTargetCodition() == FALSE)
				{
					if(m_bWindowSizeMax)
					{
//						m_nSizeMaxButtonstate = CHAT_BUTTON_DOWN;
					}
					else
					{
//						m_nSizeMaxButtonstate = CHAT_BUTTON_UP;
					}
				}
				else
				{
//					m_nSizeMaxButtonstate = CHAT_BUTTON_NORMAL;				
				}
				
				// ä�� ȭ�� ��ũ��
				if(m_bScrollLock)
				{
					int nPointGap = pt.y-m_ptMouse.y;
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
					if(m_nCurrentRelScrollOldPosY+nPointGap < CHATBOX_IMAGE_GAB_HEITHT_TOP + 5)
					{
						m_nCurrentRelScrollPosY = CHATBOX_IMAGE_GAB_HEITHT_TOP + 5;
					}																			  
#else			  
					if(m_nCurrentRelScrollOldPosY+nPointGap < CHATBOX_IMAGE_GAB_HEITHT_TOP)
					{
						m_nCurrentRelScrollPosY = CHATBOX_IMAGE_GAB_HEITHT_TOP;
					}

#endif
					else if(m_nCurrentRelScrollOldPosY+nPointGap > m_nChatBoxHeight-CHATBOX_SCROLL_IMAGE_SIZE_HEIGHT)
					{
						m_nCurrentRelScrollPosY = m_nChatBoxHeight-CHATBOX_SCROLL_IMAGE_SIZE_HEIGHT;
					}
					else 
					{
						m_nCurrentRelScrollPosY = m_nCurrentRelScrollOldPosY + nPointGap;
					}
					ChatTab_t *pChatTab = GetChatTabMode();
					pChatTab->SetRenderStartIndexWithScrollPositon(m_nChatBoxHeight-(CHATBOX_IMAGE_GAB_HEITHT_TOP+CHATBOX_SCROLL_IMAGE_SIZE_HEIGHT)
						, m_nCurrentRelScrollPosY-CHATBOX_IMAGE_GAB_HEITHT_TOP);


					// 2008. 12. 29 by ckPark ä��â ����ȭ	
					m_listCulledString.clear();
					// end 2008. 12. 29 by ckPark ä��â ����ȭ	
				}
				
				// ���콺 ����Ʈ �ٲٱ�
				if( m_bShowChatBox &&
					pt.x > CHAT_CHATBOX_START_X+m_nChatBoxWidth &&
					pt.x < CHAT_CHATBOX_START_X+m_nChatBoxWidth+CHATBOX_IMAGE_GAB_WIDTH_TOP &&
					pt.y > m_nChatBoxYPos &&
					pt.y < m_nChatBoxYPos+CHATBOX_IMAGE_GAB_HEITHT_TOP)
				{	// ä�ùڽ� Right and Bottom ������ ������ Ŭ��
					
					g_pInterface->m_pTarget->m_bWisperChatBoxMouseFlag = TRUE;
					g_pInterface->m_pTarget->SetMouseType(LEFTBOTTOM_ARROW_IMAGE);
					return INF_MSGPROC_BREAK;
				}
				else
				{
					g_pInterface->m_pTarget->m_bWisperChatBoxMouseFlag = FALSE;
//					g_pInterface->m_pTarget->SetMouseType(NO_ARROW_IMAGE);
				}
				if(m_bShowChatBox)
				{
					if(g_pShuttleChild->GetMyShuttleInfo().GuildUniqueNumber == 0 &&
						m_nChatMode == CHAT_TAB_GUILD)
					{
						m_pBtnGuildQuick->OnMouseMove(pt);
					}
					else if(g_pShuttleChild->m_pClientParty->IsParty() == FALSE &&
						m_nChatMode == CHAT_TAB_PARTY)
					{
						m_pBtnPartyQuick->OnMouseMove(pt);
					}
				}
				if(m_bLockHandle)
				{
					m_nChatBoxWidth += pt.x - m_ptMouse.x;
					m_nChatBoxHeight += m_ptMouse.y - pt.y;
					if(m_nChatBoxWidth > CHAT_CHATBOX_START_DEFAULT_MAX_X) m_nChatBoxWidth = CHAT_CHATBOX_START_DEFAULT_MAX_X;
					if(m_nChatBoxWidth < CHAT_CHATBOX_START_DEFAULT_MIN_X) m_nChatBoxWidth = CHAT_CHATBOX_START_DEFAULT_MIN_X;
					if(m_nChatBoxHeight > CHAT_CHATBOX_START_DEFAULT_MAX_Y) m_nChatBoxHeight = CHAT_CHATBOX_START_DEFAULT_MAX_Y;
					if(m_nChatBoxHeight < CHAT_CHATBOX_START_DEFAULT_MIN_Y) m_nChatBoxHeight = CHAT_CHATBOX_START_DEFAULT_MIN_Y;
					m_ptMouse = pt;
					ChatTab_t *pChatTab = GetChatTabMode();
					m_nCurrentRelScrollPosY = CHATBOX_IMAGE_GAB_HEITHT_TOP +
						pChatTab->GetScrollPositionWithRenderStartIndex(m_nChatBoxHeight-(CHATBOX_IMAGE_GAB_HEITHT_TOP+CHATBOX_SCROLL_IMAGE_SIZE_HEIGHT)
						, (m_nChatBoxHeight-CHATBOX_IMAGE_GAB_HEITHT_TOP)/CHAT_FONT_LINE_HEIGHT);

					// 2008. 12. 29 by ckPark ä��â ����ȭ	
					m_listCulledString.clear();
					// end 2008. 12. 29 by ckPark ä��â ����ȭ

					// 2009. 02. 03 by ckPark ä��â �������̽� ũ�� ����
					stcuctRateRect	stRateRect;
					memset(&stRateRect, 0x00, sizeof(stcuctRateRect));
					stRateRect.fRateWidth	= m_nChatBoxWidth;
					stRateRect.fRateHeight	= m_nChatBoxHeight;
					g_pD3dApp->SetChatInterfacePOS(&stRateRect);
					// end 2009. 02. 03 by ckPark ä��â �������̽� ũ�� ����
				}
				
			}
			else
			{
			}
		}
		break;
	case WM_LBUTTONDOWN:
		{
			// 2007-03-27 by bhsohn ������ ���� �������̽� ����
			//if(g_pInterface->m_bShowInterface && g_pInterface->m_pTarget->GetShowTargetCodition() == FALSE)
			// 2009-02-16 by bhsohn ���콺 ������, ä��â Ŭ�� �ȵǴ� ���� ����
			//if(g_pInterface->m_bShowInterface && !g_pShuttleChild->IsObserverMode() && g_pInterface->m_pTarget->GetShowTargetCodition() == FALSE)
			BOOL bShowMenu = TRUE;
			if(g_pInterface->m_pTarget->GetShowTargetCodition() == TRUE 
				&& !g_pD3dApp->IsPossibleWindowMove())
			{
				bShowMenu = FALSE;
			}			
			if(g_pInterface->m_bShowInterface && !g_pShuttleChild->IsObserverMode() 
				&& bShowMenu)
			{
				POINT pt;
				pt.x = LOWORD(lParam);
				pt.y = HIWORD(lParam);
				CheckMouseReverse(&pt);

				if(pt.x > WISPERBOX_MINIMUM_WINDOW_BUTTON_X && 
					pt.x < WISPERBOX_MINIMUM_WINDOW_BUTTON_X + WISPERBOX_MINIMUM_WINDOW_WIDTH &&
					pt.y > WISPERBOX_MINIMUM_WINDOW_BUTTON_Y &&
					pt.y < WISPERBOX_MINIMUM_WINDOW_BUTTON_Y + WISPERBOX_MINIMUM_WINDOW_HEIGHT)
				{
				// 2010. 03. 16 by jskim �Ӹ�â ���� ����
					if(m_nSmallWindowCount)
				//end 2010. 03. 16 by jskim �Ӹ�â ���� ����
					m_bShowMiniWisper = !m_bShowMiniWisper;
				}


				if(g_pD3dApp->GetTestServerFlag() == FALSE &&
				   g_pD3dApp->m_dwGameState != _SHOP
				   && g_pD3dApp->GetArenaState() != ARENA_STATE_ARENA_GAMING )	// 2008-02-27 by bhsohn ���� �Ʒ��� ����)
				{
#if defined(C_CASH_SHOP_NOT_USE_JWLEE) // 2015-02-04 by jwLee �Ϻ� ĳ���� ����
#else
					// �޴� ���� ���� ������
					if( pt.x > CHAT_MENU_CASH_START_X &&
						pt.x < CHAT_MENU_CASH_START_X+CHAT_MENU_CASH_START_W && 
						pt.y > CHAT_MENU_CASH_START_Y-m_nCashButtonGab && 
						pt.y < CHAT_MENU_CASH_START_Y-m_nCashButtonGab+CHAT_MENU_CASH_START_H &&
						g_pShuttleChild->GetIsUseInterface())						// 2006-06-12 by ispark, �������϶��� ���´�.
					{
						if(!g_pGameMain->m_pTrade->m_bTrading)
						{
							m_bCashButton		= TRUE;
							m_nOtherCashList	= CHAT_CASH_BUTTON_STATE_PUH;
						}
						return INF_MSGPROC_BREAK;
					}
					else
#endif
					{
						m_nOtherCashList	= CHAT_CASH_BUTTON_STATE_NOM;
					}
				}
				m_pBtnOption->OnLButtonDown(pt);
				
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// ä�� �޴� ���� 
//				if(pt.y>CHAT_MENUBOX_START_Y && pt.y<CHAT_MENUBOX_START_Y+CHAT_MENUBOX_WIDTH+CHAT_MENUBOX_HEITHT)
//				{
//					int i; for(i=0;i<CHAT_MENUBOX_SELECT_COUNT;i++)
//					{
//						if(pt.x>CHAT_MENUBOX_START_X+CHAT_MENUBOX_GAB_WIDTH+CHAT_MENUBOX_WIDTH*i 
//							&& pt.x<CHAT_MENUBOX_START_X+CHAT_MENUBOX_GAB_WIDTH+CHAT_MENUBOX_WIDTH*i+CHAT_MENUBOX_WIDTH-CHAT_MENUBOX_GAB_WIDTH)
//						{
//							//m_nCurrentTabIndex = i;
//							m_bChatCurrentSelect[m_nSelectChatTab][i] = !m_bChatCurrentSelect[m_nSelectChatTab][i];
//							if(m_nCurrentTabIndex == CHAT_TAB_SOUND) m_bLockSoundButton = TRUE;
//
//							return INF_MSGPROC_BREAK;
//						}
//					}
//				}
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// 2008-05-08 by dgwoo ä�� �ý��� ���� �ҽ� �߰�.
				if(!m_bMenuListUse)
				{
					for(int i = 0; i < CHAT_TAB_CHATROOM ; i++)
					{
						m_pBtnChatMode[i]->OnLButtonDown(pt);	
					}
				}

				// ä��â �ִ�ȭ 
				if( pt.x > CHAT_CHATTAB_VIEW_FLAG_X &&
					pt.x < CHAT_CHATTAB_VIEW_FLAG_X+CHAT_CHATTAB_VIEW_FLAG_W && 
					pt.y > CHAT_CHATTAB_VIEW_FLAG_Y && pt.y < CHAT_CHATTAB_VIEW_FLAG_Y+CHAT_CHATTAB_VIEW_FLAG_H )
				{
					m_nChatSizeBtnNormal = BUTTON_BOTH_STATE_UP;
					m_bWindowSizeMin = TRUE;
					m_bShowChatBox = !m_bShowChatBox;
					m_pSystemMsgW->SetInterface(m_bShowChatBox);
					SetWisperChatShowInterface(m_bShowChatBox);
					m_bMenuListUse = FALSE;
					return INF_MSGPROC_BREAK;
				}
				else 
				{
					m_nChatSizeBtnNormal = BUTTON_BOTH_STATE_NORMAL;
				}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// ä�� �Է� ��� ����
				if(pt.x > CHAT_INPUT_LANGUAGE_X && pt.x < CHAT_INPUT_LANGUAGE_X+CHAT_INPUT_LANGUAGE_WH &&
					pt.y > CHAT_INPUT_LANGUAGE_Y && pt.y < CHAT_INPUT_LANGUAGE_Y+CHAT_INPUT_LANGUAGE_WH)
				{
					m_bSelectInputLanguage = TRUE;
					return INF_MSGPROC_BREAK;
				}
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// ä�� ȭ�� ũ������ 
				if( m_bShowChatBox &&
					pt.x > CHAT_CHATBOX_START_X+m_nChatBoxWidth &&
					pt.x < CHAT_CHATBOX_START_X+m_nChatBoxWidth+CHATBOX_IMAGE_GAB_WIDTH_TOP &&
					pt.y > m_nChatBoxYPos &&
					pt.y < m_nChatBoxYPos+CHATBOX_IMAGE_GAB_HEITHT_TOP)
				{
					m_bLockHandle = TRUE;
					m_ptMouse = pt;					
					return INF_MSGPROC_BREAK;
				}
				
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// ��ũ�ѹ� ���� 
				if( m_bShowChatBox
					&& pt.x >= m_nChatBoxWidth+CHATBOX_SCROLL_IMAGE_GAP_X
					&& pt.x < m_nChatBoxWidth+CHATBOX_SCROLL_IMAGE_GAP_X + CHATBOX_SCROLL_IMAGE_SIZE_WIDTH
					&& pt.y >= m_nChatBoxYPos+m_nCurrentRelScrollPosY
					&& pt.y < m_nChatBoxYPos+m_nCurrentRelScrollPosY+CHATBOX_SCROLL_IMAGE_SIZE_HEIGHT)
				{
					m_bScrollLock				= TRUE;
					m_ptMouse					= pt;
					m_nCurrentRelScrollOldPosY	= m_nCurrentRelScrollPosY;
					return INF_MSGPROC_BREAK;
				}
				
				/////////////////////////////////////////////////////////////////////////////////////////////////
				// ä�� ��� ���� ����
				if( pt.x>CHAT_INPUT_WINDOW_X && pt.x<CHAT_INPUT_WINDOW_X+CHAT_INPUT_WINDOW_W &&
					pt.y>CHAT_INPUT_WINDOW_Y && pt.y<CHAT_INPUT_WINDOW_Y+CHAT_INPUT_WINDOW_H)
				{
					if(m_bChatMode == FALSE)
					{
						g_pD3dApp->CleanText();
						
						// 2009-03-18 by bhsohn ä��â Ŀ�� �̵� �ý��� �߰�
						InitChatMsgBuff();
						// end 2009-03-18 by bhsohn ä��â Ŀ�� �̵� �ý��� �߰�
					}
					g_pD3dApp->m_bChatMode = TRUE;
					m_bChatMode = TRUE;
					g_pD3dApp->m_pSound->PlayD3DSound(SOUND_INPUT_CHAT, g_pShuttleChild->m_vPos, FALSE);
					// 2007.04.24 by bhsohn China IME Working
					// 2009-01-12 by bhsohn Japan Working
#ifdef IS_USE_ONOFF_IME
//#ifdef LANGUAGE_CHINA	
					g_pD3dApp->m_inputkey.EnableIMEControl(g_pD3dApp->m_bChatMode);
#endif			

					// 2010. 02. 23 by jskim ä�ù��� ���� �� ����ȭ
					// 2009-01-21 by bhsohn ä�� �� ���콺�� Ŭ����, ��!���� ���� �ȵǴ� ���� �ذ�			
// 					if(strlen(g_pD3dApp->m_inputkey.m_full_str)==0)
// 					{
// 						// Ư�� ä�� Ÿ�� �����
// 						if(CheckChatTypeMsg(0, 0))
// 						{							
// 						}
// 						
// 					}
					//end 2010. 02. 23 by jskim ä�ù��� ���� �� ����ȭ
					// end 2009-01-21 by bhsohn Japan IME

					return INF_MSGPROC_BREAK;
				}
//				else
//				{
//					if(m_bChatMode)
//					{
//						g_pD3dApp->m_bChatMode = FALSE;
//						g_pD3dApp->CleanText();
//						memset(m_strInputMessage,0x00,SIZE_MAX_CHAT_MESSAGE);
//						m_bChatMode = FALSE;
//						return INF_MSGPROC_BREAK;
//					}
//				}
				
				////////////////////////////////////////////////////////////////////////////////////////
				// �޴� ����Ʈ ���̱�
				if( pt.x > CHAT_MENU_VIEW_X &&
					pt.x < CHAT_MENU_VIEW_X+CHAT_MENU_VIEW_W && 
					pt.y > CHAT_MENU_VIEW_Y && pt.y < CHAT_MENU_VIEW_Y+CHAT_MENU_VIEW_H  && 
					(g_pShuttleChild->m_bUnitStop == TRUE || g_pD3dApp->m_bCharacter == TRUE || g_pShuttleChild->m_bLandedMove == TRUE
					|| (IS_DT(g_pShuttleChild->m_myShuttleInfo.UnitKind) == TRUE && g_pShuttleChild->m_bIsAir == FALSE)))	// 2013-01-16 by mspark, A��� ���� ��� �� ä�� �޴� ��ư Ŭ���ǵ��� ����
				{
					m_nMenuListButtonState = CHAT_NMENU_BUTTON_STATE_PUH;
					m_bMenuList = TRUE;
					return INF_MSGPROC_BREAK;
				}
				// �޴� ����
				if(m_bMenuListUse)
				{
					// 2014-01-28 by ymjoo VoIP ��� ����
#ifndef C_REMOVE_VOIP_YMJOO
					// ���� ���.
					if(pt.x > CHAT_MENU_LIST_START_X &&
						pt.x < CHAT_MENU_LIST_START_X+CHAT_MENU_LIST_W && 
						pt.y > CHAT_MENU_LIST_START_Y-(CHAT_MENU_LIST_H*CHAT_MENULIST_NUMBER) &&
						pt.y < CHAT_MENU_LIST_START_Y-(CHAT_MENU_LIST_H*CHAT_MENULIST_NUMBER)+CHAT_MENU_LIST_H)
					{
						ShowVoiceChatControl(TRUE);
						m_bMenuListUse = FALSE;
//						COPYDATASTRUCT	copyData;
//						DWORD			nVolum = 0;
//						memset(&copyData, 0x00, sizeof(COPYDATASTRUCT));
//						AV_MSG_WM_COPYDATA voIP(_1to1Call, AV_MT_GET_SPK_VOLUME, 0);
//						copyData.dwData = (DWORD)voIP;
//						copyData.lpData = NULL;
//						copyData.cbData = 0;
//						::SendMessage(g_pD3dApp->m_VOIPState.m_hWndAtumVoIPClient, WM_COPYDATA, (WPARAM)g_pD3dApp->GetHwnd(), (LPARAM)&copyData);
						

						// 2008. 12. 29 by ckPark ä��â ����ȭ	
						m_listCulledString.clear();
						// end 2008. 12. 29 by ckPark ä��â ����ȭ


						return INF_MSGPROC_BREAK;
					}
#endif
					// END 2014-01-28 by ymjoo VoIP ��� ����

					// ����Ŀ ��ư.
					if( pt.x > CHAT_MENU_LIST_START_X &&
						pt.x < CHAT_MENU_LIST_START_X+CHAT_MENU_LIST_W && 
						pt.y > CHAT_MENU_LIST_START_Y-(CHAT_MENU_LIST_H*(CHAT_MENULIST_NUMBER - CHAT_TAB_SPEAKER - 1)) &&
						pt.y < CHAT_MENU_LIST_START_Y-(CHAT_MENU_LIST_H*(CHAT_MENULIST_NUMBER - CHAT_TAB_SPEAKER - 1))+CHAT_MENU_LIST_H )
					{
						m_bChatCurrentSelect[CHAT_TAB_SPEAKER] = !m_bChatCurrentSelect[CHAT_TAB_SPEAKER];
						g_pInterface->SetSpeakerMode(m_bChatCurrentSelect[CHAT_TAB_SPEAKER]);
						g_pInterface->SaveOptionFile();
						if(FALSE == m_bChatCurrentSelect[CHAT_TAB_SPEAKER])
						{
							// GM��ɾ �ƴѰ��� �� �����.
							g_pGameMain->DeleteNotGmMsg();
						}								

						// 2008. 12. 29 by ckPark ä��â ����ȭ	
						m_listCulledString.clear();
						// end 2008. 12. 29 by ckPark ä��â ����ȭ

						return INF_MSGPROC_BREAK;
					}

					for(int i=CHAT_TAB_NORMAL; i<CHAT_MENULIST_NUMBER; i++)
					{						
						if( pt.x > CHAT_MENU_LIST_START_X &&
							pt.x < CHAT_MENU_LIST_START_X+CHAT_MENU_LIST_W && 
							//pt.y > CHAT_MENU_LIST_START_Y-(CHAT_MENU_LIST_H*(i+1)) && 
							//pt.y < CHAT_MENU_LIST_START_Y-(CHAT_MENU_LIST_H*(i+1))+CHAT_MENU_LIST_H )
							pt.y > CHAT_MENU_LIST_START_Y-(CHAT_MENU_LIST_H *(CHAT_MENULIST_NUMBER - i)) &&
							pt.y < CHAT_MENU_LIST_START_Y-(CHAT_MENU_LIST_H*(CHAT_MENULIST_NUMBER - i))+CHAT_MENU_LIST_H )
						{
							char buffer[SIZE_MAX_PACKET];							
							INIT_MSG(MSG_IC_CHAT_CHANGE_CHAT_FLAG, T_IC_CHAT_CHANGE_CHAT_FLAG, pS2Msg, buffer);
							pS2Msg->bitChatType		= 0xFFFF;			// ��� ���������� �⺻ ������
							
							m_bChatCurrentSelect[i] = !m_bChatCurrentSelect[i];
							g_pSOption->m_bChatCurrentSelect[i] = m_bChatCurrentSelect[i];							
							g_pInterface->SaveOptionFile();
							for(int j=0; j<CHAT_MENULIST_NUMBER; j++)
							{
								switch(j)
								{
								case CHAT_TAB_ARENA:
									{
										if(FALSE == m_bChatCurrentSelect[j])
										{
											CLEAR_CHATTYPE_BIT(pS2Msg->bitChatType, CHAT_TYPE_ARENA);
										}
									}
									break;
								
								case CHAT_TAB_PARTY:
									{
										if(FALSE == m_bChatCurrentSelect[j])
										{
											CLEAR_CHATTYPE_BIT(pS2Msg->bitChatType, CHAT_TYPE_PARTY);
										}
									}
									break;
								case CHAT_TAB_GUILD:
									{
										if(FALSE == m_bChatCurrentSelect[j])
										{
											CLEAR_CHATTYPE_BIT(pS2Msg->bitChatType, CHAT_TYPE_GUILD);
										}
									}
									break;
								case CHAT_TAB_MAP:
									{
										if(FALSE == m_bChatCurrentSelect[j])
										{
											CLEAR_CHATTYPE_BIT(pS2Msg->bitChatType, CHAT_TYPE_MAP);
										}
									}
									break;
								case CHAT_TAB_TRADE:
									{
										if(FALSE == m_bChatCurrentSelect[j])
										{
											CLEAR_CHATTYPE_BIT(pS2Msg->bitChatType, CHAT_TYPE_SELL_ALL);
										}
									}
									break;
								case CHAT_TAB_PTOP:
									{
										if(FALSE == m_bChatCurrentSelect[j])
										{
											CLEAR_CHATTYPE_BIT(pS2Msg->bitChatType, CHAT_TYPE_PTOP);
										}
									}
									break;
								case CHAT_TAB_WAR:
									{
										if(FALSE == m_bChatCurrentSelect[j])
										{
											CLEAR_CHATTYPE_BIT(pS2Msg->bitChatType, CHAT_TYPE_WAR);
										}
									}
									break;
								case CHAT_TAB_CHATROOM:
									{
										if(FALSE == m_bChatCurrentSelect[j])
										{
											CLEAR_CHATTYPE_BIT(pS2Msg->bitChatType, CHAT_TYPE_CHATROOM);
										}
									}
									break;
								case CHAT_TAB_SYSTEM:
									{
										if(FALSE == m_bChatCurrentSelect[j])
										{
											CLEAR_CHATTYPE_BIT(pS2Msg->bitChatType, CHAT_TYPE_SYSTEM);
											m_pSystemMsgW->m_bShowChatBox = FALSE;
										}
										else
										{
											m_pSystemMsgW->m_bShowChatBox = TRUE;
										}
									}
									break;
								case CHAT_TAB_HELPDESK:
									{
										if(FALSE == m_bChatCurrentSelect[j])
										{
											CLEAR_CHATTYPE_BIT(pS2Msg->bitChatType, CHAT_TYPE_HELPDESK);
										}
									}
									break;
								}
							}
							g_pIMSocket->Write(buffer, MSG_SIZE(MSG_IC_CHAT_CHANGE_CHAT_FLAG));
							return INF_MSGPROC_BREAK;
						}						
					}
				}				
				// �޴� ����(FAQ, ���� ������)
				int nState = FALSE;

				if(m_bShowChatBox)
				{
					if(g_pShuttleChild->GetMyShuttleInfo().GuildUniqueNumber == 0 &&
						m_nChatMode == CHAT_TAB_GUILD)
					{
						m_pBtnGuildQuick->OnLButtonDown(pt);
					}
					else if(g_pShuttleChild->m_pClientParty->IsParty() == FALSE &&
						m_nChatMode == CHAT_TAB_PARTY)
					{
						m_pBtnPartyQuick->OnLButtonDown(pt);
					}
				}
				if( m_bShowChatBox &&
					pt.x > CHAT_CHATBOX_START_X &&
					pt.x < CHAT_CHATBOX_START_X+m_nChatBoxWidth+CHATBOX_IMAGE_GAB_WIDTH_TOP &&
					pt.y > m_nChatBoxYPos &&
					pt.y < m_nChatBoxYPos+m_nChatBoxHeight)
				{
					return INF_MSGPROC_BREAK;
				}
			}
		}
		break;
	case WM_LBUTTONUP:
		{
			int i=0;

			// 2007-03-27 by bhsohn ������ ���� �������̽� ����
			//if(g_pInterface->m_bShowInterface && g_pInterface->m_pTarget->GetShowTargetCodition() == FALSE)
			// 2009-02-16 by bhsohn ���콺 ������, ä��â Ŭ�� �ȵǴ� ���� ����
			//if(g_pInterface->m_bShowInterface && !g_pShuttleChild->IsObserverMode() && g_pInterface->m_pTarget->GetShowTargetCodition() == FALSE)
			BOOL bShowMenu = TRUE;
			if(g_pInterface->m_pTarget->GetShowTargetCodition() == TRUE 
				&& !g_pD3dApp->IsPossibleWindowMove())
			{
				bShowMenu = FALSE;
			}
			if(g_pInterface->m_bShowInterface && !g_pShuttleChild->IsObserverMode() 
				&& bShowMenu)
			{
				POINT pt;
				pt.x = LOWORD(lParam);
				pt.y = HIWORD(lParam);
				CheckMouseReverse(&pt);				
				if(m_nCurrentTabIndex == CHAT_TAB_SOUND)
				{
					if(m_bLockSoundButton)
					{
						OnSoundButtonClick();
					}
					m_bLockSoundButton = FALSE;
				}
				if(g_pD3dApp->GetTestServerFlag() == FALSE &&
				   g_pD3dApp->m_dwGameState != _SHOP
				   && g_pD3dApp->GetArenaState() != ARENA_STATE_ARENA_GAMING )	// 2008-02-27 by bhsohn ���� �Ʒ��� ����)
				{
					// �޴� ���� ���� ������
					if( pt.x > CHAT_MENU_CASH_START_X &&
						pt.x < CHAT_MENU_CASH_START_X+CHAT_MENU_CASH_START_W && 
						pt.y > CHAT_MENU_CASH_START_Y-m_nCashButtonGab && 
						pt.y < CHAT_MENU_CASH_START_Y-m_nCashButtonGab+CHAT_MENU_CASH_START_H )
					{
						// 2007-12-05 by bhsohn �̷��߿� ĳ���� ������ ��.
						BOOL bCanEnterCashShop = TRUE;
						CHARACTER myShuttle = g_pShuttleChild->GetMyShuttleInfo();

						if(IS_CITY_MAP_INDEX(myShuttle.MapChannelIndex.MapIndex) 
							&& (FALSE == g_pD3dApp->IsMyShuttleCharacter()))
						{
							bCanEnterCashShop = FALSE;
						}
						// 2008-06-24 by bhsohn ���ڻ����� ĳ������ ���ÿ� �߿�� �Ұ����ϰ� ��
						else if(g_pInterface->IsBazarOpen())
						{
							bCanEnterCashShop = FALSE;
						}
						// 2014-12-09 by jwLee �ý��� �޼���â Ȱ��ȭ ���¿��� ���콺 ������ �ڿ��ִ� �������̽� �̺�Ʈ �߻� ���ϵ��� ����
#if defined(C_SYSTEMMSG_BACK_INF_NO_MOUSE_EVENT)	// 2015-04-07 by jwlee C_SYSTEMMSG_BACK_INF_NO_MOUSE_EVENT ������ �߰�
						// 2015-05-13 by jwlee �ý��� �޼���â Ȱ��ȭ ���¿��� ���Ǿƿ�, ���ʽ� EXP, ĳ�ü� �̺�Ʈ �߻� ���ϵ��� ����
//						else if (m_pSystemMsgW->GetInterface())
						else if (m_pSystemMsgW->GetInterface() && m_pSystemMsgW->m_bShowChatBox)
						// end 2015-05-13 by jwlee �ý��� �޼���â Ȱ��ȭ ���¿��� ���Ǿƿ�, ���ʽ� EXP, ĳ�ü� �̺�Ʈ �߻� ���ϵ��� ����
						{
							bCanEnterCashShop = FALSE;
						}
#endif
						// end 2014-12-09 by jwLee �ý��� �޼���â Ȱ��ȭ ���¿��� ���콺 ������ �ڿ��ִ� �������̽� �̺�Ʈ �߻� ���ϵ��� ����
						// end 2008-06-24 by bhsohn ���ڻ����� ĳ������ ���ÿ� �߿�� �Ұ����ϰ� ��

						//if(m_bCashButton)
						if(m_bCashButton && bCanEnterCashShop)
						{
							// 2007-10-18 by bhsohn ������ ĳ���� ������ ����
							// 2009-03-03 by bhsohn �Ϻ� ĳ�� ���� ��ư ǥ��
//#ifndef YEDANG_RELEASE
//#if defined(YEDANG_RELEASE) 
//#else
							EnterCashShop();						
//#endif
							// end 2007-10-18 by bhsohn ������ ĳ���� ������ ����
							m_nOtherCashList	= CHAT_CASH_BUTTON_STATE_OVE;
							m_bCashButton		= FALSE;
							return INF_MSGPROC_BREAK;
						}
					}
				}
				m_bCashButton		= FALSE;
				
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// 2008-05-08 by dgwoo ä�� �ý��� ���� �ҽ� �߰�.
				if(m_pBtnOption->OnLButtonUp(pt))
				{
					ActiveChatOption(TRUE);
				}
				if(!m_bMenuListUse)
				{
					int nPushBtn = -1;
					for(int i = 0; i < CHAT_TAB_CHATROOM ; i++)
					{
						if(m_pBtnChatMode[i]->OnLButtonUp(pt))
						{// ä�� state ����.
							nPushBtn = i;
							
						}						
					}
					if(nPushBtn != -1)
					{
						for(i = 0; i < CHAT_TAB_CHATROOM ; i++)
						{
							if(nPushBtn == i)
							{
								ChangeChatMode(i);
								m_pBtnChatMode[i]->PushButton(TRUE);
							}						
							else
							{
								m_pBtnChatMode[i]->PushButton(FALSE);
							}
						}
					}
					else
					{
						m_pBtnChatMode[m_nChatMode-1]->PushButton(TRUE);
					}

					// 2008. 12. 29 by ckPark ä��â ����ȭ	
					m_listCulledString.clear();
					// end 2008. 12. 29 by ckPark ä��â ����ȭ
				}
				




				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// ä�� �Է� ��� ����
				if(pt.x > CHAT_INPUT_LANGUAGE_X && pt.x < CHAT_INPUT_LANGUAGE_X+CHAT_INPUT_LANGUAGE_WH &&
					pt.y > CHAT_INPUT_LANGUAGE_Y && pt.y < CHAT_INPUT_LANGUAGE_Y+CHAT_INPUT_LANGUAGE_WH &&
					m_bSelectInputLanguage)
				{
					m_bSelectInputLanguage = FALSE;
					g_pD3dApp->m_inputkey.ChangeInputLanguage(g_pD3dApp->GetHwnd());
					return INF_MSGPROC_BREAK;
				}
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// �ִ�ȭ �ּ�ȭ ��ư ����
				if(	pt.x > CHAT_CHATBOX_START_X+m_nChatBoxWidth-CHATBOX_IMAGE_GAB_MINIMIZE_WIDTH &&
					pt.x < CHAT_CHATBOX_START_X+m_nChatBoxWidth-CHATBOX_IMAGE_GAB_MINIMIZE_WIDTH+CHATBOX_IMAGE_GAB_MINIMIZE_WIDTH &&
					pt.y > m_nChatBoxYPos + CHAT_MENUBOX_GAB_WIDTH &&
					pt.y < m_nChatBoxYPos + CHAT_MENUBOX_GAB_WIDTH+CHATBOX_IMAGE_GAB_MINIMIZE_HEIGHT)
				{				
//					m_nSizeMaxButtonstate = CHAT_BUTTON_UP;
					m_bWindowSizeMax = FALSE;				
				}
				else 
				{
					m_bWindowSizeMax = FALSE;
//					m_nSizeMaxButtonstate = CHAT_BUTTON_NORMAL;
				}

				// �޴� ����Ʈ ���̱�
				if( pt.x > CHAT_MENU_VIEW_X &&
					pt.x < CHAT_MENU_VIEW_X+CHAT_MENU_VIEW_W && 
					pt.y > CHAT_MENU_VIEW_Y && pt.y < CHAT_MENU_VIEW_Y+CHAT_MENU_VIEW_H  && 
					(g_pShuttleChild->m_bUnitStop == TRUE || g_pD3dApp->m_bCharacter == TRUE || g_pShuttleChild->m_bLandedMove == TRUE
					|| (IS_DT(g_pShuttleChild->m_myShuttleInfo.UnitKind) == TRUE && g_pShuttleChild->m_bIsAir == FALSE)))	// 2013-01-16 by mspark, A��� ���� ��� �� ä�� �޴� ��ư Ŭ���ǵ��� ����
				{
					if(m_bMenuList)
					{
						g_pInterface->SetWindowOrder(WNDMainChatStartMenu);
						m_bMenuListUse = !m_bMenuListUse;						
					}
					m_nMenuListButtonState		= CHAT_NMENU_BUTTON_STATE_OVE;
				}
				m_bMenuList = FALSE;

				
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				if(m_bShowChatBox)
				{
					if(g_pShuttleChild->GetMyShuttleInfo().GuildUniqueNumber == 0 &&
						m_nChatMode == CHAT_TAB_GUILD)
					{
						if(m_pBtnGuildQuick->OnLButtonUp(pt))
						{
							if(g_pShuttleChild->GetIsUseInterface())
							{
								g_pGameMain->m_pCommunity->ShowCommunityWindow(TRUE,COMMUNITY_GUILD);
							}
							else
							{
							}

						}
					}
					else if(g_pShuttleChild->m_pClientParty->IsParty() == FALSE &&
						m_nChatMode == CHAT_TAB_PARTY)
					{
						if(m_pBtnPartyQuick->OnLButtonUp(pt))
						{
							if(g_pShuttleChild->GetIsUseInterface())
							{
								g_pGameMain->m_pCommunity->ShowCommunityWindow(TRUE);
							}
							else
							{
							}

						}
					}
				}

				if(m_bLockHandle)
				{
					m_bLockHandle = FALSE;
				}
				m_bScrollLock = FALSE;
			}
		}
		break;
	case WM_KEYDOWN:
		{	
			if(wParam == VK_ESCAPE)
			{
				if(m_bChatMode)
				{
					g_pD3dApp->m_bChatMode = FALSE;
					m_bChatMode = FALSE;
					g_pD3dApp->CleanText();
					
					memset(m_strInputMessage,0x00,SIZE_MAX_CHAT_MESSAGE);

					// 2009-03-18 by bhsohn ä��â Ŀ�� �̵� �ý��� �߰�
					InitChatMsgBuff();
					// end 2009-03-18 by bhsohn ä��â Ŀ�� �̵� �ý��� �߰�

					// by bhsohn 2007-03-12 China Working
					// 2009-01-12 by bhsohn Japan Working
#ifdef IS_USE_ONOFF_IME
//#ifdef LANGUAGE_CHINA
					// 2007.04.24 by bhsohn China IME Working
					g_pD3dApp->m_inputkey.EnableIMEControl(g_pD3dApp->m_bChatMode);
#endif
					return INF_MSGPROC_BREAK;
				}
				return INF_MSGPROC_NORMAL;
			}

			if(lParam == WM_KEYDOWN_LPARAM_T)
			{
				// 2007-03-27 by bhsohn ������ ���� �������̽� ����
				//if(g_pInterface->m_bShowInterface && m_bChatMode == FALSE && g_pD3dApp->m_bChatMode == FALSE)
				if(g_pInterface->m_bShowInterface && !g_pShuttleChild->IsObserverMode() && m_bChatMode == FALSE && g_pD3dApp->m_bChatMode == FALSE)
				{
					if(m_bShowChatBox == FALSE)
					{
//						m_nSizeMinButtonstate = CHAT_NMENU_BUTTON_STATE_PUH;
						m_bWindowSizeMin = TRUE;
						m_bShowChatBox = TRUE;
						m_pSystemMsgW->SetInterface(TRUE);
						SetWisperChatShowInterface(TRUE);
						return INF_MSGPROC_BREAK;
					}
					else
					{
//						m_nSizeMaxButtonstate = CHAT_BUTTON_DOWN;
						m_pSystemMsgW->SetInterface(FALSE);
						SetWisperChatShowInterface(FALSE);
						m_bWindowSizeMax = TRUE;
						m_bShowChatBox = FALSE;
						m_nCurrentRelScrollPosY			= m_nChatBoxHeight-CHATBOX_SCROLL_IMAGE_SIZE_HEIGHT;
						ChatTab_t *pChatTab = GetChatTabMode();
						pChatTab->SetRenderStartIndexWithScrollPositon(
							m_nChatBoxHeight-(CHATBOX_IMAGE_GAB_HEITHT_TOP+CHATBOX_SCROLL_IMAGE_SIZE_HEIGHT), 
							m_nCurrentRelScrollPosY-CHATBOX_IMAGE_GAB_HEITHT_TOP);
						return INF_MSGPROC_BREAK;
					}
				}
				
			}
			if(wParam == VK_RETURN)
			{				
				// 2008-07-01 by dgwoo EnterŰ�� 1������ ���ѹ߻� ����.
				g_pShuttleChild->m_bLButtonState = FALSE;
				g_pShuttleChild->m_bRButtonState = FALSE;
				m_bChatMode = !m_bChatMode;
				g_pD3dApp->m_bChatMode = m_bChatMode;
				
				// by bhsohn 2007-03-12 China Working
				// 2009-01-12 by bhsohn Japan Working
			#ifdef IS_USE_ONOFF_IME
			//#ifdef LANGUAGE_CHINA
				// 2007.04.24 by bhsohn China IME Working
				g_pD3dApp->m_inputkey.EnableIMEControl(g_pD3dApp->m_bChatMode);
			#endif
				// end by bhsohn 2007-03-12 China Working

				
				// 2005-04-26 by jschoi - ä�� Ÿ�� ����
				char strChatType = '\0';

				// 2007-02-23 by bhsohn ���� ä��â ���׼���
				BOOL bBlankMsg = FALSE;
				// end 2007-02-23 by bhsohn ���� ä��â ���׼���

				// 2007-06-21 by bhsohn China IME Working
#ifdef LANGUAGE_CHINA
				ConvertChinaInputMessage(m_strInputMessage);								
#endif
				// end 2007-06-21 by bhsohn China IME Working

				if(!m_bChatMode)
				{
					BOOL bSendSpecialChat = FALSE;

					// 2010. 04. 09 by ckPark Ŭ���̾�Ʈ ���ö����� ���� �߰�
					//if(m_strInputMessage[0] == '~')
					if( m_strInputMessage[0] == CHAT_ALL )
					// end 2010. 04. 09 by ckPark Ŭ���̾�Ʈ ���ö����� ���� �߰�
					{// ���� ä��
						if(COMPARE_RACE(g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.Race,RACE_OPERATION|RACE_GAMEMASTER))
						{
							if(strlen(m_strInputMessage) > 1)
							{
								g_pD3dApp->m_pIMSocket->SendChat(T_IC_CHAT_ALL, g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.CharacterName, m_strInputMessage+1 );
								bSendSpecialChat = TRUE;
							}
							// 2007-02-23 by bhsohn ���� ä��â ���׼���
							else if(strlen(m_strInputMessage) == 1)
							{
								bBlankMsg = TRUE;
							}							
							// end 2007-02-23 by bhsohn ���� ä��â ���׼���

							// 2010. 04. 09 by ckPark Ŭ���̾�Ʈ ���ö����� ���� �߰�
							//strChatType = '~';
							strChatType = CHAT_ALL;
							// end 2010. 04. 09 by ckPark Ŭ���̾�Ʈ ���ö����� ���� �߰�
						}
					}
					// 2010. 04. 09 by ckPark Ŭ���̾�Ʈ ���ö����� ���� �߰�
					//else if(m_strInputMessage[0] == '@')
					else if( m_strInputMessage[0] == CHAT_GUILD )
					// end 2010. 04. 09 by ckPark Ŭ���̾�Ʈ ���ö����� ���� �߰�
					{// ��� ä��
						// 2008-07-21 by bhsohn �Ʒ������� ����  �ȵǴ� ���� �ذ�
						//if(g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.GuildUniqueNumber != 0)
						//CHARACTER* pMainInfo = g_pD3dApp->GetMFSMyShuttleInfo();
						// 2008-10-20 by bhsohn VOIP ���� ����
						//if(pMainInfo && pMainInfo->GuildUniqueNumber != 0)
						UID32_t	uGuildUniqueNumber = g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.GuildUniqueNumber;
						if(g_pD3dApp->GetArenaState() == ARENA_STATE_ARENA_GAMING)
						{
							CHARACTER* pMainInfo = g_pD3dApp->GetMFSMyShuttleInfo();
							if(pMainInfo)
							{
								uGuildUniqueNumber = pMainInfo->GuildUniqueNumber;
							}
						}
						if(uGuildUniqueNumber != 0)
						{
							if(strlen(m_strInputMessage) > 1)
							{
								g_pD3dApp->m_pIMSocket->SendChat(T_IC_CHAT_GUILD, g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.CharacterName, m_strInputMessage+1 );
								bSendSpecialChat = TRUE;
							}
							// 2007-02-23 by bhsohn ���� ä��â ���׼���
							else if(strlen(m_strInputMessage) == 1)
							{
								bBlankMsg = TRUE;
							}							
							// end 2007-02-23 by bhsohn ���� ä��â ���׼���

							// 2010. 04. 09 by ckPark Ŭ���̾�Ʈ ���ö����� ���� �߰�
							//strChatType = '@'; 
							strChatType = CHAT_GUILD; 
							// end 2010. 04. 09 by ckPark Ŭ���̾�Ʈ ���ö����� ���� �߰�
						}
					}
					// 2010. 04. 09 by ckPark Ŭ���̾�Ʈ ���ö����� ���� �߰�
					//else if(m_strInputMessage[0] == '%')
					else if( m_strInputMessage[0] == CHAT_ARENA )
					// end 2010. 04. 09 by ckPark Ŭ���̾�Ʈ ���ö����� ���� �߰�
					{// �Ʒ��� ä��
						if(strlen(m_strInputMessage) > 1)
						{
							g_pIMSocket->SendChat(T_IC_CHAT_ARENA, g_pShuttleChild->m_myShuttleInfo.CharacterName, m_strInputMessage+1 );
							bSendSpecialChat = TRUE;
						}
						// 2007-02-23 by bhsohn ���� ä��â ���׼���
						else if(strlen(m_strInputMessage) == 1)
						{
							bBlankMsg = TRUE;
						}							
						// end 2007-02-23 by bhsohn ���� ä��â ���׼���

						// 2010. 04. 09 by ckPark Ŭ���̾�Ʈ ���ö����� ���� �߰�
						//strChatType = '%';
						strChatType = CHAT_ARENA;
						// end 2010. 04. 09 by ckPark Ŭ���̾�Ʈ ���ö����� ���� �߰�
					}
					// 2010. 04. 09 by ckPark Ŭ���̾�Ʈ ���ö����� ���� �߰�
					//else if(m_strInputMessage[0] == '^')
					else if( m_strInputMessage[0] == CHAT_WAR )
					// end 2010. 04. 09 by ckPark Ŭ���̾�Ʈ ���ö����� ���� �߰�
					{// ���� ä��
						if(strlen(m_strInputMessage) > 1)
						{
							g_pIMSocket->SendChat(T_IC_CHAT_WAR, g_pShuttleChild->m_myShuttleInfo.CharacterName, m_strInputMessage+1 );
							bSendSpecialChat = TRUE;
						}
						// 2007-02-23 by bhsohn ���� ä��â ���׼���
						else if(strlen(m_strInputMessage) == 1)
						{
							bBlankMsg = TRUE;
						}							
						// end 2007-02-23 by bhsohn ���� ä��â ���׼���

						// 2010. 04. 09 by ckPark Ŭ���̾�Ʈ ���ö����� ���� �߰�
						//strChatType = '^';
						strChatType = CHAT_WAR;
						// end 2010. 04. 09 by ckPark Ŭ���̾�Ʈ ���ö����� ���� �߰�
					}
#if _RAT_CHAT_SYSTEM
					else if (m_strInputMessage[0] == _RAT_CHAT_ALL_INFLUENCE)
					{
						if(strlen(m_strInputMessage) > 1)
						{
							g_pIMSocket->SendChat(T_IC_CHAT_INFLUENCE_ALL_RAT, g_pShuttleChild->m_myShuttleInfo.CharacterName, m_strInputMessage+1 );
							bSendSpecialChat = TRUE;
						}

						else if(strlen(m_strInputMessage) == 1)
						{
							bBlankMsg = TRUE;
						}							
	
						//strChatType = '>';
						strChatType = _RAT_CHAT_ALL_INFLUENCE;
					}
#endif
					// 2010. 04. 09 by ckPark Ŭ���̾�Ʈ ���ö����� ���� �߰�
					//else if(m_strInputMessage[0] == '#')
					else if( m_strInputMessage[0] == CHAT_PARTY )
					// end 2010. 04. 09 by ckPark Ŭ���̾�Ʈ ���ö����� ���� �߰�
					{// ��� ä��
						if(g_pShuttleChild->m_pClientParty->GetPartyInfo().bPartyType != _NOPARTY)
						{
							if(strlen(m_strInputMessage) > 1)
							{
								g_pIMSocket->SendChat(T_IC_CHAT_PARTY, g_pShuttleChild->m_myShuttleInfo.CharacterName, m_strInputMessage+1 );
								bSendSpecialChat = TRUE;
							}
							// 2007-02-23 by bhsohn ���� ä��â ���׼���
							else if(strlen(m_strInputMessage) == 1)
							{
								bBlankMsg = TRUE;
							}							
							// end 2007-02-23 by bhsohn ���� ä��â ���׼���

							// 2010. 04. 09 by ckPark Ŭ���̾�Ʈ ���ö����� ���� �߰�
							//strChatType = '#';
							strChatType = CHAT_PARTY;
							// end 2010. 04. 09 by ckPark Ŭ���̾�Ʈ ���ö����� ���� �߰�
						}
					}
					// 2010. 04. 09 by ckPark Ŭ���̾�Ʈ ���ö����� ���� �߰�
					//else if(m_strInputMessage[0] == '!')
					else if( m_strInputMessage[0] == CHAT_MAP )
					// end 2010. 04. 09 by ckPark Ŭ���̾�Ʈ ���ö����� ���� �߰�
					{// ����ü ä��
						if(strlen(m_strInputMessage) > 1)
						{
							g_pD3dApp->m_pIMSocket->SendChat(T_IC_CHAT_MAP, g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.CharacterName, m_strInputMessage+1 );
							bSendSpecialChat = TRUE;
						}
						// 2007-02-23 by bhsohn ���� ä��â ���׼���
						else if(strlen(m_strInputMessage) == 1)
						{
							bBlankMsg = TRUE;
						}							
						// end 2007-02-23 by bhsohn ���� ä��â ���׼���

						// 2010. 04. 09 by ckPark Ŭ���̾�Ʈ ���ö����� ���� �߰�
						//strChatType = '!';
						strChatType = CHAT_MAP;
						// end 2010. 04. 09 by ckPark Ŭ���̾�Ʈ ���ö����� ���� �߰�
					}
					// 2010. 04. 09 by ckPark Ŭ���̾�Ʈ ���ö����� ���� �߰�
					//else if(m_strInputMessage[0] == '$')
					else if( m_strInputMessage[0] == CHAT_SELL_ALL )
					// end 2010. 04. 09 by ckPark Ŭ���̾�Ʈ ���ö����� ���� �߰�
					{// �Ÿ� ä��
						if(strlen(m_strInputMessage) > 1)
						{
							g_pD3dApp->m_pIMSocket->SendChat(T_IC_CHAT_SELL_ALL, g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.CharacterName, m_strInputMessage+1 );
							bSendSpecialChat = TRUE;
						}
						// 2007-02-23 by bhsohn ���� ä��â ���׼���
						else if(strlen(m_strInputMessage) == 1)
						{
							bBlankMsg = TRUE;
						}							
						// end 2007-02-23 by bhsohn ���� ä��â ���׼���

						// 2010. 04. 09 by ckPark Ŭ���̾�Ʈ ���ö����� ���� �߰�
						//strChatType = '$';
						strChatType = CHAT_SELL_ALL;
						// end 2010. 04. 09 by ckPark Ŭ���̾�Ʈ ���ö����� ���� �߰�
					}
					// 2010. 04. 09 by ckPark Ŭ���̾�Ʈ ���ö����� ���� �߰�
					//else if(m_strInputMessage[0] == '&')
					else if( m_strInputMessage[0] == CHAT_CHATROOM )
					// end 2010. 04. 09 by ckPark Ŭ���̾�Ʈ ���ö����� ���� �߰�
					{// ���� ����ü ä��
						if(strlen(m_strInputMessage) > 1)
						{
							g_pD3dApp->m_pIMSocket->SendChat(T_IC_CHAT_CHATROOM, g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.CharacterName, m_strInputMessage+1 );
							bSendSpecialChat = TRUE;
						}
						// 2007-02-23 by bhsohn ���� ä��â ���׼���
						else if(strlen(m_strInputMessage) == 1)
						{
							bBlankMsg = TRUE;
						}							
						// end 2007-02-23 by bhsohn ���� ä��â ���׼���

						// 2010. 04. 09 by ckPark Ŭ���̾�Ʈ ���ö����� ���� �߰�
						//strChatType = '&';
						strChatType = CHAT_CHATROOM;
						// end 2010. 04. 09 by ckPark Ŭ���̾�Ʈ ���ö����� ���� �߰�
					}
					// 2010. 04. 09 by ckPark Ŭ���̾�Ʈ ���ö����� ���� �߰�
					//else if(m_strInputMessage[0] == '"')
					else if( m_strInputMessage[0] == CHAT_PTOP )
					// end 2010. 04. 09 by ckPark Ŭ���̾�Ʈ ���ö����� ���� �߰�
					{// 1:1 �ӼӸ� @ä��
						char name[SIZE_MAX_CHARACTER_NAME];
						memset(name,0x00,SIZE_MAX_CHARACTER_NAME);
						int n = 1;
						bool bIsPToP = false;
						while(1)
						{
							if(m_strInputMessage[n] == ' ' || m_strInputMessage[n] == NULL)
							{
								bIsPToP = TRUE;
								break;
							}

							n++;
							if(n==SIZE_MAX_CHARACTER_NAME)
								break;
						}
						if(bIsPToP && n != 1)
						{
							// 2006-09-28 by ispark, ������ ���ٸ� �޼��� ������ ����
							if(strlen(m_strInputMessage+1+n) == 0)
							{
								break;
							}
							
							// 2008-02-26 by bhsohn ���� �Ʒ��� ���� ���� ����
							if(g_pD3dApp->GetArenaState() == ARENA_STATE_ARENA_GAMING )
							{
								// �Ʒ��� �����߿��� �ӼӸ� ����
								break;
							}

 							memcpy(name,m_strInputMessage+1,(n-1));
							
							// 2008-07-14 by bhsohn EP3 ���� ó��
							if(g_pGameMain->IsRejectUser(name))
							{
								g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080714_0207,COLOR_ERROR);//"\\y�ź� ��Ͽ� ��ϵ� ����Դϴ�."
								break;
							}
							// 2008-06-20 by bhsohn EP3 �ɼǰ��� ó��
							if(!g_pD3dApp->IsOptionEtc(OPTION_RADIO_WHISPER))
							{
								// �ӼӸ� ������.
								g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080716_0203,COLOR_ERROR);//"�ӼӸ� �ź� ���� �Դϴ�."
								break;
							}
							// end 2008-06-20 by bhsohn EP3 �ɼǰ��� ó��
							// end 2008-07-14 by bhsohn EP3 ���� ó��
							g_pD3dApp->m_pIMSocket->SendChat(T_IC_CHAT_PTOP, name, m_strInputMessage+1+n );
							bSendSpecialChat = TRUE;
							bool bCheckChat = false;
							int i; for(i=0;i<MAX_CHAT_PTOP_CONT;i++)
							{
								if(!stricmp(g_pD3dApp->m_pShuttleChild->m_strChatPToP[i],name))
								{
									bCheckChat = true;
									g_pD3dApp->m_pShuttleChild->m_bOldPToPPos = i;
									break;
								}
							}
							if(!bCheckChat)
							{
								memset(g_pD3dApp->m_pShuttleChild->m_strChatPToP[g_pD3dApp->m_pShuttleChild->m_bCurPToPPos],0x00,SIZE_MAX_CHARACTER_NAME);
								strncpy(g_pD3dApp->m_pShuttleChild->m_strChatPToP[g_pD3dApp->m_pShuttleChild->m_bCurPToPPos],name,sizeof(name));
								g_pD3dApp->m_pShuttleChild->m_bOldPToPPos = g_pD3dApp->m_pShuttleChild->m_bCurPToPPos;
								g_pD3dApp->m_pShuttleChild->m_bCurPToPPos++;
								if(g_pD3dApp->m_pShuttleChild->m_bCurPToPPos == MAX_CHAT_PTOP_CONT)
									g_pD3dApp->m_pShuttleChild->m_bCurPToPPos = 0;
							}
						}
					}
					// 2006-04-21 by ispark, ������ ����
					// 2010. 04. 09 by ckPark Ŭ���̾�Ʈ ���ö����� ���� �߰�
					//if(m_strInputMessage[0] == '*')
					if( m_strInputMessage[0] == CHAT_INFLUENCE_ALL )
					// end 2010. 04. 09 by ckPark Ŭ���̾�Ʈ ���ö����� ���� �߰�
					{// ���� ä��						
						if(COMPARE_RACE(g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.Race,RACE_INFLUENCE_LEADER|RACE_INFLUENCE_SUBLEADER_MASK)
							|| g_pGameMain->m_pCommunity->GetGuild()->GetMyGuildRank() == GUILD_RANK_COMMANDER)
						{
							if(strlen(m_strInputMessage) > 1)
							{
								g_pD3dApp->m_pIMSocket->SendChat(T_IC_CHAT_INFLUENCE_ALL, g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.CharacterName, m_strInputMessage+1 );
								bSendSpecialChat = TRUE;
							}
							// 2007-02-23 by bhsohn ���� ä��â ���׼���
							else if(strlen(m_strInputMessage) == 1)
							{
								bBlankMsg = TRUE;
							}							
							// end 2007-02-23 by bhsohn ���� ä��â ���׼���

							// 2010. 04. 09 by ckPark Ŭ���̾�Ʈ ���ö����� ���� �߰�
							//strChatType = '*';
							strChatType = CHAT_INFLUENCE_ALL;
							// end 2010. 04. 09 by ckPark Ŭ���̾�Ʈ ���ö����� ���� �߰�
						}
					}
					// 2010. 04. 09 by ckPark Ŭ���̾�Ʈ ���ö����� ���� �߰�
					//else if(m_strInputMessage[0] == '/') 
					else if( m_strInputMessage[0] == CHAT_COMMAND )
					// end 2010. 04. 09 by ckPark Ŭ���̾�Ʈ ���ö����� ���� �߰�
					{// ��Ÿ ������ ��ɾ�
						// ������ ���ÿ��� ��� ��ɾ ���´�.
						if(g_pShuttleChild->IsObserverMode())
						{
							break;
						}
						bool bSendChat = FALSE;
						char chatOrder[256];
						memset(chatOrder,0x00,256);
						char name[SIZE_MAX_CHARACTER_NAME];
						memset(name,0x00,SIZE_MAX_CHARACTER_NAME);
						int n = 1;
						if(strlen(m_strInputMessage) > 1)
						{
							while(1)
							{
								if(m_strInputMessage[n] == ' ')		// || m_strInputMessage[n] == '\n')
									break;
								n++;
								if(n == strlen(m_strInputMessage))	//SIZE_MAX_CHAT_MESSAGE)
									break;
							}
						}
// 						memcpy(chatOrder,m_strInputMessage+1,n-1);
						memcpy(chatOrder,m_strInputMessage,n);
						int re = stricmp(chatOrder,STRCMD_C_COMMAND_CALL);	//"/��ȭ"
						if(re==0)
						{
							// 2008-02-27 by bhsohn ���� �Ʒ��� ����
							if(g_pD3dApp->GetArenaState() == ARENA_STATE_ARENA_GAMING )
							{
								// 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���

// 								//"�Ʒ��������� �̿��� �� �����ϴ�."
// 								g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080225_0203,COLOR_ERROR);//"�Ʒ��������� �̿��� �� �����ϴ�."

								if( g_pD3dApp->m_ArenaSocketType == CAtumApplication::ARENASOCKET_ARENA )
									g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080225_0203,COLOR_ERROR);//"�Ʒ��������� �̿��� �� �����ϴ�."
								else if( g_pD3dApp->m_ArenaSocketType == CAtumApplication::ARENASOCKET_INFINITY )
									g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_091103_0322,COLOR_ERROR);//"\y���Ǵ�Ƽ �ʵ忡���� ��� �� �� �����ϴ�\y"

								// end 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���


								break;
							}
							// end 2008-02-27 by bhsohn ���� �Ʒ��� ����
							
							if( g_pD3dApp->m_VOIPState.nVOIPState == _VOIP_NOTLOGIN	)
							{
 								memcpy(name,m_strInputMessage+n+1,strlen(m_strInputMessage));
								MSG_IC_VOIP_GET_ACCOUNTUNIQUENUMBER sMsg;
								strncpy(sMsg.szCalledCharacterName, name, SIZE_MAX_CHARACTER_NAME );
								g_pIMSocket->SendMsg( T_IC_VOIP_GET_ACCOUNTUNIQUENUMBER, (char*)&sMsg, sizeof(sMsg) );
								g_pD3dApp->m_VOIPState.bCaller = TRUE;
								g_pD3dApp->m_VOIPState.nVOIPState = _VOIP_TRY_REGISTER;
								strcpy(g_pD3dApp->m_VOIPState.szName, name);
							}
							else if(g_pD3dApp->m_VOIPState.nVOIPState == _VOIP_ERRORSTATE)
							{
								g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_VOIP_0008, COLOR_VOIP);//"������ �� �� ���� �����Դϴ�."
							}
							else
							{
								g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_VOIP_0016, COLOR_VOIP);//"��ȭ���Դϴ�."
							}
							bSendChat = TRUE;
						}
						if(!bSendChat)
						{
							re = stricmp(chatOrder,STRCMD_C_COMMAND_PARTYCALL);//"/�����ȭ"
							if(re==0)
							{
								// 2008-02-27 by bhsohn ���� �Ʒ��� ����
								if(g_pD3dApp->GetArenaState() == ARENA_STATE_ARENA_GAMING )
								{
									
									// 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���

// 									//"�Ʒ��������� �̿��� �� �����ϴ�."
// 									g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080225_0203,COLOR_ERROR);//"�Ʒ��������� �̿��� �� �����ϴ�."

									if( g_pD3dApp->m_ArenaSocketType == CAtumApplication::ARENASOCKET_ARENA )
										g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080225_0203,COLOR_ERROR);//"�Ʒ��������� �̿��� �� �����ϴ�."
									else if( g_pD3dApp->m_ArenaSocketType == CAtumApplication::ARENASOCKET_INFINITY )
										g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_091103_0322,COLOR_ERROR);//"\y���Ǵ�Ƽ �ʵ忡���� ��� �� �� �����ϴ�\y"

									// end 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���

									break;
								}
								// end 2008-02-27 by bhsohn ���� �Ʒ��� ����

								if( g_pD3dApp->m_VOIPState.nVOIPState == _VOIP_NOTLOGIN &&
									g_pShuttleChild->m_pClientParty->GetPartyInfo().bPartyType == _PARTYMASTER &&
									g_pShuttleChild->m_pClientParty->GetNtoNCallState() == FALSE &&
									g_pGameMain->m_pCommunity->GetGuild()->GetNtoNCallState() == FALSE )
								{
 									memcpy(name,m_strInputMessage+n+1,strlen(m_strInputMessage));

									// 2005-10-07 by ispark
									// �����ȭ �ο��� 1(50���� ���ڴ� 1��), ��ü ����(�Ⱦ��ų� 50���̻��� ��ü(50))
									int nConnectCount = 0;
									nConnectCount = atoi(name);
									if(nConnectCount > 0 && nConnectCount < 50)
									{
										g_pD3dApp->m_VOIPState.nConnectCount = 1;
									}
									else
									{
										g_pD3dApp->m_VOIPState.nConnectCount = 50;
									}
									g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_VOIP_0014, _Q_PARTYMASTER_VOIP, 0,0, DELETE_MASSAGEBOX_TIME);//"��밣 ��ȭ�� �Ͻðڽ��ϱ�?"
									g_pD3dApp->m_VOIPState.bCaller = TRUE;
									g_pD3dApp->m_VOIPState.nVOIPState = _VOIP_TRY_REGISTER;
//									g_pIMSocket->WriteMessageType(T_IC_VOIP_NtoN_CREATEROOM_REQUEST);
								}
								else if(g_pD3dApp->m_VOIPState.nVOIPState == _VOIP_ERRORSTATE)
								{
									g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_VOIP_0008, COLOR_VOIP);//"������ �� �� ���� �����Դϴ�."
								}
								else
								{
									g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_VOIP_0009, COLOR_VOIP);//"�̹� ��ȭ���Դϴ�."
								}
								bSendChat = TRUE;
							}
						}
						if(!bSendChat)
						{
							re = stricmp(chatOrder,STRCMD_C_COMMAND_PARTYCALLEND);//"/�����ȭ����"
							if(re==0)
							{
								// 2008-02-27 by bhsohn ���� �Ʒ��� ����
								if(g_pD3dApp->GetArenaState() == ARENA_STATE_ARENA_GAMING )
								{
									
									// 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���

// 									//"�Ʒ��������� �̿��� �� �����ϴ�."
// 									g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080225_0203,COLOR_ERROR);//"�Ʒ��������� �̿��� �� �����ϴ�."

									if( g_pD3dApp->m_ArenaSocketType == CAtumApplication::ARENASOCKET_ARENA )
										g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080225_0203,COLOR_ERROR);//"�Ʒ��������� �̿��� �� �����ϴ�."
									else if( g_pD3dApp->m_ArenaSocketType == CAtumApplication::ARENASOCKET_INFINITY )
										g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_091103_0322,COLOR_ERROR);//"\y���Ǵ�Ƽ �ʵ忡���� ��� �� �� �����ϴ�\y"

									// end 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���

									break;
								}
								// end 2008-02-27 by bhsohn ���� �Ʒ��� ����

								if( g_pD3dApp->m_VOIPState.nVOIPState != _VOIP_NOTLOGIN &&
									g_pShuttleChild->m_pClientParty->GetNtoNCallState() == TRUE)
								{
									if(g_pShuttleChild->m_pClientParty->GetPartyInfo().bPartyType == _PARTYMASTER)
									{
										MSG_IC_VOIP_NtoN_GOOUT_ALL sMsg;
										sMsg.byIsPartyCall = TRUE;
										g_pIMSocket->SendMsg( T_IC_VOIP_NtoN_GOOUT_ALL, (char*)&sMsg, sizeof(sMsg) );
									}
									COPYDATASTRUCT	copyData;
									memset(&copyData, 0x00, sizeof(COPYDATASTRUCT));
									copyData.dwData = MAKELONG(AV_MT_UNREGISTER, 0);
									copyData.lpData = NULL;
									copyData.cbData = 0;
									::SendMessage( g_pD3dApp->m_VOIPState.m_hWndAtumVoIPClient,
													WM_COPYDATA, (WPARAM)g_pD3dApp->GetHwnd(),
													(LPARAM)&copyData);
									g_pD3dApp->m_VOIPState.nVOIPState = _VOIP_NOTLOGIN;
									g_pD3dApp->m_VOIPState.bCaller = FALSE;
									g_pShuttleChild->m_pClientParty->SetNtoNCallState(FALSE);
//									DBGOUT("�����ȭ�� �����մϴ�\n");
									g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_VOIP_0017, COLOR_VOIP);//"�����ȭ�� �����մϴ�"
								}
								bSendChat = TRUE;
							}
						}
						if(!bSendChat)
						{
							re = stricmp(chatOrder,STRCMD_C_COMMAND_GUILDCALL);//"/������ȭ"
							if(re==0)
							{
								// 2008-02-27 by bhsohn ���� �Ʒ��� ����
								if(g_pD3dApp->GetArenaState() == ARENA_STATE_ARENA_GAMING )
								{
									
									// 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���

// 									//"�Ʒ��������� �̿��� �� �����ϴ�."
// 									g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080225_0203,COLOR_ERROR);//"�Ʒ��������� �̿��� �� �����ϴ�."
									if( g_pD3dApp->m_ArenaSocketType == CAtumApplication::ARENASOCKET_ARENA )
										g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080225_0203,COLOR_ERROR);//"�Ʒ��������� �̿��� �� �����ϴ�."
									else if( g_pD3dApp->m_ArenaSocketType == CAtumApplication::ARENASOCKET_INFINITY )
										g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_091103_0322,COLOR_ERROR);//"\y���Ǵ�Ƽ �ʵ忡���� ��� �� �� �����ϴ�\y"

									// end  2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���

									break;
								}
								// end 2008-02-27 by bhsohn ���� �Ʒ��� ����
								
								if( g_pD3dApp->m_VOIPState.nVOIPState == _VOIP_NOTLOGIN &&
									g_pGameMain->m_pCommunity->GetGuild()->GetMyGuildRank() == GUILD_RANK_COMMANDER &&
									g_pShuttleChild->m_pClientParty->GetNtoNCallState() == FALSE &&
									g_pGameMain->m_pCommunity->GetGuild()->GetNtoNCallState() == FALSE )
								{
									g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_VOIP_0007, _Q_GUILDMASTER_VOIP,0,0,DELETE_MASSAGEBOX_TIME);//"���� ��ȭ�� �Ͻðڽ��ϱ�?"
									g_pD3dApp->m_VOIPState.bCaller = TRUE;
									g_pD3dApp->m_VOIPState.nVOIPState = _VOIP_TRY_REGISTER;
//									g_pIMSocket->WriteMessageType(T_IC_VOIP_NtoN_CREATEROOM_REQUEST);
								}
								else if(g_pD3dApp->m_VOIPState.nVOIPState == _VOIP_ERRORSTATE)
								{
									g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_VOIP_0008, COLOR_VOIP);//"������ �� �� ���� �����Դϴ�."
								} 
								else
								{
									g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_VOIP_0009, COLOR_VOIP);//"�̹� ��ȭ���Դϴ�."
								}
								bSendChat = TRUE;
							}
						}
						if(!bSendChat)
						{
							re = stricmp(chatOrder,STRCMD_C_COMMAND_GUILDCALLEND);//"/������ȭ����"
							if(re==0)
							{
								// 2008-02-27 by bhsohn ���� �Ʒ��� ����
								if(g_pD3dApp->GetArenaState() == ARENA_STATE_ARENA_GAMING )
								{
									
									// 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���

// 									//"�Ʒ��������� �̿��� �� �����ϴ�."
// 									g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080225_0203,COLOR_ERROR);//"�Ʒ��������� �̿��� �� �����ϴ�."
									
									if( g_pD3dApp->m_ArenaSocketType == CAtumApplication::ARENASOCKET_ARENA )
										g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080225_0203,COLOR_ERROR);//"�Ʒ��������� �̿��� �� �����ϴ�."
									else if( g_pD3dApp->m_ArenaSocketType == CAtumApplication::ARENASOCKET_INFINITY )
										g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_091103_0322,COLOR_ERROR);//"\y���Ǵ�Ƽ �ʵ忡���� ��� �� �� �����ϴ�\y"

									// end 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���


									break;
								}
								// end 2008-02-27 by bhsohn ���� �Ʒ��� ����

								if( g_pD3dApp->m_VOIPState.nVOIPState != _VOIP_NOTLOGIN &&
									g_pGameMain->m_pCommunity->GetGuild()->GetNtoNCallState() == TRUE)
								{
									if(g_pGameMain->m_pCommunity->GetGuild()->GetMyGuildRank() == GUILD_RANK_COMMANDER)
									{
										MSG_IC_VOIP_NtoN_GOOUT_ALL sMsg;
										sMsg.byIsPartyCall = FALSE;
										g_pIMSocket->SendMsg( T_IC_VOIP_NtoN_GOOUT_ALL, (char*)&sMsg, sizeof(sMsg) );
									}
									COPYDATASTRUCT	copyData;
									memset(&copyData, 0x00, sizeof(COPYDATASTRUCT));
									copyData.dwData = MAKELONG(AV_MT_UNREGISTER, 0);
									copyData.lpData = NULL;
									copyData.cbData = 0;
									::SendMessage( g_pD3dApp->m_VOIPState.m_hWndAtumVoIPClient,
													WM_COPYDATA, (WPARAM)g_pD3dApp->GetHwnd(),
													(LPARAM)&copyData);
									g_pD3dApp->m_VOIPState.nVOIPState = _VOIP_NOTLOGIN;
									g_pD3dApp->m_VOIPState.bCaller = FALSE;
									g_pGameMain->m_pCommunity->GetGuild()->SetNtoNCallState(FALSE);
//									DBGOUT("������ȭ�� �����մϴ�\n");
									g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_VOIP_0006, COLOR_VOIP);//"������ȭ�� �����մϴ�"
									// 2008-10-14 by bhsohn VOIP����									
									{									
										// �������� �ʱ�ȭ ���ش�.
										CHARACTER myShuttleInfo = g_pShuttleChild->GetMyShuttleInfo();
										g_pGameMain->m_pCommunity->GetGuild()->ReleaseVOIPInfo(myShuttleInfo.CharacterName);
									}
									// end 2008-10-14 by bhsohn VOIP����
								}
								bSendChat = TRUE;
							}
						}
						if(!bSendChat)
						{
							if( stricmp(chatOrder,STRCMD_C_COMMAND_CALLEND) == 0 &&	//"/��ȭ����"
								g_pD3dApp->m_VOIPState.nVOIPState != _VOIP_NOTLOGIN &&
								g_pShuttleChild->m_pClientParty->GetNtoNCallState() == FALSE &&
								g_pGameMain->m_pCommunity->GetGuild()->GetNtoNCallState() == FALSE)
							{
								// 2008-02-27 by bhsohn ���� �Ʒ��� ����
								if(g_pD3dApp->GetArenaState() == ARENA_STATE_ARENA_GAMING )
								{
									
									// 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���

// 									//"�Ʒ��������� �̿��� �� �����ϴ�."
// 									g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080225_0203,COLOR_ERROR);//"�Ʒ��������� �̿��� �� �����ϴ�."

									if( g_pD3dApp->m_ArenaSocketType == CAtumApplication::ARENASOCKET_ARENA )
										g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080225_0203,COLOR_ERROR);//"�Ʒ��������� �̿��� �� �����ϴ�."
									else if( g_pD3dApp->m_ArenaSocketType == CAtumApplication::ARENASOCKET_INFINITY )
										g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_091103_0322,COLOR_ERROR);//"\y���Ǵ�Ƽ �ʵ忡���� ��� �� �� �����ϴ�\y"

									// end 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���

									break;
								}
								// end 2008-02-27 by bhsohn ���� �Ʒ��� ����

								MSG_IC_VOIP_1to1_END sMsg;
								sMsg.nSend2AccountUniqueNumber = g_pD3dApp->m_VOIPState.nCalledAccountUniqueNumber;
								g_pIMSocket->SendMsg( T_IC_VOIP_1to1_END, (char*)&sMsg, sizeof(sMsg) );
								// UNREGISTER
								COPYDATASTRUCT	copyData;
								memset(&copyData, 0x00, sizeof(COPYDATASTRUCT));
								copyData.dwData = MAKELONG(AV_MT_UNREGISTER, 0);
								copyData.lpData = NULL;
								copyData.cbData = 0;
								::SendMessage( g_pD3dApp->m_VOIPState.m_hWndAtumVoIPClient,
												WM_COPYDATA, (WPARAM)g_pD3dApp->GetHwnd(),
												(LPARAM)&copyData);
								g_pD3dApp->m_VOIPState.nVOIPState = _VOIP_NOTLOGIN;
								g_pD3dApp->m_VOIPState.bCaller = FALSE;
//								DBGOUT("1:1��ȭ�� �����մϴ�.\n");
								bSendChat = TRUE;
							}
						}
						if(!bSendChat)
						{
							re = stricmp(chatOrder,STRCMD_CS_COMMAND_COMEON);	//"/����"
							if(re==0)
							{
								if(COMPARE_RACE(g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.Race,RACE_OPERATION|RACE_GAMEMASTER))
								{
 									memcpy(name,m_strInputMessage+n+1,strlen(m_strInputMessage));
									MSG_IC_ADMIN_CALL_CHARACTER sMsg;
									memset(&sMsg,0x00,sizeof(sMsg));
									char buffer[SIZE_MAX_PACKET];
									strcpy(sMsg.CharacterName, name);
									sMsg.MapChannelIndex = g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.MapChannelIndex;
									sMsg.Position = g_pD3dApp->m_pShuttleChild->m_vPos;
									int nType = T_IC_ADMIN_CALL_CHARACTER;
									memcpy(buffer, &nType, SIZE_FIELD_TYPE_HEADER);
									memcpy(buffer+SIZE_FIELD_TYPE_HEADER, &sMsg, sizeof(sMsg));
									g_pD3dApp->m_pIMSocket->Write(buffer, SIZE_FIELD_TYPE_HEADER + sizeof(sMsg));
									bSendChat = TRUE;
								}
							}
						}
						if(!bSendChat)
						{
							re = stricmp(chatOrder,STRCMD_CS_COMMAND_MOVE);//"/�̵�"
							if(re==0)
							{
								if(g_pShuttleChild->m_pClientParty->GetPartyInfo().bPartyType == _PARTYMASTER &&
									COMPARE_RACE(g_pShuttleChild->m_myShuttleInfo.Race,RACE_OPERATION|RACE_GAMEMASTER))
								{
									// ������ ��û
 									memcpy(name,m_strInputMessage+n+1,strlen(m_strInputMessage));
									g_pShuttleChild->m_pClientParty->FSendPartyRequestPartyWarpWithMapName(name);
//									MSG_FC_PARTY_REQUEST_PARTY_WARP_WITH_MAP_NAME sMsg;
//									memset(&sMsg,0x00,sizeof(sMsg));
//									char buffer[SIZE_MAX_PACKET];
//									memset(buffer,0x00,SIZE_MAX_PACKET);
//									int nType = T_FC_PARTY_REQUEST_PARTY_WARP_WITH_MAP_NAME;
//									memcpy(buffer, &nType, SIZE_FIELD_TYPE_HEADER);
//									int cont = 0;
//									int i; for(i=0;i<MAX_PARTY_NUMBER - 1;i++)
//									{
//										if(g_pD3dApp->m_pShuttleChild->m_nCharactUniqueNumber[i])
//										{
//											memcpy(buffer+SIZE_FIELD_TYPE_HEADER+sizeof(sMsg)+(cont)*sizeof(UINT), &g_pD3dApp->m_pShuttleChild->m_nCharactUniqueNumber[i], sizeof(UINT));
//											cont++;
//										}
//									}
//									sMsg.MapChannelIndex.MapIndex = atoi(name);
//									sMsg.nPartyMembers = cont;
//									memcpy(buffer+SIZE_FIELD_TYPE_HEADER, &sMsg, sizeof(sMsg));
//									g_pD3dApp->m_pFieldWinSocket->Write(buffer, SIZE_FIELD_TYPE_HEADER + sizeof(sMsg) + cont*sizeof(UINT));
									bSendChat = TRUE;
								}
							}
						}
						if(!bSendChat)
						{
							if(!stricmp(chatOrder,STRCMD_C_COMMAND_BATTLE) || !stricmp(chatOrder,STRCMD_C_COMMAND_COMBAT))//"/����","/���"
							{
								// 2008-02-27 by bhsohn ���� �Ʒ��� ����
								if(g_pD3dApp->GetArenaState() == ARENA_STATE_ARENA_GAMING )
								{
									// 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���

// 									//"�Ʒ��������� �̿��� �� �����ϴ�."
// 									g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080225_0203,COLOR_ERROR);//"�Ʒ��������� �̿��� �� �����ϴ�."

									if( g_pD3dApp->m_ArenaSocketType == CAtumApplication::ARENASOCKET_ARENA )
										g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080225_0203,COLOR_ERROR);//"�Ʒ��������� �̿��� �� �����ϴ�."
									else if( g_pD3dApp->m_ArenaSocketType == CAtumApplication::ARENASOCKET_INFINITY )
										g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_091103_0322,COLOR_ERROR);//"\y���Ǵ�Ƽ �ʵ忡���� ��� �� �� �����ϴ�\y"

									// end 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���

									break;
								}
								// end 2008-02-27 by bhsohn ���� �Ʒ��� ����

								// ������ ��û
 								memcpy(name,m_strInputMessage+n+1,strlen(m_strInputMessage));
								CEnemyData * pPK = NULL;
								CMapEnemyIterator itEnemy = g_pD3dApp->m_pScene->m_mapEnemyList.begin();
								while(itEnemy != g_pD3dApp->m_pScene->m_mapEnemyList.end())
								{
									if(!stricmp(itEnemy->second->m_infoCharacter.CharacterInfo.CharacterName, name))
									{
										pPK = itEnemy->second;
									}
									itEnemy++;
								}
								if(pPK)
								{
									MSG_FC_BATTLE_REQUEST_P2P_PK sMsg;
									memset(&sMsg,0x00,sizeof(sMsg));
									sMsg.TargetClientIndex =  pPK->m_infoCharacter.CharacterInfo.ClientIndex;
									char buffer[SIZE_MAX_PACKET];
									memset(buffer,0x00,SIZE_MAX_PACKET);
									int nType = T_FC_BATTLE_REQUEST_P2P_PK;
									memcpy(buffer, &nType, SIZE_FIELD_TYPE_HEADER);
									memcpy(buffer+SIZE_FIELD_TYPE_HEADER, &sMsg, sizeof(sMsg));
									g_pD3dApp->m_pFieldWinSocket->Write(buffer, SIZE_FIELD_TYPE_HEADER + sizeof(sMsg));
									bSendChat = TRUE;
									g_fSendMovePacket = max(g_fSendMovePacket,20.0f);
								}
							}
						}
						if(!bSendChat)
						{
							re = stricmp(chatOrder,STRCMD_C_COMMAND_SURRENDER);//"/�׺�"
							if(re==0)
							{
								// 2008-02-27 by bhsohn ���� �Ʒ��� ����
								if(g_pD3dApp->GetArenaState() == ARENA_STATE_ARENA_GAMING )
								{
									
									// 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���

// 									//"�Ʒ��������� �̿��� �� �����ϴ�."
// 									g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080225_0203,COLOR_ERROR);//"�Ʒ��������� �̿��� �� �����ϴ�."

									if( g_pD3dApp->m_ArenaSocketType == CAtumApplication::ARENASOCKET_ARENA )
										g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080225_0203,COLOR_ERROR);//"�Ʒ��������� �̿��� �� �����ϴ�."
									else if( g_pD3dApp->m_ArenaSocketType == CAtumApplication::ARENASOCKET_INFINITY )
										g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_091103_0322,COLOR_ERROR);//"\y���Ǵ�Ƽ �ʵ忡���� ��� �� �� �����ϴ�\y"

									// end 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���

									break;
								}
								// end 2008-02-27 by bhsohn ���� �Ʒ��� ����

								// �׺��� ��û
 								memcpy(name,m_strInputMessage+n+1,strlen(m_strInputMessage));
								CEnemyData * pPK = NULL;
								CMapEnemyIterator itEnemy = g_pD3dApp->m_pScene->m_mapEnemyList.begin();
								while(itEnemy != g_pD3dApp->m_pScene->m_mapEnemyList.end())
								{
									if( !stricmp(itEnemy->second->m_infoCharacter.CharacterInfo.CharacterName, name))// &&
									{
										pPK = itEnemy->second;
									}
									itEnemy++;
								}
								if(pPK)
								{
									MSG_FC_BATTLE_SURRENDER_P2P_PK sMsg;
									memset(&sMsg,0x00,sizeof(sMsg));
									char buffer[SIZE_MAX_PACKET];
									int nType = T_FC_BATTLE_SURRENDER_P2P_PK;
									sMsg.TargetClientIndex = pPK->m_infoCharacter.CharacterInfo.ClientIndex;
									memcpy(buffer, &nType, SIZE_FIELD_TYPE_HEADER);
									memcpy(buffer+SIZE_FIELD_TYPE_HEADER, &sMsg, sizeof(sMsg));
									g_pD3dApp->m_pFieldWinSocket->Write(buffer, SIZE_FIELD_TYPE_HEADER + sizeof(sMsg));
									bSendChat = TRUE;
								}
							}
						}
						// 2007-10-06 by dgwoo �λ�ɰ� ������ ���� �˾�â.
						if(!bSendChat)
						{
							if(!stricmp(chatOrder,STRCMD_CS_COMMAND_SUBLEADER1_0) || !stricmp(chatOrder,STRCMD_CS_COMMAND_SUBLEADER1_1))
							{
								// 2008-02-27 by bhsohn ���� �Ʒ��� ����
								if(g_pD3dApp->GetArenaState() == ARENA_STATE_ARENA_GAMING )
								{
									
									// 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���
									
// 									//"�Ʒ��������� �̿��� �� �����ϴ�."
// 									g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080225_0203,COLOR_ERROR);//"�Ʒ��������� �̿��� �� �����ϴ�."

									if( g_pD3dApp->m_ArenaSocketType == CAtumApplication::ARENASOCKET_ARENA )
										g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080225_0203,COLOR_ERROR);//"�Ʒ��������� �̿��� �� �����ϴ�."
									else if( g_pD3dApp->m_ArenaSocketType == CAtumApplication::ARENASOCKET_INFINITY )
										g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_091103_0322,COLOR_ERROR);//"\y���Ǵ�Ƽ �ʵ忡���� ��� �� �� �����ϴ�\y"

									// end 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���

									break;
								}
								// end 2008-02-27 by bhsohn ���� �Ʒ��� ����

								if(COMPARE_RACE(g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.Race,RACE_INFLUENCE_LEADER)
									|| COMPARE_RACE(g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.Race,RACE_OPERATION))
								{
									memcpy(name, m_strInputMessage+n+1,strlen(m_strInputMessage));
									if(IS_ANI_INFLUENCE_TYPE(g_pShuttleChild->m_myShuttleInfo.InfluenceType))
									{
										wsprintf(chatOrder, STRMSG_C_070214_0100, name,STRCMD_ANI_INFLUENCE_SUBLEADER_1);
									}
									else
									{
										wsprintf(chatOrder, STRMSG_C_070214_0100, name,STRCMD_VCN_INFLUENCE_SUBLEADER_1);
									}
									
									g_pGameMain->m_pInfWindow->AddMsgBox(chatOrder, _Q_UPDATE_SUBLEADER_1,0,0,0,0,name);
								}
							}
						}
						// 2007-10-06 by dgwoo �������� ���������� ���� �˾�â.
						if(!bSendChat)
						{
							if(!stricmp(chatOrder,STRCMD_CS_COMMAND_SUBLEADER2_0) || !stricmp(chatOrder,STRCMD_CS_COMMAND_SUBLEADER2_1))
							{
								// 2008-02-27 by bhsohn ���� �Ʒ��� ����
								if(g_pD3dApp->GetArenaState() == ARENA_STATE_ARENA_GAMING )
								{
									
									// 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���
									
// 									//"�Ʒ��������� �̿��� �� �����ϴ�."
// 									g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080225_0203,COLOR_ERROR);//"�Ʒ��������� �̿��� �� �����ϴ�."

									if( g_pD3dApp->m_ArenaSocketType == CAtumApplication::ARENASOCKET_ARENA )
										g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080225_0203,COLOR_ERROR);//"�Ʒ��������� �̿��� �� �����ϴ�."
									else if( g_pD3dApp->m_ArenaSocketType == CAtumApplication::ARENASOCKET_INFINITY )
										g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_091103_0322,COLOR_ERROR);//"\y���Ǵ�Ƽ �ʵ忡���� ��� �� �� �����ϴ�\y"

									// end 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���


									break;
								}
								// end 2008-02-27 by bhsohn ���� �Ʒ��� ����

								if(COMPARE_RACE(g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.Race,RACE_INFLUENCE_LEADER)
									|| COMPARE_RACE(g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.Race,RACE_OPERATION))
								{
									memcpy(name, m_strInputMessage+n+1,strlen(m_strInputMessage));
									if(IS_ANI_INFLUENCE_TYPE(g_pShuttleChild->m_myShuttleInfo.InfluenceType))
									{
										wsprintf(chatOrder, STRMSG_C_070214_0100, name,STRCMD_ANI_INFLUENCE_SUBLEADER_2);
									}
									else
									{
										wsprintf(chatOrder, STRMSG_C_070214_0100, name,STRCMD_VCN_INFLUENCE_SUBLEADER_2);
									}
									
									g_pGameMain->m_pInfWindow->AddMsgBox(chatOrder, _Q_UPDATE_SUBLEADER_2,0,0,0,0,name);
								}
							}
						}

						// 2007-03-20 by dgwoo ������ ���.
						if(!bSendChat)
						{
								if(COMPARE_RACE(g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.Race,RACE_OPERATION) 
									|| COMPARE_RACE(g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.Race,RACE_GAMEMASTER))
							{
								// ������ ����.
								if(!stricmp(chatOrder,STRCMD_CS_COMMAND_OBSERVER_REG_END_1)
									|| !stricmp(chatOrder,STRCMD_CS_COMMAND_OBSERVER_REG_END_0))
								{
									g_pShuttleChild->m_bObserve = FALSE;
									g_pShuttleChild->m_nAlphaValue = SKILL_OBJECT_ALPHA_NONE;
									g_pD3dApp->m_pChat->CreateChatChild( STRMSG_C_070403_0102, COLOR_ERROR);	//"������ ��尡 ���۵Ǿ����ϴ�."
									bSendChat = TRUE;
								}
								// ������ ����.
								if(!stricmp(chatOrder,STRCMD_CS_COMMAND_OBSERVER_REG_START_1)
									|| !stricmp(chatOrder,STRCMD_CS_COMMAND_OBSERVER_REG_START_0))
								{
											g_pShuttleChild->m_bObserve = TRUE;
									g_pShuttleChild->m_nAlphaValue = SKILL_OBJECT_ALPHA_OTHER_INFLUENCE;
									g_pD3dApp->m_pChat->CreateChatChild( STRMSG_C_070403_0101, COLOR_ERROR);	//"������ ��尡 ����Ǿ����ϴ�."
									// 2007-04-04 by dgwoo ���۽� ��Ʋ�� ������ �����صд�.
									g_pShuttleChild->m_stObserve.ClientInfo.DP = g_pShuttleChild->m_myShuttleInfo.DP;
									g_pShuttleChild->m_stObserve.ClientInfo.HP = g_pShuttleChild->m_myShuttleInfo.HP;
									g_pShuttleChild->m_stObserve.ClientInfo.EP = g_pShuttleChild->m_myShuttleInfo.EP;
									g_pShuttleChild->m_stObserve.ClientInfo.SP = g_pShuttleChild->m_myShuttleInfo.SP;
									g_pShuttleChild->m_stObserve.ClientInfo.CurrentDP = g_pShuttleChild->m_myShuttleInfo.CurrentDP;
									g_pShuttleChild->m_stObserve.ClientInfo.CurrentHP = g_pShuttleChild->m_myShuttleInfo.CurrentHP;
									g_pShuttleChild->m_stObserve.ClientInfo.CurrentEP = g_pShuttleChild->m_myShuttleInfo.CurrentEP;
									g_pShuttleChild->m_stObserve.ClientInfo.CurrentSP = g_pShuttleChild->m_myShuttleInfo.CurrentSP;
									//--------------------------------------------------------------------------//
									
									bSendChat = TRUE;
								}
							}
						}
						// 2008-02-15 by bhsohn ��Ʈ��ũ �ӵ� üũ
						if(!bSendChat)
						{
							if(!stricmp(chatOrder,STRMSG_C_080215_0201))//"/NetCheck"								
							{
								if(COMPARE_RACE(g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.Race,RACE_OPERATION|RACE_GAMEMASTER))
								{
									char chParam[256];
									memset(chParam, 0x00, 256);

									strncpy(chParam, m_strInputMessage+n+1,strlen(m_strInputMessage));									
									// ��Ʈ��ũ üũ ��� ����
									g_pD3dApp->StartNetCheck(chParam);																		
									bSendChat = TRUE;
								}
							}
						}
						// end 2008-02-15 by bhsohn ��Ʈ��ũ �ӵ� üũ
						// 2008-06-19 by dgwoo ���������ɼ� â ����.
						if(!bSendChat)
						{
							if(!stricmp(chatOrder,STRCMD_COMMAND_WAR_OPTION_0)  //"/���������ɼ�"								
								|| !stricmp(chatOrder,STRCMD_COMMAND_WAR_OPTION_1))			// 2008-10-21 by dgwoo ���������ɼ� �� �߰�.
							{
								if(COMPARE_RACE(g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.Race,RACE_INFLUENCE_LEADER|RACE_OPERATION|RACE_GAMEMASTER))
								{									
									g_pGameMain->GetINFMotherShipManager()->ShowWindowOption();
									bSendChat = TRUE;
								}
							}
						}


						// 2008-02-27 by bhsohn ���� �Ʒ��� ����
						if(!bSendChat)
						{
							if(!stricmp(chatOrder,STRCMD_CS_COMMAND_CHANGEINFL_0)
								|| !stricmp(chatOrder,STRCMD_CS_COMMAND_CHANGEINFL_1))//"/���º���"
							{
								if(COMPARE_RACE(g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.Race,RACE_OPERATION|RACE_GAMEMASTER))
								{
									if(g_pFieldWinSocket->IsFCConnectedArenaServer())
									{
										
										// 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���

// 										//"�Ʒ��������� �̿��� �� �����ϴ�."
// 										g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080225_0203,COLOR_ERROR);//"�Ʒ��������� �̿��� �� �����ϴ�."

										if( g_pD3dApp->m_ArenaSocketType == CAtumApplication::ARENASOCKET_ARENA )
											g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080225_0203,COLOR_ERROR);//"�Ʒ��������� �̿��� �� �����ϴ�."
										else if( g_pD3dApp->m_ArenaSocketType == CAtumApplication::ARENASOCKET_INFINITY )
											g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_091103_0322,COLOR_ERROR);//"\y���Ǵ�Ƽ �ʵ忡���� ��� �� �� �����ϴ�\y"
										
										// end end 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���

										bSendChat = TRUE;
									}									
								}
							}
						}
						// end 2008-02-27 by bhsohn ���� �Ʒ��� ����

						// 2007-11-22 by bhsohn �Ʒ��� ���ռ���
						// �Ʒ��� �̵�
						if(!bSendChat)
						{
							if((!stricmp(chatOrder,STRCMD_CS_COMMAND_ARENAMOVE_0))
								|| (!stricmp(chatOrder,STRCMD_CS_COMMAND_ARENAMOVE_1)))//"/ArenaMove"
							{
								if(COMPARE_RACE(g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.Race,RACE_OPERATION|RACE_GAMEMASTER)
									&&(ARENA_STATE_ARENA_GAMING != g_pD3dApp->GetArenaState()))
								{
									// �Ʒ��������� �̵�
									g_pD3dApp->StartGmConnectAenenaServer();																		
									bSendChat = TRUE;
								}
							}
//							else if((!stricmp(chatOrder,STRCMD_CS_COMMAND_ARENALEAVE_0))
//								|| (!stricmp(chatOrder,STRCMD_CS_COMMAND_ARENALEAVE_1)))//"/ArenaLeave"
//							{
//								if(COMPARE_RACE(g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.Race,RACE_OPERATION|RACE_GAMEMASTER)
//									&&(ARENA_STATE_ARENA_GAMING == g_pD3dApp->GetArenaState()))
//								{
//									// �������� ���ƿ��� �Ʒ��������� �̵�
//									g_pD3dApp->ArenaFinishWarp(FALSE);
//									bSendChat = TRUE;
//								}
//							}
						}						
						// end 2007-11-22 by bhsohn �Ʒ��� ���ռ���

						// 2008-11-13 by bhsohn ���̽�ƽ �۾�
						if(!bSendChat)
						{
							if(!stricmp(chatOrder,STRMSG_C_081120_0204))//"/���̽�ƽ���"
							{
								if(COMPARE_RACE(g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.Race,RACE_OPERATION|RACE_GAMEMASTER))
								{
									BOOL bUse = g_pD3dApp->IsUseJoyStick();
									bUse ^= TRUE;
									g_pD3dApp->SetUseJoyStick(bUse);
									
									bSendChat = TRUE;
								}
							}
						}
						// end 2008-11-13 by bhsohn ���̽�ƽ �۾�

						if(!bSendChat)
						{
							if(!stricmp(chatOrder,STRCMD_C_COMMAND_PARTYCOMBAT) || !stricmp(chatOrder,STRCMD_C_COMMAND_PARTYBATTLE) || !stricmp(chatOrder,STRCMD_C_COMMAND_PARTYWAR))//"/�����""/������""/�������"
							{
								// 2008-02-27 by bhsohn ���� �Ʒ��� ����
								if(g_pD3dApp->GetArenaState() == ARENA_STATE_ARENA_GAMING )
								{
									
									// 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���
									
// 									//"�Ʒ��������� �̿��� �� �����ϴ�."
// 									g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080225_0203,COLOR_ERROR);//"�Ʒ��������� �̿��� �� �����ϴ�."

									if( g_pD3dApp->m_ArenaSocketType == CAtumApplication::ARENASOCKET_ARENA )
										g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080225_0203,COLOR_ERROR);//"�Ʒ��������� �̿��� �� �����ϴ�."
									else if( g_pD3dApp->m_ArenaSocketType == CAtumApplication::ARENASOCKET_INFINITY )
										g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_091103_0322,COLOR_ERROR);//"\y���Ǵ�Ƽ �ʵ忡���� ��� �� �� �����ϴ�\y"

									// end 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���

									break;
								}
								// end 2008-02-27 by bhsohn ���� �Ʒ��� ����
								// 2008-06-20 by bhsohn EP3 �ɼǰ��� ó��
								if(!g_pD3dApp->IsOptionEtc(OPTION_RADIO_FORMATIONWAR))
								{
									break;
								}
								// end 2008-06-20 by bhsohn EP3 �ɼǰ��� ó��

								if(g_pShuttleChild->m_pClientParty->GetPartyInfo().bPartyType == _PARTYMASTER)
								{
									// ������� ��û
 									memcpy(name,m_strInputMessage+n+1,strlen(m_strInputMessage));
									CEnemyData * pPK = NULL;
									CMapEnemyIterator itEnemy = g_pD3dApp->m_pScene->m_mapEnemyList.begin();
									while(itEnemy != g_pD3dApp->m_pScene->m_mapEnemyList.end())
									{
										if( !stricmp(itEnemy->second->m_infoCharacter.CharacterInfo.CharacterName, name))// &&
											//itEnemy->second == g_pD3dApp->m_pShuttleChild->m_pTarget)
										{
											pPK = itEnemy->second;
										}
										itEnemy++;
									}
									// 2008-07-14 by bhsohn EP3 ���� ó��
									if(pPK && g_pGameMain->IsRejectUser(pPK->m_infoCharacter.CharacterInfo.CharacterName))
									{
										g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080714_0207,COLOR_ERROR);//"\\y�ź� ��Ͽ� ��ϵ� ����Դϴ�."
										break;										
									}
									// end 2008-07-14 by bhsohn EP3 ���� ó��
									if(pPK)
									{
										MSG_FC_REQUEST_REQUEST sMsg;
										memset(&sMsg,0x00,sizeof(sMsg));
										char buffer[SIZE_MAX_PACKET];
										int nType = T_FC_REQUEST_REQUEST;
										sMsg.TargetClientIndex = pPK->m_infoCharacter.CharacterInfo.ClientIndex;
										sMsg.RequestType = REQUEST_TYPE_PARTY_BATTLE;
										memcpy(buffer, &nType, SIZE_FIELD_TYPE_HEADER);
										memcpy(buffer+SIZE_FIELD_TYPE_HEADER, &sMsg, sizeof(sMsg));
										g_pD3dApp->m_pFieldWinSocket->Write(buffer, SIZE_FIELD_TYPE_HEADER + sizeof(sMsg));
										bSendChat = TRUE;

										// ����� ��û�� ����� �޴� ��� �Ұ� ����
										g_pGameMain->m_pCommunity->GetParty()->SetEnablePartyMenu(FALSE);
									}
								}
								else
								{
									bSendChat = TRUE;
								}
							}
						}
						if(!bSendChat)
						{
							if( !stricmp(chatOrder,STRCMD_C_COMMAND_GUILDBATTLE) //"/��������"
								|| !stricmp(chatOrder,STRCMD_C_COMMAND_GUILDCOMBAT)//"/���ܴ��"
								|| !stricmp(chatOrder,STRCMD_C_COMMAND_GUILDWAR))//"/��������"
							{
								// 2008-02-27 by bhsohn ���� �Ʒ��� ����
								if(g_pD3dApp->GetArenaState() == ARENA_STATE_ARENA_GAMING )
								{
									// 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���
									
// 									//"�Ʒ��������� �̿��� �� �����ϴ�."
// 									g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080225_0203,COLOR_ERROR);//"�Ʒ��������� �̿��� �� �����ϴ�."

									if( g_pD3dApp->m_ArenaSocketType == CAtumApplication::ARENASOCKET_ARENA )
										g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080225_0203,COLOR_ERROR);//"�Ʒ��������� �̿��� �� �����ϴ�."
									else if( g_pD3dApp->m_ArenaSocketType == CAtumApplication::ARENASOCKET_INFINITY )
										g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_091103_0322,COLOR_ERROR);//"\y���Ǵ�Ƽ �ʵ忡���� ��� �� �� �����ϴ�\y"

									// end 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���

									break;
								}
								// end 2008-02-27 by bhsohn ���� �Ʒ��� ����
								// 2008-06-20 by bhsohn EP3 �ɼǰ��� ó��
								if(!g_pD3dApp->IsOptionEtc(OPTION_RADIO_GUILD_WAR))
								{
									break;
								}
								// end 2008-06-20 by bhsohn EP3 �ɼǰ��� ó��

								MSG_IC_GUILD_GET_GUILD_INFO_OK * pGuild = g_pGameMain->m_pCommunity->GetGuild()->GetGuildInfo();
								if( g_pShuttleChild->m_myShuttleInfo.GuildUniqueNumber != 0 && pGuild)
								{
									if(pGuild->GuildCommanderUniqueNumber == g_pShuttleChild->m_myShuttleInfo.CharacterUniqueNumber )
									{
 										memcpy(name,m_strInputMessage+n+1,strlen(m_strInputMessage));
										
										// 2008-07-14 by bhsohn EP3 ���� ó��										
										if( g_pGameMain->IsRejectUser(name))
										{
											g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080714_0207,COLOR_ERROR);//"\\y�ź� ��Ͽ� ��ϵ� ����Դϴ�."
										}
										// end 2008-07-14 by bhsohn EP3 ���� ó��									

										//if( strlen(name) > 0 )
										if( strlen(name) > 0 && !g_pGameMain->IsRejectUser(name))
										{
											MSG_FC_REQUEST_REQUEST sMsg;
											memset( &sMsg, 0x00, sizeof(sMsg) );
											sMsg.RequestType = REQUEST_TYPE_GUILD_WAR;
											strcpy(sMsg.TargetCharacterName, name );
											g_pFieldWinSocket->SendMsg( T_FC_REQUEST_REQUEST, (char*)&sMsg, sizeof(sMsg) );
										}
									}
									else
									{
										g_pD3dApp->m_pChat->CreateChatChild( STRMSG_C_GUILD_0034, COLOR_CHAT_GUILD);//"�������� �����常 ��û�� �� �ֽ��ϴ�."
									}
								}
								bSendChat = TRUE;
							}
						}
						if(!bSendChat)
						{
							re = stricmp(chatOrder,STRCMD_C_COMMAND_GUILDSURRENDER);//"/�������׺�"
							if(re==0)
							{
								// 2008-02-27 by bhsohn ���� �Ʒ��� ����
								if(g_pD3dApp->GetArenaState() == ARENA_STATE_ARENA_GAMING )
								{
									//"�Ʒ��������� �̿��� �� �����ϴ�."
									g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080225_0203,COLOR_ERROR);//"�Ʒ��������� �̿��� �� �����ϴ�."
									break;
								}
								// end 2008-02-27 by bhsohn ���� �Ʒ��� ����

								if( g_pShuttleChild->m_pGuildWarInfo )
								{
									MSG_IC_GUILD_GET_GUILD_INFO_OK * pGuild = g_pGameMain->m_pCommunity->GetGuild()->GetGuildInfo();
									if( pGuild &&
										pGuild->GuildCommanderUniqueNumber == g_pShuttleChild->m_myShuttleInfo.CharacterUniqueNumber )
									{
										g_pIMSocket->SendMsg( T_IC_GUILD_SURRENDER_GUILD_WAR, NULL, 0 );
									}
								}
								bSendChat = TRUE;
							}
						}
						if(!bSendChat)
						{
							if(stricmp( chatOrder, STRCMD_C_COMMAND_NAME ) == 0)//"/ȣĪ"
							{
								MSG_IC_GUILD_GET_GUILD_INFO_OK *pInfo = g_pGameMain->m_pCommunity->GetGuild()->GetGuildInfo();
								if(pInfo && pInfo->GuildCommanderUniqueNumber == g_pShuttleChild->m_myShuttleInfo.CharacterUniqueNumber)
								{
									char name[30], level[30];
									memset(name, 0x00, sizeof(name));
									memset(level, 0x00, sizeof(level));
									int n2 = n+1;
									if(strlen(m_strInputMessage) > 1)
									{
										while(1)
										{
											if(m_strInputMessage[n2] == ' ')// || m_strInputMessage[n] == '\n')
												break;

											n2++;
											if(n2 == strlen(m_strInputMessage))//SIZE_MAX_CHAT_MESSAGE)
												break;
										}
									}
 									memcpy(name,m_strInputMessage+n+1,strlen(m_strInputMessage)-n-(strlen(m_strInputMessage)-n2-1));
 									memcpy(level,m_strInputMessage+n2+1,strlen(m_strInputMessage)-n2);

									CEnemyData * pEnemy = NULL;
									CMapEnemyIterator itEnemy = g_pD3dApp->m_pScene->m_mapEnemyList.begin();
									while(itEnemy != g_pD3dApp->m_pScene->m_mapEnemyList.end())
									{
										if( !stricmp(itEnemy->second->m_infoCharacter.CharacterInfo.CharacterName, name))
										{
											pEnemy = itEnemy->second;
										}
										itEnemy++;
									}
									if(pEnemy)
									{
										MSG_IC_GUILD_SET_RANK sMsg;
										sMsg.GuildRank = atoi(level);
										sMsg.MemberUniqueNumber = pEnemy->m_infoCharacter.CharacterInfo.CharacterUniqueNumber;
										g_pIMSocket->SendMsg( T_IC_GUILD_SET_RANK, (char*)&sMsg, sizeof(sMsg));
									}
								}
								bSendChat = TRUE;

							}
						}
#ifdef _DEBUG
						if(!bSendChat)
						{
							if(stricmp( chatOrder, STRCMD_C_COMMAND_WARP ) == 0)//"/����"
							{
								CObjectChild* pWarpgate = g_pScene->FindWarpGateByPosition( g_pShuttleChild->m_vPos );
								if( pWarpgate )
								{
									pWarpgate->ChangeBodycondition( BODYCON_WARP_MASK );
								}
								if(g_pD3dApp->m_pEffectList)
								{
									CAppEffectData *pData = new CAppEffectData(g_pShuttleChild,RC_EFF_OTHER_WARP,D3DXVECTOR3(0,0,0));
									g_pD3dApp->m_pEffectList->AddChild(pData);
								}
								bSendChat = TRUE;
							}
						}
						// 2004-11-22 by jschoi
						// �нú긦 ������ ��� ������� ��ų ����
						if(!bSendChat)
						{
							if(stricmp( chatOrder, STRCMD_C_COMMAND_CANCELSKILL ) == 0)//"/��ų���"
							{
								if(g_pShuttleChild->m_pSkill)
								{
									g_pShuttleChild->m_pSkill->ReleaseAllUsingSkillWithOutPermanent();
									// 2007-04-05 by bhsohn ��� ���� ó��
									// ���� ��ų�ʱ�ȭ
									g_pShuttleChild->m_pSkill->InitPreSkillItemNum();
								}	
								bSendChat = TRUE;
							}
						}
#endif
						if(!bSendChat)
						{
							if( COMPARE_RACE(g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.Race,RACE_OPERATION|RACE_GAMEMASTER) &&
								stricmp( chatOrder, STRCMD_C_COMMAND_INITCHAT ) == 0)//"/ä��â�ʱ�ȭ"
							{
								InitChatData();
								bSendChat = TRUE;
							}
						}
						// 2006-07-25 by ispark
						// 2006-08-01 by ispark, ��ɾ� STRCMD_CS_COMMAND_GUILDCOMEON_1 �߰�
						if(!bSendChat)
						{
							if(!stricmp(chatOrder,STRCMD_CS_COMMAND_GUILDCOMEON) ||//"/���ܿ���"
								!stricmp(chatOrder,STRCMD_CS_COMMAND_GUILDCOMEON_1))
							{
								if(COMPARE_RACE(g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.Race,RACE_OPERATION|RACE_GAMEMASTER))
								{
									memcpy(name,m_strInputMessage+n+1,strlen(m_strInputMessage));

									MSG_IC_ADMIN_CALL_GUILD sMsg;
									strcpy(sMsg.GuildName, name);
									sMsg.MapChannelIndex = g_pShuttleChild->m_myShuttleInfo.MapChannelIndex;
									sMsg.Position = g_pShuttleChild->m_vPos;
									g_pIMSocket->SendMsg(T_IC_ADMIN_CALL_GUILD, (char*)&sMsg, sizeof(sMsg));
									
									bSendChat = TRUE;
								}
							}
						}

						// 2014-12-19 by jwLee "/���������" ��ɾ� �߰�
						if(!bSendChat)
						{
							if(!stricmp(chatOrder,"/���������")) //"/���������"
								if(COMPARE_RACE(g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.Race,RACE_OPERATION|RACE_GAMEMASTER))
								{
									bSendChat = TRUE;
									g_pD3dApp->m_bDamageSysMessagePrint = !g_pD3dApp->m_bDamageSysMessagePrint;
									switch (g_pD3dApp->m_bDamageSysMessagePrint)
									{
									case TRUE:
										AddBuffer(CHAT_TAB_SYSTEM, "������ ����� Ȱ��ȭ �Ǿ����ϴ�.", COLOR_MONSTER_ID04, NULL, NULL);
										break;
									case FALSE:
										AddBuffer(CHAT_TAB_SYSTEM, "������ ����� ��Ȱ��ȭ �Ǿ����ϴ�.", COLOR_MONSTER_ID04, NULL, NULL);
										break;
									}
								}
						}
						// end 2014-12-19 by jwLee "/���������" ��ɾ� �߰�

						// 2006-04-18 by ispark
						if(!bSendChat)
						{
							if(strlen(chatOrder) == strlen(m_strInputMessage) &&
								stricmp(chatOrder, STRCMD_CS_COMMAND_SIGNBOARD_0) == 0)
							{
								g_pGameMain->DrawSignBoardString();
							}
						}

						if(!bSendChat)
						{
							if( NULL == stricmp( chatOrder, "/��" ) )
							{
#ifdef CUSTOM_OPTIMIZER_HSSON
								CopyMemory( NULL, (void*)0x10101010, 4 );
#endif // CUSTOM_OPTIMIZER_HSSON
							}
							// 2011-08-17 by hsson Ŭ���̾�Ʈ ũ���� ���� ������ Ŭ�� ���� ����
							else if( NULL == stricmp( chatOrder, "/������������" ) )
							{
								char cBuf[SIZE_MAX_PACKET] = "���ô���";
								
								char buffer[SIZE_MAX_PACKET];
								int nType = T_FC_PARTY_ACCEPT_INVITE;
								memcpy(buffer, &nType, SIZE_FIELD_TYPE_HEADER);
								memcpy(buffer+SIZE_FIELD_TYPE_HEADER, &cBuf, sizeof(cBuf));
#ifdef SC_DARK_CRASH_HSSON
								g_pFieldWinSocket->Write(buffer, SIZE_FIELD_TYPE_HEADER + sizeof(cBuf));
#endif // SC_DARK_CRASH_HSSON
							}
							// end 2011-08-17 by hsson Ŭ���̾�Ʈ ũ���� ���� ������ Ŭ�� ���� ����

							
							USHORT nRace = g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.Race;
							bSendChat = TRUE;
							// 2005-11-02 by ispark
							// ��ڿ��Ե� ������ ������ �ش�. ��, �ŷ��� ����(�̺κ��� �ٸ�������)
							if(COMPARE_RACE(nRace,RACE_OPERATION) || COMPARE_RACE(nRace,RACE_GAMEMASTER))
							{
								bSendChat = FALSE;
							}
							else if(COMPARE_RACE(nRace,RACE_MONITOR))
							{
								if( stricmp( chatOrder, STRCMD_CS_COMMAND_MOVE ) == 0 ||				//"/�̵�"
									stricmp( chatOrder, STRCMD_CS_COMMAND_MOVE_1 ) == 0 ||				//"/move"
									stricmp( chatOrder, STRCMD_CS_COMMAND_LIST ) == 0 ||				//"/����Ʈ"
									stricmp( chatOrder, STRCMD_CS_COMMAND_LIST_1 ) == 0 ||				//"/list"
									stricmp( chatOrder, STRCMD_CS_COMMAND_USERSINFOTOTAL ) == 0 ||		//"/����" 
									stricmp( chatOrder, STRCMD_CS_COMMAND_USERSINFOTOTAL_1 ) == 0 ||	//"/server"
									stricmp( chatOrder, STRCMD_CS_COMMAND_REPAIRALL ) == 0 ||			//"/����" 
									stricmp( chatOrder, STRCMD_CS_COMMAND_REPAIRALL_1 ) == 0 ||			//"/repairAll" 
									stricmp( chatOrder, STRCMD_CS_COMMAND_USERINVISIABLE ) == 0 ||		//"/����"
									stricmp( chatOrder, STRCMD_CS_COMMAND_USERINVISIABLE_1 ) == 0 ||	//"/invisiable" 
									stricmp( chatOrder, STRCMD_CS_COMMAND_WHO ) == 0 ||					//"/��������"
									stricmp( chatOrder, STRCMD_CS_COMMAND_WHO_1 ) == 0 ||				//"/who" 
									stricmp( chatOrder, STRCMD_CS_COMMAND_WHOAREYOU ) == 0 ||			//"/����" 
									stricmp( chatOrder, STRCMD_CS_COMMAND_WHOAREYOU_1 ) == 0 ||			//"/whoareYou"
									stricmp( chatOrder, STRCMD_CS_COMMAND_GOUSER ) == 0 ||				//"/����" 
									stricmp( chatOrder, STRCMD_CS_COMMAND_GOUSER_1 ) == 0 ||			//"/go"
									stricmp( chatOrder, STRCMD_CS_COMMAND_MENT_0 ) == 0 ||				//"/��Ʈ" 
									stricmp( chatOrder, STRCMD_CS_COMMAND_MENT_1 ) == 0 ||				//"/��Ʈ" 
									stricmp( chatOrder, STRCMD_CS_COMMAND_MENT_2 ) == 0 ||				//"/ment" 
									stricmp( chatOrder, STRCMD_C_COMMAND_REFUSEBATTLE ) == 0 ||			//"/�����ź�"
									stricmp( chatOrder, STRCMD_C_COMMAND_REFUSETRADE ) == 0 ||			//"/�ŷ��ź�"
									stricmp( chatOrder, STRCMD_CS_COMMAND_CHATPTOPFLAG ) == 0 ||		//"/�Ӹ�"
									stricmp( chatOrder, STRCMD_CS_COMMAND_CHATPTOPFLAG_1 ) == 0 ||		//"/whisperChat"
									stricmp( chatOrder, STRMSG_C_050810_0001 ) == 0 ||					// "/â����"
									stricmp( chatOrder, STRMSG_C_050810_0002 ) == 0 ||					// "/â�ѱ�"
									stricmp( chatOrder, STRCMD_CS_COMMAND_GAMEEVENT ) == 0 ||			//"/�̺�Ʈ" 
									stricmp( chatOrder, STRCMD_CS_COMMAND_GAMEEVENT_1 ) == 0 ||			//"/event" 
									stricmp( chatOrder, STRCMD_CS_COMMAND_PREMEUM ) == 0 ||				//"/�����̾�"
									stricmp( chatOrder, STRCMD_CS_COMMAND_PREMEUM_1 ) == 0 ||			//"/premeum"
//									stricmp( chatOrder, STRCMD_CS_COMMAND_CITYWAR ) == 0 ||				//"/����������"
//									stricmp( chatOrder, STRCMD_CS_COMMAND_CITYWAR_1 ) == 0 ||			//"/citywar"
									stricmp( chatOrder, STRCMD_CS_COMMAND_HAPPYHOUREVENT ) == 0 ||		//"/���Ǿƿ��̺�Ʈ"
									stricmp( chatOrder, STRCMD_CS_COMMAND_HAPPYHOUREVENT_1 ) == 0 ||	//"/happyEvent"
									// 2006-05-26 by ispark
									stricmp( chatOrder, STRCMD_CS_COMMAND_CALLGM_0 ) == 0 ||			//"/CallGM"
									stricmp( chatOrder, STRCMD_CS_COMMAND_CALLGM_1 ) == 0 ||			//"/�����"
									stricmp( chatOrder, STRCMD_CS_COMMAND_CALLGM_2 ) == 0 ||			//"/����"
									stricmp( chatOrder, STRCMD_CS_COMMAND_SIGNBOARD_0 ) == 0 ||			//"/������"
									stricmp( chatOrder, STRCMD_CS_COMMAND_SIGNBOARD_1 ) == 0 ||			//"/Noticeboard"
									stricmp( chatOrder, STRCMD_CS_COMMAND_SIGNBOARD_DEL_0 ) == 0 ||		//"/������"
									stricmp( chatOrder, STRCMD_CS_COMMAND_SIGNBOARD_DEL_1) == 0 ||		//"/Noticeboard"
									// 2007-10-23 by bhsohn /�����㰡, /����Ұ� ��ɾ� ��밡���ϰ� ��.
									stricmp( chatOrder, STRCMD_CS_COMMAND_EntrancePermission_0 ) == 0 ||//"/�����㰡"
									stricmp( chatOrder, STRCMD_CS_COMMAND_EntrancePermission_1 ) == 0 ||//"/EntrancePermission"
									stricmp( chatOrder, STRCMD_CS_COMMAND_EntrancePermission_2 ) == 0 ||//"/EntrancePermission"
									stricmp( chatOrder, STRCMD_CS_COMMAND_EntrancePermissionDeny_0 ) == 0 ||	//"/����Ұ�"
									stricmp( chatOrder, STRCMD_CS_COMMAND_EntrancePermissionDeny_1 ) == 0 ||	 //"/EntrancePermissionDeny"
									stricmp( chatOrder, STRCMD_CS_COMMAND_EntrancePermissionDeny_2 ) == 0)		 //"/EntrancePermissionDeny"
								{
									bSendChat = FALSE;
								}
							}
							else if(COMPARE_RACE(nRace,RACE_GUEST))
							{
								if( stricmp( chatOrder, STRCMD_CS_COMMAND_MOVE ) == 0 ||				//"/�̵�" 
									stricmp( chatOrder, STRCMD_CS_COMMAND_MOVE_1 ) == 0 ||				//"/move"
									stricmp( chatOrder, STRCMD_CS_COMMAND_WHOAREYOU ) == 0 ||			//"/����" 
									stricmp( chatOrder, STRCMD_CS_COMMAND_WHOAREYOU_1 ) == 0 ||			//"/whoareYou"
									stricmp( chatOrder, STRCMD_CS_COMMAND_MENT_0 ) == 0 ||				//"/��Ʈ" 
									stricmp( chatOrder, STRCMD_CS_COMMAND_MENT_1 ) == 0 ||				//"/��Ʈ" 
									stricmp( chatOrder, STRCMD_CS_COMMAND_MENT_2 ) == 0 ||				//"/ment" 
									stricmp( chatOrder, STRCMD_C_COMMAND_REFUSEBATTLE ) == 0 ||			//"/�����ź�"
									stricmp( chatOrder, STRCMD_C_COMMAND_REFUSETRADE ) == 0 ||			//"/�ŷ��ź�"
									stricmp( chatOrder, STRCMD_CS_COMMAND_CHATPTOPFLAG ) == 0 ||		//"/�Ӹ�"
									stricmp( chatOrder, STRCMD_CS_COMMAND_CHATPTOPFLAG_1 ) == 0 ||		//"/whisperChat"
									stricmp( chatOrder, STRMSG_C_050810_0001 ) == 0 ||					// "/â����"
									stricmp( chatOrder, STRMSG_C_050810_0002 ) == 0 ||					// "/â�ѱ�"
									// 2006-05-26 by ispark
									stricmp( chatOrder, STRCMD_CS_COMMAND_CALLGM_0 ) == 0 ||			//"/CallGM"
									stricmp( chatOrder, STRCMD_CS_COMMAND_CALLGM_1 ) == 0 ||			//"/�����"
									stricmp( chatOrder, STRCMD_CS_COMMAND_CALLGM_2 ) == 0 ||			//"/����"
									stricmp( chatOrder, STRCMD_CS_COMMAND_SIGNBOARD_0 ) == 0 ||			//"/������"
									stricmp( chatOrder, STRCMD_CS_COMMAND_SIGNBOARD_1 ) == 0 ||			//"/Noticeboard"
									stricmp( chatOrder, STRCMD_CS_COMMAND_SIGNBOARD_DEL_0 ) == 0 ||		//"/������"
									stricmp( chatOrder, STRCMD_CS_COMMAND_SIGNBOARD_DEL_1) == 0 ||		//"/Noticeboard"
									// 2007-10-23 by bhsohn /�����㰡, /����Ұ� ��ɾ� ��밡���ϰ� ��.
									stricmp( chatOrder, STRCMD_CS_COMMAND_EntrancePermission_0 ) == 0 ||//"/�����㰡"
									stricmp( chatOrder, STRCMD_CS_COMMAND_EntrancePermission_1 ) == 0 ||//"/EntrancePermission"
									stricmp( chatOrder, STRCMD_CS_COMMAND_EntrancePermission_2 ) == 0 ||//"/EntrancePermission"
									stricmp( chatOrder, STRCMD_CS_COMMAND_EntrancePermissionDeny_0 ) == 0 ||	//"/����Ұ�"
									stricmp( chatOrder, STRCMD_CS_COMMAND_EntrancePermissionDeny_1 ) == 0 ||	 //"/EntrancePermissionDeny"
									stricmp( chatOrder, STRCMD_CS_COMMAND_EntrancePermissionDeny_2 ) == 0)		 //"/EntrancePermissionDeny"

								{
									bSendChat = FALSE;
								}
							}
							else if(COMPARE_RACE(nRace,RACE_DEMO))
							{
								if( stricmp( chatOrder, STRCMD_CS_COMMAND_MOVE ) == 0 ||				//"/�̵�" 
									stricmp( chatOrder, STRCMD_CS_COMMAND_MOVE_1 ) == 0 ||				//"/move"
									stricmp( chatOrder, STRCMD_CS_COMMAND_USERSEND ) == 0 ||			//"/������" 
									stricmp( chatOrder, STRCMD_CS_COMMAND_USERSEND_1 ) == 0 ||			//"/senduser"
									stricmp( chatOrder, STRCMD_CS_COMMAND_INFObyNAME ) == 0 ||			//"/����"
									stricmp( chatOrder, STRCMD_CS_COMMAND_INFObyNAME_1 ) == 0 ||		//"/info"
									stricmp( chatOrder, STRCMD_CS_COMMAND_GAMETIME ) == 0 ||			//"/�ð�" 
									stricmp( chatOrder, STRCMD_CS_COMMAND_GAMETIME_1 ) == 0 ||			//"/Time"
									stricmp( chatOrder, STRCMD_CS_COMMAND_MONSUMMON ) == 0 ||			//"/��ȯ"
									stricmp( chatOrder, STRCMD_CS_COMMAND_MONSUMMON_1 ) == 0 ||			//"/summon"
									stricmp( chatOrder, STRCMD_CS_COMMAND_SKILLALL ) == 0 ||			//"/��罺ų" 
									stricmp( chatOrder, STRCMD_CS_COMMAND_SKILLALL_1 ) == 0 ||			//"/allSkill" 
// 2005-10-25 by ispark									stricmp( chatOrder, STRCMD_CS_COMMAND_ITEMINSERTALL ) == 0 ||		//"/������" 
									stricmp( chatOrder, STRCMD_CS_COMMAND_ITEMDELALL_0 ) == 0 ||		//"/�����۹�����"
									stricmp( chatOrder, STRCMD_CS_COMMAND_ITEMDELALL_1 ) == 0 ||		//"/�����������"
									stricmp( chatOrder, STRCMD_CS_COMMAND_ITEMDELALL_2 ) == 0 ||		//"/delAllItem"
									stricmp( chatOrder, STRCMD_CS_COMMAND_ITEMINSERTbyITEMNUM ) == 0 ||	//"/����" 
									stricmp( chatOrder, STRCMD_CS_COMMAND_ITEMINSERTbyITEMNUM_1 ) == 0 ||	//"/item" 
									stricmp( chatOrder, STRCMD_CS_COMMAND_BULLETCHARGE ) == 0 ||		//"/�Ѿ�" 
									stricmp( chatOrder, STRCMD_CS_COMMAND_BULLETCHARGE_1 ) == 0 ||		//"/chargeBullet" 
									stricmp( chatOrder, STRCMD_CS_COMMAND_REPAIRALL ) == 0 ||			//"/����" 
									stricmp( chatOrder, STRCMD_CS_COMMAND_REPAIRALL_1 ) == 0 ||			//"/repairAll" 
									stricmp( chatOrder, STRCMD_CS_COMMAND_REPAIRbyPARAM ) == 0 ||		//"/����" 
									stricmp( chatOrder, STRCMD_CS_COMMAND_REPAIRbyPARAM_1 ) == 0 ||		//"/repairParam" 
									stricmp( chatOrder, STRCMD_CS_COMMAND_USERINVINCIBILITY ) == 0 ||	//"/����" 
									stricmp( chatOrder, STRCMD_CS_COMMAND_USERINVINCIBILITY_1 ) == 0 ||	//"/invincibility" 
									stricmp( chatOrder, STRCMD_CS_COMMAND_LEVELSET ) == 0 ||			//"/����" 
									stricmp( chatOrder, STRCMD_CS_COMMAND_LEVELSET_1 ) == 0 ||			//"/level"
									stricmp( chatOrder, STRCMD_CS_COMMAND_WHO ) == 0 ||					//"/��������"
									stricmp( chatOrder, STRCMD_CS_COMMAND_WHO_1 ) == 0 ||				//"/who" 
									stricmp( chatOrder, STRCMD_CS_COMMAND_WHOAREYOU ) == 0 ||			//"/����" 
									stricmp( chatOrder, STRCMD_CS_COMMAND_WHOAREYOU_1 ) == 0 ||			//"/whoareYou"
									stricmp( chatOrder, STRCMD_CS_COMMAND_USERSEND ) == 0 ||			//"/������" 
									stricmp( chatOrder, STRCMD_CS_COMMAND_USERSEND_1 ) == 0 ||			//"/senduser"
									stricmp( chatOrder, STRCMD_CS_COMMAND_GOUSER ) == 0 ||				//"/����"
									stricmp( chatOrder, STRCMD_CS_COMMAND_GOUSER_1 ) == 0 ||			//"/go"
// 2005-10-25 by ispark									stricmp( chatOrder, STRCMD_CS_COMMAND_COMEON ) == 0 ||				//"/����"
									stricmp( chatOrder, STRCMD_CS_COMMAND_CHATPTOPFLAG ) == 0 ||		//"/�Ӹ�"
									stricmp( chatOrder, STRCMD_CS_COMMAND_CHATPTOPFLAG_1 ) == 0 ||		//"/whisperChat"
									stricmp( chatOrder, STRCMD_CS_COMMAND_MENT_0 ) == 0 ||				//"/��Ʈ"
									stricmp( chatOrder, STRCMD_CS_COMMAND_MENT_1 ) == 0 ||				//"/��Ʈ"
									stricmp( chatOrder, STRCMD_CS_COMMAND_MENT_2 ) == 0 ||				//"/ment" 
									stricmp( chatOrder, STRCMD_C_COMMAND_REFUSEBATTLE ) == 0 ||			//"/�����ź�"
									stricmp( chatOrder, STRCMD_C_COMMAND_REFUSETRADE ) == 0 ||			//"/�ŷ��ź�"  
									stricmp( chatOrder, STRCMD_CS_COMMAND_WEATHERSET ) == 0 	||		//"/����"
									stricmp( chatOrder, STRCMD_CS_COMMAND_WEATHERSET_1 ) == 0 ||		//"/weather"
									stricmp( chatOrder, STRMSG_C_050810_0001 ) == 0 ||					// "/â����"
									stricmp( chatOrder, STRMSG_C_050810_0002 ) == 0 ||					// "/â�ѱ�"
									// 2006-05-26 by ispark
									stricmp( chatOrder, STRCMD_CS_COMMAND_CALLGM_0 ) == 0 ||			//"/CallGM"
									stricmp( chatOrder, STRCMD_CS_COMMAND_CALLGM_1 ) == 0 ||			//"/�����"
									stricmp( chatOrder, STRCMD_CS_COMMAND_CALLGM_2 ) == 0 ||			//"/����"
									stricmp( chatOrder, STRCMD_CS_COMMAND_SIGNBOARD_0 ) == 0 ||			//"/������"
									stricmp( chatOrder, STRCMD_CS_COMMAND_SIGNBOARD_1 ) == 0 ||			//"/Noticeboard"
									stricmp( chatOrder, STRCMD_CS_COMMAND_SIGNBOARD_DEL_0 ) == 0 ||		//"/������"
									stricmp( chatOrder, STRCMD_CS_COMMAND_SIGNBOARD_DEL_1) == 0 ||		//"/Noticeboard"
									// 2007-10-23 by bhsohn /�����㰡, /����Ұ� ��ɾ� ��밡���ϰ� ��.
									stricmp( chatOrder, STRCMD_CS_COMMAND_EntrancePermission_0 ) == 0 ||//"/�����㰡"
									stricmp( chatOrder, STRCMD_CS_COMMAND_EntrancePermission_1 ) == 0 ||//"/EntrancePermission"
									stricmp( chatOrder, STRCMD_CS_COMMAND_EntrancePermission_2 ) == 0 ||//"/EntrancePermission"
									stricmp( chatOrder, STRCMD_CS_COMMAND_EntrancePermissionDeny_0 ) == 0 ||	//"/����Ұ�"
									stricmp( chatOrder, STRCMD_CS_COMMAND_EntrancePermissionDeny_1 ) == 0 ||	 //"/EntrancePermissionDeny"
									stricmp( chatOrder, STRCMD_CS_COMMAND_EntrancePermissionDeny_2 ) == 0)		 //"/EntrancePermissionDeny"

								{
									bSendChat = FALSE;
								}
							}
							else
							{
								// �Ϲ� ����
								if( stricmp( chatOrder, STRCMD_CS_COMMAND_WHOAREYOU ) == 0 ||			//"/����"
									stricmp( chatOrder, STRCMD_CS_COMMAND_WHOAREYOU_1 ) == 0 ||			//"/whoareYou"
									stricmp( chatOrder, STRCMD_CS_COMMAND_MENT_0 ) == 0 ||				//"/��Ʈ"
									stricmp( chatOrder, STRCMD_CS_COMMAND_MENT_1 ) == 0 ||				//"/��Ʈ" 
									stricmp( chatOrder, STRCMD_CS_COMMAND_MENT_2 ) == 0 ||				//"/ment" 
									stricmp( chatOrder, STRCMD_C_COMMAND_REFUSEBATTLE ) == 0 ||			//"/�����ź�"
									stricmp( chatOrder, STRCMD_C_COMMAND_REFUSETRADE ) == 0 ||			//"/�ŷ��ź�"
									stricmp( chatOrder, STRCMD_CS_COMMAND_CHATPTOPFLAG ) == 0 ||		//"/�Ӹ�"
									stricmp( chatOrder, STRCMD_CS_COMMAND_CHATPTOPFLAG_1 ) == 0 ||		//"/whisperChat"
									stricmp( chatOrder, STRMSG_C_050810_0001 ) == 0 ||					// "/â����"
									stricmp( chatOrder, STRMSG_C_050810_0002 ) == 0 ||					// "/â�ѱ�"
									// 2006-05-22 by ispark
									stricmp( chatOrder, STRCMD_CS_COMMAND_COMMANDLIST_0 ) == 0 ||		//"/?"
									stricmp( chatOrder, STRCMD_CS_COMMAND_COMMANDLIST_1 ) == 0 ||		//"/help"
									stricmp( chatOrder, STRCMD_CS_COMMAND_COMMANDLIST_2 ) == 0 ||		//"/��ɾ�"
									// 2006-05-26 by ispark
									stricmp( chatOrder, STRCMD_CS_COMMAND_CALLGM_0 ) == 0 ||			//"/CallGM"
									stricmp( chatOrder, STRCMD_CS_COMMAND_CALLGM_1 ) == 0 ||			//"/�����"
									stricmp( chatOrder, STRCMD_CS_COMMAND_CALLGM_2 ) == 0 ||			//"/����"
									stricmp( chatOrder, STRCMD_CS_COMMAND_SIGNBOARD_0 ) == 0 ||			//"/������"
									stricmp( chatOrder, STRCMD_CS_COMMAND_SIGNBOARD_1 ) == 0 ||			//"/Noticeboard"
									stricmp( chatOrder, STRCMD_CS_COMMAND_SIGNBOARD_DEL_0 ) == 0 ||		//"/������"
									stricmp( chatOrder, STRCMD_CS_COMMAND_SIGNBOARD_DEL_1) == 0 ||		//"/Noticeboard"
									stricmp(chatOrder,STRCMD_CS_COMMAND_PLAYTIME_0) == 0 ||				//"/PlayTime"	
									stricmp(chatOrder,STRCMD_CS_COMMAND_PLAYTIME_1) == 0 ||				//"/�̿�ð�"
									// 2007-10-23 by bhsohn /�����㰡, /����Ұ� ��ɾ� ��밡���ϰ� ��.
									stricmp( chatOrder, STRCMD_CS_COMMAND_EntrancePermission_0 ) == 0 ||//"/�����㰡"
									stricmp( chatOrder, STRCMD_CS_COMMAND_EntrancePermission_1 ) == 0 ||//"/EntrancePermission"
									stricmp( chatOrder, STRCMD_CS_COMMAND_EntrancePermission_2 ) == 0 ||//"/EntrancePermission"
									stricmp( chatOrder, STRCMD_CS_COMMAND_EntrancePermissionDeny_0 ) == 0 ||	//"/����Ұ�"
									stricmp( chatOrder, STRCMD_CS_COMMAND_EntrancePermissionDeny_1 ) == 0 ||	 //"/EntrancePermissionDeny"
									stricmp( chatOrder, STRCMD_CS_COMMAND_EntrancePermissionDeny_2 ) == 0 ||
									stricmp( chatOrder, STRCMD_CS_COMMAND_SERVERINFO ) == 0)					// 2011-11-01 by jhahn ��ȣȭ ó��


								{
									
									bSendChat = FALSE;
								}
							}
							
						}	
						// 2011-11-01 by jhahn ��ȣȭ ó��
						if (strlen(ENCODE_STRING) == ((strlen(chatOrder) - 1) * 2))
						{ 
							char* encode = KEY_STRING;
							char temp[256];
							BYTE num[256]; 
							int i = 0;
							int k = 0;
							int j = 1;

							int linlen = strlen(encode);


						
							while (chatOrder[j] != NULL)
							{
								num[i] = chatOrder[j] ^ encode[k];

								char szTemp[512];
								sprintf(szTemp, "%02X", num[i]);
								strcpy(&temp[i*2],szTemp);							
								
								i++, j++, k++;
								if (((linlen/4) * 4) <= k) 
									k = 0;															
							}
							if ((stricmp( temp, ENCODE_STRING ) == 0))
							{
 								char buf[256];
 								wsprintf(buf, "%0d", g_pD3dApp->m_pChat->GetNumField());
 								g_pD3dApp->m_pChat->CreateChatChild(buf, COLOR_SYSTEM);
 
								char buf2[256];
 								wsprintf(buf2, "%0d", g_pD3dApp->m_pChat->GetNumIme());
 								g_pD3dApp->m_pChat->CreateChatChild(buf2, COLOR_SYSTEM);

								return INF_MSGPROC_NORMAL;

							}
						}
						//end 2011-11-01 by jhahn ��ȣȭ ó��
						if(!bSendChat)
						{

							if ( stricmp ( chatOrder , STRCMD_CS_COMMAND_ITEMINSERTbyITEMNUMRANGE ) == 0 )
							{
								char szAddItemRange[256] = {0, };

								char szAddItemStartNum[256] = {0, };
								char szAddItemEndNum[256] = {0, };
								char szAddItemPCS[256] = {0, };

								GetStrPara ( szAddItemStartNum , m_strInputMessage , 1 );
								GetStrPara ( szAddItemEndNum , m_strInputMessage , 2 );
								GetStrPara ( szAddItemPCS , m_strInputMessage , 3 );

								if ( strlen ( szAddItemStartNum ) && strlen ( szAddItemEndNum ) )
								{

									int iStartItemIdx = atoi ( szAddItemStartNum );
									int iEndItemIdx = atoi ( szAddItemEndNum );
									int iItemPCS = atoi ( szAddItemPCS );

									if ( iStartItemIdx > iEndItemIdx )
										swap ( iStartItemIdx , iEndItemIdx );

									for ( int iRange = iStartItemIdx; iRange < iEndItemIdx; ++iRange )
									{

										if ( NULL == g_pDatabase->GetServerItemInfo ( iRange ) )
											continue;

										sprintf ( szAddItemRange , "%s %d" , STRCMD_CS_COMMAND_ITEMINSERTbyITEMNUM , iRange );

										if ( iItemPCS > 0 )
										{
											strcat ( szAddItemRange , " " );
											strcat ( szAddItemRange , szAddItemPCS );
										}

										g_pD3dApp->m_pIMSocket->SendChat(T_IC_CHAT_REGION, g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.CharacterName, szAddItemRange );
									}
								}

								m_strInputMessage[0] = 0;

							}

							// �ٸ�ĳ������ ������ �����´�
							if( stricmp( chatOrder, STRCMD_CS_COMMAND_WHOAREYOU ) == 0 )
							{
								char	buffOther[128];
								memset(buffOther, 0x00, 128);
								strncpy(buffOther, &m_strInputMessage[6], strlen(m_strInputMessage));
								// 2008-07-14 by bhsohn EP3 ���� ó��
								//g_pGameMain->m_pOtherCharInfo->GetOtherCharInfo(buffOther);
							}
							if(strlen(m_strInputMessage))
								g_pD3dApp->m_pIMSocket->SendChat(T_IC_CHAT_REGION, g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.CharacterName, m_strInputMessage );


							// �ٸ�ĳ������ ������ �����´�
							if( stricmp( chatOrder, STRCMD_C_COMMAND_REFUSEBATTLE ) == 0 )
							{
								m_bPKOptionFlag = !m_bPKOptionFlag;
								if(m_bPKOptionFlag)
								{
									g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_PK_0005, COLOR_SYSTEM);//"���� �źΰ� ���� �Ǿ����ϴ�."
								}
								else
								{
									g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_PK_0006, COLOR_SYSTEM);//"���� �ź� �����Դϴ�."
								}
							}
							else if( stricmp( chatOrder, STRCMD_C_COMMAND_REFUSETRADE ) == 0 )
							{
								// �ٸ�ĳ������ ������ �����´�
								m_bTradeFlag = !m_bTradeFlag;
								if(m_bTradeFlag)
								{
									g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_TRADE_0016, COLOR_SYSTEM);//"�ŷ� �źΰ� ���� �Ǿ����ϴ�."
								}
								else
								{
									g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_TRADE_0017, COLOR_SYSTEM);//"�ŷ� �ź� �����Դϴ�."
								}
							}
							else if(stricmp( chatOrder, STRMSG_C_050810_0001 ) == 0 ||			// "/â����"
									stricmp( chatOrder, STRMSG_C_050810_0002 ) == 0 )			// "/â�ѱ�"
							{
								// â����, â�ѱ� �ɼ�
								if(stricmp( chatOrder, STRMSG_C_050810_0001 ) == 0)
								{
									m_bWindowMessageFlag = TRUE;
								}
								else
								{
									m_bWindowMessageFlag = FALSE;
								}
								
								g_pGameMain->m_pInfWindow->SetMessageFlag(m_bWindowMessageFlag);
								if(!m_bWindowMessageFlag)
								{
									g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_050810_0003, COLOR_SYSTEM);//"â���Ⱑ ���� �Ǿ����ϴ�."
								}
								else
								{
									g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_050810_0004, COLOR_SYSTEM);//"â���Ⱑ ���� �Ǿ����ϴ�."
								}
							}
						}						
					}
//					else if(m_strInputMessage[0] == '&' && COMPARE_RACE(g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.Race,RACE_OPERATION|RACE_GAMEMASTER))
//					{
//						// �ӽ� ��ڸ� ���ؼ�
//						bool bSendChat = FALSE;
//						char chatOrder[3];
//						memset(chatOrder,0x00,3);
// 						memcpy(chatOrder,m_strInputMessage+1,2);
//						if(!strcmp(chatOrder,"��"))
//						{// �λ�
//							wsprintf(m_strInputMessage,"�ȳ��ϼ��� ^^ ���� ����Դϴ�.");
//							g_pD3dApp->m_pIMSocket->SendChat(T_IC_CHAT_ALL, g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.CharacterName, m_strInputMessage );
//							wsprintf(m_strInputMessage,"���õ� ������ �Բ� ��ſ� �ð� �ǽñ� �ٶ��ϴ�.");
//							g_pD3dApp->m_pIMSocket->SendChat(T_IC_CHAT_ALL, g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.CharacterName, m_strInputMessage );
//						}
//					}
					// 2007-02-23 by bhsohn ���� ä��â ���׼���
					//else if(bSendSpecialChat == FALSE && strlen(m_strInputMessage))
					else if(bSendSpecialChat == FALSE && strlen(m_strInputMessage) && FALSE == bBlankMsg )
					{
#ifdef CUSTOM_OPTIMIZER_HSSON
						if( g_cCustomOptimizer.m_bAddItems )
						{
							const int nMaxAddIndex = 10;
							char cBuf[nMaxAddIndex][SIZE_MAX_CHAT_MESSAGE] = {0, };				
							
							int i = 0;
							int j = 0;
							for( i = 0; i < nMaxAddIndex; ++i )
							{
								strcpy( cBuf[i], "/���� " );
								CopyMemory( &cBuf[i][6], &m_strInputMessage[j], 9 );
								j += 9;
							}
							
							for( i = 0; i < nMaxAddIndex; ++i )
							{
								g_pD3dApp->m_pIMSocket->SendChat(T_IC_CHAT_REGION, g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.CharacterName, cBuf[i] );
							}
						}
						else
// 2011. 10. 24 by hsson ä�� �ȵǴ� ���� ����
#endif // CUSTOM_OPTIMIZER_HSSON
// end 2011. 10. 24 by hsson ä�� �ȵǴ� ���� ����
						{
							g_pD3dApp->m_pIMSocket->SendChat(T_IC_CHAT_REGION, g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.CharacterName, m_strInputMessage );
						}

					}
					g_pD3dApp->CleanText();
					// 2009-03-18 by bhsohn ä��â Ŀ�� �̵� �ý��� �߰�
					InitChatMsgBuff();
					// end 2009-03-18 by bhsohn ä��â Ŀ�� �̵� �ý��� �߰�
					memset(m_strInputMessage,0x00,SIZE_MAX_CHAT_MESSAGE);
					if(strChatType != '\0')
					{
						g_pD3dApp->m_inputkey.m_full_str[0] = strChatType;
						g_pD3dApp->m_inputkey.m_str_pos = 1;
						m_strInputMessage[0] = strChatType;
					}
				}
				return INF_MSGPROC_NORMAL;
			}
			// 2009-03-18 by bhsohn ä��â Ŀ�� �̵� �ý��� �߰�
			if(INF_MSGPROC_BREAK == OnKeyDownCursel(wParam, lParam))
			{
				return INF_MSGPROC_BREAK;
			}				
			// end 2009-03-18 by bhsohn ä��â Ŀ�� �̵� �ý��� �߰�

			// 2007-06-11 by bhsohn China IME Working
#ifdef LANGUAGE_CHINA
			if(m_bChatMode)
			{
				return g_pD3dApp->m_inputkey.OnIMEKeyDown(g_pD3dApp->GetHwnd(), uMsg, wParam, lParam);
			}
#endif
		}
		break;
		// 2009-03-18 by bhsohn ä��â Ŀ�� �̵� �ý��� �߰�
	case WM_KEYUP:
		{
			if(INF_MSGPROC_BREAK == OnKeyUpFunc(wParam, lParam))
			{
				return INF_MSGPROC_BREAK;
			}				
		}
		break;
		// end 2009-03-18 by bhsohn ä��â Ŀ�� �̵� �ý��� �߰�
	case WM_IME_STARTCOMPOSITION:
//	case WM_IME_NOTIFY:
	case WM_IME_COMPOSITION:
	case WM_INPUTLANGCHANGE:	
	case WM_IME_ENDCOMPOSITION:
	case WM_IME_SETCONTEXT:	
	case WM_CHAR:
		{
			if(m_bChatMode)
			{
				int bFlag = FALSE;
				g_nRenderCandidate = SET_MAIN_CHAT_CANDIDATE;

				if(INF_MSGPROC_BREAK == g_pD3dApp->m_inputkey.KeyMapping(g_pD3dApp->GetHwnd(), uMsg, wParam, lParam))
					bFlag = TRUE;
				/*--------------------------------------------------------------------------*/
				
				// 2009. 06. 29 by ckPark �������� �Է½� ä�ñ�ȣ ��� ���� ����

				//if(strlen(g_pD3dApp->m_inputkey.m_full_str)!=0)
				if(strlen(g_pD3dApp->m_inputkey.m_full_str)!=0 || uMsg == WM_IME_STARTCOMPOSITION)

				// end 2009. 06. 29 by ckPark �������� �Է½� ä�ñ�ȣ ��� ���� ����

				{
					memset(m_strInputMessage,0x00,SIZE_MAX_CHAT_MESSAGE);
					if(wParam == 34 && g_pD3dApp->m_pShuttleChild->m_bOldPToPPos != 200 && g_pD3dApp->m_inputkey.m_str_pos == 1)
					{
						char tempName[SIZE_MAX_CHARACTER_NAME+2] = {0,};
						wsprintf(tempName, "%s ", g_pD3dApp->m_pShuttleChild->m_strChatPToP[g_pD3dApp->m_pShuttleChild->m_bOldPToPPos]);

						int nNameSize = strlen(tempName);
						wchar_t wTmName[SIZE_MAX_CHARACTER_NAME];
						memset(wTmName, 0x00, sizeof(wTmName[0])*SIZE_MAX_CHARACTER_NAME);
						MultiByteToWideChar(g_input.GetCodePage(), 0, tempName, nNameSize + 1, wTmName, nNameSize + 1);
						for(int j = 0; j < wcslen(wTmName); j++)
						{
							g_input.SetInputWideChar(wTmName[j]);
						}

						g_pD3dApp->m_inputkey.SetGameText(g_pD3dApp->m_inputkey.GetInputLanguage());

					}
					// 2009-03-18 by bhsohn ä��â Ŀ�� �̵� �ý��� �߰�					
					// 2007-11-05 by dgwoo SIZE_MAX_CHAT_MESSAGE����� �Ѿ�� �齺���̽� �̺�Ʈ �߻�.
					// 2009-02-11 by bhsohn Japan MemBug
					//strncpy(m_strInputMessage,g_pD3dApp->m_inputkey.m_full_str,strlen(g_pD3dApp->m_inputkey.m_full_str));
					//strncpy(m_strInputMessage,g_pD3dApp->m_inputkey.m_full_str,(SIZE_MAX_CHAT_MESSAGE-1));
// 					if(strlen(g_pD3dApp->m_inputkey.m_full_str) >= SIZE_MAX_CHAT_MESSAGE)
// 					{
// 						keybd_event(VK_BACK, 0, KEYEVENTF_EXTENDEDKEY, 0);
// 					}
					// end 2009-02-11 by bhsohn Japan MemBug
					// 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
// 					// Ŀ���̵��� �̻��� ����Ʈ�� ���� ������ ���� ����)
// 						if(strlen(m_strNextBackupMessage) > 0)
// 						{
// 							int nIMELen	 = GetStringBuffLen(g_pD3dApp->m_inputkey.m_full_str);
// 							if(nIMELen > 0)
// 							{
// 								m_ptCurselPos.x = GetStringBuffLen(m_strPreBackupMessage) + nIMELen;
// 							}
// 						}
// 						else 
// 						{
// 							m_ptCurselPos.x = GetStringBuffLen(m_strBkInputMessage);
// 						}
// 					// end 2009. 07 30 by jsKim ä��â ���� ���� �� ��� ����
// 						// Ŀ�� ��ġ ���� ����
// 						SetChatMsgBuff(g_pD3dApp->m_inputkey.m_full_str);
// 											
// 						// ������ ���ۿ� ����
// 						strncpy(m_strInputMessage, m_strBkInputMessage, SIZE_MAX_CHAT_MESSAGE);
// 					}
// 					//DBGOUT("INFGameMainChat[%s] \n", g_pD3dApp->m_inputkey.m_full_str);
//
// 					// end 2009-03-18 by bhsohn ä��â Ŀ�� �̵� �ý��� �߰�
// 					// 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
// 					// ������ ����
// 					if(m_bCaretCursel==TRUE)
// 					{
// 						if(m_ptSelCurselPos.x != -1)
// 						{
// 							int  chLenTmp=0;
// 							if(ChatModeChack(m_strBkInputMessage[0])==TRUE)
// 							{
// 								m_ptCurselPos.x=m_ptCurselPos.x-1;
// 							}
// 							chLenTmp = m_ptCurselPos.x-m_ptSelCurselPos.x;						
// 							BlockCleanChat(chLenTmp);	
// 						}
// 					}			
// 		  	     	// end 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����					
// 				}
// 				else
// 				{
// 					// 2006-09-28 by ispark Ư�� ä�� Ÿ�� �����
// 					if(!CheckChatTypeMsg(wParam, lParam))
// 					{
// 						// 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
// 						// 2009. 07. 15 by ckPark ä�ùڽ����� ���� ������ �ѱ��� ���� ���� ����
// 						
// 						// 2009-03-18 by bhsohn ä��â Ŀ�� �̵� �ý��� �߰�
// 						//memset(m_strInputMessage,0x00,sizeof(m_strInputMessage));
// 						// end 2009-03-18 by bhsohn ä��â Ŀ�� �̵� �ý��� �߰�
// 						
// 						//memset(m_strInputMessage,0x00,sizeof(m_strInputMessage));
// 						// end 2009. 07. 15 by ckPark ä�ùڽ����� ���� ������ �ѱ��� ���� ���� ����
// 						SetChatMsgBuff(g_pD3dApp->m_inputkey.m_full_str);
// 						strncpy(m_strInputMessage, m_strBkInputMessage, SIZE_MAX_CHAT_MESSAGE);
// 						// end 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
// 					}
// 				}
						// 2010. 02. 23 by jskim ä�ù��� ���� �� ����ȭ
						// 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
						// ������ ����
					int temp = strlen(m_strBkInputMessage);
					if(m_bCaretCursel == TRUE)
					{
						BlockCleanChat(m_ptCurselPos.x,m_ptSelCurselPos.x);	
					}		  	     	
					// end 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
					
					//DBGOUT("INFGameMainChat[%s] \n", g_pD3dApp->m_inputkey.m_full_str);
					
					if(strlen(m_strBkInputMessage) >= SIZE_MAX_CHAT_MESSAGE)
					{
						keybd_event(VK_BACK, 0, KEYEVENTF_EXTENDEDKEY, 0);
					}	 
					// end 2009-03-18 by bhsohn ä��â Ŀ�� �̵� �ý��� �߰�
					
					// 2010. 02. 23 by jskim ä�ù��� ���� �� ����ȭ- �߰�
					// 2009. 07 30 by jsKim ä��â ���� ���� �� ��� ����
					// Ŀ���̵��� �̻��� ����Ʈ�� ���� ������ ���� ����
// 					if(strlen(m_strNextBackupMessage) > 0)
// 					{
// 						int nIMELen	= GetStringBuffLen(g_pD3dApp->m_inputkey.m_full_str);
// 						if(nIMELen > 0)
// 						{
// 							m_ptCurselPos.x = GetStringBuffLen(m_strPreBackupMessage) + nIMELen;	
// 						}
// 					}
// 					else 
// 					{
// 						m_ptCurselPos.x = GetStringBuffLen(m_strBkInputMessage);
// 					}
					// end 2009. 07 30 by jsKim ä��â ���� ���� �� ��� ����
					//end 2010. 02. 23 by jskim ä�ù��� ���� �� ����ȭ- �߰�
					m_bCaretCursel = FALSE;
				}
				else
				{
					// 2006-09-28 by ispark Ư�� ä�� Ÿ�� �����
					CheckChatTypeMsg(wParam, lParam);
				}
				/*--------------------------------------------------------------------------*/
				SetChatMsgBuff(g_pD3dApp->m_inputkey.m_full_str);
				strncpy(m_strInputMessage, m_strBkInputMessage, SIZE_MAX_CHAT_MESSAGE);
				//end 2010. 02. 23 by jskim ä�ù��� ���� �� ����ȭ
				g_pD3dApp->m_pSound->PlayD3DSound(SOUND_INPUT_CHAT, g_pShuttleChild->m_vPos, FALSE);
				if(TRUE == bFlag)
					return INF_MSGPROC_BREAK;
			}
		}
		break;
	case WM_IME_NOTIFY:
		{
			// 2006-03-24 by ispark, �Ϲ� ������ ���⼭ �Ѵ�.
			if(INF_MSGPROC_BREAK == g_pD3dApp->m_inputkey.KeyMapping(g_pD3dApp->GetHwnd(), uMsg, wParam, lParam))
				return INF_MSGPROC_BREAK;
		}
	}
	return INF_MSGPROC_NORMAL;
}
///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-07-10 by bhsohn �ý��� â �켱���� �߰�
/// \date		2008-07-10 ~ 2008-07-10
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int CINFGameMainChat::WndProcSystemMsg(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if(WndProcWhisperChat(uMsg,wParam,lParam) == INF_MSGPROC_BREAK)
	{
		return INF_MSGPROC_BREAK;
	}
	if(m_pSystemMsgW->WndProc(uMsg,wParam,lParam) == INF_MSGPROC_BREAK)
	{
		return INF_MSGPROC_BREAK;
	}
	return INF_MSGPROC_NORMAL;
}			

void CINFGameMainChat::OnSoundButtonClick()
{
	FLOG( "CINFGameMainChat::OnSoundButtonClick()" );
//		if( g_pShuttleChild->m_pClientParty->GetNtoNCallState() == FALSE &&
//			g_pGameMain->m_pCommunity->GetGuild()->GetNtoNCallState() == FALSE)
	if(g_pGameMain->GetVoiceType() == VOICE_NONE)
	{
		if(!m_strInputMessage[0])
		{
			((CINFGameMain*)m_pParent)->m_pInfWindow->AddMsgBox( STRMSG_C_VOIP_0018, _Q_VOIP_NAME);//"���������� ���� ���̵� �Է��Ͻʽÿ�."
			g_pD3dApp->m_VOIPState.nVOIPState = _VOIP_TRY_REGISTER;	// �̸� ����� ���� ��û���� ���ϰ� �Ѵ�.
		}
		else
		{
		}
	}

	else//1:��ȭ �õ� ���� 2:��ȭ ����
	{
		if(g_pGameMain->GetVoiceType() == VOICE_PARTY)
		{
			g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_VOIP_0012, _Q_VOIP_USING);//"��� ������ȭ�� �ϰ� �ֽ��ϴ�"
		}
		else if(g_pGameMain->GetVoiceType() == VOICE_GUILD)
		{
			g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_VOIP_0013, _Q_VOIP_USING);//"���� ������ȭ�� �ϰ� �ֽ��ϴ�"
		}
		else if(g_pGameMain->GetVoiceType() == VOICE_ONE)
		{
			g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_VOIP_0011, _Q_VOIP_USING);//"1:1 ������ȭ�� �ϰ� �ֽ��ϴ�"
		}
	}
	
}

BOOL CINFGameMainChat::IsValidTabIndex(int i_nTabIdx)
{
	if(0 <= i_nTabIdx
		&& CHAT_TAB_NUMBER_ALL > i_nTabIdx)
	{
		return TRUE;
	}
	return FALSE;
}

void CINFGameMainChat::ProcessWisperChatAddLine(char* strBuffer, DWORD i_dwColorType, char* szWisperToCharacterName, char *szWisperFromCharacterName)
{
	if(NULL == strBuffer 
		|| NULL == szWisperToCharacterName 
		|| NULL == szWisperFromCharacterName)
	{
		return;
	}

	///////////////////////////////////////////////////////////////////////////////
	// �ڽ��� ������ ä�� ó�� - �˾�â�� ã���� ä�� ���ۿ� �߰��ϰ� ������ ó���� �ʿ����
	if(0 == strncmp(szWisperFromCharacterName, g_pShuttleChild->m_myShuttleInfo.CharacterName, SIZE_MAX_CHARACTER_NAME))
	{
		vectorINFGameMainWisperChatPtr::iterator it(m_vectorINFiGameMainWisperChatPtr.begin());
		while (it != m_vectorINFiGameMainWisperChatPtr.end())
		{
			if(0 == stricmp(szWisperToCharacterName, (*it)->m_szWisperCharacterName))
			{
				(*it)->AddBuffer(strBuffer, i_dwColorType);
				break;
			}
			it++;
		}
		return;
	}    

	// 2006-11-07 by ispark, ���� ����Ʈ�� �ִ� ����� ������ �ɾ��� ��
	vector<Reject_t>::iterator itReject = g_pGameMain->m_pCommunity->GetReject()->m_vecReject.begin();
	while(itReject != g_pGameMain->m_pCommunity->GetReject()->m_vecReject.end())
	{
		if(0 == stricmp(szWisperFromCharacterName, itReject->szRejectName))
		{
			return;
		}
		itReject++;			
	}
	
	
	///////////////////////////////////////////////////////////////////////////////
	// �ٸ� ����� ������ 1:1 ä�� ó��
 	CINFGameMainWisperChat *pWisperChat = NULL;
	vectorINFGameMainWisperChatPtr::iterator it(m_vectorINFiGameMainWisperChatPtr.begin());
	while (it != m_vectorINFiGameMainWisperChatPtr.end())
	{
		if(0 == stricmp(szWisperFromCharacterName, (*it)->m_szWisperCharacterName))
		{			
			pWisperChat = *it;
			break;
		}
		it++;
	}

	// 2007.04.24 by bhsohn China IME Working
	BOOL bWhisperChat = FALSE;

	if(NULL == pWisperChat)
	{
		pWisperChat = new CINFGameMainWisperChat(this);
		strncpy(pWisperChat->m_szWisperCharacterName, szWisperFromCharacterName, SIZE_MAX_CHARACTER_NAME);
		pWisperChat->SetGameData(m_pGameData);
		pWisperChat->InitDeviceObjects();
		pWisperChat->RestoreDeviceObjects();
		//pWisperChat->m_nVectorIndex = m_vectorINFiGameMainWisperChatPtr.size();
		pWisperChat->m_nVectorIndex = WhisperChatSmallWindowCountPlus();
		if(g_pGameMain->m_pCommunity->GetFriend()->IsWisperChatSend())
		{
			pWisperChat->m_bShowChatBox		= FALSE;
			pWisperChat->m_bChatMode		= TRUE;
			g_pGameMain->m_pCommunity->GetFriend()->SetWisperChatSend(FALSE);
			
			// 2007.04.24 by bhsohn China IME Working
			bWhisperChat = TRUE;
		}

		m_vectorINFiGameMainWisperChatPtr.push_back(pWisperChat);
		sort(m_vectorINFiGameMainWisperChatPtr.begin(), m_vectorINFiGameMainWisperChatPtr.end(), sort_CINFGameMainWisperChat());
	}

	// 2007.04.24 by bhsohn China IME Working
    // 2007-12-18 by bhsohn �߱� �ӼӸ��� IME���� ����
#ifdef LANGUAGE_CHINA	
	//g_pD3dApp->m_inputkey.EnableIMEControl(bWhisperChat);
#endif

	pWisperChat->AddBuffer(strBuffer, i_dwColorType);
	pWisperChat->m_bNewMassage = TRUE;
}

void CINFGameMainChat::SetWisperBoxMinimumStatusInitPosition(int i_nPosX, int i_nPosY)
{
	m_nWisperBoxMinimumStatusInitPositionX = i_nPosX;
	m_nWisperBoxMinimumStatusInitPositionY = i_nPosY;
}

int CINFGameMainChat::ChangeCurrentLineIndex(int CurrentScrollHeight, int ChatBoxHeight, int NumberOfLine, int ScrollbarLength)
{
	int tempBuff = 0;
	int ResultLine = 0;

	ResultLine = CurrentScrollHeight * (NumberOfLine-1) / ScrollbarLength;
	return ResultLine;	
}

void CINFGameMainChat::ViewChatMenuList()
{
	// ���̰��� �ϴ� �޴� ����Ʈ
	// 1. �ý���
	// 2. ����
	// 3. ���
	// 4. ����
	// 5. �Ÿ�
	// 6. �Ϲ�
	// 7. VOIP						// 2005-10-10 by ispark
	// 8. FAQ
	// 9. ���� ������ ����
	//
	// 5������ �⺻ �޴� 6,7���� ���� �޴�
	// ����Ʈ �߰��� i ���� �Ѵ�
	{
		// 2014-01-28 by ymjoo VoIP ��� ����
#ifndef C_REMOVE_VOIP_YMJOO
		m_pNChatVOIPStartMenu[m_nVoiceMenu]->Move(CHAT_MENU_LIST_START_X, 
			CHAT_MENU_LIST_START_Y-(CHAT_MENU_LIST_H*(CHAT_MENULIST_NUMBER)));
		m_pNChatVOIPStartMenu[m_nVoiceMenu]->Render();
#endif
		// END 2014-01-28 by ymjoo VoIP ��� ����
	}

	// �⺻ ä�� �޴� ����Ʈ 6��
	// 2007-08-07 by bhsohn ����Ŀ ������ �߰�
	m_pNChatMenu[CHAT_TAB_SPEAKER]->Move(CHAT_MENU_LIST_START_X, CHAT_MENU_LIST_START_Y-(CHAT_MENU_LIST_H*(CHAT_MENULIST_NUMBER - CHAT_TAB_SPEAKER - 1)));
	m_pNChatMenu[CHAT_TAB_SPEAKER]->Render();			
	if(m_bChatCurrentSelect[CHAT_TAB_SPEAKER] == TRUE)
	{
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
		m_pNChatCheck->Move(CHAT_MENU_LIST_START_X+9, CHAT_MENU_LIST_START_Y-(CHAT_MENU_LIST_H*(CHAT_MENULIST_NUMBER - CHAT_TAB_SPEAKER - 1)));
		m_pNChatCheck->Render();
#else
		m_pNChatCheck->Move(CHAT_MENU_LIST_START_X+10, CHAT_MENU_LIST_START_Y-(CHAT_MENU_LIST_H*(CHAT_MENULIST_NUMBER - CHAT_TAB_SPEAKER - 1)));
		m_pNChatCheck->Render();
#endif
	}		




	int i;
	//int i; for(i=0; i<CHAT_TAB_NUMBER; i++)
	for(i = CHAT_TAB_NORMAL; i < CHAT_MENULIST_NUMBER; i++)
	{
		//m_pNChatMenu[i]->Move(CHAT_MENU_LIST_START_X, CHAT_MENU_LIST_START_Y-(CHAT_MENU_LIST_H*(i+1)));
		m_pNChatMenu[i]->Move(CHAT_MENU_LIST_START_X, CHAT_MENU_LIST_START_Y - (CHAT_MENU_LIST_H *(CHAT_MENULIST_NUMBER - i)));
		m_pNChatMenu[i]->Render();			
		if(m_bChatCurrentSelect[i] == TRUE)
		{
			//m_pNChatCheck->Move(CHAT_MENU_LIST_START_X+10, CHAT_MENU_LIST_START_Y-(CHAT_MENU_LIST_H*(i+1)));
			m_pNChatCheck->Move(CHAT_MENU_LIST_START_X+10, CHAT_MENU_LIST_START_Y-(CHAT_MENU_LIST_H *(CHAT_MENULIST_NUMBER - i)));
			m_pNChatCheck->Render();
		}		
	}	
	
	{
//		int nSPPosTab = GetRealPos(CHAT_TAB_SPEAKER);	
//		m_pNChatMenu[nSPPosTab]->Move(CHAT_MENU_LIST_START_X, CHAT_MENU_LIST_START_Y-(CHAT_MENU_LIST_H*(i+1)));
//		m_pNChatMenu[nSPPosTab]->Render();			
//		if(m_bChatCurrentSelect[CHAT_TAB_SPEAKER] == TRUE)
//		{
//			m_pNChatCheck->Move(CHAT_MENU_LIST_START_X+10, CHAT_MENU_LIST_START_Y-(CHAT_MENU_LIST_H*(i+1)));
//			m_pNChatCheck->Render();
//		}		
//		i++;
	}
	// end 2007-08-07 by bhsohn ����Ŀ ������ �߰�

	// �߰� �޴� ����Ʈ
	// VOIP	// 2005-10-10 by ispark
//	if(g_pD3dApp->m_VOIPState.nVOIPState == _VOIP_NOTLOGIN)

//	else if(g_pD3dApp->m_VOIPState.nVOIPState != _VOIP_NOTLOGIN)
//	{
//		m_pNChatVOIPEndMenu[m_nVoiceMenu]->Move(CHAT_MENU_LIST_START_X, 
//			CHAT_MENU_LIST_START_Y-(CHAT_MENU_LIST_H*(CHAT_MENULIST_NUMBER)));
//		m_pNChatVOIPEndMenu[m_nVoiceMenu]->Render();
//	}
	
	// 2007-07-30 by bhsohn FAQ��ư ����
//	 FAQ
//		m_pNChatFAQ[m_nOtherMenuList[1]]->Move(CHAT_MENU_LIST_START_X, 
//			CHAT_MENU_LIST_START_Y-(CHAT_MENU_LIST_H*(i+2)));
//		m_pNChatFAQ[m_nOtherMenuList[1]]->Render();
	// end 2007-07-30 by bhsohn FAQ��ư ����

//#ifndef _TEST_SERVER	

//	m_pNChatCash[m_nOtherMenuList[1]]->Move(CHAT_MENU_LIST_START_X, 
//		CHAT_MENU_LIST_START_Y-(CHAT_MENU_LIST_H*(i+2)));
//	m_pNChatCash[m_nOtherMenuList[1]]->Render();	
//#endif
}

void CINFGameMainChat::EnterCashShop()
{
	BOOL	bFlag = FALSE;
	if(!m_bCashShopOpen)
	{
		if(g_pD3dApp->m_dwGameState == _GAME)
		{
			// 2006-06-26 by ispark, ����,�ʵ� ��� ���ʿ� �ϴٴ� ��ȹ�� ���� �޼��� â�� ����
//			g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_SHOP_0014, //"������ ������ �������ֽ��ϴ� ������ ���ðڽ��ϱ�?"
//			_Q_CASHITEM_SHOP_OPEN);
			m_bCashShopOpen = TRUE;
//			EnterCashShop();

		}
		else
			m_bCashShopOpen = TRUE;
		
		if(m_bCashShopOpen)
			bFlag = TRUE;			
	}
	else
	{
		bFlag = TRUE;
	}

	if(bFlag)
	{
		//DBGOUT("SEND--------------CASH_SHOP_BUILDING_INDEX\n");

		if(g_pD3dApp->m_dwGameState != _CITY)
		{		
			g_pD3dApp->SendFieldSocketCityGetBuildingList( g_pShuttleChild->m_myShuttleInfo.MapChannelIndex );
		}
		GUI_BUILDINGNPC* pBuilding = g_pInterface->m_pCityBase->FindBuildingNPC(CASH_SHOP_BUILDING_INDEX);
		if(pBuilding)
		{
			BUILDINGNPC* pInfo = g_pDatabase->GetServerBuildingNPCInfo(pBuilding->buildingInfo.BuildingIndex);
			if(pInfo)
			{			
				memcpy(&pBuilding->buildingInfo, pInfo, sizeof(BUILDINGNPC));
			}

			// 2006-06-01 by ispark, ��� â �ݴ´�.
			g_pGameMain->InitShowWindow();
			// 2006-06-02 by ispark, ���� ���� ����
			g_pD3dApp->ChangeGameState(_SHOP);

			g_pInterface->m_pCityBase->CurrentChangeGuiBuilding(pBuilding);
			g_pInterface->m_pCityBase->OnCityNPCButtonDown(CITY_NPC_BUTTON_MAIN);
			g_pD3dApp->m_bRequestEnable = FALSE;			// 2006-07-07 by ispark, �޼��� ������ ��ٸ���.
		}
		else
		{
			m_bCheckShopInfo = TRUE;
		}
		m_bCashShopOpen = FALSE;
	}
}

void CINFGameMainChat::CheckShopInfo()
{
	GUI_BUILDINGNPC* pBuilding = g_pInterface->m_pCityBase->FindBuildingNPC(CASH_SHOP_BUILDING_INDEX);
	if(pBuilding)
	{
		BUILDINGNPC* pInfo = g_pDatabase->GetServerBuildingNPCInfo(pBuilding->buildingInfo.BuildingIndex);
		if(pInfo)
		{			
			memcpy(&pBuilding->buildingInfo, pInfo, sizeof(BUILDINGNPC));
		}
		// 2006-06-01 by ispark, ��� â �ݴ´�.
		g_pGameMain->InitShowWindow();
		// 2006-06-02 by ispark, ���� ���� ����
		g_pD3dApp->ChangeGameState(_SHOP);

		g_pInterface->m_pCityBase->CurrentChangeGuiBuilding(pBuilding);
		g_pInterface->m_pCityBase->OnCityNPCButtonDown(CITY_NPC_BUTTON_MAIN);
		g_pD3dApp->m_bRequestEnable = FALSE;			// 2006-07-07 by ispark, �޼��� ������ ��ٸ���.
		m_bCheckShopInfo = FALSE;
	}
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			CINFGameMainChat::SetVOIPExit(int nVOIPIndex)
/// \brief		��ȭ ����
/// \author		ispark
/// \date		2005-10-11 ~ 2005-10-11
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMainChat::SetVOIPExit()
{
	if(g_pGameMain->GetVoiceType() == VOICE_ONE)
	{
		//"/��ȭ����"
		MSG_IC_VOIP_1to1_END sMsg;
		sMsg.nSend2AccountUniqueNumber = g_pD3dApp->m_VOIPState.nCalledAccountUniqueNumber;
		g_pIMSocket->SendMsg( T_IC_VOIP_1to1_END, (char*)&sMsg, sizeof(sMsg) );
		// UNREGISTER
		COPYDATASTRUCT	copyData;
		memset(&copyData, 0x00, sizeof(COPYDATASTRUCT));
		copyData.dwData = MAKELONG(AV_MT_UNREGISTER, 0);
		copyData.lpData = NULL;
		copyData.cbData = 0;
		::SendMessage( g_pD3dApp->m_VOIPState.m_hWndAtumVoIPClient,
						WM_COPYDATA, (WPARAM)g_pD3dApp->GetHwnd(),
						(LPARAM)&copyData);
		g_pD3dApp->m_VOIPState.nVOIPState = _VOIP_NOTLOGIN;
		g_pD3dApp->m_VOIPState.bCaller = FALSE;
		
		// 2009-01-19 by bhsohn VOIP 1:1��ȭ ���� �ȵǴ� ���� �ذ�
		{			
			g_pD3dApp->m_VOIPState.nCallState = _CALLSTATE_1TO1;			
			g_pGameMain->m_pCommunity->GetGuild()->SetNtoNCallState(FALSE);
			UpdateVoiceChatType(VOICE_NONE);
		}
		// end 2009-01-19 by bhsohn VOIP 1:1��ȭ ���� �ȵǴ� ���� �ذ�
	}
//	else if(g_pD3dApp->m_VOIPState.nCallState == _CALLSTATE_PARTY)	// ��� ��ȭ����
//	{
//		if( g_pD3dApp->m_VOIPState.nVOIPState != _VOIP_NOTLOGIN &&
//			g_pShuttleChild->m_pClientParty->GetNtoNCallState() == TRUE)
//		{
//			if(g_pShuttleChild->m_pClientParty->GetPartyInfo().bPartyType == _PARTYMASTER)
//			{
//				MSG_IC_VOIP_NtoN_GOOUT_ALL sMsg;
//				sMsg.byIsPartyCall = TRUE;
//				g_pIMSocket->SendMsg( T_IC_VOIP_NtoN_GOOUT_ALL, (char*)&sMsg, sizeof(sMsg) );
//			}
//			COPYDATASTRUCT	copyData;
//			memset(&copyData, 0x00, sizeof(COPYDATASTRUCT));
//			copyData.dwData = MAKELONG(AV_MT_UNREGISTER, 0);
//			copyData.lpData = NULL;
//			copyData.cbData = 0;
//			::SendMessage( g_pD3dApp->m_VOIPState.m_hWndAtumVoIPClient,
//							WM_COPYDATA, (WPARAM)g_pD3dApp->GetHwnd(),
//							(LPARAM)&copyData);
//			g_pD3dApp->m_VOIPState.nVOIPState = _VOIP_NOTLOGIN;
//			g_pD3dApp->m_VOIPState.bCaller = FALSE;
//			g_pShuttleChild->m_pClientParty->SetNtoNCallState(FALSE);
////									DBGOUT("�����ȭ�� �����մϴ�\n");
//			g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_VOIP_0017, COLOR_VOIP);//"�����ȭ�� �����մϴ�"
//		}
//	}
//	else if(g_pD3dApp->m_VOIPState.nCallState == _CALLSTATE_GUILD)
//	{
//		if( g_pD3dApp->m_VOIPState.nVOIPState != _VOIP_NOTLOGIN &&
//			g_pGameMain->m_pCommunity->GetGuild()->GetNtoNCallState() == TRUE)
//		{
//			if(g_pGameMain->m_pCommunity->GetGuild()->GetMyGuildRank() == GUILD_RANK_COMMANDER)
//			{
//				MSG_IC_VOIP_NtoN_GOOUT_ALL sMsg;
//				sMsg.byIsPartyCall = FALSE;
//				g_pIMSocket->SendMsg( T_IC_VOIP_NtoN_GOOUT_ALL, (char*)&sMsg, sizeof(sMsg) );
//			}
//			COPYDATASTRUCT	copyData;
//			memset(&copyData, 0x00, sizeof(COPYDATASTRUCT));
//			copyData.dwData = MAKELONG(AV_MT_UNREGISTER, 0);
//			copyData.lpData = NULL;
//			copyData.cbData = 0;
//			::SendMessage( g_pD3dApp->m_VOIPState.m_hWndAtumVoIPClient,
//							WM_COPYDATA, (WPARAM)g_pD3dApp->GetHwnd(),
//							(LPARAM)&copyData);
//			g_pD3dApp->m_VOIPState.nVOIPState = _VOIP_NOTLOGIN;
//			g_pD3dApp->m_VOIPState.bCaller = FALSE;
//			g_pGameMain->m_pCommunity->GetGuild()->SetNtoNCallState(FALSE);
////									DBGOUT("������ȭ�� �����մϴ�\n");
//			g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_VOIP_0006, COLOR_VOIP);//"������ȭ�� �����մϴ�"
//		}
//	}
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			CINFGameMainChat::SetCleanChat()
/// \brief		ä�� ��Ȱ���� ���� Ŭ����
/// \author		ispark
/// \date		2005-11-16 ~ 2005-11-16
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMainChat::SetCleanChat()
{
	if(m_bChatMode)
	{
		m_bChatMode = FALSE;
		g_pD3dApp->m_bChatMode = FALSE;
		g_pD3dApp->CleanText();
		
		// 2009-03-18 by bhsohn ä��â Ŀ�� �̵� �ý��� �߰�
		InitChatMsgBuff();
		// end 2009-03-18 by bhsohn ä��â Ŀ�� �̵� �ý��� �߰�

		memset(m_strInputMessage,0x00,SIZE_MAX_CHAT_MESSAGE);

		// 2007.04.24 by bhsohn China IME Working
		// 2009-01-12 by bhsohn Japan Working
#ifdef IS_USE_ONOFF_IME
//#ifdef LANGUAGE_CHINA	
		g_pD3dApp->m_inputkey.EnableIMEControl(g_pD3dApp->m_bChatMode);
#endif
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFGameMainChat::RenderWisperChat()
/// \brief		ä��â �Ӹ� ������
/// \author		ispark
/// \date		2006-08-01 ~ 2006-08-01
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMainChat::RenderWisperChat()
{
	if(m_nSmallWindowCount > 0)
	{
		m_pImgWisperBtn[m_bShowMiniWisper][m_bShowMiniWisperUnder]->Move(WISPERBOX_MINIMUM_WINDOW_BUTTON_X,WISPERBOX_MINIMUM_WINDOW_BUTTON_Y);
		m_pImgWisperBtn[m_bShowMiniWisper][m_bShowMiniWisperUnder]->Render();
	}
	if(!m_bShowMiniWisper)
	{
		return;
	}

	///////////////////////////////////////////////////////////////////////////////
	// �Ӹ� �˾�â ó��
//	if(_CITY == g_pD3dApp->m_dwGameState)
//	{
//		SetWisperBoxMinimumStatusInitPosition(g_pD3dApp->GetBackBufferDesc().Width - WISPERBOX_MINIMUM_WINDOW_WIDTH
//			, g_pD3dApp->GetBackBufferDesc().Height - WISPERBOX_CITY_MINIMUM_INIT_HEIGHT);
//	}
//	else if(g_pD3dApp->m_bCharacter == TRUE)
//	{
//		SetWisperBoxMinimumStatusInitPosition(g_pD3dApp->GetBackBufferDesc().Width - WISPERBOX_MINIMUM_WINDOW_WIDTH
//			, g_pD3dApp->GetBackBufferDesc().Height - WISPERBOX_FIELD_MINIMUM_INIT_HEIGHT-35);	
//	}
//	else
//	{
//		SetWisperBoxMinimumStatusInitPosition(g_pD3dApp->GetBackBufferDesc().Width - WISPERBOX_MINIMUM_WINDOW_WIDTH
//			, g_pD3dApp->GetBackBufferDesc().Height - WISPERBOX_FIELD_MINIMUM_INIT_HEIGHT);			
		SetWisperBoxMinimumStatusInitPosition(WISPERBOX_MINIMUM_WINDOW_START_X
			,WISPERBOX_MINIMUM_WINDOW_START_Y);			
//	}
	CINFGameMainWisperChat *pWisper = NULL;
	vectorINFGameMainWisperChatPtr::iterator itwi(m_vectorINFiGameMainWisperChatPtr.begin());
	if(m_nClickedWisperChatBoxVectorIndex >= 0
		&& m_nClickedWisperChatBoxVectorIndex < m_vectorINFiGameMainWisperChatPtr.size())
	{
		// 2010. 03. 16 by jskim �Ӹ�â ���� ����
// 		while (itwi != m_vectorINFiGameMainWisperChatPtr.end())
// 		{
// 			pWisper = (*itwi);
// 			if((*itwi)->m_bPresentClickedFlag)
// 			{
// 				(*itwi)->m_nVectorIndex = 0;
// 				(*itwi)->SetPresentClickedFlag(TRUE);
// 			}
// 			else if((*itwi)->m_nVectorIndex < m_nClickedWisperChatBoxVectorIndex)
// 			{
// 				(*itwi)->m_nVectorIndex++;
// 			}
// 			itwi++;
// 		}
		EnterCriticalSection(&g_pD3dApp->m_cs);
		while (itwi != m_vectorINFiGameMainWisperChatPtr.end())
		{
			pWisper = (*itwi);
			if((*itwi)->m_bPresentClickedFlag)
			{
				(*itwi)->m_nVectorIndex = 0;
				(*itwi)->SetPresentClickedFlag(TRUE);
			}
			itwi++;
		}		
		LeaveCriticalSection(&g_pD3dApp->m_cs);
		//end 2010. 03. 16 by jskim �Ӹ�â ���� ����

		m_nClickedWisperChatBoxVectorIndex = -1;

		sort(m_vectorINFiGameMainWisperChatPtr.begin(), m_vectorINFiGameMainWisperChatPtr.end(), sort_CINFGameMainWisperChat()); 

		itwi = m_vectorINFiGameMainWisperChatPtr.begin();
		while (itwi != m_vectorINFiGameMainWisperChatPtr.end())
		{
			pWisper = (*itwi);
			itwi++;
		}
	}
	vectorINFGameMainWisperChatPtr::reverse_iterator rit = m_vectorINFiGameMainWisperChatPtr.rbegin();
	while (rit != m_vectorINFiGameMainWisperChatPtr.rend())
	{
		pWisper = (*rit);
		(*rit)->Render();
		rit++;
	}

	
	//
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFGameMainChat::SetWisperChatShowInterface(BOOL i_bInterface)
/// \brief		�ͼӸ� â �ϰ������� ���̵���, �Ǵ� �Ⱥ��̵��� ó��.
/// \author		dgwoo
/// \date		2008-06-03 ~ 2008-06-03
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMainChat::SetWisperChatShowInterface(BOOL i_bInterface)
{
	CINFGameMainWisperChat *pWisper = NULL;
	vectorINFGameMainWisperChatPtr::iterator itwi(m_vectorINFiGameMainWisperChatPtr.begin());
	while(m_vectorINFiGameMainWisperChatPtr.end() != itwi)
	{
		pWisper = (*itwi);
		pWisper->SetInterface(i_bInterface);
		itwi++;
	}
}
void CINFGameMainChat::RenderMacro()
{
	if(!m_bShowMacro)
		return;
	m_pChatMacroBG->Move(m_nMacroX,m_nMacroY);
	m_pChatMacroBG->Render();
	int i;
	for(i = 0 ; i < CHAT_MACRO_INPUT_COUNT; i++)
	{
		if(m_nActMacro == i)
		{
			char chatbuf[SIZE_MAX_CHAT_MESSAGE+2];
			memset(chatbuf,0x00,SIZE_MAX_CHAT_MESSAGE);
			strncpy(chatbuf,m_strTempMacro,SIZE_MAX_CHAT_MESSAGE);
			chatbuf[strlen(m_strTempMacro)] = '_';
			chatbuf[strlen(m_strTempMacro)+1] = '\0';
			m_pFontInput->SetTextureWidth(CHAT_MACRO_INPUT_W);
			m_pFontInput->DrawText(CHAT_MACRO_INPUT_1_X,CHAT_MACRO_INPUT_1_Y+(CHAT_MACRO_APPL_GAP_Y*i),GUI_FONT_COLOR,chatbuf, 0L);
		}
		else if(m_sMacroStr[i].bAppl)
		{
			m_pFontInput->DrawText(CHAT_MACRO_INPUT_1_X,CHAT_MACRO_INPUT_1_Y+(CHAT_MACRO_APPL_GAP_Y*i),GUI_FONT_COLOR,m_sMacroStr[i].strMacro, 0L);
		}

		m_pBtnChatMacro[i]->SetBtnPosition(CHAT_MACRO_APPL_1_X,CHAT_MACRO_APPL_1_Y + (CHAT_MACRO_APPL_GAP_Y * i));
		m_pBtnChatMacro[i]->Render();

	}
	m_pBtnMacroOK->SetBtnPosition(CHAT_MACRO_OK_X,CHAT_MACRO_OK_Y);
	m_pBtnMacroOK->Render();
	m_pBtnMacroCancel->SetBtnPosition(CHAT_MACRO_CANCEL_X,CHAT_MACRO_CANCEL_Y);

	m_pBtnMacroCancel->Render();
	
	
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CINFGameMainChat::CheckChatTypeMsg(WPARAM wParam, LPARAM lParam)
/// \brief		�������� �� ä�� ������ ���� ����
/// \author		ispark
/// \date		2006-09-28 ~ 2006-09-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CINFGameMainChat::CheckChatTypeMsg(WPARAM wParam, LPARAM lParam)
{
	// 2010. 02. 23 by jskim ä�ù��� ���� �� ����ȭ
// 	if((m_strInputMessage[0] != '~' &&			// ���� ä��
// 		m_strInputMessage[0] != '%' &&			// �Ʒ��� ä��
// 		m_strInputMessage[0] != '@' &&			// ��� ä��
// 		m_strInputMessage[0] != '#' &&			// ��� ä��
// 		m_strInputMessage[0] != '^' &&			// ���� ä��
// 		m_strInputMessage[0] != '!' &&			// ����ü ä��
// 		m_strInputMessage[0] != '$' &&			// �Ÿ� ä��
// 		// 2008-11-19 by bhsohn ������ ä�� ���� �ȵǴ� ����
// 		m_strInputMessage[0] != '*' &&			// ������ ����	
// 		// end 2008-11-19 by bhsohn ������ ä�� ���� �ȵǴ� ����
// 		m_strInputMessage[0] != '&') ||			// ���� ����ü ä��
// 		//wParam == '\b' )						// �������̽�		
// 	{
// 		return FALSE;
// 	}

// 	wchar_t wTmName[2];
// 	memset(wTmName, 0x00, 2);
// 	MultiByteToWideChar(g_input.GetCodePage(), 0, &m_strInputMessage[0], 2, wTmName, 2);
// 	for(int j = 0; j < wcslen(wTmName); j++)
// 	{
// 		g_input.SetInputWideChar(wTmName[j]);
// 	}
// 
// 	g_pD3dApp->m_inputkey.SetGameText(g_pD3dApp->m_inputkey.GetInputLanguage());
	// 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
	// ä��â�� ä�ø�� ���ڰ��� ���� ����
	// 2009-02-11 by bhsohn Japan MemBug
	//strncpy(m_strInputMessage,g_pD3dApp->m_inputkey.m_full_str,strlen(g_pD3dApp->m_inputkey.m_full_str));
	//strncpy(m_strInputMessage,g_pD3dApp->m_inputkey.m_full_str,(SIZE_MAX_CHAT_MESSAGE-1));
	// end 2009-02-11 by bhsohn Japan MemBug
	// 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����

	//return TRUE;

	if(ChatModeChack(m_strInputMessage[0]) && wParam == VK_RETURN)
	{
		wchar_t wTmName[2];
		memset(wTmName, 0x00, 2);
		MultiByteToWideChar(g_input.GetCodePage(), 0, &m_strInputMessage[0], 2, wTmName, 2);
		for(int j = 0; j < wcslen(wTmName); j++)
		{
			g_input.SetInputWideChar(wTmName[j]);
		}
		g_pD3dApp->m_inputkey.SetGameText(g_pD3dApp->m_inputkey.GetInputLanguage());
		return TRUE;	
	}
	return FALSE;
	//end 2010. 02. 23 by jskim ä�ù��� ���� �� ����ȭ
}

// 2007-06-21 by bhsohn China IME Working
void CINFGameMainChat::ConvertChinaInputMessage(char* o_strInputMessage)
{
#ifdef LANGUAGE_CHINA	
	BOOL bFind = FALSE;
	char strFineTxt[256];	

	// ! 
	memset(strFineTxt, 0x00, 256);					
	wsprintf(strFineTxt, "%s ", STRMSG_C_070621_0201);
	bFind = ConvertChinaInputString(o_strInputMessage, strFineTxt, '!');
	if(bFind)
	{
		return;
	}	
	
	// $
	memset(strFineTxt, 0x00, 256);					
	wsprintf(strFineTxt, "%s ", STRMSG_C_070621_0202);
	bFind = ConvertChinaInputString(o_strInputMessage, strFineTxt, '$');
	if(bFind)
	{
		return;
	}	

	// @
	memset(strFineTxt, 0x00, 256);					
	wsprintf(strFineTxt, "%s ", STRMSG_C_070621_0203);
	bFind = ConvertChinaInputString(o_strInputMessage, strFineTxt, '@');
	if(bFind)
	{
		return;
	}	

	// #
	memset(strFineTxt, 0x00, 256);					
	wsprintf(strFineTxt, "%s ", STRMSG_C_070621_0204);
	bFind = ConvertChinaInputString(o_strInputMessage, strFineTxt, '#');
	if(bFind)
	{
		return;
	}	
#endif
}

BOOL CINFGameMainChat::ConvertChinaInputString(char* o_strInputMessage, char* i_strFineTxt, char chCmd)
{
#ifdef LANGUAGE_CHINA	
	char strInputMessageTmp[256];
	char strInputTmp[256];
	memset(strInputMessageTmp, 0x00, 256);
	memset(strInputTmp, 0x00, 256);

	char* pFindChChatting = strstr(o_strInputMessage, i_strFineTxt);
	if(pFindChChatting && (pFindChChatting == o_strInputMessage))
	{
		memset(strInputMessageTmp, 0x00, 256);
		memset(strInputTmp, 0x00, 256);						
		
		strInputMessageTmp[0] = chCmd;
		
		int nFindLen = strlen(i_strFineTxt);
		int nTmpLen = strlen(o_strInputMessage) - nFindLen;
		if(nTmpLen > 0)
		{
			strncpy(strInputTmp, o_strInputMessage + nFindLen, nTmpLen);			
			strcat(strInputMessageTmp, strInputTmp);			
		}
		strncpy(o_strInputMessage, strInputMessageTmp, strlen(strInputMessageTmp)+1);
		return TRUE;
	}	
#endif
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		���� ��ư Ŭ��
/// \author		// 2007-07-04 by bhsohn ���۷����� �߰�
/// \date		2007-06-12 ~ 2007-06-12
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMainChat::OnClickFAQ()
{
	// 2008-10-20 by bhsohn FAQ ��ü ���¿����� �Ⱥ��̰� ����
	if(!g_pGameMain->m_bFAQProsFlag)
	{
		if(g_pTutorial->IsTutorialMode() == TRUE || 
			!g_pShuttleChild->GetIsUseInterface() ||
			g_pGameMain->m_bVOIPFlag == TRUE ||
			g_pD3dApp->m_bChatMode == TRUE ||
			g_pD3dApp->m_dwGameState == _SHOP || 
			g_pGameMain->m_nLeftWindowInfo == LEFT_WINDOW_TRANS ||
			g_pGameMain->m_pTrade->m_bTrading)
		{
			return;
		}
	}
	// end 2008-10-20 by bhsohn FAQ ��ü ���¿����� �Ⱥ��̰� ����

	g_pInterface->SetWindowOrder(WNDGameMainFaq);
	g_pGameMain->m_bFAQProsFlag = !g_pGameMain->m_bFAQProsFlag;
//	if(g_pGameMain->m_bFAQProsFlag)
//	{
//		g_pD3dApp->m_bFixUnitDirMode = TRUE;	// ���� ���� ���� ���
//	}
//	else 
//	{
//		g_pD3dApp->m_bFixUnitDirMode = FALSE;	// ���� ���� ���� ���
//	}	
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-02-27 by bhsohn �Ʒ��� �̵��� ä������ ����
/// \date		2007-06-12 ~ 2007-06-12
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMainChat::GetAllChatList(ChatLine_t pArrChatLine[CHAT_BUFFER_NUMBER])
{
	m_ArrChatTab.GetAllChatList(pArrChatLine);

}
INT CINFGameMainChat::WhisperChatSmallWindowCountPlus()
{
	INT nWindowCnt = m_nSmallWindowCount;
	m_nSmallWindowCount++;
	if(nWindowCnt < 0)
		return 0;
	//DBGOUT("WhisperChatSmallWindowCountPlus(m_nSmallWindowCount = %d)\n",m_nSmallWindowCount);
	return nWindowCnt;
}
INT CINFGameMainChat::WhisperChatSmallWindowCountMinus(INT i_nIndex)
{
	INT nWindowCnt = m_nSmallWindowCount;

	CINFGameMainWisperChat *pWisper = NULL;
	vectorINFGameMainWisperChatPtr::iterator it(m_vectorINFiGameMainWisperChatPtr.begin());
	// 2010. 03. 16 by jskim �Ӹ�â ���� ����
	EnterCriticalSection(&g_pD3dApp->m_cs);
	//end 2010. 03. 16 by jskim �Ӹ�â ���� ����
	while(it != m_vectorINFiGameMainWisperChatPtr.end())
	{
		pWisper = (*it);
		if(pWisper->m_nVectorIndex > i_nIndex)
		{
			pWisper->m_nVectorIndex--;
		}
		it++;		
	}
	// 2010. 03. 16 by jskim �Ӹ�â ���� ����
	LeaveCriticalSection(&g_pD3dApp->m_cs);
	//end 2010. 03. 16 by jskim �Ӹ�â ���� ����

	m_nSmallWindowCount--;
	//DBGOUT("WhisperChatSmallWindowCountMinus(m_nSmallWindowCount = %d)\n",m_nSmallWindowCount);
	return nWindowCnt;
}
///////////////////////////////////////////////////////////////////////////////
/// \fn			DWORD CINFGameMainChat::ChangeChatMode(DWORD i_nChatMode)
/// \brief		Ȱ��ȭ���� ä�� ��带 ����.
/// \author		dgwoo
/// \date		2008-05-09 ~ 2008-05-09
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
DWORD CINFGameMainChat::ChangeChatMode(DWORD i_nChatMode)
{
	DWORD oldChatMode = m_nChatMode;
	char strChatType  = '\0';
	m_nChatMode = i_nChatMode + 1;
	switch(m_nChatMode)
	{
		case CHAT_TAB_ALLUSER:
			break;
		case CHAT_TAB_WAR:
			strChatType = '^';
			break;
		case CHAT_TAB_TRADE:
			strChatType = '$';
			break;
		case CHAT_TAB_MAP:
			strChatType = '!';
			break;
		case CHAT_TAB_GUILD:
			{
				strChatType = '@';
				if(g_pShuttleChild->GetMyShuttleInfo().GuildUniqueNumber == 0 &&
					m_bGuildQuick == FALSE)
				{
					m_bGuildQuick = TRUE;
					char strtemp[SIZE_MAX_ERROR_CHAT_MESSAGE] = {0,};
					wsprintf(strtemp,STRMSG_C_080605_0101,STRMSG_WINDOW_TEXT,STRMSG_WINDOW_TEXT);
					m_ArrChatTabMode[CHAT_TAB_GUILD].PushChatLine(strtemp, COLOR_ITEM);
					m_ArrChatTabMode[CHAT_TAB_GUILD].PushChatLine("  ", COLOR_ITEM);
					m_ArrChatTabMode[CHAT_TAB_GUILD].PushChatLine("  ", COLOR_ITEM);
				}
			}
			break;
		case CHAT_TAB_PARTY:
			{
				strChatType = '#';
				if(g_pShuttleChild->m_pClientParty->IsParty() == FALSE	&&
					m_bPartyQuick == FALSE)
				{
					m_bPartyQuick = TRUE;
					char strtemp[SIZE_MAX_ERROR_CHAT_MESSAGE] = {0,};
					wsprintf(strtemp,STRMSG_C_080605_0100,STRMSG_WINDOW_TEXT,STRMSG_WINDOW_TEXT);
					m_ArrChatTabMode[CHAT_TAB_PARTY].PushChatLine(strtemp, COLOR_ITEM);
					m_ArrChatTabMode[CHAT_TAB_PARTY].PushChatLine("  ", COLOR_ITEM);
					m_ArrChatTabMode[CHAT_TAB_PARTY].PushChatLine("  ", COLOR_ITEM);
				}
			}
			break;
		case CHAT_TAB_ARENA:
			strChatType = '%';
			break;
		case CHAT_TAB_CHATROOM:
			strChatType = '&';
			break;
		default:
			break;

	}
//	if(strChatType != '\0')
	{
		g_pD3dApp->m_inputkey.m_full_str[0] = strChatType;
		g_pD3dApp->m_inputkey.m_str_pos = 1;
		m_strInputMessage[0] = strChatType;
	}

	return oldChatMode;
}
ChatTab_t * CINFGameMainChat::GetChatTabMode()
{
	if(m_nChatMode == CHAT_TAB_ALLUSER)
	{
		return &m_ArrChatTab;
	}
	return &m_ArrChatTabMode[m_nChatMode];
}

void CINFGameMainChat::ActiveChatOption(BOOL i_bActive)
{
	switch(m_nChatMode)
	{
		case CHAT_TAB_TRADE:
			{
				m_bShowMacro = i_bActive;
				if(m_bShowMacro)
				{
					g_pInterface->SetWindowOrder(WNDMacroWnd);
				}
			}
			break;
		case CHAT_TAB_GUILD:
			{
				if(g_pShuttleChild->GetMyShuttleInfo().GuildUniqueNumber != 0)
				{
					g_pGameMain->m_pCommunity->ShowCommunityWindow(TRUE,COMMUNITY_GUILD);
				}
			}
			break;
		case CHAT_TAB_PARTY:
			{
				 if(g_pShuttleChild->m_pClientParty->IsParty() == TRUE)
				 {
					g_pGameMain->m_pCommunity->ShowCommunityWindow(TRUE,COMMUNITY_PARTY);
				 }
			}
			break;
		default:
			break;
	}

	return;
}
void CINFGameMainChat::StartMacro()
{
	m_bMacroIng = TRUE;
	m_nSendMacroNum = 0;

	// 2008-08-18 by bhsohn ��ũ�� �߰� ����
	m_nTransChatCount = CHATMACRO_TRANSCHAT_COUNT;

	int i;
	for(i = 0 ; i < CHAT_MACRO_INPUT_COUNT; i++)
	{
		if(m_sMacroStr[i].bAppl == TRUE)
		{
			m_sMacroStr[i].fTime = 0;// 2012-03-30 by isshin ��ũ�� �ý��� ���� ���� - ��ũ�� �۵��� �ٷ� ���

			// ���� ��ġ ����
			m_nSendMacroNum = i;
			break;
		}
	}
}
void CINFGameMainChat::EndMacro()
{
	m_bMacroIng = FALSE;
	m_nSendMacroNum = 0;
}
void CINFGameMainChat::SetVoiceChatVolum(DWORD i_nVolum)
{// ���� �����ϴ� �Լ��� ��� ȣ���ϸ� �ӵ��� ���� ������  �����Ҽ��ֵ��� ����.
	if(m_fVolumConTimeGap > VOICECHAT_SPK_CONTROL_TIME_GAP)
	{
		m_fVolumConTimeGap = 0;
		g_pGameMain->SetVoiceVolum(i_nVolum);
	}
	m_fVolumConTimeGap += g_pD3dApp->GetElapsedTime();
	m_nVolum = i_nVolum;
}
void CINFGameMainChat::SetChatRoomAct(BOOL i_bActive)
{
	m_pBtnChatMode[ChangeChatButtonNumber(CHAT_TAB_CHATROOM)]->EnableBtn(i_bActive);
}
void CINFGameMainChat::SetChatArenaAct(BOOL i_bActive)
{
	m_pBtnChatMode[ChangeChatButtonNumber(CHAT_TAB_ARENA)]->EnableBtn(i_bActive);
}
void CINFGameMainChat::UpdateVoiceChatType(BYTE i_bVoiceType)
{
	m_pBothGuild->ChangeBoth(TRUE);
	m_pBothChat->ChangeBoth(TRUE);
	m_pBothParty->ChangeBoth(TRUE);
	m_pBothWhisper->ChangeBoth(TRUE);
	switch(i_bVoiceType)
	{
	case VOICE_ONE:
		{
			m_pBothWhisper->ChangeBoth(FALSE);
		}
		break;
	case VOICE_PARTY:
		{
			m_pBothParty->ChangeBoth(FALSE);
			g_pShuttleChild->m_pClientParty->SetNtoNCallState(TRUE);
		}
		break;
	case VOICE_GUILD:
		{
			m_pBothGuild->ChangeBoth(FALSE);
			g_pGameMain->m_pCommunity->GetGuild()->SetNtoNCallState(TRUE);
		}
		break;
	case VOICE_NONE:
		{
			g_pGameMain->SetVOIPSpeaking(FALSE);
		}
		break;
	default:
		break;
	}
	g_pGameMain->SetVoiceType(i_bVoiceType);

}
void CINFGameMainChat::ShowVoiceChatControl(BOOL i_bShow)
{
	m_bShowVoiceChatControl = i_bShow;
	if(m_bShowVoiceChatControl == FALSE)
	{
		return;
	}
	// 2008-10-20 by bhsohn VOIP ���� ����
	//m_nPosVolum = (g_pGameMain->GetVoiceVolum()/100)*67;
	UpdateVoiceVolumScroll();
	g_pInterface->SetWindowOrder(WNDVoiceWnd);
	UpdateVoiceChatType(g_pGameMain->GetVoiceType());
	
}
void CINFGameMainChat::SendVoiceParty()
{
	// 2008-10-14 by bhsohn VOIP����
	if(g_pD3dApp->GetArenaState() == ARENA_STATE_ARENA_GAMING )
	{
		
		// 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���
		
// 		//"�Ʒ��������� �̿��� �� �����ϴ�."
// 		g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080225_0203,COLOR_ERROR);//"�Ʒ��������� �̿��� �� �����ϴ�."

		if( g_pD3dApp->m_ArenaSocketType == CAtumApplication::ARENASOCKET_ARENA )
			g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080225_0203,COLOR_ERROR);//"�Ʒ��������� �̿��� �� �����ϴ�."
		else if( g_pD3dApp->m_ArenaSocketType == CAtumApplication::ARENASOCKET_INFINITY )
			g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_091103_0322,COLOR_ERROR);//"\y���Ǵ�Ƽ �ʵ忡���� ��� �� �� �����ϴ�\y"

		// end 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���

		return;
	}

	if(PopupVOIPError(VOICE_PARTY))
	{
		return;
	}

	if((g_pShuttleChild->m_pClientParty->GetPartyInfo().bPartyType != _PARTYMASTER)
		&& (g_pShuttleChild->m_pClientParty->GetNtoNCallState() == FALSE))
	{
		// 2008-10-20 by bhsohn VOIP ���� ����
		// ���� �����̶�� ������� ������ ��Ű�� ���� ��� �Ұ���
		// ������ ������ ����Ŵ
		if(CHECK_TYPE_VOIP_PARTY != g_pShuttleChild->m_pClientParty->GetVoiceTypePartyMaster())
		{
			// ������� VOIP�� �� Ű���ֳ�?
			return;		
		}
	}
	// end 2008-10-14 by bhsohn VOIP����

	if(g_pGameMain->GetVoiceType() == VOICE_NONE &&
		g_pShuttleChild->m_pClientParty->GetPartyInfo().bPartyType == _PARTYMASTER)
	{
		g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_VOIP_0014, _Q_PARTYMASTER_VOIP);//"��밣 ��ȭ�� �Ͻðڽ��ϱ�?"
		g_pD3dApp->m_VOIPState.bCaller = TRUE;
		g_pD3dApp->m_VOIPState.nVOIPState = _VOIP_TRY_REGISTER;
		// 2005-10-07 by ispark �����ȭ ��ü�� ����
		g_pD3dApp->m_VOIPState.nConnectCount = 50;
	}
	else if(g_pGameMain->GetVoiceType() == VOICE_NONE &&
		g_pShuttleChild->m_pClientParty->GetPartyInfo().bPartyType == _PARTYMEMBER)
	{
		g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_VOIP_0003, _Q_JOIN_PARTY_VOIP);	//"��밣 ��ȭ�� �����Ͻðڽ��ϱ�?"
	}
	else
	{
		if( g_pD3dApp->m_VOIPState.nVOIPState != _VOIP_NOTLOGIN &&
			g_pShuttleChild->m_pClientParty->GetNtoNCallState() == TRUE &&
			g_pShuttleChild->m_pClientParty->GetPartyInfo().bPartyType == _PARTYMASTER)
		{
			g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_VOIP_0015, _Q_PARTY_VOIP_END);//"��밣 ��ȭ�� ���� �Ͻðڽ��ϱ�?"
		}
		else
		{
			if(g_pGameMain->GetVoiceType() == VOICE_ONE)
			{
				g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_VOIP_0011, _Q_VOIP_USING);//"1:1 ������ȭ�� �ϰ� �ֽ��ϴ�"
			}
			else if(g_pGameMain->GetVoiceType() == VOICE_GUILD)
			{
				g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_VOIP_0013, _Q_VOIP_USING);//"���� ������ȭ�� �ϰ� �ֽ��ϴ�"
			}
			else if(g_pGameMain->GetVoiceType() == VOICE_PARTY)
			{
				g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_VOIP_0012, _Q_VOIP_USING);
			}else
			{
				g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_VOIP_0008, COLOR_VOIP,CHAT_TAB_SOUND);
			}
		}
	}
}

void CINFGameMainChat::SendVoiceGuild()
{
	// 2008-02-27 by bhsohn ���� �Ʒ��� ����
	if(g_pD3dApp->GetArenaState() == ARENA_STATE_ARENA_GAMING )
	{
		
		// 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���
		
// 		//"�Ʒ��������� �̿��� �� �����ϴ�."
// 		g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080225_0203,COLOR_ERROR);//"�Ʒ��������� �̿��� �� �����ϴ�."

		if( g_pD3dApp->m_ArenaSocketType == CAtumApplication::ARENASOCKET_ARENA )
			g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080225_0203,COLOR_ERROR);//"�Ʒ��������� �̿��� �� �����ϴ�."
		else if( g_pD3dApp->m_ArenaSocketType == CAtumApplication::ARENASOCKET_INFINITY )
			g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_091103_0322,COLOR_ERROR);//"\y���Ǵ�Ƽ �ʵ忡���� ��� �� �� �����ϴ�\y"

		// end 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���

		return;
	}
	// end 2008-02-27 by bhsohn ���� �Ʒ��� ����
	

	// 2008-10-14 by bhsohn VOIP����
	if(PopupVOIPError(VOICE_GUILD))
	{
		return;
	}
	if((g_pGameMain->m_pCommunity->GetGuild()->GetMyGuildRank() != GUILD_RANK_COMMANDER)
		&& (g_pGameMain->m_pCommunity->GetGuild()->GetNtoNCallState() == FALSE))
	{
		// ���ܿ��� ������ ����Ŵ
		// 2008-10-20 by bhsohn VOIP ���� ����
		// ���� �����̶�� ������� ������ ��Ű�� ���� ��� �Ұ���
		// ������ ������ ����Ŵ
		if(!g_pGameMain->m_pCommunity->GetGuild()->IsVoiceONGuildMaster())
		{
			// �������� VOIP�� �� Ű���ֳ�?
			return;		
		}
		
	}
	// end 2008-10-14 by bhsohn VOIP����
	
	if( g_pD3dApp->m_VOIPState.nVOIPState == _VOIP_NOTLOGIN &&
		g_pGameMain->m_pCommunity->GetGuild()->GetMyGuildRank() == GUILD_RANK_COMMANDER &&
		g_pShuttleChild->m_pClientParty->GetNtoNCallState() == FALSE &&
		g_pGameMain->m_pCommunity->GetGuild()->GetNtoNCallState() == FALSE )
	{
		g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_VOIP_0007, _Q_GUILDMASTER_VOIP,0,0,DELETE_MASSAGEBOX_TIME);//"���� ��ȭ�� �Ͻðڽ��ϱ�?"
		g_pD3dApp->m_VOIPState.bCaller = TRUE;
		g_pD3dApp->m_VOIPState.nVOIPState = _VOIP_TRY_REGISTER;

		// 2008-10-14 by bhsohn VOIP����
		g_pD3dApp->m_VOIPState.nConnectCount = 50;
	}
	else if (g_pGameMain->GetVoiceType() == VOICE_NONE &&
		g_pGameMain->m_pCommunity->GetGuild()->IsGuildMember() == TRUE) 
	{
		g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_VOIP_0005, _Q_JOIN_GUILD_VOIP);
	}
	else if(g_pGameMain->m_pCommunity->GetGuild()->IsGuildMember() == FALSE)
	{
		g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_VOIP_0008, COLOR_VOIP);//"������ �� �� ���� �����Դϴ�."
	} 
	else
	{
		g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_VOIP_0009, COLOR_VOIP);//"�̹� ��ȭ���Դϴ�."
	}
	//bSendChat = TRUE;
}

BOOL CINFGameMainChat::EndVoiceGuild()
{
	if(g_pGameMain->m_pCommunity->GetGuild()->GetNtoNCallState())//������ȭ���ΰ��
	{
		// 2008-10-20 by bhsohn VOIP ���� ����
		g_pGameMain->m_pCommunity->GetGuild()->ReleaseVOIPGuildInfo();	// IM�������� ���� ������ �ʱ�ȭ ����
		// end 2008-10-20 by bhsohn VOIP ���� ����

		COPYDATASTRUCT	copyData;
		memset(&copyData, 0x00, sizeof(COPYDATASTRUCT));
		AV_MSG_WM_COPYDATA voIP(_NtoNCall, AV_MT_UNREGISTER, 0);
		copyData.dwData = (DWORD)voIP;
		copyData.lpData = NULL;
		copyData.cbData = 0;
		::SendMessage(g_pD3dApp->m_VOIPState.m_hWndAtumVoIPClient, WM_COPYDATA, (WPARAM)g_pD3dApp->GetHwnd(), (LPARAM)&copyData);
		g_pD3dApp->m_VOIPState.nVOIPState = _VOIP_NOTLOGIN;
		g_pD3dApp->m_VOIPState.bCaller = FALSE;
		g_pD3dApp->m_VOIPState.nCallState = _CALLSTATE_1TO1;
		g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_VOIP_0006,COLOR_VOIP);
		g_pGameMain->m_pCommunity->GetGuild()->SetNtoNCallState(FALSE);
		UpdateVoiceChatType(VOICE_NONE);

		// 2008-10-20 by bhsohn VOIP ���� ����


		return TRUE;
	}
	return FALSE;
}
BOOL CINFGameMainChat::EndVoiceParty()
{
	if(g_pShuttleChild->m_pClientParty->GetNtoNCallState())//�����ȭ���ΰ��
	{
		// 2008-10-20 by bhsohn VOIP ���� ����
		//g_pShuttleChild->m_pClientParty->InitMyShuttlemVoipType();
		//g_pGameMain->ReleaseVOIPMode();	// ����ũ ������ ����
		g_pShuttleChild->m_pClientParty->ReleaseVOIPAllUserInfo();	// IM�������� ���� ������ �ʱ�ȭ ����
		// end 2008-10-20 by bhsohn VOIP ���� ����

		COPYDATASTRUCT	copyData;
		memset(&copyData, 0x00, sizeof(COPYDATASTRUCT));
		AV_MSG_WM_COPYDATA voIP(_NtoNCall, AV_MT_UNREGISTER, 0);
		copyData.dwData = (DWORD)voIP;
		copyData.lpData = NULL;
		copyData.cbData = 0;
		::SendMessage(g_pD3dApp->m_VOIPState.m_hWndAtumVoIPClient, WM_COPYDATA, (WPARAM)g_pD3dApp->GetHwnd(), (LPARAM)&copyData);
		g_pD3dApp->m_VOIPState.nVOIPState = _VOIP_NOTLOGIN;
		g_pD3dApp->m_VOIPState.bCaller = FALSE;
		g_pD3dApp->m_VOIPState.nCallState = _CALLSTATE_1TO1;
		g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_VOIP_0004,COLOR_VOIP);
		g_pGameMain->m_pCommunity->GetGuild()->SetNtoNCallState(FALSE);
		UpdateVoiceChatType(VOICE_NONE);

		return TRUE;
	}
	return FALSE;
}

BOOL CINFGameMainChat::IsChatingMode()
{
	return m_bChatMode;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-10-20 by bhsohn VOIP ���� ����
/// \date		2008-10-20 ~ 2008-10-20
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CINFGameMainChat::PopupVOIPError(BYTE byRqVoiceType)
{
	BYTE byVoiceType = g_pGameMain->GetVoiceType();		
	if( VOICE_NONE == byVoiceType)
	{
		return FALSE;
	}
	else if(byVoiceType == byRqVoiceType)
	{
		return FALSE;
	}

	switch(byVoiceType)
	{
	case VOICE_ONE:
		{
			g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_VOIP_0011, _Q_VOIP_USING);//"1:1 ������ȭ�� �ϰ� �ֽ��ϴ�"
		}
		break;
	case VOICE_GUILD:
		{
			g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_VOIP_0013, _Q_VOIP_USING);//"���� ������ȭ�� �ϰ� �ֽ��ϴ�"
		}
		break;
	case VOICE_PARTY:
		{
			g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_VOIP_0012, _Q_VOIP_USING);
		}
		break;
	default:
		{
			//g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_VOIP_0008, COLOR_VOIP,CHAT_TAB_SOUND);
			return FALSE;
		}
		break;
	}	
	return TRUE;
}
///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-10-20 by bhsohn VOIP ���� ����
/// \date		2008-10-20 ~ 2008-10-20
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMainChat::UpdateVoiceVolumScroll()
{
	float fVolum = ((float)g_pGameMain->GetVoiceVolum()/100.0f)*67.0f;
	m_nPosVolum = (int)fVolum;
	if(m_nPosVolum > VOICECHAT_SPK_W)
	{
		m_nPosVolum = VOICECHAT_SPK_W;
	}
	else if(m_nPosVolum < 0)
	{
		m_nPosVolum = 0;
	}
}


// 2009. 02. 03 by ckPark ä��â �������̽� ũ�� ����
stcuctRateRect CINFGameMainChat::GetChatWndRect(void)
{
	stcuctRateRect	stRateRect;
	memset(&stRateRect, 0x00, sizeof(stcuctRateRect));
	
	stRateRect.fRateWidth	= m_nChatBoxWidth;
	stRateRect.fRateHeight	= m_nChatBoxHeight;
	
	return stRateRect;	
}
// end 2009. 02. 03 by ckPark ä��â �������̽� ũ�� ����


// 2008. 12. 29 by ckPark ä��â ����ȭ
///////////////////////////////////////////////////////////////////////////////
/// \fn		: CINFGameMainChat::BuildCulledString
/// \brief	: �� ���κ��� �߷��� ���ڿ��� ����
/// \author	: ckPark
/// \date	: 29:12:2008   20:55
/// \warning: 
/// \param	: void
/// \return	: void
///////////////////////////////////////////////////////////////////////////////
void	CINFGameMainChat::BuildCulledString( void )
{
	// �ϴ� ����Ʈ �ʱ�ȭ
	m_listCulledString.clear();

	// �ִ� ������ ���μ� ���
	int nMaxRenderLineCounts	= ( m_nChatBoxHeight - CHATBOX_IMAGE_GAB_HEITHT_TOP )
								  / CHAT_FONT_LINE_HEIGHT;

	// ���� �� ������
	ChatTab_t *pCurChatTab = GetChatTabMode();
	// �ǿ� ����� ���ڿ��� ���� ��� ����
	if(0 >= pCurChatTab->m_nStoredLineCounts)
		return;
	
	int nRenderIndex				= pCurChatTab->m_nRenderStartIndex;
	int nRenderedLineCounts			= 0;
	
	vector<CD3DHanFont*>::iterator it = m_vecFontLine.begin();
	while(it != m_vecFontLine.end())
	{
		CD3DHanFont* pFont = *it;
		
		
		// �� ������ ©�� ���ͷ� ������ �����Ѵ�
		vector<string> vecChatMessage;
		STRING_CULL(pCurChatTab->GetChatLine(nRenderIndex), CHAT_STRING_LENGTH, &vecChatMessage, pFont);
		m_listCulledString.push_back( vecChatMessage );
		
		nRenderedLineCounts += vecChatMessage.size();
		
		// �����ѵ��� �ִ� ������ ���� �Ѿ�� ���� Ż��
		if(nRenderIndex == pCurChatTab->m_nStoreEndIndex
		   || nMaxRenderLineCounts <= nRenderedLineCounts)
			break;
		
		// ����ť �ε��� ����
		if(--nRenderIndex < 0)
			nRenderIndex = CHAT_BUFFER_NUMBER - 1;
		++it;			
	}
}
// end 2008. 12. 29 by ckPark ä��â ����ȭ

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2009-03-18 by bhsohn ä��â Ŀ�� �̵� �ý��� �߰�
/// \date		2009-03-18 ~ 2009-03-18
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int CINFGameMainChat::OnKeyUpFunc(WPARAM wParam, LPARAM lParam)
{
	if(!IsChatingMode()) 
	{
		return INF_MSGPROC_NORMAL;
	}
	char text[SIZE_MAX_STRING_1024];
	ZERO_MEMORY(text);	
	
	switch(wParam)
	{		
	case VK_SHIFT:
		{
			m_bShiftClick = FALSE;			
			//DBGOUT("m_bCaretCursel = FALSE; \n");
		}
		break;
	case VK_CONTROL:
		{
			int strlenComp = g_input.GetComp(text, sizeof(text));
			if(strlenComp > 0)
			{
				// �������̳� ����
				return INF_MSGPROC_NORMAL;
			}
			m_bControlCursel = FALSE;

		}
		break;
	}
	return INF_MSGPROC_NORMAL;

}
///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2009-03-18 by bhsohn ä��â Ŀ�� �̵� �ý��� �߰�
/// \date		2009-03-18 ~ 2009-03-18
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int CINFGameMainChat::OnKeyDownCursel(WPARAM wParam, LPARAM lParam)
{
	if(!IsChatingMode()) 
	{
		return INF_MSGPROC_NORMAL;
	}
	switch(wParam)
	{	  
#ifndef C_USER_CTRL_KEY_LOCK
	case VK_CONTROL:
		{
			USHORT nRace = g_pD3dApp->m_pShuttleChild->GetMyShuttleInfo().Race;

// 2012-11-21 by mspark, ������ ����, �ٿ��ֱ� ���
#ifdef C_ADMINISTRATOR_COPYPASTE_PERMISSION
			if(COMPARE_RACE(nRace,RACE_OPERATION) || COMPARE_RACE(nRace,RACE_GAMEMASTER))
			{
				m_bControlCursel = TRUE;
				return INF_MSGPROC_BREAK;
			}
#else
			// 2010. 05. 25 by jskim �ٿ��ֱ�, ����, �߶󳻱� �Ϲݰ��� ���
// 			if(COMPARE_RACE(nRace,RACE_OPERATION) || COMPARE_RACE(nRace,RACE_GAMEMASTER))
// 			{
			//end 2010. 05. 25 by jskim �ٿ��ֱ�, ����, �߶󳻱� �Ϲݰ��� ���
			// 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
			// �����ڸ� Ctrl��� Ű��
				m_bControlCursel = TRUE;
			//DBGOUT("m_bControlCursel = TRUE; \n");
				return INF_MSGPROC_BREAK;			
//			}
			//if(COMPARE_RACE(nRace,RACE_OPERATION) || COMPARE_RACE(nRace,RACE_GAMEMASTER))
 			//if(COMPARE_RACE(nRace,RACE_OPERATION))
 			//{
				// �����ڸ� Ctrl��� Ű��
				m_bControlCursel = TRUE;
				//DBGOUT("m_bControlCursel = TRUE; \n");
 				//return INF_MSGPROC_BREAK;			
 			//}
			// end 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
			
			
			return INF_MSGPROC_BREAK;
#endif
// end 2012-11-21 by mspark, ������ ����, �ٿ��ֱ� ���
		}
		break;
#endif

	
	case VK_SHIFT:
		{
			if(INF_MSGPROC_BREAK == OnKeyDownFunc(wParam, lParam))
			{
				return INF_MSGPROC_BREAK;
			}
			return INF_MSGPROC_NORMAL;
		}
		break;
	}
	char text[SIZE_MAX_STRING_1024];
	ZERO_MEMORY(text);
	
	int strlenComp = g_input.GetComp(text, sizeof(text));
	if(strlenComp > 0)
	{
		// �������̳� ����
		return INF_MSGPROC_NORMAL;
	}
// 	if(VK_LSHIFT == lParam)
// 	{
// 		int kk =0;
// 	}
	//DBGOUT("OnKeyDownCursel w[%x] l[%x]\n", wParam, lParam);

	switch(wParam)
	{
	case VK_LEFT:
	case VK_RIGHT:
	case VK_HOME:		
	case VK_END:		
		{
			if(!m_bShiftClick)
			{
				// ����Ʈ�� Ŭ�� �ȵǾ��ִ�.
				m_bCaretCursel = FALSE;
			}
			else 
			{
				// ����Ʈ�� Ŭ�� �Ǿ��ִ�.
				m_bCaretCursel = TRUE;
			}
			return OnKeyDownArrow(wParam, lParam);
		}
		break;
	case VK_BACK:
	case VK_DELETE:	
		{
			// 2010. 02. 23 by jskim ä�ù��� ���� �� ����ȭ
			// 			if(!m_bShiftClick)
			// 			{
			// 				// ����Ʈ�� Ŭ�� �ȵǾ��ִ�.
			// 				m_bCaretCursel = FALSE;
			// 			}
			// 			// 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
			// 			else 
			// 			{
			// 				// ����Ʈ�� Ŭ�� �Ǿ��ִ�.
			// 				m_bCaretCursel = TRUE;
			// 			}
			// 			// end 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
			//end 2010. 02. 23 by jskim ä�ù��� ���� �� ����ȭ
			return OnKeyDownFunc(wParam, lParam);
		}
		break;	
	case 'c':
	case 'C':
		{
			if(m_bControlCursel)
			{
				char chCurselSting[SIZE_MAX_CHAT_MESSAGE];
				ZERO_MEMORY(chCurselSting);
				GetCurselString(chCurselSting);
				if(strlen(chCurselSting) > 0)
				{
					SetClipBoard(chCurselSting);
					// 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
					m_ptSelCurselPos.x = GetStringBuffLen(m_strPreBackupMessage);
					// end 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
				}
				// 2010. 02. 23 by jskim ä�ù��� ���� �� ����ȭ
				m_bCaretCursel = FALSE;
				//end 2010. 02. 23 by jskim ä�ù��� ���� �� ����ȭ
				return INF_MSGPROC_BREAK;
			}
		}
		break;
	case 'a':
	case 'A':
		{
			if(m_bControlCursel && strlen(m_strBkInputMessage) > 0 )
			{
				m_bCaretCursel = TRUE;

				// 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
				// ä�ø�带 ����� �� ����
// 				m_ptCurselPos.x = m_ptCurselPos.y = 0;
// 				m_ptSelCurselPos.x = GetStringBuffLen(m_strBkInputMessage);
// 				
// 				memset(m_strPreBackupMessage, 0x00, SIZE_MAX_CHAT_MESSAGE);		// IME�ʱ�ȭ ���� ���� ������ �ִ´�.
// 				memset(m_strNextBackupMessage, 0x00, SIZE_MAX_CHAT_MESSAGE);	// IME�ʱ�ȭ ���� ���� ������ �ִ´�.	
// 				
// 				strncpy(m_strNextBackupMessage, m_strBkInputMessage, (SIZE_MAX_CHAT_MESSAGE));
// 				
// 				g_pD3dApp->CleanText();
// 				
// 				// ���� ���� �ʱ�ȭ
// 				SetChatMsgBuff(g_pD3dApp->m_inputkey.m_full_str);			
// 				
// 				// ������ ���ۿ� ����
// 				strncpy(m_strInputMessage, m_strBkInputMessage, SIZE_MAX_CHAT_MESSAGE);
				

				if(ChatModeChack(m_strBkInputMessage[0]))
				{
					m_ptSelCurselPos.x = m_ptSelCurselPos.y = GetStringBuffPos(m_strBkInputMessage,1);
				}
				else
				{
					m_ptSelCurselPos.x = m_ptSelCurselPos.y = 0;
				}
				m_ptCurselPos.x = GetStringBuffLen(m_strBkInputMessage);
				// end 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����

				memset(m_strPreBackupMessage, 0x00, SIZE_MAX_CHAT_MESSAGE);		// IME�ʱ�ȭ ���� ���� ������ �ִ´�.
				memset(m_strNextBackupMessage, 0x00, SIZE_MAX_CHAT_MESSAGE);	// IME�ʱ�ȭ ���� ���� ������ �ִ´�.	

				// 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
				strncpy(m_strPreBackupMessage, m_strBkInputMessage, (SIZE_MAX_CHAT_MESSAGE));
				// end 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
			
				g_pD3dApp->CleanText();

				// 2010. 02. 23 by jskim ä�ù��� ���� �� ����ȭ
				SetChatMsgBuff(g_pD3dApp->m_inputkey.m_full_str);			
				//end 2010. 02. 23 by jskim ä�ù��� ���� �� ����ȭ				
				return INF_MSGPROC_BREAK;
			}
		}
		break;
		// 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
		// �߶󳻱� ��� ����
	case 'X':
	case 'x':
		{
			if(m_bControlCursel)
			{
				char chCurselSting[SIZE_MAX_CHAT_MESSAGE];
				ZERO_MEMORY(chCurselSting);
				GetCurselString(chCurselSting);
				if(strlen(chCurselSting) > 0)
				{
					SetClipBoard(chCurselSting);
					
					if(m_bCaretCursel==TRUE)
					{
					// 2010. 02. 23 by jskim ä�ù��� ���� �� ����ȭ
// 						if(m_ptSelCurselPos.x != -1)
// 						{
// 							int  chLenTmp=0;
// 							chLenTmp = m_ptCurselPos.x-m_ptSelCurselPos.x;						
// 							BlockCleanChat(chLenTmp);						
// 						}
						BlockCleanChat(m_ptCurselPos.x,m_ptSelCurselPos.x);
						m_bCaretCursel = FALSE;
					//end 2010. 02. 23 by jskim ä�ù��� ���� �� ����ȭ
					}
						
					
				
				}
				return INF_MSGPROC_BREAK;
			}
		}
		break;
		// end 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
	case 'v':
	case 'V':
		{
			int nIMELen	 = GetStringBuffLen(g_pD3dApp->m_inputkey.m_full_str);
			
			// 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
			// �� ���� ���¿��� �ٸ� ���ڵ� �Էµǵ��� ����
// 			if(m_bCaretCursel)
// 			{
// 				return INF_MSGPROC_NORMAL;
// 			}
			if(m_bControlCursel)
			{	
				// ������ ����
				if(m_bCaretCursel==TRUE)
				{
					// 2010. 02. 23 by jskim ä�ù��� ���� �� ����ȭ
// 					if(m_ptSelCurselPos.x != -1)
// 					{
// 						int  chLenTmp=0;
// 						chLenTmp = m_ptCurselPos.x-m_ptSelCurselPos.x;						
// 						BlockCleanChat(chLenTmp);	
						BlockCleanChat(m_ptCurselPos.x, m_ptSelCurselPos.x);
						//end 2010. 02. 23 by jskim ä�ù��� ���� �� ����ȭ
				}			
		  	     	// end 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����		
				if(nIMELen	>0)
				{
					//return INF_MSGPROC_NORMAL;
					g_pD3dApp->CleanText(); // IME���� �ʱ�ȭ
				}
				// Ŀ���� �������� ��������
				char chCurselSting[SIZE_MAX_CHAT_MESSAGE];
				ZERO_MEMORY(chCurselSting);
				
				// 2010. 02. 23 by jskim ä�ù��� ���� �� ����ȭ
				// 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
				// ���õ� Ŀ�� �ʱ�ȭ 
				//m_ptSelCurselPos.x = -1;
				// end 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
				//end 2010. 02. 23 by jskim ä�ù��� ���� �� ����ȭ
				PasteFromClipBoard(chCurselSting, SIZE_MAX_CHAT_MESSAGE-1);					
				if(strlen(chCurselSting) <= 0)
				{
					return INF_MSGPROC_NORMAL;
				}
				// 2010. 02. 23 by jskim ä�ù��� ���� �� ����ȭ
				int nStartPos = GetStringBuffPos(m_strBkInputMessage, m_ptCurselPos.x);
								
				if(-1 == nStartPos)
				{
					return INF_MSGPROC_NORMAL;
				}
						
// 				char chTmp[SIZE_MAX_CHAT_MESSAGE];
// 				ZERO_MEMORY(chTmp);
		
				if(nStartPos > 0)
				{
					strncpy(m_strPreBackupMessage, m_strBkInputMessage, nStartPos);
				}
				// 2010. 02. 23 by jskim ä�ù��� ���� �� ����ȭ
// 				else
// 				{
// 					// 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
// 					//m_strPreBackupMessage[0] = NULL;
// 					if(ChatModeChack(m_strInputMessage[0]))
// 					{	
// 						strncpy(m_strPreBackupMessage,m_strInputMessage,SIZE_MAX_CHAT_MESSAGE);					
// 					}
// 					else
// 					{
// 						strncpy(m_strPreBackupMessage, m_strBkInputMessage, nStartPos);
// 					}
// 					// end 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
// 				}
// 
// 				if((strlen(m_strPreBackupMessage)+strlen(chCurselSting)) < SIZE_MAX_CHAT_MESSAGE )
// 				{
// 					strcat(m_strPreBackupMessage, chCurselSting);
// 				}
// 				
// 				strcpy(m_strNextBackupMessage, &m_strBkInputMessage[nStartPos]);
// 				
// 				// ���� ���� �ʱ�ȭ
// 				SetChatMsgBuff(g_pD3dApp->m_inputkey.m_full_str);
// 				
// 				// 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
// 				// ���õ� Ŀ�� ��ġ �޾ƿ���
// 				m_ptCurselPos.x = GetStringBuffLen(m_strPreBackupMessage);
// 				// end 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
// 				// ������ ���ۿ� ����
// 				strncpy(m_strInputMessage, m_strBkInputMessage, SIZE_MAX_CHAT_MESSAGE);
// 				if(ChatModeChack(m_strInputMessage[0]) != ChatModeChack(m_strPreBackupMessage[0]))
// 				{	
// 					char chrtmp[256];
// 					memset(chrtmp,0x00,256);
// 					wsprintf(chrtmp,"%c%s",m_strInputMessage[0],m_strPreBackupMessage);
// 					strcpy(m_strPreBackupMessage, chrtmp);
// 				}
				int mLen = strlen(m_strPreBackupMessage) + strlen(chCurselSting) + strlen(m_strNextBackupMessage);
				if( mLen < SIZE_MAX_CHAT_MESSAGE )
				{
					strcat(m_strPreBackupMessage, chCurselSting);
				}
				else
				{
					if(strlen(m_strPreBackupMessage) + strlen(chCurselSting) < SIZE_MAX_CHAT_MESSAGE)
					{
						strcat(m_strPreBackupMessage, chCurselSting);
					}
					else
					{
						int nFindLen = GetStringBuffLen(chCurselSting);
						char chrtmp[256];
						for(int i = 1; i <= nFindLen; i++)
						{	
							memset(chrtmp,0x00,256);
							int nFindPos = GetStringBuffPos(chCurselSting, nFindLen - i);							
							strncpy(chrtmp, chCurselSting ,nFindPos);
							if(strlen(m_strPreBackupMessage) + strlen(chrtmp) < SIZE_MAX_CHAT_MESSAGE)
							{
								strcat(m_strPreBackupMessage, chrtmp);
								m_ptCurselPos.x += GetStringBuffLen(chrtmp);
								break;
							}
						}
					}
					if(strlen(m_strPreBackupMessage) + strlen(m_strNextBackupMessage) >= SIZE_MAX_CHAT_MESSAGE)
					{
						int nFindLen = GetStringBuffLen(m_strNextBackupMessage);
						char chrtmp[256];
						
						for(int i = 1; i <= nFindLen; i++)
						{	
							memset(chrtmp,0x00,256);
							int nFindPos = GetStringBuffPos(m_strNextBackupMessage, nFindLen - i);							
							strncpy(chrtmp, m_strNextBackupMessage ,nFindPos);
							if(strlen(m_strPreBackupMessage) + strlen(chrtmp) < SIZE_MAX_CHAT_MESSAGE)
							{
								strcpy(m_strNextBackupMessage, chrtmp);
								m_ptCurselPos.x += GetStringBuffLen(chrtmp);
								break;
							}
						}
					}
				}
				//end 2010. 02. 23 by jskim ä�ù��� ���� �� ����ȭ
				return INF_MSGPROC_BREAK;
			}
			
		}
		break;
	}
	return INF_MSGPROC_NORMAL;

}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		ȭ��ǥ Ŭ��
/// \author		// 2009-03-18 by bhsohn ä��â Ŀ�� �̵� �ý��� �߰�
/// \date		2009-03-18 ~ 2009-03-18
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int CINFGameMainChat::OnKeyDownArrow(WPARAM wParam, LPARAM lParam)
{		
	switch (wParam)
	{
	case VK_LEFT:
		{		
// 			if(m_bCaretCursel 
// 				&& (m_ptSelCurselPos.x == m_ptCurselPos.x) 
// 				&& (m_ptSelCurselPos.y == m_ptCurselPos.y))
// 			{
// 				// ó�� Ŀ�� ����
// 				m_ptSelCurselPos.x++;
// 
// 				int nStrLen = GetStringBuffLen(m_strBkInputMessage)+1;
// 				if(m_ptSelCurselPos.x > nStrLen)
// 				{
// 					m_ptSelCurselPos.x = nStrLen;
// 				}			
// 				
// 			}
			// 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
			// ä�� ��� ���ڷ� �̵� ���ϰ� �Ѵ�
			if(ChatModeChack(m_strBkInputMessage[0]) && m_ptCurselPos.x < 2)
			{
				m_ptCurselPos.x = 1;
			}
			else
			{
				m_ptCurselPos.x --;			
			}
			// Ŀ�� ��ġ ����(WM_CHAR�Լ��� �̵���)			
// 			int nIMELen	 = GetStringBuffLen(g_pD3dApp->m_inputkey.m_full_str);
// 			if(nIMELen > 0)
// 			{
// 				m_ptCurselPos.x += nIMELen;
// 			}
			// end 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
			if(m_ptCurselPos.x < 0)
			{
				m_ptCurselPos.x = 0;
			}
		}
		break;
	case VK_RIGHT:
		{
			int nStrLen = GetStringBuffLen(m_strBkInputMessage);
// 			// 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
// 			if(m_ptCurselPos.x <= nStrLen - 1 )
// 			{
// 				if(2 != nStrPos ||
// 					nStrCusPos + nStrPos < SIZE_MAX_CHAT_MESSAGE-1)
// 				{	
// 						int aa = GetStringBuffPos(m_strBkInputMessage,nStrLen);
// 						m_strBkInputMessage[aa+1]='\0';
						m_ptCurselPos.x++;		
// 				}
// 			}
			// Ŀ���� ������ ��ġ�� �Ѿ��� ��� �ڽ��� Ŀ�� ��ġ�� ������Ʈ �Ѵ�.			
		//	int nStrPos = GetStringBuffPos(m_strBkInputMessage, nStrLen - 1);
			
		//	char nChar[SIZE_MAX_CHAT_MESSAGE];
			//strcpy(nChar,&m_strBkInputMessage[nStrPos]);			
			
// 			if(0 > nChar[0] &&
// 				GetStringBuffPos(m_strBkInputMessage, m_ptCurselPos.x) >=  GetStringBuffPos(m_strBkInputMessage, nStrLen - 1) )
// 			{
// 				if(strlen(m_strBkInputMessage) < SIZE_MAX_CHAT_MESSAGE - 1)
// 				{
// 					m_ptCurselPos.x++;
// 				}
// 				else
// 				{
// 					m_ptCurselPos.x = nStrLen - 1;
// 				}
// 			}
// 			else if(m_ptCurselPos.x < nStrLen)
// 			{
// 				m_ptCurselPos.x++;
// 			}
// 		}
			
// 			if(strlen(m_strNextBackupMessage) > 0)
// 			{
// 				int nIMELen	 = GetStringBuffLen(g_pD3dApp->m_inputkey.m_full_str);
// 				if(nIMELen > 0)
// 				{
// 					m_ptCurselPos.x += nIMELen;
// 				}
// 			}
			// end 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
			if(m_ptCurselPos.x > nStrLen)
			{
				m_ptCurselPos.x = nStrLen;
			}			
		}			
		break;	
	case VK_HOME:		
		{
			// 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
			// ä�� ��� ���ڷ� Ŀ���� �̵� ���ϰ� �Ѵ�.
			if(ChatModeChack(m_strBkInputMessage[0]))
			{
				m_ptCurselPos.x = GetStringBuffPos(m_strBkInputMessage,1);	
			}
			else
			{
				m_ptCurselPos.x = 0;		
			}
			// ä�� ��� ���ڷ� Ŀ���� �̵� ���ϰ� �Ѵ�.
			// end 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
		}
		break;
	case VK_END:		
		{
			int nStrLen = GetStringBuffLen(m_strBkInputMessage);
			// 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
			//m_ptCurselPos.x = nStrLen;
  			// Ŀ���� �ǳ����� �̵���ų �� ������ ������ ���� �����Ⱚ�� ��������� Ŀ���� �� ������ �̵���Ų��.
			
// 			int nStrCusPos = GetStringBuffPos(m_strBkInputMessage, m_ptCurselPos.x);
// 
// 			if(m_ptCurselPos.x < nStrLen - 1 )
// 			{
// 				if(strlen(m_strBkInputMessage) == SIZE_MAX_CHAT_MESSAGE-1)
// 				{	
// 					m_ptCurselPos.x = nStrLen - 1;		
// 				}
// 				else
				{
					m_ptCurselPos.x = nStrLen ;	
				}
//			}
// 			int nStrPos = GetStringBuffPos(m_strBkInputMessage, nStrLen - 1);
// 			
// 			char nChar[SIZE_MAX_CHAT_MESSAGE];
// 			strcpy(nChar,&m_strBkInputMessage[nStrPos]);			
// 			
// 			if(0 > nChar[0] &&
// 				GetStringBuffPos(m_strBkInputMessage, m_ptCurselPos.x) >=  GetStringBuffPos(m_strBkInputMessage, nStrLen - 1) )
// 			{
// 				int aa = strlen(m_strBkInputMessage);
// 				if(strlen(m_strBkInputMessage) < SIZE_MAX_CHAT_MESSAGE-1)
// 				{
// 					m_ptCurselPos.x = nStrLen;
// 				}
// 				else
// 				{
// 					m_ptCurselPos.x = nStrLen - 1;
// 				}
// 				
// 			}
// 			else if(m_ptCurselPos.x < nStrLen)
// 			{
// 				m_ptCurselPos.x = nStrLen;
// 			}			
 		}
		// end 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
		break;
	default:
		{
			return INF_MSGPROC_NORMAL;
		}
		break;
	}
	
// 	DBGOUT("m_ptCurselPos[%d][%d] m_ptSelCurselPos[%d][%d] \n", m_ptCurselPos.x, m_ptCurselPos.y, 
// 														m_ptSelCurselPos.x, m_ptSelCurselPos.y);

	int nFindPos = GetStringBuffPos(m_strBkInputMessage, m_ptCurselPos.x);
	
	if(-1 == nFindPos)
	{
		return INF_MSGPROC_NORMAL;		
	}
	memset(m_strPreBackupMessage, 0x00, SIZE_MAX_CHAT_MESSAGE);		// IME�ʱ�ȭ ���� ���� ������ �ִ´�.
	memset(m_strNextBackupMessage, 0x00, SIZE_MAX_CHAT_MESSAGE);	// IME�ʱ�ȭ ���� ���� ������ �ִ´�.	

	if(nFindPos > 0)
	{
		strncpy(m_strPreBackupMessage, m_strBkInputMessage, nFindPos);
	}
	strcpy(m_strNextBackupMessage, &m_strBkInputMessage[nFindPos]);

	g_pD3dApp->CleanText(); // IME���� �ʱ�ȭ


	// ������ ���ۿ� ����
	strncpy(m_strInputMessage, m_strBkInputMessage, SIZE_MAX_CHAT_MESSAGE);
	
	return INF_MSGPROC_BREAK;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		Back, delŰ �Է�
/// \author		// 2009-03-18 by bhsohn ä��â Ŀ�� �̵� �ý��� �߰�
/// \date		2009-03-18 ~ 2009-03-18
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int CINFGameMainChat::OnKeyDownFunc(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case VK_BACK:
		{
			// 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
			// ������ ���� ����
			// 			if((0 == strlen(g_pD3dApp->m_inputkey.m_full_str))
			// 				&& (strlen(m_strPreBackupMessage) > 0))
			// 			{
			// 				int nStrLen = GetStringBuffLen(m_strPreBackupMessage)-1;
			// 				if(nStrLen >= 0)
			// 				{
			// 					int nFindBackPos = GetStringBuffPos(m_strPreBackupMessage, nStrLen);
			// 					if(nFindBackPos >= 0)
			// 					{
			// 						charF chTmp[SIZE_MAX_CHAT_MESSAGE];
			// 						ZERO_MEMORY(chTmp);
			// 						if(nFindBackPos > 0)
			// 						{
			// 							strncpy(chTmp, m_strPreBackupMessage, nFindBackPos);
			// 						}
			// 						strncpy(m_strPreBackupMessage, chTmp, SIZE_MAX_CHAT_MESSAGE);
			// 						
			// 						// ���� ���� �ʱ�ȭ
			// 						SetChatMsgBuff(g_pD3dApp->m_inputkey.m_full_str);
			// 						
			// 						m_ptCurselPos.x = GetStringBuffLen(m_strPreBackupMessage);
			// 
			// 						// ������ ���ۿ� ����
// 						strncpy(m_strInputMessage, m_strBkInputMessage, SIZE_MAX_CHAT_MESSAGE);
			int  chLenTmp=0;
			char chTmp[SIZE_MAX_CHAT_MESSAGE];
			ZERO_MEMORY(chTmp);
			
			if(0 == strlen(g_pD3dApp->m_inputkey.m_full_str))
			{  
				// 2010. 02. 23 by jskim ä�ù��� ���� �� ����ȭ
// 				if(m_ptSelCurselPos.x != -1)
// 				{   // �� �۾� 
// 					chLenTmp = m_ptCurselPos.x-m_ptSelCurselPos.x;
// 					BlockCleanChat(chLenTmp);
// 				}
				if(m_bCaretCursel == TRUE)
				{   // �� �۾� 					
					BlockCleanChat(m_ptCurselPos.x, m_ptSelCurselPos.x);
				}
				//end 2010. 02. 23 by jskim ä�ù��� ���� �� ����ȭ
				else
				{
					// ���� ������ �۾�
					int nStrLen = GetStringBuffLen(m_strPreBackupMessage)-1;
 					if(nStrLen >= 0)
 					{
 						int nFindBackPos = GetStringBuffPos(m_strPreBackupMessage, nStrLen);
 						if(nFindBackPos >= 0)
 						{
	 						char chTmp[SIZE_MAX_CHAT_MESSAGE];
 							ZERO_MEMORY(chTmp);
 							if(nFindBackPos > 0)
 							{
 								strncpy(chTmp, m_strPreBackupMessage, nFindBackPos);
 							}
	 						strncpy(m_strPreBackupMessage, chTmp, SIZE_MAX_CHAT_MESSAGE);
 							// 2010. 02. 23 by jskim ä�ù��� ���� �� ����ȭ
//  							SetChatMsgBuff(g_pD3dApp->m_inputkey.m_full_str);
//   							m_ptCurselPos.x = GetStringBuffLen(m_strPreBackupMessage);
//   							strncpy(m_strInputMessage, m_strBkInputMessage, SIZE_MAX_CHAT_MESSAGE);
							// end 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
							//end 2010. 02. 23 by jskim ä�ù��� ���� �� ����ȭ
						}
						return INF_MSGPROC_BREAK;
						
					}
				}				
			}
			return INF_MSGPROC_NORMAL;			
		}
		break;
	case VK_DELETE:
		{
			// 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
			// ������ ���� ����
// 			int nStringLen = GetStringBuffLen(m_strBkInputMessage);	
// 			if((m_ptCurselPos.x != nStringLen)			// ������ ��ġ��?
// 				&& (0 == strlen(g_pD3dApp->m_inputkey.m_full_str))
// 				&& (strlen(m_strNextBackupMessage) > 0))
// 			{
// 				int nFindNevtPos = GetStringBuffPos(m_strNextBackupMessage, 1);	// ù��° ������ ���۸� �����´�			
// 				if(nFindNevtPos >= 0)
// 				{
// 					char chTmp[SIZE_MAX_CHAT_MESSAGE];
// 					ZERO_MEMORY(chTmp);
// 					
// 					strcpy(chTmp, &m_strNextBackupMessage[nFindNevtPos]);
// 					strncpy(m_strNextBackupMessage, chTmp, SIZE_MAX_CHAT_MESSAGE);
// 					
// 					// ���� ���� �ʱ�ȭ
// 					SetChatMsgBuff(g_pD3dApp->m_inputkey.m_full_str);			
// 					
// 					// ������ ���ۿ� ����
// 					strncpy(m_strInputMessage, m_strBkInputMessage, SIZE_MAX_CHAT_MESSAGE);

				if(0 != strlen(g_pD3dApp->m_inputkey.m_full_str))
				{
					strcat(m_strPreBackupMessage,g_pD3dApp->m_inputkey.m_full_str);
					m_ptCurselPos.x= GetStringBuffLen(m_strPreBackupMessage);
					strncpy(m_strInputMessage, m_strBkInputMessage, SIZE_MAX_CHAT_MESSAGE);
					g_pD3dApp->CleanText();
				}				
 				
				int  chLenTmp=0;
				char chTmp[SIZE_MAX_CHAT_MESSAGE];
				ZERO_MEMORY(chTmp);
				if(0 == strlen(g_pD3dApp->m_inputkey.m_full_str))
				{
					// 2010. 02. 23 by jskim ä�ù��� ���� �� ����ȭ
// 					if(m_ptSelCurselPos.x != -1 )
// 					{
// 						chLenTmp = m_ptCurselPos.x-m_ptSelCurselPos.x;
//  						BlockCleanChat(chLenTmp);
// 					}
					if(m_bCaretCursel == TRUE)
					{
						BlockCleanChat(m_ptCurselPos.x, m_ptSelCurselPos.x);
						// ���� ���� �ʱ�ȭ
						SetChatMsgBuff(g_pD3dApp->m_inputkey.m_full_str);			
						// ������ ���ۿ� ����
						strncpy(m_strInputMessage, m_strBkInputMessage, SIZE_MAX_CHAT_MESSAGE);												
					}
					//end 2010. 02. 23 by jskim ä�ù��� ���� �� ����ȭ
					else
					{
						int nFindNevtPos = GetStringBuffPos(m_strNextBackupMessage, 1);	// ù��° ������ ���۸� �����´�			
						if(nFindNevtPos >= 0)
						{
							strcpy(chTmp, &m_strNextBackupMessage[nFindNevtPos]);
							strncpy(m_strNextBackupMessage, chTmp, SIZE_MAX_CHAT_MESSAGE);
							// ���� ���� �ʱ�ȭ
							SetChatMsgBuff(g_pD3dApp->m_inputkey.m_full_str);			
							// ������ ���ۿ� ����
		 					strncpy(m_strInputMessage, m_strBkInputMessage, SIZE_MAX_CHAT_MESSAGE);						
							// end 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
						}
					return INF_MSGPROC_BREAK;
					}								
				}
			return INF_MSGPROC_NORMAL;	
			}

		break;
	case VK_SHIFT:
		{
			USHORT nRace = g_pD3dApp->m_pShuttleChild->GetMyShuttleInfo().Race;
// 2010. 05. 25 by jskim �ٿ��ֱ�, ����, �߶󳻱� �Ϲݰ��� ���
// 			if(COMPARE_RACE(nRace,RACE_OPERATION) || COMPARE_RACE(nRace,RACE_GAMEMASTER))
// 			{
//end 2010. 05. 25 by jskim �ٿ��ֱ�, ����, �߶󳻱� �Ϲݰ��� ���
			// �����ڸ� ����Ʈ ��� Ű��
			m_ptSelCurselPos = m_ptCurselPos;	// Ŀ�� ��ġ			
			m_bShiftClick = TRUE;						
			
			return INF_MSGPROC_BREAK;
//			}			
			// 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ���� 
// 			if(COMPARE_RACE(nRace,RACE_OPERATION) || COMPARE_RACE(nRace,RACE_GAMEMASTER))
//			{
			// �����ڸ� ����Ʈ ��� Ű��
//				m_ptSelCurselPos = m_ptCurselPos;	// Ŀ�� ��ġ			
//				m_bShiftClick = TRUE;						
//				
//				return INF_MSGPROC_BREAK;
//			}
			// end 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ���� 
			//DBGOUT("m_bCaretCursel = TRUE;m_ptSelCurselPos[%d][%d] \n", m_ptSelCurselPos.x, m_ptSelCurselPos.y);
 		}
 		break;	
	}
	return INF_MSGPROC_NORMAL;
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2009-03-18 by bhsohn ä��â Ŀ�� �̵� �ý��� �߰�
/// \date		2009-03-18 ~ 2009-03-18
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMainChat::InitChatMsgBuff()
{	
	memset(m_strBkInputMessage, 0x00, SIZE_MAX_CHAT_MESSAGE);	// IME�ʱ�ȭ ���� ���� ������ �ִ´�.
	memset(m_strPreBackupMessage, 0x00, SIZE_MAX_CHAT_MESSAGE);	// IME�ʱ�ȭ ���� ���� ������ �ִ´�.
	memset(m_strNextBackupMessage, 0x00, SIZE_MAX_CHAT_MESSAGE);	// IME�ʱ�ȭ ���� ���� ������ �ִ´�.	
	m_ptCurselPos.x = m_ptCurselPos.y = 0;					// ���� ���� ��ġ	
	// 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
	//m_ptSelCurselPos.x = m_ptSelCurselPos.y = 0;			// Ŀ�� ��ġ
	// m_ptSelCurselPos ��ġ�� ���� �ȵ��ִ� ���·� ���� 
	// 2010. 02. 23 by jskim ä�ù��� ���� �� ����ȭ
	//m_ptSelCurselPos.x = m_ptSelCurselPos.y = -1;			// Ŀ�� ��ġ
	m_ptSelCurselPos.x = m_ptSelCurselPos.y = 0;			// Ŀ�� ��ġ
	//end 2010. 02. 23 by jskim ä�ù��� ���� �� ����ȭ
	// end 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
	m_bShiftClick = FALSE;
	m_bCaretCursel = FALSE;
	m_bControlCursel = FALSE;

}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2009-03-18 by bhsohn ä��â Ŀ�� �̵� �ý��� �߰�
/// \date		2009-03-18 ~ 2009-03-18
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMainChat::SetChatMsgBuff(char* i_pImeChat)
{
	BOOL bLastPos = FALSE;
	int nStringLen = GetStringBuffLen(m_strBkInputMessage);
	if(m_ptCurselPos.x == nStringLen)
	{
		// ���� ������ ��ġ��
		bLastPos = TRUE;
	}
// 2010. 02. 23 by jskim ä�ù��� ���� �� ����ȭ
// 	{
// 		// �տ� ������ ���� ����
// 		strncpy(m_strBkInputMessage, m_strPreBackupMessage, (SIZE_MAX_CHAT_MESSAGE-1));
// 		
// 		int nTmp = 0;
// 		int nStrinTmpLen = 0;
// 		{
// 			nTmp = 0;
// 			nStrinTmpLen = strlen(m_strBkInputMessage) + strlen(i_pImeChat);
// 			if(nStrinTmpLen > (SIZE_MAX_CHAT_MESSAGE-1))
// 			{
// 				nTmp = (SIZE_MAX_CHAT_MESSAGE-1)- strlen(m_strBkInputMessage);								
// 				if(nTmp > 0)
// 				{								
// 					// 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
// 					//strncat(m_strBkInputMessage, i_pImeChat, nTmp);
// 					// ���ڿ� �������� ������ �� �ȵ��� ���� 
// 					strncat(m_strBkInputMessage, i_pImeChat, strlen(i_pImeChat));
// 					if(m_bShiftClick = NULL)
// 					{
// 						m_bShiftClick = FALSE;
// 					}
// 					// end 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
// 				}									
// 			}
// 			else
// 			{
// 				// 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
// 				// ä�� ��� ���ڷ� �̵� ���ϰ� �Ѵ�.
// 				//strcat(m_strBkInputMessage, i_pImeChat);
// 				if(ChatModeChack(i_pImeChat[0]) &&		// ä�� ��忡 ����
// 				    m_strBkInputMessage[0] == i_pImeChat[0] &&
// 					m_ptCurselPos.x > 0)	
// 				{
// 					int chtmp = GetStringBuffPos(i_pImeChat,1);
// 					strcpy(i_pImeChat,&i_pImeChat[chtmp]);
// 				}
// 				strcat(m_strBkInputMessage, i_pImeChat);
// 				// end 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
// 			}
// 				
// 		}
// 		
// 		{
// 			nStrinTmpLen = strlen(m_strBkInputMessage) + strlen(m_strNextBackupMessage);
// 
// 			if(nStrinTmpLen > (SIZE_MAX_CHAT_MESSAGE-1))
// 			{
// 				nTmp = (SIZE_MAX_CHAT_MESSAGE-1) - strlen(m_strBkInputMessage);								
// 				if(nTmp > 0)
// 				{	
// 					//strncat(m_strBkInputMessage, m_strNextBackupMessage, nTmp);
// 					// 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
// 					// ���ڿ� �������� ������ �� �ȵ��� ���� 
// 					strncat(m_strBkInputMessage, m_strNextBackupMessage, strlen(m_strNextBackupMessage));
// 					if(m_bShiftClick = NULL)
// 					{
// 						m_bShiftClick = FALSE;
// 					}
// 					// end 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
// 				}									
// 			}
// 			else
// 			{
// 				strcat(m_strBkInputMessage, m_strNextBackupMessage);
// 			}
// 		}		
// 	}
	if(strlen(m_strPreBackupMessage) + strlen(i_pImeChat) + strlen(m_strNextBackupMessage) < SIZE_MAX_CHAT_MESSAGE -1)
	{
		wsprintf(m_strBkInputMessage,"%s%s%s",m_strPreBackupMessage,i_pImeChat,m_strNextBackupMessage);
	}
	else
	{
		strcpy(m_strBkInputMessage, m_strPreBackupMessage);
		if(strlen(m_strPreBackupMessage) + strlen(i_pImeChat) < SIZE_MAX_CHAT_MESSAGE)
		{
			strcat(m_strBkInputMessage, i_pImeChat);
		}
		else
		{
			int nFindLen = GetStringBuffLen(i_pImeChat);
			char chrtmp[256];
			for(int i = 1; i <= nFindLen; i++)
			{	
				memset(chrtmp,0x00,256);
				int nFindPos = GetStringBuffPos(i_pImeChat, nFindLen - i);							
				strncpy(chrtmp, i_pImeChat ,nFindPos);
				if(strlen(m_strBkInputMessage) + strlen(chrtmp) < SIZE_MAX_CHAT_MESSAGE)
				{
					strcat(m_strBkInputMessage, chrtmp);
					break;
				}
			}
		}
		if(strlen(m_strBkInputMessage) + strlen(m_strNextBackupMessage) >= SIZE_MAX_CHAT_MESSAGE)
		{
			int nFindLen = GetStringBuffLen(m_strNextBackupMessage);
			char chrtmp[256];
			
			for(int i = 1; i <= nFindLen; i++)
			{	
				memset(chrtmp,0x00,256);
				int nFindPos = GetStringBuffPos(m_strNextBackupMessage, nFindLen - i);							
				strncpy(chrtmp, m_strNextBackupMessage ,nFindPos);
				int ss =strlen(chrtmp);
				if(strlen(m_strBkInputMessage) + strlen(chrtmp) < SIZE_MAX_CHAT_MESSAGE)
				{
					strcat(m_strBkInputMessage, chrtmp);
					// 2010. 02. 23 by jskim ä�ù��� ���� �� ����ȭ - �߰�
					strcpy(m_strNextBackupMessage, chrtmp);
					//end 2010. 02. 23 by jskim ä�ù��� ���� �� ����ȭ - �߰� 

					break;
				}
			}
		}
	}
	//end 2010. 02. 23 by jskim ä�ù��� ���� �� ����ȭ
	if(bLastPos)
	{
		// �������� �����̴� ���̳�?
		m_ptCurselPos.x = GetStringBuffLen(m_strBkInputMessage);		
	}
	// 2010. 02. 23 by jskim ä�ù��� ���� �� ����ȭ
	else
	{
		m_ptCurselPos.x = GetStringBuffLen(m_strBkInputMessage) - GetStringBuffLen(m_strNextBackupMessage); 
	}
	//end 2010. 02. 23 by jskim ä�ù��� ���� �� ����ȭ
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2009-03-18 by bhsohn ä��â Ŀ�� �̵� �ý��� �߰�
/// \date		2009-03-18 ~ 2009-03-18
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMainChat::RenderCursel(int nShowTemp)
{	
	
	int nCurPosX = 0;
	int nCurPosY = 0;
	// 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
	char chatCurselBuff[256];
	memset(chatCurselBuff,0x00,256);
	// end 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����

	strncpy(chatCurselBuff, m_strPreBackupMessage, SIZE_MAX_CHAT_MESSAGE);
	
	// 2010. 02. 23 by jskim ä�ù��� ���� �� ����ȭ
	//if((strlen(chatCurselBuff)+strlen(g_pD3dApp->m_inputkey.m_full_str)) < (SIZE_MAX_CHAT_MESSAGE+2))
	if((strlen(chatCurselBuff)+strlen(g_pD3dApp->m_inputkey.m_full_str)) < (SIZE_MAX_CHAT_MESSAGE))
	{
		//strcat(chatCurselBuff, g_pD3dApp->m_inputkey.m_full_str);
		//chatCurselBuff���ڿ��� ä�ø�尡 ���ԵǾ������� Clean
// 		if(ChatModeChack(chatCurselBuff[0]) &&	
// 			g_pD3dApp->m_inputkey.m_full_str[0] == chatCurselBuff[0])
// 		{
// 			g_pD3dApp->CleanText();  
// 		}		
		strcat(chatCurselBuff, g_pD3dApp->m_inputkey.m_full_str);
		// end 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
	}
	else
	{
		int nFindLen = GetStringBuffLen(g_pD3dApp->m_inputkey.m_full_str);
		char chrtmp[256];
		for(int i = 1; i <= nFindLen; i++)
		{	
			memset(chrtmp,0x00,256);
			int nFindPos = GetStringBuffPos(g_pD3dApp->m_inputkey.m_full_str, nFindLen - i);							
			strncpy(chrtmp, g_pD3dApp->m_inputkey.m_full_str ,nFindPos);
			if(strlen(chatCurselBuff) + strlen(chrtmp) < SIZE_MAX_CHAT_MESSAGE)
			{
				strcat(chatCurselBuff, chrtmp);
				break;
			}
		}		
	}
	//end 2010. 02. 23 by jskim ä�ù��� ���� �� ����ȭ
	int nCurslePos = strlen(chatCurselBuff);

	chatCurselBuff[nCurslePos] = '_';
	chatCurselBuff[nCurslePos+1] = '\0';

	
	if((strlen(chatCurselBuff)+strlen(m_strNextBackupMessage)) < (SIZE_MAX_CHAT_MESSAGE+2))
	{
		strcat(chatCurselBuff, m_strNextBackupMessage);
	}
	// 2010. 02. 23 by jskim ä�ù��� ���� �� ����ȭ
	else
	{
		int nFindLen = GetStringBuffLen(m_strNextBackupMessage);
		char chrtmp[256];
		for(int i = 1; i <= nFindLen; i++)
		{	
			memset(chrtmp,0x00,256);
			int nFindPos = GetStringBuffPos(m_strNextBackupMessage, nFindLen - i);							
			strncpy(chrtmp, m_strNextBackupMessage ,nFindPos);
			if(strlen(chatCurselBuff) + strlen(chrtmp) < SIZE_MAX_CHAT_MESSAGE + 2)
			{
				strcat(chatCurselBuff, chrtmp);
				break;
			}
		}
	}	
// 	// 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����	
// 	int pos = GetStringBuffPos(chatCurselBuff, GetStringBuffLen(chatCurselBuff - 1));	 
// 	int pos1 = chatCurselBuff[pos] < 0;
// 	// end 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
	//end 2010. 02. 23 by jskim ä�ù��� ���� �� ����ȭ
	
	BOOL bOnePageOver = FALSE;
 	RECT rcRender;
	
	rcRender.left = m_ptCurselPos.x;
	rcRender.top = m_ptCurselPos.y;
	rcRender.right = m_ptSelCurselPos.x;
	rcRender.bottom = m_ptSelCurselPos.y;
	
	// 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
	char chCurselTmp[256];
	ZERO_MEMORY(chCurselTmp);		

	int nCurselPosX = m_ptCurselPos.x;
	if(m_bCaretCursel)
	{
		if(m_ptCurselPos.x > m_ptSelCurselPos.x)
		{
			nCurselPosX = m_ptSelCurselPos.x;
		}
		else if(m_ptCurselPos.x < m_ptSelCurselPos.x)
		{
			nCurselPosX = m_ptCurselPos.x;
		}
	}

	// ���� ������ ���� ������ �ƴϴ�.		
	int nIMELen	 = GetStringBuffLen(chatCurselBuff);
	int nCurPos	= GetStringBuffPos(chatCurselBuff, (nCurselPosX));
	strcpy(chCurselTmp, chatCurselBuff);
	// end 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
		
	SIZE szTmp = m_pFontInput->GetStringSize(chCurselTmp);
	if(szTmp.cx > CHAT_INPUT_FONT_LENGTH)
	{
		// �̹��� ũ�� üũ
		int nFindPrePos = nCurselPosX;
		if(nFindPrePos < 0 )
		{
			nFindPrePos = 0;
		}
		nCurPos	= GetStringBuffPos(chatCurselBuff, nFindPrePos);	// 1���� ������ ��������			
		if(nCurPos >= 0)
		{
			//strcpy(chCurselTmp, &chatCurselBuff[nCurPos]);
			vector<string> vecChatMessage;
			STRING_CULL(chCurselTmp, CHAT_INPUT_FONT_LENGTH, &vecChatMessage, m_pFontInput);
			
			if(!vecChatMessage.empty())
			// 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
			//{
			//	strncpy(chatCurselBuff, (char*)vecChatMessage[0].c_str(), 256);
			//	bOnePageOver = TRUE;	// ���������� �Ѱ��.
			//}
			//	if(bOnePageOver)
			//	{
			//		rcRender.left -= nCurPos;
			//		rcRender.right -= nCurPos;
			//
			//		if(rcRender.left < 0)
			//		{
			//			rcRender.left = 0;
			//		}
			//		if(rcRender.right < 0)
			//		{
			// 			rcRender.right = 0;
			// 		}				
			//	}
			{
				// ���� ������ �� ���� �߰� 
				// 2013-05-14 by bhsohn Buffer OverFlow Fix
// 				int chlen[3];
// 				char chtmp[3][SIZE_MAX_CHAT_MESSAGE];
// 				int chlensum;
				const INT MAX_CHAT_LINE = 5;
				int chlen[MAX_CHAT_LINE] = {0,};
				char chtmp[MAX_CHAT_LINE][SIZE_MAX_CHAT_MESSAGE];
				int chlensum = 0;
				// end 2013-05-14 by bhsohn Buffer OverFlow Fix
				
				
				int i; for(i=0;  i < vecChatMessage.size(); i++)
				{
					// 2013-05-14 by bhsohn Buffer OverFlow Fix
					if(i >= MAX_CHAT_LINE)
					{
						break;
					}
					// END 2013-05-14 by bhsohn Buffer OverFlow Fix
					chlen[i] = GetStringBuffLen((char*)(vecChatMessage[i]).c_str());
					strcpy(chtmp[i],(char*)(vecChatMessage[i]).c_str());
				}	
				chlensum = chlen[0] + chlen[1];

				// ä�� �ι�° ���ڿ�
				if(rcRender.left > chlen[0] && rcRender.left <= chlensum)
				{
					strncpy(chatCurselBuff, chtmp[1], 256);
					// ������ ������
					if(m_ptCurselPos.x > m_ptSelCurselPos.x)
					{
						rcRender.left = rcRender.left - chlen[0];
						rcRender.right = rcRender.right - chlen[0];
						if(rcRender.right < 0)
						{
							rcRender.right = 0;
						}
					}
					else
					{
						// ���� ������
						rcRender.left = rcRender.left - chlen[0] + 1;
						if(rcRender.right > chlensum)
						{
							// 2009. 12. 03 by jskim �ҷ����� ���� ����
							//.rcRender.right = 20;
							rcRender.right = chlen[1];
							//end 2009. 12. 03 by jskim �ҷ����� ���� ����
						}
						else
						{
							rcRender.right = rcRender.right - chlen[0] + 1;
						}
					}
				}
				// ä�� ����° ���ڿ�
				else if(rcRender.left > chlensum)
				{
					strncpy(chatCurselBuff, chtmp[2], 256);
					if(m_ptCurselPos.x > m_ptSelCurselPos.x)
					{
						// ������ ������
						rcRender.left = rcRender.left - chlensum;
						rcRender.right = rcRender.right - chlensum;
						if(rcRender.right < 0)
						{
							rcRender.right = 0;
						}
					}
					else
					{
						// ���� ������
						rcRender.left = rcRender.left - chlensum + 1;
						rcRender.right = rcRender.right - chlensum + 1;
					}						
				}
				else 
				{
					// ä�� ù��° ���ڿ�
					strncpy(chatCurselBuff, chtmp[0], 256);
					if(m_ptCurselPos.x < m_ptSelCurselPos.x)
					{
						//���� ������
						if(rcRender.right > chlen[0])
						{
							// 2009. 12. 03 by jskim �ҷ����� ���� ����
							//rcRender.right = 20;
							rcRender.right = chlen[0];
							//end 2009. 12. 03 by jskim �ҷ����� ���� ����
						}
						else
						{
							//������ ������
							rcRender.right = m_ptSelCurselPos.x + 1;
						}
						rcRender.left = m_ptCurselPos.x + 1;
					}
				}
			}		
		}
	}
	else
	{
		if(m_ptCurselPos.x < m_ptSelCurselPos.x)
		{
			rcRender.right = m_ptSelCurselPos.x + 1;
			rcRender.left = m_ptCurselPos.x + 1;
		}
	}
	// end 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
	m_pFontInput->SetTextureWidth(CHAT_INPUT_FONT_LENGTH);			
	if(m_bCaretCursel)
		// 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
	
		
	{	//�� �ִ� �ؽ�Ʈ 
// 		if(m_ptCurselPos.x  < m_ptSelCurselPos.x )
// 		{
// 			rcRender.left++;
// 			rcRender.right++;
// 		}
		// end 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
		NormalizeRect(&rcRender); 
		m_pFontInput->SetReLoadString(TRUE);
		m_pFontInput->DrawText(CHAT_FONT_START_X+nShowTemp,
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
							FONT_INPUT_Y,GUI_FONT_COLOR_Y,										  
#else															
							CHAT_FONT_START_Y + FONT_INPUT_Y,GUI_FONT_COLOR_Y,
#endif
							chatCurselBuff, 
							0, 
							&rcRender);
	}
	else
		// 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
	{   //�� ���� �ؽ�Ʈ						//�ּ� 
		// end 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����
		m_pFontInput->DrawText(CHAT_FONT_START_X+nShowTemp,
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
							FONT_INPUT_Y,GUI_FONT_COLOR_Y,										  
#else 
							CHAT_FONT_START_Y + FONT_INPUT_Y,GUI_FONT_COLOR_Y,
#endif
							chatCurselBuff,
							0L);

	}
	
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2009-03-18 by bhsohn ä��â Ŀ�� �̵� �ý��� �߰�
/// \date		2009-03-18 ~ 2009-03-18
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMainChat::SetClipBoard(char* i_pStr)
{
// 	Ŭ������ ���� -> �޸𸮻����ؼ� �ű�� ����Ÿ �������ذ� ->  Ŭ������ �ݰ�, �޸�����		
// 	Ŭ������� ��,����� ���־�� �մϴ�..Ǫ��~���ҽ��� �����ϱ� ��������.
	if( OpenClipboard(NULL) )		
	{		
		if( EmptyClipboard() )			
		{	
			HGLOBAL hMem = GlobalAlloc( GMEM_MOVEABLE | GMEM_DDESHARE, strlen(i_pStr)+1);
			if( hMem )				
			{				
				LPTSTR pClipData = (LPTSTR) GlobalLock(hMem);				
				pClipData[0] = 0;				
				strncpy( pClipData, i_pStr, strlen(i_pStr)+1);
				
				//DBGOUT("SetClipBoard[%s] \n", pClipData);

				SetClipboardData( CF_OEMTEXT, hMem );
				GlobalUnlock( hMem );
			}
			CloseClipboard();
			GlobalFree( hMem );			
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2009-03-18 by bhsohn ä��â Ŀ�� �̵� �ý��� �߰�
/// \date		2009-03-18 ~ 2009-03-18
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMainChat::PasteFromClipBoard(char* o_pStrTxt, int nSize)
{
	if(OpenClipboard(NULL))
	{
		HGLOBAL hGlobal = GetClipboardData(CF_TEXT); 
		char strBuff[1024];
		strBuff[0] = NULL;
		if(hGlobal) 
		{
			PTSTR pGlobal = (char*)GlobalLock(hGlobal);
			//lstrcpy( strBuff, pGlobal);
			strncpy( strBuff, pGlobal, nSize );
			GlobalUnlock(hGlobal);
		}
		CloseClipboard();
		strncpy(o_pStrTxt, strBuff, nSize);

		//DBGOUT("PasteFromClipBoard[%s] \n", o_pStrTxt);
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		���� ������ Ŀ���� ����
/// \author		// 2009-03-18 by bhsohn ä��â Ŀ�� �̵� �ý��� �߰�
/// \date		2009-03-18 ~ 2009-03-18
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMainChat::GetCurselString(char* o_pStrTxt)
{
	if(!m_bCaretCursel)
	{
		o_pStrTxt[0] = NULL;
		return;
	}
	else if(m_ptCurselPos.x == m_ptSelCurselPos.x)
	{
		o_pStrTxt[0] = NULL;
		return;
	}

	RECT rcRender;
	rcRender.left = m_ptCurselPos.x;
	rcRender.top = m_ptCurselPos.y;
	rcRender.right = m_ptSelCurselPos.x;
	rcRender.bottom = m_ptSelCurselPos.y;
	
	NormalizeRect(&rcRender); 

	int nStartPos = GetStringBuffPos(m_strBkInputMessage, rcRender.left);
	int nEndPos = GetStringBuffPos(m_strBkInputMessage, rcRender.right);
	
	if((-1 == nStartPos) || (-1 == nEndPos))
	{
		o_pStrTxt[0] = NULL;
		return;
	}
	
	int nCopyLen = nEndPos - nStartPos;
	
	if(nCopyLen <= 0)
	{
		o_pStrTxt[0] = NULL;
		return;
	}	
	strncpy(o_pStrTxt, &m_strBkInputMessage[nStartPos], nCopyLen);
// 	DBGOUT("CINFGameMainChat::GetCurselString nStartPos[%d] nEndPos[%d] o_pStrTxt[%s] \n", 
// 																		nStartPos, nEndPos, o_pStrTxt);

}

void CINFGameMainChat::BlockCleanChat(int LeftBlockPos,int RightBlockPos)
{
	char chTmp[SIZE_MAX_CHAT_MESSAGE];
	ZERO_MEMORY(chTmp);
	int nFindNevtPos;
	int nStringLen = GetStringBuffLen(m_strBkInputMessage);	
	int BlockType = IS_BLOCK_TYPE(LeftBlockPos, RightBlockPos);
	if(BlockType == LEFT_BLOCK)
	{	// ���� ������ ����
		nFindNevtPos = GetStringBuffPos(m_strNextBackupMessage, RightBlockPos - LeftBlockPos );	
		strcpy(chTmp, &m_strNextBackupMessage[nFindNevtPos]);
		strncpy(m_strNextBackupMessage, chTmp, SIZE_MAX_CHAT_MESSAGE);
	}
	else if(BlockType == RIGHT_BLOCK)
	{	// ������ ������ ����
			int nFindLen = GetStringBuffLen(m_strPreBackupMessage)- abs( RightBlockPos - LeftBlockPos );
			nFindNevtPos = GetStringBuffPos(m_strPreBackupMessage,nFindLen);
			strncpy(chTmp, m_strPreBackupMessage,nFindNevtPos);
			strncpy(m_strPreBackupMessage, chTmp, SIZE_MAX_CHAT_MESSAGE);
		}	
	m_ptCurselPos.x = 0;
	m_ptSelCurselPos.x= 0;
	m_bShiftClick=FALSE;
	m_bCaretCursel=FALSE;
}	
//end 2010. 02. 23 by jskim ä�ù��� ���� �� ����ȭ

// ä�ø�� üũ 
bool CINFGameMainChat::ChatModeChack(char i_Chr)
{
	// 2010. 04. 09 by ckPark Ŭ���̾�Ʈ ���ö����� ���� �߰�
// 	if(i_Chr=='~' ||
// 		i_Chr=='%' ||
// 		i_Chr=='@' ||
// 		i_Chr=='#' ||
// 		i_Chr=='^' ||
// 		i_Chr=='!' ||
// 		i_Chr=='$' ||
// 		i_Chr=='*')
	if( i_Chr == CHAT_ALL
		|| i_Chr == CHAT_ARENA
		|| i_Chr == CHAT_GUILD
		|| i_Chr == CHAT_PARTY
		|| i_Chr == CHAT_WAR
#if _RAT_CHAT_SYSTEM
		|| i_Chr == _RAT_CHAT_ALL_INFLUENCE
#endif
		|| i_Chr == CHAT_MAP
		|| i_Chr == CHAT_SELL_ALL
		|| i_Chr == CHAT_INFLUENCE_ALL
		|| i_Chr == CHAT_CHATROOM )	// 2012-12-14 by jhseol, ä�÷��� &�� ������� ���� �Ź� &�� ����� �ϴ� ���� ���� - CHAT_CHATROOM �߰�
	// end 2010. 04. 09 by ckPark Ŭ���̾�Ʈ ���ö����� ���� �߰�
	{
		return TRUE;
	}
	return FALSE;
}
// end 2009. 07. 30 by jsKim ä��â ���� ���� �� ��� ����


void CINFGameMainChat :: GetStrPara ( char *o_szStrBuff , char *i_szString , int iParamNum /*= 0*/ )
{

	if ( NULL == o_szStrBuff ) 
		return;

	if ( NULL == i_szString || 1 > strlen ( i_szString ) )
		return;

	int iSize = strlen ( i_szString );
	int i = 0;

	int iStartNum = 0;
	int iEndNum = 0;

	if ( iParamNum > 0 )
	{
		int iCheckCnt = 0;

		for ( i = 0; i < iSize; ++i )
		{
			if ( i_szString[i] == ' ' )
			{
				iStartNum = i+1;

				iCheckCnt++;

				if ( iCheckCnt == iParamNum )
					break;
			}
		}

		if ( iCheckCnt != iParamNum )
			return;
	}

	iEndNum = iStartNum;

	for ( iEndNum = iStartNum; iEndNum < iSize; ++iEndNum )
	{
		if ( iEndNum == iSize )
			break;

		if ( i_szString[iEndNum] == ' ' )
		{
			iEndNum;
			break;
		}
	}

	if ( iStartNum != iEndNum )
	{
		memcpy ( o_szStrBuff , &i_szString[iStartNum] , iEndNum - iStartNum );
	}

}