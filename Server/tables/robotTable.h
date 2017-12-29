#ifndef __ROBOTTABLE_H__
#define __ROBOTTABLE_H__
#include "config.h"

class RobotTab
{
public:
	struct RobotData 
	{
		U32					robotId_;
		U32					robotTmpId_;			//��ȡPlayerData
		U32					robotLevel_;
		std::string			robotAIclass_;
		std::string			robotName_;				//����������
		U32					babyId_;				//������Я����ս����
		U32					babyLevel_;
		std::string			babyAIclass_;
		std::vector<U32>	employees_;				//������Я����ս���
		std::vector<U32>	equips_;				//����װ��
		JobType				job_;
		U32					JobLevel_;
	};

public:
	static bool load(char const*fn);
	static bool check();
	static RobotData const* getRobotDataById(U32 id);
public:
	static std::map<S32,RobotData*>  data_;
};

class PlayerAI
{
public:
	
	U32			id_;
	JobType		prof_;
	std::string playerClass_;
	std::string babyClass_;

public:
	static bool load(char const*fn);
	static bool check();
	static PlayerAI const* getAI(JobType jt);
public:
	static std::vector<PlayerAI*> data_;
};

class RobotActionTable
{
public:
	struct RobotActionData 
	{
		std::string			robotName_;				//����������
		std::string			userName_;				//�������˻�
		RobotActionType		actionType_;			//�ж�����
		JobType				jobtype_;				//ְҵ
		U32					npcid_;					//���Ǹ�NPC��ֹ
		U32					title_;					//����ĳƺ�
		std::vector<U32>	npclist_;				//Ѳ����
		std::vector<U32>	equips_;				//����װ��
		//U32					babyId_;				//������Я����ս����
		//U32					babyLevel_;
		//std::string			babyAIclass_;
		//std::vector<U32>	employees_;				//������Я����ս���
	};
public:
	static bool load(char const*fn);
	static bool check();
	static RobotActionData const* getActionData(std::string userName);
	static bool isRobot(std::string& name);
public:
	static std::vector<RobotActionData*> actiondata_;
};

#endif