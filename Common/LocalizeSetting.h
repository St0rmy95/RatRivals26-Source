#ifndef _LOCALIZE_SETTING_H_
#define _LOCALIZE_SETTING_H_



// �������� Ư�� ����
#if defined( LANGUAGE_ITALIA )
	#define	CHAT_ALL			'<'		// ����ä��
	#define	CHAT_GUILD			'@'		// ���ä��
	#define	CHAT_ARENA			'%'		// �Ʒ���ä��
	#define	CHAT_WAR			'^'		// ����ä��
	#define	CHAT_PARTY			'#'		// ����ä��
	#define	CHAT_MAP			'!'		// ����üä��
	#define	CHAT_SELL_ALL		'$'		// �Ÿ�ä��
	#define	CHAT_CHATROOM		'&'		// �������üä��
	#define	CHAT_PTOP			'"'		// �ӼӸ�
	#define	CHAT_INFLUENCE_ALL	'*'		// �����ڰ���
	#define	CHAT_COMMAND		'/'		// ���Ӹ��ɾ�
#else
	#define	CHAT_ALL			'~'		// GM MESSAGE
	#define	CHAT_GUILD			'@'		// ���ä��
	#define	CHAT_ARENA			'%'		// �Ʒ���ä��
	#define	CHAT_WAR			'^'		// ����ä��
	#define	CHAT_PARTY			'#'		// ����ä��
	#define	CHAT_MAP			'!'		// ����üä��
	#define	CHAT_SELL_ALL		'$'		// �Ÿ�ä��
	#define	CHAT_CHATROOM		'&'		// �������üä��
	#define	CHAT_PTOP			'"'		// �ӼӸ�
	#define	CHAT_INFLUENCE_ALL	'*'		// �����ڰ���
	#define	CHAT_COMMAND		'/'		// ���Ӹ��ɾ�
#if _RAT_CHAT_SYSTEM
	#define _RAT_CHAT_ALL_INFLUENCE	'<' // To Chat ALL
#endif
#endif

#endif