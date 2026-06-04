#include "stdafx.h"
#include "INFEvoKillfeed.h"
#include "AtumApplication.h"
#include "D3DHanFont.h"
#include "AtumDefine.h"
#include "ShuttleChild.h"
#include "GameDataLast.h"
#include "INFImageEx.h"
#include "d3dx9core.h"
#include "dxutil.h"

#define ICON_CRASH			"wisopt0"		// Crash Death
#define ICON_CRASH_FUEL		"fuelG01"		// Fuel Death

#define ICON_KILL_PVP		"kill_icon"		// Kill icon PK

#define ICON_BIGBOOM		"xclose1"		// B-Gear BigBoom

#if _RAT_CUSTOM_ICONS
	#define ICON_CRASH			"DeathC"	// Crash Death
	#define ICON_CRASH_FUEL		"DeathF"	// Fuel Death

	#define ICON_KILL_PVE		"DeathN"		// Monster

	#define ICON_DEATH1			"Death1"
	#define ICON_DEATH2			"Death2"
	#define ICON_DEATH3			"Death3"
	#define ICON_DEATH4			"Death4"
#else 
	#define ICON_CRASH			"wisopt0"		// Crash Death
	#define ICON_CRASH_FUEL		"fuelG01"		// Fuel Death
	#define ICON_KILL_PVE		"more_s1"		// Monster
#endif

#define  D3DFVF_KFITEMVERTEX (D3DFVF_XYZRHW  | D3DFVF_TEX1)
struct KillfeedItemVertex
{
	D3DXVECTOR4 p;  
	FLOAT tu, tv;
};

INFEvoKillfeed::INFEvoKillfeed()
{
	m_vecItems.reserve(40);
	
	// 1. Define Anchor Ratios (Top-Right = X: 1.0, Y: 0.0)
	float anchorX = 1.0f;
	float anchorY = 0.0f;

	// 2. Define your exact 1080p pixel offsets
	int offsetX = -300;
	int offsetY = 15;

	// 3. Compute the native position using screen dimensions
	m_kfBeginX = static_cast<int>(g_pApp->GetWidth() * anchorX) + offsetX;
	m_kfBeginY = static_cast<int>(g_pApp->GetHeight() * anchorY) + offsetY;

	m_pFont = nullptr;
	m_pDeathIcon1 = nullptr;
	m_pDeathIcon2 = nullptr;
	m_pDeathIcon3 = nullptr;
	m_pDeathIcon4 = nullptr;
	m_pCrashIcon = nullptr;
	m_pFuelIcon = nullptr;
	m_pMonsterIcon = nullptr;
	m_pBigBoomIcon = nullptr;
}

INFEvoKillfeed::~INFEvoKillfeed()
{
	m_vecItems.clear();
#if _KILL_STREAK
	m_vecKillStreakMsg.clear();
#endif
	SAFE_DELETE(m_pDeathIcon1);
	SAFE_DELETE(m_pDeathIcon2);
	SAFE_DELETE(m_pDeathIcon3);
	SAFE_DELETE(m_pDeathIcon4);
	SAFE_DELETE(m_pCrashIcon);
	SAFE_DELETE(m_pFuelIcon);
	SAFE_DELETE(m_pMonsterIcon);
	SAFE_DELETE(m_pBigBoomIcon);
	SAFE_DELETE(m_pFont);
}

HRESULT INFEvoKillfeed::InitDeviceObjects()
{
	// thanks to Salz_mich_ein for help with the icons
	DataHeader* pDataHeader = NULL;
#if _RAT_CUSTOM_ICONS
	pDataHeader = m_pGameData->Find(ICON_CRASH);
#else
	pDataHeader = m_pGameData->Find(ICON_CRASH);
#endif
	if (pDataHeader)
	{
		m_pCrashIcon = new CINFImageEx;
		m_pCrashIcon->InitDeviceObjects(pDataHeader);
	}
#if _RAT_CUSTOM_ICONS
	pDataHeader = m_pGameData->Find(ICON_CRASH_FUEL);
#else
	pDataHeader = m_pGameData->Find(ICON_CRASH_FUEL);
#endif
	if (pDataHeader)
	{
		m_pFuelIcon = new CINFImageEx;
		m_pFuelIcon->InitDeviceObjects(pDataHeader);
	}
	//////////////////////////////////////////////
#if _RAT_CUSTOM_ICONS
	pDataHeader = m_pGameData->Find(ICON_KILL_PVE);
#else
	pDataHeader = m_pGameData->Find(ICON_KILL_PVE);
#endif
	if (pDataHeader)
	{
		m_pMonsterIcon = new CINFImageEx;
		m_pMonsterIcon->InitDeviceObjects(pDataHeader);
	}
#if _RAT_CUSTOM_ICONS
	pDataHeader = m_pGameData->Find(ICON_DEATH1);
#else
	pDataHeader = m_pGameData->Find(ICON_KILL_PVP);
#endif
	if (pDataHeader)
	{
		m_pDeathIcon1 = new CINFImageEx;
		m_pDeathIcon1->InitDeviceObjects(pDataHeader);
	}
#if _RAT_CUSTOM_ICONS
	pDataHeader = m_pGameData->Find(ICON_DEATH2);
	if (pDataHeader)
	{
		m_pDeathIcon2 = new CINFImageEx;
		m_pDeathIcon2->InitDeviceObjects(pDataHeader);
	}
	pDataHeader = m_pGameData->Find(ICON_DEATH3);
	if (pDataHeader)
	{
		m_pDeathIcon3 = new CINFImageEx;
		m_pDeathIcon3->InitDeviceObjects(pDataHeader);
	}
	pDataHeader = m_pGameData->Find(ICON_DEATH4);
	if (pDataHeader)
	{
		m_pDeathIcon4 = new CINFImageEx;
		m_pDeathIcon4->InitDeviceObjects(pDataHeader);
	}
#endif
	//////////////////////////////////////////////
#if _RAT_CUSTOM_ICONS
	pDataHeader = m_pGameData->Find(ICON_DEATH1);
#else
	pDataHeader = m_pGameData->Find(ICON_BIGBOOM);
#endif
	if (pDataHeader)
	{
		m_pBigBoomIcon = new CINFImageEx;
		m_pBigBoomIcon->InitDeviceObjects(pDataHeader);
	}

	m_pFont = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()), 10, D3DFONT_BOLD, TRUE, 1024, 32);
	m_pFont->InitDeviceObjects(g_pD3dDev);
	m_pFont->RestoreDeviceObjects();
	return S_OK;
}

HRESULT INFEvoKillfeed::RestoreDeviceObjects()
{
	if (m_pDeathIcon1)
		m_pDeathIcon1->RestoreDeviceObjects();

	if (m_pDeathIcon2)
		m_pDeathIcon2->RestoreDeviceObjects();

	if (m_pDeathIcon3)
		m_pDeathIcon3->RestoreDeviceObjects();

	if (m_pDeathIcon4)
		m_pDeathIcon4->RestoreDeviceObjects();
	
	if (m_pCrashIcon)
		m_pCrashIcon->RestoreDeviceObjects();

	if (m_pFuelIcon)
		m_pFuelIcon->RestoreDeviceObjects();

	if (m_pMonsterIcon)
		m_pMonsterIcon->RestoreDeviceObjects();

	if (m_pBigBoomIcon)
		m_pBigBoomIcon->RestoreDeviceObjects();

	m_pFont->RestoreDeviceObjects();

	for (auto& item : m_vecItems)
	{
		item->RestoreDeviceObjects();
	}

#if _KILL_STREAK
	for (auto& ks_item : m_vecKillStreakMsg)
	{
		ks_item->RestoreDeviceObjects();
	}
#endif

	return S_OK;
}

HRESULT INFEvoKillfeed::DeleteDeviceObjects()
{
	if (m_pDeathIcon1)
		m_pDeathIcon1->DeleteDeviceObjects();

	if (m_pDeathIcon2)
		m_pDeathIcon2->DeleteDeviceObjects();

	if (m_pDeathIcon3)
		m_pDeathIcon3->DeleteDeviceObjects();

	if (m_pDeathIcon4)
		m_pDeathIcon4->DeleteDeviceObjects();
	
	if (m_pCrashIcon)
		m_pCrashIcon->DeleteDeviceObjects();

	if (m_pFuelIcon)
		m_pFuelIcon->DeleteDeviceObjects();

	if (m_pMonsterIcon)
		m_pMonsterIcon->DeleteDeviceObjects();

	if (m_pBigBoomIcon)
		m_pBigBoomIcon->DeleteDeviceObjects();

	m_pFont->DeleteDeviceObjects();

	SAFE_DELETE(m_pDeathIcon1);
	SAFE_DELETE(m_pDeathIcon2);
	SAFE_DELETE(m_pDeathIcon3);
	SAFE_DELETE(m_pDeathIcon4);
	SAFE_DELETE(m_pCrashIcon);
	SAFE_DELETE(m_pFuelIcon);
	SAFE_DELETE(m_pMonsterIcon);
	SAFE_DELETE(m_pFont);

	for (auto& item : m_vecItems)
	{
		item->DeleteDeviceObjects();
	}

#if _KILL_STREAK
	for (auto& ks_item : m_vecKillStreakMsg)
	{
		ks_item->DeleteDeviceObjects();
	}
#endif
	return S_OK;
}

HRESULT INFEvoKillfeed::InvalidateDeviceObjects()
{
	if (m_pDeathIcon1)
		m_pDeathIcon1->InvalidateDeviceObjects();

	if (m_pDeathIcon2)
		m_pDeathIcon2->InvalidateDeviceObjects();

	if (m_pDeathIcon3)
		m_pDeathIcon3->InvalidateDeviceObjects();

	if (m_pDeathIcon4)
		m_pDeathIcon4->InvalidateDeviceObjects();

	if (m_pCrashIcon)
		m_pCrashIcon->InvalidateDeviceObjects();

	if (m_pFuelIcon)
		m_pFuelIcon->InvalidateDeviceObjects();

	if (m_pMonsterIcon)
		m_pMonsterIcon->InvalidateDeviceObjects();

	if (m_pBigBoomIcon)
		m_pBigBoomIcon->InvalidateDeviceObjects();

	m_pFont->InvalidateDeviceObjects();

	for (auto& item : m_vecItems)
	{
		item->InvalidateDeviceObjects();
	}
#if _KILL_STREAK
	for (auto& ks_item : m_vecKillStreakMsg)
	{
		ks_item->InvalidateDeviceObjects();
	}
#endif

	return S_OK;
}

void INFEvoKillfeed::Render()
{
#if _RAT_FFA
	// Work in PVP Map Too but Skip Town
	int MapIndex = g_pD3dApp->GetMyShuttleMapInfo()->MapIndex;
	if (IS_CITY_MAP_INDEX(MapIndex) || IS_OUTPOST_CITY_MAP_INDEX(MapIndex))
	{
		return;
	}
#else
	if (MAP_INFLUENCE_PVP_ALL == g_pD3dApp->GetMyShuttleMapInfo()->MapInfluenceType) {
		return;
	}
#endif

	int offset_y = 0;

	// Enable necessary render states for alpha texture blending across the canvas texture
	g_pD3dDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3dDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3dDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	auto rev_iter = m_vecItems.rbegin();
	while (rev_iter != m_vecItems.rend())
	{
		auto item = (*rev_iter).get();
		if (item) {
			item->Move(m_kfBeginX - (item->GetWidth() / 2), m_kfBeginY + offset_y);

			// Dynamically set Direct3D blending factor using the item's current fading alpha
			DWORD itemAlphaFactor = D3DCOLOR_ARGB(item->GetAlpha(), 255, 255, 255);

			// Force the alpha factor into the texture stage color argument pipeline
			g_pD3dDev->SetRenderState(D3DRS_TEXTUREFACTOR, itemAlphaFactor);
			g_pD3dDev->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
			g_pD3dDev->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
			g_pD3dDev->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TFACTOR);

			g_pD3dDev->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
			g_pD3dDev->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
			g_pD3dDev->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TFACTOR);

			// Render the element fading smoothly
			item->Render();

#if _KILL_STREAK
			offset_y += item->GetHeight() + 6;
#else
			offset_y += KFITEM_HEIGHT + KILLFEED_ITEM_SPACING;
#endif
			++rev_iter;
		}
	}

#if _KILL_STREAK
	auto ks_rev_iter = m_vecKillStreakMsg.rbegin();
	while (ks_rev_iter != m_vecKillStreakMsg.rend())
	{
		auto ks_msg = (*ks_rev_iter).get();
		if (ks_msg) {

			// If we have multiple items, and this loop is looking at an OLDER one...
			if (m_vecKillStreakMsg.size() > 1 && ks_rev_iter != m_vecKillStreakMsg.rbegin())
			{
				ks_msg->Set_ShouldRemove();
			}

			ks_msg->Move(g_pD3dApp->GetBackBufferDesc().Width / 2, m_kfBeginY + KFITEM_OFFSET_Y);

			// Dynamically set Direct3D blending factor using the ksmsg's current fading alpha
			DWORD ks_msg_AlphaFactor = D3DCOLOR_ARGB(ks_msg->GetAlpha(), 255, 255, 255);

			// Force the alpha factor into the texture stage color argument pipeline
			g_pD3dDev->SetRenderState(D3DRS_TEXTUREFACTOR, ks_msg_AlphaFactor);
			g_pD3dDev->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
			g_pD3dDev->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
			g_pD3dDev->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TFACTOR);

			g_pD3dDev->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
			g_pD3dDev->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
			g_pD3dDev->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TFACTOR);

			// Render the element fading smoothly
			ks_msg->Render();

			offset_y += ks_msg->GetHeight() + 6;
			++ks_rev_iter;
		}
	}
#endif

	// Restore standard texture behavior states so it doesn't leak into other parts of the UI
	g_pD3dDev->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	g_pD3dDev->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3dDev->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	g_pD3dDev->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
}

void INFEvoKillfeed::Tick()
{
	auto iter = m_vecItems.begin();
	while (iter != m_vecItems.end())
	{
		(*iter)->Tick();

		// Instead of deleting immediately when lifespan expires,
		//    wait until the item has completely faded out to an alpha of 0
		if ((*iter)->ShouldBeRemoved() && (*iter)->GetAlpha() == 0)
		{
			iter = m_vecItems.erase(iter);
		}
		else
		{
			++iter;
		}
	}

#if _KILL_STREAK
	auto ks_iter = m_vecKillStreakMsg.begin();
	while (ks_iter != m_vecKillStreakMsg.end())
	{
		(*ks_iter)->Tick();

		// Instead of deleting immediately when lifespan expires,
		//    wait until the item has completely faded out to an alpha of 0
		if ((*ks_iter)->ShouldBeRemoved() && (*ks_iter)->GetAlpha() == 0 || (*ks_iter)->Get_ForceRemove())
		{
			ks_iter = m_vecKillStreakMsg.erase(ks_iter);
		}
		else
		{
			++ks_iter;
		}
	}
#endif
}

#if _RAT_CUSTOM_ICONS
CINFImageEx* INFEvoKillfeed::GetRandomDeathIcon()
{
	int randomIndex = rand() % 4;

	switch (randomIndex)
	{
	case 0: return m_pDeathIcon1;
	case 1: return m_pDeathIcon2;
	case 2: return m_pDeathIcon3;
	case 3: return m_pDeathIcon4;
	default: return m_pDeathIcon1; // Safe fallback
	}
}
#endif

void INFEvoKillfeed::AddKillFeedItem(MSG_FC_CHARACTER_DEAD_NOTIFY_MAP* msg)
{	
	std::unique_ptr<KillFeedItem> item = std::make_unique<KillFeedItem>(this, msg);
	if (item->RestoreDeviceObjects() == S_OK)
	{
		m_vecItems.push_back(std::move(item));
	}

#if _KILL_STREAK
	if (strcmp(msg->AttackerName, g_pShuttleChild->m_myShuttleInfo.CharacterName) == 0)
	{
		std::unique_ptr<KillStreakMsg> ks_item = std::make_unique<KillStreakMsg>(this, msg);
		if (ks_item->RestoreDeviceObjects() == S_OK)
		{
			m_vecKillStreakMsg.push_back(std::move(ks_item));
		}
	}
#endif
}

KillFeedItem::KillFeedItem(INFEvoKillfeed* parent, MSG_FC_CHARACTER_DEAD_NOTIFY_MAP* msg)
{
	m_initialised = false; 
	m_remove = false;

	if (!parent || !msg)
	{
		m_remove = true;
		return;
	}

	m_pParent = parent;
	m_data = *msg;

	m_createdTime = std::chrono::system_clock::now();
	m_alpha = 255;

	if (strcmp(msg->AttackerName, g_pShuttleChild->m_myShuttleInfo.CharacterName) == 0)
	{
		m_attackerIsMe = true;
		STRNCPY_MEMSET(m_data.AttackerName, "Me",SIZE_MAX_CHARACTER_NAME);
	}
	else
	{
		m_attackerIsMe = false;
	}

	if (strcmp(msg->TargetName, g_pShuttleChild->m_myShuttleInfo.CharacterName) == 0)
	{
		m_targetIsMe = true;
		STRNCPY_MEMSET(m_data.TargetName, "Me",SIZE_MAX_CHARACTER_NAME);
	}
	else
	{
		m_targetIsMe = false;
	}

}

KillFeedItem::~KillFeedItem()
{
	DeleteDeviceObjects();
}

HRESULT KillFeedItem::InitDeviceObjects()
{
	return S_OK;
}

HRESULT KillFeedItem::RestoreDeviceObjects()
{
	if (m_initialised)
	{
		return S_OK;
	}
	short nMMEventHelpMe = 101;
	short nMMEventMarkForm = 102;

	// --- HELPER TO STRIP COLOR CODES FOR ACCURATE MONSTER/NPC TEXT SIZE MEASUREMENT ---
	auto GetCleanStringSize = [this](const char* sourceText) -> SIZE {
		std::string cleanStr = "";
		for (size_t i = 0; sourceText[i] != '\0'; ++i) {
			if (sourceText[i] == '\\' && sourceText[i + 1] != '\0') {
				i++; // Skip the '\' and the color indicator character (e.g., 'c', 'e', 'r')
				continue;
			}
			cleanStr += sourceText[i];
		}
		return m_pParent->GetFont()->GetStringSize(const_cast<char*>(cleanStr.c_str()));
		};

	SIZE attackerstringsize = GetCleanStringSize(m_data.AttackerName);
	SIZE targetstringsize = GetCleanStringSize(m_data.TargetName);
	char szHelpMeMsg[100];

	CINFImageEx* icon = nullptr;

	// --- 1. DETERMINE WHICH ICON WE ARE USING UP FRONT --
#if _RAT_CUSTOM_ICONS
	CINFImageEx* icon2 = nullptr;

	switch (m_data.DamageType)
	{
	case DAMAGE_BY_COLLISION:
	{
		icon = m_pParent->GetPlayerIcon();
		icon2 = m_pParent->GetCrashIcon();
	}
	break;
	case DAMAGE_BY_MONSTER:   icon = m_pParent->GetMonsterIcon(); break;
	case DAMAGE_BY_FUEL_ALLIN:icon = m_pParent->GetFuelIcon(); break;
	case DAMAGE_BY_NA:        icon = m_pParent->GetBigBoomIcon(); break;
	case DAMAGE_BY_PK:        icon = m_pParent->GetRandomDeathIcon(); break;
	}
#else
	CINFImageEx* icon = nullptr;

	switch (m_data.DamageType)
	{
	case DAMAGE_BY_COLLISION: icon = m_pParent->GetCrashIcon(); break;
	case DAMAGE_BY_MONSTER:   icon = m_pParent->GetMonsterIcon(); break;
	case DAMAGE_BY_FUEL_ALLIN:icon = m_pParent->GetFuelIcon(); break;
	case DAMAGE_BY_NA:        icon = m_pParent->GetBigBoomIcon(); break;
	case DAMAGE_BY_PK:        icon = m_pParent->GetPlayerIcon(); break;
	}
#endif

	// --- 2. DYNAMICALLY READ TRUE ICON DIMENSIONS ---
	int realIconWidth = 0;
	int realIconHeight = KFITEM_ICON_HEIGHT;

	int realIconWidth2 = 0;
	int realIconHeight2 = KFITEM_ICON_HEIGHT;

	if (icon)
	{
		realIconWidth = icon->GetImgSize().x;
		if (icon->GetImgSize().y > realIconHeight)
		{
			realIconHeight = icon->GetImgSize().y;
		}
	}

	if (icon2)
	{
		realIconWidth2 = icon2->GetImgSize().x;
		if (icon2->GetImgSize().y > realIconHeight2)
		{
			realIconHeight2 = icon2->GetImgSize().y;
		}
	}

	int iconSpaceAllocation = (realIconWidth > 0) ? (realIconWidth + 6) : 0;
	int iconSpaceAllocation2 = (realIconWidth2 > 0) ? (realIconWidth2 + 6) : 0;

	// --- 3. CALCULATE STREAK PREFIX CONFIGS ---
	char szCombo[32] = { 0 };
	int streakSpaceAllocation = 0;
	char finalStreakMsg[32] = { 0 }; // Replaces the std::string entirely

#if _KILL_STREAK
	// Only render streak prefix layout text if it's an actual active combo streak (> 1)
	if (m_data.DamageType == DAMAGE_BY_PK && m_data.KillStreak > 1)
	{
		const char* colorFlag = "\\y"; // Default color for streaks > 1

		// Must check from highest to lowest!
		if (m_data.KillStreak >= 10)       colorFlag = "\\m"; // Magenta for 10+
		else if (m_data.KillStreak >= 7)   colorFlag = "\\r"; // Red for 7+
		else if (m_data.KillStreak >= 5)   colorFlag = "\\e"; // Orange for 5+

		// This builds: [ColorFlag]x[StreakNumber] -> e.g., "\yx5"
		sprintf(finalStreakMsg, "%sx%i", colorFlag, m_data.KillStreak);

		// Then measure the clean size as usual
		SIZE comboStringSize = m_pParent->GetFont()->GetStringSize(finalStreakMsg);
		streakSpaceAllocation = comboStringSize.cx + 6;
	}
#endif

	// --- 4. SCENARIO CANVAS WIDTH CALCULATION ---
	int width = (2 * KFITEM_TEXT_MARGIN_X);

	switch (m_data.DamageType)
	{
	case DAMAGE_BY_COLLISION:
		// Formatt : [Icon] [Icon] [TargetName]
#if _RAT_CUSTOM_ICONS
		width += iconSpaceAllocation2 + iconSpaceAllocation + targetstringsize.cx;
#else
		// Formatt : [Icon] [TargetName]
		width += iconSpaceAllocation + targetstringsize.cx;
#endif
		break;
	case DAMAGE_BY_FUEL_ALLIN:
		// Format: [Icon] [TargetName]
		width += iconSpaceAllocation + targetstringsize.cx;
		break;
	case DAMAGE_BY_MONSTER:
		// Format: [MonsterName] [Icon] [TargetName]
		width += attackerstringsize.cx + 8 + iconSpaceAllocation + targetstringsize.cx;
		break;
	case DAMAGE_BY_PK:
	case DAMAGE_BY_NA:
		// Format: [KillStreak] [AttackerName] [Icon] [TargetName]
		width += streakSpaceAllocation + attackerstringsize.cx + 16 + iconSpaceAllocation + targetstringsize.cx;
		break;
	default:
		width += attackerstringsize.cx + 8 + iconSpaceAllocation + targetstringsize.cx;
		break;
	}

	int height = realIconHeight + 2 * KFITEM_TEXT_MARGIN_Y;

	if (!SUCCEEDED(g_pD3dDev->CreateTexture(width, height, 0, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pTexture, 0)))
	{
		return S_FALSE;
	}

	if (!SUCCEEDED(m_pTexture->GetSurfaceLevel(0, &m_pSurface)))
	{
		return S_FALSE;
	}

	IDirect3DSurface9* pBackbuffer = nullptr;
	if (!SUCCEEDED(g_pD3dDev->GetRenderTarget(0, &pBackbuffer)))
	{
		return S_FALSE;
	}

	if (!SUCCEEDED(g_pD3dDev->SetRenderTarget(0, m_pSurface)))
	{
		return S_FALSE;
	}

	D3DVIEWPORT9 vp, vp_orig;
	vp.Height = height;
	vp.Width = width;
	vp.X = 0;
	vp.Y = 0;
	vp.MaxZ = 1.0f;
	vp.MinZ = 0.0f;
	g_pD3dDev->GetViewport(&vp_orig);
	g_pD3dDev->SetViewport(&vp);

	DWORD clearColor = (m_attackerIsMe || m_targetIsMe) ? KFITEM_BACKGROUND_COLOR_PLAYER : KFITEM_BACKGROUND_COLOR_NORMAL;
	if (!SUCCEEDED(g_pD3dDev->Clear(0, 0, D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET, clearColor, 1.0f, 0)))
	{
		return S_FALSE;
	}

	BYTE myInfluence = g_pShuttleChild->m_myShuttleInfo.InfluenceType;
	DWORD attackercolor;
	DWORD targetcolor;

#if _KILL_FEED_INF_COLORS
	if (!m_attackerIsMe)
	{
		if (m_data.AttackerInfluence == INFLUENCE_TYPE_ANI)			attackercolor = KFITEM_TEXT_COLOR_ANI;
		else if (m_data.AttackerInfluence == INFLUENCE_TYPE_VCN)		attackercolor = KFITEM_TEXT_COLOR_BCU;
		else if (m_data.AttackerInfluence == INFLUENCE_TYPE_RRP)		attackercolor = KFITEM_TEXT_COLOR_ENEMY;
		else														attackercolor = KFITEM_TEXT_COLOR_ALL;
	}
	else
	{
		attackercolor = COLOR_PARTY;
	}

	if (!m_targetIsMe)
	{
		if (m_data.TargetInfluence == INFLUENCE_TYPE_ANI)			targetcolor = KFITEM_TEXT_COLOR_ANI;
		else if (m_data.TargetInfluence == INFLUENCE_TYPE_VCN)		targetcolor = KFITEM_TEXT_COLOR_BCU;
		else if (m_data.TargetInfluence == INFLUENCE_TYPE_RRP)		targetcolor = KFITEM_TEXT_COLOR_ENEMY;
		else														targetcolor = KFITEM_TEXT_COLOR_ALL;
	}
	else
	{
		targetcolor = COLOR_PARTY;
	}
#else
	attackercolor = m_attackerIsMe ? KFITEM_TEXT_COLOR_ME : ((myInfluence == m_data.PlayerInfluence) ? KFITEM_TEXT_COLOR_ALLY : KFITEM_TEXT_COLOR_ENEMY);
	targetcolor = m_targetIsMe ? KFITEM_TEXT_COLOR_ME : ((myInfluence == m_data.EnemyInfluence) ? KFITEM_TEXT_COLOR_ALLY : KFITEM_TEXT_COLOR_ENEMY);
#endif

	int text_offset_y = static_cast<int>(static_cast<float>(height - attackerstringsize.cy) / 2 - 0.5f);
	int current_render_x = KFITEM_TEXT_MARGIN_X;

	// --- 5. RENDER CASES ---
	switch (m_data.DamageType)
	{
	case DAMAGE_BY_COLLISION:
	{
#if _RAT_CUSTOM_ICONS
		// Format: [Icon] [Icon] [TargetName]
		if (icon2)
		{
			icon2->Move(current_render_x, KFITEM_TEXT_MARGIN_Y);
			icon2->SetScale(1.0f, 1.0f);
			icon2->Render();
			current_render_x += iconSpaceAllocation2;
		}
#endif
		// Format: [Icon] [TargetName]
		if (icon)
		{
			icon->Move(current_render_x, KFITEM_TEXT_MARGIN_Y);
			icon->SetScale(1.0f, 1.0f);
			icon->Render();
			current_render_x += iconSpaceAllocation;
		}

		m_pParent->GetFont()->DrawTextA(current_render_x, text_offset_y - 4, targetcolor, m_data.TargetName, 0);
	}
	break;

	case DAMAGE_BY_FUEL_ALLIN:
	{
		// Format: [Icon] [TargetName]
		if (icon)
		{
			icon->Move(current_render_x, KFITEM_TEXT_MARGIN_Y);
			icon->SetScale(1.0f, 1.0f);
			icon->Render();
			current_render_x += iconSpaceAllocation;
		}

		m_pParent->GetFont()->DrawTextA(current_render_x, text_offset_y - 4, targetcolor, m_data.TargetName, 0);
	}
	break;

	case DAMAGE_BY_MONSTER:
	{
		// Format: [MonsterName] [Icon] [TargetName]
		m_pParent->GetFont()->DrawTextA(current_render_x, text_offset_y - 4, attackercolor, m_data.AttackerName, 0);
		current_render_x += attackerstringsize.cx + 8; // Draw normally, then add 10px spacing before the icon

		if (icon)
		{
			icon->Move(current_render_x, KFITEM_TEXT_MARGIN_Y);
			icon->SetScale(1.0f, 1.0f);
			icon->Render();
			current_render_x += iconSpaceAllocation;
		}

		m_pParent->GetFont()->DrawTextA(current_render_x, text_offset_y - 4, targetcolor, m_data.TargetName, 0);
	}
	break;

	case DAMAGE_BY_PK:
	case DAMAGE_BY_NA:
	{
		// Format: [KillStreak] [AttackerName] [Icon] [TargetName]
#if _KILL_STREAK
		if (finalStreakMsg[0] != '\0')
		{
			m_pParent->GetFont()->DrawTextA(current_render_x, text_offset_y - 4, attackercolor, finalStreakMsg, 0);
			current_render_x += streakSpaceAllocation;
		}
#endif
		m_pParent->GetFont()->DrawTextA(current_render_x, text_offset_y - 4, attackercolor, m_data.AttackerName, 0);
		current_render_x += attackerstringsize.cx + 8; // Draw normally, then add 10px spacing before the icon

		if (icon)
		{
			icon->Move(current_render_x, KFITEM_TEXT_MARGIN_Y);
			icon->SetScale(1.0f, 1.0f);
			icon->Render();
			current_render_x += iconSpaceAllocation;
		}

		m_pParent->GetFont()->DrawTextA(current_render_x, text_offset_y - 4, targetcolor, m_data.TargetName, 0);
	}
	break;

	default:
	{
		// Generic system fallback sequence
		// Format: [AttackerName] [Icon] [TargetName]
		m_pParent->GetFont()->DrawTextA(current_render_x, text_offset_y - 4, attackercolor, m_data.AttackerName, 0);
		current_render_x += attackerstringsize.cx + 8; // Draw normally, then add 10px spacing before the icon

		if (icon)
		{
			icon->Move(current_render_x, KFITEM_TEXT_MARGIN_Y);
			icon->SetScale(1.0f, 1.0f);
			icon->Render();
			current_render_x += iconSpaceAllocation;
		}

		m_pParent->GetFont()->DrawTextA(current_render_x, text_offset_y - 4, targetcolor, m_data.TargetName, 0);
	}
	break;
	}

	g_pD3dDev->SetViewport(&vp_orig);
	if (!SUCCEEDED(g_pD3dDev->SetRenderTarget(0, pBackbuffer)))
	{
		return S_FALSE;
	}
	pBackbuffer->Release();

	if (!SUCCEEDED(g_pD3dDev->CreateVertexBuffer(6 * sizeof(KillfeedItemVertex), D3DUSAGE_WRITEONLY, D3DFVF_KFITEMVERTEX, D3DPOOL_MANAGED, &m_pVB, NULL)))
	{
		return S_FALSE;
	}

	m_coordinates.left = 0;
	m_coordinates.right = width;
	m_coordinates.top = 0;
	m_coordinates.bottom = height;
	m_initialised = true;
	return S_OK;
}

HRESULT KillFeedItem::DeleteDeviceObjects()
{
	SAFE_RELEASE(m_pVB);
	SAFE_RELEASE(m_pSurface);
	SAFE_RELEASE(m_pTexture);
	m_initialised = false;
	return S_OK;
}

HRESULT KillFeedItem::InvalidateDeviceObjects()
{
	SAFE_RELEASE(m_pVB);
	SAFE_RELEASE(m_pSurface);
	SAFE_RELEASE(m_pTexture);
	m_initialised = false;
	return S_OK;
}

void KillFeedItem::Render()
{
	if (m_remove || !m_initialised)
	{
		return;
	}

	g_pD3dDev->SetTexture(0, m_pTexture);
	g_pD3dDev->SetStreamSource(0, m_pVB, 0, sizeof(KillfeedItemVertex));
	g_pD3dDev->SetFVF(D3DFVF_KFITEMVERTEX);

	g_pD3dDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3dDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3dDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	g_pD3dDev->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3dDev->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

	// Multiplies the color channel by alpha factor to handle smooth rendering fadeout steps cleanly
	g_pD3dDev->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3dDev->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	g_pD3dDev->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TFACTOR);

	g_pD3dDev->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TFACTOR);
	g_pD3dDev->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	DWORD factor = D3DCOLOR_ARGB(m_alpha, m_alpha, m_alpha, m_alpha);
	g_pD3dDev->SetRenderState(D3DRS_TEXTUREFACTOR, factor);

	g_pD3dDev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
}

void KillFeedItem::Tick()
{
	if (m_remove)
	{
		return;
	}

	auto now = std::chrono::system_clock::now();
	auto deltaTime = now - m_createdTime;

	if (deltaTime >= KFITEM_LIFETIME)
	{
		m_remove = true;
	}
	else
	{
		// Default fully visible state
		m_alpha = 255;

		// Calculate fade-out when entering the last segment of item life
		if (deltaTime > KFITEM_LIFETIME - KFITEM_FADEOUT_TIME)
		{
			auto fadeTime = std::chrono::duration_cast<std::chrono::milliseconds>(deltaTime) -
				std::chrono::milliseconds(KFITEM_LIFETIME - KFITEM_FADEOUT_TIME);

			long long elapsedMs = fadeTime.count();
			long long maxFadeMs = std::chrono::duration_cast<std::chrono::milliseconds>(KFITEM_FADEOUT_TIME).count();

			if (elapsedMs < maxFadeMs)
			{
				m_alpha = static_cast<byte>(255 - (elapsedMs * 255 / maxFadeMs));
			}
			else
			{
				m_alpha = 0;
			}
		}
	}
}

void KillFeedItem::Move(int x, int y)
{
	if (m_remove)
	{
		return;
	}

	if (x != m_coordinates.left || y != m_coordinates.top)
	{
		UpdateVertexBuffer(x, y);
	}
}

void KillFeedItem::UpdateVertexBuffer(int x, int y)
{
	int width = GetWidth();
	int height = GetHeight();

	KillfeedItemVertex* vertices;
	HRESULT hr = 0;
	if (SUCCEEDED(m_pVB->Lock(0, 0, reinterpret_cast<void**>(&vertices), 0)))
	{
		vertices[0] = KillfeedItemVertex{ D3DXVECTOR4(x - 0.5f, y + height - 0.5f, 0.9f, 1.0f), 0.0f, 1.0f };
		vertices[1] = KillfeedItemVertex{ D3DXVECTOR4(x - 0.5f, y - 0.5f, 0.9f, 1.0f), 0.0f, 0.0f };
		vertices[2] = KillfeedItemVertex{ D3DXVECTOR4(x + width - 0.5f, y - 0.5f, 0.9f, 1.0f), 1.0f, 0.0f };
		vertices[3] = KillfeedItemVertex{ D3DXVECTOR4(x - 0.5f, y + height - 0.5f, 0.9f, 1.0f), 0.0f, 1.0f };
		vertices[4] = KillfeedItemVertex{ D3DXVECTOR4(x + width - 0.5f, y - 0.5f, 0.9f, 1.0f), 1.0f, 0.0f };
		vertices[5] = KillfeedItemVertex{ D3DXVECTOR4(x + width - 0.5f, y + height - 0.5f, 0.9f, 1.0f), 1.0f, 1.0f };
		m_pVB->Unlock();
	}

	m_coordinates.right = x + width;
	m_coordinates.left = x;
	m_coordinates.bottom = y + height;
	m_coordinates.top = y;
}

#if _KILL_STREAK
KillStreakMsg::KillStreakMsg(INFEvoKillfeed* parent, MSG_FC_CHARACTER_DEAD_NOTIFY_MAP* msg)
{
	m_initialised = false;
	m_remove = false;
	m_forceremove = false;

	if (!parent || !msg)
	{
		m_remove = true;
		return;
	}

	m_pParent = parent;
	m_data = *msg;

	m_createdTime = std::chrono::system_clock::now();
	m_alpha = 255;

}

KillStreakMsg::~KillStreakMsg()
{
	DeleteDeviceObjects();
}

HRESULT KillStreakMsg::InitDeviceObjects()
{
	return S_OK;
}

HRESULT KillStreakMsg::RestoreDeviceObjects()
{
	if (m_initialised)
	{
		return S_OK;
	}

	// --- 1. DETERMINE WHICH ICON WE ARE USING ---
	CINFImageEx* icon = nullptr;
	switch (m_data.DamageType)
	{
	case DAMAGE_BY_NA:        icon = m_pParent->GetBigBoomIcon(); break;
	case DAMAGE_BY_PK:        icon = m_pParent->GetPlayerIcon(); break;
	}

	// --- 2. CANVAS SIZE (ICON ONLY, NO TEXT MARGINS) ---
	int width = KFITEM_ICON_WIDTH;
	int height = KFITEM_ICON_HEIGHT;

	if (icon)
	{
		width = icon->GetImgSize().x;
		height = icon->GetImgSize().y;
	}

	if (!SUCCEEDED(g_pD3dDev->CreateTexture(width, height, 0, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pTexture, 0)))
	{
		return S_FALSE;
	}

	if (!SUCCEEDED(m_pTexture->GetSurfaceLevel(0, &m_pSurface)))
	{
		return S_FALSE;
	}

	IDirect3DSurface9* pBackbuffer = nullptr;
	if (!SUCCEEDED(g_pD3dDev->GetRenderTarget(0, &pBackbuffer)))
	{
		return S_FALSE;
	}

	if (!SUCCEEDED(g_pD3dDev->SetRenderTarget(0, m_pSurface)))
	{
		return S_FALSE;
	}

	D3DVIEWPORT9 vp, vp_orig;
	vp.Height = height;
	vp.Width = width;
	vp.X = 0;
	vp.Y = 0;
	vp.MaxZ = 1.0f;
	vp.MinZ = 0.0f;
	g_pD3dDev->GetViewport(&vp_orig);
	g_pD3dDev->SetViewport(&vp);

	// CRITICAL FIX: Removed D3DCLEAR_ZBUFFER so it doesn't silently fail and abort the function.
	// Clears the texture background to fully transparent.
	if (!SUCCEEDED(g_pD3dDev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0)))
	{
		return S_FALSE;
	}

	// --- 3. RENDER ONLY THE ICON INTO THE TEXTURE ---
	switch (m_data.DamageType)
	{
	case DAMAGE_BY_NA:
	case DAMAGE_BY_PK:
		{
			if (icon)
			{
				icon->Move(0, 0);
				icon->SetScale(1.0f, 1.0f);
				icon->Render();
			}
			break;
		}
	}

	g_pD3dDev->SetViewport(&vp_orig);
	if (!SUCCEEDED(g_pD3dDev->SetRenderTarget(0, pBackbuffer)))
	{
		return S_FALSE;
	}
	pBackbuffer->Release();

	if (!SUCCEEDED(g_pD3dDev->CreateVertexBuffer(6 * sizeof(KillfeedItemVertex), D3DUSAGE_WRITEONLY, D3DFVF_KFITEMVERTEX, D3DPOOL_MANAGED, &m_pVB, NULL)))
	{
		return S_FALSE;
	}

	// --- 4. FORCE MIDDLE OF SCREEN COORDINATES ---
	int screenWidth = g_pD3dApp->GetBackBufferDesc().Width;

	// Locks the bounding box directly to the upper-middle of the screen
	m_coordinates.left = (screenWidth / 2) - (width / 2);
	m_coordinates.right = m_coordinates.left + width;
	m_coordinates.top = 50; // Set this to (g_pD3dApp->GetBackBufferDesc().Height / 2) if you want dead center vertically
	m_coordinates.bottom = m_coordinates.top + height;

	m_initialised = true;
	return S_OK;
}

HRESULT KillStreakMsg::DeleteDeviceObjects()
{
	SAFE_RELEASE(m_pVB);
	SAFE_RELEASE(m_pSurface);
	SAFE_RELEASE(m_pTexture);
	m_initialised = false;
	return S_OK;
}

HRESULT KillStreakMsg::InvalidateDeviceObjects()
{
	SAFE_RELEASE(m_pVB);
	SAFE_RELEASE(m_pSurface);
	SAFE_RELEASE(m_pTexture);
	m_initialised = false;
	return S_OK;
}

void KillStreakMsg::Render()
{
	if (m_remove || m_forceremove ||  !m_initialised)
	{
		return;
	}

	g_pD3dDev->SetTexture(0, m_pTexture);
	g_pD3dDev->SetStreamSource(0, m_pVB, 0, sizeof(KillfeedItemVertex));
	g_pD3dDev->SetFVF(D3DFVF_KFITEMVERTEX);

	g_pD3dDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3dDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3dDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	g_pD3dDev->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3dDev->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

	// Multiplies the color channel by alpha factor to handle smooth rendering fadeout steps cleanly
	g_pD3dDev->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3dDev->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	g_pD3dDev->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TFACTOR);

	g_pD3dDev->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TFACTOR);
	g_pD3dDev->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	DWORD factor = D3DCOLOR_ARGB(m_alpha, m_alpha, m_alpha, m_alpha);
	g_pD3dDev->SetRenderState(D3DRS_TEXTUREFACTOR, factor);

	g_pD3dDev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
}

void KillStreakMsg::Tick()
{
	if (m_remove || m_forceremove)
	{
		return;
	}

	auto now = std::chrono::system_clock::now();
	auto deltaTime = now - m_createdTime;

	if (deltaTime >= KFITEM_LIFETIME_KS)
	{
		m_remove = true;
	}
	else
	{
		// Default fully visible state
		m_alpha = 255;

		// Calculate fade-out when entering the last segment of item life
		if (deltaTime > KFITEM_LIFETIME_KS - KFITEM_FADEOUT_TIME_KS)
		{
			auto fadeTime = std::chrono::duration_cast<std::chrono::milliseconds>(deltaTime) -
				std::chrono::milliseconds(KFITEM_LIFETIME_KS - KFITEM_FADEOUT_TIME_KS);

			long long elapsedMs = fadeTime.count();
			long long maxFadeMs = std::chrono::duration_cast<std::chrono::milliseconds>(KFITEM_FADEOUT_TIME_KS).count();

			if (elapsedMs < maxFadeMs)
			{
				m_alpha = static_cast<byte>(255 - (elapsedMs * 255 / maxFadeMs));
			}
			else
			{
				m_alpha = 0;
			}
		}
	}
}

void KillStreakMsg::Move(int x, int y)
{
	if (m_remove || m_forceremove)
	{
		return;
	}

	if (x != m_coordinates.left || y != m_coordinates.top)
	{
		UpdateVertexBuffer(x, y);
	}
}

void KillStreakMsg::UpdateVertexBuffer(int x, int y)
{
	int width = GetWidth();
	int height = GetHeight();

	KillfeedItemVertex* vertices;
	HRESULT hr = 0;
	if (SUCCEEDED(m_pVB->Lock(0, 0, reinterpret_cast<void**>(&vertices), 0)))
	{
		vertices[0] = KillfeedItemVertex{ D3DXVECTOR4(x - 0.5f, y + height - 0.5f, 0.9f, 1.0f), 0.0f, 1.0f };
		vertices[1] = KillfeedItemVertex{ D3DXVECTOR4(x - 0.5f, y - 0.5f, 0.9f, 1.0f), 0.0f, 0.0f };
		vertices[2] = KillfeedItemVertex{ D3DXVECTOR4(x + width - 0.5f, y - 0.5f, 0.9f, 1.0f), 1.0f, 0.0f };
		vertices[3] = KillfeedItemVertex{ D3DXVECTOR4(x - 0.5f, y + height - 0.5f, 0.9f, 1.0f), 0.0f, 1.0f };
		vertices[4] = KillfeedItemVertex{ D3DXVECTOR4(x + width - 0.5f, y - 0.5f, 0.9f, 1.0f), 1.0f, 0.0f };
		vertices[5] = KillfeedItemVertex{ D3DXVECTOR4(x + width - 0.5f, y + height - 0.5f, 0.9f, 1.0f), 1.0f, 1.0f };
		m_pVB->Unlock();
	}

	m_coordinates.right = x + width;
	m_coordinates.left = x;
	m_coordinates.bottom = y + height;
	m_coordinates.top = y;
}
#endif