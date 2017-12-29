#ifndef __BINChannel_h__
#define __BINChannel_h__
#include "Channel.h"
#include "ProtocolMemReader.h"
#include "ProtocolWriter.h"



/** ����binЭ�������ͨѶ Channel.

	BINChannel ��һ�� BIN_STUB��һ�� BIN_PROXY ��һ�� Channel ͨ�Źܵ�
	���ϵ�һ��ʵ����ʹ����� Channel �� BIN��ڵ��õķ��ͺͽ��չ�����
	BINChannel �����յ�������ͨ�� BIN_PROXY ������Ϣ���ɣ����� BIN_PROXY 
	�ж�Ӧ�� BIN �ӿں�����ʹ���߿���ͨ������ BIN_STUB �еĽӿڶ���Ϣ���д���
	ʹ���߻�����ͨ��������� BINChannel �� BIN_STUB �ӿڷ��� BIN ��Ϣ��

	@see BINConnection
*/
template< class BIN_STUB, class BIN_PROXY >
class BINChannel :
	public Channel,
	public BIN_STUB,
	public ProtocolWriter /* protocol writer for BIN_STUB */
{
public:
	/** �����channel���յ������ݻύ�� p ���з��ɴ���. */
	BINChannel():
	proxy_(NULL)
	{
	}

	/** ����proxyָ��. */
	void setProxy(BIN_PROXY* p)		{ 
		proxy_ = p; }

	/** ����channel���յ�������.
		����BIN proxy����dispatch.
	*/
	virtual bool handleReceived(void* data, size_t size)
	{
		if(!proxy_)
			return false;

		// �����յ�����Ϣͨ�� BIN_PROXY::dispatch ���з��ɣ����ö�Ӧ�Ľӿڡ�
		//ACE_DEBUG((LM_ERROR, "Channel(%d) size %d \n",guid_,size));
		ProtocolMemReader r(data, size);
		if(!proxy_->dispatch(&r))
		{
			ACE_DEBUG((LM_ERROR, "Channel %d %d %d dispatch error \n",guid_,size,*(U16*)data));
			return false;
		}
		return true;
	}

	/** Stub events. */
	virtual ProtocolWriter* methodBegin()
	{
		fillBegin();
		return this;
	}
	virtual void methodEnd()
	{
		fillEnd();
	}

	/** BIN_ProtocolWriter interface. */
	virtual void write(const void* data, size_t len)
	{
		fill((void*)data, len);
	}

protected:
	BIN_PROXY*		proxy_;
};

#endif//__BINChannel_h__
