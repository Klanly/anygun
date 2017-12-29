#ifndef	__GMCMDMGR_H__
#define	__GMCMDMGR_H__
/** GM����*/
#include "config.h"
#include "account.h"
class GMCmdMgr
{
public:
	struct GmCmd
	{
		GmCmd():gmLevel_(GML_All){}
		GMLevel		gmLevel_;		//<gm����
		std::string scriptFunName_;	//<�ű�������
	};

	static void addGmCmd( std::string& cmdName,GMLevel level,std::string& funName);
	static void callGmCmd(Account* account,char const* cmd);
	static void callGmCmd(Player* player,char const* cmd);
	static std::map<std::string,GmCmd>		GmCmds_;
};

#endif