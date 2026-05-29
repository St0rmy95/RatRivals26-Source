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


#define  D3DFVF_KFITEMVERTEX (D3DFVF_XYZRHW  | D3DFVF_TEX1)
struct KillfeedItemVertex
{
	D3DXVECTOR4 p;  
	FLOAT tu, tv;
};

INFEvoKillfeed::INFEvoKillfeed()
{
	m_vecItems.reserve(40);
	
	m_kfBeginX = g_pApp->GetWidth() - 230;
	m_kfBeginY = 200;

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
	pDataHeader = m_pGameData->Find("kill_icon");
	if (pDataHeader)
	{
		m_pMissleIcon = new CINFImageEx;
		m_pMissleIcon->InitDeviceObjects(pDataHeader);
	}
	pDataHeader = m_pGameData->Find("wisopt0");
	if (pDataHeader)
	{
		m_pCrashIcon = new CINFImageEx;
		m_pCrashIcon->InitDeviceObjects(pDataHeader);
	}
	pDataHeader = m_pGameData->Find("fuelG01");
	if (pDataHeader)
	{
		m_pFuelIcon = new CINFImageEx;
		m_pFuelIcon->InitDeviceObjects(pDataHeader);
	}
	pDataHeader = m_pGameData->Find("more_s1");
	if (pDataHeader)
	{
		m_pMonsterIcon = new CINFImageEx;
		m_pMonsterIcon->InitDeviceObjects(pDataHeader);
	}

	pDataHeader = m_pGameData->Find("xclose1");
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
			item->Move(m_kfBeginX - item->GetWidth(), m_kfBeginY + offset_y);

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

#if _KILL_STREAK
	// Capture the killstreak value from the server's network packet
	m_killStreak = msg->KillStreak;
#endif
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
	SIZE attackerstringsize = m_pParent->GetFont()->GetStringSize(m_data.PlayerName);
	SIZE targetstringsize = m_pParent->GetFont()->GetStringSize(m_data.EnemyName);
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
	int realIconHeight = KFITEM_ICON_HEIGHT; // Fallback to header definition

	if (icon)
	{
		realIconWidth = icon->GetImgSize().x;

		if (icon->GetImgSize().y > realIconHeight)
		{
			realIconHeight = icon->GetImgSize().y;
		}
	}

	// Add a little breathing room padding around the icon if it exists
	int iconSpaceAllocation = (realIconWidth > 0) ? (realIconWidth + 10) : 0;

#if _KILL_STREAK
	// ----------------------------------------------------
	// ADVANCED MULTI-KILL COMBO CONFIGURATION
	// ----------------------------------------------------
	int baseRowHeight = realIconHeight + 2 * KFITEM_TEXT_MARGIN_Y;

	// Dynamic Width Row 1: Left Margin + Attacker Text + Calculated Icon Width Space + Target Text + Right Margin
	int widthRow1 = KFITEM_TEXT_MARGIN_X + iconSpaceAllocation + targetstringsize.cx + KFITEM_TEXT_MARGIN_X;
	if (m_data.DamageType == DAMAGE_BY_PK)
	{
		widthRow1 += attackerstringsize.cx;
	}

	int widthRow2 = 0;
	int height = baseRowHeight;
	char szCombo[32] = { 0 };

	if (m_data.DamageType == DAMAGE_BY_PK && m_killStreak > 1)
	{
		sprintf(szCombo, "x%i", m_killStreak);
		string fullStreakString = string(m_data.PlayerName) + " " + szCombo;
		SIZE streakStringSize = m_pParent->GetFont()->GetStringSize(const_cast<char*>(fullStreakString.c_str()));

		widthRow2 = streakStringSize.cx + (2 * KFITEM_TEXT_MARGIN_X);
		height = baseRowHeight * 2;
	}

	// Canvas wrapper matches the exact dimension of the longest row cleanly
	int width = (widthRow2 > widthRow1) ? widthRow2 : widthRow1;
#else
	// ----------------------------------------------------
	// ORIGINAL 1-ROW NATIVE RENDERING BLUEPRINT
	// ----------------------------------------------------
	int width = targetstringsize.cx + realIconWidth + 4 + 2 * KFITEM_TEXT_MARGIN_X;
	width += (m_data.DamageType == DAMAGE_BY_PK) ? attackerstringsize.cx + 4 : 0;
	int height = realIconHeight + 2 * KFITEM_TEXT_MARGIN_Y;
#endif

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
	DWORD attackercolor = m_attackerIsMe ? KFITEM_TEXT_COLOR_ME : ((myInfluence == m_data.PlayerInfluence) ? KFITEM_TEXT_COLOR_ALLY : KFITEM_TEXT_COLOR_ENEMY);
	DWORD targetcolor = m_targetIsMe ? KFITEM_TEXT_COLOR_ME : ((myInfluence == m_data.EnemyInfluence) ? KFITEM_TEXT_COLOR_ALLY : KFITEM_TEXT_COLOR_ENEMY);

	int attackername_offset = 0;

#if _KILL_STREAK
	int row1_text_offset_y = static_cast<int>(static_cast<float>(baseRowHeight - attackerstringsize.cy) / 2 - 0.5f);
#else
	int row1_text_offset_y = static_cast<int>(static_cast<float>(height - attackerstringsize.cy) / 2 - 0.5f);
#endif

	// --- STEP 3: DRAW ATTACKER TEXT ---
	if (m_data.DamageType == DAMAGE_BY_PK)
	{
		m_pParent->GetFont()->DrawTextA(KFITEM_TEXT_MARGIN_X, row1_text_offset_y - 4, attackercolor, m_data.PlayerName, 0);
		attackername_offset = attackerstringsize.cx;
	}

	// --- STEP 4: RENDER SYSTEM ACTION ICON GRAPHICS USING REAL IMAGE DIMENSIONS ---
	if (icon)
	{
		int icon_x_pos = KFITEM_TEXT_MARGIN_X + attackername_offset + 5; // 5px padding before icon
		icon->Move(icon_x_pos, KFITEM_TEXT_MARGIN_Y);
		icon->SetScale(1.0f, 1.0f);
		icon->Render();
	}

	// --- STEP 5: DRAW TARGET OR VICTIM META LINE ---
#if _KILL_STREAK
	int target_text_offset_y = static_cast<int>(static_cast<float>(baseRowHeight - targetstringsize.cy) / 2 - 0.5f);
#else
	int target_text_offset_y = static_cast<int>(static_cast<float>(height - targetstringsize.cy) / 2 - 0.5f);
#endif

	// The target name starts perfectly right after Attacker Name + Dynamic Icon Space Allocation
	int target_x_pos = KFITEM_TEXT_MARGIN_X + attackername_offset + iconSpaceAllocation;

	if (m_data.DamageType == nMMEventHelpMe)
		m_pParent->GetFont()->DrawTextA(target_x_pos, target_text_offset_y - 4, RGB(0, 125, 255), szHelpMeMsg, 0);
	else if (m_data.DamageType == nMMEventMarkForm)
		m_pParent->GetFont()->DrawTextA(target_x_pos, target_text_offset_y - 4, RGB(0, 255, 0), szHelpMeMsg, 0);
	else
	{
#if _KILL_STREAK
		m_pParent->GetFont()->DrawTextA(target_x_pos, target_text_offset_y - 4, targetcolor, m_data.EnemyName, 0);
#else
		m_pParent->GetFont()->DrawTextA(width - targetstringsize.cx - KFITEM_TEXT_MARGIN_X, target_text_offset_y - 4, targetcolor, m_data.EnemyName, 0);
#endif
	}

	// --- STEP 6: RENDER ROW 2 (LOCKS TEXT TO THE RIGHTMOST CORNER) ---
#if _KILL_STREAK
	if (szCombo[0] != '\0')
	{
		int row2_text_offset_y = baseRowHeight + static_cast<int>(static_cast<float>(baseRowHeight - attackerstringsize.cy) / 2 - 0.5f);

		SIZE comboStringSize = m_pParent->GetFont()->GetStringSize(szCombo);
		int row2_combo_x = width - comboStringSize.cx - KFITEM_TEXT_MARGIN_X;
		int row2_name_x = row2_combo_x - attackerstringsize.cx - KFITEM_TEXT_MARGIN_X;

		// Draw Player Name aligned left of the combo multiplier text
		m_pParent->GetFont()->DrawTextA(row2_name_x, row2_text_offset_y - 4, attackercolor, m_data.PlayerName, 0);

		string colorFlag = "\\c";
		if (m_killStreak == 3)       colorFlag = "\\e";
		else if (m_killStreak == 4)  colorFlag = "\\m";
		else if (m_killStreak >= 5)  colorFlag = "\\r";

		string finalStreakMsg = colorFlag + szCombo;

		// Draw Combo multiplier text pinned right
		m_pParent->GetFont()->DrawTextA(row2_combo_x, row2_text_offset_y - 4, attackercolor, const_cast<char*>(finalStreakMsg.c_str()), 0);
	}
#endif

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