#include "stdafx.h"
#include "atumparam.h"
#include "atumprotocol.h"
#include "AtumError.h"				// 2006-10-02 by cmkwon
#include <fstream>					// 2007-05-10 by cmkwon

#ifdef _ATUM_FIELD_SERVER
#include "FieldIOCPSocket.h"
#endif

#ifndef DBGOUT
#define	DBGOUT	(void(0))
#endif

///////////////////////////////////////////////////////////////////////////////
// Config Variables
///////////////////////////////////////////////////////////////////////////////
char	CONFIG_ROOT[1024];

///////////////////////////////////////////////////////////////////////////////
// String Conversion Functions
const char *DBG_GET_POSITION_STRING(D3DXVECTOR3& vec, string& str)
{
#ifdef _DEBUG
	char buffer[256];
	sprintf(buffer, "(%d, %d, %d)", (int)vec.x, (int)vec.y, (int)vec.z);
	str += buffer;

	return str.c_str();
#else
	return NULL;
#endif
}

const char *GetMapString(MAP_CHANNEL_INDEX &refMapChannelIndex, string &str)
{
	char buffer[512];
	sprintf(buffer, "%d(%d)", refMapChannelIndex.MapIndex, refMapChannelIndex.ChannelIndex);
	str += buffer;

	return str.c_str();
}

const char *GetCharacterString(const CHARACTER *pCharac, string &str)
{
	if (pCharac == NULL)
	{
		return "[NULL]";
	}

	char buffer[512];
	sprintf(buffer, "[A(%s:%d) C(%s:%d) CI(%d)]",
		pCharac->AccountName, pCharac->AccountUniqueNumber, pCharac->CharacterName, pCharac->CharacterUniqueNumber, pCharac->ClientIndex);
// 2007-07-18 by cmkwon, ���� ���� - ���� ���� ����
//	sprintf(buffer, "[A: %s, CH: %s, CI: %d, UN: %d]",
//		pCharac->AccountName, pCharac->CharacterName, pCharac->ClientIndex, pCharac->CharacterUniqueNumber);
	str += buffer;

	return str.c_str();
}

const char *GetItemString(const ITEM_BASE *pItem, string &str)
{
	if (pItem == NULL)
	{
		return "[NULL]";
	}

	char buffer[512];
	sprintf(buffer, "[N: %s, IN: %d, UN: %I64d]",
		pItem->ItemInfo->ItemName, pItem->ItemNum, pItem->UniqueNumber);
	str += buffer;

	return str.c_str();
}

const char *GetItemGeneralString(const ITEM_GENERAL *pItem, string &str)
{
	if (pItem == NULL)
	{
		return "[NULL]";
	}

	char buffer[512];
	// 2008-02-14 by cmkwon, ���� ���� ��
	sprintf(buffer, "[IN:%d N:%10s UN:%I64d C:%d]",
		pItem->ItemNum, pItem->ItemInfo->ItemName, pItem->UniqueNumber, pItem->CurrentCount);
	str += buffer;

	return str.c_str();
}

const char *GetTimeString(string &str)
{
	char buffer[128];
	time_t ltime;
	struct tm *today = NULL;

	time(&ltime);
	today = localtime(&ltime);
	strftime(buffer, 128, "[%m-%d %H:%M:%S]", today );
	str += buffer;

	return str.c_str();
}

const char *GetItemSkillString(const ITEM_SKILL *pItem, string &str)
{
	if (pItem == NULL)
	{
		return "[NULL]";
	}

	char buffer[512];
	// 2008-02-14 by cmkwon, ���� ���� ��
	sprintf(buffer, "[IN:%d N:%10s UN:%I64d]",
		pItem->ItemNum, pItem->ItemInfo->ItemName, pItem->UniqueNumber);
	str += buffer;

	return str.c_str();
}

const char *Int2String(int n, string &str)
{
	char buffer[64];
	sprintf(buffer, "%d", n);
	str += buffer;

	return str.c_str();
}

const char *GetRaceString(USHORT race)
{
	switch(race)
	{
	case RACE_BATTALUS:			return STRCMD_CS_COMMON_RACE_BATTALUS;
	case RACE_DECA:				return STRCMD_CS_COMMON_RACE_DECA;
	case RACE_PHILON:			return STRCMD_CS_COMMON_RACE_PHILON;
	case RACE_SHARRINE:			return STRCMD_CS_COMMON_RACE_SHARRINE;
// 2006-04-20 by cmkwon	case RACE_MONSTER1:			return STRCMD_CS_COMMON_RACE_MONSTER1;
	case RACE_INFLUENCE_LEADER:	return STRCMD_CS_COMMON_RACE_INFLUENCE_LEADER;			// 2006-04-20 by cmkwon
// 2006-12-08 by dhjin	case RACE_MONSTER2:			return STRCMD_CS_COMMON_RACE_MONSTER2;

// 2007-10-06 by cmkwon, �������� 2���� ȣĪ�� �ٸ��� ���� -
//	case RACE_INFLUENCE_SUBLEADER: return STRCMD_CS_COMMON_RACE_INFLUENCE_SUBLEADER;	// 2006-12-08 by dhjin
//	case RACE_NPC:				return STRCMD_CS_COMMON_RACE_NPC;
	case RACE_INFLUENCE_SUBLEADER_1:	return STRCMD_CS_COMMON_RACE_INFLUENCE_SUBLEADER_1;	// 2007-10-06 by cmkwon, �������� 2���� ȣĪ�� �ٸ��� ���� -
	case RACE_INFLUENCE_SUBLEADER_2:	return STRCMD_CS_COMMON_RACE_INFLUENCE_SUBLEADER_2;	// 2007-10-06 by cmkwon, �������� 2���� ȣĪ�� �ٸ��� ���� -
	case RACE_OPERATION:		return STRCMD_CS_COMMON_RACE_OPERATION;
	case RACE_GAMEMASTER:		return STRCMD_CS_COMMON_RACE_GAMEMASTER;
	case RACE_MONITOR:			return STRCMD_CS_COMMON_RACE_MONITOR;
	case RACE_GUEST:			return STRCMD_CS_COMMON_RACE_GUEST;
	case RACE_DEMO:				return STRCMD_CS_COMMON_RACE_DEMO;
	case RACE_ALL:				return STRCMD_CS_COMMON_RACE_ALL;
	}

	return STRCMD_CS_COMMON_RACE_UNKNOWN;
}

char* Underbar2Space(char *string)
{
	int len = strlen(string);
	for (int i = 0; i < len && i < 128; i++)
	{
		if (string[i] == '_')
		{
			string[i] = ' ';
		}
	}

	return string;
}

bool operator<(const VersionInfo &v1, const VersionInfo &v2)
{
	if (v1.GetVersion()[0] != v2.GetVersion()[0])
	{
		return v1.GetVersion()[0] < v2.GetVersion()[0];
	}
	if (v1.GetVersion()[1] != v2.GetVersion()[1])
	{
		return v1.GetVersion()[1] < v2.GetVersion()[1];
	}
	if (v1.GetVersion()[2] != v2.GetVersion()[2])
	{
		return v1.GetVersion()[2] < v2.GetVersion()[2];
	}
	if (v1.GetVersion()[3] != v2.GetVersion()[3])
	{
		return v1.GetVersion()[3] < v2.GetVersion()[3];
	}
	
	return FALSE;
}

void PrintExchangeMsg(BYTE SendOrRecv, MessageType_t nType, char *peerIP, ENServerType st, BYTE printLevel)
{
#ifdef _DEBUG
	int bPrint = FALSE;

/*	if (HIBYTE(nType) == T0_FC_BATTLE)
	{
		// ������ ���!
		bPrint = TRUE;
	} else*/
	if (printLevel == PRINTLEVEL_NO_MSG)
	{
		return;
	}
	else if (printLevel == PRINTLEVEL_ALL)
	{
		bPrint = TRUE;
	}
	else if (printLevel == PRINTLEVEL_WO_ALIVE)
	{
		if (IS_ALIVE_MSG(nType))
		{
			return;
		}

		bPrint = TRUE;
	}
	else if (printLevel == PRINTLEVEL_WO_MOVE_BATTLE &&
		HIBYTE(nType) != T0_FC_MOVE &&
		HIBYTE(nType) != T0_FN_MOVE &&
		HIBYTE(nType) != T0_FN_MONSTER &&
		HIBYTE(nType) != T0_FC_BATTLE &&
		HIBYTE(nType) != T0_FN_BATTLE &&
		nType != T_FC_CHARACTER_CHANGE_CURRENTHPDPSPEP &&
		nType != T_FC_CHARACTER_CHANGE_BODYCONDITION &&
		nType != T_FN_MONSTER_CHANGE_HP &&
		nType != T_FC_STRING_128
	)
	{
		bPrint = TRUE;
	}
	else if (printLevel == PRINTLEVEL_A_FEW &&
//		HIBYTE(nType) == T0_FC_TRADE
//*
		(HIBYTE(nType) == T0_FC_PARTY ||
		HIBYTE(nType) == T0_IC_PARTY ||
		HIBYTE(nType) == T0_FI_PARTY)
		&&
		!(nType >= T_FC_PARTY_UPDATE_MEMBER_INFO_ALL &&
		nType <= T_FC_PARTY_UPDATE_MEMBER_INFO_BODYCONDITION)
//*/
	)
	{
		// PARTY ���ø� ���
		bPrint = TRUE;
	}
	else if (printLevel == PRINTLEVEL_FEW &&
		HIBYTE(nType) == T0_FI_ADMIN
	)
	{
		// ADMIN �� ���
		bPrint = TRUE;
	}
	else
	{
		return;
	}

	// bPrint Ȯ���ϱ�
	if (!bPrint) return;

	char szTime[128];
	time_t ltime;
	struct tm *today = NULL;
	const char *st_string;

	st_string = GGetENServerTypeString(st);

	if (SendOrRecv == RECV_TYPE)
	{
		time(&ltime);
		today = localtime(&ltime);
		strftime(szTime, 128, "[%m-%d %H:%M:%S]", today );
		DBGOUT("%s RECV TYPE: %s(%#04x) from %s[%s]\n", szTime, GetProtocolTypeString(nType), nType, st_string, peerIP);
	}
	else if (SendOrRecv == SEND_TYPE)
	{
		time(&ltime);
		today = localtime(&ltime);
		strftime(szTime, 128, "[%m-%d %H:%M:%S]", today );
		DBGOUT("%s SEND TYPE: %s(%#04x) to %s[%s]\n", szTime, GetProtocolTypeString(nType), nType, st_string, peerIP);
	}
#endif

}

BYTE* GetIPAddressInBytes(char *i_szIPAddress, BYTE *o_pIPArray)
{
	char *token;
	char seps[] = ".";
	char buffer[SIZE_MAX_VERSION_STRING];
	STRNCPY_MEMSET(buffer, i_szIPAddress, SIZE_MAX_VERSION_STRING);

	token = strtok(buffer, seps); o_pIPArray[0] = (BYTE)atoi(token);
	token = strtok(NULL, seps); o_pIPArray[1] = (BYTE)atoi(token);
	token = strtok(NULL, seps); o_pIPArray[2] = (BYTE)atoi(token);
	token = strtok(NULL, seps); o_pIPArray[3] = (BYTE)atoi(token);

	return o_pIPArray;
}

const char *GetIPAddressString(BYTE *i_pIPArray, STRNBUF &i_strnbuf)
{
	sprintf(i_strnbuf.GetBuffer(), "%d.%d.%d.%d", i_pIPArray[0], i_pIPArray[1], i_pIPArray[2], i_pIPArray[3]);
	return i_strnbuf.GetBuffer();
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			char *GetMonsterBellString(BYTE i_byMonBell)
/// \brief		
/// \author		cmkwon
/// \date		2006-12-13 ~ 2006-12-13
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
char *GetMonsterBellString(BYTE i_byMonBell)
{
	switch(i_byMonBell)
	{
	case BELL_ATATTACK:						return "BELL_ATATTACK";
	case BELL_DEFENSE:						return "BELL_DEFENSE";
	case BELL_RETREAT:						return "BELL_RETREAT";
	case BELL_TAGETATATTACK:				return "BELL_TAGETATATTACK";
	case BELL_NOTATTACK:					return "BELL_NOTATTACK";
	case BELL_ATTACK_OUTPOST_PROTECTOR:		return "BELL_ATTACK_OUTPOST_PROTECTOR";

	case BELL_INFLUENCE_VCN:				return "BELL_INFLUENCE_VCN";
	case BELL_INFLUENCE_ANI:				return "BELL_INFLUENCE_ANI";
	case BELL_STRATEGYPOINT_VCN:			return "BELL_STRATEGYPOINT_VCN";
	case BELL_STRATEGYPOINT_ANI:			return "BELL_STRATEGYPOINT_ANI";
	case BELL_OUTPOST_PROTECTOR_VCN:		return "BELL_OUTPOST_PROTECTOR_VCN";
	case BELL_OUTPOST_PROTECTOR_ANI:		return "BELL_OUTPOST_PROTECTOR_ANI";
	case BELL_OUTPOST_RESET_VCN:			return "BELL_OUTPOST_RESET_VCN";
	case BELL_OUTPOST_RESET_ANI:			return "BELL_OUTPOST_RESET_ANI";
	case BELL_ONEY_ATTACK_INFLUENCE_VCN:	return "BELL_ONEY_ATTACK_INFLUENCE_VCN";
	case BELL_ONEY_ATTACK_INFLUENCE_ANI:	return "BELL_ONEY_ATTACK_INFLUENCE_ANI";
	}
	
	return "UNKNOWN_BELL";
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			const char *GetItemDesParameter(BYTE i_byDesParameter)
/// \brief		
/// \author		cmkwon
/// \date		2005-11-25 ~ 2005-11-25
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
const char *GetItemDesParameter(DestParam_t i_byDesParameter)		// 2011-08-01 by hskim, ��Ʈ�� �ý��� 2�� - �ڷ��� ���� (DestParameter - 255 -> 32767 ����)
{
	switch(i_byDesParameter)
	{
	GET_CASERETURN_STRING_BY_TYPE(DES_NULL);
	GET_CASERETURN_STRING_BY_TYPE(DES_ATTACK_PART);
	GET_CASERETURN_STRING_BY_TYPE(DES_DEFENSE_PART);
	GET_CASERETURN_STRING_BY_TYPE(DES_FUEL_PART);
	GET_CASERETURN_STRING_BY_TYPE(DES_SOUL_PART);
	GET_CASERETURN_STRING_BY_TYPE(DES_SHIELD_PART);
	GET_CASERETURN_STRING_BY_TYPE(DES_DODGE_PART);
	GET_CASERETURN_STRING_BY_TYPE(DES_BODYCONDITION);
	GET_CASERETURN_STRING_BY_TYPE(DES_ENDURANCE_01);
	GET_CASERETURN_STRING_BY_TYPE(DES_ENDURANCE_02);
	GET_CASERETURN_STRING_BY_TYPE(DES_CHARGING_01);
	GET_CASERETURN_STRING_BY_TYPE(DES_CHARGING_02);
	GET_CASERETURN_STRING_BY_TYPE(DES_PROPENSITY);
	GET_CASERETURN_STRING_BY_TYPE(DES_HP);
	GET_CASERETURN_STRING_BY_TYPE(DES_DP);
	GET_CASERETURN_STRING_BY_TYPE(DES_SP);
	GET_CASERETURN_STRING_BY_TYPE(DES_EP);
	GET_CASERETURN_STRING_BY_TYPE(DES_SPRECOVERY);
	GET_CASERETURN_STRING_BY_TYPE(DES_HPRECOVERY);
	GET_CASERETURN_STRING_BY_TYPE(DES_MINATTACK_01);
	GET_CASERETURN_STRING_BY_TYPE(DES_MAXATTACK_01);
	GET_CASERETURN_STRING_BY_TYPE(DES_MINATTACK_02);
	GET_CASERETURN_STRING_BY_TYPE(DES_MAXATTACK_02);
	GET_CASERETURN_STRING_BY_TYPE(DES_ATTACKPROBABILITY_01);
	GET_CASERETURN_STRING_BY_TYPE(DES_ATTACKPROBABILITY_02);
	GET_CASERETURN_STRING_BY_TYPE(DES_DEFENSE_01);
	GET_CASERETURN_STRING_BY_TYPE(DES_DEFENSE_02);
	GET_CASERETURN_STRING_BY_TYPE(DES_DEFENSEPROBABILITY_01);
	GET_CASERETURN_STRING_BY_TYPE(DES_DEFENSEPROBABILITY_02);
	GET_CASERETURN_STRING_BY_TYPE(DES_SKILLPROBABILITY_01);
	GET_CASERETURN_STRING_BY_TYPE(DES_SKILLPROBABILITY_02);
	GET_CASERETURN_STRING_BY_TYPE(DES_FACTION_01);
	GET_CASERETURN_STRING_BY_TYPE(DES_FACTION_02);
	GET_CASERETURN_STRING_BY_TYPE(DES_FACTIONRESISTANCE_01);
	GET_CASERETURN_STRING_BY_TYPE(DES_FACTIONRESISTANCE_02);
	GET_CASERETURN_STRING_BY_TYPE(DES_SPEED);
	GET_CASERETURN_STRING_BY_TYPE(DES_TRANSPORT);
	GET_CASERETURN_STRING_BY_TYPE(DES_MATERIAL);
	GET_CASERETURN_STRING_BY_TYPE(DES_REATTACKTIME_01);
	GET_CASERETURN_STRING_BY_TYPE(DES_REATTACKTIME_02);
	GET_CASERETURN_STRING_BY_TYPE(DES_ABRASIONRATE_01);
	GET_CASERETURN_STRING_BY_TYPE(DES_ABRASIONRATE_02);
	GET_CASERETURN_STRING_BY_TYPE(DES_RANGE_01);
	GET_CASERETURN_STRING_BY_TYPE(DES_RANGE_02);
	GET_CASERETURN_STRING_BY_TYPE(DES_RANGEANGLE_01);
	GET_CASERETURN_STRING_BY_TYPE(DES_RANGEANGLE_02);
	GET_CASERETURN_STRING_BY_TYPE(DES_MULTITAGET_01);
	GET_CASERETURN_STRING_BY_TYPE(DES_MULTITAGET_02);
	GET_CASERETURN_STRING_BY_TYPE(DES_EXPLOSIONRANGE_01);
	GET_CASERETURN_STRING_BY_TYPE(DES_EXPLOSIONRANGE_02);
	GET_CASERETURN_STRING_BY_TYPE(DES_UNIT);
	GET_CASERETURN_STRING_BY_TYPE(DES_REVISION);
	GET_CASERETURN_STRING_BY_TYPE(DES_FACTIONPROBABILITY_01);
	GET_CASERETURN_STRING_BY_TYPE(DES_FACTIONPROBABILITY_02);
	GET_CASERETURN_STRING_BY_TYPE(DES_SHOTNUM_01);
	GET_CASERETURN_STRING_BY_TYPE(DES_SHOTNUM_02);
	GET_CASERETURN_STRING_BY_TYPE(DES_MULTINUM_01);
	GET_CASERETURN_STRING_BY_TYPE(DES_MULTINUM_02);
	GET_CASERETURN_STRING_BY_TYPE(DES_ATTACKTIME_01);
	GET_CASERETURN_STRING_BY_TYPE(DES_ATTACKTIME_02);
	GET_CASERETURN_STRING_BY_TYPE(DES_TIME_01);
	GET_CASERETURN_STRING_BY_TYPE(DES_TIME_02);
	GET_CASERETURN_STRING_BY_TYPE(DES_OVERHITTIME_01);
	GET_CASERETURN_STRING_BY_TYPE(DES_OVERHITTIME_02);
	GET_CASERETURN_STRING_BY_TYPE(DES_UNITKIND);
	GET_CASERETURN_STRING_BY_TYPE(DES_ITEMKIND);
	GET_CASERETURN_STRING_BY_TYPE(DES_SUMMON);
	GET_CASERETURN_STRING_BY_TYPE(DES_GRADUAL_HP_UP);
	GET_CASERETURN_STRING_BY_TYPE(DES_GRADUAL_DP_UP);
	GET_CASERETURN_STRING_BY_TYPE(DES_GRADUAL_SP_UP);
	GET_CASERETURN_STRING_BY_TYPE(DES_GRADUAL_EP_UP);
	GET_CASERETURN_STRING_BY_TYPE(DES_IN_TIME_HP_UP);
	GET_CASERETURN_STRING_BY_TYPE(DES_IN_TIME_DP_UP);
	GET_CASERETURN_STRING_BY_TYPE(DES_IN_TIME_SP_UP);
	GET_CASERETURN_STRING_BY_TYPE(DES_IN_TIME_EP_UP);
	GET_CASERETURN_STRING_BY_TYPE(DES_IMMEDIATE_HP_UP);
	GET_CASERETURN_STRING_BY_TYPE(DES_IMMEDIATE_DP_UP);
	GET_CASERETURN_STRING_BY_TYPE(DES_IMMEDIATE_SP_UP);
	GET_CASERETURN_STRING_BY_TYPE(DES_IMMEDIATE_EP_UP);
	GET_CASERETURN_STRING_BY_TYPE(DES_GROUNDMODE);
	GET_CASERETURN_STRING_BY_TYPE(DES_SIEGEMODE);
	GET_CASERETURN_STRING_BY_TYPE(DES_WEIGHT_01);
	GET_CASERETURN_STRING_BY_TYPE(DES_WEIGHT_02);
	GET_CASERETURN_STRING_BY_TYPE(DES_BULLET_01);
	GET_CASERETURN_STRING_BY_TYPE(DES_BULLET_02);
	GET_CASERETURN_STRING_BY_TYPE(DES_PRIMARY_WEAPON);
	GET_CASERETURN_STRING_BY_TYPE(DES_SECONDARY_WEAPON);
	GET_CASERETURN_STRING_BY_TYPE(DES_ALL_WEAPON);
	GET_CASERETURN_STRING_BY_TYPE(DES_CRITICALHITRATE_01);
	GET_CASERETURN_STRING_BY_TYPE(DES_CRITICALHITRATE_02);
	GET_CASERETURN_STRING_BY_TYPE(DES_WARP);
	GET_CASERETURN_STRING_BY_TYPE(DES_REACTION_RANGE);
	GET_CASERETURN_STRING_BY_TYPE(DES_RARE_FIX_NONE);
	GET_CASERETURN_STRING_BY_TYPE(DES_RARE_FIX_PREFIX);
	GET_CASERETURN_STRING_BY_TYPE(DES_RARE_FIX_SUFFIX);
	GET_CASERETURN_STRING_BY_TYPE(DES_RARE_FIX_BOTH);
	GET_CASERETURN_STRING_BY_TYPE(DES_REQ_MIN_LEVEL);
	GET_CASERETURN_STRING_BY_TYPE(DES_REQ_MAX_LEVEL);
	GET_CASERETURN_STRING_BY_TYPE(DES_CASH_STAT_ALL_INITIALIZE);
	GET_CASERETURN_STRING_BY_TYPE(DES_CASH_STAT_PART_INITIALIZE);
	GET_CASERETURN_STRING_BY_TYPE(DES_RARE_FIX_PREFIX_INITIALIZE);
	GET_CASERETURN_STRING_BY_TYPE(DES_RARE_FIX_SUFFIX_INITIALIZE);
	GET_CASERETURN_STRING_BY_TYPE(DES_ENCHANT_INITIALIZE);				// 2007-04-03 by cmkwon

	GET_CASERETURN_STRING_BY_TYPE(DES_CASH_STEALTH);
	GET_CASERETURN_STRING_BY_TYPE(DES_CASH_HP_AND_DP_UP);
	GET_CASERETURN_STRING_BY_TYPE(DES_CASH_GUILD_ALL_MEMBERS_SUMMON);
	GET_CASERETURN_STRING_BY_TYPE(DES_CASH_GUILD_MEMBER_SUMMON);
	GET_CASERETURN_STRING_BY_TYPE(DES_CASH_NORMAL_RESTORE);
	GET_CASERETURN_STRING_BY_TYPE(DES_CASH_SUPER_RESTORE);
	GET_CASERETURN_STRING_BY_TYPE(DES_CASH_GUILD);
	GET_CASERETURN_STRING_BY_TYPE(DES_CASH_MONSTER_SUMMON);
	GET_CASERETURN_STRING_BY_TYPE(DES_CASH_CHANGE_CHARACTERNAME);
	GET_CASERETURN_STRING_BY_TYPE(DES_CASH_SKILL_INITIALIZE);
	GET_CASERETURN_STRING_BY_TYPE(DES_CASH_CHANGE_PILOTFACE);
	GET_CASERETURN_STRING_BY_TYPE(DES_CASH_CRACKER_CARD);
	GET_CASERETURN_STRING_BY_TYPE(DES_SKILL_REDUCE_SHIELD_DAMAGE);
	GET_CASERETURN_STRING_BY_TYPE(DES_SKILL_INVINCIBLE);
	GET_CASERETURN_STRING_BY_TYPE(DES_SKILL_BIG_BOOM);
	GET_CASERETURN_STRING_BY_TYPE(DES_SKILL_HALLUCINATION);
	GET_CASERETURN_STRING_BY_TYPE(DES_SKILL_RANGEDOWN_01);
	GET_CASERETURN_STRING_BY_TYPE(DES_SKILL_RANGEDOWN_02);
	GET_CASERETURN_STRING_BY_TYPE(DES_SKILL_PROHIBITION_01);
	GET_CASERETURN_STRING_BY_TYPE(DES_SKILL_PROHIBITION_02);
	GET_CASERETURN_STRING_BY_TYPE(DES_ATTACK_RANGE_01);
	GET_CASERETURN_STRING_BY_TYPE(DES_ATTACK_RANGE_02);
	GET_CASERETURN_STRING_BY_TYPE(DES_INVISIBLE);
// 2005-12-02 by cmkwon	GET_CASERETURN_STRING_BY_TYPE(DES_SKILL_HYPERMOVING);
	GET_CASERETURN_STRING_BY_TYPE(DES_SKILL_DEFENSE_01);
	GET_CASERETURN_STRING_BY_TYPE(DES_SKILL_DEFENSE_02);
	GET_CASERETURN_STRING_BY_TYPE(DES_SKILL_FREEZINGBODY);
	GET_CASERETURN_STRING_BY_TYPE(DES_SKILL_REVERSECONTROL);
	GET_CASERETURN_STRING_BY_TYPE(DES_SKILL_GRADUAL_HPSHIELD_DOWN);
	GET_CASERETURN_STRING_BY_TYPE(DES_SKILL_SLOWMOVING);
	GET_CASERETURN_STRING_BY_TYPE(DES_SKILL_BOOSTEROFF);
	GET_CASERETURN_STRING_BY_TYPE(DES_SKILL_COLLISIONDAMAGE_DOWN);
//	GET_CASERETURN_STRING_BY_TYPE(DES_SKILL_CAMOUFLAGE);
	GET_CASERETURN_STRING_BY_TYPE(DES_SKILL_RANDOMTELEPORT);
	GET_CASERETURN_STRING_BY_TYPE(DES_SKILL_ATTACK_ALL);
	GET_CASERETURN_STRING_BY_TYPE(DES_SKILL_SCANNING);
	GET_CASERETURN_STRING_BY_TYPE(DES_SKILL_REVERSEENGINE);
	GET_CASERETURN_STRING_BY_TYPE(DES_SKILL_LOCKDOWN);
	GET_CASERETURN_STRING_BY_TYPE(DES_SKILL_STEALSP);
	GET_CASERETURN_STRING_BY_TYPE(DES_SKILL_SMARTSP);
	GET_CASERETURN_STRING_BY_TYPE(DES_SKILL_SUMMON_FORMATION_MEMBER);
	GET_CASERETURN_STRING_BY_TYPE(DES_SKILL_CANCEL_MAGIC);
	GET_CASERETURN_STRING_BY_TYPE(DES_SKILL_RANDOM_CANCEL);
	GET_CASERETURN_STRING_BY_TYPE(DES_SKILL_STOPMAGIC);
	GET_CASERETURN_STRING_BY_TYPE(DES_SKILL_CANCELALL);
	GET_CASERETURN_STRING_BY_TYPE(DES_SKILL_REACTIONSPEED);
	GET_CASERETURN_STRING_BY_TYPE(DES_SKILL_ENGINEANGLE);
	GET_CASERETURN_STRING_BY_TYPE(DES_SKILL_ENGINEBOOSTERANGLE);
	GET_CASERETURN_STRING_BY_TYPE(DES_DROP_EXP);
	GET_CASERETURN_STRING_BY_TYPE(DES_DROP_SPI);
	GET_CASERETURN_STRING_BY_TYPE(DES_DROP_ITEM);
	GET_CASERETURN_STRING_BY_TYPE(DES_RARE_ITEM_DROP_RATE);	// 238,2010-11-30 by shcho, ��������� ��� Ȯ�� ���� ������ ����
	GET_CASERETURN_STRING_BY_TYPE(DES_HP_REPAIR_RATE_FLIGHTING);
	GET_CASERETURN_STRING_BY_TYPE(DES_DP_REPAIR_RATE);
	GET_CASERETURN_STRING_BY_TYPE(DES_SP_REPAIR_RATE);
	GET_CASERETURN_STRING_BY_TYPE(DES_BAZAAR_SELL);
	GET_CASERETURN_STRING_BY_TYPE(DES_BAZAAR_BUY);
	GET_CASERETURN_STRING_BY_TYPE(DES_KILLMARK_EXP);
	GET_CASERETURN_STRING_BY_TYPE(DES_HYPER_BOOSTER);
	GET_CASERETURN_STRING_BY_TYPE(DES_SKILL_CHAFF_HP);
	GET_CASERETURN_STRING_BY_TYPE(DES_SKILL_AIR_BOMBING);
	GET_CASERETURN_STRING_BY_TYPE(DES_SKILL_NO_WARNING);
	GET_CASERETURN_STRING_BY_TYPE(DES_SKILL_ROLLING_TIME);
	GET_CASERETURN_STRING_BY_TYPE(DES_SKILL_FULL_RECOVERY);
	GET_CASERETURN_STRING_BY_TYPE(DES_SKILL_CAMOUFLAGE);
	GET_CASERETURN_STRING_BY_TYPE(DES_SKILL_BARRIER);
	GET_CASERETURN_STRING_BY_TYPE(DES_SKILL_HYPERSHOT);
	GET_CASERETURN_STRING_BY_TYPE(DES_SKILL_SHIELD_PARALYZE);
	GET_CASERETURN_STRING_BY_TYPE(DES_WARHEAD_SPEED);			// 176, 2007-06-11 by cmkwon, ź���� �ӵ�
	GET_CASERETURN_STRING_BY_TYPE(DES_CHAT_ALL_INFLUENCE);		// 177		// 2007-08-09 by cmkwon, ��� ���¿� ä�� �����ϱ� - desparam �߰�, ���������
	// 2008-09-22 by dhjin, �ű� ��þƮ
	GET_CASERETURN_STRING_BY_TYPE(DES_ENGINE_BOOSTER_TIME_UP);		// 178		// 2008-09-22 by dhjin, �ν��� �ð� ����
	GET_CASERETURN_STRING_BY_TYPE(DES_ENGINE_MAX_SPEED_UP);			// 179		// 2008-09-22 by dhjin, ���� �Ϲݼӵ�(�ִ�) ����
	GET_CASERETURN_STRING_BY_TYPE(DES_ENGINE_MIN_SPEED_UP);			// 180		// 2008-09-22 by dhjin, ���� �Ϲݼӵ�(�ּ�) ����
	GET_CASERETURN_STRING_BY_TYPE(DES_ENGINE_BOOSTER_SPEED_UP);		// 181		// 2008-09-22 by dhjin, ���� �ν��ͼӵ� ����
	GET_CASERETURN_STRING_BY_TYPE(DES_ENGINE_GROUND_SPEED_UP);		// 182		// 2008-09-22 by dhjin, ���� ����ӵ� ����
	GET_CASERETURN_STRING_BY_TYPE(DES_RADAR_OBJECT_DETECT_RANGE);	// 183		// 2008-09-22 by dhjin, ���̴� ��ü ���� �ݰ�
	GET_CASERETURN_STRING_BY_TYPE(DES_PIERCE_UP_01);				// 184		// 2008-09-22 by dhjin, �⺻���� �Ǿ�� ���� ī��
	GET_CASERETURN_STRING_BY_TYPE(DES_PIERCE_UP_02);				// 185		// 2008-09-22 by dhjin, ��޹��� �Ǿ�� ���� ī��
	GET_CASERETURN_STRING_BY_TYPE(DES_ENGINE_ANGLE_UP);				// 186		// 2008-09-30 by dhjin, ���� ȸ���� ���� ī��
	GET_CASERETURN_STRING_BY_TYPE(DES_ENGINE_BOOSTERANGLE_UP);		// 187		// 2008-09-30 by dhjin, ���� �ν��� ȸ���� ���� ī��
	GET_CASERETURN_STRING_BY_TYPE(DES_RARE_ITEM_PARTNER_SPEED);		// 239,		// 2010-12-21 by jskim, ���� �̵� �ӵ� ���� ������ ����
	GET_CASERETURN_STRING_BY_TYPE(DES_RARE_ITEM_PARTNER_DAMAGE);	// 240,		// 2010-12-21 by jskim, ��Ʈ�� ������ ���� ������ ����
	GET_CASERETURN_STRING_BY_TYPE(DES_RARE_ITEM_HPDP);				// 241,		// 2010-12-21 by jskim, HP, DP ŰƮ ���뷮 ���� ������ ����
	GET_CASERETURN_STRING_BY_TYPE(DES_SUMMON_POSITION_X);			// 242,		// 2011-05-02 by hskim, ���Ǵ�Ƽ 3�� - ��ȯ�� ��ġ ���� (��밪)
	GET_CASERETURN_STRING_BY_TYPE(DES_SUMMON_POSITION_Y);			// 243,		// 2011-05-02 by hskim, ���Ǵ�Ƽ 3�� - ��ȯ�� ��ġ ���� (��밪)
	GET_CASERETURN_STRING_BY_TYPE(DES_SUMMON_POSITION_Z);			// 244,		// 2011-05-02 by hskim, ���Ǵ�Ƽ 3�� - ��ȯ�� ��ġ ���� (��밪)

	GET_CASERETURN_STRING_BY_TYPE(DES_MAPBUFF_RANDOM_ADD_REATTACKTIME);		// 245,		// 2011-09-01 by hskim, EP4 [Ʈ���� �ý���] - ȭ���� / �� ��ǳ - �ʹ��� �߰� �ð� ����
	GET_CASERETURN_STRING_BY_TYPE(DES_MAPBUFF_RANDOM_ADD_TIME);				// 246,		// 2011-09-01 by hskim, EP4 [Ʈ���� �ý���] - ȭ���� / �� ��ǳ - �ʹ��� �߰� �ð� ����
	GET_CASERETURN_STRING_BY_TYPE(DES_ENCHANT_ONCE_APPLY);					// 247,		// 2011-09-01 by hskim, EP4 [Free to play] - 10ȸ ��þƮ ������ ��� ����
	GET_CASERETURN_STRING_BY_TYPE(DES_GAMBLE_RARE_ITEM_FIX);				// 248,		// 2011-09-01 by hskim, EP4 [Free to play] - ����/���� ���� �ɼ�

	GET_CASERETURN_STRING_BY_TYPE(DES_PET_SOCKET_ITEM_AUTOKIT);		// 23000,	// 2011-09-01 by hskim, ��Ʈ�� �ý��� 2�� - ��Ʈ�� �ý��� ���Ϸ� - �ڵ� ŰƮ
	GET_CASERETURN_STRING_BY_TYPE(DES_PET_SOCKET_ITEM_AUTOSKILL);	// 23001,	// 2011-09-01 by hskim, ��Ʈ�� �ý��� 2�� - ��Ʈ�� �ý��� ���Ϸ� - �ڵ� ��ų

	GET_CASERETURN_STRING_BY_TYPE(DES_PET_SLOT_ITEM_AUTOKIT_HP);			// 239000,	// 2011-09-01 by hskim, ��Ʈ�� �ý��� 2�� - �ڵ� ŰƮ HP
	GET_CASERETURN_STRING_BY_TYPE(DES_PET_SLOT_ITEM_AUTOKIT_SHIELD);		// 239001,	// 2011-09-01 by hskim, ��Ʈ�� �ý��� 2�� - �ڵ� ŰƮ Shield
	GET_CASERETURN_STRING_BY_TYPE(DES_PET_SLOT_ITEM_AUTOKIT_SP);			// 239002,	// 2011-09-01 by hskim, ��Ʈ�� �ý��� 2�� - �ڵ� ŰƮ SP

	GET_CASERETURN_STRING_BY_TYPE(DES_PET_SLOT_ITEM_AUTOSKILL_AGEAR);		// 239010,	// 2011-09-01 by hskim, ��Ʈ�� �ý��� 2�� - �ڵ� ��ų A ���
	GET_CASERETURN_STRING_BY_TYPE(DES_PET_SLOT_ITEM_AUTOSKILL_BGEAR);		// 239011,	// 2011-09-01 by hskim, ��Ʈ�� �ý��� 2�� - �ڵ� ��ų B ���
	GET_CASERETURN_STRING_BY_TYPE(DES_PET_SLOT_ITEM_AUTOSKILL_IGEAR);		// 239012,	// 2011-09-01 by hskim, ��Ʈ�� �ý��� 2�� - �ڵ� ��ų I ���
	GET_CASERETURN_STRING_BY_TYPE(DES_PET_SLOT_ITEM_AUTOSKILL_MGEAR);		// 239013,	// 2011-09-01 by hskim, ��Ʈ�� �ý��� 2�� - �ڵ� ��ų M ���
	}

	return "UNKNOWN_DES_PARAMETER";
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL GIsValidInfuenceType(BYTE i_byInfluenceTy)
/// \brief		
/// \author		cmkwon
/// \date		2005-12-03 ~ 2005-12-03
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL GIsValidInfuenceType(BYTE i_byInfluenceTy)
{
	switch(i_byInfluenceTy)
	{
	case INFLUENCE_TYPE_NORMAL:
	case INFLUENCE_TYPE_VCN:
	case INFLUENCE_TYPE_ANI:
	case INFLUENCE_TYPE_RRP:
		break;
	default:
		{
			return FALSE;
		}
	}
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			char *GGetLowerCase(char *o_szLowercaseSting, char *i_szString, int nMaxStringSize)
/// \brief		
/// \author		cmkwon
/// \date		2006-05-22 ~ 2006-05-22
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
char *GGetLowerCase(char *o_szLowercaseSting, char *i_szString, int nMaxStringSize)
{
	STRNCPY_MEMSET(o_szLowercaseSting, i_szString, nMaxStringSize);
	_strlwr(o_szLowercaseSting);
	return o_szLowercaseSting;
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			int GDelimiterIndex(char *i_szStr, int i_nMinIndex)
/// \brief		
/// \author		cmkwon
/// \date		2006-04-12 ~ 2006-04-12
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int GDelimiterIndex(char *i_szStr, int i_nMaxCount)
{
	if(i_nMaxCount >= strlen(i_szStr))
	{
		return strlen(i_szStr);
	}

	char *pBeforeStr = i_szStr;
	char *pCurStr = CharNext(pBeforeStr);
	while(pCurStr)
	{
		pBeforeStr	= pCurStr;
		pCurStr		= CharNext(pCurStr);
		int nCurCount = pCurStr - i_szStr;
		if(nCurCount == i_nMaxCount)
		{
			return nCurCount;
		}
		else if(nCurCount > i_nMaxCount)
		{
			return pBeforeStr - i_szStr;
		}
	}

	return 0;
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// 2006-10-02 by cmkwon
int		g_nargvCount;
char	g_szArrargv[SIZE_MAX_ARGV_COUNT][SIZE_MAX_ARGV_PARAM_STRING_SIZE];

///////////////////////////////////////////////////////////////////////////////
/// \fn			Err_t GSetExcuteParameterList(int i_nParamCount, char ** i_ppszParamString)
/// \brief		
/// \author		cmkwon
/// \date		2006-10-02 ~ 2006-10-02
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
Err_t GSetExcuteParameterList(int i_nParamCount, char ** i_ppszParamString)
{
	if(SIZE_MAX_ARGV_COUNT < i_nParamCount)
	{
		return ERR_INVALID_EXCUTE_PARAMETER_COUNT;
	}

	g_nargvCount			= i_nParamCount;
	int i; for(i=0; i < g_nargvCount; i++)
	{
		STRNCPY_MEMSET(g_szArrargv[i], i_ppszParamString[i], SIZE_MAX_ARGV_PARAM_STRING_SIZE);
	}

	return ERR_NO_ERROR;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			Err_t GCheckExcuteParameterList(SEXCUTE_PARAMETER *io_pExeParam)
/// \brief		
/// \author		cmkwon
/// \date		2006-10-02 ~ 2006-10-02
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
Err_t GCheckExcuteParameterList(SEXCUTE_PARAMETER *io_pExeParam)
{
#ifdef _DEBUG
	return ERR_NO_ERROR;
#endif

	// 2008-04-25 by cmkwon, ���� ���/���� �߰��� �� �߰� �Ǿ�� �ϴ� ���� - [����-�ʼ�] C_Exe1, C_Exe2 ����� ���� �Ķ���� ó�� �Լ� �߰�

#ifdef SERVICE_TYPE_KOREAN_SERVER_1
	return GCheckExcuteParameterList_Kor(io_pExeParam);
#endif

#ifdef SERVICE_TYPE_KOREAN_SERVER_2
	return GCheckExcuteParameterList_Kor2(io_pExeParam);
#endif

#ifdef SERVICE_TYPE_ENGLISH_SERVER_1
	return GCheckExcuteParameterList_Eng(io_pExeParam);
#endif

// 2007-12-21 by cmkwon, Gameforge(Europe) ������Ʈ �߰� - �߰���
// 2008-12-22 by cmkwon, ���� ���� �߰�(Gameforge4D ��Ű��, �Ҿ�, ��Ż���ƾ�) - �Ʒ��� ���� 3�� ��� �߰�
//#if defined(SERVICE_TYPE_ENGLISH_SERVER_2) || defined(SERVICE_TYPE_GERMAN_SERVER_1)		// 2008-04-25 by cmkwon, Gameforge4D_Deu �߰��� - 
// 2009-06-04 by cmkwon, ���� ���� �߰�(Gameforge4D �������, �����ξ�) - 
//#if defined(SERVICE_TYPE_ENGLISH_SERVER_2) || defined(SERVICE_TYPE_GERMAN_SERVER_1) || defined(SERVICE_TYPE_TURKISH_SERVER_1) || defined(SERVICE_TYPE_FRENCH_SERVER_1) || defined(SERVICE_TYPE_ITALIAN_SERVER_1)
// 2010-11-01 by shcho,	 ���� ���� �߰�(Gameforge4D �����ξ�, �Ƹ���Ƽ����) -  
//#if defined(SERVICE_TYPE_ENGLISH_SERVER_2) || defined(SERVICE_TYPE_GERMAN_SERVER_1) || defined(SERVICE_TYPE_TURKISH_SERVER_1) || defined(SERVICE_TYPE_FRENCH_SERVER_1) || defined(SERVICE_TYPE_ITALIAN_SERVER_1) || defined(SERVICE_TYPE_POLISH_SERVER_1) || defined(SERVICE_TYPE_SPANISH_SERVER_1)
#if defined(SERVICE_TYPE_ENGLISH_SERVER_2) || defined(SERVICE_TYPE_GERMAN_SERVER_1) || defined(SERVICE_TYPE_TURKISH_SERVER_1) || defined(SERVICE_TYPE_FRENCH_SERVER_1) || defined(SERVICE_TYPE_ITALIAN_SERVER_1) || defined(SERVICE_TYPE_POLISH_SERVER_1) || defined(SERVICE_TYPE_SPANISH_SERVER_1) || defined(SERVICE_TYPE_ARGENTINA_SERVER_1)
	return GCheckExcuteParameterList_Eng_Server_2(io_pExeParam);
#endif

#ifdef SERVICE_TYPE_VIETNAMESE_SERVER_1
	return GCheckExcuteParameterList_Viet(io_pExeParam);
#endif

	// 2007-05-15 by cmkwon, �߱� ����	
#ifdef SERVICE_TYPE_CHINESE_SERVER_1
	return GCheckExcuteParameterList_Chn(io_pExeParam);
#endif

// 2008-05-02 by cmkwon, WinnerOnline_Tha �߰��ϱ� - 
#if defined(SERVICE_TYPE_THAI_SERVER_1) || defined(SERVICE_TYPE_SINGAPORE_1) || defined(SERVICE_TYPE_INDONESIA_SERVER_1)
	return GCheckExcuteParameterList_Tha(io_pExeParam);
#endif

// 2008-05-29 by cmkwon, ���� ���� �߰�(Innova_Rus ���þƾ� �߰�) - 
#ifdef SERVICE_TYPE_RUSSIAN_SERVER_1
	return GCheckExcuteParameterList_Rus(io_pExeParam);
#endif

// 2008-09-23 by cmkwon, ���� ���� �߰�(�븸 Netpower_Tpe) - 
#ifdef SERVICE_TYPE_TAIWANESE_SERVER_1
	return GCheckExcuteParameterList_Tpe(io_pExeParam);
#endif

// 2008-12-03 by cmkwon, ���� ���� �߰�(�Ϻ� Arario_Jpn) - 
#ifdef SERVICE_TYPE_JAPANESE_SERVER_1
	return GCheckExcuteParameterList_Jpn(io_pExeParam);
#endif
	return ERR_NO_ERROR;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			Err_t GCheckExcuteParameterList_Kor(SEXCUTE_PARAMETER *io_pExeParam)
/// \brief		
/// \author		cmkwon
/// \date		2006-10-09 ~ 2006-10-09
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
Err_t GCheckExcuteParameterList_Kor(SEXCUTE_PARAMETER *io_pExeParam)
{
	switch(io_pExeParam->i_nExcuteFileType)
	{
	case EXCUTE_FILE_TYPE_SC_EXE:

		// 2012-07-11 by hskim, ������ �˴ٿ�
		if(1 != g_nargvCount && 2 != g_nargvCount)
		{
			return ERR_INVALID_EXCUTE_PARAMETER_COUNT;
		}

		if( 1 == g_nargvCount )
		{
			g_nargvCount++;
			STRNCPY_MEMSET(g_szArrargv[1], STR_DEFAULT_VALUE_SELECTIVE_SHUTDOWN_INFO, SIZE_MAX_SELECTIVE_SHUTDOWN_INFO);
		}

		STRNCPY_MEMSET(io_pExeParam->o_szSelectiveShutdownInfo, g_szArrargv[1], SIZE_MAX_SELECTIVE_SHUTDOWN_INFO);
		break;
		// 2012-07-11 by hskim, ������ �˴ٿ�

	case EXCUTE_FILE_TYPE_SC_ATM:
		break;
	case EXCUTE_FILE_TYPE_SC_LAUNCHER_ATM:
		{
			///////////////////////////////////////////////////////////////////////////////
			// 2006-10-02 by cmkwon
			// argv[0]: char[??]	���� ���� �̸�
			// argv[1]: char[24]	// 2012-07-11 by hskim, ������ �˴ٿ�
			// argv[2]:	char[16]	2007-05-15 by cmkwon, PreServer IP
			///////////////////////////////////////////////////////////////////////////////			
			if(1 != g_nargvCount && 2 != g_nargvCount && 3 != g_nargvCount)		// 2012-07-11 by hskim, ������ �˴ٿ�
			{
				return ERR_INVALID_EXCUTE_PARAMETER_COUNT;
			}

			if(2 == g_nargvCount)
			{// 2007-05-15 by cmkwon, PreServer IP�� ���ڸ���Ʈ�� �ִ�
				STRNCPY_MEMSET(io_pExeParam->o_szPreServerIP0, g_szArrargv[1], SIZE_MAX_IPADDRESS);
			}

			// 2012-07-11 by hskim, ������ �˴ٿ�
			if(3 == g_nargvCount)
			{
				STRNCPY_MEMSET(io_pExeParam->o_szSelectiveShutdownInfo, g_szArrargv[1], SIZE_MAX_SELECTIVE_SHUTDOWN_INFO);
				STRNCPY_MEMSET(io_pExeParam->o_szPreServerIP0, g_szArrargv[2], SIZE_MAX_IPADDRESS);				
			}
			// end 2012-07-11 by hskim, ������ �˴ٿ�
		}
		break;
	}
	return ERR_NO_ERROR;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			Err_t GCheckExcuteParameterList_Kor2(SEXCUTE_PARAMETER *io_pExeParam)
/// \brief		
/// \author		cmkwon
/// \date		2006-10-09 ~ 2006-10-09
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
Err_t GCheckExcuteParameterList_Kor2(SEXCUTE_PARAMETER *io_pExeParam)
{
	switch(io_pExeParam->i_nExcuteFileType)
	{
	case EXCUTE_FILE_TYPE_SC_EXE:
		{
			///////////////////////////////////////////////////////////////////////////////
			// 2006-10-02 by cmkwon
			// argv[0]: char[??]	���� ���� �̸�
			// argv[1]:	char[20]	AccountName
			// argv[2]:	char[33]	MD5PWD
			// argv[3]: int			Seed			[0~
			// argv[4]:	int			ExcuteType
			// argv[5]:	char[21]	2007-03-29 by cmkwon, Yedang ���� Key
			// argv[6]:	char[20]	2007-06-05 by cmkwon, BirthYear - ����⵵
			// argv[7]: char[24]	// 2012-07-11 by hskim, ������ �˴ٿ�
			///////////////////////////////////////////////////////////////////////////////			
			if(7 != g_nargvCount && 8 != g_nargvCount)		// 2012-07-11 by hskim, ������ �˴ٿ�
			{
				return ERR_INVALID_EXCUTE_PARAMETER_COUNT;
			}

			// 2012-07-11 by hskim, ������ �˴ٿ�
			if( 7 == g_nargvCount )
			{
				g_nargvCount++;
				STRNCPY_MEMSET(g_szArrargv[7], STR_DEFAULT_VALUE_SELECTIVE_SHUTDOWN_INFO, SIZE_MAX_SELECTIVE_SHUTDOWN_INFO);
			}

			STRNCPY_MEMSET(io_pExeParam->o_szSelectiveShutdownInfo, g_szArrargv[7], SIZE_MAX_SELECTIVE_SHUTDOWN_INFO);
			// end 2012-07-11 by hskim, ������ �˴ٿ�

			// argv[1]
			_strlwr(g_szArrargv[1]);				// 2006-10-18 by cmkwon, �ҹ��ڷ� ����
			STRNCPY_MEMSET(io_pExeParam->o_szAccountName0, g_szArrargv[1], SIZE_MAX_ACCOUNT_NAME);
			
			// argv[2], argv[3]
			char szEncryptMutexName[1024];
			sprintf(szEncryptMutexName, "%s%s", g_szArrargv[2], g_szArrargv[3]);
			HANDLE hMutex = ::OpenMutex(MUTEX_ALL_ACCESS, TRUE, szEncryptMutexName);
			if(hMutex == NULL)
			{		
				return ERR_INVALID_EXCUTE_PARAMETER;
			}	
			CloseHandle(hMutex);		// 2006-10-19 by cmkwon, �Լ� ����(ReleaseMutex-->CloseHandle)

		}
		break;
	case EXCUTE_FILE_TYPE_SC_LAUNCHER_ATM:
		{
			///////////////////////////////////////////////////////////////////////////////
			// 2006-10-02 by cmkwon
			// argv[0]: char[??]	���� ���� �̸�
			// argv[1]:	char[20]	AccountName
			// argv[2]:	char[33]	MD5PWD
			// argv[3]: int			Seed			[0~
			// argv[4]:	int			ExcuteType
			// argv[5]:	char[21]	2007-03-29 by cmkwon, Yedang ���� Key
			// argv[6]:	char[20]	2007-06-05 by cmkwon, BirthYear - ����⵵
			// argv[7]: char[24]	// 2012-07-11 by hskim, ������ �˴ٿ�
			// argv[8]: char[16]	2007-05-15 by cmkwon, PreServer IP
			///////////////////////////////////////////////////////////////////////////////			
			if(8 != g_nargvCount && 9 != g_nargvCount)		// 2012-07-11 by hskim, ������ �˴ٿ�
			{
				return ERR_INVALID_EXCUTE_PARAMETER_COUNT;
			}

			// argv[1]
			_strlwr(g_szArrargv[1]);				// 2006-10-18 by cmkwon, �ҹ��ڷ� ����
			STRNCPY_MEMSET(io_pExeParam->o_szAccountName0, g_szArrargv[1], SIZE_MAX_ACCOUNT_NAME);
			
			STRNCPY_MEMSET(io_pExeParam->o_szSelectiveShutdownInfo, g_szArrargv[7], SIZE_MAX_SELECTIVE_SHUTDOWN_INFO);		// 2012-07-11 by hskim, ������ �˴ٿ�

			// argv[2], argv[3]
			char szEncryptMutexName[1024];
			sprintf(szEncryptMutexName, "%s%s", g_szArrargv[2], g_szArrargv[3]);
			HANDLE hMutex = ::OpenMutex(MUTEX_ALL_ACCESS, TRUE, szEncryptMutexName);
			if(hMutex == NULL)
			{		
				return ERR_INVALID_EXCUTE_PARAMETER;
			}	
			CloseHandle(hMutex);		// 2006-10-19 by cmkwon, �Լ� ����(ReleaseMutex-->CloseHandle)

			if(9 == g_nargvCount)		// 2012-07-11 by hskim, ������ �˴ٿ�
			{// 2007-05-15 by cmkwon, PreServer IP�� ���ڸ���Ʈ�� �ִ�
				STRNCPY_MEMSET(io_pExeParam->o_szPreServerIP0, g_szArrargv[8], SIZE_MAX_IPADDRESS);		// 2012-07-11 by hskim, ������ �˴ٿ�
			}

			///////////////////////////////////////////////////////////////////////////////
			// 2007-06-05 by cmkwon, ����⵵�� �ѱ��
			io_pExeParam->o_nBirthYear	= atoi(g_szArrargv[6]);
		}
		break;
	case EXCUTE_FILE_TYPE_SC_ATM:
		{
			///////////////////////////////////////////////////////////////////////////////
			// 2006-10-09 by cmkwon
			// argv[0]: char[??]	���� ���� �̸�
			// argv[1]: char[16]	FieldServer IP
			// argv[2]: int			FieldServer Port
			// argv[3]: char[16]	IMServer IP
			// argv[4]: int			IMServer Port
			// argv[5]: Width		�ػ� ��
			// argv[6]: Height		�ػ� ����
			// argv[7]: Degree		��� ���� (0 �����, 1 �߻�� , 2 ����, 3 �浹ó��(����))
			// argv[8]:	char[20]	AccountName
			// argv[9]:	char[33]	MD5PWD
			// argv[10]:int			Seed			[0~
			// argv[11]:int			ExcuteType
			// argv[12]:char[20]	Reserve
			// argv[13]:char[20]	Reserve
			///////////////////////////////////////////////////////////////////////////////			
		}
		break;
	}
	return ERR_NO_ERROR;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			Err_t GCheckExcuteParameterList_Eng(SEXCUTE_PARAMETER *io_pExeParam)
/// \brief		
/// \author		cmkwon
/// \date		2006-10-09 ~ 2006-10-09
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
Err_t GCheckExcuteParameterList_Eng(SEXCUTE_PARAMETER *io_pExeParam)
{
	switch(io_pExeParam->i_nExcuteFileType)
	{
	case EXCUTE_FILE_TYPE_SC_EXE:
	case EXCUTE_FILE_TYPE_SC_ATM:
		break;
	case EXCUTE_FILE_TYPE_SC_LAUNCHER_ATM:
		{
			///////////////////////////////////////////////////////////////////////////////
			// 2006-10-02 by cmkwon
			// argv[0]: char[??]	���� ���� �̸�
			// argv[1]:	char[16]	2007-05-15 by cmkwon, PreServer IP
			///////////////////////////////////////////////////////////////////////////////			
			if(1 != g_nargvCount && 2 != g_nargvCount)
			{
				return ERR_INVALID_EXCUTE_PARAMETER_COUNT;
			}

			if(2 == g_nargvCount)
			{// 2007-05-15 by cmkwon, PreServer IP�� ���ڸ���Ʈ�� �ִ�
				STRNCPY_MEMSET(io_pExeParam->o_szPreServerIP0, g_szArrargv[1], SIZE_MAX_IPADDRESS);
			}
		}
		break;
	}
	return ERR_NO_ERROR;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			Err_t GCheckExcuteParameterList_Eng_Server_2(SEXCUTE_PARAMETER *io_pExeParam)
/// \brief		// 2007-12-21 by cmkwon, Gameforge(Europe) ������Ʈ �߰� - GCheckExcuteParameterList_Eng_Server_2() �߰�
/// \author		cmkwon
/// \date		2007-12-21 ~ 2007-12-21
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
Err_t GCheckExcuteParameterList_Eng_Server_2(SEXCUTE_PARAMETER *io_pExeParam)
{
	switch(io_pExeParam->i_nExcuteFileType)
	{
	case EXCUTE_FILE_TYPE_SC_EXE:
	case EXCUTE_FILE_TYPE_SC_ATM:
		break;
	case EXCUTE_FILE_TYPE_SC_LAUNCHER_ATM:
		{
			///////////////////////////////////////////////////////////////////////////////
			// 2006-10-02 by cmkwon
			// argv[0]: char[??]	���� ���� �̸�
			// argv[1]:	char[16]	2007-05-15 by cmkwon, PreServer IP
			///////////////////////////////////////////////////////////////////////////////			
			if(1 != g_nargvCount && 2 != g_nargvCount)
			{
				return ERR_INVALID_EXCUTE_PARAMETER_COUNT;
			}

			if(2 == g_nargvCount)
			{// 2007-05-15 by cmkwon, PreServer IP�� ���ڸ���Ʈ�� �ִ�
				STRNCPY_MEMSET(io_pExeParam->o_szPreServerIP0, g_szArrargv[1], SIZE_MAX_IPADDRESS);
			}
		}
		break;
	}
	return ERR_NO_ERROR;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			Err_t GCheckExcuteParameterList_Viet(SEXCUTE_PARAMETER *io_pExeParam)
/// \brief		
/// \author		cmkwon
/// \date		2006-10-09 ~ 2006-10-09
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
Err_t GCheckExcuteParameterList_Viet(SEXCUTE_PARAMETER *io_pExeParam)
{
	switch(io_pExeParam->i_nExcuteFileType)
	{
	case EXCUTE_FILE_TYPE_SC_EXE:
	case EXCUTE_FILE_TYPE_SC_ATM:
		break;
	case EXCUTE_FILE_TYPE_SC_LAUNCHER_ATM:
		{
			///////////////////////////////////////////////////////////////////////////////
			// 2006-10-02 by cmkwon
			// argv[0]: char[??]	���� ���� �̸�
			// argv[1]:	char[16]	2007-05-15 by cmkwon, PreServer IP
			///////////////////////////////////////////////////////////////////////////////			
			if(1 != g_nargvCount && 2 != g_nargvCount)
			{
				return ERR_INVALID_EXCUTE_PARAMETER_COUNT;
			}

			if(2 == g_nargvCount)
			{// 2007-05-15 by cmkwon, PreServer IP�� ���ڸ���Ʈ�� �ִ�
				STRNCPY_MEMSET(io_pExeParam->o_szPreServerIP0, g_szArrargv[1], SIZE_MAX_IPADDRESS);
			}
		}
		break;
	}
	return ERR_NO_ERROR;
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			Err_t GCheckExcuteParameterList_Chn(SEXCUTE_PARAMETER *io_pExeParam)
/// \brief		
/// \author		cmkwon
/// \date		2006-10-09 ~ 2006-10-09
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
Err_t GCheckExcuteParameterList_Chn(SEXCUTE_PARAMETER *io_pExeParam)
{
	switch(io_pExeParam->i_nExcuteFileType)
	{
	case EXCUTE_FILE_TYPE_SC_EXE:
	case EXCUTE_FILE_TYPE_SC_ATM:
		break;
	case EXCUTE_FILE_TYPE_SC_LAUNCHER_ATM:
		{
			///////////////////////////////////////////////////////////////////////////////
			// 2006-10-02 by cmkwon
			// argv[0]: char[??]	���� ���� �̸�
			// argv[1]:	char[16]	2007-05-15 by cmkwon, PreServer IP
			///////////////////////////////////////////////////////////////////////////////			
			if(1 != g_nargvCount && 2 != g_nargvCount)
			{
				return ERR_INVALID_EXCUTE_PARAMETER_COUNT;
			}

			if(2 == g_nargvCount)
			{// 2007-05-15 by cmkwon, PreServer IP�� ���ڸ���Ʈ�� �ִ�
				STRNCPY_MEMSET(io_pExeParam->o_szPreServerIP0, g_szArrargv[1], SIZE_MAX_IPADDRESS);
			}
		}
		break;
	}
	return ERR_NO_ERROR;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			Err_t GCheckExcuteParameterList_Tha(SEXCUTE_PARAMETER *io_pExeParam)
/// \brief		// 2008-05-02 by cmkwon, WinnerOnline_Tha �߰��ϱ� - GCheckExcuteParameterList_Tha() �߰�
/// \author		cmkwon
/// \date		2008-05-02 ~ 2005-05-02
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
Err_t GCheckExcuteParameterList_Tha(SEXCUTE_PARAMETER *io_pExeParam)
{
	switch(io_pExeParam->i_nExcuteFileType)
	{
	case EXCUTE_FILE_TYPE_SC_EXE:
	case EXCUTE_FILE_TYPE_SC_ATM:
		break;
	case EXCUTE_FILE_TYPE_SC_LAUNCHER_ATM:
		{
			///////////////////////////////////////////////////////////////////////////////
			// 2006-10-02 by cmkwon
			// argv[0]: char[??]	���� ���� �̸�
			// argv[1]:	char[16]	2007-05-15 by cmkwon, PreServer IP
			///////////////////////////////////////////////////////////////////////////////			
			if(1 != g_nargvCount && 2 != g_nargvCount)
			{
				return ERR_INVALID_EXCUTE_PARAMETER_COUNT;
			}
			
			if(2 == g_nargvCount)
			{// 2007-05-15 by cmkwon, PreServer IP�� ���ڸ���Ʈ�� �ִ�
				STRNCPY_MEMSET(io_pExeParam->o_szPreServerIP0, g_szArrargv[1], SIZE_MAX_IPADDRESS);
			}
		}
		break;
	}
	return ERR_NO_ERROR;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			Err_t GCheckExcuteParameterList_Rus(SEXCUTE_PARAMETER *io_pExeParam)
/// \brief		// 2008-05-29 by cmkwon, ���� ���� �߰�(Innova_Rus ���þƾ� �߰�) - GCheckExcuteParameterList_Rus() �߰�
/// \author		cmkwon
/// \date		2008-05-29 ~ 2005-05-29
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
Err_t GCheckExcuteParameterList_Rus(SEXCUTE_PARAMETER *io_pExeParam)
{
	switch(io_pExeParam->i_nExcuteFileType)
	{
	case EXCUTE_FILE_TYPE_SC_EXE:
	case EXCUTE_FILE_TYPE_SC_ATM:
		break;
	case EXCUTE_FILE_TYPE_SC_LAUNCHER_ATM:
		{
			///////////////////////////////////////////////////////////////////////////////
			// 2006-10-02 by cmkwon
			// argv[0]: char[??]	���� ���� �̸�
			// argv[1]:	char[16]	2007-05-15 by cmkwon, PreServer IP
			///////////////////////////////////////////////////////////////////////////////			
			if(1 != g_nargvCount && 2 != g_nargvCount)
			{
				return ERR_INVALID_EXCUTE_PARAMETER_COUNT;
			}
			
			if(2 == g_nargvCount)
			{// 2007-05-15 by cmkwon, PreServer IP�� ���ڸ���Ʈ�� �ִ�
				STRNCPY_MEMSET(io_pExeParam->o_szPreServerIP0, g_szArrargv[1], SIZE_MAX_IPADDRESS);
			}
		}
		break;
	}
	return ERR_NO_ERROR;
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			Err_t GCheckExcuteParameterList_Tpe(SEXCUTE_PARAMETER *io_pExeParam)
/// \brief		// 2008-09-23 by cmkwon, ���� ���� �߰�(�븸 Netpower_Tpe) - 
/// \author		cmkwon
/// \date		2008-09-23 ~ 2008-09-23
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
Err_t GCheckExcuteParameterList_Tpe(SEXCUTE_PARAMETER *io_pExeParam)
{
	switch(io_pExeParam->i_nExcuteFileType)
	{
	case EXCUTE_FILE_TYPE_SC_EXE:
	case EXCUTE_FILE_TYPE_SC_ATM:
		break;
	case EXCUTE_FILE_TYPE_SC_LAUNCHER_ATM:
		{
			///////////////////////////////////////////////////////////////////////////////
			// 2006-10-02 by cmkwon
			// argv[0]: char[??]	���� ���� �̸�
			// argv[1]:	char[16]	2007-05-15 by cmkwon, PreServer IP
			///////////////////////////////////////////////////////////////////////////////			
			if(1 != g_nargvCount && 2 != g_nargvCount)
			{
				return ERR_INVALID_EXCUTE_PARAMETER_COUNT;
			}
			
			if(2 == g_nargvCount)
			{// 2007-05-15 by cmkwon, PreServer IP�� ���ڸ���Ʈ�� �ִ�
				STRNCPY_MEMSET(io_pExeParam->o_szPreServerIP0, g_szArrargv[1], SIZE_MAX_IPADDRESS);
			}
		}
		break;
	}
	return ERR_NO_ERROR;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			Err_t GCheckExcuteParameterList_Jpn(SEXCUTE_PARAMETER *io_pExeParam)
/// \brief		// 2008-12-03 by cmkwon, ���� ���� �߰�(�Ϻ� Arario_Jpn) - 
/// \author		cmkwon
/// \date		2008-12-03 ~ 2008-12-03
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
Err_t GCheckExcuteParameterList_Jpn(SEXCUTE_PARAMETER *io_pExeParam)
{
	switch(io_pExeParam->i_nExcuteFileType)
	{
	case EXCUTE_FILE_TYPE_SC_EXE:	// ACEonline.atm
		{
			///////////////////////////////////////////////////////////////////////////////
			// 2008-12-18 by cmkwon, �Ϻ� Arario ��ó ���� - 
			// argv[0]: char[??]	���� ���� �̸�
			// argv[1]:	char[20]	AccountName
			// argv[2]:	char[33]	Password
			// argv[3]:	char[301]	Session Key
			///////////////////////////////////////////////////////////////////////////////			
			if(4 != g_nargvCount)
			{
				return ERR_INVALID_EXCUTE_PARAMETER_COUNT;
			}
			
			STRNCPY_MEMSET(io_pExeParam->o_szAccountName0, g_szArrargv[1], SIZE_MAX_ACCOUNT_NAME);
			STRNCPY_MEMSET(io_pExeParam->o_szPassword, g_szArrargv[2], SIZE_MAX_PASSWORD_MD5_STRING);
			STRNCPY_MEMSET(io_pExeParam->o_szSessionKey, g_szArrargv[3], SIZE_MAX_WEBLOGIN_AUTHENTICATION_KEY);
		}
		break;
	case EXCUTE_FILE_TYPE_SC_LAUNCHER_ATM:	// Launcher.atm
		{
			///////////////////////////////////////////////////////////////////////////////
			// 2008-12-18 by cmkwon, �Ϻ� Arario ��ó ���� - 
			// argv[0]: char[??]	���� ���� �̸�
			// argv[1]:	char[20]	AccountName
			// argv[2]:	char[33]	Password
			// argv[3]:	char[301]	Session Key
			// argv[4]:	char[16]	2007-05-15 by cmkwon, PreServer IP
			///////////////////////////////////////////////////////////////////////////////			
			if(1 != g_nargvCount && 5 != g_nargvCount)
			{
				return ERR_INVALID_EXCUTE_PARAMETER_COUNT;
			}
			
			if(5 == g_nargvCount)
			{
				STRNCPY_MEMSET(io_pExeParam->o_szAccountName0, g_szArrargv[1], SIZE_MAX_ACCOUNT_NAME);
				STRNCPY_MEMSET(io_pExeParam->o_szPassword, g_szArrargv[2], SIZE_MAX_PASSWORD_MD5_STRING);
				STRNCPY_MEMSET(io_pExeParam->o_szSessionKey, g_szArrargv[3], SIZE_MAX_WEBLOGIN_AUTHENTICATION_KEY);
				STRNCPY_MEMSET(io_pExeParam->o_szPreServerIP0, g_szArrargv[4], SIZE_MAX_IPADDRESS);
			}
		}
		break;
	case EXCUTE_FILE_TYPE_SC_ATM:
		break;
	}
	return ERR_NO_ERROR;
}

Err_t GReadVersionInfoFile(VersionInfo *o_pLauncherVerInfo, SREG_DATA_EXE_2 *o_pRegDataExe2, char *i_szVersionInfoFileName)
{
	o_pLauncherVerInfo->SetVersion(0,0,0,0);
	o_pRegDataExe2->resetREG_DATA_EXE_2();


	const int	BUFF_SIZE = 1024;
	char		buff[BUFF_SIZE];
	const char	*token;
	char		seps[] = " \t";
	ifstream	fin;

	fin.open(i_szVersionInfoFileName);
	if (!fin.is_open())
	{
		return ERR_VERSIONINFO_FILE_NOT_FOUND;
	}

	while(TRUE)
	{
		memset(buff, 0x00, BUFF_SIZE);
		BOOL bFlagFileEnd = fin.getline(buff, BUFF_SIZE).eof();
		if (bFlagFileEnd == TRUE)
		{
			break;
		}

		token = strtok(buff, seps);
		if (token == NULL						// ignore blank lines
			|| strncmp(token, "#", 1) == 0		// ignore comments
			|| strncmp(token, "$", 1) == 0)		// ignore user defined variables
		{
			continue;
		}

		if (0 == stricmp(token, COMMON_STRMSG_REG_KEY_NAME_LAUNCHER_VERSION))	// 2013-10-15 by bckim, ������ �������� ���� ��Ʈ�� ����	STRMSG_REG_KEY_NAME_LAUNCHER_VERSION->COMMON_STRMSG_REG_KEY_NAME_LAUNCHER_VERSION
		{
			token = strtok(NULL, seps);
			if (token)
			{
				o_pLauncherVerInfo->SetVersion(token);
			}
		}
		else if (0 == stricmp(token, COMMON_STRMSG_REG_KEY_NAME_CLIENT_VERSION))	// 2013-10-15 by bckim, ������ �������� ���� ��Ʈ�� ���� STRMSG_REG_KEY_NAME_CLIENT_VERSION->COMMON_STRMSG_REG_KEY_NAME_CLIENT_VERSION  
		{
			char *token = strtok(NULL, seps);
			if (token)
			{
				o_pRegDataExe2->ClientVersion.SetVersion(token);
			}
		}
		else if (0 == stricmp(token, COMMON_STRMSG_REG_KEY_NAME_WINDOWDEGREE_NEW))	// 2013-10-15 by bckim, ������ �������� ���� ��Ʈ�� ���� COMMON_STRMSG_REG_KEY_NAME_WINDOWDEGREE_NEW
		{
// 2007-12-27 by cmkwon, �������� ��� ��� �߰� - �Ʒ��� ���� ����
//			char *token = strtok(NULL, seps);
//			if (token)
//			{
//				o_pRegDataExe2->WindowDegree = atoi(token);
//			}
			char *token = strtok(NULL, "\t");
			if (token)
			{
				STRNCPY_MEMSET(o_pRegDataExe2->WindowDegree, token, SIZE_MAX_WINDOW_DEGREE_NAME);
			}
		}
		else if (0 == stricmp(token, COMMON_STRMSG_REG_KEY_NAME_WINDOWMODE))	// 2013-10-15 by bckim, ������ �������� ���� ��Ʈ�� ���� STRMSG_REG_KEY_NAME_WINDOWMODE->COMMON_STRMSG_REG_KEY_NAME_WINDOWMODE
		{// 2008-01-03 by cmkwon, �������� ���� �����ϱ� - GReadVersionInfoFile() �� ó�� �߰�
			char *token = strtok(NULL, seps);
			if (token)
			{
				int nMode = atoi(token);
				if(0 != nMode)
				{
					o_pRegDataExe2->IsWindowMode	= TRUE;
				}
			}
		}
		else if (0 == stricmp(token, COMMON_STRMSG_REG_KEY_NAME_ACCOUNT_NAME))	// 2013-10-15 by bckim, ������ �������� ���� ��Ʈ�� ���� STRMSG_REG_KEY_NAME_ACCOUNT_NAME->COMMON_STRMSG_REG_KEY_NAME_ACCOUNT_NAME
		{
			char *token = strtok(NULL, seps);
			if (token)
			{
				STRNCPY_MEMSET(o_pRegDataExe2->BeforeAccountName, token, SIZE_MAX_ACCOUNT_NAME);
			}
		}
		else if (0 == stricmp(token, STRMSG_REG_KEY_NAME_SERVER_GROUP_NAME))
		{
			char *token = strtok(NULL, seps);
			if (token)
			{
				STRNCPY_MEMSET(o_pRegDataExe2->SelectedServerGroupName, token, SIZE_MAX_SERVER_NAME);
			}
		}
	}
	fin.close();

	return ERR_NO_ERROR;
}

Err_t GLoadExe1VersionInfo(VersionInfo *o_pLauncherVerInfo, char *i_szVersionInfoFileName)
{
	VersionInfo lver;
	SREG_DATA_EXE_2 regDataExe2;
	regDataExe2.resetREG_DATA_EXE_2();
	Err_t errCode = GReadVersionInfoFile(&lver, &regDataExe2, i_szVersionInfoFileName);
	if(errCode != ERR_NO_ERROR)
	{
		return errCode;
	}

	*o_pLauncherVerInfo = lver;
	return ERR_NO_ERROR;
}

Err_t GLoadExe2VersionInfo(SREG_DATA_EXE_2 *o_pRegDataEXE2, char *i_szVersionInfoFileName)
{
	VersionInfo lver;
	SREG_DATA_EXE_2 regDataExe2;
	regDataExe2.resetREG_DATA_EXE_2();
	Err_t errCode = GReadVersionInfoFile(&lver, &regDataExe2, i_szVersionInfoFileName);
	if(errCode != ERR_NO_ERROR)
	{
		return errCode;
	}

	*o_pRegDataEXE2		= regDataExe2;
	return ERR_NO_ERROR;
}


Err_t GWriteVersionInfoFile(VersionInfo *i_pLauncherVerInfo, SREG_DATA_EXE_2 *i_pRegDataEXE2, char *i_szVersionInfoFileName)
{
	// ����� ���� ����
	DeleteFile(i_szVersionInfoFileName);
	int nErr = GetLastError();
	SetLastError(0);
	
	// ���� ����
	HANDLE hFile = INVALID_HANDLE_VALUE;
	hFile = CreateFile(i_szVersionInfoFileName, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
	{
		int nErr = GetLastError();
		SetLastError(0);
		return ERR_VERSIONINFO_FILE_CAN_NOT_CREATE;
	}

	const int	BUFF_SIZE = 1024;
	char		buff[BUFF_SIZE];
	DWORD		nWritten;

	sprintf(buff, "###############################################################################\r\n");
	WriteFile(hFile, buff, strlen(buff), &nWritten, NULL);
	sprintf(buff, "#  %s			0.0.0.0\r\n#\r\n", COMMON_STRMSG_REG_KEY_NAME_LAUNCHER_VERSION);	// 2013-10-15 by bckim, ������ �������� ���� ��Ʈ�� ����	STRMSG_REG_KEY_NAME_LAUNCHER_VERSION->COMMON_STRMSG_REG_KEY_NAME_LAUNCHER_VERSION
	WriteFile(hFile, buff, strlen(buff), &nWritten, NULL);
	sprintf(buff, "#  %s			0.0.0.0\r\n", COMMON_STRMSG_REG_KEY_NAME_CLIENT_VERSION);		// 2013-10-15 by bckim, ������ �������� ���� ��Ʈ�� ���� STRMSG_REG_KEY_NAME_CLIENT_VERSION->COMMON_STRMSG_REG_KEY_NAME_CLIENT_VERSION  
	WriteFile(hFile, buff, strlen(buff), &nWritten, NULL);
// 2007-12-27 by cmkwon, �������� ��� ��� �߰� - �Ʒ��� ���� ����
//	sprintf(buff, "#  %s				0\r\n#\r\n", STRMSG_REG_KEY_NAME_WINDOWDEGREE);
	sprintf(buff, "#  %s			1024x768 (high)\r\n#\r\n", COMMON_STRMSG_REG_KEY_NAME_WINDOWDEGREE_NEW);	// 2013-10-15 by bckim, ������ �������� ���� ��Ʈ�� ���� COMMON_STRMSG_REG_KEY_NAME_WINDOWDEGREE_NEW
	WriteFile(hFile, buff, strlen(buff), &nWritten, NULL);
	
	// 2008-01-03 by cmkwon, �������� ���� �����ϱ� - 
	sprintf(buff, "#  %s				0\r\n#\r\n", COMMON_STRMSG_REG_KEY_NAME_WINDOWMODE);	// 2013-10-15 by bckim, ������ �������� ���� ��Ʈ�� ���� STRMSG_REG_KEY_NAME_WINDOWMODE->COMMON_STRMSG_REG_KEY_NAME_WINDOWMODE
	WriteFile(hFile, buff, strlen(buff), &nWritten, NULL);

	sprintf(buff, "#  %s				Mir\r\n", COMMON_STRMSG_REG_KEY_NAME_ACCOUNT_NAME);	// 2013-10-15 by bckim, ������ �������� ���� ��Ʈ�� ���� STRMSG_REG_KEY_NAME_ACCOUNT_NAME->COMMON_STRMSG_REG_KEY_NAME_ACCOUNT_NAME
	WriteFile(hFile, buff, strlen(buff), &nWritten, NULL);
	sprintf(buff, "#  %s			ACE\r\n", STRMSG_REG_KEY_NAME_SERVER_GROUP_NAME);
	WriteFile(hFile, buff, strlen(buff), &nWritten, NULL);
	sprintf(buff, "###############################################################################\r\n\r\n");
	WriteFile(hFile, buff, strlen(buff), &nWritten, NULL);

	sprintf(buff, "%s\t\t\t%s\r\n\r\n", COMMON_STRMSG_REG_KEY_NAME_LAUNCHER_VERSION, i_pLauncherVerInfo->GetVersionString());	// 2013-10-15 by bckim, ������ �������� ���� ��Ʈ�� ����	STRMSG_REG_KEY_NAME_LAUNCHER_VERSION->COMMON_STRMSG_REG_KEY_NAME_LAUNCHER_VERSION
	WriteFile(hFile, buff, strlen(buff), &nWritten, NULL);

	sprintf(buff, "%s\t\t\t%s\r\n", COMMON_STRMSG_REG_KEY_NAME_CLIENT_VERSION, i_pRegDataEXE2->ClientVersion.GetVersionString());		// 2013-10-15 by bckim, ������ �������� ���� ��Ʈ�� ���� STRMSG_REG_KEY_NAME_CLIENT_VERSION->COMMON_STRMSG_REG_KEY_NAME_CLIENT_VERSION  
	WriteFile(hFile, buff, strlen(buff), &nWritten, NULL);
// 2007-12-27 by cmkwon, �������� ��� ��� �߰� -
//	sprintf(buff, "%s\t\t\t%d\r\n\r\n", STRMSG_REG_KEY_NAME_WINDOWDEGREE, i_pRegDataEXE2->WindowDegree);
	sprintf(buff, "%s\t\t\t%s\r\n\r\n", COMMON_STRMSG_REG_KEY_NAME_WINDOWDEGREE_NEW, i_pRegDataEXE2->WindowDegree);	// 2013-10-15 by bckim, ������ �������� ���� ��Ʈ�� ���� COMMON_STRMSG_REG_KEY_NAME_WINDOWDEGREE_NEW
	WriteFile(hFile, buff, strlen(buff), &nWritten, NULL);
	
	// 2008-01-03 by cmkwon, �������� ���� �����ϱ� - 
	sprintf(buff, "%s\t\t\t\t%d\r\n\r\n", COMMON_STRMSG_REG_KEY_NAME_WINDOWMODE, i_pRegDataEXE2->IsWindowMode);	// 2013-10-15 by bckim, ������ �������� ���� ��Ʈ�� ���� STRMSG_REG_KEY_NAME_WINDOWMODE->COMMON_STRMSG_REG_KEY_NAME_WINDOWMODE
	WriteFile(hFile, buff, strlen(buff), &nWritten, NULL);

	sprintf(buff, "%s\t\t\t\t%s\r\n", COMMON_STRMSG_REG_KEY_NAME_ACCOUNT_NAME, i_pRegDataEXE2->BeforeAccountName);	// 2013-10-15 by bckim, ������ �������� ���� ��Ʈ�� ���� STRMSG_REG_KEY_NAME_ACCOUNT_NAME->COMMON_STRMSG_REG_KEY_NAME_ACCOUNT_NAME
	WriteFile(hFile, buff, strlen(buff), &nWritten, NULL);
	sprintf(buff, "%s\t\t\t%s\r\n", STRMSG_REG_KEY_NAME_SERVER_GROUP_NAME, i_pRegDataEXE2->SelectedServerGroupName);
	WriteFile(hFile, buff, strlen(buff), &nWritten, NULL);
	
	CloseHandle(hFile);		// ���� �ݱ�
	return ERR_NO_ERROR;
}

Err_t GSaveExe1VersionInfo(VersionInfo *i_pLauncherVerInfo, char *i_szVersionInfoFileName)
{
	VersionInfo lver;
	SREG_DATA_EXE_2 regDataExe2;
	regDataExe2.resetREG_DATA_EXE_2();
	Err_t errCode = GReadVersionInfoFile(&lver, &regDataExe2, i_szVersionInfoFileName);
		
	lver = *i_pLauncherVerInfo;
	return GWriteVersionInfoFile(&lver, &regDataExe2, i_szVersionInfoFileName);
}

Err_t GSaveExe2VersionInfo(SREG_DATA_EXE_2 *i_pRegDataEXE2, char *i_szVersionInfoFileName)
{
	VersionInfo lver;
	SREG_DATA_EXE_2 regDataExe2;
	regDataExe2.resetREG_DATA_EXE_2();
	Err_t errCode = GReadVersionInfoFile(&lver, &regDataExe2, i_szVersionInfoFileName);
	
	regDataExe2 = *i_pRegDataEXE2;
	return GWriteVersionInfoFile(&lver, &regDataExe2, i_szVersionInfoFileName);
}

///////////////////////////////////////////////////////////////////////////////
// 2008-04-25 by cmkwon, ���� ���/���� �߰��� �� �߰� �Ǿ�� �ϴ� ���� - [����-�ʼ�] AdminTool, DBTool, Monitor �� ������ ������ ����Ʈ ����

// 2006-01-09 by cmkwon, EP2�� ���ؼ� DB���� ������
//						atum_db_account			--> atum2_db_account
//						atum_db_[n]				--> atum2_db_[n]
//						atum_db_account_test	--> atum2_db_account_test
//						atum_db_test			--> atum2_db_test
#ifndef _ATUM_CLIENT
GAME_SERVER_INFO_FOR_ADMIN g_arrGameServers[] = 
{
	// 2007-11-07 by cmkwon, �α� DB ���� ���� �����ϱ� - �ʵ� 4�� �߰�, LogDBIP, LogDBPort, LogDBUID, LogDBPWD
	// {Name, XOREncodedPreServerIP, XOREncodedDBServerIP, DBServerPort, XOREncodedDBUserID, XOREncodedDBPWD, DB Name, LogDBIP, LogDBPort, LogDBUID, LogDBPWD, PreServerIP, DBServerIP, DBUserID, DBPWD}
	// 2007-10-24 by cmkwon, ���� ���� ��ȣȭ - Key
	// #define STR_XOR_KEY_STRING_SERVER_INFO			"~8xANs(^fP{)34$(fcbTN$(C-=x"	// 2007-10-24 by cmkwon, ���� ���� ��ȣȭ - DB Server Password XOR Key

// 2008-08-29 by cmkwon, AdminTool,DBTool ������ ����Ʈ ���� ����(���񽺺��� ���̰�) - 
//#ifdef _ATUM_ADMIN_RELEASE

#ifdef SERVICE_TYPE_ENGLISH_SERVER_1
	{ "RAT46 (atum/callweb) [atum2_db_1]",
		"4F0A4F6F7E5D187057", "4F0A4F6F7E5D187057", 1433, //IP,IP,PORT
		"1F4C0d2C",	"1D59142D39164A",//DBID,DBPWD
		"atum2_db_1",//DBNAME
		"4F0A4F6F7E5D187057", 1433, //DBIP,DBPORT
		"1F4C0d2C",	"1D59142D39164A" },//DBUID,DBPWD
#endif// #ifdef SERVICE_TYPE_ENGLISH_SERVER_1
	
	{NULL, NULL, NULL, 0, NULL, NULL}
	// ServerName, PreServerIP, DBIP, DBPort, DBUID, DBPWD, DBName
};
#else // _ATUM_CLIENT
GAME_SERVER_INFO_FOR_ADMIN g_arrGameServers[] = 
{
	{NULL, NULL, NULL, 0, NULL, NULL}
};
#endif // _ATUM_CLIENT


///////////////////////////////////////////////////////////////////////////////
/// \fn			void GDecryptGameServerInfoByXOR(void)
/// \brief		// 2007-10-24 by cmkwon, ���� ���� ��ȣȭ -
/// \author		cmkwon
/// \date		2007-10-24 ~ 2007-10-24
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void GDecryptGameServerInfoByXOR(void)
{
#ifndef _ATUM_CLIENT

	for(int i = 0; g_arrGameServers[i].ServerName != NULL; i++)
	{
		BYTE byEncodedBinary[1024];

		memset(byEncodedBinary, 0x00, 1024);
		if(XOR::XORString2Binary(byEncodedBinary, g_arrGameServers[i].XOREncodedServerIP))
		{
			XOR::XOREncode((BYTE*)g_arrGameServers[i].ServerIP, byEncodedBinary, strlen(g_arrGameServers[i].XOREncodedServerIP)/2, STR_XOR_KEY_STRING_SERVER_INFO);
		}

		memset(byEncodedBinary, 0x00, 1024);
		if(XOR::XORString2Binary(byEncodedBinary, g_arrGameServers[i].XOREncodedDBIP))
		{
			XOR::XOREncode((BYTE*)g_arrGameServers[i].DBIP, byEncodedBinary, strlen(g_arrGameServers[i].XOREncodedDBIP)/2, STR_XOR_KEY_STRING_SERVER_INFO);
		}

		memset(byEncodedBinary, 0x00, 1024);
		if(XOR::XORString2Binary(byEncodedBinary, g_arrGameServers[i].XOREncodedDBUID))
		{
			XOR::XOREncode((BYTE*)g_arrGameServers[i].DBUID, byEncodedBinary, strlen(g_arrGameServers[i].XOREncodedDBUID)/2, STR_XOR_KEY_STRING_SERVER_INFO);
		}

		memset(byEncodedBinary, 0x00, 1024);
		if(XOR::XORString2Binary(byEncodedBinary, g_arrGameServers[i].XOREncodedDBPWD))
		{
			XOR::XOREncode((BYTE*)g_arrGameServers[i].DBPWD, byEncodedBinary, strlen(g_arrGameServers[i].XOREncodedDBPWD)/2, STR_XOR_KEY_STRING_SERVER_INFO);
		}
		
		///////////////////////////////////////////////////////////////////////////////		
		// 2007-11-07 by cmkwon, �α� DB ���� ���� �����ϱ� - GAME_SERVER_INFO_FOR_ADMIN �������� 4�� �ʵ� �߰�
		// 2007-11-07 by cmkwon, LogDBIP, LogDBUID, LogDBPWD �� �ʵ�� ���ڵ� �Ǿ� �����Ƿ� �Ʒ��� ���� ��ȣȭ �ؾ� ��
		char szEncryptData[1024];

		memset(szEncryptData, 0x00, 1024);
		strncpy(szEncryptData, g_arrGameServers[i].LogDBIP, 2*SIZE_MAX_ADDRESS - 1);		// 2009-01-15 by cmkwon, PreServer, DBServer ���� DNS�� ���� �����ϰ� ���� - ����(SIZE_MAX_IPADDRESS)
		memset(g_arrGameServers[i].LogDBIP, 0x00, 2*SIZE_MAX_ADDRESS);						// 2009-01-15 by cmkwon, PreServer, DBServer ���� DNS�� ���� �����ϰ� ���� - ����(SIZE_MAX_IPADDRESS)
		memset(byEncodedBinary, 0x00, 1024);
		if(XOR::XORString2Binary(byEncodedBinary, szEncryptData))
		{
			XOR::XOREncode((BYTE*)g_arrGameServers[i].LogDBIP, byEncodedBinary, strlen(szEncryptData)/2, STR_XOR_KEY_STRING_SERVER_INFO);
		}

		memset(szEncryptData, 0x00, 1024);
		strncpy(szEncryptData, g_arrGameServers[i].LogDBUID, 2*SIZE_MAX_DB_USER_ID - 1);
		memset(g_arrGameServers[i].LogDBUID, 0x00, 2*SIZE_MAX_DB_USER_ID);
		memset(byEncodedBinary, 0x00, 1024);
		if(XOR::XORString2Binary(byEncodedBinary, szEncryptData))
		{
			XOR::XOREncode((BYTE*)g_arrGameServers[i].LogDBUID, byEncodedBinary, strlen(szEncryptData)/2, STR_XOR_KEY_STRING_SERVER_INFO);
		}
		
		memset(szEncryptData, 0x00, 1024);
		strncpy(szEncryptData, g_arrGameServers[i].LogDBPWD, 2*SIZE_MAX_DB_USER_PWD - 1);
		memset(g_arrGameServers[i].LogDBPWD, 0x00, 2*SIZE_MAX_DB_USER_PWD);
		memset(byEncodedBinary, 0x00, 1024);
		if(XOR::XORString2Binary(byEncodedBinary, szEncryptData))
		{
			XOR::XOREncode((BYTE*)g_arrGameServers[i].LogDBPWD, byEncodedBinary, strlen(szEncryptData)/2, STR_XOR_KEY_STRING_SERVER_INFO);
		}
	}
#endif
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			char *GetDayOfWeekString(int i_nDayOfWeek)
/// \brief		// 2007-10-30 by cmkwon, ���º� ���Ǿƿ� �̺�Ʈ ���� -
/// \author		cmkwon
/// \date		2007-10-30 ~ 2007-10-30
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
char *GetDayOfWeekString(int i_nDayOfWeek)
{
	switch(i_nDayOfWeek)
	{
	case DAY_OF_WEEK_SUMDAY:				return "Sunday";
	case DAY_OF_WEEK_MONDAY:				return "Monday";
	case DAY_OF_WEEK_TUESDAY:				return "Tuesday";
	case DAY_OF_WEEK_WEDNESDAY:				return "Wednesday";
	case DAY_OF_WEEK_THURSDAY:				return "Thursday";
	case DAY_OF_WEEK_FRIDAY:				return "Friday";
	case DAY_OF_WEEK_SATURDAY:				return "Saturday";
	case DAY_OF_WEEK_HAPPYHOUREVENT_PERIOD:	return "HappyHourEventPeriod";
	case DAY_OF_WEEK_PCBANG_HAPPYHOUREVENT:	return "PCBangHappyHourEventPeriod";
	}
	return "Unknown day of week";	
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			char *GetWPUTString(BYTE i_byWPUT)
/// \brief		// 2009-01-22 by cmkwon, ���� ���� ���� �α� ���� - 
/// \author		cmkwon
/// \date		2009-01-22 ~ 2009-01-22
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
char *GetWPUTString(BYTE i_byWPUT)
{
	switch(i_byWPUT)
	{
	case WPUT_GENERAL:				return "WPUT_GENERAL";
	case WPUT_ARENA:				return "WPUT_ARENA";
	case WPUT_MOTHERSHIPWAR:		return "WPUT_MOTHERSHIPWAR";
	case WPUT_STRATEGYPOINTWAR:		return "WPUT_STRATEGYPOINTWAR";
	case WPUT_OUTPOSTWAR:			return "WPUT_OUTPOSTWAR";
	case WPUT_SHOP:					return "WPUT_SHOP";
	case WPUT_ADMIN_COMMAND:		return "WPUT_ADMIN_COMMAND";
	case WPUT_TRIGGER:				return "WPUT_TRIGGER";			// 2011-11-07 by hskim, EP4 [Ʈ���� �ý���] - NCG ������ �ý���
	case WPUT_MARKET:				return "WPUT_MARKET";	 		// 2013-11-25 by jhseol&bckim, �ŷ���
	}

	return WPUT_UNKNOWN;
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			char *LowercaseOnly_i_forTurkish(char *i_szString, int i_nMaxLen)
/// \brief		// 2009-01-23 by cmkwon, ��Ű i,I ���� ���� ó�� -
/// \author		cmkwon
/// \date		2009-01-23 ~ 2009-01-23
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
char *LowercaseOnly_i_forTurkish(char *i_szString, int i_nMaxLen)
{
#if defined(SERVICE_TYPE_TURKISH_SERVER_1)
	char *	pCurChar	= i_szString;
	int		nLen		= min(i_nMaxLen, strlen(i_szString));
	while(pCurChar && pCurChar < i_szString + nLen)
	{
		// 2009-01-23 by cmkwon, I���ڸ��� i�� ����
		if('I' == *pCurChar)
		{
			*pCurChar = 'i';
		}
		
		pCurChar = CharNext(pCurChar);		// 2007-12-05 by cmkwon, ���� ���ڷ� �̵�
	}
#endif
	return i_szString;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			int GetArrIdxByUnitMaskforWRK(INT i_unitMask)
/// \brief		// 2009-02-12 by cmkwon, EP3-3 ���巩ŷ�ý��� ���� - 
/// \author		cmkwon
/// \date		2009-02-18 ~ 2009-02-18
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int GetArrIdxByUnitMaskforWRK(INT i_unitMask)
{
	if(UNITKIND_ALL_MASK == i_unitMask)
	{
		return 0;
	}

	if(COMPARE_BIT_FLAG(i_unitMask, UNITKIND_BGEAR))
	{
		return 1;
	}
	if(COMPARE_BIT_FLAG(i_unitMask, UNITKIND_MGEAR))
	{
		return 2;
	}
	if(COMPARE_BIT_FLAG(i_unitMask, UNITKIND_AGEAR))
	{
		return 3;
	}
	if(COMPARE_BIT_FLAG(i_unitMask, UNITKIND_IGEAR))
	{
		return 4;
	}

	return -1;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			int GetUnitMaskByArrIdxforWRK(INT i_arrIdx)
/// \brief		// 2009-02-12 by cmkwon, EP3-3 ���巩ŷ�ý��� ���� - 
/// \author		cmkwon
/// \date		2009-02-18 ~ 2009-02-18
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int GetUnitMaskByArrIdxforWRK(INT i_arrIdx)
{
	switch(i_arrIdx)
	{
	case 0:			return UNITKIND_ALL_MASK;
	case 1:			return UNITKIND_BGEAR;
	case 2:			return UNITKIND_MGEAR;
	case 3:			return UNITKIND_AGEAR;
	case 4:			return UNITKIND_IGEAR;
	}

	return 0;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			int GetArrayIndexByInfluenceType(BYTE i_byInflTy)
/// \brief		// 2007-10-30 by cmkwon, ���º� ���Ǿƿ� �̺�Ʈ ���� - GetArrayIndexByInfluenceType() �Լ� �߰�
/// \author		cmkwon
/// \date		2007-11-01 ~ 2007-11-01
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int GetArrayIndexByInfluenceType(BYTE i_byInflTy)
{
	switch(i_byInflTy)
	{
	case INFLUENCE_TYPE_NORMAL:				return 0;
	case INFLUENCE_TYPE_VCN:				return 1;
	case INFLUENCE_TYPE_ANI:				return 2;
	case INFLUENCE_TYPE_ALL_MASK:			return 3;
	}

	return -1;	
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			BYTE GetInfluenceTypeByArrayIndex(int i_nArrIdx)
/// \brief		// 2007-10-30 by cmkwon, ���º� ���Ǿƿ� �̺�Ʈ ���� - GetInfluenceTypeByArrayIndex() �Լ� �߰�
/// \author		cmkwon
/// \date		2007-11-01 ~ 2007-11-01
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BYTE GetInfluenceTypeByArrayIndex(int i_nArrIdx)
{
	switch(i_nArrIdx)
	{
	case 0:			return INFLUENCE_TYPE_NORMAL;
	case 1:			return INFLUENCE_TYPE_VCN;
	case 2:			return INFLUENCE_TYPE_ANI;
	case 3:			return INFLUENCE_TYPE_ALL_MASK;
	}

	return INFLUENCE_TYPE_UNKNOWN;	
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		// 2008-06-03 by cmkwon, AdminTool, DBTool ���� ������ �˻��� �޺��ڽ����� �˻� ��� �߰�(K0000143) - 
/// \author		cmkwon
/// \date		2008-06-03 ~ 2008-06-03
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
char *StringCullingForValidChar(char *i_szSource, int i_nCullingSize)
{
	char *pCur	= i_szSource;
	char *pPrev = i_szSource;
	while('\0' != *pCur)
	{
		pCur = CharNext(pCur);
		int nGap = pCur - i_szSource;
		if(nGap == i_nCullingSize)
		{
			return pCur;
		}
		else if(nGap > i_nCullingSize)
		{
			return pPrev;
		}
		pPrev = pCur;
	}

	return pCur;
}


// operator overloading
MEX_ITEM_INFO& MEX_ITEM_INFO::operator=(const ITEM& rhs)
{
	this->ItemNum			= rhs.ItemNum;		
	this->Kind				= rhs.Kind;			
	this->AbilityMin		= rhs.AbilityMin;		
	this->AbilityMax		= rhs.AbilityMax;		
	this->ReqUnitKind		= rhs.ReqUnitKind;	
	this->ReqMinLevel		= rhs.ReqMinLevel;
	this->ReqMaxLevel		= rhs.ReqMaxLevel;
	this->HitRate			= rhs.HitRate;		
	this->Defense			= rhs.Defense;		
	this->SpeedPenalty		= rhs.SpeedPenalty;	
	this->Range				= rhs.Range;			
	this->Price				= rhs.Price;
	this->CashPrice			= rhs.CashPrice;
// 2009-04-21 by cmkwon, ITEM�� DesParam �ʵ� ���� 8���� �ø��� - �Ʒ��� ���� ����
// 	this->DestParameter1	= rhs.DestParameter1;	
// 	this->ParameterValue1	= rhs.ParameterValue1;
// 	this->DestParameter2	= rhs.DestParameter2;	
// 	this->ParameterValue2	= rhs.ParameterValue2;
// 	this->DestParameter3	= rhs.DestParameter3;	
// 	this->ParameterValue3	= rhs.ParameterValue3;
// 	this->DestParameter4	= rhs.DestParameter4;	
// 	this->ParameterValue4	= rhs.ParameterValue4;
	memcpy(this->ArrDestParameter, rhs.ArrDestParameter, sizeof(this->ArrDestParameter[0])*SIZE_MAX_DESPARAM_COUNT_IN_ITEM);
	memcpy(this->ArrParameterValue, rhs.ArrParameterValue, sizeof(this->ArrParameterValue[0])*SIZE_MAX_DESPARAM_COUNT_IN_ITEM);

	this->ReAttacktime		= rhs.ReAttacktime;	
	this->Time				= rhs.Time;			
	this->RepeatTime		= rhs.RepeatTime;			// 2006-12-08 by cmkwon, �߰���
	this->RangeAngle		= rhs.RangeAngle;		
	this->MultiTarget		= rhs.MultiTarget;	
	this->ExplosionRange	= rhs.ExplosionRange;	
	this->ReactionRange		= rhs.ReactionRange;	
	this->ShotNum			= rhs.ShotNum;		
	this->MultiNum			= rhs.MultiNum;		
	this->AttackTime		= rhs.AttackTime;		
	this->ReqSP				= rhs.ReqSP;			
	this->OrbitType			= rhs.OrbitType;		
	this->ItemAttribute		= rhs.ItemAttribute;	
	this->BoosterAngle		= rhs.BoosterAngle;	

	return *this;
}

ITEM& ITEM::operator=(const MEX_ITEM_INFO& rhs)
{
	this->ItemNum			= rhs.ItemNum;		
	this->Kind				= rhs.Kind;			
	this->AbilityMin		= rhs.AbilityMin;		
	this->AbilityMax		= rhs.AbilityMax;		
	this->ReqUnitKind		= rhs.ReqUnitKind;	
	this->ReqMinLevel		= rhs.ReqMinLevel;
	this->ReqMaxLevel		= rhs.ReqMaxLevel;
	this->HitRate			= rhs.HitRate;		
	this->Defense			= rhs.Defense;		
	this->SpeedPenalty		= rhs.SpeedPenalty;	
	this->Range				= rhs.Range;			
	this->Price				= rhs.Price;
	this->CashPrice			= rhs.CashPrice;
// 2009-04-21 by cmkwon, ITEM�� DesParam �ʵ� ���� 8���� �ø��� - �Ʒ��� ���� ����
// 	this->DestParameter1	= rhs.DestParameter1;	
// 	this->ParameterValue1	= rhs.ParameterValue1;
// 	this->DestParameter2	= rhs.DestParameter2;	
// 	this->ParameterValue2	= rhs.ParameterValue2;
// 	this->DestParameter3	= rhs.DestParameter3;	
// 	this->ParameterValue3	= rhs.ParameterValue3;
// 	this->DestParameter4	= rhs.DestParameter4;	
// 	this->ParameterValue4	= rhs.ParameterValue4;
	memcpy(this->ArrDestParameter, rhs.ArrDestParameter, sizeof(this->ArrDestParameter[0])*SIZE_MAX_DESPARAM_COUNT_IN_ITEM);
	memcpy(this->ArrParameterValue, rhs.ArrParameterValue, sizeof(this->ArrParameterValue[0])*SIZE_MAX_DESPARAM_COUNT_IN_ITEM);

	this->ReAttacktime		= rhs.ReAttacktime;	
	this->Time				= rhs.Time;			
	this->RepeatTime		= rhs.RepeatTime;			// 2006-12-08 by cmkwon, �߰���
	this->RangeAngle		= rhs.RangeAngle;		
	this->MultiTarget		= rhs.MultiTarget;	
	this->ExplosionRange	= rhs.ExplosionRange;	
	this->ReactionRange		= rhs.ReactionRange;	
	this->ShotNum			= rhs.ShotNum;		
	this->MultiNum			= rhs.MultiNum;		
	this->AttackTime		= rhs.AttackTime;		
	this->ReqSP				= rhs.ReqSP;			
	this->OrbitType			= rhs.OrbitType;		
	this->ItemAttribute		= rhs.ItemAttribute;	
	this->BoosterAngle		= rhs.BoosterAngle;	

	return *this;
}

BOOL GCheckLimitLevel(EN_CHECK_TYPE i_checkType, int i_nLevel)
{
	switch(i_checkType)
	{
	case CHECK_TYPE_BATTLE_P2P_PK:
		{
			if(i_nLevel >= 10)
			{
				return TRUE;
			}
		}
		break;
	case CHECK_TYPE_BATTLE_PARTY_WAR:
		{
			if(i_nLevel >= 10)
			{
				return TRUE;
			}
		}
		break;
	case CHECK_TYPE_CHARACTER_MENT:
		{
			if(i_nLevel >= 30)
			{
				return TRUE;
			}
		}
		break;
//	case CHECK_TYPE_GUILD_CREATE:
//	case CHECK_TYPE_CHAT_SELL_ALL:		// 2008-05-19 by dhjin, EP3 - ä�� �ý��� ����, ���� ä��
	case CHECK_TYPE_GUILD_CREATE:
		{
			if(i_nLevel >= GuildCommanderMinLevel)		// 2008-10-13 by dhjin, ������ ���� ���� ���� üũ �߰�.
			{
				return TRUE;
			}
		}
		break;
	case CHECK_TYPE_PENALTY_ON_DEAD:
		{
			if(i_nLevel > 15)
			{
				return TRUE;
			}
		}
		break;
	case CHECK_TYPE_LOWLEVEL_ADVANTAGE:			// 2006-03-15 by cmkwon
		{
			if(i_nLevel <= 5)
			{
				return TRUE;
			}
		}
		break;
	case CHECK_TYPE_CHAT_WAR:			// 2008-05-19 by dhjin, EP3 - ä�� �ý��� ����, ���� ä��
		{
			if(i_nLevel >= 20)
			{
				return TRUE;
			}
		}
		break;
#if _RAT_CHAT_SYSTEM
	case CHECK_TYPE_CHAT_INFLUENCE_ALL_RAT:
		{
			if (i_nLevel >= 20)
			{
				return TRUE;
			}
		}
#endif
	}
	return FALSE;
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL GCheckRaceAndInfluenceType(EN_CHECK_TYPE i_checkType, USHORT i_usRace, BYTE i_byInfluenceTy, USHORT i_usPeerRace, BYTE i_byPeerInfluenceTy)
/// \brief		
/// \author		cmkwon
/// \date		2005-12-06 ~ 2005-12-06
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL GCheckRaceAndInfluenceType(EN_CHECK_TYPE i_checkType
								, USHORT i_usRace, BYTE i_byInfluenceTy
								, USHORT i_usPeerRace, BYTE i_byPeerInfluenceTy)
{
	switch(i_checkType)
	{
	case CHECK_TYPE_TRADE:		// ������ ���� ���� ó�� �ʿ�, 2005-12-06 by cmkwon
		{
			if ( COMPARE_RACE(i_usRace, RACE_DEMO|RACE_GUEST|RACE_MONITOR|RACE_GAMEMASTER)
				|| COMPARE_RACE(i_usPeerRace, RACE_DEMO|RACE_GUEST|RACE_MONITOR|RACE_GAMEMASTER) )
			{
				return FALSE;
			}

			if(COMPARE_RACE(i_usRace, RACE_OPERATION))
			{// 2005-12-06 by cmkwon, �����ڵ� ������ ������ �ŷ� ����, ���� ������ �϶�
				if(FALSE == COMPARE_RACE(i_usPeerRace, RACE_OPERATION))
				{
					return FALSE;
				}
			}
			else if(COMPARE_RACE(i_usPeerRace, RACE_OPERATION))
			{// 2005-12-06 by cmkwon, �����ڵ� ������ ������ �ŷ� ����, ������ ������ �϶�
				if(FALSE == COMPARE_RACE(i_usRace, RACE_OPERATION))
				{
					return FALSE;
				}
			}
			else
			{
// 2006-05-18 by cmkwon, �Ʒ��� ���� ���� ������ �ƴϸ� �ŷ� �Ұ�
// 				if(COMPARE_INFLUENCE(i_byInfluenceTy, INFLUENCE_TYPE_ANI))
// 				{// �ݶ�����
// 					if(i_byInfluenceTy != i_byPeerInfluenceTy)
// 					{// �ٸ� �����ϰ�� �ŷ� �Ұ�
// 						return FALSE;
// 					}
// 				}
// 				else
// 				{// �Ϲݼ���, ���Լ���
// 					if(FALSE == COMPARE_INFLUENCE(i_byPeerInfluenceTy, INFLUENCE_TYPE_NORMAL|INFLUENCE_TYPE_VCN))
// 					{// �ٸ� �����ϰ�� �ŷ� �Ұ�
// 						return FALSE;
// 					}
// 				}

				if(COMPARE_INFLUENCE(i_byInfluenceTy, INFLUENCE_TYPE_NORMAL))
				{// �Ϲݼ����� �ŷ� �Ұ�
					return FALSE;
				}

				if(COMPARE_INFLUENCE(i_byPeerInfluenceTy, INFLUENCE_TYPE_NORMAL))
				{// �Ϲݼ����� �ŷ� �Ұ�
					return FALSE;
				}
				
				if(i_byInfluenceTy != i_byPeerInfluenceTy)
				{// 2006-05-18 by cmkwon, �ٸ� ������
					return FALSE;
				}
			}
		}
		break;
	case CHECK_TYPE_BAZAAR:		// 2006-08-07 by cmkwon
		{
			if ( COMPARE_RACE(i_usRace, RACE_DEMO|RACE_GUEST|RACE_MONITOR)
				|| COMPARE_RACE(i_usPeerRace, RACE_DEMO|RACE_GUEST|RACE_MONITOR) )
			{
				return FALSE;
			}

			if(COMPARE_RACE(i_usRace, RACE_OPERATION|RACE_GAMEMASTER)
				^ COMPARE_RACE(i_usPeerRace, RACE_OPERATION|RACE_GAMEMASTER))
			{// 2006-08-07 by cmkwon, �ڽŰ� ���� �߿� �Ѹ� ������ Ȥ�� ��� �϶�
				return FALSE;
			}			
		}
		break;

	case CHECK_TYPE_GUILD_JOIN:		// ������ ó�� �ʿ� ����, 2005-12-07 by cmkwon
		{
			if(COMPARE_INFLUENCE(i_byPeerInfluenceTy, INFLUENCE_TYPE_NORMAL))
			{// �Ϲݼ����� ���� ���� �Ұ�
				return FALSE;
			}
			if(i_byInfluenceTy != i_byPeerInfluenceTy)
			{// ������ �ٸ��� ���� ���� �Ұ�
				return FALSE;
			}
		}
		break;

	case CHECK_TYPE_PARTY_JOIN:
	case CHECK_TYPE_CHAT_SELL_ALL:		// 2005-12-07 by cmkwon
	case CHECK_TYPE_CHAT_CASH_ALL:		// 2005-12-07 by cmkwon
	case CHECK_TYPE_BATTLE_PARTY_WAR:		// 2006-01-05 by cmkwon
	case CHECK_TYPE_BATTLE_GUILD_WAR:		// 2006-01-05 by cmkwon
	case CHECK_TYPE_CHAT_WAR:			// 2008-05-19 by dhjin, EP3 - ä�� �ý��� ����, ���� ä��
		{// ���� ���¸� �����ϴ�
			if(i_byInfluenceTy != i_byPeerInfluenceTy)
			{
				//////////////////////////////////////////////////////////////////////////
				// 2006-10-12 by dhjin, �ٸ� ������ �Ұ�
				//if(FALSE == COMPARE_INFLUENCE(i_byInfluenceTy, INFLUENCE_TYPE_NORMAL|INFLUENCE_TYPE_VCN)
				//	|| FALSE == COMPARE_INFLUENCE(i_byPeerInfluenceTy, INFLUENCE_TYPE_NORMAL|INFLUENCE_TYPE_VCN))
				//{
				return FALSE;
				//}
			}
		}
		break;
#if _RAT_CHAT_SYSTEM
	case CHECK_TYPE_CHAT_INFLUENCE_ALL_RAT:
#endif
	case CHECK_TYPE_CHAT_PTOP:		// 2005-12-07 by cmkwon
	case CHECK_TYPE_VOIP_1to1:		// 2005-12-07 by cmkwon
		{
			///////////////////////////////////////////////////////////////////////////////
			// 1. �Ѹ��̶� ������, ���Ӹ����ʹ� ������ ����
			// 2. ������ �ٸ��� �Ұ�
			if(COMPARE_RACE(i_usRace, RACE_OPERATION|RACE_GAMEMASTER)
				|| COMPARE_RACE(i_usPeerRace, RACE_OPERATION|RACE_GAMEMASTER))
			{
				return TRUE;
			}
			if(i_byInfluenceTy != i_byPeerInfluenceTy)
			{
				if(COMPARE_INFLUENCE(i_byInfluenceTy, INFLUENCE_TYPE_NORMAL|INFLUENCE_TYPE_VCN)
					&& COMPARE_INFLUENCE(i_byPeerInfluenceTy, INFLUENCE_TYPE_NORMAL|INFLUENCE_TYPE_VCN))
				{
					return TRUE;
				}
				return FALSE;
			}
		}
		break;
	default:
		{
			return FALSE;
		}
	}
	
	return TRUE;
}

const char * GET_ARENA_STATE_STRING(BYTE i_byAState)
{
	switch(i_byAState)
	{
	case ARENA_STATE_NONE:					return "ARENA_STATE_NONE";
	case ARENA_STATE_JOINING:				return "ARENA_STATE_JOINING";
	case ARENA_STATE_READY:					return "ARENA_STATE_READY";
	case ARENA_STATE_READY_FINISH:			return "ARENA_STATE_READY_FINISH";
	case ARENA_STATE_FIGHTING_WARREADY:		return "ARENA_STATE_FIGHTING_WARREADY";
	case ARENA_STATE_FIGHTING_WARING:		return "ARENA_STATE_FIGHTING_WARING";
	case ARENA_STATE_FIGHTING_WARFINISH:	return "ARENA_STATE_FIGHTING_WARFINISH";
	}

	return "ARENA_STATE_UNKNOWN";
}

char *GetLeader8SubLeaderString(BYTE i_byInflTy, USHORT i_usRace)
{
	switch(i_byInflTy)
	{
	case INFLUENCE_TYPE_VCN:
		{
			if(COMPARE_RACE(i_usRace, RACE_INFLUENCE_LEADER))
			{
				return STRCMD_VCN_INFLUENCE_LEADER;
			}
			if(COMPARE_RACE(i_usRace, RACE_INFLUENCE_SUBLEADER_1))
			{
				return STRCMD_VCN_INFLUENCE_SUBLEADER_1;
			}
			if(COMPARE_RACE(i_usRace, RACE_INFLUENCE_SUBLEADER_2))
			{
				return STRCMD_VCN_INFLUENCE_SUBLEADER_2;
			}
		}
		break;
	case INFLUENCE_TYPE_ANI:
		{
			if(COMPARE_RACE(i_usRace, RACE_INFLUENCE_LEADER))
			{
				return STRCMD_ANI_INFLUENCE_LEADER;
			}
			if(COMPARE_RACE(i_usRace, RACE_INFLUENCE_SUBLEADER_1))
			{
				return STRCMD_ANI_INFLUENCE_SUBLEADER_1;
			}
			if(COMPARE_RACE(i_usRace, RACE_INFLUENCE_SUBLEADER_2))
			{
				return STRCMD_ANI_INFLUENCE_SUBLEADER_2;
			}
		}
		break;
	}

	return "";
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			INT CalcGradeByRate(float i_nMaxValue, float i_nValue, INT i_nRate)
/// \brief		���� ���� ǥ�� ��ȹ�� - ������ ���� ����� ����Ѵ�.
/// \author		dhjin
/// \date		2008-03-24 ~ 2008-03-24
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
INT CalcGradeByRate(float i_nMaxValue, float i_nValue, INT i_nRate)
{
	//////////////////////////////////////////////////////////////////////////
	//	i_nValue			 i_nRate
	//	-----------	 * 100 * -------  = i_nValue / i_nMaxValue * i_nRate
	//	i_nMaxValue			   100	
	//////////////////////////////////////////////////////////////////////////
	
	float CalcGrade = i_nValue / i_nMaxValue * i_nRate;
	INT	o_Grade = ceil(CalcGrade);

	return o_Grade;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		// 2009-10-22 by cmkwon, �ð� �������� ������ �ý��� ���� - 
/// \author		cmkwon
/// \date		2009-10-22 ~ 2009-10-22
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
inline int GetNumberOfBits(INT64 i_n64Mask)
{
	int nBits = 0;
    while( i_n64Mask )
    {
        i_n64Mask = i_n64Mask & ( i_n64Mask - 1 ); 
        nBits++;
    }
    return nBits;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		// 2009-11-02 by cmkwon, ĳ��(�κ�/â�� Ȯ��) ������ �߰� ���� - 
/// \author		cmkwon
/// \date		2009-11-02 ~ 2009-11-02
/// \warning	
///
/// \param		BYTE i_enStorage		==> ITEM_IN_XXX
/// \return		
///////////////////////////////////////////////////////////////////////////////
BYTE CHARACTER::GetAddedPermanentInventoryCount(BYTE i_enStorage/*=ITEM_IN_CHARACTER*/)
{
	BYTE by4Ret = 0;
	switch(i_enStorage)
	{
	case ITEM_IN_CHARACTER:				by4Ret = RacingPoint & 0xFF;			return min(by4Ret, SIZE_MAX_ADDABLE_INVENTORY_COUNT);
	case ITEM_IN_STORE:					by4Ret = (RacingPoint & 0xFF00)>>8;		return min(by4Ret, SIZE_MAX_ADDABLE_STORE_COUNT);
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		// 2009-11-02 by cmkwon, ĳ��(�κ�/â�� Ȯ��) ������ �߰� ���� - 
/// \author		cmkwon
/// \date		2009-11-03 ~ 2009-11-03
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CHARACTER::SetAddedPermanentInventoryCount(BYTE i_byAddCount, BYTE i_enStorage/*=ITEM_IN_CHARACTER*/)
{	
	switch(i_enStorage)
	{
	case ITEM_IN_CHARACTER:
		{
			RacingPoint &= ~(0xFF);
			RacingPoint |= i_byAddCount;
		}
		break;
	case ITEM_IN_STORE:
		{
			RacingPoint &= ~(0xFF00);
			RacingPoint |= ((int)i_byAddCount)<<8;
		}
		break;
	default:
		{
			return FALSE;
		}
	}
	return TRUE;
}

struct find_if_INT		// 2010-01-18 by cmkwon, ������ ���� Parameter �ߺ� üũ �ý��� ���� - 
{
	find_if_INT(INT i_findValue): m_findValue(i_findValue){};
	bool operator()(const INT i_nValue)
	{
		return m_findValue == i_nValue;
	}
	INT m_findValue;
};

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		// 2010-01-18 by cmkwon, ������ ���� Parameter �ߺ� üũ �ý��� ���� - 
/// \author		cmkwon
/// \date		2010-01-18 ~ 2010-01-18
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL ITEM::CheckParamOverlap(ITEM *i_pUsingItemInfo)
{
	if(NULL == this->pParamOverlapIdxList || NULL == i_pUsingItemInfo->pParamOverlapIdxList)
	{
		return TRUE;
	}
	
	vectINT *pMainVec	= this->pParamOverlapIdxList;
	vectINT *pSubVec	= i_pUsingItemInfo->pParamOverlapIdxList;
	if(this->pParamOverlapIdxList->size() > i_pUsingItemInfo->pParamOverlapIdxList->size())
	{
		pMainVec	= i_pUsingItemInfo->pParamOverlapIdxList;
		pSubVec		= this->pParamOverlapIdxList;
	}
	
	vectINT::iterator MItr(pMainVec->begin());
	for(; MItr != pMainVec->end(); MItr++)
	{
		INT OverlapIdx = *MItr;
		
		vectINT::iterator SItr = find_if(pSubVec->begin(), pSubVec->end(), find_if_INT(OverlapIdx));
		if(SItr != pSubVec->end())
		{
			return FALSE;
		}
	}
	
	return TRUE;
}


#ifdef _ATUM_SERVER
#include "VMemPool.h"

void * EVENTINFO::operator new(size_t size)
{
	return CVMemPool::vmObjectNew(size);
}

void EVENTINFO::operator delete(void* p)
{
	CVMemPool::vmObjectDelete(p, sizeof(EVENTINFO));
}

#ifndef _ATUM_ADMINTOOL		// 2005-11-26 by cmkwon
void * ITEM_GENERAL::operator new(size_t size)
{
	return CVMemPool::vmObjectNew(size);
}

void ITEM_GENERAL::operator delete(void* p)
{
	CVMemPool::vmObjectDelete(p, sizeof(ITEM_GENERAL));
}
#endif // end_#ifndef _ATUM_ADMINTOOL

void * ITEM_SKILL::operator new(size_t size)
{
	return CVMemPool::vmObjectNew(size);
}

void ITEM_SKILL::operator delete(void* p)
{
	CVMemPool::vmObjectDelete(p, sizeof(ITEM_SKILL));
}


// 2010-06-15 by shcho&hslee ��ý��� - �޸� Ǯ ���.
void * tPET_CURRENTINFO :: operator new(size_t size)
{
	return CVMemPool::vmObjectNew(size);
}

void tPET_CURRENTINFO :: operator delete(void* p)
{
	CVMemPool::vmObjectDelete(p, sizeof(tPET_CURRENTINFO));
}

// 2010-11 by dhjin, �ƶ󸮿� ä�θ� �α���.
char* GetConnectPublisherName(eCONNECT_PUBLISHER i_eCONNECT_PUBLISHER)
{
	switch(i_eCONNECT_PUBLISHER)
	{
	case CONNECT_PUBLISHER_NHN_JPN:
		{
			return "NHN";
		}
		break;
	default:
		{
			return "DEFAULT";
		}
	}
}
// 2011-11-18 by shcho, �����ٿ� ���������ٿ� ���� ó�� - �߰� ��ɹ� ����
BOOL CheckAdminCommand(char *token)
{

#ifdef S_GM_COMMAND_USE_SHCHO
	return FALSE;
#endif

	if(
	// ���� �ִ� ��ɾ�� �� �Ұ��� ó���Ѵ�.
	0 == stricmp(token, STRCMD_CS_COMMAND_ITEMINSERTbyKIND)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_ITEMINSERTbyKIND_1)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_ITEMINSERTbyKIND_HELP)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_ITEMINSERTbyITEMNUMRANGE)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_ITEMINSERTbyITEMNUMRANGE_1)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_ITEMINSERTbyITEMNUMRANGE_HELP)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_STATINIT)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_STATINIT_1)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_STATINIT_2)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_STATINIT_HELP)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_GAMETIME)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_GAMETIME_1)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_GAMETIME_HELP)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_STRINGLEVEL_0)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_STRINGLEVEL_1)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_STRINGLEVEL_2)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_STRINGLEVEL_HELP)
// 	|| 0 == stricmp(token, STRCMD_CS_COMMAND_ITEMINSERTALL)
// 	|| 0 == stricmp(token, STRCMD_CS_COMMAND_ITEMINSERTALL_1)
// 	|| 0 == stricmp(token, STRCMD_CS_COMMAND_ITEMINSERTALL_HELP)
// 	|| 0 == stricmp(token, STRCMD_CS_COMMAND_ITEMINSERTWEAPON)
// 	|| 0 == stricmp(token, STRCMD_CS_COMMAND_ITEMINSERTWEAPON_1)
// 	|| 0 == stricmp(token, STRCMD_CS_COMMAND_ITEMINSERTWEAPON_HELP)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_USERSINFOTOTAL)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_USERSINFOTOTAL_1)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_USERSINFOTOTAL_HELP)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_DEBUGPRINTDBG)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_DEBUGPRINTDBG_1)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_DEBUGPRINTDBG_HELP)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_DEBUGSETPARAMF)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_DEBUGSETPARAMF_HELP)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_VARIABLESET)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_VARIABLESET_1)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_VARIABLESET_HELP)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_DEBUGPRINTMSGF_0)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_DEBUGPRINTMSGF_1)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_DEBUGPRINTMSGF_HELP)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_GAMEEVENT)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_GAMEEVENT_1)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_GAMEEVENT_P1EXP)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_GAMEEVENT_P1SPI)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_GAMEEVENT_P1EXPR)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_GAMEEVENT_P1ITEM)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_GAMEEVENT_P1RARE)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_GAMEEVENT_P2END)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_GAMEEVENT_HELP)
//	|| 0 == stricmp(token, STRCMD_CS_COMMAND_CITYWAR)
//	|| 0 == stricmp(token, STRCMD_CS_COMMAND_CITYWAR_1)
//	|| 0 == stricmp(token, STRCMD_CS_COMMAND_CITYWAR_PSTART)
//	|| 0 == stricmp(token, STRCMD_CS_COMMAND_CITYWAR_PEND)
//	|| 0 == stricmp(token, STRCMD_CS_COMMAND_CITYWAR_HELP)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_HAPPYHOUREVENT)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_HAPPYHOUREVENT_1)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_HAPPYHOUREVENT_PSTART)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_HAPPYHOUREVENT_PEND)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_HAPPYHOUREVENT_HELP)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_DEBUGSETPARAMI)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_DEBUGSETPARAMI_HELP)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_REGISTERADMIN)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_REGISTERADMIN_1)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_REGISTERADMIN_HELP)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_DEBUGPRINTMSGI_0)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_DEBUGPRINTMSGI_1)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_DEBUGPRINTMSGI_HELP)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_SERVERDOWN)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_SERVERDOWN_1)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_SERVERDOWN_HELP)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_PASSWORDSET)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_PASSWORDSET_1)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_PASSWORDSET_HELP)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_PASSWORDROLLBACK)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_PASSWORDROLLBACK_1)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_PASSWORDROLLBACK_HELP)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_PASSWORDLIST)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_PASSWORDLIST_1)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_PASSWORDLIST_HELP)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_PASSWORDENCRYPT)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_PASSWORDENCRYPT_1)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_PASSWORDENCRYPT_HELP)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_ACCOUNTBLOCKLIST)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_ACCOUNTBLOCKLIST_1)
	|| 0 == stricmp(token, STRCMD_CS_COMMAND_ACCOUNTBLOCKLIST_HELP)
// 	|| 0 == stricmp(token, STRCMD_CS_COMMAND_ITEMINMAP_0)
// 	|| 0 == stricmp(token, STRCMD_CS_COMMAND_ITEMINMAP_1)
// 	|| 0 == stricmp(token, STRCMD_CS_COMMAND_ITEMINMAP_2)
// 	|| 0 == stricmp(token, STRCMD_CS_COMMAND_ITEMINMAP_HELP)
	)
		{
			return TRUE;
		}
	return FALSE;
}

// 2013-03-13 by hskim, �� ĳ�� ���� - RawData ���� ��� �߰�
char *StrCaseStr(const char *s, const char *find)
{
	char c, sc;
	size_t len;

	if ((c = *find++) != 0) {
		c = tolower((unsigned char)c);
		len = strlen(find);
		do {
			do {
				if ((sc = *s++) == 0)
					return (NULL);
			} while ((char)tolower((unsigned char)sc) != c);
		} while (_strnicmp(s, find, len) != 0);
		s--;
	}
	return ((char *)s);
}

char *StrRCaseStr(const char *s, const char *find)
{
	char c, sc;
	size_t len;

	if ((c = *find++) != 0) {
		c = tolower((unsigned char)c);
		len = strlen(find);
		do {
			do {
				if ((sc = *s++) == 0)
					return (NULL);
			} while ((char)tolower((unsigned char)sc) != c);
		} while (_strnicmp(s, find, len) != 0);
		s--;
	}

	return ((char *)s + len + 1);
}
// end 2013-03-13 by hskim, �� ĳ�� ���� - RawData ���� ��� �߰�

//void * ENCHANT::operator new(size_t size)
//{
//	return CVMemPool::vmObjectNew(size);
//}
//
//void ENCHANT::operator delete(void* p)
//{
//	CVMemPool::vmObjectDelete(p, sizeof(ENCHANT));
//}
#endif // _ATUM_SERVER

#if _RAT_RANK_SYSTEM

// 1. Initialize the table values exactly once here
std::map<int, SRANK_DATA> SRANK_SYSTEM::Table = {
	{ 1, { 1, "\\pTrainee",     0,    { 5.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.00f }}},
	{ 2, { 2, "\\cRookie",      5,    { 10.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.00f }}},
	{ 3, { 3, "\\gPilot",       25,   { 15.0f, 2.0f, 2.0f, 2.0f, 2.0f, 0.00f }}},
	{ 4, { 4, "\\yFlight_Lead", 100,  { 20.0f, 3.0f, 3.0f, 3.0f, 3.0f, 0.00f }}},
	{ 5, { 5, "\\rAce_Pilot",   500,  { 30.0f, 4.0f, 4.0f, 4.0f, 4.0f, 0.01f }}},
	{ 6, { 6, "\\eCommander",   1500, { 45.0f, 5.0f, 5.0f, 5.0f, 5.0f, 0.05f }}},
	{ 7, { 7, "\\bSky_Marshal", 5000, { 60.0f, 6.0f, 6.0f, 6.0f, 6.0f, 0.10f }}}
};

// 2. C++11/C++14 safe loop using standard pair iterators
SRANK_DATA SRANK_SYSTEM::GetRankByFame(int currentFame)
{
	// Default fallback row
	SRANK_DATA GrabbedTable = { 0, "\\gUnknown", 0, { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.00f } };

	// Classic map loop: 'it->first' is the Index, 'it->second' is the SRANK_DATA
	for (auto it = Table.begin(); it != Table.end(); ++it)
	{
		if (currentFame >= it->second.RequiredFame)
		{
			GrabbedTable = it->second; // Player qualifies! Save it.
		}
		else
		{
			return GrabbedTable; // Hit a rank too high, exit early with the last saved rank
		}
	}

	return GrabbedTable;
}

#endif // _RAT_RANK_SYSTEM