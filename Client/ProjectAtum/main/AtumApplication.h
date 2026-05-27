// AtumApplication.h: interface for the CAtumApplication class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ATUMAPPLICATION_H__32E91AE4_C7F3_424D_B983_17488D8A215B__INCLUDED_)
#define AFX_ATUMAPPLICATION_H__32E91AE4_C7F3_424D_B983_17488D8A215B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "D3DApp.h"
#include "IMEKey.h"		// imm32.lib
#include "INFGameMainQSlot.h"
// 2008-03-19 by bhsohn Ep3�ɼ�â
//#include "INFSystem.h"
#include "INFOptionSystem.h"

#include "CInput.h"

// 2009. 06. 09 by ckPark OMI ���� ���۽� üũ�� ����ϵ��� ����
#include "sha256.h"
// end 2009. 06. 09 by ckPark OMI ���� ���۽� üũ�� ����ϵ��� ����
#include "zwave_sdk_client.h"		 // 2012-10-13 by jhahn �ٽ���->Xigncode����

class CFrustum;
class CD3DHanFont;
class CKeyBoardInput;
class CCamera;
class CShuttleRender;
class CShuttleChild;
class CCharacterChild;
class CTraceRender;
class IMEKey;
class CChat;
class CFieldWinSocket;
class CIMSocket;
// 2007-11-22 by bhsohn �Ʒ��� ���ռ���
class CIMSocketManager;
class CFieldWinSocketManager;
class CArenaManager;

class CMapInitThread;
class CGameData;
class CEffectRender;
class CAtumNode;
class CInterface;
class CAbuseFilter;
class CAtumSound;
class CSceneData;
class CAtumDatabase;
class CINFStageEffect;
class CINFGameMain;
class CStoreData;
class CQuestData;
class CBackground;
class CINFSelect;
class CINFChannelList;
class CUnitRender;
class CCharacterRender;						// 2005-07-21 by ispark
class CFxSystem;
class CTutorialSystem;
class CInputManager;
class CGlobalImage;
class CUnitData;
class CSinglePlayGame;	// 2008-08-11 by bhsohn �ܵ����� ���� �ǰԲ�
// 2008-11-13 by bhsohn ���̽�ƽ �۾�
class CJoyStickInput;	
class CJoyStickFreedback;
// end 2008-11-13 by bhsohn ���̽�ƽ �۾�

class CWorldRankManager;		// 2009-02-13 by bhsohn ���� ��ŷ �ý���

// 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���
class CInfinityManager;
// end 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���

// 2009. 11. 23 by jskim ���ҽ� �ε� ���� ����
class CSkinnedMesh;
class CMeshInitThread;
//end 2009. 11. 23 by jskim ���ҽ� �ε� ���� ����

// 2010-06-15 by shcho&hslee ��ý���
class CPetManager;
// end 2010-06-15 by shcho&hslee ��ý���

class CINFEnemyItemInfo;	// 2012-06-14 by isshin ���۹̸�����

class CMapLoad;    // 2010. 10. 05 by jskim �ʷε� ���� ����

// 2011. 10. 10 by jskim UI�ý��� ����
class CINFGroupManager;
class CINFImageList;
// end 2011. 10. 10 by jskim UI�ý��� ����
class CVTCThread;			// 2011. 1. 18 by jskim ��Ʈ�� VTC����

class CProfiler;	// 2014-06-09 by ymjoo �������Ϸ� ����

typedef struct 
{
	INT			ItemNum;						// ������ ������ȣ, ���� �������� �� (ITEM_BASE*)
	BYTE		byItemKind;				// ������ ����(�����, ��, ����, ��ų.....)
	UID64_t		nUniqueNumber;			// ������ ������ȣ
	INT			nAmount;				// ������ ����
	UINT		nBuildingIndex;			// �ǹ� �ε���
	char		szIconName[20];			// ������ ID
	char		szName[50];				// ������ �̸�
	UINT		uSellingPrice;			// �Ǹ� ���� 
	INT			SourceIndex;			// ����Ʈ, ������(��/����) ���ҽ� ����Ÿ
	BYTE		bySelectType;
	POINT		ptIcon;
} stMultiSelectItem;

// 2007-11-20 by bhsohn �ʷε� �ϴ� ��� ����
// ���� ���� �� ����ü
typedef struct 
{
	AVECTOR3		vPos;
	BitFlag16_t		MapWeather;
} stGameStartInfo;

// 2007-12-21 by bhsohn ���α׷� ���� �� ���� ����
// ������ ���
#define		MULTI_LOCK_ALL_MATCHING		0		//	��� ��Ī �Ǿ����� Ǯ����.
#define		MULTI_LOCK_ONE_MATCHING		1		//	�ϳ��� ��Ī�ǵ� Ǯ����.

// ���� �����ϱ� ���� �⺻ ����
typedef struct 
{
	MessageType_t			nLockMsg;
	vector<MessageType_t>	vecUnLockMsg;
	int						nLockType;
	BOOL					bFiledServer;
} stMultiLockInfo;
// end 2007-12-21 by bhsohn ���α׷� ���� �� ���� ����

// 2007-11-22 by bhsohn �Ʒ��� ���ռ���
// ���� ��ŸƮ �Ϸ�� ó�� �Ǵ� ����ü
typedef struct 
{
	char			ServerGroupName0[SIZE_MAX_SERVER_NAME];			// 2007-04-09 by cmkwon
	char			MainORTestServerName[SIZE_MAX_SERVER_NAME];		// 2007-04-09 by cmkwon
	char			GamePublisher[SIZE_MAX_GAME_PUBLISHER_NAME];	// 2007-04-09 by cmkwon
	
	MAP_CHANNEL_INDEX	MapChannelIndex;		// ĳ���Ͱ� ���� �� �� ä��
	BYTE				CharacterMode0;				// 
	
	AVECTOR3			PositionVector;
	BitFlag16_t			MapWeather;	
	BOOL				bMemberPCBang;			// ���� PC�� �÷���
}structGameStartOkInfo;
// end 2007-11-22 by bhsohn �Ʒ��� ���ռ���

// 2009. 11. 23 by jskim ���ҽ� �ε� ���� ����
struct structLoadingGameData
{
	structLoadingGameData()
	{
		LoadingPriority = _NOTHING_PRIORITY;
	}
	CGameData*		pGameData;
	int				MeshIndex;
	int				MeshType;
	int				Step;					// �ε� ����(1, 6)
	int				Text_Cnt;				// �ؽ��� �ε� ���� ��
	int				LoadingPriority;
	CSkinnedMesh*	pSkinnedMesh;
};
struct structLoadingGameInfo
{
	structLoadingGameInfo()
	{
		LoadingPriority = _NOTHING_PRIORITY;
	}	
	char			MeshName[16];
	int				MeshType;
	CSkinnedMesh*	pSkinnedMesh;
	int				LoadingPriority;
};
// 2011. 1. 18 by jskim ��Ʈ�� VTC����
typedef bool (_stdcall *func1) ();
typedef bool (_stdcall *func2) ();
typedef bool (_stdcall *func3) (char*);
typedef void (_stdcall *func4) ();
// end 2011. 1. 18 by jskim ��Ʈ�� VTC����

// 2007-07-10 by bhsohn ��� Ÿ�� ������ ���� ó��
#define SIZE_MAX_ERROR_CHAT_MESSAGE			512

// 2008-11-13 by bhsohn ���̽�ƽ �۾�
#define MAX_JOYCTL_LIST			10			// MAX_JOY_LIST�� ������ ���̾���Ѵ�.

// 2009-01-22 by bhsohn Xign Code ����ϴ� ���� ��� �߰�
//////////////////////// ���� ���� ����////////////////////////
//
#define		USE_GAMEGUARD_NONE					0		//���Ӱ��� ������
#define		USE_GAMEGUARD_AHNLAB_HACKSHIELD		1		//�ٽ��� ���Ӱ���
#define		USE_GAMEGUARD_XIGNCODE				2		//Xign ���Ӱ���
#define		USE_GAMEGUARD_NPROTECTOR			3		// 2009-01-28 by bhsohn nProtector ���� ���� �߰�				
// 2009. 06. 17 by ckPark Frost System
#define		USE_GAMEGUARD_FROST					4
// end 2009. 06. 17 by ckPark Frost System
	// 2009. 09. 21 by jskim ���Ӱ��� XTRAP ����(��Ʈ��)
#define		USE_GAMEGUARD_XTRAP					5
	//end 2009. 09. 21 by jskim ���Ӱ��� XTRAP ����(��Ʈ��)

// 2009. 11. 03 by ckPark �±� APEX ���Ӱ��� �۾�
#define		USE_GAMEGUARD_APEX					6
// end 2009. 11. 03 by ckPark �±� APEX ���Ӱ��� �۾�
// 2011. 1. 18 by jskim ��Ʈ�� VTC����
#define		USE_GAMEGUARD_VTC					7
// end 2011. 1. 18 by jskim ��Ʈ�� VTC����

// 2013-10-11 by bhsohn XTrap&VTC ���� �۾�
#define		USE_GAMEGUARD_XTRAP_N_VTC		8		//XTrap+VTC����
// END 2013-10-11 by bhsohn XTrap&VTC ���� �۾�


// 2009. 06. 17 by ckPark Frost System

// #if defined(_DEBUG) || defined(INNOVA_RELEASE) || defined(GAMEFORGE_RELEASE)
// 	// ���Ӱ��� ������
// 	#define		GAMEGUARD_TYPE 					USE_GAMEGUARD_NONE
// 	#define		NO_GAMEGUARD
// #elif defined(LANGUAGE_CHINA) // 2009-04-15 by bhsohn �߱� XignCode���
// 	#define		DEFINE_USE_GAMEGUARD_XIGNCODE		
// 	// XIGNCode
// 	#define		GAMEGUARD_TYPE					USE_GAMEGUARD_XIGNCODE	
// 
// // 2009-01-28 by bhsohn nProtector ���� ���� �߰�
// #elif defined(LANGUAGE_JAPAN)
// 	// nProtector ���� ���� �߰�
// 	#define		GAMEGUARD_TYPE 					USE_GAMEGUARD_NPROTECTOR
// 	#define		DEFINE_USE_GAMEGUARD_NPROTECTOR	
// 	#pragma comment(lib, "NPGameLib.lib")
// 	#include "NPGameLib.h"		// 
// // end 2009-01-28 by bhsohn nProtector ���� ���� �߰�
// #else
// 	// �ٽ���
// 	#define		GAMEGUARD_TYPE					USE_GAMEGUARD_AHNLAB_HACKSHIELD		
// #endif
// // end 2009-01-22 by bhsohn Xign Code ����ϴ� ���� ��� �߰�


	// 2009. 07. 13 by jsKim �������� �ٽǵ� ����
// #if defined(_DEBUG) || defined(GAMEFORGE_RELEASE)
// 	// ���Ӱ��� ������
// 	#define		GAMEGUARD_TYPE 					USE_GAMEGUARD_NONE
// 	#define		NO_GAMEGUARD

// 2013-07-12 by bhsohn China Work
// 2015-04-13 by jwLee �Ϻ� ���Ӱ��� ����
//#if defined(_DEBUG) || defined(TEST140) || defined(WIKIGAMES_ENG)|| defined(LANGUAGE_CHINA)// 2012-10-22 by bhsohn ���Ӱ��� ������ ����
#if defined(_DEBUG) || defined(TEST140) || defined(WIKIGAMES_ENG)|| defined(LANGUAGE_CHINA) || defined(LANGUAGE_JAPAN) // 2012-10-22 by bhsohn ���Ӱ��� ������ ����
// end 2015-04-13 by jwLee �Ϻ� ���Ӱ��� ����
// ���Ӱ��� ������
#define		GAMEGUARD_TYPE 					USE_GAMEGUARD_NONE
#define		NO_GAMEGUARD

	// 2011. 01. 18 by jsKim 140�� �ٽǵ� ���� 
#elif  defined(GAMEGUARD_NOT_EXECUTE_HSSON)
#define		GAMEGUARD_TYPE					USE_GAMEGUARD_NONE
	// end 2011. 01. 18 by jsKim 140�� �ٽǵ� ���� 
#elif  defined(GAMEFORGE_RELEASE)
// 2015-01-07 by jwLee �������� nProtector ����
//#define		GAMEGUARD_TYPE					USE_GAMEGUARD_AHNLAB_HACKSHIELD
	// end 2009. 07. 13 by jsKim �������� �ٽǵ� ����
	#define		GAMEGUARD_TYPE 					USE_GAMEGUARD_NPROTECTOR
	#define		DEFINE_USE_GAMEGUARD_NPROTECTOR	
	#define		DEFINE_USE_GAMEGUARD_NPROTECTOR_AUTH3
	#pragma comment(lib, "NPGameLib.lib")
	#include "NPGameLib.h"
// end 2015-01-07 by jwLee �������� nProtector ����


// 2013-07-12 by bhsohn China Work
// #elif defined(LANGUAGE_CHINA)
// 	// 2009-04-15 by bhsohn �߱� XignCode���
// 	#define		DEFINE_USE_GAMEGUARD_XIGNCODE		
// 	// XIGNCode
// 	#define		GAMEGUARD_TYPE					USE_GAMEGUARD_XIGNCODE	
// END 2013-07-12 by bhsohn China Work
// 2015-04-13 by jwLee �Ϻ� ���Ӱ��� ����
// #elif defined(LANGUAGE_JAPAN)
// 	// 2009-01-28 by bhsohn nProtector ���� ���� �߰�
// 	// nProtector ���� ���� �߰�
// 	#define		GAMEGUARD_TYPE 					USE_GAMEGUARD_NPROTECTOR
// 	#define		DEFINE_USE_GAMEGUARD_NPROTECTOR	
// 	#pragma comment(lib, "NPGameLib.lib")
// 	#include "NPGameLib.h"		// 
// 	// end 2009-01-28 by bhsohn nProtector ���� ���� �߰�
// 
// 	// 2009. 09. 21 by jskim ���Ӱ��� XTRAP ����(��Ʈ��)
// end 2015-04-13 by jwLee �Ϻ� ���Ӱ��� ����
#elif defined(LANGUAGE_VIETNAM)
// 2011. 1. 18 by jskim ��Ʈ�� VTC����
// 	#define		GAMEGUARD_TYPE 					USE_GAMEGUARD_XTRAP
// 	#define		DEFINE_USE_GAMEGUARD_XTRAP
// 
// 	#pragma comment(lib, "XTrap4Client_st")
// 	#pragma comment(lib, "XTrap4Client_ClientPart_st")
// 	#pragma comment(lib, "XTrap4Client_ServerPart_st")
// 	#pragma comment(lib, "XTrap_Unipher_st")
// 	#include "Xtrap_C_Interface.h"
	//end 2009. 09. 21 by jskim ���Ӱ��� XTRAP ����(��Ʈ��)
// 2013-10-11 by bhsohn XTrap&VTC ���� �۾�
//  	#define		GAMEGUARD_TYPE 					USE_GAMEGUARD_VTC
// 	#define		DEFINE_USE_GAMEGUARD_VTC
	#ifdef SC_XTRAP_VTC_GAMEGUARD_BHSOHN_JHSEOL
		#define		GAMEGUARD_TYPE					USE_GAMEGUARD_XTRAP_N_VTC
		#define		DEFINE_USE_GAMEGUARD_XTRAP
		#pragma comment(lib, "XTrap4Client_st")
		#pragma comment(lib, "XTrap4Client_ClientPart_st")
		#pragma comment(lib, "XTrap4Client_ServerPart_st")
		#pragma comment(lib, "XTrap_Unipher_st")
		#include "Xtrap_C_Interface.h"
	#else
		#define		GAMEGUARD_TYPE 					USE_GAMEGUARD_VTC
		#define		DEFINE_USE_GAMEGUARD_VTC

	#endif
// END 2013-10-11 by bhsohn XTrap&VTC ���� �۾�

// end 2011. 1. 18 by jskim ��Ʈ�� VTC����

	// 2009. 11. 03 by ckPark �±� APEX ���Ӱ��� �۾�
#elif defined(LANGUAGE_THAI)
	#define		GAMEGUARD_TYPE					USE_GAMEGUARD_APEX
	#define		DEFINE_USE_GAMEGUARD_APEX

	#include "ApexClient.h"
	#pragma comment( lib, "AHClientInterface.lib" )
	// end 2009. 11. 03 by ckPark �±� APEX ���Ӱ��� �۾�

#elif defined(INNOVA_RELEASE)
	#define		GAMEGUARD_TYPE					USE_GAMEGUARD_FROST
	#define		DEFINE_USE_GAMEGUARD_FROST

	// 2010. 01. 13 by ckPark Frost���Ӱ��� 2009.11.10���� ������Ʈ
	#pragma warning (disable : 4786)
	// end 2010. 01. 13 by ckPark Frost���Ӱ��� 2009.11.10���� ������Ʈ

	#include "shieldSecurity.h"
	#include "shieldSecurityDll.h"
// 2010. 11. 05 by jskim ���Ӱ��� ���� (�Ƹ���Ƽ��)
#elif defined(LANGUAGE_ARGENTINA)
	#define		GAMEGUARD_TYPE					USE_GAMEGUARD_XTRAP
	#define		DEFINE_USE_GAMEGUARD_XTRAP
	#pragma comment(lib, "XTrap4Client_st")
	#pragma comment(lib, "XTrap4Client_ClientPart_st")
	#pragma comment(lib, "XTrap4Client_ServerPart_st")
	#pragma comment(lib, "XTrap_Unipher_st")
	#include "Xtrap_C_Interface.h"
// end 2010. 11. 05 by jskim ���Ӱ��� ���� (�Ƹ���Ƽ��)
// 2012-10-22 by bhsohn ���Ӱ��� ������ ����
// 2012-10-13 by jhahn �ٽ���->Xigncode����
//#else
// 	#define				DEFINE_USE_GAMEGUARD_XIGNCODE		
// 	#define				GAMEGUARD_TYPE					USE_GAMEGUARD_XIGNCODE	
// 
// 	#define				GAME_GUARD_LICENSE		"FF7cjcycIB38"
// 	#define				GAME_GUARD_FOLDER		"Xigncode"
// 	#define				GAME_GUARD_FOLDER_DEBUG	"Xigncode_D"
//end 2012-10-13 by jhahn �ٽ���->Xigncode����
#elif defined(YEDANG_KOR)
	#define				DEFINE_USE_GAMEGUARD_XIGNCODE		
	#define				GAMEGUARD_TYPE					USE_GAMEGUARD_XIGNCODE	

	#define				GAME_GUARD_LICENSE		"FF7cjcycIB38"
	#define				GAME_GUARD_FOLDER		"Xigncode"
	#define				GAME_GUARD_FOLDER_DEBUG	"Xigncode_D"
#else 
	#define				GAMEGUARD_TYPE					USE_GAMEGUARD_AHNLAB_HACKSHIELD		
// END 2012-10-22 by bhsohn ���Ӱ��� ������ ����
#endif

// end 2009. 06. 17 by ckPark Frost System


class CAtumApplication : public CD3DApplication  
{
	friend class CShuttleChild;
public:
	CAtumApplication();
	virtual ~CAtumApplication();

	HRESULT InitDShowTextureRenderer();
	HRESULT MovieRender();
	
	HRESULT CheckMovieStatus(void);
	void CleanupDShow(void);
	
	
	HRESULT AddToROT(IUnknown *pUnkGraph); 
    void RemoveFromROT(void);

	D3DSURFACE_DESC & GetBackBufferDesc() { return m_d3dsdBackBuffer; }
	FLOAT 	GetFPS();
	FLOAT	GetElapsedTime() { return m_fElapsedTime; }
	HWND	GetHwnd() { return m_hWnd; }
	D3DCAPS9 & GetDeviceCaps() { return m_d3dCaps; }
	VOID	SendMovePacket(BOOL bActive);	// 2004-11-08 by jschoi
	void	InitStageEffect( int nIndex, float fPlayTime=5.0f, BOOL bEnableSkip=TRUE );
	DWORD	ResourceLoadThread();	// load thread function(CInitThread�� �Բ� ����Ѵ�.)
	DWORD	ResourceRestoreThread();
	VOID	RenderGame();
	VOID	CleanText();
	VOID	CheckError(DWORD err);
	VOID	LoadPath( char* strPath, UINT nType, char * strFileName );
	VOID	CalcObjectSourceScreenCoords(D3DXVECTOR3 vObjPos,int iScreenWidth, int iScreenHeight,int &iCoordX, int &iCoordY, int &iCoordW);
	VOID	CheckRenderState();
	VOID	SetCamPosInit();
	FLOAT	Distance3DTo2D(D3DXVECTOR3 vPos1, D3DXVECTOR3 vPos2);
	VOID	ChangeEffectTexture(CAtumNode * pNode,char * str);
	// 2008-01-18 by bhsohn �߱� Ŭ���̾�Ʈ �״� ���� �ذ�
	//VOID	ChangeGameState(DWORD dwType);
	VOID	ChangeGameState(DWORD dwType, BOOL bUseThread=FALSE);
	int		GetScreenShotNumber();
	void	TakeScreenShot(IDirect3DDevice9* device, char* file_name, int screenx, int screeny);
	void	DeleteEffectList();
	void	InitSpeedHackTimer();
	BOOL	IsWindowMode() { return m_bWindowed; }
	// 2007-07-20 by bhsohn �긮�η� ����
	DWORD	GetGameState();
	
    HRESULT OneTimeSceneInit();
    HRESULT InitDeviceObjects();
    HRESULT RestoreDeviceObjects();
    HRESULT InvalidateDeviceObjects();
    HRESULT DeleteDeviceObjects();
    HRESULT Render();
    HRESULT FrameMove();
	HRESULT InActiveFrameMove();										// 2006-07-06 by ispark
    HRESULT FinalCleanup();
	LRESULT MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	HRESULT ConfirmDevice( D3DCAPS9* pCaps, DWORD dwBehavior, D3DFORMAT Format );
	VOID	NetworkErrorMsgBox( char* strMsg);

	void	RenderCity();
	// remodeling, 2004-03-17 by dhkwon
	// SendFieldSocket~
	// 2007-11-22 by bhsohn �Ʒ��� ���ռ���
	//VOID	SendFieldSocketConnectLogin();
	VOID	SendFieldSocketConnectLogin(CFieldWinSocket* pFieldSocket);
	VOID	SendFieldSocketChangeCharacterBodyCondition(BodyCond_t hySingleBodyCondition, BOOL bSet);//FieldSocketCharacterChangeCurrentHPDPSPEP,FieldSocketCharacterChangeCurrentHP
	VOID	SendFieldSocketCityGetBuildingList( MAP_CHANNEL_INDEX mapChannelIndex );
	VOID	SendFieldSocketGetShopWarpTargetMapList( MAP_CHANNEL_INDEX mapChannelIndex );	
	void	SendArenaLoginOk();
	void	SendAreneEnterRoomWarp();
	void	SendFCArenaCharacterGameStart();					// ���μ������� �Ʒ����� �ε��
	void	SendFCCharacterGameStartFromArenaToMainServer();	// �Ʒ��� ���ҽ� �ε�Ϸ� 
	int		NextStepArenaState();		// �Ʒ��� ���°� ������Ʈ 
	void	ConevertArenaRenderUserName(int nArenaState, char* pSrcDst);
	CHARACTER* GetMFSMyShuttleInfo();	//MainServer ������ ���´�.
	void	SetMFSMyShuttleInfo(CHARACTER *pMyShuttleInfo);//MainServer ������ �����Ѵ�. 

	// 2007-02-12 by bhsohn Item ���� ���� ó��
	void	DelMultiItemList(BOOL bInitCtlBtn=FALSE);	
	BOOL	CheckMultItemSel(UID64_t	 nUniqueNumber);	
	BOOL	CheckCityStoreMultItemSel(UID64_t	 nUniqueNumber); // â���� ������ ���� ���� �Ǵ�.��
	int		GetMultiSelectItem();
	int		GetCityStoreMultiSelectItem();
	void	GetMultiItemSPI(int nShopId, char* pDstSpi);

	// 2007-03-02 by bhsohn ���� ���� �߰� ����
	deque<stMultiSelectItem>* GetMultiSelVector(BYTE byType);

	// by bhsohn 2007-03-12 China Working
	void DxSetDialogBoxMode(BOOL bEnable);

	// 2007-04-05 by bhsohn �ʷε��, üũ�� �߰�
	MAP_CHANNEL_INDEX GetMyShuttleMapChannelIndex();

	// 2007.04.24 by bhsohn China IME Working
	void	UpdateReadingString(char* pText, int nTextLen);
	void	UpdateIMEType(char* pText, int nTextLen);

	// 2007-05-17 by bhsohn ������Ʈ �ڿ� �������� �� ���� ó �˻� ó��
	BOOL	IsMyShuttleCharacter();
	// 2007-05-21 by bhsohn China IME Working
	void	RenderIMEType(int x, int y);

	// 2007-07-11 by bhsohn omi üũ�� �߰�
	void	SendOMICheckSum();

	// 2010. 03. 12 by ckPark Interface.tex üũ�� �߰�
	void	SendInterfaceCheckSum( void );
	// end 2010. 03. 12 by ckPark Interface.tex üũ�� �߰�

	// 2007-07-24 by bhsohn �����̼� mp3�߰�
	// 2009. 01. 22 by ckPark �� ���º� ���۷����� MP3 �и�
	//void	StartNarrationSound(char* pNarrationSound);
	void	StartNarrationSound(char* pNarrationSound, char* pErNarrationSound=NULL);
	void	EndNarrationSound();	
	void	SetFirstUserIntoFreeSka(BOOL bTake);
	BOOL	GetFirstUserIntoFreeSka();	
	
	// 2007-08-29 by bhsohn �ּ� �����ӽ� �⺻ �ƸӸ� �ε��ϰԲ� ����
	BOOL	SendMeshObjectCheckSum(int nMeshIndex);

	// 2007-08-29 by bhsohn �ּ� �����ӽ� �⺻ �ƸӸ� �ε��ϰԲ� ����
	void	ReLoadEnemyRenderList();		

	// 2007-09-06 by bhsohn �����̾� ������ �Ѿ˼� 2��
	BOOL	IsPrimiumUser();

	// 2007-09-05 by bhsohn ���� ������
	void	EnableChatMode(BOOL bChat, BOOL bUpdatIMEDevice);	
	BOOL	IsMyShuttleLeader();
	BOOL	IsMyShuttleGuildMaster();
	BOOL	IsLeaderOutPost();

	// 2007-09-12 by bhsohn 2�� ��ȣ �ý��� ����
	BYTE	IsUseSecondaryPasswordSystem();
	BYTE	IsSetSecondaryPassword();	
	void	EnterLock(BOOL bUnLock);
	BOOL	GetEnterLock();
	void	SendDeleteCharcter(char* pEncordPassWord);

	// 2008-07-07 by bhsohn 2�� �н����� Ȱ��ȭ��, �κ� �ȿ����� ��
	BYTE	IsSecondPassLock();
	void	SetSecondPassLock(BYTE bySecondPassLock);

	// 2007-12-21 by bhsohn ���α׷� ���� �� ���� ����
	void	EnterMultiLock(BOOL bFiledServer, MessageType_t nLockMsg, vector<MessageType_t> vecUnLockMsg, int nLockType);
	void	CheckMultiLock(BOOL bFiledServer, MessageType_t msgUnLockMsg);
	// 2007-11-22 by bhsohn �Ʒ��� ���ռ���

	// �ش� �޽��� Lock�� ���� Ȯ��.
	bool	IsEnableMultiLock ( MessageType_t nLockMsg );

	void	OnClickArenaShop();
	void	RequestArenaTeamList();
	void	SetArenaState(int nState);
	int		GetArenaState();
	void	ArenaFinishWarp(BOOL bForceCloseArenaSocket);	// �Ʒ��� ���� â�� ���� Ȯ�� 
	void	ArenaGameStarOk(structGameStartOkInfo *pMsg, BOOL bGotoArena);
	void	CloseArenaSocket();
	CHARACTER*	GetArenaCharacterInfo();
	void	StartGmConnectAenenaServer();		// GM�� �Ʒ��� ������ ���� 
	void	GmConnectAenenaIMServer();			// GM�� �Ʒ��� IM������ ���� 
	void	SetGmModeConnect(BOOL bGmModeConnect);
	BOOL	IsGmModeConnect();

	// 2008-03-03 by bhsohn ���� �Ʒ��� IM���� ������� ����
	void	UserConnectAenenaIMServer();


	// 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���
	void	OnClickInfinityField( void );
	void	UserConnectInfinityIMServer( void );
	// end 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���


	// 2008-02-15 by bhsohn ��Ʈ��ũ �ӵ� üũ
	VOID	StartNetCheck(char* pCmd);
	VOID	SendCheckNetState();

	// 2008-03-07 by bhsohn ��������, �Ʒ��� �̿� ���ϰ� ����
	BOOL	IsDoingInfluenceWar();

	// 2008-03-17 by bhsohn ������ �̵��� Tick�ȵ����� ���� ó��
	BOOL	IsPossibleWindowMove();

	// 2008-03-27 by bhsohn �̼Ǽ���â�� ���ִ� ���¿����� ������ �ȿ����� ����
	BOOL	IsPossibleShopOpen();

	// 2008-04-07 by bhsohn �ý���Ű �ɷ����� �ý��� �߰�
	BOOL	IsSysKeyDownPermisiion(WPARAM wParam, LPARAM lParam);

	// 2008-06-16 by bhsohn �±� ���� ������ �������� �߿�� ��
	BOOL	ExcuteExplore();

	// 2008-06-20 by bhsohn EP3 �ɼǰ��� ó��
	void	InitOptionEtcInfo(sOPTION_ETC* pEtc);
	BOOL	IsOptionEtc(int nOptionIdx);
	stcuctRateRect GetOptionInterfacePOS();
	void	SetOptionInterfacePOS(stcuctRateRect* pRect);


	// 2009. 02. 03 by ckPark ä��â �������̽� ũ�� ����

	stcuctRateRect GetChatInterfacePOS(void);
	void	SetChatInterfacePOS(stcuctRateRect* pRect);

	// end 2009. 02. 03 by ckPark ä��â �������̽� ũ�� ����


	int		GetFriendListOnCount();

	// 2008-08-11 by bhsohn �ܵ����� ���� �ǰԲ�
	BOOL	IsSingletonMode();
	void	SingPlayGameStartOk(MSG_FC_CHARACTER_GAMESTART_OK * pMsg);

	// 2008-09-17 by bhsohn ���� �������ϸ� üũ�� �߰�
	void	SendAtmCheckSum();

	// 2008-11-11 by bhsohn ����Ʈ CheckSum�߰�
	void	SendQuestCheckSum();

	// 2008-11-13 by bhsohn ���̽�ƽ �۾�
	// ��Ʈ�� ���̽�ƽ
	CJoyStickInput *GetJoystickControl();
	BOOL GetAsyncKeyState_DIK_DIJ(int code);	
	// ���̽�ƽ ��Ʈ�� ����
	int GetJoystickCtrlDeviceListLen();	
	char* GetJoystickCtrlDeviceList(int i_nIdx);

	// �����е�
	CJoyStickFreedback *GetJoyStickFeedback();
	void SetJoyStickFeedback(BOOL bSetFeedBack, int nPowerIndex);

	// ���̽�ƽ �������
	BOOL IsUseJoyStick();
	BOOL IsUseJoyFeedBack();	// ���� ��� ����
	void SetUseJoyStick(BOOL bUse);
	void SetUseJoyFeedBack(BOOL bUse);

	// ���̽�ƽ �ɼ�����
	void InitJoyStickOptionInfo(structJoyStickOptionInfo* pJoysticOp);

	// ���̽�ƽ ��ġ �ʱ�ȭ
	int InitJoyStickDevice(BOOL bJoyControl, BOOL bJoyFeed, char* o_pDevice);
	// end 2008-11-13 by bhsohn ���̽�ƽ �۾�

	// 2008-12-29 by bhsohn ��Ű �ӽ� ���� ����Ʈ �߰�
	void CreateMyAppEffectData(int i_nType, D3DXVECTOR3	i_vPos, D3DXVECTOR3	i_vVel, D3DXVECTOR3	i_vUp); // �� ��ġ�� ����Ʈ ����
	void SendCharcterShowMapEffect(MSG_FC_CHARACTER_SHOW_MAP_EFFECT* i_pMsg);
	D3DXVECTOR3 GetMyShuttleCharacterPos();
	D3DXVECTOR3 GetViewDirVel();
	// end 2008-12-29 by bhsohn ��Ű �ӽ� ���� ����Ʈ �߰�

	// 2009-01-28 by bhsohn nProtector ���� ���� �߰�
	BOOL InitGameGuardNProtector();
	BOOL SetGameGuardHWND();
	BOOL TickGetCheckGameGuardNProtector();		
	void	HS_SendHackShieldErrorMsg(long lHackClientCode, char * pMsg = NULL);
	// end 2009-01-28 by bhsohn nProtector ���� ���� �߰�
	// 2009. 09. 21 by jskim ���Ӱ��� XTRAP ����(��Ʈ��)
	void TickGetCheckGameGuardXTrap();
	//end 2009. 09. 21 by jskim ���Ӱ��� XTRAP ����(��Ʈ��)

	// 2009-02-13 by bhsohn ���� ��ŷ �ý���
	CWorldRankManager*	GetWorldRankManager();
	void RqAllWorldRankInfo();
	// end 2009-02-13 by bhsohn ���� ��ŷ �ý���

	// 2009-02-24 by bhsohn ĳ���� ���� �������� �߰�
		// 2012-11-28 by jhjang �������� �� ���� ���� �߰� �۾�
	// 2012-11-23 by jhjang �������� �� ���� ���� �۾�
	// void PopupWebWindow(BOOL i_bPopup);
	// void PopupWebWindow(BOOL i_bPopup,char* strWebSite = NULL);
	void PopupWebWindow(BOOL i_bPopup,char* strWebSite = NULL,char* strWebParameter = NULL,int nWebPosX = -1,int nWebPosY = -1,int nWebWidth = -1,int nWebHeight = -1);
	// end 2012-11-23 by jhjang �������� �� ���� ���� �۾�
	// end 2012-11-28 by jhjang �������� �� ���� ���� �߰� �۾�
	// end 2009-02-24 by bhsohn ĳ���� ���� �������� �߰�

	// 2009-02-26 by bhsohn Japan IME
	VOID CleanIMEControl();
	// end 2009-02-26 by bhsohn Japan IME

	// 2009-03-10 by bhsohn nProtector CS��� �߰�
	void SendNpGameMonCheckCSAuth2(PVOID dwArg);
	// end 2009-03-10 by bhsohn nProtector CS��� �߰�
	// 2015-01-07 by jwLee �������� nProtector ����
	void SendNpGameMonCheckCSAuth3(PVOID dwArg);
	// end 2015-01-07 by jwLee �������� nProtector ����

	// 2009-04-08 by bhsohn ���� ���ý�, ����ũ �� ��æƮ �� ������ �ǸŽ� ��� �޽��� ��� ��ȹ ����(K0000174)
	void AddMultiSelWarningMsg(UID64_t	UniqueNumber);
	// end 2009-04-08 by bhsohn ���� ���ý�, ����ũ �� ��æƮ �� ������ �ǸŽ� ��� �޽��� ��� ��ȹ ����(K0000174)

	// 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���
	CInfinityManager*	GetInfinityManager( void );
	// end 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���

   	// 2009. 11. 23 by jskim ���ҽ� �ε� ���� ����
	void LoadMeshPorcess();
	BOOL ObjectLoadingTimeChack();	
	BOOL IsEmptyLoadingGameDataList(void);
	void LoadingGameDataSort();
	structLoadingGameData* vecFrontGameData();
	void DeleteIsLoadingGameData(structLoadingGameData* nGameData);
	void vecPushBackGameData(structLoadingGameData* nGameData);
	void vecPushGameData(structLoadingGameData* i_pGameData);
	BOOL DeleteLoadingGameData(CSkinnedMesh *i_pSkinnedMesh);
	//end 2009. 11. 23 by jskim ���ҽ� �ε� ���� ����

	VOID ShotDownGameTime(); // 2012-07-17 by jhahn, �˴ٿ� �ð� ǥ��
	
	void FieldSocketCharacterPCBangPremiumApply(MSG_FC_CHARACTER_PCBANG_PREMIUN_APPLY* pMsg);	// 2012-10-16 by bhsohn NPlay PC�� ���
	void FieldSocketCharacterXignCodeAckPacket(MSG_FC_CHARACTER_XIGNCODE_ACK_PACKET* pMsg);	// 2012-10-17 by bhsohn XignCode�۾�
	
	// 2013-05-07 by bhsohn ��ĳ�� ���� ����Ű �߰�
	void FieldSocketShopAuthKey(MSG_FC_SHOP_AUTH_KEY* pMsg); 	
	// END 2013-05-07 by bhsohn ��ĳ�� ���� ����Ű �߰�

	// 2013-05-07 by bhsohn ��������Ʈ ������ �ý���
	void FieldSocketWarInflConseVictites(MSG_FC_WAR_INFLUENCE_CONSECUTIVE_VICTORITES* pMsg);
	void FieldSocketShopInflBuffOk(MSG_FC_SHOP_INFLUENCE_BUFF_OK* pMsg);
	// END 2013-05-07 by bhsohn ��������Ʈ ������ �ý���

	void SetCharacterChangeCurrentHPAndDamageBodyCondition(float fHP){CharacterChangeCurrentHPAndDamageBodyCondition(fHP);}			// 2013-06-25 by ssjung ������ ����Ʈ�� �ȳ����� ���� ����
	
protected:
	// MsgProc~
	int MsgProcGame( UINT uMsg, WPARAM wParam, LPARAM lParam );
	int MsgProcCity( UINT uMsg, WPARAM wParam, LPARAM lParam );
	int MsgProcCreate( UINT uMsg, WPARAM wParam, LPARAM lParam );
	// OnRecvFieldSocket~
	// 2007-11-22 by bhsohn �Ʒ��� ���ռ���
	//int		OnRecvFieldSocketMessage( DWORD dwMsgType );
	int		OnRecvFieldSocketMessage( DWORD wParam, UINT nSocketNotifyType);
	// 2007-11-22 by bhsohn �Ʒ��� ���ռ���
	//VOID	OnRecvFieldSocketWS_CONNECTED( USHORT nConnect );
	VOID	OnRecvFieldSocketWS_CONNECTED( USHORT nConnect, CFieldWinSocket* pFieldSocket);
	VOID	OnRecvFieldSocketWS_CLOSED(void);
	VOID	OnRecvCopyData(WPARAM wParam, COPYDATASTRUCT* pCopyDataStruct);
	// FieldSocket~
	VOID	FieldSocketConnectLoginOk(MSG_FC_CONNECT_LOGIN_OK * pMsg);
	VOID	FieldSocketCharacterGetCharacterOk(MSG_FC_CHARACTER_GET_CHARACTER_OK * pMsg);
	VOID	FieldSocketCharacterCreateOk(MSG_FC_CHARACTER_CREATE_OK* pMsg);
	VOID	FieldSocketCharacterDeleteOk(void);
	VOID	FieldSocketCharacterGetOtherInfoOk(MSG_FC_CHARACTER_GET_OTHER_INFO_OK* pMsg);
	VOID	FieldSocketCharacterGetMonsterInfoOk(MSG_FC_CHARACTER_GET_MONSTER_INFO_OK* pMsg);
	VOID	FieldSocketCharacterGameStartOk(MSG_FC_CHARACTER_GAMESTART_OK * pMsg);
	VOID	FieldSocketCharacterConnectGameStartOk(MSG_FC_CHARACTER_CONNECT_GAMESTART_OK * pMsg);
	// 2008-03-10 by bhsohn �Ʒ������� ��ȯ ��Ż ó��
	//VOID	FieldSocketCharacterGameEndOk(MSG_FC_CHARACTER_GAMEEND_OK * pMsg);
	VOID	FieldSocketCharacterGameEndOk(UINT nSocketNotifyType, MSG_FC_CHARACTER_GAMEEND_OK * pMsg);
	VOID	FieldSocketMoveOk( MSG_FC_MOVE_OK* pMsg);
	VOID	FieldSocketMonsterMoveOk(MSG_FC_MONSTER_MOVE_OK* pMsg);
	VOID	FieldSocketCharacterChangeHPDPSPEP(MSG_FC_CHARACTER_CHANGE_HPDPSPEP * pMsg);
	VOID	FieldSocketCharacterChangeCurrentHPDPSPEP(MSG_FC_CHARACTER_CHANGE_CURRENTHPDPSPEP * pMsg);
	VOID	FieldSocketCharacterChangeCurrentHP(MSG_FC_CHARACTER_CHANGE_CURRENTHP * pMsg);
	VOID	FieldSocketCharacterChangeCurrentDP(MSG_FC_CHARACTER_CHANGE_CURRENTDP * pMsg);
	VOID	FieldSocketCharacterChangeCurrentSP(MSG_FC_CHARACTER_CHANGE_CURRENTSP * pMsg);
	VOID	FieldSocketCharacterChangeCurrentEP(MSG_FC_CHARACTER_CHANGE_CURRENTEP * pMsg);
	VOID	FieldSocketCharacterChangeBodycondition(MSG_FC_CHARACTER_CHANGE_BODYCONDITION * pMsg);
	VOID	FieldSocketCharacterChangeUnitkind(MSG_FC_CHARACTER_CHANGE_UNITKIND * pMsg);
	VOID	FieldSocketCharacterPayWarPoint(MSG_FC_CHARACTER_PAY_WARPOINT* pMsg);
	VOID	FieldSocketCharacterUpdateSubleaderOk(MSG_FC_CHARACTER_UPDATE_SUBLEADER_OK * pMsg);
	VOID	FieldSocketPartyCreateOk(MSG_FC_PARTY_CREATE_OK* pMsg);
	VOID	FieldSocketPartyRequestInviteQuestion(MSG_FC_PARTY_REQUEST_INVITE_QUESTION* pMsg);
	VOID	FieldSocketPartyRequestInviteQuestion_THE_ARENA(MSG_FC_PARTY_REQUEST_INVITE_QUESTION_THE_ARENA* pMsg);	/// 2012-04-12 by jhseol, �Ʒ��� �߰����� - �ڵ���Ƽ : ��Ƽ ���� �غ�
	VOID	FieldSocketPartyAutoCreated_THE_ARENA(MSG_FC_PARTY_AUTO_CREATED_THE_ARENA* pMsg);	/// 2012-04-12 by jhseol, �Ʒ��� �߰����� - �ڵ���Ƽ : �ڵ����� ��Ƽ�� ������ ��Ŷ.
	VOID	FieldSocketPartyRejectInviteOk(MSG_FC_PARTY_REJECT_INVITE_OK* pMsg);
	VOID	FieldSocketPartyPutMember(MSG_FC_PARTY_PUT_MEMBER* pMsg);
	VOID	FieldSocketPartyUpdateMemberInfoAll(MSG_FC_PARTY_UPDATE_MEMBER_INFO_ALL* pMsg);
	VOID	FieldSocketPartyUpdateMemberInfoLevel(MSG_FC_PARTY_UPDATE_MEMBER_INFO_LEVEL* pMsg);
	VOID	FieldSocketPartyUpdateMemberInfoHP(MSG_FC_PARTY_UPDATE_MEMBER_INFO_HP* pMsg);
	VOID	FieldSocketPartyUpdateMemberInfoCurrentHP(MSG_FC_PARTY_UPDATE_MEMBER_INFO_CURRENT_HP* pMsg);
	VOID	FieldSocketPartyUpdateMemberInfoDP(MSG_FC_PARTY_UPDATE_MEMBER_INFO_DP* pMsg);
	VOID	FieldSocketPartyUpdateMemberInfoCurrentDP(MSG_FC_PARTY_UPDATE_MEMBER_INFO_CURRENT_DP* pMsg);
	VOID	FieldSocketPartyUpdateMemberInfoSP(MSG_FC_PARTY_UPDATE_MEMBER_INFO_SP* pMsg);
	VOID	FieldSocketPartyUpdateMemberInfoCurrentSP(MSG_FC_PARTY_UPDATE_MEMBER_INFO_CURRENT_SP* pMsg);
	VOID	FieldSocketPartyUpdateMemberInfoEP(MSG_FC_PARTY_UPDATE_MEMBER_INFO_EP* pMsg);
	VOID	FieldSocketPartyUpdateMemberInfoCurrentEP(MSG_FC_PARTY_UPDATE_MEMBER_INFO_CURRENT_EP* pMsg);
	VOID	FieldSocketPartyUpdateMemberInfoBodyCondition(MSG_FC_PARTY_UPDATE_MEMBER_INFO_BODYCONDITION* pMsg);
	VOID	FieldSocketCityCheckWarpStateOk(MSG_FC_CITY_CHECK_WARP_STATE_OK* pMsg);
	VOID	FieldSocketEventWarpOtherFieldServer(MSG_FC_EVENT_WARP * pMsg);
	VOID	FieldSocketEventWarpSameMap(MSG_FC_EVENT_WARP_SAME_MAP * pMsg);
	VOID	FieldSocketEventWarpSameFieldServer(MSG_FC_EVENT_WARP_SAME_FIELD_SERVER * pMsg);
	VOID	FieldSocketEventOtherWarped(MSG_FC_EVENT_OTHER_WARPED * pMsg);
	VOID	FieldSocketEventWarpConnectOk(MSG_FC_EVENT_WARP_CONNECT_OK* pMsg);
	VOID	FieldSocketStorePutItemHeader(MSG_FC_STORE_PUT_ITEM_HEADER* pMsg);
	VOID	FieldSocketStorePutItem(MSG_FC_STORE_PUT_ITEM* pMsg);
	VOID	FieldSocketStorePutItemDone(MSG_FC_STORE_PUT_ITEM_DONE* pMsg);
	VOID	FieldSocketCharacterChangeLevel(MSG_FC_CHARACTER_CHANGE_LEVEL* pMsg);
	VOID	FieldSocketCharacterChangeExp(MSG_FC_CHARACTER_CHANGE_EXP* pMsg);
	VOID	FieldSocketCharacterChangeStat(MSG_FC_CHARACTER_CHANGE_STAT * pMsg);
	VOID	FieldSocketCharacterChangeTotalGearStat(MSG_FC_CHARACTER_CHANGE_TOTALGEAR_STAT * pMsg);	
	VOID	FieldSocketCharacterChangeStatus(MSG_FC_CHARACTER_CHANGE_STATUS* pMsg);
	VOID	FieldSocketItemChangeWindowPositionOk(MSG_FC_ITEM_CHANGE_WINDOW_POSITION_OK * pMsg);
	VOID	FieldSocketMoveLandingOk(MSG_FC_MOVE_LANDING_OK* pMsg);
	VOID	FieldSocketMoveTakeOffOk(MSG_FC_MOVE_TAKEOFF_OK* pMsg);
	VOID	FieldSocketItemShowItem(MSG_FC_ITEM_SHOW_ITEM* pMsg);
	VOID	FieldSocketBattleDropMineOk(MSG_FC_BATTLE_DROP_MINE_OK* pMsg);
	VOID	FieldSocketItemGetItemOk(MSG_FC_ITEM_GET_ITEM_OK* pMsg);
	VOID	FieldSocketItemHideItem(MSG_FC_ITEM_HIDE_ITEM* pMsg);
	VOID	FieldSocketPartyPutItemOther(MSG_FC_PARTY_PUT_ITEM_OTHER* pMsg);
	VOID	FieldSocketItemGetItemFail(MSG_FC_ITEM_GET_ITEM_FAIL* pMsg);
	VOID	FieldSocketMissileMoveOk(MSG_FC_MISSILE_MOVE_OK* pMsg);
	VOID	FieldSocketCityRequestEnterBuildingOk(MSG_FC_CITY_REQUEST_ENTER_BUILDING_OK* pMsg);
	VOID	FieldSocketEventEnterBuilding(MSG_FC_EVENT_ENTER_BUILDING* pMsg);
	VOID	FieldSocketEventLeaveBuildingOk(MSG_FC_EVENT_LEAVE_BUILDING_OK* pMsg);
	VOID	FieldSocketShopCheckGiveTargetOK(MSG_FC_SHOP_CHECK_GIVE_TARGET_OK* pMsg);
	VOID	FieldSocketShopBuyCashItemOK(MSG_FC_SHOP_BUY_CASH_ITEM_OK* pMsg);
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
    VOID	FieldSocketShopBuyItemUpdate(MSG_FC_SHOP_BUY_ITEM_UPDATE* pMsg);
#endif
	
	VOID	FieldSocketShopPutItemHeader(MSG_FC_SHOP_PUT_ITEM_HEADER* pMsg);
	VOID	FieldSocketShopPutItem(MSG_FC_SHOP_PUT_ITEM* pMsg);
	VOID	FieldSocketShopPutItemDone(MSG_FC_SHOP_PUT_ITEM_DONE* pMsg);
	VOID	FieldSocketShopGetItemInfoOk(MSG_FC_SHOP_GET_ITEMINFO_OK* pMsg);
	VOID	FieldSocketShopBuyItemOk(MSG_FC_SHOP_BUY_ITEM_OK* pMsg);
	VOID	FieldSocketShopSellItemOk(MSG_FC_SHOP_SELL_ITEM_OK* pMsg);
	VOID	FieldSocketShopGetUsedItemPriceOk(MSG_FC_SHOP_GET_USED_ITEM_PRICE_OK* pMsg);
	VOID	FieldSocketItemThrowAwayItemOk(MSG_FC_ITEM_THROW_AWAY_ITEM_OK* pMsg);
	
	VOID	FieldSocketItemUseEnergyOk(MSG_FC_ITEM_USE_ENERGY_OK* pMsg);
	VOID	FieldSocketItemUseItemOk(MSG_FC_ITEM_USE_ITEM_OK* pMsg);
	VOID	FieldSocketItemUseCardItemMonstersummonNotify(MSG_FC_ITEM_USE_CARDITEM_MONSTERSUMMON_NOTIFY* pMsg);
	VOID	FieldSocketItemUseCardItemChangecharacternameNotify(MSG_FC_ITEM_USE_CARDITEM_CHANGECHARACTERNAME_NOTIFY* pMsg);
	VOID	FieldSocketItemUseCardItemSkillinitializeNotify(MSG_FC_ITEM_USE_CARDITEM_SKILLINITIALIZE_NOTIFY* pMsg);
	VOID	FieldSocketItemUseCardItemChangepilotfaceNotify(MSG_FC_ITEM_USE_CARDITEM_CHANGEPILOTFACE_NOTIFY* pMsg);
	VOID	FieldSocketItemUseCarditemGuildNotify(MSG_FC_ITEM_USE_CARDITEM_GUILD_NOTIFY* pMsg);	
	VOID	FieldSocketItemUseCarditemDeleteAllEnchant(MSG_FC_ITEM_DELETE_ALL_ENCHANT* pMsg);

	VOID	FieldSocketChatRegion(MSG_FC_CHAT_REGION* pMsg);
	VOID    FieldSocketChatCashAll(MSG_FC_CHAT_CASH_ALL* pMsg);
	VOID	FieldSocketChatMap(MSG_FC_CHAT_MAP* pMsg);
	VOID	FieldSocketChatArena(MSG_FC_CHAT_ARENA* pMsg);
	// 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���
	VOID	FieldSocketChatInfinity( MSG_FC_CHAT_INFINITY* pMsg );
	// end 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���


	VOID	FieldSocketTradeRequestTradeOk(MSG_FC_TRADE_REQUEST_TRADE_OK* pMsg);
	VOID	FieldSocketTradeAcceptTradeOk(MSG_FC_TRADE_ACCEPT_TRADE_OK* pMsg);
	VOID	FieldSocketTradeRejectTradeOk(MSG_FC_TRADE_REJECT_TRADE_OK* pMsg);
	VOID	FieldSocketTradeRejectTrading(MSG_FC_TRADE_REJECT_TRADING* pMsg);
	VOID	FieldSocketTradeShowTradeWindow(MSG_FC_TRADE_SHOW_TRADE_WINDOW* pMsg);
	VOID	FieldSocketTradeOkTradeOk(MSG_FC_TRADE_OK_TRADE_OK* pMsg);
	VOID	FieldSocketTradeCancelTradeOk(MSG_FC_TRADE_CANCEL_TRADE_OK* pMsg);
	VOID	FieldSocketTradeDeleteItem(MSG_FC_TRADE_DELETE_ITEM* pMsg);
public:
	VOID	FieldSocketTradeUpdateItemCount(MSG_FC_TRADE_UPDATE_ITEM_COUNT* pMsg);
	VOID	FieldSocketTradeInsertItem(MSG_FC_TRADE_INSERT_ITEM* pMsg);
protected:
	VOID	FieldSocketTradeTransItemOk(MSG_FC_TRADE_TRANS_ITEM_OK* pMsg);
	VOID	FieldSocketStoreUpdateEndurance(MSG_FC_STORE_UPDATE_ENDURANCE* pMsg);
	VOID	FieldSocketTradeSeeItemOk(MSG_FC_TRADE_SEE_ITEM_OK* pMsg);
	// 2010-06-15 by shcho&hslee ��ý��� - �ŷ� �� �� ���� ����
	VOID	FieldSocketTradeSeePetData(MSG_TRADE_PET_DATA* pMsg);
	VOID	FieldSocketTradeDeletePetData(MSG_TRADE_PET_DATA* pMsg); // �ŷ��� �� ���� ���� ó��
	VOID	FieldSocketTradeInsertPetData(MSG_FC_ITEM_PET_BASEDATA* pMsg); // �ŷ��� �� ���� �߰� ó��
	// end 2010-06-15 by shcho&hslee ��ý��� - �ŷ� �� �� ���� ����
	VOID	FieldSocketCitywarGetOccupyinfoOk(MSG_FC_CITYWAR_GET_OCCUPYINFO_OK* pMsg);
	VOID	FieldSocketCitywarBringSumoftexOk(MSG_FC_CITYWAR_BRING_SUMOFTEX_OK* pMsg);
	VOID	FieldSocketCitywarStartWar(MSG_FC_CITYWAR_START_WAR* pMsg);
	VOID	FieldSocketCitywarEndWar(MSG_FC_CITYWAR_END_WAR* pMsg);
	VOID	FieldSocketCharacterGetCashMoneyCountOk(MSG_FC_CHARACTER_GET_CASH_MONEY_COUNT_OK* pMsg);
	VOID	FieldSocketCharacterChangeCharacterModeOk(MSG_FC_CHARACTER_CHANGE_CHARACTER_MODE_OK* pMsg);
	VOID	FieldSocketSkillUseSkill(MSG_FC_SKILL_USE_SKILL_OK *pMsg);
	VOID	FieldSocketInvenItempHidePetData(MSG_FC_ITEM_NOTIFY_WINDOW_POSITION* pMsg);	   //2011-10-06 by jhahn ��Ʈ�� ������ �ý���
	VOID	FieldSocketSkillCancelSkillOK(MSG_FC_SKILL_CANCEL_SKILL_OK * pMsg);
	VOID	FieldSocketInvalidateSkill(MSG_FC_SKILL_INVALIDATE_SKILL *pMsg);
	VOID	FieldSocketCharacterGetAccountUniqueNumberOk(MSG_FC_CHARACTER_GET_ACCOUNTUNIQUENUMBER_OK* pMsg);
	VOID	FieldSocketBattleRequestPkOk(MSG_FC_BATTLE_REQUEST_PK_OK* pMsg);
	VOID	FieldSocketBattleCancelPK(void);
	VOID	FieldSocketBattleDropBundleOk(MSG_FC_BATTLE_DROP_BUNDLE_OK* pMsg);
	VOID	FieldSocketCharacterDeleteOtherInfo(MSG_FC_CHARACTER_DELETE_OTHER_INFO* pMsg);
	VOID	FieldSocketCharacterMonsterCreated(MSG_FC_MONSTER_CREATED* pMsg);
	VOID	FieldSocketMonsterChangeBodycondition(MSG_FC_MONSTER_CHANGE_BODYCONDITION* pMsg);
	VOID	FieldSocketCharacterChangeMonsterHP(MSG_FC_MONSTER_CHANGE_HP* pMsg);
	VOID	FieldSocketCharacterShowEffectOk(MSG_FC_CHARACTER_SHOW_EFFECT_OK* pMsg);
	VOID	FieldSocketBattleRequestP2PPkOk(MSG_FC_BATTLE_REQUEST_P2P_PK_OK* pMsg);
	VOID	FieldSocketBattleAcceptRequestP2PPkOk(MSG_FC_BATTLE_ACCEPT_REQUEST_P2P_PK_OK* pMsg);
	VOID	FieldSocketBattleRejectRequestP2PPkOk(MSG_FC_BATTLE_REJECT_REQUEST_P2P_PK_OK* pMsg);
	VOID	FieldSocketBattleSurrenderP2PPkOk(MSG_FC_BATTLE_SURRENDER_P2P_PK_OK* pMsg);
	VOID	FieldSocketCharacterChangeCharacterMent(MSG_FC_CHARACTER_CHANGE_CHARACTER_MENT* pMsg);
	VOID	FieldSocketBattleRejectSurrenderP2PPkOk(MSG_FC_BATTLE_REJECT_SURRENDER_P2P_PK_OK* pMsg);
	VOID	FieldSocketBattleEndP2PPk(MSG_FC_BATTLE_END_P2P_PK* pMsg);
	VOID	FieldSocketCharacterChangePKPoint(MSG_FC_CHARACTER_CHANGE_PKPOINT* pMsg);
	VOID	FieldSocketBattleDropDummyOk(MSG_FC_BATTLE_DROP_DUMMY_OK* pMsg);
	VOID	FieldSocketBattleDeleteDummyOK(MSG_FC_BATTLE_DELETE_DUMMY_OK* pMsg);
	VOID	FieldSocketBattleExplodeDummyOK(MSG_FC_BATTLE_EXPLODE_DUMMY_OK* pMsg);
	VOID	FieldSocketBattleAttackHideItem(MSG_FC_BATTLE_ATTACK_HIDE_ITEM* pMsg);
	VOID	FieldSocketBattleAttackExplodeItem(MSG_FC_BATTLE_ATTACK_EXPLODE_ITEM* pMsg);
	VOID	FieldSocketMonsterHide(MSG_FC_MONSTER_HIDE* pMsg);
	VOID	FieldSocketMonsterShow(MSG_FC_MONSTER_SHOW* pMsg);
	VOID	FieldSocketBattleDropFixerOk(MSG_FC_BATTLE_DROP_FIXER_OK* pMsg);
	VOID	FieldSocketInfoGetItemInfoOk(ITEM & item);
	VOID	FieldSocketInfoGetRareItemInfoOk(RARE_ITEM_INFO & rareItem);
	VOID	FieldSocketInfoGetMonsterInfoOk(MSG_FC_INFO_GET_MONSTER_INFO_OK *mon);
	VOID	FieldSocketInfoGetMapObjectInfoOk(MAPOBJECTINFO & obj);
	VOID	FieldSocketBattleAttackHideItemWKind(MSG_FC_BATTLE_ATTACK_HIDE_ITEM_W_KIND* pMsg);
	VOID	FieldSocketBattleAttackExplodeItemWKind(MSG_FC_BATTLE_ATTACK_EXPLODE_ITEM_W_KIND* pMsg);
	VOID	FieldSocketConnectSyncTime(MSG_FC_CONNECT_SYNC_TIME* pMsg);
	VOID	FieldSocketItemReloadItemInfo(void);
	VOID	FieldSocketItemUseEnchantOk(MSG_FC_ITEM_USE_ENCHANT_OK* pMsg);
	VOID	FieldSocketItemPutEnchant(MSG_FC_ITEM_PUT_ENCHANT* pMsg);
	VOID	FieldSocketQuestRequestStartResult(MSG_FC_QUEST_REQUEST_START_RESULT* pMsg);
	VOID	FieldSocketQuestRequestSuccessResult(MSG_FC_QUEST_REQUEST_SUCCESS_RESULT* pMsg);
	VOID	FieldSocketQuestRequestSuccessCheckResult(MSG_FC_QUEST_REQUEST_SUCCESS_CHECK_RESULT* pMsg);
	VOID	FieldSocketQuestPutAllQuest(MSG_FC_QUEST_PUT_ALL_QUEST* pMsg);
	VOID	FieldSocketSkillSetupSkillOk(MSG_FC_SKILL_SETUP_SKILL_OK* pMsg);
	VOID	FieldSocketRequestRequestOk(MSG_FC_REQUEST_REQUEST_OK* pMsg);
	VOID	FieldSocketRequestRejectRequestOk(MSG_FC_REQUEST_REJECT_REQUEST_OK* pMsg);
	VOID	FieldSocketRequestCancelRequest(MSG_FC_REQUEST_CANCEL_REQUEST* pMsg);
	VOID	FieldSocketRequestAcceptRequestOk(MSG_FC_REQUEST_ACCEPT_REQUEST_OK* pMsg);
	VOID	FieldSocketPartyBattleStart(MSG_FC_PARTY_BATTLE_START* pMsg);
	VOID	FieldSocketPartyBattleEnd(MSG_FC_PARTY_BATTLE_END* pMsg);
	VOID	FieldSocketQuestUpdateMonsterCount(MSG_FC_QUEST_UPDATE_MONSTER_COUNT* pMsg);
	VOID	FieldSocketQuestPutAllQuestMonsterCount(MSG_FC_QUEST_PUT_ALL_QUEST_MONSTER_COUNT* pMsg);
	VOID	FieldSocketItemResetSkillEnchantToLoadedItem(void);
	VOID	FieldSocketBattleToggleShieldResult(MSG_FC_BATTLE_TOGGLE_SHIELD_RESULT* pMsg);
	VOID	FieldSocketBattleToggleDecoyOk(MSG_FC_BATTLE_TOGGLE_DECOY_OK* pMsg);
	VOID	FieldSocketBattlePriBulletReloaded(MSG_FC_BATTLE_PRI_BULLET_RELOADED* pMsg);
	VOID	FieldSocketBattleSecBulletReloaded(MSG_FC_BATTLE_SEC_BULLET_RELOADED* pMsg);
	VOID	FieldSocketEventChangeWeather(MSG_FC_EVENT_CHANGE_WEATHER* pMsg);
	VOID	FieldSocketItemUpdateItemPos(MSG_FC_ITEM_UPDATE_ITEM_POS* pMsg);
	VOID	FieldSocketCharacterGetOtherRenderInfoOk(MSG_FC_CHARACTER_GET_OTHER_RENDER_INFO_OK* pMsg);
	VOID	FieldSocketInfoGetBuildingNPCInfoOk(MSG_FC_INFO_GET_BUILDINGNPC_INFO_OK* pMsg);
	VOID	FieldSocketEventSuggestChannels(MSG_FC_EVENT_SUGGEST_CHANNELS* pMsg);
	VOID	FieldSocketCityGetBuildingListOk(MSG_FC_CITY_GET_BUILDING_LIST_OK* pMsg);
	VOID	FieldSocketGetShopWarpTargetMapListOk(MSG_FC_EVENT_GET_SHOP_WARP_TARGET_MAP_LIST_OK* pMsg);
	VOID	FieldSocketAdminGetServerStatOk(MSG_FC_ADMIN_GET_SERVER_STAT_OK* pMsg);
	VOID	FieldSocketConnectClose(MSG_FC_CONNECT_CLOSE* pMsg);
	VOID	FieldSocketString128(MSG_FC_STRING_128* pMsg);
	VOID	FieldSocketString256(MSG_FC_STRING_256* pMsg);
	VOID	FieldSocketString512(MSG_FC_STRING_512* pMsg);
	VOID	FieldSocketError(MSG_ERROR* pMsg);
	VOID	FieldSocketInvalidPacket(char* pPacket);
	VOID	FieldSocketMonsterSkillUseSkill(MSG_FC_MONSTER_SKILL_USE_SKILL* pMsg);
	VOID	FieldSocketMonsterSkillEndSkill(MSG_FC_MONSTER_SKILL_END_SKILL* pMsg);
	VOID	FieldSocketInfoGetSimpleItemInfoOk(MEX_ITEM_INFO & ItemInfo);
	VOID	FieldSocketInfoGetEnchantCostOk(MSG_FC_INFO_GET_ENCHANT_COST_OK* pMsg);
	VOID	FieldSocketItemMixItemsResult(MSG_FC_ITEM_MIX_ITEMS_RESULT* pMsg);
	VOID	FieldSocketGuildGetWarInfoOk(MSG_FC_GUILD_GET_WAR_INFO_OK* pMsg);
	VOID	FieldSocketStoreMoveItemOk(MSG_FC_STORE_MOVE_ITEM_OK* pMsg);
	VOID	FieldSocketCharacterGetOtherParamfactorOk(MSG_FC_CHARACTER_GET_OTHER_PARAMFACTOR_OK* pMsg);
	VOID	FieldSocketStoreUpdatePossess(MSG_FC_STORE_UPDATE_POSSESS* pMsg);
	VOID	FieldSocketStoreUpdateRareFix(MSG_FC_STORE_UPDATE_RARE_FIX* pMsg);
	VOID	FieldSocketQuestDiscardQuestOk(MSG_FC_QUEST_DISCARD_QUEST_OK* pMsg);
	VOID	FieldSocketTimerStartTimer(MSG_FC_TIMER_START_TIMER* pMsg);
	VOID	FieldSocketTimerStopTimer(MSG_FC_TIMER_STOP_TIMER* pMsg);
	VOID	FieldSocketTimerUpdateTimer(MSG_FC_TIMER_UPDATE_TIMER* pMsg);
	VOID	FieldSocketTimerPauseTimer(MSG_FC_TIMER_PAUSE_TIMER* pMsg);
	VOID	FieldSocketTimerContinueTimer(MSG_FC_TIMER_CONTINUE_TIMER* pMsg);
	VOID	FieldSocketSKillPrepareUseOk(MSG_FC_SKILL_PREPARE_USE_OK* pMsg);
	VOID	FieldSocketCancelPrepareOk(MSG_FC_SKILL_CANCEL_PREPARE_OK* pMsg);
	VOID	FieldSocketMoveWeaponVelOk(MSG_FC_MOVE_WEAPON_VEL_OK* pMsg);
	VOID	FieldSocketCountdownStart(MSG_FC_COUNTDOWN_START* pMsg);
	VOID	FieldSocketBattleShowDamage(MSG_FC_BATTLE_SHOW_DAMAGE* pMsg);
	VOID	FieldSocketItemUseBuffOk(MSG_FC_ITEM_USE_INFLUENCE_BUFF_OK* pMsg);
	VOID	FieldSocketItemUseInfluenceGameEventOk(MSG_FC_ITEM_USE_INFLUENCE_GAMEEVENT_OK* pMsg);
	VOID	FieldSocketShopBuyWarPointItemOK(MSG_FC_SHOP_BUY_WARPOINT_ITEM_OK* pMsg);


	VOID	FieldSocketBattleAttackOk(MSG_FC_BATTLE_ATTACK_OK* pMsg);
	VOID	FieldSocketBattleAttackFindOk(MSG_FC_BATTLE_ATTACK_FIND_OK* pMsg);
	VOID	FieldSocketBattleMineAttackOk(MSG_FC_BATTLE_MINE_ATTACK_OK* pMsg);
	VOID	FieldSocketBattleMineAttackFindOk(MSG_FC_BATTLE_MINE_ATTACK_FIND_OK* pMsg);
	VOID	FieldSocketObjectChangeBodyConditionOk(MSG_FC_OBJECT_CHANGE_BODYCONDITION_OK* pMsg);
	VOID	FieldSocketBattleAttackEvasionOk(MSG_FC_BATTLE_ATTACK_EVASION_OK* pMsg);
	VOID	FieldSocketWarNotifyInvasion(MSG_FC_WAR_NOTIFY_INVASION *pMsg);
	VOID	FieldSocketWarNotifyInfluenceMonsterDead(MSG_FC_WAR_NOTIFY_INFLUENCE_MONSTER_DEAD *pMsg);
	VOID	FieldSocketWarNotifyInfluenceAutoMonsterDead(MSG_FC_WAR_NOTIFY_INFLUENCE_MONSTER_DEAD *pMsg); // 2007-02-15 by bhsohn �� �ڵ� �Ҹ�� �̺�Ʈ ����.
	VOID	FieldSocketWarNotifyInfluenceMonsterIvasion(MSG_FC_WAR_NOTIFY_INFLUENCE_MONSTER_INVASION* pMsg);
	VOID	FieldSocketWarBossMonsterSummonDataInvasion(MSG_FC_WAR_BOSS_MONSTER_SUMMON_DATA* pMsg);
	VOID	FieldSocketWarSignBoardInsertString(MSG_FC_WAR_SIGN_BOARD_INSERT_STRING* pMsg);
	VOID	FieldSocketWarReqSignBoardStringListOk(MSG_FC_WAR_REQ_SIGN_BOARD_STRING_LIST_OK* pMsg);
	VOID	FieldSocketWarSignBoardDeleteString(MSG_FC_WAR_SIGN_BOARD_DELETE_STRING* pMsg);
	VOID	FieldSocketWarUpdateContributionPointOk(MSG_FC_WAR_UPDATE_CONTRIBUTION_POINT_OK* pMsg);
	VOID	FieldSocketWarJacoMonsterSummon(MSG_FC_WAR_JACO_MONSTER_SUMMON* pMsg);
	VOID 	FieldSocketWarInfluenceData(MSG_FC_WAR_INFLUENCE_DATA* pMsg);
	VOID	FieldSocketEventNotifyMsgGetOK(MSG_FC_EVENT_NOTIFY_MSG_GET_OK* pMsg);
	VOID	FieldSocketCityWarInfoInfluenceOK(MSG_FC_CITY_WARINFO_INFLUENCE_OK* pMsg);
	VOID	FieldSocketCityWarInfoOutPostOK(MSG_FC_CITY_WARINFO_OUTPOST_OK * pMsg);
	VOID	FieldSocketInfoGetGuildMarkOK(MSG_FC_INFO_GET_GUILDMARK_OK* pMsg);
	
	// 2007-07-04 by bhsohn ���۷����� �߰�
	VOID	FieldSocketWarStrategypointMonsterSummon(MSG_FC_WAR_STRATEGYPOINT_MONSTER_SUMMON* pMsg);

	VOID	FieldSocketAuctionInsertItem(MSG_FC_AUCTION_INSERT_ITEM* pMsg);
	VOID	FieldSocketAuctionRegisterItemOk(MSG_FC_AUCTION_REGISTER_ITEM_OK* pMsg);
	VOID	FieldSocketAuctionCancerRegisterOk(MSG_FC_AUCTION_CANCEL_REGISTER_OK* pMsg);
	VOID	FieldSocketAuctionBuyItemOk(MSG_FC_AUCTION_BUY_ITEM_OK* pMsg);
	VOID	FieldSocketAuctionPutEnchant(MSG_FC_AUCTION_PUT_ENCHANT* pMsg);

	VOID	FieldSocketMoveLockonOk(MSG_FC_MOVE_LOCKON_OK* pMsg);
	VOID	FieldSocketMoveUnlockonOk(MSG_FC_MOVE_UNLOCKON_OK* pMsg);
	VOID	FieldSocketMoveRolling(MSG_FC_MOVE_ROLLING_OK *pMsg);
	VOID	FieldSocketInfoGetCurrentMapInfoOk(MSG_FC_INFO_GET_CURRENT_MAP_INFO_OK* pMsg);
	VOID	FieldSocketCharacterCashPremiumCardInfo(MSG_FC_CHARACTER_CASH_PREMIUM_CARD_INFO* pMsg);
	VOID	FieldSocketStoreInsertUsingItem(MSG_FC_STORE_INSERT_USINGITEM* pMsg);
	VOID	FieldSocketStoreDeleteUsingItem(MSG_FC_STORE_DELETE_USINGITEM* pMsg);
	VOID	FieldSocketGuildSummonMember(MSG_FC_GUILD_SUMMON_MEMBER* pMsg);
	VOID	FieldSocketItemUseCarditemRestoreNotify(MSG_FC_ITEM_USE_CARDITEM_RESTORE_NOTIFY* pMsg);
	VOID	FieldSocketItemUseCarditemGuildsummonNotify(MSG_FC_ITEM_USE_CARDITEM_GUILDSUMMON_NOTIFY* pMsg);
	// 2008-03-14 by bhsohn �������� ���� ���Ǿƿ�� ó��
	VOID	FieldSocketInfoGetHappyHourEventInfoOk(BOOL bLevelUp, MSG_FC_INFO_GET_HAPPY_HOUR_EVENT_INFO_OK* pMsg);
	VOID	FieldSocketInfoGetGameEventInfoOk(MSG_FC_INFO_GET_GAME_EVENT_INFO_OK* pMsg);
	VOID	FieldSocketMonsterTutorialMonsterDeadNotify(MSG_FC_MONSTER_TUTORIAL_MONSTER_DEAD_NOTIFY* pMsg);

	// 2009. 09. 18 by ckPark ���Ǵ�Ƽ �ʵ� HP�� ���� ���� ��ȭ
	VOID	FieldSocketMonsterHPTalk( MSG_FC_MONSTER_HPTALK* pMsg );
	// end 2009. 09. 18 by ckPark ���Ǵ�Ƽ �ʵ� HP�� ���� ���� ��ȭ
// 2011-02-08 by jhahn EP4 Ʈ����  �ý��� ������Ʈ ����			
	VOID	FieldObjectChangeOK(MSG_FC_OBJECT_CHANGE* pMsg);
	VOID	FieldSocketShopClose(MSG_FC_SHOP_CLOSE* pMsg);
	VOID	FieldSocketSetLimitTime( MSG_FC_SET_LIMITTIME* pMsg);
//end 2011-02-08 by jhahn EP4 Ʈ����  �ý��� ������Ʈ ����			

	// 2009. 09. 21 by ckPark ���Ǵ�Ƽ �ʵ� ���� ��ų ����
	VOID	FieldSocketMonsterSkill( MSG_FC_MONSTER_SKILL* pMsg );
	VOID	FieldSocketMonsterMonsterBarrierUsing( MSG_FC_BATTLE_MONSTER_BARRIER_USING* pMsg );
	VOID	FieldSocketMonsterMonsterBarrierUse( MSG_FC_BATTLE_MONSTER_BARRIER_USE* pMsg );
	VOID	FieldSocketCharacterDebuffDotInfo( MSG_FC_CHARACTER_DEBUFF_DOT_INFO_OK* pMsg );
	VOID	FieldSocketCharacterDebuffDotApply( MSG_FC_CHARACTER_DEBUFF_DOT_APPLYING* pMsg );
	VOID	FieldSocketCharacterDebuffDotRelease( MSG_FC_CHARACTER_DEBUFF_DOT_RELEASE* pMsg );
	// end 2009. 09. 21 by ckPark ���Ǵ�Ƽ �ʵ� ���� ��ų ����
	//2011-02-08 by jhahn EP4 Ʈ����  �ý���
	VOID	FieldSocketTriggerMapBuffSkill(MSG_FC_TRIGGER_MAP_BUFF_SKILL* pMsg );				//2011-10-24 by jhahn Ʈ���� �ý��� 
	//end 2011-02-08 by jhahn EP4 Ʈ����  �ý���

	// 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���
	VOID	FieldSocketInfinityModeListOK( MSG_FC_INFINITY_MODE_LIST_OK* pMsg );
	VOID	FieldSocketInfinityReadyListOK( MSG_FC_INFINITY_READY_LIST_OK* pMsg );
	VOID	FieldSocketInfinityCreateOK( MSG_FC_INFINITY_CREATE_OK* pMsg );
	VOID	FieldSocketInfinityMemberInfoList( MSG_FC_INFINITY_MEMBER_INFO_LIST_OK* pMsg );
	VOID	FieldSocketInfinityLeaveOK( MSG_FC_INFINITY_LEAVE_OK* pMsg );
	VOID	FieldSocketInfinityBanOK( MSG_FC_INFINITY_BAN_OK* pMsg );
	VOID	FieldSocketInfinityJoinRequest( MSG_FC_INFINITY_JOIN_REQUEST_MASTERUSER* pMsg );
	VOID	FieldSocketInfinityJoinOK( MSG_FC_INFINITY_JOIN_OK* pMsg );
	VOID	FieldSocketInfinityEnter( MSG_FC_INFINITY_ENTER* pMsg );
	VOID	FieldSocketInfinityReadyOK( MSG_FC_INFINITY_READY_OK* pMsg );
	VOID	FieldSocketInfinityReadyCancelOK( MSG_FC_INFINITY_READY_CANCEL_OK* pMsg );
	VOID	FieldSocketInfinityChangeMaster( MSG_FC_INFINITY_CHANGE_MASTER_OK* pMsg );
	VOID	FieldSocketInfinityCinema( MSG_FC_INFINITY_CINEMA* pMsg );
	VOID	FieldSocketInfinitySuccessFIN( void );
	VOID	FieldSocketInfinityFailFIN( void );
	VOID	FieldSocketInfinityReadyFinishMainSvrStart( void );
	VOID	FieldSocketInfinityTenderDropItemInfo( MSG_FC_INFINITY_TENDER_DROPITEM_INFO* pMsg );
	VOID	FieldSocketInfinityTenderStart( MSG_FC_INFINITY_TENDER_START* pMsg );
	VOID	FieldSocketInfinityPutInTenderOK( MSG_FC_INFINITY_TENDER_PUT_IN_TENDER_OK* pMsg );
	VOID	FieldSocketInfinityTenderResult( MSG_FC_INFINITY_TENDER_RESULT* pMsg );
	VOID	FieldSocketInfinityTenderResultTimeOver( MSG_FC_INFINITY_TENDER_RESULT_TIMEOVER* pMsg );
	VOID	FieldSocketInfinityTenderResultAllGiveUp( MSG_FC_INFINITY_TENDER_RESULT_ALLGIVEUP* pMsg );
	VOID	FieldSocketInfinityApplyResistanceItem( MSG_FC_INFO_APPLY_RESISTANCE_ITEM* pMsg );
	VOID	FieldSocketInfinityShopItemHeader( void );
	VOID	FieldSocketInfinityShopItem( MSG_FC_SHOP_INFINITY_ITEM* pMsg );
	VOID	FieldSocketInfinityShopItemDone( void );
	VOID	FieldSocketInfinityChangeLimitTime( MSG_FC_INFINITY_CHANGE_LIMITTIME* pMsg );
	VOID	FieldSocketInfinityJoinCancelRequestMaster( MSG_FC_INFINITY_JOIN_CANCEL_REQUEST_MASTERUSER* pMsg );
	VOID	FieldSocketInfinityRequestRestartByDisconnect( void );
	VOID	FieldSocketInfinityDeletedCinema( MSG_FC_INFINITY_DELETED_CINEMA* pMsg );
	VOID	FieldSocketInfinityEnterByDisConnect( MSG_FC_INFINITY_ENTER_BY_DISCONNECT* pMsg );
	VOID	FieldSocketInfinityPartyAutoCreated( MSG_FC_PARTY_AUTO_CREATED* pMsg );
	// end 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���

	// 2010. 05. 19 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����. (��ȣó�� + ���� ó��(����) )
	VOID	FieldSocketInfinityRegsiterDifficultyBonusInfoListData ( MSG_INFINITY_DIFFICULTY_LIST_OK* pMsg );
	VOID	FieldSocketInfinityChangeRoomDifficultyLevelOK( MSG_FC_INFINITY_CHANGE_DIFFICULTY_LEVEL_OK* pMsg );
	// End 2010. 05. 19 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����. (��ȣó�� + ���� ó��(����) )

	// 2010. 05. 31 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����. (������Ʈ ���� �뷱�� ���� ���� ����.)
	VOID	FieldSocketInfinityReadyCancelAllOK ( MSG_FC_INFINITY_READY_CANCEL_ALL_OK* pMsg );
	// End 2010. 05. 31 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����. (������Ʈ ���� �뷱�� ���� ���� ����.)

	// 2010. 07. 27 by hsLee ���Ǵ�Ƽ 2�� ���� ��� �ó׸� ���� ��ŵ ó��.
	VOID	FieldSocketInfinityCinemaSkip ( MSG_FC_INFINITY_SKIP_ENDING_CINEMA_OK * pMsg );
	// End 2010. 07. 27 by hsLee ���Ǵ�Ƽ 2�� ���� ��� �ó׸� ���� ��ŵ ó��.

	// 2010. 02. 11 by ckPark �ߵ��� ����������
	VOID	FieldSocketInfoApplyDestParam( MSG_FC_INFO_APPLY_DESTPARAM* pMsg );
	VOID	FieldSocketInfoApplyDestParamList( MSG_FC_INFO_APPLY_DESTPARAM_LIST* pMsg );
	VOID	FieldSocketItemEndCoolItemOK( MSG_FC_ITEM_END_COOLINGTIME_ITEM_OK* pMsg );
	VOID	FieldSocketItemGetCoolTimeInfoOK( MSG_FC_ITEM_GET_COOLINGTIME_INFO_OK* pMsg );
	VOID	FieldSocketItemUseInvokingWearItemBuff( MSG_FC_ITEM_USE_INVOKING_WEAR_ITEM_BUFF* pMsg );
	// end 2010. 02. 11 by ckPark �ߵ��� ����������

	// 2010. 03. 15 by ckPark ���Ǵ�Ƽ �ʵ� 2��(���� ó��)
	VOID	FieldSocketInfinityChangeAliveForGameClearMonsterHP( MSG_FC_INFINITY_CHANGE_ALIVE_FOR_GAMECLEAR_MONSTERHP* pMsg );
	VOID	FieldSocketMonsterCreatedAliveForGameClear( MSG_FC_MONSTER_CREATED_ALIVE_FOR_GAMECLEAR* pMsg );
	// end 2010. 03. 15 by ckPark ���Ǵ�Ƽ �ʵ� 2��(���� ó��)

	// 2010. 03. 18 by ckPark ���Ǵ�Ƽ �ʵ� 2��(���� ��ų �߰�)
	VOID	FieldSocketMonsterCancelSkill( MSG_FC_MONSTER_SKILL_CANCEL* pMsg );
	// end 2010. 03. 18 by ckPark ���Ǵ�Ƽ �ʵ� 2��(���� ��ų �߰�)

	VOID	FieldSocketCharacterTutorialSkipOk(MSG_FC_CHARACTER_TUTORIAL_SKIP_OK* pMsg);
	VOID	FieldSocketTutorialStartOK(MSG_FC_TUTORIAL_START_OK* pMsg);
	VOID	FieldSocketTutorialCompleteOK(MSG_FC_TUTORIAL_COMPLETE_OK* pMsg);
	VOID	FieldSocketTutorialEndOK();
	VOID	FieldSocketCharacterDeadNotify(MSG_FC_CHARACTER_DEAD_NOTIFY* pMsg);
	VOID	FieldSocketCitywarMonsterDead(MSG_FC_CITYWAR_MONSTER_DEAD* pMsg);
	VOID	FieldSocketCharacterChangeInfluenceType(MSG_FC_CHARACTER_CHANGE_INFLUENCE_TYPE* pMsg);
	VOID	FieldSocketCharacterChangePropensity(MSG_FC_CHARACTER_CHANGE_PROPENSITY* pMsg);
	VOID	FieldSocketRequestRepairOk(MSG_FC_SHOP_REQUEST_REPAIR_OK* pMsg);
	VOID	FieldSocketSkillConfirmUseAck(MSG_FC_SKILL_CONFIRM_USE_ACK* pMsg);
	VOID	FieldSocketSkillConfirmUse(MSG_FC_SKILL_CONFIRM_USE* pMsg);
	VOID	FieldSocketStoreUpdateItemStorage(MSG_FC_STORE_UPDATE_ITEMSTORAGE* pMsg);
	VOID	FieldSocketShopBuyColorItemOk(MSG_FC_SHOP_BUY_COLOR_ITEM_OK* pMsg);
	VOID	FieldSocketStoreUpdateUsingItem(MSG_FC_STORE_UPDATE_USINGITEM* pMsg);
	VOID	FieldSocketStoreUpdateItemNum(MSG_FC_STORE_UPDATE_ITEMNUM* pMsg);
	VOID	FieldSocketStoreLogGuildItemOK(MSG_FC_STORE_LOG_GUILD_ITEM_OK* pMsg);
	VOID	FieldSocketStoreLogGuildItemOKHeader();
	VOID	FieldSocketStoreLogGuildItemOKDone();
	VOID	FieldSocketEventCallWarpEventReqeust(MSG_FC_EVENT_CALL_WARP_EVENT_REQUEST* pMsg);

	// 2007-03-29 by dgwoo ��ۿ� ������ ���.
	VOID	FieldSocketCharacterObserverStartOK(MSG_FC_CHARACTER_OBSERVER_START* pMsg);
	VOID	FieldSocketCharacterObserverEndOK(MSG_FC_CHARACTER_OBSERVER_END* pMsg);
	VOID	FieldSocketCharacterObserverRegOK(MSG_FC_CHARACTER_OBSERVER_REG* pMsg);
	VOID	FieldSocketCharacterObserverInfoOK(MSG_FC_CHARACTER_OBSERVER_INFO* pMsg);

	VOID	FieldSocketArenaWatchReady(MSG_FC_ARENA_WATCH_READY* pMsg);
	VOID 	FieldSocketArenaWatchStart(MSG_FC_ARENA_WATCH_START* pMsg);
	VOID	FieldSocketArenaWatchEnd();
	VOID	FieldSocketArenaWatchRemoveUser(MSG_FC_ARENA_WATCH_REMOVE_USER* pMsg);
	VOID	FieldSocketCharacterWatchInfo(MSG_FC_CHARACTER_WATCH_INFO* pMsg);

	// 2007-08-16 by dgwoo ��������
	VOID	FieldSocketOutPostWarBefore(MSG_FC_OUTPOST_WAR_BEFORE* pMsg);
	VOID	FieldSocketOutPostWarStart(MSG_FC_OUTPOST_WAR_START* pMsg);
	VOID	FieldSocketOutPostProtectorDestroy(MSG_FC_OUTPOST_PROTECTOR_DESTROY* pMsg);
	VOID	FieldSocketOutPostResetStartOk(MSG_FC_OUTPOST_RESET_START_OK* pMsg);
	VOID	FieldSocketOutPostResetDestroy(MSG_FC_OUTPOST_RESET_DESTROY* pMsg);
	VOID	FieldSocketOutPostResetSuccess(MSG_FC_OUTPOST_RESET_SUCCESS* pMsg);
	VOID	FieldSocketOutPostWarEnd(MSG_FC_OUTPOST_WAR_END* pMsg);
	VOID	FieldSocketInfoNoticeRequestOk(MSG_FC_INFO_NOTICE_REQUEST_OK* pMsg);
	VOID	FieldSocketInfoNoticeRegOk();
	VOID	FieldSocketInfoNoticeModifyOk();
	VOID	FieldSocketInfoExpediencyfundPayBackOk(MSG_FC_INFO_EXPEDIENCYFUND_PAYBACK_OK* pMsg);
	VOID	FieldSocketInfoExpediencyfundRequestOk(MSG_FC_INFO_EXPEDIENCYFUND_REQUEST_OK* pMsg);
	VOID	FieldSocketOutPostNextWarInfoRequestOk(MSG_FC_OUTPOST_NEXTWAR_INFO_REQUEST_OK* pMsg);
	VOID 	FieldSocketOutPostNextWarSetTimeOk(MSG_FC_OUTPOST_NEXTWAR_SET_TIME_OK* pMsg);
	VOID	FieldSocketOutPostWarInfo(MSG_FC_OUTPOST_WAR_INFO* pMsg);

	// 2007-09-19 by dgwoo �ڷ���Ʈ.
	VOID	FieldSocketEventTeleportBuildComplete(MSG_FC_EVENT_TELEPORT_BUILDCOMPLETE* pMsg);
	VOID	FieldSocketEventTeleportDestroy(MSG_FC_EVENT_TELEPORT_DESTROY* pMsg);

	// 2007-04-19 by dgwoo �Ʒ��� �ý���.
	VOID	FieldSocketArenaRequestTeamOK(MSG_FC_ARENA_REQUEST_TEAM_OK* pMsg);
	VOID	FieldSocketArenaCreateTeamOK(MSG_FC_ARENA_CREATE_TEAM_OK* pMsg);
	VOID	FieldSocketArenaEnterTeamOK(MSG_FC_ARENA_ENTER_TEAM_OK* pMsg);
	VOID	FieldSocketArenaTeamMemberList(MSG_FC_ARENA_TEAM_MEMBER_LIST* pMsg);
	VOID	FieldSocketArenaReaveTeamOK();
	VOID	FieldSocketArenaTeamReady(MSG_FC_ARENA_TEAM_READY* pMsg);
	VOID	FieldSocketArenaEnterRoom(MSG_FC_ARENA_ENTER_ROOM* pMsg);
	VOID	FieldSocketArenaRoomWarStart();
	VOID	FieldSocketArenaRoomWarInfo(MSG_FC_ARENA_ROOM_WAR_INFO* pMsg);
	VOID	FieldSocketArenaRoomWarFinishHeader(MSG_FC_ARENA_ROOM_WAR_FINISH_HEADER* pMsg);
	VOID	FieldSocketArenaRoomWarFinish(MSG_FC_ARENA_ROOM_WAR_FINISH* pMsg);
	VOID	FieldSocketArenaRoomWarFinishDone(MSG_FC_ARENA_ROOM_WAR_FINISH_DONE* pMsg);
	VOID	FieldSocketArenaRoomWarFinishDraw(MSG_FC_ARENA_ROOM_WAR_FINISH_DRAW* pMsg);
	VOID	FieldSocketArenaFinishWarpOK(MSG_FC_ARENA_FINISH_WARP_OK* pMsg);
	VOID	FieldSocketArenaBeforRoomWarFinish();
	VOID	FieldSocketArenaRequestCreateTeamInfoOK(MSG_FC_ARENA_REQUEST_CREATE_TEAMINFO_OK* pMsg);
	VOID	FieldSocketArenaTeamMatching();
	VOID	FieldSocketArenaRequestOtherTeamInfoOK(MSG_FC_ARENA_REQUEST_OTHER_TEAM_INFO_OK* pMsg);
	VOID	FieldSocketArenaGMCommandInfoHeader();
	VOID	FieldSocketArenaGMCommandInfo(MSG_FC_ARENA_GM_COMMAND_INFO* pMsg);
	VOID	FieldSocketArenaGMCommandInfoDone(MSG_FC_ARENA_GM_COMMAND_INFO_DONE* pMsg);

	VOID	FieldSocketBazaarSellPutItemOK(MSG_FC_BAZAAR_SELL_PUT_ITEM_OK* pMsg);
	VOID	FieldSocketBazaarBuyPutItemOK(MSG_FC_BAZAAR_BUY_PUT_ITEM_OK* pMsg);
	VOID	FieldSocketBazaarSellCancelItemOK(MSG_FC_BAZAAR_SELL_CANCEL_ITEM_OK* pMsg);
	VOID	FieldSocketBazaarBuyCancelItemOK(MSG_FC_BAZAAR_BUY_CANCEL_ITEM_OK* pMsg);
	VOID	FieldSocketBazaarSellStartOK();
	VOID	FieldSocketBazaarBuyStartOK();
	VOID	FieldSocketBazaarInfoOK(MSG_FC_BAZAAR_INFO_OK* pMsg);
	VOID	FieldSocketBazaarSellReQuestItemListOK(MSG_FC_BAZAAR_SELL_REQUEST_ITEMLIST_OK* pMsg);
	VOID	FieldSocketBazaarBuyReQuestItemListOK(MSG_FC_BAZAAR_BUY_REQUEST_ITEMLIST_OK* pMsg);
	VOID	FieldSocketBazaarSellItemEnchantlistOK(MSG_FC_BAZAAR_SELL_ITEM_ENCHANTLIST_OK* pMsg);
	VOID	FieldSocketBazaarCustomerInfoOK(MSG_FC_BAZAAR_CUSTOMER_INFO_OK* pMsg);
	VOID	FieldSocketBazaarSellBuyItemOK(MSG_FC_BAZAAR_SELL_BUY_ITEM_OK* pMsg);
	VOID	FieldSocketBazaarBuySellItemOK(MSG_FC_BAZAAR_BUY_SELL_ITEM_OK* pMsg);

	VOID	FieldSocketItemUseRandomBoxOk(MSG_FC_ITEM_USE_RANDOMBOX_OK* pMsg);
	VOID	FieldSocketItemUseRandomBoxOkDone();	// 2008-08-26 by bhsohn �����ڽ� �ý��� ����
	VOID	FieldSocketStoreRequestQuickslotOK(MSG_FC_STORE_REQUEST_QUICKSLOT_OK* pMsg);
	VOID	FieldSocketCharacterUseBonusstatOK(MSG_FC_CHARACTER_USE_BONUSSTAT_OK* pMsg);
	VOID	FieldSocketUseSkillSupportItemOK(MSG_FC_ITEM_USE_SKILL_SUPPORT_ITEM_OK* pMsg);
	VOID	FieldSocketGetServerDataTimeOK(MSG_FC_INFO_GET_SERVER_DATE_TIME_OK* pMsg);
	VOID	FieldSocketRequestPartyWarp(MSG_FC_QUEST_REQUEST_PARTY_WARP* pMsg);

	// 2007-08-07 by bhsohn ����Ŀ ������ �߰�
	VOID	FieldSocketChatAllInfluenceOK(MSG_FC_CHAT_ALL_INFLUENCE * pMsg);
	VOID	FieldSocketChatOutPostGuild(MSG_FC_CHAT_OUTPOST_GUILD* pMsg);

	// 2007-10-29 by dgwoo ���ý���
	VOID	FieldSocketCityPollRequestLeaderCandidateListOKHeader(MSG_FC_CITY_POLL_REQUEST_LEADER_CANDIDATE_LIST_OK_HEADER* pMsg);
	VOID	FieldSocketCityPollRequestLeaderCandidateListOK(MSG_FC_CITY_POLL_REQUEST_LEADER_CANDIDATE_LIST_OK* pMsg);
	VOID	FieldSocketCityPollRequestLeaderCandidateListOKDone();
	VOID	FieldSocketCityPollRequestLeaderCandidateInfoOK(MSG_FC_CITY_POLL_REQUEST_LEADER_CANDIDATE_INFO_OK* pMsg);
	VOID	FieldSocketCityPollRequestLeaderCandidateInfoOkGuildMark(MSG_FC_CITY_POLL_REQUEST_LEADER_CANDIDATE_INFO_OK_GUILDMARK* pMsg);
	VOID	FieldSocketCityPollRegLeaderCandidateOK(MSG_FC_CITY_POLL_REG_LEADER_CANDIDATE_OK* pMsg);
	VOID	FieldSocketCityPollDeleteLeaderCandidateOK();
	VOID	FieldSocketCityPollRequestPollDateOK(MSG_FC_CITY_POLL_REQUEST_POLL_DATE_OK* pMsg);
	VOID	FieldSocketCityPollVoteOK();
	VOID	FieldSocketCityPollLeaderElectionInfo(MSG_FC_CITY_POLL_LEADER_ELECTION_INFO* pMsg);
// 2008-12-09 by dgwoo �̼Ǹ�����.
	VOID	FieldSocketQuestRequestMissionMasterHelpInvite(MSG_FC_QUEST_REQUEST_MISSIONMASTER_HELP_INVITE* pMsg);
	VOID	FieldSocketQuestMissionMasterHelpInviteOK(MSG_FC_QUEST_MISSIONMASTER_HELP_INVITE_OK* pMsg);
	VOID	FieldSocketQuestMissionMasterHelpRejectOK(MSG_FC_QUEST_MISSIONMASTER_HELP_REJECT_OK* pMsg);
// end 2008-12-09 by dgwoo �̼Ǹ�����.

	// 2008-12-30 by bhsohn ���ﺸ���߰� ��ȹ��
	VOID	FieldSocketBossContributionGuild(MSG_FC_WAR_BOSS_CONTRIBUTION_GUILD* pMsg);
	// end 2008-12-30 by bhsohn ���ﺸ���߰� ��ȹ��


	// 2009. 02. 10 by ckPark ���� ���� �ý��� �߰� ����
	VOID	SetWarDeclareInfo(SDECLARATION_OF_WAR* pWarInfo, SDECLARATION_OF_WAR_FORBID_TIME* pForbidTime, BOOL bSetDefault);
	// end 2009. 02. 10 by ckPark ���� ���� �ý��� �߰� ����
	
	
	// 2009. 01. 12 by ckPark ���� ���� �ý���
	// �������� ������ �������� ���
	VOID	FieldSocketWarDeclareInfoOK(MSG_FC_INFO_DECLARATION_MSWAR_INFO_OK* pMsg);
	// end 2009. 01. 12 by ckPark ���� ���� �ý���




	// HackShield
	// 2008-04-04 by bhsohn �ٽ��� ��� ����
	//VOID	FieldSocketMoveHackShield_GuidReqMsg(MSG_FC_MOVE_HACKSHIELD_GuidReqMsg* pMsg);
	VOID	FieldSocketMoveHackShield_CRCReqMsg(MSG_FC_MOVE_HACKSHIELD_CRCReqMsg* pMsg);

	// 2008-11-28 by bhsohn XignCode�߰�
	VOID	FieldSocketMoveXignCodeReqScanInit(UINT nSocketNotifyType, MSG_FC_MOVE_XIGNCODE_REQ_SCAN_INIT* pMsg);
	VOID	FieldSocketMoveXignCodeReqScanCheck(UINT nSocketNotifyType, MSG_FC_MOVE_XIGNCODE_REQ_SCAN_CHECK* pMsg);


	// ETC
	VOID	InitCharacterGameStartOk(AVECTOR3 vPos, BitFlag16_t MapWeather);// CharacterGameStartOk, CharacterConnectGameStartOk
	VOID	CharacterChangeCurrentHPAndDamageBodyCondition(float fCurrentHP);//FieldSocketCharacterChangeCurrentHP,FieldSocketCharacterChangeCurrentHPDPSPEP
	VOID	CharacterChangeCurrentDP(float sCurrentDP);
	VOID	CharacterChangeCurrentSP(SHORT sCurrentSP);
	VOID	CharacterChangeCurrentEP(float fCurrentEP);
	VOID	EventWarpOtherMap(MAP_CHANNEL_INDEX &channelIndex);

	VOID	FieldSocketNotifyServerShutdown();
	VOID	FieldSocketWarMonsterCreated(MSG_FC_WAR_MONSTER_CREATED* pMsg);
	VOID	FieldSocketWarMonsterAutoDestroyed(MSG_FC_WAR_MONSTER_AUTO_DESTROYED* pMsg);
	VOID	FieldSocketWarMonsterDead(MSG_FC_WAR_MONSTER_DEAD* pMsg);

	// 2007-09-12 by bhsohn 2�� ��ȣ �ý��� ����
	VOID	FieldSocketInfoSecondarypasswordCheckPassword(BOOL bSuccess);
	VOID	FieldSecondLockOk(MSG_FC_INFO_SECONDARYPASSWORD_LOCK_OK* pMsg);
	VOID	FieldSocketSecondPasswordUpdateOk(BOOL bSuccess);	
	// 2007-11-22 by bhsohn �Ʒ��� ���ռ���
	void	FieldSocketConnectArenaServerInfo(MSG_FC_CONNECT_ARENASERVER_INFO* pMsg);
	void	FieldSocketConnectArenaServerLoginOk(MSG_FC_CONNECT_ARENASERVER_LOGIN_OK* pMsg);
	void	FieldSocketArenaPossibleGameStart(MSG_FC_ARENA_POSSIBLE_GAMESTART* pMsg);	
	void	FieldSocketCharacterReadyGamestartFromArenaToMainserver(MSG_FC_CHARACTER_READY_GAMESTART_FROM_ARENA_TO_MAINSERVER_OK* pMsg);


	// 2009. 04. 06 by ckPark ���ӽ��۽� �߷� ��æƮ ���� �ȵȻ��·� ������ ����(0001388)
	void	FieldSocketPutEnchantDone( void );
	// end 2009. 04. 06 by ckPark ���ӽ��۽� �߷� ��æƮ ���� �ȵȻ��·� ������ ����(0001388)

	VOID	FieldSocketEventCouponEventUseCouponOK(MSG_FC_EVENT_COUPON_EVENT_USE_COUPON_OK* pMsg);
	VOID	FieldSocketEventCouponEventInfo(MSG_FC_EVENT_COUPON_EVENT_INFO* pMsg);

	// 2008-02-15 by bhsohn ��Ʈ��ũ �ӵ� üũ
	VOID	FieldSocketConnectNetWorkCheckOk(MSG_FC_CONNECT_NETWORK_CHECK_OK* pMsg);

	// 2008-02-25 by bhsohn �Ʒ��� ���� ���� ������ ǥ���ϰ� ����
	void	FieldSocketArenaServerSServerGroupForClient(MSG_FC_CONNECT_ARENASERVER_SSERVER_GROUP_FOR_CLIENT* pMsg);
	
	// 2008-03-10 by bhsohn �Ʒ������� ��ȯ ��Ż ó��
	void	FieldSocketArenaUseCityWarpItem();
	void	FieldSocketInfoMSWarInfoDisplay(MSG_FC_INFO_MSWARINFO_DISPLAY* pMsg);
	void	FieldSocketInfoMSWarInfoDisplayOptionOK(MSG_FC_INFO_MSWARINFO_DISPLAY_OPTION_OK*);
	// 2008-03-19 by bhsohn ����, ������ ����â
	void FieldSocketInfoMsWarInfoResultOk(MSG_FC_INFO_MSWARINFO_RESULT_OK* pMsg);
	void FieldSocketInfoSpWarInfoResultOkHeader();
	void FieldSocketInfoSpWarInfoResultOk(MSG_FC_INFO_SPWARINFO_RESULT_OK* pMsg);
	// end 2008-03-19 by bhsohn ����, ������ ����â
	void FieldSocketEventClickTeleportOK(MSG_FC_EVENT_CLICK_TELEPORT_OK* pMsg);
	// 2008-04-22 by bhsohn ��/������ �������� ������ ǥ�� �ϰ� ����
	void FieldSocketInfoSpWarInfoResultOkDone();

	// 2008-04-04 by bhsohn Ep3 Ŀ�´�Ƽ â
	// ���� ����Ʈ �޽���
	void FieldSocketChatLetterRqTitleHeader();
	void FieldSocketChatLetterRqTitle(MSG_FC_CHAT_LETTER_REQUEST_TITLE_OK* pMsg);	
	void FieldSocketChatLetterRqTitleOkDone();

	void FieldSocketChatALLLetterRqTitle(MSG_FC_CHAT_ALLLETTER_REQUEST_TITLE_OK* pMsg); // ��ü ����
	void FieldSocketChatALLLetterRqTitleOkDone();	 // ��ü ���� �� �޾���

	void FieldSocketLetterReadOk(MSG_FC_CHAT_LETTER_READ_OK* pMsg);		// ���� ���� ��û
	void FieldSocketAllLetterReadOk(MSG_FC_CHAT_ALLLETTER_READ_OK* pMsg);		// ��ü���� ���� ��û
	void FieldSocketChatLetterDelOk();	// ���� ����
	void FieldSocketChatSendOk();		// ���� ������
	void FiedldSocketChatLetterReceive(MSG_FC_CHAT_LETTER_RECEIVE* pMsg);
	void FiedldSocketChatAllLetterReceive(MSG_FC_CHAT_ALLLETTER_RECEIVE* pMsg);
	void FieldSocketCharacterGetUserInfoOk(MSG_FC_CHARACTER_GET_USER_INFO_OK* pMsg);
	
	void FieldSocketCharacterGetUserItemInfoSecretOk(MSG_FC_CHARACTER_GET_USER_ITEM_INFO_SECRET_OK* pMsg);	// 2012-06-14 by isshin ���۹̸�����					// 2012-07-12 by isshin ���۹̸����� On / Off ��� - ���� ����
	void FieldSocketCharacterGetUserItemInfoOk(MSG_FC_ENEMY_ITEM_INFO* pMsg);		// 2012-06-14 by isshin ���۹̸�����
	void FieldSocketCharacterGetUserItemInfoDone(MSG_FC_CHARACTER_GET_USER_ITEM_INFO_OK_DONE* pMsg);	// 2012-06-14 by isshin ���۹̸�����		
	void FieldSocketCharacterChangeInfoOptionSecetOk();
	// end 2008-04-04 by bhsohn Ep3 Ŀ�´�Ƽ â
	// 2008-11-04 by dgwoo LuckyMachine��ȹ �߰�.
	void FieldSocketItemUseRuckyItemOK(MSG_FC_ITEM_USE_LUCKY_ITEM_OK* pMsg);
	// 2008-11-04 by dgwoo LuckyMachine��ȹ �߰�.

	// 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����
	void FieldSocketItemChangedShapeItemNum( MSG_FC_ITEM_CHANGED_SHAPEITEMNUM* pMsg );
	void FieldSocketItemChangedEffectItemNum( MSG_FC_ITEM_CHANGED_EFFECTITEMNUM* pMsg );
	// end 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����

	// 2010. 01. 12 by ckPark ���� ������ ���� ������ ������ �ƴ� ���� �������� ����ϴ� ���� �ذ�
	void FieldSocketPutAllQuestDone( void );
	// end 2010. 01. 12 by ckPark ���� ������ ���� ������ ������ �ƴ� ���� �������� ����ϴ� ���� �ذ�
	
	// 2009-02-03 by bhsohn �̼� ���۽� �Ϸ� üũ üũ
	void FieldSocketQuestPutAllQuestMonsterCountDone();
	// end 2009-02-03 by bhsohn �̼� ���۽� �Ϸ� üũ üũ

	// 2009-02-13 by bhsohn ���� ��ŷ �ý���
	void FieldSocketInfoWRKGetServiceInfoOk(MSG_FC_INFO_WRK_GET_SERVICE_INFO_OK* pMsg);
	void FieldSocketInfoWRKGetServiceInfoOkImage(MSG_FC_INFO_WRK_GET_SERVICE_INFO_OK_IMAGE* pMsg);
	void FieldSocketInfoWRKGetServiceInfoOkDone();
	void FieldSocketInfoWRKGetLevelRankerListOk(MSG_FC_INFO_WRK_GET_LEVEL_RANKER_LIST_OK* pMsg);
	void FieldSocketInfoWRKGetFameRankerListOk(MSG_FC_INFO_WRK_GET_FAME_RANKER_LIST_OK* pMsg);
	void FieldSocketInfoWRKGetPVPRankerListOk(MSG_FC_INFO_WRK_GET_PVP_RANKER_LIST_OK* pMsg);
	void FieldSocketCharacterChangeNickNameOk(MSG_FC_CHARACTER_CHANGE_NICKNAME_OK* pMsg);
	void FieldSocketInfoWrkGetSelfRankingOk(MSG_FC_INFO_WRK_GET_SELF_RANKING_OK* pMsg);
	// end 2009-02-13 by bhsohn ���� ��ŷ �ý���

	// 2009-03-10 by bhsohn nProtector CS��� �߰�
	void FieldSocketMoveNProtectReqAuthData(MSG_FC_MOVE_NPROTECT_REQ_AUTH_DATA* pMsg);
	// end 2009-03-10 by bhsohn nProtector CS��� �߰�
	// 2015-01-07 by jwLee �������� nProtector ����
	void FieldSocketMoveNProtectNewReqAuthData(MSG_FC_MOVE_NPROTECT_NEW_REQ_AUTH_DATA* pMsg);
	// end 2015-01-07 by jwLee �������� nProtector ����
	// 2009. 09. 21 by jskim ���Ӱ��� XTRAP ����(��Ʈ��)
	void FieldSocketMoveXTrapReqStep(MSG_FC_MOVE_XTRAP_REQ_STEP* pMsg);	
	//end 2009. 09. 21 by jskim ���Ӱ��� XTRAP ����(��Ʈ��)

	// 2009. 11. 03 by ckPark �±� APEX ���Ӱ��� �۾�
	void FieldSocketApexReqApexData( MSG_FC_MOVE_APEX_REQ_APEXDATA* pMsg );
	// end 2009. 11. 03 by ckPark �±� APEX ���Ӱ��� �۾�

	// 2009. 10. 14 by jskim ������ī ���� 
	void FieldSocketCharacterChangeStart(MSG_FC_CHARACTER_CHANGE_START_CITY_MAPINDEX_OK* pMsg);
	//end 2009. 10. 14 by jskim ������ī ���� 
	// 2009. 11. 3 by jskim ĳ��(�κ�/â�� Ȯ��) ������ �߰� ����
	void FieldSocketChangeAddedInventoryCount(MSG_FC_CHARACTER_CHANGE_ADDED_INVENTORY_COUNT* pMsg);
	//end 2009. 11. 3 by jskim ĳ��(�κ�/â�� Ȯ��) ������ �߰� ����
	// 2010. 03. 18 by jskim ���ͺ��� ī��
	void FieldSocketItemUpdateTransformerOk(MSG_FC_ITEM_UPDATE_TRANSFORMER_OK* pMsg);
	//end 2010. 03. 18 by jskim ���ͺ��� ī��
	// 2009-04-01 by bhsohn ���� �ұ���, ���� �ʱ�ȭ �ý���
	void FieldSocketQuestInserQuest(MSG_FC_QUEST_INSERT_QUEST* pMsg);
	void FieldSocketQuestDeleteQuest(MSG_FC_QUEST_DELETE_QUEST* pMsg);
	// end 2009-04-01 by bhsohn ���� �ұ���, ���� �ʱ�ȭ �ý���
	
	// 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������
	void FieldSocketCharacterKillCount(MSG_FC_CHARACTER_KILLCOUNT* pMsg);
	void FieldSocketCharacterRestCount(MSG_FC_CHARACTER_RESTCOUNT* pMsg);
	void FieldSocketCharacterBonusExpRate(MSG_FC_CHARACTER_BONUS_EXP_RATE* pMsg);
	// end 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������
	
	// 2010. 06. 08 by jskim Ȩ�����̾� �������� ó��
	void FieldSocketHomePremium(MSG_FC_ITEM_HOMEPREMIUM_INFO* pMsg);
	//end 2010. 06. 08 by jskim Ȩ�����̾� �������� ó��

	// 2010-06-15 by shcho&hslee ��ý��� - �������� ó��
	void FieldSocketCurrentPetBaseData(MSG_FC_ITEM_PET_BASEDATA* pMsg);
//	void FieldSocketCurrentPetSkillData(MSG_FC_ITEM_PET_SKILLDATA* pMsg);		   //2011-10-06 by jhahn ��Ʈ�� ������ �ý���
//	void FieldSocketCurrentPetSocketData(MSG_FC_ITEM_PET_SOCKETDATA* pMsg);		   //2011-10-06 by jhahn ��Ʈ�� ������ �ý���
	// End 2010-06-15 by shcho&hslee ��ý��� - �������� ó��

	void FieldSocketStoreUpdateArmorItemEventInfo(MSG_FC_STORE_UPDATE_ARMOR_ITEM_EVENT_INFO* pMsg); // 2013-05-15 by ssjung �̴��� �Ƹ� - �̴��� �Ƹ� ���� ���� ��Ŷ ���� 

	// 2013-05-28 by bhsohn �Ƹ� �÷��� �ý���
	void FieldSocketCollectionInfo(MSG_FC_COLLECTION_INFO* pMsg);
	void FieldSocketCollectionShapeChange(MSG_FC_COLLECTION_SHAPE_CHANGE* pMsg);
	void UpdateStoreShapeItemNum(MSG_FC_ITEM_CHANGED_SHAPEITEMNUM* pMsg );
	// END 2013-05-28 by bhsohn �Ƹ� �÷��� �ý���

	// 2013-06-26 by bhsohn �Ƹ� �÷��� �߰� ����
	void PopupUseRandomBoxOk(INT nResultItemNum0);	// ������ ItemNum
	void PopupGetCollectionInfo(INT nResultItemNum0);	// ���� �Ƹ� �÷��� ����
	// END 2013-06-26 by bhsohn �Ƹ� �÷��� �߰� ����

	// 2013-06-14 by ssjung �Ƹ� �÷��� �ý��� �̴��� �Ƹ� 
	void FieldSocketCollectionMontylyAromorInit();
	void FieldSocketCollectionMontylyAromorInfo(MSG_FC_COLLECTION_MONTHLY_AROMOR_EVENT_INFO* pMsg);
	// end 2013-06-14 by ssjung �Ƹ� �÷��� �ý��� �̴��� �Ƹ� 

	void FieldSocketWarInfluenceConsecutivePoint(MSG_FC_WAR_INFLUENCE_CONSECUTIVE_POINT* pMsg);	// 2013-08-02 by ssjung ������ ���� ����ǥ��

	void FieldSocketInfluenceShowInfo(MSG_FC_INFLUENCE_SHOW_INFO* pMsg);		// 2014-06-18 by ymjoo ȭ�� ��ܿ� ���� ǥ��

	void FieldSocketNGCWarDisplay(MSG_NGCSPWAR_DISPLAY* pMsg);				   // 2013-08-28 by ssjung ������ ������(NGC)

	void FieldSocketChracterPayContributionPoint(MSG_FC_CHARACTER_PAY_CONTRIBUTIONPOINT* pMsg); // 2013-10-10 by ssjung, ������ ������ - ��������Ʈ ���� ����

// 2013-11-29 by ssjung �ŷ��� ����
	void FieldSocketMarketRegOK(MSG_FC_MARKET_SELL_OK* pMsg);
	void FieldSocketMarketBuyOK(MSG_FC_MARKET_BUY_OK* pMsg);
	void FieldSocketMarkeBaseHeader(MSG_FC_MARKET_BASE_INFO_HEAD* pMsg);
	void FieldSocketMarketBaseOK(MSG_FC_MARKET_BASE_INFO_OK* pMsg);
	void FieldSocketMarketBaseDone(MSG_FC_MARKET_BASE_INFO_DONE* pMsg);
	void FieldSocketMarkeMyListHeader();
	void FieldSocketMarketListOK(MSG_FC_MARKET_MY_LIST_OK* pMsg);
	void FieldSocketMarketListOKDone(MSG_FC_MARKET_MY_LIST_DONE* pMsg);
	void FieldSocketMarketGetOk(MSG_FC_MARKET_GET_OK* pMsg);
	void FieldSocketMarketPaginHeader();
	void FieldSocketMarketPaginOK(MSG_FC_MARKET_PAGING_OK* pMsg);
	void FieldSocketMarketPaginDone(MSG_FC_MARKET_PAGING_DONE* pMsg);
	void FieldSocketMarkeSerchHeader();
	void FieldSocketMarkeSerchOK(MSG_FC_MARKET_SEARCH_OK* pMsg);
	void FieldSocketMarkeSerchDone(MSG_FC_MARKET_SEARCH_DONE* pMsg);
	void FieldSocketMarkeSortHeader();
	void FieldSocketMarkeSortOK(MSG_FC_MARKET_SORT_OK* pMsg);
	void FieldSocketMarkeSortDone(MSG_FC_MARKET_SORT_DONE* pMsg);
// end 2013-11-29 by ssjung �ŷ��� ����
// 2014-01-15 by ssjung �ı� ����� ����
	void FieldSocketDestroyAuctionBaseHeader(MSG_FC_DESTROY_AUCTION_BASE_INFO_HEADER* pMsg);
	void FieldSocketDestroyAuctionBaseOk(MSG_FC_DESTROY_AUCTION_BASE_INFO_OK* pMsg);
	void FieldSocketDestroyAuctionBaseDone();
	void FieldSocketDestroyAuctionTenderOk(MSG_FC_DESTROY_AUCTION_TENDER_OK* pMsg);
	void FieldSocketDestroyAuctionMyListHeader();
	void FieldSocketDestroyAuctionMyListOk(MSG_FC_DESTROY_AUCTION_MY_LIST_OK* pMsg);
	void FieldSocketDestroyAuctionMyListDone();
	void FieldSocketDestroyAuctionGetOk(MSG_FC_DESTROY_AUCTION_GET_OK* pMsg);
	void FieldSocketDestroyAuctionNotiStart();						// 2014-06-12 by ymjoo �ı� ����� �߰��۾�
	void FieldSocketDestroyAuctionNotiEnd();
// end 2014-01-15 by ssjung �ı� ����� ����

	void FieldSocketBugtrapSeverInfo(SBUGTRAP_SERVER_INFO* pMsg);	// 2014-02-10 by ssjung, ���� Ʈ��

	void FieldSocketItemUseCardItemChangeInfluenceNotify(MSG_FC_ITEM_USE_CARDITEM_CHANGE_INFLUENCE_NOTIFY* pMsg);	// 2014-06-10 by ymjoo ���� ���� ������



	// OnRecvIMSocket~
	// 2007-11-22 by bhsohn �Ʒ��� ���ռ���
	//int	OnRecvIMSocketMessage(DWORD wParam);
	int	OnRecvIMSocketMessage(DWORD wParam, UINT uMsg);
	// IMSocket~
	VOID	IMSocketConnectLoginOk(void);
	VOID	IMSocketChatPtoP(MSG_IC_CHAT_PTOP* pMsg);
	VOID	IMSocketChatParty(MSG_IC_CHAT_PARTY* pMsg);
	VOID	IMSocketChatGuild(MSG_IC_CHAT_GUILD* pMsg);
	VOID	IMSocketChatAll(char* pPacket);
	VOID	IMSocketChatSellAll(MSG_IC_CHAT_SELL_ALL* pMsg);
	VOID	IMSocketChatCashAll(MSG_IC_CHAT_CASH_ALL* pMsg);
	VOID	IMSocketChatInfluenceAll(char* pPacket);
	VOID	IMSocketChatWar(MSG_IC_CHAT_WAR* pMsg);
#ifdef _RAT_CHAT_SYSTEM
	VOID	IMSocketChatInfluenceAll_RAT(MSG_IC_CHAT_INFLUENCE_ALL_RAT* pMsg);
#endif
	VOID	IMSocketChatChatRoom(MSG_IC_CHAT_CHATROOM* pMsg);
	
	// 2007-11-22 by bhsohn �Ʒ��� ���ռ���
//	VOID	IMSocketChatGetGuildOk(MSG_IC_CHAT_GET_GUILD_OK* pMsg);
//	VOID	IMSocketChatChangeGuild(MSG_IC_CHAT_CHANGE_GUILD* pMsg);
//	VOID	IMSocketChatChangeParty(MSG_IC_CHAT_CHANGE_PARTY* pMsg);
	VOID	IMSocketChatGetGuildOk(MSG_IC_CHAT_GET_GUILD_OK* pMsg, UINT nSocketNotifyType);
	VOID	IMSocketChatChangeGuild(MSG_IC_CHAT_CHANGE_GUILD* pMsg, UINT nSocketNotifyType);
	VOID	IMSocketChatChangeParty(MSG_IC_CHAT_CHANGE_PARTY* pMsg, UINT nSocketNotifyType);
	// end 2007-11-22 by bhsohn �Ʒ��� ���ռ���

	void	FieldSocketEventInfluenceMark(MSG_FC_EVENT_INFLUENCEMARK* pMsg);
	void	FieldSocketEventInfluenceMarkEnd();

	// 2008-11-21 by bhsohn �ŷ� �Ϸ� �ý��� ó��
	void	FieldSocketTradeOkTradeNotify(MSG_FC_TRADE_OK_TRADE_NOTIFY* pMsg);
	// end 2008-11-21 by bhsohn �ŷ� �Ϸ� �ý��� ó��
	
	// 2010-08-31 by shcho&&jskim, ���� �ý��� ����
	void	FieldSocketDissolDissolutionPutItem(MSG_FC_DISSOLVED_SUCCESS_AND_FAILED* pMsg);
	// end 2010-08-31 by shcho&&jskim, ���� �ý��� ����
	
	// 2011-05-17 by jhahn	����3�� ���� ��ü
	void	FieldMonsterChangeOK(MSG_FC_MONSTER_CHANGE_INDEX* pMsg);
	// end 2011-05-17 by jhahn	����3�� ���� ��ü
	//2011-10-06 by jhahn ��Ʈ�� ������ �ý���
	void	FieldPetNameChangeOK(MSG_FC_ITEM_PET_SET_NAME_OK* pMsg );
	void	FieldPetExpRationOK(MSG_FC_ITEM_PET_SET_EXP_RATIO_OK* pMsg);
	
	void	FieldPetLevelChangeOK(MSG_FC_ITEM_PET_CHANGE_LEVEL* pMsg);
	void	FieldPetExpChangeOK(MSG_FC_ITEM_PET_CHANGE_EXP* pMsg);

	void	FieldPetSetSocket(MSG_FC_ITEM_PET_SET_SOCKET_OK* pMsg);
	void	FieldPetSetKitSlot(MSG_FC_ITEM_PET_SET_KIT_SLOT_OK* pMsg);	
	void	FieldPetSetAutoSkillSlot(MSG_FC_ITEM_PET_SET_AUTOSKILL_SLOT_OK* pMsg);
	//end 2011-10-06 by jhahn ��Ʈ�� ������ �ý���
	// 2011-05-30 by jhahn, ����3�� ���� ����
	void	FieldMonsterDeleteOK(MSG_FC_MONSTER_CINEMA_DELETE_NOTIFY* pMsg);
	// end 2011-05-30 by jhahn, ����3�� ���� ����

	// 2011-05-30 by jhahn, ����3�� �ð� ����
	void	FieldSocketInfinityResetTime( MSG_FC_INFINITY_SET_LIMITTIME* pMsg );
	// end 2011-05-30 by jhahn, ����3�� �ð� ����


	// 2011-05-17 by jhahn	����3���ó׸� ����
	void	FieldInfinityCinemaOK(MSG_FC_INFINITY_MOVIE* pMsg);
	// end 2011-05-17 by jhahn	����3���ó׸� ����
	
	VOID	IMSocketPartyAcceptInviteOk(MSG_IC_PARTY_ACCEPT_INVITE_OK* pMsg);
	VOID	IMSocketPartyPutMember(MSG_IC_PARTY_PUT_MEMBER* pMsg);
	VOID	IMSocketPartyLeaveOk(MSG_IC_PARTY_LEAVE_OK* pMsg);
	VOID	IMSocketPartyBanMemberOk(MSG_IC_PARTY_BAN_MEMBER_OK* pMsg);
	VOID	IMSocketPartyDismemberOk(MSG_IC_PARTY_DISMEMBER_OK* pMsg);
	VOID	IMSocketPartyTransferMasterOk(MSG_IC_PARTY_TRANSFER_MASTER_OK* pMsg);
	VOID	IMSocketPartyPutAllMember(MSG_IC_PARTY_PUT_ALL_MEMBER* pMsg);
	VOID	IMSocketPartyChangeFlightFormationOk(MSG_IC_PARTY_CHANGE_FLIGHT_FORMATION_OK* pMsg);
	VOID	IMSocketPartyGetFlightPosition(MSG_IC_PARTY_GET_FLIGHT_POSITION* pMsg);
	VOID	IMSocketPartyChangeFlightPosition(MSG_IC_PARTY_CHANGE_FLIGHT_POSITION* pMsg);
	VOID	IMSocketPartyCancelFlightPosition(MSG_IC_PARTY_CANCEL_FLIGHT_POSITION* pMsg);
	VOID	IMSocketPartyAllFlightPosition(MSG_IC_PARTY_ALL_FLIGHT_POSITION* pMsg);
	VOID	IMSocketPartyPutLastPartyInfo(MSG_IC_PARTY_PUT_LAST_PARTY_INFO* pMsg);
	VOID	IMSocketPartyUpdateMemberInfoMapName(MSG_IC_PARTY_UPDATE_MEMBER_INFO_MAPNAME* pMsg);
	VOID	IMSocketPartyMemberInvalidated(MSG_IC_PARTY_MEMBER_INVALIDATED* pMsg);
	VOID	IMSocketPartyMemberRejoined(MSG_IC_PARTY_MEMBER_REJOINED* pMsg);
	VOID	IMSocketPartyUpdateItemPos(MSG_IC_PARTY_UPDATE_ITEM_POS* pMsg);
	VOID	IMSocketGuildCreateOk(MSG_IC_GUILD_CREATE_OK* pMsg);
	VOID	IMSocketGuildGetGuildInfoOk(MSG_IC_GUILD_GET_GUILD_INFO_OK* pMsg);
	VOID	IMSocketGuildLeaveOk(MSG_IC_GUILD_LEAVE_OK* pMsg);
	VOID	IMSocketGuildBanMemberOk(MSG_IC_GUILD_BAN_MEMBER_OK* pMsg);
	VOID	IMSocketGuildRequestInviteQuestion(MSG_IC_GUILD_REQUEST_INVITE_QUESTION* pMsg);
	VOID	IMSocketGuildAcceptInviteOk(MSG_IC_GUILD_ACCEPT_INVITE_OK* pMsg);
	VOID	IMSocketGuildRejectInviteOk(MSG_IC_GUILD_REJECT_INVITE_OK* pMsg);
	VOID	IMSocketGuildSetMemberState(MSG_IC_GUILD_SET_MEMBER_STATE* pMsg);
	VOID	IMSocketGuildDismemberOk(MSG_IC_GUILD_DISMEMBER_OK* pMsg);
	VOID	IMSocketGuildCancelDismemberOk(MSG_IC_GUILD_CANCEL_DISMEMBER_OK* pMsg);
	VOID	IMSocketGuildGetDismemberDateOk(MSG_IC_GUILD_GET_DISMEMBER_DATE_OK* pMsg);
	VOID	IMSocketGuildChangeGuildNameOk(MSG_IC_GUILD_CHANGE_GUILD_NAME_OK* pMsg);
	VOID	IMSocketGuildSetGuildMarkOk(MSG_IC_GUILD_SET_GUILD_MARK_OK* pMsg);
	VOID	IMSocketGuildGetGuildMarkOk(MSG_IC_GUILD_GET_GUILD_MARK_OK* pMsg);
	VOID	IMSocketGuildSetRankOk(MSG_IC_GUILD_SET_RANK_OK* pMsg);
	VOID	IMSocketGuildChangeGuildState(MSG_IC_GUILD_CHANGE_GUILD_STATE* pMsg);
	VOID	IMSocketGuildLoadingGuildDone(MSG_IC_GUILD_LOADING_GUILD_DONE* pMsg);
	VOID	IMSocketGuildGetOtherGuildInfoOk(MSG_IC_GUILD_GET_OTHER_GUILD_INFO_OK* pMsg);
	VOID	IMSocketAdminGetServerStatOk(MSG_IC_ADMIN_GET_SERVER_STAT_OK* pMsg);
	VOID	IMSocketConnectClose(MSG_IC_CONNECT_CLOSE* pMsg);
	VOID	IMSocketString128(MSG_IC_STRING_128* pMsg);
	VOID	IMSocketString256(MSG_IC_STRING_256* pMsg);						// 2006-04-13 by ispark
	VOID	IMSocketString512(MSG_IC_STRING_512* pMsg);						// 2006-04-13 by ispark
	VOID	IMSocketGuildWarReady(MSG_IC_GUILD_WAR_READY* pMsg);	
	VOID	IMSocketGuildStartWar(MSG_IC_GUILD_START_WAR* pMsg);
	VOID	IMSocketGuildEndWar(MSG_IC_GUILD_END_WAR* pMsg);
	VOID	IMSocketError(MSG_ERROR* pMsg);
	VOID	IMSocketInvalidPacket(char* pPacket);
	VOID	IMSocketVoipGetAccountUniquenumberOk(MSG_IC_VOIP_GET_ACCOUNTUNIQUENUMBER_OK* pMsg);
	VOID	IMSocketVoip1to1Dial(MSG_IC_VOIP_1to1_DIAL* pMsg);
	VOID	IMSocketVoip1to1DialOk(MSG_IC_VOIP_1to1_DIAL_OK* pMsg);
	VOID	IMSocketVoip1to1End(MSG_IC_VOIP_1to1_END* pMsg);
	VOID	IMSocketVoipNtoNCreateRoomRequestOk(MSG_IC_VOIP_NtoN_CREATEROOM_REQUEST_OK* pMsg);
	VOID	IMSocketVoipNtoNInviteYou(MSG_IC_VOIP_NtoN_INVITE_YOU* pMsg);
	VOID	IMSocketVoipError(MSG_IC_VOIP_ERROR* pMsg);
	VOID	IMSocketVoipNtoNGooutAll(MSG_IC_VOIP_NtoN_GOOUT_ALL* pMsg);
	VOID	IMSocketVoIPSetOK(MSG_IC_VOIP_SET_OK* pMsg);
	VOID	IMSocketChatFriendlistAll(MSG_IC_CHAT_FRIENDLIST_LOADING_OK* pMsg);
	VOID	IMSocketChatFriendlistInsertOk(MSG_IC_CHAT_FRIENDLIST_INSERT_OK* pMsg);
	VOID	IMSocketChatRejectlistAll(MSG_IC_CHAT_REJECTLIST_LOADING_OK* pMsg);
	VOID	IMSocketChatRejectlistInsertOk(MSG_IC_CHAT_REJECTLIST_INSERT_OK* pMsg);
	VOID	IMSocketChatFriendlistRefreshOk(MSG_IC_CHAT_FRIENDLIST_REFRESH_OK* pMsg);
	VOID	IMSocketChatFriendlistDeleteOk(MSG_IC_CHAT_FRIENDLIST_DELETE_OK* pMsg);
	VOID	IMSocketChatRejectlistDeleteOk(MSG_IC_CHAT_REJECTLIST_DELETE_OK* pMsg);
	VOID	IMSocketCountdownStart(MSG_IC_COUNTDOWN_START* pMsg);
	VOID	IMSocketItemUseCarditemGuildChangeMemberCapacity(MSG_IC_GUILD_CHANGE_MEMBER_CAPACITY* pMsg);
	VOID	IMSocketGuildGetGuildMemberListOk(MSG_IC_GUILD_GET_GUILD_MEMBER_LIST_OK* pMsg);
	VOID	IMSocketAdminCallGMInfoOk(MSG_IC_ADMIN_CALLGM_INFO_OK* pMsg);
	VOID	IMSocketAdminCallGMViewOk(char* pPacket);
	VOID	IMSocketAdminCallGMBringOk(char* pPacket);
	VOID	IMSocketGuildEndWarAdminNotify(MSG_IC_GUILD_END_WAR_ADMIN_NOTIFY* pMsg);

	VOID	IMSocketChatRoomCreateOK(MSG_IC_CHATROOM_CREATE_OK* pMsg);
	VOID	IMSocketChatRoomListInfoOK(MSG_IC_CHATROOM_LIST_INFO_OK* pMsg);
	VOID	IMSocketChatRoomRequestInviteQuestion(MSG_IC_CHATROOM_REQUEST_INVITE_QUESTION *pMsg);
	VOID	IMSocketChatRoomJoinOK();
	VOID	IMSocketChatRoomAcceptInviteOK(MSG_IC_CHATROOM_ACCEPT_INVITE_OK* pMsg);
	VOID	IMSocketChatRoomRejectInviteOK();
	VOID	IMSocketChatRoomLeaveOK(MSG_IC_CHATROOM_LEAVE_OK* pMsg);
	VOID	IMSocketChatRoomBanOK(MSG_IC_CHATROOM_BAN_OK* pMsg);
	VOID	IMSocketChatRoomChangeNameOK(MSG_IC_CHATROOM_CHANGE_NAME_OK* pMsg);
	VOID	IMSocketChatroomChangeMasterOK(MSG_IC_CHATROOM_CHANGE_MASTER_OK* pMsg);
	VOID	IMSocketChatRoomChangeLockPWOK(MSG_IC_CHATROOM_CHANGE_LOCK_PW_OK* pMsg);
	VOID	IMSocketChatRoomChangeMaxMemberOK(MSG_IC_CHATROOM_CHANGE_MAX_MEMBER_OK* pMsg);
	VOID	IMSocketChatRoomMemberInfoOK(MSG_IC_CHATROOM_MEMBER_INFO_OK* pMsg);
	VOID	IMSocketChatRoomOtherMemberInfoOK(MSG_IC_CHATROOM_MEMBER_INFO_OK* pMsg);
	// 2008-07-11 by bhsohn ������ ģ�� ����Ʈ �ý��� �߰�
	void	IMSocketChatOnlineEachOtherFriendCount(MSG_IC_CHAT_ONLINE_EACHOTHER_FRIEND_COUNT* pMsg);

	// 2008-06-16 by bhsohn EP3���� ���׼���
	void	IMSocketGuildUpdateIntroductionOk();
	void	IMSocketGuildDelIntroductionOk();
	void	IMSocketUpdateSelfIntroOk();
	void	IMSocketDelSelfIntroOk();

	// 2008-06-18 by bhsohn ���ܿ����� ī�� ���� ó��
	void	IMSocketGuildChangeMemberShip(MSG_IC_GUILD_CHANGE_MEMBERSHIP* pMsg);

	
	// 2009. 01. 12 by ckPark ���� ���� �ý���
	// �������� ������ �������� ���
	void	IMSocketWarDeclareSetOK(MSG_IC_INFO_DECLARATION_MSWAR_SET_OK* pMsg);
	// end 2009. 01. 12 by ckPark ���� ���� �ý���
	// 2010. 03. 18 by jskim ���ͺ��� ī��
	void	IMSocketPartyUpdateItemTransformerOk(MSG_IC_PARTY_UPDATE_ITEM_TRANSFORMER_OK* pMsg);
	//end 2010. 03. 18 by jskim ���ͺ��� ī��
	// 2008-07-17 by bhsohn ���� ��ũ ���Ž� �ñ�� ���� �ذ�
	void	IMGuildChangeFameRank(MSG_IC_GUILD_CHANGE_FAME_RANK* pMsg);

	// 2009-01-12 by bhsohn ģ�� ��� ���ϴ� ���� �޽���â ��� �߰�
	VOID	IMChatFriendListInsertNotify(MSG_IC_CHAT_FRIENDLIST_INSERT_NOTIFY* pMsg);
	// end 2009-01-12 by bhsohn ģ�� ��� ���ϴ� ���� �޽���â ��� �߰�

	// 2007-04-19 by bhsohn ��ġ���� ������ �߰�
	// ��ġ ���� ����Ʈ ���
	VOID	FieldSocketCharacterMapEffectOk(MSG_FC_CHARACTER_SHOW_MAP_EFFECT_OK* pMsg);

	// 2007.04.24 by bhsohn China IME Working
	BOOL	RenderReadingText(int x, int y);

	// 2007-07-04 by bhsohn ���۷����� �߰�
	VOID ShowOpMissionComplete(MSG_FC_QUEST_REQUEST_SUCCESS_RESULT* pMsg);	

	// 2007-07-24 by bhsohn �����̼� mp3�߰�
	void	CompleteNarrationSound(char* pNarrationMusic);	

	// 2007-11-01 by bhsohn ���� �ƿ�� �̺�Ʈ ó�� ��� ����
	VOID	RequestHappyHourInfo();
	// 2007-11-28 by dgwoo ���� ���ӽ� ���� �޽����� �ִ��� ������ ��û.
	VOID	RequestNotifyMsg();

	// 2007-11-05 by bhsohn ���� ������Ʈ üũ�� ó��
	BOOL	IsMeshMonsterObject(int nMeshIndex);

	// 2007-12-21 by bhsohn ���α׷� ���� �� ���� ����
	void	InitMultiLockInfo();

	// 2008-06-20 by bhsohn EP3 �ɼǰ��� ó��
	BOOL	ForceMousePos(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void	ShowPartyChangeInfo(SPARTY_INFO* pNewSetupInfo);

	// 2008-12-30 by bhsohn ���ﺸ���߰� ��ȹ��
	VOID	CreateChatWarContribution(BYTE i_ItemUpdateType, int i_nOrgItemCount, int i_nNewItemCount);

private:
	void	RenderDbg();

	// 2004-12-13 by jschoi - Fade-In & Out �ý���
	void	FadeEffectTick();
	void	FadeEffectRender();

	// 2005-03-03 by jschoi - RequestEnable 
	void	RenderRequestEnable();
	void	RequestEnableTick(float fElapsedTime);

	// 2005-03-17 by jschoi - Error ó��
	BOOL	FieldSocketErrorByMsgType(MSG_ERROR* pMsg);
	BOOL	FieldSocketErrorByErrorCode(MSG_ERROR* pMsg);
	BOOL	IMSocketErrorByMsgType(MSG_ERROR* pMsg);
	BOOL	IMSocketErrorByErrorCode(MSG_ERROR* pMsg);

	/*--------------------------------------------------------------------------*/
	// 2006-06-05 by ispark, �� ���� �� �Լ�
	BOOL	HS_Init();
	BOOL	HS_UnInit();
	BOOL	HS_StartService();
	BOOL	HS_StopService();
	/*--------------------------------------------------------------------------*/
	/*--------------------------------------------------------------------------*/
	// �� ���� ���� �Լ�
	BOOL	HS_SaveFuncAdress();

	// 2008-04-04 by bhsohn �ٽ��� ��� ����
	//void	HS_MakeGuidAckMsg(unsigned char *pbyReqMsg, unsigned char *pbyAckMsg);
	//void	HS_MakeCRCAckMsg(unsigned char *pbyReqMsg, unsigned char *pbyAckMsg);
	// end 2008-04-04 by bhsohn �ٽ��� ��� ����

	// 2009-01-28 by bhsohn nProtector ���� ���� �߰�
	//void	HS_SendHackShieldErrorMsg(long lHackClientCode, char * pMsg = NULL);
	/*--------------------------------------------------------------------------*/
	/*--------------------------------------------------------------------------*/
	// 2006-06-15 by ispark, ���� �ð��� ��Ŷ ������ �Լ�
	void	SendOtherPacket();
	/*--------------------------------------------------------------------------*/
	
	// 2006-11-16 by ispark, ���� ������
	void	RenderAlpha();

	// 2007-02-12 by bhsohn Item ���� ���� ó��
	void	AddMultiItemList(deque<stMultiSelectItem>* pVector, const stMultiSelectItem* pSelItem, BOOL bfrontAdd);	
	void	DelMultiItem(deque<stMultiSelectItem>* pVector, INVEN_DISPLAY_INFO *pDisplayInfo);
	void	DelCityStoreMultiItem(UID64_t	 nUniqueNumber);	// â���� ���� ���
	void	SellMultiResponseOK();
	void	SellMutltiOneItem();
	void	Convert_DWORD_To_String(DWORD dwNum, char* pDstSpi);
	void	ToStoreMultiResponseOK();
	void	UpdateMutltiItemError();
	void	UpdateMultiResponseOK();
	void	ToStoreMultiItemError();
	void	SellMutltiItemError();	
	void	FromStoreMultiResponseOK();
	void	FromStoreMultiItemError();
	BOOL	IsCheckCityStoreFull();
	BOOL	IsCheckInvenFull();
	BOOL	IsCheckSPIEmpty();
	BOOL	IsCheckGuildStore();

	// 2007-02-28 by bhsohn ���� �ǸŽ� 0 spi�� ���� ó��
	void	UpdateMultiSellZeroSPIItem(UID64_t nUniqueNumber);

	// 2007-03-09 by bhsohn ���� ���� â�� �κ� ����
	BOOL	IsStoreHave(int nItemNum);
	BOOL	IsInvenHave(int nItemNum);

	// 2007-04-02 by bhsohn Move��Ŷ���� ���� ���� üũ
	void	UpdateEnemySkillState(bool bUseSkill, CUnitData* pUnit, ClientIndex_t	ClientIndex, INT ItemNum);

	// 2007-07-09 by bhsohn ���� ������ ���� ���� ���½ÿ� ���� ó��
	VOID	CancelBazzarSkill(int nSkillItemNum);

	// 2007-07-24 by bhsohn �����̼� mp3�߰�
	void	PlayNarrationSound();

	// 2007-08-03 by bhsohn ĳ���� ������Ʈ üũ�� ����
	void	ResetCharecterOmiInfo();
	
	// 2007-08-07 by bhsohn ����Ŀ ������ �߰�
	VOID	AddSpeakerGMString(char* pGmChat, BOOL bGmColor);

	// 2007-08-23 by bhsohn �������� �⿩���� ū ������ ���� �޽��� ó��
	VOID	AlertMsgWarMonsterInfo(MEX_MONSTER_INFO* pMonsterInfo, char* pBestGuildName);

	// 2007-09-05 by bhsohn China IME Working
	void	TickImeChange();

	// 2008-01-11 by bhsohn 1�е��� ������ Ŭ���̾�Ʈ ���߰� �ϸ� Ŭ���̾�Ʈ ���� ����
	BOOL	IsCompultionGame(DWORD dwCapTime);		// ���� ���� ���� ���� �Ǵ�
	// 2007-11-22 by bhsohn �Ʒ��� ���ռ���
	CFieldWinSocket* GetFieldWinSocket(UINT nSocketNotifyType);		// ���� ���¿� �´� �ʵ� ����
	CIMSocket* GetIMWinSocket(UINT nSocketNotifyType);				// ���� ���¿� �´� IM����
	void DoModalAreanQuestion();
	void ReCreateAllGameObject();										// ���� ������Ʈ�� �� ������ �ٽ� ����
	void SetMyShuttleInfo(CHARACTER* pCharacter);		// ����ü�� Ŭ���̾�Ʈ �ε��� �� ����
	void SendArenaIMLogin();

	// 2008-03-03 by bhsohn ���� �Ʒ��� IM���� ������� ����
	void ArenaIMSocketConnectLoginOk();
	void IMSocketConnectFmToImOk();

	// 2008-05-28 by bhsohn Multi Lock������ ��û�� ���� �����ÿ� ���� ó��
	void MultiLockFinished(MessageType_t	nPreLockMsg);

	// 2008-06-03 by bhsohn EP3 ���� ���� ó��
	void IMSocketNoticeWriteOk(MSG_IC_GUILD_NOTICE_WRITE_OK* pMsg);		// ���� ���� ���� ���
	// ���� ������ ����
	void IMSocketGetApplicantOkHeader();
	void IMSocketGetApplicantOKDone();
	void IMSocketGetApplicantOk(MSG_IC_GUILD_GET_APPLICANT_OK *pMsg);	
	void IMSocketGetIntroducitonOk(MSG_IC_GUILD_GET_INTRODUCTION_OK* pMsg);
	void IMSocketGuildSearchIntroOk(MSG_IC_GUILD_SEARCH_INTRODUCTION_OK* pMsg);
	void IMSocketGuildSearchIntroDone();
	void IMSocketGuildMemerLevelUp(MSG_IC_GUILD_MEMBER_LEVEL_UP* pMsg);

	// 2008-06-03 by bhsohn EP3 ��� ���� ó��
	void IMSocketPartyListInfoOk(MSG_IC_PARTY_LIST_INFO_OK* pMsg); // ��� ����Ʈ 
	void IMSocketPartyReCommandMemberOk(MSG_IC_PARTY_RECOMMENDATION_MEMBER_OK* pMsg) ;
	void IMSocketPartyChangeInfoOk();
	void IMSocketPartyInfo(MSG_IC_PARTY_INFO* pMsg);
	void IMSocketGetSelfIntroductionOK(MSG_IC_GUILD_GET_SELF_INTRODUCTION_OK* pMsg);

	// 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���
	void IMSocketPartyGetAutoInfoOK( MSG_IC_PARTY_GET_AUTO_PARTY_INFO_OK* pMsg );
	// end 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���


	// 2008-08-11 by bhsohn �ܵ����� ���� �ǰԲ�
	BOOL SetTempCharcaterInfo();

	// 2008-08-18 by bhsohn 1�� ���� ������ �̵� �ý��� 
	void TickItemSell();
	void IntervalSellMutltiOneItem();	// ������ �ְ� �Ǹ�


	// 2010. 03. 03 by ckPark ���Ǵ�Ƽ �ʵ� 2��(���� UI����)
	void TickInfinityStart( void );
	// end 2010. 03. 03 by ckPark ���Ǵ�Ƽ �ʵ� 2��(���� UI����)


	// 2010. 03. 23 by ckPark ���Ǵ�Ƽ �ʵ� 2��(���Ǵ�Ƽ �ʵ� ���� ĳ��������)
	void	TickInfintyMapLoadedSend( void );
	// end 2010. 03. 23 by ckPark ���Ǵ�Ƽ �ʵ� 2��(���Ǵ�Ƽ �ʵ� ���� ĳ��������)


	// 2008-11-13 by bhsohn ���̽�ƽ �۾�
	void TickJoyStickInfo();

	// 2009-04-21 by bhsohn �κ��� ������ �̺�Ʈ ���޽� �޽���â �������� �����ذ�
	void TradeUpdateItemAddChat(MSG_FC_TRADE_UPDATE_ITEM_COUNT* pMsg);
	// end 2009-04-21 by bhsohn �κ��� ������ �̺�Ʈ ���޽� �޽���â �������� �����ذ�

	void TradeItemCenterLockFree();														 // 2013-11-29 by ssjung �ŷ��� ����

public:

	void	StartFadeEffect(BOOL bFadeIn,int nTime,D3DCOLOR dwColor);
	void	EndFadeEffect();
	float	GetFadeAlpha();
	void	SetWeb(BOOL bWeb) { m_bWeb = bWeb; }
	BOOL	GetWeb() { return m_bWeb; }
//	BOOL	GetCashShopFlag(){return m_bCashShopFlag;}
	BOOL	GetTestServerFlag() { return m_bTestServer; }	// TRUE : �׽�Ʈ ������.
	// 2012-11-28 by jhjang �׼� ���� ���� ó�� �߰�
	BOOL	GetTestServerConnect() { return m_bIsTestServerConnect; }
	void 	SetTestServerConnect(BOOL bIsTestServerConnect) { m_bIsTestServerConnect = bIsTestServerConnect; }
	// end 2012-11-28 by jhjang �׼� ���� ���� ó�� �߰�

	// 2012-11-28 by jhjang �׼� ���� ���� ó�� �߰�
	BYTE	GetDBSid()				{	return m_nDBSid;	}
	void	SetDBSid(BYTE nDBSid)	{	m_nDBSid = nDBSid;	}
	// end 2012-11-28 by jhjang �׼� ���� ���� ó�� �߰�
	void	RenderCandidate(int x, int y);
	int		SerchMissionCondition(int nNewItemCount = 0);
	void	SetHanFontLang(LPARAM lParam);
	char*	GetFontStyle(){ return m_strFont;}
	void	SendMissionComplete(int nPartyMissionIndex = 0);// 2006-03-28 by ispark, ��Ƽ�̼��� ��� �ε����� �Ѱ� �޴´�.

	int		GetUnitArmorColorNum(){return m_nArmorNum;}
	int		GetUnitArmorColorMax(){return m_nArmorNumMax;}
	void	SetUnitArmorColorNum(int nNum){ m_nArmorNum = nNum;}
	void	SetUnitArmorColorMax(int nNum){ m_nArmorNumMax = nNum;}

	// 2005-03-18 by jschoi
	void	SetPremiumCardInfo(MSG_FC_CHARACTER_CASH_PREMIUM_CARD_INFO* sMsg);
	MSG_FC_CHARACTER_CASH_PREMIUM_CARD_INFO* GetPrimiumCardInfo() { return &m_PremiumCardInfo; }

	// 2005-12-21 by ispark
	void	SendHackTime_WeaponInfo();
	void	SendHackTime_TotalWeight();
	void	SendHackTime_EngineInfo();
	void	SendHackTime_MemoryCheck(float ValidDistance, float CurrentDistance, float fElapsedTime);

	// 2006-04-13 by ispark
	void	CheckReadyStringFiltering(char *szChat, int *nFTWordCounts, int *nFTTotalBytes);

	
	// 2006-06-05 by ispark, �� ����
	BOOL	HS_Start();
	void	HS_Close();
	int	__stdcall HS_CallbackProc ( long lCode, long lParamSize, void* pParam );

	// 2008-11-28 by bhsohn XignCode�߰�
	BOOL StartGameGuard();
	BOOL CloseGameGuard();
	// end 2008-11-28 by bhsohn XignCode�߰�

	// 2006-06-15 by ispark
//	template<class VECTYPE> void	SetIntDataByVector(vector<VECTYPE> &vecInfo, int nIndex);
//	template<class VECTYPE> void	SetClientIndexDataByVector(vector<VECTYPE> &vecInfo, ClientIndex_t nClientIndex);

	// 2006-09-27 by ispark
	void LostDeviceTick();

	void SetEffectUseItem(ITEM* pItemInfo);
	// 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������
	void SetPlayEffect(INT nEffectNum,INT nSoundNum);
	// end 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������

	// 2007-02-12 by bhsohn ��Ŀ�� �Ҿ� �Ծ��� ���� ���� ó��
	void UpdateCheckTime();
	FLOAT GetCheckElapsedTime();

	// 2007-02-12 by bhsohn Item ���� ���� ó��
	void	StartSellMultiItem();	
	BOOL	SetMultiSelectItem(INVEN_DISPLAY_INFO *pDisplayInfo, INVEN_DISPLAY_INFO	*pSelectItem, POINT ptIcon, BYTE bySelectType);

	// 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����
	//BOOL	SetMultiSelectCityStoreItem(CItemInfo* pItemInfo, INVEN_DISPLAY_INFO	*pSelectItem, POINT ptIcon, BYTE bySelectType);
	BOOL	SetMultiSelectCityStoreItem(CItemInfo* pItemInfo, INVEN_DISPLAY_INFO	*pSelectItem, POINT ptIcon, BYTE bySelectType, INVEN_DISPLAY_INFO  *pDisSelectItem);
	// end 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����

	void	OnCtrlBtnClick(BOOL bCtrlBtnClick);
	BOOL	GetCtrlBtnClick();	
	void	StartToStoreMultiItem();
	void	ToStoreMultiOneItem();
	void	StartFromStoreMultiItem();
	void	FromStoreMultiOneItem();

	// 2007-05-21 by bhsohn �Ʒ��� �ʿ��� �̼�â Ŭ�� �ȵǰ� ����
	MAP_INFO* GetMyShuttleMapInfo();
	BOOL	IsWarMotherShip();
	
	// 2007-06-04 by bhsohn ���� ����� �ð� ��ũ�� ��
	HRESULT DrawBMPText(ATUM_DATE_TIME time, HANDLE *pfFilehandle);

	// 2007-06-18 by bhsohn ��Ʈ�� ���� ���� ó��
	void	SetKeyBoardLostDevice(BOOL bLostDevice);

	// 2007-11-27 by bhsohn �׽�Ʈ ���� ������
	BOOL IsTestServerDefine() { return m_bTestServerDefine; }
// 2007-11-20 by bhsohn �ʷε� �ϴ� ��� ����
	void	ConnectLoginIMServer(char* pUserId,char* pCharacterName, char* pUserPassWord);
	void	SendGameStart(ClientIndex_t	ClientIndex, UID32_t CharacterUniqueNumber);
	// 2007-11-22 by bhsohn �Ʒ��� ���ռ���
	void	InitOnlyGameStartOk(AVECTOR3 vPos, BitFlag16_t MapWeather, BOOL bArenaRestart);
	void	UpdateGameStartMapInfo();

	// 2007-12-17 by bhsohn ������ ������ �� �ȿ��� ���� �����·�
	BOOL	IsLockMode();

	// 2008-08-11 by bhsohn �ܵ����� ���� �ǰԲ�
	void	InitItemList();
	void	AddItemList(MSG_FC_TRADE_INSERT_ITEM* pMsg);
	void	SaveItemList();
	void	SetUnitDetailInfo(CHARACTER* pCharac);
	void	SaveUnitDetailInfo();
	void	SetLoginOkInfo(MSG_FC_CONNECT_LOGIN_OK* pLoginInfo);
	void	SaveLoginOkInfo();
	void	SetGameStartOkInfo(MSG_FC_CHARACTER_GAMESTART_OK* pGamestartInfo);
	void	SaveGameStartOkInfo();
	void	SaveSinglePlayInfo();

	// 2009-03-16 by bhsohn A��� ���� ���� �������� �ּ�ȭ
	DWORD	GetCurrentGameTime();
	// end 2009-03-16 by bhsohn A��� ���� ���� �������� �ּ�ȭ

	// 2009. 11. 03 by ckPark �±� APEX ���Ӱ��� �۾�
	void	StartApexClient( void );
	// end 2009. 11. 03 by ckPark �±� APEX ���Ӱ��� �۾�

	// 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���
	void	ChangeMapObject( ObjectIdx_t nOrigObjIndex, ObjectNum_t nChangeObjIndex );
	// end 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���

	// 2012-11-29 by mspark, ��ġ���� ��ġ�� �̵��ϴ� ĳ������ ��ġ�� �����ϵ��� ����
	void SetPlaySearchEyeEffect(CUnitData * pUnit, INT nEffectNum, INT nSoundNum, bool bMoveCheck = true);
	void ClearPlaySearchEyeEffect(CUnitData * pUnit, INT nEffectNum);
	// end 2012-11-29 by mspark, ��ġ���� ��ġ�� �̵��ϴ� ĳ������ ��ġ�� �����ϵ��� ����

	// 2012-12-17 by jhjang ������ ���콺 Ŀ���� ����� �������� �ʴ� ���� ����
	int AddINFCnt();	//�������̽� â �ߺ� �������� ���ϰ�, �������� ����Ͽ� ����
	int RemoveINFCnt();	//�������̽� â �ߺ� �������� ����, �������� ����Ͽ� ����
	int GetINFCnt();	//�������̽� â �ߺ� �������� ����
	void SetINFCnt(int nInfCnt);
	// end 2012-12-17 by jhjang ������ ���콺 Ŀ���� ����� �������� �ʴ� ���� ����

	// 2012-11-29 by mspark, ��ġ���� ��ġ�� �̵��ϴ� ĳ������ ��ġ�� �����ϵ��� ����
	void SetItemNum(INT nItemNum);
	// end 2012-11-29 by mspark, ��ġ���� ��ġ�� �̵��ϴ� ĳ������ ��ġ�� �����ϵ��� ����

	// 2012-12-21 by bhsohn ��Ʈ�� ���� ���� �ȵǴ� ���� �ذ�
	void SetClientLogOff(BOOL bClientLogOff) {m_bClientLogOff = bClientLogOff;}
	BOOL GetClientLogOff() {return m_bClientLogOff;}
	// END 2012-12-21 by bhsohn ��Ʈ�� ���� ���� �ȵǴ� ���� �ذ�

	// 2013-03-25 by bhsohn ��Ʈ�� ŰƮ �ڵ� ��� ���� ���� ���� ����
	DWORD GetGameCurrentTime() {return m_dwCurrentTime;}
	// END 2013-03-25 by bhsohn ��Ʈ�� ŰƮ �ڵ� ��� ���� ���� ���� ����

	// 2013-05-07 by bhsohn ��ĳ�� ���� ����Ű �߰�
	char*	GetAuthenticationKey() {return m_chAuthenticationKey;}
	void	SetAuthenticationKey(char* pAuthenticationKey) {strncpy(m_chAuthenticationKey, pAuthenticationKey, SIZE_MAX_WEB_AUTHENTICATION_KEY); }
	// END 2013-05-07 by bhsohn ��ĳ�� ���� ����Ű �߰�
	
	// 2013-05-07 by bhsohn ��������Ʈ ������ �ý���
	MSG_FC_WAR_INFLUENCE_CONSECUTIVE_VICTORITES*	GetInflConVictorites() {return &m_structInflConVictorites;}
	void	SetInflConVictorites(MSG_FC_WAR_INFLUENCE_CONSECUTIVE_VICTORITES* pMsg) {memcpy(&m_structInflConVictorites, pMsg, sizeof(MSG_FC_WAR_INFLUENCE_CONSECUTIVE_VICTORITES));}			
	// END 2013-05-07 by bhsohn ��������Ʈ ������ �ý���

	float GetPVPBuffPercent(){return m_fPVPBuffPercent;}		// 2013-08-02 by ssjung ������ ���� ����ǥ��
	
	void CityShopLock(BOOL bState);		// 2014-07-04 by ymjoo ���� �������� ������ ���ԵǴ� ���� ����

#ifdef SC_COLLECTION_ARMOR_JHSEOL_BCKIM
	void LookChangeLimitTimeMSG();	// 2013-05-09 by ssjung ���� ���� �Ⱓ���� ��� �޽��� ����
#endif
	BOOL GetInitFlag()	{return m_bInitFlag;}									// 2013-07-02 ������ ó�� �ε� �� �ź��� ä�� ���̴� ���� ����
	void SetInitFlag(BOOL bFlag)	{m_bInitFlag = bFlag;}						// 2013-07-02 ������ ó�� �ε� �� �ź��� ä�� ���̴� ���� ����
public:
	// 2004-11-11 by jschoi ���ǵ��� ���� ����
	int							m_nSendMovePacketCount;	// MovePacket�� ���� ��
	int							m_nCheckSpeedHackCount;	// ���ǵ��� üũ ī��Ʈ 1�ʴ� 5��
	DWORD						m_dwCheckSpeedHackTime;		// ���ǵ��� üũ Ÿ�� timeGetTime()
	DWORD						m_dwSpeedHackTimer;
	DWORD						m_dwHackCheckTime;		// 2005-12-21 by ispark, �� üũ Ÿ��(1�д�)
	DWORD						m_dwMoveCheckTime;		// 2006-01-10 by ispark, ���� üũ Ÿ��(1�д�)
	// 2014-06-27 by ymjoo DrawText ���� ���� �۾� (DBG �ؽ�Ʈ)
#ifdef C_DRAWTEXT_UPGRADE_YMJOO
	CD3DHanFont		*			m_pFontDebugFps;
	CD3DHanFont		*			m_pFontDebugErr;
	CD3DHanFont		*			m_pFontDebugDBG;
	CD3DHanFont		*			m_pFontDebugServer;
	CD3DHanFont		*			m_pFontDebugInfl;
	CD3DHanFont		*			m_pFontDebugServerUserNum;
	CD3DHanFont		*			m_pFontDebugMapUserNum;
	CD3DHanFont		*			m_pFontDebugMem;
	CD3DHanFont		*			m_pFontDebugObj;
	CD3DHanFont		*			m_pFontDebugEffCnt;
	CD3DHanFont		*			m_pFontDebugEnemyMovePacket;
	CD3DHanFont		*			m_pFontDebugMissileCnt;
	CD3DHanFont		*			m_pFontDebugCharacterPos;
	CD3DHanFont		*			m_pFontInfl;
#else
	CD3DHanFont		*			m_pFontDebug;				// �ؽ�Ʈ ǥ�ÿ� ��Ʈ
#endif
	// END 2014-06-27 by ymjoo DrawText ���� ���� �۾� (DBG �ؽ�Ʈ)
	CD3DHanFont		*			m_pFontCandidate[CHAR_INF_CANDIDATE];				// ����Ʈ
	// 2007.04.24 by bhsohn China IME Working
	CD3DHanFont		*			m_pFontCompositon;
	CD3DHanFont		*			m_pFontIMEType;

	CKeyBoardInput	*			m_pKeyBoard;				// KeyBoard ����
	CCamera			*			m_pCamera;					// Camera ����

	// 2008-11-13 by bhsohn ���̽�ƽ �۾�
	CJoyStickInput*				m_pJoyStick;				// ���̽�ƽ ����
	CJoyStickFreedback*			m_pJoyStickFreedback;				// ���� ���̽�ƽ ����	
	// end 2008-11-13 by bhsohn ���̽�ƽ �۾�

	CUnitRender		*			m_pUnitRender;
	CCharacterRender*			m_pCharacterRender;			// 2005-07-13 by ispark ĳ���� ������
	CShuttleChild	*			m_pShuttleChild;			// ��Ʋ Data
	CCharacterChild *			m_pCharacterChild;			// ĳ���� Data// 2005-07-21 by ispark

	DWORD						m_dwStateBlock;				// 
	DWORD						m_dwGameState;				
	LPDIRECT3DVERTEXBUFFER9		m_pVBSleep;
	BOOL						m_bBazaar;					// ���ڸ�
	// 2012-07-17 by jhahn, �˴ٿ� �ð� ǥ��
	BOOL						FristSeting;
	int							nCount;
	int							nOldTime;	
	int							nNewTime;
	//end 2012-07-17 by jhahn, �˴ٿ� �ð� ǥ��

	CD3DHanFont		*			m_pFontInput;
	IMEKey						m_inputkey;
	CChat			*			m_pChat;
	BOOL						m_bChatMode;
	BOOL						m_bFixUnitDirMode;				// ���� ������� ���� ���
	BOOL						m_bMessageBox;					// �޽��� �ڽ��� ȭ��� �����ϴ°�?
	char						m_strChat[SIZE_MAX_CHAT_MESSAGE];

	// 2007-11-22 by bhsohn �Ʒ��� ���ռ���
	//CFieldWinSocket *			m_pFieldWinSocket;				// �ʵ� ����
	CFieldWinSocketManager *			m_pFieldWinSocket;				// �ʵ� ����

	BOOL						m_bReconnectFieldServer;		// �ٸ� IP �������� ������
	
	// 2007-11-22 by bhsohn �Ʒ��� ���ռ���
	//CIMSocket		*			m_pIMSocket;					// ä�� ����
	CIMSocketManager		*			m_pIMSocket;			// ä�� ����
	

	char						m_strUserID[SIZE_MAX_ACCOUNT_NAME];
	char						m_strUserPassword[SIZE_MAX_PASSWORD_MD5_STRING];
	UINT						m_accountUniqueNumber;
	char						m_strFieldIP[SIZE_MAX_IPADDRESS];
	char						m_strFieldIPCurrent[SIZE_MAX_IPADDRESS];
	INT							m_nFieldPort;
	char						m_strChatIP[SIZE_MAX_IPADDRESS];
	INT							m_nChatPort;

	BOOL						m_bOtherFieldWarping;
	USHORT						m_sWarpAreaIndex;

	// 2014-01-06 by bhsohn Xtrap �׽�Ʈ���� Ű �ٸ��� ó��	
	BOOL						m_bArgcTestServer;			// Launcher���� �˷��ִ� Test���� ����
	// END 2014-01-06 by bhsohn Xtrap �׽�Ʈ���� Ű �ٸ��� ó��	

	INT							m_nInvalidClientIndexCont;		// Ÿĳ���� ����Ʈ�� �ε����� 0 �� ����Ʈ ��
	///////////// Thread ////////////////
	CMapInitThread	*			m_pMapInitThread;				// �� �ε�
	CRITICAL_SECTION			m_cs;							// ����ȭ ��ü
	///////////// Tile Texture Buffer /////////////
	CGameData		*			m_pData;						// ����Ÿ���� (��Ÿ������)

	D3DXVECTOR3					m_vClientOldPos;				// Move ���� �����ÿ� ������ �Ÿ��� üũ�ϱ����� ���� ��Ʋ��ǥ ����
	///////////// Render ���� /////////////
	INT							m_nCheckRenderPos;				// ������ �˻縦 �ؾ��� �κ��� üũ�ϴ� ����
	FLOAT						m_fRenderDeleteCheckTime;		// ������� ���� ���ҽ��� ���� �ð� üũ 
	BYTE						m_nItemStorage;					//������â, â�� ����
	// VoIP	//////////////////////////////////////////////////////////////////
	VOIP_STATE					m_VOIPState;
	/////////////////////////////////////////////////////////////////////////
	// Effect
	CEffectRender	*			m_pEffectRender;//by dhkwon	2003.5.13
	/////////////////////////////////////////////////////////////////////////
	FLOAT						m_fCheckSocketTime;				// Socket Check Time
	FLOAT						m_fOldTickTime;					// ���� ElapsedTime
	FLOAT						m_fReturnKeyTime;				// Return Key Check Time

	CAtumNode		*			m_pEffectList;

	/////////////////////////////////////////////////////////////////////////
	BOOL						m_bDebugText;
	/////////////////////////////////////////////////////////////////////////
	BOOL						m_bClientQuit;
	// 2012-12-21 by bhsohn ��Ʈ�� ���� ���� �ȵǴ� ���� �ذ�
	BOOL						m_bClientLogOff;
	// END 2012-12-21 by bhsohn ��Ʈ�� ���� ���� �ȵǴ� ���� �ذ�

	BOOL						m_bResCheck;
	BOOL						m_bReadyBeginScene;

	BOOL						m_bDeleteItemSend;			// Item �� ������ ������ ����

	CInterface				*	m_pInterface;
	BOOL						m_IsFullMode;					// â�������
	CAbuseFilter	*			m_pAbuseFilter;
	CGameData		*			m_pAbuseFilterData;

	FLOAT						m_fBattleCountCheckTime;	// ��Ƽ ���� ī��Ʈ �ٿ� ���� ���� ����
	INT							m_nBattlePartyCount;
	INT							m_bDegree;					// 0 �����, 1 �߻�� , 2 ����, 3 �浹ó��(����)
	INT							m_bMovePlayer;				// ������ �÷��� ����

	char						m_strDebug[512];			// ������ ����׿� ���� �޼���
	// 2010-09-29 by jskim, SpriteDevice Lost �Ǿ��� �� ���� ����
	//LPD3DXSPRITE				m_pd3dxSprite;
	// end 2010-09-29 by jskim, SpriteDevice Lost �Ǿ��� �� ���� ����
	FLOAT						m_fUserCheckTime;
	char						m_strSeverUserNum[128];
	char						m_strMapUserNum[128];

	// 2012-11-07 by bhsohn ��Ʈ�� ��Ŷ ó��
	FLOAT						m_fServerLiveTime;
	// END 2012-11-07 by bhsohn ��Ʈ�� ��Ŷ ó��

	// remodeling, 2004-03-19 by dhkwon
	CAtumSound					*m_pSound;
	CSceneData					*m_pScene;
	CAtumDatabase				*m_pDatabase;

	BOOL						m_bReadyToGetGuildInfo;

	// 2007-01-07 by bhsohn ��� ���� ����ȭ ���� ���� ó��
	BOOL						m_bReadyFieldGameStartOk;

	CINFStageEffect	*			m_pStageEffect;
	CQuestData		*			m_pQuestData;
	CFxSystem *					m_pFxSystem;	
	BOOL						m_bWeb;
	BOOL						m_bRequestEnable;		// ������ ��û �� �� �ִ� �����ΰ�?
	BOOL						m_bInputItemDone;		// 2007-07-16 by dgwoo ó�� ���Խ� ��� �������� �޾Ҵ°�?
	float						m_fRequestEnableTime;	// �޽��� �ִϸ��̼��� ���� �ð� ����
	DWORD						m_dwTargetting;			// 2005-03-25 by jschoi - Ÿ���� ���� 
	CTutorialSystem*			m_pTutorial;			// Ʃ�丮�� �ý���
	CInputManager*				m_pInputManager;
	
	// ĳ����
	BOOL						m_bCharacter;			// TRUE : ĳ���͸��, FLASE: �����

	// 2005-08-10 by ispark
	// �׸��� ������ ��ġ�� ���� ���� üũ (�׷��� ī�忡�� ������ ���� ����)
	int							m_nDephbias;

	// �Ƹ� Į���� �������ϱ� ���� ��������
	int							m_nArmorNum;		// ���� ��Ʋ Į��
	int							m_nArmorNumMax;		// �ƸӰ� ������ �ִ� �ִ� Į���
	
	D3DXVECTOR3					m_vShuttleOldPos;		// �� ��ǥ

	// 2010. 10. 05 by jskim �ʷε� ���� ����
	CMapLoad*					m_pMaploading;
	// end 2010. 10. 05 by jskim �ʷε� ���� ����
#ifdef _DEBUG
	// �̺�Ʈ ������Ʈ ����
	BOOL						m_bEventObjectRender;	// TURE : ����, FALSE : �Ұ���
#endif
	
	// IME���� �ĺ�����Ʈ ����
	vector<string>	m_vecStingCandidate;
	int				m_nGlabalImageCase;
	char			m_strFont[64];

	/*--------------------------------------------------------------------------*/
	// �����͸� ���� �ð����� ������ ���� ����
	vectorClientIndex			m_vecCharacterOtherInfo;
	vectorClientIndex			m_vecCharacterOtherInfoRequest;
	vectorClientIndex			m_vecCharacterOtherMove;
	vectorClientIndex			m_vecCharacterOtherRenderInfo;
	vectorClientIndex			m_vecCharacterOtherRenderInfoRequest;
	vectorClientIndex			m_vecMoveTarget;

	vector<INT>					m_vecMapObjectInfo;
	vector<INT>					m_vecMonsterInfo;
	vector<INT>					m_vecSimpleItemInfo;
	vector<INT>					m_vecItemInfo;
	/*--------------------------------------------------------------------------*/

	/*--------------------------------------------------------------------------*/
	// 2006-07-05 by ispark, ���� ����� ó���ϴ� �κ�
	BOOL						m_bShutDown;				// ���� ����?
	// 2007-07-10 by bhsohn ��� Ÿ�� ������ ���� ó��
	//char						m_strMsgLastError[SIZE_MAX_CHAT_MESSAGE];
	char						m_strMsgLastError[SIZE_MAX_ERROR_CHAT_MESSAGE];

	BOOL						m_bGameShutDown;		// 2006-08-04 by ispark, ���� ���� ����
	float						m_fGameShutDownTime;	// 2006-08-04 by ispark, ���� ���� ���� �ð�
	/*--------------------------------------------------------------------------*/
	
	BOOL						m_bCheckQuickSlotSave;

	// 2007-07-27 by dgwoo ���� ������ �� �����ΰ�?
	BOOL						m_bInfregular;	

	vector<MSG_FC_TRADE_INSERT_ITEM>			m_vecTutorialInsertItem;
	vector<MSG_FC_TRADE_UPDATE_ITEM_COUNT>     m_vecTutorialUpdateItem;

	vector<CItemInfo*>							m_vecWearDisplayInfo;		// 2012-06-14 by isshin ���۹̸�����

	// 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���
	CInfinityManager*			m_pInfinityManager;		// ���Ǵ�Ƽ UI���� ����

	typedef enum ARENASOCKET_TYPE { ARENASOCKET_ARENA, ARENASOCKET_INFINITY, ARENASOCKET_NONE };

	ARENASOCKET_TYPE			m_ArenaSocketType;		// �Ʒ��� ���� Ÿ��

	BOOL						m_bInfinityMapload;		// ���Ǵ�Ƽ �� �ε� ���ΰ�?(���Ǵ�Ƽ �� �ε��� ������ ������ �ö����� ����Ѵ�)

	BOOL						m_bEnterInfinityAllowed;// ���Ǵ�Ƽ �ʿ� ���� �㰡(��� ��Ƽ������ �ʷε��� �� ��������� TRUE)

	BOOL						m_bInfinityRestart;		// ���Ǵ�Ƽ ƨ������ �������ΰ�?
	BOOL						m_bAddInfinityRestartMessageBox;	// ���Ǵ�Ƽ ������ �޼��� �ڽ��� �����ΰ�?
	// end 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���


	// 2010. 03. 03 by ckPark ���Ǵ�Ƽ �ʵ� 2��(���� UI����)
	BOOL						m_bWaitInfinityMapLoad;	// ���Ǵ�Ƽ �� �ε��� ��ٸ��� ���ΰ�?

	DWORD						m_nInfinityMapLoadTime;	// ���Ǵ�Ƽ �� �ε��� ������ �ð�

	MSG_FC_ARENA_POSSIBLE_GAMESTART	m_ArenaStartPacket;	// ���Ǵ�Ƽ �� �ε��� ����� ��Ŷ ����
	// end 2010. 03. 03 by ckPark ���Ǵ�Ƽ �ʵ� 2��(���� UI����)


	// 2010. 03. 23 by ckPark ���Ǵ�Ƽ �ʵ� 2��(���Ǵ�Ƽ �ʵ� ���� ĳ��������)
	BOOL						m_bInfinityMapLoadedSendEnable;
	BOOL						m_bInfinitySkillSetupOKDone;
	// end 2010. 03. 23 by ckPark ���Ǵ�Ƽ �ʵ� 2��(���Ǵ�Ƽ �ʵ� ���� ĳ��������)


	// 2009. 11. 23 by jskim ���ҽ� �ε� ���� ����
	DWORD							m_dwTimeCheck;	
	vector<structLoadingGameData*>	m_vecLoadingGameData;
	CMeshInitThread*				m_pMeshInitThread;
	structLoadingGameData*			m_pLoadingGameData;
	//end 2009. 11. 23 by jskim ���ҽ� �ε� ���� ����

	// 2011. 10. 10 by jskim UI�ý��� ����
	CINFImageList*				m_pImageList;
	// end 2011. 10. 10 by jskim UI�ý��� ����

	// 2015-02-03 by jwLee nProtect �޼��� �����޼��� ���
	// 2009-01-28 by bhsohn nProtector ���� ���� �߰�	
#if defined(DEFINE_USE_GAMEGUARD_NPROTECTOR)
	char				m_strMsgHackError[SIZE_MAX_ERROR_CHAT_MESSAGE];
	int					m_bMsgHackError;
#endif
	// end 2009-01-28 by bhsohn nProtector ���� ���� ��
	// end 2015-02-03 by jwLee nProtect �޼��� �����޼��� ���

	// 2011. 1. 18 by jskim ��Ʈ�� VTC����
	HINSTANCE m_hGuardLibrary;
	func1	m_fnVTCDLLInit;
	func2	m_fnVTCDLLGetStatus;
	func3	m_fnVTCDLLSetUser;
	func4	m_fnVTCDLLExit;

	CVTCThread* m_pVTCGuard;
	// end 2011. 1. 18 by jskim ��Ʈ�� VTC����

	bool				b_CanadaMutex;// 2012-09-17 by jhahn	ĳ���� �ٽ��� ���� ����

#ifdef _WIREFRAME
	BOOL		m_bWireframe; //2014-09-03 St0rmy wireframe
#endif
#ifdef _NOCLIP
	BOOL		m_bNoclip; //2014-09-03 St0rmy NoClip
#endif
#ifdef _DRAW_EVENTS
	BOOL		m_bDrawEvents; //2015-01-29 by St0rmy, Draw Events
#endif
#ifdef _SHOW_LATENCY
	FLOAT		m_fLatency;
#endif

	BOOL				m_bTradeCenterLock;												// 2013-11-29 by ssjung �ŷ��� ����

	BOOL				m_bCityShopLock;				// 2014-07-04 by ymjoo ���� �������� ������ ���ԵǴ� ���� ����

	SBUGTRAP_SERVER_INFO	m_strBugtrapSeverInfo;		// 2014-02-10 by ssjung, ���� Ʈ��

	CProfiler*			m_pProfiler;					// 2014-06-09 by ymjoo �������Ϸ� ����

	bool				m_bDamageSysMessagePrint;	// 2014-12-19 by jwLee "/���������" ��ɾ� �߰�

private:
//	BOOL						m_bCashShopFlag;		// ĳ���� �÷���
	BOOL						m_bTestServer;			// �׽�Ʈ ���� �÷���
	BOOL						m_bIsTestServerConnect;	// 2012-11-28 by jhjang �׼� ���� ���� ó�� �߰�
	BYTE						m_nDBSid;
	BOOL						m_bDeadByP2PPK;			// PK�� �� ���ֿ��� �׾���? TRUE : �� ���ֿ��� �׾���.
	
	MSG_FC_CHARACTER_CASH_PREMIUM_CARD_INFO		m_PremiumCardInfo;	

	// 2007-02-12 by bhsohn ��Ŀ�� �Ҿ� �Ծ��� ���� ���� ó��	
	FLOAT						m_fCheckElapsedTime;	
	DWORD						m_dwCurrentTime;

	// 2007-02-12 by bhsohn Item ���� ���� ó��
	// �Ǹ� ����
	deque<stMultiSelectItem>	m_vecSellMultiSelectItem;			
	deque<stMultiSelectItem>	m_vecInvenStoreMultiSelectItem;	
	deque<stMultiSelectItem>	m_vecCityStoreMultiSelectItem;	
	BOOL						m_bCtrlBtnClick;
	BOOL						m_bStartMultiSell;
	BOOL						m_bStartMultiStore;

	// 2007-02-28 by bhsohn ���� �ǸŽ� 0 spi�� ���� ó��
	stMultiSelectItem			m_struLastSelMultiItem;
	
	// 2007-04-09 by bhsohn ������ ���� ǥ�� ���� ó��
	char						m_strConnectSeverName[1024];	

	// 2007.04.24 by bhsohn China IME Working
	char						m_szReadingString[1024];	
	char						m_szImeString[1024];	

	// 2007-05-21 by bhsohn China IME Working
	FLOAT						m_fIMETypeShowTime;			
	vector<MSG_FC_ARENA_GM_COMMAND_INFO> m_vecTeamInfo;			// GM��ɾ� /�Ʒ���.

	// 2007-07-10 by bhsohn ��� Ÿ�� ������ ���� ó��
	int							m_nPreComType;
	int							m_nPreIMComType;

	// 2007-07-24 by bhsohn �����̼� mp3�߰�
	char				m_chNarrationSound[256];
	// 2009. 01. 22 by ckPark �� ���º� ���۷����� MP3 �и�
	char				m_chErNarrationSound[256];
	// end 2009. 01. 22 by ckPark �� ���º� ���۷����� MP3 �и�
	
	// 2007-08-03 by bhsohn ĳ���� ������Ʈ üũ�� ����
	vector<int>					m_vecSendCharacterOmiInfo;

	// 2007-09-12 by bhsohn 2�� ��ȣ �ý��� ����
	BYTE			m_bIsUseSecondaryPasswordSystem;	// �ý����� ������� ����
	BYTE			m_bIsSetSecondaryPassword;		// ��ȣ�� �����ߴ��� ����

	// 2007-10-30 by dgwoo ������ ����� �ð��� �������� �ѹ��� �������ش�.
	BOOL			m_bResortingItem;

	// 2007-11-27 by bhsohn �׽�Ʈ ���� ������
	BOOL			m_bTestServerDefine;

	// 2007-11-20 by bhsohn �ʷε� �ϴ� ��� ����
	stGameStartInfo		m_struGameStartInfo;
	BOOL				m_bGameStartInfo;	
	// 2007-11-22 by bhsohn �Ʒ��� ���ռ���
	CArenaManager*		m_pArenaManager;
	
	// 2007-12-17 by bhsohn ������ ������ �� �ȿ��� ���� �����·�
	

	// 2007-12-21 by bhsohn ���α׷� ���� �� ���� ����	
	stMultiLockInfo		m_vecLockProtocol;

	// 2008-01-11 by bhsohn 1�е��� ������ Ŭ���̾�Ʈ ���߰� �ϸ� Ŭ���̾�Ʈ ���� ����
	DWORD				m_dwLastestTickTime;		// Tick�� ���������� 	



	// 2008-02-15 by bhsohn ��Ʈ��ũ �ӵ� üũ
	structNetCheckInfo	m_stNetCheckInfo;

	// 2008-06-20 by bhsohn EP3 �ɼǰ��� ó��
	float				m_fMouseLockTime;
	BOOL				m_bWndMoving;
	int					m_nOnFriendCount;

	// 2008-07-07 by bhsohn 2�� �н����� Ȱ��ȭ��, �κ� �ȿ����� ��
	BYTE				m_bSecondPassLock;

	// 2008-08-11 by bhsohn �ܵ����� ���� �ǰԲ�
	CSinglePlayGame*	m_pSinglePlayGame;	

	// 2008-08-18 by bhsohn 1�� ���� ������ �̵� �ý��� 	
	DWORD				m_dwSendTermTime;
	BOOL				m_bSendTerm;

	// 2008-11-13 by bhsohn ���̽�ƽ �۾�
	float				m_fJoyStickCheckTime;
	float				m_fJoyStickFeedbackPlayTime;	// �����ð�
	int					m_nJoyStickFeedbackType;		// ����Ÿ��	
	int					m_nJoyContorlLen;
	char				m_chJoystickCtrlList[MAX_JOYCTL_LIST][MAX_PATH];
	// end 2008-11-13 by bhsohn ���̽�ƽ �۾�

	// 2009-01-28 by bhsohn nProtector ���� ���� �߰�	
	#if defined(DEFINE_USE_GAMEGUARD_NPROTECTOR)	
		CNPGameLib *		m_pNpgl;
		float				m_fnProtectorHackCheckTime;
	#endif
	// end 2009-01-28 by bhsohn nProtector ���� ���� �߰�
	// 2015-01-07 by jwLee �������� nProtector ����
	#if defined(DEFINE_USE_GAMEGUARD_NPROTECTOR_AUTH3)
		BYTE*				m_pNpAuth3Data;
		int					m_pNpAuth3DataCnt;
	#endif
	// end 2015-01-07 by jwLee �������� nProtector ����
	// 2009. 09. 21 by jskim ���Ӱ��� XTRAP ����(��Ʈ��)
	#if defined(DEFINE_USE_GAMEGUARD_XTRAP)	
		float				m_fXTrapHackCheckTime;
	#endif
	//end 2009. 09. 21 by jskim ���Ӱ��� XTRAP ����(��Ʈ��)

	// 2009-02-13 by bhsohn ���� ��ŷ �ý���
	CWorldRankManager*		m_pWorldRankManager;
	// end 2009-02-13 by bhsohn ���� ��ŷ �ý���

	// 2009-04-08 by bhsohn ���� ���ý�, ����ũ �� ��æƮ �� ������ �ǸŽ� ��� �޽��� ��� ��ȹ ����(K0000174)
	stMultiSelectItem		m_stMultiWarningSelItem;
	// end 2009-04-08 by bhsohn ���� ���ý�, ����ũ �� ��æƮ �� ������ �ǸŽ� ��� �޽��� ��� ��ȹ ����(K0000174)

	// 2009. 06. 09 by ckPark OMI ���� ���۽� üũ�� ����ϵ��� ����
	BYTE					m_nOMICheckSum[32];
	long					m_nOMIFileSize;
	// end 2009. 06. 09 by ckPark OMI ���� ���۽� üũ�� ����ϵ��� ����


	// 2010. 03. 12 by ckPark Interface.tex üũ�� �߰�
	BYTE					m_nInterfaceCheckSum[32];
	long					m_nInterfaceFileSize;
	// end 2010. 03. 12 by ckPark Interface.tex üũ�� �߰�


	// 2009. 11. 03 by ckPark �±� APEX ���Ӱ��� �۾�
	#if defined( DEFINE_USE_GAMEGUARD_APEX )
		_FUNC_C_REC				m_pApexfp_rec;
	#endif
	// end 2009. 11. 03 by ckPark �±� APEX ���Ӱ��� �۾�

	// 2012-12-17 by jhjang ������ ���콺 Ŀ���� ����� �������� �ʴ� ���� ����
	int m_nINFCnt;				// �������̽�â �ߺ� ������
	// end 2012-12-17 by jhjang ������ ���콺 Ŀ���� ����� �������� �ʴ� ���� ����

	// 2012-11-29 by mspark, ��ġ���� ��ġ�� �̵��ϴ� ĳ������ ��ġ�� �����ϵ��� ����
	INT						m_nItemNum;
	// end 2012-11-29 by mspark, ��ġ���� ��ġ�� �̵��ϴ� ĳ������ ��ġ�� �����ϵ��� ����

	//2013-04-11 by ssjung ���� �غ������ �� �� �̵��� �ٽ� �����÷��̾� �Ǵ� ��Ȳ����
	BOOL m_bBossMonsterSummeryReady;
	BYTE m_byInfluence;
	//end 2013-04-11 by ssjung ���� �غ������ �� �� �̵��� �ٽ� �����÷��̾� �Ǵ� ��Ȳ����

	// 2013-05-07 by bhsohn ��ĳ�� ���� ����Ű �߰�
	char		m_chAuthenticationKey[SIZE_MAX_WEB_AUTHENTICATION_KEY];  // 2013-03-13 by hskim, �� ĳ�� ����
	// END 2013-05-07 by bhsohn ��ĳ�� ���� ����Ű �߰�
	
	// 2013-05-07 by bhsohn ��������Ʈ ������ �ý���
	MSG_FC_WAR_INFLUENCE_CONSECUTIVE_VICTORITES		m_structInflConVictorites;
	// END 2013-05-07 by bhsohn ��������Ʈ ������ �ý���

	BOOL				m_bInitFlag;		// 2013-07-02 ������ ó�� �ε� �� �ź��� ä�� ���̴� ���� ����

	float				m_fServerLockTime;// 2013-07-05 by bhsohn ���������, ����� �ý���

	float				m_fPVPBuffPercent;	// 2013-08-02 by ssjung ������ ���� ����ǥ��	

	BYTE				m_SuperiorInfluenceType;	// 2014-06-18 by ymjoo ȭ�� ��ܿ� ���� ǥ��

#ifdef _RAT_FFA
public:
	bool bIsFFAstarted;
	int nTimeDiffFFA;// tmStartedFFATime;
	ATUM_DATE_TIME sTimeEndFFA;// tmStartedFFATime;
#endif
};

// ������������
extern CAtumApplication			*g_pD3dApp;
extern CAtumSJ					*g_pAtumSJ;
extern LPDIRECT3DDEVICE9		g_pD3dDev;	// ���� ����̽� PTR
extern sOPTION_SYSTEM			*g_pSOption;
extern sOPTION_CHARACTER		*g_pSOptionCharacter;
extern int						g_nMoveCountPerRate;
extern float					g_fMoveCountFrame;
// 2008-06-20 by bhsohn EP3 �ɼǰ��� ó��
extern sOPTION_ETC				*g_pSOptionEtc;

// 2008-11-13 by bhsohn ���̽�ƽ �۾�	
extern structJoyStickOptionInfo*		g_pJoysticOp;	
// end 2008-11-13 by bhsohn ���̽�ƽ �۾�

extern CSceneData				*g_pScene;
extern CShuttleChild			*g_pShuttleChild;
extern CCharacterChild			*g_pCharacterChild;		// 2005-07-21 by ispark
extern CAtumDatabase			*g_pDatabase;
extern CInterface				*g_pInterface;
extern CINFGameMain				*g_pGameMain;
extern CStoreData				*g_pStoreData;
extern CQuestData				*g_pQuestData;
extern CCamera					*g_pCamera;
extern CBackground				*g_pGround;

// 2007-11-22 by bhsohn �Ʒ��� ���ռ���
//extern CFieldWinSocket			*g_pFieldWinSocket;
//extern CIMSocket				*g_pIMSocket;
extern CFieldWinSocketManager	*g_pFieldWinSocket;
extern CIMSocketManager			*g_pIMSocket;

extern CINFSelect				*g_pSelect;
extern CINFChannelList			*g_pChannelList;
extern CFrustum					*g_pFrustum;
extern float					g_fSendMovePacket;
extern BOOL						g_bDetailDrawFrame;		// ���� �ø� �ɼ�
extern CTutorialSystem			*g_pTutorial;			// Ʃ�丮��
extern CInputManager			*g_pInputManager;
extern CInput					g_input;
extern int						g_nRenderCandidate;		// IME���� �ĺ�����Ʈ ��� ��ġ
extern CGlobalImage				*g_pGImage;
extern BOOL						g_bEventRecovery;		// �̺�Ʈ ȸ���� ���� Flag
extern float					g_fEventRecoveryRate;	// �̺�Ʈ ȸ����
extern ATUM_DATE_TIME			g_ServerDateTime;		// 2006-10-11 by ispark, ���� �ð�
extern int						g_GameStartTime;		// 2006-10-11 by ispark, ���� ���� �ð�
// 2009. 08. 19 by jsKim ���� �� �޴� ������ ��� Ŀ���� ������ �ʴ� ����
// 2012-12-17 by jhjang ������ ���콺 Ŀ���� ����� �������� �ʴ� ���� ����
//extern int						g_INFCnt;				// �������̽�â �ߺ� ������
// end 2012-12-17 by jhjang ������ ���콺 Ŀ���� ����� �������� �ʴ� ���� ����
// end 2009. 08. 19 by jsKim ���� �� �޴� ������ ��� Ŀ���� ������ �ʴ� ����
// 2009. 09. 10 by jsKim �Ʒ��� ���Խ� ���� ī���� ���� ����
extern ATUM_DATE_TIME			g_ArenaServerDateTime;
extern int						g_ArenaStartTime;	
// end 2009. 09. 10 by jsKim �Ʒ��� ���Խ� ���� ī���� ���� ����
#endif
