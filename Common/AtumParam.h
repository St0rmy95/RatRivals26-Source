///////////////////////////////////////////////////////////////////////////////
//		ĳ����, ����, ������ �Ķ���� ����
///////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ATUMPARAM_H)
#define AFX_ATUMPARAM_H

#include <math.h>
#include <d3dx9math.h>

#ifndef _ATUM_CLIENT
	#include "XOR_Lib.h"		// 2007-10-24 by cmkwon, ���� ���� ��ȣȭ - �߰���
#endif

#include <stdio.h>
#include "DebugAssert.h"
#include <string>
#include <vector>
#include <SQLTYPES.H>
#include "DefineGlobal.h"					// 2007-03-14 by cmkwon
#include "LocalizationDefineCommon.h"		// 2006-09-05 by cmkwon
#include "AtumDateTime.h"
#include "mt_stl.h"							// 2007-01-09 by cmkwon

#if defined(_ATUM_SERVER)
#include "GlobalFunc.h"						// 2008-06-26 by cmkwon, float -> int ����ȯ �Լ� �߰� - 
#endif

using namespace std;

// 2008-04-25 by cmkwon, ���� ���/���� �߰��� �� �߰� �Ǿ�� �ϴ� ���� - [���-�ʼ�] �߰� ��� ���� �߰�
#define LANGUAGE_TYPE_UNKNOWN			-1
#define LANGUAGE_TYPE_KOREAN			0
#define LANGUAGE_TYPE_ENGLISH			1
#define LANGUAGE_TYPE_JAPANESE			2
#define LANGUAGE_TYPE_CHINESE			3
#define LANGUAGE_TYPE_VIETNAMESE		4			// 2006-02-27 by cmkwon
#define LANGUAGE_TYPE_GERMAN			5			// 2008-04-25 by cmkwon, ���� �� ���Ͼ� �߰� - ��� ���� �߰�, Gameforge4D_Deu
#define LANGUAGE_TYPE_THAI				6			// 2008-04-11 by cmkwon, ���� ��� �߰� - �±���(Thai - Tha)
#define LANGUAGE_TYPE_RUSSIAN			7			// 2008-04-11 by cmkwon, ���� ��� �߰� - ���þƾ�(Russian - Rus)
#define LANGUAGE_TYPE_TAIWANESE			8			// 2008-09-02 by cmkwon, ���� ��� �߰�(�븸�� Taiwanese - Tpe) - 
#define LANGUAGE_TYPE_TURKISH			9			// 2008-10-20 by cmkwon, ���� ��� �߰�(��Ű��, �Ҿ�, ��Ż���ƾ�) - 
#define LANGUAGE_TYPE_FRENCH			10			// 2008-10-20 by cmkwon, ���� ��� �߰�(��Ű��, �Ҿ�, ��Ż���ƾ�) - 
#define LANGUAGE_TYPE_ITALIAN			11			// 2008-10-20 by cmkwon, ���� ��� �߰�(��Ű��, �Ҿ�, ��Ż���ƾ�) - 
#define LANGUAGE_TYPE_POLISH			12			// 2009-03-17 by cmkwon, ���� ��� �߰�(�������, �����ξ�) - Gameforge4D_Pol(PL)
#define LANGUAGE_TYPE_SPANISH			13			// 2009-03-17 by cmkwon, ���� ��� �߰�(�������, �����ξ�) - Gameforge4D_Esp(ES)
#define LANGUAGE_TYPE_ARGENTINA			14			// 2010-11-01 by shcho, Lin �Ƹ���Ƽ�� ���� ���� �غ� - ������� �߰�
#define LANGUAGE_TYPE_INDONESIA			15			// 2010-01-11 by shcho,	 ���� ���� �߰�(WinnerOnline �ε��׽þƾ�) -

#define LANGUAGE_TYPE_LAST				LANGUAGE_TYPE_INDONESIA		// 2009-03-17 by cmkwon, ���� ��� �߰�(�������, �����ξ�) - 
// 2008-04-11 by cmkwon, ���� ��� �߰� - �Ʒ��� ���� ����
//#define IS_VALID_LANGUAGE_TYPE(_lang)	((_lang) >= LANGUAGE_TYPE_KOREAN && (_lang) <= LANGUAGE_TYPE_VIETNAMESE)
#define IS_VALID_LANGUAGE_TYPE(_lang)	((_lang) >= LANGUAGE_TYPE_KOREAN && (_lang) <= LANGUAGE_TYPE_LAST)	// 2008-04-11 by cmkwon, ���� ��� �߰� - 

extern char *GET_LANGUAGE_TYPE_STRING(int i_nLangTy);	// 2008-04-25 by cmkwon, ���� �� ���Ͼ� �߰� - Gameforge4D_Deu �߰�

// 2013-10-15 by bckim, ������ �������� ���� ��Ʈ�� ���� COMMON_STRMSG_REG_KEY_NAME_WINDOWDEGREE_NEW
// exe �� ���Ŀ��� ��� 
#define COMMON_STRMSG_VERSION_INFO_FILE_NAME				"VersionInfo.ver"
#define COMMON_STRMSG_REG_KEY_NAME_LAUNCHER_VERSION			"LauncherVersion"			
#define COMMON_STRMSG_REG_KEY_NAME_CLIENT_VERSION			"ClientVersion"			
#define COMMON_STRMSG_REG_KEY_NAME_WINDOWDEGREE_NEW			"WindowDegreeNew"
#define COMMON_STRMSG_REG_KEY_NAME_WINDOWMODE				"WindowMode"
#define COMMON_STRMSG_REG_KEY_NAME_ACCOUNT_NAME				"AccountName"
#define COMMON_STRMSG_REG_KEY_NAME_SERVER_GROUP_NAME		"ServerGroupName"		// ??
// End. 2013-10-15 by bckim, ������ �������� ���� ��Ʈ�� ����

// start 2011-12-12 by hskim, GLog 2��

#ifdef SERVICE_TYPE_KOREAN_SERVER_1
#define SERVICE_COUNTRY_STRING		"Korea_MS"
#endif

#ifdef SERVICE_TYPE_KOREAN_SERVER_2
#define SERVICE_COUNTRY_STRING		"Korea_YD"
#endif

#ifdef SERVICE_TYPE_ENGLISH_SERVER_1
#define SERVICE_COUNTRY_STRING		"Canada"
#endif

#ifdef SERVICE_TYPE_ENGLISH_SERVER_2
#define SERVICE_COUNTRY_STRING		"England"
#endif

#ifdef SERVICE_TYPE_GERMAN_SERVER_1
#define SERVICE_COUNTRY_STRING		"Germany"
#endif

#ifdef SERVICE_TYPE_CHINESE_SERVER_1
#define SERVICE_COUNTRY_STRING		"China"
#endif

#ifdef SERVICE_TYPE_VIETNAMESE_SERVER_1
#define SERVICE_COUNTRY_STRING		"Vietnam"
#endif

#ifdef SERVICE_TYPE_THAI_SERVER_1
#define SERVICE_COUNTRY_STRING		"Thailand"
#endif

#ifdef SERVICE_TYPE_SINGAPORE_1
#define SERVICE_COUNTRY_STRING		"Singapore"
#endif

#ifdef SERVICE_TYPE_INDONESIA_SERVER_1
#define SERVICE_COUNTRY_STRING		"Indonesia"
#endif

#ifdef SERVICE_TYPE_RUSSIAN_SERVER_1
#define SERVICE_COUNTRY_STRING		"Russia"
#endif

#ifdef SERVICE_TYPE_TAIWANESE_SERVER_1
#define SERVICE_COUNTRY_STRING		"Taiwan"
#endif

#ifdef SERVICE_TYPE_JAPANESE_SERVER_1
#define SERVICE_COUNTRY_STRING		"Japan"
#endif

#ifdef SERVICE_TYPE_TURKISH_SERVER_1
#define SERVICE_COUNTRY_STRING		"Turkey"
#endif

#ifdef SERVICE_TYPE_ITALIAN_SERVER_1
#define SERVICE_COUNTRY_STRING		"Italy"
#endif

#ifdef SERVICE_TYPE_FRENCH_SERVER_1
#define SERVICE_COUNTRY_STRING		"France"
#endif

#ifdef SERVICE_TYPE_POLISH_SERVER_1
#define SERVICE_COUNTRY_STRING		"Poland"
#endif

#ifdef SERVICE_TYPE_SPANISH_SERVER_1
#define SERVICE_COUNTRY_STRING		"Spain"
#endif

#ifdef SERVICE_TYPE_ARGENTINA_SERVER_1
#define SERVICE_COUNTRY_STRING		"Argentina"
#endif

#ifdef SERVICE_TYPE_GLOBAL_SERVER_1							// 2013-09-04 by jhseol, �۷ι� ���� ����ɼ� �߰�
#define SERVICE_COUNTRY_STRING		"Masang_Global"
#endif
// end 2011-12-12 by hskim, GLog 2��

// 2009-12-28 by cmkwon, ����ȸ�� IP ���� - ����(121.134.114.)
#define MASANG_PREFIX_IP1				"127.0.0."//"115.144.35."//"61.39.170."			// 2014-10-17 by ymjoo ���� ��� �繫�� ip ��� // 2010-01-18 by cmkwon, ���� ���� �繫��, // 2007-01-03 by cmkwon, MasangSoft �����͹̳η� ����
#define MASANG_PREFIX_IP2				"127.0.0."			// 2010-01-18 by cmkwon, ���� �д� �繫��, // 2009-03-02 by cmkwon, ���� �׼����� ĳ�� ����Ʈ ���� ����(����� ���ø� ����) - 2�� ����, // 2007-01-03 by cmkwon, MasangSoft �����͹̳η� ����
#define IS_MASANG_IP(ip)				(0 == strncmp((ip),MASANG_PREFIX_IP1,strlen(MASANG_PREFIX_IP1)) || 0 == strncmp((ip),MASANG_PREFIX_IP2,strlen(MASANG_PREFIX_IP2)))

#define MASANG_LIVE_PC_IP				"127.0.0.1"			// 2012-06-25 by hskim, ���̺� ����� ȯ�� ���� 


///////////////////////////////////////////////////////////////////////////////
// Atum Type ����
typedef INT64		TimeUnit_t;				// milli-seconds
typedef SHORT		Stat_t;					// �� ���� ��
typedef BYTE		TimerEventType;			// Ÿ�̸� �̺�Ʈ Ÿ��, TE_TYPE_XXX
typedef UINT64		PartyID_t;				// ��Ƽ ���̵�, PartyID(PartyUnqiueNumber + CreationTime)
typedef BYTE		BitFlag8_t;				// 8 bit flag
typedef USHORT		BitFlag16_t;			// 16 bit flag
typedef UINT		BitFlag32_t;			// 32 bit flag
typedef ULONGLONG	BitFlag64_t;			// 64 bit flag
typedef double		Experience_t;			// ����ġ
#define COMPARE_BIT_FLAG(VAR, MASK)	(((VAR) & (MASK)) != 0)
#define SET_BIT_FLAG(VAR, MASK)		{(VAR) |= (MASK);}
#define CLEAR_BIT_FLAG(VAR, MASK)	{(VAR) &= ~(MASK);}
typedef short		Prob256_t;				// Ȯ�� [0, 256)
#define PROB256_MAX_VALUE	255
typedef short		Prob100_t;				// Ȯ�� [0, 100]
// 2010-07-19 by dhjin, Ȯ�� ���� ����
// #define PROB100_MAX_VALUE	99	// 2010-07-19 by dhjin, Ȯ�� ���� ����
#define PROB100_MAX_VALUE	100
typedef short		Prob1000_t;				// Ȯ�� [0, 1000)
#define PROB1000_MAX_VALUE	999
typedef short		Prob10K_t;				// Ȯ�� [0, 10000)
#define PROB10K_MAX_VALUE	9999
typedef int			Prob100K_t;				// Ȯ�� [0, 100000)
#define PROB100K_MAX_VALUE	99999
typedef int			Prob1000K_t;			// Ȯ�� [0, 1000000)
#define PROB1000K_MAX_VALUE	999999
typedef USHORT ChannelIndex_t;
typedef USHORT MapIndex_t;
const char *Int2String(int n, string &str);	// convert integer to string
#define INT2STRING(x)	Int2String(x, string())
typedef USHORT	Err_t;
typedef vector<UINT>		vectUINT;		// 2009-09-17 by cmkwon, B��� ü�� ���� - 

///////////////////////////////////////////////////////////////////////////////
// 2008-04-16 by cmkwon, ���� ��� �� ���� ��ȯ �̺�Ʈ �ý��� ���� - 
#define MILLISECOND_TO_SECOND(ms)			((int)((ms)/1000))		// 2008-04-16 by cmkwon, ���� ��� �� ���� ��ȯ �̺�Ʈ �ý��� ���� - MilliSecond �� Second �� �����ϴ� ������ �߰�
#define Prob256_TO_Prob10K(pro)				(((pro)==PROB256_MAX_VALUE) ? PROB10K_MAX_VALUE : (Prob10K_t)((pro)*39.0625f))	// 2008-04-16 by cmkwon, ���� ��� �� ���� ��ȯ �̺�Ʈ �ý��� ���� - 256 Ȯ���� 10K Ȯ���� ����
#define MAX_DELAY_TIME_AT_EVENT_MONSTER		600		// 2008-04-17 by cmkwon, 600 �� = 10 ��

typedef enum
{
	MGAME_EVENT_NO_EVENT				= 0,
	MGAME_EVENT_OPEN_BETA_ATTENDANCE	= 1,			// ���º�Ÿ �⼮ �̺�Ʈ
} MGAME_EVENT_t;

typedef USHORT	UID16_t;	// 2 Bytes Unique IDentifier, 0�̰ų� INVALID_UID16�̸� �߸��� UID��, ������ UniqueNumber�� �ش�, 20040722, kelovon
typedef UINT32	UID32_t;	// 4 Bytes Unique IDentifier, 0�̰ų� INVALID_UID32�̸� �߸��� UID��, ������ UniqueNumber�� �ش�, 20040722, kelovon
typedef UINT64	UID64_t;	// 8 Bytes Unique IDentifier, 0�̰ų� INVALID_UID64�̸� �߸��� UID��, ������ UniqueNumber�� �ش�, 20040722, kelovon
#define INVALID_UID16		((UID16_t)~0)
#define INVALID_UID32		((UID32_t)~0)
#define INVALID_UID64		((UID64_t)~0)
#define INVALID_GUILD_UID	0				// 2005-02-04 by cmkwon

// Atum Defined SQL_C_XXX
#define SQL_C_PROB256		SQL_C_SHORT
#define SQL_C_PROB100		SQL_C_SHORT
#define SQL_C_PROB1000		SQL_C_SHORT
#define SQL_C_PROB10K		SQL_C_SHORT
#define SQL_C_PROB100K		SQL_C_LONG	
#define SQL_C_PROB1000K		SQL_C_LONG	
#define SQL_C_UID16			SQL_C_USHORT
#define SQL_C_UID32			SQL_C_ULONG
#define SQL_C_UID64			SQL_C_UBIGINT


// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���Ǵ�Ƽ ���� Type ����
typedef INT			MSec_t;				// MilliSecond ���� ǥ��
typedef INT			HPActionUID_t;		// HPActionUID	Type
typedef INT			HPActionIdx_t;		// HPActionIndex Type
typedef BYTE		HPValueRate_t;		// HPValueRate Type
typedef INT			ItemIdx_t;			// ItemIndex Type
typedef BYTE		HPHitRate_t;		// HPHitRate Type
typedef INT			HPUseCount_t;		// HPUseCount Type	
typedef BYTE		HPTalkCondition_t;	// HPTalkCondition Type
typedef BYTE		HPTalkImportance_t; // HPTalkImportance Type
typedef char		HPTalk_t;			// HPTalk Type
typedef float		MonHP_t;			// MonsterHP Type
typedef	INT			CinemaNum_t;		// CinemaNum Type
typedef	INT			CinemaOrder_t;		// CinemaOrder Type
typedef	INT			RevisionNum_t;		// RevisionNum Type
typedef	USHORT		RevisionHP_t;		// RevisionHP Type
typedef	USHORT		RevisionDP_t;		// RevisionDP Type
typedef	INT			RevisionWeapon1_t;	// RevisionStandardWeapon Type
typedef	INT			RevisionWeapon2_t;	// RevisionAdvancedWeapon Type
typedef INT			EffectIdx_t;		// EffectIndex Type
typedef FLOAT		Position_t;			// Position Type
typedef INT			EffectPlayCount_t;	// EffectPlayCount Type
typedef short		ObjectIdx_t;		// ObjectIndex Type
typedef INT			ObjectNum_t;		// ObjectNumber Type
typedef INT			MonIdx_t;			// MonsterIdx Type
typedef BYTE		InfiMonTargetType_t;	// InfinityMonster Target Type
typedef BYTE		InfiMonTargetCount_t;	// InfinityMonster TargetCount Type
typedef INT			InfiModeUID_t;		// InfinityModeUID Type
typedef BYTE		ResetCycle_t;		// ResetCycle Type
typedef BYTE		EntranceCount_t;	// EntranceCount Type
typedef INT			Minute_t;			// Minute ���� ǥ��
typedef BYTE		Lv_t;				// Level Type
typedef BYTE		AdmissionCount_t;	// AdmissionCount Type
typedef UID64_t		ImputeUID_t;		// ImputeUID Type
typedef UID64_t		InfinityCreateUID_t;		// InfinityCreateUID Type
typedef BYTE		ChangeTarget_t;		// ChangeTarget Type
typedef UID32_t		KillCnt_t;			// KillCount Type
typedef UID32_t		DeathCnt_t;			// DeathCount Type
typedef UID32_t		TenderUID_t;		// TenderUID Type
typedef INT			ItemNum_t;			// ItemNum Type		// 2010-01-26 by cmkwon, ĳ�� ������ �����Ǹ� �ý��� ���� - Ÿ�� ���� �߰�(���� UID32_t)
typedef BYTE		DiceCnt_t;			// DiceCount Type
typedef char		CinemaTalk_t;		// CinemaTalk Type
typedef	float		ParamValue_t;		// Item ParamValue Type
typedef	UID32_t		InfinityShopUID_t;	// InfinityShopUID Type			// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ����
typedef UID32_t		InfinityShopItemCnt_t;	// InfinityShopItemCount Type // 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ����
typedef USHORT		DestParam_t;		// 2011-08-01 by hskim, ��Ʈ�� �ý��� 2�� - �ڷ��� ���� (DestParameter - 255 -> 32767 ����) - // DestParam Type	// 2009-09-09 ~ 2010-02-10 by dhjin, ���Ǵ�Ƽ - �ߵ�������������
typedef INT			InvokingDestParamID_t;	// InvokingDestParamID Type	// 2009-09-09 ~ 2010-02-10 by dhjin, ���Ǵ�Ƽ - �ߵ�������������
typedef UID64_t		ItemUID_t;			// ItemUID Type		// 2009-09-09 ~ 2010-02-10 by dhjin, ���Ǵ�Ƽ - �ߵ�������������
typedef char		FileName_t;			// FileName Type		// 2010-03-31 by dhjin, ���Ǵ�Ƽ(�������) -
typedef INT			SummonCnt_t;		// SummonCount Type		// 2010-03-31 by dhjin, ���Ǵ�Ƽ(�������) -
typedef INT			Distance_t;			// Distance Type		// 2010-03-31 by dhjin, ���Ǵ�Ƽ(�������) -
typedef INT			QuestIndex_t;		// QuestIndex Type		// 2011-03-09 by hskim, ���Ǵ�Ƽ 3�� - �ó׸� ����Ʈ �ε��� ���� �߰�
typedef	BYTE		KeyMonster_t;		// KeyMonster Type		// 2011-04-21 by hskim, ���Ǵ�Ƽ 3�� - �ó׸� �ܰ躰 ��� ����
typedef INT			CustomIdx_t;		// CustomIdx Type		// 2011-04-28 by hskim, ���Ǵ�Ƽ 3�� - �ó׸� ���� ��� �߰�
typedef INT			Penalty_t;			// Penalty Type			// 2011-06-14 by hskim, ���Ǵ�Ƽ 3�� - �г�Ƽ ��� �߰� (HP �� �ð� ���� ������ ����)					

// start 2011-10-28 by hskim, EP4 [Ʈ���� �ý���] - ũ����Ż �ý���
typedef INT			MapTriggerID_t;			// MapTriggerID Type
typedef INT			FunctionID_t;			// FunctionID Type
typedef INT			CrystalGroupID_t;		// CrystalGroupID Type
typedef INT			DestroyGroupID_t;		// DestroyGroupID Type
typedef INT			EventID_t;				// EventID Type
typedef SHORT		SequenceNumber_t;		// SequenceNumber Type
typedef INT			NGCInflWarGroupID_t;	// NGCInflWarGroupID Type
typedef INT			SummonMosterGroupID_t;	// 2013-01-21 by jhseol, NGC �������� Ʈ���� �ý��� - ��ȯ ���� �׷� ID

typedef enum
{
	MAP_TRIGGER_NONE			= 0,		// ����
	MAP_TRIGGER_CRYSTAL			= 1,		// ũ����Ż �ý���
	MAP_TRIGGER_NGC_INFL_WAR	= 2			// NGC ������
	,MAP_TRIGGER_NGC_OUTPOST	= 3			// 2013-01-21 by jhseol, NGC �������� Ʈ���� �ý��� - ����������

} MapTriggerType_t;						// MapTriggerType Type
// end 2011-10-28 by hskim, EP4 [Ʈ���� �ý���] - ũ����Ż �ý���

// start 2012-01-16 by hskim, ��� - ȭ��
typedef INT64		StatisticsMoneyUnit_t;	// Money Type			

typedef enum
{
	STATISTICS_SPI = 0,
	STATISTICS_WAR_POINT,
	STATISTICS_SYSTEM_ORB,
	STATISTICS_QUASAR_ORB,
	STATISTICS_CLUSTER_ORB,
	STATISTICS_GALAXY_ORG,
	STATISTICS_UNIVERSE_ORB,

	STATISTICS_KIND_END

} StatisticsMoneyKind;

#define STATISTICS_MONEY_FUNCTION_ADD	0		// ȹ��
#define STATISTICS_MONEY_FUNCTION_SUB	1		// ���
#define STATISTICS_MONEY_FUNCTION_MAX	2		// ��ü Function ����

struct SSTATISTICS_MONEY_UNIT
{
	StatisticsMoneyUnit_t System;
	StatisticsMoneyUnit_t Quasar;
	StatisticsMoneyUnit_t Cluster;
	StatisticsMoneyUnit_t Galaxy;
	StatisticsMoneyUnit_t Universe;
	StatisticsMoneyUnit_t SPI;

	void operator+=(const SSTATISTICS_MONEY_UNIT &MoneyOrg)
	{
		this->System += MoneyOrg.System;
		this->Quasar += MoneyOrg.Quasar;
		this->Cluster += MoneyOrg.Cluster;
		this->Galaxy += MoneyOrg.Galaxy;
		this->Universe += MoneyOrg.Universe;
		this->SPI += MoneyOrg.SPI;
	}

	void operator-=(const SSTATISTICS_MONEY_UNIT &MoneyOrg)
	{
		this->System -= MoneyOrg.System;
		this->Quasar -= MoneyOrg.Quasar;
		this->Cluster -= MoneyOrg.Cluster;
		this->Galaxy -= MoneyOrg.Galaxy;
		this->Universe -= MoneyOrg.Universe;
		this->SPI -= MoneyOrg.SPI;
	}
};
// end 2012-01-16 by hskim, ��� - ȭ��

// start 2011-04-28 by hskim, ���Ǵ�Ƽ 3�� - �ó׸� ���� ��� �߰�
typedef enum
{
	CINEMA_MONSTER_INDEX_CREATE				= 0,		// ���� ����
	CINEMA_MONSTER_INDEX_DESTORY			= 1,		// ���� �ı�
	CINEMA_MONSTER_INDEX_CHANGE				= 2,		// ���� ��ü
	CINEMA_MONSTER_INDEX_REGEN_ON			= 3,		// ���� ���� ON ����
	CINEMA_MONSTER_INDEX_REGEN_OFF			= 4			// ���� ���� OFF ����
} eCINEMA_MONSTER_INDEX_TYPE;
// end 2011-04-28 by hskim, ���Ǵ�Ƽ 3�� - �ó׸� ���� ��� �߰�

// 2010-01-18 by cmkwon, ������ ���� Parameter �ߺ� üũ �ý��� ���� - �Ʒ��� �ִ����� ���� �������� �ű�
typedef vector<INT>				vectINT;					// 2008-01-31 by cmkwon, �ð����� ������ DB �� �߰� �� üũ - 


// 2012-11-21 by bckim, �������߰�, ��æƮ���������ű��
struct SUB_ENCHANT_INFO
{
	INT		nNumber;
	INT		nSubEnchantItemNum;
	INT		nEnchantCount;
	UINT64		SequenceNumber_DB;		// 2013-07-01 by bckim, 10��æƮ �̸� ������ī��ó��, �α��߰�, ��� ����
};
typedef vector<SUB_ENCHANT_INFO>	vectSUB_ENCHANT_INFO;
// 2012-11-21 by bckim, �������߰�, ��æƮ���������ű��. End

///////////////////////////////////////////////////////////////////////////////
// START - Atum VECTOR3 ����
typedef SHORT		CoordUnit_t;			// ��ǥ�� ����

typedef struct _AVECTOR3
{
	CoordUnit_t	x;
	CoordUnit_t	y;
	CoordUnit_t	z;

	_AVECTOR3() { Reset(); }
	_AVECTOR3(CoordUnit_t i_x, CoordUnit_t i_y, CoordUnit_t i_z)
	{
		x = i_x;
		y = i_y;
		z = i_z;
	}

	inline _AVECTOR3& operator=(const D3DXVECTOR3& rhs)
	{
		this->x = (CoordUnit_t)rhs.x;
		this->y = (CoordUnit_t)rhs.y;
		this->z = (CoordUnit_t)rhs.z;
		return *this;
	}

	inline D3DXVECTOR3& CopyA2DX(D3DXVECTOR3& outVec)
	{
		outVec.x = (float)this->x;
		outVec.y = (float)this->y;
		outVec.z = (float)this->z;
		return outVec;
	}

	inline void Reset()
	{
		x = y = z = 0;
	}
} AVECTOR3;		// Atum Protocol�� Vector

#define A2DX(vec3)		(D3DXVECTOR3(vec3.x, vec3.y, vec3.z))			// Convert AVECTOR3 to D3DXVECTOR3
#define AP2DX(pVec3)	(D3DXVECTOR3(pVec3->x, pVec3->y, pVec3->z))		// Convert AVECTOR3* to D3DXVECTOR3
// END - Atum VECTOR3 ����
///////////////////////////////////////////////////////////////////////////////

struct STRNBUF
{
	STRNBUF(int i_nSize) { szBuf = new char[i_nSize]; memset(szBuf, 0, i_nSize); nSize = i_nSize; }
	~STRNBUF() { if (szBuf != NULL) {delete(szBuf); szBuf = NULL;} nSize = 0; }

	char* GetBuffer() { return szBuf; }
	int GetSize() { return nSize; }

private:
	char	*szBuf;
	int		nSize;
};

inline float GGetLength(float x, float z)
{
	return sqrtf(x * x + z * z);
}

extern char CONFIG_ROOT[1024];

#ifndef __NPCID_T__
#define __NPCID_T__
typedef INT	NPCID_t;
typedef INT	NPCScriptID_t;
#endif// end__NPCID_T__

#define MAKEUINT32(low, high) ( (UINT)((USHORT)(low)) | ((UINT)((USHORT)(high)) << 16) )
#define MAKEUINT64(low, high) ( (UINT64)((UINT)(low)) | ((UINT64)((UINT)(high)) << 32) )

#define VALID_ATTACK_DISTANCE					100.0f		// Lock On, Attack ���ÿ� �ʿ��� �⺻ �Ÿ���
#define VALID_ATTACK_PINPOINT					0.523f		// 3.14 * 1/6 ==> 30��

#define SIZE_OTHER_SERVER_LIST					20			// �ٸ� �������� ���� IOCPSocket�� Array Server�� �Ҵ�

#define SIZE_MAX_CLIENT_REPORT					256
#define SIZE_MAX_VERSION						4		// Client Version
#define SIZE_MIN_CHARACTER_NAME					2		// 2006-03-16 by cmkwon, �ּ� ĳ���͸� Character Name
#define SIZE_MAX_CHARACTER_NAME					20		// Character Name
#define SIZE_MAXUSE_CHARACTER_NAME				15		// 2006-05-19 by cmkwon, �ִ�� 20bytes ������ �����δ� 15Bytes������ ��� ����
#define SIZE_MAX_NICK_NAME						SIZE_MAX_CHARACTER_NAME		// 2009-02-12 by cmkwon, EP3-3 ���巩ŷ�ý��� ���� - 

// 2008-10-08 by cmkwon, �븸 2�ܰ� ���� �ý��� ���� ����(email->uid) - 
#if !defined(SIZE_MAX_ACCOUNT_NAME)
#define SIZE_MAX_ACCOUNT_NAME					20		// 1�� ���� �̿ܿ� ���� 2�� ���� ������, ��κ��� �̰��� ����Ѵ�.
#endif
#if !defined(SIZE_MAX_ORIGINAL_ACCOUNT_NAME)
#define SIZE_MAX_ORIGINAL_ACCOUNT_NAME			20		// 2008-10-08 by cmkwon, �븸 2�ܰ� ���� �ý��� ���� ����(email->uid) - �����ÿ��� ���� 1�� ���� ������
#endif

#define SIZE_MAX_CITY_NAME						40
#define SIZE_MAX_PASSWORD						20		// 6 ~ 16, �� ���� �ٲٸ� FtpPassword������ UpdateFileList�� ��� �ٲ�� �ϹǷ� ���� ��!
#define SIZE_MAX_PASSWORD_MD5					16		//
#define SIZE_MAX_PASSWORD_MD5_STRING			33		// 32 characters
#define SIZE_MAX_GUILD_NAME						30
#define SIZE_MAX_GUILD_MARK_IMAGE				1600	// bytes, 20x20 4Bytes image
#define SIZE_MAX_SERVER_NAME					20		// SIZE_MAX_SERVER_GROUP_NAME
#define SIZE_MAX_MAP_NAME						40
#define SIZE_MAX_MAP_DESCRIPTION				1024		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - 
#define SIZE_MAX_PET_NAME						40		// 2010-06-16 by hslee, 20 --> 40
#define SIZE_MAX_PET_OPERATOR_DESCRIPTION		128		// 2010-12-03 by shcho, �� �ý��� ���� ��Ʈ�� ���ø����̼� �߰�
#define SIZE_MAX_MONSTER_NAME					40		// 2005-12-19 by cmkwon, 20 --> 40
#define SIZE_MAX_BUILDING_NAME					40		// 2008-01-03 by cmkwon, BuildingName �ʵ� 40Bytes �� ���� - , // = SIZE_MAX_SHOP_NAME
// 2008-01-03 by cmkwon, BuildingName �ʵ� 40Bytes �� ���� - ������� ����
//#define SIZE_MAX_SHOP_NAME						20		// = SIZE_MAX_BUILDING_NAME
#define SIZE_MAX_NPC_NAME						40
#define SIZE_MAX_NPC_TALK_STRING				2000	// 2005-10-18 by cmkwon, 1000���� 2000���� ������, string1024�� string2048�� ��������
#define SIZE_MAX_BUILDING_NPC_TALK_STRING		1000	// 2005-10-18 by cmkwon, �������� SIZE_MAX_NPC_TALK_STRING�� ���� �����
#define SIZE_MAX_QUEST_NAME						40
#define SIZE_MAX_RARE_FIX_NAME					30
#define SIZE_MAX_ITEM_NAME						40
#define SIZE_MAX_ITEM_DESCRIPTION				300		// 2015-02-12 SIZE_MAX_ITEM_DESCRIPTION �� 200���� 300���� ����
#define SIZE_MAX_NUM_CHARACTER					3
#define SIZE_MAX_CHAT_MESSAGE					100			// 2006-05-04 by cmkwon, 60-->100
#define SIZE_MAX_ERROR_STRING					512	//60	// 2013-09-23 by jekim, ���� ������ �޼��� �ѷ��ֱ�. 60->512 ����
#define SIZE_MAX_A_LOG_LINE						1400		// check: SIZE_MAX_PACKET - 92 !!!
#define SIZE_MAX_LOG_ACTION_STRING				1000		// check: SIZE_MAX_A_LOG_LINE - N
#define SIZE_MAX_WORKSPACE_FILE_NAME			40			// Map���� Workspace File Name Size
#define SIZE_MAX_PROJECT_FILE_NAME				40			// Map���� Project File Name Size
#define SIZE_MAX_EVENT_PARAM_NAME				40			// Map���� Event Param Name Size
#define SIZE_MAX_MONSTER_REGION_NAME			40			// Map���� Event Param Name Size
#define SIZE_MAX_NUM_MEMBER_IN_PARTY			8
#define HEIGHT_FLYING_ALTITUDE					30
#define SIZE_MAX_MAP_PER_A_FIELD_SERVER			100
#define SIZE_MAX_BLOCK_ELEMENT					100
#define MONSTER_CLIENT_INDEX_START_NUM			((ClientIndex_t)10000)		// monster�� client index�� ���� ��ȣ
#define MONSTER_CLIENT_INDEX_END_NUM			((ClientIndex_t)15000)		// monster�� client index�� ���� ��ȣ
#define SIZE_MAX_WARP_TARGET_NAME				40
#define SIZE_MAX_CITY_BRIEFING_LENGTH			100
#ifndef SIZE_MAX_IPADDRESS
	#define SIZE_MAX_IPADDRESS					16		// string IP Address
#endif
#define SIZE_MAX_OBJECT_NAME					40
#define SIZE_MAX_COUPON_NUMBER					30
#define SIZE_MAX_BLOCKED_ACCOUNT_REASON			200
#define SIZE_MAX_SERVICE_COUNTRY				40		// 2011-12-12 by hskim, GLog 2��
#define SIZE_MAX_WEB_AUTHENTICATION_KEY			65		// 2013-03-13 by hskim, �� ĳ�� ����
#define SIZE_MAX_TEMP_SYSTEM_STRING				1024	// 2013-05-20 by hskim, [���� �ý���] ���������� ������� ������ �߰� ����

#define SIZE_MAX_PACKET_PADDING					2		// 2012-12-22 by hskim, ���� ���� ���� - ���� ������ ȣȯ �ȵǵ��� ����ü ũ�� �ٲ�

// 2006-09-04 by cmkwon, LocalizationDefineCommon.h ȭ�Ͽ� ����
//#define SIZE_MAX_GUILD_MEMBER_CAPACITY			60		// �ִ� ���� ���� ��
//#define SIZE_MAX_INITIAL_GUILD_CAPACITY			40		// �ʱ� ��� ���� �� ���� ���� ��
#define ROLLING_USE_INTERVAL_TICK				3000	// �Ѹ� ���� �ð�, // 2005-11-18 by cmkwon, 4��->3��
#define ROLLING_USE_CONSUMPTION_SP				3		// �Ѹ� ���� �Ҹ�Ǵ� SP, // 2005-11-18 by cmkwon, 5->3


#define MAX_ITEM_COUNTS							2000000000					// �ִ� ������ ī��Ʈ(20��)
#define MAX_NOTIFY_ITEM_COUNTS					(MAX_ITEM_COUNTS-100000000)	// �ִ� ��� ������ ī��Ʈ(19�� = 20��-1��)
#define ITEM_NOT_USING							0							// ���ð��� �ִ� �������� ��� ������� �ƴϴ�
#define	MAX_ITEM_COUNTS_FOR_BUY					10							// 2008-07-16 by cmkwon, ITEM_GENERAL ���� ���� üũ - �������� ��ī��Ʈ�� ������ ���� ������ �ִ� ����, �ǸŴ� ��� ����.

#define SIZE_MAX_SZQUERY						2000			// 2007-01-30 by dhjin, ���� �ϼ��� ���� ��Ʈ�� ũ��
#define SIZE_MAX_TABLE_NAME						128				// 2008-08-27 by cmkwon, �������� Procedure�� ���� - 

// Client Index ����
#if defined(_ATUM_FIELD_SERVER) || defined(_ATUM_NPC_SERVER)
#define CLIENT_INDEX_START_NUM					((ClientIndex_t)SIZE_MAX_UDP_CHANNEL_SESSION)	// 2008-08-29 by cmkwon, FieldServ<->NPCServ �� UDP ��� �� ä�μ� - // client index�� ���� ��ȣ
#elif defined(_ATUM_IM_SERVER)
#define CLIENT_INDEX_START_NUM					((ClientIndex_t)1)		// client index�� ���� ��ȣ
#else
#define CLIENT_INDEX_START_NUM					((ClientIndex_t)0)		// 2008-08-29 by cmkwon, FieldServ<->NPCServ �� UDP ��� �� ä�μ� - // client index�� ���� ��ȣ
#endif
#define CLIENT_INDEX_FIELDSERVER_NUM			60001					// 2011-03-28 by hskim, ���Ǵ�Ƽ 3�� - ���� ��Ƽ Ÿ���� ��� �߰� - field server index ��ȣ - �߻�� 2�� ������ �ʵ� ���� ó���� ���� (���õ� ������ ����)
#define INVALID_CLIENT_INDEX					((ClientIndex_t)~0)
#define IS_CHARACTER_CLIENT_INDEX(x)			((ClientIndex_t)(x) >= CLIENT_INDEX_START_NUM && (ClientIndex_t)(x) < MONSTER_CLIENT_INDEX_START_NUM)	// character���� Ȯ��
#define IS_MONSTER_CLIENT_INDEX(x)				((ClientIndex_t)(x) >= MONSTER_CLIENT_INDEX_START_NUM && (ClientIndex_t)(x) < 20000)					// monster���� Ȯ��, check: 20000�̸� ����ϴٰ� ������, 2003103, kelovon w/ chkwon
#define IS_VALID_CLIENT_INDEX(idx)				(idx >= CLIENT_INDEX_START_NUM && idx < MONSTER_CLIENT_INDEX_START_NUM && idx != INVALID_CLIENT_INDEX && idx != 0)
#define IS_VALID_CHARACTER_AND_MONSTER_INDEX(idx)				(idx >= CLIENT_INDEX_START_NUM && idx < 20000 && idx != INVALID_CLIENT_INDEX && idx != 0)			// 2009-09-09 ~ 2010-01-11 by dhjin, ���Ǵ�Ƽ - ���Ͱ� Ÿ�� ������ ���� ����			
#define INVALID_UNIQUE_NUMBER					(UINT)(~0)
#define IS_VALID_UNIQUE_NUMBER(num)				((num) != 0 && (num) != INVALID_UNIQUE_NUMBER)
#define IS_VALID_UID64(num)						((num) != 0 && (num) != INVALID_UID64)				// 2006-10-11 by cmkwon
#define SIZE_MAX_VERSION_STRING					64
// 2006-09-06 by cmkwon, LocalizationDefineCommon.h ȭ�Ͽ� ����
//#define CHARACTER_MAX_LEVEL						100
#define PI										3.1415926535f
#define SIZE_MAX_LONG_PACKET					200000	// �� packet�� ���� �� ����� buffer�� ������, ���� ũ�� �� �ʿ���
#define DEFAULT_POSITION_X						100
#define DEFAULT_POSITION_Y						HEIGHT_FLYING_ALTITUDE
#define DEFAULT_POSITION_Z						100
#define SPEED_INCREASE_AMOUNT					19
#define REQUERED_TRADE_DISTANCE					500			// check: ��Ȯ�� �Ÿ� ���ϱ�
#define REQUERED_P2P_PK_DISTANCE				1500			// check: ��Ȯ�� �Ÿ� ���ϱ�
#define REQUERED_REQUEST_DISTANCE				1500			// check: ��Ȯ�� �Ÿ� ���ϱ�
// 2005-12-08 by cmkwon, ���ŵ�
//#define POSSESS_STORE_NUMBER					0			// â���� ���� �� possess ��ġ
#define POSSESS_AUCTION_NUMBER					((UID32_t)0xFFFFFFFF)	// ��� ���� �� possess ��ġ, -1 = 0xFFFFFFFF
#define CHARACTER_SIZE							15.0f		// ĳ���� ������
#define INVALID_MAP_NAME						""
#define MAP_INDEX_ALL							(USHORT)(~0)
#define ATUM_LOAD_TEST_PREFIX_ACCOUNT_NAME			"*loadtest"
#define ATUM_LOAD_TEST_PREFIX_ACCOUNT_NAME_SIZE		9
#define SIZE_MAX_PARTY_MEMBER					6			// �ִ� ��Ƽ�� ��
#define SIZE_MAX_INITIAL_SUM_OF_STAT			24
#define SIZE_MAX_ENCHANT_PER_ITEM				40			// �� �����ۿ� ���� �� �ִ� �ִ� ��æƮ ��
#define SIZE_MAX_ENCHANT_USE_ITEMKIND_PREVENTION_DELETE_ITEM	40	// �Ĺ�(�İ�����) ��� ������ �ִ� ��æƮ��, // 2006-08-23 by cmkwon, 8 --> 40
#define SIZE_REMAIN_ENCHANT_COUNT_BY_PREVENTION_DELETE_ITEM		5	// ��æƮ�� �Ĺ�(�İ�����) ����ϸ� ���� ��æũ ī��Ʈ
#define IS_VALID_PLANE_COORDINATES(x, z, maxX, maxZ)	((x) >= 0 && (z) >= 0 && (x) < (maxX) && (z) < (maxZ))
#define ACOS(fVal)									(((fVal) > 1.0f) ? acos(1.0f) : acos(fVal))
#define SIZE_MAX_FTP_URL							64
#define DOWNLOAD_BUFFER_SIZE						4096
#define SIZE_MAX_FTP_FILE_PATH						256
#define SIZE_MAX_FRIENDLIST_COUNT					60		// 2006-07-18 by cmkwon, 50 --> 60
#define SIZE_MAX_REJECTLIST_COUNT					60		// 2006-07-18 by cmkwon, 50 --> 60
#define SIZE_CITY_POSITION_RANDOM_XZ_RADIUS			30		// 2005-12-21 by cmkwon, 50 --> 30		

// 2006-09-04 by cmkwon, LocalizationDefineCommon.h ȭ�Ͽ� ����
//#define SIZE_MAX_ITEM_GENERAL						61		// ĳ������ �κ��丮�� ������ �� �ִ� �������� �ִ� ����(1���� SPI �������� ī��Ʈ�̴�, Ŭ���̾�Ʈ�� 60�� ����Ѵ�.)
//#define SIZE_MAX_ITEM_GENERAL_IN_STORE				101		// â���� ������ �� �ִ� �������� �ִ� ����

#define TUTORIAL_MAP_INDEX							8001	// Ʃ�丮����� �ϳ��̹Ƿ� define�Ѵ�
#define VCN_CITY_MAP_INDEX							2001	// �Ϲݱ�, ���Ա� ���ø��ε���
#define ANI_CITY_MAP_INDEX							2002	// �ݶ��� ���ø��ε���
// 2009-10-12 by cmkwon, ������ī ���� ��� ���� - ����
//#define NORMAL_CITY_MAP_INDEX						2003	// 2007-05-21 by cmkwon, �Ϲݱ� ���ø��ε��� - ��ī���̸�
#define INFLUENCE_CITY_MAP_INDEX					9999	// �� ���º� ���ø��ε���
#define INFLUENCE_GARDEN_MAP_INDEX					9998	// 2009-10-12 by cmkwon, ������ī ���� ��� ���� - �� ���º� �ո���(Garden)
#define VCN_CONFERENCEROOM_MAP_INDEX				1001	// 2007-08-30 by cmkwon, ȸ�Ƿ� �ý��� ���� - ���Ա� ȸ�Ƿ� ���ε���
#define ANI_CONFERENCEROOM_MAP_INDEX				1002	// 2007-08-30 by cmkwon, ȸ�Ƿ� �ý��� ���� - �ݶ��� ȸ�Ƿ� ���ε���

#define STONES_RUIN_MAP_INDEX						3002	// 2012-07-02 by hskim, ���� ���� - ���� ����� ������ ���� ���� �Ұ�
#define TYLENT_JUNGLE_MAP_INDEX						3003	// 2012-07-02 by hskim, ���� ���� - ���� ����� ������ ���� ���� �Ұ�

#define HELL_MAP_1ST								4401	// 2011-10-28 by hskim, EP4 [Ʈ���� �ý���] - ũ����Ż �ý��� - ������2
#define HELL_MAP_2ND								4403	// 2012-05-08 by hskim, EP4 [Ʈ���� �ý���] - ũ����Ż �ý��� 2�� - ������ 2

#define IS_HELL_2ND_MAP(MapIndex) (((MapIndex) == HELL_MAP_1ST) || ((MapIndex) == HELL_MAP_2ND))		// 2012-05-08 by hskim, EP4 [Ʈ���� �ý���] - ũ����Ż �ý��� 2�� - ������ 2

// 2006-07-03 by cmkwon, 1000����� ���λ��������� ��� �� ����
//#define IS_CITY_MAP_INDEX(__MAP_INDEX)				(((MapIndex_t)__MAP_INDEX)/1000==1)		// �ݳ�����
#define IS_CONFERENCEROOM_MAP_INDEX(__MAP_INDEX)	( (VCN_CONFERENCEROOM_MAP_INDEX==(__MAP_INDEX)) || (ANI_CONFERENCEROOM_MAP_INDEX==(__MAP_INDEX)) )			// 2007-08-30 by cmkwon, ȸ�Ƿ� �ý��� ���� - ���ε��� ���� �߰���
#define IS_BAZAAR_MAP_INDEX(__MAP_INDEX)			(IS_CONFERENCEROOM_MAP_INDEX(__MAP_INDEX))	// 2007-08-30 by cmkwon, ȸ�Ƿ� �ý��� ���� - ����  ���ڸ��� �̿���,	// 2006-07-19 by cmkwon, ���λ�����
#define IS_CITYWAR_MAP_INDEX(__MAP_INDEX)			(((MapIndex_t)__MAP_INDEX)/1000==5)		// ������������ �Ͼ�� ��
#define IS_SPACE_MAP_INDEX(__MAP_INDEX)				(((MapIndex_t)__MAP_INDEX)/1000==6)		// ���ָ�
#define IS_TUTORIAL_MAP_INDEX(__MAP_INDEX)			((__MAP_INDEX)==TUTORIAL_MAP_INDEX)		// Ʃ�丮���
#define IS_RACING_MAP_INDEX(__MAP_INDEX)			(((MapIndex_t)__MAP_INDEX)/1000==9)		// ���̸̽�
#define IS_VCN_CITY_MAP_INDEX(__MAP_INDEX)			((__MAP_INDEX) == VCN_CITY_MAP_INDEX)	// �Ϲݱ�, ���Ա� ���ø��ε����ΰ�?
#define IS_ANI_CITY_MAP_INDEX(__MAP_INDEX)			((__MAP_INDEX) == ANI_CITY_MAP_INDEX)	// �ݶ��� ���ø��ε����ΰ�?
// 2009-10-12 by cmkwon, ������ī ���� ��� ���� - ����
//#define IS_NORMAL_CITY_MAP_INDEX(__MAP_INDEX)		((__MAP_INDEX) == NORMAL_CITY_MAP_INDEX)	// 2007-05-21 by cmkwon, �Ϲݱ� ���ø��ε����ΰ�?
#define IS_OUTPOST_CITY_MAP_INDEX(__MAP_INDEX)		(2004 == (__MAP_INDEX) || 2005 == (__MAP_INDEX) || 2006 == (__MAP_INDEX) || 2007 == (__MAP_INDEX))	// 2013-01-21 by jhseol, NGC �������� Ʈ���� �ý��� - 2007 ���ø� ���		// 2008-09-10 by dhjin, 2006�߰� ���� MAP_INFLUENCE_OUTPOST = 6000������ �����ؾ��ҵ��ϴ�.	// 2007-09-10 by dhjin, �������� ���ø� �ΰ�? 
#define IS_STONES_RUIN_MAP_INDEX(__MAP_INDEX)			((__MAP_INDEX) == STONES_RUIN_MAP_INDEX)	// 2012-07-02 by hskim, ���� ���� - ���� ����� ������ ���� ���� �Ұ�
#define IS_TYLENT_JUNGLE_MAP_INDEX(__MAP_INDEX)			((__MAP_INDEX) == TYLENT_JUNGLE_MAP_INDEX)	// 2012-07-02 by hskim, ���� ���� - ���� ����� ������ ���� ���� �Ұ�

// 2008-02-12 by cmkwon, IS_CITY_MAP_INDEX() ��ũ�θ� �������� ���ø����� ���θ� ����
// 2009-10-12 by cmkwon, ������ī ���� ��� ���� - �Ϲݼ��� ���ø� ����
//#define IS_CITY_MAP_INDEX(__MAP_INDEX)				(IS_VCN_CITY_MAP_INDEX(__MAP_INDEX) || IS_ANI_CITY_MAP_INDEX(__MAP_INDEX) || IS_NORMAL_CITY_MAP_INDEX(__MAP_INDEX) || IS_CONFERENCEROOM_MAP_INDEX(__MAP_INDEX) || IS_OUTPOST_CITY_MAP_INDEX(__MAP_INDEX))		// �ݳ����� - // 2007-05-21 by cmkwon, IS_NORMAL_CITY_MAP_INDEX() �߰���
#define IS_CITY_MAP_INDEX(__MAP_INDEX)				(IS_VCN_CITY_MAP_INDEX(__MAP_INDEX) || IS_ANI_CITY_MAP_INDEX(__MAP_INDEX) || IS_CONFERENCEROOM_MAP_INDEX(__MAP_INDEX) || IS_OUTPOST_CITY_MAP_INDEX(__MAP_INDEX))		// 2009-10-12 by cmkwon, ������ī ���� ��� ���� - ,// �ݳ����� - // 2007-05-21 by cmkwon, IS_NORMAL_CITY_MAP_INDEX() �߰���

// 2009-10-12 by cmkwon, ������ī ���� ��� ���� - �Ϲݼ��� ���ø� ����
//#define IS_INFLUENCE_CITY_MAP_INDEX(__MAP_INDEX)	(IS_VCN_CITY_MAP_INDEX(__MAP_INDEX) || IS_ANI_CITY_MAP_INDEX(__MAP_INDEX) || IS_NORMAL_CITY_MAP_INDEX(__MAP_INDEX))		// 2008-02-12 by cmkwon, ���º� ���ø�
#define IS_INFLUENCE_CITY_MAP_INDEX(__MAP_INDEX)	(IS_VCN_CITY_MAP_INDEX(__MAP_INDEX) || IS_ANI_CITY_MAP_INDEX(__MAP_INDEX))		// 2009-10-12 by cmkwon, ������ī ���� ��� ���� - , // 2008-02-12 by cmkwon, ���º� ���ø�

///////////////////////////////////////////////////////////////////////////////
// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - �ñ� ���� ������ ó��
#define INFINITY_MAP_INDEX				9200
#define	INFINITY_MAP_INDEX_LAST			9299
#define IS_INFINITY_MAP_INDEX(__MAP_INDEX)		( INFINITY_MAP_INDEX <= (__MAP_INDEX) && INFINITY_MAP_INDEX_LAST >= (__MAP_INDEX) )


#define MONEY_ITEM_NUMBER							7000022		// ����(SPI) �����۳ѹ�
#define ITEM_NUM_CASH_NORMAL_PREMIUM_CARD			7001120		// �Ϲ� �����̾� �����۳ѹ�
// 2006-07-05 by cmkwon, MonthlyPay �ý��ۿ��� �ʿ� ���� define
//#define ITEM_NUM_CASH_SUPER_PREMIUM_CARD			7001130		// ���� �����̾� �����۳ѹ�
//#define ITEM_NUM_CASH_UPGRADE_PREMIUM_CARD			7001140		// ���� ���׷��̵� �����۳ѹ�
#define ITEM_NUM_APLUS_GRADE_HP_KIT					7010430		// A+�޼���ŰƮ		- Ŭ���̾�Ʈ������ ���
#define ITEM_NUM_APLUS_GRADE_DP_KIT					7010440		// A+�޽���ŰƮ		- Ŭ���̾�Ʈ������ ���
#define ITEM_NUM_S_GRADE_HP_KIT						7010290		// S�޼���ŰƮ		- Ŭ���̾�Ʈ������ ���
#define ITEM_NUM_S_GRADE_DP_KIT						7010300		// S�޽���ŰƮ		- Ŭ���̾�Ʈ������ ���
#define ITEM_NUM_PARTNER							72300		// 2012-03-15 by jhseol, ��Ʈ�ʷ�

#define ITEM_NUM_NEUTRON_RECHARGEABLE_BATTERY_MKIII	7026260		// 2009-09-09 ~ 2010-01-13 by dhjin, ���Ǵ�Ƽ - ȸ�� ������ �߰� // ��Ʈ�� ������ MKIII
#define ITEM_NUM_NEUTRON_RECHARGEABLE_BATTERY_MKII	7026280		// 2009-09-09 ~ 2010-01-13 by dhjin, ���Ǵ�Ƽ - ȸ�� ������ �߰� // ��Ʈ�� ������ MKII
#define ITEM_NUM_NEUTRON_RECHARGEABLE_BATTERY_MKI	7026290		// 2009-09-09 ~ 2010-01-13 by dhjin, ���Ǵ�Ƽ - ȸ�� ������ �߰� // ��Ʈ�� ������ MKI
#define ITEM_NUM_DEUS_EX_MACHINA_MKIII				7026300		// 2009-09-09 ~ 2010-01-13 by dhjin, ���Ǵ�Ƽ - ȸ�� ������ �߰� // ���콺 ���� ��Ű�� MKIII
#define ITEM_NUM_DEUS_EX_MACHINA_MKII				7026310		// 2009-09-09 ~ 2010-01-13 by dhjin, ���Ǵ�Ƽ - ȸ�� ������ �߰� // ���콺 ���� ��Ű�� MKII
#define ITEM_NUM_DEUS_EX_MACHINA_MKI				7026320		// 2009-09-09 ~ 2010-01-13 by dhjin, ���Ǵ�Ƽ - ȸ�� ������ �߰� // ���콺 ���� ��Ű�� MKI


#define ITEM_NUM_BRIGHTNESS_OF_BCU_LEADER			7001320		// 2007-05-02 by dhjin, '�������� ����' ������ ��ȣ 
#define ITEM_NUM_BRIGHTNESS_OF_ANI_LEADER			7001330		// 2007-05-02 by dhjin, '�������� ����' ������ ��ȣ 

// start 2012-01-16 by hskim, ��� - ȭ��
#define ITEM_NUM_SYSTEM_ORB							7025990
#define ITEM_NUM_QUASAR_ORB							7026000
#define ITEM_NUM_CLUSTER_ORB						7026010
#define ITEM_NUM_GALAXY_ORG							7026020
#define ITEM_NUM_UNIVERSE_ORB						7026030
// end 2012-01-16 by hskim, ��� - ȭ��

#define SIZE_MAX_ARMOR_COLOR_COUNT						10			// 2005-12-08 by cmkwon, �ƸӰ� ������ �ִ� �ִ� ���� ����
#define COLORItemNum_TO_ArmorSourceIndex(itemNum)		(((int)((itemNum)/100))*100)		// ����������� ItemNum�� �Ƹ��� SourceIndex�� ��ȯ�ϱ�
#define ARMORSourceIndex_TO_BaseColorItemNum(itemNum)	(((int)((itemNum)/100))*100 + 1)	// �Ƹ��� SourceIndex�� �⺻����������� ItemNum���� ��ȯ�ϱ�

#define TERM_ENABLE_CASH_PREMIUM_CARD_BUY_MONTH		1			// �Ѵ޴� �߰��� ���� �����ϴ�
#define TERM_MONTHLYPAY_MAX_BUY_ENABLE_DAY			180			// MonthlyPay ���� ���� �ִ� ��¥

#define CASH_SHOP_BUILDING_INDEX					9999		// ����ȭ ���� BuindNPCIndex
#define FIELD_STORE_SHOP_BUILDING_INDEX				9998		// 2009-09-23 by cmkwon, �ʵ�â�� ĳ�� ������ ���� - �ʵ�â�� BuildingIndex

#define DEFAULT_OBJECT_MONSTER_OBJECT				90000000
#define IS_DEFAULT_OBJECT_MONSTER_OBJECT(num)		(  (int)((num)/10000000) == 9  )

#define DEFAULT_CHANGE_OBJECT_ADD_INDEX				90000000	// 2011-12-19 by hskim, EP4 [Ʈ���� �ý���] - ũ����Ż �ý��� - ����� ��ü ������Ʈ�� ������ �߰� �ε��� ��

#define TIMEGAP_CITYWAR_CHANGEABLE_TERM_HOUR		4		// �������� ���� ������(����Ʈ �ð����ĺ���) ���� ���������� �ð�
#define CITYWAR_MINIMUM_TEX_PERCENT					2.0f	// ���������� ���� �̿� �ּ� tex
#define CITYWAR_MAXIMUM_TEX_PERCENT					100.0f	// ���������� ���� �̿� �ִ� tex

#define TICKGAP_SEND_INVASION_MSG					300000	// ħ�� �޽��� ���� ��, ����:ms, 300000 = 300�� = 5��
#define MAXIMUM_USABLE_FAME_POINT_FOR_ONE_DAY		20		// 2005-12-29 by cmkwon, �Ϸ翡 �Ѹ����� ������ �ִ� �ִ� ����ġ

#define SIZE_MAX_USERLIST_ON_BOSS_MONSTER_DEAD		10		// 2006-01-23 by cmkwon, ���� ���� ���� �� �α� ���� ���� ����Ʈ ����

// 2006-09-28 by cmkwon, ����(1000-->300)
#define SIZE_MIN_SELECTED_INFLUENCE_TYPE_USER_COUNT_FOR_INFLUENCE_DISTRIBUTION		100		// 2009-03-31 by cmkwon, �����ʱ�ȭ �ý��� ���� - ����(300), // 2006-02-08 by cmkwon, ���� ���� ó���� ���� ������ ���� ���� ������ ����

#define SIZE_MAX_SIGN_BOARD_STRING					64		// 2006-04-17 by cmkwon, �����ǿ� �� ��Ʈ�� �ִ� ����
#define INFLWAR_APPLY_TAX_PERIOD_DAY				30		// 2006-05-19 by cmkwon, ������ ���� ��꿡 �� ĳ���� �˻��� �ֱ� �α����� ���翡�� �̳�¥ �������� ���Ŀ����Ѵ�.

#define WEIGHT_RATE_HEAVY							0.7f	// 2006-10-13 by cmkwon, �ʰ��� ���� �Ҹ� 2�� 
#define WEIGHT_RATE_VERY_HEAVY						0.8f	// 2006-10-13 by cmkwon, �ʰ��� ���� �Ҹ� 2��, �ν��� ��� �ȵ�

#define TERM_QUEST_REQUEST_WARP_EFFECTIVE_TIME		20000	// 2006-10-16 by cmkwon, ��Ƽ ���� ��ȿ�ð�(����:ms)

#define TERM_STRATEGYPOINT_OCCUPY_TIME						7200000		// 2006-11-21 by cmkwon, ��������Ʈ ���Ľ� ���� �ð�(����:ms, 7200000 = 2�ð� = 2*60*60*1000)
#define ADD_CONTRIBUTIONPOINT_STRATEGYPOINT_MONSTER			500			// 2006-11-21 by cmkwon, ��������Ʈ ����/��� ������ ���� �⿩��
#define ADD_CONTRIBUTIONPOINT_BOSS_MONSTER					1000		// 2007-05-15 by dhjin, �� ����/��� ������ ���� �⿩��

// 2013-05-09 by hskim, ���� ����Ʈ ����
// 2013-08-14 by jhseol, ������ ������ - ��������Ʈ ���� ����
#ifdef SC_STRATEGYPOINTWAR_RENEWAL_JHSEOL_SSJUNG
#define CONTRIBUTIONPOINT_BOSS_MONSTER_WINNER				200
#define CONTRIBUTIONPOINT_BOSS_MONSTER_LOSER				(CONTRIBUTIONPOINT_BOSS_MONSTER_WINNER/5)
#else
#define CONTRIBUTIONPOINT_BOSS_MONSTER_WINNER				1000
#define CONTRIBUTIONPOINT_BOSS_MONSTER_LOSER				200
#endif
// end 2013-08-14 by jhseol, ������ ������ - ��������Ʈ ���� ����
#define CONTRIBUTIONPOINT_OUTPOST_WAR_WINNER				500
#define CONTRIBUTIONPOINT_OUTPOST_WAR_LOSER					100
// end 2013-05-09 by hskim, ���� ����Ʈ ����
// 2014-02-06 by jhseol, ��������Ʈ�� ���� ���� ������ �뷱�� ��ġ - ���� ��������Ʈ ����
#define CONTRIBUTIONPOINT_STRATEGYPOINT_MONSTER_WINNER		500
#define CONTRIBUTIONPOINT_STRATEGYPOINT_MONSTER_LOSER		100
inline int GetAddSTRATEGYPOINTbyVictoriesPoint(int i_nVictoriesPoint)
{
	switch(i_nVictoriesPoint)
	{
	case 2:	return 200;
	case 3:	return 500;
	case 4:	return 700;
	case 5:	return 900;
	case 6:	return 1100;
	case 7:	return 1500;
	case 8:	return 2500;
	default: return 0;
	}
};
// end 2014-02-06 by jhseol, ��������Ʈ�� ���� ���� ������ �뷱�� ��ġ - ���� ��������Ʈ ����

// 2013-12-16 by jhseol, ������ ��ȸ ���� ������ - ���� WP ����
#ifdef S_UPGRADE_INFLUENCE_POINT_RENEWAL_JHSEOL		// - ���� WP ����
#define ADD_WARPOINT_BOSS_MONSTER							(1000+400)	// �� ����/��� ������ ���� WARPOINT
#define ADD_WARPOINT_BOSS_MONSTER_BY_LOSE					(400+400)	// �� ����/��� �й�� ���� WARPOINT
#define ADD_WARPOINT_STRATEGYPOINT_MONSTER					(600+400)	// ��������Ʈ ����/��� ������ ���� WARPOINT 
#define ADD_WARPOINT_STRATEGYPOINT_MONSTER_BY_LOSE			(200+400)	// ��������Ʈ ����/��� �й�� ���� WARPOINT 
#else
#define ADD_WARPOINT_STRATEGYPOINT_MONSTER					600			// 2011-12-27 by hskim, EP4 [�뷱�� ����] // 2007-09-06 by dhjin 100=>300, // 2007-05-15 by dhjin, ��������Ʈ ����/��� ������ ���� WARPOINT 
#define ADD_WARPOINT_BOSS_MONSTER							1000		// 2011-12-27 by hskim, EP4 [�뷱�� ����] // 2007-09-06 by dhjin 300=>500, // 2007-05-15 by dhjin, �� ����/��� ������ ���� WARPOINT
#define ADD_WARPOINT_STRATEGYPOINT_MONSTER_BY_LOSE			200			// 2011-12-27 by hskim, EP4 [�뷱�� ����] // 2008-01-07 by dhjin, ���� ���� ���� - ��������Ʈ ����/��� �й�� ���� WARPOINT 
#define ADD_WARPOINT_BOSS_MONSTER_BY_LOSE					400			// 2011-12-27 by hskim, EP4 [�뷱�� ����] // 2008-01-07 by dhjin, ���� ���� ���� - �� ����/��� �й�� ���� WARPOINT
#endif
// end 2013-12-16 by jhseol, ������ ��ȸ ���� ������ - ���� WP ����
#define ADD_WARPOINT_EVENT_MONSTER_BY_LOSE					250			// 2010-06-21 by jskim, �̺�Ʈ ���� ���� ������Ʈ

#define TERM_GAME_PLAYTIME_LIMIT_FIRST_SEC					10800		// 2006-11-23 by cmkwon, 10800��(3*60*60) = 3�ð� - ����ġ/SPI 50%
#define TERM_GAME_PLAYTIME_LIMIT_LAST_SEC					18000		// 2006-11-23 by cmkwon, 18000��(5*60*60) = 5�ð� - ����ġ/SPI 0%

// 2009-04-06 by cmkwon, ��ų ���� �Ӽ� �߰��� ����(��� �ð� ����) - �Ӽ����� ó����, ���ŵ�.
//#define TERM_TICK_MUST_SERVER_CHECK_SKILL_REATTACK_TIME		600000		// 2006-12-15 by cmkwon, 10��(10*60*1000) RaattackTime�� 10�� �ʰ��� ��ų�� ���������� üũ�Ѵ�

#define WM_UPDATEFILE_DOWNLOAD_ERROR						WM_USER + 100	// 2007-01-05 by cmkwon
#define WM_UPDATEFILE_DOWNLOAD_INIT							WM_USER + 101	// 2007-01-05 by cmkwon
#define WM_UPDATEFILE_DOWNLOAD_PROGRESS						WM_USER + 102	// 2007-01-05 by cmkwon
#define WM_UPDATEFILE_DOWNLOAD_OK							WM_USER + 103	// 2007-01-05 by cmkwon
#define WM_UPDATE_VTCGUARD_OK								WM_USER + 104	// 2012-02-09 by hskim, ��Ʈ�� X-Trap -> VTC ����� ����

#define SIZE_MAX_SERVER_GROUP_COUNT							20				// 2007-01-18 by cmkwon, ���� �׷� �ִ� ����

// 2008-12-18 by cmkwon, �Ϻ� Arario �ܺ�����, ���� ��� �����ϱ� - �Ʒ��� ���� �Ϻ��� ����� �ٸ��� �Ѵ�.
//#define SIZE_MAX_WEBLOGIN_AUTHENTICATION_KEY				30				// 2007-03-29 by cmkwon, ������Ű �ִ� ��Ʈ�� ������(����� ���縸 ��� ����)
#if defined(SERVICE_TYPE_JAPANESE_SERVER_1)
#define SIZE_MAX_WEBLOGIN_AUTHENTICATION_KEY				301				// 2008-12-18 by cmkwon, �Ϻ� Arario �ܺ�����, ���� ��� �����ϱ� - ����Ű�� ���ް���. AUTH_SESSIONKEY_LEN + 1 ũ�Ⱑ �ʿ�
#else
#define SIZE_MAX_WEBLOGIN_AUTHENTICATION_KEY				30				// 2007-03-29 by cmkwon, ������Ű �ִ� ��Ʈ�� ������(����� ���縸 ��� ����)
#endif

#define SIZE_MAX_GAME_PUBLISHER_NAME						20				// 2007-04-09 by cmkwon
#define SIZE_MAX_ADD_CHARACTER_NAME							5				// 2007-04-10 by cmkwon, ĳ���͸��ڿ� ���̴� ��Ʈ�� �ִ� ����Ʈ


#define SIZE_MAX_GAME_SERVER_GROUP_NAME						30				// 2007-05-02 by cmkwon
#define COUNT_MAX_GAME_SERVER_GROUP_LIST					10					

// 2008-09-17 by cmkwon, Ŭ���̾�Ʈ �������ϵ� üũ�� üũ �߰� - 
//#define	SIZE_MAX_RESOBJ_FILE_NAME							20				// 2007-05-28 by cmkwon, 
#define	SIZE_MAX_RESOBJ_FILE_NAME							30				// 2008-09-17 by cmkwon, Ŭ���̾�Ʈ �������ϵ� üũ�� üũ �߰� - 30 Bytes �� ����

#define	TICKGAP_WARHEAD_LIFETIME							20000			// 2007-06-12 by cmkwon, 2�� ���� ź�ΰ� �߻� �� ��ȿ�� �ð�(ms)
#define	TICKGAP_WARHEAD_LIFETIME_LONG						50000			// 2007-06-12 by cmkwon, 2�� ���� ź�ΰ� �߻� �� ��ȿ�� �ð�(ms) - // 2011-03-28 by hskim, ���Ǵ�Ƽ 3�� - ���� ��Ƽ Ÿ���� ��� �߰� - ������ �� �ð� 2�� ź�� ����

// 2007-06-27 by cmkwon, ��Ƽ�� ����ġ �й� ��� �ý��� �߰� - Ÿ�� ����
#define MAX_LEVEL_GAP_APPLY_PARTY_BONUS						14				// 2008-06-10 by dhjin, EP3 ���� ���� - 7->14�� ���� // 2007-06-27 by cmkwon, ��Ƽ ���ʽ� ���� �ִ� ������			
#define EXP_DISTRIBUTE_TYPE_DAMAGE							0				// 2007-06-27 by cmkwon, ���Ϳ� �� �������� ���� ����ġ �й�
#define EXP_DISTRIBUTE_TYPE_EQUALITY						1				// 2007-06-27 by cmkwon, �յ� �й�

#define TERM_10MINUTES_BY_SECOND							600				// 2007-06-28 by cmkwon, ���� 7�� PC�� ���̺�Ʈ ���� �ð� ���� -
#define TERM_30MINUTES_BY_SECOND							1800			// 2007-06-28 by cmkwon, ���� 7�� PC�� ���̺�Ʈ ���� �ð� ���� -
#define TERM_60MINUTES_BY_SECOND							3600			// 2007-06-28 by cmkwon, ���� 7�� PC�� ���̺�Ʈ ���� �ð� ����
#define TERM_10MINUTES_BY_MILLISECOND						600000			// 2007-06-28 by cmkwon, �߱� ��������(���� �ð� �˸� ����) - 10��

#define SIZE_MAX_JUMIN_NUMBER								20				// 2007-06-29 by cmkwon, td_account ���̺��� �ֹι�ȣ�����ϱ� 

#define RECHARGE_BULLET_ALL_CALIBER							255				// 2007-08-07 by cmkwon, 1��/2�� ���� �Ѿ� ���� ������ ���� - Caliber ����

#define SIZE_MAX_STRING_128									128				// 2007-08-09 by cmkwon, ��� ���¿� ä�� �����ϱ� - ���� �߰�
#define SIZE_MAX_STRING_256									256				// 2007-08-09 by cmkwon, ��� ���¿� ä�� �����ϱ� - ���� �߰�
#define SIZE_MAX_STRING_512									512				// 2007-08-09 by cmkwon, ��� ���¿� ä�� �����ϱ� - ���� �߰�
#define SIZE_MAX_STRING_1024								1024			// 2007-08-09 by cmkwon, ��� ���¿� ä�� �����ϱ� - ���� �߰�

#define SIZE_MAX_CONFERENCEROOM_USER						100				// 2007-08-30 by cmkwon, ȸ�Ƿ� �ý��� ���� - ȸ�Ǹ� �㰡 �ִ� �ο���

#define	STR_INVALID_CHARACTER_NAME							" \r\n\t"		// 2007-10-22 by cmkwon, ĳ���͸��� ��ȿ���� ���� ����
#define	STR_INVALID_PRE8SUFFIX_GUILD_NAME					" \r\n\t"		// 2007-10-22 by cmkwon, ���ܸ� ���۰� ���� ��ȿ���� ���� ����

#define SIZE_MAX_SELECTIVE_SHUTDOWN_INFO					30				// 2012-07-11 by hskim, ������ �˴ٿ�
#define SIZE_MAX_SHUTDOWN_SERVICE_BLOCK						24				// 2012-07-11 by hskim, ������ �˴ٿ�
#define STR_DEFAULT_VALUE_SELECTIVE_SHUTDOWN_INFO			"111111111111111111111111"		// 2012-07-11 by hskim, ������ �˴ٿ�

#ifdef	S_GAMEFORGE_KEY_CHANGE_JHSEOL
#define STR_XOR_KEY_STRING_SERVER_INFO						"0an%M)~Y*BAi~f5b)UM~)%#058v~#YVV~&#@"			// 2012-07-26 by jhseol, �������� Key ����
#define STR_XOR_KEY_STRING_PRE_SERVER_ADDRESS				"+-faNsf(^fP{)3>fnao??_+|23kdasf*^@`d{]s*&DS"	// 2008-04-23 by cmkwon, PreServer �ּҸ� IP�� ������ �Ѵ� ���� - 
#define STR_XOR_KEY_STRING_DB_ID_PWD						"m045%h@M`g0nq~683tT__!*@^OTE~W09n3$q+b94`lwrei~53nm_%byr~(*PN$^*"	// 2012-07-26 by jhseol, �������� Key ����
#define STR_XOR_KEY_STRING_SECURITY_COMMAND					"^@dk@11@<$HGJKAOkfjqpojg@1-09f-0102890jkfmlk!@#68f91!@jf902121Z"	// 2011-06-22 by hskim, �缳 ���� ���� (Ŀ�ǵ�� ��ȣȭ Ű)
#else
#define STR_XOR_KEY_STRING_SERVER_INFO						"~8xANs(^fP{)34$(fcbTN$(C-=x"					// 2007-10-24 by cmkwon, ���� ���� ��ȣȭ - DB Server Password XOR Key
#define STR_XOR_KEY_STRING_PRE_SERVER_ADDRESS				"+-faNsf(^fP{)3>fnao??_+|23kdasf*^@`d{]s*&DS"	// 2008-04-23 by cmkwon, PreServer �ּҸ� IP�� ������ �Ѵ� ���� - 
#define STR_XOR_KEY_STRING_DB_ID_PWD						"@34ns%<<fdsa(Tflsd!sndsa^#)fndsla$nvsa$fndsla&nfdsJak(fnldsa!#F"	// 2008-09-01 by cmkwon, global.cfg ���Ͽ� DB ID/PWD ��ȣȭ - 
#define STR_XOR_KEY_STRING_SECURITY_COMMAND					"^@dk@11@<$HGJKAOkfjqpojg@1-09f-0102890jkfmlk!@#68f91!@jf902121Z"	// 2011-06-22 by hskim, �缳 ���� ���� (Ŀ�ǵ�� ��ȣȭ Ű)
#endif


#define COUNT_MAX_SECURITY_COMMAND							3				// 2011-06-22 by hskim, �缳 ���� ���� (Ŀ�ǵ�� ��ȣȭ Ű ������ �ִ� ����)
#define SIZE_MAX_SECURITY_COMMAND							1024			// 2011-06-22 by hskim, �缳 ���� ���� (Ŀ�ǵ�� ��ȣȭ Ű�� �ִ� ũ��)
#define SIZE_THRESHOLD_SECURITY_COMMAND						50				// 2011-06-22 by hskim, �缳 ���� ���� (Ŀ�ǵ�� ��ȣȭ���� Ű�� ���̷� �Ǵ��ϴ� �ּ� ��)

#define SIZE_MAX_DB_USER_ID									128				// 2007-12-13 by cmkwon, 128 bytes �� ����, // 2007-10-24 by cmkwon, ���� ���� ��ȣȭ
#define SIZE_MAX_DB_USER_PWD								128				// 2007-12-13 by cmkwon, 128 bytes �� ����, // 2007-10-24 by cmkwon, ���� ���� ��ȣȭ

#define SIZE_MAX_WINDOW_DEGREE_NAME							128				// 2007-12-27 by cmkwon, �������� ��� ��� �߰� - �߰�

#define SIZE_MAX_ODBC_CONN_STRING							128		// 2008-03-03 by cmkwon, SIZE_MAX_ODBC_CONN_STRING ���� ��ġ ���� - GlobalGameServer.h �� �ִ����� ����� �ű�

#define	TICKGAP_DROP_ITEM_TIMEOUT							300000			// 2012-03-05 by hskim, ��� ������ ���� �ð��� ���� (5�� : 1000 ms * 60 sec * 5 min)

///////////////////////////////////////////////////////////////////////////////
// 2010-11-29 by shcho, �Ƹ���Ƽ�� �ܺ����� ���� SOAP ó��
#define SIZE_MAX_URL_STRNIG									512
#define SIZE_MAX_GAME_ID									10
// end 2010-11-29 by shcho, �Ƹ���Ƽ�� �ܺ����� ���� SOAP ó��
///////////////////////////////////////////////////////////////////////////////


// 2008-04-29 by cmkwon, ������ ���� DB�� �߰�(�ű� ���� ĳ���� ���� ���� �ý����߰�) - 
#define SIZE_MAX_INIT_LIMIT_USER_COUNT_PER_SERVER_GROUP		500				// 2008-04-29 by cmkwon, ������ ���� DB�� �߰�(�ű� ���� ĳ���� ���� ���� �ý����߰�) - 

#define MIN_SUPPORT_YEAR			1970		// 2008-06-27 by cmkwon, ��¥�ð� ���� ���� ����(1970 ~ 2037) - 
#define MAX_SUPPORT_YEAR			2037		// 2008-06-27 by cmkwon, ��¥�ð� ���� ���� ����(1970 ~ 2037) - 

#define MAX_ITEM_COUNT_FOR_PACKAGE_ITEM						10				// 2008-08-26 by cmkwon, ItemAttribute �߰� - ��Ű��(Package) ������, �ִ� ���� ����


#define MAX_PACKET_SIZE_FOR_XIGNCODE						512				// 2008-11-28 by cmkwon, �븸 Netpower_Tpe XignCode(���Ӱ���) ���� - 

#define SIZE_MAX_ADDRESS									128				// 2009-01-15 by cmkwon, PreServer, DBServer ���� DNS�� ���� �����ϰ� ���� - 


// 2010-06-01 by shcho, GLogDB ���� -
#define SIZE_MAX_GLOG_CHARACTER_RACE_NAME						32
#define SIZE_MAX_GLOG_CHARACTER_CLASS_NAME						32
#define SIZE_MAX_GLOG_EVENT_DESCRIPTION							512

// 2011-01-26 by hskim, ���� ���� ����
#define SIZE_MAX_AUTH_GAMENAME					30
#define SIZE_MAX_AUTH_CURRENTVER				30
#define SIZE_MAX_AUTH_PUBLISHER					35
#define SIZE_MAX_AUTH_ACCEPT_COMMENT			254
#define SIZE_MAX_AUTH_RESOURCE_FILE_NAME		254

#define MAX_ENCHANT_ONCE_APPLY_COUNT			10							// 2011-10-19 by hskim, EP4 [Free to play] - 10 ȸ ��þƮ ������ ��� ���� (��ȹ���� �Ǽ� ������ ���� �ý��������� �Ѱ� ����)

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// 2007-01-06 by cmkwon
#define AU_SERVER_TYPE_FTP				0
#define AU_SERVER_TYPE_HTTP				1






#define SIZE_STRING_32								32
#define SIZE_STRING_64								64
#define SIZE_STRING_128								128

enum EN_DAY_OF_WEEK
{
	DAY_OF_WEEK_SUMDAY					= 0,			// 2006-08-24 by cmkwon, �Ͽ���
	DAY_OF_WEEK_MONDAY					= 1,			// 2006-08-24 by cmkwon, ������
	DAY_OF_WEEK_TUESDAY					= 2,			// 2006-08-24 by cmkwon, ȭ����
	DAY_OF_WEEK_WEDNESDAY				= 3,			// 2006-08-24 by cmkwon, ������
	DAY_OF_WEEK_THURSDAY				= 4,			// 2006-08-24 by cmkwon, �����
	DAY_OF_WEEK_FRIDAY					= 5,			// 2006-08-24 by cmkwon, �ݿ���
	DAY_OF_WEEK_SATURDAY				= 6,			// 2006-08-24 by cmkwon, �����
	DAY_OF_WEEK_HAPPYHOUREVENT_PERIOD	= 7,			// 2006-08-24 by cmkwon, ���Ǿƿ� �̺�Ʈ �Ⱓ ���� - ���� �ʵ�� ������� ����
	DAY_OF_WEEK_PCBANG_HAPPYHOUREVENT	= 8				// 2006-08-24 by cmkwon, PCBang ���Ǿƿ� �̺�Ʈ �Ⱓ �� ���� ����
};

#define ATUM_PRE_SERVER								0
#define ATUM_IM_SERVER								1
#define ATUM_LOG_SERVER								2
#define ATUM_MONITOR_SERVER							3
#define ATUM_FIELD_SERVER_1							6
#define ATUM_NPC_SERVER_1							7
#define ATUM_FIELD_SERVER_2							8
#define ATUM_NPC_SERVER_2							9
#define ATUM_FIELD_SERVER_3							10
#define ATUM_NPC_SERVER_3							11
#define ATUM_FIELD_SERVER_4							12
#define ATUM_NPC_SERVER_4							13
#define ATUM_FIELD_SERVER_5							14
#define ATUM_NPC_SERVER_5							15

// Ư��ġ ����
#define OT_ATTACK_TRAIT_DEFAULT_VALUE	0.05f
#define DT_DEFENSE_TRAIT_DEFAULT_VALUE	0.03f
#define BT_AVOID_TRAIT_DEFAULT_VALUE	1.0f

///////////////////////////////////////////////////////////////////////////////
//	ATUM - CHaracter, Monster, Item - Parameter ����
///////////////////////////////////////////////////////////////////////////////

// 2005-06-23 by cmkwon
// ��Ʈ �÷��� ���� - ���� Ÿ������ ���� �߿� �ϳ��� ���� ������.
#define INFLUENCE_TYPE_UNKNOWN				(BYTE)0x0000	// �˼� ����
#define INFLUENCE_TYPE_NORMAL				(BYTE)0x0001	// 2005-12-20 by cmkwon, ���������� �Ϲݱ�
#define INFLUENCE_TYPE_VCN					(BYTE)0x0002	// 2005-12-20 by cmkwon, ���������� ���Ա�, ����(V.C.U: Vijuenill City United.)
#define INFLUENCE_TYPE_ANI					(BYTE)0x0004	// 2005-12-20 by cmkwon, �˸��� ���Ա�, ����(�� �������� ���� -�˸��� ��Ƽ �ݶ���- (A.N.I: Anti Nationalism Influence))
#define INFLUENCE_TYPE_RRP					(BYTE)0x0008	// �κ��Ͼ� ���� ���� - ��Ż���� ���決- (R.R.P: Robenia Revolution Federation)
#define INFLUENCE_TYPE_ALL_MASK				(BYTE)0x00FF	// ��� ����, 255
#define INFLUENCE_TYPE_COUNT				4				// 2006-04-17 by cmkwon, ������ ����(�� 4�� - Normal, VCN, ANI, ALL)
#define INFLUENCE_TYPE_COUNT_EX_ALL			3				// 2009-09-16 by cmkwon, ���� �ʱ�ȭ�� ���¡ ���� ���� - ������ ����(�� 3�� - Normal, VCN, ANI)
#define COMPARE_INFLUENCE(VAR, MASK)		(((VAR) & (MASK)) != 0)

#define IS_NORMAL_INFLUENCE_TYPE(charInfl)	(COMPARE_INFLUENCE((charInfl), INFLUENCE_TYPE_NORMAL))		// 2007-05-22 by cmkwon, �߰���
#define IS_VCN_INFLUENCE_TYPE(charInfl)		(COMPARE_INFLUENCE((charInfl), INFLUENCE_TYPE_VCN))			// 2007-05-22 by cmkwon
#define IS_ANI_INFLUENCE_TYPE(charInfl)		(COMPARE_INFLUENCE((charInfl), INFLUENCE_TYPE_ANI))
#define IS_VALID_INFLUENCE_TYPE(charInfl)	(INFLUENCE_TYPE_NORMAL==(charInfl)|| INFLUENCE_TYPE_VCN==(charInfl)||INFLUENCE_TYPE_ANI==(charInfl))		// 2006-02-08 by cmkwon

// 2010-06-01 by shcho, GLogDB ���� -
#define INFLUENCE_TYPE_ENG_NORMAL			"NORMAL_INFLUENCE"
#define INFLUENCE_TYPE_ENG_VCN				"VCN_INFLUENCE"
#define INFLUENCE_TYPE_ENG_ANI				"ANI_INFLUENCE"
#define INFLUENCE_TYPE_ENG_ALL_MASK			"ALL_INFLUENCE"

#define UNITKIND_ENG_BGEAR					"B-Gear"
#define UNITKIND_ENG_MGEAR					"M-Gear"
#define UNITKIND_ENG_AGEAR					"A-Gear"
#define UNITKIND_ENG_IGEAR					"I-Gear"
#define UNITKIND_ENG_UNKNOWN				"UNKNOWN_Gear"


// 2005-12-26 by cmkwon
// ��Ʈ �÷��� ���� �ƴ� - ti_MapInfo���̺��� MapInfluenceType �ʵ� �� ���� Ÿ�� ����
#define MAP_INFLUENCE_NEUTRALITY		(USHORT)0		// �߸� ����
#if _RAT_FFA
#define MAP_INFLUENCE_PVP_ALL			REF_MAP_INFLUENCE_PVP_ALL
#endif
#define MAP_INFLUENCE_NON_DISPUTE		(USHORT)400		// ������ ����� ���� // 2012-01-17 by hskim, EP4 [����� ����] - ������ ���� ���� ����
#define MAP_INFLUENCE_HELL				(USHORT)500		// ���� ���� (������ Backmap ���� �̵� �� �ʱ� ���� �Ұ� ����) // 2011-10-28 by hskim, EP4 [Ʈ���� �ý���] - ũ����Ż �ý���
#define MAP_INFLUENCE_VCN_CITY			(USHORT)1000	// ���������� ���ø�
#define MAP_INFLUENCE_VCN_START			(USHORT)1001	// ���������� ���۸�
#define MAP_INFLUENCE_VCN_MSWAR			(USHORT)1700	// ���������� - �����ÿ� ƨ��� �� - // 2012-12-05 by hskim, ���� ���۽ÿ� ��� ���� ���ø����� ����
#define MAP_INFLUENCE_VCN_BASE			(USHORT)1701	// ���������� - �����ÿ� ƨ��� �� + �Ϲ� ��Ȳ���� ���� ��ȯ - // 2012-12-05 by hskim, ���� ���۽ÿ� ��� ���� ���ø����� ����
#define MAP_INFLUENCE_VCN_LAST			(USHORT)1999	// ���������� ��������
#define MAP_INFLUENCE_ANI_CITY			(USHORT)2000	// �˸��� ���ø�
#define MAP_INFLUENCE_ANI_START			(USHORT)2001	// �˸��� ���۸�
#define MAP_INFLUENCE_ANI_MSWAR			(USHORT)2700	// �˸��� - �����ÿ� ƨ��� �� - // 2012-12-05 by hskim, ���� ���۽ÿ� ��� ���� ���ø����� ����
#define MAP_INFLUENCE_ANI_BASE			(USHORT)2701	// �˸��� - �����ÿ� ƨ��� �� + �Ϲ� ��Ȳ���� ���� ��ȯ - // 2012-12-05 by hskim, ���� ���۽ÿ� ��� ���� ���ø����� ����
#define MAP_INFLUENCE_ANI_LAST			(USHORT)2999	// �˸��� ��������
#define MAP_INFLUENCE_NORMAL_CITY		(USHORT)3000	// 2007-05-22 by cmkwon, �Ϲݱ����ø�
#define MAP_INFLUENCE_INFINITY			(USHORT)5000	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - 
#define MAP_INFLUENCE_INFINITY_LAST		(USHORT)5999	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - 
#define MAP_INFLUENCE_OUTPOST			(USHORT)6000	// 2007-08-17 by dhjin, �������� ���� �� 
#define MAP_INFLUENCE_OUTPOST_START		(USHORT)6001	// 2007-08-17 by dhjin, �������� �� 
#define MAP_INFLUENCE_OUTPOST_LAST		(USHORT)6999	// 2007-08-17 by dhjin, �������� ��
#define MAP_INFLUENCE_OUTPOST_TRIGGER	(USHORT)4303	// 2013-01-21 by jhseol, NGC �������� Ʈ���� �ý��� - Ʈ���� �������� �� �߰�
#define MAP_INFLUENCE_ARENA				(USHORT)7000	// 2007-05-04 by dhjin, ARENA ��
#define MAP_INFLUENCE_ARENA_LAST		(USHORT)7999	// 2007-05-04 by dhjin, ARENA ��
#define MAP_INFLUENCE_EVENT_CITY		(USHORT)8000	// �̺�Ʈ ���ø�(�ǹ̾���)
#define MAP_INFLUENCE_EVENT_START		(USHORT)8001	// �̺�Ʈ ���۸�, 2006-07-18 by cmkwon
#define MAP_INFLUENCE_EVENT_LAST		(USHORT)8999	// �̺�Ʈ ��������, 2006-07-18 by cmkwon
#define MAP_INFLUENCE_CONFLICT_AREA_CITY		(USHORT)9000	// ���� ���� ���۸�(�ǹ̾���), // 2006-02-09 by cmkwon
#define MAP_INFLUENCE_CONFLICT_AREA_START		(USHORT)9001	// ���� ���� ���۸�, // 2006-02-09 by cmkwon
#define MAP_INFLUENCE_CONFLICT_AREA_LAST		(USHORT)9999	// ���� ���� ��������, // 2006-02-09 by cmkwon

#define IS_MAP_INFLUENCE_NON_DISPUTE(mapInfl)	( MAP_INFLUENCE_NON_DISPUTE == (mapInfl) )	// ������ ����� ���� // 2012-01-17 by hskim, EP4 [����� ����] - ������ ���� ���� ����
#define IS_MAP_INFLUENCE_HELL(mapInfl)			( MAP_INFLUENCE_HELL == (mapInfl) )	// ���� ���� (������ Backmap ���� �̵�) // 2011-10-28 by hskim, EP4 [Ʈ���� �ý���] - ũ����Ż �ý���
#define IS_MAP_INFLUENCE_VCN(mapInfl)			( MAP_INFLUENCE_VCN_CITY <= (mapInfl) && MAP_INFLUENCE_VCN_LAST >= (mapInfl) )	// ���������� ���� ��(1000 ~ 1999)�ΰ�?
#define IS_MAP_INFLUENCE_ANI(mapInfl)			( MAP_INFLUENCE_ANI_CITY <= (mapInfl) && MAP_INFLUENCE_ANI_LAST >= (mapInfl) )	// �˸��� ���� ��(2000 ~ 2999)�ΰ�?
#define IS_MAP_INFLUENCE_NORMAL(mapInfl)		( MAP_INFLUENCE_NORMAL_CITY == (mapInfl) )	// 2007-05-22 by cmkwon, �Ϲݱ����ø�(3000)�ΰ�?
#define IS_MAP_INFLUENCE_CONFLICT_AREA(mapInfl)	( MAP_INFLUENCE_CONFLICT_AREA_CITY <= (mapInfl) && MAP_INFLUENCE_CONFLICT_AREA_LAST >= (mapInfl) )	// ���� ���� ��(9000 ~ 9999)�ΰ�?
#define IS_MAP_INFLUENCE_EVENT_AREA(mapInfl)	( MAP_INFLUENCE_EVENT_CITY <= (mapInfl) && MAP_INFLUENCE_EVENT_LAST >= (mapInfl) )	// �̺�Ʈ��(8000 ~ 8999)�ΰ�?
#define IS_MAP_INFLUENCE_ARENA(mapInfl)			( MAP_INFLUENCE_ARENA <= (mapInfl) && MAP_INFLUENCE_ARENA_LAST >= (mapInfl) )	// �Ʒ��� ��(7000 ~ 7999)�ΰ�?
#define IS_MAP_INFLUENCE_OUTPOST(mapInfl)		((MAP_INFLUENCE_OUTPOST_START <= (mapInfl) && MAP_INFLUENCE_OUTPOST_LAST >= (mapInfl)) || MAP_INFLUENCE_OUTPOST_TRIGGER == (mapInfl) )	// �������� ��(6000 ~ 6999)�ΰ�?	// 2013-01-21 by jhseol, NGC �������� Ʈ���� �ý��� - Ʈ���� �������� �� �߰�
#define IS_MAP_INFLUENCE_INFINITY(mapInfl)		( MAP_INFLUENCE_INFINITY <= (mapInfl) && MAP_INFLUENCE_INFINITY_LAST >= (mapInfl) )	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - 

#define IS_MAP_INFLUENCE_MSWAR(mapInfl)			( MAP_INFLUENCE_VCN_MSWAR == (mapInfl) || MAP_INFLUENCE_ANI_MSWAR == (mapInfl) || MAP_INFLUENCE_VCN_BASE == (mapInfl) || MAP_INFLUENCE_ANI_BASE == (mapInfl) )		// 2012-12-05 by hskim, ���� ���۽ÿ� ��� ���� ���ø����� ����
#define IS_MAP_INFLUENCE_MSWAR_ANI(mapInfl)		( MAP_INFLUENCE_ANI_MSWAR == (mapInfl) || MAP_INFLUENCE_ANI_BASE == (mapInfl) )		// 2012-12-05 by hskim, ���� ���۽ÿ� ��� ���� ���ø����� ����
#define IS_MAP_INFLUENCE_MSWAR_VCN(mapInfl)		( MAP_INFLUENCE_VCN_MSWAR == (mapInfl) || MAP_INFLUENCE_VCN_BASE == (mapInfl) )		// 2012-12-05 by hskim, ���� ���۽ÿ� ��� ���� ���ø����� ����

// 2009-10-12 by cmkwon, ������ī ���� ��� ���� - CAtumSJ::IsSameCharacterInfluence8MapInfluence#�� ��ü
// // 2007-05-22 by cmkwon, �Ϲݱ� ���ø� �߰�
// #define IS_SAME_CHARACTER_8_MAP_INFLUENCE(charInfl, mapInfl)	(  ( COMPARE_INFLUENCE((charInfl), INFLUENCE_TYPE_NORMAL) && IS_MAP_INFLUENCE_NORMAL(mapInfl) ) \
// 																|| ( COMPARE_INFLUENCE((charInfl), INFLUENCE_TYPE_VCN) && IS_MAP_INFLUENCE_VCN(mapInfl) ) \
//																|| ( COMPARE_INFLUENCE((charInfl), INFLUENCE_TYPE_ANI) && IS_MAP_INFLUENCE_ANI(mapInfl) )  )

// 2007-05-22 by cmkwon, �Ʒ� #define���� ���� ó����
//#define IS_OTHER_INFLUENCE_CITY(charInfl, mapInfl)	( (COMPARE_INFLUENCE(charInfl, INFLUENCE_TYPE_NORMAL|INFLUENCE_TYPE_VCN) && MAP_INFLUENCE_ANI_CITY == mapInfl) \
//																|| (COMPARE_INFLUENCE(charInfl, INFLUENCE_TYPE_ANI) && MAP_INFLUENCE_VCN_CITY == mapInfl) )
#define IS_MAP_INFLUENCE_CITY(mapInfl)				( MAP_INFLUENCE_VCN_CITY == (mapInfl) || MAP_INFLUENCE_ANI_CITY == (mapInfl) || MAP_INFLUENCE_NORMAL_CITY == (mapInfl))

// 2009-10-12 by cmkwon, ������ī ���� ��� ���� - CAtumSJ::IsOtherInfluenceMap#���� ��ü��
//#define IS_OTHER_INFLUENCE_MAP(charInfl, mapInfl)	( (COMPARE_INFLUENCE(charInfl, INFLUENCE_TYPE_NORMAL|INFLUENCE_TYPE_VCN) && IS_MAP_INFLUENCE_ANI(mapInfl)) \
//																|| (COMPARE_INFLUENCE(charInfl, INFLUENCE_TYPE_ANI) && IS_MAP_INFLUENCE_VCN(mapInfl)) )

// 2008-12-23 by dhjin, ���� ���� �߰���
#define IS_MAP_INFLUENCE_WAR(mapInfl)				( IS_MAP_INFLUENCE_VCN(mapInfl) || IS_MAP_INFLUENCE_ANI(mapInfl) || IS_MAP_INFLUENCE_OUTPOST(mapInfl))

// check: ���� ù bit�� ����ϰ� �ȴٸ�, ���� DB schema�� Race�� type�� int�� �����ؾ� ��.
#define RACE_BATTALUS				(USHORT)0x0001	// ��Ż����, 1
#define RACE_DECA					(USHORT)0x0002	// ��ī, 2
#define RACE_PHILON					(USHORT)0x0004	// �ʷ�, 4
#define RACE_SHARRINE				(USHORT)0x0008	// ����, 8
#define RACE_INFLUENCE_LEADER		(USHORT)0x0010	// 16, ������ ����, 2006-04-20 by cmkwon, RACE_MONSTER1(����, 16)�� ������ ����
// 2007-10-06 by cmkwon, �������� 2���� ȣĪ�� �ٸ��� ���� - ���� ����, �Ʒ����� ���� ����
//#define RACE_INFLUENCE_SUBLEADER	(USHORT)0x0020	// 32, ������ ��������, 2006-12-08 by cmkwon, RACE_MONSTER2(����, 32)�� ������ ���� ����, 32
//#define RACE_NPC					(USHORT)0x0040	// NPC, 64
#define RACE_INFLUENCE_SUBLEADER_1	(USHORT)0x0020	// 32, ������ �������� 1 - VCN(�λ�ɰ�), ANI(������), // 2007-10-06 by cmkwon, �������� 2���� ȣĪ�� �ٸ��� ���� -
#define RACE_INFLUENCE_SUBLEADER_2	(USHORT)0x0040	// 64, ������ �������� 2 - VCN(��������), ANI(����������), // 2007-10-06 by cmkwon, �������� 2���� ȣĪ�� �ٸ��� ���� -
#define RACE_OPERATION				(USHORT)0x0080	// ������, 128
#define RACE_GAMEMASTER				(USHORT)0x0100	// ���Ӹ�����, 256
#define RACE_MONITOR				(USHORT)0x0200	// �����, 512
#define RACE_GUEST					(USHORT)0x0400	// �Խ�Ʈ, 1024
#define RACE_DEMO					(USHORT)0x0800	// �ÿ�(����)��, 2048
#define RACE_DELETED_CHARACTER		(USHORT)0x4000	// ������ ĳ����, 16384 // 2007-02-21 by cmkwon
#define RACE_ALL					(USHORT)0x000F	// ��� ����, (RACE_BATTALUS|RACE_DECA|RACE_PHILON|RACE_SHARRINE), 15
#define RACE_ACCOUNT_TYPE_MASK		(RACE_OPERATION|RACE_GAMEMASTER|RACE_MONITOR|RACE_GUEST|RACE_DEMO)
#define RACE_INFLUENCE_SUBLEADER_MASK	(RACE_INFLUENCE_SUBLEADER_1|RACE_INFLUENCE_SUBLEADER_2)		// 2007-10-06 by cmkwon, �������� 2���� ȣĪ�� �ٸ��� ���� - ���� �߰�
#define COMPARE_RACE(VAR, MASK)		(((VAR) & (MASK)) != 0)
/* - ���� ���� ���� -
			�����ڼ�Ȯ��	���ͼ�ȯ	���̵�	�̵�/ȣ��	�����ۻ���	�����ۻ��	��ü�޽���	���ڽ�	PK ����
������		����			����		����	����		����		��ΰ���	����		����	����
���Ӹ�����	����			����		����	����		�Ұ�		��ΰ���	����		����	����
�����		����			�Ұ�		����	�̵�������	�Ұ�		�Ұ�		�Ұ�		�⺻	�Ұ�
�Խ�Ʈ		�Ұ�			�Ұ�		�Ұ�	�Ұ�		�Ұ�		����30����	�Ұ�		�Ұ�	�Ұ�
����		�Ұ�			�Ұ�		����	�Ұ�		�Ұ�		����50����	�Ұ�		����	����
�Ϲ�		�Ϲ�			�Ϲ�		�Ϲ�	�Ϲ�		�Ϲ�		�Ϲ�		�Ϲ�		�Ϲ�	�Ϲ�
*/


////////////////////////////////////
// ĳ���� ������ ����
#define UNITKIND_BT01				(USHORT)0x0001	// BT - 01��, B-GEAR, 1
#define UNITKIND_BT02				(USHORT)0x0002	// BT - 02��, B-GEAR, 2
#define UNITKIND_BT03				(USHORT)0x0004	// BT - 03��, B-GEAR, 4
#define UNITKIND_BT04				(USHORT)0x0008	// BT - 04��, B-GEAR, 8

#define UNITKIND_OT01				(USHORT)0x0010	// OT - 01��, M-GEAR, 16
#define UNITKIND_OT02				(USHORT)0x0020	// OT - 02��, M-GEAR, 32
#define UNITKIND_OT03				(USHORT)0x0040	// OT - 03��, M-GEAR, 64
#define UNITKIND_OT04				(USHORT)0x0080	// OT - 04��, M-GEAR, 128

#define UNITKIND_DT01				(USHORT)0x0100	// DT - 01��, A-GEAR, 256
#define UNITKIND_DT02				(USHORT)0x0200	// DT - 02��, A-GEAR, 512
#define UNITKIND_DT03				(USHORT)0x0400	// DT - 03��, A-GEAR, 1024
#define UNITKIND_DT04				(USHORT)0x0800	// DT - 04��, A-GEAR, 2048

#define UNITKIND_ST01				(USHORT)0x1000	// ST - 01��, I-GEAR, 4096
#define UNITKIND_ST02				(USHORT)0x2000	// ST - 02��, I-GEAR, 8192
#define UNITKIND_ST03				(USHORT)0x4000	// ST - 03��, I-GEAR, 16384
#define UNITKIND_ST04				(USHORT)0x8000	// ST - 04��, I-GEAR, 32768

#define UNITKIND_BGEAR_MASK			(USHORT)0x000F	// B-GEAR, 15
#define UNITKIND_MGEAR_MASK			(USHORT)0x00F0	// M-GEAR, 240
#define UNITKIND_AGEAR_MASK			(USHORT)0x0F00	// A-GEAR, 3840
#define UNITKIND_IGEAR_MASK			(USHORT)0xF000	// I-GEAR, 61440
#define UNITKIND_ALL_MASK			(USHORT)0xFFFF	// 65535

#define IS_BT(x) ((x&UNITKIND_BGEAR_MASK) != 0)	// B-GEAR
#define IS_OT(x) ((x&UNITKIND_MGEAR_MASK) != 0)	// M-GEAR
#define IS_DT(x) ((x&UNITKIND_AGEAR_MASK) != 0)	// A-GEAR
#define IS_ST(x) ((x&UNITKIND_IGEAR_MASK) != 0)	// I-GEAR

#define UNITKIND_BGEAR		((USHORT)0x0001)	// B-GEAR, 1
#define UNITKIND_MGEAR		((USHORT)0x0010)	// M-GEAR, 16
#define UNITKIND_AGEAR		((USHORT)0x0100)	// A-GEAR, 256
#define UNITKIND_IGEAR		((USHORT)0x1000)	// I-GEAR, 4096

#define IS_BGEAR(x) ((x&UNITKIND_BGEAR_MASK) != 0)	// B-GEAR
#define IS_MGEAR(x) ((x&UNITKIND_MGEAR_MASK) != 0)	// M-GEAR
#define IS_AGEAR(x) ((x&UNITKIND_AGEAR_MASK) != 0)	// A-GEAR
#define IS_IGEAR(x) ((x&UNITKIND_IGEAR_MASK) != 0)	// I-GEAR
#define IS_SAME_UNITKIND(x1, x2) ( (IS_BGEAR(x1)&&IS_BGEAR(x2))	 ||	\
									(IS_MGEAR(x1)&&IS_MGEAR(x2)) ||	\
									(IS_AGEAR(x1)&&IS_AGEAR(x2)) ||	\
									(IS_IGEAR(x1)&&IS_IGEAR(x2)) )

////////////////////////////////////
// ĳ���� �ź�, STATUS_XXX
#define STATUS_BEGINNER_AIRMAN		((BYTE)0)	// �Ʒ� �����, 1 ~ 100	
#define STATUS_3RD_CLASS_AIRMAN		((BYTE)1)	// 3rd �����, 101 ~ 300, �̼����� �±� ����
#define STATUS_2ND_CLASS_AIRMAN		((BYTE)2)	// 2nd �����, 301 ~ 600, �̼����� �±� ����
#define STATUS_1ST_CLASS_AIRMAN		((BYTE)3)	// 1st �����, 601 ~ 1000, �̼����� �±� ����
#define STATUS_3RD_CLASS_WINGMAN	((BYTE)4)	// 3rd ����, 1001 ~ 1500, �̼����� �±� ����
#define STATUS_2ND_CLASS_WINGMAN	((BYTE)5)	// 2nd ����, 1501 ~ 2000, �̼����� �±� ����
#define STATUS_1ST_CLASS_WINGMAN	((BYTE)6)	// 1st ����, 2001 ~ 2500, �̼����� �±� ����
#define STATUS_3RD_CLASS_LEADER		((BYTE)7)	// 3rd ����, 2501 ~ 5000, ���� ����
#define STATUS_2ND_CLASS_LEADER		((BYTE)8)	// 2nd ����, 5000 ~ 10000, ���� ���� �� 1�ܰ� ���� �̼� Ŭ���� �� (5�� �߰� �ο� Ȯ��), ��ü �� ������ ���� ���� ������� ����
#define STATUS_1ST_CLASS_LEADER		((BYTE)9)	// 1st ����, 10001 ~ 15000, ���� ���� �� 2�ܰ� ���� �̼� Ŭ���� �� (5�� �߰� �ο� Ȯ�� �� ���� ��ũ ���� ����), ��ü �� ������ ���� ���� ������� ����
#define STATUS_3RD_CLASS_ACE		((BYTE)10)	// 3rd ���̽�, 15001 ~ 20000, ���� ���� �� 3�ܰ� ���� �̼� Ŭ���� �� (5�� �߰� �ο� Ȯ�� �� ���� â�� ���� ����), ��ü �� ������ ���� ���� ������� ����
#define STATUS_2ND_CLASS_ACE		((BYTE)11)	// 2nd ���̽�, 20000 ~ 25000, ���� ���� �� 4�ܰ� ���� �̼� Ŭ���� �� (5�� �߰� �ο� Ȯ�� �� �������� ��û ����), ��ü �� ������ ���� ���� ������� ����
#define STATUS_1ST_CLASS_ACE		((BYTE)12)	// 1st ���̽�, 25001 ~ 30000, ���� ���� �� 5�ܰ� ���� �̼� Ŭ���� �� (10�� �߰� �ο� Ȯ��), ��ü �� ������ ���� ���� ������� ����
#define STATUS_COPPER_CLASS_GENERAL	((BYTE)13)	// ���强, -, ���� ���� �� ��� ���� �̼� Ŭ���� �� (10�� �߰� �ο� Ȯ��), ��ü �� ������ ���� ���� ������� ����
#define STATUS_SILVER_CLASS_GENERAL	((BYTE)14)	// ���强, -, 1���� ���ÿ� ���� ���ɱ� ���� , ���� �� ���� �� ������ ���� ���� ������� ����
#define STATUS_GOLD_CLASS_GENERAL	((BYTE)15)	// ���强, -, 2���� ���ÿ� ���� ���ɱ� ����, ���� �� ���� �� ������ ���� ���� ������� ����
#define STATUS_MASTER_GENERAL		((BYTE)16)	// ���强, -, ��� �� �� ���ÿ� ���� ���ɱ� ����, ���� �� ���� �� ������ ���� ���� ������� ����

////////////////////////////////////
// ĳ���� & ������ ����
typedef UINT64 BodyCond_t;

#define NUM_OF_BODYCONDITION_BIT		64

// Body Conditions
#define BODYCON_SET_OR_CLEAR_MASK		(BodyCond_t)0x0000000000000001		// set(1) or clear(0)
// start - exclusive condition
#define BODYCON_FLY_MASK				(BodyCond_t)0x0000000000000002		// ����
#define BODYCON_LANDING_MASK			(BodyCond_t)0x0000000000000040		// ������, exclusive�ؾ� �Ѵٰ� ��û��, by kelovon w/ jinkin, 20040203
#define BODYCON_LANDED_MASK				(BodyCond_t)0x0000000000000004		// ���� �Ϸ�
#define BODYCON_DEAD_MASK				(BodyCond_t)0x0000000000000008		// ����
#define BODYCON_NOT_USED1_MASK			(BodyCond_t)0x0000000000000010
// end - exclusive condition
// start - new bodycon
#define BODYCON_WEAPON_POSITION_MASK	(BodyCond_t)0x0000000000000020		// 2005-12-16 by cmkwon, 1��/2�� ���� �������� ���� �ٵ������, BODYCON_NOT_USED2_MASK�� ������
#define BODYCON_BOOSTER1_MASK			(BodyCond_t)0x0000000000000080		// �ν���(1~10) - ����(������ ���� ��)
#define BODYCON_BOOSTER2_MASK			(BodyCond_t)0x0000000000000100		// �ν���(10~15) - ������(WŰ�� ���� ����)
#define BODYCON_BOOSTER3_MASK			(BodyCond_t)0x0000000000000200		// �ν���(70~80) - �ν��ͽ�(SpaceŰ�� ���� ����)
#define BODYCON_BOOSTER4_MASK			(BodyCond_t)0x0000000000000400		// �ν���(81~100) - ������(SŰ�� ���� ����)
#define BODYCON_NIGHTFLY_MASK			(BodyCond_t)0x0000000000000800		// �߰�����(�߰���)
#define BODYCON_EXPLOSION_MASK			(BodyCond_t)0x0000000000001000		// ����
#define BODYCON_DAMAGE1_MASK			(BodyCond_t)0x0000000000002000		// ������1, ������
#define BODYCON_DAMAGE2_MASK			(BodyCond_t)0x0000000000004000		// ������2, ������
#define BODYCON_DAMAGE3_MASK			(BodyCond_t)0x0000000000008000		// ������3, ������
#define BODYCON_CREATION_MASK			(BodyCond_t)0x0000000000010000		// ������
#define BODYCON_FIRE_MASK				(BodyCond_t)0x0000000000020000		// �߻�
#define BODYCON_BULLET_MASK				(BodyCond_t)0x0000000000040000		// źü
#define BODYCON_HIT_MASK				(BodyCond_t)0x0000000000080000		// Ÿ��


///////////////////////////////////////////////////////////////////////////////
// Ŭ���̾�Ʈ������ ���Ǵ� BodyCondition
// ���̴� �ٵ� ����� ����
#define RADAR_BODYCON_BOOSTER_ON		(BodyCond_t)0x0000000000000008		// ���� ����
#define RADAR_BODYCON_BOOSTER_OFF		(BodyCond_t)0x0000000000000002		// ���� ����

// cmkwon, ������ʹ� ĳ���� ���Ͱ� �ٸ��� �����

///////////////////////////////////////////////////////////////////////////////
// Strat --> Character BodyCondition, BODYCON_XXX
#define BODYCON_SPRAY_MASK					(BodyCond_t)0x0000000000100000		// ������,����,��
#define BODYCON_APRE_MASK					(BodyCond_t)0x0000000000200000		// 2005-12-07 by cmkwon, A��� �� ������ Bodycondition
// end - new bodycon
#define BODYCON_SHAKEING_MASK				(BodyCond_t)0x0000000004000000		// ��鸲
#define BODYCON_FREEZING_MASK				(BodyCond_t)0x0000000008000000		// ����
#define BODYCON_ATTACKSLOW_MASK				(BodyCond_t)0x0000000010000000		// ����� ������
#define BODYCON_SLOW_MASK					(BodyCond_t)0x0000000020000000		// ���ǵ� ������
#define BODYCON_NOATTACK_MASK				(BodyCond_t)0x0000000040000000		// ���ݱ���
#define BODYCON_ILLUSION_MASK				(BodyCond_t)0x0000000080000000		// ����
#define BODYCON_FIGHTING_MASK				(BodyCond_t)0x0000000100000000		// ������
#define BODYCON_EVENT_HANDLE_MASK			(BodyCond_t)0x0000000200000000		// �̺�Ʈ(����, ����) ó����, ������ client�� �̵� ���� ����
#define BODYCON_STOP_MASK					(BodyCond_t)0x0000000400000000		// 2010-03-30 by cmkwon, �ʵ�â�� ������ �̿� ���� ����(E0044710) - ������ �϶� B+Enter ����, // ��������	------> ���� ���ϴ� 2002.11.25.�� �߰�
#define BODYCON_STEALTH_MASK				(BodyCond_t)0x0000000800000000		// ���ڽ�����
#define BODYCON_GHOST_MASK					(BodyCond_t)0x0000001000000000		// ����Ʈ����
#define BODYCON_CLOAKING_MASK				(BodyCond_t)0x0000002000000000		// Ŭ��ŷ����
#define BODYCON_FALL_MASK					(BodyCond_t)0x0000004000000000		// �߶�����
#define BODYCON_SKILLBAN_MASK				(BodyCond_t)0x0000008000000000		// ��ų����������
#define BODYCON_RESIST_MASK					(BodyCond_t)0x0000010000000000		// ��ų���׻���
#define BODYCON_SHIELD_MASK					(BodyCond_t)0x0000020000000000		// ���� ����, 20030917�� �߰�
#define BODYCON_BOOSTER5_MASK				(BodyCond_t)0x0000040000000000		// ������ �ν���
#define BODYCON_TAKEOFF_MASK				(BodyCond_t)0x0000080000000000		// �̷�
#define BODYCON_SIEGE_ON_MASK				(BodyCond_t)0x0000100000000000		// ���� ��� ��
#define BODYCON_SIEGE_OFF_MASK				(BodyCond_t)0x0000200000000000		// ���� ��� ����
#define BODYCON_DECOY_MASK					(BodyCond_t)0x0000400000000000		// ������ ����
#define BODYCON_CHARACTER_MODE_STOP			(BodyCond_t)0x0001000000000000		// ĳ���� ��� - ����
#define BODYCON_CHARACTER_MODE_WALK			(BodyCond_t)0x0002000000000000		// ĳ���� ��� - �ȱ�
#define BODYCON_CHARACTER_MODE_RUN			(BodyCond_t)0x0004000000000000		// ĳ���� ��� - �ٱ�
#define BODYCON_EVENT_SELECTCHANNEL_MASK	(BodyCond_t)0x0008000000000000		// ä�� ���� â ����, BODYCON_EVENT_HANDLE_MASK�� ���� ���δ�
#define BODYCON_ROLLING_MASK				(BodyCond_t)0x0010000000000000		// 2009-07-07 by cmkwon, �κ� �Ƹ� ���� ó�� �߰� - �Ѹ� �ٵ������ �߰�
#define BODYCON_PET_POSITION_MASK			(BodyCond_t)0x0020000000000000		// 2010-06-15 by shcho&hslee ��ý��� �� ���� ��ġ BodyCon �߰�
#define BODYCON_MARK_POSITION_MASK			(BodyCond_t)0x0040000000000000		// 2011-03-21 by jhAhn	��ũ�ý��� â����ġ BodyCon �߰�
// End --> Character BodyCondition
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Start --> Monster BodyCondition
#define COUNT_MONSTER_ATTACK_BODYCON	2		// �ϳ��� Attack�� ������ ������ ����(PreAttack, FireAttack)

#define BODYCON_MON_PREATTACK1_MASK		(BodyCond_t)0x0000000000100000		// ����1�� �غ�			(Effect = 20)
#define BODYCON_MON_FIREATTACK1_MASK	(BodyCond_t)0x0000000000200000		// ����1�� �߻�			(Effect = 21)

#define BODYCON_MON_PREATTACK2_MASK		(BodyCond_t)0x0000000000400000		// ����2�� �غ�			(Effect = 22)
#define BODYCON_MON_FIREATTACK2_MASK	(BodyCond_t)0x0000000000800000		// ����2�� �߻�			(Effect = 23)

#define BODYCON_MON_PREATTACK3_MASK		(BodyCond_t)0x0000000001000000		// ����3�� �غ�			(Effect = 24)
#define BODYCON_MON_FIREATTACK3_MASK	(BodyCond_t)0x0000000002000000		// ����3�� �߻�			(Effect = 25)

#define BODYCON_MON_PREATTACK4_MASK		(BodyCond_t)0x0000000004000000		// ����4�� �غ�			(Effect = 26)
#define BODYCON_MON_FIREATTACK4_MASK	(BodyCond_t)0x0000000008000000		// ����4�� �߻�			(Effect = 27)

#define BODYCON_MON_PREATTACK5_MASK		(BodyCond_t)0x0000000010000000		// ����5�� �غ�			(Effect = 28)
#define BODYCON_MON_FIREATTACK5_MASK	(BodyCond_t)0x0000000020000000		// ����5�� �߻�			(Effect = 29)

////////////////////////////////////////////////////////////////////////////////
// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ��Ʈ�ѽ�ų�� �̸� ����
//#define BODYCON_MON_PREATTACK6_MASK		(BodyCond_t)0x0000000040000000		// ����6�� �߻�			(Effect = 30)
//#define BODYCON_MON_FIREATTACK6_MASK	(BodyCond_t)0x0000000080000000		// ����6�� �Ϸ�			(Effect = 31)
#define BODYCON_MON_PRECONTROLSKILL_MASK	(BodyCond_t)0x0000000040000000		// ��Ʈ�ѽ�ų�� �߻�			(Effect = 30)
#define BODYCON_MON_FIRECONTROLSKILL_MASK	(BodyCond_t)0x0000000080000000		// ��Ʈ�ѽ�ų�� �Ϸ�			(Effect = 31)

#define BODYCON_MON_AUTODESTROYED_MASK	(BodyCond_t)0x0000000100000000		// ���� �ڵ� �Ҹ�		(Effect = 32)
#define BODYCON_MON_BUILDING			(BodyCond_t)0x0000001000000000		// 2007-09-06 by cmkwon, ���� ������			(Effect = 36)
#define BODYCON_MON_BUILDED				(BodyCond_t)0x0000002000000000		// 2007-09-06 by cmkwon, ���� ���ſϷ�		(Effect = 37)
////////////////////////////////////////////////////////////////////////////////
// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - 6~15���� �߰�
#define BODYCON_MON_PREATTACK6_MASK		(BodyCond_t)0x0000010000000000		// ����6�� �غ�			(Effect = 40)
#define BODYCON_MON_FIREATTACK6_MASK	(BodyCond_t)0x0000020000000000		// ����6�� �߻�			(Effect = 41)
#define BODYCON_MON_PREATTACK7_MASK		(BodyCond_t)0x0000040000000000		// ����7�� �غ�			(Effect = 42)
#define BODYCON_MON_FIREATTACK7_MASK	(BodyCond_t)0x0000080000000000		// ����7�� �߻�			(Effect = 43)
#define BODYCON_MON_PREATTACK8_MASK		(BodyCond_t)0x0000100000000000		// ����8�� �غ�			(Effect = 44)
#define BODYCON_MON_FIREATTACK8_MASK	(BodyCond_t)0x0000200000000000		// ����8�� �߻�			(Effect = 45)
#define BODYCON_MON_PREATTACK9_MASK		(BodyCond_t)0x0000400000000000		// ����9�� �غ�			(Effect = 46)
#define BODYCON_MON_FIREATTACK9_MASK	(BodyCond_t)0x0000800000000000		// ����9�� �߻�			(Effect = 47)
#define BODYCON_MON_PREATTACK10_MASK	(BodyCond_t)0x0001000000000000		// ����10�� �غ�			(Effect = 48)
#define BODYCON_MON_FIREATTACK10_MASK	(BodyCond_t)0x0002000000000000		// ����10�� �߻�			(Effect = 49)
#define BODYCON_MON_PREATTACK11_MASK	(BodyCond_t)0x0004000000000000		// ����11�� �غ�			(Effect = 50)
#define BODYCON_MON_FIREATTACK11_MASK	(BodyCond_t)0x0008000000000000		// ����11�� �߻�			(Effect = 51)
#define BODYCON_MON_PREATTACK12_MASK	(BodyCond_t)0x0010000000000000		// ����12�� �غ�			(Effect = 52)
#define BODYCON_MON_FIREATTACK12_MASK	(BodyCond_t)0x0020000000000000		// ����12�� �߻�			(Effect = 53)
#define BODYCON_MON_PREATTACK13_MASK	(BodyCond_t)0x0040000000000000		// ����13�� �غ�			(Effect = 54)
#define BODYCON_MON_FIREATTACK13_MASK	(BodyCond_t)0x0080000000000000		// ����13�� �߻�			(Effect = 55)
#define BODYCON_MON_PREATTACK14_MASK	(BodyCond_t)0x0100000000000000		// ����14�� �غ�			(Effect = 56)
#define BODYCON_MON_FIREATTACK14_MASK	(BodyCond_t)0x0200000000000000		// ����14�� �߻�			(Effect = 57)
#define BODYCON_MON_PREATTACK15_MASK	(BodyCond_t)0x0400000000000000		// ����15�� �غ�			(Effect = 58)
#define BODYCON_MON_FIREATTACK15_MASK	(BodyCond_t)0x0800000000000000		// ����15�� �߻�			(Effect = 59)

////////////////////////////////////////////////////////////////////////////////
// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - 6~15, ��Ʈ�ѽ�ų���� �߰�
#define BODYCON_MON_ATTACK1_MASK		(BodyCond_t)(BODYCON_MON_PREATTACK1_MASK | BODYCON_MON_FIREATTACK1_MASK)	// ����1
#define BODYCON_MON_ATTACK2_MASK		(BodyCond_t)(BODYCON_MON_PREATTACK2_MASK | BODYCON_MON_FIREATTACK2_MASK)	// ����2
#define BODYCON_MON_ATTACK3_MASK		(BodyCond_t)(BODYCON_MON_PREATTACK3_MASK | BODYCON_MON_FIREATTACK3_MASK)	// ����3
#define BODYCON_MON_ATTACK4_MASK		(BodyCond_t)(BODYCON_MON_PREATTACK4_MASK | BODYCON_MON_FIREATTACK4_MASK)	// ����4
#define BODYCON_MON_ATTACK5_MASK		(BodyCond_t)(BODYCON_MON_PREATTACK5_MASK | BODYCON_MON_FIREATTACK5_MASK)	// ����5
#define BODYCON_MON_ATTACK6_MASK		(BodyCond_t)(BODYCON_MON_PREATTACK6_MASK | BODYCON_MON_FIREATTACK6_MASK)	// ����6
#define BODYCON_MON_ATTACK7_MASK		(BodyCond_t)(BODYCON_MON_PREATTACK7_MASK | BODYCON_MON_FIREATTACK7_MASK)	// ����7
#define BODYCON_MON_ATTACK8_MASK		(BodyCond_t)(BODYCON_MON_PREATTACK8_MASK | BODYCON_MON_FIREATTACK8_MASK)	// ����8
#define BODYCON_MON_ATTACK9_MASK		(BodyCond_t)(BODYCON_MON_PREATTACK9_MASK | BODYCON_MON_FIREATTACK9_MASK)	// ����9
#define BODYCON_MON_ATTACK10_MASK		(BodyCond_t)(BODYCON_MON_PREATTACK10_MASK | BODYCON_MON_FIREATTACK10_MASK)	// ����10
#define BODYCON_MON_ATTACK11_MASK		(BodyCond_t)(BODYCON_MON_PREATTACK11_MASK | BODYCON_MON_FIREATTACK11_MASK)	// ����11
#define BODYCON_MON_ATTACK12_MASK		(BodyCond_t)(BODYCON_MON_PREATTACK12_MASK | BODYCON_MON_FIREATTACK12_MASK)	// ����12
#define BODYCON_MON_ATTACK13_MASK		(BodyCond_t)(BODYCON_MON_PREATTACK13_MASK | BODYCON_MON_FIREATTACK13_MASK)	// ����13
#define BODYCON_MON_ATTACK14_MASK		(BodyCond_t)(BODYCON_MON_PREATTACK14_MASK | BODYCON_MON_FIREATTACK14_MASK)	// ����14
#define BODYCON_MON_ATTACK15_MASK		(BodyCond_t)(BODYCON_MON_PREATTACK15_MASK | BODYCON_MON_FIREATTACK15_MASK)	// ����15
#define BODYCON_MON_CONTROLSKILL_MASK	(BodyCond_t)(BODYCON_MON_PRECONTROLSKILL_MASK | BODYCON_MON_FIRECONTROLSKILL_MASK)	// ��Ʈ�ѽ�ų
#define BODYCON_MON_PREATTACK_ALL_MASK	(BodyCond_t)(BODYCON_MON_PREATTACK1_MASK | BODYCON_MON_PREATTACK2_MASK \
													| BODYCON_MON_PREATTACK3_MASK | BODYCON_MON_PREATTACK4_MASK \
													| BODYCON_MON_PREATTACK5_MASK | BODYCON_MON_PREATTACK6_MASK \
													| BODYCON_MON_PREATTACK7_MASK | BODYCON_MON_PREATTACK8_MASK \
													| BODYCON_MON_PREATTACK9_MASK | BODYCON_MON_PREATTACK10_MASK \
													| BODYCON_MON_PREATTACK11_MASK | BODYCON_MON_PREATTACK12_MASK \
													| BODYCON_MON_PREATTACK13_MASK | BODYCON_MON_PREATTACK14_MASK \
													| BODYCON_MON_PREATTACK15_MASK | BODYCON_MON_PRECONTROLSKILL_MASK)	// ��� ���� �غ�
#define BODYCON_MON_FIREATTACK_ALL_MASK	(BodyCond_t)(BODYCON_MON_FIREATTACK1_MASK | BODYCON_MON_FIREATTACK2_MASK \
													| BODYCON_MON_FIREATTACK3_MASK | BODYCON_MON_FIREATTACK4_MASK \
													| BODYCON_MON_FIREATTACK5_MASK | BODYCON_MON_FIREATTACK6_MASK \
													| BODYCON_MON_FIREATTACK7_MASK | BODYCON_MON_FIREATTACK8_MASK \
													| BODYCON_MON_FIREATTACK9_MASK | BODYCON_MON_FIREATTACK10_MASK \
													| BODYCON_MON_FIREATTACK11_MASK | BODYCON_MON_FIREATTACK12_MASK \
													| BODYCON_MON_FIREATTACK13_MASK | BODYCON_MON_FIREATTACK14_MASK \
													| BODYCON_MON_FIREATTACK15_MASK | BODYCON_MON_FIRECONTROLSKILL_MASK)	// ��� ���� �غ�
#define BODYCON_MON_ATTACKALL_MASK		(BodyCond_t)(BODYCON_MON_ATTACK1_MASK | BODYCON_MON_ATTACK2_MASK \
													| BODYCON_MON_ATTACK3_MASK | BODYCON_MON_ATTACK4_MASK \
													| BODYCON_MON_ATTACK5_MASK | BODYCON_MON_ATTACK6_MASK \
													| BODYCON_MON_ATTACK7_MASK | BODYCON_MON_ATTACK8_MASK \
													| BODYCON_MON_ATTACK9_MASK | BODYCON_MON_ATTACK10_MASK \
													| BODYCON_MON_ATTACK11_MASK | BODYCON_MON_ATTACK12_MASK \
													| BODYCON_MON_ATTACK13_MASK | BODYCON_MON_ATTACK14_MASK \
													| BODYCON_MON_ATTACK15_MASK | BODYCON_MON_CONTROLSKILL_MASK)		// ���� ���� ���� BodyCondition�� Clear�ϱ� ���� define

// End --> Monster BodyCondition
///////////////////////////////////////////////////////////////////////////////

// bit ���� ��ũ��
#define CLEAR_BODYCON_BIT(VAR, MASK) { VAR &= ~(MASK); }
#define SET_BODYCON_BIT(VAR, MASK)								\
{																\
	if ((MASK & BODYCON_EX_STATE_CLEAR_MASK) != 0)				\
	{															\
		CLEAR_BODYCON_BIT(VAR, BODYCON_EX_STATE_CLEAR_MASK);	\
	}															\
	if ((MASK & BODYCON_BOOSTER_EX_STATE_CLEAR_MASK) != 0)		\
	{															\
		CLEAR_BODYCON_BIT(VAR, BODYCON_BOOSTER_EX_STATE_CLEAR_MASK);\
	}															\
	VAR |= MASK;												\
}
#define COMPARE_BODYCON_BIT(VAR, MASK) (((VAR) & (MASK)) != 0)
#define BODYCON_EX_STATE_CLEAR_MASK		(BodyCond_t)(BODYCON_FLY_MASK | BODYCON_LANDING_MASK | BODYCON_LANDED_MASK | BODYCON_DEAD_MASK | BODYCON_NOT_USED1_MASK | BODYCON_CHARACTER_MODE_STOP | BODYCON_CHARACTER_MODE_WALK | BODYCON_CHARACTER_MODE_RUN)
										// BODYCON_FLY_MASK | BODYCON_LANDED_MASK | BODYCON_LANDING_MASK | BODYCON_DEAD_MASK | BODYCON_NOT_USED_MASK
										// ���� �װ��� bit�� set�Ҷ��� �׻� �� mask�� clear���־�� ��
										// �� state�� exclusive�ϱ� �����̴�
										//
										// ex)
										// CLEAR_BODYCON_BIT( c, BODYCON_EX_STATE_CLEAR_MASK)
										// SET_BODYCON_BIT( c, BODYCON_FLY_MASK)
#define BODYCON_BOOSTER_EX_STATE_CLEAR_MASK	(BodyCond_t)(BODYCON_BOOSTER1_MASK | BODYCON_BOOSTER2_MASK | BODYCON_BOOSTER3_MASK | BODYCON_BOOSTER4_MASK \
											| BODYCON_BOOSTER5_MASK | BODYCON_SIEGE_ON_MASK | BODYCON_SIEGE_OFF_MASK)
											// BODYCON_BOOSTER1_MASK | BODYCON_BOOSTER2_MASK | BODYCON_BOOSTER3_MASK | BODYCON_BOOSTER4_MASK
#define BODYCON_KEEPING_MASK			(BodyCond_t)(BODYCON_EX_STATE_CLEAR_MASK)	// ������ body coditions
#define BODYCON_CHARACTER_MODE_MASK		(BodyCond_t)(BODYCON_CHARACTER_MODE_STOP|BODYCON_CHARACTER_MODE_WALK|BODYCON_CHARACTER_MODE_RUN)		// 2006-01-23 by cmkwon
#define BODYCON_MON_BUILD_MASK			(BodyCond_t)(BODYCON_MON_BUILDING|BODYCON_MON_BUILDED)		// 2007-09-10 by dhjin



////////////////////////////////////
// ������ �迭
#define FACTION_GENERAL					0	// �Ϲ����� ����
#define FACTION_GUN						1	// ������ (�����, ��)
#define FACTION_ROCKET					2	// �������� (����, ����ź)
#define FACTION_SPECIAL					3	// Ư���� ���� (�ΰ����� ����� �ִ� ����)


///////////////////////////////////
// MonsterForm(������ ����)
#define FORM_FLYING_RIGHT				0	// ���������� (��������·� �����ϸ� ����)
#define FORM_FLYING_COPTER				1	// �������� (������·� �����ϸ� ����)
#define FORM_GROUND_MOVE				2	// ������	  (�� ���� �̵��ϸ� ����)
#define FORM_FLYINGandGROUND_RIGHT		3	// ��������� (����)
#define FORM_FLYINGandGROUND_COPTER		4	// ��������� (����)
#define FORM_SWIMMINGFLYING_RIGHT		5	// ���������� (���ӿ��� ������ ���� ����, ���������)
#define FORM_SWIMMINGFLYING_COPTER		6	// ���������� (���ӿ��� ������ ���� ����, ��� ������)
//#define FORM_SWIMMING					7	// ���������� (���ӿ��� ����)
#define FORM_OBJECT_STOP				8	// ������Ʈ ���� TargetVector�� ��ȭ�� ��������
#define FORM_OBJECT_PLANE_ROTATE		9	// ������Ʈ ���� TargetVector�� �������θ� �̵���(2���� ��ȭ)
#define FORM_OBJECT_CANNON				10	// ������Ʈ ���� TargetVector�� �����·� �̵� ������

#define IS_OBJECT_MON_FORM(MonForm)		((MonForm) == FORM_OBJECT_STOP || (MonForm) == FORM_OBJECT_PLANE_ROTATE || (MonForm) == FORM_OBJECT_CANNON)		// 2008-04-16 by cmkwon, ���� ��� �� ���� ��ȯ �̺�Ʈ �ý��� ���� - 

///////////////////////////////////
// Monster Attack Pattern(������ ���� ����)
#define ATTPAT_NORMAL					0	// �Ϲ� ���� ���� ����
//#define ATTPAT_BODYSLAM					1	// ��ü�� �̿��� �������
#define ATTPAT_SELFDESTRUCTION			2	// ��ü�� �̿��� ��������
#define ATTPAT_RETREAT					3	// HP�� 30% ������ ��� ����� ������ �ݺ�
#define ATTPAT_HITANDRUN				4	// ���� �� ���� �ݺ��ϴ� ����
// 2005-05-02 by cmkwon, AttackObjec�� �����ؾ���
//#define ATTPAT_TIBE						5	// ���� ������ ������ ���� �����ϴ� ����
#define ATTPAT_ONEATATTCK				6	// ó�� Ÿ���� ���� ���ָ� ������ �����ϴ� ����
#define ATTPAT_PK						7	// PK ��ġ�� ���� ����� ����

///////////////////////////////////
// Monster Move Pattern(������ �̵�����)
#define MOVPAT_STOP						0	// �̵� ����
#define MOVPAT_STRAIGHT					1	// ���� �̵�
#define MOVPAT_RIGHTANDLEFT				2	// �¿�� ���� �̵�
#define MOVPAT_8RIGHTANDLEFT			3	// �¿�� 8�� �̵�
#define MOVPAT_PATROL					4	// ���� ���������� ����
#define MOVPAT_PARTY					5	// ������ ���� �̵�

#define MOVPAT_UPANDDOWN				10	// ���Ϸ� �̵�
#define MOVPAT_OBLIQUE					11	// �밢�� �缱���� ���� �̵�
#define MOVPAT_OBLIQUEANDCURVE			12	// �밢�� �缱���� � �̵�
#define MOVPAT_TELEPORT					13	// ���� �����̵�

// start 2011-05-23 by hskim, ���Ǵ�Ƽ 3�� - ��������Ʈ ����
#define MOVPAT_FOLLOWPATH				20	//  ������ ��� �̵� (��������Ʈ ���󰡱�)
// end 2011-05-23 by hskim, ���Ǵ�Ƽ 3�� - ��������Ʈ ����

///////////////////////////////////
// Monster Belligerence(������ ȣ����)
#define BELL_ATATTACK					0	// ������ ��������
#define BELL_DEFENSE					1	// �� ��� �� ��������
#define BELL_RETREAT					2	// HP�� 30% ������ ��� ������ ��������
#define BELL_TAGETATATTACK				3	// ������ ��������, ���� ���� ������ Ÿ�ٸ� �����ϴ� ����
#define BELL_NOTATTACK					4	// ����� �������� �ʴ�����
#define BELL_ATTACK_OUTPOST_PROTECTOR	5	// NPC������ ��ȣ��, ���� ���о��� �����Ѵ�.

///////////////////////////////////////////////////////////////////////////////
// 2007-09-05 by dhjin, ��Ģ ���� - ������ ���ʹ� 10 <= BELL_XXX <= 29�̸� ¦��=VCN, Ȧ��=ANI, // 2006-11-20 by cmkwon, ��Ģ ���� - ������ ���ʹ� 10 <= BELL_XXX <= 19�̸� ¦��=VCN, Ȧ��=ANI
#define BELL_INFLUENCE_VCN				10	// 2005-12-27 by cmkwon, �������̴��� ���¸���	- �˸��� ���¸��� �����Ѵ�.
#define BELL_INFLUENCE_ANI				11	// 2005-12-27 by cmkwon, �˸��� ���¸���			- ���������� ���¸��� �����Ѵ�.
#define BELL_STRATEGYPOINT_VCN			12	// 2005-12-27 by cmkwon, ��������Ʈ ���¸���		- �˸��� ���¸��� �����Ѵ�.
#define BELL_STRATEGYPOINT_ANI			13	// 2005-12-27 by cmkwon, ��������Ʈ ���¸���		- ���������� ���¸��� �����Ѵ�.
#define BELL_OUTPOST_PROTECTOR_VCN		14	// 2007-08-17 by dhjin,  �������̴��� �������� ��ȣ��
#define BELL_OUTPOST_PROTECTOR_ANI		15	// 2007-08-17 by dhjin,  �˸��� �������� ��ȣ��
#define BELL_OUTPOST_RESET_VCN			16	// 2007-08-17 by dhjin,  �������̴��� �������� �߾� ó�� ��ġ
#define BELL_OUTPOST_RESET_ANI			17	// 2007-08-17 by dhjin,  �˸��� �������� �߾� ó�� ��ġ
#define BELL_INFLUENCE_TELEPORT_VCN		18  // 2007-09-05 by dhjin,  ���������� ������ �ڷ���Ʈ 
#define BELL_INFLUENCE_TELEPORT_ANI		19  // 2007-09-05 by dhjin,  �˸��� ������ �ڷ���Ʈ 

#define BELL_ONEY_ATTACK_INFLUENCE_VCN	20	// 2010-07-06 by jskim, �⿩�� ���� ���� ���� �߰� �������̴��� ����, ���ݸ� �ϴ� ���� - �˸��� ���¸��� �����Ѵ�.
#define BELL_ONEY_ATTACK_INFLUENCE_ANI	21	// 2010-07-06 by jskim, �⿩�� ���� ���� ���� �߰� �˸��� ����, ���ݸ� �ϴ� ���� - �������̴��� ���¸��� �����Ѵ�.

#define BELL_INFINITY_DEFENSE_MONSTER			30	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� �������� ����, ���� 31�� ���� ����
#define BELL_INFINITY_ATTACK_MONSTER			31	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� 30�� ���Ϳ� �Ϲ� ���� ����

#define IS_INFLWAR_MONSTER(monBell)				( ((monBell) >= 10) && ((monBell) <= 29) )		// 2007-09-05 by dhjin,  19 => 29
#define IS_MOTHERSHIPWAR_MONSTER(monBell)		( ((monBell) >= BELL_INFLUENCE_VCN) && ((monBell) <= BELL_INFLUENCE_ANI) )	// 2007-08-23 by cmkwon, ��������Ʈ�� ���� �ƴϴ�, // 2007-08-21 by dhjin, ������ �ʿ��� �������� üũ
#define IS_STRATEGYPOINT_MONSTER(monBell)		( ((monBell) >= BELL_STRATEGYPOINT_VCN) && ((monBell) <= BELL_STRATEGYPOINT_ANI) )

#define IS_ONEY_ATTACK_MONSTER(monBell)			( ((monBell) >= BELL_ONEY_ATTACK_INFLUENCE_VCN) && ((monBell) <= BELL_ONEY_ATTACK_INFLUENCE_ANI)) // 2010-07-06 by jskim, �⿩�� ���� ���� ���� �߰�

// 2007-09-19 by cmkwon, ������
#define IS_TELEPORT_MONSTER(monBell)			( ((monBell) >= BELL_INFLUENCE_TELEPORT_VCN) && ((monBell) <= BELL_INFLUENCE_TELEPORT_ANI) )	// 2007-09-19 by dhjin, �ڷ���Ʈ üũ
#define IS_BELL_VCN(monBell)					(0 == (monBell)%2)		// 2006-11-20 by cmkwon, 
#define IS_BELL_ANI(monBell)					(1 == (monBell)%2)		// 2006-11-20 by cmkwon, 
#define IS_SAME_CHARACTER_MONSTER_INFLUENCE(charInfl, monBell)	(  IS_INFLWAR_MONSTER(monBell) \
																	&& ( (COMPARE_INFLUENCE((charInfl), INFLUENCE_TYPE_NORMAL|INFLUENCE_TYPE_VCN) && 0 == (monBell)%2) || (COMPARE_INFLUENCE((charInfl), INFLUENCE_TYPE_NORMAL|INFLUENCE_TYPE_ANI) && 1 == (monBell)%2) )  )

// 2009-12-11 by cmkwon, ������ ��׷η� Ÿ���� �����ϴ� ���� ���� - ������ ���� ���� ���� üũ
#define IS_BELL_ATTACK(monBell)					((monBell) != BELL_NOTATTACK)

// 2007-10-01 by cmkwon, ���������� ���� ���� ����
#define IS_OUTPOST_MONSTER(monBell)				( ((monBell) >= BELL_OUTPOST_PROTECTOR_VCN) && ((monBell) <= BELL_OUTPOST_RESET_ANI) )

// 2006-11-29 by cmkwon, INFLUENCE_TYPE_XXX�� ������ ���� ���¸��� Belligerence�� ���Ѵ�
// 2006-11-29 by cmkwon, �Ʒ��� ���Ǵ� INFLUENCE_TYPE_NORMAL�� IS_INFLWAR_MONSTER()�� üũ���� �ʴ´�, !!! ������� ���� �� üũ�ؾ���
#define GET_SAME_MONSTER_BELL_BY_CHARACTER_INFLTYPE(charInflTy)		( (INFLUENCE_TYPE_VCN==(charInflTy))?BELL_INFLUENCE_VCN:BELL_INFLUENCE_ANI )
#define GET_SAME_CHARACTER_INFL_BY_MONSTER_BELL(monBell)			( (IS_BELL_VCN(monBell))?INFLUENCE_TYPE_VCN:INFLUENCE_TYPE_ANI )
#define GET_OTHER_CHARACTER_INFL_BY_MONSTER_BELL(monBell)			( (IS_BELL_VCN(monBell))?INFLUENCE_TYPE_ANI:INFLUENCE_TYPE_VCN )				// 2009-01-12 by dhjin, ���� ����
#define GET_OTHER_MONSTER_BELL_BY_CHARACTER_INFLTYPE(charInflTy)	( (INFLUENCE_TYPE_VCN==(charInflTy))?BELL_INFLUENCE_ANI:BELL_INFLUENCE_VCN )		// 2006-12-20 by cmkwon, ĳ���Ϳ� ���뼼��

// 2010-03-16 by cmkwon, ����2�� MtoM, MtoC Ÿ�� ���� ���� ���� - 
#define IS_WARABLE_M2M_BELL(AttMonBell, TarMonBell)		( (BELL_INFINITY_ATTACK_MONSTER == (AttMonBell) && BELL_INFINITY_DEFENSE_MONSTER == (TarMonBell)) || (BELL_INFINITY_DEFENSE_MONSTER == (AttMonBell) && BELL_INFINITY_ATTACK_MONSTER == (TarMonBell)) )

// 2006-12-13 by cmkwon
char *GetMonsterBellString(BYTE i_byMonBell);		

///////////////////////////////////
// Monster Attack Object(������ ���� Ÿ�� ����), ATTACKOBJ_XXX
#define ATTACKOBJ_CLOSERANGE			0	// ���� �ٰŸ� ���ְ���
#define ATTACKOBJ_FIRSTATTACK			1	// ���� ������ ���ְ���
#define ATTACKOBJ_LOWHP					2	// HP�� ���� ���� ���ְ���
#define ATTACKOBJ_HIGHHP				3	// HP�� ���� ���� ���ְ���
//#define ATTACKOBJ_PK					4	// PK ��ġ�� ���� ����� ���� - ����� PK �ý����� ����
#define ATTACKOBJ_SAMERACE				5	// ��������, ���ݴ��� ���� ������ Ÿ���� ���� ���͵� ���� �����Ѵ�
#define ATTACKOBJ_RANDOM				6	// �������� ����
#define ATTACKOBJ_AGGRO					7	// 2009-12-11 by cmkwon, ������ ��׷η� Ÿ���� �����ϴ� ���� ���� - 


///////////////////////////////////
// Monster Move Pattern Option(������ �̵� ���� �ɼ�, ��Ʈ �÷��� ���), MPOPTION_XXX,MPOPTION_BIT_XXX
// 2010-01-11 by cmkwon, ���� MPOption 64bit�� ���� - ����(8bit)
#define COMPARE_MPOPTION_BIT(VAR, MASK) (((VAR) & (MASK)) != 0)
#define MPOPTION_BIT_DEAD_FALL					((BitFlag64_t)0x0000000000000001)	// 1,	���Ͱ� ���߽� �߶��Ұ������� �÷���(0�̸� ����)
#define MPOPTION_BIT_MOVE_PARTY					((BitFlag64_t)0x0000000000000002)	// 2,	MPOptionParam1 = ���� ����, MPOptionParam2 = �ִ����� ������ ==> �������⵵ ���ÿ� ���´�
#define MPOPTION_BIT_PATTERN_MONSTER			((BitFlag64_t)0x0000000000000004)	// 4,	���Ͱ� ������ MONSTER_EVENT_MON_NOT_MOVE_AFTER_CREATED_TERM_TICK �̽ð� ���� �������� �ʴ´�, (���ϰ� �ִϸ��̼��� ����Ǵ� �ð�)
#define MPOPTION_BIT_BOSS_MONSTER				((BitFlag64_t)0x0000000000000008)	// 8,	���� ���� �÷��� - MoveRange�� ũ��, ���SPI/���������/������� ������ �ս� ����
#define MPOPTION_BIT_AUTO_DESTROY				((BitFlag64_t)0x0000000000000010)	// 16,	�����ǰ� MPOptionParam1 �ð��� ��� �ϸ� �ڵ� �Ҹ�Ǵ� ������ ����(����:��), �ּ� 1�� ~ �ִ� 255��
#define MPOPTION_BIT_NAMED_MONSTER				((BitFlag64_t)0x0000000000000020)	// 32,	2005-12-16 by cmkwon, ���ӵ� ���� - ���SPI/���������/������� ������ �ս� ����
#define MPOPTION_BIT_RECOGNIZE_INVISIBLE		((BitFlag64_t)0x0000000000000040)	// 64,	2007-01-16 by cmkwon, �κ����� ��ų ������ ĳ���͸� �ν��Ѵ�
#define MPOPTION_BIT_KEY_MONSTER				((BitFlag64_t)0x0000000000000080)	// 128,	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� �̺�Ʈ�� �߻��� �� �ִ� Key����
#define MPOPTION_BIT_NO_ALPHABLENDING_IN_DEAD	((BitFlag64_t)0x0000000000000100)	// 256,	// 2010-01-11 by cmkwon, ���� ���Ľ� ���ĺ�����(AlphaBlending) ó�� ���� �÷��� - 
#define MPOPTION_BIT_KEY_MONSTER_ALIVE_FOR_GAMECLEAR	((BitFlag64_t)0x0000000000000200)	// 512,	// 2010-03-31 by dhjin, ���Ǵ�Ƽ(�������) - ���Ľ� ���Ǵ�Ƽ ���� �Ǵ� Ű����
#define MPOPTION_BIT_STOP_AUTO_CREATE			((BitFlag64_t)0x0000000000000400)	// 1024,	// 2011-10-28 by hskim, EP4 [Ʈ���� �ý���] - ũ����Ż �ý��� - ���� �ڵ� ���� ����
#define MPOPTION_BIT_RECOGNIZE_STEALTH			((BitFlag64_t)0x0000000000000800)	// 2048,	// 2012-11-05 by jhseol, ���ڽ� ������ �ɸ��͸� �ν��Ѵ�.
#define MPOPTION_BIT_ADD_DAMAGE_UNAPPLIED		((BitFlag64_t)0x0000000000001000)	// 4096,	// 2013-07-23 by jhseol, ���� �߰������ ������ �ɼ�.

///////////////////////////////////
// Monster Move Pattern Option - MPOPTION_MOVE_PARTY, ���� ����
#define FORMATION_COLUMN					0		// ����
#define FORMATION_LINE						1		// Ⱦ��
#define FORMATION_TRIANGLE					2		// �ﰢ
#define FORMATION_INVERTED_TRIANGLE			3		// ���ﰢ
#define FORMATION_BELL						4		// ��
#define FORMATION_INVERTED_BELL				5		// ����


///////////////////////////////////////////////////////////////////////////////
// ���� ��������
#define DES_MONHABIT_NOT					0	// (���Ӽ�)
#define DES_MONHABIT_DAY					1	// (�� ���߷� 10% ���)
#define DES_MONHABIT_NIGHT					2	// (�� ���߷� 10% ���)


///////////////////////////////////
// ������ ����(�����, ��, ����.......), ITEMKIND_XXX
// ĳ���Ϳ� ������
//#define IS_CHARACTER_ITEM(x)			((x) >= ITEMKIND_AUTOMATIC && (x) <= ITEMKIND_SKILL_ATTRIBUTE  || ((x) >= ITEMKIND_GENERAL_ITEM_2ND_END && (x) <= ITEMKIND_GENERAL_ITEM_2ND_START))		// 2011-09-20 by hskim, ��Ʈ�� �ý��� 2��, ��� ���ϸ� ������. �켱 �Ϲ� ������ ���� �߰��� ����
// �Ϲ� ������
#define IS_GENERAL_ITEM(x)				(((x) >= ITEMKIND_AUTOMATIC && (x) <= ITEMKIND_GENERAL_ITEM_END) || ((x) >= ITEMKIND_GENERAL_ITEM_2ND_END && (x) <= ITEMKIND_GENERAL_ITEM_2ND_START))		// 2011-09-20 by hskim, ��Ʈ�� �ý��� 2��, �Ϲ� ������ ���� �߰�
// �����
#define IS_WEAPON(x)					((x) >= ITEMKIND_AUTOMATIC && (x) <= ITEMKIND_DECOY)
// 1�� ����
#define IS_PRIMARY_WEAPON(x)			((x) >= ITEMKIND_AUTOMATIC && (x) <= ITEMKIND_MASSDRIVE)
// 1-1�� ����
#define IS_PRIMARY_WEAPON_1(x)			((x) >= ITEMKIND_AUTOMATIC && (x) <= ITEMKIND_MASSDRIVE)	// 1-1�� �����ΰ�?
#define ITEMKIND_AUTOMATIC				(BYTE)0		// �����ƽ��(1-1��)
#define ITEMKIND_VULCAN					(BYTE)1		// ��ĭ��(1-1��)
#define ITEMKIND_DUALIST				(BYTE)2		// ��󸮽�Ʈ��(1-1��)	// 2005-08-01 by hblee : GRENADE -> DUALIST ���� ����.
#define ITEMKIND_CANNON					(BYTE)3		// ĳ����(1-1��)
#define ITEMKIND_RIFLE					(BYTE)4		// �����÷�(1-1��)
#define ITEMKIND_GATLING				(BYTE)5		// ��Ʋ����(1-1��)
#define ITEMKIND_LAUNCHER				(BYTE)6		// ��ó��(1-1��)
#define ITEMKIND_MASSDRIVE				(BYTE)7		// �޽�����̺��(1-1��)
// 1-2�� ����
//#define IS_PRIMARY_WEAPON_2(x)			((x) >= ITEMKIND_RIFLE && (x) <= ITEMKIND_MASSDRIVE)	// 1-2��(BEAM��) �����ΰ�?
#define IS_PRIMARY_WEAPON_2(x)			(FALSE)		// 2005-09-27 by cmkwon, 1-2�� ����� ����
// 2005-09-27 by cmkwon, 1-1������ ������
//#define ITEMKIND_RIFLE					(BYTE)4		// �����÷�(1-2��)
//#define ITEMKIND_GATLING				(BYTE)5		// ��Ʋ����(1-2��)
//#define ITEMKIND_LAUNCHER				(BYTE)6		// ��ó��(1-2��)
//#define ITEMKIND_MASSDRIVE				(BYTE)7		// �޽�����̺��(1-2��)
// 2�� ����
#define IS_SECONDARY_WEAPON(x)			((x) >= ITEMKIND_ROCKET && (x) <= ITEMKIND_DECOY)
// 2-1�� ����
#define IS_SECONDARY_WEAPON_1(x)		((x) >= ITEMKIND_ROCKET && (x) <= ITEMKIND_MINE)
#define ITEMKIND_ROCKET					(BYTE)8		// ���Ϸ�(2-1��)
#define ITEMKIND_MISSILE				(BYTE)9		// �̻��Ϸ�(2-1��)
#define ITEMKIND_BUNDLE					(BYTE)10	// �����(2-1��)
#define ITEMKIND_MINE					(BYTE)11	// ���η�(2-1��)
// 2-2�� ����
#define IS_SECONDARY_WEAPON_2(x)		((x) >= ITEMKIND_SHIELD && (x) <= ITEMKIND_DECOY)
#define ITEMKIND_SHIELD					(BYTE)12	// �����(2-2��)
#define ITEMKIND_DUMMY					(BYTE)13	// ���̷�(2-2��)
#define ITEMKIND_FIXER					(BYTE)14	// �ȼ���(2-2��)
#define ITEMKIND_DECOY					(BYTE)15	// �����̷�(2-2��)
// ������ ������
#define ITEMKIND_DEFENSE				(BYTE)16	// �Ƹӷ�
#define ITEMKIND_SUPPORT				(BYTE)17	// ��Ÿ��������, ���� ��
#define ITEMKIND_ENERGY					(BYTE)18	// ��������, countable
#define ITEMKIND_INGOT					(BYTE)19	// 2008-11-24 by dhjin, ��Ű ������ // ���� & ����, countable
#define ITEMKIND_CARD					(BYTE)20	// �Ϲ� ī��(���� �������� ����, 20040716, kelovon, ����ϰ� �Ǹ� �츲)
#define ITEMKIND_ENCHANT				(BYTE)21	// ��æƮ ī��
#define ITEMKIND_TANK					(BYTE)22	// ��ũ(EP ��ũ ��)
#define ITEMKIND_BULLET					(BYTE)23	// ź�˷�(=ź��), countable
#define ITEMKIND_QUEST					(BYTE)24	// ����Ʈ�� ������, countable
#define ITEMKIND_RADAR					(BYTE)25	// ���̴�
#define ITEMKIND_COMPUTER				(BYTE)26	// ��ǻ�� ������
#define ITEMKIND_GAMBLE					(BYTE)27	// RareFix ������ ī��, ��æƮ�� ���� ��� ���
#define ITEMKIND_PREVENTION_DELETE_ITEM	(BYTE)28	// ��æƮ �ÿ� ������ ���� ���� ������ 
#define ITEMKIND_BLASTER				(BYTE)29	// 2005-08-01 by hblee : �������ͷ� ������ �߰�.
#define ITEMKIND_RAILGUN				(BYTE)30	// 2005-08-01 by hblee : ���ϰǷ� ������ �߰�.
#define ITEMKIND_ACCESSORY_UNLIMITED	(BYTE)31	// 2006-03-17 by cmkwon, ���ð��� <����>�� �׼����� ������
#define ITEMKIND_ACCESSORY_TIMELIMIT	(BYTE)32	// 2006-03-17 by cmkwon, ���ð��� �ð� ������ �ִ� �׼����� ������
#define ITEMKIND_INFLUENCE_BUFF			(BYTE)33	// 2009-01-05 by dhjin, �̼Ǹ����� - ���� ���� ������ �߰� - ������ ITEMKIND_BUFF ��� �ǹ̷� ����, // 2006-04-21 by cmkwon, ���� ����, ����� ���¹��� ������
#define ITEMKIND_INFLUENCE_GAMEEVENT	(BYTE)34	// 2006-04-21 by cmkwon, ���� �����̺�Ʈ
#define ITEMKIND_RANDOMBOX				(BYTE)35	// 2006-08-10 by cmkwon, ���� �ڽ� - �ǵ��� �ڽ�
#define ITEMKIND_MARK					(BYTE)36	// 2006-08-21 by cmkwon, ��ũ - ����Ʈ ������
#define ITEMKIND_SKILL_SUPPORT_ITEM		(BYTE)37	// 2006-09-29 by cmkwon, ������ų������
#define ITEMKIND_PET_ITEM				(BYTE)38	// 2010-06-15 by shcho&hslee ��ý��� - �� ������.
#define ITEMKIND_GENERAL_ITEM_END		(BYTE)39	// General Item�� ���� ǥ����, ����� ��� �� ��

// DestParameter & ParamValue�� + ReqItemKind��, ���� �������� Kind �ʵ忡�� ���� ����, ���� enchant, skill���� ���, 20041019, kelovon with sjmin
#define ITEMKIND_ALL_ITEM				(BYTE)40	// ��� ������, ReqItemKind Ȯ���� �ʿ� ����
#define ITEMKIND_ALL_WEAPON				(BYTE)43	// ��� ����
#define ITEMKIND_PRIMARY_WEAPON_ALL		(BYTE)44	// 1�� ����
#define ITEMKIND_PRIMARY_WEAPON_1		(BYTE)45	// 1-1�� ����
#define ITEMKIND_PRIMARY_WEAPON_2		(BYTE)46	// 1-2�� ����
#define ITEMKIND_SECONDARY_WEAPON_ALL	(BYTE)47	// 2�� ����
#define ITEMKIND_SECONDARY_WEAPON_1		(BYTE)48	// 2-1�� ���� ����
#define ITEMKIND_SECONDARY_WEAPON_2		(BYTE)49	// 2-2�� ��� ����
// ��ų�� ������
#define IS_SKILL_ITEM(x)				((x) >= ITEMKIND_SKILL_ATTACK && (x) <= ITEMKIND_SKILL_ATTRIBUTE)
#define ITEMKIND_SKILL_ATTACK			(BYTE)50	// ���� ��ų
#define ITEMKIND_SKILL_DEFENSE			(BYTE)51	// ��� ��ų
#define ITEMKIND_SKILL_SUPPORT			(BYTE)52	// ��Ʈ�� ��ų + ���� ��ų
#define ITEMKIND_SKILL_ATTRIBUTE		(BYTE)53	// �Ӽ� ��ų

#define ITEMKIND_COLOR_ITEM				(BYTE)60	// �Ƹ� �������� ���� ������, // 2005-12-06 by cmkwon

// ���Ϳ� ������
#define IS_MONSTER_ITEM(x)				((x) >= ITEMKIND_FOR_MON_PRIMARY && (x) <= ITEMKIND_FOR_MON_MAIN_ARMAMENT) // 2011-05-13 by hskim, ���Ǵ�Ƽ 3��
#define IS_PRIMARY_WEAPON_MONSTER(x)	((x) >= ITEMKIND_FOR_MON_PRIMARY && (x) <= ITEMKIND_FOR_MON_RANGE_ATTACK)		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ��ų ������ Kind �߰�
#define IS_SECONDARY_WEAPON_MONSTER(x)	((x) >= ITEMKIND_FOR_MON_SECONDARY && (x) <= ITEMKIND_FOR_MON_MAIN_ARMAMENT) // 2011-05-13 by hskim, ���Ǵ�Ƽ 3��
#define ITEMKIND_FOR_MON_PRIMARY		(BYTE)100	// 1�� ���Ϳ� ������
#define ITEMKIND_FOR_MON_GUN			(BYTE)101	// ���� �������(1-1��)
#define ITEMKIND_FOR_MON_BEAM			(BYTE)102	// ���� ����(1-2��)
#define ITEMKIND_FOR_MON_ALLATTACK		(BYTE)103	// ���� ��ü ����
#define ITEMKIND_FOR_MON_SKILL			(BYTE)104	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ��ų ������ Kind �߰�
#define ITEMKIND_FOR_MON_RANGE_ATTACK	(BYTE)105	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���� ���� 
#define ITEMKIND_FOR_MON_SECONDARY		(BYTE)150	// 2�� ���Ϳ� ������
#define ITEMKIND_FOR_MON_ROCKET			(BYTE)151	// ���� ����(2-1��)
#define ITEMKIND_FOR_MON_MISSILE		(BYTE)152	// ���� �̻��Ϸ�(2-1��)
#define ITEMKIND_FOR_MON_BUNDLE			(BYTE)153	// ���� �����(2-1��)
#define ITEMKIND_FOR_MON_MINE			(BYTE)154	// ���� ���η�(2-1��)
#define ITEMKIND_FOR_MON_SHIELD			(BYTE)155	// ���� �����(2-2��)
#define ITEMKIND_FOR_MON_DUMMY			(BYTE)156	// ���� ���̷�(2-2��)
#define ITEMKIND_FOR_MON_FIXER			(BYTE)157	// ���� �ȼ���(2-2��)
#define ITEMKIND_FOR_MON_DECOY			(BYTE)158	// ���� �����̷�(2-2��)
#define ITEMKIND_FOR_MON_FIRE			(BYTE)159	// ���� ���̾��
#define ITEMKIND_FOR_MON_OBJBEAM		(BYTE)160	// ���� �浹���� ���� e ���� ���� �浹�� ��� ������ �߻�
#define ITEMKIND_FOR_MON_STRAIGHTBOOM	(BYTE)161	// ���� ���� ��ź�� e ������ ���⼺�� ������ ���Ⱑ �߻�Ǹ� �� ������Ʈ�� ���� ��� ������ �߻� (�������� ���� ����, ����ٶ�)
#define ITEMKIND_FOR_MON_MAIN_ARMAMENT	(BYTE)162	// ���� ���� ���ݷ� (���Ǵ�Ƽ 3�� ����) - // 2011-03-28 by hskim, ���Ǵ�Ƽ 3�� - ���� ��Ƽ Ÿ���� ��� �߰� - ���� ������ ������ ��� ���� �Ÿ��� ����� �߻�Ǵ� ����Ʈ�� �� �� ����

/////////////////////////////////////////////////
// start 2011-09-20 by hskim, ��Ʈ�� �ý��� 2��
/////////////////////////////////////////////////
// �Ϲ� �����۷� (IS_GENERAL_ITEM) 2��
// 249 ���� �����ؼ� ���� ��ȣ�� �Ҵ��ϼ���. ��) 249 -> 248 -> 247 -> 246 -> 245 -> ���
// ITEMKIND �� ������ �� ���׿� �ִ��� �Ʋ����� �Ф�
#define ITEMKIND_GENERAL_ITEM_2ND_END	ITEMKIND_PET_SOCKET_ITEM		// General Item 2���� ���� ǥ����

#define ITEMKIND_PET_SOCKET_ITEM		(BYTE)249	// ���� ���� ���Ϸ� ������, // 2011-09-01 by hskim, ��Ʈ�� �ý��� 2�� - ���� ����ɽÿ��� SQL ���� ���ν��� arena_CopyDBInfo �� arena_CopyDBInfo_Infinity ���� �����ϼ��� (������ 249 ��ȣ ���� ����)

#define ITEMKIND_GENERAL_ITEM_2ND_START	ITEMKIND_PET_SOCKET_ITEM		// General Item 2���� ������ ǥ����
// end 2011-09-20 by hskim, ��Ʈ�� �ý��� 2��
///////////////////////////////////////////////

#define ITEMKIND_UNKNOWN				(BYTE)255	// 2006-07-28 by cmkwon, 
#define ITEMKIND_ALL_ITEM_END			ITEMKIND_UNKNOWN	// Itemkind �� ���� ǥ���� - // 2012-12-14 by hskim, �޸��� �ڵ� ���� ��� ����
#define IS_VALID_ITEMKIND(x)			((x) >= ITEMKIND_AUTOMATIC && (x) <= ITEMKIND_ALL_ITEM_END)		// Itemkind �� Ȯ�� - // 2012-12-14 by hskim, �޸��� �ڵ� ���� ��� ����
 
// ���� ��ũ��
	// IS_COUNTABLE_ITEM		==> ������ ����ϴ� �����۷��ΰ�? ��������, INGOT, ź�˷� ��
	// IS_BUNCH_COUNTABLE_ITEM	==> ���� ������ ����ϴ� �����۷��ΰ�? ī���, ��æƮ��, ������
#define COUNT_BUNCH_COUNTABLE_ITEM_UNIT			10	// ���� ���� �����۷� ���� ����

// 2008-11-26 by cmkwon, �븸 Netpower_Tpe ������ ������ �߰� ���ν��� �߰� - 
//							- IS_COUNTABLE_ITEM ������ �ݵ�� dbo.atum_IsCountableItem �� ���� ���� �ؾ� �Ѵ�.
#define IS_COUNTABLE_ITEM(_ITEM_KIND)			((_ITEM_KIND) == ITEMKIND_ENERGY || (_ITEM_KIND) == ITEMKIND_INGOT || (_ITEM_KIND) == ITEMKIND_CARD || (_ITEM_KIND) == ITEMKIND_ENCHANT || (_ITEM_KIND) == ITEMKIND_BULLET || (_ITEM_KIND) == ITEMKIND_QUEST || (_ITEM_KIND) == ITEMKIND_GAMBLE || (_ITEM_KIND) == ITEMKIND_PREVENTION_DELETE_ITEM || (_ITEM_KIND) == ITEMKIND_INFLUENCE_BUFF || (_ITEM_KIND) == ITEMKIND_INFLUENCE_GAMEEVENT)
#define IS_SPECIAL_COUNTABLE_ITEM(_ITEM_KIND)	((_ITEM_KIND) == ITEMKIND_CARD || (_ITEM_KIND) == ITEMKIND_ENCHANT || (_ITEM_KIND) == ITEMKIND_GAMBLE || (_ITEM_KIND) == ITEMKIND_PREVENTION_DELETE_ITEM)

// 2010-04-20 by cmkwon, �ű� ��Ű �ӽ� ���� - �Ƹ�(ITEMKIND_DEFENSE) �߰�
#define COMPARE_ITEMKIND(_REQ_ITEM_KIND, _TARGET_KIND_VAR)											\
	((_REQ_ITEM_KIND == ITEMKIND_ALL_ITEM) || (_REQ_ITEM_KIND == _TARGET_KIND_VAR)				\
	|| ((_REQ_ITEM_KIND == ITEMKIND_ALL_WEAPON) && IS_WEAPON(_TARGET_KIND_VAR))						\
	|| ((_REQ_ITEM_KIND == ITEMKIND_PRIMARY_WEAPON_ALL) && IS_PRIMARY_WEAPON(_TARGET_KIND_VAR))		\
	|| ((_REQ_ITEM_KIND == ITEMKIND_PRIMARY_WEAPON_1) && IS_PRIMARY_WEAPON_1(_TARGET_KIND_VAR))		\
	|| ((_REQ_ITEM_KIND == ITEMKIND_PRIMARY_WEAPON_2) && IS_PRIMARY_WEAPON_2(_TARGET_KIND_VAR))		\
	|| ((_REQ_ITEM_KIND == ITEMKIND_SECONDARY_WEAPON_ALL) && IS_SECONDARY_WEAPON(_TARGET_KIND_VAR))	\
	|| ((_REQ_ITEM_KIND == ITEMKIND_SECONDARY_WEAPON_1) && IS_SECONDARY_WEAPON_1(_TARGET_KIND_VAR))	\
	|| ((_REQ_ITEM_KIND == ITEMKIND_DEFENSE) && (ITEMKIND_DEFENSE == _TARGET_KIND_VAR))	\
	|| ((_REQ_ITEM_KIND == ITEMKIND_SECONDARY_WEAPON_2) && IS_SECONDARY_WEAPON_2(_TARGET_KIND_VAR)))

// 2008-11-26 by cmkwon, �븸 Netpower_Tpe ������ ������ �߰� ���ν��� �߰� - 
//							- IS_CHARGABLE_ITEM ������ �ݵ�� dbo.atum_IsChargableItem �� ���� ���� �ؾ� �Ѵ�.
//							- ī���ͺ� �������� Chargable Item �� �ɼ� ����. Chargable Item�� �ݵ�� ��ī���ͺ� �����۸� �����ϴ�.
#define IS_CHARGABLE_ITEM(_ITEM_KIND)	(IS_WEAPON(_ITEM_KIND)||(_ITEM_KIND)==ITEMKIND_TANK || (_ITEM_KIND)==ITEMKIND_ACCESSORY_UNLIMITED || (_ITEM_KIND)==ITEMKIND_ACCESSORY_TIMELIMIT)	// ITEM::Charging�� ITEM_GENERAL::CurrentCount�� �Ҵ��ؼ� ���� ������

// 2007-08-29 by cmkwon, ���ս� �Ƹӵ� ����� ���� ����/��æƮ ���� �����ϱ� - 
#define IS_ITEMKIND_REMAIN_RARE8ENCHANT_AS_MIX(_ITEM_KIND)	(IS_WEAPON(_ITEM_KIND) || ITEMKIND_DEFENSE==(_ITEM_KIND))

// 2009-02-17 by cmkwon, ��æƮ �� �� �ִ� ������ ī�ε� ���� - ����, �Ƹ�, ���̴�, ����
#define IS_ENCHANT_TARGET_ITEMKIND(_IT_)		(IS_WEAPON(_IT_) || ITEMKIND_DEFENSE == (_IT_) || ITEMKIND_RADAR == (_IT_) || ITEMKIND_SUPPORT == (_IT_) || ITEMKIND_ACCESSORY_UNLIMITED == (_IT_))	// 2009-09-09 ~ 2010-02-10 by dhjin, ���Ǵ�Ƽ - �ߵ�������������

// 2010-04-20 by cmkwon, �ű� ��Ű �ӽ� ���� - �Ƹ�(ITEMKIND_DEFENSE)�� �߰�
#define IS_RARE_TARGET_ITEMKIND(_IT_)			(IS_WEAPON(_IT_) || ITEMKIND_DEFENSE == (_IT_))	// 2009-09-09 ~ 2010-02-10 by dhjin, ���Ǵ�Ƽ - �ߵ�������������

// 2009-08-26 by cmkwon, �׷��� ���ҽ� ���� �ý��� ���� - 
//						- ���� ���� ���� Kind �� 5��, 1��/2�� ����, ��ũ, �Ƹ�, ���̴�, ��Ʈ��
//						- �������� ����Ʈ ���� ���� Kind �� 2��, 1��/2�� ����
#define IS_ENABLE_CHANGE_ShapeItemNum(_ITEM_KIND)		(IS_WEAPON(_ITEM_KIND) || ITEMKIND_MARK == (_ITEM_KIND) || ITEMKIND_DEFENSE == (_ITEM_KIND) || ITEMKIND_RADAR == (_ITEM_KIND) || ITEMKIND_PET_ITEM == (_ITEM_KIND))		// 2012-12-03 by hskim, ��Ʈ�� �Ⱓ�� ���� ����
#define IS_ENABLE_CHANGE_EffectItemNum(_ITEM_KIND)		(IS_WEAPON(_ITEM_KIND))


///////////////////////////////////////////////////////////////////////////////
// ����ȭ ������ kind - ITEM ����ü���� SummonMonster �ʵ带 ����Ѵ�
// 2009-01-28 by cmkwon, ĳ���� ����(��õ��,�Ż�ǰ �߰�) - �Ʒ��� �÷� �Ǹ� �����ϰ� �ٸ� ���� �ǹ̸� ���� �ʴ´�. ���� ���� �������� �ǹ��ϰ� ������.
// #define CASH_ITEMKIND_PREMIUM_CARD			(BYTE)0
// #define CASH_ITEMKIND_OPTION_ITEM			(BYTE)1
// #define CASH_ITEMKIND_CARD_ITEM				(BYTE)2
// #define CASH_ITEMKIND_ACCESSORY_ITEM		(BYTE)3
// #define CASH_ITEMKIND_COLOR_ITEM			(BYTE)4			// 2007-08-09 by cmkwon, ��������� �Ƹ� �÷� ���� �� �߰�
// #define CASH_ITEMKIND_PACKAGE_ITEM			(BYTE)5			// 2008-10-20 by cmkwon, ��������� ĳ�� ���� �� �߰�

#define CASH_ITEMKIND_RECOMMEND_ITEM				((BYTE)0x00)	// 2009-01-28 by cmkwon, ĳ���� ����(��õ��,�Ż�ǰ �߰�) - ù��° ���� ��õ��
#define CASH_ITEMKIND_COLOR_ITEM					((BYTE)0x09)	// 2009-01-28 by cmkwon, ĳ���� ����(��õ��,�Ż�ǰ �߰�) - �÷����� ���� �ؾ� �ϹǷ� �ϴ� ���� �ڷ� ������.

#define CASHSHOP_BIT_TAPINDEX_MASK					((BYTE)0x0F)	// 2009-01-28 by cmkwon, ĳ���� ����(��õ��,�Ż�ǰ �߰�) - 
#define CASHSHOP_BIT_RECOMMEND						((BYTE)0x10)	// 2009-01-28 by cmkwon, ĳ���� ����(��õ��,�Ż�ǰ �߰�) - 
#define CASHSHOP_BIT_NEW							((BYTE)0x20)	// 2009-01-28 by cmkwon, ĳ���� ����(��õ��,�Ż�ǰ �߰�) - 
#define GET_TABINDEX_BY_CASHSHOPINDEX(idx)				((idx)&CASHSHOP_BIT_TAPINDEX_MASK)				// 2009-01-28 by cmkwon, ĳ���� ����(��õ��,�Ż�ǰ �߰�) - 0~15������ ���ε�����
#define GET_CASHSHOP_BIT_BY_CASHSHOPINDEX(idx)			((idx)&((BYTE)(~CASHSHOP_BIT_TAPINDEX_MASK)))	// 2009-01-28 by cmkwon, ĳ���� ����(��õ��,�Ż�ǰ �߰�) - 16~255������ ĳ�������� ��Ʈ�÷���
#define IS_NEW_CASHSHOPITEM_BY_CASHSHOPINDEX(idx)		(0 != ((idx)&CASHSHOP_BIT_NEW))				// 2009-01-28 by cmkwon, ĳ���� ����(��õ��,�Ż�ǰ �߰�) - �Ż�ǰ üũ
#define IS_RECOMMEND_CASHSHOPITEM_BY_CASHSHOPINDEX(idx)	(0 != ((idx)&CASHSHOP_BIT_RECOMMEND))		// 2009-01-28 by cmkwon, ĳ���� ����(��õ��,�Ż�ǰ �߰�) - ��õ��ǰ üũ


///////////////////////////////////////////////////////////////////////////////
// ITEM�� OrbitType �ʵ忡 ��� define ������ �̻���, ���� ���� ������ ��Ÿ����
#define ORBIT_SINGLE_CROSS_FIRE			1            // �ѹ߷� ���� ������Ÿ�ӵ��� �յ��ϰ� ������ �߻��Ѵ�.
#define ORBIT_SINGLE_FIRE_100			32        // �ѹ� �߻�_100,150,200,250,300,320,350, �ѹ߸� �߻�Ǹ� ���� �ð� �� ���� ���� �߻�ȴ�.
#define ORBIT_SINGLE_FIRE_150			33
#define ORBIT_SINGLE_FIRE_200			2	// �ѹ� �߻�_200,250,300,320,350, �ѹ߸� �߻�Ǹ� ���� �ð� �� ���� ���� �߻�ȴ�.
#define ORBIT_SINGLE_FIRE_250			3
#define ORBIT_SINGLE_FIRE_300			4
#define ORBIT_SINGLE_FIRE_320			5
#define ORBIT_SINGLE_FIRE_350			6
#define ORBIT_TWIN_CROSS_FIRE			7	// �ֹ߷� ���� ������Ÿ�ӵ��� �յ��ϰ� ������ �߻��Ѵ�.
#define ORBIT_TWIN_FIRE_100				34        // �ֹ� �߻�_100,150,200,250,300,320,350, �ֹ߷� �߻�Ǹ� ���� �ð� �� ���� ���� �߻�ȴ�.
#define ORBIT_TWIN_FIRE_150				35
#define ORBIT_TWIN_FIRE_200				8	// �ֹ� �߻�_200,250,300,320,350, �ֹ߷� �߻�Ǹ� ���� �ð� �� ���� ���� �߻�ȴ�.
#define ORBIT_TWIN_FIRE_250				9
#define ORBIT_TWIN_FIRE_300				10
#define ORBIT_TWIN_FIRE_320				11
#define ORBIT_TWIN_FIRE_350				12
#define ORBIT_CROSS_FIRE				13	// ������ �߻�, �ֹ߷� ���� ������Ÿ�ӵ��� �յ��ϰ� ������ �߻��Ѵ�.
#define ORBIT_STRAIGHT_ROCKET_250		14	// ���� ���� �߻�_250, �������� �߻�ȴ�.
#define ORBIT_FALL_ROCKET_250			15	// �ϰ� ���� �߻�_250, �ϰ� �� �������� ������ �߻�ȴ�.
#define ORBIT_LEFT_ROCKET_200			16	// ���� ���� ���� �߻�_200, ���ʺ��� ���� ������ �߻�ȴ�.
#define ORBIT_RIGHT_ROCKET_200			17	// ������ ���� ���� �߻�_200, �����ʺ��� ���� ������ �߻�ȴ�.
#define ORBIT_THREE_ROCKET				18	// 3�� ���� ���� �߻�, ������ ������ Ÿ���� 3�ܰ�� �Ͽ� ���� Ÿ�ӿ��� ���� �и��Ǹ鼭 Ÿ�������� ������ ������ �߻�ȴ�.
#define ORBIT_CHILD_ROCKET				19	// ����ź ���� �߻�, Ÿ���� ��ó�� ���� �̵��� �� �ֺ����� ����ź�� �и��Ǿ� �߻�ȴ�.
#define ORBIT_STRAIGHT_MISSILE_300		20	// ���� ���� �̻��� �߻�_300, �������� ����Ͽ� �����ȴ�.
#define ORBIT_FALL_MISSILE_300			21	// �ϰ� ���� �̻��� �߻�_300, �ϰ� �� �������� ���� �̻����� �߻�ȴ�.
#define ORBIT_LEFT_MISSILE_300			22	// ���� ���� �̻��� �߻�_300, ���ʺ��� �������� ���� �̻����� �߻�ȴ�.
#define ORBIT_RIGHT_MISSILE_270			23	// �ٱ��� ���� �̻��� �߻�_270, �ٱ��ʺ��� �������� ���� �̻����� �߻�ȴ�.
#define ORBIT_UPDOWN_ROCKET_270			24	// ��� ��� ���� �߻�_270, ���� ��� �� Ÿ�ٱ��� ����·� �������� ������ �߻�ȴ�.
#define ORBIT_UPDOWN_MISSILE_300		25	// ��� ������ �̻��� �߻�_300, ���� ��� �� Ÿ�ٱ��� ������ �̻����� �߻�ȴ�.
#define ORBIT_FLAME_THROWER				26	// �л��� ���� �߻�, ȭ���̳� �ñ�� �л簡 ������ ���Ⱑ �߻�ȴ�.
#define ORBIT_BODYSLAM					27	// ���� ���� �߻�, ���� Ÿ���Ͽ� �����Ѵ�.
#define ORBIT_MINE_300					28	// ���� �߻�_300,400, Ư���� ��Ʈ�� ������ �߻��Ѵ�.
#define ORBIT_MINE_400					29
#define ORBIT_RANGE_ROCKET_300			30	// ���� ����_300,400, ���� �ֺ����� ������ �߻��Ѵ�.
#define ORBIT_RANGE_ROCKET_400			31
#define ORBIT_FIRE						100	// ���� ���̾��
#define ORBIT_OBJBEAM					101	// ���� �浹���� ���� e ���� ���� �浹�� ��� ������ �߻�
#define ORBIT_STRAIGHTBOOM				102	// ���� ���� ��ź�� e ������ ���⼺�� ������ ���Ⱑ �߻�Ǹ� �� ������Ʈ�� ���� ��� ������ �߻� (�������� ���� ����, ����ٶ�)
#define ORBIT_CATCH						103	// ���� �����ݷ�
#define ORBIT_STICK						104	// ���� �������ݷ�
#define ORBIT_ATTACK_ALL				105	// ���� ��ü���ݷ�
#define ORBIT_SKILL_DEBUFF_TIMELIMIT	200	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - �ð��� DEBUFF
#define ORBIT_SKILL_DOT_TIMELIMIT		210	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - �ð��� DOT
#define IS_ORBIT_SKILL(x)				((x) >= ORBIT_SKILL_DEBUFF_TIMELIMIT && (x) <= ORBIT_SKILL_DOT_TIMELIMIT)		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - 

///////////////////////////////////
// �ǹ�(����) ����, BUILDINGKIND_XXX
#define BUILDINGKIND_1ST_WEAPONSHOP		(BYTE)0		// �⺻������Ʈ
#define BUILDINGKIND_2ND_WEAPONSHOP		(BYTE)1		// ���޹�����Ʈ
#define BUILDINGKIND_COMPONENTSHOP		(BYTE)2		// �Ҹ�ǰ��Ʈ
#define BUILDINGKIND_PETSHOP			(BYTE)3		// ����Ʈ
#define BUILDINGKIND_ANTIQUESHOP		(BYTE)4		// ��ǰ��Ʈ
#define BUILDINGKIND_CITYWARP			(BYTE)5		// ��������(�� ���ÿ���, �� BUILDINGKIND_HANGAR)
#define BUILDINGKIND_PUBLICOFFICE		(BYTE)6		// ������Ʈ
#define BUILDINGKIND_ACTIONHOUSE		(BYTE)7		// �����Ʈ
#define BUILDINGKIND_RACETRACK			(BYTE)8		// ���̽���Ʈ
#define BUILDINGKIND_REFINERY			(BYTE)9		// ������Ʈ - ���� ����
#define BUILDINGKIND_LABORATORY			(BYTE)10	// ������Ʈ
#define BUILDINGKIND_FACTORY			(BYTE)11	// ������Ʈ, �� BUILDINGKIND_ROBOTHANGAR
#define BUILDINGKIND_MILITARYACADEMY	(BYTE)12	// ����б���Ʈ
#define BUILDINGKIND_STORE				(BYTE)13	// â��
#define BUILDINGKIND_SKILL_SHOP			(BYTE)14	// ��ų ����
#define BUILDINGKIND_AUCTION			(BYTE)15	// ���, ��ǰ ���� ����
#define BUILDINGKIND_CITY_OCCUPY_INFO	(BYTE)16	// ���� ���� ���� ����
#define BUILDINGKIND_TUNING_COLOR		(BYTE)17	// 2005-11-11 by cmkwon, Ʃ�� ���� ����
#define BUILDINGKIND_ARENA				(BYTE)18	// 2007-04-23 by dhjin, ARENA
#define BUILDINGKIND_WARPOINT_SHOP		(BYTE)19	// 2007-05-17 by dhjin, WARPOINT SHOP
#define BUILDINGKIND_BRIEFING_ROOM		(BYTE)20	// 2007-07-16 by dhjin, BRIEFING_ROOM
#define BUILDINGKIND_TUTORIAL			(BYTE)21	// 2007-07-16 by dhjin, BUILDINGKIND_TUTORIAL
#define BUILDINGKIND_CITYLEADER_LEADER  (BYTE)22	// 2007-08-27 by dhjin, BUILDINGKIND_CITYLEADER_LEADER
#define BUILDINGKIND_CITYLEADER_OUTPOST (BYTE)23	// 2007-08-27 by dhjin, BUILDINGKIND_CITYLEADER_OUTPOST
#define BUILDINGKIND_LUCKY				(BYTE)24	// 2010-04-20 by cmkwon, �ű� ��Ű �ӽ� ���� - �Ƹ�/����/���Ǹ� ���, �ɼǸӽ��� �Ʒ��� ���� �߰�// 2008-11-04 by dhjin, ��Ű�ӽ�, BUILDINGKIND_LUCKY
#define BUILDINGKIND_WORLDRANKING		(BYTE)25	// 2009-02-12 by cmkwon, EP3-3 ���巩ŷ�ý��� ���� - 
#define BUILDINGKIND_INFINITY			(BYTE)30	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - 
#define BUILDINGKIND_INFINITY_SHOP		(BYTE)31	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ����
#define BUILDINGKIND_LUCKY_OPTION_MACHINE	(BYTE)32	// 2010-04-20 by cmkwon, �ű� ��Ű �ӽ� ���� - �ɼǸӽ��� ���� �߰�
#define BUILDINGKIND_DISSOLUTION		(BYTE)33	// 2010-08-31 by shcho&jskim �����ۿ��� �ý��� -
#define BUILDINGKIND_TRIGGER_CRYSTAL	(BYTE)34	// 2011-10-28 by hskim, EP4 [Ʈ���� �ý���] - ũ����Ż �ý���
#define BUILDINGKIND_PARTSSHOP			(BYTE)35	// 2012-02-29 by mspark, ���� Ÿ��Ʋ �ֱ� - ��������
#define BUILDINGKIND_GEARSHOP			(BYTE)36	// 2012-02-29 by mspark, ���� Ÿ��Ʋ �ֱ� - ������
#define BUILDINGKIND_CARDSHOP			(BYTE)37	// 2012-02-29 by mspark, ���� Ÿ��Ʋ �ֱ� - ī�����
#define BUILDINGKIND_MYSTERY_SHOP		(BYTE)38	// 2012-07-04 by JHAHN, �̽��͸� �ӽ� ����
#define BUILDINGKIND_INFLBUFF_SHOP		(BYTE)39	// 2013-05-09 by hskim, ���� ����Ʈ ����
#define BUILDINGKIND_DESTROY_AUCTION	(BYTE)40	// 2014-01-03 by jhseol&bckim, �ı������ - �ǹ� ���� �߰�
#define BUILDINGKIND_CASH_SHOP			(BYTE)100	// ����ȭ ��ǰ ����




///////////////////////////////////
// �ǹ� �� ��� NPC ����
typedef struct _BUILDINGNPC {
	UINT		BuildingIndex;							// �ǹ�(���� ��) ���� ��ȣ
	char		BuildingName[SIZE_MAX_BUILDING_NAME];
	BYTE		BuildingKind;							// �ǹ� ����, BUILDINGKIND_XXX
	MapIndex_t	MapIndex;								// ���� �ִ� �� Index
	UINT		NPCIndex;								// ��� NPC
	char		NPCName[SIZE_MAX_NPC_NAME];
	char		GreetingTalk[SIZE_MAX_BUILDING_NPC_TALK_STRING];	// �λ縻
	MapIndex_t	OwnerCityMapIndex;						// �� ������ ������ ���ø��� ���ε���
	INT			OwnerOrderNumber;						// ���ø��� ���������� �������� ���� ����
} BUILDINGNPC;	// �ǹ� �� ��� NPC ����

//////////////////////////////////////////////////////////////////////
// 2010-06-15 by shcho&hslee ��ý��� - �� Ÿ�� ��
//2011-10-06 by jhahn ��Ʈ�� ������ �ý���
enum PARTNER_TYPE 
{	// ��Ʈ��(��) Ÿ�� ������.

	PARTNER_TYPE_START = 0,			// �Ϲ���.

	PARTNER_TYPE_NORMAL = 1,		// ������.
	PARTNER_TYPE_GROWTH,			// ������.
	

	MAX_PARTNER_TYPE

};
//end 2011-10-06 by jhahn ��Ʈ�� ������ �ý���

///////////////////////////////////
// 2010-06-15 by shcho&hslee ��ý��� - ���� ���� ���� Enum������ ����.
// 2011-09-20 by hskim, ��Ʈ�� �ý��� 2�� - ������ ������ (�κ��丮�� �������� ������, �κ��丮 ���� ��꿡�� ���Ե��� �ʴ´�) - ��Ʈ�� �ý��� ���� ���� ������ �� 
// ������ ���� ��ġ(POS_XXX)
enum EQUIP_POS
{
	POS_NONE = -1 ,

	POS_PROW = 0 , 
	POS_PROWIN ,
	POS_PROWOUT , 
	POS_WINGIN , 
	POS_WINGOUT , 

	POS_CENTER , 
	POS_REAR , 
	POS_ACCESSORY_UNLIMITED , 
	POS_ACCESSORY_TIME_LIMIT , 
	POS_PET , 

	MAX_EQUIP_POS , 

	POS_HIDDEN_ITEM = 98,			// 2011-09-20 by hskim, ��Ʈ�� �ý��� 2�� - ������ ������ (�κ��丮�� �������� ������, �κ��丮 ���� ��꿡�� ���Ե��� �ʴ´�) - ��Ʈ�� �ý��� ���� ���� ������ ��, ���� �ٸ� ���������ε� ����� ��� ��ũ��Ų �������� �����ɶ� ���� �����ǵ��� ó�� �Ұ�
	POS_INVALID_POSITION = 99

};

/*
// ������ ���� ��ġ(POS_XXX)
#define POS_PROW						((BYTE)0)	// ���̴�(���� ���)	--> ���� 2��
#define POS_PROWIN						((BYTE)1)	// CPU ��ǻ��(�߾� ����)	--> ���� 2��
#define POS_PROWOUT						((BYTE)2)	// 1�� ����(���� ����)	--> ���� 1��
#define POS_WINGIN						((BYTE)3)	// 2006-07-20 by cmkwon, ����Ʈ ������ (�߾� ����), ��ũ ������
#define POS_WINGOUT						((BYTE)4)	// 2�� ����(���� ����)	--> ���� 1��
#define POS_CENTER						((BYTE)5)	// �Ƹ�(�߾� ���)	--> ���� 4��
#define POS_REAR						((BYTE)6)	// ����(�Ĺ� ���)	--> ���� 3��

// 2010-06-15 by shcho&hslee ��ý��� - ���� ����.
//#define POS_ATTACHMENT					((BYTE)7)	// 2006-03-30 by cmkwon, ������ �Ǽ��縮 - ������(�Ĺ� ����-������ũ|�����̳ʰ迭), ������ ���� --> ���� 3��
#define POS_ACCESSORY_UNLIMITED			((BYTE)7)	// 2010-06-15 by shcho&hslee ��ý��� - ������ �Ǽ��縮 

//#define POS_PET							((BYTE)8)	// 2006-03-30 by cmkwon, �ð����� �Ǽ��縮(�Ĺ� ����)	--> ���� 4��
#define POS_ACCESSORY_TIME_LIMIT		((BYTE)8)	// 2010-06-15 by shcho&hslee ��ý��� - �ð����� �Ǽ��縮
// End 2010-06-15 by shcho&hslee ��ý��� - ���� ����.


// 2010-06-15 by shcho&hslee ��ý��� - ���� ����.
#define POS_PET							((BYTE)9)	// 2010-06-15 by shcho&hslee ��ý��� - �� ������.

#define POS_INVALID_POSITION			((BYTE)99)	// 99,  invalid position
*/
// End 2010-06-15 by shcho&hslee ��ý��� - ���� ���� ���� Enum������ ����.

// 2013-02-28 by bckim, �������� �����߰�
#define RETURN_USER_NOT_USING_ITEM		0		// ������ �̻����( ���������ƴ� )
#define RETURN_USER_USING_ITEM0			1		// ������   �����( ��������)
#define RETURN_USER_PARTY_BUFFSKILL_NUM		7841131	// ���������� �ƴ� ����� �� ������� ������ų �ѹ�
// End. 2013-02-28 by bckim, �������� �����߰�


#define POS_ITEMWINDOW_OFFSET			((BYTE)100)	// 100, �� ��ȣ���� ������â�� ����

// 2010-06-15 by shcho&hslee ��ý��� - ������ ���� ����. (��) �߰�. ���. 9 -> MAX_EQUIP_POS
#define SIZE_MAX_POS					MAX_EQUIP_POS
//#define SIZE_MAX_POS					10			// ���� ������ slot�� ����
//#define SIZE_MAX_POS					9			// ���� ������ slot�� ����

#define IS_ATTACHABLE_POSITION(pos)		(SIZE_MAX_POS > (pos))							// 2009-10-22 by cmkwon, �ð� �������� ������ �ý��� ���� - ���� ���� ������ üũ
#define IS_ATTACHABLE_ITEM(pItem)		(FALSE == IS_COUNTABLE_ITEM((pItem)->Kind) && IS_ATTACHABLE_POSITION((pItem)->Position))		// 2009-10-22 by cmkwon, �ð� �������� ������ �ý��� ���� - ���� ���� ������ üũ

///////////////////////////////////
// WEAR - WEAR_XXX
#define WEAR_NOT_ATTACHED				0	// ������
#define WEAR_ATTACHED					1	// ����

///////////////////////////////////////////////////////////////////////////////
// 2005-12-07 by cmkwon - ITEM_IN_XXX
#define ITEM_IN_CHARACTER				0	// ĳ�����κ�, ������ ĳ���� ���� ���۽� �ѹ��� ȣ���
#define ITEM_IN_STORE					1	// â��
#define ITEM_IN_GUILD_STORE             2   // 2006-09-14 by dhjin, ���� â�� 
#define ITEM_IN_MARKET					3   // 2013-11-25 by jhseol&bckim, �ŷ��� - �ŷ��߰��ҿ� ��ϵ� ������
#define ITEM_IN_DESTROY_AUCTION			4   // 2014-01-03 by jhseol&bckim, �ı������ - �ı�����忡 ��ϵ� ������

///////////////////////////////////
// �������� ĳ���� �Ķ����� - DES_XXX
#define DES_NULL							0		// ��� �Ķ���Ͱ� ���� ��� ���
#define DES_ATTACK_PART						1		// ���� ��Ʈ
#define DES_DEFENSE_PART					2		// ��� ��Ʈ
#define DES_FUEL_PART						3		// ���� ��Ʈ
#define DES_SOUL_PART						4		// ���� ��Ʈ
#define DES_SHIELD_PART						5		// ���� ��Ʈ
#define DES_DODGE_PART						6		// ȸ�� ��Ʈ
#define DES_ALL_PART						106		// ��� ����	// 2013-05-31 by jhseol,bckim �Ƹ� �÷��� - ��� ���� DES_ALL_PART �߰�
#define DES_BODYCONDITION					7		// ������
#define DES_ENDURANCE_01					8		// ������ 01
#define DES_ENDURANCE_02					9		// ������ 02
#define DES_CHARGING_01						10		// ��ź�� 01
#define DES_CHARGING_02						11		// ��ź�� 02
#define DES_PROPENSITY						12		// ����
#define DES_HP								13		// ��Ʈ����Ʈ, MAX HP�� +VALUE��ŭ �÷���
#define DES_DP								89		// ����(DEFENSE)����Ʈ
#define DES_SP								14		// �ҿ�����Ʈ
#define DES_EP								15		// ��������Ʈ
#define DES_SPRECOVERY						16		// �ҿ�����Ʈȸ����
#define DES_HPRECOVERY						17		// ����������Ʈȸ����
#define DES_MINATTACK_01					18		// (*) �ּ� ���ݷ� 01
#define DES_MAXATTACK_01					71		// (*) �ִ� ���ݷ� 01
#define DES_MINATTACK_02					19		// (*) �ּ� ���ݷ� 02
#define DES_MAXATTACK_02					72		// (*) �ִ� ���ݷ� 02
#define DES_ATTACKPROBABILITY_01			20		// ����Ȯ�� 01
#define DES_ATTACKPROBABILITY_02			21		// ����Ȯ�� 02
#define DES_DEFENSE_01						22		// (*) ���� 01 (������ ���� Ȯ��) 20040622 �߰�
#define DES_DEFENSE_02						23		// (*) ���� 02 (������ ���� Ȯ��) 20040622 �߰�
#define DES_DEFENSEPROBABILITY_01			24		// ���Ȯ�� 01 (ȸ�� Ȯ��)
#define DES_DEFENSEPROBABILITY_02			25		// ���Ȯ�� 02 (ȸ�� Ȯ��)
#define DES_SKILLPROBABILITY_01				26		// ��ų����Ȯ�� 01
#define DES_SKILLPROBABILITY_02				64		// ��ų����Ȯ�� 02
#define DES_FACTION_01						79		// �Ӽ� 01, check: �߰���
#define DES_FACTION_02						80		// �Ӽ� 02, check: �߰���
#define DES_FACTIONRESISTANCE_01			27		// �Ӽ����׷� 01
#define DES_FACTIONRESISTANCE_02			65		// �Ӽ����׷� 02
#define DES_SPEED							28		// (*) �̵��ӵ�, FIXER ���� �ӵ� ���ҷ�
#define DES_TRANSPORT						29		// ��ݷ�
#define DES_MATERIAL						30		// ����
#define DES_REATTACKTIME_01					31		// (*) ������Ÿ�� 01 (- ����)
#define DES_REATTACKTIME_02					32		// (*) ������Ÿ�� 02 (- ����)
#define DES_ABRASIONRATE_01					33		// ������ 01
#define DES_ABRASIONRATE_02					34		// ������ 02
#define DES_RANGE_01						35		// (*) ��ȿ�Ÿ� 01
#define DES_RANGE_02						36		// (*) ��ȿ�Ÿ� 02
#define DES_RANGEANGLE_01					37		// ��ȿ���� 01
#define DES_RANGEANGLE_02					38		// ��ȿ���� 02
#define DES_MULTITAGET_01					39		// ��ƼŸ�� 01
#define DES_MULTITAGET_02					66		// ��ƼŸ�� 02
#define DES_EXPLOSIONRANGE_01				40		// ���߹ݰ� 01
#define DES_EXPLOSIONRANGE_02				67		// ���߹ݰ� 02
#define DES_UNIT							41		// ������ ���� (28 ~ 29�� ���� ���� ���ָ����� ���������� ����)
#define DES_REVISION						42		// ������ ������ (28 ~ 29�� ���� ���� ���ָ����� ���������� ����)
#define DES_FACTIONPROBABILITY_01			43		// �Ӽ��� ���� ���Ȯ�� 01
#define DES_FACTIONPROBABILITY_02			68		// �Ӽ��� ���� ���Ȯ�� 02
#define DES_SHOTNUM_01						44		// ������ �� �߻� �� 01
#define DES_SHOTNUM_02						69		// ������ �� �߻� �� 02
#define DES_MULTINUM_01						45		// ���� �߻� �� 01
#define DES_MULTINUM_02						70		// ���� �߻� �� 02
#define DES_ATTACKTIME_01					46		// ó�� ���� ���� Ÿ�� 01 (- ����)
#define DES_ATTACKTIME_02					47		// ó�� ���� ���� Ÿ�� 02 (- ����)
#define DES_TIME_01							48		// (*) ���� �ð� 01, check: + -> *
#define DES_TIME_02							49		// (*) ���� �ð� 02, check: + -> *
#define DES_OVERHITTIME_01					73		// (*) ������ȸ���ð� 01, check: �߰���
#define DES_OVERHITTIME_02					74		// (*) ������ȸ���ð� 02, check: �߰���
#define DES_UNITKIND						50		// ��ü ���׷��̵�� �ش� ��ü
#define DES_ITEMKIND						51		// �������� ����(ITEMKIND_XXX)
#define DES_SUMMON							52		// ���� ��ȯ
#define DES_GRADUAL_HP_UP					53		// ��������, ���� HP�� ���� �ð�(ITEM.Time�� ����)���� ���������� VALUE��ŭ �÷���, �߰��� �ν��� �Ѱų� ���� ������ cancel
#define DES_GRADUAL_DP_UP					81		// ��������, ���� DP�� ���� �ð�(ITEM.Time�� ����)���� ���������� VALUE��ŭ �÷���, �߰��� �ν��� �Ѱų� ���� ������ cancel, check: �߰���
#define DES_GRADUAL_SP_UP					54		// ��������, ���� SP�� ���� �ð�(ITEM.Time�� ����)���� ���������� VALUE��ŭ �÷���, �߰��� ��(?)������ cancel
#define DES_GRADUAL_EP_UP					55		// ��������, ���� EP�� ���� �ð�(ITEM.Time�� ����)���� ���������� VALUE��ŭ �÷���, �߰��� ��(?)������ cancel
#define DES_IN_TIME_HP_UP					56		// ��������, ���� HP�� ���� �ð�(ITEM.Time�� ����)�� ���� �� VALUE��ŭ �÷���
#define DES_IN_TIME_DP_UP					82		// ��������, ���� DP�� ���� �ð�(ITEM.Time�� ����)�� ���� �� VALUE��ŭ �÷���, check: �߰���
#define DES_IN_TIME_SP_UP					57		// ��������, ���� SP�� ���� �ð�(ITEM.Time�� ����)�� ���� �� VALUE��ŭ �÷���
#define DES_IN_TIME_EP_UP					58		// ��������, ���� EP�� ���� �ð�(ITEM.Time�� ����)�� ���� �� VALUE��ŭ �÷���
#define DES_IMMEDIATE_HP_UP					59		// ��������, ���� HP�� ��� VALUE��ŭ �÷���
#define DES_IMMEDIATE_DP_UP					83		// ��������, ���� DP�� ��� VALUE��ŭ �÷���, check: �߰���
#define DES_IMMEDIATE_SP_UP					60		// ��������, ���� SP�� ��� VALUE��ŭ �÷���
#define DES_IMMEDIATE_EP_UP					61		// ��������, ���� EP�� ��� VALUE��ŭ �÷���
#define DES_GROUNDMODE						62		// ���ݸ��
#define DES_SIEGEMODE						63		// ������
#define DES_WEIGHT_01						75		// (*) ���� 01, check: �߰���
#define DES_WEIGHT_02						76		// (*) ���� 02, check: �߰���
#define DES_BULLET_01						77		// (*) 1�� �Ѿ� 01, 2005-11-02 by cmkwon ���Ҹ��ʾ˷��� ������
#define DES_BULLET_02						78		// (*) 2�� �Ѿ� 02, 2005-11-02 by cmkwon ���Ҹ��ʾ˷��� ������
#define DES_PRIMARY_WEAPON					84		// 1�� ����, �����
#define DES_SECONDARY_WEAPON				85		// 2�� ����, ����
#define DES_ALL_WEAPON						86		// 1,2�� ���� ���, ����
#define DES_CRITICALHITRATE_01				87		// (*)ũ��Ƽ�� Ȯ�� 20040622 �߰�
#define DES_CRITICALHITRATE_02				88		// (*)ũ��Ƽ�� Ȯ�� 20040622 �߰�
#define DES_WARP							90		// ���ÿ��� �����ۿ�
#define DES_REACTION_RANGE					91		// ITEM�� ReactionRange ����
#define DES_RARE_FIX_NONE					92		// ���λ�, ���̻� ��� ����, ITEMKIND_GAMEBLE�� DestParam1�� ����
#define DES_RARE_FIX_PREFIX					93		// ���λ�, ITEMKIND_GAMEBLE�� DestParam1�� ����
#define DES_RARE_FIX_SUFFIX					94		// ���̻�, ITEMKIND_GAMEBLE�� DestParam1�� ����
#define DES_RARE_FIX_BOTH					95		// ���λ�, ���̻� ��� ����, ITEMKIND_GAMEBLE�� DestParam1�� ����
#define DES_REQ_MIN_LEVEL					96		// ���������� �䱸 MinLevel�� �����
#define DES_REQ_MAX_LEVEL					97		// ���������� �䱸 MaxLevel�� �����
#define DES_WARP_OUTPOST					98		// 2007-09-05 by dhjin, �������� ���ÿ��� �����ۿ�
#define DES_CHAT_BLOCK						99		// 2008-12-30 by cmkwon, ������ ä�� ���� ī�� ���� - 

#define DES_CASH_STAT_ALL_INITIALIZE		100		// ���� ��� ���� �ʱ�ȭ ������
//#define DES_CASH_STAT_HALF_INITIALIZE		101		// (���� ��Ȯ��)���� 50% ���� �ʱ�ȭ ������
#define DES_CASH_STAT_PART_INITIALIZE		102		// ���� �κ� ���� �ʱ�ȭ ������
#define DES_RARE_FIX_PREFIX_INITIALIZE		103		// ���λ� �ʱ�ȭ, ITEMKIND_GAMEBLE�� DestParam1�� ����
#define DES_RARE_FIX_SUFFIX_INITIALIZE		104		// ���̻� �ʱ�ȭ, ITEMKIND_GAMEBLE�� DestParam1�� ����
#define DES_ENCHANT_INITIALIZE				105		// 2007-04-03 by cmkwon, ��æƮ �ʱ�ȭ, ITEMKIND_ENCHANT�� DestParam1�� ����
//											106		// ��� ����(DES_ALL_PART)���� ���	// 2013-05-31 by jhseol,bckim �Ƹ� �÷��� - ��� ���� DES_ALL_PART �߰�
#define DES_CASH_STEALTH					108		// ���ڽ� ������
#define DES_CASH_HP_AND_DP_UP				109		// HP and DP UP ������
#define DES_CASH_GUILD_ALL_MEMBERS_SUMMON	110		// ��� ���ܿ� ��ȯ - �����常 ��밡��
#define DES_CASH_GUILD_MEMBER_SUMMON		111		// ���ܿ� 1�� ��ȯ - �����常 ��밡��
#define DES_CASH_NORMAL_RESTORE				112		// �Ϲ� ��Ȱ ī�� - ��
#define DES_CASH_SUPER_RESTORE				113		// ���� ��Ȱ ī��
#define DES_CASH_GUILD						114		// �Ϲ�/���� ���� ī��
#define DES_CASH_MONSTER_SUMMON				115		// ���� ��ȯ ī��
#define DES_CASH_CHANGE_CHARACTERNAME		116		// ĳ���͸� ���� ī��
#define DES_CASH_SKILL_INITIALIZE			117		// ��ų �ʱ�ȭ ī��
#define DES_CASH_CHANGE_PILOTFACE			118		// �� ���� ī��
#define DES_CASH_CRACKER_CARD				119		// ���� ���� ī��

// 2014-06-10 by bckim, ���º��� ������
#define DES_CASH_CHANGE_INFLUENCE			120		// ���� ���� ī�� 
// End. 2014-06-10 by bckim, ���º��� ������


///////////////////////////////////////////////////////////////////////////////
// 2005-11-21 by cmkwon, ���� �߰��� DesParam
#define DES_SKILL_REDUCE_SHIELD_DAMAGE		121		// ���忡 ���� �������� �ٿ��ش�.
#define DES_SKILL_INVINCIBLE				122		// ���� ����
#define DES_SKILL_BIG_BOOM					123		// 		�̱��� - �ڽ��� HP�� ��� �Ҹ��Ͽ� �ֺ����� �������� ������, �ڽ��� �����Ѵ�.
#define DES_SKILL_HALLUCINATION				124		// ü�� ����.
#define DES_SKILL_RANGEDOWN_01				125		// 		�̱��� - ���� �⺻���� ��Ÿ��� ���δ�.
#define DES_SKILL_RANGEDOWN_02				126		// 		�̱��� - ���� ���� ���� ��Ÿ��� ���δ�.
#define DES_SKILL_PROHIBITION_01			127		// 		�̱��� - ���� �⺻ ���� ����� ������Ų��.
#define DES_SKILL_PROHIBITION_02			128		// 		�̱��� - ���� ���� ���� ����� ������Ų��.
#define DES_ATTACK_RANGE_01					129		// ���̴��� �⺻ ���� ���� �Ÿ��� ������Ų��.(*)
#define DES_ATTACK_RANGE_02					130		// ���̴��� ���� ���� ���� �Ÿ��� ������Ų��.(*)
#define DES_INVISIBLE						131		//	���ڽ� ���μ� ������ ������ ������, ���̴ٿ��� ������ �ʴ´�. �ڽŵ� ������ ���� �ʴ´�.
// 2005-12-02 by cmkwon, 154, 155, 156���� ����#define DES_SKILL_HYPERMOVING				132		// ������ ��ü �̵��ӵ��� ��������, �ν��� ����� ���� �ʴ´�.(*)
#define DES_SKILL_DEFENSE_01				133		// 		�̱��� - ���� �⺻������ ����߸���.(*)
#define DES_SKILL_DEFENSE_02				134		// 		�̱��� - ���� ���޹����� ����߸���.(*)
#define DES_SKILL_FREEZINGBODY				135		// 		�̱��� - ���� HP,���� ȸ���� �Ұ����ϰ� �����. ����Ŷ,����Ŷ,��ųȸ��(��ü)�� �ȵȴ�.
#define DES_SKILL_REVERSECONTROL			136		// 2010-03-31 by dhjin, ���Ǵ�Ƽ(�������) -	// 		�̱��� - ���� �������� �ݴ�� �����̰� �Ѵ�.
#define DES_SKILL_GRADUAL_HPSHIELD_DOWN		137		// 		�̱��� - ���� HP,���带 ���� ���ҽ�Ų��.
#define DES_SKILL_SLOWMOVING				138		// ���� �������� ���ϰ� �Ѵ�.(�ִ��̵� �ӵ�, �ν��� �ӵ�, �̵� ����, �ν��� �̵� ����)(*)
#define DES_SKILL_BOOSTEROFF				139		// 		�̱��� - ���� �ν��� ����� ������Ų��.
#define DES_SKILL_COLLISIONDAMAGE_DOWN		140		// ��� ������Ʈ,�ٴ� �浹�� �������� ���ҽ�Ų��.
//#define DES_SKILL_CAMOUFLAGE				141		// 		�̱��� - �����Ͽ� ���� �þ߿� ������ �ʴ´�. Ÿ�ٿ��� ������.
#define DES_SKILL_RANDOMTELEPORT			142		// 		�̱��� - ���� �ʿ��� �����ϰ� �̵��Ѵ�.
#define DES_SKILL_ATTACK_ALL				143		// 		�̱��� - ��ü ���� ��ų
#define DES_SKILL_SCANNING					144		// Invisible ������ ������ �� �� �ֵ��� �Ѵ�
#define DES_SKILL_REVERSEENGINE				145		// ������ ������ �����ϰ� �Ѵ�.
#define DES_SKILL_LOCKDOWN					146		// 		�̱��� - ������ �Ͻ� ������Ų��.(����,�¿켱ȸ,�ν��� ����, ��, ���ݱ���� ����)
#define DES_SKILL_STEALSP					147		// 		�̱��� - ������ SP�� ������ �P�ƿ´�.
#define DES_SKILL_SMARTSP					148		// �ڽ��� ����ϴ� ��� ��ų�� ��뷮�� �ٿ��ش�.(*)
#define DES_SKILL_SUMMON_FORMATION_MEMBER	149		// ����� �� 1���� ��ȯ�Ѵ�.
#define DES_SKILL_CANCEL_MAGIC				150		// 		�̱��� - ���� ���� ��ų�� ��� ������Ų��.
#define DES_SKILL_RANDOM_CANCEL				151		// 		�̱��� - Ÿ���� ����� ��ų�� �ϳ� �����ϰ� �����Ѵ�.
#define DES_SKILL_STOPMAGIC					152		// ���� ��ų�� �����ð� ��������Ų��. - 2011-10-28 by hskim, EP4 [Ʈ���� �ý���] - ũ����Ż �ý���
#define DES_SKILL_CANCELALL					153		// 		�̱��� - ����� ���� ��ų�� ��� �����Ѵ�.
#define DES_SKILL_REACTIONSPEED				154		// (*)������ ����(�����ӵ�)
#define DES_SKILL_ENGINEANGLE				155		// (*)������ ����(��ȸ��)
#define DES_SKILL_ENGINEBOOSTERANGLE		156		// (*)������ ����(�ν��� ��ȸ��)

// 2006-03-30 by cmkwon
#define DES_DROP_EXP						157		// ����ġ, �����̾��� ��ø �Ұ�
#define DES_DROP_SPI						158		// SPI, �����̾��� ��ø �Ұ�
#define DES_DROP_ITEM						159		// ������ �����, �����̾��� ��ø �Ұ�
#define DES_HP_REPAIR_RATE_FLIGHTING		160		// ����� HP ȸ����
#define DES_DP_REPAIR_RATE					161		// DP ȸ����
#define DES_SP_REPAIR_RATE					162		// SP ȸ����

// 2006-07-26 by cmkwon
#define DES_BAZAAR_SELL						163		// 2006-07-26 by cmkwon, ���� �Ǹ� ����
#define DES_BAZAAR_BUY						164		// 2006-07-26 by cmkwon, ���� ���� ����

// 2006-08-14 by dhjin
#define DES_KILLMARK_EXP					165		// 2006-08-14 by dhjin, ų��ũ ����ġ

// 2006-10-11 by cmkwon
#define DES_HYPER_BOOSTER					166		// 2006-10-11 by cmkwon, �ν��� ������ �������� ����

// 2006-11-17 by dhjin, 2�� ��ų�� ���� �߰��� ����
#define DES_SKILL_CHAFF_HP					167		// 2006-11-17 by dhjin, ü���� HP
#define DES_SKILL_AIR_BOMBING				168		// 2006-11-17 by dhjin, ���� ����
#define DES_SKILL_NO_WARNING				169		// 2006-11-17 by dhjin, Ÿ�� ��ų ����, �ش���� �������� ���̴� ������ �︮�� �ʰ� �ȴ�
#define DES_SKILL_ROLLING_TIME				170		// 2006-11-17 by dhjin, 30�ʵ��� �Ѹ� ���� �ð��� ����.
#define DES_SKILL_FULL_RECOVERY				171		// 2006-11-17 by dhjin, ��ü�� HP, ����, ����, SP�� ����ȸ���Ѵ�.
#define DES_SKILL_CAMOUFLAGE				172		// 2006-11-17 by dhjin, A����� ���� ��ų
#define DES_SKILL_BARRIER					173		// 2006-11-17 by dhjin, A����� ���޹��⿡ ���� ���� ��ų
#define DES_SKILL_HYPERSHOT					174		// 2006-11-17 by dhjin, A����� �⺻���� ��¡��, ���÷��� �������� Range
#define DES_SKILL_SHIELD_PARALYZE			175		// 2006-11-17 by dhjin, A����� ���帶�� ��ų, ������� ���� ȸ������ 0���� �����.

#define DES_WARHEAD_SPEED					176		// 2007-06-11 by cmkwon, ź���� �ӵ�
#define DES_CHAT_ALL_INFLUENCE				177		// 2007-08-09 by cmkwon, ��� ���¿� ä�� �����ϱ� - desparam �߰�, ���������

// 2008-09-22 by dhjin, �ű� ��þƮ
#define DES_ENGINE_BOOSTER_TIME_UP			178		// 2008-09-22 by dhjin, �ν��� �ð� ����
#define DES_ENGINE_MAX_SPEED_UP				179		// 2008-09-22 by dhjin, ���� �Ϲݼӵ�(�ִ�) ����
#define DES_ENGINE_MIN_SPEED_UP				180		// 2008-09-22 by dhjin, ���� �Ϲݼӵ�(�ּ�) ����
#define DES_ENGINE_BOOSTER_SPEED_UP			181		// 2008-09-22 by dhjin, ���� �ν��ͼӵ� ����
#define DES_ENGINE_GROUND_SPEED_UP			182		// 2008-09-22 by dhjin, ���� ����ӵ� ����
#define DES_RADAR_OBJECT_DETECT_RANGE		183		// 2008-09-22 by dhjin, ���̴� ��ü ���� �ݰ�
#define DES_PIERCE_UP_01					184		// 2008-09-22 by dhjin, �⺻���� �Ǿ�� ���� ī��
#define DES_PIERCE_UP_02					185		// 2008-09-22 by dhjin, ���޹��� �Ǿ�� ���� ī��
#define DES_ENGINE_ANGLE_UP                 186		// 2008-09-30 by dhjin, ���� ȸ���� ���� ī��
#define DES_ENGINE_BOOSTERANGLE_UP          187		// 2008-09-30 by dhjin, ���� �ν��� ȸ���� ���� ī��

// 2009-01-05 by dhjin, �̼Ǹ����� - ���� ���� ������ �߰� 
#define DES_ITEM_BUFF_INFLUENCE				188
#define DES_ITEM_BUFF_PARTY					189

// 2009-01-19 by dhjin, ��þƮ Ȯ�� ����, 10��þ �Ĺ� ī�� - ��þƮ Ȯ�� ���� ī��
#define DES_ENCHANT_PREVENTION_DELETE_USE_ENCHANT	190		// ��� �ϱ� ���� �������� ������æƮ ī��Ʈ ����
#define DES_ENCHANT_PREVENTION_DELETE_SAVE_ENCHANT	191		// ��æƮ ���н� ����� ��æƮ ī��Ʈ ����
#define DES_ENCHANT_INCREASE_PROBABILITY			192		// ��æƮ ī�� Ȯ�� ������ ����

///////////////////////////////////////////////////////////////////////////////
// 2009-08-03 by cmkwon, EP3-4 ���� ���� ��ų ���� - DES_ �߰�
#define DES_SKILL_DAMAGE_DISTRIBUTION				193		// �������� ��������� �л�(�й�) ó�� �Ѵ�.

///////////////////////////////////////////////////////////////////////////////
// 2009-08-26 by cmkwon, �׷��� ���ҽ� ���� �ý��� ���� - 
#define DES_SHAPE_ITEM								194		// ���ս� �ҽ� �������� ShapeItemNum�� ���� �� Item, LinkItem�� ���		(Value => KIND_ITEM_FIX_MIXING_WEAPON / KIND_ITEM_FIX_MIXING_DEFENSE)		// 2012-02-20 by hskim, DB ����ȭ - ItemMixingInfo
#define DES_EFFECT_ITEM								195		// ���ս� �ҽ� �������� EffectItemNum�� ���� �� Item, �ش� ItemNum�� ���	(Value => KIND_ITEM_FIX_MIXING_WEAPON / KIND_ITEM_FIX_MIXING_DEFENSE)		// 2012-02-20 by hskim, DB ����ȭ - ItemMixingInfo

///////////////////////////////////////////////////////////////////////////////
// 2009-09-23 by cmkwon, �ʵ�â�� ĳ�� ������ ���� - 
#define DES_FIELD_STORE								196		// �ʵ�â��

///////////////////////////////////////////////////////////////////////////////
// 2009-10-01 by cmkwon, �׷��� ���ҽ� ���� ���� �ʱ�ȭ ��� ���� - 
#define DES_INIT_SHAPE_ITEM							197		// ���ս� �ҽ� �������� ShapeItemNum�� �ʱ�ȭ �� Item		(Value => KIND_ITEM_FIX_MIXING_WEAPON / KIND_ITEM_FIX_MIXING_DEFENSE)		// 2012-02-20 by hskim, DB ����ȭ - ItemMixingInfo
#define DES_INIT_EFFECT_ITEM						198		// ���ս� �ҽ� �������� EffectItemNum�� �ʱ�ȭ �� Item		(Value => KIND_ITEM_FIX_MIXING_WEAPON / KIND_ITEM_FIX_MIXING_DEFENSE)		// 2012-02-20 by hskim, DB ����ȭ - ItemMixingInfo

///////////////////////////////////////////////////////////////////////////////
// 2009-11-02 by cmkwon, ĳ��(�κ�/â�� Ȯ��) ������ �߰� ���� - DES_XXX �߰�
#define DES_INCREASE_INVENTORY_SPACE				199		// ĳ���� �κ��丮 ����
#define DES_INCREASE_STORE_SPACE					200		// ĳ���� â�� ����

////////////////////////////////////////////////////////////////////////////////
// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - 
#define DES_ITEM_RESISTANCE							201		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ������ ��� üũ 
#define DES_ITEM_ADDATTACK							202		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���밪 Ÿ��ġ ������ ��� üũ 
#define DES_ITEM_IGNOREDEFENCE						203		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���� ������ ��� üũ
#define DES_ITEM_IGNOREAVOID						204		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ȸ�Ƿ� ���� ������ ��� üũ
#define DES_ITEM_REDUCEDAMAGE						205		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ������ ���밪 ���� ������ ��� üũ
#define DES_ITEM_ADDATTACK_SEC						206		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���밪 Ÿ��ġ ������ ���޹����(�⹫�� �з�)
#define DES_ITEM_ONCE_RESISTANCE					207		// 2009-09-09 ~ 2010-01-19 by dhjin, ���Ǵ�Ƽ - �� ���� �����ϰ� �������� ���� ������ �߰�
#define DES_SKILL_MON_SILENCE_PRIMARY				210		// ���� ���Ϸ��� ��ų (1������ ����)
#define DES_SKILL_MON_SILENCE_SECOND				211		// ���� ���Ϸ��� ��ų (2������ ����)
#define DES_SKILL_MON_FREEZE_HP						212		// ���� ������ ��ų HP ȸ�� �Ұ�  
#define DES_SKILL_MON_FREEZE_DP						213		// ���� ������ ��ų DP ȸ�� �Ұ�
#define DES_SKILL_MON_FREEZE_SP						214		// ���� ������ ��ų SP ȸ�� �Ұ�
#define DES_SKILL_MON_HOLD							215		// ���� Ȧ�� ��ų
#define DES_SKILL_MON_STEALING						216		// ���� ��ƿ�� ��ų 
#define DES_SKILL_MON_DRAIN							217		// ���� �巹�� ��ų
#define DES_SKILL_RELEASE							218		// M��� ������ ��ų
#define DES_SKILL_MON_SILENCE_SKILL					219		// ���� ���Ϸ��� ��ų (��ų ����)

///////////////////////////////////////////////////////////////////////////////
// 2009-09-09 ~ 2010-02-10 by dhjin, ���Ǵ�Ƽ - �ߵ�������������
#define DES_PAIR_DRAIN_1_RATE						220		// �巹�� �ߵ� Ȯ��
#define DES_PAIR_DRAIN_2_HP_DP_UP_RATE				221		// �巹�� ȸ���� HP->DP ȸ�� (�������� %)
#define DES_ANTI_DRAIN_RATE							222		// �巹�� �ߵ� ���� Ȯ��
#define DES_PAIR_REFLECTION_1_RATE					223		// ������ �ݻ� Ȯ��
#define DES_PAIR_REFLECTION_2_DAMAGE_RATE			224		// �ݻ� �������� %
#define DES_ANTI_REFLECTION_RATE					225		// ������ �ݻ� ���� Ȯ��

///////////////////////////////////////////////////////////////////////////////
// 2010-03-31 by dhjin, ���Ǵ�Ƽ(�������) - 
#define DES_BLIND									226
#define DES_SUPERINTEND								227
#define DES_IMMEDIATE_HP_OR_DP_UP					228		// HP�� ���� ä��� �� ���Ŀ� DP�� ä���.
#define DES_HIT_INVOKE_SKILL						229		// ���߽� �ش� �����Ķ����� ��ų�� �����Ѵ�.
#define DES_TIME_BOMB								230

///////////////////////////////////////////////////////////////////////////////
// 2010-03-18 by cmkwon, ���ͺ��� ���� - 
#define DES_TRANSFORM_TO_MONSTER					231		// ParamValue�� MonsterUnitKind �Է�

///////////////////////////////////////////////////////////////////////////////
// 2010-03-23 by cmkwon, ���Ǵ�Ƽ ���� ĳ�� ������ ���� - 1ȸ�� �߰� ���� ����
#define DES_INFINITY_REENTRY_TICKET					232		// ����� ParamValue�� ������� ����

///////////////////////////////////////////////////////////////////////////////
// 2010-04-05 by cmkwon, ���ͺ��Ű��� ���� ī�� ���� - 
#define DES_TRANSFORM_TO_GEAR						233		// ����� ParamValue�� ������� ����.

///////////////////////////////////////////////////////////////////////////////
// 2010-05-18 by cmkwon, WarPoint ���� ������ ����(�Ϻ���û) - 
#define DES_PLUS_WARPOINT_RATE						234		// ParamValue: WarPoint ���� Rate

///////////////////////////////////////////////////////////////////////////////
// 2010-06-01 by shcho, PC�� ���� ȹ��(ĳ��) ������ - 
#define DES_PCROOM_USE_CARD							235		//PC�� �÷��׸� TRUE�� ��ȯ ��Ų��.

///////////////////////////////////////////////////////////////////////////////
// 2010-08-26 by shcho&jsKim, �� ������ ���� -
#define DES_MAX_SP_UP								236		// SP�� �ִ�ġ�� ������Ų��.

///////////////////////////////////////////////////////////////////////////////
// 2010-08-27 by shcho&&jskim, WARPOINT ���� ������ ����
#define DES_WAR_POINT_UP							237		// WARPOINT ����

///////////////////////////////////////////////////////////////////////////////
// 2010-11-30 by shcho, ��������� ���Ȯ�� ���� ������ ����
#define DES_RARE_ITEM_DROP_RATE						238		// ���� ������ ���Ȯ�� ����

///////////////////////////////////////////////////////////////////////////////
// 2010-12-21 by jskim, ���� �̵� �ӵ� ���� ������ ����
#define DES_RARE_ITEM_PARTNER_SPEED					239		// ���� �̵� ���ǵ� ����

///////////////////////////////////////////////////////////////////////////////
// 2010-12-21 by jskim, ��Ʈ�� ������ ���� ������ ����
#define DES_RARE_ITEM_PARTNER_DAMAGE				240		// ��Ʈ�� ������ ����

///////////////////////////////////////////////////////////////////////////////
// 2010-12-21 by jskim, HP, DP ŰƮ ���뷮 ���� ������ ����
#define DES_RARE_ITEM_HPDP							241		// HP DP ŰƮ ���뷮

// start 2011-05-02 by hskim, ���Ǵ�Ƽ 3�� - �ó׸� ���� ��� �߰� - Ư�� ��ǥ�� ��ȯ
#define DES_SUMMON_POSITION_X						242		// ��ȯ�� ��ġ ���� (��밪)
#define DES_SUMMON_POSITION_Y						243		// ��ȯ�� ��ġ ���� (��밪)
#define DES_SUMMON_POSITION_Z						244		// ��ȯ�� ��ġ ���� (��밪)
// end 2011-05-02 by hskim, ���Ǵ�Ƽ 3�� - �ó׸� ���� ��� �߰� - Ư�� ��ǥ�� ��ȯ

// start 2011-10-18 by hskim, EP4 [Ʈ���� �ý���] - ȭ���� / �� ��ǳ
#define DES_MAPBUFF_RANDOM_ADD_REATTACKTIME			245		// �ʹ��� �߰� �ð� ����
#define DES_MAPBUFF_RANDOM_ADD_TIME					246		// �ʹ��� �߰� �ð� ����
#define DES_ENCHANT_ONCE_APPLY						247		// 2011-10-19 by hskim, EP4 [Free to play] - 10ȸ ��þƮ ������ ��� ����
#define DES_GAMBLE_RARE_ITEM_FIX					248		// 2011-10-20 by hskim, EP4 [Free to play] - ����/���� ���� �ɼ�
// end 2011-10-18 by hskim, EP4 [Ʈ���� �ý���] - ȭ���� / �� ��ǳ

// 2014-06-17 by bckim, ���� �ұ��� ( �ʽ��� ������ ������ ��� ���� )
#define DES_BEGINNER_ITEM							249		// 2014-06-17 by bckim, ���� �ұ��� ( �ʽ��� ������ ������ ��� ���� )
// End. 2014-06-17 by bckim, ���� �ұ��� ( �ʽ��� ������ ������ ��� ���� )
// 2014-06-17 by bckim, ���� �ұ��� ( ������ ��ȸ WP ȹ�淮 ���� )
#define DES_PLUS_WARPOINT_RATE_SHOW_TOOLTIP			250		// �������� ������� ����. ������ �����Ķ� �߰� - ������ ��ȸ 
// End. 2014-06-17 by bckim, ���� �ұ��� ( ������ ��ȸ WP ȹ�淮 ���� )

// 2013-05-07 by jhseol,bckim ���� �г�Ƽ
#define DES_BUFF_PENALTY_RATIO						251		// �г�Ƽ ���� (1.0f = 100%)
#define DES_BUFF_PENALTY_APPLIED_UNIT_KIND			252		// �г�Ƽ ���� ��� (ReqUnitKind)
// end 2013-05-07 by jhseol,bckim ���� �г�Ƽ

// 2013-05-09 by hskim, ���� ����Ʈ ����
#define DES_SKILLTYPE_CONSECUTIVE_VICTORIES			253		// ���� ����Ʈ ���� - ������ ������ ����
#define DES_SKILLTYPE_TRUN_AROUND					254		// ���� ����Ʈ ���� - ������ ������ ����

#define DES_SKILL_BUFF_MON_ATTACK_POWER				300		// ���� ���ݽ� - ���ݷ� ���� : Value ���� %
#define DES_SKILL_BUFF_MON_ATTACK_PROBABILITY		301		// ���� ���ݽ� - ���ݷ� Ȯ�� : Value ���� %
#define DES_SKILL_BUFF_MON_ATTACK_PIERCE			302		// ���� ���ݽ� - �Ǿ ���� : Value ���� %
#define DES_SKILL_BUFF_MON_DEFENCE					303		// ���� ���� - ���� ���� : Value ���� %
#define DES_SKILL_BUFF_MON_DEFENCE_AVOID			304		// ���� ���� - ȸ�Ƿ� ���� : Value ���� %
#define DES_SKILL_BUFF_PVP_ATTACK_POWER				305		// PVP - ���ݷ� ���� : Value ���� %
#define DES_SKILL_BUFF_PVP_ATTACK_PROBABILITY		306		// PVP - ���߷� ���� : Value ���� %		// 2013-08-01 by jhseol, ������ ���� ������
#define DES_SKILL_BUFF_PVP_ATTACK_PIERCE			307		// PVP - �Ǿ ���� : Value ���� %		// 2013-08-01 by jhseol, ������ ���� ������
#define DES_SKILL_BUFF_PVP_DEFENCE					308		// PVP - ���� ���� : Value ���� %		// 2013-08-01 by jhseol, ������ ���� ������
#define DES_SKILL_BUFF_PVP_DEFENCE_PROBABILITY		309		// PVP - ȸ�Ƿ� ���� : Value ���� %		// 2013-08-01 by jhseol, ������ ���� ������
// end 2013-05-09 by hskim, ���� ����Ʈ ����

// 2013-05-31 by jhseol,bckim �Ƹ� �÷��� - COLLECTION INDEX DesParam ��� (390~399 : 10�� ����)
#define DES_COLLECTION_ARMOR_INDEX					390		// �Ƹ� �÷��ǿ��� ���� �ε���
// end 2013-05-31 by jhseol,bckim �Ƹ� �÷��� - COLLECTION INDEX DesParam ��� (390~399 : 10�� ����)
// 2014-07-17 by bckim, �����̾� �Ƹ� �÷���
#define DES_PREMIUM_COLLECTION_ARMOR_INDEX			391		// �����̾� �Ƹ� �÷��ǿ��� ���� �ε���
// End. 2014-07-17 by bckim, �����̾� �Ƹ� �÷���

// 2013-08-07 by bckim, �̼������н� ������
#define DES_QUEST_MISSION_FREE_PASS					410		// �����н� ������ ���п� �����Ķ�
#define DES_QUEST_MISSION_FREE_PASS_MIN_LV			411		// �����н� ������ ��� ����Ʈ �ּ� ����
#define DES_QUEST_MISSION_FREE_PASS_MAX_LV			412		// �����н� ������ ��� ����Ʈ �ִ� ���� 
// End. 2013-08-07 by bckim, �̼������н� ������

// 2013-08-30 by bckim, �ʵ��̵�����������
#define DES_MOVEMENT_RESTRICTION_GIVE				420		// �����ڰ� ����ϴ� ī�� ������ 
#define DES_MOVEMENT_RESTRICTION_TAKE				421		// �ɸ��Ϳ��� �ο��Ǵ� ��ų	
#define DES_MOVEMENT_RESTRICTION_TAKE_ITEMNUM		7044190	// �ɸ��Ϳ��� �ο��Ǵ� ��ų������ �ѹ� 
// End. 2013-08-30 by bckim, �ʵ��̵�����������

// 2013-02-28 by bckim, �������� �����߰�
#define DES_PLUS_WARPOINT_RATE_FOR_RETURN_USER 		499		// ParamValue: WarPoint ���� Rate ( ��ȸ�� ) // 1ȸ�� DES_PLUS_WARPOINT_RATE
#define DES_BUFF_TO_RETURN_USER						500		// 2013-02-28 by bckim, �������� �����߰�
// End 2013-02-28 by bckim, �������� �����߰�

// 2012-10-10 by hskim, �Ⱓ�� �Ӽ� ���� (�Ⱓ�� ����)
#define DES_FIXED_TERM_SHAPE_TIME					501		// �Ⱓ�� ���� ���� �ð� (��)
#define DES_FIXED_TERM_ITEM_TIME					502		// �Ⱓ�� ������ ���� �ð� (��)
// end 2012-10-10 by hskim, �Ⱓ�� �Ӽ� ���� (�Ⱓ�� ����)

#define DES_WEB_DELETE_ITEM							503		// 2013-03-13 by hskim, �� ĳ�� ���� - �� �������̽��� ���� ���� ������ ������

#define DES_INGAME_SHOW								504		// �ΰ��� ���սĿ� ǥ������ ���� // 2013-07-02 by bhsohn �ΰ��� ���ս� Show�߰� ó��
#define DES_WEBPAGE_OPEN							505		// ������ ���� ���������� �ٿ�� // 2013-09-27 by jhseol, 1�ֳ� �̺�Ʈ

// start 2011-09-01 by hskim, ��Ʈ�� �ý��� 2��

// �� ������ ������ ���� ( 600 ~ 699 : 100��)  
// 2013-04-18 by jhseol,bckim �̴��� �Ƹ� - �߰� DesParam ����
#define DES_OPTION_ITEM_DEFAULT_DESPARAM			600		// �̴��� �Ƹӿ� ����� �ɼ� ���������� ������ DesParam
// 2014-07-17 by bckim, �����̾� �Ƹ� �÷���
#define DES_PREMIUM_OPTION_ITEM_DEFAULT_DESPARAM	601		// �̴��� �����̾� �Ƹӿ� ����� �ɼ� ���������� ������ DesParam
// End. 2014-07-17 by bckim, �����̾� �Ƹ� �÷���
// 2014-12-29 by shchoi �̴��� �� �Ƹ�
#define DES_OLD_OPTION_ITEM_DEFAULT_DESPARAM		602		// �̴��� �� �Ƹӿ� ����� �ɼ� ���������� ������ DesParam

// ��Ʈ�� ���� �����۷� ���� (23000 ~ 23899 : 900 �� )
#define DES_PET_SOCKET_ITEM_AUTOKIT					23000		// ��Ʈ�� �ý��� ���Ϸ� - �ڵ� ŰƮ, �ʼ������� DestParameter 0���� ���� �ؾ���
#define DES_PET_SOCKET_ITEM_AUTOSKILL				23001		// ��Ʈ�� �ý��� ���Ϸ� - �ڵ� ��ų, �ʼ������� DestParameter 0���� ���� �ؾ���
#define DES_PET_SOCKET_ITEM_SPEED					23002		// ��Ʈ�� �ý��� ���Ϸ� - �ڵ� ��ų, �ʼ������� DestParameter 0���� ���� �ؾ���

// ��Ʈ�� �ڵ� ŰƮ �����۷� ���� (23900 ~ 23909 : 10 ��)
#define DES_PET_SLOT_ITEM_AUTOKIT_HP				23900		// �ڵ� ŰƮ HP		=> VALUE : ��� 1 ~ 100 ����
#define DES_PET_SLOT_ITEM_AUTOKIT_SHIELD			23901		// �ڵ� ŰƮ Shield	=> VALUE : ��� 1 ~ 100 ����
#define DES_PET_SLOT_ITEM_AUTOKIT_SP				23902		// �ڵ� ŰƮ SP		=> VALUE : ��� 1 ~ 100 ����

// ��Ʈ�� �ڵ� ��ų �����۷� ���� (23910 ~ 23919 : 10 ��)
#define DES_PET_SLOT_ITEM_AUTOSKILL_AGEAR			23910		// �ڵ� ��ų A ���
#define DES_PET_SLOT_ITEM_AUTOSKILL_BGEAR			23911		// �ڵ� ��ų B ���
#define DES_PET_SLOT_ITEM_AUTOSKILL_IGEAR			23912		// �ڵ� ��ų I ���
#define DES_PET_SLOT_ITEM_AUTOSKILL_MGEAR			23913		// �ڵ� ��ų M ���

#define IS_DES_PET_SOCKET_ITEM(pItemInfo)	( DES_PET_SOCKET_ITEM_AUTOKIT <= (pItemInfo)->ArrDestParameter[0] && (pItemInfo)->ArrDestParameter[0] <= DES_PET_SOCKET_ITEM_SPEED )
// end 2011-09-01 by hskim, ��Ʈ�� �ý��� 2��

// 2009-04-21 by cmkwon, ITEM�� DesParam �ʵ� ���� 8���� �ø��� - ITEM::IsExistDesParam() �Լ��� ������
//#define IS_EXIST_DES_PARAM(pItemInfo, des)	((des) == (pItemInfo)->DestParameter1 || (des) == (pItemInfo)->DestParameter2 \
//												|| (des) == (pItemInfo)->DestParameter3 || (des) == (pItemInfo)->DestParameter4)

// 2008-10-21 by cmkwon, �������� ���õ� ����� �ٽ� ������ �ʰ� ���� - 
// 2009-04-21 by cmkwon, ITEM�� DesParam �ʵ� ���� 8���� �ø��� - 
//#define IS_DES_RARE_FIX_PREFIX(pItemInfo)	( DES_RARE_FIX_PREFIX == (pItemInfo)->DestParameter1 )
//#define IS_DES_RARE_FIX_SUFFIX(pItemInfo)	( DES_RARE_FIX_SUFFIX == (pItemInfo)->DestParameter1 )
#define IS_DES_RARE_FIX_PREFIX(pItemInfo)	( DES_RARE_FIX_PREFIX == (pItemInfo)->ArrDestParameter[0] )
#define IS_DES_RARE_FIX_SUFFIX(pItemInfo)	( DES_RARE_FIX_SUFFIX == (pItemInfo)->ArrDestParameter[0] )

// 2006-07-26 by cmkwon
// 2009-04-21 by cmkwon, ITEM�� DesParam �ʵ� ���� 8���� �ø��� - �Ʒ��� ���� ���� ��.
//#define IS_BAZAAR_SKILL(pItemInfo)			(IS_EXIST_DES_PARAM((pItemInfo), DES_BAZAAR_SELL) || IS_EXIST_DES_PARAM((pItemInfo), DES_BAZAAR_BUY))
#define IS_BAZAAR_SKILL(pItemInfo)			((pItemInfo)->IsExistDesParam(DES_BAZAAR_SELL) || (pItemInfo)->IsExistDesParam(DES_BAZAAR_BUY))

// 2006-08-14 by dhjin
// 2009-04-21 by cmkwon, ITEM�� DesParam �ʵ� ���� 8���� �ø��� - 
//#define IS_KILLMARK_EXP(pItemInfo)			(DES_KILLMARK_EXP==(pItemInfo)->DestParameter1)
#define IS_KILLMARK_EXP(pItemInfo)			(DES_KILLMARK_EXP==(pItemInfo)->ArrDestParameter[0])

// 2013-05-28 by bhsohn ���¹����� [��ȭ]�� �� ���󰡴� ���� ó��
#define IS_INFUENCE_BUFF(pItemInfo)   ((pItemInfo)->IsExistDesParam(DES_SKILLTYPE_CONSECUTIVE_VICTORIES) || (pItemInfo)->IsExistDesParam(DES_SKILLTYPE_TRUN_AROUND))
// END 2013-05-28 by bhsohn ���¹����� [��ȭ]�� �� ���󰡴� ���� ó��

///////////////////////////////////////////////////////////////////////////////
// 2009-04-21 by cmkwon, ITEM�� DesParam �ʵ� ���� 8���� �ø��� - 
#define SIZE_MAX_DESPARAM_COUNT_IN_ITEM			8


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// 2005-12-21 by cmkwon, �޸��� üũ Ÿ�� ����
#define HACK_CHECK_TYPE_SHOTNUM					1		// 2005-12-20 by cmkwon
#define HACK_CHECK_TYPE_MULTINUM				2		// 2005-12-20 by cmkwon
#define HACK_CHECK_TYPE_REATTACKTIME			3		// 2005-12-20 by cmkwon
#define HACK_CHECK_TYPE_REPEATTIME				4		// 2005-12-20 by cmkwon
#define HACK_CHECK_TYPE_TIME					5		// 2005-12-20 by cmkwon
#define HACK_CHECK_TYPE_RANGEANGLE				6		// 2005-12-20 by cmkwon
#define HACK_CHECK_TYPE_BOOSTERANGLE			7		// 2005-12-20 by cmkwon
#define HACK_CHECK_TYPE_ORBITTYPE				8		// 2005-12-20 by cmkwon
#define HACK_CHECK_TYPE_ABILITYMIN				9		// 2005-12-20 by cmkwon
#define HACK_CHECK_TYPE_ABILITYMAX				10		// 2005-12-20 by cmkwon
#define HACK_CHECK_TYPE_SPEEDPENALTY			11		// 2005-12-20 by cmkwon
#define HACK_CHECK_TYPE_RANGE					12		// 2005-12-20 by cmkwon
#define HACK_CHECK_TYPE_TRANSPORT				13		// 2005-12-20 by cmkwon
#define HACK_CHECK_TYPE_TOTALWEIGHT				14		// 2005-12-20 by cmkwon
#define HACK_CHECK_TYPE_POSITION				15		// 2005-12-20 by cmkwon
#define HACK_CHECK_TYPE_MAP_CHECK_SUM			16		// 2007-04-10 by cmkwon
#define HACK_CHECK_TYPE_RESOBJ_CHECK_SUM		17		// 2007-05-28 by cmkwon

#define HACK_CHECK_TYPE_END				HACK_CHECK_TYPE_RESOBJ_CHECK_SUM		// 2012-12-14 by hskim, �޸��� �ڵ� ���� ��� ����

///////////////////////////////////
// ������ ����
#define MAT_MATERIAL01						0	// ����1
#define MAT_MATERIAL02						1	// ����2
#define MAT_MATERIAL03						2	// ����3
#define MAT_MATERIAL04						3	// ����4
#define MAT_MATERIAL05						4	// ����5

///////////////////////////////////////////////////////////////////////////////
// ���� �������� ȸ���� �ʿ��� SPI
#define COST_HP_REPAIR_PER_1HP				5		// 1HP �� ȸ�� ���
#define COST_DP_REPAIR_PER_1DP				3		// 1DP �� ȸ�� ��� - ����
#define COST_EP_REPAIR_PER_1EP				1		// 1EP �� ȸ�� ��� - ����
#define COST_SP_REPAIR_PER_1SP				200		// 1SP �� ȸ�� ��� - 

///////////////////////////////////
// Skills

/******************************************************************************
//  BEGIN - Deprecated - 2003. 04. 21.

// ����ü�� ItemInfo(skill)�� �̿��� ���ÿ� ������ ������ ������ �����Ѵ�
// skill & item �� RequiredLevel field�� ����Ѵ�
#define LEVEL_TRANSMITTER			0x00	// ��ű� ����, �޽��� ��밡��(����1)
#define LEVEL_BEAM					0x01	// ���迭 ����(����3)
#define LEVEL_ROCKET				0x02	// ���� ����(����5)
#define LEVEL_PARTY					0x03	// ��Ƽ ����,����(����6)
#define LEVEL_PICKING				0x04	// �ڿ�ä��(����10)
#define LEVEL_BANK					0x05	// �����밡��(����11)
#define LEVEL_SALE					0x06	// ������ �ڵ��ǸŰ���(����12)
#define LEVEL_TALKROOM				0x07	// ��ȭ�� ����(����13)
#define LEVEL_GUIDED				0x08	// ����ź�迭 ����(����15)
#define LEVEL_PET					0x09	// �� ��밡��(����20)
#define LEVEL_GUILD					0x0A	// ��� ����(����30)
#define LEVEL_MAKING				0x0B	// ������ ���� �ɷ�(����50)
// END - Deprecated - 2003. 04. 21.
******************************************************************************/

///////////////////////////////////
// Skill - BaseNum & Macro

/* ��ų�� ItemNum �� BaseNum�� ����� ��
	- ItemNum: �� 7�ڸ� ����, DB�� ����
		1,2	�ڸ�: 78
		3	�ڸ�: UnitKind(BT:0, OT: 1, DT: 2, ST: 3)
		4	�ڸ�: Skill ����(����: 0, ���: 1, ��Ʈ��: 2, �Ӽ�|����: 3)
		5,6	�ڸ�: ��ų ��ȣ
		7	�ڸ�: Skill Level
	- BaseNum: ItemNum���� 7��° �ڸ��� 0���� �ٲ۴�, DB�� ���� �ȵ�
*/
#ifdef _ATUM_SERVER
	#define SKILL_BASE_NUM(x)	((int)x/10)*10	
#endif
// 2013-03-12 by jhseol, ��ų �ѹ��� �ý��� ����
#ifdef SC_SKILL_NUMBERING_RENEWAL_JHSEOL_BHSOHN
#define SKILL_KIND_ATTACK		ITEMKIND_SKILL_ATTACK				// ����
#define SKILL_KIND_DEFENSE		ITEMKIND_SKILL_DEFENSE				// ���
#define SKILL_KIND_CONTROL		ITEMKIND_SKILL_SUPPORT				// ��Ʈ��
#define SKILL_KIND_ATTRIBUTE	ITEMKIND_SKILL_ATTRIBUTE			// �Ӽ�/����
#else	// #ifdef SC_SKILL_NUMBERING_RENEWAL_JHSEOL_BHSOHN
					// ��ų�� ItemNum���� BaseNum�� ����
#define SKILL_LEVEL(x)		(x - ((int)x/10)*10)				// ��ų�� ItemNum���� SkillLevel�� ����
#define SKILL_NUMBER(x)		((int)x/10) - ((int)x/1000)*100		// ��ų ��ȣ
#define SKILL_KIND(x)		((int)x/1000) - ((int)x/10000)*10	// Skill ����(����: 0, ���: 1, ��Ʈ��: 2, �Ӽ�|����: 3)
#define SKILL_UNIT_KIND(x)	((int)x/10000) - ((int)x/100000)*10	// UnitKind(BT:0, OT: 1, DT: 2, ST: 3)

#define SKILL_KIND_ATTACK		0				// ����
#define SKILL_KIND_DEFENSE		1				// ���
#define SKILL_KIND_CONTROL		2				// ��Ʈ��
#define SKILL_KIND_ATTRIBUTE	3				// �Ӽ�/����
#endif	// #ifdef SC_SKILL_NUMBERING_RENEWAL_JHSEOL_BHSOHN
// end 2013-03-12 by jhseol, ��ų �ѹ��� �ý��� ����
//#define SKILL_KIND_SUPPORT		4

///////////////////////////////////////////////////////////////////////////////
// 2005-11-22 by cmkwon, ��ų BaseNum ����
// B-Gear
#define BGEAR_SKILL_BASENUM_BACKMOVEMACH		7802010	// ��Ʈ��	- �鹫�긶��
#define BGEAR_SKILL_BASENUM_TURNAROUND			7802020	// ��Ʈ��	- �Ͼ����	
#define BGEAR_SKILL_BASENUM_GROUNDBOMBINGMODE	7800040	// ���		- �������ݸ��
#define BGEAR_SKILL_BASENUM_AIRBOMBINGMODE		7800070	// ���		- �������ݸ��
#define BGEAR_SKILL_BASENUM_INVISIBLE			7803030	// ���		- �κ�����
#define BGEAR_SKILL_BASENUM_BIG_BOOM			7803040	// ��Ƽ��	- ���

// M-Gear
#define MGEAR_SKILL_BASENUM_SMARTSP				7813020	// �ð�		- ����ƮSP
#define MGEAR_SKILL_BASENUM_CALLOFHERO			7813030	// Ŭ��		- �ݿ��������
#define MGEAR_SKILL_BASENUM_REVERSEENGINE		7812020	// ���		- ����������
#define MGEAR_SKILL_BASENUM_INVICIBLE			7811100	// ��Ƽ�� 	- ����
#define MGEAR_SKILL_BASENUM_SCANNING			7813060	// ���� 	- ��ĵ

// A-Gear
#define AGEAR_SKILL_BASENUM_SIEGEMODE			7820050	// ���		- ������
#define AGEAR_SKILL_BASENUM_SIEGEDEFENSEMODE	7821040	// ���		- ������潺���
#define AGEAR_SKILL_BASENUM_GROUNDACCELERATOR	7822010	// ��� 	- �׶��忢��������
#define AGEAR_SKILL_BASENUM_AIRSIEGEMODE    	7820060	// ��� 	- ���������
#define AGEAR_SKILL_BASENUM_CAMOUFLAGE	    	7823040	// ��� 	- ����
#define AGEAR_SKILL_BASENUM_BARIAL		    	7821060	// �ð�  	- ������	// 2013-01-29 by jhseol, ������ ��ų ����Ʈ ����

// I-Gear
#define IGEAR_SKILL_BASENUM_BACKMOVEMACH		7832010	// ��Ʈ��	- �鹫�긶��
#define IGEAR_SKILL_BASENUM_TURNAROUND			7832020	// ��Ʈ��	- �Ͼ����
#define IGEAR_SKILL_BASENUM_SILENCE				7833040	// ��Ƽ��	- ħ��
#define IGEAR_SKILL_BASENUM_FRENZY				7830030	// ��Ƽ��	- ������
#define IGEAR_SKILL_BASENUM_BERSERKER			7833050	// ��Ƽ��	- ����

// 2005-11-22 by cmkwon, �ӽÿ����� ���� Ŭ���̾�Ʈ���� ��� �� �̾ ���� ��, ���� �����ؾ���
#define SMART_SPEED								7812020
#define FLASH_ACCELERATOR						7822030

// 2005-11-22 by cmkwon
//// BT
//#define BT_SKILL_QUICKTURN			7802010	// Ŭ����
//#define BT_SKILL_REVERSETURN		7802020	// Ŭ����
//#define BT_SKILL_COPTERFLIGHT		7802030	// Ŭ����
//
//// OT
//#define OT_SKILL_GRENADEMASTERY		7810010	// ������
//#define OT_SKILL_LAUNCHERMASTERY	7810020	// ������
//#define OT_SKILL_DUALSHOT			7810030	// �ð���
//#define OT_SKILL_SCORPING			7810040	// �ð���
//#define OT_SKILL_FRENZY				7810050	// �ð���
//#define OT_SKILL_CONVERGINGSHOT		7810060	// �ð���
//#define OT_SKILL_BUNDLEMASTERY		7810070	// ������
//#define OT_SKILL_OVERRADAR			7810080	// �ð���
//#define OT_SKILL_CRAZYSHOT			7810090	// �ð���
//#define OT_SKILL_EYEFORANEYE		7810100	// �ð���
//#define OT_SKILL_BURSTSHOT			7810110	// �ð���
//#define OT_SKILL_FLYINGWORM			7811010	// �ð���
//#define OT_SKILL_DIFFUSION			7811020	// �ð���
//#define OT_SKILL_PARALLELMOVEMENT	7812030	// Ŭ����
//#define OT_SKILL_SCREWPUSHING		7812040	// Ŭ����
//#define OT_SKILL_OVERRISING			7812050	// Ŭ����
////#define OT_SKILL_NONAME			7812060	// �ð���
//
//// DT
//#define DT_SKILL_CANNONMASTERY		7820010	// ������
//#define DT_SKILL_MASSDRIVEMASTERY	7820020	// ������
//#define DT_SKILL_CHARGINGSHOT		7820030	// �ð���
//#define DT_SKILL_WILDSHOT			7820040	// �ð���
//#define DT_SKILL_WIDERANGE			7820050	// �ð���
//#define DT_SKILL_HAWKEYE			7820060	// �ð���
//#define DT_SKILL_MINEMASTERY		7820070	// ������
//#define DT_SKILL_SPHERETARGET		7820080	// �ð���
//#define DT_SKILL_CARPETBLAST		7820090	// �ð���
//#define DT_SKILL_ASSASSINSCOPE		7820100	// �ð���
//#define DT_SKILL_MINEDISTURBANCE	7820110	// �ð���
//#define DT_SKILL_CAMOUFLAGE			7821010	// �ð���
//#define DT_SKILL_SMOKESCREEN		7821020	// �ð���
//#define DT_SKILL_MIRRORIMAGE		7821030	// �ð���
//#define DT_SKILL_DASH				7822010	// Ŭ����
//#define DT_SKILL_AUTODRIVING		7822020	// Ŭ����
//#define DT_SKILL_CONCENTRATION		7822030	// �ð���
//#define DT_SKILL_OREGATHERING		7822040	// Ŭ����
//#define DT_SKILL_OREFINDING			7822050	// Ŭ����
//#define DT_SKILL_ORESEARCH			7822060	// Ŭ����
//#define DT_SKILL_OREREFINING		7822070	// Ŭ����
//
//// ST
//#define ST_SKILL_VULCANMASTERY		7830010	// ������
//#define ST_SKILL_GATLINGMASTERY		7830020	// ������
//#define ST_SKILL_STRAFESHOT			7830030	// �ð���
//#define ST_SKILL_SNIPESHOT			7830040	// �ð���
//#define ST_SKILL_BURSTSHOT			7830050	// �ð���
//#define ST_SKILL_WIDESHOT			7830060	// �ð���
//#define ST_SKILL_MISSILEMASTERY		7830070	// ������
//#define ST_SKILL_STRAFEBLAST		7830080	// �ð���
//#define ST_SKILL_MULTIPLEBLAST		7830090	// �ð���
//#define ST_SKILL_FRENZYBLAST		7830100	// �ð���
//#define ST_SKILL_WIDEBLAST			7830110	// �ð���
//#define ST_SKILL_BLASTPROTECTION	7831010	// �ð���
//#define ST_SKILL_BLASTREFLECTION	7831020	// �ð���
//#define ST_SKILL_YOYOSPINNING		7832010	// Ŭ����
//#define ST_SKILL_OVERBOOST			7832020	// Ŭ����
//#define ST_SKILL_COPTERFLIGHT		7832030	// �ð���
//#define ST_SKILL_CONCENTRATION		7832040	// �ð���

// 2005-11-22 by cmkwon
// BT
//#define 	BT_SKILL_AUTOMATICMASTERY		7800010		// ������
//#define 	BT_SKILL_RIFLEMASTERY			7800020		// ������
//#define 	BT_SKILL_STRAFESHOT				7800030		// ������
//#define 	BT_SKILL_SNIPESHOT				7800040		// �ð���
//#define 	BT_SKILL_BURSTSHOT				7800050		// �ð���
//#define 	BT_SKILL_WIDESHOT				7800060		// �ð���
//#define 	BT_SKILL_ROCKETMASTERY			7800070		// ������
//#define 	BT_SKILL_STRAFEBLAST			7800080		// ������
//#define 	BT_SKILL_SNIPEBLAST				7800090		// �ð���
//#define 	BT_SKILL_BURSTBLAST				7800100		// �ð���
//#define 	BT_SKILL_WIDEBLAST				7800200		// �ð���
//#define 	BT_SKILL_DODGE					7801010		// �ð���
//#define 	BT_SKILL_STRATEGICFIELD			7801020		// �ð���
//#define 	BT_SKILL_QUICKTURN				7802010		// Ŭ����
//#define 	BT_SKILL_REVERSETURN			7802020		// Ŭ����
//#define 	BT_SKILL_COPTERFLIGHT			7802030		// Ŭ����
//#define 	BT_SKILL_CONCENTRATION			7802040		// �ð���
//
//// OT
//#define 	OT_SKILL_GRENADEMASTERY			7811010		// ������
//#define 	OT_SKILL_LAUNCHERMASTERY		7811020		// ������
//#define 	OT_SKILL_DUALSHOT				7811030		// �ð���
//#define 	OT_SKILL_SCORPING				7811040		// �ð���
//#define 	OT_SKILL_FRENZY					7811050		// �ð���
//#define 	OT_SKILL_CONVERGINGSHOT	 		7811060		// �ð���
//#define 	OT_SKILL_BUNDLEMASTERY			7811070		// ������
//#define 	OT_SKILL_OVERRADAR				7811080		// �ð���
//#define 	OT_SKILL_CRAZYSHOT	 			7811090		// �ð���
//#define 	OT_SKILL_EYEFORANEYE 			7811100		// �ð���
//#define 	OT_SKILL_BURSTSHOT				7811110		// �ð���
//#define 	OT_SKILL_FLYINGWORM	 			7812010		// �ð���
//#define 	OT_SKILL_DIFFUSION	 			7812020		// Ŭ����
//#define 	OT_SKILL_PARALLELMOVEMENT 		7812030		// Ŭ����
//#define 	OT_SKILL_SCREWPUSHING 			7812040		// Ŭ����
//#define 	OT_SKILL_OVERRISING	 			7812050		// �ð���
////#define 		���� ȸ��				7812060
//
//// DT
//#define 	DT_SKILL_CANNONMASTERY			7820010		// ������
//#define 	DT_SKILL_MASSDRIVEMASTERY		7820020		// ������
//#define 	DT_SKILL_CHARGINGSHOT			7820030		// �ð���
//#define 	DT_SKILL_WILDSHOT				7820040		// �ð���
//#define 	DT_SKILL_WIDERANGE				7820050		// �ð���
//#define 	DT_SKILL_HAWKEYE				7820060		// �ð���
//#define 	DT_SKILL_MINEMASTERY			7820070		// ������
//#define 	DT_SKILL_SPHERETARGET			7820080		// �ð���
//#define 	DT_SKILL_CARPETBLAST			7820090		// Ŭ����
//#define 	DT_SKILL_ASSASSINSCOPE			7820100		// �ð���
//#define 	DT_SKILL_MINEDISTURBANCE		7820110		// �ð���
//#define 	DT_SKILL_CAMOUFLAGE				7821010		// �ð���
//#define 	DT_SKILL_SMOKESCREEN			7821020		// �ð���
//#define 	DT_SKILL_MIRRORIMAGE			7821030		// �ð���
//#define 	DT_SKILL_DASH					7822010		// Ŭ����
//#define 	DT_SKILL_AUTODRIVING			7822020		// �ð���
//#define 	DT_SKILL_CONCENTRATION			7822030		// �ð���
//#define 	DT_SKILL_OREGATHERING			7822040		// ������
//#define 	DT_SKILL_OREFINDING				7822050		// ������
//#define 	DT_SKILL_ORESEARCH				7822060		// �ð���
//#define 	DT_SKILL_OREREFINING			7822070		// Ŭ����
//
//// ST
//#define 	ST_SKILL_VULCANMASTERY			7830010		// ������
//#define 	ST_SKILL_GATLINGMASTERY			7830020		// ������
//#define 	ST_SKILL_STRAFESHOT				7830030		// ������
//#define 	ST_SKILL_SNIPESHOT				7830040		// �ð���
//#define 	ST_SKILL_BURSTSHOT				7830050		// �ð���
//#define 	ST_SKILL_WIDESHOT				7830060		// �ð���
//#define 	ST_SKILL_MISSILEMASTERY			7830070		// ������
//#define 	ST_SKILL_STRAFEBLAST			7830080		// ������
//#define 	ST_SKILL_MULTIPLEBLAST			7830090		// �ð���
//#define 	ST_SKILL_FRENZYBLAST			7830100		// �ð���
//#define 	ST_SKILL_WIDEBLAST				7830110		// �ð���
//#define 	ST_SKILL_BLASTPROTECTION		7831010		// �ð���
//#define 	ST_SKILL_BLASTREFLECTION		7831020		// �ð���
//#define 	ST_SKILL_YOYOSPINNING			7832010		// Ŭ����
//#define 	ST_SKILL_OVERBOOST				7832020		// �ð���
//#define 	ST_SKILL_COPTERFLIGHT			7832030		// Ŭ����
//#define 	ST_SKILL_CONCENTRATION			7832040		// �ð���
////


///////////////////////////////////////////////////////////////////////////////
// Monster Target Type
#define MONSTER_TARGETTYPE_NORMAL			0			// �Ϲ� Ÿ�� Ÿ�� ����
#define MONSTER_TARGETTYPE_TUTORIAL			1			// Ʃ�丮�� Ÿ�� Ÿ�� ����	- Ư�� �������Ը� ���̰� �������� �����۵� Ư�� �������Ը� ���δ�
#define MONSTER_TARGETTYPE_MISSION			2			// �̼� Ÿ�� Ÿ�� ����		- �̼��� ���� �����鿡�Ը� ���̰� �������� �����۵� Ư�� �����鿡�Ը� ���δ�


///////////////////////////////////////////////////////////////////////////////
// Event-Related Definitions
///////////////////////////////////////////////////////////////////////////////
// Event ����ü
struct EVENTINFO
{
// 2010-04-14 by cmkwon, ���� �޸� ���� ���� ���� - �Ʒ��� ���� ����
// 	BYTE		m_EventReceiver;							// EVENT_RECEIVER_XXX
// 	INT			m_TileOrObjectIndex;						// TileIndex or ObjectIndex
// 	D3DXVECTOR3 m_vPosition;								// ���������� ���� �����ÿ��� ����Ѵ�. �������� �ε� �� ������ 0���� �����, ��, ObjectEvent�� ���� Object�� Position, by kelovon, 20030713
// 	BYTE		m_bEventType;								// EVENT_TYPE_XXX
// 	short		m_EventwParam1;								// ���� event area index, Building Index, ~0�̸� ���߿� T_FP_EVENT_NOTIFY_WARP_OK ���� m_EventwParam1�� Ȯ���ؼ� ~0�̸� SAFE_DELETE()�Ѵ�
// 	short		m_EventwParam2;								// ã�ư� event area index, Building Kind, ~0�̸� defaultWarpTargetIndex�� ����Ѵ�
// 	short		m_EventwParam3;								// �� �̸�
// 	INT			m_NextEventIndex;							// 2005-07-15 by cmkwon, Ÿ�� event area index
// 	BYTE		m_byObjectMonsterCreated;
// 	BYTE		m_byBossMonster;							// 2006-11-22 by cmkwon, ������ ����(m_byIsCityWarMonster->m_byBossMonster) - ������������ ������
// 	INT			m_nObejctMonsterUnitKind;					// 2009-10-12 by cmkwon, ������ī ���� ��� ���� - ������ ���� ���Ұ� ���� ����(��Ʈ�÷���)���� ����, 
// 	DWORD		m_dwLastTimeObjectMonsterCreated;
// 	//	char		m_EventstrParam[SIZE_MAX_EVENT_PARAM_NAME];	// �� �̸�
	///////////////////////////////////////////////////////////////////////////////
	// 2010-04-14 by cmkwon, ���� �޸� ���� ���� ���� - 
	D3DXVECTOR3 m_vPosition;								// ���������� ���� �����ÿ��� ����Ѵ�. �������� �ε� �� ������ 0���� �����, ��, ObjectEvent�� ���� Object�� Position, by kelovon, 20030713
	INT			m_nObejctMonsterUnitKind;					// 2009-10-12 by cmkwon, ������ī ���� ��� ���� - ������ ���� ���Ұ� ���� ����(��Ʈ�÷���)���� ����, 
	INT			m_NextEventIndex;							// 2005-07-15 by cmkwon, Ÿ�� event area index
	DWORD		m_dwLastTimeObjectMonsterCreated;
	short		m_EventwParam1;								// ���� event area index, Building Index, ~0�̸� ���߿� T_FP_EVENT_NOTIFY_WARP_OK ���� m_EventwParam1�� Ȯ���ؼ� ~0�̸� SAFE_DELETE()�Ѵ�
	short		m_EventwParam2;								// ã�ư� event area index, Building Kind, ~0�̸� defaultWarpTargetIndex�� ����Ѵ�
	short		m_EventwParam3;								// �� �̸�
	BYTE		m_EventReceiver;							// EVENT_RECEIVER_XXX
	BYTE		m_bEventType;								// EVENT_TYPE_XXX
	BYTE		m_byObjectMonsterCreated;
	BYTE		m_byBossMonster;							// 2006-11-22 by cmkwon, ������ ����(m_byIsCityWarMonster->m_byBossMonster) - ������������ ������

	EVENTINFO()
	{
		ResetEVENTINFO();
	}
	void ResetEVENTINFO(void)
	{
		m_EventReceiver						= 0;
// 2010-04-14 by cmkwon, ���� �޸� ���� ���� ���� - �ʿ� ��� ���ŵ�
//		m_TileOrObjectIndex					= 0;
		m_vPosition							= D3DXVECTOR3(0,0,0);
		m_bEventType						= 0;
		m_EventwParam1						= 0;
		m_EventwParam2						= 0;
		m_EventwParam3						= 0;
		m_NextEventIndex					= 0;
		m_byObjectMonsterCreated			= FALSE;
		m_byBossMonster						= FALSE;		// 2006-11-22 by cmkwon, ������ ����(m_byIsCityWarMonster->m_byBossMonster) - ������������ ������
		m_nObejctMonsterUnitKind			= 0;
		m_dwLastTimeObjectMonsterCreated	= 0;
	}


	void * operator new(size_t size);
	void operator delete(void* p);
};

#define EVENT_RECEIVER_NONE		(BYTE)0		// �׳� �̺�Ʈ
#define	EVENT_RECEIVER_TILE		(BYTE)1		// TILE�� ���� �̺�Ʈ
#define	EVENT_RECEIVER_OBJECT	(BYTE)2		// OBJECT�� ���� �̺�Ʈ

// PK Type
#define PK_TYPE_PK						0x00
#define PK_TYPE_COMBAT					0x01
#define PK_TYPE_SAFE					0x02

// Event Type
typedef BYTE EventType_t;

#define EVENT_TYPE_NO_OBJECT_MONSTER		(EventType_t)0	// 
#define EVENT_TYPE_NOEVENT					(EventType_t)0
#define EVENT_TYPE_WARP						(EventType_t)1
#define EVENT_TYPE_WARP_TARGET				(EventType_t)2
#define EVENT_TYPE_ENTER_BUILDING			(EventType_t)3		// �������� �̺�Ʈ - EventParam1(EventAreaIndex), EventParam2(�̷��� �̵� �� �̷����� ������Ʈ EventAreaIndex)
#define EVENT_TYPE_LANDING					(EventType_t)4		// ���� Object
#define EVENT_TYPE_RACING_CHECK_POTINT		(EventType_t)5		// ���̽� üũ ����Ʈ Object
#define EVENT_TYPE_OBJECT_MONSTER			(EventType_t)6		// ObjectMonster Position Information Object
//#define EVENT_TYPE_OBJECT_MONSTER_STOP		(EventType_t)6	// ������, ObjectMonster Position Object
//#define EVENT_TYPE_OBJECT_MONSTER_ROTATE	(EventType_t)7		// Ÿ�ٺ��Ͱ� ���ϴ� ����, ObjectMonster Position Object
#define EVENT_TYPE_PATTERN_POINT			(EventType_t)8		// ĳ���� ������ ������ ����/�� ������Ʈ
#define EVENT_TYPE_OBJ_BUILDING_NPC			(EventType_t)9		// 2005-07-21 by cmkwon, ���� NPC ������Ʈ - EventParam1(EventAreaIndex), NextEventIndex(NPCIndex)
#define EVENT_TYPE_LANDING_PATTERN_START	(EventType_t)10		// 2005-07-14 by cmkwon, ����忡�� ���� ������ ���� ������Ʈ - EventParam1(EventAreaIndex), NextEventIndex(���� ��ǥ ������Ʈ EventAreaIndex)
#define EVENT_TYPE_LANDING_PATTERN_END		(EventType_t)11		// 2005-07-14 by cmkwon, ����忡�� ���� ������ ���� ������Ʈ, ������Ʈ�� ������ ���� ���°� �ȴ�. - EventParam1(EventAreaIndex), NextEventIndex(���� �� �̵� �� ��ǥ ������Ʈ EventAreaIndex)
#define EVENT_TYPE_TAKEOFF_PATTERN_START	(EventType_t)12		// 2005-07-14 by cmkwon, ����忡�� �̷� ������ ���� ������Ʈ - EventParam1(EventAreaIndex), NextEventIndex(�̷� ��ǥ ������Ʈ EventAreaIndex)
#define EVENT_TYPE_TAKEOFF_PATTERN_END		(EventType_t)13		// 2005-07-14 by cmkwon, ����忡�� �̷� ������ ���� ������Ʈ - EventParam1(EventAreaIndex)
#define EVENT_TYPE_OBJ_ENTER_BUILDING		(EventType_t)14		// 2005-07-22 by cmkwon, �� ���� ��  �������� �̵��� ��ǥ ������Ʈ - EventParam1(EventAreaIndex)
#define EVENT_TYPE_OBJ_QUEST_OBJECT			(EventType_t)15		// 2005-08-17 by cmkwon, ����Ʈ���� �̿�Ǵ� �浹 ������Ʈ - EventParam1(EventAreaIndex)
#define EVENT_TYPE_CHARACTERMODE_WARP			(EventType_t)21		// 2006-07-14 by cmkwon, ĳ���͸�忡�� ���� �ҽ� ������Ʈ
#define EVENT_TYPE_CHARACTERMODE_WARP_TARGET	(EventType_t)22		// 2006-07-14 by cmkwon, ĳ���͸�忡�� ���� Ÿ�� ������Ʈ
#define EVENT_TYPE_ENTER_BUILDING_BAZAAR		(EventType_t)23		// 2006-07-19 by cmkwon, ���λ��� ����
#define EVENT_TYPE_CHARACTERMODE_DIRECTLY_WARP	(EventType_t)24		// 2007-12-14 by cmkwon, ĳ���͸�忡�� �ٷ� ���� �ý��� ���� - �� ������Ʈ�� �浹�� �ٷ� ������

#define EVENT_TYPE_INFI_CINEMA				(EventType_t)30		// 2010. 05. 27 by jskim �ó׸� ���� ī�޶� ����
#define EVENT_TYPE_PARAM_INFI_CINEMA		701					// 2010. 05. 27 by jskim �ó׸� ���� ī�޶� ����

#define EVENT_TYPE_INFI_CINEMA_THIRD				(EventType_t)31		// 2011-06-23 by jhahn ����3�� �ó׸� ���� ī�޶� ����
#define EVENT_TYPE_PARAM_INFITHIRD_CINEMA_FAIL			702						// 2011-06-23 by jhahn ����3�� �ó׸� ���� ī�޶� ����
#define EVENT_TYPE_PARAM_INFITHIRD_CINEMA_SUCCESS		703						// 2011-06-23 by jhahn ����3�� �ó׸� ���� ī�޶� ����

#define EVENT_TYPE_TUTORIAL_GATE_POINT		(EventType_t)100	// 

#define EVENT_TYPE2_TRIGGERWARP			    (EventType_t)11 

extern char *Get_EVENT_TYPE_String(EventType_t i_evType);

// Event Result
typedef BYTE EventResult_t;

//#define EVENT_RESULT_ERROR				0x00	// check: ���ʿ��ϴٰ� �Ǵ�, EVENT_RESULT_CLOSE_CONNECTION�� ��ȯ��, �ʿ��ϸ� �츲, 20030812, kelovon
#define EVENT_RESULT_BREAK				0x01	// �̺�Ʈ�� ó������ �ʾ���
#define EVENT_RESULT_CONTINUE			0x02	// �̺�Ʈ�� ���������� ó����, ��� �����ϸ� ��
#define EVENT_RESULT_CLOSE_CONNECTION	0x03	// �ɰ��� ���� �߻�, ���� ���� �䱸

///////////////////////////////////////////////////////////////////////////////
// Variable Type Definitions
///////////////////////////////////////////////////////////////////////////////
typedef USHORT ClientIndex_t;
typedef vector<ClientIndex_t>		vectorClientIndex;
typedef set<ClientIndex_t>			setClientIndex_t;		// 2009-12-11 by cmkwon, ������ ��׷η� Ÿ���� �����ϴ� ���� ���� - 

// MapIndex �� ChannelIndex ������
struct MAP_CHANNEL_INDEX
{
	// member variables
	MapIndex_t		MapIndex;
	ChannelIndex_t	ChannelIndex;

	// overloaded operators
	inline bool operator==(MAP_CHANNEL_INDEX &rhs)
	{
		return (this->MapIndex == rhs.MapIndex && this->ChannelIndex == rhs.ChannelIndex);
	}

	inline bool operator!=(MAP_CHANNEL_INDEX &rhs)
	{
		return (this->MapIndex != rhs.MapIndex || this->ChannelIndex != rhs.ChannelIndex);
	}
	inline bool IsSameMapChannelIndex(const MAP_CHANNEL_INDEX &rhs)
	{
		return (this->MapIndex == rhs.MapIndex && this->ChannelIndex == rhs.ChannelIndex);
	}

	// functions
	MAP_CHANNEL_INDEX() : MapIndex(0), ChannelIndex(0) {}
	MAP_CHANNEL_INDEX(MapIndex_t mapIdx, ChannelIndex_t channIdx) : MapIndex(mapIdx), ChannelIndex(channIdx) {}
	inline BOOL IsValid() { return (MapIndex != 0); }
	inline void Invalidate() { MapIndex = 0; }
	inline void Validate(MapIndex_t i_MapIndex, ChannelIndex_t i_ChannelIndex)
	{
		MapIndex = i_MapIndex; ChannelIndex = i_ChannelIndex;
	}
};

struct GEAR_STAT
{
	Stat_t	AttackPart;		// ������Ʈ
	Stat_t	DefensePart;	// �����Ʈ
	Stat_t	FuelPart;		// ������Ʈ
	Stat_t	SoulPart;		// ������Ʈ
	Stat_t	ShieldPart;		// ������Ʈ
	Stat_t	DodgePart;		// ȸ����Ʈ, 0 ~ 255�� Ȯ��
};


// 2012-04-12 by jhseol, �Ʒ��� �߰����� - �Ʒ��� PlayCount ���� ����ü
struct SArenaPlayInfo
{
	int				nPlayCount;									// ���� �÷��� ī��Ʈ
	ATUM_DATE_TIME	atimeLastPlayTime;							// ���������� �÷��� �� �ð�
	ATUM_DATE_TIME	atimeResetTime;								// �Ʒ��� ����Ƚ�� �ʱ�ȭ �ð�
};
// end 2012-04-12 by jhseol, �Ʒ��� �߰����� - �Ʒ��� PlayCount ���� ����ü

///////////////////////////////////////////////////////////////////////////////
//	ATUM - Character - Parameter Struct ����
///////////////////////////////////////////////////////////////////////////////
struct CHARACTER_DB_EX;

#if _KILL_STREAK
struct SKILL_STREAK_DATA
{
	int		KillStreak;
	DWORD	LastKillTime;
};
#endif // _KILL_STREAK

#if _RAT_RANK_SYSTEM
struct SRANK_DATA
{
	int ID = 0;							// Integer ID (e.g., 1)
	string Name = "\\gUnknown";			// Formatted name (e.g., "/ePrivate")
	int RequiredFame = 0;				// The minimum fame needed for this rank

	// Nested parameters for stats to keep it organized
	struct Stats {
		float Atk;	// Min/Max of All
		float Pen;	// Penetration
		float Prob;	// Accuracy

		float Def;	// Defense
		float Eva;	// Evasion
		float Res;	// Resistance to ALL DAMAGE --> {(Defense + Evasion) * (1 - 0.1)} = %10 Damage Reduce overall 

	} Rank_Parameters;
};

struct SRANK_SYSTEM
{
	static std::map<int, SRANK_DATA> Table;

	static SRANK_DATA GetRankByFame(int currentFame);
};

#endif // _RAT_RANK_SYSTEM

#if _RAT_ANTI_CHEAT
	// Weapon
	struct SATTACK_COOLDOWN {
		DWORD	Primary_LastAttackTime;
		UINT	Primary_ReAttacktime;

		DWORD	Secondary_LastAttackTime;
		UINT	Secondary_ReAttacktime;

		INT		Secondary_ShotCount;
		INT		Secondary_ShotCountMAX;

		BOOL	Secondary_isOnUse = false;
	};

	// Engine
	struct SENGINE_INFO {
		FLOAT				m_fShuttleSpeed;
		FLOAT				m_fShuttleSpeedMax;
		FLOAT				m_fShuttleSpeedMin;
		FLOAT				m_fShuttleSpeedBoosterOn;
		FLOAT				m_fShuttleGroundSpeed;
		FLOAT				m_fShuttleGroundSpeedMax;

		FLOAT				m_fRealShuttleSpeedMax;
		FLOAT				m_fRealShuttleSpeedMin;
		FLOAT				m_fRealShuttleSpeedBoosterOn;
	};
#endif // _RAT_ANTI_CHEAT

struct CHARACTER
{
#if _KILL_STREAK
	SKILL_STREAK_DATA	KILLSTREAK_INFO;
#endif // _KILL_STREAK

#if _RAT_RANK_SYSTEM
	int					RankID;							// 2012-04-12 by jhseol, �Ʒ��� �߰����� - �Ʒ��� Rank ID
#endif // _RAT_RANK_SYSTEM

#if _RAT_ANTI_CHEAT
	SATTACK_COOLDOWN	ATTACK_INFO;
	SENGINE_INFO		ENGINE_INFO;
#endif // _RAT_ANTI_CHEAT

	ClientIndex_t		ClientIndex;
	char				AccountName[SIZE_MAX_ACCOUNT_NAME];			// ����� ���̵�
	UID32_t				AccountUniqueNumber;						//  ���� ���� ��ȣ
	char				CharacterName[SIZE_MAX_CHARACTER_NAME];		// ����(ĳ����) �̸�
	UID32_t				CharacterUniqueNumber;						// ĳ���� ������ȣ
	BYTE				Gender;							// false(0) : ��, true(1) : ��
	BYTE				PilotFace;						// ȭ�鿡 ��Ÿ���� �ι� �ɸ���
	BYTE				CharacterMode;					// 2005-07-13 by cmkwon, ���� ĳ���� ���� �÷���
	USHORT				Race;							// ����
	USHORT				UnitKind;						// ������ ����
	BYTE				InfluenceType;					// ���� Ÿ������
	BYTE				SelectableInfluenceMask;		// 2005-12-07 by cmkwon, ���¼��ý� ���ð����� ����Mask, �Ѱ������� �ϳ��� ���¸� ���� ������
	BYTE				AutoStatType;					// �ڵ� �й� ���� Ÿ��
	GEAR_STAT			GearStat;						// ��� ����
	GEAR_STAT			TotalGearStat;					// ���� ��� ���� - ��ǻ�� ������ ���� ����
	char				GuildName[SIZE_MAX_GUILD_NAME];	// ��� �̸�
	UID32_t				GuildUniqueNumber;				// ��� ��ȣ, 0�̸� ��� ����
	BYTE				Level;							//
	Experience_t		Experience;						//
	Experience_t		DownExperience;					// ĳ���� ������ ������ ����ġ
	INT					DownSPIOnDeath;					// 2006-04-10 by cmkwon, ĳ���� ������ ������ SPI
	BodyCond_t			BodyCondition;					// ����, bit flag ���
	INT					Propensity;						// ����ġ, ����(��, ��)
	BYTE				Status;							// �ź�
	USHORT				PKWinPoint;						// PK �¸� ��ġ
	USHORT				PKLossPoint;					// PK �й� ��ġ
	USHORT				Material;						// ����(HI : Main, LOW : Sub)
	SHORT				HP;								// Health Point
	float				CurrentHP;						// Current Health Point
	SHORT				DP;								// ����, Defense Point
	float				CurrentDP;						// ���� ����, Current Defense Point
	SHORT				SP;								// Skill Point
	SHORT				CurrentSP;						//
	SHORT				EP;								// Fuel
	float				CurrentEP;						// Current Fuel
	char				PetName[SIZE_MAX_PET_NAME];
	BYTE				PetLevel;
	Experience_t		PetExperience;
	MAP_CHANNEL_INDEX	MapChannelIndex;				// ĳ���Ͱ� ���� �� �� ä��
	D3DXVECTOR3			PositionVector;					// ĳ���� ��ǥ
	D3DXVECTOR3			TargetVector;					//
	D3DXVECTOR3			UpVector;						//
	BYTE				MaxLevel;
	BYTE				BonusStat;						// �߰� 2002.12.13
	// 2005-11-15 by cmkwon, ������
	//	BYTE				BonusSkillPoint;				// �߰� 2002.12.13
	BYTE				BonusStatPoint;					// 2005-11-15 by cmkwon, �������� �ƴ� �ٸ�������� ���� ���ʽ� ���� ����Ʈ, BonusSkillPoint�� ������ // �߰� 2002.12.13
	PartyID_t			LastPartyID;					// ������ ��Ƽ ID, ������������ ����Ǿ��� �� ��Ƽ ������ ���� ����
	INT					RacingPoint;					// 2009-11-02 by cmkwon, ĳ��(�κ�/â�� Ȯ��) ������ �߰� ���� - ����ù��°1Byte:�κ��߰�����, �����ι�°1Byte:â���߰�����, ��������°/�׹�°2Byte�� ������� ����, // Racing ��� Point
	LONGLONG			TotalPlayTime;					// �ʴ���
	ATUM_DATE_TIME		CreatedTime;					// ĳ���� ���� �ð�
	ATUM_DATE_TIME		LastStartedTime;				// ���� ���� ���� �ð�
	ATUM_DATE_TIME		LevelUpTime;					// 2006-12-18 by dhjin, ������ �ð�
	INT					WarPoint;						// 2007-04-17 by dhjin, WP
	INT					CumulativeWarPoint;				// 2007-05-28 by dhjin, ����WP
	INT					ArenaWin;						// 2007-06-07 by dhjin, �Ʒ��� ���� ���� ��
	INT					ArenaLose;						// 2007-06-07 by dhjin, �Ʒ��� ���� ���� ��
	INT					ArenaDisConnect;				// 2007-06-07 by dhjin, �Ʒ��� ���� ����
	LONGLONG			PCBangTotalPlayTime;			// 2007-06-07 by dhjin, PC�� �� �÷��� �ð�, �ʴ���
	INT					SecretInfoOption;				// 2008-06-23 by dhjin, EP3 ���������ɼ� -
	char				NickName[SIZE_MAX_CHARACTER_NAME];	// 2009-02-12 by cmkwon, EP3-3 ���巩ŷ�ý��� ���� - ���� ��ŷ�� ���� NickName
	SArenaPlayInfo		ArenaPlayInfo;					// 2012-04-12 by jhseol, �Ʒ��� �߰����� - ���� : �Ʒ��� �÷��� ����

	// 2013-02-28 by bckim, �������� �����߰�
	BYTE				bUsingReturnItem;
	// 2015-05-26 by bckim, ��Ʈ�� �������� �α��εǴ� ���� �α� ����
	BYTE				bIsBlockedUser;
	// End. 2015-05-26 by bckim, ��Ʈ�� �������� �α��εǴ� ���� �α� ����

	CHARACTER()
	{
		bUsingReturnItem = 0;
	}
	// end 2013-02-28 by bckim, �������� �����߰�

	// operator overloading
	CHARACTER& operator=(const CHARACTER_DB_EX& rhs);
	// 2009-10-12 by cmkwon, ������ī ���� ��� ���� - 
	// 	BYTE GetInfluenceMask(void)
	// 	{
	// 		if(COMPARE_INFLUENCE(InfluenceType, INFLUENCE_TYPE_NORMAL|INFLUENCE_TYPE_VCN))
	// 		{
	// 			return INFLUENCE_TYPE_NORMAL|INFLUENCE_TYPE_VCN;
	// 		}
	// 		return InfluenceType;
	// 	}
		///////////////////////////////////////////////////////////////////////////////
		// 2009-10-12 by cmkwon, ������ī ���� ��� ���� - 
	BYTE GetInfluenceMask(void)
	{
		if (IS_NORMAL_INFLUENCE_TYPE(InfluenceType))
		{
			if (IS_ANI_CITY_MAP_INDEX(Material))
			{
				return INFLUENCE_TYPE_NORMAL | INFLUENCE_TYPE_ANI;
			}
			return INFLUENCE_TYPE_NORMAL | INFLUENCE_TYPE_VCN;
		}

		return InfluenceType | INFLUENCE_TYPE_NORMAL;
	};
	///////////////////////////////////////////////////////////////////////////////
	/// \fn			
	/// \brief		// 2009-10-12 by cmkwon, ������ī ���� ��� ���� - 
	/// \author		cmkwon
	/// \date		2009-10-12 ~ 2009-10-12
	/// \warning	
	///
	/// \param		
	/// \return		
	///////////////////////////////////////////////////////////////////////////////
	USHORT GetStartCityMapIndex(void)
	{
		switch (InfluenceType)
		{
		case INFLUENCE_TYPE_NORMAL:
		{
			if (IS_ANI_CITY_MAP_INDEX(Material))
			{
				return Material;
			}
			return VCN_CITY_MAP_INDEX;	// 2009-10-12 by cmkwon, �������� ���� ���� �⺻
		}
		case INFLUENCE_TYPE_VCN:				return VCN_CITY_MAP_INDEX;
		case INFLUENCE_TYPE_ANI:				return ANI_CITY_MAP_INDEX;
		}

		return VCN_CITY_MAP_INDEX;		// 2009-10-12 by cmkwon, �⺻��
	}

	///////////////////////////////////////////////////////////////////////////////
	// 2009-11-02 by cmkwon, ĳ��(�κ�/â�� Ȯ��) ������ �߰� ���� - 
	BYTE GetAddedPermanentInventoryCount(BYTE i_enStorage = ITEM_IN_CHARACTER);
	BOOL SetAddedPermanentInventoryCount(BYTE i_byAddCount, BYTE i_enStorage = ITEM_IN_CHARACTER);
};

// ���� Ÿ��: C(ĳ����), M(����), I(�ʵ������), CI(ĳ���Ϳ� ���ӵ� ������)
typedef enum
{
	ERR2ERR	= 0,
	C2C		= 1,
	C2M,
	C2I,
	C2CI,
	C2NULL,			// NULL Target
	M2C,
	M2M,			// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - �߰�
	M2I,
	M2CI,
	M2NULL,			// NULL Target
	NULL2NULL		// 2013-05-09 by hskim, ���� ����Ʈ ����, [�ش��ϴ� ������ �־��ּ���]
} enumAttackToTarget;

///////////////////////////////////////////////////////////////////////////////
// 2009-09-09 ~ 2010-02-10 by dhjin, ���Ǵ�Ƽ - �ߵ�������������
struct INVOKING_WEAR_ITEM_DESTPARAM {
	InvokingDestParamID_t	InvokingDestParamID;
	DestParam_t				InvokingDestParam;
	ParamValue_t			InvokingDestParamValue;
	EffectIdx_t				InvokingEffectIdx;
};
typedef vector<INVOKING_WEAR_ITEM_DESTPARAM>		InvokingWearItemDestParamList;
typedef ez_map<InvokingDestParamID_t, InvokingWearItemDestParamList>	ezmapInvokingDPIdDPList;

struct MEX_ITEM_INFO;

///////////////////////////////////////////////////////////////////////////////
//	ATUM - Item - Parameter Struct ����
///////////////////////////////////////////////////////////////////////////////
struct ITEM
{
	INT			ItemNum;						// ������ ������ȣ, ���� �������� �� (ITEM_BASE*)
	BYTE		Kind;							// ������ ����(�����, ��, ����, ��ų.....), ITEMKIND_XXX
	char		ItemName[SIZE_MAX_ITEM_NAME];	// ������ �̸�
	float		AbilityMin;						// �������ּҼ���
	float		AbilityMax;						// �������ִ뼺��
	USHORT		ReqRace;						// �ʿ�����
	GEAR_STAT	ReqGearStat;					// �ʿ� ��� ����
	USHORT		ReqUnitKind;					// �ʿ���������
	BYTE		ReqMinLevel;					// �ʿ� ���� ����
	BYTE		ReqMaxLevel;					// �ʿ� ���� ����
	BYTE		ReqItemKind;					// �ʿ����������, ITEMKIND_XXX, check: ��ų���� ���, 20040818, kelovon
	USHORT		Weight;							// ����
	float		HitRate;						// ����Ȯ��(0~255)	// 2010-07-19 by dhjin, Ȯ�� ���� ����
	BYTE		Defense;						// ����
	float		FractionResistance;				// 2008-10-06 by dhjin, �Ǿ���� �ϴ� ��� // �Ӽ����׷�(0~255) // 2010-07-19 by dhjin, Ȯ�� ���� ����
	BYTE		NaturalFaction;					// õ���迭, ����(����, ĳ����) Index (õ��)
	BYTE		SpeedPenalty;					// ���ǵ����Ƽ, �̵��ӵ�����ġ�� ����(-:����)
	USHORT		Range;							// ���ݹ���, �������� ��쿡�� �ν��� ���� �� �ӵ�, ��ų�� ��� ���� ����
	BYTE		Position;						// ������ġ
	BYTE		Scarcity;						// ��ͼ�, ���ӻ� ���� Ȯ��, define�ؼ� ���, see below
	float		Endurance;						// ������, ������
	Prob256_t	AbrasionRate;					// ������, �������� �پ��� ������(0~255)
	USHORT		Charging;						// ����������� �ִ� ��ź ��, �������� �ѹ��� ����Ǵ� ����, TANK���� ��
	BYTE		Luck;							// ���
	USHORT		MinTradeQuantity;				// �ּ� �ŷ� ����, Price�� �� ������ ���� �����̴�
	UINT		Price;							// �ּ� �ŷ� ������ ����
	UINT		CashPrice;						// �ּ� �ŷ� ������ ���� ����

// 2009-04-21 by cmkwon, ITEM�� DesParam �ʵ� ���� 8���� �ø��� - �Ʒ��� ���� �迭�� ���� ��.
// 	BYTE		DestParameter1;					// ����Ķ����1
// 	float		ParameterValue1;				// �����Ķ����1
// 	BYTE		DestParameter2;					// ����Ķ����2
// 	float		ParameterValue2;				// �����Ķ����2
// 	BYTE		DestParameter3;					// ����Ķ����3
// 	float		ParameterValue3;				// �����Ķ����3
// 	BYTE		DestParameter4;					// ����Ķ����4
// 	float		ParameterValue4;				// �����Ķ����4
	DestParam_t	ArrDestParameter[SIZE_MAX_DESPARAM_COUNT_IN_ITEM];	// 2011-08-01 by hskim, ��Ʈ�� �ý��� 2�� - �ڷ��� ���� (DestParameter - 255 -> 32767 ����) - // 2009-04-21 by cmkwon, ITEM�� DesParam �ʵ� ���� 8���� �ø��� -
	float		ArrParameterValue[SIZE_MAX_DESPARAM_COUNT_IN_ITEM];	// 2009-04-21 by cmkwon, ITEM�� DesParam �ʵ� ���� 8���� �ø��� - 

	UINT		ReAttacktime;					// �� ���ݽð�(ms)
	INT			Time;							// ���� �ð�(��ų�� ��)
	USHORT		RepeatTime;						// ����������� ���� �Ѿ� ���� ���, �������� ����, �ð��� ��ų������ ���� �ð�, ������ ��ų�� ��� ����
	USHORT		Material;						// ����
	USHORT		ReqMaterial;					// �ʿ��� ���� ��(����,������ �ʿ�)
	float		RangeAngle;						// ��������(0 ~ PI), ȭ��
	BYTE		UpgradeNum;						// ���׷��̵� ��, ���׷��̵��� �Ѱ踦 ��Ÿ��.
	INT			LinkItem;						// ��ũ������, �����۰� ������ ������(�Ѿ�)
	BYTE		MultiTarget;					// ���ÿ� ���� �� �ִ� Ÿ���� ��
	USHORT		ExplosionRange;					// ���߹ݰ�(���� �� �������� ������ ��ġ�� �ݰ�)
	USHORT		ReactionRange;					// �����ݰ�(���� ���� �����ϴ� �ݰ�)
	BYTE		ShotNum;						// ���� ��,	���� �� �߻� ���� ��Ÿ����.
	BYTE		MultiNum;						// ���� �߻� ź ��,	1�� �߻翡 ����� ���ÿ� ��������
	USHORT		AttackTime;						// ���ݽð�, ������ �ϱ� ���� �ʿ��� �ð�
	BYTE		ReqSP;							// SP �Ҹ�(��ų)
	INT			SummonMonster;					// 2006-06-08 by cmkwon, ����ȭ ������ �Ǳ����ڷ� ����Ѵ�.(CASH_ITEMKIND_XXXX)
	INT			NextSkill;						// ���� �ܰ��� ��ų ������ �ѹ�(��ų)
	BYTE		SkillLevel;						// ����
	Prob256_t	SkillHitRate;					// ��ų����Ȯ��(0~255)
	BYTE		SkillType;						// ��ų����(�ð� �� �ߵ� ����), ����|Ŭ��|�ð�|����
	BYTE		SkillTargetType;				// ��ų Ÿ�� Ÿ��, SKILLTARGETTYPE_XXX
	BYTE		Caliber;						// ����(�Ѿ�, ź�� ��)
	BYTE		OrbitType;						// �̻���, ���� ���� ����
	BitFlag64_t	ItemAttribute;					// �������� �Ӽ�, ITEM_ATTR_XXX
	FLOAT		BoosterAngle;					// �ν��ͽÿ� ������ ȸ����, ����� �������� ���
	INT			CameraPattern;					// ī�޶� ����
	INT			SourceIndex;					// 2005-08-22 by cmkwon, ����Ʈ, ������(��/����) ���ҽ� ����Ÿ
	vectINT *	pParamOverlapIdxList;			// 2010-01-18 by cmkwon, ������ ���� Parameter �ߺ� üũ �ý��� ���� - 
	char		Description[SIZE_MAX_ITEM_DESCRIPTION];	// ������ ����
	BYTE		EnchantCheckDestParam;			// 2009-09-09 ~ 2010-02-10 by dhjin, ���Ǵ�Ƽ - �ߵ�������������
	InvokingDestParamID_t	InvokingDestParamID;	// 2009-09-09 ~ 2010-02-10 by dhjin, ���Ǵ�Ƽ - �ߵ�������������
	InvokingDestParamID_t	InvokingDestParamIDByUse;// 2009-09-09 ~ 2010-02-10 by dhjin, ���Ǵ�Ƽ - �ߵ�������������	
	InvokingWearItemDestParamList *	pInvokingDestParamList;			// 2009-09-09 ~ 2010-02-10 by dhjin, ���Ǵ�Ƽ - �ߵ�������������
	InvokingWearItemDestParamList *	pInvokingDestParamByUseList;	// 2009-09-09 ~ 2010-02-10 by dhjin, ���Ǵ�Ƽ - �ߵ�������������	
	BYTE		IsTenderDropItem;				// 2010-04-09 by cmkwon, ����2�� �߰� ����(�ܰ躰 ���� �߰�) - CFieldIOCP::SetTenderItemList#���� ������

	// operator overloading
	ITEM& operator=(const MEX_ITEM_INFO& rhs);

	BOOL IsExistDesParam(DestParam_t desParam)		// 2011-08-01 by hskim, ��Ʈ�� �ý��� 2�� - �ڷ��� ���� (DestParameter - 255 -> 32767 ����)
	{
// 2009-04-21 by cmkwon, ITEM�� DesParam �ʵ� ���� 8���� �ø��� - �Ʒ��� ���� ����
// 		if(desParam == DestParameter1
// 			|| desParam == DestParameter2
// 			|| desParam == DestParameter3
// 			|| desParam == DestParameter4)
// 		{
// 			return TRUE;
// 		}
		// 2009-04-21 by cmkwon, ITEM�� DesParam �ʵ� ���� 8���� �ø��� - 
		int i; for(i=0; i < SIZE_MAX_DESPARAM_COUNT_IN_ITEM; i++)
		{
			if(desParam == ArrDestParameter[i])
			{
				return TRUE;
			}
		}

		return FALSE;
	};
	float GetParameterValue(DestParam_t i_destParam)		// 2011-08-01 by hskim, ��Ʈ�� �ý��� 2�� - �ڷ��� ���� (DestParameter - 255 -> 32767 ����)
	{
// 2009-04-21 by cmkwon, ITEM�� DesParam �ʵ� ���� 8���� �ø��� - �Ʒ��� ���� ������
// 		if(i_destParam == DestParameter1)
// 		{
// 			return ParameterValue1;
// 		}
// 		if(i_destParam == DestParameter2)
// 		{
// 			return ParameterValue2;
// 		}
// 		if(i_destParam == DestParameter3)
// 		{
// 			return ParameterValue3;
// 		}
// 		if(i_destParam == DestParameter4)
// 		{
// 			return ParameterValue4;
// 		}
		// 2009-04-21 by cmkwon, ITEM�� DesParam �ʵ� ���� 8���� �ø��� - 
		int i; for(i=0; i < SIZE_MAX_DESPARAM_COUNT_IN_ITEM; i++)
		{
			if(i_destParam == ArrDestParameter[i])
			{
				return ArrParameterValue[i];
			}
		}
		return 0.0f;
	};

	///////////////////////////////////////////////////////////////////////////////
	// 2009-12-11 by cmkwon, ������ ��׷η� Ÿ���� �����ϴ� ���� ���� - 
	float GetSkillDamageForAggro(void)
	{
		if(FALSE == IS_SKILL_ITEM(Kind))
		{
			return 0.0f;
		}

		return AbilityMax;		
	}

	///////////////////////////////////////////////////////////////////////////////
	// 2010-01-18 by cmkwon, ������ ���� Parameter �ߺ� üũ �ý��� ���� - 
	BOOL CheckParamOverlap(ITEM *i_pUsingItemInfo);
};
typedef vector<ITEM*>			vectItemPtr;		// 2009-08-26 by cmkwon, �׷��� ���ҽ� ���� �ý��� ���� - 


///////////////////////////////////////////////////////////////////////////////
// 2013-03-29 by jhseol, ������ �̺�Ʈ - ����Ÿ�� �߰������� ����
// SUB_EVENT_TYPE_XXX
#define SIZE_MAX_DESPARAM_COUNT_IN_ITEM_EVENT	3
/**************************************************
���� ������ �̺�Ʈ ����ɼ��� �߰��ɶ�, ���������� ���� ī��Ʈ�� ���� �ø��� �ذ��� �ǳ�.
DB ���̺� �� ���ν����� �߰��� ������ �Ͽ� ����(�ݿ�) �ؾ��Ѵ�.
1. atum2_db_account.dbo.td_ItemEventSubType			���̺�
2. atum2_db_[n].dbo.atum_InsertItemEventSubType		���ν���
3. atum2_db_[n].dbo.atum_GetItemEventSubType		���ν���
2013. 4. 23 ����ɼ� ���� ���� ����			- ITEM_EVENT_TYPE_ONLYONE �� ITEM_EVENT_TYPE_ONEDAY �̺�Ʈ ���� Play Time ����ɼ� ���� ����
2013. 4. 23 ����ɼ� �켱���� �������� ���� - �÷���Ÿ���� ���� üũ�ϰ� �Ŀ� �������� ������ Ȯ��
											- �̰��� �����Ϸ��� SetDefaultSubTypePriority() �Լ�ȣ���� ���ϸ� ��
											- �׸��� ���� ������ üũ�ڽ� ��Ʈ�ѷ��� Ȱ��ȭ �ؾ���.
**************************************************/

#define ITEM_EVENT_MASK_CHECK(VAR, MASK)		(((VAR) & (MASK)) != 0)
#define ITEM_EVENT_STEP_PASS_MASK_SUCCESS		0x01	// 1
#define ITEM_EVENT_STEP_PASS_MASK_FAIL			0x10	// 2
#define ITEM_EVENT_DES_EMPTY					0	// 2013-03-29 by jhseol, ������ �̺�Ʈ
#define ITEM_EVENT_DES_PLAY_TIME				1	// 2013-03-29 by jhseol, ������ �̺�Ʈ - �÷��� �ð��� ��������
#define ITEM_EVENT_DES_PLAY_REQUIRED_ITEM		2	// 2013-03-29 by jhseol, ������ �̺�Ʈ - Ư�������� ������ ���� ����
#define ITEM_EVENT_DES_PLAY_REQUIRED_COUNT		3	// 2013-03-29 by jhseol, ������ �̺�Ʈ - Ư�������� ������ ���� ����
// 2013-03-29 by jhseol, ������ �̺�Ʈ - ����Ÿ�� �߰������� ����

// 2014-02-10 by jhseol&bckim, ü�θ�
struct SCHANNELING_SERVER_INFO
{
	int		nChannelingSeverUID;
	char	cChannelingServerToken;
	char	ChannelingServerName[20];
};
typedef	vector<SCHANNELING_SERVER_INFO*>		vectChannelingServerInfo;
// End. 2014-02-10 by jhseol&bckim, ü�θ�

// 2006-08-24 by dhjin, �̺�Ʈ ������ ����
struct SITEM_EVENT_INFO
{
	int				ItemEventUID;
	int				ItemEventType;		// ITEM_EVENT_TYPE_XXX
	// 2013-03-29 by jhseol, ������ �̺�Ʈ - ����Ÿ�� �߰������� ����
	BOOL			SubEventType;
	DestParam_t		ArrDestParameter[SIZE_MAX_DESPARAM_COUNT_IN_ITEM_EVENT];
	INT				ArrParameterValue[SIZE_MAX_DESPARAM_COUNT_IN_ITEM_EVENT];
	// end 2013-03-29 by jhseol, ������ �̺�Ʈ - ����Ÿ�� �߰������� ����
	int				OnlyPCBang;
	int				ChannelingType;			// 2014-02-10 by jhseol&bckim, ü�θ�		
	BYTE			byInfluenceType;
	int				ItemNum;
	int				Count;
	ATUM_DATE_TIME  StartTime;
	ATUM_DATE_TIME	EndTime;
	BOOL			MemberShip;			// 2006-09-29 by dhjin, �ɹ��� ������ ����
	BYTE			ReqLevel;			// 2007-07-20 by dhjin, ITEM_EVENT_TYPE_NEWMEMBER_LEVELUP �߰��� ���� �ʵ� �߰�
	BOOL			NewMember;			// 2007-07-23 by dhjin, �̺�Ʈ �Ⱓ�ȿ� ������ �������Ը� ����
	INT				UnitKind;			// 2007-07-24 by dhjin, ���� ��� ����
	INT				PrefixCodeNum;		// 2007-07-25 by dhjin, ������ ���� �ɼ�
	INT				SuffixCodeNum;		// 2007-07-25 by dhjin, ������ ���� �ɼ�
	BOOL			UseLastGameEndDate;	// 2008-02-01 by cmkwon, ItemEvent �� LastGameEndDate üũ ��ƾ �߰� - SITEM_EVENT_INFO �� �ʵ� �߰�
	ATUM_DATE_TIME  atLastGameEndDate;	// 2008-02-01 by cmkwon, ItemEvent �� LastGameEndDate üũ ��ƾ �߰� - SITEM_EVENT_INFO �� �ʵ� �߰�
	INT				CheckWithCharacterUID;	// 0 =  Account UID , 1 = ĳ���� UID , 2 = CI�� üũ. // 2014-03-12 by jekim, �ֹι�ȣ�� ������ ����
	INT				iLevelMin;
	INT				iLevelMax;
	INT				LoginCheckNumber;		// 2011-08-25 by shcho, Ƚ���� ������ ���ޱ�� ���� - 0�ΰ�� ���������� ó��. 2���� ���, �Ϸ翡 �ѹ� ���ѱ��� 2�� �����ؾ� ����
	BOOL			UseFixedPeriod;			// 2013-02-28 by bckim, �������� �����߰�
	INT				FixedPeriod_DAY;		// 2013-02-28 by bckim, �������� �����߰�
	ATUM_DATE_TIME  GiveItemAtTime;			// 2013-09-30 by bckim, Ư���ð� ���������� 

	// 2013-03-29 by jhseol, ������ �̺�Ʈ - ����Ÿ�� �߰������� ����
	char* GetDestParameterStr(DestParam_t i_DestParam)
	{
		switch(i_DestParam)
		{
		case ITEM_EVENT_DES_EMPTY:					return "ITEM_EVENT_DES_EMPTY";
		case ITEM_EVENT_DES_PLAY_TIME:				return "ITEM_EVENT_DES_PLAY_TIME";
		case ITEM_EVENT_DES_PLAY_REQUIRED_ITEM:		return "ITEM_EVENT_DES_PLAY_REQUIRED_ITEM";
		case ITEM_EVENT_DES_PLAY_REQUIRED_COUNT:	return "ITEM_EVENT_DES_PLAY_REQUIRED_COUNT";
		}
		return "ITEM_EVENT_DES_UNKNOWN";
	}

	char* GetDestParameterShotStr(DestParam_t i_DestParam)
	{
		switch(i_DestParam)
		{
		case ITEM_EVENT_DES_EMPTY:					return "Empty";
		case ITEM_EVENT_DES_PLAY_TIME:				return "PlayTime";
		case ITEM_EVENT_DES_PLAY_REQUIRED_ITEM:		return "ReqItem";
		case ITEM_EVENT_DES_PLAY_REQUIRED_COUNT:	return "ReqCount";
		}
		return "ITEM_EVENT_DES_UNKNOWN";
	}
	// end 2013-03-29 by jhseol, ������ �̺�Ʈ - ����Ÿ�� �߰������� ����
};

// 2014-03-12 by jekim, �ֹι�ȣ�� ������ ����
#define ITEM_EVENT_CHECKWITH_ACCOUNT_UID 0
#define ITEM_EVENT_CHECKWITH_CHARACTER_UID 1
#define ITEM_EVENT_CHECKWITH_ACCOUNTEXT_UID 2 // CI�� üũ
// end 2014-03-12 by jekim, �ֹι�ȣ�� ������ ����


typedef	vector<SITEM_EVENT_INFO>	vectItemEventInfo;
// ITEM_EVENT_TYPE_XXX
#define ITEM_EVENT_TYPE_ONLYONE					1
#define ITEM_EVENT_TYPE_ONEDAY					2
#define ITEM_EVENT_TYPE_INFLCHANGE				3
#define ITEM_EVENT_TYPE_LEVELUP					4
#define ITEM_EVENT_TYPE_COUPON_ONLYONE			5	// 2008-01-10 by cmkwon, ������ �̺�Ʈ �ý��ۿ� �� ���� �ý��� �߰� - �Ѱ����� �ѹ��� ������ ���� �̺�Ʈ
#define ITEM_EVENT_TYPE_COUPON_ONEDAY			6	// 2008-01-10 by cmkwon, ������ �̺�Ʈ �ý��ۿ� �� ���� �ý��� �߰� - �Ѱ����� �Ϸ翡 �ѹ� ������ ���� �̺�Ʈ
#define ITEM_EVENT_TYPE_LOGIN					7	// 2011-08-25 by shcho, Ƚ���� ������ ���ޱ�� ����
#define ITEM_EVENT_TYPE_FIRST_PURCHASE			8	// 2013-03-29 by jhseol, ������ �̺�Ʈ - �ſ� ù ����� ��������
#define ITEM_EVENT_TYPE_AT_TIME					9	// 2013-09-30 by bckim, Ư���ð� ���������� 

struct MAP_AREA {
	INT		MapIndex;
	INT		X;
	INT		Y;
	INT		Radius;

	BOOL IsPositionInArea(INT i_nMapIndex, INT i_nX, INT i_nY)
	{
		// map Ȯ��
		if (MapIndex == 0) {							return TRUE; }
		if (MapIndex != i_nMapIndex) {					return FALSE; }

		// �Ÿ� Ȯ��
		if (X == -1 || Y == -1 || Radius == -1){		return TRUE; }
		if ((INT)LENGTH(X-i_nX, Y-i_nY) <= Radius)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}

		return TRUE;
	}

	void Reset() { MapIndex = 0; X = 0; Y = 0; Radius = 0; }
};

typedef struct
{
	ITEM		*pItemInfo;
	DWORD		dwUsingPercent;
	BYTE		byArrayIndex;
	BYTE		byBodyConArrayIndex;		// 2006-12-15 by cmkwon, DB�� ���� - ����Ʈ �ٵ�����ǰ� ���� �ִ�
} MONSTER_ITEM;

// start 2011-03-21 by hskim, ���Ǵ�Ƽ 3�� - ���� ��Ƽ Ÿ���� ��� �߰�
typedef struct 
{
	D3DXVECTOR3		Position;
} MONSTER_TARGET;
// end 2011-03-21 by hskim, ���Ǵ�Ƽ 3�� - ���� ��Ƽ Ÿ���� ��� �߰�


// 2013-08-28 by bckim, �������� ����ȭ
struct BOSS_MONSTER_REWARD
{	
	float			fMinDamege;	
	INT				nMaxPerson;	
	INT				nTime;		
	INT				ItemNum;

	BOSS_MONSTER_REWARD()
	{
		memset(this, 0x00, sizeof(BOSS_MONSTER_REWARD));
	}
};
// End. 2013-08-28 by bckim, �������� ����ȭ

struct ITEM_W_COUNT {
	INT		ItemNum;
	INT		Count;

	void Reset() { ItemNum = 0; Count = 0; }
};

struct ITEM_W_COUNT_CHECK
{
	BOOL	bChecked;		// 2006-08-28 by cmkwon
	INT		ItemNum;
	INT		Count;

	void Reset(void) { bChecked = FALSE; ItemNum = 0; Count = 0; }
};

struct MONSTER_W_COUNT	// 2005-10-19 by cmkwon
{
	INT		MonsterUniqueNumber;
	INT		Count;
	MAP_AREA		MapArea;			// 2007-03-14 by cmkwon, ���� ��ġ ��ǥ�� �̴ϸʿ� �����ֱ� ����

	void Reset() { MonsterUniqueNumber = 0; Count = 0; }
};
typedef vector<MONSTER_W_COUNT>			vectMONSTER_W_COUNT;

struct ITEM_W_COUNT_PROB {
	INT			ItemNum;
	INT			Count;
	Prob100_t	Prob100;		// Ȯ��

	void Reset() { ItemNum = 0; Count = 0; Prob100 = 0; }
};

struct ITEM_UNIQUE_NUMBER_W_COUNT {
	UID64_t	ItemUniqueNumber;
	INT		Count;

	void Reset() { ItemUniqueNumber = 0; Count = 0; }
};

struct ItemID_t
{
	UID64_t	ItemUID;
	INT		ItemNum;

	ItemID_t() {}
	ItemID_t(UID64_t i_ItemUID, INT i_ItemNum)
	{
		ItemUID = i_ItemUID;
		ItemNum = i_ItemNum;
	}
};

typedef mt_vector<ItemID_t>		mtvectorItemID;		// 2013-05-09 by hskim, ���� ����Ʈ ����

struct ITEM_UID_W_ITEMNUM_COUNT			// 2008-09-26 by cmkwon, ���ս� GameLog ���� - ���� �߰� ��
{
	UID64_t		ItemUID;
	INT			ItemNum;
	INT			Count;
};


///////////////////////////////////////////////////////////////////////////////
//	ATUM - Monster - Parameter Struct ����
///////////////////////////////////////////////////////////////////////////////
//#define ARRAY_SIZE_MONSTER_SECONDARY_ITEM			5
#define ARRAY_SIZE_MONSTER_ITEM						16			// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - 10�� �߰� 6 -> 16
#define ARRAY_SIZE_MONSTER_TARGET					10			// 2011-03-21 by hskim, ���Ǵ�Ƽ 3�� - ���� ��Ƽ Ÿ���� ��� �߰� - 10���� ����
#define ARRAY_INDEX_MONSTER_SKILL_ITEM				15			// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - 10�� �߰� 5 -> 15
#define ARRAY_SIZE_MONSTER_SKILL_ITEM				10			// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� �������� ������������� ����ϰ� �߰��� 10�� �������� ��ų���������� ����Ѵ�.
#define SIZE_MAX_FILE_NAME			50	// 2010-03-31 by dhjin, ���Ǵ�Ƽ(�������) - 
struct MONSTER_INFO
{
//	ClientIndex_t	MonsterIndex;					// �ε���
//	SHORT			CurrentHP;						// ���� ������
//	BodyCond_t		BodyCondition;					// ĳ���� BodyCondition
//	ITEM			*ItemInfoPrimary;				// Primary ���� Item, DB���� ���� ���� ItemNum�� �Ҵ��ϰ�, �� ���Ŀ� pointer�� �Ҵ���, by kelovon
//	ITEM			*ItemInfoSecondary[ARRAY_SIZE_MONSTER_SECONDARY_ITEM];			// Secondary ���� Item
//	D3DXVECTOR3		PositionVector;					// ĳ���� ��ǥ
//	D3DXVECTOR3		TargetVector;					//
//	D3DXVECTOR3		UpVector;						//
	INT				MonsterUnitKind;				// ���� ������ȣ
	char			MonsterName[SIZE_MAX_MONSTER_NAME];	// ���� �̸�
	BYTE			Level;							// ������ Level
	INT				MonsterHP;						// ����
	USHORT			Race;							// ����
	float			Defense;						// ����, 0 ~ 255		// 2010-07-19 by dhjin, Ȯ�� ���� ����, // 2009-12-17 by cmkwon, ������ ���� ������ �ʵ�(����,ȸ��,�Ǿ,Ȯ��)�� 255�̻� ���� ���� �����ϰ� ���� - �����ڷ���(BYTE)
	float			DefenseProbability;				// ����Ȯ��, 20030630, �߰��� // 2010-07-19 by dhjin, Ȯ�� ���� ����
	BYTE			Speed;							// �̵��ӵ�
	MONSTER_ITEM	ItemInfo[ARRAY_SIZE_MONSTER_ITEM];	// ���Ͱ� ������ �ִ� ��� ������
	USHORT			Size;							// �ʵ� ������ SizeForClient�� loading,  NPC ������ SizeForServer�� loading
	BYTE			Faction;						// �迭
	SHORT			MonsterForm;					// Monster ����
	BYTE			AttackPattern;					//
	SHORT			MovePattern;					//
	BYTE			Belligerence;					// ȣ����
	BYTE			AttackObject;					// ATTACKOBJ_XXX
	SHORT			AttackRange;					// ���ݼ��� ������ ���Ͱ� Ÿ���ð����� �Ÿ�
	LONGLONG		Experience;						// ���Ľ� �ִ� ����ġ
	BYTE			AlphaBlending;					// alpha blending ����, TRUE(1), FALSE(0), client�� ����� ���� �߰�, 20030616
	USHORT			HPRecoveryTime;					// HP ���� �ð�
	SHORT			HPRecoveryValue;				// �ѹ��� ���� HP�� ��
	USHORT			RenderIndex;
	float			ScaleValue;
	BYTE			TextureIndex;
	UINT			SourceIndex;
	BYTE			QuickTurnAngle;					// �ִ밢 ����
	BYTE			QuickSpeed;						// ������ �̵��� �ӵ�
	USHORT			QuickTurnTerm;					// ������ �̵��ϴ� Term
	BitFlag64_t		MPOption;						// 2010-01-11 by cmkwon, ���� MPOption 64bit�� ���� - ����(BYTE), MPOPTION_BIT_XXX
	BYTE			MPOptionParam1;
	BYTE			MPOptionParam2;
	USHORT			Range;
	FLOAT			TurnAngle;
	BYTE			MonsterHabit;					// ����, ex) �߰� ���ݷ� ���� ��
	BYTE			ClickEvent;						// 2007-09-05 by dhjin, ���� Ŭ�� �̺�Ʈ
	HPActionIdx_t	HPActionIdx;					// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - HP �ൿ
	MonIdx_t		MonsterTarget;					// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���� ���� ��� ��ȣ
	ChangeTarget_t	ChangeTarget;					// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���� ���� ��� Ÿ�ٰ� ���� ����
	MonIdx_t		MonsterTarget2;					// 2010-03-31 by dhjin, ���Ǵ�Ƽ(�������) - ���� ���� ���� ��� ��ȣ 2��° �켱 ����
	char			PortraitFileName[SIZE_MAX_FILE_NAME];	// 2010-03-31 by dhjin, ���Ǵ�Ƽ(�������) - ���� �ʻ�ȭ ����
	INT				ChangeTargetTime;				// 2010-04-14 by cmkwon, ����2�� ���� ���� Ÿ�� ���� ó�� - 
	MONSTER_TARGET	MultiTargetInfo[ARRAY_SIZE_MONSTER_TARGET];				// 2011-03-21 by hskim, ���Ǵ�Ƽ 3�� - ���� ��Ƽ Ÿ���� ��� �߰�
																			// ���� ���� => �ε����� ���������δ� 0���� ����
																			// ������� �ε����� 1���� ����, 0�� ��Ƽ Ÿ���� ���� ���� �ǹ�
	INT				WayPointPattern;				// 2011-05-23 by hskim, ���Ǵ�Ƽ 3�� - ��������Ʈ ���� - WayPointPattern �ʵ� �߰�

	// 2013-08-28 by bckim, �������� ����ȭ
	BOSS_MONSTER_REWARD	MonsterRewardInfo;
	DWORD				m_dwBossRewardStrartTick;
	// End. 2013-08-28 by bckim, �������� ����ȭ
};


// 2010. 05. 19 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����. (��ȣó�� + ���� ó��(����) )
//////////////////////////////////////////////////////////////////////////////////////////////////

// 2010-05-24 by shcho, ���Ǵ�Ƽ ���̵� ���� -
struct INFINITY_DIFFICULTY_BONUS_INFO
{
	int iIncreaseStep; //���̵� �ܰ�
	int iExp; //����ġ Ȯ��
	int iDrop_Item_Persent;//��� ������ Ȯ��
	int iItem_EA_persent;//������ ���� Ȯ��
};
typedef vector<INFINITY_DIFFICULTY_BONUS_INFO>	vectorInfinity_DifficultyInfo_Bonus; //���̵� ����Ʈ ����

// 2010-05-24 by shcho, ���Ǵ�Ƽ ���̵� ���� -
struct INFINITY_DIFFICULTY_MONSTER_SETTING_INFO
{
	int iIncreaseStep; //���̵� �ܰ�
	int iMonsterHP; //���� �� HP
	int iMonsterDefense;//���� �� ����
	int iMonsterEvasion;//���� �� ȸ�Ƿ�
	int iMonsterAttackItem;//���� �� ���� ������ ������ & ��ų ���ӽð�
	int iMonsterPopulation;//���� �� ���� ��ü�� 
};
typedef vector<INFINITY_DIFFICULTY_MONSTER_SETTING_INFO>	vectorInfinity_DifficultyInfo_Monster; //���̵� ���� ���� ����Ʈ ����

struct MONSTER_BALANCE_DATA						// ���� �뷱�� Ȯ�� ����.
{
	MONSTER_BALANCE_DATA( const INT a_Step = 0 )
	{

		this->DifficultyStep = a_Step;

		this->fMaxHPRatio = 1.0f;
		this->fDefenseRatio = 1.0f;
		this->fDefenseProbabilityRatio = 1.0f;
		this->fAtkMsgRatio = 1.0f;
		this->fIncreaseExpRatio = 1.0f;
		this->fIncreaseDropItemProbabilityRatio = 1.0f;
		this->fIncreaseDropItemCountRatio = 1.0f;
		this->fSummonCountRatio = 1.0f;
	}

	void Reset ( void )
	{
		memset ( this , 0x00 , sizeof( MONSTER_BALANCE_DATA ) );
	}

	void Init ( const INT a_Step )
	{
		this->DifficultyStep = a_Step;
		
		this->fMaxHPRatio = 1.0f;
		this->fDefenseRatio = 1.0f;
		this->fDefenseProbabilityRatio = 1.0f;
		this->fAtkMsgRatio = 1.0f;
		this->fIncreaseExpRatio = 1.0f;
		this->fIncreaseDropItemProbabilityRatio = 1.0f;
		this->fIncreaseDropItemCountRatio = 1.0f;
		this->fSummonCountRatio = 1.0f;
	}

	void operator= ( const MONSTER_BALANCE_DATA &a_MonsterBalanceData )
	{
		memcpy ( this , &a_MonsterBalanceData , sizeof ( MONSTER_BALANCE_DATA ) );
	}

	void operator= ( const INFINITY_DIFFICULTY_BONUS_INFO &a_Infinity_BonusInfo )
	{
		if ( this->DifficultyStep != a_Infinity_BonusInfo.iIncreaseStep )
			return;

		this->fIncreaseExpRatio = (float)a_Infinity_BonusInfo.iExp * 0.01f;
		this->fIncreaseDropItemProbabilityRatio = (float)a_Infinity_BonusInfo.iDrop_Item_Persent * 0.01f;
		this->fIncreaseDropItemCountRatio = (float)a_Infinity_BonusInfo.iItem_EA_persent * 0.01f;
	}

	void operator = ( const INFINITY_DIFFICULTY_MONSTER_SETTING_INFO &a_Infinity_MonsterInfo ) 
	{
		if ( this->DifficultyStep != a_Infinity_MonsterInfo.iIncreaseStep )
			return;
		
		this->fMaxHPRatio = (float)a_Infinity_MonsterInfo.iMonsterHP * 0.01f;
		this->fDefenseRatio = (float)a_Infinity_MonsterInfo.iMonsterDefense * 0.01f;
		this->fDefenseProbabilityRatio = (float)a_Infinity_MonsterInfo.iMonsterEvasion * 0.01f;
		this->fAtkMsgRatio = (float)a_Infinity_MonsterInfo.iMonsterAttackItem * 0.01f;
		this->fSummonCountRatio = (float)a_Infinity_MonsterInfo.iMonsterPopulation * 0.01f;
	}

	void operator += ( const INFINITY_DIFFICULTY_BONUS_INFO &a_Infinity_BonusInfo )
	{
		if ( this->DifficultyStep != a_Infinity_BonusInfo.iIncreaseStep )
			return;

		this->fIncreaseExpRatio += (float)a_Infinity_BonusInfo.iExp * 0.01f;
		this->fIncreaseDropItemProbabilityRatio += (float)a_Infinity_BonusInfo.iDrop_Item_Persent * 0.01f;
		this->fIncreaseDropItemCountRatio += (float)a_Infinity_BonusInfo.iItem_EA_persent * 0.01f;
	}

	void operator += ( const INFINITY_DIFFICULTY_MONSTER_SETTING_INFO &a_Infinity_MonsterInfo ) 
	{
		if ( this->DifficultyStep != a_Infinity_MonsterInfo.iIncreaseStep )
			return;
		
		this->fMaxHPRatio += (float)a_Infinity_MonsterInfo.iMonsterHP * 0.01f;
		this->fDefenseRatio += (float)a_Infinity_MonsterInfo.iMonsterDefense * 0.01f;
		this->fDefenseProbabilityRatio += (float)a_Infinity_MonsterInfo.iMonsterEvasion * 0.01f;
		this->fAtkMsgRatio += (float)a_Infinity_MonsterInfo.iMonsterAttackItem * 0.01f;
		this->fSummonCountRatio += (float)a_Infinity_MonsterInfo.iMonsterPopulation * 0.01f;
	}

	// 2010. 07. 05 by hsLee. ���� ��ȯ ����. (�뷱�� ������ ���� ����.) - MaxHp�� 0���ϰ� �ɼ� ����.
	const bool IsValidData ( void ) const
	{
		return ( fMaxHPRatio > .0f );
	}

	INT		DifficultyStep;

	float	fMaxHPRatio;							// ���� HP ������.
	float	fDefenseRatio;							// ���� ���� ������.
	float	fDefenseProbabilityRatio;				// ���� ����(ȸ��) ������.
	float	fAtkMsgRatio;							// ���� ���·� ������.
	float	fSummonCountRatio;						// ���� ��ȯ ������.
	
	float	fIncreaseExpRatio;						// ���� óġ ����ġ ȹ�� ������.
	float	fIncreaseDropItemProbabilityRatio;		// ���� óġ ������ ������� ������.
	float	fIncreaseDropItemCountRatio;			// ���� óġ ������ ��� ���� ������.

};
// End 2010. 05. 19 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����. (��ȣó�� + ���� ó��(����) )

// 2010. 05. 19 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����. (��ȣó�� + ���� ó��(����) )
struct MONSTER_INFO_EXTEND
{

	float			fMaxHP;								// ���� �ִ� HP.
	float			Defense;							// ���� ����.	// 2010-07-19 by dhjin, Ȯ�� ���� ����
	float			DefenseProbability;					// ���� �����.	// 2010-07-19 by dhjin, Ȯ�� ���� ����
	float			fAtkDmgRatio;						// ���� ���ݷ� ������.

	float			fIncreaseExpRatio;					// ���� óġ�� ȹ�� ����ġ ������.
	float			fIncreaseDropProbabilityRatio;		// ���� óġ�� ������ ���Ȯ���� ������.
	float			fIncreaseDropItemCountRatio;		// ���� óġ�� ������ ��� ���� ������.
};
// End. 2010. 05. 19 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����. (��ȣó�� + ���� ó��(����) )


class MONSTER
{
public:
	MONSTER_INFO *		MonsterInfoPtr;					// ���� ���� ������
	ClientIndex_t		MonsterIndex;					// �ε���
	float				CurrentHP;						// ���� ������
	D3DXVECTOR3			PositionVector;					// ĳ���� ��ǥ
	D3DXVECTOR3			TargetVector;					//
	D3DXVECTOR3			UpVector;						//
	BodyCond_t			BodyCondition;					// ĳ���� BodyCondition

// 2010. 05. 19 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����. (��ȣó�� + ���� ó��(����) )
	MONSTER_INFO_EXTEND	MonsterInfoExtend;				// ���� Ȯ�� ����. 
	MONSTER_BALANCE_DATA MonsterInfoBalance;			// ���� �뷱�� ����.
// End 2010. 05. 19 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����. (��ȣó�� + ���� ó��(����) )

protected:
	MONSTER(){};
};


///////////////////////////////////////////////////////////////////////////////
// 2009-12-23 by cmkwon, �浹 üũ�� ������ �浹 ������ ���� �ʴ� ������Ʈ ���� - COLLISION_TYPE_XXX
#define COLLISION_TYPE_NONE					0
#define COLLISION_TYPE_NORMAL				1
#define COLLISION_TYPE_NO_DAMAGE			2

typedef struct _MAPOBJECTINFO
{
	_MAPOBJECTINFO()
	{
		Code				= 0;
		Alpha				= 0;
		Collision			= 0;
		CollisionForServer	= 0;
		ObjectRenderType	= 0;
		RenderIndex			= 0;
	}
	INT		Code;						// Object Type
	BYTE	Alpha;						//
	BYTE	Collision;					// �浹 ó�� �÷���, // 2009-12-23 by cmkwon, �浹 üũ�� ������ �浹 ������ ���� �ʴ� ������Ʈ ���� - COLLISION_TYPE_XXX
	BYTE	CollisionForServer;
	BYTE	ObjectRenderType;
	USHORT	RenderIndex;

	// 2009-12-23 by cmkwon, �浹 üũ�� ������ �浹 ������ ���� �ʴ� ������Ʈ ���� - 
	BOOL IsCheckDamage(void)
	{
		if(FALSE == Collision
			|| COLLISION_TYPE_NO_DAMAGE == Collision)
		{
			return FALSE;
		}
		
		return TRUE;
	}
} MAPOBJECTINFO;

/*
typedef struct _MAPOBJECTINFO
{
	INT		Code;						// Object Type
	BOOL	Alpha;						//
	USHORT	RadiusForServer;			// Ojbect ������, ������
	USHORT	RadiusForClient;			// Ojbect ������, Ŭ���̾�Ʈ��
	BOOL	Collision;					// �浹 ó�� �÷���
	BOOL	CollisionForServer;
	USHORT	RenderIndex;
	char	ObjectName[SIZE_MAX_OBJECT_NAME];
	BYTE	ObjectRenderType;
} MAPOBJECTINFO;
*/

// ��ų����(�ð� �� �ߵ� ����)
#define SKILLTYPE_PERMANENT		0	// ������
#define SKILLTYPE_CLICK			1	// Ŭ����
#define SKILLTYPE_TIMELIMIT		2	// �ð���
#define SKILLTYPE_TOGGLE		3	// �����
#define SKILLTYPE_CHARGING		4	// ��¡��, ��ų ��� ���� �ٷ� ������ ����(�߻� ��)���� 1ȸ ����Ǵ� ��ų

// ��ų Ÿ�� Ÿ��, SKILLTARGETTYPE_XXX
#define SKILLTARGETTYPE_ME								0	// �ڱ� �ڽ�
#define SKILLTARGETTYPE_ONE								1	// �ϳ��� Ÿ��
#define SKILLTARGETTYPE_PARTY_WITH_ME					2	// ������ ��Ƽ��, �ڽ� ����
#define SKILLTARGETTYPE_INRANGE_WITH_ME					3	// ����, �ڽ� ����
#define SKILLTARGETTYPE_PARTY_WITHOUT_ME				4	// ������ ��Ƽ��, �ڽ� ���� �� ��
#define SKILLTARGETTYPE_INRANGE_WITHOUT_ME				5	// ����, �ڽ� ���� �� ��
#define SKILLTARGETTYPE_ONE_OURS_INRANGE_WITHOUT_ME		6	// 2010-03-31 by dhjin, ���Ǵ�Ƽ(�������) - ��Ÿ� �ȿ� �ڽ��� ������ �ϳ��� �Ʊ�
#define SKILLTARGETTYPE_ALL_OURS_INRANGE_WITHOUT_ME		7	// 2010-03-31 by dhjin, ���Ǵ�Ƽ(�������) - ��Ÿ� �ȿ� �ڽ��� ������ ��� �Ʊ�
#define SKILLTARGETTYPE_ONE_ENEMY_INRANGE				8	// 2010-03-31 by dhjin, ���Ǵ�Ƽ(�������) - ��Ÿ� �ȿ� �ϳ��� ��
#define SKILLTARGETTYPE_MUTI_ENEMY_INRANGE				9	// 2010-03-31 by dhjin, ���Ǵ�Ƽ(�������) - ��Ÿ� �ȿ� ��Ƽ Ÿ�� �� ��ŭ�� ��
#define SKILLTARGETTYPE_ONE_EXCLUDE_ME					11	// �ϳ��� Ÿ��, �ڽ��� ����
#define SKILLTARGETTYPE_PARTY_ONE						21	// �ƹ��� �ϳ��� ��Ƽ��, // 2005-12-05 by cmkwon
#define SKILLTARGETTYPE_PARTY_ONE_EXCLUDE_ME			22	// �ڽ��� ������ �ϳ��� ��Ƽ��, // 2005-12-05 by cmkwon
#define SKILLTARGETTYPE_ALL_ENEMY						23	// 2006-11-17 by dhjin, �ڽ��� �߽����� �� ����(Ÿ����, ����, 1:1, ������, ������)
#define SKILLTARGETTYPE_ONE_EXCEPT_OURS					24	// 2006-11-17 by dhjin, �ϳ��� Ÿ��, �Ʊ��� ����
#define SKILLTARGETTYPE_ALL_OURS						25  // 2007-02-06 by dhjin, �ڽ��� �߽����� �� �Ʊ���



// ȸ�͵�(Scarcity) ����
#define SCARCITY_100000			0	// Ȯ�� 0~99999
#define SCARCITY_1000000		1	// Ȯ�� 0~999999
#define SCARCITY_10000000		2	// Ȯ�� 0~9999999

// �������� �Ӽ�, ITEM_ATTR_XXX
#define ITEM_ATTR_AUTO_PICK_UP			0x00000001		// 1, ���Ͱ� ������ �ڵ����� �Ա�(�ٴڿ� �� ������)
#define ITEM_ATTR_NO_TRANSFER			0x00000002		// 2, â�� �̵�, ������, �������� ����, ������ �Ǹ�, ������ �ŷ� �Ұ�
#define ITEM_ATTR_QUEST_ITEM			0x00000004		// 4, ����Ʈ ������, ������ ���� �������� �ʰ�, ����Ʈ �������̸� ���ǿ� ������ ���� ������, check: deprecated, ITEMKIND_QUEST�� ���, 20040714, kelovon
#define ITEM_ATTR_TIME_LIMITE			0x00000008		// 8, �ð� ���� ������, ������ ���� ��� �ð� ������ �ִ�
#define ITEM_ATTR_KILL_MARK_ITEM		0x00000010		// 16, ������ ų��ũ ������(â���̵�/������/�������Ǹ� ����, �������ŷ�/������������ �Ұ�), 2006-02-09 by cmkwon
#define ITEM_ATTR_SKILL_SUPPORT_ITEM	0x00000020		// 32, ��ų ���� ������, 2006-09-29 by cmkwon �߰� ��
#define ITEM_ATTR_DELETED_TIME_LIMITE	0x00000040		// 64, �������� ���� �� ��ȿ �ð�(ti_item.Endurance)�� ����ϸ� �ڵ����� �����Ǵ� ������, 2006-09-29 by cmkwon
#define ITEM_ATTR_ACCOUNT_POSSESSION	0x00000080		// 128, ��������������(����â���̵�/������/�������Ǹ�/������������ ����, �������ŷ�/����â���̵� �Ұ�), // 2007-09-17 by cmkwon, ���� ĳ������ ĳ�������� �ŷ� �Ұ� ��� �߰� - 

#define ITEM_ATTR_ARENA_ITEM					0x00000100		// 256, �Ʒ��������� ��� ������ ������, 2007-06-01 by dhjin
#define ITEM_ATTR_SUPER_GAMBLE_ITEM				0x00000200		// 512, // 2007-11-07 by cmkwon, ����/���� �ٴ� �ý��� ���� - ���۰������۰��� �ɼ��� ���� ����ī�������
#define	ITEM_ATTR_PACKAGE_ITEM					0x00000400		// 1024, // 2008-08-26 by cmkwon, ItemAttribute �߰� - ��Ű��(Package) ������, ����� �̽��׸�ĸ���� �����
#define	ITEM_ATTR_FOR_ONLY_GAME_MASTER			0x00000800		// 2048, // 2008-08-26 by cmkwon, ItemAttribute �߰� - GM�� ������, RACE_GAMEMASTER �� ��� ������ ������

#define ITEM_ATTR_UNIQUE_ITEM					0x00001000		// 4096, ����ũ ������, ��æƮ/���� �Ұ�, 2005-11-21 by cmkwon
#define ITEM_ATTR_BAZAAR_ITEM					0x00002000		// 8192, 2006-07-26 by cmkwon, ���λ����� ����/�Ǹ� ���� ������
#define ITEM_ATTR_LEGEND_ITEM					0x00004000		// 16384, // 2007-08-22 by cmkwon, ������ ������, �⺻�� ����ũ������ �Ӽ��̸� ���ս� Ÿ�� �������� ������ �̸� ��æƮ�� �����ȴ�
#define ITEM_ATTR_FORBID_ARENA_COPY_ITEM		0x00008000		// 32768, // 2008-01-07 by dhjin, �Ʒ��� ���� - atum2_db_n => atum2_db_arena �� td_store�� �����ϸ� �ȵǴ� ������

#define ITEM_ATTR_CASH_ITEM						0x00010000		// 65536, ����ȭ ������
#define ITEM_ATTR_CASH_ITEM_PREMIUM_CARD		0x00020000		// 131072, // 2008-08-26 by cmkwon, ItemAttribute �߰� - �����(�����̾�) ������,  

#define ITEM_ATTR_LUCKY_ITEM					0x00040000		// 262144, // 2008-11-04 by dhjin, ��Ű�ӽ�
#define ITEM_ATTR_DELETED_TIME_LIMITE_AFTER_USED	0x00080000		// 524288, // 2008-11-26 by cmkwon, ��� �� �ð�(����ð�) ���� ������ ���� - �߰� ��

#define ITEM_ATTR_MISSION_MASTER				0x00100000		// 1048576, // 2008-12-15 by dhjin, �̼Ǹ�����
#define ITEM_ATTR_ROBOT_ARMOR					0x00200000		// 2097152, // 2009-07-07 by cmkwon, �κ� �Ƹ� ���� ó�� �߰� - �κ��Ƹ� ������ �Ӽ� �߰�

#define ITEM_ATTR_CANNOT_USE_INFINITY			0x00400000		// 4194304, // 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���Ǵ�Ƽ���� ��� �Ұ� ������
#define ITEM_ATTR_ONLY_USE_INFINITY				0x00800000		// 8388608, // 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���Ǵ�Ƽ������ ��� ���� ������
#define ITEM_ATTR_CHECK_SKILL_RESISTANCE_STATE	0x01000000		// 16777216, // 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���������� ŰƮ ���� ���θ� üũ�ؾߵǴ� ������

#define ITEM_ATTR_NOT_STORE_SAVE				0x02000000		// 33554432, // 2011-06-07 by shcho, ��Ʈ�� ��û â������ ���� �Ұ� �Ӽ� ����
#define ITEM_ATTR_WAREHOUSE_SHARE_BANNED		0x04000000		// 67108864, // 2012-01-14 by hskim, ��Ʈ�� �ý��� 2�� - ���� â�� ���� ���� �߰� (ITEM_ATTR_ACCOUNT_POSSESSION ���� �Ӽ��� ���� ����ؾ���)
#define ITEM_ATTR_HYPER_GAMBLE_ITEM				0x08000000		// 134217728, // 2012-12-27 by hskim, ������ ����/���� �ý��� ����

///////////////////////////////////////////////////////////////////////////////
// 2009-04-06 by cmkwon, ��ų ���� �Ӽ� �߰��� ����(��� �ð� ����) - ITEM.ItemAttribute �ʵ带 ����Ѵ�.
#define SKILL_ATTR_STORE_USING_TIME				0x00000001		// 1, // 2009-04-06 by cmkwon, ��ų ���� �Ӽ� �߰��� ����(��� �ð� ����) - 1, ��ų ��� �ð� �����ؾ� �ϴ� ��ų
#define SKILL_ATTR_PARTY_FORMATION_SKILL		0x00000002		// 2, // 2009-08-03 by cmkwon, EP3-4 ���� ���� ��ų ���� - ���� ���� ��ų

#define SIZE_MAX_STORE_ITEM		sizeof(ITEM_GENERAL)		// check: �������� Ÿ�� �� ���� ũ�Ⱑ ū ����ü�� ũ��

// 2012-10-10 by hskim, �Ⱓ�� �Ӽ� ���� (�Ⱓ�� ����)

// 2013-05-31 by jhseol,bckim �Ƹ� �÷��� - #define ����
#define SHAPE_STAT_INIT_LEVEL					0		// �ʱ�ȭ Lv
#define SHAPE_STAT_MAX_LEVEL					10		// ��æƮ ���� �ִ� Lv
#define SHAPE_STAT_FIXED_TIME_LIMITE_LEVEL		10		// �Ⱓ ������ ���� Lv

#define COLLECTION_TYPE_ARMOR					1		// �Ƹ� �÷��� Ÿ��
#define COLLECTION_XAM_ENCHANT_RETURN_ITEMNUM	7006380		// �ִ� ��ȭ�̻�� �ǵ����� ALL��� ���� ĸ�� ������ ��ȣ
// end 2013-05-31 by jhseol,bckim �Ƹ� �÷��� - #define ����

// 2014-07-17 by bckim, �����̾� �Ƹ� �÷���
#define PREMIUM_COLLECTION_MAX_ENCHANT_RETURN_ITEMNUM_B		7046210		
#define PREMIUM_COLLECTION_MAX_ENCHANT_RETURN_ITEMNUM_M		7046230		
#define PREMIUM_COLLECTION_MAX_ENCHANT_RETURN_ITEMNUM_A		7046240		
#define PREMIUM_COLLECTION_MAX_ENCHANT_RETURN_ITEMNUM_I		7046250		
// End. 2014-07-17 by bckim, �����̾� �Ƹ� �÷���


struct FIXED_TERM_INFO
{
	BOOL			bActive;			// ���� ����
	ATUM_DATE_TIME	StartDate;			// ���� �ð�
	ATUM_DATE_TIME	EndDate;			// ���� �ð�

	UID32_t			TimerUID;			// ���� �ð� ������ UID (���������� ���, Ŭ�󿡼��� ��� ����)
	
	// 2013-05-31 by jhseol,bckim �Ƹ� �÷��� - ����ü ���� �߰�
	ItemNum_t		nStatShapeItemNum;	// �ܺ�Ŷ ���� ��ȣ
	BYTE			nStatLevel;			// ����
	
	FIXED_TERM_INFO()
	{
		memset(this, 0x00, sizeof(FIXED_TERM_INFO));
	}
	// end 2013-05-31 by jhseol,bckim �Ƹ� �÷��� - ����ü ���� �߰�
};


// 2014-03-31 by bckim, ��� ���� ų�α� ( ĳ���� ��û) 
enum EN_MONSTER_KILL_LOG_TYPE
{
	KILL_LOG_MONSTER_NORMAL = 1,
	DAMAGE_LOG_MONSTER_MS		= 2,
	DAMAGE_LOG_MONSTER_SP		= 3,
	DAMAGE_LOG_MONSTER_OP		= 4
};
// End. 2014-03-31 by bckim, ��� ���� ų�α� ( ĳ���� ��û) 



// 2013-04-18 by jhseol,bckim �̴��� �Ƹ� - �̺�Ʈ ����Ʈ ����ü ����
struct MONTHLY_ARMOR_EVNET_INFO
{
	INT				nEventUID;			// �̺�Ʈ ��ȣ
	ATUM_DATE_TIME	atStartDate;		// �̺�Ʈ ���� �Ⱓ
	ATUM_DATE_TIME	atEndDate;			// �̺�Ʈ ���� �Ⱓ
	ItemNum_t		nArmorItemNum;		// �̴��� �Ƹ� ����
	ItemNum_t		nArmorSourceIndex;	// �̴��� �Ƹ� ����
	ItemNum_t		nOptionItemNum;		// �ɼ� ������
	INT				nDuration;			// �ɼ� ���� �Ⱓ(��)	// 2013-09-06 by jhseol, �̴��� �Ƹ� �̺�Ʈ ���� �Ⱓ ����
};
typedef vector<MONTHLY_ARMOR_EVNET_INFO>	vectMONTHLY_ARMOR_EVNET_INFO;
// end 2013-04-18 by jhseol,bckim �̴��� �Ƹ� - �̺�Ʈ ����Ʈ ����ü ����

typedef enum FIXED_TERM_TYPE
{
	FIXED_TERM_NONE			= 0,			// ���� 
	FIXED_TERM_SHAPE		= 1,			// �Ⱓ�� ����
	FIXED_TERM_ITEM			= 2,			// ������ �Ⱓ��
	FIXED_TERM_NULL			= 3				// NULL
};
// end 2012-10-10 by hskim, �Ⱓ�� �Ӽ� ���� (�Ⱓ�� ����)

struct ITEM_BASE
{
	BYTE		Kind;							// ������ ����(�����, ��, ����, ��ų.....)
	UID64_t		UniqueNumber;					// ������ ������ȣ
	INT			ItemNum;						// ������ ��ȣ
	ITEM		*ItemInfo;						// ITEM�� ���� pointer
};

// �Ϲ� ������(�����, ����, ...)
struct ITEM_GENERAL : public ITEM_BASE
{
	// store-item-specific fields
	UID32_t			AccountUniqueNumber;
	UID32_t			Possess;					// CharacterUniqueNumber or POSSESS_STORE_NUMBER
	BYTE			ItemStorage;				// 0:ĳ�����κ�, 1:â�� // 2005-12-07 by cmkwon, �Ѱ����� ĳ���� â�� ������ ���´�. ITEM_IN_XXX
	BYTE			Wear;						// 0: ������, 1: ����, 2:����, WEAR_XXX
	INT				CurrentCount;				// ����: ���� �߼�, ������: ���� ����
// 2009-08-25 by cmkwon, ������� �ʴ� �ʵ� ����(td_Store.ScarcityNumber) - 
//	LONGLONG		ScarcityNumber;
	INT				ItemWindowIndex;			// ���� ȭ�鿡�� ������ â�� ���� �ڸ�
	SHORT			NumOfEnchants;				// check: ���� ������� ����! 20031106, kelovon // ������ enchant�� ��, 0�̸� �ƹ��͵� �������� ����
	INT				PrefixCodeNum;				// ���λ�, ������ 0
	INT				SuffixCodeNum;				// ���̻�, ������ 0
	// derived from 'struct ITEM'
	float			CurrentEndurance;			// �Ϲ� ������: ���� ������, ��������(TIMED_HP_UP): ���� �ð�
	
	INT				ColorCode;				// 2009-08-26 by cmkwon, �׷��� ���ҽ� ���� �ý��� ���� - EffectItemNum, �����δ� ������ ź�� ����Ʈ ItemNum�� �ǹ��Ѵ�, // Ʃ�׽� �Ƹ��� ColorCode
	INT				ShapeItemNum;			// 2009-08-26 by cmkwon, �׷��� ���ҽ� ���� �ý��� ���� - 
	UID64_t			MainSvrItemUID;			// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - Main���� ������ UID �߰�

	INT				UsingTimeStamp;				// �������� ���� �ð� �ʴ���(second)
	ATUM_DATE_TIME	UsingStartTime;				// ������ ��� ���� �ð�
	float			DesWeight;					// �߷� ��æƮ ��ġ, 2006-01-24 by cmkwon
	ATUM_DATE_TIME	CreatedTime;				// ������ ���� �ð�, 2006-09-29 by cmkwon �߰� �� - ���� �ð� �� �ڵ� �����Ǵ� ������

	INT				CoolingTimeStamp;				// 2009-09-09 ~ 2010-02-10 by dhjin, ���Ǵ�Ƽ - �ߵ�������������
	ATUM_DATE_TIME	CoolingStartTime;				// 2009-09-09 ~ 2010-02-10 by dhjin, ���Ǵ�Ƽ - �ߵ�������������

	FIXED_TERM_INFO	FixedTermShape;					// 2012-10-10 by hskim, �Ⱓ�� �Ӽ� ���� (�Ⱓ�� ����)

	// 2013-04-18 by jhseol,bckim �̴��� �Ƹ�
	ItemNum_t		nMonthlyOptionItemNum;		// �̴��� �Ƹ� �ɼ� ������ ��ȣ (�ش� �����ۿ� ��ϵ� DexParam�� ����)
	ATUM_DATE_TIME	atMonthlyEventEndDate;		// �̴��� �Ƹ� �̺�Ʈ ����ð� 
	// end 2013-04-18 by jhseol,bckim �̴��� �Ƹ�

	inline ITEM_GENERAL()
	{// 2007-11-27 by cmkwon, �����ϱ� �α� ���� - �߰���
		memset(this, 0x00, sizeof(ITEM_GENERAL));
	}

#ifdef _ATUM_SERVER

	inline ITEM_GENERAL(ITEM* pItemInfo)
	{
		memset(this, 0x00, sizeof(ITEM_GENERAL));
		if (pItemInfo != NULL)
		{
			///////////////////////////////////////////////////////////////////////////////
			// �⺻�� ����
			Wear				= WEAR_NOT_ATTACHED;
			CurrentCount		= (IS_CHARGABLE_ITEM(pItemInfo->Kind)?pItemInfo->Charging:1);
// 2009-08-25 by cmkwon, ������� �ʴ� �ʵ� ����(td_Store.ScarcityNumber) - 
//			ScarcityNumber		= 0;
			ItemWindowIndex		= POS_INVALID_POSITION;
			NumOfEnchants		= 0;
			ColorCode			= 0;
			UsingTimeStamp		= ITEM_NOT_USING;
			ShapeItemNum		= 0;	// 2009-08-26 by cmkwon, �׷��� ���ҽ� ���� �ý��� ���� - ShapeItemNum �ʵ� �߰�

			UsingStartTime.Reset();
			CoolingStartTime.Reset();				// 2009-09-09 ~ 2010-02-10 by dhjin, ���Ǵ�Ƽ - �ߵ�������������
			
			*this				= *pItemInfo;		// ITEM�� ���� �Ҵ�			
			ItemInfo			= pItemInfo;		// ItemInfo Pointer �Ҵ�
		}
	}
	inline ITEM_GENERAL& operator=(const ITEM& rhs)
	{
		this->ItemNum			= rhs.ItemNum;
		this->Kind				= rhs.Kind;
		this->CurrentEndurance	= rhs.Endurance;
		return *this;
	}
#ifndef _ATUM_ADMINTOOL		// 2005-11-26 by cmkwon
	void * operator new(size_t size);
	void operator delete(void* p);
#endif // end_#ifndef _ATUM_ADMINTOOL
#endif // _ATUM_SERVER

	///////////////////////////////////////////////////////////////////////////////
	// 2007-10-15 by cmkwon, ����� ������ źâ�� �ι�� Ŀ����
	int GetMaxBulletCount(BOOL i_bIsMembershipUser)
	{
		if(NULL == ItemInfo)
		{
			return 0;
		}

		if(FALSE == i_bIsMembershipUser)
		{
			return ItemInfo->Charging;
		}

// 2007-10-15 by cmkwon, ��Ʈ���� ������, ����� ������ 2��
#if !defined(SERVICE_TYPE_VIETNAMESE_SERVER_1)
		return 2*ItemInfo->Charging;
#endif
		return ItemInfo->Charging;
	}
	int GetMaxBulletCount(BOOL i_bIsMembershipUser, BOOL i_bIsEffectInWingout = FALSE)
	{
		if (NULL == ItemInfo)
		{
			return 0;
		}

		if (FALSE == i_bIsMembershipUser)
		{
			if (TRUE == i_bIsEffectInWingout)
			{
				//return ItemInfo->Charging + (USHORT)(ItemInfo->Charging/2);
				return ItemInfo->Charging * 1.2;
				// 2015-02-23 by shchoi ����Ʈ ���� ���޹��� ź���� ������������ ���� �����Ǵ� ���� ����
			}

			return ItemInfo->Charging;
		}

#if !defined(SERVICE_TYPE_VIETNAMESE_SERVER_1)
		if (TRUE == i_bIsEffectInWingout)
		{
			//return 2*ItemInfo->Charging + (USHORT)(ItemInfo->Charging/2);
			return 2 * ItemInfo->Charging * 1.1;
			// 2015-02-23 by shchoi ����Ʈ ���� ���޹��� ź���� ������������ ���� �����Ǵ� ���� ����
		}
		return 2 * ItemInfo->Charging;
#endif
		return ItemInfo->Charging;
	}
	// End. // 2014-12-08 by bckim, jwLee ���޹��� ����Ʈ ��ź�� Ȯ�� ����߰�
	///////////////////////////////////////////////////////////////////////////////
	// 2009-08-26 by cmkwon, �׷��� ���ҽ� ���� �ý��� ���� - ShapeItemNum �ʵ� �߰�
	INT GetShapeItemNum(void)
	{
		if(FALSE == IS_ENABLE_CHANGE_ShapeItemNum(Kind))
		{
			return this->ItemInfo->ItemNum;
		}

		if(0 != ShapeItemNum)
		{
			return ShapeItemNum;
		}

		return this->ItemInfo->ItemNum;
	}

	///////////////////////////////////////////////////////////////////////////////
	// 2009-08-26 by cmkwon, �׷��� ���ҽ� ���� �ý��� ���� - ShapeItemNum �ʵ� �߰�
	INT GetEffectItemNum(void)
	{
		if(FALSE == IS_ENABLE_CHANGE_EffectItemNum(Kind))
		{// 2009-08-26 by cmkwon, ����� ���⸸ ����
			return 0;
		}

		if(0 != ColorCode)
		{
			return ColorCode;
		}

		return this->ItemInfo->ItemNum;
	}
};

struct LOG_GUILDSTORE_ITEM_INFO
{// 2006-09-27 by dhjin, ���� �α� ���̺����� ������ �� ���� ����ü
	BYTE			LogType;
	ATUM_DATE_TIME	Time;
	UID32_t			GuildUID;
	CHAR			GuildName[SIZE_MAX_GUILD_NAME];
	UID32_t			AccountUID;
	CHAR			AccountName[SIZE_MAX_ACCOUNT_NAME];
	UID32_t			CharacterUID;
	CHAR			CharacterName[SIZE_MAX_CHARACTER_NAME];
	UID64_t			ItemUID;
	INT				ItemNum;
	CHAR			ItemName[SIZE_MAX_ITEM_NAME];
	INT				PrefixCodeNum;
	INT				SuffixCodeNum;
	INT				ItemResultCount;
	INT				ItemChangeCount;
};

// ��ų�� ������
struct ITEM_SKILL : public ITEM_BASE
{
	// store-item-specific fields
	UID32_t		AccountUniqueNumber;
	UINT		Possess;
	INT			ItemWindowIndex;				// ���� ȭ�鿡�� ������ â�� ���� �ڸ�
	ATUM_DATE_TIME	UseTime;					// 2006-11-17 by dhjin, ��ų ����� �ð�					

#ifdef _ATUM_SERVER
//	ITEM_SKILL() {};
	inline ITEM_SKILL(ITEM* pItem)
	{
		if (pItem != NULL)
		{
			*this = *pItem;
			ItemInfo = pItem;
		}
	}
	inline ITEM_SKILL& operator=(const ITEM& rhs)
	{
		this->ItemNum = rhs.ItemNum;
		this->Kind = rhs.Kind;

		return *this;
	}

	void * operator new(size_t size);
	void operator delete(void* p);
#endif // _ATUM_SERVER
};


///////////////////////////////////////////////////////////////////////////////
// 2009-08-03 by cmkwon, EP3-4 ���� ���� ��ų ���� - 
typedef ez_map<INT, ITEM_SKILL*>	mapINT2ItemSkillPtr;		// ItemNum and ITEN_SKILL pointer


inline int CopyItem2Buffer(char *pBuffer, ITEM_BASE *pItem)	// returns sizeof(ITEM_XXX)
{
	int retSize = 0;
	if (IS_GENERAL_ITEM(pItem->Kind))
	{
		*(ITEM_GENERAL*)pBuffer = *(ITEM_GENERAL*)pItem;
		retSize += sizeof(ITEM_GENERAL);
	}
	else if (IS_SKILL_ITEM(pItem->Kind))
	{
		*(ITEM_SKILL*)pBuffer = *(ITEM_SKILL*)pItem;
		retSize += sizeof(ITEM_SKILL);
	}
	else
	{
		// not reachable
		assert(0);
	}

	return retSize;
}

///////////////////////////////////////////////////////////////////////////////
// Enchant
///////////////////////////////////////////////////////////////////////////////
struct ENCHANT
{
	UID64_t		TargetItemUniqueNumber;
	INT			TargetItemNum;				// ��� �������� ItemNum
	INT			EnchantItemNum;				// enchant�� ���� �������� ItemNum
	// 2013-01-15 by bckim, ��æƮ������ �������ѹ� �߰�
	UINT64		SequenceNumber_DB;

//#ifdef _ATUM_SERVER
//	void * operator new(size_t size);
//	void operator delete(void* p);
//#endif // _ATUM_SERVER

	// 2013-01-15 by bckim, ��æƮ������ �������ѹ� �߰�
	ENCHANT()
	{
		TargetItemUniqueNumber = 0;
		TargetItemNum = 0;
		EnchantItemNum = 0;
		SequenceNumber_DB = 0;
	}
};

// 2013-01-15 by bckim, ��æƮ������ �������ѹ� �߰�
struct ENCHANT_ITEM_SORT_BY_SEQUENCE_NUMBER : binary_function<ENCHANT, ENCHANT, bool>
{
	bool operator()(ENCHANT Param1, ENCHANT Param2)
	{
        return Param1.SequenceNumber_DB < Param2.SequenceNumber_DB; 	// ���� ���� ����
    }
};
// End. 2013-01-15 by bckim, ��æƮ������ �������ѹ� �߰�

typedef vector<ENCHANT>						vectENCHANT;		// 2013-02-27 by bckim, ��æƮ ����Ʈ���� ������(�����۳ѹ�����->��æƮ�ȼ���)		

struct ENCHANT_INFO
{
	INT			EnchantItemNum;			// �ʿ��� ��� ������ �ѹ�
	INT			EnchantItemCount;		// �ʿ��� ��� ����
	INT			EnchantCost;			// ��� ������ ���� ������
	Prob10K_t	ProbabilityPerLevel[SIZE_MAX_ENCHANT_PER_ITEM];	// �� ������ ���� ��þƮ �� ���յ� Ȯ��
};

// 2013-07-01 by bckim, 10��æƮ �̸� ������ī��ó��, �α��߰�, ��� ����
struct SUB_ENCHANT_INFO_SORT_BY_SEQUENCE_NUMBER : binary_function<SUB_ENCHANT_INFO, SUB_ENCHANT_INFO, bool>
{
	bool operator()(SUB_ENCHANT_INFO Param1, SUB_ENCHANT_INFO Param2)
	{
        return Param1.SequenceNumber_DB < Param2.SequenceNumber_DB; 	// ���� ���� ����
    }
};
// End. 2013-07-01 by bckim, 10��æƮ �̸� ������ī��ó��, �α��߰�, ��� ����


#define COUNT_ITEM_MIXING_SOURCE	5
#define COUNT_MAX_MIXING_COUNT		9999	// 2008-03-17 by cmkwon, ���� �ý��� ��� �߰� - �ѹ��� ���� ������ �ִ�ī��Ʈ

// start 2012-03-16 by hskim, DB ���ս� ���� (������ �������� ����)
#define COUNT_ITEM_FIX_MIXING_SOURCE		2
#define INDEX_ITEM_FIX_MIXING_EQUIPMENT		0		// ��� �ε��� (����/�Ƹ�)
#define INDEX_ITEM_FIX_MIXING_EFFECT_CARD	1		// ȿ���� �ε��� (���� ����Ʈ ���� ī��/���� ���� ���� ī��/�Ƹ� ���� ���� ī��)

#define KIND_ITEM_FIX_MIXING_NONE			0		// ����
#define KIND_ITEM_FIX_MIXING_SHAPE_PRIMARY_WEAPON_A		1		// ���� ���� - �⺻ ���� A ���
#define KIND_ITEM_FIX_MIXING_SHAPE_PRIMARY_WEAPON_BMI	2		// ���� ���� - �⺻ ���� BMI ���
#define KIND_ITEM_FIX_MIXING_SHAPE_SECOND_WEAPON_A		3		// ���� ���� - ���� ���� A ���
#define KIND_ITEM_FIX_MIXING_SHAPE_SECOND_WEAPON_BMI	4		// ���� ���� - ���� ���� BMI ���
#define KIND_ITEM_FIX_MIXING_EFFECT_PRIMARY_WEAPON		5		// ���� ���� - �⺻ ���� ����Ʈ
#define KIND_ITEM_FIX_MIXING_EFFECT_SECOND_WEAPON		6		// ���� ���� - ���� ���� ����Ʈ
#define KIND_ITEM_FIX_MIXING_SHAPE_DEFENSE_B			7		// �Ƹ� ���� - B ���
#define KIND_ITEM_FIX_MIXING_SHAPE_DEFENSE_M			8		// �Ƹ� ���� - M ���
#define KIND_ITEM_FIX_MIXING_SHAPE_DEFENSE_A			9		// �Ƹ� ���� - A ���
#define KIND_ITEM_FIX_MIXING_SHAPE_DEFENSE_I			10		// �Ƹ� ���� - I ���
#define KIND_ITEM_FIX_MIXING_SHAPE_DEFENSE_INIT			11		// �Ƹ� ���� - �ʱ�ȭ
#define KIND_ITEM_FIX_MIXING_SHAPE_SECOND_EFFECT_INIT	12		// ����Ʈ ���� - ���� ���� �ʱ�ȭ 
#define KIND_ITEM_FIX_MIXING_SHAPE_PRIMARY_EFFECT_INIT	13		// ����Ʈ ���� - �⺻ ���� �ʱ�ȭ 

#define KIND_ITEM_FIX_MIXING_SHAPE_PET_ITEM				21		// ��Ʈ�� ���� - // 2012-12-03 by hskim, ��Ʈ�� �Ⱓ�� ���� ����
// end2012-03-16 by hskim, DB ���ս� ���� (������ �������� ����)
 
struct ITEM_MIXING_INFO
{
	INT				TargetItemNum;			// �ϼ��� ��� ItemNum
	Prob10K_t		MixingProbability;		// ���۵� Ȯ��(1~10000)
	INT				MixingCost;				// ��� ������ ���� ������
	ITEM_W_COUNT	SourceItem[COUNT_ITEM_MIXING_SOURCE];	// �ʿ��� ��� ItemNum �� ����
	INT				NumOfSourceItems;		// ������ �������� ����(�ε� �� ����ؼ� �Ҵ��ϱ�!)
	BYTE			Visible;				// ȭ�鿡 ǥ�� ���� - // 2013-05-06 by hskim, ������ �̸� ���� (�Ӽ� �� �߰�)

	// 2013-05-06 by hskim, ������ �̸� ���� (�Ӽ� �� �߰�) 
	ITEM_MIXING_INFO()
	{
		TargetItemNum		= 0;				// �ϼ��� ��� ItemNum
		MixingProbability	= 0;				// ���۵� Ȯ��(1~10000)
		MixingCost			= 0;				// ��� ������ ���� ������
		memset(SourceItem, 0x00, sizeof(ITEM_W_COUNT) * COUNT_ITEM_MIXING_SOURCE); // �ʿ��� ��� ItemNum �� ����  
		NumOfSourceItems	= 0;				// ������ �������� ����(�ε� �� ����ؼ� �Ҵ��ϱ�!)
		Visible				= 0;							// ȭ�鿡 ǥ�� ���� - 
	}
	// end 2013-05-06 by hskim, ������ �̸� ���� (�Ӽ� �� �߰�) 
};

// start 2012-02-20 by hskim, DB ����ȭ - ItemMixingInfo
struct ITEM_MIXING_INFO_TOOL
{
	INT				UniqueID;				// ����ũ ID
	INT				TargetItemNum;			// �ϼ��� ��� ItemNum
	Prob10K_t		MixingProbability;		// ���۵� Ȯ��(1~10000)
	INT				MixingCost;				// ��� ������ ���� ������
	BYTE			Visible;				// ȭ�鿡 ǥ�� ���� - // 2013-05-06 by hskim, ������ �̸� ���� (�Ӽ� �� �߰�)
};

struct ITEM_MIXING_ELEMENT_TOOL
{
	INT				UniqueID;				// ����ũ ID
	ITEM_W_COUNT	SourceItem;				// �ʿ��� ��� ItemNum
};
// end 2012-02-20 by hskim, DB ����ȭ - ItemMixingInfo

// DBGOUT
#ifdef _ATUM_SERVER
#ifdef _DEBUG
extern void DbgOut (LPCTSTR pFormat, ...);
#define DBGOUT ::DbgOut
#else
#define DBGOUT ((void)0)
#endif
#endif // _ATUM_SERVER

#define SIZE_DES_PARAM_PER_RARE_ITEM_INFO	9

#define RARE_ITEM_USE_TYPE_NORMAL			1		// �Ϲ�(��ӽ�) ���
#define RARE_ITEM_USE_TYPE_GAMBLE			2		// ���� ���
#define RARE_ITEM_USE_TYPE_SUPERGAMBLE		4		// ���۰��� ���
#define RARE_ITEM_USE_TYPE_HYPERGAMBLE		8		// �����۰��� ��� - // 2012-12-27 by hskim, ������ ����/���� �ý��� ����

struct RARE_ITEM_INFO
{
	INT			CodeNum;			// ���λ�, ���̻� ���е�
	char		Name[SIZE_MAX_RARE_FIX_NAME];
	INT			ReqUseType;			// BitFlag ���
	INT			ReqMinLevel;
	INT			ReqMaxLevel;
	BYTE		ReqItemKind;		// �ʿ����������, ��� ����Ǵ� ������ ����, ITEMKIND_XXX
	GEAR_STAT	ReqGearStat;		// �ʿ� ��� ����
	BYTE		DesParameter[SIZE_DES_PARAM_PER_RARE_ITEM_INFO];
	FLOAT		ParameterValue[SIZE_DES_PARAM_PER_RARE_ITEM_INFO];
	Prob100K_t	Probability;		// ���� ������ ���� Ȯ��, ����: 1 ~ 100000
};
typedef vector<RARE_ITEM_INFO*>			vectRARE_ITEM_INFOPtrList;		// 2010-04-20 by cmkwon, �ű� ��Ű �ӽ� ���� - 
typedef map<int, RARE_ITEM_INFO*>		mapRARE_ITEM_INFOPtrList;		// 2010-04-20 by cmkwon, �ű� ��Ű �ӽ� ���� - <CodeNum, RARE_ITEM_INFO*>

// 1000���� ���λ� 5000���� ���̻� 1�� ������
// 2000���� ���λ� 6000���� ���̻� 2�� ������
#define IS_RARE_PREFIX(_CODE_NUM)	(_CODE_NUM > 0 && _CODE_NUM < 5000)
#define IS_RARE_SUFFIX(_CODE_NUM)	(_CODE_NUM >= 5000)


///////////////////////////////////////////////////////////////////////////////
// 2010-04-09 by cmkwon, ����2�� �߰� ����(�ܰ躰 ���� �߰�) - DROP_TYPE_XXX
typedef INT		DropType_t;
#define DROP_TYPE_DEAD_MONSTER						0		// �Ϲ� ���� ���Ľ� ����Ǵ� ������
#define DROP_TYPE_DEAD_ALL_INFINITY_KEY_MONSTER		1		// ���Ǵ�Ƽ �������� �ش� �ܰ� Ű���Ͱ� ��� ���Ľ� ����Ǵ� ������ ����Ʈ

struct MONSTER2ITEM
{
	INT				MonsterUniqueNumber;	// ���� ����
	INT				ItemNumber;				// �����۰����ѹ�
	INT				MinCount;				// ������ �������� �ּ� ����
	INT				MaxCount;				// ������ �������� �ִ� ����, ���� ������ ������ �ִٸ� MinCount = MixCount
	Prob1000K_t		Probability;			// ���� Ȯ��: 0 ~ 1000000
	Prob100K_t		PrefixProbability;		// ���λ簡 ���� Ȯ��, 0 ~ 100000
	Prob100K_t		SuffixProbability;		// ���̻簡 ���� Ȯ��, 0 ~ 100000
	INT				QuestIndex;				// ����Ʈ �������� ��� QuestIndex ����, �ƴϸ� 0
	DropType_t		DropType;				// DROP_TYPE_XXX // 2010-04-09 by cmkwon, ����2�� �߰� ����(�ܰ躰 ���� �߰�) - 
};

struct CHARACTER2ITEM		// 2006-03-02 by cmkwon
{
	INT				ItemNumber;				// �����۰����ѹ�
	INT				MinCount;				// ������ �������� �ּ� ����
	INT				MaxCount;				// ������ �������� �ִ� ����, ���� ������ ������ �ִٸ� MinCount = MixCount
	Prob1000K_t		Probability;			// ���� Ȯ��: 0 ~ 1000000
	INT				QuestIndex;				// ����Ʈ �������� ��� QuestIndex ����, �ƴϸ� 0
};
typedef vector<CHARACTER2ITEM>			vectCHARACTER2ITEM;

struct CHARACTER2ITEMLIST		// 2006-03-02 by cmkwon
{
	BYTE				InfluenceType0;			// ���� Ÿ������
	USHORT				UnitKindMask0;			// ������ ����
	vectCHARACTER2ITEM	vectCharacter2Item;
};
typedef vector<CHARACTER2ITEMLIST>		vectCHARACTER2ITEMLIST;


#ifndef _ATUM_CLIENT
struct PROJECTINFO
{
	int				m_useTileSetIndex;
	MapIndex_t		m_nMapIndex;
	USHORT			m_nCreateChannelCounts;
	char			m_strFieldIP[SIZE_MAX_IPADDRESS];
	short			m_sFieldListenPort;
	short			m_sFieldUDPPort;
	char			m_strNPCIP[SIZE_MAX_IPADDRESS];
	short			m_sNPCListenPort;
	short			m_sNPCUDPPort;
	short			m_sXSize;						// map�� ���� Ÿ�� ��
	short			m_sYSize;						// map�� ���� Ÿ�� ��
	short			m_sMaximumAltitude;				// map�� �ִ� �̵� ���� ����
	short			m_sMinimumAltitude;				// map�� ���� �̵� ���� ����
	short			m_sWaterAltitude;				// map�� �� ����
	float			m_fFrontPositionDistance;		// 2004-04-09 by cmkwon, ������ ���� ��ǥ�� ���ϱ� ���� �Ÿ�, �ʺ��� �ٸ��� �ִ�.
	BOOL			m_bCreateNPCThread;
	BOOL			m_bAutoCreateMonster;
	MapIndex_t		m_DeadDefaultMapIndex;			// 2004-03-26 by cmkwon, ĳ���� �׾��� �� �����ϴ� default map�� ����
//	BOOL			m_bGuildWarMap;					// ����� ���� ������ ����
	BOOL			m_bAutoDPRecovery;				// 2004-03-26 by cmkwon, �ڵ� DP ȸ�� ����
//	BOOL			m_bTutorialMap;					// 2004-03-26 by cmkwon, Ʃ�丮�� ������ ����
	DWORD			m_dwMaxUserCounts;				// 2004-11-22 by cmkwon, ä�δ� Max ���� ī��Ʈ(ȥ�⵵����� ���� �ʿ�) //2004-03-26 by cmkwon, �ش� ���̰� ä�δ� ��밡���� Bandwidth (config ȭ�Ͽ��� Mbps �� ���� �Ǿ��ְ� loading�ÿ� bps ������ �����Ѵ�)
	D3DXVECTOR3		m_CityWarpTargetPosition;		// ���� ���� ���� ���� Ÿ�� ��ǥ ���� ����
	int				m_nUserVisibleDiameter;			// ���� Move ���� �Ÿ�, ����
	int				m_nMonsterVisibleDiameter;		// ���� Move ���� �Ÿ�, ����
	int				m_nQuestIndexForWarp;			// �̸����� ���� ���ؼ��� ������Ʈ�� �� �Ϸ��ؾ��Ѵ�.
	int				m_nMapInfluenceType;			// 2005-12-28 by cmkwon, ���� ���� ����(MAP_INFLUENCE_XXX)
	MapIndex_t		m_nBeforeMapIndex;				// 2006-08-02 by cmkwon, Ÿ���¸ʿ��� �׾��� ��� ��Ȱ�� ���⿡ ������ �ʿ��� ��Ȱ��
	INT				m_VCNWarpObjectIndex;			// 2006-12-08 by cmkwon
	INT				m_ANIWarpObjectIndex;			// 2006-12-08 by cmkwon
	INT				m_TeleportWarpObjectIndex;		// 2007-09-15 by dhjin
	MapIndex_t		m_nBeforeMapIndex2;				// 2008-06-20 by cmkwon, EP3 ��� �ý��� ����(�ʴ� ����� 2�� ���� �� �� �ִ�) - 


	PROJECTINFO()
	{
	}
	PROJECTINFO(PROJECTINFO &i_refPrj)
	{
		*this = i_refPrj;
	}

	///////////////////////////////////////////////////////////////////////////////
	// 2008-06-20 by cmkwon, EP3 ��� �ý��� ����(�ʴ� ����� 2�� ���� �� �� �ִ�) - 
	BOOL IsValidBeforeMapIndex(void)
	{
		if(0 != m_nBeforeMapIndex
			|| 0 != m_nBeforeMapIndex2)
		{
			return TRUE;
		}

		return FALSE;
	}
};
#endif // _ATUM_CLIENT

struct GBUFFER
{
	char	ptr[SIZE_MAX_LONG_PACKET];
	int		size;

	void Reset() { size = 0; }
	char* GetPtr() { return ptr; }
	int GetSize() { ASSERT_ASSERT(size <= SIZE_MAX_LONG_PACKET); return size; }
};

#ifndef SIZE_MAX_PACKET
#define SIZE_MAX_PACKET						1492	// ��Ŷ �ִ� ������(�������� �޼����� �ϳ��� ��Ŷ���� ���۵ɼ� ����)
#endif

struct GBUFFER_SIZE_MAX_PACKET
{
	char	ptr[SIZE_MAX_PACKET];
	int		size;

	void Reset() { size = 0; }
	char* GetPtr() { return ptr; }
	int GetSize() { ASSERT_ASSERT(size <= SIZE_MAX_PACKET); return size; }
};

// Field Server�� ID�� ������ ����
struct SERVER_ID
{
	// member functions
	SERVER_ID() { Reset(); }
	SERVER_ID(char *IP, int port) { Reset(); SetValue(IP, port); }
	SERVER_ID(const char *szIPPort) { Reset(); SetValue(szIPPort); }
	inline void SetValue(char *IP, int port);
	inline void SetValue(const char *szIPPort);
	inline bool CompareValue(char *IP, int port);
	inline const char* GetString(char* buffer);
	inline const char* GetString(string& str);
	inline bool operator==(SERVER_ID &rhs);
	inline bool operator!=(SERVER_ID &rhs);
	inline void Reset() { memset(this, 0, sizeof(SERVER_ID)); }

	// member variables
	char	IP[SIZE_MAX_IPADDRESS];
	int		port;
};


void SERVER_ID::SetValue(char *IP, int port)
{
	strncpy(this->IP, IP, SIZE_MAX_IPADDRESS);
	this->port = port;
}

void SERVER_ID::SetValue(const char *szIPPort)
{
	char *token;
	char seps[] = " \t,";
	char buffer[64];
	strncpy(buffer, szIPPort, 64);

	token = strtok(buffer, seps);
	if (token == NULL) return;
	strncpy(IP, token, SIZE_MAX_IPADDRESS);
	token = strtok(NULL, seps);
	if (token == NULL) return;
	port = atoi(token);
}

bool SERVER_ID::CompareValue(char *IP, int port)
{
	return strncmp(this->IP, IP, SIZE_MAX_IPADDRESS) == 0 && this->port == port;
}

const char* SERVER_ID::GetString(char* buffer)
{
	if (strncmp(IP, "", SIZE_MAX_IPADDRESS) == 0)
	{
		sprintf(buffer, "0.0.0.0, %d", port);
	}
	else
	{
		sprintf(buffer, "%s, %d", IP, port);
	}
	return buffer;
}

const char* SERVER_ID::GetString(string& str)
{
	char port_str[10];
	sprintf(port_str, "%d", port);
	if (strncmp(IP, "", SIZE_MAX_IPADDRESS) == 0)
	{
		str = "0.0.0.0";
	}
	else
	{
		str = IP;
	}
	str += ", ";
	str += port_str;
	return str.c_str();
}

bool SERVER_ID::operator==(SERVER_ID &rhs)
{
	return (strncmp(IP, rhs.IP, SIZE_MAX_IPADDRESS) == 0 && port == rhs.port);
}

bool SERVER_ID::operator!=(SERVER_ID &rhs)
{
	return !(operator==(rhs));
}

inline bool operator<(const SERVER_ID& lhs, const SERVER_ID& rhs)
{
	bool ret;
	int res_strcmp = strncmp(lhs.IP, rhs.IP, SIZE_MAX_IPADDRESS);

	if (res_strcmp < 0)
	{
		ret = TRUE;
	}
	else if (res_strcmp > 0)
	{
		ret = FALSE;
	}
	else // lhs.IP == rhs.IP
	{
		ret = lhs.port < rhs.port;
	}

	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Version Management
///////////////////////////////////////////////////////////////////////////////
class VersionInfo
{
public:
	VersionInfo()
	{
		memset(this, 0x00, sizeof(VersionInfo));
		m_bIsValid			= FALSE;				// 2006-12-28 by cmkwon
	}

	VersionInfo(const char* string)
	{
		m_bIsValid			= FALSE;				// 2006-12-28 by cmkwon

		char *token;
		char seps[] = ".";
		char buffer[SIZE_MAX_VERSION_STRING];
		memset(buffer, 0x00, SIZE_MAX_VERSION_STRING);
		strncpy(buffer, string, SIZE_MAX_VERSION_STRING);

		token = strtok(buffer, seps);
		if(NULL == token)
		{// 2006-12-28 by cmkwon
			return;
		}
		version[0] = atoi(token);

		token = strtok(NULL, seps);
		if(NULL == token)
		{// 2006-12-28 by cmkwon
			return;
		}
		version[1] = atoi(token);

		token = strtok(NULL, seps);
		if(NULL == token)
		{// 2006-12-28 by cmkwon
			return;
		}
		version[2] = atoi(token);

		token = strtok(NULL, seps);
		if(NULL == token)
		{// 2006-12-28 by cmkwon
			return;
		}
		version[3] = atoi(token);

		if( 0 == (version[0] | version[1] | version[2] | version[3]) )
		{// 2006-12-28 by cmkwon
			return;
		}

		m_bIsValid			= TRUE;				// 2006-12-28 by cmkwon
		sprintf(strBuf, "%d.%d.%d.%d", version[0], version[1], version[2], version[3]);
	}


	///////////////////////////////////////////////////////////////////////////////
	/// \fn			BOOL IsValidVersionInfo(void)
	/// \brief		
	/// \author		cmkwon
	/// \date		2006-12-28 ~ 2006-12-28
	/// \warning	
	///
	/// \param		
	/// \return		
	///////////////////////////////////////////////////////////////////////////////
	BOOL IsValidVersionInfo(void)
	{
		if( 0 == (version[0] | version[1] | version[2] | version[3]) )
		{
			return FALSE;
		}

		return m_bIsValid;
	}

	VersionInfo(const USHORT* ver)
	{
		version[0] = ver[0];
		version[1] = ver[1];
		version[2] = ver[2];
		version[3] = ver[3];
		sprintf(strBuf, "%d.%d.%d.%d", ver[0], ver[1], ver[2], ver[3]);

		if( 0 != (version[0] | version[1] | version[2] | version[3]) )
		{
			m_bIsValid = TRUE;
		}
	}

	inline void SetVersion(USHORT v0, USHORT v1, USHORT v2, USHORT v3)
	{
		version[0] = v0; version[1] = v1; version[2] = v2; version[3] = v3;
		sprintf(strBuf, "%d.%d.%d.%d", v0, v1, v2, v3);
	
		if( 0 != (version[0] | version[1] | version[2] | version[3]) )
		{
			m_bIsValid = TRUE;
		}
	}

	inline void SetVersion(const USHORT* ver)
	{
		version[0] = ver[0];
		version[1] = ver[1];
		version[2] = ver[2];
		version[3] = ver[3];
		sprintf(strBuf, "%d.%d.%d.%d", ver[0], ver[1], ver[2], ver[3]);
		if( 0 != (version[0] | version[1] | version[2] | version[3]) )
		{
			m_bIsValid = TRUE;
		}
	}

	inline void SetVersion(const char* string)
	{
		m_bIsValid		= FALSE;

		char *token;
		char seps[] = ".";
		char buffer[SIZE_MAX_VERSION_STRING];
		strncpy(buffer, string, SIZE_MAX_VERSION_STRING);

		token = strtok(buffer, seps);
		if(NULL == token)
		{
			return;
		}
		version[0] = atoi(token);

		token = strtok(NULL, seps);
		if(NULL == token)
		{
			return;
		}
		version[1] = atoi(token);

		token = strtok(NULL, seps);
		if(NULL == token)
		{
			return;
		}
		version[2] = atoi(token);

		token = strtok(NULL, seps);
		if(NULL == token)
		{
			return;
		}
		version[3] = atoi(token);

		sprintf(strBuf, "%d.%d.%d.%d", version[0], version[1], version[2], version[3]);

		if( 0 != (version[0] | version[1] | version[2] | version[3]) )
		{
			m_bIsValid = TRUE;
		}
	}

	inline const USHORT* GetVersion(USHORT* o_pVersion) const
	{
		o_pVersion[0] = version[0];
		o_pVersion[1] = version[1];
		o_pVersion[2] = version[2];
		o_pVersion[3] = version[3];

		return version;
	}

	inline const USHORT* GetVersion() const
	{
		return version;
	}

	inline char* GetVersionString()
	{
		if (strlen(strBuf) == 0)
		{
			sprintf(strBuf, "%d.%d.%d.%d", version[0], version[1], version[2], version[3]);
		}

		return strBuf;
	}

	inline BOOL Compare(VersionInfo *v)
	{
		if ( version[0] == v->GetVersion()[0] && version[1] == v->GetVersion()[1] && version[2] == v->GetVersion()[2] && version[3] == v->GetVersion()[3] )
		{
			return TRUE;
		}

		return FALSE;
	}

	static bool lt_data(VersionInfo* d1, VersionInfo* d2)
	{
		if (d1->GetVersion()[0] != d2->GetVersion()[0])
		{
			return d1->GetVersion()[0] < d2->GetVersion()[0];
		}
		if (d1->GetVersion()[1] != d2->GetVersion()[1])
		{
			return d1->GetVersion()[1] < d2->GetVersion()[1];
		}
		if (d1->GetVersion()[2] != d2->GetVersion()[2])
		{
			return d1->GetVersion()[2] < d2->GetVersion()[2];
		}
		if (d1->GetVersion()[3] != d2->GetVersion()[3])
		{
			return d1->GetVersion()[3] < d2->GetVersion()[3];
		}

		return FALSE;
	}

	static bool gt_data(VersionInfo* d1, VersionInfo* d2)
	{
		return !lt_data(d1, d2);
	}

	inline bool operator==(const VersionInfo & v)
	{
		if ( version[0] == v.GetVersion()[0] && version[1] == v.GetVersion()[1] && version[2] == v.GetVersion()[2] && version[3] == v.GetVersion()[3] )
		{
			return TRUE;
		}
		return FALSE;
	}

	inline bool operator!=(const VersionInfo & v)
	{
		return !(*this == v);
	}

	inline bool operator<(const VersionInfo & v)
	{
		if (this->GetVersion()[0] != v.GetVersion()[0])
		{
			return this->GetVersion()[0] < v.GetVersion()[0];
		}
		if (this->GetVersion()[1] != v.GetVersion()[1])
		{
			return this->GetVersion()[1] < v.GetVersion()[1];
		}
		if (this->GetVersion()[2] != v.GetVersion()[2])
		{
			return this->GetVersion()[2] < v.GetVersion()[2];
		}
		if (this->GetVersion()[3] != v.GetVersion()[3])
		{
			return this->GetVersion()[3] < v.GetVersion()[3];
		}

		return FALSE;
	}

	inline bool operator>(const VersionInfo & v)
	{
		if (this->GetVersion()[0] != v.GetVersion()[0])
		{
			return this->GetVersion()[0] > v.GetVersion()[0];
		}
		if (this->GetVersion()[1] != v.GetVersion()[1])
		{
			return this->GetVersion()[1] > v.GetVersion()[1];
		}
		if (this->GetVersion()[2] != v.GetVersion()[2])
		{
			return this->GetVersion()[2] > v.GetVersion()[2];
		}
		if (this->GetVersion()[3] != v.GetVersion()[3])
		{
			return this->GetVersion()[3] > v.GetVersion()[3];
		}

		return FALSE;
	}

	inline bool operator<=(const VersionInfo &v) { return !(*this > v); }
	inline bool operator>=(const VersionInfo &v) { return !(*this < v); }

protected:
	BOOL	m_bIsValid;				// 2006-12-28 by cmkwon, 
	USHORT	version[SIZE_MAX_VERSION];
	char	strBuf[SIZE_MAX_VERSION_STRING];
};
typedef mt_map<VersionInfo, VersionInfo>					mtmapVersionInfo;

bool operator<(const VersionInfo &v1, const VersionInfo &v2);

struct MAP_INFO
{
	MapIndex_t		MapIndex;						// 
	MapIndex_t		RenderMapIndex;					// Render ���� ������ �̸��� �ε��� ������ ����, �Ʒ� �Ķ���ʹ� �������� �ʾƵ���
	MapIndex_t		BeforeMapIndex;					// 2006-08-02 by cmkwon, Ÿ���¸ʿ��� �׾��� ��� ��Ȱ�� ���⿡ ������ �ʿ��� ��Ȱ��
	char			MapName[SIZE_MAX_MAP_NAME];
	SHORT			MapInfluenceType;				// ���� ���� Ÿ�� ����(MAP_INFLUENCE_XXX)
	MapIndex_t		CityMapIndex;					// ���������� ���� �ݳ��� ���ε���
	INT				CityWarQuestIndex;				// 
	INT				CityWarQuestNPCIndex;
	INT				CityWarQuestMonsterUID;
	SHORT			MaxUserCount;
	SHORT			MaxGroundHeight;				// �������κ��� �ִ� ����
	SHORT			MinGroundHeight;				// �������κ��� �ּ� ����
	SHORT			WaterHeight;
	SHORT			UserVisibleDistance;
	SHORT			MonsterVisibleDistance;
	INT				QuestIndexForWarp;
	SHORT			FrontPositionDistance;
	BYTE			AutoRecoveryFlag;
	MapIndex_t		DefaultMapIndex;				
	AVECTOR3		CityWarpTargetPosition;
	SHORT			ClientMaxAltitudeHeight;		// Ŭ���̾�Ʈ �ִ� ����, 2005-07-11 by cmkwon
	DWORD			DayFogColor;
	DWORD			NightFogColor;
	SHORT			DayFogStartDistance;
	SHORT			DayFogEndDistance;
	SHORT			NightFogStartDistance;
	SHORT			NightFogEndDistance;
	AVECTOR3		DaySunDirection;
	AVECTOR3		NightSunDirection;
	BYTE			WaterType;
	BYTE			PKZoneFlag;
	BYTE			TileRenderingFlag;
	BYTE			SkyRenderingFlag;
	BYTE			SunRenderingFlag;
	BYTE			FogRenderingFlag;
	INT				VCNWarpObjectIndex;			// 2006-12-08 by cmkwon
	INT				ANIWarpObjectIndex;			// 2006-12-08 by cmkwon
	MapIndex_t		Dat;						// 2007-03-15 by dhjin
	MapIndex_t		Map;						// 2007-03-15 by dhjin
	MapIndex_t		Tex;						// 2007-03-15 by dhjin
	MapIndex_t		Cloud;						// 2007-03-15 by dhjin
	MapIndex_t		Sky;						// 2007-03-15 by dhjin
	MapIndex_t		Nsky;						// 2007-03-15 by dhjin
	MapIndex_t		Bgm;						// 2007-03-15 by dhjin
	INT				TeleportWarpObjectIndex;	// 2007-09-05 by dhjin
	MapIndex_t		BeforeMapIndex2;			// 2008-06-20 by cmkwon, EP3 ��� �ý��� ����(�ʴ� ����� 2�� ���� �� �� �ִ�) - 
	char			MapDescription[SIZE_MAX_MAP_DESCRIPTION];		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - 
	void ResetMAP_INFO(void)
	{
		memset(this, 0x00, sizeof(*this));
	}
};
typedef vector<MAP_INFO>		vectorMAP_INFO;

// String Conversion Functions
const char *GetCharacterString(const CHARACTER *pCharac, string &str);
const char *GetItemString(const ITEM_BASE *pItemBase, string &str);
const char *GetItemGeneralString(const ITEM_GENERAL *pItemGeneral, string &str);
const char *GetItemSkillString(const ITEM_SKILL *pItemSkill, string &str);
const char *DBG_GET_POSITION_STRING(D3DXVECTOR3& vec, string& str);
const char *GetRaceString(USHORT race);
char* Underbar2Space(char *string);
const char *GetTimeString(string &str);

const char *GetMapString(MAP_CHANNEL_INDEX &refMapChannelIndex, string &str);
#define GET_MAP_STRING(refMapChannelIndex)	GetMapString(refMapChannelIndex, string())

BYTE* GetIPAddressInBytes(char *i_szIPAddress, BYTE *o_pIPArray);
const char *GetIPAddressString(BYTE *i_pIPArray, STRNBUF &i_strnbuf);
const char *GetItemDesParameter(DestParam_t i_byDesParameter);		// 2011-08-01 by hskim, ��Ʈ�� �ý��� 2�� - �ڷ��� ���� (DestParameter - 255 -> 32767 ����)
BOOL GIsValidInfuenceType(BYTE i_byInfluenceTy);
char *GGetLowerCase(char *o_szLowercaseSting, char *i_szString, int nMaxStringSize);

enum EN_CHECK_TYPE
{
	CHECK_TYPE_BATTLE_P2P_PK		= 0,		// 1:1 ��� 
	CHECK_TYPE_BATTLE_PARTY_WAR		= 1,		// ������
	CHECK_TYPE_CHARACTER_MENT		= 2,		// "/��Ʈ' ���ɾ�
	CHECK_TYPE_PENALTY_ON_DEAD		= 3,		// ĳ���� �׾��� �� �г�Ƽ(����ġ �ٿ� or SPI �ٿ�) ���� ����
	CHECK_TYPE_TRADE				= 4,		// ������ �ŷ�// 2005-12-06 by cmkwon
	CHECK_TYPE_BATTLE_GUILD_WAR		= 5,		// ������
	CHECK_TYPE_LOWLEVEL_ADVANTAGE	= 6,		// ���� ���� ����
	CHECK_TYPE_BAZAAR				= 7,		// 2006-08-07 by cmkwon, ���� ���� �ŷ�(����/�Ǹ� ����)

	CHECK_TYPE_GUILD_CREATE			= 10,		// ��� ����
	CHECK_TYPE_GUILD_JOIN			= 11,		// ���� ����// 2005-12-07 by cmkwon

	CHECK_TYPE_PARTY_JOIN			= 20,		// ��Ƽ ����// 2005-12-07 by cmkwon

	CHECK_TYPE_CHAT_ALL				= 100,		// ä�� - ��üä��// 2005-12-07 by cmkwon
	CHECK_TYPE_CHAT_MAP				= 101,		// ä�� - ��ä��// 2005-12-07 by cmkwon
	CHECK_TYPE_CHAT_REGION			= 102,		// ä�� - ����ä��// 2005-12-07 by cmkwon
	CHECK_TYPE_CHAT_PTOP			= 103,		// ä�� - �Ӹ�ä��// 2005-12-07 by cmkwon
	CHECK_TYPE_CHAT_SELL_ALL		= 104,		// �Ÿ� ä��
	CHECK_TYPE_CHAT_CASH_ALL		= 105,		// ä�� - ������üä��// 2005-12-07 by cmkwon
	//////////////////////////////////////////////////////////////////////////
	// 2008-06-17 by dhjin, EP3 VOIP - �ý��� �������� �ذ� ���� ����
//	CHECK_TYPE_VOIP_1to1			= 106,		// ����ä�� - 1:1 ä��// 2005-12-07 by cmkwon
//	CHECK_TYPE_CHAT_WAR				= 107		// 2008-05-19 by dhjin, EP3 - ä�� �ý��� ����, ���� ä��
	CHECK_TYPE_CHAT_WAR				= 106,		// 2008-05-19 by dhjin, EP3 - ä�� �ý��� ����, ���� ä��
#if _RAT_CHAT_SYSTEM
	CHECK_TYPE_CHAT_INFLUENCE_ALL_RAT = 109,
#endif

	CHECK_TYPE_VOIP_NONE			= 201,		// 2008-06-17 by dhjin, EP3 VOIP - ����ä������ �ƴϴ�.
	CHECK_TYPE_VOIP_1to1			= 202,		// ����ä�� - 1:1 ä��// 2005-12-07 by cmkwon
	CHECK_TYPE_VOIP_PARTY			= 203,		// 2008-06-17 by dhjin, EP3 VOIP - ��Ƽ ���� ä��
	CHECK_TYPE_VOIP_GUILD			= 204		// 2008-06-17 by dhjin, EP3 VOIP - ���� ���� ä��

};
BOOL GCheckLimitLevel(EN_CHECK_TYPE i_checkType, int i_nLevel);
BOOL GCheckRaceAndInfluenceType(EN_CHECK_TYPE i_checkType, USHORT i_usRace, BYTE i_byInfluenceTy, USHORT i_usPeerRace, BYTE i_byPeerInfluenceTy);

// UID32_t(Unique Number) Generator
class CUID32Generator
{
public:
	CUID32Generator(UID32_t min = 1, UID32_t max = ((UID32_t)~0)-1)
	{
		m_num = min-1;
		m_min = min;
		m_max = max;
	}
	inline UID32_t GetNext()
	{
		if (m_num < m_min-1) return INVALID_UID32;
		if (m_num > m_max) Reset();
		return ++m_num;
	}
	inline UID32_t GetCurrent() { return m_num; }
	inline void Reset() { m_num = m_min-1; }
	inline UID32_t GetMin() { return m_min; }
	inline UID32_t GetMax() { return m_max; }
private:
	UID32_t	m_num;	// ���� ������ UID32
	UID32_t	m_min;	// �ּ� UID32
	UID32_t	m_max;	// �ִ� UID32
};

// UID16_t(Unique Number) Generator
class CUID16Generator
{
public:
	CUID16Generator(UID16_t min = 1, UID16_t max = ((UID16_t)~0)-1)
	{
		m_num = min-1;
		m_min = min;
		m_max = max;
	}
	inline UID16_t GetNext()
	{
		if (m_num < m_min-1) return INVALID_UID16;
		if (m_num > m_max) Reset();
		return ++m_num;
	}
	inline UID16_t GetCurrent() { return m_num; }
	inline void Reset() { m_num = m_min-1; }
	inline UID16_t GetMin() { return m_min; }
	inline UID16_t GetMax() { return m_max; }
private:
	UID16_t	m_num;	// ���� ������ UID16
	UID16_t	m_min;	// �ּ� UID16
	UID16_t	m_max;	// �ִ� UID16
};

///////////////////////////////////////////////////////////////////////////////
// Admin Tool�� Server List
///////////////////////////////////////////////////////////////////////////////
// 2007-10-24 by cmkwon, ���� ���� ��ȣȭ - �Ʒ��� ���� ������
//struct GAME_SERVER_INFO_FOR_ADMIN
//{
//	const char	*ServerName;
//	const char	*ServerIP;
//	const char	*DBIP;
//	int			DBPort;
//	const char	*DBUID;
//	const char	*DBPWD;
//	const char	*DBName;
//};
struct GAME_SERVER_INFO_FOR_ADMIN
{
	const char	*ServerName;
// 2009-01-15 by cmkwon, PreServer, DBServer ���� DNS�� ���� �����ϰ� ���� - �Ʒ��� ���� ���� ��.
//	char		XOREncodedServerIP[2*SIZE_MAX_IPADDRESS];		// 2007-10-24 by cmkwon, ���� ���� ��ȣȭ - �߰��� �ʵ�
//	char		XOREncodedDBIP[2*SIZE_MAX_IPADDRESS];			// 2007-10-24 by cmkwon, ���� ���� ��ȣȭ - �߰��� �ʵ�
	char		XOREncodedServerIP[2*SIZE_MAX_ADDRESS];		// 2009-01-15 by cmkwon, PreServer, DBServer ���� DNS�� ���� �����ϰ� ���� - 
	char		XOREncodedDBIP[2*SIZE_MAX_ADDRESS];			// 2009-01-15 by cmkwon, PreServer, DBServer ���� DNS�� ���� �����ϰ� ���� - 
	int			DBPort;
	char		XOREncodedDBUID[2*SIZE_MAX_DB_USER_ID];		// 2007-10-24 by cmkwon, ���� ���� ��ȣȭ - �߰��� �ʵ�
	char		XOREncodedDBPWD[2*SIZE_MAX_DB_USER_PWD];		// 2007-10-24 by cmkwon, ���� ���� ��ȣȭ - �߰��� �ʵ�
	const char	*DBName;
// 2009-01-15 by cmkwon, PreServer, DBServer ���� DNS�� ���� �����ϰ� ���� - �Ʒ��� ���� ���� ��.
//	char		LogDBIP[2*SIZE_MAX_IPADDRESS];			// 2007-11-07 by cmkwon, �α� DB ���� ���� �����ϱ� - XOR ��ȣȭ�Ǿ� ����, ��ȣȭ �Ͽ� ��� �ؾ� ��
	char		LogDBIP[2*SIZE_MAX_ADDRESS];			// 2009-01-15 by cmkwon, PreServer, DBServer ���� DNS�� ���� �����ϰ� ���� - 
	int			LogDBPort;								// 2007-11-07 by cmkwon, �α� DB ���� ���� �����ϱ� - XOR ��ȣȭ�Ǿ� ����, ��ȣȭ �Ͽ� ��� �ؾ� ��
	char		LogDBUID[2*SIZE_MAX_DB_USER_ID];		// 2007-11-07 by cmkwon, �α� DB ���� ���� �����ϱ� - XOR ��ȣȭ�Ǿ� ����, ��ȣȭ �Ͽ� ��� �ؾ� ��
	char		LogDBPWD[2*SIZE_MAX_DB_USER_PWD];		// 2007-11-07 by cmkwon, �α� DB ���� ���� �����ϱ� - XOR ��ȣȭ�Ǿ� ����, ��ȣȭ �Ͽ� ��� �ؾ� ��
// 2009-01-15 by cmkwon, PreServer, DBServer ���� DNS�� ���� �����ϰ� ���� - �Ʒ��� ���� ���� ��.
//	char		ServerIP[SIZE_MAX_IPADDRESS];
//	char		DBIP[SIZE_MAX_IPADDRESS];
	char		ServerIP[SIZE_MAX_ADDRESS];				// 2009-01-15 by cmkwon, PreServer, DBServer ���� DNS�� ���� �����ϰ� ���� - 
	char		DBIP[SIZE_MAX_ADDRESS];					// 2009-01-15 by cmkwon, PreServer, DBServer ���� DNS�� ���� �����ϰ� ���� - 
	char		DBUID[SIZE_MAX_DB_USER_ID];
	char		DBPWD[SIZE_MAX_DB_USER_PWD];
};

///////////////////////////////////////////////////////////////////////////////
// 
///////////////////////////////////////////////////////////////////////////////
typedef enum EN_CASH_PREMIUM_CARD_STATE
{
	CASH_PREMIUM_CARD_STATE_NOT_EXIST	= 0,
	CASH_PREMIUM_CARD_STATE_NORMAL		= 1,
	CASH_PREMIUM_CARD_STATE_INSERTING	= 2,
	CASH_PREMIUM_CARD_STATE_UPDATING	= 3,
	CASH_PREMIUM_CARD_STATE_DELETING	= 4
};

struct SCASH_PREMEIUM_CARD_INFO
{
	void ResetCASH_PREMEIUM_CARD_INFO(void)
	{
		enCardState			= CASH_PREMIUM_CARD_STATE_NOT_EXIST;
		n64UniqueNumber10	= 0;
		nAccountUID10		= 0;
		nCardItemNum		= 0;
		atumTimeCreatedTime.Reset();
		atumTimeUpdatedTime.Reset();
		atumTimeExpireTime.Reset();

		fExpRate			= 0.0f;
		fSPIRate			= 0.0f;
		fDropRate			= 0.0f;
		fDropRareRate		= 0.0f;
		fExpRepairRate		= 0.0f;
		nInventoryPlusCounts		= 0;		// 2006-09-06 by cmkwon
		nStorePlusCounts			= 0;		// 2006-09-06 by cmkwon
		nGuildCapacityPlusCounts	= 0;		// 2006-09-06 by cmkwon
	}

	void ResetAllPlusRateByPremiumCard(int i_nLangTy)
	{
		fExpRate			= 0.0f;
		fSPIRate			= 0.0f;
		fDropRate			= 0.0f;
		fDropRareRate		= 0.0f;
		fExpRepairRate		= 0.0f;
		nInventoryPlusCounts		= 0;		// 2006-09-06 by cmkwon
		nStorePlusCounts			= 0;		// 2006-09-06 by cmkwon
		nGuildCapacityPlusCounts	= 0;		// 2006-09-06 by cmkwon

		if(CASH_PREMIUM_CARD_STATE_NOT_EXIST == enCardState)
		{// 2006-10-11 by cmkwon
			return;
		}

		///////////////////////////////////////////////////////////////////////////////
		// �����̾� �ɼ� [����,��ȹ]
		nInventoryPlusCounts		= COUNT_IN_MEMBERSHIP_ADDED_INVENTORY;		// 2006-09-06 by cmkwon
		nStorePlusCounts			= COUNT_IN_MEMBERSHIP_ADDED_STORE;			// 2006-09-06 by cmkwon
		nGuildCapacityPlusCounts	= COUNT_IN_MEMBERSHIP_ADDED_GUILD_CAPACITY;	// 2006-09-06 by cmkwon
		fExpRepairRate				= 0.5f;										// 2006-10-19 by cmkwon, ��� ���� �� �г�Ƽ 50% ����

		// 2008-04-25 by cmkwon, ���� ���/���� �߰��� �� �߰� �Ǿ�� �ϴ� ���� - [���-�ɼ�] ����� �߰� ���� ����
		switch(i_nLangTy)
		{
		case LANGUAGE_TYPE_VIETNAMESE:
			{// 2006-10-11 by cmkwon, ��Ʈ���� ����(����ġ 20%, �����۵���� 20%, SPI ����� 40%)
				fExpRate			= 0.2f;
				fSPIRate			= 0.4f;
				fDropRate			= 0.2f;
				fDropRareRate		= 0.0f;
			}
			break;
		case LANGUAGE_TYPE_CHINESE:
			{// 2007-11-06 by cmkwon, �߱����� ����� ���� �߰� - ����ġ 15%
				fExpRate			= 0.15f;
			}
			break;
		case LANGUAGE_TYPE_TAIWANESE:
			{// 2008-12-15 by cmkwon, �븸 Netpower_tpe �� ����� �߰� ����(����ġ 20%) �߰� - 
				fExpRate			= 0.2f;
			}
			break;
		}
// 2007-11-06 by cmkwon, �߱����� ����� ���� �߰� - ���� ���� ���� ��
//		if(LANGUAGE_TYPE_VIETNAMESE == i_nLangTy)
//		{// 2006-10-11 by cmkwon, ��Ʈ���� ����(����ġ 20%, �����۵���� 20%, SPI ����� 40%)
//			fExpRate			= 0.2f;
//			fSPIRate			= 0.4f;
//			fDropRate			= 0.2f;
//			fDropRareRate		= 0.0f;
//		}
	}
	EN_CASH_PREMIUM_CARD_STATE	enCardState;
	UID64_t			n64UniqueNumber10;
	UID32_t			nAccountUID10;
	INT				nCardItemNum;
	ATUM_DATE_TIME	atumTimeCreatedTime;	// ������ �ð�
	ATUM_DATE_TIME	atumTimeUpdatedTime;	// ������ �ð�
	ATUM_DATE_TIME	atumTimeExpireTime;		// ���� �ð�

	float			fExpRate;
	float			fSPIRate;
	float			fDropRate;
	float			fDropRareRate;
	float			fExpRepairRate;

	int				nInventoryPlusCounts;		// 2006-09-06 by cmkwon, �κ��丮 �߰� ī��Ʈ
	int				nStorePlusCounts;			// 2006-09-06 by cmkwon, â�� �߰� ī��Ʈ
	int				nGuildCapacityPlusCounts;	// 2006-09-06 by cmkwon, ���ܿ� �߰� ī��Ʈ
};

struct SCITY_OCCUPY_INFO
{
	UID32_t			OccupyGuildUID;
	char			OccupyGuildName[SIZE_MAX_GUILD_NAME];
	UID32_t			OccupyGuildMasterCharacterUID;
	float			fTexPercent;								// ���� �ۼ�Ʈ(2 ~ 100)
	ATUM_DATE_TIME	CityWarDefaultTime;
	ATUM_DATE_TIME	CityWarSettingTime;
	INT				nDefenseCounts;
	INT				nSumOfTex;
	char			szBriefing[SIZE_MAX_CITY_BRIEFING_LENGTH];

	void ResetCITY_OCCUPY_INFO(void);
};

struct SCOUPON
{
	INT					nCouponUniqueNumber;
	char				szCouponNumber[SIZE_MAX_COUPON_NUMBER];
	ATUM_DATE_TIME		atimeExpireTime;
	BOOL				bUsedFlag;
	char				szUsedAccountName[SIZE_MAX_ACCOUNT_NAME];
	ATUM_DATE_TIME		atimeUsedTime;
};


enum EN_BLOCKED_TYPE
{
	T_BLOCKEDACCOUNT_UNKNOWN			= 0,		// �˼� ����
	T_BLOCKEDACCOUNT_NORMAL				= 1,		// Ư���� ���� ����, �ӽ÷�
	T_BLOCKEDACCOUNT_MONEY_RELATED		= 2,		// �� ���� - SPI, 			
	T_BLOCKEDACCOUNT_ITEM_RELATED		= 3,		// ������ ���� - ���(������ ����, �Ǹ�)  
	T_BLOCKEDACCOUNT_SPEEDHACK_RELATED	= 4,		// ���ǵ��� ����
	T_BLOCKEDACCOUNT_CHAT_RELATED		= 5,		// ä�� ���� - �弳 
	T_BLOCKEDACCOUNT_CHAT_GAMEBUG		= 6,		// ���� ���� ���� - ���� ���� �̿��� ����
	T_BLOCKEDACCOUNT_MEMORYHACK_AUTOBLOCK	= 7,	// �޸��� ���� ���� - // 2012-12-14 by hskim, �޸��� �ڵ� ���� ��� ����
	T_BLOCKEDACCOUNT_SPEEDHACK_AUTOBLOCK	= 8		// ���ǵ��� ���� ���� - // 2013-01-29 by hskim, ���ǵ��� �ڵ� ���� ��� ����
};

char * GetStringBLOCKED_TYPE(int i_blocktype);
int GetBlockTypeBYBlockTypeString(char *i_szTyString);	// 2008-01-30 by cmkwon, ���� ���� �α� ����� ���� - GetBlockTypeBYBlockTypeString() �߰�
struct SBLOCKED_ACCOUNT_INFO
{
	char			szBlockedAccountName[SIZE_MAX_ACCOUNT_NAME];
	EN_BLOCKED_TYPE	enBlockedType;
	ATUM_DATE_TIME	atimeStartTime;
	ATUM_DATE_TIME	atimeEndTime;
	INT				AdminFieldServerClientIndex;		// 2008-01-31 by cmkwon, ���� ����/���� ���ɾ�� ������ �ý��� ���� - PreServer<->FieldServer ������ �����
	char			szBlockAdminAccountName[SIZE_MAX_ACCOUNT_NAME];
	char			szBlockedReasonForUser[SIZE_MAX_BLOCKED_ACCOUNT_REASON];
	char			szBlockedReasonForOnlyAdmin[SIZE_MAX_BLOCKED_ACCOUNT_REASON];		// 2007-01-10 by cmkwon
};

///////////////////////////////////////////////////////////////////////////////
// 2006-04-12 by cmkwon, ������ ���� �ý������� �߰���
#define MAX_INFLUENCEWAR_WARTIMESTAGE			5		// 2006-04-13 by cmkwon, 0 ~ 5
#define MAX_INFLUENCEWAR_EVENT_SUMMON_COUNT		5		// 2006-04-13 by cmkwon
#define	STRATEGYPOINT_MONSTER_NUM_VCN			2052000	// 2007-11-07 by dhjin, ��������Ʈ VCN��ȣ
#define	STRATEGYPOINT_MONSTER_NUM_ANI			2052100	// 2007-11-07 by dhjin, ��������Ʈ ANI��ȣ

struct SDB_INFLUENCE_WAR_INFO
{
	BYTE			InfluenceType;					// INFLUENCE_TYPE_VCN(2) or INFLUENCE_TYPE_ANI(4)
	BYTE			WartimeStage;					// ���ôܰ�
	INT				ReqContributionPoint;			// ���ôܰ谡 �Ǳ� ���� �ʿ� �⿩��(ContributionPoint)
	float			HPRepairRate;					// �ش� ���ôܰ� �� �� HPȸ����                            
	float			DPRepairRate;					// �ش� ���ôܰ� �� �� DPȸ����                            
	float			SPRepairRate;					// �ش� ���ôܰ� �� �� SPȸ����                            
	INT				EventTime;						// �������������� ���� �� �ش� ���ôܰ迡 ���۵Ǵ� �̺�Ʈ ���� �ð�(����:��)
	float			EventExperience;				// �������������� ���� �� �ش� ���ôܰ迡 ���۵Ǵ� �̺�Ʈ �̺�Ʈ - ����ġ          
	float			EventDropSPI;					// �������������� ���� �� �ش� ���ôܰ迡 ���۵Ǵ� �̺�Ʈ �̺�Ʈ - ��� SPI        
	float			EventDownExperience;			// �������������� ���� �� �ش� ���ôܰ迡 ���۵Ǵ� �̺�Ʈ �̺�Ʈ - ����ġ ���     
	float			EventDropItem;					// �������������� ���� �� �ش� ���ôܰ迡 ���۵Ǵ� �̺�Ʈ �̺�Ʈ - ��� Item       
	float			EventDropRareItem;				// �������������� ���� �� �ش� ���ôܰ迡 ���۵Ǵ� �̺�Ʈ �̺�Ʈ - ��� ���� Item  
	INT				SupplyItemNum;					// �������������� ���� �� �ش� ���ôܰ迡 ���޵Ǵ� ItemNum
	INT				SupplyItemCount;				// �������������� ���� �� �ش� ���ôܰ迡 ���޵Ǵ� Item Count
	BYTE			IsSummonJacoMonster;
	INT				BossMonsterUnitKind;			// �� �ܰ� �ʿ� �⿩���� �Ѿ�� ������ ��ȯ�Ǵ� �������������� MonsterUnitKind          
	INT				BossMonsterCount;				// �� �ܰ� �ʿ� �⿩���� �Ѿ�� ������ ��ȯ�Ǵ� Monster count
	INT				BossMonsterSummonTerm;			// �� �ܰ� �ʿ� �⿩���� �Ѿ�� ������ ��ȯ�Ǵ� �������������Ͱ� ��ȯ�Ǵ� �ð� ��(���� 15��, ����:��)
	SHORT			BossMonsterSummonMapIndex;		// �� �ܰ� �ʿ� �⿩���� �Ѿ�� ������ ��ȯ�Ǵ� �������������Ͱ� ��ȯ�Ǵ� MapIndex        
	SHORT			BossMonsterSummonPositionX;		// �� �ܰ� �ʿ� �⿩���� �Ѿ�� ������ ��ȯ�Ǵ� �������������Ͱ� ��ȯ�Ǵ� ��ǥ x                   
	SHORT			BossMonsterSummonPositionY;		// �� �ܰ� �ʿ� �⿩���� �Ѿ�� ������ ��ȯ�Ǵ� �������������Ͱ� ��ȯ�Ǵ� ��ǥ y                   
	SHORT			BossMonsterSummonPositionZ;		// �� �ܰ� �ʿ� �⿩���� �Ѿ�� ������ ��ȯ�Ǵ� �������������Ͱ� ��ȯ�Ǵ� ��ǥ z                   
	INT				SummonMonsterUnitKind[MAX_INFLUENCEWAR_EVENT_SUMMON_COUNT];		// �������������� ���� �� �ش� ���ôܰ迡 ��ȯ�Ǵ� MonsterUnitKind
	INT				SummonCount[MAX_INFLUENCEWAR_EVENT_SUMMON_COUNT];				//  ��ȯ�Ǵ� Monster Count
	SHORT			SummonMapIndex[MAX_INFLUENCEWAR_EVENT_SUMMON_COUNT];			//  ���Ͱ� ��ȯ�Ǵ� MapIndex
	SHORT			SummonPositionX[MAX_INFLUENCEWAR_EVENT_SUMMON_COUNT];			//  ��ȯ�Ǵ� ��ǥ x
	SHORT			SummonPositionY[MAX_INFLUENCEWAR_EVENT_SUMMON_COUNT];			//  ��ȯ�Ǵ� ��ǥ y
	SHORT			SummonPositionZ[MAX_INFLUENCEWAR_EVENT_SUMMON_COUNT];			//  ��ȯ�Ǵ� ��ǥ z
	INT				SupplyItemNum2;					// �������������� ���� �� �ش� ���ôܰ迡 ���޵Ǵ� ItemNum	// 2007-05-16 by dhjin, �߰���
	INT				SupplyItemCount2;				// �������������� ���� �� �ش� ���ôܰ迡 ���޵Ǵ� Item Count	// 2007-05-16 by dhjin, �߰���
	INT				WinBossMonsterUnitKind;			// 2009-03-10 by dhjin, �ܰ躰 �� �ý��� - ���� �� �¸� ������ ��� ��ȯ�Ǿ�� �Ǵ� ��UID
	INT				LossBossMonsterUnitKind;		// 2009-03-10 by dhjin, �ܰ躰 �� �ý��� - ���� �� �й� ������ ��� ��ȯ�Ǿ�� �Ǵ� ��UID

	// 2008-05-20 by cmkwon, ��� �̺�Ʈ(HappyHoure,MotherShip,Item) �׷� ���ÿ� �����ϰ� - 
	BOOL IsValidGameEvent(void)
	{
		if(0 >= EventTime)
		{
			return FALSE;
		}

		if( 0.0f < EventExperience
			|| 0.0f < EventDropSPI
			|| 0.0f < EventDownExperience
			|| 0.0f < EventDropItem
			|| 0.0f < EventDropRareItem )
		{
			return TRUE;
		}

		return FALSE;
	}
};
typedef vector<SDB_INFLUENCE_WAR_INFO>			vectDB_INFLUENCE_WAR_INFO;

struct SINFLUENCE_WAR_DATA
{
	BYTE			InfluenceType;			// INFLUENCE_TYPE_VCN(2) or INFLUENCE_TYPE_ANI(4)
	INT				MGameServerID;			// ������ ä�� ���� ��ȣ - global.cfg ���Ͽ� �����Ѵ�.
	BYTE			WartimeStage;			// ���� ���ôܰ�
	INT				ContributionPoint;		// ���� �⿩�� - �Ƹ� �Ѵ� ���� �⿩���� �ɰ��̴�
	UID32_t			InflLeaderCharacterUID;	// ���� ������ CharacterUID
	UID32_t			InflSub1LeaderCharacterUID;	// 2006-12-08 by dhjin, ��������1
	UID32_t			InflSub2LeaderCharacterUID; // 2006-12-08 by dhjin, ��������2
	CHAR			InflLeaderCharacterName[SIZE_MAX_CHARACTER_NAME];		// 2007-12-03 by dhjin, ������ 
	CHAR			InflSubLeader1CharacterName[SIZE_MAX_CHARACTER_NAME];	// 2007-12-03 by dhjin, ��������1
	CHAR			InflSubLeader2CharacterName[SIZE_MAX_CHARACTER_NAME];	// 2007-12-03 by dhjin, ��������2
	SHORT			MSWarOptionType;		// 2008-04-10 by dhjin, ���� ���� ǥ�� ��ȹ�� - 
	SHORT			ConsecutiveVictories;	// 2013-05-09 by hskim, ���� ����Ʈ ����
};

struct SINFLBOSS_MONSTER_SUMMON_DATA
{
	MONSTER_INFO	*pMonsterInfo;				// �������������� ����
	INT				SummonCount;				// ��ȯ�� Monster Count
	INT				SummonTerm;					// ��ȯ�Ǳ� ���� �ð� ��(���� 15��, ����:��)
	ATUM_DATE_TIME	atimeInsertedTime;			// ��ȯ ���� �߰��� �ð� - ��ȯ�Ǳ� ���� �ð� �� ó���� ���� �ʿ�
	SHORT			SummonMapIndex;				// �������������Ͱ� ��ȯ�Ǵ� MapIndex
	AVECTOR3		SummonPosition;				// �������������Ͱ� ��ȯ�Ǵ� ��ǥ
	BYTE			BossStep;					// 2009-03-10 by dhjin, �ܰ躰 �� �ý��� - �� �ܰ�
	BYTE			BeforeWinCheck;				// 2009-03-10 by dhjin, �ܰ躰 �� �ý��� - �� �ܰ� ���� ����
};

int GDelimiterIndex(char *i_szStr, int i_nMinIndex);

struct SSUMMONBOSSMONSTER_INFO
{// 2007-02-06 by dhjin, ��ȯ ���� ���� 
	BOOL			bSummonBossMonster;
	ATUM_DATE_TIME	SummonBossTime;
	INT				SummonMonsterUnitkind;
	INT				ContributionPoint;			// 2008-04-01 by dhjin, ����, ������ ����â ��ȹ�� - 
	BYTE			BossStep;					// 2009-03-10 by dhjin, �ܰ躰 �� �ý��� - �� �ܰ�
	BYTE			BeforeWinCheck;				// 2009-03-10 by dhjin, �ܰ躰 �� �ý��� - �� �ܰ� ���� ����
};

struct SDELETED_CHARACTER_INFO
{// 2007-02-22 by dhjin, �ɸ��� ���� ��å���� ���� ������ �ɸ��� ���� ����ü.
	UID32_t			AccountUID;
	CHAR 			AccountName[SIZE_MAX_ACCOUNT_NAME];
	UID32_t			CharacterUID;
	CHAR 			CharacterName[SIZE_MAX_CHARACTER_NAME];
	BYTE			InflueceType0;			// 2008-01-17 by cmkwon, T_A: ���� ������ ĳ���� �� ����, ���� ������ ���� �����ֱ� �߰� - SDELETED_CHARACTER_INFO �� �ʵ� �߰�
	BYTE			SelectableInflueceMask;	// 2008-01-17 by cmkwon, T_A: ���� ������ ĳ���� �� ����, ���� ������ ���� �����ֱ� �߰� - SDELETED_CHARACTER_INFO �� �ʵ� �߰�
	ATUM_DATE_TIME	atDeletedDTime;			// 2008-03-03 by cmkwon, ���� ������ ĳ���͸���Ʈ ������ ���� �� ��¥ ���� �ֱ� - 
};

struct SSUMMON_STRATEGYPOINT_INFO
{// 2007-02-23 by dhjin, /�������� ���ɾ�
	MapIndex_t		MapIndex;
	BYTE			InfluenceType;
	CHAR			MapName[SIZE_MAX_MAP_NAME];
	ATUM_DATE_TIME	SummonStrategyPointTime;
};

struct SSTRATEGYPOINT_SUMMONTIME_INFO
{// 2007-02-28 by dhjin, ��������Ʈ ���� ���� ����ü
	MapIndex_t		MapIndex;
	BYTE			SummonCount;
	ATUM_DATE_TIME	SummonTime;
	BOOL			SummonAttribute;		// 2008-04-08 by dhjin, ��ȯ ���� �ð� ���� - 
};
typedef vector<SSTRATEGYPOINT_SUMMONTIME_INFO>	vectSSTRATEGYPOINT_SUMMONTIME_INFO;

struct SSTRATEGYPOINT_SUMMON_RANGE
{// 2007-02-28 by dhjin, ��������Ʈ ���� �ֱ� ����ü
	SHORT			SummonRange;
	BOOL			StrategyPointSummonCheck;
	BYTE			MaxSummonCountDaily;
	ATUM_DATE_TIME	StartTime;
	ATUM_DATE_TIME	EndTime;
	SHORT			NewSummonRange;
	BYTE			NewMaxSummonCountDaily;
};

struct SSTRATEGYPOINT_NOT_SUMMON_TIME
{// 2007-02-28 by dhjin, ��������Ʈ �����Ǹ� �ȵǴ� ���Ϻ� �ð� ���� ����ü
	SHORT			DayOfWeek;
	ATUM_DATE_TIME	StartTime;
	ATUM_DATE_TIME	EndTime;
	BOOL			CheckSummon;			// 2008-04-04 by dhjin, ��ȯ ���� �ð� ���� - 0:�����ð� , 1:��ȯ�ð�
};
typedef vector<SSTRATEGYPOINT_NOT_SUMMON_TIME>	vectSSTRATEGYPOINT_NOT_SUMMON_TIME;

struct SSTRATEGYPOINT_DAY
{// 2007-03-07 by dhjin, ��������Ʈ ���� üũ ����.
	USHORT			Year;
	BYTE			Month;
	BYTE			Day;
	BYTE			MaxCount;
};

struct SSPPossibleTimeInfo
{// 2009-03-23 by dhjin, ��������Ʈ �ð� ���� ���� - ��������Ʈ ��ȯ ������ �ð��� ���� ����
	ATUM_DATE_TIME	StartTime;
	ATUM_DATE_TIME	EndTime;
	INT				PossibleMinRange;
	BOOL			CheckSummon;			// 2008-04-04 by dhjin, ��ȯ ���� �ð� ���� - 0:�����ð� , 1:��ȯ�ð�
};
typedef vector<SSPPossibleTimeInfo>		vectSSPPossibleTimeInfo;

///////////////////////////////////////////////////////////////////////////////
// 2006-07-25 by cmkwon, ���λ��� ����
#define SIZE_MAX_BAZAAR_ITEM_COUNT		16			// 2006-07-25 by cmkwon, �Ǹ� Ȥ�� ���� ����Ʈ �ִ� ����
#define SIZE_MAX_BAZAAR_NAME			32			// 2006-07-25 by cmkwon, 
#define SIZE_MAX_BAZAAR_NAME			32			// 2006-07-25 by cmkwon, 
#define REQUERED_BAZAAR_DISTANCE		100.0f		// 2006-08-01 by cmkwon, ���� ������ �ŷ��ϱ� ���� �Ÿ�

#define BAZAAR_TYPE_NONE				0		// 2006-07-25 by cmkwon
#define BAZAAR_TYPE_SELL				1		// ���� �Ǹ� ����
#define BAZAAR_TYPE_BUY					2		// ���� ���� ����

#define BAZAAR_STATE_NONE				0		// 2006-07-25 by cmkwon
#define BAZAAR_STATE_READY				1		// 2006-07-26 by cmkwon, ���� ���� �غ� ���� - ��ų ����� ���۵Ǿ����� ���� ������ �������� ���� ����
#define BAZAAR_STATE_ACTIVE				2		// 2006-07-26 by cmkwon, Ÿ������ ���� ���� �Ǹ�/���� ���� ����
#define BAZAAR_STATE_END				3		// 2006-07-26 by cmkwon, ǰ��

///////////////////////////////////////////////////////////////////////////////
// 2006-08-25 by cmkwon
struct SHAPPY_HOUR_EVENT
{
	INT				EventUniqueNumber;		// 
	INT				ServerGroupID;			// 2006-08-25 by cmkwon, 0(=AllServerGroup), 1(=10061), 2(10062), ...
	INT				DayOfWeek;				// ����	- ��(0) ��(1) ȭ(2) ��(3) ��(4) ��(5) ��(6) �ش缼��HappyHourEvent�Ⱓ(7) PCBangHappyHourEvent�Ⱓ����(8)
	ATUM_DATE_TIME	atimeStartTime2;		//
	ATUM_DATE_TIME	atimeEndTime2;			//
	float			fEXPRate2;
	float			fSPIRate2;
	float			fEXPRepairRate2;
	float			fDropItemRate2;
	float			fDropRareItemRate2;
	float			fWarPointRate2;			// 2007-06-26 by dhjin, WarPoint �̺�Ʈ
	BYTE			InfluenceType3;			// 2007-10-30 by cmkwon, ���º� ���Ǿƿ� �̺�Ʈ ���� - SHAPPY_HOUR_EVENT ����ü�� �ʵ� �߰�
	INT				MinLevel;				// 2008-03-13 by dhjin, Level�� ���Ǿƿ� �̺�Ʈ ���� -
	INT				MaxLevel;				// 2008-03-13 by dhjin, Level�� ���Ǿƿ� �̺�Ʈ ���� -

	// 2013-08-12 by bckim, �ű����Ǿƿ�
	float			fHPRecoveryRate;	
	float			fSHDRecoveryRate;
	float			fSPRecoveryRate;
	float			fWeaponEnchantRate;
	float			fArmorEnchantRate;
	float			fETCItemEnchantRate;
	float			fSPIDiscountRate;
	float			fWPDiscountRate;
	
	SHAPPY_HOUR_EVENT()
	{
		MEMSET_ZERO(this, sizeof(SHAPPY_HOUR_EVENT));
	}
	// End. 2013-08-12 by bckim, �ű����Ǿƿ�
};

struct SHAPPY_HOUR_EVENT_PERIOD
{// 2007-10-30 by cmkwon, ���º� ���Ǿƿ� �̺�Ʈ ���� ����ü �߰�
	INT				EventUniqueNumber;		// 
	ATUM_DATE_TIME	atimeStartTime2;		//
	ATUM_DATE_TIME	atimeEndTime2;			//
	BYTE			InfluenceType3;			//

	void InitSHAPPY_HOUR_EVENT_PERIOD(BYTE i_byInflTy)
	{
		EventUniqueNumber		= 0;
		atimeStartTime2.Reset();
		atimeEndTime2.Reset();
		InfluenceType3			= i_byInflTy;
	}
};

#define SERVERGROUP_START_ID			10061					// 2006-08-25 by cmkwon, global.cfg ������ atum2_db_1 DB�� ����ϴ� ��ȣ�� ������ �ؾ��Ѵ�.
#define STR_ALL_SERVERGROUP_NAME		"All ServerGroup"		// 2006-08-25 by cmkwon

///////////////////////////////////////////////////////////////////////////////
// end 2011-12-12 by hskim, GLog 2��

#define GLOG_EXCUTE_FILE_NAME				"./GLogClient.exe"
#define GLOG_EXCUTE_FILE_NAME_WATCHPROC		"../Bin/Release/GLogClient.exe"
#define GLOG_EXCUTE_FILE_NAME_VISUALC		"../../Bin/Release/GLogClient.exe"

///////////////////////////////////////////////////////////////////////////////
// 2006-10-02 by cmkwon, WebLauncher ����
#define SIZE_MAX_ARGV_COUNT					10					// 2006-10-02 by cmkwon, ���� ���� �ִ� ����
// 2008-12-18 by cmkwon, �Ϻ� Arario ��ó ���� - �Ʒ��� ���� 400 ���� ����
//#define SIZE_MAX_ARGV_PARAM_STRING_SIZE		50					// 2006-10-02 by cmkwon, �ϳ��� ���� ���� ��Ʈ�� �ִ� ����
#define SIZE_MAX_ARGV_PARAM_STRING_SIZE		400		// 2008-12-18 by cmkwon, �Ϻ� Arario ��ó ���� - SessionKey(301 Bytes) ���� Ŀ�� �Ѵ�. // 2006-10-02 by cmkwon, �ϳ��� ���� ���� ��Ʈ�� �ִ� ����

#define EXCUTE_FILE_TYPE_SC_EXE				1
#define EXCUTE_FILE_TYPE_SC_LAUNCHER_ATM	2
#define EXCUTE_FILE_TYPE_SC_ATM				3
#define EXCUTE_FILE_TYPE_SC_WEBLAUNCHER		10


struct SEXCUTE_PARAMETER
{
	int			i_nExcuteFileType;
	char		o_szAccountName0[SIZE_MAX_ACCOUNT_NAME];
	char		o_szPreServerIP0[SIZE_MAX_IPADDRESS];
	int			o_nBirthYear;								// 2007-06-05 by cmkwon, ����⵵
	char		o_szPassword[SIZE_MAX_PASSWORD_MD5_STRING];				// 2008-12-18 by cmkwon, �Ϻ� Arario ��ó ���� - SEXCUTE_PARAMETER �� ��� ���� �߰�
	char		o_szSessionKey[SIZE_MAX_WEBLOGIN_AUTHENTICATION_KEY];	// 2008-12-18 by cmkwon, �Ϻ� Arario ��ó ���� - SEXCUTE_PARAMETER �� ��� ���� �߰�
	char		o_szSelectiveShutdownInfo[SIZE_MAX_SELECTIVE_SHUTDOWN_INFO];		// 2012-07-11 by hskim, ������ �˴ٿ�
};

extern int		g_nargvCount;
extern char		g_szArrargv[SIZE_MAX_ARGV_COUNT][SIZE_MAX_ARGV_PARAM_STRING_SIZE];

// 2008-04-25 by cmkwon, ���� ���/���� �߰��� �� �߰� �Ǿ�� �ϴ� ���� - [����-�ʼ�] C_Exe1, C_Exe2 ����� ���� �Ķ���� ó�� �Լ� ���� �߰�
Err_t GSetExcuteParameterList(int i_nParamCount, char ** i_ppszParamString);
Err_t GCheckExcuteParameterList(SEXCUTE_PARAMETER *io_pExeParam);
Err_t GCheckExcuteParameterList_Kor(SEXCUTE_PARAMETER *io_pExeParam);
Err_t GCheckExcuteParameterList_Kor2(SEXCUTE_PARAMETER *io_pExeParam);
Err_t GCheckExcuteParameterList_Eng(SEXCUTE_PARAMETER *io_pExeParam);
Err_t GCheckExcuteParameterList_Eng_Server_2(SEXCUTE_PARAMETER *io_pExeParam);		// 2007-12-21 by cmkwon, Gameforge(Europe) ������Ʈ �߰� - GCheckExcuteParameterList_Eng_Server_2() �߰�
Err_t GCheckExcuteParameterList_Viet(SEXCUTE_PARAMETER *io_pExeParam);
Err_t GCheckExcuteParameterList_Chn(SEXCUTE_PARAMETER *io_pExeParam);
Err_t GCheckExcuteParameterList_Tha(SEXCUTE_PARAMETER *io_pExeParam);		// 2008-05-02 by cmkwon, WinnerOnline_Tha �߰��ϱ� - 
Err_t GCheckExcuteParameterList_Rus(SEXCUTE_PARAMETER *io_pExeParam);		// 2008-05-29 by cmkwon, ���� ���� �߰�(Innova_Rus ���þƾ� �߰�) - 
Err_t GCheckExcuteParameterList_Tpe(SEXCUTE_PARAMETER *io_pExeParam);		// 2008-09-23 by cmkwon, ���� ���� �߰�(�븸 Netpower_Tpe) - 
Err_t GCheckExcuteParameterList_Jpn(SEXCUTE_PARAMETER *io_pExeParam);		// 2008-12-03 by cmkwon, ���� ���� �߰�(�Ϻ� Arario_Jpn) - 

///////////////////////////////////////////////////////////////////////////////
// 2007-05-09 by cmkwon
struct SREG_DATA_EXE_2
{
	VersionInfo		ClientVersion;
	VersionInfo		DVersion;		// DeleteFileListVersion
	VersionInfo		NVersion;		// NoticeFileVersion
// 2007-12-27 by cmkwon, �������� ��� ��� �߰� - �ػ� ���� �ý��� ����
//	int				WindowDegree;	// �ػ� ���� �ε���
	char			WindowDegree[SIZE_MAX_WINDOW_DEGREE_NAME];		// 2007-12-27 by cmkwon, �������� ��� ��� �߰� - �߰�
	char			BeforeAccountName[SIZE_MAX_ACCOUNT_NAME];
	char			SelectedServerGroupName[SIZE_MAX_SERVER_NAME];
	int				IsWindowMode;	// 2008-01-03 by cmkwon, �������� ���� �����ϱ� - SREG_DATA_EXE_2 �� �ʵ� �߰�

	void resetREG_DATA_EXE_2(void)
	{
		ClientVersion.SetVersion(0,0,0,0);
		DVersion.SetVersion(0,0,0,0);
		NVersion.SetVersion(0,0,0,0);
		// 2007-12-27 by cmkwon, �������� ��� ��� �߰� -
		//WindowDegree		= -1;
		MEMSET_ZERO(WindowDegree, SIZE_MAX_WINDOW_DEGREE_NAME);		// 2007-12-27 by cmkwon, �������� ��� ��� �߰� - �߰�
		MEMSET_ZERO(BeforeAccountName, SIZE_MAX_ACCOUNT_NAME);
		MEMSET_ZERO(SelectedServerGroupName, SIZE_MAX_SERVER_NAME);
		IsWindowMode		= FALSE;	// 2008-01-03 by cmkwon, �������� ���� �����ϱ� - 
	}
};
Err_t GLoadExe1VersionInfo(VersionInfo *o_pLauncherVerInfo, char *i_szVersionInfoFileName);
Err_t GLoadExe2VersionInfo(SREG_DATA_EXE_2 *o_pRegDataEXE2, char *i_szVersionInfoFileName);
Err_t GSaveExe1VersionInfo(VersionInfo *i_pLauncherVerInfo, char *i_szVersionInfoFileName);
Err_t GSaveExe2VersionInfo(SREG_DATA_EXE_2 *i_pRegDataEXE2, char *i_szVersionInfoFileName);

struct PCBANG_INFO
{// 2007-01-22 by dhjin, PC�� DB���� ����ü
	UID32_t		PCBangUID;
	char		ST_IP[SIZE_MAX_IPADDRESS];
	char		ED_IP[4];
	char		User_Id[SIZE_MAX_ACCOUNT_NAME];
	char		Branch_Name[50];
	char		Branch_RegNO[12];
	char		Branch_Tel[14];
	char		ZipCode[15];
	char		Addr_Sido[10];
	char		Addr_SiGuGun[20];
	char		Addr_Dong[100];
	char		Addr_Detail[50];
	BYTE		User_Level;				// 2007-06-25 by dhjin, PC�� ��� �߰�

	void ResetPCBANG_INFO(void)
	{
		MEMSET_ZERO(this, sizeof(PCBANG_INFO));
	}
	
	void SetPCBANG_INFO(UID32_t i_uidPCBangUID, char *i_szST_IP, char *i_szED_IP, char *i_szUser_Id, char *i_szBranch_Name, char *i_szBranch_RegNO, char *i_szBranch_Tel, char *i_szZipCode, char *i_szAddr_Sido, char *i_szAddr_SiGuGun, char *i_szAddr_Dong, char *i_szAddr_Detail, BYTE i_byUser_Level)
	{
		this->ResetPCBANG_INFO();

		PCBangUID		= i_uidPCBangUID;
		STRNCPY_MEMSET(ST_IP, i_szST_IP, SIZE_MAX_IPADDRESS);
		STRNCPY_MEMSET(ED_IP, i_szED_IP, 4);
		STRNCPY_MEMSET(User_Id, i_szUser_Id, SIZE_MAX_ACCOUNT_NAME);
		STRNCPY_MEMSET(Branch_Name, i_szBranch_Name, 50);
		STRNCPY_MEMSET(Branch_RegNO, i_szBranch_RegNO, 12);
		STRNCPY_MEMSET(Branch_Tel, i_szBranch_Tel, 14);
		STRNCPY_MEMSET(ZipCode, i_szZipCode, 15);
		STRNCPY_MEMSET(Addr_Sido, i_szAddr_Sido, 10);
		STRNCPY_MEMSET(Addr_SiGuGun, i_szAddr_SiGuGun, 20);
		STRNCPY_MEMSET(Addr_Dong, i_szAddr_Dong, 100);
		STRNCPY_MEMSET(Addr_Detail, i_szAddr_Detail, 50);
		User_Level		= i_byUser_Level;
	}
};
typedef vector<PCBANG_INFO>		vectorPCBANG_INFO;


//////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// 2007-04-17 by dhjin, �Ʒ����� ���õ� ����.
#define	ARENA_STATE_NONE				0	// �Ʒ����� ���õ� ���� �ϰ� ���� �ʴ�.
#define	ARENA_STATE_JOINING				1	// �Ʒ������� ������ ����, ���� ������ �� ���� �ʾҴ�.
#define	ARENA_STATE_READY				2	// �Ʒ��������� �� ���� �������� �غ� �ϷḦ ��ٸ��� ����.
#define	ARENA_STATE_READY_FINISH		3	// �Ʒ��������� �� ���� ������ �غ� �ϷḦ �������� (FieldIOCPSocket������ ���)
#define	ARENA_STATE_FIGHTING_WARREADY	101	// �Ʒ����濡 �����Ͽ� 1�а� ����ϴ� ����.
#define	ARENA_STATE_FIGHTING_WARING		102	// �Ʒ����濡�� �������� ����.
#define	ARENA_STATE_FIGHTING_WARFINISH	103	// �Ʒ����濡�� ������ ������ ������ �޴� ����, ������ �����ϱ� �������� ����.
// 2012-04-12 by jhseol, �Ʒ��� �߰����� - ������ �� ��ȣ �߰�
#define	ARENA_MAP_SELECT_ALL			0	
#define	ARENA_MAP_SELECT_RANDOM			9100
// end 2012-04-12 by jhseol, �Ʒ��� �߰����� - ������ �� ��ȣ �߰�

const char * GET_ARENA_STATE_STRING(BYTE i_byAState);

#define	SIZE_MAX_TEAM_PW			5

// 2007-04-17 by dhjin, �Ʒ��� ���.
#define	ARENAMODE_DEATHMATCH		1
#define	ARENAMODE_ROUND				2

// 2007-04-17 by dhjin, �ɸ��� ���� ��ũ �̸�.
#define	SIZE_MAX_LEVELRANK			40

// 2007-04-17 by dhjin, �������� ������ �� �ִ� �� �ִ� �� 
#define SIZE_MAX_TEAM				500

// 2007-04-19 by dhjin, �������� �����ϴ� �Ʒ��� ��
#define SIZE_MAX_ARENA_ROOM			80

// 2007-04-17 by dhjin, ���尡���� ������ ��
#define	ARENA_STAGE_D_START_LEVEL			11	// ���尡���� D�� ���۷��� 11~
#define ARENA_STAGE_D_END_LEVEL				31	// ���尡���� D�� ���������� 31
#define ARENA_STAGE_C_START_LEVEL			32	// ���尡���� C�� ���۷��� 32~
#define ARENA_STAGE_C_END_LEVEL				51	// ���尡���� C�� ���������� 51
#define ARENA_STAGE_B_START_LEVEL			52	// ���尡���� B�� ���۷��� 52~
#define ARENA_STAGE_B_END_LEVEL				71	// ���尡���� B�� ���������� 71
#define ARENA_STAGE_A_START_LEVEL			72	// ���尡���� A�� ���۷��� 72~
// 2010-03-03 by cmkwon, �ִ뷹������ ���� �Ʒ��� ����� ���� ���� - 110���� ����, ĳ���� �ִ뷹�� ����ø��� ���� �ʿ�
//#define ARENA_STAGE_A_END_LEVEL				100	// ���尡���� A�� ���������� 100
#define ARENA_STAGE_A_END_LEVEL				110	// ���尡���� A�� ���������� 100

#define ARENA_STAGE_START_LEVEL				25	// 2012-06-08 by jhseol, �Ʒ��� �߰�����part2 - �ɸ��� : �� ���巹��

// 2012-06-14 by jhseol, �Ʒ��� �߰�����part2 - �ɸ��� : �÷��� Ÿ��
#define ARENA_PLAY_TYPE_NO						0
#define ARENA_PLAY_TYPE_ATT						1
#define ARENA_PLAY_TYPE_DEF						2
#define ARENA_PLAY_TYPE_DOD						3
// end 2012-06-14 by jhseol, �Ʒ��� �߰�����part2 - �ɸ��� : �÷��� Ÿ��

// 2007-04-18 by dhjin, ������
#define STATE_ERROR							-1

// 2007-04-20 by dhjin, �Ʒ��� ���� ���� 
#define ARENA_ISSUE_WIN						1
#define ARENA_ISSUE_LOSE					2
#define ARENA_ISSUE_DRAW					3

// 2007-05-16 by dhjin, �Ʒ��� ���� ���� ����
#define ARENA_END_TYPE_POINT				1	// 2007-05-16 by dhjin, ����Ʈ�� 0�� �Ǿ� ������ ����
#define ARENA_END_TYPE_TIME					2	// 2007-05-16 by dhjin, ��� ���� �ð� �ʰ��� ������ ����
#define ARENA_END_TYPE_GIVEUP				3	// 2007-05-16 by dhjin, ��� ������ ���� �Ʒ��� �ʿ��� ���� ������ ����

// 2007-04-20 by dhjin, �Ʒ��� ƽ ����. 1��
#define ARENA_TICK_INTERVAL			1000

// 2011-06-22 by hskim, �缳 ���� ����
#define SECURITY_TICK_INTERVAL		1000

// 2012-07-11 by hskim, ������ �˴ٿ�
#define SELECTIVE_SHUTDOWN_TICK_INTERVAL		1000

// 2011-07-21 by hskim, ���� ���� ���� - ������ Timeout ó��
#define SPTOMP_TICK_INTERVAL		1000

// 2011-06-22 by hskim, �缳 ���� ����
#define STATISTICS_TICK_INTERVAL		600000		// 10 ��

// 2007-04-27 by dhjin, ��û�� �� ����� �� ���� �����ִ� ��
#define ARENA_MAX_REQUEST_TEAM				20

// 2007-05-09 by dhjin, �Ʒ��� �غ� ��ư ������ ���� : ��
#define ARENA_READYBUTTON_INTERVAL			3

// 2007-06-05 by dhjin, �Ʒ��� ��� �� ���� ��û ����
#define ARENA_REQUEST_TEAM_STATE_OUR		1	// 2007-06-05 by dhjin, ��� ����
#define ARENA_REQUEST_TEAM_STATE_JOINING	2	// 2007-06-05 by dhjin, ��� ��
#define ARENA_REQUEST_TEAM_STATE_OTHER		3	// 2007-06-05 by dhjin, ��� ��

///////////////////////////////////////////////////////////////////////////////
// 2007-04-17 by dhjin, Arena �ý��ۿ� �ʿ��� ����ü ����
struct SDBARENA_INFO
{// 2007-04-17 by dhjin, ti_ArenaInfo ��
	BYTE	ArenaMode;				// �Ʒ��� ��� 1 : DeathMatch, 2 : Round
	BYTE	ReqMemberNum;			// �� �ο� ����
	INT		PayInfluencePointWIN;	// �¸� ���¿��� ����Ǵ� ��������Ʈ��
	INT		PayInfluencePointLOSE;	// �й� ���¿��� ����Ǵ� ��������Ʈ��
	INT		PayWarPointWIN;			// �¸� ������ ����Ǵ� WP��
	INT		PayWarPointLOSE;		// �й� ������ ����Ǵ� WP��
//////////////////////////////////////////////////////////////////////////////
// 2012-05-23 by jhseol, �Ʒ��� �߰����� - �ּ� ���� ���� �ʵ� �߰�
	INT		DefaultPayWarPointWIN;	/// ����Ƚ�� �ʰ��� �⺻������ ���޵Ǵ� WP
	INT		DefaultPayWarPointLOSE;	/// ����Ƚ�� �ʰ��� �⺻������ ���޵Ǵ� WP
// end 2012-05-23 by jhseol, �Ʒ��� �߰����� - �ּ� ���� ���� �ʵ� �߰�
};
typedef vector<SDBARENA_INFO>	vectorSDBARENA_INFO;

struct SDBARENA_MAPINFO
{// 2007-04-17 by dhjin, ti_ArenaMapInfo �� 
	MapIndex_t 	ArenaMapIndex;			// �� �ε���
	BYTE 	ArenaMode;					// �Ʒ��� ��� 1 : DeathMatch, 2 : Round
	BYTE 	ReqMemberNum; 				// �� �ο� ����
	BYTE 	PlayLimitedTime;			// ��� ���� �ð�
	BYTE 	WINCondition;				// ��� �¸� ����
	INT		LvDSupplyItemNum1;				// �Ʒ��� ���� ���� ������1
	INT		LvDSupplyItemCount1;			// �Ʒ��� ���� ���� ������1 �� 
	INT		LvDSupplyItemNum2;				// �Ʒ��� ���� ���� ������2
	INT		LvDSupplyItemCount2;			// �Ʒ��� ���� ���� ������2 ��
	INT		LvDSupplyItemNum3;				// �Ʒ��� ���� ���� ������3
	INT		LvDSupplyItemCount3;			// �Ʒ��� ���� ���� ������3 ��
	// 2012-09-14 by jhseol, �Ʒ��� �߰����� part3 - �Ʒ��� ���� ������ �߰� (�Ʒ��� ���� ź�� ������ ī��)
	INT		LvDSupplyItemNum4;				// �Ʒ��� ���� ���� ������4
	INT		LvDSupplyItemCount4;			// �Ʒ��� ���� ���� ������4 ��
	// end 2012-09-14 by jhseol, �Ʒ��� �߰����� part3 - �Ʒ��� ���� ������ �߰� (�Ʒ��� ���� ź�� ������ ī��)
};
typedef vector<SDBARENA_MAPINFO>	vectorSDBARENA_MAPINFO;

struct SARENA_INFO
{// 2007-04-17 by dhjin, ������ ������ �ִ� ����.
	BYTE	ArenaMode;				// Arena ��� ����
	BYTE	State;					// Arena ���� ����
	BYTE	ShootingDown;			// Arena �濡�� ���߽�Ų ����
	BYTE	SufferingAttack;		// Arena �濡�� �ǰݴ��� ����
	BYTE	LostPoint;				// Arena �濡�� �ǰ� ������ �ʰ� ���� ī��Ʈ
	SHORT	SaveSP;					// Arena �� ���� �� SP
	SHORT	SaveEP;					// Arena �� ���� �� EP
	INT		TeamNum;				// Arena �� ��ȣ
	INT		DeathMatchRoomNum;		// Arena ������ġ �� ��ȣ
	BodyCond_t	SaveBodyCondition;	// Arena �� ���� �� BodyCondition
	float	SaveHP;					// Arena �� ���� �� HP
	float	SaveDP;					// Arena �� ���� �� DP
	ATUM_DATE_TIME	ReadyButtonClickTime;	// Arena �غ� �Ϸ� ��ư ���� �ð� ����, 3�� ������ �ʿ�
	BOOL	WatchState;				// Arena ���� ���� 0 : ���� ���°� �ƴϴ�. 1 : ���� ����				
	BOOL	Command;				// 2008-02-21 by dhjin, �Ʒ��� ���� - '/�Ʒ����̵�' ���ɾ� ������� �Ʒ��� ������ �°����� üũ ��Ʈ

	///////////////////////////////////////////////////////////////////////////////
	/// \fn			void ResetArenaInfo(void)
	/// \brief		
	/// \author		cmkwon
	/// \date		2007-05-14 ~ 2007-05-14
	/// \warning	
	///
	/// \param		
	/// \return		
	///////////////////////////////////////////////////////////////////////////////
	void ResetArenaInfo(void)
	{
		MEMSET_ZERO(this, sizeof(SARENA_INFO));
		TeamNum				= -1;
		DeathMatchRoomNum	= -1;
	}
	///////////////////////////////////////////////////////////////////////////////
	/// \fn			BOOL IsValidArenaState(void)
	/// \brief		
	/// \author		cmkwon
	/// \date		2007-05-14 ~ 2007-05-14
	/// \warning	
	///
	/// \param		
	/// \return		
	///////////////////////////////////////////////////////////////////////////////
	BOOL IsValidArenaState(void)
	{
		if(ARENA_STATE_NONE == State)
		{
			return FALSE;
		}

		if(0 > TeamNum
			&& 0 > DeathMatchRoomNum)
		{
			return FALSE;
		}

		return TRUE;
	}
};

struct SARENA_PAY_INFO
{// 2007-04-17 by dhjin, �Ʒ��� ���� ����
	INT		PayInfluencePointWIN;	// �¸� ���¿��� ����Ǵ� ��������Ʈ��
	INT		PayInfluencePointLOSE;	// �й� ���¿��� ����Ǵ� ��������Ʈ��
	INT		PayWarPointWIN;			// �¸� ������ ����Ǵ� WP��
	INT		PayWarPointLOSE;		// �й� ������ ����Ǵ� WP��
	//////////////////////////////////////////////////////////////////////////////
	// 2012-05-23 by jhseol, �Ʒ��� �߰����� - �ּ� ���� ���� �ʵ� �߰�
	INT		DefaultPayWarPointWIN;
	INT		DefaultPayWarPointLOSE;
	// end 2012-05-23 by jhseol, �Ʒ��� �߰����� - �ּ� ���� ���� �ʵ� �߰�
};

struct SARENA_MAP_MANAGER
{// 2007-05-02 by dhjin, �Ʒ��� �� ����
	MapIndex_t		ArenaMap;			// 2007-04-30 by dhjin, �Ʒ��� ��
	ChannelIndex_t	ArenaMapChannel;	// 2007-04-30 by dhjin, �Ʒ��� ä��
	BOOL			bArenaChannelSet;	// 2007-04-30 by dhjin, �Ʒ��� ä�� �Ҵ� ���� 0 : �Ҵ���� ����, 1 : �Ҵ��
};
typedef mt_vector<SARENA_MAP_MANAGER>				mtvectSARENA_MAP_MANAGER;

typedef mt_vector<ClientIndex_t>					mtvectorClientIndex_t;

struct SARENA_OTHER_TEAM_INFO
{// 2007-05-28 by dhjin, ����� ���� ���� �� Ŭ���̾�Ʈ���� ����
	BYTE ArenaMode;								// �Ʒ��� ��� 1 : DeathMatch, 2 : Round
	BYTE TeamSize;								// �� �ִ� �ο���
};
typedef vector<SARENA_OTHER_TEAM_INFO>				vectSARENA_OTHER_TEAM_INFO;

struct SARENA_GM_COMMAND_INFO_TEAM
{// 2007-05-28 by dhjin, /�Ʒ��� GM���ɾ� ���� ����
	BYTE 	ArenaMode;							// �Ʒ��� ��� 1 : DeathMatch, 2 : Round
	BYTE 	TeamState;							// ���� ����
	BYTE	Level;								// �� ����
	BYTE	MemberCount;						// �� �ִ� �ο���
	INT		CurrenMemberCount;					// ���� �� �ο���
};
typedef vector<SARENA_GM_COMMAND_INFO_TEAM>				vectSARENA_GM_COMMAND_INFO_TEAM;


///////////////////////////////////////////////////////////////////////////////
// 2007-05-11 by cmkwon, �̽��׸�ĸ�� �ý���
struct MYSTERY_ITEM_DROP
{
	INT				MysteryItemDropNum;				
	USHORT			ReqUnitKind;					// �ʿ���������
	BYTE			ReqMinLevel;					// �ʿ� ���� ����
	BYTE			ReqMaxLevel;					// �ʿ� ���� ����
	INT				DropItemNum;
	INT				MinCount;
	INT				MaxCount;
	Prob1000K_t		Probability;			// ���� Ȯ��(��밪���� ó����): 0 ~ 1000000
	Prob100K_t		PrefixProbability;		// ���λ簡 ���� Ȯ��, 0 ~ 100000
	Prob100K_t		SuffixProbability;		// ���̻簡 ���� Ȯ��, 0 ~ 100000
	USHORT			Period;					// ��Ű�ӽ� �Ⱓ, 2008-11-04 by dhjin, ��Ű�ӽ�
	INT				CountPerPeriod;			// �Ⱓ���� ����� �ִ� ������ ��, 2008-11-04 by dhjin, ��Ű�ӽ�
	INT				DropCount;				// �Ⱓ���� ���� ����� ������ ��, 2008-11-04 by dhjin, ��Ű�ӽ�
	ATUM_DATE_TIME	Starttime;				// ��Ű�ӽ� ���� �ð�, 2008-11-04 by dhjin, ��Ű�ӽ�
};
typedef multimap<INT, MYSTERY_ITEM_DROP>		mmapINT2MYSTERY_ITEM_DROP;		// 2007-05-14 by cmkwon
typedef mt_multimap<INT, MYSTERY_ITEM_DROP>		mtmapINT2MYSTERY_ITEM_DROP;		// 2008-11-10 by dhjin, ��Ű�ӽ� multimap -> mt_multimap���� ����
typedef vector<MYSTERY_ITEM_DROP*>				vectMYSTERY_ITEM_DROPPtr;			// 2007-05-14 by cmkwon

// 2008-11-04 by dhjin, ��Ű�ӽ�
struct LUCKYITEM_DROP_INFO
{
	BOOL			LuckItemUsing;
	USHORT			Period;
	UID64_t			MysteryItemDropNumUID;
	INT				MysteryItemDropNum;				
	INT				DropItemNum;
	INT				MinCount;
	INT				MaxCount;
	Prob100K_t		PrefixProbability;		// ���λ簡 ���� Ȯ��, 0 ~ 100000
	Prob100K_t		SuffixProbability;		// ���̻簡 ���� Ȯ��, 0 ~ 100000
};

///////////////////////////////////////////////////////////////////////////////
// 2007-05-28 by cmkwon
struct SRESOBJ_CHECKSUM
{
	char		szResObjFileName[SIZE_MAX_RESOBJ_FILE_NAME];
	int			nFileSize;
	// 2009-05-29 by cmkwon, Hash�˰����� �߰�(SHA256) - 
	//UINT		uiObjCheckSum;	
	BYTE		byDigest[32];		// 2009-05-29 by cmkwon, Hash�˰����� �߰�(SHA256) - 

	// 2009-05-29 by cmkwon, Hash�˰����� �߰�(SHA256) - 
	BOOL IsSame(int i_nLen, BYTE i_byCheckSum[32])
	{
		if(i_nLen != nFileSize)
		{
			return FALSE;
		}
		
		int i; for(i=0; i < 4 ;i++)
		{
			if(((INT64*)i_byCheckSum)[i] != ((INT64*)byDigest)[i])
			{
				return FALSE;
			}
		}

		return TRUE;
	}
};
typedef map<string, SRESOBJ_CHECKSUM>			mapstring2SRESOBJ_CHECKSUM;		// 2007-05-28 by cmkwon

//////////////////////////////////////////////////////////////////////////
// 2007-07-06 by dhjin, Tutorial
struct STUTORIAL_INFO
{// 2007-07-06 by dhjin, Tutorial ����
	INT			TutorialUID;					// Tutorial ��ȣ 
	INT			TutorialPayItem1;				// Tutorial ������ ��ȣ 
	INT			TutorialPayItemCount1;			// Tutorial ������ ��
	INT			TutorialPayItem2;				
	INT			TutorialPayItemCount2;
	INT			TutorialPayItem3;
	INT			TutorialPayItemCount3;
};
typedef vector<STUTORIAL_INFO>	vectSTutorialInfo;			// 2007-07-06 by dhjin
typedef vector<INT>				vectTutorial;				// 2007-07-06 by dhjin
// 2010-01-18 by cmkwon, ������ ���� Parameter �ߺ� üũ �ý��� ���� - �������� �̵�
//typedef vector<INT>				vectINT;					// 2008-01-31 by cmkwon, �ð����� ������ DB �� �߰� �� üũ - 

// 2008-01-31 by cmkwon, �ð����� ������ DB �� �߰� �� üũ - find_if() �Լ���
struct Sfind_if_INT
{
	Sfind_if_INT(int i_nValue): m_nFindValue(i_nValue){};
	bool operator()(INT i_nValue)
	{
		return i_nValue == m_nFindValue;
	}
	int m_nFindValue;
};


// 2007-07-09 by dhjin, �⺻ ����
#define FIRST_WEAPON_AGEAR					7000050
#define SECOND_WEAPON_AGEAR					7900440
#define FIRST_WEAPON_BGEAR					7001950
#define SECOND_WEAPON_BGEAR					7900000
#define FIRST_WEAPON_MGEAR					7001950
#define SECOND_WEAPON_MGEAR					7900000
#define FIRST_WEAPON_IGEAR					7001950
#define SECOND_WEAPON_IGEAR					7900000

// 2007-07-11 by dhjin, ���� ��ȯ �ð� ���� MS
#define TICK_CREATE_MONSTER_TERM			1000

//////////////////////////////////////////////////////////////////////////
// 2007-08-03 by dhjin, PC�� IP����Ʈ ������ ���õ� ����ü
struct SIPClassD
{
	UID32_t		PCBangUID;			// 2007-08-03 by dhjin, PC�� UID 
	BYTE		IPClassDStart;		// 2007-08-03 by dhjin, ���� IP Class D
	BYTE		IPClassDEnd;		// 2007-08-03 by dhjin, �� IP Class D
};
typedef vector<SIPClassD>					vectorSIPClassD;
typedef mt_map<DWORD, vectorSIPClassD>		mtmapDWORDvectorSIPClassD;

//////////////////////////////////////////////////////////////////////////
// 2007-08-13 by dhjin, OutPost ����
#define	OUTPOST_NORMAL		0x00
#define	OUTPOST_WARSTART	0x10
#define	OUTPOST_WARING		0x20
#define	OUTPOST_WAREND		0x30
#define	OUTPOST_RESETSTART	0x01
#define	OUTPOST_RESETING	0x02
#define	OUTPOST_RESETEND	0x03
#define IS_OUTPOST(x)		( (x & 0xFF) > 0 )
#define IS_OUTPOST_WAR(x)	( (x & 0xF0) > 0 )
#define IS_OUTPOST_RESET(x)	( (x & 0x0F) > 0 )
#define IS_OUTPOST_RESETING(x) ( (x &  OUTPOST_RESETING) == OUTPOST_RESETING)

//////////////////////////////////////////////////////////////////////////
// 2007-08-13 by dhjin, �������� ������, �������� ���������� ���� ���
#define	NOTICE_LEADER			1
#define	NOTICE_GUILDCOMMANDER	2

// 2007-08-13 by dhjin, �������� ���ڿ� ũ��
#define	SIZE_MAX_NOTICE			512

// 2007-11-06 by dhjin, �������� �¸��� ���� ������ 
#define	OUTPOST_PAY_ITEM		7010720	// ���޻��� ������
#define	OUTPOST_PAY_ITEM_COUNT	1		// ���޻��� ������ ��

//////////////////////////////////////////////////////////////////////////
// 2007-08-16 by dhjin, �������� ���� ����
struct	SOUTPOST_INFO
{
	BYTE			OutPostInfluence;						// �������� ���� ����
	BYTE			OutPostNextWarTimeSet;					// �������� ���� ���� �ð� ����
	INT				OutPostMapIndex;						// �������� �� ��ȣ
	INT				OutPostCityMapIndex;					// �������� ���� �� ��ȣ
	UID32_t			OutPostGuildUID;						// �������� ���� ����
	CHAR			OutPostGuildName[SIZE_MAX_GUILD_NAME];	// �������� ���� ���ܸ�
	ATUM_DATE_TIME	OutPostGetTime;							// �������� ���� ���� �ð�
	ATUM_DATE_TIME	OutPostNextWarTime;						// �������� ���� ���� �ð�
};
typedef vector<SOUTPOST_INFO>			vectSOutPostInfo;

// 2009-07-08 by cmkwon, ���� ���� ���� ��ġ �̵�(LocalizationDefineCommon.h) - 
//// 2007-08-16 by dhjin, �������� ���� define
//#define	OUTPOST_WARTIME					120	// ���������� �ð�, 120��
//#define OUTPOST_WARTIME_FOR_TESTSERVER	60	// 2008-10-29 by cmkwon, �׼��� ���������� 1�ð�(60��)���� ���� - 

// 2009-05-12 by cmkwon, (�Ϻ���û) �Ϻ��� ���� ������ �ֱ� 7�Ϸ� ���� - LocalizationDefineCommon.h �� ��ġ �̵�
//#define	OUTPOST_NEXTWARGAP				5	// 2008-10-22 by dhjin, �������� 3�� 10 -> 5�Ϸ� ���� // ���� ���������������� �� ��, 10�� 

#define	OUTPOST_RESET					5	// �������� ���� ��Ű�� �ð�, 1��
// 2013-12-16 by jhseol, ������ ��ȸ ���� ������ - ���� ������ ���� WP �߰�
#ifdef S_UPGRADE_INFLUENCE_POINT_RENEWAL_JHSEOL		// - ���� ������ ���� WP �߰�
#define	OUTPOST_PAY_WARPOINT			(600+400)	// 400WP �߰�
#define	OUTPOST_PAY_WARPOINT_BY_LOSE	(200+400)	// 400WP �߰�
#else
#define	OUTPOST_PAY_WARPOINT			600	// 2011-12-27 by hskim, EP4 [�뷱�� ����] // ���������� �¸� ���� ���� WarPoint
#define	OUTPOST_PAY_WARPOINT_BY_LOSE	200	// 2011-12-27 by hskim, EP4 [�뷱�� ����] // 2008-01-07 by dhjin, ���� ���� ���� - ���������� �й� ���� ���� WarPoint
#endif
// end 2013-12-16 by jhseol, ������ ��ȸ ���� ������ - ���� ������ ���� WP �߰�

//////////////////////////////////////////////////////////////////////////
// 2007-08-16 by dhjin, ���� ������, ������ ���� ����
struct	SCITYLEADER_INFO
{
	INT			MapIndex;					// �����Ǵ� ���� �� ��ȣ ex)1001 : ������ ���� ��
	BYTE		Influence;					// ����
	UID32_t		CharacterUID;				// ���� UID
	INT			ExpediencyFundCumulative;	// ���� �ǰ� ��
	INT			ExpediencyFund;				// ���� �ǰ� ��
	INT			ExpediencyFundRate;			// �ǰ�����, %����, 1000������ ��� 10 => 1%
	CHAR		Notice[SIZE_MAX_NOTICE];	// ��������
};
typedef vector<SCITYLEADER_INFO>		vectSCityLeaderInfo;

// 2007-08-16 by dhjin, �ǰ��� ���� define, �ǰ�����, %����, 1000������ ��� 10 => 1%
#define	EXPEDIENCYFUND_LEADER				10		// ���� ������ �ǰ�����
#define	EXPEDIENCYFUND_GUILDCOMMANDER		10		// �������� ���� ���� �ǰ�����
#define	EXPEDIENCYFUND_LEADER_OUTPOST		5		// �������� ���� ���� ������ �߰� �ǰ�����
#define	EXPEDIENCYFUND_LEADER_INFLUENCEWAR	2		// ���� ���� ���� �� �߰� ��� ����
#define EXPEDIENCYFUND_RATE_VALUE			1000	// �ǰ�����, %����, 1000������ ��� 10 => 1%

// 2007-08-16 by dhjin, �������� ���� define
#define	NOTICE_LEADER						1	// �������� ������
#define	NOTICE_GUILDCOMMANDER				2	// �������� �������� ������
#define	SIZE_MAX_NOTICE						512	// �������� ���ڿ� ũ��

// 2007-08-30 by dhjin, ������ ��������Ʈ ���� �ð� 		
#define STRATEGYPOINT_SUMMONTIME_BY_INFLUENCEBOSS	120 // ������ ��������Ʈ ���� �ð� 120��

// 2007-09-03 by dhjin, ��������Ʈ ���� �ð� �ٽ� ���� �� �����ߵǴ� Gap
#define STRATEGYPOINT_SUMMON_GAP_BY_INFLUENCEWAR	4	// �������� �� �����ߵǴ� GAP
#define STRATEGYPOINT_SUMMON_GAP_BY_OUTPOST			8	// �������� ���� �� �����ߵǴ� GAP

// 2007-09-04 by dhjin, ������ �ڷ���Ʈ ����
#define TELEPORT_BUILDING_TIME_SECOND				180   // ������ �ڷ���Ʈ�� ��������� �ð�(180��)

// 2007-09-05 by dhjin, �ڷ���Ʈ ���°�
#define TELEPORT_STATE_NOT_SUMMON					0	// �ڷ���Ʈ ��ȯ ���°� �ƴ� ��
#define TELEPORT_STATE_NONE							1	// �ڷ���Ʈ ���� ���°�
#define TELEPORT_STATE_READY						2   // ��������Ʈ�� �ı��Ǿ� �ڷ���Ʈ ��ġ�� ������ ����
#define TELEPORT_STATE_BUILDING						3   // �ڷ���Ʈ ���� ��
#define TELEPORT_STATE_COMPLETE						4	// �ڷ���Ʈ ��ġ�Ǿ� �ִ� ����

// 2007-09-05 by dhjin, Monster ClickEvent �ʵ� ��
#define MONSTER_CLICKEVENT_OUTPOST_RESET			1	// �������� �߾�ó����ġ Ŭ�� �̺�Ʈ (����)
#define MONSTER_CLICKEVENT_TELEPORT_BUILDING		2	// �ڷ���Ʈ Ŭ�� �̺�Ʈ (����)

struct STELEPORT_INFO_BUILDING
{// 2007-09-07 by dhjin, ���� �����Ǿ� �ִ� �ڷ���Ʈ ����
	BOOL			bBuilded;		// �ڷ���Ʈ�� �ϼ��Ǿ����� TRUE, �������̶�� FALSE
	INT				MapInfluence;	// ���� 
	MapIndex_t		MapIndex;
	ATUM_DATE_TIME	BuildStartTime;
};

// 2007-10-06 by cmkwon, �������� 2���� ȣĪ�� �ٸ��� ���� -
char *GetLeader8SubLeaderString(BYTE i_byInflTy, USHORT i_usRace);

// 2007-10-10 by dhjin, �ɹ��� ���� ������� ���� %
#define	MEMBERSHIP_DISCOUNT_WARPFEE		50		// 2007-10-10 by dhjin, 50%

// 2007-10-16 by cmkwon, �α� �߰� - OutPost.h ���Ͽ� �ִ����� ����� �̵���
struct SOutPostProtectorDamage
{
	BYTE	Influence;
	UID32_t	GuildUID;
	CHAR 	GuildName[SIZE_MAX_GUILD_NAME];
	float	Damage;
};
typedef	mt_vector<SOutPostProtectorDamage>		mtvectSOutPostProtectorDamage;

// 2007-10-24 by cmkwon, ���� ���� ��ȣȭ - �߰���
extern GAME_SERVER_INFO_FOR_ADMIN g_arrGameServers[];
extern void GDecryptGameServerInfoByXOR(void);

// 2007-10-30 by cmkwon, ���º� ���Ǿƿ� �̺�Ʈ ���� -
extern char *GetDayOfWeekString(int i_nDayOfWeek);

// 2007-10-30 by cmkwon, ���º� ���Ǿƿ� �̺�Ʈ ���� -
extern int GetArrayIndexByInfluenceType(BYTE i_byInflTy);
extern BYTE GetInfluenceTypeByArrayIndex(int i_nArrIdx);


//////////////////////////////////////////////////////////////////////////
// 2007-10-26 by dhjin, Poll ����

struct SACTION_BY_LEVEL_DB
{// 2007-10-26 by dhjin, ������ ���� ���� �ൿ��
	BYTE		Level;
	INT			PollPoint;		// ������ ���� ��ǥ ����
};
typedef vector<SACTION_BY_LEVEL_DB>		vectSACTION_BY_LEVEL_DB;

struct SPOLLDATE_DB
{// 2007-10-26 by dhjin, ���� ����
	ATUM_DATE_TIME	ApplicationStartDate;		// �ĺ� ��û ���� ��
	ATUM_DATE_TIME	ApplicationEndDate;			// �ĺ� ��û ������ ��
	ATUM_DATE_TIME	VoteStartDate;				// ��ǥ ���� ��
	ATUM_DATE_TIME	VoteEndDate;				// ��ǥ ������ ��
	ATUM_DATE_TIME	Election;					// ������
};

struct SVOTER_LIST
{// 2007-10-26 by dhjin, ��ǥ�� ����Ʈ 
	UID32_t		AccountUID;						//	��ǥ�� ���� UID
	UID32_t		CharacterUID;					//	��ǥ�� UID
	INT			LeaderCandidateNum;				//	��ǥ�ڰ� ��ǥ�� �ĺ��� ��ȣ
};
typedef mt_vector<SVOTER_LIST>			mtvectSVOTER_LIST;

#define SIZE_MAX_CAMPAIGNPROMISES				512

struct SLEADER_CANDIDATE
{// 2007-10-26 by dhjin, ������ �ĺ���
	BYTE			Influence;									//  ������ �ĺ��� ����
	BOOL			DeleteCandidate;							//  �̹� ���� �Ⱓ�� �ĺ� Ż�� �ߴ��� ����, TRUE = Ż��
	INT				LeaderCandidateNum;							//	������ �ĺ� ��ȣ
	INT				PollCount;									//  ������ �ĺ� ��ǥ��
	UID32_t			AccountUID;									//	������ �ĺ� ���� UID
	UID32_t			CharacterUID;								//	������ �ĺ� UID
	UID32_t			GuildUID;									//  ������ �ĺ� ��� UID
	CHAR			CharacterName[SIZE_MAX_CHARACTER_NAME];		//  ������ �ĺ� �̸�
	CHAR			GuildName[SIZE_MAX_GUILD_NAME];				//  ������ �ĺ� ����
	CHAR			CampaignPromises[SIZE_MAX_CAMPAIGNPROMISES];//  ������ �ĺ� ����	
};
typedef mt_vector<SLEADER_CANDIDATE>		mtvectSLEADER_CANDIDATE;

#define LEADERCANDIDATE_REQUIRE_LEVEL			60
#define LEADERCANDIDATE_REQUIRE_PROPENSITY		1000
#define LEADERCANDIDATE_REQUIRE_GUILDMEMBERNUM  1		// 2007-11-28 by dhjin, ���ܿ� �ο� üũ ���� - ��ȹ ��û
#define LEADERCANDIDATE_REQUIRE_GUILDFAME		1000
#define LEADERVOTE_REQUIRE_LEVEL				11

///////////////////////////////////////////////////////////////////////////////
// 2007-11-28 by cmkwon, �����ý��� ���� -
#define SIZE_MAX_NOTIFY_MSG_STRING				512		// 2007-11-28 by cmkwon, ��Ʈ�� �ִ� ����
#define NOTIFY_MSG_TYPE_TEXT					1		// �����޽���Ÿ�� - �ϴ� ��Ʈ��
#define NOTIFY_MSG_TYPE_RECV_GIFT				2		// �����޽���Ÿ�� - ������ ���� ���� �޽���
struct SNOTIFY_MSG		// 2007-11-28 by cmkwon, �����ý��� ���� -
{
	UID64_t			NotifyMsgUID;				// 
	UID32_t			CharacterUID;				// �����޽��� ���� ĳ���� UID, 0 �̸� ��� ĳ���Ϳ��� ����(0 �ΰ��� ������ ���� �� ����)
	BYTE			NotifyMsgType;				// NOTIFY_MSG_TYPE_XXX
	char			NotifyMsgString[SIZE_MAX_NOTIFY_MSG_STRING];	// �����޽��� ��Ʈ��
	UID32_t			SenderCharacterUID;								// �����޽��� ������ CharacterUID
	char			SenderCharacterName[SIZE_MAX_CHARACTER_NAME];	// �����޽��� ������ CharacterName
	ATUM_DATE_TIME	CreateTime;										// �����޽��� DB�� ������ �ð�
};
typedef mt_vector<SNOTIFY_MSG>		mtvectSNOTIFY_MSG;				


//////////////////////////////////////////////////////////////////////////
// 2007-12-26 by dhjin, �Ʒ��� ���� - �Ʒ��� ���� ����
struct SARENA_SERVER_INFO
{
	BOOL			ArenaFieldServerCheck;		// �Ʒ��� �ʵ� �������� üũ, TRUE=>�Ʒ����ʵ弭��	
	char			ArenaServerName[SIZE_MAX_SERVER_NAME];
	INT				ArenaServerID;
	char			ArenaFieldServerIP[SIZE_MAX_IPADDRESS];
	int				ArenaFieldServerPort;
	char			ArenaIMServerIP[SIZE_MAX_IPADDRESS];
	int				ArenaIMServerPort;	
};

struct SAFS_NEED_MFSINFO
{// 2008-01-03 by dhjin, �Ʒ��� ���� - MFS�� AFS �ɸ��� ���� ��Ī ����
	ClientIndex_t	MFSClientIdx;
	UID32_t			MFSCharacterUID;
	INT				MFSServerID;
};


// 2014-01-27 by bckim, ���� Ʈ��
struct SBUGTRAP_SERVER_INFO
{
	BOOL		BugTrapServerFlag;
	BYTE		BugTrapServerType;
	char		BugTrapServerIP[SIZE_MAX_IPADDRESS];
	char		LoginID[SIZE_MAX_ACCOUNT_NAME];
	char		LoginPW[SIZE_MAX_PASSWORD];
	char		ServerNationInfo[SIZE_MAX_SERVER_NAME];	

	char		ServerGroupName0[SIZE_MAX_SERVER_NAME];	
	char		GamePublisher[SIZE_MAX_GAME_PUBLISHER_NAME];
	int			nLanguageType;
};

typedef SBUGTRAP_SERVER_INFO	MSG_FC_CONNECT_BUGTRAP_SERVER_INFO;
// End. 2014-01-27 by bckim, ���� Ʈ��




#define	JAMBOREE_SERVER_ID			10080			// 2008-03-05 by dhjin, �Ʒ��� ���� - ��ȸ ���� ID

//////////////////////////////////////////////////////////////////////////
// 2008-03-24 by dhjin, ���� ���� ǥ�� ��ȹ�� - 
#define MS_WAR_HP_RATE					10				// 2008-03-26 by dhjin, ���� ���� ǥ�� ��ȹ�� - ���� HP �����ִ� ����
#define MS_WAR_MIN_HP_RATE				0				// 2008-03-26 by dhjin, ���� ���� ǥ�� ��ȹ�� - ���� HP �����ִ� ����HP ����

INT CalcGradeByRate(float i_nMaxValue, float i_nValue, INT i_nRate); // 2008-03-24 by dhjin, ���� ���� ǥ�� ��ȹ�� - ������ ���� ����� ����Ѵ�.

// 2008-03-24 by dhjin, ���� ���� ǥ�� ��ȹ�� - ��Ʈ �÷��� ����
#define MS_WAR_OPTION_TYPE_UNKNOWN					(USHORT)0x0000	// �˼� ����
#define MS_WAR_OPTION_TYPE_NONE						(USHORT)0x0001	// 1 - ���� ���� ǥ�� ���� �ȵ�
#define MS_WAR_OPTION_TYPE_ATT_ACTIVATED			(USHORT)0x0002	// 2 - (��) Ȱ��ȭ �Ϸ� ǥ��
#define MS_WAR_OPTION_TYPE_ATT_ACTIVE				(USHORT)0x0004	// 4 - (��) Ȱ��ȭ ���� �� ǥ��
#define MS_WAR_OPTION_TYPE_ATT_ACTIVE_TIME			(USHORT)0x0008	// 8 - (��) Ȱ��ȭ ���� �ð� ǥ��
#define MS_WAR_OPTION_TYPE_ATT_TELEPORT_HP			(USHORT)0x0010	// 16 - (��) �ڷ���Ʈ HP ǥ��
#define MS_WAR_OPTION_TYPE_ATT_STRATEGYPOINT_LIVE	(USHORT)0x0020	// 32 - (��) ��������Ʈ �������� ǥ��
#define MS_WAR_OPTION_TYPE_DEF_STRATEGYPOINT_HP		(USHORT)0x0040	// 64 - (��) ��������Ʈ HP ǥ��
#define MS_WAR_OPTION_TYPE_DEF_STRATEGYPOINT_LIVE	(USHORT)0x0080	// 128 - (��) ��������Ʈ �������� ǥ��
#define MS_WAR_OPTION_TYPE_LEADER					(USHORT)0x0100	// 256 - ������ ����
		
#define IS_MS_WAR_OPTION_TYPE(_CurrentOption, _CompareOption)   ((_CurrentOption & _CompareOption) != 0)

struct MSWARINFO_DISPLAY
{// 2008-03-26 by dhjin, ���� ���� ǥ�� ��ȹ�� - �������� �ʿ��� ���� ǥ�� ����Ÿ
	MapIndex_t		MapIndex;
	INT				MapInfluenceType;
	BYTE			Belligerence;
	INT				HPRate;
	INT				TelePortState;
	ATUM_DATE_TIME  TelePortBuildingStartTime;
	ATUM_DATE_TIME  TelePortBuildingEndTime;
	BYTE			DisplatType;	// 2013-08-14 by jhseol, ������ ������ - ��� Ÿ�� (0:����, 1:�Ϲ� ������)
};
typedef vector<MSWARINFO_DISPLAY>		vectMSWARINFO_DISPLAY;

enum EN_MSWARINFO_MODIFY_TYPE
{// 2008-03-27 by dhjin, ���� ���� ǥ�� ��ȹ�� - �� ���� ǥ�� �����Ǵ� Ÿ��
	T_MSWARINFO_MODIFY_UNKNOWN					= 0,		// �˼� ����
	T_MSWARINFO_MODIFY_HPRATE					= 1,		// HP��� ����
	T_MSWARINFO_MODIFY_CREATE_TELEPORT			= 2,		// Teleport ����
	T_MSWARINFO_MODIFY_CHANGE_TELEPORT_STATE	= 3			// Teleport ���°� ����
};

//////////////////////////////////////////////////////////////////////////
// 2008-04-01 by dhjin, ����, ������ ����â ��ȹ�� - 
struct SMSWAR_INFO_RESULT
{// 2008-04-01 by dhjin, ������ ��������
	BYTE			AttInfluence;
	INT				MonsterUID;
	INT				ContributionPoint;
	ATUM_DATE_TIME	MSWarStartTime;
	ATUM_DATE_TIME	MSWarEndTime;
	BYTE			WinInfluence;
};
typedef vector<SMSWAR_INFO_RESULT>		vectSMSWAR_INFO_RESULT;

struct SSPWAR_INFO_RESULT
{// 2008-04-01 by dhjin, ������ ��������
	BYTE			AttInfluence;
	INT				SPSummonMapIndex;
	ATUM_DATE_TIME	SPWarStartTime;
	ATUM_DATE_TIME	SPWarEndTime;
	BYTE			WinInfluence;
	BYTE			SPLevel;			// 2013-08-14 by jhseol, ������ ������ - ������ ��� �α׶� ���� ���� ����
};
typedef vector<SSPWAR_INFO_RESULT>		vectSSPWAR_INFO_RESULT;
typedef SSPWAR_INFO_RESULT				MSG_FC_INFO_SPWARINFO_RESULT_OK;

///////////////////////////////////////////////////////////////////////////////
// 2008-04-16 by cmkwon, ���� ��� �� ���� ��ȯ �̺�Ʈ �ý��� ���� - 
typedef UINT32 ExceptMon_t;
#define EXCEPTMON_OBJECT_MONSTER_MASK		(ExceptMon_t)0x00000001			// ������Ʈ ���� MonsterForm ���� 8,9,10
#define EXCEPTMON_INFLUENCE_TYPE_MASK		(ExceptMon_t)0x00000002			// ������ ���� Belligerence
#define EXCEPTMON_BELL_NOTATTACK_MASK		(ExceptMon_t)0x00000004			// ���� ������ ���� ���� Belligerence ���� 4�� ����

struct SEVENT_MONSTER
{
	INT					EventMonsterUID;			
	INT					ServerGroupID;				// ServerGroupID ( 0�̸� ��� �������� ����, 0�� �ƴϸ� �ش� �������� ����)
	ATUM_DATE_TIME		StartDateTime;				// EventMonster ���� ��¥�ð�
	ATUM_DATE_TIME		EndDateTime;				// EventMonster ���� ��¥�ð�
	MapIndex_t			SummonerMapIndex;			// ��ȯ�Ǵ� ���ε���(0�̸� ���ʿ��� ��ȯ��, 0�� �ƴϸ� ������ �ʿ����� ��ȯ��)
	BYTE				SummonerReqMinLevel;		// ��ȯ�ϴ� ������ �ּ� ���� üũ(0�̸� üũ���� ����)
	BYTE				SummonerReqMaxLevel;		// ��ȯ�ϴ� ������ �ְ� ���� üũ(0�̸� ��ũ���� ����)
	ExceptMon_t			SummonerExceptMonster;		// ��ȯ�ϴ� ���� ���� üũ  Bit Flag
	INT					SummonMonsterNum;			// ��ȯ�Ǵ� MonsterUniqueNumber
	INT					SummonMonsterCount;			// ��ȯ�� ��ȯ�Ǵ� ���� ����
	INT					SummonDelayTime;			// ���� ��� �� ��ȯ���� �ɸ��� �����ð�(����:��)
	Prob10K_t			SummonProbability;			// ��ȯ ���� Ȯ��(0~10000)
}; 
typedef mt_vector<SEVENT_MONSTER>				mtvectSEVENT_MONSTER;

struct SSUMMON_EVENT_MONSTER
{
	BOOL				IsSummonChecked;			// ��ȯ ���� üũ �÷���
	INT					SummonMonsterNum;			// ��ȯ�Ǵ� MonsterUniqueNumber
	INT					SummonMonsterCount;			// ��ȯ�� ��ȯ�Ǵ� ���� ����
	INT					SummonDelayTime;			// ���� ��� �� ��ȯ���� �ɸ��� �����ð�(����:��)
	Prob10K_t			SummonProbability;			// ��ȯ ���� Ȯ��(0~10000)	
	
	inline SSUMMON_EVENT_MONSTER& operator=(const SEVENT_MONSTER& rhs)
	{
		this->SummonMonsterNum		= rhs.SummonMonsterNum;
		this->SummonMonsterCount	= rhs.SummonMonsterCount;
		this->SummonDelayTime		= rhs.SummonDelayTime;
		this->SummonProbability		= rhs.SummonProbability;
		return *this;
	}
};
typedef mt_vector<SSUMMON_EVENT_MONSTER>		mtvectSSUMMON_EVENT_MONSTER;


///////////////////////////////////////////////////////////////////////////////
// 2008-04-29 by cmkwon, ������ ���� DB�� �߰�(�ű� ���� ĳ���� ���� ���� �ý����߰�) - 
struct SDBSERVER_GROUP
{
	int				ServerGroupID;
	char			ServerGroupName[SIZE_MAX_SERVER_NAME];
	int				LimitUserCount;
	BOOL			LockCreateCharacterForNewAccount;
};

//////////////////////////////////////////////////////////////////////////
// 2008-04-15 by dhjin, EP3 ���� �ý��� - 
#define	LETTER_PASSED_RANGE_DAY		14			// 2008-04-29 by dhjin, EP3 ���� �ý��� - ���� ���� �Ⱓ, ���� ��
#define	SIZE_MAX_LETTER_TITLE		40		// 2008-04-15 by dhjin, EP3 ���� �ý��� - ���� ����
#define	SIZE_MAX_LETTER_CONTENT		1000		// 2008-04-15 by dhjin, EP3 ���� �ý��� - ���� ����
struct SLETTER_INFO
{
	UID64_t			LetterUID;
	UID32_t			RecvCharacterUID;
	CHAR			SendCharacterName[SIZE_MAX_CHARACTER_NAME];
	ATUM_DATE_TIME  SendDate;
	BOOL			CheckRead;
	CHAR			Title[SIZE_MAX_LETTER_TITLE];
	CHAR			Content[SIZE_MAX_LETTER_CONTENT];
};
typedef vector<SLETTER_INFO>			vectSLETTER_INFO;

// 2008-06-03 by cmkwon, AdminTool, DBTool ���� ������ �˻��� �޺��ڽ����� �˻� ��� �߰�(K0000143) - 
char *StringCullingForValidChar(char *i_szSource, int i_nCullingSize);

//////////////////////////////////////////////////////////////////////////
// 2008-05-27 by dhjin, EP3 - ���� ���� ���� - ���� ������ ����
#define	GUILDINTRODUCTION_PASSED_RANGE_DAY		5			// 2008-05-27 by dhjin, EP3 - ���� ���� ���� - ���� ������ ����
struct SGUILD_INTRODUCTION
{
	char			IntroductionContent[SIZE_MAX_NOTICE];
	ATUM_DATE_TIME	RegDate;
};

struct SGUILD_APPLICANT_INFO
{
	UID32_t		CharacterUID;
	char		CharacterName[SIZE_MAX_CHARACTER_NAME];
	USHORT		UnitKind;
	BYTE		Level;				
};
typedef vector<SGUILD_APPLICANT_INFO>	vectSGUILD_APPLICANT_INFO;

struct SGUILD_SEARCH_INTRODUCTION
{// 2008-05-27 by dhjin, EP3 - ���� ���� ���� - ���� �Ұ� �˻�
	UID32_t			GuildUID;
	char			GuildName[SIZE_MAX_GUILD_NAME];
	ATUM_DATE_TIME	WriteDate;
	char			GuildIntroduction[SIZE_MAX_NOTICE];
	char			CharacterName[SIZE_MAX_CHARACTER_NAME];
};
typedef vector<SGUILD_SEARCH_INTRODUCTION>	vectSGUILD_SEARCH_INTRODUCTION;

//////////////////////////////////////////////////////////////////////////
// 2008-06-02 by dhjin, EP3 ���� ���� - 
#define ITEM_DISTRIBUTE_TYPE_DAMAGE			0	// 2008-06-02 by dhjin, EP3 ���� ���� - ���� ����	
#define ITEM_DISTRIBUTE_TYPE_ORDER			1	// 2008-06-02 by dhjin, EP3 ���� ���� - ���� ���� 
#define ITEM_DISTRIBUTE_TYPE_RANDOM			2	// 2008-06-02 by dhjin, EP3 ���� ���� - ���� ����

#define PARTY_JOIN_TYPE_INVITE_MASTER		0	// 2008-06-02 by dhjin, EP3 ���� ���� - ������ �ʴ� ���� ��� 
#define PARTY_JOIN_TYPE_FREE				1	// 2008-06-02 by dhjin, EP3 ���� ���� - ���� ���� ���

#define SIZE_MAX_PARTY_NAME					32	// 2008-06-02 by dhjin, EP3 ���� ���� - ��Ƽ �̸� �ִ� ����

#define SIZE_MAX_RECOMMENDATION				5	// 2008-06-04 by dhjin, EP3 ���� ���� -  ��õ �ɸ��� ���� �ִ� ��

struct SPARTY_INFO
{// 2008-06-02 by dhjin, EP3 ���� ���� - ���� ����
	BYTE		PartyInfluence;
	char		PartyName[SIZE_MAX_PARTY_NAME];
	BYTE		PartyJoinType;
	BYTE		ExpDistributeType;
	BYTE		ItemDistributeType;
	BOOL		PartyLock;
	CHAR		PartyPW[SIZE_MAX_TEAM_PW];
	INT			MinLevel;
	INT			MaxLevel;
	BYTE		FormationType;
	BYTE		IsAppliedFormationSkill;	// 2009-08-03 by cmkwon, EP3-4 ���� ���� ��ų ���� - 
};

//////////////////////////////////////////////////////////////////////////
// 2008-06-09 by dhjin, EP3 ä�ù� -
#define SIZE_MAX_CHATROOM_NAME				34		// 2008-06-09 by dhjin, EP3 ä�ù� - ä�ù� �̸� �ִ� ��	
#define SIZE_MAX_CHATROOM_COUNT				1000	// 2008-06-16 by dhjin, EP3 ä�ù� - ä�ù� �ִ� ��

//////////////////////////////////////////////////////////////////////////
// 2008-06-20 by dhjin, EP3 ���������ɼ� -
#define USER_INFO_OPTION_SECRET_LEVEL				(USHORT)0x0001			// 2008-06-23 by dhjin, EP3 ���������ɼ� - ��� (�Ϲ�)
#define USER_INFO_OPTION_SECRET_POSITION			(USHORT)0x0002			// 2008-06-23 by dhjin, EP3 ���������ɼ� - ��ġ (�Ϲ�)
#define USER_INFO_OPTION_SECRET_PROPENSITY			(USHORT)0x0004			// 2008-06-23 by dhjin, EP3 ���������ɼ� - ���� (�Ϲ�)
#define USER_INFO_OPTION_SECRET_GUILD				(USHORT)0x0008			// 2008-06-23 by dhjin, EP3 ���������ɼ� - �Ҽ� (�Ϲ�)
#define USER_INFO_OPTION_SECRET_LASTLOGIN			(USHORT)0x0010			// 2008-06-23 by dhjin, EP3 ���������ɼ� - ���� ������ (�Ϲ�)
#define USER_INFO_OPTION_SECRET_ITEMINFO			(USHORT)0x0080			// 2012-07-12 by isshin ���۹̸����� On / Off ���	// EP4 ���������ɼ� - ������ ���� (�Ϲ�)
#define USER_INFO_OPTION_SECRET_GUILD_LEVEL			(USHORT)0x0100			// 2008-06-23 by dhjin, EP3 ���������ɼ� - ��� (����)
#define USER_INFO_OPTION_SECRET_GUILD_POSITION		(USHORT)0x0200			// 2008-06-23 by dhjin, EP3 ���������ɼ� - ��ġ (����)
#define USER_INFO_OPTION_SECRET_GUILD_PROPENSITY	(USHORT)0x0400			// 2008-06-23 by dhjin, EP3 ���������ɼ� - ���� (����)
#define USER_INFO_OPTION_SECRET_GUILD_GUILD			(USHORT)0x0800			// 2008-06-23 by dhjin, EP3 ���������ɼ� - �Ҽ� (����)
#define USER_INFO_OPTION_SECRET_GUILD_LASTLOGIN		(USHORT)0x1000			// 2008-06-23 by dhjin, EP3 ���������ɼ� - ���� ������ (����)
#define USER_INFO_OPTION_SECRET_GUILD_ITEMINFO		(USHORT)0x8000			// 2012-07-12 by isshin ���۹̸����� On / Off ���	// EP4 ���������ɼ� - ������ ���� (����)
#define USER_INFO_OPTION_MISSIONMASTER				(USHORT)0x2000			// 2008-12-08 by dhjin, �̼Ǹ����� - ������ �̼� ������ ������ �ߴ����� ���� ����
#define USER_INFO_OPTION_ITEMINFO_DELETE_ALL_MASK	(USHORT)0x7F7F		// 2012-10-17 by jhseol, ���� �̸����� ������ ON ��Ű�� - ���� �̸����⸸ ���� �� ����ũ

struct SUSER_INFO_OPTION
{// 2008-06-20 by dhjin, EP3 ���������ɼ� -
	BYTE				PilotFace;
	char				CharacterName[SIZE_MAX_CHARACTER_NAME];
	USHORT				UnitKind;
	UID32_t				GuildUID;
	char				GuildName[SIZE_MAX_GUILD_NAME];
	BYTE				Level;
	MAP_CHANNEL_INDEX	MapChannelIndex;
	INT					Propensity;
	ATUM_DATE_TIME		LastStartedTime;
	INT					SecretInfoOption;
	char				NickName[SIZE_MAX_CHARACTER_NAME];			// 2009-02-12 by cmkwon, EP3-3 ���巩ŷ�ý��� ���� - 
};

//////////////////////////////////////////////////////////////////////////
// 2008-08-18 by dhjin, 1�� �� �ý��� ��ȹ��
#define INTERVAL_SYSTEM_MS			200   

//////////////////////////////////////////////////////////////////////////
// 2008-08-25 by dhjin, �±� PC�� IP���� �ε�
#define MinPCBangMinTick			10
#define MaxPCBangMinTick			1440


typedef vector<MapIndex_t>			vectMapIndexList;		// 2008-09-10 by cmkwon, ���վƷ��� �ʼ���(map.cfg) ���� ���� - 

//////////////////////////////////////////////////////////////////////////
// 2008-10-13 by dhjin, ������ ���� ���� ���� üũ �߰�.
#define GuildCommanderMinLevel		20

//////////////////////////////////////////////////////////////////////////
// 2008-11-10 by dhjin, ��Ű�ӽ�
struct SLUCKY_MACHINE
{
	INT			BuildingIndex;
	BYTE		MachineKind;		// 2009-03-03 by dhjin, ��Ű�ӽ� ������
	INT			MachineNum;			// 2009-03-03 by dhjin, ��Ű�ӽ� ������
	INT			CoinItemNum;
	BYTE		SlotNum;			// 2009-03-03 by dhjin, ��Ű�ӽ� ������
	INT			SlotProbability;
	INT			MysteryItemDropNum;
};
typedef vector<SLUCKY_MACHINE>		vectSLUCKY_MACHINE;
typedef vector<SLUCKY_MACHINE*>		vectSLUCKY_MACHINEPtr;	// 2010-04-20 by cmkwon, �ű� ��Ű �ӽ� ���� - ���� �ҽ� ���� - 

#define MaxPayLuckyMachineItem		3			// �ִ� ���� ī��Ʈ(MAX_LUCKY_MACHINE_SLOT)�� ���� �ǹ̷� ���

//////////////////////////////////////////////////////////////////////////
// 2008-12-08 by dhjin, �̼Ǹ�����
#define SIZE_MAX_MISSIONMASTER_HELP_COUNT	5

//////////////////////////////////////////////////////////////////////////
// 2008-12-23 by dhjin, ���� ���� �߰���
#define	BGEAR_WAR_CONTRIBUTION		0.7f
#define	IGEAR_WAR_CONTRIBUTION		1
#define	MGEAR_WAR_CONTRIBUTION		3
#define	AGEAR_WAR_CONTRIBUTION		1	
#define PAY_WAR_CONTRIBUTION_BY_BOSS				2000000
#define PAY_WAR_CONTRIBUTION_BY_OUTPOST				1000000
#define PAY_WAR_CONTRIBUTION_BY_STRATEGYPOINT		500000
#define PAY_WAR_CONTRIBUTION_LEADER_BY_BOSS			200
#define PAY_WAR_CONTRIBUTION_1_GUILD_BY_BOSS		100
#define PAY_WAR_CONTRIBUTION_2_GUILD_BY_BOSS		80
#define PAY_WAR_CONTRIBUTION_3_GUILD_BY_BOSS		50
#define PAY_WAR_CONTRIBUTION_1_GUILD_BY_BOSS_PLUS	30000000
#define PAY_WAR_CONTRIBUTION_2_GUILD_BY_BOSS_PLUS	20000000
#define PAY_WAR_CONTRIBUTION_3_GUILD_BY_BOSS_PLUS	10000000
#define PAY_TYPE_BOSS				(BYTE)0
#define PAY_TYPE_OUTPOST			(BYTE)1
#define PAY_TYPE_STRATEGYPOINT		(BYTE)2
#define PAY_TYPE_BOSS_LEADER		(BYTE)10
#define PAY_TYPE_BOSS_1_GUILD		(BYTE)11
#define PAY_TYPE_BOSS_2_GUILD		(BYTE)12
#define PAY_TYPE_BOSS_3_GUILD		(BYTE)13

// 2009-07-08 by cmkwon, ���� ���� ���� ��ġ �̵�(LocalizationDefineCommon.h) - 
//#define PAY_MINIMUN_COUNT			10

#define PAY_MINIMUN_BY_BOSS				100000
#define PAY_MINIMUN_BY_OUTPOST			100000	
#define PAY_MINIMUN_BY_STRATEGYPOINT	50000
#define PAY_MAXMUN_BY_BOSS				10000000	// 2009-03-18 by cmkwon, ���� ���� �߰��� ����(���� ���� �ִ밪 ����) - ���� õ��
#define PAY_MAXMUN_BY_OUTPOST			10000000	// 2009-03-18 by cmkwon, ���� ���� �߰��� ����(���� ���� �ִ밪 ����) - ���������� õ��
#define PAY_MAXMUN_BY_STRATEGYPOINT		5000000		// 2009-03-18 by cmkwon, ���� ���� �߰��� ����(���� ���� �ִ밪 ����) - ������ 5�鸸

#define NOT_OTHER_INFL_STAY			0
#define OTHER_INFL_STAY				1
#define NONE_DAMAGE_CONTRIBUTION	0
#define DAMAGE_CONTRIBUTION			1

struct SWAR_CONTRIBUTION_INFO
{// ������ ��뼼�¸ʿ� �ӹ� �ð��� ���� ���� �����Ѵ�.
	ATUM_DATE_TIME	OtherInflStayStartTime;
	INT				OtherInflStayTime;
	BOOL			CheckOtherInflStay;		// NOT_OTHER_INFL_STAY : ��뼼�¸��� �ƴ�, OTHER_INFL_STAY : ��뼼�¸�, 0->1 : ��뼼�¸����� �̵�, 1->0 : ��뼼���� �ƴ� ������ �̵�
	INT				DeathCount;
	UID64_t			Contribution;
	BOOL			CheckDamageContribution; // NONE_DAMAGE_CONTRIBUTION : ���� �������� �⿩�� ����, DAMAGE_CONTRIBUTION : ������ �⿩���� ����
};

///////////////////////////////////////////////////////////////////////////////
// 2009-01-14 by cmkwon, ��� �ڵ� ���� �ý��� ���� - 
#define SIZE_MAX_ADMIN_NOTICE_STRING			256		// �ִ� ���� ���� ���� 
#define SIZE_MAX_COUNT_ADMIN_NOTICE_STRING		20		// ���� ���� �ִ� ����
#define MIN_LOOP_SECONDS_OF_ADMIN_NOTICE		60		// �ڵ� ���� �ý����� �ٽ� �����ϴ� �ּ� Interval time(second), 60�� = 1��
#define MAX_LOOP_SECONDS_OF_ADMIN_NOTICE		604800	// �ڵ� ���� �ý����� �ٽ� �����ϴ� �ִ� Interval time(second), 604800�� = 10080�� = 168�ð� = 7��
#define MIN_INTERVAL_SECONDS_OF_ADMIN_NOTICE	5		// ���� ��Ʈ���� �����ϰ� ���� ���� ��Ʈ�� �����ϱ� ������ �ּ� Interval time(second), 5��
#define MAX_INTERVAL_SECONDS_OF_ADMIN_NOTICE	86400	// ���� ��Ʈ���� �����ϰ� ���� ���� ��Ʈ�� �����ϱ� ������ �ּ� Interval time(second), 86400�� = 1440�� = 24�ð� = 1��
#define DELAY_SEC_AFTER_SERVER_STARTED			300		// ���� ���� �� �ڵ� ���� �ý����� �ٽ� �����ϴ� ���� �ð� 300�� = 5��

struct SANoticeInfo
{
	BOOL			UsingFlag;
	INT				LoopSec;					// ����:��
	INT				IntervalSec;				// ����:��
	char			EditorAccountName[SIZE_MAX_ACCOUNT_NAME];
	ATUM_DATE_TIME	LastStartedTime;
	INT				LastSentNoticeStringIndex;
};
struct SANoticeString		// AdminNoticeString
{
	INT				NoticeStringIndex;
	char			NoticeString[SIZE_MAX_ADMIN_NOTICE_STRING];
};
typedef vector<SANoticeString>			vectSANoticeString;
typedef mt_vector<SANoticeString>		mtvectSANoticeString;

struct sort_SANoticeString_by_StrIdx
{
	bool operator()(SANoticeString op1, SANoticeString op2)
	{
		return op1.NoticeStringIndex < op2.NoticeStringIndex;		// �������� ����
	}
};

//////////////////////////////////////////////////////////////////////////
// 2009-01-12 by dhjin, ���� ����
#define MSWAR_NOT_START		0
#define MSWARING_BEFORE		1
#define MSWARING			2
#define MSWAR_END_WIN		11
#define MSWAR_END_LOSS		21
#define MSWAR_FORBID_GAP_HOUR 12
#define MSWAR_NEXT_LEADER_SETP	99
#define MSWAR_FINAL_SETP	5

struct SDECLARATION_OF_WAR
{
	BYTE			Influence;
	BYTE			MSWarStep;
	INT				NCP;
	INT				MSNum;
	MapIndex_t		MSAppearanceMap;
	ATUM_DATE_TIME	MSWarStepStartTime;
	ATUM_DATE_TIME	MSWarStepEndTime;
	ATUM_DATE_TIME	MSWarStartTime;
	ATUM_DATE_TIME	MSWarEndTime;
	BYTE			SelectCount;
	BOOL			GiveUp;
	BYTE			MSWarEndState;		// MSWAR_NOT_START : ���� �������� ����, MSWARING : ������, MSWAR_END_WIN : �¸�, MSWAR_END_LOSS : �й�
};

struct SDECLARATION_OF_WAR_FORBID_TIME
{
	INT				DayOfWeek;
	ATUM_DATE_TIME	ForbidStartTime;
	ATUM_DATE_TIME	ForbidEndTime;
};


///////////////////////////////////////////////////////////////////////////////
// 2009-01-22 by cmkwon, ���� ���� ���� �α� ���� - WPUT_XXX, WarPointUpdateType
#define WPUT_UNKNOWN				0	
#define WPUT_GENERAL				1	
#define WPUT_ARENA					2	
#define WPUT_MOTHERSHIPWAR			3	
#define WPUT_STRATEGYPOINTWAR		4	
#define WPUT_OUTPOSTWAR				5	
#define WPUT_SHOP					6	
#define WPUT_ADMIN_COMMAND			7	
#define WPUT_TRIGGER				8		// 2011-11-07 by hskim, EP4 [Ʈ���� �ý���] - NCG ������ �ý���
#define WPUT_MARKET					9		// 2013-11-25 by jhseol&bckim, �ŷ���
extern char *GetWPUTString(BYTE i_byWPUT);

///////////////////////////////////////////////////////////////////////////////
// 2009-01-23 by cmkwon, ��Ű i,I ���� ���� ó�� - LowercaseOnly_i_forTurkish() �߰�, ��Ű ���񽺸� i���ڸ� �ҹ��ڷ� ����
extern char *LowercaseOnly_i_forTurkish(char *i_szString, int i_nMaxLen);


///////////////////////////////////////////////////////////////////////////////
// 2009-02-12 by cmkwon, EP3-3 ���巩ŷ�ý��� ���� - 
#define SIZE_MAX_SERVICE_NAME			20						// ���� ��Ű���� ���� ���� ���� ���񽺸� �ִ� ���ڼ�, �ִ� ���� 19����
#define SIZE_MAX_NAME_FOR_RANKING		SIZE_MAX_CHARACTER_NAME	// 
#define SIZE_MAX_SERVICE_SYMBOL_IMAGE	2000					// 48x28 jpg ����,
#define SIZE_MAX_WRK_COUNT				100						// ���巩ŷ �ʼ� ��ŷ
#define SIZE_MAX_REQUEST_COUNT			20						// �ѹ��� ��û ������ �ִ� ��ŷ����Ʈ

#define RANKING_SCOPE_LOCAL				0		// ���� ���� ���� ��ŷ, Name �� NickName
#define RANKING_SCOPE_WORLD				1		// ���� ��ŷ ����, Name �� CharacterName
#define IS_VALID_RANKING_SCOPE(s)		((s) == 0 || (s) == 1)

#define RANKING_TYPE_LEVEL				0		// Level ��ŷ
#define RANKING_TYPE_FAME				1		// ���� ���� ��ŷ
#define RANKING_TYPE_PVP				2		// 1:1 PvP ��ŷ

struct SWRK_SERVICE_INFO
{
	INT			ServiceUID;
	char		ServiceName[SIZE_MAX_SERVICE_NAME];
	BYTE		ServiceSymbolIamge[SIZE_MAX_SERVICE_SYMBOL_IMAGE];
	INT			SymbolImageSize;
};
struct SWRK_SERVER_GROUP
{
	INT			ServerGroupID;
	char		ServerGroupNameforRK[SIZE_MAX_SERVER_NAME];
};
struct SWRK_BASE
{
	INT				ServiceUID;
	INT				UnitKind;
	char			ServerGroupNameforRK[SIZE_MAX_SERVER_NAME];
	char			NameforRK[SIZE_MAX_NAME_FOR_RANKING];
	BYTE			InfluenceType;
	BYTE			Level;
	BYTE			RankingScope;		// RANKING_SCOPE_XXX
};
typedef SWRK_BASE	SWRK_LEVEL;
struct SWRK_LEVEL_FOR_DB: public SWRK_LEVEL
{
	INT				ServerGroupID;
	UID32_t			CharacterUID;
	Experience_t	Experience;	
	ATUM_DATE_TIME	LevelUpTime;	
};

struct SWRK_FAME: public SWRK_BASE
{
	INT				Fame;
};
struct SWRK_FAME_FOR_DB: public SWRK_FAME
{
	INT				ServerGroupID;
	UID32_t			CharacterUID;
};

struct SWRK_PVP: public SWRK_BASE
{
	INT			WinPoint;
	INT			LossPoint;
	INT			Score;
};
struct SWRK_PVP_FOR_DB: public SWRK_PVP
{
	INT				ServerGroupID;
	UID32_t			CharacterUID;
};
typedef vector<SWRK_SERVER_GROUP>		vectSWRK_SERVER_GROUP;

typedef mt_vector<SWRK_SERVICE_INFO>	mtvectSWRK_SERVICE_INFO;

typedef mt_vector<SWRK_LEVEL>			mtvectSWRK_LEVEL;
typedef mt_vector<SWRK_LEVEL*>			mtvectSWRK_LEVELPtr;
typedef mt_vector<SWRK_LEVEL_FOR_DB>	mtvectSWRK_LEVEL_FOR_DB;

typedef mt_vector<SWRK_FAME>			mtvectSWRK_FAME;
typedef mt_vector<SWRK_FAME*>			mtvectSWRK_FAMEPtr;
typedef mt_vector<SWRK_FAME_FOR_DB>		mtvectSWRK_FAME_FOR_DB;

typedef mt_vector<SWRK_PVP>				mtvectSWRK_PVP;
typedef mt_vector<SWRK_PVP*>			mtvectSWRK_PVPPtr;
typedef mt_vector<SWRK_PVP_FOR_DB>		mtvectSWRK_PVP_FOR_DB;

extern int GetArrIdxByUnitMaskforWRK(INT i_unitMask);
extern int GetUnitMaskByArrIdxforWRK(INT i_arrIdx);


//////////////////////////////////////////////////////////////////////////
// 2009-03-03 by dhjin, ��Ű�ӽ� ������
#define SIZE_MAX_LUCKYMACHINE_DESCRIPTION		200
struct LUCKY_MACHINE_OMI
{
	INT			order;
	INT			BuildingInx;
	BYTE		MachineKind;
	INT			MachineNum;
	INT			CoinItemNum;
	BYTE		SlotNum;
	INT			SourceIndex;
	char		szDescription[SIZE_MAX_LUCKYMACHINE_DESCRIPTION];
};


///////////////////////////////////////////////////////////////////////////////
// 2009-03-09 by cmkwon, �Ϻ� Arario nProtect�� CS���� �����ϱ� - 
#define MAX_PACKET_SIZE_FOR_NPROTECT	128			// 2009-03-09 by cmkwon, �Ϻ� Arario nProtect�� CS���� �����ϱ� - �ִ� �������� ũ��

///////////////////////////////////////////////////////////////////////////////
// 2015-01-07 by jwLee �������� nProtector ����
#define MAX_PACKET_SIZE_FOR_NPROTECT_NEW	400

//////////////////////////////////////////////////////////////////////////
// 2009-03-10 by dhjin, �ܰ躰 �� �ý���
#define MSBOSSSTEP_UNKNOWN_BEFOREWAR	0			// �� �ֱ⿡ ���� ������ ���ų� ù �ֱ� ��
#define MSBOSSSTEP_WIN_BEFOREWAR		1			// �� �ֱ⿡ ���� �¸�
#define MSBOSSSTEP_LOSS_BEFOREWAR		2			// �� �ֱ⿡ ���� �й�



///////////////////////////////////////////////////////////////////////////////
// 2009-03-31 by cmkwon, �����ʱ�ȭ �ý��� ���� - 
#define QUEST_INDEX_OF_SELECT_INFLUENCE				112		// ���� ���� �̼� QuestIndex, ��� ���� ������

struct SQUEST_MATCHING
{
	INT		QuestIndexForBCU;
	INT		QuestIndexForANI;
};
typedef vector<SQUEST_MATCHING>			vectSQUEST_MATCHING;

struct SQUEST_MATCH_CHANGE
{
	INT		FromQuestIndex;
	INT		ToQuestIndex;
};
typedef vector<SQUEST_MATCH_CHANGE>		vectSQUEST_MATCH_CHANGE;

struct SITEM_MATCHING
{
	INT		ItemNumForBCU;
	INT		ItemNumForANI;
};
typedef vector<SITEM_MATCHING>			vectSITEM_MATCHING;

struct SITEM_MATCH_CHANGE
{
	INT		FromItemNum;
	INT		ToItemNum;
};
typedef vector<SITEM_MATCH_CHANGE>		vectSITEM_MATCH_CHANGE;



///////////////////////////////////////////////////////////////////////////////
// 2009-04-06 by cmkwon, �ݿ��� ����� ��ų �ý��� ���� - 
struct SSKILL_CONFIRM_USE
{
	int					SkillConfirmUseUID;
	DWORD				ExpireTick;
	UID32_t				TargetCharacterUID;
	int					UsingSkillItemNum;		// ��� ��ų ItemNum
	MAP_CHANNEL_INDEX	MapChannelIndex;		// ��ų ������� MapChannelIndex
	D3DXVECTOR3			PositionVec3;
};
typedef mt_vector<SSKILL_CONFIRM_USE>			mtvectSSKILL_CONFIRM_USE;


///////////////////////////////////////////////////////////////////////////////
// 2009-07-09 by jwlee, ���� ���� ���̺� ������ DB�� �о�ֱ� �� ���� -
#define SIZE_MAX_ITEM_INFO_NAME					250
#define SIZE_MAX_TABINDEX						250
#define SIZE_MAX_ITEMDESCRIPTION				250
#define SIZE_MAX_OBJECT_DESCRIPTION				250

typedef struct 
{
	int		ShopOrder;
	int		UniqueNumber;
	int		ItemNum;
}SHOP_INFO;
typedef mt_vector<SHOP_INFO>			vectSHOP_INFO;

typedef struct
{
	int		MapIndex;
	int		BuildingIndex;
	int		WarpTargetMapIndex;
	int		WarpTargetIndex;
	char	WarpTargetName[SIZE_MAX_WARP_TARGET_NAME];
	int		Fee;
}CITY_TARGET_WARPMAP;
typedef mt_vector<CITY_TARGET_WARPMAP>			vectCITY_TARGET_WARPMAP;

typedef struct
{
	char			MapName[SIZE_MAX_MAP_NAME];
	MapIndex_t		MapIndex;
	int				StratrgyPiontNum;
}STRATEGYPOINT_SUMMON_MAPINDEX;
typedef mt_vector<STRATEGYPOINT_SUMMON_MAPINDEX>			vectSTRATEGYPOINT_SUMMON_MAPINDEX;

struct MONSTER_DATA : public MONSTER_INFO
{
	int		ControlSkil;
	int		SizeForServer;
	int		SizeForClient;
	int		MonsterItem[ARRAY_SIZE_MONSTER_ITEM];
};
typedef mt_vector<MONSTER_DATA>			vectMONSTER_DATA;

struct MAPOBJECT : public _MAPOBJECTINFO
{
	char	ObjectName[SIZE_MAX_OBJECT_NAME];
	USHORT	RadiusForServer;
	USHORT	RadiusForClient;
	char	ObjectDescription[SIZE_MAX_OBJECT_DESCRIPTION];
};
typedef mt_vector<MAPOBJECT>			vectMAPOBJECT;

struct LUCKY_MACHINE : public LUCKY_MACHINE_OMI
{
	int		SlotProbability;
	int		MysteryItemDropNum;
};
typedef mt_vector<LUCKY_MACHINE>			vectLUCKY_MACHINE;

typedef vector<MYSTERY_ITEM_DROP>				vectMYSTERY_ITEM_DROP;

typedef struct
{
	float	IsDisable;
	float	GameUID;
	float	ItemNum;
	char	ItemName[SIZE_MAX_ITEM_NAME];
	float	TabIndex;
	char	IconFileName[SIZE_MAX_TABINDEX];
	float	ItemUnitPrice;
	char	ItemDescription[SIZE_MAX_ITEMDESCRIPTION];
}ITEM_INFO;
typedef vector<ITEM_INFO>			vectItem_Info;			  

// 2009-09-16 by cmkwon, ���� �ʱ�ȭ�� ���¡ ���� ���� - ti_InfluenceRate ���̺� �߰�, 
struct STI_INFLUENCERATE
{
	BYTE	StartLevel;
	BYTE	EndLevel;
};
typedef vector<STI_INFLUENCERATE>		vectSTI_INFLUENCERATE;


///////////////////////////////////////////////////////////////////////////////
// 2009-08-03 by cmkwon, EP3-4 ���� ���� ��ų ���� - AtumProtocol.h�� ���ǵǾ� �ִ°��� ����� �ű�
#define FLIGHT_FORM_NONE				(BYTE)0 // ���� ���� �� ��
#define FLIGHT_FORM_2_COLUMN			(BYTE)1 // �̷� ����, �̷� ���� ������� �� �ٷ� ������ �� ����̴�
#define FLIGHT_FORM_2_LINE				(BYTE)2 // �̷� Ⱦ��, �̷� Ⱦ�� ������� �� �ٷ� ������ �� ����̴�
#define FLIGHT_FORM_TRIANGLE			(BYTE)3 // �ﰢ ����, �ﰢ�� ������� ��ܺ��� 1, 2, 3���� ������ ��ġ�Ѵ�
#define FLIGHT_FORM_INVERTED_TRIANGLE	(BYTE)4 // ���ﰢ ����, �� �ﰢ�� ������� ��ܺ��� 3, 2, 1���� ������ ��ġ�Ѵ�
#define FLIGHT_FORM_BELL				(BYTE)5 // �� ����, �� ������� ��ܺ��� 1, 3, 2���� ������ ��ġ�Ѵ�
#define FLIGHT_FORM_INVERTED_BELL		(BYTE)6 // ���� ����, ���� ������� ��ܺ��� 2, 3, 1���� ������ ��ġ�Ѵ�
#define FLIGHT_FORM_X					(BYTE)7 // X�� ����
#define FLIGHT_FORM_STAR				(BYTE)8 // �� ����

#define ITEM_UID_FOR_PARTY_FLIGHT_FORMATION_SKILL_START			(INVALID_UID64-1000)	// ���� �ڿ� 1000���� ���� ��ų�� UID�� ����ϵ��� �Ѵ�.

///////////////////////////////////////////////////////////////////////////////
// 2009-09-16 by cmkwon, ���� �ʱ�ȭ�� ���¡ ���� ���� - 
#define PERIOD_OF_DAY_FOR_VALID_INFLUENCE		30		// ��ȿ�� ���� ���� ���� �ϼ�

struct SINFL_USER_COUNT
{
	BYTE			StartLevel;
	BYTE			EndLevel;
	ATUM_DATE_TIME	UpdatedTime;
	INT				AllowablePercent;
	INT				arrUserCount[INFLUENCE_TYPE_COUNT_EX_ALL];		// index ==> 0:Normal, 1:BCU, 2:ANI

	BOOL AddUserCount(BYTE i_byInflTy, int i_nValues=1)
	{
		switch(i_byInflTy)
		{
		case INFLUENCE_TYPE_NORMAL:		arrUserCount[0] += i_nValues;		break;
		case INFLUENCE_TYPE_VCN:		arrUserCount[1] += i_nValues;		break;
		case INFLUENCE_TYPE_ANI:		arrUserCount[2] += i_nValues;		break;
		default:
			{
				return FALSE;
			}
		}
		return TRUE;
	}
	BOOL SubtractUserCount(BYTE i_byInflTy, int i_nValues=1)
	{
		switch(i_byInflTy)
		{
		case INFLUENCE_TYPE_NORMAL:		arrUserCount[0] = max(0, arrUserCount[0] - i_nValues);		break;
		case INFLUENCE_TYPE_VCN:		arrUserCount[1] = max(0, arrUserCount[1] - i_nValues);		break;
		case INFLUENCE_TYPE_ANI:		arrUserCount[2] = max(0, arrUserCount[2] - i_nValues);		break;
		default:
			{
				return FALSE;
			}
		}
		return TRUE;
	}
	BOOL IsSetForAll(void)
	{
		if(0 == StartLevel && 0 == EndLevel)
		{
			return TRUE;
		}
		return FALSE;
	}
};
typedef mt_vector<SINFL_USER_COUNT>		mtvectSINFL_USER_COUNT;

///////////////////////////////////////////////////////////////////////////////
// 2009-10-06 by cmkwon, ��Ʈ�� ���� ���� X-TRAP���� ���� - 
#define XTRAP_SIZE_MAX_SESSIONBUF		320			// 2009-10-06 by cmkwon, ��Ʈ�� ���� ���� X-TRAP���� ���� - �ִ� �������� ũ��
#define XTRAP_CSFILE_NUM				5			// 2009-10-06 by cmkwon, ��Ʈ�� ���� ���� X-TRAP���� ���� - �ǽð� ���� �������� ������Ʈ ����
// 2009-10-29 by cmkwon, ��Ʈ�� X-TRAP �ڵ�������Ʈ ��� ���� - 

// 2013-10-09 by jhseol, X-Trap + VTC ���Ӱ���
#if defined(SC_XTRAP_VTC_GAMEGUARD_BHSOHN_JHSEOL) && defined(S_ACCESS_INTERNAL_SERVER_HSSON)
	//Test server: http://xtrap.phidoi.vtcgame.vn/test
	//KEY: 660970B4E839D84DC5856D9844CFEF62857803FA0D9352A0D77FCEA14C6339D4DD77DD0D07F2066633F8AA7F5AF9FE930A9CC8E3ED645820723BB42DED42338D0F7D04245246E41FB1670C4E95407F04E2D092B9A3C7041B8028237A3CEF16158CBEC7
	#define XTRAP_KEY_STRING				"660970B4E839D84DC5856D9844CFEF62857803FA0D9352A0D77FCEA14C6339D4DD77DD0D07F2066633F8AA7F5AF9FE930A9CC8E3ED645820723BB42DED42338D0F7D04245246E41FB1670C4E95407F04E2D092B9A3C7041B8028237A3CEF16158CBEC7"
#elif defined(SC_XTRAP_VTC_GAMEGUARD_BHSOHN_JHSEOL)
	//Live server: http://xtrap.phidoi.vtcgame.vn/live
	//KEY: 660970B4E839D84DC5856D9844CFEF62857803FA0D9352A0D77FCEA14C6339D4DD77DD0D07F2066633F8AA7F5AF9FE930A9CC8E3ED645820723BB42DED42338D0F7D04245246E41FB1670C4E95407F04E2D092B9A3C7041B8028237A3CEF160DFE4A2E
	#define XTRAP_KEY_STRING				"660970B4E839D84DC5856D9844CFEF62857803FA0D9352A0D77FCEA14C6339D4DD77DD0D07F2066633F8AA7F5AF9FE930A9CC8E3ED645820723BB42DED42338D0F7D04245246E41FB1670C4E95407F04E2D092B9A3C7041B8028237A3CEF160DFE4A2E"
#endif
#define XTRAP_KEY_STRING_TEST				"660970B4E839D84DC5856D9844CFEF62857803FA0D9352A0D77FCEA14C6339D4DD77DD0D07F2066633F8AA7F5AF9FE930A9CC8E3ED645820723BB42DED42338D0F7D04245246E41FB1670C4E95407F04E2D092B9A3C7041B8028237A3CEF16158CBEC7"
#define XTRAP_KEY_STRING_LIVE				"660970B4E839D84DC5856D9844CFEF62857803FA0D9352A0D77FCEA14C6339D4DD77DD0D07F2066633F8AA7F5AF9FE930A9CC8E3ED645820723BB42DED42338D0F7D04245246E41FB1670C4E95407F04E2D092B9A3C7041B8028237A3CEF160DFE4A2E"
// end 2013-10-09 by jhseol, X-Trap + VTC ���Ӱ���

//#if defined(SERVICE_TYPE_VIETNAMESE_SERVER_1)		// 2012-02-09 by hskim, ��Ʈ�� X-Trap -> VTC ����� ����
//#define XTRAP_KEY_STRING				"660970B4E839D8FFE53D6D9844CFE862B5FBE52B2875C638EC78A75D5FDB5C182F76A736AABEA256E36B6165D77729DD9C3419ED86B2D75179618347974228D00F7D04245246E41FB1670C4E95407F04E2D092B9A3C70452972B692C3EF35811"		
//#endif

#if defined(SERVICE_TYPE_ARGENTINA_SERVER_1)
	#define XTRAP_KEY_STRING				"660970B4963BD8A390256D9844CFE862F4BDBA635141DB3F0785BDC3E5836D033AFA4B1C226F9494F98192EBFF893A88756E0C810FF0175398D854AF913E10F40F7D04245246E406A670095295516F08D696B66EAE38D3BD5E287A3A23"
#endif


///////////////////////////////////////////////////////////////////////////////
// 2009-10-22 by cmkwon, �ð� �������� ������ �ý��� ���� - 
extern int GetNumberOfBits(INT64 i_n64Mask);
typedef enum{
	TIME_TERM_USING_ITEM	= 1,		//
	TIME_TERM_DELETE_ITEM,				//
	TIME_TERM_PREMIUM,					//
	TIME_TERM_EVENT						//
										//
} TIME_TERM_t;

// 2009. 10. 27 by jskim ����� Ȯ��
#define WM_PROGRESSBAR_RANGE							WM_USER + 400	
#define WM_PROGRESSBAR_POS								WM_USER + 401	
//end 2009. 10. 27 by jskim ����� Ȯ��


///////////////////////////////////////////////////////////////////////////////
// 2009-11-04 by cmkwon, �±� ���Ӱ��� Apex�� ���� - 
#define SECURITY_APEX_MaxPacketLen			1024	
#define SECURITY_APEX_ClientIpFlag			0x01
#define SECURITY_APEX_Cmd_Login				0x11
#define SECURITY_APEX_Cmd_Logout			0x12
#define SECURITY_APEX_Cmd_ApexData			0x13
#define SECURITY_APEX_Cmd_SimpleInputMsg	0x14
#define SECURITY_APEX_Cmd_ClientRet			0x15 

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// 2010. 05. 19 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����. (��ȣó�� + ���� ó��(����) )
#define DEFAULT_LEVEL_INFINITY_DIFFICULTY	25					// ���Ǵ�Ƽ �� ������ �⺻ ���� ���̵�. ( ��� ������ [Ȯ��-����]�ȴٸ� �ܺ� ������ �ٲ� �� ����. )


////////////////////////////////////////////////////////////////////////////////
// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - 

#define TICK_CREATE_MONSTER_TERM_ONLY_INFINITY		2592000000		// 1000Msec * 60 Sec * 60 Min * 24 Hour * 30 Day : �� �� �� �ڿ� ��ȯ �Ǵ� ��
#define TICK_FIRST_FORCED_CREATE_MONSTER_TERM		120000		// 1000Msec * 60 Sec * 2�� Min : ù ���� ��ȯ ��
#define COUNT_DELAY_FORCED_CREATE_MONSTER_TERM		60			// 60 Sec * 1 Min : ���� ��ȯ �� �ٽ� ���� ��ȯ üũ���� ��
#define TICK_TENDER_PROCESSING_TERM					20000		// 1000Msec * 20 Sec : Tender ���� ��

typedef enum
{
	HPACTION_TALK_CONDITION_NONE				= 0,
	HPACTION_TALK_CONDITION_CREATE				= 1,				// ������ ��ȭ ���
	HPACTION_TALK_CONDITION_DEAD				= 2,				// ������ ��ȭ ���
	HPACTION_TALK_CONDITION_HP_RATE				= 3,				// HP���¿� ���� ��ȭ ���
	HPACTION_TALK_CONDITION_DAMAGED_RANDOM		= 4,				// ���� ���� ��� ���� ��ȭ ���
	HPACTION_TALK_CONDITION_ATTACK				= 5,				// �ش� HPAction  ���ݽ� ��ȭ ���
	HPACTION_TALK_CONDITION_TARGET_CHANGE		= 6,				// Ÿ�� ���� �� ��ȭ ���
} eHPACTION_TALK_CONDITION;
typedef enum
{
	HPACTION_TALK_IMPORTANCE_NONE				= 0,
	HPACTION_TALK_IMPORTANCE_ALL				= 1,				// ��� �������� ��ȭ ����
	HPACTION_TALK_IMPORTANCE_INFL				= 2,				// ���� ���� �������� ��ȭ ����
	HPACTION_TALK_IMPORTANCE_CHANNEL			= 3,				// ���� ä�� �������� ��ȭ ����
//	HPACTION_TALK_IMPORTANCE_PARTY				= 4,				// ��Ƽ������ ��ȭ ����
} eHPACTION_TALK_IMPORTANCE;

#define SIZE_MAX_HPTALK_DESCRIPTION					SIZE_MAX_CHAT_MESSAGE
#define HPTALK_DAMAGED_RANDOM_RATE				3					// �ǰݽ� ��� �� Ȯ�� 3%
#define SIZE_MAX_CINEMATALK_DESCRIPTION				SIZE_MAX_HPTALK_DESCRIPTION

struct HPACTION
{
	HPActionUID_t					HPActionUID;
	HPActionIdx_t					HPActionNum;
	HPValueRate_t					HPMaxValueRate;
	HPValueRate_t					HPMinValueRate;
	ItemIdx_t						UseItemArrayIdx;
	ItemIdx_t						NextUseItemArrayIdx;
	HPHitRate_t						HitRate;
	HPUseCount_t					UseCount;
	eHPACTION_TALK_CONDITION		HPTalkCondition;
	eHPACTION_TALK_IMPORTANCE		HPTalkImportance;
	MSec_t							PreHPCameraTremble;
	HPTalk_t						PreHPTalk[SIZE_MAX_HPTALK_DESCRIPTION];
	MSec_t							HPCameraTremble;
	HPTalk_t						HPTalk[SIZE_MAX_HPTALK_DESCRIPTION];
};
typedef vector<HPACTION>			vectHPAction;	
struct HPACTION_TALK_DAMAGED_RANDOM
{
	HPTalk_t						HPTalk[SIZE_MAX_HPTALK_DESCRIPTION];
};
typedef vector<HPACTION_TALK_DAMAGED_RANDOM>	vectHPActionTalkDamagedRandom;
struct HPACTION_TALK_HPRATE
{
	HPValueRate_t					HPValueRate;
	eHPACTION_TALK_IMPORTANCE		HPTalkImportance;
	MSec_t							HPCameraTremble;
	ClientIndex_t					TargetClientIdx;			// ��� ���õ� ��簡 �ִٸ� �����Ѵ�.
	HPTalk_t						HPTalk[SIZE_MAX_HPTALK_DESCRIPTION];
};
typedef vector<HPACTION_TALK_HPRATE>	vectHPActionTalkHPRate;
struct HPACTION_ATTACK_HPRATE
{
	HPActionUID_t					HPActionUID;		// 2009-09-09 ~ 2010-01-13 by dhjin, ���Ǵ�Ƽ - �� ���������� ���� ��� �����ϰ� ����
	HPValueRate_t					HPMaxValueRate;
	HPValueRate_t					HPMinValueRate;
	ItemIdx_t						UseItemArrayIdx;
	ItemIdx_t						NextUseItemArrayIdx;
	HPHitRate_t						HitRate;
	HPUseCount_t					UseCount;
};
typedef vector<HPACTION_ATTACK_HPRATE>	vectHPActionAttackHPRate;

struct HPACTION_TALK_ATTACK
{
	ItemIdx_t						ItemNum;
	HPActionUID_t					HPActionUID;		// 2009-09-09 ~ 2010-01-13 by dhjin, ���Ǵ�Ƽ - �� ���������� ���� ��� �����ϰ� ����
	ItemIdx_t						UseItemArrayIdx;
	MSec_t							PreHPCameraTremble;
	HPTalk_t						PreHPTalk[SIZE_MAX_HPTALK_DESCRIPTION];
	MSec_t							HPCameraTremble;
	HPTalk_t						HPTalk[SIZE_MAX_HPTALK_DESCRIPTION];
};
typedef vector<HPACTION_TALK_ATTACK>	vectHPActionTalkAttack; 

struct DEBUFFINFO {
	INT			ItemNum;						// ������ ������ȣ, ���� �������� �� (ITEM_BASE*)
	BYTE		Kind;							// 104 : ���� ��ų // ������ ����(�����, ��, ����, ��ų.....), ITEMKIND_XXX
	DestParam_t	DesParam;						// 2011-08-01 by hskim, ��Ʈ�� �ý��� 2�� - �ڷ��� ���� (DestParameter - 255 -> 32767 ����)
	float		DesParamValue;
	INT			Time;							// ���� �ð�(��ų�� ��) ���� : ms
	BYTE		SkillLevel;						// ����
	BYTE		SkillType;						// ��ų����(�ð� �� �ߵ� ����), ����|Ŭ��|�ð�|����
	DWORD		dwUseTime;						// ����� ���� �ð�
};
typedef mt_vector<DEBUFFINFO>					mtvectorDebuffInfo;

struct DOTINFO {
	UID32_t				FirstTimerUID;
	ClientIndex_t		ClientIndex;
	INT					ItemNum;						// ������ ������ȣ, ���� �������� �� (ITEM_BASE*)
	BYTE				Kind;							// 104 : ���� ��ų // ������ ����(�����, ��, ����, ��ų.....), ITEMKIND_XXX
	DestParam_t			DesParam;						// 2011-08-01 by hskim, ��Ʈ�� �ý��� 2�� - �ڷ��� ���� (DestParameter - 255 -> 32767 ����)
	float				DesParamValue;
	INT					Time;							// ���� �ð�(��ų�� ��) ���� : ms
};
typedef mt_vector<DOTINFO>					mtvectorDotInfo;

typedef enum
{
	INFINITY_MODE_NONE				= 0,
	INFINITY_MODE_BOSSRUSH			= 1,
	INFINITY_MODE_DEFENCE			= 2,
	INFINITY_MODE_MSHIPBATTLE		= 3					// 2011-02-18 by hskim, ���Ǵ�Ƽ 3�� - �𼱹�Ʋ

} eINFINITY_MODE;

// start 2011-04-21 by hskim, ���Ǵ�Ƽ 3�� - �ó׸� �ܰ躰 ��� ����
// typedef enum
// {
// 	INFINITY_KEYMONSTER_NONE					= 0,
// 	INFINITY_KEYMONSTER_DEAD_FOR_NEXT_STEP		= 1,
// 	INFINITY_KEYMONSTER_ALIVE_FOR_GAME_CLEAR	= 2,
// 
// } eINFINITY_KEYMONSTER;
// end 2011-04-21 by hskim, ���Ǵ�Ƽ 3�� - �ó׸� �ܰ躰 ��� ����

typedef enum		// ���Ǵ�Ƽ ��ŵ ���°�.
{
	INFINITY_SKIP_CINEMA_NONE		= 0 ,			
	INFINITY_SKIP_CINEMA_NORMAL			,			// ��ŵ - ���� ����.
	INFINITY_SKIP_CINEMA_REQ_SKIP		,			// ��ŵ - ���� ��û.

} eINFINITY_SKIP_CINEMA;


struct CINEMAINFO {	// 2010-03-31 by dhjin, ���Ǵ�Ƽ(�������) - ���� ����
	CinemaNum_t			CinemaNum;	
	CinemaOrder_t		CinemaOrder;		// 51000 : ���� ���� �ó׸�, 52000 : ���� ���� �ó׸�, CINEMA_FIN_XXX
	MSec_t				StartTime;			// msec
	EffectIdx_t			EffectIdx;
	Position_t			EffectPosition_X;
	Position_t			EffectPosition_Y;
	Position_t			EffectPosition_Z;	
	MSec_t				EffectPlayTime;		// msec	
	EffectPlayCount_t	EffectPlayCount;
	ObjectIdx_t			ObjectIdx;					// �ʿ� ���� Object�� EvnetParamIndex
	ObjectNum_t			ChangeObjectIdx;			// ����� ObjectNum
	MSec_t				ChangeTime;			// msec			
	MSec_t				CameraTremble;		// msec	
	KeyMonster_t		KeyMonster;		// 2011-04-21 by hskim, ���Ǵ�Ƽ 3�� - �ó׸� �ܰ躰 ��� ����
	MonIdx_t			MonsterIdx;					// ��ȯ�� MonsterUnitkind
	SummonCnt_t			SummonCount;	
	Distance_t			SummonRandomPos;	// M
	ObjectIdx_t			ObjectBodyConditionIdx;		// �ʿ� ���� Object�� EvnetParamIndex
	BodyCond_t			BodyCondition;				// ObjectBodyConditionIdx Object�� ���� �� BodyCondition(����:1024, ����:32)
	FileName_t			TipFileName[SIZE_MAX_FILE_NAME];	
	FileName_t			SkyFileName[SIZE_MAX_FILE_NAME];
	CinemaTalk_t		CinemaTalk[SIZE_MAX_CINEMATALK_DESCRIPTION];
	FileName_t			SoundFileName[SIZE_MAX_FILE_NAME];		// 2010-03-29 by cmkwon, ����2�� �ó׸��� ȿ���� ���� ���� �߰� - 
	// start 2011-04-28 by hskim, ���Ǵ�Ƽ 3�� - �ó׸� ���� ��� �߰�
	QuestIndex_t		QuestIndex;					// 2011-03-09 by hskim, �ó׸� ����Ʈ �ε��� ���� �߰�
	eCINEMA_MONSTER_INDEX_TYPE	MonsterIdxType;		// CINEMA_MONSTER_INDEX_CREATE = 0 ,	CINEMA_MONSTER_INDEX_CREATE = 1
	CustomIdx_t			CustomIdx;					// 1xxx = �ó׸� 1�� , 2xxx = �ó׸� 2�� , 3xxx = �ó׸� 3��
	MonIdx_t			UpdateMonsterIdx;			// ������ ���� �ε���
	// end 2011-04-28 by hskim, ���Ǵ�Ƽ 3�� - �ó׸� ���� ��� �߰�
};	
typedef vector<CINEMAINFO>					vectorCinemaInfo;

struct REVISIONINFO {
	RevisionNum_t		RevisionNum;
	INT					UnitKind;
	Lv_t				RevisionLevel;
	RevisionHP_t		RevisionHP;
	RevisionDP_t		RevisionDP;
	RevisionWeapon1_t	RevisionStandardWeapon;
	RevisionWeapon2_t	RevisionAdvancedWeapon;
};
typedef vector<REVISIONINFO>				vectorRevisionInfo;

struct INFINITY_MONSTERINFO {
	UID32_t				InfinityMonsterUID;
	MonIdx_t			InfinityMonsterIdx;
	MonIdx_t			MonsterIdx;	
	InfiMonTargetType_t	TargetType;
	InfiMonTargetCount_t	TargetCount;
};
typedef vector<INFINITY_MONSTERINFO>		vectorInfinityMonsterInfo;

struct INFINITY_MODEINFO {
	InfiModeUID_t		InfinityModeUID;
	MapIndex_t			MapIdx;		
	eINFINITY_MODE		ModeTypeNum;
	MonIdx_t			InfinityMonsterIdx;
	CinemaNum_t			CinemaNum;
	RevisionNum_t		RevisionNum;
	ResetCycle_t		ResetCycle;
	EntranceCount_t		EntranceCount;
	MSec_t				LimitTime;
	Lv_t				MinLv;
	Lv_t				MaxLv;
	AdmissionCount_t	MinAdmissionCount;
	AdmissionCount_t	MaxAdmissionCount;
	Minute_t			TimePenaltyValue;		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ����� �г�Ƽ �߰�
	Penalty_t			HPPenaltyValue;			// 2011-06-14 by hskim, ���Ǵ�Ƽ 3�� - �г�Ƽ ��� �߰� (HP �� �ð� ���� ������ ����)
};
typedef vector<INFINITY_MODEINFO>		vectorInfinityModeInfo;

struct INFINITY_IMPUTE {
	InfiModeUID_t		InfinityModeUID;
	EntranceCount_t		EntranceCount;
};
typedef mt_vector<INFINITY_IMPUTE>			mt_vectorInfinityImpute;
typedef vector<INFINITY_IMPUTE>				vectINFINITY_IMPUTE;			// 2010-04-05 by cmkwon, ���� ������ ī�� ���� �ý��� ���� - 

typedef enum
{
	INFINITY_STATE_NONE					= 0,
	INFINITY_STATE_UNPREPARED			= 1,				// ���Ǵ�Ƽ ������ ������ ���ڴ� ������ ���� ����
	INFINITY_STATE_READY				= 2,				// ���Ǵ�Ƽ �ʿ� ���� �� ����
	INFINITY_STATE_READY_ENTER_CHECK	= 3,				// 2010-03-23 by cmkwon, ���Ǵ�Ƽ ���� ĳ�� ������ ���� - MF�κ��� Start ������ ���� ����
	INFINITY_STATE_READY_ENTER_CHECKED	= 4,				// 2010-03-23 by cmkwon, ���Ǵ�Ƽ ���� ĳ�� ������ ���� - MF�κ��� Start ������ ���� ����
	INFINITY_STATE_ENTERING				= 5,				// 2009-09-09 ~ 2010-01-29 by dhjin, ���Ǵ�Ƽ - ���Ǵ�Ƽ ���� ��ư ���� ���� �߰�
	INFINITY_STATE_MAPLOADED			= 6,				// ���Ǵ�Ƽ �� �ε� �Ϸ�
	INFINITY_STATE_PLAYING				= 7,				// ���Ǵ�Ƽ �ʿ� �����Ͽ� ������ ���� 
	INFINITY_STATE_DONE_SUCCESS			= 8,				// 2010-03-31 by dhjin, ���Ǵ�Ƽ(�������) - // ���Ǵ�Ƽ ���� ���� ����
	INFINITY_STATE_DONE_FAIL			= 9,				// 2010-03-31 by dhjin, ���Ǵ�Ƽ(�������) - // ���Ǵ�Ƽ ���� ���� ����

	// PLAYING_STEP �ƴ� ��� ���⿡ �߰��ϼ���

// start 2011-04-08 by hskim, ���Ǵ�Ƽ 3�� - �ó׸� �ܰ躰 ��� ����
// [����] ������ �߰��ɰ�� �Ʒ� ���� �������ֱ�
// IS_INFINITY_STATE_PLAYING_LAST/IS_INFINITY_STATE_PLAYING/IS_INFINITY_STATE_PLAYING_STEP/CINEMA_PLAYING_STEP_MAX
// CFieldIOCPSocket::InfinityOnCharacterGameEndRoutine �Լ� �� switch ��

	INFINITY_STATE_PLAYING_STEP1		= 101,				// ���Ǵ�Ƽ 3�� ���� 1 - ���� �ı�
	INFINITY_STATE_PLAYING_STEP2		= 102,				// ���Ǵ�Ƽ 3�� ���� 2 - Ȱ�ַ� �ı�
	INFINITY_STATE_PLAYING_STEP3		= 103,				// ���Ǵ�Ƽ 3�� ���� 3 - �ݳ��� ħ��
	INFINITY_STATE_PLAYING_STEP4		= 104,				// ���Ǵ�Ƽ 3�� ���� 4 - ���̴� ���� �ı�
	INFINITY_STATE_PLAYING_STEP5		= 105,				// ���Ǵ�Ƽ 3�� ���� 5-1	- ������ �ı� 1�ܰ� (��ȣ�� �ı�)
	INFINITY_STATE_PLAYING_STEP6		= 106,				// ���Ǵ�Ƽ 3�� ���� 5-2	- ������ �ı� 2�ܰ� (���� �ı�)
	INFINITY_STATE_PLAYING_STEP7		= 107,				// ���Ǵ�Ƽ 3�� ���� 5-3	- ���� (���� �� ħ�� ����)
	INFINITY_STATE_PLAYING_STEP8		= 108,				// ���Ǵ�Ƽ 3�� ���� 6		- ���ʽ� ���� (Ż�⼱ ���)
	INFINITY_STATE_PLAYING_STEP9		= 109				// ���Ǵ�Ƽ 3�� ���� 7		- ���� ó��
// end 2011-04-08 by hskim, ���Ǵ�Ƽ 3�� - �ó׸� �ܰ躰 ��� ����
} eINFINITY_STATE;

// start 2011-04-11 by hskim, ���Ǵ�Ƽ 3�� - �ó׸� �ܰ躰 ��� ����
#define IS_INFINITY_STATE_PLAYING_LAST(_IT_)		(INFINITY_STATE_PLAYING_STEP9 == (_IT_))		// ������ ������ ����? - �� �������ֱ�
#define IS_INFINITY_STATE_PLAYING(_IT_)		(INFINITY_STATE_PLAYING == (_IT_) || INFINITY_STATE_PLAYING_STEP1 == (_IT_) ||	\
											INFINITY_STATE_PLAYING_STEP2 == (_IT_) || INFINITY_STATE_PLAYING_STEP3 == (_IT_) ||		\
											INFINITY_STATE_PLAYING_STEP4 == (_IT_) || INFINITY_STATE_PLAYING_STEP5 == (_IT_) ||		\
											INFINITY_STATE_PLAYING_STEP6 == (_IT_) || INFINITY_STATE_PLAYING_STEP7 == (_IT_) ||	\
											INFINITY_STATE_PLAYING_STEP8 == (_IT_) || INFINITY_STATE_PLAYING_STEP9 == (_IT_))

#define IS_INFINITY_STATE_PLAYING_STEP(_IT_)		( INFINITY_STATE_PLAYING_STEP1 == (_IT_) ||	INFINITY_STATE_PLAYING_STEP2 == (_IT_) ||	\
													INFINITY_STATE_PLAYING_STEP3 == (_IT_) || INFINITY_STATE_PLAYING_STEP4 == (_IT_) ||	\
													INFINITY_STATE_PLAYING_STEP5 == (_IT_) || INFINITY_STATE_PLAYING_STEP6 == (_IT_) || \
													INFINITY_STATE_PLAYING_STEP7 == (_IT_) || INFINITY_STATE_PLAYING_STEP8 == (_IT_) || \
													INFINITY_STATE_PLAYING_STEP9 == (_IT_))
// end 2011-04-11 by hskim, ���Ǵ�Ƽ 3�� - �ó׸� �ܰ躰 ��� ����


struct INFINITY_PLAYING_INFO {
	InfinityCreateUID_t InfinityCreateUID;
	InfiModeUID_t		InfinityModeUID;
	MapIndex_t			MapIdx;		
	eINFINITY_MODE		ModeTypeNum;
	eINFINITY_STATE		InfinityState;
	Lv_t				RevisionLevel;
	RevisionHP_t		RevisionHP;
	RevisionDP_t		RevisionDP;
	RevisionWeapon1_t	RevisionStandardWeapon;
	RevisionWeapon2_t	RevisionAdvancedWeapon;
	KillCnt_t			KillCount;
	DeathCnt_t			DeathCount;
	Minute_t			TimePenaltyValue;			// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ����� �г�Ƽ �߰�
	BOOL				bHaveReentryTicket;			// 2010-03-23 by cmkwon, ���Ǵ�Ƽ ���� ĳ�� ������ ���� - �ش� �������� �����ϱ� �ִ��� ����
	Penalty_t			HPPenaltyValue;				// 2011-06-14 by hskim, ���Ǵ�Ƽ 3�� - �г�Ƽ ��� �߰� (HP �� �ð� ���� ������ ����)
};

#define INFINITY_CREATE_MAP_CHANNEL_IDX_ERROR	-1

struct INFINITY_INSERT_ITEM_INFO {
	UID64_t			ItemUID;
	INT				ItemNum;
	INT				ItemWindowIndex;
	INT				CurrentCount;
	INT				PrefixCodeNum;
	INT				SuffixCodeNum;
	BYTE			Wear;
	INT				ShapeItemNum;
	INT				UsingTimeStamp;
	ATUM_DATE_TIME	CreatedTime;
	INT				CoolingTimeStamp;		// 2009-09-09 ~ 2010-02-10 by dhjin, ���Ǵ�Ƽ - �ߵ�������������
};
typedef mt_vector<INFINITY_INSERT_ITEM_INFO>			mtvectorInfinityInsertItemInfo;

struct INFINITY_UPDATE_ITEM_INFO {
	UID64_t			ItemUID;
	UID64_t			MainSvrItemUID;
	INT				ItemWindowIndex;
	INT				CurrentCount;
	BYTE			Wear;
	INT				UsingTimeStamp;
	INT				CoolingTimeStamp;		// 2009-09-09 ~ 2010-02-10 by dhjin, ���Ǵ�Ƽ - �ߵ�������������
};
typedef mt_vector<INFINITY_UPDATE_ITEM_INFO>			mtvectorInfinityUpdateItemInfo;

struct INFINITY_DELETE_ITEM_INFO {
	UID64_t			MainSvrItemUID;
};
typedef mt_vector<INFINITY_DELETE_ITEM_INFO>			mtvectorInfinityDeleteItemInfo;


///////////////////////////////////////////////////////////////////////////////
// 2009-12-11 by cmkwon, ������ ��׷η� Ÿ���� �����ϴ� ���� ���� - 
#define TICK_MONSTER_TARGET_UNCHANGE_TERM			15000			// 15�ʰ� Ÿ�� ����
#define TICK_MONSTER_DELETE_TARGET_TERM				15000			// 2010-03-02 by cmkwon, ���� Ÿ�� ���� üũ 15�ʷ� ���� - // ���Ͱ� 30�ʰ� �������� ���� Ÿ���� �����Ѵ�.

struct TENDER_INFO {
	TenderUID_t		TenderUID;
	ItemNum_t		TenderItemNum;
};
typedef vector<TENDER_INFO>								vectorTenderInfo;


#define MAX_DICE_COUNT						100
#define MIN_DICE_COUNT						1
#define EXIT_DICE_COUNT						100		// 2009-09-09 ~ 2010-01 by dhjin, ���Ǵ�Ƽ - �ҽ� üũ, ���� ���� ����

///////////////////////////////////////////////////////////////////////////////
// 2009-12-29 by cmkwon, ĳ���� �ִ� ���� ����(110����) - 1~100~110
#define CHARACTER_LEVEL_100					100
#define CHARACTER_LEVEL_100_MAX_STAT_POINT	300

// 2015-07-21 by bckim, ���� Ȯ�� ( 110 >> 115 )
#if defined(SC_LEVEL_EXPANSION_115_BCKIM_JWLEE)
#define CHARACTER_LEVEL_110					120	
#else
#define CHARACTER_LEVEL_110					110	
#endif
// End. 2015-07-21 by bckim, ���� Ȯ�� ( 110 >> 115 )

#define CHARACTER_LEVEL_110_MAX_STAT_POINT	340

///////////////////////////////////////////////////////////////////////////////////////
// start 2011-08-17 by hskim, ��Ʈ�� �ý��� 2�� - �ڷ� ���� ����
#define PET_LEVEL_25						25
#define PET_LEVEL_MAX						PET_LEVEL_25

// 2010-02-19 by cmkwon, 100���� ���� �ִ뽺�� ��ġ ���� ���� - 
#define GET_MAX_STAT_POINT(level)			( ((level) <= CHARACTER_LEVEL_100) ? CHARACTER_LEVEL_100_MAX_STAT_POINT : CHARACTER_LEVEL_110_MAX_STAT_POINT)

// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ����
struct INFINITY_SHOP_INFO {
	InfinityShopUID_t		InfinityShopUID;
	ItemNum_t				BuyItemNum;
	InfinityShopItemCnt_t	BuyItemCount;
	ItemNum_t				TradeItemNum1;
	InfinityShopItemCnt_t	TradeItemCount1;
	ItemNum_t				TradeItemNum2;
	InfinityShopItemCnt_t	TradeItemCount2;
	ItemNum_t				TradeItemNum3;
	InfinityShopItemCnt_t	TradeItemCount3;
	ItemNum_t				TradeItemNum4;
	InfinityShopItemCnt_t	TradeItemCount4;
	ItemNum_t				TradeItemNum5;	
	InfinityShopItemCnt_t	TradeItemCount5;
};
typedef vector<INFINITY_SHOP_INFO>						vectorInfinityShopInfo;


///////////////////////////////////////////////////////////////////////////////
// 2010-01-18 by cmkwon, ������ ���� Parameter �ߺ� üũ �ý��� ���� - 
struct SITEM_PARAM_OVERLAP
{
	INT			ItemNum;
	INT			OverlapIndex;		// ���� OverlapIndex�� ������ ��� �Ұ�
};
typedef vector<SITEM_PARAM_OVERLAP>		vectSITEM_PARAM_OVERLAP;	// 
typedef ez_map<INT, vectINT>			ezmapINT2vectINT;			// ITEMNUM and OverlapIndexVector

///////////////////////////////////////////////////////////////////////////////
// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - �ñ� ���� ������ ó��
struct INFINITY_DISCONNECTUSER_INFO {
	char					CharacterName[SIZE_MAX_CHARACTER_NAME];
	InfinityCreateUID_t		InfinityCreateUID;		// �ش� ���� ���� ��ȣ
	USHORT					MainServerID;			// ������ ĳ������ ����
	eINFINITY_MODE			InfinityMode;
};
typedef mt_vector<INFINITY_DISCONNECTUSER_INFO>		mtvectorInfinityDisConnectUser;

///////////////////////////////////////////////////////////////////////////////
// 2009-09-09 ~ 2010-02-10 by dhjin, ���Ǵ�Ƽ - �ߵ�������������
struct INVOKING_ITEM_DESTPARAM_TYPE {
	ItemUID_t				InvokingItemUID;
	DestParam_t				InvokingDestParam;
	ParamValue_t			InvokingDestParamValue;
	EffectIdx_t				InvokingEffectIdx;
};
typedef vector<INVOKING_ITEM_DESTPARAM_TYPE>		InvokingItemDestParamTypeList;
typedef mt_vector<INVOKING_ITEM_DESTPARAM_TYPE>		mtInvokingItemDestParamTypeList;

///////////////////////////////////////////////////////////////////////////////
// 2010-03-31 by dhjin, ���Ǵ�Ƽ(�������) - CINEMA_FIN_XXX
#define CINEMA_FIN_SUCCESS				51000
#define CINEMA_FIN_FAIL					52000
#define PENALTY_REMAIN_HP				100

// start 2011-04-08 by hskim, ���Ǵ�Ƽ 3�� - �ó׸� �ܰ躰 ��� ����
#define CINEMA_PLAYING_STEP_MAX			9			// �ִ� �����ϴ� Playing Step �� - �ִ� �� ����� eINFINITY_STATE / IS_INFINITY_STATE_PLAYING ������ ��

#define CINEMA_PLAYING_STEP_START_NUMBER			10001		// PLAYING ���� ���� ��ȣ	- STEP1 = 10001,	STEP2 = 10002,	STEP3 = 10003,	STEP4 = 10004,	STEP5 = 10005,	STEP6 = 10006, STEP7 = 10007, STEP8 = 10008
// end 2011-04-08 by hskim, ���Ǵ�Ƽ 3�� - �ó׸� �ܰ躰 ��� ����

// 2010-04-07 by cmkwon, ����2�� �߰� ���� - 
typedef enum
{
	INFINITY_FIN_UNKNOWN					= 0,		// �� �� ����
	INFINITY_FIN_SUCCESS_BY_PASS_ALL_STEP	= 100,		// ����: ��� �ܰ�(Step)�� ���
	INFINITY_FIN_SUCCESS_BY_TIMEOVER,					// ����: ���� �ð� ���
	INFINITY_FIN_SUCCESS_BY_DEAD_ALL_KEY_MONSTER_FOR_NEXTSTEP,	// 2010-04-09 by cmkwon, ����2��(���� ���� �߰�) - MPOPTION_BIT_KEY_MONSTER�� ������ ���Ͱ� ��� ���ŵ�
	INFINITY_FIN_FAIL_BY_TIMEOVER			= 200,		// ����: ���� �ð� ���
	INFINITY_FIN_FAIL_BY_DEAD_KEYMONSTER				// ����: Ű���� �ı���
} INFINITY_FIN_t;


///////////////////////////////////////////////////////////////////////////////
// 2010-04-20 by cmkwon, �ű� ��Ű �ӽ� ���� - ���� �ҽ� ���� - LUCKY_MACHINE_KIND_XXX, LUCKY_MACHINE_XXX
#define LUCKY_MACHINE_KIND_UNKNOWN				0		// �˼� ����
#define LUCKY_MACHINE_KIND_HAPPY_MACHINE		1		// ���Ǹӽ�
#define LUCKY_MACHINE_KIND_WEAPON_MACHINE		2		// ����ӽ�
#define LUCKY_MACHINE_KIND_ARMOR_MACHINE		3		// �ƸӸӽ�
#define LUCKY_MACHINE_KIND_MYSTARY_MACHINE		4		// �̽��׸��ӽ�

// 2010-06-01 by shcho, GLogDB ���� -
struct MOSTSTAYED_MAP_INFO
{
	MapIndex_t  MapIndex;	 // �ӹ��� �� �ε���
	DWORD		StayedTime;	 // �ӹ����� �� �����ð�
};

// 2010-08-05 by dhjin, ���׸� - 
typedef INT		BurningMapUID_t;
typedef	USHORT	UnitKind_t;
struct BURNING_MAP_INFO {
	BurningMapUID_t		BurningMapUID;
	MapIndex_t			MapIndex;
	UnitKind_t			ReqUnitKind;
	Lv_t				ReqMinLv;
	Lv_t				ReqMaxLv;
};
typedef vector<BURNING_MAP_INFO>	BurningMapInfoList;


///////////////////////////////////////////////////////////////////////////////////////
// start 2011-08-17 by hskim, ��Ʈ�� �ý��� 2�� - �ڷ� ���� ����

//////////
// ����

//// 2010-06-15 by shcho&hslee ��ý���
//#define SIZE_MAX_PETSKILLITEM 6			// ���� ��ų ������ ����.
//#define SIZE_MAX_PETSOCKETITEM 6		// ���� ���� ���� ����.
//
//typedef struct 
//{	// ���� �⺻ ����.
//
//	char	szPetName[SIZE_MAX_PET_NAME];
//
//	INT		UniqueNumber;
//	INT		PetIndex;
//	INT		PetKind;
//	BOOL	EnableName;
//	BOOL	EnableLevel;
//
//} tPET_BASEDATA;
//
//typedef std::vector< tPET_BASEDATA > vectorPetBaseData;
//
//typedef struct 
//{	// �� ������ ���� ����.
//
//	INT				UniqueNumber;
//	INT				Level;
//	Experience_t	NeedExp;	
//	DOUBLE			Stamina;
//	INT				CitySourceIndex;
//	INT				FieldSourceIndex;
//	INT				PetAttackIndex; // 2010-06-15 by shcho&hslee ��ý��� - �� ���� ó�� �Ѿ� �ε��� �ʵ� �߰�
//
//	INT				PetSkillItemIndex[SIZE_MAX_PETSKILLITEM];
//
//} tPET_LEVEL_DATA;
//
//typedef std::vector< tPET_LEVEL_DATA > vectorPetLevelData;
//
//struct tPET_BASE_ALL_DATA
//{
//	tPET_BASEDATA		BaseData;
//	vectorPetLevelData  vectPetLevelDataInfo;
//
//	tPET_LEVEL_DATA *rtn_LevelData ( const int a_iLevel )
//	{
//		for ( unsigned ui = 0; ui < this->vectPetLevelDataInfo.size(); ++ui )
//		{
//			if ( this->vectPetLevelDataInfo[ui].Level == a_iLevel )
//				return &this->vectPetLevelDataInfo[ui];
//		}
//		return NULL;
//	}
//
//};
//
//typedef std::vector< tPET_BASE_ALL_DATA > vectorPetDataInfo;
//
//struct tPET_CURRENTINFO
//{	// ������ �� ����.
//
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
//	DOUBLE			Stamina;
//
//	INT				SourceIndex_Field;
//	INT				SourceIndex_City;
//
//	const ITEM			*pItem_PetSkill[SIZE_MAX_PETSKILLITEM];
//	const ITEM			*pItem_PetSocketItem[SIZE_MAX_PETSOCKETITEM];
//
//#ifdef _ATUM_SERVER
//
//	tPET_CURRENTINFO ( tPET_CURRENTINFO *pPetCurInfo )
//	{
//		if ( pPetCurInfo )
//			memcpy ( this , pPetCurInfo , sizeof( tPET_CURRENTINFO ) );
//		else
//			memset ( this , 0x00 , sizeof( tPET_CURRENTINFO ) );
//	}
//
//	void * operator new(size_t size);
//	void operator delete(void* p);
//#endif
//	
//};
//
//typedef std::vector		< tPET_CURRENTINFO* > vecPetCurrentInfo;
//
//typedef mt_vector		< tPET_CURRENTINFO* > mtvectPetCurrentInfo;
//
// End 2010-06-15 by shcho&hslee ��ý���

///////////////////////////////////////////////////////////////////////////////////////
// ����

#define SIZE_MAX_PETSOCKET					6		// ���� ���� ���� ����
#define SIZE_MAX_PETSOCKET_AUTOSKILL_SLOT	6		// ���� ���� ��ų ���� ����

typedef struct 
{
	INT		PetIndex;
	char	PetName[SIZE_MAX_PET_NAME];	
	INT		PetKind;
	BOOL	EnableName;
	BOOL	EnableLevel;
	INT		MaxLevel;
	INT		BaseSocketCount;

} tPET_BASEDATA;

typedef std::vector< tPET_BASEDATA > vectorPetBaseData;

typedef struct 
{
	INT				PetIndex;
	INT				Level;
	Experience_t	NeedExp;	
	INT				UseWeaponIndex;
	BYTE			SlotCountSkill;		// ���� �������� �����ϴ� ��ų ��
	BYTE			SlotCountSocket;	// ���� �������� �����ϴ� ���� ��
	BYTE			KitLevelHP;			// ���� �������� �����ϴ� �ְ� HP Kit
	BYTE			KitLevelShield;		// ���� �������� �����ϴ� �ְ� ���� Kit
	BYTE			KitLevelSP;			// ���� �������� �����ϴ� �ְ� SP Kit

} tPET_LEVEL_DATA;

typedef std::vector< tPET_LEVEL_DATA > vectorPetLevelData;

struct tPET_BASE_ALL_DATA
{
	tPET_BASEDATA		BaseData;
	vectorPetLevelData  vectPetLevelDataInfo;

	tPET_LEVEL_DATA *rtn_LevelData ( const int a_iLevel )
	{
		for ( unsigned ui = 0; ui < this->vectPetLevelDataInfo.size(); ++ui )
		{
			if ( this->vectPetLevelDataInfo[ui].Level == a_iLevel )
				return &this->vectPetLevelDataInfo[ui];
		}
		return NULL;
	}

};

typedef std::vector< tPET_BASE_ALL_DATA > vectorPetDataInfo;

struct SPET_KIT_SLOT_ITEM_LEVEL
{
	int Level;				// ����				[0 ~ 100]
	int	ItemNum;			// ������ ��ȣ
};

struct SSort_KIT_SLOT_ITEM_LEVEL_BY_LEVEL: binary_function<int, int, bool>
{
	bool operator()(SPET_KIT_SLOT_ITEM_LEVEL param1, SPET_KIT_SLOT_ITEM_LEVEL param2)
	{
        return param1.Level < param2.Level;
    };
};

typedef std::vector<SPET_KIT_SLOT_ITEM_LEVEL> vectorPetKitLevel;		// �ӵ� ����ȭ�� ���ؼ� �� �����ؼ� ����ϼ���


struct SPET_AUTOSKILL_SLOT_ITEM
{
	int	ItemNum;
};

typedef std::vector<SPET_AUTOSKILL_SLOT_ITEM> vectorPetAutoSkill;


struct SPET_KIT_SLOT_DATA
{
	INT		ItemNum;
	float	TriggerValue;
};

struct SPET_AUTOSKILL_SLOT_DATA
{
	INT		ItemNum[SIZE_MAX_PETSOCKET_AUTOSKILL_SLOT];
};

struct tPET_CURRENTINFO
{
	UID64_t			CreatedPetUID;
	char			PetName[SIZE_MAX_PET_NAME];
	INT				PetIndex;
	INT				PetLevel;
	Experience_t	PetExp;
	BYTE			PetExpRatio;
	BYTE			PetEnableSocketCount;
	UID64_t			PetSocketItemUID[SIZE_MAX_PETSOCKET];

	// ���� ������ ����

	SPET_KIT_SLOT_DATA	PetKitHP;
	SPET_KIT_SLOT_DATA	PetKitShield;
	SPET_KIT_SLOT_DATA	PetKitSP;

	SPET_AUTOSKILL_SLOT_DATA	PetAutoSkill;

	// ��ũ

	ITEM			*pItemPetSocket[SIZE_MAX_PETSOCKET];

#ifdef _ATUM_SERVER
	tPET_CURRENTINFO ( tPET_CURRENTINFO *pPetCurInfo )
	{
		if ( pPetCurInfo )
			memcpy ( this , pPetCurInfo , sizeof( tPET_CURRENTINFO ) );
		else
			memset ( this , 0x00 , sizeof( tPET_CURRENTINFO ) );
	}

	void * operator new(size_t size);
	void operator delete(void* p);
#endif
	
};

typedef std::vector		< tPET_CURRENTINFO* > vecPetCurrentInfo;
typedef mt_vector		< tPET_CURRENTINFO* > mtvectPetCurrentInfo;

// end 2011-08-17 by hskim, ��Ʈ�� �ý��� 2�� - �ڷ� ���� ����
///////////////////////////////////////////////////////////////////////////////////////

// 2010-06-15 by shcho&hslee ��ý��� - ���۷����� ����

struct OperatorInfo
{	// ���۷����� ����.
	int		ActionType;
	int		Itemnum;
	int		FunctionIndex;
	double	FunctionValue;
	int		SourceIndex;
	char	ActionDesc[128]; 
};

typedef std::vector< OperatorInfo > vectorOperatorInfo;

// END 2010-06-15 by shcho&hslee ��ý��� - ���۷����� ����

// 2010-08-31 by shcho&jskim �����ۿ��� �ý��� - ���� ������ ���� ����ü 

#define SIZE_MAX_DISSOLUTION_ITEMS	3

struct tDissolutionItemInfo
{
	INT		SourceItemnum;				// ���� �� ������ ��ȣ
	INT		ResultItemNum[SIZE_MAX_DISSOLUTION_ITEMS];			// ��� ������ ��ȣ
	INT		ResultItemMinCount[SIZE_MAX_DISSOLUTION_ITEMS];		// ������ �ּ� ����
	INT		ResultItemMaxCount[SIZE_MAX_DISSOLUTION_ITEMS];		// ������ �ִ� ����
	INT		ResultItemProbabillity[SIZE_MAX_DISSOLUTION_ITEMS];	// ������ ���� Ȯ��
};

struct DissolutionItems
{
	INT Itemnum[SIZE_MAX_DISSOLUTION_ITEMS];
	INT Itemcount[SIZE_MAX_DISSOLUTION_ITEMS];
};

typedef std::vector<tDissolutionItemInfo> vectorDissolutionItemInfo; // ������ ���
typedef mt_map<INT, tDissolutionItemInfo> mtmapDissolutionItemInfo; // �ʿ� ����

// END 2010-08-31 by shcho&jskim �����ۿ��� �ý��� - ���� ������ ���� ����ü 

// start 2011-03-17 by hskim, ���Ǵ�Ƽ 3�� - ���� ��Ƽ Ÿ���� ��� �߰�

// 2011-03-18 by hskim, ���Ǵ�Ƽ 3�� - �۾��� Ŭ��� ���� ����� �ڷ��� ����
typedef enum 
{
	DB_ITEM,
	DB_MONSTER_INFO,
	DB_MAPOBJECT,
	DB_RARE_ITEM,
	DB_BUILDINGNPC,
	DB_GUILD_MARK,
	DB_MAP_INFO,
	DB_MIXING_INFO,
	DB_MYSTERY_ITEM_DROP,
	// 2009-03-04 by bhsohn ��Ű �ӽ� ������
	DB_LUCKYMACHINE,
	// end 2009-03-04 by bhsohn ��Ű �ӽ� ������
	// 2010. 02. 11 by ckPark �ߵ��� ����������
	DB_INVOKINGWEARITEM_DPNUM,			// 2009-09-09 ~ 2010-02-10 by dhjin, ���Ǵ�Ƽ - �ߵ�������������
	DB_INVOKINGWEARITEM_DPNUM_BY_USE,	// 2009-09-09 ~ 2010-02-10 by dhjin, ���Ǵ�Ƽ - �ߵ�������������
	// end 2010. 02. 11 by ckPark �ߵ��� ����������

	// 2010-08-10 by dgwoo ���׸� �ý���
	DB_BURNING_MAP,
	// 2010-08-10 by dgwoo ���׸� �ý���

	// 2010-06-15 by shcho&hslee ��ý���
	DB_PET_BASEDATA,						// 2010-06-15 by shcho&hslee ��ý��� - �� �⺻ ����.
	DB_PET_LEVELDATA,						// 2010-06-15 by shcho&hslee ��ý��� - �� ������ ��������.
	DB_PET_OPERATOR,						// 2010-06-15 by shcho&hslee ��ý��� - ���۷����� ����
	// End 2010-06-15 by shcho&hslee ��ý���
	DB_DISSOLUTIONITEM,					// 2010-08-31 by shcho&&jskim, ���� �ý��� ����
	DB_MONSTER_MULTI_TARGET					// 2011-03-17 by hskim, ���Ǵ�Ƽ 3�� - ���� ��Ƽ Ÿ���� ��� �߰�

} DB_TYPE;

// 2011. 03. 08 by jskim ����3�� ����
struct DATA_HEADER
{
	DB_TYPE nType;
	int nDataCount;
};
// end 2011. 03. 08 by jskim ����3�� ����

///////////////////////////////////////////////////////////////////////////////
// MonsterMultiTarget - Parameter Struct ����
// 2011-03-17 by hskim, ����ƼƼ 3�� ���� ��Ƽ Ÿ���� ��� �߰�
///////////////////////////////////////////////////////////////////////////////
struct MONSTER_MULTI_TARGET
{
	INT			MonsterIndex;						// ���� ���� ��ȣ
	INT			PointIndex;							// �߰��� ���� Ÿ���� ��ȣ
	D3DXVECTOR3	TargetPosition;						// �߰��� ���� ��ǥ (x,y,z)
};
typedef std::vector<MONSTER_MULTI_TARGET>	vectorMonsterMultiTarget;
typedef std::vector<MONSTER_MULTI_TARGET>::iterator vectoritMonsterMultiTarget;
// end 2011-03-17 by hskim, ���Ǵ�Ƽ 3�� - ���� ��Ƽ Ÿ���� ��� �߰�

// 2013-08-28 by bckim, �������� ����ȭ
struct BOSS_MONSTER_REWARD_INFO
{
	INT					MonsterIndex;						// ���� ���� ��ȣ
	BOSS_MONSTER_REWARD	BossMonsterReward;
};
typedef std::vector<BOSS_MONSTER_REWARD_INFO>	vectorBossMonsterReward;
typedef std::vector<BOSS_MONSTER_REWARD_INFO>::iterator vectoritBossMonsterReward;
// End. 2013-08-28 by bckim, �������� ����ȭ

// 2010-11 by dhjin, �ƶ󸮿� ä�θ� �α���.
typedef enum
{
	CONNECT_PUBLISHER_DEFAULT = 0,
	CONNECT_PUBLISHER_NHN_JPN = 1
} eCONNECT_PUBLISHER;

char* GetConnectPublisherName(eCONNECT_PUBLISHER i_eCONNECT_PUBLISHER);

// start 2011-05-17 by hskim, ���Ǵ�Ƽ 3�� - �ó׸� ����
///////////////////////////////////////////////////////////////////////////////
// �ó׸�(DB:account, ti_Cinema) Ŀ���� �ε���(CustomIdx) ����
// 2011-05-17 by hskim, ���Ǵ�Ƽ 3�� - �ó׸� ����
//
// �ó׸����� ���������� ������� ���� ����� ���⿡ �߰� �����Ѵ�.
///////////////////////////////////////////////////////////////////////////////
enum
{
	INFINITY3_STEP5_MOVIE_START			= 1,		// ���Ǵ�Ƽ 3�� - ���� 5 - ���� �� ħ�� ���� ����
	INFINITY3_STEP5_MOVIE_END			= 2,		// ���Ǵ�Ƽ 3�� - ���� 5 - ���� �� ħ�� ���� ����
	INFINITY3_STEP5_TIMELIMIT_SET		= 3,		// ���Ǵ�Ƽ 3�� - ���� 6 - �� Ż�� �ð� �缳��
	INFINITY3_STEP6_MOVE_SUCCESS_POSITION	= 4,		// ���Ǵ�Ƽ 3�� - ���� 7 - ĳ���� ��ġ �̵� (����) - �ó׸� ���� ���۽� ���� ����
	INFINITY3_STEP6_MOVE_FAIL_POSITION		= 5,		// ���Ǵ�Ƽ 3�� - ���� 7 - ĳ���� ��ġ �̵� (����) - �ó׸� ���� ���۽� ���� ����
	INFINITY3_FAIL_MOVIE_START				= 6			// ���Ǵ�Ƽ 3�� - ���н� - �Ʊ� �� ħ�� ���� ����
};


///////////////////////////////////////////////////////////////////////////////
// MSG_FC_INFINITY_MOVIE �޽��� ���� ��ȣ(UniqueNumber) ����
// 2011-05-17 by hskim, ���Ǵ�Ƽ 3�� - �ó׸� ����
///////////////////////////////////////////////////////////////////////////////
enum
{
	INFINITY_MOVIE_001_INF3_STEP5		= 1,		// ���Ǵ�Ƽ 3�� - ���� �� ħ�� ����
	INFINITY_MOVIE_002_INF3_FAIL		= 2			// ���Ǵ�Ƽ 3�� - �Ʊ� �� ħ�� ����
};

///////////////////////////////////////////////
// MSG_FC_INFINITY_MOVIE �޽��� Command ����
enum
{
	MOVIE_COMMAND_START					= 1,		// ���� ����
	MOVIE_COMMAND_END					= 2			// ���� ����
};
// end 2011-05-17 by hskim, ���Ǵ�Ƽ 3�� - �ó׸� ����

///////////////////////////////////////////////////////////////////////////////
// WayPoint ���� - Parameter Struct �� Define ����
// 2011-05-23 by hskim, ���Ǵ�Ƽ 3�� - ��������Ʈ ����
///////////////////////////////////////////////////////////////////////////////

// SWAY_POINT.byPostionAttribute �Ӽ�
#define WAY_POINT_POSITION_ATTRIBUTE_RELATIVE			0			// ��� ��ǥ						- ���� ����
#define WAY_POINT_POSITION_ATTRIBUTE_ABSOLUTE			1			// ���� ��ǥ		- ��� ����

// CWayPointPattern.m_byCompletionAction �Ӽ�
#define WAY_POINT_COMPLETION_ACTION_REPEAT				0			// �ݺ�
#define WAY_POINT_COMPLETION_ACTION_RECIPROCATION		1			// �պ�
#define WAY_POINT_COMPLETION_ACTION_STOP				2			// ����

#define WAY_POINT_COLLISION_THRESHOLD					2000.0f		// WAY_POINT ���� ������ Threshold ��

struct SWAY_POINT
{
	UINT dwPatternIndex;				// ���� ��ȣ
	UINT dwSequenceNum;					// ��������Ʈ ����
	BYTE byPostionAttribute;			// �Ӽ�				(���� ��ǥ, ��� ��ǥ)								/ ���� ���� : ���� ��ǥ
	D3DXVECTOR3 vPoint;					// ��ǥ
	
	SWAY_POINT()
	{
		dwPatternIndex = 0;
		dwSequenceNum = 0;
		byPostionAttribute = WAY_POINT_POSITION_ATTRIBUTE_RELATIVE;
		vPoint = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	
	SWAY_POINT(UINT i_dwPatternNum, UINT i_dwSequenceNum, BYTE i_byPostionAttribute, D3DXVECTOR3 i_vPoint)
	{
		dwPatternIndex = i_dwPatternNum;
		dwSequenceNum = i_dwSequenceNum;
		byPostionAttribute = i_byPostionAttribute;
		vPoint = i_vPoint;
	}
};

struct SWAY_POINT_MOVE
{
	UINT dwIndex;						// ���� ��ȣ
	BYTE byCompletionAction;			// �Ϸ� �� ����		(�ݺ�, �պ�, ����)
};

typedef vector<SWAY_POINT>	vectorWayPoint;
typedef vector<SWAY_POINT_MOVE>	vectorWayPointMove;

struct SSORT_WAY_POINT_BY_SEQUENCE_NUMBER : binary_function<SWAY_POINT, SWAY_POINT, bool>
{
	bool operator()(SWAY_POINT Param1, SWAY_POINT Param2)
	{
        return Param1.dwSequenceNum < Param2.dwSequenceNum;		// ���� ���� ����
    };
};
// end 2011-05-23 by hskim, ���Ǵ�Ƽ 3�� - ��������Ʈ ����

// start 2011-05-30 by hskim, ���Ǵ�Ƽ 3�� - �÷��� �ð� �缳�� ���
#define INFINITY3_STEP6_TIMELIMIT_VALUE			60000		// (1 min * 60 sec * 1000 ms)
// end 2011-05-30 by hskim, ���Ǵ�Ƽ 3�� - �÷��� �ð� �缳�� ���

// start 2011-06-01 ���Ǵ�Ƽ 3�� - ���� 7 - ĳ���� ��ġ �̵�
#define INFINITY3_STEP6_MOVE_SUCCESS_POSTION_X			500.0f
#define INFINITY3_STEP6_MOVE_SUCCESS_POSTION_Y			2500.0f
#define INFINITY3_STEP6_MOVE_SUCCESS_POSTION_Z			3500.0f

#define INFINITY3_STEP6_MOVE_FAIL_POSTION_X				9800.0f
#define INFINITY3_STEP6_MOVE_FAIL_POSTION_Y				3500.0f
#define INFINITY3_STEP6_MOVE_FAIL_POSTION_Z				5000.0f
// end 2011-06-01 ���Ǵ�Ƽ 3�� - ���� 7 - ĳ���� ��ġ �̵�

// start 2011-07-15 by shcho - ĳ�������� üũ �ý��� ����
struct cashItemCheckData
{
	int ItemNumber;
	int	Price;
	int	CashPrice;
	int	Time;
	int ItemAttribute;
	int UniqueNumber;
};

typedef vector<cashItemCheckData> vectCashCheckData;

#define OLD_DATA	0
#define NEW_DATA	1
// end 2011-07-15 by shcho - ĳ�������� üũ �ý��� ����

// START 2011-11-03 by shcho, yedang �˴ٿ��� ���� - �˴ٿ����� üũ�� ����
struct ShutdownUserData
{ // �߰��� ������ �����Ƿ� �ϴ� ����� ����
	UID32_t			Account_UniqueNumber;
	UID32_t			CharacterUniqueNumber[3];
};
typedef vector<ShutdownUserData> vectShutDownUserData;

#define SHUTDOWNMINORS_YEARS_OLD	16
// END 2011-11-03 by shcho, yedang �˴ٿ��� ���� - �˴ٿ����� üũ�� ����

// 2011-11-18 by shcho, �����ٿ� ���������ٿ� ���� ó�� - üũ �Լ� �߰�
BOOL CheckAdminCommand(char *token);
		   
char *StrCaseStr(const char *s, const char *find);		// 2013-03-13 by hskim, �� ĳ�� ���� - RawData ���� ��� �߰�
char *StrRCaseStr(const char *s, const char *find);		// 2013-03-13 by hskim, �� ĳ�� ���� - RawData ���� ��� �߰�
// start 2011-10-10 by hskim, EP4 [Ʈ���� �ý���] - ȭ���� / �� ��ǳ
struct STRIGGER_MAP_BUFF
{
	MapIndex_t MapIndex;		// ���� ��
	ItemNum_t ItemNum;		// ���� ���� (ItemNum : ��ų ��ȣ)

	STRIGGER_MAP_BUFF()
	{
		MapIndex = 0;
		ItemNum = 0;
	}

	STRIGGER_MAP_BUFF(MapIndex_t i_MapIndex, ItemNum_t i_ItemNum)
	{
		MapIndex = i_MapIndex;
		ItemNum = i_ItemNum;
	}
};
typedef vector<STRIGGER_MAP_BUFF>	vectorTriggerMapBuff; //���̵� ����Ʈ ����
// end 2011-10-10 by hskim, EP4 [Ʈ���� �ý���] - ȭ���� / �� ��ǳ

// start 2011-10-28 by hskim, EP4 [Ʈ���� �ý���] - ũ����Ż �ý���

// Ʈ���� - NGC������

#define STRIGEER_NGCINFLWAR_MAPINDEX_1ST		4101
#define STRIGEER_NGCINFLWAR_MAPINDEX_2ND		4301
#define STRIGEER_NGCINFLWAR_WW2_EVENT_MAPINDEX_BCU		9021		// 2013-07-08 by jhseol, Ʈ���� �ý��� Ȯ�� - 2�� ������� BCU �̺�Ʈ��
#define STRIGEER_NGCINFLWAR_WW2_EVENT_MAPINDEX_ANI		9022		// 2013-07-08 by jhseol, Ʈ���� �ý��� Ȯ�� - 2�� ������� ANI �̺�Ʈ��
#define STRIGEER_NGCINFLWAR_WW2_EVENT_ITEM_NUM			COLLECTION_XAM_ENCHANT_RETURN_ITEMNUM			// 2013-07-08 by jhseol, Ʈ���� �ý��� Ȯ�� - ���� ������ ��ȣ
#define STRIGEER_NGCINFLWAR_WW2_EVENT_ITEM_COUNT		1			// 2013-07-08 by jhseol, Ʈ���� �ý��� Ȯ�� - ���� ������ ����
#define STRIGEER_NGCINFLWAR_WW2_EVENT_TRIGGER_FUNID_BCU		6000	// 2013-07-08 by jhseol, Ʈ���� �ý��� Ȯ�� - 2�� ������� BCU Ʈ���� ID
#define STRIGEER_NGCINFLWAR_WW2_EVENT_TRIGGER_FUNID_ANI		7000	// 2013-07-08 by jhseol, Ʈ���� �ý��� Ȯ�� - 2�� ������� ANI Ʈ���� ID

#define STRIGEER_NGCINFLWAR_EVENT_2ND_TOP_GROUP_ITEM_UID			7035110
#define STRIGEER_NGCINFLWAR_EVENT_2ND_TOP_GROUP_ITEM_COUNT			1
#define STRIGEER_NGCINFLWAR_EVENT_2ND_MIDDLE_GROUP_ITEM_UID			7035120
#define STRIGEER_NGCINFLWAR_EVENT_2ND_MIDDLE_GROUP_ITEM_COUNT		1
#define STRIGEER_NGCINFLWAR_EVENT_2ND_ALL_ITEM_UID					7035130
#define STRIGEER_NGCINFLWAR_EVENT_2ND_ALL_ITEM_COUNT				1

#ifdef _DEBUG
#define STRIGEER_NGCINFLWAR_EVENT_2ND_TOP_GROUP_ITEM_PAY_RANK		2		// �׽�Ʈ �� ����
#define STRIGEER_NGCINFLWAR_EVENT_2ND_MIDDLE_GROUP_ITEM_PAY_RANK	4
#else
#define STRIGEER_NGCINFLWAR_EVENT_2ND_TOP_GROUP_ITEM_PAY_RANK		5		// ���� ���� �� ����
#define STRIGEER_NGCINFLWAR_EVENT_2ND_MIDDLE_GROUP_ITEM_PAY_RANK	15
#endif

// Ʈ���� - ũ����Ż

#define STRIGEER_CRYSTAL_MAPINDEX_1ST			4100
#define STRIGEER_CRYSTAL_MAPINDEX_2ND			4300

#ifdef _DEBUG
#define STRIGGER_CRYSTAL_NEXT_CREATE_TIME		10		// ��
#else
#define STRIGGER_CRYSTAL_NEXT_CREATE_TIME		60		// ��
#define STRIGGER_CRYSTAL_NEXT_EVENT_1ST			20		// ��
#define STRIGGER_CRYSTAL_NEXT_EVENT_2ND			45		// ��
#endif

#define STRIGEER_CRYSTAL_EVENT_NONE						0
#define STRIGEER_CRYSTAL_EVENT_HELL_WARP				1
#define STRIGGER_CRYSTAL_EVENT_SUMMON_BOSS_MONSTER		2
#define STRIGGER_CRYSTAL_EVENT_SHOP_KIT					3
#define STRIGGER_CRYSTAL_EVENT_EXP_100					4
#define STRIGGER_CRYSTAL_EVENT_SHOP_HYPER_CARD			5
#define STRIGGER_CRYSTAL_EVENT_SHOP_SEAL				6
#define STRIGGER_CRYSTAL_EVENT_DROP_100					7
#define STRIGGER_CRYSTAL_EVENT_EXP_SPI_DROP_100			8

#define STRIGGER_CRYSTAL_EVENT_2ND_WARPOINT				21
#define STRIGGER_CRYSTAL_EVENT_2ND_SUMMON_BOSS_MONSTER	22
#define STRIGGER_CRYSTAL_EVENT_2ND_EXP_150				23
#define STRIGGER_CRYSTAL_EVENT_2ND_DROP_150				24
#define STRIGGER_CRYSTAL_EVENT_2ND_EXP_SPI_DROP_150		25
#define STRIGGER_CRYSTAL_EVENT_2ND_CAPSULE_ITEM			26
#define STRIGGER_CRYSTAL_EVENT_2ND_SHOP_PREFIX_SUFFIX	27
#define STRIGGER_CRYSTAL_EVENT_2ND_SHOP_KIT				28
#define STRIGGER_CRYSTAL_EVENT_2ND_SHOP_HYPER_CARD		29
#define STRIGGER_CRYSTAL_EVENT_2ND_SHOP_WEAPON			30
#define STRIGGER_CRYSTAL_EVENT_2ND_HELL_WARP			31

// 2014-03-12 by bckim, ����Ÿ��(��������)
// mapindex : 3091
#define STRIGGER_CRYSTAL_EVENT_BURNING_1ND_SUMMON_BOSS_MONSTER_40	40
#define STRIGGER_CRYSTAL_EVENT_BURNING_1ND_SUMMON_BOSS_MONSTER_41	41
#define STRIGGER_CRYSTAL_EVENT_BURNING_1ND_SUMMON_BOSS_MONSTER_42	42
#define STRIGGER_CRYSTAL_EVENT_BURNING_1ND_SUMMON_BOSS_MONSTER_43	43
#define STRIGGER_CRYSTAL_EVENT_BURNING_1ND_SUMMON_BOSS_MONSTER_44	44
#define STRIGGER_CRYSTAL_EVENT_BURNING_1ND_SUMMON_BOSS_MONSTER_45	45
#define STRIGGER_CRYSTAL_EVENT_BURNING_1ND_VALUE_SUMMON_BOSS_MONSTER_UID_40			2128800
#define STRIGGER_CRYSTAL_EVENT_BURNING_1ND_VALUE_SUMMON_BOSS_MONSTER_UID_41			2128900
#define STRIGGER_CRYSTAL_EVENT_BURNING_1ND_VALUE_SUMMON_BOSS_MONSTER_UID_42			2128300
#define STRIGGER_CRYSTAL_EVENT_BURNING_1ND_VALUE_SUMMON_BOSS_MONSTER_UID_43			2128500
#define STRIGGER_CRYSTAL_EVENT_BURNING_1ND_VALUE_SUMMON_BOSS_MONSTER_UID_44			2128200
#define STRIGGER_CRYSTAL_EVENT_BURNING_1ND_VALUE_SUMMON_BOSS_MONSTER_UID_45			2128400

// mapindex : 3092
#define STRIGGER_CRYSTAL_EVENT_BURNING_2ND_SUMMON_BOSS_MONSTER_50	50		
#define STRIGGER_CRYSTAL_EVENT_BURNING_2ND_SUMMON_BOSS_MONSTER_51	51
#define STRIGGER_CRYSTAL_EVENT_BURNING_2ND_SUMMON_BOSS_MONSTER_52	52
#define STRIGGER_CRYSTAL_EVENT_BURNING_2ND_SUMMON_BOSS_MONSTER_53	53
#define STRIGGER_CRYSTAL_EVENT_BURNING_2ND_SUMMON_BOSS_MONSTER_54	54
#define STRIGGER_CRYSTAL_EVENT_BURNING_2ND_SUMMON_BOSS_MONSTER_55	55
#define STRIGGER_CRYSTAL_EVENT_BURNING_2ND_VALUE_SUMMON_BOSS_MONSTER_UID_50			2129000
#define STRIGGER_CRYSTAL_EVENT_BURNING_2ND_VALUE_SUMMON_BOSS_MONSTER_UID_51			2129100
#define STRIGGER_CRYSTAL_EVENT_BURNING_2ND_VALUE_SUMMON_BOSS_MONSTER_UID_52			2128500
#define STRIGGER_CRYSTAL_EVENT_BURNING_2ND_VALUE_SUMMON_BOSS_MONSTER_UID_53			2128700
#define STRIGGER_CRYSTAL_EVENT_BURNING_2ND_VALUE_SUMMON_BOSS_MONSTER_UID_54			2128400
#define STRIGGER_CRYSTAL_EVENT_BURNING_2ND_VALUE_SUMMON_BOSS_MONSTER_UID_55			2128600

#define IS_CRYSTAL_EVENT_BURNING(x)	((EventID_t)(x) >= STRIGGER_CRYSTAL_EVENT_BURNING_1ND_SUMMON_BOSS_MONSTER_40 && (EventID_t)(x) <= STRIGGER_CRYSTAL_EVENT_BURNING_2ND_SUMMON_BOSS_MONSTER_55 )
#define IS_CRYSTAL_EVENT_BURNING_MAP_2(x)	((EventID_t)(x) >= STRIGGER_CRYSTAL_EVENT_BURNING_1ND_SUMMON_BOSS_MONSTER_40 && (EventID_t)(x) <= STRIGGER_CRYSTAL_EVENT_BURNING_1ND_SUMMON_BOSS_MONSTER_45 )
#define IS_CRYSTAL_EVENT_BURNING_MAP_3(x)	((EventID_t)(x) >= STRIGGER_CRYSTAL_EVENT_BURNING_2ND_SUMMON_BOSS_MONSTER_50 && (EventID_t)(x) <= STRIGGER_CRYSTAL_EVENT_BURNING_2ND_SUMMON_BOSS_MONSTER_55 )


// End. 2014-03-12 by bckim, ����Ÿ��(��������)

#define STRIGGER_CRYSTAL_EVENT_VALUE_SUMMON_BOSS_MONSTER_UID					2111500

#define STRIGGER_CRYSTAL_EVENT_2ND_VALUE_SUMMON_BOSS_MONSTER_TOTAL_COUNT		6
#define STRIGGER_CRYSTAL_EVENT_2ND_VALUE_SUMMON_BOSS_MONSTER_UID_01				2114600
#define STRIGGER_CRYSTAL_EVENT_2ND_VALUE_SUMMON_BOSS_MONSTER_UID_02				2114700
#define STRIGGER_CRYSTAL_EVENT_2ND_VALUE_SUMMON_BOSS_MONSTER_UID_03				2114800
#define STRIGGER_CRYSTAL_EVENT_2ND_VALUE_SUMMON_BOSS_MONSTER_UID_04				2114900
#define STRIGGER_CRYSTAL_EVENT_2ND_VALUE_SUMMON_BOSS_MONSTER_UID_05				2115000
#define STRIGGER_CRYSTAL_EVENT_2ND_VALUE_SUMMON_BOSS_MONSTER_UID_06				2115100

#define STRIGGER_CRYSTAL_EVENT_2ND_VALUE_SUMMON_BOSS_MONSTER_COUNT				1
#define STRIGGER_CRYSTAL_EVENT_2ND_VALUE_SUMMON_BOSS_MONSTER_RANDOM_POS			0

#define STRIGGER_CRYSTAL_EVENT_VALUE_KIT_SHOP_ITEM_BUILDING_INDEX				9369
#define STRIGGER_CRYSTAL_EVENT_VALUE_HYPER_CARD_SHOP_ITEM_BUILDING_INDEX		9370
#define STRIGGER_CRYSTAL_EVENT_VALUE_SEAL_SHOP_ITEM_BUILDING_INDEX				9371

#define STRIGGER_CRYSTAL_EVENT_2ND_VALUE_PREFIX_SUFFIX_SHOP_ITEM_BUILDING_INDEX	9372
#define STRIGGER_CRYSTAL_EVENT_2ND_VALUE_KIT_SHOP_ITEM_BUILDING_INDEX			9373
#define STRIGGER_CRYSTAL_EVENT_2ND_VALUE_HYPER_CARD_SHOP_ITEM_BUILDING_INDEX	9374
#define STRIGGER_CRYSTAL_EVENT_2ND_VALUE_SEAL_SHOP_ITEM_BUILDING_INDEX			9375

///////////////////////////////////////////////////////////////////////////////////////
// �̸�							���� ������Ʈ	��ü ������Ʈ	EventwParam1
///////////////////////////////////////////////////////////////////////////////////////
// ȭ��� ���� 1				3202000			93202000		201
// ȭ��� ���� 2				3202100			93202100		202
// ȭ��� ���� 3				3202200			93202200		203
//
// ������ ���� �浹������Ʈ #1	3202600			93202600		9857		<-- ��� ���� 9856 �̳� 9857 ��ü
// ������ ���� �浹������Ʈ #2	3202700			93202700		9856		<-- ��� ���� 9857 �̳� 9856 ��ü 
// ������ ���� ������Ʈ			3202800			93202800		401
///////////////////////////////////////////////////////////////////////////////////////

#define STRIGGER_CRYSTAL_EVENT_SHOP_INIT_VOLUME									0			// �� ���½� �ʱ� ���� ���� (Ȥ�� �� ��Ȳ�� ���� 0���� �ʱ�ȭ)

#define STRIGGER_CRYSTAL_EVENT_VALUE_KIT_SHOP_OBJECT_IDX						201
#define STRIGGER_CRYSTAL_EVENT_VALUE_KIT_SHOP_OBJECT_NUM_DEFAULT				3202000
#define STRIGGER_CRYSTAL_EVENT_VALUE_KIT_SHOP_OBJECT_NUM_CHANGE					93202000

#define STRIGGER_CRYSTAL_EVENT_VALUE_HYPER_CARD_SHOP_OBJECT_IDX					202
#define STRIGGER_CRYSTAL_EVENT_VALUE_HYPER_CARD_SHOP_OBJECT_NUM_DEFAULT			3202100
#define STRIGGER_CRYSTAL_EVENT_VALUE_HYPER_CARD_SHOP_OBJECT_NUM_CHANGE			93202100

#define STRIGGER_CRYSTAL_EVENT_VALUE_SEAL_SHOP_OBJECT_IDX						203
#define STRIGGER_CRYSTAL_EVENT_VALUE_SEAL_SHOP_OBJECT_NUM_DEFAULT				3202200
#define STRIGGER_CRYSTAL_EVENT_VALUE_SEAL_SHOP_OBJECT_NUM_CHANGE				93202200

#define STRIGGER_CRYSTAL_EVENT_VALUE_WARP_OBJECT_IDX							9857
#define STRIGGER_CRYSTAL_EVENT_VALUE_WARP_OBJECT_NUM_DEFAULT					3202600
#define STRIGGER_CRYSTAL_EVENT_VALUE_WARP_OBJECT_NUM_CHANGE						93202600

#define STRIGGER_CRYSTAL_EVENT_VALUE_WARP2_OBJECT_IDX							9856
#define STRIGGER_CRYSTAL_EVENT_VALUE_WARP2_OBJECT_NUM_DEFAULT					3202700
#define STRIGGER_CRYSTAL_EVENT_VALUE_WARP2_OBJECT_NUM_CHANGE					93202700

#define STRIGGER_CRYSTAL_EVENT_VALUE_WARP3_OBJECT_IDX							401
#define STRIGGER_CRYSTAL_EVENT_VALUE_WARP3_OBJECT_NUM_DEFAULT					3202800
#define STRIGGER_CRYSTAL_EVENT_VALUE_WARP3_OBJECT_NUM_CHANGE					93202800

#define STRIGGER_CRYSTAL_EVENT_VALUE_KIT_SALES_VOLUME							100
#define STRIGGER_CRYSTAL_EVENT_VALUE_HYPER_CARD_SALES_VOLUME					5
#define STRIGGER_CRYSTAL_EVENT_VALUE_SEAL_SALES_VOLUME							1
#define STRIGGER_CRYSTAL_EVENT_VALUE_PREFIX_SUFFIX_VOLUME						3

#define STRIGGER_CRYSTAL_EVENT_VALUE_HOUR_EVENT_APPLY_TIME						60			// ���� : �� 
#define STRIGGER_CRYSTAL_EVENT_VALUE_HOUR_EVENT_ADD_EXP							1.0f		// ���� : 100.0 �ۼ�Ʈ
#define STRIGGER_CRYSTAL_EVENT_VALUE_HOUR_EVENT_ADD_SPI							1.0f		// ���� : 100.0 �ۼ�Ʈ
#define STRIGGER_CRYSTAL_EVENT_VALUE_HOUR_EVENT_ADD_DROP_ITEM					1.0f		// ���� : 100.0 �ۼ�Ʈ

#define STRIGGER_CRYSTAL_EVENT_2ND_VALUE_HOUR_EVENT_APPLY_TIME					60			// ���� : �� 
#define STRIGGER_CRYSTAL_EVENT_2ND_VALUE_HOUR_EVENT_ADD_EXP						1.5f		// ���� : 150.0 �ۼ�Ʈ
#define STRIGGER_CRYSTAL_EVENT_2ND_VALUE_HOUR_EVENT_ADD_SPI						1.5f		// ���� : 150.0 �ۼ�Ʈ
#define STRIGGER_CRYSTAL_EVENT_2ND_VALUE_HOUR_EVENT_ADD_DROP_ITEM				1.5f		// ���� : 150.0 �ۼ�Ʈ

#define STRIGGER_CRYSTAL_EVENT_VALUE_HELL_MAP_INDEX_1ST							4400		// ������ ù��°
#define STRIGGER_CRYSTAL_EVENT_VALUE_HELL_MAP_INDEX_2ND							4401		// ������ �ι�°

#define STRIGGER_CRYSTAL_EVENT_2ND_VALUE_HELL_MAP_INDEX_1ST						4402		// ������2 ù��°
#define STRIGGER_CRYSTAL_EVENT_2ND_VALUE_HELL_MAP_INDEX_2ND						4403		// ������2 �ι�°

// 2013-03-21 by bckim, ������ ��Ȱī�� ���� ���� ���� 
#define IS_CRYSTAL_EVENT_MAP( currentMapNum )	((currentMapNum == STRIGGER_CRYSTAL_EVENT_VALUE_HELL_MAP_INDEX_1ST) || \
												(currentMapNum == STRIGGER_CRYSTAL_EVENT_VALUE_HELL_MAP_INDEX_2ND) || \
												(currentMapNum == STRIGGER_CRYSTAL_EVENT_2ND_VALUE_HELL_MAP_INDEX_1ST) || \
												(currentMapNum == STRIGGER_CRYSTAL_EVENT_2ND_VALUE_HELL_MAP_INDEX_2ND))
// End. 2013-03-21 by bckim, ������ ��Ȱī�� ���� ���� ���� 

#define STRIGGER_CRYSTAL_EVENT_VALUE_HELL_MAP_1ST_SUMMON_MONSTER_UID_01			2110200 
#define STRIGGER_CRYSTAL_EVENT_VALUE_HELL_MAP_1ST_SUMMON_MONSTER_UID_02			2110300 
#define STRIGGER_CRYSTAL_EVENT_VALUE_HELL_MAP_1ST_SUMMON_MONSTER_UID_03			2110400 
#define STRIGGER_CRYSTAL_EVENT_VALUE_HELL_MAP_1ST_SUMMON_MONSTER_UID_04			2110500 

#define STRIGGER_CRYSTAL_EVENT_VALUE_HELL_MAP_1ST_SUMMON_MONSTER_COUNT			10

#define STRIGGER_CRYSTAL_EVENT_VALUE_HELL_MAP_1ST_SUMMON_MONSTER_UID_05			2109700  
#define STRIGGER_CRYSTAL_EVENT_VALUE_HELL_MAP_1ST_SUMMON_MONSTER_UID_06			2109800  
#define STRIGGER_CRYSTAL_EVENT_VALUE_HELL_MAP_1ST_SUMMON_MONSTER_UID_07			2109900  
#define STRIGGER_CRYSTAL_EVENT_VALUE_HELL_MAP_1ST_SUMMON_MONSTER_UID_08			2110000  
#define STRIGGER_CRYSTAL_EVENT_VALUE_HELL_MAP_1ST_SUMMON_MONSTER_UID_09			2110100  

#define STRIGGER_CRYSTAL_EVENT_VALUE_HELL_MAP_1ST_SUMMON_BOSS_MONSTER_COUNT		1

#define STRIGGER_CRYSTAL_EVENT_VALUE_HELL_MAP_2ND_SUMMON_MONSTER_UID_01			2111000 
#define STRIGGER_CRYSTAL_EVENT_VALUE_HELL_MAP_2ND_SUMMON_MONSTER_UID_02			2111100 
#define STRIGGER_CRYSTAL_EVENT_VALUE_HELL_MAP_2ND_SUMMON_MONSTER_UID_03			2111200 
#define STRIGGER_CRYSTAL_EVENT_VALUE_HELL_MAP_2ND_SUMMON_MONSTER_UID_04			2111300 
#define STRIGGER_CRYSTAL_EVENT_VALUE_HELL_MAP_2ND_SUMMON_MONSTER_UID_05			2111400 

#define STRIGGER_CRYSTAL_EVENT_VALUE_HELL_MAP_2ND_SUMMON_MONSTER_COUNT			10

#define STRIGGER_CRYSTAL_EVENT_VALUE_HELL_MAP_2ND_SUMMON_MONSTER_UID_06			2110600  
#define STRIGGER_CRYSTAL_EVENT_VALUE_HELL_MAP_2ND_SUMMON_MONSTER_UID_07			2110700  
#define STRIGGER_CRYSTAL_EVENT_VALUE_HELL_MAP_2ND_SUMMON_MONSTER_UID_08			2110800  
#define STRIGGER_CRYSTAL_EVENT_VALUE_HELL_MAP_2ND_SUMMON_MONSTER_UID_09			2110900  

#define STRIGGER_CRYSTAL_EVENT_VALUE_HELL_MAP_2ND_SUMMON_BOSS_MONSTER_COUNT		1

#define STRIGGER_CRYSTAL_EVENT_VALUE_HELL_MAP_SUMMON_MONSTER_RANDOM_POS			800

#define STRIGGER_CRYSTAL_EVENT_VALUE_HELL_MAP_1ST_REWARD_ITEM_UID				7033570

#define STRIGGER_CRYSTAL_EVENT_VALUE_HELL_MAP_2ND_ENTER_CONDITION_ITEM_UID_01	7033570
#define STRIGGER_CRYSTAL_EVENT_VALUE_HELL_MAP_2ND_ENTER_CONDITION_ITEM_UID_02	7033580

#define STRIGGER_CRYSTAL_EVENT_2ND_VALUE_WINNER_WAYPOINT						400

#define STRIGGER_CRYSTAL_EVENT_2ND_VALUE_WINNER_CAPSULE_ITEM_UID				7004540
#define STRIGGER_CRYSTAL_EVENT_2ND_VALUE_WINNER_CAPSULE_ITEM_COUNT				2

///////////////////////////////////////////////////////////////////////////////////////
// �̸�								���� ������Ʈ	��ü ������Ʈ	EventwParam1	EventType
///////////////////////////////////////////////////////////////////////////////////////
// �޾����� ���� 1					3202000			93202000		401				9			9372	������ �� ����(����/���� ����)
// �޾����� ���� 2					3202100			93202100		402				9			9373	������ �� ����(S�� ŰƮ)
// �޾����� ���� 3					3202200			93202200		403				9			9374	������ �� ����(������ ī��)
// �޾����� ���� 4					3207500			93207500		404				9			9375	������ �� ����(100���� �̻� ����)

// �޾����� ���� �浹������Ʈ #1	3207900			93207900		7142			8			<-- ��� ���� 7141 �̳� 7142 ��ü
// �޾����� ���� �浹������Ʈ #2	3208000			93208000		7141			1			<-- ��� ���� 7142 �̳� 7141 ��ü
// �޾����� ���� ������Ʈ			3202800			93202800		411				6
///////////////////////////////////////////////////////////////////////////////////////

#define STRIGGER_CRYSTAL_EVENT_2ND_VALUE_PREFIX_SUFFIX_SHOP_OBJECT_IDX			401
#define STRIGGER_CRYSTAL_EVENT_2ND_VALUE_PREFIX_SUFFIX_SHOP_OBJECT_NUM_DEFAULT	3202000
#define STRIGGER_CRYSTAL_EVENT_2ND_VALUE_PREFIX_SUFFIX_SHOP_OBJECT_NUM_CHANGE	93202000

#define STRIGGER_CRYSTAL_EVENT_2ND_VALUE_KIT_SHOP_OBJECT_IDX					402
#define STRIGGER_CRYSTAL_EVENT_2ND_VALUE_KIT_SHOP_OBJECT_NUM_DEFAULT			3202100
#define STRIGGER_CRYSTAL_EVENT_2ND_VALUE_KIT_SHOP_OBJECT_NUM_CHANGE				93202100

#define STRIGGER_CRYSTAL_EVENT_2ND_VALUE_HYPER_CARD_SHOP_OBJECT_IDX				403
#define STRIGGER_CRYSTAL_EVENT_2ND_VALUE_HYPER_CARD_SHOP_OBJECT_NUM_DEFAULT		3202200
#define STRIGGER_CRYSTAL_EVENT_2ND_VALUE_HYPER_CARD_SHOP_OBJECT_NUM_CHANGE		93202200

#define STRIGGER_CRYSTAL_EVENT_2ND_VALUE_WEAPON_SHOP_OBJECT_IDX					404
#define STRIGGER_CRYSTAL_EVENT_2ND_VALUE_WEAPON_SHOP_OBJECT_NUM_DEFAULT			3207500
#define STRIGGER_CRYSTAL_EVENT_2ND_VALUE_WEAPON_SHOP_OBJECT_NUM_CHANGE			93207500

#define STRIGGER_CRYSTAL_EVENT_2ND_VALUE_WARP_OBJECT_IDX						7142
#define STRIGGER_CRYSTAL_EVENT_2ND_VALUE_WARP_OBJECT_NUM_DEFAULT				3207900
#define STRIGGER_CRYSTAL_EVENT_2ND_VALUE_WARP_OBJECT_NUM_CHANGE					93207900

#define STRIGGER_CRYSTAL_EVENT_2ND_VALUE_WARP2_OBJECT_IDX						7141
#define STRIGGER_CRYSTAL_EVENT_2ND_VALUE_WARP2_OBJECT_NUM_DEFAULT				3208000
#define STRIGGER_CRYSTAL_EVENT_2ND_VALUE_WARP2_OBJECT_NUM_CHANGE				93208000

#define STRIGGER_CRYSTAL_EVENT_2ND_VALUE_WARP3_OBJECT_IDX						411
#define STRIGGER_CRYSTAL_EVENT_2ND_VALUE_WARP3_OBJECT_NUM_DEFAULT				3208100
#define STRIGGER_CRYSTAL_EVENT_2ND_VALUE_WARP3_OBJECT_NUM_CHANGE				93208100

// 2013-01-21 by jhseol, NGC �������� Ʈ���� �ý���
#define STRIGGER_CRYSTAL_EVENT_OUTPOST_1ST_VALUE_BOSS_PROTECTIVE_FILM_OBJECT_IDX			401
#define STRIGGER_CRYSTAL_EVENT_OUTPOST_1ST_VALUE_BOSS_PROTECTIVE_FILM_OBJECT_NUM_DEFAULT	3218000			// (���� ������Ʈ) ��ȣ�� ���� ��
#define STRIGGER_CRYSTAL_EVENT_OUTPOST_1ST_VALUE_BOSS_PROTECTIVE_FILM_OBJECT_NUM_CHANGE		93218000		// (�Ķ� ������Ʈ) ��ȣ�� �ִ� ��
// end 2013-01-21 by jhseol, NGC �������� Ʈ���� �ý���

// 2013-07-08 by jhseol, Ʈ���� �ý��� Ȯ��
#define STRIGGER_CRYSTAL_EVENT_TRIGGER_EX_1ST_VALUE_BOSS_PROTECTIVE_FILM_OBJECT_IDX			401
#define STRIGGER_CRYSTAL_EVENT_TRIGGER_EX_1ST_VALUE_BOSS_PROTECTIVE_FILM_OBJECT_NUM_DEFAULT	3225600			// (���� ������Ʈ) ��ȣ�� ���� ��
#define STRIGGER_CRYSTAL_EVENT_TRIGGER_EX_1ST_VALUE_BOSS_PROTECTIVE_FILM_OBJECT_NUM_CHANGE	93225600		// (�Ķ� ������Ʈ) ��ȣ�� �ִ� ��
// end 2013-07-08 by jhseol, Ʈ���� �ý��� Ȯ��

struct STRIGGER_MAP
{
	MapTriggerID_t	MapTriggerID;		// �� Ʈ���� ID
	MapIndex_t		MapIndex;			// ���� �� ��ȣ
	ChannelIndex_t	MapChannel;			// ���� �� ä��
	FunctionID_t	FunctionID;			// ���� ��� ����
};
typedef vector<STRIGGER_MAP>	vectorTriggerMap;

struct STRIGGER_FUNCTION_CRYSTAL
{
	FunctionID_t		FunctionID;
	CrystalGroupID_t	CrystalGroupID;
	INT					PeriodTime;				// ��
	BYTE				RandomSequence;			// 0 = ũ����Ż ���� ���ش�� , 1 = ũ����Ż ���� ����
};
typedef vector<STRIGGER_FUNCTION_CRYSTAL> vectorTriggerFunctionCrystal;

struct STRIGGER_CRYSTAL_GROUP
{
	CrystalGroupID_t	CrystalGroupID;
	DestroyGroupID_t	DestroyGroupID;
	EventID_t			EventID;
};
typedef vector<STRIGGER_CRYSTAL_GROUP> vectorTriggerCrystalGroup;

struct STRIGGER_CRYSTAL_DESTROY_GROUP
{
	DestroyGroupID_t	DestroyGroupID;
	SequenceNumber_t	SequenceNumber;
	MonIdx_t			TargetMonster;

	void operator= (const STRIGGER_CRYSTAL_DESTROY_GROUP &rCrystalDestoryGroup)
	{
		memcpy(this ,&rCrystalDestoryGroup , sizeof(STRIGGER_CRYSTAL_DESTROY_GROUP));
	}
};
typedef vector<STRIGGER_CRYSTAL_DESTROY_GROUP> vectorTriggerCrystalDestroyGroup;

struct STRIGGER_ATTACK_USER_DAMAGE
{
	MonIdx_t	MonsterIdx;
	UID32_t		CharacterUniqueNumber;
	UID32_t		GuildUniqueNumber;
	BYTE		InfluenceType;
	float		fDamage;
};

struct SSORT_TRIGGER_ATTACK_USER_DAMAGE_BY__DAMAGE : binary_function<STRIGGER_ATTACK_USER_DAMAGE, STRIGGER_ATTACK_USER_DAMAGE, bool>
{
	bool operator()(STRIGGER_ATTACK_USER_DAMAGE Param1, STRIGGER_ATTACK_USER_DAMAGE Param2)
	{
        return Param1.fDamage > Param2.fDamage;		// ���� ���� ����
    };
};

typedef	mt_vector<STRIGGER_ATTACK_USER_DAMAGE> mtvectTriggerAttackUserDamage;
typedef	vector<MonIdx_t> vectorDestroyedSequence;		// mtvectTriggerCrystalDamage ����Ͽ� ����ȭ

// ��� ���� ����� ������ ����
struct STRIGGER_ALL_MONSTER_DEAD_ITEM_PAY		
{
	BOOL		Enable;			// ��� ����
	TimeUnit_t	TimeLimit;		// ���� �ѵ� ���� �ð�
	ItemNum_t	ItemNum;		// ������ ����
};
// end 2011-10-28 by hskim, EP4 [Ʈ���� �ý���] - ũ����Ż �ý���

// start 2011-11-07 by hskim, EP4 [Ʈ���� �ý���] - NCG ������ �ý���
struct STRIGGER_FUNCTION_NGC_INFLWAR
{
	FunctionID_t		FunctionID;
	NGCInflWarGroupID_t	NGCInflWarGroupID;
	INT					PeriodTime;				// ��
	MonIdx_t			BossMonster;
	INT					WinInfluenceWP;
	INT					LossInfluenceWP;
	INT					FirstDamageGuildWP;
	INT					FixedTimeType;			// Ư�� �ð� ���̿� �����Ǵ� ��� Ÿ��
	INT					DestroyCrystalcount;	// 2013-07-08 by jhseol, Ʈ���� �ý��� Ȯ�� - �ı��ؾ��� ũ����Ż�� ��
};
typedef vector<STRIGGER_FUNCTION_NGC_INFLWAR> vectorTriggerFunctionNGCInflWar;

// 2013-01-21 by jhseol, NGC �������� Ʈ���� �ý���
struct STRIGGER_FUNCTION_NGC_OUTPOST
{
	FunctionID_t				FunctionID;					// Ʈ���� ID
	SummonMosterGroupID_t		SummonMonsterGroupID;		// ��ȯ ���� �׷� ID
	MapIndex_t					StandardOutPostMap;			// ������ �� �������� ��
	MonIdx_t					BossMonster;
	INT							WinInfluenceWP;
	INT							LossInfluenceWP;
	MapIndex_t					NextOutPostMap;				// ���� �������� ��
	INT							DestroyCrystalcount;		// �ı��ؾ��� ũ����Ż�� ��
};
typedef vector<STRIGGER_FUNCTION_NGC_OUTPOST> vectorTriggerFunctionNGCOutPost;

struct STRIGGER_TRIGGER_OUTPOST_BOSS_KILL_INFO
{
	MonIdx_t					BossMonster;
	MonIdx_t					CrystalNum;				// ũ����Ż ��ȣ
	INT							RegenMinTimeMinutes;	// ���� �ּ� �ð�(��)
	INT							RegenMaxTimeMinutes;	// ���� �ִ� �ð�(��)
	BOOL						IsDestroy;				// �ı�����
	ATUM_DATE_TIME				DestroyTime;			// �ı��ð�
};
typedef vector<STRIGGER_TRIGGER_OUTPOST_BOSS_KILL_INFO> vectorTriggerOutPostBossKillInfo;
typedef mt_vector<STRIGGER_TRIGGER_OUTPOST_BOSS_KILL_INFO> mtvectorTriggerOutPostMonsterKillInfo;

struct STRIGGER_CRYSTAL_BUFF
{
	FunctionID_t				FunctionID;				// Ʈ���� ID
	INT							SkillItemNum;			// ��ų ��ȣ
};
typedef vector<STRIGGER_CRYSTAL_BUFF> vectorTriggerCrystalBuff;
// end 2013-01-21 by jhseol, NGC �������� Ʈ���� �ý���

struct STRIGGER_NGC_INFLWAR_MONSTER_GROUP
{
	NGCInflWarGroupID_t	NGCInflWarGroupID;
	MonIdx_t			Monster;
	INT					SummonCount;
	INT					SummonRandomPos;
};
typedef vector<STRIGGER_NGC_INFLWAR_MONSTER_GROUP> vectorTriggerNGCInflWarMonsterGroup;

typedef enum
{
	MAP_ENTRANCE_CONDITION_OPTION_NONE				= 0,		// ����
	MAP_ENTRANCE_CONDITION_OPTION_DELETE			= 1,		// ����
} eMAP_ENTRANCE_CONDITION_OPTION;

struct SMAP_ENTRANCE_CONDITION
{
	ItemNum_t						ItemNum;			// ������ ��ȣ
	INT								RequireCount;		// �䱸 ����
	eMAP_ENTRANCE_CONDITION_OPTION	Option;				// ���� ����
};
typedef vector<SMAP_ENTRANCE_CONDITION> vectorMapEntranceCondition;
// end 2011-11-07 by hskim, EP4 [Ʈ���� �ý���] - NCG ������ �ý���

// start 2011-12-21 by hskim, EP4 [������ 1ȸ ���]
typedef enum
{
	SYSTEM_EVENT_OPENING_MOVIE		= 0

} eSYSTEM_EVENT;
// end 2011-12-21 by hskim, EP4 [������ 1ȸ ���]

// start 2012-03-13 by hskim, ����ȭ ���� DB ���� ����
struct SOVERLAP_ITEM
{
	ItemNum_t	ItemNum;
	INT			CashPrice;
	INT			Tab;
	INT			ItemAttribute;
};
typedef vector<SOVERLAP_ITEM> vectorOverlapItem;
// end 2012-03-13 by hskim, ����ȭ ���� DB ���� ����

// start 2012-03-05 by hskim, ��� ������ ���� �ð��� ����
struct SDELETE_DROP_ITEM
{
	UINT				ItemFieldIndex;
	D3DXVECTOR3			Position;
};
typedef vector<SDELETE_DROP_ITEM>	vectorDeleteDropItem;		
// end 2012-03-05 by hskim, ��� ������ ���� �ð��� ����

// 2012-06-08 by jhseol, �Ʒ��� �߰�����part2 - �ɸ��� : Ÿ�� ����
#define CHARACTER_B_ACC_NAME "MSAce_34122_B_Copy1"
#define CHARACTER_M_ACC_NAME "MSAce_34122_M_Copy1"
#define CHARACTER_I_ACC_NAME "MSAce_34122_I_Copy1"
#define CHARACTER_A_ACC_NAME "MSAce_34122_A_Copy1"

#define CHARACTER_TYPE_B_ATT "MSAce34122BAtt"
#define CHARACTER_TYPE_B_DEF "MSAce34122BDef"
#define CHARACTER_TYPE_B_DOD "MSAce34122BDod"

#define CHARACTER_TYPE_M_ATT "MSAce34122MAtt"
#define CHARACTER_TYPE_M_DEF "MSAce34122MDef"
#define CHARACTER_TYPE_M_DOD "MSAce34122MDod"

#define CHARACTER_TYPE_A_ATT "MSAce34122AAtt"
#define CHARACTER_TYPE_A_DEF "MSAce34122ADef"
#define CHARACTER_TYPE_A_DOD "MSAce34122ADod"

#define CHARACTER_TYPE_I_ATT "MSAce34122IAtt"
#define CHARACTER_TYPE_I_DEF "MSAce34122IDef"
#define CHARACTER_TYPE_I_DOD "MSAce34122IDod"
// end 2012-06-08 by jhseol, �Ʒ��� �߰�����part2 - �ɸ��� : Ÿ�� ����

// 2012-06-21 by jhseol, �Ʒ��� �߰�����part2 - �Ʒ��� ���� ������ ( 0 = ����, 1 = �Ʒ��� )
#define SLOT_PURPOSE_MAIN	0
#define SLOT_PURPOSE_ARENA	1
// end 2012-06-21 by jhseol, �Ʒ��� �߰�����part2 - �Ʒ��� ���� ������ ( 0 = ����, 1 = �Ʒ��� )

// 2012-10-08 by jhjang ���Ǿƿ� ����ġ ������
#define KILLCOUNT_MAX		300		
#define KILLCOUNT_ITEMNUM	7038810
// end 2012-10-08 by jhjang ���Ǿƿ� ����ġ ������

///////////////////////////////////////////////////////////////////////////////
// 2012-11-13 by jhseol, ���� �ý��� ������ - ������
#define RenewalStrategyPointWeekDay					7
#define RenewalStrategyPointSummonTimeTermMin		1800 // 30��*60��

struct SRENEWAL_STRATEGYPOINT_SUMMON_TIME
{//���Ϻ� �Ű��� ���� �ð� �� ���º� ��ȯ ���� ��
	SHORT			DayOfWeek;
	ATUM_DATE_TIME	StartTime;
	ATUM_DATE_TIME	EndTime;
	BYTE			CountBCU;
	BYTE			CountANI;
};
typedef vector<SRENEWAL_STRATEGYPOINT_SUMMON_TIME>	vectSRENEWAL_STRATEGYPOINT_SUMMON_TIME;

struct SSTRATEGYPOINT_MAP_INFLUENCESTRATEGYPOINT_INFO
{//���� �� �������� ����
	MapIndex_t		MapIndex;
	char			MapName[SIZE_MAX_MAP_NAME];
	int				Influence;
};
typedef vector<SSTRATEGYPOINT_MAP_INFLUENCESTRATEGYPOINT_INFO>	vectSSTRATEGYPOINT_MAP_INFLUENCESTRATEGYPOINT_INFO;
// end 2012-11-13 by jhseol, ���� �ý��� ������ - ������

// 2013-05-09 by hskim, ���� ����Ʈ ����
#define CONSECUTIVE_VICTORIES_BUFF_SKILL_2ND	7841051
#define CONSECUTIVE_VICTORIES_BUFF_SKILL_3RD	7841061
#define CONSECUTIVE_VICTORIES_BUFF_SKILL_4TH	7841071
#define CONSECUTIVE_VICTORIES_BUFF_SKILL_5TH	7841081
#define CONSECUTIVE_VICTORIES_BUFF_SKILL_6TH	7841091
#define CONSECUTIVE_VICTORIES_BUFF_SKILL_7TH	7841101
#define CONSECUTIVE_VICTORIES_BUFF_SKILL_8TH	7841111

#define TURN_AROUND_BUFF_SKILL_1ST				7841121		
#define TURN_AROUND_BUFF_SKILL_2ND				7841122
#define TURN_AROUND_BUFF_SKILL_3RD				7841141


#define TURN_AROUND_BUFF_SKILL_1ST_THRESHOLD	7000
#define TURN_AROUND_BUFF_SKILL_2ND_THRESHOLD	8000
// 2013-08-14 by jhseol, ������ ������ - ��������Ʈ ���� ����
#ifdef SC_STRATEGYPOINTWAR_RENEWAL_JHSEOL_SSJUNG
#define TURN_AROUND_BUFF_SKILL_NEW_THRESHOLD	3000
#else
#define TURN_AROUND_BUFF_SKILL_NEW_THRESHOLD	4000		// 2013-08-01 by jhseol, ������ ���� ������ - ������ �ο��ϴ� ��������Ʈ ����
#endif
// end 2013-08-14 by jhseol, ������ ������ - ��������Ʈ ���� ����
// 2013-12-16 by jhseol, ������ ��ȸ ���� ������ - ������ ����
#ifdef S_UPGRADE_INFLUENCE_POINT_RENEWAL_JHSEOL		// - ������ ����
#define TURN_AROUND_BUFF_SKILL_MAXIMUM_POINT_GAP	5000	// ���� ���� �ִ� ��������Ʈ�� 2����, ���� ������ ȯ���ϸ� [0.006*5000 = 30%]
#else
#define TURN_AROUND_BUFF_SKILL_MAXIMUM_POINT_GAP	20000	// 2013-08-01 by jhseol, ������ ���� ������ - ���� ���� �ִ� ��������Ʈ�� 2����, ���� ������ ȯ���ϸ� [0.75 *(20000/100) = 150%]
#endif
// end 2013-12-16 by jhseol, ������ ��ȸ ���� ������ - ������ ����
#define TURN_AROUND_BUFF_SKILL_100P_VALUE			0.006f	// 2013-10-31 by jhseol, ������ ���� ����	// 2013-08-01 by jhseol, ������ ���� ������ - ��������Ʈ 1����Ʈ�� ���� ���� ��
// end 2013-05-09 by hskim, ���� ����Ʈ ����

// 2013-05-20 by hskim, [���� �ý���] ���������� ������� ������ �߰� ����
#define TEMPORARY_SYSTEM_INFOMATION_INDEX_ITEMSECURITY	2
// end 2013-05-20 by hskim, [���� �ý���] ���������� ������� ������ �߰� ����


// 2013-05-31 by jhseol,bckim �Ƹ� �÷��� - ����ä ����
struct COLLECTION_INFO
{
	INT				CollectionType;		// �÷��� Ÿ�� (1 : �Ƹ�)
	UID32_t			AccountUID;			// ���� UID
	UID32_t			CharacterUID;		// ĳ���� UID
	ItemNum_t		ShapeNum;			// ������ ������ ������ ��ȣ
	ItemNum_t		ShapeItemNum;		// �ܺ�Ŷ ������ ��ȣ
	BYTE			EnchantLevel;		// ��ȭ �ܰ�
	UINT			RemainSeconds;		// ���� �ð�(��) : �ִ� 136��
	ATUM_DATE_TIME	EndTime;			// ���� �ð����� ���� �ð��� ���Ͽ� ����� ������ ����ð�
	INT				ActivedCount;		// ������ ����� �������� �� (0:����� �ƸӰ� ����=������� �ƴ�, 1�̻� �����)
	ItemNum_t		nOptionItemNum;		// 2013-09-06 by jhseol, �̴��� �Ƹ� �̺�Ʈ ���� �Ⱓ ���� - �̴��� �Ƹ� �ɼ� ������ ��ȣ
	ATUM_DATE_TIME	DurationTime;		// 2013-09-06 by jhseol, �̴��� �Ƹ� �̺�Ʈ ���� �Ⱓ ���� - �̴��� �Ƹ� �ɼ� ����ð�

	COLLECTION_INFO()
	{
		MEMSET_ZERO(this, sizeof(COLLECTION_INFO));
	}
};
typedef vector<COLLECTION_INFO>	COLLECTION_LIST;

struct COLLECTION_SHAPE_CHANGE
{
	INT				CollectionType;		// �÷��� Ÿ�� (1 : �Ƹ�)
	ItemUID_t		TargetItemUID;		// ���������� ������� ������UID
	ItemNum_t		ShapeNum;			// ���� ��ȣ(�ҽ��ε���)

	COLLECTION_SHAPE_CHANGE()
	{
		MEMSET_ZERO(this, sizeof(COLLECTION_SHAPE_CHANGE));
	}
};
// end 2013-05-31 by jhseol,bckim �Ƹ� �÷��� - ����ä ����

// 2013-08-14 by jhseol, ������ ������ - [ti_MonsterGrade] ���̺� ����ü ����
#define MONSTER_GRADE_TYPE_STRATEGYPOINT		1
#define WARINFO_DISPLAY_TYPE_MSWAR				0	// �������� ���Ÿ�� (0:��)
#define WARINFO_DISPLAY_TYPE_SPWAR				1	// �������� ���Ÿ�� (1:�Ϲ� ����)
#define WARINFO_DISPLAY_TYPE_NGCSPWAR			2	// �������� ���Ÿ�� (2:NGC ����)
#define FIEXD_MSWAR_SPLEVEL						6	// ���� �� ��ȯ�Ǵ� ���� lv
#define SPLEVEL_INIT							5	// ������ �ʱ�ȭ ����
#define SPLEVEL_MIN								1	// ������ �ּ� ����
// 2014-03-25 by jekim, �¸��� ȯȣ
#ifdef S_ACCLAIM_OF_VICTORY_JEKIM
#define SPLEVEL_MAX								20	// ������ �ִ� ����
#else
	#ifdef SC_UNBALANCED_FORCES_ADJUST_SPLEVEL_MAX		// 2014-07-10 by bckim, ���� �ұ���(�¸���ȯȣ���Ž� �������� MAX ����
		#define SPLEVEL_MAX								20	// ������ �ִ� ����
	#else 
        #define SPLEVEL_MAX								10	// ������ �ִ� ����
	#endif
#endif
// end 2014-03-25 by jekim, �¸��� ȯȣ
#define TRIGGER_FIXEDTIMETYPR_NOMAL				0	// Ʈ���� �ð� (�Ϲ�)
#define TRIGGER_FIXEDTIMETYPR_FIXED				1	// Ʈ���� �ð� (�ð��� ���� ����6~12��)
#define TRIGGER_FIXEDTIMETYPR_SPTIME			2	// Ʈ���� �ð� (������ ��ȯ�ð�)
struct MONSTER_GRADE_INFO
{
	BYTE MonsterGeadeType;	// Ÿ�� (1. ��������)
	BYTE InflType;			// ����
	BYTE Level;				// ���� 
	INT MonsterNum;			// �ش� ������ ���ͳѹ�
	INT BeforeMonsterNum;	// ���� ������ ���ͳѹ�
	INT AfterMonsterNum;	// ���� ������ ���ͳѹ�
	MONSTER_GRADE_INFO()
	{
		MEMSET_ZERO(this, sizeof(MONSTER_GRADE_INFO));
	}
};
typedef vector<MONSTER_GRADE_INFO>	MONSTER_GRADE_LIST;
// end 2013-08-14 by jhseol, ������ ������ - [ti_MonsterGrade] ���̺� ����ü ����


// 2013-11-25 by jhseol&bckim, �ŷ��� - �ش� �߰�
#define MARKET_VECTOR_SIZE								400000	// ������ ����ĳ���� 4��(Ȯ���� ������), �������� ���� 5��(�ΰ����� ���), ���� 1000�� ���� �Ϸ翡 20�Ծ� �ø��� �ִ� �� 4*5*1000*20=40��
#define MARKET_VIEW_LIST_COUNT							8		// ���������� �����ִ� ����Ʈ
#define MARKET_SELL_ITEM_COUNT							10		// ��ϰ����� �������� ��
#define MARKET_MONEY_TYPE_SPI							0		// SPI �Ǹ�
#define MARKET_MONEY_TYPE_WP							1		// WP �Ǹ�
#define MARKET_ITEM_FULL_NAME							140		// ����, ���� ���Ե� ������ �̸�
#define MARKET_PACKET_RECV_TICK_BUY_PAGE				1000	// �ŷ��� ���� ���� ��Ŷ ���� �� - ����������
#define MARKET_PACKET_RECV_TICK_SELL_PAGE				1000	// �ŷ��� ���� ���� ��Ŷ ���� �� - ���������
#define MARKET_PACKET_RECV_TICK_MY_LIST_PAGE			1000	// �ŷ��� ���� ���� ��Ŷ ���� �� - ��Ȳ������
#define MARKET_PACKET_RECV_TICK_GET_REQUEST				1000	// �ŷ��� ���� ���� ��Ŷ ���� �� - ȸ����û
#define MARKET_PACKET_RECV_TICK							1000	// �ŷ��� ���� ���� ��Ŷ ���� ��

#if defined(TEST140) || defined(_DEBUG)
#define MARKET_SELLING_MINUTES							(30)	// �׽�Ʈ 30�� 
#else
#define MARKET_SELLING_MINUTES							(10080)	// �ŷ��� �Ǹ� �����ð� �Ⱓ 7�� 60��*24�ð�*7�� = 10080
#endif

#define MARKET_SELL_CHARGE_SPI							0.005f	// �ŷ��� �Ǹ� SPI ������ 0.5%
#define MARKET_SELL_CHARGE_WP							0.005f	// �ŷ��� �Ǹ� WP ������ 0.5%

inline INT GetMarketSellChargeSPI(INT i_nPrice)	{return max(1, i_nPrice*MARKET_SELL_CHARGE_SPI);}	// SPI �����Ḧ ����ϴ� �Լ�
inline INT GetMarketSellChargeWP(INT i_nPrice)	{return max(1, i_nPrice*MARKET_SELL_CHARGE_WP);}	// WP �����Ḧ ����ϴ� �Լ�
// MARKET_STATE_TYPE									// ���� Ÿ��
#define MARKET_STATE_SELL					1			// �Ǹ���
#define MARKET_STATE_SELL_DONE				2			// �ǸſϷ�
#define MARKET_STATE_TIME_OUT				3			// �Ⱓ����
#define MARKET_STATE_DELETE					4			// �ŷ��Ϸ�(�������)
#define MARKET_GET_SELLING					5			// �ŷ�ȸ�� (�Ǹ���)	// Ŭ���̾�Ʈ ����� 
#define MARKET_GET_EXPIRATION				6			// �ŷ�ȸ�� (�Ⱓ����)	// Ŭ���̾�Ʈ ����� 
#define MARKET_GET_SOLD						7			// �ŷ�ȸ�� (�ǸſϷ�)	// Ŭ���̾�Ʈ ����� 

// MARKET_SORT_TYPE										// ���� Ÿ��
#define MARKET_SORT_PRICE_UP				1			// ���� ��������
#define MARKET_SORT_PRICE_DOWN				2			// ���� ��������
#define MARKET_SORT_LEVEL_UP				3			// ���� ��������
#define MARKET_SORT_LEVEL_DOWN				4			// ���� ��������
#define MARKET_SORT_ENCHANT_UP				5			// ��þƮ ��������
#define MARKET_SORT_ENCHANT_DOWN			6			// ��þƮ ��������
#define MARKET_SORT_NAME_UP					7			// �̸� ��������
#define MARKET_SORT_NAME_DOWN				8			// �̸� ��������
#define MARKET_SORT_TIME_UP					9			// �ð� ��������
#define MARKET_SORT_TIME_DOWN				10			// �ð� ��������

// MARKET_ITEM_KIND
#define MARKET_ITEM_KIND_ALL							0	//	��ü
#define		MARKET_ITEM_KIND_WEAPON						1	//	����
#define			MARKET_ITEM_KIND_PRIMARY_WEAPON			2	//		�⺻����
#define				MARKET_ITEM_KIND_VULCAN				3	//			��ĭ
#define				MARKET_ITEM_KIND_CANNON				4	//			ĳ��
#define				MARKET_ITEM_KIND_GATLING			5	//			��Ʋ��
#define				MARKET_ITEM_KIND_RIFLE				6	//			������
#define				MARKET_ITEM_KIND_AUTOMATIC			7	//			�����ƽ
#define				MARKET_ITEM_KIND_DUALIST			8	//			��󸮽�Ʈ
#define				MARKET_ITEM_KIND_MASSDRIVE			9	//			�޽�����̺�
#define			MARKET_ITEM_KIND_SECONDARY_WEAPON		10	//		���޹���
#define				MARKET_ITEM_KIND_MISSILE			11	//			�̻���
#define				MARKET_ITEM_KIND_BUNDLE				12	//			����
#define		MARKET_ITEM_KIND_ARMOR						13	//	�Ƹ�
#define			MARKET_ITEM_KIND_VEIL					14	//		����
#define			MARKET_ITEM_KIND_DEFENDER				15	//		�����
#define			MARKET_ITEM_KIND_GUARDER				16	//		����
#define			MARKET_ITEM_KIND_BINDER					17	//		���δ�
#define		MARKET_ITEM_KIND_RADAR						18	//	���̴�
#define			MARKET_ITEM_KIND_RADAR_B				19	//		���̴� B-Gear
#define			MARKET_ITEM_KIND_RADAR_M				20	//		���̴� M-Gear
#define			MARKET_ITEM_KIND_RADAR_A				21	//		���̴� A-Gear
#define			MARKET_ITEM_KIND_RADAR_I				22	//		���̴� I-Gear
#define		MARKET_ITEM_KIND_SUPPORT					23	//	�������
#define			MARKET_ITEM_KIND_UNLIMITED_ACCESSORY	24	//		������ �Ǽ��縮
#define			MARKET_ITEM_KIND_TIMELIMIT_ACCESSORY	25	//		�ð��� �Ǽ��縮
#define			MARKET_ITEM_KIND_COMPUTER				26	//		��ǻ��(CPU)
#define			MARKET_ITEM_KIND_MARK					27	//		��ũ
#define		MARKET_ITEM_KIND_ENGIN						28	//	����
#define			MARKET_ITEM_KIND_ENGIN_B				29	//		���� B-Gear
#define			MARKET_ITEM_KIND_ENGIN_M				30	//		���� M-Gear
#define			MARKET_ITEM_KIND_ENGIN_A				31	//		���� A-Gear
#define			MARKET_ITEM_KIND_ENGIN_I				32	//		���� I-Gear
#define		MARKET_ITEM_KIND_CONSUMABLE					33	//	�Ҹ�ǰ
#define			MARKET_ITEM_KIND_ENERGY					34	//		ȸ��ŰƮ
#define			MARKET_ITEM_KIND_GAMBLE					35	//		����ī��
#define			MARKET_ITEM_KIND_ENCHANT				36	//		��þī��
#define			MARKET_ITEM_KIND_CARD					37	//		�Ҹ�ǰī��
#define			MARKET_ITEM_KIND_RANDOMBOX				38	//		����ǻ���
#define		MARKET_ITEM_KIND_ETC						39	//	��Ÿ
#define			MARKET_ITEM_KIND_MATERIAL				40	//		�������

inline BYTE GetMarketItemKindByOriginItemKind(ITEM i_itemInfo)
{
	switch(i_itemInfo.Kind)
	{
	case ITEMKIND_VULCAN:							return MARKET_ITEM_KIND_VULCAN;
	case ITEMKIND_CANNON:							return MARKET_ITEM_KIND_CANNON;
	case ITEMKIND_GATLING:							return MARKET_ITEM_KIND_GATLING;
	case ITEMKIND_RIFLE:							return MARKET_ITEM_KIND_RIFLE;
	case ITEMKIND_AUTOMATIC:						return MARKET_ITEM_KIND_AUTOMATIC;
	case ITEMKIND_DUALIST:							return MARKET_ITEM_KIND_DUALIST;
	case ITEMKIND_MASSDRIVE:						return MARKET_ITEM_KIND_MASSDRIVE;
	case ITEMKIND_MISSILE:							return MARKET_ITEM_KIND_MISSILE;
	case ITEMKIND_BUNDLE:							return MARKET_ITEM_KIND_BUNDLE;
	case ITEMKIND_DEFENSE:
		{
			if ( IS_BGEAR(i_itemInfo.ReqUnitKind) )	return MARKET_ITEM_KIND_VEIL;
			if ( IS_MGEAR(i_itemInfo.ReqUnitKind) )	return MARKET_ITEM_KIND_DEFENDER;
			if ( IS_AGEAR(i_itemInfo.ReqUnitKind) )	return MARKET_ITEM_KIND_GUARDER;
			if ( IS_IGEAR(i_itemInfo.ReqUnitKind) )	return MARKET_ITEM_KIND_BINDER;
		};
	case ITEMKIND_RADAR:
		{
			if ( IS_BGEAR(i_itemInfo.ReqUnitKind) )	return MARKET_ITEM_KIND_RADAR_B;
			if ( IS_MGEAR(i_itemInfo.ReqUnitKind) )	return MARKET_ITEM_KIND_RADAR_M;
			if ( IS_AGEAR(i_itemInfo.ReqUnitKind) )	return MARKET_ITEM_KIND_RADAR_A;
			if ( IS_IGEAR(i_itemInfo.ReqUnitKind) )	return MARKET_ITEM_KIND_RADAR_I;
		};
	case ITEMKIND_ACCESSORY_UNLIMITED:				return MARKET_ITEM_KIND_UNLIMITED_ACCESSORY;
	case ITEMKIND_ACCESSORY_TIMELIMIT:				return MARKET_ITEM_KIND_TIMELIMIT_ACCESSORY;
	case ITEMKIND_COMPUTER:							return MARKET_ITEM_KIND_COMPUTER;
	case ITEMKIND_MARK:								return MARKET_ITEM_KIND_MARK;
	case ITEMKIND_SUPPORT:
		{
			if ( IS_BGEAR(i_itemInfo.ReqUnitKind) )	return MARKET_ITEM_KIND_ENGIN_B;
			if ( IS_MGEAR(i_itemInfo.ReqUnitKind) )	return MARKET_ITEM_KIND_ENGIN_M;
			if ( IS_AGEAR(i_itemInfo.ReqUnitKind) )	return MARKET_ITEM_KIND_ENGIN_A;
			if ( IS_IGEAR(i_itemInfo.ReqUnitKind) )	return MARKET_ITEM_KIND_ENGIN_I;
		};
	case ITEMKIND_ENERGY:							return MARKET_ITEM_KIND_ENERGY;
	case ITEMKIND_GAMBLE:							return MARKET_ITEM_KIND_GAMBLE;
	case ITEMKIND_PREVENTION_DELETE_ITEM:			return MARKET_ITEM_KIND_ENCHANT;	// ��þ �Ĺ�, Ȯ�� ī��
	case ITEMKIND_ENCHANT:							return MARKET_ITEM_KIND_ENCHANT;	// ��þ ī��
	case ITEMKIND_CARD:								return MARKET_ITEM_KIND_CARD;
	case ITEMKIND_RANDOMBOX:						return MARKET_ITEM_KIND_RANDOMBOX;
	case ITEMKIND_INGOT:							return MARKET_ITEM_KIND_MATERIAL;
	default : return ITEMKIND_UNKNOWN;
	};
}

inline BOOL IsMarketItemKindSame(BYTE i_nSource, BYTE i_nDestination)
{
	switch(i_nSource)
	{
	case MARKET_ITEM_KIND_ALL:						return	TRUE;
	case MARKET_ITEM_KIND_WEAPON:					return	IS_IN_RANGE(MARKET_ITEM_KIND_VULCAN,i_nDestination,MARKET_ITEM_KIND_MASSDRIVE) || IS_IN_RANGE(MARKET_ITEM_KIND_MISSILE,i_nDestination,MARKET_ITEM_KIND_BUNDLE);
	case	MARKET_ITEM_KIND_PRIMARY_WEAPON:		return		 IS_IN_RANGE(MARKET_ITEM_KIND_VULCAN,i_nDestination,MARKET_ITEM_KIND_MASSDRIVE);
	case		MARKET_ITEM_KIND_VULCAN:			return			MARKET_ITEM_KIND_VULCAN == i_nDestination;
	case		MARKET_ITEM_KIND_CANNON:			return			MARKET_ITEM_KIND_CANNON == i_nDestination;
	case		MARKET_ITEM_KIND_GATLING:			return			MARKET_ITEM_KIND_GATLING == i_nDestination;
	case		MARKET_ITEM_KIND_RIFLE:				return			MARKET_ITEM_KIND_RIFLE == i_nDestination;
	case		MARKET_ITEM_KIND_AUTOMATIC:			return			MARKET_ITEM_KIND_AUTOMATIC == i_nDestination;
	case		MARKET_ITEM_KIND_DUALIST:			return			MARKET_ITEM_KIND_DUALIST == i_nDestination;
	case		MARKET_ITEM_KIND_MASSDRIVE:			return			MARKET_ITEM_KIND_MASSDRIVE == i_nDestination;
	case	MARKET_ITEM_KIND_SECONDARY_WEAPON:		return		IS_IN_RANGE(MARKET_ITEM_KIND_MISSILE,i_nDestination,MARKET_ITEM_KIND_BUNDLE);
	case		MARKET_ITEM_KIND_MISSILE:			return			MARKET_ITEM_KIND_MISSILE == i_nDestination;
	case		MARKET_ITEM_KIND_BUNDLE:			return			MARKET_ITEM_KIND_BUNDLE == i_nDestination;
	case MARKET_ITEM_KIND_ARMOR:					return	IS_IN_RANGE(MARKET_ITEM_KIND_VEIL,i_nDestination,MARKET_ITEM_KIND_BINDER);
	case	MARKET_ITEM_KIND_VEIL:					return		MARKET_ITEM_KIND_VEIL == i_nDestination;
	case	MARKET_ITEM_KIND_DEFENDER:				return		MARKET_ITEM_KIND_DEFENDER == i_nDestination;
	case	MARKET_ITEM_KIND_GUARDER:				return		MARKET_ITEM_KIND_GUARDER == i_nDestination;
	case	MARKET_ITEM_KIND_BINDER:				return		MARKET_ITEM_KIND_BINDER == i_nDestination;
	case MARKET_ITEM_KIND_RADAR:					return	IS_IN_RANGE(MARKET_ITEM_KIND_RADAR_B,i_nDestination,MARKET_ITEM_KIND_RADAR_I);
	case	MARKET_ITEM_KIND_RADAR_B:				return		MARKET_ITEM_KIND_RADAR_B == i_nDestination;
	case	MARKET_ITEM_KIND_RADAR_M:				return		MARKET_ITEM_KIND_RADAR_M == i_nDestination;
	case	MARKET_ITEM_KIND_RADAR_A:				return		MARKET_ITEM_KIND_RADAR_A == i_nDestination;
	case	MARKET_ITEM_KIND_RADAR_I:				return		MARKET_ITEM_KIND_RADAR_I == i_nDestination;
	case MARKET_ITEM_KIND_SUPPORT:					return	IS_IN_RANGE(MARKET_ITEM_KIND_UNLIMITED_ACCESSORY,i_nDestination,MARKET_ITEM_KIND_MARK);
	case	MARKET_ITEM_KIND_UNLIMITED_ACCESSORY:	return		MARKET_ITEM_KIND_UNLIMITED_ACCESSORY == i_nDestination;
	case	MARKET_ITEM_KIND_TIMELIMIT_ACCESSORY:	return		MARKET_ITEM_KIND_TIMELIMIT_ACCESSORY == i_nDestination;
	case	MARKET_ITEM_KIND_COMPUTER:				return		MARKET_ITEM_KIND_COMPUTER == i_nDestination;
	case	MARKET_ITEM_KIND_MARK:					return		MARKET_ITEM_KIND_MARK == i_nDestination;
	case MARKET_ITEM_KIND_ENGIN:					return	IS_IN_RANGE(MARKET_ITEM_KIND_ENGIN_B,i_nDestination,MARKET_ITEM_KIND_ENGIN_I);
	case	MARKET_ITEM_KIND_ENGIN_B:				return		MARKET_ITEM_KIND_ENGIN_B == i_nDestination;
	case	MARKET_ITEM_KIND_ENGIN_M:				return		MARKET_ITEM_KIND_ENGIN_M == i_nDestination;
	case	MARKET_ITEM_KIND_ENGIN_A:				return		MARKET_ITEM_KIND_ENGIN_A == i_nDestination;
	case	MARKET_ITEM_KIND_ENGIN_I:				return		MARKET_ITEM_KIND_ENGIN_I == i_nDestination;
	case MARKET_ITEM_KIND_CONSUMABLE:				return	IS_IN_RANGE(MARKET_ITEM_KIND_ENERGY,i_nDestination,MARKET_ITEM_KIND_RANDOMBOX);
	case	MARKET_ITEM_KIND_ENERGY:				return		MARKET_ITEM_KIND_ENERGY == i_nDestination;
	case	MARKET_ITEM_KIND_GAMBLE:				return		MARKET_ITEM_KIND_GAMBLE == i_nDestination;
	case	MARKET_ITEM_KIND_ENCHANT:				return		MARKET_ITEM_KIND_ENCHANT == i_nDestination;
	case	MARKET_ITEM_KIND_CARD:					return		MARKET_ITEM_KIND_CARD == i_nDestination;
	case	MARKET_ITEM_KIND_RANDOMBOX:				return		MARKET_ITEM_KIND_RANDOMBOX == i_nDestination;
	case MARKET_ITEM_KIND_ETC:						return	IS_IN_RANGE(MARKET_ITEM_KIND_MATERIAL,i_nDestination,MARKET_ITEM_KIND_MATERIAL);
	case	MARKET_ITEM_KIND_MATERIAL:				return		MARKET_ITEM_KIND_MATERIAL == i_nDestination;
	default : return FALSE;
	};
}

struct MARKET_ENCHANT_INFO // ��þƮ ���� ����
{
	ItemNum_t		ItemNum;			// ��þī�� �����۳ѹ�
	BYTE			Count;				// ��þ Ƚ��
};
struct MARKET_INFO // �ŷ��� ��� ������ ����
{
	UID64_t			MarketUID;			// �ŷ��� ������ȣ
	UID64_t			ItemUID;			// ������ ������ȣ
	UID32_t			AccountUID;			// ������ ���� UID
	UID32_t			CharacterUID;		// ������ ĳ���� UID
	BYTE			ItemKind;			// ������ ����
	char			ItemName[MARKET_ITEM_FULL_NAME];	// ������ �̸�(����, ���� ����)
	ItemNum_t		ItemNum;			// ������ ��ȣ
	ItemNum_t		ItemCount;			// �Ǹ� ����(������ ��� �Ѿ� ����)
	ItemNum_t		PrefixCodeNum;		// ���� �ɼ�(������ 0)
	ItemNum_t		SuffixCodeNum;		// ���� �ɼ�(������ 0)
	BYTE			EnchantCount;		// ��þƮ ��(������ 0)
	MARKET_ENCHANT_INFO	Enchant[8];		// ��þƮ ���� ����
	ItemNum_t		ShapeItemNum;		// �ƸӴ� ���� ����, ���޹���� ����Ʈ ����
	INT				ColorCode;			// ���� ����Ʈ ����
	BYTE			ItemLevel;			// ��밡�� ����
	USHORT			ItemGear;			// ��밡�� ���
	ATUM_DATE_TIME	RegistTime;			// �ŷ��� ��Ͻð�
	BYTE			MoneyType;			// ȭ�� Ÿ��(0=SPI, 1=WP)
	INT				Price;				// �Ǹűݾ�
	BYTE			MarketState;		// �����ۿ� ���� �ŷ��� ����(�Ǹ���, �ǸſϷ�, �Ⱓ���� ���)
	BYTE			FindNameIndex;		// �̸��˻��� �ֱ� �˻��� �̸��� �ε��� ��ġ(���������� �˻��Ҷ� ���)
	
	BYTE			MarketItemInfl;		// 2014-06-17 by bckim, ���� �ұ��� ( �ŷ��� ���ϼ��°����� �ŷ��� �̷������ ���� )			

	MARKET_INFO()
	{
		MEMSET_ZERO(this, sizeof(MARKET_INFO));
	}
	MARKET_INFO(MARKET_INFO *i_pMarket)
	{
		MEMSET_ZERO(this, sizeof(MARKET_INFO));
		memcpy(this, i_pMarket, sizeof(MARKET_INFO));
	}
};
typedef mt_vector<MARKET_INFO*>				MARKET_LIST;
typedef mt_vector<MARKET_INFO*>::iterator	MARKET_ITR;

//////////////////////////////////
// �ŷ��� ��ȣ�� ��� ã��
struct MARKET_LIST_MarketUID_Find_Object
{
	MARKET_LIST_MarketUID_Find_Object(UID64_t index): m_nFindIndex(index){};
	bool operator()(const MARKET_INFO *pMarKet)
	{
		return pMarKet->MarketUID == m_nFindIndex;
	}
	UID64_t m_nFindIndex;
};
//////////////////////////////////
// ���ݺ� ����
struct MARKET_LIST_SORT_PRICE_UP
{
	bool operator()(MARKET_INFO op1, MARKET_INFO op2)
	{
		return op1.Price < op2.Price;		// �������� ����
	}
};
struct MARKET_LIST_SORT_PRICE_DOWN
{
	bool operator()(MARKET_INFO op1, MARKET_INFO op2)
	{
		return op1.Price > op2.Price;		// �������� ����
	}
};
//////////////////////////////////
// ������ ����
struct MARKET_LIST_SORT_LEVEL_UP
{
	bool operator()(MARKET_INFO op1, MARKET_INFO op2)
	{
		return op1.ItemLevel < op2.ItemLevel;		// �������� ����
	}
};
struct MARKET_LIST_SORT_LEVEL_DOWN
{
	bool operator()(MARKET_INFO op1, MARKET_INFO op2)
	{
		return op1.ItemLevel > op2.ItemLevel;		// �������� ����
	}
};
//////////////////////////////////
// ��þƮ�� ����
struct MARKET_LIST_SORT_ENCHANT_UP
{
	bool operator()(MARKET_INFO op1, MARKET_INFO op2)
	{
		return op1.EnchantCount < op2.EnchantCount;		// �������� ����
	}
};
struct MARKET_LIST_SORT_ENCHANT_DOWN
{
	bool operator()(MARKET_INFO op1, MARKET_INFO op2)
	{
		return op1.EnchantCount > op2.EnchantCount;		// �������� ����
	}
};
//////////////////////////////////
// �ð��� ����
struct MARKET_LIST_SORT_TIME_UP
{
	bool operator()(MARKET_INFO op1, MARKET_INFO op2)
	{
		return op1.MarketUID < op2.MarketUID;		// �������� ����
	}
};
struct MARKET_LIST_SORT_TIME_DOWN
{
	bool operator()(MARKET_INFO op1, MARKET_INFO op2)
	{
		return op1.MarketUID > op2.MarketUID;		// �������� ����
	}
};
//////////////////////////////////
// �̸��� ����		strcmp ���� ��� : [ 0 : s1 = s2 ] , [ -1 : s1 < s2 ] , [ 1 : s1 > s2 ]
struct MARKET_LIST_SORT_NAME_UP
{
	bool operator()(MARKET_INFO op1, MARKET_INFO op2)
	{
		return 0 > strcmp(op1.ItemName, op2.ItemName);	// �������� ����
	}
};
struct MARKET_LIST_SORT_NAME_DOWN
{
	bool operator()(MARKET_INFO op1, MARKET_INFO op2)
	{
		return 0 < strcmp(op1.ItemName, op2.ItemName);	// �������� ����
	}
};
//////////////////////////////////
// ���ڿ����� �ܾ� �˻�
inline int SearchWord(char* string, char* word, int index)
{
	int i, j, Ls= strlen(string), Lw = strlen(word);
	for (i=index; i<Ls; i++ )
	{
		if (string[i] == word[0])
		{
			if ( 1 < Lw )
			{
				for(j=1; j<Lw; j++)
				{
					if(string[i+j] != word[j])	{ break;		}
					if(j == Lw-1)				{ return i+j+1;	}    //������������ �ε��� ���� 
				} 
			}
			else	{ return i+1; }
		}
	}
	return 0;
}
// end 2013-11-25 by jhseol&bckim, �ŷ��� - �ش� �߰�

// 2014-01-03 by jhseol&bckim, �ı������ - �ش� �߰�

// DESROY_AUCTION_ITEM_STATE							// ���� Ÿ��
#define AUCTION_ITEM_STATE_INIT				1			// ���� �ʱ� �ܰ� 
#define AUCTION_ITEM_STATE_START			2			// ��� ���۵Ǹ� ���� >> 2
#define AUCTION_ITEM_STATE_3				3			// �ѹ��̶� ������ ����Ǿ��ٴ� ? ( DB������ ���� )
#define AUCTION_ITEM_STATE_END				4			// ������� (����) : ȸ�� ���� ����  
#define AUCTION_ITEM_STATE_COMPLETE			5			// ȸ�� �Ϸ� : ���� ���� ��� 	
#define AUCTION_ITEM_STATE_6              	6			// 	

#if defined(TEST140)
	#define DESTROY_AUCTION_RUN_TIME_MINUTE				30			// ��� ���� �ð�(��)
	#define DESTROY_AUCTION_RUN_READY_TIME_MINUTE		1			// ��� ���� �� �غ� �ð�
	#define DESTROY_AUCTION_RUN_GAP_TIME_HOUR			1			// ��� ���۽ð� ��
	#define DESTROY_AUCTION_PACKET_RECV_TICK			200			// �ŷ��� ���� ���� ��Ŷ ���� ��
	#define DESTROY_AUCTION_INIT_PRICE					100000		// ��� ���۰� 10��SPI
	#define DESTROY_AUCTION_GET_POSSIBLE_TIME_HOUR		2			// ����ǰ ȸ�� ���� �ð�
	#define DESTROY_AUCTION_TENDET_ITEM_NUM_LIMITED		7045530		// �Ⱓ�� ������
	#define DESTROY_AUCTION_TENDET_ITEM_NUM_UNLIMITED	7045540		// ������ ������
	#define DESTROY_AUCTION_LISTUP_ITEM_ENCHANT_TYPE_1	3			// ����, ���̴�, ������� ����Ʈ�� ��æ �ּҰ�
	#define DESTROY_AUCTION_LISTUP_ITEM_ENCHANT_TYPE_2	10			// �⺻, ���޹���, �Ƹ� ����Ʈ�� ��æ �ּҰ�
#else
	#define DESTROY_AUCTION_RUN_TIME_MINUTE				60			// ��� ���� �ð�(��)
	#define DESTROY_AUCTION_RUN_READY_TIME_MINUTE		1			// ��� ���� �� �غ� �ð�
	#define DESTROY_AUCTION_RUN_GAP_TIME_HOUR			3			// ��� ���۽ð� ��
	#define DESTROY_AUCTION_PACKET_RECV_TICK			200			// �ŷ��� ���� ���� ��Ŷ ���� ��
	#define DESTROY_AUCTION_INIT_PRICE					100000		// ��� ���۰� 10��SPI
	#define DESTROY_AUCTION_GET_POSSIBLE_TIME_HOUR		24			// ����ǰ ȸ�� ���� �ð�
	#define DESTROY_AUCTION_TENDET_ITEM_NUM_LIMITED		7045530		// �Ⱓ�� ������
	#define DESTROY_AUCTION_TENDET_ITEM_NUM_UNLIMITED	7045540		// ������ ������
	#define DESTROY_AUCTION_LISTUP_ITEM_ENCHANT_TYPE_1	3			// ����, ���̴�, ������� ����Ʈ�� ��æ �ּҰ�
	#define DESTROY_AUCTION_LISTUP_ITEM_ENCHANT_TYPE_2	10			// �⺻, ���޹���, �Ƹ� ����Ʈ�� ��æ �ּҰ�
#endif

//////////////////////////////////
// ����� ��� ������ ����
struct DESTROY_AUCTION_INFO
{
	UID64_t			DAuctionUID;		// ��� ��ȣ
	UID64_t			ItemUID;			// ������ ������ȣ
	ItemNum_t		ItemNum;			// ������ ��ȣ
	BYTE			ItemKind;			// ������ ����
	ItemNum_t		ItemCount;			// �Ǹ� ����(������ ��� �Ѿ� ����)
	ItemNum_t		PrefixCodeNum;		// ���� �ɼ�(������ 0)
	ItemNum_t		SuffixCodeNum;		// ���� �ɼ�(������ 0)
	BYTE			EnchantCount;		// ��þƮ ��(������ 0)
	MARKET_ENCHANT_INFO	Enchant[8];		// ��þƮ ���� ����
	ItemNum_t		ShapeItemNum;		// �ƸӴ� ���� ����, ���޹���� ����Ʈ ����
	INT				ColorCode;			// ���� ����Ʈ ����
	BYTE			MoneyType;			// ȭ�� Ÿ��(0=SPI, 1=WP)
	INT				Price;				// �ְ������ݾ�
	INT				MyTenderPrice;		// ���� ������ �ݾ�(������Ȳ������ ���)
	ATUM_DATE_TIME	DestroyedTime;		// ������ �ı�(���)�ð� 
	BYTE			DAuctionState;		// �����ۿ� ���� ��� ����(�����, ����, ���� ���)
	UID32_t			AccountUID;			// �ְ������� ���� UID
	UID32_t			CharacterUID;		// �ְ������� ĳ���� UID
	ATUM_DATE_TIME	DAuctionEndTime;	// ����ǰ ȸ�� ���� �ð�

	DESTROY_AUCTION_INFO()
	{
		MEMSET_ZERO(this, sizeof(DESTROY_AUCTION_INFO));
	}
	DESTROY_AUCTION_INFO(DESTROY_AUCTION_INFO *i_pInfo)
	{
		MEMSET_ZERO(this, sizeof(DESTROY_AUCTION_INFO));
		memcpy(this, i_pInfo, sizeof(DESTROY_AUCTION_INFO));
	}
};
typedef mt_vector<DESTROY_AUCTION_INFO*>			DESTROY_AUCTION_LIST;
typedef mt_vector<DESTROY_AUCTION_INFO*>::iterator	DESTROY_AUCTION_ITR;

//////////////////////////////////
// ��� ��ȣ�� ��� ã��
struct DESTROY_AUCTION_LIST_DAuctionUID_Find_Object
{
	DESTROY_AUCTION_LIST_DAuctionUID_Find_Object(UID64_t index): m_nFindIndex(index){};
	bool operator()(const DESTROY_AUCTION_INFO *i_pInfo)
	{
		return i_pInfo->DAuctionUID == m_nFindIndex;
	}
	UID64_t m_nFindIndex;
};
// end 2014-01-03 by jhseol&bckim, �ı������ - �ش� �߰�

// 2014-02-10 by jhseol&bckim, ü�θ�
#define CHANNELING_TOKEN_01			'!'
#define CHANNELING_TOKEN_02			'?'
#define CHANNELING_TOKEN_03			'$'
#define CHANNELING_TOKEN_04			'%'
#define CHANNELING_TOKEN_05			'^'
#define CHANNELING_TOKEN_06			'&'
/****************************************
Ư�� �� [ @ , # , * ] �� �̹� ������̴�.
****************************************/
#define CHANNELING_MUNPIA_NUMBER	(BYTE)1

inline int GetChannelingNumByAccountName(char* i_AccountName)
{
	if ( 0 >= strlen(i_AccountName) )
	{
		return 0;
	}
	switch(i_AccountName[0])
	{
	case CHANNELING_TOKEN_01:	return CHANNELING_MUNPIA_NUMBER;
	default:	return 0;
	}
};

#define USER_CI_SIZE		150
// end 2014-02-10 by jhseol&bckim, ü�θ�

#endif
