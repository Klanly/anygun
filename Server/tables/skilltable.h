/************************************************************************/
/**
 * @file	skilltable.h
 * @date	2015-3-2015/03/05 	
 * @author 	Lucifer<hotlala8088@gmail.com>            					
 * */
/************************************************************************/

#ifndef __SKILL_TABLE_H__
#define __SKILL_TABLE_H__

#include "config.h"

class SkillTable
{
public:
	struct Core
	{
		bool dontCare_; //buff ���㶯
		S32 id_;
		std::string skillName_;
		S32 level_;
		S32 costHp_;
		S32 costMana_;
		U32 exp_;
		U32	learnGroup_;	//��Ϊ0�ǿ�ѧϰ����
		U32	learnpre_;		//ѧϰ�˼���ǰ������(����ID)
		S32 learnCoin_;		//ѧϰ�˼���ǰ����������Ǯ��
		U32 learnLv_;		//ѧϰ�˼���ǰ���������ȼ���
		SkillType		skType_;
		SkillTargetType targetType_;
		bool isPhysic_;
		bool isMelee_; //�Ƿ��ܴ����
		PropertyType	resistPropType_;
		float				resistNum_;
		U32				levelUpNeedItem_;	
		std::string  gloCondition_;
		std::string  gloAction_;
		
		std::vector<std::string> conditions_;
		std::vector<std::string> actions_;
		std::vector<std::string> filters_;
		float dropExp_;
	};
	
public:
	static bool load(char const *fn);
	static bool loadBabyEquipSkillGroup(char const* fn);
	static bool check();

	static Core const* getSkillById(S32 id,S32 skLevel);
	static void randBabyEquipSkillInfo(int32 &skillId, int32 &skillLev);
public:
	static std::map< S32 , std::vector< Core* > >  data_;
	static std::vector<std::pair<S32 ,S32> > babyEquipSkillGroup_;
};

#endif