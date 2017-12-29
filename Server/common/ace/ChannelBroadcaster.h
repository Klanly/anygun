#ifndef __ChannelBroadcaster_h__
#define __ChannelBroadcaster_h__

#include "ChannelConnection.h"
#include <map>

/** ���һ�� CHANNEL ���͹㲥��Ϣ�Ĺ�����.
	
	ChannelBroadcaster ����һ�� CHANNEL �ļ��ϣ����ͨ�� ChannelBroadcaster 
	������Ϣ�ķ��ͣ������Ϣ��㲥��������������е� CHANNEL ����

	ChannelBroadcaster ������ ChannelConnection �����ݹ㲥�ӿ��ϡ�
*/
template<class CHANNEL>
class ChannelBroadcaster 
{
public:
	ChannelBroadcaster(ChannelConnection * conn)
		:conn_(conn)
	{
		SRV_ASSERT(conn);
	}

	virtual ~ChannelBroadcaster()
	{
	}

	/** ���һ��channel����.
		@warning ���channel���������Ч�������ڱ�ChannelBroadcaster���������
				 ���ܱ��ر�.
	*/
	void addChannel(CHANNEL* ch)
	{
		SRV_ASSERT(ch);
		if(!ch->isValid())
		{
			ACE_DEBUG((LM_ERROR,"if(!ch->isValid())\n"));
			return ;
		}
		if(conn_ != ch->getConn()){
			ACE_DEBUG((LM_ERROR,"if(conn_ != ch->getConn())\n"));
			return ;
		}
		//ACE_DEBUG((LM_ERROR,"Insert channel %d\n",ch->getGuid()));
		channels_.insert(ch);
	}

	/** �Ƴ�һ��channel����. */
	void removeChannel(CHANNEL* ch)
	{
		SRV_ASSERT(this);
		if(!ch){
			ACE_DEBUG((LM_ERROR,"if(!ch)\n"));
			return ;
		}
		if((conn_ != ch->getConn()))
		{
			ACE_DEBUG((LM_ERROR,"Remove channel %d if((conn_ != ch->getConn()))\n",ch->getGuid()));
		}
		//ACE_DEBUG((LM_ERROR,"Remove channel %d\n",ch->getGuid()));
		if(channels_.find(ch) != channels_.end())
			channels_.erase(ch);
	}

	/** ������е�channel����. */
	void clearChannels()
	{
		channels_.clear();
	}

	/** ׼���㲥����. 
		�˲���Ϊ�����е�ÿ��connection׼����channel���ϣ��ȴ����������� fillSendingData 
		���㲥����.
	*/
	void initSendingData()
	{
		conn_->initBCSendingData(channels_);
	}

	/** ���㲥����. 
		�˲���Ϊ�����е�ÿ��connection���ô��㲥�����ݣ��ȴ��������� flushSendingData
		���͹㲥����.
	*/
	void fillSendingData(void* data, size_t size)
	{
		conn_->fillSendingData(data,size);
	}

	/** ���͹㲥����. 
		�˲���Ϊ�����е�ÿ��connection�����յ����ݷ��ͣ��㲥����.
	*/
	void flushSendingData()
	{
		conn_->flushSendingData();
	}
	typedef std::set<Channel*> ChannelSet;
	ChannelSet channels_;
	ChannelConnection* conn_;
};

#endif//__ChannelBroadcaster_h__
