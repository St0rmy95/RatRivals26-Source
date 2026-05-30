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

#define ICON_KILL_PVE		"more_s1"		// Monster
#define ICON_KILL_PVP		"kill_icon"		// Kill icon PK

#define ICON_BIGBOOM		"xclose1"		// B-Gear BigBoom

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
	m_pMissleIcon = nullptr;
	m_pCrashIcon = nullptr;
	m_pFuelIcon = nullptr;
	m_pMonsterIcon = nullptr;
	m_pBigBoomIcon = nullptr;
}

INFEvoKillfeed::~INFEvoKillfeed()
{
	m_vecItems.clear();
	SAFE_DELETE(m_pMissleIcon);
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
	pDataHeader = m_pGameData->Find(ICON_CRASH);
	if (pDataHeader)
	{
		m_pCrashIcon = new CINFImageEx;
		m_pCrashIcon->InitDeviceObjects(pDataHeader);
	}
	pDataHeader = m_pGameData->Find(ICON_CRASH_FUEL);
	if (pDataHeader)
	{
		m_pFuelIcon = new CINFImageEx;
		m_pFuelIcon->InitDeviceObjects(pDataHeader);
	}
	//////////////////////////////////////////////
	pDataHeader = m_pGameData->Find(ICON_KILL_PVE);
	if (pDataHeader)
	{
		m_pMonsterIcon = new CINFImageEx;
		m_pMonsterIcon->InitDeviceObjects(pDataHeader);
	}
	pDataHeader = m_pGameData->Find(ICON_KILL_PVP);
	if (pDataHeader)
	{
		m_pMissleIcon = new CINFImageEx;
		m_pMissleIcon->InitDeviceObjects(pDataHeader);
	}
	//////////////////////////////////////////////
	pDataHeader = m_pGameData->Find(ICON_BIGBOOM);
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
	if (m_pMissleIcon)
		m_pMissleIcon->RestoreDeviceObjects();

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

	return S_OK;
}

HRESULT INFEvoKillfeed::DeleteDeviceObjects()
{
	if (m_pMissleIcon)
		m_pMissleIcon->DeleteDeviceObjects();

	if (m_pCrashIcon)
		m_pCrashIcon->DeleteDeviceObjects();

	if (m_pFuelIcon)
		m_pFuelIcon->DeleteDeviceObjects();

	if (m_pMonsterIcon)
		m_pMonsterIcon->DeleteDeviceObjects();

	if (m_pBigBoomIcon)
		m_pBigBoomIcon->DeleteDeviceObjects();

	m_pFont->DeleteDeviceObjects();

	SAFE_DELETE(m_pMissleIcon);
	SAFE_DELETE(m_pCrashIcon);
	SAFE_DELETE(m_pFuelIcon);
	SAFE_DELETE(m_pMonsterIcon);
	SAFE_DELETE(m_pFont);

	for (auto& item : m_vecItems)
	{
		item->DeleteDeviceObjects();
	}

	return S_OK;
}

HRESULT INFEvoKillfeed::InvalidateDeviceObjects()
{
	if (m_pMissleIcon)
		m_pMissleIcon->InvalidateDeviceObjects();

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
}

void INFEvoKillfeed::AddKillFeedItem(MSG_FC_CHARACTER_DEAD_NOTIFY_MAP* msg)
{	
	std::unique_ptr<KillFeedItem> item = std::make_unique<KillFeedItem>(this, msg);
	if (item->RestoreDeviceObjects() == S_OK)
	{
		m_vecItems.push_back(std::move(item));
	}
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

	if (strcmp(msg->PlayerName, g_pShuttleChild->m_myShuttleInfo.CharacterName) == 0)
	{
		m_attackerIsMe = true;
		STRNCPY_MEMSET(m_data.PlayerName, "Me",SIZE_MAX_CHARACTER_NAME);
	}
	else
	{
		m_attackerIsMe = false;
	}

	if (strcmp(msg->EnemyName, g_pShuttleChild->m_myShuttleInfo.CharacterName) == 0)
	{
		m_targetIsMe = true;
		STRNCPY_MEMSET(m_data.EnemyName, "Me",SIZE_MAX_CHARACTER_NAME);
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

	SIZE attackerstringsize = GetCleanStringSize(m_data.PlayerName);
	SIZE targetstringsize = GetCleanStringSize(m_data.EnemyName);
	char szHelpMeMsg[100];

	// --- 1. DETERMINE WHICH ICON WE ARE USING UP FRONT ---
	CINFImageEx* icon = nullptr;
	switch (m_data.DamageType)
	{
	case DAMAGE_BY_COLLISION: icon = m_pParent->GetCrashIcon(); break;
	case DAMAGE_BY_MONSTER:   icon = m_pParent->GetMonsterIcon(); break;
	case DAMAGE_BY_FUEL_ALLIN:icon = m_pParent->GetFuelIcon(); break;
	case DAMAGE_BY_NA:        icon = m_pParent->GetBigBoomIcon(); break;
	case DAMAGE_BY_PK:        icon = m_pParent->GetPlayerIcon(); break;
	}

	// --- 2. DYNAMICALLY READ TRUE ICON DIMENSIONS ---
	int realIconWidth = 0;
	int realIconHeight = KFITEM_ICON_HEIGHT;

	if (icon)
	{
		realIconWidth = icon->GetImgSize().x;
		if (icon->GetImgSize().y > realIconHeight)
		{
			realIconHeight = icon->GetImgSize().y;
		}
	}

	int iconSpaceAllocation = (realIconWidth > 0) ? (realIconWidth + 6) : 0;

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
	case DAMAGE_BY_FUEL_ALLIN:
		// Format: [Icon] [PlayerName]
		width += iconSpaceAllocation + attackerstringsize.cx;
		break;

	case DAMAGE_BY_MONSTER:
		// Format: [Me/TargetName] [Icon] [MonsterName]
		width += targetstringsize.cx + iconSpaceAllocation + attackerstringsize.cx;
		break;

	case DAMAGE_BY_PK:
	case DAMAGE_BY_NA:
		// Format: [KillStreak] [PlayerName] [Icon] [EnemyName]
		width += streakSpaceAllocation + attackerstringsize.cx + iconSpaceAllocation + targetstringsize.cx;
		break;

	default:
		width += attackerstringsize.cx + iconSpaceAllocation + targetstringsize.cx;
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
		if (m_data.PlayerInfluence == INFLUENCE_TYPE_ANI)			attackercolor = KFITEM_TEXT_COLOR_ANI;
		else if (m_data.PlayerInfluence == INFLUENCE_TYPE_VCN)		attackercolor = KFITEM_TEXT_COLOR_BCU;
		else if (m_data.PlayerInfluence == INFLUENCE_TYPE_RRP)		attackercolor = KFITEM_TEXT_COLOR_ENEMY;
		else														attackercolor = KFITEM_TEXT_COLOR_ALL;
	}
	else
	{
		attackercolor = COLOR_PARTY;
	}

	if (!m_targetIsMe)
	{
		if (m_data.EnemyInfluence == INFLUENCE_TYPE_ANI)			targetcolor = KFITEM_TEXT_COLOR_ANI;
		else if (m_data.EnemyInfluence == INFLUENCE_TYPE_VCN)		targetcolor = KFITEM_TEXT_COLOR_BCU;
		else if (m_data.EnemyInfluence == INFLUENCE_TYPE_RRP)		targetcolor = KFITEM_TEXT_COLOR_ENEMY;
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
	case DAMAGE_BY_FUEL_ALLIN:
	{
		// Format: [Icon] [PlayerName]
		if (icon)
		{
			icon->Move(current_render_x, KFITEM_TEXT_MARGIN_Y);
			icon->SetScale(1.0f, 1.0f);
			icon->Render();
			current_render_x += iconSpaceAllocation;
		}

		m_pParent->GetFont()->DrawTextA(current_render_x, text_offset_y - 4, attackercolor, m_data.PlayerName, 0);
	}
	break;

	case DAMAGE_BY_MONSTER:
	{
		// Format: [Me / TargetName] [Icon] [MonsterName]
		m_pParent->GetFont()->DrawTextA(current_render_x, text_offset_y - 4, targetcolor, m_data.EnemyName, 0);
		current_render_x += targetstringsize.cx;

		if (icon)
		{
			icon->Move(current_render_x + 2, KFITEM_TEXT_MARGIN_Y);
			icon->SetScale(1.0f, 1.0f);
			icon->Render();
			current_render_x += iconSpaceAllocation;
		}

		m_pParent->GetFont()->DrawTextA(current_render_x, text_offset_y - 4, attackercolor, m_data.PlayerName, 0);
	}
	break;

	case DAMAGE_BY_PK:
	case DAMAGE_BY_NA:
	{
		// Format: [KillStreak] [PlayerName] [Icon] [EnemyName]
#if _KILL_STREAK
		if (finalStreakMsg[0] != '\0')
		{
			// Much cleaner! Just drop 'finalStreakMsg' right in.
			m_pParent->GetFont()->DrawTextA(current_render_x, text_offset_y - 4, attackercolor, finalStreakMsg, 0);
			current_render_x += streakSpaceAllocation;
		}
#endif
		m_pParent->GetFont()->DrawTextA(current_render_x, text_offset_y - 4, attackercolor, m_data.PlayerName, 0);
		current_render_x += attackerstringsize.cx;

		if (icon)
		{
			icon->Move(current_render_x + 2, KFITEM_TEXT_MARGIN_Y);
			icon->SetScale(1.0f, 1.0f);
			icon->Render();
			current_render_x += iconSpaceAllocation;
		}

		m_pParent->GetFont()->DrawTextA(current_render_x, text_offset_y - 4, targetcolor, m_data.EnemyName, 0);
	}
	break;

	default:
	{
		// Generic system fallback sequence
		m_pParent->GetFont()->DrawTextA(current_render_x, text_offset_y - 4, attackercolor, m_data.PlayerName, 0);
		current_render_x += attackerstringsize.cx;

		if (icon)
		{
			icon->Move(current_render_x + 2, KFITEM_TEXT_MARGIN_Y);
			icon->SetScale(1.0f, 1.0f);
			icon->Render();
			current_render_x += iconSpaceAllocation;
		}

		m_pParent->GetFont()->DrawTextA(current_render_x, text_offset_y - 4, targetcolor, m_data.EnemyName, 0);
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