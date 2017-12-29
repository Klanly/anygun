#ifndef __COPYSCENE_H__
#define __COPYSCENE_H__

#include "config.h"

class CopyScene
{
public:
	struct copyTableData
	{
		U32			copyLevel_;
		U32			sceneId_;
		U32			questId_;
		U32			endQuest_;		//������������
		U32			copyNum_;		//ÿ�տɽ������
		std::vector<U32> nextSecnes_;
	};
public:
	static bool load(char const *fn);
	static bool check();

	static U32	getCopyStartQuestById(U32 id);
	static U32	getCopyLevelById(U32 id);
	static U32	getCopyNumById(U32 id);
	static bool isNextCopySecne(U32 copylevel,U32 nextId);
	static U32	getCopyAllNumByLevel(U32 playerLevel);
public:
	static std::vector<copyTableData> data_;
};


#endif