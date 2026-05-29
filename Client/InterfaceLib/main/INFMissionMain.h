// INFMissionMain.h: interface for the CINFMissionMain class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFMISSIONMAIN_H__49494CB9_B795_4B0E_A26D_6A026A1D2F42__INCLUDED_)
#define AFX_INFMISSIONMAIN_H__49494CB9_B795_4B0E_A26D_6A026A1D2F42__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "INFBase.h"
#include "INFArenaScrollBar.h"
#include "INFImageBtn.h"
#include "INFMissionTreeInfo.h"
#include "INFMissionPopupInfo.h"
#include "INFMissionSelInfluence.h"
#include "INFMissionMasterReg.h"
// �̼� ������ ����
#define		MISSOIN_SHOW_TREE				0		// ����Ʈ ��Ʈ��
#define		MISSOIN_SHOW_POPUP				1		// �˾� ������ 
#define		MISSOIN_SHOW_SEL_INFLUENCE		2		// ���¼��� 
#define		MAX_MISSOIN_SHOW				3

class CINFImage;
class CD3DHanFont;


class CINFMissionMain  : public CINFBase
{
public:
	CINFMissionMain();
	virtual ~CINFMissionMain();

	virtual HRESULT InitDeviceObjects();
	virtual HRESULT RestoreDeviceObjects();
	virtual HRESULT DeleteDeviceObjects();
	virtual HRESULT InvalidateDeviceObjects();
	virtual void	Render();
	virtual void	Tick();

	int WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

	void RenderMissionINGInfo();
	void SetMissionEnterShop(BOOL bEnterShopState);

	BOOL IsShowTreeWnd();
	void ShowTreeWnd(BOOL bFlag, BOOL bSoundPlay);

	// Ư�� ��ġ �̼�
	void SetPosMissionSearchStart(BOOL nstate);
	void SetPosMissionInfo(CQuest* pQuest);
	void SetPosMissionComplete(BOOL bFlag);

	// ���¹̼� ����
	BOOL GetInfluenceMission() ;
	void SetInfluenceMission(BOOL bFlag, float fANIPercent, float fVANPercent);

	// �̼� ���� �ʱ�ȭ 
	void RefreshMission(BOOL bClick, INT QuestIndex);

	void MissionEnd(DWORD dMissionIndex);

	void SelectNextMission(INT nQuestIndex);	

	void ShowMissionPopWnd(BOOL bShow, int nPossibleQuestIdx);

	BOOL IsLevelSecnQuest(BYTE byUpLevel, int nSuccessQuestIdx, int* o_nPossibleQuestIdx);
	void LoadQuestList(vector<int>* pVecQuestIndex);

	// ����Ʈ �̸�
	void SetQuestNameString(CQuest* pQuest, vector<string>* o_vecMissionName, 
											CINFImageListBox* pINFImageListBox, int nMaxString);
	// �̼ǰ��
	void SetQuestResult(CQuest* pQuest, vector<string>* o_vecPossibleDesc, 
										 CINFImageListBox* pINFImageListBox, int nMaxString);
	
	// ��ǥġ
	void SetGoalInfo(CQuest* pQuest, vector<string>* o_vecPossibleDesc);

	// �̼��� ������ �������� �Ǵ�	
	BOOL CheckMissionStart();	
	BOOL CheckMissionIdxStart(DWORD i_dwSelQuestIndex);	

	// �̼� ����
	void MissionStart(DWORD i_dwSelQuestIndex);

	// ��������Ʈ
	float GetVCNInflDistributionPercent();
	float GetANIInflDistributionPercent();
	
	// �ű� ���� �̼�â �߿��	
	int	GetMissionMapQuestIdx();
	void SetMissionMapQuestIdx(int nQuestIdx);
	void SetFirstPossibleQuestIdx(int nPossibleQuestIdx);
	int  GetFirstPossibleQuestIdx();
	void OnClickFirstUserCloseBtn();

	// �̼Ǹ� ���� UI������Ʈ
	void RefreshMissionUI();
	
// 2008-12-09 by dgwoo �̼Ǹ�����.
	void SetMissionMasterWindowShow(BOOL i_bShow);
	INT	 GetMissionMasterQuestIdx();
	void UpdateMissionMasterButton();
	
private:
	BOOL IsShowWnd(int nShowWnd);
	void TickHideMission();
	void TickBtn();

	int OnLButtonDown(WPARAM wParam, LPARAM lParam);
	int OnLButtonUp(WPARAM wParam, LPARAM lParam);
	int OnMouseMove(WPARAM wParam, LPARAM lParam);

	void OnClickGoMap();	// ��� ��ư 
	void OnClickGoMissionMap(); // �̼Ǹ����� �̵�

private:
	// �̼� Ʈ��
	CINFMissionTreeInfo*	m_pINFMissionTreeInfo;
	// �˾� Ʈ��
	CINFMissionPopupInfo*	m_pINFMissionPopupInfo;
	// ���� ���� �̼�
	CINFMissionSelInfluence*	m_pINFMissionSelInfluence;
// 2008-12-09 by dgwoo �̼Ǹ�����.
	// �̼� ������ ��� â.
	CINFMissionMasterReg*	m_pINFMissionMaster;
	
	// ��� ��ư
	CINFImageBtn*			m_pGoMapBtn;
	// �̼Ǹ����� �̵�
	CINFImageBtn*			m_pGoMissionMapBtn;
#if _RAT_FFA
	CINFImageBtn*			m_pGoFFABtn;
#endif


	int						m_nShowMissionWnd;		// �̼� ������ ����	

	// 2014-07-02 by ymjoo DrawText ���� ���� �۾� (�����߹̼�)
#ifdef C_DRAWTEXT_UPGRADE_YMJOO
	CD3DHanFont*			m_pMissionINGFont[10];
#else
	CD3DHanFont	*			m_pMissionINGFont;
#endif
	// END 2014-07-02 by ymjoo DrawText ���� ���� �۾� (�����߹̼�)


	BOOL					m_bSearchPosQuest;
	CQuest*					m_pHidePosQuest;

	// ���¼��� �̼�
	BOOL					m_bInfluenceFlag;

	float					m_fVCNInflDistributionPercent;	// ���������� ���Ա� ���º��� - ���¼��� �̼ǽø� ����
	float					m_fANIInflDistributionPercent;	// �˸��� ���Ա� - ���¼��� �̼ǽø� ����

	// Ư�� ���� ����Ʈ
	BOOL					m_bPosMissionComplete;

	int						m_nMyShuttleCharacter;

	int						m_nMissionMapQuestIndex;
	// ������ ����Ʈ ��ȣ
	int						m_nFirstPossibleQuestIdx;
};

#endif // !defined(AFX_INFMISSIONMAIN_H__49494CB9_B795_4B0E_A26D_6A026A1D2F42__INCLUDED_)
