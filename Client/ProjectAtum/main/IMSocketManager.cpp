// IMSocketManager.cpp: implementation of the CIMSocketManager class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "IMSocket.h"
#include "AtumApplication.h"
#include "ShuttleChild.h"
#include "Chat.h"

#include "IMSocketManager.h"

// 2008-07-11 by bhsohn ������ ä�ý�, ä�ñ��� �ý��� �߰�
#define MIN_CHATCAP_SECOND	5		// ä�ð� �ּ� ����
#define MIN_CHATCAP_COUNT	5		// �ִ� ä�� ��� ��
#define FORBID_CHAT_TIME	60		// ä�� ���� �ð�(1��=60��)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIMSocketManager::CIMSocketManager(HWND hwnd)
{	
	m_pMainIMSocket = new CIMSocket(hwnd, WM_IM_ASYNC, WM_IM_NOTIFY);
	g_pIMSocket = this;

	m_pArenaIMSocket = NULL;
	
	m_hwnd = hwnd;

	// 2008-07-11 by bhsohn ������ ä�ý�, ä�ñ��� �ý��� �߰�
	m_timeLastSendChat = GetServerDateTime();
	m_timeLastSendChat.Year = 0;
	m_timeLastSendChat.Month = 0;
	m_timeLastSendChat.Day = 0;
	m_timeLastSendChat.Hour = 0;
	m_timeLastSendChat.Minute = 0;
	m_timeLastSendChat.Second = 0;
	
	m_timeForbidSendChat = GetServerDateTime();	// �����Ǵ� �ð�	
	m_timeForbidSendChat.Year = 0;
	m_timeForbidSendChat.Month = 0;
	m_timeForbidSendChat.Day = 0;
	m_timeForbidSendChat.Hour = 0;
	m_timeForbidSendChat.Minute = 0;
	m_timeForbidSendChat.Second = 0;

	m_nMinChatCount = 0;

	// 2009. 06. 17 by ckPark Frost System
#if defined( DEFINE_USE_GAMEGUARD_FROST )
	m_pMainIMSocket->SetFrostEnable( TRUE );
#endif
	// end 2009. 06. 17 by ckPark Frost System
}

CIMSocketManager::~CIMSocketManager()
{
	SAFE_DELETE(m_pMainIMSocket);
	SAFE_DELETE(m_pArenaIMSocket);
	g_pIMSocket = NULL;
}
///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		���� IM ������ ����
/// \author		// 2007-11-22 by bhsohn �Ʒ��� ���ռ���
/// \date		2008-01-30 ~ 2008-01-30
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CIMSocketManager::Connect(LPCSTR strPeerIP, int nPort)
{
	return m_pMainIMSocket->Connect(strPeerIP, nPort);
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		���� IM ������ ��������
/// \author		// 2007-11-22 by bhsohn �Ʒ��� ���ռ���
/// \date		2008-01-30 ~ 2008-01-30
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CIMSocketManager::CloseSocket()
{
	if(IsIMArenaServerConnected())
	{
		CloseArenaIMSocket();
	}
	return m_pMainIMSocket->CloseSocket();
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		IM�����ʿ� ��Ŷ�� ���.
/// \author		// 2007-11-22 by bhsohn �Ʒ��� ���ռ���
/// \date		2008-01-30 ~ 2008-01-30
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CIMSocketManager::Write(LPCSTR pPacket, int nLength, BOOL bArenaSend)
{
	if(IsArenaLoadSuccess() || bArenaSend)
	{
		if(IsIMArenaServerConnected())
		{
			return m_pArenaIMSocket->Write(pPacket, nLength);		
		}		
	}
	else
	{
		return m_pMainIMSocket->Write(pPacket, nLength);
	}	
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		IM�����ʿ� ��Ŷ�� ���.
/// \author		// 2007-11-22 by bhsohn �Ʒ��� ���ռ���
/// \date		2008-01-30 ~ 2008-01-30
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CIMSocketManager::Write(BYTE *pPacket, int nLength) 
{ 
	if(IsArenaLoadSuccess())
	{
		if(IsIMArenaServerConnected())
		{
			return m_pArenaIMSocket->Write(pPacket, nLength);
		}
	}
	else
	{
		return m_pMainIMSocket->Write(pPacket, nLength);	
	}
	return TRUE;	
}	

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		IM�����ʿ� ��Ŷ�� ���.
/// \author		// 2007-11-22 by bhsohn �Ʒ��� ���ռ���
/// \date		2008-01-30 ~ 2008-01-30
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CIMSocketManager::SendMsg( int nType, char *pPacket, int nSize )
{
	BOOL bBothSend = FALSE;
	BOOL bArenaSend = FALSE;
	switch(nType)
	{
	case T_IC_CONNECT_ALIVE:	// Ŭ���̾�Ʈ�� ��������� �˷���
		{
			bArenaSend = TRUE;
			bBothSend = TRUE;
		}
		break;
	case T_IC_PARTY_LEAVE_FROM_M_TO_A:					// Main�������� Arena������ �Ë� ����
	case T_IC_PARTY_REQUEST_PARTYINFO_FROM_A_TO_M:		// Arena�������� Main������ �Ë� ����	
		{
			bArenaSend = FALSE;
		}
		break;
	case T_IC_PARTY_LEAVE_FROM_A_TO_M:
	// 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���
	case T_IC_PARTY_GET_AUTO_PARTY_INFO:
	// end 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���
		{
			bArenaSend = TRUE;
		}
		break;
	///////////////////////////////////////////////////////////////////////////////////////////////////
	/// 2012-04-12 by jhseol, �Ʒ��� �߰����� - �ڵ���Ƽ : ��Ƽ���� ��Ŷ�� �Ʒ��������� ������ �����ϰ� ����
	case T_IC_PARTY_RECOMMENDATION_MEMBER:
	case T_IC_PARTY_CHANGE_INFO:
	case T_IC_PARTY_LIST_INFO:
	case T_IC_PARTY_JOIN_FREE:
		{
#ifdef SC_ARENA_EX_1ST_JHSEOL_MSPARK
			// 2013-05-21 by bhsohn �Ʒ��� ��Ŷ ���� ó��
// 			bArenaSend = TRUE;
// 			bBothSend = TRUE;						
			if(g_pD3dApp && g_pD3dApp->GetArenaState() == ARENA_STATE_ARENA_GAMING )
			{
				bArenaSend = TRUE; 
			}
#endif
		}
		break;
	/// end 2012-04-12 by jhseol, �Ʒ��� �߰����� - �ڵ���Ƽ : ��Ƽ���� ��Ŷ�� �Ʒ��������� ������ �����ϰ� ����
	///////////////////////////////////////////////////////////////////////////////////////////////////
	}	

	if(bArenaSend )
	{
		BOOL bRtn = FALSE;
		if(IsIMArenaServerConnected())
		{
			bRtn = m_pArenaIMSocket->SendMsg( nType, pPacket, nSize );
		}
		if(FALSE == bBothSend)
		{
			return bRtn;
		}		
		return m_pMainIMSocket->SendMsg( nType, pPacket, nSize );
	}
	else
	{
		return m_pMainIMSocket->SendMsg( nType, pPacket, nSize );
	}
	return TRUE;
	
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		IM�����ʿ� ��Ŷ�� ���.
/// \author		// 2007-11-22 by bhsohn �Ʒ��� ���ռ���
/// \date		2008-01-30 ~ 2008-01-30
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CIMSocketManager::WriteMessageType(MessageType_t msgType)
{
	if(IsArenaLoadSuccess())
	{
		if(IsIMArenaServerConnected())
		{
			return m_pArenaIMSocket->WriteMessageType(msgType);
		}
	}
	else
	{
		return m_pMainIMSocket->WriteMessageType(msgType);
	}
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		IM�����ʿ� ä�� �޽����� �Ѹ���.
/// \author		// 2007-11-22 by bhsohn �Ʒ��� ���ռ���
/// \date		2008-01-30 ~ 2008-01-30
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CIMSocketManager::SendChat(int nType, char* strCharacter, char* strChat)
{
	BOOL bSendArenaServer = FALSE;
	BOOL bNoSend = FALSE;
	switch(nType)
	{
	case T_IC_CHAT_ALL:		// ��������
	case T_IC_CHAT_GUILD:	// ���ä��	
	case T_IC_CHAT_MAP:		// ��ä��
	case T_IC_CHAT_SELL_ALL:	// ��ü ä��($)
	case T_IC_CHAT_CASH_ALL:	// ���� �� ä��(&)
	case T_IC_CHAT_PTOP:		// �ӼӸ� ä�� 
	case T_IC_CHAT_WAR:
#if _RAT_CHAT_SYSTEM
	case T_IC_CHAT_INFLUENCE_ALL_RAT:
#endif
	case T_IC_CHAT_CHATROOM:
	case T_IC_CHAT_INFLUENCE_ALL:	// ������ ä��
		{

		}
		break;			
	case T_IC_CHAT_PARTY:	// ���ä��	
		{
			if((IsArenaLoadSuccess())
				&& (IsIMArenaServerConnected()))
			{
				bSendArenaServer = TRUE;
			}
		}
		break;
	case T_IC_CHAT_REGION:	// ���� ä��	
		{
			BOOL bAdmin = 
				COMPARE_RACE(g_pShuttleChild->m_myShuttleInfo.Race,RACE_OPERATION|RACE_GAMEMASTER);
			if(IsIMArenaServerConnected())
			{
				if(IsArenaLoadSuccess())
				{
					bSendArenaServer = TRUE;
				}
				else if(bAdmin && IsOnlySendArenaCmd(strChat))
				{
					bSendArenaServer = TRUE;
				}
			}
			else if(bAdmin && IsOnlySendArenaCmd(strChat))
			{			
				bNoSend = TRUE;
				g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080225_0205,COLOR_ERROR);//"���� �Ʒ��� ������ �������ּ���"
			}
		}
		break;

	// 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���
	case T_IC_CHAT_INFINITY:
	// end 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���
	case T_IC_CHAT_ARENA:	// �Ʒ��� ä��
		{
			if(IsIMArenaServerConnected())
			{
				bSendArenaServer = TRUE;
			}
			else
			{
				bNoSend = TRUE;
			}

		}
		break;
	}
	if(bNoSend)
	{
		return;
	}
	
	// 2008-07-11 by bhsohn ������ ä�ý�, ä�ñ��� �ý��� �߰�
	if(!IsPossibleSendChat())
	{
		g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080711_0200,COLOR_ERROR);//"\\y��õ��� ä���� �̿��Ͻ� �� �����ϴ�."
		return;
	}

	// end 2008-07-11 by bhsohn ������ ä�ý�, ä�ñ��� �ý��� �߰�

	if(bSendArenaServer)
	{
		m_pArenaIMSocket->SendChat(nType, strCharacter, strChat);		
	}
	else
	{
		m_pMainIMSocket->SendChat(nType, strCharacter, strChat);
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		����IM������ ������ �Ǿ��ֳ�?
/// \author		// 2007-11-22 by bhsohn �Ʒ��� ���ռ���
/// \date		2008-01-30 ~ 2008-01-30
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CIMSocketManager::IsConnected()
{
	return m_pMainIMSocket->IsConnected();
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		����IM������ ���ῡ �ʿ��� �̺�Ʈ ó��
/// \author		// 2007-11-22 by bhsohn �Ʒ��� ���ռ���
/// \date		2008-01-30 ~ 2008-01-30
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
LONG CIMSocketManager::OnAsyncEvent(LONG lParam)
{
	return m_pMainIMSocket->OnAsyncEvent(lParam);

}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		����IM�������� ��Ŷ�� �д´�. 
/// \author		// 2007-11-22 by bhsohn �Ʒ��� ���ռ���
/// \date		2008-01-30 ~ 2008-01-30
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int CIMSocketManager::Read(LPSTR *pPacket, int &nLength, int nSocketNotifyType)
{
	if(WM_IM_ARENA_NOTIFY == nSocketNotifyType)
	{
		if(m_pArenaIMSocket)
		{
			return m_pArenaIMSocket->Read(pPacket, nLength);
		}
	}	
	else
	{
		return m_pMainIMSocket->Read(pPacket, nLength);
	}
	return 0;	
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		��� ������ �д´�.
/// \author		// 2007-11-22 by bhsohn �Ʒ��� ���ռ���
/// \date		2008-01-30 ~ 2008-01-30
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CIMSocketManager::OnRecvdGetGuildOK(MSG_IC_CHAT_GET_GUILD_OK* pMsg, int nSocketNotifyType)
{
	if(WM_IM_ARENA_NOTIFY == nSocketNotifyType)
	{
		m_pArenaIMSocket->OnRecvdGetGuildOK(pMsg);
	}
	else
	{
		m_pMainIMSocket->OnRecvdGetGuildOK(pMsg);
	}	
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		�ٲ� ��� ������ �д´�.
/// \author		// 2007-11-22 by bhsohn �Ʒ��� ���ռ���
/// \date		2008-01-30 ~ 2008-01-30
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CIMSocketManager::OnRecvdChangeGuild(MSG_IC_CHAT_CHANGE_GUILD* pMsg, int nSocketNotifyType)
{
	if(WM_IM_ARENA_NOTIFY == nSocketNotifyType)
	{
		m_pArenaIMSocket->OnRecvdChangeGuild(pMsg);
	}
	else
	{
		m_pMainIMSocket->OnRecvdChangeGuild(pMsg);
	}	
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		�ٲ� ��Ƽ������ �����Ѵ�.
/// \author		// 2007-11-22 by bhsohn �Ʒ��� ���ռ���
/// \date		2008-01-30 ~ 2008-01-30
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CIMSocketManager::OnRecvdChangeParty(MSG_IC_CHAT_CHANGE_PARTY* pMsg, int nSocketNotifyType)
{
	if(WM_IM_ARENA_NOTIFY == nSocketNotifyType)
	{
		m_pArenaIMSocket->OnRecvdChangeParty(pMsg);
	}
	else
	{
		m_pMainIMSocket->OnRecvdChangeParty(pMsg);
	}
}
///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		���μ����� �ɸ��� ���� ����
/// \author		// 2007-11-22 by bhsohn �Ʒ��� ���ռ���
/// \date		2008-01-30 ~ 2008-01-30
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CIMSocketManager::SetChaterInfo(CHARACTER* pInfo)
{
	m_pMainIMSocket->SetChaterInfo(pInfo);
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		�Ʒ��� ������ ���� �õ�
/// \author		// 2007-11-22 by bhsohn �Ʒ��� ���ռ���
/// \date		2008-01-30 ~ 2008-01-30
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CIMSocketManager::ConnectArena(LPCSTR strPeerIP, int nPort, BOOL* bAlReadyConnect)
{
	if(NULL == m_pArenaIMSocket)
	{			
		m_pArenaIMSocket = new CIMSocket(m_hwnd, WM_IM_ARENA_ASYNC, WM_IM_ARENA_NOTIFY);		
	}
	(*bAlReadyConnect) = FALSE;
	if(m_pArenaIMSocket->IsConnected())
	{
		(*bAlReadyConnect) = TRUE;
		return TRUE;
	}
	BOOL bConnect = m_pArenaIMSocket->Connect(strPeerIP, nPort);
	return bConnect;	
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		�Ʒ��� ������ ���ӿ� �ʿ��� �̺�Ʈ ó��
/// \author		// 2007-11-22 by bhsohn �Ʒ��� ���ռ���
/// \date		2008-01-30 ~ 2008-01-30
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
LONG CIMSocketManager::OnArenaAsyncEvent(LONG lParam)
{
	if(NULL == m_pArenaIMSocket)
	{
		return 0;
	}

	return m_pArenaIMSocket->OnAsyncEvent(lParam);
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		�Ʒ��� IM������ ������ ���´�.
/// \author		// 2007-11-22 by bhsohn �Ʒ��� ���ռ���
/// \date		2008-01-30 ~ 2008-01-30
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CIMSocketManager::CloseArenaIMSocket()
{
	DBGOUT("CIMSocketManager::CloseArenaIMSocket\n");
	BOOL bRtn = TRUE;
	if(IsIMArenaServerConnected())
	{
		bRtn = m_pArenaIMSocket->CloseSocket();				
	}
	return bRtn;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		������ ������ ���´�.
/// \author		// 2007-11-22 by bhsohn �Ʒ��� ���ռ���
/// \date		2008-01-30 ~ 2008-01-30
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
CIMSocket* CIMSocketManager::GetIMWinSocket(UINT nSocketNotifyType)
{	
	if(WM_IM_ARENA_NOTIFY == nSocketNotifyType)
	{
		return GetArenaIMSocket();
	}
	return m_pMainIMSocket;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		�Ʒ��� ������ ����
/// \author		// 2007-11-22 by bhsohn �Ʒ��� ���ռ���
/// \date		2008-01-30 ~ 2008-01-30
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
CIMSocket* CIMSocketManager::GetArenaIMSocket()
{
	return m_pArenaIMSocket;	
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		�Ʒ��� IM������ ����Ǿ����� ���� �Ǵ�
/// \author		// 2007-11-22 by bhsohn �Ʒ��� ���ռ���
/// \date		2008-01-30 ~ 2008-01-30
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CIMSocketManager::IsIMArenaServerConnected()
{
	if(m_pArenaIMSocket && m_pArenaIMSocket->IsConnected())
	{
		return TRUE;
	}
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		�Ʒ��� �������� �Ǵ�
/// \author		// 2007-11-22 by bhsohn �Ʒ��� ���ռ���
/// \date		2008-01-30 ~ 2008-01-30
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CIMSocketManager::IsArenaLoadSuccess()
{
	if((g_pD3dApp->GetArenaState() == ARENA_STATE_ARENA_LOAD_GAME_INFO )
		|| (g_pD3dApp->GetArenaState() == ARENA_STATE_ARENA_GAMING ))
	{
		return TRUE;
	}
	return FALSE;	
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		�Ʒ��� �ɸ��� ���� ���� ����
/// \author		// 2007-11-22 by bhsohn �Ʒ��� ���ռ���
/// \date		2008-01-30 ~ 2008-01-30
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CIMSocketManager::SetArenaChaterInfo(CHARACTER* pInfo)
{
	m_pArenaIMSocket->SetChaterInfo(pInfo);
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		�Ʒ��� IM�������� ������ Ŀ�ǵ����� �Ǵ�
/// \author		// 2007-11-22 by bhsohn �Ʒ��� ���ռ���
/// \date		2008-03-10 ~ 2008-03-10
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CIMSocketManager::IsOnlySendArenaCmd(char* pChat)
{
	if(0 == COMPARE_RACE(g_pShuttleChild->m_myShuttleInfo.Race,RACE_OPERATION|RACE_GAMEMASTER))
	{
		// �����ڰ� �ƴϸ� ������ �ȵȴ�.
		return FALSE;
	}

	char chCmd[256];
	memset(chCmd, 0x00, 256);
	int nCnt = 0;

	for(nCnt = 0; nCnt< strlen(pChat);nCnt++)
	{
		if(pChat[nCnt] == ' ')		// || m_strInputMessage[n] == '\n')
			break;
		chCmd[nCnt] = pChat[nCnt];
	}	

	if ((stricmp( chCmd, STRCMD_CS_COMMAND_ARENAEVENT_0 )==0)
		||(stricmp( chCmd, STRCMD_CS_COMMAND_ARENAEVENT_1 )==0)
		||(stricmp( chCmd, STRCMD_CS_COMMAND_ARENAEVENT_2 )==0)
		||(stricmp( chCmd, STRCMD_CS_COMMAND_ARENAEVENTRELEASE_0 )==0)
		||(stricmp( chCmd, STRCMD_CS_COMMAND_ARENAEVENTRELEASE_1 )==0)
		||(stricmp( chCmd, STRCMD_CS_COMMAND_ARENAEVENTRELEASE_2 )==0))
	{
		return TRUE;
	}

	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-07-11 by bhsohn ������ ä�ý�, ä�ñ��� �ý��� �߰�
/// \date		2008-07-11 ~ 2008-07-11
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CIMSocketManager::IsPossibleSendChat()
{
	CHARACTER myShuttleInfo = g_pShuttleChild->GetMyShuttleInfo();		
	// ������ �� �������� Ȥ�� �����ڴ� ä�� �������� ���ܵȴ�.
	if(COMPARE_RACE(myShuttleInfo.Race, RACE_INFLUENCE_LEADER)
		||COMPARE_RACE(myShuttleInfo.Race, RACE_INFLUENCE_SUBLEADER_1)
		||COMPARE_RACE(myShuttleInfo.Race, RACE_INFLUENCE_SUBLEADER_2)
		||COMPARE_RACE(myShuttleInfo.Race,RACE_OPERATION|RACE_GAMEMASTER))
	{
		return TRUE;
	}
	
	
	ATUM_DATE_TIME	currenttime = GetServerDateTime();
	if(m_timeForbidSendChat.Year != 0)
	{
		if(currenttime < m_timeForbidSendChat)
		{
			// ���� �ð��̴�.
			return FALSE;
		}
	}
	
	ATUM_DATE_TIME	oldtime = m_timeLastSendChat;

	if(currenttime < oldtime || (0 == m_timeLastSendChat.Year) )
	{
		m_timeLastSendChat = currenttime;
		return TRUE;
	}
	int nSecondDiff = currenttime.GetTimeInSeconds() - oldtime.GetTimeInSeconds();
	if(nSecondDiff < MIN_CHATCAP_SECOND)
	{
		m_nMinChatCount++;		
		if(m_nMinChatCount >= MIN_CHATCAP_COUNT)
		{
			m_timeForbidSendChat = currenttime;
			m_timeForbidSendChat.AddDateTime(0,0,0,0,0, FORBID_CHAT_TIME);	// 1�е��� ä�� ����
			return FALSE;
		}
	}
	else
	{
		m_timeForbidSendChat.Year = 0;
		m_timeForbidSendChat.Month = 0;
		m_timeForbidSendChat.Day = 0;
		m_timeForbidSendChat.Hour = 0;
		m_timeForbidSendChat.Minute = 0;
		m_timeForbidSendChat.Second = 0;

		m_timeForbidSendChat.Year = 0;
		m_timeLastSendChat = currenttime;
		m_nMinChatCount = 0;
	}
	
	
	return TRUE;

}