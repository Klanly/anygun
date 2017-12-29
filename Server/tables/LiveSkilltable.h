#ifndef __LIVESKILLTABLE_H__
#define __LIVESKILLTABLE_H__

#include "config.h"

class GatherTable
{
public:
	struct GatherCore
	{
		U32					id_;				//ID
		MineType			type_;
		S32					level_;
		U32					superdrop_;
		U32					dropId_;
		S32					money_;
		S32					addmoney_;
		S32					itemId_;
	};

public:
	static bool load(char const *fn);
	static bool check();
	static std::vector<int32> getItemsByLevel(S32 lev);
	static GatherCore const * getGatherById(S32 id);

public:
	static std::map< S32 , GatherCore* >  gatherData_;
};

class MakeTable
{
public:
	struct MakeCore
	{
		U32					id_;					//���������ĵ���ID����ITEM����һ��			
		U32					kind_;					//������Ҫ�ļ���			
		U32					level_;					//������Ҫ�ü��ܵĵȼ�
		U32					gainSkillExp_;			//��������Ʒ���õļ��ܾ���
		PropertyType		costType_;				//���вɼ��������õ���ʱ����Ҫ���ĵ���Դ
		U32					costNum_;				//���вɼ��������õ���ʱ����Ҫ���ĸ���Դ������	
		U32					profession_;			//ר��ְҵ��ר��ְҵ��������Ʒʱ����þ��鷭��
		S32					needMoney_;				//��������Ǯ
		S32					chance_;				//������Ʒ������ֱ�
		S32					newItem_;				//��Ʒװ��
		std::vector<U32>	costItems_;				//�����õ�����Ҫ���ĵĵ���ID�������������������һһ��Ӧ
		std::vector<U32>	costItemNum_;			//�����õ�����Ҫ�ĺϳɵ������������������������IDһһ��Ӧ
	};

public:
	static bool load(char const *fn);
	static bool check();

	static MakeCore const * getMakeById(S32 id);

public:
	static std::map< S32 , MakeCore* >  MakeData_;
};

#endif