#ifndef __EMPLOYEE_QUEST_TABLES_H__
#define __EMPLOYEE_QUEST_TABLES_H__

class EmployeeSkill{
public:
	static bool load(char const* fn);
	static int32 getRestrain(int32 skillId, EmployeeSkillType type);
	static std::map<int32,std::vector<int32> > data_;
};

class EmployeeMonster{
public:
	int32 id_;
	std::vector<EmployeeSkillType> skills_;
public:
	static bool load(char const* fn);
	static EmployeeMonster const* find(int32 id);
	static std::map<int32, EmployeeMonster*> data_;
};



class EmployeeQuest{
public:
	int32 id_;
	EmployeeQuestColor color_;
	int32 timeRequier_;		//ʱ��
	int32 employeeRequier_; //��Ҫ���ٻ��
	int32 successRate_;		//�ɹ�����
	int32 cost_;			//����
	std::vector<int32>	rewards_;	///����
	std::vector<int32> monsters_;

public:
	static bool load(char const* fn);
	static bool check();
	
	static EmployeeQuest const* getQuest(int32 id){
		return data_[id];
	}

	static std::vector<int32> const getColors(EmployeeQuestColor color){
		return colors_[color];
	}

	static std::vector< std::vector<int32> > colors_;
	static std::map<int32, EmployeeQuest*> data_;
};



#endif