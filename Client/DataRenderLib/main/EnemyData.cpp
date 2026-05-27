// EnemyData.cpp: implementation of the CEnemyData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EnemyData.h"
#include "ChatMoveData.h"
#include "AtumApplication.h"
//#include "TraceData.h"
#include "FieldWinSocket.h"
#include "ShuttleChild.h"
#include "CharacterChild.h"				// 2005-07-21 by ispark
#include "Chat.h"
#include "Background.h"
#include "SceneData.h"
#include "Camera.h"
//#include "TraceRender.h"
#include "Weapon.h"
#include "AtumDatabase.h"
#include "WeaponShieldData.h"
#include "UnitRender.h"
#include "CharacterRender.h"					// 2005-07-21 by ispark
#include "Frustum.h"
//#include "ObjectRender.h"
#include "ObjectChild.h"
#include "ClientParty.h"
#include "ObjRender.h"
#include "SkillEffect.h"
#include "dxutil.h"
#include "PkNormalTimer.h"
#include "Skill.h"
#include "WeaponItemInfo.h"
#include "StoreData.h"		// 2008-08-19 by bhsohn ���� ��ũ �ý��� �߰�
#include "INFGameMain.h"	// 2010. 03. 18 by jskim ���ͺ��� ī��



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEnemyData::CEnemyData(MSG_FC_CHARACTER_GET_OTHER_INFO_OK* pMsg)
{
	FLOG( "CEnemyData()" );
	m_pCharacterInfo = NULL;
	m_pEnemyCharacterInfo = NULL;							// 2005-07-26 by ispark �� ĳ���� ����
//	m_pRenderer = g_pD3dApp->m_pShuttleRender;
	m_pRender = g_pD3dApp->m_pUnitRender;
	m_pCharacterRender = g_pD3dApp->m_pCharacterRender;		// 2005-07-26 by ispark ĳ���� Rendering
	m_pTarget = NULL;
	m_fTargetCheckTime = 1.0f;

	m_fCurrentTime = 1.0f;
	//m_dwState = _NORMAL;
	m_dwPartType = _ENEMY;

//	m_vPos = D3DXVECTOR3(0,30,0);
//	m_vVel = D3DXVECTOR3(1,0,1);
//	D3DXVec3Normalize(&m_vVel,&m_vVel);
//	m_vUp = D3DXVECTOR3(0,1,0);

//	m_vMovepos = D3DXVECTOR3(1,0,0);
//	m_vMoveVel = D3DXVECTOR3(1,0,0);
//	m_vNextUp = D3DXVECTOR3(0,1,0);
//	m_vNextVel = D3DXVECTOR3(1,0,0);
//	m_vOriNextUp = D3DXVECTOR3(1,0,0);
//	m_vOriNextVel = D3DXVECTOR3(1,0,0);
//	m_vMoveUp = D3DXVECTOR3(0,1,0);
//	m_vNextPos = D3DXVECTOR3(1,30,0);

	// 2004-12-16 by jschoi
	m_vPos = A2DX(pMsg->CharacterInfo.PositionVector);
	m_vNextPos = m_vPos;

	m_vVel = A2DX(pMsg->CharacterInfo.TargetVector);
	D3DXVec3Normalize(&m_vVel,&m_vVel);
	m_vNextVel = m_vVel;
	m_vOriNextVel = m_vVel;

	m_vUp = A2DX(pMsg->CharacterInfo.UpVector);
	D3DXVec3Normalize(&m_vUp,&m_vUp);
	m_vNextUp = m_vUp;
	m_vOriNextUp = m_vUp;

	m_vMovepos = D3DXVECTOR3(0,0,0);
	m_vMoveVel = D3DXVECTOR3(0,0,0);
	m_vMoveUp  = D3DXVECTOR3(0,0,0);

//	m_nEnemyTypePrimary = ENEMYDATA_ENEMYLIST;
//	m_nEnemyTypeSecondary = ENEMYDATA_ENEMYLIST;
	m_pMoveChat = NULL;
	m_pMoveChat = new CAtumNode;
	m_pIDChat = NULL;
	m_pIDChat = new CAtumNode;
	
	m_fLifeTime = 2.0f;

	m_bIsUnderWater = FALSE;
	m_bCheckColl = FALSE;
	m_bRequestMove = FALSE;

//	memset(&m_infoParty,0x00,sizeof(PARTYINFO));
//	m_infoParty.bPartyType = _NOPARTY;
	m_nPartyID = 0;
	
	memset(&m_infoCharacter,0x00,sizeof(ENEMYINFO));

	m_fObjectSize = 15.0f;
	m_bIsInit = FALSE;
	
	m_bUseMoveSkill = FALSE;
	m_bSkillMoveType = 0;

	m_bZBuffer=  FALSE;

//	m_bAttackEnemy = FALSE;

	m_ptCurRegion.x = (int)(m_vPos.x/(TILE_SIZE*3));
	m_ptCurRegion.y = (int)(m_vPos.z/(TILE_SIZE*3));
	m_ptOldRegion = m_ptCurRegion;

//	memset(&m_CharacterRenderInfo,0x00,sizeof(CHARACTER_RENDER_INFO));
	m_bIsItemPointSet = FALSE;
	m_pEffectTarget = NULL;

	m_bIsRender = TRUE;
	m_fCheckItemInfoTime = 0.0f;

	m_fRollStartTime = 0.0f;
	m_fRollAngle = 0.0f;
	m_bRollStart = FALSE;
	m_bRollLeft = FALSE;
	m_bRollRight = FALSE;
	
	m_bEnemyCharacter = FALSE;				// 2005-07-21 by ispark
//	RestoreShadow();
#ifdef _DEBUG
	m_nDebugMoveCount = 0;
	m_fCheckMoveTime = 0;
#endif

	m_infoCharacter.CharacterInfo = pMsg->CharacterInfo;
	if(COMPARE_BODYCON_BIT(pMsg->CharacterInfo.BodyCondition,BODYCON_DEAD_MASK))
	{
		ChangeUnitState( _FALLEN );
		pMsg->CharacterInfo.BodyCondition = BODYCON_DEAD_MASK | BODYCON_DAMAGE1_MASK | BODYCON_DAMAGE2_MASK | BODYCON_DAMAGE3_MASK;
	}
	
	m_infoCharacter.CharacterRenderInfo = pMsg->CharacterRenderInfo;

	// 2005-11-03 by ispark  -  PK Delay Timer
	m_pPkNormalTimer = new CPkNormalTimer;
	m_nTargetIndex = 0;

	// 2005-07-28 by ispark
	// �� ĳ����
//	m_bEnemyCharacter = TRUE;
	m_hyBodyCondition = 0;
	if(m_infoCharacter.CharacterInfo.CharacterMode0 == FALSE)
	{
		m_bEnemyCharacter = FALSE;
	}
	else
	{
		m_bEnemyCharacter = TRUE;
		// ĳ���ʹ� Up���Ͱ� �ؿ���
		m_vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	}

// 2011-07-18 by jhahn ����3�� �ó׸� Ÿĳ���� �Ⱥ��̱�
	m_bRender = TRUE;
//end 2011-07-18 by jhahn ����3�� �ó׸� Ÿĳ���� �Ⱥ��̱�

	m_bSetPosition = FALSE;
	m_pMoveChatShop = NULL;

	// 2010. 03. 18 by jskim ���ͺ��� ī��
	m_MonsterTransformer = pMsg->CharacterRenderInfo.RI_MonsterUnitKind_ForTransformer;

	ITEM *temp = g_pDatabase->GetServerMonsterTransItemInfo(m_MonsterTransformer);
	if(temp)
 		m_MonsterTransScale = temp->AbilityMin;

	m_MonsterTransPrimarySidePos = D3DXVECTOR3(0, 0, 0);
	m_MonsterTransSecondarySidePos = D3DXVECTOR3(0, 0, 0);
	//end 2010. 03. 18 by jskim ���ͺ��� ī��
}

CEnemyData::~CEnemyData()
{
	FLOG( "~CEnemyData()" );
	if(m_nPartyID != 0 && g_pShuttleChild && g_pShuttleChild->m_pClientParty)
	{
		PARTYENEMYINFO * pPartyEnemyInfo;
		pPartyEnemyInfo = g_pShuttleChild->m_pClientParty->PartyFindMemberByUniqueNumber(m_infoCharacter.CharacterInfo.CharacterUniqueNumber);
		if(pPartyEnemyInfo)
		{
			if(pPartyEnemyInfo->m_bPartyType == _PARTYMASTER)
			{
				pPartyEnemyInfo->m_bPartyType = _PARTYOTHERMAPMASTER;
			}
			else if(pPartyEnemyInfo->m_bPartyType == _PARTYMEMBER)
			{
				pPartyEnemyInfo->m_bPartyType = _PARTYOTHERMAPMEMBER;
			}
			pPartyEnemyInfo->m_pEnemyData = NULL;			
		}
	}

	if(m_pMoveChat)
	{
		m_pMoveChat->InvalidateDeviceObjects();
		m_pMoveChat->DeleteDeviceObjects();
	}
	SAFE_DELETE(m_pMoveChat);
	if(m_pIDChat)
	{
		m_pIDChat->InvalidateDeviceObjects();
		m_pIDChat->DeleteDeviceObjects();
	}
	SAFE_DELETE(m_pIDChat);
	if(m_pCharacterInfo)//�߰�
	{
		m_pCharacterInfo->InvalidateDeviceObjects();
		m_pCharacterInfo->DeleteDeviceObjects();
		SAFE_DELETE(m_pCharacterInfo);
	}
	if(m_pEffectTarget)
	{
		m_pEffectTarget->m_bUsing = FALSE;
		m_pEffectTarget = NULL;
	}

//	InvalidateShadow();

	SAFE_DELETE(m_pPkNormalTimer);
	SAFE_DELETE(m_pEnemyCharacterInfo);
	SAFE_DELETE(m_pMoveChatShop);
}

HRESULT CEnemyData::InitDeviceObjects()
{
	if(m_pIDChat)
		m_pIDChat->InitDeviceObjects();
	if(m_pMoveChat)
		m_pMoveChat->InitDeviceObjects();

	if(m_pMoveChatShop)
		m_pMoveChatShop->InitDeviceObjects();

	// 2005-07-27 by ispark
	if(m_pEnemyCharacterInfo)
	{
		m_pEnemyCharacterInfo->InvalidateDeviceObjects();
		m_pEnemyCharacterInfo->DeleteDeviceObjects();
		SAFE_DELETE(m_pEnemyCharacterInfo);
	}
	// 2010-06-15 by shcho&hslee ��ý��� - �� ���� ó��
	m_pPetManager = g_pShuttleChild->GetPetManager();
	//end 2010-06-15 by shcho&hslee ��ý��� - �� ���� ó��
	return S_OK;
}

HRESULT CEnemyData::RestoreDeviceObjects()
{
	if(m_pIDChat)
		m_pIDChat->RestoreDeviceObjects();
	if(m_pMoveChat)
		m_pMoveChat->RestoreDeviceObjects();
//	if(m_pEnemyCharacterInfo)					// 2005-07-26 by ispark
//		m_pEnemyCharacterInfo->RestoreDeviceObjects();
	if(m_pMoveChatShop)
		m_pMoveChatShop->RestoreDeviceObjects();
	return CUnitData::RestoreDeviceObjects();
}

HRESULT CEnemyData::InvalidateDeviceObjects()
{
	if(m_pIDChat)
		m_pIDChat->InvalidateDeviceObjects();
	if(m_pMoveChat)
		m_pMoveChat->InvalidateDeviceObjects();
//	if(m_pEnemyCharacterInfo)					// 2005-07-26 by ispark
//		m_pEnemyCharacterInfo->InvalidateDeviceObjects();

	if(m_pMoveChatShop)
		m_pMoveChatShop->InvalidateDeviceObjects();

	DeleteItemPoint();
	return CUnitData::InvalidateDeviceObjects();
}

HRESULT CEnemyData::DeleteDeviceObjects()
{
	if(m_pIDChat)
		m_pIDChat->DeleteDeviceObjects();
	if(m_pMoveChat)
		m_pMoveChat->DeleteDeviceObjects();
	// 2005-07-27 by ispark
	if(m_pEnemyCharacterInfo)
	{
		m_pEnemyCharacterInfo->InvalidateDeviceObjects();
		m_pEnemyCharacterInfo->DeleteDeviceObjects();
		SAFE_DELETE(m_pEnemyCharacterInfo);
	}

	if(m_pMoveChatShop)
	{
		m_pMoveChatShop->DeleteDeviceObjects();
		SAFE_DELETE(m_pMoveChatShop);
	}

	return S_OK;
}


//void CEnemyData::RestoreChat()
//{
//	FLOG( "CEnemyData::RestoreChat()" );
//	if(m_pIDChat)
//		m_pIDChat->RestoreDeviceObjects();
//	if(m_pMoveChat)
//		m_pMoveChat->RestoreDeviceObjects();
//}
//
//void CEnemyData::InvalidateChat()
//{
//	FLOG( "CEnemyData::InvalidateChat()" );
//	if(m_pIDChat)
//		m_pIDChat->InvalidateDeviceObjects();
//	if(m_pMoveChat)
//		m_pMoveChat->InvalidateDeviceObjects();
//	DeleteItemPoint();
//}

void CEnemyData::Init()
{
	FLOG( "CEnemyData::Init()" );
	CChatMoveData * pData;
	if(COMPARE_RACE(m_infoCharacter.CharacterInfo.Race,RACE_GAMEMASTER))
	{
#ifdef _RAT_FFA
		if (MAP_INFLUENCE_PVP_ALL == g_pD3dApp->GetMyShuttleMapInfo()->MapInfluenceType)
			pData = new CChatMoveData(m_pIDChat, "FFA Enemy", COLOR_CHARACTER_ID02, 9, 256, 32);
		else
			pData = new CChatMoveData(m_pIDChat, m_infoCharacter.CharacterInfo.CharacterName, COLOR_CHARACTER_ID02, 9, 256, 32);
		m_dwPartType = _ADMIN;
#else
		pData = new CChatMoveData(m_pIDChat,m_infoCharacter.CharacterInfo.CharacterName,COLOR_CHARACTER_ID02,9,256,32);
		m_dwPartType = _ADMIN;
#endif
	}
	else
	{
#ifdef _RAT_FFA
		if (MAP_INFLUENCE_PVP_ALL == g_pD3dApp->GetMyShuttleMapInfo()->MapInfluenceType)
			pData = new CChatMoveData(m_pIDChat, "FFA Enemy", COLOR_CHARACTER_ID00, 9, 256, 32);
		else
			pData = new CChatMoveData(m_pIDChat, m_infoCharacter.CharacterInfo.CharacterName, COLOR_CHARACTER_ID00, 9, 256, 32);
#else
		pData = new CChatMoveData(m_pIDChat, m_infoCharacter.CharacterInfo.CharacterName, COLOR_CHARACTER_ID00, 9, 256, 32);
#endif
	}

	pData->InitDeviceObjects();
//	pData->RestoreDeviceObjects();
	pData = (CChatMoveData *)m_pIDChat->AddChild(pData);
	// �ʱ�ȭ�ÿ� ���� ��Ʈ������ ���Ѵ�.
	D3DXMatrixLookAtRH( &m_mMatrix, &m_vPos, &(m_vPos+100.0f*m_vVel), &m_vUp);
	D3DXMatrixInverse( &m_mMatrix, NULL, &m_mMatrix );

	float fDistanceToCamera;
	float fDistance;
	
	fDistanceToCamera = D3DXVec3Length(&(m_vPos - g_pD3dApp->m_pCamera->GetEyePt()));
//	fDistance = ((g_pScene->m_fOrgFogEndValue/10)/(10-g_pSOption->sUnitDetail));
//	fDistance = (g_pScene->m_fFogEndValue*g_pSOption->sUnitDetail)/MAX_OPTION_VALUE;
	fDistance = (RANGE_OF_VISION*g_pSOption->sUnitDetail)/MAX_OPTION_VALUE;

	if(fDistanceToCamera < fDistance)
	{
		m_bDegree = 2;
		m_bItemDegree = TRUE;
	}
	else
	{
		m_bDegree = 0;
		m_bItemDegree = FALSE;
	}
	// 2005-11-24 by ispark, ItemNum -> SourceIndex���� ����

	// 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����
	//ITEM * pItem = g_pDatabase->GetServerItemInfo(m_infoCharacter.CharacterRenderInfo.RI_Center);
	
	// ���������۹�ȣ�� ���ٸ� ���� ������ ��ȣ�� ����Ѵ�
	int nItemNum = 0;
	if( m_infoCharacter.CharacterRenderInfo.RI_Center_ShapeItemNum )
		nItemNum = m_infoCharacter.CharacterRenderInfo.RI_Center_ShapeItemNum;
	else
		nItemNum = m_infoCharacter.CharacterRenderInfo.RI_Center;
	ITEM* pItem	= g_pDatabase->GetServerItemInfo( nItemNum );
	// end 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����

	// 2010. 03. 18 by jskim ���ͺ��� ī��
	BOOL bMonTras = FALSE;
	if(m_MonsterTransformer)
	{
		ChangeUnitCharacterInfo(nItemNum, m_infoCharacter.CharacterInfo.UnitKind, m_infoCharacter.CharacterInfo.BodyCondition, FALSE);
		SetMonsterTransPrimarySidePos(m_PrimaryAttack.vSidePos);
		SetMonsterTransSecondarySidePos(m_SecondaryAttack.vSidePos);
	}

	if(m_MonsterTransformer)
	{
		bMonTras = TRUE;
		MEX_MONSTER_INFO * pTempIn = g_pGameMain->CheckMonsterInfo( m_MonsterTransformer );
		if(pTempIn)
			nItemNum = pTempIn->SourceIndex;
	}
	else
	{
		if(pItem)
			nItemNum = pItem->SourceIndex;
	}
	//end 2010. 03. 18 by jskim ���ͺ��� ī��

#ifdef _RAT_FFA
	if (MAP_INFLUENCE_PVP_ALL == g_pD3dApp->GetMyShuttleMapInfo()->MapInfluenceType)
		pItem = NULL;
#endif

	if(pItem)
	{
		ChangeUnitCharacterInfo(nItemNum, m_infoCharacter.CharacterInfo.UnitKind, m_infoCharacter.CharacterInfo.BodyCondition, FALSE , bMonTras);
		//end 2010. 03. 18 by jskim ���ͺ��� ī��
	}
	else
	{
		// ����Ʈ
		ChangeUnitCharacterInfo(0, 
			m_infoCharacter.CharacterInfo.UnitKind, m_infoCharacter.CharacterInfo.BodyCondition, FALSE);
	}

	// 2005-07-28 by ispark
	// ĳ���� ������ ��ȣ �Է�
	SetPilotNumber(m_infoCharacter.CharacterInfo.PilotFace);

	// 2005-07-28 by ispark
	// ĳ���� ���� ��ǥ �Է� - ���⼭ �ʱ�ȭ�� ���� ��ǥ�� ���Ϸ� �Է�
	m_vOldPos = m_vPos;

	if(m_pCharacterInfo)
	{
		m_pCharacterInfo->SetShuttleChildEffect(FALSE);
	}
	m_bIsInit = TRUE;
//	RestoreChat();
	RestoreDeviceObjects();

	// ����� ����ΰ�?
	if( g_pShuttleChild && 
		g_pShuttleChild->m_pClientParty)
	{
		if( g_pShuttleChild->IsPkState(PK_FVF) &&
			g_pShuttleChild->m_pClientParty->IsFVFEnemy(m_infoCharacter.CharacterInfo.CharacterUniqueNumber))
		{
			SetPkState( PK_FVF, TRUE );
		}
	}

	// ������ ����ΰ�?
	if(g_pShuttleChild->m_pGuildWarInfo)
	{
		if( g_pShuttleChild->IsPkState(PK_GVG) &&
			m_infoCharacter.CharacterInfo.GuildUniqueNumber == g_pShuttleChild->m_pGuildWarInfo->PeerGuildUID )
		{
			SetPkState( PK_GVG, TRUE );
		}
	}

	// ������
//	if(g_pShuttleChild->IsInfluenceWarType(m_infoCharacter.CharacterInfo.InfluenceType) == TRUE)
#ifdef _RAT_FFA
	if ( (g_pShuttleChild->m_myShuttleInfo.MapChannelIndex.MapIndex == m_infoCharacter.CharacterInfo.MapChannelIndex.MapIndex && MAP_INFLUENCE_PVP_ALL == g_pD3dApp->GetMyShuttleMapInfo()->MapInfluenceType))
	{
		SetPkState(PK_WAR, TRUE);
	}
	else
	{
		if (!IsInfluenceCharacter(g_pShuttleChild->m_myShuttleInfo.InfluenceType, m_infoCharacter.CharacterInfo.InfluenceType))
		{
			SetPkState(PK_WAR, TRUE);
		}
	}
#else
	if(!IsInfluenceCharacter(g_pShuttleChild->m_myShuttleInfo.InfluenceType, m_infoCharacter.CharacterInfo.InfluenceType))
	{
		SetPkState( PK_WAR, TRUE );
	}
#endif

	MSG_FC_CHARACTER_GET_OTHER_PARAMFACTOR sMsg;
	sMsg.ClientIndex = m_infoCharacter.CharacterInfo.ClientIndex;
	sMsg.ItemPosition = POS_PROWOUT;
	g_pFieldWinSocket->SendMsg( T_FC_CHARACTER_GET_OTHER_PARAMFACTOR, (char*)&sMsg, sizeof(sMsg) );

	// 2006-07-28 by ispark, ���� ������
	m_byBazaarType = 0;
	memset(m_szBazaarName, 0x00, SIZE_MAX_BAZAAR_NAME);

	// 2006-09-20 by ispark, ����Ʈ �ʱ�ȭ
	InitItemPoint();

	// 2006-11-27 by ispark, ���Ŀ� ���õ� ������ ���̸�
	if(m_infoCharacter.CharacterRenderInfo.RI_Invisible)
	{
		SetAlphaData();
	}
}

void CEnemyData::Tick()
{
	FLOG( "CEnemyData::Tick()" );
//	DBGOUT("%f\n",m_fLifeTime);
	if(!m_bUsing)
		return;
	float fElapsedTime = g_pD3dApp->GetElapsedTime();

	// 2005-11-03 by ispark - Pk Delay Timer
	m_pPkNormalTimer->Tick(fElapsedTime);

	// 2005-08-02 by ispark
	D3DXVECTOR3 vPos;
	if(GetCurrentBodyCondition() & BODYCON_CLIENT_SINGLE == 0)
	{
		DBGOUT("(%s)Enemy ������ ����\n", m_infoCharacter.CharacterInfo.CharacterName);
	}

	if(m_bEnemyCharacter)
	{
		TickCharacter(fElapsedTime);
		// ĳ���� Ű ���̷� ����
		vPos = m_vPos;
		vPos.y += GetCharacterHeight(m_nPilotNum) + 1.0f;
	}
	else
	{
		TickUnit(fElapsedTime);
		vPos = m_vPos;
		// 2006-12-04 by ispark, ü������
		ChaffDataTick();
	}

	// 2005-08-02 by ispark
	// ��ũ������ ��ǥ�� ���Ѵ�.
	if(m_bSetPosition == TRUE)
	{
		g_pD3dApp->CalcObjectSourceScreenCoords(vPos, g_pD3dApp->GetBackBufferDesc().Width, g_pD3dApp->GetBackBufferDesc().Height, 
			m_nObjScreenX, m_nObjScreenY, m_nObjScreenW );
	}

	m_pMoveChat->Tick();
	m_pIDChat->Tick();
	// 2006-07-28 by ispark, 
	if(m_pMoveChatShop)
	{
		m_pMoveChatShop->Tick();
	}

	// 2007-05-17 by bhsohn ������Ʈ �ڿ� �������� �� ���� ó �˻� ó��		
	TickCheckObjectTOEnemy();
}
///////////////////////////////////////////////////////////////////////////////
/// \fn			void CEnemyData::UpdateCheckObject()
/// \brief		������Ʈ �浹 ���� üũ
/// \author		// 2007-05-17 by bhsohn ������Ʈ �ڿ� �������� �� ���� ó �˻� ó��	
/// \date		2007-05-17 ~ 2007-05-17
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CEnemyData::TickCheckObjectTOEnemy()
{
	// 2008-06-20 by bhsohn EP3 �ɼǰ��� ó��
		//|| (IsInfluenceCharacter(g_pShuttleChild->GetMyShuttleInfo().InfluenceType, m_infoCharacter.CharacterInfo.InfluenceType))) // ���� ����	
	//(g_pD3dApp->IsMyShuttleCharacter() == TRUE)		// �����̸� ������ ���δ�.
	if((m_infoCharacter.CharacterInfo.ClientIndex == g_pShuttleChild->GetTargetClientIndext())	// ���� Ÿ�� ���������
		|| (m_nTargetIndex == g_pShuttleChild->GetMyShuttleInfo().ClientIndex)// ���� Ÿ���� ��� ������ ������ ���δ�.
		)		
	{		
		InitCheckInfo();
		return;
	}

	// üũ �ð��� 1�ʸ���
	n_fCheckObjectTime -= g_pD3dApp->GetCheckElapsedTime();

	if( n_fCheckObjectTime > 0)
	{
		return;
	}
	n_fCheckObjectTime = CHECK_OBJECT_TIME;
	UpdateCheckObjectTOEnemy(FALSE);	
}

void CEnemyData::InitCheckInfo()
{
	m_bCheckObject = FALSE;
	m_bCheckObjectEnemyShow = TRUE;	
	n_fCheckObjectTime = 0;
}

void CEnemyData::UpdateCheckObjectTOEnemy(BOOL bTarget)
{
	// ������Ʈ �浹 ���� üũ
	D3DXVECTOR3	vMyShuttlePos	= g_pShuttleChild->m_vPos;
	D3DXVECTOR3	vEmenyPos		= m_vPos;

	m_bCheckObject = FALSE;
	m_bCheckObjectEnemyShow = TRUE;		
	// 2008-06-20 by bhsohn EP3 �ɼǰ��� ó��
	BOOL bHidden = FALSE;
	//BOOL bSamInfluence = IsInfluenceCharacter(g_pShuttleChild->GetMyShuttleInfo().InfluenceType, m_infoCharacter.CharacterInfo.InfluenceType);	
	BOOL bSamInfluence = IsSameInfluence(g_pShuttleChild->GetMyShuttleInfo().InfluenceType, m_infoCharacter.CharacterInfo.InfluenceType);	
	if(!bTarget)
	{		
		if(m_infoCharacter.CharacterInfo.ClientIndex == g_pShuttleChild->GetTargetClientIndext())
		{
			// Ÿ���� ������ ���δ�.
			InitCheckInfo();
			return;
		}
		else
		{
			// Tick���� üũ �ϴ°͸� ���̵� ����� ����		
			if(!bSamInfluence)
			{
				if(g_pD3dApp->IsOptionEtc(OPTION_RADIO_ENEMY_ID_HIDE))
				{
					bHidden = TRUE;				
				}	
			}
			else 
			{
				if(g_pD3dApp->IsOptionEtc(OPTION_RADIO_FRIEND_ID_HIDE))
				{
					bHidden = TRUE;
				}			
			}
		}				
		if(bHidden)
		{
			// ���ܶ�
			m_bCheckObject = TRUE;
			m_bCheckObjectEnemyShow = FALSE;
			return;			
		}				
		
		// Ÿ���ÿ��� üũ
		if(bSamInfluence || (g_pD3dApp->IsMyShuttleCharacter() == TRUE))
		{			
			// ���� ���� Ȥ�� �������� ������Ʈ �浹 üũ���ʿ����
			InitCheckInfo();		
			return;
		}
	}		
	else
	{
		if(bSamInfluence || (g_pD3dApp->IsMyShuttleCharacter() == TRUE))
		{
			if(!bSamInfluence)
			{
				if(g_pD3dApp->IsOptionEtc(OPTION_RADIO_ENEMY_ID_HIDE))
				{
					bHidden = TRUE;				
				}	
			}
			else 
			{
				if(g_pD3dApp->IsOptionEtc(OPTION_RADIO_FRIEND_ID_HIDE))
				{
					bHidden = TRUE;
				}			
			}
			if(bHidden)
			{
				// ���ܶ�
				m_bCheckObject = TRUE;
				m_bCheckObjectEnemyShow = FALSE;				
			}	
			else
			{
				InitCheckInfo();
			}
			// ���� ���� Ȥ�� �������� ������Ʈ �浹 üũ���ʿ����
			return;			
		}
	}


	
	// end 2008-06-20 by bhsohn EP3 �ɼǰ��� ó��
	if(g_pScene->IsObjectCheckPosTOPos(vMyShuttlePos, vEmenyPos, m_vUp))
	{
		// ������Ʈ�� �ִ�.
		m_bCheckObject = TRUE;
		m_bCheckObjectEnemyShow = FALSE;
	}
	// �������� üũ�� �Ѵ�. 
	else if(g_pScene->IsTileCheckPosTOPos(vMyShuttlePos, vEmenyPos))
	{
		// ������ �ִ�.
		m_bCheckObject = TRUE;
		m_bCheckObjectEnemyShow = FALSE;		
	}	
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CEnemyData::UpdateCheckObject()
/// \brief		������Ʈ �浹 ���� üũ
/// \author		// 2007-05-17 by bhsohn ������Ʈ �ڿ� �������� �� ���� ó �˻� ó��	
/// \date		2007-05-17 ~ 2007-05-17
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CEnemyData::IsCheckObjectShow()
{	
	return m_bCheckObjectEnemyShow;	
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CEnemyData::IsCheckObjectColl()
/// \brief		������Ʈ �浹 ���� ���� �Ǵ� 
/// \author		// 2007-05-17 by bhsohn ������Ʈ �ڿ� �������� �� ���� ó �˻� ó��	
/// \date		2007-05-17 ~ 2007-05-17
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CEnemyData::IsCheckObjectColl()
{	
	UpdateCheckObjectTOEnemy(TRUE);	
	return m_bCheckObject;
}


void CEnemyData::ChangeBodyConditionFromServer(BodyCond_t hyBodyCondition)
{
	if(	COMPARE_BODYCON_BIT(hyBodyCondition,BODYCON_DEAD_MASK) )
	{
		DelSecondWeapon();
		if( m_dwState == _FALLEN )
		{
			// 2006-01-21 by ispark, �ٵ������ ���� ����
//			ChangeSingleBodyCondition(hyBodyCondition);
			hyBodyCondition &= ~(BODYCON_CHARACTER_MODE_STOP|BODYCON_CHARACTER_MODE_RUN|BODYCON_CHARACTER_MODE_WALK);
			ChangeBodyCondition( hyBodyCondition );
		}
		else if( !COMPARE_BODYCON_BIT(GetCurrentBodyCondition(),BODYCON_EXPLOSION_MASK) )
		{
//			m_bAttackEnemy = FALSE;
//			SetPkState( PK_ALL, FALSE );
//			g_pShuttleChild->SetAttackAvaliableEnemyIndex( m_infoCharacter.ClientIndex, FALSE );
			// 2006-01-13 by ispark, Ÿ�� �ε��� ����
			m_nTargetIndex = 0;
			if( g_pShuttleChild->m_pOrderTarget == this)
			{
				g_pShuttleChild->m_pOrderTarget = NULL;
			}
			//m_infoCharacter.BodyCondition = hyBodyCondition;
			ChangeSingleBodyCondition(BODYCON_EXPLOSION_MASK);
			ChangeUnitState( _FALLING );
			
			// 2007-01-31 by dgwoo ���Ⱑ �׾��� ��� ĳ�������� ��ų�� ����Ѵ�.
			if(this->m_pSkillEffect)
				this->m_pSkillEffect->DeleteCastingStateSkillEffect();


			// 2009. 09. 21 by ckPark ���Ǵ�Ƽ �ʵ� ���� ��ų ����
			
			if( m_pSkillEffect )
				m_pSkillEffect->DeleteCastingStateMonsterSkillEffect();

			// end 2009. 09. 21 by ckPark ���Ǵ�Ƽ �ʵ� ���� ��ų ����



			// ������ �� ĳ���� ���ϴ� �͵�
			CWeapon * pNode = (CWeapon *)g_pScene->m_pWeaponData->m_pChild;
			while(pNode)
			{
				if(pNode->m_pTarget == this)
				{
					pNode->m_pTarget = NULL;

					// 2004-12-02 by ydkim ���ΰ��ݽ� ������������ Ÿ���� ����������
					if(pNode->m_dwPartType == _MINE
						&& pNode->m_dwWeaponState == _EXPLODING)
					{
						pNode->m_dwWeaponState = _NORMAL;
					}
				}
				pNode = (CWeapon *)pNode->m_pNext;
			}
			// ������� ��� ��� ��Ż

//			if(m_infoParty.bPartyType == _PARTYMASTER 
//				&& g_pShuttleChild->m_pClientParty->IsFormationFlight())
			if( m_nPartyID != 0 &&
				g_pShuttleChild->m_pClientParty->GetMasterInfo().m_nUniqueNumber == m_infoCharacter.CharacterInfo.CharacterUniqueNumber &&
				g_pShuttleChild->m_pClientParty->IsFormationFlight())
			{
				g_pShuttleChild->SendPacket(T_IC_PARTY_CANCEL_FLIGHT_POSITION);
				g_pShuttleChild->m_pClientParty->FormationFlightClear();
//				g_pShuttleChild->m_pClientParty->GetPartyInfo().bFormationFlyingPositionType = 0;
//				g_pShuttleChild->m_bFormationFlight = FALSE;
				DBGOUT("PartyMaster Is Dead.. So Cancel Flight Position\n");
			}
		}

	}
	else if(m_bEnemyCharacter == FALSE)
	{
		// 2009. 07. 07 by ckPark �κ���� ��û����(�Ѹ�, ����ȭ��, ����, A�������)
		
		// �Ѹ��� �ν��� �ִϸ��̼��� ��������Ƿ� ���´�(ü�ηѸ��ó� �Ѹ��� ������)
		if( COMPARE_BODYCON_BIT(hyBodyCondition, BODYCON_BOOSTER1_MASK | BODYCON_BOOSTER2_MASK | BODYCON_BOOSTER3_MASK | BODYCON_BOOSTER4_MASK | BODYCON_BOOSTER5_MASK) )
		{
			if( IsRobotArmor() && (m_bRollLeft || m_bRollRight) )
				return;
		}
		
		// end 2009. 07. 07 by ckPark �κ���� ��û����(�Ѹ�, ����ȭ��, ����, A�������)

		// 2006-01-21 by ispark, �ٵ������ ���� ����
//		if( COMPARE_BODYCON_BIT(GetCurrentBodyCondition(),BODYCON_BOOSTER3_MASK) && 
//			!COMPARE_BODYCON_BIT(hyBodyCondition,BODYCON_BOOSTER3_MASK))
//		{
//			ChangeSingleBodyCondition(BODYCON_BOOSTER4_MASK);
//		}
//		else
//		{
//			ChangeUnitBodyCondition( hyBodyCondition );
//			DBGOUT("(%s)Enemy ChangeBodycondition %016I64X\n", m_infoCharacter.CharacterInfo.CharacterName, hyBodyCondition);
			hyBodyCondition &= ~(BODYCON_CHARACTER_MODE_STOP|BODYCON_CHARACTER_MODE_RUN|BODYCON_CHARACTER_MODE_WALK);
			ChangeBodyCondition( hyBodyCondition );
//		}
		if(COMPARE_BODYCON_BIT(hyBodyCondition,BODYCON_LANDING_MASK))
		{
			ChangeUnitState( _LANDING );
//			DBGOUT("Enemy ChangeBodycondition[BODYCON_LANDING_MASK]\n");
		}
		else if(COMPARE_BODYCON_BIT(hyBodyCondition,BODYCON_LANDED_MASK))
		{
			ChangeUnitState( _LANDED );
			m_vMovepos = D3DXVECTOR3(0,0,0);
//			DBGOUT("Enemy ChangeBodycondition[BODYCON_LANDED_MASK]\n");
		}
		else
		{
			//DBGOUT("Enemy ChangeBodycondition[%016I64X]\n", hyBodyCondition);
			ChangeUnitState( _NORMAL );
		}
		// ������� ��� �ٵ������ ����
//		if( m_infoParty.bPartyType == _PARTYMASTER && 
		if( m_nPartyID != 0 &&
			g_pShuttleChild->m_pClientParty->GetMasterInfo().m_nUniqueNumber == m_infoCharacter.CharacterInfo.CharacterUniqueNumber &&
			g_pShuttleChild->m_pClientParty->IsFormationFlight())
		{
			if( COMPARE_BODYCON_BIT(hyBodyCondition,BODYCON_BOOSTER1_MASK) ||
				COMPARE_BODYCON_BIT(hyBodyCondition,BODYCON_BOOSTER2_MASK) ||
				COMPARE_BODYCON_BIT(hyBodyCondition,BODYCON_BOOSTER4_MASK) )
			{
				g_pShuttleChild->ChangeSingleBodyCondition(hyBodyCondition);
				g_pShuttleChild->m_nBooster = BOOSTER_TYPE_MIN;
				g_pShuttleChild->SendFieldSocketChangeBodyCondition(g_pShuttleChild->m_myShuttleInfo.ClientIndex, 
						(hyBodyCondition&(~BODYCON_FLY_MASK)) | BODYCON_SET_OR_CLEAR_MASK);
			}
			else if( COMPARE_BODYCON_BIT(hyBodyCondition,BODYCON_BOOSTER3_MASK) )
			{
//				g_pShuttleChild->ChangeSingleBodyCondition(BODYCON_BOOSTER3_MASK);
				g_pShuttleChild->m_nBooster = BOOSTER_TYPE_MAX;
				g_pShuttleChild->SendFieldSocketChangeBodyCondition(g_pShuttleChild->m_myShuttleInfo.ClientIndex, 
						BODYCON_BOOSTER3_MASK | BODYCON_SET_OR_CLEAR_MASK);
			}
			else if( COMPARE_BODYCON_BIT(hyBodyCondition,BODYCON_BOOSTER5_MASK) )
			{
				g_pShuttleChild->ChangeSingleBodyCondition(BODYCON_BOOSTER5_MASK);
				g_pShuttleChild->m_nBooster = BOOSTER_TYPE_AIRBREAK;
				g_pShuttleChild->SendFieldSocketChangeBodyCondition(g_pShuttleChild->m_myShuttleInfo.ClientIndex, 
						BODYCON_BOOSTER5_MASK | BODYCON_SET_OR_CLEAR_MASK);
			}
			else if( COMPARE_BODYCON_BIT(hyBodyCondition,BODYCON_LANDING_MASK) )
			{
				g_pShuttleChild->SendPacket(T_IC_PARTY_CANCEL_FLIGHT_POSITION);
				g_pShuttleChild->m_pClientParty->FormationFlightClear();
//				g_pShuttleChild->m_infoParty.bFormationFlyingPositionType = 0;
//				g_pShuttleChild->m_bFormationFlight = FALSE;
				g_pShuttleChild->ChangeSingleBodyCondition(BODYCON_LANDING_MASK);
				if(g_pD3dApp->m_pCamera->m_bCamType == CAMERA_TYPE_FPS)
				{
					g_pD3dApp->m_pCamera->ChangeCamType();
					g_pShuttleChild->m_bLandingOldCamtypeFPS = TRUE;
				}
				g_pShuttleChild->m_fAniFlag = 0;
				g_pShuttleChild->m_fNumpad0keyTime = 0.0f;
				g_pShuttleChild->TryLandingState();
			}
		}
	}
	else
	{
		// ĳ���� �ٵ� �����
		// ������ ���� �����

	}
}


//void CEnemyData::FormationFlight(D3DXVECTOR3& vPos, D3DXVECTOR3& vTarget, D3DXVECTOR3& vUp, D3DXVECTOR3& vSide, BYTE bFormType, BYTE bPositionType)
//{
//
//	FLOG( "CShuttleChild::FormationFlight()" );
//	
//	switch(bFormType)
//	{
//	case FLIGHT_FORM_2_COLUMN:// �̿� ���� ���
//			FormationFlightType1(vPos,vTarget,vUp,vSide,bPositionType);
//		break;
//	case FLIGHT_FORM_2_LINE:// �̿� Ⱦ�� ���
//			FormationFlightType2(vPos,vTarget,vUp,vSide,bPositionType);
//		break;
//	case FLIGHT_FORM_TRIANGLE:// �ﰢ ���
//			FormationFlightType3(vPos,vTarget,vUp,vSide,bPositionType);
//		break;
//	case FLIGHT_FORM_INVERTED_TRIANGLE:// ���ﰢ ���
//			FormationFlightType4(vPos,vTarget,vUp,vSide,bPositionType);
//		break;
//	case FLIGHT_FORM_BELL:// �� ���
//			FormationFlightType5(vPos,vTarget,vUp,vSide,bPositionType);
//		break;
//	case FLIGHT_FORM_INVERTED_BELL:// ���� ���
//			FormationFlightType6(vPos,vTarget,vUp,vSide,bPositionType);
//		break;
//	case FLIGHT_FORM_X:// X-�� ���
//			FormationFlightType7(vPos,vTarget,vUp,vSide,bPositionType);
//		break;
//	case FLIGHT_FORM_STAR:// Star-�� ���
//			FormationFlightType8(vPos,vTarget,vUp,vSide,bPositionType);
//		break;
//	}
//}
//
//void CEnemyData::FormationFlightType1(D3DXVECTOR3& vPos, D3DXVECTOR3& vTarget, D3DXVECTOR3& vUp, D3DXVECTOR3& vSide, BYTE bPositionType)// �̿�������
//{
//	FLOG( "CShuttleChild::FormationFlightType1()" );
//	float fElapsedTime = g_pD3dApp->GetElapsedTime();
//	
//		switch(bPositionType)
//		{
//		case 1:
//			{
//				m_vNextPos = vPos - 30.0f*vSide;
//			}
//			break;
//		case 2:
//			{
//				m_vNextPos = vPos - 30.0f*vTarget;
//			}
//			break;
//		case 3:
//			{
//				m_vNextPos = vPos - 30.0f*vTarget - 30.0f*vSide;
//			}
//			break;
//		case 4:
//			{
//				m_vNextPos = vPos - 60.0f*vTarget;
//			}
//			break;
//		case 5:
//			{
//				m_vNextPos = vPos - 60.0f*vTarget - 30.0f*vSide;
//			}
//			break;
//		default:
//			{
//				//m_bFormationFlight = FALSE; // error
//				//m_infoParty.bFormationFlyingPositionType = 0;
//			}
//		}
//		SetPosition( m_vNextPos, vTarget, vUp);
//}
//
//void CEnemyData::FormationFlightType2(D3DXVECTOR3& vPos, D3DXVECTOR3& vTarget, D3DXVECTOR3& vUp, D3DXVECTOR3& vSide, BYTE bPositionType)// �̿�Ⱦ����
//{
//	FLOG( "CShuttleChild::FormationFlightType2()" );
//	float fElapsedTime = g_pD3dApp->GetElapsedTime();
//	
///*		float fAngle;
//		D3DXMATRIX matTemp;
//		fAngle = ACOS(D3DXVec3Dot(&m_vVel,&vTarget))*fElapsedTime;
//		if(fAngle)
//		{
//			D3DXVec3Cross(&vSide,&m_vVel,&vTarget);
//			D3DXMatrixRotationAxis(&matTemp,&vSide,fAngle);
//			D3DXVec3TransformCoord(&m_vVel,&m_vVel,&matTemp);
//		}
//		fAngle = ACOS(D3DXVec3Dot(&m_vUp,&vUp))*fElapsedTime;
//		if(fAngle)
//		{
//			D3DXVec3Cross(&vSide,&m_vUp,&vUp);
//			D3DXMatrixRotationAxis(&matTemp,&vSide,fAngle);
//			D3DXVec3TransformCoord(&m_vUp,&m_vUp,&matTemp);
//		}
//*/
//		
//		switch(bPositionType)
//		{
//		case 1:
//			{
//				m_vNextPos = vPos - 30.0f*vSide;
//			}
//			break;
//		case 2:
//			{
//				m_vNextPos = vPos + 30.0f*vSide;
//			}
//			break;
//		case 3:
//			{
//				m_vNextPos = vPos - 30.0f*vTarget;
//			}
//			break;
//		case 4:
//			{
//				m_vNextPos = vPos - 30.0f*vTarget - 30.0f*vSide;
//			}
//			break;
//		case 5:
//			{
//				m_vNextPos = vPos - 30.0f*vTarget + 30.0f*vSide;
//			}
//			break;
//		default:
//			{
//				//m_bFormationFlight = FALSE; // error
//				//m_infoParty.bFormationFlyingPositionType = 0;
//			}
//		}
//		
//		SetPosition( m_vNextPos, vTarget, vUp);
//
//}
//
//void CEnemyData::FormationFlightType3(D3DXVECTOR3& vPos, D3DXVECTOR3& vTarget, D3DXVECTOR3& vUp, D3DXVECTOR3& vSide, BYTE bPositionType)// �ﰢ ��� ��
//{
//	FLOG( "CShuttleChild::FormationFlightType3()" );
//	float fElapsedTime = g_pD3dApp->GetElapsedTime();
//
//		
///*		float fAngle;
//		D3DXMATRIX matTemp;
//		fAngle = ACOS(D3DXVec3Dot(&m_vVel,&vTarget))*fElapsedTime;
//		if(fAngle)
//		{
//			D3DXVec3Cross(&vSide,&m_vVel,&vTarget);
//			D3DXMatrixRotationAxis(&matTemp,&vSide,fAngle);
//			D3DXVec3TransformCoord(&m_vVel,&m_vVel,&matTemp);
//		}
//		fAngle = ACOS(D3DXVec3Dot(&m_vUp,&vUp))*fElapsedTime;
//		if(fAngle)
//		{
//			D3DXVec3Cross(&vSide,&m_vUp,&vUp);
//			D3DXMatrixRotationAxis(&matTemp,&vSide,fAngle);
//			D3DXVec3TransformCoord(&m_vUp,&m_vUp,&matTemp);
//		}
//*/
//		
//		switch(bPositionType)
//		{
//		case 1:
//			{
//				m_vNextPos = vPos - 30.0f*vTarget - 15.0f*vSide;
//			}
//			break;
//		case 2:
//			{
//				m_vNextPos = vPos - 30.0f*vTarget + 15.0f*vSide;
//			}
//			break;
//		case 3:
//			{
//				m_vNextPos = vPos - 60.0f*vTarget - 30.0f*vSide;
//			}
//			break;
//		case 4:
//			{
//				m_vNextPos = vPos - 60.0f*vTarget + 30.0f*vSide;
//			}
//			break;
//		case 5:
//			{
//				m_vNextPos = vPos - 60.0f*vTarget;
//			}
//			break;
//		default:
//			{
//				//m_bFormationFlight = FALSE; // error
//				//m_infoParty.bFormationFlyingPositionType = 0;
//			}
//		}
//		
//		SetPosition( m_vNextPos, vTarget, vUp);
//
//}
//
//void CEnemyData::FormationFlightType4(D3DXVECTOR3& vPos, D3DXVECTOR3& vTarget, D3DXVECTOR3& vUp, D3DXVECTOR3& vSide, BYTE bPositionType)// ���ﰢ ��
//{
//	FLOG( "CShuttleChild::FormationFlightType4()" );
//	float fElapsedTime = g_pD3dApp->GetElapsedTime();
//
//		
///*		float fAngle;
//		D3DXMATRIX matTemp;
//		fAngle = ACOS(D3DXVec3Dot(&m_vVel,&vTarget))*fElapsedTime;
//		if(fAngle)
//		{
//			D3DXVec3Cross(&vSide,&m_vVel,&vTarget);
//			D3DXMatrixRotationAxis(&matTemp,&vSide,fAngle);
//			D3DXVec3TransformCoord(&m_vVel,&m_vVel,&matTemp);
//		}
//		fAngle = ACOS(D3DXVec3Dot(&m_vUp,&vUp))*fElapsedTime;
//		if(fAngle)
//		{
//			D3DXVec3Cross(&vSide,&m_vUp,&vUp);
//			D3DXMatrixRotationAxis(&matTemp,&vSide,fAngle);
//			D3DXVec3TransformCoord(&m_vUp,&m_vUp,&matTemp);
//		}
//*/
//		
//		switch(bPositionType)
//		{
//		case 1:
//			{
//				m_vNextPos = vPos - 30.0f*vSide;
//			}
//			break;
//		case 2:
//			{
//				m_vNextPos = vPos + 30.0f*vSide;
//			}
//			break;
//		case 3:
//			{
//				m_vNextPos = vPos - 30.0f*vTarget - 15.0f*vSide;
//			}
//			break;
//		case 4:
//			{
//				m_vNextPos = vPos - 30.0f*vTarget + 15.0f*vSide;
//			}
//			break;
//		case 5:
//			{
//				m_vNextPos = vPos - 60.0f*vTarget;
//			}
//			break;
//		default:
//			{
//				//m_bFormationFlight = FALSE; // error
//				//m_infoParty.bFormationFlyingPositionType = 0;
//			}
//		}
//		
//		SetPosition( m_vNextPos, vTarget, vUp);
//
//}
//
//void CEnemyData::FormationFlightType5(D3DXVECTOR3& vPos, D3DXVECTOR3& vTarget, D3DXVECTOR3& vUp, D3DXVECTOR3& vSide, BYTE bPositionType)// �� ��
//{
//	FLOG( "CShuttleChild::FormationFlightType5()" );
//	float fElapsedTime = g_pD3dApp->GetElapsedTime();
//
//		
///*		float fAngle;
//		D3DXMATRIX matTemp;
//		fAngle = ACOS(D3DXVec3Dot(&m_vVel,&vTarget))*fElapsedTime;
//		if(fAngle)
//		{
//			D3DXVec3Cross(&vSide,&m_vVel,&vTarget);
//			D3DXMatrixRotationAxis(&matTemp,&vSide,fAngle);
//			D3DXVec3TransformCoord(&m_vVel,&m_vVel,&matTemp);
//		}
//		fAngle = ACOS(D3DXVec3Dot(&m_vUp,&vUp))*fElapsedTime;
//		if(fAngle)
//		{
//			D3DXVec3Cross(&vSide,&m_vUp,&vUp);
//			D3DXMatrixRotationAxis(&matTemp,&vSide,fAngle);
//			D3DXVec3TransformCoord(&m_vUp,&m_vUp,&matTemp);
//		}
//*/
//		
//		switch(bPositionType)
//		{
//		case 1:
//			{
//				m_vNextPos = vPos - 30.0f*vTarget;
//			}
//			break;
//		case 2:
//			{
//				m_vNextPos = vPos - 30.0f*vTarget - 30.0f*vSide;
//			}
//			break;
//		case 3:
//			{
//				m_vNextPos = vPos - 30.0f*vTarget + 30.0f*vSide;
//			}
//			break;
//		case 4:
//			{
//				m_vNextPos = vPos - 60.0f*vTarget - 15.0f*vSide;
//			}
//			break;
//		case 5:
//			{
//				m_vNextPos = vPos - 60.0f*vTarget + 15.0f*vSide;
//			}
//			break;
//		default:
//			{
//				//m_bFormationFlight = FALSE; // error
//				//m_infoParty.bFormationFlyingPositionType = 0;
//			}
//		}
//
//		SetPosition( m_vNextPos, vTarget, vUp);
//
//}
//
//void CEnemyData::FormationFlightType6(D3DXVECTOR3& vPos, D3DXVECTOR3& vTarget, D3DXVECTOR3& vUp, D3DXVECTOR3& vSide, BYTE bPositionType)// ���� ��
//{
//	FLOG( "CShuttleChild::FormationFlightType6()" );
//	float fElapsedTime = g_pD3dApp->GetElapsedTime();
//
//		
///*		float fAngle;
//		D3DXMATRIX matTemp;
//		fAngle = ACOS(D3DXVec3Dot(&m_vVel,&vTarget))*fElapsedTime;
//		if(fAngle)
//		{
//			D3DXVec3Cross(&vSide,&m_vVel,&vTarget);
//			D3DXMatrixRotationAxis(&matTemp,&vSide,fAngle);
//			D3DXVec3TransformCoord(&m_vVel,&m_vVel,&matTemp);
//		}
//		fAngle = ACOS(D3DXVec3Dot(&m_vUp,&vUp))*fElapsedTime;
//		if(fAngle)
//		{
//			D3DXVec3Cross(&vSide,&m_vUp,&vUp);
//			D3DXMatrixRotationAxis(&matTemp,&vSide,fAngle);
//			D3DXVec3TransformCoord(&m_vUp,&m_vUp,&matTemp);
//		}
//*/
//		
//		switch(bPositionType)
//		{
//		case 1:
//			{
//				m_vNextPos = vPos - 30.0f*vSide;
//			}
//			break;
//		case 2:
//			{
//				m_vNextPos = vPos - 30.0f*vTarget - 15.0f*vSide;
//			}
//			break;
//		case 3:
//			{
//				m_vNextPos = vPos - 30.0f*vTarget + 15.0f*vSide;
//			}
//			break;
//		case 4:
//			{
//				m_vNextPos = vPos - 30.0f*vTarget - 45.0f*vSide;
//			}
//			break;
//		case 5:
//			{
//				m_vNextPos = vPos - 60.0f*vTarget - 15.0f*vSide;
//			}
//			break;
//		default:
//			{
//				//m_bFormationFlight = FALSE; // error
//				//m_infoParty.bFormationFlyingPositionType = 0;
//			}
//		}
//
//		SetPosition( m_vNextPos, vTarget, vUp);
//
//}
//
//void CEnemyData::FormationFlightType7(D3DXVECTOR3& vPos, D3DXVECTOR3& vTarget, D3DXVECTOR3& vUp, D3DXVECTOR3& vSide, BYTE bPositionType)// X-��
//{
//	FLOG( "CShuttleChild::FormationFlightType7()" );
//	float fElapsedTime = g_pD3dApp->GetElapsedTime();
//
//		
///*		float fAngle;
//		D3DXMATRIX matTemp;
//		fAngle = ACOS(D3DXVec3Dot(&m_vVel,&vTarget))*fElapsedTime;
//		if(fAngle)
//		{
//			D3DXVec3Cross(&vSide,&m_vVel,&vTarget);
//			D3DXMatrixRotationAxis(&matTemp,&vSide,fAngle);
//			D3DXVec3TransformCoord(&m_vVel,&m_vVel,&matTemp);
//		}
//		fAngle = ACOS(D3DXVec3Dot(&m_vUp,&vUp))*fElapsedTime;
//		if(fAngle)
//		{
//			D3DXVec3Cross(&vSide,&m_vUp,&vUp);
//			D3DXMatrixRotationAxis(&matTemp,&vSide,fAngle);
//			D3DXVec3TransformCoord(&m_vUp,&m_vUp,&matTemp);
//		}
//*/
//		
//		switch(bPositionType)
//		{
//		case 1:
//			{
//				m_vNextPos = vPos - 30.0f*vSide + 30.0f*vUp - 30.0f*vTarget;
//			}
//			break;
//		case 2:
//			{
//				m_vNextPos = vPos + 30.0f*vSide + 30.0f*vUp - 30.0f*vTarget;
//			}
//			break;
//		case 3:
//			{
//				m_vNextPos = vPos - 30.0f*vSide - 30.0f*vUp - 30.0f*vTarget;
//			}
//			break;
//		case 4:
//			{
//				m_vNextPos = vPos + 30.0f*vSide - 30.0f*vUp - 30.0f*vTarget;
//			}
//			break;
//		case 5:
//			{
//				m_vNextPos = vPos - 30.0f*vTarget;
//			}
//			break;
//		default:
//			{
//				//m_bFormationFlight = FALSE; // error
//				//m_infoParty.bFormationFlyingPositionType = 0;
//			}
//		}
//
//		SetPosition( m_vNextPos, vTarget, vUp);
//
//}
//void CEnemyData::FormationFlightType8(D3DXVECTOR3& vPos, D3DXVECTOR3& vTarget, D3DXVECTOR3& vUp, D3DXVECTOR3& vSide, BYTE bPositionType)// Star-��
//{
//	FLOG( "CShuttleChild::FormationFlightType8()" );
//	float fElapsedTime = g_pD3dApp->GetElapsedTime();
//
//		
///*		float fAngle;
//		D3DXMATRIX matTemp;
//		fAngle = ACOS(D3DXVec3Dot(&m_vVel,&vTarget))*fElapsedTime;
//		if(fAngle)
//		{
//			D3DXVec3Cross(&vSide,&m_vVel,&vTarget);
//			D3DXMatrixRotationAxis(&matTemp,&vSide,fAngle);
//			D3DXVec3TransformCoord(&m_vVel,&m_vVel,&matTemp);
//		}
//		fAngle = ACOS(D3DXVec3Dot(&m_vUp,&vUp))*fElapsedTime;
//		if(fAngle)
//		{
//			D3DXVec3Cross(&vSide,&m_vUp,&vUp);
//			D3DXMatrixRotationAxis(&matTemp,&vSide,fAngle);
//			D3DXVec3TransformCoord(&m_vUp,&m_vUp,&matTemp);
//		}
//*/
//		
//		switch(bPositionType)
//		{
//		case 1:
//			{
//				m_vNextPos = vPos + 30.0f*vUp;
//			}
//			break;
//		case 2:
//			{
//				m_vNextPos = vPos + 20.0f*vSide + 10.0f*vUp;
//			}
//			break;
//		case 3:
//			{
//				m_vNextPos = vPos - 20.0f*vSide + 10.0f*vUp;
//			}
//			break;
//		case 4:
//			{
//				m_vNextPos = vPos + 15.0f*vSide - 10.0f*vUp;
//			}
//			break;
//		case 5:
//			{
//				m_vNextPos = vPos - 15.0f*vSide - 10.0f*vUp;
//			}
//			break;
//		default:
//			{
//				//m_bFormationFlight = FALSE; // error
//				//m_infoParty.bFormationFlyingPositionType = 0;
//			}
//		}
//
//		SetPosition( m_vNextPos, vTarget, vUp);
//
//}


/*
void CEnemyData::DeleteChild(CAtumNode * pNode)
{
	CAtumNode * pChild = (CAtumNode *)pNode->m_pChild;
	while(pChild)
	{
		if(pChild->m_pChild)
			DeleteChild(pChild);
		else
			pChild->m_bUsing = FALSE;
		pChild = (CAtumNode *)pChild->m_pNext;
	}
}
*/
void CEnemyData::Render()
{
	FLOG( "CEnemyData::Render()" );
	
	if(m_bDegree == 2) 
	{ 
		// 2010. 03. 18 by jskim ���ͺ��� ī��
		//g_pD3dDev->SetRenderState( D3DRS_SPECULARENABLE, TRUE ); 
		if(m_MonsterTransformer)
		{
			g_pD3dDev->SetRenderState( D3DRS_SPECULARENABLE, FALSE ); 
		}
		else
		{
			g_pD3dDev->SetRenderState( D3DRS_SPECULARENABLE, TRUE ); 
		}	
		//end 2010. 03. 18 by jskim ���ͺ��� ī��
	}

	// 2005-07-26 by ispark
	// ĳ���� Rendering
	if(m_bEnemyCharacter)
	{
		// ĳ�����϶� Speculare�� ����.
		g_pD3dDev->SetRenderState( D3DRS_SPECULARENABLE, FALSE );
		g_pD3dDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		g_pD3dDev->SetRenderState( D3DRS_ZENABLE,  TRUE );
		g_pD3dDev->SetRenderState( D3DRS_LIGHTING, TRUE );
		g_pD3dDev->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
		g_pD3dDev->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
		g_pD3dDev->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
		g_pD3dDev->SetRenderState( D3DRS_ALPHATESTENABLE,  TRUE );
		g_pD3dDev->SetRenderState( D3DRS_ALPHAFUNC,  D3DCMP_GREATER );
		g_pD3dDev->SetRenderState( D3DRS_ALPHAREF,  0x00000088 );
	
		m_pCharacterRender->Render(this);
	}
	else
	{
		
		if(GetUnitAlphaState() != CL_SKILL_NONE)
		{
			SetAlphaData();
		}
		

		// 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����

// 		int nArmorColor;
// 		if(m_infoCharacter.CharacterRenderInfo.RI_ArmorColorCode == 0)
// 			nArmorColor = 0;
// 		else
// 			nArmorColor = max(1, m_infoCharacter.CharacterRenderInfo.RI_ArmorColorCode%100);
// 		((CUnitRender*)m_pRender)->Render(this, nArmorColor);

		// �Ƹ� Į��� ���� ������� �ʴ´�
		// 2011-07-18 by jhahn ����3�� �ó׸� Ÿĳ���� �Ⱥ��̱�
		if (m_bRender)					
		((CUnitRender*)m_pRender)->Render( this, 0 );
		//end 2011-07-18 by jhahn ����3�� �ó׸� Ÿĳ���� �Ⱥ��̱�

		// end 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����

	}

	if(m_bDegree == 2)
	{
		g_pD3dDev->SetRenderState( D3DRS_SPECULARENABLE, FALSE );
	}
}

void CEnemyData::SetPosition(MSG_FC_MOVE_OK* pMsg)
{
	FLOG( "CEnemyData::SetPosition(MSG_FC_MOVE_OK* pMsg)" );
	// 2006-01-13 by ispark, 
	// m_bSetPosition�� Enemy�� ���� ���� Ȯ���� ������ ����Ÿ��� �˸���. 
	// �� �̸��� ���� ������ ������ ���� �ϳ��� �־���. ó������ ���Ⱚ�� ���� �� �ֱ� ������
	// ��Ʈ������ ����� ����. �׷��� �������� �� �� �ʰ� ���Ծ���. 
	m_bSetPosition = TRUE;	
	// 2005-07-29 by ispark
	// Move�� ĳ�������� �������� �Ǵ�.
	if(pMsg->moveBitFlag.CharacterMode0 != m_bEnemyCharacter)
	{
		if(pMsg->moveBitFlag.CharacterMode0 == FALSE)
		{
			m_bEnemyCharacter = FALSE;
			m_infoCharacter.CharacterInfo.CharacterMode0 = 0;				// 2006-09-27 by ispark
			ChangeUnitState(_NORMAL);
			InitItemPoint();												// 2006-10-20 by ispark, ����Ʈ �����
		}
		else
		{
			m_bEnemyCharacter = TRUE;
			m_infoCharacter.CharacterInfo.CharacterMode0 = 1;				// 2006-09-27 by ispark
			InitItemPoint();												// 2006-10-20 by ispark, ����Ʈ �����
		}
	}

	if(m_fLifeTime < 0.0f)
	{
		m_vPos = A2DX(pMsg->PositionVector);
		m_vNextPos = A2DX(pMsg->PositionVector);
	}
	else
	{
		m_vNextPos = A2DX(pMsg->PositionVector);
	}

	// FC_MOVE_TARGET : shuttlechild�� ���������� ���, ���� �Ÿ��� ����ϸ� �ش� ĳ���Ϳ��� ������.
	if( UNIT_STATE_NO_MOVE(g_pShuttleChild->m_dwState) && 
		g_pD3dApp->Distance3DTo2D(g_pShuttleChild->m_vPos, m_vPos) > SEND_FC_TARGET_DISTANCE &&
		g_pD3dApp->Distance3DTo2D(g_pShuttleChild->m_vPos, m_vNextPos) < SEND_FC_TARGET_DISTANCE)
	{
//		MSG_FC_MOVE_TARGET sMsg;
//		sMsg.ClientIndex = m_infoCharacter.CharacterInfo.ClientIndex;
//		g_pFieldWinSocket->SendMsg( T_FC_MOVE_TARGET, (char*)&sMsg, sizeof(sMsg));
//		DBGOUT("**************    Second FC_MOVE_TARGET:Index[%d]    �Ÿ��� SEND_FC_TARGET_DISTANCE ������ ����*****************\n",m_infoCharacter.CharacterInfo.ClientIndex);
		SetClientIndexDataByVector(g_pD3dApp->m_vecMoveTarget, m_infoCharacter.CharacterInfo.ClientIndex);
	}

	m_bRequestMove = FALSE;
	D3DXVec3Normalize(&m_vOriNextVel,&A2DX(pMsg->TargetVector));
	D3DXVec3Normalize(&m_vOriNextUp,&A2DX(pMsg->UpVector));
	// ĳ���� ���ڱ� ������ �ȵɽ� �Ʒ� �ڵ�� �����͸� ��������
//	m_vUp = pMsg->UpVector;

	float fLength = D3DXVec3Length(&(m_vNextPos - m_vPos));
	// �Ÿ����� �߻� ������ ���������� ����Ѵ�.-������ �ӵ��� ����Ͽ� ���
	m_vExpectPos = m_vNextPos + (m_vNextPos - m_vPos);//*5.0f;//*fLength;
	m_vMovepos = m_vExpectPos - m_vPos;
//	fLength = D3DXVec3Length(&m_vMovepos);
	// ���� �ӵ��� ��Ʋ�� �ִ� �ӵ����� ũ�� �ִ� �ӵ���ŭ�� ũ��� �ٿ�����Ѵ�.
	if(fLength > 800.0f)
	{
		D3DXVec3Normalize(&m_vMovepos,&m_vMovepos);
		m_vPos = m_vNextPos;
		DBGOUT("Enemy : Different Position to Server \n");// ��ǥ ���̰� ���� ���� �ѹ��� �̵��մϴ�.\n
	}
	// 2007-04-09 by bhsohn ĳ���� �ִϸ��̼� ��� �����̴� ���� ó��
 	else if(fLength < 3.0f)
	{
		m_vPos = m_vNextPos;
		m_vMovepos = D3DXVECTOR3(0,0,0);
	}
/*	// ����� �����ʹ� ��ǥó�� ũ�� ������ ���� �����Ƿ� Expect�� ������ �ʰڴ�.
	if(D3DXVec3Length(&(m_vNextVel-m_vVel)) < 0.3f)
	{
		m_vMoveVel = D3DXVECTOR3(0,0,0);
		m_vVel = m_vNextVel;
	}
	else
		m_vMoveVel = m_vNextVel - m_vVel;
*/
	D3DXVec3Normalize(&m_vNextVel,&(m_vVel + (m_vOriNextVel - m_vVel)*1.5f));
	D3DXVec3Normalize(&m_vOriNextVel,&(m_vVel + (m_vOriNextVel - m_vVel)*1.3f));
	m_vMoveVel = m_vNextVel - m_vVel;
	D3DXVec3Normalize(&m_vNextUp,&(m_vUp + (m_vOriNextUp - m_vUp)*1.5f));
	D3DXVec3Normalize(&m_vOriNextUp,&(m_vUp + (m_vOriNextUp - m_vUp)*1.3f));
	m_vMoveUp = m_vNextUp - m_vUp;

//	m_vMoveUp = m_vNextUp - m_vUp;
	if(m_fLifeTime < -3.0f)
		DBGOUT("$$$$ Dangerous LifeTime (%s)Enemy Time = %f\n",m_infoCharacter.CharacterInfo.CharacterName, m_fLifeTime);
	m_fLifeTime = 2.0f;
#ifdef _DEBUG
	m_nDebugMoveCount++;
#endif

	// 2005-07-27 by ispark
	// �׽�Ʈ
//	DBGOUT("ID : %s(%d%d)\n", m_infoCharacter.CharacterInfo.CharacterName, m_infoCharacter.CharacterInfo.CharacterMode0, m_bEnemyCharacter);
//	DBGOUT("Pos: %f %f %f\n", m_vPos.x, m_vPos.y, m_vPos.z);
//	DBGOUT("Vel: %f %f %f\n", m_vVel.x, m_vVel.y, m_vVel.z);
//	DBGOUT("Up: %f %f %f\n", m_vUp.x, m_vUp.y, m_vUp.z);
}

void CEnemyData::CheckShadowPos(BOOL bOnObject)
{
	FLOG( "CEnemyData::CheckShadowPos()" );
	D3DXVECTOR3 vTempShadowPos[4];
	if( IsTileMapRenderEnable(g_pShuttleChild->m_myShuttleInfo.MapChannelIndex.MapIndex) == FALSE &&
		bOnObject == FALSE)
	{
		m_bShadowIsRender = FALSE;
		return;
	}
	D3DXMATRIX matTemp;
	D3DXVec3Normalize( &m_vSideVel, &m_vSideVel );
	m_vShadowPos1 = m_vPos+m_fObjectSize*(m_vVel+m_vSideVel);
	m_vShadowPos2 = m_vPos+m_fObjectSize*(m_vVel-m_vSideVel);
	m_vShadowPos3 = m_vPos-m_fObjectSize*(m_vVel+m_vSideVel);
	m_vShadowPos4 = m_vPos-m_fObjectSize*(m_vVel-m_vSideVel);

//	FLOAT fBary1, fBary2;
	FLOAT fDist;
	int i,j;
	i = (int)(m_vShadowPos1.x/TILE_SIZE);
	j = (int)(m_vShadowPos1.z/TILE_SIZE);
	D3DXVECTOR3 v,orig,dir,vPos,vSide;//,v2;
	orig = m_vShadowPos1;
	dir = D3DXVECTOR3(0,-1,0);
	vSide = D3DXVECTOR3(0,0,1);
	
	if(i >= 0 && i < g_pGround->m_projectInfo.sXSize && j >= 0 && j < g_pGround->m_projectInfo.sYSize)
	{
		if(g_pGround->IntersectTriangle(orig,dir,g_pGround->m_pTileVertexArray[i*(g_pGround->m_projectInfo.sYSize+1)+j].pos,
			g_pGround->m_pTileVertexArray[i*(g_pGround->m_projectInfo.sYSize+1)+(j+1)].pos,
			g_pGround->m_pTileVertexArray[(i+1)*(g_pGround->m_projectInfo.sYSize+1)+(j)].pos,
			&fDist))//, &fBary1, &fBary2 ))
		{
			m_vShadowPos1 = orig + dir*fDist;
			if(g_pShuttleChild->CheckIsWater(orig))
			{
				if(m_vShadowPos1.y < g_pGround->m_projectInfo.fWaterHeight)
					m_vShadowPos1.y = g_pGround->m_projectInfo.fWaterHeight;
			}
			vTempShadowPos[0] = m_vShadowPos1;
			float fTempHeight = DEFAULT_COLLISION_DISTANCE;// = 100.0f;
			if(bOnObject)
			{
				D3DXMatrixLookAtLH(&matTemp,&orig,&(orig + dir),&vSide);
				fTempHeight = g_pScene->m_pObjectRender->CheckCollMesh(matTemp,orig).fDist;
				if(m_vShadowPos1.y < orig.y - fTempHeight)
					m_vShadowPos1.y = orig.y - fTempHeight;
				else if(IsTileMapRenderEnable(g_pShuttleChild->m_myShuttleInfo.MapChannelIndex.MapIndex) == FALSE)
					m_bShadowIsRender = FALSE;
			}
		}
		else if(g_pGround->IntersectTriangle(orig,dir,g_pGround->m_pTileVertexArray[i*(g_pGround->m_projectInfo.sYSize+1)+j+1].pos,
			g_pGround->m_pTileVertexArray[(i+1)*(g_pGround->m_projectInfo.sYSize+1)+(j)].pos,
			g_pGround->m_pTileVertexArray[(i+1)*(g_pGround->m_projectInfo.sYSize+1)+j+1].pos,
			&fDist))//, &fBary1, &fBary2 ))
		{
			m_vShadowPos1 = orig + dir*fDist;
			if(g_pShuttleChild->CheckIsWater(orig))
			{
				if(m_vShadowPos1.y < g_pGround->m_projectInfo.fWaterHeight)
					m_vShadowPos1.y = g_pGround->m_projectInfo.fWaterHeight;
			}
			vTempShadowPos[0] = m_vShadowPos1;
			float fTempHeight = DEFAULT_COLLISION_DISTANCE;// = 100.0f;
			if(	bOnObject )
			{
				D3DXMatrixLookAtLH(&matTemp,&orig,&(orig + dir),&vSide);
				fTempHeight = g_pScene->m_pObjectRender->CheckCollMesh(matTemp,orig).fDist;
				if(m_vShadowPos1.y < orig.y - fTempHeight)
					m_vShadowPos1.y = orig.y - fTempHeight;
				else if(IsTileMapRenderEnable(g_pShuttleChild->m_myShuttleInfo.MapChannelIndex.MapIndex) == FALSE)
					m_bShadowIsRender = FALSE;
			}
		}
	}
	i = (int)(m_vShadowPos2.x/TILE_SIZE);
	j = (int)(m_vShadowPos2.z/TILE_SIZE);
	orig = m_vShadowPos2;
	dir = D3DXVECTOR3(0,-1,0);
	if(i >= 0 && i < g_pGround->m_projectInfo.sXSize && j >= 0 && j < g_pGround->m_projectInfo.sYSize)
	{
		if(g_pGround->IntersectTriangle(orig,dir,g_pGround->m_pTileVertexArray[i*(g_pGround->m_projectInfo.sYSize+1)+j].pos,
			g_pGround->m_pTileVertexArray[i*(g_pGround->m_projectInfo.sYSize+1)+(j+1)].pos,
			g_pGround->m_pTileVertexArray[(i+1)*(g_pGround->m_projectInfo.sYSize+1)+(j)].pos,
			&fDist))//, &fBary1, &fBary2 ))
		{
			m_vShadowPos2 = orig + dir*fDist;
			if(g_pShuttleChild->CheckIsWater(orig))
			{
				if(m_vShadowPos2.y < g_pGround->m_projectInfo.fWaterHeight)
					m_vShadowPos2.y = g_pGround->m_projectInfo.fWaterHeight;
			}
			vTempShadowPos[1] = m_vShadowPos2;
			float fTempHeight = DEFAULT_COLLISION_DISTANCE;// = 100.0f;
			if(bOnObject)
			{
				D3DXMatrixLookAtLH(&matTemp,&orig,&(orig + dir),&vSide);
				fTempHeight = g_pScene->m_pObjectRender->CheckCollMesh(matTemp,orig).fDist;
				if(m_vShadowPos2.y < orig.y - fTempHeight)
					m_vShadowPos2.y = orig.y - fTempHeight;
				else if(IsTileMapRenderEnable(g_pShuttleChild->m_myShuttleInfo.MapChannelIndex.MapIndex) == FALSE)
					m_bShadowIsRender = FALSE;
			}
		}
		else if(g_pGround->IntersectTriangle(orig,dir,g_pGround->m_pTileVertexArray[i*(g_pGround->m_projectInfo.sYSize+1)+j+1].pos,
			g_pGround->m_pTileVertexArray[(i+1)*(g_pGround->m_projectInfo.sYSize+1)+(j)].pos,
			g_pGround->m_pTileVertexArray[(i+1)*(g_pGround->m_projectInfo.sYSize+1)+j+1].pos,
			&fDist))//, &fBary1, &fBary2 ))
		{
			m_vShadowPos2 = orig + dir*fDist;
			if(g_pShuttleChild->CheckIsWater(orig))
			{
				if(m_vShadowPos2.y < g_pGround->m_projectInfo.fWaterHeight)
					m_vShadowPos2.y = g_pGround->m_projectInfo.fWaterHeight;
			}
			vTempShadowPos[1] = m_vShadowPos2;
			float fTempHeight = DEFAULT_COLLISION_DISTANCE;// = 100.0f;
			if(bOnObject)
			{
				D3DXMatrixLookAtLH(&matTemp,&orig,&(orig + dir),&vSide);
				fTempHeight = g_pScene->m_pObjectRender->CheckCollMesh(matTemp,orig).fDist;
				if(m_vShadowPos2.y < orig.y - fTempHeight)
					m_vShadowPos2.y = orig.y - fTempHeight;
				else if(IsTileMapRenderEnable(g_pShuttleChild->m_myShuttleInfo.MapChannelIndex.MapIndex) == FALSE)
					m_bShadowIsRender = FALSE;
			}
		}
	}
	i = (int)(m_vShadowPos3.x/TILE_SIZE);
	j = (int)(m_vShadowPos3.z/TILE_SIZE);
	orig = m_vShadowPos3;
	dir = D3DXVECTOR3(0,-1,0);
	if(i >= 0 && i < g_pGround->m_projectInfo.sXSize && j >= 0 && j < g_pGround->m_projectInfo.sYSize)
	{
		if(g_pGround->IntersectTriangle(orig,dir,g_pGround->m_pTileVertexArray[i*(g_pGround->m_projectInfo.sYSize+1)+j].pos,
			g_pGround->m_pTileVertexArray[i*(g_pGround->m_projectInfo.sYSize+1)+(j+1)].pos,
			g_pGround->m_pTileVertexArray[(i+1)*(g_pGround->m_projectInfo.sYSize+1)+(j)].pos,
			&fDist))//, &fBary1, &fBary2 ))
		{
			m_vShadowPos3 = orig + dir*fDist;
			if(g_pShuttleChild->CheckIsWater(orig))
			{
				if(m_vShadowPos3.y < g_pGround->m_projectInfo.fWaterHeight)
					m_vShadowPos3.y = g_pGround->m_projectInfo.fWaterHeight;
			}
			vTempShadowPos[2] = m_vShadowPos3;
			float fTempHeight = DEFAULT_COLLISION_DISTANCE;// = 100.0f;
			if( bOnObject )
			{
				D3DXMatrixLookAtLH(&matTemp,&orig,&(orig + dir),&vSide);
				fTempHeight = g_pScene->m_pObjectRender->CheckCollMesh(matTemp,orig).fDist;
				if(m_vShadowPos3.y < orig.y - fTempHeight)
					m_vShadowPos3.y = orig.y - fTempHeight;
				else if(IsTileMapRenderEnable(g_pShuttleChild->m_myShuttleInfo.MapChannelIndex.MapIndex) == FALSE)
					m_bShadowIsRender = FALSE;
			}
		}
		else if(g_pGround->IntersectTriangle(orig,dir,g_pGround->m_pTileVertexArray[i*(g_pGround->m_projectInfo.sYSize+1)+j+1].pos,
			g_pGround->m_pTileVertexArray[(i+1)*(g_pGround->m_projectInfo.sYSize+1)+(j)].pos,
			g_pGround->m_pTileVertexArray[(i+1)*(g_pGround->m_projectInfo.sYSize+1)+j+1].pos,
			&fDist))//, &fBary1, &fBary2 ))
		{
			m_vShadowPos3 = orig + dir*fDist;
			if(g_pShuttleChild->CheckIsWater(orig))
			{
				if(m_vShadowPos3.y < g_pGround->m_projectInfo.fWaterHeight)
					m_vShadowPos3.y = g_pGround->m_projectInfo.fWaterHeight;
			}
			vTempShadowPos[2] = m_vShadowPos3;
			float fTempHeight = DEFAULT_COLLISION_DISTANCE;// = 100.0f;
			if(bOnObject)
			{
				D3DXMatrixLookAtLH(&matTemp,&orig,&(orig + dir),&vSide);
				fTempHeight = g_pScene->m_pObjectRender->CheckCollMesh(matTemp,orig).fDist;
				if(m_vShadowPos3.y < orig.y - fTempHeight)
					m_vShadowPos3.y = orig.y - fTempHeight;
				else if(IsTileMapRenderEnable(g_pShuttleChild->m_myShuttleInfo.MapChannelIndex.MapIndex) == FALSE)
					m_bShadowIsRender = FALSE;
			}
		}
	}
	i = (int)(m_vShadowPos4.x/TILE_SIZE);
	j = (int)(m_vShadowPos4.z/TILE_SIZE);
	orig = m_vShadowPos4;
	dir = D3DXVECTOR3(0,-1,0);
	if(i >= 0 && i < g_pGround->m_projectInfo.sXSize && j >= 0 && j < g_pGround->m_projectInfo.sYSize)
	{
		if(g_pGround->IntersectTriangle(orig,dir,g_pGround->m_pTileVertexArray[i*(g_pGround->m_projectInfo.sYSize+1)+j].pos,
			g_pGround->m_pTileVertexArray[i*(g_pGround->m_projectInfo.sYSize+1)+(j+1)].pos,
			g_pGround->m_pTileVertexArray[(i+1)*(g_pGround->m_projectInfo.sYSize+1)+(j)].pos,
			&fDist))//, &fBary1, &fBary2 ))
		{
			m_vShadowPos4 = orig + dir*fDist;
			if(g_pShuttleChild->CheckIsWater(orig))
			{
				if(m_vShadowPos4.y < g_pGround->m_projectInfo.fWaterHeight)
					m_vShadowPos4.y = g_pGround->m_projectInfo.fWaterHeight;
			}
			vTempShadowPos[3] = m_vShadowPos4;
			float fTempHeight = DEFAULT_COLLISION_DISTANCE;// = 100.0f;
			if(bOnObject)
			{
				D3DXMatrixLookAtLH(&matTemp,&orig,&(orig + dir),&vSide);
				fTempHeight = g_pScene->m_pObjectRender->CheckCollMesh(matTemp,orig).fDist;
				if(m_vShadowPos4.y < orig.y - fTempHeight)
					m_vShadowPos4.y = orig.y - fTempHeight;
				else if(IsTileMapRenderEnable(g_pShuttleChild->m_myShuttleInfo.MapChannelIndex.MapIndex) == FALSE)
					m_bShadowIsRender = FALSE;
			}
		}
		else if(g_pGround->IntersectTriangle(orig,dir,g_pGround->m_pTileVertexArray[i*(g_pGround->m_projectInfo.sYSize+1)+j+1].pos,
			g_pGround->m_pTileVertexArray[(i+1)*(g_pGround->m_projectInfo.sYSize+1)+(j)].pos,
			g_pGround->m_pTileVertexArray[(i+1)*(g_pGround->m_projectInfo.sYSize+1)+j+1].pos,
			&fDist))//, &fBary1, &fBary2 ))
		{
			m_vShadowPos4 = orig + dir*fDist;
			if(g_pShuttleChild->CheckIsWater(orig))
			{
				if(m_vShadowPos4.y < g_pGround->m_projectInfo.fWaterHeight)
					m_vShadowPos4.y = g_pGround->m_projectInfo.fWaterHeight;
			}
			vTempShadowPos[3] = m_vShadowPos4;
			float fTempHeight = DEFAULT_COLLISION_DISTANCE;// = 100.0f;
			if(bOnObject)
			{
				D3DXMatrixLookAtLH(&matTemp,&orig,&(orig + dir),&vSide);
				fTempHeight = g_pScene->m_pObjectRender->CheckCollMesh(matTemp,orig).fDist;
				if(m_vShadowPos4.y < orig.y - fTempHeight)
					m_vShadowPos4.y = orig.y - fTempHeight;
				else if(IsTileMapRenderEnable(g_pShuttleChild->m_myShuttleInfo.MapChannelIndex.MapIndex) == FALSE)
					m_bShadowIsRender = FALSE;
			}
		}
	}
	if(bOnObject && g_pScene->m_pObjectRender &&
		(D3DXVec3Length(&(m_vShadowPos4-m_vShadowPos2)) > m_fObjectSize*6 ||
		D3DXVec3Length(&(m_vShadowPos1-m_vShadowPos3)) > m_fObjectSize*6))
	{// �׸��ڰ� ������Ʈ�� ���� �þ����� ������ ���� �������� �׸��� ��ġ�� �����Ѵ�.
		m_vShadowPos1 = vTempShadowPos[0];
		m_vShadowPos2 = vTempShadowPos[1];
		m_vShadowPos3 = vTempShadowPos[2];
		m_vShadowPos4 = vTempShadowPos[3];
	}
	SPRITEVERTEX* pV;
	m_pVBShadow->Lock( 0, 0, (void**)&pV, 0 );
	pV[0].p = m_vShadowPos4; 
	pV[1].p = m_vShadowPos1; 
	pV[2].p = m_vShadowPos3; 
	pV[3].p = m_vShadowPos2;
	m_pVBShadow->Unlock();
}

void CEnemyData::InitItemPoint()
{
	FLOG( "CEnemyData::InitItemPoint()" );
	//DBGOUT("CEnemyData::InitItemPoint()\n");
	DeleteItemPoint();
 	ITEM * pItem = NULL;
	
	// 2006-07-21 by ispark, ĳ���Ϳ� ��� ����Ʈ �ʱ�ȭ
	/*--------------------------------------------------------------------------*/
	// ��� ����Ʈ
	if(m_bEnemyCharacter == FALSE)
	{
		pItem = g_pDatabase->GetServerItemInfo(m_infoCharacter.CharacterRenderInfo.RI_ProwOut);


		// 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����
		// ���� �������� �߰������� ���´�
		ITEM* pShapeItem	= g_pDatabase->GetServerItemInfo( m_infoCharacter.CharacterRenderInfo.RI_ProwOut_ShapeItemNum );
		// end 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����

		memset(&m_PrimaryAttack, 0x00, sizeof(ATTACK_DATA));
				
		// 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����
		//CreatePrimaryWeaponItem(pItem);
		CreatePrimaryWeaponItem( pItem, pShapeItem );
		// end 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����

		if(pItem)
		{
			m_PrimaryAttack.nMultiNumCount = GetMultiNum(pItem, &m_paramFactor);
		}
		pItem = g_pDatabase->GetServerItemInfo(m_infoCharacter.CharacterRenderInfo.RI_WingOut);


		// 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����
		// ���� �������� �߰������� ���´�
		pShapeItem	= g_pDatabase->GetServerItemInfo( m_infoCharacter.CharacterRenderInfo.RI_WingOut_ShapeItemNum );
		// end 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����


		memset(&m_SecondaryAttack, 0x00, sizeof(ATTACK_DATA));

		// 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����
		//CreateSecondaryWeaponItem(pItem);
		CreateSecondaryWeaponItem( pItem, pShapeItem );
		// end 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����

		if(pItem)
		{
			m_SecondaryAttack.nMultiNumCount = GetMultiNum(pItem, &m_paramFactor);
		}
		if(m_infoCharacter.CharacterRenderInfo.RI_Rear)
		{	
			// 2005-08-23 by ispark
			pItem = g_pDatabase->GetServerItemInfo(m_infoCharacter.CharacterRenderInfo.RI_Rear);
			if(pItem)
			{
	//			CreateWearItem( WEAR_ITEM_KIND_ENGINE, m_infoCharacter.CharacterRenderInfo.RI_Rear );
				CreateWearItem( WEAR_ITEM_KIND_ENGINE, pItem->SourceIndex );
			}
		}
		if(m_infoCharacter.CharacterRenderInfo.RI_Prow)
		{
			// 2005-08-23 by ispark


			// 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����
			//pItem = g_pDatabase->GetServerItemInfo(m_infoCharacter.CharacterRenderInfo.RI_Prow);

			// ���������۹�ȣ�� ���ٸ� ���� ������ ��ȣ�� ����Ѵ�
			int nItemNum = 0;
			if( m_infoCharacter.CharacterRenderInfo.RI_Prow_ShapeItemNum )
				nItemNum = m_infoCharacter.CharacterRenderInfo.RI_Prow_ShapeItemNum;
			else
				nItemNum = m_infoCharacter.CharacterRenderInfo.RI_Prow;

			pItem = g_pDatabase->GetServerItemInfo( nItemNum );

			// end 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����


			if(pItem)
			{
	//			CreateWearItem( WEAR_ITEM_KIND_PROW, EFFECT_NUMBER_WEAR_RADAR(m_infoCharacter.CharacterRenderInfo.RI_Prow) );
				CreateWearItem( WEAR_ITEM_KIND_PROW, EFFECT_NUMBER_WEAR_RADAR(pItem->SourceIndex) );
			}
		}
		if(m_infoCharacter.CharacterRenderInfo.RI_Center)
		{
			// 2005-07-20 by ispark
			// ��ü�� ���õ� ���̹Ƿ� FALSE
			// 2005-11-22 by ispark


			// 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����
			//pItem = g_pDatabase->GetServerItemInfo(m_infoCharacter.CharacterRenderInfo.RI_Center);

			// ���������۹�ȣ�� ���ٸ� ���� ������ ��ȣ�� ����Ѵ�
			int nItemNum = 0;
			if( m_infoCharacter.CharacterRenderInfo.RI_Center_ShapeItemNum )
				nItemNum = m_infoCharacter.CharacterRenderInfo.RI_Center_ShapeItemNum;
			else
				nItemNum = m_infoCharacter.CharacterRenderInfo.RI_Center;

			pItem = g_pDatabase->GetServerItemInfo( nItemNum );
			// end 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����
			// 2010. 03. 18 by jskim ���ͺ��� ī��
			BOOL bMonTras = FALSE;

			if(m_MonsterTransformer)
			{
				ChangeUnitCharacterInfo(nItemNum, m_infoCharacter.CharacterInfo.UnitKind, m_infoCharacter.CharacterInfo.BodyCondition, FALSE);
				SetMonsterTransPrimarySidePos(m_PrimaryAttack.vSidePos);
				SetMonsterTransSecondarySidePos(m_SecondaryAttack.vSidePos);
			}

			if(m_MonsterTransformer)
			{
				bMonTras = TRUE;
				MEX_MONSTER_INFO * pTempIn = g_pGameMain->CheckMonsterInfo( m_MonsterTransformer );
				if(pTempIn)
					nItemNum = pTempIn->SourceIndex;
			}
			else
			{
				if(pItem)
					nItemNum = pItem->SourceIndex;
			}
			//end 2010. 03. 18 by jskim ���ͺ��� ī��

#ifdef _RAT_FFA
			if (MAP_INFLUENCE_PVP_ALL == g_pD3dApp->GetMyShuttleMapInfo()->MapInfluenceType)
				pItem = NULL;
#endif

			if(pItem)
			{
				// 2010. 03. 18 by jskim ���ͺ��� ī��
				ChangeUnitCharacterInfo(nItemNum, m_infoCharacter.CharacterInfo.UnitKind, m_infoCharacter.CharacterInfo.BodyCondition, FALSE , bMonTras);
				//end 2010. 03. 18 by jskim ���ͺ��� ī��
			}
			else
			{
				// ����Ʈ
 				ChangeUnitCharacterInfo(0, 
 					m_infoCharacter.CharacterInfo.UnitKind, m_infoCharacter.CharacterInfo.BodyCondition, FALSE);
			}

			if(m_pCharacterInfo)
			{
				m_pCharacterInfo->SetShuttleChildEffect(FALSE);
			}
		}	
	}
	/*--------------------------------------------------------------------------*/
	// ĳ���� ����Ʈ
	else if(m_bEnemyCharacter == TRUE)
	{
		// 2012-06-14 by isshin ���۹̸����� - ���������� ����Ʈ���� ��� ����
		ITEM* pShapeItem = NULL;
		if(m_infoCharacter.CharacterRenderInfo.RI_ProwOut)
		{
			pItem = g_pDatabase->GetServerItemInfo(m_infoCharacter.CharacterRenderInfo.RI_ProwOut);
			pShapeItem	= g_pDatabase->GetServerItemInfo( m_infoCharacter.CharacterRenderInfo.RI_ProwOut_ShapeItemNum );
			memset(&m_PrimaryAttack, 0x00, sizeof(ATTACK_DATA));
			CreatePrimaryWeaponItem( pItem, pShapeItem );
		}		
		
		if(m_infoCharacter.CharacterRenderInfo.RI_WingOut)
		{
			pItem = g_pDatabase->GetServerItemInfo(m_infoCharacter.CharacterRenderInfo.RI_WingOut);
			pShapeItem	= g_pDatabase->GetServerItemInfo( m_infoCharacter.CharacterRenderInfo.RI_WingOut_ShapeItemNum );
			memset(&m_SecondaryAttack, 0x00, sizeof(ATTACK_DATA));
			CreateSecondaryWeaponItem( pItem, pShapeItem );
		}		
		// end 2012-06-14 by isshin ���۹̸����� - ���������� ����Ʈ���� ��� ����
	}

	/*--------------------------------------------------------------------------*/
	// ��ü ����Ʈ
	// 2006-07-21 by ispark, ����Ʈ ĳ�� ������
	if(m_infoCharacter.CharacterRenderInfo.RI_WingIn)
	{
		// 2008-08-19 by bhsohn ���� ��ũ �ý��� �߰�
		//pItem = g_pDatabase->GetServerItemInfo( m_infoCharacter.CharacterRenderInfo.RI_WingIn );
		int nTmpItemNum = m_infoCharacter.CharacterRenderInfo.RI_WingIn ;

		// 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����
		// ���������۹�ȣ�� �ִٸ� ���������� ��ȣ�� ���
		if( m_infoCharacter.CharacterRenderInfo.RI_WingIn_ShapeItemNum )
			nTmpItemNum	= m_infoCharacter.CharacterRenderInfo.RI_WingIn_ShapeItemNum;
		// end 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����


		int nObjectId = g_pStoreData->GetInfluenceMarkShow(m_infoCharacter.CharacterInfo.InfluenceType);		
		if(nObjectId)
		{
			nTmpItemNum = nObjectId;
		}	
		pItem = g_pDatabase->GetServerItemInfo( nTmpItemNum );
		// end 2008-08-19 by bhsohn ���� ��ũ �ý��� �߰�
		if(pItem)
		{
			CreateWearItem( WEAR_ITEM_KIND_WINGIN, pItem->SourceIndex, m_bEnemyCharacter );
		}
	}
	
	//if(m_infoCharacter.CharacterRenderInfo.RI_Attachment)
	if ( m_infoCharacter.CharacterRenderInfo.RI_AccessoryUnLimited )
	{
		// 2005-08-23 by ispark
		pItem = g_pDatabase->GetServerItemInfo(m_infoCharacter.CharacterRenderInfo.RI_AccessoryUnLimited);
		if(pItem)
		{
			CreateWearItem( WEAR_ITEM_KIND_ACCESSORY_UNLIMITED, pItem->SourceIndex, m_bEnemyCharacter );
		}
	}

	//if(m_infoCharacter.CharacterRenderInfo.RI_Pet)
	if(m_infoCharacter.CharacterRenderInfo.RI_AccessoryTimeLimit)
	{
		// 2005-08-23 by ispark
		pItem = g_pDatabase->GetServerItemInfo(m_infoCharacter.CharacterRenderInfo.RI_AccessoryTimeLimit);
		if(pItem)
		{
			CreateWearItem( WEAR_ITEM_KIND_ACCESSORY_TIME_LIMIT, pItem->SourceIndex, m_bEnemyCharacter );
		}
	}

	// 2010-06-15 by shcho&hslee ��ý���
	if ( m_infoCharacter.CharacterRenderInfo.RI_Pet )
	{
		// 2013-05-16 by bhsohn �극���κж����� �� �Ⱥ��̴� ���� ó��
//		pItem = g_pDatabase->GetServerItemInfo( m_infoCharacter.CharacterRenderInfo.RI_Pet );
		INT nPetItemNum = m_infoCharacter.CharacterRenderInfo.RI_Pet;
		if(m_infoCharacter.CharacterRenderInfo.RI_Pet_ShapeItemNum > 0)
		{
			nPetItemNum = m_infoCharacter.CharacterRenderInfo.RI_Pet_ShapeItemNum;
		}
		pItem = g_pDatabase->GetServerItemInfo( nPetItemNum );
		// END 2013-05-16 by bhsohn �극���κж����� �� �Ⱥ��̴� ���� ó��
		
		if ( pItem )
		{	// ���� SourceIndex�� 2���̱� ������  'RI_Pet_ShapeItemNum'�� �� ���������� Ȱ���Ѵ�.
			// 2013-05-16 by bhsohn �극���κж����� �� �Ⱥ��̴� ���� ó��
//			tPET_LEVEL_DATA *psPetLvData = g_pDatabase->GetPtr_PetLevelData( pItem->LinkItem , m_infoCharacter.CharacterRenderInfo.RI_Pet_ShapeItemNum );
			tPET_LEVEL_DATA *psPetLvData = g_pDatabase->GetPtr_PetLevelData( pItem->LinkItem , 1); // ��� �극�� ������ 1�� �ε�
			// END 2013-05-16 by bhsohn �극���κж����� �� �Ⱥ��̴� ���� ó��

			tPET_BASE_ALL_DATA *psPetAllData = g_pDatabase->GetPtr_PetAllDataByIndex( pItem->LinkItem);	   //2011-10-06 by jhahn ��Ʈ�� ������ �ý���
			
			INT SourceIndex = 0;

			if ( psPetLvData )
			{
				if ( m_bEnemyCharacter )
					SourceIndex = pItem->SourceIndex - 3100000;//psPetLvData->CitySourceIndex;	  //2011-10-06 by jhahn ��Ʈ�� ������ �ý���
				else 
					SourceIndex = pItem->SourceIndex - 3200000;//psPetLvData->FieldSourceIndex;	  //2011-10-06 by jhahn ��Ʈ�� ������ �ý���

				CreateWearItem ( WEAR_ITEM_KIND_PET , SourceIndex , m_bEnemyCharacter );
			}
		}
	}
	/*--------------------------------------------------------------------------*/

	m_bIsItemPointSet = TRUE;
	m_bIsRender = TRUE;
}


// 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����
//void CEnemyData::ChangeItemPoint(BYTE bPos,INT nItemNum, INT nColorNum)
// 2012-11-29 by bhsohn ��Ʈ�� ���� ���� ��Ʈ�� ����
//void	CEnemyData::ChangeItemPoint( BYTE bPos, INT nItemNum, INT nShapeItemNum, INT nEffectItemNum )
void	CEnemyData::ChangeItemPoint( BYTE bPos, INT nItemNum, INT nShapeItemNum, INT nEffectItemNum, int nPetLevel/*=-1*/)
// end 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����

{
	FLOG( "CEnemyData::ChangeItemPoint(BYTE bPos,INT nItemNum)" );
	D3DXVECTOR3 vTempPos = D3DXVECTOR3(0,0,0);
	switch(bPos)
	{
	case POS_PROWOUT:
		{// 1��
			DeleteWearItem( WEAR_ITEM_KIND_WEAPON_11 );
			DeleteWearItem( WEAR_ITEM_KIND_WEAPON_12 );

			// 2009. 07. 07 by ckPark �κ���� ��û����(�Ѹ�, ����ȭ��, ����, A�������)
			DeleteRobotAGearWeapon();
			// end 2009. 07. 07 by ckPark �κ���� ��û����(�Ѹ�, ����ȭ��, ����, A�������)

			ITEM * pItem = g_pDatabase->GetServerItemInfo(nItemNum);
			memset(&m_PrimaryAttack, 0x00, sizeof(ATTACK_DATA));


			// 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����
			//CreatePrimaryWeaponItem(pItem);

			ITEM*	pShapeItem	= g_pDatabase->GetServerItemInfo( nShapeItemNum );

#ifdef _RAT_FFA
			if (MAP_INFLUENCE_PVP_ALL == g_pD3dApp->GetMyShuttleMapInfo()->MapInfluenceType)
				pShapeItem = NULL;
#endif

			CreatePrimaryWeaponItem( pItem, pShapeItem );
			// end 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����


			if(pItem)
			{
				m_PrimaryAttack.nMultiNumCount = GetMultiNum(pItem, &m_paramFactor);
			}
		}
		break;
	case POS_WINGOUT:
		{// 2��
			DeleteWearItem( WEAR_ITEM_KIND_WEAPON_21 );
			DeleteWearItem( WEAR_ITEM_KIND_WEAPON_22 );
			ITEM * pItem = g_pDatabase->GetServerItemInfo(nItemNum);
			memset(&m_SecondaryAttack, 0x00, sizeof(ATTACK_DATA));


			// 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����
			//CreateSecondaryWeaponItem(pItem);

			ITEM*	pShapeItem	= g_pDatabase->GetServerItemInfo( nShapeItemNum );
			CreateSecondaryWeaponItem( pItem, pShapeItem );
			// end 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����

#ifdef _RAT_FFA
			if (MAP_INFLUENCE_PVP_ALL == g_pD3dApp->GetMyShuttleMapInfo()->MapInfluenceType)
				pShapeItem = NULL;
#endif
			if(pItem)
			{
				m_SecondaryAttack.nMultiNumCount = GetMultiNum(pItem, &m_paramFactor);
			}
		}
		break;
	case POS_REAR:
		{// ����
			DeleteWearItem( WEAR_ITEM_KIND_ENGINE );
			// 2005-11-14 by ispark
				ITEM * pItem = g_pDatabase->GetServerItemInfo(nItemNum);
			if(pItem)
			{
//				CreateWearItem( WEAR_ITEM_KIND_ENGINE, nItemNum );
				CreateWearItem( WEAR_ITEM_KIND_ENGINE, pItem->SourceIndex );
			}
		}
		break;
	case POS_PROW:
		{// ����
			DeleteWearItem( WEAR_ITEM_KIND_PROW );
			// 2005-11-14 by ispark
				ITEM * pItem = g_pDatabase->GetServerItemInfo(nItemNum);
			if(pItem)
			{
//				CreateWearItem( WEAR_ITEM_KIND_PROW, nItemNum );
				CreateWearItem( WEAR_ITEM_KIND_PROW, pItem->SourceIndex );
			}
		}
		break;
	case POS_CENTER:
		{// ���
			m_infoCharacter.CharacterRenderInfo.RI_Center = nItemNum;

			// 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����

			//m_infoCharacter.CharacterRenderInfo.RI_ArmorColorCode = nColorNum;
			m_infoCharacter.CharacterRenderInfo.RI_Center_ShapeItemNum = nShapeItemNum;

			if( nShapeItemNum )
				// 2010. 02. 17 by ckPark �׷��� ���ҽ� ���� �ý��� ���� ����
				//nItemNum = nItemNum;
				nItemNum = nShapeItemNum;
				// end 2010. 02. 17 by ckPark �׷��� ���ҽ� ���� �ý��� ���� ����

			ITEM * pItem = g_pDatabase->GetServerItemInfo(nItemNum);
	
			// 2010. 03. 18 by jskim ���ͺ��� ī��
			if(m_MonsterTransformer)
			{
				ChangeUnitCharacterInfo(nItemNum, m_infoCharacter.CharacterInfo.UnitKind, m_infoCharacter.CharacterInfo.BodyCondition, FALSE);
				SetMonsterTransPrimarySidePos(m_PrimaryAttack.vSidePos);
				SetMonsterTransSecondarySidePos(m_SecondaryAttack.vSidePos);
			}

			BOOL bMonTras = FALSE;
			if(m_MonsterTransformer)
			{
				bMonTras = TRUE;
				MEX_MONSTER_INFO * pTempIn = g_pGameMain->CheckMonsterInfo( m_MonsterTransformer );
				if(pTempIn)
					nItemNum = pTempIn->SourceIndex;
			}
			else
			{
				if(pItem)
					nItemNum = pItem->SourceIndex;
			}

#ifdef _RAT_FFA
			if (MAP_INFLUENCE_PVP_ALL == g_pD3dApp->GetMyShuttleMapInfo()->MapInfluenceType)
				pItem = NULL;
#endif

			//end 2010. 03. 18 by jskim ���ͺ��� ī��
			if(pItem)
			{
				// 2010. 03. 18 by jskim ���ͺ��� ī��
				//ChangeUnitCharacterInfo(pItem->SourceIndex, m_infoCharacter.CharacterInfo.UnitKind, m_infoCharacter.CharacterInfo.BodyCondition, FALSE);
				ChangeUnitCharacterInfo(nItemNum, m_infoCharacter.CharacterInfo.UnitKind, m_infoCharacter.CharacterInfo.BodyCondition, FALSE, bMonTras);
				//end 2010. 03. 18 by jskim ���ͺ��� ī��
				if(m_pCharacterInfo)
				{
					m_pCharacterInfo->SetShuttleChildEffect(FALSE);
				}

				// 2009. 07. 07 by ckPark �κ���� ��û����(�Ѹ�, ����ȭ��, ����, A�������)
				// �ϴ� ������� �� �����
				// 2014-08-01 by ymjoo A��� �κ��Ƹ� �⺻���� ���� �ȵǴ� ���� ����
				//ShowWeapon( FALSE );
				ShowWeapon(0, FALSE);
				// END 2014-08-01 by ymjoo A��� �κ��Ƹ� �⺻���� ���� �ȵǴ� ���� ����
				DeleteRobotAGearWeapon();
				if( !IsRobotArmor() )
				{
					// 2010. 03. 18 by jskim ���ͺ��� ī��
					// �κ� �ƸӰ� �ƴҰ�� ���� ������� �߰�
					//ShowWeapon( FALSE );
					//ShowWeapon( TRUE );
					// 2014-08-01 by ymjoo A��� �κ��Ƹ� �⺻���� ���� �ȵǴ� ���� ����
					if(IS_DT(m_infoCharacter.CharacterInfo.UnitKind))
					{
						ITEM* pItem = g_pDatabase->GetServerItemInfo(m_infoCharacter.CharacterRenderInfo.RI_ProwOut);
						ITEM* pShapeItem = g_pDatabase->GetServerItemInfo(m_infoCharacter.CharacterRenderInfo.RI_ProwOut_ShapeItemNum);
						CreatePrimaryWeaponItem(pItem, pShapeItem);
					}
					if(m_MonsterTransformer)
						//ShowWeapon( FALSE );
						ShowWeapon(0, FALSE);
					else
						//ShowWeapon( TRUE );
						ShowWeapon(0, TRUE);
					// END 2014-08-01 by ymjoo A��� �κ��Ƹ� �⺻���� ���� �ȵǴ� ���� ����
					//end 2010. 03. 18 by jskim ���ͺ��� ī��
					
				}
				else
				{
					// �κ� �Ƹ��� ���
					int		type = 0;
					ITEM*	pPrimaryWeapon = NULL;

					type = GetUnitTypeDecimal(m_infoCharacter.CharacterInfo.UnitKind);
					pPrimaryWeapon = g_pDatabase->GetServerItemInfo( m_infoCharacter.CharacterRenderInfo.RI_ProwOut );

					// A����̰�, �ֹ��⸦ �����Ͽ��� ��� A���� �ӽ� ���� ����Ʈ �߰�
					if( type == 2 && pPrimaryWeapon )
					{
						// 2014-08-01 by ymjoo A��� �κ��Ƹ� �⺻���� ���� �ȵǴ� ���� ����
// 						ITEM* pAGearWeapon = g_pDatabase->GetServerItemInfo( A_GEAR_ROBOT_PRIMARY_WEAPON_ITEM_NUM );
// 						if( pAGearWeapon )
//							CreateRobotAGearWeapon( pAGearWeapon, type );
						ITEM* pItem = g_pDatabase->GetServerItemInfo(m_infoCharacter.CharacterRenderInfo.RI_ProwOut);
						ITEM* pShapeItem = g_pDatabase->GetServerItemInfo(m_infoCharacter.CharacterRenderInfo.RI_ProwOut_ShapeItemNum);
						CreatePrimaryWeaponItem(pItem, pShapeItem);
						ShowWeapon(1, TRUE);
						// END 2014-08-01 by ymjoo A��� �κ��Ƹ� �⺻���� ���� �ȵǴ� ���� ����
					}
				}
				// end 2009. 07. 07 by ckPark �κ���� ��û����(�Ѹ�, ����ȭ��, ����, A�������)
			}
			else
			{
				// ����Ʈ
				ChangeUnitCharacterInfo(0, 
					m_infoCharacter.CharacterInfo.UnitKind, m_infoCharacter.CharacterInfo.BodyCondition, FALSE);
			}
		}
		break;
		// 2006-07-25 by ispark, POS_ATTACHMENT -> POS_WINGIN���� ����
	case POS_WINGIN:
		{
			DeleteWearItem( WEAR_ITEM_KIND_WINGIN );

#ifdef _RAT_FFA
			if (MAP_INFLUENCE_PVP_ALL == g_pD3dApp->GetMyShuttleMapInfo()->MapInfluenceType)
				break;
#endif
			// 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����
			if( nShapeItemNum )
				nItemNum = nShapeItemNum;
			// end 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����


			// 2008-08-19 by bhsohn ���� ��ũ �ý��� �߰�					
			int nObjectId = g_pStoreData->GetInfluenceMarkShow(m_infoCharacter.CharacterInfo.InfluenceType);		
			if(nObjectId)
			{
				nItemNum = nObjectId;
			}				
			// end 2008-08-19 by bhsohn ���� ��ũ �ý��� �߰�

			// 2005-11-14 by ispark
				ITEM * pItem = g_pDatabase->GetServerItemInfo(nItemNum);
			if(pItem)
			{
				CreateWearItem( WEAR_ITEM_KIND_WINGIN, pItem->SourceIndex, m_bEnemyCharacter );
			}
		}
		break;

	//case POS_ATTACHMENT:
	case POS_ACCESSORY_UNLIMITED :
		{// �����̳� (������)
			DeleteWearItem( WEAR_ITEM_KIND_ACCESSORY_UNLIMITED );
			// 2005-11-14 by ispark
				ITEM * pItem = g_pDatabase->GetServerItemInfo(nItemNum);
			if(pItem)
			{
				CreateWearItem( WEAR_ITEM_KIND_ACCESSORY_UNLIMITED, pItem->SourceIndex, m_bEnemyCharacter );
			}
		}
		break;

	//case POS_PET:
	case POS_ACCESSORY_TIME_LIMIT :
		{
			DeleteWearItem( WEAR_ITEM_KIND_ACCESSORY_TIME_LIMIT );
			// 2005-11-14 by ispark
				ITEM * pItem = g_pDatabase->GetServerItemInfo(nItemNum);
			if(pItem)
			{
				CreateWearItem( WEAR_ITEM_KIND_ACCESSORY_TIME_LIMIT, pItem->SourceIndex, m_bEnemyCharacter );
			}
		}
		break;

	// 2010-06-15 by shcho&hslee ��ý��� - �� ����ǰ �ε� �߰�.
	case POS_PET :
		{
			// 2012-11-29 by bhsohn ��Ʈ�� ���� ���� ��Ʈ�� ����
#ifdef	SC_PARTNER_SHAPE_CHANGE_HSKIM
			if( nShapeItemNum > 0 )
			{
				nItemNum = nShapeItemNum;
			}
			if(nPetLevel <=0)
			{
				nPetLevel = 1;
			}
#endif
			// END 2012-11-29 by bhsohn ��Ʈ�� ���� ���� ��Ʈ�� ����

			DeleteWearItem ( WEAR_ITEM_KIND_PET );

			ITEM *pItem = g_pDatabase->GetServerItemInfo ( nItemNum );
			

			if ( pItem )
			{
				// 2012-11-29 by bhsohn ��Ʈ�� ���� ���� ��Ʈ�� ����
//				tPET_LEVEL_DATA *psPetLvData = g_pDatabase->GetPtr_PetLevelData ( pItem->LinkItem , nShapeItemNum );
#ifdef	SC_PARTNER_SHAPE_CHANGE_HSKIM
				tPET_LEVEL_DATA *psPetLvData = g_pDatabase->GetPtr_PetLevelData ( pItem->LinkItem , nPetLevel);
#else
				tPET_LEVEL_DATA *psPetLvData = g_pDatabase->GetPtr_PetLevelData ( pItem->LinkItem , nShapeItemNum );
#endif				
				// END 2012-11-29 by bhsohn ��Ʈ�� ���� ���� ��Ʈ�� ����
				tPET_BASE_ALL_DATA *psPetAllData = g_pDatabase->GetPtr_PetAllDataByIndex( pItem->LinkItem); //2011-10-06 by jhahn ��Ʈ�� ������ �ý���

				if ( psPetLvData )
				{
					CreateWearItem ( WEAR_ITEM_KIND_PET , m_bEnemyCharacter == TRUE ? pItem->SourceIndex - 3100000: pItem->SourceIndex - 3200000, m_bEnemyCharacter );	//2011-10-06 by jhahn ��Ʈ�� ������ �ý���
				}
			}
		}
		break;
	}
}
/*
///////////////////////////////////////////////////////////////////////////////
/// \fn			void CEnemyData::CheckPrimaryAttack(BOOL bReset, ITEM* pPrimary)
/// \brief		Primary weapon�� action�� �����Ѵ�.
/// \author		dhkwon
/// \date		2004-03-21 ~ 2004-03-21
/// \warning	CUnitData�� PrimaryAttackAction�Լ��� �������̵�(virtual function)�Ͽ� �籸��
///				((CUnitData*)p)->PrimaryAttackAction�� �����ϴ��� �ڽ��� ���� �����
///				�� �κ��� CEnemyData,CShuttleChild���� �ణ�� ���̰� �־� ���� �����Ǿ���.
///				1�� ������ ��ȣ�� ���� ������ ��ȣ���� ���� : EFFECT_WEAR_WEAPON_1
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CEnemyData::CheckPrimaryAttack(BOOL bReset, ITEM* pPrimary)
{
	FLOG( "CEnemyData::CheckPrimaryAttack(BOOL bReset)" );


	if( m_pPrimaryAttackTarget && 
		(!m_pPrimaryAttackTarget->m_bUsing || m_pPrimaryAttackTarget->m_dwState != _NORMAL))
		m_pPrimaryAttackTarget = NULL;	// ����Ÿ�� ������ ������ üũ�Ͽ� Ÿ�������͸� NULL����
	// ����Ű�� ������ ���������� ���� �Ѿ��� ���ư��� �ȴ�
	ITEM * info1 = NULL;
	ITEM * info2 = NULL;

	if(m_pWeapon1_1)
	{
		info1 = g_pDatabase->GetServerItemInfo(m_pWeapon1_1->m_nType - EFFECT_WEAR_WEAPON_1);
	}
	
	if(m_pWeapon1_2)
	{
		info2 = g_pDatabase->GetServerItemInfo(m_pWeapon1_2->m_nType - EFFECT_WEAR_WEAPON_1);
	}

	if(!info1 && !info2)
		return;
	
	if(!info1)
		info1 = info2;
	
	if(info1)
	{
//		if(IS_CLIENT_SET_AUTOMATIC_TIMER(info1->OrbitType))
//		{
//			if(m_PrimaryAttack.fCheckAutoMaticTimer > 0.0f)
				m_PrimaryAttack.fCheckAutoMaticTimer -= g_pD3dApp->GetElapsedTime();
//		}
//		if(m_PrimaryAttack.fCheckAttackTime > 0.0f)
			m_PrimaryAttack.fCheckAttackTime -= g_pD3dApp->GetElapsedTime();
		CUnitData::CheckPrimaryAttack( bReset, info1 );
	}
}
*/
// 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����
//void CEnemyData::CheckAttack(ATTACK_DATA &attackData, BOOL bReset, ITEM* pWeaponITEM)
void CEnemyData::CheckAttack( ATTACK_DATA &attackData, BOOL bReset, ITEM* pWeaponITEM /* = NULL */, ITEM* pEffectItem /* = NULL */ )
// end 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����
{
	FLOG( "CEnemyData::CheckPrimaryAttack(BOOL bReset)" );
	pWeaponITEM = g_pDatabase->GetServerItemInfo(attackData.AttackData.ItemNum);
	if(pWeaponITEM)
	{
		
		// 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����
		//CUnitData::CheckAttack( attackData, bReset, pWeaponITEM );

		// �Ѿ� ������ ����Ʈ ��ȣ�� ���� �Ѱ��ش�
		ITEM* pEffectItem = NULL;
		if( IS_PRIMARY_ATT_TYPE( attackData.AttackData.AttackType ) )
		{
			if( m_infoCharacter.CharacterRenderInfo.RI_ProwOut_EffectItemNum )
				pEffectItem = g_pDatabase->GetServerItemInfo( m_infoCharacter.CharacterRenderInfo.RI_ProwOut_EffectItemNum );
		}
		else if( IS_SECONDARY_ATT_TYPE( attackData.AttackData.AttackType ) )
		{
			if( m_infoCharacter.CharacterRenderInfo.RI_WingOut_EffectItemNum )
				pEffectItem = g_pDatabase->GetServerItemInfo( m_infoCharacter.CharacterRenderInfo.RI_WingOut_EffectItemNum );
		}
		// 2010-06-15 by shcho&hslee ��ý��� - �� ���� ����
// 		if( ATT_TYPE_PET_GENERAL == attackData.AttackData.AttackType )
// 		{
// 			if( m_infoCharacter.CharacterRenderInfo.RI_ProwOut_EffectItemNum )
// 				pEffectItem = g_pDatabase->GetServerItemInfo( m_infoCharacter.CharacterRenderInfo.RI_ProwOut_EffectItemNum );
// 		}
		// end 2010-06-15 by shcho&hslee ��ý��� - �� ���� ����
		CUnitData::CheckAttack( attackData, bReset, pWeaponITEM, pEffectItem );

		// end 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����
	}

}

///////////////////////////////////////////////////////////////////////////////
/// \fn			CEnemyData::CreateSecondaryShieldDamage(D3DXVECTOR3 vCollPos)
/// \brief		���� �������� �������� ���� ��� ����Ʈ ����
/// \author		dhkwon
/// \date		2004-05-18 ~ 2004-05-18
/// \warning	2�� ������ ��ȣ�� ���� ������ ��ȣ���� ���� : EFFECT_WEAR_WEAPON_2
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CEnemyData::CreateSecondaryShieldDamage(D3DXVECTOR3 vCollPos)
{
//	int nItemNum = m_pWeapon2_1->m_nType + EFFECT_WEAR_WEAPON_2;
//	ITEM *pItem = g_pDatabase->GetServerItemInfo(nItemNum);
//	if(!pItem || pItem->Kind != ITEMKIND_SHIELD)
//	{
//		nItemNum = m_pWeapon2_2->m_nType + EFFECT_WEAR_WEAPON_2;
//		pItem = g_pDatabase->GetServerItemInfo(m_pWeapon2_2->m_nType + EFFECT_WEAR_WEAPON_2);
//	}
//	if(pItem && pItem->Kind == ITEMKIND_SHIELD)
//	{
//		CWeaponShieldData* pShield = new CWeaponShieldData(this, nItemNum, vCollPos );
		CWeaponShieldData* pShield = new CWeaponShieldData(this, RC_EFF_SHIELD_HIT, vCollPos );
		g_pScene->m_pWeaponData->AddChild(pShield);
//	}
}

USHORT CEnemyData::GetShiftWeaponBodyconditionByUnitKind()
{
	if(IS_BT(m_infoCharacter.CharacterInfo.UnitKind))
		return UNIT_KIND_SHIFT_B_GEAR;
	if(IS_ST(m_infoCharacter.CharacterInfo.UnitKind))
		return UNIT_KIND_SHIFT_I_GEAR;
	if(IS_OT(m_infoCharacter.CharacterInfo.UnitKind))
		return UNIT_KIND_SHIFT_M_GEAR;
	if(IS_DT(m_infoCharacter.CharacterInfo.UnitKind))
		return UNIT_KIND_SHIFT_A_GEAR;
	return UNIT_KIND_SHIFT_DEFAULT;
}


void CEnemyData::MoveSkill()
{
	float fElapsedTime = g_pD3dApp->GetElapsedTime();
	m_fSkillMoveTime += fElapsedTime;
	D3DXMATRIX matTemp;
	D3DXVECTOR3 vSide,vVel,vUp;
	D3DXVECTOR3 vOldPos = m_vPos;
	D3DXVec3Cross(&vSide,&m_vUp,&m_vVel);

	if(m_bSkillMoveType == 0)
	{// ���ϰ����� 360�� ȸ��(Ÿ�� 0)
		D3DXMatrixRotationAxis( &matTemp, &vSide, -fElapsedTime);
		D3DXVec3TransformCoord( &m_vUp, &m_vUp, &matTemp );
		D3DXVec3TransformCoord( &m_vVel, &m_vVel, &matTemp );
	}
	else if(m_bSkillMoveType == 1)
	{// ���ϰ����� 360�� ȸ��(Ÿ�� 1)
		D3DXMatrixRotationAxis( &matTemp, &vSide, -m_fSkillMoveTime);
		D3DXVec3TransformCoord( &vVel, &m_vVel, &matTemp );
	}
	else if(m_bSkillMoveType == 2)
	{// ���ϰ����� 360�� ȸ��(Ÿ�� 2)
		D3DXMatrixRotationAxis( &matTemp, &vSide, -fElapsedTime);
		D3DXVec3TransformCoord( &m_vUp, &m_vUp, &matTemp );
		D3DXVec3TransformCoord( &m_vVel, &m_vVel, &matTemp );
	}
	else if(m_bSkillMoveType == 3)
	{// ���ϰ����� 360�� ȸ��(Ÿ�� 3)
		D3DXMatrixRotationAxis( &matTemp, &vSide, -m_fSkillMoveTime);
		D3DXVec3TransformCoord( &vVel, &m_vVel, &matTemp );
		vUp = m_vUp;
		D3DXMatrixRotationAxis( &matTemp, &m_vVel, -10.0f*m_fSkillMoveTime);
		D3DXVec3TransformCoord( &m_vUp, &m_vUp, &matTemp );
	}
	else if(m_bSkillMoveType == 4)
	{// ������ ����
		vUp = m_vUp;
		D3DXMatrixRotationAxis( &matTemp, &m_vVel, -10.0f*m_fSkillMoveTime);
		D3DXVec3TransformCoord( &m_vUp, &m_vUp, &matTemp );
	}
	else if(m_bSkillMoveType == 5)
	{//�� �̵�
	}
	else if(m_bSkillMoveType == 6)
	{//�� �̵�
	}
	else if(m_bSkillMoveType == 7)
	{// BT �� - ����(�� 360�� ��)
	}
	else if(m_bSkillMoveType == 8)
	{// BT �� - ����(�� 360�� ��)
	}
	else if(m_bSkillMoveType == 9)
	{// BT �� - ��������(����극��ũ �� ��뺸�� ���� ���̷� �ް����Ͽ� �ڷ� ���ν����Ͽ� ����� �Ĺ̸� ��� ��)
	}
	else if(m_bSkillMoveType == 10)
	{// BT �� - �ں��⵿(������ ���θ� ��� ���� ���ǵ带 0���� �Ͽ� ���ڸ��� ���ְ� �����)
	}

	float fCheckTime = 2.0f*3.14f;
	if(m_bSkillMoveType==4)
		fCheckTime = 3.14f/4.0f;
	else if(m_bSkillMoveType==5 || m_bSkillMoveType==6)
		fCheckTime = 3.14f/6.0f;
	if(m_fSkillMoveTime > fCheckTime)
	{
		m_fSkillMoveTime = 0.0f;
		m_vVel.y = 0.0f;
		D3DXVec3Normalize(&m_vVel,&m_vVel);
		D3DXVec3Cross(&m_vUp,&m_vVel,&vSide);
		m_bUseMoveSkill = FALSE;
	}
}

float CEnemyData::CheckOnObject()
{
	D3DXVECTOR3 vUp(0,1,0);
	D3DXVECTOR3 vVel(1,0,0);
	D3DXMATRIX mat;

	D3DXMatrixLookAtLH( &mat, &m_vPos, &(m_vPos-vUp), &vVel);
	return g_pScene->m_pObjectRender->CheckCollMesh(mat,m_vPos).fDist;			
}

void CEnemyData::SetItemParamFactor( MSG_FC_CHARACTER_GET_OTHER_PARAMFACTOR_OK* pMsg )
{
	m_paramFactor.Reset();
	char* p = ((char*)pMsg) + sizeof(MSG_FC_CHARACTER_GET_OTHER_PARAMFACTOR_OK);
	int i; for(i=0;i<pMsg->NumOfParamValues;i++)
	{
		SetParamFactor_DesParam( m_paramFactor, ((DES_PARAM_VALUE*)p)->DestParameter, ((DES_PARAM_VALUE*)p)->ParameterValue);
		p += sizeof(DES_PARAM_VALUE);
	}
	ITEM * pItem = g_pDatabase->GetServerItemInfo(m_infoCharacter.CharacterRenderInfo.RI_ProwOut);
	if(pItem)
	{
		m_PrimaryAttack.nMultiNumCount = GetMultiNum(pItem, &m_paramFactor);
	}
	pItem = g_pDatabase->GetServerItemInfo(m_infoCharacter.CharacterRenderInfo.RI_WingOut);
	if(pItem)
	{
		m_SecondaryAttack.nMultiNumCount = GetMultiNum(pItem, &m_paramFactor);
	}
//	switch(pMsg->ItemPosition)
//	{
//	case POS_PROWOUT:
//		{
//			m_paramFactor.Reset();
//			char* p = ((char*)pMsg) + sizeof(MSG_FC_CHARACTER_GET_OTHER_PARAMFACTOR_OK);
//			int i; for(i=0;i<pMsg->NumOfParamValues;i++)
//			{
//				SetParamFactor_DesParam( m_paramFactor, ((DES_PARAM_VALUE*)p)->DestParameter, ((DES_PARAM_VALUE*)p)->ParameterValue);
//				p += sizeof(DES_PARAM_VALUE);
//			}
//			ITEM * pItem = g_pDatabase->GetServerItemInfo(m_infoCharacter.CharacterRenderInfo.RI_ProwOut);
//			memset(&m_PrimaryAttack, 0x00, sizeof(ATTACK_DATA));
//			if(pItem)
//			{
//				m_PrimaryAttack.nMultiNumCount = GetMultiNum(pItem, &m_paramFactor);
//			}
//		}
//		break;
//	case POS_WINGOUT:
//		{
//			m_paramFactor.Reset();
//			char* p = ((char*)pMsg) + sizeof(MSG_FC_CHARACTER_GET_OTHER_PARAMFACTOR_OK);
//			int i; for(i=0;i<pMsg->NumOfParamValues;i++)
//			{
//				SetParamFactor_DesParam( m_paramFactor, ((DES_PARAM_VALUE*)p)->DestParameter, ((DES_PARAM_VALUE*)p)->ParameterValue);
//				p += sizeof(DES_PARAM_VALUE);
//			}
//			ITEM * pItem = g_pDatabase->GetServerItemInfo(m_infoCharacter.CharacterRenderInfo.RI_WingOut);
//			memset(&m_SecondaryAttack, 0x00, sizeof(ATTACK_DATA));
//			if(pItem)
//			{
//				m_SecondaryAttack.nMultiNumCount = GetMultiNum(pItem, &m_paramFactor);
//			}
//		}
//		break;
//	default:
//		{
//			DBGOUT("MSG_FC_CHARACTER_GET_OTHER_PARAMFACTOR_OK(pos:%d) ���� �ȵ�\n",pMsg->ItemPosition);
//		}
//		break;
//	}
}

// 2006-11-27 by ispark, �Ⱦ��� �Լ� �̹Ƿ� �ּ� ó��
//void CEnemyData::UseSkillFromServer(INT nSkillItemNumber, ClientIndex_t nTargetIndex)
//	{
//// 2004-10-28 by jschoi
//// Enemy�� ��ų�� ����ϸ� �ش� ����Ʈ�� �����ش�.
//
////	if( SKILL_KIND(nSkillItemNumber) == SKILL_KIND_CONTROL )
////	{
////	}
////	else 
////	{
//		CAppEffectData* pEff = new CAppEffectData(this,
//								SKILL_BASE_NUM(nSkillItemNumber),
//								D3DXVECTOR3(0,0,0));
//		if(pEff->m_bUsing == TRUE )
//		{
//			pEff = (CAppEffectData *)g_pD3dApp->m_pEffectList->AddChild(pEff);
//	}
//	else 
//	{
//			delete pEff;
//	}
////	}
//}


///////////////////////////////////////////////////////////////////////////////
/// \fn			RollingSystem()
/// \brief		�Ѹ� �ý���(Ű�� �˻��� �׿� �´� �ִϸ��̼� �ϵ��ڵ�)
///				ȸ������ ����
///				(��, 0�� �̵��� ���� �� ����.)
/// \author		ispark
/// \date		2005-07-05 ~ 2005-07-05
/// \warning	
///
/// \param		void
/// \return		float
///////////////////////////////////////////////////////////////////////////////
float CEnemyData::RollingSystem(float fElapsedTime)
{
	// AŰ ���� �Ѹ�
	if(m_bRollLeft)
	{
		m_fRollStartTime += fElapsedTime;
		if(m_fRollStartTime >= ROLLING_USE_TIME)					// �Ѹ� ���ӽð�
		{
			return 0.0f;
		}

		m_fRollAngle += 360 * fElapsedTime;

		if(D3DXToRadian(360) <= D3DXToRadian(m_fRollAngle))
		{
			m_bRollLeft = FALSE;
			m_bRollStart = FALSE;
			m_fRollStartTime = 0.0f;

			return 0.0f;
		}
		else
		{
			return D3DXToRadian(m_fRollAngle);
		}
	}
	
	// DŰ ���� �Ѹ�
	if(m_bRollRight)
	{
		m_fRollStartTime += fElapsedTime;

		if(m_fRollStartTime >= ROLLING_USE_TIME)					// �Ѹ� ���� �ð�
		{
			return 0.0f;
		}

		m_fRollAngle += 360 * fElapsedTime;

		if(D3DXToRadian(360) <= D3DXToRadian(m_fRollAngle))
		{
			m_bRollRight = FALSE;
			m_bRollStart = FALSE;
			m_fRollStartTime = 0.0f;
			
			return 0.0f;
		}
		else
		{
			return -D3DXToRadian(m_fRollAngle);
		}
	}

	return 0.0f;
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		ispark
/// \date		2005-07-07 ~ 2005-07-07
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CEnemyData::CheckRoll(MSG_FC_MOVE_ROLLING_OK *pMsg)
{
	m_bRollStart = TRUE;
	m_fRollStartTime = 0.0f;
	m_fRollAngle = 80.0f;
	m_vRollStart = A2DX(pMsg->PositionAVec3);

	if(pMsg->byLeftDirectionFlag)
		m_bRollLeft = TRUE;
	else
		m_bRollRight = TRUE;

	// 2009. 07. 07 by ckPark �κ���� ��û����(�Ѹ�, ����ȭ��, ����, A�������)
	// �κ� �Ƹ��ϰ��
	if( IsRobotArmor() )
	{
		// �ν��� �ִϸ��̼ǰ� �Ѹ� �ٵ������� �� ������, ���� �����Ѵ�
		TurnSingleBodyCondition( BODYCON_BOOSTER1_MASK, FALSE );
		TurnSingleBodyCondition( BODYCON_BOOSTER2_MASK, FALSE );
		TurnSingleBodyCondition( BODYCON_BOOSTER3_MASK, FALSE );
		TurnSingleBodyCondition( BODYCON_BOOSTER4_MASK, FALSE );
		TurnSingleBodyCondition( BODYCON_BOOSTER5_MASK, FALSE );
		TurnSingleBodyCondition( BODYCON_ROLLING_MASK, FALSE );
	}
	TurnSingleBodyCondition( BODYCON_ROLLING_MASK, TRUE );
	// end 2009. 07. 07 by ckPark �κ���� ��û����(�Ѹ�, ����ȭ��, ����, A�������)
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			CEnemyData::LoadEnemyCharacterInfo(char *strFileName)
/// \brief		�� ĳ���Ϳ��� �ʿ��� �κ�
/// \author		ispark
/// \date		2005-07-27 ~ 2005-07-27
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CEnemyData::LoadEnemyCharacterInfo(char *strFileName)
{
	if((m_pEnemyCharacterInfo))
	{
		(m_pEnemyCharacterInfo)->InvalidateDeviceObjects();
		(m_pEnemyCharacterInfo)->DeleteDeviceObjects();
		SAFE_DELETE(m_pEnemyCharacterInfo);
	}
	(m_pEnemyCharacterInfo) = new CCharacterInfo();
	if((m_pEnemyCharacterInfo)->Load(strFileName))
	{
		(m_pEnemyCharacterInfo)->InitDeviceObjects();
		(m_pEnemyCharacterInfo)->RestoreDeviceObjects();
	}
	else
	{
		SAFE_DELETE((m_pEnemyCharacterInfo));
		DBGOUT("WARNING!! [EFFECT ERROR] Can't Find Effect File : %s \n",strFileName);
	}	
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			CEnemyData::CheckShadowPos()
/// \brief		�� ĳ���� �׸���
/// \author		ispark
/// \date		2005-07-27 ~ 2005-07-27
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CEnemyData::CheckShadowPos()
{
	D3DXVECTOR3 vShadowPos[4];
	// ���⼭ ��ġ�� �׸��ڸ� �Ѹ� ����� ���Ѵ�. �������� �밢�� �������� �Ÿ��̴�.
	vShadowPos[0] = m_vPos + CHARACTER_SHADOW_SCALE * (m_vVel - m_vSideVel);
	vShadowPos[1] = m_vPos + CHARACTER_SHADOW_SCALE * (m_vVel + m_vSideVel);
	vShadowPos[2] = m_vPos - CHARACTER_SHADOW_SCALE * (m_vVel - m_vSideVel);
	vShadowPos[3] = m_vPos - CHARACTER_SHADOW_SCALE * (m_vVel + m_vSideVel);

	for(int i = 0 ; i < 4 ; i++)
	{
		vShadowPos[i].y += 7.087f;
		float fTempHeight = 0.0f;
		float fObjHeight = -DEFAULT_COLLISION_DISTANCE;

		D3DXMATRIX matTemp;
		D3DXVECTOR3 vSide(0, 0, 1), vUp(0, 1, 0);
		D3DXMatrixLookAtLH(&matTemp,&vShadowPos[i],&(vShadowPos[i] - vUp),&vSide);
		fTempHeight = g_pScene->m_pObjectRender->CheckCollMesh(matTemp,vShadowPos[i]).fDist - 7.087f;

		if(fTempHeight <= 1.0f && fTempHeight >= -1.0f)
		{
			vShadowPos[i].y += -fTempHeight;
		}
		else
		{
			if(fTempHeight > 0) 
			{
				vShadowPos[i].y += -fTempHeight;
			}
			else
			{
				float fRealObjectHeight = vShadowPos[i].y - fTempHeight;
				if( fRealObjectHeight > vShadowPos[i].y )
				{
					vShadowPos[i].y = fRealObjectHeight;
				}
			}
		}

		// �׸��ڴ� Z���۸� ����ϹǷ� �׸��� ���̸� 0.2f��ŭ �ø���.
		// �� ĳ���Ϳ� ��ġ�� ���󶧹��̴�. �׷��� �� ĳ���Ϳ� ��ĳ���Ͱ��� ��Ȳ�� �ʿ�
//		vShadowPos[i].y -= (7.087f - 0.1f);
		vShadowPos[i].y -= (7.087f);
	}

	SPRITEVERTEX* pV;
	m_pVBShadow->Lock( 0, 0, (void**)&pV,	0 );
	pV[0].p = vShadowPos[3]; 
	pV[1].p = vShadowPos[0]; 
	pV[2].p = vShadowPos[2]; 
	pV[3].p = vShadowPos[1];
	m_pVBShadow->Unlock();

	m_vShadowPos1 = vShadowPos[0];
	m_vShadowPos2 = vShadowPos[1];
	m_vShadowPos3 = vShadowPos[2];
	m_vShadowPos4 = vShadowPos[3];

}


///////////////////////////////////////////////////////////////////////////////
/// \fn			TickUnit(float fElapsedTime)
/// \brief		
/// \author		ispark
/// \date		2005-07-27 ~ 2005-07-27
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CEnemyData::TickUnit(float fElapsedTime)
{

	if( m_dwState == _INITIALIZING || m_infoCharacter.CharacterInfo.ClientIndex == INVALID_CLIENT_INDEX) 
		return; // initializing
	m_ptOldRegion = m_ptCurRegion;

//	static float fCheckItemInfoTime = 0.0f;
	if(m_fCheckItemInfoTime > 0.0f)
		m_fCheckItemInfoTime -= fElapsedTime;
	m_bIsUnderWater = FALSE;
	D3DXVECTOR3 vMovepos = D3DXVECTOR3(0,0,0);
//	if( m_dwState == _NORMAL || 
//		m_dwState == _EXPLODING || 
//		m_dwState == _FALLING || 
//		m_dwState == _TAKINGOFF)

	/// add by syjun 
	// FrameMove���� �ϰ������� ���־�� �Ұ���
	//������� �������� �غ��Ѵ�.
	// ������� ���Ѵ�.
	/*
	if(m_infoParty.bPartyType == _PARTYMASTER )
	{
		if( ���� ������� ��� )
		//���� ������ ��� �������� ��ġ�� ����
		else
		{
			//�������� ��ġ�� ���ؼ�
			//���� ��������� ��ġ�� ����
		}
	}
	else if( m_infoParty.bPartyType == _PARTYMEMBER)
	{
		if( ���� ������� ��� )
		//�� ������ ��ġ�� ���� �������� ����
		else

	}*/
	// 2005-08-29 by ispark
	// A��� �ϰ�� _LANDED�� ������ �����̴� ����̹Ƿ� �����̰� �Ѵ�.
	if(UNIT_STATE_MOVE(m_dwState) || IS_DT(m_infoCharacter.CharacterInfo.UnitKind) == TRUE)
	{
		if(m_fLifeTime > -8.0f)
			m_fLifeTime -= fElapsedTime;
		if(m_fLifeTime < -8.0f)
			m_fLifeTime = -8.0f;

		if(	m_fLifeTime > -8.0f && 
			m_fLifeTime < -3.0f && 
			!m_bRequestMove)
		{
			// Move ���� ��û �ؾ���
			m_bRequestMove = TRUE;
//			if(m_dwState == _FALLING || m_dwState == _EXPLODING)
//			{
//				ChangeUnitState( _FALLEN );
//				ResetBodyCondition(BODYCON_EXPLOSION_MASK);
//				m_fLifeTime = 2.0f;
//			}
//			else
//			{
				// 2006-06-15 by ispark, �����ð��� ������ ������� ����
//				MSG_FC_CHARACTER_GET_OTHER_MOVE sMsg;
//				memset(&sMsg,0x00,sizeof(sMsg));
//				char buffer[SIZE_MAX_PACKET];
//				sMsg.OtherClientIndex = m_infoCharacter.CharacterInfo.ClientIndex;
//				int nType = T_FC_CHARACTER_GET_OTHER_MOVE;
//				memcpy(buffer, &nType, SIZE_FIELD_TYPE_HEADER);
//				memcpy(buffer+SIZE_FIELD_TYPE_HEADER, &sMsg, sizeof(sMsg));
//				g_pD3dApp->m_pFieldWinSocket->Write(buffer, SIZE_FIELD_TYPE_HEADER + sizeof(sMsg));
				SetClientIndexDataByVector(g_pD3dApp->m_vecCharacterOtherMove, m_infoCharacter.CharacterInfo.ClientIndex);
				
				DBGOUT("(%s)Enemy LifeTime < -3.0f Request Infomation MSG_FC_CHARACTER_GET_OTHER_MOVE\n",
					m_infoCharacter.CharacterInfo.CharacterName);
//			}
		}

//		if( m_fLifeTime < -8.0f &&
////			m_infoParty.bPartyType == _NOPARTY && 
////			m_nPartyID == 0 &&
//			IsPkState(PK_PVP)==FALSE && 
//			IsPkState(PK_FVF)==FALSE )
		// ������ ������ ���� ���� ����
		if(m_bIsItemPointSet && m_fLifeTime <= -8.0f)
		{
			DeleteItemPoint();
			m_bIsItemPointSet = FALSE;
		}
		if( m_fLifeTime <= -8.0f )
		{
			m_bUsing = FALSE;
			DBGOUT("(%s)Enemy m_fLifeTime <= -8.0f --> Delete Enemy .2[m_dwState=%d]\n",
				m_infoCharacter.CharacterInfo.CharacterName,
				m_dwState);
			return;
		}
		else if(!m_bIsItemPointSet && m_fLifeTime > -8.0f)
		{
			if(m_fCheckItemInfoTime < 0.0f)
			{// ���� ��û
//				MSG_FC_CHARACTER_GET_OTHER_RENDER_INFO sMsg;
//				memset(&sMsg,0x00,sizeof(sMsg));
//				char buffer[SIZE_MAX_PACKET];
//				sMsg.ClientIndex = m_infoCharacter.CharacterInfo.ClientIndex;
//				int nType = T_FC_CHARACTER_GET_OTHER_RENDER_INFO;
//				memcpy(buffer, &nType, SIZE_FIELD_TYPE_HEADER);
//				memcpy(buffer+SIZE_FIELD_TYPE_HEADER, &sMsg, sizeof(sMsg));
//				g_pD3dApp->m_pFieldWinSocket->Write(buffer, SIZE_FIELD_TYPE_HEADER + sizeof(sMsg));
				SetClientIndexDataByVector(g_pD3dApp->m_vecCharacterOtherRenderInfo, m_infoCharacter.CharacterInfo.ClientIndex);
				m_fCheckItemInfoTime = 1.0f;
			}
		}

//		if(m_fLifeTime < 0.0f || 
//			m_infoParty.bPartyType == _PARTYOTHERMAPMASTER || 
//			m_infoParty.bPartyType == _PARTYOTHERMAPMEMBER 
//			|| m_infoParty.bPartyType == _PARTYRESTARTMEMBER)
//		{
//			g_pD3dApp->CalcObjectSourceScreenCoords(m_vPos, g_pD3dApp->GetBackBufferDesc().Width, g_pD3dApp->GetBackBufferDesc().Height, 
//				m_nObjScreenX, m_nObjScreenY, m_nObjScreenW );
//			return;
//		}
		// ��Ŷ�� ���� �ð��� ���� �̵� ������ ���δ�(������ ���� ��鸲 ����)
		if(m_fLifeTime < 1.5f && m_fLifeTime >= 0.0f)
		{
			vMovepos = m_vMovepos * (m_fLifeTime / 1.5f);
		}
		else if(m_fLifeTime < 0.0f)
		{
			vMovepos = D3DXVECTOR3(0,0,0);
		}
		else
		{
			vMovepos = m_vMovepos;
		}
	}
	else if( UNIT_STATE_NO_MOVE(m_dwState) ) 
	{	
		if(m_fLifeTime > -8.0f)
			m_fLifeTime -= fElapsedTime;
		if(m_fLifeTime < -8.0f)
			m_fLifeTime = -8.0f;
		// 2004-12-27 by jschoi
		float fDistance = g_pD3dApp->Distance3DTo2D(g_pShuttleChild->m_vPos, m_vPos);
		if( m_fLifeTime <= -8.0f &&
			(m_nPartyID == 0 ||
			m_nPartyID != g_pShuttleChild->m_pClientParty->GetPartyInfo().PartyID) &&
			fDistance > REMOVE_ENEMY_DISTANCE &&
			IsPkEnable() == FALSE)
		{
			m_bUsing = FALSE;
		}

		D3DXVECTOR3 vDistance = m_vNextPos - m_vPos;
		if( D3DXVec3Length( &vDistance ) < 3.0f )
		{
			m_vPos = m_vNextPos;
			m_vVel = m_vNextVel;
			m_vUp = m_vNextUp;
		}
		else
		{
			D3DXVec3Normalize( &vDistance, &vDistance );
			m_vPos += vDistance * 40 * g_pD3dApp->GetElapsedTime();
			m_vVel = m_vNextVel;
			m_vUp = m_vNextUp;
		}
	}
/*	// ������ üũ
	if(((!m_pWeapon1_1) && (!m_pWeapon1_2)) || 
		((!m_pWeapon2_1) && (!m_pWeapon2_2)) || 
		(m_CharacterRenderInfo.RI_Rear && !m_pEngine))
//		|| (m_CharacterRenderInfo.RI_Prow && !m_pRadar) 
//		|| (m_CharacterRenderInfo.RI_Center && !m_pArmor) 
//		|| (m_CharacterRenderInfo.RI_Attachment && !m_pContainer))
	{
		if(fCheckItemInfoTime <= 0.0f && 
			m_infoCharacter.ClientIndex < 10000 && 
			!IS_BT(m_infoCharacter.UnitKind) && 
			!IS_OT(m_infoCharacter.UnitKind) && 
			!IS_DT(m_infoCharacter.UnitKind))
*/
	if( m_fCheckItemInfoTime <= 0.0f &&
		m_infoCharacter.CharacterInfo.ClientIndex < 60000 &&
//		((IS_DT(m_infoCharacter.CharacterInfo.UnitKind) && !m_pWeapon1_1 && !m_pWeapon1_2) ||	!m_pEngine))
//		((IS_DT(m_infoCharacter.CharacterInfo.UnitKind) && !m_pWeapon1_1_1 && !m_pWeapon1_2) ||	!m_pEngine))
		(IS_DT(m_infoCharacter.CharacterInfo.UnitKind) && !m_pWeapon1_1_1 && !m_pWeapon1_2))
	{// ���� ��û
//		MSG_FC_CHARACTER_GET_OTHER_RENDER_INFO sMsg;
//		memset(&sMsg,0x00,sizeof(sMsg));
//		char buffer[SIZE_MAX_PACKET];
//		sMsg.ClientIndex = m_infoCharacter.CharacterInfo.ClientIndex;
//		int nType = T_FC_CHARACTER_GET_OTHER_RENDER_INFO;
//		memcpy(buffer, &nType, SIZE_FIELD_TYPE_HEADER);
//		memcpy(buffer+SIZE_FIELD_TYPE_HEADER, &sMsg, sizeof(sMsg));
//		g_pD3dApp->m_pFieldWinSocket->Write(buffer, SIZE_FIELD_TYPE_HEADER + sizeof(sMsg));
		SetClientIndexDataByVector(g_pD3dApp->m_vecCharacterOtherRenderInfo, m_infoCharacter.CharacterInfo.ClientIndex);

		m_fCheckItemInfoTime = 1.0f;
		DBGOUT("SEND ---> MSG_FC_CHARACTER_GET_OTHER_RENDER_INFO [%X],NAME[%s],INFOMATION[%X][%X][%X][%X][%X]\n",
			m_infoCharacter.CharacterInfo.UnitKind, m_infoCharacter.CharacterInfo.CharacterName,
			m_pWeapon1_1_1,m_pWeapon1_2,m_pWeapon2_1_1,m_pWeapon2_2,m_infoCharacter.CharacterRenderInfo.RI_Rear,m_pEngine);
	}

//	if( m_dwState == _INITIALIZING || m_infoCharacter.ClientIndex == INVALID_CLIENT_INDEX) 
//		return; // initializing
//	if(m_dwState==_NORMAL)

	PARTYENEMYINFO* pPartyEnemyInfo = NULL;
	if(m_nPartyID != 0)
	{
		pPartyEnemyInfo = g_pShuttleChild->m_pClientParty->FormationFlightFindMemberByUniqueNumber(
							m_infoCharacter.CharacterInfo.CharacterUniqueNumber);
	}

//	if(UNIT_STATE_MOVE(m_dwState))
	// 2005-08-29 by ispark
	// A��� �ϰ�� _LANDED�� ������ �����̴� ����̹Ƿ� �����̰� �Ѵ�.
	if((UNIT_STATE_MOVE(m_dwState) || 
		IS_DT(m_infoCharacter.CharacterInfo.UnitKind) == TRUE) && 
		pPartyEnemyInfo == NULL)
	{
		char buf[8];
		memset(buf,0x00,sizeof(buf));
//		m_nEnemyTypePrimary = ENEMYDATA_ENEMYLIST; // �ӽ� List  Ÿ���� ���־�������...

		D3DXVECTOR3 vOldVel;
		vOldVel = m_vVel;
		float fOldAngle,fCurAngle;
		fOldAngle = ACOS(D3DXVec3Dot(&m_vOriNextVel,&m_vVel));
//		m_vVel += 5.0f*m_vMoveVel*fElapsedTime;
		m_vVel += 1.5f*m_vMoveVel*fElapsedTime;
		D3DXVec3Normalize(&m_vVel,&m_vVel);
		fCurAngle = ACOS(D3DXVec3Dot(&m_vOriNextVel,&m_vVel));
		if(fCurAngle > fOldAngle)
			m_vVel = m_vOriNextVel;
		D3DXVec3Normalize(&m_vVel,&m_vVel);
		
		D3DXVECTOR3 vOldUp;
		vOldUp = m_vUp;
		fOldAngle = ACOS(D3DXVec3Dot(&m_vOriNextUp,&m_vUp));
//		m_vUp += 5.0f*m_vMoveUp*fElapsedTime;
		m_vUp += 1.5f*m_vMoveUp*fElapsedTime;
		D3DXVec3Normalize(&m_vUp,&m_vUp);
		fCurAngle = ACOS(D3DXVec3Dot(&m_vOriNextUp,&m_vUp));
		if(fCurAngle > fOldAngle)
			m_vUp = m_vOriNextUp;
		D3DXVec3Normalize(&m_vUp,&m_vUp);

		// 2005-07-08 by ispark
		// ���� �ӵ��� �ι�� �÷Ⱥ���
		if(!g_pShuttleChild->IsObserverMode())
			m_vPos += vMovepos*fElapsedTime*1.0f;
		else
			m_vPos += (m_vNextPos - m_vPos)*fElapsedTime;
	}
	if(m_dwState == _FALLING)
	{
		if(m_pEffectTarget)
		{
			m_pEffectTarget->m_bUsing = FALSE;
			m_pEffectTarget = NULL;
			char message[256];
			wsprintf(message,STRMSG_C_TARGET_0001);	//"2�� Ÿ�� ������"
			g_pD3dApp->m_pChat->CreateChatChild(message,COLOR_SYSTEM);
		}
//		m_nEnemyTypePrimary = ENEMYDATA_ENEMYLIST;
//		m_nEnemyTypeSecondary = ENEMYDATA_ENEMYLIST;
		if(g_pShuttleChild->m_pOrderTarget == this)
			g_pShuttleChild->m_pOrderTarget = NULL;

		if(m_fCurrentTime < 225.0f)
			m_fCurrentTime += 30.0f*fElapsedTime;
		if(m_fCurrentTime > 225.0f)
		{
			m_fCurrentTime = 186.0f;
		}
		if(m_vPos.y < g_pShuttleChild->CheckMap(m_vPos) + 2.0f)
		{
			ChangeUnitState( _FALLEN );
			ResetBodyCondition(BODYCON_EXPLOSION_MASK);
			m_fLifeTime = 2.0f;
			//m_dwState = _FALLEN;
			//ChangeSingleBodyCondition(BODYCON_DEAD_MASK);
		}
		m_vPos += vMovepos*fElapsedTime;
		m_vVel = m_vNextVel*200.0f*fElapsedTime;
		D3DXVec3Normalize(&m_vVel,&m_vVel);
		m_vUp += m_vMoveUp*fElapsedTime;
		D3DXVec3Normalize(&m_vUp,&m_vUp);
		// �������� üũ
		if( g_pShuttleChild->CheckIsWater(m_vPos) && 
			m_vPos.y < g_pGround->m_projectInfo.fWaterHeight)
		{
			m_bIsUnderWater = TRUE;
		}
	}
	else if( m_dwState == _FALLEN)
	{
		if(!COMPARE_BODYCON_BIT(GetCurrentBodyCondition(),BODYCON_DEAD_MASK))
		{
			ChangeSingleBodyCondition(BODYCON_DEAD_MASK);
			if(m_pEffectTarget)
			{
				m_pEffectTarget->m_bUsing = FALSE;
				m_pEffectTarget = NULL;
				char message[256];
				wsprintf(message,STRMSG_C_TARGET_0001);	//"2�� Ÿ�� ������"
				g_pD3dApp->m_pChat->CreateChatChild(message,COLOR_SYSTEM);
			}
//			m_nEnemyTypePrimary = ENEMYDATA_ENEMYLIST;
//			m_nEnemyTypeSecondary = ENEMYDATA_ENEMYLIST;
			if(g_pShuttleChild->m_pOrderTarget == this)
				g_pShuttleChild->m_pOrderTarget = NULL;

			m_vPos += vMovepos*fElapsedTime;
			m_vVel = m_vNextVel;//*200.0f*fElapsedTime;
			D3DXVec3Normalize(&m_vVel,&m_vVel);
			m_vUp = m_vNextUp;//*fElapsedTime;
			D3DXVec3Normalize(&m_vUp,&m_vUp);
			// �������� üũ
			if(g_pShuttleChild->CheckIsWater(m_vPos) && m_vPos.y < g_pGround->m_projectInfo.fWaterHeight)
				m_bIsUnderWater = TRUE;
		}


	}
	else if(m_dwState==_EXPLODING)
	{
		if(m_pEffectTarget)
		{
			m_pEffectTarget->m_bUsing = FALSE;
			m_pEffectTarget = NULL;
			char message[256];
			wsprintf(message,STRMSG_C_TARGET_0001);	//"2�� Ÿ�� ������"
			g_pD3dApp->m_pChat->CreateChatChild(message,COLOR_SYSTEM);
		}
//		m_nEnemyTypePrimary = ENEMYDATA_ENEMYLIST;
//		m_nEnemyTypeSecondary = ENEMYDATA_ENEMYLIST;
		if(g_pShuttleChild->m_pOrderTarget == this)
			g_pShuttleChild->m_pOrderTarget = NULL;

		if(m_fCurrentTime < 249.0f)
			m_fCurrentTime += 10.0f*fElapsedTime;
		if(m_fCurrentTime > 249.0f)
		{
			m_fCurrentTime = 250.0f;
			ChangeUnitState( _EXPLODED );
			//m_dwState = _EXPLODED;
		}
	}
	else if(m_dwState == _EXPLODED)
	{
		if(m_pEffectTarget)
		{
			m_pEffectTarget->m_bUsing = FALSE;
			m_pEffectTarget = NULL;
			char message[256];
			wsprintf(message,STRMSG_C_TARGET_0001);	//"2�� Ÿ�� ������"
			g_pD3dApp->m_pChat->CreateChatChild(message,COLOR_SYSTEM);
		}
//		m_nEnemyTypePrimary = ENEMYDATA_ENEMYLIST;
//		m_nEnemyTypeSecondary = ENEMYDATA_ENEMYLIST;
		if(g_pShuttleChild->m_pTarget == this)
			g_pShuttleChild->m_pTarget = NULL;

		m_fCurrentTime = 250.0f;
	}
	
	D3DXVECTOR3 vVirtualUp = m_vUp;

	// 2005-07-07 by ispark
	// �Ѹ� �ִϸ��̼�
	if(m_bRollStart)
	{
		float fElapsedTime = g_pD3dApp->GetElapsedTime();
		float fUpRate = RollingSystem(fElapsedTime);		// 2005-07-05 by ispark

		// 2009. 07. 07 by ckPark �κ���� ��û����(�Ѹ�, ����ȭ��, ����, A�������)

		// �κ� �Ƹ��� ���, �Ѹ� ȸ���� ���� �ʴ´�
		if( IsRobotArmor() )
			fUpRate = 0.0f;

		// end 2009. 07. 07 by ckPark �κ���� ��û����(�Ѹ�, ����ȭ��, ����, A�������)

		D3DXMATRIX mMatrix;
		D3DXMatrixRotationAxis(&mMatrix, &m_vVel, fUpRate);		
		D3DXVec3TransformCoord(&vVirtualUp, &m_vUp, &mMatrix );
	}
	
	// 2007-04-17 by dgwoo �ٸ� ������ �� ������ ���� ����.
//	D3DXMATRIX matVirtualTemp;
//	//D3DXMatrixRotationAxis(&matVirtualTemp, &m_vVel, 0.0f);
//	D3DXMatrixIdentity(&matVirtualTemp);
//	D3DXVec3TransformCoord(&vVirtualUp, &vVirtualUp, &matVirtualTemp);
//	D3DXMatrixLookAtRH( &m_mMatrix, &m_vPos, &(m_vPos+m_vVel), &vVirtualUp);
//	D3DXMatrixInverse( &m_mMatrix, NULL, &m_mMatrix );
//
	// �浹�� �ִϸ��̼��� �����ֱ� ���� ��Ʈ������ �����Ѵ�.
	D3DXMatrixLookAtRH( &m_mMatrix, &m_vPos, &(m_vPos+m_vVel), &m_vUp);
	D3DXMatrixLookAtRH( &m_mMatrix, &m_vPos, &(m_vPos+m_vVel), &vVirtualUp);
	D3DXMatrixInverse( &m_mMatrix, NULL, &m_mMatrix );
	m_vSideVel.x = m_mMatrix._11;
	m_vSideVel.y = m_mMatrix._12;
	m_vSideVel.z = m_mMatrix._13;

	if(IS_DT(m_infoCharacter.CharacterInfo.UnitKind) == TRUE)
	{
		D3DXVec3TransformCoord(&m_vLWBackPos, &m_PrimaryAttack.vSideBackPos, &m_mMatrix);
		D3DXVECTOR3 vTempPrimary = m_PrimaryAttack.vSideBackPos - m_PrimaryAttack.vSidePos;
		float fLen = D3DXVec3Length(&vTempPrimary);
		D3DXVec3Normalize(&m_vWeaponVel,&m_vWeaponVel);
		m_vLWPos = m_vLWBackPos + fLen*m_vWeaponVel;
		
		//D3DXVECTOR3 vPrimaryRightPos = D3DXVECTOR3(-m_vPrimarySidePos.x, m_vPrimarySidePos.y, m_vPrimarySidePos.z);
		D3DXVECTOR3 vPrimaryRightBackPos = D3DXVECTOR3(-m_PrimaryAttack.vSideBackPos.x, m_PrimaryAttack.vSideBackPos.y, m_PrimaryAttack.vSideBackPos.z);
		D3DXVECTOR3 vRWBackPos;
		D3DXVec3TransformCoord(&vRWBackPos, &vPrimaryRightBackPos, &m_mMatrix);
		m_vRWPos = vRWBackPos + fLen*m_vWeaponVel;
			
		// 2010-06-15 by shcho&hslee ��ý��� - ���� ��ġ
		D3DXVec3TransformCoord(&m_vPetLeftPos, &m_PetAttack.vSidePos, &m_mMatrix);
		
		D3DXVECTOR3 vPetRightPos = D3DXVECTOR3(-m_PetAttack.vSidePos.x,
												m_PetAttack.vSidePos.y, 
												m_PetAttack.vSidePos.z);
		D3DXVec3TransformCoord(&m_vPetRightPos, &vPetRightPos, &m_mMatrix);
		// end 2010-06-15 by shcho&hslee ��ý��� - ���� ��ġ
		m_vRWPos += 3.0f*m_vWeaponVel;
		D3DXVec3TransformCoord(&m_vLWSecondaryPos, &m_SecondaryAttack.vSidePos, &m_mMatrix);
		D3DXVECTOR3 vSecondaryRightPos = D3DXVECTOR3(-m_SecondaryAttack.vSidePos.x, m_SecondaryAttack.vSidePos.y, m_SecondaryAttack.vSidePos.z);
		D3DXVec3TransformCoord(&m_vRWSecondaryPos, &vSecondaryRightPos, &m_mMatrix);
	}
	else
	{
		D3DXVec3TransformCoord(&m_vLWPos, &m_PrimaryAttack.vSidePos, &m_mMatrix);
		m_vLWPos += 5.0f*m_vVel;
		D3DXVECTOR3 vPrimaryRightPos = D3DXVECTOR3(-m_PrimaryAttack.vSidePos.x, m_PrimaryAttack.vSidePos.y, m_PrimaryAttack.vSidePos.z);
		D3DXVec3TransformCoord(&m_vRWPos, &vPrimaryRightPos, &m_mMatrix);
		m_vRWPos += 5.0f*m_vVel;

		// 2010-06-15 by shcho&hslee ��ý��� - ���� ��ġ
		D3DXVec3TransformCoord(&m_vPetLeftPos, &m_PetAttack.vSidePos, &m_mMatrix);
		
		D3DXVECTOR3 vPetRightPos = D3DXVECTOR3(-m_PetAttack.vSidePos.x,
												m_PetAttack.vSidePos.y, 
												m_PetAttack.vSidePos.z);
		D3DXVec3TransformCoord(&m_vPetRightPos, &vPetRightPos, &m_mMatrix);
		// end 2010-06-15 by shcho&hslee ��ý��� - ���� ��ġ

		// 2010-12-27 by hsson ��ý��� - �� ����ȭ �κ� ����
		m_vPetLeftVel = m_vVel;
		m_vPetRightVel = m_vVel;
		// end 2010-12-27 by hsson ��ý��� - �� ����ȭ �κ� ����

		D3DXVec3TransformCoord(&m_vLWSecondaryPos, &m_SecondaryAttack.vSidePos, &m_mMatrix);
		D3DXVECTOR3 vSecondaryRightPos = D3DXVECTOR3(-m_SecondaryAttack.vSidePos.x, m_SecondaryAttack.vSidePos.y, m_SecondaryAttack.vSidePos.z);
		D3DXVec3TransformCoord(&m_vRWSecondaryPos, &vSecondaryRightPos, &m_mMatrix);
	}
	// SKILL EFFECT
	if(m_pSkillEffect)
	{
		m_pSkillEffect->Tick(fElapsedTime);
	}
	

	// 2005-01-05 by jschoi - ���� ���� �޽� ��� ����.
//	m_bCheckBlend = FALSE;

	m_bCheckColl = FALSE;
	// 50.0f ��ġ�� ���Ŀ� ��Ʋ�� ũ��� ������ ũ���� ���� ������ ũ��� ���õǾ���Ѵ�.
	if(D3DXVec3Length(&(m_vPos - g_pShuttleChild->m_vPos)) < 50.0f)
	{
		m_bCheckColl = TRUE;
		g_pShuttleChild->m_bCollShuttleCheck++;		// ��Ʋ���� �浹 üũ��ƾ�� ����� ����
	}

	///  Enemy �� ����ü �ø��� �����Ͽ� m_vecEnemyRenderList �� �����. - 2004-07-31 jschoi
	if(m_bUsing)
	{
		BOOL bResult = g_pFrustum->CheckSphere( m_vPos.x, m_vPos.y, m_vPos.z, m_fObjectSize );
		if(bResult)
		{
			g_pScene->m_vecEnemyRenderList.push_back(this);
			g_pScene->m_vecUnitRenderList.push_back((CUnitData*)this);
			m_fDistanceCamera = D3DXVec3Length(&(m_vPos - g_pD3dApp->m_pCamera->GetEyePt()));

			// 2005-01-05 by jschoi - ���� ���� �޽� ��� ����.
//			D3DXVECTOR3 v1,v2;
//			m_bCheckBlend = FALSE;
//			D3DXVec3Normalize(&v1,&(g_pShuttleChild->m_vPos - g_pD3dApp->m_pCamera->GetEyePt()));
//			D3DXVec3Normalize(&v2,&(m_vPos - g_pD3dApp->m_pCamera->GetEyePt()));
//			float fDistance = D3DXVec3Length(&(g_pShuttleChild->m_vPos-m_vPos));
//			if(g_pShuttleChild->m_fDistanceCamera + m_fObjectSize > m_fDistanceCamera)
//			{
//				if(sin(ACOS(D3DXVec3Dot(&v1,&v2)))*m_fDistanceCamera <= m_fObjectSize)
//				{
//					m_bCheckBlend = TRUE;
//				}
//			}
		}	
	}

	/// �׸��� �׸� Enemy ���� 2004-07-29 jschoi
	if(m_bUsing)
	{
		D3DXVECTOR3 vShadowPos;
		vShadowPos = m_vPos;
		BOOL bIsWater = g_pShuttleChild->CheckIsWater(m_vPos);
		if(bIsWater)
		{
			vShadowPos.y = g_pGround->m_projectInfo.fWaterHeight;
		}
		else
		{
			vShadowPos.y = g_pCamera->CheckMap(m_vPos);
		}
		BOOL bOnObject = FALSE;
		float fDistance = CheckOnObject();
		if(fDistance != DEFAULT_COLLISION_DISTANCE)
		{
			vShadowPos.y = m_vPos.y - fDistance;
			bOnObject = TRUE;
		}
		m_bShadowIsRender = FALSE;
		if(g_pSOption->sShadowState > 0)
		{
			BOOL bResult = g_pFrustum->CheckSphere( vShadowPos.x, vShadowPos.y, vShadowPos.z, m_fObjectSize );
			float fDistanceToCam = D3DXVec3Length(&(vShadowPos - g_pD3dApp->m_pCamera->GetEyePt()));
	//		if( g_pSOption->sShadowState && bResult && fDistanceToCam < SHADOW_MAX_DISTANCE)
//			if( bResult && 
//				fDistanceToCam < g_pScene->m_fFogEndValue*g_pSOption->sShadowState/MAX_OPTION_VALUE)
			if( bResult && 
				fDistanceToCam < RANGE_OF_VISION*g_pSOption->sShadowState/MAX_OPTION_VALUE)
			{
				m_bShadowIsRender = TRUE;
				g_pScene->m_vecEnemyShadowRenderList.push_back(this);
				CheckShadowPos(bOnObject);
			}
		}
	}

	// effect matrix & ticking
	if(m_pCharacterInfo)
	{
		m_pCharacterInfo->SetAllBodyConditionMatrix( m_mMatrix );
		m_pCharacterInfo->Tick(fElapsedTime);
		m_fCurrentTime = GetCurrentAnimationTime();
	}

	if(m_bUseMoveSkill)
	{
		MoveSkill();
	}
	
//	D3DXVECTOR3 v1,v2;
	if(D3DXVec3Length(&(g_pShuttleChild->m_vPos - m_vPos)) > 200.0f)
		m_bZBuffer = TRUE;
	else
		m_bZBuffer = FALSE;

	m_ptCurRegion.x = (int)(m_vPos.x/(TILE_SIZE*3));
	m_ptCurRegion.y = (int)(m_vPos.z/(TILE_SIZE*3));
	if( m_ptCurRegion.x < 0 )
	{
		m_ptCurRegion.x = 0;
		DBGOUT("ENEMY m_ptCurRegion.x < 0\n");
	}
	if( m_ptCurRegion.y < 0 )
	{
		m_ptCurRegion.y = 0;
		DBGOUT("ENEMY m_ptCurRegion.y < 0\n");
	}
	if( m_ptCurRegion.x > g_pGround->m_projectInfo.sXSize/3 )
	{
		m_ptCurRegion.x = g_pGround->m_projectInfo.sXSize/3;
		DBGOUT("ENEMY m_ptCurRegion.x > g_pGround->m_projectInfo.sXSize/3\n");
	}
	if( m_ptCurRegion.y > g_pGround->m_projectInfo.sYSize/3 )
	{
		m_ptCurRegion.y = g_pGround->m_projectInfo.sYSize/3;
		DBGOUT("ENEMY m_ptCurRegion.y > g_pGround->m_projectInfo.sYSize/3\n");
	}

	if(m_ptCurRegion.x != m_ptOldRegion.x || m_ptCurRegion.y != m_ptOldRegion.y)
	{
		g_pScene->ChangeToBlockData(this);
	}


//	CheckPrimaryAttack(FALSE);
	m_PrimaryAttack.fCheckAutoMaticTimer -= g_pD3dApp->GetElapsedTime();
	m_PrimaryAttack.fCheckAttackTime -= g_pD3dApp->GetElapsedTime();
	// 2010-06-15 by shcho&hslee ��ý��� - �� ���� ó��
	m_PetAttack.fCheckAutoMaticTimer -= g_pD3dApp->GetElapsedTime();
	m_PetAttack.fCheckAttackTime -= g_pD3dApp->GetElapsedTime();
	//SetPetPosition();
	// end 2010-06-15 by shcho&hslee ��ý��� - �� ���� ó��

	CheckAttack(m_PrimaryAttack, FALSE);
	m_SecondaryAttack.fCheckAutoMaticTimer -= g_pD3dApp->GetElapsedTime();
	m_SecondaryAttack.fCheckAttackTime -= g_pD3dApp->GetElapsedTime();
//	CheckAttack(m_SecondaryAttack, FALSE);


	
	float fDistanceToCamera;
	float fDistance;

	INT nOldDegree = m_bDegree;
	
	fDistanceToCamera = D3DXVec3Length(&(m_vPos - g_pD3dApp->m_pCamera->GetEyePt()));
// 	fDistance = (g_pScene->m_fFogEndValue*g_pSOption->sUnitDetail)/MAX_OPTION_VALUE;
	fDistance = (RANGE_OF_VISION*g_pSOption->sUnitDetail)/MAX_OPTION_VALUE;
	if(fDistanceToCamera < fDistance)
	{
		m_bDegree = 2;
		m_bItemDegree = TRUE;
	}
	else
	{
		m_bDegree = 0;
		m_bItemDegree = FALSE;
	}

	if(nOldDegree != m_bDegree)
	{
		// 2005-11-24 by ispark, ItemNum -> SourceIndex���� ����

		// 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����
		//ITEM * pItem = g_pDatabase->GetServerItemInfo(m_infoCharacter.CharacterRenderInfo.RI_Center);

		// ���������۹�ȣ�� ���ٸ� ���� ������ ��ȣ�� ����Ѵ�
		int nItemNum = 0;
		if( m_infoCharacter.CharacterRenderInfo.RI_Center_ShapeItemNum )
			nItemNum = m_infoCharacter.CharacterRenderInfo.RI_Center_ShapeItemNum;
		else
			nItemNum = m_infoCharacter.CharacterRenderInfo.RI_Center;

		ITEM* pItem = g_pDatabase->GetServerItemInfo( nItemNum );
		// end 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����
		// 2010. 03. 18 by jskim ���ͺ��� ī��
		BOOL bMonTras = FALSE;

		if(m_MonsterTransformer)
		{
			ChangeUnitCharacterInfo(nItemNum, m_infoCharacter.CharacterInfo.UnitKind, m_infoCharacter.CharacterInfo.BodyCondition, FALSE);
			SetMonsterTransPrimarySidePos(m_PrimaryAttack.vSidePos);
			SetMonsterTransSecondarySidePos(m_SecondaryAttack.vSidePos);
		}

		if(m_MonsterTransformer)
		{
			bMonTras = TRUE;
			MEX_MONSTER_INFO * pTempIn = g_pGameMain->CheckMonsterInfo( m_MonsterTransformer );
			if(pTempIn)
				nItemNum = pTempIn->SourceIndex;
		}
		else
		{
			if(pItem)
				nItemNum = pItem->SourceIndex;
		}

#ifdef _RAT_FFA
		if (MAP_INFLUENCE_PVP_ALL == g_pD3dApp->GetMyShuttleMapInfo()->MapInfluenceType)
			pItem = NULL;
#endif

		//end 2010. 03. 18 by jskim ���ͺ��� ī��
		if(pItem)
		{
			// 2010. 03. 18 by jskim ���ͺ��� ī��
			// 			ChangeUnitCharacterInfo(pItem->SourceIndex, 
			// 				m_infoCharacter.CharacterInfo.UnitKind, m_infoCharacter.CharacterInfo.BodyCondition, FALSE);
			ChangeUnitCharacterInfo(nItemNum, 
				m_infoCharacter.CharacterInfo.UnitKind, m_infoCharacter.CharacterInfo.BodyCondition, FALSE , bMonTras);
			//end 2010. 03. 18 by jskim ���ͺ��� ī��
		}
		else
		{
			// ����Ʈ
			ChangeUnitCharacterInfo(0, 
				m_infoCharacter.CharacterInfo.UnitKind, m_infoCharacter.CharacterInfo.BodyCondition, FALSE);
		}

		if(m_pCharacterInfo)
		{
			m_pCharacterInfo->SetShuttleChildEffect(FALSE);
		}
	}
/*	if(fDistanceToCamera < RANGE_OF_VISION)
	{
		m_bItemDegree = TRUE;
	}
	else
	{
		m_bItemDegree = FALSE;
	}
*/
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			TickCharacter(float fElapsedTime)
/// \brief		
/// \author		ispark
/// \date		2005-07-27 ~ 2005-07-27
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CEnemyData::TickCharacter(float fElapsedTime)
{
	//////////////////////////////////////////////////////////////////////////
	// �̵�
	D3DXVECTOR3 vMovepos = D3DXVECTOR3(0,0,0);
	// ��Ŷ�� ���� �ð��� ���� �̵� ������ ���δ�(������ ���� ��鸲 ����)
	if(m_fLifeTime < 1.5f && m_fLifeTime >= 0.0f)
	{
		vMovepos = m_vMovepos * (m_fLifeTime / 1.5f);
	}
	else if(m_fLifeTime < 0.0f)
	{
		vMovepos = D3DXVECTOR3(0,0,0);
	}
	else
	{
		vMovepos = m_vMovepos;
	}

	// 2006-01-10 by ispark, ���� ���� ��û Ÿ��
	if(m_fLifeTime > -8.0f)
		m_fLifeTime -= fElapsedTime;
	if(m_fLifeTime < -8.0f)
		m_fLifeTime = -8.0f;

	if(	m_fLifeTime > -8.0f && 
		m_fLifeTime < -3.0f && 
		!m_bRequestMove)
	{
		// Move ���� ��û �ؾ���
		m_bRequestMove = TRUE;
		// 2006-06-15 by ispark, �����ð��� ������ ������� ����
//		MSG_FC_CHARACTER_GET_OTHER_MOVE sMsg;
//		memset(&sMsg,0x00,sizeof(sMsg));
//		char buffer[SIZE_MAX_PACKET];
//		sMsg.OtherClientIndex = m_infoCharacter.CharacterInfo.ClientIndex;
//		int nType = T_FC_CHARACTER_GET_OTHER_MOVE;
//		memcpy(buffer, &nType, SIZE_FIELD_TYPE_HEADER);
//		memcpy(buffer+SIZE_FIELD_TYPE_HEADER, &sMsg, sizeof(sMsg));
//		g_pD3dApp->m_pFieldWinSocket->Write(buffer, SIZE_FIELD_TYPE_HEADER + sizeof(sMsg));
		SetClientIndexDataByVector(g_pD3dApp->m_vecCharacterOtherMove, m_infoCharacter.CharacterInfo.ClientIndex);

		DBGOUT("(%s)Enemy LifeTime < -3.0f Request Infomation MSG_FC_CHARACTER_GET_OTHER_MOVE\n",
			m_infoCharacter.CharacterInfo.CharacterName);
	}

	if( m_fLifeTime <= -8.0f )
	{
		m_bUsing = FALSE;
		DBGOUT("(%s)Enemy m_fLifeTime <= -8.0f --> Delete Enemy .2[m_dwState=%d]\n",
			m_infoCharacter.CharacterInfo.CharacterName,
			m_dwState);
		return;
	}

//	if( UNIT_STATE_NO_MOVE(m_dwState) ) 
//	{	
//		if(m_fLifeTime > -8.0f)
//			m_fLifeTime -= fElapsedTime;
//		if(m_fLifeTime < -8.0f)
//			m_fLifeTime = -8.0f;
//		// 2004-12-27 by jschoi
//		float fDistance = g_pD3dApp->Distance3DTo2D(g_pShuttleChild->m_vPos, m_vPos);
//		if( m_fLifeTime <= -8.0f &&
//			(m_nPartyID == 0 ||
//			m_nPartyID != g_pShuttleChild->m_pClientParty->GetPartyInfo().PartyID) &&
//			fDistance > REMOVE_ENEMY_DISTANCE &&
//			IsPkEnable() == FALSE)
//		{
//			m_bUsing = FALSE;
//		}
//
//		D3DXVECTOR3 vDistance = m_vNextPos - m_vPos;
//		if( D3DXVec3Length( &vDistance ) < 3.0f )
//		{
//			m_vPos = m_vNextPos;
//			m_vVel = m_vNextVel;
//			m_vUp = m_vNextUp;
//		}
//		else
//		{
//			D3DXVec3Normalize( &vDistance, &vDistance );
//			m_vPos += vDistance * 40 * g_pD3dApp->GetElapsedTime();
//			m_vVel = m_vNextVel;
//			m_vUp = m_vNextUp;
//		}
//	}

//	PARTYENEMYINFO* pPartyEnemyInfo = NULL;
//	if(m_nPartyID != 0)
//	{
//		pPartyEnemyInfo = g_pShuttleChild->m_pClientParty->FormationFlightFindMemberByUniqueNumber(
//							m_infoCharacter.CharacterInfo.CharacterUniqueNumber);
//	}
//	
//	if(UNIT_STATE_MOVE(m_dwState) && pPartyEnemyInfo == NULL)
	{
		char buf[8];
		memset(buf,0x00,sizeof(buf));
//		m_nEnemyTypePrimary = ENEMYDATA_ENEMYLIST; // �ӽ� List  Ÿ���� ���־�������...

//		D3DXVECTOR3 vOldVel;
//		vOldVel = m_vVel;
//		float fOldAngle,fCurAngle;
//		fOldAngle = ACOS(D3DXVec3Dot(&m_vOriNextVel,&m_vVel));
////		m_vVel += 5.0f*m_vMoveVel*fElapsedTime;
//		m_vVel += 1.5f*m_vMoveVel*fElapsedTime;
//		D3DXVec3Normalize(&m_vVel,&m_vVel);
//		fCurAngle = ACOS(D3DXVec3Dot(&m_vOriNextVel,&m_vVel));
//		if(fCurAngle > fOldAngle)
//			m_vVel = m_vOriNextVel;
//		D3DXVec3Normalize(&m_vVel,&m_vVel);
		
//		D3DXVECTOR3 vOldUp;
//		vOldUp = m_vUp;
//		fOldAngle = ACOS(D3DXVec3Dot(&m_vOriNextUp,&m_vUp));
////		m_vUp += 5.0f*m_vMoveUp*fElapsedTime;
//		m_vUp += 1.5f*m_vMoveUp*fElapsedTime;
//		D3DXVec3Normalize(&m_vUp,&m_vUp);
//		fCurAngle = ACOS(D3DXVec3Dot(&m_vOriNextUp,&m_vUp));
//		if(fCurAngle > fOldAngle)
//			m_vUp = m_vOriNextUp;
//		D3DXVec3Normalize(&m_vUp,&m_vUp);

		// 2005-07-28 by ispark
		// ĳ���� ���� ���ʹ� ��� �ٲ۴�.
//		float fAngle;
//		D3DXMATRIX matTemp;
//		fAngle = ACOS(D3DXVec3Dot(&m_vOriNextVel,&m_vVel));
//		D3DXMatrixRotationY(&matTemp, (float)fAngle);
//		D3DXVec3TransformCoord(&m_vVel, &m_vVel, &matTemp);
		m_vVel = m_vOriNextVel;

		// ĳ���ʹ� Up���Ͱ� �׻� �ؿ� ���̴�.
		m_vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// 2005-07-08 by ispark
		// ���� �ӵ��� �ι�� �÷Ⱥ���
		m_vPos += vMovepos*fElapsedTime*1.0f;
	}


	// 2005-08-04 by ispark 
//	g_pD3dApp->CalcObjectSourceScreenCoords(m_vPos, g_pD3dApp->GetBackBufferDesc().Width, g_pD3dApp->GetBackBufferDesc().Height, 
//		m_nObjScreenX, m_nObjScreenY, m_nObjScreenW );

	//////////////////////////////////////////////////////////////////////////
	// ������ �� ���ΰ�?
	if(m_bUsing)
	{
		BOOL bResult = g_pFrustum->CheckSphere( m_vPos.x, m_vPos.y, m_vPos.z, m_fObjectSize );
		if(bResult)
		{
			g_pScene->m_vecEnemyRenderList.push_back(this);
			g_pScene->m_vecUnitRenderList.push_back((CUnitData*)this);
			m_fDistanceCamera = D3DXVec3Length(&(m_vPos - g_pD3dApp->m_pCamera->GetEyePt()));

			// 2006-07-26 by ispark, ĳ���� ���� �̺�Ʈ������ ���� �̵� ����
			CObjectChild* pCurrentObjEvent;
			pCurrentObjEvent = (CObjectChild *)g_pScene->m_pObjectRender->CheckCollMeshEventOther(m_vPos, m_vVel, m_vUp, 80.0f, EVENT_TYPE_CHARACTERMODE_WARP_TARGET);
			if(pCurrentObjEvent == NULL)
			{
				pCurrentObjEvent = (CObjectChild *)g_pScene->m_pObjectRender->CheckCollMeshEventOther(m_vPos, m_vVel, m_vUp, 80.0f, EVENT_TYPE_CHARACTERMODE_WARP);
			}

			if(pCurrentObjEvent)
			{
				D3DXVECTOR3 vEventPos = pCurrentObjEvent->m_vPos;
				D3DXVECTOR3 vChaPos = m_vPos;
				vEventPos.y = vChaPos.y = 0.0f;

				if(D3DXVec3Length(&D3DXVECTOR3(vEventPos - vChaPos)) > 14.0f)
				{
					// 2005-08-04 by ispark
					// ������ �Ҷ��� ��ǥ���� ��Ȯ�ϰ� üũ�Ѵ�.
					CheckCharacterPos();
				}
			}
			else
			{
				// 2005-08-04 by ispark
				// ������ �Ҷ��� ��ǥ���� ��Ȯ�ϰ� üũ�Ѵ�.
				CheckCharacterPos();
			}

			// �׸���
			if(0 < g_pSOption->sShadowState)
			{
				m_bShadowIsRender = TRUE;
				g_pScene->m_vecEnemyShadowRenderList.push_back(this);
				// 2005-07-27 by ispark
				CheckShadowPos();				
			}
		}	
	}	

	//////////////////////////////////////////////////////////////////////////
	// �׸���
//	D3DXVECTOR3 vShadowPos;
//	vShadowPos = m_vPos;
//	// 2005-08-01 by ispark
//	if(m_bUsing)
//	{
//		m_bShadowIsRender = FALSE;
//		if(g_pSOption->sShadowState > 0)
//		{
//			BOOL bResult = g_pFrustum->CheckSphere( vShadowPos.x, vShadowPos.y, vShadowPos.z, m_fObjectSize );
//			float fDistanceToCam = D3DXVec3Length(&(vShadowPos - g_pD3dApp->m_pCamera->GetEyePt()));
//			if( bResult && 
//				fDistanceToCam < RANGE_OF_VISION*g_pSOption->sShadowState/MAX_OPTION_VALUE)
//			{
//				m_bShadowIsRender = TRUE;
//				g_pScene->m_vecEnemyShadowRenderList.push_back(this);
//				// 2005-07-27 by ispark
//				CheckShadowPos();
//			}
//		}
//
//	}

	// �浹�� �ִϸ��̼��� �����ֱ� ���� ��Ʈ������ �����Ѵ�.
	D3DXMatrixLookAtRH( &m_mMatrix, &m_vPos, &(m_vPos+m_vVel), &m_vUp);
	D3DXMatrixInverse( &m_mMatrix, NULL, &m_mMatrix );
	// 2005-08-04 by ispark
	D3DXVec3Cross(&m_vSideVel,&m_vUp,&m_vVel);
//	m_vSideVel.x = m_mMatrix._11;
//	m_vSideVel.y = m_mMatrix._12;
//	m_vSideVel.z = m_mMatrix._13;

	// 2005-07-28 by ispark
	// ĳ���� ������ Ȯ��
	D3DXMATRIX matTemp;
	D3DXMatrixScaling(&matTemp, CHARACTER_SCALE, CHARACTER_SCALE, CHARACTER_SCALE);
	m_mMatrix = matTemp * m_mMatrix;

	//////////////////////////////////////////////////////////////////////////
	// �ִϸ��̼�
	// 2005-08-04 by ispark
	// X�� Z�������� �Ǵ�. Y���� ����
	// �ٵ� ����� �Ǵ�
	if(m_pEnemyCharacterInfo)
	{
		if(m_vOldPos.x == m_vPos.x &&
			m_vOldPos.z == m_vPos.z)
		{
			// �������� ���� ����
			m_pEnemyCharacterInfo->ChangeBodyCondition(BODYCON_CHARACTER_MODE_STOP);
			if(m_pContainer)
			{
				m_pContainer->ChangeBodyCondition(BODYCON_CHARACTER_MODE_STOP);					// 2006-06-29 by ispark
			}
		}
		else
		{
			// �����̴� ���� (�޸���)
			m_pEnemyCharacterInfo->ChangeBodyCondition(BODYCON_CHARACTER_MODE_RUN);
			if(m_pContainer)
			{
				m_pContainer->ChangeBodyCondition(BODYCON_CHARACTER_MODE_RUN);					// 2006-06-29 by ispark
			}
		}
	}

	// �Է�
	if(m_pEnemyCharacterInfo)
	{
		m_pEnemyCharacterInfo->SetAllBodyConditionMatrix(m_mMatrix);
		m_pEnemyCharacterInfo->Tick(fElapsedTime);
		m_fCurrentTime = m_pEnemyCharacterInfo->GetCurrentCharacterAnimationTime();
	}

	m_vOldPos = m_vPos;

}


///////////////////////////////////////////////////////////////////////////////
/// \fn			CEnemyData::SetPilotNumber(BYTE PilotFace)
/// \brief		�� ĳ���� �ѹ� �Է�
/// \author		ispark
/// \date		2005-07-28 ~ 2005-07-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CEnemyData::SetPilotNumber(BYTE PilotFace)
{
	int nTemp = ::GetUnitNum(0, 0, PilotFace, TRUE);
	if(nTemp != m_nPilotNum)
	{
		char strFileName[16];
		m_nPilotNum = nTemp;
		wsprintf( strFileName, "%08d", m_nPilotNum );
		LoadEnemyCharacterInfo(strFileName);
		if(m_pEnemyCharacterInfo)
		{
			m_pEnemyCharacterInfo->SetAllBodyConditionMatrix(m_mMatrix);
			m_pEnemyCharacterInfo->SetCharacterAnimationBodyConditionMask(BODYCON_HUMAN_ANIMATION_TIME);
			m_pEnemyCharacterInfo->SetBodyCondition(m_hyBodyCondition);
		}
	}
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			CEnemyData::CheckCharacterPos()
/// \brief		�� ĳ���� ��ġ ����
/// \author		ispark
/// \date		2005-08-04 ~ 2005-08-04
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CEnemyData::CheckCharacterPos()
{
	//////////////////////////////////////////////////////////////////////////
	// ������Ʈ �浹
	// ���⼭ ������Ʈ�� ���� �����̴�.
	// ĳ���ʹ� ������Ʈ ���� �����Ѵٴ� ���Ƿ� �����Ѵ�. ���� ���� ����
	D3DXVECTOR3 vPos = m_vPos;
	vPos.y += 7.087f;			// �浹�˻�� ���� ���� ���� �ø���.
	float fTempHeight = 0.0f;
	float fObjHeight = -DEFAULT_COLLISION_DISTANCE;
	
	D3DXMATRIX matTemp;
	D3DXVECTOR3 vSide(0, 0, 1), vUp(0, 1, 0);
	D3DXMatrixLookAtLH(&matTemp,&vPos,&(vPos - vUp),&vSide);
	fTempHeight = g_pScene->m_pObjectRender->CheckCollMesh(matTemp,vPos).fDist - 7.087f;
	
	if(fTempHeight<m_vPos.y)
		m_vPos.y += -fTempHeight;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CEnemyData::DeleteChatMoveShop()
/// \brief		
/// \author		ispark
/// \date		2006-08-03 ~ 2006-08-03
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CEnemyData::DeleteChatMoveShop()
{
	m_byBazaarType = 0;
	memset(m_szBazaarName, 0x00, SIZE_MAX_BAZAAR_NAME);
	m_pMoveChatShop->InvalidateDeviceObjects();
	m_pMoveChatShop->DeleteDeviceObjects();
	SAFE_DELETE(m_pMoveChatShop);
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CEnemyData::UseSkillFromServer(INT ItemNum)
/// \brief		���� ���� ��ų ������ ó��
/// \author		ispark
/// \date		2006-11-27 ~ 2006-11-27
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CEnemyData::UseSkillFromServer(INT ItemNum)
{
	ITEM *pitem = g_pDatabase->GetServerItemInfo(ItemNum);

	// ������ ��ų�� ��� ��Ű�� ��ų(������� ���)
	// ��ĳ��
	// 2009-04-21 by bhsohn ������ DesParam�߰�
	//if(IS_EXIST_DES_PARAM(pitem, DES_SKILL_SCANNING))
	if(pitem->IsExistDesParam(DES_SKILL_SCANNING))
	{
		// 2007-02-12 by dgwoo ������ ��ĵ��ų�� ����������.
		// 2007-04-19 by bhsohn ��ġ���� ������ �߰�
		D3DXVECTOR3	vVel, vUp;
		vVel = D3DXVECTOR3(0,0,1);
		vUp = D3DXVECTOR3(0,1,0);
// 2012-11-29 by mspark, ��ġ���� ��ġ�� �̵��ϴ� ĳ������ ��ġ�� �����ϵ��� ����
#ifdef SC_SEARCHEYE_SHUTTLE_POSITION_JHSEOL_MSPARK
		//
#else
		g_pScene->AddFieldItemScanObject(this,pitem->Time, RC_EFF_SCAN_SKILL, _LAY, vVel, vUp);
#endif
// end 2012-11-29 by mspark, ��ġ���� ��ġ�� �̵��ϴ� ĳ������ ��ġ�� �����ϵ��� ����
 	
//		if(!IsInfluenceCharacter(g_pShuttleChild->m_myShuttleInfo.InfluenceType,m_infoCharacter.CharacterInfo.InfluenceType) ||	// ����� �̰ų�
//			IsPkEnable())																											// PK���
//			{
// 2007-02-06 by dgwoo SCAN ��ų�� ���� ��������� ��ų�� ����ϴ°��� �ƴ϶�  ���̰� �Ѵ�.
//					g_pShuttleChild->m_pSkill->ReleseSkill(DES_SKILL_SCANNING, ItemNum);
//			}
	}
 	
	// 2007-02-28 by dgwoo �������� ��ȭ��ų�� ��������� ĳ����Ÿ�����ִ� ��ų�� ����Ʈ�� �����Ѵ�.
	// 2009-04-21 by bhsohn ������ DesParam�߰�
	//if(IS_EXIST_DES_PARAM(pitem, DES_SKILL_CANCELALL))
	if(pitem->IsExistDesParam(DES_SKILL_CANCELALL))
	{
		m_pSkillEffect->DeleteCastingStateSkillEffect();
	}


	// 2009. 09. 21 by ckPark ���Ǵ�Ƽ �ʵ� ���� ��ų ����
	// 2012-02-23 by jhahn ħ���� ��� ����Ʈ ���� ����


	// ���� ������� ���� ����
	if( pitem->IsExistDesParam( DES_SKILL_RELEASE )  ||
		ItemNum/10 == IGEAR_SKILL_BASENUM_SILENCE / 10 )
		m_pSkillEffect->DeleteCastingStateMonsterSkillEffect();

	//end 2012-02-23 by jhahn ħ���� ��� ����Ʈ ���� ����
	// end 2009. 09. 21 by ckPark ���Ǵ�Ƽ �ʵ� ���� ��ų ����

		
	//--------------------------------------------------------------------------//
	// ����, �κ�����
	// 2009-04-21 by bhsohn ������ DesParam�߰�
// 	if(IS_EXIST_DES_PARAM(pitem, DES_SKILL_CAMOUFLAGE) ||
// 		IS_EXIST_DES_PARAM(pitem, DES_INVISIBLE))
	if(pitem->IsExistDesParam(DES_SKILL_CAMOUFLAGE) ||
		pitem->IsExistDesParam(DES_INVISIBLE))
	{
		SetAlphaData();
	}	
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CEnemyData::CancelUsingSkill(INT ItemNum)
/// \brief		
/// \author		dgwoo
/// \date		2006-11-28 ~ 2006-11-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CEnemyData::CancelUsingSkill(INT ItemNum)
{
	ITEM *pitem = g_pDatabase->GetServerItemInfo(ItemNum);

	// ĳ���� Ÿ���� �ִ� ��ų ����Ʈ�� �����Ѵ�.
	if(pitem->AttackTime > 0)
	{
		m_pSkillEffect->DeleteCastingStateSkillEffect();		
	}


	// 2009. 09. 21 by ckPark ���Ǵ�Ƽ �ʵ� ���� ��ų ����

	if( pitem->AttackTime > 0 )
	{
		m_pSkillEffect->DeleteCastingStateMonsterSkillEffect();
	}

	// end 2009. 09. 21 by ckPark ���Ǵ�Ƽ �ʵ� ���� ��ų ����

	//--------------------------------------------------------------------------//
	// ����, �κ�����
	// 2009-04-21 by bhsohn ������ DesParam�߰�
// 	if(IS_EXIST_DES_PARAM(pitem, DES_SKILL_CAMOUFLAGE) ||
// 		IS_EXIST_DES_PARAM(pitem, DES_INVISIBLE))
	if(pitem->IsExistDesParam(DES_SKILL_CAMOUFLAGE) ||
		pitem->IsExistDesParam(DES_INVISIBLE))
	{
		InitAlphaData();
	}	
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CEnemyData::SetAlphaData()
/// \brief		��쿡 ���� ���� �Ǵ� ���������� ���̰� �Ѵ�.
/// \author		ispark
/// \date		2006-11-28 ~ 2006-11-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CEnemyData::SetAlphaData()
{
	// 2007-04-19 by bhsohn ��ġ���� ������ �߰�
	// ��ĵ ������ ������ �����ʰų�  �Ÿ��� �ָ� �����ϰ� ���δ�.
	BOOL bCanSeeInvisible = g_pShuttleChild->m_pSkill->IsCanSeeInvisible(m_vPos);

	if((((!IsInfluenceCharacter(g_pShuttleChild->m_myShuttleInfo.InfluenceType, m_infoCharacter.CharacterInfo.InfluenceType)		// �ٸ� �����̰ų�.
		|| IsPkEnable())																// PK����϶�.
#ifdef _RAT_FFA
		|| MAP_INFLUENCE_PVP_ALL == g_pD3dApp->GetMyShuttleMapInfo()->MapInfluenceType
#endif
		)
		&& (FALSE == bCanSeeInvisible))		// �κ����� �� ��ü�� ���� �ִ� ���³�?
		//--------------------------------------------------------------------------//
#ifndef _DEBUG
		&& !COMPARE_RACE(g_pShuttleChild->m_myShuttleInfo.Race,RACE_OPERATION|RACE_GAMEMASTER)
#endif 
		)	// ������, ���ڴ� ������ ó����
	{// �����ϰ� ���δ�.
		SetUnitAlpha(CL_SKILL_CAMOUFLAGE, SKILL_OBJECT_ALPHA_OTHER_INFLUENCE);
		
		// 2006-11-28 by ispark, Ÿ�� ���� �༮�� ���� �༮�̸�
		if(g_pShuttleChild->m_pOrderTarget == this)
		{
			g_pShuttleChild->SetUnLockOn();
			g_pShuttleChild->m_pTarget = NULL;
			if(g_pShuttleChild->m_pSecondaryWeapon)
			{
				g_pShuttleChild->m_pSecondaryWeapon->DelTargetIndex(m_infoCharacter.CharacterInfo.ClientIndex);
			}
		}
	}
	else
	{// �������ϰ� ���δ�.
		SetUnitAlpha(CL_SKILL_CAMOUFLAGE, SKILL_OBJECT_ALPHA_DEFAULT);
	}

	m_infoCharacter.CharacterRenderInfo.RI_Invisible = TRUE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CEnemyData::InitAlphaData()
/// \brief		
/// \author		ispark
/// \date		2006-11-28 ~ 2006-11-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CEnemyData::InitAlphaData()
{
	SetUnitAlpha(CL_SKILL_NONE, SKILL_OBJECT_ALPHA_NONE);
	m_infoCharacter.CharacterRenderInfo.RI_Invisible = FALSE;
}
///////////////////////////////////////////////////////////////////////////////
/// \fn			ENEMYINFO CEnemyData::GetEnemyInfo()
/// \brief		
/// \author		// 2007-06-13 by bhsohn �޸� ���� �����
/// \date		2007-06-13 ~ 2007-06-13
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
ENEMYINFO CEnemyData::GetEnemyInfo()
{
	return m_infoCharacter;
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-07-14 by bhsohn ĳ���� ���� ���� ����
/// \date		2007-07-14 ~ 2007-07-14
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CEnemyData::IsSameInfluence(BYTE	myInfluenceType, BYTE	emenyInfluenceType)
{
	if(COMPARE_INFLUENCE(myInfluenceType, INFLUENCE_TYPE_NORMAL))
	{// ����������  ��Ƽ �Ϲݱ�
		if(COMPARE_INFLUENCE(emenyInfluenceType, INFLUENCE_TYPE_NORMAL))
		{
			return TRUE;
		}
	}
	if(COMPARE_INFLUENCE(myInfluenceType, INFLUENCE_TYPE_VCN))
	{// ����������  ��Ƽ ���Ա�
		if(COMPARE_INFLUENCE(emenyInfluenceType, INFLUENCE_TYPE_VCN))
		{
			return TRUE;
		}
	}	
	if(COMPARE_INFLUENCE(myInfluenceType, INFLUENCE_TYPE_ANI))
	{// �˸��� ��Ƽ �ݶ���
		if(COMPARE_INFLUENCE(emenyInfluenceType, INFLUENCE_TYPE_ANI))
		{
			return TRUE;
		}
	}
	if(COMPARE_INFLUENCE(myInfluenceType, INFLUENCE_TYPE_RRP))
	{// ��Ż���� ���決
		if(COMPARE_INFLUENCE(emenyInfluenceType, INFLUENCE_TYPE_RRP))
		{
			return TRUE;
		}
	}
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		�� ��ü ��ũ ������ ����
/// \author		// 2008-08-19 by bhsohn ���� ��ũ �ý��� �߰�
/// \date		2008-08-19 ~ 2008-08-19
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CEnemyData::RefreshMarkItem()
{
#ifdef _RAT_FFA
	if (MAP_INFLUENCE_PVP_ALL == g_pD3dApp->GetMyShuttleMapInfo()->MapInfluenceType)
		return;
#endif

	if(m_infoCharacter.CharacterRenderInfo.RI_WingIn)
	{
		// 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����
		//ChangeItemPoint(POS_WINGIN, m_infoCharacter.CharacterRenderInfo.RI_WingIn, 0);
		ChangeItemPoint( POS_WINGIN, m_infoCharacter.CharacterRenderInfo.RI_WingIn, m_infoCharacter.CharacterRenderInfo.RI_WingIn_ShapeItemNum, 0 );
		// end 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����
	}
	
}

// 2013-06-17 by bhsohn ���� ���� ���� ���� ����
BYTE CEnemyData::GetRtnGameUser() 
{
	if(!g_pShuttleChild)
	{
		return 0;
	}
	if(!IsInfluenceCharacter(g_pShuttleChild->m_myShuttleInfo.InfluenceType, m_infoCharacter.CharacterInfo.InfluenceType))
	{
		return 0;
	}
	return m_infoCharacter.CharacterInfo.UsingReturnItem;
}
