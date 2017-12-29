/** File generate by <hotlala8088@gmail.com> 2015/01/13  

 */

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "config.h"
#include "client.h"
#include "entity.h"
#include "baby.h"
#include "tmptable.h"
#include "monstertable.h"
#include "ScriptHandle.h"
#include "employee.h"
#include "InnerPlayer.h"
#include "Scene.h"
#define PLAYER_SCENE_PROXY_DEF(FUNC) void scene_##FUNC;
#define PLAYER_SCENE_PROXY_IMPL(FUNC) void Player::scene_##FUNC

struct FuncPInfo;
class Team;
class ScenePlayer;
class Player : public InnerPlayer
{
	static NamePlayerMap nameStore_;
	static IdPlayerMap   idStore_;
public:
	enum State
	{
		PlayerState_None,
		PlayerState_Battle,
		PlayerState_Max,
	};
public:
	static PlayerList store_;
public:
	Player(Account *);
	~Player();
	ClientHandler *getClient();
	
	static void genDBPlayerInst(U8 playerTmpId, std::string const &playerName, SGE_DBPlayerData &out);
	static void transforDBPlayer2SimplePlayer(COM_SimplePlayerInst &inst, SGE_DBPlayerData &data);
	static Player *createPlayer(Account *pAcc,SGE_DBPlayerData &data,int32 serverId);
	static Player *getPlayerByName(std::string const &playerName);
	static Player *getPlayerByInstId(U32 instId);
	static void removePlayer(std::string const &playerName);
	static void removePlayer(Player* player);
	static void updatePlayer(float dt);
	static void cleanActivationAll(ActivityType type);
	static void OnlinePlayerPassZeroHour();
	static void saveAll();
	static void OnlinePlayerAddMoney(U32 money);
	//static void resetPlayerMineTimes();
public:
	void doScript(std::string const& script);
	void uiBehavior(UIBehaviorType type);
	void passZeroHour();
	void freeBabies();
	void freeBagItems();
	void freeEmployees();
	bool genItemInst(U32 itemId, U32 itemCount, std::vector<COM_Item*> &items, bool isBind = false, bool isLock =false);
public: ///<properties
	void calcProperty();
	void syncProp();
	void ping();
	void syncState();
	
	void lockBaby(U32 instId, bool isLock);
	void addBaby(S32 monsterId,std::vector<COM_Item> &equips);
	void addBaby(S32 monsterId,bool isToStorage = false);
	void addBaby(COM_BabyInst& inst,bool isToStorage = false);
	U32	 getminlevelbaby(S32 tableid);			//��ȡ��id�ȼ���С����
	void addBaby2(COM_BabyInst& inst,bool isToStorage = false);
	void delBabyByBabyId(S32 babyId);
	void delBaby(S32 instId);
	void delBabyOk(S32 instId);
	void remouldBaby(S32 instId);
	Baby* findBaby(U32 instId);
	Baby* findBabybyTableId(U32 tableId);
	bool checkBabyCache(S32 monsterId);
	U32	 calchasBabybyRace(RaceType type);
	///
	void initSignup();
	void initBabies();
	void initEmployees(bool first =false);
	void initBagItem();
	int32 findFirstBagEmptySlot();
	void addBagItemByItemId(U32 itemId,U32 itemCount, bool isLock = false,  S32 fromid = -1);
	void delBagItemByInstId(U32 itemInstId, U32 stack = 1,S32 fromid = -1);
	void delBagItemByItemId(U32 itemId, U32 stack = 1, int32 fromId = -1);
	void getBagItemByItemId(U32 itemId, std::vector<COM_Item*> &out);
	bool addBagItemByInst(COM_Item* item,S32 fromid = -1);
	COM_Item* getBagItemMinStackByItemId(U32 itemId); ///��С�ѵ�
	COM_Item* getBagItemByInstId(U32 instId);
	COM_Item* getEquipByInstId(U32 instId);
	S32 getFirstEmptySlot();
	U32 getBagEmptySlot();
	U32 getItemNumByItemId(U32 itemId);			//���ݱ�ID��ȡ��������
	void useItem(U32 slot , U32 target , int32 stack);
	bool wearEquipment(U32 target,U32 itemInstId );
	bool delEquipment(U32 target,U32 instId);
	U32 getBagItemSize();
	COM_Item* getItemInst(ItemContainerType type,U32 itemInstId);
	void getItemByItemSubType(ItemSubType type,std::vector<COM_Item*> &out);	//��ȡĳһ�����͵���
	COM_Item* getPlayerEquipBySlot(EquipmentSlot slot);

	void randSkillExp(U32 itemId);			//���һ�����ܼӾ���
	ErrorNo usessItem(S32 target,U32 itemID);
	bool sortBagItem();
	bool sellBagItem(U32 instId,U32 num);
	void lockItem(uint32 instId, bool isLock);
	bool openBagGrid(U32 itemId);
	bool bagItemSplit(U32 instId,U32 splitNum);
	void updateItemUseTimeout(S32 tm);
	void updateBabySellTimeout(S32 tm);
	S32 calcEmptyItemNum(U32 itemId); //������ԷŶ��ٵ��� (�ѵ�)
	void lotteryGo(U32 itemId);
	bool giveDrop(S32 dropId,bool usebase = false);
public:
	void initEquipItems(std::vector<COM_Item>& equipItems);
	Entity * getEntity(U32 id);
	///
	void subProperty(PropertyType pt);
	void resetProperty();
	void addProperty(U32 guid,const std::vector<COM_Addprop> &props);
	void autoaddprop();
	void changeProp(U32 guid,PropertyType type, float uVal);
	void caleDoubleExpTime(float dt);
	void chackLevelUp();
	void levelup();
	void calcConvertExp();		//����ת������
public:
	bool hasNpc(int npcId);
	void localAddNpc(int npcId);
	void localDelNpc(int npcId);
	void talkedNpc(int npcId);
	void talkNpc(int npcId);
	
public:
	Player* asPlayer(){return this;}
	U32	getGUID(){return playerId_;}
	const char* getNameC(){return playerName_.c_str();}
	void save();
	void deattachClient();
	void reattachClient();
	void login();
	void logout();
	void tick(float dt);
public:
	void getScenePlayerInfo(SGE_ScenePlayerInfo& info);
	void getSimpleInfo(COM_SimpleInformation &out);
	void getSimplePlayerInst(COM_SimplePlayerInst& out);
	void getSimpleScenePlayer(COM_ScenePlayerInformation& out);
	void getBattleEntityInformation(COM_BattleEntityInformation& info);
	void setPlayerInst(COM_PlayerInst &tmp);
	void getPlayerInst(COM_PlayerInst &out);
	void setDBPlayerData(SGE_DBPlayerData &tmp);
	void getDBPlayerData(SGE_DBPlayerData &out);
public:
	void syncOrder(COM_Order& order);
	bool queryPlayerInst(U32 playerId);
	void showBaby(U32 instId);
	void selectBaby(U32 instId,bool isBattle);
	void initBattleStatus(U32 battleId,GroupType battleForce,BattlePosition battlePos,bool initActive = false);
	void cleanBattleStatus(bool resetProperty = false);
	void enterBattle(S32 battleId);
	void enterBattle2(S32 battleId);
	void zoneJoinBattle(S32 zoneId);

public:
	class Scene* myScene();
	void transforScene(S32 sceneId);
	void transforHome();
	void sceneLoaded();
	void openScene(S32 sceneId);

	//����
	U32  getCopyNum(S32 sceneid);			//��ȡ�����������
	void startCopy(S32 startsecenId,S32 sceneid);
	void exitCopy();

	void joinTeam(U32 teamId,STRING& pwd);
	void exitTeam();
	Team* isTeamMember();
	Team* isTeamLeader();
	Team* myTeam();
	void kickTeamMember(U32 uPlayerId);
	void isjoinTeam(U32 teamId,B8 isFlag);
	void changeTeamSettings(U32 teamId,COM_CreateTeamInfo& ccti);
	void leaveTeam();
	void backTeam();
	void refuseBackTeam();
	void teamCallMember(S32 playerId);
	void requestJoinTeam(std::string& targetName);
	void ratifyJoinTeam(std::string& sendName);

	void addSkillExp(S32 skillID, U32 exp,ItemUseFlag flag);
	void skillLevelUp(S32 skillId);
	void learnSkill(S32 skId, U16 sklv = 1);
	void forgetSkill(S32 skId);
	bool canLearnSkill(S32 skId, U16 sklv);
	bool canLevelUpSkill(S32 skId, U16 sklv);
	void babyLearnSkill(U32 instId, U32 oldSkId, U32 newSkId,U32 newSkLv);
public:
	bool setPlayerFront(bool isFront);
public:
	bool drawLotteryBox(BoxType type,bool isFree);
	bool addEmployee(U32 buddyId);
	void addEmployee(COM_EmployeeInst& inst);
	bool delEmployee(U32 empInstId); //flag �Ƿ����
	void dismissalEmployees(std::vector< U32 >& instIds);
	bool delEmployeeOk(std::vector< U32 >& instIds);
	void removeEmployee();
	Employee* findEmployee(U32 instID);
	U32 findEmployeebyTableid(U32 tableid);
	void setBattleEmployee(U32 instID,EmployeesBattleGroup group, bool isBattle);
	void changeEmpBattleGroup(EmployeesBattleGroup group);
	bool findBattleEmployee(EmployeesBattleGroup group,U32 instId);
	std::vector<U32>&  getCurrentBattleEmployees();
	void empEvolve(U32 instId);
	void empUpstar(U32 instId);
	void empSkillLevelUp(U32 empId, S32 skillId);
	Employee* getEmployeeByTableId(U32 tableId);
	void dismissalSoul(U32 instid, U32 soulNum);
	void calcEmployeeSoul(Employee* employee);
	bool calcEmployeeCurrency(Employee* employee);
public:
	//�������
	void addQuestCounter(S32 questId);
	void reduceQuestCounter(S32 questId);
	COM_QuestInst* getQuestInst(S32 questId);
	S32 getQuestIndex(S32 questId);
	void prepareAcceptQuest(S32 questId);
	bool acceptQuest(S32 questId);
	void prepareSubmitQuest(S32 npcId, S32 questId, int32 instId);
	bool submitQuest(S32 npcId, S32 questId, int32 instId);
	bool giveupQuest(S32 questId);
	bool hasQuestByType(QuestKind qk);
	bool cleanTeamQuest();
	void cleanCopyQuest();
	void cleanGuildQuest();
	void postAcceptEvent(S32 questId);
	void postSubmitEvent(S32 questId);
	bool postQuestEvent(S32 killedId, S32 killNum = 0);
	bool postQuestKillAiEvent(S32 killedAiId, S32 killNum = 0);
	bool postQuestItemEvent(S32 itemId, S32 itemNum = 1);
	S32 checkQuestItem(S32 itemID);		//����Ƿ�����������
	void checkQuestItem();
	bool completeQuest(S32 questId);
	void transferCheckEquip();				//תְ���װ��
	void transferCheckSkill();				//תְ��鼼��
	COM_QuestTarget* getQuestTarget(COM_QuestInst& inst, U32 target);
	bool checkQuestComplate(COM_QuestInst& inst);
	bool isQuestTarget(COM_QuestInst& inst,U32 targetId);
	S32	 getQuestTargetIndex(S32 questId,U32 targetId);
	void cleanRandQuestCounter(){
		submitQuestCount_ = accecptQuestCount_ = 0;
	}
public:
	void requestAudio(int32 audioId);
	void sendChat(COM_Chat& content, const char* targetName);
	bool publishItemInst(ItemContainerType type, U32 itemInstId, ChatKind chatType, std::string& playerName);
	bool publishbabyInst(ChatKind chatType,U32 babyInstId, std::string& playerName);
	bool queryItemInst(int32 showId);
	bool querybabyInst(S32 showId);
	///gmt
	void setNoTalkTime(float t);
public:
	void findContactInfoById(U32 instId);
	void findContactInfoByName(const char* name);
	void addFriend(U32 instId);
	void delFriend(U32 instId);
	void addBlacklist(U32 instId);
	void delBlacklist(U32 instId);
	void referrFriend();
	void requestFriendList();
	void updataFriend();
	COM_ContactInfo*		findBlacklistById(U32 instId);
	COM_ContactInfo*		findFriendById(U32 instId);
 
public:
	void resetgathers();
	void initGather();
	void openGather(S32 gatherId,GatherStateType tp);
	ErrorNo checkGatherStates(S32 gatherId,GatherStateType tp);
	GatherStateType getGatherState(S32 gatherId,GatherStateType tp);
	COM_Gather* getGatherData(S32 gatherId);
	bool isGatherOpenAdvanced(MineType t);
	void mining(S32 gatherId,S32 times);
	void initCompound();
	void openCompound(U32 itemId);
	bool checkCompound(U32 itemId);
	bool makeItem(U32 itemId,U32 gemId);
	void gatherAddRollItem(U32 itemId,bool needsync);
	void itemAddProp(COM_Item *item,std::vector<std::pair< PropertyType , float > > const &d, std::vector<std::pair< PropertyType , float > > const& p );
public:
	//JJC
	void startChallenge(std::string name);
	void findRival();
	void requestJJCData();
	void resetRivalTime();
	void calcRivalNum();
	void checkMsg(std::string name);
	void battleMsg(COM_JJCBattleMsg& msg);
	void requestAllBttleMsg();
	void promoteAward(BattleType type);
	
	//���а�
	void requestJJCRank();
	void requestLevelRank();
	void requestBabyRank();
	void requestEmpRank();
	void requestPlayerFFRank();

	//��ѯ��Ϣ
	void queryOnlinePlayer(std::string& name);
	void queryPlayerbyName(std::string& name);
	void queryPlayerInstOK(SGE_DBPlayerData &data);
	void queryBaby(U32 instid);
	void queryEmployee(U32 instid);
public:
	void addMagicCurrency(S32 num);
	void addMoney(S32 num);
	void addDiamond(S32 num);
	void getFirstRechargeItem();
	void buyShopItem(S32 id, S32 num);
	bool orderFromSDK(S32 shopId,S32 num,std::string const& orderid,std::string const& paytime,float payment);
	bool orderFromGMT(S32 shopId,S32 num,std::string const& orderid,std::string const& paytime,float payment);
	bool justOrder(S32 shopId,S32 num,std::string const& orderid,std::string const& paytime,float payment);
	void wishing(COM_Wishing& wish);
	void shareWish();
public:
	void addReputation(S32 value,bool islogin = false);
	void addPlayerTitle(S32 title);
	void delPlayerTitle(S32 title);
	void setCurrentTitle(S32 title);
//�ɾ�
public:
	void initAchievement();
	void checkAchievement(S32 achId);
	bool isAchievement(S32 achId);
	void caleAchievement(AchievementType achType, U32 achValue);
	COM_Achievement* findAchievement(U32 achId);
	void requestAchaward(S32 achId);
	void requestActivityReward(U32 itemid);
	void setAchievement(AchievementType achType, U32 achValue);
	void addAchievement(AchievementType achType, U32 achValue);
public:
	void resetHundredTier();
public:
	//box
	void resetGreenBoxTime();
	void resetBlueBoxTime();
	void openBuyBox();
//GM
public:
	void gmAcceptQuest(S32 questId);
	void gmSubmitQuest(S32 questId);
	void setHundredTier(S32 tier);
	void enterHundredScene(S32 level);
	bool canGotoNextScene();
	void completeAchievement(S32 achId);
	void completeAllAchievement();
	void resetCounter();			//�������д���
	void errorMessageToC(ErrorNo errt);
	
	void setOpenSubSystemFlag(OpenSubSystemFlag ossf);
	bool getOpenSubSystemFlag(OpenSubSystemFlag ossf);

	void sign(S32 index);

	void resetBaby(S32 babyId);
	void resetBabyProp(S32 babyId);

	void setOpenDoubleTimeFlag(bool isFlag);

	void addNpc(NpcList& npcs);
	void delNpc(NpcList& npcs);
	void initNpc();
	void checkNpc();
	void initQuest();
	//VIP
	void vipreward();
	//pvpjjc
	void jjcBattleGo(U32 id);
	void calePvpPlayerGrade(Team* tmp, GroupType winGT);		//������˻���
	void caleSinglePvpPlayerGrade(GroupType winGT);
	void checkJJCsec();
	void syncMyJJCTeamMsg();
	//mail
	void initMail();
	void sendMail(STRING& playername, STRING& title, STRING& content);
	void readMail(S32 mailId);
	void delMail(S32 mailId);
	void fatchMail();
	void appendMail(std::vector<COM_Mail>& mails);
	void updataMail();
	void getMailItem(S32 mailId);

	void initSelling();
	void initSellingOk(std::vector<COM_SellItem>& items);
	void initSelledOk(std::vector<COM_SelledItem>& items);
	void fetchSell(COM_SearchContext& context,bool is2);
	void fetchSellOk(std::vector<COM_SellItem>& items,S32 total);
	void sell(S32 iteminstid, S32 babyinstid,S32 price);
	void sellOk(COM_SellItem item);
	void unsell(S32 sellid);
	void unSellOk(S32 sellid);
	void buy(S32 sellid);
	void buyOk(COM_SellItem& item);
	void buyFail(ErrorNo error);
	
	int getActivitionCount(ActivityType type);
	void resetActivation();
	void cleanActivation(ActivityType type);
	void addActivation(ActivityType type,U32 count);
	void move(COM_FPosition& pos);
	void moveToNpc(S32 npcid);
	void moveToNpc2(NpcType type);
	void moveToZone(S32 sceneId, S32 zoneId);
	void autoBattle();
	bool stopAutoBattle();
	void stopMove();

	//fix
	void fixEquipment(S32 instId, FixType type);	
	void fixAllItem(std::vector< U32 >& instIds, FixType type);
	void calcEquipmentDurability();
	//
	void makeDebirsItem(S32 instId,S32 num);

	//�ֿ�
	void initItemStorage();
	void initBabyStorage();
	void freeItemStorage();
	void freeBabyStorage();
	void depositItem(U32 instid);
	void getoutItem(U32 instid);
	bool depositBaby(U32 instid);
	bool depositBaby(COM_BabyInst& inst);
	void getoutBaby(U32 instid);
	void delStorageBaby(U32 instid);

	void sortItemStorage();
	void sortBabyStorage();

	void openGrid(StorageType tp);

	COM_Item* findItemFromStorageByInstId(U32 instid);
	COM_BabyInst* findBabyFormStorageByInstId(U32 instid);
	S32 findItemStorageFirstemptySlot();
	S32 findBabyStorageFirstemptySlot();

	void exchangeGift(std::string code);

	void giftaward(const std::string &giftName,std::vector<COM_GiftItem>& items,int32 diamond);
public:
	bool calcInRect(COM_FPosition pos);
	void calcBroadcastPlayers(SceneBroadcaster& broadcaster);
	void regBroadcastPlayer(U32 instId);
	void unregBroadcastPlayer(U32 instId);
	bool isCanVisiblePlayer(Player* p);
	bool isInVisiblePlayers(U32 instId);
	void calcVisiblePlayers();
	void regVisiblePlayer(U32 instId);
	void unregVisiblePlayer(U32 instId);
	
	void move2(COM_FPosition& pos);
	void transfor2(COM_FPosition& pos);
	void joinScene(COM_SceneInfo& info);
	void getSceneInfo(COM_SceneInfo& info);
	void levelUpMagicItem(std::vector< U32 >& items);
	void tupoMagicItem(S32 level);
	void changeMagicJob(JobType job);
	void magicItemLevelUp(S32 level,S32 exp);
    void initMagicItemLevelUp();
	void magicItemOneKeyLevel();
public:
	void requestPK(U32 playerId);
	class Guild* myGuild();
	struct COM_Guild* myGuildData();
	struct COM_GuildMember* myGuildMember();
	void updateMyGuildMember();
	bool buyGuildItem(S32 tableId,S32 times);
	bool isInGuildScene();
	int32 getGuildBattleScene();
	bool isInGuildBattleScene();
	void joinGuildBattleScene();
	int32 getGuildContribution();
	void addGuildContribution(int32 val);
	COM_Skill* findGuildSkill(int32 skId);
	void cleanGuildInfomation();
public:
	void wearFuwen(int32 itemInstId);
	void takeoffFuwen(int32 slotId);
	void compFuwen(int32 itemInstId);
public:
	void requestEmployeeQuest();
	void acceptEmployeeQuest(int32 questId, std::vector<int32> const& employees);
	void submitEmployeeQuest(int32 questId);
public:
	bool eraseSyncPlayer(S32 playerId);
public:
	//ˮ��ϵͳ
	void initCrystal();
	void crystalUp();
	void crystalUpdata(bool isflag);
	void resetCrystalProp(std::vector<int32> locks);
	COM_CrystalData		crystalData_;
public:
	//�������
	void addCourseGift();
	void delCourseGift(U32 shopid);
	void calcCourseGifttime(float delta);
	bool buyCourseGift(U32 shopid);
	std::vector<COM_CourseGift> coursegift_;
public:
	bool			isSceneLoaded_;
	bool			isGm_;
	bool			isFirstLogin_;
	int32			serverId_;
	uint64			openSubSystemFlag_;
	Account*		account_;
	time_t			loginTime_;
	time_t			logoutTime_;
	time_t			pingTime_;
	time_t			createTime_;
	float			sycnTime_;		//ͬ��˫������ʱ���CD
	bool			firstRechargeDiamond_;		//�׳�
	bool			isFirstRechargeGift_;		//�Ƿ���ȡ�׳����

	U32				playerId_;
	std::string		playerName_;
	U32			signs_;					///ǩ��
	bool		signFlag_;
	
	U32			teamId_;
	bool		isLeavingTeam_;//�Ƿ��������״̬
	
	//��Ծ��
	COM_ActivityTable activity_;

	//��Ը
	U32			wishShareNum_;					//��Ըÿ�շ���

	//JJC
	float		rivalTimes_;				//JJC��սCDʱ��
	U32			rivalNum_;					//JJC��ս����
	U32			promoteAward_;				//���������ı��
	float		rivalWaitTimes_;			//����ͬ��������ƥ��ȴ�ʱ��
	
	//����ѡ�λ
	U32			warriortrophyNum_;			//������Ӹ���

	//box
	float		greenBoxTimes_;				//��ͨ����CDʱ��
	float		blueBoxTimes_;				//��ͨ����CDʱ��
	U32			greenBoxFreeNum_;			//��ͨ������Ѵ���
	U32			employeelasttime_;			//��һ����ʯ���������ɫ����
	U32			employeeonecount_;			//��ʯ�������
	U32			employeetencount_;			//��ʯ10�������

	U64			guideIdx_;	

	//���˵���
	U32			curTier_;					//��ս��
	U32			tier_;						//��ʷ��߲�
	U32			hundredNum_;				//�������
	U32			hundredresetNum_;			//�������ô���
	//PVP
	COM_PlayerVsPlayer	pvpInfo_;
	//������һ��order

	EmployeesBattleGroup empbattlegroup_;	//��ǰ����ս��
	std::vector<U32>     battleEmpsGroup1_;
	std::vector<U32>	 battleEmpsGroup2_;
	std::vector<COM_Item*> fuwen_; ///����

	bool				firstRollEmployeeCon_; //��һ�ν��roll
	bool				firstRollEmployeeDia_; //��һ����ʯroll
	std::vector<COM_JJCBattleMsg>	battleMsg_;
	std::vector<COM_Item*>			bagItmes_;
	int32							submitQuestCount_;  ///�ύ�ܻ��������
	int32							accecptQuestCount_; ///��ȡ�ܻ��������
	std::vector<S32>				completeQuest_; ///�������
	std::vector<COM_QuestInst>		currentQuest_;  ///��ǰ����
	std::vector<COM_ContactInfo>	friend_;
	std::vector<COM_ContactInfo>	blacklist_;
	
	std::vector<S32>				titles_;
	std::vector<COM_Achievement>	achievement_;		//�ɾ�
	std::vector<std::string>			gifttype_;

	///mail
	float							fatchMailTimeout_;
	bool							isFatchMail_;
	S32								fatchMailId_;
	std::vector<COM_Mail>			mails_;

	float							noTalkTime_;	///<���Ե���ʱ
	float							worldTalkTime_; //���纰������ʱ
	float saveFreq_;
	//mall
	S32								sellIdMax_; ///����ID ���ֵ
	bool							waitSell_; ///
	bool							is2_;// mall fetch2
	bool							autoBattle_;
	std::vector<COM_SellItem>		sellitems_;
	std::vector<COM_SelledItem>		selledItems_;
	S32								initSyncEmpIndex_;
	//�����ȼ�
	S32 magicItemLevel_;
	S32 magicItemExp_;
	JobType magicItemJob_;
	S32 magicTupoLevel_;
	///�����������
	S32 sceneId_;
	ScenePlayer* scenePlayer_;
	std::vector<S32> openScenes_;
	NpcList npcList_;
	bool posDirty_;
	COM_FPosition position_; //�����е�λ��
	std::vector<U32> copynums_;				//�ɽ��븱������
	//�ֿ�
	std::vector<COM_Item*>			itemStorage_;
	std::vector<COM_BabyInst*>		babyStorage_;
	bool							isSorting_;		//����ֿ�����״̬
	U32								itemStorageSize_;	//�������д�С
	U32								babyStorageSize_;	//�������д�С
	float noBattleTime_;
	
	float nextDoingTime_;

	bool rollEmpHigh_;
	S32	 rollEmpCounter_;
	std::vector<SceneFilterType> filterTypes_;
	NpcList syncNpcs_;
	
	float updateVisiblePlayersTimeout_;
	std::vector<U32> broadcastPlayers_;
	std::vector<U32> visiblePlayers_;
	//����tableid
	std::vector<U32>	babycache_;
	//�ɼ�
	U32 gaterMaxNum_;			//�ɼ��ܴ���
	std::vector<COM_Gather>	gathers_;
	///����ϳ�
	std::vector<U32>		compounds_;
	uint32 exitGuildTime_;
	int32 guildContribution_;
	std::vector<COM_Skill> guildSkills_;
	//vip
	bool	viprewardflag_;
	//���˳�פ�ۼƳ�ֵ
	void updatemySelfRecharge();
	void requestmySelfRecharge(int index);
	COM_ADChargeTotal myselfrecharge_;
	///��Ӫ�
	///���ջ
	void updateFestival();
	void requestFestival(int index);
	COM_ADLoginTotal festival_;

	///�����ۼƳ�ֵ
	void updateSelfRecharge();
	void requestSelfRecharge(int index);
	COM_ADChargeTotal selfRecharge_;

	///ϵͳ�ۼƳ�ֵ
	void updateSysRecharge();
	void requestSysRecharge(int index);
	COM_ADChargeTotal sysRecharge_;
	
	///���˴����̵�
	void updateSelfDiscountStore();
	void buySelfDiscountStore(int itemId, int buyStack);
	COM_ADDiscountStore	selfDiscountStore_; //�����̵�
	
	///ϵͳ�����̵�
	void updateSysDiscountStore();
	void buySysDiscountStore(int itemId, int buyStack);
	COM_ADDiscountStore	sysDiscountStore_; //�����̵�
	
	void updateSelfOnceRecharge(int money);
	void requestSelfOnceRecharge(int index);
	COM_ADChargeEvery selfOnceRecharge_; ///���ʳ�ֵ

	void updateSysOnceRecharge(int money);
	void requestSysOnceRecharge(int index);
	COM_ADChargeEvery sysOnceRecharge_;

	//����
	void openCard(U16 index);
	void resetCard(bool ispasszero = false);
	bool hasCardReward(U32 id);		//����Ƿ�鵽���˽���
	COM_ADCards		selfCards_;

	//�ȵ��̵�
	void hotRoleBuy();
	COM_ADHotRole hotdata_;

	//7��

	void caleSevenday(AchievementType type,U32 qvalue);
	void sevendayClose();
	bool isSevenday(U32 qid);
	COM_Sevenday* findSevenday(U32 qid);
	void checkSevenday(U32 qid);
	void sevenReward(U32 qid);
	bool						sevenflag_;
	std::vector<COM_Sevenday>	sevenday_;

	//����
	void refreshOnlineReward();
	void requestOnlineReward(U32 index);
	bool				onlinetimeflag_;			//���߼�ʱ����
	float				onlinetime_;				//����ʱ��
	std::vector<U32>	onlinereward_;				//���߽���

	//�ɳ�����
	void buyFund(U32 level);
	bool				isFund_;				//�Ƿ������
	std::vector<U32>	fundtag_;				//������		�ȼ�

	//����ۼƳ�ȡ
	void updateEmployeeActivity(bool isflag=false);
	void requestEmployeeActivity(int index);
	COM_ADEmployeeTotal empact_;

	//�ȼ����
	void requestLevelGift(U32 level);
	std::vector<U32> levelgift_;

	void verificationSMS(std::string phoneNumber,std::string code);
	//�ֻ�������֤
	std::string smsCode_;
	std::string phoneNumber_; //���ֻ����ʱ�洢
	uint64		smsTime_;
	//С�����
	bool updateMinGiftActivity(int32 shopId = 0);
	COM_ADGiftBag gbact_;

	//��¼��ֵ
	std::vector<SGE_OrderInfo> orders_;

	//�����̵�
	void updateIntegral(U32 cont = 0);
	void integralShopBuy(U32 id, U32 num);
	void resetIntegralState();
	void updateIntegralShop();
	COM_IntegralData icdata_;
};


#endif