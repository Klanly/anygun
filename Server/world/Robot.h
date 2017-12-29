//������
#ifndef __ROBOT_H__
#define __ROBOT_H__

#include "config.h"
#include "entity.h"
#include "baby.h"
#include "employee.h"
#include "InnerPlayer.h"

class Robot : public InnerPlayer
{
	static U32				robotTID_;
public:
	Robot(U32 robot);
	Robot(SGE_DBPlayerData& robot);
	~Robot();
public:
	void setRobotInst(U8 robotTmpId);
public:
	
	void setRobotInst(SGE_DBPlayerData &tmp);
	void getRobotInst(COM_SimplePlayerInst &out);
	
	U32	getGUID(){return robotId_;}	
	Robot* asRobot(){return this;}
	const char* getNameC(){return robotName_.c_str();}
	bool isBattleAtkTimeout(){return !battleActive_;}
public:
	void		addBabyFromTemlate(U32 uBabyTmpId,U32 uLevel);
	COM_Item*	genItemInst(U32 itemId);
	void		wearEquipment();
	const ItemTable::ItemData* getWearEquipData(EquipmentSlot eSlot);		///��ȡ������ϴ���װ��
public:
	U32				robotId_;
	std::string		robotName_;
	JobType			Job_;
	U32				JobLevel_;
	bool			isPlayerData_;			//������������ݻ��Ǳ�������,true���������
};

#endif