/************************************************************************/
/**
 * @file	battle.h
 * @date	2015-3-2015/03/06 	
 * @author 	Lucifer<hotlala8088@gmail.com>            					
 * */
/************************************************************************/

#ifndef __BATTLE_H__
#define __BATTLE_H__ 


#include "config.h"
#include "scenetable.h"
#include "ScriptHandle.h"
class Player;
class Entity;
class Baby;
class Monster;
class Team;
class Robot;

class Battle
{
public:
	
	typedef std::vector<COM_ReportAction> RAList;

	enum
	{
		BattleCacheSize = 4000
	};

	enum BattleState 
	{
		BS_None,
		BS_Used,
	};


	enum ChangePropType{
		CPT_Normal,
		CPT_State,
		CPT_Fanji,
	};

	//static const char* logdir_;
	static std::vector<Battle*> battleCache_;

	static void init();
	static void fini();
	static Battle* find(S32 id);
	static Battle* getOneFree();
	static void updateBattle(float dt);
public:

	Battle();

	void create(Team* pTeam, ZoneInfo* pZone);
	void create(Player* player,ZoneInfo* zone);
	void create(Player* p0, Player* p1,BattleType tp = BT_PVP);
	void create(Player* pPlayer, Robot* pRobot);
	void create(Team* pTeam,S32 battleTableId);
	void create(Player* p0, S32 battleTableId);
	void create(Team* pTeamDown,Team* pTeamUp,BattleType tp);
	void create(Player* player,Team* pTeam,BattleType tp);
	void create(Player* sendplayer,U32 playerId); //�𳡾�PK
	void create(Player* player, Monster* monster);

	void update(float dt);
	
	void battleOver();
	SneakAttackType calcSneakAttack(Player *player);
public:
///�غ�
	bool execRound(float dt);
	bool execOneOrder();
	void startBattle();
	void syncRoundReport();
	void cleanRound();
public:
	void insertState(S8 pos, U32 stId, U32 isAction);
	bool checkState(S8 pos, U32 type);
	void removeState(S8 pos, U32 stId);
	void clearState(S8 pos);
	void deleteStateByTrun();
	void lookupStateByTrun();
	COM_State*  findState(StateType type, BattlePosition pos);
	U32  getStateLevel(StateType type, BattlePosition pos);
	void cuttickState(StateType type, BattlePosition pos, U32 cutNum);
	void postState();
public:
	std::vector<COM_ReportAction>& actions(){return roundReport_.actionResults_;}
	void pushRA(COM_Order& order,int sklevel = 0);
	void pushOrder(COM_Order &order);
	bool checkSecondOrder(COM_Order &order);
	void pushOrderByAI(COM_Order &order);
	void pushOrderTimeout(U32 instId);
	void orderSort();
	void checkUnite();									///�ϻ�
	void updateUnite();
	COM_Order* findOrder(U32 instId, bool skipDontCare = true);
	COM_Order* getCurrentOrder();
	bool findOrder(BattlePosition targetPos,U32 skillId);
	Entity* findEntityByPos(S8 pos);  
	Entity* findEntityById(U32 id); 
	void eraseEntityByPos(S8 pos);
	bool isInThisBattle(Entity *pEntity);
	S32 getIndex(U32 instId);
	void selectBaby(Player *player, U32 instId, bool isBattle);
	bool hasBaby(Player *player);
	bool isBattleBaby(U32 babyId);
	bool flee(Player* player,bool isFly = false);
	void fly(Entity* entity);
	void catchBaby(S8 pos,Entity* handle);
	void changePosition(BattlePosition src, BattlePosition dest);
	void changeProp(ChangePropType, BattlePosition, PropertyType, float, bool isBao=false);
	void changeProp(S8 pos, PropertyType type, float val, bool bao= false);
	void changePropBystate(S8 pos, PropertyType type, float val);
	void changePropByfanji(S8 pos, PropertyType type, float val, bool bao=false);
	void changeReportSkillId(U32 skillId,S8 pos);
	void changeOrderSkillId(U32 skillId);
	void changeOrderTarget(S8 pos);
	void removeCurrentOrder();
	void addActionCounter(U32 casterId, U32 uTargetPos, PropertyType type, float val, bool bao);
	//void exitBattleinst();
	void allLose();
	void calcBattleReward();
	void calcBattleRewardPVE();
	void calcBattlePlayerRewardPVE(Player* player);
	void calcBattleRewardPVR();
	void calcBattleRewardPVH();
	void calcBattlePlayerRewardPVH(Player* player);
	void calcBattleRewardGuild();
	void calcBattleRewardPVP();
	void calcBattleRewardPK();
	void calcBattlePKFlee(Player* player);
	void checkKillMonster(Player* player);
	Monster* findMonster(U32 id);
	bool checkCurrentAction();
	COM_ReportAction *getCurrentAction();
	BattlePosition calcFriendPosition(Entity *pEntity); ///�����Ѿ�λ

	U32 orderCounter(Entity *pEntity);
	bool hasOnceMagic(Entity *pEntity);
	void calcWinner();
	void addWaveMonster();
	BattlePosition findPosition(Entity* pEntity,GroupType type);
	BattlePosition findMonsterPosition();

	void initAI();
	void update(Entity* ent);
	void addHuwei(BattlePosition target, BattlePosition caster){ huwei_.push_back(std::pair<BattlePosition ,BattlePosition>(target,caster));}
	void addMonster(std::vector<std::string>& className);
	void calcPlayerKillEvent(Player* caster, Entity* target);
	
	void getInitData(COM_InitBattle& r,U32 playerid);
	S32 findMaxMpPos(GroupType type);
	S32 findMinHpPos(GroupType type);
	S32 findMaxHpPos(GroupType type);
	bool checkForceHp(GroupType type, float valueHp);
	BattlePosition findBossPos();
	U32 getMonsterType(BattlePosition pos);
protected:
	void cleanPosTable();
	void regenPosTable();
	void setPosTable(BattlePosition bp, Entity *p);
	void resetEntityProp(Entity *p);//������ս��ǰ��Ѫħ
	void cleanOderParam();
	void setOrderParam(OrderParamType opt, S32 param);
	void cleanHuwei(){huwei_.clear();}
	BattlePosition getHuwei(BattlePosition target);

	void prepareOrder(); ///��ǰ���order
	bool checkState(Entity *p); ///����޲���״̬
	bool isInvalid(Entity *p);
	void removePlayer(Player *player,COM_ReportAction* pra);
	
	bool calcBabyLoyal(COM_Order& order);
	void battleItem();		//ս��ʹ�õ���
	void battleWeapon();	//ս���л�����
	void battleSkill();		//ս��ʹ�ü���
	void checkBattleSkill();
	
	S32 totalAtkVal(S32 unitId, S32 unitNum, S32 val);
	void cleanUnitAtk(){unitAtk_.clear();}

public:
	void createPlayerUnit(Player* player,GroupType gt = GT_Down);
	void createMonsterUnits(std::vector<std::string>& monsters, std::vector<Monster*> &units);
	void createPlayerEmployees(Player*player);
protected:
	void cleanBattle();
	void checkBattleStatus();
	void checkCleaner(COM_BattleOverClearing&);
	void checkInit(COM_InitBattle&);
	void checkReport();
	void checkEntity();
	void checkOrder();
	void checkSameGuid();
	void logJoinBattle();
	void logExitBattle();
public:
	
	S32									opentime_; //
	
	bool								activeRound_;	///��ʼ�غ� ��־
	bool								hasPlayerPushOrder_; //�Ƿ��������������
	S32									id_;
	S32									battleDataId_;	///ս����ID 
	BattleState							battleState_;
	BattleType							battleType_;
	GroupType							battleWinner_;
	U32									actionIndex_;		///��ǰֻ������
	U32									roundCount_;	///ս���غ���
	COM_BattleReport 					roundReport_;	///�غ�ս��
	SneakAttackType						sneakattack_;	///͵Ϯ��ҽǶ�
	S32									upWave_;   ///�Ϲ��ﲨ��
	S32									downWave_; ///�¹��ﲨ��
	float								waitCloseTimeout_; ///�Ȳ���ORDER �ر�ս��ʱ��
	float								waitOrderTimeout_; ///��һ����ҷ���order ��ʼ��ʱ
	float								waitCalcOrderTimeout_; ///��̼�����
	Robot*								battleRobot_;		///���߾�����������
	///����
	std::vector<Entity*>				entities_;		//ս����Ա
	std::vector<Monster*>				monsters_;		//�ܹ���
	std::vector<std::vector<Monster*> > monsterList_;   //�������
	std::vector<Monster*>				killmonsters_;	//��ɱ����
	std::vector<Baby*>					deadthBaby_;
	std::map<S32,S32>					posTable_;
	std::map<S32,S32>					orderParam_;
	std::vector<std::pair<BattlePosition, BattlePosition> > huwei_;	///������������λ��, ������λ��		
	std::vector<Team*> teams_;
	std::vector<std::pair<S32 ,S32> > unitAtk_;	///ÿ�غϺϻ��˺�ͳ��
	int32 upLosePlayerSum_;
	int32 downLosePlayerSum_;
	int32 guildSceneId_;
	int32 guildNpcId_;
};

#endif