//==============================================================================
/**
@date:		2012:7:26
@file: 		PeriodEvent.h
@author:	Lucifer
*/
//==============================================================================
#ifndef	__PeriodEvent_H__
#define	__PeriodEvent_H__
#include "config.h"
#define DAY_SECONDS		ONE_DAY_SEC
#define WEEK_SECONDS	604800

class PeriodEvent;
class BasePeriodEventTrigger
{
public:
	void init( PeriodEvent* event ){ event_ = event; }
	virtual void run(){};
private:
	PeriodEvent* event_;
};
class PeriodEvent
{
public:
	PeriodEvent(PeriodType type, const std::string script, int customPeriod = 0);
	~PeriodEvent();

	void setEventTrigger(BasePeriodEventTrigger* eventTrigger );
	// �����һ��ʱ��[idx, hour, minute] ��nextʱ�䡣
	void initTimer(int day, int hour, int minute, int sec = 0);
	// ������һ�ε�ʱʱ�䡣
	void calcNextTimer();

	PeriodType				eventType_;
	std::string				eventScript_;
	S64					triggerDatetime_;	// ��.ACE_Time_Value.sec().
	int						customPeriod_;
	BasePeriodEventTrigger*	eventTrigger_;

public:
	static void		updateDatetime();
	
	/** ��ǰʱ������·�*/   /*��һ������� ��Ҫ��ȷ����ʱ����ʹ��*/
	static S64	getMonthStart() { return monthlyStart_; }
	/** ��ǰʱ���������*/
	static S64	getWeekStart() { return weekStart_; }
	/** ��ǰʱ�������*/
	static S64	getDailyStart() { return dailyStart_; }
	/** ��ǰʱ�����Сʱ ���*/
	static S64	getHourlyStart() { return hourlyStart_; }
	
	/** ����һ����ǰ���ڶ�ʱ���ʽ xxxx-xx-xx */
	static std::string getCurShortDate();
	/** ���ص�ǰ�����ڳ�ʱ���ʽ* xxxx-xx-xx hh:mm:ss*/
	static std::string getCurLongDateTime();

	/** ���ص�ǰ��*/
	static int getCurYear();
	/** ���ص�ǰ��*/
	static int getCurMonth();
	/** ���ص�ǰ��*/
	static int getCurDay();
	/** ���ص�ǰʱ*/
	static int getCurHour();
	/** ���ص�ǰ��*/
	static int getCurMinute();
	/** ���ص�ǰ����*/
	static int getCurWeek();
	/** ���ص�ǰ����ʱ����*/
	static S64 getCurHourlyStart();

	static S64 monthlyStart_;
	static S64 weekStart_;
	static S64 dailyStart_;
	static S64 hourlyStart_;
};



#endif