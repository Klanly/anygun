#ifndef __MONSTER_TABLE_H__
#define __MONSTER_TABLE_H__

#include "config.h"

class MonsterTable
{
public:
	struct MonsterData
	{
		U32					monsterId_;
		U32					monsterLevel_;	
		std::string			monsterClass_;
		U32					monsterType_;
		U32					twiceAction_;			//2 Ϊ����
		RaceType			race_;
		S32					assetId_;
		U32					skillNum_;				//���������
		std::string			name_;
		U32					refromMonster_;			//���������õ�monster
		std::vector<U32>	refrommItem_;			//���������������
		std::vector<S32>	gearProps_;				//��������
		std::vector<float>	properties_;			//��������	
		bool	pet_;
		U32		petProbability_;
		PetQuality petQuality_;
		BindType bindType_;
		std::vector< std::pair<S32,S32> >	defaultSkill_;
	};

	struct sortBabyFunction
	{
		bool operator()(struct COM_BabyInst* l, struct COM_BabyInst* r);
	};

public:
	static bool load(char const *fn);
	static bool check();
	static MonsterData const * getMonsterById(U32 id);

public:
	static void	genMonsterPropFromTable(U32 monsterId, COM_MonsterInst &out);

public:
	static std::map< S32 , MonsterData*>  data_;
};

class MonsterClass
{
public:
	
	struct Core
	{
		U32			monsterId_;
		U32			level_;
		U32			dropId_;
		bool		isAddValue_;
		std::string className_;
		std::vector<std::string> events_;
		std::vector<float> properties_;
	};
	
	static bool load(char const *fn);
	static void clear();
	static bool check();
	static Core const * getClassByName(std::string const& name);

public:
	static std::map< std::string, Core* > classes_;
};

class PetIntensive
{
public:

	struct Core
	{
		U32		level_;			//ǿ���ȼ�
		U32		needItem_;		
		U32		needItemNum_;
		U32		probability_;	//����
		U32		maxtime_;		//��ǰǿ���ȼ����ǿ������
		float	grow_;			//��ǰǿ���ȼ��ɳ�ϵ��
	};

	static bool load(char const *fn);
	static bool check();
	static Core const * getCoreBylevel(U32 level);

public:
	static std::map< U32, Core* > data_;
};

class Monster2Table 
{
public:
	struct Core{
		U32					monsterId_;
		U32					monsterId2_;
		U32					level_;
		U32					levelExp_;
		S32					assetId_;
		std::string			monsterClass_;
		std::vector<float>	properties_;
		std::vector< std::pair<S32,S32> >	defaultSkill_;
		std::vector<int32> leftNpcs_;
		std::vector<int32> rigthNpcs_;
	};
	static bool load(char const *fn);
	static bool check();
	static Core const * getMonster2Core(U32 id,U32 level);
	static S32	getMonsterLeftNpc(U32 id,U32 level,S32 index);
	static S32	getMonsterRightNpc(U32 id,U32 level,S32 index);
	static S32 findMonsterIdByNpcId(S32 npcId, bool&isLeft);
public:
	static std::vector< Core* > data_;
};

#endif