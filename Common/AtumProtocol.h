/******************************************************************************
	ATUM C/S Protocol ����

	* protocol header ( size of data + ��ȣȭ ���� + seq. #), ������ 4 bytes
	----------------------------------------------------
	| size(2B) | encode_flag(1bit)+N(7bit)| seq. # (1B)|
	----------------------------------------------------

	* ��ȣȭ�� �������� ��� (�ڼ��� ������ �� ���� �Ʒ� �κ� ����)
	<------------------- 4B --------------->
	-----------------------------------------------------------------------
	| size | encode_flag +   N    | seq. # | MSGs ... | dummy  | checksum |
	| (2B) |   (1bit)    + (7bit) |  (1B)  |          | (0~3B) |   (1B)   |
	-----------------------------------------------------------------------
								  <- XOR -><----------- XOR -------------->

	* ��ȣȭ���� ���� �������� ���
	---------------------------------------------------
	| size | encode_flag +   N    | seq. # | MSGs ... |
	| (2B) |   (1bit)    + (7bit) |  (1B)  |          |
	---------------------------------------------------
		   <----------- 0x0000 ------------>

	* message header
	-------------------------
	| Type1(1B) | Type2(1B) |
	-------------------------

	�ۼ���: ������(ywlee@webcallworld.com)
	�ۼ���: 2002. 9. 23.

******************************************************************************/


/* JUST FOR EDITING
0x00
0x01
0x02
0x03
0x04
0x05
0x06
0x07
0x08
0x09
0x0A
0x0B
0x0C
0x0D
0x0E
0x0F
0x10
0x11
0x12
0x13
0x14
0x15
0x16
0x17
0x18
0x19
0x1A
0x1B
0x1C
0x1D
0x1E
0x1F
0x20
0x21
0x22
0x23
0x24
0x25
0x26
0x27
0x28
0x29
0x2A
0x2B
0x2C
0x2D
0x2E
0x2F
*/

#ifndef __ATUM_PROTOCOL_H__
#define __ATUM_PROTOCOL_H__

#include "windows.h"
#include "DefineGlobal.h"
#include "SocketHeader.h"
#include "LocalizationDefineCommon.h"		// 2009-06-12 by cmkwon, �븸 Ŭ���̾�Ʈ ������ ���� �ذ� - 
#include "AtumParam.h"
#include "time.h"
#include "ThreadCheck.h"

#if defined(_ATUM_CLIENT)		// 2008-03-25 by cmkwon, Ŭ���̾�Ʈ ���� ����
// 2008-04-03 by cmkwon, �ٽ��� ���� ���� �ý��� ���� - �Ʒ��� ��� ���Ϸ� �����
//#include "AntiCpSvrFunc.h"				// 2008-03-24 by cmkwon, �ٽ��� 2.0 ���� - AntiCpSvrFunc.h ������ ���Ǹ� �״�� ����ϰ� Ŭ���̾�Ʈ���� ������� �����ϱ�
// 2008-12-19 by cmkwon, �ѱ� Yedang �ٽ��� ����͸� ���� ���� �߰� - 
//#include "AntiCpXSvr.h"					// 2008-04-03 by cmkwon, �ٽ��� ���� ���� �ý��� ���� - 
#include "HShield.h"					// 2008-12-19 by cmkwon, �ѱ� Yedang �ٽ��� ����͸� ���� ���� �߰� - 
#else
// 2008-04-03 by cmkwon, �ٽ��� ���� ���� �ý��� ���� - 
//#include "Security\AntiCpSvrFunc.h"		// 2008-03-24 by cmkwon, �ٽ��� 2.0 ���� - AntiCpSvrFunc.h ������ ���Ǹ� �״�� ����ϰ� Ŭ���̾�Ʈ���� ������� �����ϱ�
#include "Security\AntiCpXSvr.h"		// 2008-04-03 by cmkwon, �ٽ��� ���� ���� �ý��� ���� - 
#endif



#define PRE_SERVER_PORT			15100
#define IM_SERVER_PORT			15101
#define LOG_SERVER_PORT			15102
#define FIELD_SERVER_PORT		15103
#define NPC_SERVER_PORT			15104
//#define NPC_MONITOR_PORT		N/A

const char* GetProtocolTypeString(MessageType_t msgType);
const char* GetGameLogTypeString(MessageType_t msgType);
const char* GetItemUpdateTypeString(BYTE i_byItemUpdateTy);				// 2006-10-27 by cmkwon
const char* GetItemDeleteTypeString(BYTE i_byItemDeleteTy);				// 2008-01-23 by cmkwon, S_F, S_L: ����/�������� ���� �α׿� �߰� - GetItemDeleteTypeString() �߰�

// 2014-03-31 by bckim, ��� ���� ų�α� ( ĳ���� ��û) 
const char* GetKillLogTypeString(INT msgType);
// End. 2014-03-31 by bckim, ��� ���� ų�α� ( ĳ���� ��û) 


void PrintExchangeMsg(BYTE SendOrRecv, MessageType_t nType, char* peerIP, ENServerType st = ST_INVALID_TYPE, BYTE printLevel = PRINTLEVEL_NO_MSG);

///////////////////////////////////////////////////////////////////////////////
// Message Type 0 (��з�)
///////////////////////////////////////////////////////////////////////////////
/*
//#define T0_PC_DEFAULT_UPDATE		0x00
//#define T0_PC_CONNECT				0x01
//#define T0_FN_CONNECT				0x02
//#define T0_FC_CONNECT				0x03
//#define T0_FP_CONNECT				0x04
//#define T0_IP_CONNECT				0x05
//#define T0_FI_CONNECT				0x06
//#define T0_IC_CONNECT				0x07
//#define T0_PM_CONNECT				0x08
//#define T0_FM_CONNECT				0x09
//#define T0_LM_CONNECT				0x0A
//#define T0_IM_CONNECT				0x0B
//#define T0_NM_CONNECT				0x0C
//#define T0_PL_CONNECT				0x0D
//#define T0_IL_CONNECT				0x0E
//#define T0_FL_CONNECT				0x0F
//#define T0_NL_CONNECT				0x10
//#define T0_FI_EVENT					0x11
//#define T0_IC_CHAT					0x12
//#define T0_FI_CHAT					0x13
//#define T0_FC_CHAT					0x14
//#define T0_FC_CHARACTER				0x15
//#define T0_FN_CHARACTER				0x16
//#define T0_FC_MOVE					0x17
//#define T0_FN_MOVE					0x18
//#define T0_FC_BATTLE				0x19
//#define T0_FN_BATTLE				0x1A
//#define T0_FC_PARTY					0x1B
//#define T0_FI_PARTY					0x1C
//#define T0_IC_PARTY					0x1D
//#define T0_FC_MONSTER				0x1E
//#define T0_FN_MONSTER				0x1F
//#define T0_FC_EVENT					0x20
//#define T0_FN_EVENT					0x21
//#define T0_FP_EVENT					0x22
//#define T0_FC_STORE					0x23
//#define T0_FC_ITEM					0x24
//#define T0_FC_SHOP					0x25
//#define T0_FC_TRADE					0x26
//#define T0_FC_GUILD					0x27
//#define T0_FI_GUILD					0x28
//#define T0_IC_GUILD					0x29
//#define T0_FC_SKILL					0x2A
//#define T0_FN_SKILL					0x2B
//#define T0_FC_QUEST					0x2C
////#define T0_FC_SYNC					0x2D
//#define T0_FC_INFO					0x2E
//#define T0_FC_REQUEST				0x2F	// ĳ���Ͱ��� ��û, ����, ���� � ����, general-purpose
//#define T0_FC_CITY					0x30	// ���ÿ� ��������
//// monitor protocol
//#define T0_FM_MONITOR				0x31
//#define T0_PM_MONITOR				0x32
//#define T0_NM_MONITOR				0x33
//#define T0_IM_MONITOR				0x34
//#define T0_LM_MONITOR				0x35
//// admin protocol
//#define T0_FI_ADMIN					0x36
//#define T0_IC_ADMIN					0x37
//#define T0_FC_ADMIN					0x38
//// SendErrorMessage� Type���� ����ϱ� ����
//#define T0_PRE						0x40
//#define T0_IM						0x41
//#define T0_FIELD					0x42
//#define T0_NPC						0x43
//#define T0_TIMER					0x44
//#define T0_DB						0x45
//
//#define T0_FC_RACING				0x50	// ���̽� �ý��ۿ��� ���
//#define T0_FC_TIMER					0x51
//
//// VoIP
//#define T0_ATUMVOIP					0x60				// ���� ��ȭ�� ����
//
//// ĳ������ ���� ����
//#define T0_FI_CHARACTER				0x90
//// admin tool protocol
//#define T0_PA_ADMIN					0xA0
//#define T0_IA_ADMIN					0xA1
//#define T0_FA_ADMIN					0xA2
//#define T0_NA_ADMIN					0xA3
//// INVALID PROTOCOL
//#define T0_NA						0xD0	// NOT AVAILABLE
//// log protocol
//#define T0_FL_LOG					0xE0
//// debugging protocol
//#define T0_FC_CLIENT_REPORT			0xFC	// C -> F
//#define T0_IC_STRING				0xFD
//#define T0_FC_STRING				0xFE
//// error protocol
//#define T0_ERROR					0xFF
*/
// �⺻ ������Ʈ�� ��������, ���� �Ұ�
#define T0_PC_DEFAULT_UPDATE		0x00

// ���� ���� ��������
#define T0_PC_CONNECT				0x10
#define T0_FN_CONNECT				0x11
#define T0_FC_CONNECT				0x31		// 2008-02-13 by cmkwon, �������� ����, �� Ŭ���̾�Ʈ�� ���� ������Ʈ �ؾ���
#define T0_FP_CONNECT				0x13
#define T0_IP_CONNECT				0x14
#define T0_FI_CONNECT				0x15
#define T0_IC_CONNECT				0x16
#define T0_PM_CONNECT				0x17
#define T0_FM_CONNECT				0x18
#define T0_LM_CONNECT				0x19
#define T0_IM_CONNECT				0x1A
#define T0_NM_CONNECT				0x1B
#define T0_PL_CONNECT				0x1C
#define T0_IL_CONNECT				0x1D
#define T0_FL_CONNECT				0x1E
#define T0_NL_CONNECT				0x1F

// 2007-12-27 by dhjin, �Ʒ��� ���� - �Ʒ��� �������� MainField <=> ArenaField
#define T0_MF_TO_AF					0x20

#define T0_PP_CONNECT				0x21	// 2008-02-22 by cmkwon, ServerPreServer->MasangPreServer �� ���� ���� ���� �ý��� �߰� - 

// FC, Field Server <-> Client
#define T0_FC_ADMIN					0x30
#define T0_FC_BATTLE				0x12		// 2008-02-13 by cmkwon, �������� ����, �� Ŭ���̾�Ʈ�� ���� ������Ʈ �ؾ���
#define T0_FC_CHARACTER				0x22	//0x32		    // 2015-06-10 by bckim, �������� ������ŷ ��ġ����
#define T0_FC_CHAT					0x26	//0x33			// 2015-07-03 by bckim, �������� ������ŷ ��ġ���� 2ź
#define T0_FC_CITY					0x34	// ���ÿ� ��������
#define T0_FC_CLIENT_REPORT			0x35	// C -> F
#define T0_FC_EVENT					0x36
#define T0_FC_GUILD					0x37
#define T0_FC_INFO					0x38
#define T0_FC_ITEM					0x23	//0x39	    // 2015-06-10 by bckim, �������� ������ŷ ��ġ����
#define T0_FC_MONSTER				0x3A
#define T0_FC_MOVE					0x3B
#define T0_FC_PARTY					0x3C
#define T0_FC_QUEST					0x3D
#define T0_FC_RACING				0x3E	// ���̽� �ý��ۿ��� ���
#define T0_FC_REQUEST				0x3F	// ĳ���Ͱ��� ��û, ����, ���� � ����, general-purpose
#define T0_FC_SHOP					0x40
#define T0_FC_SKILL					0x41
#define T0_FC_STORE					0x24	//0x42	    // 2015-06-10 by bckim, �������� ������ŷ ��ġ����
#define T0_FC_STRING				0x43
#define T0_FC_TIMER					0x44
#define T0_FC_TRADE					0x25	//0x45		// 2015-06-10 by bckim, �������� ������ŷ ��ġ����
#define T0_FC_COUNTDOWN				0x46
#define T0_FC_OBJECT				0x47
#define T0_FC_AUCTION				0x48
#define T0_FC_CITYWAR				0x49
#define T0_FC_WAR					0x4A	// 2005-12-27 by cmkwon, ������
#define T0_FC_BAZAAR				0x4B	// 2006-07-25 by cmkwon, ���λ���
#define T0_FC_ARENA					0x4C	// 2007-04-17 by dhjin, �Ʒ��� 
#define T0_FC_TUTORIAL				0x4D	// 2007-07-06 by dhjin, Tutorial
#define T0_FC_OUTPOST				0x4E	// 2007-08-13 by dhjin, OutPost
#define T0_FC_INFINITY				0x4F	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - 

// FC, Field Server <-> Client 2��			(0xD1 ~ 0xDF ����)	// 2011-10-18 by hskim, EP4 [Ʈ���� �ý���] - ȭ���� / �� ��ǳ
#define T0_FC_TRIGGER				0xD1						// 2011-10-18 by hskim, EP4 [Ʈ���� �ý���] - ȭ���� / �� ��ǳ
#define	T0_FC_COLLECTION			0xD5	// 0xD2	// 2015-06-10 by bckim, �������� ������ŷ ��ġ���� // 2013-05-31 by jhseol,bckim �Ƹ� �÷��� - ��Ŷ �߰� : �ش�
#define	T0_FC_MARKET				0xD6	// 0xD3 // 2015-06-10 by bckim, �������� ������ŷ ��ġ���� // 2013-11-25 by jhseol&bckim, �ŷ��� - ��Ŷ �߰� : �ش�


// 2015-07-03 by bckim, �������� ������ŷ ��ġ���� 2ź
// FI, Field Server <-> IM Server
#define T0_FI_ADMIN				0x60	//	0x50
#define T0_FI_CHARACTER			0x61	//	0x5A	//	0x51		// 2015-06-10 by bckim, �������� ������ŷ ��ġ����
#define T0_FI_CHAT				0x6A	//	0x5B	//	0x52		// 2015-06-10 by bckim, �������� ������ŷ ��ġ����
#define T0_FI_EVENT				0x6B	//	0x5C	//	0x53		// 2015-06-10 by bckim, �������� ������ŷ ��ġ����
#define T0_FI_GUILD				0x64	//	0x54
#define T0_FI_PARTY				0x65	//	0x55
#define T0_FI_CITYWAR			0x66	//	0x56
#define T0_FI_CASH				0x67	//	0x57
#define T0_FI_INFO				0x68	//	0x58			// 2009-01-12 by dhjin, ���� ����

// FN, Field Server <-> NPC Server
#define T0_FN_BATTLE			0x50	//	0x60
#define T0_FN_CHARACTER			0x5A	//	0x61
#define T0_FN_EVENT				0x5B	//	0x6A	//	0x62		// 2015-06-10 by bckim, �������� ������ŷ ��ġ����
#define T0_FN_MONSTER			0x5C	//	0x6B	//	0x63		// 2015-06-10 by bckim, �������� ������ŷ ��ġ����
#define T0_FN_MOVE				0x54	//	0x64
#define T0_FN_SKILL				0x55	//	0x65
#define T0_FN_CITYWAR			0x56	//	0x66
#define T0_FN_NPCSERVER			0x57	//	0x67			// 2006-04-18 by cmkwon
// End. 2015-07-03 by bckim, �������� ������ŷ ��ġ���� 2ź

// FP, Field Server <-> Pre Server
#define T0_FP_EVENT					0x70
#define T0_FP_MONITOR				0x71
#define T0_FP_CASH					0x72
// 2015-06-10 by bckim, �������� ������ŷ ��ġ����
//#define T0_FP_ADMIN					0x73			// 2008-01-31 by cmkwon, ���� ����/���� ���ɾ�� ������ �ý��� ���� - 
#define T0_FP_ADMIN					0x78			
// End 2015-06-10 by bckim, �������� ������ŷ ��ġ����
#define T0_FP_GLOG					0x74			// 2012-01-08 by hskim, GLog 2��

// IC, IM Server <-> Client
// 2015-07-03 by bckim, �������� ������ŷ ��ġ���� 2ź
#define T0_IC_ADMIN					0x91	//0x80
#define T0_IC_CHAT					0x92	//0x81
#define T0_IC_GUILD					0x93	//0x82
#define T0_IC_PARTY					0x94	//0x83
#define T0_IC_STRING				0x95	//0x84
#define T0_IC_COUNTDOWN				0x96	//0x85
#define T0_IC_CITYWAR				0x97	//0x86
#define T0_IC_VOIP					0x98	//0x87			// 2008-06-17 by dhjin, EP3 VOIP -
#define T0_IC_CHATROOM				0x9A	//0x88			// 2008-06-16 by dhjin, EP3 ä�ù� -
#define T0_IC_INFO					0x9B	//0x89			// 2009-01-12 by dhjin, ���� ����
// End. 2015-07-03 by bckim, �������� ������ŷ ��ġ���� 2ź

// log protocol
#define T0_FL_LOG					0x90

// authentication protocol
#define T0_PAUTH_CONNECT			0x99			// 2011-01-26 by hskim, ���� ���� ���� (Pre Server <-> Authentication Server)

// monitor protocol
#define T0_PM_MONITOR				0xA0
#define T0_IM_MONITOR				0xA1
#define T0_LM_MONITOR				0xA2
#define T0_FM_MONITOR				0xA3
#define T0_NM_MONITOR				0xA4

// admin tool protocol
#define T0_PA_ADMIN					0xB0
#define T0_IA_ADMIN					0xB1
#define T0_FA_ADMIN					0xB2
#define T0_NA_ADMIN					0xB3

// �� ����
#define T0_PRE						0xC0
#define T0_IM						0xC1
#define T0_FIELD					0xC2
#define T0_NPC						0xC3

// ���� ��ȭ�� ����
#define T0_ATUMVOIP					0xD0

//									0xD1 ~ 0xDF		// FC, Field Server <-> Client 2�� ����		// start 2011-10-18 by hskim, EP4 [Ʈ���� �ý���] - ȭ���� / �� ��ǳ

// ����
#define T0_TIMER					0xE0
#define T0_DB						0xE1

// error protocol
#define T0_ERROR					0xFE

// INVALID PROTOCOL
#define T0_NA						0xFF	// NOT AVAILABLE

///////////////////////////////////////////////////////////////////////////////
// Message Type 1 (�Һз�)
///////////////////////////////////////////////////////////////////////////////
// PC_DEFAULT_UPDATE: Atum.exe�� ���� �����, Launcher ������Ʈ��
#define T1_PC_DEFAULT_UPDATE_LAUNCHER_VERSION		0x01
#define T1_PC_DEFAULT_UPDATE_LAUNCHER_UPDATE_INFO	0x02
#define T1_PC_DEFAULT_UPDATE_LAUNCHER_VERSION_OK	0x03
#define T1_PC_DEFAULT_NEW_UPDATE_LAUNCHER_VERSION		0x10		// 2007-01-08 by cmkwon
#define T1_PC_DEFAULT_NEW_UPDATE_LAUNCHER_UPDATE_INFO	0x11		// 2007-01-06 by cmkwon, FTP or HTTP�� �̿��� Launcher update


// PC_CONNECT
#define T1_PC_CONNECT					0x00		// ������� ����
#define T1_PC_CONNECT_OK				0x01		// ������� ����
#define T1_PC_CONNECT_CLOSE				0x02
#define T1_PC_CONNECT_ALIVE				0x03
#define T1_PC_CONNECT_VERSION			0x04
#define T1_PC_CONNECT_UPDATE_INFO		0x05
#define T1_PC_CONNECT_VERSION_OK		0x06
#define T1_PC_CONNECT_REINSTALL_CLIENT	0x07
#define T1_PC_CONNECT_LOGIN				0x08
#define T1_PC_CONNECT_LOGIN_OK			0x09
#define T1_PC_CONNECT_SINGLE_FILE_VERSION_CHECK		0x10		// single file�� ���� ���� Ȯ��(deletefilelist.txt, notice.txt ��)
#define T1_PC_CONNECT_SINGLE_FILE_VERSION_CHECK_OK	0x11
#define T1_PC_CONNECT_SINGLE_FILE_UPDATE_INFO		0x12
#define T1_PC_CONNECT_GET_SERVER_GROUP_LIST			0x13
#define T1_PC_CONNECT_GET_SERVER_GROUP_LIST_OK		0x14

#define T1_PC_CONNECT_GET_GAME_SERVER_GROUP_LIST		0x20		// 2007-05-02 by cmkwon, C->P
#define T1_PC_CONNECT_GET_GAME_SERVER_GROUP_LIST_OK		0x21		// 2007-05-02 by cmkwon, P->C
#define T1_PC_CONNECT_NETWORK_CHECK						0x22		// 2007-06-18 by cmkwon, C->P, // 2007-06-18 by cmkwon, ��Ʈ��ũ ���� üũ 
#define T1_PC_CONNECT_NETWORK_CHECK_OK					0x23		// 2007-06-18 by cmkwon, P->C, // 2007-06-18 by cmkwon, ��Ʈ��ũ ���� üũ 
#define T1_PC_CONNECT_GET_NEW_GAME_SERVER_GROUP_LIST		0x24	// 2007-09-05 by cmkwon, EXE_1�� �α��� ���� ���� �������̽� ���� - C->P
#define T1_PC_CONNECT_GET_NEW_GAME_SERVER_GROUP_LIST_OK		0x25	// 2007-09-05 by cmkwon, EXE_1�� �α��� ���� ���� �������̽� ���� - P->C

#define T1_PC_CONNECT_LOGIN_BLOCKED		0xF0


// FC_CONNECT
#define T1_FC_CONNECT					0x00		// ������� ����
#define T1_FC_CONNECT_OK				0x01		// ������� ����
#define T1_FC_CONNECT_CLOSE				0x02
#define T1_FC_CONNECT_ALIVE				0x03
#define T1_FC_CONNECT_LOGIN				0x04
#define T1_FC_CONNECT_LOGIN_OK			0x05
#define T1_FC_CONNECT_SYNC_TIME			0x06
#define T1_FC_CONNECT_NOTIFY_SERVER_SHUTDOWN	0x07	// No body, 2006-08-04 by cmkwon
#define T1_FC_CONNECT_NETWORK_CHECK				0x09	// C->F, // 2008-02-15 by cmkwon, Client<->FieldServer �� ��Ʈ��ũ ���� üũ - 
#define T1_FC_CONNECT_NETWORK_CHECK_OK			0x0A	// F->C, // 2008-02-15 by cmkwon, Client<->FieldServer �� ��Ʈ��ũ ���� üũ - 
#define T1_FC_CONNECT_ARENASERVER_INFO			0x0B	// 2007-12-28 by dhjin, �Ʒ��� ���� -
#define T1_FC_CONNECT_ARENASERVER_LOGIN			0x0C	// 2007-12-28 by dhjin, �Ʒ��� ���� -
#define T1_FC_CONNECT_ARENASERVER_LOGIN_OK		0x0D	// 2007-12-28 by dhjin, �Ʒ��� ���� -
#define T1_FC_CONNECT_ARENASERVER_SSERVER_GROUP_FOR_CLIENT		0x0E	// 2008-02-25 by dhjin, �Ʒ��� ���� -
#define T1_FC_CONNECT_ARENASERVER_TO_IMSERVER		0x0F	// 2008-03-03 by dhjin, �Ʒ��� ���� -
// start 2011-11-03 by shcho, yedang �˴ٿ��� ���� - ���� �ڵ� �߰�
#define T1_FC_CONNECT_SHUTDOWNMINS_USER_ALTER	0x10	// 10�и��� ���� �ð� �˸� ����
#define T1_FC_CONNECT_SHUTDOWNMINS_USER_ENDGAME	0x11	// 12���̹Ƿ� ���� ���� �˸�
// end 2011-11-03 by shcho, yedang �˴ٿ��� ���� - ���� �ڵ� �߰�

#define T1_FC_CONNECT_BUGTRAPSERVER_INFO		0x12	// 2014-01-27 by bckim, ���� Ʈ��

// FP_CONNECT
#define T1_FP_CONNECT					0x00		// ������� ����
#define T1_FP_CONNECT_OK				0x01		// ������� ����
#define T1_FP_CONNECT_CLOSE				0x02
#define T1_FP_CONNECT_ALIVE				0x03
#define T1_FP_CONNECT_AUTH_USER			0x04
#define T1_FP_CONNECT_AUTH_USER_OK		0x05
#define T1_FP_CONNECT_FIELD_CONNECT		0x06
#define T1_FP_CONNECT_FIELD_CONNECT_OK	0x07
#define T1_FP_CONNECT_NOTIFY_CLOSE		0x08
#define T1_FP_CONNECT_NOTIFY_FIELDSERVER_CHANGE		0x09
#define T1_FP_CONNECT_NOTIFY_FIELDSERVER_CHANGE_OK	0x0A
#define T1_FP_CONNECT_PREPARE_SHUTDOWN				0x0B		// No body, 2006-08-04 by cmkwon
#define T1_FP_CONNECT_UPDATE_DBSERVER_GROUP			0x10		// 2008-04-29 by cmkwon, ������ ���� DB�� �߰�(�ű� ���� ĳ���� ���� ���� �ý����߰�) - P->F
#define T1_FP_CONNECT_CHECK_CONNECTABLE_ACCOUNT		0x11		// 2008-04-29 by cmkwon, ������ ���� DB�� �߰�(�ű� ���� ĳ���� ���� ���� �ý����߰�) - P->F
#define T1_FP_CONNECT_CHECK_CONNECTABLE_ACCOUNT_OK	0x12		// 2008-04-29 by cmkwon, ������ ���� DB�� �߰�(�ű� ���� ĳ���� ���� ���� �ý����߰�) - F->P
#define T1_FP_ADMIN_RELOAD_WORLDRANKING				0x13		// 2009-02-12 by cmkwon, EP3-3 ���巩ŷ�ý��� ���� - P->F(n)
#define T1_FP_ADMIN_RELOAD_INFLUENCERATE			0x14		// P->F // 2009-09-16 by cmkwon, ���� �ʱ�ȭ�� ���¡ ���� ���� - 
#define T1_FP_AUTHENTICATION_SHUTDOWN				0x15		// P->F // 2011-06-22 by hskim, �缳 ���� ���� 

////////////////////////////////////////////////////////////////////////////
// 2012-10-05 by jhseol, NPlay pc�� ���
// end  2012-10-05 by jhseol, NPlay pc�� ���
#define T1_FP_PCBANG_USER_GAME_START				0x16
#define T1_FP_PCBANG_USER_GAME_END					0x17
#define T1_FP_PCBANG_USER_PREMIUN_END				0x18
#define T1_FP_PCBANG_USER_PREMIUM_INFO				0x19
#define T1_FP_PCBANG_USER_PREMIUM_REQUEST			0x1A
#define T1_FP_PCBANG_USER_PREMIUM_RESIDUAL_TIME		0x1B


// IP_CONNECT
#define T1_IP_CONNECT					0x00		// ������� ����
#define T1_IP_CONNECT_OK				0x01		// ������� ����
#define T1_IP_CONNECT_CLOSE				0x02
#define T1_IP_CONNECT_ALIVE				0x03
#define T1_IP_CONNECT_IM_CONNECT		0x04
#define T1_IP_CONNECT_IM_CONNECT_OK		0x05
#define T1_IP_GET_SERVER_GROUP_INFO		0x06
#define T1_IP_GET_SERVER_GROUP_INFO_ACK	0x07
#define T1_IP_ADMIN_PETITION_SET_PERIOD	0x08	// 2007-11-19 by cmkwon, �����ý��� ������Ʈ - P->I(n)
#define T1_IP_ADMIN_RELOAD_ADMIN_NOTICE_SYSTEM		0x09	// 2009-01-14 by cmkwon, ��� �ڵ� ���� �ý��� ���� - P->I(n)
#define T1_IP_AUTHENTICATION_SHUTDOWN				0x0A	// P->F // 2011-06-22 by hskim, �缳 ���� ���� 
#define T1_IP_SELECTIVE_SHUTDOWN_NOTICE				0x0B	// P->I // 2012-07-11 by hskim, ������ �˴ٿ�
#define T1_IP_MONITOR_RELOAD_VERSION_INFO_OK		0x0C	// P->I // 2013-03-14 by jhseol, �������� ���ε� �� ���� ��� IP����Ʈ�� ����
#define T1_IP_RELOAD_GUILD_INFO						0x0D	// 2014-02-11 by bckim, �����ʱ�ȭ�� ���� ����ȭó��


// IC_CONNECT
#define T1_IC_CONNECT					0x00		// ������� ����
#define T1_IC_CONNECT_OK				0x01		// ������� ����
#define T1_IC_CONNECT_CLOSE				0x02
#define T1_IC_CONNECT_ALIVE				0x03
#define T1_IC_CONNECT_LOGIN				0x04
#define T1_IC_CONNECT_LOGIN_OK			0x05
#define T1_IC_CONNECT_FM_TO_IM_OK		0x06		// 2008-03-03 by dhjin, �Ʒ��� ����

// FI_CONNECT
#define T1_FI_CONNECT						0x00
#define T1_FI_CONNECT_OK					0x01
#define T1_FI_CONNECT_CLOSE					0x02
#define T1_FI_CONNECT_ALIVE					0x03
#define T1_FI_NOTIFY_FIELDSERVER_IP			0x04
#define T1_FI_NOTIFY_GAMEEND				0x05
//#define T1_FI_CONNECT_NOTIFY_MAP_CHANGE	0x06		// F -> I, check: deprecated, T1_FI_EVENT_NOTIFY_WARP�� ��ü��
#define T1_FI_CONNECT_NOTIFY_DEAD			0x07		// F -> I
#define T1_FI_GET_FIELD_USER_COUNTS			0x08
#define T1_FI_GET_FIELD_USER_COUNTS_ACK		0x09
#define T1_FI_CONNECT_NOTIFY_GAMESTART		0x0A	// F->I, ���� �������� �� IM Server�� �˸�, ��Ƽ ���� Ȯ�� ��û ��
#define T1_FI_CONNECT_NOTIFY_DEAD_GAMESTART	0x0B
#define T1_FI_CONNECT_PREPARE_SHUTDOWN		0x10	// I->F, // 2007-08-27 by cmkwon, �����ٿ��غ� ���ɾ� �߰�(SCAdminTool���� SCMonitor�� PrepareShutdown�� ���� �� �� �ְ�)

// PM_CONNECT
#define T1_PM_CONNECT					0x00
#define T1_PM_CONNECT_OK				0x01
#define T1_PM_CONNECT_CLOSE				0x02
#define T1_PM_CONNECT_ALIVE				0x03

// FM_CONNECT
#define T1_FM_CONNECT					0x00
#define T1_FM_CONNECT_OK				0x01
#define T1_FM_CONNECT_CLOSE				0x02
#define T1_FM_CONNECT_ALIVE				0x03

// FN_CONNECT
#define T1_FN_CONNECT					0x00		// ������� ����
#define T1_FN_CONNECT_OK				0x01		// ������� ����
#define T1_FN_CONNECT_CLOSE				0x02
#define T1_FN_CONNECT_ALIVE				0x03
#define T1_FN_CONNECT_INCREASE_CHANNEL	0x04	// F->N
#define T1_FN_CONNECT_SET_CHANNEL_STATE	0x05	// F->N

// LM_CONNECT
#define T1_LM_CONNECT					0x00
#define T1_LM_CONNECT_OK				0x01
#define T1_LM_CONNECT_CLOSE				0x02
#define T1_LM_CONNECT_ALIVE				0x03

// IM_CONNECT
#define T1_IM_CONNECT					0x00
#define T1_IM_CONNECT_OK				0x01
#define T1_IM_CONNECT_CLOSE				0x02
#define T1_IM_CONNECT_ALIVE				0x03

// NM_CONNECT
#define T1_NM_CONNECT					0x00
#define T1_NM_CONNECT_OK				0x01
#define T1_NM_CONNECT_CLOSE				0x02
#define T1_NM_CONNECT_ALIVE				0x03

// PL_CONNECT
#define T1_PL_CONNECT					0x00
#define T1_PL_CONNECT_OK				0x01
#define T1_PL_CONNECT_CLOSE				0x02
#define T1_PL_CONNECT_ALIVE				0x03

// IL_CONNECT
#define T1_IL_CONNECT					0x00
#define T1_IL_CONNECT_OK				0x01
#define T1_IL_CONNECT_CLOSE				0x02
#define T1_IL_CONNECT_ALIVE				0x03

// FL_CONNECT
#define T1_FL_CONNECT					0x00
#define T1_FL_CONNECT_OK				0x01
#define T1_FL_CONNECT_CLOSE				0x02
#define T1_FL_CONNECT_ALIVE				0x03

// NL_CONNECT
#define T1_NL_CONNECT					0x00
#define T1_NL_CONNECT_OK				0x01
#define T1_NL_CONNECT_CLOSE				0x02
#define T1_NL_CONNECT_ALIVE				0x03

// 2008-02-22 by cmkwon, ServerPreServer->MasangPreServer �� ���� ���� ���� �ý��� �߰� - 
// 2008-02-22 by cmkwon, #define T0_PP_CONNECT				0x20	
#define T1_PP_CONNECT					0x00	// 2008-02-22 by cmkwon, ServerPreServer->MasangPreServer �� ���� ���� ���� �ý��� �߰� - 
#define T1_PP_CONNECT_OK				0x01	// 2008-02-22 by cmkwon, ServerPreServer->MasangPreServer �� ���� ���� ���� �ý��� �߰� - 
#define T1_PP_CONNECT_DO_CLOSE			0x02	// 2008-02-22 by cmkwon, ServerPreServer->MasangPreServer �� ���� ���� ���� �ý��� �߰� - 

#define T_PP_CONNECT					(MessageType_t)((T0_PP_CONNECT<<8)|T1_PP_CONNECT)			// 2008-02-22 by cmkwon, ServerPreServer->MasangPreServer �� ���� ���� ���� �ý��� �߰� - 
#define T_PP_CONNECT_OK					(MessageType_t)((T0_PP_CONNECT<<8)|T1_PP_CONNECT_OK)		// 2008-02-22 by cmkwon, ServerPreServer->MasangPreServer �� ���� ���� ���� �ý��� �߰� - 
#define T_PP_CONNECT_DO_CLOSE			(MessageType_t)((T0_PP_CONNECT<<8)|T1_PP_CONNECT_DO_CLOSE)	// 2008-02-22 by cmkwon, ServerPreServer->MasangPreServer �� ���� ���� ���� �ý��� �߰� - 



// FI_EVENT
#define T1_FI_EVENT_NOTIFY_WARP			0x00		// F -> I
#define T1_FI_EVENT_NOTIFY_WARP_OK		0x01		// I -> F
#define T1_FI_EVENT_GET_WARP_INFO		0x02		// F -> I
#define T1_FI_EVENT_GET_WARP_INFO_OK	0x03		// I -> F
#define T1_FI_EVENT_CHAT_BLOCK			0x04		// 2008-12-30 by cmkwon, ������ ä�� ���� ī�� ���� - F->I

// IC_CHAT
#define T1_IC_CHAT_ALL					0x00	// ������, ��ڿ�
#define T1_IC_CHAT_MAP					0x01	// �� ��ü
#define T1_IC_CHAT_REGION				0x02	// ������ �Ʊ׵鿡�Ը�
#define T1_IC_CHAT_PTOP					0x03	// 1:1
#define T1_IC_CHAT_PARTY				0x04	// ��Ƽ
#define T1_IC_CHAT_GUILD				0x05	// ���
#define T1_IC_CHAT_GET_GUILD			0x06
#define T1_IC_CHAT_GET_GUILD_OK			0x07
#define T1_IC_CHAT_CHANGE_GUILD			0x08
#define T1_IC_CHAT_CHANGE_GUILD_OK		0x09
#define T1_IC_CHAT_CHANGE_PARTY			0x0A
#define T1_IC_CHAT_CHANGE_PARTY_OK		0x0B
#define T1_IC_CHAT_CHANGE_CHAT_FLAG		0x0C
#define T1_IC_CHAT_POSITION				0x0D
#define T1_IC_CHAT_BLOCK				0x0E
#define T1_IC_CHAT_GET_BLOCK			0x0F
#define T1_IC_CHAT_GET_BLOCK_OK			0x10
#define T1_IC_CHAT_BLOCK_YOU			0x11
#define T1_IC_CHAT_FRIENDLIST_AND_REJECTLIST_LOADING	0x12	// No Body
#define T1_IC_CHAT_FRIENDLIST_LOADING_OK	0x13
#define T1_IC_CHAT_FRIENDLIST_INSERT		0x14
#define T1_IC_CHAT_FRIENDLIST_INSERT_OK		0x15
#define T1_IC_CHAT_FRIENDLIST_DELETE		0x16
#define T1_IC_CHAT_FRIENDLIST_DELETE_OK		0x17
#define T1_IC_CHAT_FRIENDLIST_REFRESH		0x18	// No Body
#define T1_IC_CHAT_FRIENDLIST_REFRESH_OK	0x19
#define T1_IC_CHAT_REJECTLIST_LOADING_OK	0x1A
#define T1_IC_CHAT_REJECTLIST_INSERT		0x1B
#define T1_IC_CHAT_REJECTLIST_INSERT_OK		0x1C
#define T1_IC_CHAT_REJECTLIST_DELETE		0x1D
#define T1_IC_CHAT_REJECTLIST_DELETE_OK		0x1E	
#define T1_IC_CHAT_FRIENDLIST_INSERT_NOTIFY	0x1F	// 2009-01-13 by cmkwon, ģ�� ��Ͻ� ���濡�� �˸� �ý��� ���� - 

#define T1_IC_CHAT_SELL_ALL					0x30	// �Ÿ� ��ü ä��
#define T1_IC_CHAT_CASH_ALL					0x31	// ���� ��ü ä��
#define T1_IC_CHAT_INFLUENCE_ALL			0x32	// ���� ��ü ä�� - ���������ڸ� ����
#define T1_IC_CHAT_ARENA					0x33	// 2007-05-02 by dhjin, �Ʒ��� ä��
#define T1_IC_CHAT_WAR						0x34	// 2008-05-19 by dhjin, EP3 - ä�� �ý��� ����, ���� ä��
#if _RAT_CHAT_SYSTEM
#define T1_IC_CHAT_INFLUENCE_ALL_RAT		0x37
#endif
#define T1_IC_CHAT_CHATROOM					0x35	// 2008-06-18 by dhjin, EP3 ä�ù� - 
#define T1_IC_CHAT_INFINITY					0x36	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ä��

// FI_CHAT (IM Server --> Field Server)
#define T1_FI_CHAT_MAP						0x00
#define T1_FI_CHAT_REGION					0x01
#define T1_FI_CHAT_CHANGE_CHAT_FLAG			0x02
#define T1_FI_CHAT_CASH_ALL					0x03	// ���� ��ü ä��
#define	T1_FI_CHAT_ARENA					0x04	// 2007-05-02 by dhjin, �Ʒ��� ä��
#define	T1_FI_CHAT_OUTPOST_GUILD			0x05	// 2007-10-06 by cmkwon, ���� ���� ������ ������ ���� ä�� ����
#define T1_FI_CHAT_INFINITY					0x06	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ä��

#define T1_FI_CHAT_ONLINE_EACHOTHER_FRIEND_COUNT_OK	0x10	// 2006-07-18 by cmkwon, ���� ����� �¶��� ģ�� ī��Ʈ
#define T1_IC_CHAT_ONLINE_EACHOTHER_FRIEND_COUNT	0x11	// 2008-07-11 by dhjin, EP3 ģ����� -
// FC_CHAT (Field Server --> Clients)
#define T1_FC_CHAT_MAP								0x00
#define T1_FC_CHAT_REGION							0x01
#define T1_FC_CHAT_CASH_ALL							0x02
#define T1_FC_CHAT_ARENA							0x03			// 2007-05-02 by dhjin	F->C(n)
#define T1_FC_CHAT_INFINITY							0x12			// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ä��
#define T1_FC_CHAT_ALL_INFLUENCE					0x10			// 2007-08-09 by cmkwon, ��� ���¿� ä�� �����ϱ� - ��������Ÿ�� �߰�
#define T1_FC_CHAT_OUTPOST_GUILD					0x11			// 2007-10-06 by cmkwon, ���� ���� ������ ������ ���� ä�� ����
#define T1_FC_CHAT_LETTER_REQUEST_TITLE				0x21			// 2008-04-29 by dhjin, EP3 ���� �ý��� - ���� ����Ʈ ��û C->F
#define T1_FC_CHAT_LETTER_REQUEST_TITLE_OK_HEADER	0x22			// 2008-04-29 by dhjin, EP3 ���� �ý��� - ���� ����Ʈ ���� F->C
#define T1_FC_CHAT_LETTER_REQUEST_TITLE_OK			0x23			// 2008-04-29 by dhjin, EP3 ���� �ý��� - ���� ����Ʈ ���� F->C
#define T1_FC_CHAT_LETTER_REQUEST_TITLE_OK_DONE		0x24			// 2008-04-29 by dhjin, EP3 ���� �ý��� - ���� ����Ʈ ���� F->C
#define T1_FC_CHAT_LETTER_READ						0x25			// 2008-04-29 by dhjin, EP3 ���� �ý��� - ���� �б� ��û C->F
#define T1_FC_CHAT_LETTER_READ_OK					0x26			// 2008-04-29 by dhjin, EP3 ���� �ý��� - ���� �б� �Ϸ� F->C
#define T1_FC_CHAT_LETTER_DELETE					0x27			// 2008-04-29 by dhjin, EP3 ���� �ý��� - ���� ����� ��û C->F
#define T1_FC_CHAT_LETTER_DELETE_OK					0x28			// 2008-04-29 by dhjin, EP3 ���� �ý��� - ���� ����� �Ϸ� F->C
#define T1_FC_CHAT_LETTER_SEND						0x29			// 2008-05-08 by dhjin, EP3 ���� �ý��� - ���� ���� C->F
#define T1_FC_CHAT_LETTER_SEND_OK					0x2A			// 2008-05-08 by dhjin, EP3 ���� �ý��� - ���� ���� �Ϸ� F->C
#define T1_FC_CHAT_LETTER_RECEIVE					0x2B			// 2008-05-08 by dhjin, EP3 ���� �ý��� - ���� ���� ���� F->C
#define T1_FC_CHAT_ALLLETTER_REQUEST_TITLE				0x31			// 2008-05-09 by dhjin, EP3 ���� �ý��� - ��ü ���� ����Ʈ ��û C->F
#define T1_FC_CHAT_ALLLETTER_REQUEST_TITLE_OK_HEADER	0x32		// 2008-05-09 by dhjin, EP3 ���� �ý��� - ��ü ���� ����Ʈ ���� F->C
#define T1_FC_CHAT_ALLLETTER_REQUEST_TITLE_OK			0x33			// 2008-05-09 by dhjin, EP3 ���� �ý��� - ��ü ���� ����Ʈ ���� F->C
#define T1_FC_CHAT_ALLLETTER_REQUEST_TITLE_OK_DONE		0x34			// 2008-05-09 by dhjin, EP3 ���� �ý��� - ��ü ���� ����Ʈ ���� F->C
#define T1_FC_CHAT_ALLLETTER_READ						0x35			// 2008-05-09 by dhjin, EP3 ���� �ý��� - ��ü ���� �б� ��û C->F
#define T1_FC_CHAT_ALLLETTER_READ_OK					0x36			// 2008-05-09 by dhjin, EP3 ���� �ý��� - ��ü ���� �б� �Ϸ� F->C
#define T1_FC_CHAT_ALLLETTER_DELETE						0x37			// 2008-05-09 by dhjin, EP3 ���� �ý��� - ��ü ���� ����� ��û C->F
#define T1_FC_CHAT_ALLLETTER_DELETE_OK					0x38			// 2008-05-09 by dhjin, EP3 ���� �ý��� - ��ü ���� ����� �Ϸ� F->C
#define T1_FC_CHAT_ALLLETTER_SEND						0x39			// 2008-05-09 by dhjin, EP3 ���� �ý��� - ��ü ���� ���� C->F
#define T1_FC_CHAT_ALLLETTER_SEND_OK					0x3A			// 2008-05-09 by dhjin, EP3 ���� �ý��� - ��ü ���� ���� �Ϸ� F->C 
#define T1_FC_CHAT_ALLLETTER_RECEIVE					0x3B			// 2008-05-09 by dhjin, EP3 ���� �ý��� - ��ü ���� ���� ���� F->C

// FC_CHARACTER
#define T1_FC_CHARACTER_CREATE						0x00
#define T1_FC_CHARACTER_CREATE_OK					0x01
#define T1_FC_CHARACTER_DELETE						0x02
#define T1_FC_CHARACTER_DELETE_OK					0x03
#define T1_FC_CHARACTER_GET_CHARACTER				0x04
#define T1_FC_CHARACTER_GET_CHARACTER_OK			0x05
#define T1_FC_CHARACTER_GAMESTART					0x06
#define T1_FC_CHARACTER_GAMESTART_OK				0x07
#define T1_FC_CHARACTER_CONNECT_GAMESTART			0x08
#define T1_FC_CHARACTER_CONNECT_GAMESTART_OK		0x09
#define T1_FC_CHARACTER_GAMEEND						0x0A
#define T1_FC_CHARACTER_GAMEEND_OK					0x0B
#define T1_FC_CHARACTER_REPAIR						0x0C
#define T1_FC_CHARACTER_REPAIR_OK					0x0D
#define T1_FC_CHARACTER_REPAIR_ERR					0x0E
#define T1_FC_CHARACTER_DOCKING						0x0F
#define T1_FC_CHARACTER_UNDOCKING					0x10
#define T1_FC_CHARACTER_DOCKING_ERR					0x11
#define T1_FC_CHARACTER_GET_OTHER_INFO				0x12
#define T1_FC_CHARACTER_GET_OTHER_INFO_OK			0x13
#define T1_FC_CHARACTER_GET_MONSTER_INFO_OK			0x14
#define T1_FC_CHARACTER_CHANGE_UNITKIND				0x15
#define T1_FC_CHARACTER_CHANGE_STAT					0x16
#define T1_FC_CHARACTER_CHANGE_TOTALGEAR_STAT		0x17
#define T1_FC_CHARACTER_CHANGE_FRIEND				0x18
#define T1_FC_CHARACTER_CHANGE_EXP					0x19
#define T1_FC_CHARACTER_CHANGE_BODYCONDITION		0x1A
#define T1_FC_CHARACTER_CHANGE_BODYCONDITION_SKILL	0x1B
#define T1_FC_CHARACTER_CHANGE_INFLUENCE_TYPE		0x1C
#define T1_FC_CHARACTER_CHANGE_STATUS				0x1D
#define T1_FC_CHARACTER_CHANGE_PKPOINT				0x1E
#define T1_FC_CHARACTER_CHANGE_CURRENTHPDPSPEP		0x1F
#define T1_FC_CHARACTER_CHANGE_CURRENTHP			0x20
#define T1_FC_CHARACTER_CHANGE_CURRENTDP			0x21
#define T1_FC_CHARACTER_CHANGE_CURRENTSP			0x22
#define T1_FC_CHARACTER_CHANGE_CURRENTEP			0x23
#define T1_FC_CHARACTER_CHANGE_MAPNAME				0x24
#define T1_FC_CHARACTER_CHANGE_PETINFO				0x25
#define T1_FC_CHARACTER_CHANGE_POSITION				0x26
#define T1_FC_CHARACTER_CHANGE_LEVEL				0x27
#define T1_FC_CHARACTER_USE_BONUSSTAT				0x28
// �Ʒ��� ���ǵǾ� ���� #define T1_FC_CHARACTER_USE_BONUSSTAT_OK					0x67	// F->C, 2006-09-18 by cmkwon
#define T1_FC_CHARACTER_DEAD_NOTIFY					0x29	// F->C, ĳ���Ͱ� �������� Ŭ���̾�Ʈ�� �˸�
#define T1_FC_CHARACTER_GET_ACCOUNTUNIQUENUMBER		0x2A
#define T1_FC_CHARACTER_GET_ACCOUNTUNIQUENUMBER_OK	0x2B
#define T1_FC_CHARACTER_APPLY_COLLISION_DAMAGE		0x2C
#define T1_FC_CHARACTER_GET_OTHER_MOVE				0x2D
#define T1_FC_CHARACTER_DELETE_OTHER_INFO			0x2E
#define T1_FC_CHARACTER_DEAD_GAMESTART				0x2F	// C -> F
#define T1_FC_CHARACTER_OTHER_REVIVED				0x30	// F -> C
#define T1_FC_CHARACTER_GET_OTHER_RENDER_INFO		0x31
#define T1_FC_CHARACTER_GET_OTHER_RENDER_INFO_OK	0x32
#define T1_FC_CHARACTER_CHANGE_BODYCONDITION_ALL	0x33
#define T1_FC_CHARACTER_CHANGE_PROPENSITY			0x34	// F->C // 2005-08-22 by cmkwon, ������� �ʴ� ���� ������
#define T1_FC_CHARACTER_CHANGE_HPDPSPEP				0x35
#define T1_FC_CHARACTER_SHOW_EFFECT					0x36	// C->F
#define T1_FC_CHARACTER_SHOW_EFFECT_OK				0x37	// F->C
#define T1_FC_CHARACTER_GET_OTHER_PARAMFACTOR		0x38	// C->F
#define T1_FC_CHARACTER_GET_OTHER_PARAMFACTOR_OK	0x39	// F->C
#define T1_FC_CHARACTER_SEND_PARAMFACTOR_IN_RANGE	0x3A	// C->F
#define T1_FC_CHARACTER_GET_OTHER_SKILL_INFO		0x3B	// C->F
#define T1_FC_CHARACTER_GET_OTHER_SKILL_INFO_OK		0x3C	// F->C
#define T1_FC_CHARACTER_SPEED_HACK_USER				0x3D	// C->F
#define T1_FC_CHARACTER_CHANGE_CHARACTER_MENT		0x3E	// F->C(n)
#define T1_FC_CHARACTER_GET_CASH_MONEY_COUNT		0x3F	// C->F
#define T1_FC_CHARACTER_GET_CASH_MONEY_COUNT_OK		0x40	// F->C
#define T1_FC_CHARACTER_CASH_PREMIUM_CARD_INFO		0x41	// F->C
#define T1_FC_CHARACTER_TUTORIAL_SKIP				0x42	// C->F
#define T1_FC_CHARACTER_TUTORIAL_SKIP_OK			0x43	// F->C
#define T1_FC_CHARACTER_CHANGE_CHARACTER_MODE		0x50	// C->F
#define T1_FC_CHARACTER_CHANGE_CHARACTER_MODE_OK	0x51	// F->C(n)
#define T1_FC_CHARACTER_FALLING_BY_FUEL_ALLIN		0x52	// C->F
#define T1_FC_CHARACTER_WARP_BY_AGEAR_LANDING_FUEL_ALLIN	0x53	// C->F
#define T1_FC_CHARACTER_GET_REAL_WEAPON_INFO				0x60	// F->C// 2005-12-21 by cmkwon
#define T1_FC_CHARACTER_GET_REAL_WEAPON_INFO_OK				0x61	// C->F// 2005-12-21 by cmkwon
#define T1_FC_CHARACTER_GET_REAL_ENGINE_INFO				0x62	// F->C// 2005-12-21 by cmkwon
#define T1_FC_CHARACTER_GET_REAL_ENGINE_INFO_OK				0x63	// C->F// 2005-12-21 by cmkwon
#define T1_FC_CHARACTER_GET_REAL_TOTAL_WEIGHT				0x64	// F->C// 2005-12-21 by cmkwon
#define T1_FC_CHARACTER_GET_REAL_TOTAL_WEIGHT_OK			0x65	// C->F// 2005-12-21 by cmkwon
#define T1_FC_CHARACTER_MEMORY_HACK_USER					0x66	// C->F// 2005-12-21 by cmkwon
#define T1_FC_CHARACTER_USE_BONUSSTAT_OK					0x67	// F->C, 2006-09-18 by cmkwon
#define T1_FC_CHARACTER_UPDATE_SUBLEADER					0x68	// C->F, 2007-02-14 by dhjin
#define T1_FC_CHARACTER_UPDATE_SUBLEADER_OK					0x6A	// F->C, 2007-10-06 by dhjin

#define T1_FC_CHARACTER_OBSERVER_START						0x69	// C->F, 2007-03-27 by dhjin

#define T1_FC_CHARACTER_OBSERVER_START_OK					0x70	// F->C, 2007-03-27 by dhjin
#define T1_FC_CHARACTER_OBSERVER_END						0x71	// C->F, 2007-03-27 by dhjin
#define T1_FC_CHARACTER_OBSERVER_END_OK						0x72	// F->C, 2007-03-27 by dhjin
#define T1_FC_CHARACTER_OBSERVER_INFO						0x73	// F->C, 2007-03-27 by dhjin
#define T1_FC_CHARACTER_OBSERVER_REG						0x74	// F->C, 2007-03-27 by dhjin
#define T1_FC_CHARACTER_SHOW_MAP_EFFECT						0x75	// C->F, // 2007-04-20 by cmkwon
#define T1_FC_CHARACTER_SHOW_MAP_EFFECT_OK					0x76	// F->C(n), // 2007-04-20 by cmkwon
#define T1_FC_CHARACTER_PAY_WARPOINT						0x77	// F->C(n), // 2007-05-16 by dhjin
#define T1_FC_CHARACTER_WATCH_INFO							0x78	// F->C, // 2007-06-19 by dhjin
#define T1_FC_CHARACTER_READY_GAMESTART_FROM_ARENA_TO_MAINSERVER	0x79	// C->F, // 2008-01-31 by dhjin, �Ʒ��� ���� - 
#define T1_FC_CHARACTER_READY_GAMESTART_FROM_ARENA_TO_MAINSERVER_OK	0x7A	// F->C, // 2008-01-31 by dhjin, �Ʒ��� ���� - 
#define T1_FC_CHARACTER_GAMESTART_FROM_ARENA_TO_MAINSERVER	0x7B	// C->F, // 2008-01-10 by dhjin, �Ʒ��� ���� - 
#define T1_FC_CHARACTER_GET_USER_INFO						0x7C	// C->F, // 2008-06-23 by dhjin, EP3 ���������ɼ� -
#define T1_FC_CHARACTER_GET_USER_INFO_OK					0x7D	// F->C, // 2008-06-23 by dhjin, EP3 ���������ɼ� -
#define T1_FC_CHARACTER_CHANGE_INFO_OPTION_SECRET			0x7E	// C->F, // 2008-06-23 by dhjin, EP3 ���������ɼ� -
#define T1_FC_CHARACTER_CHANGE_INFO_OPTION_SECRET_OK		0x7F	// F->C, // 2008-06-23 by dhjin, EP3 ���������ɼ� -
#define T1_FC_CHARACTER_CHANGE_NICKNAME						0x80	// C->F, // 2009-02-12 by cmkwon, EP3-3 ���巩ŷ�ý��� ���� - 
#define T1_FC_CHARACTER_CHANGE_NICKNAME_OK					0x81	// F->C, // 2009-02-12 by cmkwon, EP3-3 ���巩ŷ�ý��� ���� - 
#define T1_FC_CHARACTER_CHANGE_START_CITY_MAPINDEX			0x82	// C->F, // 2009-10-12 by cmkwon, ������ī ���� ��� ���� - 
#define T1_FC_CHARACTER_CHANGE_START_CITY_MAPINDEX_OK		0x83	// F->C, // 2009-10-12 by cmkwon, ������ī ���� ��� ���� - 
#define T1_FC_CHARACTER_CHANGE_ADDED_INVENTORY_COUNT		0x84	// F->C, // 2009-11-02 by cmkwon, ĳ��(�κ�/â�� Ȯ��) ������ �߰� ���� - 
#define T1_FC_CHARACTER_DEBUFF_DOT_INFO						0x90	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - C -> F
#define T1_FC_CHARACTER_DEBUFF_DOT_INFO_OK					0x91	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - F -> C
#define T1_FC_CHARACTER_DEBUFF_DOT_APPLYING					0x92	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - F -> C
#define T1_FC_CHARACTER_DEBUFF_DOT_RELEASE					0x93	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - F -> C
//////////////////////////////////////////////////////////////////
// 2012-06-05 by jhseol, ���۹̸����� - Ŭ���û ��Ŷ �߰�
#define T1_FC_CHARACTER_GET_USER_ITEM_INFO					0x94	// 2012-06-05 by jhseol, ���۹̸����� - ���캼 �ɸ��� UID
#define T1_FC_CHARACTER_GET_USER_ITEM_INFO_OK				0x95	// 2012-06-05 by jhseol, ���۹̸����� - ���캻 �ɸ����� ��������
#define T1_FC_CHARACTER_GET_USER_ITEM_INFO_OK_DONE			0x96	// 2012-06-05 by jhseol, ���۹̸����� - ���캻 �ɸ����� ��������
#define T1_FC_CHARACTER_GET_USER_ITEM_INFO_SECRET			0x97	// 2012-07-12 by isshin ���۹̸����� On / Off ��� - ���� ����
#define T1_FC_CHARACTER_GET_USER_ITEM_INFO_SECRET_OK		0x98	// 2012-07-12 by isshin ���۹̸����� On / Off ��� - ���� ����

// 2012-10-10 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������
#define T1_FC_CHARACTER_KILLCOUNT							0x99	// 2012-10-10 by jhjang ųī��Ʈ �ý��� �߰�
#define T1_FC_CHARACTER_RESTCOUNT							0x9A	// 2012-10-10 by jhjang �޽� ����ġ �ý��� �߰�
#define T1_FC_CHARACTER_BONUS_EXP_RATE						0x9B	// 2012-10-10 by jhjang ���ʽ� ����ġ ǥ�� �߰�
// end 2012-10-10 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������

//////////////////////////////////////////////////////////////////////
// 2012-10-05 by jhseol, NPlay PC�� ��� - ��ü ���� �� NPlay ���� Connect
#define T1_FC_CHARACTER_PCBANG_PREMIUN_APPLY				0x9C	// pc�� �����̾� ���� ����

// 2012-10-17 by bhsohn XignCode�۾�
#define T1_FC_CHARACTER_XIGNCODE_S_ACK_PACKET					0x9D
#define T1_FC_CHARACTER_XIGNCODE_C_ACK_PACKET					0x9E
#define T1_FC_CHARACTER_XIGNCODE_C_ACK_CODE						0x9F
// end 2012-10-17 by bhsohn XignCode�۾�

#define T1_FC_CHARACTER_PAY_CONTRIBUTIONPOINT				0xA0	// 2013-08-14 by jhseol, ������ ������ - ��������Ʈ ���� ����
#define T1_FC_BUGTRAP_ACCEPT								0xA1	// 2014-01-27 by bckim, ���� Ʈ��	

// FN_CHARACTER
#define T1_FN_CHARACTER_CHANGE_UNITKIND				0x01
#define T1_FN_CHARACTER_CHANGE_BODYCONDITION		0x02
#define T1_FN_CHARACTER_CHANGE_HPDPSPEP				0x03
#define T1_FN_CHARACTER_CHANGE_CURRENTHPDPSPEP		0x04
#define T1_FN_CHARACTER_CHANGE_MAPNAME				0x05
#define T1_FN_CHARACTER_CHANGE_POSITION				0x06
#define T1_FN_CHARACTER_CHANGE_STEALTHSTATE			0x07
#define T1_FN_CHARACTER_CHANGE_CHARACTER_MODE_OK	0x08
#define T1_FN_CHARACTER_CHANGE_INFLUENCE_TYPE		0x09	// F->I, 2005-12-03 by cmkwon
#define T1_FN_CHARACTER_CHANGE_INVISIBLE			0x0A	// F->I, 2006-11-27 by dhjin

// FC_MOVE
#define T1_FC_MOVE						0x00
#define T1_FC_MOVE_OK					0x01
#define T1_FC_MOVE_LOCKON				0x02
#define T1_FC_MOVE_LOCKON_OK			0x03
#define T1_FC_MOVE_UNLOCKON				0x04
#define T1_FC_MOVE_UNLOCKON_OK			0x05
#define T1_FC_MOVE_LANDING				0x06
#define T1_FC_MOVE_LANDING_OK			0x07
#define T1_FC_MOVE_LANDING_DONE			0x08	// C->F, ���� �ϷḦ �˸�
#define T1_FC_MOVE_TAKEOFF				0x09
#define T1_FC_MOVE_TAKEOFF_OK			0x0A
#define T1_FC_MISSILE_MOVE_OK			0x0B
#define T1_FC_MOVE_TARGET				0x0C
#define T1_FC_MOVE_WEAPON_VEL			0x0D
#define T1_FC_MOVE_WEAPON_VEL_OK		0x0E
#define T1_FC_MOVE_ROLLING				0x10
#define T1_FC_MOVE_ROLLING_OK			0x11
#define T1_FC_MOVE_HACKSHIELD_GuidReqMsg		0xA0	// 2006-06-05 by cmkwon, Anlab - HackShield
#define T1_FC_MOVE_HACKSHIELD_GuidAckMsg		0xA1	// 2006-06-05 by cmkwon, Anlab - HackShield
#define T1_FC_MOVE_HACKSHIELD_CRCReqMsg			0xA2	// 2006-06-05 by cmkwon, Anlab - HackShield
#define T1_FC_MOVE_HACKSHIELD_CRCAckMsg			0xA3	// 2006-06-05 by cmkwon, Anlab - HackShield
#define T1_FC_MOVE_HACKSHIELD_HACKING_CLIENT	0xA4	// 2006-06-05 by cmkwon, Anlab - HackShield
#define T1_FC_MOVE_XIGNCODE_REQ_SCAN_INIT		0xB0	// 2008-11-28 by cmkwon, �븸 Netpower_Tpe XignCode(���Ӱ���) ���� - S->C(1)
#define T1_FC_MOVE_XIGNCODE_REQ_SCAN_INIT_OK	0xB1	// 2008-11-28 by cmkwon, �븸 Netpower_Tpe XignCode(���Ӱ���) ���� - C->S
#define T1_FC_MOVE_XIGNCODE_REQ_SCAN_CHECK		0xB2	// 2008-11-28 by cmkwon, �븸 Netpower_Tpe XignCode(���Ӱ���) ���� - S->C(1)
#define T1_FC_MOVE_XIGNCODE_REQ_SCAN_CHECK_OK	0xB3	// 2008-11-28 by cmkwon, �븸 Netpower_Tpe XignCode(���Ӱ���) ���� - C->S
#define T1_FC_MOVE_NPROTECT_REQ_AUTH_DATA		0xB4	// 2009-03-09 by cmkwon, �Ϻ� Arario nProtect�� CS���� �����ϱ� - S->C(1)
#define T1_FC_MOVE_NPROTECT_REQ_AUTH_DATA_OK	0xB5	// 2009-03-09 by cmkwon, �Ϻ� Arario nProtect�� CS���� �����ϱ� - C->S
#define T1_FC_MOVE_XTRAP_REQ_STEP				0xB6	// 2009-10-06 by cmkwon, ��Ʈ�� ���� ���� X-TRAP���� ���� - S->C(1)
#define T1_FC_MOVE_XTRAP_REQ_STEP_OK			0xB7	// 2009-10-06 by cmkwon, ��Ʈ�� ���� ���� X-TRAP���� ���� - C(1)->S
#define T1_FC_MOVE_APEX_REQ_APEXDATA			0xB8	// 2009-11-04 by cmkwon, �±� ���Ӱ��� Apex�� ���� - S->C(1)
#define T1_FC_MOVE_APEX_REQ_APEXDATA_OK			0xB9	// 2009-11-04 by cmkwon, �±� ���Ӱ��� Apex�� ���� - C(1)->S
#define T1_FC_MOVE_NPROTECT_NEW_REQ_AUTH_DATA		0xBA	// 2015-01-07 by jwLee �������� nProtector S->C
#define T1_FC_MOVE_NPROTECT_NEW_REQ_AUTH_DATA_OK	0xBB	// 2015-01-07 by jwLee �������� nProtector C->S

// FN_MOVE
#define T1_FN_MONSTER_MOVE				0x00
#define T1_FN_MOVE_OK					0x01
#define T1_FN_MOVE_LOCKON				0x02
#define T1_FN_MOVE_LOCKON_OK			0x03
#define T1_FN_MOVE_LOCKON_AVOID			0x04
#define T1_FN_MOVE_LOCKON_AVOID_OK		0x05
#define T1_FN_MISSILE_MOVE				0x06
#define T1_FN_MONSTER_HPRECOVERY		0x07
#define T1_FN_MONSTER_HIDE				0x08
#define T1_FN_MONSTER_SHOW				0x09

// FC_BATTLE
#define T1_FC_BATTLE_ATTACK						0x00	// C->F
#define T1_FC_BATTLE_ATTACK_OK					0x01	// F->C_in_range
#define T1_FC_BATTLE_ATTACK_FIND				0x02	// C->F
#define T1_FC_BATTLE_ATTACK_FIND_OK				0x03	// F->C_in_range
#define T1_FC_BATTLE_DROP_MINE					0x04	// C->F
#define T1_FC_BATTLE_DROP_MINE_OK				0x05	// F->C_in_range, ������ �����ֱ�
#define T1_FC_BATTLE_MINE_ATTACK				0x06	// C->F
#define T1_FC_BATTLE_MINE_ATTACK_OK				0x07	// F->C_in_range
#define T1_FC_BATTLE_MINE_ATTACK_FIND			0x08	// C->F
#define T1_FC_BATTLE_MINE_ATTACK_FIND_OK		0x09	// F->C_in_range
#define T1_FC_BATTLE_REQUEST_PK					0x0A
#define T1_FC_BATTLE_REQUEST_PK_OK				0x0B
#define T1_FC_BATTLE_CANCEL_PK					0x0C
#define T1_FC_BATTLE_REQUEST_P2P_PK				0x0D
#define T1_FC_BATTLE_REQUEST_P2P_PK_OK			0x0E
#define T1_FC_BATTLE_ACCEPT_REQUEST_P2P_PK		0x0F
#define T1_FC_BATTLE_ACCEPT_REQUEST_P2P_PK_OK	0x10
#define T1_FC_BATTLE_REJECT_REQUEST_P2P_PK		0x11
#define T1_FC_BATTLE_REJECT_REQUEST_P2P_PK_OK	0x12
#define T1_FC_BATTLE_SURRENDER_P2P_PK			0x13
#define T1_FC_BATTLE_SURRENDER_P2P_PK_OK		0x14
#define T1_FC_BATTLE_ACCEPT_SURRENDER_P2P_PK	0x15
#define T1_FC_BATTLE_REJECT_SURRENDER_P2P_PK	0x16
#define T1_FC_BATTLE_REJECT_SURRENDER_P2P_PK_OK	0x17
#define T1_FC_BATTLE_END_P2P_PK					0x18
#define T1_FC_BATTLE_ATTACK_EXPLODE_ITEM		0x19
#define T1_FC_BATTLE_ATTACK_HIDE_ITEM			0x1A
#define T1_FC_BATTLE_ATTACK_EXPLODE_ITEM_W_KIND	0x1B
#define T1_FC_BATTLE_ATTACK_HIDE_ITEM_W_KIND	0x1C
#define T1_FC_BATTLE_TOGGLE_SHIELD				0x1D	// No Body
#define T1_FC_BATTLE_TOGGLE_SHIELD_RESULT		0x1E
#define T1_FC_BATTLE_DROP_DUMMY					0x1F
#define T1_FC_BATTLE_DROP_DUMMY_OK				0x20
#define T1_FC_BATTLE_DROP_FIXER					0x21
#define T1_FC_BATTLE_DROP_FIXER_OK				0x22
#define T1_FC_BATTLE_PRI_BULLET_RELOADED		0x23
#define T1_FC_BATTLE_SEC_BULLET_RELOADED		0x24
#define T1_FC_BATTLE_SHIELD_DAMAGE				0x25
#define T1_FC_BATTLE_TOGGLE_DECOY				0x26	// C->F, No Body
#define T1_FC_BATTLE_TOGGLE_DECOY_OK			0x27	// F->C
#define T1_FC_BATTLE_SHOW_DAMAGE				0x28	// F->C
#define T1_FC_BATTLE_ATTACK_EVASION				0x29	// C->F, // 2005-12-12 by cmkwon
#define T1_FC_BATTLE_ATTACK_EVASION_OK			0x2A	// F->C(1), // 2005-12-12 by cmkwon
#define T1_FC_BATTLE_DELETE_DUMMY_OK			0x30	// 2006-12-04 by dhjin, F->C(n)
#define T1_FC_BATTLE_EXPLODE_DUMMY_OK			0x31	// 2006-12-04 by dhjin, F->C(n)
#define T1_FC_BATTLE_MONSTER_BARRIER_USING		0x32	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - F -> C
#define T1_FC_BATTLE_MONSTER_BARRIER_USE		0x33	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - F -> C


// FN_BATTLE
#define T1_FN_BATTLE_ATTACK_PRIMARY				0x00
#define T1_FN_BATTLE_ATTACK_RESULT_PRIMARY		0x01
#define T1_FN_BATTLE_ATTACK_SECONDARY			0x02
#define T1_FN_BATTLE_ATTACK_RESULT_SECONDARY	0x03
#define T1_FN_BATTLE_ATTACK_FIND				0x04
#define T1_FN_BATTLE_ATTACK_FIND_RESULT			0x05
#define T1_FN_BATTLE_SET_ATTACK_CHARACTER		0x06
#define T1_FN_BATTLE_DROP_FIXER					0x07
#define T1_FN_BATTLE_DROP_FIXER_OK				0x08
#define T1_FN_BATTLE_ATTACK_HIDE_ITEM_W_KIND	0x09
#define T1_FN_BATTLE_ATTACK_SKILL				0x0A			// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - N -> F
#define T1_FN_BATTLE_ATTACK_SKILL_CANCEL		0x0B			// 2010-03-31 by dhjin, ���Ǵ�Ƽ(�������) - N -> F

// FC_PARTY
#define T1_FC_PARTY_CREATE_OK							0x00
#define T1_FC_PARTY_REQUEST_INVITE						0x01
#define T1_FC_PARTY_REQUEST_INVITE_QUESTION				0x02
#define T1_FC_PARTY_ACCEPT_INVITE						0x03
#define T1_FC_PARTY_REJECT_INVITE						0x04
#define T1_FC_PARTY_REJECT_INVITE_OK					0x05
#define T1_FC_PARTY_GET_MEMBER							0x06
#define T1_FC_PARTY_PUT_MEMBER							0x07
#define T1_FC_PARTY_GET_ALL_MEMBER						0x08
#define T1_FC_PARTY_PUT_ALL_MEMBER						0x09
#define T1_FC_PARTY_UPDATE_MEMBER_INFO_ALL				0x0A
#define T1_FC_PARTY_UPDATE_MEMBER_INFO_LEVEL			0x0B
#define T1_FC_PARTY_UPDATE_MEMBER_INFO_HP				0x0C
#define T1_FC_PARTY_UPDATE_MEMBER_INFO_CURRENT_HP		0x0D
#define T1_FC_PARTY_UPDATE_MEMBER_INFO_DP				0x0E
#define T1_FC_PARTY_UPDATE_MEMBER_INFO_CURRENT_DP		0x0F
#define T1_FC_PARTY_UPDATE_MEMBER_INFO_SP				0x10
#define T1_FC_PARTY_UPDATE_MEMBER_INFO_CURRENT_SP		0x11
#define T1_FC_PARTY_UPDATE_MEMBER_INFO_EP				0x12
#define T1_FC_PARTY_UPDATE_MEMBER_INFO_CURRENT_EP		0x13
#define T1_FC_PARTY_UPDATE_MEMBER_INFO_BODYCONDITION	0x14
#define T1_FC_PARTY_REQUEST_PARTY_WARP					0x15
#define T1_FC_PARTY_REQUEST_PARTY_WARP_WITH_MAP_NAME	0x16
#define T1_FC_PARTY_REQUEST_PARTY_OBJECT_EVENT			0x17
#define T1_FC_PARTY_GET_OTHER_MOVE						0x18
#define T1_FC_PARTY_BATTLE_START						0x19
#define T1_FC_PARTY_BATTLE_END							0x20
#define T1_FC_PARTY_PUT_ITEM_OTHER						0x21	// F->C, �ٸ� ��Ƽ���� ������ ��� ���� ����
#define T1_FC_PARTY_AUTO_CREATED						0x30	// 2009-09-09 ~ 2010-01-26 by dhjin, ���Ǵ�Ƽ - �ڵ� ���� ���� �Ϸ� �˸�, F -> C
#define T1_FC_PARTY_AUTO_CREATED_THE_ARENA				0x31	// 2012-04-12 by jhseol, �Ʒ��� �߰����� - �ڵ���Ƽ : �ڵ����� ��Ƽ�� ������ ��Ŷ.
#define T1_FC_PARTY_REQUEST_INVITE_QUESTION_THE_ARENA	0x32	// 2012-04-12 by jhseol, �Ʒ��� �߰����� - �ڵ���Ƽ : ��Ƽ�� ���Խ�ų Ŭ�󿡰� ��Ƽ ���� �غ� ��Ŷ ������.

// FI_PARTY
#define T1_FI_PARTY_CREATE_OK							0x01
#define T1_FI_PARTY_ACCEPT_INVITE_OK					0x02
#define T1_FI_PARTY_BAN_MEMBER_OK						0x03
#define T1_FI_PARTY_LEAVE_OK							0x04
#define T1_FI_PARTY_TRANSFER_MASTER_OK					0x05
#define T1_FI_PARTY_DISMEMBER_OK						0x06
#define T1_FI_PARTY_CHANGE_FLIGHT_FORMATION_OK			0x07
#define T1_FI_PARTY_CHANGE_FLIGHT_POSITION				0x08
#define T1_FI_PARTY_CANCEL_FLIGHT_POSITION				0x09
#define T1_FI_PARTY_NOTIFY_BATTLE_PARTY					0x10
#define T1_FI_PARTY_NOTIFY_BATTLE_PARTY_OK				0x12
#define T1_FI_PARTY_ADD_MEMBER							0x13
#define T1_FI_PARTY_DELETE_MEMBER						0x14
#define T1_FI_PARTY_UPDATE_ITEM_POS						0x15	// F->I, ��Ƽ���� ������ ������ �������� �� ����
#define T1_FI_PARTY_ALL_FLIGHT_POSITION					0x16	// F->I, ��Ƽ���� �� ������ ��Ƽ������ Position
#define T1_FI_PARTY_UPDATE_PARTY_INFO					0x17
#define T1_FI_PARTY_CHANGE_EXP_DISTRIBUTE_TYPE			0x18	// 2008-06-04 by dhjin, EP3 ���� ���� - ����ġ �й� ��� ���� 
#define T1_FI_PARTY_CHANGE_ITEM_DISTRIBUTE_TYPE			0x19	// 2008-06-04 by dhjin, EP3 ���� ���� - ������ �й� ��� ����
#define T1_FI_PARTY_CHANGE_FORMATION_SKILL				0x20	// 2009-08-03 by cmkwon, EP3-4 ���� ���� ��ų ���� - 
#define T1_FI_PARTY_AUTO_CREATE							0x30	// 2009-09-09 ~ 2010-01-26 by dhjin, ���Ǵ�Ƽ - �ڵ� ���� ���� ��û, F -> I
#define T1_FI_PARTY_AUTO_CREATE_OK						0x31	// 2009-09-09 ~ 2010-01-26 by dhjin, ���Ǵ�Ƽ - �ڵ� ���� ���� �Ϸ�, I -> F
#define T1_FI_PARTY_DISCONNECT_LEAVE_OK					0x32	// 2009-09-09 ~ 2010-01-27 by dhjin, ���Ǵ�Ƽ - ���� ���� ���� ��Ƽ���� Ż��ó��!
#define T1_FI_PARTY_UPDATE_ITEM_TRANSFORMER_OK			0x33	// F->I, // 2010-03-18 by cmkwon, ���ͺ��� ���� - 
#define T1_FI_PARTY_ARENA_TEAM_NUM						0x34	// F->I, // 2012-04-12 by jhseol, �Ʒ��� �߰����� - �ڵ���Ƽ : ����ȣ ������

// FI_CHARACTER
#define T1_FI_CHARACTER_DELETE_CHARACTER				0x01
#define T1_FI_CHARACTER_CHANGE_LEVEL					0x02
#define T1_FI_CHARACTER_UPDATE_GUILD_INFO				0x03
#define T1_FI_CHARACTER_UPDATE_MAP_CHANNEL				0x04
#define T1_FI_CHARACTER_CHANGE_INFLUENCE_TYPE			0x05	// F->I, 2005-12-03 by cmkwon
#define T1_FI_UPDATE_SUBLEADER							0x06	// F->I, 2005-12-03 by cmkwon
#define T1_FI_CREATE_GUILD_BY_SUBLEADER					0x07	// F->I, 2007-10-06 by dhjin

// IC_PARTY
#define T1_IC_PARTY_CREATE								0x00
#define T1_IC_PARTY_ACCEPT_INVITE_OK					0x01
#define T1_IC_PARTY_GET_MEMBER							0x02
#define T1_IC_PARTY_PUT_MEMBER							0x03
#define T1_IC_PARTY_GET_ALL_MEMBER						0x04
#define T1_IC_PARTY_PUT_ALL_MEMBER						0x05
#define T1_IC_PARTY_BAN_MEMBER							0x06
#define T1_IC_PARTY_BAN_MEMBER_OK						0x07
#define T1_IC_PARTY_LEAVE								0x08
#define T1_IC_PARTY_LEAVE_OK							0x09
#define T1_IC_PARTY_TRANSFER_MASTER						0x0A
#define T1_IC_PARTY_TRANSFER_MASTER_OK					0x0B
#define T1_IC_PARTY_DISMEMBER							0x0C
#define T1_IC_PARTY_DISMEMBER_OK						0x0D
#define T1_IC_PARTY_CHANGE_FLIGHT_FORMATION				0x0E	// Cm -> I
#define T1_IC_PARTY_CHANGE_FLIGHT_FORMATION_OK			0x0F	// I -> C
#define T1_IC_PARTY_GET_FLIGHT_POSITION					0x10	// C -> I -> Cm
#define T1_IC_PARTY_CHANGE_FLIGHT_POSITION				0x11	// Cm -> I -> C
#define T1_IC_PARTY_CANCEL_FLIGHT_POSITION				0x12	// C -> I -> Cm
#define T1_IC_PARTY_PUT_LAST_PARTY_INFO					0x13	// I -> C
#define T1_IC_PARTY_UPDATE_MEMBER_INFO_MAPNAME			0x14	// I -> C, ������ ���̸� ����
#define T1_IC_PARTY_MEMBER_INVALIDATED					0x15	// I -> C, ��Ƽ���� ������������ ���ӿ��� ƨ���� �� ����
#define T1_IC_PARTY_MEMBER_REJOINED						0x16	// I -> C, ��Ƽ���� �ٽ� ������ �����Ͽ��� �� ����
#define T1_IC_PARTY_UPDATE_ITEM_POS						0x17	// I -> C, ��Ƽ���� ������ ������ �������� �� ����
#define T1_IC_PARTY_ALL_FLIGHT_POSITION					0x18
#define T1_IC_PARTY_REQUEST_PARTYINFO_FROM_A_TO_M		0x19	// 2008-02-28 by dhjin, �Ʒ��� ���� - C->I, �Ʒ��� ���� �� ���� ������ ���� �� ���� ��Ƽ �˻� 
#define T1_IC_PARTY_LEAVE_FROM_M_TO_A					0x1A	// 2008-02-28 by dhjin, �Ʒ��� ���� - C->I, �Ʒ��� ������ ���� ���μ������� ��Ƽ ���� ó��
#define T1_IC_PARTY_LEAVE_FROM_A_TO_M					0x1B	// 2008-02-28 by dhjin, �Ʒ��� ���� - C->I, �Ʒ��� �������� ���μ����� �����Ҷ� �Ʒ��� �������� ��Ƽ Ż�� ó�� Ŭ���̾�Ʈ���� �������� �ʴ´�.
#define T1_IC_PARTY_LIST_INFO							0x1C	// C -> I, 2008-06-02 by dhjin, EP3 ���� ���� - ���� ���� ����Ʈ ��û
#define T1_IC_PARTY_LIST_INFO_OK						0x1D	// I -> C, 2008-06-02 by dhjin, EP3 ���� ���� - ���� ���� ����Ʈ ��û OK
#define T1_IC_PARTY_JOIN_FREE							0x1E	// C -> I, 2008-06-03 by dhjin, EP3 ���� ���� - ���� ���� ����
#define T1_IC_PARTY_JOIN_FREE_OK						0x1F	// I -> C, 2008-06-03 by dhjin, EP3 ���� ���� - ���� ���� ���� OK
#define	T1_IC_PARTY_CHANGE_INFO							0x20	// C -> I, 2008-06-04 by dhjin, EP3 ���� ���� - ���� ���� ����
#define T1_IC_PARTY_CHANGE_INFO_OK						0x21	// I -> C, 2008-06-04 by dhjin, EP3 ���� ���� - ���� ���� ���� OK
#define T1_IC_PARTY_RECOMMENDATION_MEMBER				0x22	// C -> I, 2008-06-04 by dhjin, EP3 ���� ���� - ��õ �ɸ��� ��û
#define T1_IC_PARTY_RECOMMENDATION_MEMBER_OK			0x23	// I -> C, 2008-06-04 by dhjin, EP3 ���� ���� - ��õ �ɸ��� ��û OK
#define T1_IC_PARTY_INFO								0x24	// I -> C, 2008-06-10 by dhjin, EP3 ���� ���� - ���� ���� ����
#define T1_IC_PARTY_GET_AUTO_PARTY_INFO					0x30	// 2009-09-09 ~ 2010-01-26 by dhjin, ���Ǵ�Ƽ - �ڵ� ���� ���� ��û, C -> I
#define T1_IC_PARTY_GET_AUTO_PARTY_INFO_OK				0x31	// 2009-09-09 ~ 2010-01-26 by dhjin, ���Ǵ�Ƽ - �ڵ� ���� ���� ����, I -> C
#define T1_IC_PARTY_UPDATE_ITEM_TRANSFORMER_OK			0x32	// I -> C(n), // 2010-03-18 by cmkwon, ���ͺ��� ���� - 

// FC_MONSTER
#define T1_FC_MONSTER_CREATED							0x01
#define T1_FC_MONSTER_MOVE_OK							0x02
#define T1_FC_MONSTER_HIDE								0x03
#define T1_FC_MONSTER_SHOW								0x04
#define T1_FC_MONSTER_CHANGE_HP							0x05
#define T1_FC_MONSTER_CHANGE_BODYCONDITION				0x06
#define T1_FC_MONSTER_SKILL_USE_SKILL					0x07
#define T1_FC_MONSTER_SKILL_END_SKILL					0x08
#define T1_FC_MONSTER_SUMMON_MONSTER					0x09	// C->F
#define T1_FC_MONSTER_TUTORIAL_MONSTER_DEAD_NOTIFY		0x0A	// F->C
#define T1_FC_MONSTER_TUTORIAL_MONSTER_DELETE			0x0B	// F->C
#define T1_FC_MONSTER_HPTALK							0x0C	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - , F->C(n)
#define T1_FC_MONSTER_SKILL								0x0D	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - , F->C(n)
#define T1_FC_MONSTER_CREATED_ALIVE_FOR_GAMECLEAR		0x0E	// 2010-03-31 by dhjin, ���Ǵ�Ƽ(�������) -
#define T1_FC_MONSTER_SKILL_CANCEL						0x0F	// 2010-03-31 by dhjin, ���Ǵ�Ƽ(�������) - F->C(n)
#define T1_FC_MONSTER_CHANGE_INDEX						0x10	// 2011-05-17 by hskim, ���Ǵ�Ƽ 3�� - �ó׸� ���� ��ü ��� , F->C(n)
#define T1_FC_MONSTER_CINEMA_DELETE_NOTIFY				0x11	// 2011-05-30 by hskim, ���Ǵ�Ƽ 3�� - �ó׸����� ���� ���� Ŭ���̾�Ʈ �ݿ� F->C(n)

// FN_MONSTER
#define T1_FN_MAPPROJECT_START							0x02
#define T1_FN_MAPPROJECT_START_OK						0x03
#define T1_FN_MAPPROJECT_START_OK_ACK					0x04
#define T1_FN_MONSTER_CREATE							0x05
#define T1_FN_MONSTER_CREATE_OK							0x06
#define T1_FN_MONSTER_DELETE							0x07
#define T1_FN_CLIENT_GAMESTART_OK						0x08
#define T1_FN_CLIENT_GAMEEND_OK							0x09
#define T1_FN_GET_CHARACTER_INFO						0x0A
#define T1_FN_GET_CHARACTER_INFO_OK						0x0B
#define T1_FN_ADMIN_SUMMON_MONSTER						0x0C
#define T1_FN_MONSTER_CHANGE_HP							0x0D
#define T1_FN_MONSTER_CHANGE_BODYCONDITION				0x0E
#define T1_FN_MONSTER_SKILL_USE_SKILL					0x0F
#define T1_FN_MONSTER_SKILL_END_SKILL					0x10
#define T1_FN_MONSTER_AUTO_DESTROYED					0x20	// N->F, 2006-04-17 by cmkwon
#define T1_FN_MONSTER_STRATEGYPOINT_INIT				0x30	// 2006-11-20 by cmkwon, F->N
#define T1_FN_MONSTER_STRATEGYPOINT_SUMMON				0x31	// 2007-03-02 by dhjin, F->N
#define T1_FN_MONSTER_OUTPOST_INIT						0x35	// 2007-08-24 by dhjin, F->N
#define T1_FN_MONSTER_OUTPOST_RESET_SUMMON				0x36	// 2007-08-24 by dhjin, F->N
#define T1_FN_MONSTER_CREATE_IN_MAPCHANNEL_BYVALUE		0x37	// 2007-08-29 by dhjin, F->N
#define T1_FN_MONSTER_TELEPORT_SUMMON					0x38	// 2007-09-05 by dhjin, F->N
////////////////////////////////////////////////////////////////////////////////
// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - 
#define T1_FN_MONSTER_HPTALK							0x39	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - , N->F
#define T1_FN_MONSTER_KEYMONSTER_CREATE					0x50	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - Ű ���� ����, F -> N
#define T1_FN_MONSTER_CHANGE_OK							0x51	// 2011-05-11 by hskim, ���Ǵ�Ƽ 3�� - �ó׸� ���� ��� �߰� - �ش� ��ä�� Ư�� ���� ���� ��� �߰� N -> F

// T0_FN_NPCSERVER
#define T1_FN_NPCSERVER_START							0x00	// TCP:
#define T1_FN_NPCSERVER_START_OK						0x01	// TCP:
#define T1_FN_NPCSERVER_SUMMON_JACO_MONSTER				0x02	// TCP:F->N, 
#define T1_FN_NPCSERVER_DELETE_MONSTER_IN_MAPCHANNEL	0x10	// TCP:F->N, // 2007-08-22 by cmkwon, �ش� ��ä�� ���� ��� �����ϱ� ��� �߰�
#define T1_FN_NPCSERVER_CINEMA_MONSTER_CREATE			0x11	// 2010-03-31 by dhjin, ���Ǵ�Ƽ(�������) -	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - Ű ���� ����, F -> N
#define T1_FN_NPCSERVER_NEW_CHANGE_OBJECT				0x12		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ������Ʈ�� ����!!!! 
#define T1_FN_NPCSERVER_RESET_CHANGE_OBJECT				0x13		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ������Ʈ�� ����!!!! 
#define T1_FN_NPCSERVER_CINEMA_MONSTER_DESTROY			0x14	// 2011-04-28 by hskim, ���Ǵ�Ƽ 3�� - �ó׸� ���� ��� �߰� - �ش� ��ä�� Ư�� ���� ���� ��� �߰�
#define T1_FN_NPCSERVER_CINEMA_MONSTER_CHANGE			0x15	// 2011-05-11 by hskim, ���Ǵ�Ƽ 3�� - �ó׸� ���� ��� �߰� - �ش� ��ä�� Ư�� ���� ���� ��� �߰�
#define T1_FN_NPCSERVER_CINEMA_MONSTER_REGEN			0x16	// 2011-06-02 by hskim, ���Ǵ�Ƽ 3�� - ���� 6 - �ֱ��� ��ȯ ��� ����
#define T1_FN_MONITOR_RELOAD_VERSION_INFO_OK			0x17	// 2013-03-14 by jhseol, �������� ���ε� �� ���� ��� IP����Ʈ�� ����

// FC_EVENT
#define T1_FC_EVENT_WARP						0x00
#define T1_FC_EVENT_WARP_SAME_MAP				0x01
#define T1_FC_EVENT_WARP_SAME_MAP_DONE			0x02
#define T1_FC_EVENT_WARP_SAME_FIELD_SERVER		0x03
#define T1_FC_EVENT_WARP_SAME_FIELD_SERVER_DONE	0x04
#define T1_FC_EVENT_OTHER_WARPED				0x05
#define T1_FC_EVENT_WARP_CONNECT				0x06
#define T1_FC_EVENT_WARP_CONNECT_OK				0x07
#define T1_FC_EVENT_ENTER_BUILDING				0x08
#define T1_FC_EVENT_ENTER_BUILDING_OK			0x09
#define T1_FC_EVENT_LEAVE_BUILDING				0x0A
#define T1_FC_EVENT_LEAVE_BUILDING_OK			0x0B
#define T1_FC_EVENT_REQUEST_WARP				0x0C
#define T1_FC_EVENT_REJECT_WARP					0x0D
#define T1_FC_EVENT_REQUEST_OBJECT_EVENT		0x0E
#define T1_FC_EVENT_CHANGE_WEATHER				0x0F
#define T1_FC_EVENT_SUGGEST_CHANNELS			0x10
#define T1_FC_EVENT_SELECT_CHANNEL				0x11
#define T1_FC_EVENT_SELECT_CHANNEL_WITH_PARTY	0x12
#define T1_FC_EVENT_REQUEST_RACING_WARP			0x13
#define T1_FC_EVENT_GET_SHOP_WARP_TARGET_MAP_LIST		0x14
#define T1_FC_EVENT_GET_SHOP_WARP_TARGET_MAP_LIST_OK	0x15
#define T1_FC_EVENT_REQUEST_SHOP_WARP					0x16
#define T1_FC_EVENT_CHARACTERMODE_ENTER_BUILDING		0x17	// 2005-07-28 by cmkwon
#define T1_FC_EVENT_CALL_WARP_EVENT_REQUEST				0x20	// 2006-07-21 by cmkwon
#define T1_FC_EVENT_CALL_WARP_EVENT_REQUEST_ACK			0x21	// 2006-07-21 by cmkwon
#define T1_FC_EVENT_CLICK_TELEPORT						0x22	// 2007-09-06 by dhjin
#define T1_FC_EVENT_CLICK_TELEPORT_OK					0x23	// 2008-04-22 by dhjin, ���� ���� ǥ�� ��ȹ�� - �ڷ���Ʈ ���� �Ϸ� �ð�
#define T1_FC_EVENT_TELEPORT_BUILDCOMPLETE				0x24	// 2007-09-19 by dhjin
#define T1_FC_EVENT_TELEPORT_DESTROY					0x25	// 2007-09-19 by dhjin

#define T1_FC_EVENT_NOTIFY_MSG_GET						0x30	// 2007-11-28 by cmkwon, �����ý��� ���� - C->F
#define T1_FC_EVENT_NOTIFY_MSG_GET_OK					0x31	// 2007-11-28 by cmkwon, �����ý��� ���� - F->C
#define T1_FC_EVENT_NOTIFY_MSG_DELETE					0x32	// 2007-11-28 by cmkwon, �����ý��� ���� - C->F

#define T1_FC_EVENT_COUPON_EVENT_INFO					0x36	// 2008-01-10 by cmkwon, ������ �̺�Ʈ �ý��ۿ� �� ���� �ý��� �߰� - F->C
#define T1_FC_EVENT_COUPON_EVENT_USE_COUPON				0x37	// 2008-01-10 by cmkwon, ������ �̺�Ʈ �ý��ۿ� �� ���� �ý��� �߰� - C->F
#define T1_FC_EVENT_COUPON_EVENT_USE_COUPON_OK			0x38	// 2008-01-10 by cmkwon, ������ �̺�Ʈ �ý��ۿ� �� ���� �ý��� �߰� - F->C

#define T1_FC_EVENT_INFLUENCEMARK					0x3A	// 2008-08-18 by dhjin, ���¸�ũ�̺�Ʈ 
#define T1_FC_EVENT_INFLUENCEMARKEND				0x3B	// 2008-08-18 by dhjin, ���¸�ũ�̺�Ʈ 

// FN_EVENT
#define T1_FN_EVENT_WARP						0x00
#define T1_FN_EVENT_OTHER_WARPED				0x01
#define T1_FN_EVENT_WARP_CONNECT_OK				0x02
////////////////////////////////////////////////////////////////////////////////
// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ������Ʈ�� ����!!!! 
#define T1_FN_EVENT_NEW_CHANGE_OBJECT			0x10
#define T1_FN_EVENT_RESET_CHANGE_OBJECT			0x11

// FP_EVENT	
#define T1_FP_EVENT_NOTIFY_WARP					0x00
#define T1_FP_EVENT_NOTIFY_WARP_OK				0x01
#define T1_FP_EVENT_ENTER_SELECT_SCREEN			0x02	// F->P, Client�� ĳ���� ���� â�� ����
#define T1_FP_EVENT_GAME_STARTED				0x03	// F->P, Client�� ������ ������(������ ����)
#define T1_FP_EVENT_MAP_CHANGED					0x04	// F->P, Client�� ���� �̵���
#define T1_FP_EVENT_RELOAD_HAPPYEV				0x05	// P->F, No body, All ServerGroup reload HappyHourEvent.
#define T1_FP_EVENT_RELOAD_ITEMEV				0x06	// P->F, No body, All ServerGroup reload ItemEvent.	
#define T1_FP_EVENT_UPDATE_PCBANGLIST			0x07	// P->F, No body,
#define T1_FP_EVENT_UPDATE_STRATEGYPOINT_NOTSUMMONTIM			0x08	// P->F, No body,

// T0_FP_MONITOR	
#define T1_FP_MONITOR_SET_MGAME_EVENT_TYPE		0x01
#define T1_FP_MONITOR_RELOAD_VERSION_INFO_OK	0x02	// P->F(n), No body, // 2008-09-08 by cmkwon, SCMonitor���� ReloadVersionInfo�ÿ� �Ϻ� üũ������(.\Res-Tex\*.*)�� ���ε��ϱ� - 

// T0_FP_CASH	
#define T1_FP_CASH_CHANGE_CHARACTERNAME			0x00


// 2015-06-10 by bckim, �������� ������ŷ ��ġ����
//// #define T0_FP_ADMIN					0x73			// 2008-01-31 by cmkwon, ���� ����/���� ���ɾ�� ������ �ý��� ���� - 
//#define T1_FP_ADMIN_BLOCKACCOUNT				0x00	// 2008-01-31 by cmkwon, ���� ����/���� ���ɾ�� ������ �ý��� ���� - 
//#define T1_FP_ADMIN_BLOCKACCOUNT_OK				0x01	// 2008-01-31 by cmkwon, ���� ����/���� ���ɾ�� ������ �ý��� ���� - 
//#define T1_FP_ADMIN_UNBLOCKACCOUNT				0x02	// 2008-01-31 by cmkwon, ���� ����/���� ���ɾ�� ������ �ý��� ���� - 
//#define T1_FP_ADMIN_UNBLOCKACCOUNT_OK			0x03	// 2008-01-31 by cmkwon, ���� ����/���� ���ɾ�� ������ �ý��� ���� - 
//#define T1_FP_ADMIN_STRATRGYPOINT_INFO_CHANGE	0x04	// 2012-11-13 by jhseol, ���� �ý��� ������ - ������, ���ο��� ���������� �����ߴٰ� �˸�

// #define T0_FP_ADMIN					0x73			// 2008-01-31 by cmkwon, ���� ����/���� ���ɾ�� ������ �ý��� ���� - 
#define T1_FP_ADMIN_BLOCKACCOUNT				0x20	// 2008-01-31 by cmkwon, ���� ����/���� ���ɾ�� ������ �ý��� ���� - 
#define T1_FP_ADMIN_BLOCKACCOUNT_OK				0x21	// 2008-01-31 by cmkwon, ���� ����/���� ���ɾ�� ������ �ý��� ���� - 
#define T1_FP_ADMIN_UNBLOCKACCOUNT				0x22	// 2008-01-31 by cmkwon, ���� ����/���� ���ɾ�� ������ �ý��� ���� - 
#define T1_FP_ADMIN_UNBLOCKACCOUNT_OK			0x23	// 2008-01-31 by cmkwon, ���� ����/���� ���ɾ�� ������ �ý��� ���� - 
#define T1_FP_ADMIN_STRATRGYPOINT_INFO_CHANGE	0x24	// 2012-11-13 by jhseol, ���� �ý��� ������ - ������, ���ο��� ���������� �����ߴٰ� �˸�
// End 2015-06-10 by bckim, �������� ������ŷ ��ġ����


// start 2011-12-12 by hskim, GLog 2��
#define T1_FP_GLOG_CONNECT_USER_NEW				0x00	// P->F, GLog ���� ���� �̺�Ʈ
#define T1_FP_GLOG_CONNECT_USER_LOGIN			0x01	// P->F, GLog ���� �α��� �̺�Ʈ
// end 2011-12-12 by hskim, GLog 2��

#define T1_FP_GLOG_NEW_ACCOUNT_INFO				0x02	// P->F, GLog ���� ����			// 2013-03-14 by bckim, Glog ����߰�

// FC_STORE
#define T1_FC_STORE_GET_ITEM					0x00
#define T1_FC_STORE_PUT_ITEM_HEADER				0x01
#define T1_FC_STORE_PUT_ITEM					0x02
#define T1_FC_STORE_PUT_ITEM_DONE				0x03
#define T1_FC_STORE_MOVE_ITEM					0x04
#define T1_FC_STORE_MOVE_ITEM_OK				0x05
#define T1_FC_STORE_INSERT_ITEM					0x06
#define T1_FC_STORE_DELETE_ITEM					0x07
#define T1_FC_STORE_UPDATE_ITEM_COUNT			0x08
#define T1_FC_STORE_UPDATE_ENDURANCE			0x09
#define T1_FC_STORE_UPDATE_POSSESS				0x0A
#define T1_FC_STORE_UPDATE_RARE_FIX				0x0B
#define T1_FC_STORE_INSERT_USINGITEM			0x0C		// F->C
#define T1_FC_STORE_DELETE_USINGITEM			0x0D		// F->C
#define T1_FC_STORE_UPDATE_USINGITEM			0x0E		// F->C, 2006-03-30 by cmkwon
#define T1_FC_STORE_EXPIRE_USINGITEM			0x0F		// C->F, 2006-10-11 by cmkwon, ��� �ð��� �������� ������ �˸�
#define T1_FC_STORE_UPDATE_ITEMSTORAGE			0x10			// 2005-12-07 by cmkwon
#define T1_FC_STORE_UPDATE_ITEMNUM				0x11			// 2006-06-14 by cmkwon
#define T1_FC_STORE_REQUEST_QUICKSLOT			0x12		// 2006-09-04 by dhjin
#define T1_FC_STORE_REQUEST_QUICKSLOT_OK		0x13		// 2006-09-04 by dhjin
#define T1_FC_STORE_SAVE_QUICKSLOT				0x14		// 2006-09-04 by dhjin
#define T1_FC_STORE_LOG_GUILD_ITEM				0x15		// 2006-09-27 by dhjin
#define T1_FC_STORE_LOG_GUILD_ITEM_OK			0x16		// 2006-09-27 by dhjin
#define T1_FC_STORE_LOG_GUILD_ITEM_OK_HEADER	0x17		// 2006-09-27 by dhjin
#define T1_FC_STORE_LOG_GUILD_ITEM_OK_DONE		0x18		// 2006-09-27 by dhjin
#define T1_FC_STORE_UPDATE_ARMOR_ITEM_EVENT_INFO	0x19	// 2013-04-18 by jhseol,bckim �̴��� �Ƹ� - �̴��� �Ƹ� ���� ���� ���� ��Ŷ

// FC_ITEM
#define T1_FC_ITEM_SHOW_ITEM							0x00
#define T1_FC_ITEM_HIDE_ITEM							0x01
#define T1_FC_ITEM_GET_ITEM								0x02
#define T1_FC_ITEM_GET_ITEM_OK							0x03
#define T1_FC_ITEM_GET_ITEM_FAIL						0x04
#define T1_FC_ITEM_PUT_ITEM								0x05
// 2005-11-15 by cmkwon, ������
//#define T1_FC_ITEM_BONUSSKILLPOINT						0x06
//#define T1_FC_ITEM_BONUSSKILLPOINT_OK					0x07
#define T1_FC_ITEM_CHANGE_WINDOW_POSITION				0x08
#define T1_FC_ITEM_CHANGE_WINDOW_POSITION_OK			0x09
#define T1_FC_ITEM_UPDATE_WINDOW_ITEM_LIST				0x0A
#define T1_FC_ITEM_THROW_AWAY_ITEM						0x0B
#define T1_FC_ITEM_THROW_AWAY_ITEM_OK					0x0C
#define T1_FC_ITEM_USE_ENERGY							0x0D
#define T1_FC_ITEM_USE_ENERGY_OK						0x0E	// F->C
#define T1_FC_ITEM_USE_ITEM								0x0F
#define T1_FC_ITEM_USE_ITEM_OK							0x10	// F->C
#define T1_FC_ITEM_DELETE_ITEM_ADMIN					0x11
#define T1_FC_ITEM_RELOAD_ITEM_INFO						0x12	// ������ ������ ������Ʈ�Ǿ���
#define T1_FC_ITEM_USE_ENCHANT							0x13
#define T1_FC_ITEM_USE_ENCHANT_OK						0x14
#define T1_FC_ITEM_PUT_ENCHANT_HEADER					0x15
#define T1_FC_ITEM_PUT_ENCHANT							0x16
#define T1_FC_ITEM_PUT_ENCHANT_DONE						0x17
#define T1_FC_ITEM_DELETE_ALL_ENCHANT					0x18	// F->C, ��� ��æƮ�� �����Ѵ�
#define T1_FC_ITEM_DELETE_DROP_ITEM						0x19	// F->C, �ڽ��� �Ѹ� ������(���ε�)�� ���� �� ����
#define T1_FC_ITEM_UPDATE_ITEM_POS						0x1A	// F->C, ������ ����(��)�� ������, ������ ������ �ٲٸ� ������ ������
#define T1_FC_ITEM_MIX_ITEMS							0x20	// C->F, ������ �������� ����Ʈ�� ����
#define T1_FC_ITEM_MIX_ITEMS_RESULT						0x21	// F->C, ������ ���� ����� ����
#define T1_FC_ITEM_USE_CARDITEM_GUILDSUMMON				0x22	// ��� ��ȯ ī��
#define T1_FC_ITEM_USE_CARDITEM_GUILDSUMMON_NOTIFY		0x23	// ��� ��ȯ ī��� ��ȯ���� �˸�
#define T1_FC_ITEM_USE_CARDITEM_RESTORE					0x24	// ��Ȱ ī��
#define T1_FC_ITEM_USE_CARDITEM_RESTORE_NOTIFY			0x25	// ��Ȱ ī��� ��Ȱ���� �˸�
#define T1_FC_ITEM_USE_CARDITEM_GUILD					0x26	// C->F, �Ϲ�/���� ���� ī��
#define T1_FC_ITEM_USE_CARDITEM_GUILD_NOTIFY			0x27	// F->C, �Ϲ�/���� ���� ī��
#define T1_FC_ITEM_USE_CARDITEM_MONSTERSUMMON			0x28	// C->F, ���� ��ȯ ī��
#define T1_FC_ITEM_USE_CARDITEM_MONSTERSUMMON_NOTIFY	0x29	// F->C, ���� ��ȯ ī��
#define T1_FC_ITEM_USE_CARDITEM_CHANGECHARACTERNAME		0x2A	// C->F, ĳ���� �̸� ���� ī��
#define T1_FC_ITEM_USE_CARDITEM_CHANGECHARACTERNAME_NOTIFY	0x2B	// F->C, ĳ���� �̸� ���� ī��
#define T1_FC_ITEM_USE_CARDITEM_SKILLINITIALIZE			0x2C	// C->F, ��ų �ʱ�ȭ ī��
#define T1_FC_ITEM_USE_CARDITEM_SKILLINITIALIZE_NOTIFY	0x2D	// F->C, ��ų �ʱ�ȭ ī��
#define T1_FC_ITEM_USE_CARDITEM_CHANGEPILOTFACE			0x2E	// C->F, �� ���� ī��
#define T1_FC_ITEM_USE_CARDITEM_CHANGEPILOTFACE_NOTIFY	0x2F	// F->C, �� ���� ī��
#define T1_FC_ITEM_USE_INFLUENCE_BUFF					0x30	// C->F, ���� ����		// 2006-04-21 by cmkwon
#define T1_FC_ITEM_USE_INFLUENCE_BUFF_OK				0x31	// F->C					// 2006-04-21 by cmkwon
#define T1_FC_ITEM_USE_INFLUENCE_GAMEEVENT				0x32	// C->F, ���� �̺�Ʈ	// 2006-04-21 by cmkwon
#define T1_FC_ITEM_USE_INFLUENCE_GAMEEVENT_OK			0x33	// F->C					 // 2006-04-21 by cmkwon
#define T1_FC_ITEM_USE_RANDOMBOX						0x34	// C->F, 2006-08-10 by cmkwon
#define T1_FC_ITEM_USE_RANDOMBOX_OK						0x35	// F->C(n), 2006-08-10 by cmkwon
#define T1_FC_ITEM_USE_SKILL_SUPPORT_ITEM				0x36	// C->F, 2006-09-29 by cmkwon
#define T1_FC_ITEM_USE_SKILL_SUPPORT_ITEM_OK			0x37	// F->C, 2006-09-29 by cmkwon
#define T1_FC_ITEM_USE_RANDOMBOX_OK_DONE				0x38	// F->C, // 2008-08-26 by cmkwon, ItemAttribute �߰� - ��Ű��(Package) ������, (no body) Ŭ���̾�Ʈ�� �� �޽����� �ް� �����¸� ���� �Ѵ�.
#define T1_FC_ITEM_USE_LUCKY_ITEM						0x39	// C->F, 2008-11-04 by dhjin, ��Ű�ӽ�
#define T1_FC_ITEM_USE_LUCKY_ITEM_OK					0x3A	// F->C, 2008-11-04 by dhjin, ��Ű�ӽ�
#define T1_FC_ITEM_USE_LUCKY_ITEM_WIN					0x3B	// C->F, 2008-11-04 by dhjin, ��Ű�ӽ�
#define T1_FC_ITEM_USE_LUCKY_ITEM_WIN_OK				0x3C	// F->C, 2008-11-04 by dhjin, ��Ű�ӽ�
#define T1_FC_ITEM_CHANGED_SHAPEITEMNUM					0x3D	// F->C, // 2009-08-26 by cmkwon, �׷��� ���ҽ� ���� �ý��� ���� - 
#define T1_FC_ITEM_CHANGED_EFFECTITEMNUM				0x3E	// F->C, // 2009-08-26 by cmkwon, �׷��� ���ҽ� ���� �ý��� ���� - 
#define T1_FC_ITEM_USE_INVOKING_WEAR_ITEM				0x40	// C->F, 2009-09-09 ~ 2010-02-10 by dhjin, ���Ǵ�Ƽ - �ߵ������������� ���
#define T1_FC_ITEM_EXPIRE_TIME_INVOKING_WEAR_ITEM		0x41	// C->F, 2009-09-09 ~ 2010-02-10 by dhjin, ���Ǵ�Ƽ - �ߵ������������� ���� �ð� �Ϸ�
#define T1_FC_ITEM_END_COOLINGTIME_ITEM					0x42	// C->F, 2009-09-09 ~ 2010-02-10 by dhjin, ���Ǵ�Ƽ - �ߵ�������������, ��Ÿ�� ����	
#define T1_FC_ITEM_END_COOLINGTIME_ITEM_OK				0x43	// F->C, 2009-09-09 ~ 2010-02-10 by dhjin, ���Ǵ�Ƽ - �ߵ�������������, ��Ÿ�� ����	
#define T1_FC_ITEM_GET_COOLINGTIME_INFO					0x44	// C->F, // 2009-09-09 ~ 2010-02-10 by dhjin, ���Ǵ�Ƽ - �ߵ�������������, ��Ÿ�� ���� ��û
#define T1_FC_ITEM_GET_COOLINGTIME_INFO_OK				0x45	// F->C, // 2009-09-09 ~ 2010-02-10 by dhjin, ���Ǵ�Ƽ - �ߵ�������������, ��Ÿ�� ���� ��û
#define T1_FC_ITEM_USE_INVOKING_WEAR_ITEM_BUFF			0x46	// F->C, // 2009-09-09 ~ 2010-02-10 by dhjin, ���Ǵ�Ƽ - �ߵ�������������, ���� �ø�����
#define T1_FC_ITEM_UPDATE_TRANSFORMER_OK				0x47	// F->C(n), // 2010-03-18 by cmkwon, ���ͺ��� ���� - 
#define T1_FC_ITEM_HOMEPREMIUM_INFO						0x48	// F->C, // 2010-06-01 by shcho, PC�� ���� ȹ��(ĳ��) ������ -

#define T1_FC_ITEM_PET_HEADER							0x49	// 2010-06-15 by shcho&hslee ��ý��� - ���� �� ���� �ε�.
#define T1_FC_ITEM_PET									0x50	// 2010-06-15 by shcho&hslee ��ý��� - ���� �� ���� �ε�.
#define T1_FC_ITEM_PET_BASEDATA_OK						0x51	// 2010-06-15 by shcho&hslee ��ý��� - ���� �� ���� �ε�.
#define T1_FC_ITEM_PET_SKILLDATA_OK						0x52	// 2010-06-15 by shcho&hslee ��ý��� - ���� �� ���� �ε�.
#define T1_FC_ITEM_PET_SOCKETDATA_OK					0x53	// 2010-06-15 by shcho&hslee ��ý��� - ���� �� ���� �ε�.
#define T1_FC_ITEM_PET_DONE								0x54	// 2010-06-15 by shcho&hslee ��ý��� - ���� �� ���� �ε�.
#define T1_FC_ITEM_DISSOLUTIONITEM						0x55	// 2010-08-31 by shcho&jskim �����ۿ��� �ý��� - ���� �ý��� ��Ŷ ó��
#define T1_FC_ITEM_DISSOLUTIONITEM_OK					0x56	// 2010-08-31 by shcho&jskim �����ۿ��� �ý��� - ���� �ý��� ��Ŷ ó��

#define T1_FC_ITEM_PET_SET_NAME							0x57	// C->F, 2011-08-22 by hskim, ��Ʈ�� �ý��� 2�� - �� �̸� ���� ��û
#define T1_FC_ITEM_PET_SET_NAME_OK						0x58	// F->C, 2011-08-22 by hskim, ��Ʈ�� �ý��� 2�� - �� �̸� ���� ��û ���
#define T1_FC_ITEM_PET_SET_EXP_RATIO					0x59	// C->F, 2011-08-22 by hskim, ��Ʈ�� �ý��� 2�� - �� ����ġ ȹ�� ���� ���� ��û
#define T1_FC_ITEM_PET_SET_EXP_RATIO_OK					0x60	// F->C, 2011-08-22 by hskim, ��Ʈ�� �ý��� 2�� - �� ����ġ ȹ�� ���� ���� ���
#define T1_FC_ITEM_PET_CHANGE_LEVEL						0x61	// C->F, 2011-08-22 by hskim, ��Ʈ�� �ý��� 2�� - ��� ����
#define T1_FC_ITEM_PET_CHANGE_EXP						0x62	// C->F, 2011-08-22 by hskim, ��Ʈ�� �ý��� 2�� - ��� ����

#define T1_FC_ITEM_PET_SET_SOCKET						0x63	// C->F, 2011-08-22 by hskim, ��Ʈ�� �ý��� 2�� - ���� ������ ����
#define T1_FC_ITEM_PET_SET_SOCKET_OK					0x64	// F->C, 2011-08-22 by hskim, ��Ʈ�� �ý��� 2�� - ���� ������ ���� ���
#define T1_FC_ITEM_PET_SET_KIT_SLOT						0x65	// C->F, 2011-08-22 by hskim, ��Ʈ�� �ý��� 2�� - ŰƮ ���� ����
#define T1_FC_ITEM_PET_SET_KIT_SLOT_OK					0x66	// F->C, 2011-08-22 by hskim, ��Ʈ�� �ý��� 2�� - ŰƮ ���� ���� ���
#define T1_FC_ITEM_PET_SET_KIT_AUTOSKILL_SLOT			0x67	// C->F, 2011-08-22 by hskim, ��Ʈ�� �ý��� 2�� - ���� ��ų ���� ����
#define T1_FC_ITEM_PET_SET_KIT_AUTOSKILL_SLOT_OK		0x68	// F->C, 2011-08-22 by hskim, ��Ʈ�� �ý��� 2�� - ���� ��ų ���� ����

#define T1_FC_ITEM_USE_PET_SOCKET_ITEM					0x69	// C->F, // 2011-09-20 by hskim, ��Ʈ�� �ý��� 2�� - ���� ������ ��� (���)
#define T1_FC_ITEM_USE_PET_SOCKET_ITEM_OK				0x6a	// F->C, // 2011-09-20 by hskim, ��Ʈ�� �ý��� 2�� - ���� ������ ��� ��� (���)
#define T1_FC_ITEM_CANCEL_PET_SOCKET_ITEM				0x6b	// C->F, // 2011-09-20 by hskim, ��Ʈ�� �ý��� 2�� - ���� ������ ��� ���� (���)
#define T1_FC_ITEM_CANCEL_PET_SOCKET_ITEM_OK			0x6c	// F->C, // 2011-09-20 by hskim, ��Ʈ�� �ý��� 2�� - ���� ������ ��� ���� ��� (���)
#define T1_FC_ITEM_NOTIFY_WINDOW_POSITION				0x6d	// F->C, // 2011-09-20 by hskim, ��Ʈ�� �ý��� 2�� - ItemWindowIndex ���� �˸� (F->C) , ������ ���� ó��

// 2014-06-10 by bckim, ���º��� ������
#define T1_FC_ITEM_USE_CARDITEM_CHANGE_INFLUENCE		0x6e	// C->F, ���º��� ī��
#define T1_FC_ITEM_USE_CARDITEM_CHANGE_INFLUENCE_NOTIFY	0x70	// F->C, ���º��� ī��
// End. 2014-06-10 by bckim, ���º��� ������

// FC_SHOP	
#define T1_FC_SHOP_PUT_ITEM_HEADER			0x00
#define T1_FC_SHOP_PUT_ITEM					0x01
#define T1_FC_SHOP_PUT_ITEM_DONE			0x02
#define T1_FC_SHOP_GET_ITEMINFO				0x03
#define T1_FC_SHOP_GET_ITEMINFO_OK			0x04
#define T1_FC_SHOP_BUY_ITEM					0x05
#define T1_FC_SHOP_BUY_ITEM_OK				0x06
#define T1_FC_SHOP_SELL_ITEM				0x07
#define T1_FC_SHOP_SELL_ITEM_OK				0x08
#define T1_FC_SHOP_GET_USED_ITEM_PRICE		0x09
#define T1_FC_SHOP_GET_USED_ITEM_PRICE_OK	0x0A
#define T1_FC_SHOP_GET_SHOP_ITEM_LIST		0x0B
#define T1_FC_SHOP_REQUEST_REPAIR			0x0C	// C->F, ��ü ���� ��û
#define T1_FC_SHOP_REQUEST_REPAIR_OK		0x0D	// F->C, ��ü ���� ��û ����
#define T1_FC_SHOP_BUY_CASH_ITEM			0x0E	// C->F, ���� ������ ����
#define T1_FC_SHOP_BUY_CASH_ITEM_OK			0x0F	// F->C, // 2007-11-13 by cmkwon, �����ϱ� ��� �߰� -���� ������ ���� ����
#define T1_FC_SHOP_BUY_COLOR_ITEM			0x10	// C->F, ���� ������ ����// 2005-12-06 by cmkwon
#define T1_FC_SHOP_BUY_COLOR_ITEM_OK		0x11	// F->C, ���� ������ ���� ����// 2005-12-06 by cmkwon
#define T1_FC_SHOP_BUY_WARPOINT_ITEM		0x12	// C->F, WarPoint ������ ���� // 2007-06-13 by dhjin
#define T1_FC_SHOP_BUY_WARPOINT_ITEM_OK		0x13	// F->C, // 2007-06-13 by dhjin
#define T1_FC_SHOP_CHECK_GIVE_TARGET		0x14	// C->F, // 2007-11-13 by cmkwon, �����ϱ� ��� �߰� - �����޴� ĳ���� üũ ��û ��������
#define T1_FC_SHOP_CHECK_GIVE_TARGET_OK		0x15	// F->C, // 2007-11-13 by cmkwon, �����ϱ� ��� �߰� -
#define T1_FC_SHOP_INFINITY_ITEM_HEADER		0x16	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ����
#define T1_FC_SHOP_INFINITY_ITEM			0x17	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ����
#define T1_FC_SHOP_INFINITY_ITEM_DONE		0x18	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ����
#define T1_FC_SHOP_INFINITY_BUY_ITEM		0x19	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ����, ����
#define T1_FC_SHOP_CLOSE					0x1A	// 2011-10-28 by hskim, EP4 [Ʈ���� �ý���] - ũ����Ż �ý���
#define T1_FC_SHOP_BUY_ITEM_UPDATE			0x1B	// F->C, // 2011-12-26 by hskim, EP4 [Ʈ���� �ý���] - ũ����Ż �ý���
#define T1_FC_SHOP_AUTH_KEY					0x1C	// C->F, �� ĳ�� ������ ����Ű ���� - // 2013-03-13 by hskim, �� ĳ�� ����
#define T1_FC_SHOP_INFLUENCE_BUFF			0x1D	// C->F, // 2013-05-09 by hskim, ���� ����Ʈ ����
#define T1_FC_SHOP_INFLUENCE_BUFF_OK		0x1E	// F->C, // 2013-05-09 by hskim, ���� ����Ʈ ����

// FC_TRADE
#define T1_FC_TRADE_REQUEST_TRADE			0x00
#define T1_FC_TRADE_REQUEST_TRADE_OK		0x01
#define T1_FC_TRADE_CANCEL_REQUEST			0x02
#define T1_FC_TRADE_CANCEL_REQUEST_OK		0x03
#define T1_FC_TRADE_ACCEPT_TRADE			0x04
#define T1_FC_TRADE_ACCEPT_TRADE_OK			0x05
#define T1_FC_TRADE_REJECT_TRADE			0x06
#define T1_FC_TRADE_REJECT_TRADE_OK			0x07
#define T1_FC_TRADE_REJECT_TRADING			0x08
#define T1_FC_TRADE_SHOW_TRADE_WINDOW		0x09
#define T1_FC_TRADE_TRANS_ITEM				0x0A
#define T1_FC_TRADE_TRANS_ITEM_OK			0x0B
#define T1_FC_TRADE_SEE_ITEM				0x0C
#define T1_FC_TRADE_SEE_ITEM_OK				0x0D
#define T1_FC_TRADE_OK_TRADE				0x0E
#define T1_FC_TRADE_OK_TRADE_OK				0x0F
#define T1_FC_TRADE_CANCEL_TRADE			0x10
#define T1_FC_TRADE_CANCEL_TRADE_OK			0x11
#define T1_FC_TRADE_INSERT_ITEM				0x12
#define T1_FC_TRADE_DELETE_ITEM				0x13
#define T1_FC_TRADE_UPDATE_ITEM_COUNT		0x14
#define T1_FC_TRADE_OK_TRADE_NOTIFY			0x15	// 2008-11-21 by cmkwon, �ŷ� ���� Ȯ�� �ý��� ���� - F->C(2)
// 2010-06-15 by shcho&hslee ��ý��� - �ŷ� �� �� ���� ����
#define T1_FC_TRADE_SEE_PET_DATA			0x16	
#define T1_FC_TRADE_DELETE_CURRENT_PET_DATA	0x17 // F->C Ʈ���̵� ������ ������ ���� �˸� ��Ŷ
#define T1_FC_TRADE_INSERT_CURRENT_PET_DATA	0x18 // F->C Ʈ���̵� ������ ������ �߰� �˸� ��Ŷ
// END 2010-06-15 by shcho&hslee ��ý��� - �ŷ� �� �� ���� ����

// T0_FC_COUNTDOWN
#define T1_FC_COUNTDOWN_START					0x00	// F -> C
#define T1_FC_COUNTDOWN_DONE					0x01	// C -> F

// T0_FC_OBJECT
#define T1_FC_OBJECT_CHANGE_BODYCONDITION		0x00
#define T1_FC_OBJECT_CHANGE_BODYCONDITION_OK	0x01
#define T1_FC_OBJECT_CHANGE						0x02	// C -> F(n), 2011-11-07 by hskim, EP4 [Ʈ���� �ý���] - ũ����Ż �ý���

// T0_FC_AUCTION
#define T1_FC_AUCTION_REGISTER_ITEM			0x00	// C->F, ��� ������ ���
#define T1_FC_AUCTION_REGISTER_ITEM_OK		0x01	// F->C, ��� ������ ��� ���
#define T1_FC_AUCTION_CANCEL_REGISTER		0x02	// C->F, ��� ������ ��� ���
#define T1_FC_AUCTION_CANCEL_REGISTER_OK	0x03	// F->C, ��� ������ ��� ��� ���
#define T1_FC_AUCTION_BUY_ITEM				0x04	// C->F, ��� ������ ����
#define T1_FC_AUCTION_BUY_ITEM_OK			0x05	// F->C, ��� ������ ���� ���
#define T1_FC_AUCTION_GET_ITEM_LIST			0x06	// C->F, ��� ������ ��� ��û
#define T1_FC_AUCTION_INSERT_ITEM			0x07	// F->C, ��� ������ ���ۿ�
#define T1_FC_AUCTION_PUT_ENCHANT			0x08	// F->C, ��� �������� ��æƮ ���� ���ۿ�

// FC_GUILD
#define T1_FC_GUILD_GET_MAP_OWNER_INFO			0x00
#define T1_FC_GUILD_GET_MAP_OWNER_INFO_OK		0x01
#define T1_FC_GUILD_REQUEST_GUILD_WAR			0x02
#define T1_FC_GUILD_REQUEST_GUILD_WAR_RESULT	0x03
#define T1_FC_GUILD_GET_CHALLENGER_GUILD		0x04
#define T1_FC_GUILD_GET_CHALLENGER_GUILD_OK		0x05
#define T1_FC_GUILD_GET_WAR_INFO				0x06	// C->F
#define T1_FC_GUILD_GET_WAR_INFO_OK				0x07	// F->C
#define T1_FC_GUILD_SURRENDER_GUILD_WAR			0x08	// C->F
#define T1_FC_GUILD_SUMMON_MEMBER				0x09	// F->C(n)
#define T1_FC_GUILD_SUMMON_MEMBER_OK			0x0A	// C(n)->F
#define T1_FC_GUILD_DISMEMBER					0x0B	// C->F

// T0_FI_GUILD
#define T1_FI_GUILD_NOTIFY_START_WAR			0x00	// F->I
#define T1_FI_GUILD_NOTIFY_END_WAR				0x01	// I->F
#define T1_FI_GUILD_DELETE_GUILD				0x02	// F->I
#define T1_FI_GUILD_ADD_GUILD_FAME				0x10	// F->I
#define T1_FI_GUILD_REG_DELETE_GUILD			0x11	// I->F
#define T1_FI_GUILD_DISMEMBER					0x12	// F->I
#define T1_FI_GUILD_OUTPOST						0x13	// F->I, // 2008-05-20 by dhjin, EP3 - ���� ���� ���� - �������� ����
// 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������
#define T1_FI_GUILD_BONUS_EXP_RATE				0x14	// 2012-10-12 by jhjang ���� ����ġ ���ʽ� ���� ����
// 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������
// IC_GUILD
#define T1_IC_GUILD_CREATE					0x00	// C->I, ��� ���� ��û
#define T1_IC_GUILD_CREATE_OK				0x01	// I->C, ��� ���� ���
#define T1_IC_GUILD_GET_GUILD_INFO			0x02	// C->I, ��� ���� ��û
#define T1_IC_GUILD_GET_GUILD_INFO_OK		0x03	// I->C, ��� ���� ���
#define T1_IC_GUILD_GET_OTHER_GUILD_INFO	0x04	// C->I, �ٸ� ��� ���� ��û
#define T1_IC_GUILD_GET_OTHER_GUILD_INFO_OK	0x05	// I->C, �ٸ� ��� ���� ���
#define T1_IC_GUILD_REQUEST_INVITE			0x06	// C->I, ���� ����, ������ ��û
#define T1_IC_GUILD_REQUEST_INVITE_QUESTION	0x07	// I->C, ���� ����, ����ڿ��� ����
#define T1_IC_GUILD_ACCEPT_INVITE			0x08	// C->I, ���� �³�, ������ ��û
#define T1_IC_GUILD_ACCEPT_INVITE_OK		0x09	// I->C, ���� �³�, �������� ����
#define T1_IC_GUILD_REJECT_INVITE			0x0A	// C->I, ���� �ź�, ������ ��û
#define T1_IC_GUILD_REJECT_INVITE_OK		0x0B	// I->C, ���� �ź�, ����ڿ��� ����
#define T1_IC_GUILD_BAN_MEMBER				0x0C	// C->I, ���� �߹�
#define T1_IC_GUILD_BAN_MEMBER_OK			0x0D	// I->C, ���� �߹� ���
#define T1_IC_GUILD_LEAVE					0x0E	// C->I, ���� Ż��
#define T1_IC_GUILD_LEAVE_OK				0x0F	// I->C, ���� Ż�� ���
// #define T1_IC_GUILD_DISMEMBER				0x10	// C->I, ���� ��ü
#define T1_IC_GUILD_DISMEMBER_OK			0x11	// I->C, ���� ��ü ���
#define T1_IC_GUILD_SET_MEMBER_STATE		0x12	// I->C, ������ ���� ��ȭ(ONLINE, OFFLINE ��)
#define T1_IC_GUILD_CANCEL_DISMEMBER		0x13	// C->I, ���� ��ü ��� ��û
#define T1_IC_GUILD_CANCEL_DISMEMBER_OK		0x14	// I->C, ���� ��ü ��� ���
#define T1_IC_GUILD_GET_DISMEMBER_DATE		0x15	// C->I, ��� �ػ� �ð� ��û
#define T1_IC_GUILD_GET_DISMEMBER_DATE_OK	0x16	// I->C, ��� �ػ� �ð� ���
#define T1_IC_GUILD_CHANGE_GUILD_NAME		0x17	// C->I, ���� �̸� ���� ��û
#define T1_IC_GUILD_CHANGE_GUILD_NAME_OK	0x18	// I->C, ���� �̸� ���� ���
#define T1_IC_GUILD_GET_GUILD_MARK			0x19	// C->I, ���� ���� ��û
#define T1_IC_GUILD_GET_GUILD_MARK_OK		0x1A	// I->C, ���� ���� ���
#define T1_IC_GUILD_SET_GUILD_MARK			0x1B	// C->I, ���� ���� ���� ��û
#define T1_IC_GUILD_SET_GUILD_MARK_OK		0x1C	// I->C, ���� ���� ���� ���
#define T1_IC_GUILD_SET_RANK				0x1D	// C->I, ��� ����
#define T1_IC_GUILD_SET_RANK_OK				0x1E	// I->C, ��� ���� ���
#define T1_IC_GUILD_CHANGE_GUILD_STATE		0x1F	// I->C, ���� ���� ����
#define T1_IC_GUILD_LOADING_GUILD_DONE		0x20	// I->C, ���������� ��� ���� �ε� �Ϸ� �˸�
#define T1_IC_GUILD_WAR_READY				0x21	// I->C
#define T1_IC_GUILD_START_WAR				0x22	// I->C
#define T1_IC_GUILD_END_WAR					0x23	// I->C
#define T1_IC_GUILD_UPDATE_WAR_POINT		0x24	// I->C
#define T1_IC_GUILD_SURRENDER_GUILD_WAR		0x25	// C->I, ����� �׺�
#define T1_IC_GUILD_CHANGE_MEMBER_CAPACITY	0x26	// I->C, ���� ���� �ο� ����
#define T1_IC_GUILD_GET_GUILD_MEMBER_LIST_OK	0x27	// I->C, ���ܿ� ����Ʈ
#define T1_IC_GUILD_END_WAR_ADMIN_NOTIFY		0x28	// I->C(n), 2006-08-09 by cmkwon
#define T1_IC_GUILD_MEMBER_LEVEL_UP			0x29	// I->C(n), // 2008-05-20 by dhjin, EP3 - ���� ���� ���� - ���ܿ� ������ ����
#define T1_IC_GUILD_NEW_COMMANDER			0x2A	// C->I, // 2008-05-20 by dhjin, EP3 - ���� ���� ���� - ������ ����
#define T1_IC_GUILD_NOTICE_WRITE			0x2B	// C->I, // 2008-05-20 by dhjin, EP3 - ���� ���� ���� - ���� ���� �ۼ�
#define T1_IC_GUILD_NOTICE_WRITE_OK			0x2C	// I->C, // 2008-05-20 by dhjin, EP3 - ���� ���� ���� - ���� ���� �ۼ� OK
#define T1_IC_GUILD_GET_APPLICANT			0x2D	// C->I, // 2008-05-27 by dhjin, EP3 - ���� ���� ���� - ���� ������ ����
#define T1_IC_GUILD_GET_APPLICANT_OK_HEADER	0x2E	// I->C, // 2008-05-27 by dhjin, EP3 - ���� ���� ���� - ���� ������ ���� OK
#define T1_IC_GUILD_GET_APPLICANT_OK		0x2F	// I->C, // 2008-05-27 by dhjin, EP3 - ���� ���� ���� - ���� ������ ���� OK
#define T1_IC_GUILD_GET_APPLICANT_OK_DONE	0x30	// I->C, // 2008-05-27 by dhjin, EP3 - ���� ���� ���� - ���� ������ ���� OK
#define T1_IC_GUILD_GET_INTRODUCTION		0x31	// C->I, // 2008-05-27 by dhjin, EP3 - ���� ���� ���� - ���� �Ұ�
#define T1_IC_GUILD_GET_INTRODUCTION_OK		0x32	// I->C, // 2008-05-27 by dhjin, EP3 - ���� ���� ���� - ���� �Ұ� ok
#define T1_IC_GUILD_GET_SELF_INTRODUCTION		0x33	// C->I, // 2008-05-27 by dhjin, EP3 - ���� ���� ���� - ���� ������ �Ұ��� 
#define T1_IC_GUILD_GET_SELF_INTRODUCTION_OK	0x34	// I->C, // 2008-05-27 by dhjin, EP3 - ���� ���� ���� - ���� ������ �Ұ��� OK
#define T1_IC_GUILD_SEARCH_INTRODUCTION			0x35		// C->I, // 2008-05-27 by dhjin, EP3 - ���� ���� ���� - ���� �Ұ� �˻�  
#define T1_IC_GUILD_SEARCH_INTRODUCTION_OK_HEADER	0x36	// I->C, // 2008-05-27 by dhjin, EP3 - ���� ���� ���� - ���� �Ұ� �˻� OK 
#define T1_IC_GUILD_SEARCH_INTRODUCTION_OK			0x37	// I->C, // 2008-05-27 by dhjin, EP3 - ���� ���� ���� - ���� �Ұ� �˻� OK 
#define T1_IC_GUILD_SEARCH_INTRODUCTION_OK_DONE		0x38	// I->C, // 2008-05-27 by dhjin, EP3 - ���� ���� ���� - ���� �Ұ� �˻� OK 
#define T1_IC_GUILD_UPDATE_INTRODUCTION				0x39	// C->I, // 2008-05-27 by dhjin, EP3 - ���� ���� ���� - ���� �Ұ� �ۼ� 
#define T1_IC_GUILD_UPDATE_INTRODUCTION_OK			0x3A	// I->C, // 2008-05-27 by dhjin, EP3 - ���� ���� ���� - ���� �Ұ� �ۼ� OK
#define T1_IC_GUILD_DELETE_INTRODUCTION				0x3B	// C->I, // 2008-05-27 by dhjin, EP3 - ���� ���� ���� - ���� �Ұ� �����  
#define T1_IC_GUILD_DELETE_INTRODUCTION_OK			0x3C	// I->C, // 2008-05-27 by dhjin, EP3 - ���� ���� ���� - ���� �Ұ� ����� OK
#define T1_IC_GUILD_UPDATE_SELFINTRODUCTION			0x3D	// C->I, // 2008-05-27 by dhjin, EP3 - ���� ���� ���� - �ڱ� �Ұ� �ۼ� 
#define T1_IC_GUILD_UPDATE_SELFINTRODUCTION_OK		0x3E	// I->C, // 2008-05-27 by dhjin, EP3 - ���� ���� ���� - �ڱ� �Ұ� �ۼ� OK
#define T1_IC_GUILD_DELETE_SELFINTRODUCTION			0x3F	// C->I, // 2008-05-27 by dhjin, EP3 - ���� ���� ���� - �ڱ� �Ұ� �����  
#define T1_IC_GUILD_DELETE_SELFINTRODUCTION_OK		0x40	// I->C, // 2008-05-27 by dhjin, EP3 - ���� ���� ���� - �ڱ� �Ұ� ����� OK
#define T1_IC_GUILD_CHANGE_FAME_RANK				0x41	// I->C, // 2008-06-10 by dhjin, EP3 - ���� ���� ���� - ���� ���� ����
#define T1_IC_GUILD_APPLICANT_INVITE				0x42	// C->I, // 2008-06-12 by dhjin, EP3 - ���� ���� ���� - ������ �������� ���ܿ� �ʴ�
#define T1_IC_GUILD_APPLICANT_INVITE_OK				0x43	// I->C, // 2008-06-12 by dhjin, EP3 - ���� ���� ���� - ������ �������� ���ܿ� �ʴ� OK
#define T1_IC_GUILD_APPLICANT_REJECT_INVITE			0x44	// C->I, // 2008-06-12 by dhjin, EP3 - ���� ���� ���� - ������ �������� ���ܿ� �ʴ� �ź� 
#define T1_IC_GUILD_APPLICANT_REJECT_INVITE_OK		0x45	// I->C, // 2008-06-12 by dhjin, EP3 - ���� ���� ���� - ������ �������� ���ܿ� �ʴ� �ź� OK
#define T1_IC_GUILD_CHANGE_MEMBERSHIP				0x46	// I->C, // 2008-06-20 by dhjin, EP3 - ���� ���� ���� - ������ �ɹ��� ���� ����

// FC_SKILL
#define T1_FC_SKILL_USE_SKILLPOINT			0x00
#define T1_FC_SKILL_USE_SKILLPOINT_OK		0x01
#define T1_FC_SKILL_SETUP_SKILL				0x02
#define T1_FC_SKILL_SETUP_SKILL_OK_HEADER	0x03
#define T1_FC_SKILL_SETUP_SKILL_OK			0x04
#define T1_FC_SKILL_SETUP_SKILL_OK_DONE		0x05
#define T1_FC_SKILL_USE_SKILL				0x06
#define T1_FC_SKILL_USE_SKILL_OK			0x07
#define T1_FC_SKILL_CANCEL_SKILL			0x08
#define T1_FC_SKILL_INVALIDATE_SKILL		0x09
#define T1_FC_SKILL_PREPARE_USE				0x0A
#define T1_FC_SKILL_PREPARE_USE_OK			0x0B
#define T1_FC_SKILL_CANCEL_PREPARE			0x0C
#define T1_FC_SKILL_CANCEL_PREPARE_OK		0x0D
#define T1_FC_SKILL_CONFIRM_USE				0x0F		// 2005-12-02 by cmkwon, C->F, F->C
#define T1_FC_SKILL_CONFIRM_USE_ACK			0x10		// 2005-12-02 by cmkwon, C->F, F->C
#define T1_FC_SKILL_CANCEL_SKILL_OK			0x11		// 2006-11-28 by dhjin, F->C

// FN_SKILL
#define T1_FN_SKILL_USE_SKILL				0x00
#define T1_FN_SKILL_USE_SKILL_OK			0x01

// FC_QUEST
#define T1_FC_QUEST_REQUEST_START					0x00
#define T1_FC_QUEST_REQUEST_START_RESULT			0x01
#define T1_FC_QUEST_ACCEPT_QUEST					0x02
#define T1_FC_QUEST_CANCEL_QUEST					0x03
#define T1_FC_QUEST_REQUEST_SUCCESS					0x04
#define T1_FC_QUEST_REQUEST_SUCCESS_RESULT			0x05
#define T1_FC_QUEST_PUT_ALL_QUEST_HEADER			0x06
#define T1_FC_QUEST_PUT_ALL_QUEST					0x07
#define T1_FC_QUEST_PUT_ALL_QUEST_DONE				0x08
#define T1_FC_QUEST_DISCARD_QUEST					0x09
#define T1_FC_QUEST_DISCARD_QUEST_OK				0x0A
#define T1_FC_QUEST_MOVE_QUEST_MAP					0x0B	// C->F
#define T1_FC_QUEST_PUT_ALL_QUEST_MONSTER_COUNT_HEADER		0x0C	// F->C, // 2005-10-25 by cmkwon
#define T1_FC_QUEST_PUT_ALL_QUEST_MONSTER_COUNT		0x0D	// F->C, // 2005-10-25 by cmkwon
#define T1_FC_QUEST_PUT_ALL_QUEST_MONSTER_COUNT_DONE		0x0E	// F->C, // 2005-10-25 by cmkwon
#define T1_FC_QUEST_UPDATE_MONSTER_COUNT			0x0F	// F->C, // 2005-10-25 by cmkwon
#define T1_FC_QUEST_REQUEST_SUCCESS_CHECK			0x10	// C->F, // 2006-03-24 by cmkwon
#define T1_FC_QUEST_REQUEST_SUCCESS_CHECK_RESULT	0x11	// F->C(n), // 2006-03-24 by cmkwon
#define T1_FC_QUEST_REQUEST_PARTY_WARP				0x12	// F->C(n), // 2006-10-16 by cmkwon
#define T1_FC_QUEST_REQUEST_PARTY_WARP_ACK			0x13	// C(n)->F, // 2006-10-16 by cmkwon
#define T1_FC_QUEST_REQUEST_MISSIONMASTER_HELP		0x14	// 2008-12-02 by dhjin, C -> F, �̼Ǹ����� ��û
#define T1_FC_QUEST_REQUEST_MISSIONMASTER_HELP_INVITE 0x15	// 2008-12-02 by dhjin, F -> C(n), �������� ���� �̼Ǹ����Ϳ��� ��û
#define T1_FC_QUEST_MISSIONMASTER_HELP_INVITE		0x16	// 2008-12-02 by dhjin, C -> F, �̼Ǹ����� ��û �¶� 
#define T1_FC_QUEST_MISSIONMASTER_HELP_INVITE_OK	0x17	// 2008-12-02 by dhjin, F -> C, �̼Ǹ����� ��û �¶�
#define T1_FC_QUEST_MISSIONMASTER_HELP_REJECT		0x18	// 2008-12-02 by dhjin, C -> F, �̼Ǹ����� ��û ���� 
#define T1_FC_QUEST_MISSIONMASTER_HELP_REJECT_OK	0x19	// 2008-12-02 by dhjin, F -> C, �̼Ǹ����� ��û ����
#define T1_FC_QUEST_INSERT_QUEST					0x20	// 2009-03-31 by cmkwon, �����ʱ�ȭ �ý��� ���� - F->C
#define T1_FC_QUEST_DELETE_QUEST					0x21	// 2009-03-31 by cmkwon, �����ʱ�ȭ �ý��� ���� - F->C


// FC_SYNC
//#define T1_FC_SYNC_PRIMARY_REATTACK_OK		0x00
//#define T1_FC_SYNC_SECONDARY_REATTACK_OK	0x01
//#define T1_FC_SYNC_SKILL_REUSE_OK			0x02

// FC_INFO
#define T1_FC_INFO_GET_MONSTER_INFO					0x00
#define T1_FC_INFO_GET_MONSTER_INFO_OK				0x01
#define T1_FC_INFO_GET_MAPOBJECT_INFO				0x02
#define T1_FC_INFO_GET_MAPOBJECT_INFO_OK			0x03
#define T1_FC_INFO_GET_ITEM_INFO					0x04
#define T1_FC_INFO_GET_ITEM_INFO_OK					0x05
#define T1_FC_INFO_GET_RARE_ITEM_INFO				0x06
#define T1_FC_INFO_GET_RARE_ITEM_INFO_OK			0x07
#define T1_FC_INFO_GET_BUILDINGNPC_INFO				0x08
#define T1_FC_INFO_GET_BUILDINGNPC_INFO_OK			0x09
#define T1_FC_INFO_GET_SIMPLE_ITEM_INFO				0x0A
#define T1_FC_INFO_GET_SIMPLE_ITEM_INFO_OK			0x0B
#define T1_FC_INFO_GET_ENCHANT_COST					0x0C
#define T1_FC_INFO_GET_ENCHANT_COST_OK				0x0D
#define T1_FC_INFO_GET_CURRENT_MAP_INFO				0x10
#define T1_FC_INFO_GET_CURRENT_MAP_INFO_OK			0x11
#define T1_FC_INFO_GET_HAPPY_HOUR_EVENT_INFO_OK		0x12
#define T1_FC_INFO_GET_GAME_EVENT_INFO_OK			0x13
#define T1_FC_INFO_GET_SERVER_DATE_TIME				0x14		// 2006-10-11 by cmkwon, C->F
#define T1_FC_INFO_GET_SERVER_DATE_TIME_OK			0x15		// 2006-10-11 by cmkwon, F->C
#define T1_FC_INFO_GET_HAPPY_HOUR_EVENT_INFO		0x16		// 2007-10-30 by cmkwon, ���º� ���Ǿƿ� �̺�Ʈ ���� - C->F
#define T1_FC_INFO_GET_HAPPY_HOUR_EVENT_INFO_BY_LEVEL	0x17		// 2008-03-14 by dhjin, Level�� ���Ǿƿ� �̺�Ʈ ���� - F->C

#define T1_FC_INFO_CHECK_RESOBJ_CHECKSUM			0x20		// 2007-05-28 by cmkwon, C->F
#define T1_FC_INFO_NOTICE_REQUEST					0x30		// C->F
#define T1_FC_INFO_NOTICE_REQUEST_OK				0x31		// F->C
#define T1_FC_INFO_NOTICE_REG						0x32		// C->F
#define T1_FC_INFO_NOTICE_REG_OK					0x33		// F->C
#define T1_FC_INFO_NOTICE_MODIFY					0x34		// C->F
#define T1_FC_INFO_NOTICE_MODIFY_OK					0x35		// F->C
#define T1_FC_INFO_EXPEDIENCYFUND_REQUEST			0x36		// C->F
#define T1_FC_INFO_EXPEDIENCYFUND_REQUEST_OK		0x37		// F->C
#define T1_FC_INFO_EXPEDIENCYFUND_PAYBACK			0x38		// C->F
#define T1_FC_INFO_EXPEDIENCYFUND_PAYBACK_OK		0x39		// F->C
#define T1_FC_INFO_SECONDARYPASSWORD_UPDATE_PASSWORD	0x40	// 2007-09-12 by cmkwon, ��Ʈ�� 2���н����� ���� - �������� �߰�, C->F
#define T1_FC_INFO_SECONDARYPASSWORD_UPDATE_PASSWORD_OK	0x41	// 2007-09-12 by cmkwon, ��Ʈ�� 2���н����� ���� - �������� �߰�, F->C
#define T1_FC_INFO_SECONDARYPASSWORD_CHECK_PASSWORD		0x42	// 2007-09-12 by cmkwon, ��Ʈ�� 2���н����� ���� - �������� �߰�, C->F
#define T1_FC_INFO_SECONDARYPASSWORD_CHECK_PASSWORD_OK	0x43	// 2007-09-12 by cmkwon, ��Ʈ�� 2���н����� ���� - �������� �߰�, F->C
#define T1_FC_INFO_SECONDARYPASSWORD_LOCK				0x44	// 2007-09-12 by cmkwon, ��Ʈ�� 2���н����� ���� - �������� �߰�, C->F
#define T1_FC_INFO_SECONDARYPASSWORD_LOCK_OK			0x45	// 2007-09-12 by cmkwon, ��Ʈ�� 2���н����� ���� - �������� �߰�, F->C
#define T1_FC_INFO_GET_GUILDMARK						0x46	// 2007-12-07 by dhjin, ���� ��ũ C->F
#define T1_FC_INFO_GET_GUILDMARK_OK						0x47	// 2007-12-07 by dhjin, ���� ��ũ F->C
#define T1_FC_INFO_MSWARINFO_DISPLAY					0x48	// 2008-03-27 by dhjin, ���� ���� ǥ�� ��ȹ�� - ���� ���� ���� F->C
#define T1_FC_INFO_MSWARINFO_DISPLAY_OPTION				0x49	// 2008-03-27 by dhjin, ���� ���� ǥ�� ��ȹ�� - ���� ���� �ɼ� ���� C->F
#define T1_FC_INFO_MSWARINFO_DISPLAY_OPTION_OK			0x4A	// 2008-03-27 by dhjin, ���� ���� ǥ�� ��ȹ�� - ���� ���� �ɼ� ���� F->C
#define T1_FC_INFO_MSWARINFO_RESULT						0x4B	// 2008-04-02 by dhjin, ����, ������ ����â ��ȹ�� - ���� ��� ���� C->F
#define T1_FC_INFO_MSWARINFO_RESULT_OK					0x4C	// 2008-04-02 by dhjin, ����, ������ ����â ��ȹ�� - ���� ��� ���� F->C
#define T1_FC_INFO_SPWARINFO_RESULT						0x4D	// 2008-04-02 by dhjin, ����, ������ ����â ��ȹ�� - ������ ��� ���� C->F
#define T1_FC_INFO_SPWARINFO_RESULT_OK_HEADER			0x4E	// 2008-04-02 by dhjin, ����, ������ ����â ��ȹ�� - ������ ��� ���� F->C
#define T1_FC_INFO_SPWARINFO_RESULT_OK					0x4F	// 2008-04-02 by dhjin, ����, ������ ����â ��ȹ�� - ������ ��� ���� F->C
#define T1_FC_INFO_SPWARINFO_RESULT_OK_DONE				0x50	// 2008-04-02 by dhjin, ����, ������ ����â ��ȹ�� - ������ ��� ���� F->C
#define T1_FC_INFO_DECLARATION_MSWAR_INFO				0x51	// 2009-01-12 by dhjin, ���� ���� - �������� ���� ��û C->F
#define T1_FC_INFO_DECLARATION_MSWAR_INFO_OK			0x52	// 2009-01-12 by dhjin, ���� ���� - �������� ���� ���� F->C
#define T1_FC_INFO_DECLARATION_MSWAR_SET				0x53	// 2009-01-12 by dhjin, ���� ���� - �������� �ð� �� ���� ���� C->F

#define T1_FC_INFO_WRK_GET_SERVICE_INFO					0x60	// 2009-02-12 by cmkwon, EP3-3 ���巩ŷ�ý��� ���� - C->F
#define T1_FC_INFO_WRK_GET_SERVICE_INFO_OK				0x61	// 2009-02-12 by cmkwon, EP3-3 ���巩ŷ�ý��� ���� - F->C
#define T1_FC_INFO_WRK_GET_SERVICE_INFO_OK_IMAGE		0x62	// 2009-02-12 by cmkwon, EP3-3 ���巩ŷ�ý��� ���� - F->C
#define T1_FC_INFO_WRK_GET_SERVICE_INFO_OK_DONE			0x63	// 2009-02-12 by cmkwon, EP3-3 ���巩ŷ�ý��� ���� - F->C
#define T1_FC_INFO_WRK_GET_RANKER_LIST					0x64	// 2009-02-12 by cmkwon, EP3-3 ���巩ŷ�ý��� ���� - C->F
#define T1_FC_INFO_WRK_GET_LEVEL_RANKER_LIST_OK			0x65	// 2009-02-12 by cmkwon, EP3-3 ���巩ŷ�ý��� ���� - F->C
#define T1_FC_INFO_WRK_GET_FAME_RANKER_LIST_OK			0x66	// 2009-02-12 by cmkwon, EP3-3 ���巩ŷ�ý��� ���� - F->C
#define T1_FC_INFO_WRK_GET_PVP_RANKER_LIST_OK			0x67	// 2009-02-12 by cmkwon, EP3-3 ���巩ŷ�ý��� ���� - F->C
#define T1_FC_INFO_WRK_GET_SELF_RANKING					0x68	// 2009-02-12 by cmkwon, EP3-3 ���巩ŷ�ý��� ���� - C->F
#define T1_FC_INFO_WRK_GET_SELF_RANKING_OK				0x69	// 2009-02-12 by cmkwon, EP3-3 ���巩ŷ�ý��� ���� - F->C
#define T1_FC_INFO_APPLY_RESISTANCE_ITEM				0x70	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ������ ���� ���� ����, F -> C(n)
#define T1_FC_INFO_APPLY_DESTPARAM						0x71	// 2009-09-09 ~ 2010-02-10 by dhjin, ���Ǵ�Ƽ - �ߵ�������������, F -> C(n)
#define T1_FC_INFO_APPLY_DESTPARAM_LIST					0x72	// 2009-09-09 ~ 2010-02-10 by dhjin, ���Ǵ�Ƽ - �ߵ�������������, F -> C(n)
#define T1_FC_INFO_NGCSPWAR_DISPLAY						0x73	// 2013-08-14 by jhseol, ������ ������ - NGC ����

// FC_REQUEST - ĳ���Ͱ��� ��û, ����, ���� � ����, general-purpose
#define T1_FC_REQUEST_REQUEST				0x00
#define T1_FC_REQUEST_REQUEST_OK			0x01
#define T1_FC_REQUEST_ACCEPT_REQUEST		0x02
#define T1_FC_REQUEST_ACCEPT_REQUEST_OK		0x03
#define T1_FC_REQUEST_REJECT_REQUEST		0x04
#define T1_FC_REQUEST_REJECT_REQUEST_OK		0x05
#define T1_FC_REQUEST_CANCEL_REQUEST		0x06


//////////////////////////////////////////////////////////////////////////
// FC_CITY
#define T1_FC_CITY_GET_BUILDING_LIST						0x00
#define T1_FC_CITY_GET_BUILDING_LIST_OK						0x01
#define T1_FC_CITY_GET_WARP_TARGET_MAP_LIST					0x02
#define T1_FC_CITY_GET_WARP_TARGET_MAP_LIST_OK				0x03
#define T1_FC_CITY_REQUEST_ENTER_BUILDING					0x04	// C->F, ���� �� ���� ��û
#define T1_FC_CITY_REQUEST_ENTER_BUILDING_OK				0x05	// F->C, ���� ���� �ϷḦ �˸�
#define T1_FC_CITY_REQUEST_WARP								0x06	// C->F, ���ÿ��� �����ؼ� ������ ���� ��û
#define T1_FC_CITY_CHECK_WARP_STATE							0x07
#define T1_FC_CITY_CHECK_WARP_STATE_OK						0x08

#define T1_FC_CITY_POLL_REQUEST_LEADER_CANDIDATE_LIST			0x10	// C->F, ������ �ĺ� ����Ʈ ��û
#define T1_FC_CITY_POLL_REQUEST_LEADER_CANDIDATE_LIST_OK_HEADER	0x11	// F->C, ������ �ĺ� ����Ʈ ��û
#define T1_FC_CITY_POLL_REQUEST_LEADER_CANDIDATE_LIST_OK		0x12	// F->C, ������ �ĺ� ����Ʈ ��û
#define T1_FC_CITY_POLL_REQUEST_LEADER_CANDIDATE_LIST_OK_DONE	0x13	// F->C, ������ �ĺ� ����Ʈ ��û
#define T1_FC_CITY_POLL_REQUEST_LEADER_CANDIDATE_INFO			0x14	// C->F, ������ �ĺ� ���� ��û
#define T1_FC_CITY_POLL_REQUEST_LEADER_CANDIDATE_INFO_OK		0x15	// F->C, ������ �ĺ� ���� ��û
#define T1_FC_CITY_POLL_REQUEST_LEADER_CANDIDATE_INFO_OK_GUILDMARK		0x16	// F->C, ������ �ĺ� ���� ��û ���� ��ũ
#define T1_FC_CITY_POLL_REG_LEADER_CANDIDATE					0x17	// C->F, ������ �ĺ� ���
#define T1_FC_CITY_POLL_REG_LEADER_CANDIDATE_OK					0x18	// F->C, ������ �ĺ� ���
#define T1_FC_CITY_POLL_DELETE_LEADER_CANDIDATE					0x19	// C->F, ������ �ĺ� Ż��
#define T1_FC_CITY_POLL_DELETE_LEADER_CANDIDATE_OK				0x1A	// F->C, ������ �ĺ� Ż��
#define T1_FC_CITY_POLL_VOTE									0x1B	// C->F, ������ �ĺ����� ��ǥ
#define T1_FC_CITY_POLL_VOTE_OK									0x1C	// F->C, ������ �ĺ����� ��ǥ
#define T1_FC_CITY_POLL_REQUEST_POLL_DATE						0x1D	// C->F, ���� �Ⱓ ��û
#define T1_FC_CITY_POLL_REQUEST_POLL_DATE_OK					0x1E	// F->C, ���� �Ⱓ ��û
#define T1_FC_CITY_POLL_LEADER_ELECTION_INFO					0x1F	// F->C, ���� ��� ����

#define T1_FC_CITY_WARINFO_INFLUENCE							0x20	// C->F, ���� ����
#define T1_FC_CITY_WARINFO_INFLUENCE_OK							0x21	// F->C, ���� ����
#define T1_FC_CITY_WARINFO_OUTPOST								0x22	// C->F, �������� ����
#define T1_FC_CITY_WARINFO_OUTPOST_OK							0x23	// F->C, �������� ���� 



//////////////////////////////////////////////////////////////////////////
// FC_TIMER
#define T1_FC_TIMER_START_TIMER					0x00	// F->C, TIMER_EVENT ����
#define T1_FC_TIMER_STOP_TIMER					0x01	// F->C, TIMER_EVENT ����
#define T1_FC_TIMER_UPDATE_TIMER				0x02	// F->C, TIMER_EVENT ����(�ð� ����)
#define T1_FC_TIMER_PAUSE_TIMER					0x03	// F->C, TIMER_EVENT �Ͻ� ����
#define T1_FC_TIMER_CONTINUE_TIMER				0x04	// F->C, TIMER_EVENT �����
#define T1_FC_TIMER_TIMEOUT						0x05	// C->F, �ð��� �� ���� �˸�

// Debug String
#define T1_FC_CLIENT_REPORT					0x00
#define T1_IC_STRING_128					0x01
#define T1_IC_STRING_256					0x02
#define T1_IC_STRING_512					0x03

#define T1_FC_STRING_128					0x01
#define T1_FC_STRING_256					0x02
#define T1_FC_STRING_512					0x03

// FI_ADMIN
#define T1_FI_ADMIN_GET_CHARACTER_INFO		0x00
#define T1_FI_ADMIN_GET_CHARACTER_INFO_OK	0x01
#define T1_FI_ADMIN_CALL_CHARACTER			0x02	// I -> F
#define T1_FI_ADMIN_MOVETO_CHARACTER		0x03	// I -> F
#define T1_FI_ADMIN_PRINT_DEBUG_MSG			0x04	// I -> F
#define T1_FI_ADMIN_CHANGE_WEATHER			0x05	// I -> F

// IC_ADMIN
#define T1_IC_ADMIN_CALL_CHARACTER			0x01	// C -> I
#define T1_IC_ADMIN_GET_SERVER_STAT			0x02	// C -> I, NO BODY
#define T1_IC_ADMIN_GET_SERVER_STAT_OK		0x03	// I -> C
#define T1_IC_ADMIN_CALL_GUILD				0x04	// C -> I
#define T1_IC_ADMIN_CALLGM_INFO_OK			0x10	// C -> I, // 2006-05-08 by cmkwon
#define T1_IC_ADMIN_CALLGM_VIEW_OK			0x11	// C -> I, // 2006-05-08 by cmkwon
#define T1_IC_ADMIN_CALLGM_BRING_OK			0x12	// C -> I, // 2006-05-08 by cmkwon

// FC_ADMIN
#define T1_FC_ADMIN_GET_SERVER_STAT			0x00	// C -> F, NO BODY
#define T1_FC_ADMIN_GET_SERVER_STAT_OK		0x01	// F -> C

// T0_IC_COUNTDOWN
#define T1_IC_COUNTDOWN_START				0x00	// I -> C
#define T1_IC_COUNTDOWN_DONE				0x01	// C -> I

// T0_IC_VOIP
// 2008-06-17 by dhjin, EP3 VOIP -
#define T1_IC_VOIP_SET						0x00		// C -> I, 2008-06-17 by dhjin, EP3 VOIP - ���� 
#define T1_IC_VOIP_SET_OK					0x01		// I -> C, 2008-06-17 by dhjin, EP3 VOIP - ���� ���� ����

//////////////////////////////////////////////////////////////////////////
// T0_IC_CHATROOM
#define T1_IC_CHATROOM_CREATE					0x00	// C -> I, 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� ����
#define T1_IC_CHATROOM_CREATE_OK				0x01	// I -> C, 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� ���� OK
#define T1_IC_CHATROOM_LIST_INFO				0x02	// C -> I, 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� ��� ��������
#define T1_IC_CHATROOM_LIST_INFO_OK				0x03	// I -> C, 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� ��� �������� OK
#define T1_IC_CHATROOM_REQUEST_INVITE			0x04	// C -> I, 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� �ʴ� ��û 
#define T1_IC_CHATROOM_REQUEST_INVITE_QUESTION	0x05	// I -> C, 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� �ʴ� ��󿡰� ����
#define T1_IC_CHATROOM_JOIN						0x06	// C -> I, 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� ����
#define T1_IC_CHATROOM_JOIN_OK					0x07	// I -> C, 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� ���� OK
#define T1_IC_CHATROOM_ACCEPT_INVITE			0x08	// C -> I, 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� �ʴ� ����
#define T1_IC_CHATROOM_ACCEPT_INVITE_OK			0x09	// I -> C, 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� �ʴ� ���� OK
#define T1_IC_CHATROOM_REJECT_INVITE			0x0A	// C -> I, 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� �ʴ� ����
#define T1_IC_CHATROOM_REJECT_INVITE_OK			0x0B	// I -> C, 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� �ʴ� ���� OK
#define T1_IC_CHATROOM_LEAVE					0x0C	// C -> I, 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� ������
#define T1_IC_CHATROOM_LEAVE_OK					0x0D	// I -> C, 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� ������ OK
#define T1_IC_CHATROOM_BAN						0x0E	// C -> I, 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� �߹�
#define T1_IC_CHATROOM_BAN_OK					0x0F	// I -> C, 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� �߹� OK
#define T1_IC_CHATROOM_CHANGE_NAME				0x10	// C -> I, 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� �̸� ����
#define T1_IC_CHATROOM_CHANGE_NAME_OK			0x11	// I -> C, 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� �̸� ���� OK
#define T1_IC_CHATROOM_CHANGE_MASTER			0x12	// C -> I, 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� ���� ����
#define T1_IC_CHATROOM_CHANGE_MASTER_OK			0x13	// I -> C, 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� ���� ���� OK
#define T1_IC_CHATROOM_CHANGE_LOCK_PW			0x14	// C -> I, 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� ��й�ȣ ����
#define T1_IC_CHATROOM_CHANGE_LOCK_PW_OK		0x15	// I -> C, 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� ��й�ȣ ���� OK
#define T1_IC_CHATROOM_CHANGE_MAX_MEMBER		0x16	// C -> I, 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� �ο��� ����
#define T1_IC_CHATROOM_CHANGE_MAX_MEMBER_OK		0x17	// I -> C, 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� �ο��� ���� OK
#define T1_IC_CHATROOM_MEMBER_INFO				0x18	// C -> I, 2008-06-25 by dhjin, EP3 ä�ù� - ä�ù� �ɹ� ���� ����
#define T1_IC_CHATROOM_MEMBER_INFO_OK			0x19	// I -> C, 2008-06-25 by dhjin, EP3 ä�ù� - ä�ù� �ɹ� ���� ���� OK
#define T1_IC_CHATROOM_OTHER_MEMBER_INFO		0x1A	// C -> I, 2008-06-25 by dhjin, EP3 ä�ù� - ä�ù� �ٸ� �ɹ� ���� ����
#define T1_IC_CHATROOM_OTHER_MEMBER_INFO_OK		0x1B	// I -> C, 2008-06-25 by dhjin, EP3 ä�ù� - ä�ù� �ٸ� �ɹ� ���� ���� OK


// T0_FC_CITYWAR
#define T1_FC_CITYWAR_START_WAR					0x01
#define T1_FC_CITYWAR_MONSTER_CREATED			0x02
#define T1_FC_CITYWAR_MONSTER_DEAD				0x03
#define T1_FC_CITYWAR_END_WAR					0x04
#define T1_FC_CITYWAR_GET_OCCUPYINFO			0x05	// C->F
#define T1_FC_CITYWAR_GET_OCCUPYINFO_OK			0x06	// F->C
#define T1_FC_CITYWAR_SET_SETTINGTIME			0x07	// C->F
#define T1_FC_CITYWAR_SET_TEX					0x08	// C->F
#define T1_FC_CITYWAR_SET_BRIEFING				0x09	// C->F
#define T1_FC_CITYWAR_BRING_SUMOFTEX			0x0A	// C->F
#define T1_FC_CITYWAR_BRING_SUMOFTEX_OK			0x0B	// F->C

// T0_FC_WAR
#define T1_FC_WAR_NOTIFY_INVASION					0x01	// F->C(n)
#define T1_FC_WAR_NOTIFY_INFLUENCE_MONSTER_DEAD		0x02	// F->C(n)
#define T1_FC_WAR_NOTIFY_INFLUENCE_MONSTER_INVASION	0x03	// F->C(n),// 2006-01-20 by cmkwon
#define T1_FC_WAR_NOTIFY_INFLUENCE_MONSTER_AUTO_DESTROYED		0x04	// F->C(n), // 2007-02-14 by dhjin

#define T1_FC_WAR_BOSS_MONSTER_SUMMON_DATA			0x10	// F->C, F->C(n) - 2006-04-14 by cmkwon
#define T1_FC_WAR_JACO_MONSTER_SUMMON				0x11	// F->C(n) // 2006-04-20 by cmkwon
#define T1_FC_WAR_STRATEGYPOINT_MONSTER_SUMMON		0x12	// F->C		// 2007-07-16 by dhjin
#define T1_FC_WAR_SIGN_BOARD_INSERT_STRING			0x20	// F->C(n) - 2006-04-17 by cmkwon
#define T1_FC_WAR_SIGN_BOARD_DELETE_STRING			0x21	// F->C(n) - 2006-04-17 by cmkwon
#define T1_FC_WAR_REQ_SIGN_BOARD_STRING_LIST		0x22	// C->F - 2006-04-17 by cmkwon
#define T1_FC_WAR_REQ_SIGN_BOARD_STRING_LIST_OK		0x23	// F->C - 2006-04-17 by cmkwon
#define T1_FC_WAR_UPDATE_CONTRIBUTION_POINT_OK		0x24	// F->C(n) - 2006-04-19 by cmkwon
#define T1_FC_WAR_INFLUENCE_DATA					0x25	// F->C - 2006-04-21 by cmkwon


#define T1_FC_WAR_MONSTER_CREATED					0x30	// 2006-11-20 by cmkwon, F->C(n)
#define T1_FC_WAR_MONSTER_AUTO_DESTROYED			0x31	// 2006-11-20 by cmkwon, F->C(n)
#define T1_FC_WAR_MONSTER_DEAD						0x32	// 2006-11-20 by cmkwon, F->C(n)
#define T1_FC_WAR_BOSS_CONTRIBUTION_GUILD			0x33	// 2008-12-29 by dhjin, ���� ���� �߰���, F->C(n)

#define T1_FC_WAR_INFLUENCE_CONSECUTIVE_VICTORITES	0x34	// 2013-05-09 by hskim, ���� ����Ʈ ����
#define T1_FC_WAR_INFLUENCE_CONSECUTIVE_POINT		0x35	// F->C // 2013-08-01 by jhseol, ������ ���� ������ - ��������Ʈ ���� �����ֱ�
#define T1_FC_INFLUENCE_SHOW_INFO					0x36	// F->C // 2014-06-17 by bckim, ���� �ұ��� ( �������� �� �켼���� ǥ�� )



///////////////////////////////////////////////////////////////////////////////
// 2006-07-25 by cmkwon
// T0_FC_BAZAAR
#define T1_FC_BAZAAR_CUSTOMER_INFO_OK				0x01	// F->C
#define T1_FC_BAZAAR_INFO_OK						0x02	// F->C(n)
#define T1_FC_BAZAAR_SELL_PUT_ITEM					0x03	// C->F
#define T1_FC_BAZAAR_SELL_PUT_ITEM_OK				0x04	// F->C
#define T1_FC_BAZAAR_SELL_CANCEL_ITEM				0x05	// C->F
#define T1_FC_BAZAAR_SELL_CANCEL_ITEM_OK			0x06	// F->C
#define T1_FC_BAZAAR_SELL_START						0x07	// C->F
#define T1_FC_BAZAAR_SELL_START_OK					0x08	// F->C
#define T1_FC_BAZAAR_SELL_REQUEST_ITEMLIST			0x09	// C->F
#define T1_FC_BAZAAR_SELL_REQUEST_ITEMLIST_OK		0x0A	// F->C
#define T1_FC_BAZAAR_SELL_ITEM_ENCHANTLIST_OK		0x0B	// F->C
#define T1_FC_BAZAAR_SELL_BUY_ITEM					0x0C	// C->F
#define T1_FC_BAZAAR_SELL_BUY_ITEM_OK				0x0D	// F->C(2)

#define T1_FC_BAZAAR_BUY_PUT_ITEM					0x23	// C->F
#define T1_FC_BAZAAR_BUY_PUT_ITEM_OK				0x24	// F->C
#define T1_FC_BAZAAR_BUY_CANCEL_ITEM				0x25	// C->F
#define T1_FC_BAZAAR_BUY_CANCEL_ITEM_OK				0x26	// F->C
#define T1_FC_BAZAAR_BUY_START						0x27	// C->F
#define T1_FC_BAZAAR_BUY_START_OK					0x28	// F->C
#define T1_FC_BAZAAR_BUY_REQUEST_ITEMLIST			0x29	// C->F
#define T1_FC_BAZAAR_BUY_REQUEST_ITEMLIST_OK		0x2A	// F->C
#define T1_FC_BAZAAR_BUY_SELL_ITEM					0x2B	// C->F
#define T1_FC_BAZAAR_BUY_SELL_ITEM_OK				0x2C	// F->C(2)






// T0_FI_CITYWAR

// T0_FI_CASH
#define T1_FI_CASH_USING_GUILD						0x00
#define T1_FI_CASH_USING_CHANGE_CHARACTERNAME		0x01
#define T1_FI_CASH_PREMIUM_CARD_INFO                0x02
#define T1_FI_GUILD_RANK_OK							0x03
#define T1_FI_GUILD_DELETE_INFO_OK					0x04

// T0_FI_WAR, // 2005-12-27 by cmkwon
#define T1_FI_WAR_ADD_GUILD_FAME					0x00	// F->I

// T0_FI_INFO
#define T1_FI_INFO_DECLARATION_MSWAR_SET_OK			0x00	// F->I		// 2009-01-12 by dhjin, ���� ���� - �������� �ð� �� ���� ���� F->I

// T0_IC_INFO
#define T1_IC_INFO_DECLARATION_MSWAR_SET_OK			0x00	// I->C		// 2009-01-12 by dhjin, ���� ���� - �������� �ð� �� ���� ���� I->C

// T0_IC_CITYWAR

// T0_FN_CITYWAR
#define T1_FN_CITYWAR_START_WAR					0x00	// F->N
#define T1_FN_CITYWAR_END_WAR					0x01	// F->N
#define T1_FN_CITYWAR_CHANGE_OCCUPY_INFO		0x02	// F->N

// SendErrorMessage� Type���� ����ϱ� ����
#define T1_PRE_IOCP								0x00
#define T1_PRE_DB								0x01

#define T1_IM_IOCP								0x00
#define T1_IM_DB								0x01

#define T1_FIELD_IOCP							0x00
#define T1_FIELD_DB								0x01

#define T1_NPC_IOCP								0x00
#define T1_NPC_DB								0x01

#define T1_TIMER								0x00

#define T1_DB									0x00

// INVALID PROTOCOL
#define T1_NA									0x00

// ERROR
#define T1_ERROR								0x00


// T0_FC_RACING
#define T1_FC_RACING_RACINGLIST_REQUEST			0x00	// No Body
#define T1_FC_RACING_RACINGLIST_REQUEST_ACK		0x01
#define T1_FC_RACING_RACINGINFO_REQUEST			0x02
#define T1_FC_RACING_RACINGINFO_REQUEST_ACK		0x03
#define T1_FC_RACING_RACINGNOTIFY				0x04
#define T1_FC_RACING_JOIN_ENABLE				0x05
#define T1_FC_RACING_JOIN_REQUEST				0x06
#define T1_FC_RACING_JOIN_REQUEST_ACK			0x07
#define T1_FC_RACING_COUNTDOWN					0x08
#define T1_FC_RACING_CHECKPOINT_CHECK			0x09
#define T1_FC_RACING_CHECKPOINT_CHECK_ACK		0x0A
#define T1_FC_RACING_FINISHED					0x0B
#define T1_FC_RACING_OTHER_FINISHED				0x0C
#define T1_FC_RACING_FINALRANKING				0x0D


//////////////////////////////////////////////////////////////////////////
// 2007-04-17 by dhjin
// T0_FC_ARENA
#define T1_FC_ARENA_REQUEST_TEAM				0x00	// C->F
#define T1_FC_ARENA_REQUEST_TEAM_OK				0x01	// F->C
#define T1_FC_ARENA_CREATE_TEAM					0x02	// C->F
#define T1_FC_ARENA_CREATE_TEAM_OK				0x03	// F->C
#define T1_FC_ARENA_ENTER_TEAM					0x04	// C->F
#define T1_FC_ARENA_ENTER_TEAM_OK				0x05	// F->C
#define T1_FC_ARENA_TEAM_MEMBER_LIST			0x06	// F->C(n)
#define T1_FC_ARENA_REAVE_TEAM					0x07	// C->F
#define T1_FC_ARENA_REAVE_TEAM_OK				0x08	// F->C
#define T1_FC_ARENA_TEAM_READY					0x09	// F->C(n)
#define T1_FC_ARENA_TEAM_READY_FINISH			0x0A	// C->F
#define T1_FC_ARENA_TEAM_READY_FINISH_CANCEL	0x0B	// C->F
#define T1_FC_ARENA_TEAM_MATCHING				0x0C	// F->C(n)
#define T1_FC_ARENA_ENTER_ROOM					0x0D	// F->C(n)
#define T1_FC_ARENA_ENTER_ROOM_WARP				0x0E	// C->F
#define T1_FC_ARENA_ROOM_WAR_START				0x0F	// F->C(n)
#define T1_FC_ARENA_ROOM_WAR_INFO				0x10	// F->C(n)	
#define T1_FC_ARENA_ROOM_WAR_FINISH_HEADER		0x11	// F->C(n)
#define T1_FC_ARENA_ROOM_WAR_FINISH				0x12	// F->C(n)
#define T1_FC_ARENA_ROOM_WAR_FINISH_DONE		0x13	// F->C(n)
#define T1_FC_ARENA_ROOM_WAR_FINISH_DRAW		0x14	// F->C(n)
#define T1_FC_ARENA_FINISH_WARP					0x15	// C->F
#define T1_FC_ARENA_FINISH_WARP_OK				0x16	// F->C(n)
#define T1_FC_ARENA_REQUEST_CREATE_TEAMINFO		0x17	// C->F
#define T1_FC_ARENA_REQUEST_CREATE_TEAMINFO_OK	0x18	// F->C
#define T1_FC_ARENA_BEFORE_ROOM_WAR_FINISH		0x19	// F->C
#define T1_FC_ARENA_REQUEST_OTHER_TEAM_INFO		0x1A	// C->F
#define T1_FC_ARENA_REQUEST_OTHER_TEAM_INFO_OK	0x1B	// F->C
#define T1_FC_ARENA_GM_COMMAND_INFO_HEADER		0x1C	// F->C
#define T1_FC_ARENA_GM_COMMAND_INFO				0x1D	// F->C
#define T1_FC_ARENA_GM_COMMAND_INFO_DONE		0x1E	// F->C
#define T1_FC_ARENA_QUICK_ENTER_TEAM			0x1F	// C->F
#define T1_FC_ARENA_WATCH_READY					0x20	// F->C
#define T1_FC_ARENA_WATCH_START					0x21	// F->C
#define T1_FC_ARENA_WATCH_END					0x22	// F->C
#define T1_FC_ARENA_WATCH_REMOVE_USER			0x23	// F->C
// �Ʒ��� ���� -
#define T1_FC_ARENA_POSSIBLE_GAMESTART			0x24	// F->C
#define T1_FC_ARENA_CHARACTER_GAMESTART			0x25	// C->F
#define T1_FC_ARENA_CHARACTER_GAMESTART_OK		0x26	// F->C
#define T1_FC_ARENA_USE_CITYWARPITEM			0x27	// F->C
#define T1_FC_ARENA_PLAY_CHARACTER_TYPE			0x28	// c->f(a)	// 2012-06-08 by jhseol, �Ʒ��� �߰�����part2 - �ɸ��� : Ÿ�� ����


//////////////////////////////////////////////////////////////////////////
// 2007-07-06 by dhjin, Tutorial
// T0_FC_TUTORIAL
#define T1_FC_TUTORIAL_START					0x00	// C->F
#define T1_FC_TUTORIAL_START_OK					0x01	// F->C
#define T1_FC_TUTORIAL_COMPLETE					0x02	// C->F
#define T1_FC_TUTORIAL_COMPLETE_OK				0x03	// F->C
#define T1_FC_TUTORIAL_END						0x04	// C->F
#define T1_FC_TUTORIAL_END_OK					0x05	// F->C
#define T1_FC_TUTORIAL_WARP						0x06	// C->F


//////////////////////////////////////////////////////////////////////////
// 2007-08-13 by dhjin, OutPost
// T0_FC_OUTPOST
#define T1_FC_OUTPOST_WAR_BEFORE				0x00	// F->C(N)
#define T1_FC_OUTPOST_WAR_START					0x01	// F->C(N)
#define T1_FC_OUTPOST_PROTECTOR_DESTROY			0x02	// F->C(N)
//#define T1_FC_OUTPOST_RESET_CHECK_START			0x03	// C->F
//#define T1_FC_OUTPOST_RESET_CHECK_START_OK		0x04	// F->C
#define T1_FC_OUTPOST_RESET_START				0x05	// C->F
#define T1_FC_OUTPOST_RESET_START_OK			0x06	// F->C
#define T1_FC_OUTPOST_RESET_DESTROY				0x07	// F->C
#define T1_FC_OUTPOST_RESET_SUCCESS				0x08	// F->C
#define T1_FC_OUTPOST_WAR_END					0x09	// F->C(N)
#define T1_FC_OUTPOST_NEXTWAR_INFO_REQUEST		0x0A	// C->F
#define T1_FC_OUTPOST_NEXTWAR_INFO_REQUEST_OK	0x0B	// F->C
#define T1_FC_OUTPOST_NEXTWAR_SET_TIME			0x0C	// C->F
#define T1_FC_OUTPOST_NEXTWAR_SET_TIME_OK		0x0D	// F->C
#define T1_FC_OUTPOST_WAR_INFO					0x0E	// F->C

////////////////////////////////////////////////////////////////////////////////
// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - 
// T0_FC_INFINITY
#define T1_FC_INFINITY_MODE_LIST				0x00	// C -> F
#define T1_FC_INFINITY_MODE_LIST_OK				0x01	// F -> C
#define T1_FC_INFINITY_READY_LIST				0x02	// C -> F
#define T1_FC_INFINITY_READY_LIST_OK			0x03	// F -> C
#define T1_FC_INFINITY_CREATE					0x04	// C -> F
#define T1_FC_INFINITY_CREATE_OK				0x05	// F -> C
#define T1_FC_INFINITY_JOIN						0x06	// C -> F
#define T1_FC_INFINITY_JOIN_REQUEST_MASTERUSER	0x07	// F -> C
#define T1_FC_INFINITY_JOIN_REQUEST_MASTERUSER_OK	0x08	// C -> F
#define T1_FC_INFINITY_JOIN_OK					0x09	// F -> C
#define T1_FC_INFINITY_MEMBER_INFO_LIST			0x0A	// C -> F
#define T1_FC_INFINITY_MEMBER_INFO_LIST_OK		0x0B	// F -> C
#define T1_FC_INFINITY_CHANGE_MASTER			0x0C	// C -> F
#define T1_FC_INFINITY_CHANGE_MASTER_OK			0x0D	// F -> C
#define T1_FC_INFINITY_LEAVE					0x0E	// C -> F
#define T1_FC_INFINITY_LEAVE_OK					0x0F	// F -> C
#define T1_FC_INFINITY_BAN						0x10	// C -> F
#define T1_FC_INFINITY_BAN_OK					0x11	// F -> C
#define T1_FC_INFINITY_READY					0x12	// C -> F
#define T1_FC_INFINITY_READY_OK					0x13	// F -> C
#define T1_FC_INFINITY_READY_CANCEL				0x14	// C -> F
#define T1_FC_INFINITY_READY_CANCEL_OK			0x15	// F -> C
#define T1_FC_INFINITY_START					0x16	// C -> F
#define T1_FC_INFINITY_MAP_LOADING				0x17	// F -> C
#define T1_FC_INFINITY_MAP_LOADED				0x18	// C -> F
#define T1_FC_INFINITY_ENTER					0x19	// F -> C
#define T1_FC_INFINITY_CINEMA					0x1A	// F -> C
#define T1_FC_INFINITY_SUCCESS_FIN				0x1B	// F -> C
#define T1_FC_INFINITY_FAIL_FIN					0x1C	// F -> C
#define T1_FC_INFINITY_FIN_OK					0x1D	// C -> F
#define T1_FC_INFINITY_READY_FINISH_MAINSVR_START 0x1E	// F -> C
#define T1_FC_INFINITY_TENDER_DROPITEM_INFO		0x1F	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���Ϳ��Լ� ����� Tender ������, F -> C
#define T1_FC_INFINITY_TENDER_START				0x20	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - Tender ����, F -> C
#define T1_FC_INFINITY_TENDER_PUT_IN_TENDER		0x21	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� Tender ��ư ����, C -> F
#define T1_FC_INFINITY_TENDER_PUT_IN_TENDER_OK  0x22	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� Tender ��ư ���� ���, F -> C
#define T1_FC_INFINITY_TENDER_RESULT			0x23	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ������ ���, F -> C
#define T1_FC_INFINITY_TENDER_TIMEOVER			0x24	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - Tender �ð��� �������� �����ڰ� ����, F -> C
#define T1_FC_INFINITY_TENDER_ALLGIVEUP			0x25	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ������ ��� ����, F -> C
#define T1_FC_INFINITY_CHANGE_LIMITTIME			0x26	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ����� �г�Ƽ �߰�, F -> C
#define T1_FC_INFINITY_JOIN_CANCEL				0x27	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���� ���
#define T1_FC_INFINITY_JOIN_CANCEL_REQUEST_MASTERUSER	0x28		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���� ���
#define T1_FC_INFINITY_REQUEST_RESTART_BY_DISCONNECT	0x29	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - �ñ� ���� ������ ó��
#define T1_FC_INFINITY_RESTART_BY_DISCONNECT	0x2A	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - �ñ� ���� ������ ó��
#define T1_FC_INFINITY_MAP_LOADED_RESTART_BY_DISCONNECT	0x2B		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - �ñ� ���� ������ ó��, C -> AFS
#define T1_FC_INFINITY_DELETED_CINEMA_HEADER	0x2C				// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - �ñ� ���� ������ ó��
#define T1_FC_INFINITY_DELETED_CINEMA			0x2D				// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - �ñ� ���� ������ ó��
#define T1_FC_INFINITY_DELETED_CINEMA_DONE		0x2E				// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - �ñ� ���� ������ ó��
#define T1_FC_INFINITY_ENTER_BY_DISCONNECT		0x2F				// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - �ñ� ���� ������ ó��
#define T1_FC_INFINITY_CHANGE_ALIVE_FOR_GAMECLEAR_MONSTERHP			0x30		// 2010-03-31 by dhjin, ���Ǵ�Ƽ(�������) - ���� ����� �г�Ƽ, F -> C

// 2010. 05. 19 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����. (��ȣó�� + ���� ó��(����) )
//#define T1_FC_INFINITY_DIFFICULTY_LIST			0x31 // 2010-05-04 by shcho, ���Ǵ�Ƽ ���̵� ���� ��� ��û. - C -> AFS
#define T1_FC_INFINITY_DIFFICULTY_LIST_OK		0x31 // 2010-05-04 by shcho, ���Ǵ�Ƽ ���̵� ���� ��� ��û. - AFS -> C

#define T1_FC_INFINITY_CHANGE_DIFFICULTY_LEVEL		0x32	// 2010. 05. 19 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����. (��ȣó�� + ���� ó��(����) ) - ���� ���̵� ����. C -> AFS
#define T1_FC_INFINITY_CHANGE_DIFFICULTY_LEVEL_OK	0x33	// 2010. 05. 19 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����. (��ȣó�� + ���� ó��(����) ) - ���� ���̵� ����. AFS -> C
// End 2010. 05. 19 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����. (��ȣó�� + ���� ó��(����) )

#define T1_FC_INFINITY_READY_CANCEL_ALL_OK		0x34		// 2010. 05. 31 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����. (������Ʈ ���� �뷱�� ���� ���� ����.) - ���� ��� �ɹ� ���� ��� ó��. AFS -> C (���� ���̵� ����� ���.)

// 2010. 07. 27 by hsLee ���Ǵ�Ƽ 2�� ���� ��� �ó׸� ���� ��ŵ ó��.
#define T1_FC_INFINITY_SKIP_ENDING_CINEMA		0x35		// ���Ǵ�Ƽ ���� ��� ���� �ó׸� ���� ��ŵ ��û. 2010. 07. 27 by hsLee.
#define T1_FC_INFINITY_SKIP_ENDING_CINEMA_OK	0x36		// ���Ǵ�Ƽ ���� ��� ���� �ó׸� ���� ��ŵ ���. 2010. 07. 27 by hsLee.
// End 2010. 07. 27 by hsLee ���Ǵ�Ƽ 2�� ���� ��� �ó׸� ���� ��ŵ ó��.

#define T1_FC_INFINITY_MOVIE					0x37		// 2011-05-17 by hskim, ���Ǵ�Ƽ 3�� - �ó׸� ����, F -> C
#define T1_FC_INFINITY_SET_LIMITTIME			0x38		// 2011-05-30 by hskim, ���Ǵ�Ƽ 3�� - �÷��� �ð� �缳�� ���, F -> C

/////////////////////////////////////////////////////////////////////////////////////////////
// T0_FC_COLLECTION
#define T1_FC_COLLECTION_INFO							0x00		// 2013-05-31 by jhseol,bckim �Ƹ� �÷��� - ��Ŷ �߰� : �÷��� ���� ��Ŷ
#define T1_FC_COLLECTION_SHAPE_CHANGE					0x01		// 2013-05-31 by jhseol,bckim �Ƹ� �÷��� - ��Ŷ �߰� : ���� ���� ��û ��Ŷ
#define T1_FC_COLLECTION_MONTHLY_AROMOR_EVENT_INIT		0x02		// 2013-04-18 by jhseol,bckim �̴��� �Ƹ� - ��Ŷ �߰� : �÷��ǿ� ǥ���� �̴��ǾƸ� �̺�Ʈ ���� �ʱ�ȭ ��Ŷ
#define T1_FC_COLLECTION_MONTHLY_AROMOR_EVENT_INFO		0x03		// 2013-04-18 by jhseol,bckim �̴��� �Ƹ� - ��Ŷ �߰� : �÷��ǿ� ǥ���� �̴��ǾƸ� �̺�Ʈ ���� ��Ŷ

// 2007-12-27 by dhjin, �Ʒ��� ���� - �Ʒ��� �������� MainField <=> ArenaField 
#define T1_FtoA_MFSINFO							0x00
#define T1_FtoA_MFSINFO_OK						0x01
#define T1_FtoA_ALIVE							0x02
#define T1_FtoA_AUTH_CHARACTER					0x03
#define T1_FtoA_AUTH_CHARACTER_OK				0x04
#define T1_FtoA_ARENA_STATE_CHANGE				0x05
#define T1_FtoA_ARENA_STATE_CHANGE_OK			0x06
#define T1_FtoA_ARENA_TEAM_MATCHING				0x07
#define T1_FtoA_ARENA_TEAM_MATCHING_OK			0x08
#define T1_FtoA_ARENA_SERVER_PAY				0x09		
#define T1_FtoA_ARENA_CHARACTER_PAY				0x0A
#define T1_FtoA_ARENA_CHARACTER_DISCONNECT		0x0B
#define T1_FtoA_ARENA_CHARACTERARENAINFO_UPDATA	0x0C	// 2012-04-12 by jhseol, �Ʒ��� �߰����� - ���� : AFS -> MFS CharacterArena UUpdata ��û ��Ŷ
#define T1_FtoA_ARENA_CHARACTER_RESET_RELOAD	0x0D	// 2012-12-18 by jhseol, �Ʒ��� ĳ���� ���� �� ĳ���� ���� �ٽ� �ε��ϱ�.
// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - MFS <-> AFS ���Ǵ�Ƽ ���� ���
#define T1_FtoA_INFINITY_IMPUTE_LIST			0x30	//	MFS -> AFS
#define T1_FtoA_INFINITY_START					0x31	//	AFS -> MFS
#define T1_FtoA_INFINITY_START_OK				0x32	//	MFS -> AFS
#define T1_FtoA_INFINITY_IMPUTE					0x33	//	AFS -> MFS
#define T1_FtoA_INFINITY_UPDATE_ALL_ITEM_COUNT	0x34	//	AFS -> MFS
#define T1_FtoA_INFINITY_INSERT_ITEM_HEADER		0x35	//	AFS -> MFS
#define T1_FtoA_INFINITY_INSERT_ITEM			0x36	//	AFS -> MFS
#define T1_FtoA_INFINITY_INSERT_ITEM_DONE		0x37	//	AFS -> MFS
#define T1_FtoA_INFINITY_UPDATE_ITEM_HEADER		0x38	//	AFS -> MFS
#define T1_FtoA_INFINITY_UPDATE_ITEM			0x39	//	AFS -> MFS
#define T1_FtoA_INFINITY_UPDATE_ITEM_DONE		0x3A	//	AFS -> MFS
#define T1_FtoA_INFINITY_DELETE_ITEM			0x3B	//	AFS -> MFS
#define T1_FtoA_INFINITY_UPDATE_USER_INFO		0x3C	//	AFS -> MFS
#define T1_FtoA_INFINITY_READY_FINISH_MAINSVR_START		0x3D		//	MFS -> AFS
#define T1_FtoA_INFINITY_LOG					0x3E	//	AFS -> MFS
#define T1_FtoA_USING_TIME_LIMIT_ITEM			0x3F	//	AFS -> MFS
#define T1_FtoA_INFINITY_STATE_CHANGE			0x40	// 2009-09-09 ~ 2010-01-20 by dhjin, ���Ǵ�Ƽ - ���� ���� ���� ���μ����� �����Ѵ�. ���� ���� üũ //	AFS -> MFS
#define T1_FtoA_INFINITY_START_CHECK			0x41	// AF->MF, // 2010-03-23 by cmkwon, ���Ǵ�Ƽ ���� ĳ�� ������ ���� - 
#define T1_FtoA_INFINITY_START_CHECK_ACK		0x42	// MF->AF, // 2010-03-23 by cmkwon, ���Ǵ�Ƽ ���� ĳ�� ������ ���� - 
#define T1_FtoA_UPDATE_ITEM_NOTI				0x43	//	MFS -> AFS // 2010-03-31 by dhjin, ���Ǵ�Ƽ ���� ĳ�� ������ ���� - 
#define T1_FtoA_INFINITY_UPDATE_USER_MAP_INFO	0x44	//	AFS -> MFS // 2010-04-06 by cmkwon, ����2�� �߰� ���� - 
#define T1_FtoA_LOG_INFINITYUSER_GET_TENDERITEM	0x45	//	AFS -> MFS //// 2010-06-25 by shcho, ���Ǵ�Ƽ ���÷α� ��� - ���� ������ ���� DB���� 
#define T1_FtoA_INFINITY_COME_BACK_PREWORK		0x46	//  AMF - >MFS // 2011-09-29 by hskim, ��Ʈ�� �ý��� 2�� - ���� MainFieldServer�� ���ư��� ���� ���� �۾� ó�� ����
#define T1_FtoA_INFINITY_UPDATE_ITEM_PET		0x47	//	AFS -> MFS // 2011-09-30 by hskim, ��Ʈ�� �ý��� 2�� - ���� MainFieldServer�� ��Ʈ�� ������ ����ȭ ���� ����
#define T1_FtoA_INFINITY_COME_BACK_POSTWORK		0x48	//  AMF - >MFS // 2011-09-29 by hskim, ��Ʈ�� �ý��� 2�� - ���� MainFieldServer�� ���ư��� ���� �� �۾� ó�� ����

// 2011-01-26 by hskim, ���� ���� ����
#define T1_PAUTH_CONNECT_LOGIN					0x00
#define T1_PAUTH_CONNECT_LOGIN_OK				0x01
#define T1_PAUTH_CONNECT_LOGIN_FAIL				0x02
#define T1_PAUTH_CONNECT_LOGIN_SHUTDOWN			0x03

// 2011-10-18 by hskim, EP4 [Ʈ���� �ý���] - ȭ���� / �� ��ǳ
#define T1_FC_TRIGGER_MAP_BUFF_SKILL			0x00
#define T1_FC_SET_LIMITTIME						0x01

///////////////////////////////////////////////////////////////////////////////
// Message Type
///////////////////////////////////////////////////////////////////////////////
#define T_PC_DEFAULT_UPDATE_LAUNCHER_VERSION		(MessageType_t)((T0_PC_DEFAULT_UPDATE<<8)|T1_PC_DEFAULT_UPDATE_LAUNCHER_VERSION)
#define T_PC_DEFAULT_UPDATE_LAUNCHER_UPDATE_INFO	(MessageType_t)((T0_PC_DEFAULT_UPDATE<<8)|T1_PC_DEFAULT_UPDATE_LAUNCHER_UPDATE_INFO)
#define T_PC_DEFAULT_UPDATE_LAUNCHER_VERSION_OK		(MessageType_t)((T0_PC_DEFAULT_UPDATE<<8)|T1_PC_DEFAULT_UPDATE_LAUNCHER_VERSION_OK)
#define T_PC_DEFAULT_NEW_UPDATE_LAUNCHER_VERSION			(MessageType_t)((T0_PC_DEFAULT_UPDATE<<8)|T1_PC_DEFAULT_NEW_UPDATE_LAUNCHER_VERSION)		// C->P
#define T_PC_DEFAULT_NEW_UPDATE_LAUNCHER_UPDATE_INFO		(MessageType_t)((T0_PC_DEFAULT_UPDATE<<8)|T1_PC_DEFAULT_NEW_UPDATE_LAUNCHER_UPDATE_INFO)	// P->C

#define T_PC_CONNECT_CLOSE						(MessageType_t)((T0_PC_CONNECT<<8)|T1_PC_CONNECT_CLOSE)
#define T_PC_CONNECT_ALIVE						(MessageType_t)((T0_PC_CONNECT<<8)|T1_PC_CONNECT_ALIVE)
#define T_PC_CONNECT_VERSION					(MessageType_t)((T0_PC_CONNECT<<8)|T1_PC_CONNECT_VERSION)
#define T_PC_CONNECT_UPDATE_INFO				(MessageType_t)((T0_PC_CONNECT<<8)|T1_PC_CONNECT_UPDATE_INFO)
#define T_PC_CONNECT_VERSION_OK					(MessageType_t)((T0_PC_CONNECT<<8)|T1_PC_CONNECT_VERSION_OK)		// no body
#define T_PC_CONNECT_REINSTALL_CLIENT			(MessageType_t)((T0_PC_CONNECT<<8)|T1_PC_CONNECT_REINSTALL_CLIENT)
#define T_PC_CONNECT_LOGIN						(MessageType_t)((T0_PC_CONNECT<<8)|T1_PC_CONNECT_LOGIN)
#define T_PC_CONNECT_LOGIN_OK					(MessageType_t)((T0_PC_CONNECT<<8)|T1_PC_CONNECT_LOGIN_OK)
#define T_PC_CONNECT_SINGLE_FILE_VERSION_CHECK		(MessageType_t)((T0_PC_CONNECT<<8)|T1_PC_CONNECT_SINGLE_FILE_VERSION_CHECK)		// single file�鿡 ���� ���� Ȯ��(deletefilelist.txt, notice.txt ��)
#define T_PC_CONNECT_SINGLE_FILE_VERSION_CHECK_OK	(MessageType_t)((T0_PC_CONNECT<<8)|T1_PC_CONNECT_SINGLE_FILE_VERSION_CHECK_OK)	// No Body
#define T_PC_CONNECT_SINGLE_FILE_UPDATE_INFO		(MessageType_t)((T0_PC_CONNECT<<8)|T1_PC_CONNECT_SINGLE_FILE_UPDATE_INFO)
#define T_PC_CONNECT_GET_SERVER_GROUP_LIST			(MessageType_t)((T0_PC_CONNECT<<8)|T1_PC_CONNECT_GET_SERVER_GROUP_LIST)		// Launcher->P, No Body
#define T_PC_CONNECT_GET_SERVER_GROUP_LIST_OK		(MessageType_t)((T0_PC_CONNECT<<8)|T1_PC_CONNECT_GET_SERVER_GROUP_LIST_OK)	// P->Launcher
#define T_PC_CONNECT_GET_GAME_SERVER_GROUP_LIST		(MessageType_t)((T0_PC_CONNECT<<8)|T1_PC_CONNECT_GET_GAME_SERVER_GROUP_LIST)		// 2007-05-02 by cmkwon, C->P
#define T_PC_CONNECT_GET_GAME_SERVER_GROUP_LIST_OK	(MessageType_t)((T0_PC_CONNECT<<8)|T1_PC_CONNECT_GET_GAME_SERVER_GROUP_LIST_OK)		// 2007-05-02 by cmkwon, P->C
#define T_PC_CONNECT_NETWORK_CHECK					(MessageType_t)((T0_PC_CONNECT<<8)|T1_PC_CONNECT_NETWORK_CHECK)			// 2007-06-18 by cmkwon, C->P, // 2007-06-18 by cmkwon, ��Ʈ��ũ ���� üũ
#define T_PC_CONNECT_NETWORK_CHECK_OK				(MessageType_t)((T0_PC_CONNECT<<8)|T1_PC_CONNECT_NETWORK_CHECK_OK)		// 2007-06-18 by cmkwon, P->C, // 2007-06-18 by cmkwon, ��Ʈ��ũ ���� üũ
#define T_PC_CONNECT_GET_NEW_GAME_SERVER_GROUP_LIST		(MessageType_t)((T0_PC_CONNECT<<8)|T1_PC_CONNECT_GET_NEW_GAME_SERVER_GROUP_LIST)	// 2007-09-05 by cmkwon, EXE_1�� �α��� ���� ���� �������̽� ���� - C->P
#define T_PC_CONNECT_GET_NEW_GAME_SERVER_GROUP_LIST_OK	(MessageType_t)((T0_PC_CONNECT<<8)|T1_PC_CONNECT_GET_NEW_GAME_SERVER_GROUP_LIST_OK)	// 2007-09-05 by cmkwon, EXE_1�� �α��� ���� ���� �������̽� ���� - P->C

#define T_PC_CONNECT_LOGIN_BLOCKED					(MessageType_t)((T0_PC_CONNECT<<8)|T1_PC_CONNECT_LOGIN_BLOCKED)				// P->Launcher

#define T_FC_CONNECT_CLOSE						(MessageType_t)((T0_FC_CONNECT<<8)|T1_FC_CONNECT_CLOSE)
#define T_FC_CONNECT_ALIVE						(MessageType_t)((T0_FC_CONNECT<<8)|T1_FC_CONNECT_ALIVE)
#define T_FC_CONNECT_LOGIN						(MessageType_t)((T0_FC_CONNECT<<8)|T1_FC_CONNECT_LOGIN)
#define T_FC_CONNECT_LOGIN_OK					(MessageType_t)((T0_FC_CONNECT<<8)|T1_FC_CONNECT_LOGIN_OK)
#define T_FC_CONNECT_SYNC_TIME					(MessageType_t)((T0_FC_CONNECT<<8)|T1_FC_CONNECT_SYNC_TIME)				// �ð� ����ȭ�� ����
#define T_FC_CONNECT_NOTIFY_SERVER_SHUTDOWN		(MessageType_t)((T0_FC_CONNECT<<8)|T1_FC_CONNECT_NOTIFY_SERVER_SHUTDOWN)	// No body, 2006-08-04 by cmkwon
#define T_FC_CONNECT_NETWORK_CHECK				(MessageType_t)((T0_FC_CONNECT<<8)|T1_FC_CONNECT_NETWORK_CHECK)		// C->F, // 2008-02-15 by cmkwon, Client<->FieldServer �� ��Ʈ��ũ ���� üũ 
#define T_FC_CONNECT_NETWORK_CHECK_OK			(MessageType_t)((T0_FC_CONNECT<<8)|T1_FC_CONNECT_NETWORK_CHECK_OK)	// F->C, // 2008-02-15 by cmkwon, Client<->FieldServer �� ��Ʈ��ũ ���� üũ 
#define T_FC_CONNECT_ARENASERVER_INFO			(MessageType_t)((T0_FC_CONNECT<<8)|T1_FC_CONNECT_ARENASERVER_INFO)		// 2007-12-28 by dhjin, �Ʒ��� ���� - F -> C 
#define T_FC_CONNECT_ARENASERVER_LOGIN			(MessageType_t)((T0_FC_CONNECT<<8)|T1_FC_CONNECT_ARENASERVER_LOGIN)		// 2007-12-28 by dhjin, �Ʒ��� ���� - AF -> C 
#define T_FC_CONNECT_ARENASERVER_LOGIN_OK		(MessageType_t)((T0_FC_CONNECT<<8)|T1_FC_CONNECT_ARENASERVER_LOGIN_OK)		// 2007-12-28 by dhjin, �Ʒ��� ���� - C -> AF 
#define T_FC_CONNECT_ARENASERVER_SSERVER_GROUP_FOR_CLIENT			(MessageType_t)((T0_FC_CONNECT<<8)|T1_FC_CONNECT_ARENASERVER_SSERVER_GROUP_FOR_CLIENT)		// 2008-02-25 by dhjin, �Ʒ��� ���� - AF -> C
#define T_FC_CONNECT_ARENASERVER_TO_IMSERVER	(MessageType_t)((T0_FC_CONNECT<<8)|T1_FC_CONNECT_ARENASERVER_TO_IMSERVER)		// 2008-03-03 by dhjin, �Ʒ��� ���� - C -> F 

#define T_FC_CONNECT_BUGTRAPSERVER_INFO			(MessageType_t)((T0_FC_CONNECT<<8)|T1_FC_CONNECT_BUGTRAPSERVER_INFO)				// 2014-01-27 by bckim, ���� Ʈ��


#define T_FP_CONNECT_CLOSE						(MessageType_t)((T0_FP_CONNECT<<8)|T1_FP_CONNECT_CLOSE)
#define T_FP_CONNECT_ALIVE						(MessageType_t)((T0_FP_CONNECT<<8)|T1_FP_CONNECT_ALIVE)
#define T_FP_CONNECT_AUTH_USER					(MessageType_t)((T0_FP_CONNECT<<8)|T1_FP_CONNECT_AUTH_USER)
#define T_FP_CONNECT_AUTH_USER_OK				(MessageType_t)((T0_FP_CONNECT<<8)|T1_FP_CONNECT_AUTH_USER_OK)
#define T_FP_CONNECT_FIELD_CONNECT				(MessageType_t)((T0_FP_CONNECT<<8)|T1_FP_CONNECT_FIELD_CONNECT)
#define T_FP_CONNECT_FIELD_CONNECT_OK			(MessageType_t)((T0_FP_CONNECT<<8)|T1_FP_CONNECT_FIELD_CONNECT_OK)
#define T_FP_CONNECT_NOTIFY_CLOSE				(MessageType_t)((T0_FP_CONNECT<<8)|T1_FP_CONNECT_NOTIFY_CLOSE)
#define T_FP_CONNECT_NOTIFY_FIELDSERVER_CHANGE		(MessageType_t)((T0_FP_CONNECT<<8)|T1_FP_CONNECT_NOTIFY_FIELDSERVER_CHANGE)
#define T_FP_CONNECT_NOTIFY_FIELDSERVER_CHANGE_OK	(MessageType_t)((T0_FP_CONNECT<<8)|T1_FP_CONNECT_NOTIFY_FIELDSERVER_CHANGE_OK)
#define T_FP_CONNECT_PREPARE_SHUTDOWN				(MessageType_t)((T0_FP_CONNECT<<8)|T1_FP_CONNECT_PREPARE_SHUTDOWN)				// No body, 2006-08-04 by cmkwon
#define T_FP_CONNECT_UPDATE_DBSERVER_GROUP			(MessageType_t)((T0_FP_CONNECT<<8)|T1_FP_CONNECT_UPDATE_DBSERVER_GROUP)			// 2008-04-29 by cmkwon, ������ ���� DB�� �߰�(�ű� ���� ĳ���� ���� ���� �ý����߰�) - P->F
#define T_FP_CONNECT_CHECK_CONNECTABLE_ACCOUNT		(MessageType_t)((T0_FP_CONNECT<<8)|T1_FP_CONNECT_CHECK_CONNECTABLE_ACCOUNT)		// 2008-04-29 by cmkwon, ������ ���� DB�� �߰�(�ű� ���� ĳ���� ���� ���� �ý����߰�) - P->F
#define T_FP_CONNECT_CHECK_CONNECTABLE_ACCOUNT_OK	(MessageType_t)((T0_FP_CONNECT<<8)|T1_FP_CONNECT_CHECK_CONNECTABLE_ACCOUNT_OK)	// 2008-04-29 by cmkwon, ������ ���� DB�� �߰�(�ű� ���� ĳ���� ���� ���� �ý����߰�) - F->P
#define T_FP_ADMIN_RELOAD_WORLDRANKING				(MessageType_t)((T0_FP_CONNECT<<8)|T1_FP_ADMIN_RELOAD_WORLDRANKING)		// 2009-02-12 by cmkwon, EP3-3 ���巩ŷ�ý��� ���� - P->F(n)
#define T_FP_ADMIN_RELOAD_INFLUENCERATE				(MessageType_t)((T0_FP_CONNECT<<8)|T1_FP_ADMIN_RELOAD_INFLUENCERATE)		// P->F // 2009-09-16 by cmkwon, ���� �ʱ�ȭ�� ���¡ ���� ���� - 

#define T_IP_CONNECT_CLOSE						(MessageType_t)((T0_IP_CONNECT<<8)|T1_IP_CONNECT_CLOSE)
#define T_IP_CONNECT_ALIVE						(MessageType_t)((T0_IP_CONNECT<<8)|T1_IP_CONNECT_ALIVE)
#define T_IP_CONNECT_IM_CONNECT					(MessageType_t)((T0_IP_CONNECT<<8)|T1_IP_CONNECT_IM_CONNECT)
#define T_IP_CONNECT_IM_CONNECT_OK				(MessageType_t)((T0_IP_CONNECT<<8)|T1_IP_CONNECT_IM_CONNECT_OK)
#define T_IP_GET_SERVER_GROUP_INFO				(MessageType_t)((T0_IP_CONNECT<<8)|T1_IP_GET_SERVER_GROUP_INFO)
#define T_IP_GET_SERVER_GROUP_INFO_ACK			(MessageType_t)((T0_IP_CONNECT<<8)|T1_IP_GET_SERVER_GROUP_INFO_ACK)
#define T_IP_ADMIN_PETITION_SET_PERIOD			(MessageType_t)((T0_IP_CONNECT<<8)|T1_IP_ADMIN_PETITION_SET_PERIOD)	// 2007-11-19 by cmkwon, �����ý��� ������Ʈ - P->I(n)
#define T_IP_ADMIN_RELOAD_ADMIN_NOTICE_SYSTEM	(MessageType_t)((T0_IP_CONNECT<<8)|T1_IP_ADMIN_RELOAD_ADMIN_NOTICE_SYSTEM)	// 2009-01-14 by cmkwon, ��� �ڵ� ���� �ý��� ���� - P->I(n)
#define T_IP_MONITOR_RELOAD_VERSION_INFO_OK		(MessageType_t)((T0_IP_CONNECT<<8)|T1_IP_MONITOR_RELOAD_VERSION_INFO_OK)	// P->I // 2013-03-14 by jhseol, �������� ���ε� �� ���� ��� IP����Ʈ�� ����


#define T_IC_CONNECT_CLOSE						(MessageType_t)((T0_IC_CONNECT<<8)|T1_IC_CONNECT_CLOSE)
#define T_IC_CONNECT_ALIVE						(MessageType_t)((T0_IC_CONNECT<<8)|T1_IC_CONNECT_ALIVE)
#define T_IC_CONNECT_LOGIN						(MessageType_t)((T0_IC_CONNECT<<8)|T1_IC_CONNECT_LOGIN)
#define T_IC_CONNECT_LOGIN_OK					(MessageType_t)((T0_IC_CONNECT<<8)|T1_IC_CONNECT_LOGIN_OK)
#define T_IC_CONNECT_FM_TO_IM_OK				(MessageType_t)((T0_IC_CONNECT<<8)|T1_IC_CONNECT_FM_TO_IM_OK)		// 2008-03-03 by dhjin, �Ʒ��� ���� - I->C

#define T_FI_CONNECT							(MessageType_t)((T0_FI_CONNECT<<8)|T1_FI_CONNECT)
#define T_FI_CONNECT_OK							(MessageType_t)((T0_FI_CONNECT<<8)|T1_FI_CONNECT_OK)
#define T_FI_CONNECT_CLOSE						(MessageType_t)((T0_FI_CONNECT<<8)|T1_FI_CONNECT_CLOSE)
#define T_FI_CONNECT_ALIVE						(MessageType_t)((T0_FI_CONNECT<<8)|T1_FI_CONNECT_ALIVE)
#define T_FI_CONNECT_NOTIFY_FIELDSERVER_IP		(MessageType_t)((T0_FI_CONNECT<<8)|T1_FI_NOTIFY_FIELDSERVER_IP)
#define T_FI_CONNECT_NOTIFY_GAMEEND				(MessageType_t)((T0_FI_CONNECT<<8)|T1_FI_NOTIFY_GAMEEND)
//#define T_FI_CONNECT_NOTIFY_MAP_CHANGE			(MessageType_t)((T0_FI_CONNECT<<8)|T1_FI_CONNECT_NOTIFY_MAP_CHANGE)	// F -> I, check: deprecated, T_FI_EVENT_NOTIFY_WARP�� ��ü��
#define T_FI_CONNECT_NOTIFY_DEAD				(MessageType_t)((T0_FI_CONNECT<<8)|T1_FI_CONNECT_NOTIFY_DEAD)		// F -> I
#define T_FI_GET_FIELD_USER_COUNTS				(MessageType_t)((T0_FI_CONNECT<<8)|T1_FI_GET_FIELD_USER_COUNTS)		// F -> I
#define T_FI_GET_FIELD_USER_COUNTS_ACK			(MessageType_t)((T0_FI_CONNECT<<8)|T1_FI_GET_FIELD_USER_COUNTS_ACK)	// F -> I
#define T_FI_CONNECT_NOTIFY_GAMESTART			(MessageType_t)((T0_FI_CONNECT<<8)|T1_FI_CONNECT_NOTIFY_GAMESTART)		// F->I, ���� �������� �� IM Server�� �˸�, ��Ƽ ���� Ȯ�� ��û ��
#define T_FI_CONNECT_NOTIFY_DEAD_GAMESTART		(MessageType_t)((T0_FI_CONNECT<<8)|T1_FI_CONNECT_NOTIFY_DEAD_GAMESTART)	// F->I, �����Ŀ� ���� �������� �� IM Server�� �˸�
#define T_FI_CONNECT_PREPARE_SHUTDOWN			(MessageType_t)((T0_FI_CONNECT<<8)|T1_FI_CONNECT_PREPARE_SHUTDOWN)		// I->F, // 2007-08-27 by cmkwon, �����ٿ��غ� ���ɾ� �߰�(SCAdminTool���� SCMonitor�� PrepareShutdown�� ���� �� �� �ְ�)

#define T_PM_CONNECT							(MessageType_t)((T0_PM_CONNECT<<8)|T1_PM_CONNECT)
#define T_PM_CONNECT_OK							(MessageType_t)((T0_PM_CONNECT<<8)|T1_PM_CONNECT_OK)
#define T_PM_CONNECT_CLOSE						(MessageType_t)((T0_PM_CONNECT<<8)|T1_PM_CONNECT_CLOSE)
#define T_PM_CONNECT_ALIVE						(MessageType_t)((T0_PM_CONNECT<<8)|T1_PM_CONNECT_ALIVE)

#define T_FM_CONNECT							(MessageType_t)((T0_FM_CONNECT<<8)|T1_FM_CONNECT)
#define T_FM_CONNECT_OK							(MessageType_t)((T0_FM_CONNECT<<8)|T1_FM_CONNECT_OK)
#define T_FM_CONNECT_CLOSE						(MessageType_t)((T0_FM_CONNECT<<8)|T1_FM_CONNECT_CLOSE)
#define T_FM_CONNECT_ALIVE						(MessageType_t)((T0_FM_CONNECT<<8)|T1_FM_CONNECT_ALIVE)

#define T_FN_CONNECT_CLOSE						(MessageType_t)((T0_FN_CONNECT<<8)|T1_FN_CONNECT_CLOSE)
#define T_FN_CONNECT_ALIVE						(MessageType_t)((T0_FN_CONNECT<<8)|T1_FN_CONNECT_ALIVE)
#define T_FN_CONNECT_INCREASE_CHANNEL			(MessageType_t)((T0_FN_CONNECT<<8)|T1_FN_CONNECT_INCREASE_CHANNEL)		// F->N
#define T_FN_CONNECT_SET_CHANNEL_STATE			(MessageType_t)((T0_FN_CONNECT<<8)|T1_FN_CONNECT_SET_CHANNEL_STATE)		// F->N

#define T_LM_CONNECT							(MessageType_t)((T0_LM_CONNECT<<8)|T1_LM_CONNECT)
#define T_LM_CONNECT_OK							(MessageType_t)((T0_LM_CONNECT<<8)|T1_LM_CONNECT_OK)
#define T_LM_CONNECT_CLOSE						(MessageType_t)((T0_LM_CONNECT<<8)|T1_LM_CONNECT_CLOSE)
#define T_LM_CONNECT_ALIVE						(MessageType_t)((T0_LM_CONNECT<<8)|T1_LM_CONNECT_ALIVE)

#define T_IM_CONNECT							(MessageType_t)((T0_IM_CONNECT<<8)|T1_IM_CONNECT)
#define T_IM_CONNECT_OK							(MessageType_t)((T0_IM_CONNECT<<8)|T1_IM_CONNECT_OK)
#define T_IM_CONNECT_CLOSE						(MessageType_t)((T0_IM_CONNECT<<8)|T1_IM_CONNECT_CLOSE)
#define T_IM_CONNECT_ALIVE						(MessageType_t)((T0_IM_CONNECT<<8)|T1_IM_CONNECT_ALIVE)

#define T_NM_CONNECT							(MessageType_t)((T0_NM_CONNECT<<8)|T1_NM_CONNECT)
#define T_NM_CONNECT_OK							(MessageType_t)((T0_NM_CONNECT<<8)|T1_NM_CONNECT_OK)
#define T_NM_CONNECT_CLOSE						(MessageType_t)((T0_NM_CONNECT<<8)|T1_NM_CONNECT_CLOSE)
#define T_NM_CONNECT_ALIVE						(MessageType_t)((T0_NM_CONNECT<<8)|T1_NM_CONNECT_ALIVE)

#define T_PL_CONNECT							(MessageType_t)((T0_PL_CONNECT<<8)|T1_PL_CONNECT)
#define T_PL_CONNECT_OK							(MessageType_t)((T0_PL_CONNECT<<8)|T1_PL_CONNECT_OK)
#define T_PL_CONNECT_CLOSE						(MessageType_t)((T0_PL_CONNECT<<8)|T1_PL_CONNECT_CLOSE)
#define T_PL_CONNECT_ALIVE						(MessageType_t)((T0_PL_CONNECT<<8)|T1_PL_CONNECT_ALIVE)

#define T_IL_CONNECT							(MessageType_t)((T0_IL_CONNECT<<8)|T1_IL_CONNECT)
#define T_IL_CONNECT_OK							(MessageType_t)((T0_IL_CONNECT<<8)|T1_IL_CONNECT_OK)
#define T_IL_CONNECT_CLOSE						(MessageType_t)((T0_IL_CONNECT<<8)|T1_IL_CONNECT_CLOSE)
#define T_IL_CONNECT_ALIVE						(MessageType_t)((T0_IL_CONNECT<<8)|T1_IL_CONNECT_ALIVE)

#define T_FL_CONNECT							(MessageType_t)((T0_FL_CONNECT<<8)|T1_FL_CONNECT)
#define T_FL_CONNECT_OK							(MessageType_t)((T0_FL_CONNECT<<8)|T1_FL_CONNECT_OK)
#define T_FL_CONNECT_CLOSE						(MessageType_t)((T0_FL_CONNECT<<8)|T1_FL_CONNECT_CLOSE)
#define T_FL_CONNECT_ALIVE						(MessageType_t)((T0_FL_CONNECT<<8)|T1_FL_CONNECT_ALIVE)

#define T_NL_CONNECT							(MessageType_t)((T0_NL_CONNECT<<8)|T1_NL_CONNECT)
#define T_NL_CONNECT_OK							(MessageType_t)((T0_NL_CONNECT<<8)|T1_NL_CONNECT_OK)
#define T_NL_CONNECT_CLOSE						(MessageType_t)((T0_NL_CONNECT<<8)|T1_NL_CONNECT_CLOSE)
#define T_NL_CONNECT_ALIVE						(MessageType_t)((T0_NL_CONNECT<<8)|T1_NL_CONNECT_ALIVE)

#define T_FI_EVENT_NOTIFY_WARP					(MessageType_t)((T0_FI_EVENT<<8)|T1_FI_EVENT_NOTIFY_WARP)			// F -> I
// 2005-07-27 by cmkwon, �ٸ� �ʵ弭������ ������ �����Ƿ� ������
//#define T_FI_EVENT_NOTIFY_WARP_OK				(MessageType_t)((T0_FI_EVENT<<8)|T1_FI_EVENT_NOTIFY_WARP_OK)		// I -> F, �ٸ� �ʵ� �������� ������ ��츸 �޴´�
//#define T_FI_EVENT_GET_WARP_INFO				(MessageType_t)((T0_FI_EVENT<<8)|T1_FI_EVENT_GET_WARP_INFO)		// F -> I, Party & TimerEvent����, �ٸ� �ʵ� �������� ������ ��� ���� ��û
//#define T_FI_EVENT_GET_WARP_INFO_OK				(MessageType_t)((T0_FI_EVENT<<8)|T1_FI_EVENT_GET_WARP_INFO_OK)	// I -> F, Party & TimerEvent����, �ٸ� �ʵ� �������� ������ ��� ���� �ֱ�
#define T_FI_EVENT_CHAT_BLOCK					(MessageType_t)((T0_FI_EVENT<<8)|T1_FI_EVENT_CHAT_BLOCK)		// 2008-12-30 by cmkwon, ������ ä�� ���� ī�� ���� - F->I

#define T_IC_CHAT_ALL							(MessageType_t)((T0_IC_CHAT<<8)|T1_IC_CHAT_ALL)
#define T_IC_CHAT_MAP							(MessageType_t)((T0_IC_CHAT<<8)|T1_IC_CHAT_MAP)
#define T_IC_CHAT_REGION						(MessageType_t)((T0_IC_CHAT<<8)|T1_IC_CHAT_REGION)
#define T_IC_CHAT_PTOP							(MessageType_t)((T0_IC_CHAT<<8)|T1_IC_CHAT_PTOP)
#define T_IC_CHAT_PARTY							(MessageType_t)((T0_IC_CHAT<<8)|T1_IC_CHAT_PARTY)
#define T_IC_CHAT_GUILD							(MessageType_t)((T0_IC_CHAT<<8)|T1_IC_CHAT_GUILD)
#define T_IC_CHAT_GET_GUILD						(MessageType_t)((T0_IC_CHAT<<8)|T1_IC_CHAT_GET_GUILD)
#define T_IC_CHAT_GET_GUILD_OK					(MessageType_t)((T0_IC_CHAT<<8)|T1_IC_CHAT_GET_GUILD_OK)
#define T_IC_CHAT_CHANGE_GUILD					(MessageType_t)((T0_IC_CHAT<<8)|T1_IC_CHAT_CHANGE_GUILD)
#define T_IC_CHAT_CHANGE_GUILD_OK				(MessageType_t)((T0_IC_CHAT<<8)|T1_IC_CHAT_CHANGE_GUILD_OK)
#define T_IC_CHAT_CHANGE_PARTY					(MessageType_t)((T0_IC_CHAT<<8)|T1_IC_CHAT_CHANGE_PARTY)
#define T_IC_CHAT_CHANGE_PARTY_OK				(MessageType_t)((T0_IC_CHAT<<8)|T1_IC_CHAT_CHANGE_PARTY_OK)
#define T_IC_CHAT_CHANGE_CHAT_FLAG				(MessageType_t)((T0_IC_CHAT<<8)|T1_IC_CHAT_CHANGE_CHAT_FLAG)
#define T_IC_CHAT_POSITION						(MessageType_t)((T0_IC_CHAT<<8)|T1_IC_CHAT_POSITION)
#define T_IC_CHAT_BLOCK							(MessageType_t)((T0_IC_CHAT<<8)|T1_IC_CHAT_BLOCK)
#define T_IC_CHAT_GET_BLOCK						(MessageType_t)((T0_IC_CHAT<<8)|T1_IC_CHAT_GET_BLOCK)
#define T_IC_CHAT_GET_BLOCK_OK					(MessageType_t)((T0_IC_CHAT<<8)|T1_IC_CHAT_GET_BLOCK_OK)
#define T_IC_CHAT_BLOCK_YOU						(MessageType_t)((T0_IC_CHAT<<8)|T1_IC_CHAT_BLOCK_YOU)
#define T_IC_CHAT_FRIENDLIST_AND_REJECTLIST_LOADING		(MessageType_t)((T0_IC_CHAT<<8)|T1_IC_CHAT_FRIENDLIST_AND_REJECTLIST_LOADING)
#define T_IC_CHAT_FRIENDLIST_LOADING_OK			(MessageType_t)((T0_IC_CHAT<<8)|T1_IC_CHAT_FRIENDLIST_LOADING_OK)
#define T_IC_CHAT_FRIENDLIST_INSERT				(MessageType_t)((T0_IC_CHAT<<8)|T1_IC_CHAT_FRIENDLIST_INSERT)
#define T_IC_CHAT_FRIENDLIST_INSERT_OK			(MessageType_t)((T0_IC_CHAT<<8)|T1_IC_CHAT_FRIENDLIST_INSERT_OK)
#define T_IC_CHAT_FRIENDLIST_DELETE				(MessageType_t)((T0_IC_CHAT<<8)|T1_IC_CHAT_FRIENDLIST_DELETE)
#define T_IC_CHAT_FRIENDLIST_DELETE_OK			(MessageType_t)((T0_IC_CHAT<<8)|T1_IC_CHAT_FRIENDLIST_DELETE_OK)
#define T_IC_CHAT_FRIENDLIST_REFRESH			(MessageType_t)((T0_IC_CHAT<<8)|T1_IC_CHAT_FRIENDLIST_REFRESH)
#define T_IC_CHAT_FRIENDLIST_REFRESH_OK			(MessageType_t)((T0_IC_CHAT<<8)|T1_IC_CHAT_FRIENDLIST_REFRESH_OK)
#define T_IC_CHAT_REJECTLIST_LOADING_OK			(MessageType_t)((T0_IC_CHAT<<8)|T1_IC_CHAT_REJECTLIST_LOADING_OK)
#define T_IC_CHAT_REJECTLIST_INSERT				(MessageType_t)((T0_IC_CHAT<<8)|T1_IC_CHAT_REJECTLIST_INSERT)
#define T_IC_CHAT_REJECTLIST_INSERT_OK			(MessageType_t)((T0_IC_CHAT<<8)|T1_IC_CHAT_REJECTLIST_INSERT_OK)
#define T_IC_CHAT_REJECTLIST_DELETE				(MessageType_t)((T0_IC_CHAT<<8)|T1_IC_CHAT_REJECTLIST_DELETE)
#define T_IC_CHAT_REJECTLIST_DELETE_OK			(MessageType_t)((T0_IC_CHAT<<8)|T1_IC_CHAT_REJECTLIST_DELETE_OK)
#define T_IC_CHAT_FRIENDLIST_INSERT_NOTIFY		(MessageType_t)((T0_IC_CHAT<<8)|T1_IC_CHAT_FRIENDLIST_INSERT_NOTIFY)	// 2009-01-13 by cmkwon, ģ�� ��Ͻ� ���濡�� �˸� �ý��� ���� - 

#define T_IC_CHAT_SELL_ALL						(MessageType_t)((T0_IC_CHAT<<8)|T1_IC_CHAT_SELL_ALL)	// �Ÿ� ��ü ä��
#define T_IC_CHAT_CASH_ALL						(MessageType_t)((T0_IC_CHAT<<8)|T1_IC_CHAT_CASH_ALL)	// ���� ��ü ä��
#define T_IC_CHAT_INFLUENCE_ALL					(MessageType_t)((T0_IC_CHAT<<8)|T1_IC_CHAT_INFLUENCE_ALL)	// ���� ��ü ä�� - ���������ڸ� ����
#define T_IC_CHAT_ARENA							(MessageType_t)((T0_IC_CHAT<<8)|T1_IC_CHAT_ARENA)			// 2007-05-02 by dhjin, �Ʒ��� ä��
#define T_IC_CHAT_WAR							(MessageType_t)((T0_IC_CHAT<<8)|T1_IC_CHAT_WAR)				// 2008-05-19 by dhjin, EP3 - ä�� �ý��� ����, ���� ä��
#if _RAT_CHAT_SYSTEM
#define T_IC_CHAT_INFLUENCE_ALL_RAT				(MessageType_t)((T0_IC_CHAT<<8)|T1_IC_CHAT_INFLUENCE_ALL_RAT)
#endif
#define T_IC_CHAT_CHATROOM						(MessageType_t)((T0_IC_CHAT<<8)|T1_IC_CHAT_CHATROOM)		// 2008-06-18 by dhjin, EP3 ä�ù� - 
#define T_IC_CHAT_INFINITY						(MessageType_t)((T0_IC_CHAT<<8)|T1_IC_CHAT_INFINITY)		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ä��

#define T_FI_CHAT_MAP							(MessageType_t)((T0_FI_CHAT<<8)|T1_FI_CHAT_MAP)
#define T_FI_CHAT_REGION						(MessageType_t)((T0_FI_CHAT<<8)|T1_FI_CHAT_REGION)
#define T_FI_CHAT_CHANGE_CHAT_FLAG				(MessageType_t)((T0_FI_CHAT<<8)|T1_FI_CHAT_CHANGE_CHAT_FLAG)
#define T_FI_CHAT_CASH_ALL						(MessageType_t)((T0_FI_CHAT<<8)|T1_FI_CHAT_CASH_ALL)	// ���� ��ü ä��
#define T_FI_CHAT_ARENA							(MessageType_t)((T0_FI_CHAT<<8)|T1_FI_CHAT_ARENA)		// 2007-05-02 by dhjin
#define	T_FI_CHAT_OUTPOST_GUILD					(MessageType_t)((T0_FI_CHAT<<8)|T1_FI_CHAT_OUTPOST_GUILD)	// 2007-10-06 by cmkwon, ���� ���� ������ ������ ���� ä�� ����
#define T_FI_CHAT_INFINITY						(MessageType_t)((T0_FI_CHAT<<8)|T1_FI_CHAT_INFINITY)		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ä��


#define T_FI_CHAT_ONLINE_EACHOTHER_FRIEND_COUNT_OK		(MessageType_t)((T0_FI_CHAT<<8)|T1_FI_CHAT_ONLINE_EACHOTHER_FRIEND_COUNT_OK)	// 2006-07-18 by cmkwon, �¶��� ģ�� ī��Ʈ
#define T_IC_CHAT_ONLINE_EACHOTHER_FRIEND_COUNT			(MessageType_t)((T0_FI_CHAT<<8)|T1_IC_CHAT_ONLINE_EACHOTHER_FRIEND_COUNT)		// 2008-07-11 by dhjin, EP3 ģ����� -

#define T_FC_CHAT_MAP							(MessageType_t)((T0_FC_CHAT<<8)|T1_FC_CHAT_MAP)
#define T_FC_CHAT_REGION						(MessageType_t)((T0_FC_CHAT<<8)|T1_FC_CHAT_REGION)
#define T_FC_CHAT_CASH_ALL						(MessageType_t)((T0_FC_CHAT<<8)|T1_FC_CHAT_CASH_ALL)
#define T_FC_CHAT_ARENA							(MessageType_t)((T0_FC_CHAT<<8)|T1_FC_CHAT_ARENA)		// 2007-05-02 by dhjin
#define T_FC_CHAT_ALL_INFLUENCE					(MessageType_t)((T0_FC_CHAT<<8)|T1_FC_CHAT_ALL_INFLUENCE)	// 2007-08-09 by cmkwon, ��� ���¿� ä�� �����ϱ� - ��������Ÿ�� �߰�
#define T_FC_CHAT_OUTPOST_GUILD					(MessageType_t)((T0_FC_CHAT<<8)|T1_FC_CHAT_OUTPOST_GUILD)	// 2007-10-06 by cmkwon, ���� ���� ������ ������ ���� ä�� ����
#define T_FC_CHAT_INFINITY						(MessageType_t)((T0_FC_CHAT<<8)|T1_FC_CHAT_INFINITY)		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ä��

#define T_FC_CHARACTER_CREATE					(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_CREATE)
#define T_FC_CHARACTER_CREATE_OK				(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_CREATE_OK)
#define T_FC_CHARACTER_DELETE					(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_DELETE)
#define T_FC_CHARACTER_DELETE_OK				(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_DELETE_OK)
#define T_FC_CHARACTER_GET_CHARACTER			(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_GET_CHARACTER)
#define T_FC_CHARACTER_GET_CHARACTER_OK			(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_GET_CHARACTER_OK)
#define T_FC_CHARACTER_GAMESTART				(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_GAMESTART)
#define T_FC_CHARACTER_GAMESTART_OK				(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_GAMESTART_OK)
#define T_FC_CHARACTER_CONNECT_GAMESTART		(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_CONNECT_GAMESTART)
#define T_FC_CHARACTER_CONNECT_GAMESTART_OK		(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_CONNECT_GAMESTART_OK)
#define T_FC_CHARACTER_GAMEEND					(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_GAMEEND)
#define T_FC_CHARACTER_GAMEEND_OK				(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_GAMEEND_OK)
#define T_FC_CHARACTER_REPAIR					(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_REPAIR)
#define T_FC_CHARACTER_REPAIR_OK				(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_REPAIR_OK)
#define T_FC_CHARACTER_REPAIR_ERR				(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_REPAIR_ERR)
#define T_FC_CHARACTER_DOCKING					(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_DOCKING)
#define T_FC_CHARACTER_UNDOCKING				(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_UNDOCKING)
#define T_FC_CHARACTER_DOCKING_ERR				(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_DOCKING_ERR)
#define T_FC_CHARACTER_GET_OTHER_INFO			(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_GET_OTHER_INFO)
#define T_FC_CHARACTER_GET_OTHER_INFO_OK		(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_GET_OTHER_INFO_OK)
#define T_FC_CHARACTER_GET_MONSTER_INFO_OK		(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_GET_MONSTER_INFO_OK)
#define T_FC_CHARACTER_CHANGE_UNITKIND			(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_CHANGE_UNITKIND)
#define T_FC_CHARACTER_CHANGE_STAT				(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_CHANGE_STAT)
#define T_FC_CHARACTER_CHANGE_TOTALGEAR_STAT	(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_CHANGE_TOTALGEAR_STAT)
#define T_FC_CHARACTER_CHANGE_FRIEND			(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_CHANGE_FRIEND)
#define T_FC_CHARACTER_CHANGE_EXP				(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_CHANGE_EXP)
#define T_FC_CHARACTER_CHANGE_BODYCONDITION		(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_CHANGE_BODYCONDITION)
#define T_FC_CHARACTER_CHANGE_BODYCONDITION_SKILL	(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_CHANGE_BODYCONDITION_SKILL)
#define T_FC_CHARACTER_CHANGE_INFLUENCE_TYPE		(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_CHANGE_INFLUENCE_TYPE)
#define T_FC_CHARACTER_CHANGE_STATUS			(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_CHANGE_STATUS)
#define T_FC_CHARACTER_CHANGE_PKPOINT			(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_CHANGE_PKPOINT)
#define T_FC_CHARACTER_CHANGE_HPDPSPEP			(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_CHANGE_HPDPSPEP)
#define T_FC_CHARACTER_CHANGE_CURRENTHPDPSPEP	(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_CHANGE_CURRENTHPDPSPEP)
#define T_FC_CHARACTER_CHANGE_CURRENTHP			(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_CHANGE_CURRENTHP)
#define T_FC_CHARACTER_CHANGE_CURRENTDP			(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_CHANGE_CURRENTDP)
#define T_FC_CHARACTER_CHANGE_CURRENTSP			(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_CHANGE_CURRENTSP)
#define T_FC_CHARACTER_CHANGE_CURRENTEP			(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_CHANGE_CURRENTEP)
#define T_FC_CHARACTER_CHANGE_MAPNAME			(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_CHANGE_MAPNAME)
#define T_FC_CHARACTER_CHANGE_PETINFO			(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_CHANGE_PETINFO)
#define T_FC_CHARACTER_CHANGE_POSITION			(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_CHANGE_POSITION)
#define T_FC_CHARACTER_CHANGE_LEVEL				(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_CHANGE_LEVEL)
#define T_FC_CHARACTER_USE_BONUSSTAT			(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_USE_BONUSSTAT)
#define T_FC_CHARACTER_USE_BONUSSTAT_OK			(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_USE_BONUSSTAT_OK)		// 2006-09-18 by cmkwon
#define T_FC_CHARACTER_DEAD_NOTIFY				(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_DEAD_NOTIFY)
#define T_FC_CHARACTER_GET_ACCOUNTUNIQUENUMBER	(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_GET_ACCOUNTUNIQUENUMBER)
#define T_FC_CHARACTER_GET_ACCOUNTUNIQUENUMBER_OK	(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_GET_ACCOUNTUNIQUENUMBER_OK)
#define T_FC_CHARACTER_APPLY_COLLISION_DAMAGE	(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_APPLY_COLLISION_DAMAGE)
#define T_FC_CHARACTER_GET_OTHER_MOVE			(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_GET_OTHER_MOVE)
#define T_FC_CHARACTER_DELETE_OTHER_INFO		(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_DELETE_OTHER_INFO)
#define T_FC_CHARACTER_DEAD_GAMESTART			(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_DEAD_GAMESTART)	// C -> F
#define T_FC_CHARACTER_OTHER_REVIVED			(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_OTHER_REVIVED)		// F -> C, �׾��� �ǻ�Ƴ��� �� �ٸ� ĳ����(����� ��Ƽ��)���� ����
#define T_FC_CHARACTER_GET_OTHER_RENDER_INFO	(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_GET_OTHER_RENDER_INFO)
#define T_FC_CHARACTER_GET_OTHER_RENDER_INFO_OK	(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_GET_OTHER_RENDER_INFO_OK)
#define T_FC_CHARACTER_CHANGE_BODYCONDITION_ALL	(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_CHANGE_BODYCONDITION_ALL)	// C->F, ������ BodyCondition ���� ��û
#define T_FC_CHARACTER_CHANGE_PROPENSITY			(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_CHANGE_PROPENSITY)		// F->C, // 2005-08-22 by cmkwon, ������
#define T_FC_CHARACTER_SHOW_EFFECT					(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_SHOW_EFFECT)			// C->F, ������ �ڽ��� ����Ʈ ���� ��û
#define T_FC_CHARACTER_SHOW_EFFECT_OK				(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_SHOW_EFFECT_OK)		// F->C, ������ ĳ���鿡�� ����
#define T_FC_CHARACTER_GET_OTHER_PARAMFACTOR		(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_GET_OTHER_PARAMFACTOR)		// C->F, �ش� ĳ������ ParamFactor ���� ��û
#define T_FC_CHARACTER_GET_OTHER_PARAMFACTOR_OK		(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_GET_OTHER_PARAMFACTOR_OK)	// F->C, �ش� ĳ������ ParamFactor ���� ��û ���
#define T_FC_CHARACTER_SEND_PARAMFACTOR_IN_RANGE	(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_SEND_PARAMFACTOR_IN_RANGE)		// C->F, �ڽ��� ParamFactor�� ������ �������� ��û
//#define T_FC_CHARACTER_GET_OTHER_SKILL_INFO		(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_GET_OTHER_SKILL_INFO)		// C->F
//#define T_FC_CHARACTER_GET_OTHER_SKILL_INFO_OK	(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_GET_OTHER_SKILL_INFO_OK)	// F->C
#define T_FC_CHARACTER_SPEED_HACK_USER				(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_SPEED_HACK_USER)			// C->F
#define T_FC_CHARACTER_CHANGE_CHARACTER_MENT		(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_CHANGE_CHARACTER_MENT)		// F->C(n)
#define T_FC_CHARACTER_GET_CASH_MONEY_COUNT			(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_GET_CASH_MONEY_COUNT)		// C->F
#define T_FC_CHARACTER_GET_CASH_MONEY_COUNT_OK		(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_GET_CASH_MONEY_COUNT_OK)	// F->C
#define T_FC_CHARACTER_CASH_PREMIUM_CARD_INFO		(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_CASH_PREMIUM_CARD_INFO)	// F->C
#define T_FC_CHARACTER_TUTORIAL_SKIP				(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_TUTORIAL_SKIP)	// C->F
#define T_FC_CHARACTER_TUTORIAL_SKIP_OK				(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_TUTORIAL_SKIP_OK)	// F->C
#define T_FC_CHARACTER_CHANGE_CHARACTER_MODE		(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_CHANGE_CHARACTER_MODE)		// C->F
#define T_FC_CHARACTER_CHANGE_CHARACTER_MODE_OK		(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_CHANGE_CHARACTER_MODE_OK)	// F->C(n)
#define T_FC_CHARACTER_FALLING_BY_FUEL_ALLIN		(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_FALLING_BY_FUEL_ALLIN)					// C->F
#define T_FC_CHARACTER_WARP_BY_AGEAR_LANDING_FUEL_ALLIN	(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_WARP_BY_AGEAR_LANDING_FUEL_ALLIN)	// C->F
#define T_FC_CHARACTER_GET_REAL_WEAPON_INFO			(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_GET_REAL_WEAPON_INFO)	// F->C// 2005-12-21 by cmkwon
#define T_FC_CHARACTER_GET_REAL_WEAPON_INFO_OK		(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_GET_REAL_WEAPON_INFO_OK)	// C->F// 2005-12-21 by cmkwon
#define T_FC_CHARACTER_GET_REAL_ENGINE_INFO			(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_GET_REAL_ENGINE_INFO)		// F->C// 2005-12-21 by cmkwon
#define T_FC_CHARACTER_GET_REAL_ENGINE_INFO_OK		(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_GET_REAL_ENGINE_INFO_OK)	// C->F// 2005-12-21 by cmkwon
#define T_FC_CHARACTER_GET_REAL_TOTAL_WEIGHT		(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_GET_REAL_TOTAL_WEIGHT)		// F->C// 2005-12-21 by cmkwon
#define T_FC_CHARACTER_GET_REAL_TOTAL_WEIGHT_OK		(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_GET_REAL_TOTAL_WEIGHT_OK)	// C->F// 2005-12-21 by cmkwon
#define T_FC_CHARACTER_MEMORY_HACK_USER				(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_MEMORY_HACK_USER)			// C->F// 2005-12-21 by cmkwon
#define T_FC_CHARACTER_UPDATE_SUBLEADER				(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_UPDATE_SUBLEADER)			// C->F// 2007-02-14 by dhjin
#define T_FC_CHARACTER_UPDATE_SUBLEADER_OK			(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_UPDATE_SUBLEADER_OK)		// F->C, 2007-10-06 by dhjin
#define T_FC_CHARACTER_OBSERVER_START				(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_OBSERVER_START)			// C->F, 2007-03-27 by dhjin
#define T_FC_CHARACTER_OBSERVER_START_OK			(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_OBSERVER_START_OK)			// F->C, 2007-03-27 by dhjin
#define T_FC_CHARACTER_OBSERVER_END					(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_OBSERVER_END)				// C->F, 2007-03-27 by dhjin
#define T_FC_CHARACTER_OBSERVER_END_OK				(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_OBSERVER_END_OK)			// F->C, 2007-03-27 by dhjin
#define T_FC_CHARACTER_OBSERVER_INFO				(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_OBSERVER_INFO)			// F->C, 2007-03-27 by dhjin
#define T_FC_CHARACTER_OBSERVER_REG					(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_OBSERVER_REG)			// F->C, 2007-03-27 by dhjin
#define T_FC_CHARACTER_SHOW_MAP_EFFECT				(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_SHOW_MAP_EFFECT)			// C->F, // 2007-04-20 by cmkwon
#define T_FC_CHARACTER_SHOW_MAP_EFFECT_OK			(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_SHOW_MAP_EFFECT_OK)		// F->C(n), // 2007-04-20 by cmkwon
#define T_FC_CHARACTER_PAY_WARPOINT					(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_PAY_WARPOINT)			// F->C(n), // 2007-04-20 by cmkwon
#define T_FC_CHARACTER_WATCH_INFO					(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_WATCH_INFO)			// F->C, 2007-03-27 by dhjin
// 2008-01-10 by dhjin,  �Ʒ��� ���� - �Ʒ��� ���� �� �ٽ� �ʵ� ���� ���� ����
#define T_FC_CHARACTER_READY_GAMESTART_FROM_ARENA_TO_MAINSERVER 	(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_READY_GAMESTART_FROM_ARENA_TO_MAINSERVER)			// C->F, // 2008-01-31 by dhjin
#define T_FC_CHARACTER_READY_GAMESTART_FROM_ARENA_TO_MAINSERVER_OK 	(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_READY_GAMESTART_FROM_ARENA_TO_MAINSERVER_OK)			// F->C, // 2008-01-31 by dhjin
#define T_FC_CHARACTER_GAMESTART_FROM_ARENA_TO_MAINSERVER 			(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_GAMESTART_FROM_ARENA_TO_MAINSERVER)			// C->F, // 2008-01-10 by dhjin
#define T_FC_CHARACTER_GET_USER_INFO				(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_GET_USER_INFO)					// C->F, // 2008-06-23 by dhjin, EP3 ���������ɼ� -
#define T_FC_CHARACTER_GET_USER_INFO_OK				(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_GET_USER_INFO_OK)				// F->C, // 2008-06-23 by dhjin, EP3 ���������ɼ� -
// 2012-06-05 by jhseol, ���۹̸����� - Ŭ���û ��Ŷ �߰�
#define T_FC_CHARACTER_GET_USER_ITEM_INFO					(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_GET_USER_ITEM_INFO)			// C->F
#define T_FC_CHARACTER_GET_USER_ITEM_INFO_OK				(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_GET_USER_ITEM_INFO_OK)			// F->C
#define T_FC_CHARACTER_GET_USER_ITEM_INFO_OK_DONE			(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_GET_USER_ITEM_INFO_OK_DONE)	// F->C
#define T_FC_CHARACTER_GET_USER_ITEM_INFO_SECRET			(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_GET_USER_ITEM_INFO_SECRET)				// C->F	// 2012-07-12 by isshin ���۹̸����� On / Off ��� - ���� ����
#define T_FC_CHARACTER_GET_USER_ITEM_INFO_SECRET_OK			(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_GET_USER_ITEM_INFO_SECRET_OK)			// F->C	// 2012-07-12 by isshin ���۹̸����� On / Off ��� - ���� ����
// end 2012-06-05 by jhseol, ���۹̸����� - Ŭ���û ��Ŷ �߰�
#define T_FC_CHARACTER_CHANGE_INFO_OPTION_SECRET	(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_CHANGE_INFO_OPTION_SECRET)		// C->F, // 2008-06-23 by dhjin, EP3 ���������ɼ� -
#define T_FC_CHARACTER_CHANGE_INFO_OPTION_SECRET_OK	(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_CHANGE_INFO_OPTION_SECRET_OK)	// F->C, // 2008-06-23 by dhjin, EP3 ���������ɼ� -
#define T_FC_CHARACTER_CHANGE_NICKNAME				(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_CHANGE_NICKNAME)		// C->F, // 2009-02-12 by cmkwon, EP3-3 ���巩ŷ�ý��� ���� - 
#define T_FC_CHARACTER_CHANGE_NICKNAME_OK			(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_CHANGE_NICKNAME_OK)	// F->C, // 2009-02-12 by cmkwon, EP3-3 ���巩ŷ�ý��� ���� - 
#define T_FC_CHARACTER_CHANGE_START_CITY_MAPINDEX		(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_CHANGE_START_CITY_MAPINDEX)	// C->F, // 2009-10-12 by cmkwon, ������ī ���� ��� ���� - 
#define T_FC_CHARACTER_CHANGE_START_CITY_MAPINDEX_OK	(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_CHANGE_START_CITY_MAPINDEX_OK)	// F->C, // 2009-10-12 by cmkwon, ������ī ���� ��� ���� - 
#define T_FC_CHARACTER_CHANGE_ADDED_INVENTORY_COUNT		(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_CHANGE_ADDED_INVENTORY_COUNT)	// F->C, // 2009-11-02 by cmkwon, ĳ��(�κ�/â�� Ȯ��) ������ �߰� ���� - 

// 2012-10-10 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������
#define T_FC_CHARACTER_KILLCOUNT							(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_KILLCOUNT)
#define T_FC_CHARACTER_RESTCOUNT							(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_RESTCOUNT)
#define T_FC_CHARACTER_BONUS_EXP_RATE						(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_BONUS_EXP_RATE)
// end 2012-10-10 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������

#define T_FC_BUGTRAP_ACCEPT									(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_BUGTRAP_ACCEPT)		// 2014-01-27 by bckim, ���� Ʈ��

#define T_FC_CHARACTER_PAY_CONTRIBUTIONPOINT		(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_PAY_CONTRIBUTIONPOINT)		// F->C, // 2013-08-14 by jhseol, ������ ������ - ��������Ʈ ���� ����

#define T_FN_CHARACTER_CHANGE_UNITKIND			(MessageType_t)((T0_FN_CHARACTER<<8)|T1_FN_CHARACTER_CHANGE_UNITKIND)
#define T_FN_CHARACTER_CHANGE_BODYCONDITION		(MessageType_t)((T0_FN_CHARACTER<<8)|T1_FN_CHARACTER_CHANGE_BODYCONDITION)
#define T_FN_CHARACTER_CHANGE_HPDPSPEP			(MessageType_t)((T0_FN_CHARACTER<<8)|T1_FN_CHARACTER_CHANGE_HPDPSPEP)
#define T_FN_CHARACTER_CHANGE_CURRENTHPDPSPEP	(MessageType_t)((T0_FN_CHARACTER<<8)|T1_FN_CHARACTER_CHANGE_CURRENTHPDPSPEP)
#define T_FN_CHARACTER_CHANGE_MAPNAME			(MessageType_t)((T0_FN_CHARACTER<<8)|T1_FN_CHARACTER_CHANGE_MAPNAME)
#define T_FN_CHARACTER_CHANGE_POSITION			(MessageType_t)((T0_FN_CHARACTER<<8)|T1_FN_CHARACTER_CHANGE_POSITION)
#define T_FN_CHARACTER_CHANGE_STEALTHSTATE		(MessageType_t)((T0_FN_CHARACTER<<8)|T1_FN_CHARACTER_CHANGE_STEALTHSTATE)
#define T_FN_CHARACTER_CHANGE_CHARACTER_MODE_OK	(MessageType_t)((T0_FN_CHARACTER<<8)|T1_FN_CHARACTER_CHANGE_CHARACTER_MODE_OK)
#define T_FN_CHARACTER_CHANGE_INFLUENCE_TYPE	(MessageType_t)((T0_FN_CHARACTER<<8)|T1_FN_CHARACTER_CHANGE_INFLUENCE_TYPE)		// F->I, 2005-12-03 by cmkwon
#define T_FN_CHARACTER_CHANGE_INVISIBLE			(MessageType_t)((T0_FN_CHARACTER<<8)|T1_FN_CHARACTER_CHANGE_INVISIBLE)			// F->N, 2006-11-27 by dhjin

#define T_FC_MOVE								(MessageType_t)((T0_FC_MOVE<<8)|T1_FC_MOVE)
#define T_FC_MOVE_OK							(MessageType_t)((T0_FC_MOVE<<8)|T1_FC_MOVE_OK)
#define T_FC_MOVE_LOCKON						(MessageType_t)((T0_FC_MOVE<<8)|T1_FC_MOVE_LOCKON)
#define T_FC_MOVE_LOCKON_OK						(MessageType_t)((T0_FC_MOVE<<8)|T1_FC_MOVE_LOCKON_OK)
#define T_FC_MOVE_UNLOCKON						(MessageType_t)((T0_FC_MOVE<<8)|T1_FC_MOVE_UNLOCKON)
#define T_FC_MOVE_UNLOCKON_OK					(MessageType_t)((T0_FC_MOVE<<8)|T1_FC_MOVE_UNLOCKON_OK)
#define T_FC_MOVE_LANDING						(MessageType_t)((T0_FC_MOVE<<8)|T1_FC_MOVE_LANDING)
#define T_FC_MOVE_LANDING_OK					(MessageType_t)((T0_FC_MOVE<<8)|T1_FC_MOVE_LANDING_OK)
#define T_FC_MOVE_LANDING_DONE					(MessageType_t)((T0_FC_MOVE<<8)|T1_FC_MOVE_LANDING_DONE)	// C->F, ���� �ϷḦ �˸�
#define T_FC_MOVE_TAKEOFF						(MessageType_t)((T0_FC_MOVE<<8)|T1_FC_MOVE_TAKEOFF)
#define T_FC_MOVE_TAKEOFF_OK					(MessageType_t)((T0_FC_MOVE<<8)|T1_FC_MOVE_TAKEOFF_OK)
#define T_FC_MISSILE_MOVE_OK					(MessageType_t)((T0_FC_MOVE<<8)|T1_FC_MISSILE_MOVE_OK)
#define T_FC_MOVE_TARGET						(MessageType_t)((T0_FC_MOVE<<8)|T1_FC_MOVE_TARGET)
#define T_FC_MOVE_WEAPON_VEL					(MessageType_t)((T0_FC_MOVE<<8)|T1_FC_MOVE_WEAPON_VEL)		// C->F, ������ ������ ������ ����
#define T_FC_MOVE_WEAPON_VEL_OK					(MessageType_t)((T0_FC_MOVE<<8)|T1_FC_MOVE_WEAPON_VEL_OK)	// F->C_in_range, ������ ������ ������ ����
#define T_FC_MOVE_ROLLING						(MessageType_t)((T0_FC_MOVE<<8)|T1_FC_MOVE_ROLLING)			// F->C, �Ѹ� ��� ��û
#define T_FC_MOVE_ROLLING_OK					(MessageType_t)((T0_FC_MOVE<<8)|T1_FC_MOVE_ROLLING_OK)		// F->C, �Ѹ� ��� �㰡

#define T_FC_MOVE_HACKSHIELD_GuidReqMsg			(MessageType_t)((T0_FC_MOVE<<8)|T1_FC_MOVE_HACKSHIELD_GuidReqMsg)	// F->C, 2006-06-05 by cmkwon, Anlab - HackShield
#define T_FC_MOVE_HACKSHIELD_GuidAckMsg			(MessageType_t)((T0_FC_MOVE<<8)|T1_FC_MOVE_HACKSHIELD_GuidAckMsg)	// C->F, 2006-06-05 by cmkwon, Anlab - HackShield
#define T_FC_MOVE_HACKSHIELD_CRCReqMsg			(MessageType_t)((T0_FC_MOVE<<8)|T1_FC_MOVE_HACKSHIELD_CRCReqMsg)	// F->C, 2006-06-05 by cmkwon, Anlab - HackShield
#define T_FC_MOVE_HACKSHIELD_CRCAckMsg			(MessageType_t)((T0_FC_MOVE<<8)|T1_FC_MOVE_HACKSHIELD_CRCAckMsg)	// C->F, 2006-06-05 by cmkwon, Anlab - HackShield
#define T_FC_MOVE_HACKSHIELD_HACKING_CLIENT		(MessageType_t)((T0_FC_MOVE<<8)|T1_FC_MOVE_HACKSHIELD_HACKING_CLIENT)	// 2006-06-05 by cmkwon, Anlab - HackShield
#define T_FC_MOVE_XIGNCODE_REQ_SCAN_INIT		(MessageType_t)((T0_FC_MOVE<<8)|T1_FC_MOVE_XIGNCODE_REQ_SCAN_INIT)		// 2008-11-28 by cmkwon, �븸 Netpower_Tpe XignCode(���Ӱ���) ���� - S->C(1)
#define T_FC_MOVE_XIGNCODE_REQ_SCAN_INIT_OK		(MessageType_t)((T0_FC_MOVE<<8)|T1_FC_MOVE_XIGNCODE_REQ_SCAN_INIT_OK)	// 2008-11-28 by cmkwon, �븸 Netpower_Tpe XignCode(���Ӱ���) ���� - C->S
#define T_FC_MOVE_XIGNCODE_REQ_SCAN_CHECK		(MessageType_t)((T0_FC_MOVE<<8)|T1_FC_MOVE_XIGNCODE_REQ_SCAN_CHECK)		// 2008-11-28 by cmkwon, �븸 Netpower_Tpe XignCode(���Ӱ���) ���� - S->C(1)
#define T_FC_MOVE_XIGNCODE_REQ_SCAN_CHECK_OK	(MessageType_t)((T0_FC_MOVE<<8)|T1_FC_MOVE_XIGNCODE_REQ_SCAN_CHECK_OK)	// 2008-11-28 by cmkwon, �븸 Netpower_Tpe XignCode(���Ӱ���) ���� - C->S
#define T_FC_MOVE_NPROTECT_REQ_AUTH_DATA		(MessageType_t)((T0_FC_MOVE<<8)|T1_FC_MOVE_NPROTECT_REQ_AUTH_DATA)		// 2009-03-09 by cmkwon, �Ϻ� Arario nProtect�� CS���� �����ϱ� - S->C(1)
#define T_FC_MOVE_NPROTECT_REQ_AUTH_DATA_OK		(MessageType_t)((T0_FC_MOVE<<8)|T1_FC_MOVE_NPROTECT_REQ_AUTH_DATA_OK)	// 2009-03-09 by cmkwon, �Ϻ� Arario nProtect�� CS���� �����ϱ� - C->S
#define T_FC_MOVE_NPROTECT_NEW_REQ_AUTH_DATA	(MessageType_t)((T0_FC_MOVE<<8)|T1_FC_MOVE_NPROTECT_NEW_REQ_AUTH_DATA)		// 2015-01-07 by jwLee �������� nProtector ���� S->C
#define T_FC_MOVE_NPROTECT_NEW_REQ_AUTH_DATA_OK	(MessageType_t)((T0_FC_MOVE<<8)|T1_FC_MOVE_NPROTECT_NEW_REQ_AUTH_DATA_OK)	// 2015-01-07 by jwLee �������� nProtector ���� C->S
#define T_FC_MOVE_XTRAP_REQ_STEP				(MessageType_t)((T0_FC_MOVE<<8)|T1_FC_MOVE_XTRAP_REQ_STEP)			// 2009-10-06 by cmkwon, ��Ʈ�� ���� ���� X-TRAP���� ���� - S->C(1)
#define T_FC_MOVE_XTRAP_REQ_STEP_OK				(MessageType_t)((T0_FC_MOVE<<8)|T1_FC_MOVE_XTRAP_REQ_STEP_OK)		// 2009-10-06 by cmkwon, ��Ʈ�� ���� ���� X-TRAP���� ���� - C(1)->S
#define T_FC_MOVE_APEX_REQ_APEXDATA				(MessageType_t)((T0_FC_MOVE<<8)|T1_FC_MOVE_APEX_REQ_APEXDATA)		// 2009-11-04 by cmkwon, �±� ���Ӱ��� Apex�� ���� - S->C(1)
#define T_FC_MOVE_APEX_REQ_APEXDATA_OK			(MessageType_t)((T0_FC_MOVE<<8)|T1_FC_MOVE_APEX_REQ_APEXDATA_OK)	// 2009-11-04 by cmkwon, �±� ���Ӱ��� Apex�� ���� - C(1)->S

#define T_FN_MONSTER_MOVE						(MessageType_t)((T0_FN_MOVE<<8)|T1_FN_MONSTER_MOVE)
#define T_FN_MOVE_OK							(MessageType_t)((T0_FN_MOVE<<8)|T1_FN_MOVE_OK)
#define T_FN_MOVE_LOCKON						(MessageType_t)((T0_FN_MOVE<<8)|T1_FN_MOVE_LOCKON)
#define T_FN_MOVE_LOCKON_OK						(MessageType_t)((T0_FN_MOVE<<8)|T1_FN_MOVE_LOCKON_OK)
#define T_FN_MOVE_LOCKON_AVOID					(MessageType_t)((T0_FN_MOVE<<8)|T1_FN_MOVE_LOCKON_AVOID)
#define T_FN_MOVE_LOCKON_AVOID_OK				(MessageType_t)((T0_FN_MOVE<<8)|T1_FN_MOVE_LOCKON_AVOID_OK)
#define T_FN_MISSILE_MOVE						(MessageType_t)((T0_FN_MOVE<<8)|T1_FN_MISSILE_MOVE)
#define T_FN_MONSTER_HPRECOVERY					(MessageType_t)((T0_FN_MOVE<<8)|T1_FN_MONSTER_HPRECOVERY)
#define T_FN_MONSTER_HIDE						(MessageType_t)((T0_FN_MOVE<<8)|T1_FN_MONSTER_HIDE)
#define T_FN_MONSTER_SHOW						(MessageType_t)((T0_FN_MOVE<<8)|T1_FN_MONSTER_SHOW)

#define T_FC_BATTLE_ATTACK						(MessageType_t)((T0_FC_BATTLE<<8)|T1_FC_BATTLE_ATTACK)						// C->F
#define T_FC_BATTLE_ATTACK_OK					(MessageType_t)((T0_FC_BATTLE<<8)|T1_FC_BATTLE_ATTACK_OK)					// F->C_in_range
#define T_FC_BATTLE_ATTACK_FIND					(MessageType_t)((T0_FC_BATTLE<<8)|T1_FC_BATTLE_ATTACK_FIND)					// C->F
#define T_FC_BATTLE_ATTACK_FIND_OK				(MessageType_t)((T0_FC_BATTLE<<8)|T1_FC_BATTLE_ATTACK_FIND_OK)				// F->C_in_range
#define T_FC_BATTLE_DROP_MINE					(MessageType_t)((T0_FC_BATTLE<<8)|T1_FC_BATTLE_DROP_MINE)					// C->F
#define T_FC_BATTLE_DROP_MINE_OK				(MessageType_t)((T0_FC_BATTLE<<8)|T1_FC_BATTLE_DROP_MINE_OK)				// F->C_in_range, ������ �����ֱ�
#define T_FC_BATTLE_MINE_ATTACK					(MessageType_t)((T0_FC_BATTLE<<8)|T1_FC_BATTLE_MINE_ATTACK)					// C->F
#define T_FC_BATTLE_MINE_ATTACK_OK				(MessageType_t)((T0_FC_BATTLE<<8)|T1_FC_BATTLE_MINE_ATTACK_OK)				// F->C_in_range
#define T_FC_BATTLE_MINE_ATTACK_FIND			(MessageType_t)((T0_FC_BATTLE<<8)|T1_FC_BATTLE_MINE_ATTACK_FIND)			// C->F
#define T_FC_BATTLE_MINE_ATTACK_FIND_OK			(MessageType_t)((T0_FC_BATTLE<<8)|T1_FC_BATTLE_MINE_ATTACK_FIND_OK)			// F->C_in_range
#define T_FC_BATTLE_REQUEST_PK					(MessageType_t)((T0_FC_BATTLE<<8)|T1_FC_BATTLE_REQUEST_PK)					// C->F, client�� PK ��û
#define T_FC_BATTLE_REQUEST_PK_OK				(MessageType_t)((T0_FC_BATTLE<<8)|T1_FC_BATTLE_REQUEST_PK_OK)				// F->C, PK ��û �³�
#define T_FC_BATTLE_CANCEL_PK					(MessageType_t)((T0_FC_BATTLE<<8)|T1_FC_BATTLE_CANCEL_PK)					// F->C, PK ����
#define T_FC_BATTLE_REQUEST_P2P_PK				(MessageType_t)((T0_FC_BATTLE<<8)|T1_FC_BATTLE_REQUEST_P2P_PK)				// C->F, �ϴ��� PK ��û
#define T_FC_BATTLE_REQUEST_P2P_PK_OK			(MessageType_t)((T0_FC_BATTLE<<8)|T1_FC_BATTLE_REQUEST_P2P_PK_OK)			// F->C, �ϴ��� PK ��û
#define T_FC_BATTLE_ACCEPT_REQUEST_P2P_PK		(MessageType_t)((T0_FC_BATTLE<<8)|T1_FC_BATTLE_ACCEPT_REQUEST_P2P_PK)		// C->F, �ϴ��� PK �³�
#define T_FC_BATTLE_ACCEPT_REQUEST_P2P_PK_OK	(MessageType_t)((T0_FC_BATTLE<<8)|T1_FC_BATTLE_ACCEPT_REQUEST_P2P_PK_OK)	// F->C, �ϴ��� PK �³�
#define T_FC_BATTLE_REJECT_REQUEST_P2P_PK		(MessageType_t)((T0_FC_BATTLE<<8)|T1_FC_BATTLE_REJECT_REQUEST_P2P_PK)		// C->F, �ϴ��� PK ����
#define T_FC_BATTLE_REJECT_REQUEST_P2P_PK_OK	(MessageType_t)((T0_FC_BATTLE<<8)|T1_FC_BATTLE_REJECT_REQUEST_P2P_PK_OK)	// F->C, �ϴ��� PK ����
#define T_FC_BATTLE_SURRENDER_P2P_PK			(MessageType_t)((T0_FC_BATTLE<<8)|T1_FC_BATTLE_SURRENDER_P2P_PK)			// C->F, �ϴ��� PK �׺�
#define T_FC_BATTLE_SURRENDER_P2P_PK_OK			(MessageType_t)((T0_FC_BATTLE<<8)|T1_FC_BATTLE_SURRENDER_P2P_PK_OK)			// F->C, �ϴ��� PK �׺�
#define T_FC_BATTLE_ACCEPT_SURRENDER_P2P_PK		(MessageType_t)((T0_FC_BATTLE<<8)|T1_FC_BATTLE_ACCEPT_SURRENDER_P2P_PK)		// C->F, �ϴ��� PK �׺� �³�
#define T_FC_BATTLE_REJECT_SURRENDER_P2P_PK		(MessageType_t)((T0_FC_BATTLE<<8)|T1_FC_BATTLE_REJECT_SURRENDER_P2P_PK)		// C->F, �ϴ��� PK �׺� ����
#define T_FC_BATTLE_REJECT_SURRENDER_P2P_PK_OK	(MessageType_t)((T0_FC_BATTLE<<8)|T1_FC_BATTLE_REJECT_SURRENDER_P2P_PK_OK)	// F->C, �ϴ��� PK �׺� ����
#define T_FC_BATTLE_END_P2P_PK					(MessageType_t)((T0_FC_BATTLE<<8)|T1_FC_BATTLE_END_P2P_PK)					// F->C, PK ����
#define T_FC_BATTLE_ATTACK_EXPLODE_ITEM			(MessageType_t)((T0_FC_BATTLE<<8)|T1_FC_BATTLE_ATTACK_EXPLODE_ITEM)
#define T_FC_BATTLE_ATTACK_HIDE_ITEM			(MessageType_t)((T0_FC_BATTLE<<8)|T1_FC_BATTLE_ATTACK_HIDE_ITEM)
#define T_FC_BATTLE_ATTACK_EXPLODE_ITEM_W_KIND	(MessageType_t)((T0_FC_BATTLE<<8)|T1_FC_BATTLE_ATTACK_EXPLODE_ITEM_W_KIND)
#define T_FC_BATTLE_ATTACK_HIDE_ITEM_W_KIND		(MessageType_t)((T0_FC_BATTLE<<8)|T1_FC_BATTLE_ATTACK_HIDE_ITEM_W_KIND)
#define T_FC_BATTLE_TOGGLE_SHIELD				(MessageType_t)((T0_FC_BATTLE<<8)|T1_FC_BATTLE_TOGGLE_SHIELD)				// No Body
#define T_FC_BATTLE_TOGGLE_SHIELD_RESULT		(MessageType_t)((T0_FC_BATTLE<<8)|T1_FC_BATTLE_TOGGLE_SHIELD_RESULT)
#define T_FC_BATTLE_DROP_DUMMY					(MessageType_t)((T0_FC_BATTLE<<8)|T1_FC_BATTLE_DROP_DUMMY)
#define T_FC_BATTLE_DROP_DUMMY_OK				(MessageType_t)((T0_FC_BATTLE<<8)|T1_FC_BATTLE_DROP_DUMMY_OK)
#define T_FC_BATTLE_DROP_FIXER					(MessageType_t)((T0_FC_BATTLE<<8)|T1_FC_BATTLE_DROP_FIXER)
#define T_FC_BATTLE_DROP_FIXER_OK				(MessageType_t)((T0_FC_BATTLE<<8)|T1_FC_BATTLE_DROP_FIXER_OK)
#define T_FC_BATTLE_PRI_BULLET_RELOADED			(MessageType_t)((T0_FC_BATTLE<<8)|T1_FC_BATTLE_PRI_BULLET_RELOADED)	// 1�� ������ ź���� ���ε�Ǿ���
#define T_FC_BATTLE_SEC_BULLET_RELOADED			(MessageType_t)((T0_FC_BATTLE<<8)|T1_FC_BATTLE_SEC_BULLET_RELOADED)	// 2�� ������ ź���� ���ε�Ǿ���
#define T_FC_BATTLE_SHIELD_DAMAGE				(MessageType_t)((T0_FC_BATTLE<<8)|T1_FC_BATTLE_SHIELD_DAMAGE)
#define T_FC_BATTLE_TOGGLE_DECOY				(MessageType_t)((T0_FC_BATTLE<<8)|T1_FC_BATTLE_TOGGLE_DECOY)		// C->F, No Body
#define T_FC_BATTLE_TOGGLE_DECOY_OK				(MessageType_t)((T0_FC_BATTLE<<8)|T1_FC_BATTLE_TOGGLE_DECOY_OK)		// F->C
#define T_FC_BATTLE_SHOW_DAMAGE					(MessageType_t)((T0_FC_BATTLE<<8)|T1_FC_BATTLE_SHOW_DAMAGE)			// F->C, ���� �������� ǥ����
#define T_FC_BATTLE_ATTACK_EVASION				(MessageType_t)((T0_FC_BATTLE<<8)|T1_FC_BATTLE_ATTACK_EVASION)	// C->F, // 2005-12-12 by cmkwon
#define T_FC_BATTLE_ATTACK_EVASION_OK			(MessageType_t)((T0_FC_BATTLE<<8)|T1_FC_BATTLE_ATTACK_EVASION_OK)	// F->C(1), // 2005-12-12 by cmkwon
#define T_FC_BATTLE_DELETE_DUMMY_OK				(MessageType_t)((T0_FC_BATTLE<<8)|T1_FC_BATTLE_DELETE_DUMMY_OK)		// 2006-12-04 by dhjin, F->C(n)
#define T_FC_BATTLE_EXPLODE_DUMMY_OK			(MessageType_t)((T0_FC_BATTLE<<8)|T1_FC_BATTLE_EXPLODE_DUMMY_OK)	// 2006-12-04 by dhjin, F->C(n)


#define T_FN_BATTLE_ATTACK_PRIMARY				(MessageType_t)((T0_FN_BATTLE<<8)|T1_FN_BATTLE_ATTACK_PRIMARY)
#define T_FN_BATTLE_ATTACK_RESULT_PRIMARY		(MessageType_t)((T0_FN_BATTLE<<8)|T1_FN_BATTLE_ATTACK_RESULT_PRIMARY)
#define T_FN_BATTLE_ATTACK_SECONDARY			(MessageType_t)((T0_FN_BATTLE<<8)|T1_FN_BATTLE_ATTACK_SECONDARY)
#define T_FN_BATTLE_ATTACK_RESULT_SECONDARY		(MessageType_t)((T0_FN_BATTLE<<8)|T1_FN_BATTLE_ATTACK_RESULT_SECONDARY)
#define T_FN_BATTLE_ATTACK_FIND					(MessageType_t)((T0_FN_BATTLE<<8)|T1_FN_BATTLE_ATTACK_FIND)
#define T_FN_BATTLE_ATTACK_FIND_RESULT			(MessageType_t)((T0_FN_BATTLE<<8)|T1_FN_BATTLE_ATTACK_FIND_RESULT)
#define T_FN_BATTLE_SET_ATTACK_CHARACTER		(MessageType_t)((T0_FN_BATTLE<<8)|T1_FN_BATTLE_SET_ATTACK_CHARACTER)
#define T_FN_BATTLE_DROP_FIXER					(MessageType_t)((T0_FN_BATTLE<<8)|T1_FN_BATTLE_DROP_FIXER)					// F -> N
#define T_FN_BATTLE_DROP_FIXER_OK				(MessageType_t)((T0_FN_BATTLE<<8)|T1_FN_BATTLE_DROP_FIXER_OK)				// N -> F
#define T_FN_BATTLE_ATTACK_HIDE_ITEM_W_KIND		(MessageType_t)((T0_FN_BATTLE<<8)|T1_FN_BATTLE_ATTACK_HIDE_ITEM_W_KIND)

#define T_FC_PARTY_CREATE_OK						(MessageType_t)((T0_FC_PARTY<<8)|T1_FC_PARTY_CREATE_OK)
#define T_FC_PARTY_REQUEST_INVITE					(MessageType_t)((T0_FC_PARTY<<8)|T1_FC_PARTY_REQUEST_INVITE)
#define T_FC_PARTY_REQUEST_INVITE_QUESTION			(MessageType_t)((T0_FC_PARTY<<8)|T1_FC_PARTY_REQUEST_INVITE_QUESTION)
#define T_FC_PARTY_ACCEPT_INVITE					(MessageType_t)((T0_FC_PARTY<<8)|T1_FC_PARTY_ACCEPT_INVITE)
#define T_FC_PARTY_REJECT_INVITE					(MessageType_t)((T0_FC_PARTY<<8)|T1_FC_PARTY_REJECT_INVITE)
#define T_FC_PARTY_REJECT_INVITE_OK					(MessageType_t)((T0_FC_PARTY<<8)|T1_FC_PARTY_REJECT_INVITE_OK)
#define T_FC_PARTY_GET_MEMBER						(MessageType_t)((T0_FC_PARTY<<8)|T1_FC_PARTY_GET_MEMBER)
#define T_FC_PARTY_PUT_MEMBER						(MessageType_t)((T0_FC_PARTY<<8)|T1_FC_PARTY_PUT_MEMBER)
#define T_FC_PARTY_GET_ALL_MEMBER					(MessageType_t)((T0_FC_PARTY<<8)|T1_FC_PARTY_GET_ALL_MEMBER)
#define T_FC_PARTY_PUT_ALL_MEMBER					(MessageType_t)((T0_FC_PARTY<<8)|T1_FC_PARTY_PUT_ALL_MEMBER)
#define T_FC_PARTY_UPDATE_MEMBER_INFO_ALL			(MessageType_t)((T0_FC_PARTY<<8)|T1_FC_PARTY_UPDATE_MEMBER_INFO_ALL)
#define T_FC_PARTY_UPDATE_MEMBER_INFO_LEVEL			(MessageType_t)((T0_FC_PARTY<<8)|T1_FC_PARTY_UPDATE_MEMBER_INFO_LEVEL)
#define T_FC_PARTY_UPDATE_MEMBER_INFO_HP			(MessageType_t)((T0_FC_PARTY<<8)|T1_FC_PARTY_UPDATE_MEMBER_INFO_HP)
#define T_FC_PARTY_UPDATE_MEMBER_INFO_CURRENT_HP	(MessageType_t)((T0_FC_PARTY<<8)|T1_FC_PARTY_UPDATE_MEMBER_INFO_CURRENT_HP)
#define T_FC_PARTY_UPDATE_MEMBER_INFO_DP			(MessageType_t)((T0_FC_PARTY<<8)|T1_FC_PARTY_UPDATE_MEMBER_INFO_DP)
#define T_FC_PARTY_UPDATE_MEMBER_INFO_CURRENT_DP	(MessageType_t)((T0_FC_PARTY<<8)|T1_FC_PARTY_UPDATE_MEMBER_INFO_CURRENT_DP)
#define T_FC_PARTY_UPDATE_MEMBER_INFO_SP			(MessageType_t)((T0_FC_PARTY<<8)|T1_FC_PARTY_UPDATE_MEMBER_INFO_SP)
#define T_FC_PARTY_UPDATE_MEMBER_INFO_CURRENT_SP	(MessageType_t)((T0_FC_PARTY<<8)|T1_FC_PARTY_UPDATE_MEMBER_INFO_CURRENT_SP)
#define T_FC_PARTY_UPDATE_MEMBER_INFO_EP			(MessageType_t)((T0_FC_PARTY<<8)|T1_FC_PARTY_UPDATE_MEMBER_INFO_EP)
#define T_FC_PARTY_UPDATE_MEMBER_INFO_CURRENT_EP	(MessageType_t)((T0_FC_PARTY<<8)|T1_FC_PARTY_UPDATE_MEMBER_INFO_CURRENT_EP)
#define T_FC_PARTY_UPDATE_MEMBER_INFO_BODYCONDITION	(MessageType_t)((T0_FC_PARTY<<8)|T1_FC_PARTY_UPDATE_MEMBER_INFO_BODYCONDITION)
#define T_FC_PARTY_REQUEST_PARTY_WARP				(MessageType_t)((T0_FC_PARTY<<8)|T1_FC_PARTY_REQUEST_PARTY_WARP)
#define T_FC_PARTY_REQUEST_PARTY_WARP_WITH_MAP_NAME	(MessageType_t)((T0_FC_PARTY<<8)|T1_FC_PARTY_REQUEST_PARTY_WARP_WITH_MAP_NAME)
#define T_FC_PARTY_REQUEST_PARTY_OBJECT_EVENT		(MessageType_t)((T0_FC_PARTY<<8)|T1_FC_PARTY_REQUEST_PARTY_OBJECT_EVENT)
#define T_FC_PARTY_GET_OTHER_MOVE					(MessageType_t)((T0_FC_PARTY<<8)|T1_FC_PARTY_GET_OTHER_MOVE)	// ��Ƽ���� MOVE_OK ��û
#define T_FC_PARTY_BATTLE_START						(MessageType_t)((T0_FC_PARTY<<8)|T1_FC_PARTY_BATTLE_START)
#define T_FC_PARTY_BATTLE_END						(MessageType_t)((T0_FC_PARTY<<8)|T1_FC_PARTY_BATTLE_END)
#define T_FC_PARTY_PUT_ITEM_OTHER					(MessageType_t)((T0_FC_PARTY<<8)|T1_FC_PARTY_PUT_ITEM_OTHER)	// F->C, �ٸ� ��Ƽ���� ������ ��� ���� ����
#define T_FC_PARTY_AUTO_CREATED_THE_ARENA			(MessageType_t)((T0_FC_PARTY<<8)|T1_FC_PARTY_AUTO_CREATED_THE_ARENA)				// 2012-04-12 by jhseol, �Ʒ��� �߰����� - �ڵ���Ƽ : �ڵ����� ��Ƽ�� ������ ��Ŷ.
#define T_FC_PARTY_REQUEST_INVITE_QUESTION_THE_ARENA	(MessageType_t)((T0_FC_PARTY<<8)|T1_FC_PARTY_REQUEST_INVITE_QUESTION_THE_ARENA)	// 2012-04-12 by jhseol, �Ʒ��� �߰����� - �ڵ���Ƽ : ��Ƽ�� ���Խ�ų Ŭ�󿡰� ��Ƽ ���� �غ� ��Ŷ ������.

#define T_FI_PARTY_CREATE_OK						(MessageType_t)((T0_FI_PARTY<<8)|T1_FI_PARTY_CREATE_OK)
#define T_FI_PARTY_ACCEPT_INVITE_OK					(MessageType_t)((T0_FI_PARTY<<8)|T1_FI_PARTY_ACCEPT_INVITE_OK)
#define T_FI_PARTY_BAN_MEMBER_OK					(MessageType_t)((T0_FI_PARTY<<8)|T1_FI_PARTY_BAN_MEMBER_OK)
#define T_FI_PARTY_LEAVE_OK							(MessageType_t)((T0_FI_PARTY<<8)|T1_FI_PARTY_LEAVE_OK)
#define T_FI_PARTY_TRANSFER_MASTER_OK				(MessageType_t)((T0_FI_PARTY<<8)|T1_FI_PARTY_TRANSFER_MASTER_OK)
#define T_FI_PARTY_DISMEMBER_OK						(MessageType_t)((T0_FI_PARTY<<8)|T1_FI_PARTY_DISMEMBER_OK)
#define T_FI_PARTY_CHANGE_FLIGHT_FORMATION_OK		(MessageType_t)((T0_FI_PARTY<<8)|T1_FI_PARTY_CHANGE_FLIGHT_FORMATION_OK)
#define T_FI_PARTY_CHANGE_FLIGHT_POSITION			(MessageType_t)((T0_FI_PARTY<<8)|T1_FI_PARTY_CHANGE_FLIGHT_POSITION)	// C -> F -> I,All
#define T_FI_PARTY_CANCEL_FLIGHT_POSITION			(MessageType_t)((T0_FI_PARTY<<8)|T1_FI_PARTY_CANCEL_FLIGHT_POSITION)	// C -> F -> I,All
#define T_FI_PARTY_NOTIFY_BATTLE_PARTY				(MessageType_t)((T0_FI_PARTY<<8)|T1_FI_PARTY_NOTIFY_BATTLE_PARTY)		// F->I, ��Ƽ���� �˸�
#define T_FI_PARTY_NOTIFY_BATTLE_PARTY_OK			(MessageType_t)((T0_FI_PARTY<<8)|T1_FI_PARTY_NOTIFY_BATTLE_PARTY_OK)	// I->F, ��Ƽ���� �˸��� ���� ACK
#define T_FI_PARTY_ADD_MEMBER						(MessageType_t)((T0_FI_PARTY<<8)|T1_FI_PARTY_ADD_MEMBER)		// I->F, ��Ƽ���� �߰��϶�� Field Server �˸�
#define T_FI_PARTY_DELETE_MEMBER					(MessageType_t)((T0_FI_PARTY<<8)|T1_FI_PARTY_DELETE_MEMBER)		// I->F, ��Ƽ���� �����϶�� Field Server �˸�
#define T_FI_PARTY_UPDATE_ITEM_POS					(MessageType_t)((T0_FI_PARTY<<8)|T1_FI_PARTY_UPDATE_ITEM_POS)	// F->I, ��Ƽ���� ������ ������ �������� �� ����
#define T_FI_PARTY_ALL_FLIGHT_POSITION				(MessageType_t)((T0_FI_PARTY<<8)|T1_FI_PARTY_ALL_FLIGHT_POSITION)
#define T_FI_PARTY_UPDATE_PARTY_INFO				(MessageType_t)((T0_FI_PARTY<<8)|T1_FI_PARTY_UPDATE_PARTY_INFO)	// I->F, ��Ƽ ������ ������Ʈ
#define T_FI_PARTY_CHANGE_EXP_DISTRIBUTE_TYPE		(MessageType_t)((T0_FI_PARTY<<8)|T1_FI_PARTY_CHANGE_EXP_DISTRIBUTE_TYPE)	// 2008-06-04 by dhjin, EP3 ���� ���� - ����ġ �й� ��� ���� 
#define T_FI_PARTY_CHANGE_ITEM_DISTRIBUTE_TYPE		(MessageType_t)((T0_FI_PARTY<<8)|T1_FI_PARTY_CHANGE_ITEM_DISTRIBUTE_TYPE)	// 2008-06-04 by dhjin, EP3 ���� ���� - ������ �й� ��� ����
#define T_FI_PARTY_CHANGE_FORMATION_SKILL			(MessageType_t)((T0_FI_PARTY<<8)|T1_FI_PARTY_CHANGE_FORMATION_SKILL)		// 2009-08-03 by cmkwon, EP3-4 ���� ���� ��ų ���� - 
#define T_FI_PARTY_ARENA_TEAM_NUM					(MessageType_t)((T0_FI_PARTY<<8)|T1_FI_PARTY_ARENA_TEAM_NUM)	// 2012-04-12 by jhseol, �Ʒ��� �߰����� - �ڵ���Ƽ : ����ȣ ������

#define T_IC_PARTY_CREATE							(MessageType_t)((T0_IC_PARTY<<8)|T1_IC_PARTY_CREATE)
#define T_IC_PARTY_ACCEPT_INVITE_OK					(MessageType_t)((T0_IC_PARTY<<8)|T1_IC_PARTY_ACCEPT_INVITE_OK)
#define T_IC_PARTY_GET_MEMBER						(MessageType_t)((T0_IC_PARTY<<8)|T1_IC_PARTY_GET_MEMBER)
#define T_IC_PARTY_PUT_MEMBER						(MessageType_t)((T0_IC_PARTY<<8)|T1_IC_PARTY_PUT_MEMBER)
#define T_IC_PARTY_GET_ALL_MEMBER					(MessageType_t)((T0_IC_PARTY<<8)|T1_IC_PARTY_GET_ALL_MEMBER)
#define T_IC_PARTY_PUT_ALL_MEMBER					(MessageType_t)((T0_IC_PARTY<<8)|T1_IC_PARTY_PUT_ALL_MEMBER)
#define T_IC_PARTY_BAN_MEMBER						(MessageType_t)((T0_IC_PARTY<<8)|T1_IC_PARTY_BAN_MEMBER)
#define T_IC_PARTY_BAN_MEMBER_OK					(MessageType_t)((T0_IC_PARTY<<8)|T1_IC_PARTY_BAN_MEMBER_OK)
#define T_IC_PARTY_LEAVE							(MessageType_t)((T0_IC_PARTY<<8)|T1_IC_PARTY_LEAVE)
#define T_IC_PARTY_LEAVE_OK							(MessageType_t)((T0_IC_PARTY<<8)|T1_IC_PARTY_LEAVE_OK)
#define T_IC_PARTY_TRANSFER_MASTER					(MessageType_t)((T0_IC_PARTY<<8)|T1_IC_PARTY_TRANSFER_MASTER)
#define T_IC_PARTY_TRANSFER_MASTER_OK				(MessageType_t)((T0_IC_PARTY<<8)|T1_IC_PARTY_TRANSFER_MASTER_OK)
#define T_IC_PARTY_DISMEMBER						(MessageType_t)((T0_IC_PARTY<<8)|T1_IC_PARTY_DISMEMBER)
#define T_IC_PARTY_DISMEMBER_OK						(MessageType_t)((T0_IC_PARTY<<8)|T1_IC_PARTY_DISMEMBER_OK)
#define T_IC_PARTY_CHANGE_FLIGHT_FORMATION			(MessageType_t)((T0_IC_PARTY<<8)|T1_IC_PARTY_CHANGE_FLIGHT_FORMATION)		// Cm -> I
#define T_IC_PARTY_CHANGE_FLIGHT_FORMATION_OK		(MessageType_t)((T0_IC_PARTY<<8)|T1_IC_PARTY_CHANGE_FLIGHT_FORMATION_OK)	// I -> C
#define T_IC_PARTY_GET_FLIGHT_POSITION				(MessageType_t)((T0_IC_PARTY<<8)|T1_IC_PARTY_GET_FLIGHT_POSITION)			// C -> I -> Cm
#define T_IC_PARTY_CHANGE_FLIGHT_POSITION			(MessageType_t)((T0_IC_PARTY<<8)|T1_IC_PARTY_CHANGE_FLIGHT_POSITION)		// Cm -> I -> C
#define T_IC_PARTY_CANCEL_FLIGHT_POSITION			(MessageType_t)((T0_IC_PARTY<<8)|T1_IC_PARTY_CANCEL_FLIGHT_POSITION)		// C -> I -> Cm
#define T_IC_PARTY_PUT_LAST_PARTY_INFO				(MessageType_t)((T0_IC_PARTY<<8)|T1_IC_PARTY_PUT_LAST_PARTY_INFO)			// I -> C, ��Ƽ���� �ٽ� ������ �����Ͽ��� �� ����, �ڱ� �ڽſ��Ը� ����
#define T_IC_PARTY_UPDATE_MEMBER_INFO_MAPNAME		(MessageType_t)((T0_IC_PARTY<<8)|T1_IC_PARTY_UPDATE_MEMBER_INFO_MAPNAME)	// I -> C, ������ ���̸� ����
#define T_IC_PARTY_MEMBER_INVALIDATED				(MessageType_t)((T0_IC_PARTY<<8)|T1_IC_PARTY_MEMBER_INVALIDATED)			// I -> C, ��Ƽ���� ������������ ���ӿ��� ƨ���� �� ����
#define T_IC_PARTY_MEMBER_REJOINED					(MessageType_t)((T0_IC_PARTY<<8)|T1_IC_PARTY_MEMBER_REJOINED)				// I -> C, ��Ƽ���� �ٽ� ������ �����Ͽ��� �� ����, �ڽ��� ������
#define T_IC_PARTY_UPDATE_ITEM_POS					(MessageType_t)((T0_IC_PARTY<<8)|T1_IC_PARTY_UPDATE_ITEM_POS)				// I -> C, ��Ƽ���� ������ ������ �������� �� ����
#define T_IC_PARTY_ALL_FLIGHT_POSITION				(MessageType_t)((T0_IC_PARTY<<8)|T1_IC_PARTY_ALL_FLIGHT_POSITION)			// C->I, I->C, ��Ƽ���� IMServer�� �����ϸ� IMServer�� ��� ��Ƽ���鿡�� ����
#define T_IC_PARTY_REQUEST_PARTYINFO_FROM_A_TO_M	(MessageType_t)((T0_IC_PARTY<<8)|T1_IC_PARTY_REQUEST_PARTYINFO_FROM_A_TO_M) // 2008-02-28 by dhjin, �Ʒ��� ���� - C->I, �Ʒ��� ���� �� ���� ������ ���� �� ���� ��Ƽ �˻� 
#define T_IC_PARTY_LEAVE_FROM_M_TO_A				(MessageType_t)((T0_IC_PARTY<<8)|T1_IC_PARTY_LEAVE_FROM_M_TO_A)				// 2008-02-28 by dhjin, �Ʒ��� ���� - C->I, �Ʒ��� ������ ���� ���μ������� ��Ƽ ���� ó��
#define T_IC_PARTY_LEAVE_FROM_A_TO_M				(MessageType_t)((T0_IC_PARTY<<8)|T1_IC_PARTY_LEAVE_FROM_A_TO_M)				// 2008-02-28 by dhjin, �Ʒ��� ���� - C->I, �Ʒ��� �������� ���μ����� �����Ҷ� �Ʒ��� �������� ��Ƽ Ż�� ó�� Ŭ���̾�Ʈ���� �������� �ʴ´�.
#define T_IC_PARTY_LIST_INFO						(MessageType_t)((T0_IC_PARTY<<8)|T1_IC_PARTY_LIST_INFO)						// C -> I, 2008-06-02 by dhjin, EP3 ���� ���� - ���� ���� ����Ʈ ��û
#define T_IC_PARTY_LIST_INFO_OK						(MessageType_t)((T0_IC_PARTY<<8)|T1_IC_PARTY_LIST_INFO_OK)					// I -> C, 2008-06-02 by dhjin, EP3 ���� ���� - ���� ���� ����Ʈ ��û OK
#define T_IC_PARTY_JOIN_FREE						(MessageType_t)((T0_IC_PARTY<<8)|T1_IC_PARTY_JOIN_FREE)						// C -> I, 2008-06-03 by dhjin, EP3 ���� ���� - ���� ���� ����
#define T_IC_PARTY_JOIN_FREE_OK						(MessageType_t)((T0_IC_PARTY<<8)|T1_IC_PARTY_JOIN_FREE_OK)					// I -> C, 2008-06-03 by dhjin, EP3 ���� ���� - ���� ���� ���� OK
#define T_IC_PARTY_CHANGE_INFO						(MessageType_t)((T0_IC_PARTY<<8)|T1_IC_PARTY_CHANGE_INFO)					// C -> I, 2008-06-04 by dhjin, EP3 ���� ���� - ���� ���� ����
#define T_IC_PARTY_CHANGE_INFO_OK					(MessageType_t)((T0_IC_PARTY<<8)|T1_IC_PARTY_CHANGE_INFO_OK)				// I -> C, 2008-06-04 by dhjin, EP3 ���� ���� - ���� ���� ���� OK
#define T_IC_PARTY_RECOMMENDATION_MEMBER			(MessageType_t)((T0_IC_PARTY<<8)|T1_IC_PARTY_RECOMMENDATION_MEMBER)			// C -> I, 2008-06-04 by dhjin, EP3 ���� ���� - ��õ �ɸ��� ��û
#define T_IC_PARTY_RECOMMENDATION_MEMBER_OK			(MessageType_t)((T0_IC_PARTY<<8)|T1_IC_PARTY_RECOMMENDATION_MEMBER_OK)		// I -> C, 2008-06-04 by dhjin, EP3 ���� ���� - ��õ �ɸ��� ��û OK
#define T_IC_PARTY_INFO								(MessageType_t)((T0_IC_PARTY<<8)|T1_IC_PARTY_INFO)							// I -> C, 2008-06-10 by dhjin, EP3 ���� ���� - ���� ���� ����

// FI_CHARACTER
#define T_FI_CHARACTER_DELETE_CHARACTER				(MessageType_t)((T0_FI_CHARACTER<<8)|T1_FI_CHARACTER_DELETE_CHARACTER)		// F->I, ĳ���� ���� ����
#define T_FI_CHARACTER_CHANGE_LEVEL					(MessageType_t)((T0_FI_CHARACTER<<8)|T1_FI_CHARACTER_CHANGE_LEVEL)			// F->I, ĳ���� ���� ��ȭ ����
#define T_FI_CHARACTER_UPDATE_GUILD_INFO			(MessageType_t)((T0_FI_CHARACTER<<8)|T1_FI_CHARACTER_UPDATE_GUILD_INFO)		// I->F, ��� ���� ������Ʈ
#define T_FI_CHARACTER_UPDATE_MAP_CHANNEL			(MessageType_t)((T0_FI_CHARACTER<<8)|T1_FI_CHARACTER_UPDATE_MAP_CHANNEL)	// F->I, ��ä�� ���� ������Ʈ
#define T_FI_CHARACTER_CHANGE_INFLUENCE_TYPE		(MessageType_t)((T0_FI_CHARACTER<<8)|T1_FI_CHARACTER_CHANGE_INFLUENCE_TYPE)	// F->I, 2005-12-03 by cmkwon
#define T_FI_UPDATE_SUBLEADER						(MessageType_t)((T0_FI_CHARACTER<<8)|T1_FI_UPDATE_SUBLEADER)				// F->I, 2007-02-14 by dhjin
#define T_FI_CREATE_GUILD_BY_SUBLEADER				(MessageType_t)((T0_FI_CHARACTER<<8)|T1_FI_CREATE_GUILD_BY_SUBLEADER)		// F->I, 2007-10-06 by dhjin


#define T_FC_MONSTER_CREATED						(MessageType_t)((T0_FC_MONSTER<<8)|T1_FC_MONSTER_CREATED)
#define T_FC_MONSTER_MOVE_OK						(MessageType_t)((T0_FC_MONSTER<<8)|T1_FC_MONSTER_MOVE_OK)
#define T_FC_MONSTER_HIDE							(MessageType_t)((T0_FC_MONSTER<<8)|T1_FC_MONSTER_HIDE)
#define T_FC_MONSTER_SHOW							(MessageType_t)((T0_FC_MONSTER<<8)|T1_FC_MONSTER_SHOW)
#define T_FC_MONSTER_CHANGE_HP						(MessageType_t)((T0_FC_MONSTER<<8)|T1_FC_MONSTER_CHANGE_HP)
#define T_FC_MONSTER_CHANGE_BODYCONDITION			(MessageType_t)((T0_FC_MONSTER<<8)|T1_FC_MONSTER_CHANGE_BODYCONDITION)
#define T_FC_MONSTER_SKILL_USE_SKILL				(MessageType_t)((T0_FC_MONSTER<<8)|T1_FC_MONSTER_SKILL_USE_SKILL)
#define T_FC_MONSTER_SKILL_END_SKILL				(MessageType_t)((T0_FC_MONSTER<<8)|T1_FC_MONSTER_SKILL_END_SKILL)
#define T_FC_MONSTER_SUMMON_MONSTER					(MessageType_t)((T0_FC_MONSTER<<8)|T1_FC_MONSTER_SUMMON_MONSTER)			// C->F, ���� ���� ����
#define T_FC_MONSTER_TUTORIAL_MONSTER_DEAD_NOTIFY	(MessageType_t)((T0_FC_MONSTER<<8)|T1_FC_MONSTER_TUTORIAL_MONSTER_DEAD_NOTIFY)	// F->C, Ʃ�丮��ʿ��� ���Ͱ� �������� Ŭ���̾�Ʈ�� �˸�
#define T_FC_MONSTER_TUTORIAL_MONSTER_DELETE		(MessageType_t)((T0_FC_MONSTER<<8)|T1_FC_MONSTER_TUTORIAL_MONSTER_DELETE)		// C->F, Ʃ�丮��ʿ��� ���� ������ ������ ��û
#define T_FC_MONSTER_CHANGE_INDEX					(MessageType_t)((T0_FC_MONSTER<<8)|T1_FC_MONSTER_CHANGE_INDEX)		// F->C, 2011-05-17 by hskim, ���Ǵ�Ƽ 3�� - �ó׸� ���� ��ü ���
#define T_FC_MONSTER_CINEMA_DELETE_NOTIFY			(MessageType_t)((T0_FC_MONSTER<<8)|T1_FC_MONSTER_CINEMA_DELETE_NOTIFY)		// F->C, 2011-05-30 by hskim, ���Ǵ�Ƽ 3�� - ���� ���� Ŭ���̾�Ʈ �ݿ�

#define T_FN_MAPPROJECT_START						(MessageType_t)((T0_FN_MONSTER<<8)|T1_FN_MAPPROJECT_START)
#define T_FN_MAPPROJECT_START_OK					(MessageType_t)((T0_FN_MONSTER<<8)|T1_FN_MAPPROJECT_START_OK)
#define T_FN_MAPPROJECT_START_OK_ACK				(MessageType_t)((T0_FN_MONSTER<<8)|T1_FN_MAPPROJECT_START_OK_ACK)
#define T_FN_MONSTER_CREATE							(MessageType_t)((T0_FN_MONSTER<<8)|T1_FN_MONSTER_CREATE)
#define T_FN_MONSTER_CREATE_OK						(MessageType_t)((T0_FN_MONSTER<<8)|T1_FN_MONSTER_CREATE_OK)
#define T_FN_MONSTER_DELETE							(MessageType_t)((T0_FN_MONSTER<<8)|T1_FN_MONSTER_DELETE)
#define T_FN_MONSTER_CHANGE_OK						(MessageType_t)((T0_FN_MONSTER<<8)|T1_FN_MONSTER_CHANGE_OK)		// 2011-05-11 by hskim, ���Ǵ�Ƽ 3�� - �ó׸� ���� ��� �߰� - �ش� ��ä�� Ư�� ���� ���� ��� �߰�
#define T_FN_CLIENT_GAMESTART_OK					(MessageType_t)((T0_FN_MONSTER<<8)|T1_FN_CLIENT_GAMESTART_OK)
#define T_FN_CLIENT_GAMEEND_OK						(MessageType_t)((T0_FN_MONSTER<<8)|T1_FN_CLIENT_GAMEEND_OK)
#define T_FN_GET_CHARACTER_INFO						(MessageType_t)((T0_FN_MONSTER<<8)|T1_FN_GET_CHARACTER_INFO)
#define T_FN_GET_CHARACTER_INFO_OK					(MessageType_t)((T0_FN_MONSTER<<8)|T1_FN_GET_CHARACTER_INFO_OK)
#define T_FN_ADMIN_SUMMON_MONSTER					(MessageType_t)((T0_FN_MONSTER<<8)|T1_FN_ADMIN_SUMMON_MONSTER)
#define T_FN_MONSTER_CHANGE_HP						(MessageType_t)((T0_FN_MONSTER<<8)|T1_FN_MONSTER_CHANGE_HP)
#define T_FN_MONSTER_CHANGE_BODYCONDITION			(MessageType_t)((T0_FN_MONSTER<<8)|T1_FN_MONSTER_CHANGE_BODYCONDITION)
#define T_FN_MONSTER_SKILL_USE_SKILL				(MessageType_t)((T0_FN_MONSTER<<8)|T1_FN_MONSTER_SKILL_USE_SKILL)
#define T_FN_MONSTER_SKILL_END_SKILL				(MessageType_t)((T0_FN_MONSTER<<8)|T1_FN_MONSTER_SKILL_END_SKILL)
#define T_FN_MONSTER_AUTO_DESTROYED					(MessageType_t)((T0_FN_MONSTER<<8)|T1_FN_MONSTER_AUTO_DESTROYED)	// 2006-04-17 by cmkwon
#define T_FN_MONSTER_STRATEGYPOINT_INIT				(MessageType_t)((T0_FN_MONSTER<<8)|T1_FN_MONSTER_STRATEGYPOINT_INIT)	// 2006-11-20 by cmkwon, F->N
#define T_FN_MONSTER_STRATEGYPOINT_SUMMON			(MessageType_t)((T0_FN_MONSTER<<8)|T1_FN_MONSTER_STRATEGYPOINT_SUMMON)	// 2006-11-20 by cmkwon, F->N
#define T_FN_MONSTER_OUTPOST_INIT					(MessageType_t)((T0_FN_MONSTER<<8)|T1_FN_MONSTER_OUTPOST_INIT)		// 2007-08-24 by dhjin, F->N
#define T_FN_MONSTER_OUTPOST_RESET_SUMMON			(MessageType_t)((T0_FN_MONSTER<<8)|T1_FN_MONSTER_OUTPOST_RESET_SUMMON)	// 2007-08-24 by dhjin, F->N
#define T_FN_MONSTER_CREATE_IN_MAPCHANNEL_BYVALUE	(MessageType_t)((T0_FN_MONSTER<<8)|T1_FN_MONSTER_CREATE_IN_MAPCHANNEL_BYVALUE)	// 2007-08-29 by dhjin
#define T_FN_MONSTER_TELEPORT_SUMMON				(MessageType_t)((T0_FN_MONSTER<<8)|T1_FN_MONSTER_TELEPORT_SUMMON)	// 2007-09-05 by dhjin

#define T_FN_NPCSERVER_START						(MessageType_t)((T0_FN_NPCSERVER<<8)|T1_FN_NPCSERVER_START)
#define T_FN_NPCSERVER_START_OK						(MessageType_t)((T0_FN_NPCSERVER<<8)|T1_FN_NPCSERVER_START_OK)
#define T_FN_NPCSERVER_SUMMON_JACO_MONSTER			(MessageType_t)((T0_FN_NPCSERVER<<8)|T1_FN_NPCSERVER_SUMMON_JACO_MONSTER)
#define T_FN_NPCSERVER_DELETE_MONSTER_IN_MAPCHANNEL	(MessageType_t)((T0_FN_NPCSERVER<<8)|T1_FN_NPCSERVER_DELETE_MONSTER_IN_MAPCHANNEL)	// TCP:F->N, // 2007-08-22 by cmkwon, �ش� ��ä�� ���� ��� �����ϱ� ��� �߰�
#define T_FN_NPCSERVER_CINEMA_MONSTER_CREATE		(MessageType_t)((T0_FN_NPCSERVER<<8)|T1_FN_NPCSERVER_CINEMA_MONSTER_CREATE)	// 2010-03-31 by dhjin, ���Ǵ�Ƽ(�������) -	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - Ű ���� ����, F -> N
#define T_FN_NPCSERVER_CINEMA_MONSTER_DESTROY		(MessageType_t)((T0_FN_NPCSERVER<<8)|T1_FN_NPCSERVER_CINEMA_MONSTER_DESTROY)	// 2011-04-28 by hskim, ���Ǵ�Ƽ 3�� - �ó׸� ���� ��� �߰� - �ش� ��ä�� Ư�� ���� ���� ��� �߰�
#define T_FN_NPCSERVER_CINEMA_MONSTER_CHANGE		(MessageType_t)((T0_FN_NPCSERVER<<8)|T1_FN_NPCSERVER_CINEMA_MONSTER_CHANGE)		// 2011-05-11 by hskim, ���Ǵ�Ƽ 3�� - �ó׸� ���� ��� �߰� - �ش� ��ä�� Ư�� ���� ���� ��� �߰�
#define T_FN_NPCSERVER_CINEMA_MONSTER_REGEN			(MessageType_t)((T0_FN_NPCSERVER<<8)|T1_FN_NPCSERVER_CINEMA_MONSTER_REGEN)		// 2011-06-02 by hskim, ���Ǵ�Ƽ 3�� - ���� 6 - �ֱ��� ��ȯ ��� ����
#define T_FN_NPCSERVER_NEW_CHANGE_OBJECT			(MessageType_t)((T0_FN_NPCSERVER<<8)|T1_FN_NPCSERVER_NEW_CHANGE_OBJECT)		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ������Ʈ�� ����!!!! 
#define T_FN_NPCSERVER_RESET_CHANGE_OBJECT			(MessageType_t)((T0_FN_NPCSERVER<<8)|T1_FN_NPCSERVER_RESET_CHANGE_OBJECT)		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ������Ʈ�� ����!!!! 
#define T_FN_MONITOR_RELOAD_VERSION_INFO_OK			(MessageType_t)((T0_FN_NPCSERVER<<8)|T1_FN_MONITOR_RELOAD_VERSION_INFO_OK)		// 2013-03-14 by jhseol, �������� ���ε� �� ���� ��� IP����Ʈ�� ����


#define T_FC_EVENT_WARP							(MessageType_t)((T0_FC_EVENT<<8)|T1_FC_EVENT_WARP)
#define T_FC_EVENT_WARP_SAME_MAP				(MessageType_t)((T0_FC_EVENT<<8)|T1_FC_EVENT_WARP_SAME_MAP)
#define T_FC_EVENT_WARP_SAME_MAP_DONE			(MessageType_t)((T0_FC_EVENT<<8)|T1_FC_EVENT_WARP_SAME_MAP_DONE)
#define T_FC_EVENT_WARP_SAME_FIELD_SERVER		(MessageType_t)((T0_FC_EVENT<<8)|T1_FC_EVENT_WARP_SAME_FIELD_SERVER)
#define T_FC_EVENT_WARP_SAME_FIELD_SERVER_DONE	(MessageType_t)((T0_FC_EVENT<<8)|T1_FC_EVENT_WARP_SAME_FIELD_SERVER_DONE)
#define T_FC_EVENT_OTHER_WARPED					(MessageType_t)((T0_FC_EVENT<<8)|T1_FC_EVENT_OTHER_WARPED)
// 2004-12-16 by cmkwon, �ٸ� �ʵ弭������ ������ �����Ƿ� ������
//#define T_FC_EVENT_WARP_CONNECT					(MessageType_t)((T0_FC_EVENT<<8)|T1_FC_EVENT_WARP_CONNECT)
#define T_FC_EVENT_WARP_CONNECT_OK				(MessageType_t)((T0_FC_EVENT<<8)|T1_FC_EVENT_WARP_CONNECT_OK)
#define T_FC_EVENT_ENTER_BUILDING				(MessageType_t)((T0_FC_EVENT<<8)|T1_FC_EVENT_ENTER_BUILDING)
#define T_FC_EVENT_ENTER_BUILDING_OK			(MessageType_t)((T0_FC_EVENT<<8)|T1_FC_EVENT_ENTER_BUILDING_OK)
#define T_FC_EVENT_LEAVE_BUILDING				(MessageType_t)((T0_FC_EVENT<<8)|T1_FC_EVENT_LEAVE_BUILDING)
#define T_FC_EVENT_LEAVE_BUILDING_OK			(MessageType_t)((T0_FC_EVENT<<8)|T1_FC_EVENT_LEAVE_BUILDING_OK)
#define T_FC_EVENT_REQUEST_WARP					(MessageType_t)((T0_FC_EVENT<<8)|T1_FC_EVENT_REQUEST_WARP)
#define T_FC_EVENT_REJECT_WARP					(MessageType_t)((T0_FC_EVENT<<8)|T1_FC_EVENT_REJECT_WARP)
#define T_FC_EVENT_REQUEST_OBJECT_EVENT			(MessageType_t)((T0_FC_EVENT<<8)|T1_FC_EVENT_REQUEST_OBJECT_EVENT)
#define T_FC_EVENT_CHANGE_WEATHER				(MessageType_t)((T0_FC_EVENT<<8)|T1_FC_EVENT_CHANGE_WEATHER)
#define T_FC_EVENT_SUGGEST_CHANNELS				(MessageType_t)((T0_FC_EVENT<<8)|T1_FC_EVENT_SUGGEST_CHANNELS)	// F->C, ���� ������ ä���� ������
#define T_FC_EVENT_SELECT_CHANNEL				(MessageType_t)((T0_FC_EVENT<<8)|T1_FC_EVENT_SELECT_CHANNEL)	// C->F, ������ ä���� ������
#define T_FC_EVENT_SELECT_CHANNEL_WITH_PARTY	(MessageType_t)((T0_FC_EVENT<<8)|T1_FC_EVENT_SELECT_CHANNEL_WITH_PARTY)	// C->F, ������ ä���� ������, ��Ƽ�� ����Ʈ ����
#define T_FC_EVENT_REQUEST_RACING_WARP			(MessageType_t)((T0_FC_EVENT<<8)|T1_FC_EVENT_REQUEST_RACING_WARP)	// C->F, ���̸̽������� ���� ��û
#define T_FC_EVENT_GET_SHOP_WARP_TARGET_MAP_LIST	(MessageType_t)((T0_FC_EVENT<<8)|T1_FC_EVENT_GET_SHOP_WARP_TARGET_MAP_LIST)
#define T_FC_EVENT_GET_SHOP_WARP_TARGET_MAP_LIST_OK	(MessageType_t)((T0_FC_EVENT<<8)|T1_FC_EVENT_GET_SHOP_WARP_TARGET_MAP_LIST_OK)
#define T_FC_EVENT_REQUEST_SHOP_WARP				(MessageType_t)((T0_FC_EVENT<<8)|T1_FC_EVENT_REQUEST_SHOP_WARP)
#define T_FC_EVENT_CHARACTERMODE_ENTER_BUILDING		(MessageType_t)((T0_FC_EVENT<<8)|T1_FC_EVENT_CHARACTERMODE_ENTER_BUILDING)	// C->F, 
#define T_FC_EVENT_CALL_WARP_EVENT_REQUEST			(MessageType_t)((T0_FC_EVENT<<8)|T1_FC_EVENT_CALL_WARP_EVENT_REQUEST)		// 2006-07-21 by cmkwon, F->C(n)
#define T_FC_EVENT_CALL_WARP_EVENT_REQUEST_ACK		(MessageType_t)((T0_FC_EVENT<<8)|T1_FC_EVENT_CALL_WARP_EVENT_REQUEST_ACK)	// 2006-07-21 by cmkwon, C(n)->F


#define T_FN_EVENT_WARP							(MessageType_t)((T0_FN_EVENT<<8)|T1_FN_EVENT_WARP)
#define T_FN_EVENT_OTHER_WARPED					(MessageType_t)((T0_FN_EVENT<<8)|T1_FN_EVENT_OTHER_WARPED)
#define T_FN_EVENT_WARP_CONNECT_OK				(MessageType_t)((T0_FN_EVENT<<8)|T1_FN_EVENT_WARP_CONNECT_OK)

// 2005-07-27 by cmkwon, �ٸ� �ʵ弭������ ������ �����Ƿ� ������
//#define T_FP_EVENT_NOTIFY_WARP					(MessageType_t)((T0_FP_EVENT<<8)|T1_FP_EVENT_NOTIFY_WARP)
//#define T_FP_EVENT_NOTIFY_WARP_OK				(MessageType_t)((T0_FP_EVENT<<8)|T1_FP_EVENT_NOTIFY_WARP_OK)
#define T_FP_EVENT_ENTER_SELECT_SCREEN			(MessageType_t)((T0_FP_EVENT<<8)|T1_FP_EVENT_ENTER_SELECT_SCREEN)	// F->P, Client�� ĳ���� ���� â�� ����
#define T_FP_EVENT_GAME_STARTED					(MessageType_t)((T0_FP_EVENT<<8)|T1_FP_EVENT_GAME_STARTED)			// F->P, Client�� ������ ������(������ ����)
#define T_FP_EVENT_MAP_CHANGED					(MessageType_t)((T0_FP_EVENT<<8)|T1_FP_EVENT_MAP_CHANGED)			// F->P, Client�� ���� �̵���
#define T_FP_EVENT_RELOAD_HAPPYEV				(MessageType_t)((T0_FP_EVENT<<8)|T1_FP_EVENT_RELOAD_HAPPYEV)		// P->F, No Body, All ServerGroup reload HappyHourEvent.
#define T_FP_EVENT_RELOAD_ITEMEV				(MessageType_t)((T0_FP_EVENT<<8)|T1_FP_EVENT_RELOAD_ITEMEV)			// P->F, No Body, All ServerGroup reload ITEMEvent.
#define T_FP_EVENT_UPDATE_PCBANGLIST			(MessageType_t)((T0_FP_EVENT<<8)|T1_FP_EVENT_UPDATE_PCBANGLIST)		// P->F, No Body
#define T_FP_EVENT_UPDATE_STRATEGYPOINT_NOTSUMMONTIM			(MessageType_t)((T0_FP_EVENT<<8)|T1_FP_EVENT_UPDATE_STRATEGYPOINT_NOTSUMMONTIM)		// P->F, No Body

// T0_FP_MONITOR
#define T_FP_MONITOR_SET_MGAME_EVENT_TYPE		(MessageType_t)((T0_FP_MONITOR<<8)|T1_FP_MONITOR_SET_MGAME_EVENT_TYPE)
#define T_FP_MONITOR_RELOAD_VERSION_INFO_OK		(MessageType_t)((T0_FP_MONITOR<<8)|T1_FP_MONITOR_RELOAD_VERSION_INFO_OK)	// P->F(n), No Body, // 2008-09-08 by cmkwon, SCMonitor���� ReloadVersionInfo�ÿ� �Ϻ� üũ������(.\Res-Tex\*.*)�� ���ε��ϱ� - 

// T0_FP_CASH
#define T_FP_CASH_CHANGE_CHARACTERNAME			(MessageType_t)((T0_FP_CASH<<8)|T1_FP_CASH_CHANGE_CHARACTERNAME)

struct MSG_FP_CASH_CHANGE_CHARACTERNAME
{
	char		szAccName[SIZE_MAX_ACCOUNT_NAME];
	char		szChangedCharName[SIZE_MAX_CHARACTER_NAME];
};

// #define T0_FP_ADMIN					0x73			// 2008-01-31 by cmkwon, ���� ����/���� ���ɾ�� ������ �ý��� ���� - 
#define T_FP_ADMIN_BLOCKACCOUNT					(MessageType_t)((T0_FP_ADMIN<<8)|T1_FP_ADMIN_BLOCKACCOUNT)	// 2008-01-31 by cmkwon, ���� ����/���� ���ɾ�� ������ �ý��� ���� - 
#define T_FP_ADMIN_BLOCKACCOUNT_OK				(MessageType_t)((T0_FP_ADMIN<<8)|T1_FP_ADMIN_BLOCKACCOUNT_OK)	// 2008-01-31 by cmkwon, ���� ����/���� ���ɾ�� ������ �ý��� ���� - 
#define T_FP_ADMIN_UNBLOCKACCOUNT				(MessageType_t)((T0_FP_ADMIN<<8)|T1_FP_ADMIN_UNBLOCKACCOUNT)	// 2008-01-31 by cmkwon, ���� ����/���� ���ɾ�� ������ �ý��� ���� - 
#define T_FP_ADMIN_UNBLOCKACCOUNT_OK			(MessageType_t)((T0_FP_ADMIN<<8)|T1_FP_ADMIN_UNBLOCKACCOUNT_OK)	// 2008-01-31 by cmkwon, ���� ����/���� ���ɾ�� ������ �ý��� ���� - 
#define T_FP_ADMIN_STRATRGYPOINT_INFO_CHANGE	(MessageType_t)((T0_FP_ADMIN<<8)|T1_FP_ADMIN_STRATRGYPOINT_INFO_CHANGE)	// 2012-11-13 by jhseol, ���� �ý��� ������ - ������

struct MSG_FP_ADMIN_BLOCKACCOUNT		// 2008-01-31 by cmkwon, ���� ����/���� ���ɾ�� ������ �ý��� ���� - 
{
	SBLOCKED_ACCOUNT_INFO blockAccInfo;
};
struct MSG_FP_ADMIN_BLOCKACCOUNT_OK		// 2008-01-31 by cmkwon, ���� ����/���� ���ɾ�� ������ �ý��� ���� - 
{
	Err_t	ErrCode;		// ERR_NO_ERROR �̸� ����
	INT		AdminFieldServerClientIndex;		// 2008-01-31 by cmkwon, ���� ����/���� ���ɾ�� ������ �ý��� ���� - PreServer<->FieldServer ������ �����
	char	AdminAccName[SIZE_MAX_ACCOUNT_NAME];
	char	BlockedAccName[SIZE_MAX_ACCOUNT_NAME];
	ATUM_DATE_TIME	atimeEndTime;				// ���� ���� �ð�
};

struct MSG_FP_ADMIN_UNBLOCKACCOUNT		// 2008-01-31 by cmkwon, ���� ����/���� ���ɾ�� ������ �ý��� ���� - 
{
	SBLOCKED_ACCOUNT_INFO blockAccInfo;
};
struct MSG_FP_ADMIN_UNBLOCKACCOUNT_OK	// 2008-01-31 by cmkwon, ���� ����/���� ���ɾ�� ������ �ý��� ���� - 
{
	Err_t	ErrCode;		// ERR_NO_ERROR �̸� ����
	INT		AdminFieldServerClientIndex;		// 2008-01-31 by cmkwon, ���� ����/���� ���ɾ�� ������ �ý��� ���� - PreServer<->FieldServer ������ �����
	char	AdminAccName[SIZE_MAX_ACCOUNT_NAME];
	char	UnblockedAccName[SIZE_MAX_ACCOUNT_NAME];
};


#define T_FC_STORE_GET_ITEM						(MessageType_t)((T0_FC_STORE<<8)|T1_FC_STORE_GET_ITEM)
#define T_FC_STORE_PUT_ITEM_HEADER				(MessageType_t)((T0_FC_STORE<<8)|T1_FC_STORE_PUT_ITEM_HEADER)
#define T_FC_STORE_PUT_ITEM						(MessageType_t)((T0_FC_STORE<<8)|T1_FC_STORE_PUT_ITEM)
#define T_FC_STORE_PUT_ITEM_DONE				(MessageType_t)((T0_FC_STORE<<8)|T1_FC_STORE_PUT_ITEM_DONE)
#define T_FC_STORE_MOVE_ITEM					(MessageType_t)((T0_FC_STORE<<8)|T1_FC_STORE_MOVE_ITEM)
#define T_FC_STORE_MOVE_ITEM_OK					(MessageType_t)((T0_FC_STORE<<8)|T1_FC_STORE_MOVE_ITEM_OK)
#define T_FC_STORE_INSERT_ITEM					(MessageType_t)((T0_FC_STORE<<8)|T1_FC_STORE_INSERT_ITEM)
#define T_FC_STORE_DELETE_ITEM					(MessageType_t)((T0_FC_STORE<<8)|T1_FC_STORE_DELETE_ITEM)
#define T_FC_STORE_UPDATE_ITEM_COUNT			(MessageType_t)((T0_FC_STORE<<8)|T1_FC_STORE_UPDATE_ITEM_COUNT)
#define T_FC_STORE_UPDATE_ENDURANCE				(MessageType_t)((T0_FC_STORE<<8)|T1_FC_STORE_UPDATE_ENDURANCE)
#define T_FC_STORE_UPDATE_POSSESS				(MessageType_t)((T0_FC_STORE<<8)|T1_FC_STORE_UPDATE_POSSESS)
#define T_FC_STORE_UPDATE_RARE_FIX				(MessageType_t)((T0_FC_STORE<<8)|T1_FC_STORE_UPDATE_RARE_FIX)		// F->C, ���λ�, ���̻��� ������Ʈ ����
#define T_FC_STORE_INSERT_USINGITEM				(MessageType_t)((T0_FC_STORE<<8)|T1_FC_STORE_INSERT_USINGITEM)
#define T_FC_STORE_DELETE_USINGITEM				(MessageType_t)((T0_FC_STORE<<8)|T1_FC_STORE_DELETE_USINGITEM)
#define T_FC_STORE_UPDATE_USINGITEM				(MessageType_t)((T0_FC_STORE<<8)|T1_FC_STORE_UPDATE_USINGITEM)		// F->C, 2006-03-30 by cmkwon
#define T_FC_STORE_EXPIRE_USINGITEM				(MessageType_t)((T0_FC_STORE<<8)|T1_FC_STORE_EXPIRE_USINGITEM)		// C->F, 2006-10-11 by cmkwon, ��� �ð��� �������� ������ �˸�
#define T_FC_STORE_UPDATE_ITEMSTORAGE			(MessageType_t)((T0_FC_STORE<<8)|T1_FC_STORE_UPDATE_ITEMSTORAGE)	// 2005-12-07 by cmkwon
#define T_FC_STORE_UPDATE_ITEMNUM				(MessageType_t)((T0_FC_STORE<<8)|T1_FC_STORE_UPDATE_ITEMNUM)		// 2006-06-14 by cmkwon
#define T_FC_STORE_REQUEST_QUICKSLOT			(MessageType_t)((T0_FC_STORE<<8)|T1_FC_STORE_REQUEST_QUICKSLOT)		// 2006-09-04 by dhjin
#define T_FC_STORE_REQUEST_QUICKSLOT_OK			(MessageType_t)((T0_FC_STORE<<8)|T1_FC_STORE_REQUEST_QUICKSLOT_OK)	// 2006-09-04 by dhjin
#define T_FC_STORE_SAVE_QUICKSLOT				(MessageType_t)((T0_FC_STORE<<8)|T1_FC_STORE_SAVE_QUICKSLOT)		// 2006-09-04 by dhjin
#define T_FC_STORE_LOG_GUILD_ITEM				(MessageType_t)((T0_FC_STORE<<8)|T1_FC_STORE_LOG_GUILD_ITEM)			// 2006-09-27 by dhjin
#define T_FC_STORE_LOG_GUILD_ITEM_OK			(MessageType_t)((T0_FC_STORE<<8)|T1_FC_STORE_LOG_GUILD_ITEM_OK)			// 2006-09-27 by dhjin
#define T_FC_STORE_LOG_GUILD_ITEM_OK_HEADER		(MessageType_t)((T0_FC_STORE<<8)|T1_FC_STORE_LOG_GUILD_ITEM_OK_HEADER)	// 2006-09-27 by dhjin
#define T_FC_STORE_LOG_GUILD_ITEM_OK_DONE		(MessageType_t)((T0_FC_STORE<<8)|T1_FC_STORE_LOG_GUILD_ITEM_OK_DONE)	// 2006-09-27 by dhjin
#define T_FC_STORE_UPDATE_ARMOR_ITEM_EVENT_INFO	(MessageType_t)((T0_FC_STORE<<8)|T1_FC_STORE_UPDATE_ARMOR_ITEM_EVENT_INFO)		// 2013-04-18 by jhseol,bckim �̴��� �Ƹ� - �̴��� �Ƹ� ���� ���� ���� ��Ŷ

#define T_FC_ITEM_SHOW_ITEM								(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_SHOW_ITEM)
#define T_FC_ITEM_HIDE_ITEM								(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_HIDE_ITEM)
#define T_FC_ITEM_GET_ITEM								(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_GET_ITEM)
#define T_FC_ITEM_GET_ITEM_OK							(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_GET_ITEM_OK)
#define T_FC_ITEM_GET_ITEM_FAIL							(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_GET_ITEM_FAIL)
#define T_FC_ITEM_PUT_ITEM								(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_PUT_ITEM)
// 2005-11-15 by cmkwon, ������
//#define T_FC_ITEM_BONUSSKILLPOINT						(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_BONUSSKILLPOINT)
//#define T_FC_ITEM_BONUSSKILLPOINT_OK					(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_BONUSSKILLPOINT_OK)
#define T_FC_ITEM_CHANGE_WINDOW_POSITION				(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_CHANGE_WINDOW_POSITION)
#define T_FC_ITEM_CHANGE_WINDOW_POSITION_OK				(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_CHANGE_WINDOW_POSITION_OK)
#define T_FC_ITEM_UPDATE_WINDOW_ITEM_LIST				(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_UPDATE_WINDOW_ITEM_LIST)
#define T_FC_ITEM_THROW_AWAY_ITEM						(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_THROW_AWAY_ITEM)
#define T_FC_ITEM_THROW_AWAY_ITEM_OK					(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_THROW_AWAY_ITEM_OK)
#define T_FC_ITEM_USE_ENERGY							(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_USE_ENERGY)
#define T_FC_ITEM_USE_ENERGY_OK							(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_USE_ENERGY_OK)
#define T_FC_ITEM_USE_ITEM								(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_USE_ITEM)
#define T_FC_ITEM_USE_ITEM_OK							(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_USE_ITEM_OK)
#define T_FC_ITEM_DELETE_ITEM_ADMIN						(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_DELETE_ITEM_ADMIN)
#define T_FC_ITEM_RELOAD_ITEM_INFO						(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_RELOAD_ITEM_INFO)	// ������ ������ ������Ʈ�Ǿ���, no body
#define T_FC_ITEM_USE_ENCHANT							(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_USE_ENCHANT)
#define T_FC_ITEM_USE_ENCHANT_OK						(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_USE_ENCHANT_OK)
#define T_FC_ITEM_PUT_ENCHANT_HEADER					(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_PUT_ENCHANT_HEADER)
#define T_FC_ITEM_PUT_ENCHANT							(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_PUT_ENCHANT)
#define T_FC_ITEM_PUT_ENCHANT_DONE						(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_PUT_ENCHANT_DONE)
#define T_FC_ITEM_DELETE_ALL_ENCHANT					(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_DELETE_ALL_ENCHANT)	// F->C, �������� ��� ��æƮ�� �����Ѵ�
#define T_FC_ITEM_DELETE_DROP_ITEM						(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_DELETE_DROP_ITEM)	// F->C, �ڽ��� �Ѹ� ������(���ε�)�� ���� �� ����
#define T_FC_ITEM_UPDATE_ITEM_POS						(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_UPDATE_ITEM_POS)		// F->C, ������ ����(��)�� ������, ������ ������ �ٲٸ� ������ ������
#define T_FC_ITEM_MIX_ITEMS								(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_MIX_ITEMS)			// C->F, ������ �������� ����Ʈ�� ����
#define T_FC_ITEM_MIX_ITEMS_RESULT						(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_MIX_ITEMS_RESULT)	// F->C, ������ ���� ����� ����
#define T_FC_ITEM_USE_CARDITEM_GUILDSUMMON				(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_USE_CARDITEM_GUILDSUMMON)				// ��� ��ȯ ī��
#define T_FC_ITEM_USE_CARDITEM_GUILDSUMMON_NOTIFY		(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_USE_CARDITEM_GUILDSUMMON_NOTIFY)			// ��� ��ȯ ī��� ��ȯ���� �˸�
#define T_FC_ITEM_USE_CARDITEM_RESTORE					(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_USE_CARDITEM_RESTORE)					// ��Ȱ ī��
#define T_FC_ITEM_USE_CARDITEM_RESTORE_NOTIFY			(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_USE_CARDITEM_RESTORE_NOTIFY)				// ��Ȱ ī��� ��Ȱ���� �˸�
#define T_FC_ITEM_USE_CARDITEM_GUILD					(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_USE_CARDITEM_GUILD)					// �Ϲ�/���� ���� ī��
#define T_FC_ITEM_USE_CARDITEM_GUILD_NOTIFY				(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_USE_CARDITEM_GUILD_NOTIFY)			// �Ϲ�/���� ���� ī��
#define T_FC_ITEM_USE_CARDITEM_MONSTERSUMMON			(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_USE_CARDITEM_MONSTERSUMMON)			// ���� ��ȯ ī��
#define T_FC_ITEM_USE_CARDITEM_MONSTERSUMMON_NOTIFY		(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_USE_CARDITEM_MONSTERSUMMON_NOTIFY)	// ���� ��ȯ ī��
#define T_FC_ITEM_USE_CARDITEM_CHANGECHARACTERNAME		(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_USE_CARDITEM_CHANGECHARACTERNAME)	// ĳ���� �̸� ���� ī��
#define T_FC_ITEM_USE_CARDITEM_CHANGECHARACTERNAME_NOTIFY	(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_USE_CARDITEM_CHANGECHARACTERNAME_NOTIFY)	// ĳ���� �̸� ���� ī��
#define T_FC_ITEM_USE_CARDITEM_SKILLINITIALIZE			(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_USE_CARDITEM_SKILLINITIALIZE)		// ��ų �ʱ�ȭ ī��
#define T_FC_ITEM_USE_CARDITEM_SKILLINITIALIZE_NOTIFY	(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_USE_CARDITEM_SKILLINITIALIZE_NOTIFY)	// ��ų �ʱ�ȭ ī��
#define T_FC_ITEM_USE_CARDITEM_CHANGEPILOTFACE			(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_USE_CARDITEM_CHANGEPILOTFACE)		// �� ���� ī��
#define T_FC_ITEM_USE_CARDITEM_CHANGEPILOTFACE_NOTIFY	(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_USE_CARDITEM_CHANGEPILOTFACE_NOTIFY)	// �� ���� ī��
#define T_FC_ITEM_USE_INFLUENCE_BUFF					(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_USE_INFLUENCE_BUFF)			// C->F, ���� ����		// 2006-04-21 by cmkwon
#define T_FC_ITEM_USE_INFLUENCE_BUFF_OK					(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_USE_INFLUENCE_BUFF_OK)		// F->C					// 2006-04-21 by cmkwon
#define T_FC_ITEM_USE_INFLUENCE_GAMEEVENT				(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_USE_INFLUENCE_GAMEEVENT)		// C->F, ���� �̺�Ʈ	// 2006-04-21 by cmkwon
#define T_FC_ITEM_USE_INFLUENCE_GAMEEVENT_OK			(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_USE_INFLUENCE_GAMEEVENT_OK)	// F->C					 // 2006-04-21 by cmkwon
#define T_FC_ITEM_USE_RANDOMBOX							(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_USE_RANDOMBOX)		// C->F, 2006-08-10 by cmkwon
#define T_FC_ITEM_USE_RANDOMBOX_OK						(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_USE_RANDOMBOX_OK)	// F->C(n), 2006-08-10 by cmkwon
#define T_FC_ITEM_USE_SKILL_SUPPORT_ITEM				(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_USE_SKILL_SUPPORT_ITEM)		// C->F, 2006-09-29 by cmkwon
#define T_FC_ITEM_USE_SKILL_SUPPORT_ITEM_OK				(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_USE_SKILL_SUPPORT_ITEM_OK)	// F->C, 2006-09-29 by cmkwon
#define T_FC_ITEM_USE_RANDOMBOX_OK_DONE					(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_USE_RANDOMBOX_OK_DONE)		// F->C, // 2008-08-26 by cmkwon, ItemAttribute �߰� - ��Ű��(Package) ������, (no body) Ŭ���̾�Ʈ�� �� �޽����� �ް� �����¸� ���� �Ѵ�.
#define T_FC_ITEM_USE_LUCKY_ITEM						(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_USE_LUCKY_ITEM)			// C->F, 2008-11-04 by dhjin, ��Ű�ӽ�
#define T_FC_ITEM_USE_LUCKY_ITEM_OK						(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_USE_LUCKY_ITEM_OK)		// F->C, 2008-11-04 by dhjin, ��Ű�ӽ�
#define T_FC_ITEM_CHANGED_SHAPEITEMNUM					(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_CHANGED_SHAPEITEMNUM)	// F->C, // 2009-08-26 by cmkwon, �׷��� ���ҽ� ���� �ý��� ���� - 
#define T_FC_ITEM_CHANGED_EFFECTITEMNUM					(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_CHANGED_EFFECTITEMNUM)	// F->C, // 2009-08-26 by cmkwon, �׷��� ���ҽ� ���� �ý��� ���� - 
#define T_FC_ITEM_USE_PET_SOCKET_ITEM					(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_USE_PET_SOCKET_ITEM)			// C->F, // 2011-09-20 by hskim, ��Ʈ�� �ý��� 2��
#define T_FC_ITEM_USE_PET_SOCKET_ITEM_OK				(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_USE_PET_SOCKET_ITEM_OK)		// F->C, // 2011-09-20 by hskim, ��Ʈ�� �ý��� 2��
#define T_FC_ITEM_CANCEL_PET_SOCKET_ITEM				(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_CANCEL_PET_SOCKET_ITEM)		// C->F, // 2011-09-20 by hskim, ��Ʈ�� �ý��� 2��
#define T_FC_ITEM_CANCEL_PET_SOCKET_ITEM_OK				(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_CANCEL_PET_SOCKET_ITEM_OK)	// F->C, // 2011-09-20 by hskim, ��Ʈ�� �ý��� 2��
#define T_FC_ITEM_NOTIFY_WINDOW_POSITION				(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_NOTIFY_WINDOW_POSITION)		// F->C, // 2011-09-20 by hskim, ��Ʈ�� �ý��� 2��

// 2014-06-10 by bckim, ���º��� ������
#define T_FC_ITEM_USE_CARDITEM_CHANGE_INFLUENCE			(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_USE_CARDITEM_CHANGE_INFLUENCE)			// ���º��� ī��
#define T_FC_ITEM_USE_CARDITEM_CHANGE_INFLUENCE_NOTIFY	(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_USE_CARDITEM_CHANGE_INFLUENCE_NOTIFY)	// ���º��� ī��
// End. 2014-06-10 by bckim, ���º��� ������

#define T_FC_SHOP_PUT_ITEM_HEADER				(MessageType_t)((T0_FC_SHOP<<8)|T1_FC_SHOP_PUT_ITEM_HEADER)
#define T_FC_SHOP_PUT_ITEM						(MessageType_t)((T0_FC_SHOP<<8)|T1_FC_SHOP_PUT_ITEM)
#define T_FC_SHOP_PUT_ITEM_DONE					(MessageType_t)((T0_FC_SHOP<<8)|T1_FC_SHOP_PUT_ITEM_DONE)
#define T_FC_SHOP_GET_ITEMINFO					(MessageType_t)((T0_FC_SHOP<<8)|T1_FC_SHOP_GET_ITEMINFO)
#define T_FC_SHOP_GET_ITEMINFO_OK				(MessageType_t)((T0_FC_SHOP<<8)|T1_FC_SHOP_GET_ITEMINFO_OK)
#define T_FC_SHOP_BUY_ITEM						(MessageType_t)((T0_FC_SHOP<<8)|T1_FC_SHOP_BUY_ITEM)
#define T_FC_SHOP_BUY_ITEM_OK					(MessageType_t)((T0_FC_SHOP<<8)|T1_FC_SHOP_BUY_ITEM_OK)
#define T_FC_SHOP_BUY_ITEM_UPDATE				(MessageType_t)((T0_FC_SHOP<<8)|T1_FC_SHOP_BUY_ITEM_UPDATE)						// F->C, // 2011-12-26 by hskim, EP4 [Ʈ���� �ý���] - ũ����Ż �ý���
#define T_FC_SHOP_SELL_ITEM						(MessageType_t)((T0_FC_SHOP<<8)|T1_FC_SHOP_SELL_ITEM)
#define T_FC_SHOP_SELL_ITEM_OK					(MessageType_t)((T0_FC_SHOP<<8)|T1_FC_SHOP_SELL_ITEM_OK)
#define T_FC_SHOP_GET_USED_ITEM_PRICE			(MessageType_t)((T0_FC_SHOP<<8)|T1_FC_SHOP_GET_USED_ITEM_PRICE)
#define T_FC_SHOP_GET_USED_ITEM_PRICE_OK		(MessageType_t)((T0_FC_SHOP<<8)|T1_FC_SHOP_GET_USED_ITEM_PRICE_OK)
#define T_FC_SHOP_GET_SHOP_ITEM_LIST			(MessageType_t)((T0_FC_SHOP<<8)|T1_FC_SHOP_GET_SHOP_ITEM_LIST)		// C->F, �������� �Ĵ� �������� ����Ʈ�� ��û, ������ T_FC_SHOP_PUT_ITEM_XXX
#define T_FC_SHOP_REQUEST_REPAIR				(MessageType_t)((T0_FC_SHOP<<8)|T1_FC_SHOP_REQUEST_REPAIR)			// C->F, ��ü ���� ��û, 2005-11-08 by cmkwon
#define T_FC_SHOP_REQUEST_REPAIR_OK				(MessageType_t)((T0_FC_SHOP<<8)|T1_FC_SHOP_REQUEST_REPAIR_OK)		// F->C, ��ü ���� ��û ����
#define T_FC_SHOP_BUY_CASH_ITEM					(MessageType_t)((T0_FC_SHOP<<8)|T1_FC_SHOP_BUY_CASH_ITEM)			// C->F, ���� ������ ����
#define T_FC_SHOP_BUY_CASH_ITEM_OK				(MessageType_t)((T0_FC_SHOP<<8)|T1_FC_SHOP_BUY_CASH_ITEM_OK)		// F->C, // 2007-11-13 by cmkwon, �����ϱ� ��� �߰� -���� ������ ���� ����
#define T_FC_SHOP_BUY_COLOR_ITEM				(MessageType_t)((T0_FC_SHOP<<8)|T1_FC_SHOP_BUY_COLOR_ITEM)			// C->F, ���� ������ ����// 2005-12-06 by cmkwon
#define T_FC_SHOP_BUY_COLOR_ITEM_OK				(MessageType_t)((T0_FC_SHOP<<8)|T1_FC_SHOP_BUY_COLOR_ITEM_OK)			// F->C, ���� ������ ���� ����// 2005-12-06 by cmkwon
#define T_FC_SHOP_BUY_WARPOINT_ITEM				(MessageType_t)((T0_FC_SHOP<<8)|T1_FC_SHOP_BUY_WARPOINT_ITEM)			// C->F, WarPoint ������ ���� // 2007-06-13 by dhjin
#define T_FC_SHOP_BUY_WARPOINT_ITEM_OK			(MessageType_t)((T0_FC_SHOP<<8)|T1_FC_SHOP_BUY_WARPOINT_ITEM_OK)		// F->C, // 2007-06-13 by dhjin
#define T_FC_SHOP_CHECK_GIVE_TARGET				(MessageType_t)((T0_FC_SHOP<<8)|T1_FC_SHOP_CHECK_GIVE_TARGET)		// C->F, // 2007-11-13 by cmkwon, �����ϱ� ��� �߰� - �����޴� ĳ���� üũ ��û ��������
#define T_FC_SHOP_CHECK_GIVE_TARGET_OK			(MessageType_t)((T0_FC_SHOP<<8)|T1_FC_SHOP_CHECK_GIVE_TARGET_OK)	// F->C, // 2007-11-13 by cmkwon, �����ϱ� ��� �߰� -
#define T_FC_SHOP_CLOSE							(MessageType_t)((T0_FC_SHOP<<8)|T1_FC_SHOP_CLOSE)					// F->C, // 2011-10-28 by hskim, EP4 [Ʈ���� �ý���] - ũ����Ż �ý���
#define T_FC_SHOP_INFLUENCE_BUFF				(MessageType_t)((T0_FC_SHOP<<8)|T1_FC_SHOP_INFLUENCE_BUFF)			// C->F, // 2013-05-09 by hskim, ���� ����Ʈ ����
#define T_FC_SHOP_INFLUENCE_BUFF_OK				(MessageType_t)((T0_FC_SHOP<<8)|T1_FC_SHOP_INFLUENCE_BUFF_OK)		// F->C, // 2013-05-09 by hskim, ���� ����Ʈ ����

#define T_FC_TRADE_REQUEST_TRADE				(MessageType_t)((T0_FC_TRADE<<8)|T1_FC_TRADE_REQUEST_TRADE)
#define T_FC_TRADE_REQUEST_TRADE_OK				(MessageType_t)((T0_FC_TRADE<<8)|T1_FC_TRADE_REQUEST_TRADE_OK)
#define T_FC_TRADE_CANCEL_REQUEST				(MessageType_t)((T0_FC_TRADE<<8)|T1_FC_TRADE_CANCEL_REQUEST)
#define T_FC_TRADE_CANCEL_REQUEST_OK			(MessageType_t)((T0_FC_TRADE<<8)|T1_FC_TRADE_CANCEL_REQUEST_OK)
#define T_FC_TRADE_ACCEPT_TRADE					(MessageType_t)((T0_FC_TRADE<<8)|T1_FC_TRADE_ACCEPT_TRADE)
#define T_FC_TRADE_ACCEPT_TRADE_OK				(MessageType_t)((T0_FC_TRADE<<8)|T1_FC_TRADE_ACCEPT_TRADE_OK)
#define T_FC_TRADE_REJECT_TRADE					(MessageType_t)((T0_FC_TRADE<<8)|T1_FC_TRADE_REJECT_TRADE)
#define T_FC_TRADE_REJECT_TRADE_OK				(MessageType_t)((T0_FC_TRADE<<8)|T1_FC_TRADE_REJECT_TRADE_OK)
#define T_FC_TRADE_REJECT_TRADING				(MessageType_t)((T0_FC_TRADE<<8)|T1_FC_TRADE_REJECT_TRADING)
#define T_FC_TRADE_SHOW_TRADE_WINDOW			(MessageType_t)((T0_FC_TRADE<<8)|T1_FC_TRADE_SHOW_TRADE_WINDOW)
#define T_FC_TRADE_TRANS_ITEM					(MessageType_t)((T0_FC_TRADE<<8)|T1_FC_TRADE_TRANS_ITEM)
#define T_FC_TRADE_TRANS_ITEM_OK				(MessageType_t)((T0_FC_TRADE<<8)|T1_FC_TRADE_TRANS_ITEM_OK)
#define T_FC_TRADE_SEE_ITEM						(MessageType_t)((T0_FC_TRADE<<8)|T1_FC_TRADE_SEE_ITEM)
#define T_FC_TRADE_SEE_ITEM_OK					(MessageType_t)((T0_FC_TRADE<<8)|T1_FC_TRADE_SEE_ITEM_OK)
#define T_FC_TRADE_OK_TRADE						(MessageType_t)((T0_FC_TRADE<<8)|T1_FC_TRADE_OK_TRADE)
#define T_FC_TRADE_OK_TRADE_OK					(MessageType_t)((T0_FC_TRADE<<8)|T1_FC_TRADE_OK_TRADE_OK)
#define T_FC_TRADE_CANCEL_TRADE					(MessageType_t)((T0_FC_TRADE<<8)|T1_FC_TRADE_CANCEL_TRADE)
#define T_FC_TRADE_CANCEL_TRADE_OK				(MessageType_t)((T0_FC_TRADE<<8)|T1_FC_TRADE_CANCEL_TRADE_OK)
#define T_FC_TRADE_INSERT_ITEM					(MessageType_t)((T0_FC_TRADE<<8)|T1_FC_TRADE_INSERT_ITEM)
#define T_FC_TRADE_DELETE_ITEM					(MessageType_t)((T0_FC_TRADE<<8)|T1_FC_TRADE_DELETE_ITEM)
#define T_FC_TRADE_UPDATE_ITEM_COUNT			(MessageType_t)((T0_FC_TRADE<<8)|T1_FC_TRADE_UPDATE_ITEM_COUNT)
#define T_FC_TRADE_OK_TRADE_NOTIFY				(MessageType_t)((T0_FC_TRADE<<8)|T1_FC_TRADE_OK_TRADE_NOTIFY)	// 2008-11-21 by cmkwon, �ŷ� ���� Ȯ�� �ý��� ���� - F->C(2)
#define T_FC_TRADE_SEE_PET_DATA					(MessageType_t)((T0_FC_TRADE<<8)|T1_FC_TRADE_SEE_PET_DATA)				// 2010-06-15 by shcho&hslee ��ý��� - �ŷ� �� �� ���� ����
#define T_FC_TRADE_DELETE_CURRENT_PET_DATA		(MessageType_t)((T0_FC_TRADE<<8)|T1_FC_TRADE_DELETE_CURRENT_PET_DATA)	// 2010-06-15 by shcho&hslee ��ý��� - �ŷ� �� �� ���� ����
#define T_FC_TRADE_INSERT_CURRENT_PET_DATA 		(MessageType_t)((T0_FC_TRADE<<8)|T1_FC_TRADE_INSERT_CURRENT_PET_DATA)	// 2010-06-15 by shcho&hslee ��ý��� - �ŷ� �� �� ���� ����
// T0_FC_COUNTDOWN
#define T_FC_COUNTDOWN_START					(MessageType_t)((T0_FC_COUNTDOWN<<8)|T1_FC_COUNTDOWN_START)	// F -> C
#define T_FC_COUNTDOWN_DONE						(MessageType_t)((T0_FC_COUNTDOWN<<8)|T1_FC_COUNTDOWN_DONE)	// C -> F

// T0_FC_OBJECT
#define T_FC_OBJECT_CHANGE_BODYCONDITION		(MessageType_t)((T0_FC_OBJECT<<8)|T1_FC_OBJECT_CHANGE_BODYCONDITION)	// C -> F
#define T_FC_OBJECT_CHANGE_BODYCONDITION_OK		(MessageType_t)((T0_FC_OBJECT<<8)|T1_FC_OBJECT_CHANGE_BODYCONDITION_OK)	// F -> C(n)
#define T_FC_OBJECT_CHANGE						(MessageType_t)((T0_FC_OBJECT<<8)|T1_FC_OBJECT_CHANGE)					// F -> C(n), 2011-11-07 by hskim, EP4 [Ʈ���� �ý���] - ũ����Ż �ý���

#define T_FC_AUCTION_REGISTER_ITEM				(MessageType_t)((T0_FC_AUCTION<<8)|T1_FC_AUCTION_REGISTER_ITEM)			// C->F, ��� ������ ���
#define T_FC_AUCTION_REGISTER_ITEM_OK			(MessageType_t)((T0_FC_AUCTION<<8)|T1_FC_AUCTION_REGISTER_ITEM_OK)		// F->C, ��� ������ ��� ���
#define T_FC_AUCTION_CANCEL_REGISTER			(MessageType_t)((T0_FC_AUCTION<<8)|T1_FC_AUCTION_CANCEL_REGISTER)		// C->F, ��� ������ ��� ���
#define T_FC_AUCTION_CANCEL_REGISTER_OK			(MessageType_t)((T0_FC_AUCTION<<8)|T1_FC_AUCTION_CANCEL_REGISTER_OK)	// F->C, ��� ������ ��� ��� ���
#define T_FC_AUCTION_BUY_ITEM					(MessageType_t)((T0_FC_AUCTION<<8)|T1_FC_AUCTION_BUY_ITEM)				// C->F, ��� ������ ����
#define T_FC_AUCTION_BUY_ITEM_OK				(MessageType_t)((T0_FC_AUCTION<<8)|T1_FC_AUCTION_BUY_ITEM_OK)			// F->C, ��� ������ ���� ���
#define T_FC_AUCTION_GET_ITEM_LIST				(MessageType_t)((T0_FC_AUCTION<<8)|T1_FC_AUCTION_GET_ITEM_LIST)			// C->F, ��� ������ ��� ��û
#define T_FC_AUCTION_INSERT_ITEM				(MessageType_t)((T0_FC_AUCTION<<8)|T1_FC_AUCTION_INSERT_ITEM)			// F->C, ��� ������ ��� ���ۿ�
#define T_FC_AUCTION_PUT_ENCHANT				(MessageType_t)((T0_FC_AUCTION<<8)|T1_FC_AUCTION_PUT_ENCHANT)			// F->C, ��� �������� ��æƮ ���� ���ۿ�

#define T_FC_GUILD_GET_MAP_OWNER_INFO			(MessageType_t)((T0_FC_GUILD<<8)|T1_FC_GUILD_GET_MAP_OWNER_INFO)		// C->F, �� ���� ���� ��û
#define T_FC_GUILD_GET_MAP_OWNER_INFO_OK		(MessageType_t)((T0_FC_GUILD<<8)|T1_FC_GUILD_GET_MAP_OWNER_INFO_OK)		// F->C, �� ���� ���� ��û ���
#define T_FC_GUILD_REQUEST_GUILD_WAR			(MessageType_t)((T0_FC_GUILD<<8)|T1_FC_GUILD_REQUEST_GUILD_WAR)			// C->F, ������ ��û
#define T_FC_GUILD_REQUEST_GUILD_WAR_RESULT		(MessageType_t)((T0_FC_GUILD<<8)|T1_FC_GUILD_REQUEST_GUILD_WAR_RESULT)	// F->C, ������ ��û ���
#define T_FC_GUILD_GET_CHALLENGER_GUILD			(MessageType_t)((T0_FC_GUILD<<8)|T1_FC_GUILD_GET_CHALLENGER_GUILD)		// C->F, ������ ��û ��� ��� ����Ʈ ��û
#define T_FC_GUILD_GET_CHALLENGER_GUILD_OK		(MessageType_t)((T0_FC_GUILD<<8)|T1_FC_GUILD_GET_CHALLENGER_GUILD_OK)	// F->C, ������ ��û ��� ��� ����Ʈ ��û ���
#define T_FC_GUILD_GET_WAR_INFO					(MessageType_t)((T0_FC_GUILD<<8)|T1_FC_GUILD_GET_WAR_INFO)				// C->F, ������ ������ ��û
#define T_FC_GUILD_GET_WAR_INFO_OK				(MessageType_t)((T0_FC_GUILD<<8)|T1_FC_GUILD_GET_WAR_INFO_OK)			// F->C, ������ ������ ����
// 2004-12-10 by cmkwon, IM Server���� ó���Ѵ�, �������� ������
//#define T_FC_GUILD_SURRENDER_GUILD_WAR			(MessageType_t)((T0_FC_GUILD<<8)|T1_FC_GUILD_SURRENDER_GUILD_WAR)		// C->F, ������ �׺�, No Body
#define T_FC_GUILD_SUMMON_MEMBER				(MessageType_t)((T0_FC_GUILD<<8)|T1_FC_GUILD_SUMMON_MEMBER)	// F->C
#define T_FC_GUILD_SUMMON_MEMBER_OK				(MessageType_t)((T0_FC_GUILD<<8)|T1_FC_GUILD_SUMMON_MEMBER_OK)	// C(n)->F
#define T_FC_GUILD_DISMEMBER					(MessageType_t)((T0_FC_GUILD<<8)|T1_FC_GUILD_DISMEMBER)	// C->F

#define T_FI_GUILD_NOTIFY_START_WAR				(MessageType_t)((T0_FI_GUILD<<8)|T1_FI_GUILD_NOTIFY_START_WAR)			// F->I
#define T_FI_GUILD_NOTIFY_END_WAR				(MessageType_t)((T0_FI_GUILD<<8)|T1_FI_GUILD_NOTIFY_END_WAR)			// I->F
#define T_FI_GUILD_DELETE_GUILD					(MessageType_t)((T0_FI_GUILD<<8)|T1_FI_GUILD_DELETE_GUILD)				// F->I
#define T_FI_GUILD_ADD_GUILD_FAME				(MessageType_t)((T0_FI_GUILD<<8)|T1_FI_GUILD_ADD_GUILD_FAME)		// F->I, // 2005-12-27 by cmkwon
#define T_FI_GUILD_REG_DELETE_GUILD				(MessageType_t)((T0_FI_GUILD<<8)|T1_FI_GUILD_REG_DELETE_GUILD)			// I->F
// 2007-11-12 by dhjin, T_IC_GUILD_DISMEMBER => T_FI_GUILD_DISMEMBER �� ����
#define T_FI_GUILD_DISMEMBER					(MessageType_t)((T0_FI_GUILD<<8)|T1_FI_GUILD_DISMEMBER)				// F->I, ���� ��ü
#define T_FI_GUILD_OUTPOST						(MessageType_t)((T0_FI_GUILD<<8)|T1_FI_GUILD_OUTPOST)				// F->I, // 2008-05-20 by dhjin, EP3 - ���� ���� ���� - �������� ����
// 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������
#define T_FI_GUILD_BONUS_EXP_RATE				(MessageType_t)((T0_FI_GUILD<<8)|T1_FI_GUILD_BONUS_EXP_RATE)		// F->I, jhjang
// 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������


#define T_IC_GUILD_CREATE						(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_CREATE)				// C->I, ��� ���� ��û
#define T_IC_GUILD_CREATE_OK					(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_CREATE_OK)				// I->C, ��� ���� ���
#define T_IC_GUILD_GET_GUILD_INFO				(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_GET_GUILD_INFO)		// C->I, ��� ���� ��û
#define T_IC_GUILD_GET_GUILD_INFO_OK			(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_GET_GUILD_INFO_OK)		// I->C, ��� ���� ���
#define T_IC_GUILD_GET_OTHER_GUILD_INFO			(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_GET_OTHER_GUILD_INFO)		// C->I, �ٸ� ��� ���� ��û
#define T_IC_GUILD_GET_OTHER_GUILD_INFO_OK		(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_GET_OTHER_GUILD_INFO_OK)	// I->C, �ٸ� ��� ���� ���
#define T_IC_GUILD_REQUEST_INVITE				(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_REQUEST_INVITE)		// C->I, ���� ����, ������ ��û
#define T_IC_GUILD_REQUEST_INVITE_QUESTION		(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_REQUEST_INVITE_QUESTION)	// I->C, ���� ����, ����ڿ��� ����
#define T_IC_GUILD_ACCEPT_INVITE				(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_ACCEPT_INVITE)			// C->I, ���� �³�, ������ ��û
#define T_IC_GUILD_ACCEPT_INVITE_OK				(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_ACCEPT_INVITE_OK)		// I->C, ���� �³�, �������� ����
#define T_IC_GUILD_REJECT_INVITE				(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_REJECT_INVITE)			// C->I, ���� �ź�, ������ ��û
#define T_IC_GUILD_REJECT_INVITE_OK				(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_REJECT_INVITE_OK)		// I->C, ���� �ź�, ����ڿ��� ����
#define T_IC_GUILD_BAN_MEMBER					(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_BAN_MEMBER)			// C->I, ���� �߹�
#define T_IC_GUILD_BAN_MEMBER_OK				(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_BAN_MEMBER_OK)			// I->C, ���� �߹� ���
#define T_IC_GUILD_LEAVE						(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_LEAVE)					// C->I, ���� Ż��
#define T_IC_GUILD_LEAVE_OK						(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_LEAVE_OK)				// I->C, ���� Ż�� ���
// 2007-11-12 by dhjin, FI�� ����
//#define T_IC_GUILD_DISMEMBER					(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_DISMEMBER)				// C->I, ���� ��ü
#define T_IC_GUILD_DISMEMBER_OK					(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_DISMEMBER_OK)			// I->C, ���� ��ü ���
#define T_IC_GUILD_SET_MEMBER_STATE				(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_SET_MEMBER_STATE)		// I->C, ������ ���� ��ȭ(ONLINE, OFFLINE ��)
#define T_IC_GUILD_CANCEL_DISMEMBER				(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_CANCEL_DISMEMBER)		// C->I, ���� ��ü ��� ��û
#define T_IC_GUILD_CANCEL_DISMEMBER_OK			(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_CANCEL_DISMEMBER_OK)	// I->C, ���� ��ü ��� ���
#define T_IC_GUILD_GET_DISMEMBER_DATE			(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_GET_DISMEMBER_DATE)	// C->I, ��� �ػ� �ð� ��û
#define T_IC_GUILD_GET_DISMEMBER_DATE_OK		(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_GET_DISMEMBER_DATE_OK)	// I->C, ��� �ػ� �ð� ���
#define T_IC_GUILD_CHANGE_GUILD_NAME			(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_CHANGE_GUILD_NAME)		// C->I, ���� �̸� ���� ��û
#define T_IC_GUILD_CHANGE_GUILD_NAME_OK			(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_CHANGE_GUILD_NAME_OK)	// I->C, ���� �̸� ���� ���
#define T_IC_GUILD_GET_GUILD_MARK				(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_GET_GUILD_MARK)		// C->I, ���� ���� ��û
#define T_IC_GUILD_GET_GUILD_MARK_OK			(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_GET_GUILD_MARK_OK)		// I->C, ���� ���� ���
#define T_IC_GUILD_SET_GUILD_MARK				(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_SET_GUILD_MARK)		// C->I, ���� ���� ���� ��û
#define T_IC_GUILD_SET_GUILD_MARK_OK			(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_SET_GUILD_MARK_OK)		// I->C, ���� ���� ���� ���
#define T_IC_GUILD_SET_RANK						(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_SET_RANK)				// C->I, ��� ����
#define T_IC_GUILD_SET_RANK_OK					(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_SET_RANK_OK)			// I->C, ��� ���� ���
#define T_IC_GUILD_CHANGE_GUILD_STATE			(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_CHANGE_GUILD_STATE)	// I->C, ���� ���� ����
#define T_IC_GUILD_LOADING_GUILD_DONE			(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_LOADING_GUILD_DONE)	// I->C, ���������� ��� ���� �ε� �Ϸ� �˸�
#define T_IC_GUILD_WAR_READY					(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_WAR_READY)				// I->C, ������ ���� ��� ���¸� �˸�
#define T_IC_GUILD_START_WAR					(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_START_WAR)				// I->C, ������ ������ �˸�
#define T_IC_GUILD_END_WAR						(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_END_WAR)				// I->C, ������ ���Ḧ �˸�
#define T_IC_GUILD_UPDATE_WAR_POINT				(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_UPDATE_WAR_POINT)		// I->C, ������ ������ ��������и� DB Update���Ŀ� �������� ����
#define T_IC_GUILD_SURRENDER_GUILD_WAR			(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_SURRENDER_GUILD_WAR)	// C->I, ������ �׺�
#define T_IC_GUILD_CHANGE_MEMBER_CAPACITY		(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_CHANGE_MEMBER_CAPACITY)	// I->C, ���� ���� �ο� ����
#define T_IC_GUILD_GET_GUILD_MEMBER_LIST_OK		(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_GET_GUILD_MEMBER_LIST_OK)	// I->C, ���ܿ� ����Ʈ
#define T_IC_GUILD_END_WAR_ADMIN_NOTIFY			(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_END_WAR_ADMIN_NOTIFY)		// I->C(n)
#define T_IC_GUILD_MEMBER_LEVEL_UP				(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_MEMBER_LEVEL_UP)			// I->C(n), // 2008-05-20 by dhjin, EP3 - ���� ���� ���� - ���ܿ� ������ ����
#define T_IC_GUILD_NEW_COMMANDER				(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_NEW_COMMANDER)				// C->I, // 2008-05-20 by dhjin, EP3 - ���� ���� ���� - ������ ����
#define T_IC_GUILD_NOTICE_WRITE					(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_NOTICE_WRITE)				// C->I, // 2008-05-20 by dhjin, EP3 - ���� ���� ���� - ���� ���� �ۼ�
#define T_IC_GUILD_NOTICE_WRITE_OK				(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_NOTICE_WRITE_OK)			// I->C, // 2008-05-20 by dhjin, EP3 - ���� ���� ���� - ���� ���� �ۼ� OK
#define T_IC_GUILD_GET_APPLICANT				(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_GET_APPLICANT)				// C->I, // 2008-05-27 by dhjin, EP3 - ���� ���� ���� - ���� ������ ����
#define T_IC_GUILD_GET_APPLICANT_OK_HEADER		(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_GET_APPLICANT_OK_HEADER)	// I->C, // 2008-05-27 by dhjin, EP3 - ���� ���� ���� - ���� ������ ���� OK
#define T_IC_GUILD_GET_APPLICANT_OK				(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_GET_APPLICANT_OK)			// I->C, // 2008-05-27 by dhjin, EP3 - ���� ���� ���� - ���� ������ ���� OK
#define T_IC_GUILD_GET_APPLICANT_OK_DONE		(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_GET_APPLICANT_OK_DONE)		// I->C, // 2008-05-27 by dhjin, EP3 - ���� ���� ���� - ���� ������ ���� OK
#define T_IC_GUILD_GET_INTRODUCTION				(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_GET_INTRODUCTION)			// C->I, // 2008-05-27 by dhjin, EP3 - ���� ���� ���� - ���� �Ұ�
#define T_IC_GUILD_GET_INTRODUCTION_OK			(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_GET_INTRODUCTION_OK)		// I->C, // 2008-05-27 by dhjin, EP3 - ���� ���� ���� - ���� �Ұ� ok
#define T_IC_GUILD_GET_SELF_INTRODUCTION		(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_GET_SELF_INTRODUCTION)		// C->I, // 2008-05-27 by dhjin, EP3 - ���� ���� ���� - ���� ������ �Ұ��� 
#define T_IC_GUILD_GET_SELF_INTRODUCTION_OK		(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_GET_SELF_INTRODUCTION_OK)	// I->C, // 2008-05-27 by dhjin, EP3 - ���� ���� ���� - ���� ������ �Ұ��� OK
#define T_IC_GUILD_SEARCH_INTRODUCTION				(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_SEARCH_INTRODUCTION)			// C->I, // 2008-05-27 by dhjin, EP3 - ���� ���� ���� - ���� �Ұ� �˻� 
#define T_IC_GUILD_SEARCH_INTRODUCTION_OK_HEADER	(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_SEARCH_INTRODUCTION_OK_HEADER)	// I->C, // 2008-05-27 by dhjin, EP3 - ���� ���� ���� - ���� �Ұ� �˻� OK
#define T_IC_GUILD_SEARCH_INTRODUCTION_OK			(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_SEARCH_INTRODUCTION_OK)		// I->C, // 2008-05-27 by dhjin, EP3 - ���� ���� ���� - ���� �Ұ� �˻� OK
#define T_IC_GUILD_SEARCH_INTRODUCTION_OK_DONE		(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_SEARCH_INTRODUCTION_OK_DONE)	// I->C, // 2008-05-27 by dhjin, EP3 - ���� ���� ���� - ���� �Ұ� �˻� OK
#define T_IC_GUILD_UPDATE_INTRODUCTION			(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_UPDATE_INTRODUCTION)			// C->I, // 2008-05-27 by dhjin, EP3 - ���� ���� ���� - ���� �Ұ� �ۼ� 
#define T_IC_GUILD_UPDATE_INTRODUCTION_OK		(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_UPDATE_INTRODUCTION_OK)		// I->C, // 2008-05-27 by dhjin, EP3 - ���� ���� ���� - ���� �Ұ� �ۼ� OK
#define T_IC_GUILD_DELETE_INTRODUCTION			(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_DELETE_INTRODUCTION)			// C->I, // 2008-05-27 by dhjin, EP3 - ���� ���� ���� - ���� �Ұ� �����  
#define T_IC_GUILD_DELETE_INTRODUCTION_OK		(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_DELETE_INTRODUCTION_OK)		// I->C, // 2008-05-27 by dhjin, EP3 - ���� ���� ���� - ���� �Ұ� ����� OK
#define T_IC_GUILD_UPDATE_SELFINTRODUCTION		(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_UPDATE_SELFINTRODUCTION)		// C->I, // 2008-05-27 by dhjin, EP3 - ���� ���� ���� - �ڱ� �Ұ� �ۼ� 
#define T_IC_GUILD_UPDATE_SELFINTRODUCTION_OK	(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_UPDATE_SELFINTRODUCTION_OK)	// I->C, // 2008-05-27 by dhjin, EP3 - ���� ���� ���� - �ڱ� �Ұ� �ۼ� OK
#define T_IC_GUILD_DELETE_SELFINTRODUCTION		(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_DELETE_SELFINTRODUCTION)		// C->I, // 2008-05-27 by dhjin, EP3 - ���� ���� ���� - �ڱ� �Ұ� �����  
#define T_IC_GUILD_DELETE_SELFINTRODUCTION_OK	(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_DELETE_SELFINTRODUCTION_OK)	// I->C, // 2008-05-27 by dhjin, EP3 - ���� ���� ���� - �ڱ� �Ұ� ����� OK
#define T_IC_GUILD_CHANGE_FAME_RANK				(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_CHANGE_FAME_RANK)				// I->C, // 2008-06-10 by dhjin, EP3 - ���� ���� ���� - ���� ���� ����
#define T_IC_GUILD_APPLICANT_INVITE				(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_APPLICANT_INVITE)				// C->I, // 2008-06-12 by dhjin, EP3 - ���� ���� ���� - ������ �������� ���ܿ� �ʴ�
#define T_IC_GUILD_APPLICANT_INVITE_OK			(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_APPLICANT_INVITE_OK)			// I->C, // 2008-06-12 by dhjin, EP3 - ���� ���� ���� - ������ �������� ���ܿ� �ʴ� OK
#define T_IC_GUILD_APPLICANT_REJECT_INVITE		(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_APPLICANT_REJECT_INVITE)		// C->I, // 2008-06-12 by dhjin, EP3 - ���� ���� ���� - ������ �������� ���ܿ� �ʴ� �ź� 
#define T_IC_GUILD_APPLICANT_REJECT_INVITE_OK	(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_APPLICANT_REJECT_INVITE_OK)	// I->C, // 2008-06-12 by dhjin, EP3 - ���� ���� ���� - ������ �������� ���ܿ� �ʴ� �ź� OK
#define T_IC_GUILD_CHANGE_MEMBERSHIP			(MessageType_t)((T0_IC_GUILD<<8)|T1_IC_GUILD_CHANGE_MEMBERSHIP)				// I->C, // 2008-06-20 by dhjin, EP3 - ���� ���� ���� - ������ �ɹ��� ���� ����

#define T_FC_SKILL_USE_SKILLPOINT				(MessageType_t)((T0_FC_SKILL<<8)|T1_FC_SKILL_USE_SKILLPOINT)
#define T_FC_SKILL_USE_SKILLPOINT_OK			(MessageType_t)((T0_FC_SKILL<<8)|T1_FC_SKILL_USE_SKILLPOINT_OK)
#define T_FC_SKILL_SETUP_SKILL					(MessageType_t)((T0_FC_SKILL<<8)|T1_FC_SKILL_SETUP_SKILL)
#define T_FC_SKILL_SETUP_SKILL_OK_HEADER		(MessageType_t)((T0_FC_SKILL<<8)|T1_FC_SKILL_SETUP_SKILL_OK_HEADER)
#define T_FC_SKILL_SETUP_SKILL_OK				(MessageType_t)((T0_FC_SKILL<<8)|T1_FC_SKILL_SETUP_SKILL_OK)
#define T_FC_SKILL_SETUP_SKILL_OK_DONE			(MessageType_t)((T0_FC_SKILL<<8)|T1_FC_SKILL_SETUP_SKILL_OK_DONE)
#define T_FC_SKILL_USE_SKILL					(MessageType_t)((T0_FC_SKILL<<8)|T1_FC_SKILL_USE_SKILL)
#define T_FC_SKILL_USE_SKILL_OK					(MessageType_t)((T0_FC_SKILL<<8)|T1_FC_SKILL_USE_SKILL_OK)
#define T_FC_SKILL_CANCEL_SKILL					(MessageType_t)((T0_FC_SKILL<<8)|T1_FC_SKILL_CANCEL_SKILL)
#define T_FC_SKILL_CANCEL_SKILL_OK				(MessageType_t)((T0_FC_SKILL<<8)|T1_FC_SKILL_CANCEL_SKILL_OK)
#define T_FC_SKILL_INVALIDATE_SKILL				(MessageType_t)((T0_FC_SKILL<<8)|T1_FC_SKILL_INVALIDATE_SKILL)
#define T_FC_SKILL_PREPARE_USE					(MessageType_t)((T0_FC_SKILL<<8)|T1_FC_SKILL_PREPARE_USE)
#define T_FC_SKILL_PREPARE_USE_OK				(MessageType_t)((T0_FC_SKILL<<8)|T1_FC_SKILL_PREPARE_USE_OK)
#define T_FC_SKILL_CANCEL_PREPARE				(MessageType_t)((T0_FC_SKILL<<8)|T1_FC_SKILL_CANCEL_PREPARE)
#define T_FC_SKILL_CANCEL_PREPARE_OK			(MessageType_t)((T0_FC_SKILL<<8)|T1_FC_SKILL_CANCEL_PREPARE_OK)
#define T_FC_SKILL_CONFIRM_USE					(MessageType_t)((T0_FC_SKILL<<8)|T1_FC_SKILL_CONFIRM_USE)		// 2005-12-02 by cmkwon, C->F, F->C
#define T_FC_SKILL_CONFIRM_USE_ACK				(MessageType_t)((T0_FC_SKILL<<8)|T1_FC_SKILL_CONFIRM_USE_ACK)	// 2005-12-02 by cmkwon, C->F, F->C

#define T_FN_SKILL_USE_SKILL					(MessageType_t)((T0_FN_SKILL<<8)|T1_FN_SKILL_USE_SKILL)
#define T_FN_SKILL_USE_SKILL_OK					(MessageType_t)((T0_FN_SKILL<<8)|T1_FN_SKILL_USE_SKILL_OK)

#define T_FC_QUEST_REQUEST_START				(MessageType_t)((T0_FC_QUEST<<8)|T1_FC_QUEST_REQUEST_START)			// C->F, Quest ������ ��û
#define T_FC_QUEST_REQUEST_START_RESULT			(MessageType_t)((T0_FC_QUEST<<8)|T1_FC_QUEST_REQUEST_START_RESULT)	// F->C, Quest ������ ����, Client�� �� MSG�� ������ Pre NPCTalk�� �ε��Ѵ�
#define T_FC_QUEST_ACCEPT_QUEST					(MessageType_t)((T0_FC_QUEST<<8)|T1_FC_QUEST_ACCEPT_QUEST)			// C->F, Quest�� �޾Ƶ���
#define T_FC_QUEST_CANCEL_QUEST					(MessageType_t)((T0_FC_QUEST<<8)|T1_FC_QUEST_CANCEL_QUEST)			// C->F, Quest�� ������(������ �� ���� Quest�� ������)
#define T_FC_QUEST_REQUEST_SUCCESS				(MessageType_t)((T0_FC_QUEST<<8)|T1_FC_QUEST_REQUEST_SUCCESS)		// C->F, Quest ��� ������ ��û
#define T_FC_QUEST_REQUEST_SUCCESS_RESULT		(MessageType_t)((T0_FC_QUEST<<8)|T1_FC_QUEST_REQUEST_SUCCESS_RESULT)// F->C, Quest ���(�Ϸ�)�� �˸�, Client�� �� MSG�� ������ quest�� �����ϰ� After NPCTalk�� �ε��Ѵ�
#define T_FC_QUEST_PUT_ALL_QUEST_HEADER			(MessageType_t)((T0_FC_QUEST<<8)|T1_FC_QUEST_PUT_ALL_QUEST_HEADER)	// F->C, �Ϸ�ǰų� �������� ��� ����Ʈ�� ����
#define T_FC_QUEST_PUT_ALL_QUEST				(MessageType_t)((T0_FC_QUEST<<8)|T1_FC_QUEST_PUT_ALL_QUEST)			// F->C, �Ϸ�ǰų� �������� ��� ����Ʈ�� ����
#define T_FC_QUEST_PUT_ALL_QUEST_DONE			(MessageType_t)((T0_FC_QUEST<<8)|T1_FC_QUEST_PUT_ALL_QUEST_DONE)	// F->C, �Ϸ�ǰų� �������� ��� ����Ʈ�� ����
#define T_FC_QUEST_DISCARD_QUEST				(MessageType_t)((T0_FC_QUEST<<8)|T1_FC_QUEST_DISCARD_QUEST)			// C->F, �̹� ���۵� ����Ʈ�� ������
#define T_FC_QUEST_DISCARD_QUEST_OK				(MessageType_t)((T0_FC_QUEST<<8)|T1_FC_QUEST_DISCARD_QUEST_OK)		// F->C, �̹� ���۵� ����Ʈ�� �����Կ� ���� ���
#define T_FC_QUEST_MOVE_QUEST_MAP				(MessageType_t)((T0_FC_QUEST<<8)|T1_FC_QUEST_MOVE_QUEST_MAP)		// C->F, �������� �̼Ǹ����� �̵�
#define T_FC_QUEST_PUT_ALL_QUEST_MONSTER_COUNT_HEADER	(MessageType_t)((T0_FC_QUEST<<8)|T1_FC_QUEST_PUT_ALL_QUEST_MONSTER_COUNT_HEADER)	// F->C, // 2005-10-25 by cmkwon
#define T_FC_QUEST_PUT_ALL_QUEST_MONSTER_COUNT	(MessageType_t)((T0_FC_QUEST<<8)|T1_FC_QUEST_PUT_ALL_QUEST_MONSTER_COUNT)	// F->C, // 2005-10-25 by cmkwon
#define T_FC_QUEST_PUT_ALL_QUEST_MONSTER_COUNT_DONE	(MessageType_t)((T0_FC_QUEST<<8)|T1_FC_QUEST_PUT_ALL_QUEST_MONSTER_COUNT_DONE)	// F->C, // 2005-10-25 by cmkwon
#define T_FC_QUEST_UPDATE_MONSTER_COUNT			(MessageType_t)((T0_FC_QUEST<<8)|T1_FC_QUEST_UPDATE_MONSTER_COUNT)			// F->C, // 2005-10-25 by cmkwon
#define T_FC_QUEST_REQUEST_SUCCESS_CHECK		(MessageType_t)((T0_FC_QUEST<<8)|T1_FC_QUEST_REQUEST_SUCCESS_CHECK)			// C->F, // 2006-03-24 by cmkwon
#define T_FC_QUEST_REQUEST_SUCCESS_CHECK_RESULT	(MessageType_t)((T0_FC_QUEST<<8)|T1_FC_QUEST_REQUEST_SUCCESS_CHECK_RESULT)	// F->C(n), // 2006-03-24 by cmkwon
#define T_FC_QUEST_REQUEST_PARTY_WARP			(MessageType_t)((T0_FC_QUEST<<8)|T1_FC_QUEST_REQUEST_PARTY_WARP)	// F->C(n), // 2006-10-16 by cmkwon
#define T_FC_QUEST_REQUEST_PARTY_WARP_ACK		(MessageType_t)((T0_FC_QUEST<<8)|T1_FC_QUEST_REQUEST_PARTY_WARP_ACK)	// C(n)->F, // 2006-10-16 by cmkwon

//#define T_FC_SYNC_PRIMARY_REATTACK_OK			(MessageType_t)((T0_FC_SYNC<<8)|T1_FC_SYNC_PRIMARY_REATTACK_OK)
//#define T_FC_SYNC_SECONDARY_REATTACK_OK			(MessageType_t)((T0_FC_SYNC<<8)|T1_FC_SYNC_SECONDARY_REATTACK_OK)
//#define T_FC_SYNC_SKILL_REUSE_OK				(MessageType_t)((T0_FC_SYNC<<8)|T1_FC_SYNC_SKILL_REUSE_OK)

#define T_FC_INFO_GET_MONSTER_INFO				(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_GET_MONSTER_INFO)
#define T_FC_INFO_GET_MONSTER_INFO_OK			(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_GET_MONSTER_INFO_OK)
#define T_FC_INFO_GET_MAPOBJECT_INFO			(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_GET_MAPOBJECT_INFO)
#define T_FC_INFO_GET_MAPOBJECT_INFO_OK			(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_GET_MAPOBJECT_INFO_OK)
#define T_FC_INFO_GET_ITEM_INFO					(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_GET_ITEM_INFO)
#define T_FC_INFO_GET_ITEM_INFO_OK				(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_GET_ITEM_INFO_OK)
#define T_FC_INFO_GET_RARE_ITEM_INFO			(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_GET_RARE_ITEM_INFO)
#define T_FC_INFO_GET_RARE_ITEM_INFO_OK			(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_GET_RARE_ITEM_INFO_OK)
#define T_FC_INFO_GET_BUILDINGNPC_INFO			(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_GET_BUILDINGNPC_INFO)
#define T_FC_INFO_GET_BUILDINGNPC_INFO_OK		(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_GET_BUILDINGNPC_INFO_OK)
#define T_FC_INFO_GET_SIMPLE_ITEM_INFO			(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_GET_SIMPLE_ITEM_INFO)
#define T_FC_INFO_GET_SIMPLE_ITEM_INFO_OK		(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_GET_SIMPLE_ITEM_INFO_OK)
#define T_FC_INFO_GET_ENCHANT_COST				(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_GET_ENCHANT_COST)		// C->F, ��æƮ ������ ��û
#define T_FC_INFO_GET_ENCHANT_COST_OK			(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_GET_ENCHANT_COST_OK)		// F->C, ��æƮ ������ ����
#define T_FC_INFO_GET_CURRENT_MAP_INFO				(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_GET_CURRENT_MAP_INFO)
#define T_FC_INFO_GET_CURRENT_MAP_INFO_OK			(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_GET_CURRENT_MAP_INFO_OK)
#define T_FC_INFO_GET_HAPPY_HOUR_EVENT_INFO_OK		(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_GET_HAPPY_HOUR_EVENT_INFO_OK)	// F->C
#define T_FC_INFO_GET_GAME_EVENT_INFO_OK			(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_GET_GAME_EVENT_INFO_OK)	// F->C
#define T_FC_INFO_GET_SERVER_DATE_TIME				(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_GET_SERVER_DATE_TIME)		// 2006-10-11 by cmkwon, C->F
#define T_FC_INFO_GET_SERVER_DATE_TIME_OK			(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_GET_SERVER_DATE_TIME_OK)		// 2006-10-11 by cmkwon, F->C
#define T_FC_INFO_GET_HAPPY_HOUR_EVENT_INFO			(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_GET_HAPPY_HOUR_EVENT_INFO)	// 2007-10-30 by cmkwon, ���º� ���Ǿƿ� �̺�Ʈ ���� - C->F
#define T_FC_INFO_GET_HAPPY_HOUR_EVENT_INFO_BY_LEVEL		(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_GET_HAPPY_HOUR_EVENT_INFO_BY_LEVEL)	// 2008-03-14 by dhjin, Level�� ���Ǿƿ� �̺�Ʈ ���� -

#define T_FC_INFO_CHECK_RESOBJ_CHECKSUM				(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_CHECK_RESOBJ_CHECKSUM)		// 2007-05-28 by cmkwon, C->F


#define T_FC_REQUEST_REQUEST					(MessageType_t)((T0_FC_REQUEST<<8)|T1_FC_REQUEST_REQUEST)			// C->F, ��û
#define T_FC_REQUEST_REQUEST_OK					(MessageType_t)((T0_FC_REQUEST<<8)|T1_FC_REQUEST_REQUEST_OK)		// F->C, ��û�� ����
#define T_FC_REQUEST_ACCEPT_REQUEST				(MessageType_t)((T0_FC_REQUEST<<8)|T1_FC_REQUEST_ACCEPT_REQUEST)	// C->F, �³�
#define T_FC_REQUEST_ACCEPT_REQUEST_OK			(MessageType_t)((T0_FC_REQUEST<<8)|T1_FC_REQUEST_ACCEPT_REQUEST_OK)	// F->C, �³��� ����
#define T_FC_REQUEST_REJECT_REQUEST				(MessageType_t)((T0_FC_REQUEST<<8)|T1_FC_REQUEST_REJECT_REQUEST)	// C->F, ����
#define T_FC_REQUEST_REJECT_REQUEST_OK			(MessageType_t)((T0_FC_REQUEST<<8)|T1_FC_REQUEST_REJECT_REQUEST_OK)	// F->C, ������ ����
#define T_FC_REQUEST_CANCEL_REQUEST				(MessageType_t)((T0_FC_REQUEST<<8)|T1_FC_REQUEST_CANCEL_REQUEST)	// C->F, ��û ��ҵ�

#define T_FC_CITY_GET_BUILDING_LIST				(MessageType_t)((T0_FC_CITY<<8)|T1_FC_CITY_GET_BUILDING_LIST)			// C->F, ������ �ǹ�(���� ��) ����Ʈ ���� ��û
#define T_FC_CITY_GET_BUILDING_LIST_OK			(MessageType_t)((T0_FC_CITY<<8)|T1_FC_CITY_GET_BUILDING_LIST_OK)		// F->C, ������ �ǹ�(���� ��) ����Ʈ ����
//#define T_FC_CITY_GET_WARP_TARGET_MAP_LIST		(MessageType_t)((T0_FC_CITY<<8)|T1_FC_CITY_GET_WARP_TARGET_MAP_LIST)	// C->F, ���ÿ��� �����س��� �� �ִ� ���� ����Ʈ ���� ��û
//#define T_FC_CITY_GET_WARP_TARGET_MAP_LIST_OK	(MessageType_t)((T0_FC_CITY<<8)|T1_FC_CITY_GET_WARP_TARGET_MAP_LIST_OK)	// F->C, ���ÿ��� �����س��� �� �ִ� ���� ����Ʈ ����
#define T_FC_CITY_REQUEST_ENTER_BUILDING		(MessageType_t)((T0_FC_CITY<<8)|T1_FC_CITY_REQUEST_ENTER_BUILDING)		// C->F, ���� �� ���� ��û
#define T_FC_CITY_REQUEST_ENTER_BUILDING_OK		(MessageType_t)((T0_FC_CITY<<8)|T1_FC_CITY_REQUEST_ENTER_BUILDING_OK)	// F->C, ���� ���� �ϷḦ �˸� 
//#define T_FC_CITY_REQUEST_WARP					(MessageType_t)((T0_FC_CITY<<8)|T1_FC_CITY_REQUEST_WARP)				// C->F, ���ÿ��� �����ؼ� ������ ���� ��û, ������ ä���� �ϳ��϶��� �������϶��� �ٸ���
#define T_FC_CITY_CHECK_WARP_STATE				(MessageType_t)((T0_FC_CITY<<8)|T1_FC_CITY_CHECK_WARP_STATE)			// C->F, ���� ������ �������� Ȯ�� ��û, No Body
#define T_FC_CITY_CHECK_WARP_STATE_OK			(MessageType_t)((T0_FC_CITY<<8)|T1_FC_CITY_CHECK_WARP_STATE_OK)			// F->C, ���� ������ ���������� ���� ���

#define T_FC_TIMER_START_TIMER					(MessageType_t)((T0_FC_TIMER<<8)|T1_FC_TIMER_START_TIMER)		// F->C, TIMER_EVENT ����
#define T_FC_TIMER_STOP_TIMER					(MessageType_t)((T0_FC_TIMER<<8)|T1_FC_TIMER_STOP_TIMER)		// F->C, TIMER_EVENT ����
#define T_FC_TIMER_UPDATE_TIMER					(MessageType_t)((T0_FC_TIMER<<8)|T1_FC_TIMER_UPDATE_TIMER)		// F->C, TIMER_EVENT ����(�ð� ����)
#define T_FC_TIMER_PAUSE_TIMER					(MessageType_t)((T0_FC_TIMER<<8)|T1_FC_TIMER_PAUSE_TIMER)		// F->C, TIMER_EVENT �Ͻ� ����
#define T_FC_TIMER_CONTINUE_TIMER				(MessageType_t)((T0_FC_TIMER<<8)|T1_FC_TIMER_CONTINUE_TIMER)	// F->C, TIMER_EVENT �����
#define T_FC_TIMER_TIMEOUT						(MessageType_t)((T0_FC_TIMER<<8)|T1_FC_TIMER_TIMEOUT)			// C->F, �ð��� �� ���� �˸�

#define T_FC_CLIENT_REPORT						(MessageType_t)((T0_FC_CLIENT_REPORT<<8)|T1_FC_CLIENT_REPORT)
#define T_IC_STRING_128							(MessageType_t)((T0_IC_STRING<<8)|T1_IC_STRING_128)
#define T_IC_STRING_256							(MessageType_t)((T0_IC_STRING<<8)|T1_IC_STRING_256)
#define T_IC_STRING_512							(MessageType_t)((T0_IC_STRING<<8)|T1_IC_STRING_512)

#define T_FC_STRING_128							(MessageType_t)((T0_FC_STRING<<8)|T1_FC_STRING_128)
#define T_FC_STRING_256							(MessageType_t)((T0_FC_STRING<<8)|T1_FC_STRING_256)
#define T_FC_STRING_512							(MessageType_t)((T0_FC_STRING<<8)|T1_FC_STRING_512)

#define T_FI_ADMIN_GET_CHARACTER_INFO			(MessageType_t)((T0_FI_ADMIN<<8)|T1_FI_ADMIN_GET_CHARACTER_INFO)
#define T_FI_ADMIN_GET_CHARACTER_INFO_OK		(MessageType_t)((T0_FI_ADMIN<<8)|T1_FI_ADMIN_GET_CHARACTER_INFO_OK)
#define T_FI_ADMIN_CALL_CHARACTER				(MessageType_t)((T0_FI_ADMIN<<8)|T1_FI_ADMIN_CALL_CHARACTER)		// I -> F
#define T_FI_ADMIN_MOVETO_CHARACTER				(MessageType_t)((T0_FI_ADMIN<<8)|T1_FI_ADMIN_MOVETO_CHARACTER)
#define T_FI_ADMIN_PRINT_DEBUG_MSG				(MessageType_t)((T0_FI_ADMIN<<8)|T1_FI_ADMIN_PRINT_DEBUG_MSG)
#define T_FI_ADMIN_CHANGE_WEATHER				(MessageType_t)((T0_FI_ADMIN<<8)|T1_FI_ADMIN_CHANGE_WEATHER)

#define T_IC_ADMIN_CALL_CHARACTER				(MessageType_t)((T0_IC_ADMIN<<8)|T1_IC_ADMIN_CALL_CHARACTER)		// C -> I
#define T_IC_ADMIN_GET_SERVER_STAT				(MessageType_t)((T0_IC_ADMIN<<8)|T1_IC_ADMIN_GET_SERVER_STAT)		// C -> I, NO BODY
#define T_IC_ADMIN_GET_SERVER_STAT_OK			(MessageType_t)((T0_IC_ADMIN<<8)|T1_IC_ADMIN_GET_SERVER_STAT_OK)	// I -> C
#define T_IC_ADMIN_CALL_GUILD					(MessageType_t)((T0_IC_ADMIN<<8)|T1_IC_ADMIN_CALL_GUILD)			// I -> C
#define T_IC_ADMIN_CALLGM_INFO_OK				(MessageType_t)((T0_IC_ADMIN<<8)|T1_IC_ADMIN_CALLGM_INFO_OK)		// I -> C
#define T_IC_ADMIN_CALLGM_VIEW_OK				(MessageType_t)((T0_IC_ADMIN<<8)|T1_IC_ADMIN_CALLGM_VIEW_OK)		// I -> C
#define T_IC_ADMIN_CALLGM_BRING_OK				(MessageType_t)((T0_IC_ADMIN<<8)|T1_IC_ADMIN_CALLGM_BRING_OK)		// I -> C


#define T_FC_ADMIN_GET_SERVER_STAT				(MessageType_t)((T0_FC_ADMIN<<8)|T1_FC_ADMIN_GET_SERVER_STAT)		// C -> F, NO BODY
#define T_FC_ADMIN_GET_SERVER_STAT_OK			(MessageType_t)((T0_FC_ADMIN<<8)|T1_FC_ADMIN_GET_SERVER_STAT_OK)	// F -> C


// T0_IC_COUNTDOWN
#define T_IC_COUNTDOWN_START					(MessageType_t)((T0_IC_COUNTDOWN<<8)|T1_IC_COUNTDOWN_START)		// I -> C
#define T_IC_COUNTDOWN_DONE						(MessageType_t)((T0_IC_COUNTDOWN<<8)|T1_IC_COUNTDOWN_DONE)		// C -> I

//////////////////////////////////////////////////////////////////////////
// 2008-06-17 by dhjin, EP3 VOIP -
#define T_IC_VOIP_SET							(MessageType_t)((T0_IC_VOIP<<8)|T1_IC_VOIP_SET)					// C -> I, 2008-06-17 by dhjin, EP3 VOIP - ���� 
#define T_IC_VOIP_SET_OK						(MessageType_t)((T0_IC_VOIP<<8)|T1_IC_VOIP_SET_OK)				// I -> C, 2008-06-17 by dhjin, EP3 VOIP - ���� ���� ����

//////////////////////////////////////////////////////////////////////////
// T0_IC_CHATROOM
#define T_IC_CHATROOM_CREATE					(MessageType_t)((T0_IC_CHATROOM<<8)|T1_IC_CHATROOM_CREATE)					// C -> I, 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� ����
#define T_IC_CHATROOM_CREATE_OK					(MessageType_t)((T0_IC_CHATROOM<<8)|T1_IC_CHATROOM_CREATE_OK)				// I -> C, 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� ���� OK
#define T_IC_CHATROOM_LIST_INFO					(MessageType_t)((T0_IC_CHATROOM<<8)|T1_IC_CHATROOM_LIST_INFO)				// C -> I, 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� ��� ��������
#define T_IC_CHATROOM_LIST_INFO_OK				(MessageType_t)((T0_IC_CHATROOM<<8)|T1_IC_CHATROOM_LIST_INFO_OK)			// I -> C, 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� ��� �������� OK
#define T_IC_CHATROOM_REQUEST_INVITE			(MessageType_t)((T0_IC_CHATROOM<<8)|T1_IC_CHATROOM_REQUEST_INVITE)			// C -> I, 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� �ʴ� ��û 
#define T_IC_CHATROOM_REQUEST_INVITE_QUESTION	(MessageType_t)((T0_IC_CHATROOM<<8)|T1_IC_CHATROOM_REQUEST_INVITE_QUESTION)	// I -> C, 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� �ʴ� ��󿡰� ����
#define T_IC_CHATROOM_JOIN						(MessageType_t)((T0_IC_CHATROOM<<8)|T1_IC_CHATROOM_JOIN)					// C -> I, 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� ����
#define T_IC_CHATROOM_JOIN_OK					(MessageType_t)((T0_IC_CHATROOM<<8)|T1_IC_CHATROOM_JOIN_OK)					// I -> C, 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� ���� OK
#define T_IC_CHATROOM_ACCEPT_INVITE				(MessageType_t)((T0_IC_CHATROOM<<8)|T1_IC_CHATROOM_ACCEPT_INVITE)			// C -> I, 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� �ʴ� ����
#define T_IC_CHATROOM_ACCEPT_INVITE_OK			(MessageType_t)((T0_IC_CHATROOM<<8)|T1_IC_CHATROOM_ACCEPT_INVITE_OK)		// I -> C, 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� �ʴ� ���� OK
#define T_IC_CHATROOM_REJECT_INVITE				(MessageType_t)((T0_IC_CHATROOM<<8)|T1_IC_CHATROOM_REJECT_INVITE)			// C -> I, 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� �ʴ� ����
#define T_IC_CHATROOM_REJECT_INVITE_OK			(MessageType_t)((T0_IC_CHATROOM<<8)|T1_IC_CHATROOM_REJECT_INVITE_OK)		// I -> C, 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� �ʴ� ���� OK
#define T_IC_CHATROOM_LEAVE						(MessageType_t)((T0_IC_CHATROOM<<8)|T1_IC_CHATROOM_LEAVE)					// C -> I, 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� ������
#define T_IC_CHATROOM_LEAVE_OK					(MessageType_t)((T0_IC_CHATROOM<<8)|T1_IC_CHATROOM_LEAVE_OK)				// I -> C, 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� ������ OK
#define T_IC_CHATROOM_BAN						(MessageType_t)((T0_IC_CHATROOM<<8)|T1_IC_CHATROOM_BAN)						// C -> I, 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� �߹�
#define T_IC_CHATROOM_BAN_OK					(MessageType_t)((T0_IC_CHATROOM<<8)|T1_IC_CHATROOM_BAN_OK)					// I -> C, 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� �߹� OK
#define T_IC_CHATROOM_CHANGE_NAME				(MessageType_t)((T0_IC_CHATROOM<<8)|T1_IC_CHATROOM_CHANGE_NAME)				// C -> I, 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� �̸� ����
#define T_IC_CHATROOM_CHANGE_NAME_OK			(MessageType_t)((T0_IC_CHATROOM<<8)|T1_IC_CHATROOM_CHANGE_NAME_OK)			// I -> C, 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� �̸� ���� OK
#define T_IC_CHATROOM_CHANGE_MASTER				(MessageType_t)((T0_IC_CHATROOM<<8)|T1_IC_CHATROOM_CHANGE_MASTER)			// C -> I, 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� ���� ����
#define T_IC_CHATROOM_CHANGE_MASTER_OK			(MessageType_t)((T0_IC_CHATROOM<<8)|T1_IC_CHATROOM_CHANGE_MASTER_OK)		// I -> C, 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� ���� ���� OK
#define T_IC_CHATROOM_CHANGE_LOCK_PW			(MessageType_t)((T0_IC_CHATROOM<<8)|T1_IC_CHATROOM_CHANGE_LOCK_PW)			// C -> I, 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� ��й�ȣ ����
#define T_IC_CHATROOM_CHANGE_LOCK_PW_OK			(MessageType_t)((T0_IC_CHATROOM<<8)|T1_IC_CHATROOM_CHANGE_LOCK_PW_OK)		// I -> C, 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� ��й�ȣ ���� OK
#define T_IC_CHATROOM_CHANGE_MAX_MEMBER			(MessageType_t)((T0_IC_CHATROOM<<8)|T1_IC_CHATROOM_CHANGE_MAX_MEMBER)		// C -> I, 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� �ο��� ����
#define T_IC_CHATROOM_CHANGE_MAX_MEMBER_OK		(MessageType_t)((T0_IC_CHATROOM<<8)|T1_IC_CHATROOM_CHANGE_MAX_MEMBER_OK)	// I -> C, 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� �ο��� ���� OK
#define T_IC_CHATROOM_MEMBER_INFO				(MessageType_t)((T0_IC_CHATROOM<<8)|T1_IC_CHATROOM_MEMBER_INFO)				// C -> I, 2008-06-25 by dhjin, EP3 ä�ù� - ä�ù� �ɹ� ���� ����
#define T_IC_CHATROOM_MEMBER_INFO_OK			(MessageType_t)((T0_IC_CHATROOM<<8)|T1_IC_CHATROOM_MEMBER_INFO_OK)			// I -> C, 2008-06-25 by dhjin, EP3 ä�ù� - ä�ù� �ɹ� ���� ���� OK
#define T_IC_CHATROOM_OTHER_MEMBER_INFO			(MessageType_t)((T0_IC_CHATROOM<<8)|T1_IC_CHATROOM_OTHER_MEMBER_INFO)		// C -> I, 2008-06-25 by dhjin, EP3 ä�ù� - �ٸ� ä�ù� �ɹ� ���� ����
#define T_IC_CHATROOM_OTHER_MEMBER_INFO_OK		(MessageType_t)((T0_IC_CHATROOM<<8)|T1_IC_CHATROOM_OTHER_MEMBER_INFO_OK)	// I -> C, 2008-06-25 by dhjin, EP3 ä�ù� - �ٸ� ä�ù� �ɹ� ���� ���� OK

///////////////////////////////////////////////////////////////////////////////
// CITYWAR ����
// T0_FC_CITYWAR
#define T_FC_CITYWAR_START_WAR					(MessageType_t)((T0_FC_CITYWAR<<8)|T1_FC_CITYWAR_START_WAR)			// F->C(n)
#define T_FC_CITYWAR_MONSTER_CREATED			(MessageType_t)((T0_FC_CITYWAR<<8)|T1_FC_CITYWAR_MONSTER_CREATED)			// F->C(n)
#define T_FC_CITYWAR_MONSTER_DEAD				(MessageType_t)((T0_FC_CITYWAR<<8)|T1_FC_CITYWAR_MONSTER_DEAD)		// F->C(n)
#define T_FC_CITYWAR_END_WAR					(MessageType_t)((T0_FC_CITYWAR<<8)|T1_FC_CITYWAR_END_WAR)			// F->C(n)
#define T_FC_CITYWAR_GET_OCCUPYINFO				(MessageType_t)((T0_FC_CITYWAR<<8)|T1_FC_CITYWAR_GET_OCCUPYINFO)
#define T_FC_CITYWAR_GET_OCCUPYINFO_OK			(MessageType_t)((T0_FC_CITYWAR<<8)|T1_FC_CITYWAR_GET_OCCUPYINFO_OK)
#define T_FC_CITYWAR_SET_SETTINGTIME			(MessageType_t)((T0_FC_CITYWAR<<8)|T1_FC_CITYWAR_SET_SETTINGTIME)	// C->F
#define T_FC_CITYWAR_SET_TEX					(MessageType_t)((T0_FC_CITYWAR<<8)|T1_FC_CITYWAR_SET_TEX)			// C->F
#define T_FC_CITYWAR_SET_BRIEFING				(MessageType_t)((T0_FC_CITYWAR<<8)|T1_FC_CITYWAR_SET_BRIEFING)		// C->F
#define T_FC_CITYWAR_BRING_SUMOFTEX				(MessageType_t)((T0_FC_CITYWAR<<8)|T1_FC_CITYWAR_BRING_SUMOFTEX)	// C->F
#define T_FC_CITYWAR_BRING_SUMOFTEX_OK			(MessageType_t)((T0_FC_CITYWAR<<8)|T1_FC_CITYWAR_BRING_SUMOFTEX_OK)	// F->C

struct MSG_FC_CITYWAR_START_WAR
{
	MapIndex_t			CityWarMapIndex3;
	UID32_t				OccupyGuildUID3;
	char				szOccupyGuildName3[SIZE_MAX_GUILD_NAME];
	ATUM_DATE_TIME		atimeCityWarEndTime;
};
struct MSG_FC_CITYWAR_MONSTER_DEAD
{
	MapIndex_t			CityWarMapIndex3;
	UID32_t				OccupyGuildUID3;
	char				szOccupyGuildName3[SIZE_MAX_GUILD_NAME];
};
struct MSG_FC_CITYWAR_END_WAR
{
	MapIndex_t			CityWarMapIndex3;
	UID32_t				OccupyGuildUID3;
	char				szOccupyGuildName3[SIZE_MAX_GUILD_NAME];
	ATUM_DATE_TIME		atimeNextCityWarDefaultTime;
};
struct MSG_FC_CITYWAR_GET_OCCUPYINFO_OK
{
	MapIndex_t			CurrentMapIndex3;			// ���� MapIndex 
	MapIndex_t			CityWarMapIndex3;			// ���������� MapIndex
	MapIndex_t			CityWarCityMapIndex3;		// ���������� ���� MapIndex
	SCITY_OCCUPY_INFO	CityWarOccupyInfo3;			// ���������� ���� ����
};
struct MSG_FC_CITYWAR_SET_SETTINGTIME
{
	ATUM_DATE_TIME		atimeSetCityWarSettingTime;
};
struct MSG_FC_CITYWAR_SET_TEX
{
	float				fSetTex;
};
struct MSG_FC_CITYWAR_SET_BRIEFING
{
	char				szSetBriefing[SIZE_MAX_CITY_BRIEFING_LENGTH];
};
struct MSG_FC_CITYWAR_BRING_SUMOFTEX_OK
{
	int					nBroughtSumOfTex;
};

// T0_FC_WAR
#define T_FC_WAR_NOTIFY_INVASION						(MessageType_t)((T0_FC_WAR<<8)|T1_FC_WAR_NOTIFY_INVASION)
#define T_FC_WAR_NOTIFY_INFLUENCE_MONSTER_DEAD			(MessageType_t)((T0_FC_WAR<<8)|T1_FC_WAR_NOTIFY_INFLUENCE_MONSTER_DEAD)
#define T_FC_WAR_NOTIFY_INFLUENCE_MONSTER_INVASION		(MessageType_t)((T0_FC_WAR<<8)|T1_FC_WAR_NOTIFY_INFLUENCE_MONSTER_INVASION)
#define T_FC_WAR_NOTIFY_INFLUENCE_MONSTER_AUTO_DESTROYED		(MessageType_t)((T0_FC_WAR<<8)|T1_FC_WAR_NOTIFY_INFLUENCE_MONSTER_AUTO_DESTROYED)

#define T_FC_WAR_BOSS_MONSTER_SUMMON_DATA				(MessageType_t)((T0_FC_WAR<<8)|T1_FC_WAR_BOSS_MONSTER_SUMMON_DATA)
#define T_FC_WAR_JACO_MONSTER_SUMMON					(MessageType_t)((T0_FC_WAR<<8)|T1_FC_WAR_JACO_MONSTER_SUMMON)
#define T_FC_WAR_STRATEGYPOINT_MONSTER_SUMMON			(MessageType_t)((T0_FC_WAR<<8)|T1_FC_WAR_STRATEGYPOINT_MONSTER_SUMMON)	// 2007-07-16 by dhjin
#define T_FC_WAR_SIGN_BOARD_INSERT_STRING				(MessageType_t)((T0_FC_WAR<<8)|T1_FC_WAR_SIGN_BOARD_INSERT_STRING)		// 2006-04-17 by cmkwon
#define T_FC_WAR_SIGN_BOARD_DELETE_STRING				(MessageType_t)((T0_FC_WAR<<8)|T1_FC_WAR_SIGN_BOARD_DELETE_STRING)		// 2006-04-17 by cmkwon
#define T_FC_WAR_REQ_SIGN_BOARD_STRING_LIST				(MessageType_t)((T0_FC_WAR<<8)|T1_FC_WAR_REQ_SIGN_BOARD_STRING_LIST)		// 2006-04-17 by cmkwon
#define T_FC_WAR_REQ_SIGN_BOARD_STRING_LIST_OK			(MessageType_t)((T0_FC_WAR<<8)|T1_FC_WAR_REQ_SIGN_BOARD_STRING_LIST_OK)		// 2006-04-17 by cmkwon
#define T_FC_WAR_UPDATE_CONTRIBUTION_POINT_OK			(MessageType_t)((T0_FC_WAR<<8)|T1_FC_WAR_UPDATE_CONTRIBUTION_POINT_OK)		// 2006-04-19 by cmkwon
#define T_FC_WAR_INFLUENCE_DATA							(MessageType_t)((T0_FC_WAR<<8)|T1_FC_WAR_INFLUENCE_DATA)		// 2006-04-21 by cmkwon
#define T_FC_WAR_MONSTER_CREATED						(MessageType_t)((T0_FC_WAR<<8)|T1_FC_WAR_MONSTER_CREATED)			// 2006-11-20 by cmkwon, F->C(n)
#define T_FC_WAR_MONSTER_AUTO_DESTROYED					(MessageType_t)((T0_FC_WAR<<8)|T1_FC_WAR_MONSTER_AUTO_DESTROYED)	// 2006-11-20 by cmkwon, F->C(n)
#define T_FC_WAR_MONSTER_DEAD							(MessageType_t)((T0_FC_WAR<<8)|T1_FC_WAR_MONSTER_DEAD)				// 2006-11-20 by cmkwon, F->C(n)
#define T_FC_WAR_BOSS_CONTRIBUTION_GUILD				(MessageType_t)((T0_FC_WAR<<8)|T1_FC_WAR_BOSS_CONTRIBUTION_GUILD)	// 2008-12-29 by dhjin, ���� ���� �߰���, F->C(n)
#define T_FC_WAR_INFLUENCE_CONSECUTIVE_VICTORITES		(MessageType_t)((T0_FC_WAR<<8)|T1_FC_WAR_INFLUENCE_CONSECUTIVE_VICTORITES)		// 2013-05-09 by hskim, ���� ����Ʈ ����
#define T_FC_WAR_INFLUENCE_CONSECUTIVE_POINT			(MessageType_t)((T0_FC_WAR<<8)|T1_FC_WAR_INFLUENCE_CONSECUTIVE_POINT)	// F->C // 2013-08-01 by jhseol, ������ ���� ������ - ��������Ʈ ���� �����ֱ�
#define T_FC_INFLUENCE_SHOW_INFO						(MessageType_t)((T0_FC_WAR<<8)|T1_FC_INFLUENCE_SHOW_INFO)	// F->C // 2014-06-17 by bckim, ���� �ұ��� ( �������� �� �켼���� ǥ�� )

struct MSG_FC_WAR_NOTIFY_INVASION					// 2005-12-27 by cmkwon
{
	MAP_CHANNEL_INDEX	MapChannelIndex0;		// Ÿ ������ ħ���� MapChannelIndex
};

struct MSG_FC_WAR_NOTIFY_INFLUENCE_MONSTER_DEAD		// 2005-12-27 by cmkwon
{
	INT					MonsterUnitkind;		// ���� ����
	UID32_t				uidBestGuildUID;						// 2007-08-23 by cmkwon, �� ���Ľ� �ְ� ������ �� ���ܸ� ǥ�� - GuildUID
	char				szBestGuildName[SIZE_MAX_GUILD_NAME];	// 2007-08-23 by cmkwon, �� ���Ľ� �ְ� ������ �� ���ܸ� ǥ�� - GuildName 
};

struct MSG_FC_WAR_NOTIFY_INFLUENCE_MONSTER_INVASION		// 2006-01-20 by cmkwon
{
	INT					MonsterUnitkind;		// ���� �޴� ����
};

struct MSG_FC_WAR_BOSS_MONSTER_SUMMON_DATA				// 2006-04-14 by cmkwon
{
	INT					SummonMonsterUnitkind;		// ��ȯ �� MonsterUnitKind
	INT					RemainMinute;				// ���Ͱ� ��ȯ�Ǳ� ���� ���� �ð�(����:��)
	INT					ContributionPoint;			// 2008-04-01 by dhjin, ����, ������ ����â ��ȹ�� - 
	ATUM_DATE_TIME		SummonMonsterTime;			// 2007-02-06 by dhjin, ����(����) ���� ��ȯ�� �ð� 
	BYTE				BossStep;					// 2009-03-10 by dhjin, �ܰ躰 �� �ý��� - �� �ܰ�
	BYTE				BeforeWinCheck;				// 2009-03-10 by dhjin, �ܰ躰 �� �ý��� - �� �ܰ� ���� ����
};

struct MSG_FC_WAR_JACO_MONSTER_SUMMON				// 2006-04-19 by cmkwon
{
	int		nBelligerence0;
};

struct MSG_FC_WAR_STRATEGYPOINT_MONSTER_SUMMON
{// 2007-07-18 by dhjin,
	MapIndex_t		MapIndex;
	BYTE			InfluenceType;
	CHAR			MapName[SIZE_MAX_MAP_NAME];
	ATUM_DATE_TIME	SummonStrategyPointTime;
};

struct MSG_SIGN_BOARD_STRING
{
	BYTE			InfluenceMask0;									// 2006-04-17 by cmkwon, ���� ����ũ
	BOOL			IsInfluenceLeader;								// 2006-04-17 by cmkwon, TRUE:����������, FALSE:��� Ȥ�� ������
	INT				StringIndex;									// ������ ��Ʈ�� �ε���
	ATUM_DATE_TIME	SignBoardExprieATime;							// ������ ��Ʈ�� ���� �ð�
	char			SingBoardString[SIZE_MAX_SIGN_BOARD_STRING];	// ������ ��Ʈ��
};
struct MSG_FC_WAR_SIGN_BOARD_INSERT_STRING				// 2006-04-17 by cmkwon
{
	BOOL			IsInfluenceLeader;								// 2006-04-17 by cmkwon, TRUE:����������, FALSE:��� Ȥ�� ������
	INT				StringIndex;									// ������ ��Ʈ�� �ε���
	ATUM_DATE_TIME	SignBoardExprieATime;							// ������ ��Ʈ�� ���� �ð�
	char			SingBoardString[SIZE_MAX_SIGN_BOARD_STRING];	// ������ ��Ʈ��
};
struct MSG_FC_WAR_SIGN_BOARD_DELETE_STRING				// 2006-04-18 by cmkwon
{
	INT				DeleteStringIndex;						// ������ ��Ʈ�� �ε���
};
struct MSG_FC_WAR_REQ_SIGN_BOARD_STRING_LIST				// 2006-04-17 by cmkwon
{
	INT		nReqStringCount;									// ������ ��Ʈ�� ����
};
struct MSG_FC_WAR_REQ_SIGN_BOARD_STRING_LIST_OK				// 2006-04-17 by cmkwon
{
	INT		nStringCount;									// ������ ��Ʈ�� ����
	ARRAY_(MSG_FC_WAR_SIGN_BOARD_INSERT_STRING);			// ������ ����
};
struct MSG_FC_WAR_UPDATE_CONTRIBUTION_POINT_OK				// 2006-04-19 by cmkwon
{
	BYTE	byInfluenceType;
	int		nContributionPoint;
};
struct MSG_FC_WAR_INFLUENCE_DATA							// 2006-04-21 by cmkwon
{
	BYTE	byInfluenceType;
	float	fHPRepairRate;
	float	fDPRepairRate;
	float	fSPRepairRate;
};

struct MSG_FC_WAR_MONSTER_CREATED			// 2006-11-20 by cmkwon
{
	INT					MonsterUnitKind;
	MAP_CHANNEL_INDEX	MapChannIdx;
	ATUM_DATE_TIME		CreateTime;			// 2007-07-16 by dhjin, ���� �ð� �߰�
};

struct MSG_FC_WAR_MONSTER_AUTO_DESTROYED	// 2006-11-20 by cmkwon
{
	INT					MonsterUnitKind;
	MAP_CHANNEL_INDEX	MapChannIdx;
};

struct MSG_FC_WAR_MONSTER_DEAD				// 2006-11-20 by cmkwon
{
	INT					MonsterUnitKind;
	MAP_CHANNEL_INDEX	MapChannIdx;
};

struct SCONTRIBUTION_GUILD_INFO
{
	BYTE		order;
	UID32_t		GuildUID;
	char		GuildName[SIZE_MAX_GUILD_NAME];
	INT			GuildPay;
};

struct MSG_FC_WAR_BOSS_CONTRIBUTION_GUILD
{// 2008-12-29 by dhjin, ���� ���� �߰���
	SCONTRIBUTION_GUILD_INFO   ContributionGuldInfo[3];
};

// 2013-05-09 by hskim, ���� ����Ʈ ����
struct MSG_FC_WAR_INFLUENCE_CONSECUTIVE_VICTORITES
{
	INT PointBCU;
	INT PointANI;
};
// end 2013-05-09 by hskim, ���� ����Ʈ ����
// 2013-08-01 by jhseol, ������ ���� ������
struct MSG_FC_WAR_INFLUENCE_CONSECUTIVE_POINT
{
	float PVPBuffPercent;
};
// end 2013-08-01 by jhseol, ������ ���� ������

// 2014-06-17 by bckim, ���� �ұ��� ( �������� �� �켼���� ǥ�� )
struct MSG_FC_INFLUENCE_SHOW_INFO
{
	BYTE	InfluenceType;
	INT		TurnAroundPoint;
};
// End. 2014-06-17 by bckim, ���� �ұ��� ( �������� �� �켼���� ǥ�� )


///////////////////////////////////////////////////////////////////////////////
// 2006-07-26 by cmkwon
// T0_FC_BAZAAR
#define T_FC_BAZAAR_CUSTOMER_INFO_OK				(MessageType_t)((T0_FC_BAZAAR<<8)|T1_FC_BAZAAR_CUSTOMER_INFO_OK)		// F->C
#define T_FC_BAZAAR_INFO_OK							(MessageType_t)((T0_FC_BAZAAR<<8)|T1_FC_BAZAAR_INFO_OK)					// F->C(n)
#define T_FC_BAZAAR_SELL_PUT_ITEM					(MessageType_t)((T0_FC_BAZAAR<<8)|T1_FC_BAZAAR_SELL_PUT_ITEM)			// C->F
#define T_FC_BAZAAR_SELL_PUT_ITEM_OK				(MessageType_t)((T0_FC_BAZAAR<<8)|T1_FC_BAZAAR_SELL_PUT_ITEM_OK)		// F->C
#define T_FC_BAZAAR_SELL_CANCEL_ITEM				(MessageType_t)((T0_FC_BAZAAR<<8)|T1_FC_BAZAAR_SELL_CANCEL_ITEM)		// C->F
#define T_FC_BAZAAR_SELL_CANCEL_ITEM_OK				(MessageType_t)((T0_FC_BAZAAR<<8)|T1_FC_BAZAAR_SELL_CANCEL_ITEM_OK)		// F->C
#define T_FC_BAZAAR_SELL_START						(MessageType_t)((T0_FC_BAZAAR<<8)|T1_FC_BAZAAR_SELL_START)				// C->F
#define T_FC_BAZAAR_SELL_START_OK					(MessageType_t)((T0_FC_BAZAAR<<8)|T1_FC_BAZAAR_SELL_START_OK)			// F->C
#define T_FC_BAZAAR_SELL_REQUEST_ITEMLIST			(MessageType_t)((T0_FC_BAZAAR<<8)|T1_FC_BAZAAR_SELL_REQUEST_ITEMLIST)	// C->F
#define T_FC_BAZAAR_SELL_REQUEST_ITEMLIST_OK		(MessageType_t)((T0_FC_BAZAAR<<8)|T1_FC_BAZAAR_SELL_REQUEST_ITEMLIST_OK)	// F->C
#define T_FC_BAZAAR_SELL_ITEM_ENCHANTLIST_OK		(MessageType_t)((T0_FC_BAZAAR<<8)|T1_FC_BAZAAR_SELL_ITEM_ENCHANTLIST_OK)	// F->C
#define T_FC_BAZAAR_SELL_BUY_ITEM					(MessageType_t)((T0_FC_BAZAAR<<8)|T1_FC_BAZAAR_SELL_BUY_ITEM)			// C->F
#define T_FC_BAZAAR_SELL_BUY_ITEM_OK				(MessageType_t)((T0_FC_BAZAAR<<8)|T1_FC_BAZAAR_SELL_BUY_ITEM_OK)		// F->C

#define T_FC_BAZAAR_BUY_PUT_ITEM					(MessageType_t)((T0_FC_BAZAAR<<8)|T1_FC_BAZAAR_BUY_PUT_ITEM)			// C->F
#define T_FC_BAZAAR_BUY_PUT_ITEM_OK					(MessageType_t)((T0_FC_BAZAAR<<8)|T1_FC_BAZAAR_BUY_PUT_ITEM_OK)			// F->C(2)
#define T_FC_BAZAAR_BUY_CANCEL_ITEM					(MessageType_t)((T0_FC_BAZAAR<<8)|T1_FC_BAZAAR_BUY_CANCEL_ITEM)			// C->F
#define T_FC_BAZAAR_BUY_CANCEL_ITEM_OK				(MessageType_t)((T0_FC_BAZAAR<<8)|T1_FC_BAZAAR_BUY_CANCEL_ITEM_OK)		// F->C
#define T_FC_BAZAAR_BUY_START						(MessageType_t)((T0_FC_BAZAAR<<8)|T1_FC_BAZAAR_BUY_START)				// C->F
#define T_FC_BAZAAR_BUY_START_OK					(MessageType_t)((T0_FC_BAZAAR<<8)|T1_FC_BAZAAR_BUY_START_OK)			// F->C
#define T_FC_BAZAAR_BUY_REQUEST_ITEMLIST			(MessageType_t)((T0_FC_BAZAAR<<8)|T1_FC_BAZAAR_BUY_REQUEST_ITEMLIST)	// C->F
#define T_FC_BAZAAR_BUY_REQUEST_ITEMLIST_OK			(MessageType_t)((T0_FC_BAZAAR<<8)|T1_FC_BAZAAR_BUY_REQUEST_ITEMLIST_OK)	// F->C
#define T_FC_BAZAAR_BUY_SELL_ITEM					(MessageType_t)((T0_FC_BAZAAR<<8)|T1_FC_BAZAAR_BUY_SELL_ITEM)			// C->F
#define T_FC_BAZAAR_BUY_SELL_ITEM_OK				(MessageType_t)((T0_FC_BAZAAR<<8)|T1_FC_BAZAAR_BUY_SELL_ITEM_OK)		// F->C

#define T_FI_GUILD_RANK_OK							(MessageType_t)((T0_FI_GUILD<<8)|T1_FI_GUILD_RANK_OK)		// I->F
#define T_FI_GUILD_DELETE_INFO_OK					(MessageType_t)((T0_FI_GUILD<<8)|T1_FI_GUILD_DELETE_INFO_OK	)		// I->F

struct MSG_FC_BAZAAR_CUSTOMER_INFO_OK
{
	ClientIndex_t	clientIndex0;
};

struct MSG_FC_BAZAAR_INFO_OK
{
	ClientIndex_t	clientIndex0;
	BYTE			byBazaarType;
	char			szBazaarName[SIZE_MAX_BAZAAR_NAME];
};

struct MSG_FC_BAZAAR_SELL_PUT_ITEM
{
	UID64_t			itemUID;
	int				nAmount;
	int				nEachPrice;
};


struct MSG_FC_BAZAAR_SELL_PUT_ITEM_OK
{
	UID64_t			itemUID;
};

struct MSG_FC_BAZAAR_SELL_CANCEL_ITEM
{
	UID64_t			itemUID;
};

struct MSG_FC_BAZAAR_SELL_CANCEL_ITEM_OK
{
	UID64_t			itemUID;
};

struct MSG_FC_BAZAAR_SELL_START
{
	char			szBazaarName[SIZE_MAX_BAZAAR_NAME];
};

struct MSG_FC_BAZAAR_SELL_REQUEST_ITEMLIST
{
	ClientIndex_t	clientIndex0;
};

struct SBAZAAR_SELL_ITEM
{
	int				nSellItemNum0;
	int				nSellAmount0;
	int				nSellEachPrice0;
	UID64_t			itemUID;					// 2006-07-26 by cmkwon
	INT				PrefixCodeNum0;				// ���λ�, ������ 0
	INT				SuffixCodeNum0;				// ���̻�, ������ 0
	// 2009-08-26 by cmkwon, �׷��� ���ҽ� ���� �ý��� ���� - 
	//	INT				ColorCode0;					// Ʃ�׽� �Ƹ��� ColorCode
	INT				ShapeItemNum0;			// 2009-08-26 by cmkwon, �׷��� ���ҽ� ���� �ý��� ���� - 
	INT				EffectItemNum0;			// 2009-08-26 by cmkwon, �׷��� ���ҽ� ���� �ý��� ���� - 
	INT				CoolingTime;			// 2009-09-09 ~ 2010-02-10 by dhjin, ���Ǵ�Ƽ - �ߵ�������������
	FIXED_TERM_INFO	FixedTermShape;				// 2012-10-10 by hskim, �Ⱓ�� �Ӽ� ���� (�Ⱓ�� ����)
};

struct MSG_FC_BAZAAR_SELL_REQUEST_ITEMLIST_OK
{
	ClientIndex_t	clientIndex0;
	int				nItemListCnts0;
	_ARRAY(SBAZAAR_SELL_ITEM);
};

struct MSG_FC_BAZAAR_SELL_ITEM_ENCHANTLIST_OK
{
	UID64_t			itemUID;
	int				nEnchatCnts;
	_ARRAY(int EnchantItemNum);
};

struct MSG_FC_BAZAAR_SELL_BUY_ITEM
{
	ClientIndex_t	clientIndex0;
	UID64_t			itemUID;					// 2006-07-26 by cmkwon
	int				nAmount0;
};

struct MSG_FC_BAZAAR_SELL_BUY_ITEM_OK
{
	ClientIndex_t	clientIndex0;
	UID64_t			itemUID;					// 2006-07-26 by cmkwon
	int				nAmount0;
};

struct MSG_FC_BAZAAR_BUY_PUT_ITEM
{
	int				itemNum0;
	int				nAmount;
	int				nEachPrice;
};

struct MSG_FC_BAZAAR_BUY_PUT_ITEM_OK
{
	int				itemNum0;
	int				nBuyItemIndex0;
};

struct MSG_FC_BAZAAR_BUY_CANCEL_ITEM
{
	int				nBuyItemIndex0;
};

struct MSG_FC_BAZAAR_BUY_CANCEL_ITEM_OK
{
	int				nBuyItemIndex0;
};

struct MSG_FC_BAZAAR_BUY_START
{
	char			szBazaarName[SIZE_MAX_BAZAAR_NAME];
};

struct MSG_FC_BAZAAR_BUY_REQUEST_ITEMLIST
{
	ClientIndex_t	clientIndex0;
};

struct SBAZAAR_BUY_ITEM
{
	int				nBuyItemIndex0;
	int				nBuyItemNum0;
	int				nBuyAmount0;
	int				nBuyEachPrice0;
};
struct MSG_FC_BAZAAR_BUY_REQUEST_ITEMLIST_OK
{
	ClientIndex_t	clientIndex0;
	int				nItemListCnts0;
	_ARRAY(SBAZAAR_BUY_ITEM);
};

struct MSG_FC_BAZAAR_BUY_SELL_ITEM
{
	ClientIndex_t	clientIndex0;
	int				nBuyItemIndex0;
	UID64_t			itemUID;					// 2006-07-26 by cmkwon
	int				nAmount0;
};

struct MSG_FC_BAZAAR_BUY_SELL_ITEM_OK
{
	ClientIndex_t	clientIndex0;
	int				nBuyItemIndex0;
	UID64_t			itemUID;					// 2006-07-26 by cmkwon
	int				nAmount0;
};



// T0_FI_CASH
#define T_FI_CASH_USING_GUILD						(MessageType_t)((T0_FI_CASH<<8)|T1_FI_CASH_USING_GUILD)
#define T_FI_CASH_USING_CHANGE_CHARACTERNAME		(MessageType_t)((T0_FI_CASH<<8)|T1_FI_CASH_USING_CHANGE_CHARACTERNAME)
#define T_FI_CASH_PREMIUM_CARD_INFO	            	(MessageType_t)((T0_FI_CASH<<8)|T1_FI_CASH_PREMIUM_CARD_INFO)

struct MSG_FI_CASH_USING_GUILD
{
	UID32_t		guildUID;
	int			nIncreaseMemberCapacity;
	UID32_t		CashPrice;						// 2008-05-28 by dhjin, EP3 ���� ���� ���� - ���ܿ� ���� ĳ�� ������
};
struct MSG_FI_CASH_USING_CHANGE_CHARACTERNAME
{
	UID32_t		charUID;
	char		szChangedCharacterName[SIZE_MAX_CHARACTER_NAME];
};

struct MSG_FI_CASH_PREMIUM_CARD_INFO
{// 2006-09-14 by dhjin, ���� �ʴ�� �ɹ��� ���� �ʿ�
	UID32_t			AccountUID;
	INT				nCardItemNum1;
	//	ATUM_DATE_TIME	atumTimeUpdatedTime1;	// ������ �ð�
	ATUM_DATE_TIME	atumTimeExpireTime1;	// ���� �ð�		// 2008-06-20 by dhjin, EP3 ���� ���� ���� - ���� �ð� �ʿ�
	//	float			fExpRate1;
	//	float			fDropRate1;
	//	float			fDropRareRate1;
	//	float			fExpRepairRate1;
};

struct MSG_FI_GUILD_RANK
{
	UID32_t		charUID;
	BYTE		GuildRank;
};

// T0_FN_CITYWAR
#define T_FN_CITYWAR_START_WAR					(MessageType_t)((T0_FN_CITYWAR<<8)|T1_FN_CITYWAR_START_WAR)	// F->N
#define T_FN_CITYWAR_END_WAR					(MessageType_t)((T0_FN_CITYWAR<<8)|T1_FN_CITYWAR_END_WAR)	// F->N
#define T_FN_CITYWAR_CHANGE_OCCUPY_INFO			(MessageType_t)((T0_FN_CITYWAR<<8)|T1_FN_CITYWAR_CHANGE_OCCUPY_INFO)	// F->N

struct MSG_FN_CITYWAR_START_WAR
{
	ChannelIndex_t		ChannelIndex;
};
struct MSG_FN_CITYWAR_END_WAR
{
	ChannelIndex_t		ChannelIndex;
	UID32_t				OccupyGuildUID4;
};
struct MSG_FN_CITYWAR_CHANGE_OCCUPY_INFO
{
	ChannelIndex_t		ChannelIndex;
	UID32_t				OccupyGuildUID4;
};


// STRING_128 type
#define STRING_128_DEBUG_L1		0	// ����׿�, level 1
#define STRING_128_DEBUG_L2		1	// ����׿�, level 2
#define STRING_128_DEBUG_L3		2	// ����׿�, level 3
#define STRING_128_ADMIN_CMD	3	// ������ ���ɾ��
#define STRING_128_USER_ERR		4	// ����ڿ��� �ִ� ����
#define STRING_128_USER_NOTICE	5	// ����ڿ��� �ִ� �˸�
#define STRING_128_DEBUG_PRINT	6	// ����׿�, DBGOUT�� ���
#define STRING_128_SYSTEM_NOTICE	7	// ����ڿ��� �ִ� �˸�		// 2012-03-30 by hskim, EP4 Ʈ���� �ý��� �̺�Ʈ �˸�
#define STRING_128_USER_POPUP	8	// ����ڿ��� �ִ� �˾��˸�		// 2013-05-31 by jhseol,bckim �Ƹ� �÷���
#define STRING_128_USER_OPERATOR	9	// ����ڿ��� 		// 2013-10-02 by bckim, �������� ����ȭ ��Ʈ�� �����۾� 


// SendErrorMessage� Type���� ����ϱ� ����
#define T_PRE_IOCP								(MessageType_t)((T0_PRE<<8)|T1_PRE_IOCP)
#define T_PRE_DB								(MessageType_t)((T0_PRE<<8)|T1_PRE_DB)

#define T_IM_IOCP								(MessageType_t)((T0_IM<<8)|T1_IM_IOCP)
#define T_IM_DB									(MessageType_t)((T0_IM<<8)|T1_IM_DB)

#define T_FIELD_IOCP							(MessageType_t)((T0_FIELD<<8)|T1_FIELD_IOCP)
#define T_FIELD_DB								(MessageType_t)((T0_FIELD<<8)|T1_FIELD_DB)

#define T_NPC_IOCP								(MessageType_t)((T0_NPC<<8)|T1_NPC_IOCP)

#define T_NPC_DB								(MessageType_t)((T0_NPC<<8)|T1_NPC_DB)

#define T_TIMER									(MessageType_t)((T0_TIMER<<8)|T1_TIMER)
#define T_DB									(MessageType_t)((T0_DB<<8)|T1_DB)

#define T_NA									(MessageType_t)((T0_NA<<8)|T1_NA)		// NOT AVAILABLE PROTOCOL

#define T_ERROR									(MessageType_t)((T0_ERROR<<8)|T1_ERROR)



// T0_FC_RACING
#define T_FC_RACING_RACINGLIST_REQUEST			(MessageType_t)((T0_FC_RACING<<8)|T1_FC_RACING_RACINGLIST_REQUEST)
#define T_FC_RACING_RACINGLIST_REQUEST_ACK		(MessageType_t)((T0_FC_RACING<<8)|T1_FC_RACING_RACINGLIST_REQUEST_ACK)
#define T_FC_RACING_RACINGINFO_REQUEST			(MessageType_t)((T0_FC_RACING<<8)|T1_FC_RACING_RACINGINFO_REQUEST)
#define T_FC_RACING_RACINGINFO_REQUEST_ACK		(MessageType_t)((T0_FC_RACING<<8)|T1_FC_RACING_RACINGINFO_REQUEST_ACK)
#define T_FC_RACING_RACINGNOTIFY				(MessageType_t)((T0_FC_RACING<<8)|T1_FC_RACING_RACINGNOTIFY)
#define T_FC_RACING_JOIN_ENABLE					(MessageType_t)((T0_FC_RACING<<8)|T1_FC_RACING_JOIN_ENABLE)
#define T_FC_RACING_JOIN_REQUEST				(MessageType_t)((T0_FC_RACING<<8)|T1_FC_RACING_JOIN_REQUEST)
#define T_FC_RACING_JOIN_REQUEST_ACK			(MessageType_t)((T0_FC_RACING<<8)|T1_FC_RACING_JOIN_REQUEST_ACK)
#define T_FC_RACING_COUNTDOWN					(MessageType_t)((T0_FC_RACING<<8)|T1_FC_RACING_COUNTDOWN)
#define T_FC_RACING_CHECKPOINT_CHECK			(MessageType_t)((T0_FC_RACING<<8)|T1_FC_RACING_CHECKPOINT_CHECK)
#define T_FC_RACING_CHECKPOINT_CHECK_ACK		(MessageType_t)((T0_FC_RACING<<8)|T1_FC_RACING_CHECKPOINT_CHECK_ACK)
#define T_FC_RACING_FINISHED					(MessageType_t)((T0_FC_RACING<<8)|T1_FC_RACING_FINISHED)
#define T_FC_RACING_OTHER_FINISHED				(MessageType_t)((T0_FC_RACING<<8)|T1_FC_RACING_OTHER_FINISHED)
#define T_FC_RACING_FINALRANKING				(MessageType_t)((T0_FC_RACING<<8)|T1_FC_RACING_FINALRANKING)


/* ���߿� �ʿ信 ���� �Ʒ��� ���� ��������
//#define T_CONNECT_ID			0x0000
//#define T_CONNECT_ID_OK			0x0001
//
//#define T_CHARACTER_CREATE		0x0400
//#define T_CHARACTER_CREATE_OK	0x0401
//#define T_CHARACTER_DELETE		0x0402
//#define T_CHARACTER_DELETE_OK	0x0403
//#define T_CHARACTER_REPAIR		0x0404
//#define T_CHARACTER_REPAIR_OK	0x0405
//#define T_CHARACTER_REPAIR_ERR	0x0406
//#define T_CHARACTER_DOCKING		0x0407
//#define T_CHARACTER_UNDOCKING	0x0408
//#define T_CHARACTER_DOCKING_ERR	0x0409
//
//#define T_MOVE_MOVE				0x0500
//#define T_MOVE_MOVE_OK			0x0501
//
//#define T_BATTLE_ATTACK			0x0800
//#define T_BATTLE_ATTACK_RESULT	0x0801
//#define T_BATTLE_CHANGE_INFO	0x0802
*/


/*
//typedef struct
//{
//	BYTE Type1;
//	BYTE Type2;
//	BYTE Dummy[6];
//} MESSAGE_HEADER, *PMESSAGE_HEADER;
//*/

///////////////////////////////////////////////////////////////////////////////
// Macro Definitions
///////////////////////////////////////////////////////////////////////////////
#define IS_ALIVE_MSG(_MSG_TYPE)			((HIBYTE(_MSG_TYPE) >= T0_PC_CONNECT && HIBYTE(_MSG_TYPE) <= T0_NL_CONNECT) && (LOBYTE(_MSG_TYPE) == 0x03))

///////////////////////////////////////////////////////////////////////////////
// Structures for Data Exchange
///////////////////////////////////////////////////////////////////////////////

typedef struct
{
	ClientIndex_t	ClientIndex;
} MSG_UNIT_INDEX;

///////////////////////////////
// PC_DEFAULT_UPDATE
typedef struct
{
	USHORT	Version[SIZE_MAX_VERSION];
} MSG_PC_DEFAULT_UPDATE_LAUNCHER_VERSION;

typedef struct
{
	USHORT	UpdateVersion[SIZE_MAX_VERSION];
	char	FtpIP[SIZE_MAX_FTP_URL];
	USHORT	FtpPort;
	char	FtpAccountName[SIZE_MAX_ACCOUNT_NAME];
	char	FtpPassword[SIZE_MAX_PASSWORD];
	char	LauncherFileDownloadPath[SIZE_MAX_FTP_FILE_PATH];		// 2005-12-23 by cmkwon, ����
} MSG_PC_DEFAULT_UPDATE_LAUNCHER_UPDATE_INFO;

struct MSG_PC_DEFAULT_NEW_UPDATE_LAUNCHER_VERSION					// 2007-01-08 by cmkwon, C->P
{
	USHORT	Version[SIZE_MAX_VERSION];
};

struct MSG_PC_DEFAULT_NEW_UPDATE_LAUNCHER_UPDATE_INFO			// 2007-01-06 by cmkwon, �߰���
{
	int		nAutoUpdateServerType;						// 2007-01-08 by cmkwon, AU_SERVER_TYPE_XXX
	USHORT	UpdateVersion[SIZE_MAX_VERSION];
	char	UpdateServerIP[SIZE_MAX_FTP_URL];
	USHORT	UpdateServerPort;
	char	AccountName[SIZE_MAX_ACCOUNT_NAME];
	char	Password[SIZE_MAX_PASSWORD];
	char	LauncherFileDownloadPath[SIZE_MAX_FTP_FILE_PATH];
};


///////////////////////////////
// PC_CONNECT

typedef struct
{
	USHORT	ClientVersion[SIZE_MAX_VERSION];
} MSG_PC_CONNECT_VERSION;

typedef struct
{
	int		nAutoUpdateServerType;				// 2007-01-08 by cmkwon, AU_SERVER_TYPE_XXX
	USHORT	OldVersion[SIZE_MAX_VERSION];		// ������Ʈ ���� ����
	USHORT	UpdateVersion[SIZE_MAX_VERSION];	// ������Ʈ �� ����
	char	FtpIP[SIZE_MAX_FTP_URL];
	USHORT	FtpPort;
	char	FtpAccountName[SIZE_MAX_ACCOUNT_NAME];
	char	FtpPassword[SIZE_MAX_PASSWORD];
	// 2005-12-23 by cmkwon
	//	char	FtpUpdateDir[SIZE_MAX_FTP_FILE_PATH];	// ������Ʈ�� ������ �ִ� ���
	char	FtpUpdateDownloadDir[SIZE_MAX_FTP_FILE_PATH];	// 2005-12-23 by cmkwon, ������Ʈ�� ���� �ٿ�ε� ���
} MSG_PC_CONNECT_UPDATE_INFO;

typedef struct
{
	USHORT	LatestVersion[SIZE_MAX_VERSION];		// �ֽ� ����
} MSG_PC_CONNECT_REINSTALL_CLIENT;


#define LOGIN_TYPE_DIRECT	((BYTE)0)
#define LOGIN_TYPE_MGAME	((BYTE)1)

typedef struct
{
	BYTE	LoginType;		// LOGIN_TYPE_XXX

	// 2008-10-08 by cmkwon, �븸 2�ܰ� ���� �ý��� ���� ����(email->uid) - 
	//	char	AccountName[SIZE_MAX_ACCOUNT_NAME];
	char	AccountName[SIZE_MAX_ORIGINAL_ACCOUNT_NAME];	// 2008-10-08 by cmkwon, �븸 2�ܰ� ���� �ý��� ���� ����(email->uid) - 

	BYTE	Password[SIZE_MAX_PASSWORD_MD5];
	char	FieldServerGroupName[SIZE_MAX_SERVER_NAME];
	char	PrivateIP[SIZE_MAX_IPADDRESS];
	INT		MGameSEX;		// ���� - ��=0, ����=1, ����=2
	INT		MGameYear;		// ����⵵(ex> 1976, 1981, 2000)
	char	WebLoginAuthKey[SIZE_MAX_WEBLOGIN_AUTHENTICATION_KEY];		// 2007-03-29 by cmkwon, �߰���
	char	ClientIP[SIZE_MAX_IPADDRESS];	// 2008-10-08 by cmkwon, �븸 Netpower_Tpe �ܺ����� ���� - PreServer�� ������ client IP
	char	SelectiveShutdownInfo[SIZE_MAX_SELECTIVE_SHUTDOWN_INFO];		// 2012-07-11 by hskim, ������ �˴ٿ�
} MSG_PC_CONNECT_LOGIN;

typedef struct
{
	char	AccountName[SIZE_MAX_ACCOUNT_NAME];		// 2008-10-08 by cmkwon, �븸 2�ܰ� ���� �ý��� ���� ����(email->uid) - 2�� ������ ������

	char	FieldServerIP[SIZE_MAX_IPADDRESS];
	char	IMServerIP[SIZE_MAX_IPADDRESS];
	USHORT	FieldServerPort;
	USHORT	IMServerPort;
	BOOL	OpeningMoviePlay;		// 2011-12-21 by hskim, EP4 [������ 1ȸ ���]
	BOOL	ConnectToTestServer;	// 2014-01-06 by jhseol, �׼� ���� ����(TRUE=�׼�, FALSE=����)
} MSG_PC_CONNECT_LOGIN_OK;

typedef struct
{
	INT		reason;
} MSG_PC_CONNECT_CLOSE;

typedef struct
{
	USHORT	DeleteFileListVersion[SIZE_MAX_VERSION];
	USHORT	NoticeVersion[SIZE_MAX_VERSION];
} MSG_PC_CONNECT_SINGLE_FILE_VERSION_CHECK;		// single file�鿡 ���� ���� Ȯ��(deletefilelist.txt, notice.txt ��)

typedef struct
{
	int		nAutoUpdateServerType;						// 2007-01-08 by cmkwon, AU_SERVER_TYPE_XXX
	USHORT	NewDeleteFileListVersion[SIZE_MAX_VERSION];
	USHORT	NewNoticeVersion[SIZE_MAX_VERSION];
	char	FtpIP[SIZE_MAX_FTP_URL];
	USHORT	FtpPort;
	char	FtpAccountName[SIZE_MAX_ACCOUNT_NAME];
	char	FtpPassword[SIZE_MAX_PASSWORD];
	char	DeleteFileListDownloadPath[SIZE_MAX_FTP_FILE_PATH];
	char	NoticeFileDownloadPath[SIZE_MAX_FTP_FILE_PATH];
} MSG_PC_CONNECT_SINGLE_FILE_UPDATE_INFO;		// single file�鿡 ���� ������Ʈ ����(deletefilelist.txt, notice.txt ��)

#ifndef MGAME_MAX_PARAM_STRING_SIZE
#define MGAME_MAX_PARAM_STRING_SIZE			50
#endif

struct MEX_SERVER_GROUP_INFO_FOR_LAUNCHER
{
	char	ServerGroupName[SIZE_MAX_SERVER_NAME];
	int		Crowdedness;		// ȥ�⵵, 0% ~ 100%
};

typedef struct
{
	int		NumOfServerGroup;
	ARRAY_(MEX_SERVER_GROUP_INFO_FOR_LAUNCHER);
} MSG_PC_CONNECT_GET_SERVER_GROUP_LIST_OK;	// P->Launcher

struct SGAME_SERVER_GROUP_OLD		// 2007-09-05 by cmkwon, EXE_1�� �α��� ���� ���� �������̽� ���� - ���� ���� ȣȯ�� ���� ����ü
{
	char	szGameServerGroupName[SIZE_MAX_GAME_SERVER_GROUP_NAME];
	char	szPreServerIP0[SIZE_MAX_IPADDRESS];
	USHORT	usPreServerPort0;
};

struct MSG_PC_CONNECT_GET_GAME_SERVER_GROUP_LIST_OK		// 2007-05-02 by cmkwon, PreServer ����
{// 2007-05-15 by cmkwon, ����ü�� ����� SIZE_MAX_PACKET ���� �۾ƾ� �Ѵ�.
	SGAME_SERVER_GROUP_OLD arrGameServerGroupList[COUNT_MAX_GAME_SERVER_GROUP_LIST];		// 2007-09-05 by cmkwon, EXE_1�� �α��� ���� ���� �������̽� ���� - ���� ���� ȣȯ�� ���� ����ü ���
};

struct SGAME_SERVER_GROUP		// 2007-05-02 by cmkwon, PreServer ����
{
	char	szGameServerGroupName[SIZE_MAX_GAME_SERVER_GROUP_NAME];
	char	szPreServerIP0[SIZE_MAX_IPADDRESS];
	// 2007-09-05 by cmkwon, EXE_1�� �α��� ���� ���� �������̽� ���� - Port�� �⺻��Ʈ�� �����
	//	USHORT	usPreServerPort0;
	USHORT	usPreServerTab8OrderIndex;			// 2007-09-05 by cmkwon, EXE_1�� �α��� ���� ���� �������̽� ���� - �ʵ��߰�
};
typedef vector<SGAME_SERVER_GROUP>		vectSGAME_SERVER_GROUP;			// 2007-05-15 by cmkwon

struct MSG_PC_CONNECT_GET_NEW_GAME_SERVER_GROUP_LIST_OK		// 2007-09-05 by cmkwon, EXE_1�� �α��� ���� ���� �������̽� ���� - ���� �߰��� ����ü
{// 2007-05-15 by cmkwon, ����ü�� ����� SIZE_MAX_PACKET ���� �۾ƾ� �Ѵ�.
	SGAME_SERVER_GROUP arrGameServerGroupList[COUNT_MAX_GAME_SERVER_GROUP_LIST];
};

struct MSG_PC_CONNECT_NETWORK_CHECK			// 2007-06-18 by cmkwon, ��Ʈ��ũ ���� üũ 
{
	int		nCheckCount;
};

typedef MSG_PC_CONNECT_NETWORK_CHECK	MSG_PC_CONNECT_NETWORK_CHECK_OK;		// 2007-06-18 by cmkwon, ��Ʈ��ũ ���� üũ 


struct MSG_PC_CONNECT_LOGIN_BLOCKED
{
	// 2008-10-08 by cmkwon, �븸 2�ܰ� ���� �ý��� ���� ����(email->uid) -
	//	char			szAccountName[SIZE_MAX_ACCOUNT_NAME];				// 2007-01-10 by cmkwon
	char			szAccountName[SIZE_MAX_ORIGINAL_ACCOUNT_NAME];		// 2008-10-08 by cmkwon, �븸 2�ܰ� ���� �ý��� ���� ����(email->uid) -

	int				nBlockedType;
	ATUM_DATE_TIME	atimeStart;
	ATUM_DATE_TIME	atimeEnd;
	char			szBlockedReasonForUser[SIZE_MAX_BLOCKED_ACCOUNT_REASON];		// 2007-01-10 by cmkwon
};

///////////////////////////////
// FN_CONNECT

typedef struct
{
	MapIndex_t	MapIndex;
} MSG_FN_CONNECT_MAP_INFO;

typedef struct
{
	MapIndex_t	MapIndex;
	INT			TotalChannelCount;
	DWORD		Padding[SIZE_MAX_PACKET_PADDING];		// 2011-07-21 by hskim, ���� ���� ���� - ���� ������ ȣȯ �ȵǵ��� ����ü ũ�� �ٲ�
} MSG_FN_CONNECT_INCREASE_CHANNEL;		// F->N

typedef struct
{
	MAP_CHANNEL_INDEX	MapChannelIndex;
	BOOL				EnableChannel;	// TRUE: Enable, FALSE: Disable
	DWORD				Padding[SIZE_MAX_PACKET_PADDING];		// 2011-07-21 by hskim, ���� ���� ���� - ���� ������ ȣȯ �ȵǵ��� ����ü ũ�� �ٲ�
} MSG_FN_CONNECT_SET_CHANNEL_STATE;		// F->N

///////////////////////////////
// FC_CONNECT

typedef struct
{
	char	AccountName[SIZE_MAX_ACCOUNT_NAME];
	char	Password[SIZE_MAX_PASSWORD_MD5_STRING];
	char	PrivateIP[SIZE_MAX_IPADDRESS];
	DWORD	Padding[SIZE_MAX_PACKET_PADDING];		// 2011-07-21 by hskim, ���� ���� ���� - ���� ������ ȣȯ �ȵǵ��� ����ü ũ�� �ٲ�
} MSG_FC_CONNECT_LOGIN;

// 2005-12-08 by cmkwon
/////////////////////////////////////
//// ������ ���� ��ġ(POS_XXX)
//#define POS_PROW							((BYTE)0)	// ���̴�(���� ���)
//#define POS_PROWIN						((BYTE)1)	// ��ǻ��(�߾� ����)
//#define POS_PROWOUT						((BYTE)2)	// 1�� ����(���� ����)
//#define POS_WINGIN						((BYTE)3)	//		������(�߾� ����)
//#define POS_WINGOUT						((BYTE)4)	// 2�� ����(���� ����)
//#define POS_CENTER						((BYTE)5)	// �Ƹ�(�߾� ���)
//#define POS_REAR							((BYTE)6)	// ����(�Ĺ� ���)
//#define POS_ATTACHMENT					((BYTE)7)	// 2006-03-30 by cmkwon, ������ �Ǽ��縮 - ������(�Ĺ� ����-������ũ|�����̳ʰ迭)
//#define POS_PET							((BYTE)8)	// 2006-03-30 by cmkwon, �ð����� �Ǽ��縮(�Ĺ� ����)
typedef struct
{
	INT		RI_Prow;			// POS_PROW�� ItemNum, ���� (����Ʈ�迭 + ���迭 or ���̴�)
	INT		RI_ProwIn;			// 2005-03-17 by cmkwon (CPU ��ǻ��)
	INT		RI_ProwOut;			// POS_PROWOUT�� ItemNum, ������ �ٱ���, ���� (1������ - ���迭 or ĳ���迭)
	INT		RI_WingIn;			// 2005-03-17 by cmkwon (��ũ)
	INT		RI_WingOut;			// POS_WINGOUT�� ItemNum, ������ �ٱ���, ����(2������ - ���ϰ迭 or �̻��ϰ迭)
	INT		RI_Center;			// POS_CENTER�� ItemNum, �߾� (���迭 - �Ƹ�) ����
	// 2009-08-26 by cmkwon, �׷��� ���ҽ� ���� �ý��� ���� - �ʿ� ����
	//	INT		RI_ArmorColorCode;	// 2005-12-08 by cmkwon, �Ƹ��� ����Į��
	INT		RI_Rear;			// POS_REAR�� ItemNum, �Ĺ� (�����迭)

	// 2010-06-15 by shcho&hslee ��ý���
	//INT		RI_Attachment;		// POS_ATTACHMENT�� ItemNum, ������ (�����̳ʰ迭<������ũ/��Ÿ�迭> or �������� ����)
	INT		RI_AccessoryUnLimited;

	// 2010-06-15 by shcho&hslee ��ý���
	//INT		RI_Pet;				// 2005-03-17 by cmkwon (�ð����� �Ǽ��縮)
	INT		RI_AccessoryTimeLimit;

	BOOL	RI_Invisible;		// 2006-11-27 by dhjin, ĳ���� ������ �ʴ� �÷���
	INT		RI_Prow_ShapeItemNum;			// 2009-08-26 by cmkwon, �׷��� ���ҽ� ���� �ý��� ���� - ���̴� ShapeItemNum
	INT		RI_WingIn_ShapeItemNum;			// 2009-08-26 by cmkwon, �׷��� ���ҽ� ���� �ý��� ���� - ��ũ ShapeItemNum
	INT		RI_Center_ShapeItemNum;			// 2009-08-26 by cmkwon, �׷��� ���ҽ� ���� �ý��� ���� - �Ƹ� ShapeItemNum
	INT		RI_ProwOut_ShapeItemNum;		// 2009-08-26 by cmkwon, �׷��� ���ҽ� ���� �ý��� ���� - 1������ ShapeItemNum
	INT		RI_WingOut_ShapeItemNum;		// 2009-08-26 by cmkwon, �׷��� ���ҽ� ���� �ý��� ���� - 2������ ShapeItemNum
	INT		RI_ProwOut_EffectItemNum;		// 2009-08-26 by cmkwon, �׷��� ���ҽ� ���� �ý��� ���� - 1������ ź�� EffectItemNum
	INT		RI_WingOut_EffectItemNum;		// 2009-08-26 by cmkwon, �׷��� ���ҽ� ���� �ý��� ���� - 2������ ź�� EffectItemNum
	INT		RI_MonsterUnitKind_ForTransformer;	// 2010-03-18 by cmkwon, ���ͺ��� ���� - ���Ż����� ���� ����ī��

	INT		RI_Pet;							// 2010-06-15 by shcho&hslee ��ý��� - �� ������.
	INT		RI_Pet_ShapeItemNum;			// 2010-06-15 by shcho&hslee ��ý��� - ShapeItemNum.

	///////////////////////////////////////////////////////////////////////////////
	/// \fn			
	/// \brief		// 2009-08-26 by cmkwon, �׷��� ���ҽ� ���� �ý��� ���� - 
	/// \author		cmkwon
	/// \date		2009-08-27 ~ 2009-08-27
	/// \warning	
	///
	/// \param		
	/// \return		
	///////////////////////////////////////////////////////////////////////////////
	BOOL SetRenderInfoWithPOS(INT i_nPos, INT i_nItemNum, INT i_nShapeItemNum, INT i_nEffectItemNum)
	{
		switch (i_nPos)
		{

		case POS_PROW:			// ���̴� - �������氡��
		{
			RI_Prow = i_nItemNum;
			RI_Prow_ShapeItemNum = i_nShapeItemNum;
		}
		break;

		case POS_PROWIN:		// CPU ��ǻ�� - 
		{
			RI_ProwIn = i_nItemNum;		// 2012-06-20 by isshin CPU ���� ���� ����
		}
		break;

		case POS_PROWOUT:		// 1�� ���� - �������氡�� + ź������Ʈ���氡��
		{
			RI_ProwOut = i_nItemNum;
			RI_ProwOut_ShapeItemNum = i_nShapeItemNum;
			RI_ProwOut_EffectItemNum = i_nEffectItemNum;
		}
		break;

		case POS_WINGIN:		// ��ũ - �������氡��
		{
			RI_WingIn = i_nItemNum;
			RI_WingIn_ShapeItemNum = i_nShapeItemNum;
		}
		break;

		case POS_WINGOUT:		// 2�� ���� - �������氡�� + ź������Ʈ���氡��
		{
			RI_WingOut = i_nItemNum;
			RI_WingOut_ShapeItemNum = i_nShapeItemNum;
			RI_WingOut_EffectItemNum = i_nEffectItemNum;
		}
		break;

		case POS_CENTER:		// �Ƹ� - �������氡��
		{
			RI_Center = i_nItemNum;
			RI_Center_ShapeItemNum = i_nShapeItemNum;
		}
		break;

		case POS_REAR:			// ���� - 
		{
			RI_Rear = i_nItemNum;
		}
		break;

		// 2010-06-15 by shcho&hslee ��ý��� - ���� ����.
		//case POS_ATTACHMENT:	// ������ũ or �������Ǳ��� - 
		case POS_ACCESSORY_UNLIMITED:
		{
			//RI_Attachment	= i_nItemNum;
			RI_AccessoryUnLimited = i_nItemNum;
		}
		break;

		// 2010-06-15 by shcho&hslee ��ý��� - ���� ����.
		//case POS_PET:						// �ð����� �Ǽ��縮 - 
		case POS_ACCESSORY_TIME_LIMIT:		// �ð����� �Ǽ��縮 - 
		{
			//RI_Pet			= i_nItemNum;
			RI_AccessoryTimeLimit = i_nItemNum;
		}
		break;

		// 2010-06-15 by shcho&hslee ��ý���
		case POS_PET:
		{
			RI_Pet = i_nItemNum;
			RI_Pet_ShapeItemNum = i_nShapeItemNum;
		}
		break;

		default:
		{
			return FALSE;
		}
		}
		return TRUE;
	};
} CHARACTER_RENDER_INFO;		// ��ü�� �׸��� ���� �ʿ��� ������ ������ ����

typedef struct
{
	char					CharacterName[SIZE_MAX_CHARACTER_NAME];
	UID32_t					CharacterUniqueNumber;
	USHORT					Race;
	USHORT					UnitKind;
	BYTE					PilotFace;
	BYTE					Gender;
	int						RacingPoint;		// 2009-11-02 by cmkwon, ĳ��(�κ�/â�� Ȯ��) ������ �߰� ���� - 
	CHARACTER_RENDER_INFO	CharacterRenderInfo;
	// START 2011-11-03 by shcho, yedang �˴ٿ��� ���� - ���������� �߰��� �޾ƿ´�.
	BOOL					ShutDownMINS;
	// END 2011-11-03 by shcho, yedang �˴ٿ��� ���� - ���������� �߰��� �޾ƿ´�.
	DWORD					Padding[SIZE_MAX_PACKET_PADDING];		// 2011-07-21 by hskim, ���� ���� ���� - ���� ������ ȣȯ �ȵǵ��� ����ü ũ�� �ٲ�
} FC_CONNECT_LOGIN_INFO;

struct MSG_FC_CONNECT_LOGIN_OK
{
	UID32_t				AccountUniqueNumber;
	BYTE				NumCharacters;
	FC_CONNECT_LOGIN_INFO	Characters[3];
	char				VoIP1to1ServerIP[SIZE_MAX_IPADDRESS];
	USHORT				VoIP1to1ServerPort;
	char				VoIPNtoNServerIP[SIZE_MAX_IPADDRESS];
	USHORT				VoIPNtoNServerPort;
	BYTE				bIsUseSecondaryPasswordSystem;			// 2007-09-13 by cmkwon, ��Ʈ�� 2���н����� ���� - MSG_FC_CONNECT_LOGIN_OK �� �ʵ� �߰�
	BYTE				bIsSetSecondaryPassword;				// 2007-09-13 by cmkwon, ��Ʈ�� 2���н����� ���� - MSG_FC_CONNECT_LOGIN_OK �� �ʵ� �߰�
	DWORD				Padding[SIZE_MAX_PACKET_PADDING];		// 2011-07-21 by hskim, ���� ���� ���� - ���� ������ ȣȯ �ȵǵ��� ����ü ũ�� �ٲ�
	BOOL				BIsTestServer;							// 2012-11-27 by khkim, �׽�Ʈ �������� �Ϲ� �������� ����
	BYTE				DBNum;									// 2012-11-28 by jhseol, �������� ĳ�� WEB ���� - ������ ����ϴ� ��ȣ
};

typedef struct
{
	INT		reason;
} MSG_FC_CONNECT_CLOSE;

typedef struct {
	UINT	CurrentTime;	// 4�ð� �������� ���� ��
} MSG_FC_CONNECT_SYNC_TIME;


struct MSG_FC_CONNECT_NETWORK_CHECK		// 2008-02-15 by cmkwon, Client<->FieldServer �� ��Ʈ��ũ ���� üũ - 
{
	int		nCheckCount;
	DWORD	dwClientTick;
};
// 2008-10-31 by cmkwon, ��Ʈ��ũ ���� üũ ���� ����(���۰����� ����) - �Ʒ��� ���� ���� ������
//typedef MSG_FC_CONNECT_NETWORK_CHECK	MSG_FC_CONNECT_NETWORK_CHECK_OK;	// 2008-02-15 by cmkwon, Client<->FieldServer �� ��Ʈ��ũ ���� üũ - 
struct MSG_FC_CONNECT_NETWORK_CHECK_OK		// 2008-10-31 by cmkwon, ��Ʈ��ũ ���� üũ ���� ����(���۰����� ����) - 
{
	int		nCheckCount;
	DWORD	dwClientTick;
	int		nWriteBufferSize;		// 2008-10-31 by cmkwon, ��Ʈ��ũ ���� üũ ���� ����(���۰����� ����) - 
};

struct MSG_FC_CONNECT_ARENASERVER_INFO
{// 2007-12-28 by dhjin, �Ʒ��� ���� - F -> C 
	USHORT		MainServer_ID;
	USHORT		ArenaServer_ID;
	USHORT		AFS_Port;
	USHORT		AIS_Port;
	CHAR		AFS_IP[SIZE_MAX_IPADDRESS];
	CHAR		AIS_IP[SIZE_MAX_IPADDRESS];
};

struct MSG_FC_CONNECT_ARENASERVER_LOGIN
{// 2007-12-28 by dhjin, �Ʒ��� ���� - AF -> C 
	UID32_t			AccountUID;
	UID32_t			MFSCharacterUID;
	ClientIndex_t	MFSClientIdx;
	USHORT			MFS_ID;
};

struct MSG_FC_CONNECT_ARENASERVER_LOGIN_OK
{// 2007-12-28 by dhjin, �Ʒ��� ���� - C -> AF
	CHARACTER		AFSCharacter;
	ATUM_DATE_TIME	atimeCurServerTime;		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - �ñ� ���� ������ ó��, ���� �Ʒ��� ���� ��¥ �ð�
};

// 2008-02-25 by dhjin, �Ʒ��� ���� - AF -> C
struct SSERVER_GROUP_FOR_CLIENT
{
	CHAR			MFS_ServerIDName[SIZE_MAX_SERVER_NAME];
	CHAR			MFS_Name[SIZE_MAX_SERVER_NAME];
};

struct MSG_FC_CONNECT_ARENASERVER_SSERVER_GROUP_FOR_CLIENT
{// �Ʒ��� ���� -
	SSERVER_GROUP_FOR_CLIENT		ServerGroupInfo[SIZE_MAX_SERVER_GROUP_COUNT];
};



///////////////////////////////
// FP_CONNECT

#define PRESERVER_AUTH_TYPE_LOGIN				0x00
// 2004-12-16 by cmkwon, �ٸ� �ʵ弭������ ������ �����Ƿ� ������
//#define PRESERVER_AUTH_TYPE_WARP_CONNECT		0x01
// 2005-07-21 by cmkwon, �ٸ� �ʵ弭������ GameStart�� �����Ƿ� ������
//#define PRESERVER_AUTH_TYPE_CONNECT_GAMESTART	0x02

typedef struct
{
	char			AccountName[SIZE_MAX_ACCOUNT_NAME];
	SERVER_ID		FieldServerID;
	char			PrivateIP[SIZE_MAX_IPADDRESS];
	ClientIndex_t	ClientIndex;
	BYTE			AuthType;
	DWORD			Padding[SIZE_MAX_PACKET_PADDING];		// 2011-07-21 by hskim, ���� ���� ���� - ���� ������ ȣȯ �ȵǵ��� ����ü ũ�� �ٲ�
} MSG_FP_CONNECT_AUTH_USER;

typedef struct
{
	char			AccountName[SIZE_MAX_ACCOUNT_NAME];
	UID32_t			AccountUniqueNumber;
	ClientIndex_t	ClientIndex;
	BYTE			AuthType;
	int				GalaNetAccountIDNum;							// 2006-06-01 by cmkwon, exteranl authentication DB accountID Number
	ATUM_DATE_TIME	AccountRegisteredDate;							// 2006-06-02 by cmkwon
	char			PasswordFromDB[SIZE_MAX_PASSWORD_MD5_STRING];	// 2006-06-02 by cmkwon
	int				GameContinueTimeInSecondOfToday;				// 2006-11-15 by cmkwon, ���� �Ϸ� ���� ���� �ð�
	ATUM_DATE_TIME	LastGameEndDate;								// 2006-11-15 by cmkwon, ������ ���� ���� �ð�
	ATUM_DATE_TIME	Birthday;										// 2007-06-28 by cmkwon, �߱� ��������(�������� FielServer�� ��������) - �������� ����
	char			SecondaryPassword[SIZE_MAX_PASSWORD_MD5_STRING];	// 2007-09-12 by cmkwon, ��Ʈ�� 2���н����� ���� - MSG_FP_CONNECT_AUTH_USER_OK �� �ʵ� �߰�
	USHORT			UserType;											// 2013-01-18 by khkim, GLog ���� ���� 
#ifdef S_ARARIO_HSSON
	eCONNECT_PUBLISHER	eOtherPublisherConncect;				// 2010-11 by dhjin, �ƶ󸮿� ä�θ� �α���.
#endif
	DWORD			Padding[SIZE_MAX_PACKET_PADDING];		// 2011-07-21 by hskim, ���� ���� ���� - ���� ������ ȣȯ �ȵǵ��� ����ü ũ�� �ٲ�
} MSG_FP_CONNECT_AUTH_USER_OK;

typedef struct
{
	char		FieldServerGroupName[SIZE_MAX_SERVER_NAME];
	SERVER_ID	FieldServerID;
	int			NumOfMapIndex;
	BOOL		ArenaFieldServerCheck;	// 2007-12-26 by dhjin, �Ʒ��� ���� - TRUE => �Ʒ��� �ʵ� ����
	SDBSERVER_GROUP		DBServerGroup;	// 2008-04-29 by cmkwon, ������ ���� DB�� �߰�(�ű� ���� ĳ���� ���� ���� �ý����߰�) - 
	ARRAY_(MapIndex_t);					// array of MapIndexes
} MSG_FP_CONNECT_FIELD_CONNECT;

typedef struct
{
	MGAME_EVENT_t	CurrentMGameEventType;
	DWORD			Padding[SIZE_MAX_PACKET_PADDING];		// 2011-07-21 by hskim, ���� ���� ���� - ���� ������ ȣȯ �ȵǵ��� ����ü ũ�� �ٲ�
} MSG_FP_CONNECT_FIELD_CONNECT_OK;

typedef struct
{
	char			AccountName[SIZE_MAX_ACCOUNT_NAME];
	ClientIndex_t	ClientIndex;
	DWORD			Padding[SIZE_MAX_PACKET_PADDING];		// 2011-07-21 by hskim, ���� ���� ���� - ���� ������ ȣȯ �ȵǵ��� ����ü ũ�� �ٲ�
} MSG_FP_CONNECT_NOTIFY_CLOSE;

typedef struct
{
	char			AccountName[SIZE_MAX_ACCOUNT_NAME];
	SERVER_ID		FieldServerID;
	ClientIndex_t	ClientIndex;
} MSG_FP_CONNECT_NOTIFY_FIELDSERVER_CHANGE;

typedef struct
{
	ClientIndex_t	ClientIndex;
} MSG_FP_CONNECT_NOTIFY_FIELDSERVER_CHANGE_OK;


struct MSG_FP_CONNECT_UPDATE_DBSERVER_GROUP		// 2008-04-29 by cmkwon, ������ ���� DB�� �߰�(�ű� ���� ĳ���� ���� ���� �ý����߰�) - 
{
	SDBSERVER_GROUP DBServerGroup;
};

struct MSG_FP_CONNECT_CHECK_CONNECTABLE_ACCOUNT			// 2008-04-29 by cmkwon, ������ ���� DB�� �߰�(�ű� ���� ĳ���� ���� ���� �ý����߰�) - 
{
	char					AccountName[SIZE_MAX_ACCOUNT_NAME];
	MSG_PC_CONNECT_LOGIN_OK PCConnectLoginOK;
};

struct MSG_FP_CONNECT_CHECK_CONNECTABLE_ACCOUNT_OK		// 2008-04-29 by cmkwon, ������ ���� DB�� �߰�(�ű� ���� ĳ���� ���� ���� �ý����߰�) - 
{
	int						ErrorCode;	// 0�̸� No Error, 0�� �ƴϸ� �����ڵ��� 
	char					AccountName[SIZE_MAX_ACCOUNT_NAME];
	MSG_PC_CONNECT_LOGIN_OK PCConnectLoginOK;
};

// start 2011-12-12 by hskim, GLog 2��
#define T_FP_GLOG_CONNECT_USER_NEW				(MessageType_t)((T0_FP_GLOG<<8)|T1_FP_GLOG_CONNECT_USER_NEW)
#define T_FP_GLOG_CONNECT_USER_LOGIN			(MessageType_t)((T0_FP_GLOG<<8)|T1_FP_GLOG_CONNECT_USER_LOGIN)

struct MSG_FP_GLOG_CONNECT_USER_NEW
{
	char AccountName[SIZE_MAX_ACCOUNT_NAME];		// �ű� ���� ����
};

struct MSG_FP_GLOG_CONNECT_USER_LOGIN
{
	char AccountName[SIZE_MAX_ACCOUNT_NAME];		// ���� ���� ���� �߰�
};
// end 2011-12-12 by hskim, GLog 2��


// 2013-03-14 by bckim, Glog ����߰�
#define T_FP_GLOG_NEW_ACCOUNT_INFO				(MessageType_t)((T0_FP_GLOG<<8)|T1_FP_GLOG_NEW_ACCOUNT_INFO)

struct MSG_FP_GLOG_NEW_ACCOUNT_INFO
{
	ATUM_DATE_TIME	RegisteredDate;					// ��������
	INT			Type;								// ����Ÿ��
	UID64_t		AccountUniqueNumber;				// ����������ȣ 
	char AccountName[SIZE_MAX_ACCOUNT_NAME];		// �����̸�
	CHAR		CertifyCode[USER_CI_SIZE];			// CI ��		// 2014-02-10 by jhseol&bckim, ü�θ� - �ѱ� ���� ���� �߰�����
};
// End. 2013-03-14 by bckim, Glog ����߰�

///////////////////////////////
// IP_CONNECT

typedef struct
{
	char		ServerGroupName[SIZE_MAX_SERVER_NAME];
	SERVER_ID	IMServerID;								// 2006-05-10 by cmkwon
	DWORD		Padding[SIZE_MAX_PACKET_PADDING];		// 2011-07-21 by hskim, ���� ���� ���� - ���� ������ ȣȯ �ȵǵ��� ����ü ũ�� �ٲ�
	// 2006-05-10 by cmkwon, IMServerID ������ ���� - IP ������ ����Ѵ�.
	//	int		IMServerListenPort;
} MSG_IP_CONNECT_IM_CONNECT;

typedef struct
{
	char	ServerGroupName[SIZE_MAX_SERVER_NAME];
	UINT	IMCurrentUserCounts;
	UINT	IMMaxUserCounts;
	DWORD	Padding[SIZE_MAX_PACKET_PADDING];		// 2011-07-21 by hskim, ���� ���� ���� - ���� ������ ȣȯ �ȵǵ��� ����ü ũ�� �ٲ�
} MSG_IP_GET_SERVER_GROUP_INFO_ACK;

struct MSG_IP_ADMIN_PETITION_SET_PERIOD
{// 2007-11-19 by cmkwon, �����ý��� ������Ʈ - MSG_IP_ADMIN_PETITION_SET_PERIOD ����ü �߰�
	BYTE			byIsImmediatOn;		// 2007-11-20 by cmkwon, ��� ���� �÷���
	BYTE			byIsImmediatOff;	// 2007-11-20 by cmkwon, ��� ���� �÷���
	ATUM_DATE_TIME	atStart;			// 2007-11-20 by cmkwon, ���� ��¥�ð�
	ATUM_DATE_TIME	atEnd;				// 2007-11-20 by cmkwon, ���� ��¥�ð�
};

///////////////////////////////
// FI_CONNECT

typedef struct
{
	SERVER_ID	FieldServerID;
	int			NumOfMapIndex;
	BOOL		ArenaServerCheck;		// 2008-02-28 by dhjin, �Ʒ��� ���� - 0:�Ϲ� ���Ӽ���, 1:�Ʒ������ռ���
	ARRAY_(MapIndex_t);					// array of MapIndexes
} MSG_FI_CONNECT;

typedef struct
{
	UID32_t		CharacterUniqueNumber;
	SERVER_ID	FieldServerID;
	//char		IPAddress[SIZE_MAX_IPADDRESS];
	DWORD		Padding[SIZE_MAX_PACKET_PADDING];		// 2011-07-21 by hskim, ���� ���� ���� - ���� ������ ȣȯ �ȵǵ��� ����ü ũ�� �ٲ�
} MSG_FI_CONNECT_NOTIFY_FIELDSERVER_IP;

typedef struct
{
	UID32_t	CharacterUniqueNumber;
} MSG_FI_CONNECT_NOTIFY_GAMEEND;


///////////////////////////////////////////////////////////////////////////////
struct MSG_PP_CONNECT		// 2008-02-22 by cmkwon, ServerPreServer->MasangPreServer �� ���� ���� ���� �ý��� �߰� - 
{
	int			nServiceUID;						// ����� ������� ����, ���� ó���� ���� �߰�
	int			nLanguageType;						// 
	char		szPreServerIP[SIZE_MAX_IPADDRESS];
	USHORT		nPreServerPort;
	BYTE		byIsOnlyChoiceServer;
	BYTE		byIsTestServer;
	BYTE		byIsUseExternalAuthentication;
	int			nPreServerGroupCnts;				// PreServer Count
	int			nEnableGameServerGroupCnts;			// Active ServerGroup Count
	char		szReserve[100];						// 
	char* GetWriteLogString(char* o_szLogString)
	{
		sprintf(o_szLogString, "%d|%d|%15s|%d|%d|%d|%d|%d|%d\r\n", nServiceUID, nLanguageType, szPreServerIP, nPreServerPort
			, byIsOnlyChoiceServer, byIsTestServer, byIsUseExternalAuthentication, nPreServerGroupCnts, nEnableGameServerGroupCnts);
		return o_szLogString;
	}
};

///////////////////////////////////////////////////////////////////////////////
// 2011-01-26 by hskim, ���� ���� ����
struct MSG_PATUM_CONNECT
{
	char		szGameName[SIZE_MAX_AUTH_GAMENAME];
	char		szServerIP[SIZE_MAX_IPADDRESS];
	USHORT		nServerPort;
	char		szCurrentVer[SIZE_MAX_AUTH_CURRENTVER];
	int			nLanguageType;
	BYTE		byTestServer;
	BYTE		byUseExternalAuthentication;
	int			nPreServerGroupCnts;
	int			nEnableGameServerGroupCnts;
	char		szReserve[50];
	char* GetWriteLogString(char* o_szLogString)
	{
		sprintf(o_szLogString, "%s|%s|%d|%s|%d|%d|%d|%d|%d\r\n", szGameName, szServerIP, nServerPort, szCurrentVer, nLanguageType,
			byTestServer, byUseExternalAuthentication, nPreServerGroupCnts, nEnableGameServerGroupCnts);

		return o_szLogString;
	}
};

struct MSG_PATUM_CONNECT_OK
{
	char		szReserve[100];
};

struct MSG_PATUM_CONNECT_FAIL
{
	char		szReserve[100];
};

// start 2011-06-22 by hskim, �缳 ���� ����
struct MSG_PATUM_CONNECT_SHUTDOWN
{
	char		szReserve[100];
};
// end 2011-06-22 by hskim, �缳 ���� ����

#if defined(_ATUM_SERVER)	// 2008-02-26 by cmkwon, Ŭ���̾�Ʈ���� ������ ���� ���� �ذ�
struct MSG_PP_CONNECT_OK		// 2008-02-22 by cmkwon, ServerPreServer->MasangPreServer �� ���� ���� ���� �ý��� �߰� - 
{
	char		szPreServerODBCDSN[SIZE_MAX_ODBC_CONN_STRING];		// ODBC_DSN
	char		szPreServerODBCUID[SIZE_MAX_ODBC_CONN_STRING];		// ODBC_UID
	char		szPreServerODBCPASSWORD[SIZE_MAX_ODBC_CONN_STRING];	// ODBC_PASSWD	
	char		szReserve[100];										// 
};
#endif

typedef struct
{
	UID32_t	CharacterUniqueNumber;
	MAP_CHANNEL_INDEX	MapChannelIndex;	// ��ȭ�� ������ �� �� �̸�
	INT		nNumOfTimer;					// ���� �ʵ� �������� ������ ���� 0
	ARRAY_(TIMER_EVENT_4_EXCHANGE);
} MSG_FI_EVENT_NOTIFY_WARP;					// ��ȭ�� �� �̸�, ���� Timer ����(���� �ʵ� �������� ������ ������ �ʴ´�), ���

struct MSG_FI_EVENT_CHAT_BLOCK				// 2008-12-30 by cmkwon, ������ ä�� ���� ī�� ���� - 
{
	char	szBlockedCharacterName[SIZE_MAX_CHARACTER_NAME];
	int		nBlockedMinutes;
};



// Just Declare
struct TIMER_EVENT;

struct TIMER_EVENT_4_EXCHANGE
{
	TimerEventType		Type;
	//	TimeUnit_t			StartTimeStamp;			// milli-seconds
	//	TimeUnit_t			ExpireTime;				// milli-seconds
	TimeUnit_t			TimeInterval;			// milli-seconds, (ExpireTime - StartTimeStamp)
	//	CFieldIOCPSocket	*pFieldIOCPSocket;
	UID32_t				CharacterUniqueNumber;	// event�� ������ charac�� ������ �ٸ� charac�� socket�� ����ϴ� ��츦 ���� ����, IsUsing()�� CharacterUniqueNumber�� ���ƾ� ��!
	//	ClientIndex_t		ClientIndex;			// event�� ������ charac�� ������ �ٸ� charac�� socket�� ����ϴ� ��츦 ���� ����, IsUsing()�� ClientIndex�� ���ƾ� ��!
	float				FloatParam1;			// delete_item��: ���� Endurance
	INT					IntParam1;				// delete_item��: ItemNum
	//	TIMER_EVENT_BUCKET	*pCurrentBucket;

		// operator overloading
	TIMER_EVENT_4_EXCHANGE& operator=(const TIMER_EVENT& rhs);
};

typedef struct
{
	UID32_t	CharacterUniqueNumber;
} MSG_FI_EVENT_NOTIFY_WARP_OK;			// �ٸ� �ʵ� �������� ������ ��츸 �޴´�

typedef struct
{
	UID32_t			CharacterUniqueNumber;
} MSG_FI_EVENT_GET_WARP_INFO;			// Party & TimerEvent����, �ٸ� �ʵ� �������� ������ ��� ���� ��û

typedef struct
{
	UID32_t			AccountUniqueNumber;		// �ٸ� �ʵ� �������� ������, ������ �ʿ���
	UID32_t			CharacterUniqueNumber;
	PartyID_t		PartyID;
	UID32_t			MasterCharacterUniqueNumber;
	USHORT			nPartyMembers;
	USHORT			nTimerEvents;
	ARRAY_(FI_PARTY_MEMBER_INFO);
	ARRAY_(TIMER_EVENT_4_EXCHANGE);
} MSG_FI_EVENT_GET_WARP_INFO_OK;		// Party & TimerEvent����, �ٸ� �ʵ� �������� ������ ��� ���� �ֱ�

typedef struct
{
	UID32_t	CharacterUniqueNumber;
	UID32_t AttackerGuildUID;
} MSG_FI_CONNECT_NOTIFY_DEAD;	// F->I, check: ����� DEAD�� ��Ƽ Ż�� ���ؼ� �������, 20030821, kelovon

typedef struct
{
	SERVER_ID	FieldServerID;
	UINT		AccumulatedFieldUserCounts;
	UINT		CurrentFieldUserCounts;
	UINT		MaxFieldUserCounts;
	UINT		AccumulatedFieldMonsterCounts;
	UINT		CurrentFieldMonsterCounts;
} MSG_FI_GET_FIELD_USER_COUNTS_ACK;

typedef enum
{
	GST_GAMESTART = 0,
	GST_CONN_GAMESTART = 1,
	GST_WARP_CONN_GAMESTART = 2,
	GST_WARP_SAME_MAP = 3,
	GST_WARP_SAME_FIELD_SERVER = 4
} GameStartType;

typedef struct {
	UID32_t			CharacterUniqueNumber;
	GameStartType	FieldGameStartType;
	MAP_CHANNEL_INDEX	MapChannelIndex;
} MSG_FI_CONNECT_NOTIFY_GAMESTART;				// F->I, ���� �������� �� IM Server�� �˸�, ��Ƽ ���� Ȯ�� ��û ��

typedef struct
{
	UID32_t			CharacterUniqueNumber;
} MSG_FI_CONNECT_NOTIFY_DEAD_GAMESTART;

struct MSG_FI_CONNECT_PREPARE_SHUTDOWN	// 2007-08-27 by cmkwon, �����ٿ��غ� ���ɾ� �߰�(SCAdminTool���� SCMonitor�� PrepareShutdown�� ���� �� �� �ְ�)
{
	BOOL			bPrepareShutdown;			// TURE�� �����ٿ� �غ� ����, FALSE�̸� �����ٿ� �غ� ����
};

///////////////////////////////
// IC_CONNECT

typedef	struct
{
	char	AccountName[SIZE_MAX_ACCOUNT_NAME];
	char	ServerName[SIZE_MAX_SERVER_NAME];
	char	CharacterName[SIZE_MAX_CHARACTER_NAME];
	char	Password[SIZE_MAX_PASSWORD_MD5_STRING];			// MD5
	BYTE	LoginType;						// see below
	DWORD	Padding[SIZE_MAX_PACKET_PADDING];		// 2011-07-21 by hskim, ���� ���� ���� - ���� ������ ȣȯ �ȵǵ��� ����ü ũ�� �ٲ�
} MSG_IC_CONNECT_LOGIN;

#define CHAT_LOGIN_TYPE_GAME		0x00
#define CHAT_LOGIN_TYPE_MESSENGER	0x01

typedef struct
{
	INT		reason;
} MSG_IC_CONNECT_CLOSE;

/*
// check: Ȯ�� �ʿ�
//typedef	struct
//{
//	BYTE					NumCharacters;
//	FC_CONNECT_LOGIN_INFO	Characters[3];
//} MSG_IC_CONNECT_LOGIN_OK;
//*/

///////////////////////////////
// FM_CONNECT
typedef struct
{
	char	ServerName[SIZE_MAX_SERVER_NAME];
	time_t	StartedTime;
	char	IPAddress[SIZE_MAX_IPADDRESS];
	USHORT	Port;
	USHORT	NumOfClients;
	BOOL	CalcBandwidth;
	USHORT	LoadedMapCounts;
} MSG_FM_CONNECT_OK;
typedef MSG_FM_CONNECT_OK		MSG_NM_CONNECT_OK;
typedef MSG_FM_CONNECT_OK		MSG_IM_CONNECT_OK;

///////////////////////////////
// PM_CONNECT
typedef struct
{
	char	ServerName[SIZE_MAX_SERVER_NAME];
	time_t	StartedTime;
	char	IPAddress[SIZE_MAX_IPADDRESS];
	USHORT	Port;
	USHORT	NumOfClients;
	BOOL	CalcBandwidth;
	USHORT	LoadedMapCounts;
	int		nMGameEventType;
	// 2007-01-08 by cmkwon, �޽��� ����ü�� Ŀ���� T_PM_AUTO_UPDATE_FTP_SERVER_SETTING �������ݷ� ����
	//	char	FtpIP[SIZE_MAX_FTP_URL];
	//	USHORT	FtpPort;
	//	char	FtpAccountName[SIZE_MAX_ACCOUNT_NAME];
	//	char	FtpPassword[SIZE_MAX_PASSWORD];
	//	char	ClientFTPUpdateUploadDir[SIZE_MAX_FTP_FILE_PATH];	// UPDATE_DIR
	//	char	LauncherFileUploadPath[SIZE_MAX_FTP_FILE_PATH];	// LAUNCHER_FILE_NAME
	//	char	DeleteFileListUploadPath[SIZE_MAX_FTP_FILE_PATH];	// DELFILELIST_FILE_NAME
	//	char	NoticeFileUploadPath[SIZE_MAX_FTP_FILE_PATH];		// NOTICE_FILE_NAME
} MSG_PM_CONNECT_OK;

///////////////////////////////
// IC_CHAT
typedef struct
{
	char	FromCharacterName[SIZE_MAX_CHARACTER_NAME];
	BYTE	MessageLength;
	//�ڿ� �޽����� �ٿ��� ������
	//char*	ChatMessage;
} MSG_IC_CHAT_MAP;

typedef MSG_IC_CHAT_MAP						 MSG_IC_CHAT_REGION;

typedef struct
{
	char	FromCharacterName[SIZE_MAX_CHARACTER_NAME];
	char	ToCharacterName[SIZE_MAX_CHARACTER_NAME];
	BYTE	FromInflTy;				// 2007-11-19 by cmkwon, �����ý��� ������Ʈ - MSG_IC_CHAT_PTOP ����ü�� ������� ���� �ʵ� �߰�
	BYTE	MessageLength;
	//�ڿ� �޽����� �ٿ��� ������
	//char*	ChatMessage;
} MSG_IC_CHAT_PTOP;

typedef MSG_IC_CHAT_MAP						MSG_IC_CHAT_PARTY;
typedef MSG_IC_CHAT_MAP						MSG_IC_CHAT_GUILD;
typedef MSG_IC_CHAT_MAP						MSG_IC_CHAT_ALL;
typedef MSG_IC_CHAT_MAP						MSG_IC_CHAT_CHATROOM;		// 2008-06-18 by dhjin, EP3 ä�ù� - 

typedef struct
{
	UID32_t	CharacterUniqueNumber;
} MSG_IC_CHAT_GET_GUILD;

typedef struct
{
	UID32_t	CharacterUniqueNumber;
	char	CharacterName[SIZE_MAX_CHARACTER_NAME];
	BYTE	ConnectionCondition;			// ������,�޽���,����
} MSG_IC_CHAT_GET_GUILD_OK;

typedef struct
{
	UID32_t	CharacterUniqueNumber;
	char	CharacterName[SIZE_MAX_CHARACTER_NAME];
	char	Guild[SIZE_MAX_GUILD_NAME];
	BYTE	Joined;							// ���� ����
} MSG_IC_CHAT_CHANGE_GUILD;

typedef struct
{
	UID32_t	CharacterUniqueNumber;
	char	CharacterName[SIZE_MAX_CHARACTER_NAME];
	char	Guild[SIZE_MAX_GUILD_NAME];
	BYTE	Joined;							// ���� ����
} MSG_IC_CHAT_CHANGE_GUILD_OK;

typedef struct
{
	UID32_t	CharacterUniqueNumber;
	char	PartyName[20];
	BYTE	Joined;			// ����, Ż��
} MSG_IC_CHAT_CHANGE_PARTY;

typedef struct
{
	UID32_t	CharacterUniqueNumber;
	char	PartyName[20];
	BYTE	Joined;			// ����, Ż��
} MSG_IC_CHAT_CHANGE_PARTY_OK;

typedef struct
{
	// 2008-05-15 by dhjin, EP3 - ä�� �ý��� ����
//	BitFlag8_t	bitChatType;	// see below
	BitFlag16_t	bitChatType;	// see below
} MSG_IC_CHAT_CHANGE_CHAT_FLAG;

typedef MSG_IC_CHAT_MAP				MSG_IC_CHAT_SELL_ALL;
typedef MSG_IC_CHAT_MAP				MSG_IC_CHAT_CASH_ALL;
typedef MSG_IC_CHAT_MAP				MSG_IC_CHAT_INFLUENCE_ALL;			// 2006-04-21 by cmkwon
typedef MSG_IC_CHAT_MAP				MSG_IC_CHAT_ARENA;					// 2007-05-02 by dhjin
typedef MSG_IC_CHAT_MAP				MSG_IC_CHAT_WAR;					// 2008-05-19 by dhjin, EP3 - ä�� �ý��� ����, ���� ä��
#if _RAT_CHAT_SYSTEM
typedef MSG_IC_CHAT_MAP				MSG_IC_CHAT_INFLUENCE_ALL_RAT;
#endif
typedef MSG_IC_CHAT_MAP				MSG_IC_CHAT_INFINITY;				// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ä��

// 2008-05-15 by dhjin, EP3 - ä�� �ý��� ����
//	#define CHAT_TYPE_UNCONDITIONAL	(BitFlag8_t)0x01	// disable �Ұ�, (���� ����, ���� ��ü ä��, ����ä��)
//	#define CHAT_TYPE_SELL_ALL		(BitFlag8_t)0x02	// disable ����, �Ÿ� ��ü ä��
//	#define CHAT_TYPE_MAP			(BitFlag8_t)0x04	// disable ����, �� ä��
//	#define CHAT_TYPE_PTOP			(BitFlag8_t)0x08	// disable ����, 1:1 ä�� 
//	#define CHAT_TYPE_GUILD			(BitFlag8_t)0x10	// disable ����, ��� ä��
//	#define CHAT_TYPE_PARTY			(BitFlag8_t)0x20	// disable ����, ��Ƽ ä��
//	#define CHAT_TYPE_INFLUENCE		(BitFlag8_t)0x40	// disable �Ұ�
//	#define CHAT_TYPE_ARENA			(BitFlag8_t)0x80	// disable �Ұ�, ARENA ä��
#define CHAT_TYPE_UNCONDITIONAL	(BitFlag16_t)0x0001	// disable �Ұ�, (���� ����, ���� ��ü ä��, ����ä��)
#define CHAT_TYPE_SELL_ALL		(BitFlag16_t)0x0002	// disable ����, �Ÿ� ��ü ä��
#define CHAT_TYPE_MAP			(BitFlag16_t)0x0004	// disable ����, �� ä��
#define CHAT_TYPE_PTOP			(BitFlag16_t)0x0008	// disable ����, 1:1 ä�� 
#define CHAT_TYPE_GUILD			(BitFlag16_t)0x0010	// disable ����, ��� ä��
#define CHAT_TYPE_PARTY			(BitFlag16_t)0x0020	// disable ����, ��Ƽ ä��
#define CHAT_TYPE_INFLUENCE		(BitFlag16_t)0x0040	// disable �Ұ�
#define CHAT_TYPE_ARENA			(BitFlag16_t)0x0080	// disable �Ұ�, ARENA ä��
#define CHAT_TYPE_WAR			(BitFlag16_t)0x0100	// 2008-05-15 by dhjin, EP3 - ä�� �ý��� ����,	���� ä�� 
#define CHAT_TYPE_CHATROOM		(BitFlag16_t)0x0200	// 2008-05-15 by dhjin, EP3 - ä�� �ý��� ����, ä�ù� 
#define CHAT_TYPE_SYSTEM		(BitFlag16_t)0x0400	// 2008-05-15 by dhjin, EP3 - ä�� �ý��� ����, �ý��� 
#define CHAT_TYPE_HELPDESK		(BitFlag16_t)0x0800	// 2008-05-15 by dhjin, EP3 - ä�� �ý��� ����, ����

#define COMPARE_CHATTYPE_BIT(VAR, MASK)	(((VAR) & (MASK)) != 0)
#define CLEAR_CHATTYPE_BIT(VAR, MASK)	{ (VAR) &= ~(MASK); }
#define SET_CHATTYPE_BIT(VAR, MASK)		{ (VAR) |= (MASK); }

typedef struct
{
	UID32_t		CharacterUniqueNumber;
	AVECTOR3	PosVector;
} MSG_IC_CHAT_POSITION;

typedef enum
{
	FRIEND_TYPE_FRIEND = 0,
	FRIEND_TYPE_REJECT = 1
} FRIEND_TYPE;

typedef struct
{
	char	CharacterName[SIZE_MAX_CHARACTER_NAME];
	char	FriendName[SIZE_MAX_CHARACTER_NAME];
	BYTE	FriendType;
	ATUM_DATE_TIME	RegDate;	// 2008-04-11 by dhjin, EP3 �źθ�� -
} DB_FRIEND_INFO;

typedef struct
{
	char		szCharacterName[SIZE_MAX_CHARACTER_NAME];
	BYTE		byIsOnline;
	ATUM_DATE_TIME	RegDate;	// 2008-04-11 by dhjin, EP3 �źθ�� -
} FRIENDINFO;

typedef struct
{
	int			nFriendListCounts;
	ARRAY_(FRIENDINFO);
} MSG_IC_CHAT_FRIENDLIST_LOADING_OK;

typedef struct
{
	char szCharacterName[SIZE_MAX_CHARACTER_NAME];
} MSG_IC_CHAT_FRIENDLIST_INSERT;

typedef FRIENDINFO							MSG_IC_CHAT_FRIENDLIST_INSERT_OK;

typedef MSG_IC_CHAT_FRIENDLIST_INSERT		MSG_IC_CHAT_FRIENDLIST_DELETE;

typedef MSG_IC_CHAT_FRIENDLIST_INSERT		MSG_IC_CHAT_REJECTLIST_DELETE_OK;

struct MSG_IC_CHAT_FRIENDLIST_INSERT_NOTIFY		// 2009-01-13 by cmkwon, ģ�� ��Ͻ� ���濡�� �˸� �ý��� ���� - 
{
	char szDoerCharacName[SIZE_MAX_CHARACTER_NAME];	// ģ�� ��Ͻ� ������ �¶��� ������ ��� �˸�
};

typedef MSG_IC_CHAT_FRIENDLIST_LOADING_OK	MSG_IC_CHAT_FRIENDLIST_REFRESH_OK;

typedef struct
{
	int			nRejectListCounts;
	ARRAY_(FRIENDINFO);
} MSG_IC_CHAT_REJECTLIST_LOADING_OK;

typedef MSG_IC_CHAT_FRIENDLIST_INSERT		MSG_IC_CHAT_REJECTLIST_INSERT;

//////////////////////////////////////////////////////////////////////////
// 2008-04-11 by dhjin, EP3 �źθ�� - �ذ� ���� ����
// typedef MSG_IC_CHAT_FRIENDLIST_INSERT		MSG_IC_CHAT_REJECTLIST_INSERT_OK;
typedef struct
{
	char szCharacterName[SIZE_MAX_CHARACTER_NAME];
	ATUM_DATE_TIME	RegDate;
} MSG_IC_CHAT_REJECTLIST_INSERT_OK;

typedef MSG_IC_CHAT_FRIENDLIST_INSERT		MSG_IC_CHAT_REJECTLIST_DELETE;

typedef MSG_IC_CHAT_FRIENDLIST_INSERT		MSG_IC_CHAT_FRIENDLIST_DELETE_OK;



///////////////////////////////
// FC_CHAT
typedef MSG_IC_CHAT_MAP					MSG_FC_CHAT_MAP;
typedef MSG_IC_CHAT_REGION				MSG_FC_CHAT_REGION;
typedef MSG_IC_CHAT_CASH_ALL			MSG_FC_CHAT_CASH_ALL;
typedef MSG_IC_CHAT_ARENA				MSG_FC_CHAT_ARENA;
typedef MSG_IC_CHAT_MAP					MSG_FC_CHAT_OUTPOST_GUILD;	// 2007-10-06 by cmkwon, ���� ���� ������ ������ ���� ä�� ����
typedef MSG_IC_CHAT_INFINITY			MSG_FC_CHAT_INFINITY;		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ä��

struct MSG_FC_CHAT_ALL_INFLUENCE		// 2007-08-09 by cmkwon, ��� ���¿� ä�� �����ϱ� - ����ü �߰�
{
	char	FromCharacterName[SIZE_MAX_CHARACTER_NAME];
	char	str256ChatMsg[SIZE_MAX_STRING_256];			// 2007-08-09 by cmkwon, ��� ���¿� ä�� �����ϱ� - 
};

///////////////////////////////
// FI_CHAT
typedef struct
{
	UID32_t	CharacterUniqueNumber;
	BYTE	MessageLength;
	//�ڿ� �޽����� �ٿ��� ������
	//char*	ChatMessage;
} MSG_FI_CHAT_MAP;

typedef MSG_FI_CHAT_MAP					MSG_FI_CHAT_REGION;

typedef struct
{
	UID32_t		CharacterUniqueNumber;
	// 2008-05-15 by dhjin, EP3 - ä�� �ý��� ����
	//	BitFlag8_t	ChatFlag;				// ä�� ���� flag
	BitFlag16_t	ChatFlag;				// ä�� ���� flag
} MSG_FI_CHAT_CHANGE_CHAT_FLAG;

typedef MSG_FI_CHAT_MAP					MSG_FI_CHAT_CASH_ALL;
typedef MSG_FI_CHAT_MAP					MSG_FI_CHAT_ARENA;		// 2007-05-02 by dhjin
typedef MSG_FI_CHAT_MAP					MSG_FI_CHAT_OUTPOST_GUILD;		// 2007-10-06 by cmkwon, ���� ���� ������ ������ ���� ä�� ����
typedef MSG_FI_CHAT_MAP					MSG_FI_CHAT_INFINITY;		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ä��

struct MSG_FI_CHAT_ONLINE_EACHOTHER_FRIEND_COUNT_OK		// 2006-07-18 by cmkwon
{
	UID32_t		CharacterUniqueNumber;
	int			OnlineFriendCnts;			// 2006-07-18 by cmkwon, ���� ����� �¶��� ģ�� ī��Ʈ	
};

struct MSG_IC_CHAT_ONLINE_EACHOTHER_FRIEND_COUNT
{// 2008-07-11 by dhjin, EP3 ģ����� -
	int			OnlineFriendCnts;
};

///////////////////////////////
// FC_CHARACTER
typedef struct
{
	UID32_t		AccountUniqueNumber;
	UID32_t		CharacterUniqueNumber;
	// START 2011-11-03 by shcho, yedang �˴ٿ��� ���� - ���������� �߰��� �޾ƿ´�.
	BOOL     ShutDownMINS;
	// END 2011-11-03 by shcho, yedang �˴ٿ��� ���� - ���������� �߰��� �޾ƿ´�.
} MSG_FC_CHARACTER_GET_CHARACTER;

typedef struct
{
	CHARACTER	Character;
	//char		FieldServerIP[SIZE_MAX_IPADDRESS];		// MSG_FC_CHARACTER_GAMESTART_OK�� �̵�
} MSG_FC_CHARACTER_GET_CHARACTER_OK;

typedef struct
{
	UID32_t		AccountUniqueNumber;
	char		CharacterName[SIZE_MAX_CHARACTER_NAME];
	USHORT		UnitKind;
	USHORT		Race;
	BYTE		AutoStatType1;
	GEAR_STAT	GearStat1;			// ��� ����
	BYTE		Gender;
	BYTE		PilotFace;
	BYTE		InfluenceType0;		// 2005-06-23 by cmkwon, ���� Ÿ������ ���߿� ��� ���� �ʵ�
} MSG_FC_CHARACTER_CREATE;

typedef struct
{
	CHARACTER				Character;
	CHARACTER_RENDER_INFO	CharacterRenderInfo;		// 2006-01-23 by cmkwon, �߰���
} MSG_FC_CHARACTER_CREATE_OK;

struct MSG_FC_CHARACTER_DELETE
{
	UID32_t	AccountUniqueNumber;
	UID32_t	CharacterUniqueNumber;
	char	CurrentSecPassword[SIZE_MAX_PASSWORD_MD5_STRING];	// 2007-09-13 by cmkwon, ��Ʈ�� 2���н����� ���� - MSG_FC_CHARACTER_DELETE �� �ʵ� �߰�
};

/* This message has NO body
//typedef struct
//{
//} MSG_FC_CHARACTER_DELETE_OK;
*/

typedef struct
{
	UID32_t	CharacterUniqueNumber;
} MSG_FC_CHARACTER_REPAIR;

typedef struct
{
	INT	RepairCharge;
	INT	Remainder;
} MSG_FC_CHARACTER_REPAIR_OK;


typedef struct
{
	BYTE	ErrCode;
} MSG_FC_CHARACTER_REPAIR_ERR;

// Repair Error Code
#define ERROR_REPAIR_NOERROR			0x00
#define ERROR_REPAIR_NOT_ENOUGH_MONEY	0x01

typedef struct
{
	UINT	ItemIndex;
} MSG_FC_CHARACTER_DOCKING;

typedef struct
{
	UINT	 ItemIndex;
} MSG_FC_CHARACTER_UNDOCKING;

typedef struct
{
	BYTE	 ErrCode;
} MSG_FC_CHARACTER_DOCKING_ERR;

// Docking Error Code
#define ERROR_DOCKING_NOERROR			0x00
#define ERROR_DOCKING_NO_SUCH_ITEM		0x01
#define ERROR_DOCKING_INVALID_POSITION	0x02

typedef struct
{
	ClientIndex_t	ClientIndex;
	UID32_t			CharacterUniqueNumber;
} MSG_FC_CHARACTER_GAMESTART;

struct MSG_FC_CHARACTER_GAMESTART_OK
{
	ClientIndex_t	ClientIndex;
	char			FieldServerIP[SIZE_MAX_IPADDRESS];
	int				FieldServerPort;
	BYTE			CharacterMode0;
	AVECTOR3		PositionVector;
	BitFlag16_t		MapWeather;
	BOOL			bMemberPCBang;			// 2007-01-25 by cmkwon, ���� PC�� �÷���
	char			ServerGroupName0[SIZE_MAX_SERVER_NAME];			// 2007-04-09 by cmkwon
	char			MainORTestServerName[SIZE_MAX_SERVER_NAME];		// 2007-04-09 by cmkwon
	char			GamePublisher[SIZE_MAX_GAME_PUBLISHER_NAME];	// 2007-04-09 by cmkwon
	MAP_CHANNEL_INDEX MapInfo;				// 2007-12-12 by dhjin, ������ �̸� ������
	BodyCond_t		BodyCondition;			// 2008-04-01 by cmkwon, ���øʿ��� ���� ������ ��� ��Ȱ���Ѽ� ĳ���� ���·� ó�� - MSG_FC_CHARACTER_GAMESTART_OK �� �߰�
	float			CurrentHP;				// 2008-04-01 by cmkwon, ���øʿ��� ���� ������ ��� ��Ȱ���Ѽ� ĳ���� ���·� ó�� - MSG_FC_CHARACTER_GAMESTART_OK �� �߰�
	float			CurrentDP;				// 2008-04-01 by cmkwon, ���øʿ��� ���� ������ ��� ��Ȱ���Ѽ� ĳ���� ���·� ó�� - MSG_FC_CHARACTER_GAMESTART_OK �� �߰�
	float			CurrentEP;				// 2008-04-01 by cmkwon, ���øʿ��� ���� ������ ��� ��Ȱ���Ѽ� ĳ���� ���·� ó�� - MSG_FC_CHARACTER_GAMESTART_OK �� �߰�
	float			CurrentSP;				// 2008-04-01 by cmkwon, ���øʿ��� ���� ������ ��� ��Ȱ���Ѽ� ĳ���� ���·� ó�� - MSG_FC_CHARACTER_GAMESTART_OK �� �߰�
	DWORD			Padding[SIZE_MAX_PACKET_PADDING];				// 2011-07-21 by hskim, ���� ���� ���� - ���� ������ ȣȯ �ȵǵ��� ����ü ũ�� �ٲ�
};

typedef struct
{
	char	AccountName[SIZE_MAX_ACCOUNT_NAME];
	char	Password[SIZE_MAX_PASSWORD_MD5_STRING];
	char	PrivateIP[SIZE_MAX_IPADDRESS];
	UID32_t	AccountUniqueNumber;
	UID32_t	CharacterUniqueNumber;
	DWORD	Padding[SIZE_MAX_PACKET_PADDING];				// 2011-07-21 by hskim, ���� ���� ���� - ���� ������ ȣȯ �ȵǵ��� ����ü ũ�� �ٲ�
} MSG_FC_CHARACTER_CONNECT_GAMESTART;

typedef struct
{
	ClientIndex_t	ClientIndex;
	AVECTOR3		PositionVector;
	BitFlag16_t		MapWeather;
} MSG_FC_CHARACTER_CONNECT_GAMESTART_OK;

typedef struct
{
	ClientIndex_t	ClientIndex;
	UID32_t			CharacterUniqueNumber;
	BOOL			bRebirthInCityMap;			// TRUE:���º����ø� ��Ȱ, FALSE:����ʿ��� ��Ȱ
} MSG_FC_CHARACTER_DEAD_GAMESTART;

typedef struct {
	UID32_t			CharacterUniqueNumber;
} MSG_FC_CHARACTER_OTHER_REVIVED;	// F -> C, �׾��� �ǻ�Ƴ��� �� �ٸ� ĳ����(����� ��Ƽ��)���� ����

typedef struct
{
	ClientIndex_t	ClientIndex;
	BOOL			SelectCharacterView;		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - �ɸ��� ���� â���� �̵��̸� TRUE	
} MSG_FC_CHARACTER_GAMEEND;

typedef struct
{
	ClientIndex_t	ClientIndex;
} MSG_FC_CHARACTER_GAMEEND_OK;

typedef struct
{
	ClientIndex_t	ClientIndex;
	USHORT			UnitKind;
} MSG_FC_CHARACTER_CHANGE_UNITKIND;

typedef struct
{
	ClientIndex_t	ClientIndex;
	GEAR_STAT		GearStat1;		// ��� ����
	BYTE			BonusStat;		// ���� ���ʽ� ����
} MSG_FC_CHARACTER_CHANGE_STAT;
typedef struct
{
	ClientIndex_t	ClientIndex;
	BYTE			byAutoStatType;
	GEAR_STAT		GearStat1;		// ��� ����
} MSG_FC_CHARACTER_CHANGE_TOTALGEAR_STAT;

typedef struct
{
	ClientIndex_t	ClientIndex;
	char			Guild[SIZE_MAX_GUILD_NAME];
} MSG_FC_CHARACTER_CHANGE_GUILD;

typedef struct
{
	ClientIndex_t	ClientIndex;
	BYTE			Level;
	BYTE			BonusStat;
	// 2005-11-15 by cmkwon, ������
	//	BYTE			BonusSkillPoint;
} MSG_FC_CHARACTER_CHANGE_LEVEL;

typedef struct
{
	ClientIndex_t	ClientIndex;
	Experience_t	Experience;						// �� ����ġ
} MSG_FC_CHARACTER_CHANGE_EXP;

typedef struct
{
	ClientIndex_t	ClientIndex;
	BodyCond_t		BodyCondition;					// ���� 32bit�� ��� <-- check: ��ų bodycon�� �������� �����ϱ�!
} MSG_FC_CHARACTER_CHANGE_BODYCONDITION;

typedef struct
{
	ClientIndex_t	ClientIndex;
	BodyCond_t		SkillBodyCondition;				// ���� 32bit�� ��� <-- check: ��ų bodycon�� �������� �����ϱ�!
} MSG_FC_CHARACTER_CHANGE_BODYCONDITION_SKILL;

struct MSG_FC_CHARACTER_CHANGE_INFLUENCE_TYPE
{
	ClientIndex_t	ClientIndex;
	BYTE			InfluenceType0;					// 
};

typedef struct
{
	ClientIndex_t	ClientIndex;
	BodyCond_t		BodyCondition;					// ���� 32bit�� ��� <-- check: ��ų bodycon�� �������� �����ϱ�!
} MSG_FC_CHARACTER_CHANGE_BODYCONDITION_ALL;		// C->F, ������ BodyCondition ���� ��û

typedef struct
{
	ClientIndex_t	ClientIndex;
	BYTE			byUpdateType;					// 2005-08-22 by cmkwon, ����� �ΰ�(IUT_PENALTY_ON_DEAD, IUT_PENALTY_AGEAR_FUEL_ALLIN) - IUT_XXX, ITEM_UPDATE_TYPE_XXX
	INT				Propensity;
} MSG_FC_CHARACTER_CHANGE_PROPENSITY;				// 2005-08-22 by cmkwon, 

typedef struct
{
	ClientIndex_t	ClientIndex;
	BYTE			Status;
} MSG_FC_CHARACTER_CHANGE_STATUS;

typedef struct
{
	ClientIndex_t	ClientIndex;
	INT				Propensity;
	USHORT			PKWinPoint;
	USHORT			PKLossPoint;
} MSG_FC_CHARACTER_CHANGE_PKPOINT;

typedef struct
{
	ClientIndex_t	ClientIndex;
	SHORT	HP;
	SHORT	DP;
	SHORT	SP;
	SHORT	EP;
	float	CurrentHP;
	float	CurrentDP;
	SHORT	CurrentSP;
	float	CurrentEP;
} MSG_FC_CHARACTER_CHANGE_HPDPSPEP;

typedef struct
{
	ClientIndex_t	ClientIndex;
	float	CurrentHP;
	float	CurrentDP;
	SHORT	CurrentSP;
	float	CurrentEP;
} MSG_FC_CHARACTER_CHANGE_CURRENTHPDPSPEP;

typedef struct
{
	ClientIndex_t	ClientIndex;
	float			CurrentHP;
} MSG_FC_CHARACTER_CHANGE_CURRENTHP;

typedef struct
{
	ClientIndex_t	ClientIndex;
	float			CurrentDP;
} MSG_FC_CHARACTER_CHANGE_CURRENTDP;

typedef struct
{
	ClientIndex_t	ClientIndex;
	SHORT			CurrentSP;
} MSG_FC_CHARACTER_CHANGE_CURRENTSP;

typedef struct
{
	ClientIndex_t	ClientIndex;
	float			CurrentEP;
} MSG_FC_CHARACTER_CHANGE_CURRENTEP;

typedef struct
{
	ClientIndex_t		ClientIndex;
	MAP_CHANNEL_INDEX	MapChannelIndex;
} MSG_FC_CHARACTER_CHANGE_MAPNAME;

typedef struct
{
	ClientIndex_t	ClientIndex;
	BYTE			Level;
	Experience_t	Experience;
} MSG_FC_CHARACTER_CHANGE_PETINFO;

typedef struct
{
	ClientIndex_t	ClientIndex;
	AVECTOR3		PositionVector;		// ĳ���� ��ǥ
} MSG_FC_CHARACTER_CHANGE_POSITION;

typedef struct
{
	ClientIndex_t	ClientIndex;
	BYTE	KindOfStat;	// see below
} MSG_FC_CHARACTER_USE_BONUSSTAT;

struct MSG_FC_CHARACTER_USE_BONUSSTAT_OK		// 2006-09-18 by cmkwon
{
	BYTE	byReaminBonusStat;
};

struct MSG_FC_CHARACTER_DEAD_NOTIFY
{
	ClientIndex_t	ClientIndex;
	BYTE			byDamageKind;
	BOOL			bDeadByP2PPK;	// P2PPK ������ ����
};


#define COUNT_MAX_STAT_POINT			(CHARACTER_LEVEL_110_MAX_STAT_POINT)	// 2009-12-29 by cmkwon, ĳ���� �ִ� ���� ����(110����) - 100Lv�̻��� 340�� �ִ�

// Kind of Stat, STAT_XXX
#define STAT_ATTACK_PART				((BYTE)0)	// ���� ��Ʈ
#define STAT_DEFENSE_PART				((BYTE)1)	// ��� ��Ʈ
#define STAT_FUEL_PART					((BYTE)2)	// ���� ��Ʈ
#define STAT_SOUL_PART					((BYTE)3)	// ���� ��Ʈ
#define STAT_SHIELD_PART				((BYTE)4)	// ���� ��Ʈ
#define STAT_DODGE_PART					((BYTE)5)	// ȸ�� ��Ʈ
#define STAT_BONUS						((BYTE)6)	// ���ʽ��� �޴� stat
#define STAT_ALL_PART					((BYTE)7)	// ��� ��Ʈ
#define STAT_BONUS_STAT_POINT			((BYTE)8)	// 2007-06-20 by cmkwon, ���ʽ� ���� ���� �α� ����� - ���ʽ��� �޴� statPoint

///////////////////////////////////////////////////////////////////////////////
// ĳ�� ������ Level 20������ 
#define AUTOSTAT_TYPE_FREESTYLE					0	// ����� ������
#define AUTOSTAT_TYPE_BGEAR_ATTACK				1	// B-Gear ������
#define AUTOSTAT_TYPE_BGEAR_MULTI				2	// B-Gear ��Ƽ��
#define AUTOSTAT_TYPE_IGEAR_ATTACK				3	// I-Gear ������
#define AUTOSTAT_TYPE_IGEAR_DODGE				4	// I-Gear ȸ����
#define AUTOSTAT_TYPE_AGEAR_ATTACK				5	// A-Gear ������
#define AUTOSTAT_TYPE_AGEAR_SHIELD				6	// A-Gear ������
#define AUTOSTAT_TYPE_MGEAR_DEFENSE				7	// M-Gear �����
#define AUTOSTAT_TYPE_MGEAR_SUPPORT				8	// M-Gear ������

typedef struct
{
	ClientIndex_t		ClientIndex;
} MSG_FC_CHARACTER_GET_OTHER_INFO;

#define CITYWAR_TEAM_TYPE_NORMAL				0	// �������������� �ƴϰų� ������������ ���۾ȵ�
#define CITYWAR_TEAM_TYPE_ATTACKER				1	// ������, ������
#define CITYWAR_TEAM_TYPE_DEFENSER				2	// �����, 

struct MEX_OTHER_CHARACTER_INFO
{
	// 2009-08-26 by cmkwon, �׷��� ���ҽ� ���� �ý��� ���� - �Ʒ��� ���� �ʵ� ������ �����Ѵ�.
	BodyCond_t		BodyCondition;
	INT				Propensity;			// 2005-12-27 by cmkwon, ����(��,��)�� �ƴϰ� �������� �����
	UID32_t			CharacterUniqueNumber;
	// 2009-08-26 by cmkwon, �׷��� ���ҽ� ���� �ý��� ���� - ������� �����Ƿ� ����
	//	INT				RacingPoint;		// Racing ��� Point
	UID32_t			GuildUniqueNumber;
	MAP_CHANNEL_INDEX	MapChannelIndex;		// ĳ���Ͱ� ���� �� �� ä��, 2006-01-18 by cmkwon, �߰���
	AVECTOR3		PositionVector;
	AVECTOR3		TargetVector;
	AVECTOR3		UpVector;
	ClientIndex_t	ClientIndex;
	USHORT			Race;
	USHORT			UnitKind;
	USHORT			PKWinPoint;			// PK �¸� ��ġ
	USHORT			PKLossPoint;		// PK �й� ��ġ
	char			CharacterName[SIZE_MAX_CHARACTER_NAME];
	char			szCharacterMent[SIZE_STRING_32];
	BYTE			Gender;				// false(0) : ��, true(1) : ��
	BYTE			PilotFace;			// ȭ�鿡 ��Ÿ���� �ι� ĳ����
	BYTE			CharacterMode0;		// 2005-07-13 by cmkwon, ���� ĳ���� ���� �÷���
	BYTE			InfluenceType;		// ���� Ÿ��, 2005-06-23 by cmkwon
	BYTE			Level1;				//
	BYTE			CityWarTeamType;	// 
	BYTE			Status;				// �ź�
	BYTE			UsingReturnItem;				// 2013-02-28 by bckim, �������� �����߰�

	// operator overloading
	MEX_OTHER_CHARACTER_INFO& operator=(const CHARACTER& rhs)
	{
		ClientIndex = rhs.ClientIndex;
		CharacterUniqueNumber = rhs.CharacterUniqueNumber;
		STRNCPY_MEMSET(CharacterName, rhs.CharacterName, SIZE_MAX_CHARACTER_NAME);
		Gender = rhs.Gender;
		PilotFace = rhs.PilotFace;
		CharacterMode0 = rhs.CharacterMode;
		InfluenceType = rhs.InfluenceType;
		Race = rhs.Race;
		UnitKind = rhs.UnitKind;
		Level1 = rhs.Level;
		Propensity = rhs.Propensity;
		Status = rhs.Status;
		PKWinPoint = rhs.PKWinPoint;
		PKLossPoint = rhs.PKLossPoint;
		// 2009-08-26 by cmkwon, �׷��� ���ҽ� ���� �ý��� ���� - ������� �����Ƿ� ����
		//		RacingPoint				= rhs.RacingPoint;
		GuildUniqueNumber = rhs.GuildUniqueNumber;
		BodyCondition = rhs.BodyCondition;
		MapChannelIndex = rhs.MapChannelIndex;
		PositionVector = rhs.PositionVector;
		TargetVector = rhs.TargetVector * 1000.0f;
		UpVector = rhs.UpVector;
		UsingReturnItem = rhs.bUsingReturnItem;		// 2013-02-28 by bckim, �������� �����߰�

		return *this;
	}
};

typedef struct
{
	MEX_OTHER_CHARACTER_INFO	CharacterInfo;
	CHARACTER_RENDER_INFO		CharacterRenderInfo;
} MSG_FC_CHARACTER_GET_OTHER_INFO_OK;

typedef struct
{
	ClientIndex_t	MonsterIndex;
	INT				CurrentHP;
	INT				MonsterUnitKind;
	SHORT			MonsterForm;
	AVECTOR3		PositionVector;
	AVECTOR3		TargetVector;
	BodyCond_t		BodyCondition;
	INT				MaxHP;
} MSG_FC_CHARACTER_GET_MONSTER_INFO_OK;

typedef struct
{
	char		CharacterName[SIZE_MAX_CHARACTER_NAME];	// ��ȭ ���
} MSG_FC_CHARACTER_GET_ACCOUNTUNIQUENUMBER;				// ��ȭ ��û �� �ʿ���

typedef struct
{
	char		CharacterName[SIZE_MAX_CHARACTER_NAME];	// ��ȭ ���
	UID32_t		AccountUniqueNumber;					// ��ȭ ���
} MSG_FC_CHARACTER_GET_ACCOUNTUNIQUENUMBER_OK;			// ��ȭ ��û �� �ʿ���

// �浹 Ÿ��
#define COLLISION_TYPE_LAND			(BYTE)0x00	// ��, �� ���� �������� �浹
#define COLLISION_TYPE_BUILDING		(BYTE)0x01	// �ǹ����� �浹
#define COLLISION_TYPE_CHARACTER	(BYTE)0x02	// �ٸ� ĳ���Ϳ��� �浹
#define COLLISION_TYPE_MONSTER		(BYTE)0x03	// ���Ϳ��� �浹
struct MSG_FC_CHARACTER_APPLY_COLLISION_DAMAGE
{
	ClientIndex_t	UnitIndex;								// ���Ϳ� �浹�ô� �浹 ���� Index, ĳ���� �浹�ô� �浹 ĳ���� Index
	SHORT			SpeedOfCollision;						// �浹�� ���� ���ǵ�
	BYTE			CollisionType;							// �浹 Ÿ��, see below
};


typedef struct
{
	ClientIndex_t	OtherClientIndex;
} MSG_FC_CHARACTER_GET_OTHER_MOVE;			// C -> F, �ٸ� ������ MOVE ������ ��û��, ������ MSG_FC_MOVE

typedef struct
{
	ClientIndex_t	OtherClientIndex;
} MSG_FC_CHARACTER_DELETE_OTHER_INFO;		// F -> C,	Ŭ���̾�Ʈ���� �ٸ� ����(OTHER_INFO)�� ������ ��û��

typedef struct {
	ClientIndex_t	ClientIndex;
} MSG_FC_CHARACTER_GET_OTHER_RENDER_INFO;

typedef struct
{
	ClientIndex_t			ClientIndex;
	CHARACTER_RENDER_INFO	CharacterRenderInfo;
} MSG_FC_CHARACTER_GET_OTHER_RENDER_INFO_OK;

//typedef struct {
//	ClientIndex_t			ClientIndex;
//	USHORT					UnitState;
//} MSG_FC_CHARACTER_PUT_OTHER_EFFECT;		// F->C, �ٸ� ������ ���� ������ ����, ���� ����Ʈ � ���, check: ���ŵ�, 20040626, kelovon
//
//#define UNIT_EFFECT_NO_EFFECT		((USHORT)0)
//#define UNIT_EFFECT_HP_UP			((USHORT)1)
//#define UNIT_EFFECT_DP_UP			((USHORT)2)
//#define UNIT_EFFECT_SP_UP			((USHORT)3)
//#define UNIT_EFFECT_EP_UP			((USHORT)4)

typedef struct
{
	UINT			EffectIndex;	// Ŭ���̾�Ʈ�� ���ǵ� effect�� index
} MSG_FC_CHARACTER_SHOW_EFFECT;		// C->F, ������ �ڽ��� ����Ʈ ���� ��û

typedef struct
{
	ClientIndex_t	ClientIndex;
	UINT			EffectIndex;	// Ŭ���̾�Ʈ�� ���ǵ� effect�� index
} MSG_FC_CHARACTER_SHOW_EFFECT_OK;	// F->C, ������ ĳ���鿡�� ����

typedef struct
{
	ClientIndex_t	ClientIndex;
	BYTE			ItemPosition;				// POS_XXX
} MSG_FC_CHARACTER_GET_OTHER_PARAMFACTOR;		// C->F, �ش� ĳ������ ParamFactor ���� ��û

struct DES_PARAM_VALUE
{
	BYTE			DestParameter;				// ����Ķ����, DES_XXX
	float			ParameterValue;				// �����Ķ����
};

typedef struct
{
	ClientIndex_t	ClientIndex;
	BYTE			ItemPosition;				// POS_XXX
	INT				ItemNum;
	INT				NumOfParamValues;
	ARRAY_(DES_PARAM_VALUE);
} MSG_FC_CHARACTER_GET_OTHER_PARAMFACTOR_OK;	// F->C, �ش� ĳ������ ParamFactor ���� ��û ���

typedef struct
{
	BYTE			ItemPosition;				// POS_XXX
} MSG_FC_CHARACTER_SEND_PARAMFACTOR_IN_RANGE;	// C->F, �ڽ��� ParamFactor�� ������ �������� ��û

typedef struct
{
	ClientIndex_t	ClientIndex;				// ������ ClientIndex
} MSG_FC_CHARACTER_GET_OTHER_SKILL_INFO;		// C->F

typedef struct
{
	ClientIndex_t	ClientIndex;				// ������ ClientIndex
	INT				NumOfSkillInfos;
	ARRAY_(MEX_OTHER_SKILL_INFO);
} MSG_FC_CHARACTER_GET_OTHER_SKILL_INFO_OK;		// F->C

typedef struct
{
	int				nSendMoveCounts;			// ������ ������ Move ��Ŷ ī��Ʈ
	DWORD			dwTimeGap;					// �ð�(���� ms)
} MSG_FC_CHARACTER_SPEED_HACK_USER;

struct MSG_FC_CHARACTER_CHANGE_CHARACTER_MENT
{
	ClientIndex_t	ClientIdx;
	char			szCharacterMent1[SIZE_STRING_32];
};

struct MSG_FC_CHARACTER_GET_CASH_MONEY_COUNT_OK
{
	int				nMCash;						// MCash
	int				nGiftCard;					// ��ǰ��
};

struct MSG_FC_CHARACTER_CASH_PREMIUM_CARD_INFO
{
	INT				nCardItemNum1;
	ATUM_DATE_TIME	atumTimeUpdatedTime1;	// ������ �ð�
	ATUM_DATE_TIME	atumTimeExpireTime1;	// ���� �ð�
	float			fExpRate1;
	float			fDropRate1;
	float			fDropRareRate1;
	float			fExpRepairRate1;
};

struct MSG_FC_CHARACTER_TUTORIAL_SKIP		// 2006-10-13 by cmkwon
{
	UID32_t				CharacterUniqueNumber;
};

struct MSG_FC_CHARACTER_TUTORIAL_SKIP_OK
{
	ClientIndex_t		ClientIndex;
	UID32_t				CharacterUniqueNumber;
	MAP_CHANNEL_INDEX	mapChannelIdx;
};

struct MEX_OTHER_SKILL_INFO
{
	INT		SkillItemNum;						// Skill�� ItemNum
};

// 2005-07-26 by hblee : �����忡�� ĳ���� ��� ��ȯ.
struct MSG_FC_CHARACTER_CHANGE_CHARACTER_MODE
{
	BYTE				CharacterMode0;
	AVECTOR3			PositionAVec3;
	AVECTOR3			TargetAVec3;
};

struct MSG_FC_CHARACTER_CHANGE_CHARACTER_MODE_OK
{
	ClientIndex_t		ClientIndex;
	BYTE				CharacterMode0;
	AVECTOR3			PositionAVec3;
	AVECTOR3			TargetAVec3;
};

struct MSG_FC_CHARACTER_GET_REAL_WEAPON_INFO_OK		// 2005-12-21 by cmkwon
{
	UID64_t		ItemUID0;
	float		ShotNum0;
	float		MultiNum0;
	float		ReattackTime0;
	float		RepeatTime0;
	float		Time0;
	float		RangeAngle0;
	float		BoosterAngle0;
	float		OrbitType0;
};

struct MSG_FC_CHARACTER_GET_REAL_ENGINE_INFO_OK		// 2005-12-21 by cmkwon
{
	UID64_t		ItemUID0;
	float		AbilityMin0;
	float		AbilityMax0;
	float		SpeedPenalty0;
	float		Time0;
	float		Range0;
	float		RangeAngle0;
	float		BoosterAngle0;
};

struct MSG_FC_CHARACTER_GET_REAL_TOTAL_WEIGHT_OK		// 2005-12-21 by cmkwon
{
	UID64_t		ItemUID0;				// �Ƹ��� ItemUID
	float		Transport0;				// ���� �ɷ�
	float		TotalWeight0;			// ���� ���� �ѷ�
};

struct MSG_FC_CHARACTER_MEMORY_HACK_USER				// 2005-12-22 by cmkwon
{
	UID64_t		ItemUID0;				// ������ ItemUID
	float		ValidMoveDistance;		// ���� ��ȿ �ִ� �̵� �Ÿ� - TickGap�ð� ���� ������ �ִ� �Ÿ�
	float		CurrentMoveDistance;	// �̵��� �Ÿ� - TickGap�ð� ���� �̵��� �Ÿ�
	int			TickGap;				// ����� �ð�(����:ms, ex> 1��= 1000, 0.5��= 500)
};

struct MSG_FC_CHARACTER_UPDATE_SUBLEADER
{// 2007-02-13 by dhjin, �������� ���� ���ν���, �� ��° ������������ üũ�� �ʿ�
	BYTE			InflType;
	BYTE			SubLeaderRank;		// 2007-10-06 by dhjin, �� ��° ������������
	char			CharacterName[SIZE_MAX_CHARACTER_NAME];
};

struct MSG_FC_CHARACTER_UPDATE_SUBLEADER_OK
{// 2007-10-06 by dhjin, �������� ������ ������ Ŭ���̾�Ʈ�� ����
	BYTE			SubLeaderRank;		// 2007-10-06 by dhjin, �� ��° ������������
	char			CharacterName[SIZE_MAX_CHARACTER_NAME];
};

struct MSG_FC_CHARACTER_OBSERVER_TARGET_CHARACTERINDEX
{// 2007-03-27 by dhjin, ������ ��� ���� �ε��� 
	ClientIndex_t		TargetClientIndex;
};
typedef MSG_FC_CHARACTER_OBSERVER_TARGET_CHARACTERINDEX MSG_FC_CHARACTER_OBSERVER_START;
typedef MSG_FC_CHARACTER_OBSERVER_TARGET_CHARACTERINDEX MSG_FC_CHARACTER_OBSERVER_END;


struct MSG_FC_CHARACTER_OBSERVER_INFO
{// 2007-03-27 by dhjin, ���������� �����Ǵ� ����
	ClientIndex_t		ClientIndex;
	SHORT				HP;
	SHORT				DP;
	SHORT				SP;
	SHORT				EP;
	float				CurrentHP;
	float				CurrentDP;
	SHORT				CurrentSP;
	float				CurrentEP;
};

struct MSG_FC_CHARACTER_OBSERVER_REG
{// 2007-03-27 by dhjin, ������ ������ ��� ���� ����ϴ� ����ü
	ClientIndex_t		ClientIndex;
	SHORT				nRegNum;
};

struct MSG_FC_CHARACTER_SHOW_MAP_EFFECT		// 2007-04-20 by cmkwon
{
	UINT			EffectIndex;			// Ŭ���̾�Ʈ�� ���ǵ� effect�� index
	AVECTOR3		avec3Up;				// effect�� Up Vector, Normalize �ؾ���
	AVECTOR3		avec3Target;			// effect�� Target Vector, Normalize �ؾ���
	AVECTOR3		avec3Position;			// effect�� Positon Vector
	INT				nLifetime;				// effect�� ��ȿ�ð�(����:ms) - 0 �����̸� ������� ���� effect ��
};

struct MSG_FC_CHARACTER_SHOW_MAP_EFFECT_OK		// 2007-04-20 by cmkwon
{
	ClientIndex_t	ClientIdx;
	UINT			EffectIndex;			// Ŭ���̾�Ʈ�� ���ǵ� effect�� index
	AVECTOR3		avec3Up;				// effect�� Up Vector, Normalize �ؾ���(=����UpVector*1000f)
	AVECTOR3		avec3Target;			// effect�� Target Vector, Normalize �ؾ���(=����TargetVector*1000f)
	AVECTOR3		avec3Position;			// effect�� Positon Vector
	INT				nLifetime;				// effect�� ��ȿ�ð�(����:ms) - 0 �����̸� ������� ���� effect ��
};

struct MSG_FC_CHARACTER_PAY_WARPOINT
{// 2007-05-16 by dhjin, WarPoint�� ���޵Ǿ� ���� �Ѵ�.
	INT				WarPoint;				// 2007-05-16 by dhjin, ���޵� WarPoint
	INT				TotalWarPoint;			// 2007-05-16 by dhjin, �� WarPoint
	INT				CumulativeWarPoint;		// 2007-05-28 by dhjin, ���� WarPoint
	BOOL			UseItemFlag;			// 2010-08-27 by shcho&&jskim, WARPOINT ���� ������ ���� - ������ ���ȹ��(TRUE)���� ���ӿ��� ȹ��(FALSE)���� ����
};

struct MSG_FC_CHARACTER_WATCH_INFO
{// 2007-06-19 by dhjin, �����ڿ��� �����Ǵ� ����
	ClientIndex_t		ClientIndex;
	SHORT				HP;
	SHORT				DP;
	float				CurrentHP;
	float				CurrentDP;
};

struct MSG_FC_CHARACTER_GAMESTART_FROM_ARENA_TO_MAINSERVER
{// 2008-01-11 by dhjin, �Ʒ��� ���� - 
	ClientIndex_t		ClientIndex;
};

struct MSG_FC_CHARACTER_READY_GAMESTART_FROM_ARENA_TO_MAINSERVER
{// 2008-01-31 by dhjin, �Ʒ��� ���� - 
	ClientIndex_t		ClientIndex;
};

struct MSG_FC_CHARACTER_GET_USER_INFO
{// 2008-06-20 by dhjin, EP3 ���������ɼ� -
	UID32_t				TargetCharcterUID;
};

struct MSG_FC_CHARACTER_GET_USER_INFO_OK
{// 2008-06-20 by dhjin, EP3 ���������ɼ� -
	BYTE				PilotFace;						// ȭ�鿡 ��Ÿ���� �ι� �ɸ���
	char				CharacterName[SIZE_MAX_CHARACTER_NAME];		// ����(ĳ����) �̸�
	USHORT				UnitKind;						// ������ ����	
	UID32_t				GuildUID;
	char				GuildName[SIZE_MAX_GUILD_NAME];	// ��� �̸�
	BYTE				Level;
	MAP_CHANNEL_INDEX	MapChannelIndex;
	INT					Propensity;						// ����ġ, ����(��, ��)
	ATUM_DATE_TIME		LastStartedTime;				// ���� ���� ���� �ð�
	char				NickName[SIZE_MAX_CHARACTER_NAME];			// 2009-02-12 by cmkwon, EP3-3 ���巩ŷ�ý��� ���� - 
};

// 2012-07-12 by isshin ���۹̸����� On / Off ��� - ���� ����
struct MSG_FC_CHARACTER_GET_USER_ITEM_INFO_SECRET
{
	UID32_t				TargetCharcterUID;
};
struct MSG_FC_CHARACTER_GET_USER_ITEM_INFO_SECRET_OK
{
	BOOL				bItemInfoSecret;
};
// end 2012-07-12 by isshin ���۹̸����� On / Off ��� - ���� ����

// 2012-06-05 by jhseol, ���۹̸����� - Ŭ���û ��Ŷ �߰�
struct MSG_FC_CHARACTER_GET_USER_ITEM_INFO
{
	UID32_t				TargetCharcterUID;
};
// end 2012-06-05 by jhseol, ���۹̸����� - Ŭ���û ��Ŷ �߰�

struct MSG_FC_CHARACTER_CHANGE_INFO_OPTION_SECRET
{// 2008-06-20 by dhjin, EP3 ���������ɼ� -
	INT					SecretInfoOption;
};

struct MSG_FC_CHARACTER_CHANGE_NICKNAME		// 2009-02-12 by cmkwon, EP3-3 ���巩ŷ�ý��� ���� - 
{
	UID32_t				CharacUID;
	char				NickName[SIZE_MAX_CHARACTER_NAME];
};
typedef MSG_FC_CHARACTER_CHANGE_NICKNAME		MSG_FC_CHARACTER_CHANGE_NICKNAME_OK;	// 2009-02-12 by cmkwon, EP3-3 ���巩ŷ�ý��� ���� - 

struct MSG_FC_CHARACTER_CHANGE_START_CITY_MAPINDEX		// 2009-10-12 by cmkwon, ������ī ���� ��� ���� - 
{
	UID32_t				CharacUID;
	MapIndex_t			nStartCityMapIdx;
};
typedef MSG_FC_CHARACTER_CHANGE_START_CITY_MAPINDEX		MSG_FC_CHARACTER_CHANGE_START_CITY_MAPINDEX_OK;	// 2009-10-12 by cmkwon, ������ī ���� ��� ���� - 


struct MSG_FC_CHARACTER_CHANGE_ADDED_INVENTORY_COUNT	// 2009-11-02 by cmkwon, ĳ��(�κ�/â�� Ȯ��) ������ �߰� ���� - 
{
	UID32_t				CharacUID;
	int					nRacingPoint;
};

// 2012-10-10 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������
typedef struct
{
	INT nCount;
} MSG_FC_CHARACTER_KILLCOUNT;		// C->F

typedef struct
{
	INT nKillCount;
	INT nRestCount;
} MSG_FC_CHARACTER_RESTCOUNT;		// C->F

typedef struct
{
	INT nPartyRate;
	INT nFriendRate;
	INT nGuildRate;
} MSG_FC_CHARACTER_BONUS_EXP_RATE;		// C->F
// end 2012-10-10 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������

// 2013-08-14 by jhseol, ������ ������ - ��������Ʈ ���� ����
struct MSG_FC_CHARACTER_PAY_CONTRIBUTIONPOINT
{
	INT				AddPoint;
};
// end 2013-08-14 by jhseol, ������ ������ - ��������Ʈ ���� ����

///////////////////////////////////////////////////////////////////////////////
// FN CHARACTER
struct MSG_FN_CHARACTER_CHANGE_CHARACTER_MODE_OK
{
	ChannelIndex_t		ChannelIndex;
	ClientIndex_t		ClientIndex;
	BYTE				CharacterMode0;
};

struct MSG_FN_CHARACTER_CHANGE_INFLUENCE_TYPE
{
	ChannelIndex_t		ChannelIndex;
	ClientIndex_t		ClientIndex;
	BYTE				InfluenceType0;				// 
};

typedef struct : public MSG_FC_CHARACTER_GAMEEND_OK
{
	ChannelIndex_t		ChannelIndex;
} MSG_FN_CLIENT_GAMEEND_OK;

typedef struct : public MSG_FC_CHARACTER_CHANGE_UNITKIND
{
	ChannelIndex_t		ChannelIndex;
} MSG_FN_CHARACTER_CHANGE_UNITKIND;

typedef struct : public MSG_FC_CHARACTER_CHANGE_BODYCONDITION
{
	ChannelIndex_t		ChannelIndex;
} MSG_FN_CHARACTER_CHANGE_BODYCONDITION;

typedef struct : public MSG_FC_CHARACTER_CHANGE_HPDPSPEP
{
	ChannelIndex_t		ChannelIndex;
} MSG_FN_CHARACTER_CHANGE_HPDPSPEP;

typedef struct : public MSG_FC_CHARACTER_CHANGE_CURRENTHPDPSPEP
{
	ChannelIndex_t		ChannelIndex;
} MSG_FN_CHARACTER_CHANGE_CURRENTHPDPSPEP;

typedef struct : public MSG_FC_CHARACTER_CHANGE_CURRENTHP
{
	ChannelIndex_t		ChannelIndex;
} MSG_FN_CHARACTER_CHANGE_CURRENTHP;

typedef struct : public MSG_FC_CHARACTER_CHANGE_CURRENTSP
{
	ChannelIndex_t		ChannelIndex;
} MSG_FN_CHARACTER_CHANGE_CURRENTSP;		// check: �ʿ��Ѱ�? ö�ξ����� Ȯ�� ��!

typedef struct : public MSG_FC_CHARACTER_CHANGE_CURRENTEP
{
	ChannelIndex_t		ChannelIndex;
} MSG_FN_CHARACTER_CHANGE_CURRENTEP;		// check: �ʿ��Ѱ�? ö�ξ����� Ȯ�� ��!
typedef struct : public MSG_FC_CHARACTER_CHANGE_MAPNAME
{
	ChannelIndex_t		ChannelIndex;
} MSG_FN_CHARACTER_CHANGE_MAPNAME;
typedef struct : public MSG_FC_CHARACTER_CHANGE_PETINFO
{
	ChannelIndex_t		ChannelIndex;
} MSG_FN_CHARACTER_CHANGE_PETINFO;
typedef struct : public MSG_FC_CHARACTER_CHANGE_POSITION
{
	ChannelIndex_t		ChannelIndex;
} MSG_FN_CHARACTER_CHANGE_POSITION;

struct MSG_FN_CHARACTER_CHANGE_STEALTHSTATE
{
	ChannelIndex_t		ChannelIndex;
	ClientIndex_t		ClientIndex;
	BOOL				bStealthState2;
};

struct MSG_FN_CHARACTER_CHANGE_INVISIBLE
{
	ChannelIndex_t		ChannelIndex;
	ClientIndex_t		ClientIndex;
	BOOL				bInvisible;
};

///////////////////////////////////////////////////////////////////////////////
// FC_MOVE ( Field server <-> Client)
typedef struct
{
	ClientIndex_t	ClientIndex;
	USHORT			TimeGap;
	BYTE			DistanceGap;		// Client�� ���� ������ ������
	AVECTOR3		PositionVector;
	AVECTOR3		TargetVector;
	AVECTOR3		UpVector;
} MSG_FC_MOVE;

struct MSG_FC_MOVE_BIT_FLAG					// 2007-03-29 by cmkwon
{
	BYTE			CharacterMode0 : 1;		// 
	BYTE			Invisible0 : 1;			// �κ����� ��ų ��� ����
	BYTE			ChargingSkill : 1;		// 2007-04-02 by cmkwon, A-Gear ��¡ ��ų ��� ����
	BYTE			HyperShot : 1;			// A-Gear �����ۼ� ��ų ��� ����
	// 2012-12-06 by jhseol, ��ġ���� ���� ĳ���� �߽����� ����
	bool			bSearchEye_1;			// �Ϲ� ��ġ����
	bool			bSearchEye_2;			// ��ȭ ��ġ����
	bool			bUsingBarialSkill;		// 2013-01-29 by jhseol, ������ ��ų ����Ʈ ����
	bool			bUsingInvicibleSkill;	// 2013-02-06 by jhseol, M��� ������ų �̺�Ʈ ����
	MSG_FC_MOVE_BIT_FLAG()
	{
		bSearchEye_1 = FALSE;				// �ʱⰪ �̻������ ���� (FALSE : �̻��, TRUE : ���)
		bSearchEye_2 = FALSE;				// �ʱⰪ �̻������ ���� (FALSE : �̻��, TRUE : ���)
		bUsingBarialSkill = FALSE;			// 2013-01-29 by jhseol, ������ ��ų ����Ʈ ����
		bUsingInvicibleSkill = FALSE;		// 2013-02-06 by jhseol, M��� ������ų �̺�Ʈ ����
	}
	// end 2012-12-06 by jhseol, ��ġ���� ���� ĳ���� �߽����� ����
};

// 2012-12-06 by jhseol, ��ġ���� ���� ĳ���� �߽����� ����
struct UsingItemBitFlag
{
	bool			bSearchEye_1;			// �Ϲ� ��ġ����
	bool			bSearchEye_2;			// ��ȭ ��ġ����
	bool			bUsingBarialSkill;		// 2013-01-29 by jhseol, ������ ��ų ����Ʈ ����
	bool			bUsingInvicibleSkill;	// 2013-02-06 by jhseol, M��� ������ų �̺�Ʈ ����
	UsingItemBitFlag()
	{
		bSearchEye_1 = FALSE;				// �ʱⰪ �̻������ ���� (FALSE : �̻��, TRUE : ���)
		bSearchEye_2 = FALSE;				// �ʱⰪ �̻������ ���� (FALSE : �̻��, TRUE : ���)
		bUsingBarialSkill = FALSE;			// 2013-01-29 by jhseol, ������ ��ų ����Ʈ ����
		bUsingInvicibleSkill = FALSE;		// 2013-02-06 by jhseol, M��� ������ų �̺�Ʈ ����
	}
};
// end 2012-12-06 by jhseol, ��ġ���� ���� ĳ���� �߽����� ����

typedef struct
{
	ClientIndex_t	ClientIndex;
	// 2007-03-29 by cmkwon, �Ʒ��� ���� ��Ʈ�÷��� ������ �ϳ� �߰���
	//	BYTE			CharacterMode0;		// 2005-07-29 by cmkwon
	MSG_FC_MOVE_BIT_FLAG moveBitFlag;	// 2007-03-29 by cmkwon
	AVECTOR3		PositionVector;
	AVECTOR3		TargetVector;
	AVECTOR3		UpVector;
} MSG_FC_MOVE_OK;

typedef struct
{
	UINT			ItemNum;						// ���� ������ ����
	ClientIndex_t	MonsterIndex;					// ���� ������ �ε���
	INT				WeaponIndex;					// ���� ���� �ε���(���Ϳ� ���� ������)
	AVECTOR3		PositionVector;
	AVECTOR3		TargetVector;
} MSG_FC_MISSILE_MOVE_OK;

typedef struct
{
	ClientIndex_t	AttackIndex;
	ClientIndex_t	TargetIndex;
} MSG_FC_MOVE_LOCKON;

typedef struct
{
	char			AttackCharacterName[SIZE_MAX_CHARACTER_NAME];
	ClientIndex_t	AttackIndex;		// 2005-10-11 by cmkwon
	ClientIndex_t	TargetIndex;
} MSG_FC_MOVE_LOCKON_OK;

typedef struct
{
	ClientIndex_t	AttackIndex;
	ClientIndex_t	TargetIndex;
} MSG_FC_MOVE_UNLOCKON;

typedef struct
{
	char			AttackCharacterName[SIZE_MAX_CHARACTER_NAME];
	ClientIndex_t	AttackIndex;		// 2005-10-12 by cmkwon
	ClientIndex_t	TargetIndex;
} MSG_FC_MOVE_UNLOCKON_OK;

typedef struct
{
	ClientIndex_t	ClientIndex;
	AVECTOR3		Position;
} MSG_FC_MOVE_LANDING;

typedef struct
{
	AVECTOR3	Position;
} MSG_FC_MOVE_LANDING_OK;

typedef struct
{
	AVECTOR3	Position;
} MSG_FC_MOVE_LANDING_DONE;		// C->F, ���� �ϷḦ �˸�

typedef struct
{
	ClientIndex_t		ClientIndex;
	AVECTOR3	Position;
} MSG_FC_MOVE_TAKEOFF;

typedef struct
{
	AVECTOR3	Position;
} MSG_FC_MOVE_TAKEOFF_OK;

typedef MSG_UNIT_INDEX		MSG_FC_MOVE_TARGET;

typedef struct
{
	D3DXVECTOR3		WeaponVel;
	D3DXVECTOR3		PetLeftVel;
	D3DXVECTOR3		PetRightVel;
} MSG_FC_MOVE_WEAPON_VEL;		// C->F, ������ ������ ������ ����

typedef struct
{
	ClientIndex_t	ClientIndex;
	D3DXVECTOR3		WeaponVel;
	D3DXVECTOR3		PetLeftVel;
	D3DXVECTOR3		PetRightVel;
} MSG_FC_MOVE_WEAPON_VEL_OK;	// F->C_in_range, ������ ������ ������ ����

struct MSG_FC_MOVE_ROLLING
{
	AVECTOR3		PositionAVec3;
	AVECTOR3		TargetAVec3;
	AVECTOR3		UpAVec3;
	BYTE			byLeftDirectionFlag;		// ���� �Ѹ� �÷���
};
struct MSG_FC_MOVE_ROLLING_OK
{
	ClientIndex_t	ClientIndex;
	AVECTOR3		PositionAVec3;
	AVECTOR3		TargetAVec3;
	AVECTOR3		UpAVec3;
	BYTE			byLeftDirectionFlag;		// ���� �Ѹ� �÷���
};

// 2008-04-03 by cmkwon, �ٽ��� ���� ���� �ý��� ���� - ������� �ʴ� ����ü, �Ʒ��� ���� �����ؼ� ���
// // 2008-03-24 by cmkwon, �ٽ��� 2.0 ���� - �������� ����� üũ �ؾ��ϴ� ������ �־ AntiCpSvrFunc.h ������ ���Ǹ� �״�� ����ϰ� Ŭ���̾�Ʈ���� ������� �����ϱ�
// // #define SIZE_SIZEOF_REQMSG			160				// Request Message�� ���� ������ ũ��
// // #define SIZE_SIZEOF_ACKMSG			72				// Ack Message�� ���� ������ ũ��, // 2007-04-02 by cmkwon, ����(56->72)
// // #define SIZE_SIZEOF_GUIDREQMSG		20				// GUID Request Message�� ���� ������ ũ��
// // #define SIZE_SIZEOF_GUIDACKMSG		20				// GUID Ack Message�� ���� ������ ũ��
// struct MSG_FC_MOVE_HACKSHIELD_GuidReqMsg		// 2006-06-05 by cmkwon
// {
// 	// 2008-03-24 by cmkwon, �ٽ��� 2.0 ���� - AntiCpSvrFunc.h ������ ���Ǹ� �״�� ����ϰ� Ŭ���̾�Ʈ���� ������� �����ϱ�
// 	//unsigned char	pbyGuidReqMsg[SIZE_SIZEOF_GUIDREQMSG];
// 	unsigned char	pbyGuidReqMsg[SIZEOF_GUIDREQMSG];
// };
// struct MSG_FC_MOVE_HACKSHIELD_GuidAckMsg		// 2006-06-05 by cmkwon
// {
// 	// 2008-03-24 by cmkwon, �ٽ��� 2.0 ���� - AntiCpSvrFunc.h ������ ���Ǹ� �״�� ����ϰ� Ŭ���̾�Ʈ���� ������� �����ϱ�
// 	//unsigned char	pbyGuidAckMsg[SIZE_SIZEOF_GUIDACKMSG];
// 	unsigned char	pbyGuidAckMsg[SIZEOF_GUIDACKMSG];
// };
// struct MSG_FC_MOVE_HACKSHIELD_CRCReqMsg			// 2006-06-05 by cmkwon
// {
// 	// 2008-03-24 by cmkwon, �ٽ��� 2.0 ���� - AntiCpSvrFunc.h ������ ���Ǹ� �״�� ����ϰ� Ŭ���̾�Ʈ���� ������� �����ϱ�
// 	//unsigned char	pbyReqMsg[SIZE_SIZEOF_REQMSG];
// 	unsigned char	pbyReqMsg[SIZEOF_REQMSG];
// };
// struct MSG_FC_MOVE_HACKSHIELD_CRCAckMsg			// 2006-06-05 by cmkwon
// {
// 	// 2008-03-24 by cmkwon, �ٽ��� 2.0 ���� - AntiCpSvrFunc.h ������ ���Ǹ� �״�� ����ϰ� Ŭ���̾�Ʈ���� ������� �����ϱ�
// 	//unsigned char	pbyAckMsg[SIZE_SIZEOF_ACKMSG];	
// 	unsigned char	pbyAckMsg[SIZEOF_ACKMSG];	
// };
struct MSG_FC_MOVE_HACKSHIELD_CRCReqMsg			// 2008-04-03 by cmkwon, �ٽ��� ���� ���� �ý��� ���� - 
{
	_AHNHS_TRANS_BUFFER		stRequestBuf;
};
struct MSG_FC_MOVE_HACKSHIELD_CRCAckMsg			// 2008-04-03 by cmkwon, �ٽ��� ���� ���� �ý��� ���� - 
{
	_AHNHS_TRANS_BUFFER		stResponseBuf;
};

struct MSG_FC_MOVE_HACKSHIELD_HACKING_CLIENT	// 2006-06-05 by cmkwon
{
	long			lHackingClinetCode;			// ERR_AHNHS_XXXXXX	
	char			szErrString[SIZE_STRING_128];			// 2006-10-20 by cmkwon, �߰���(��ŷ ���α׷���)
};


struct MSG_FC_MOVE_XIGNCODE_REQ_SCAN_INIT	// 2008-11-28 by cmkwon, �븸 Netpower_Tpe XignCode(���Ӱ���) ���� - 
{
	BYTE	byCurDataIndex;		// 0,1,2,3,...
	BYTE	byDataCount;		// Data Count
	BYTE	byCheckData[MAX_PACKET_SIZE_FOR_XIGNCODE];
};
struct MSG_FC_MOVE_XIGNCODE_REQ_SCAN_INIT_OK	// 2008-11-28 by cmkwon, �븸 Netpower_Tpe XignCode(���Ӱ���) ���� - 
{
	BYTE	byResultData[MAX_PACKET_SIZE_FOR_XIGNCODE];
};
struct MSG_FC_MOVE_XIGNCODE_REQ_SCAN_CHECK	// 2008-11-28 by cmkwon, �븸 Netpower_Tpe XignCode(���Ӱ���) ���� - 
{
	BYTE	byCurDataIndex;		// 0,1,2,3,...
	BYTE	byDataCount;		// Data Count
	BYTE	byCheckData[MAX_PACKET_SIZE_FOR_XIGNCODE];
};
struct MSG_FC_MOVE_XIGNCODE_REQ_SCAN_CHECK_OK	// 2008-11-28 by cmkwon, �븸 Netpower_Tpe XignCode(���Ӱ���) ���� - 
{
	BYTE	byResultData[MAX_PACKET_SIZE_FOR_XIGNCODE];
};

struct MSG_FC_MOVE_NPROTECT_REQ_AUTH_DATA		// 2009-03-09 by cmkwon, �Ϻ� Arario nProtect�� CS���� �����ϱ� - 
{
	BYTE 	reqAuthData[MAX_PACKET_SIZE_FOR_NPROTECT];
};
struct MSG_FC_MOVE_NPROTECT_REQ_AUTH_DATA_OK	// 2009-03-09 by cmkwon, �Ϻ� Arario nProtect�� CS���� �����ϱ� - 
{
	BYTE	resAuthData[MAX_PACKET_SIZE_FOR_NPROTECT];
};
struct MSG_FC_MOVE_NPROTECT_NEW_REQ_AUTH_DATA		// 2015-01-07 by jwLee �������� nProtector ����
{
	BYTE 	reqAuthData[MAX_PACKET_SIZE_FOR_NPROTECT_NEW];
	UINT32	datasize;
};
struct MSG_FC_MOVE_NPROTECT_NEW_REQ_AUTH_DATA_OK	// 2015-01-07 by jwLee �������� nProtector ����
{
	BYTE	resAuthData[MAX_PACKET_SIZE_FOR_NPROTECT_NEW];
	UINT32	datasize;
};
struct MSG_FC_MOVE_XTRAP_REQ_STEP			// 2009-10-06 by cmkwon, ��Ʈ�� ���� ���� X-TRAP���� ���� - 
{
	BYTE	reqCSStepData[XTRAP_SIZE_MAX_SESSIONBUF];
};

struct MSG_FC_MOVE_XTRAP_REQ_STEP_OK		// 2009-10-06 by cmkwon, ��Ʈ�� ���� ���� X-TRAP���� ���� - 
{
	BYTE	resCSStepData[XTRAP_SIZE_MAX_SESSIONBUF];
};

struct MSG_FC_MOVE_APEX_REQ_APEXDATA		// 2009-11-04 by cmkwon, �±� ���Ӱ��� Apex�� ���� - 
{
	char	cMsgType;
	char	szApexData[SECURITY_APEX_MaxPacketLen];
	int		nApexDataLen;
};
typedef MSG_FC_MOVE_APEX_REQ_APEXDATA		MSG_FC_MOVE_APEX_REQ_APEXDATA_OK;		// 2009-11-04 by cmkwon, �±� ���Ӱ��� Apex�� ���� - 


///////////////////////////////////////////////////////////////////////////////
// FN_MOVE (Field server <-> NPC server)


///////////////////////////////////////////////////////////////////////////////
// FC_BATTLE (Field server <-> Client)
struct MEX_TARGET_INFO
{
	AVECTOR3		TargetPosition;			// ���� Ŭ���̾�Ʈ�� ȭ�鿡���� Ÿ�� ������
	ClientIndex_t	TargetIndex;			// ���� ��� ClientIndex or MonterIndex, 0�̸� ItemFieldIndex�� ��ȿ
	UINT			TargetItemFieldIndex;	// ���� ��� ������ �������̸� TargetIndex ��ȿ, �ƴϸ� TargetIndex�� 0
	USHORT			MultiTargetIndex;		// 2011-03-21 by hskim, ���Ǵ�Ƽ 3�� - ���� ��Ƽ Ÿ���� ��� �߰�

public:
	void SetNullTarget()
	{
		TargetIndex = 0;
		TargetItemFieldIndex = 0;
		MultiTargetIndex = 0;				// 2011-03-21 by hskim, ���Ǵ�Ƽ 3�� - ���� ��Ƽ Ÿ���� ��� �߰�
	}
};

typedef struct
{
	MEX_TARGET_INFO	TargetInfo;
	AVECTOR3		FirePosition;		// ������ �߻� ��ġ
	BYTE			AttackType;			// ���� Ÿ��, ATT_TYPE_XXX, see below
	UINT			SkillNum;			// ��ų ��� �� ���
} MSG_FC_BATTLE_ATTACK;					// C->F

// ATT_TYPE_XXX, 1~100: 1�� ����, 101~200: 2�� ����
#define	ATT_TYPE_NONE			((BYTE)0)	// Attack Type ����
// 1�� ����
#define	ATT_TYPE_GENERAL_PRI		((BYTE)1)	// 1�� ���� �Ϲ� ����
#define	ATT_TYPE_GROUND_BOMBING_PRI	((BYTE)2)	// 1�� ���� ���� ���
#define	ATT_TYPE_AIR_BOMBING_PRI	((BYTE)3)	// 1�� ���� ���� ���
#define	ATT_TYPE_SEIGE_PRI			((BYTE)4)	// 1�� ���� ���
#define	ATT_TYPE_SPLASH_PRI			((BYTE)5)	// 1�� Splash ���� ���
#define	ATT_TYPE_END_PRI			((BYTE)100)	// 1�� ���� ���� ��, ������ �� ����
// 2�� ����
#define ATT_TYPE_GENERAL_SEC		((BYTE)101)	// 2�� ���� �Ϲ� ����
#define ATT_TYPE_GROUND_BOMBING_SEC	((BYTE)102)	// 2�� ���� ���� ���
#define ATT_TYPE_AIR_BOMBING_SEC	((BYTE)103)	// 2�� ���� ���� ���
#define ATT_TYPE_SIEGE_SEC			((BYTE)104)	// 2�� ���� ���
#define	ATT_TYPE_END_SEC			((BYTE)200)	// 2�� ���� ���� ��, ������ �� ����

// 2010-06-15 by shcho&hslee ��ý��� - �� ���� ó��
#define ATT_TYPE_PET_ATK			ATT_TYPE_PET_GENERAL
#define ATT_TYPE_PET_GENERAL		((BYTE)201) // �� ����(�Ϲ� ����)
#define ATT_TYPE_PET_END			((BYTE)300)	// �� ���� ��

#define IS_PET_ATT_TPYE(_ATT_TYPE)			(IS_IN_RANGE(ATT_TYPE_PET_START, _ATT_TYPE, ATT_TYPE_PET_END))
// END 2010-06-15 by shcho&hslee ��ý��� - �� ���� ó��
#define IS_PRIMARY_ATT_TYPE(_ATT_TYPE)		(IS_IN_RANGE(ATT_TYPE_GENERAL_PRI, _ATT_TYPE, ATT_TYPE_END_PRI))
#define IS_SECONDARY_ATT_TYPE(_ATT_TYPE)	(IS_IN_RANGE(ATT_TYPE_GENERAL_SEC, _ATT_TYPE, ATT_TYPE_END_SEC))

///////////////////////////////////////////////////////////////////////////////
// 2007-06-04 by cmkwon
#if _RAT_ANTI_CHEAT
struct SATTACK_PARAMETER
{
	UID16_t			WeaponIndex;					// ź�� ������ȣ - 2�� ���⸸ ó����
	DWORD			dwShotTick;						// 2007-06-08 by cmkwon, �߻� Tick
	ITEM* pWeaponItemInfo;				// ���� ���� ������ ����
	float			fAttackProbability;				// ���� Ȯ��
	float			fPierceAttackProbability;		// ���� �Ǿ��
	float			fAttack;						// ���ݷ�
	float			fMaxAttack;						// �ִ���ݷ�	
	ClientIndex_t	TargetIndex;					// 2010-04-05 by cmkwon, ����2�� M2M 2�� ���� ���� ó�� - 
	BYTE			AttackType;						// 2010-04-05 by cmkwon, ����2�� M2M 2�� ���� ���� ó�� - 
	USHORT			MultiTargetIndex;				// 2011-04-04 by hskim, ���Ǵ�Ƽ 3�� - ���� ��Ƽ Ÿ���� ��� �߰
};
typedef mt_vector<SATTACK_PARAMETER>			mtvectSATTACK_PARAMETER;		// 2007-06-07 by cmkwon
typedef vector<SATTACK_PARAMETER>				vectSATTACK_PARAMETER;			// 2010-04-05 by cmkwon, ����2�� M2M 2�� ���� ���� ó�� - 

#else
struct SATTACK_PARAMETER
{
	UID16_t			WeaponIndex;					// ź�� ������ȣ - 2�� ���⸸ ó����
	DWORD			dwShotTick;						// 2007-06-08 by cmkwon, �߻� Tick
	ITEM* pWeaponItemInfo;				// ���� ���� ������ ����
	float			fAttackProbability;				// ���� Ȯ��
	float			fPierceAttackProbability;		// ���� �Ǿ��
	float			fAttack;						// ���ݷ�
	float			fMaxAttack;						// �ִ���ݷ�	
	ClientIndex_t	TargetIndex;					// 2010-04-05 by cmkwon, ����2�� M2M 2�� ���� ���� ó�� - 
	BYTE			AttackType;						// 2010-04-05 by cmkwon, ����2�� M2M 2�� ���� ���� ó�� - 
	USHORT			MultiTargetIndex;				// 2011-04-04 by hskim, ���Ǵ�Ƽ 3�� - ���� ��Ƽ Ÿ���� ��� �߰
};
typedef mt_vector<SATTACK_PARAMETER>			mtvectSATTACK_PARAMETER;		// 2007-06-07 by cmkwon
typedef vector<SATTACK_PARAMETER>				vectSATTACK_PARAMETER;			// 2010-04-05 by cmkwon, ����2�� M2M 2�� ���� ���� ó�� - 
#endif

#if _RAT_ANTI_CHEAT
typedef struct
{
	ClientIndex_t	AttackIndex;
	MEX_TARGET_INFO	TargetInfo;
	AVECTOR3		FirePosition;		// ������ �߻� ��ġ
	BYTE			AttackType;			// ���� Ÿ��, ATT_TYPE_XXX
	UID16_t			WeaponIndex;		// Ŭ���̾�Ʈ���� �߻�� �Ѿ��� �ε���, �������� ����, CUID16Generator ���
	UINT			ItemNum;			// ������ ItemNum
	USHORT			RemainedBulletFuel;	// ���� �Ѿ�(Ȥ�� Fuel)�� ��
	UINT			SkillNum;			// ��ų ��� �� ���
	ClientIndex_t	DelegateClientIdx;	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� �� 2�� ���� ���� ó�� �� ���� Ŭ���̾�Ʈ

	float			ServerExplosionRange_Secondary;
	float			ServerWarheadSpeed_Secondary;
} MSG_FC_BATTLE_ATTACK_OK;				// F->C_in_range
#else
typedef struct
{
	ClientIndex_t	AttackIndex;
	MEX_TARGET_INFO	TargetInfo;
	AVECTOR3		FirePosition;		// ������ �߻� ��ġ
	BYTE			AttackType;			// ���� Ÿ��, ATT_TYPE_XXX
	UID16_t			WeaponIndex;		// Ŭ���̾�Ʈ���� �߻�� �Ѿ��� �ε���, �������� ����, CUID16Generator ���
	UINT			ItemNum;			// ������ ItemNum
	USHORT			RemainedBulletFuel;	// ���� �Ѿ�(Ȥ�� Fuel)�� ��
	UINT			SkillNum;			// ��ų ��� �� ���
	ClientIndex_t	DelegateClientIdx;	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� �� 2�� ���� ���� ó�� �� ���� Ŭ���̾�Ʈ
} MSG_FC_BATTLE_ATTACK_OK;				// F->C_in_range
#endif

typedef struct
{
	ClientIndex_t	AttackIndex;
	MEX_TARGET_INFO	TargetInfo;
	UINT			ItemNum;			// ������ ItemNum, ������ 2�� ���ݿ��� ����
	UID16_t			WeaponIndex;		// Ŭ���̾�Ʈ���� �߻�� �Ѿ��� �ε���, �������� ����, CUID16Generator ���
	BYTE			AttackType;			// ���� Ÿ��, ATT_TYPE_XXX
} MSG_FC_BATTLE_ATTACK_FIND;			// C->F

typedef struct
{
	ClientIndex_t	AttackIndex;
	ClientIndex_t	TargetIndex;			// ���� ��� ClientIndex or MonterIndex, 0�̸� ItemFieldIndex�� ��ȿ
	UINT			TargetItemFieldIndex;	// ���� ��� ������ �������̸� TargetIndex ��ȿ, �ƴϸ� TargetIndex�� 0
	UID16_t			WeaponIndex;		// Ŭ���̾�Ʈ���� �߻�� �Ѿ��� �ε���, �������� ����, CUID16Generator ���
	BYTE			AttackType;			// ���� Ÿ��, ATT_TYPE_XXX
} MSG_FC_BATTLE_ATTACK_FIND_OK;			// F->C_in_range

// ���η� ó��
typedef struct
{
	BYTE			NumOfMines;
	ClientIndex_t	TargetIndex;		// Mine�� �� Target�� ������ �����ȴ�(������ Ŭ���̾�Ʈ�� ���޸� �ϸ��)
	ARRAY_(AVECTOR3);					// MINE�� ������ ��ġ
} MSG_FC_BATTLE_DROP_MINE;				// C->F

typedef struct
{
	ClientIndex_t	AttackIndex;		// MINE ������
	ClientIndex_t	TargetIndex;		// Mine�� �� Target�� ������ �����ȴ�(������ Ŭ���̾�Ʈ�� ���޸� �ϸ��)
	UINT			ItemFieldIndex;		// ���� ������ ������ �ӽ÷� �����ϴ� ���� ��ȣ
	INT				ItemNum;			// Ŭ���̾�Ʈ�� �������� ������ �����ֱ� ���� ����
	AVECTOR3		DropPosition;		// MINE�� ������ ��ġ
	USHORT			RemainedBulletFuel;	// ���� �Ѿ�(Ȥ�� Fuel)�� ��
} MSG_FC_BATTLE_DROP_MINE_OK;			// F->C_in_range, ������ �����ֱ�

typedef struct
{
	UINT			ItemFieldIndex;		// ������ �ӽ÷� �����ϴ� ���� ��ȣ
	MEX_TARGET_INFO	TargetInfo;			// �ǰ�����
} MSG_FC_BATTLE_MINE_ATTACK;			// C->F

typedef struct
{
	UINT			ItemFieldIndex;		// ������ �ӽ÷� �����ϴ� ���� ��ȣ
	MEX_TARGET_INFO	TargetInfo;			// �ǰ�����
} MSG_FC_BATTLE_MINE_ATTACK_OK;			// F->C_in_range

typedef struct
{
	UINT			ItemFieldIndex;		// ������ �ӽ÷� �����ϴ� ���� ��ȣ
	MEX_TARGET_INFO	TargetInfo;			// �ǰ�����
} MSG_FC_BATTLE_MINE_ATTACK_FIND;		// C->F

typedef struct
{
	UINT			ItemFieldIndex;		// ������ �ӽ÷� �����ϴ� ���� ��ȣ
	MEX_TARGET_INFO	TargetInfo;			// �ǰ�����
} MSG_FC_BATTLE_MINE_ATTACK_FIND_OK;	// F->C_in_range

// 2007-08-07 by cmkwon, 1��/2�� ���� �Ѿ� ���� ������ ���� - �Ʒ��� ���� ������
//typedef struct  {
//	USHORT			BulletCount;		// ������ reload�� �Ѿ��� ���� ����
//} MSG_FC_BATTLE_PRI_BULLET_RELOADED;
//
//typedef struct  {
//	USHORT			BulletCount;		// ������ reload�� �Ѿ��� ���� ����
//} MSG_FC_BATTLE_SEC_BULLET_RELOADED;

// 2007-08-07 by cmkwon, 1��/2�� ���� �Ѿ� ���� ������ ���� - BULLET_RECHARGE_TYPE_XXX ���� �߰�
#define BULLET_RECHARGE_TYPE_NORMAL			((BYTE)0)
#define BULLET_RECHARGE_TYPE_REPAIR_SHOP	((BYTE)1)
#define BULLET_RECHARGE_TYPE_BULLET_ITEM	((BYTE)2)
#define BULLET_RECHARGE_TYPE_ADMIN_COMMAND	((BYTE)3)
struct  MSG_FC_BATTLE_PRI_BULLET_RELOADED
{
	USHORT			BulletCount;		// ������ reload�� �Ѿ��� ���� ����
	USHORT			RechargeCount;		// 2007-08-07 by cmkwon, 1��/2�� ���� �Ѿ� ���� ������ ���� - �߰��� �ʵ�
	BYTE			RechargeType;		// 2007-08-07 by cmkwon, 1��/2�� ���� �Ѿ� ���� ������ ���� - �߰��� �ʵ�(BULLET_RECHARGE_TYPE_XXX)
};
typedef MSG_FC_BATTLE_PRI_BULLET_RELOADED		 MSG_FC_BATTLE_SEC_BULLET_RELOADED;

// Kind of Damages: ����Ʈ�� ǥ���ϱ� ���� ����Ѵ�. check: �Ʒ��з��� �����ǵǾ�� �Ѵ�.
// DAMAGEKIND_XXX
#define DAMAGEKIND_NO_DAMAGE	(BYTE)0x00
#define DAMAGEKIND_NORMAL		(BYTE)0x01	// 0 < DAMAGE < 100
#define DAMAGEKIND_CRITICAL		(BYTE)0x02	// �ǰ������� ���� ����
#define DAMAGEKIND_ADD_DAMAGE	(BYTE)0x03	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���밪 �߰� Ÿ��ġ ������
#define DAMAGEKIND_REFLECTION	(BYTE)0x04	// 2009-09-09 ~ 2010-02-10 by dhjin, ���Ǵ�Ƽ - ������ �ݻ�
#define DAMAGEKIND_PET			(BYTE)0x05	// 2010-11-01 by jskim, �� ������ View ����

typedef struct
{
	ClientIndex_t	TargetIndex;			// �ش� �������� ������ ClientIndex
	UINT			TargetItemFieldIndex;
} MSG_FC_BATTLE_ATTACK_EXPLODE_ITEM;		// ��ü�� �ް� �ִ� ������(DUMMY �� ��)�� ������ ���

typedef struct
{
	ClientIndex_t	TargetIndex;			// �ش� �������� ������ ClientIndex
	UINT			TargetItemFieldIndex;
} MSG_FC_BATTLE_ATTACK_HIDE_ITEM;			// ��ü�� �ް� �ִ� ������(DUMMY �� ��)�� �׳� ������� ���(Time Out ��� ����...)

typedef struct
{
	ClientIndex_t	TargetIndex;			// �ش� �������� ������ ClientIndex
	BYTE			ItemKind;
	UINT			TargetItemFieldIndex;
} MSG_FC_BATTLE_ATTACK_EXPLODE_ITEM_W_KIND;	// With KIND, ��ü�� �ް� �ִ� ������(FIXER �� ��)�� ������ ���

typedef struct
{
	ClientIndex_t	TargetIndex;			// �ش� �������� ������ ClientIndex
	BYTE			ItemKind;
	UINT			TargetItemFieldIndex;
} MSG_FC_BATTLE_ATTACK_HIDE_ITEM_W_KIND;	// With KIND, ��ü�� �ް� �ִ� ������(FIXER �� ��)�� �׳� ������� ���(Time Out ��� ����...)

// ����� ó��
typedef struct
{
	UID64_t			ItemUniqueNumber;
	ClientIndex_t	AttackClientIndex;
	ClientIndex_t	TargetClientIndex;
	AVECTOR3		DropPosition;
} MSG_FC_BATTLE_DROP_BUNDLE;

typedef struct
{
	UID64_t			ItemUniqueNumber;
	ClientIndex_t	AttackClientIndex;
	ClientIndex_t	TargetClientIndex;
	INT				ItemNum;			// Ŭ���̾�Ʈ�� �������� ������ �����ֱ� ���� ����
	AVECTOR3		DropPosition;
	USHORT			NumOfBullet;		// �߻��� źü�� ����
} MSG_FC_BATTLE_DROP_BUNDLE_OK;

typedef struct
{
	UID64_t			BundleItemUniqueNumber;	// ������ ItemUniqueNumber
	AVECTOR3		AttackPosition;
	ClientIndex_t	TargetIndex;
	AVECTOR3		TargetPosition;
} MSG_FC_BATTLE_BUNDLE_ATTACK;

typedef struct
{
	INT				ItemNum;				// bundle�� ��ũ ������(�̻��� ��)�� ItemNum
	ClientIndex_t	AttackIndex;
	AVECTOR3		AttackPosition;
	ClientIndex_t	TargetIndex;
	AVECTOR3		TargetPosition;
} MSG_FC_BATTLE_BUNDLE_ATTACK_RESULT;

typedef struct
{
	UID64_t			BundleItemUniqueNumber;	// ������ ItemUniqueNumber
	AVECTOR3		AttackPosition;
	ClientIndex_t	TargetIndex;
	UINT			TargetItemFieldIndex;	// ��� ������
	AVECTOR3		TargetPosition;
} MSG_FC_BATTLE_BUNDLE_ATTACK_ITEM;

typedef struct
{
	INT				ItemNum;				// bundle�� ��ũ ������(�̻��� ��)�� ItemNum
	ClientIndex_t	AttackIndex;
	AVECTOR3		AttackPosition;
	ClientIndex_t	TargetIndex;
	UINT			TargetItemFieldIndex;	// ��� ������
	AVECTOR3		TargetPosition;
} MSG_FC_BATTLE_BUNDLE_ATTACK_ITEM_RESULT;

// check: �ʿ��ϸ� �츲(���� NO BODY��), kelovon, 20030917
//typedef struct
//{
//} MSG_FC_BATTLE_TOGGLE_SHIELD;

typedef struct
{
	ClientIndex_t	AttackIndex;		// shield�� ������ ĳ����
	BYTE			IsOn;				// 0(FALSE): off, 1(TRUE): on
	INT				ItemNum;
} MSG_FC_BATTLE_TOGGLE_SHIELD_RESULT;	// F->C, SHIELD�� �������̸� MSG_FC_CHARACTER_GET_OTHER_INFO_OK���� �� �� MSG�� �ٿ�������.

// check: �ʿ��ϸ� �츲(���� NO BODY��), kelovon, 20040517
//typedef struct
//{
//} MSG_FC_BATTLE_TOGGLE_DECOY;

typedef struct
{
	ClientIndex_t	AttackIndex;	// decoy�� ������ ĳ����
	BYTE			IsOn;			// 0(FALSE): off, 1(TRUE): on
	INT				ItemNum;
} MSG_FC_BATTLE_TOGGLE_DECOY_OK;	// F->C, DECOY�� �������̸� MSG_FC_CHARACTER_GET_OTHER_INFO_OK���� �� �� MSG�� �ٿ�������.

typedef struct
{
	ClientIndex_t	TargetIndex;		// shield�� ������Ű�� �ִ� ĳ����
	AVECTOR3		CollisionPosition;	// �浹 ��ġ
} MSG_FC_BATTLE_SHIELD_DAMAGE;

// ����(DUMMY)��
typedef struct
{
	UID64_t		ItemUniqueNumber;
	//	BYTE		NumOfDummies;			// check: �����. 20030930, kelovon with jinking
	//	ARRAY_(AVECTOR3);					// DUMMY�� ��ġ(��ü�� ���� ��� ��ǥ), check: �����. 20030930, kelovon with jinking
} MSG_FC_BATTLE_DROP_DUMMY;				// ���̴� �ѹ��� �� ���.

// 2007-06-21 by cmkwon, ü�� �ϳ��� �޽����� ��� ���� - �Ʒ��� ���� ����ü ����
//typedef struct
//{
//	ClientIndex_t	AttackIndex;		// DUMMY�� �ߵ��� ��ü
//	UINT			ItemFieldIndex;		// ���� ������ ������ �ӽ÷� �����ϴ� DUMMY ��ȣ
//	INT				ItemNum;			// Ŭ���̾�Ʈ�� �������� ������ �����ֱ� ���� ����
////	AVECTOR3		DropPosition;		// ��ü�� ���� ��� ��ǥ, check: �����. 20030930, kelovon with jinking
//} MSG_FC_BATTLE_DROP_DUMMY_OK;			// ������ �����ֱ�,  DUMMY�� �������̸� MSG_FC_CHARACTER_GET_OTHER_INFO_OK���� �� �� MSG�� �ٿ�������.
struct MSG_FC_BATTLE_DROP_DUMMY_OK		// 2007-06-21 by cmkwon, ü�� �ϳ��� �޽����� ��� ���� -
{
	ClientIndex_t	AttackIndex;		// DUMMY�� �ߵ��� ��ü
	INT				ItemNum;			// Ŭ���̾�Ʈ�� �������� ������ �����ֱ� ���� ����
	INT				DummyCounts;		// 2007-06-21 by cmkwon, ü�� �ϳ��� �޽����� ��� ���� -
	_ARRAY(UINT ItemFieldIndex);		// 2007-06-21 by cmkwon, ü�� �ϳ��� �޽����� ��� ���� - DummyCounts ��ŭ �ٿ��� ����
};

// �ȼ�(FIXER)��
typedef struct
{
	UID64_t			ItemUniqueNumber;
	ClientIndex_t	TargetIndex;
} MSG_FC_BATTLE_DROP_FIXER;				// �� ���� ������ŭ �� ��

typedef struct
{
	ClientIndex_t	AttackIndex;		// FIXER�� �� ��ü
	ClientIndex_t	TargetIndex;
	UINT			ItemFieldIndex;		// ���� ������ ������ �ӽ÷� �����ϴ� FIXER�� ��ȣ
	INT				ItemNum;			// Ŭ���̾�Ʈ�� �������� ������ �����ֱ� ���� ����
} MSG_FC_BATTLE_DROP_FIXER_OK;			// ������ ���� ����, ������ �����ֱ�, FIXER�� �������̸� MSG_FC_CHARACTER_GET_OTHER_INFO_OK���� �� �� MSG�� �ٿ�������.

// check: �ʿ��ϸ� �츲(���� NO BODY��), kelovon, 20030612
//typedef struct
//{
//} MSG_FC_BATTLE_REQUEST_PK;			// C->F, client�� PK ��û

typedef struct
{
	ClientIndex_t	ClientIndex;		// PK�� ��û�� client
} MSG_FC_BATTLE_REQUEST_PK_OK;			// F->C, pk ��û �³�

// check: �ʿ��ϸ� �츲(���� NO BODY��), kelovon, 20030612
//typedef struct
//{
//} MSG_FC_BATTLE_CANCEL_PK;			// F->C, PK ����

typedef struct
{
	ClientIndex_t	TargetClientIndex;		// �ǿ�û��
} MSG_FC_BATTLE_REQUEST_P2P_PK;				// C->F, �ϴ��� PK ��û

typedef struct
{
	ClientIndex_t	SourceClientIndex;		// ��û��
} MSG_FC_BATTLE_REQUEST_P2P_PK_OK;			// F->C, �ϴ��� PK ��û

typedef struct
{
	ClientIndex_t	SourceClientIndex;		// ��û��
} MSG_FC_BATTLE_ACCEPT_REQUEST_P2P_PK;		// C->F, �ϴ��� PK �³�

typedef struct
{
	ClientIndex_t	PeerClientIndex;		// ����
} MSG_FC_BATTLE_ACCEPT_REQUEST_P2P_PK_OK;	// F->C, �ϴ��� PK �³�, �� ������ ����, Ŭ���̾�Ʈ�� ������ PK ����

typedef struct
{
	ClientIndex_t	SourceClientIndex;		// ��û��
} MSG_FC_BATTLE_REJECT_REQUEST_P2P_PK;		// C->F, �ϴ��� PK ����

typedef struct
{
	ClientIndex_t	TargetClientIndex;		// �ǿ�û��
} MSG_FC_BATTLE_REJECT_REQUEST_P2P_PK_OK;	// F->C, �ϴ��� PK ����

typedef struct
{
	ClientIndex_t	TargetClientIndex;		// �ǿ�û��
} MSG_FC_BATTLE_SURRENDER_P2P_PK;			// C->F, �ϴ��� PK �׺�

typedef struct
{
	ClientIndex_t	SourceClientIndex;		// ��û��
} MSG_FC_BATTLE_SURRENDER_P2P_PK_OK;		// F->C, �ϴ��� PK �׺�

typedef struct
{
	ClientIndex_t	SourceClientIndex;		// ��û��
} MSG_FC_BATTLE_ACCEPT_SURRENDER_P2P_PK;	// C->F, �ϴ��� PK �׺� �³�, �̿� ���� ������ MSG_FC_BATTLE_END_P2P_PK�� ó��

/*
typedef struct
{
	ClientIndex_t	TargetClientIndex;		// �ǿ�û��
} MSG_FC_BATTLE_ACCEPT_SURRENDER_P2P_PK_OK;	// F->C, �ϴ��� PK �׺� �³�
*/

typedef struct
{
	ClientIndex_t	SourceClientIndex;		// ��û��
} MSG_FC_BATTLE_REJECT_SURRENDER_P2P_PK;	// C->F, �ϴ��� PK �׺� ����

typedef struct
{
	ClientIndex_t	TargetClientIndex;		// �ǿ�û��
} MSG_FC_BATTLE_REJECT_SURRENDER_P2P_PK_OK;	// F->C, �ϴ��� PK �׺� ����

typedef struct
{
	ClientIndex_t	PeerClientIndex;		// ������ ClientIndex
	USHORT			EndType;				// ���� ���� Ÿ��, BATTLE_END_XXX
} MSG_FC_BATTLE_END_P2P_PK;					// PK ����

// ���� ���� Ÿ��, BATTLE_END_XXX
#define BATTLE_END_WIN			(USHORT)0x0000	// �¸�
#define BATTLE_END_DEFEAT		(USHORT)0x0001	// �й�
#define BATTLE_END_TIE			(USHORT)0x0002	// ���º�
#define BATTLE_END_END			(USHORT)0x0003	// �׳� ����Ǿ����ϴ�(�����ҹ�)
#define BATTLE_END_TIME_LIMITE	(USHORT)0x0004	// �ð�����
#define BATTLE_END_SURRENDER	(USHORT)0x0005	// �׺�

typedef struct
{
	ClientIndex_t	TargetIndex;	// TargetIndex
	USHORT			AmountDamage;	// ������ ��
	BYTE			DamageKind;		// DAMAGEKIND_XXX
	BYTE			byIsPrimaryWeapon;		// 2008-12-03 by cmkwon, ������ ������ 1��,2�� ���� �߰� - 
	USHORT			MultiTargetIndex;		// 2011-03-21 by hskim, ���Ǵ�Ƽ 3�� - ���� ��Ƽ Ÿ���� ��� �߰�
} MSG_FC_BATTLE_SHOW_DAMAGE;		// F->C, ���� ���������� ǥ����



struct MSG_FC_BATTLE_ATTACK_EVASION		// 2005-12-12 by cmkwon
{
	ClientIndex_t	AttackIndex;
	MEX_TARGET_INFO	TargetInfo;
	UINT			ItemNum;			// ������ ItemNum, ������ 2�� ���ݿ��� ����
	UID16_t			WeaponIndex;		// Ŭ���̾�Ʈ���� �߻�� �Ѿ��� �ε���, �������� ����, CUID16Generator ���
	BYTE			AttackType;			// ���� Ÿ��, ATT_TYPE_XXX
};

typedef MSG_FC_BATTLE_ATTACK_EVASION		MSG_FC_BATTLE_ATTACK_EVASION_OK;	// 2005-12-12 by cmkwon

struct MSG_FC_BATTLE_DELETE_DUMMY_OK		// 2006-12-04 by dhjin
{
	ClientIndex_t	AttackIndex;
	UINT			ItemFieldIndex;
};

struct MSG_FC_BATTLE_EXPLODE_DUMMY_OK		// 2006-12-04 by dhjin
{
	ClientIndex_t	AttackIndex;
	UINT			ItemFieldIndex;
};


///////////////////////////////////////////////////////////////////////////////
// FN_BATTLE (Field server <-> NPC server)

typedef struct
{
	ChannelIndex_t	ChannelIndex;
	ClientIndex_t	AttackIndex;
	ClientIndex_t	TargetIndex;
	UINT			WeaponItemNumber;	// ���� Ÿ��(�� ��������,��ų����)
	USHORT			WeaponIndex;		// ���� �Ѿ�(Ȥ�� Fuel)�� ��, Fuel�� ��쿡�� x10�Ͽ� �����
	AVECTOR3		TargetPosition;		// ���� Ŭ���̾�Ʈ�� ȭ�鿡���� Ÿ�� ������
	USHORT			MultiTargetIndex;	// 2011-03-21 by hskim, ���Ǵ�Ƽ 3�� - ���� ��Ƽ Ÿ���� ��� �߰�
} MSG_FN_BATTLE_ATTACK_PRIMARY;

typedef struct
{
	ClientIndex_t	AttackIndex;
	ClientIndex_t	TargetIndex;
	UINT			WeaponItemNumber;	// ���� Ÿ��(�� ��������,��ų����)
	USHORT			WeaponIndex;		// ���� �Ѿ�(Ȥ�� Fuel)�� ��, Fuel�� ��쿡�� x10�Ͽ� �����
	AVECTOR3		TargetPosition;		// ���� Ŭ���̾�Ʈ�� ȭ�鿡���� Ÿ�� ������
	BYTE			DamageKind;
} MSG_FN_BATTLE_ATTACK_RESULT_PRIMARY;

typedef struct
{
	ChannelIndex_t	ChannelIndex;
	ClientIndex_t	AttackIndex;
	ClientIndex_t	TargetIndex;
	UINT			WeaponItemNumber;	// ���� Ÿ��(�� ��������,��ų����)
	USHORT			WeaponIndex;		// ���� �Ѿ�(Ȥ�� Fuel)�� ��, Fuel�� ��쿡�� x10�Ͽ� �����
	AVECTOR3		TargetPosition;		// ���� Ŭ���̾�Ʈ�� ȭ�鿡���� Ÿ�� ������
	USHORT			MultiTargetIndex;	// 2011-03-21 by hskim, ���Ǵ�Ƽ 3�� - ���� ��Ƽ Ÿ���� ��� �߰�
	BYTE			Distance;
	BYTE			SecAttackType;		// 2�� ���� ���� Ÿ��: SEC_ATT_TYPE_XXX, see below
	AVECTOR3		AttackPosition;		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ��ġ
} MSG_FN_BATTLE_ATTACK_SECONDARY;

typedef struct
{
	ClientIndex_t	AttackIndex;
	ClientIndex_t	TargetIndex;
	UINT			WeaponItemNumber;	// ���� Ÿ��(�� ��������,��ų����)
	USHORT			WeaponIndex;		// ���� �Ѿ�(Ȥ�� Fuel)�� ��, Fuel�� ��쿡�� x10�Ͽ� �����
	AVECTOR3		TargetPosition;		// ���� Ŭ���̾�Ʈ�� ȭ�鿡���� Ÿ�� ������
	BYTE			DamageKind;
	BYTE			Distance;
	BYTE			SecAttackType;		// 2�� ���� ���� Ÿ��: SEC_ATT_TYPE_XXX
} MSG_FN_BATTLE_ATTACK_RESULT_SECONDARY;

typedef struct
{
	ClientIndex_t	AttackIndex;
	ClientIndex_t	TargetIndex;
	AVECTOR3		TargetPosition;		// ���� Ŭ���̾�Ʈ�� ȭ�鿡���� Ÿ�� ������
	USHORT			WeaponIndex;		// Ŭ���̾�Ʈ���� �߻�� �Ѿ��� �ε���
	ChannelIndex_t	ChannelIndex;
} MSG_FN_BATTLE_ATTACK_FIND;

typedef struct
{
	ClientIndex_t	AttackIndex;
	ClientIndex_t	TargetIndex;
	USHORT			WeaponIndex;		// Ŭ���̾�Ʈ���� �߻�� �Ѿ��� �ε���
	BYTE			DamageKind;
} MSG_FN_BATTLE_ATTACK_FIND_RESULT;

typedef struct
{
	ChannelIndex_t	ChannelIndex;		// check_cmkwon, �߰��ϱ�~, 20040330, kelovon
	ClientIndex_t	AttackIndex;		// Attack Character
	ClientIndex_t	TargetIndex;		// Target Monster
	INT				ItemNum;			// Fixer�� ItemNum
} MSG_FN_BATTLE_DROP_FIXER;				// F -> N

typedef struct
{
	ChannelIndex_t	ChannelIndex;		// check_cmkwon, �߰��ϱ�~, 20040330, kelovon
	ClientIndex_t	AttackIndex;		// Attack Character
	ClientIndex_t	TargetIndex;		// Target Monster
	UINT			ItemFieldIndex;
	INT				ItemNum;			// Ŭ���̾�Ʈ�� �������� ������ �����ֱ� ���� ����
} MSG_FN_BATTLE_DROP_FIXER_OK;			// N -> F

typedef struct : public MSG_FC_BATTLE_ATTACK_HIDE_ITEM_W_KIND
{
	ChannelIndex_t	ChannelIndex;
} MSG_FN_BATTLE_ATTACK_HIDE_ITEM_W_KIND;

typedef struct
{
	ChannelIndex_t	ChannelIndex;
	ClientIndex_t	AttackIndex;
	ClientIndex_t	TargetIndex;
	float			DamageAmount;
	BYTE			ItemKind;
} MSG_FN_BATTLE_SET_ATTACK_CHARACTER;

///////////////////////////////////////////////////////////////////////////////
// Party(����, ��Ƽ) ���� ��������
///////////////////////////////////////////////////////////////////////////////

// IMServer���� FieldServer�� �Ѱ��־�� �ϴ� ����
struct MEX_FIELD_PARTY_INFO
{
	INT		nTotalPartyMember;			// �� ��Ƽ�� ��
	BYTE	lowestMemberLevel;			// ���� ��Ƽ�� level, check: FieldServer�� IMServer�� ������� level ���� �� update�ϴ� �κ� �����ؾ� ��! 20031101, kelovon
};

// ��Ƽ ����
typedef struct
{
	UID32_t		CharacterUniqueNumber;		// ������(��Ƽ��) ��ȣ
	SPARTY_INFO	PartyInfo;					// 2008-06-02 by dhjin, EP3 ���� ���� - ���� ����
	DWORD		Padding[SIZE_MAX_PACKET_PADDING];					// 2011-07-21 by hskim, ���� ���� ���� - ���� ������ ȣȯ �ȵǵ��� ����ü ũ�� �ٲ�
} MSG_IC_PARTY_CREATE;

typedef struct
{
	PartyID_t				PartyID;
	UID32_t					CharacterUniqueNumber;	// ������(��Ƽ��) ��ȣ
	MEX_FIELD_PARTY_INFO	FieldPartyInfo;
	BYTE					ExpDistributeType;		// 2008-06-02 by dhjin, EP3 ���� ���� - ���� ����ġ �й� Ÿ��
	BYTE					ItemDistributeType;		// 2008-06-02 by dhjin, EP3 ���� ���� - ���� ������ �й� Ÿ��
} MSG_FI_PARTY_CREATE_OK;

typedef struct
{
	PartyID_t	PartyID;
} MSG_FC_PARTY_CREATE_OK;

// ��Ƽ�� �ʴ�
typedef struct
{
	char		CharacterName[SIZE_MAX_CHARACTER_NAME];		// �ʴ��� ����
} MSG_FC_PARTY_REQUEST_INVITE;

typedef struct
{
	PartyID_t	PartyID;
	char		MasterCharacterName[SIZE_MAX_CHARACTER_NAME];	// ��Ƽ��
} MSG_FC_PARTY_REQUEST_INVITE_QUESTION;

typedef MSG_FC_PARTY_REQUEST_INVITE_QUESTION	MSG_FC_PARTY_REQUEST_INVITE_QUESTION_THE_ARENA;	// 2012-04-12 by jhseol, �Ʒ��� �߰����� - �ڵ���Ƽ : ��Ƽ�� ���Խ�ų Ŭ�󿡰� ��Ƽ ���� �غ� ��Ŷ ������.

typedef struct
{
	PartyID_t	PartyID;
} MSG_FC_PARTY_ACCEPT_INVITE;

typedef struct
{
	PartyID_t				PartyID;
	UID32_t					CharacterUniqueNumber;		// ���� ������ ��Ƽ��
	MEX_FIELD_PARTY_INFO	FieldPartyInfo;				// �� MSG�� F->I�� ���� ������
} MSG_FI_PARTY_ACCEPT_INVITE_OK;						// F->I, I->F �� �� ����

//////////////////////////////////////////////////////////////////////
// 2012-04-12 by jhseol, �Ʒ��� �߰����� - �ڵ���Ƽ : ����ȣ ������
typedef struct
{
	UID32_t					CharacterUniqueNumber;		/// 2012-04-12 by jhseol, �Ʒ��� �߰����� - �ڵ���Ƽ : IM���� ����� ���� ã���� ���� CUID
	int						TeamNum;					/// 2012-04-12 by jhseol, �Ʒ��� �߰����� - �ڵ���Ƽ : IM���� ���� ������ üũ�� �� ��ȣ
} MSG_FI_PARTY_ARENA_TEAM_NUM;
// end 2012-04-12 by jhseol, �Ʒ��� �߰����� - �ڵ���Ƽ : ����ȣ ������


struct IMPartyMember;

typedef struct _IM_PARTY_MEMBER_INFO
{
	UID32_t		CharacterUniqueNumber;
	char		CharacterName[SIZE_MAX_CHARACTER_NAME];
	BYTE		PilotFace;
	USHORT		UnitKind;
	USHORT		Race;
	BYTE		Level;
	//char		MapName[SIZE_MAX_MAP_NAME];	// IS_VALID_MAP_NAME()�� FALSE�̸�, ��Ƽ �Ҽ��̳� �������� �ƴ� ĳ����(�׾ ���� ĳ���� ��)
	MAP_CHANNEL_INDEX	MapChannelIndex;	// IsValid()�� FALSE�̸�, ��Ƽ �Ҽ��̳� �������� �ƴ� ĳ����(�׾ ���� ĳ���� ��)
	EN_CHECK_TYPE	VoipType;		// 2008-07-16 by dhjin, EP3 - Voip ����

	// operator overloading
	_IM_PARTY_MEMBER_INFO& operator=(const IMPartyMember& rhs);
	inline _IM_PARTY_MEMBER_INFO& operator=(const CHARACTER& rhs)
	{
		this->CharacterUniqueNumber = rhs.CharacterUniqueNumber;
		this->PilotFace = rhs.PilotFace;
		this->UnitKind = rhs.UnitKind;
		this->Race = rhs.Race;
		this->Level = rhs.Level;
		STRNCPY_MEMSET(this->CharacterName, rhs.CharacterName, SIZE_MAX_CHARACTER_NAME);
		this->MapChannelIndex = rhs.MapChannelIndex;
		return *this;
	}
} IM_PARTY_MEMBER_INFO;										// IM Server�� �׻� �����ؾ� �ϴ� ����

typedef struct
{
	PartyID_t				PartyID;
	IM_PARTY_MEMBER_INFO	IMPartyMemberInfo;
} MSG_IC_PARTY_ACCEPT_INVITE_OK;

typedef struct
{
	PartyID_t	PartyID;
} MSG_FC_PARTY_REJECT_INVITE;

typedef struct
{
	PartyID_t	PartyID;
	char		CharacterName[SIZE_MAX_CHARACTER_NAME];		// �ʴ��ߴ� ����
} MSG_FC_PARTY_REJECT_INVITE_OK;

// ��Ƽ�� ����(from IM Server)
typedef struct
{
	UID32_t		CharacterUniqueNumber;
} MSG_IC_PARTY_GET_MEMBER;					// ���� ��Ƽ������ �������� Ȯ���Ѵ�

typedef struct
{
	IM_PARTY_MEMBER_INFO	IMPartyMemberInfo;
} MSG_IC_PARTY_PUT_MEMBER;

typedef struct
{
	PartyID_t	PartyID;
} MSG_IC_PARTY_GET_ALL_MEMBER;

typedef struct
{
	PartyID_t	PartyID;
	UID32_t		MasterUniqueNumber;			// ��Ƽ���� CharacterUniqueNumber
	UINT		nNumOfPartyMembers;
	ARRAY_(IM_PARTY_MEMBER_INFO);
} MSG_IC_PARTY_PUT_ALL_MEMBER;

// ��Ƽ�� ����(from Field Server)
typedef struct _FIELD_PARTY_MEMBER_INFO
{
	UID32_t			CharacterUniqueNumber;
	ClientIndex_t	ClientIndex;
	char			CharacterName[SIZE_MAX_CHARACTER_NAME];
	//char			MapName[SIZE_MAX_MAP_NAME];	// IS_VALID_MAP_NAME()�� FALSE�̸�, ��Ƽ �Ҽ��̳� �������� �ƴ� ĳ����(�׾ ���� ĳ���� ��)
	MAP_CHANNEL_INDEX	MapChannelIndex;	// IsValid()�� FALSE�̸�, ��Ƽ �Ҽ��̳� �������� �ƴ� ĳ����(�׾ ���� ĳ���� ��)
	SHORT			HP;
	float			CurrentHP;
	SHORT			DP;
	float			CurrentDP;
	SHORT			SP;
	SHORT			CurrentSP;
	SHORT			EP;
	float			CurrentEP;

	// operator overloading
	inline _FIELD_PARTY_MEMBER_INFO& operator=(const CHARACTER& rhs)
	{
		this->CharacterUniqueNumber = rhs.CharacterUniqueNumber;
		this->ClientIndex = rhs.ClientIndex;
		this->HP = rhs.HP;
		this->CurrentHP = rhs.CurrentHP;
		this->DP = rhs.DP;
		this->CurrentDP = rhs.CurrentDP;
		this->SP = rhs.SP;
		this->CurrentSP = rhs.CurrentSP;
		this->EP = rhs.EP;
		this->CurrentEP = rhs.CurrentEP;
		STRNCPY_MEMSET(this->CharacterName, rhs.CharacterName, SIZE_MAX_CHARACTER_NAME);
		this->MapChannelIndex = rhs.MapChannelIndex;
		return *this;
	}
} FIELD_PARTY_MEMBER_INFO;

typedef struct
{
	UID32_t		CharacterUniqueNumber;
} MSG_FC_PARTY_GET_MEMBER;					// ���� ��Ƽ������ �������� Ȯ���Ѵ�

typedef struct
{
	FIELD_PARTY_MEMBER_INFO	FieldMemberInfo;
} MSG_FC_PARTY_PUT_MEMBER;

typedef struct
{
	PartyID_t	PartyID;
} MSG_FC_PARTY_GET_ALL_MEMBER;

typedef struct
{
	UID32_t		MasterUniqueNumber;			// ��Ƽ���� CharacterUniqueNumber
	UINT		nNumOfPartyMembers;
	ARRAY_(MSG_FC_PARTY_PUT_MEMBER);
} MSG_FC_PARTY_PUT_ALL_MEMBER;

// ��Ƽ�� ���� ������Ʈ
typedef struct
{
	UID32_t		CharacterUniqueNumber;
	BYTE		Level;
	SHORT		HP;
	float		CurrentHP;
	SHORT		DP;
	float		CurrentDP;
	SHORT		SP;
	SHORT		CurrentSP;
	SHORT		EP;
	float		CurrentEP;
	BodyCond_t	BodyCondition;
} MSG_FC_PARTY_UPDATE_MEMBER_INFO_ALL;

typedef struct
{
	UID32_t		CharacterUniqueNumber;
	BYTE		Level;
} MSG_FC_PARTY_UPDATE_MEMBER_INFO_LEVEL;

typedef struct
{
	UID32_t		CharacterUniqueNumber;
	SHORT		HP;
	float		CurrentHP;
} MSG_FC_PARTY_UPDATE_MEMBER_INFO_HP;

typedef struct
{
	UID32_t		CharacterUniqueNumber;
	float		CurrentHP;
} MSG_FC_PARTY_UPDATE_MEMBER_INFO_CURRENT_HP;

typedef struct
{
	UID32_t		CharacterUniqueNumber;
	SHORT		DP;
	float		CurrentDP;
} MSG_FC_PARTY_UPDATE_MEMBER_INFO_DP;

typedef struct
{
	UID32_t		CharacterUniqueNumber;
	float		CurrentDP;
} MSG_FC_PARTY_UPDATE_MEMBER_INFO_CURRENT_DP;

typedef struct
{
	UID32_t		CharacterUniqueNumber;
	SHORT		SP;
	SHORT		CurrentSP;
} MSG_FC_PARTY_UPDATE_MEMBER_INFO_SP;

typedef struct
{
	UID32_t		CharacterUniqueNumber;
	SHORT		CurrentSP;
} MSG_FC_PARTY_UPDATE_MEMBER_INFO_CURRENT_SP;

typedef struct
{
	UID32_t		CharacterUniqueNumber;
	SHORT		EP;
	float		CurrentEP;
} MSG_FC_PARTY_UPDATE_MEMBER_INFO_EP;

typedef struct
{
	UID32_t		CharacterUniqueNumber;
	float		CurrentEP;
} MSG_FC_PARTY_UPDATE_MEMBER_INFO_CURRENT_EP;

typedef struct
{
	UID32_t		CharacterUniqueNumber;
	BodyCond_t	BodyCondition;
} MSG_FC_PARTY_UPDATE_MEMBER_INFO_BODYCONDITION;

typedef struct
{
	UID32_t		CharacterUniqueNumber;
	MAP_CHANNEL_INDEX	MapChannelIndex;
} MSG_IC_PARTY_UPDATE_MEMBER_INFO_MAPNAME;		// ������ �� �̸� ������Ʈ

// �߹�
typedef struct
{
	PartyID_t	PartyID;
	UID32_t		CharacterUniqueNumber;
} MSG_IC_PARTY_BAN_MEMBER;

typedef struct
{
	PartyID_t	PartyID;
	UID32_t		CharacterUniqueNumber;
} MSG_IC_PARTY_BAN_MEMBER_OK;

typedef struct
{
	PartyID_t				PartyID;
	UID32_t					CharacterUniqueNumber;
	MEX_FIELD_PARTY_INFO	FieldPartyInfo;
} MSG_FI_PARTY_BAN_MEMBER_OK;

// Ż��
typedef struct
{
	PartyID_t	PartyID;
} MSG_IC_PARTY_LEAVE;

typedef struct
{
	PartyID_t	PartyID;
	UID32_t		CharacterUniqueNumber;
	bool		bMoveToArena;
} MSG_IC_PARTY_LEAVE_OK;

typedef struct
{
	PartyID_t				PartyID;
	UID32_t					CharacterUniqueNumber;
	MEX_FIELD_PARTY_INFO	FieldPartyInfo;
} MSG_FI_PARTY_LEAVE_OK;

// ��Ƽ�� ���� �絵
typedef struct
{
	PartyID_t	PartyID;
	UID32_t		OldMasterCharacterUniqueNumber;
	UID32_t		NewMasterCharacterUniqueNumber;
} MSG_IC_PARTY_TRANSFER_MASTER;

typedef struct
{
	PartyID_t	PartyID;
	UID32_t		OldMasterCharacterUniqueNumber;
	UID32_t		NewMasterCharacterUniqueNumber;
} MSG_IC_PARTY_TRANSFER_MASTER_OK;

typedef struct
{
	PartyID_t	PartyID;
	UID32_t		OldMasterCharacterUniqueNumber;
	UID32_t		NewMasterCharacterUniqueNumber;
} MSG_FI_PARTY_TRANSFER_MASTER_OK;

// �ػ�
typedef struct
{
	PartyID_t	PartyID;
} MSG_IC_PARTY_DISMEMBER;

typedef struct
{
	PartyID_t	PartyID;
} MSG_IC_PARTY_DISMEMBER_OK;

typedef struct
{
	PartyID_t	PartyID;
} MSG_FI_PARTY_DISMEMBER_OK;

// ���� ���� ��û
typedef struct
{
	PartyID_t	PartyID;
	BYTE		Formation;				// ���� ���� ����, see below
} MSG_IC_PARTY_CHANGE_FLIGHT_FORMATION;	// Cm -> I

// 2009-08-03 by cmkwon, EP3-4 ���� ���� ��ų ���� - AtumParam.h�� �ű�
// #define FLIGHT_FORM_NONE				(BYTE)0	// ���� ���� �� ��
// #define FLIGHT_FORM_2_COLUMN			(BYTE)1	// �̷� ����, �̷� ���� ������� �� �ٷ� ������ �� ����̴�
// #define FLIGHT_FORM_2_LINE				(BYTE)2	// �̷� Ⱦ��, �̷� Ⱦ�� ������� �� �ٷ� ������ �� ����̴�
// #define FLIGHT_FORM_TRIANGLE			(BYTE)3	// �ﰢ ����, �ﰢ�� ������� ��ܺ��� 1, 2, 3���� ������ ��ġ�Ѵ�
// #define FLIGHT_FORM_INVERTED_TRIANGLE	(BYTE)4	// ���ﰢ ����, �� �ﰢ�� ������� ��ܺ��� 3, 2, 1���� ������ ��ġ�Ѵ�
// #define FLIGHT_FORM_BELL				(BYTE)5	// �� ����, �� ������� ��ܺ��� 1, 3, 2���� ������ ��ġ�Ѵ�
// #define FLIGHT_FORM_INVERTED_BELL		(BYTE)6	// ���� ����, ���� ������� ��ܺ��� 2, 3, 1���� ������ ��ġ�Ѵ�
// #define FLIGHT_FORM_X					(BYTE)7 // X�� ����
// #define FLIGHT_FORM_STAR				(BYTE)8	// �� ����

typedef struct
{
	PartyID_t	PartyID;
	BYTE		Formation;					// ���� ���� ����
} MSG_IC_PARTY_CHANGE_FLIGHT_FORMATION_OK;	// I -> C, ��Ƽ�忡�Ե� ����

typedef struct
{
	PartyID_t	PartyID;
	BYTE		Formation;					// ���� ���� ����
} MSG_FI_PARTY_CHANGE_FLIGHT_FORMATION_OK;	// I -> C, ��Ƽ�忡�Ե� ����

typedef struct
{
	UID32_t		CharacterUniqueNumber;
} MSG_IC_PARTY_GET_FLIGHT_POSITION;			// C -> I -> Cm

typedef struct
{
	UID32_t		CharacterUniqueNumber;
	BYTE		FlightPosition;				// �ڱ� �ڽ��� ���� ���� ��ġ
} MSG_IC_PARTY_CHANGE_FLIGHT_POSITION;		// Cm -> I -> C

typedef struct
{
	PartyID_t	PartyID;
	UID32_t		CharacterUniqueNumber;
	BYTE		FlightPosition;				// �ڱ� �ڽ��� ���� ���� ��ġ
} MSG_FI_PARTY_CHANGE_FLIGHT_POSITION;		// Cm -> I -> C

// 2011-02-22 by shcho&hsSon, ������� ���� �ȵǴ� ���� ����
#define FORMATION_SKILL_NULL	0	// �����̼� ���� ������� ����
#define FORMATION_SKILL_ON		1	// �����̼� ���
#define FORMATION_SKILL_OFF		2	// �����̼� ��� ���� �ƴ�
// END 2011-02-22 by shcho&hsSon, ������� ���� �ȵǴ� ���� ����

typedef struct
{
	// 2011-02-22 by shcho&hsSon, ������� ���� �ȵǴ� ���� ����
	BOOL		Formation_On_Off;
	// end 2011-02-22 by shcho&hsSon, ������� ���� �ȵǴ� ���� ����
	UID32_t		CharacterUniqueNumber;
} MSG_IC_PARTY_CANCEL_FLIGHT_POSITION;		// C -> I -> Cm

typedef struct
{
	PartyID_t	PartyID;
	UID32_t		CharacterUniqueNumber;
} MSG_FI_PARTY_CANCEL_FLIGHT_POSITION;		// C -> I -> Cm

typedef struct
{
	UID32_t		CharacterUniqueNumber;
} MSG_IC_PARTY_MEMBER_INVALIDATED;			// I -> C, ��Ƽ���� ������������ ���ӿ��� ƨ���� �� ����

typedef struct
{
	UID32_t				CharacterUniqueNumber;
	MAP_CHANNEL_INDEX	MapChannelIndex;
} MSG_IC_PARTY_MEMBER_REJOINED;				// I -> C, ��Ƽ���� �ٽ� ������ �����Ͽ��� �� ����, �ڽ��� ������

typedef struct {
	UID32_t			CharacterUniqueNumber;	// ������ â���� ���ŵ� ��Ƽ��
	BYTE			ItemPosition;			// POS_XXX
	INT				ItemNum;
	// 2009-08-26 by cmkwon, �׷��� ���ҽ� ���� �ý��� ���� - ����
	//	INT				ColorCode;				// 2005-12-08 by cmkwon, �Ƹ� ���� Ʃ�� ����
	INT				nShapeItemNum;		// 2009-08-26 by cmkwon, �׷��� ���ҽ� ���� �ý��� ���� - 
	INT				nEffectItemNum;		// 2009-08-26 by cmkwon, �׷��� ���ҽ� ���� �ý��� ���� - 
} MSG_IC_PARTY_UPDATE_ITEM_POS;				// I->C, ��Ƽ���� ������ ������ �������� �� ����

typedef struct
{
	UID32_t			AllPartyMemberCharacterUniqueNumber[SIZE_MAX_PARTY_MEMBER - 1];
} MSG_IC_PARTY_ALL_FLIGHT_POSITION;

struct MSG_IC_PARTY_LIST_INFO
{// 2008-06-02 by dhjin, EP3 ���� ���� - ���� ���� ����Ʈ 
	PartyID_t		StartNum;
};

struct MSG_IC_PARTY_JOIN_FREE
{// 2008-06-03 by dhjin, EP3 ���� ���� - ���� ���� ����
	PartyID_t		PartyNum;
	CHAR			PartyPW[SIZE_MAX_TEAM_PW];
};

struct SPARTY_LIST_INFO
{// 2008-06-02 by dhjin, EP3 ���� ���� - ���� ���� ����Ʈ OK
	PartyID_t	PartyNum;
	CHAR		PartyName[SIZE_MAX_PARTY_NAME];
	BYTE		ExpDistributeType;
	BYTE		ItemDistributeType;
	BOOL		PartyLock;
	CHAR		PartyPW[SIZE_MAX_TEAM_PW];
	INT			MinLevel;
	INT			MaxLevel;
	CHAR		PartyMasterName[SIZE_MAX_CHARACTER_NAME];
	BYTE		Membercount;
	BOOL		VoipCheck;
};

struct MSG_IC_PARTY_LIST_INFO_OK
{// 2008-06-02 by dhjin, EP3 ���� ���� - ���� ���� ����Ʈ OK
	INT				PartyInfoTotalCount;	// 2008-06-02 by dhjin, ��Ƽ �ִ� ���
	INT				PartyInfoListCount;		// 2008-06-02 by dhjin,
	_ARRAY(SPARTY_LIST_INFO);
};

struct MSG_IC_PARTY_CHANGE_INFO
{// 2008-06-04 by dhjin, EP3 ���� ���� - ���� ���� ����
	SPARTY_INFO	PartyInfo;
};
typedef MSG_IC_PARTY_CHANGE_INFO	MSG_IC_PARTY_INFO;

struct SRECOMMENDATION_MEMBER_INFO
{
	char		CharacterName[SIZE_MAX_CHARACTER_NAME];
	UID32_t		CharacterUID;
};

struct MSG_IC_PARTY_RECOMMENDATION_MEMBER_OK
{// 2008-06-04 by dhjin, EP3 ���� ���� - ��õ �ɸ��� ��û
	UINT		Count;
	ARRAY_(SRECOMMENDATION_MEMBER_INFO);
};


// check: FI_EVENT_GET_WARP_INFO(��Ƽ ����+�̺�Ʈ ����)�� ��ü�Ѵ�. ���� ��Ƽ ������ �޾ƿ;��� �ʿ伺�� ����� �츰��. 20031006.
// �ٸ� �ʵ� ����(��Ƽ ������ ������ ����)���� ������, IM �����κ��� ������ �޾� ��Ƽ ���� ����
//typedef struct
//{
//	UID32_t			CharacterUniqueNumber;
//} MSG_FI_PARTY_GET_PARTY_INFO;
//
//typedef struct
//{
//	UID32_t			AccountUniqueNumber;		// �ٸ� �ʵ� �������� ������, ������ �ʿ���
//	UID32_t			CharacterUniqueNumber;
//	PartyID_t		PartyID;
//	UID32_t			MasterCharacterUniqueNumber;
//	int				NumOfPartyMembers;
//	ARRAY_(FI_PARTY_MEMBER_INFO);
//} MSG_FI_PARTY_GET_PARTY_INFO_OK;

typedef struct
{
	UID32_t			CharacterUniqueNumber;
	//	char			CurrentMapName[SIZE_MAX_MAP_NAME];	// check: �ٸ� �ʵ弭���� �ִ� ��Ƽ���� �������� �ʱ�� �ϸ鼭 ����, 20031010, Ȯ��&�����Ǹ� ���� ����
} FI_PARTY_MEMBER_INFO;	// Field Server�� IM Server ���̿� ����ϴ� ��Ƽ�� ����

// ���� �������� ��Ƽ�� ����
typedef struct
{
	int				nPartyMembers;				// ���� ������ ��Ƽ���� ��, ������ ����
	ARRAY_(UID32_t);							// ��Ƽ�� character uniquenumber�� array
} MSG_FC_PARTY_REQUEST_PARTY_WARP;

typedef struct
{
	MAP_CHANNEL_INDEX	MapChannelIndex;
	int					nPartyMembers;				// ���� ������ ��Ƽ���� ��, ������ ����
	ARRAY_(UID32_t);								// ��Ƽ�� character uniquenumber�� array
} MSG_FC_PARTY_REQUEST_PARTY_WARP_WITH_MAP_NAME;

//typedef struct
//{
//	INT				ObjectIndex;				// Object�� Index
//	int				nPartyMembers;				// ���� ������ ��Ƽ���� ��, ������ ����
//	ARRAY_(UID32_t);							// ��Ƽ�� character uniquenumber�� array
//} MSG_FC_PARTY_REQUEST_PARTY_OBJECT_EVENT;
typedef struct
{
	DWORD			ObjectType;
	AVECTOR3		ObjectPosition;
	int				nPartyMembers;				// ���� ������ ��Ƽ���� ��, ������ ����
	ARRAY_(UID32_t);							// ��Ƽ�� character uniquenumber�� array
} MSG_FC_PARTY_REQUEST_PARTY_OBJECT_EVENT;

// ��Ƽ���� MOVE ���� ��û
typedef struct
{
	UID32_t			OtherCharacterUniqueNumber;
} MSG_FC_PARTY_GET_OTHER_MOVE;

// ���ӿ��� �����ٰ� ������ �� ���� ���� ����
typedef struct
{
	PartyID_t	PartyID;				// �ֱٿ� ����Ҵ� ��Ƽ�� �α��Ͽ��� �� �����ϹǷ�, �׿� ���� �غ� ��û
} MSG_IC_PARTY_PUT_LAST_PARTY_INFO;		// I -> C, ��Ƽ���� �ٽ� ������ �����Ͽ��� �� ����, �ڱ� �ڽſ��Ը� ����

// ��Ƽ�� ����
typedef struct
{
	PartyID_t		PeerPartyID;				// ��� PartyID
	ClientIndex_t	PeerPartyMasterClientIndex;	// ��Ƽ���� ClientIndex
	SHORT			nPeerPartyMemberToBattle;	// ��Ƽ���� ������ ��� ��Ƽ���� ��
	ARRAY_(PEER_PARTY_MEMBER);
} MSG_FC_PARTY_BATTLE_START;					// F->C, ��� ��Ƽ�� ������ ������.

struct PEER_PARTY_MEMBER
{
	ClientIndex_t	ClientIndex;
	UID32_t			CharacterUniqueNumber;
};

typedef struct
{
	PartyID_t		PeerPartyID;				// ������ ClientIndex
	USHORT			EndType;					// ���� ���� Ÿ��, BATTLE_END_XXX
} MSG_FC_PARTY_BATTLE_END;						// F->C, ��Ƽ�� ���

typedef struct
{
	PartyID_t		PartyID1;					// ��Ƽ 1
	PartyID_t		PeerPartyID1;				// ��Ƽ 1�� ��� ��Ƽ
	PartyID_t		PartyID2;					// ��Ƽ 2
	PartyID_t		PeerPartyID2;				// ��Ƽ 2�� ��� ��Ƽ
} MSG_FI_PARTY_NOTIFY_BATTLE_PARTY;				// F->I, ��Ƽ���� �˸�

typedef struct
{
	PartyID_t		PartyID1;					// ��Ƽ 1
	PartyID_t		PeerPartyID1;				// ��Ƽ 1�� ��� ��Ƽ
	PartyID_t		PartyID2;					// ��Ƽ 2
	PartyID_t		PeerPartyID2;				// ��Ƽ 2�� ��� ��Ƽ
} MSG_FI_PARTY_NOTIFY_BATTLE_PARTY_OK;			// I->F, ��Ƽ���� �˸��� ���� ACK

typedef struct {
	INT				ItemNum;					// �������� ����
	USHORT			Amount;						// �������� ����
	ClientIndex_t	ClientIndex;
} MSG_FC_PARTY_PUT_ITEM_OTHER;					// F->C, �ٸ� ��Ƽ���� ������ ��� ���� ����

typedef struct {
	PartyID_t				PartyID;
	UID32_t					CharacterUniqueNumber;	// �߰��� ��Ƽ��
	MEX_FIELD_PARTY_INFO	FieldPartyInfo;
} MSG_FI_PARTY_ADD_MEMBER;						// I->F, ��Ƽ���� �߰��϶�� Field Server �˸�

typedef struct {
	PartyID_t				PartyID;
	UID32_t					CharacterUniqueNumber;	// ������ ��Ƽ��
	MEX_FIELD_PARTY_INFO	FieldPartyInfo;
} MSG_FI_PARTY_DELETE_MEMBER;					// I->F, ��Ƽ���� �����϶�� Field Server �˸�

typedef struct {
	UID32_t			CharacterUniqueNumber;	// ������ â���� ���ŵ� ��Ƽ��
	BYTE			ItemPosition;			// POS_XXX
	INT				ItemNum;
	// 2009-08-26 by cmkwon, �׷��� ���ҽ� ���� �ý��� ���� - ����
	//	INT				ColorCode;				// 2005-12-08 by cmkwon, �Ƹ� ���� Ʃ�� ����
	INT				nShapeItemNum;		// 2009-08-26 by cmkwon, �׷��� ���ҽ� ���� �ý��� ���� - 
	INT				nEffectItemNum;		// 2009-08-26 by cmkwon, �׷��� ���ҽ� ���� �ý��� ���� - 
} MSG_FI_PARTY_UPDATE_ITEM_POS;				// F->I, ��Ƽ���� ������ ������ �������� �� ����

typedef struct
{
	PartyID_t		PartyID;
	UID32_t			AllPartyMemberCharacterUniqueNumber[SIZE_MAX_PARTY_MEMBER - 1];
} MSG_FI_PARTY_ALL_FLIGHT_POSITION;

typedef struct
{
	PartyID_t				PartyID;
	MEX_FIELD_PARTY_INFO	FieldPartyInfo;
} MSG_FI_PARTY_UPDATE_PARTY_INFO;	// I->F, ��Ƽ ������ ������Ʈ

struct MSG_FI_PARTY_CHANGE_EXP_DISTRIBUTE_TYPE
{// 2008-06-04 by dhjin, EP3 ���� ���� - ����ġ �й� ��� ���� 
	PartyID_t	PartyID;
	BYTE		ExpDistributeType;
};

struct MSG_FI_PARTY_CHANGE_ITEM_DISTRIBUTE_TYPE
{// 2008-06-04 by dhjin, EP3 ���� ���� - ������ �й� ��� ���� 
	PartyID_t	PartyID;
	BYTE		ItemDistributeType;
};

struct MSG_FI_PARTY_CHANGE_FORMATION_SKILL		// 2009-08-03 by cmkwon, EP3-4 ���� ���� ��ų ���� - 
{
	UID32_t		PartyMasterCharcUID;	// PartyMaster CharacterUID
	BYTE		Is_On_or_Off;			// TRUE is ON, FALSE is Off
	BYTE		FlightFormation;		// 
};

///////////////////////////////////////////////////////////////////////////////
// FI_CHARACTER
typedef struct
{
	UID32_t	AccountUniqueNumber;
	UID32_t	CharacterUniqueNumber;
	UID32_t	GuildUniqueNumber;
} MSG_FI_CHARACTER_DELETE_CHARACTER;

typedef struct
{
	UID32_t	CharacterUniqueNumber;
	BYTE	Level;
} MSG_FI_CHARACTER_CHANGE_LEVEL;

typedef struct
{
	UID32_t	CharacterUniqueNumber;
	char	GuildName[SIZE_MAX_GUILD_NAME];	// ��� �̸�
	UID32_t	GuildUniqueNumber;				// ��� ��ȣ, 0�̸� ��� ����
	BOOL	GuildDelete;					// 2006-09-29 by dhjin, ��� ���� ����, 1->����
} MSG_FI_CHARACTER_UPDATE_GUILD_INFO;


// 2007-10-06 by dhjin, �������ڰ� ���� ������ InflWarManager Ŭ������ �������� ������ ����.
struct MSG_FI_CREATE_GUILD_BY_SUBLEADER
{
	byte	Influence;
	int		SubLeaderRank;
	UID32_t CharacterUID;
};

typedef struct
{
	UID32_t				CharacterUniqueNumber;
	MAP_CHANNEL_INDEX	MapChannel;
} MSG_FI_CHARACTER_UPDATE_MAP_CHANNEL;

struct MSG_FI_CHARACTER_CHANGE_INFLUENCE_TYPE
{
	UID32_t				CharacterUID;
	BYTE				InfluenceType0;					// 
};

struct MSG_FI_UPDATE_SUBLEADER
{// 2007-02-14 by dhjin, �������� ���� �� IM������ ���� ����.
	UID32_t				CharacterUID;
	BYTE				SubLeaderNum;
	BYTE				InfluenceType;
};

///////////////////////////////////////////////////////////////////////////////
// FC_GUILD (Cleint <-> Field Server)
typedef struct
{
	MapIndex_t	MapIndex;
} MSG_FC_GUILD_GET_MAP_OWNER_INFO;			// C->F, �� ���� ���� ��û

typedef struct
{
	char	DefenderGuildName[SIZE_MAX_GUILD_NAME];	// ���� ��� �̸�
	BYTE	NumOfCallengerGuilds;					// ���� ��� ��
} MSG_FC_GUILD_GET_MAP_OWNER_INFO_OK;		// F->C, �� ���� ���� ��û ���

typedef struct
{
	char	GuildName[SIZE_MAX_GUILD_NAME];
} MSG_FC_GUILD_REQUEST_GUILD_WAR;			// C->F, ������ ��û

typedef struct
{
	INT		Order;							// ����(1���� ����), 0 �����̸� ��û ����
} MSG_FC_GUILD_REQUEST_GUILD_WAR_RESULT;	// F->C, ������ ��û ���

typedef struct
{
	UID32_t	DefenderGuildUniqueNumber;		// ���� ��� ���� ��ȣ
} MSG_FC_GUILD_GET_CHALLENGER_GUILD;		// C->F, ������ ��û ��� ��� ����Ʈ ��û

typedef struct
{
	BYTE	NumOfCallengerGuilds;			// ���� ��� �̸� ����(�켱 ���� ����)
	ARRAY_(char[SIZE_MAX_GUILD_NAME]);
} MSG_FC_GUILD_GET_CHALLENGER_GUILD_OK;		// F->C, ������ ��û ��� ��� ����Ʈ ��û ���

typedef struct
{
	UID32_t		GuildUID;				// �ڽ��� ���� ����� UID
} MSG_FC_GUILD_GET_WAR_INFO;			// C->F, ������ ������ ��û

typedef struct
{
	MAP_CHANNEL_INDEX	MapChannel;		// �������� �Ͼ�� ��
	UID32_t				PeerGuildUID;	// ��� ����� ��� ��ȣ
} MSG_FC_GUILD_GET_WAR_INFO_OK;			// F->C, ������ ������ ����

struct MSG_FC_GUILD_SUMMON_MEMBER
{
	UID32_t				uidGuildUID;	// ��� UID
	MAP_CHANNEL_INDEX	MapChannel;		// �������� �ִ� ��
	AVECTOR3			PositionVector;	// �������� ��ǥ
};
struct MSG_FC_GUILD_SUMMON_MEMBER_OK
{
	UID32_t				uidGuildUID;	// ��� UID
	MAP_CHANNEL_INDEX	MapChannel;		// �������� �ִ� ��
	AVECTOR3			PositionVector;	// �������� ��ǥ
};

///////////////////////////////////////////////////////////////////////////////
// FI_GUILD (Field Server <-> IM Server)
typedef struct
{
	UID32_t		DefenderGuildUID;
	UID32_t		ChallengerGuildUID;
	MAP_CHANNEL_INDEX	WarMapChannel;
} MSG_FI_GUILD_NOTIFY_START_WAR;	// F->I

typedef struct
{
	USHORT		WarEndType;			// BATTLE_END_XXX, BATTLE_END_WIN or BATTLE_END_DEFEAT�̸� ���� ����
	UID32_t		WinnerGuildUID;
	UID32_t		LoserGuildUID;
	MAP_CHANNEL_INDEX	WarMapChannel;
} MSG_FI_GUILD_NOTIFY_END_WAR;		// F->I

typedef struct
{
	UID32_t		DeleteGuildUID;
} MSG_FI_GUILD_DELETE_GUILD;
typedef		MSG_FI_GUILD_DELETE_GUILD	MSG_FI_GUILD_REG_DELETE_GUILD;		// 2007-11-09 by dhjin

struct MSG_FI_GUILD_ADD_GUILD_FAME	// 2005-12-27 by cmkwon
{
	UID32_t		guildUID;		// 
	int			addValues;		// 1 or 100
};

struct MSG_FI_GUILD_OUTPOST
{// 2008-05-21 by dhjin, EP3 - ���� ���� ���� - �������� ����
	UID32_t		GuildUID;
	MapIndex_t	MapIndex;
};

///////////////////////////////////////////////////////////////////////////////
// IC_GUILD (Cleint <-> IM Server)
typedef struct
{
	char	GuildName[SIZE_MAX_GUILD_NAME];
} MSG_IC_GUILD_CREATE;						// C->I, ��� ���� ��û

typedef struct
{
	char	GuildName[SIZE_MAX_GUILD_NAME];
	UID32_t	GuildUniqueNumber;				// ��� ������ȣ
	char	GuildCommanderUniqueNumber;		// ������
} MSG_IC_GUILD_CREATE_OK;					// I->C, ��� ���� ���

typedef struct
{
	UID32_t	GuildUniqueNumber;				// ��� ������ȣ
} MSG_IC_GUILD_GET_GUILD_INFO;				// C->I, ��� ���� ��û

// GUILD_STATE_XXX
#define GUILD_STATE_NORMAL				((BYTE)0)	// ���� ��� ����
#define GUILD_STATE_DISMEMBER_READY		((BYTE)1)	// ��� ��ü ��� ����
#define GUILD_STATE_IN_GUILD_WAR		((BYTE)2)	// ����� ����
#define GUILD_STATE_CITYWAR				((BYTE)3)	// ���������� ����

///////////////////////////////////////////////////////////////////////////////
// 2007-08-02 by cmkwon, ���� ��ũ �ɻ� �ý��� ���� - GUILD_MARK_STATE_XXX ����
#define GUILD_MARK_STATE_NONE					((BYTE)0)	// ��ũ ���� ����
#define GUILD_MARK_STATE_WAITING_PERMISSION		((BYTE)1)	// ��ũ ����� ��ٸ��� ����, ���ӻ󿡼��� ��� �Ұ�
#define GUILD_MARK_STATE_NORMAL					((BYTE)2)	// ��ũ ��� ���� ����
char* GetStringGuildMarkState(BYTE i_byGuildMarkState, BOOL i_bForUser = FALSE);


typedef struct
{
	char	GuildName[SIZE_MAX_GUILD_NAME];
	UID32_t	GuildUniqueNumber;				// ��� ������ȣ
	UID32_t	GuildCommanderUniqueNumber;		// ������
	INT		GuildMemberCapacity;			// ��� �ο� ����
	BYTE	NumOfGuildMemberInfo;
	BYTE	GuildState;						// GUILD_STATE_XXX
	UINT	GuildMarkVersion;
	INT		WarWinPoint;					// ����� �¼�
	INT		WarLossPoint;					// ����� �м�
	char    Notice[SIZE_MAX_NOTICE];		// 2008-06-05 by dhjin, EP3 - ���� ���� ����
	MapIndex_t GuildOutPostCityMapIndex;	// 2008-06-05 by dhjin, EP3 - ���� ���� ����
	INT		GuildTotalFame;					// 2008-06-05 by dhjin, EP3 - ���� ���� ����			
	INT		GuildMonthlyFame;				// 2008-06-05 by dhjin, EP3 - ���� ���� ����
	INT		GuildTotalFameRank;				// 2008-06-05 by dhjin, EP3 - ���� ���� ����	
	INT		GuildMonthlyFameRank;			// 2008-06-05 by dhjin, EP3 - ���� ���� ����
	BOOL    GuildMemberShip;					// 2008-06-20 by dhjin, EP3 - ���� ���� ����
	ATUM_DATE_TIME GuildMemberShipExpireTime;	// 2008-06-20 by dhjin, EP3 - ���� ���� ����
	ARRAY_(MEX_GUILD_MEMBER_INFO);
} MSG_IC_GUILD_GET_GUILD_INFO_OK;			// I->C, ��� ���� ���

// ���� ���, GUILD_RANK_XXX, BYTE
#define GUILD_RANK_PRIVATE_NULL			((BYTE)0)	// ���Ҽ� ����
#define GUILD_RANK_COMMANDER			((BYTE)1)	// ���࿩����, �����
#define GUILD_RANK_SUBCOMMANDER			((BYTE)2)	// �ο�����				// 2008-05-20 by dhjin, EP3 - ���� ���� ����
#define GUILD_RANK_SQUAD_LEADER_1		((BYTE)3)	// �� 1 ��������
#define GUILD_RANK_PRIVATE_1			((BYTE)4)	// �� 1 �������
#define GUILD_RANK_SQUAD_LEADER_2		((BYTE)5)	// �� 2 ��������
#define GUILD_RANK_PRIVATE_2			((BYTE)6)	// �� 2 �������
#define GUILD_RANK_SQUAD_LEADER_3		((BYTE)7)	// �� 3 ��������
#define GUILD_RANK_PRIVATE_3			((BYTE)8)	// �� 3 �������
#define GUILD_RANK_SQUAD_LEADER_4		((BYTE)9)	// �� 4 ��������
#define GUILD_RANK_PRIVATE_4			((BYTE)10)	// �� 4 �������
#define GUILD_RANK_SQUAD_LEADER_5		((BYTE)11)	// �� 5 ��������
#define GUILD_RANK_PRIVATE_5			((BYTE)12)	// �� 5 �������

// check: MSG_IC_GUILD_GET_GUILD_INFO�� ����, �ʿ��ϸ� �츲, 20040520, kelovon
//typedef struct
//{
//	UID32_t	GuildUniqueNumber;		// ��� ������ȣ
//} MSG_IC_GUILD_GET_MEMBER;		// C->I, ���� ���� ��û

class CGuildMember;

struct MEX_GUILD_MEMBER_INFO
{
	char	MemberName[SIZE_MAX_CHARACTER_NAME];
	UID32_t	MemberUniqueNumber;
	BYTE	GuildRank;				// GUILD_RANK_XXX
	BYTE	IsOnline;				// 1: TRUE, 0: FALSE
	INT		UnitKind;				// 2008-05-20 by dhjin, EP3 - ���� ���� ����
	BYTE	MemberLevel;			// 2008-05-20 by dhjin, EP3 - ���� ���� ����	
	EN_CHECK_TYPE	VoipType;		// 2008-07-16 by dhjin, EP3 - Voip ����

#ifdef _ATUM_IM_SERVER
	// operator overloading
	MEX_GUILD_MEMBER_INFO& operator=(const CGuildMember& rhs);
#endif // _ATUM_IM_SERVER
};

// check: MSG_IC_GUILD_GET_GUILD_INFO_OK�� ����, �ʿ��ϸ� �츲, 20040520, kelovon
//typedef struct
//{
//	UID32_t	GuildUniqueNumber;		// ��� ������ȣ
//	BYTE	NumOfGuildMemberInfo;
//	ARRAY_(MEX_GUILD_MEMBER_INFO);
//} MSG_IC_GUILD_GET_MEMBER_OK;		// I->C, ���� ���� ���

class CGuild;

struct MEX_OTHER_GUILD_INFO
{
	char	GuildName[SIZE_MAX_GUILD_NAME];
	UID32_t	GuildUniqueNumber;
	UINT	GuildMarkVersion;

#ifdef _ATUM_IM_SERVER
	// operator overloading
	MEX_OTHER_GUILD_INFO& operator=(const CGuild& rhs);
#endif // _ATUM_IM_SERVER
};

typedef struct
{
	UID32_t	GuildUniqueNumber;
} MSG_IC_GUILD_GET_OTHER_GUILD_INFO;

typedef struct
{
	MEX_OTHER_GUILD_INFO		OtherGuildMemberInfo;
} MSG_IC_GUILD_GET_OTHER_GUILD_INFO_OK;

typedef struct
{
	char	InviteeCharacterName[SIZE_MAX_CHARACTER_NAME];		// �ʴ��� ���� ���̵�
} MSG_IC_GUILD_REQUEST_INVITE;		// C->I, ���� ����, ������ ��û

typedef struct
{
	UID32_t	GuildUniqueNumber;										// ��� ���� ��ȣ
	char	GuildName[SIZE_MAX_GUILD_NAME];							// ��� �̸�
	char	GuildCommanderCharacterName[SIZE_MAX_CHARACTER_NAME];	// ����� ���̵�
} MSG_IC_GUILD_REQUEST_INVITE_QUESTION;		// I->C, ���� ����, ����ڿ��� ����

typedef struct
{
	UID32_t	GuildUniqueNumber;		// ��� ���� ��ȣ, MSG_IC_GUILD_REQUEST_INVITE_QUESTION�� �� 
} MSG_IC_GUILD_ACCEPT_INVITE;		// C->I, ���� �³�, ������ ��û

typedef struct
{
	MEX_GUILD_MEMBER_INFO	MemberInfo;		// �� ������ ����
} MSG_IC_GUILD_ACCEPT_INVITE_OK;			// I->C, ���� �³�, ����� �� �������� ����

typedef struct
{
	UID32_t	GuildUniqueNumber;		// ��� ���� ��ȣ, MSG_IC_GUILD_REQUEST_INVITE_QUESTION�� ��
} MSG_IC_GUILD_REJECT_INVITE;		// C->I, ���� �ź�, ������ ��û

typedef struct
{
	char	CharacterName[SIZE_MAX_CHARACTER_NAME];	// ���� �ź��� character�� �̸�
} MSG_IC_GUILD_REJECT_INVITE_OK;	// I->C, ���� �ź�, ����ڿ��� ����

typedef struct
{
	UID32_t	MemberUniqueNumber;
} MSG_IC_GUILD_BAN_MEMBER;			// C->I, ���� �߹�

typedef struct
{
	UID32_t	MemberUniqueNumber;
} MSG_IC_GUILD_BAN_MEMBER_OK;		// I->C, ���� �߹� ���

typedef struct
{
	UID32_t	GuildUniqueNumber;
} MSG_IC_GUILD_LEAVE;				// C->I, ���� Ż��

typedef struct
{
	UID32_t	MemberUniqueNumber;
	DWORD	Padding[SIZE_MAX_PACKET_PADDING];				// 2011-07-21 by hskim, ���� ���� ���� - ���� ������ ȣȯ �ȵǵ��� ����ü ũ�� �ٲ�
} MSG_IC_GUILD_LEAVE_OK;			// I->C, ���� Ż�� ���

typedef struct
{
	UID32_t	GuildUniqueNumber;
} MSG_IC_GUILD_DISMEMBER;			// C->I, ���� ��ü
typedef MSG_IC_GUILD_DISMEMBER		MSG_FC_GUILD_DISMEMBER;
typedef MSG_IC_GUILD_DISMEMBER		MSG_FI_GUILD_DISMEMBER;


typedef struct
{
	char	GuildName[SIZE_MAX_GUILD_NAME];
} MSG_IC_GUILD_DISMEMBER_OK;		// I->C, ���� ��ü ���

// GUILD_MEMBER_STATE_XXX
#define GUILD_MEMBER_STATE_OFFLINE		((BYTE)0)
#define GUILD_MEMBER_STATE_ONLINE		((BYTE)1)

typedef struct
{
	UID32_t	MemberUniqueNumber;
	BYTE	GuildMemberState;		// GUILD_MEMBER_STATE_XXX
} MSG_IC_GUILD_SET_MEMBER_STATE;	// I->C, ������ ���� ��ȭ(ONLINE, OFFLINE ��)

typedef struct
{
	UID32_t	GuildUniqueNumber;
} MSG_IC_GUILD_CANCEL_DISMEMBER;		// C->I, ���� ��ü ��� ��û

typedef struct
{
	BYTE	GuildState;					// GUILD_STATE_XXX
} MSG_IC_GUILD_CANCEL_DISMEMBER_OK;		// I->C, ���� ��ü ��� ���

typedef struct
{
	UID32_t	GuildUniqueNumber;
} MSG_IC_GUILD_GET_DISMEMBER_DATE;		// C->I, ��� �ػ� �ð� ��û

typedef struct
{
	ATUM_DATE_TIME	DismemberDateTime;
} MSG_IC_GUILD_GET_DISMEMBER_DATE_OK;	// C->I, ��� �ػ� �ð� ���

typedef struct
{
	char	NewGuildName[SIZE_MAX_GUILD_NAME];
} MSG_IC_GUILD_CHANGE_GUILD_NAME;		// C->I, ���� �̸� ���� ��û

typedef struct
{
	char	NewGuildName[SIZE_MAX_GUILD_NAME];
} MSG_IC_GUILD_CHANGE_GUILD_NAME_OK;	// I->C, ���� �̸� ���� ���

typedef struct
{
	UID32_t	GuildUniqueNumber;
} MSG_IC_GUILD_GET_GUILD_MARK;			// C->I, ���� ���� ��û

// MSG_SEQUENCE_XXX
#define MSG_SEQUENCE_SINGLE		((BYTE)0)	// �ܵ� MSG
#define MSG_SEQUENCE_BEGIN		((BYTE)1)	// LONG MSG�� ����
#define MSG_SEQUENCE_MIDDLE		((BYTE)2)	// LONG MSG�� �߰�
#define MSG_SEQUENCE_END		((BYTE)3)	// LONG MSG�� ��

typedef struct
{
	UID32_t	GuildUniqueNumber;
	UINT	GuildMarkVersion;
	UINT	SizeOfGuildMark;			// ��� ������ size <= SIZE_MAX_GUILD_MARK_IMAGE
	ARRAY_(char);						// ��� ����, image(bmp, gif, jpg, ...)
} MSG_IC_GUILD_GET_GUILD_MARK_OK;		// I->C, ���� ���� ���

typedef struct
{
	UINT	SizeOfGuildMark;			// ��� ������ size <= SIZE_MAX_GUILD_MARK_IMAGE
	ARRAY_(char);						// ��� ����, image(bmp, gif, jpg, ...)
} MSG_IC_GUILD_SET_GUILD_MARK;			// C->I, ���� ���� ���� ��û

typedef struct
{
	UINT	GuildMarkVersion;
	UINT	SizeOfGuildMark;			// ��� ������ size <= SIZE_MAX_GUILD_MARK_IMAGE
	ARRAY_(char);						// ��� ����, image(bmp, gif, jpg, ...)
} MSG_IC_GUILD_SET_GUILD_MARK_OK;		// I->C, ���� ���� ���� ���

typedef struct
{
	UID32_t	MemberUniqueNumber;
	BYTE	GuildRank;					// GUILD_RANK_XXX
} MSG_IC_GUILD_SET_RANK;				// C->I, ��� ����

typedef struct
{
	UID32_t	MemberUniqueNumber;
	BYTE	GuildRank;					// GUILD_RANK_XXX
} MSG_IC_GUILD_SET_RANK_OK;				// I->C, ��� ���� ���

typedef struct
{
	BYTE	GuildState;					// GUILD_STATE_XXX
} MSG_IC_GUILD_CHANGE_GUILD_STATE;		// I->C, ���� ���� ����

typedef struct
{
	UID32_t	GuildUniqueNumber;
} MSG_IC_GUILD_LOADING_GUILD_DONE;		// I->C, ���������� ��� ���� �ε� �Ϸ� �˸�

typedef struct
{
	UID32_t		PeerGuildUID;			// ��� ���
	INT			WaitingTime;			// ��� �ð�, ���� ���õ� �ð� �Ŀ� ������ ����
} MSG_IC_GUILD_WAR_READY;				// I->C, ������ ���� ��� ���¸� �˸�

typedef struct
{
	UID32_t		PeerGuildUID;			// ��� ���
} MSG_IC_GUILD_START_WAR;				// I->C, ������ ������ �˸�

typedef struct
{
	USHORT		WarEndType;				// ���, BATTLE_END_XXX
	char		PeerGuildName[SIZE_MAX_GUILD_NAME];	// ��� ��� �̸�
} MSG_IC_GUILD_END_WAR;					// I->C, ������ ���Ḧ �˸�

typedef struct
{
	INT			WarWinPoint;			// ����� �¼�
	INT			WarLossPoint;			// ����� �м�
} MSG_IC_GUILD_UPDATE_WAR_POINT;

struct MSG_IC_GUILD_CHANGE_MEMBER_CAPACITY
{
	UID32_t		guildUID;				// ��� UID
	INT			nMemberCapacity;		// ���� ���� �ο�
	INT			IncreaseCapacity;		// 2008-05-28 by dhjin, EP3 ���� ���� ���� - ���ܿ� ���� ĳ�� ������
};

struct MSG_IC_GUILD_GET_GUILD_MEMBER_LIST_OK
{
	UID32_t	GuildUniqueNumber;				// ��� ������ȣ
	BYTE	NumOfGuildMemberInfo;
	ARRAY_(MEX_GUILD_MEMBER_INFO);
};

struct MSG_IC_GUILD_END_WAR_ADMIN_NOTIFY		// 2006-08-09 by cmkwon
{
	USHORT		WarEndType;								// ���, BATTLE_END_XXX
	char		WinerGuildName[SIZE_MAX_GUILD_NAME];	// �¸� ��� �̸�
	char		LoserGuildName[SIZE_MAX_GUILD_NAME];	// �й� ��� �̸�
};

struct MSG_IC_GUILD_MEMBER_LEVEL_UP
{// 2008-05-20 by dhjin, EP3 - ���� ���� ���� - ���ܿ� ������ ����
	UID32_t		CharacterUID;
	INT			Level;
};

struct MSG_IC_GUILD_NEW_COMMANDER
{// 2008-05-20 by dhjin, EP3 - ���� ���� ���� - ������ ����
	UID32_t		NewCommanderUID;
};

struct MSG_IC_GUILD_NOTICE_WRITE
{// 2008-05-20 by dhjin, EP3 - ���� ���� ���� - ���� ����
	char		Notice[SIZE_MAX_NOTICE];
};
typedef MSG_IC_GUILD_NOTICE_WRITE   MSG_IC_GUILD_NOTICE_WRITE_OK;

struct MSG_IC_GUILD_GET_INTRODUCTION_OK
{// 2008-05-27 by dhjin, EP3 - ���� ���� ���� - ���� ������ ����
	char		GuildIntroduction[SIZE_MAX_NOTICE];
};

struct MSG_IC_GUILD_GET_APPLICANT_OK
{// 2008-05-27 by dhjin, EP3 - ���� ���� ���� - ���� ������ ����
	UID32_t		CharacterUID;
	char		CharacterName[SIZE_MAX_CHARACTER_NAME];
	BYTE		UnitKind;
	INT			Level;
};

struct MSG_IC_GUILD_GET_SELF_INTRODUCTION
{// 2008-05-27 by dhjin, EP3 - ���� ���� ���� - ���� ������ �Ұ��� 
	UID32_t		CharacterUID;
};

struct MSG_IC_GUILD_GET_SELF_INTRODUCTION_OK
{// 2008-05-27 by dhjin, EP3 - ���� ���� ���� - ���� ������ �Ұ��� 
	char		GuildName[SIZE_MAX_GUILD_NAME];
	char		SelfIntroduction[SIZE_MAX_NOTICE];
};

struct MSG_IC_GUILD_SEARCH_INTRODUCTION_OK
{// 2008-05-27 by dhjin, EP3 - ���� ���� ���� - ���� �Ұ� �˻�
	UID32_t			GuildUID;
	char			GuildName[SIZE_MAX_GUILD_NAME];
	ATUM_DATE_TIME	WriteDate;
	char			GuildIntroduction[SIZE_MAX_NOTICE];
	char			CharacterName[SIZE_MAX_CHARACTER_NAME];
};

struct MSG_IC_GUILD_UPDATE_INTRODUCTION
{// 2008-05-28 by dhjin, EP3 - ���� ���� ���� - ���� �Ұ� �ۼ� 
	char			GuildIntroduction[SIZE_MAX_NOTICE];
};

struct MSG_IC_GUILD_UPDATE_SELFINTRODUCTION
{// 2008-05-28 by dhjin, EP3 - ���� ���� ���� - �ڱ� �Ұ� �ۼ�
	UID32_t			TargetGuildUID;
	char			SelfIntroduction[SIZE_MAX_NOTICE];
};

struct MSG_IC_GUILD_CHANGE_FAME_RANK
{// 2008-06-10 by dhjin, EP3 - ���� ���� ���� - ���� ���� ����
	INT		GuildTotalFameRank;
	INT		GuildMonthlyFameRank;
};

struct MSG_IC_GUILD_APPLICANT_INVITE
{// 2008-06-12 by dhjin, EP3 - ���� ���� ���� - ������ �������� ���ܿ� �ʴ�
	UID32_t		CharacterUID;
	char		CharacterName[SIZE_MAX_CHARACTER_NAME];
	BYTE		UnitKind;
	INT			Level;
};

struct MSG_IC_GUILD_APPLICANT_REJECT_INVITE
{// 2008-06-12 by dhjin, EP3 - ���� ���� ���� - ������ �������� ���ܿ� �ʴ� �ź� 
	UID32_t		CharacterUID;
	char		GuildName[SIZE_MAX_GUILD_NAME];
};

struct MSG_IC_GUILD_CHANGE_MEMBERSHIP
{// I->C, // 2008-06-20 by dhjin, EP3 - ���� ���� ���� - ������ �ɹ��� ���� ����
	BOOL			MemberShip;
	ATUM_DATE_TIME	MemberShipExpireTime;
};

///////////////////////////////////////////////////////////////////////////////
// FC_QUEST
struct MEX_QUEST_INFO						// Character�� ����Ʈ ����
{
	INT				QuestIndex;				// ����Ʈ ��ȣ
	BYTE			QuestState;				// �Ϸ�, ������
	LONGLONG		QuestPlayTimeStamp;		// ����Ʈ ���� ���� TotalPlayTime
	char			szCityWarServerGroupName[SIZE_MAX_SERVER_NAME];
};

struct MEX_QUEST_MONSTER_COUNT						// Character�� ����Ʈ ����
{
	INT				QuestIndex;				// ����Ʈ ��ȣ
	INT				MonsterUniqueNumber;
	INT				Count;
};

typedef struct
{
	INT			QuestIndex;
	BYTE		QuestStartType;			// QUEST_START_TYPE_XXX
	BYTE		PassQuest;				// ����Ʈ�� �׳� �ѱ�, CQuest::IsDiscardable�� TRUE�� ���� ó����
	AVECTOR3	AVec3QuestPosition;		// ����Ʈ ���۽� ��ǥ, 2005-08-29 by cmkwon
	char		szCouponNumber[SIZE_MAX_COUPON_NUMBER];
} MSG_FC_QUEST_REQUEST_START;		// C->F, Quest ������ ��û

typedef struct
{
	MEX_QUEST_INFO	MexQuestInfo;	// ����Ʈ ����
	float			fVCNInflDistributionPercent;	// 2006-02-08 by cmkwon, ���������� ���Ա� ���º��� - ���¼��� �̼ǽø� ����
	float			fANIInflDistributionPercent;	// 2006-02-08 by cmkwon, �˸��� ���Ա� - ���¼��� �̼ǽø� ����
} MSG_FC_QUEST_REQUEST_START_RESULT;	// F->C, Quest ������ ����, Client�� �� MSG�� ������ Pre NPCTalk�� �ε��Ѵ�

typedef struct
{
	INT		QuestIndex;
} MSG_FC_QUEST_ACCEPT_QUEST;	// C->F, Quest�� �޾Ƶ���

typedef struct
{
	INT		QuestIndex;
} MSG_FC_QUEST_CANCEL_QUEST;	// C->F, Quest�� ������(������ �� ���� Quest�� ������)

// check: no body, �ʿ��ϸ� �츲
//typedef struct {
//} MSG_FC_QUEST_LEAVE_NPC;		// C->F, NPC�� ����
//
//typedef struct {
//} MSG_FC_QUEST_LEAVE_NPC_OK;	// F->C, NPC�� ������ ���� ACK

typedef struct
{
	INT			QuestIndex;
	INT			QuestResult;			// ����Ʈ�� ���� Ȥ�� ����, 0�̸� ����, 10~13(A~D)�̸� �Ѱ��ֱ�, check: ����� ������� �Ѱ��ֱ�, 20040224, kelovon
	INT			SpentTimeInSeconds;		// ����Ʈ ���� �� ���� �ð�, 20041129, kelovon, ���������� Ŭ���̾�Ʈ �ð��� �������� ����
	AVECTOR3	AVec3QuestPosition;		// ����Ʈ �Ϸ�� ��ǥ, 2005-08-29 by cmkwon
} MSG_FC_QUEST_REQUEST_SUCCESS;	// C->F, Quest ��� ������ ��û

struct QUEST_PAY_ITEM_INFO
{
	INT		ItemNum;					// 2007-07-09 by dhjin, ���� ������ ��ȣ 
	INT		ItemCount;					// 2007-07-09 by dhjin, ���� ������ ��
};

typedef struct
{
	INT		QuestIndex;
	BOOL	IsSuccessful;
	INT		QuestResult;		// ����Ʈ�� ���� Ȥ�� ����, 0�̸� ����, 10~13(A~D)�̸� �Ѱ��ֱ�, check: ����� ������� �Ѱ��ֱ�, 20040224, kelovon
	INT		ExpOfCompensation;			// 2007-03-06 by cmkwon, ����Ʈ �Ϸ�� ������ �߰��� ���� ����ġ
	BYTE	BonusStatOfCompensation;	// 2007-07-09 by dhjin, BonusStat ���� ���� 
	INT		QuestPayInfoListCount;		// 2007-07-09 by dhjin, ������ ���� ��
	ARRAY_(QUEST_PAY_ITEM_INFO);
} MSG_FC_QUEST_REQUEST_SUCCESS_RESULT;	// F->C, Quest ���(�Ϸ�)�� �˸�, Client�� �� MSG�� ������ quest�� �����ϰ� After NPCTalk�� �ε��Ѵ�

typedef struct
{
	float			fVCNInflDistributionPercent;	// 2006-02-08 by cmkwon, ���������� ���Ա� ���º��� - ���¼��� �̼ǽø� ����
	float			fANIInflDistributionPercent;	// 2006-02-08 by cmkwon, �˸��� ���Ա� - ���¼��� �̼ǽø� ����
	INT		NumOfQuest;
	ARRAY_(MEX_QUEST_INFO);		// QuestIndex�� array, see below
} MSG_FC_QUEST_PUT_ALL_QUEST;			// F->C, �Ϸ�ǰų� �������� ��� ����Ʈ�� ����, ���� ���� �� ������ ���� �� �̾ ����

typedef struct
{
	INT		QuestIndex;
} MSG_FC_QUEST_DISCARD_QUEST;		// C->F, �̹� ���۵� ����Ʈ�� ������

typedef struct
{
	INT		QuestIndex;
	BYTE	IsDiscarded;			// ����Ʈ ���� ���� ����, 1: TRUE, 0:FALSE
} MSG_FC_QUEST_DISCARD_QUEST_OK;	// F->C, �̹� ���۵� ����Ʈ�� �����Կ� ���� ���

struct MSG_FC_QUEST_MOVE_QUEST_MAP
{
	INT		QuestIndex0;
};

struct MSG_FC_QUEST_PUT_ALL_QUEST_MONSTER_COUNT
{
	INT		NumOfMonsterCount;
	ARRAY_(MEX_QUEST_MONSTER_COUNT);
};	// 2005-10-25 by cmkwon

typedef MEX_QUEST_MONSTER_COUNT					MSG_FC_QUEST_UPDATE_MONSTER_COUNT; 	// 2005-10-25 by cmkwon

typedef MSG_FC_QUEST_REQUEST_SUCCESS			MSG_FC_QUEST_REQUEST_SUCCESS_CHECK;			// 2006-03-24 by cmkwon

typedef MSG_FC_QUEST_REQUEST_SUCCESS_RESULT		MSG_FC_QUEST_REQUEST_SUCCESS_CHECK_RESULT;	// 2006-03-24 by cmkwon

struct MSG_FC_QUEST_REQUEST_PARTY_WARP			// 2006-10-16 by cmkwon
{
	UID32_t				callerCharacterUID;			// ȣ���� CharcterUID
	DWORD				dwRemainTime;				// ����:ms(ex> 1000 <== 1��)
	MAP_CHANNEL_INDEX	warpMapChannIndex;
};

struct MSG_FC_QUEST_REQUEST_PARTY_WARP_ACK		// 2006-10-16 by cmkwon
{
	UID32_t				callerCharacterUID;
	MAP_CHANNEL_INDEX	warpMapChannIndex;
};

///////////////////////////////////////////////////////////////////////////////
// FC_MONSTER (Client <-> Field server)

typedef MSG_FC_CHARACTER_GET_MONSTER_INFO_OK		MSG_FC_MONSTER_CREATED;

typedef struct
{
	ClientIndex_t	MonsterIndex;
	ClientIndex_t	TargetIndex;
	AVECTOR3		PositionVector;
	AVECTOR3		TargetVector;
} MSG_FC_MONSTER_MOVE_OK;

typedef struct
{
	ClientIndex_t	MonsterIndex;
} MSG_FC_MONSTER_HIDE;

typedef MSG_FC_MONSTER_HIDE							MSG_FC_MONSTER_SHOW;

typedef struct
{
	ClientIndex_t	MonsterIndex;
	INT				CurrentHP;
} MSG_FC_MONSTER_CHANGE_HP;					// F -> C, ������ ���� HP�� ������

typedef struct
{
	ClientIndex_t	MonsterIndex;
	BodyCond_t		BodyCondition;					// ���� 32bit�� ��� <-- check: ��ų bodycon�� �������� �����ϱ�!
} MSG_FC_MONSTER_CHANGE_BODYCONDITION;

typedef struct
{
	ClientIndex_t		MonsterIndex;				// ��ų�� ����� ����
	ClientIndex_t		ClientIndex;				// ���� ��ų�� ���Ḧ �˷��� Ŭ���̾�Ʈ �ε���
	INT					SkillItemNum;				// ��ų�� ItemNum
} MSG_FC_MONSTER_SKILL_USE_SKILL;

// start 2011-05-17 by hskim, ���Ǵ�Ƽ 3�� - �ó׸� ���� ��ü ���
typedef struct
{
	ClientIndex_t	MonsterIndex;
	INT				ChangeMonsterUnitKind;
} MSG_FC_MONSTER_CHANGE_INDEX;					// F -> C, ���� ��ü �޽��� ����
// end 2011-05-17 by hskim, ���Ǵ�Ƽ 3�� - �ó׸� ���� ��ü ���

typedef struct
{
	ClientIndex_t	MonsterIndex;
	AVECTOR3		PositionVector;
	AVECTOR3		TargetVector;
} MSG_FC_MONSTER_SKILL_END_SKILL;

struct MSG_FC_MONSTER_SUMMON_MONSTER
{
	ClientIndex_t	clientIdx;
	INT				SummonMonsterUnitKind;			// ���� ������ȣ
	INT				nSummonCounts;
	BYTE			byMonsterTargetType2;
	int				nTargetTypeData2;
	AVECTOR3		PositionAVector;
};
struct MSG_FC_MONSTER_TUTORIAL_MONSTER_DEAD_NOTIFY
{
	ClientIndex_t	monsterIdx;
};
struct MSG_FC_MONSTER_TUTORIAL_MONSTER_DELETE
{
	ClientIndex_t	monsterIdx;
};

///////////////////////////////////////////////////////////////////////////////
// FN_MONSTER (Field server <-> NPC server)
typedef struct
{
	USHORT		CreateChannelCounts;
	BOOL		bCityWarStarted;
	UID32_t		CityWarOccupyGuildUID;
	ARRAY_(MSG_FN_CONNECT_SET_CHANNEL_STATE);
} MSG_FN_MAPPROJECT_START_OK;

typedef struct
{
	ChannelIndex_t			ChannelIndex;
	ClientIndex_t			MonsterIndex;				// �ε���
	INT						MonsterUnitKind;				// ���� ������ȣ
	BYTE					MonsterTargetType1;
	int						TargetTypeData1;
	ClientIndex_t			CltIdxForTargetType1;
	BodyCond_t				BodyCondition;					// ���� BodyCondition
	AVECTOR3				PositionVector;					// ���� ��ǥ
	AVECTOR3				TargetVector;					//
	BYTE					ObjectMonsterType;
	MONSTER_BALANCE_DATA	MonsterBalanceData;				// 2010. 05. 19 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����. (��ȣó�� + ���� ó��(����) ) - ���� �뷱�� ���� �߰�.
} MSG_FN_MONSTER_CREATE;	// check: ���ʿ��� ������ ���־� ���� ������? Ȯ�� ���!

typedef struct
{
	ChannelIndex_t	ChannelIndex;
	ClientIndex_t	MonsterIndex;
} MSG_FN_MONSTER_CREATE_OK;

typedef struct
{
	ChannelIndex_t	ChannelIndex;
	ClientIndex_t	MonsterIndex;
	BOOL			CinemaDelete;		// 2011-05-30 by hskim, ���Ǵ�Ƽ 3�� - ���� ���� Ŭ���̾�Ʈ �ݿ� - �ó׸����� �����Ѱ�� TRUE
} MSG_FN_MONSTER_DELETE;

// start 2011-05-11 by hskim, ���Ǵ�Ƽ 3�� - �ó׸� ���� ��� �߰� - �ش� ��ä�� Ư�� ���� ���� ��� �߰�
typedef struct
{
	ChannelIndex_t	ChannelIndex;
	ClientIndex_t	MonsterIndex;
	INT				ChangeMonsterUnitKind;
} MSG_FN_MONSTER_CHANGE_OK;
// end 2011-05-11 by hskim, ���Ǵ�Ƽ 3�� - �ó׸� ���� ��� �߰� - �ش� ��ä�� Ư�� ���� ���� ��� �߰�

// start 2011-05-30 by hskim, ���Ǵ�Ƽ 3�� - ���� ���� Ŭ���̾�Ʈ �ݿ�
struct MSG_FC_MONSTER_CINEMA_DELETE_NOTIFY
{
	ClientIndex_t	MonsterIdx;
};
// end 2011-05-30 by hskim, ���Ǵ�Ƽ 3�� - ���� ���� Ŭ���̾�Ʈ �ݿ�

typedef struct
{
	ChannelIndex_t	ChannelIndex;
	ClientIndex_t	ClientIndex;
	ClientIndex_t	TargetIndex;
	AVECTOR3		PositionVector;
	AVECTOR3		TargetVector;
	USHORT			usSendRange;
} MSG_FN_MONSTER_MOVE;

typedef struct
{
	ChannelIndex_t	ChannelIndex;
	ClientIndex_t	ClientIndex;
	AVECTOR3		PositionVector;
	AVECTOR3		TargetVector;
} MSG_FN_MOVE_OK;

struct MEX_CHARACTER_1
{
	USHORT			Race;						// ����
	USHORT			UnitKind;
	BYTE			InfluenceType0;				// 2005-12-27 by cmkwon
	BYTE			CharacterMode0;				// 2005-07-15 by cmkwon
	UID32_t			CharacterUniqueNumber;
	UID32_t			GuildUID;
	BodyCond_t		BodyCondition;				// ����, bit flag ���
	float			CurrentHP;					// ������
	AVECTOR3		PositionVector;				// ĳ���� ��ǥ

	MEX_CHARACTER_1& operator=(const CHARACTER& rhs)
	{
		Race = rhs.Race;
		UnitKind = rhs.UnitKind;
		InfluenceType0 = rhs.InfluenceType;
		CharacterMode0 = rhs.CharacterMode;
		CharacterUniqueNumber = rhs.CharacterUniqueNumber;
		GuildUID = rhs.GuildUniqueNumber;
		BodyCondition = rhs.BodyCondition;
		CurrentHP = rhs.CurrentHP;
		PositionVector = rhs.PositionVector;
		return *this;
	};
};
typedef struct
{
	ChannelIndex_t	ChannelIndex;
	ClientIndex_t	ClientIndex;
	MEX_CHARACTER_1	mexCharacter;
	UID32_t			GuildMasterCharUID;
	BOOL			bStealthState1;
	BOOL			bInvisible;			// 2006-11-27 by dhjin, ĳ���� �Ⱥ��̱� �÷���
} MSG_FN_CLIENT_GAMESTART_OK;

typedef struct
{
	ChannelIndex_t	ChannelIndex;
	ClientIndex_t	ClientIndex;
} MSG_FN_GET_CHARACTER_INFO;

typedef MSG_FN_CLIENT_GAMESTART_OK					MSG_FN_GET_CHARACTER_INFO_OK;

typedef struct
{
	ChannelIndex_t			ChannelIndex;
	char					CharacterName[SIZE_MAX_CHARACTER_NAME];
	INT						MonsterUnitKind;
	BYTE					MonsterTargetType1;
	int						TargetTypeData1;
	ClientIndex_t			CltIdxForTargetType1;
	INT						NumOfMonster;
	AVECTOR3				Position;

	// 2010. 06. 08 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����. (�Ʊ� ���� �뷱�� ����.)
	MONSTER_BALANCE_DATA	MonsterBalanceData;

} MSG_FN_ADMIN_SUMMON_MONSTER;

typedef struct
{
	ChannelIndex_t		ChannelIndex;
	ClientIndex_t		MonsterIndex;
	float				CurrentHP;
} MSG_FN_MONSTER_CHANGE_HP;

typedef struct : MSG_FC_CHARACTER_CHANGE_BODYCONDITION
{
	ChannelIndex_t		ChannelIndex;
} MSG_FN_MONSTER_CHANGE_BODYCONDITION;

typedef struct
{
	ChannelIndex_t		ChannelIndex;
	ClientIndex_t		MonsterIndex;				// ��ų�� ����� ����
	ClientIndex_t		ClientIndex;				// ���� ��ų�� ���Ḧ �˷��� Ŭ���̾�Ʈ �ε���
	INT					SkillItemNum;				// ��ų�� ItemNum
} MSG_FN_MONSTER_SKILL_USE_SKILL;

typedef struct
{
	ChannelIndex_t		ChannelIndex;
	ClientIndex_t		MonsterIndex;
	AVECTOR3			PositionVector;
	AVECTOR3			TargetVector;
} MSG_FN_MONSTER_SKILL_END_SKILL;

struct MSG_FN_MONSTER_AUTO_DESTROYED		// 2006-04-17 by cmkwon
{
	MAP_CHANNEL_INDEX	MapChannIdx;				// 2007-11-26 by cmkwon, ���� �ڵ����� �޽��� TCP�� ����(N->F) - MSG_FN_MONSTER_AUTO_DESTROYED �� �ʵ� �߰�
	// 2007-11-26 by cmkwon, ���� �ڵ����� �޽��� TCP�� ����(N->F) - MapChannIdx �� �߰�
	//	ChannelIndex_t		ChannelIndex;
	ClientIndex_t		MonsterIndex;
	BodyCond_t			BodyCondition;				// 2007-11-26 by cmkwon, ���� �ڵ����� �޽��� TCP�� ����(N->F) - MSG_FN_MONSTER_AUTO_DESTROYED �� �ʵ� �߰�
};

struct MSG_FN_MONSTER_STRATEGYPOINT_INIT		// 2006-11-20 by cmkwon
{
	ChannelIndex_t		ChannelIndex;
	int					bVCNMapInflTyforInit;	// 2007-09-16 by dhjin, Belligerence �˻����� �������� ���Ͽ� ������Ʈ Bell������ ���� // 2006-11-21 by cmkwon, �ʱ�ȭ �� ���� VCN���� ����(TRUE=IS_MAP_INFLUENCE_VCN, FALSE=IS_MAP_INFLUENCE_ANI)
	BOOL				bCreateFlag;			// �ʱ�ȭ �Ŀ� ��ȯ ���� �÷���
	BOOL				bInfluenceBoss;			// 2007-08-30 by dhjin, ������ ��������Ʈ ��ȯ���� üũ ��Ʈ 0 : FASLE, 1 : TRUE
	INT					SummonMonsterNum;		// 2013-08-14 by jhseol, ������ ������ - ������ ��ȯ�� ���͹�ȣ
};

struct MSG_FN_MONSTER_STRATEGYPOINT_SUMMON
{
	MapIndex_t			MapIndex;
	INT					SummonMonsterNum;		// 2013-08-14 by jhseol, ������ ������ - �Ϲ����� ��ȯ�� ���͹�ȣ
};

struct MSG_FN_MONSTER_OUTPOST_INIT
{// 2007-08-24 by dhjin, �������� �� ���� �ʱ�ȭ �� ������ �°� ���͸� ��ȯ�ؾ��� 
	MAP_CHANNEL_INDEX	mapChann;
	int					bell1;			// �⺻���� -1 �̾�� ��
	int					bell2;			// �⺻���� -1 �̾�� ��
	int					bell3;			// �⺻���� -1 �̾�� ��
};

struct MSG_FN_MONSTER_OUTPOST_RESET_SUMMON
{// 2007-08-24 by dhjin, �������� ���� ��ȯ, ����~!! ��ȣ���� �ı��� ���� ������ ��ȯ�ؾ��Ѵ�.
	MAP_CHANNEL_INDEX	mapChann;
	int					bell1;			// �⺻���� -1 �̾�� ��
};
typedef MSG_FN_MONSTER_OUTPOST_RESET_SUMMON		MSG_FN_MONSTER_TELEPORT_SUMMON;

struct MSG_MONSTER_SUMMON_BY_BELL
{// 2007-09-19 by cmkwon, ����ü �߰�
	int					MonsterBell;	// �⺻���� -1 �̾�� ��
};



struct MSG_FN_NPCSERVER_SUMMON_JACO_MONSTER		// 2006-04-18 by cmkwon
{
	BYTE			Belligerence0;				// 
	BOOL			IsSummonJacoMonster;		// 
};

struct MSG_FN_NPCSERVER_DELETE_MONSTER_IN_MAPCHANNEL		// TCP:F->N, // 2007-08-22 by cmkwon, �ش� ��ä�� ���� ��� �����ϱ� ��� �߰�
{
	MAP_CHANNEL_INDEX	mapChann;
	BOOL				bAllFlag;		// FALSE�� �ƴϸ� �Ʒ��� �ʵ�鿡 ������� ��� ���Ͱ� ������
	int					bell1;			// �⺻���� -1 �̾�� ��
	int					bell2;			// �⺻���� -1 �̾�� ��
	int					excludeBell1;	// �⺻���� -1 �̾�� ��
	int					excludeBell2;	// �⺻���� -1 �̾�� ��
	BOOL				bNotCreateMonster;	// ���� ���� ���� 0 => False 1 => True
};

struct MSG_FN_MONSTER_CREATE_IN_MAPCHANNEL_BYVALUE		// TCP:F->N, // 2007-08-29 by dhjin, �ش� ��ä�� ���� ��� ���������ϰ� ����
{
	MAP_CHANNEL_INDEX	mapChann;
};


typedef struct
{
	ChannelIndex_t	ChannelIndex;
	UINT			ItemNum;						// ���� ������ ����
	ClientIndex_t	MonsterIndex;					// ���� ������ �ε���
	INT				WeaponIndex;					// ���� ���� �ε���(���Ϳ� ���� ������)
	AVECTOR3		PositionVector;
	AVECTOR3		TargetVector;
} MSG_FN_MISSILE_MOVE;

typedef struct
{
	ChannelIndex_t	ChannelIndex;
	ClientIndex_t	MonsterIndex;
	UINT			RecoveryHP;
} MSG_FN_MONSTER_HPRECOVERY;


typedef struct
{
	ChannelIndex_t	ChannelIndex;
	ClientIndex_t	ClientIndex;
} MSG_FN_MONSTER_HIDE;
typedef MSG_FN_MONSTER_HIDE MSG_FN_MONSTER_SHOW;

///////////////////////////////////////////////////////////////////////////////
// FC_EVENT (Field server <-> Client)

// ���� Ÿ��: WARP_TYPE_XXX
#define WARP_TYPE_SAME_MAP				(BYTE)0x00	// ���� �������� ����
#define WARP_TYPE_SAME_FIELD_SERVER		(BYTE)0x01	// �ٸ� ��(���� �ʵ� ����)������ ����
#define WARP_TYPE_OTHER_FIELD_SERVER	(BYTE)0x02	// �ٸ� ��(�ٸ� �ʵ� ����)������ ����

typedef struct
{
	MAP_CHANNEL_INDEX	MapChannelIndex;
	SERVER_ID			FieldServerID;
	USHORT				WarpAreaIndex;
} MSG_FC_EVENT_WARP;			// F->C, �ٸ� �ʵ� ������ ������

typedef struct
{
	AVECTOR3			PositionVector;
	BYTE				CharacterMode0;		// 2005-07-27 by cmkwon
} MSG_FC_EVENT_WARP_SAME_MAP;				// F->C, ���� �ʵ� ���� & ���� ������ ������

typedef struct
{
	MAP_CHANNEL_INDEX	MapChannelIndex;
	BitFlag16_t			MapWeather;
	AVECTOR3			PositionVector;
	BYTE				CharacterMode0;		// 2005-07-27 by cmkwon
} MSG_FC_EVENT_WARP_SAME_FIELD_SERVER;		// F->C, ���� �ʵ� ���� & �ٸ� ������ ������

typedef struct
{
	ClientIndex_t		ClientIndex;
	MapIndex_t			WarpMapIndex;	// 2005-11-01 by cmkwon, �̵� �� MapIndex
} MSG_FC_EVENT_OTHER_WARPED;

typedef struct
{
	char	AccountName[SIZE_MAX_ACCOUNT_NAME];
	char	Password[SIZE_MAX_PASSWORD_MD5_STRING];		// MD5
	char	PrivateIP[SIZE_MAX_IPADDRESS];
	UID32_t	AccountUniqueNumber;
	UID32_t	CharacterUniqueNumber;
	UINT	PartyNumber;
	MAP_CHANNEL_INDEX	MapChannelIndex;
	USHORT	WarpAreaIndex;
} MSG_FC_EVENT_WARP_CONNECT;

typedef struct
{
	ClientIndex_t	ClientIndex;
	AVECTOR3		PositionVector;
	AVECTOR3		TargetVector;
	BitFlag16_t		MapWeather;
} MSG_FC_EVENT_WARP_CONNECT_OK;

typedef struct
{
	BUILDINGNPC		BuildingNPCInfo;
	// 2006-02-08 by cmkwon
	//	float			fCityWarTexRate;				//
	float			fInflDistributionTexPercent;	// 2006-02-08 by cmkwon, ���º��� ����
} MSG_FC_EVENT_ENTER_BUILDING;				// F->C

typedef struct
{
	UINT		BuildingIndex;
	BOOL		SendShopItemList;
} MSG_FC_EVENT_ENTER_BUILDING_OK;			// C->F

typedef struct
{
	UINT		BuildingIndex;
} MSG_FC_EVENT_LEAVE_BUILDING;				// C->F

typedef struct
{
	AVECTOR3	PositionVector;
	AVECTOR3	TargetVector;
} MSG_FC_EVENT_LEAVE_BUILDING_OK;			// F->C

typedef struct
{
	ClientIndex_t	ClientIndex;
} MSG_FC_EVENT_REQUEST_WARP;				// C->F, ��Ƽ�� ������ ��Ƽ�常 ��û ����, �������� ��û �Ұ�

typedef struct
{
	Err_t			Reason;
} MSG_FC_EVENT_REJECT_WARP;					// F->C, check: �ʿ��ϰ� �Ǹ� ��ü���� MSG ���� ���ϱ�!


//typedef struct
//{
//	INT				ObjectIndex;			// Object�� Index
//} MSG_FC_EVENT_REQUEST_OBJECT_EVENT;		// F->C, Object�� ���� Event�� ��û

typedef struct
{
	DWORD			ObjectType;
	AVECTOR3		ObjectPosition;
} MSG_FC_EVENT_REQUEST_OBJECT_EVENT;		// F->C, Object�� ���� Event�� ��û

typedef struct
{
	BitFlag16_t		MapWeather;
} MSG_FC_EVENT_CHANGE_WEATHER;

#define WEATHER_DEFAULT		(BitFlag16_t)0x0000	// �⺻
#define WEATHER_SUNNY		(BitFlag16_t)0x0001	// ����
#define WEATHER_RAINY		(BitFlag16_t)0x0002	// ��
#define WEATHER_SNOWY		(BitFlag16_t)0x0004	// ��
#define WEATHER_CLOUDY		(BitFlag16_t)0x0008	// �帲
#define WEATHER_FOGGY		(BitFlag16_t)0x0010	// �Ȱ�

struct MEX_CHANNEL_INFO {
	ChannelIndex_t	ChannelIndex;
	INT				Crowdedness;		// ȥ�⵵, 0% ~ 100%??, check: ��Ȯ�� ��� �����ؾ� ��
};

typedef struct {
	MapIndex_t		MapIndex;
	INT				WarpTargetIndex;	// Ŭ���̾�Ʈ�� �� ������ MSG_FC_EVENT_SELECT_CHANNEL�� �״�� �����ؼ� ������ �Ѱ��־�� ��
	INT				NumOfChannels;		// ���� ������ ä���� ��
	ARRAY_(MEX_CHANNEL_INFO);
} MSG_FC_EVENT_SUGGEST_CHANNELS;		// F->C, ���� ������ ä���� ������

typedef struct {
	ClientIndex_t		ClientIndex;
	INT					WarpTargetIndex;	// Ŭ���̾�Ʈ�� �� ������ MSG_FC_EVENT_SUGGEST_CHANNELS�κ��� �״�� �����ؼ� ������ �Ѱ��־�� ��
	MAP_CHANNEL_INDEX	MapChannelIndex;
} MSG_FC_EVENT_SELECT_CHANNEL;				// C->F, ������ ä���� ������

typedef struct {
	ClientIndex_t		ClientIndex;
	INT					WarpTargetIndex;	// Ŭ���̾�Ʈ�� �� ������ MSG_FC_EVENT_SUGGEST_CHANNELS�κ��� �״�� �����ؼ� ������ �Ѱ��־�� ��
	MAP_CHANNEL_INDEX	MapChannelIndex;
	int					nPartyMembers;		// ���� ������ ��Ƽ���� ��, ������ ����
	ARRAY_(UID32_t);						// ��Ƽ�� character uniquenumber�� array
} MSG_FC_EVENT_SELECT_CHANNEL_WITH_PARTY;	// C->F, ������ ä���� ������

typedef struct {
	ClientIndex_t		ClientIndex;
	MAP_CHANNEL_INDEX	MapChannelIndex;
} MSG_FC_EVENT_REQUEST_RACING_WARP;	// C->F, ���̸̽������� ���� ��û


typedef struct
{
	MAP_CHANNEL_INDEX	MapChannelIndex;
} MSG_FC_EVENT_GET_SHOP_WARP_TARGET_MAP_LIST;

struct WARP_TARGET_MAP_INFO_4_EXCHANGE
{
	MapIndex_t	MapIndex;
	INT			TargetIndex;	// EVENTINFO�� �����ϴ� TargetIndex
	char		TargetName[SIZE_MAX_WARP_TARGET_NAME];	// Ÿ���� �̸�(ex: ���û��, �����ϴ�)
	INT			Fee;			// ���� ���
};

typedef struct
{
	INT		NumOfTargetMaps;
	ARRAY_(WARP_TARGET_MAP_INFO_4_EXCHANGE);
} MSG_FC_EVENT_GET_SHOP_WARP_TARGET_MAP_LIST_OK;

typedef struct
{
	MapIndex_t	MapIndex;
	INT			TargetIndex;			// EVENTINFO�� �����ϴ� TargetIndex	
} MSG_FC_EVENT_REQUEST_SHOP_WARP;

struct MSG_FC_EVENT_CHARACTERMODE_ENTER_BUILDING
{
	INT			nBuildingIndex0;
};

struct MSG_FC_EVENT_CALL_WARP_EVENT_REQUEST			// 2006-07-21 by cmkwon
{
	DWORD				dwCallWarpEventID0;
	DWORD				dwSupportTermTick0;
	char				szUserMessage[SIZE_STRING_128];
};

struct MSG_FC_EVENT_CALL_WARP_EVENT_REQUEST_ACK		// 2006-07-21 by cmkwon
{
	DWORD				dwCallWarpEventID0;
};


///////////////////////////////////////////////////////////////////////////////
// FN_EVENT (Field server <-> NPC server)
typedef MSG_FC_EVENT_OTHER_WARPED	MSG_FN_EVENT_OTHER_WARPED;

///////////////////////////////////////////////////////////////////////////////
// FP_EVENT (Field server <-> Pre server)
typedef struct
{
	char			AccountName[SIZE_MAX_ACCOUNT_NAME];
	SERVER_ID		FieldServerID;
	UID32_t			CharacterUniqueNumber;
} MSG_FP_EVENT_NOTIFY_WARP;		// F --> P

typedef struct
{
	UID32_t			CharacterUniqueNumber;
} MSG_FP_EVENT_NOTIFY_WARP_OK;		// P --> F

typedef struct
{
	char			AccountName[SIZE_MAX_ACCOUNT_NAME];
} MSG_FP_EVENT_ENTER_SELECT_SCREEN;		// F->P, Client�� ĳ���� ���� â�� ����

typedef struct
{
	char				AccountName[SIZE_MAX_ACCOUNT_NAME];
	char				CharacterName[SIZE_MAX_CHARACTER_NAME];
	UID32_t				CharacterUniqueNumber;
	MAP_CHANNEL_INDEX	MapChannelIndex;
} MSG_FP_EVENT_GAME_STARTED;			// F->P, Client�� ������ ������(������ ����)

typedef struct
{
	char				AccountName[SIZE_MAX_ACCOUNT_NAME];
	char				CharacterName[SIZE_MAX_CHARACTER_NAME];
	UID32_t				CharacterUniqueNumber;
	MAP_CHANNEL_INDEX	MapChannelIndex;
} MSG_FP_EVENT_MAP_CHANGED;				// F->P, Client�� ���� �̵���

// T0_FP_MONITOR
typedef struct
{
	MGAME_EVENT_t		enMGameEvent;
} MSG_FP_MONITOR_SET_MGAME_EVENT_TYPE;



///////////////////////////////////////////////////////////////////////////////
// FC_STORE
typedef struct
{
	UID32_t	AccountUniqueNumber;
	UID32_t	PossessCharacter;		// CharacterUniqueNumber 
	BYTE	ItemStorage0;			// 0(ITEM_IN_CHARACTER):ĳ�����κ�, 1(ITEM_IN_STORE):â��
	BOOL	bSendToClient;			// Client�� �������� ����, WARP_CONNECT�ô� ���� ���ʿ�
	BOOL	bMainGameStartFlag;		// 2012-10-08 by khkim, GLog - ���ӽ��۽� ������ Ȯ���� ����
} MSG_FC_STORE_GET_ITEM;

typedef struct
{
	UID32_t	PossessCharacter;		// CharacterUniqueNumber
	BYTE	ItemStorage0;			// 2006-01-05 by cmkwon, 0(ITEM_IN_CHARACTER):ĳ�����κ�, 1(ITEM_IN_STORE):â��
} MSG_FC_STORE_PUT_ITEM_HEADER;

typedef struct
{
	int		BytesToRead;			// �ڿ� �ٴ� �������� �� ����Ʈ��, ���ǰ� �ʿ���
	ARRAY_(ITEM_XXX);
} MSG_FC_STORE_PUT_ITEM;

typedef struct
{
	UINT	NumOfItem;
	BYTE	ItemStorage0;			// 2006-01-05 by cmkwon, 0(ITEM_IN_CHARACTER):ĳ�����κ�, 1(ITEM_IN_STORE):â��
} MSG_FC_STORE_PUT_ITEM_DONE;

typedef struct						// 2012-06-05 by jhseol, ���۹̸����� - Ŭ���û ��Ŷ �߰�
{
	struct ItemEnahcntInfo
	{
		// 2013-01-24 by jhseol, ���۹̸����� ��Ŷ ������ �ʰ��� ���� ���� ����
		UID64_t		TargetItemUniqueNumber;
		INT			TargetItemNum;				// ��� �������� ItemNum
		INT			EnchantItemNum;				// enchant�� ���� �������� ItemNum
		// end 2013-01-24 by jhseol, ���۹̸����� ��Ŷ ������ �ʰ��� ���� ���� ����
		int			EnchantCount;
	};
	ItemEnahcntInfo ItemEnchant[6][8];
} MSG_FC_CHARACTER_GET_USER_ITEM_INFO_OK_DONE;

typedef struct
{
	UID64_t		ItemUniqueNumber;		// STORE Talbe�� �ε���, DB paramemter�� (STORE_ITEM*)��
	BYTE		FromItemStorage;		// 0(ITEM_IN_CHARACTER):ĳ�����κ�, 1(ITEM_IN_STORE):â��
	BYTE		ToItemStorage;			// 0(ITEM_IN_CHARACTER):â��->ĳ�����κ�, 1(ITEM_IN_STORE):ĳ�����κ�->â��
	INT			Count;					// ���� �������� ����
} MSG_FC_STORE_MOVE_ITEM;

typedef struct
{
	UID64_t		ItemUniqueNumber;
	UID32_t		FromPossessCharacter;	// CharacterUniqueNumber or 0
	UID32_t		ToPossessCharacter;		// CharacterUniqueNumber or 0
	INT			Count;					// ���� �������� ����
} MSG_FC_STORE_MOVE_ITEM_OK;

struct MSG_FC_STORE_LOG_GUILD_ITEM
{// 2006-09-27 by dhjin, C --> F ���� �α� ���� ��û
	UID32_t		AccountUID;
	UID32_t		CharacterUID;
};

struct MSG_FC_STORE_LOG_GUILD_ITEM_OK
{// 2006-09-27 by dhjin, F --> C ���� �α� ���� ����
	BYTE			LogType;
	ATUM_DATE_TIME	Time;
	UID32_t			CharacterUID;
	CHAR			CharacterName[SIZE_MAX_CHARACTER_NAME];
	INT				ItemNum;
	INT				PrefixCodeNum;
	INT				SuffixCodeNum;
	INT				ItemChangeCount;
};

// 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������
typedef struct
{
	INT				nBonusExpRate;
	UID32_t			CharacterUID; // 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������
} MSG_FI_GUILD_BONUS_EXP_RATE;
// 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������


// 2008-01-23 by cmkwon, S_F, S_L: ����/�������� ���� �α׿� �߰� - IDT_XXX, ITEM_DELETE_TYPE_XXX
#define IDT_GENERAL						((BYTE)0)	// �Ϲ� �뵵
#define IDT_EXPIRE_TIME					((BYTE)1)	// ��ȿ �ð�/�Ⱓ ���
#define IDT_INVALID_ITEMNUM				((BYTE)2)	// ��ȿ���� ���� ItemNum		// 2009-11-20 by cmkwon, ���� ������ �ε��� ��ȿ���� ���� ������ ó�� ���� - 
#define IDT_COUNTABLEITEM_ZERO			((BYTE)3)	// ī���ͺ� ������ Count 0		// 2009-11-20 by cmkwon, ���� ������ �ε��� ��ȿ���� ���� ������ ó�� ���� - 
#define IDT_MARKET						((BYTE)4)	// 2013-11-25 by jhseol&bckim, �ŷ��� - �ŷ��߰��� Ÿ�� �߰�


// IUT_XXX, ITEM_UPDATE_TYPE_XXX
#define IUT_GENERAL						((BYTE)0)	// �Ϲ� �뵵
#define IUT_DROP_ITEM					((BYTE)1)	// ��� ������
#define IUT_MIXING						((BYTE)2)	// ������ ����
#define IUT_TRADE						((BYTE)3)	// �ŷ�
#define IUT_SHOP						((BYTE)4)	// ���� ���� ������, �Ǹ� �ݾ� ��
#define IUT_QUEST						((BYTE)5)	// ����Ʈ�� ���� ����
#define IUT_ADMIN						((BYTE)6)	// ����, ���߿�
#define IUT_BULLET						((BYTE)7)	// �Ѿ� ������Ʈ
#define IUT_SKILL						((BYTE)8)	// ��ų ������
#define IUT_LOADING						((BYTE)9)	// ���� ���� �� �ε�
#define IUT_AUCTION						((BYTE)10)	// ��� ����
#define IUT_ENCHANT						((BYTE)11)	// ��æƮ
#define IUT_USE_ITEM					((BYTE)12)	// ������ ���
#define IUT_MGAME_EVENT					((BYTE)13)	// MGameEvent
#define IUT_USE_ENERGY					((BYTE)14)	// �������� ������ ���
#define IUT_EXPIRE_CARD_ITEM			((BYTE)15)	// �ð����� ������ ��� �ð� ����
#define IUT_PENALTY_ON_DEAD				((BYTE)16)	// ĳ���� ���� ���� �г�Ƽ
#define IUT_PENALTY_AGEAR_FUEL_ALLIN	((BYTE)17)	// ĳ���� ���� ���� �г�Ƽ
#define IUT_INFLUENCEWAR_KILLER_BONUS	((BYTE)18)	// ���������� ų�� ���ʽ�
#define IUT_BONUS_ITEM					((BYTE)19)	// 2006-04-26 by cmkwon, ���ʽ� ������
#define IUT_BAZAAR_SELL					((BYTE)20)	// ���� �Ǹ� ���� �ŷ�
#define IUT_BAZAAR_BUY					((BYTE)21)	// ���� ���� ���� �ŷ�
#define IUT_RANDOMBOX					((BYTE)22)	// 2006-08-10 by cmkwon, �����ڽ� ���
#define IUT_GIVEEVENTITEM				((BYTE)23)	// 2006-08-25 by dhjin, �̺�Ʈ ������ ���
#define IUT_GUILD_STORE					((BYTE)24)	// 2006-09-25 by cmkwon, ���� â��
#define IUT_EXPIRE_ITEM					((BYTE)25)	// 2006-09-29 by cmkwon, ������ ����
#define IUT_STORE						((BYTE)26)	// 2006-10-26 by cmkwon, â�� �̿�
#define IUT_STORE_FEE					((BYTE)27)	// 2006-10-26 by cmkwon, â�� �̿��
#define IUT_ARENA_ITEM					((BYTE)28)	// 2007-06-04 by dhjin, �Ʒ��� ���� ������
#define IUT_TUTORIAL_PAY_ITEM			((BYTE)29)	// 2007-07-24 by dhjin, Tutorial ���� ������
#define IUT_EXPEDIENCYFUND_PAYBACK		((BYTE)30)	// 2007-08-22 by dhjin, �ǰ��� ȯ��
#define IUT_GIVEEVENTITEM_COUPONEVENT	((BYTE)31)	// 2008-01-10 by cmkwon, ������ �̺�Ʈ �ý��ۿ� �� ���� �ý��� �߰� - 
#define IUT_LUCKY_ITEM					((BYTE)32)	// 2008-11-10 by dhjin, ��Ű�ӽ�
#define IUT_WAR_CONTRIBUTION			((BYTE)33)	// 2008-12-23 by dhjin, ���� ���� �߰���
#define IUT_WAR_CONTRIBUTION_LEADER		((BYTE)34)	// 2008-12-23 by dhjin, ���� ���� �߰��� - ������
#define IUT_WAR_CONTRIBUTION_GUILD		((BYTE)35)	// 2008-12-23 by dhjin, ���� ���� �߰��� - ���
#define IUT_DISSOLUTION_ITEM			((BYTE)36)	// 2010-08-31 by shcho&jskim �����ۿ��� �ý��� - ���� �ý��� ��Ŷ ó��
#define IUT_DEPENDENCY_ITEM				((BYTE)37)	// 2011-09-20 by hskim, ��Ʈ�� �ý��� 2�� - ������ ������ ó�� (�� ������ ���� ������ ���� ����)
#define IUT_WARP						((BYTE)38)	// 2011-10-28 by hskim, EP4 [Ʈ���� �ý���] - ũ����Ż �ý��� - ���� ���� ���ǿ� ���� ������ ����
#define IUT_MARKET						((BYTE)42)	// 2013-11-25 by jhseol&bckim, �ŷ��� - �ŷ��߰��� Ÿ�� �߰�

// start 2012-11-21 by khkim, GLog 2��
#define GLOG_WARPOINTSHOP				((BYTE)39)	// ���� ���� 
#define GLOG_INFINITYOBSHOP				((BYTE)40)	// ����	����
#define GLOG_CASHSHOP					((BYTE)41)	// ĳ�� ����
#define GLOG_DEFAULT_ZERO				((BYTE)0) 	// ����Ʈ 0�� ����
// end 2012-11-21 by khkim, GLog 2��

#define IUT_CITYWAR_BRING_SUMOFTEX		((BYTE)100)	// ���������� ����

typedef struct
{
	UID32_t			FromCharacterUniqueNumber;		// From Possess, Ȥ�� FromCharacterUniqueNumber
	BYTE			ItemInsertionType;				// ������ ���� Ÿ��, IUT_XXX
	ITEM_GENERAL	ItemGeneral;
} MSG_FC_STORE_INSERT_ITEM;

typedef struct
{
	UID64_t			ItemUniqueNumber;	// ���� ������
	BYTE			ItemDeletionType;	// ������ ���� Ÿ��, IUT_XXX
} MSG_FC_STORE_DELETE_ITEM;

typedef struct
{
	UID64_t			ItemUniqueNumber;	// Update�� ������
	INT				NewCount;			// Count�� �� ��
	BYTE			ItemUpdateType;		// ������ ���� Ÿ��, IUT_XXX
} MSG_FC_STORE_UPDATE_ITEM_COUNT;

typedef struct
{
	UID64_t			ItemUniqueNumber;
	float			Endurance;
} MSG_FC_STORE_UPDATE_ENDURANCE;

typedef struct
{
	UID64_t			ItemUniqueNumber;
	UID32_t			FromPossess;
	UID32_t			ToPossess;
} MSG_FC_STORE_UPDATE_POSSESS;

typedef struct
{
	UID64_t	ItemUID;
	INT		PrefixCodeNum;	// ���λ�, ������ 0
	INT		SuffixCodeNum;	// ���̻�, ������ 0
} MSG_FC_STORE_UPDATE_RARE_FIX;

struct MSG_FC_STORE_INSERT_USINGITEM
{
	INT				ItemNum;
	UID64_t			ItemUID;						// 2006-04-24 by cmkwon
	BYTE			ItemInsertionType;				// ������ ���� Ÿ��, IUT_XXX
	INT				nRemainSecond;
};

struct MSG_FC_STORE_DELETE_USINGITEM
{
	INT				ItemNum;
	BYTE			ItemDeletionType;	// ������ ���� Ÿ��, IUT_XXX
};

struct MSG_FC_STORE_UPDATE_USINGITEM
{
	UID64_t			ItemUID0;
	INT				UsingTimeStamp0;	// ���ݱ��� ���� �ð�(����:��)
};

struct MSG_FC_STORE_EXPIRE_USINGITEM		// 2006-10-11 by cmkwon
{
	UID64_t			ItemUID0;
};

struct MSG_FC_STORE_UPDATE_ITEMSTORAGE
{
	//	UID32_t			PossessCharacter;		// 2006-09-18 by dhjin, ���õ� �ɸ���
	UID64_t			ItemUniqueNumber;
	UID32_t			FromItemStorage;
	UID32_t			ToItemStorage;
};

struct MSG_FC_STORE_UPDATE_ITEMNUM		// 2006-06-14 by cmkwon
{
	UID64_t			ItemUniqueNumber;
	INT				ItemNum;
	BYTE			ItemUpdateType;		// ������ ���� Ÿ��, IUT_XXX
};

///////////////////////////////////////////////////////////////////////////////
// 2006-09-04 by dhjin, �� ���� ���� 
#define QUICKTABCOUNT		3
#define QUICKSLOTCOUNT		10			// 2008-06-19 by dhjin, EP3 - 8 -> 10���� ����  

struct SQUICKSLOT_INFO
{
	BOOL		Delete;
	int			arrItemNum_[QUICKSLOTCOUNT];
};

struct MSG_FC_STORE_REQUEST_QUICKSLOT_OK
{
	SQUICKSLOT_INFO		POS[QUICKTABCOUNT];
};

struct MSG_FC_STORE_SAVE_QUICKSLOT
{
	SQUICKSLOT_INFO		POS[QUICKTABCOUNT];
	int					SlotPurpose;	// 2012-06-21 by jhseol, �Ʒ��� �߰�����part2 - �Ʒ��� ���� ������
};

///////////////////////////////////////////////////////////////////////////////
// FC_ITEM
typedef struct
{
	UINT			ItemFieldIndex;				// ���� ������ ������ �ӽ÷� �����ϴ� ��ȣ
	INT				ItemNum;					// Ŭ���̾�Ʈ�� �������� ������ �����ֱ� ���� ����
	UID32_t			FirstCharacterUID;			// ������ ���� ������ ù��° ĳ����
	INT				Amount;						// �������� ����
	AVECTOR3		Position;
	BYTE			DropItemType;				// ������ �������� ����(����� ������, ���ݿ�(���η�) ������ ���)
} MSG_FC_ITEM_SHOW_ITEM;

#define DROP_ITEM_TYPE_PICKUP		(BYTE)0x00		// ����� ������
#define DROP_ITEM_TYPE_ATTACK_MINE	(BYTE)0x01		// ���ݿ� ���η� ������

typedef struct
{
	UINT			ItemFieldIndex;				// ���� ������ ������ �ӽ÷� �����ϴ� ��ȣ
	ClientIndex_t	ClientIndex;				// �������� ���� character�� client index
} MSG_FC_ITEM_HIDE_ITEM;

typedef struct
{
	ClientIndex_t	ClientIndex;
	UINT			ItemFieldIndex;					// ���� ������ ������ �ӽ÷� �����ϴ� ��ȣ
} MSG_FC_ITEM_GET_ITEM;

typedef struct
{
	ClientIndex_t	ClientIndex;
	UINT			ItemFieldIndex;				// ���� ������ ������ �ӽ÷� �����ϴ� ��ȣ
	INT				ItemNum;					// �������� ����
	INT				Amount;						// �������� ����
	INT				SizeOfItem;					// sizeof(�ش�Item)
	ARRAY_(ITEM_XXX);							// ITEM_XXX�� �´�
} MSG_FC_ITEM_GET_ITEM_OK;

typedef struct
{
	ClientIndex_t	ClientIndex;
	UINT			ItemFieldIndex;				// ���� ������ ������ �ӽ÷� �����ϴ� ��ȣ
} MSG_FC_ITEM_GET_ITEM_FAIL;

typedef struct
{
	UINT			ItemFieldIndex;				// ���� ������ ������ �ӽ÷� �����ϴ� ��ȣ
	STRUCT_(ITEM_XXX);							// ���Ŀ� �ش� ITEM_XXXX�� �´�
} MSG_FC_ITEM_PUT_ITEM;

// 2005-11-15 by cmkwon, ������
//typedef struct
//{
//	ClientIndex_t	ClientIndex;
//	BYTE			KindOfSkill;				// check: �ǹ� �ľ� �� �̸� ���� �ʿ�
//} MSG_FC_ITEM_BONUSSKILLPOINT;
//
//typedef struct
//{
//	ClientIndex_t	ClientIndex;
//	BYTE			OldKindOfSkill;				// check: �ǹ� �ľ� �� �̸� ���� �ʿ�
//	BYTE			NewKindOfSkill;				// check: �ǹ� �ľ� �� �̸� ���� �ʿ�
//	BYTE			RemainedAmountOfSkill;		// check: ���� type Ȯ���ؾ� ��!
//} MSG_FC_ITEM_BONUSSKILLPOINT_OK;

typedef struct
{
	UID32_t			CharacterUniqueNumber;
	UID64_t			FromItemUniqueNumber;	// ���� ������ �̵��� ������
	INT				FromItemWindowIndex;	// ���� ������ �̵��� �������� ���� ��ġ
	UID64_t			ToItemUniqueNumber;		// �̵� ��ġ(destination)�� ��� �ִ� ������(�����Ѵٸ�), ���ٸ� 0
	INT				ToItemWindowIndex;		// �̵� ��ġ(destination)�� ItemWindowIndex
} MSG_FC_ITEM_CHANGE_WINDOW_POSITION;

typedef struct
{
	UID64_t			UniqueNumber;			// ���� ������ �̵��� ������
	INT				ItemWindowIndex;		// ���� ������ �̵��� �������� �� ��ġ
	BYTE			Wear;					// ���� ������ �̵��� �������� wear ����
	UID64_t			UniqueNumberDest;		// �̵� ��ġ(destination)�� ��� �ִ� ���� ������(�����Ѵٸ�), ���ٸ� 0
	INT				ItemWindowIndexDest;	// �̵� ��ġ(destination)�� ��� �ִ� ���� �������� �� ��ġ(�����Ѵٸ�), ���ٸ� POS_INVALID_POSITION
	BYTE			WearDest;				// �̵� ��ġ(destination)�� ��� �ִ� ���� ������ wear ����(�����Ѵٸ�), ���ٸ� 0
} MSG_FC_ITEM_CHANGE_WINDOW_POSITION_OK;

// start 2011-09-20 by hskim, ��Ʈ�� �ý��� 2��
typedef struct
{
	UID64_t			UniqueNumber;			// ������ �̵��� ������
	INT				ItemWindowIndex;		// ������ �̵��� �������� ��ġ
	BYTE			Wear;					// ������ �̵��� �������� wear ����

	// �������� �� �޽��� ���� CalcInventoryHiddenItemCounts() �Լ��� �� ȣ�����־���� (������ ������ ���� ����)

} MSG_FC_ITEM_NOTIFY_WINDOW_POSITION;		// F -> C, �������� ItemWindowIndex ����ɽÿ� Ŭ���̾�Ʈ���� �˷��ش�
// end 2011-09-20 by hskim, ��Ʈ�� �ý��� 2��

typedef struct
{
	INT				NumOfItems;
	ARRAY_(ITEM_WINDOW_INFO);
} MSG_FC_ITEM_UPDATE_WINDOW_ITEM_LIST;

typedef struct
{
	UID64_t			ItemUniqueNumber;
	BYTE			ItemKind;
	BYTE			Wear;
	INT				ItemWindowIndex;
} ITEM_WINDOW_INFO;

typedef struct
{
	ClientIndex_t	ClientIndex;
	UID64_t			ItemUniqueNumber;
	INT				Amount;					// ������ ����
} MSG_FC_ITEM_THROW_AWAY_ITEM;

typedef struct
{
	ClientIndex_t	ClientIndex;
	UID64_t			ItemUniqueNumber;
	INT				RemainedNumOfItem;		// ���� �� �����ִ� ����. 0 �̸� ������ ������.
} MSG_FC_ITEM_THROW_AWAY_ITEM_OK;

typedef struct
{
	ClientIndex_t	ClientIndex;
	UID64_t			ItemUniqueNumber;
	INT				nParam1;				//
} MSG_FC_ITEM_USE_ENERGY;
struct MSG_FC_ITEM_USE_ENERGY_OK
{
	ClientIndex_t	ClientIndex;
	INT				ItemNum;
};

struct MSG_FC_ITEM_USE_ITEM
{
	ClientIndex_t	ClientIndex;
	UID64_t			ItemUniqueNumber;
	char			str256ChatMsg[SIZE_MAX_STRING_256];		// 2007-08-09 by cmkwon, ��� ���¿� ä�� �����ϱ� - 
};
struct MSG_FC_ITEM_USE_ITEM_OK
{
	ClientIndex_t	ClientIndex;
	INT				ItemNum;
};

typedef struct
{
	UINT			ItemFieldIndex;	// ���� ������ ������ �ӽ÷� �����ϴ� ��ȣ
	AVECTOR3		DropPosition;	// �������� ��ġ
} MSG_FC_ITEM_DELETE_ITEM_ADMIN;

typedef struct
{
	UINT			ItemFieldIndex;	// ���� ������ ������ �ӽ÷� �����ϴ� ��ȣ
	AVECTOR3		DropPosition;	// ������(����)�� ��ġ
} MSG_FC_ITEM_DELETE_DROP_ITEM;		// F->C, �ڽ��� �Ѹ� ������(���ε�)�� ���� �� ����

typedef struct {
	ClientIndex_t	ClientIndex;
	BYTE			ItemPosition;	// POS_XXX
	INT				ItemNum;
	// 2009-08-26 by cmkwon, �׷��� ���ҽ� ���� �ý��� ���� - ����
	//	INT				ColorCode;		// 2005-12-08 by cmkwon, �Ƹ� ���� Ʃ�� ����
	INT				nShapeItemNum;		// 2009-08-26 by cmkwon, �׷��� ���ҽ� ���� �ý��� ���� - 
	INT				nEffectItemNum;		// 2009-08-26 by cmkwon, �׷��� ���ҽ� ���� �ý��� ���� - 
	INT				nPetLevel;		// 2012-12-05 by hskim, ��Ʈ�� �Ⱓ�� ���� ����
} MSG_FC_ITEM_UPDATE_ITEM_POS;		// F->C, ������ ����(��)�� ������, ������ ������ �ٲٸ� ������ ������

typedef struct
{
	UID64_t			EnchantItemUniqueNumber;	// ��æƮ ������
	UID64_t			TargetItemUniqueNumber;		// ��æƮ�� �ٸ� ��� ������
	UID64_t			AttachItemUniqueNumber;		// �߰� ������
	UID64_t			IncreaseProbabilityItemUID;	// 2009-01-19 by dhjin, ��þƮ Ȯ�� ����, 10��þ �Ĺ� ī�� - ��þƮ Ȯ�� ���� ī��
	UID64_t			EnchantItemUniqueNumber2;	// ��æƮ ������2 // 2010-04-20 by cmkwon, �ű� ��Ű �ӽ� ���� - SuffixCard ItemUID 
} MSG_FC_ITEM_USE_ENCHANT;

typedef struct
{
	// 2010-04-20 by cmkwon, �ű� ��Ű �ӽ� ���� - (�����κ��߰�) - 
	//INT				ItemNum;					// ��æƮ ������
	INT				EnchantItemNum;			// 2010-04-20 by cmkwon, �ű� ��Ű �ӽ� ���� - (�����κ��߰�) - 
	INT				SuffixRareItemNum;		// 2010-04-20 by cmkwon, �ű� ��Ű �ӽ� ���� - (�����κ��߰�) - 
	BOOL			bSuccessFlag;			// 2010-04-20 by cmkwon, �ű� ��Ű �ӽ� ���� - (�����κ��߰�) - 
} MSG_FC_ITEM_USE_ENCHANT_OK;					// ��æƮ �ϷḦ ����

typedef struct
{
	ENCHANT			Enchant;
} MSG_FC_ITEM_PUT_ENCHANT;

struct MSG_FC_ITEM_DELETE_ALL_ENCHANT
{
	UID64_t			ItemUniqueNumber;			// ��æƮ�� ������ ������	
};

typedef struct
{
	INT				NumOfItems;
	INT				nMixCounts;		// 2008-03-17 by cmkwon, ���� �ý��� ��� �߰� - 
	ARRAY_(ITEM_UNIQUE_NUMBER_W_COUNT);
} MSG_FC_ITEM_MIX_ITEMS;		// C->F, ������ �������� ����Ʈ�� ����

typedef struct
{
	Err_t			Err;		// ERR_XXX, ERROR_NO_ERROR�̸� ����
} MSG_FC_ITEM_MIX_ITEMS_RESULT;	// F->C, ������ ���� ����� ����

struct MSG_FC_ITEM_USE_CARDITEM_GUILDSUMMON
{
	UID64_t			ItemUniqueNumber;
	char			szCharacterName10[SIZE_MAX_CHARACTER_NAME];
};
struct MSG_FC_ITEM_USE_CARDITEM_GUILDSUMMON_NOTIFY
{
	ClientIndex_t	guildSummonClientIdx;
};

struct MSG_FC_ITEM_USE_CARDITEM_RESTORE
{
	UID64_t			ItemUniqueNumber;
	char			szCharacterName10[SIZE_MAX_CHARACTER_NAME];
};
struct MSG_FC_ITEM_USE_CARDITEM_RESTORE_NOTIFY
{
	ClientIndex_t	restoreClientIdx;
};

struct MSG_FC_ITEM_USE_CARDITEM_GUILD
{
	UID64_t			ItemUniqueNumber;
};
struct MSG_FC_ITEM_USE_CARDITEM_GUILD_NOTIFY
{
	ClientIndex_t	notifyClientIdx;
	UID32_t			guildUID;
};
struct MSG_FC_ITEM_USE_CARDITEM_MONSTERSUMMON
{
	UID64_t			ItemUniqueNumber;
};
struct MSG_FC_ITEM_USE_CARDITEM_MONSTERSUMMON_NOTIFY
{
	ClientIndex_t	notifyClientIdx;
	INT				notifyItemNum;
	INT				summonMonsterUnitKind;
};
struct MSG_FC_ITEM_USE_CARDITEM_CHANGECHARACTERNAME
{
	UID64_t			ItemUniqueNumber;
	char			szChangeCharacterName[SIZE_MAX_CHARACTER_NAME];
};
struct MSG_FC_ITEM_USE_CARDITEM_CHANGECHARACTERNAME_NOTIFY
{
	ClientIndex_t	notifyClientIdx;
	char			szChangedCharacterName[SIZE_MAX_CHARACTER_NAME];
	char			szOriginCharacterName[SIZE_MAX_CHARACTER_NAME];
};
struct MSG_FC_ITEM_USE_CARDITEM_SKILLINITIALIZE
{
	UID64_t			ItemUniqueNumber;
	INT				skillItemNum;
};
struct MSG_FC_ITEM_USE_CARDITEM_SKILLINITIALIZE_NOTIFY
{
	ClientIndex_t	notifyClientIdx;
	INT				notifyItemNum;
};
struct MSG_FC_ITEM_USE_CARDITEM_CHANGEPILOTFACE
{
	UID64_t			ItemUniqueNumber;
	BYTE			pilotFace;
};
struct MSG_FC_ITEM_USE_CARDITEM_CHANGEPILOTFACE_NOTIFY
{
	ClientIndex_t	notifyClientIdx;
	INT				notifyItemNum;
	BYTE			pilotFace;
};

struct MSG_FC_ITEM_USE_INFLUENCE_BUFF				// 2006-04-21 by cmkwon
{
	UID64_t			ItemUniqueNumber;
};
struct MSG_FC_ITEM_USE_INFLUENCE_BUFF_OK			// 2006-04-21 by cmkwon
{
	// 2009-01-05 by dhjin, �̼Ǹ����� - ���� ���� ������ �߰� - �ذ� ���� ����
	//	UID64_t			ItemUniqueNumber;
	char			ItemUseCharacterName[SIZE_MAX_CHARACTER_NAME];
	INT				ItemNum;
};
struct MSG_FC_ITEM_USE_INFLUENCE_GAMEEVENT			// 2006-04-21 by cmkwon
{
	UID64_t			ItemUniqueNumber;
};
struct MSG_FC_ITEM_USE_INFLUENCE_GAMEEVENT_OK		// 2006-04-21 by cmkwon
{
	UID64_t			ItemUniqueNumber;
};


// 2014-06-10 by bckim, ���º��� ������
struct MSG_FC_ITEM_USE_CARDITEM_CHANGE_INFLUENCE
{
	UID64_t			ItemUniqueNumber;
	BYTE			InfluenceType;
};
struct MSG_FC_ITEM_USE_CARDITEM_CHANGE_INFLUENCE_NOTIFY
{
	UID64_t			ItemUniqueNumber;
	BYTE			InfluenceType;
};
// End. 2014-06-10 by bckim, ���º��� ������


// 2006-08-10 by cmkwon
#define RANDOMBOX_RESULT_FAIL				0		// ����
#define RANDOMBOX_RESULT_ITEM				1		// ������
#define RANDOMBOX_RESULT_SPI				2		// Money(SPI)
#define RANDOMBOX_RESULT_EXP				3		// ����ġ
#define RANDOMBOX_RESULT_SKILL_SUPPORT_ITEM	4		// ��ų ���� ������, 2006-09-29 by cmkwon �߰���, ITEM_ATTR_SKILL_SUPPORT_ITEM
#define RANDOMBOX_RESULT_KIND_COUNT			5		// �����ڽ� ��� ���� ����

struct MSG_FC_ITEM_USE_RANDOMBOX		// 2006-08-10 by cmkwon
{
	UID64_t			ItemUID;
};
struct MSG_FC_ITEM_USE_RANDOMBOX_OK		// 2006-08-10 by cmkwon
{
	char			szCharacterName0[SIZE_MAX_CHARACTER_NAME];	// ����� CharacterName
	INT				nRandomBoxResult;							// RANDOMBOX_RESULT_XXX
	INT				nResultItemNum0;							// ������ ItemNum
	INT64			n64ResultCounts;							//
	INT				nPrefixCodeNum0;							// ���λ�, ������ 0
	INT				nSuffixCodeNum0;							// ���̻�, ������ 0
};

typedef MSG_FC_ITEM_USE_ITEM			MSG_FC_ITEM_USE_SKILL_SUPPORT_ITEM;		// 2006-09-29 by cmkwon
typedef MSG_FC_ITEM_USE_ITEM_OK			MSG_FC_ITEM_USE_SKILL_SUPPORT_ITEM_OK;	// 2006-09-29 by cmkwon

///////////////////////////////////////////////////////////////////////////////////////
// start 2011-09-20 by hskim, ��Ʈ�� �ý��� 2��

struct MSG_FC_ITEM_USE_PET_SOCKET_ITEM
{
	ClientIndex_t	ClientIndex;
	UID64_t			ItemUniqueNumber;
};

struct MSG_FC_ITEM_USE_PET_SOCKET_ITEM_OK
{
	ClientIndex_t	ClientIndex;
	UID64_t			ItemUniqueNumber;
};

struct MSG_FC_ITEM_CANCEL_PET_SOCKET_ITEM
{
	ClientIndex_t	ClientIndex;
	UID64_t			ItemUniqueNumber;
};

struct MSG_FC_ITEM_CANCEL_PET_SOCKET_ITEM_OK
{
	ClientIndex_t	ClientIndex;
	UID64_t			ItemUniqueNumber;
};

// end 2011-09-20 by hskim, ��Ʈ�� �ý��� 2��
///////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// 2008-11-04 by dhjin, ��Ű�ӽ�
// 2009-03-03 by dhjin, ��Ű�ӽ� ������ - �ذ� ���� ����
// typedef MSG_FC_ITEM_USE_RANDOMBOX		MSG_FC_ITEM_USE_LUCKY_ITEM;
struct MSG_FC_ITEM_USE_LUCKY_ITEM
{
	UID64_t			ItemUID;
	INT				MachineNum;
};

struct LUCKY_ITEM_SIMPLEINFO
{
	SHORT			SlotNum;
	INT				MysteryItemDropNum;
	INT				Itemnum;
	INT64			n64ResultCounts;							//
	INT				nPrefixCodeNum0;							// ���λ�, ������ 0
	INT				nSuffixCodeNum0;							// ���̻�, ������ 0
};

struct MSG_FC_ITEM_USE_LUCKY_ITEM_OK
{
	LUCKY_ITEM_SIMPLEINFO	LuckyItemSimpleInfo[MaxPayLuckyMachineItem];
};


struct MSG_FC_ITEM_CHANGED_SHAPEITEMNUM			// 2009-08-26 by cmkwon, �׷��� ���ҽ� ���� �ý��� ���� - 
{
	UINT64				nItemUID;
	INT					nShapeItemNum;

	FIXED_TERM_INFO		FixedTermShape;			// 2012-10-10 by hskim, �Ⱓ�� �Ӽ� ���� (�Ⱓ�� ����)
};

struct MSG_FC_ITEM_CHANGED_EFFECTITEMNUM		// 2009-08-26 by cmkwon, �׷��� ���ҽ� ���� �ý��� ���� - 
{
	UINT64			nItemUID;
	INT				nEffectItemNum;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// FC_SHOP
typedef struct
{
	UINT		BuildingIndex;
} MSG_FC_SHOP_PUT_ITEM_HEADER;

typedef struct
{
	USHORT		BytesToRead;			// �ڿ� �ٴ� �����۵��� �� ����Ʈ��
	ARRAY_(SHOP_ITEM);
} MSG_FC_SHOP_PUT_ITEM;

#define UNLIMITED_REMAIN_COUNT_FOR_LIMITED_EDITION		-1		// 2010-01-26 by cmkwon, ĳ�� ������ �����Ǹ� �ý��� ���� - 
#define SOLD_OUT_REMAIN_COUNT_FOR_LIMITED_EDITION		0		// 2010-01-26 by cmkwon, ĳ�� ������ �����Ǹ� �ý��� ���� - 

struct SHOP_ITEM
{
	UINT		ItemNum;
	char		ItemName[SIZE_MAX_ITEM_NAME];
	USHORT		MinTradeQuantity;
	INT			Price;
	BYTE		ItemKind;
	BYTE		CashShopIndex;		// 2009-01-28 by cmkwon, ĳ���� ����(��õ��,�Ż�ǰ �߰�) - SHOP_ITEM�� �߰�, ���� 4��Ʈ�� ���ε���, ���� 4��Ʈ�� ��Ʈ �÷��׷� ���
	INT			RemainCountForLimitedEdition;		// 2010-01-26 by cmkwon, ĳ�� ������ �����Ǹ� �ý��� ���� - 
	INT			RecommandedIdx;						// 2013-09-24 by bckim, ĳ�ü� ��õ�� ���ļ����ο� ����

	// 2010-01-26 by cmkwon, ĳ�� ������ �����Ǹ� �ý��� ���� - ��������
	BOOL IsSoldOutShopItem(void)
	{
		if (SOLD_OUT_REMAIN_COUNT_FOR_LIMITED_EDITION != RemainCountForLimitedEdition)
		{
			return FALSE;
		}
		return TRUE;
	}
	BOOL IsLimitedEditionShopItem(void)
	{
		if (SOLD_OUT_REMAIN_COUNT_FOR_LIMITED_EDITION > RemainCountForLimitedEdition)
		{
			return FALSE;
		}
		return TRUE;
	}

	// start 2011-10-28 by hskim, EP4 [Ʈ���� �ý���] - ũ����Ż �ý���

	// ���� �߰��Ǵ°� ���θ� �� �� �ִ� 1ȸ�� ������ ���� �Ǹ� ���(DB ������ �ʿ����)�� �� (ũ����Ż �ý���)
	// ���� ���� ����� ���ÿ� ����ϴ� ���� �Ǹ� ����� �ʿ��ϴٸ� ����ȭ �� �߰� ����� ������

	BOOL IsAvailableShopItem(int Amount)
	{
		if (UNLIMITED_REMAIN_COUNT_FOR_LIMITED_EDITION == RemainCountForLimitedEdition)
		{
			return TRUE;
		}

		if (Amount <= RemainCountForLimitedEdition)
		{
			return TRUE;
		}

		return FALSE;
	}
	// end 2011-10-28 by hskim, EP4 [Ʈ���� �ý���] - ũ����Ż �ý���
};

typedef struct
{
	UINT		NumOfItem;
} MSG_FC_SHOP_PUT_ITEM_DONE;

typedef struct
{
	INT			ItemNum;
} MSG_FC_SHOP_GET_ITEMINFO;

typedef struct
{
	ITEM		ItemInfo;
} MSG_FC_SHOP_GET_ITEMINFO_OK;

typedef struct
{
	UINT		BuildingIndex;
	UINT		ItemNum;
	INT			Amount;					// ������ �������� ����
} MSG_FC_SHOP_BUY_ITEM;

typedef struct
{
	INT			RemainedMoney;			// ���� �� ���� ��
	INT			SizeOfItem;				// sizeof(�ش�Item)�� ����
	ARRAY_(ITEM_XXX);						// ITEM_XXX�� �´�
} MSG_FC_SHOP_BUY_ITEM_OK;

// 2013-03-13 by hskim, �� ĳ�� ����
#define T_FC_SHOP_AUTH_KEY		(MessageType_t)((T0_FC_SHOP<<8)|T1_FC_CHARACTER_XIGNCODE_S_ACK_PACKET)

struct MSG_FC_SHOP_AUTH_KEY
{
	char AuthenticationKey[SIZE_MAX_WEB_AUTHENTICATION_KEY];
	INT ServerID;
};
// end 2013-03-13 by hskim, �� ĳ�� ����

// 2011-12-26 by hskim, EP4 [Ʈ���� �ý���] - ũ����Ż �ý���
struct MSG_FC_SHOP_BUY_ITEM_UPDATE
{
	UINT		BuildingIndex;
	UINT		ItemNum;
	INT			RemainCountForLimitedEdition;
};
// 2011-12-26 by hskim, EP4 [Ʈ���� �ý���] - ũ����Ż �ý���

typedef struct
{
	UINT		BuildingIndex;
	UID64_t		ItemUniqueNumber;
	BYTE		ItemKind;
	INT			Amount;					// �Ǹ��� �������� ����
} MSG_FC_SHOP_SELL_ITEM;

typedef struct
{
	UID64_t		ItemUniqueNumber;
	INT			RemainedNumOfItem;		// �Ǹ� �� ���� �ִ� ����(0�̸� ����, Countable Item �� ��� �ǹ� ����)
	INT			RemainedMoney;			// �Ǹ� �� ���� ��
} MSG_FC_SHOP_SELL_ITEM_OK;

typedef struct
{
	UID64_t		ItemUniqueNumber;
	INT			Amount;
} MSG_FC_SHOP_GET_USED_ITEM_PRICE;

typedef struct
{
	UID64_t		ItemUniqueNumber;
	UINT		Price;
} MSG_FC_SHOP_GET_USED_ITEM_PRICE_OK;

typedef struct
{
	INT			BuildingIndex;
} MSG_FC_SHOP_GET_SHOP_ITEM_LIST;	// C->F, �������� �Ĵ� �������� ����Ʈ�� ��û, ������ T_FC_SHOP_PUT_ITEM_XXX

typedef struct
{
	INT			DesParam;			// ������ �κ�(DES_HP, DES_DP, DES_EP, DES_SP, DES_BULLET_01, DES_BULLET_02)
	INT			Count;				// ��� �縸ŭ ������ ������
} MSG_FC_SHOP_REQUEST_REPAIR;		// C->F, ��ü ���� ��û

struct MSG_FC_SHOP_REQUEST_REPAIR_OK
{
	INT			DesParam;			// ������ �κ�(DES_HP, DES_DP, DES_EP, DES_SP, DES_BULLET_01, DES_BULLET_02)
	INT			Count;				// ������ ��
	INT			RepairCost;			// ���� ���
};

struct MSG_FC_SHOP_BUY_CASH_ITEM
{
	UINT		BuildingIndex;
	UINT		ItemNum;
	INT			Amount;					// ������ �������� ����
	UID32_t		GiveTargetCharacterUID;	// 2007-11-13 by cmkwon, �����ϱ� ��� �߰� - 0 �̸� �ڽ��� ����, 0�� �ƴϸ� �ش� ĳ���Ϳ��� �����ϱ�
};
struct MSG_FC_SHOP_BUY_CASH_ITEM_OK
{// 2007-11-13 by cmkwon, �����ϱ� ��� �߰� - MSG_FC_SHOP_BUY_CASH_ITEM_OK ����ü �߰�
	UINT		ItemNum;
	INT			Amount;					// ������ �������� ����
	UID32_t		GiveTargetCharacterUID;	// 2007-11-13 by cmkwon, �����ϱ� ��� �߰� - 0 �̸� �ڽ��� ����, 0�� �ƴϸ� �ش� ĳ���Ϳ��� �����ϱ�
	char		GiveTargetCharacterName[SIZE_MAX_CHARACTER_NAME];	// 2007-11-13 by cmkwon, �����ϱ� ��� �߰� - 
	INT			RemainCountForLimitedEdition;		// 2010-01-26 by cmkwon, ĳ�� ������ �����Ǹ� �ý��� ���� - 
};

struct MSG_FC_SHOP_BUY_COLOR_ITEM	// 2005-12-06 by cmkwon
{
	UINT		BuildingIndex;
	UINT		ItemNum;
};

struct MSG_FC_SHOP_BUY_COLOR_ITEM_OK	// 2005-12-06 by cmkwon
{
	UID64_t		ItemUID64;
	INT			ColorCode;
};

struct MSG_FC_SHOP_BUY_WARPOINT_ITEM
{// 2007-06-13 by dhjin, WarPoint �� 
	UINT		BuildingIndex;
	UINT		ItemNum;
	INT			Amount;					// ������ �������� ����
};

struct MSG_FC_SHOP_BUY_WARPOINT_ITEM_OK
{// 2007-06-13 by dhjin, WarPointItem �����ϰ� �� ����.
	INT				PayWarPoint;			// 2007-06-13 by dhjin, ������ WarPoint
	INT				WarPoint;				// 2007-06-13 by dhjin, �� WarPoint
};

struct MSG_FC_SHOP_CHECK_GIVE_TARGET
{// 2007-11-13 by cmkwon, �����ϱ� ��� �߰� - MSG_FC_SHOP_CHECK_GIVE_TARGET ����ü �߰�
	char			GiveTargetCharName[SIZE_MAX_CHARACTER_NAME];	// �����޴� ĳ���͸�
	INT				GiveItemNum;
};

struct MSG_FC_SHOP_CHECK_GIVE_TARGET_OK
{// 2007-11-13 by cmkwon, �����ϱ� ��� �߰� - MSG_FC_SHOP_CHECK_GIVE_TARGET_OK ����ü �߰�
	char			GiveTargetCharName[SIZE_MAX_CHARACTER_NAME];	// �����޴� ĳ���͸�
	UID32_t			GiveTargetCharUID;
	char			GiveTargetGuildName[SIZE_MAX_GUILD_NAME];
	USHORT			GiveTargetUnitKind;
	BYTE			GiveTargetLevel;
};

// start 2011-10-28 by hskim, EP4 [Ʈ���� �ý���] - ũ����Ż �ý���
struct MSG_FC_SHOP_CLOSE
{
	UINT BuildingIndex;
};
// end 2011-10-28 by hskim, EP4 [Ʈ���� �ý���] - ũ����Ż �ý���

// 2013-05-09 by hskim, ���� ����Ʈ ����
struct MSG_FC_SHOP_INFLUENCE_BUFF
{
	INT	nConsecutiveVictories;		// ���� ����Ʈ
};

struct MSG_FC_SHOP_INFLUENCE_BUFF_OK
{
	INT	nLastSkillNum;
};
// end 2013-05-09 by hskim, ���� ����Ʈ ����

struct SGIVE_TARGET_CHARACTER
{// 2007-11-13 by cmkwon, �����ϱ� ��� �߰� - SGIVE_TARGET_CHARACTER ����ü �߰�
	char			AccountName0[SIZE_MAX_ACCOUNT_NAME];
	UID32_t			AccountUID0;
	INT				ConnectingServerGroupID;
	INT				MembershipItemNum;
	ATUM_DATE_TIME	MembershipExpireTime;
	char			CharacterName0[SIZE_MAX_CHARACTER_NAME];
	UID32_t			CharacterUID0;
	BYTE			InfluenceType0;
	char			GuildName0[SIZE_MAX_GUILD_NAME];
	USHORT			UnitKind0;
	BYTE			Level0;
	INT				BuyItemNum;								// ���� �� ItemNum
};


///////////////////////////////////////////////////////////////////////////////
// FC_TRADE
typedef struct
{
	char			TradeTarget[SIZE_MAX_CHARACTER_NAME];	// �ǿ�û��
} MSG_FC_TRADE_REQUEST_TRADE;

typedef struct
{
	char			TradeSource[SIZE_MAX_CHARACTER_NAME];	// ��û��
	UID32_t			TradeSourceCharacterUniqueNumber;		// ��û���� character unique number
} MSG_FC_TRADE_REQUEST_TRADE_OK;

typedef struct
{
	char			TradeTarget[SIZE_MAX_CHARACTER_NAME];	// �ǿ�û��
} MSG_FC_TRADE_CANCEL_REQUEST;

typedef struct
{
	char			TradeSource[SIZE_MAX_CHARACTER_NAME];	// ��û��
	UID32_t			TradeSourceCharacterUniqueNumber;		// ��û���� character unique number
} MSG_FC_TRADE_CANCEL_REQUEST_OK;

typedef struct
{
	UID32_t			TradeSourceCharacterUniqueNumber;		// ��û���� character unique number
} MSG_FC_TRADE_ACCEPT_TRADE;

typedef struct
{
	char			TradeTarget[SIZE_MAX_CHARACTER_NAME];	// �ǿ�û��
	UID32_t			TradeTargetCharacterUniqueNumber;		// �ǿ�û���� character unique number
} MSG_FC_TRADE_ACCEPT_TRADE_OK;

typedef struct
{
	UID32_t			TradeSourceCharacterUniqueNumber;		// ��û���� character unique number
} MSG_FC_TRADE_REJECT_TRADE;

typedef struct
{
	char			TradeTarget[SIZE_MAX_CHARACTER_NAME];	// �ǿ�û��
	UID32_t			TradeTargetCharacterUniqueNumber;		// �ǿ�û���� character unique number
} MSG_FC_TRADE_REJECT_TRADE_OK;

typedef struct
{
	char			TradeTarget[SIZE_MAX_CHARACTER_NAME];	// �ǿ�û��
} MSG_FC_TRADE_REJECT_TRADING;								// �ŷ����̹Ƿ� �ŷ��� �� ���� ����

typedef struct
{
	UID32_t			PeerTradeCharacterUniqueNumber;			// �ŷ� ����� character unique number
} MSG_FC_TRADE_SHOW_TRADE_WINDOW;

typedef struct
{
	UID32_t			CharacterUniqueNumber;					// ������ �ø� ���
	UID64_t			ItemUniqueNumber;						// �ø� ������
	INT				ItemNum;								// ������ ����
	INT				Amount;									// �ø� ����(���������� �ش�, �������� 1)
} MSG_FC_TRADE_TRANS_ITEM;

typedef struct
{
	UID32_t			CharacterUniqueNumber;					// ������ �ø� ���
	ITEM_GENERAL	TradeItem;								// �� �������� count�� ���� ����
	INT				NumOfEnchants;							// �������� �� ��æƮ ����
	ARRAY_(INT);											// EnchantItemNum�� Array
} MSG_FC_TRADE_TRANS_ITEM_OK;

typedef struct
{
	UID32_t			CharacterUniqueNumber;					// ������ �ø� ���
	UID64_t			ItemUniqueNumber;						// �ø� ������
	INT				ItemNum;								// ������ ����
	INT				Amount;									// �ø� ����(countable item�� ���� ����, �������� 1)
} MSG_FC_TRADE_SEE_ITEM;

typedef struct
{
	UID32_t			CharacterUniqueNumber;					// ������ �ø� ���
	STRUCT_(ITEM_XXX);										// �� �������� count�� ���� ����
} MSG_FC_TRADE_SEE_ITEM_OK;

typedef struct
{
	UID32_t			CharacterUniqueNumber;					// �ڽ�
} MSG_FC_TRADE_OK_TRADE;

typedef struct
{
	UID32_t			CharacterUniqueNumber;					// ����
} MSG_FC_TRADE_OK_TRADE_OK;

typedef struct
{
	UID32_t			CharacterUniqueNumber;					// ����
} MSG_FC_TRADE_CANCEL_TRADE;

typedef struct
{
	UID32_t			CharacterUniqueNumber;					// ����
} MSG_FC_TRADE_CANCEL_TRADE_OK;

typedef MSG_FC_STORE_INSERT_ITEM		MSG_FC_TRADE_INSERT_ITEM;
typedef MSG_FC_STORE_INSERT_ITEM		MSG_FC_ENEMY_ITEM_INFO;		// 2012-06-05 by jhseol, ���۹̸����� - Ŭ���û ��Ŷ �߰�
typedef MSG_FC_STORE_DELETE_ITEM		MSG_FC_TRADE_DELETE_ITEM;
typedef MSG_FC_STORE_UPDATE_ITEM_COUNT	MSG_FC_TRADE_UPDATE_ITEM_COUNT;

struct MSG_FC_TRADE_OK_TRADE_NOTIFY		// 2008-11-21 by cmkwon, �ŷ� ���� Ȯ�� �ý��� ���� - 
{
	UID32_t			CharacterUniqueNumber;					// �ŷ� ���� ��ư�� ������ ĳ����
};

typedef enum
{
	COUNTDOWN_TYPE_P2P_WAR = 0,
	COUNTDOWN_TYPE_PARTY_WAR = 1,
	COUNTDOWN_TYPE_GUILD_WAR = 2,
	COUNTDOWN_TYPE_RACING = 3,
	COUNTDOWN_TYPE_INVALID = 4
} COUNTDOWN_TYPE;
// T0_FC_COUNTDOWN
typedef struct
{
	int		nWaitingSecond;
	BYTE	byCountdownType;
} MSG_FC_COUNTDOWN_START;

typedef struct
{
	BYTE	byCountdownType;
} MSG_FC_COUNTDOWN_DONE;


// T0_FC_OBJECT
typedef struct
{
	INT			nObjectCodeNum;
	AVECTOR3	AVec3Position;
	BodyCond_t	bodyCondition;
} MSG_FC_OBJECT_CHANGE_BODYCONDITION;

typedef MSG_FC_OBJECT_CHANGE_BODYCONDITION		MSG_FC_OBJECT_CHANGE_BODYCONDITION_OK;

///////////////////////////////////////////////////////////////////////////////////////
// start 2011-08-17 by hskim, ��Ʈ�� �ý��� 2�� - �ڷ� ���� ����
//
// ���� 
//

//// 2010-06-15 by shcho&hslee ��ý��� - �ŷ� �� �� ���� ���� ��Ŷ �߰�
//typedef struct
//{
//	UID64_t			CreatedPetUID;
//
//	BOOL			EnableEditPetName;
//	BOOL			EnableLevelUp;
//
//	char			szPetName[SIZE_MAX_PET_NAME];
//	
//	INT				PetIndex;
//	INT				PetLevel;
//	
//	Experience_t	PetExp;
//
//} MSG_TRADE_PET_DATA;
//// end 2010-06-15 by shcho&hslee ��ý��� - �ŷ� �� �� ���� ���� ��Ŷ �߰�

/////////
// ����

typedef struct
{
	UID64_t			CreatedPetUID;

	char			PetName[SIZE_MAX_PET_NAME];

	INT				PetIndex;
	INT				PetLevel;

	Experience_t	PetExp;

	// Ŭ�󿡼� �ʿ��� ���� �޾Ƽ� ó�� by hskim

} MSG_TRADE_PET_DATA;
// end 2011-08-17 by hskim, ��Ʈ�� �ý��� 2�� - �ڷ� ���� ����
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// FC_AUCTION
typedef struct
{
	UID32_t		ItemUID;
	INT			Price;
} MSG_FC_AUCTION_REGISTER_ITEM;			// C->F, ��� ������ ���

typedef struct
{
	UID32_t		ItemUID;
	INT			Price;
} MSG_FC_AUCTION_REGISTER_ITEM_OK;		// F->C, ��� ������ ��� ���

typedef struct
{
	UID32_t		ItemUID;
} MSG_FC_AUCTION_CANCEL_REGISTER;		// C->F, ��� ������ ��� ���

typedef struct
{
	UID32_t		ItemUID;
} MSG_FC_AUCTION_CANCEL_REGISTER_OK;	// F->C, ��� ������ ��� ��� ���

typedef struct
{
	UID32_t		ItemUID;
} MSG_FC_AUCTION_BUY_ITEM;				// C->F, ��� ������ ����

typedef struct
{
	UID32_t		ItemUID;
} MSG_FC_AUCTION_BUY_ITEM_OK;			// F->C, ��� ������ ���� ���

typedef struct
{
	UID32_t		CharacterUID;			// �ڽ��� ����� ��� �������� ��û�� ���� �ڽ��� CharacterUID, �ƴϸ� 0
	BYTE		AuctionKind;			// ��û�� ��� ������ ����, AUCTION_KIND_XXX
} MSG_FC_AUCTION_GET_ITEM_LIST;			// C->F, ��� ������ ��� ��û

// AUCTION_KIND_XXX
#define AUCTION_KIND_MY_ITEM	((BYTE)0)	// �ڽ��� ����� ������
#define AUCTION_KIND_ATTACH		((BYTE)1)	// ������ 0 ~ 17, 22, 25 ~ 26
#define AUCTION_KIND_CARD		((BYTE)2)	// ī��� 21, 27
#define AUCTION_KIND_ETC		((BYTE)3)	// ��Ÿ�� 18 ~ 20, 23 ~ 24

#define IS_AUCTION_KIND_ATTACH(_ITEM_KIND)	\
	(IS_WEAPON(_ITEM_KIND)					\
	|| _ITEM_KIND == ITEMKIND_DEFENSE		\
	|| _ITEM_KIND == ITEMKIND_SUPPORT		\
	|| _ITEM_KIND == ITEMKIND_TANK			\
	|| _ITEM_KIND == ITEMKIND_RADAR			\
	|| _ITEM_KIND == ITEMKIND_COMPUTER)
#define IS_AUCTION_KIND_CARD(_ITEM_KIND)	\
	(_ITEM_KIND == ITEMKIND_ENCHANT			\
	|| _ITEM_KIND == ITEMKIND_GAMBLE)
#define IS_AUCTION_KIND_ETC(_ITEM_KIND)		\
	(_ITEM_KIND == ITEMKIND_ENERGY			\
	|| _ITEM_KIND == ITEMKIND_INGOT			\
	|| _ITEM_KIND == ITEMKIND_CARD			\
	|| _ITEM_KIND == ITEMKIND_BULLET		\
	|| _ITEM_KIND == ITEMKIND_QUEST)

typedef struct
{
	BYTE			AuctionKind;		// AUCTION_KIND_XXX
	char			SellerCharacterName[SIZE_MAX_CHARACTER_NAME];
	ITEM_GENERAL	AuctionItemGeneral;	// ��� ������
	int				AuctionPrice;		// ��� ����
	ATUM_DATE_TIME	AuctionStartDate;	// ��� ���� �ð�
} MSG_FC_AUCTION_INSERT_ITEM;			// F->C, ��� ������ ���ۿ�

typedef struct
{
	BYTE			AuctionKind;		// AUCTION_KIND_XXX
	ENCHANT			AuctionItemEnchant;
} MSG_FC_AUCTION_PUT_ENCHANT;			// F->C, ��� �������� ��æƮ ���� ���ۿ�

///////////////////////////////////////////////////////////////////////////////
// FC_SKILL
typedef struct
{
	UINT		KindOfSkill;
} MSG_FC_SKILL_USE_SKILL_POINT;

typedef struct
{
	UINT		KindOfSkill;
	BYTE		UsedPoints;
	BYTE		RemainedPoints;
} MSG_FC_SKILL_USE_SKILL_POINT_OK;

typedef struct
{
	INT			ItemNum;
} MSG_FC_SKILL_SETUP_SKILL;

typedef struct
{
	BYTE		ItemUpdateType;		// IUT_SHOP, IUT_LOADING, IUT_SKILL
	ITEM_SKILL	ItemSkill;
} MSG_FC_SKILL_SETUP_SKILL_OK;

typedef struct
{
	ItemID_t		SkillItemID;
	ClientIndex_t	AttackIndex;
	ClientIndex_t	TargetIndex;	// target�� ���� skill�� ��� 0
	UID32_t			TargetCharUID;	// 2005-11-24 by cmkwon, target������ TargetIndex�� 0�϶� ����, TargetIndex�� ����� 1�� ��ȯ ��ų�� ����Ѵ�.
} MSG_FC_SKILL_USE_SKILL;

typedef struct
{
	ItemID_t		SkillItemID;
	ClientIndex_t	AttackIndex;
	ClientIndex_t	TargetIndex;	// target�� ���� skill�� ��� 0
	ATUM_DATE_TIME	UseTime;		// 2006-11-17 by dhjin, 2�� ��ų ��� �ð�
	//	BOOL			UseSkillTimeOk;	// 2006-11-17 by dhjin, 0 -> 2�� ��ų ��� ��� �ð�, 1 -> 2�� ��ų ����� �� �ִ�.
} MSG_FC_SKILL_USE_SKILL_OK;

typedef struct
{
	ItemID_t		SkillItemID;			// ����Ǵ� ��ų ����
	INT				AttackSkillItemNum0;	// 2006-12-12 by cmkwon, ���� ��ų�� ����ǰ� �ϴ� ���ݽ�ų �����۳ѹ� 
} MSG_FC_SKILL_CANCEL_SKILL;

typedef struct
{
	ClientIndex_t	ClientIndex;
	ItemID_t		SkillItemID;
	INT				AttackSkillItemNum0;	// 2006-12-12 by cmkwon, ���� ��ų�� ����ǰ� �ϴ� ���ݽ�ų �����۳ѹ�
} MSG_FC_SKILL_CANCEL_SKILL_OK;

typedef struct
{
	ItemID_t		SkillItemID;
	ClientIndex_t	ClientIndex;
} MSG_FC_SKILL_INVALIDATE_SKILL;	// skill ��� ����(�ð� ������ ���� ���)

typedef struct
{
	ItemID_t		SkillItemID;
} MSG_FC_SKILL_PREPARE_USE;

typedef struct
{
	ClientIndex_t	ClientIndex;
	ItemID_t		SkillItemID;
} MSG_FC_SKILL_PREPARE_USE_OK;

typedef struct
{
	ItemID_t		SkillItemID;
} MSG_FC_SKILL_CANCEL_PREPARE;

typedef struct
{
	ClientIndex_t	ClientIndex;
	ItemID_t		SkillItemID;
} MSG_FC_SKILL_CANCEL_PREPARE_OK;

struct MSG_FC_SKILL_CONFIRM_USE			// 2005-12-02 by cmkwon
{
	char				szAttackCharacterName[SIZE_MAX_CHARACTER_NAME];	// ��ų ������� CharacterName;
	UID32_t				AttackCharacterUID;		// ��ų ����� CharacterUID
	UID32_t				TargetCharacterUID;		// ��ų Ÿ�� CharacterUID
	int					UsingSkillItemNum;		// ��� ��ų ItemNum
	MAP_CHANNEL_INDEX	MapChannelIndex;		// ��ų ������� MapChannelIndex
	int					SkillConfirmUseUID;		// 2009-04-06 by cmkwon, �ݿ��� ����� ��ų �ý��� ���� - �ش� ��û�� UID
};

struct MSG_FC_SKILL_CONFIRM_USE_ACK		// 2005-12-02 by cmkwon
{
	BOOL				bYesOrNo;				// ���� ����
	UID32_t				AttackCharacterUID;		// ��ų ����� CharacterUID
	UID32_t				TargetCharacterUID;		// ��ų Ÿ�� CharacterUID
	int					UsingSkillItemNum;		// ��� ��ų ItemNum
	int					SkillConfirmUseUID;		// 2009-04-06 by cmkwon, �ݿ��� ����� ��ų �ý��� ���� - �ش� ��û�� UID
};



///////////////////////////////////////////////////////////////////////////////
// FN_SKILL
typedef MSG_FC_SKILL_USE_SKILL				MSG_FN_SKILL_USE_SKILL;
typedef struct : public MSG_FC_SKILL_USE_SKILL_OK
{
	ChannelIndex_t		ChannelIndex;
} MSG_FN_SKILL_USE_SKILL_OK;

///////////////////////////////////////////////////////////////////////////////
// FC_SYNC
//typedef struct
//{
//	INT		ItemNum;
//} MSG_FC_SYNC_SKILL_REUSE_OK;

///////////////////////////////////////////////////////////////////////////////
// FC_INFO
typedef struct
{
	INT				MonsterUnitKind;	// ���� ���� ��ȣ
} MSG_FC_INFO_GET_MONSTER_INFO;

struct MEX_MONSTER_INFO
{
	INT				MonsterUnitKind;					// ���� ������ȣ
	char			MonsterName[SIZE_MAX_MONSTER_NAME];	// ���� �̸�
	BYTE			Level;								// ������ Level
	INT				HP;									// ����
	BYTE			Size;								// �ʵ� ������ SizeForClient�� loading,  NPC ������ SizeForServer�� loading
	BYTE			Belligerence;						// ȣ����, // 2005-12-28 by cmkwon �߰���
	BYTE			AlphaBlending;						// alpha blending ����, TRUE(1), FALSE(0), client�� ����� ���� �߰�, 20030616
	USHORT			RenderIndex;
	float			ScaleValue;
	BYTE			TextureIndex;
	UINT			SourceIndex;
	BitFlag64_t		MPOption;			// 2010-01-11 by cmkwon, ���� MPOption 64bit�� ���� - ����(BYTE)
	BYTE			ClickEvent;							// 2007-09-05 by dhjin, ���� Ŭ�� �̺�Ʈ �߰�
	char			PortraitFileName[SIZE_MAX_FILE_NAME];	// 2010-03-31 by dhjin, ���Ǵ�Ƽ(�������) - ���� �ʻ�ȭ ����

	// operator overloading
	MEX_MONSTER_INFO& operator=(const MONSTER_INFO& rhs)
	{
		this->MonsterUnitKind = rhs.MonsterUnitKind;
		STRNCPY_MEMSET(this->MonsterName, rhs.MonsterName, SIZE_MAX_MONSTER_NAME);
		this->Level = rhs.Level;
		this->HP = rhs.MonsterHP;
		this->Size = rhs.Size;
		this->Belligerence = rhs.Belligerence;				// ȣ����
		this->AlphaBlending = rhs.AlphaBlending;
		this->RenderIndex = rhs.RenderIndex;
		this->ScaleValue = rhs.ScaleValue;
		this->TextureIndex = rhs.TextureIndex;
		this->SourceIndex = rhs.SourceIndex;
		this->MPOption = rhs.MPOption;
		this->ClickEvent = rhs.ClickEvent;				// 2007-09-05 by dhjin
		STRNCPY_MEMSET(this->PortraitFileName, rhs.PortraitFileName, SIZE_MAX_FILE_NAME);	// 2010-03-31 by dhjin, ���Ǵ�Ƽ(�������) - ���� �ʻ�ȭ ����

		return *this;
	}
};

typedef struct
{
	MEX_MONSTER_INFO	MonsterInfo;
} MSG_FC_INFO_GET_MONSTER_INFO_OK;

typedef struct
{
	INT				Code;
} MSG_FC_INFO_GET_MAPOBJECT_INFO;

typedef struct
{
	MAPOBJECTINFO	MapObjectInfo;
} MSG_FC_INFO_GET_MAPOBJECT_INFO_OK;

typedef struct
{
	INT				ItemNum;
} MSG_FC_INFO_GET_ITEM_INFO;

typedef struct
{
	ITEM			ItemInfo;
} MSG_FC_INFO_GET_ITEM_INFO_OK;

typedef struct
{
	INT				CodeNum;
} MSG_FC_INFO_GET_RARE_ITEM_INFO;

typedef struct
{
	RARE_ITEM_INFO	RareItemInfo;
} MSG_FC_INFO_GET_RARE_ITEM_INFO_OK;

typedef struct
{
	INT				BuildingIndex;
} MSG_FC_INFO_GET_BUILDINGNPC_INFO;

typedef struct
{
	BUILDINGNPC		BuildingNPCInfo;
} MSG_FC_INFO_GET_BUILDINGNPC_INFO_OK;

typedef struct
{
	INT				ItemNum;
} MSG_FC_INFO_GET_SIMPLE_ITEM_INFO;

struct MEX_ITEM_INFO
{
	INT			ItemNum;						// ������ ������ȣ, ���� �������� �� (ITEM_BASE*)
	BYTE		Kind;							// ������ ����(�����, ��, ����, ��ų.....), ITEMKIND_XXX
	float		AbilityMin;						// �������ּҼ���
	float		AbilityMax;						// �������ִ뼺��
	USHORT		ReqUnitKind;					// �ʿ���������
	BYTE		ReqMinLevel;					// �ʿ� ���� ����
	BYTE		ReqMaxLevel;					// �ʿ� ���� ����
	float		HitRate;						// ����Ȯ��(0~255), // 2010-07-19 by dhjin, Ȯ�� ���� ����
	BYTE		Defense;						// ����
	BYTE		SpeedPenalty;					// ���ǵ����Ƽ, �̵��ӵ�����ġ�� ����(-:����)
	USHORT		Range;							// ���ݹ���, �������� ��쿡�� �ν��� ���� �� �ӵ�
	UINT		Price;							// �ּ� �ŷ� ������ ����
	UINT		CashPrice;						// �ּ� �ŷ� ������ ���� ����
	// 2009-04-21 by cmkwon, ITEM�� DesParam �ʵ� ���� 8���� �ø��� - 
	// 	BYTE		DestParameter1;					// ����Ķ����1
	// 	float		ParameterValue1;				// �����Ķ����1
	// 	BYTE		DestParameter2;					// ����Ķ����2
	// 	float		ParameterValue2;				// �����Ķ����2
	// 	BYTE		DestParameter3;					// ����Ķ����3
	// 	float		ParameterValue3;				// �����Ķ����3
	// 	BYTE		DestParameter4;					// ����Ķ����4
	// 	float		ParameterValue4;				// �����Ķ����4
	DestParam_t	ArrDestParameter[SIZE_MAX_DESPARAM_COUNT_IN_ITEM];	// 2011-08-01 by hskim, ��Ʈ�� �ý��� 2�� - �ڷ��� ���� (DestParameter - 255 -> 32767 ����)) - // 2009-04-21 by cmkwon, ITEM�� DesParam �ʵ� ���� 8���� �ø��� - 
	float		ArrParameterValue[SIZE_MAX_DESPARAM_COUNT_IN_ITEM];	// 2009-04-21 by cmkwon, ITEM�� DesParam �ʵ� ���� 8���� �ø��� - 

	UINT		ReAttacktime;					// �� ���ݽð�(ms)
	INT			Time;							// ���� �ð�(��ų�� ��)
	USHORT		RepeatTime;						// 2006-12-08 by cmkwon, �߰���(����������� ���� �Ѿ� ���� ���, �������� ����, �ð��� ��ų������ ���� �ð�, ������ ��ų�� ��� ����)
	float		RangeAngle;						// ��������(0 ~ PI)
	BYTE		MultiTarget;					// ���ÿ� ���� �� �ִ� Ÿ���� ��
	USHORT		ExplosionRange;					// ���߹ݰ�(���� �� �������� ������ ��ġ�� �ݰ�)
	USHORT		ReactionRange;					// �����ݰ�(���� ���� �����ϴ� �ݰ�)
	BYTE		ShotNum;						// ���� ��,	���� �� �߻� ���� ��Ÿ����.
	BYTE		MultiNum;						// ���� �߻� ź ��,	1�� �߻翡 ����� ���ÿ� ��������
	USHORT		AttackTime;						// ���ݽð�, ������ �ϱ� ���� �ʿ��� �ð�
	BYTE		ReqSP;							// SP �Ҹ�(��ų)
	BYTE		OrbitType;						// �̻���, ���� ���� ����
	BitFlag64_t	ItemAttribute;					// �������� �Ӽ�, ITEM_ATTR_XXX
	FLOAT		BoosterAngle;					// �ν��ͽÿ� ������ ȸ����, ����� �������� ���

	// operator overloading
	MEX_ITEM_INFO& operator=(const ITEM& rhs);
};
typedef struct
{
	MEX_ITEM_INFO	ItemInfo;
} MSG_FC_INFO_GET_SIMPLE_ITEM_INFO_OK;
typedef struct
{
	INT				EnchantItemNum;
} MSG_FC_INFO_GET_ENCHANT_COST;		// C->F, ��æƮ ������ ��û
typedef struct
{
	INT				Cost;
} MSG_FC_INFO_GET_ENCHANT_COST_OK;	// F->C, ��æƮ ������ ����

struct MSG_FC_INFO_GET_CURRENT_MAP_INFO		// 2007-04-06 by cmkwon, �߰���
{
	MAP_CHANNEL_INDEX	mapChannelIdx0;			// 2007-04-06 by cmkwon
	// 2009-05-29 by cmkwon, Hash�˰����� �߰�(SHA256) - 
	//UINT				checkSum0;				// 2007-04-06 by cmkwon, map�� checksum ���
	int					nFileSize;			// 2009-05-29 by cmkwon, Hash�˰����� �߰�(SHA256) - 
	BYTE				byDigest[32];		// 2009-05-29 by cmkwon, Hash�˰����� �߰�(SHA256) - 
};

struct MSG_FC_INFO_GET_CURRENT_MAP_INFO_OK
{
	BYTE			IsPKMap;				// 2005-02-15 by cmkwon, ���� ������� ����
	BYTE			IsCityWarStarted;		// ���������� ���� �÷���
	BYTE			byCityWarTeamType;		//
};

enum
{
	HAPPYEV_STATE_TYPE_END = 0,			// �Ϲ� ���Ǿƿ� �̺�Ʈ �����
	HAPPYEV_STATE_TYPE_START = 1,			// �Ϲ� ���Ǿƿ� �̺�Ʈ ���۵�
	HAPPYEV_STATE_TYPE_STARTING = 2,			// �Ϲ� ���Ǿƿ� �̺�Ʈ ������
	PCBANG_HAPPYEV_STATE_TYPE_END = 10,			// PCBang ���Ǿƿ� �̺�Ʈ �����
	PCBANG_HAPPYEV_STATE_TYPE_START = 11,			// PCBang ���Ǿƿ� �̺�Ʈ ���۵�
	PCBANG_HAPPYEV_STATE_TYPE_STARTING = 12,			// PCBang ���Ǿƿ� �̺�Ʈ ������
	GAME_EVENT_GROUP_MOTHERSHIP_END = 20,		// 2008-05-20 by cmkwon, ��� �̺�Ʈ(HappyHoure,MotherShip,Item) �׷� ���ÿ� �����ϰ� - 
	GAME_EVENT_GROUP_MOTHERSHIP_START = 21,		// 2008-05-20 by cmkwon, ��� �̺�Ʈ(HappyHoure,MotherShip,Item) �׷� ���ÿ� �����ϰ� - 
	GAME_EVENT_GROUP_MOTHERSHIP_STARTING = 22,		// 2008-05-20 by cmkwon, ��� �̺�Ʈ(HappyHoure,MotherShip,Item) �׷� ���ÿ� �����ϰ� - 
	GAME_EVENT_GROUP_ITEM_END = 30,		// 2008-05-20 by cmkwon, ��� �̺�Ʈ(HappyHoure,MotherShip,Item) �׷� ���ÿ� �����ϰ� - 
	GAME_EVENT_GROUP_ITEM_START = 31,		// 2008-05-20 by cmkwon, ��� �̺�Ʈ(HappyHoure,MotherShip,Item) �׷� ���ÿ� �����ϰ� - 
	GAME_EVENT_GROUP_ITEM_STARTING = 32,		// 2008-05-20 by cmkwon, ��� �̺�Ʈ(HappyHoure,MotherShip,Item) �׷� ���ÿ� �����ϰ� - 
	GAME_EVENT_GROUP_CRYSTAL_SYSTEM_END = 40,		// 2011-10-28 by hskim, EP4 [Ʈ���� �ý���] - ũ����Ż �ý���
	GAME_EVENT_GROUP_CRYSTAL_SYSTEM_START = 41,		// 2011-10-28 by hskim, EP4 [Ʈ���� �ý���] - ũ����Ż �ý���
	GAME_EVENT_GROUP_CRYSTAL_SYSTEM_STARTING = 42,		// 2011-10-28 by hskim, EP4 [Ʈ���� �ý���] - ũ����Ż �ý���
	GAME_EVENT_GROUP_CRYSTAL_SYSTEM_2ND_END = 50,		// 2012-05-08 by hskim, EP4 [Ʈ���� �ý���] - ũ����Ż �ý��� 2��
	GAME_EVENT_GROUP_CRYSTAL_SYSTEM_2ND_START = 51,		// 2012-05-08 by hskim, EP4 [Ʈ���� �ý���] - ũ����Ż �ý��� 2��
	GAME_EVENT_GROUP_CRYSTAL_SYSTEM_2ND_STARTING = 52		// 2012-05-08 by hskim, EP4 [Ʈ���� �ý���] - ũ����Ż �ý��� 2��
};
struct MSG_FC_INFO_GET_HAPPY_HOUR_EVENT_INFO_OK
{
	BYTE			byStateType;			// 0(�����), 1(���۵�), 2(������)
	BYTE			byInfluenceType4;		// 2007-10-30 by cmkwon, ���º� ���Ǿƿ� �̺�Ʈ ���� - MSG_FC_INFO_GET_HAPPY_HOUR_EVENT_INFO_OK ����ü�� �߰��� �ʵ�
	ATUM_DATE_TIME	StartATime;
	ATUM_DATE_TIME	EndATime;
	float			fEXPRate2;
	float			fSPIRate2;
	float			fEXPRepairRate2;
	float			fDropItemRate2;
	float			fDropRareRate2;
	float			fWarPointRate2;			// 2007-06-26 by dhjin, ������Ʈ �̺�Ʈ ���� �߰�

	// 2013-08-12 by bckim, �ű����Ǿƿ�
	float			fHPRecoveryRate;
	float			fSHDRecoveryRate;
	float			fSPRecoveryRate;
	float			fWeaponEnchantRate;
	float			fArmorEnchantRate;
	float			fETCItemEnchantRate;
	float			fSPIDiscountRate;
	float			fWPDiscountRate;
	// End. 2013-08-12 by bckim, �ű����Ǿƿ�
};
struct MSG_FC_INFO_GET_GAME_EVENT_INFO_OK
{
	BYTE			byStateType;			// 0(�����), 1(���۵�), 2(������)
	int				nGameEventType;			// �̺�Ʈ Ÿ��
	float			fRate;					// �̺�Ʈ Rate
	int				nRemainMinute;			// ���� �ð�(����:��)
};

struct MSG_FC_INFO_GET_SERVER_DATE_TIME_OK		// 2006-10-11 by cmkwon
{
	ATUM_DATE_TIME	atimeCurServerTime;		// 2006-10-11 by cmkwon, ���� ���� ��¥ �ð�
};

struct MSG_FC_INFO_CHECK_RESOBJ_CHECKSUM		// 2007-05-28 by cmkwon
{
	int			nItemNum0;
	char		szObjFileName[SIZE_MAX_RESOBJ_FILE_NAME];
	// 2009-05-29 by cmkwon, Hash�˰����� �߰�(SHA256) - 
	//UINT		uiCheckSum0;
	int			nFileSize0;
	BYTE		byDigest[32];		// 2009-05-29 by cmkwon, Hash�˰����� �߰�(SHA256) - 
};


///////////////////////////////////////////////////////////////////////////////
// FC_REQUEST - ĳ���Ͱ��� ��û, ����, ���� � ����, general-purpose
// REQUEST_TYPE_XXX
#define REQUEST_TYPE_NULL			((BYTE)0)
#define REQUEST_TYPE_TRADE			((BYTE)1)	// �ŷ�
#define REQUEST_TYPE_PARTY_INVITE	((BYTE)2)	// ��Ƽ �ʴ�
#define REQUEST_TYPE_GUILD_INVITE	((BYTE)3)	// ���� �ʴ�
#define REQUEST_TYPE_P2P_PK			((BYTE)4)	// 1�� 1 ����
#define REQUEST_TYPE_PARTY_BATTLE	((BYTE)5)	// ��Ƽ�� ����
#define REQUEST_TYPE_GUILD_WAR		((BYTE)6)	// ������ ��û, ���� �ʿ��� ������ ����

typedef struct
{
	ClientIndex_t	TargetClientIndex;	// �ǿ�û��
	char			TargetCharacterName[SIZE_MAX_CHARACTER_NAME];	// ClientIndex�� 0�� ��� �� �ʵ� ����
	BYTE			RequestType;
} MSG_FC_REQUEST_REQUEST;				// C->F, ��û

typedef struct
{
	ClientIndex_t	SourceClientIndex;	// ��û��
	char			SourceCharacterName[SIZE_MAX_CHARACTER_NAME];	// ClientIndex�� 0�� ��� �� �ʵ� ����
	BYTE			RequestType;
} MSG_FC_REQUEST_REQUEST_OK;			// F->C, ��û�� ����

typedef struct
{
	ClientIndex_t	SourceClientIndex;	// ��û��
	char			SourceCharacterName[SIZE_MAX_CHARACTER_NAME];	// ClientIndex�� 0�� ��� �� �ʵ� ����
	BYTE			RequestType;
} MSG_FC_REQUEST_ACCEPT_REQUEST;		// C->F, �³�

typedef struct
{
	ClientIndex_t	PeerClientIndex;	// ����
	char			PeerCharacterName[SIZE_MAX_CHARACTER_NAME];	// ClientIndex�� 0�� ��� �� �ʵ� ����
	BYTE			RequestType;
} MSG_FC_REQUEST_ACCEPT_REQUEST_OK;		// F->C, �³��� ����, ��(Ȥ�� ��) ������ ����

typedef struct
{
	ClientIndex_t	SourceClientIndex;	// ��û��
	char			SourceCharacterName[SIZE_MAX_CHARACTER_NAME];	// ClientIndex�� 0�� ��� �� �ʵ� ����
	BYTE			RequestType;
} MSG_FC_REQUEST_REJECT_REQUEST;		// C->F, ����

typedef struct
{
	ClientIndex_t	PeerClientIndex;	// ����
	char			PeerCharacterName[SIZE_MAX_CHARACTER_NAME];	// ClientIndex�� 0�� ��� �� �ʵ� ����
	BYTE			RequestType;
} MSG_FC_REQUEST_REJECT_REQUEST_OK;		// F->C, ������ ����, ��(Ȥ�� ��) ������ ����

typedef struct
{
	ClientIndex_t	PeerClientIndex;	// ����
	char			PeerCharacterName[SIZE_MAX_CHARACTER_NAME];	// ClientIndex�� 0�� ��� �� �ʵ� ����
	BYTE			RequestType;
} MSG_FC_REQUEST_CANCEL_REQUEST;		// C->F, ��û ��ҵ�, ��(Ȥ�� ��) ������ ����

///////////////////////////////////////////////////////////////////////////////
// FC_CITY - ���ÿ� ��������
typedef struct
{
	MAP_CHANNEL_INDEX	MapChannelIndex;
} MSG_FC_CITY_GET_BUILDING_LIST;

struct CITY_BUILDING_INFO_4_EXCHANGE
{
	UINT	BuildingIndex;	// �ǹ�(���� ��) ���� ��ȣ
	BYTE	BuildingKind;
};

typedef struct
{
	INT		NumOfBuildings;
	ARRAY_(CITY_BUILDING_INFO_4_EXCHANGE);
} MSG_FC_CITY_GET_BUILDING_LIST_OK;

typedef struct
{
	MAP_CHANNEL_INDEX	MapChannelIndex;
} MSG_FC_CITY_GET_WARP_TARGET_MAP_LIST;

// 2004-11-10 by cmkwon, ������ ������
//struct WARP_TARGET_MAP_INFO_4_EXCHANGE
//{
//	MapIndex_t	MapIndex;
//	INT			TargetIndex;	// EVENTINFO�� �����ϴ� TargetIndex
//	char		TargetName[SIZE_MAX_WARP_TARGET_NAME];	// Ÿ���� �̸�(ex: ���û��, �����ϴ�)
//	INT			Fee;			// ���� ���
//};

typedef struct
{
	INT		NumOfTargetMaps;
	ARRAY_(WARP_TARGET_MAP_INFO_4_EXCHANGE);
} MSG_FC_CITY_GET_WARP_TARGET_MAP_LIST_OK;

typedef struct
{
	INT		BuildingIndex;
} MSG_FC_CITY_REQUEST_ENTER_BUILDING;	// C->F, ���� �� ���� ��û

typedef struct
{
	INT		BuildingIndex;
	// 2006-02-08 by cmkwon
	//	float	fCityWarTexRate;			//
	float	fInflDistributionTexPercent;	// 2006-02-08 by cmkwon, ���º��� ����
} MSG_FC_CITY_REQUEST_ENTER_BUILDING_OK;	// F->C, ���� ���� �ϷḦ �˸�

typedef struct
{
	MapIndex_t	MapIndex;
	INT			TargetIndex;			// EVENTINFO�� �����ϴ� TargetIndex	
} MSG_FC_CITY_REQUEST_WARP;				// C->F, ���ÿ��� �����ؼ� ������ ���� ��û

typedef struct
{
	Err_t		Err;				// ERR_NO_ERROR�̸� ����
} MSG_FC_CITY_CHECK_WARP_STATE_OK;	// F->C, ���� ������ ���������� ���� ���

///////////////////////////////////////////////////////////////////////////////
// FC_TIMER - Ÿ�̸� ������ ��������
///////////////////////////////////////////////////////////////////////////////

// TimerEventType �� ����, TE_TYPE_XXX
#define TE_TYPE_TEST					(TimerEventType)0
//#define TE_TYPE_SYNC_PRI				(TimerEventType)1
//#define TE_TYPE_SYNC_SEC				(TimerEventType)2
//#define TE_TYPE_SYNC_SKILL			(TimerEventType)3
//#define TE_TYPE_END_SKILL				(TimerEventType)4		// check: Ŭ���̾�Ʈ�� ��û�� ���� ������, �ش� �ð� ��� �� Ŭ���̾�Ʈ���� CANCEL_SKILL ����, 20041005, kelovon with jschoi
//#define TE_TYPE_DELETE_MINE			(TimerEventType)5	// check: ���� ������ Ŭ���̾�Ʈ���� ��� �����ϱ�� �ϸ鼭 ������, 20041118, kelovon with dhkwon
#define TE_TYPE_DELETE_DUMMY			(TimerEventType)6
#define TE_TYPE_DELETE_FIXER			(TimerEventType)7
#define TE_TYPE_DELETE_DECOY			(TimerEventType)8		// �����̴� TimeOut�߻� �� CurrentCount�� ���̰�, CurrentCount=0���� �ݺ���
#define TE_TYPE_GRADUAL_SHIELD_UP		(TimerEventType)9		// 2-2�� ���� ����, interval�� ������ 1000 ms
#define TE_TYPE_RECOVER_HP				(TimerEventType)10		// �������� ���� ä��(5�ʴ� 3)
#define TE_TYPE_RECOVER_DP				(TimerEventType)11		// �������� ���� ä��
#define TE_TYPE_RECOVER_SP				(TimerEventType)12
#define TE_TYPE_GRADUAL_HP_UP			(TimerEventType)13		// interval�� ������ 1000 ms, ITEM_GENERAL.Endurance�� 0�� �� ������ �ݺ���
#define TE_TYPE_GRADUAL_DP_UP			(TimerEventType)14		// interval�� ������ 1000 ms, ITEM_GENERAL.Endurance�� 0�� �� ������ �ݺ���
#define TE_TYPE_GRADUAL_SP_UP			(TimerEventType)15		// interval�� ������ 1000 ms, ITEM_GENERAL.Endurance�� 0�� �� ������ �ݺ���, not used yet: SP�� �ڵ����� ȸ����, TE_TYPE_RECOVER_SP�� ���
#define TE_TYPE_GRADUAL_EP_UP			(TimerEventType)16		// interval�� ������ 1000 ms, ITEM_GENERAL.Endurance�� 0�� �� ������ �ݺ���
#define TE_TYPE_IMMEDIATE_HP_UP			(TimerEventType)17		// ���� �ٷ� ä��� Time ���� ������ �ȵȴ�
#define TE_TYPE_IMMEDIATE_DP_UP			(TimerEventType)18		// ���� �ٷ� ä��� Time ���� ������ �ȵȴ�
#define TE_TYPE_IMMEDIATE_SP_UP			(TimerEventType)19		// ���� �ٷ� ä��� Time ���� ������ �ȵȴ�
#define TE_TYPE_IMMEDIATE_EP_UP			(TimerEventType)20		// ���� �ٷ� ä��� Time ���� ������ �ȵȴ�
#define TE_TYPE_REQUEST_TIMEOUT			(TimerEventType)21		// �ŷ�, ��Ƽ��, �ϴ��ϴ�� ���� ��û�� ���� TimeOut
#define TE_TYPE_DECREASE_SP				(TimerEventType)22		// TOGGLE�� ��ų ��� ��, SP�� ReqSP��ŭ �Ҹ�, SP ���� �� ��ų �ڵ� ���
#define TE_TYPE_DO_MINUTELY_WORK		(TimerEventType)23		// 1�п� �ѹ��� �����ϴ� Ÿ�̸�
////////////////////////////////////////////////////////////////////////////////
// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - 
#define TE_TYPE_DOTSKILL_STEALING		(TimerEventType)24		// Stealing ��ų - SP���� (SP�� ���� �Ǿ ��� ���� �Ǿ�� �Ѵ�.)
#define TE_TYPE_DOTSKILL_DRAIN			(TimerEventType)25		// Drain ��ų - �ǰݴ�� HP���ҽ��� ���ݴ�󿡰� ä���ش�.
#define TE_TYPE_DOTSKILL_TIME_BOMB		(TimerEventType)26		// TimeBomb ��ų - �� ��󿡰� �ð� ����� ���� �ǿ� %�� �������� ������.
#define TE_TYPE_FIXED_TERM_SHAPE		(TimerEventType)27		// 2012-10-10 by hskim, �Ⱓ�� �Ӽ� ���� (�Ⱓ�� ����)


#define TIMER_DOT_INTERVAL					1000


#define TIMER_DECOY_TIME_CHECK_INTERVAL		1000
#define TIMER_GRADUAL_UP_INTERVAL			1000	// gradual up�� ���Ǵ� interval, DELETE_DECOY���� �����
#define _DEFAULT_TIME_GRANULARITY			100		// milli-seconds
#define _MAX_TIMER_INTERVAL_TIME			150000	// maximum 150 seconds, check: �����ؾ� ��
#define SIZE_MAX_TIMER_EVENT_MEMPOOL		1000
#define _TIMER_TICK							_DEFAULT_TIME_GRANULARITY/3
#define TIMER_REPEAT_INFINITE				MAX_INT_VALUE
#define TIMER_DECREASE_SP_INTERVAL			1000				// 1��
#define TIMER_DO_MINUTELY_WORK				60*1000				// 1��


#define MANAGE_MAX_TIME_FIXED_TERM_MINUTELY		10080				// 2012-10-10 by hskim, �Ⱓ�� �Ӽ� ���� (�Ⱓ�� ����) - 1�� 60�� * 24�ð� * 7�� (�Ⱓ�� ������ 7������ ���� �͸� ó��)

struct MEX_TIMER_EVENT
{
	TimerEventType		Type;
	UID32_t				TimerUID;				// Ÿ�̸� ���̵�
	TimeUnit_t			StartTimeStamp;			// milli-seconds
	TimeUnit_t			ExpireTime;				// milli-seconds
	TimeUnit_t			TimeInterval;			// milli-seconds, (ExpireTime - StartTimeStamp)
	UID32_t				CharacterUniqueNumber;	// event�� ������ charac�� ������ �ٸ� charac�� socket�� ����ϴ� ��츦 ���� ����, IsUsing()�� CharacterUniqueNumber�� ���ƾ� ��!
	ClientIndex_t		ClientIndex;			// event�� ������ charac�� ������ �ٸ� charac�� socket�� ����ϴ� ��츦 ���� ����, IsUsing()�� ClientIndex�� ���ƾ� ��!
	UINT				nGeneralParam1;			// end_skill: ITEM_SKILL* ,	mine: CMapBlock*,	delete_item��: ITEM_GENERAL*, GRADUAL_SHIELD_UP: HI(ItemUID), GRADUAL_XXX_UP: ITEM*, DELETE_DUMMY: FIELD_DUMMY*
	UINT				nGeneralParam2;			// end_skill: ,				mine: DROPMINE*,	delete_item��:              , GRADUAL_SHIELD_UP: LO(ItemUID)
	UINT				nGeneralParam3;			// end_skill: ,				mine: CFieldIOCP*,	delete_item��:              , GRADUAL_SHIELD_UP: ItemNum
	BOOL				bRepeatable;			// repeat�ؾ� �ϴ��� ����
	INT					nRemainedRepeatCount;	// ���� Ƚ��, ~0(0xFFFFFFFF): ���� �ݺ�, 0����: ����, 1�̻�: ȸ����ŭ �ݺ�
};

typedef struct
{
	MEX_TIMER_EVENT		TimerEvent;
} MSG_FC_TIMER_START_TIMER;			// F->C, TIMER_EVENT ����

typedef struct
{
	UID32_t				TimerUID;
} MSG_FC_TIMER_STOP_TIMER;			// F->C, TIMER_EVENT ����

typedef struct
{
	MEX_TIMER_EVENT		TimerEvent;
} MSG_FC_TIMER_UPDATE_TIMER;		// F->C, TIMER_EVENT ����(�ð� ����)

typedef struct
{
	UID32_t				TimerUID;
} MSG_FC_TIMER_PAUSE_TIMER;			// F->C, TIMER_EVENT �Ͻ� ����

typedef struct
{
	UID32_t				TimerUID;
} MSG_FC_TIMER_CONTINUE_TIMER;		// F->C, TIMER_EVENT �����

typedef struct
{
	MEX_TIMER_EVENT		TimerEvent;
} MSG_FC_TIMER_TIMEOUT;				// C->F, �ð��� �� ���� �˸�


// 2014-01-27 by bckim, ���� Ʈ��
typedef struct
{
	UID32_t				CharacterUniqueNumber;
} MSG_FC_BUGTRAP_ACCEPT;		// C -> F
// End. 2014-01-27 by bckim, ���� Ʈ��

///////////////////////////////////////////////////////////////////////////////
// FC_CLIENT_REPORT
typedef struct
{
	char			ClientPrivateIP[SIZE_MAX_IPADDRESS];	// �缳���� ��� private ip
	char			CharacterName[SIZE_MAX_CHARACTER_NAME];
	char			Message[SIZE_MAX_CLIENT_REPORT];
} MSG_FC_CLIENT_REPORT;		// C -> F

///////////////////////////////////////////////////////////////////////////////
// STRING128 - DEBUG Message
typedef struct
{
	BYTE			PrintType;		// STR128_PRINT_TYPE_XXX
	char			String[128];
	WORD			SecurityNumber;		// 2011-06-22 by hskim, �缳 ���� ����
} MSG_FC_STRING_128;
typedef struct
{
	BYTE			PrintType;		// STR128_PRINT_TYPE_XXX
	char			String[256];
	WORD			SecurityNumber;		// 2011-06-22 by hskim, �缳 ���� ����
} MSG_FC_STRING_256;
typedef struct
{
	BYTE			PrintType;		// STR128_PRINT_TYPE_XXX
	char			String[512];
	WORD			SecurityNumber;		// 2011-06-22 by hskim, �缳 ���� ����
} MSG_FC_STRING_512;

#define STR128_PRINT_TYPE_CHAT		(BYTE)0x00	// ä��â�� ���
#define STR128_PRINT_TYPE_STATIC	(BYTE)0x01	// ���� text�� ���
#define STR128_PRINT_TYPE_DBGOUT	(BYTE)0x02	// Ŭ���̾�Ʈ DBGOUT ��� - // 2012-02-13 by hskim, ���� ������ ��� �׽�Ʈ ���ɾ�
#define STR128_PRINT_TYPE_NOTICE	(BYTE)0x03	// Ŭ���̾�Ʈ ���� ��ũ�ѿ� �ø� - // 2012-03-30 by hskim, EP4 Ʈ���� �ý��� �̺�Ʈ �˸�
#define STR128_PRINT_TYPE_POPUP		(BYTE)0x04	// Ŭ���̾�Ʈ ���� �˾����� �ٿ� - // 2013-05-31 by jhseol,bckim �Ƹ� �÷��� - STR128_PRINT_TYPE_POPUP �߰�
#define STR128_PRINT_TYPE_OPERATOR	(BYTE)0x05	// 2013-10-02 by bckim, �������� ����ȭ ��Ʈ�� �����۾� 


typedef MSG_FC_STRING_128	MSG_IC_STRING_128;
typedef MSG_FC_STRING_256	MSG_IC_STRING_256;
typedef MSG_FC_STRING_512	MSG_IC_STRING_512;

///////////////////////////////////////////////////////////////////////////////
// FI_ADMIN
typedef struct
{
	BYTE	Type;			// see below
	UID32_t	AdminCharacterUniqueNumber;
	UID32_t	CharacterUniqueNumber;
} MSG_FI_ADMIN_GET_CHARACTER_INFO;

#define ADMIN_GET_CHARAC_TYPE_SEND	 (BYTE)0	// �׳� ���ۿ�
#define ADMIN_GET_CHARAC_TYPE_MOVETO (BYTE)1	// ������

typedef struct
{
	BYTE		Type;		// see above
	UID32_t		AdminCharacterUniqueNumber;
	char		AccountName[SIZE_MAX_ACCOUNT_NAME];
	char		CharacterName[SIZE_MAX_CHARACTER_NAME];
	MAP_CHANNEL_INDEX	MapChannelIndex;
	AVECTOR3	Position;
	BYTE		Level;
} MSG_FI_ADMIN_GET_CHARACTER_INFO_OK;

typedef struct
{
	UID32_t			CharacterUniqueNumber;
	MAP_CHANNEL_INDEX	MapChannelIndex;			// admin�� ���̸�
	AVECTOR3		Position;						// admin�� ��ǥ
} MSG_FI_ADMIN_CALL_CHARACTER;	// I -> F

typedef struct
{
	UID32_t			AdminCharacterUniqueNumber;
	MAP_CHANNEL_INDEX	MapChannelIndex;			// Target�� ���̸�
	AVECTOR3		Position;						// Target�� ��ǥ
} MSG_FI_ADMIN_MOVETO_CHARACTER;

typedef struct
{
	MapIndex_t		MapIndex;		// MAP_INDEX_ALL �̸� ��� �� �ǹ�
	BitFlag16_t		MapWeather;
	BOOL			OnOff;
} MSG_FI_ADMIN_CHANGE_WEATHER;

///////////////////////////////////////////////////////////////////////////////
// IC_ADMIN
typedef struct
{
	char				CharacterName[SIZE_MAX_CHARACTER_NAME];
	MAP_CHANNEL_INDEX	MapChannelIndex;				// admin�� ���̸�
	AVECTOR3			Position;						// admin�� ��ǥ
} MSG_IC_ADMIN_CALL_CHARACTER;	// I -> C

typedef struct
{
	INT					TotalUserCount;				// ������ ��ü�� ����� ��
} MSG_IC_ADMIN_GET_SERVER_STAT_OK;					// I -> C

typedef struct
{
	char				GuildName[SIZE_MAX_GUILD_NAME];
	MAP_CHANNEL_INDEX	MapChannelIndex;				// admin�� ���̸�
	AVECTOR3			Position;						// admin�� ��ǥ
} MSG_IC_ADMIN_CALL_GUILD;	// I -> C

struct MSG_IC_ADMIN_CALLGM_INFO_OK		// 2006-05-08 by cmkwon
{
	int		nCallGMTotalCount;
};

#define SIZE_MAX_CALLGM_LIST					1000			// 2006-05-08 by cmkwon
#define SIZE_MAX_CALLGM_BRING_COUNT				10				// 2006-05-08 by cmkwon
struct SCALLGM			// 2006-05-08 by cmkwon
{
	UID32_t			CallerCharacterUID;
	BYTE			CallerInflTy;			// 2007-11-19 by cmkwon, �����ý��� ������Ʈ - SCALLGM ����ü�� ���� �ʵ� �߰�
	char			szCallerCharacterName[SIZE_MAX_CHARACTER_NAME];
	ATUM_DATE_TIME	atimeCallTime;
	char			szCallGMDescription[SIZE_MAX_CHAT_MESSAGE];
};
struct MSG_IC_ADMIN_CALLGM_VIEW_OK		// 2006-05-08 by cmkwon
{
	int		nCallGMCount;
	ARRAY_(SCALLGM);
};
typedef MSG_IC_ADMIN_CALLGM_VIEW_OK		 MSG_IC_ADMIN_CALLGM_BRING_OK;		// 2006-05-08 by cmkwon


///////////////////////////////////////////////////////////////////////////////
// FC_ADMIN
typedef struct
{
	MAP_CHANNEL_INDEX	CurrentMapChannelIndex;		// ���� ��
	INT					CurrentUserCount;			// ���� ���� ����� ��
	INT					CurrentBCUUserCount;
	INT					CurrentANIUserCount;
} MSG_FC_ADMIN_GET_SERVER_STAT_OK;					// F -> C

///////////////////////////////////////////////////////////////////////////////
// ERROR
typedef struct
{
	MessageType_t	MsgType;	// ������ �Ͼ�� �� ó�����̾��� Message Type
	Err_t			ErrorCode;			// 2 bytes
	BOOL			CloseConnection;	// Client���� ������ �������� ���� ����
	INT				ErrParam1;			// general-purpose err parameter 1
	INT				ErrParam2;			// general-purpose err parameter 2
	USHORT			StringLength;		// 2 bytes
	//char*	String;				// error string
} MSG_ERROR;

///////////////////////////////////////////////////////////////////////////////
// Log Server Protocol (T0: 0x20~)
///////////////////////////////////////////////////////////////////////////////
/*
- Item:		����(�ŷ�,�ݴ°��), ������â->â��,â��->������â, �����Ǻн�(�ŷ��� �������, �ٴڿ� ����߸� ��� ��ǥ)
- Skill:	����, ������ �н�
- Level:	Up(n), down(-n)
- Exp:		Up(n), down(-n)
- Stat:		6��(AttackPart, DefensePart, FuelPart, SoulPart, ShieldPart, DodgePart), type,n
- EndGame:	���ӽð�, ����ð�, IP, PlayTime, ��ǥ
*/


// 2010-04-20 by cmkwon, �ű� ��Ű �ӽ� ���� - 
// enum EN_ENCHANT_LOGTYPE
// {
// 	ENCHANT_LOGTYPE_FAIL		= 0,
// 	ENCHANT_LOGTYPE_SUCCESS		= 1,
// 	ENCHANT_LOGTYPE_TARGETITEM	= 2,
// 	ENCHANT_LOGTYPE_ATTACHITEM	= 3,
// 	ENCHANT_LOGTYPE_INCREASE_PROBABILITY = 4		// 2009-01-19 by dhjin, ��þƮ Ȯ�� ����, 10��þ �Ĺ� ī��
// };
///////////////////////////////////////////////////////////////////////////////
// 2010-04-20 by cmkwon, �ű� ��Ű �ӽ� ���� - 
enum EN_ENCHANT_LOGTYPE
{
	ENCHANT_LOGTYPE_UNKNOWN = 0,		// 
	ENCHANT_LOGTYPE_ENCHANT_FAIL = 100,		// ��æƮ ����
	ENCHANT_LOGTYPE_ENCHANT_SUCCESS = 101,		// ��æƮ ����
	ENCHANT_LOGTYPE_ENCHANT_INIT_FAIL = 110,		// ��æƮ �ʱ�ȭ ����
	ENCHANT_LOGTYPE_ENCHANT_INIT_SUCCESS = 111,
	ENCHANT_LOGTYPE_GAMBLE_PREFIX_FAIL = 120,		// ���� �׺� ����
	ENCHANT_LOGTYPE_GAMBLE_PREFIX_SUCCESS = 121,
	ENCHANT_LOGTYPE_GAMBLE_SUFFIX_FAIL = 122,		// ���� �׺� ����
	ENCHANT_LOGTYPE_GAMBLE_SUFFIX_SUCCESS = 123,
	ENCHANT_LOGTYPE_GAMBLE_PREFIX_INIT_FAIL = 130,		// ���� �׺� �ʱ�ȭ ����
	ENCHANT_LOGTYPE_GAMBLE_PREFIX_INIT_SUCCESS = 131,
	ENCHANT_LOGTYPE_GAMBLE_SUFFIX_INIT_FAIL = 132,		// ���� �׺� �ʱ�ȭ ����
	ENCHANT_LOGTYPE_GAMBLE_SUFFIX_INIT_SUCCESS = 133
};
char* GetEnchatLogTypeString(int i_nEnchantLogTy);		// 2010-04-20 by cmkwon, �ű� ��Ű �ӽ� ���� - 
int GetEnchantLogType(ITEM* i_pEnchantItemInfo, BOOL i_bSuccessFlag);



// 2013-07-01 by bckim, 10��æƮ �̸� ������ī��ó��, �α��߰�, ��� ����
enum EN_TRY_ENCHANT_SUCCESS_LOGTYPE
{
	TRY_ENCHANT_FAIL = 0,
	TRY_ENCHANT_SUCCESS = 1,
	TRY_ENCHANT_PREVENT_5 = 5,
	TRY_ENCHANT_PREVENT_10 = 10
};
char* GetTryEnchantSuccessTypeString(int i_nSuccessType);
// End. 2013-07-01 by bckim, 10��æƮ �̸� ������ī��ó��, �α��߰�, ��� ����


// CONNECTION LOG(0x00~)
#define T1_FL_LOG_LOGIN							0x00	// 0 - �α���
#define T1_FL_LOG_LOGOUT						0x01	// 1 - �α׾ƿ�
// USER LOG(0x10~)
#define T1_FL_LOG_LEVEL							0x10	// 16 - ���� ��ȭ
#define T1_FL_LOG_EXP							0x11	// 17 - ����ġ ��ȭ
#define T1_FL_LOG_STAT							0x12	// 18 - ���� ���
#define T1_FL_LOG_GAME_START					0x13	// 19 - ���� ����
#define T1_FL_LOG_GAME_END						0x14	// 20 - ���� ����
#define T1_FL_LOG_QUEST_COMPLETION				0x15	// 21 - ����Ʈ �Ϸ�
#define T1_FL_LOG_PKWIN							0x16	// 22 - 1:1 ���� �¸�
#define T1_FL_LOG_PKLOSS						0x17	// 23 - 1:1 ���� �й�
#define T1_FL_LOG_DEAD							0x18	// 24 - ��ü ����
#define T1_FL_LOG_WARP							0x19	// 25 - ����
#define T1_FL_LOG_SPEED_HACK					0x1A	// 26 - ���ǵ� ��
#define T1_FL_LOG_CREATE_CHARACTER				0x1B	// 27 - ĳ���� ����
#define T1_FL_LOG_DELETE_CHARACTER				0x1C	// 28 - ĳ���� ����
#define T1_FL_LOG_MEMORY_HACK					0x1D	// 29 - �޸���, 2005-12-20 by cmkwon
#define T1_FL_LOG_PvEWIN						0x1E	// 30 - ���������� ��� ���� ĳ���͸� ����, 2006-03-06 by cmkwon
#define T1_FL_LOG_PvELOSS						0x1F	// 31 - ���������� ��� ���¿� ���� ����, 2006-03-06 by cmkwon

// ITEM LOG(0x20~)
#define T1_FL_LOG_ITEM_CHARACTER_ITEM			0x20	// 32 - ��� ���� ������ ����
#define T1_FL_LOG_ITEM_GET_ITEM					0x21	// 33 - Drop Item ����
#define T1_FL_LOG_ITEM_TRADE_SEND				0x22	// 34 - ������ �ŷ�: �ֱ�
#define T1_FL_LOG_ITEM_TRADE_RECV				0x23	// 35 - ������ �ŷ�: �ޱ�
#define T1_FL_LOG_ITEM_THROWAWAY_ITEM			0x24	// 36 - ������ ������
#define T1_FL_LOG_ITEM_BUY_ITEM					0x25	// 37 - ������ ����
#define T1_FL_LOG_ITEM_SELL_ITEM				0x26	// 38 - ������ �Ǹ�
#define T1_FL_LOG_ITEM_USE_ITEM					0x27	// 39 - ������ ���
#define T1_FL_LOG_ITEM_USE_ENERGY				0x28	// 40 - �������� ������ ���
#define T1_FL_LOG_ITEM_USE_ENCHANT				0x29	// 41 - ��æƮ�� ������ ���
#define T1_FL_LOG_ITEM_ADD_ITEM_BY_ADMIN		0x2A	// 42 - ����� ���� ����
#define T1_FL_LOG_ITEM_DEL_ITEM_BY_ADMIN		0x2B	// 43 - ����� ���� ����
#define T1_FL_LOG_ITEM_ADD_ITEM_BY_COMMAND		0x2C	// 44 - ���ɾ ���� ����
#define T1_FL_LOG_ITEM_INSERT_TO_STORE			0x2D	// 45 - â���� ����
#define T1_FL_LOG_ITEM_DRAW_FROM_STORE			0x2E	// 46 - â������ ������
#define T1_FL_LOG_ITEM_STORE_ITEM				0x2F	// 47 - â�� ���� ������ ����, â�� ���� ������
#define T1_FL_LOG_ITEM_USE_MIX					0x30	// 48 - ����
#define T1_FL_LOG_ITEM_USE_CHANGE_CHARACTER_NAME_ORIGIN	0x31	// 49 - ĳ���� ����� �������� ĳ����
#define T1_FL_LOG_ITEM_USE_CHANGE_CHARACTER_NAME_NEW	0x32	// 50 - ĳ���� ����� ���ο� ĳ����
#define T1_FL_LOG_ITEM_BAZAAR_SEND				0x33	// 51 - ���λ��� �ŷ�: �ֱ�, 2006-07-27 by cmkwon
#define T1_FL_LOG_ITEM_BAZAAR_RECV				0x34	// 52 - ���λ��� �ŷ�: �ޱ�, 2006-07-27 by cmkwon
#define T1_FL_LOG_ITEM_INSERT_TO_GUILDSTORE		0x35	// 53 - ���� â���� ����, 2006-09-27 by dhjin
#define T1_FL_LOG_ITEM_DRAW_FROM_GUILDSTORE		0x36	// 54 - ���� â������ ������, 2006-09-27 by dhjin
#define T1_FL_LOG_ITEM_SPI						0x37	// 55 - ĳ���� ������ �ٿ� SPI Log, 2006-10-27 by cmkwon
#define T1_FL_LOG_ITEM_GET_ITEM_BY_ITEMEVENT	0x38	// 56 - ItemEvent�� ���� ������ �߰�, 2007-01-11 by cmkwon
#define T1_FL_LOG_QUEST_COMPENSATION			0x39	// 57 - ����Ʈ ����, 2007-01-16 by dhjin
#define T1_FL_LOG_WARPOINT						0x3A	// 58 - WarPoint ����, 2007-05-15 by dhjin
#define T1_FL_LOG_ARENA_TEAM_MATCH				0x3B	// 59 - Arena �� ��Ī, 2007-06-11 by dhjin
#define T1_FL_LOG_TUTORIAL_COMPLETION			0x3C	// 60 - Tutorial, 2007-07-06 by dhjin
#define T1_FL_LOG_OUTPOST_START					0x3D	// 61 - OutPost���� �α�, 2007-10-02 by dhjin
#define T1_FL_LOG_OUTPOST_END					0x3E	// 62 - OutPost���� �α�, 2007-10-02 by dhjin
#define T1_FL_LOG_EXPEDIENCYFUND				0x3F	// 63 - �ǰ��� ��/�� �α�, 2007-10-02 by dhjin

#define T1_FL_LOG_ITEM_BUY_CASH_PRICE			0x46	// 70 - // 2012-10-16 by bckim, ĳ�������� �������� Log �߰�
#define T1_FL_LOG_ITEM_CHARACTER_ITEM_GUILDSTORE_RESULT 0x49 // 73 - // 2012-12-17 by bckim, ���â�� ������ �̵� ���� �߰��α� 
// 2012-11-21 by bckim, �������߰�, ��æƮ���������ű��
#define T1_FL_LOG_ITEM_ENCHANT_BY_ADMIN			0x47	// 71 - ������ ��æƮ ���� Log �߰�
#define T1_FL_LOG_ITEM_DISENCHANT_BY_ADMIN		0x48	// 72 - ������ ��æƮ ���� Log �߰�
// 2012-11-21 by bckim, �������߰�, ��æƮ���������ű��. End 

#define T1_FL_LOG_ITEM_TRY_ENCHANT_INFO			0x4B	// 75 - // 2013-07-01 by bckim, 10��æƮ �̸� ������ī��ó��, �α��߰�, ��� ����
#define T1_FL_LOG_ITEM_DISSOLUTION_ITEM			0x4C	// 76 - // 2013-08-05 by bckim, ���� �������� �α� �߰�


// ETC LOG(0x40~)
#define T1_FL_LOG_SERVER_INFO_MAP				0x40	// 64 - �ʺ� ������
#define T1_FL_LOG_SERVER_INFO_TOTAL				0x41	// 65 - 
#define T1_FL_LOG_HACKING_LOG					0x42	// 66 - 
#define T1_FL_LOG_LIVE_DELETED_CHARACTER		0x43	// 67 - ������ �ɸ���, 2007-02-22 by dhjin
#define T1_FL_LOG_EVENT_PARTICIPATION_RATE		0x44	// 68 - // 2010-06-01 by shcho, GLogDB ���� -

// MONSTER LOG(0x50~)
#define T1_FL_LOG_MONSTER_BOSS					0x50	// 80 - ������ ����
#define T1_FL_LOG_MS_WAR						0x51	// 81 - // 2008-04-01 by dhjin, ����, ������ ����â ��ȹ�� - 
#define T1_FL_LOG_SP_WAR						0x52	// 82 - // 2008-04-01 by dhjin, ����, ������ ����â ��ȹ�� - 
#define T1_FL_LOG_WAR_CONTRIBUTION				0x53	// 83 - // 2008-12-23 by dhjin, ���� ���� �߰���
#define T1_FL_LOG_WAR_CONTRIBUTION_GEAR			0x54	// 84 - // 2008-12-23 by dhjin, ���� ���� �߰���

// 2013-11-25 by jhseol&bckim, �ŷ��� - GameLog �߰�
#define T1_FL_LOG_MARKET_REGISTRATION			0x55	// 85 - ���
#define T1_FL_LOG_MARKET_BUY					0x56	// 86 - ����
#define T1_FL_LOG_MARKET_GET					0x57	// 87 - ȸ��
// end 2013-11-25 by jhseol&bckim, �ŷ��� - GameLog �߰�

#define T1_FL_LOG_DELETE_CHARACTER_BY_ADMIN		0x58	// 88 - ������ ĳ���� ���� - 2014-01-21 by jekim, ������ ĳ���� ���� �����ϰ� �ϱ�.

// 2014-01-03 by jhseol&bckim, �ı������ - GameLog �߰�
#define T1_FL_LOG_DESTROY_AUCTION_TENDER		0x59	// 89 - ����
#define T1_FL_LOG_DESTROY_AUCTION_FIX			0x5A	// 90 - ����
#define T1_FL_LOG_DESTROY_AUCTION_GET			0x5B	// 91 - ����ǰ ȸ��
// end 2014-01-03 by jhseol&bckim, �ı������ - GameLog �߰�

//
#define T1_FL_LOG_SERVER_INTEGRAION							0x80	// 128 - ���� ���� ���� - ĳ���� ���� ó�� ��
#define T1_FL_LOG_SERVER_INTEGRAION_GUILD_STORE_ITEMS		0x81	// 129 - ���� ���� ���� - ���� â�� ������ ���� ó����, // 2007-02-15 by cmkwon
#define T1_FL_LOG_SERVER_INTEGRAION_ONLY_CASH_STORE_ITEMS	0x82	// 130 - ���� ���� ���� - ĳ�� �����۸� ���ռ����� DB �� �̵�, // 2008-02-28 by cmkwon, ���� ������ ���� ĳ�� �����۸� �̵��ϴ� ���ν���

#define T1_FL_LOG_INFLWAR_START							0x90	// 144 - // 2007-10-16 by cmkwon, �α� �߰� - ������ �α�
#define T1_FL_LOG_INFLWAR_END							0x91	// 145 - // 2007-10-16 by cmkwon, �α� �߰� - ������ �α�
#define T1_FL_LOG_OUTPOSTWAR_RESET_START				0x95	// 149 - // 2007-10-16 by cmkwon, �α� �߰� - ���������� �α�
#define T1_FL_LOG_OUTPOSTWAR_RESET_DESTROY				0x96	// 150 - // 2007-10-16 by cmkwon, �α� �߰� - ���������� �α�
#define T1_FL_LOG_OUTPOSTWAR_RESET_COMPLETE				0x97	// 151 - // 2007-10-16 by cmkwon, �α� �߰� - ���������� �α�
#define T1_FL_LOG_OUTPOSTWAR_PROTECTOR_DESTROY			0x98	// 152 - // 2007-10-16 by cmkwon, �α� �߰� - ���������� �α�
#define T1_FL_LOG_OUTPOSTWAR_SET_NEXTTIME				0x99	// 153 - // 2007-10-16 by cmkwon, �α� �߰� - ���������� �α�

#define T1_FL_LOG_POLL_VOTE								0xA0	// 160 - // 2007-11-08 by dhjin, ��ǥ �α� 
#define T1_FL_LOG_POLL_DELETE_LEADERCANDIDATE			0xA1	// 161 - // 2007-11-08 by dhjin, ������ �⸶ Ż�� �α�

#define T1_FL_LOG_DISMEMBER_GUILD						0xA2	// 162 - // 2007-11-09 by dhjin
#define T1_FL_LOG_NOTIFY_MSG_DELETE						0xA3	// 163 - // 2007-11-28 by cmkwon, �����ý��� ���� -
#define T1_FL_LOG_USE_COUPON							0xA4	// 164 - // 2008-01-23 by cmkwon, S_F, S_L: ���� ��� ���� �α׿� �߰� - ���� ���� �α�

#define T1_FL_LOG_ITEM_GIFT_SEND						0xB0	// 176 - // 2007-11-13 by cmkwon, �����ϱ� ��� �߰� - �����ϱ� : �ֱ�
#define T1_FL_LOG_ITEM_GIFT_RECV						0xB1	// 177 - // 2007-11-13 by cmkwon, �����ϱ� ��� �߰� - �����ϱ� : �ޱ�
#define T1_FL_LOG_ITEM_REARRANGE_DELETE_ITEM			0xB2	// 178 - // 2007-11-29 by cmkwon, ī���ͺ������� �������� ���� �α� ����� - ������ ������
#define T1_FL_LOG_ITEM_REARRANGE_ITEM					0xB3	// 179 - // 2007-11-29 by cmkwon, ī���ͺ������� �������� ���� �α� ����� - ������ ������
#define T1_FL_LOG_ITEM_ATTACH_ITEM						0xB4	// 180 - // 2008-01-23 by cmkwon, S_F, S_L: ����/�������� ���� �α׿� �߰� - ����
#define T1_FL_LOG_ITEM_DETACH_ITEM						0xB5	// 181 - // 2008-01-23 by cmkwon, S_F, S_L: ����/�������� ���� �α׿� �߰� - ��������
#define T1_FL_LOG_ITEM_DELETE							0xB6	// 182 - // 2008-01-23 by cmkwon, S_F, S_L: ����/�������� ���� �α׿� �߰� - ������ ������(��ȿ�ð� ���)

#define T1_FL_LOG_LUCKY_DROP							0xC0	// 192 - // 2009-03-31 by dhjin, ��Ű�ӽ� �α�
#define T1_FL_LOG_INFINITY_START						0xC1	// 193 - // 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���ӷα� �߰�, ���� ���� ���� 
#define T1_FL_LOG_INFINITY_START_ITEM					0xC2	// 194 - // 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���ӷα� �߰�, ���۽� ������ ���� ����
#define T1_FL_LOG_INFINITY_CINEMA						0xC3	// 195 - // 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���ӷα� �߰�, ���� �α�
#define T1_FL_LOG_MONSTER_SKILL							0xC4	// 196 - // 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���ӷα� �߰�, ���� ��ų ����
#define T1_FL_LOG_HPACTION_TALK							0xC5	// 197 - // 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���ӷα� �߰�, ���� ��ȭ ����
#define T1_FL_LOG_INFINITY_FIN							0xC6	// 198 - // 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���ӷα� �߰�, ���� ���� ���� 
#define T1_FL_LOG_INFINITY_FIN_ITEM						0xC7	// 199 - // 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���ӷα� �߰�, ����� ������ ���� ����
#define T1_FL_LOG_INFINITY_FIN_ALIVE_KEY_MONSTER		0xC8	// 200 - // 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���ӷα� �߰�, ����� ����ִ� ���� ����
#define T1_FL_LOG_INFINITY_LEAVE_ITEM					0xC9	// 201 - // 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���ӷα� �߰�, ���� Ż��� ������ ���� ����

#define T1_FL_LOG_BLOCK_ACCOUNT							0xD0	// 208 - // 2008-01-30 by cmkwon, ���� ���� �α� ����� ���� - ���� ����
#define T1_FL_LOG_UNBLOCK_ACCOUNT						0xD1	// 209 - // 2008-01-30 by cmkwon, ���� ���� �α� ����� ���� - ���� ���� ����

#define	T1_FL_GLOG_NEW_ACCOUNT_INFO						0xD2	// 210 - // 2013-03-14 by bckim, Glog ����߰�

#define T1_FL_LOG_PET_LEVEL								0xD5	// 213 - // 2011-09-15 by hskim, ��Ʈ�� �ý��� 2�� - ��Ʈ�� ���� ����

#define T1_FL_LOG_CONNECT_USER_NEW						0xD6	// 214 - // 2012-01-08 by hskim, GLog 2�� - ���� �ű� ����
#define T1_FL_LOG_CONNECT_USER_LOGIN					0xD7	// 215 - // 2012-01-08 by hskim, GLog 2�� - ���� ����

#define T1_FL_LOG_STATISTICS_MONEY						0xD8	// 216 - // 2012-01-16 by hskim, ��� - ȭ��

#define T1_FL_LOG_FIXED_TERM_SHAPE_START				0xD9	// 217 - // 2012-10-10 by hskim, �Ⱓ�� �Ӽ� ���� (�Ⱓ�� ����)
#define T1_FL_LOG_FIXED_TERM_SHAPE_END					0xDA	// 218 - // 2012-10-10 by hskim, �Ⱓ�� �Ӽ� ���� (�Ⱓ�� ����)

// 2013-1-02 by khkim, GLog
#define T1_FL_LOG_ACCOUNTCONNECT						0xDB		 
#define T1_FL_LOG_CHARDATA								0xDC	
#define	T1_FL_LOG_ITEM									0xDD
#define	T1_FL_LOG_ITEMSTATE								0xDE
#define	T1_FL_LOG_SERVER								0xDF
// end 2013-1-02 by khkim, GLog


#define T1_FL_LOG_ITEM_INITIALIZED_GUILD_STORE			0xE0	// 224 - // 2012-12-20 by bckim, �����ʱ�ȭ�� ���â���������� ����忡�� �Ű����� ������ �α�
#define T1_FL_LOG_ITEM_GET_WITH_SAME_ACCOUNT			0xE1	// 225 - // 2012-12-27 by bckim, ���ϰ���, ������ �ɸ��Ͱ��� ������ �̵��� �α��߰�

#define T1_FL_LOG_COLLECTION_STATE						0xE2	// 226 - // 2013-05-31 by jhseol,bckim �Ƹ� �÷��� - GameLog �߰�
#define T1_FL_LOG_COLLECTION_SHAPE_CHANGE				0xE3	// 227 - // 2013-05-31 by jhseol,bckim �Ƹ� �÷��� - GameLog �߰�
#define T1_FL_LOG_ACCOUNT_INFL_CHANGE_BY_ADMIN			0xE4	// 228 - // 2013-07-26 by jhseol, Ÿ ���� ���º��� - GameLog �߰�

#define T1_FL_LOG_BUGTRAP_ACCEPT						0xE5	// 229		// 2014-01-27 by bckim, ���� Ʈ��
#define T1_FL_LOG_USE_SKILL								0xE6	// 230 - // 2014-03-31 by jekim, ��ų ��� �α�

#define T1_FL_LOG_ALL_MONSTER_KILL_LOG					0xE7	// 230		// 2014-03-31 by bckim, ��� ���� ų�α� ( ĳ���� ��û)

#define T1_FL_LOG_MONITOR_RELOAD_VERSION_INFO_OK		0xFE	// 254 - // 2013-03-14 by jhseol, �������� ���ε� �� ���� ��� IP����Ʈ�� ����
#define T1_FL_LOG_START_FIELD_SERVER			0xFF	// 255 - FieldServer Start



#define T_FL_LOG_LOGIN					(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_LOGIN)				// �α���
#define T_FL_LOG_LOGOUT					(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_LOGOUT)			// �α׾ƿ�
#define T_FL_LOG_LEVEL					(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_LEVEL)				// ���� ��ȭ
#define T_FL_LOG_EXP					(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_EXP)				// ����ġ ��ȭ
#define T_FL_LOG_STAT					(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_STAT)				// ���� ���
#define T_FL_LOG_GAME_START				(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_GAME_START)		// ���� ����
#define T_FL_LOG_GAME_END				(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_GAME_END)			// ���� ����
#define T_FL_LOG_QUEST_COMPLETION		(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_QUEST_COMPLETION)	// ����Ʈ �Ϸ�
#define T_FL_LOG_QUEST_COMPENSATION		(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_QUEST_COMPENSATION)// ����Ʈ ����
#define T_FL_LOG_PKWIN					(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_PKWIN)				// 1:1 ���� �¸�
#define T_FL_LOG_PKLOSS					(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_PKLOSS)			// 1:1 ���� �й�
#define T_FL_LOG_DEAD					(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_DEAD)				// ��ü ����
#define T_FL_LOG_WARP					(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_WARP)				// ����
#define T_FL_LOG_SPEED_HACK				(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_SPEED_HACK)		// ���ǵ� ��
#define T_FL_LOG_CREATE_CHARACTER		(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_CREATE_CHARACTER)	// ĳ���� ����
#define T_FL_LOG_DELETE_CHARACTER		(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_DELETE_CHARACTER)	// ĳ���� ����
#define T_FL_LOG_MEMORY_HACK			(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_MEMORY_HACK)		// 29 - �޸���, 2005-12-20 by cmkwon
#define T_FL_LOG_PvEWIN					(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_PvEWIN)			// 30 - ���������� ��� ���� ĳ���͸� ����, 2006-03-06 by cmkwon
#define T_FL_LOG_PvELOSS				(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_PvELOSS)			// 31 - ���������� ��� ���¿� ���� ����, 2006-03-06 by cmkwon

#define T_FL_LOG_ITEM_CHARACTER_ITEM	(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_ITEM_CHARACTER_ITEM)	// ��� ���� ������ ����
#define T_FL_LOG_ITEM_GET_ITEM			(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_ITEM_GET_ITEM)		// Drop Item ����
#define T_FL_LOG_ITEM_TRADE_SEND		(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_ITEM_TRADE_SEND)	// ������ �ŷ�: �ֱ�
#define T_FL_LOG_ITEM_TRADE_RECV		(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_ITEM_TRADE_RECV)	// ������ �ŷ�: �ޱ�
#define T_FL_LOG_ITEM_THROWAWAY_ITEM	(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_ITEM_THROWAWAY_ITEM)	// ������ ������

#define T_FL_LOG_ITEM_TRY_ENCHANT_INFO	(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_ITEM_TRY_ENCHANT_INFO)	// 2013-07-01 by bckim, 10��æƮ �̸� ������ī��ó��, �α��߰�, ��� ����
#define T_FL_LOG_ITEM_DISSOLUTION_ITEM	(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_ITEM_DISSOLUTION_ITEM)	// 2013-08-05 by bckim, ���� �������� �α� �߰�

#define T_FL_LOG_ITEM_BUY_ITEM			(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_ITEM_BUY_ITEM)		// ������ ����

#define T_FL_LOG_ITEM_BUY_CASH_PRICE	(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_ITEM_BUY_CASH_PRICE)	// 2012-10-16 by bckim, ĳ�������� �������� Log �߰�
#define T_FL_LOG_ITEM_CHARACTER_ITEM_GUILDSTORE_RESULT	(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_ITEM_CHARACTER_ITEM_GUILDSTORE_RESULT)	// 2012-12-17 by bckim, ���â�� ������ �̵� ���� �߰��α� 
#define T_FL_LOG_ITEM_INITIALIZED_GUILD_STORE	(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_ITEM_INITIALIZED_GUILD_STORE)	// 2012-12-20 by bckim, �����ʱ�ȭ�� ���â���������� ����忡�� �Ű����� ������ �α�
#define T_FL_LOG_ITEM_GET_WITH_SAME_ACCOUNT		(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_ITEM_GET_WITH_SAME_ACCOUNT)	// 2012-12-27 by bckim, ���ϰ���, ������ �ɸ��Ͱ��� ������ �̵��� �α��߰�

#define T_FL_LOG_ITEM_SELL_ITEM			(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_ITEM_SELL_ITEM)	// ������ �Ǹ�
#define T_FL_LOG_ITEM_USE_ITEM			(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_ITEM_USE_ITEM)		// ������ ���
#define T_FL_LOG_ITEM_USE_ENERGY		(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_ITEM_USE_ENERGY)	// �������� ������ ���
#define T_FL_LOG_ITEM_USE_ENCHANT		(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_ITEM_USE_ENCHANT)	// ��æƮ�� ������ ���
#define T_FL_LOG_ITEM_ADD_ITEM_BY_ADMIN	(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_ITEM_ADD_ITEM_BY_ADMIN)		// ����� ���� ����
#define T_FL_LOG_ITEM_DEL_ITEM_BY_ADMIN	(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_ITEM_DEL_ITEM_BY_ADMIN)		// ����� ���� ����
#define T_FL_LOG_ITEM_ADD_ITEM_BY_COMMAND	(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_ITEM_ADD_ITEM_BY_COMMAND)	// ���ɾ ���� ����
#define T_FL_LOG_ITEM_INSERT_TO_STORE	(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_ITEM_INSERT_TO_STORE)	// â���� ����
#define T_FL_LOG_ITEM_DRAW_FROM_STORE	(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_ITEM_DRAW_FROM_STORE)	// â������ ������
#define T_FL_LOG_ITEM_STORE_ITEM		(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_ITEM_STORE_ITEM)		// â�� ���� ������ ����, â�� ���� ������
#define T_FL_LOG_ITEM_USE_MIX			(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_ITEM_USE_MIX)			// ����
#define T_FL_LOG_ITEM_USE_CHANGE_CHARACTER_NAME_ORIGIN		(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_ITEM_USE_CHANGE_CHARACTER_NAME_ORIGIN)	// ĳ��������
#define T_FL_LOG_ITEM_BAZAAR_SEND		(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_ITEM_BAZAAR_SEND)	// ���λ��� �ŷ�: �ֱ�
#define T_FL_LOG_ITEM_BAZAAR_RECV		(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_ITEM_BAZAAR_RECV)	// ���λ��� �ŷ�: �ޱ�
#define T_FL_LOG_ITEM_INSERT_TO_GUILDSTORE			(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_ITEM_INSERT_TO_GUILDSTORE)		// 2006-09-27 by dhjin, ���� â�� �α� �����
#define T_FL_LOG_ITEM_DRAW_FROM_GUILDSTORE			(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_ITEM_DRAW_FROM_GUILDSTORE)		// 2006-09-27 by dhjin, ���� â�� �α� �����
#define T_FL_LOG_ITEM_SPI							(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_ITEM_SPI)							// 55 - SPI Log, 2006-10-27 by cmkwon
#define T_FL_LOG_ITEM_GET_ITEM_BY_ITEMEVENT			(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_ITEM_GET_ITEM_BY_ITEMEVENT)		// 56 - ItemEvent�� ���� ������ �߰�, 2007-01-11 by cmkwon
#define T_FL_LOG_WARPOINT							(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_WARPOINT)						// 58 - WarPoint ����, 2007-05-15 by dhjin
#define T_FL_LOG_ARENA_TEAM_MATCH					(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_ARENA_TEAM_MATCH)				// 59 - Arena �� ��Ī, 2007-06-11 by dhjin
#define T_FL_LOG_TUTORIAL_COMPLETION				(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_TUTORIAL_COMPLETION)			// 60 - Tutorial, 2007-07-06 by dhjin
#define T_FL_LOG_OUTPOST_START			(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_OUTPOST_START)				// 61 - OutPost���� �α�, 2007-10-02 by dhjin
#define T_FL_LOG_OUTPOST_END			(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_OUTPOST_END)				// 62 - OutPost���� �α�, 2007-10-02 by dhjin
#define T_FL_LOG_EXPEDIENCYFUND			(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_EXPEDIENCYFUND)			// 63 - �ǰ��� ��/�� �α�, 2007-10-02 by dhjin

#define T_FL_LOG_SERVER_INFO_MAP		(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_SERVER_INFO_MAP)
#define T_FL_LOG_SERVER_INFO_TOTAL		(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_SERVER_INFO_TOTAL)
#define T_FL_LOG_HACKING_LOG			(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_HACKING_LOG)

#define T_FL_LOG_MONSTER_BOSS			(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_MONSTER_BOSS)			// ������ ����
#define T_FL_LOG_MS_WAR					(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_MS_WAR)			// 81 - // 2008-04-01 by dhjin, ����, ������ ����â ��ȹ�� - 
#define T_FL_LOG_SP_WAR					(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_SP_WAR)			// 82 - // 2008-04-01 by dhjin, ����, ������ ����â ��ȹ�� - 
#define T_FL_LOG_WAR_CONTRIBUTION		(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_WAR_CONTRIBUTION)			// 83  - // 2008-12-23 by dhjin, ���� ���� �߰���
#define T_FL_LOG_WAR_CONTRIBUTION_GEAR	(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_WAR_CONTRIBUTION_GEAR)		// 84  - // 2008-12-23 by dhjin, ���� ���� �߰���

#define T_FL_LOG_ALL_MONSTER_KILL_LOG			(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_ALL_MONSTER_KILL_LOG)		// 2014-03-31 by bckim, ��� ���� ų�α� ( ĳ���� ��û)

// 2013-11-25 by jhseol&bckim, �ŷ��� - GameLog �߰�
#define T_FL_LOG_MARKET_REGISTRATION	(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_MARKET_REGISTRATION)		// 85 - ���
#define T_FL_LOG_MARKET_BUY				(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_MARKET_BUY)				// 86 - ����
#define T_FL_LOG_MARKET_GET				(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_MARKET_GET)				// 87 - ȸ��
// end 2013-11-25 by jhseol&bckim, �ŷ��� - GameLog �߰�

#define T_FL_LOG_DELETE_CHARACTER_BY_ADMIN (MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_DELETE_CHARACTER_BY_ADMIN)	// 88 - ������ ĳ���� ���� - 2014-01-21 by jekim, ������ ĳ���� ���� �����ϰ� �ϱ�.

// 2014-01-03 by jhseol&bckim, �ı������ - GameLog �߰�
#define T_FL_LOG_DESTROY_AUCTION_TENDER				(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_DESTROY_AUCTION_TENDER)	// 89 - ����
#define T_FL_LOG_DESTROY_AUCTION_FIX				(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_DESTROY_AUCTION_FIX)		// 90 - ����
#define T_FL_LOG_DESTROY_AUCTION_GET				(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_DESTROY_AUCTION_GET)		// 91 - ����ǰ ȸ��
// end 2014-01-03 by jhseol&bckim, �ı������ - GameLog �߰�

#define T_FL_LOG_INFLWAR_START					(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_INFLWAR_START)					// 144 - // 2007-10-16 by cmkwon, �α� �߰� - ������ �α�
#define T_FL_LOG_INFLWAR_END					(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_INFLWAR_END)					// 145 - // 2007-10-16 by cmkwon, �α� �߰� - ������ �α�
#define T_FL_LOG_OUTPOSTWAR_RESET_START			(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_OUTPOSTWAR_RESET_START)		// 151 - // 2007-10-16 by cmkwon, �α� �߰� - ���������� �α�
#define T_FL_LOG_OUTPOSTWAR_RESET_DESTROY		(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_OUTPOSTWAR_RESET_DESTROY)		// 154 - // 2007-10-16 by cmkwon, �α� �߰� - ���������� �α�
#define T_FL_LOG_OUTPOSTWAR_RESET_COMPLETE		(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_OUTPOSTWAR_RESET_COMPLETE)		// 152 - // 2007-10-16 by cmkwon, �α� �߰� - ���������� �α�
#define T_FL_LOG_OUTPOSTWAR_PROTECTOR_DESTROY	(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_OUTPOSTWAR_PROTECTOR_DESTROY)	// 153 - // 2007-10-16 by cmkwon, �α� �߰� - ���������� �α�
#define T_FL_LOG_OUTPOSTWAR_SET_NEXTTIME		(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_OUTPOSTWAR_SET_NEXTTIME)		// 156 - // 2007-10-16 by cmkwon, �α� �߰� - ���������� �α�

#define T_FL_LOG_POLL_VOTE						(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_POLL_VOTE)						// 160 - // 2007-11-08 by dhjin, ��ǥ �α�
#define T_FL_LOG_POLL_DELETE_LEADERCANDIDATE	(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_POLL_DELETE_LEADERCANDIDATE)	// 161 - // 2007-11-08 by dhjin, ������ �⸶ Ż�� �α�

#define T_FL_LOG_DISMEMBER_GUILD				(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_DISMEMBER_GUILD)		// 162 - // 2007-11-09 by dhjin, ���� ��ü�α�
#define T_FL_LOG_NOTIFY_MSG_DELETE				(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_NOTIFY_MSG_DELETE)		// 163 - // 2007-11-28 by cmkwon, �����ý��� ���� -
#define T_FL_LOG_USE_COUPON						(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_USE_COUPON)			// 164 - // 2008-01-23 by cmkwon, S_F, S_L: ���� ��� ���� �α׿� �߰� - ���� ���� �α�

#define T_FL_LOG_ITEM_ATTACH_ITEM				(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_ITEM_ATTACH_ITEM)		// 180 - // 2008-01-23 by cmkwon, S_F, S_L: ����/�������� ���� �α׿� �߰� - ����
#define T_FL_LOG_ITEM_DETACH_ITEM				(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_ITEM_DETACH_ITEM)		// 181 - // 2008-01-23 by cmkwon, S_F, S_L: ����/�������� ���� �α׿� �߰� - ��������
#define T_FL_LOG_ITEM_DELETE					(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_ITEM_DELETE)			// 182 - // 2008-01-23 by cmkwon, S_F, S_L: ����/�������� ���� �α׿� �߰� - ������

#define T_FL_LOG_LUCKY_DROP						(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_LUCKY_DROP)			// 192 - // 2009-03-31 by dhjin, ��Ű�ӽ� �α�

#define T_FL_LOG_INFINITY_START					(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_INFINITY_START)			// 193 - // 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���ӷα� �߰�, ���� ���� ���� 
#define T_FL_LOG_INFINITY_START_ITEM			(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_INFINITY_START_ITEM)		// 194 - // 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���ӷα� �߰�, ���۽� ������ ���� ����
#define T_FL_LOG_INFINITY_CINEMA				(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_INFINITY_CINEMA)			// 195 - // 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���ӷα� �߰�, ���� �α�
#define T_FL_LOG_MONSTER_SKILL					(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_MONSTER_SKILL)				// 196 - // 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���ӷα� �߰�, ���� ��ų ����
#define T_FL_LOG_HPACTION_TALK					(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_HPACTION_TALK)				// 197 - // 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���ӷα� �߰�, ���� ��ȭ ����
#define T_FL_LOG_INFINITY_FIN					(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_INFINITY_FIN)				// 198 - // 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���ӷα� �߰�, ���� ���� ���� 
#define T_FL_LOG_INFINITY_FIN_ITEM				(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_INFINITY_FIN_ITEM)			// 199 - // 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���ӷα� �߰�, ����� ������ ���� ����
#define T_FL_LOG_INFINITY_FIN_ALIVE_KEY_MONSTER		(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_INFINITY_FIN_ALIVE_KEY_MONSTER)	// 200 - // 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���ӷα� �߰�, ����� ����ִ� ���� ����
#define T_FL_LOG_INFINITY_LEAVE_ITEM			(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_INFINITY_LEAVE_ITEM)		// 201 - // 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���ӷα� �߰�, ���� Ż��� ������ ���� ����

#define T_FL_LOG_PET_LEVEL						(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_PET_LEVEL)					// 213 - // 2011-09-15 by hskim, ��Ʈ�� �ý��� 2�� - ��Ʈ�� ���� ����

#define T_FL_LOG_CONNECT_USER_NEW				(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_CONNECT_USER_NEW)			// 214 - // 2012-01-08 by hskim, GLog 2�� - ���� �ű� ����
#define T_FL_LOG_CONNECT_USER_LOGIN				(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_CONNECT_USER_LOGIN)		// 215 - // 2012-01-08 by hskim, GLog 2�� - ���� ����

#define T_FL_LOG_STATISTICS_MONEY				(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_STATISTICS_MONEY)			// 216 - // 2012-01-16 by hskim, ��� - ȭ��

#define T_FL_LOG_FIXED_TERM_SHAPE_START			(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_FIXED_TERM_SHAPE_START)	// 217 - // 2012-10-10 by hskim, �Ⱓ�� �Ӽ� ���� (�Ⱓ�� ����)
#define T_FL_LOG_FIXED_TERM_SHAPE_END			(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_FIXED_TERM_SHAPE_END)		// 218 - // 2012-10-10 by hskim, �Ⱓ�� �Ӽ� ���� (�Ⱓ�� ����)

#define T_FL_LOG_START_FIELD_SERVER				(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_START_FIELD_SERVER)		// FieldServer Start

// start 2012-10-08 by khkim, GLog
#define T_FL_LOG_ACCOUNTCONNECT					(MessageType_t)((T0_FL_LOG<<8)| T1_FL_LOG_ACCOUNTCONNECT)			// 218		2012-10-08 by khkim, GLog
#define T_FL_LOG_CHARDATA						(MessageType_t)((T0_FL_LOG<<8)| T1_FL_LOG_CHARDATA)					// 219		
#define T_FL_LOG_ITEM							(MessageType_t)((T0_FL_LOG<<8)| T1_FL_LOG_ITEM)						// 220
#define T_FL_LOG_ITEMSTATE						(MessageType_t)((T0_FL_LOG<<8)| T1_FL_LOG_ITEMSTATE)				// 221	
#define T_FL_LOG_SERVER							(MessageType_t)((T0_FL_LOG<<8)| T1_FL_LOG_SERVER)					// 222
// end 2012-10-08 by khkim, GLog

#define T_FL_GLOG_NEW_ACCOUNT_INFO				(MessageType_t)((T0_FL_LOG<<8)|T1_FL_GLOG_NEW_ACCOUNT_INFO)			// 210		// 2013-03-14 by bckim, Glog ����߰�

#define T_FL_LOG_COLLECTION_STATE				(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_COLLECTION_STATE)			// 226		// 2013-05-31 by jhseol,bckim �Ƹ� �÷��� - GameLog �߰�
#define T_FL_LOG_COLLECTION_SHAPE_CHANGE		(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_COLLECTION_SHAPE_CHANGE)	// 227		// 2013-05-31 by jhseol,bckim �Ƹ� �÷��� - GameLog �߰�
#define T_FL_LOG_ACCOUNT_INFL_CHANGE_BY_ADMIN		(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_ACCOUNT_INFL_CHANGE_BY_ADMIN)	// 228 - // 2013-07-26 by jhseol, Ÿ ���� ���º��� - GameLog �߰�

#define T_FL_LOG_BUGTRAP_ACCEPT					(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_BUGTRAP_ACCEPT)			// 229		// 2014-01-27 by bckim, ���� Ʈ��

#define T_FL_LOG_USE_SKILL						(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_USE_SKILL)						// 230		// 2014-03-31 by jekim, ��ų ��� �α�

#define T_FL_LOG_MONITOR_RELOAD_VERSION_INFO_OK	(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_MONITOR_RELOAD_VERSION_INFO_OK)	// 254 - // 2013-03-14 by jhseol, �������� ���ε� �� ���� ��� IP����Ʈ�� ����

////////////////////////////////
// CONNECTION LOG(0x00~)
struct MSG_FL_LOG_LOGIN
{
	UID32_t	AccountUniqueNumber;
	CHAR	AccountName[SIZE_MAX_ACCOUNT_NAME];
	BYTE	IPAddress[4];
	CHAR	ServerGroupName[SIZE_MAX_SERVER_NAME];
#ifdef S_ARARIO_HSSON
	CHAR	PublisherName[SIZE_MAX_GAME_PUBLISHER_NAME];				// 2010-11 by dhjin, �ƶ󸮿� ä�θ� �α���.
#endif
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		sprintf(o_szLogString, "%s|%u|%s|%d.%d.%d.%d|%s\r\n", GetGameLogTypeString(i_nLogType), AccountUniqueNumber, AccountName
			, IPAddress[0], IPAddress[1], IPAddress[2], IPAddress[3], ServerGroupName);
		return o_szLogString;
	}
};					// �α���

struct MSG_FL_LOG_LOGOUT
{
	UID32_t	AccountUniqueNumber;
	CHAR	AccountName[SIZE_MAX_ACCOUNT_NAME];
	BYTE	IPAddress[4];
	CHAR	ServerGroupName[SIZE_MAX_SERVER_NAME];
#ifdef S_ARARIO_HSSON
	CHAR	PublisherName[SIZE_MAX_GAME_PUBLISHER_NAME];				// 2010-11 by dhjin, �ƶ󸮿� ä�θ� �α���.
#endif
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		sprintf(o_szLogString, "%s|%u|%s|%d.%d.%d.%d|%s\r\n", GetGameLogTypeString(i_nLogType), AccountUniqueNumber, AccountName
			, IPAddress[0], IPAddress[1], IPAddress[2], IPAddress[3], ServerGroupName);
		return o_szLogString;
	}
};				// �α׾ƿ�

////////////////////////////////
// USER LOG(0x10~)
struct FL_USER_LOG_BASE
{
	UID32_t		CharacterUniqueNumber;
	MapIndex_t	CurrentMapIndex;
	ChannelIndex_t	CurrentChannIdx;		// 2007-11-30 by cmkwon, �����ʿ� ä���� �ٸ� ��쵵 ���� ó�� - FL_USER_LOG_BASE �� �ʵ� �߰�
	AVECTOR3	CurrentPosition;
	char* GetLogBaseString(char* o_szLogString)
	{
		// 2007-11-30 by cmkwon, �����ʿ� ä���� �ٸ� ��쵵 ���� ó�� - ���� �α� ���� ����
		sprintf(o_szLogString, "%d|%d|%d|(%d, %d, %d)", CharacterUniqueNumber, CurrentMapIndex, CurrentChannIdx, CurrentPosition.x, CurrentPosition.y, CurrentPosition.z);
		return o_szLogString;
	}
};

struct MSG_FL_LOG_LEVEL : public FL_USER_LOG_BASE
{
	BYTE		FromLevel;
	BYTE		ToLevel;
	LONGLONG	TotalPlayTime;
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		char szTemp[1024];
		sprintf(o_szLogString, "%s|%s|%d|%d|%I64d\r\n", GetGameLogTypeString(i_nLogType), GetLogBaseString(szTemp), FromLevel, ToLevel, TotalPlayTime);
		return o_szLogString;
	}
};					// ���� ��ȭ

struct MSG_FL_LOG_EXP : public FL_USER_LOG_BASE
{
	float		AcquiredExperience;	// ���� ����ġ
	LONGLONG	CharacterExperiece;	// ���� ����ġ, Experience_t�̳� DB���� BIGINT�� ����
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		char szTemp[1024];
		sprintf(o_szLogString, "%s|%s|%.0f|%I64d\r\n", GetGameLogTypeString(i_nLogType), GetLogBaseString(szTemp), AcquiredExperience, CharacterExperiece);
		return o_szLogString;
	}
};					// ����ġ ��ȭ

struct MSG_FL_LOG_STAT : public FL_USER_LOG_BASE
{
	BYTE	StatKind;				// STAT_XXX, ������ ����
	BYTE	RemainedBonusStat;		// ���� ���� ���ʽ� ����
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		char szTemp[1024];
		sprintf(o_szLogString, "%s|%s|%d|%d|0\r\n", GetGameLogTypeString(i_nLogType), GetLogBaseString(szTemp), StatKind, RemainedBonusStat);
		return o_szLogString;
	}
};					// ���� ���

struct MSG_FL_LOG_GAME_START : public FL_USER_LOG_BASE
{
	CHAR	CharacterName[SIZE_MAX_CHARACTER_NAME];
	UID32_t	AccountUniqueNumber;
	CHAR	AccountName[SIZE_MAX_ACCOUNT_NAME];
	LONGLONG	TotalPlayTime;		// �� ���� �ð�
	UID32_t		PCBangUID;			// 2007-01-22 by dhjin, ���� PCBang UID
	INT			GameContinueTimeOfToday;	// 2007-11-07 by cmkwon, ���ð������ӽð� ���ӷα׿� �߰� - �ʵ� �߰�
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		char szTemp[1024];
		// 2007-11-07 by cmkwon, ���ð������ӽð� ���ӷα׿� �߰� - GameContinueTimeOfToday �߰�
		sprintf(o_szLogString, "%s|%s|%s|%u|%s|0|%I64d|%u|%d\r\n", GetGameLogTypeString(i_nLogType), GetLogBaseString(szTemp), CharacterName
			, AccountUniqueNumber, AccountName, TotalPlayTime, PCBangUID, GameContinueTimeOfToday);
		return o_szLogString;
	}
};			// ���� ����

struct MSG_FL_LOG_GAME_END : public FL_USER_LOG_BASE
{
	CHAR	CharacterName[SIZE_MAX_CHARACTER_NAME];
	UID32_t	AccountUniqueNumber;
	CHAR	AccountName[SIZE_MAX_ACCOUNT_NAME];
	UINT	PlayTime;				// ���� ���� ���� �� ���� �ð�
	LONGLONG	TotalPlayTime;		// �� ���� �ð�
	UINT		PCBangPlayTime;		// 2006-12-18 by cmkwon, ���� PCBang���� ���ӽð�
	UID32_t		PCBangUID;			// 2007-01-22 by dhjin, ���� PCBang UID
	INT			GameContinueTimeOfToday;	// 2007-11-07 by cmkwon, ���ð������ӽð� ���ӷα׿� �߰� - �ʵ� �߰�
	ATUM_DATE_TIME	LoginDate;								// 2010-06-01 by shcho, GLogDB ���� -		
	CHAR			CharacterRace[SIZE_MAX_GLOG_CHARACTER_RACE_NAME];		// 2010-06-01 by shcho, GLogDB ���� -
	CHAR			CharacterClass[SIZE_MAX_GLOG_CHARACTER_CLASS_NAME];		// 2010-06-01 by shcho, GLogDB ���� -
	Experience_t	PlayExp;											// 2010-06-01 by shcho, GLogDB ���� -
	Experience_t	TotalExp;											// 2010-06-01 by shcho, GLogDB ���� -
	Lv_t			CharacterLevel;										// 2010-06-01 by shcho, GLogDB ���� -
	CHAR			MostStayedInZoneName[SIZE_MAX_MAP_NAME];			// 2010-06-01 by shcho, GLogDB ���� -	

	UID32_t			CharacterUniqueNumber;								// 2011-12-12 by hskim, GLog 2��
	USHORT			Race;												// 2011-12-12 by hskim, GLog 2��
	USHORT			UnitKind;											// 2011-12-12 by hskim, GLog 2��
	BYTE			InfluenceType;										// 2011-12-12 by hskim, GLog 2��

	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		char szTemp[1024];
		// 2007-11-07 by cmkwon, ���ð������ӽð� ���ӷα׿� �߰� - GameContinueTimeOfToday �߰�
		sprintf(o_szLogString, "%s|%s|%s|%u|%s|%u|%I64d|%u|%u|%d\r\n", GetGameLogTypeString(i_nLogType), GetLogBaseString(szTemp), CharacterName
			, AccountUniqueNumber, AccountName, PlayTime, TotalPlayTime, PCBangPlayTime, PCBangUID, GameContinueTimeOfToday);
		return o_szLogString;
	}
};				// ���� ����


// 2014-01-27 by bckim, ���� Ʈ��
struct MSG_FL_LOG_BUGTRAP_ACCEPT : public FL_USER_LOG_BASE
{
	CHAR			CharacterName[SIZE_MAX_CHARACTER_NAME];
	UID32_t			AccountUniqueNumber;
	CHAR			AccountName[SIZE_MAX_ACCOUNT_NAME];
	UINT			PlayTime;								// ���� ���� ���� �� ���� �ð�
	ATUM_DATE_TIME	LoginDate;
	INT				nCloseType;
	BYTE			IPAddress[4];
	CHAR			ServerGroupName[SIZE_MAX_SERVER_NAME];
	CHAR			PublisherName[SIZE_MAX_GAME_PUBLISHER_NAME];

	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		char szTemp[1024];
		sprintf(o_szLogString, "%s|%s|%s|%d|%u|%s|%d.%d.%d.%d|%s|%s|%u\r\n", GetGameLogTypeString(i_nLogType), GetLogBaseString(szTemp), CharacterName, nCloseType
			, AccountUniqueNumber, AccountName, IPAddress[0], IPAddress[1], IPAddress[2], IPAddress[3], ServerGroupName, PublisherName, PlayTime);
		return o_szLogString;
	}
};
// End. 2014-01-27 by bckim, ���� Ʈ��


// 2014-03-31 by jekim, ��ų ��� �α�
struct MSG_FL_LOG_USE_SKILL : public FL_USER_LOG_BASE
{
	CHAR			CharacterName[SIZE_MAX_CHARACTER_NAME];
	UID32_t			AccountUniqueNumber;
	CHAR			AccountName[SIZE_MAX_ACCOUNT_NAME];
	INT				SkillNum;
	BitFlag64_t		ItemAttribute;
	INT				CurrentSP;
	INT				UsedSP;
	INT				Type;
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		char szTemp[1024];
		if (Type == 0)
		{
			sprintf(o_szLogString, "%s|%s|%s|%u|%s|USE|%u|%I64d|%u|%u\r\n", GetGameLogTypeString(i_nLogType), GetLogBaseString(szTemp), CharacterName,
				AccountUniqueNumber, AccountName, SkillNum, ItemAttribute, CurrentSP, UsedSP);
		}
		else if (Type == 1)
		{
			sprintf(o_szLogString, "%s|%s|%s|%u|%s|CANCEL|%u|%I64d\r\n", GetGameLogTypeString(i_nLogType), GetLogBaseString(szTemp), CharacterName,
				AccountUniqueNumber, AccountName, SkillNum, ItemAttribute);
		}
		else if (Type == 2)
		{
			sprintf(o_szLogString, "%s|%s|%s|%u|%s|EFFECT|%u|%I64d|%u|%u\r\n", GetGameLogTypeString(i_nLogType), GetLogBaseString(szTemp), CharacterName,
				AccountUniqueNumber, AccountName, SkillNum, ItemAttribute, CurrentSP, UsedSP);
		}
		return o_szLogString;
	}
};
// end 2014-03-31 by jekim, ��ų ��� �α�

struct MSG_FL_LOG_QUEST_COMPLETION : public FL_USER_LOG_BASE
{
	INT		QuestIndex;				// ����Ʈ �ε���
	BOOL	bFreePass;				// 2013-08-07 by bckim, �̼������н� ������ //�̼������н� ������ ������� �����߰� 
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		char szTemp[1024];
		sprintf(o_szLogString, "%s|%s|%d|%s\r\n", GetGameLogTypeString(i_nLogType), GetLogBaseString(szTemp), QuestIndex, bFreePass ? "USED" : "NOT USED"); // 2013-08-07 by bckim, �̼������н� ������ //�̼������н� ������ ������� �����߰� 
		return o_szLogString;
	}
};		// ����Ʈ �Ϸ�


struct MSG_FL_LOG_QUEST_COMPENSATION : public FL_USER_LOG_BASE		// 2007-04-18 by cmkwon
{
	INT					QuestIndex;				// 2007-04-18 by cmkwon
	INT					ExpOfCompensation;
	INT					BonusStatOfCompensation;
	INT					LenOfCompensation;		// ���� ������ �� (����ġ, SPI����)
	ARRAY_(char);								// ���� ������
	char* GetWriteLogString(int i_nLogType, char* o_szLogString, char* i_szCompensationItemList)
	{
		char szTemp[1024];
		sprintf(o_szLogString, "%s|%s|%d|%d|%d|%s\r\n", GetGameLogTypeString(i_nLogType), GetLogBaseString(szTemp), QuestIndex, ExpOfCompensation, BonusStatOfCompensation, i_szCompensationItemList);
		return o_szLogString;
	}
};	// 2007-01-16 by dhjin, ���� ������ �α�


struct MSG_FL_LOG_PKWIN : public FL_USER_LOG_BASE
{
	UID32_t	PeerCharacterUniqueNumber;	// ��� ĳ����
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		char szTemp[1024];
		sprintf(o_szLogString, "%s|%s|%u\r\n", GetGameLogTypeString(i_nLogType), GetLogBaseString(szTemp), PeerCharacterUniqueNumber);
		return o_szLogString;
	}
};						// 1:1 ���� �¸�

struct MSG_FL_LOG_PKLOSS : public FL_USER_LOG_BASE
{
	UID32_t	PeerCharacterUniqueNumber;	// ��� ĳ����
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		char szTemp[1024];
		sprintf(o_szLogString, "%s|%s|%u\r\n", GetGameLogTypeString(i_nLogType), GetLogBaseString(szTemp), PeerCharacterUniqueNumber);
		return o_szLogString;
	}
};					// 1:1 ���� �й�

// DAMAGE_BY_XXX
#define DAMAGE_BY_COLLISION		((BYTE)0)
#define DAMAGE_BY_MONSTER		((BYTE)1)
#define DAMAGE_BY_PK			((BYTE)2)
#define DAMAGE_BY_FUEL_ALLIN	((BYTE)3)
#define DAMAGE_BY_NA			((BYTE)10)	// �� �� ���ų� ���ʿ��� ���

struct MSG_FL_LOG_DEAD : public FL_USER_LOG_BASE
{
	INT			DamageKind;			// DAMAGE_BY_XXX, ���� ������ ����(PK, �浹, ���� ���� ��)
	ItemNum_t	ItemNum;			// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���ӷα� �߰�, ���� ������ ����
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		char szTemp[1024];
		sprintf(o_szLogString, "%s|%s|%d|%d\r\n", GetGameLogTypeString(i_nLogType), GetLogBaseString(szTemp), DamageKind, ItemNum);
		return o_szLogString;
	}
};					// ��ü ����

struct MSG_FL_LOG_WARP : public FL_USER_LOG_BASE
{
	MapIndex_t	TargetMapIndex;		// ������ ��
	ChannelIndex_t	TargetChannIdx;		// 2007-11-30 by cmkwon, �����ʿ� ä���� �ٸ� ��쵵 ���� ó�� - MSG_FL_LOG_WARP �� �ʵ� �߰�
	AVECTOR3	TargetPosition;		// ������ ���� ��ġ
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		char szTemp[1024];
		// 2007-11-30 by cmkwon, �����ʿ� ä���� �ٸ� ��쵵 ���� ó�� - ���� �α� ����
		sprintf(o_szLogString, "%s|%s|%d|%d|(%d,%d,%d)\r\n", GetGameLogTypeString(i_nLogType), GetLogBaseString(szTemp), TargetMapIndex, TargetChannIdx, TargetPosition.x, TargetPosition.y, TargetPosition.z);
		return o_szLogString;
	}
};					// ����, ���� ���� �� �α� ����

enum SPEEDHACK_CHECK_TYPE
{
	SPEEDHACK_CHECK_TYPE_BY_SERVER = 0,
	SPEEDHACK_CHECK_TYPE_BY_CLIENT = 1
};

struct MSG_FL_LOG_SPEED_HACK : public FL_USER_LOG_BASE
{
	BYTE	CheckType;
	INT 	ReceivedMoveCounts;
	INT		EngineItemNum;
	INT		ServerPastTime;
	INT		ClientPastTime;
	INT		PastDistance;
	INT		CurrentSpeed;
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		char szTemp[1024];
		sprintf(o_szLogString, "%s|%s|%d|%d|%d|%d|%d|%d|%d\r\n", GetGameLogTypeString(i_nLogType), GetLogBaseString(szTemp), CheckType, ReceivedMoveCounts
			, EngineItemNum, ServerPastTime, ClientPastTime, PastDistance, CurrentSpeed);
		return o_szLogString;
	}
};

struct MSG_FL_LOG_CREATE_CHARACTER : public FL_USER_LOG_BASE
{
	CHAR	CharacterName[SIZE_MAX_CHARACTER_NAME];
	UID32_t	AccountUniqueNumber;
	CHAR	AccountName[SIZE_MAX_ACCOUNT_NAME];
	USHORT	UnitKind;
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		char szTemp[1024];
		sprintf(o_szLogString, "%s|%s|%s|%u|%s|%d|1\r\n", GetGameLogTypeString(i_nLogType), GetLogBaseString(szTemp), CharacterName, AccountUniqueNumber
			, AccountName, UnitKind);
		return o_szLogString;
	}
};		// ĳ���� ����

struct MSG_FL_LOG_DELETE_CHARACTER : public FL_USER_LOG_BASE
{
	CHAR	CharacterName[SIZE_MAX_CHARACTER_NAME];
	UID32_t	AccountUniqueNumber;
	CHAR	AccountName[SIZE_MAX_ACCOUNT_NAME];
	USHORT	UnitKind;
	USHORT	Level;
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		char szTemp[1024];
		sprintf(o_szLogString, "%s|%s|%s|%u|%s|%d|%d\r\n", GetGameLogTypeString(i_nLogType), GetLogBaseString(szTemp), CharacterName, AccountUniqueNumber
			, AccountName, UnitKind, Level);
		return o_szLogString;
	}
};		// ĳ���� ����

struct MSG_FL_LOG_MEMORY_HACK : public FL_USER_LOG_BASE		// 2005-12-20 by cmkwon
{
	int		nItemKind;			// üũ ������ ����(1������, 2������, ����, �Ƹ�)
	int		nItemNum0;			// ItemNum
	UID64_t	uid64ItemUID;		// Item UniqueNumber
	int		nMemHackCheckType;	// üũ Ÿ��(CHECK_TYPE_XXXXXX)
	float	fValidValue;		// ��ȿ�� ��
	float	fCurrentValue;		// ���� ��
	int		nParam1;			// üũ Ÿ�Կ� ���� �ǹ̰� �ٸ���
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		char szTemp[1024];
		sprintf(o_szLogString, "%s|%s|%d|%d|%I64d|%d|%5.2f|%5.2f|%d\r\n", GetGameLogTypeString(i_nLogType), GetLogBaseString(szTemp), nItemKind, nItemNum0
			, uid64ItemUID, nMemHackCheckType, fValidValue, fCurrentValue, nParam1);
		return o_szLogString;
	}
};

struct MSG_FL_LOG_PvEWIN : public FL_USER_LOG_BASE		// 2006-03-06 by cmkwon
{
	UID32_t	PeerCharacterUniqueNumber;	// ��� ĳ����
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		char szTemp[1024];
		sprintf(o_szLogString, "%s|%s|%u\r\n", GetGameLogTypeString(i_nLogType), GetLogBaseString(szTemp), PeerCharacterUniqueNumber);
		return o_szLogString;
	}
};						// 1:1 ���� �¸�

struct MSG_FL_LOG_PvELOSS : public FL_USER_LOG_BASE		// 2006-03-06 by cmkwon
{
	UID32_t	PeerCharacterUniqueNumber;	// ��� ĳ����
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		char szTemp[1024];
		sprintf(o_szLogString, "%s|%s|%u\r\n", GetGameLogTypeString(i_nLogType), GetLogBaseString(szTemp), PeerCharacterUniqueNumber);
		return o_szLogString;
	}
};					// 1:1 ���� �й�


///////////////////////////////////////////////////////////////////////////////
// ITEM LOG(0x20~)
struct FL_ITEM_LOG_BASE
{
	UID32_t		CharacterUniqueNumber;
	MapIndex_t	CurrentMapIndex;
	char* GetLogItemBaseString(char* o_szLogString)
	{
		sprintf(o_szLogString, "%u|%d", CharacterUniqueNumber, CurrentMapIndex);
		return o_szLogString;
	}
};

struct ITEM_FOR_LOG
{
	UID64_t		ItemUniqueNumber;
	INT			ItemNum;
	INT			CurrentCount;
	char* GetLogItemString(char* o_szLogString)
	{
		sprintf(o_szLogString, "%I64d|%d|%d", ItemUniqueNumber, ItemNum, CurrentCount);
		return o_szLogString;
	}

#ifdef _ATUM_SERVER
	// operator overloading
	ITEM_FOR_LOG& operator=(const ITEM_GENERAL& rhs)
	{
		this->ItemUniqueNumber = rhs.UniqueNumber;
		this->ItemNum = rhs.ItemNum;
		this->CurrentCount = rhs.CurrentCount;

		return *this;
	}
#endif // _ATUM_SERVER
};

struct MSG_FL_LOG_ITEM_CHARACTER_ITEM : public FL_ITEM_LOG_BASE
{
	ITEM_FOR_LOG	Item4Log;
	INT				ChangeCount;	// ���� ����, 			// 2008-02-15 by cmkwon, �κ�<->â�� �̵� �α� ���� - MSG_FL_LOG_ITEM_STORE_ITEM �� �ʵ� �߰�
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		char szTemp[1024], szItem[1024];
		// 2008-02-15 by cmkwon, �κ�<->â�� �̵� �α� ���� - 
		//		sprintf(o_szLogString, "%s|%s|%s|-1\r\n", GetGameLogTypeString(i_nLogType), GetLogItemBaseString(szTemp), Item4Log.GetLogItemString(szItem));
		sprintf(o_szLogString, "%s|%s|%s|%d\r\n", GetGameLogTypeString(i_nLogType), GetLogItemBaseString(szTemp), Item4Log.GetLogItemString(szItem), ChangeCount);
		return o_szLogString;
	}
};	// 2008-02-15 by cmkwon, �κ�<->â�� �̵� �α� ���� - â��-->�κ� ���� ī���ͺ� ������ �̵��� �κ��� �ش� ������ �߰� �� ���� ����� ����, // (���� ���� �� �)��� ���� ������ ����


// 2012-12-17 by bckim, ���â�� ������ �̵� ���� �߰��α� 
struct MSG_FL_LOG_ITEM_CHARACTER_ITEM_GUILDSTORE_RESULT : public FL_ITEM_LOG_BASE
{
	ITEM_FOR_LOG	Item4Log;
	INT				ChangeCount;
	UID32_t			GuildUID;	/// ��� UID
	CHAR			GuildName[SIZE_MAX_GUILD_NAME];	/// ��� �̸� 

	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		char szTemp[1024], szItem[1024];
		sprintf(o_szLogString, "%s|%s|%d|%s|%s|%d\r\n", GetGameLogTypeString(i_nLogType), GetLogItemBaseString(szTemp), GuildUID, GuildName, Item4Log.GetLogItemString(szItem), ChangeCount);
		return o_szLogString;
	}
};
// 2012-12-17 by bckim, ���â�� ������ �̵� ���� �߰��α�.End



struct MSG_FL_LOG_ITEM_GET_ITEM : public FL_ITEM_LOG_BASE
{
	ITEM_FOR_LOG	Item4Log;
	UID32_t			StoreCharacterUID;			// 2006-11-01 by cmkwon
	INT				ChangeCount;
	BYTE			ItemUpdateType;				// 2008-09-26 by cmkwon, ���ս� GameLog ���� - IUT_XXX
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		char szTemp[1024], szItem[1024];
		// 2008-09-26 by cmkwon, ���ս� GameLog ���� - 
		//sprintf(o_szLogString, "%s|%s|%d|%s|%d\r\n", GetGameLogTypeString(i_nLogType), GetLogItemBaseString(szTemp), StoreCharacterUID, Item4Log.GetLogItemString(szItem), ChangeCount);
		sprintf(o_szLogString, "%s|%s|%d|%s|%d|%s\r\n", GetGameLogTypeString(i_nLogType), GetLogItemBaseString(szTemp), StoreCharacterUID, Item4Log.GetLogItemString(szItem), ChangeCount, GetItemUpdateTypeString(ItemUpdateType));
		return o_szLogString;
	}
};			// Drop Item ����

// 2013-08-05 by bckim, ���� �������� �α� �߰�
struct MSG_FL_LOG_ITEM_DISSOLUTION_ITEM : public FL_ITEM_LOG_BASE
{
	ITEM_FOR_LOG	Item4Log;
	INT				ChangeCount;
	BYTE			ItemUpdateType;
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		char szTemp[1024], szItem[1024];
		sprintf(o_szLogString, "%s|%s|%s|%d|%s\r\n", GetGameLogTypeString(i_nLogType), GetLogItemBaseString(szTemp), Item4Log.GetLogItemString(szItem), ChangeCount, GetItemUpdateTypeString(ItemUpdateType));
		return o_szLogString;
	}
};
// End. 2013-08-05 by bckim, ���� �������� �α� �߰�

struct MSG_FL_LOG_ITEM_GET_ITEM_2 : public FL_ITEM_LOG_BASE		// 2008-09-26 by cmkwon, ���ս� GameLog ���� - ���� �߰���
{
	ITEM_FOR_LOG	Item4Log;
	UID32_t			StoreCharacterUID;			// 2006-11-01 by cmkwon
	INT				ChangeCount;
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		char szTemp[1024], szItem[1024];
		sprintf(o_szLogString, "%s|%s|%d|%s|%d\r\n", GetGameLogTypeString(i_nLogType), GetLogItemBaseString(szTemp), StoreCharacterUID, Item4Log.GetLogItemString(szItem), ChangeCount);
		return o_szLogString;
	}
};

// 2008-09-26 by cmkwon, ���ս� GameLog ���� - �Ʒ��� ���� MSG_FL_LOG_ITEM_GET_ITEM_2 �� ������ ��.
//typedef MSG_FL_LOG_ITEM_GET_ITEM		MSG_FL_LOG_ITEM_ADD_ITEM_BY_ADMIN;		// ����� ���� ����
//typedef MSG_FL_LOG_ITEM_GET_ITEM		MSG_FL_LOG_ITEM_DEL_ITEM_BY_ADMIN;		// ����� ���� ����
//typedef MSG_FL_LOG_ITEM_GET_ITEM		MSG_FL_LOG_ITEM_ADD_ITEM_BY_COMMAND;	// ���ɾ ���� ����
//typedef MSG_FL_LOG_ITEM_GET_ITEM		MSG_FL_LOG_ITEM_INSERT_TO_STORE;		// â���� ����
//typedef MSG_FL_LOG_ITEM_GET_ITEM		MSG_FL_LOG_ITEM_DRAW_FROM_STORE;		// â������ ������
typedef MSG_FL_LOG_ITEM_GET_ITEM_2		MSG_FL_LOG_ITEM_ADD_ITEM_BY_ADMIN;		// ����� ���� ����
typedef MSG_FL_LOG_ITEM_GET_ITEM_2		MSG_FL_LOG_ITEM_DEL_ITEM_BY_ADMIN;		// ����� ���� ����
typedef MSG_FL_LOG_ITEM_GET_ITEM_2		MSG_FL_LOG_ITEM_ADD_ITEM_BY_COMMAND;	// ���ɾ ���� ����
typedef MSG_FL_LOG_ITEM_GET_ITEM_2		MSG_FL_LOG_ITEM_INSERT_TO_STORE;		// â���� ����
typedef MSG_FL_LOG_ITEM_GET_ITEM_2		MSG_FL_LOG_ITEM_DRAW_FROM_STORE;		// â������ ������

typedef MSG_FL_LOG_ITEM_GET_ITEM_2		MSG_FL_LOG_ITEM_GET_WITH_SAME_ACCOUNT;		// 2012-12-27 by bckim, ���ϰ���, ������ �ɸ��Ͱ��� ������ �̵��� �α��߰�

struct MSG_FL_LOG_ITEM_TRADE_SEND : public FL_ITEM_LOG_BASE
{
	UID32_t			PeerCharacterUniqueNumber;	// �ŷ� ���
	char			PeerCharacterName[SIZE_MAX_CHARACTER_NAME];	// �ŷ� ���
	ITEM_FOR_LOG	Item4Log;					// �ŷ� ������
	INT				ChangeCount;				// �ŷ� ����
	BYTE			bGiftItem;					// 2007-11-13 by cmkwon, �����ϱ� ��� �߰� - �����ϱ� �α� �÷��� ����
	BYTE			bRearrangeItem;				// 2007-11-29 by cmkwon, ī���ͺ������� �������� ���� �α� ����� - 
	BYTE			bStoreItem;					// 2007-11-29 by cmkwon, ī���ͺ������� �������� ���� �α� ����� - FALSE �̸� �κ�, FALSE �� �ƴϸ� ĳ����â��
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		char szTemp[1024], szItem[1024];
		// 2007-11-13 by cmkwon, �����ϱ� ��� �߰� - �����ϱ� �α� �÷��� ����
		// 2007-11-29 by cmkwon, ī���ͺ������� �������� ���� �α� ����� - 
		sprintf(o_szLogString, "%s|%s|%u|%s|%s|%d|%d|%d|%d\r\n", GetGameLogTypeString(i_nLogType), GetLogItemBaseString(szTemp), PeerCharacterUniqueNumber
			, PeerCharacterName, Item4Log.GetLogItemString(szItem), ChangeCount, bGiftItem, bRearrangeItem, bStoreItem);
		return o_szLogString;
	}
};					// ������ �ŷ�: �ֱ�

struct MSG_FL_LOG_ITEM_TRADE_RECV : public FL_ITEM_LOG_BASE
{
	UID32_t			PeerCharacterUniqueNumber;	// �ŷ� ���
	char			PeerCharacterName[SIZE_MAX_CHARACTER_NAME];	// �ŷ� ���
	ITEM_FOR_LOG	Item4Log;					// ������
	INT				ChangeCount;				// �ŷ� ����
	BYTE			bGiftItem;					// 2007-11-13 by cmkwon, �����ϱ� ��� �߰� - �����ϱ� �α� �÷��� ����
	BYTE			bRearrangeItem;				// 2007-11-29 by cmkwon, ī���ͺ������� �������� ���� �α� ����� - 
	BYTE			bStoreItem;					// 2007-11-29 by cmkwon, ī���ͺ������� �������� ���� �α� ����� - FALSE �̸� �κ�, FALSE �� �ƴϸ� ĳ����â��
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		char szTemp[1024], szItem[1024];
		// 2007-11-13 by cmkwon, �����ϱ� ��� �߰� - �����ϱ� �α� �÷��� ����
		// 2007-11-29 by cmkwon, ī���ͺ������� �������� ���� �α� ����� - 
		sprintf(o_szLogString, "%s|%s|%u|%s|%s|%d|%d|%d|%d\r\n", GetGameLogTypeString(i_nLogType), GetLogItemBaseString(szTemp), PeerCharacterUniqueNumber
			, PeerCharacterName, Item4Log.GetLogItemString(szItem), ChangeCount, bGiftItem, bRearrangeItem, bStoreItem);
		return o_szLogString;
	}
};					// ������ �ŷ�: �ޱ�

// 2007-06-05 by cmkwon, ��������/��æƮ������ �����ϱ�
struct MSG_FL_LOG_ITEM_THROWAWAY_ITEM : public FL_ITEM_LOG_BASE
{
	ITEM_FOR_LOG	Item4Log;
	INT				ChangeCount;	// �ŷ� ����
	INT				PrefixCodeNum;			// 2007-06-05 by cmkwon
	INT				SuffixCodeNum;			// 2007-06-05 by cmkwon
	INT				EnchatItemNumCount;		// 2007-06-05 by cmkwon, EnchantItemNum List Count
	_ARRAY(INT);							// 2007-06-05 by cmkwon, EnchantItemNum List
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		char szTemp[1024], szItem[1024];
		sprintf(o_szLogString, "%s|%s|%s|%d|%d|%d", GetGameLogTypeString(i_nLogType), GetLogItemBaseString(szTemp), Item4Log.GetLogItemString(szItem), ChangeCount
			, PrefixCodeNum, SuffixCodeNum);
		return o_szLogString;
	}
};	// ������ ������

// 2013-07-01 by bckim, 10��æƮ �̸� ������ī��ó��, �α��߰�, ��� ����
struct MSG_FL_LOG_ITEM_TRY_ENCHANT_INFO : public FL_ITEM_LOG_BASE
{
	ITEM_FOR_LOG	Item4Log;
	INT				Success;
	INT				PrefixCodeNum;
	INT				SuffixCodeNum;
	INT				EnchantCount;
	_ARRAY(INT);
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		char szTemp[1024], szItem[1024];
		sprintf(o_szLogString, "%s|%s|%s|%s|%d|%d|%d", GetGameLogTypeString(i_nLogType), GetLogItemBaseString(szTemp), Item4Log.GetLogItemString(szItem),
			GetTryEnchantSuccessTypeString(Success), EnchantCount, PrefixCodeNum, SuffixCodeNum);
		return o_szLogString;
	}
};

struct MSG_FL_LOG_ITEM_TRY_ENCHANT_INFO_STRING
{
	MSG_FL_LOG_ITEM_TRY_ENCHANT_INFO TryEnchantInfo;
	char szCardList[1024];
};
// End. 2013-07-01 by bckim, 10��æƮ �̸� ������ī��ó��, �α��߰�, ��� ����


struct MSG_FL_LOG_ITEM_BUY_ITEM : public FL_ITEM_LOG_BASE
{
	ITEM_FOR_LOG	Item4Log;
	INT				ChangeCount;	// �ŷ� ����
	INT				RemainedMoney;	// ���� ��
	INT				IsCashItem;		// 2015-02-24 by shchoi WP�� �������� ���� BOOL������ INT������ ��ȯ // 2006-06-21 by cmkwon, ���� ������
	INT				nRemainCountForLimitedEdition;		// 2010-01-26 by cmkwon, ĳ�� ������ �����Ǹ� �ý��� ���� - 
	INT				CashItemPrice;							// 2010-06-01 by shcho, GLogDB ���� -
	CHAR			AccountName[SIZE_MAX_ACCOUNT_NAME];		// 2010-06-01 by shcho, GLogDB ���� -
	CHAR			CharacterName[SIZE_MAX_CHARACTER_NAME]; // 2010-06-01 by shcho, GLogDB ���� -
	INT				CharacterLevel;							// 2010-06-01 by shcho, GLogDB ���� - GLogDB�ʵ尡 int ���̹Ƿ� Int�� �޴´�.
	CHAR			ItemName[SIZE_MAX_ITEM_NAME];			// 2010-06-01 by shcho, GLogDB ���� -

	BOOL			GLog;									// 2011-12-12 by hskim, GLog 2��
	UID32_t			AccountUniqueNumber;					// 2011-12-12 by hskim, GLog 2��
	INT				ItemNum;								// 2011-12-12 by hskim, GLog 2��

	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		char szTemp[1024], szItem[1024];
		sprintf(o_szLogString, "%s|%s|%s|%d|%d|%d|%d\r\n", GetGameLogTypeString(i_nLogType), GetLogItemBaseString(szTemp), Item4Log.GetLogItemString(szItem)
			, ChangeCount, RemainedMoney, IsCashItem, nRemainCountForLimitedEdition);
		return o_szLogString;
	}
};			// ������ ����


// 2012-10-16 by bckim, ĳ�������� �������� Log �߰�
struct MSG_FL_LOG_ITEM_BUY_CASH_PRICE : public FL_ITEM_LOG_BASE
{
	ITEM_FOR_LOG	Item4Log;								// ������ �����ѹ�, �����۹�ȣ
	UID32_t			AccountUniqueNumber;					// ���� ���� �ѹ� 
	INT				nAmount;								// ������ ���ż��� 
	INT				nType;									// ���� Ÿ��.

	INT64			nSPI;
	INT64			nWarPoint;
	INT64			nCash;
	INT64			nInfinity1;
	INT64			nInfinity2;
	INT64			nInfinity3;
	INT64			nInfinity4;
	INT64			nInfinity5;

	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		char szTemp[1024];
		//						%s|%s|%d|%d   |%d|%A|%T|%S   |%W   |%C   |%1   |%2   |%3   |%4   |%5|														
		sprintf(o_szLogString, "%s|%s|%d|%I64d|%d|%d|%d|%I64d|%I64d|%I64d|%I64d|%I64d|%I64d|%I64d|%d\r\n", GetGameLogTypeString(i_nLogType), GetLogItemBaseString(szTemp)
			, AccountUniqueNumber, Item4Log.ItemUniqueNumber, Item4Log.ItemNum, nAmount, nType
			, nSPI, nWarPoint, nCash, nInfinity1, nInfinity2, nInfinity3, nInfinity4, nInfinity5);
		return o_szLogString;
	}
};
// end 2012-10-16 by bckim, ĳ�������� �������� Log �߰�


// 2012-12-20 by bckim, �����ʱ�ȭ�� ���â���������� ����忡�� �Ű����� ������ �α�
struct MSG_FL_LOG_ITEM_INITIALIZED_GUILD_STORE
{
	// ����UID/�����̸�/�ɸ���UID/�ɸ����̸�/������UID/�����۳ѹ�/�����/����������/���ް���/���ѹ�/����̸�
	INT			AccountUniqueNumber;
	CHAR		AccountName[SIZE_MAX_ACCOUNT_NAME];
	INT			CharacterUniqueNumber;
	CHAR		CharacterName[SIZE_MAX_CHARACTER_NAME];

	INT64		ItemUniqueNumber;
	INT			ItemNum;
	INT			Kind;
	INT			CurrentCount;

	INT			GuildUniqueNumber;
	CHAR		GuildName[SIZE_MAX_GUILD_NAME];

	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		sprintf(o_szLogString, "%s|%d|%s|%d|%s|%d|%s|%I64d|%d|%d\r\n", GetGameLogTypeString(i_nLogType)
			, GuildUniqueNumber, GuildName, AccountUniqueNumber, AccountName, CharacterUniqueNumber, CharacterName, ItemUniqueNumber, ItemNum, CurrentCount);
		return o_szLogString;
	}
};
// 2012-12-20 by bckim, �����ʱ�ȭ�� ���â���������� ����忡�� �Ű����� ������ �α�. End



struct MSG_FL_LOG_ITEM_SELL_ITEM : public FL_ITEM_LOG_BASE
{
	ITEM_FOR_LOG	Item4Log;
	INT				ChangeCount;	// �ŷ� ����
	INT				RemainedMoney;	// ���� ��
	INT				PrefixCodeNum;			// 2007-07-20 by cmkwon, �Ǹž����� �α� �߰� - ����
	INT				SuffixCodeNum;			// 2007-07-20 by cmkwon, �Ǹž����� �α� �߰� - ����
	INT				EnchatItemNumCount;		// 2007-07-20 by cmkwon, �Ǹž����� �α� �߰� - EnchantItemNum List Count
	_ARRAY(INT);							// 2007-07-20 by cmkwon, �Ǹž����� �α� �߰� - EnchantItemNum List
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		char szTemp[1024], szItem[1024];
		// 2007-07-20 by cmkwon, �Ǹž����� �α� �߰� - ����/���� �߰�
		sprintf(o_szLogString, "%s|%s|%s|%d|%d|%d|%d", GetGameLogTypeString(i_nLogType), GetLogItemBaseString(szTemp), Item4Log.GetLogItemString(szItem)
			, ChangeCount, RemainedMoney, PrefixCodeNum, SuffixCodeNum);
		return o_szLogString;
	}
};		// ������ �Ǹ�

struct MSG_FL_LOG_ITEM_USE_ITEM : public FL_ITEM_LOG_BASE
{
	ITEM_FOR_LOG	Item4Log;
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		char szTemp[1024], szItem[1024];
		sprintf(o_szLogString, "%s|%s|%s|-1\r\n", GetGameLogTypeString(i_nLogType), GetLogItemBaseString(szTemp), Item4Log.GetLogItemString(szItem));
		return o_szLogString;
	}
};			// ������ ���

struct MSG_FL_LOG_ITEM_USE_ENERGY : public FL_ITEM_LOG_BASE
{
	ITEM_FOR_LOG	Item4Log;
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		char szTemp[1024], szItem[1024];
		sprintf(o_szLogString, "%s|%s|%s|-1\r\n", GetGameLogTypeString(i_nLogType), GetLogItemBaseString(szTemp), Item4Log.GetLogItemString(szItem));
		return o_szLogString;
	}
};		// �������� ������ ���

struct MSG_FL_LOG_ITEM_USE_ENCHANT : public FL_ITEM_LOG_BASE
{
	ITEM_FOR_LOG	Item4Log;
	INT				EnchantLogType;	// ENCHANT_LOGTYPE_FAIL, ENCHANT_LOGTYPE_SUCCESS, ENCHANT_LOGTYPE_TARGETITEM, ENCHANT_LOGTYPE_ATTACHITEM
	INT				nTargetItemPrefixCodeNum;	// 2007-07-30 by cmkwon, ����/��æƮ �α׿� ����/���� ���� ���� - �ʵ��߰�
	INT				nTargetItemSuffixCodeNum;	// 2007-07-30 by cmkwon, ����/��æƮ �α׿� ����/���� ���� ���� - �ʵ��߰�
	INT				nTargetItemEnchantCnt;		// 2010-04-20 by cmkwon, �ű� ��Ű �ӽ� ���� - 
	INT				nEnchantItemKind;			// ��æƮ �������� ItemKind // 2010-04-20 by cmkwon, �ű� ��Ű �ӽ� ���� - 
	INT				nEnchantItemNum;			// ��æƮ �������� ItemNum // 2010-04-20 by cmkwon, �ű� ��Ű �ӽ� ���� - 
	BOOL			bSuccessFlag;				// 2010-04-20 by cmkwon, �ű� ��Ű �ӽ� ���� - 
	UID64_t			arrAddedItemUID[2];			// 2010-04-20 by cmkwon, �ű� ��Ű �ӽ� ���� - (�߰� ����) - 
	INT				arrAddedItemNum[2];			// 2010-04-20 by cmkwon, �ű� ��Ű �ӽ� ���� - (�߰� ����) - 

	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		char szTemp[1024], szItem[1024];

		// 2007-07-30 by cmkwon, ����/��æƮ �α׿� ����/���� ���� ���� - ���� �α� ������
		// 2010-04-20 by cmkwon, �ű� ��Ű �ӽ� ���� - 
		//sprintf(o_szLogString, "%s|%s|%s|%d|%d|%d\r\n"
		//	, GetGameLogTypeString(i_nLogType), GetLogItemBaseString(szTemp), Item4Log.GetLogItemString(szItem)
		//	, EnchantLogType, nTargetItemPrefixCodeNum, nTargetItemSuffixCodeNum);
		///////////////////////////////////////////////////////////////////////////////
		// 2010-04-20 by cmkwon, �ű� ��Ű �ӽ� ���� - 
		// 2010-04-20 by cmkwon, �ű� ��Ű �ӽ� ���� - (�߰� ����) - 
		sprintf(o_szLogString, "%s|%s|%s|%s|%d|%d|%d|%d|%d|%d|%I64d|%d|%I64d|%d\r\n"
			, GetGameLogTypeString(i_nLogType), GetLogItemBaseString(szTemp), Item4Log.GetLogItemString(szItem)
			, GetEnchatLogTypeString(EnchantLogType), nTargetItemPrefixCodeNum, nTargetItemSuffixCodeNum, nTargetItemEnchantCnt, nEnchantItemKind, nEnchantItemNum, bSuccessFlag
			, arrAddedItemUID[0], arrAddedItemNum[0], arrAddedItemUID[1], arrAddedItemNum[1]);
		return o_szLogString;
	}
};		// ��æƮ�� ������ ���

struct MSG_FL_LOG_ITEM_STORE_ITEM : public FL_ITEM_LOG_BASE
{
	ITEM_FOR_LOG	Item4Log;
	INT				ChangeCount;	// ���� ����, 			// 2008-02-15 by cmkwon, �κ�<->â�� �̵� �α� ���� - MSG_FL_LOG_ITEM_STORE_ITEM �� �ʵ� �߰�
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		char szTemp[1024], szItem[1024];
		// 2008-02-15 by cmkwon, �κ�<->â�� �̵� �α� ���� - 
		//		sprintf(o_szLogString, "%s|%s|%s|-1\r\n", GetGameLogTypeString(i_nLogType), GetLogItemBaseString(szTemp), Item4Log.GetLogItemString(szItem));
		sprintf(o_szLogString, "%s|%s|%s|%d\r\n", GetGameLogTypeString(i_nLogType), GetLogItemBaseString(szTemp), Item4Log.GetLogItemString(szItem), ChangeCount);
		return o_szLogString;
	}
};		// 2008-02-15 by cmkwon, �κ�<->â�� �̵� �α� ���� - �κ�-->â�� �� ī���ͺ� ������ �̵��� â���� �ش� ������ �߰� �� ���� ����� ����, // â�� ���� ������ ����, â�� ���� ������


struct MSG_FL_LOG_ITEM_USE_MIX : public FL_ITEM_LOG_BASE
{
	ITEM_FOR_LOG	Item4Log;
	BOOL						IsSuccess;										// 2008-09-26 by cmkwon, ���ս� GameLog ���� - 
	ITEM_UID_W_ITEMNUM_COUNT	arrSourceItemList[COUNT_ITEM_MIXING_SOURCE];	// 2008-09-26 by cmkwon, ���ս� GameLog ���� - 
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		char szTemp[1024], szItem[1024];
		// 2008-09-26 by cmkwon, ���ս� GameLog ���� - �Ʒ��� ���� ���� ��
		//sprintf(o_szLogString, "%s|%s|%s|-1\r\n", GetGameLogTypeString(i_nLogType), GetLogItemBaseString(szTemp), Item4Log.GetLogItemString(szItem));
		sprintf(o_szLogString, "%s|%s|%s|%s|%I64d|%d|%d|%I64d|%d|%d|%I64d|%d|%d|%I64d|%d|%d|%I64d|%d|%d\r\n", GetGameLogTypeString(i_nLogType), GetLogItemBaseString(szTemp),
			((IsSuccess) ? "SUCCESS" : "FAIL"), Item4Log.GetLogItemString(szItem)  // 2013-07-02 by bckim, ���շα� ���� 
			, arrSourceItemList[0].ItemUID, arrSourceItemList[0].ItemNum, arrSourceItemList[0].Count, arrSourceItemList[1].ItemUID, arrSourceItemList[1].ItemNum, arrSourceItemList[1].Count
			, arrSourceItemList[2].ItemUID, arrSourceItemList[2].ItemNum, arrSourceItemList[2].Count, arrSourceItemList[3].ItemUID, arrSourceItemList[3].ItemNum, arrSourceItemList[3].Count
			, arrSourceItemList[4].ItemUID, arrSourceItemList[4].ItemNum, arrSourceItemList[4].Count);
		return o_szLogString;
	}
};			// ���� ����, CurrentCount( 0�̸� ���� 1�̸� ����)

struct MSG_FL_LOG_ITEM_USE_CHANGE_CHARACTER_NAME_ORIGIN : public FL_ITEM_LOG_BASE
{
	ITEM_FOR_LOG	Item4Log;
	char			szOriginCharName[SIZE_MAX_CHARACTER_NAME];
	char			szNewCharName[SIZE_MAX_CHARACTER_NAME];
	DWORD			Padding[SIZE_MAX_PACKET_PADDING];		// 2011-07-21 by hskim, ���� ���� ���� - ���� ������ ȣȯ �ȵǵ��� ����ü ũ�� �ٲ�
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		char szTemp[1024], szItem[1024];
		sprintf(o_szLogString, "%s|%s|%s|%s|%s\r\n", GetGameLogTypeString(i_nLogType), GetLogItemBaseString(szTemp), Item4Log.GetLogItemString(szItem)
			, szOriginCharName, szNewCharName);
		return o_szLogString;
	}
};

typedef MSG_FL_LOG_ITEM_TRADE_SEND		MSG_FL_LOG_ITEM_BAZAAR_SEND;		// 2006-07-28 by cmkwon
typedef MSG_FL_LOG_ITEM_TRADE_RECV		MSG_FL_LOG_ITEM_BAZAAR_RECV;		// 2006-07-28 by cmkwon

struct MSG_FL_LOG_ITEM_SPI : public FL_ITEM_LOG_BASE			// 2006-10-27 by cmkwon
{
	ITEM_FOR_LOG	Item4Log;
	BYTE			ItemUpdateType;	// 2006-10-27 by cmkwon, IUT_XXXX
	INT				ChangeCount;	// ���� ����
	INT				RemainedMoney;	// ���� ��
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		char szTemp[1024], szItem[1024];
		sprintf(o_szLogString, "%s|%s|%s|%s|%d|%d\r\n", GetGameLogTypeString(i_nLogType), GetLogItemBaseString(szTemp), Item4Log.GetLogItemString(szItem)
			, GetItemUpdateTypeString(ItemUpdateType), ChangeCount, RemainedMoney);
		return o_szLogString;
	}
};

// 2008-09-26 by cmkwon, ���ս� GameLog ���� - 
//typedef MSG_FL_LOG_ITEM_GET_ITEM		MSG_FL_LOG_ITEM_GET_ITEM_BY_ITEMEVENT;		// 56 - ItemEvent�� ���� ������ �߰�, 2007-01-11 by cmkwon
typedef MSG_FL_LOG_ITEM_GET_ITEM_2		MSG_FL_LOG_ITEM_GET_ITEM_BY_ITEMEVENT;		// 56 - ItemEvent�� ���� ������ �߰�, 2007-01-11 by cmkwon

struct MSG_FL_LOG_WARPOINT
{// 58 - WarPoint ����, 2007-05-15 by dhjin
	UID32_t			AccountUID;
	CHAR			AccountName[SIZE_MAX_ACCOUNT_NAME];
	UID32_t			CharacterUID;
	CHAR			CharacterName[SIZE_MAX_CHARACTER_NAME];
	INT				ChangeWarPoint;
	INT				TotalWarPoint;
	INT				CumulativeWarPoint;
	BYTE			WPUpdateType;				// 2009-01-22 by cmkwon, ���� ���� ���� �α� ���� - MSG_FL_LOG_WARPOINT�� �߰�
	INT				ArenaPlayCount;				// 2012-04-12 by jhseol, �Ʒ��� �߰����� - ���� : �÷����� �Ʒ��� Ƚ�� �α� �߰�
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		// 2009-01-22 by cmkwon, ���� ���� ���� �α� ���� - �Ʒ��� ���� �߰���.
		//sprintf(o_szLogString, "%s|%d|%s|%d|%s|%d|%d|%d\r\n"
		//	, GetGameLogTypeString(i_nLogType), AccountUID, AccountName, CharacterUID, CharacterName, ChangeWarPoint, TotalWarPoint, CumulativeWarPoint);
		//////////////////////////////////////////////////////////////////////
		// 2012-04-12 by jhseol, �Ʒ��� �߰����� - ���� : �÷����� �Ʒ��� Ƚ�� �α� �߰�
		//sprintf(o_szLogString, "%s|%d|%s|%d|%s|%d|%d|%d|%s\r\n"
		//	, GetGameLogTypeString(i_nLogType), AccountUID, AccountName, CharacterUID, CharacterName, ChangeWarPoint, TotalWarPoint, CumulativeWarPoint, GetWPUTString(WPUpdateType));
		sprintf(o_szLogString, "%s|%d|%s|%d|%s|%d|%d|%d|%s|ArenaPlayCount(%d)\r\n"
			, GetGameLogTypeString(i_nLogType), AccountUID, AccountName, CharacterUID, CharacterName, ChangeWarPoint, TotalWarPoint, CumulativeWarPoint, GetWPUTString(WPUpdateType), ArenaPlayCount);
		// end 2012-04-12 by jhseol, �Ʒ��� �߰����� - ���� : �÷����� �Ʒ��� Ƚ�� �α� �߰�
		return o_szLogString;
	}
};

struct MSG_FL_LOG_ARENA_TEAM_MATCH
{// 59 - Arena �� ��Ī, 2007-06-11 by dhjin
	BYTE			TeamMode;
	BYTE			TeamSize;
	BYTE			StartLevel;
	BYTE			EndLevel;
	MapIndex_t		ArenaMap;	// 2012-04-12 by jhseol, �Ʒ��� �߰����� - ������ �Ʒ��� �� �α� �߰�
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		//////////////////////////////////////////////////////////////////////
		// 2012-04-12 by jhseol, �Ʒ��� �߰����� - ������ �Ʒ��� �� �α� �߰�
//		sprintf(o_szLogString, "%s|%d|%d|%d~%d\r\n", GetGameLogTypeString(i_nLogType), TeamMode, TeamSize, StartLevel, EndLevel);
		sprintf(o_szLogString, "%s|%d|%d|%d~%d|%d\r\n", GetGameLogTypeString(i_nLogType), TeamMode, TeamSize, StartLevel, EndLevel, ArenaMap);
		// end 2012-04-12 by jhseol, �Ʒ��� �߰����� - ������ �Ʒ��� �� �α� �߰�
		return o_szLogString;
	}
};

struct MSG_FL_LOG_TUTORIAL_COMPLETION
{// 60 - Tutorial, 2007-07-06 by dhjin
	UID32_t			AccountUID;
	CHAR			AccountName[SIZE_MAX_ACCOUNT_NAME];
	UID32_t			CharacterUID;
	CHAR			CharacterName[SIZE_MAX_CHARACTER_NAME];
	INT				TutorialNum;
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		sprintf(o_szLogString, "%s|%d|%s|%d|%s|%d\r\n"
			, GetGameLogTypeString(i_nLogType), AccountUID, AccountName, CharacterUID, CharacterName, TutorialNum);
		return o_szLogString;
	}
};

struct MSG_FL_LOG_GUILD_STORE
{// 2006-09-27 by dhjin, ���� â�� �α� ����� ����ü
	UID32_t			GuildUID;
	CHAR			GuildName[SIZE_MAX_GUILD_NAME];
	UID32_t			AccountUID;
	CHAR			AccountName[SIZE_MAX_ACCOUNT_NAME];
	UID32_t			CharacterUID;
	CHAR			CharacterName[SIZE_MAX_CHARACTER_NAME];
	UID64_t			ItemUID;
	INT				ItemNum;
	INT				PrefixCodeNum;
	INT				SuffixCodeNum;
	INT				ItemResultCount;
	INT				ItemChangeCount;
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		sprintf(o_szLogString, "%s|%d|%s|%d|%s|%d|%s|%I64d|%d|%d|%d|%d|%d\r\n"
			, GetGameLogTypeString(i_nLogType), GuildUID, GuildName, AccountUID, AccountName, CharacterUID, CharacterName
			, ItemUID, ItemNum, PrefixCodeNum, SuffixCodeNum, ItemResultCount, ItemChangeCount);
		return o_szLogString;
	}
};

struct MSG_FL_LOG_OUTPOST_START
{// 61 - OutPost���� �α�, 2007-10-02 by dhjin
	MapIndex_t			OutPostMapIdx;
	BYTE				PossessInflTy;
	UID32_t				PossessGuildUID;
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		sprintf(o_szLogString, "%s|%d|%d|%u\r\n", GetGameLogTypeString(i_nLogType), OutPostMapIdx, PossessInflTy, PossessGuildUID);
		return o_szLogString;
	}
};

struct MSG_FL_LOG_OUTPOST_END
{// 62 - OutPost���� �α�, 2007-10-02 by dhjin
	MapIndex_t			OutPostMapIdx;
	BYTE				PossessInflTy;
	UID32_t				PossessGuildUID;
	CHAR				PossessGuildName[SIZE_MAX_GUILD_NAME];
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		sprintf(o_szLogString, "%s|%d|%d|%u|%s\r\n"
			, GetGameLogTypeString(i_nLogType), OutPostMapIdx, PossessInflTy, PossessGuildUID, PossessGuildName);
		return o_szLogString;
	}
};

struct MSG_FL_LOG_EXPEDIENCYFUND
{// 63 - �ǰ��� ��/�� �α�, 2007-10-02 by dhjin
	MapIndex_t		MapIndex;
	UID32_t			CharacterUID;	// 2007-10-16 by cmkwon, �α� �߰� - �߰�
	UID32_t			GuildUID;		// 2007-10-16 by cmkwon, �α� �߰� - �߰�
	BOOL			Increase;		// FALSE : ����, TRUE : ����
	INT				Count;
	INT				ExpediencyFundVRate;	// 2007-10-16 by cmkwon, �α� �߰� - EXPEDIENCYFUND_RATE_VALUE �� �������� ���� ¡����
	INT				TotalCount;
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		// 2007-10-16 by cmkwon, �α� �߰� - ������
		sprintf(o_szLogString, "%s|%d|%u|%u|%d|%d|%.3f|%d\r\n"
			, GetGameLogTypeString(i_nLogType), MapIndex, CharacterUID, GuildUID, Increase, Count, ((float)ExpediencyFundVRate) / EXPEDIENCYFUND_RATE_VALUE, TotalCount);
		return o_szLogString;
	}
};

////////////////////////////////
// ETC LOG(0x40~)
typedef struct
{
	MapIndex_t		MapIndex;
	ChannelIndex_t	ChannelIndex;
	INT				ClientCount;
	INT				MonsterCount;
	char			MapName[SIZE_MAX_MAP_NAME];						// 2010-06-01 by shcho, GLogDB ���� -
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		sprintf(o_szLogString, "%s|%d|%d|%d|%d\r\n", GetGameLogTypeString(i_nLogType), MapIndex, ChannelIndex, ClientCount, MonsterCount);
		return o_szLogString;
	}
} MSG_FL_LOG_SERVER_INFO_MAP;

typedef struct
{
	INT				ClientCount;
	INT				MonsterCount;
	BOOL			bGlogUpdate;		// 2010-06-01 by shcho, GLogDB ���� -
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		sprintf(o_szLogString, "%s|0|0|%d|%d\r\n", GetGameLogTypeString(i_nLogType), ClientCount, MonsterCount);
		return o_szLogString;
	}
} MSG_FL_LOG_SERVER_INFO_TOTAL;

struct MSG_FL_LOG_HACKING_LOG : public FL_USER_LOG_BASE
{
	char			AccountName0[SIZE_MAX_ACCOUNT_NAME];
	long			hackingCode;
	char			szErrString[SIZE_STRING_128];			// 2006-10-20 by cmkwon, �߰���(��ŷ ���α׷���)
	char			IPAddress[SIZE_MAX_IPADDRESS];
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		char szTemp[1024];
		sprintf(o_szLogString, "%s|%s|%s|%d|%s|%s\r\n", GetGameLogTypeString(i_nLogType), AccountName0, GetLogBaseString(szTemp), hackingCode, IPAddress, szErrString);
		return o_szLogString;
	}
};

////////////////////////////////
// MONSTER LOG(0x50~)
typedef struct
{
	MAP_CHANNEL_INDEX	MapChannel;
	INT					MonsterUnitKind;
	ATUM_DATE_TIME		CreatedTime;
	ATUM_DATE_TIME		DeadTime;
	char				AttackUser[SIZE_MAX_USERLIST_ON_BOSS_MONSTER_DEAD][SIZE_MAX_CHARACTER_NAME];
	INT					LenOfDropItemList;		// Drop Item List string�� ����
	ARRAY_(char);								// Drop Item List string
	char* GetWriteLogString(int i_nLogType, char* o_szLogString, char* i_szDropItemList)
	{
		sprintf(o_szLogString, "%s|%d|%d|%d|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s\r\n", GetGameLogTypeString(i_nLogType), MapChannel.MapIndex, MapChannel.ChannelIndex, MonsterUnitKind
			, CreatedTime.GetDateTimeString(STRNBUF(SIZE_MAX_SQL_DATETIME_STRING)), DeadTime.GetDateTimeString(STRNBUF(SIZE_MAX_SQL_DATETIME_STRING))
			, AttackUser[0], AttackUser[1], AttackUser[2], AttackUser[3], AttackUser[4], AttackUser[5]
			, AttackUser[6], AttackUser[7], AttackUser[8], AttackUser[9], i_szDropItemList);
		return o_szLogString;
	}
} MSG_FL_LOG_MONSTER_BOSS;	// ������ ����

// 2014-03-31 by bckim, ��� ���� ų�α� ( ĳ���� ��û) 
struct MSG_FL_LOG_ALL_MONSTER_KILL_LOG
{
	INT			MonsterLogType;

	UID32_t		CharacterUID;
	CHAR		CharacterName[SIZE_MAX_CHARACTER_NAME];
	UID32_t		AccountUID;
	CHAR		AccountName[SIZE_MAX_ACCOUNT_NAME];
	MapIndex_t	CurrentMapIndex;

	INT			MonsterUnitKind;
	char		MonsterName[SIZE_MAX_MONSTER_NAME];
	INT			MonsterHP;			// ����	
	float		CurrentHP;			// ���� 
	float		Damage;

	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		//sprintf(o_szLogString, "%s|%d|%d|%s|%d|%s|%d|%d|%s|%f|%f\r\n", GetGameLogTypeString(i_nLogType),MonsterLogType,CharacterUID,	CharacterName,AccountUID,AccountName,
		sprintf(o_szLogString, "%s|%s|%d|%s|%d|%s|%d|%d|%s|%8.1f(%d)|%5.2f\r\n", GetGameLogTypeString(i_nLogType), GetKillLogTypeString(MonsterLogType), CharacterUID, CharacterName, AccountUID, AccountName,
			CurrentMapIndex, MonsterUnitKind, MonsterName, CurrentHP, MonsterHP, Damage);
		return o_szLogString;
	}
};
// End. 2014-03-31 by bckim, ��� ���� ų�α� ( ĳ���� ��û) 

struct MSG_FL_LOG_INFLWAR_START
{// 2007-10-16 by cmkwon, �α� �߰� -
	MapIndex_t			MothershipCreatedMapIdx;
	BYTE				InfluenceType2;
	INT					MonsterUnitKind;
	BYTE				MonBell;
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		sprintf(o_szLogString, "%s|%d|%d|%d|%d\r\n", GetGameLogTypeString(i_nLogType), MothershipCreatedMapIdx, InfluenceType2, MonsterUnitKind, MonBell);
		return o_szLogString;
	}
};
struct MSG_FL_LOG_INFLWAR_END
{// 2007-10-16 by cmkwon, �α� �߰� -
	MapIndex_t			MothershipCreatedMapIdx;
	BYTE				InfluenceType2;
	INT					MonsterUnitKind;
	BYTE				MonBell;
	BOOL				DeadFlag;
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		sprintf(o_szLogString, "%s|%d|%d|%d|%d|%d\r\n", GetGameLogTypeString(i_nLogType), MothershipCreatedMapIdx, InfluenceType2, MonsterUnitKind, MonBell, DeadFlag);
		return o_szLogString;
	}
};
struct MSG_FL_LOG_OUTPOSTWAR_RESET_START
{// 2007-10-16 by cmkwon, �α� �߰� -
	MapIndex_t			OutPostMapIdx;
	BYTE				PossessInflTy;
	UID32_t				PossessGuildUID;
	BYTE				InflTy4Reset;
	UID32_t				GuildUID4Reset;
	UID32_t				ResetUserGuildUID;
	UID32_t				ResetUserCharacterUID;
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		sprintf(o_szLogString, "%s|%d|%d|%u|%d|%u|%u|%u\r\n", GetGameLogTypeString(i_nLogType), OutPostMapIdx, PossessInflTy, PossessGuildUID, InflTy4Reset, GuildUID4Reset, ResetUserGuildUID, ResetUserCharacterUID);
		return o_szLogString;
	}
};
struct MSG_FL_LOG_OUTPOSTWAR_RESET_DESTROY
{// 2007-10-16 by cmkwon, �α� �߰� -
	MapIndex_t			OutPostMapIdx;
	BYTE				PossessInflTy;
	UID32_t				PossessGuildUID;
	BYTE				InflTy4Reset;
	UID32_t				GuildUID4Reset;
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		sprintf(o_szLogString, "%s|%d|%d|%u|%d|%u\r\n", GetGameLogTypeString(i_nLogType), OutPostMapIdx, PossessInflTy, PossessGuildUID, InflTy4Reset, GuildUID4Reset);
		return o_szLogString;
	}
};
struct MSG_FL_LOG_OUTPOSTWAR_RESET_COMPLETE
{// 2007-10-16 by cmkwon, �α� �߰� -
	MapIndex_t			OutPostMapIdx;
	BYTE				PossessInflTy;
	UID32_t				PossessGuildUID;
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		sprintf(o_szLogString, "%s|%d|%d|%u\r\n", GetGameLogTypeString(i_nLogType), OutPostMapIdx, PossessInflTy, PossessGuildUID);
		return o_szLogString;
	}
};

#define SIZE_MAX_OUTPOSTWAR_DAMAGELIST			10		// 2007-10-16 by cmkwon, �α� �߰� - 
struct MSG_FL_LOG_OUTPOSTWAR_PROTECTOR_DESTROY
{// 2007-10-16 by cmkwon, �α� �߰� -
	MapIndex_t			OutPostMapIdx;
	BYTE				PossessInflTy;
	UID32_t				PossessGuildUID;
	BYTE				InflTy4Reset;
	UID32_t				GuildUID4Reset;
	UID32_t				ArrGuildUID[SIZE_MAX_OUTPOSTWAR_DAMAGELIST];
	float				ArrDamage[SIZE_MAX_OUTPOSTWAR_DAMAGELIST];
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		// 2007-10-16 by cmkwon, ������ ����Ʈ�� �ܺο��� ����� �̾ ���δ�
		sprintf(o_szLogString, "%s|%d|%d|%u|%d|%u", GetGameLogTypeString(i_nLogType), OutPostMapIdx, PossessInflTy, PossessGuildUID, InflTy4Reset, GuildUID4Reset);
		return o_szLogString;
	}
};
struct MSG_FL_LOG_OUTPOSTWAR_SET_NEXTTIME
{// 2007-10-16 by cmkwon, �α� �߰� -
	MapIndex_t			OutPostMapIdx;
	BYTE				PossessInflTy;
	UID32_t				PossessGuildUID;
	UID32_t				UserGuildUID;
	UID32_t				UserCharacterUID;
	ATUM_DATE_TIME		NextTime;
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		sprintf(o_szLogString, "%s|%d|%d|%u|%u|%u|%s\r\n", GetGameLogTypeString(i_nLogType), OutPostMapIdx, PossessInflTy, PossessGuildUID, UserGuildUID, UserCharacterUID, NextTime.GetDateTimeString(STRNBUF(SIZE_MAX_ATUM_DATE_TIME_STRING)));
		return o_szLogString;
	}
};

struct MSG_FL_LOG_POLL_VOTE
{// 2007-11-08 by dhjin
	UID32_t				VoteCharacterUID;
	UID32_t				CharacterUID;
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		sprintf(o_szLogString, "%s|%d|%d\r\n", GetGameLogTypeString(i_nLogType), VoteCharacterUID, CharacterUID);
		return o_szLogString;
	}
};

struct MSG_FL_LOG_POLL_DELETE_LEADERCANDIDATE
{// 2007-11-08 by dhjin
	UID32_t				CharacterUID;
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		sprintf(o_szLogString, "%s|%d\r\n", GetGameLogTypeString(i_nLogType), CharacterUID);
		return o_szLogString;
	}
};

struct MSG_FL_LOG_DISMEMBER_GUILD
{// 2007-11-09 by dhjin
	UID32_t				GuildUID;
	char				GuildName[SIZE_MAX_GUILD_NAME];
	UID32_t				GuildCommanderUID;
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		sprintf(o_szLogString, "%s|%d|%s|%d\r\n", GetGameLogTypeString(i_nLogType), GuildUID, GuildName, GuildCommanderUID);
		return o_szLogString;
	}
};

struct MSG_FL_LOG_NOTIFY_MSG_DELETE : public SNOTIFY_MSG		// 2007-11-28 by cmkwon, �����ý��� ���� -
{
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		sprintf(o_szLogString, "%s|%I64d|%u|%d|%s|%u|%s|%s\r\n", GetGameLogTypeString(i_nLogType), NotifyMsgUID, CharacterUID, NotifyMsgType, NotifyMsgString, SenderCharacterUID, SenderCharacterName, CreateTime.GetDateTimeString(STRNBUF(SIZE_MAX_ATUM_DATE_TIME_STRING)));
		return o_szLogString;
	}
};
struct MSG_FL_LOG_USE_COUPON : public FL_USER_LOG_BASE		// 2008-01-23 by cmkwon, S_F, S_L: ���� ��� ���� �α׿� �߰� - 
{
	char AccountName[SIZE_MAX_ACCOUNT_NAME];
	char CouponNumber[SIZE_MAX_COUPON_NUMBER];
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		char szTemp[1024];
		sprintf(o_szLogString, "%s|%s|%s|%s\r\n", GetGameLogTypeString(i_nLogType), GetLogBaseString(szTemp), AccountName, CouponNumber);
		return o_szLogString;
	}
};

struct MSG_FL_LOG_ITEM_ATTACH_ITEM : public FL_ITEM_LOG_BASE		// 2008-01-23 by cmkwon, S_F, S_L: ����/�������� ���� �α׿� �߰� - 
{
	ITEM_FOR_LOG	Item4Log;
	INT				ReaminTimeSec;
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		char szTemp[1024], szItem[1024];
		sprintf(o_szLogString, "%s|%s|%s|%d\r\n", GetGameLogTypeString(i_nLogType), GetLogItemBaseString(szTemp), Item4Log.GetLogItemString(szItem)
			, ReaminTimeSec);
		return o_szLogString;
	}
};
struct MSG_FL_LOG_ITEM_DETACH_ITEM : public FL_ITEM_LOG_BASE		// 2008-01-23 by cmkwon, S_F, S_L: ����/�������� ���� �α׿� �߰� - 
{
	ITEM_FOR_LOG	Item4Log;
	INT				ReaminTimeSec;
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		char szTemp[1024], szItem[1024];
		sprintf(o_szLogString, "%s|%s|%s|%d\r\n", GetGameLogTypeString(i_nLogType), GetLogItemBaseString(szTemp), Item4Log.GetLogItemString(szItem)
			, ReaminTimeSec);
		return o_szLogString;
	}
};
struct MSG_FL_LOG_ITEM_DELETE : public FL_ITEM_LOG_BASE		// 2008-01-23 by cmkwon, S_F, S_L: ����/�������� ���� �α׿� �߰� - 
{
	ITEM_FOR_LOG	Item4Log;
	INT				ItemDeleteType;
	ATUM_DATE_TIME	atCreatedTime;			// 2009-11-17 by cmkwon, �������� ���� ������ ������ �α� ���� �߰� - MSG_FL_LOG_ITEM_DELETE
	INT				nUsedTime;				// 2009-11-17 by cmkwon, �������� ���� ������ ������ �α� ���� �߰� - MSG_FL_LOG_ITEM_DELETE
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		// 2009-11-17 by cmkwon, �������� ���� ������ ������ �α� ���� �߰� - 
		char szTemp[1024], szItem[1024];
		sprintf(o_szLogString, "%s|%s|%s|%s|%s|%d\r\n", GetGameLogTypeString(i_nLogType), GetLogItemBaseString(szTemp), Item4Log.GetLogItemString(szItem)
			, GetItemDeleteTypeString(ItemDeleteType), atCreatedTime.GetDateTimeString(STRNBUF(SIZE_MAX_SQL_DATETIME_STRING)), nUsedTime);
		return o_szLogString;
	}
};

//////////////////////////////////////////////////////////////////////////
// 2008-04-01 by dhjin, ����, ������ ����â ��ȹ�� - 
struct MSG_FL_LOG_MS_WAR
{
	BYTE			AttInfluence;
	INT				MonsterUID;
	INT				ContributionPoint;
	ATUM_DATE_TIME	MSWarStartTime;
	BYTE			WinInfluence;

	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		sprintf(o_szLogString, "%s|%d|%d|%d|%s|%d\r\n", GetGameLogTypeString(i_nLogType), AttInfluence, MonsterUID, ContributionPoint, MSWarStartTime.GetDateTimeString(STRNBUF(SIZE_MAX_ATUM_DATE_TIME_STRING)), WinInfluence);
		return o_szLogString;
	}
};

struct MSG_FL_LOG_SP_WAR
{
	BYTE			AttInfluence;
	INT				SPSummonMapIndex;
	ATUM_DATE_TIME	SPWarStartTime;
	BYTE			WinInfluence;

	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		sprintf(o_szLogString, "%s|%d|%d|%s|%d\r\n", GetGameLogTypeString(i_nLogType), AttInfluence, SPSummonMapIndex, SPWarStartTime.GetDateTimeString(STRNBUF(SIZE_MAX_ATUM_DATE_TIME_STRING)), WinInfluence);
		return o_szLogString;
	}
};

struct MSG_FL_LOG_WAR_CONTRIBUTION
{
	UID32_t		CharacterUID;
	MapIndex_t	nMapIndex;
	UID64_t		nContribution;
	INT			nPay;
	BYTE		byPayType;

	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		sprintf(o_szLogString, "%s|%d|%d|%I64d|%d|%d\r\n", GetGameLogTypeString(i_nLogType), CharacterUID, nMapIndex, nContribution, nPay, byPayType);
		return o_szLogString;
	}
};

struct MSG_FL_LOG_WAR_CONTRIBUTION_GEAR
{
	UID64_t			nTotalBGearContribution;
	UID64_t			nTotalIGearContribution;
	UID64_t			nTotalAGearContribution;
	UID64_t			nTotalMGearContribution;
	INT				nBGearCount;
	INT				nIGearCount;
	INT				nAGearCount;
	INT				nMGearCount;
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		sprintf(o_szLogString, "%s|%I64d|%I64d|%I64d|%I64d|%d|%d|%d|%d\r\n", GetGameLogTypeString(i_nLogType)
			, nTotalBGearContribution, nTotalIGearContribution, nTotalAGearContribution, nTotalMGearContribution
			, nBGearCount, nIGearCount, nAGearCount, nMGearCount);
		return o_szLogString;
	}
};

struct MSG_FL_LOG_LUCKY_DROP
{// 2009-03-31 by dhjin, ��Ű�ӽ� �α�
	INT				MysteryItemDropNum;
	INT				DropItemNum;
	ATUM_DATE_TIME	Starttime;				// ��Ű�ӽ� ���� �ð�, 2008-11-04 by dhjin, ��Ű�ӽ�
	ATUM_DATE_TIME	Endtime;				// ��Ű�ӽ� ���� �ð�, 2008-11-04 by dhjin, ��Ű�ӽ�
	INT				CountPerPeriod;			// �Ⱓ���� ����� �ִ� ������ ��, 2008-11-04 by dhjin, ��Ű�ӽ�
	INT				DropCount;				// �Ⱓ���� ���� ����� ������ ��, 2008-11-04 by dhjin, ��Ű�ӽ�

	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		sprintf(o_szLogString, "%s|%d|%d|%s|%s|%d|%d\r\n", GetGameLogTypeString(i_nLogType)
			, MysteryItemDropNum, DropItemNum, Starttime.GetDateTimeString(STRNBUF(SIZE_MAX_SQL_DATETIME_STRING)), Endtime.GetDateTimeString(STRNBUF(SIZE_MAX_SQL_DATETIME_STRING))
			, CountPerPeriod, DropCount);
		return o_szLogString;
	}
};

struct MSG_FL_LOG_INFINITY_START {
	// 193 - // 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���ӷα� �߰�, ���� ���� ���� 
	InfinityCreateUID_t		InfinityCreateUID;		// �ش� ���� ���� ��ȣ
	USHORT					MainServerID;			// ������ ĳ������ ����
	BYTE					InfluenceType;			// ������ ĳ������ ����
	char					CharacterName[SIZE_MAX_CHARACTER_NAME];		//	ĳ���͸�
	UID32_t					CharacterUID;			// (ĳ���� UID)
	Lv_t					Level;					// ������ ĳ������ ����
	USHORT					UnitKind;				// ������ ĳ������ �������
	Experience_t			Experience;				// ����ġ��
	float					CurrentHP;				// HP
	float					CurrentDP;				// DP
	SHORT					CurrentSP;				// SP
	// 2014-01-24 by jhseol, ���� ���ӷα� ���� �߰�
	eINFINITY_MODE InfinityMode;
	INT InfinityLevel;
	MSG_FL_LOG_INFINITY_START()
	{
		MEMSET_ZERO(this, sizeof(MSG_FL_LOG_INFINITY_START));
	}
	// end 2014-01-24 by jhseol, ���� ���ӷα� ���� �߰�

	char* GetWriteLogString(int i_nLogType, char* o_szLogString) {
		// 2014-01-24 by jhseol, ���� ���ӷα� ���� �߰�
//		sprintf(o_szLogString, "%s|%I64d|%d|%d|%s(%d)|%d|%d|%f|%f|%f|%d\r\n", GetGameLogTypeString(i_nLogType)
//			, InfinityCreateUID, MainServerID, InfluenceType, CharacterName, CharacterUID, Level, UnitKind, Experience, CurrentHP, CurrentDP, CurrentSP);
		sprintf(o_szLogString, "%s|%I64d|%d|%d|%s(%d)|%d|%d|%f|%f|%f|%d|(%d,%d)\r\n", GetGameLogTypeString(i_nLogType)
			, InfinityCreateUID, MainServerID, InfluenceType, CharacterName, CharacterUID, Level, UnitKind, Experience, CurrentHP, CurrentDP, CurrentSP, InfinityMode, InfinityLevel);
		// end 2014-01-24 by jhseol, ���� ���ӷα� ���� �߰�
		return o_szLogString;
	}
};

struct MSG_FL_LOG_INFINITY_START_ITEM : public FL_ITEM_LOG_BASE {
	// 194 - // 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���ӷα� �߰�, ���۽� ������ ���� ����
	ITEM_FOR_LOG	Item4Log;
	INT				ReaminTimeMSec;
	UID64_t			MainSvrItemUID;
	char* GetWriteLogString(int i_nLogType, char* o_szLogString) {
		char szTemp[1024], szItem[1024];
		sprintf(o_szLogString, "%s|%s|%s|%d|%I64d\r\n", GetGameLogTypeString(i_nLogType), GetLogItemBaseString(szTemp), Item4Log.GetLogItemString(szItem)
			, ReaminTimeMSec, MainSvrItemUID);
		return o_szLogString;
	}
};

struct MSG_FL_LOG_INFINITY_CINEMA {
	// 195 - // 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���ӷα� �߰�, ���� �α�
	InfinityCreateUID_t		InfinityCreateUID;		// �ش� ���� ���� ��ȣ
	MSec_t					StartTime;
	EffectIdx_t				EffectIdx;
	ObjectIdx_t				ObjectIdx;
	ObjectNum_t				ChangeObjectIdx;
	MonIdx_t				MonsterIdx;
	MSec_t					CameraTremble;
	CinemaTalk_t			CinemaTalk[SIZE_MAX_CINEMATALK_DESCRIPTION];
	QuestIndex_t			QuestIndex;		// 2011-03-09 by hskim, ���Ǵ�Ƽ 3�� - �ó׸� ����Ʈ �ε��� ���� �߰� -

	char* GetWriteLogString(int i_nLogType, char* o_szLogString) {
		sprintf(o_szLogString, "%s|%I64d|%d|%d|%d|%d|%d|%d|%s|%d\r\n", GetGameLogTypeString(i_nLogType)
			, InfinityCreateUID, StartTime, EffectIdx, ObjectIdx, ChangeObjectIdx, MonsterIdx, CameraTremble, CinemaTalk, QuestIndex);		// 2011-03-09 by hskim, ���Ǵ�Ƽ 3�� - �ó׸� ����Ʈ �ε��� ���� �߰�
		return o_szLogString;
	}
};

struct MSG_FL_LOG_MONSTER_SKILL {
	// 196 - // 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���ӷα� �߰�, ���� ��ų ����
	MonIdx_t				MonsterIdx;
	ItemNum_t				MonsterSkillNum;

	char* GetWriteLogString(int i_nLogType, char* o_szLogString) {
		sprintf(o_szLogString, "%s|%d|%d\r\n", GetGameLogTypeString(i_nLogType)
			, MonsterIdx, MonsterSkillNum);
		return o_szLogString;
	}
};

struct MSG_FL_LOG_HPACTION_TALK {
	// 197 - // 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���ӷα� �߰�, ���� ��ȭ ����
	MonIdx_t				MonsterIdx;
	HPTalk_t				HPTalk[SIZE_MAX_HPTALK_DESCRIPTION];
	char* GetWriteLogString(int i_nLogType, char* o_szLogString) {
		sprintf(o_szLogString, "%s|%d|%s\r\n", GetGameLogTypeString(i_nLogType)
			, MonsterIdx, HPTalk);
		return o_szLogString;
	}
};

struct MSG_FL_LOG_INFINITY_FIN {
	// 198 - // 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���ӷα� �߰�, ���� ���� ���� 
	InfinityCreateUID_t		InfinityCreateUID;		// �ش� ���� ���� ��ȣ
	USHORT					MainServerID;			// ������ ĳ������ ����
	BYTE					InfluenceType;			// ������ ĳ������ ����
	char					CharacterName[SIZE_MAX_CHARACTER_NAME];		//	ĳ���͸�
	UID32_t					CharacterUID;			// (ĳ���� UID)
	Lv_t					Level;					// ������ ĳ������ ����
	USHORT					UnitKind;				// ������ ĳ������ �������
	Experience_t			Experience;				// ����ġ��
	float					CurrentHP;				// HP
	float					CurrentDP;				// DP
	SHORT					CurrentSP;				// SP
	BOOL					Clear;					// ���Ǵ�Ƽ �ʵ� Ŭ���� ����
	KillCnt_t				KillCount;				// ���� ����� �ϰ��� ��(��Ÿ Ƚ��)
	DeathCnt_t				DeathCount;				// Ŭ���� �ϱ���� ��� Ƚ��
	// 2014-01-24 by jhseol, ���� ���ӷα� ���� �߰�
	eINFINITY_MODE InfinityMode;
	INT InfinityLevel;
	DWORD InfinityPlayTick;
	MSG_FL_LOG_INFINITY_FIN()
	{
		MEMSET_ZERO(this, sizeof(MSG_FL_LOG_INFINITY_FIN));
	}
	// end 2014-01-24 by jhseol, ���� ���ӷα� ���� �߰�

	char* GetWriteLogString(int i_nLogType, char* o_szLogString) {
		// 2014-01-24 by jhseol, ���� ���ӷα� ���� �߰�
// 		sprintf(o_szLogString, "%s|%I64d|%d|%d|%s(%d)|%d|%d|%f|%f|%f|%d|%d|%d|%d\r\n", GetGameLogTypeString(i_nLogType)
// 			, InfinityCreateUID, MainServerID, InfluenceType, CharacterName, CharacterUID, Level, UnitKind, Experience, CurrentHP, CurrentDP, CurrentSP, Clear, KillCount, DeathCount);
		sprintf(o_szLogString, "%s|%I64d|%d|%d|%s(%d)|%d|%d|%f|%f|%f|%d|%d|%d|%d|(%d,%d,%d)\r\n", GetGameLogTypeString(i_nLogType)
			, InfinityCreateUID, MainServerID, InfluenceType, CharacterName, CharacterUID, Level, UnitKind, Experience, CurrentHP, CurrentDP, CurrentSP, Clear, KillCount, DeathCount, InfinityMode, InfinityLevel, InfinityPlayTick);
		// end 2014-01-24 by jhseol, ���� ���ӷα� ���� �߰�
		return o_szLogString;
	}
};

struct MSG_FL_LOG_INFINITY_FIN_ITEM : public FL_ITEM_LOG_BASE {
	// 199 - // 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���ӷα� �߰�, ����� ������ ���� ���� 
	ITEM_FOR_LOG	Item4Log;
	INT				ReaminTimeMSec;
	UID64_t			MainSvrItemUID;
	char* GetWriteLogString(int i_nLogType, char* o_szLogString) {
		char szTemp[1024], szItem[1024];
		sprintf(o_szLogString, "%s|%s|%s|%d|%I64d\r\n", GetGameLogTypeString(i_nLogType), GetLogItemBaseString(szTemp), Item4Log.GetLogItemString(szItem)
			, ReaminTimeMSec, MainSvrItemUID);
		return o_szLogString;
	}
};

struct MSG_FL_LOG_INFINITY_FIN_ALIVE_KEY_MONSTER {
	// 200 - // 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���ӷα� �߰�, ����� ����ִ� ���� ����
	MonIdx_t				MonsterIdx;

	char* GetWriteLogString(int i_nLogType, char* o_szLogString) {
		sprintf(o_szLogString, "%s|%d\r\n", GetGameLogTypeString(i_nLogType)
			, MonsterIdx);
		return o_szLogString;
	}
};

struct MSG_FL_LOG_PET_LEVEL : public FL_USER_LOG_BASE {
	// 213 - // 2011-09-15 by hskim, ��Ʈ�� �ý��� 2�� - ��Ʈ�� ���� ����
	BYTE		FromPetLevel;
	BYTE		ToPetLevel;
	LONGLONG	TotalPlayTime;
	// 2012-10-04 by hskim, �ѱ� ��ü ���� (����� IDC) - ��Ʈ�� �α� ����
	UID64_t		UniqueNumber;
	Experience_t	PetTotalExp;
	Experience_t	PetAcquisitionExp;
	// 2012-10-04 by hskim, �ѱ� ��ü ���� (����� IDC) - ��Ʈ�� �α� ����
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		char szTemp[1024];
		sprintf(o_szLogString, "%s|%s|%I64d|%f|%f|%d|%d|%I64d\r\n", GetGameLogTypeString(i_nLogType), GetLogBaseString(szTemp), UniqueNumber, PetTotalExp, PetAcquisitionExp, FromPetLevel, ToPetLevel, TotalPlayTime);
		return o_szLogString;
	}
};					// ��Ʈ�� ���� ��ȭ

// start 2011-12-12 by hskim, GLog 2��
struct MSG_FL_LOG_CONNECT_USER_NEW
{
	char AccountName[SIZE_MAX_ACCOUNT_NAME];

	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		sprintf(o_szLogString, "%s|%s\r\n", GetGameLogTypeString(i_nLogType), AccountName);
		return o_szLogString;
	}
};

struct MSG_FL_LOG_CONNECT_USER_LOGIN
{
	char AccountName[SIZE_MAX_ACCOUNT_NAME];

	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		sprintf(o_szLogString, "%s|%s\r\n", GetGameLogTypeString(i_nLogType), AccountName);
		return o_szLogString;
	}
};
// end 2011-12-12 by hskim, GLog 2��


// 2013-03-14 by bckim, Glog ����߰�
struct MSG_FL_GLOG_NEW_ACCOUNT_INFO
{
	ATUM_DATE_TIME	RegisteredDate;					// ��������
	INT			Type;								// ����Ÿ��
	UID64_t		AccountUniqueNumber;				// ����������ȣ 
	char AccountName[SIZE_MAX_ACCOUNT_NAME];		// �����̸�
	CHAR		CertifyCode[USER_CI_SIZE];			// CI ��		// 2014-02-10 by jhseol&bckim, ü�θ� - �ѱ� ���� ���� �߰�����

	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		sprintf(o_szLogString, "%s|%s|%d|%I64d|%s\r\n", GetGameLogTypeString(i_nLogType), RegisteredDate.GetDateTimeString(STRNBUF(SIZE_MAX_SQL_DATETIME_STRING))
			, Type, AccountUniqueNumber, AccountName);
		return o_szLogString;
	}
};
// End. 2013-03-14 by bckim, Glog ����߰�

// start 2012-10-08 by khkim, GLog
struct MSG_FL_LOG_ACCOUNTCONNECT
{
	SHORT		LogType;
	UID64_t		UserSerial;
	UID64_t		IP;
	int			GameServerID;

	MSG_FL_LOG_ACCOUNTCONNECT()
	{
		LogType = NULL;
		UserSerial = NULL;
		IP = NULL;
		GameServerID = NULL;
	}
};

struct MSG_FL_LOG_CHARDATA
{
	SHORT		LogType;
	UID64_t		UserSerial;
	UID64_t		CharSerial;
	SHORT		Class;
	SHORT		Lv;
	UID64_t		Exp;
	UID64_t		GameMoney;
	UID64_t		Playtime;
	int			GameServerID;

	MSG_FL_LOG_CHARDATA()
	{
		LogType = NULL;
		UserSerial = NULL;
		CharSerial = NULL;
		Class = NULL;
		Lv = NULL;
		Exp = NULL;
		GameMoney = NULL;
		Playtime = NULL;
		GameServerID = NULL;
	}
};

struct MSG_FL_LOG_ITEM
{
	SHORT		LogType;
	UID64_t		ItemSerial;
	UID64_t		Count1;
	UID64_t		Count2;
	UID64_t		CharSerial;
	int			CharLv;
	int			GameServerID;

	MSG_FL_LOG_ITEM()
	{
		LogType = NULL;
		ItemSerial = NULL;
		Count1 = NULL;
		Count2 = NULL;
		CharSerial = NULL;
		CharLv = NULL;
		GameServerID = NULL;
	}
};

struct MSG_FL_LOG_ITEMSTATE
{
	SHORT		LogType;
	UID64_t		ItemSerial;
	UID64_t		Count;
	UID64_t		CharSerial;
	int			CharLv;
	int			GameServerID;

	MSG_FL_LOG_ITEMSTATE()
	{
		LogType = NULL;
		ItemSerial = NULL;
		Count = NULL;
		CharSerial = NULL;
		CharLv = NULL;
		GameServerID = NULL;
	}
};

struct MSG_FL_LOG_SERVER
{
	SHORT		LogType;
	int			GameServerID;

	MSG_FL_LOG_SERVER()
	{
		LogType = NULL;
		GameServerID = NULL;
	}
};
// end 2012-10-08 by khkim, GLog 2��

// start 2012-01-16 by hskim, ��� - ȭ��
struct MSG_FL_LOG_STATISTICS_MONEY
{
	BYTE					FunctionType;
	StatisticsMoneyUnit_t	SPI;
	StatisticsMoneyUnit_t	WarPoint;
	StatisticsMoneyUnit_t	SystemOrb;
	StatisticsMoneyUnit_t	QuasarOrb;
	StatisticsMoneyUnit_t	ClusterOrb;
	StatisticsMoneyUnit_t	GalaxyOrb;
	StatisticsMoneyUnit_t	UniverseOrb;

	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		sprintf(o_szLogString, "%s|\r\n", GetGameLogTypeString(i_nLogType));
		return o_szLogString;
	}
};
// end 2012-01-16 by hskim, ��� - ȭ��

// 2012-10-10 by hskim, �Ⱓ�� �Ӽ� ���� (�Ⱓ�� ����) 
struct MSG_FL_LOG_FIXED_TERM_SHAPE_START : public FL_ITEM_LOG_BASE
{
	ITEM_FOR_LOG	Item4Log;
	INT				ShapeItemNum;		// ���� ��ȣ
	INT				ApplyItemNum;		// ���� ���� ������ ��ȣ
	ATUM_DATE_TIME	Starttime;			// ���� ���� ���� �ð�
	ATUM_DATE_TIME	Endtime;			// ���� ���� ���� �ð�

	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		char szTemp[1024], szItem[1024];
		sprintf(o_szLogString, "%s|%s|%s|%d|%d|%s|%s\r\n", GetGameLogTypeString(i_nLogType), GetLogItemBaseString(szTemp), Item4Log.GetLogItemString(szItem)
			, ShapeItemNum, ApplyItemNum, Starttime.GetDateTimeString(STRNBUF(SIZE_MAX_SQL_DATETIME_STRING)), Endtime.GetDateTimeString(STRNBUF(SIZE_MAX_SQL_DATETIME_STRING)));
		return o_szLogString;
	}
};

struct MSG_FL_LOG_FIXED_TERM_SHAPE_END : public FL_ITEM_LOG_BASE
{
	ITEM_FOR_LOG	Item4Log;
	INT				ShapeItemNum;		// ���� ���� ������ ��ȣ
	INT				ApplyItemNum;		// ���� ���� ������ ��ȣ
	ATUM_DATE_TIME	Starttime;			// ���� ���� ���� �ð�
	ATUM_DATE_TIME	Endtime;			// ���� ���� ���� �ð�

	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		char szTemp[1024], szItem[1024];
		sprintf(o_szLogString, "%s|%s|%s|%d|%d|%s|%s\r\n", GetGameLogTypeString(i_nLogType), GetLogItemBaseString(szTemp), Item4Log.GetLogItemString(szItem)
			, ShapeItemNum, ApplyItemNum, Starttime.GetDateTimeString(STRNBUF(SIZE_MAX_SQL_DATETIME_STRING)), Endtime.GetDateTimeString(STRNBUF(SIZE_MAX_SQL_DATETIME_STRING)));
		return o_szLogString;
	}
};
// end 2012-10-10 by hskim, �Ⱓ�� �Ӽ� ���� (�Ⱓ�� ����)

///////////////////////////////////////////////////////////////////////////////
// Monitor Server Protocol (T0: 0x30~)
///////////////////////////////////////////////////////////////////////////////

//////////////////////////////////
// T0_FM_MONITOR - Field Server Monitor
#define T1_FM_GET_NUM_CLIENTS			0x00	// No Body
#define T1_FM_GET_NUM_CLIENTS_OK		0x01
#define T1_FM_SHUTDOWN					0x02	// No Body
#define T1_FM_SHUTDOWN_OK				0x03	// No Body
#define T1_FM_PING						0x04	// No Body
#define T1_FM_PING_OK					0x05	// No Body
#define T1_FM_PRINTMAP					0x06	// No Body
#define T1_FM_SAVE_MAPBLOCK_INFO		0x07	// No Body
#define T1_FM_PRINT_DEBUG_MSG			0x08	// No Body
#define T1_FM_SEND_CHANNEL_INFO			0x09	// F->M
#define T1_FM_CHANGE_BANDWIDTH_FLAG		0x0A	// No Body
#define T1_FM_CHANGE_BANDWIDTH_FLAG_OK	0x0B	// ����� �÷��װ�
#define T1_FM_SET_MSG_PRINT_LEVEL		0x0C
#define T1_FM_GET_CHARACTER_INFO		0x0D
#define T1_FM_GET_CHARACTER_INFO_OK		0x0E
#define T1_FM_GET_MAP_USER_COUNTS		0x0F	// No Body
#define T1_FM_GET_MAP_USER_COUNTS_ACK	0x10
#define T1_FM_RELOAD_ITEM_INFO			0x11	// No Body
#define T1_FM_RELOAD_ITEM_INFO_OK		0x12	// No Body
#define T1_FM_RESET_NPC_SERVER			0x13	// No Body
#define T1_FM_RESET_NPC_SERVER_OK		0x14	// No Body
#define T1_FM_SERVER_THREAD_STATUS		0x15
#define T1_FM_SET_SERVICE_STATE			0x16
#define T1_FM_SET_SERVICE_STATE_OK		0x17	// No Body
#define T1_FM_RELOAD_SERVER_INFO		0x18
#define T1_FM_RELOAD_SERVER_INFO_OK		0x19	// No Body
#define T1_FM_INCREASE_CHANNEL			0x1A	// M->F, Channel �� ����
#define T1_FM_INCREASE_CHANNEL_OK		0x1B	// F->M, Channel �� ���� ���
#define T1_FM_SET_CHANNEL_STATE			0x1C	// M->F, Channel Enable/Disable
#define T1_FM_SET_CHANNEL_STATE_OK		0x1D	// F->M, Channel Enable/Disable ���
#define T1_FM_CITYWAR_CHANGE_WAR_TIME		0x20		// M->F
#define T1_FM_CITYWAR_CHANGED_OCCUPY_INFO	0x21	// F->M

#define T_FM_GET_NUM_CLIENTS			(MessageType_t)((T0_FM_MONITOR<<8)|T1_FM_GET_NUM_CLIENTS)
#define T_FM_GET_NUM_CLIENTS_OK			(MessageType_t)((T0_FM_MONITOR<<8)|T1_FM_GET_NUM_CLIENTS_OK)
#define T_FM_SHUTDOWN					(MessageType_t)((T0_FM_MONITOR<<8)|T1_FM_SHUTDOWN)
#define T_FM_SHUTDOWN_OK				(MessageType_t)((T0_FM_MONITOR<<8)|T1_FM_SHUTDOWN_OK)
#define T_FM_PING						(MessageType_t)((T0_FM_MONITOR<<8)|T1_FM_PING)
#define T_FM_PING_OK					(MessageType_t)((T0_FM_MONITOR<<8)|T1_FM_PING_OK)
#define T_FM_PRINTMAP					(MessageType_t)((T0_FM_MONITOR<<8)|T1_FM_PRINTMAP)
#define T_FM_SAVE_MAPBLOCK_INFO			(MessageType_t)((T0_FM_MONITOR<<8)|T1_FM_SAVE_MAPBLOCK_INFO)
#define T_FM_PRINT_DEBUG_MSG			(MessageType_t)((T0_FM_MONITOR<<8)|T1_FM_PRINT_DEBUG_MSG)
#define T_FM_SEND_CHANNEL_INFO			(MessageType_t)((T0_FM_MONITOR<<8)|T1_FM_SEND_CHANNEL_INFO)		// F->M
#define T_FM_CHANGE_BANDWIDTH_FLAG		(MessageType_t)((T0_FM_MONITOR<<8)|T1_FM_CHANGE_BANDWIDTH_FLAG)
#define T_FM_CHANGE_BANDWIDTH_FLAG_OK	(MessageType_t)((T0_FM_MONITOR<<8)|T1_FM_CHANGE_BANDWIDTH_FLAG_OK)
#define T_FM_SET_MSG_PRINT_LEVEL		(MessageType_t)((T0_FM_MONITOR<<8)|T1_FM_SET_MSG_PRINT_LEVEL)
#define T_FM_GET_CHARACTER_INFO			(MessageType_t)((T0_FM_MONITOR<<8)|T1_FM_GET_CHARACTER_INFO)
#define T_FM_GET_CHARACTER_INFO_OK		(MessageType_t)((T0_FM_MONITOR<<8)|T1_FM_GET_CHARACTER_INFO_OK)
#define T_FM_GET_MAP_USER_COUNTS		(MessageType_t)((T0_FM_MONITOR<<8)|T1_FM_GET_MAP_USER_COUNTS)
#define T_FM_GET_MAP_USER_COUNTS_ACK	(MessageType_t)((T0_FM_MONITOR<<8)|T1_FM_GET_MAP_USER_COUNTS_ACK)
#define T_FM_RELOAD_ITEM_INFO			(MessageType_t)((T0_FM_MONITOR<<8)|T1_FM_RELOAD_ITEM_INFO)
#define T_FM_RELOAD_ITEM_INFO_OK		(MessageType_t)((T0_FM_MONITOR<<8)|T1_FM_RELOAD_ITEM_INFO_OK)
#define T_FM_RESET_NPC_SERVER			(MessageType_t)((T0_FM_MONITOR<<8)|T1_FM_RESET_NPC_SERVER)
#define T_FM_RESET_NPC_SERVER_OK		(MessageType_t)((T0_FM_MONITOR<<8)|T1_FM_RESET_NPC_SERVER_OK)
#define T_FM_SERVER_THREAD_STATUS		(MessageType_t)((T0_FM_MONITOR<<8)|T1_FM_SERVER_THREAD_STATUS)
#define T_FM_SET_SERVICE_STATE			(MessageType_t)((T0_FM_MONITOR<<8)|T1_FM_SET_SERVICE_STATE)
#define T_FM_SET_SERVICE_STATE_OK		(MessageType_t)((T0_FM_MONITOR<<8)|T1_FM_SET_SERVICE_STATE_OK)	// No Body
#define T_FM_RELOAD_SERVER_INFO			(MessageType_t)((T0_FM_MONITOR<<8)|T1_FM_RELOAD_SERVER_INFO)
#define T_FM_RELOAD_SERVER_INFO_OK		(MessageType_t)((T0_FM_MONITOR<<8)|T1_FM_RELOAD_SERVER_INFO_OK)	// No Body
#define T_FM_INCREASE_CHANNEL			(MessageType_t)((T0_FM_MONITOR<<8)|T1_FM_INCREASE_CHANNEL)		// M->F, Channel �� ����
#define T_FM_INCREASE_CHANNEL_OK		(MessageType_t)((T0_FM_MONITOR<<8)|T1_FM_INCREASE_CHANNEL_OK)	// F->M, Channel �� ���� ���
#define T_FM_SET_CHANNEL_STATE			(MessageType_t)((T0_FM_MONITOR<<8)|T1_FM_SET_CHANNEL_STATE)		// M->F, Channel Enable/Disable
#define T_FM_SET_CHANNEL_STATE_OK		(MessageType_t)((T0_FM_MONITOR<<8)|T1_FM_SET_CHANNEL_STATE_OK)	// F->M, Channel Enable/Disable ���
#define T_FM_CITYWAR_CHANGE_WAR_TIME		(MessageType_t)((T0_FM_MONITOR<<8)|T1_FM_CITYWAR_CHANGE_WAR_TIME)		// M->F
#define T_FM_CITYWAR_CHANGED_OCCUPY_INFO	(MessageType_t)((T0_FM_MONITOR<<8)|T1_FM_CITYWAR_CHANGED_OCCUPY_INFO)	// F->M


typedef struct
{
	USHORT	NumOfClients;
	// 2013-10-01 by jekim, ���� �� ���º� ���� ���� �� �߰�.
	USHORT  NumOfBCU;
	USHORT  NumOfANI;
	// end 2013-10-01 by jekim, ���� �� ���º� ���� ���� �� �߰�.
} MSG_FM_GET_NUM_CLIENTS_OK;
typedef MSG_FM_GET_NUM_CLIENTS_OK		MSG_PM_GET_NUM_CLIENTS_OK;
typedef MSG_FM_GET_NUM_CLIENTS_OK		MSG_IM_GET_NUM_CLIENTS_OK;

typedef struct
{
	USHORT	LauncherVersion[4];
	USHORT	DeleteFileListVersion[4];
	USHORT	NoticeVersion[4];
	INT		NumOfClientVersions;
	ARRAY_(USHORT[8]);
} MSG_PM_RELOAD_VERSION_INFO;

typedef struct
{
	MAP_CHANNEL_INDEX		MapChannelIndex;
} MSG_FM_PRINTMAP;

typedef MSG_FM_PRINTMAP		MSG_NM_PRINTMAP;

typedef struct
{
	MAP_CHANNEL_INDEX		MapChannelIndex;
} MSG_FM_SAVE_MAPBLOCK_INFO, * PMSG_FM_SAVE_MAPBLOCK_INFO;

typedef MSG_FM_SAVE_MAPBLOCK_INFO		MSG_NM_SAVE_MAPBLOCK_INFO;

typedef struct
{
	int		IntParam1;
	int		IntParam2;
	float	FloatParam1;
	float	FloatParam2;
	char	StringParam[100];
} MSG_FM_PRINT_DEBUG_MSG;
typedef MSG_FM_PRINT_DEBUG_MSG		MSG_IM_PRINT_DEBUG_MSG;

#ifndef _ATUM_CLIENT

typedef struct
{
	PROJECTINFO			projectInfo;
	BOOL				bCityWarMap;
	SCITY_OCCUPY_INFO	cityWarOccupyInfo;
	ChannelIndex_t		ChannelIndex;	// ä���� �ε���
	BOOL				IsEnabled;		// ä���� Ȱ��ȭ ���ο� ���� ����
} MSG_FM_SEND_CHANNEL_INFO;			// F->M

typedef struct
{
	PROJECTINFO		projectInfo;
	ChannelIndex_t	ChannelIndex;	// ä���� �ε���
	BOOL			IsEnabled;		// ä���� Ȱ��ȭ ���ο� ���� ����
	UINT			LimitMonsterCount;
} MSG_NM_SEND_CHANNEL_INFO;

#endif // _ATUM_CLIENT

typedef struct
{
	BOOL	bChagedFlag;
} MSG_FM_CHANGE_BANDWIDTH_FLAG_OK, * PMSG_FM_CHANGE_BANDWIDTH_FLAG_OK;
typedef MSG_FM_CHANGE_BANDWIDTH_FLAG_OK		MSG_PM_CHANGE_BANDWIDTH_FLAG_OK;
typedef MSG_FM_CHANGE_BANDWIDTH_FLAG_OK		MSG_NM_CHANGE_BANDWIDTH_FLAG_OK;
typedef MSG_FM_CHANGE_BANDWIDTH_FLAG_OK		MSG_IM_CHANGE_BANDWIDTH_FLAG_OK;

typedef struct
{
	BYTE	Level;
} MSG_FM_SET_MSG_PRINT_LEVEL;
typedef MSG_FM_SET_MSG_PRINT_LEVEL		MSG_PM_SET_MSG_PRINT_LEVEL;
typedef MSG_FM_SET_MSG_PRINT_LEVEL		MSG_NM_SET_MSG_PRINT_LEVEL;
typedef MSG_FM_SET_MSG_PRINT_LEVEL		MSG_IM_SET_MSG_PRINT_LEVEL;

typedef struct
{
	char			CharacterName[SIZE_MAX_CHARACTER_NAME];
	UID32_t			CharacterUniqueNumber;
	ClientIndex_t	ClientIndex;
} MSG_FM_GET_CHARACTER_INFO;

typedef struct
{
	CHARACTER		CharacterInfo;
} MSG_FM_GET_CHARACTER_INFO_OK;

typedef struct
{
	MAP_CHANNEL_INDEX	MapChannIndex;
} MSG_FM_GET_MAP_USER_COUNTS;

typedef struct
{
	MAP_CHANNEL_INDEX	MapChannIndex;
	UINT		AccumulatedUserCounts;
	UINT		CurrentUserCounts;
	UINT		MaxUserCounts;
	UINT		AccumulatedMonsterCounts;
	UINT		CurrentMonsterCounts;
	// 2013-11-04 by jekim, ���� �ʺ��� �� ���º� ���� ���� �� �߰�.
	UINT        NumOfBCU;
	UINT        NumOfANI;
	// end 2013-11-04 by jekim, ���� �ʺ��� �� ���º� ���� ���� �� �߰�.
} MSG_FM_GET_MAP_USER_COUNTS_ACK;

typedef struct
{
	DWORD	dwThreadId;
	char	szThreadComment[SIZE_MAX_THREAD_COMMENT];
	DWORD	dwTimeGap;
} MSG_FM_SERVER_THREAD_STATUS;

// SERVER_SERVICE_TYPE_XXX
#define SERVER_SERVICE_TYPE_QUEST		((BYTE)0)	// ����Ʈ ����

typedef struct
{
	BYTE	ServiceType;	// SERVER_SERVICE_TYPE_XXX
	BOOL	ServiceState;	// TRUE: Start Service, FALSE: Stop Service
} MSG_FM_SET_SERVICE_STATE;

// SERVER_INFO_TYPE_XXX
#define SERVER_INFO_TYPE_QUEST			((BYTE)0)	// ����Ʈ

typedef struct
{
	BYTE	InfoType;		// SERVER_INFO_TYPE_XXX
} MSG_FM_RELOAD_SERVER_INFO;

typedef struct
{
	MapIndex_t	MapIndex;
} MSG_FM_INCREASE_CHANNEL;	// M->F, Channel �� ����

typedef struct
{
	MapIndex_t	MapIndex;
	INT			TotalChannelCount;
} MSG_FM_INCREASE_CHANNEL_OK;	// F->M, Channel �� ���� ���

typedef struct
{
	MAP_CHANNEL_INDEX	MapChannelIndex;
	BOOL				EnableChannel;		// TRUE: Enable, FALSE: Disable
} MSG_FM_SET_CHANNEL_STATE;		// M->F, Channel Enable/Disable

typedef struct
{
	MAP_CHANNEL_INDEX	MapChannelIndex;
	BOOL				IsEnabled;			// TRUE: Enable, FALSE: Disable
} MSG_FM_SET_CHANNEL_STATE_OK;	// F->M, Channel Enable/Disable ���
struct MSG_FM_CITYWAR_CHANGE_WAR_TIME
{
	MAP_CHANNEL_INDEX	MapChannelIndex;
	ATUM_DATE_TIME		CityWarATimeDefault;
	ATUM_DATE_TIME		CityWarATimeSetting;
};
struct MSG_FM_CITYWAR_CHANGED_OCCUPY_INFO
{
	MAP_CHANNEL_INDEX	MapChannelIndex;
	SCITY_OCCUPY_INFO	cityWarOccupyInfo;
};
///////////////////////////////////////////////////////////////////////////////
// PRE Server Monitor
#define T1_PM_GET_NUM_CLIENTS			0x00	// No Body
#define T1_PM_GET_NUM_CLIENTS_OK		0x01	// # of client
#define T1_PM_SHUTDOWN					0x02	// No Body
#define T1_PM_SHUTDOWN_OK				0x03	// No Body
#define T1_PM_CLOSE						0x04	// No Body
#define T1_PM_CLOSE_OK					0x05	// No Body
#define T1_PM_PING						0x06	// No Body
#define T1_PM_PING_OK					0x07	// No Body
#define T1_PM_RELOAD_VERSION_INFO		0x08	// M->P
#define T1_PM_RELOAD_VERSION_INFO_OK	0x09	// No Body
#define T1_PM_CHANGE_BANDWIDTH_FLAG		0x0A	// No Body
#define T1_PM_CHANGE_BANDWIDTH_FLAG_OK	0x0B	// ����� �÷��װ�
#define T1_PM_SET_MSG_PRINT_LEVEL		0x0C
#define T1_PM_PAUSE_SERVICE				0x0D
#define T1_PM_PAUSE_SERVICE_OK			0x0E
#define T1_PM_START_SERVICE				0x0F
#define T1_PM_START_SERVICE_OK			0x10
#define T1_PM_GET_SERVER_GROUP_INFO		0x11
#define T1_PM_GET_SERVER_GROUP_INFO_ACK	0x12
#define T1_PM_SET_LIMIT_GROUP_USER_COUNTS	0x13
#define T1_PM_SERVER_THREAD_STATUS			0x14
#define T1_PM_RELOAD_BLOCKED_ACCOUNTS		0x15	// No Body
#define T1_PM_RELOAD_BLOCKED_ACCOUNTS_OK	0x16	// No Body
#define T1_PM_SET_MGAME_EVENT_TYPE			0x17
#define T1_PM_CHANGE_ENABLE_SERVER_GROUP	0x18
#define T1_PM_PREPARE_SHUTDOWN				0x19	// 2006-08-04 by cmkwon, 

#define T1_PM_AUTO_UPDATE_FTP_SERVER_SETTING		0x20	// 2007-01-06 by cmkwon
#define T1_PM_AUTO_UPDATE_HTTP_SERVER_SETTING		0x21	// 2007-01-06 by cmkwon
#define T1_PM_RELOAD_VERSION_INFO_HEADER			0x22	// M->P
#define T1_PM_RELOAD_VERSION_INFO_LIST				0x23	// M->P
#define T1_PM_RELOAD_VERSION_INFO_DONE				0x24	// M->P

#define T_PM_GET_NUM_CLIENTS			(MessageType_t)((T0_PM_MONITOR<<8)|T1_PM_GET_NUM_CLIENTS)			// No Body
#define T_PM_GET_NUM_CLIENTS_OK			(MessageType_t)((T0_PM_MONITOR<<8)|T1_PM_GET_NUM_CLIENTS_OK)
#define T_PM_SHUTDOWN					(MessageType_t)((T0_PM_MONITOR<<8)|T1_PM_SHUTDOWN)					// No Body
#define T_PM_SHUTDOWN_OK				(MessageType_t)((T0_PM_MONITOR<<8)|T1_PM_SHUTDOWN_OK)				// No Body
#define T_PM_CLOSE						(MessageType_t)((T0_PM_MONITOR<<8)|T1_PM_CLOSE)						// No Body
#define T_PM_CLOSE_OK					(MessageType_t)((T0_PM_MONITOR<<8)|T1_PM_CLOSE_OK)					// No Body
#define T_PM_PING						(MessageType_t)((T0_PM_MONITOR<<8)|T1_PM_PING)						// No Body
#define T_PM_PING_OK					(MessageType_t)((T0_PM_MONITOR<<8)|T1_PM_PING_OK)					// No Body
#define T_PM_RELOAD_VERSION_INFO		(MessageType_t)((T0_PM_MONITOR<<8)|T1_PM_RELOAD_VERSION_INFO)		// M->P
#define T_PM_RELOAD_VERSION_INFO_OK		(MessageType_t)((T0_PM_MONITOR<<8)|T1_PM_RELOAD_VERSION_INFO_OK)	// No Body
#define T_PM_CHANGE_BANDWIDTH_FLAG		(MessageType_t)((T0_PM_MONITOR<<8)|T1_PM_CHANGE_BANDWIDTH_FLAG)		// No Body
#define T_PM_CHANGE_BANDWIDTH_FLAG_OK	(MessageType_t)((T0_PM_MONITOR<<8)|T1_PM_CHANGE_BANDWIDTH_FLAG_OK)
#define T_PM_SET_MSG_PRINT_LEVEL		(MessageType_t)((T0_PM_MONITOR<<8)|T1_PM_SET_MSG_PRINT_LEVEL)
#define T_PM_PAUSE_SERVICE				(MessageType_t)((T0_PM_MONITOR<<8)|T1_PM_PAUSE_SERVICE)
#define T_PM_PAUSE_SERVICE_OK			(MessageType_t)((T0_PM_MONITOR<<8)|T1_PM_PAUSE_SERVICE_OK)
#define T_PM_START_SERVICE				(MessageType_t)((T0_PM_MONITOR<<8)|T1_PM_START_SERVICE)
#define T_PM_START_SERVICE_OK			(MessageType_t)((T0_PM_MONITOR<<8)|T1_PM_START_SERVICE_OK)
#define T_PM_GET_SERVER_GROUP_INFO		(MessageType_t)((T0_PM_MONITOR<<8)|T1_PM_GET_SERVER_GROUP_INFO)
#define T_PM_GET_SERVER_GROUP_INFO_ACK	(MessageType_t)((T0_PM_MONITOR<<8)|T1_PM_GET_SERVER_GROUP_INFO_ACK)
#define T_PM_SET_LIMIT_GROUP_USER_COUNTS	(MessageType_t)((T0_PM_MONITOR<<8)|T1_PM_SET_LIMIT_GROUP_USER_COUNTS)
#define T_PM_SERVER_THREAD_STATUS		(MessageType_t)((T0_PM_MONITOR<<8)|T1_PM_SERVER_THREAD_STATUS)
#define T_PM_RELOAD_BLOCKED_ACCOUNTS	(MessageType_t)((T0_PM_MONITOR<<8)|T1_PM_RELOAD_BLOCKED_ACCOUNTS)		// No Body
#define T_PM_RELOAD_BLOCKED_ACCOUNTS_OK	(MessageType_t)((T0_PM_MONITOR<<8)|T1_PM_RELOAD_BLOCKED_ACCOUNTS_OK)	// No Body
#define T_PM_SET_MGAME_EVENT_TYPE		(MessageType_t)((T0_PM_MONITOR<<8)|T1_PM_SET_MGAME_EVENT_TYPE)
#define T_PM_CHANGE_ENABLE_SERVER_GROUP	(MessageType_t)((T0_PM_MONITOR<<8)|T1_PM_CHANGE_ENABLE_SERVER_GROUP)
#define T_PM_PREPARE_SHUTDOWN			(MessageType_t)((T0_PM_MONITOR<<8)|T1_PM_PREPARE_SHUTDOWN)		// 2006-08-04 by cmkwon

#define T_PM_AUTO_UPDATE_FTP_SERVER_SETTING			(MessageType_t)((T0_PM_MONITOR<<8)|T1_PM_AUTO_UPDATE_FTP_SERVER_SETTING)	// 2007-01-06 by cmkwon, P->M
#define T_PM_AUTO_UPDATE_HTTP_SERVER_SETTING		(MessageType_t)((T0_PM_MONITOR<<8)|T1_PM_AUTO_UPDATE_HTTP_SERVER_SETTING)	// 2007-01-06 by cmkwon, P->M
#define T_PM_RELOAD_VERSION_INFO_HEADER				(MessageType_t)((T0_PM_MONITOR<<8)|T1_PM_RELOAD_VERSION_INFO_HEADER)		// 2007-01-09 by cmkwon, M->P
#define T_PM_RELOAD_VERSION_INFO_LIST				(MessageType_t)((T0_PM_MONITOR<<8)|T1_PM_RELOAD_VERSION_INFO_LIST)			// 2007-01-09 by cmkwon, M->P
#define T_PM_RELOAD_VERSION_INFO_DONE				(MessageType_t)((T0_PM_MONITOR<<8)|T1_PM_RELOAD_VERSION_INFO_DONE)			// 2007-01-09 by cmkwon, M->P

typedef struct
{
	char		ServerGroupName[SIZE_MAX_SERVER_NAME];
} MSG_PM_GET_SERVER_GROUP_INFO;

typedef struct
{
	char		ServerGroupName[SIZE_MAX_SERVER_NAME];
	BOOL		bEnableServerGroup;
	SERVER_ID	IMServerID;
	UINT		AccumulatedGroupUserCounts;
	UINT		CurrentGroupUserCounts;
	UINT		MaxGroupUserCounts;
	UINT		LimitGroupUserCounts;
} MSG_PM_GET_SERVER_GROUP_INFO_ACK;

typedef struct
{
	char		ServerGroupName[SIZE_MAX_SERVER_NAME];
	UINT		LimitGroupUserCounts;
} MSG_PM_SET_LIMIT_GROUP_USER_COUNTS;

typedef MSG_FM_SERVER_THREAD_STATUS MSG_PM_SERVER_THREAD_STATUS;

typedef struct
{
	MGAME_EVENT_t		enMGameEvent;
} MSG_PM_SET_MGAME_EVENT_TYPE;

typedef struct
{
	char	ServerGroupName[SIZE_MAX_SERVER_NAME];
	BOOL	bEnableServerGroup;
} MSG_PM_CHANGE_ENABLE_SERVER_GROUP;

struct MSG_PM_PREPARE_SHUTDOWN				// 2006-08-04 by cmkwon
{
	char	ServerGroupName[SIZE_MAX_SERVER_NAME];
};

struct MSG_PM_AUTO_UPDATE_FTP_SERVER_SETTING		// 2007-01-06 by cmkwon, FTP Auto Update server 
{
	int			nAutoUpdateServerType;							// 2007-01-06 by cmkwon, AU_SERVER_TYPE_XXX
	char		FtpIP[SIZE_MAX_FTP_URL];
	USHORT		FtpPort;
	char		FtpAccountName[SIZE_MAX_ACCOUNT_NAME];
	char		FtpPassword[SIZE_MAX_PASSWORD];
	char		ClientFTPUpdateUploadDir[SIZE_MAX_FTP_FILE_PATH];
	char		LauncherFileUploadPath[SIZE_MAX_FTP_FILE_PATH];
	char		DeleteFileListUploadPath[SIZE_MAX_FTP_FILE_PATH];
	char		NoticeFileUploadPath[SIZE_MAX_FTP_FILE_PATH];
	char		szVersionListFileUploadPath[SIZE_MAX_FTP_FILE_PATH];		// 2007-01-08 by cmkwon, �߰���
};

struct MSG_PM_AUTO_UPDATE_HTTP_SERVER_SETTING		// 2007-01-06 by cmkwon, Http Auto Update server ���� �߰�
{
	int			nAutoUpdateServerType;							// 2007-01-06 by cmkwon, AU_SERVER_TYPE_XXX
	char		szDownloadHttpServerIP[SIZE_MAX_FTP_URL];
	USHORT		nDownloadHttpServerPort;
	char		szDownloadHttpServerAccountName[SIZE_MAX_ACCOUNT_NAME];
	char		szDownloadHttpServerPassword[SIZE_MAX_PASSWORD];
	char		szClientHttpUpdateDownloadDir[SIZE_MAX_FTP_FILE_PATH];
	char		szLauncherFileDownloadHttpPath[SIZE_MAX_FTP_FILE_PATH];
	char		szDeleteFileListDownloadHttpPath[SIZE_MAX_FTP_FILE_PATH];
	char		szNoticeFileDownloadHttpPath[SIZE_MAX_FTP_FILE_PATH];
	char		szVersionListFileDownloadHttpPath[SIZE_MAX_FTP_FILE_PATH];
};

struct MSG_PM_RELOAD_VERSION_INFO_HEADER			// 2007-01-09 by cmkwon
{
	USHORT	LauncherVersion[4];
	USHORT	DeleteFileListVersion[4];
	USHORT	NoticeVersion[4];
	INT		TotalNumOfClientVersions;
};

struct MSG_PM_RELOAD_VERSION_INFO_LIST				// 2007-01-09 by cmkwon
{
	INT		NumOfClientVersions;
	ARRAY_(USHORT[8]);
};


//////////////////////////////////
// NPC Server Monitor
#define T1_NM_GET_NUM_MONSTERS				0x00	// No Body
#define T1_NM_GET_NUM_MONSTERS_OK			0x01
#define T1_NM_SHUTDOWN						0x02	// No Body
#define T1_NM_SHUTDOWN_OK					0x03	// No Body
#define T1_NM_PING							0x04	// No Body
#define T1_NM_PING_OK						0x05	// No Body
#define T1_NM_PRINTMAP						0x06	// No Body
#define T1_NM_SAVE_MAPBLOCK_INFO			0x07	// No Body
#define T1_NM_SEND_CHANNEL_INFO				0x08	//
#define T1_NM_CHANGE_BANDWIDTH_FLAG			0x0A	// No Body
#define T1_NM_CHANGE_BANDWIDTH_FLAG_OK		0x0B	// ����� �÷��װ�
#define T1_NM_SET_MSG_PRINT_LEVEL			0x0C
#define T1_NM_GET_MAP_USER_COUNTS			0x0D	// No Body
#define T1_NM_GET_MAP_USER_COUNTS_ACK		0x0E
#define T1_NM_SET_LIMIT_MONSTER_COUNT		0x0F
#define T1_NM_SET_LIMIT_MONSTER_COUNT_ACK	0x10
#define T1_NM_SERVER_THREAD_STATUS			0x11
#define T1_NM_SET_CHANNEL_STATE_OK			0x12	// N->M, Channel Enable/Disable ���

#define T_NM_GET_NUM_MONSTERS				(MessageType_t)((T0_NM_MONITOR<<8)|T1_NM_GET_NUM_MONSTERS)
#define T_NM_GET_NUM_MONSTERS_OK			(MessageType_t)((T0_NM_MONITOR<<8)|T1_NM_GET_NUM_MONSTERS_OK)
#define T_NM_SHUTDOWN						(MessageType_t)((T0_NM_MONITOR<<8)|T1_NM_SHUTDOWN)
#define T_NM_SHUTDOWN_OK					(MessageType_t)((T0_NM_MONITOR<<8)|T1_NM_SHUTDOWN_OK)
#define T_NM_PING							(MessageType_t)((T0_NM_MONITOR<<8)|T1_NM_PING)
#define T_NM_PING_OK						(MessageType_t)((T0_NM_MONITOR<<8)|T1_NM_PING_OK)
#define T_NM_PRINTMAP						(MessageType_t)((T0_NM_MONITOR<<8)|T1_NM_PRINTMAP)
#define T_NM_SAVE_MAPBLOCK_INFO				(MessageType_t)((T0_NM_MONITOR<<8)|T1_NM_SAVE_MAPBLOCK_INFO)
#define T_NM_SEND_CHANNEL_INFO				(MessageType_t)((T0_NM_MONITOR<<8)|T1_NM_SEND_CHANNEL_INFO)
#define T_NM_CHANGE_BANDWIDTH_FLAG			(MessageType_t)((T0_NM_MONITOR<<8)|T1_NM_CHANGE_BANDWIDTH_FLAG)
#define T_NM_CHANGE_BANDWIDTH_FLAG_OK		(MessageType_t)((T0_NM_MONITOR<<8)|T1_NM_CHANGE_BANDWIDTH_FLAG_OK)
#define T_NM_SET_MSG_PRINT_LEVEL			(MessageType_t)((T0_NM_MONITOR<<8)|T1_NM_SET_MSG_PRINT_LEVEL)
#define T_NM_GET_MAP_USER_COUNTS			(MessageType_t)((T0_NM_MONITOR<<8)|T1_NM_GET_MAP_USER_COUNTS)
#define T_NM_GET_MAP_USER_COUNTS_ACK		(MessageType_t)((T0_NM_MONITOR<<8)|T1_NM_GET_MAP_USER_COUNTS_ACK)
#define T_NM_SET_LIMIT_MONSTER_COUNT		(MessageType_t)((T0_NM_MONITOR<<8)|T1_NM_SET_LIMIT_MONSTER_COUNT)
#define T_NM_SET_LIMIT_MONSTER_COUNT_ACK	(MessageType_t)((T0_NM_MONITOR<<8)|T1_NM_SET_LIMIT_MONSTER_COUNT_ACK)
#define T_NM_SERVER_THREAD_STATUS			(MessageType_t)((T0_NM_MONITOR<<8)|T1_NM_SERVER_THREAD_STATUS)
#define T_NM_SET_CHANNEL_STATE_OK			(MessageType_t)((T0_NM_MONITOR<<8)|T1_NM_SET_CHANNEL_STATE_OK)	// N->M, Channel Enable/Disable ���

typedef struct
{
	USHORT	NumOfMonsters;
} MSG_NM_GET_NUM_MONSTERS_OK;

typedef MSG_FM_GET_MAP_USER_COUNTS			MSG_NM_GET_MAP_USER_COUNTS;

typedef MSG_FM_GET_MAP_USER_COUNTS_ACK		MSG_NM_GET_MAP_USER_COUNTS_ACK;

typedef struct
{
	MAP_CHANNEL_INDEX	MapChannelIndex;
	UINT		SetLimitMonsterCount;
} MSG_NM_SET_LIMIT_MONSTER_COUNT;

typedef MSG_NM_SET_LIMIT_MONSTER_COUNT		MSG_NM_SET_LIMIT_MONSTER_COUNT_ACK;
typedef MSG_FM_SERVER_THREAD_STATUS			MSG_NM_SERVER_THREAD_STATUS;
typedef MSG_FM_SET_CHANNEL_STATE_OK			MSG_NM_SET_CHANNEL_STATE_OK;

//////////////////////////////////////////////////////////////////////////
// IM Server Monitor
#define T1_IM_GET_NUM_CLIENTS			0x00	// No Body
#define T1_IM_GET_NUM_CLIENTS_OK		0x01
#define T1_IM_SHUTDOWN					0x02	// No Body
#define T1_IM_SHUTDOWN_OK				0x03	// No Body
#define T1_IM_PING						0x04	// No Body
#define T1_IM_PING_OK					0x05	// No Body
#define T1_IM_PRINTMAP					0x06	// No Body
#define T1_IM_PRINT_DEBUG_MSG			0x08	// No Body
#define T1_IM_CHANGE_BANDWIDTH_FLAG		0x0A	// No Body
#define T1_IM_CHANGE_BANDWIDTH_FLAG_OK	0x0B	// ����� �÷��װ�
#define T1_IM_SET_MSG_PRINT_LEVEL		0x0C
#define T1_IM_GET_TOTAL_USER_COUNTS		0x0D	// No Body
#define T1_IM_GET_TOTAL_USER_COUNTS_ACK	0x0E
#define T1_IM_SERVER_THREAD_STATUS		0x0F

#define T_IM_GET_NUM_CLIENTS			(MessageType_t)((T0_IM_MONITOR<<8)|T1_IM_GET_NUM_CLIENTS)
#define T_IM_GET_NUM_CLIENTS_OK			(MessageType_t)((T0_IM_MONITOR<<8)|T1_IM_GET_NUM_CLIENTS_OK)
#define T_IM_SHUTDOWN					(MessageType_t)((T0_IM_MONITOR<<8)|T1_IM_SHUTDOWN)
#define T_IM_SHUTDOWN_OK				(MessageType_t)((T0_IM_MONITOR<<8)|T1_IM_SHUTDOWN_OK)
#define T_IM_PING						(MessageType_t)((T0_IM_MONITOR<<8)|T1_IM_PING)
#define T_IM_PING_OK					(MessageType_t)((T0_IM_MONITOR<<8)|T1_IM_PING_OK)
#define T_IM_PRINTMAP					(MessageType_t)((T0_IM_MONITOR<<8)|T1_IM_PRINTMAP)
#define T_IM_PRINT_DEBUG_MSG			(MessageType_t)((T0_IM_MONITOR<<8)|T1_IM_PRINT_DEBUG_MSG)
#define T_IM_CHANGE_BANDWIDTH_FLAG		(MessageType_t)((T0_IM_MONITOR<<8)|T1_IM_CHANGE_BANDWIDTH_FLAG)
#define T_IM_CHANGE_BANDWIDTH_FLAG_OK	(MessageType_t)((T0_IM_MONITOR<<8)|T1_IM_CHANGE_BANDWIDTH_FLAG_OK)
#define T_IM_SET_MSG_PRINT_LEVEL		(MessageType_t)((T0_IM_MONITOR<<8)|T1_IM_SET_MSG_PRINT_LEVEL)
#define T_IM_GET_TOTAL_USER_COUNTS		(MessageType_t)((T0_IM_MONITOR<<8)|T1_IM_GET_TOTAL_USER_COUNTS)
#define T_IM_GET_TOTAL_USER_COUNTS_ACK	(MessageType_t)((T0_IM_MONITOR<<8)|T1_IM_GET_TOTAL_USER_COUNTS_ACK)
#define T_IM_SERVER_THREAD_STATUS		(MessageType_t)((T0_IM_MONITOR<<8)|T1_IM_SERVER_THREAD_STATUS)

typedef struct
{
	char	FieldIP[SIZE_MAX_IPADDRESS];
	USHORT	FieldListenPort;
	UINT	AccumulatedFieldUserCounts;
	UINT	CurrentFieldUserCounts;
	UINT	MaxFieldUserCounts;
	UINT	AccumulatedFieldMonsterCounts;
	UINT	CurrentFieldMonsterCounts;
} MSG_FIELDSERVER_USERCOUNTS;

typedef struct
{
	UINT	AccumulatedTotalUserCounts;
	UINT	CurrentTotalUserCounts;
	UINT	MaxTotalUserCounts;
} MSG_IM_GET_TOTAL_USER_COUNTS_ACK;

typedef MSG_FM_SERVER_THREAD_STATUS MSG_IM_SERVER_THREAD_STATUS;

//////////////////////////////////////////////////////////////////////////
// PreServer <-> admin tool 
#define T1_PA_ADMIN_CONNECT				0x00
#define T1_PA_ADMIN_CONNECT_OK			0x01
#define T1_PA_ADMIN_CHANGE_SERVER_STATE	0x02
#define T1_PA_ADMIN_GET_ACCOUNT_INFO	0x03
#define T1_PA_ADMIN_GET_ACCOUNT_INFO_OK	0x04
#define T1_PA_ADMIN_DISCONNECT_USER		0x05
#define T1_PA_ADMIN_DISCONNECT_USER_OK	0x06
#define T1_PA_ADMIN_BLOCK_ACCOUNT		0x07
#define T1_PA_ADMIN_BLOCK_ACCOUNT_OK	0x08
#define T1_PA_ADMIN_UNBLOCK_ACCOUNT		0x09
#define T1_PA_ADMIN_UNBLOCK_ACCOUNT_OK	0x0A
#define T1_PA_ADMIN_GET_SERVER_INFO		0x0B
#define T1_PA_ADMIN_GET_SERVER_INFO_OK	0x0C
#define T1_PA_ADMIN_GET_ACCOUNT_LIST	0x0D
#define T1_PA_ADMIN_GET_ACCOUNT_LIST_OK	0x0E
#define T1_PA_ADMIN_RELOAD_HAPPYEV		0x0F		// A->P, No body, 2006-08-28 by cmkwon
#define T1_PA_ADMIN_RELOAD_ITEMEV		0x10		// A->P, No body, 2006-08-31 by dhjin
#define T1_PA_ADMIN_UPDATE_PCBANGLIST	0x11		// A->P, No body, 2007-01-22 by dhjin
#define T1_PA_ADMIN_UPDATE_STRATEGYPOINT_NOTSUMMONTIME	0x12		// A->P, No body, 2007-03-06 by dhjin
#define T1_PA_ADMIN_PETITION_SET_PERIOD	0x13			// 2007-11-19 by cmkwon, �����ý��� ������Ʈ - A->P
#define T1_PA_ADMIN_SET_DBSERVER_GROUP		0x14			// 2008-04-29 by cmkwon, ������ ���� DB�� �߰�(�ű� ���� ĳ���� ���� ���� �ý����߰�) - A->P
#define T1_PA_ADMIN_SET_DBSERVER_GROUP_OK	0x15			// 2008-04-29 by cmkwon, ������ ���� DB�� �߰�(�ű� ���� ĳ���� ���� ���� �ý����߰�) - P->A
#define T1_PA_ADMIN_RELOAD_ADMIN_NOTICE_SYSTEM	0x16		// 2009-01-14 by cmkwon, ��� �ڵ� ���� �ý��� ���� - A->P, �� ������ �ڵ� ���� ���ε�
#define T1_PA_ADMIN_RELOAD_WORLDRANKING			0x17		// 2009-02-12 by cmkwon, EP3-3 ���巩ŷ�ý��� ���� - A->P, 
#define T1_PA_ADMIN_RELOAD_INFLUENCERATE		0x18		// A->P // 2009-09-16 by cmkwon, ���� �ʱ�ȭ�� ���¡ ���� ���� - 
#define T1_PA_ADMIN_RELOAD_GUILD_INFO			0x19		// A->P	// 2014-02-11 by bckim, �����ʱ�ȭ�� ���� ����ȭó��


// 2012-06-07 by hskim, ������ ���� ���� ��ȭ - ���� ���� ����� �α� ����
#define T1_PA_ADMIN_LOG_ACCOUNT_ACCOUNTTYPE_CHANGE					0x1B		
#define T1_PA_ADMIN_LOG_CHARACTER_RACEACCOUNTTYPE_CHANGE			0x1C
// end 2012-06-07 by hskim, ������ ���� ���� ��ȭ - ���� ���� ����� �α� ����
#define T1_PA_ADMIN_STRATRGYPOINT_INFO_CHANGE						0x1D		// 2012-11-13 by jhseol, ���� �ý��� ������ - ������, ������ ���� �ǽð� ����

#define T_PA_ADMIN_CONNECT				(MessageType_t)((T0_PA_ADMIN<<8)|T1_PA_ADMIN_CONNECT)				// A->P
#define T_PA_ADMIN_CONNECT_OK			(MessageType_t)((T0_PA_ADMIN<<8)|T1_PA_ADMIN_CONNECT_OK)			// P->A
#define T_PA_ADMIN_CHANGE_SERVER_STATE	(MessageType_t)((T0_PA_ADMIN<<8)|T1_PA_ADMIN_CHANGE_SERVER_STATE)	// P->A
#define T_PA_ADMIN_GET_ACCOUNT_INFO		(MessageType_t)((T0_PA_ADMIN<<8)|T1_PA_ADMIN_GET_ACCOUNT_INFO)		// A->P
#define T_PA_ADMIN_GET_ACCOUNT_INFO_OK	(MessageType_t)((T0_PA_ADMIN<<8)|T1_PA_ADMIN_GET_ACCOUNT_INFO_OK)	// P->A
#define T_PA_ADMIN_DISCONNECT_USER		(MessageType_t)((T0_PA_ADMIN<<8)|T1_PA_ADMIN_DISCONNECT_USER)		// A->P
#define T_PA_ADMIN_DISCONNECT_USER_OK	(MessageType_t)((T0_PA_ADMIN<<8)|T1_PA_ADMIN_DISCONNECT_USER_OK)	// P->A
#define T_PA_ADMIN_BLOCK_ACCOUNT		(MessageType_t)((T0_PA_ADMIN<<8)|T1_PA_ADMIN_BLOCK_ACCOUNT)			// A->P
#define T_PA_ADMIN_BLOCK_ACCOUNT_OK		(MessageType_t)((T0_PA_ADMIN<<8)|T1_PA_ADMIN_BLOCK_ACCOUNT_OK)		// P->A
#define T_PA_ADMIN_UNBLOCK_ACCOUNT		(MessageType_t)((T0_PA_ADMIN<<8)|T1_PA_ADMIN_UNBLOCK_ACCOUNT)		// A->P
#define T_PA_ADMIN_UNBLOCK_ACCOUNT_OK	(MessageType_t)((T0_PA_ADMIN<<8)|T1_PA_ADMIN_UNBLOCK_ACCOUNT_OK)	// P->A
#define T_PA_ADMIN_GET_SERVER_INFO		(MessageType_t)((T0_PA_ADMIN<<8)|T1_PA_ADMIN_GET_SERVER_INFO)		// A->P, no body
#define T_PA_ADMIN_GET_SERVER_INFO_OK	(MessageType_t)((T0_PA_ADMIN<<8)|T1_PA_ADMIN_GET_SERVER_INFO_OK)	// P->A
#define T_PA_ADMIN_GET_ACCOUNT_LIST		(MessageType_t)((T0_PA_ADMIN<<8)|T1_PA_ADMIN_GET_ACCOUNT_LIST)		// A->P
#define T_PA_ADMIN_GET_ACCOUNT_LIST_OK	(MessageType_t)((T0_PA_ADMIN<<8)|T1_PA_ADMIN_GET_ACCOUNT_LIST_OK)	// P->A
#define T_PA_ADMIN_RELOAD_HAPPYEV		(MessageType_t)((T0_PA_ADMIN<<8)|T1_PA_ADMIN_RELOAD_HAPPYEV)		// A->P, No body, 2006-08-28 by cmkwon
#define T_PA_ADMIN_RELOAD_ITEMEV		(MessageType_t)((T0_PA_ADMIN<<8)|T1_PA_ADMIN_RELOAD_ITEMEV)			// A->P, No body, 2006-08-31 by dhjin
#define T_PA_ADMIN_UPDATE_PCBANGLIST	(MessageType_t)((T0_PA_ADMIN<<8)|T1_PA_ADMIN_UPDATE_PCBANGLIST)		// A->P, No body, 2007-01-22 by dhjin
#define T_PA_ADMIN_UPDATE_STRATEGYPOINT_NOTSUMMONTIME	(MessageType_t)((T0_PA_ADMIN<<8)|T1_PA_ADMIN_UPDATE_STRATEGYPOINT_NOTSUMMONTIME)		// A->P, No body, 2007-01-22 by dhjin
#define T_PA_ADMIN_PETITION_SET_PERIOD	(MessageType_t)((T0_PA_ADMIN<<8)|T1_PA_ADMIN_PETITION_SET_PERIOD)	// 2007-11-19 by cmkwon, �����ý��� ������Ʈ - A->P
#define T_PA_ADMIN_SET_DBSERVER_GROUP		(MessageType_t)((T0_PA_ADMIN<<8)|T1_PA_ADMIN_SET_DBSERVER_GROUP)	// 2008-04-29 by cmkwon, ������ ���� DB�� �߰�(�ű� ���� ĳ���� ���� ���� �ý����߰�) - A->P
#define T_PA_ADMIN_SET_DBSERVER_GROUP_OK	(MessageType_t)((T0_PA_ADMIN<<8)|T1_PA_ADMIN_SET_DBSERVER_GROUP_OK)	// 2008-04-29 by cmkwon, ������ ���� DB�� �߰�(�ű� ���� ĳ���� ���� ���� �ý����߰�) - P->A
#define T_PA_ADMIN_RELOAD_ADMIN_NOTICE_SYSTEM	(MessageType_t)((T0_PA_ADMIN<<8)|T1_PA_ADMIN_RELOAD_ADMIN_NOTICE_SYSTEM)	// 2009-01-14 by cmkwon, ��� �ڵ� ���� �ý��� ���� - A->P, �� ������ �ڵ� ���� ���ε�
#define T_PA_ADMIN_RELOAD_WORLDRANKING			(MessageType_t)((T0_PA_ADMIN<<8)|T1_PA_ADMIN_RELOAD_WORLDRANKING)			// 2009-02-12 by cmkwon, EP3-3 ���巩ŷ�ý��� ���� - A->P, 
#define T_PA_ADMIN_RELOAD_INFLUENCERATE			(MessageType_t)((T0_PA_ADMIN<<8)|T1_PA_ADMIN_RELOAD_INFLUENCERATE)		// A->P // 2009-09-16 by cmkwon, ���� �ʱ�ȭ�� ���¡ ���� ���� - 
#define T_PA_ADMIN_RELOAD_GUILD_INFO			(MessageType_t)((T0_PA_ADMIN<<8)|T1_PA_ADMIN_RELOAD_GUILD_INFO)			// A->P, // 2014-02-11 by bckim, �����ʱ�ȭ�� ���� ����ȭó��

// 2012-06-07 by hskim, ������ ���� ���� ��ȭ - ���� ���� ����� �α� ����
#define T_PA_ADMIN_LOG_ACCOUNT_ACCOUNTTYPE_CHANGE			(MessageType_t)((T0_PA_ADMIN<<8)|T1_PA_ADMIN_LOG_ACCOUNT_ACCOUNTTYPE_CHANGE)		// A->P
#define T_PA_ADMIN_LOG_CHARACTER_RACEACCOUNTTYPE_CHANGE		(MessageType_t)((T0_PA_ADMIN<<8)|T1_PA_ADMIN_LOG_CHARACTER_RACEACCOUNTTYPE_CHANGE)	// A->P
// end 2012-06-07 by hskim, ������ ���� ���� ��ȭ - ���� ���� ����� �α� ����
#define T_PA_ADMIN_STRATRGYPOINT_INFO_CHANGE				(MessageType_t)((T0_PA_ADMIN<<8)|T1_PA_ADMIN_STRATRGYPOINT_INFO_CHANGE)	// A->P	// 2012-11-13 by jhseol, ���� �ý��� ������ - ������

typedef struct
{
	char	UID[SIZE_MAX_ACCOUNT_NAME];
	char	PWD[SIZE_MAX_PASSWORD];
	DWORD	Padding[SIZE_MAX_PACKET_PADDING];		// 2011-07-21 by hskim, ���� ���� ���� - ���� ������ ȣȯ �ȵǵ��� ����ü ũ�� �ٲ�
} MSG_PA_ADMIN_CONNECT;

typedef struct
{
	// 2006-04-15 by cmkwon, �ʵ� ����
	//	BYTE	AuthOK;				// 0: FALSE, 1:TRUE
	USHORT	AccountType0;		// ���� ����
	DWORD	Padding[SIZE_MAX_PACKET_PADDING];		// 2011-07-21 by hskim, ���� ���� ���� - ���� ������ ȣȯ �ȵǵ��� ����ü ũ�� �ٲ�
	int		IsMasang;	// 2012-06-16 by jhseol, �Ʒ��� �߰�����part2 - ���� : ���� ���ΰ� �ƴϸ� ��� �Ұ�
} MSG_PA_ADMIN_CONNECT_OK;

typedef struct
{
	SERVER_ID	ServerID;
	INT			ServerType;		// ENServerType, ST_XXX
	BYTE		ServerState;	// SERVER_STATE_XXX
} MSG_PA_ADMIN_CHANGE_SERVER_STATE;

typedef struct
{
	char	AccountName[SIZE_MAX_ACCOUNT_NAME];
	char	CharacterName[SIZE_MAX_CHARACTER_NAME];
} MSG_PA_ADMIN_GET_ACCOUNT_INFO;

class CAccountInfo;

struct MEX_ACCOUNT_INFO_PRE_SERVER
{
	MEX_ACCOUNT_INFO_PRE_SERVER()
	{
		memset(this, 0x00, sizeof(MEX_ACCOUNT_INFO_PRE_SERVER));
	}

	char				AccountName[SIZE_MAX_ACCOUNT_NAME];
	UID32_t				AccountUniqueNumber;
	char				PublicClientIP[SIZE_MAX_IPADDRESS];
	char				PrivateClientIP[SIZE_MAX_IPADDRESS];
	char				CurrentCharacterName[SIZE_MAX_CHARACTER_NAME];
	UID32_t				CurrentCharacterUniqueNumber;
	char				CurrentServerGroup[SIZE_MAX_SERVER_NAME];
	SERVER_ID			CurrentFieldServerID;
	MAP_CHANNEL_INDEX	CurrentMapChannel;
	INT					ClientState;

#ifdef _ATUM_PRE_SERVER
	// operator overloading
	MEX_ACCOUNT_INFO_PRE_SERVER& operator=(const CAccountInfo& rhs);
#endif // _ATUM_IM_SERVER
};

typedef struct
{
	BYTE	IsOnline;			// 0: FALSE, 1:TRUE
	BYTE	IsBlocked;			// 0: FALSE, 1:TRUE
	SBLOCKED_ACCOUNT_INFO		BlockedAccountInfo;
	MEX_ACCOUNT_INFO_PRE_SERVER	AccountInfo;
} MSG_PA_ADMIN_GET_ACCOUNT_INFO_OK;

typedef struct
{
	char	AccountName[SIZE_MAX_ACCOUNT_NAME];
	char	CharacterName[SIZE_MAX_CHARACTER_NAME];
} MSG_PA_ADMIN_DISCONNECT_USER;

typedef struct
{
	char	AccountName[SIZE_MAX_ACCOUNT_NAME];
} MSG_PA_ADMIN_DISCONNECT_USER_OK;

typedef SBLOCKED_ACCOUNT_INFO		MSG_PA_ADMIN_BLOCK_ACCOUNT;

typedef SBLOCKED_ACCOUNT_INFO		MSG_PA_ADMIN_BLOCK_ACCOUNT_OK;


// typedef struct
// {
// 	char	AccountName[SIZE_MAX_ACCOUNT_NAME];
// } MSG_PA_ADMIN_UNBLOCK_ACCOUNT;
typedef SBLOCKED_ACCOUNT_INFO		MSG_PA_ADMIN_UNBLOCK_ACCOUNT;	// 2008-01-30 by cmkwon, ���� ���� �α� ����� ���� - 

typedef struct
{
	char	AccountName[SIZE_MAX_ACCOUNT_NAME];
} MSG_PA_ADMIN_UNBLOCK_ACCOUNT_OK;

// 2012-06-07 by hskim, ������ ���� ���� ��ȭ - ���� ���� ����� �α� ����
typedef struct
{
	char	AccountName[SIZE_MAX_ACCOUNT_NAME];
	UID32_t	AccountUniqueNumber;
	USHORT	OldAccountType;
	USHORT	NewAccountType;
} MSG_PA_ADMIN_LOG_ACCOUNT_ACCOUNTTYPE_CHANGE;

typedef struct
{
	char	AccountName[SIZE_MAX_ACCOUNT_NAME];
	char	CharacterName[SIZE_MAX_CHARACTER_NAME];
	UID32_t	AccountUniqueNumber;
	UID32_t	CharacterUniqueNumber;
	USHORT	OldAccountType;
	USHORT	NewAccountType;
} MSG_PA_ADMIN_LOG_CHARACTER_RACEACCOUNTTYPE_CHANGE;
// end 2012-06-07 by hskim, ������ ���� ���� ��ȭ - ���� ���� ����� �α� ����

//typedef struct
//{
//} MSG_PA_ADMIN_GET_SERVER_INFO;

#define SERVER_STATE_NOT_ACTIVE	((BYTE)0)
#define SERVER_STATE_NORMAL		((BYTE)1)
#define SERVER_STATE_ABNORMAL	((BYTE)2)

// 2008-04-29 by cmkwon, ������ ���� DB�� �߰�(�ű� ���� ĳ���� ���� ���� �ý����߰�) - MEX_SERVER_GROUP_INFO_FOR_ADMIN �� ��ü ��
// struct MEX_SERVER_INFO_FOR_ADMIN
// {
// 	char		ServerName[SIZE_MAX_SERVER_NAME];
// 	INT			ServerType;							// ENServerType, ST_XXX
// 	SERVER_ID	ServerID;
// 	INT			UserCount;						
// 	BYTE		ServerState;						// SERVER_STATE_XXX
// };

struct MEX_SERVER_GROUP_INFO_FOR_ADMIN				// 2008-04-29 by cmkwon, ������ ���� DB�� �߰�(�ű� ���� ĳ���� ���� ���� �ý����߰�) - 
{
	char		ServerName[SIZE_MAX_SERVER_NAME];
	SERVER_ID	IMServerID;
	INT			UserCount;
	BYTE		IMServerState;						// SERVER_STATE_XXX
	SERVER_ID	FieldServerID;
	BYTE		FieldServerState;					// SERVER_STATE_XXX
	int			ServerGroupID;						// 2008-04-29 by cmkwon, ������ ���� DB�� �߰�(�ű� ���� ĳ���� ���� ���� �ý����߰�) - 
	int			LimitUserCount;						// 2008-04-29 by cmkwon, ������ ���� DB�� �߰�(�ű� ���� ĳ���� ���� ���� �ý����߰�) - 
	BOOL		LockCreateCharacterForNewAccount;	// 2008-04-29 by cmkwon, ������ ���� DB�� �߰�(�ű� ���� ĳ���� ���� ���� �ý����߰�) - 
};

typedef struct
{
	// 2008-04-29 by cmkwon, ������ ���� DB�� �߰�(�ű� ���� ĳ���� ���� ���� �ý����߰�) - 
	//	INT		NumOfServers;
	//	ARRAY_(MEX_SERVER_INFO_FOR_ADMIN);
	INT		NumOfServerGroups;						// 2008-04-29 by cmkwon, ������ ���� DB�� �߰�(�ű� ���� ĳ���� ���� ���� �ý����߰�) - 
	ARRAY_(MEX_SERVER_GROUP_INFO_FOR_ADMIN);		// 2008-04-29 by cmkwon, ������ ���� DB�� �߰�(�ű� ���� ĳ���� ���� ���� �ý����߰�) - 
} MSG_PA_ADMIN_GET_SERVER_INFO_OK;

typedef struct
{
	char	ServerName[SIZE_MAX_SERVER_NAME];
} MSG_PA_ADMIN_GET_ACCOUNT_LIST;

struct MEX_SIMPLE_ACCOUNT_INFO_FOR_ADMIN
{
	char	AccountName[SIZE_MAX_ACCOUNT_NAME];
	char	CharacterName[SIZE_MAX_CHARACTER_NAME];
};

typedef struct
{
	INT		NumOfAccounts;
	ARRAY_(MEX_SIMPLE_ACCOUNT_INFO_FOR_ADMIN);
} MSG_PA_ADMIN_GET_ACCOUNT_LIST_OK;


typedef MSG_IP_ADMIN_PETITION_SET_PERIOD		MSG_PA_ADMIN_PETITION_SET_PERIOD;	// 2007-11-19 by cmkwon, �����ý��� ������Ʈ - 

struct MSG_PA_ADMIN_SET_DBSERVER_GROUP		// 2008-04-29 by cmkwon, ������ ���� DB�� �߰�(�ű� ���� ĳ���� ���� ���� �ý����߰�) - 
{
	char		ServerGroupName[SIZE_MAX_SERVER_NAME];
	int			LimitUserCount;
	BOOL		LockCreateCharacterForNewAccount;
};

typedef MSG_PA_ADMIN_SET_DBSERVER_GROUP		MSG_PA_ADMIN_SET_DBSERVER_GROUP_OK;		// 2008-04-29 by cmkwon, ������ ���� DB�� �߰�(�ű� ���� ĳ���� ���� ���� �ý����߰�) - 

struct MSG_PA_ADMIN_RELOAD_INFLUENCERATE	// 2009-09-16 by cmkwon, ���� �ʱ�ȭ�� ���¡ ���� ���� - 
{
	char		ServerGroupName[SIZE_MAX_SERVER_NAME];
};

//////////////////////////////////////////////////////////////////////////
// IMServer <-> admin tool 
#define T1_IA_ADMIN_CONNECT				0x00
#define T1_IA_ADMIN_CONNECT_OK			0x01
#define T1_IA_ADMIN_CHANGE_SERVER_STATE	0x02
#define T1_IA_ADMIN_GET_CHARACTER		0x03
#define T1_IA_ADMIN_GET_CHARACTER_OK	0x04
#define T1_IA_ADMIN_CHAT_ALL			0x05
#define T1_IA_ADMIN_GET_SERVER_INFO		0x06
#define T1_IA_ADMIN_GET_SERVER_INFO_OK	0x07

#define T_IA_ADMIN_CONNECT				(MessageType_t)((T0_IA_ADMIN<<8)|T1_IA_ADMIN_CONNECT)				// A->I
#define T_IA_ADMIN_CONNECT_OK			(MessageType_t)((T0_IA_ADMIN<<8)|T1_IA_ADMIN_CONNECT_OK)			// I->A
#define T_IA_ADMIN_CHANGE_SERVER_STATE	(MessageType_t)((T0_IA_ADMIN<<8)|T1_IA_ADMIN_CHANGE_SERVER_STATE)	// I->A
#define T_IA_ADMIN_GET_CHARACTER		(MessageType_t)((T0_IA_ADMIN<<8)|T1_IA_ADMIN_GET_CHARACTER)			// A->I
#define T_IA_ADMIN_GET_CHARACTER_OK		(MessageType_t)((T0_IA_ADMIN<<8)|T1_IA_ADMIN_GET_CHARACTER_OK)		// I->A
#define T_IA_ADMIN_CHAT_ALL				(MessageType_t)((T0_IA_ADMIN<<8)|T1_IA_ADMIN_CHAT_ALL)				// A->I
#define T_IA_ADMIN_GET_SERVER_INFO		(MessageType_t)((T0_IA_ADMIN<<8)|T1_IA_ADMIN_GET_SERVER_INFO)		// A->I, No Body
#define T_IA_ADMIN_GET_SERVER_INFO_OK	(MessageType_t)((T0_IA_ADMIN<<8)|T1_IA_ADMIN_GET_SERVER_INFO_OK)	// I->A

typedef struct
{
	char	UID[SIZE_MAX_ACCOUNT_NAME];
	char	PWD[SIZE_MAX_PASSWORD];
} MSG_IA_ADMIN_CONNECT;

typedef struct
{
	// 2006-04-15 by cmkwon, �ʵ� ����
	//	BYTE	AuthOK;				// 0: FALSE, 1:TRUE
	USHORT	AccountType0;		// ���� ����
} MSG_IA_ADMIN_CONNECT_OK;

typedef MSG_PA_ADMIN_CHANGE_SERVER_STATE	MSG_IA_ADMIN_CHANGE_SERVER_STATE;

typedef struct
{
	char	CharacterName[SIZE_MAX_CHARACTER_NAME];
} MSG_IA_ADMIN_GET_CHARACTER;

typedef struct
{
	BYTE	IsOnline;			// 0: FALSE, 1:TRUE
} MSG_IA_ADMIN_GET_CHARACTER_OK;

typedef MSG_IC_CHAT_ALL				MSG_IA_ADMIN_CHAT_ALL;

typedef struct
{
	INT			UserCount;
	BYTE		ServerState;	// SERVER_STATE_XXX
} MSG_IA_ADMIN_GET_SERVER_INFO_OK;

//////////////////////////////////////////////////////////////////////////
// FieldServer <-> admin tool 
#define T1_FA_ADMIN_CONNECT				0x00
#define T1_FA_ADMIN_CONNECT_OK			0x01
#define T1_FA_ADMIN_CHANGE_SERVER_STATE	0x02

#define T_FA_ADMIN_CONNECT				(MessageType_t)((T0_FA_ADMIN<<8)|T1_FA_ADMIN_CONNECT)			// A->F
#define T_FA_ADMIN_CONNECT_OK			(MessageType_t)((T0_FA_ADMIN<<8)|T1_FA_ADMIN_CONNECT_OK)		// F->A
#define T_FA_ADMIN_CHANGE_SERVER_STATE	(MessageType_t)((T0_FA_ADMIN<<8)|T1_FA_ADMIN_CHANGE_SERVER_STATE)	// F->A

typedef struct
{
	char	UID[SIZE_MAX_ACCOUNT_NAME];
	char	PWD[SIZE_MAX_PASSWORD];
} MSG_FA_ADMIN_CONNECT;

typedef struct
{
	// 2006-04-15 by cmkwon, �ʵ� ����
	//	BYTE	AuthOK;				// 0: FALSE, 1:TRUE
	USHORT	AccountType0;		// ���� ����
} MSG_FA_ADMIN_CONNECT_OK;

typedef MSG_PA_ADMIN_CHANGE_SERVER_STATE	MSG_FA_ADMIN_CHANGE_SERVER_STATE;

// IMServer -> Client
typedef MSG_FC_COUNTDOWN_START				MSG_IC_COUNTDOWN_START;

// Client -> IMServer
typedef MSG_FC_COUNTDOWN_DONE				MSG_IC_COUNTDOWN_DONE;

struct MSG_IC_VOIP_SET
{// 2008-06-17 by dhjin, EP3 VOIP - ����
	EN_CHECK_TYPE	VoipType;
};

struct MSG_IC_VOIP_SET_OK
{// 2008-06-17 by dhjin, EP3 VOIP - ����
	UID32_t	CharacterUID;
	EN_CHECK_TYPE	VoipType;
};

//////////////////////////////////////////////////////////////////////////
// 2008-06-16 by dhjin, EP3 ä�ù� -
struct MSG_IC_CHATROOM_CREATE
{// 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� ����
	CHAR	ChatRoomName[SIZE_MAX_CHATROOM_NAME];
	BOOL	ChatRoomLock;
	CHAR	ChatRoomPW[SIZE_MAX_TEAM_PW];
	BYTE	ChatRoomMaxCount;
};

struct MSG_IC_CHATROOM_CREATE_OK
{// 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� ����
	INT			ChatRoomNum;
};

struct MSG_IC_CHATROOM_LIST_INFO
{// 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� ����Ʈ 
	INT			StartNum;
};

struct SCHATROOM_LIST_INFO
{// 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� ����Ʈ  OK
	INT			ChatRoomNum;
	CHAR		ChatRoomName[SIZE_MAX_CHATROOM_NAME];
	BOOL		ChatRoomLock;
	CHAR		ChatRoomMasterName[SIZE_MAX_CHARACTER_NAME];
	BYTE		Membercount;
	BYTE		MaxMembercount;
};

struct MSG_IC_CHATROOM_LIST_INFO_OK
{// 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� ����Ʈ  OK
	INT			ChatRoomInfoTotalCount;	// 2008-06-17 by dhjin, ä�ù� �ִ� ���
	INT			ChatRoomInfoListCount;		// 2008-06-17 by dhjin,
	_ARRAY(SCHATROOM_LIST_INFO);
};

struct MSG_IC_CHATROOM_REQUEST_INVITE
{// 2008-06-17 by dhjin, EP3 ä�ù� - ä�ù� �ʴ� 
	INT		ChatRoomNum;
	char	InviteeCharacterName[SIZE_MAX_CHARACTER_NAME];		// �ʴ��� ���� ���̵�
};

struct MSG_IC_CHATROOM_REQUEST_INVITE_QUESTION
{// 2008-06-17 by dhjin, EP3 ä�ù� - ä�ù� �ʴ��ڿ��� ���� ����
	INT		ChatRoomNum;
	char	ChatRoomMasterName[SIZE_MAX_CHARACTER_NAME];
};

struct MSG_IC_CHATROOM_ACCEPT_INVITE
{// 2008-06-17 by dhjin, EP3 ä�ù� - ä�ù� �ʴ� �¶�
	INT		ChatRoomNum;
};

struct MSG_IC_CHATROOM_ACCEPT_INVITE_OK
{// 2008-06-17 by dhjin, EP3 ä�ù� - ä�ù� �ʴ� �¶� ���� ���� ����
	UID32_t	CharacterUID;
	char	CharacterName[SIZE_MAX_CHARACTER_NAME];
	BYTE	CharacterLevel;		// 2014-01-27 by jhseol, ä�ù� lv ���� �߰�
};

struct MSG_IC_CHATROOM_JOIN
{// 2008-06-18 by dhjin, EP3 ä�ù� - ä�ù� ���� ����
	INT		ChatRoomNum;
	BOOL    ChatRoomLock;
	char	ChatRoomPW[SIZE_MAX_TEAM_PW];
};

struct MSG_IC_CHATROOM_REJECT_INVITE
{// 2008-06-18 by dhjin, EP3 ä�ù� - ä�ù� �ʴ� ���
	INT		ChatRoomNum;
};

struct MSG_IC_CHATROOM_LEAVE
{// 2008-06-18 by dhjin, EP3 ä�ù� - ä�ù� ������
	INT		ChatRoomNum;
	char	LeaveCharacterName[SIZE_MAX_CHARACTER_NAME];
};

struct MSG_IC_CHATROOM_LEAVE_OK
{// 2008-06-18 by dhjin, EP3 ä�ù� - ä�ù� ������
	UID32_t	CharacterUID;
	char	LeaveCharacterName[SIZE_MAX_CHARACTER_NAME];
};

struct MSG_IC_CHATROOM_BAN
{// 2008-06-18 by dhjin, EP3 ä�ù� - ä�ù� �߹� 
	INT		ChatRoomNum;
	UID32_t	BanCharacterUID;
	char	BanCharacterName[SIZE_MAX_CHARACTER_NAME];
};

struct MSG_IC_CHATROOM_BAN_OK
{// 2008-06-18 by dhjin, EP3 ä�ù� - ä�ù� �߹� 
	UID32_t	BanCharacterUID;
	char	BanCharacterName[SIZE_MAX_CHARACTER_NAME];
};

struct MSG_IC_CHATROOM_CHANGE_NAME
{// 2008-06-18 by dhjin, EP3 ä�ù� - ä�ù� �̸� ���� 
	INT		ChatRoomNum;
	char	ChatRoomName[SIZE_MAX_CHATROOM_NAME];
};

struct MSG_IC_CHATROOM_CHANGE_NAME_OK
{// 2008-06-18 by dhjin, EP3 ä�ù� - ä�ù� �̸� ���� 
	char	ChatRoomName[SIZE_MAX_CHATROOM_NAME];
};

struct MSG_IC_CHATROOM_CHANGE_MASTER
{// 2008-06-18 by dhjin, EP3 ä�ù� - ä�ù� ���� ����
	INT		ChatRoomNum;
	UID32_t	NewCharacterUID;
};

struct MSG_IC_CHATROOM_CHANGE_MASTER_OK
{// 2008-06-18 by dhjin, EP3 ä�ù� - ä�ù� ���� ����
	UID32_t	NewCharacterUID;
	char	CharacterName[SIZE_MAX_CHARACTER_NAME];
};

struct MSG_IC_CHATROOM_CHANGE_LOCK_PW
{// 2008-06-18 by dhjin, EP3 ä�ù� - ä�ù� ��� ���� 
	INT		ChatRoomNum;
	BOOL    ChatRoomLock;
	char	ChatRoomPW[SIZE_MAX_TEAM_PW];
};

struct MSG_IC_CHATROOM_CHANGE_LOCK_PW_OK
{// 2008-06-18 by dhjin, EP3 ä�ù� - ä�ù� ��� ����
	BOOL    ChatRoomLock;
};

struct MSG_IC_CHATROOM_CHANGE_MAX_MEMBER
{// 2008-06-18 by dhjin, EP3 ä�ù� - ä�ù� �ִ� �ο��� ����
	INT		ChatRoomNum;
	BYTE	ChatRoomMaxMember;
};

struct MSG_IC_CHATROOM_CHANGE_MAX_MEMBER_OK
{// 2008-06-18 by dhjin, EP3 ä�ù� - ä�ù� �ִ� �ο��� ����
	BYTE	ChatRoomMaxMember;
};

struct MSG_IC_CHATROOM_MEMBER_INFO
{// 2008-06-25 by dhjin, EP3 ä�ù� - ä�ù� �ɹ� ����
	INT		ChatRoomNum;
};

struct SCHATROOM_MEMBER_INFO
{/// 2008-06-25 by dhjin, EP3 ä�ù� - ä�ù� �ɹ� ����
	UID32_t		CharacterUID;
	char		CharacterName[SIZE_MAX_CHARACTER_NAME];
	BYTE		CharacterLevel;		// 2014-01-27 by jhseol, ä�ù� lv ���� �߰�
};

struct MSG_IC_CHATROOM_MEMBER_INFO_OK
{/// 2008-06-25 by dhjin, EP3 ä�ù� - ä�ù� �ɹ� ����
	INT			ChatRoomNum;
	INT			ChatRoomInfoListCount;
	UID32_t		MasterCharacterUID;
	char		ChatRoomName[SIZE_MAX_CHATROOM_NAME];
	BOOL		ChatRoomLock;
	char		ChatRoomPW[SIZE_MAX_TEAM_PW];
	INT			ChatRoomMaxCount;
	_ARRAY(SCHATROOM_MEMBER_INFO);
};


///////////////////////////////////////////////////////////////////////////////
// T0_FC_RACING
typedef struct
{
	BYTE		byRacingListCounts;
	ARRAY_(MAP_CHANNEL_INDEX);
} MSG_FC_RACING_RACINGLIST_REQUEST_ACK;

typedef struct
{
	MAP_CHANNEL_INDEX	mapChannIdx;
} MSG_FC_RACING_RACINGINFO_REQUEST;

typedef struct
{
	MAP_CHANNEL_INDEX	mapChannelIndex;
	BYTE				byMaxUserCounts;				// �ִ� �����ڼ�
	BYTE				byMinUserCounts;				// �ּ� �����ڼ�
	BYTE				byRacingGameNumber;				// ����Ǵ� ���� �ѹ�
	int					nEntryFee;						// ������(����:spi)
	int					nLimitTimeForRacing;			// Racing�� ����Ǵ� ���ѽð�(����:��)
	int					nRamainTimeForJoinRacing;		// ���� ���� �ð����� ���� �ð�(����:��)	
} MSG_FC_RACING_RACINGINFO_REQUEST_ACK;

typedef struct
{
	MAP_CHANNEL_INDEX	mapChannIdx;
	DWORD				dwRamainTimeForJoinRacing;		// ���� ���� �ð����� ���� �ð�(����:��)
} MSG_FC_RACING_RACINGNOTIFY;

typedef struct
{
	MAP_CHANNEL_INDEX	mapChannIdx;
} MSG_FC_RACING_JOIN_ENABLE;

typedef struct
{
	MAP_CHANNEL_INDEX	mapChannIdx;
} MSG_FC_RACING_JOIN_REQUEST;

typedef struct
{
	BYTE				byJoinedFlag : 1;					// 1 bit ���, ���̽̿� ���� �Ǿ������� �÷���
	BYTE				byJoinedOrder : 7;				// 7 bit ���, ���̽̿� ������ ����(ex, 8���̸� 1���� 8����)
	MAP_CHANNEL_INDEX	mapChannIdx;
} MSG_FC_RACING_JOIN_REQUEST_ACK;

typedef struct
{
	BYTE				byCountDowns;
} MSG_FC_RACING_COUNTDOWN;

typedef struct
{
	BYTE				byCheckPointIndex;
	DWORD				dwObjectType;
	AVECTOR3			PositionAVector3;
} MSG_FC_RACING_CHECKPOINT_CHECK;

typedef struct
{
	BYTE				byCheckedFlag : 1;
	BYTE				byCheckPointIndex : 7;
	BYTE				byRanking;
} MSG_FC_RACING_CHECKPOINT_CHECK_ACK;

typedef struct
{
	BYTE				byRanking;
} MSG_FC_RACING_FINISHED;

typedef struct
{
	char				szCharacterName[SIZE_MAX_CHARACTER_NAME];
	BYTE				byRanking;
} MSG_FC_RACING_OTHER_FINISHED;

typedef struct
{
	char				szCharacterName[SIZE_MAX_CHARACTER_NAME];
	BYTE				byRanking;
	DWORD				dwElapsedTime;
} RankingInfo;

typedef struct
{
	BYTE				byRankingInfoCounts;		// Ranking ���� ī��Ʈ
	ARRAY_(RankingInfo);
} MSG_FC_RACING_FINALRANKING;

//////////////////////////////////////////////////////////////////////////
// 2007-04-17 by dhjin
// T0_FC_ARENA
#define T_FC_ARENA_PLAY_CHARACTER_TYPE		(MessageType_t)((T0_FC_ARENA<<8)|T1_FC_ARENA_PLAY_CHARACTER_TYPE)			// c->f(a)	// 2012-06-08 by jhseol, �Ʒ��� �߰�����part2 - �ɸ��� : Ÿ�� ����
#define T_FC_ARENA_REQUEST_TEAM				(MessageType_t)((T0_FC_ARENA<<8)|T1_FC_ARENA_REQUEST_TEAM)					// C->F
#define T_FC_ARENA_REQUEST_TEAM_OK			(MessageType_t)((T0_FC_ARENA<<8)|T1_FC_ARENA_REQUEST_TEAM_OK)				// F->C
#define T_FC_ARENA_CREATE_TEAM				(MessageType_t)((T0_FC_ARENA<<8)|T1_FC_ARENA_CREATE_TEAM)					// C->F
#define T_FC_ARENA_CREATE_TEAM_OK			(MessageType_t)((T0_FC_ARENA<<8)|T1_FC_ARENA_CREATE_TEAM_OK)				// F->C
#define T_FC_ARENA_ENTER_TEAM				(MessageType_t)((T0_FC_ARENA<<8)|T1_FC_ARENA_ENTER_TEAM)					// C->F
#define T_FC_ARENA_ENTER_TEAM_OK			(MessageType_t)((T0_FC_ARENA<<8)|T1_FC_ARENA_ENTER_TEAM_OK)					// F->C
#define T_FC_ARENA_TEAM_MEMBER_LIST			(MessageType_t)((T0_FC_ARENA<<8)|T1_FC_ARENA_TEAM_MEMBER_LIST)				// F->C(n)
#define T_FC_ARENA_REAVE_TEAM				(MessageType_t)((T0_FC_ARENA<<8)|T1_FC_ARENA_REAVE_TEAM)					// C->F
#define T_FC_ARENA_REAVE_TEAM_OK			(MessageType_t)((T0_FC_ARENA<<8)|T1_FC_ARENA_REAVE_TEAM_OK)					// F->C
#define T_FC_ARENA_TEAM_READY				(MessageType_t)((T0_FC_ARENA<<8)|T1_FC_ARENA_TEAM_READY)					// F->C(n)
#define T_FC_ARENA_TEAM_READY_FINISH		(MessageType_t)((T0_FC_ARENA<<8)|T1_FC_ARENA_TEAM_READY_FINISH)				// C->F
#define T_FC_ARENA_TEAM_READY_FINISH_CANCEL	(MessageType_t)((T0_FC_ARENA<<8)|T1_FC_ARENA_TEAM_READY_FINISH_CANCEL)		// C->F
#define T_FC_ARENA_TEAM_MATCHING			(MessageType_t)((T0_FC_ARENA<<8)|T1_FC_ARENA_TEAM_MATCHING)					// F->C(n)
#define T_FC_ARENA_ENTER_ROOM				(MessageType_t)((T0_FC_ARENA<<8)|T1_FC_ARENA_ENTER_ROOM)					// F->C(n)
#define T_FC_ARENA_ENTER_ROOM_WARP			(MessageType_t)((T0_FC_ARENA<<8)|T1_FC_ARENA_ENTER_ROOM_WARP)				// C->F
#define T_FC_ARENA_ROOM_WAR_START			(MessageType_t)((T0_FC_ARENA<<8)|T1_FC_ARENA_ROOM_WAR_START)				// F->C(n)
#define T_FC_ARENA_ROOM_WAR_INFO			(MessageType_t)((T0_FC_ARENA<<8)|T1_FC_ARENA_ROOM_WAR_INFO)					// F->C(n)	
#define T_FC_ARENA_ROOM_WAR_FINISH_HEADER	(MessageType_t)((T0_FC_ARENA<<8)|T1_FC_ARENA_ROOM_WAR_FINISH_HEADER)		// F->C(n)
#define T_FC_ARENA_ROOM_WAR_FINISH			(MessageType_t)((T0_FC_ARENA<<8)|T1_FC_ARENA_ROOM_WAR_FINISH)				// F->C(n)
#define T_FC_ARENA_ROOM_WAR_FINISH_DONE		(MessageType_t)((T0_FC_ARENA<<8)|T1_FC_ARENA_ROOM_WAR_FINISH_DONE)			// F->C(n)
#define T_FC_ARENA_ROOM_WAR_FINISH_DRAW		(MessageType_t)((T0_FC_ARENA<<8)|T1_FC_ARENA_ROOM_WAR_FINISH_DRAW)				// F->C(n)
#define T_FC_ARENA_FINISH_WARP				(MessageType_t)((T0_FC_ARENA<<8)|T1_FC_ARENA_FINISH_WARP)					// C->F
#define T_FC_ARENA_FINISH_WARP_OK			(MessageType_t)((T0_FC_ARENA<<8)|T1_FC_ARENA_FINISH_WARP_OK)				// F->C(n)
#define T_FC_ARENA_REQUEST_CREATE_TEAMINFO  (MessageType_t)((T0_FC_ARENA<<8)|T1_FC_ARENA_REQUEST_CREATE_TEAMINFO)		// C->F
#define T_FC_ARENA_REQUEST_CREATE_TEAMINFO_OK  (MessageType_t)((T0_FC_ARENA<<8)|T1_FC_ARENA_REQUEST_CREATE_TEAMINFO_OK)	// F->C
#define T_FC_ARENA_BEFORE_ROOM_WAR_FINISH	(MessageType_t)((T0_FC_ARENA<<8)|T1_FC_ARENA_BEFORE_ROOM_WAR_FINISH)		// F->C
#define T_FC_ARENA_REQUEST_OTHER_TEAM_INFO  (MessageType_t)((T0_FC_ARENA<<8)|T1_FC_ARENA_REQUEST_OTHER_TEAM_INFO)	// C->F
#define T_FC_ARENA_REQUEST_OTHER_TEAM_INFO_OK	(MessageType_t)((T0_FC_ARENA<<8)|T1_FC_ARENA_REQUEST_OTHER_TEAM_INFO_OK)	// F->C
#define T_FC_ARENA_GM_COMMAND_INFO_HEADER	(MessageType_t)((T0_FC_ARENA<<8)|T1_FC_ARENA_GM_COMMAND_INFO_HEADER)	// F->C
#define T_FC_ARENA_GM_COMMAND_INFO			(MessageType_t)((T0_FC_ARENA<<8)|T1_FC_ARENA_GM_COMMAND_INFO)	// F->C
#define T_FC_ARENA_GM_COMMAND_INFO_DONE		(MessageType_t)((T0_FC_ARENA<<8)|T1_FC_ARENA_GM_COMMAND_INFO_DONE)	// F->C
#define T_FC_ARENA_QUICK_ENTER_TEAM			(MessageType_t)((T0_FC_ARENA<<8)|T1_FC_ARENA_QUICK_ENTER_TEAM)	// C->F
#define T_FC_ARENA_WATCH_READY				(MessageType_t)((T0_FC_ARENA<<8)|T1_FC_ARENA_WATCH_READY)		// F->C
#define T_FC_ARENA_WATCH_START				(MessageType_t)((T0_FC_ARENA<<8)|T1_FC_ARENA_WATCH_START)		// F->C
#define T_FC_ARENA_WATCH_END				(MessageType_t)((T0_FC_ARENA<<8)|T1_FC_ARENA_WATCH_END)			// F->C
#define T_FC_ARENA_WATCH_REMOVE_USER		(MessageType_t)((T0_FC_ARENA<<8)|T1_FC_ARENA_WATCH_REMOVE_USER)			// F->C
// 2008-01-08 by dhjin, �Ʒ��� ���� - 
#define T_FC_ARENA_POSSIBLE_GAMESTART		(MessageType_t)((T0_FC_ARENA<<8)|T1_FC_ARENA_POSSIBLE_GAMESTART)			// F->C
#define T_FC_ARENA_CHARACTER_GAMESTART		(MessageType_t)((T0_FC_ARENA<<8)|T1_FC_ARENA_CHARACTER_GAMESTART)			// C->F
#define T_FC_ARENA_USE_CITYWARPITEM			(MessageType_t)((T0_FC_ARENA<<8)|T1_FC_ARENA_USE_CITYWARPITEM)				// F->C



struct MSG_FC_ARENA_REQUEST_TEAM
{
	BYTE				ArenaMode;			// 2007-04-17 by dhjin, �Ʒ��� ���   1 : DeathMatch, 2 : Round, so on..
	BYTE				RequestTeamState;	// 2007-06-05 by dhjin, �� ���� ��û �÷��� 1 : ��� ����, 2 : �����. 3 : ����� ����
	ClientIndex_t		ClientIndex;		// 2007-04-17 by dhjin, ��û�� Ŭ���̾�Ʈ
	INT					StartTeamNum;		// 2007-04-27 by dhjin, �� ���� ��û�Ͽ� �����ִ� �� ���� ��ȣ ex)11 => 11��° ����� ARENA_MAX_REQUEST_TEAM���� ����
	MapIndex_t			ArenaMap;			// 2012-04-12 by jhseol, �Ʒ��� �߰����� - ������ �Ʒ��� ��
};

struct SARENA_TEAM_INFO
{
	BOOL			TeamLock;				// 2007-04-17 by dhjin, �� ���� ����  0 : ����, 1: ����� 
	BOOL			TeamEvent;				// 2008-03-10 by dhjin, �Ʒ��� ���� - �̺�Ʈ������ 0: �Ϲ��� 1: �̺�Ʈ��
	BYTE			TeamSize;				// 2007-04-17 by dhjin, �� �ο� ���� 
	BYTE			CurrentTeamSize;		// 2007-04-25 by dhjin, ���� �� �ο�
	BYTE			ArenaMode;				// 2007-04-17 by dhjin, �Ʒ��� ���   1 : DeathMatch, 2 : Round, so on..
	BYTE			ArenaState;				// 2007-06-05 by dhjin, ���� �Ʒ��� ����
	BYTE			TeamStartLevel;			// 2007-06-05 by dhjin, ���� ���� ����
	BYTE			TeamEndLevel;			// 2007-06-05 by dhjin, ���� �� ����
	INT				TeamNum;				// 2007-04-17 by dhjin, �� ��ȣ
	CHAR			CharacterName[SIZE_MAX_CHARACTER_NAME];		// 2007-04-17 by dhjin, ���� �̸�
	MapIndex_t		ArenaMap;				// 2012-04-12 by jhseol, �Ʒ��� �߰����� - ������ �Ʒ��� ��
};

struct MSG_FC_ARENA_REQUEST_TEAM_OK
{
	INT				ArenaTeamInfoTotalCount;	// 2007-04-27 by dhjin, �� �ִ� ���
	INT				ArenaTeamInfoListCount;		// 2007-04-19 by dhjin,
	BYTE			RequetTeamState;			// 2007-06-07 by dhjin, �� ���� ��û �÷��� 1 : ��� ����, 2 : �����. 3 : ����� ���� 
	MapIndex_t		ArenaMap;					// 2012-04-12 by jhseol, �Ʒ��� �߰����� - ������ �Ʒ��� ��
	_ARRAY(SARENA_TEAM_INFO);
};

struct MSG_FC_ARENA_CREATE_TEAM
{
	BOOL			TeamLock;				// 2007-04-17 by dhjin, �� ���� ���� 0 : ����, 1: �����
	BYTE			ArenaMode;				// 2007-04-17 by dhjin, �Ʒ��� ���   1 : DeathMatch, 2 : Round, so on..
	BYTE			TeamSize;				// 2007-04-17 by dhjin, �� �ο� ���� 
	ClientIndex_t	ClientIndex;			// 2007-04-17 by dhjin, ��û�� Ŭ���̾�Ʈ
	CHAR			TeamPW[SIZE_MAX_TEAM_PW];	// 2007-04-17 by dhjin, �� ��� ��ȣ
	MapIndex_t		ArenaMap;				// 2012-04-12 by jhseol, �Ʒ��� �߰����� - ������ �Ʒ��� ��
};

struct MSG_FC_ARENA_CREATE_TEAM_OK
{
	BYTE			ArenaMode;				// 2007-04-17 by dhjin, �Ʒ��� ���   1 : DeathMatch, 2 : Round, so on..
	BYTE			TeamSize;				// 2007-04-17 by dhjin, �� �ο� ���� 
	INT				TeamNum;				// 2007-04-17 by dhjin, ������ �� ��ȣ
	MapIndex_t		ArenaMap;				// 2012-04-12 by jhseol, �Ʒ��� �߰����� - ������ �Ʒ��� ��
};

struct MSG_FC_ARENA_ENTER_TEAM
{
	BYTE			ArenaMode;				// 2007-04-17 by dhjin, �Ʒ��� ���   1 : DeathMatch, 2 : Round, so on..
	ClientIndex_t	ClientIndex;			// 2007-04-17 by dhjin, ��û�� Ŭ���̾�Ʈ
	CHAR			TeamPW[SIZE_MAX_TEAM_PW];	// 2007-04-17 by dhjin, �� ��� ��ȣ
	INT				TeamNum;				// 2007-04-17 by dhjin, �����Ϸ��� �� ��ȣ	
};

struct MSG_FC_ARENA_ENTER_TEAM_OK
{
	BYTE			ArenaMode;				// 2007-04-17 by dhjin, �Ʒ��� ���   1 : DeathMatch, 2 : Round, so on..
	BYTE			TeamSize;				// 2007-04-17 by dhjin, �� �ο� ���� 
	INT				TeamNum;				// 2007-04-17 by dhjin, ������ �� ��ȣ
};

struct SARENA_TEAM_CHARACTERINFO
{
	BYTE			ArenaState;				// 2007-04-17 by dhjin, ���� �Ʒ��� ����
	ClientIndex_t	ClientIndex;
	CHAR			CharacterName[SIZE_MAX_CHARACTER_NAME];	// 2007-04-17 by dhjin, �������� �̸�
	INT				PlayCharacterType;		// 2012-06-08 by jhseol, �Ʒ��� �߰�����part2 - �ɸ��� : Ÿ�� ����
};

struct MSG_FC_ARENA_TEAM_MEMBER_LIST
{
	BYTE			ArenaTeamState;						// 2007-05-07 by dhjin, �Ʒ��� �� ����
	BYTE			ArenaTeamCharacterNameListCount;	// 2007-04-19 by dhjin
	_ARRAY(SARENA_TEAM_CHARACTERINFO);
};

struct MSG_FC_ARENA_PLAY_CHARACTER_TYPE
{
	INT				PlayCharacterType;		// 2012-06-08 by jhseol, �Ʒ��� �߰�����part2 - �ɸ��� : Ÿ�� ����
};

struct MSG_FC_ARENA_REAVE_TEAM
{
	BYTE			ArenaMode;				// 2007-04-17 by dhjin, �Ʒ��� ���   1 : DeathMatch, 2 : Round, so on..
	ClientIndex_t	ClientIndex;			// 2007-04-17 by dhjin, ��û�� Ŭ���̾�Ʈ
	INT				TeamNum;				// 2007-04-17 by dhjin, Ż���Ϸ��� �� ��ȣ
};

struct MSG_FC_ARENA_TEAM_READY
{
	BYTE			ArenaMode;
	BYTE			ArenaState;				// 2007-04-17 by dhjin, ���� �Ʒ��� ����, 2 : ARENA_STATE_READY
	INT				TeamNum;				// 2007-04-17 by dhjin, �� ��ȣ
};

struct MSG_FC_ARENA_ENTER_ROOM
{
	BYTE			ArenaMode;
	BYTE			ArenaState;				// 2007-04-17 by dhjin, ���� �Ʒ��� ����, 3 : ARENA_STATE_WARREADY
	BYTE			VCNDeathCount;			// 2007-04-17 by dhjin, ���������� ������ġ ����Ʈ
	BYTE			ANIDeathCount;			// 2007-04-17 by dhjin, �˸��� ������ġ ����Ʈ
	BYTE			PlayLimitedTime;		// 2007-05-04 by dhjin, ��� ���� �ð�
	INT				TeamNum;				// 2007-04-17 by dhjin, �� ��ȣ
	ATUM_DATE_TIME	StartRoomTime;			// 2007-04-17 by dhjin, �� ���� �ð�
	ATUM_DATE_TIME	ArenaServerTime;		// 2009-09-10 by jwlee, �Ʒ��� ���� �ð� ���� ���� ���� - 
};

struct MSG_FC_ARENA_ENTER_ROOM_WARP
{// 2008-02-21 by dhjin, �Ʒ��� ���� - 
	BOOL			CheckCommand;			// 2008-02-21 by dhjin, '/�Ʒ����̵�' ���ɾ� ������� üũ
};

struct MSG_FC_ARENA_ROOM_WAR_START
{
	BYTE			ArenaMode;
	BYTE			ArenaState;				// 2007-04-17 by dhjin, ���� �Ʒ��� ����, 4 : ARENA_STATE_WARING
	ATUM_DATE_TIME	Time;					// 2007-04-17 by dhjin, ���� ���� �ð�
};

struct MSG_FC_ARENA_ROOM_WAR_INFO
{
	BYTE			ArenaMode;
	BYTE			VCNDeathCount;			// 2007-04-17 by dhjin, ���������� ������ġ ����Ʈ
	BYTE			ANIDeathCount;			// 2007-04-17 by dhjin, �˸��� ������ġ ����Ʈ
	//	ATUM_DATE_TIME	Time;					// 2007-04-17 by dhjin, ���� ���� �ð�
};

struct MSG_FC_ARENA_ROOM_WAR_FINISH
{
	BYTE			Influence;				// 2007-04-17 by dhjin, ���� 
	BYTE 			ShootingDown;			// 2007-04-17 by dhjin, ���߼� 
	BYTE 			SufferingAttack;		// 2007-04-17 by dhjin, �ǰݼ� 
	BYTE			LostPoint;				// 2007-06-01 by dhjin, LostPoint
	USHORT			UnitKind;				// 2007-04-17 by dhjin, ��� ���� 
	CHAR			CharacterLevelRank[SIZE_MAX_LEVELRANK];	// 2007-04-17 by dhjin, ���� ���� ���
	CHAR			CharacterName[SIZE_MAX_CHARACTER_NAME];	// 2007-04-17 by dhjin, ���� �̸�
	FLOAT			Average;				// 2012-06-08 by jhseol, �Ʒ��� �߰�����part2 - HP/DP ����
	INT				TeamAverage;			// 2012-06-08 by jhseol, �Ʒ��� �߰�����part2 - HP/DP ����
};

struct MSG_FC_ARENA_ROOM_WAR_FINISH_HEADER
{
	BYTE			ArenaMode;
	BYTE			ArenaState;				// 2007-04-17 by dhjin, ���� �Ʒ��� ����, 5 : ARENA_STATE_WARFINISH
	ATUM_DATE_TIME	FinishTime;				// 2007-04-17 by dhjin, ���� ���� �ð�
};

struct MSG_FC_ARENA_ROOM_WAR_FINISH_DONE
{
	BYTE			Issue;					// 2007-04-20 by dhjin, �Ʒ��� ���� ����, 1 : ARENA_ISSUE_WIN, 2 : ARENA_ISSUE_LOSE, 3 : ARENA_ISSUE_DRAW
	BYTE			EndState;				// 2007-05-16 by dhjin, �Ʒ��� ���� Ÿ��, 1 : ARENA_END_TYPE_POINT, 2 : ARENA_END_TYPE_TIME, 3 : ARENA_END_TYPE_GIVEUP
	INT				InflPoint;				// 2007-04-17 by dhjin, ���� ����Ʈ ����
	INT				WarPoint;				// 2007-04-17 by dhjin, WarPoint ����
	INT				TotalWarPoint;			// 2007-05-28 by dhjin, WP
	INT				CumulativeWarPoint;		// 2007-05-28 by dhjin, CumulativeWP
	INT				ArenaWin;				// 2007-06-07 by dhjin, �Ʒ��� ���� ���� ��
	INT				ArenaLose;				// 2007-06-07 by dhjin, �Ʒ��� ���� ���� ��
};

struct MSG_FC_ARENA_ROOM_WAR_FINISH_DRAW
{
	BYTE			ArenaMode;
	BYTE			ArenaState;				// 2007-04-17 by dhjin, ���� �Ʒ��� ����, 5 : ARENA_STATE_WARFINISH
	BYTE			Issue;					// 2007-04-20 by dhjin, �Ʒ��� ���� ����, 1 : ARENA_ISSUE_WIN, 2 : ARENA_ISSUE_LOSE, 3 : ARENA_ISSUE_DRAW
	BYTE			EndState;				// 2007-05-16 by dhjin, �Ʒ��� ���� Ÿ��, 1 : ARENA_END_TYPE_POINT, 2 : ARENA_END_TYPE_TIME, 3 : ARENA_END_TYPE_GIVEUP
	INT				InflPoint;				// 2007-04-17 by dhjin, ���� ����Ʈ ����
	INT				WarPoint;				// 2007-04-17 by dhjin, WarPoint ����
	ATUM_DATE_TIME	FinishTime;				// 2007-04-17 by dhjin, ���� ���� �ð�
};

//struct SARENA_ROOM_FINISH_INFO
//{
//	BYTE			Influence;				// 2007-04-17 by dhjin, ���� 
//// 	BYTE			Rank;					// 2007-04-17 by dhjin, ���߼��� ���� ��ŷ
//	BYTE 			ShootingDown;			// 2007-04-17 by dhjin, ���߼� 
//	BYTE 			SufferingAttack;		// 2007-04-17 by dhjin, �ǰݼ� 
//	USHORT			UnitKind;				// 2007-04-17 by dhjin, ��� ���� 
//	CHAR			CharacterLevelRank[SIZE_MAX_LEVELRANK];	// 2007-04-17 by dhjin, ���� ���� ���
//	CHAR			CharacterName[SIZE_MAX_CHARACTER_NAME];	// 2007-04-17 by dhjin, ���� �̸�
//};
//
//struct MSG_FC_ARENA_ROOM_WAR_FINISH
//{
//	BYTE			ArenaMode;
//	BYTE			ArenaState;				// 2007-04-17 by dhjin, ���� �Ʒ��� ����, 5 : ARENA_STATE_WARFINISH
//	BYTE			Issue;					// 2007-04-20 by dhjin, �Ʒ��� ���� ����, 1 : ARENA_ISSUE_WIN, 2 : ARENA_ISSUE_LOSE, 3 : ARENA_ISSUE_DRAW
//	INT				InflPoint;				// 2007-04-17 by dhjin, ���� ����Ʈ ����
//	INT				WarPoint;				// 2007-04-17 by dhjin, WarPoint ����
//	ATUM_DATE_TIME	FinishTime;				// 2007-04-17 by dhjin, ���� ���� �ð�
//	BYTE			ArenaRoomFinishInfoDeathMatchListCount; // 2007-04-19 by dhjin
//	_ARRAY(SARENA_ROOM_FINISH_INFO);
//};

struct MSG_FC_ARENA_FINISH_WARP_OK
{
	MAP_CHANNEL_INDEX	MapChannelIndex;	// 2007-04-17 by dhjin, �� ä�� ����
};

struct SARENA_REQUEST_CREATE_TEAMINFO
{
	BYTE 	ArenaMode;				// �Ʒ��� ��� 1 : DeathMatch, 2 : Round
	BYTE 	ReqMemberNum; 			// �� �ο� ����
	MapIndex_t	ArenaMap;			// 2012-04-12 by jhseol, �Ʒ��� �߰����� - ������ �Ʒ��� ��
};

struct MSG_FC_ARENA_REQUEST_CREATE_TEAMINFO_OK
{
	BYTE	ArenaRequetCreateTeamInfoListCount; // 2007-04-26 by dhjin
	_ARRAY(SARENA_REQUEST_CREATE_TEAMINFO);
};

// 2007-05-23 by dhjin, ��� �� ���� ����
struct SARENA_REQUEST_OTHER_TEAM_INFO_OK
{
	BYTE	MemberCount;			// �� �ο���
	INT		TeamCount;				// �� ��
};

struct MSG_FC_ARENA_REQUEST_OTHER_TEAM_INFO_OK
{
	BYTE 	ArenaMode;				// �Ʒ��� ��� 1 : DeathMatch, 2 : Round
	BYTE	ArenaOtherTeamListCount;
	_ARRAY(SARENA_REQUEST_OTHER_TEAM_INFO_OK);
};

// 2007-05-25 by dhjin, GM���ɾ� ����� ���� ����ü
struct SARENA_GM_COMMAND_INFO
{
	BYTE 	ArenaMode;							// �Ʒ��� ��� 1 : DeathMatch, 2 : Round
	BYTE	Level;								// �� ����
	BYTE	MemberCount;						// �� �ο���
	INT		TeamCount;							// �� ��
};
typedef SARENA_GM_COMMAND_INFO			MSG_FC_ARENA_GM_COMMAND_INFO;

struct MSG_FC_ARENA_GM_COMMAND_INFO_DONE
{
	INT	ReadyUserTotalCount;
	INT	MatchIngUserTotalCount;
	INT	ArenaFightIngUserTotalCount;
};

struct MSG_FC_ARENA_WATCH_READY
{
	BYTE			ArenaState;			// 2007-06-18 by dhjin, ���� �Ʒ��� ����
};

struct SARENA_WATCH_START_USER_INFO
{
	SHORT			HP;
	float			CurrentHP;
	SHORT			DP;
	float			CurrentDP;
	BYTE			Influence;
	ClientIndex_t	ClientIndex;
	CHAR			CharacterName[SIZE_MAX_CHARACTER_NAME];		// 2007-06-15 by dhjin, ���� �̸�
};

struct MSG_FC_ARENA_WATCH_START
{
	BYTE			VCNDeathCount;			// 2007-06-18 by dhjin, ���������� ������ġ ����Ʈ
	BYTE			ANIDeathCount;			// 2007-06-18 by dhjin, �˸��� ������ġ ����Ʈ
	INT				Time;					// 2007-06-18 by dhjin, ���� ���� �ð� (��)
	INT				ArenaWatchStartUserInfoListCount;		// 2007-06-15 by dhjin,
	_ARRAY(SARENA_WATCH_START_USER_INFO);
};

struct MSG_FC_ARENA_WATCH_REMOVE_USER
{
	ClientIndex_t	ClientIndex;			// 2007-06-18 by dhjin, �Ʒ������� ���� ����
};

// 2008-01-08 by dhjin, �Ʒ��� ���� - 
struct MSG_FC_ARENA_POSSIBLE_GAMESTART
{// 2008-01-08 by dhjin, �Ʒ��� �ɸ��� ������ �����Ѵ�.
	BitFlag16_t		MapWeather;
	CHARACTER		AFSCharacter;
	char			ServerGroupName0[SIZE_MAX_SERVER_NAME];
	char			MainORTestServerName[SIZE_MAX_SERVER_NAME];
	char			GamePublisher[SIZE_MAX_GAME_PUBLISHER_NAME];
	BOOL			IsPCBangUser;			// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - 
};

struct MSG_FC_CHARACTER_READY_GAMESTART_FROM_ARENA_TO_MAINSERVER_OK
{// 2008-01-15 by dhjin, �Ʒ��� ��� ���� �� �ʵ� ���� ���� �� �̸� �ʿ��� ������ ���⼭ �����Ѵ�.
	BitFlag16_t		MapWeather;
	BYTE			CharacterMode0;
	BOOL			bMemberPCBang;
	CHARACTER		Character;
	char			ServerGroupName0[SIZE_MAX_SERVER_NAME];
	char			MainORTestServerName[SIZE_MAX_SERVER_NAME];
	char			GamePublisher[SIZE_MAX_GAME_PUBLISHER_NAME];
	BYTE			bIsLockSecondPW;			// 2008-08-26 by cmkwon, ��Ʈ�� VTC-Intecom_Viet 2�� �н����� �ý��� ���� ���� - 2�� �н����� ���� ����
};

//////////////////////////////////////////////////////////////////////////
// 2007-07-06 by dhjin, Tutorial
#define T_FC_TUTORIAL_START				(MessageType_t)((T0_FC_TUTORIAL<<8)|T1_FC_TUTORIAL_START)			// C->F
#define T_FC_TUTORIAL_START_OK			(MessageType_t)((T0_FC_TUTORIAL<<8)|T1_FC_TUTORIAL_START_OK)		// F->C
#define T_FC_TUTORIAL_COMPLETE			(MessageType_t)((T0_FC_TUTORIAL<<8)|T1_FC_TUTORIAL_COMPLETE)		// C->F
#define T_FC_TUTORIAL_COMPLETE_OK		(MessageType_t)((T0_FC_TUTORIAL<<8)|T1_FC_TUTORIAL_COMPLETE_OK)		// F->C
#define T_FC_TUTORIAL_END				(MessageType_t)((T0_FC_TUTORIAL<<8)|T1_FC_TUTORIAL_END)				// C->F
#define T_FC_TUTORIAL_END_OK			(MessageType_t)((T0_FC_TUTORIAL<<8)|T1_FC_TUTORIAL_END_OK)			// F->C
#define T_FC_TUTORIAL_WARP				(MessageType_t)((T0_FC_TUTORIAL<<8)|T1_FC_TUTORIAL_WARP)			// C->F

struct STUTORIAL_LIST_INFO
{// 2007-07-06 by dhjin, Tutorial �Ϸ� ���� ���� ����ü
	INT		TutorialNum;				// 2007-07-06 by dhjin, Tutorial ��ȣ 
	BYTE 	TutorialComplete;			// 2007-07-06 by dhjin, Tutorial �Ϸ� ����, 0 : FALSE, 1 : TRUE
};

struct MSG_FC_TUTORIAL_START_OK
{// 2007-07-06 by dhjin, Tutorial �Ϸ� ���� �޼���
	INT		TutorialInfoListCount;		// 2007-07-06 by dhjin, Tutorial ���� ����Ʈ ��
	_ARRAY(STUTORIAL_LIST_INFO);
};

struct MSG_FC_TUTORIAL_COMPLETE
{// 2007-07-06 by dhjin, Tutorial �Ϸ� ��ȣ
	INT		TutorialNum;
};

struct MSG_FC_TUTORIAL_COMPLETE_OK
{// 2007-07-06 by dhjin, Tutorial �Ϸ� ��ȣ
	INT		TutorialNum;
	INT		TutorialItemNum1;
	INT		TutorialItemCount1;
	INT		TutorialItemNum2;
	INT		TutorialItemCount2;
	INT		TutorialItemNum3;
	INT		TutorialItemCount3;
};


//////////////////////////////////////////////////////////////////////////
// 2007-08-13 by dhjin, OUTPOST
#define T_FC_OUTPOST_WAR_BEFORE				(MessageType_t)((T0_FC_OUTPOST<<8)|T1_FC_OUTPOST_WAR_BEFORE)			// F->C(N)
#define T_FC_OUTPOST_WAR_START 				(MessageType_t)((T0_FC_OUTPOST<<8)|T1_FC_OUTPOST_WAR_START)				// F->C(N)
#define T_FC_OUTPOST_PROTECTOR_DESTROY		(MessageType_t)((T0_FC_OUTPOST<<8)|T1_FC_OUTPOST_PROTECTOR_DESTROY)		// F->C(N)
//#define T_FC_OUTPOST_RESET_CHECK_START		(MessageType_t)((T0_FC_OUTPOST<<8)|T1_FC_OUTPOST_RESET_CHECK_START)		// C->F
//#define T_FC_OUTPOST_RESET_CHECK_START_OK	(MessageType_t)((T0_FC_OUTPOST<<8)|T1_FC_OUTPOST_RESET_CHECK_START_OK)	// F->C
#define T_FC_OUTPOST_RESET_START			(MessageType_t)((T0_FC_OUTPOST<<8)|T1_FC_OUTPOST_RESET_START)			// C->F
#define T_FC_OUTPOST_RESET_START_OK 		(MessageType_t)((T0_FC_OUTPOST<<8)|T1_FC_OUTPOST_RESET_START_OK)		// F->C(N)
#define T_FC_OUTPOST_RESET_DESTROY	 		(MessageType_t)((T0_FC_OUTPOST<<8)|T1_FC_OUTPOST_RESET_DESTROY)			// F->C
#define T_FC_OUTPOST_RESET_SUCCESS	 		(MessageType_t)((T0_FC_OUTPOST<<8)|T1_FC_OUTPOST_RESET_SUCCESS)			// F->C
#define T_FC_OUTPOST_WAR_END		 		(MessageType_t)((T0_FC_OUTPOST<<8)|T1_FC_OUTPOST_WAR_END)				// F->C(N)
#define T_FC_OUTPOST_NEXTWAR_INFO_REQUEST		(MessageType_t)((T0_FC_OUTPOST<<8)|T1_FC_OUTPOST_NEXTWAR_INFO_REQUEST)			// C->F
#define T_FC_OUTPOST_NEXTWAR_INFO_REQUEST_OK 	(MessageType_t)((T0_FC_OUTPOST<<8)|T1_FC_OUTPOST_NEXTWAR_INFO_REQUEST_OK)		// F->C(N)
#define T_FC_OUTPOST_NEXTWAR_SET_TIME 		(MessageType_t)((T0_FC_OUTPOST<<8)|T1_FC_OUTPOST_NEXTWAR_SET_TIME)			// C->F
#define T_FC_OUTPOST_NEXTWAR_SET_TIME_OK	(MessageType_t)((T0_FC_OUTPOST<<8)|T1_FC_OUTPOST_NEXTWAR_SET_TIME_OK)			// F->C
#define T_FC_OUTPOST_WAR_INFO				(MessageType_t)((T0_FC_OUTPOST<<8)|T1_FC_OUTPOST_WAR_INFO)					// F->C


struct MSG_FC_OUTPOST_WAR_BEFORE
{// 2007-08-13 by dhjin, OutPost ���� �� ���� �ð� ���� ����
	BYTE	RemainTime;
	BYTE	Influence;
	INT		MapIndex;
};

struct MSG_FC_OUTPOST_WAR_START
{// 2007-08-13 by dhjin, OutPost ���� ���� ����
	BYTE			OutPostState;
	BYTE			Influence;
	INT				MapIndex;
	ATUM_DATE_TIME	WarStartTime;
	ATUM_DATE_TIME	WarEndTime;
};

struct MSG_FC_OUTPOST_PROTECTOR_DESTROY
{// 2007-08-13 by dhjin, OutPost ��ȣ�� �ı� ����
	BYTE	Influence;
	INT		MapIndex;
	UID32_t	GuildUID;
	CHAR	GuildName[SIZE_MAX_GUILD_NAME];
};

struct MSG_FC_OUTPOST_RESET_START
{// 2007-08-16 by dhjin, �߾�ó����ġ ���� ����
	ClientIndex_t	TargetIndex;
};

struct MSG_FC_OUTPOST_RESET_START_OK
{// 2007-08-16 by dhjin, �߾�ó����ġ ���� ����
	BYTE	Influence;
	INT		MapIndex;
	UID32_t	GuildUID;
	CHAR	GuildName[SIZE_MAX_GUILD_NAME];
	ATUM_DATE_TIME	ResetStartTime;
	ATUM_DATE_TIME	ResetEndTime;
};

struct MSG_FC_OUTPOST_RESET_DESTROY
{// 2007-08-13 by dhjin, �߾�ó����ġ �ı���
	INT		MapIndex;
};

struct MSG_FC_OUTPOST_RESET_SUCCESS
{// 2007-08-13 by dhjin, �߾�ó����ġ ���� ���� 
	BYTE	Influence;
	INT		MapIndex;
	UID32_t	GuildUID;
	CHAR	GuildName[SIZE_MAX_GUILD_NAME];
};

struct MSG_FC_OUTPOST_WAR_END
{// 2007-08-13 by dhjin, ���������� ����
	BYTE	Influence;
	INT		MapIndex;
	UID32_t	GuildUID;
	CHAR	GuildName[SIZE_MAX_GUILD_NAME];
};

struct MSG_FC_OUTPOST_NEXTWAR_INFO_REQUEST_OK
{// 2007-08-13 by dhjin, ���������� �ð� ���� ���� ����
	ATUM_DATE_TIME	    OutPostNextWarTime;
	INT					OutPostNextWarSelectTimeChoice;
	INT					OutPostNextWarTimeListCount;
	_ARRAY(ATUM_DATE_TIME);
};

struct MSG_FC_OUTPOST_NEXTWAR_SET_TIME
{// 2007-08-13 by dhjin, ���������� ���� �ð� ����
	INT		OutPostNextWarSelectTimeChoice;
};

struct MSG_FC_OUTPOST_NEXTWAR_SET_TIME_OK
{// 2007-09-06 by dhjin, ���������� ���� �ð� ���� ������ ��� �������� �����ش�.
	MapIndex_t		MapIndex;
	ATUM_DATE_TIME	OutPostNextWarTime;
};

struct SOUTPOST_WAR_INFO
{// 2007-09-14 by dhjin, ���� ���� �� ������� ������ ���� ���̸� ������� ������ �������� �����ش�.
	BYTE			OutPostState;
	BYTE			OutPostResetIngInfluence;			// 2007-10-04 by dhjin, ���� ���� ����
	MapIndex_t		MapIndex;
	INT				OutPostWarResetRamainSecondTime;	// 2007-10-04 by dhjin, ���� �Ϸ���� ���� �ð�
	ATUM_DATE_TIME	OutPostWarStartTime;
	ATUM_DATE_TIME  OutPostWarEndTime;
	//	ATUM_DATE_TIME	OutPostWarResetStartTime;
	//	ATUM_DATE_TIME	OutPostWarResetEndTime;
};

struct MSG_FC_OUTPOST_WAR_INFO
{// 2007-09-14 by dhjin, ���� ���� �� ������� ������ ���� ���̸� ������� ������ �������� �����ش�.
	INT					OutPostWarInfoListCount;
	_ARRAY(SOUTPOST_WAR_INFO);
};


//////////////////////////////////////////////////////////////////////////
// 2007-08-13 by dhjin, �������� (����~! FC ���������� ���� ���� ���� �ʾƼ� �ǹ̰� ����� T_FC_INFO�� �켱 �Ҵ��Ͽ� ����)
#define T_FC_INFO_NOTICE_REQUEST		(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_NOTICE_REQUEST)			// C->F
#define T_FC_INFO_NOTICE_REQUEST_OK		(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_NOTICE_REQUEST_OK)		// F->C
#define T_FC_INFO_NOTICE_REG 			(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_NOTICE_REG)			// C->F
#define T_FC_INFO_NOTICE_REG_OK			(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_NOTICE_REG_OK)		// F->C
#define T_FC_INFO_NOTICE_MODIFY 		(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_NOTICE_MODIFY)			// C->F
#define T_FC_INFO_NOTICE_MODIFY_OK		(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_NOTICE_MODIFY_OK)		// F->C

struct MSG_FC_INFO_NOTICE_REQUEST
{// 2007-08-13 by dhjin, �������� ��û
	BYTE	NoticeState;
	INT		MapIndex;
};

struct MSG_FC_INFO_NOTICE_REQUEST_OK
{// 2007-08-13 by dhjin, �������� ��û ����
	CHAR	NoticeString[SIZE_MAX_NOTICE];
};

struct MSG_FC_INFO_NOTICE_REG
{// 2007-08-13 by dhjin, �������� ���
	UID32_t	GuildUID;
	CHAR	NoticeString[SIZE_MAX_NOTICE];
};

struct MSG_FC_INFO_NOTICE_MODIFY
{// 2007-08-13 by dhjin, �������� ����
	UID32_t	GuildUID;
	CHAR	NoticeString[SIZE_MAX_NOTICE];
};

//////////////////////////////////////////////////////////////////////////
// 2007-08-13 by dhjin, �ǰ��� (����~! FC ���������� ���� ���� ���� �ʾƼ� �ǹ̰� ����� T_FC_INFO�� �켱 �Ҵ��Ͽ� ����)
#define T_FC_INFO_EXPEDIENCYFUND_REQUEST 		(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_EXPEDIENCYFUND_REQUEST)			// C->F
#define T_FC_INFO_EXPEDIENCYFUND_REQUEST_OK		(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_EXPEDIENCYFUND_REQUEST_OK)		// F->C
#define T_FC_INFO_EXPEDIENCYFUND_PAYBACK 		(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_EXPEDIENCYFUND_PAYBACK)			// C->F
#define T_FC_INFO_EXPEDIENCYFUND_PAYBACK_OK		(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_EXPEDIENCYFUND_PAYBACK_OK)		// F->C
#define T_FC_INFO_SECONDARYPASSWORD_UPDATE_PASSWORD		(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_SECONDARYPASSWORD_UPDATE_PASSWORD)	// 2007-09-12 by cmkwon, ��Ʈ�� 2���н����� ���� - �������� �߰�, C->F
#define T_FC_INFO_SECONDARYPASSWORD_UPDATE_PASSWORD_OK	(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_SECONDARYPASSWORD_UPDATE_PASSWORD_OK)	// 2007-09-12 by cmkwon, ��Ʈ�� 2���н����� ���� - �������� �߰�, F->C
#define T_FC_INFO_SECONDARYPASSWORD_CHECK_PASSWORD		(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_SECONDARYPASSWORD_CHECK_PASSWORD)	// 2007-09-12 by cmkwon, ��Ʈ�� 2���н����� ���� - �������� �߰�, C->F
#define T_FC_INFO_SECONDARYPASSWORD_CHECK_PASSWORD_OK	(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_SECONDARYPASSWORD_CHECK_PASSWORD_OK)	// 2007-09-12 by cmkwon, ��Ʈ�� 2���н����� ���� - �������� �߰�, F->C
#define T_FC_INFO_SECONDARYPASSWORD_LOCK				(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_SECONDARYPASSWORD_LOCK)				// 2007-09-12 by cmkwon, ��Ʈ�� 2���н����� ���� - �������� �߰�, C->F
#define T_FC_INFO_SECONDARYPASSWORD_LOCK_OK				(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_SECONDARYPASSWORD_LOCK_OK)			// 2007-09-12 by cmkwon, ��Ʈ�� 2���н����� ���� - �������� �߰�, F->C

struct MSG_FC_INFO_EXPEDIENCYFUND_REQUEST
{// 2007-08-13 by dhjin, �ǰ��� ���� ��û
	INT 	MapIndex;
};

struct MSG_FC_INFO_EXPEDIENCYFUND_REQUEST_OK
{// 2007-08-13 by dhjin, �ǰ��� ���� ����
	INT		CumulativeExpediencyFund;
	INT		ExpediencyFund;
	INT		ExpediencyFundRate;
};

struct MSG_FC_INFO_EXPEDIENCYFUND_PAYBACK
{// 2007-08-13 by dhjin, �ǰ��� ��û ��û
	INT	 ExpediencyFundPayBackCount;
};

struct MSG_FC_INFO_EXPEDIENCYFUND_PAYBACK_OK
{// 2007-08-13 by dhjin, �ǰ��� ��û ó�� ���� ����
	INT		CumulativeExpediencyFund;
	INT		ExpediencyFund;
	INT		ExpediencyFundPayBackCount;
	INT		ExpediencyFundRate;
};

struct MSG_FC_INFO_SECONDARYPASSWORD_UPDATE_PASSWORD
{// 2007-09-12 by cmkwon, ��Ʈ�� 2���н����� ���� -
	char	CurrentSecPassword[SIZE_MAX_PASSWORD_MD5_STRING];
	char	NewSecPassword[SIZE_MAX_PASSWORD_MD5_STRING];
};
struct MSG_FC_INFO_SECONDARYPASSWORD_CHECK_PASSWORD
{// 2007-09-12 by cmkwon, ��Ʈ�� 2���н����� ���� -
	char	CurrentSecPassword[SIZE_MAX_PASSWORD_MD5_STRING];
};
struct MSG_FC_INFO_SECONDARYPASSWORD_LOCK
{// 2007-09-12 by cmkwon, ��Ʈ�� 2���н����� ���� -	
	BYTE	bIsUnlockFlag;		// FALSE�̸� Lock, FALSE�� �ƴϸ� Unlock
	char	CurrentSecPassword[SIZE_MAX_PASSWORD_MD5_STRING];
};
struct MSG_FC_INFO_SECONDARYPASSWORD_LOCK_OK
{// 2007-09-12 by cmkwon, ��Ʈ�� 2���н����� ���� -	
	BYTE	bIsUnlockFlag;		// FALSE�̸� Lock, FALSE�� �ƴϸ� Unlock
};


//////////////////////////////////////////////////////////////////////////
// 2007-09-06 by dhjin, �ڷ���Ʈ Ŭ���Ͽ� ������ �����Ѵ�.
#define T_FC_EVENT_CLICK_TELEPORT			(MessageType_t)((T0_FC_EVENT<<8)|T1_FC_EVENT_CLICK_TELEPORT)		// 2007-09-06 by dhjin, C->F
#define T_FC_EVENT_CLICK_TELEPORT_OK		(MessageType_t)((T0_FC_EVENT<<8)|T1_FC_EVENT_CLICK_TELEPORT_OK)		// 2008-04-22 by dhjin, F->C ���� ���� ǥ�� ��ȹ�� - �ڷ���Ʈ ���� �Ϸ� �ð�
#define T_FC_EVENT_TELEPORT_BUILDCOMPLETE	(MessageType_t)((T0_FC_EVENT<<8)|T1_FC_EVENT_TELEPORT_BUILDCOMPLETE)		// 2007-09-19 by dhjin, F->C(n)
#define T_FC_EVENT_TELEPORT_DESTROY			(MessageType_t)((T0_FC_EVENT<<8)|T1_FC_EVENT_TELEPORT_DESTROY)		// 2007-09-19 by dhjin, F->C(n)

struct MSG_FC_EVENT_CLICK_TELEPORT
{// 2007-09-06 by dhjin, �ڷ���Ʈ Ŭ��
	INT 			MapIndex;
	ClientIndex_t	TargetIndex;
};

struct MSG_FC_EVENT_CLICK_TELEPORT_OK
{// 2008-04-22 by dhjin, ���� ���� ǥ�� ��ȹ�� - �ڷ���Ʈ ���� �Ϸ� �ð�
	INT				MapIndex;
	ATUM_DATE_TIME 	StartTime;
	ATUM_DATE_TIME 	EndTime;
};

struct MSG_FC_EVENT_TELEPORT_BUILDCOMPLETE
{// 2007-09-06 by dhjin, �ڷ���Ʈ �ϼ�
	MapIndex_t 		MapIndex;
};

struct MSG_FC_EVENT_TELEPORT_DESTROY
{// 2007-09-20 by cmkwon, �ڷ���Ʈ ���� - 
	MapIndex_t 		MapIndex;
	BOOL			bInactivateByOtherTeleport;		// 2007-09-20 by cmkwon, �ڷ���Ʈ ���� - �ʵ��߰�, FALSE�̸� ���ݿ� ���� ����, TRUE�̸� �ٸ� Teleport �������� ���� ��Ȱ��ȭ
};

///////////////////////////////////////////////////////////////////////////////
// 2007-11-28 by cmkwon, �����ý��� ���� -
#define T_FC_EVENT_NOTIFY_MSG_GET			(MessageType_t)((T0_FC_EVENT<<8)|T1_FC_EVENT_NOTIFY_MSG_GET)	// 2007-11-28 by cmkwon, �����ý��� ���� - C->F
#define T_FC_EVENT_NOTIFY_MSG_GET_OK		(MessageType_t)((T0_FC_EVENT<<8)|T1_FC_EVENT_NOTIFY_MSG_GET_OK)	// 2007-11-28 by cmkwon, �����ý��� ���� - F->C
#define T_FC_EVENT_NOTIFY_MSG_DELETE		(MessageType_t)((T0_FC_EVENT<<8)|T1_FC_EVENT_NOTIFY_MSG_DELETE)	// 2007-11-28 by cmkwon, �����ý��� ���� - C->F

struct MSG_FC_EVENT_NOTIFY_MSG_GET_OK		// 2007-11-28 by cmkwon, �����ý��� ���� -
{
	UID64_t			NotifyMsgUID;				//	
	UID32_t			CharacterUID;				// �����޽��� ���� ĳ���� UID, 0 �̸� ��� ĳ���Ϳ��� ����(0 �ΰ��� ������ ���� �� ����)
	BYTE			NotifyMsgType;				// NOTIFY_MSG_TYPE_XXX
	char			NotifyMsgString[SIZE_MAX_NOTIFY_MSG_STRING];
};

struct MSG_FC_EVENT_NOTIFY_MSG_DELETE		// 2007-11-28 by cmkwon, �����ý��� ���� -
{
	UID64_t			NotifyMsgUID;				//	
};

///////////////////////////////////////////////////////////////////////////////
// 2008-01-10 by cmkwon, ������ �̺�Ʈ �ý��ۿ� �� ���� �ý��� �߰� - 
#define T_FC_EVENT_COUPON_EVENT_INFO			(MessageType_t)((T0_FC_EVENT<<8)|T1_FC_EVENT_COUPON_EVENT_INFO)				// 2008-01-10 by cmkwon, ������ �̺�Ʈ �ý��ۿ� �� ���� �ý��� �߰� - F->C
#define T_FC_EVENT_COUPON_EVENT_USE_COUPON		(MessageType_t)((T0_FC_EVENT<<8)|T1_FC_EVENT_COUPON_EVENT_USE_COUPON)		// 2008-01-10 by cmkwon, ������ �̺�Ʈ �ý��ۿ� �� ���� �ý��� �߰� - C->F
#define T_FC_EVENT_COUPON_EVENT_USE_COUPON_OK	(MessageType_t)((T0_FC_EVENT<<8)|T1_FC_EVENT_COUPON_EVENT_USE_COUPON_OK)	// 2008-01-10 by cmkwon, ������ �̺�Ʈ �ý��ۿ� �� ���� �ý��� �߰� - F->C
struct MSG_FC_EVENT_COUPON_EVENT_INFO				// 2008-01-10 by cmkwon, ������ �̺�Ʈ �ý��ۿ� �� ���� �ý��� �߰� - 
{
	int		ItemEventUID;
	int		ItemEventType;
};
struct MSG_FC_EVENT_COUPON_EVENT_USE_COUPON			// 2008-01-10 by cmkwon, ������ �̺�Ʈ �ý��ۿ� �� ���� �ý��� �߰� - 
{
	int		ItemEventUID;
	char	CouponNumber[SIZE_MAX_COUPON_NUMBER];
};
struct MSG_FC_EVENT_COUPON_EVENT_USE_COUPON_OK		// 2008-01-10 by cmkwon, ������ �̺�Ʈ �ý��ۿ� �� ���� �ý��� �߰� - 
{
	int		ItemEventUID;
};



//////////////////////////////////////////////////////////////////////////
// 2007-10-29 by dhjin, Poll�ý��� ����
#define T_FC_CITY_POLL_REQUEST_LEADER_CANDIDATE_LIST			(MessageType_t)((T0_FC_CITY<<8)|T1_FC_CITY_POLL_REQUEST_LEADER_CANDIDATE_LIST)			// C->F, ������ �ĺ� ����Ʈ ��û
#define T_FC_CITY_POLL_REQUEST_LEADER_CANDIDATE_LIST_OK_HEADER	(MessageType_t)((T0_FC_CITY<<8)|T1_FC_CITY_POLL_REQUEST_LEADER_CANDIDATE_LIST_OK_HEADER)		// F->C, ������ �ĺ� ����Ʈ ��û
#define T_FC_CITY_POLL_REQUEST_LEADER_CANDIDATE_LIST_OK			(MessageType_t)((T0_FC_CITY<<8)|T1_FC_CITY_POLL_REQUEST_LEADER_CANDIDATE_LIST_OK)		// F->C, ������ �ĺ� ����Ʈ ��û
#define T_FC_CITY_POLL_REQUEST_LEADER_CANDIDATE_LIST_OK_DONE	(MessageType_t)((T0_FC_CITY<<8)|T1_FC_CITY_POLL_REQUEST_LEADER_CANDIDATE_LIST_OK_DONE)		// F->C, ������ �ĺ� ����Ʈ ��û
#define T_FC_CITY_POLL_REQUEST_LEADER_CANDIDATE_INFO			(MessageType_t)((T0_FC_CITY<<8)|T1_FC_CITY_POLL_REQUEST_LEADER_CANDIDATE_INFO)			// C->F, ������ �ĺ� ���� ��û
#define T_FC_CITY_POLL_REQUEST_LEADER_CANDIDATE_INFO_OK			(MessageType_t)((T0_FC_CITY<<8)|T1_FC_CITY_POLL_REQUEST_LEADER_CANDIDATE_INFO_OK)		// F->C, ������ �ĺ� ���� ��û
#define T_FC_CITY_POLL_REQUEST_LEADER_CANDIDATE_INFO_OK_GUILDMARK			(MessageType_t)((T0_FC_CITY<<8)|T1_FC_CITY_POLL_REQUEST_LEADER_CANDIDATE_INFO_OK_GUILDMARK)		// F->C, ������ �ĺ� ���� ��û
#define T_FC_CITY_POLL_REG_LEADER_CANDIDATE						(MessageType_t)((T0_FC_CITY<<8)|T1_FC_CITY_POLL_REG_LEADER_CANDIDATE)					// C->F, ������ �ĺ� ���
#define T_FC_CITY_POLL_REG_LEADER_CANDIDATE_OK					(MessageType_t)((T0_FC_CITY<<8)|T1_FC_CITY_POLL_REG_LEADER_CANDIDATE_OK)				// F->C, ������ �ĺ� ���
#define T_FC_CITY_POLL_DELETE_LEADER_CANDIDATE					(MessageType_t)((T0_FC_CITY<<8)|T1_FC_CITY_POLL_DELETE_LEADER_CANDIDATE)				// C->F, ������ �ĺ� Ż��
#define T_FC_CITY_POLL_DELETE_LEADER_CANDIDATE_OK				(MessageType_t)((T0_FC_CITY<<8)|T1_FC_CITY_POLL_DELETE_LEADER_CANDIDATE_OK)				// F->C, ������ �ĺ� Ż��
#define T_FC_CITY_POLL_VOTE										(MessageType_t)((T0_FC_CITY<<8)|T1_FC_CITY_POLL_VOTE)									// C->F, ������ �ĺ����� ��ǥ
#define T_FC_CITY_POLL_VOTE_OK									(MessageType_t)((T0_FC_CITY<<8)|T1_FC_CITY_POLL_VOTE_OK)								// F->C, ������ �ĺ����� ��ǥ
#define T_FC_CITY_POLL_REQUEST_POLL_DATE						(MessageType_t)((T0_FC_CITY<<8)|T1_FC_CITY_POLL_REQUEST_POLL_DATE)						// C->F, ���� �Ⱓ ��û
#define T_FC_CITY_POLL_REQUEST_POLL_DATE_OK						(MessageType_t)((T0_FC_CITY<<8)|T1_FC_CITY_POLL_REQUEST_POLL_DATE_OK)					// F->C, ���� �Ⱓ ��û
#define T_FC_CITY_POLL_LEADER_ELECTION_INFO						(MessageType_t)((T0_FC_CITY<<8)|T1_FC_CITY_POLL_LEADER_ELECTION_INFO)					// F->C, ���� ��� ����

struct MSG_FC_CITY_POLL_REQUEST_LEADER_CANDIDATE_LIST_OK_HEADER
{// 2007-10-29 by dhjin, ������ �ĺ� ����Ʈ ����
	BOOL			RegLeaderCandidate;								// ������ �ĺ� �⸶ �� ����, TURE = �⸶
};

struct MSG_FC_CITY_POLL_REQUEST_LEADER_CANDIDATE_LIST_OK
{// 2007-10-29 by dhjin, ������ �ĺ� ����Ʈ ����
	INT				LeaderCandidateNum;							//	������ �ĺ� ��ȣ
	UID32_t			CharacterUID;								//	������ �ĺ� UID
	UID32_t			GuildUID;									//  ������ �ĺ� ��� UID
	BOOL			DeleteCandidate;							//  �̹� ���� �Ⱓ�� �ĺ� Ż�� �ߴ��� ����, TRUE = Ż��
	CHAR			CharacterName[SIZE_MAX_CHARACTER_NAME];		//  ������ �ĺ� �̸�
	CHAR			GuildName[SIZE_MAX_GUILD_NAME];				//  ������ �ĺ� ����
};

struct MSG_FC_CITY_POLL_REQUEST_LEADER_CANDIDATE_INFO
{// 2007-10-29 by dhjin, ������ �ĺ� ���� ����
	INT				LeaderCandidateNum;							//	������ �ĺ� ��ȣ
};

struct MSG_FC_CITY_POLL_REQUEST_LEADER_CANDIDATE_INFO_OK
{// 2007-10-29 by dhjin, ������ �ĺ� ���� ����
	BYTE			PilotFace;									//  ������ �ĺ� ��
	BYTE			Level;										//	������ �ĺ� Level
	INT				GuildFame;									//	������ �ĺ� ���� ����
	UID32_t			AccountUID;									//	������ �ĺ� ���� UID
	UID32_t			CharacterUID;								//	������ �ĺ� UID
	CHAR			CharacterName[SIZE_MAX_CHARACTER_NAME];		//  ������ �ĺ� �̸�
	CHAR			GuildName[SIZE_MAX_GUILD_NAME];				//  ������ �ĺ� ����
	CHAR			CampaignPromises[SIZE_MAX_CAMPAIGNPROMISES];//  ������ �ĺ� ����
};

struct MSG_FC_CITY_POLL_REQUEST_LEADER_CANDIDATE_INFO_OK_GUILDMARK
{// 2007-11-01 by dhjin, ������ �ĺ� ���� ���� ���� ��ũ
	INT				GuildMarkSize;								//  ������ �ĺ� ���� ��ũ ũ��
	UID32_t			GuildUID;									//  ������ �ĺ� ��� UID
	ARRAY_(char);												//	������ �ĺ� ���� ��ũ
};

struct MSG_FC_CITY_POLL_REG_LEADER_CANDIDATE
{// 2007-10-29 by dhjin, ������ �ĺ� ���
	UID32_t			CharacterUID;								//	������ �ĺ� UID
	UID32_t			GuildUID;									//  ������ �ĺ� ��� UID
	CHAR			CampaignPromises[SIZE_MAX_CAMPAIGNPROMISES];//  ������ �ĺ� ����
};

struct MSG_FC_CITY_POLL_REG_LEADER_CANDIDATE_OK
{// 2007-10-29 by dhjin, ������ �ĺ� ���
	INT				LeaderCandidateNum;							//	������ �ĺ� ��ȣ
};

struct MSG_FC_CITY_POLL_DELETE_LEADER_CANDIDATE
{// 2007-10-29 by dhjin, ������ �ĺ� Ż��
	UID32_t			CharacterUID;								//	������ �ĺ� UID
};

struct MSG_FC_CITY_POLL_VOTE
{// 2007-10-29 by dhjin, ��ǥ
	INT				LeaderCandidateNum;							//	������ �ĺ� ��ȣ
	UID32_t			CharacterUID;								//	������ �ĺ� UID
	UID32_t			VoteCharacterUID;							//	��ǥ�� UID
};

struct MSG_FC_CITY_POLL_REQUEST_POLL_DATE_OK
{// 2007-10-29 by dhjin, ���� ����
	ATUM_DATE_TIME	ApplicationStartDate;		// �ĺ� ��û ���� ��
	ATUM_DATE_TIME	ApplicationEndDate;			// �ĺ� ��û ������ ��
	ATUM_DATE_TIME	VoteStartDate;				// ��ǥ ���� ��
	ATUM_DATE_TIME	VoteEndDate;				// ��ǥ ������ ��
	ATUM_DATE_TIME	Election;					// ������
};

struct MSG_FC_CITY_POLL_LEADER_ELECTION_INFO
{// 2007-11-16 by dhjin, ���� ���
	INT				LeaderCandidateNum;							//	������ �ĺ� ��ȣ
	CHAR			CharacterName[SIZE_MAX_CHARACTER_NAME];		//  ������ �ĺ� �̸�
	CHAR			GuildName[SIZE_MAX_GUILD_NAME];				//  ������ �ĺ� ����
	INT				Percent;									//  ������ ��ǥ��
};

//////////////////////////////////////////////////////////////////////////
// 2007-12-03 by dhjin, ���� ���� 
#define T_FC_CITY_WARINFO_INFLUENCE						(MessageType_t)((T0_FC_CITY<<8)|T1_FC_CITY_WARINFO_INFLUENCE)		// C->F, ���� ����
#define T_FC_CITY_WARINFO_INFLUENCE_OK					(MessageType_t)((T0_FC_CITY<<8)|T1_FC_CITY_WARINFO_INFLUENCE_OK)	// F->C, ���� ����
#define T_FC_CITY_WARINFO_OUTPOST						(MessageType_t)((T0_FC_CITY<<8)|T1_FC_CITY_WARINFO_OUTPOST)			// C->F, �������� ���� 
#define T_FC_CITY_WARINFO_OUTPOST_OK					(MessageType_t)((T0_FC_CITY<<8)|T1_FC_CITY_WARINFO_OUTPOST_OK)		// F->C, �������� ���� 

struct MSG_FC_CITY_WARINFO_INFLUENCE_OK
{// 2007-12-03 by dhjin, ���� ���� 
	INT			VCNInfluencePoint;
	INT			ANIInfluencePoint;
	CHAR		VCNInfluenceLeader[SIZE_MAX_CHARACTER_NAME];
	CHAR		VCNInfluenceSubLeader1[SIZE_MAX_CHARACTER_NAME];
	CHAR		VCNInfluenceSubLeader2[SIZE_MAX_CHARACTER_NAME];
	CHAR		ANIInfluenceLeader[SIZE_MAX_CHARACTER_NAME];
	CHAR		ANIInfluenceSubLeader1[SIZE_MAX_CHARACTER_NAME];
	CHAR		ANIInfluenceSubLeader2[SIZE_MAX_CHARACTER_NAME];
};

struct SCITY_WARINFO_OUTPOST
{// 2007-12-03 by dhjin, �������� ���� 
	BYTE			Influence;
	MapIndex_t		MapIndex;
	UID32_t			GuildUID;
	CHAR			GuildCommander[SIZE_MAX_CHARACTER_NAME];
	CHAR			GuildName[SIZE_MAX_GUILD_NAME];
	ATUM_DATE_TIME	OutpostDate;
};

struct MSG_FC_CITY_WARINFO_OUTPOST_OK
{// 2007-12-03 by dhjin, ���������� ����
	INT					CityWarInfoOutpostListCount;
	_ARRAY(SCITY_WARINFO_OUTPOST);
};

#define T_FC_INFO_GET_GUILDMARK				(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_GET_GUILDMARK)			// 2007-12-07 by dhjin, ���� ��ũ C->F
#define T_FC_INFO_GET_GUILDMARK_OK			(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_GET_GUILDMARK_OK)		// 2007-12-07 by dhjin, ���� ��ũ F->C
struct MSG_FC_INFO_GET_GUILDMARK
{// 2007-12-07 by dhjin
	UID32_t			GuildUID;
};

struct MSG_FC_INFO_GET_GUILDMARK_OK
{// 2007-12-07 by dhjin, ���� ��ũ ����
	INT				GuildMarkSize;
	INT				GuildMarkVersion;
	UID32_t			GuildUID;
	ARRAY_(char);
};

// 2007-12-27 by dhjin, �Ʒ��� ���� - �Ʒ��� �������� MainField <=> ArenaField 
#define T_FtoA_MFSINFO						(MessageType_t)((T0_MF_TO_AF<<8)|T1_FtoA_MFSINFO)			// 2007-12-27 by dhjin, �Ʒ��� ������ �ʵ� ���� ��� �� �ʵ� ���� ���� ����, MF->AF
#define T_FtoA_MFSINFO_OK					(MessageType_t)((T0_MF_TO_AF<<8)|T1_FtoA_MFSINFO_OK)		// 2007-12-27 by dhjin, �Ʒ��� ������ �ʵ� ���� ��� �� �ʵ� ���� ���� ����, AF->MF
#define T_FtoA_ALIVE						(MessageType_t)((T0_MF_TO_AF<<8)|T1_FtoA_ALIVE)				// 2007-12-27 by dhjin,
#define T_FtoA_AUTH_CHARACTER				(MessageType_t)((T0_MF_TO_AF<<8)|T1_FtoA_AUTH_CHARACTER)	// 2007-12-27 by dhjin, �Ʒ��� �������� ��ȿ�� �������� �ʵ� ������ Ȯ�� ��û, AF->MF
#define T_FtoA_AUTH_CHARACTER_OK			(MessageType_t)((T0_MF_TO_AF<<8)|T1_FtoA_AUTH_CHARACTER_OK)	// 2007-12-27 by dhjin, �Ʒ��� �������� ��ȿ�� �������� �ʵ� ������ Ȯ�� ��û, MF->AF
#define T_FtoA_ARENA_STATE_CHANGE			(MessageType_t)((T0_MF_TO_AF<<8)|T1_FtoA_ARENA_STATE_CHANGE)	// 2008-01-03 by dhjin, �ʵ� ������ ���� �Ʒ��� ���°� ����, AF->MF
#define T_FtoA_ARENA_TEAM_MATCHING			(MessageType_t)((T0_MF_TO_AF<<8)|T1_FtoA_ARENA_TEAM_MATCHING)	// 2008-01-04 by dhjin, �ʵ� ������ ��Ī ������ �����Ѵ�, AF->MF
#define T_FtoA_ARENA_TEAM_MATCHING_OK		(MessageType_t)((T0_MF_TO_AF<<8)|T1_FtoA_ARENA_TEAM_MATCHING_OK)	// 2008-01-04 by dhjin, �ʵ� ������ ��Ī ������ �����Ѵ�, MF->AF
#define T_FtoA_ARENA_SERVER_PAY				(MessageType_t)((T0_MF_TO_AF<<8)|T1_FtoA_ARENA_SERVER_PAY)		// 2008-01-10 by dhjin, �ʵ� ������ ���� �Ʒ��� ���� ����, AF->MF
#define T_FtoA_ARENA_CHARACTER_PAY			(MessageType_t)((T0_MF_TO_AF<<8)|T1_FtoA_ARENA_CHARACTER_PAY)	// 2008-01-10 by dhjin, �ʵ� ������ �ɸ��� �Ʒ��� ���� ����, AF->MF
#define T_FtoA_ARENA_CHARACTER_DISCONNECT	(MessageType_t)((T0_MF_TO_AF<<8)|T1_FtoA_ARENA_CHARACTER_DISCONNECT)	// 2008-01-15 by dhjin, �ʵ� ������ �ɸ��� �Ʒ��� ���� ����, AF->MF
#define T_FtoA_ARENA_CHARACTERARENAINFO_UPDATA	(MessageType_t)((T0_MF_TO_AF<<8)|T1_FtoA_ARENA_CHARACTERARENAINFO_UPDATA)	// 2012-04-12 by jhseol, �Ʒ��� �߰����� - ���� : AFS -> MFS CharacterArena UUpdata ��û ��Ŷ
#define T_FtoA_ARENA_CHARACTER_RESET_RELOAD	(MessageType_t)((T0_MF_TO_AF<<8)|T1_FtoA_ARENA_CHARACTER_RESET_RELOAD)	// 2012-12-18 by jhseol, �Ʒ��� ĳ���� ���� �� ĳ���� ���� �ٽ� �ε��ϱ�.
struct MSG_FtoA_MFSINFO
{
	USHORT		MFS_Port;
	USHORT		MFS_ID;
	CHAR		MFS_Name[SIZE_MAX_SERVER_NAME];
	CHAR		MFS_IP[SIZE_MAX_IPADDRESS];
};

struct MSG_FtoA_AUTH_CHARACTER
{
	UID32_t			AccountUID;
	UID32_t			MFSCharacterUID;
	ClientIndex_t	MFSClientIndex;
	ClientIndex_t	AFSClientIndex;
};

struct MSG_FtoA_AUTH_CHARACTER_OK
{
	bool			ErrorCheck;		// TRUE -> Error
	UID32_t			AccountUID;
	UID32_t			MFSCharacterUID;
	CHAR			MFSCharacterName[SIZE_MAX_CHARACTER_NAME];
	ClientIndex_t	MFSClientIndex;
	UID32_t			AFSCharacterUID;
	CHAR			AFSCharacterName[SIZE_MAX_CHARACTER_NAME];
	ClientIndex_t	AFSClientIndex;
	MessageType_t	ErrorMsgType;			// 2010-04-05 by cmkwon, ���� ������ ī�� ���� �ý��� ���� - 
	Err_t			ErrorCode;				// 2010-04-05 by cmkwon, ���� ������ ī�� ���� �ý��� ���� - 
	BOOL			ShutDownMins; // 2011-11-03 by shcho, yedang �˴ٿ��� ���� - �Ʒ������� �˴ٿ��� ������
	SArenaPlayInfo	ArenaPlayInfo;			// 2012-04-12 by jhseol, �Ʒ��� �߰����� - ���� : �Ʒ��� �÷��� ������ ������ ����ü ����.
};

struct MSG_FtoA_ARENA_STATE_CHANGE
{
	UID32_t			AccountUID;
	UID32_t			MFSCharacterUID;
	ClientIndex_t	MFSClientIndex;
	BYTE			AFSArenaState;
	ClientIndex_t	AFSClientIndex;
};

struct MSG_FtoA_ARENA_TEAM_MATCHING
{
	UID32_t			AccountUID;
	UID32_t			MFSCharacterUID;
	ClientIndex_t	MFSClientIndex;
	UID32_t			AFSCharacterUID;
	ClientIndex_t	AFSClientIndex;
};

struct MSG_FtoA_ARENA_TEAM_MATCHING_OK
{
	ClientIndex_t	AFSClientIndex;
	UID32_t			AccountUID;
	UID32_t			AFSCharacterUID;
};

struct MSG_FtoA_ARENA_SERVER_PAY
{
	BYTE			Influence;
	INT				PayInfluencePoint;
};

struct MSG_FtoA_ARENA_CHARACTER_PAY
{
	BYTE			Issue;					// 2007-04-20 by dhjin, �Ʒ��� ���� ����, 1 : ARENA_ISSUE_WIN, 2 : ARENA_ISSUE_LOSE, 3 : ARENA_ISSUE_DRAW
	INT				PayWarPoint;
	UID32_t			AccountUID;
	UID32_t			MFSCharacterUID;
	ClientIndex_t	MFSClientIndex;
	ClientIndex_t	AFSClientIndex;
};

struct MSG_FtoA_ARENA_CHARACTER_DISCONNECT
{
	UID32_t			AccountUID;
	UID32_t			MFSCharacterUID;
	UID32_t			ArenaCharacterUID;	// 2012-10-21 by jhseol, �Ʒ��� ���׼��� - �Ʒ��� ����� �ɸ��� ���� ����.
	ClientIndex_t	MFSClientIndex;
	ClientIndex_t	AFSClientIndex;
};

// 2012-12-18 by jhseol, �Ʒ��� ĳ���� ���� �� ĳ���� ���� �ٽ� �ε��ϱ�.
struct MSG_FtoA_ARENA_CHARACTER_RESET_RELOAD
{
	UID32_t			AccountUID;
	UID32_t			ArenaCharacterUID;
};
// end 2012-12-18 by jhseol, �Ʒ��� ĳ���� ���� �� ĳ���� ���� �ٽ� �ε��ϱ�.

//////////////////////////////////////////////////////////////////////
// 2012-04-12 by jhseol, �Ʒ��� �߰����� - ���� : MF CharacterArena ������Ʈ ��Ŷ
struct MSG_FtoA_ARENA_CHARACTERARENAINFO_UPDATA
{
	UID32_t			AccountUID;
	UID32_t			MFSCharacterUID;
	ClientIndex_t	MFSClientIndex;
	ClientIndex_t	AFSClientIndex;
	SArenaPlayInfo	ArenaInfo;
};
// end 2012-04-12 by jhseol, �Ʒ��� �߰����� - ���� : MF CharacterArena ������Ʈ ��Ŷ

//////////////////////////////////////////////////////////////////////////
// 2008-03-27 by dhjin, ���� ���� ǥ�� ��ȹ�� - 
#define T_FC_INFO_MSWARINFO_DISPLAY				(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_MSWARINFO_DISPLAY)			// 2008-03-27 by dhjin, ���� ���� ǥ�� ��ȹ�� - ���� ���� ���� F->C
#define T_FC_INFO_MSWARINFO_DISPLAY_OPTION		(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_MSWARINFO_DISPLAY_OPTION)	// 2008-03-27 by dhjin, ���� ���� ǥ�� ��ȹ�� - ���� ���� �ɼ� ���� C->F
#define T_FC_INFO_MSWARINFO_DISPLAY_OPTION_OK	(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_MSWARINFO_DISPLAY_OPTION_OK)	// 2008-03-27 by dhjin, ���� ���� ǥ�� ��ȹ�� - ���� ���� �ɼ� ���� F->C(n)
struct SMSWARINFO_DISPLAY
{// 2008-03-26 by dhjin, ���� ���� ǥ�� ��ȹ�� - �������� �ʿ��� ���� ǥ�� ����Ÿ
	MapIndex_t		MapIndex;
	INT				MapInfluenceType;
	INT				HPRate;
	INT				TelePortState;
	ATUM_DATE_TIME	TelePortBuildingStartTime;
	ATUM_DATE_TIME	TelePortBuildingEndTime;
	BYTE			DisplatType;	// 2013-08-14 by jhseol, ������ ������ - ��� Ÿ�� (0:����, 1:�Ϲ� ������)
};

struct MSG_FC_INFO_MSWARINFO_DISPLAY
{// 2008-03-26 by dhjin, ���� ���� ǥ�� ��ȹ�� - �������� �ʿ��� ���� ǥ�� ����Ÿ
	INT				MSWarInfoDisPlayListCount;
	_ARRAY(SMSWARINFO_DISPLAY);
};

struct MSG_FC_INFO_MSWARINFO_DISPLAY_OPTION
{// 2008-03-26 by dhjin, ���� ���� ǥ�� ��ȹ�� - ���� ���� �ɼ�
	SHORT			MSWarOptionType;
	UID32_t			CharacterUID;
	ClientIndex_t	ClientIndex;
};

struct MSG_FC_INFO_MSWARINFO_DISPLAY_OPTION_OK
{// 2008-03-26 by dhjin, ���� ���� ǥ�� ��ȹ�� - ���� ���� �ɼ�
	SHORT			MSWarOptionType;
};

//////////////////////////////////////////////////////////////////////////
// 2008-04-02 by dhjin, ����, ������ ����â ��ȹ�� - 
#define T_FC_INFO_MSWARINFO_RESULT				(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_MSWARINFO_RESULT)	// 2008-04-02 by dhjin, ����, ������ ����â ��ȹ�� - ���� ��� ���� C->F
#define T_FC_INFO_MSWARINFO_RESULT_OK			(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_MSWARINFO_RESULT_OK)	// 2008-04-02 by dhjin, ����, ������ ����â ��ȹ�� - ���� ��� ���� F->C
#define T_FC_INFO_SPWARINFO_RESULT				(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_SPWARINFO_RESULT)	// 2008-04-02 by dhjin, ����, ������ ����â ��ȹ�� - ������ ��� ���� C->F
#define T_FC_INFO_SPWARINFO_RESULT_OK_HEADER	(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_SPWARINFO_RESULT_OK_HEADER)	// 2008-04-02 by dhjin, ����, ������ ����â ��ȹ�� - ������ ��� ���� F->C
#define T_FC_INFO_SPWARINFO_RESULT_OK			(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_SPWARINFO_RESULT_OK)	// 2008-04-02 by dhjin, ����, ������ ����â ��ȹ�� - ������ ��� ���� F->C
#define T_FC_INFO_SPWARINFO_RESULT_OK_DONE		(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_SPWARINFO_RESULT_OK_DONE)	// 2008-04-02 by dhjin, ����, ������ ����â ��ȹ�� - ������ ��� ���� F->C
struct MSG_FC_INFO_MSWARINFO_RESULT_OK
{// 2008-04-02 by dhjin, ����, ������ ����â ��ȹ�� - ���� ��� ���� F->C
	INT				MSWarInfoResultListCount;
	_ARRAY(SMSWAR_INFO_RESULT);
};

//////////////////////////////////////////////////////////////////////////
// 2008-04-29 by dhjin, EP3 ���� �ý��� - 
#define T_FC_CHAT_LETTER_REQUEST_TITLE			(MessageType_t)((T0_FC_CHAT<<8)|T1_FC_CHAT_LETTER_REQUEST_TITLE)			// 2008-04-29 by dhjin, EP3 ���� �ý��� - ���� ����Ʈ ��û C->F
#define T_FC_CHAT_LETTER_REQUEST_TITLE_OK_HEADER (MessageType_t)((T0_FC_CHAT<<8)|T1_FC_CHAT_LETTER_REQUEST_TITLE_OK_HEADER)	// 2008-04-29 by dhjin, EP3 ���� �ý��� - ���� ����Ʈ ���� F->C
#define T_FC_CHAT_LETTER_REQUEST_TITLE_OK		(MessageType_t)((T0_FC_CHAT<<8)|T1_FC_CHAT_LETTER_REQUEST_TITLE_OK)			// 2008-04-29 by dhjin, EP3 ���� �ý��� - ���� ����Ʈ ���� F->C
#define T_FC_CHAT_LETTER_REQUEST_TITLE_OK_DONE	(MessageType_t)((T0_FC_CHAT<<8)|T1_FC_CHAT_LETTER_REQUEST_TITLE_OK_DONE)	// 2008-04-29 by dhjin, EP3 ���� �ý��� - ���� ����Ʈ ���� F->C
#define T_FC_CHAT_LETTER_READ					(MessageType_t)((T0_FC_CHAT<<8)|T1_FC_CHAT_LETTER_READ)						// 2008-04-29 by dhjin, EP3 ���� �ý��� - ���� �б� ��û C->F
#define T_FC_CHAT_LETTER_READ_OK				(MessageType_t)((T0_FC_CHAT<<8)|T1_FC_CHAT_LETTER_READ_OK)					// 2008-04-29 by dhjin, EP3 ���� �ý��� - ���� �б� �Ϸ� F->C
#define T_FC_CHAT_LETTER_DELETE					(MessageType_t)((T0_FC_CHAT<<8)|T1_FC_CHAT_LETTER_DELETE)					// 2008-04-29 by dhjin, EP3 ���� �ý��� - ���� ����� ��û C->F
#define T_FC_CHAT_LETTER_DELETE_OK				(MessageType_t)((T0_FC_CHAT<<8)|T1_FC_CHAT_LETTER_DELETE_OK)				// 2008-04-29 by dhjin, EP3 ���� �ý��� - ���� ����� �Ϸ� F->C
#define T_FC_CHAT_LETTER_SEND					(MessageType_t)((T0_FC_CHAT<<8)|T1_FC_CHAT_LETTER_SEND)						// 2008-05-08 by dhjin, EP3 ���� �ý��� - ���� ���� C->F
#define T_FC_CHAT_LETTER_SEND_OK				(MessageType_t)((T0_FC_CHAT<<8)|T1_FC_CHAT_LETTER_SEND_OK)					// 2008-05-08 by dhjin, EP3 ���� �ý��� - ���� ���� �Ϸ� F->C 
#define T_FC_CHAT_LETTER_RECEIVE				(MessageType_t)((T0_FC_CHAT<<8)|T1_FC_CHAT_LETTER_RECEIVE)					// 2008-05-08 by dhjin, EP3 ���� �ý��� - ���� ���� ���� F->C
#define T_FC_CHAT_ALLLETTER_REQUEST_TITLE			(MessageType_t)((T0_FC_CHAT<<8)|T1_FC_CHAT_ALLLETTER_REQUEST_TITLE)				// 2008-05-09 by dhjin, EP3 ���� �ý��� - ��ü ���� ����Ʈ ��û C->F
#define T_FC_CHAT_ALLLETTER_REQUEST_TITLE_OK_HEADER (MessageType_t)((T0_FC_CHAT<<8)|T1_FC_CHAT_ALLLETTER_REQUEST_TITLE_OK_HEADER)	// 2008-05-09 by dhjin, EP3 ���� �ý��� - ��ü ���� ����Ʈ ���� F->C
#define T_FC_CHAT_ALLLETTER_REQUEST_TITLE_OK		(MessageType_t)((T0_FC_CHAT<<8)|T1_FC_CHAT_ALLLETTER_REQUEST_TITLE_OK)			// 2008-05-09 by dhjin, EP3 ���� �ý��� - ��ü ���� ����Ʈ ���� F->C
#define T_FC_CHAT_ALLLETTER_REQUEST_TITLE_OK_DONE	(MessageType_t)((T0_FC_CHAT<<8)|T1_FC_CHAT_ALLLETTER_REQUEST_TITLE_OK_DONE)		// 2008-05-09 by dhjin, EP3 ���� �ý��� - ��ü ���� ����Ʈ ���� F->C
#define T_FC_CHAT_ALLLETTER_READ					(MessageType_t)((T0_FC_CHAT<<8)|T1_FC_CHAT_ALLLETTER_READ)						// 2008-05-09 by dhjin, EP3 ���� �ý��� - ��ü ���� �б� ��û C->F
#define T_FC_CHAT_ALLLETTER_READ_OK					(MessageType_t)((T0_FC_CHAT<<8)|T1_FC_CHAT_ALLLETTER_READ_OK)					// 2008-05-09 by dhjin, EP3 ���� �ý��� - ��ü ���� �б� �Ϸ� F->C
#define T_FC_CHAT_ALLLETTER_DELETE					(MessageType_t)((T0_FC_CHAT<<8)|T1_FC_CHAT_ALLLETTER_DELETE)					// 2008-05-09 by dhjin, EP3 ���� �ý��� - ��ü ���� ����� ��û C->F
#define T_FC_CHAT_ALLLETTER_DELETE_OK				(MessageType_t)((T0_FC_CHAT<<8)|T1_FC_CHAT_ALLLETTER_DELETE_OK)					// 2008-05-09 by dhjin, EP3 ���� �ý��� - ��ü ���� ����� �Ϸ� F->C
#define T_FC_CHAT_ALLLETTER_SEND					(MessageType_t)((T0_FC_CHAT<<8)|T1_FC_CHAT_ALLLETTER_SEND)						// 2008-05-09 by dhjin, EP3 ���� �ý��� - ��ü ���� ���� C->F
#define T_FC_CHAT_ALLLETTER_SEND_OK					(MessageType_t)((T0_FC_CHAT<<8)|T1_FC_CHAT_ALLLETTER_SEND_OK)					// 2008-05-09 by dhjin, EP3 ���� �ý��� - ��ü ���� ���� �Ϸ� F->C 
#define T_FC_CHAT_ALLLETTER_RECEIVE					(MessageType_t)((T0_FC_CHAT<<8)|T1_FC_CHAT_ALLLETTER_RECEIVE)					// 2008-05-09 by dhjin, EP3 ���� �ý��� - ��ü ���� ���� ���� F->C

struct MSG_FC_CHAT_LETTER_REQUEST_TITLE_OK
{// 2008-04-29 by dhjin, EP3 ���� �ý��� - ���� ����Ʈ ����
	UID64_t			LetterUID;
	CHAR			SendCharacterName[SIZE_MAX_CHARACTER_NAME];
	ATUM_DATE_TIME  SendDate;
	BOOL			CheckRead;
	CHAR			Title[SIZE_MAX_LETTER_TITLE];
};
typedef MSG_FC_CHAT_LETTER_REQUEST_TITLE_OK		MSG_FC_CHAT_ALLLETTER_REQUEST_TITLE_OK;

struct MSG_FC_CHAT_LETTER_READ
{// 2008-04-29 by dhjin, EP3 ���� �ý��� - ���� ���� ��û
	UID64_t			LetterUID;
	BOOL			CheckRead;
};
typedef MSG_FC_CHAT_LETTER_READ			MSG_FC_CHAT_ALLLETTER_READ;

struct MSG_FC_CHAT_LETTER_READ_OK
{// 2008-04-29 by dhjin, EP3 ���� �ý��� - ���� ���� ����
	UID64_t			LetterUID;
	CHAR			Content[SIZE_MAX_LETTER_CONTENT];
};
typedef MSG_FC_CHAT_LETTER_READ_OK		MSG_FC_CHAT_ALLLETTER_READ_OK;

struct MSG_FC_CHAT_LETTER_DELETE
{// 2008-04-29 by dhjin, EP3 ���� �ý��� - ���� ����� 
	UID64_t			LetterUID;
};
typedef MSG_FC_CHAT_LETTER_DELETE		MSG_FC_CHAT_ALLLETTER_DELETE;

struct MSG_FC_CHAT_LETTER_DELETE_OK
{// 2008-04-29 by dhjin, EP3 ���� �ý��� - ���� ����� �Ϸ�
	UID64_t			LetterUID;
};
typedef MSG_FC_CHAT_LETTER_DELETE_OK	MSG_FC_CHAT_ALLLETTER_DELETE_OK;

struct MSG_FC_CHAT_LETTER_SEND
{// 2008-05-08 by dhjin, EP3 ���� �ý��� - ���� ������
	INT				SendCharacterUID;
	CHAR			RecvCharacterName[SIZE_MAX_CHARACTER_NAME];
	CHAR			Title[SIZE_MAX_LETTER_TITLE];
	CHAR			Content[SIZE_MAX_LETTER_CONTENT];
};
typedef MSG_FC_CHAT_LETTER_SEND			MSG_FC_CHAT_ALLLETTER_SEND;

struct MSG_FC_CHAT_LETTER_RECEIVE
{// 2008-05-08 by dhjin, EP3 ���� �ý��� - ���� ���� ����
	CHAR				SendCharacterName[SIZE_MAX_CHARACTER_NAME];
};
typedef MSG_FC_CHAT_LETTER_RECEIVE		MSG_FC_CHAT_ALLLETTER_RECEIVE;

//////////////////////////////////////////////////////////////////////////
// 2008-08-18 by dhjin, ���¸�ũ�̺�Ʈ 
#define T_FC_EVENT_INFLUENCEMARK		(MessageType_t)((T0_FC_EVENT<<8)|T1_FC_EVENT_INFLUENCEMARK)		
#define T_FC_EVENT_INFLUENCEMARKEND		(MessageType_t)((T0_FC_EVENT<<8)|T1_FC_EVENT_INFLUENCEMARKEND)
struct MSG_FC_EVENT_INFLUENCEMARK
{
	BYTE			Influence;		// ���¸�ũ�̺�Ʈ����
};

//////////////////////////////////////////////////////////////////////////
// 2008-12-02 by dhjin, �̼Ǹ�����
#define T_FC_QUEST_REQUEST_MISSIONMASTER_HELP			(MessageType_t)((T0_FC_QUEST<<8)|T1_FC_QUEST_REQUEST_MISSIONMASTER_HELP)		// 2008-12-02 by dhjin, C -> F, �̼Ǹ����� ��û
#define T_FC_QUEST_REQUEST_MISSIONMASTER_HELP_INVITE	(MessageType_t)((T0_FC_QUEST<<8)|T1_FC_QUEST_REQUEST_MISSIONMASTER_HELP_INVITE)	// 2008-12-02 by dhjin, F -> C(n), �������� ���� �̼Ǹ����Ϳ��� ��û
#define T_FC_QUEST_MISSIONMASTER_HELP_INVITE			(MessageType_t)((T0_FC_QUEST<<8)|T1_FC_QUEST_MISSIONMASTER_HELP_INVITE)			// 2008-12-02 by dhjin, C -> F, �̼Ǹ����� ��û �¶� 
#define T_FC_QUEST_MISSIONMASTER_HELP_INVITE_OK			(MessageType_t)((T0_FC_QUEST<<8)|T1_FC_QUEST_MISSIONMASTER_HELP_INVITE_OK)		// 2008-12-02 by dhjin, F -> C, �̼Ǹ����� ��û �¶�
#define T_FC_QUEST_MISSIONMASTER_HELP_REJECT			(MessageType_t)((T0_FC_QUEST<<8)|T1_FC_QUEST_MISSIONMASTER_HELP_REJECT)			// 2008-12-02 by dhjin, C -> F, �̼Ǹ����� ��û ���� 
#define T_FC_QUEST_MISSIONMASTER_HELP_REJECT_OK			(MessageType_t)((T0_FC_QUEST<<8)|T1_FC_QUEST_MISSIONMASTER_HELP_REJECT_OK)		// 2008-12-02 by dhjin, F -> C, �̼Ǹ����� ��û ����
struct MSG_FC_QUEST_REQUEST_MISSIONMASTER_HELP
{
	INT				QuestIdx;
};

struct MSG_FC_QUEST_REQUEST_MISSIONMASTER_HELP_INVITE
{
	ClientIndex_t	ClientIdx;
	UID32_t			CharacterUID;		// 2008-12-02 by dhjin, �̼Ǹ����� ��û�� �ɸ���
	char			CharacterName[SIZE_MAX_CHARACTER_NAME];
	PartyID_t		PartyID;
};

struct MSG_FC_QUEST_MISSIONMASTER_HELP_INVITE
{
	UID32_t			CharacterUID;		// 2008-12-02 by dhjin, �̼Ǹ����� ��û�� �ɸ���
};

struct MSG_FC_QUEST_MISSIONMASTER_HELP_INVITE_OK
{
	ClientIndex_t	ClientIdx;
	UID32_t			CharacterUID;		// 2008-12-02 by dhjin, �̼Ǹ����� �ɸ���
	char			CharacterName[SIZE_MAX_CHARACTER_NAME];
};

struct MSG_FC_QUEST_MISSIONMASTER_HELP_REJECT
{
	UID32_t			CharacterUID;		// 2008-12-02 by dhjin, �̼Ǹ����� ��û�� �ɸ���
};

struct MSG_FC_QUEST_MISSIONMASTER_HELP_REJECT_OK
{
	ClientIndex_t	ClientIdx;
	UID32_t			CharacterUID;		// 2008-12-02 by dhjin, �̼Ǹ����� �ɸ���
	char			CharacterName[SIZE_MAX_CHARACTER_NAME];
};

//////////////////////////////////////////////////////////////////////////
// 2009-01-12 by dhjin, ���� ���� -
#define T_FC_INFO_DECLARATION_MSWAR_INFO		(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_DECLARATION_MSWAR_INFO)		// 2009-01-12 by dhjin, ���� ���� - �������� ���� ��û C->F
#define T_FC_INFO_DECLARATION_MSWAR_INFO_OK		(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_DECLARATION_MSWAR_INFO_OK)	// 2009-01-12 by dhjin, ���� ���� - �������� ���� ���� F->C
#define T_FC_INFO_DECLARATION_MSWAR_SET			(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_DECLARATION_MSWAR_SET)	// 2009-01-12 by dhjin, ���� ���� - �������� �ð� �� ���� ���� C->F
#define T_FI_INFO_DECLARATION_MSWAR_SET_OK		(MessageType_t)((T0_FI_INFO<<8)|T1_FI_INFO_DECLARATION_MSWAR_SET_OK)	// 2009-01-12 by dhjin, ���� ���� - �������� �ð� �� ���� ���� F->I
#define T_IC_INFO_DECLARATION_MSWAR_SET_OK		(MessageType_t)((T0_IC_INFO<<8)|T1_IC_INFO_DECLARATION_MSWAR_SET_OK)	// 2009-01-12 by dhjin, ���� ���� - �������� �ð� �� ���� ���� I->C
struct MSG_FC_INFO_DECLARATION_MSWAR_INFO_OK
{// 2009-01-12 by dhjin, ���� ���� - �������� ���� ���� F->C
	INT								DeclarationOfWarListCount;
	SDECLARATION_OF_WAR_FORBID_TIME	ForbidTime;
	_ARRAY(SDECLARATION_OF_WAR);
};

struct MSG_FC_INFO_DECLARATION_MSWAR_SET
{// 2009-01-12 by dhjin, ���� ���� - �������� �ð� �� ���� ���� C->F
	BYTE			MSWarStep;
	ATUM_DATE_TIME	MSWarStartTime;
	BOOL			GiveUp;
};

struct MSG_FI_INFO_DECLARATION_MSWAR_SET_OK
{// 2009-01-12 by dhjin, ���� ���� - �������� �ð� �� ���� ���� F->C
	BYTE			Influence;		// ���� ������ ������ ����.
	ATUM_DATE_TIME	MSWarStartTime;
	BOOL			GiveUp;
	BYTE			SelectCount;
};
typedef MSG_FI_INFO_DECLARATION_MSWAR_SET_OK	MSG_IC_INFO_DECLARATION_MSWAR_SET_OK;


///////////////////////////////////////////////////////////////////////////////
// 2009-02-12 by cmkwon, EP3-3 ���巩ŷ�ý��� ���� - 
#define T_FC_INFO_WRK_GET_SERVICE_INFO					(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_WRK_GET_SERVICE_INFO)			// 2009-02-12 by cmkwon, EP3-3 ���巩ŷ�ý��� ���� - C->F
#define T_FC_INFO_WRK_GET_SERVICE_INFO_OK				(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_WRK_GET_SERVICE_INFO_OK)			// 2009-02-12 by cmkwon, EP3-3 ���巩ŷ�ý��� ���� - F->C
#define T_FC_INFO_WRK_GET_SERVICE_INFO_OK_IMAGE			(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_WRK_GET_SERVICE_INFO_OK_IMAGE)	// 2009-02-12 by cmkwon, EP3-3 ���巩ŷ�ý��� ���� - F->C
#define T_FC_INFO_WRK_GET_SERVICE_INFO_OK_DONE			(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_WRK_GET_SERVICE_INFO_OK_DONE)	// 2009-02-12 by cmkwon, EP3-3 ���巩ŷ�ý��� ���� - F->C
#define T_FC_INFO_WRK_GET_RANKER_LIST					(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_WRK_GET_RANKER_LIST)				// 2009-02-12 by cmkwon, EP3-3 ���巩ŷ�ý��� ���� - C->F
#define T_FC_INFO_WRK_GET_LEVEL_RANKER_LIST_OK			(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_WRK_GET_LEVEL_RANKER_LIST_OK)	// 2009-02-12 by cmkwon, EP3-3 ���巩ŷ�ý��� ���� - F->C
#define T_FC_INFO_WRK_GET_FAME_RANKER_LIST_OK			(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_WRK_GET_FAME_RANKER_LIST_OK)		// 2009-02-12 by cmkwon, EP3-3 ���巩ŷ�ý��� ���� - F->C
#define T_FC_INFO_WRK_GET_PVP_RANKER_LIST_OK			(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_WRK_GET_PVP_RANKER_LIST_OK)		// 2009-02-12 by cmkwon, EP3-3 ���巩ŷ�ý��� ���� - F->C
#define T_FC_INFO_WRK_GET_SELF_RANKING					(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_WRK_GET_SELF_RANKING)			// 2009-02-12 by cmkwon, EP3-3 ���巩ŷ�ý��� ���� - C->F
#define T_FC_INFO_WRK_GET_SELF_RANKING_OK				(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_WRK_GET_SELF_RANKING_OK)			// 2009-02-12 by cmkwon, EP3-3 ���巩ŷ�ý��� ���� - F->C
struct MSG_FC_INFO_WRK_GET_SERVICE_INFO_OK
{
	INT		ServiceUID;
	char	ServiceName[SIZE_MAX_SERVICE_NAME];
	INT		SymbolImageSize;
};
struct MSG_FC_INFO_WRK_GET_SERVICE_INFO_OK_IMAGE
{
	INT		ServiceUID;
	BYTE	SymbolImageIndex;
	BYTE	SymbolImage[1000];
};
struct MSG_FC_INFO_WRK_GET_RANKER_LIST
{
	BYTE	byRankingType;			// RANKING_TYPE_XXX
	INT		UnitKind;
	BYTE	byScope;				// RANKING_SCOPE_XXX
	BYTE	byStartRank;
	BYTE	byReqRankerCnt;
};
struct MSG_FC_INFO_WRK_GET_LEVEL_RANKER_LIST_OK
{
	BYTE	byStartRank;
	BYTE	byRankerCnt;
	_ARRAY(SWRK_LEVEL);
};
struct MSG_FC_INFO_WRK_GET_FAME_RANKER_LIST_OK
{
	BYTE	byStartRank;
	BYTE	byRankerCnt;
	_ARRAY(SWRK_FAME);

};
struct MSG_FC_INFO_WRK_GET_PVP_RANKER_LIST_OK
{
	BYTE	byStartRank;
	BYTE	byRankerCnt;
	_ARRAY(SWRK_PVP);
};
struct MSG_FC_INFO_WRK_GET_SELF_RANKING_OK
{
	UID32_t	CharacUID;
	INT		LevelRanking;
	INT		FameRanking;
	INT		PvPRanking;
};



///////////////////////////////////////////////////////////////////////////////
// 2009-03-31 by cmkwon, �����ʱ�ȭ �ý��� ���� - 
#define T_FC_QUEST_INSERT_QUEST			(MessageType_t)((T0_FC_QUEST<<8)|T1_FC_QUEST_INSERT_QUEST)	// 2009-03-31 by cmkwon, �����ʱ�ȭ �ý��� ���� - F->C
#define T_FC_QUEST_DELETE_QUEST			(MessageType_t)((T0_FC_QUEST<<8)|T1_FC_QUEST_DELETE_QUEST)	// 2009-03-31 by cmkwon, �����ʱ�ȭ �ý��� ���� - F->C

struct MSG_FC_QUEST_INSERT_QUEST
{
	INT		QuestIndex;
	BYTE	QuestState;				// �Ϸ�, ������
};
struct MSG_FC_QUEST_DELETE_QUEST
{
	INT		QuestIndex;
};

////////////////////////////////////////////////////////////////////////////////
// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - 
#define T_FN_MONSTER_HPTALK							(MessageType_t)((T0_FN_MONSTER<<8)|T1_FN_MONSTER_HPTALK)	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - , N->F
struct MSG_FN_MONSTER_HPTALK {
	MAP_CHANNEL_INDEX				ChannelIndex;
	ClientIndex_t					MonsterIndex;				// �ε���
	INT								MonsterUnitKind;			// ���� ������ȣ
	HPValueRate_t					HPValueRate;
	eHPACTION_TALK_IMPORTANCE		HPTalkImportance;
	MSec_t							HPCameraTremble;
	ClientIndex_t					TargetIndex;				// ��� ���õ� ��簡 �ִٸ� �����Ѵ�.	
	HPTalk_t						HPTalk[SIZE_MAX_HPTALK_DESCRIPTION];
};

#define T_FC_MONSTER_HPTALK							(MessageType_t)((T0_FC_MONSTER<<8)|T1_FC_MONSTER_HPTALK)	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - , F->C(n)
struct MSG_FC_MONSTER_HPTALK {
	ClientIndex_t					MonsterIndex;				// �ε���
	INT								MonsterUnitKind;			// ���� ������ȣ
	eHPACTION_TALK_IMPORTANCE		HPTalkImportance;
	MSec_t							HPCameraTremble;
	ClientIndex_t					TargetIndex;				// ��� ���õ� ��簡 �ִٸ� �����Ѵ�.
	HPTalk_t						HPTalk[SIZE_MAX_HPTALK_DESCRIPTION];
};

#define T_FN_BATTLE_ATTACK_SKILL					(MessageType_t)((T0_FN_BATTLE<<8)|T1_FN_BATTLE_ATTACK_SKILL)				// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - N -> F
struct MSG_FN_BATTLE_ATTACK_SKILL
{
	MAP_CHANNEL_INDEX	MapInfo;
	ClientIndex_t		MonsterIndex;				// ��ų�� ����� ����
	ClientIndex_t		ClientIndex;				// Ŭ���̾�Ʈ �ε���
	INT					SkillItemNum;				// ��ų�� ItemNum
	AVECTOR3			PositionVector;
	AVECTOR3			TargetVector;
	float				fIncreasePowerRatio;		// ��ų�� �Ŀ�(������ or ����/����� ���� ȿ��) ������.		// 2010. 06. 08 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����. (�Ʊ� ���� �뷱�� ����.) - ���� ��ų �뷱�� ����.
};

#define T_FC_MONSTER_SKILL							(MessageType_t)((T0_FC_MONSTER<<8)|T1_FC_MONSTER_SKILL)	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - , F->C(n)
struct MSG_FC_MONSTER_SKILL {
	ClientIndex_t		MonsterIndex;				// ��ų�� ����� ����
	ClientIndex_t		ClientIndex;				// Ŭ���̾�Ʈ �ε���
	INT					SkillItemNum;				// ��ų�� ItemNum
	AVECTOR3			PositionVector;
	AVECTOR3			TargetVector;
};

#define T_FC_BATTLE_MONSTER_BARRIER_USING		(MessageType_t)((T0_FC_BATTLE<<8)|T1_FC_BATTLE_MONSTER_BARRIER_USING)	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - F -> C
struct MSG_FC_BATTLE_MONSTER_BARRIER_USING {
	ClientIndex_t		MonsterIndex;				// ��ų�� ����� ����
};

#define T_FC_BATTLE_MONSTER_BARRIER_USE			(MessageType_t)((T0_FC_BATTLE<<8)|T1_FC_BATTLE_MONSTER_BARRIER_USE)		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - F -> C(n)
struct MSG_FC_BATTLE_MONSTER_BARRIER_USE {
	ClientIndex_t		MonsterIndex;				// ��ų�� ����� ����
	INT					SkillItemNum;
};

#define T_FC_CHARACTER_DEBUFF_DOT_INFO			(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_DEBUFF_DOT_INFO)			// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - C -> F
#define T_FC_CHARACTER_DEBUFF_DOT_INFO_OK		(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_DEBUFF_DOT_INFO_OK)		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - F -> C
#define T_FC_CHARACTER_DEBUFF_DOT_APPLYING		(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_DEBUFF_DOT_APPLYING)		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - F -> C
#define T_FC_CHARACTER_DEBUFF_DOT_RELEASE		(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_DEBUFF_DOT_RELEASE)		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - F -> C
struct MSG_FC_CHARACTER_DEBUFF_DOT_INFO {
	UID32_t			CharacterUID;
};

struct MSG_DEBUFF_INFO {
	INT					ItemNum;						// ������ ������ȣ, ���� �������� �� (ITEM_BASE*)
};

struct MSG_DOT_INFO {
	INT					ItemNum;						// ������ ������ȣ, ���� �������� �� (ITEM_BASE*)
};

struct MSG_FC_CHARACTER_DEBUFF_DOT_INFO_OK {
	UID32_t				CharacterUID;
	INT					DebuffCount;
	INT					DotCount;
	_ARRAY(MSG_DEBUFF_INFO);
	_ARRAY(MSG_DOT_INFO);
};
struct MSG_FC_CHARACTER_DEBUFF_DOT_APPLYING {
	UID32_t				CharacterUID;
	INT					SkillItemNum;
};

struct MSG_FC_CHARACTER_DEBUFF_DOT_RELEASE {
	UID32_t				CharacterUID;
	INT					SkillItemNum;
};


#define T_FC_INFINITY_MODE_LIST					(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_MODE_LIST)				// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ����Ʈ ��û, C -> F
#define T_FC_INFINITY_MODE_LIST_OK				(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_MODE_LIST_OK)			// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ����Ʈ ��û, F -> C
struct INFINITY_MODE_INFO {
	MapIndex_t		InfinityMapIdx;
	InfiModeUID_t	InfinityModeUID;
	eINFINITY_MODE	InfinityMode;
	Lv_t			MinLv;
	Lv_t			MaxLv;
	BOOL			Join;
	Minute_t		TimePenaltyValue;		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ����� �г�Ƽ �߰�
	INT				MinMemberCount;			// 2009-09-09 ~ 2010-01-22 by dhjin, ���Ǵ�Ƽ - �ּ�,�ִ��ο� ���� �߰�
	INT				MaxMemberCount;			// 2009-09-09 ~ 2010-01-22 by dhjin, ���Ǵ�Ƽ - �ּ�,�ִ��ο� ���� �߰�
	INT				InfinityDifficultyStep; // 2010. 05. 19 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����. (��ȣó�� + ���� ó��(����) ) - ������ ���̵� ���� �߰�.
	Penalty_t		HPPenaltyValue;			// 2011-06-14 by hskim, ���Ǵ�Ƽ 3�� - �г�Ƽ ��� �߰� (HP �� �ð� ���� ������ ����)
};
struct MSG_FC_INFINITY_MODE_LIST_OK {
	INT				InfinityModeListCount;
	_ARRAY(INFINITY_MODE_INFO);
};

#define T_FC_INFINITY_READY_LIST					(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_READY_LIST)				// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ����Ʈ ��û, C -> F
#define T_FC_INFINITY_READY_LIST_OK					(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_READY_LIST_OK)				// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ����Ʈ ��û, F -> C
struct MSG_FC_INFINITY_READY_LIST {
	MapIndex_t		InfinityMapIdx;
	eINFINITY_MODE	InfinityMode;
};

struct INFINITY_READY_LIST {
	InfinityCreateUID_t	InfinityCreateUID;
	CHAR				MasterName[SIZE_MAX_CHARACTER_NAME];
	CHAR				InfinityTeamName[SIZE_MAX_PARTY_NAME];
	INT					PlayingRoomMemberCount;
	INT					MaxMemberCount;
	INT					DifficultLevel;
};
struct MSG_FC_INFINITY_READY_LIST_OK {
	INT				InfinityPlayingListCount;
	_ARRAY(INFINITY_READY_LIST);
};

#define T_FC_INFINITY_CREATE						(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_CREATE)				// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���� ��û, C -> F
#define T_FC_INFINITY_CREATE_OK						(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_CREATE_OK)			// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���� ��û, F -> C
struct MSG_FC_INFINITY_CREATE {
	InfiModeUID_t	InfinityModeUID;
	eINFINITY_MODE	InfinityMode;
	MapIndex_t		MapIndex;
	CHAR			InfinityTeamName[SIZE_MAX_PARTY_NAME];
	INT				InfinityDifficultyLevel;
};
struct MSG_FC_INFINITY_CREATE_OK {
	InfinityCreateUID_t	InfinityCreateUID;

	// 2010. 05. 19 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����. (��ȣó�� + ���� ó��(����) )
	INT					IntinityDifficultyLevel;
	// End 2010. 05. 19 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����. (��ȣó�� + ���� ó��(����) )

};

#define T_FC_INFINITY_JOIN							(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_JOIN)						// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���� ��û, C -> F
#define T_FC_INFINITY_JOIN_REQUEST_MASTERUSER		(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_JOIN_REQUEST_MASTERUSER)		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���忡�� ������ ���� ���� ��û, F -> C
#define T_FC_INFINITY_JOIN_REQUEST_MASTERUSER_OK	(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_JOIN_REQUEST_MASTERUSER_OK)	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���忡�� ������ ���� ���� ��û, C -> F
#define T_FC_INFINITY_JOIN_OK						(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_JOIN_OK)						// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���� ��û, F -> C
#define T_FC_INFINITY_MEMBER_INFO_LIST				(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_MEMBER_INFO_LIST)			// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� �ɹ� ����, C -> F
#define T_FC_INFINITY_MEMBER_INFO_LIST_OK			(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_MEMBER_INFO_LIST_OK)			// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� �ɹ� ����, F -> C
struct MSG_FC_INFINITY_JOIN {
	eINFINITY_MODE		InfinityMode;
	InfinityCreateUID_t	InfinityCreateUID;
	InfiModeUID_t		InfinityModeUID;		// 2010-03-23 by cmkwon, ���Ǵ�Ƽ ���� ĳ�� ������ ���� - 
};
struct MSG_FC_INFINITY_JOIN_REQUEST_MASTERUSER {
	ClientIndex_t		ReQuestClientIdx;
	CHAR				ReQuestCharacterName[SIZE_MAX_CHARACTER_NAME];
	USHORT				Gear;
	BYTE				Lv;
};
struct MSG_FC_INFINITY_JOIN_REQUEST_MASTERUSER_OK {
	ClientIndex_t		ReQuestClientIdx;
	BOOL				bAccept;
	eINFINITY_MODE		InfinityMode;
	InfinityCreateUID_t	InfinityCreateUID;
};
struct MSG_FC_INFINITY_JOIN_OK {
	ClientIndex_t		JoinClientIdx;
	CHAR				JoinCharacterName[SIZE_MAX_CHARACTER_NAME];
	USHORT				Gear;
	BYTE				Lv;
	BOOL				bAccept;
};
struct INFINITY_MEMBER_INFO_LIST {
	ClientIndex_t		ClientIdx;
	CHAR				CharacterName[SIZE_MAX_CHARACTER_NAME];
	USHORT				Gear;
	BYTE				Lv;
	eINFINITY_STATE		State;
};
struct MSG_FC_INFINITY_MEMBER_INFO_LIST_OK {
	ClientIndex_t		MasterClientIdx;
	INT					InfinityMemberListCount;
	_ARRAY(INFINITY_MEMBER_INFO_LIST);
};

#define T_FC_INFINITY_CHANGE_MASTER					(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_CHANGE_MASTER)			// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ������ ����, C -> F
#define T_FC_INFINITY_CHANGE_MASTER_OK				(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_CHANGE_MASTER_OK)		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ������ ����, F -> C
#define T_FC_INFINITY_LEAVE							(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_LEAVE)					// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� Ż��, C -> F
#define T_FC_INFINITY_LEAVE_OK						(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_LEAVE_OK)				// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� Ż��, F -> C
#define T_FC_INFINITY_BAN							(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_BAN)						// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� �߹�, C -> F
#define T_FC_INFINITY_BAN_OK						(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_BAN_OK)					// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� �߹�, F -> C
struct MSG_FC_INFINITY_CHANGE_MASTER {
	ClientIndex_t		ChangeMasterClientIdx;
};
struct MSG_FC_INFINITY_CHANGE_MASTER_OK {
	ClientIndex_t		ChangeMasterClientIdx;
};
struct MSG_FC_INFINITY_LEAVE_OK {
	ClientIndex_t		LeaveClientIdx;
};
struct MSG_FC_INFINITY_BAN {
	ClientIndex_t		BanClientIdx;
};
struct MSG_FC_INFINITY_BAN_OK {
	ClientIndex_t		BanClientIdx;
};

#define T_FtoA_INFINITY_IMPUTE_LIST					(MessageType_t)((T0_MF_TO_AF<<8)|T1_FtoA_INFINITY_IMPUTE_LIST)			// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� �ͼ� ���� ����, MFS -> AFS
struct MSG_FtoA_INFINITY_IMPUTE_LIST {
	ClientIndex_t	AFSClientIndex;
	INT				InfinityImputeListCount;
	BOOL			bHaveReentryTicket;			// 2010-03-23 by cmkwon, ���Ǵ�Ƽ ���� ĳ�� ������ ���� - 
	_ARRAY(INFINITY_IMPUTE);
};

#define T_FC_INFINITY_READY							(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_READY)			// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���� ��ư ����, C -> F
#define T_FC_INFINITY_READY_OK						(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_READY_OK)		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���� ��ư ����, F -> C
#define T_FC_INFINITY_READY_CANCEL					(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_READY_CANCEL)	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ������� ��ư ����, C -> F
#define T_FC_INFINITY_READY_CANCEL_OK				(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_READY_CANCEL_OK)	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ������� ��ư ����, F -> C
#define T_FC_INFINITY_READY_CANCEL_ALL_OK			(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_READY_CANCEL_ALL_OK)	// // 2010. 05. 31 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����. (������Ʈ ���� �뷱�� ���� ���� ����.) - ���Ǵ�Ƽ - ���̵� ����� ��� ���� ���. ( AFS -> C )
struct MSG_FC_INFINITY_READY_OK {
	ClientIndex_t		ReadyClientIdx;
};
struct MSG_FC_INFINITY_READY_CANCEL_OK {
	ClientIndex_t		ReadyCancelClientIdx;
};

// 2010. 05. 31 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����. (������Ʈ ���� �뷱�� ���� ���� ����.) - ���Ǵ�Ƽ �� ���̵� ����� ��� ���� ��� ��Ŷ.
struct MSG_FC_INFINITY_READY_CANCEL_ALL_OK
{
	InfinityCreateUID_t	InfinityCreateUID;
};
// End 2010. 05. 31 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����. (������Ʈ ���� �뷱�� ���� ���� ����.)

#define T_FC_INFINITY_START							(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_START)			// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���� ��ư ����(���� ����), C -> F
#define T_FtoA_INFINITY_START						(MessageType_t)((T0_MF_TO_AF<<8)|T1_FtoA_INFINITY_START)			// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���� MainFieldServer�� �˸�, AFS -> MFS
#define T_FtoA_INFINITY_START_OK					(MessageType_t)((T0_MF_TO_AF<<8)|T1_FtoA_INFINITY_START_OK)			// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���� MainFieldSever�غ� �Ϸ� ����, MFS -> AFS
#define T_FC_INFINITY_MAP_LOADING					(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_MAP_LOADING)		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� �� �ε� �������� �˸�, F -> C  <-- ����!!!! ���� �����!
#define T_FC_INFINITY_MAP_LOADED					(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_MAP_LOADED)		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� �� �ε� �Ϸ�, C -> F
#define T_FtoA_INFINITY_IMPUTE						(MessageType_t)((T0_MF_TO_AF<<8)|T1_FtoA_INFINITY_IMPUTE)			// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� MainFieldServer�� �ͼ� ���� ����, AFS -> MFS
#define T_FC_INFINITY_ENTER							(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_ENTER)			// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� �� ���� �㰡, F -> C
struct MSG_FtoA_INFINITY_START {
	UID32_t			AccountUID;
	UID32_t			MFSCharacterUID;
	ClientIndex_t	MFSClientIndex;
	UID32_t			AFSCharacterUID;
	ClientIndex_t	AFSClientIndex;
};
struct MSG_FtoA_INFINITY_START_OK {
	ClientIndex_t	AFSClientIndex;
	BOOL			bIsPCBangClient;
};
struct MSG_FC_INFINITY_ENTER {
	ChannelIndex_t	InfinityChannelIdx;
	D3DXVECTOR3		CharacterPosition;
	ATUM_DATE_TIME	StartTime;
	MSec_t			LimitTime;
};
struct MSG_FtoA_INFINITY_IMPUTE {
	InfiModeUID_t	InfinityModeUID;
	UID32_t			AccountUID;
	UID32_t			MFSCharacterUID;
	ClientIndex_t	MFSClientIndex;
	ClientIndex_t	AFSClientIndex;
	BOOL			CheckExistImpute;
};


#define T_FC_INFINITY_CINEMA						(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_CINEMA)			// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - �ó׸� ���� ����, F -> C
typedef CINEMAINFO	MSG_FC_INFINITY_CINEMA;

struct MSG_FN_NPCSERVER_CINEMA_MONSTER_CREATE		// 2010-03-31 by dhjin, ���Ǵ�Ƽ(�������) -
{
	MAP_CHANNEL_INDEX		mapChann;
	INT						MonsterUnitKind;
	SummonCnt_t				MonsterSummonCount;			// 2010-03-31 by dhjin, ���Ǵ�Ƽ(�������) -	
	Distance_t				MaxRandomDistance;			// 2010-03-31 by dhjin, ���Ǵ�Ƽ(�������) -
	MONSTER_BALANCE_DATA	MonsterBalanceInfo;			// 2010. 05. 19 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����. (��ȣó�� + ���� ó��(����) ) - ���� �뷱�� ����(Ȯ�� ���� ����).
};

// start 2011-04-28 by hskim, ���Ǵ�Ƽ 3�� - �ó׸� ���� ��� �߰� - �ش� ��ä�� Ư�� ���� ����/���� ��� �߰�
struct MSG_FN_NPCSERVER_CINEMA_MONSTER_DESTROY
{
	MAP_CHANNEL_INDEX		mapChann;
	INT						MonsterUnitKind;
};

struct MSG_FN_NPCSERVER_CINEMA_MONSTER_CHANGE
{
	MAP_CHANNEL_INDEX		mapChann;					// ä�� �� ��ȣ
	INT						MonsterUnitKind;			// ������ ���� ��ȣ
	INT						ChangeMonsterUnitKind;		// ����� ���� ��ȣ
};
// end 2011-04-28 by hskim, ���Ǵ�Ƽ 3�� - �ó׸� ���� ��� �߰� - �ش� ��ä�� Ư�� ���� ����/���� ��� �߰�

// start 2011-06-02 ���Ǵ�Ƽ 3�� - ���� 6 - �ֱ��� ��ȯ ��� ����
struct MSG_FN_NPCSERVER_CINEMA_MONSTER_REGEN
{
	MAP_CHANNEL_INDEX		mapChann;
	INT						iMonsterUnitKind;
	BOOL					bRegen;
	MONSTER_BALANCE_DATA	MonsterBalanceInfo;			// 2011-06-21 by hskim ���� �뷱�� ����
};
// end 2011-06-02 ���Ǵ�Ƽ 3�� - ���� 6 - �ֱ��� ��ȯ ��� ����

#define T_FC_INFINITY_SUCCESS_FIN					(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_SUCCESS_FIN)			// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ����, F -> C
#define T_FC_INFINITY_FAIL_FIN						(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_FAIL_FIN)			// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ����, F -> C
#define T_FC_INFINITY_FIN_OK						(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_FIN_OK)				// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� Ȯ�� �� ����(Main������ ���ư�), C -> F
#define T_FC_INFINITY_READY_FINISH_MAINSVR_START	(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_READY_FINISH_MAINSVR_START)	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - Main������ ���ư� �غ� �Ϸ� ��, F -> C

#define T_FtoA_INFINITY_UPDATE_ALL_ITEM_COUNT		(MessageType_t)((T0_MF_TO_AF<<8)|T1_FtoA_INFINITY_UPDATE_ALL_ITEM_COUNT)	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� MainFieldServer�� ������ ����ȭ ���� ����, AFS -> MFS
#define T_FtoA_INFINITY_INSERT_ITEM_HEADER			(MessageType_t)((T0_MF_TO_AF<<8)|T1_FtoA_INFINITY_INSERT_ITEM_HEADER)		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� MainFieldServer�� ������ ����ȭ ���� ����, AFS -> MFS
#define T_FtoA_INFINITY_INSERT_ITEM					(MessageType_t)((T0_MF_TO_AF<<8)|T1_FtoA_INFINITY_INSERT_ITEM)				// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� MainFieldServer�� ������ ����ȭ ���� ����, AFS -> MFS
#define T_FtoA_INFINITY_INSERT_ITEM_DONE			(MessageType_t)((T0_MF_TO_AF<<8)|T1_FtoA_INFINITY_INSERT_ITEM_DONE)			// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� MainFieldServer�� ������ ����ȭ ���� ����, AFS -> MFS
#define T_FtoA_INFINITY_UPDATE_ITEM_HEADER			(MessageType_t)((T0_MF_TO_AF<<8)|T1_FtoA_INFINITY_UPDATE_ITEM_HEADER)		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� MainFieldServer�� ������ ����ȭ ���� ����, AFS -> MFS
#define T_FtoA_INFINITY_UPDATE_ITEM					(MessageType_t)((T0_MF_TO_AF<<8)|T1_FtoA_INFINITY_UPDATE_ITEM)				// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� MainFieldServer�� ������ ����ȭ ���� ����, AFS -> MFS
#define T_FtoA_INFINITY_UPDATE_ITEM_DONE			(MessageType_t)((T0_MF_TO_AF<<8)|T1_FtoA_INFINITY_UPDATE_ITEM_DONE)			// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� MainFieldServer�� ������ ����ȭ ���� ����, AFS -> MFS
#define T_FtoA_INFINITY_DELETE_ITEM					(MessageType_t)((T0_MF_TO_AF<<8)|T1_FtoA_INFINITY_DELETE_ITEM)				// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� MainFieldServer�� ������ ����ȭ ���� ����, AFS -> MFS
#define T_FtoA_INFINITY_UPDATE_USER_INFO			(MessageType_t)((T0_MF_TO_AF<<8)|T1_FtoA_INFINITY_UPDATE_USER_INFO)			// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� MainFieldServer�� ���� ����ȭ ���� ����, AFS -> MFS
#define T_FtoA_INFINITY_READY_FINISH_MAINSVR_START  (MessageType_t)((T0_MF_TO_AF<<8)|T1_FtoA_INFINITY_READY_FINISH_MAINSVR_START)	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - Main������ ���ư� �غ� �Ϸ� ��, MFS -> AFS
#define T_FtoA_INFINITY_LOG							(MessageType_t)((T0_MF_TO_AF<<8)|T1_FtoA_INFINITY_LOG)						// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� MainFieldServer�� �α� ����, AFS -> MFS
#define T_FtoA_INFINITY_USING_TIME_LIMIT_ITEM		(MessageType_t)((T0_MF_TO_AF<<8)|T1_FtoA_USING_TIME_LIMIT_ITEM)				// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� MainFieldServer�� ������ ����ȭ ���� ����, AFS -> MFS
#define T_FtoA_INFINITY_COME_BACK_POSTWORK			(MessageType_t)((T0_MF_TO_AF<<8)|T1_FtoA_INFINITY_COME_BACK_POSTWORK)		// 2011-09-29 by hskim, ��Ʈ�� �ý��� 2�� - ���� MainFieldServer�� ���ư��� ���� �� �۾� ó�� ����, AFS -> MFS
#define T_FtoA_INFINITY_COME_BACK_PREWORK			(MessageType_t)((T0_MF_TO_AF<<8)|T1_FtoA_INFINITY_COME_BACK_PREWORK)		// 2011-09-29 by hskim, ��Ʈ�� �ý��� 2�� - ���� MainFieldServer�� ���ư��� ���� ���� �۾� ó�� ����, AFS -> MFS	
#define T_FtoA_INFINITY_UPDATE_ITEM_PET				(MessageType_t)((T0_MF_TO_AF<<8)|T1_FtoA_INFINITY_UPDATE_ITEM_PET)			// 2011-09-30 by hskim, ��Ʈ�� �ý��� 2�� - ���� MainFieldServer�� ��Ʈ�� ������ ����ȭ ���� ����, AFS -> MFS

struct MSG_FtoA_INFINITY_UPDATE_ALL_ITEM_COUNT {
	UID32_t			AccountUID;
	UID32_t			MFSCharacterUID;
	ClientIndex_t	MFSClientIndex;
	INT				AllItemCount;
};
struct MSG_FtoA_INFINITY_INSERT_ITEM {
	UID32_t			AccountUID;
	UID32_t			MFSCharacterUID;
	ClientIndex_t	MFSClientIndex;
	INT				ItemNum;
	INT				ItemWindowIndex;
	INT				CurrentCount;
	INT				PrefixCodeNum;
	INT				SuffixCodeNum;
	BYTE			Wear;
	INT				ShapeItemNum;
	INT				UsingTimeStamp;
	ATUM_DATE_TIME	CreatedTime;
	INT				CoolingTimeStamp;	// 2009-09-09 ~ 2010-02-10 by dhjin, ���Ǵ�Ƽ - �ߵ�������������
};
struct MSG_FtoA_INFINITY_UPDATE_ITEM {
	UID32_t			AccountUID;
	UID32_t			MFSCharacterUID;
	ClientIndex_t	MFSClientIndex;
	UID64_t			MainSvrItemUID;
	INT				ItemWindowIndex;
	INT				CurrentCount;
	BYTE			Wear;
	INT				UsingTimeStamp;
	INT				CoolingTimeStamp;	// 2009-09-09 ~ 2010-02-10 by dhjin, ���Ǵ�Ƽ - �ߵ�������������
};

// start 2011-09-30 by hskim, ��Ʈ�� �ý��� 2��
struct MSG_FtoA_INFINITY_UPDATE_ITEM_PET {
	UID32_t			AccountUID;
	UID32_t			MFSCharacterUID;
	ClientIndex_t	MFSClientIndex;
	UID64_t			MainSvrItemUID;

	struct tPET_CURRENTINFO	PetCurrentData;		// Arena -> Field �� ������ Field ���������� PetSocketItemUID �� pItemPetSocket �� �����ʹ� �������� �ʴ´�
};
// end 2011-09-30 by hskim, ��Ʈ�� �ý��� 2��

struct MSG_FtoA_INFINITY_DELETE_ITEM {
	//	INT InfinityDeleteItemInfoListCount;
	//	_ARRAY(INFINITY_DELETE_ITEM_INFO);
	UID32_t			AccountUID;
	UID32_t			MFSCharacterUID;
	ClientIndex_t	MFSClientIndex;
	UID64_t			MainSvrItemUID;
};
struct MSG_FtoA_INFINITY_UPDATE_USER_INFO {
	UID32_t				AccountUID;
	UID32_t				MFSCharacterUID;
	ClientIndex_t		MFSClientIndex;
	GEAR_STAT			GearStat;						// ��� ����
	BYTE				Level;							//
	Experience_t		Experience;						//
	Experience_t		DownExperience;					// ĳ���� ������ ������ ����ġ
	INT					DownSPIOnDeath;					// 2006-04-10 by cmkwon, ĳ���� ������ ������ SPI
	BYTE				BonusStat;						// �߰� 2002.12.13
	BYTE				BonusStatPoint;					// 2005-11-15 by cmkwon, �������� �ƴ� �ٸ�������� ���� ���ʽ� ���� ����Ʈ, BonusSkillPoint�� ������ // �߰� 2002.12.13
	LONGLONG			TotalPlayTime;					// �ʴ���
	ATUM_DATE_TIME		LevelUpTime;					// 2006-12-18 by dhjin, ������ �ð�
	INT					WarPoint;						// 2007-04-17 by dhjin, WP
	INT					CumulativeWarPoint;				// 2007-05-28 by dhjin, ����WP
	LONGLONG			PCBangTotalPlayTime;			// 2007-06-07 by dhjin, PC�� �� �÷��� �ð�, �ʴ���
	INT					SecretInfoOption;				// 2008-06-23 by dhjin, EP3 ���������ɼ� -
	MapIndex_t			InfinityMapIndex;				// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - �ñ� ���� ������ ó��
	ChannelIndex_t		InfinityChannelIndex;			// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - �ñ� ���� ������ ó��
};
struct MSG_FtoA_INFINITY_READY_FINISH_MAINSVR_START {
	ClientIndex_t	AFSClientIndex;
};

struct MSG_FtoA_INFINITY_LOG {
	UID32_t			AccountUID;
	UID32_t			MFSCharacterUID;
	ClientIndex_t	MFSClientIndex;
	ClientIndex_t	AFSClientIndex;
	InfiModeUID_t	InfinityModeUID;
	DeathCnt_t		DeathCount;
	KillCnt_t		KillCount;
	ATUM_DATE_TIME	StartTime;
	ATUM_DATE_TIME	EndTime;
	Experience_t	AllEXP;								// 2010-06-25 by shcho, ���Ǵ�Ƽ ���÷α� ��� - ����� �ִ� ����ġ �߰�
};

struct MSG_FtoA_INFINITY_USING_TIME_LIMIT_ITEM {
	UID32_t			AccountUID;
	UID32_t			MFSCharacterUID;
	ClientIndex_t	MFSClientIndex;
	INT				ItemNum;
	INT				ItemWindowIndex;
	INT				CurrentCount;
	BYTE			Wear;
	INT				ShapeItemNum;
	INT				UsingTimeStamp;
	ATUM_DATE_TIME	CreatedTime;
	UID64_t			MainSvrItemUID;
	INT				CoolingTimeStamp;			// 2009-09-09 ~ 2010-02-10 by dhjin, ���Ǵ�Ƽ - �ߵ�������������
};

// start 2011-09-29 by hskim, ��Ʈ�� �ý��� 2��
struct MSG_FtoA_INFINITY_COME_BACK_PREWORK
{
	UID32_t			AccountUID;
	UID32_t			MFSCharacterUID;
	ClientIndex_t	MFSClientIndex;
};
// end 2011-09-29 by hskim, ��Ʈ�� �ý��� 2��

// start 2012-01-16 by hskim, ��� - ȭ��
struct MSG_FtoA_INFINITY_COME_BACK_POSTWORK
{
	UID32_t			AccountUID;
	UID32_t			MFSCharacterUID;
	ClientIndex_t	MFSClientIndex;

	SSTATISTICS_MONEY_UNIT DeltaMoney;
};
// end 2012-01-16 by hskim, ��� - ȭ��

struct MSG_FN_NPCSERVER_NEW_CHANGE_OBJECT {
	MAP_CHANNEL_INDEX	mapChann;
	ObjectIdx_t			DeleteObjectUID;
	ObjectNum_t			NewObjectNum;
};
struct MSG_FN_NPCSERVER_RESET_CHANGE_OBJECT {
	MAP_CHANNEL_INDEX	mapChann;
};

#define T_FC_INFINITY_TENDER_DROPITEM_INFO		(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_TENDER_DROPITEM_INFO)	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���Ϳ��Լ� ����� Tender ������, F -> C
#define T_FC_INFINITY_TENDER_START				(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_TENDER_START)			// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - Tender ����, F -> C
#define T_FC_INFINITY_TENDER_PUT_IN_TENDER		(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_TENDER_PUT_IN_TENDER)	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� Tender ��ư ����, C -> F
#define T_FC_INFINITY_TENDER_PUT_IN_TENDER_OK	(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_TENDER_PUT_IN_TENDER_OK)	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� Tender ��ư ���� ���, F -> C
#define T_FC_INFINITY_TENDER_RESULT				(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_TENDER_RESULT)			// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ������ ���, F -> C
#define T_FC_INFINITY_TENDER_RESULT_TIMEOVER	(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_TENDER_TIMEOVER)			// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - Tender �ð��� �������� �����ڰ� ����, F -> C
#define T_FC_INFINITY_TENDER_RESULT_ALLGIVEUP	(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_TENDER_ALLGIVEUP)		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ������ ��� ����, F -> C
struct MSG_FC_INFINITY_TENDER_DROPITEM_INFO {
	UINT			ItemFieldIndex;			// ���� ������ ������ �ӽ÷� �����ϴ� ��ȣ
	ItemNum_t		TenderDropItemNum;
	INT				Count;
	INT				PrefixCodeNum;
	INT				SuffixCodeNum;
	ATUM_DATE_TIME	TenderStartTime;		// ���� ���� �ð�.
};
struct MSG_FC_INFINITY_TENDER_START {
	UINT			ItemFieldIndex;			// ���� ������ ������ �ӽ÷� �����ϴ� ��ȣ
	ItemNum_t		TenderItemNum;
	INT				Count;
};
struct MSG_FC_INFINITY_TENDER_PUT_IN_TENDER {
	ItemNum_t			TenderDropItemNum;	// 2010-06-25 by shcho, ���Ǵ�Ƽ ���÷α� ��� - �޼��� �߰�
	eINFINITY_MODE		InfinityMode;
	InfinityCreateUID_t	InfinityCreateUID;
	UINT				ItemFieldIndex;			// ���� ������ ������ �ӽ÷� �����ϴ� ��ȣ
	BOOL				GiveUp;
};
struct MSG_FC_INFINITY_TENDER_PUT_IN_TENDER_OK {
	UINT				ItemFieldIndex;			// ���� ������ ������ �ӽ÷� �����ϴ� ��ȣ
	ClientIndex_t		DiceUserIdx;			// ���� ����
	DiceCnt_t			DiceCount;				// �ֻ��� ��� ��.
};
struct MSG_FC_INFINITY_TENDER_RESULT {
	UINT				ItemFieldIndex;			// ���� ������ ������ �ӽ÷� �����ϴ� ��ȣ
	ClientIndex_t		DiceUserIdx;			// ���� ����
	DiceCnt_t			DiceCount;				// �ֻ��� ��� ��.
	ItemNum_t			TenderItemNum;
	INT					Count;
};
struct MSG_FC_INFINITY_TENDER_RESULT_TIMEOVER {
	UINT				ItemFieldIndex;			// ���� ������ ������ �ӽ÷� �����ϴ� ��ȣ
};
struct MSG_FC_INFINITY_TENDER_RESULT_ALLGIVEUP {
	UINT				ItemFieldIndex;			// ���� ������ ������ �ӽ÷� �����ϴ� ��ȣ
};

#define T_FC_INFO_APPLY_RESISTANCE_ITEM	(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_APPLY_RESISTANCE_ITEM)	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ������ ���� ���� ����, F -> C(n)
struct MSG_FC_INFO_APPLY_RESISTANCE_ITEM {
	ClientIndex_t		ResistanceUserIdx;
	ItemNum_t			SkillNum;			// 2009-09-09 ~ 2010-01-19 by dhjin, ���Ǵ�Ƽ - ���׵� ��ų ���� �߰�
	BOOL				OnceResistanceItem;	// 2009-09-09 ~ 2010-01-19 by dhjin, ���Ǵ�Ƽ - �� ���� �����ϰ� �������� ���� ������ �߰�
};

#define T_FC_SHOP_INFINITY_ITEM_HEADER		(MessageType_t)((T0_FC_SHOP<<8)|T1_FC_SHOP_INFINITY_ITEM_HEADER)	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ����
#define T_FC_SHOP_INFINITY_ITEM				(MessageType_t)((T0_FC_SHOP<<8)|T1_FC_SHOP_INFINITY_ITEM)			// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ����
#define T_FC_SHOP_INFINITY_ITEM_DONE		(MessageType_t)((T0_FC_SHOP<<8)|T1_FC_SHOP_INFINITY_ITEM_DONE)		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ����
typedef INFINITY_SHOP_INFO	MSG_FC_SHOP_INFINITY_ITEM;
#define T_FC_SHOP_INFINITY_BUY_ITEM			(MessageType_t)((T0_FC_SHOP<<8)|T1_FC_SHOP_INFINITY_BUY_ITEM)		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ����, ����
struct MSG_FC_SHOP_INFINITY_BUY_ITEM {
	InfinityShopUID_t		InfinityShopUID;
	int						Amount;
};

#define T_FC_INFINITY_CHANGE_LIMITTIME				(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_CHANGE_LIMITTIME)		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ����� �г�Ƽ �߰�, F -> C
struct MSG_FC_INFINITY_CHANGE_LIMITTIME {
	char			DeadCharactarName[SIZE_MAX_CHARACTER_NAME];		// 2009-09-09 ~ 2010-01-13 by dhjin, ���Ǵ�Ƽ - ���� ���� �̸� ���� ���� �߰�
	MSec_t			LimitTime;
};

// start 2011-05-30 by hskim, ���Ǵ�Ƽ 3�� - �÷��� �ð� �缳�� ��� 
#define T_FC_INFINITY_SET_LIMITTIME				(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_SET_LIMITTIME)		// 2011-05-30 by hskim, ���Ǵ�Ƽ 3�� - �÷��� �ð� �缳�� ���
struct MSG_FC_INFINITY_SET_LIMITTIME {
	MSec_t			LimitTime;		// ms
};
// end 2011-05-30 by hskim, ���Ǵ�Ƽ 3�� - �÷��� �ð� �缳�� ���

#define T_FC_INFINITY_JOIN_CANCEL							(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_JOIN_CANCEL)							// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���� ���
#define T_FC_INFINITY_JOIN_CANCEL_REQUEST_MASTERUSER		(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_JOIN_CANCEL_REQUEST_MASTERUSER)		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���� ���
struct MSG_FC_INFINITY_JOIN_CANCEL {
	eINFINITY_MODE		InfinityMode;
	InfinityCreateUID_t	InfinityCreateUID;
};
struct MSG_FC_INFINITY_JOIN_CANCEL_REQUEST_MASTERUSER {
	ClientIndex_t		JoinCancelClientIdx;
};

///////////////////////////////////////////////////////////////////////////////
// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - �ñ� ���� ������ ó��
#define T_FC_INFINITY_REQUEST_RESTART_BY_DISCONNECT					(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_REQUEST_RESTART_BY_DISCONNECT)			// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - �ñ� ���� ������ ó��, MFS -> C
#define T_FC_INFINITY_RESTART_BY_DISCONNECT							(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_RESTART_BY_DISCONNECT)					// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - �ñ� ���� ������ ó��, C -> AFS
#define T_FC_INFINITY_MAP_LOADED_RESTART_BY_DISCONNECT				(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_MAP_LOADED_RESTART_BY_DISCONNECT)		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - �ñ� ���� ������ ó��, C -> AFS
#define T_FC_INFINITY_DELETED_CINEMA_HEADER							(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_DELETED_CINEMA_HEADER)					// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - �ñ� ���� ������ ó��
#define T_FC_INFINITY_DELETED_CINEMA								(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_DELETED_CINEMA)							// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - �ñ� ���� ������ ó��
#define T_FC_INFINITY_DELETED_CINEMA_DONE							(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_DELETED_CINEMA_DONE)						// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - �ñ� ���� ������ ó��
#define T_FC_INFINITY_ENTER_BY_DISCONNECT							(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_ENTER_BY_DISCONNECT)						// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - �ñ� ���� ������ ó��
typedef CINEMAINFO	MSG_FC_INFINITY_DELETED_CINEMA;
struct MSG_FC_INFINITY_ENTER_BY_DISCONNECT {
	eINFINITY_MODE		InfinityMode;
	Minute_t			TimePenaltyValue;
	ChannelIndex_t		InfinityChannelIdx;
	D3DXVECTOR3			CharacterPosition;
	ATUM_DATE_TIME		StartTime;
	MSec_t				LimitTime;
	MSec_t				DecreaseTimeByDead;		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - �ñ� ���� ������ ó��
	InfinityCreateUID_t	InfinityCreateUID;	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - �ñ� ���� ������ ó��
	ClientIndex_t		MasterClientIdx;	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - �ñ� ���� ������ ó��
	Penalty_t			HPPenaltyValue;			// 2011-06-14 by hskim, ���Ǵ�Ƽ 3�� - �г�Ƽ ��� �߰� (HP �� �ð� ���� ������ ����)
};

#define T_FtoA_INFINITY_STATE_CHANGE			(MessageType_t)((T0_MF_TO_AF<<8)|T1_FtoA_INFINITY_STATE_CHANGE)		// 2009-09-09 ~ 2010-01-20 by dhjin, ���Ǵ�Ƽ - ���� ���� ���� ���μ����� �����Ѵ�.
struct MSG_FtoA_INFINITY_STATE_CHANGE {
	UID32_t			AccountUID;
	UID32_t			MFSCharacterUID;
	ClientIndex_t	MFSClientIndex;
	eINFINITY_STATE	AFSInfinityState;
	ClientIndex_t	AFSClientIndex;
};

// start 2011-05-17 by hskim, ���Ǵ�Ƽ 3�� - �ó׸� ����
#define T_FC_INFINITY_MOVIE						(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_MOVIE)				// 2011-05-17 by hskim, ���Ǵ�Ƽ 3�� - �ó׸� ����, F -> C

struct MSG_FC_INFINITY_MOVIE
{
	INT			UniqueNumber;			// ���� ��ȣ
	USHORT		Command;				// MOVIE_COMMAND_START, MOVIE_COMMAND_END
};
// end 2011-05-17 by hskim, ���Ǵ�Ƽ 3�� - �ó׸� ����

#define T_FI_PARTY_AUTO_CREATE						(MessageType_t)((T0_FI_PARTY<<8)|T1_FI_PARTY_AUTO_CREATE)					// 2009-09-09 ~ 2010-01-26 by dhjin, ���Ǵ�Ƽ - �ڵ� ���� ���� ��û, F -> I
#define T_FI_PARTY_AUTO_CREATE_OK					(MessageType_t)((T0_FI_PARTY<<8)|T1_FI_PARTY_AUTO_CREATE_OK)				// 2009-09-09 ~ 2010-01-26 by dhjin, ���Ǵ�Ƽ - �ڵ� ���� ���� �Ϸ�, I -> F
#define T_FC_PARTY_AUTO_CREATED						(MessageType_t)((T0_FC_PARTY<<8)|T1_FC_PARTY_AUTO_CREATED)					// 2009-09-09 ~ 2010-01-26 by dhjin, ���Ǵ�Ƽ - �ڵ� ���� ���� �Ϸ� �˸�, F -> C
#define T_IC_PARTY_GET_AUTO_PARTY_INFO				(MessageType_t)((T0_IC_PARTY<<8)|T1_IC_PARTY_GET_AUTO_PARTY_INFO)			// 2009-09-09 ~ 2010-01-26 by dhjin, ���Ǵ�Ƽ - �ڵ� ���� ���� ��û, C -> I
#define T_IC_PARTY_GET_AUTO_PARTY_INFO_OK			(MessageType_t)((T0_IC_PARTY<<8)|T1_IC_PARTY_GET_AUTO_PARTY_INFO_OK)		// 2009-09-09 ~ 2010-01-26 by dhjin, ���Ǵ�Ƽ - �ڵ� ���� ���� ����, I -> C
struct MSG_FI_PARTY_AUTO_CREATE {
	INT				PartyMemberListCount;
	UID32_t			MasterUID;
	_ARRAY(UID32_t);
};
struct MSG_FI_PARTY_AUTO_CREATE_OK {
	PartyID_t				PartyID;
	MEX_FIELD_PARTY_INFO	FieldPartyInfo;
	INT						PartyMemberListCount;
	UID32_t					MasterUID;
	_ARRAY(UID32_t);
};
struct MSG_FC_PARTY_AUTO_CREATED {
	PartyID_t				PartyID;
};
//////////////////////////////////////////////////////////////////////
// 2012-04-12 by jhseol, �Ʒ��� �߰����� - �ڵ���Ƽ : �ڵ����� ���� ��Ƽ�� ����.
struct MSG_FC_PARTY_AUTO_CREATED_THE_ARENA {
	SPARTY_INFO				PartyInfo;
};
// end 2012-04-12 by jhseol, �Ʒ��� �߰����� - �ڵ���Ƽ : �ڵ����� ���� ��Ƽ�� ����.

struct MSG_IC_PARTY_GET_AUTO_PARTY_INFO {
	PartyID_t				PartyID;
};
struct MSG_IC_PARTY_GET_AUTO_PARTY_INFO_OK {
	PartyID_t				PartyID;
	SPARTY_INFO				PartyInfo;
	UID32_t					MasterUniqueNumber;			// ��Ƽ���� CharacterUniqueNumber
	UINT					nNumOfPartyMembers;
	ARRAY_(IM_PARTY_MEMBER_INFO);
};

#define T_FI_PARTY_DISCONNECT_LEAVE_OK		(MessageType_t)((T0_FI_PARTY<<8)|T1_FI_PARTY_DISCONNECT_LEAVE_OK)	// 2009-09-09 ~ 2010-01-27 by dhjin, ���Ǵ�Ƽ - ���� ���� ���� ��Ƽ���� Ż��ó��!
typedef MSG_FI_PARTY_LEAVE_OK MSG_FI_PARTY_DISCONNECT_LEAVE_OK;

///////////////////////////////////////////////////////////////////////////////
// 2010-01-26 by cmkwon, ĳ�� ������ �����Ǹ� �ý��� ���� - 
typedef vector<ITEM_W_COUNT>				vectITEM_W_COUNT;
typedef mt_vector<ITEM_W_COUNT>				mtvectITEM_W_COUNT;

///////////////////////////////////////////////////////////////////////////////
// 2009-09-09 ~ 2010-02-10 by dhjin, ���Ǵ�Ƽ - �ߵ�������������
#define T_FC_ITEM_USE_INVOKING_WEAR_ITEM	(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_USE_INVOKING_WEAR_ITEM)	// 2009-09-09 ~ 2010-02-10 by dhjin, ���Ǵ�Ƽ - �ߵ������������� ���, C->F
struct MSG_FC_ITEM_USE_INVOKING_WEAR_ITEM {
	ItemUID_t				InvokingWearItemUID;
};

#define T_FC_ITEM_EXPIRE_TIME_INVOKING_WEAR_ITEM	(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_EXPIRE_TIME_INVOKING_WEAR_ITEM)	// C->F, 2009-09-09 ~ 2010-02-10 by dhjin, ���Ǵ�Ƽ - �ߵ������������� ���� �ð� �Ϸ�
struct MSG_FC_ITEM_EXPIRE_TIME_INVOKING_WEAR_ITEM {
	ItemUID_t				InvokingWearItemUID;
};

#define T_FC_INFO_APPLY_DESTPARAM		(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_APPLY_DESTPARAM)			// 2009-09-09 ~ 2010-02-10 by dhjin, ���Ǵ�Ƽ - �ߵ�������������, DestParam ���� ���� ���� ����
struct MSG_FC_INFO_APPLY_DESTPARAM {
	ClientIndex_t			ApplyClientIdx;
	DestParam_t				ApplyDestParam;
	EffectIdx_t				ApplyEffectIdx;
	ItemUID_t				ApplyItemUID;
};

#define T_FC_INFO_APPLY_DESTPARAM_LIST	(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_APPLY_DESTPARAM_LIST)			// 2009-09-09 ~ 2010-02-10 by dhjin, ���Ǵ�Ƽ - �ߵ�������������, DestParam ���� ���� ���� ����
struct APPLY_DESTPARAM_INFO {
	DestParam_t				ApplyDestParam;
	EffectIdx_t				ApplyEffectIdx;
};
struct MSG_FC_INFO_APPLY_DESTPARAM_LIST {
	ClientIndex_t			ApplyClientIdx;
	ItemUID_t				ApplyItemUID;
	UINT					ApplyDestParamCnt;
	ARRAY_(APPLY_DESTPARAM_INFO);
};

#define T_FC_ITEM_END_COOLINGTIME_ITEM		(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_END_COOLINGTIME_ITEM)	// 2009-09-09 ~ 2010-02-10 by dhjin, ���Ǵ�Ƽ - �ߵ�������������, ��Ÿ�� ���� C->F
struct MSG_FC_ITEM_END_COOLINGTIME_ITEM {
	ItemUID_t				ItemUID;
};

#define T_FC_ITEM_END_COOLINGTIME_ITEM_OK		(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_END_COOLINGTIME_ITEM_OK)	// 2009-09-09 ~ 2010-02-10 by dhjin, ���Ǵ�Ƽ - �ߵ�������������, ��Ÿ�� ���� F->C
struct MSG_FC_ITEM_END_COOLINGTIME_ITEM_OK {
	ItemUID_t				ItemUID;
};

#define T_FC_ITEM_GET_COOLINGTIME_INFO		(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_GET_COOLINGTIME_INFO)	// 2009-09-09 ~ 2010-02-10 by dhjin, ���Ǵ�Ƽ - �ߵ�������������, ��Ÿ�� ���� ��û C->F
#define T_FC_ITEM_GET_COOLINGTIME_INFO_OK	(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_GET_COOLINGTIME_INFO_OK)	// 2009-09-09 ~ 2010-02-10 by dhjin, ���Ǵ�Ƽ - �ߵ�������������, ��Ÿ�� ���� ��û F->C
struct MSG_FC_ITEM_GET_COOLINGTIME_INFO_OK {
	UID64_t			ItemUID;
	INT				CoolingTimeStamp;		// ���ݱ��� ���� �ð�(����:��)
};

#define T_FC_ITEM_USE_INVOKING_WEAR_ITEM_BUFF		(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_USE_INVOKING_WEAR_ITEM_BUFF)	// 2009-09-09 ~ 2010-02-10 by dhjin, ���Ǵ�Ƽ - �ߵ�������������, ���� �ø����� F->C
struct MSG_FC_ITEM_USE_INVOKING_WEAR_ITEM_BUFF {
	ItemUID_t				ItemUID;
};

///////////////////////////////////////////////////////////////////////////////
// 2010-03-31 by dhjin, ���Ǵ�Ƽ(�������) -
#define T_FC_INFINITY_CHANGE_ALIVE_FOR_GAMECLEAR_MONSTERHP			(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_CHANGE_ALIVE_FOR_GAMECLEAR_MONSTERHP)		// 2010-03-31 by dhjin, ���Ǵ�Ƽ(�������) - ���� ����� �г�Ƽ, F -> C
struct MSG_FC_INFINITY_CHANGE_ALIVE_FOR_GAMECLEAR_MONSTERHP {
	char			DeadCharactarName[SIZE_MAX_CHARACTER_NAME];
	MonIdx_t		MonsterNum;
	ClientIndex_t	MonsterIdx;
	float			CurrentHP;
};

#define T_FC_MONSTER_CREATED_ALIVE_FOR_GAMECLEAR					(MessageType_t)((T0_FC_MONSTER<<8)|T1_FC_MONSTER_CREATED_ALIVE_FOR_GAMECLEAR)		// 2010-03-31 by dhjin, ���Ǵ�Ƽ(�������) - F -> C
struct MSG_FC_MONSTER_CREATED_ALIVE_FOR_GAMECLEAR
{
	MonIdx_t		MonsterNum;
	ClientIndex_t	MonsterIdx;
	float			CurrentHP;

	// 2010. 06. 08 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����. (�Ʊ� ���� �뷱�� ����.) - MAX HP �߰�.
	float			MaxHP;
};


#define T_FC_ITEM_UPDATE_TRANSFORMER_OK				(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_UPDATE_TRANSFORMER_OK)	// F->C(n), // 2010-03-18 by cmkwon, ���ͺ��� ���� - 
struct MSG_FC_ITEM_UPDATE_TRANSFORMER_OK		// 2010-03-18 by cmkwon, ���ͺ��� ���� - 
{
	UID32_t			CharacUID;
	ClientIndex_t	ClientIdx;
	INT				MonsterUnitKind;
};

#define T_FI_PARTY_UPDATE_ITEM_TRANSFORMER_OK			(MessageType_t)((T0_FI_PARTY<<8)|T1_FI_PARTY_UPDATE_ITEM_TRANSFORMER_OK)	// F->I, // 2010-03-18 by cmkwon, ���ͺ��� ���� - 
typedef MSG_FC_ITEM_UPDATE_TRANSFORMER_OK	MSG_FI_PARTY_UPDATE_ITEM_TRANSFORMER_OK;	// 2010-03-18 by cmkwon, ���ͺ��� ���� - 

#define T_IC_PARTY_UPDATE_ITEM_TRANSFORMER_OK			(MessageType_t)((T0_IC_PARTY<<8)|T1_IC_PARTY_UPDATE_ITEM_TRANSFORMER_OK)	// I -> C(n), // 2010-03-18 by cmkwon, ���ͺ��� ���� - 
typedef MSG_FC_ITEM_UPDATE_TRANSFORMER_OK	MSG_IC_PARTY_UPDATE_ITEM_TRANSFORMER_OK;	// 2010-03-18 by cmkwon, ���ͺ��� ���� - 

///////////////////////////////////////////////////////////////////////////////
// 2010-03-23 by cmkwon, ���Ǵ�Ƽ ���� ĳ�� ������ ���� - 
#define T_FtoA_INFINITY_START_CHECK			(MessageType_t)((T0_MF_TO_AF<<8)|T1_FtoA_INFINITY_START_CHECK)		// AF->MF, // 2010-03-23 by cmkwon, ���Ǵ�Ƽ ���� ĳ�� ������ ���� - 
#define T_FtoA_INFINITY_START_CHECK_ACK		(MessageType_t)((T0_MF_TO_AF<<8)|T1_FtoA_INFINITY_START_CHECK_ACK)	// MF->AF, // 2010-03-23 by cmkwon, ���Ǵ�Ƽ ���� ĳ�� ������ ���� - 
struct MSG_FtoA_INFINITY_START_CHECK		// 2010-03-23 by cmkwon, ���Ǵ�Ƽ ���� ĳ�� ������ ���� - 
{
	UID32_t			AccountUID;
	UID32_t			MFSCharacterUID;
	ClientIndex_t	MFSClientIndex;
	ClientIndex_t	AFSClientIndex;
	BOOL			bCheckReentryTicket;	// 
	eINFINITY_MODE		InfinityMode;
	InfinityCreateUID_t	InfinityCreateUID;
};

struct MSG_FtoA_INFINITY_START_CHECK_ACK		// 2010-03-23 by cmkwon, ���Ǵ�Ƽ ���� ĳ�� ������ ���� - 
{
	Err_t			ErrorCode;
	UID32_t			AccountUID;
	ClientIndex_t	AFSClientIndex;
	eINFINITY_MODE		InfinityMode;
	InfinityCreateUID_t	InfinityCreateUID;
};

#define T_FN_BATTLE_ATTACK_SKILL_CANCEL					(MessageType_t)((T0_FN_BATTLE<<8)|T1_FN_BATTLE_ATTACK_SKILL_CANCEL)				// 2010-03-31 by dhjin, ���Ǵ�Ƽ(�������) - N -> F
struct MSG_FN_BATTLE_ATTACK_SKILL_CANCEL
{
	MAP_CHANNEL_INDEX	MapInfo;
	ClientIndex_t		MonsterIndex;
	INT					SkillItemNum;				// ��ų�� ItemNum
};

#define T_FC_MONSTER_SKILL_CANCEL							(MessageType_t)((T0_FC_MONSTER<<8)|T1_FC_MONSTER_SKILL_CANCEL)			// 2010-03-31 by dhjin, ���Ǵ�Ƽ(�������) - , F->C(n)
struct MSG_FC_MONSTER_SKILL_CANCEL {
	ClientIndex_t		MonsterIndex;
	INT					SkillItemNum;				// ��ų�� ItemNum
};

#define T_FtoA_UPDATE_ITEM_NOTI			(MessageType_t)((T0_MF_TO_AF<<8)|T1_FtoA_UPDATE_ITEM_NOTI)		//	MFS -> AFS // 2010-03-31 by dhjin, ���Ǵ�Ƽ ���� ĳ�� ������ ���� - 
struct MSG_FtoA_UPDATE_ITEM_NOTI {
	ClientIndex_t		AFSClientIdx;
	ItemNum_t			ItemNum;
};

#define T_FtoA_INFINITY_UPDATE_USER_MAP_INFO	(MessageType_t)((T0_MF_TO_AF<<8)|T1_FtoA_INFINITY_UPDATE_USER_MAP_INFO)	//	AFS -> MFS // 2010-04-06 by cmkwon, ����2�� �߰� ���� - 
struct MSG_FtoA_INFINITY_UPDATE_USER_MAP_INFO
{
	UID32_t				AccountUID;
	UID32_t				MFSCharacterUID;
	ClientIndex_t		MFSClientIndex;
	MapIndex_t			InfinityMapIndex;				// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - �ñ� ���� ������ ó��
	ChannelIndex_t		InfinityChannelIndex;			// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - �ñ� ���� ������ ó��
};


// 2010-05-04 by shcho, ���Ǵ�Ƽ ���̵� ���� start
//#define T_FC_INFINITY_DIFFICULTY_LIST		(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_DIFFICULTY_LIST) // C -> AFS // 2010-05-04 by shcho, ���̵� ���� ��� ��û
#define T_FC_INFINITY_DIFFICULTY_LIST_OK		(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_DIFFICULTY_LIST_OK) // AFS -> C // 2010-05-04 by shcho, Ŭ���̾�Ʈ ���̵� ���� ��� ��û�� ����
struct MSG_INFINITY_DIFFICULTY_LIST_OK
{
	int Difficulty_List_count; //����Ʈ�� �� ������ ����.
	_ARRAY(INFINITY_DIFFICULTY_BONUS_INFO);
};
// 2010-05-04 by shcho, ���Ǵ�Ƽ ���̵� ���� end


// 2010. 05. 19 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����. (��ȣó�� + ���� ó��(����) )
#define T_FC_INFINITY_CHANGE_DIFFICULTY_LEVEL		(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_CHANGE_DIFFICULTY_LEVEL)		// C -> AFS // 2010-05-24 by hsLee, ���̵� ���� ��û.
#define T_FC_INFINITY_CHANGE_DIFFICULTY_LEVEL_OK	(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_CHANGE_DIFFICULTY_LEVEL_OK)	// AFS -> C // 2010-05-24 by hsLee, ���̵� ���� ��û ���.

struct MSG_FC_INFINITY_CHANGE_DIFFICULTY_LEVEL
{
	INT	InfinityDifficultyLevel;
};

// 2010. 06. 01 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����. (����Ʈ �ڽ� �߰� + ���̵� ���� ��� ��Ŷ ����.)
struct MSG_FC_INFINITY_CHANGE_DIFFICULTY_LEVEL_OK
{
	BOOL bUpdate;									// Ŭ���̾�Ʈ �޽��� ó���� ���� Flag.
	INT InfinityDifficultyLevel;
};
// End 2010. 06. 01 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����. (����Ʈ �ڽ� �߰� + ���̵� ���� ��� ��Ŷ ����.)

// End 2010. 05. 19 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����. (��ȣó�� + ���� ó��(����) )

// 2010-06-01 by shcho, GLogDB ���� -
#define T_FL_LOG_EVENT_PARTICIPATION_RATE		(MessageType_t)((T0_FL_LOG<<8)|T1_FL_LOG_EVENT_PARTICIPATION_RATE)			// F -> L // 2010-06-01 by shcho, GLogDB ���� -
struct MSG_FL_LOG_EVENT_PARTICIPATION_RATE
{
	ATUM_DATE_TIME		StartTime;
	ATUM_DATE_TIME		EndTime;
	INT					ParticipationCount;
	USHORT				ParticipationRate;
	CHAR				Description[SIZE_MAX_GLOG_EVENT_DESCRIPTION];
};

// 2010-06-01 by shcho, PC�� ���� ȹ��(ĳ��) ������ - 
#define T_FC_ITEM_HOMEPREMIUM_INFO			(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_HOMEPREMIUM_INFO)	// F->C, // 2010-06-01 by shcho, PC�� ���� ȹ��(ĳ��) ������ -
struct MSG_FC_ITEM_HOMEPREMIUM_INFO
{
	BOOL bUse; // 0:FALSE  1:TRUE
};

///////////////////////////////////////////////////////////////////////////////////////
// start 2011-08-22 by hskim, ��Ʈ�� �ý��� 2�� - ��� ����
//
// ���� 
//
//
//#define T_FC_ITEM_PET_HEADER				(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_PET_HEADER)			// 2010-06-15 by shcho&hslee ��ý��� - Ŭ���̾�Ʈ ��Ŷ ���� Ŀ�ǵ� �߰� 
//#define T_FC_ITEM_PET						(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_PET)					// 2010-06-15 by shcho&hslee ��ý��� - Ŭ���̾�Ʈ ��Ŷ ���� Ŀ�ǵ� �߰� 
//#define T_FC_ITEM_PET_BASEDATA_OK			(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_PET_BASEDATA_OK)		// 2010-06-15 by shcho&hslee ��ý��� - Ŭ���̾�Ʈ ��Ŷ ���� Ŀ�ǵ� �߰� 
//#define T_FC_ITEM_PET_SKILLDATA_OK			(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_PET_SKILLDATA_OK)	// 2010-06-15 by shcho&hslee ��ý��� - Ŭ���̾�Ʈ ��Ŷ ���� Ŀ�ǵ� �߰� 
//#define T_FC_ITEM_PET_SOCKETDATA_OK			(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_PET_SOCKETDATA_OK)	// 2010-06-15 by shcho&hslee ��ý��� - Ŭ���̾�Ʈ ��Ŷ ���� Ŀ�ǵ� �߰� 
//#define T_FC_ITEM_PET_DONE					(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_PET_DONE)			// 2010-06-15 by shcho&hslee ��ý��� - Ŭ���̾�Ʈ ��Ŷ ���� Ŀ�ǵ� �߰� 
//
// 2010-06-15 by shcho&hslee ��ý��� - �� �⺻ ��ġ ���� ����ü
// struct MSG_FC_ITEM_PET_BASEDATA
// {
// 	BYTE			ItemUpdateType;										// ������ ���� Ÿ��, IUT_XXX
// 
// 	UID64_t			CreatedPetUID;
// 	
// 	BOOL			EnableEditPetName;
// 	BOOL			EnableLevelUp;
// 	
// 	char			szPetName[SIZE_MAX_PET_NAME];
// 	
// 	INT				PetIndex;
// 	INT				PetLevel;
// 	
// 	Experience_t	PetExp;
// 	
// 	FLOAT			Stamina;
// 	
// 	INT				SourceIndex_Field;
// 	INT				SourceIndex_City;
// 
// 	ItemNum_t		ItemIndex_PetSkill[SIZE_MAX_PETSKILLITEM];
// 	
// //	ITEM			sItem_PetSkill[SIZE_MAX_PETSKILLITEM];
// //	ITEM			sItem_PetSocketItem[SIZE_MAX_PETSOCKETITEM];
// };
// 
// 
// // 2010-06-15 by shcho&hslee ��ý��� - �� ��ų ���� ����ü
// struct MSG_FC_ITEM_PET_SKILLDATA
// {
// 	UID64_t			CreatePetUID;
// 
// 	INT				iSlotIndex;
// 
// 	ITEM			sItem_PetSkill;
// };
// 
// 
// // 2010-06-15 by shcho&hslee ��ý��� - �� ���� ���� ����ü
// struct MSG_FC_ITEM_PET_SOCKETDATA
// {
// 	UID64_t			CreatePetUID;
// 	
// 	INT				iSlotIndex;
// 	
// 	ITEM			sItem_PetSocket;
// };

/////////
// ����

#define T_FC_ITEM_PET_HEADER				(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_PET_HEADER)
#define T_FC_ITEM_PET						(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_PET)	
#define T_FC_ITEM_PET_BASEDATA_OK			(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_PET_BASEDATA_OK)
#define T_FC_ITEM_PET_DONE					(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_PET_DONE)

#define T_FC_ITEM_PET_SET_NAME				(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_PET_SET_NAME)
#define T_FC_ITEM_PET_SET_NAME_OK			(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_PET_SET_NAME_OK)
#define T_FC_ITEM_PET_SET_EXP_RATIO			(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_PET_SET_EXP_RATIO)
#define T_FC_ITEM_PET_SET_EXP_RATIO_OK		(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_PET_SET_EXP_RATIO_OK)
#define T_FC_ITEM_PET_CHANGE_LEVEL			(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_PET_CHANGE_LEVEL)
#define T_FC_ITEM_PET_CHANGE_EXP			(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_PET_CHANGE_EXP)

#define T_FC_ITEM_PET_SET_SOCKET			(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_PET_SET_SOCKET)
#define T_FC_ITEM_PET_SET_SOCKET_OK			(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_PET_SET_SOCKET_OK)
#define T_FC_ITEM_PET_SET_KIT_SLOT			(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_PET_SET_KIT_SLOT)
#define T_FC_ITEM_PET_SET_KIT_SLOT_OK		(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_PET_SET_KIT_SLOT_OK)
#define T_FC_ITEM_PET_SET_AUTOSKILL_SLOT	(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_PET_SET_KIT_AUTOSKILL_SLOT)
#define T_FC_ITEM_PET_SET_AUTOSKILL_SLOT_OK	(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_PET_SET_KIT_AUTOSKILL_SLOT_OK)

struct MSG_FC_ITEM_PET_BASEDATA
{
	BYTE			ItemUpdateType;										// ������ ���� Ÿ��, IUT_XXX
	UID64_t			CreatedPetUID;
	char			PetName[SIZE_MAX_PET_NAME];
	INT				PetIndex;
	INT				PetLevel;
	Experience_t	PetExp;
	BYTE			PetExpRatio;
	BYTE			PetEnableSocketCount;

	UID64_t			PetSocketItemUID[SIZE_MAX_PETSOCKET];

	SPET_KIT_SLOT_DATA			PetKitHP;
	SPET_KIT_SLOT_DATA			PetKitShield;
	SPET_KIT_SLOT_DATA			PetKitSP;

	SPET_AUTOSKILL_SLOT_DATA	PetAutoSkill;
};

// �̸� ����

struct MSG_FC_ITEM_PET_SET_NAME
{
	UID64_t			ItemUniqueNumber;					// ��Ʈ�� ������ UID
	char			PetName[SIZE_MAX_PET_NAME];			// ����� ��Ʈ�� �̸�
};

struct MSG_FC_ITEM_PET_SET_NAME_OK
{
	UID64_t			ItemUniqueNumber;					// ��Ʈ�� ������ UID
	char			PetName[SIZE_MAX_PET_NAME];			// ����� ��Ʈ�� �̸�
};

// ����ġ ȹ�� ���� ����

struct MSG_FC_ITEM_PET_SET_EXP_RATIO
{
	UID64_t			ItemUniqueNumber;					// ��Ʈ�� ������ UID
	BYTE			ExpRatio;							// ����ġ ȹ�� ����
};

struct MSG_FC_ITEM_PET_SET_EXP_RATIO_OK
{
	UID64_t			ItemUniqueNumber;					// ��Ʈ�� ������ UID
	BYTE			ExpRatio;							// ����ġ ȹ�� ����
};

// ����ġ ���� �� ���� ��

struct MSG_FC_ITEM_PET_CHANGE_LEVEL
{
	UID64_t			ItemUniqueNumber;					// ��Ʈ�� ������ UID
	BYTE			Level;								// ��Ʈ�� ���� ����
};

struct MSG_FC_ITEM_PET_CHANGE_EXP
{
	UID64_t			ItemUniqueNumber;					// ��Ʈ�� ������ UID
	Experience_t	Experience;							// �� ����ġ
};

// ���� ������ ����

struct MSG_FC_ITEM_PET_SET_SOCKET
{
	UID64_t			ItemUniqueNumber;					// ��Ʈ�� ������ UID
	INT				SocketIndex;						// ���� ��ȣ
	UID64_t			PetSocketItemUID;					// ���� ������ ����ũ ��ȣ
};

struct MSG_FC_ITEM_PET_SET_SOCKET_OK
{
	UID64_t			ItemUniqueNumber;					// ��Ʈ�� ������ UID
	INT				SocketIndex;						// ���� ��ȣ
	UID64_t			PetSocketItemUID;					// ���� ������ ����ũ ��ȣ
};

// ŰƮ ���� ����

struct MSG_FC_ITEM_PET_SET_KIT_SLOT
{
	UID64_t				ItemUniqueNumber;				// ��Ʈ�� ������ UID
	INT					SocketIndex;					// ���� ��ȣ
	UID64_t				PetSocketItemUID;				// ���� ������ UID
	SPET_KIT_SLOT_DATA	PetKitHP;						// HP ŰƮ ���� ����
	SPET_KIT_SLOT_DATA	PetKitShield;					// Shield ŰƮ ���� ����
	SPET_KIT_SLOT_DATA	PetKitSP;						// SP ŰƮ ���� ����
};

struct MSG_FC_ITEM_PET_SET_KIT_SLOT_OK
{
	UID64_t				ItemUniqueNumber;				// ��Ʈ�� ������ UID
	INT					SocketIndex;					// ���� ��ȣ
	UID64_t				PetSocketItemUID;				// ���� ������ UID
	SPET_KIT_SLOT_DATA	PetKitHP;						// HP ŰƮ ���� ����
	SPET_KIT_SLOT_DATA	PetKitShield;					// Shield ŰƮ ���� ����
	SPET_KIT_SLOT_DATA	PetKitSP;						// SP ŰƮ ���� ����
};

// ���� ��ų ���� ����

struct MSG_FC_ITEM_PET_SET_AUTOSKILL_SLOT
{
	UID64_t						ItemUniqueNumber;		// ��Ʈ�� ������ UID
	INT							SocketIndex;			// ���� ��ȣ
	UID64_t						PetSocketItemUID;		// ���� ������ UID
	SPET_AUTOSKILL_SLOT_DATA	PetAutoSkill;			// ���� ��ų ����
};

struct MSG_FC_ITEM_PET_SET_AUTOSKILL_SLOT_OK
{
	UID64_t						ItemUniqueNumber;		// ��Ʈ�� ������ UID
	INT							SocketIndex;			// ���� ��ȣ
	UID64_t						PetSocketItemUID;		// ���� ������ UID
	SPET_AUTOSKILL_SLOT_DATA	PetAutoSkill;			// ���� ��ų ����
};

// end 2011-08-22 by hskim, ��Ʈ�� �ý��� 2�� - ��� ����
///////////////////////////////////////////////////////////////////////////////////////

#define T_FC_INFINITY_SKIP_ENDING_CINEMA			(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_SKIP_ENDING_CINEMA)		// ���Ǵ�Ƽ ���� ��� ���� �ó׸� ���� ��ŵ ��û. 2010. 07. 27 by hsLee.
#define T_FC_INFINITY_SKIP_ENDING_CINEMA_OK			(MessageType_t)((T0_FC_INFINITY<<8)|T1_FC_INFINITY_SKIP_ENDING_CINEMA_OK)	// ���Ǵ�Ƽ ���� ��� ���� �ó׸� ���� ��ŵ ���. 2010. 07. 27 by hsLee.

struct MSG_FC_INFINITY_SKIP_ENDING					// ���Ǵ�Ƽ �ó׸� ���� ��ŵ ��Ŷ.
{
	InfinityCreateUID_t	InfinityCreateUID;			// ���Ǵ�Ƽ ��Ƽ UID.
	bool				bNormalEnding;				// ���� ���� ���� & ��ŵ ��û ���� ����.
};

struct MSG_FC_INFINITY_SKIP_ENDING_CINEMA_OK		// ���Ǵ�Ƽ �ó׸� ���� ��ŵ ��� ��Ŷ.
{
	BOOL			EnableSkip;								// ���� ��ŵ ���� ���� ����.
	BOOL			NormalEnding;							// ���� ���� ���� & ��ŵ ��û ���� ����.

	char			szCharName[SIZE_MAX_CHARACTER_NAME];	// ��ŵ�� ��� System Messageó���� ����� ��û�� ĳ���� �̸�.

	ATUM_DATE_TIME	sUpdateTenderItemStartTime;			// ���� �������� ���� ���� �ð� ���Ű�. (���� ��ŵ�� ����� �ð�).
};

// 2010-08-31 by shcho&jskim �����ۿ��� �ý��� - ���� �ý��� ��Ŷ ó��
#define T_FC_DISSOLVED_ITEM			(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_DISSOLUTIONITEM)		// client -> field
#define T_FC_DISSOLVED_ITEM_OK		(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_DISSOLUTIONITEM_OK)	// field  -> client

struct MSG_FC_DISSOLVED_ITEM // ���� �� ������ ���� ����ü client -> field
{
	UID64_t UniqueNumber;
	INT	Itemnum;
};

struct MSG_FC_DISSOLVED_SUCCESS_AND_FAILED // ���ص� ������ ó�� ���
{
	BOOL Item_Success;		// ���� ���� �Ǵ� ����
	BOOL Dissolved_success;
};
// END 2010-08-31 by shcho&jskim �����ۿ��� �ý��� - ���� �ý��� ��Ŷ ó��

// 2010-06-25 by shcho, ���Ǵ�Ƽ ���÷α� ��� - ���� ������ ���� DB����
#define T_FtoA_LOG_INFINITY_USER_GET_TENDERITEM		(MessageType_t)((T0_MF_TO_AF<<8)|T1_FtoA_LOG_INFINITYUSER_GET_TENDERITEM) // Field <- Arena

struct MSG_FtoA_INFINITY_TENDER_ITEM
{
	INT			TenderItemNum;		// ȹ���� ������ �ѹ�
	DiceCnt_t	GDicecount;			// ȹ���� �ֻ��� ī��Ʈ
	UID64_t		AccountUID;			// ���� UID
	CHAR		AccountName[SIZE_MAX_ACCOUNT_NAME];	// ���� �̸�
	UID64_t		CharacterUID;						// �ɸ��� UID
	CHAR		CharacterName[SIZE_MAX_CHARACTER_NAME];	// �ɸ��� �̸�
	INT			MFSClientIdx;

};
// END 2010-06-25 by shcho, ���Ǵ�Ƽ ���÷α� ��� - ���� ������ ���� DB����

///////////////////////////////////////////////////////////////////////////////
// 2011-01-26 by hskim, ���� ���� ����
#define T_PAUTH_CONNECT_LOGIN						(MessageType_t)((T0_PAUTH_CONNECT<<8)|T1_PAUTH_CONNECT_LOGIN)
#define T_PAUTH_CONNECT_LOGIN_OK					(MessageType_t)((T0_PAUTH_CONNECT<<8)|T1_PAUTH_CONNECT_LOGIN_OK)
#define T_PAUTH_CONNECT_LOGIN_FAIL					(MessageType_t)((T0_PAUTH_CONNECT<<8)|T1_PAUTH_CONNECT_LOGIN_FAIL)
#define T_PAUTH_CONNECT_LOGIN_SHUTDOWN				(MessageType_t)((T0_PAUTH_CONNECT<<8)|T1_PAUTH_CONNECT_LOGIN_SHUTDOWN)		// 2011-06-22 by hskim, �缳 ���� ����

struct SSERVER_AUTHENTICATION_ACCOUNT
{
	UINT64	UniqueNumber;
	char	szGameName[SIZE_MAX_AUTH_GAMENAME];
	char	szServerIP[SIZE_MAX_IPADDRESS];
	char	szServerNetmask[SIZE_MAX_IPADDRESS];
	char	szPublisher[SIZE_MAX_AUTH_PUBLISHER];
	int		iAllow;
	int		iShutdown;
	char	szResourceFileName[SIZE_MAX_AUTH_RESOURCE_FILE_NAME];
};

struct QPARAM_AUTHENTICATION_ACCOUNT
{
	BOOL	bResult;
	char	szGameName[SIZE_MAX_AUTH_GAMENAME];
	char	szServerPublicIP[SIZE_MAX_IPADDRESS];
	char	szServerPrivateIP[SIZE_MAX_IPADDRESS];
	char	szCurrentVer[SIZE_MAX_AUTH_CURRENTVER];
	int		nLanguageType;
	BYTE	byTestServer;
	USHORT	nServerPort;
	BYTE	byUseExternalAuthentication;
	int		nPreServerGroupCnts;
	int		nEnableGameServerGroupCnts;

	BOOL	bAccept;
	BOOL	bShutdown;
	char	szAcceptComment[SIZE_MAX_AUTH_ACCEPT_COMMENT];
	SSERVER_AUTHENTICATION_ACCOUNT AuthAccount;
};

///////////////////////////////////////////////////////////////////////////////
// 2011-06-22 by hskim, �缳 ���� ����

// start 2011-06-22 by hskim, �缳 ���� ����
#define T_IP_AUTHENTICATION_SHUTDOWN			(MessageType_t)((T0_IP_CONNECT<<8)|T1_IP_AUTHENTICATION_SHUTDOWN)	// PreServer �� Authentication ������ �������� �ʾҴٸ� ���� ����
#define T_FP_AUTHENTICATION_SHUTDOWN			(MessageType_t)((T0_FP_CONNECT<<8)|T1_FP_AUTHENTICATION_SHUTDOWN)	// PreServer �� Authentication ������ �������� �ʾҴٸ� ���� ����

struct MSG_IP_AUTHENTICATION_SHUTDOWN
{
	BOOL	bFlag;
};

struct MSG_FP_AUTHENTICATION_SHUTDOWN
{
	BOOL	bFlag;
};
// end 2011-06-22 by hskim, �缳 ���� ����

// 2012-07-11 by hskim, ������ �˴ٿ�
#define T_IP_SELECTIVE_SHUTDOWN_NOTICE	(MessageType_t)((T0_IP_CONNECT<<8)|T1_IP_SELECTIVE_SHUTDOWN_NOTICE)

#define T_IP_RELOAD_GUILD_INFO			(MessageType_t)((T0_IP_CONNECT<<8)|T1_IP_RELOAD_GUILD_INFO)		// 2014-02-11 by bckim, �����ʱ�ȭ�� ���� ����ȭó��

struct MSG_IP_SELECTIVE_SHUTDOWN_NOTICE
{
	UID32_t AccountUID;
	char m_szAccountName[SIZE_MAX_ACCOUNT_NAME];
	int nRemainingTime;
};
// end 2012-07-11 by hskim, ������ �˴ٿ�

// 2014-02-11 by bckim, �����ʱ�ȭ�� ���� ����ȭó��
struct MSG_IP_RELOAD_GUILD_INFO
{
	UID32_t	GuildUniqueNumber;				// ��� ������ȣ
	UID32_t	CharacterUniqueNumberDel;
};
typedef MSG_IP_RELOAD_GUILD_INFO	MSG_PA_RELOAD_GUILD_INFO;
// End.  2014-02-11 by bckim, �����ʱ�ȭ�� ���� ����ȭó��



// start 2011-11-03 by shcho, yedang �˴ٿ��� ���� - 
#define T_FC_SHUTDOWNMINS_USER_ALTER			(MessageType_t)((T0_FC_CONNECT<<8)|T1_FC_CONNECT_SHUTDOWNMINS_USER_ALTER)	// nobody
#define T_FC_SHUTDOWNMINS_USER_ENDGAME			(MessageType_t)((T0_FC_CONNECT<<8)|T1_FC_CONNECT_SHUTDOWNMINS_USER_ENDGAME)	// nobody

// end 2011-11-03 by shcho, yedang �˴ٿ��� ���� - 

// start 2011-10-18 by hskim, EP4 [Ʈ���� �ý���] - ȭ���� / �� ��ǳ
#define T_FC_TRIGGER_MAP_BUFF_SKILL				(MessageType_t)((T0_FC_TRIGGER<<8)|T1_FC_TRIGGER_MAP_BUFF_SKILL)

struct MSG_FC_TRIGGER_MAP_BUFF_SKILL
{
	ClientIndex_t		ClientIndex;				// Ŭ���̾�Ʈ �ε���
	INT					SkillItemNum;				// ��ų�� ItemNum
	INT					AddTime;					// ��ų ���� �ð��� �߰��Ǵ� �� (ms)
};
// end 2011-10-18 by hskim, EP4 [Ʈ���� �ý���] - ȭ���� / �� ��ǳ

// start 2011-10-28 by hskim, EP4 [Ʈ���� �ý���] - ũ����Ż �ý���
struct MSG_FC_OBJECT_CHANGE
{
	ObjectIdx_t			ObjectIdx;
	ObjectNum_t			ChangeObjectIdx;
};
typedef mt_vector<MSG_FC_OBJECT_CHANGE> mtvectObjectChange;

#define T_FC_SET_LIMITTIME						(MessageType_t)((T0_FC_TRIGGER<<8)|T1_FC_SET_LIMITTIME)

struct MSG_FC_SET_LIMITTIME
{
	MSec_t			LimitTime;		// ms
};

typedef mt_vector<UID32_t> mtvectCharacterUID;
// end 2011-10-28 by hskim, EP4 [Ʈ���� �ý���] - ũ����Ż �ý���


////////////////////////////////////////////////////////////////////////////
// 2012-10-05 by jhseol, NPlay pc�� ���
#define T_FP_PCBANG_USER_GAME_START				(MessageType_t)((T0_FP_CONNECT<<8)|T1_FP_PCBANG_USER_GAME_START)			// ���ӽ��� �˸�
#define T_FP_PCBANG_USER_GAME_END				(MessageType_t)((T0_FP_CONNECT<<8)|T1_FP_PCBANG_USER_GAME_END)				// �������� �˸�
#define T_FP_PCBANG_USER_PREMIUN_END			(MessageType_t)((T0_FP_CONNECT<<8)|T1_FP_PCBANG_USER_PREMIUN_END)			// PC�� �����̾� ���� ����
#define T_FP_PCBANG_USER_PREMIUM_INFO			(MessageType_t)((T0_FP_CONNECT<<8)|T1_FP_PCBANG_USER_PREMIUM_INFO)			// pc�� �����̾� ����
#define T_FP_PCBANG_USER_PREMIUM_REQUEST		(MessageType_t)((T0_FP_CONNECT<<8)|T1_FP_PCBANG_USER_PREMIUM_REQUEST)		// pc�� �����̾� ������û
#define T_FP_PCBANG_USER_PREMIUM_RESIDUAL_TIME	(MessageType_t)((T0_FP_CONNECT<<8)|T1_FP_PCBANG_USER_PREMIUM_RESIDUAL_TIME)	// pc�� �����̾� �ܿ��ð�

typedef struct
{
	char				AccountName[SIZE_MAX_ACCOUNT_NAME];			// ����� ���̵�
	char				ServerGroupName[SIZE_MAX_SERVER_NAME];		// ���� �׷� �̸�
	BOOL				PremiumApply;								// �����̾� ���� ���� ����
} MSG_FP_PCBANG_USER_GAME_START, MSG_FP_PCBANG_USER_GAME_END, MSG_FP_PCBANG_USER_PREMIUN_END, MSG_FP_PCBANG_USER_PREMIUM_INFO, MSG_FP_PCBANG_USER_PREMIUM_REQUEST;

typedef struct
{
	char				AccountName[SIZE_MAX_ACCOUNT_NAME];			// ����� ���̵�
	DWORD				ResidualTime;								// �����̾� ���� ���� ����
} MSG_FP_PCBANG_USER_PREMIUM_RESIDUAL_TIME;


#define T_FC_CHARACTER_PCBANG_PREMIUN_APPLY		(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_PCBANG_PREMIUN_APPLY)

typedef struct
{
	BOOL PremiumApply;								// �����̾� ���� ���� ����
	MSG_FC_INFO_GET_HAPPY_HOUR_EVENT_INFO_OK	msg;
} MSG_FC_CHARACTER_PCBANG_PREMIUN_APPLY;
// end 2012-10-05 by jhseol, NPlay pc�� ���

// 2012-10-17 by bhsohn XignCode�۾�
#define		XC_PACKET_SIZE		512

#define T_FC_CHARACTER_XIGNCODE_S_ACK_PACKET		(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_XIGNCODE_S_ACK_PACKET)
#define T_FC_CHARACTER_XIGNCODE_C_ACK_PACKET		(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_XIGNCODE_C_ACK_PACKET)
struct MSG_FC_CHARACTER_XIGNCODE_ACK_PACKET
{
	BYTE	byXigndAckMsg[XC_PACKET_SIZE + 1];
};

#define T_FC_CHARACTER_XIGNCODE_C_ACK_CODE		(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_XIGNCODE_C_ACK_CODE)

// start 2012-10-08 by khkim, GLog
#define GLOG_AC_LT_LOGIN						0x01	// 1 - �α���	
#define GLOG_AC_LT_LOGOUT						0x02	// 2 - �α׾ƿ� 

#define GLOG_CD_LT_GAMESTART					0x01	// 1 - ���� ����
#define GLOG_CD_LT_GAMEEND						0x02	// 2 - ���� ����
#define GLOG_CD_LT_CHARACTERCREATE				0x03	// 3 - ĳ���� ����
#define GLOG_CD_LT_CHARACTERDELETE				0x04	// 4 - ĳ���� ����
#define GLOG_CD_LT_CHARACTLEVELUP				0x05	// 5 - ������

#define GLOG_SL_LT_SERVERON						0x01	// 1 - ���� ON
#define GLOG_SL_LT_SERVEROFF					0x02	// 2 - ���� OFF

#define	GLOG_IL_LT_DROP							0x01	// 1 - ���
#define GLOG_IL_LT_QUEST						0x02	// 2 - ����Ʈ
#define GLOG_IL_LT_SHOP_BUY						0x03	// 3 - ����			(����)
#define GLOG_IL_LT_SHOP_SELL					0x04	// 4 - ����			(�Ǹ�)
#define GLOG_IL_LT_WARPOINTSHOP_BUY				0x05	// 5 - ��������		(����)
#define GLOG_IL_LT_INFINITYOBSHOP_BUY			0x06	// 6 - �������		(����)
#define GLOG_IL_LT_CASHSHOP_BUY					0x07	// 7 - ĳ������		(����)
#define GLOG_IL_LT_LUCKYMACHINE_GET				0x08	// 8 - ��Ű�ӽ�		(����)
#define GLOG_IL_LT_LUCKYMACHINE_USE				0x09	// 9 - ��Ű�ӽ�		(���)

#define GLOG_IL_LT_BAZAARBUY_GET				0x0A	// 10 - ���λ���BUY	(����)
#define GLOG_IL_LT_BAZAARBUY_GIVE				0x0B	// 11 - ���λ���BUY	(�ֱ�)
#define GLOG_IL_LT_BAZAARSELL_GET				0x0C	// 12 - ���λ���SELL(����)
#define GLOG_IL_LT_BAZAARSELL_GIVE				0x0D	// 13 - ���λ���SELL(�ֱ�)
#define GLOG_IL_LT_TREADGIVE					0x0E	// 14 - �ŷ�		(�ֱ�)
#define GLOG_IL_LT_TREADGET						0x0F	// 15 - �ŷ�		(����)
#define GLOG_IL_LT_THROWAWAY					0x10	// 16 - ������ 
#define GLOG_IL_LT_MIXING_GET					0x11	// 17 - ����		(����)
#define GLOG_IL_LT_MIXING_USE					0x12	// 18 - ����		(���)
#define GLOG_IL_LT_ENCHANT_UP					0x13	// 19 - ��þƮ		(����)
#define GLOG_IL_LT_ENCHANT_DWON					0x14	// 20 - ��þƮ		(����)
#define GLOG_IL_LT_ENCHANT_DESTROY				0x15	// 21 - ��þƮ		(�ı�)
#define GLOG_IL_LT_ENCHANT_BEGINNING			0x16    // 22 - ��þƮ		(�ʱ�ȭ) 
#define GLOG_IL_LT_ENCHANT_USEITEM				0x17	// 23 - ��þƮ�� ����� ������
#define GLOG_IL_LT_RANDOMBOX					0x18	// 24 - ĸ���� ������
#define GLOG_IL_LT_DISSOLUTION_GETITEM			0x19	// 25 - ����
#define GLOG_IL_LT_SKILL						0x1A	
#define GLOG_IL_LT_LOADING						0x1B
#define GLOG_IL_LT_AUCTION						0x1C
#define GLOG_IL_LT_USE_GETITEM					0x1D
#define GLOG_IL_LT_USE_USEITEM					0x1E
#define GLOG_IL_LT_MGAME_EVENT					0x1F
#define GLOG_IL_LT_USE_ENERGY					0x20
#define GLOG_IL_LT_EXPIRE_CARD_ITEM				0x21
#define GLOG_IL_LT_PENALTY_ON_DEAD				0x22
#define GLOG_IL_LT_PENALTY_AGEAR_FUEL_ALLIN		0x23
#define GLOG_IL_LT_INFLUENCEWAR_KILLER_BONUS	0x24
#define GLOG_IL_LT_BONUS_ITEM					0x25
#define GLOG_IL_LT_ADMIN						0x26
#define GLOG_IL_LT_GIVEEVENTITEM				0x27
#define GLOG_IL_LT_GUILD_STORE					0x28
#define GLOG_IL_LT_EXPIRE_ITEM					0x29
#define GLOG_IL_LT_STORE						0x2A
#define GLOG_IL_LT_STORE_FEE					0x2B
#define GLOG_IL_LT_ARENA_ITEM					0x2C
#define GLOG_IL_LT_TUTORIAL_PAY_ITEM			0x2D
#define GLOG_IL_LT_EXPEDIENCYFUND_PAYBACK		0x2E
#define GLOG_IL_LT_GIVEEVENTITEM_COUPONEVENT	0x2F
#define GLOG_IL_LT_LUCKY_ITEM					0x30
#define GLOG_IL_LT_WAR_CONTRIBUTION				0x31
#define GLOG_IL_LT_WAR_CONTRIBUTION_LEADER		0x32
#define GLOG_IL_LT_WAR_CONTRIBUTION_GUILD		0x33
#define GLOG_IL_LT_BULLET						0x34
#define GLOG_IL_LT_DISSOLUTION_USEITEM			0x35
#define GLOG_IL_LT_DEPENDENCY_ITEM				0x36
#define GLOG_IL_LT_WARP							0x37
#define GLOG_IL_LT_CITYWAR_BRING_SUMOFTEX		0x38
#define GLOG_IL_LT_MARKET						0x39	// 2013-11-25 by jhseol&bckim, �ŷ��� - GLog �߰�



// 2014-03-20 by bckim, �ŷ��� GLOG �߰� 
#define GLOG_IL_LT_MARKET_SELLING_SPI			0x41		//	65
#define GLOG_IL_LT_MARKET_BUYING_SPI			0x42		//	66
#define GLOG_IL_LT_MARKET_SELLING_WP			0x43		//	67
#define GLOG_IL_LT_MARKET_BUYING_WP				0x44		//	68
// End. 2014-03-20 by bckim, �ŷ��� GLOG �߰� 
#define GLOG_IL_LT_WARPOINT_ADD					0x45 // 2014-03-20 by jekim, GLog �������
#define GLOG_IL_LT_WARPOINT_DEL					0x46 // 2014-03-20 by jekim, GLog �������


#define GLOG_ISL_GAMESTART						0x01	// 1 - ���� ����
#define GLOG_ISL_CHARACTLEVELUP					0x02	// 2 - ������
// end 2012-10-08 by khkim, GLog

struct MSG_FC_CHARACTER_XIGNCODE_C_ACK_CODE
{
	ULONG Code;
};
// END 2012-10-17 by bhsohn XignCode�۾�

////////////////////////////////////////////////////////////////////////////
// 2012-11-13 by jhseol, ���� �ý��� ������ - ������
struct MSG_PA_ADMIN_STRATRGYPOINT_INFO_CHANGE
{
	char DBName[20];
};
typedef MSG_PA_ADMIN_STRATRGYPOINT_INFO_CHANGE	MSG_FP_ADMIN_STRATRGYPOINT_INFO_CHANGE;
// end 2012-11-13 by jhseol, ���� �ý��� ������ - ������

#define TIMESECOND_USER_NOTICE_MSG_SEND_TIC		3	// 2013-01-21 by jhseol, NGC �������� Ʈ���� �ý��� - ���� �˸� MSG ������ �ֱ� �ð� 3��

// 2013-04-18 by jhseol,bckim �̴��� �Ƹ� - �̴��� �Ƹ� ���� ���� ���� ��Ŷ
typedef struct
{
	UID64_t			ItemUID;			// ������ UID
	ItemNum_t		nOptionItemNum;		// �ɼ� ������
	ATUM_DATE_TIME	atEndDate;			// �̺�Ʈ ���� �Ⱓ
} MSG_FC_STORE_UPDATE_ARMOR_ITEM_EVENT_INFO;

#define T_FC_COLLECTION_MONTHLY_AROMOR_EVENT_INIT	(MessageType_t)((T0_FC_COLLECTION<<8)|T1_FC_COLLECTION_MONTHLY_AROMOR_EVENT_INIT)	// F->C, // �÷��ǿ� ǥ���� �̴��ǾƸ� �̺�Ʈ ���� �ʱ�ȭ ��Ŷ
#define T_FC_COLLECTION_MONTHLY_AROMOR_EVENT_INFO	(MessageType_t)((T0_FC_COLLECTION<<8)|T1_FC_COLLECTION_MONTHLY_AROMOR_EVENT_INFO)	// F->C, // �÷��ǿ� ǥ���� �̴��ǾƸ� �̺�Ʈ ���� ��Ŷ

typedef struct
{
	ItemNum_t		CollectionShapeNum;			// ���� ��ȣ
	ItemNum_t		nOptionItemNum;				// �ɼ� ������
	ATUM_DATE_TIME	atEndDate;					// �̺�Ʈ ���� �Ⱓ
} MSG_FC_COLLECTION_MONTHLY_AROMOR_EVENT_INFO;
// end 2013-04-18 by jhseol,bckim �̴��� �Ƹ� - �̴��� �Ƹ� ���� ���� ���� ��Ŷ

// 2013-05-31 by jhseol,bckim �Ƹ� �÷��� - ��Ŷ �߰� : �޼���
// ��Ŷ ����κ�
#define T_FC_COLLECTION_INFO					(MessageType_t)((T0_FC_COLLECTION<<8)|T1_FC_COLLECTION_INFO)			// F->C, // �÷��� ���� ��Ŷ
#define T_FC_COLLECTION_SHAPE_CHANGE			(MessageType_t)((T0_FC_COLLECTION<<8)|T1_FC_COLLECTION_SHAPE_CHANGE)	// C->F, // ���� ���� ��û ��Ŷ

// MSG ����κ�
typedef COLLECTION_INFO							MSG_FC_COLLECTION_INFO;				// �÷��� ���� ��Ŷ
typedef COLLECTION_SHAPE_CHANGE					MSG_FC_COLLECTION_SHAPE_CHANGE;		// ���� ���� ��û ��Ŷ

#define GAMELOG_COLLECTION_STATE_ADD			1	// �÷��� ���
#define GAMELOG_COLLECTION_STATE_ENCHANT		2	// �÷��� ��þƮ
#define GAMELOG_COLLECTION_STATE_TIME_START		3	// �÷��� ����(���):Ÿ�̸� ON
#define GAMELOG_COLLECTION_STATE_TIME_END		4	// �÷��� ����(�������):Ÿ�̸� OFF
#define GAMELOG_COLLECTION_STATE_MONTHLY_EVENT	5	// 2013-09-06 by jhseol, �̴��� �Ƹ� �̺�Ʈ ���� �Ⱓ ���� - �̴��� �Ƹ� �̺�Ʈ���� ����	
struct MSG_FL_LOG_COLLECTION_STATE
{
	BYTE				CollectionState;
	COLLECTION_INFO		CollectionInfo;

	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		sprintf(o_szLogString, "%s|%d|%d|%d|%d|%d(%d)|%d|%d(%s)|%d(%s)\r\n", GetGameLogTypeString(i_nLogType), CollectionInfo.CollectionType, CollectionState, CollectionInfo.AccountUID, CollectionInfo.CharacterUID
			, CollectionInfo.ShapeNum, CollectionInfo.ShapeItemNum, CollectionInfo.EnchantLevel, CollectionInfo.RemainSeconds, CollectionInfo.EndTime.GetDateTimeString(STRNBUF(SIZE_MAX_SQL_DATETIME_STRING))
			, CollectionInfo.nOptionItemNum, CollectionInfo.DurationTime.GetDateTimeString(STRNBUF(SIZE_MAX_SQL_DATETIME_STRING)));	// 2013-09-06 by jhseol, �̴��� �Ƹ� �̺�Ʈ ���� �Ⱓ ����
		return o_szLogString;
	}
};

struct MSG_FL_LOG_COLLECTION_SHAPE_CHANGE
{
	BYTE				CollectionType;
	UID32_t				AccountUID;
	UID32_t				CharacterUID;
	UID64_t				ItemUID;
	ItemNum_t			BeforeShapeNum;
	ItemNum_t			AfterShapeNum;

	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		sprintf(o_szLogString, "%s|%d|%d|%d|%I64d|%d->%d\r\n", GetGameLogTypeString(i_nLogType), CollectionType, AccountUID, CharacterUID, ItemUID, BeforeShapeNum, AfterShapeNum);
		return o_szLogString;
	}
};
// end 2013-05-31 by jhseol,bckim �Ƹ� �÷��� - ��Ŷ �߰� : �޼���

// 2013-07-26 by jhseol, Ÿ ���� ���º��� - GameLog �߰�
struct MSG_FL_LOG_ACCOUNT_INFL_CHANGE_BY_ADMIN
{
	UID32_t				AccountUID;
	UID32_t				CharacterUID;
	BYTE				BeforeInfl;
	BYTE				AfterInfl;
	UID32_t				AdminCharacterUID;

	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		sprintf(o_szLogString, "%s|%d|%d|%d->%d|%d\r\n", GetGameLogTypeString(i_nLogType), AccountUID, CharacterUID, BeforeInfl, AfterInfl, AdminCharacterUID);
		return o_szLogString;
	}
};
// end 2013-07-26 by jhseol, Ÿ ���� ���º��� - GameLog �߰�

// 2013-08-14 by jhseol, ������ ������ - NGC ����
#define T_FC_INFO_NGCSPWAR_DISPLAY	(MessageType_t)((T0_FC_INFO<<8)|T1_FC_INFO_NGCSPWAR_DISPLAY)			// 2013-08-14 by jhseol, ������ ������ - NGC ����
enum NGCSP_STATE
{
	NGCSP_START = 0,
	NGCSP_PLAYING,
	NGCSP_FINISHED
};
struct MSG_NGCSPWAR_DISPLAY
{// 2008-03-26 by dhjin, ���� ���� ǥ�� ��ȹ�� - �������� �ʿ��� ���� ǥ�� ����Ÿ
	MapIndex_t		MapIndex;
	INT				HPRate;					// ���� HP���� ��з�
	BYTE			BCUContributePercent;	// BCU������ �⿩�� 100-BCUContributePercent �ϸ� ANI������ �⿩��
	BYTE			State;					// NGC������ ����
	ATUM_DATE_TIME	StartTime;				// ���� �����ð�, �ش� �ð� ���� 1�ð����� ������ ����
};
// end 2013-08-14 by jhseol, ������ ������ - NGC ����

#if _KILL_FEED
	#define T1_FC_CHARACTER_DEAD_NOTIFY_MAP		0xA5    // send killmessage to all players on same map
	#define T_FC_CHARACTER_DEAD_NOTIFY_MAP		(MessageType_t)((T0_FC_CHARACTER<<8)|T1_FC_CHARACTER_DEAD_NOTIFY_MAP)

	#define SIZE_MAX_CHARACTER_RAT				30 // default 20

	struct MSG_FC_CHARACTER_DEAD_NOTIFY_MAP
	{
		MAP_CHANNEL_INDEX MapChannel;
		BYTE DamageType;

		char PlayerName[SIZE_MAX_CHARACTER_RAT];
		BYTE PlayerInfluence;

		char EnemyName[SIZE_MAX_CHARACTER_RAT];
		BYTE EnemyInfluence;

#if _KILL_STREAK
		int KillStreak;
#endif

	};
#endif

// 2013-11-25 by jhseol&bckim, �ŷ��� - ��Ŷ �߰�
/////////////////////////////////////////////////////////////////////////////////////////////
// T0_FC_MARKET
#define T1_FC_MARKET_BASE_INFO_REQUEST					0x00	// �ʱ����� ��û
#define T1_FC_MARKET_BASE_INFO_HEADER					0x01	// �ʱ����� �ش�
#define T1_FC_MARKET_BASE_INFO_OK						0x02	// �ʱ����� ������
#define T1_FC_MARKET_BASE_INFO_DONE						0x03	// �ʱ����� �Ϸ�
#define T1_FC_MARKET_SEARCH_REQUEST						0x04	// �˻� ��û
#define T1_FC_MARKET_SEARCH_HEADER						0x05	// �˻� �ش�
#define T1_FC_MARKET_SEARCH_OK							0x06	// �˻� ������
#define T1_FC_MARKET_SEARCH_DONE						0x07	// �˻� �Ϸ�
#define T1_FC_MARKET_PAGING_REQUEST						0x08	// ���������� ��û
#define T1_FC_MARKET_PAGING_HEADER						0x09	// ���������� �ش�
#define T1_FC_MARKET_PAGING_OK							0x0A	// ���������� ������
#define T1_FC_MARKET_PAGING_DONE						0x0B	// ���������� �Ϸ�
#define T1_FC_MARKET_SORT_REQUEST						0x0C	// ���� ��û
#define T1_FC_MARKET_SORT_HEADER						0x0D	// ���� �ش�
#define T1_FC_MARKET_SORT_OK							0x0E	// ���� ������
#define T1_FC_MARKET_SORT_DONE							0x0F	// ���� �Ϸ�
#define T1_FC_MARKET_SELL_REQUEST						0x10	// ������ ��� ��û
#define T1_FC_MARKET_SELL_OK							0x11	// ������ ��� �Ϸ�
#define T1_FC_MARKET_BUY_REQUEST						0x12	// ������ ���� ��û
#define T1_FC_MARKET_BUY_OK								0x13	// ������ ���� �Ϸ�
#define T1_FC_MARKET_GET_REQUEST						0x14	// ������ ȸ�� ��û
#define T1_FC_MARKET_GET_OK								0x15	// ������ ȸ�� �Ϸ�
#define T1_FC_MARKET_MY_LIST_REQUEST					0x16	// �Ǹ���Ȳ ��û
#define T1_FC_MARKET_MY_LIST_HEADER						0x17	// �Ǹ���Ȳ �ش�
#define T1_FC_MARKET_MY_LIST_OK							0x18	// �Ǹ���Ȳ ������
#define T1_FC_MARKET_MY_LIST_DONE						0x19	// �Ǹ���Ȳ �Ϸ�

#define T_FC_MARKET_BASE_INFO_REQUEST	(MessageType_t)((T0_FC_MARKET<<8)|T1_FC_MARKET_BASE_INFO_REQUEST)	// C->F // �ʱ����� ��û
#define T_FC_MARKET_BASE_INFO_HEADER	(MessageType_t)((T0_FC_MARKET<<8)|T1_FC_MARKET_BASE_INFO_HEADER)	// F->C // �ʱ����� �ش�
#define T_FC_MARKET_BASE_INFO_OK		(MessageType_t)((T0_FC_MARKET<<8)|T1_FC_MARKET_BASE_INFO_OK)		// F->C // �ʱ����� ������
#define T_FC_MARKET_BASE_INFO_DONE		(MessageType_t)((T0_FC_MARKET<<8)|T1_FC_MARKET_BASE_INFO_DONE)		// F->C // �ʱ����� �Ϸ�
#define T_FC_MARKET_SEARCH_REQUEST		(MessageType_t)((T0_FC_MARKET<<8)|T1_FC_MARKET_SEARCH_REQUEST)		// C->F // �˻� ��û
#define T_FC_MARKET_SEARCH_HEADER		(MessageType_t)((T0_FC_MARKET<<8)|T1_FC_MARKET_SEARCH_HEADER)		// F->C // �˻� �ش�
#define T_FC_MARKET_SEARCH_OK			(MessageType_t)((T0_FC_MARKET<<8)|T1_FC_MARKET_SEARCH_OK)			// F->C // �˻� ������
#define T_FC_MARKET_SEARCH_DONE			(MessageType_t)((T0_FC_MARKET<<8)|T1_FC_MARKET_SEARCH_DONE)			// F->C // �˻� �Ϸ�
#define T_FC_MARKET_PAGING_REQUEST		(MessageType_t)((T0_FC_MARKET<<8)|T1_FC_MARKET_PAGING_REQUEST)		// C->F // ���������� ��û
#define T_FC_MARKET_PAGING_HEADER		(MessageType_t)((T0_FC_MARKET<<8)|T1_FC_MARKET_PAGING_HEADER)		// F->C // ���������� �ش�
#define T_FC_MARKET_PAGING_OK			(MessageType_t)((T0_FC_MARKET<<8)|T1_FC_MARKET_PAGING_OK)			// F->C // ���������� ������
#define T_FC_MARKET_PAGING_DONE			(MessageType_t)((T0_FC_MARKET<<8)|T1_FC_MARKET_PAGING_DONE)			// F->C // ���������� �Ϸ�
#define T_FC_MARKET_SORT_REQUEST		(MessageType_t)((T0_FC_MARKET<<8)|T1_FC_MARKET_SORT_REQUEST)		// C->F // ���� ��û
#define T_FC_MARKET_SORT_HEADER			(MessageType_t)((T0_FC_MARKET<<8)|T1_FC_MARKET_SORT_HEADER)			// F->C // ���� �ش�
#define T_FC_MARKET_SORT_OK				(MessageType_t)((T0_FC_MARKET<<8)|T1_FC_MARKET_SORT_OK)				// F->C // ���� ������
#define T_FC_MARKET_SORT_DONE			(MessageType_t)((T0_FC_MARKET<<8)|T1_FC_MARKET_SORT_DONE)			// F->C // ���� �Ϸ�
#define T_FC_MARKET_SELL_REQUEST		(MessageType_t)((T0_FC_MARKET<<8)|T1_FC_MARKET_SELL_REQUEST)		// C->F // ������ ��� ��û
#define T_FC_MARKET_SELL_OK				(MessageType_t)((T0_FC_MARKET<<8)|T1_FC_MARKET_SELL_OK)				// F->C // ������ ��� �Ϸ�
#define T_FC_MARKET_BUY_REQUEST			(MessageType_t)((T0_FC_MARKET<<8)|T1_FC_MARKET_BUY_REQUEST)			// C->F // ������ ���� ��û
#define T_FC_MARKET_BUY_OK				(MessageType_t)((T0_FC_MARKET<<8)|T1_FC_MARKET_BUY_OK)				// F->C // ������ ���� �Ϸ�
#define T_FC_MARKET_GET_REQUEST			(MessageType_t)((T0_FC_MARKET<<8)|T1_FC_MARKET_GET_REQUEST)			// C->F // ������ ȸ�� ��û
#define T_FC_MARKET_GET_OK				(MessageType_t)((T0_FC_MARKET<<8)|T1_FC_MARKET_GET_OK)				// F->C // ������ ȸ�� �Ϸ�
#define T_FC_MARKET_MY_LIST_REQUEST		(MessageType_t)((T0_FC_MARKET<<8)|T1_FC_MARKET_MY_LIST_REQUEST)		// C->F // �Ǹ���Ȳ ��û
#define T_FC_MARKET_MY_LIST_HEADER		(MessageType_t)((T0_FC_MARKET<<8)|T1_FC_MARKET_MY_LIST_HEADER)		// F->C // �Ǹ���Ȳ �ش�
#define T_FC_MARKET_MY_LIST_OK			(MessageType_t)((T0_FC_MARKET<<8)|T1_FC_MARKET_MY_LIST_OK)			// F->C // �Ǹ���Ȳ ������
#define T_FC_MARKET_MY_LIST_DONE		(MessageType_t)((T0_FC_MARKET<<8)|T1_FC_MARKET_MY_LIST_DONE)		// F->C // �Ǹ���Ȳ �Ϸ�

struct MSG_FC_MARKET_SEARCH_REQUEST // �˻� ��û ��Ŷ
{
	BYTE			Kind;				// ������ ����(�⺻�� 0) 0=��ü
	BYTE			LevelMin;			// ����(�⺻�� 0)
	BYTE			LevelMax;			// ����(�⺻�� 0)
	BYTE			EnchantMin;			// ��þƮ(�⺻�� 0)
	BYTE			EnchantMax;			// ��þƮ(�⺻�� 0)
	USHORT			ItemGear;			// ��밡�� ���(�⺻�� 0)
	BYTE			MoneyType;			// ȭ�� Ÿ��(0=SPI, 1=WP)
	char			Name[MARKET_ITEM_FULL_NAME];	// ������ �̸�(����, ���� ����)
};

struct MSG_FC_MARKET_PAGING_REQUEST // ������ ���� ��Ŷ
{
	UID64_t			MarketUID;			// ���ܽ�ų ��ȣ(������ 0)
	int				SelectPage;			// ������ ������
};

struct MSG_FC_MARKET_SORT_REQUEST // ���� ��û ��Ŷ
{
	BYTE			SortingType;		// ���� ����
};

typedef struct
{
	INT nSellingTime;
} MSG_FC_MARKET_BASE_INFO_HEAD;

typedef struct // �ʱ�ȭ, �˻�, ����¡, ����, �Ǹ���Ȳ ����Ʈ ��Ŷ
{
	MARKET_INFO MarketInfo;
} MSG_FC_MARKET_BASE_INFO_OK, MSG_FC_MARKET_SEARCH_OK, MSG_FC_MARKET_PAGING_OK, MSG_FC_MARKET_SORT_OK, MSG_FC_MARKET_MY_LIST_OK;

typedef struct // �ʱ�ȭ, �˻�, ����¡, ���� �Ϸ� ��Ŷ���� �ش� ����� ���� ��ü �������� ���� �������� ����
{
	int				ItemCount;			// �˻��� �������� ��
	int				MaxPage;			// ��ü ������ (�������� 0�̸� �˻������ ���ٴ� �ǹ�)
	int				CurrentPage;		// �������� ������
} MSG_FC_MARKET_BASE_INFO_DONE, MSG_FC_MARKET_SEARCH_DONE, MSG_FC_MARKET_PAGING_DONE, MSG_FC_MARKET_SORT_DONE;

typedef struct					// �Ǹ���Ȳ �Ϸ� ��Ŷ , ������Ȳ 
{
	BYTE			MyListItemCount;		// �������� ��
}MSG_FC_MARKET_MY_LIST_DONE, MSG_FC_DESTROY_AUCTION_MY_LIST_DONE;

struct MSG_FC_MARKET_SELL_REQUEST // ��ǰ ��� ��û ��Ŷ
{
	UID64_t			ItemUID;			// ������ ������ȣ
	BYTE			MoneyType;			// ȭ�� Ÿ��(0=SPI, 1=WP)
	INT				Price;				// �Ǹűݾ�
	INT				Count;				// �Ǹż���
	char			Name[MARKET_ITEM_FULL_NAME];	// ������ �̸�(����, ���� ����)
};

struct MSG_FC_MARKET_SELL_OK// ��ǰ ��� �Ϸ� ��Ŷ
{
	UID64_t			ItemUID;			// ������ UID
};

typedef struct // ����, ȸ�� ��û �� �Ϸ� ��Ŷ
{
	UID64_t			MarketUID;			// �ŷ��� ������ȣ
}MSG_FC_MARKET_BUY_REQUEST, MSG_FC_MARKET_BUY_OK;

typedef struct // ȸ�� ��û
{
	UID64_t			MarketUID;			// �ŷ��� ������ȣ
	BYTE			MarketStatus;
}MSG_FC_MARKET_GET_REQUEST, MSG_FC_MARKET_GET_OK;

struct MSG_FL_LOG_MARKET_REGISTRATION	// ���ӷα� ���
{
	UID64_t				ItemUID;
	MARKET_INFO			MarketInfo;
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		sprintf(o_szLogString, "%s|%d|%d|(%I64d,%d,%d,%d,%d)|(%I64d|%I64d)\r\n", GetGameLogTypeString(i_nLogType), MarketInfo.AccountUID, MarketInfo.CharacterUID
			, ItemUID, MarketInfo.ItemNum, MarketInfo.ItemCount, MarketInfo.Price, MarketInfo.MoneyType, MarketInfo.MarketUID, MarketInfo.ItemUID);
		return o_szLogString;
	}
};
struct MSG_FL_LOG_MARKET_BUY			// ���ӷα� ����
{
	UID32_t				BuyerAccountUID;
	UID32_t				BuyerCheracterUID;
	MARKET_INFO			MarketInfo;
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		sprintf(o_szLogString, "%s|%d|%d|(%d,%d,%I64d,%I64d,%d,%d,%d,%d)\r\n", GetGameLogTypeString(i_nLogType), BuyerAccountUID, BuyerCheracterUID
			, MarketInfo.AccountUID, MarketInfo.CharacterUID, MarketInfo.MarketUID, MarketInfo.ItemUID, MarketInfo.ItemNum, MarketInfo.ItemCount, MarketInfo.Price, MarketInfo.MoneyType);
		return o_szLogString;
	}
};
struct MSG_FL_LOG_MARKET_GET			// ���ӷα� ȸ��
{
	MARKET_INFO			MarketInfo;
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		sprintf(o_szLogString, "%s|%d|%d|(%I64d,%I64d,%d,%d,%d,%d,%d)\r\n", GetGameLogTypeString(i_nLogType), MarketInfo.AccountUID, MarketInfo.CharacterUID
			, MarketInfo.MarketUID, MarketInfo.ItemUID, MarketInfo.ItemNum, MarketInfo.ItemCount, MarketInfo.Price, MarketInfo.MoneyType, MarketInfo.MarketState);
		return o_szLogString;
	}
};
// end 2013-11-25 by jhseol&bckim, �ŷ��� - ��Ŷ �߰�

// 2014-01-03 by jhseol&bckim, �ı������
/////////////////////////////////////////////////////////////////////////////////////////////
// T0_FC_MARKET �� �̾ ��Ŷ ����
#define T1_FC_DESTROY_AUCTION_BASE_INFO_REQUEST					0x1A	// �ʱ����� ��û
#define T1_FC_DESTROY_AUCTION_BASE_INFO_HEADER					0x1B	// �ʱ����� �ش�
#define T1_FC_DESTROY_AUCTION_BASE_INFO_OK						0x1C	// �ʱ����� ������
#define T1_FC_DESTROY_AUCTION_BASE_INFO_DONE					0x1D	// �ʱ����� �Ϸ�
#define T1_FC_DESTROY_AUCTION_TENDER_REQUEST					0x1E	// ���� ��û
#define T1_FC_DESTROY_AUCTION_TENDER_OK							0x1F	// ���� �Ϸ�
#define T1_FC_DESTROY_AUCTION_GET_REQUEST						0x20	// ������ ȸ�� ��û
#define T1_FC_DESTROY_AUCTION_GET_OK							0x21	// ������ ȸ�� �Ϸ�
#define T1_FC_DESTROY_AUCTION_MY_LIST_REQUEST					0x22	// ������Ȳ ��û
#define T1_FC_DESTROY_AUCTION_MY_LIST_HEADER					0x23	// ������Ȳ �ش�
#define T1_FC_DESTROY_AUCTION_MY_LIST_OK						0x24	// ������Ȳ ������
#define T1_FC_DESTROY_AUCTION_MY_LIST_DONE						0x25	// ������Ȳ �Ϸ�
#define T1_FC_DESTROY_AUCTION_NOTI_START						0x26	// �ı���� ���� �˸�
#define T1_FC_DESTROY_AUCTION_NOTI_END							0x27	// �ı���� ���� �˸�

#define T_FC_DESTROY_AUCTION_BASE_INFO_REQUEST	(MessageType_t)((T0_FC_MARKET<<8)|T1_FC_DESTROY_AUCTION_BASE_INFO_REQUEST)	// C->F // �ʱ����� ��û
#define T_FC_DESTROY_AUCTION_BASE_INFO_HEADER	(MessageType_t)((T0_FC_MARKET<<8)|T1_FC_DESTROY_AUCTION_BASE_INFO_HEADER)	// F->C // �ʱ����� �ش�
#define T_FC_DESTROY_AUCTION_BASE_INFO_OK		(MessageType_t)((T0_FC_MARKET<<8)|T1_FC_DESTROY_AUCTION_BASE_INFO_OK)		// F->C // �ʱ����� ������
#define T_FC_DESTROY_AUCTION_BASE_INFO_DONE		(MessageType_t)((T0_FC_MARKET<<8)|T1_FC_DESTROY_AUCTION_BASE_INFO_DONE)		// F->C // �ʱ����� �Ϸ�
#define T_FC_DESTROY_AUCTION_TENDER_REQUEST		(MessageType_t)((T0_FC_MARKET<<8)|T1_FC_DESTROY_AUCTION_TENDER_REQUEST)		// C->F // ���� ��û
#define T_FC_DESTROY_AUCTION_TENDER_OK			(MessageType_t)((T0_FC_MARKET<<8)|T1_FC_DESTROY_AUCTION_TENDER_OK)			// F->C // ���� �Ϸ�
#define T_FC_DESTROY_AUCTION_GET_REQUEST		(MessageType_t)((T0_FC_MARKET<<8)|T1_FC_DESTROY_AUCTION_GET_REQUEST)		// C->F // ������ ȸ�� ��û
#define T_FC_DESTROY_AUCTION_GET_OK				(MessageType_t)((T0_FC_MARKET<<8)|T1_FC_DESTROY_AUCTION_GET_OK)				// F->C // ������ ȸ�� �Ϸ�
#define T_FC_DESTROY_AUCTION_MY_LIST_REQUEST	(MessageType_t)((T0_FC_MARKET<<8)|T1_FC_DESTROY_AUCTION_MY_LIST_REQUEST)	// C->F // ������Ȳ ��û
#define T_FC_DESTROY_AUCTION_MY_LIST_HEADER		(MessageType_t)((T0_FC_MARKET<<8)|T1_FC_DESTROY_AUCTION_MY_LIST_HEADER)		// F->C // ������Ȳ �ش�
#define T_FC_DESTROY_AUCTION_MY_LIST_OK			(MessageType_t)((T0_FC_MARKET<<8)|T1_FC_DESTROY_AUCTION_MY_LIST_OK)			// F->C // ������Ȳ ������
#define T_FC_DESTROY_AUCTION_MY_LIST_DONE		(MessageType_t)((T0_FC_MARKET<<8)|T1_FC_DESTROY_AUCTION_MY_LIST_DONE)		// F->C // ������Ȳ �Ϸ�
#define T_FC_DESTROY_AUCTION_NOTI_START			(MessageType_t)((T0_FC_MARKET<<8)|T1_FC_DESTROY_AUCTION_NOTI_START)			// F->C // �ı���� ���� �˸�
#define T_FC_DESTROY_AUCTION_NOTI_END			(MessageType_t)((T0_FC_MARKET<<8)|T1_FC_DESTROY_AUCTION_NOTI_END)			// F->C // �ı���� ���� �˸�

typedef struct // �ʱ�, ������Ȳ ����Ʈ ��Ŷ
{
	ATUM_DATE_TIME DAuctionEndTime;
} MSG_FC_DESTROY_AUCTION_BASE_INFO_HEADER;

typedef struct // �ʱ�, ������Ȳ ����Ʈ ��Ŷ
{
	DESTROY_AUCTION_INFO DAuctionInfo;
} MSG_FC_DESTROY_AUCTION_BASE_INFO_OK, MSG_FC_DESTROY_AUCTION_MY_LIST_OK;

typedef struct // ���� ��û ��Ŷ
{
	UID64_t			DAuctionUID;			// ��� ��ȣ
	UID32_t			AccountUID;				// ������ ���� UID
	UID32_t			CharacterUID;			// ������ ĳ���� UID
	INT				TenderPrice;			// ���� ����
}MSG_FC_DESTROY_AUCTION_TENDER_REQUEST, MSG_FC_DESTROY_AUCTION_TENDER_OK;

typedef struct // ȸ�� ��û			// �Է����� ��������, ��� ������ȣ, �ݾ�, ������UID, 
{
	UID64_t			DAuctionUID;		// ��� ��ȣ
	BYTE			DAuctionStatus;
	UID64_t			ItemUID;			// ������ ������ȣ
	INT				Price;
	ATUM_DATE_TIME	DAuctionGetPossibleTime;	// ȸ�� ���� �ð�(���� ����(�������)�ð��� ����ȴ�)
}MSG_FC_DESTROY_AUCTION_GET_REQUEST, MSG_FC_DESTROY_AUCTION_GET_OK;

typedef struct			// 게임로그
{
	DESTROY_AUCTION_INFO			DAuctionInfo;
	char* GetWriteLogString(int i_nLogType, char* o_szLogString)
	{
		sprintf(o_szLogString, "%s|%d|%d|(%I64d,%I64d,%d,%d,%d,%d,%d)\r\n", GetGameLogTypeString(i_nLogType), DAuctionInfo.AccountUID, DAuctionInfo.CharacterUID
			, DAuctionInfo.DAuctionUID, DAuctionInfo.ItemUID, DAuctionInfo.ItemNum, DAuctionInfo.ItemCount, DAuctionInfo.Price, DAuctionInfo.MoneyType, DAuctionInfo.DAuctionState);
		return o_szLogString;
	}
}MSG_FL_LOG_DESTROY_AUCTION_TENDER, MSG_FL_LOG_DESTROY_AUCTION_FIX, MSG_FL_LOG_DESTROY_AUCTION_GET;		// 입찰, 낙찰, 회수
// end 2014-01-03 by jhseol&bckim, 파괴경매장

#endif