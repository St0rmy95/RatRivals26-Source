// INFMissionMain.cpp: implementation of the CINFMissionMain class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AtumApplication.h"
#include "ShuttleChild.h"
#include "INFImage.h"
#include "GameDataLast.h"
#include "INFGameMain.h"
#include "D3DHanFont.h"
#include "AtumSound.h"
#include "QuestData.h"
#include "StoreData.h"
#include "ItemInfo.h"
#include "Interface.h"
#include "ClientParty.h"

#include "INFMissionMain.h"
#include "INFGameMainQSlot.h"			// 2011. 10. 10 by jskim UI�ý��� ����

// 2011-03-02 by hsSon, �̼� �۾� ��ġ ����
#define MISSION_VIEW_INFO_POSX				(g_pD3dApp->GetBackBufferDesc().Width-410*HIDPI_COEFF)
// end 2011-03-02 by hsSon, �̼� �۾� ��ġ ����

#define MISSION_FONT_HEIGHT_GAB				17*HIDPI_COEFF
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����

// Go Map
#define GO_MAP_POS_X						((g_pD3dApp->GetBackBufferDesc().Width/2)-46)//(g_pD3dApp->GetBackBufferDesc().Width-127)
#define GO_MAP_POS_Y						(g_pD3dApp->GetBackBufferDesc().Height-110*HIDPI_COEFF)

// Go Mission
#define GO_MISSION_MAP_POS_X				((g_pD3dApp->GetBackBufferDesc().Width/2)-123)//(g_pD3dApp->GetBackBufferDesc().Width-253)
#define GO_MISSION_MAP_POS_Y				(g_pD3dApp->GetBackBufferDesc().Height-110*HIDPI_COEFF)

#ifdef _RAT_FFA
// Go FFA
#define GO_MAP_FFA_POS_X					((g_pD3dApp->GetBackBufferDesc().Width/2)+31)
#define GO_MAP_FFA_POS_Y					(g_pD3dApp->GetBackBufferDesc().Height-124*HIDPI_COEFF)
#endif 

#else 
// ��� ��ư 
#define GO_MAP_POS_X						((g_pD3dApp->GetBackBufferDesc().Width-105)/2)//(g_pD3dApp->GetBackBufferDesc().Width-127)
#define GO_MAP_POS_Y						(g_pD3dApp->GetBackBufferDesc().Height-75)

// Go Mission��
#define GO_MISSION_MAP_POS_X				((g_pD3dApp->GetBackBufferDesc().Width/2)-105)//(g_pD3dApp->GetBackBufferDesc().Width-253)
#define GO_MISSION_MAP_POS_Y				(g_pD3dApp->GetBackBufferDesc().Height-75)
#endif


// ù �ɸ� ����Ʈ
#define	FIRST_QUEST								101

// ���¼��� Quest
#define	SELECT_QUEST							112

// 2012-11-29 by bhsohn ȥ���� �縷 ����Ʈ �ȳ����� ���׼���
// ���������� ����
struct QuestIdx_Sort_Level: binary_function<structQuestInfo, structQuestInfo, bool>
{
	bool operator()(structQuestInfo pArenaItemInfo1, structQuestInfo pArenaItemInfo2)
	{
        if(pArenaItemInfo1.nMinLevel < pArenaItemInfo2.nMinLevel)
		{
			return TRUE;
		}		
		return FALSE;
    };
};
// END 2012-11-29 by bhsohn ȥ���� �縷 ����Ʈ �ȳ����� ���׼���


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CINFMissionMain::CINFMissionMain()
{
	m_pGoMapBtn = NULL;
	m_pGoMissionMapBtn = NULL;
#ifdef _RAT_FFA
	m_pGoFFABtn = NULL;
#endif

	m_pINFMissionTreeInfo = NULL;
	m_pINFMissionPopupInfo = NULL;
	m_pINFMissionSelInfluence = NULL;
	m_pINFMissionMaster		= NULL; // 2008-12-09 by dgwoo �̼Ǹ�����.
	m_nShowMissionWnd = 0;
	
	//m_nShowMissionWnd |= (1<<MISSOIN_SHOW_TREE);	
	//m_nShowMissionWnd |= (1<<MISSOIN_SHOW_SEL_INFLUENCE);	

	// 2014-07-02 by ymjoo DrawText ���� ���� �۾� (�����߹̼�)
#ifdef C_DRAWTEXT_UPGRADE_YMJOO
	for(int i = 0 ; i < 10 ; ++i)
	{
		m_pMissionINGFont[i] = NULL;
	}
#else
	m_pMissionINGFont = NULL;
#endif
	// END 2014-07-02 by ymjoo DrawText ���� ���� �۾� (�����߹̼�)

	m_bSearchPosQuest = FALSE;
	m_pHidePosQuest = NULL;

	m_bPosMissionComplete = FALSE;
	m_bInfluenceFlag = FALSE;

	m_fVCNInflDistributionPercent = 0.0f;
	m_fANIInflDistributionPercent = 0.0f;

	m_nMyShuttleCharacter = -1;

	m_nMissionMapQuestIndex = 0;
	m_nFirstPossibleQuestIdx =0;
}

CINFMissionMain::~CINFMissionMain()
{
	if(m_pGoMissionMapBtn)
	{
		m_pGoMissionMapBtn->DeleteDeviceObjects();	
		SAFE_DELETE(m_pGoMissionMapBtn);
	}
	if(m_pGoMapBtn)
	{
		m_pGoMapBtn->DeleteDeviceObjects();	
		SAFE_DELETE(m_pGoMapBtn);
	}
	if(m_pINFMissionTreeInfo)
	{
		m_pINFMissionTreeInfo->DeleteDeviceObjects();	
		SAFE_DELETE(m_pINFMissionTreeInfo);
	}
#ifdef _RAT_FFA
	if (m_pGoFFABtn)
	{
		m_pGoFFABtn->DeleteDeviceObjects();
		SAFE_DELETE(m_pGoFFABtn);
	}
#endif
	if(m_pINFMissionPopupInfo)
	{
		m_pINFMissionPopupInfo->DeleteDeviceObjects();	
		SAFE_DELETE(m_pINFMissionPopupInfo);
	}
	if(m_pINFMissionSelInfluence)
	{
		m_pINFMissionSelInfluence->DeleteDeviceObjects();	
		SAFE_DELETE(m_pINFMissionSelInfluence);
	}
// 2008-12-09 by dgwoo �̼Ǹ�����.
	if(m_pINFMissionMaster)
	{
		m_pINFMissionMaster->DeleteDeviceObjects();
		SAFE_DELETE(m_pINFMissionMaster);
	}
	
	// 2014-07-02 by ymjoo DrawText ���� ���� �۾� (�����߹̼�)
#ifdef C_DRAWTEXT_UPGRADE_YMJOO
	for(int i = 0 ; i < 10 ; ++i)
	{
		if(m_pMissionINGFont[i])
		{
			m_pMissionINGFont[i]->DeleteDeviceObjects();
			SAFE_DELETE(m_pMissionINGFont[i]);
		}
	}
#else
 	if(m_pMissionINGFont)
 	{
 		m_pMissionINGFont->DeleteDeviceObjects();	
 		SAFE_DELETE(m_pMissionINGFont);
 	}
#endif
	// END 2014-07-02 by ymjoo DrawText ���� ���� �۾� (�����߹̼�)
}


HRESULT CINFMissionMain::InitDeviceObjects()
{	
	DataHeader	* pDataHeader = NULL;	
	{
		if(NULL == m_pINFMissionTreeInfo)
		{
			m_pINFMissionTreeInfo = new CINFMissionTreeInfo(this);
		}	
		m_pINFMissionTreeInfo->InitDeviceObjects();		
	}
	
	{
		if(NULL == m_pINFMissionPopupInfo)
		{
			m_pINFMissionPopupInfo = new CINFMissionPopupInfo(this);
		}	
		m_pINFMissionPopupInfo->InitDeviceObjects();		
	}

	
	{
		if(NULL == m_pINFMissionSelInfluence)
		{
			m_pINFMissionSelInfluence = new CINFMissionSelInfluence(this);
		}	
		m_pINFMissionSelInfluence->InitDeviceObjects();		
	}
// 2008-12-09 by dgwoo �̼Ǹ�����.
	{
		if(NULL == m_pINFMissionMaster)
		{
			m_pINFMissionMaster = new CINFMissionMasterReg;
		}
		m_pINFMissionMaster->InitDeviceObjects();
	}

	// 2014-07-02 by ymjoo DrawText ���� ���� �۾� (�����߹̼�)
#ifdef C_DRAWTEXT_UPGRADE_YMJOO
	for(int i = 0 ; i < 10 ; ++i)
	{
		if(NULL == m_pMissionINGFont[i])
		{
			m_pMissionINGFont[i] = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()), 9*HIDPI_COEFF, D3DFONT_ZENABLE, TRUE, 1024 * HIDPI_COEFF, 32 * HIDPI_COEFF);
		}
		m_pMissionINGFont[i]->InitDeviceObjects(g_pD3dDev);
	}
#else
 	{
 		if(NULL == m_pMissionINGFont)
 		{
 			m_pMissionINGFont = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,1024,32);
 		}		
 		m_pMissionINGFont->InitDeviceObjects(g_pD3dDev) ;
 	}
#endif
	// END 2014-07-02 by ymjoo DrawText ���� ���� �۾� (�����߹̼�)
	
	// ��� ��ư 	
	{
		char szUpBtn[30], szDownBtn[30], szSelBtn[30], szDisBtn[30];
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
		wsprintf(szUpBtn, "goshn01");															  
#else 
		wsprintf(szUpBtn, "goshn");
#endif
		wsprintf(szDownBtn, "goshs");
		wsprintf(szSelBtn, "gosho");
		wsprintf(szDisBtn, "goshnot");
		if(NULL == m_pGoMapBtn)
		{
			m_pGoMapBtn = new CINFImageBtn;
		}
		// 2011. 1. 12 by jskim UI �̹��� ��ư ���� ����	
		//m_pGoMapBtn->InitDeviceObjects(szUpBtn, szDownBtn, szSelBtn, szDisBtn);
		m_pGoMapBtn->InitDeviceObjects(szUpBtn, szDownBtn, szSelBtn, szDisBtn,"STRTOOLTIP1");
		// end 2011. 1. 12 by jskim UI �̹��� ��ư ���� ����	
		
	}
	
	// �̼� ������ �̵�
	{
		char szUpBtn[30], szDownBtn[30], szSelBtn[30], szDisBtn[30];
		wsprintf(szUpBtn, "migon");
		wsprintf(szDownBtn, "migos");
		wsprintf(szSelBtn, "migoo");
		wsprintf(szDisBtn, "migonot");
		if(NULL == m_pGoMissionMapBtn)
		{
			m_pGoMissionMapBtn = new CINFImageBtn;
		}
		// 2011. 1. 12 by jskim UI �̹��� ��ư ���� ����	
		m_pGoMissionMapBtn->InitDeviceObjects(szUpBtn, szDownBtn, szSelBtn, szDisBtn, "STRTOOLTIP2");

		// end 2011. 1. 12 by jskim UI �̹��� ��ư ���� ����	
		
	}
	
#ifdef _RAT_FFA
	{
		char szUpBtn[30], szDownBtn[30], szSelBtn[30], szDisBtn[30];
		wsprintf(szUpBtn, "gosh_FFA_n");
		wsprintf(szDownBtn, "gosh_FFA_s");
		wsprintf(szSelBtn, "gosh_FFA_o");
		wsprintf(szDisBtn, "gosh_FFA_no"); // Cannot fit _gosh_FFA_not --> SO its "gosh_FFA_no"
		if (NULL == m_pGoFFABtn)
		{
			m_pGoFFABtn = new CINFImageBtn;
		}
		
		m_pGoFFABtn->InitDeviceObjects(szUpBtn, szDownBtn, szSelBtn, szDisBtn,	"STRTOOLTIP1");
	}
#endif
	
	return S_OK ;
}

HRESULT CINFMissionMain::RestoreDeviceObjects()
{
	m_pINFMissionTreeInfo->RestoreDeviceObjects();
	m_pINFMissionPopupInfo->RestoreDeviceObjects();
	m_pINFMissionSelInfluence->RestoreDeviceObjects();
// 2008-12-09 by dgwoo �̼Ǹ�����.
	m_pINFMissionMaster->RestoreDeviceObjects();

	// 2014-07-02 by ymjoo DrawText ���� ���� �۾� (�����߹̼�)
#ifdef C_DRAWTEXT_UPGRADE_YMJOO
	for(int i = 0 ; i < 10 ; ++i)
	{
		m_pMissionINGFont[i]->RestoreDeviceObjects();
	}
#else
	m_pMissionINGFont->RestoreDeviceObjects();
#endif
	// END 2014-07-02 by ymjoo DrawText ���� ���� �۾� (�����߹̼�)

	// ��� ��ư 
	{
		m_pGoMapBtn->RestoreDeviceObjects();		
//		m_pGoMapBtn->SetBtnPosition(GO_MAP_POS_X, GO_MAP_POS_Y);
	}
	// �̼Ǹ����� �̵�
	{			
		m_pGoMissionMapBtn->RestoreDeviceObjects();		
//		m_pGoMissionMapBtn->SetBtnPosition(GO_MISSION_MAP_POS_X, GO_MISSION_MAP_POS_Y);
	}
#ifdef _RAT_FFA
	{
		m_pGoFFABtn->RestoreDeviceObjects();
	}
#endif
	
	return S_OK ;
}

HRESULT CINFMissionMain::DeleteDeviceObjects()
{
	m_pINFMissionTreeInfo->DeleteDeviceObjects();	
	SAFE_DELETE(m_pINFMissionTreeInfo);		
	
	m_pINFMissionPopupInfo->DeleteDeviceObjects();	
	SAFE_DELETE(m_pINFMissionPopupInfo);		

	m_pINFMissionSelInfluence->DeleteDeviceObjects();	
	SAFE_DELETE(m_pINFMissionSelInfluence);		
	
// 2008-12-09 by dgwoo �̼Ǹ�����.
	m_pINFMissionMaster->DeleteDeviceObjects();
	SAFE_DELETE(m_pINFMissionMaster);

	// 2014-07-02 by ymjoo DrawText ���� ���� �۾� (�����߹̼�)
#ifdef C_DRAWTEXT_UPGRADE_YMJOO
	for(int i = 0 ; i < 10 ; ++i)
	{
		m_pMissionINGFont[i]->DeleteDeviceObjects();
		SAFE_DELETE(m_pMissionINGFont[i]);
	}
#else
 	m_pMissionINGFont->DeleteDeviceObjects();	
 	SAFE_DELETE(m_pMissionINGFont);			
#endif
	// END 2014-07-02 by ymjoo DrawText ���� ���� �۾� (�����߹̼�)

	{
		m_pGoMapBtn->DeleteDeviceObjects();	
		SAFE_DELETE(m_pGoMapBtn);
	}
	
	{
		m_pGoMissionMapBtn->DeleteDeviceObjects();	
		SAFE_DELETE(m_pGoMissionMapBtn);
	}
#ifdef _RAT_FFA
	{
		m_pGoFFABtn->DeleteDeviceObjects();
		SAFE_DELETE(m_pGoFFABtn);
	}
#endif


	return S_OK ;
}

HRESULT CINFMissionMain::InvalidateDeviceObjects()
{
	m_pINFMissionTreeInfo->InvalidateDeviceObjects();
	m_pINFMissionPopupInfo->InvalidateDeviceObjects();
	m_pINFMissionSelInfluence->InvalidateDeviceObjects();
// 2008-12-09 by dgwoo �̼Ǹ�����.
	m_pINFMissionMaster->InvalidateDeviceObjects();

	// 2014-07-02 by ymjoo DrawText ���� ���� �۾� (�����߹̼�)
#ifdef C_DRAWTEXT_UPGRADE_YMJOO
	for(int i = 0 ; i < 10 ; ++i)
	{
		m_pMissionINGFont[i]->InvalidateDeviceObjects();
	}
#else
	m_pMissionINGFont->InvalidateDeviceObjects();
#endif
	// END 2014-07-02 by ymjoo DrawText ���� ���� �۾� (�����߹̼�)

	m_pGoMapBtn->InvalidateDeviceObjects();		

	m_pGoMissionMapBtn->InvalidateDeviceObjects();		
	
#ifdef _RAT_FFA
	m_pGoFFABtn->InvalidateDeviceObjects();
#endif


	return S_OK ;
}

void CINFMissionMain::Tick()
{
	// ������ �̼� 
	TickHideMission();

	// ����Ʈ ��Ʈ�� 
	if(IsShowWnd(MISSOIN_SHOW_TREE))
	{
		m_pINFMissionTreeInfo->Tick();		
	}	
	if(IsShowWnd(MISSOIN_SHOW_POPUP))
	{
		m_pINFMissionPopupInfo->Tick();
	}
	if(IsShowWnd(MISSOIN_SHOW_SEL_INFLUENCE))
	{
		m_pINFMissionSelInfluence->Tick();
	}	
	m_pINFMissionMaster->Tick();// 2008-12-09 by dgwoo �̼Ǹ�����.
	// ��ư��
	TickBtn();
}
void CINFMissionMain::TickBtn()
{
	if(m_nMyShuttleCharacter != g_pD3dApp->IsMyShuttleCharacter() || -1 == m_nMyShuttleCharacter )
	{
		m_nMyShuttleCharacter = g_pD3dApp->IsMyShuttleCharacter();
		
		BOOL bShowGoMissionMapBtn,  bShowGoMapBtn;
		bShowGoMissionMapBtn = bShowGoMapBtn = FALSE;
#ifdef _RAT_FFA
		BOOL bGoFFAMapBtn = FALSE;
#endif
		
		// ���ڻ����̸� ������ �Ⱥ���
		if(FALSE == g_pGameMain->IsBazaar())
		{
			if(m_nMyShuttleCharacter)
			{
				bShowGoMissionMapBtn =  bShowGoMapBtn = TRUE;
#ifdef _RAT_FFA
				bGoFFAMapBtn = TRUE;
#endif
			}
			CQuest *pQuestInfo = g_pQuestData->GetProgressMission();
			if(NULL == pQuestInfo)
			{
				bShowGoMissionMapBtn  = FALSE;
			}
			else if(pQuestInfo && pQuestInfo->StartMapIndex <= 0)
			{
				bShowGoMissionMapBtn  = FALSE;
			}
		}		

#ifdef _RAT_GREYBUTTONS
		USHORT MapIndex = g_pShuttleChild->GetMyShuttleInfo().MapChannelIndex.MapIndex;
#endif

		if(m_pGoMissionMapBtn)
		{
			m_pGoMissionMapBtn->SetBtnPosition(GO_MISSION_MAP_POS_X, GO_MISSION_MAP_POS_Y);
#ifdef _RAT_GREYBUTTONS
			if (bShowGoMissionMapBtn == FALSE)
			{
				if (IS_OUTPOST_CITY_MAP_INDEX(MapIndex)
					|| IS_CITY_MAP_INDEX(MapIndex))
				{
					m_pGoMissionMapBtn->EnableBtn(false);
					m_pGoMissionMapBtn->ShowWindow(TRUE);
				}
				else
				{
					m_pGoMissionMapBtn->EnableBtn(false);
					m_pGoMissionMapBtn->ShowWindow(bShowGoMissionMapBtn);
				}
			}
			else
			{
				m_pGoMissionMapBtn->EnableBtn(true);
				m_pGoMissionMapBtn->ShowWindow(bShowGoMissionMapBtn);
			}
#else
			m_pGoMissionMapBtn->ShowWindow(bShowGoMissionMapBtn);
#endif

		}
		if(m_pGoMapBtn)
		{
//#ifndef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
			m_pGoMapBtn->SetBtnPosition(GO_MAP_POS_X, GO_MAP_POS_Y);
#ifdef _RAT_GREYBUTTONS
			if (bShowGoMapBtn == FALSE)
			{
				if (IS_OUTPOST_CITY_MAP_INDEX(MapIndex)
					|| IS_CITY_MAP_INDEX(MapIndex))
				{
					m_pGoMapBtn->EnableBtn(false);
					m_pGoMapBtn->ShowWindow(TRUE);
				}
				else
				{
					m_pGoMapBtn->EnableBtn(false);
					m_pGoMapBtn->ShowWindow(bShowGoMapBtn);
				}
			}
			else
			{
				m_pGoMapBtn->EnableBtn(true);
				m_pGoMapBtn->ShowWindow(bShowGoMapBtn);
			}
#else
			m_pGoMapBtn->ShowWindow(bShowGoMapBtn);
#endif
//#endif
		}
#ifdef _RAT_FFA
		{
			m_pGoFFABtn->SetBtnPosition(GO_MAP_FFA_POS_X, GO_MAP_FFA_POS_Y);
#ifdef _RAT_GREYBUTTONS
				if (bGoFFAMapBtn == FALSE)
				{
					if (IS_OUTPOST_CITY_MAP_INDEX(MapIndex)
						|| IS_CITY_MAP_INDEX(MapIndex))
					{
						m_pGoFFABtn->EnableBtn(false);
						m_pGoFFABtn->ShowWindow(TRUE);
					}
					else
					{
						m_pGoFFABtn->EnableBtn(false);
						m_pGoFFABtn->ShowWindow(bGoFFAMapBtn);
					}
				}
				else
				{
					m_pGoFFABtn->EnableBtn(true);
					m_pGoFFABtn->ShowWindow(bGoFFAMapBtn);
				}
#else
		m_pGoFFABtn->ShowWindow(bGoFFAMapBtn);
#endif
		}
#endif
	}		
}

void CINFMissionMain::TickHideMission()
{
	if(m_bSearchPosQuest == TRUE && m_pHidePosQuest)
	{	// Ư�� �����ǿ� ����Ʈ�� �ִ°�� �˻� �� �����Ѵ�.
		CQuest *pQuestInfo = g_pQuestData->GetProgressMission();
		if(pQuestInfo == NULL)
		{
			int X = (int)(g_pD3dApp->m_pShuttleChild->m_vPos.x);
			int Z = (int)(g_pD3dApp->m_pShuttleChild->m_vPos.z);
			
			if(m_pINFMissionTreeInfo->HideMissionCheckProgressMission(m_pHidePosQuest))
			{
				char buff[512];
				ZERO_MEMORY(buff);
				wsprintf(buff, STRMSG_C_050825_0001, m_pHidePosQuest->QuestName); //"�̼� %s��(��) �����Ͻðڽ��ϱ�?"
				g_pGameMain->AddMsgBox(buff,_Q_MISSION_START, (DWORD)m_pHidePosQuest->QuestIndex);
				m_bSearchPosQuest = FALSE;
			}
		}
	}
	// Ư������ �̼� �Ϸ�
	if(m_bPosMissionComplete == TRUE)
	{
		int nMissionIndex = g_pD3dApp->SerchMissionCondition();
		if(nMissionIndex)
		{
			MissionEnd(nMissionIndex);
			m_bPosMissionComplete = FALSE;
		}
	}
	// �̼� �Ϸ� �ð� ǥ��
	// ����Ʈ �����ð� ǥ��
	if(g_pGameMain->m_bQuestLimitTimeView)
	{	
		// 2008-04-07 by bhsohn ����Ʈ �ð� �����Ǵ� ���� ó��
		float fElapsedTime = g_pD3dApp->GetCheckElapsedTime();
		float fGetQuestTimeElapse = g_pGameMain->GetQuestTimeElapse();
		fGetQuestTimeElapse -= fElapsedTime;				
		g_pGameMain->SetQuestTimeElapse(fGetQuestTimeElapse);

		if(fGetQuestTimeElapse <-5)
		{
			g_pGameMain->m_bQuestLimitTimeView = FALSE;
			// �� ���� �̼���� ������
			CQuest *pQuestInfo = g_pQuestData->GetProgressMission();
			if(pQuestInfo)
			{
				// 2005-08-02 ispark
				if(QUEST_END_TYPE_TIME_OVER == pQuestInfo->QuestEndType)
				{
					// �̼� �Ϸ� ������
					// 2006-03-27 by ispark, ��Ƽ�̼� �߰�
					if(pQuestInfo->IsPartyQuest())
					{
						g_pQuestData->SendFieldSocketQuestRequestSuccessCheck(pQuestInfo->QuestIndex);
					}
					else
					{
						g_pGameMain->SetImageInfo(MISSION_SUC, TRUE);
						//g_pD3dApp->SendMissionComplete();
					}
				}
				else
				{
					// �̼� ��� ������
					g_pGameMain->SetImageInfo(MISSION_FAI, TRUE);
				}
			}
		}
	}
}
void CINFMissionMain::Render()
{
	// ������ ��ư��
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	int  nPosX, nPosY;
	nPosX = g_pGameMain->m_pQuickSlot->m_nX;
	nPosY = g_pGameMain->m_pQuickSlot->m_nY;
	int Y = nPosY  - QSLOT_TAB_NUMBER * ( QSLOT_ICON_INTERVAL + 2 ) - m_pGoMissionMapBtn->GetImgSize().y + 25;
	if( g_pGameMain->m_pQuickSlot->IsSlotOpen() == FALSE )
	{
		m_pGoMissionMapBtn->SetBtnPosition(GO_MISSION_MAP_POS_X, GO_MISSION_MAP_POS_Y);
	}
	else
	{
		m_pGoMissionMapBtn->SetBtnPosition(GO_MISSION_MAP_POS_X,GO_MISSION_MAP_POS_Y);	
	}
	if( g_pGameMain->m_pQuickSlot->IsSlotOpen() == FALSE )
	{
		m_pGoMapBtn->SetBtnPosition(GO_MAP_POS_X, GO_MAP_POS_Y);
	}
	else
	{
		m_pGoMapBtn->SetBtnPosition(GO_MAP_POS_X, GO_MAP_POS_Y);
	}
	// end 2011. 10. 10 by jskim UI�ý��� ����													  
#endif
	m_pGoMapBtn->Render();

	m_pGoMissionMapBtn->Render();
#ifdef _RAT_FFA
	m_pGoFFABtn->Render();
#endif

	// ����Ʈ ��Ʈ�� 
	if(IsShowWnd(MISSOIN_SHOW_TREE))
	{
		m_pINFMissionTreeInfo->Render();
	}
	if(IsShowWnd(MISSOIN_SHOW_POPUP))
	{
		m_pINFMissionPopupInfo->Render();
	}
	if(IsShowWnd(MISSOIN_SHOW_SEL_INFLUENCE))
	{
		m_pINFMissionSelInfluence->Render();
	}	
	m_pINFMissionMaster->Render();// 2008-12-09 by dgwoo �̼Ǹ�����.
}

int CINFMissionMain::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{	
	// 2008-12-09 by dgwoo �̼� ������ �ý���.
	if(INF_MSGPROC_BREAK == m_pINFMissionMaster->WndProc(uMsg,wParam,lParam))
		return INF_MSGPROC_BREAK;

	if(IsShowWnd(MISSOIN_SHOW_TREE))
	{
		if(INF_MSGPROC_BREAK == m_pINFMissionTreeInfo->WndProc(uMsg, wParam, lParam))
		{
			return INF_MSGPROC_BREAK;
		}
	}	
	if(IsShowWnd(MISSOIN_SHOW_POPUP))
	{
		if(INF_MSGPROC_BREAK == m_pINFMissionPopupInfo->WndProc(uMsg, wParam, lParam))
		{
			return INF_MSGPROC_BREAK;
		}
	}
	
	if(IsShowWnd(MISSOIN_SHOW_SEL_INFLUENCE))
	{
		if(INF_MSGPROC_BREAK == m_pINFMissionSelInfluence->WndProc(uMsg, wParam, lParam))
		{
			return INF_MSGPROC_BREAK;
		}
	}

	switch(uMsg)
	{
	case WM_MOUSEWHEEL:
		{
		}
		break;
	case WM_LBUTTONDOWN:
		{
			return OnLButtonDown(wParam, lParam);			
		}
		break;
	case WM_MOUSEMOVE:
		{
			return OnMouseMove(wParam, lParam);
		}
	case WM_LBUTTONUP:
		{
			return OnLButtonUp(wParam, lParam);
		}
	}
	return INF_MSGPROC_NORMAL;	
}
int CINFMissionMain::OnLButtonDown(WPARAM wParam, LPARAM lParam)
{
	POINT pt;
	pt.x = LOWORD(lParam);
	pt.y = HIWORD(lParam);
	CheckMouseReverse(&pt);
	
	{
		if(TRUE == m_pGoMapBtn->OnLButtonDown(pt))
		{
			// ��ư���� ���콺�� �ִ�.
			return  INF_MSGPROC_BREAK;
		}		
	}
	
	{
		if(TRUE == m_pGoMissionMapBtn->OnLButtonDown(pt))
		{
			// ��ư���� ���콺�� �ִ�.
			return  INF_MSGPROC_BREAK;
		}		
	}
	
#ifdef _RAT_FFA
	{
		if (TRUE == m_pGoFFABtn->OnLButtonDown(pt))
		{
			return INF_MSGPROC_BREAK;
		}
	}
#endif

	return INF_MSGPROC_NORMAL;	
}

int CINFMissionMain::OnLButtonUp(WPARAM wParam, LPARAM lParam)
{
	POINT pt;
	pt.x = LOWORD(lParam);
	pt.y = HIWORD(lParam);
	CheckMouseReverse(&pt);
	
	{
		if(TRUE == m_pGoMapBtn->OnLButtonUp(pt))
		{			
			OnClickGoMap();
			// ��ư Ŭ�� 
			g_pD3dApp->m_pSound->PlayD3DSound(SOUND_SELECT_BUTTON, D3DXVECTOR3(0,0,0), FALSE);			
			return  INF_MSGPROC_BREAK;
		}
	}
	
	{
		if(TRUE == m_pGoMissionMapBtn->OnLButtonUp(pt))
		{			
			OnClickGoMissionMap();
			// ��ư Ŭ�� 
			g_pD3dApp->m_pSound->PlayD3DSound(SOUND_SELECT_BUTTON, D3DXVECTOR3(0,0,0), FALSE);			
			return  INF_MSGPROC_BREAK;
		}
	}
	
#ifdef _RAT_FFA
	{
		if (TRUE == m_pGoFFABtn->OnLButtonUp(pt))
		{
			g_pGameMain->GoWarpMapChange(FFA_MAP);

			g_pD3dApp->m_pSound->PlayD3DSound(SOUND_SELECT_BUTTON, D3DXVECTOR3(0,0,0), FALSE);
			return  INF_MSGPROC_BREAK;
		}
	}
#endif
	return INF_MSGPROC_NORMAL;	
}
void CINFMissionMain::OnClickGoMap()
{
	// 2005-11-16 by ispark
	// ��� �̵� ���� �˻�
	if(!CheckMissionStart())
	{
		return;
	}
	
	MAP_INFO* pMapInfo = g_pGameMain->GetMapInfo(3002);	
	MEX_QUEST_INFO* pTemp = g_pQuestData->FindCharacterQuest(pMapInfo->QuestIndexForWarp);
	if(pTemp && pTemp->QuestState == QUEST_STATE_COMPLETED)
	{		
//		g_pD3dApp->StartFadeEffect(TRUE,3,D3DCOLOR_ARGB(0,0,0,0));		
//		g_pCharacterChild->FineObjectTakeOff();				
		// 0�̸� �׳� ���		
		g_pGameMain->GoWarpMapChange(0);
		
	}
	else
	{
		CQuest* pQuest = g_pQuestData->FindQuest(pMapInfo->QuestIndexForWarp);
		if(pQuest)
		{
			char buf[512];
			ZERO_MEMORY(buf);
			wsprintf(buf, STRMSG_C_050818_0010, pQuest->QuestName); //"'%s' �̼� �Ϸ� �� ��ݰ���!"
			g_pGameMain->AddMsgBox( buf, _MESSAGE);
		}
		else
		{
//			g_pD3dApp->StartFadeEffect(TRUE,3,D3DCOLOR_ARGB(0,0,0,0));			
//			g_pCharacterChild->FineObjectTakeOff();							
			g_pGameMain->GoWarpMapChange(0);
		}
	}	
}
void CINFMissionMain::OnClickGoMissionMap()
{	
	// ��� �̵� ���� �˻�
	if(!CheckMissionStart())
	{
		return;
	}
	CQuest *pProgressMission = g_pQuestData->GetProgressMission();
	if(NULL == pProgressMission)
	{
		return;
	}
	g_pGameMain->GoWarpMapChange(pProgressMission->QuestIndex);		

}

int CINFMissionMain::OnMouseMove(WPARAM wParam, LPARAM lParam)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_pD3dApp->GetHwnd(), &pt);
	CheckMouseReverse(&pt);	
	
	m_pGoMapBtn->OnMouseMove(pt);	
	m_pGoMissionMapBtn->OnMouseMove(pt);
#ifdef _RAT_FFA
	m_pGoFFABtn->OnMouseMove(pt);
#endif

	return INF_MSGPROC_NORMAL;	
}

BOOL CINFMissionMain::IsShowWnd(int nShowWnd)
{
	if(m_nShowMissionWnd & (1<<nShowWnd))
	{
		return TRUE;
	}
	return FALSE;
}

void CINFMissionMain::RenderMissionINGInfo()
{
	if(IsShowWnd(MISSOIN_SHOW_SEL_INFLUENCE))
	{
		return;
	}
	CQuest *pQuestInfo = g_pQuestData->GetProgressMission();
	if(NULL == pQuestInfo)
	{
		return;
	}
	
	int nLineCount = 0;		// ���� ����
	int nbreak = 0;		// ���� �극��ũ
	char buf[128];
	int nCount = 0;
	vector<int> nVecItemNum;
	int nItemNum = 0;
	nVecItemNum.clear();
	
	// �̼� �̸� ǥ��
	// 2014-07-02 by ymjoo DrawText ���� ���� �۾� (�����߹̼�)
#ifdef C_DRAWTEXT_UPGRADE_YMJOO
	m_pMissionINGFont[min(9, nLineCount)]->DrawText(MISSION_VIEW_INFO_POSX, 
													20 + (nLineCount * MISSION_FONT_HEIGHT_GAB), 
													GUI_FONT_COLOR_W, pQuestInfo->QuestName);
#else
 	m_pMissionINGFont->DrawText(MISSION_VIEW_INFO_POSX, 
 					20+(nLineCount*MISSION_FONT_HEIGHT_GAB), 
 					GUI_FONT_COLOR_W, 
 					pQuestInfo->QuestName);
#endif
	// END 2014-07-02 by ymjoo DrawText ���� ���� �۾� (�����߹̼�)
	nLineCount++;
	
	// 2014-02-19 by ymjoo ����Ʈ ��ũ��Ʈ �߰� - ������ ���
	// ���� ��� ������
	vector<ITEM_W_COUNT>::iterator itUseItem = pQuestInfo->TargetUseItemVector.begin();
	list<string> sQuestUseItemSameItemCheckList;
	while(itUseItem != pQuestInfo->TargetUseItemVector.end())
	{
		if(nbreak>3)
			break;
		
		if(itUseItem->Count < 0)
		{
			itUseItem++;
			continue;
		}
		
		ITEM* pItem = g_pDatabase->GetServerItemInfo(itUseItem->ItemNum);
		if(pItem)
		{
			bool samecheck = false;
			for(list<string>::iterator itsq = sQuestUseItemSameItemCheckList.begin() ; sQuestUseItemSameItemCheckList.end() != itsq ; ++itsq)
			{
				string sbuf = buf;
				if(*itsq == sbuf)
				{
					samecheck = true;
					break;
				}
			}
			if(samecheck)
			{
				itUseItem++;
				continue;
			}
			
			ZERO_MEMORY(buf);
			
			if(IS_SKILL_ITEM(pItem->Kind))
			{
				wsprintf(buf, STRMSG_C_090112_0203, pItem->ItemName, itUseItem->Count);
			}
			else
			{
				wsprintf(buf, STRMSG_C_090112_0203, pItem->ItemName, itUseItem->Count);
			}
			// 2014-07-02 by ymjoo DrawText ���� ���� �۾� (�����߹̼�)
#ifdef C_DRAWTEXT_UPGRADE_YMJOO
			m_pMissionINGFont[min(9, nLineCount)]->DrawText(MISSION_VIEW_INFO_POSX, 
															20 + (nLineCount * MISSION_FONT_HEIGHT_GAB), 
															GUI_FONT_COLOR_W, buf);
#else
			m_pMissionINGFont->DrawText(MISSION_VIEW_INFO_POSX, 20+(nLineCount*MISSION_FONT_HEIGHT_GAB), GUI_FONT_COLOR_W, buf);
#endif
			// END 2014-07-02 by ymjoo DrawText ���� ���� �۾� (�����߹̼�)
			sQuestUseItemSameItemCheckList.push_back(buf);
			nCount = itUseItem->Count;
			nVecItemNum.push_back(itUseItem->ItemNum);
			nLineCount++;
			nbreak++;
		}
#ifdef _DEBUG
		else if(NULL == pItem)
		{
			ZERO_MEMORY(buf);
			wsprintf(buf, "ItemNum : %d Check", itUseItem->ItemNum);
			// 2014-07-02 by ymjoo DrawText ���� ���� �۾� (�����߹̼�)
#ifdef C_DRAWTEXT_UPGRADE_YMJOO
			m_pMissionINGFont[min(9, nLineCount)]->DrawText(MISSION_VIEW_INFO_POSX, 
															20 + (nLineCount * MISSION_FONT_HEIGHT_GAB), 
															GUI_FONT_COLOR_W, buf);
#else
			m_pMissionINGFont->DrawText(MISSION_VIEW_INFO_POSX, 20+(nLineCount*MISSION_FONT_HEIGHT_GAB), GUI_FONT_COLOR_W, buf);
#endif
			// END 2014-07-02 by ymjoo DrawText ���� ���� �۾� (�����߹̼�)
			nLineCount++;
			nbreak++;
		}
#endif
		itUseItem++;
	}
	// END 2014-02-19 by ymjoo ����Ʈ ��ũ��Ʈ �߰� - ������ ���

	// ���� �ʿ� ������
	vector<ITEM_W_COUNT>::iterator it = pQuestInfo->TargetItemVector.begin();
	while(it != pQuestInfo->TargetItemVector.end())
	{
		if(nbreak>3)
			break;
		
		if(it->Count < 0)
		{// 2007-03-15 by dgwoo ��ġ������ ���̴� ����Ÿ
			it++;
			continue;
		}
		//////////////////////////////////////////////////////////////////////////			
		ITEM* pItem = g_pGameMain->GetServerItemInfo(it->ItemNum);
		if(pItem)
		{				
			ZERO_MEMORY(buf);
			// 2009-01-12 by bhsohn �Ϻ� �߰� ��������
			//wsprintf(buf, STRMSG_C_050726_0002, pItem->ItemName, (*it).Count); //"��ǥ:%s %d��"
			wsprintf(buf, STRMSG_C_090112_0203, pItem->ItemName, (*it).Count); //"��ǥ:%s %d��"
			// end 2009-01-12 by bhsohn �Ϻ� �߰� ��������
			// 2014-07-02 by ymjoo DrawText ���� ���� �۾� (�����߹̼�)
#ifdef C_DRAWTEXT_UPGRADE_YMJOO
			m_pMissionINGFont[min(9, nLineCount)]->DrawText(MISSION_VIEW_INFO_POSX, 
															20 + (nLineCount * MISSION_FONT_HEIGHT_GAB), 
															GUI_FONT_COLOR_W, buf);
#else
			m_pMissionINGFont->DrawText(MISSION_VIEW_INFO_POSX, 20+(nLineCount*MISSION_FONT_HEIGHT_GAB), GUI_FONT_COLOR_W, buf);
#endif
			// END 2014-07-02 by ymjoo DrawText ���� ���� �۾� (�����߹̼�)
			nCount = it->Count;
			nVecItemNum.push_back(it->ItemNum);
			nLineCount++;
			nbreak++;
		}			
#ifdef _DEBUG
		else if(NULL == pItem)
		{
			ZERO_MEMORY(buf);
			wsprintf(buf, "ItemNum : %d Check",it->ItemNum);
			// 2014-07-02 by ymjoo DrawText ���� ���� �۾� (�����߹̼�)
#ifdef C_DRAWTEXT_UPGRADE_YMJOO
			m_pMissionINGFont[min(9, nLineCount)]->DrawText(MISSION_VIEW_INFO_POSX, 
															20 + (nLineCount * MISSION_FONT_HEIGHT_GAB), 
															GUI_FONT_COLOR_W, buf);
#else
			m_pMissionINGFont->DrawText(MISSION_VIEW_INFO_POSX, 20+(nLineCount*MISSION_FONT_HEIGHT_GAB), GUI_FONT_COLOR_W, buf);
#endif
			// END 2014-07-02 by ymjoo DrawText ���� ���� �۾� (�����߹̼�)
			nLineCount++;
			nbreak++;
		}
#endif
		//////////////////////////////////////////////////////////////////////////
		it++;
	}
	
	// ���� ��ǥ ����
	vector<MONSTER_W_COUNT>::iterator itMonC = pQuestInfo->TargetMonsterVector.begin();
	while(itMonC != pQuestInfo->TargetMonsterVector.end())
	{
		if(0 < itMonC->Count )
		{
			MEX_MONSTER_INFO * pTempIn = g_pGameMain->CheckMonsterInfo((*itMonC).MonsterUniqueNumber);
			ZERO_MEMORY(buf);
			// 2009-01-12 by bhsohn �Ϻ� �߰� ��������
			//wsprintf( buf, STRMSG_C_050726_0002,pTempIn->MonsterName, (*itMonC).Count ); //"\\e%s\\e \\w%d��/%d��\\w"
			wsprintf( buf, STRMSG_C_090112_0203,pTempIn->MonsterName, (*itMonC).Count ); //"\\e%s\\e \\w%d��/%d��\\w"
			// end 2009-01-12 by bhsohn �Ϻ� �߰� ��������
			// 2014-07-02 by ymjoo DrawText ���� ���� �۾� (�����߹̼�)
#ifdef C_DRAWTEXT_UPGRADE_YMJOO
			m_pMissionINGFont[min(9, nLineCount)]->DrawText(MISSION_VIEW_INFO_POSX, 
															20 + (nLineCount * MISSION_FONT_HEIGHT_GAB), 
															GUI_FONT_COLOR_W, buf);
#else
			m_pMissionINGFont->DrawText(MISSION_VIEW_INFO_POSX, 20+(nLineCount*MISSION_FONT_HEIGHT_GAB), GUI_FONT_COLOR_W, buf);
#endif
			// END 2014-07-02 by ymjoo DrawText ���� ���� �۾� (�����߹̼�)
			nLineCount++;
		}
		itMonC++;
	}
	
	nbreak = 0;
	vector<ITEM_W_COUNT_MAP_AREA>::iterator it2 = pQuestInfo->TargetMonsterItemVector.begin();
	while(it2 != pQuestInfo->TargetMonsterItemVector.end())
	{
		if(nbreak>3)
			break;
		
		if(it2->ItemWithCount.Count < 0)
		{// 2007-03-15 by dgwoo ��ġ������ ������ ����Ÿ 
			it2++;
			continue;
		}
		//////////////////////////////////////////////////////////////////////////			
		ITEM* pItem = g_pGameMain->GetServerItemInfo(it2->ItemWithCount.ItemNum);
		if(pItem)
		{			
			if(pQuestInfo->vecQuestDropItem.size()<0)
			{
				ZERO_MEMORY(buf);
				// 2009-01-12 by bhsohn �Ϻ� �߰� ��������
				//wsprintf(buf, STRMSG_C_050726_0002, pItem->ItemName, it2->ItemWithCount.Count); //"��ǥ:%s %d��"				
				wsprintf(buf, STRMSG_C_090112_0203, pItem->ItemName, it2->ItemWithCount.Count); //"��ǥ:%s %d��"				
				// end 2009-01-12 by bhsohn �Ϻ� �߰� ��������
				
				// 2014-07-02 by ymjoo DrawText ���� ���� �۾� (�����߹̼�)
#ifdef C_DRAWTEXT_UPGRADE_YMJOO
				m_pMissionINGFont[min(9, nLineCount)]->DrawText(MISSION_VIEW_INFO_POSX, 
																20 + (nLineCount * MISSION_FONT_HEIGHT_GAB), 
																GUI_FONT_COLOR_W, buf);
#else
 				m_pMissionINGFont->DrawText(MISSION_VIEW_INFO_POSX, 
 					20+(nLineCount*MISSION_FONT_HEIGHT_GAB), GUI_FONT_COLOR_W,
 					buf);
#endif
				// END 2014-07-02 by ymjoo DrawText ���� ���� �۾� (�����߹̼�)
				
				nCount = it2->ItemWithCount.Count;
				nVecItemNum.push_back(it2->ItemWithCount.ItemNum);
				nbreak++;
				nLineCount++;
			}
			
			vector<QUEST_DROP_ITEM>::iterator itItem = pQuestInfo->vecQuestDropItem.begin();
			while(itItem != pQuestInfo->vecQuestDropItem.end())
			{
				QUEST_DROP_ITEM *pTemp = &*itItem;
				if(pItem->ItemNum == pTemp->ItemNumber)
				{
					MEX_MONSTER_INFO * pMonster = g_pGameMain->CheckMonsterInfo(pTemp->MonsterUniqueNumber);							
					if(pMonster)
					{
						ZERO_MEMORY(buf);
						// 2009-01-12 by bhsohn �Ϻ� �߰� ��������
// 						wsprintf(buf, STRMSG_C_050818_0011, pItem->ItemName,pMonster->MonsterName,
// 							it2->ItemWithCount.Count); //"��ǥ:%s %d��"						
						wsprintf(buf, STRMSG_C_090112_0205, pItem->ItemName,pMonster->MonsterName,
							it2->ItemWithCount.Count); //"��ǥ:%s %d��"						
						// end 2009-01-12 by bhsohn �Ϻ� �߰� ��������
						
						// 2014-07-02 by ymjoo DrawText ���� ���� �۾� (�����߹̼�)
#ifdef C_DRAWTEXT_UPGRADE_YMJOO
						m_pMissionINGFont[min(9, nLineCount)]->DrawText(MISSION_VIEW_INFO_POSX, 
																		20 + (nLineCount * MISSION_FONT_HEIGHT_GAB), 
																		GUI_FONT_COLOR_W, buf);
#else
 						m_pMissionINGFont->DrawText(MISSION_VIEW_INFO_POSX, 
 							20+(nLineCount*MISSION_FONT_HEIGHT_GAB), GUI_FONT_COLOR_W,
 							buf);
#endif
						// END 2014-07-02 by ymjoo DrawText ���� ���� �۾� (�����߹̼�)
						
						nCount = it2->ItemWithCount.Count;
						nVecItemNum.push_back(it2->ItemWithCount.ItemNum);
						nbreak++;
						nLineCount++;						
					}
				}
				
				itItem++;
			}				

			// 2007-07-30 by bhsohn ����Ʈ ���� ��� ���¿� ���� ���� ǥ�� �ȵǴ� ���� ����			
			vector<QUEST_DROP_CHARACTER2ITEM>::iterator itCharacter = pQuestInfo->vecQuestDropCharacter2Item.begin();
			while(itCharacter != pQuestInfo->vecQuestDropCharacter2Item.end())
			{
				QUEST_DROP_CHARACTER2ITEM *pItemInfoMap = &*itCharacter;
				if(pItem->ItemNum == pItemInfoMap->Character2Item.ItemNumber)
				{					
					ZERO_MEMORY(buf);
					// 2009-01-12 by bhsohn �Ϻ� �߰� ��������
					//wsprintf(buf, STRMSG_C_050726_0002, pItem->ItemName, it2->ItemWithCount.Count); //"��ǥ:%s %d��"						
					wsprintf(buf, STRMSG_C_090112_0203, pItem->ItemName, it2->ItemWithCount.Count); //"��ǥ:%s %d��"						
					// end 2009-01-12 by bhsohn �Ϻ� �߰� ��������
					
					// 2014-07-02 by ymjoo DrawText ���� ���� �۾� (�����߹̼�)
#ifdef C_DRAWTEXT_UPGRADE_YMJOO
					m_pMissionINGFont[min(9, nLineCount)]->DrawText(MISSION_VIEW_INFO_POSX, 
																	20 + (nLineCount * MISSION_FONT_HEIGHT_GAB), 
																	GUI_FONT_COLOR_W, buf);
#else
 					m_pMissionINGFont->DrawText(MISSION_VIEW_INFO_POSX, 
 						20+(nLineCount*MISSION_FONT_HEIGHT_GAB), GUI_FONT_COLOR_W,
 						buf);
#endif
					// END 2014-07-02 by ymjoo DrawText ���� ���� �۾� (�����߹̼�)
					
					nCount = it2->ItemWithCount.Count;
					nVecItemNum.push_back(it2->ItemWithCount.ItemNum);
					nbreak++;
					nLineCount++;						
					
				}
				itCharacter++;
			}
			// end 2007-07-30 by bhsohn ����Ʈ ���� ��� ���¿� ���� ���� ǥ�� �ȵǴ� ���� ����			
		}
#ifdef _DEBUG
		else if(NULL == pItem)
		{
			ZERO_MEMORY(buf);
			wsprintf(buf, "ItemNum : %d Check",it2->ItemWithCount.ItemNum);
			// 2014-07-02 by ymjoo DrawText ���� ���� �۾� (�����߹̼�)
#ifdef C_DRAWTEXT_UPGRADE_YMJOO
			m_pMissionINGFont[min(9, nLineCount)]->DrawText(MISSION_VIEW_INFO_POSX, 
															20 + (nLineCount * MISSION_FONT_HEIGHT_GAB), 
															GUI_FONT_COLOR_W, buf);
#else
			m_pMissionINGFont->DrawText(MISSION_VIEW_INFO_POSX, 20+(nLineCount*MISSION_FONT_HEIGHT_GAB), GUI_FONT_COLOR_W, buf);
#endif
			// END 2014-07-02 by ymjoo DrawText ���� ���� �۾� (�����߹̼�)
			nbreak++;
			nLineCount++;
		}
#endif
		//////////////////////////////////////////////////////////////////////////
		it2++;
	}
	// ���� NPC �̸�
	if(strlen(pQuestInfo->TargetMeetNPCInfo.NPCName)>0)
	{
		ZERO_MEMORY(buf);			
		wsprintf(buf, STRMSG_C_050726_0003, pQuestInfo->TargetMeetNPCInfo.NPCName); // "[%s]�� ã�ư���!"
		// 2014-07-02 by ymjoo DrawText ���� ���� �۾� (�����߹̼�)
#ifdef C_DRAWTEXT_UPGRADE_YMJOO
		m_pMissionINGFont[min(9, nLineCount)]->DrawText(MISSION_VIEW_INFO_POSX, 
														20 + (nLineCount * MISSION_FONT_HEIGHT_GAB), 
														GUI_FONT_COLOR_W, buf);
#else
		m_pMissionINGFont->DrawText(MISSION_VIEW_INFO_POSX, 20+(nLineCount*MISSION_FONT_HEIGHT_GAB), GUI_FONT_COLOR_W, buf);
#endif
		// END 2014-07-02 by ymjoo DrawText ���� ���� �۾� (�����߹̼�)
		nLineCount++;
	}
	
	// ���� �������ϴ� ������Ʈ
	// ���� ��� ���� ��������Ʈ ���
	if(pQuestInfo->TargetMeetObjectMapArea.MapIndex)
	{
		MAP_INFO* pMapInfo = g_pGameMain->GetMapInfo(pQuestInfo->TargetMeetObjectMapArea.MapIndex);
		if(pMapInfo)
		{
			ZERO_MEMORY(buf);			
			wsprintf(buf, STRMSG_C_050726_0004, pMapInfo->MapName); //"[%s]�� ����϶�!"
			// 2014-07-02 by ymjoo DrawText ���� ���� �۾� (�����߹̼�)
#ifdef C_DRAWTEXT_UPGRADE_YMJOO
			m_pMissionINGFont[min(9, nLineCount)]->DrawText(MISSION_VIEW_INFO_POSX, 
															20 + (nLineCount * MISSION_FONT_HEIGHT_GAB), 
															GUI_FONT_COLOR_W, buf);
#else
			m_pMissionINGFont->DrawText(MISSION_VIEW_INFO_POSX, 20+(nLineCount*MISSION_FONT_HEIGHT_GAB), GUI_FONT_COLOR_W, buf);
#endif
			// END 2014-07-02 by ymjoo DrawText ���� ���� �۾� (�����߹̼�)
			nLineCount++;
		}
	}
	
	// ���� ��ǥ ������
	if(pQuestInfo->QuestEndType == QUEST_END_TYPE_LEVEL_UP)
	{
		ZERO_MEMORY(buf);			
		wsprintf(buf, STRMSG_C_050805_0001); // "������ �Ѵܰ� �ø�����"
		// 2014-07-02 by ymjoo DrawText ���� ���� �۾� (�����߹̼�)
#ifdef C_DRAWTEXT_UPGRADE_YMJOO
		m_pMissionINGFont[min(9, nLineCount)]->DrawText(MISSION_VIEW_INFO_POSX, 
														20 + (nLineCount * MISSION_FONT_HEIGHT_GAB), 
														GUI_FONT_COLOR_W, buf);
#else
		m_pMissionINGFont->DrawText(MISSION_VIEW_INFO_POSX, 20+(nLineCount*MISSION_FONT_HEIGHT_GAB), GUI_FONT_COLOR_W, buf);
#endif
		// END 2014-07-02 by ymjoo DrawText ���� ���� �۾� (�����߹̼�)
		nLineCount++;
	}
	
	// ����Ʈ �����ð� ǥ��
	if(g_pGameMain->m_bQuestLimitTimeView)
	{
		ZERO_MEMORY(buf);					
		// 2008-04-07 by bhsohn ����Ʈ �ð� �����Ǵ� ���� ó��
//		if(g_pGameMain->m_nTimeSecond >= 0)		
//		{
//			wsprintf(buf, STRMSG_C_INTERFACE_0020, g_pGameMain->m_nTimeSecond/60, g_pGameMain->m_nTimeSecond%60);//"[�����ð�] %2.d�� %2.d��"
//			m_pMissionINGFont->DrawText(MISSION_VIEW_INFO_POSX, 20+(nLineCount*MISSION_FONT_HEIGHT_GAB), GUI_FONT_COLOR_W, buf);
//			nLineCount++;
//		}
		if(g_pGameMain->GetQuestTimeElapse() >= 0)
		{
			int nTimeSecond = (int)g_pGameMain->GetQuestTimeElapse();
			wsprintf(buf, STRMSG_C_INTERFACE_0020, nTimeSecond/60, nTimeSecond%60);//"[�����ð�] %2.d�� %2.d��"
			// 2014-07-02 by ymjoo DrawText ���� ���� �۾� (�����߹̼�)
#ifdef C_DRAWTEXT_UPGRADE_YMJOO
			m_pMissionINGFont[min(9, nLineCount)]->DrawText(MISSION_VIEW_INFO_POSX, 
															20 + (nLineCount * MISSION_FONT_HEIGHT_GAB), 
															GUI_FONT_COLOR_W, buf);
#else
			m_pMissionINGFont->DrawText(MISSION_VIEW_INFO_POSX, 20+(nLineCount*MISSION_FONT_HEIGHT_GAB), GUI_FONT_COLOR_W, buf);
#endif
			// END 2014-07-02 by ymjoo DrawText ���� ���� �۾� (�����߹̼�)
			nLineCount++;
		}
		// end 2008-04-07 by bhsohn ����Ʈ �ð� �����Ǵ� ���� ó��
	}
	// 2007-04-10 by dgwoo �ͽ� �������� ������.
	if(pQuestInfo->TargetMixItemTarget.Count > 0)
	{
		ZERO_MEMORY(buf);	
		ITEM* pItem = g_pGameMain->GetServerItemInfo(pQuestInfo->TargetMixItemTarget.ItemNum);
		if(pItem != NULL)
		{
			wsprintf(buf, STRMSG_C_070410_0100,pItem->ItemName);	//"[���丮]���� %s(��)�� �����϶�"
			// 2014-07-02 by ymjoo DrawText ���� ���� �۾� (�����߹̼�)
#ifdef C_DRAWTEXT_UPGRADE_YMJOO
			m_pMissionINGFont[min(9, nLineCount)]->DrawText(MISSION_VIEW_INFO_POSX, 
															20 + (nLineCount * MISSION_FONT_HEIGHT_GAB), 
															GUI_FONT_COLOR_W, buf);
#else
			m_pMissionINGFont->DrawText(MISSION_VIEW_INFO_POSX, 20+(nLineCount*MISSION_FONT_HEIGHT_GAB), GUI_FONT_COLOR_W, buf);
#endif
			// END 2014-07-02 by ymjoo DrawText ���� ���� �۾� (�����߹̼�)
			nLineCount++;
		}
	}
	
	// ����Ʈ ������ � ����
	vector<int>::iterator vecInt = nVecItemNum.begin();
	while(vecInt != nVecItemNum.end())
	{
		ITEM_GENERAL *pItem = g_pStoreData->FindItemInInventoryByItemNum(*vecInt);
		if( pItem )
		{
			ZERO_MEMORY(buf);
			wsprintf( buf, STRMSG_C_050726_0005, pItem->ItemInfo->ItemName, pItem->CurrentCount );//"\\e%s\\e \\w%d��/%d\\w"
			// 2014-07-02 by ymjoo DrawText ���� ���� �۾� (�����߹̼�)
#ifdef C_DRAWTEXT_UPGRADE_YMJOO
			m_pMissionINGFont[min(9, nLineCount)]->DrawText(MISSION_VIEW_INFO_POSX, 
															20 + (nLineCount * MISSION_FONT_HEIGHT_GAB), 
															GUI_FONT_COLOR_W, buf);
#else
			m_pMissionINGFont->DrawText(MISSION_VIEW_INFO_POSX, 20+(nLineCount*MISSION_FONT_HEIGHT_GAB), GUI_FONT_COLOR_W, buf);
#endif
			// END 2014-07-02 by ymjoo DrawText ���� ���� �۾� (�����߹̼�)
			nLineCount++;
		}
		vecInt++;
	}
	
	// ����Ʈ ���͸� ����� ��
	vector<MONSTER_W_COUNT>::iterator itMon = pQuestInfo->TargetMonsterVector.begin();
	while(itMon != pQuestInfo->TargetMonsterVector.end())
	{
		vector<Quest_MonsterInfo>::iterator it = g_pQuestData->m_vecQuestMonsterCount.begin();
		while(it != g_pQuestData->m_vecQuestMonsterCount.end())
		{
			MEX_MONSTER_INFO * pTempInfo = g_pGameMain->CheckMonsterInfo((*it).nMonsterUnitkind);
			if(pTempInfo)
			{
				if((*itMon).MonsterUniqueNumber == (*it).nMonsterUnitkind)
				{
					if(0 < itMon->Count)
					{
						ZERO_MEMORY(buf);
						wsprintf( buf, STRMSG_C_051026_0001,pTempInfo->MonsterName, (*it).nMonsterCount, (*itMon).Count ); //"\\e%s\\e \\w%d��/%d��\\w"
						// 2014-07-02 by ymjoo DrawText ���� ���� �۾� (�����߹̼�)
#ifdef C_DRAWTEXT_UPGRADE_YMJOO
						m_pMissionINGFont[min(9, nLineCount)]->DrawText(MISSION_VIEW_INFO_POSX, 
																		20 + (nLineCount * MISSION_FONT_HEIGHT_GAB), 
																		GUI_FONT_COLOR_W, buf);
#else
						m_pMissionINGFont->DrawText(MISSION_VIEW_INFO_POSX, 20+(nLineCount*MISSION_FONT_HEIGHT_GAB), GUI_FONT_COLOR_W, buf);
#endif
						// END 2014-07-02 by ymjoo DrawText ���� ���� �۾� (�����߹̼�)
						nLineCount++;
					}
				}					
			}
			it++;
		}
		itMon++;
	}	
}

void CINFMissionMain::SetMissionEnterShop(BOOL bEnterShopState)
{
	m_pINFMissionTreeInfo->SetMissionEnterShop(bEnterShopState);
}

BOOL CINFMissionMain::IsShowTreeWnd()
{	
	return IsShowWnd(MISSOIN_SHOW_TREE);
}

void CINFMissionMain::ShowTreeWnd(BOOL bFlag, BOOL bBtnClick)
{	
	if(bFlag)
	{
		CQuest* pProgressMission = g_pQuestData->GetProgressMission();
		INT nQuestIdx = 0;
		if(pProgressMission)
		{
			nQuestIdx = pProgressMission->QuestIndex;
		}

		m_nShowMissionWnd |= (1<<MISSOIN_SHOW_TREE);
		m_nShowMissionWnd &= ~(1<<MISSOIN_SHOW_POPUP);	
		RefreshMission(bBtnClick, nQuestIdx);		
		if(bBtnClick)
		{
			g_pD3dApp->m_pSound->PlayD3DSound(SOUND_OPEN_MENU, g_pShuttleChild->m_vPos, FALSE);			
		}
	}
	else
	{
		m_nShowMissionWnd &= ~(1<<MISSOIN_SHOW_TREE);
		//m_pINFMissionTreeInfo->InitMissionInfo();		
		if(bBtnClick)
		{
			g_pD3dApp->m_pSound->PlayD3DSound(SOUND_CLOSE_MENU, g_pShuttleChild->m_vPos, FALSE);
		}
	}	
}
void CINFMissionMain::ShowMissionPopWnd(BOOL bShow, int nPossibleQuestIdx)
{	
	if(bShow)
	{
		m_nShowMissionWnd |= (1<<MISSOIN_SHOW_POPUP);
		m_nShowMissionWnd &= ~(1<<MISSOIN_SHOW_TREE);
		m_pINFMissionPopupInfo->InitPopupInfo(nPossibleQuestIdx);
	}
	else
	{
		m_nShowMissionWnd &= ~(1<<MISSOIN_SHOW_POPUP);		
	}
}

void CINFMissionMain::SetPosMissionSearchStart(BOOL nstate)
{	
	m_bSearchPosQuest = nstate; 
}
void CINFMissionMain::SetPosMissionInfo(CQuest* pQuest)
{
	m_pHidePosQuest = pQuest;
}

void CINFMissionMain::SetPosMissionComplete(BOOL bFlag)
{
	m_bPosMissionComplete = bFlag; 
}

// ���¹̼� ����
BOOL CINFMissionMain::GetInfluenceMission() 
{
	return m_bInfluenceFlag;
}	

void CINFMissionMain::SetInfluenceMission(BOOL bFlag, float fANIPercent, float fVANPercent)
{
	if(bFlag)
	{
		m_nShowMissionWnd |= (1<<MISSOIN_SHOW_SEL_INFLUENCE);	
		m_pINFMissionSelInfluence->InitInfluenceMission();
	}
	else
	{
		m_nShowMissionWnd &= ~(1<<MISSOIN_SHOW_SEL_INFLUENCE);	
		m_pINFMissionSelInfluence->HideSelInfluence();
	}
	
	// ���¼��� �̼� �����κ� ( TRUE ������ �ٸ��̼� ���� �Ұ�, ����ϱ� �Ұ�)
	m_fANIInflDistributionPercent = fANIPercent;
	m_fVCNInflDistributionPercent = fVANPercent;
	m_bInfluenceFlag = bFlag;
//	if(nFlag)
//	{
//		MissionProcFlag(FALSE);
//		InitInfluenceMission();	
//	}
}
// ���� ����

void CINFMissionMain::RefreshMission(BOOL bClick, INT QuestIndex)
{	
	// ��ư ���� ����
	m_nMyShuttleCharacter = -1;
	m_pINFMissionTreeInfo->RefreshMission(bClick, QuestIndex);
}

void CINFMissionMain::MissionEnd(DWORD dMissionIndex)
{
	FLOG( "CINFMissionInfo::MissionEnd()" );
	
	if(dMissionIndex == NULL)
		return;

	g_pQuestData->SendFieldSocketQuestRequestSuccess(dMissionIndex);
}

void CINFMissionMain::SelectNextMission(INT nQuestIndex)
{
	m_pINFMissionTreeInfo->SelectNextMission(nQuestIndex);	
}


BOOL CINFMissionMain::IsLevelSecnQuest(BYTE byUpLevel, int nSuccessQuestIdx, int* o_nPossibleQuestIdx)
{	
	// ��� �̼� �ε��� �ѹ�.
	vector<int>		vecQuestIndex;	
	vecQuestIndex.clear();

	// 2008-12-29 by bhsohn ��������, �̼ǿ��۷����� �ȶߴ� ���� ����
// 	CQuest* pSueccessQuest = g_pQuestData->FindQuest(nSuccessQuestIdx);		
// 	if(NULL == pSueccessQuest)
// 	{
// 		// ���� �Ϸ��� ����Ʈ�̴�.
// 		return FALSE;
// 	}
	CQuest* pSueccessQuest = NULL;
	if(nSuccessQuestIdx != -1)
	{
		pSueccessQuest = g_pQuestData->FindQuest(nSuccessQuestIdx);		
		if(NULL == pSueccessQuest)
		{
			// ���� �Ϸ��� ����Ʈ�̴�.
			return FALSE;
		}
	}
	// end 2008-12-29 by bhsohn ��������, �̼ǿ��۷����� �ȶߴ� ���� ����
	
	// �Ϸ�� ����Ʈ ����Ʈ ������
	LoadQuestList(&vecQuestIndex);

	// 2012-11-29 by bhsohn ȥ���� �縷 ����Ʈ �ȳ����� ���׼���
	vector<structQuestInfo>	vecTmpQuest;	
	vecTmpQuest.clear();
	// END 2012-11-29 by bhsohn ȥ���� �縷 ����Ʈ �ȳ����� ���׼���

	vector<int>::iterator it = vecQuestIndex.begin();
	while(it != vecQuestIndex.end())
	{
		CQuest* pQuest = g_pQuestData->FindQuest(*it);		
		if(NULL == pQuest)
		{
			it++;
			continue;
		}
		int nQuestIdx = pQuest->QuestIndex;
		if(QUEST_KIND_SCENARIO != pQuest->QuestKind)
		{
			it++;
			continue;			
		}
		// �Ϸ�� ����Ʈ�� �˻����Ѵ�..
		if(g_pQuestData->IsQuestCompleted(pQuest->QuestIndex))
		{
			it++;
			continue;			
		}
		// 2008-12-29 by bhsohn ��������, �̼ǿ��۷����� �ȶߴ� ���� ����
		//if(pSueccessQuest->QuestEpisodeType != pQuest->QuestEpisodeType)
		if((nSuccessQuestIdx != -1) 
			&& pSueccessQuest 
			&& pSueccessQuest->QuestEpisodeType != pQuest->QuestEpisodeType)
		{
			// ����Ʈ ���Ǽҵ� Ÿ���� ���� �ٸ��� �˻����Ѵ�.
			it++;
			continue;			
		}
		if(byUpLevel < pQuest->ReqLevel.Min)
		{			
//			return FALSE;		// 2012-11-29 by bhsohn ȥ���� �縷 ����Ʈ �ȳ����� ���׼���
		}		
		else 
		{
			(*o_nPossibleQuestIdx) = nQuestIdx;
			
			// 2012-11-29 by bhsohn ȥ���� �縷 ����Ʈ �ȳ����� ���׼���
			// �Ҽ� �ִ� �ó����� ����Ʈ�� ���ߴ�.
//			return TRUE;
			// �ӽ� ���ۿ� ����
			if(byUpLevel <= pQuest->ReqLevel.Max)
			{
				structQuestInfo struTmpInfo;
				memset(&struTmpInfo, 0x00, sizeof(structQuestInfo));

				struTmpInfo.nQuestIndex = nQuestIdx;
				struTmpInfo.nMinLevel = pQuest->ReqLevel.Min;
				struTmpInfo.nMaxLevel = pQuest->ReqLevel.Max;

				vecTmpQuest.push_back(struTmpInfo);
			}
			// END 2012-11-29 by bhsohn ȥ���� �縷 ����Ʈ �ȳ����� ���׼���
		}
		it++;
	}

	// 2012-11-29 by bhsohn ȥ���� �縷 ����Ʈ �ȳ����� ���׼���
	// ���������� ����	
	if(vecTmpQuest.size() >0)
	{
		sort(vecTmpQuest.begin(), vecTmpQuest.end(), QuestIdx_Sort_Level());
		vector<structQuestInfo>::iterator it = vecTmpQuest.begin();
		structQuestInfo struTmp = (*it);

		(*o_nPossibleQuestIdx) = struTmp.nQuestIndex;
		return TRUE;
	}
	// END 2012-11-29 by bhsohn ȥ���� �縷 ����Ʈ �ȳ����� ���׼���

	return FALSE;
}

void CINFMissionMain::LoadQuestList(vector<int>* pVecQuestIndex)
{	 
	CHARACTER myShuttleInfo = g_pShuttleChild->GetMyShuttleInfo();
	
	// ���� �츮 ������ ��ü ����Ʈ�� ���´�.
	vector<int> vecQuestInflue;
	vecQuestInflue = g_pQuestData->GetRaceQuestIndex(myShuttleInfo.InfluenceType);
	
	// ��ü �̼��� �������� �κ�
	vector<int> vecQuestTemp;
	vecQuestTemp = g_pQuestData->GetRaceQuestIndex(INFLUENCE_TYPE_ALL_MASK);	
	vector<int>::iterator itQuest = vecQuestTemp.begin();
	while(itQuest != vecQuestTemp.end())
	{
		if(g_pQuestData->IsQuestCompleted(*itQuest))
		{
			// ��ȿ�� ���� ��������� ������ ����� �ٲ��� �ʰ� ������ Ʋ������ 
			// �Ϸ� �̼��� �����ֱ� ���� ���
			// �Ŀ� ��ü ���
			BOOL nQFlag = TRUE;
			vector<int>::iterator itQuestSolve = vecQuestInflue.begin();
			while(itQuestSolve != vecQuestInflue.end())
			{
				if(*itQuest == *itQuestSolve)
				{
					nQFlag = FALSE;
				}
				
				itQuestSolve++;
			}
			if(nQFlag) 
			{
				pVecQuestIndex->push_back(*itQuest);
			}
		}
		itQuest++;
	}
	// �������� ��ü ���
	vector<int>::iterator itQuestSolve2 = vecQuestInflue.begin();
	while(itQuestSolve2 != vecQuestInflue.end())
	{
		pVecQuestIndex->push_back(*itQuestSolve2);
		itQuestSolve2++;
	}
}

void CINFMissionMain::SetQuestNameString(CQuest* pQuest, vector<string>* o_vecMissionName, 
											CINFImageListBox* pINFImageListBox, int nMaxString)
{
	char buf[64];
	ZERO_MEMORY(buf);	
	
	// �̸� ����	
	char strMissionNameTemp[50] = {0,};
	ZERO_MEMORY(strMissionNameTemp);		
	int nMaxLevel = pQuest->ReqLevel.Max;

	if(pQuest->ReqLevel.Max>100)
		nMaxLevel = 100;
	
	wsprintf(buf, " [Lv.%d]", pQuest->ReqLevel.Min);
	int nLevelLen = strlen(buf);
		
	strncpy( strMissionNameTemp, pQuest->QuestName, 50-nLevelLen);
	strcat( strMissionNameTemp, buf);
	
	//STRING_CULL(strMissionNameTemp, MISSION_MAX_DESC_STRING, &m_vecMissionName, m_pMissionFontRight[0]);
	pINFImageListBox->SetStringCull(0, strMissionNameTemp, o_vecMissionName, nMaxString);
}

void CINFMissionMain::SetQuestResult(CQuest* pQuest, vector<string>* o_vecPossibleDesc, 
										 CINFImageListBox* pINFImageListBox, int nMaxString)
{
	// �̼� ���
	MEX_QUEST_INFO* pCharacterQuest = g_pQuestData->FindCharacterQuest(pQuest->QuestIndex);
	if(pCharacterQuest)
	{
		if(g_pQuestData->IsQuestProgress(pQuest->QuestIndex))
		{
			// 2008-12-16 by dgwoo �̼� �������� ��츸 �߰�.
			if(pQuest->QuestPartyType == QUEST_PARTYTYPE_PARTY)
				o_vecPossibleDesc->push_back(STRMSG_C_081215_0100);
			o_vecPossibleDesc->push_back(STRMSG_C_050726_0001); //"\\y�����Ȳ\\y"
			//m_bProgressMission = TRUE;
//			STRING_CULL(pQuest->QuestNPCInfo.MidTalk, 
//				MISSION_MAX_DESC_STRING, &m_vecPossibleDesc, m_pMissionFontRight[1]);
			pINFImageListBox->SetStringCull(1, pQuest->QuestNPCInfo.MidTalk, 
													o_vecPossibleDesc, 
													nMaxString);

			o_vecPossibleDesc->push_back("          ");			
		}
		else if(g_pQuestData->IsQuestCompleted(pQuest->QuestIndex))
		{
			// 2008-12-16 by dgwoo �̼� �������� ��츸 �߰�.
			if(pQuest->QuestPartyType == QUEST_PARTYTYPE_PARTY)
				o_vecPossibleDesc->push_back(STRMSG_C_081215_0100);
			o_vecPossibleDesc->push_back(STRMSG_C_050726_0001); //"\\y�����Ȳ\\y"
//			STRING_CULL(pQuest->QuestNPCInfo.SuccessTalk, 
//				MISSION_MAX_DESC_STRING, &m_vecPossibleDesc, m_pMissionFontRight[1]);			
			pINFImageListBox->SetStringCull(1, pQuest->QuestNPCInfo.SuccessTalk, 
													o_vecPossibleDesc, 
													nMaxString);

			o_vecPossibleDesc->push_back("          ");
		}
//		���� ���� ��Ȳ�� ����
//		else if()
//		{
//			pQuest->TargetMeetNPCInfo.FailTalk;
//		}
		else
		{
			// 2008-12-16 by dgwoo �̼� �������� ��츸 �߰�.
			if(pQuest->QuestPartyType == QUEST_PARTYTYPE_PARTY)
				o_vecPossibleDesc->push_back(STRMSG_C_081215_0100);
			o_vecPossibleDesc->push_back(STRMSG_C_050726_0001); //"\\y�����Ȳ\\y"
//			STRING_CULL(pQuest->QuestNPCInfo.PreTalk, 
//				MISSION_MAX_DESC_STRING, &m_vecPossibleDesc, m_pMissionFontRight[1]);
			pINFImageListBox->SetStringCull(1, pQuest->QuestNPCInfo.PreTalk, 
													o_vecPossibleDesc, 
													nMaxString);
			o_vecPossibleDesc->push_back("          ");
//			m_bMissionStartButtonUse = FALSE;
		}
	}
	else
	{		
		if(strlen(pQuest->QuestNPCInfo.PreTalk) > 1)
		{
			// 2008-12-16 by dgwoo �̼� �������� ��츸 �߰�.
			if(pQuest->QuestPartyType == QUEST_PARTYTYPE_PARTY)
				o_vecPossibleDesc->push_back(STRMSG_C_081215_0100);
			o_vecPossibleDesc->push_back(STRMSG_C_050726_0001); //"\\y�����Ȳ\\y"
//		STRING_CULL(pQuest->QuestNPCInfo.PreTalk, 
//				MISSION_MAX_DESC_STRING, &m_vecPossibleDesc, m_pMissionFontRight[1]);
			pINFImageListBox->SetStringCull(1, pQuest->QuestNPCInfo.PreTalk, 
													o_vecPossibleDesc, 
													nMaxString);
			o_vecPossibleDesc->push_back("          ");
		}		
	}

	// 
	if(pCharacterQuest && pCharacterQuest->QuestState == QUEST_STATE_COMPLETED)
	{
		// �̼� ����
		o_vecPossibleDesc->push_back(STRMSG_C_051209_0001); //"\\y��漳��\\y"
//		STRING_CULL(pQuest->QuestDescription, 
//			MISSION_MAX_DESC_STRING, &m_vecPossibleDesc, m_pMissionFontRight[1]);
		pINFImageListBox->SetStringCull(1, pQuest->QuestDescription, 
													o_vecPossibleDesc, 
													nMaxString);

		// ��ư���� ���� ���� �߰�
		o_vecPossibleDesc->push_back("          ");
	}
	
}

void CINFMissionMain::SetGoalInfo(CQuest* pQuest, vector<string>* o_vecPossibleDesc)
{
	// 2007-07-30 by bhsohn �Ϸ�� �̼��� ��ǥ ǥ������ ����
	if(g_pQuestData->IsQuestCompleted(pQuest->QuestIndex))
	{
		// �Ϸ�� �̼��� ��ǥ ǥ������ ����
		return;
	}
	// end 2007-07-30 by bhsohn �Ϸ�� �̼��� ��ǥ ǥ������ ����



	//2011-10-27 by jhahn ����3�� ����Ʈ â ����
	if(pQuest->QuestEpisodeType != QUEST_INFINITY_TYPE_3) 
	o_vecPossibleDesc->push_back(STRMSG_C_070627_0207); //"\\y��ǥ\\y"
	//end 2011-10-27 by jhahn ����3�� ����Ʈ â ����

	int nStartDesc = o_vecPossibleDesc->size();

	int nbreak = 0;		// ���� �극��ũ
	int nCount = 0;
	int nLineCount=0;
	char buf[128];

	// 2014-02-19 by ymjoo ����Ʈ ��ũ��Ʈ �߰� - ������ ���
	// ���� ��� ������
	vector<ITEM_W_COUNT>::iterator itUseItem = pQuest->TargetUseItemVector.begin();
	list<string> sQuestUseItemSameItemCheckList;
	while(itUseItem != pQuest->TargetUseItemVector.end())
	{
		if(nbreak>3)
		{
			break;
		}
		if(itUseItem->Count < 0)
		{
			itUseItem++;
			continue;
		}
		ITEM* pItem = g_pGameMain->GetServerItemInfo(itUseItem->ItemNum);
		if(pItem)
		{
			bool samecheck = false;
			for(list<string>::iterator itsq = sQuestUseItemSameItemCheckList.begin() ; sQuestUseItemSameItemCheckList.end() != itsq ; ++itsq)
			{
				string sbuf = buf;
				if(*itsq == sbuf)
				{
					samecheck = true;
					break;
				}
			}
			if(samecheck)
			{
				itUseItem++;
				continue;
			}
			ZERO_MEMORY(buf);

			if(IS_SKILL_ITEM(pItem->Kind))
			{
				wsprintf(buf, STRMSG_C_090112_0203, pItem->ItemName, itUseItem->Count);
			}
			else
			{
				wsprintf(buf, STRMSG_C_090112_0203, pItem->ItemName, itUseItem->Count);
			}
			sQuestUseItemSameItemCheckList.push_back(buf);
			o_vecPossibleDesc->push_back(buf);
			nCount = itUseItem->Count;
			nLineCount++;
			nbreak++;
		}
		itUseItem++;
	}
	// END 2014-02-19 by ymjoo ����Ʈ ��ũ��Ʈ �߰� - ������ ���

	// ���� �ʿ� ������
	vector<ITEM_W_COUNT>::iterator it = pQuest->TargetItemVector.begin();
	while(it != pQuest->TargetItemVector.end())
	{
		if(nbreak>3)
		{
			break;
		}
		if(it->Count < 0)
		{
			// ��ġ������ ���̴� ����Ÿ
			it++;
			continue;
		}
		ITEM* pItem = g_pGameMain->GetServerItemInfo(it->ItemNum);
		if(pItem)
		{				
			ZERO_MEMORY(buf);
			// 2009-01-12 by bhsohn �Ϻ� �߰� ��������
			//wsprintf(buf, STRMSG_C_050726_0002, pItem->ItemName, (*it).Count); //"��ǥ:%s %d��"	
			wsprintf(buf, STRMSG_C_090112_0203, pItem->ItemName, (*it).Count); //"��ǥ:%s %d��"	
			// end 2009-01-12 by bhsohn �Ϻ� �߰� ��������
			o_vecPossibleDesc->push_back(buf);
			nCount = it->Count;			
			nLineCount++;
			nbreak++;
		}	
		it++;
	}
		// ���� ��ǥ ����
	vector<MONSTER_W_COUNT>::iterator itMonC = pQuest->TargetMonsterVector.begin();
	while(itMonC != pQuest->TargetMonsterVector.end())
	{
		if(0 < itMonC->Count )
		{
			MEX_MONSTER_INFO * pTempIn = g_pGameMain->CheckMonsterInfo((*itMonC).MonsterUniqueNumber);
			ZERO_MEMORY(buf);
			// 2009-01-12 by bhsohn �Ϻ� �߰� ��������
			//wsprintf( buf, STRMSG_C_050726_0002,pTempIn->MonsterName, (*itMonC).Count ); //"\\e%s\\e \\w%d��/%d��\\w"
			wsprintf( buf, STRMSG_C_090112_0203,pTempIn->MonsterName, (*itMonC).Count ); //"\\e%s\\e \\w%d��/%d��\\w"
			// end 2009-01-12 by bhsohn �Ϻ� �߰� ��������
			o_vecPossibleDesc->push_back(buf);
			nLineCount++;
		}
		itMonC++;
	}
	
	nbreak = 0;
	vector<ITEM_W_COUNT_MAP_AREA>::iterator it2 = pQuest->TargetMonsterItemVector.begin();
	while(it2 != pQuest->TargetMonsterItemVector.end())
	{
		if(nbreak>3)
		{
			break;
		}
		
		if(it2->ItemWithCount.Count < 0)
		{
			// ��ġ������ ������ ����Ÿ 
			it2++;
			continue;
		}
		//////////////////////////////////////////////////////////////////////////			
		ITEM* pItem = g_pGameMain->GetServerItemInfo(it2->ItemWithCount.ItemNum);
		if(pItem)
		{			
			if(pQuest->vecQuestDropItem.size()<0)
			{
				ZERO_MEMORY(buf);
				// 2009-01-12 by bhsohn �Ϻ� �߰� ��������
				//wsprintf(buf, STRMSG_C_050726_0002, pItem->ItemName, it2->ItemWithCount.Count); //"��ǥ:%s %d��"				
				wsprintf(buf, STRMSG_C_090112_0203, pItem->ItemName, it2->ItemWithCount.Count); //"��ǥ:%s %d��"				
				// end 2009-01-12 by bhsohn �Ϻ� �߰� ��������
				
				o_vecPossibleDesc->push_back(buf);
				
				nCount = it2->ItemWithCount.Count;				
				nbreak++;
				nLineCount++;
			}
			
			vector<QUEST_DROP_ITEM>::iterator itItem = pQuest->vecQuestDropItem.begin();
			while(itItem != pQuest->vecQuestDropItem.end())
			{
				QUEST_DROP_ITEM *pTemp = &*itItem;
				if(pItem->ItemNum == pTemp->ItemNumber)
				{
					MEX_MONSTER_INFO * pMonster = g_pGameMain->CheckMonsterInfo(pTemp->MonsterUniqueNumber);							
					if(pMonster)
					{
						ZERO_MEMORY(buf);
						// 2009-01-12 by bhsohn �Ϻ� �߰� ��������
// 						wsprintf(buf, STRMSG_C_050818_0011, pItem->ItemName,pMonster->MonsterName,
// 							it2->ItemWithCount.Count); //"��ǥ:%s %d��"	
						wsprintf(buf, STRMSG_C_090112_0205, pItem->ItemName,pMonster->MonsterName,
							it2->ItemWithCount.Count); //"��ǥ:%s %d��"	
						// 2009-01-12 by bhsohn �Ϻ� �߰� ��������
						
						o_vecPossibleDesc->push_back(buf);
						
						nCount = it2->ItemWithCount.Count;						
						nbreak++;
						nLineCount++;						
					}
				}
				
				itItem++;
			}				
			// 2007-07-30 by bhsohn ����Ʈ ���� ��� ���¿� ���� ���� ǥ�� �ȵǴ� ���� ����			
			vector<QUEST_DROP_CHARACTER2ITEM>::iterator itCharacter = pQuest->vecQuestDropCharacter2Item.begin();
			while(itCharacter != pQuest->vecQuestDropCharacter2Item.end())
			{
				QUEST_DROP_CHARACTER2ITEM *pItemInfoMap = &*itCharacter;
				if(pItem->ItemNum == pItemInfoMap->Character2Item.ItemNumber)
				{					
					ZERO_MEMORY(buf);
					// 2009-01-12 by bhsohn �Ϻ� �߰� ��������
					//wsprintf(buf, STRMSG_C_050726_0002, pItem->ItemName, it2->ItemWithCount.Count); //"��ǥ:%s %d��"											
					wsprintf(buf, STRMSG_C_090112_0203, pItem->ItemName, it2->ItemWithCount.Count); //"��ǥ:%s %d��"											
					// end 2009-01-12 by bhsohn �Ϻ� �߰� ��������
										
					nCount = it2->ItemWithCount.Count;
					o_vecPossibleDesc->push_back(buf);
					nbreak++;
					nLineCount++;						
					
				}
				itCharacter++;
			}
			// end 2007-07-30 by bhsohn ����Ʈ ���� ��� ���¿� ���� ���� ǥ�� �ȵǴ� ���� ����		
		}
		//////////////////////////////////////////////////////////////////////////
		it2++;
	}
	// ���� NPC �̸�
	if(strlen(pQuest->TargetMeetNPCInfo.NPCName)>0)
	{
		ZERO_MEMORY(buf);			
		wsprintf(buf, STRMSG_C_050726_0003, pQuest->TargetMeetNPCInfo.NPCName); // "[%s]�� ã�ư���!"
		o_vecPossibleDesc->push_back(buf);
		nLineCount++;
	}
	
	// ���� �������ϴ� ������Ʈ
	// ���� ��� ���� ��������Ʈ ���
	if(pQuest->TargetMeetObjectMapArea.MapIndex)
	{
		MAP_INFO* pMapInfo = g_pGameMain->GetMapInfo(pQuest->TargetMeetObjectMapArea.MapIndex);
		if(pMapInfo)
		{
			ZERO_MEMORY(buf);			
			wsprintf(buf, STRMSG_C_050726_0004, pMapInfo->MapName); //"[%s]�� ����϶�!"
			o_vecPossibleDesc->push_back(buf);
			nLineCount++;
		}
	}
	
	// ���� ��ǥ ������
	if(pQuest->QuestEndType == QUEST_END_TYPE_LEVEL_UP)
	{
		ZERO_MEMORY(buf);			
		wsprintf(buf, STRMSG_C_050805_0001); // "������ �Ѵܰ� �ø�����"
		o_vecPossibleDesc->push_back(buf);
		nLineCount++;
	}
	
	// ����Ʈ �����ð� ǥ��
	if(pQuest->TimeLimitInMinutes)
	{
		ZERO_MEMORY(buf);
		
		wsprintf(buf, STRMSG_C_INTERFACE_0020, pQuest->TimeLimitInMinutes, 0);//"[�����ð�] %2.d�� %2.d��"
		o_vecPossibleDesc->push_back(buf);
		nLineCount++;
		
	}
	
	if(pQuest->TargetMixItemTarget.Count > 0)
	{
		ZERO_MEMORY(buf);	
		ITEM* pItem = g_pGameMain->GetServerItemInfo(pQuest->TargetMixItemTarget.ItemNum);
		if(pItem != NULL)
		{
			wsprintf(buf, STRMSG_C_070410_0100,pItem->ItemName);	//"[���丮]���� %s(��)�� �����϶�"
			o_vecPossibleDesc->push_back(buf);
			nLineCount++;
		}
	}	
	
	
	// ����Ʈ ���͸� ����� ��
	vector<MONSTER_W_COUNT>::iterator itMon = pQuest->TargetMonsterVector.begin();
	while(itMon != pQuest->TargetMonsterVector.end())
	{
		vector<Quest_MonsterInfo>::iterator it = g_pQuestData->m_vecQuestMonsterCount.begin();
		while(it != g_pQuestData->m_vecQuestMonsterCount.end())
		{
			MEX_MONSTER_INFO * pTempInfo = g_pGameMain->CheckMonsterInfo((*it).nMonsterUnitkind);
			if(pTempInfo)
			{
				if((*itMon).MonsterUniqueNumber == (*it).nMonsterUnitkind)
				{
					if(0 < itMon->Count)
					{
						ZERO_MEMORY(buf);
						wsprintf( buf, STRMSG_C_070627_0208,pTempInfo->MonsterName, (*itMon).Count ); //"\\e%s\\e \\w%d��\\w"	
						o_vecPossibleDesc->push_back(buf);
						nLineCount++;
					}
				}					
			}
			it++;
		}
		itMon++;
	}	

	// ���۽� �ٷ� �Ϸ� �Ǵ� �̼� 
	if(o_vecPossibleDesc->size() == nStartDesc)
	{
		//2011-07-12 by jhahn ����3�� ����Ʈ â �̼� �Ϸ� ��� �ȱ׸���
		if(pQuest->QuestEpisodeType != QUEST_INFINITY_TYPE_3)
		// end 2011-07-12 by jhahn ����3�� ����Ʈ â �̼� �Ϸ� ��� �ȱ׸���
		{
		ZERO_MEMORY(buf);
		wsprintf( buf, STRMSG_C_070627_0209); //"�̹� �̼��� �̼ǽ��۽� �ٷ� �Ϸ�Ǵ� �̼��Դϴ�."	
		o_vecPossibleDesc->push_back(buf);
		}
	}

	o_vecPossibleDesc->push_back("          ");

}

///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CINFMissionInfo::CheckMissionStart()
/// \brief		�̼� ������ ���� ���� �˻�
/// \author		ispark
/// \date		2005-11-16 ~ 2005-11-16
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CINFMissionMain::CheckMissionStart()
{
	// ���̴��� ���θ� ���	
	if(FALSE == g_pStoreData->IsShuttleWearItem(POS_PROW))
	{
		g_pGameMain->CreateChatChild(STRMSG_C_051229_0101,COLOR_SYSTEM); // "���̴��� �����Ǿ� ���� �ʽ��ϴ�."
	}

	//*--------------------------------------------------------------------------*//
	// ������ ���ٸ� �̼� ��� ����	
	if(FALSE == g_pStoreData->IsShuttleWearItem(POS_REAR))
	{
		g_pGameMain->CreateChatChild(STRMSG_C_051115_0002,COLOR_SYSTEM); // "���� ���������� ������ �� �����ϴ�."
		return FALSE;
	}
	
	if(FALSE == g_pStoreData->IsShuttleWearItem(POS_CENTER))
	{
		g_pGameMain->CreateChatChild(STRMSG_C_051206_0001,COLOR_SYSTEM); // "�Ƹ� ���������� ������ �� �����ϴ�."
		return FALSE;
	}

	// 2006-10-17 by ispark, �׾� ���� ��� ��� ���ϰ�
	if(g_pShuttleChild->CheckUnitState() == BREAKDOWN)
	{
		g_pGameMain->CreateChatChild(STRMSG_C_061017_0001,COLOR_SYSTEM); // "��� �� �� �����ϴ�."
		return FALSE;
	}
	
	// 2007-07-09 by bhsohn ��ݰ� ���ڻ��� ���� ���� ������ ó��
	if(g_pInterface->IsBazarOpen())
	{		
		g_pGameMain->CreateChatChild(STRMSG_C_061017_0001,COLOR_SYSTEM); // "��� �� �� �����ϴ�."
		return FALSE;
	}	
	// end 2007-07-09 by bhsohn ��ݰ� ���ڻ��� ���� ���� ������ ó��

	// 2009-04-30 by bhsohn ���� ����â ������ ��� ���ϰ� ����
	if(IsShowWnd(MISSOIN_SHOW_SEL_INFLUENCE))
	{
		return FALSE;
	}
	// end 2009-04-30 by bhsohn ���� ����â ������ ��� ���ϰ� ����

	// 2013-09-02 by ssjung �ʵ��̵�����������
	if(g_pGameMain && !g_pGameMain->UserWarpRestriction())
	{
		return FALSE;
	}
	// end 2013-09-02 by ssjung �ʵ��̵�����������

	return TRUE;
}

BOOL CINFMissionMain::CheckMissionIdxStart(DWORD i_dwSelQuestIndex)
{
	// 2005-12-07 by ispark, ���� ���� �̼��� ��� ��Ƽ���°� �ƴҶ� Ŭ�� ����
	if(i_dwSelQuestIndex == SELECT_QUEST && 
		g_pShuttleChild->GetPartyInfo().bPartyType != _NOPARTY)
	{
		g_pGameMain->CreateChatChild(STRMSG_C_051207_0001,COLOR_SYSTEM); // "�����¿����� ������ ������ �� �����ϴ�."
		return FALSE;
	}
	return TRUE;
}

void CINFMissionMain::MissionStart(DWORD i_dwSelQuestIndex)
{
	if(0 == i_dwSelQuestIndex)
	{
		return;
	}
	if(!CheckMissionStart())
	{
		return;
	}

	if(!CheckMissionIdxStart(i_dwSelQuestIndex))
	{
		return;
	}

	g_pGameMain->SetWindowOrder(WNDMissionInfo);

	CQuest* pQuest = g_pQuestData->FindQuest(i_dwSelQuestIndex);
	if(pQuest && pQuest->QuestEndType != QUEST_END_TYPE_IMMEDIATE)
	{
		// ���۽� �ٷ� ������ �̼� �̼�â ���� ����.
		ShowTreeWnd(FALSE, FALSE);		
	}	
	
	// Ư�� ������ �Ϸ� �̼� �˻�
	CQuest* pQuest2 = g_pQuestData->FindPosCompleteQuest( i_dwSelQuestIndex );
	if(pQuest2)
	{
		SetPosMissionComplete(TRUE);
	}
	// ���� ���� �̼�
	if(pQuest->QuestEndType == QUEST_END_TYPE_SELECT_INFLUENCE)
	{
		STAGE_EFFECT_DATA stStageData;
		stStageData.nMissionIndex = i_dwSelQuestIndex;
		// 2008-04-02 by bhsohn ���¼��� ���ѷα� ��ŵ�����ϰ� ����
		//g_pInterface->InitSoundScript("Influence.tex", &stStageData, MISSION_PRE, FALSE);
		g_pInterface->InitSoundScript("Influence.tex", &stStageData, MISSION_PRE, TRUE);
		return;
	}
	
	g_pQuestData->SendFieldSocketQuestRequestStart(i_dwSelQuestIndex,0);	

	// 2008-06-17 by bhsohn ��� ���� ó��
	// ������ ���� ��������
	if(g_pShuttleChild->m_pClientParty 
		&& g_pShuttleChild->m_pClientParty->GetPartyInfo().bPartyType == _PARTYMASTER 
		&& g_pShuttleChild->m_pClientParty->IsFormationFlight())
	{
		g_pShuttleChild->m_pClientParty->TempPartyFormation(FLIGHT_FORM_NONE);
	}
	// end 2008-06-17 by bhsohn ��� ���� ó��

}

float CINFMissionMain::GetVCNInflDistributionPercent()
{
	return m_fVCNInflDistributionPercent;
}

float CINFMissionMain::GetANIInflDistributionPercent()
{
	return m_fANIInflDistributionPercent;
}
int	CINFMissionMain::GetMissionMapQuestIdx()
{
	return m_nMissionMapQuestIndex;
}
void CINFMissionMain::SetMissionMapQuestIdx(int nMissionMapQuestIndex)
{
	m_nMissionMapQuestIndex = nMissionMapQuestIndex;
}

void CINFMissionMain::SetFirstPossibleQuestIdx(int nPossibleQuestIdx)
{
	m_nFirstPossibleQuestIdx = nPossibleQuestIdx;
}
int  CINFMissionMain::GetFirstPossibleQuestIdx()
{
	return m_nFirstPossibleQuestIdx;
}

void CINFMissionMain::RefreshMissionUI()
{
	m_nMyShuttleCharacter = -1;
}
// 2008-12-09 by dgwoo �̼Ǹ�����.
void CINFMissionMain::SetMissionMasterWindowShow(BOOL i_bShow)
{
	m_pINFMissionMaster->SetWindowShow(i_bShow);
}
// 2008-12-09 by dgwoo �̼Ǹ�����.
INT	CINFMissionMain::GetMissionMasterQuestIdx()
{
	return m_pINFMissionTreeInfo->GetMissionMasterIdx();
}
void CINFMissionMain::UpdateMissionMasterButton()
{
	m_pINFMissionTreeInfo->UpdateMissionMasterButton();
}