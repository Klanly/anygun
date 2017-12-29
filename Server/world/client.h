/** File generate by <hotlala8088@gmail.com> 2015/01/13  
 */

#ifndef __WORLDCONN_H__
#define __WORLDCONN_H__


#include "config.h"
#include "proto.h"

//-------------------------------------------------------------------------
/** ע�� ��������Ȼ��Ż��� player 
 *  ���ӽ�������е�½��֤,��֤ͨ����ŻὨ��player����game logic
 */

class Account;
class ClientHandler 
	: public BINChannel< Server2ClientStub, Client2ServerProxy >
	, public Client2ServerProxy
{
public:
	ClientHandler();
	~ClientHandler();
	bool handleClose();
	std::string infomation();

public:
	#include "Client2ServerMethods.h"
public:
	Account*account_;//�˻���Ϣ
	int32 serverId_; //�����Ϣ
	std::string ip_;
};

#endif // endif __WORLDCONN_H__
