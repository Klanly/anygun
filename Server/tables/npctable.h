#ifndef __NPC_TABLE_H__
#define __NPC_TABLE_H__

#include "config.h"

class NpcTable
{
public:
	struct NpcData
	{
		S32				npcId_;
		NpcType			npcType_;
		S32				sceneId_; //����ID
		S32				filterLevel_; //ɸѡ�ȼ�
		COM_FPosition	posi_;
		std::vector<S32>	filterQuest_; //ɸѡ����
	};

public:
	static bool load(char const *fn);
	static bool check();
	static NpcData const * getNpcById(S32 id);
	static void getNpcs(NpcType type,S32 sceneId, std::vector<const NpcData*>& npcs);
	static void getNpcs(NpcType type,std::vector<const NpcData*>& npcs);
public:
	static std::vector< NpcData* >  cache_;
	static std::map< S32 , const NpcData* > map_;
	static std::map< S32 , std::vector< std::vector< const NpcData* > > > mapping_; 
};

#endif