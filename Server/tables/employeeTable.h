
#ifndef __BUDDY_TABLE_H__
#define __BUDDY_TABLE_H__

#include "config.h"

class EmployeeTable
{
public:
	struct EmployeeData
	{
		U32						Id_;
		std::string				name_;
		RaceType				race_;				//����
		std::string				AIClassName_;
		QualityColor			quality_;			//Ʒ��
		U32						star_;				//�Ǽ�
		JobType					Job_;
		U32						JobLevel_;	
		U32						soul_;				//ת���ɻ�����
		std::vector<U32>		skillneed_;			//������������Ӷ��֮��
		std::vector<float>		grows_;				//Ʒ�ʶ�Ӧ������	
		std::vector<U32>		evolutionNum_;		//���������������
		std::vector<float>		properties_;
		std::vector< std::pair<S32,S32> >	defaultSkill_;
	};

public:
	static bool load(char const *fn);
	static bool check();
	static EmployeeData const * getEmployeeById(U32 id);
	static U32	getSkillLevelUpNeed(U32	id,U32 sklv);
public:
	static std::map< S32 , EmployeeData* >  data_;
};

#endif