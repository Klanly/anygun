//==============================================================================
/**
	@date:		2012:5:2  
	@file: 		logger.h
	@author: 	gyl
*/
//==============================================================================
#ifndef __LOGMSGMGR_H__
#define __LOGMSGMGR_H__
#include "config.h" 

/**
 *	Desc: call back �ص�����
 * */
class LoggerCallBack:	public ACE_Log_Msg_Callback
{
public:
	/**
		Desc : ���캯��	 
	 * */
	LoggerCallBack();
	
	/**
	 *	Desc : log ʵ�ʵĻص�����
	 * @param log_record log��Ϣ
	 * @override 
	 * @retrun void
	 * */
	void log (ACE_Log_Record&);
};

/**
 * Desc :<log��־�Ĺ��� �����������  �� log ����
 * */
class Logger
{


public:
	
	~Logger(){};

	static Logger* instance();
	/**
	 * <Desc :��ʼ��
	 * */
    void init();
	/**
	 * <Desc :�����ļ���Ŀ��
	 * */
	void enableFileOut ( const ACE_TCHAR* fileName,const ACE_TCHAR* dirName=NULL);

	void logPriorityMask(u_long logType=LM_ERROR|LM_INFO);
	/**
	 * <Desc :�ͷ�
	 * */
	void finit();
private:
	Logger(){}

	std::ofstream	  outFile_; //<��־�ļ�
	LoggerCallBack	  callBack_;//<�ص��������	
	std::string		  fileName_;//<�ļ���
	std::string		  dirName_; //<Ŀ¼��
};

#endif