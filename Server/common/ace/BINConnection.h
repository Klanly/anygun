#ifndef __BINConnection_h__
#define __BINConnection_h__


#include "ProtocolMemReader.h"
#include "ProtocolWriter.h"

#include "Connection.h"

/** ����BINЭ�������ͨѶ����.
	BINConnection ����aprcЭ���������˫����ͨѶ.
	BINConnection ������ һ��ָ���� BIN stub�����Կ���ֱ�ӵ���BIN stub ��
	�ӿ���Զ˷�������.
	BINConnection ������һ�� BIN proxy �����ã������յ��Է����ݺ󣬻������
	�� proxy �Ľӿ��� ��������.

	BIN Э���ʽ:
	- HdrType: ���ݳ���.
	- BIN����
*/
template< class BIN_STUB, class BIN_PROXY , class HdrType = unsigned int>
class BINConnection : 
	public ProtocolWriter,
	public Connection,
	public BIN_STUB
{
public:
	BINConnection(size_t rbSize = 0XFFFFFF, size_t sbSize = 0XFFFFFF):
	Connection(rbSize, sbSize),
	proxy_(NULL),
	hdr_(NULL)
	{
	}

	/** ����proxyָ��. */
	void setProxy(BIN_PROXY* p)		{ proxy_ = p; }

	/** �������ӽ��յ�������.
		handleReceived �����յ������ݽ���BIN proxy����dispatch��������Ӧ�ĺ���.
	*/
	virtual int handleReceived(void* data, size_t size)
	{
		if(!proxy_)
			return size;

		// �������͹�����Э�飬������BIN dispatch��������Ӧ�Ĵ������� 
		int processed = 0;

		// ѭ������ֱ�����ܴ���Ϊֹ.
		unsigned char* d = (unsigned char*)data;
		size_t dLeft = size;
		while(1)
		{
			// �������ͷ����.
			if(sizeof(HdrType) > dLeft)
				return processed;
			HdrType dLen = *((HdrType*)d);

			// �������������.
			size_t dTLen = sizeof(HdrType) + dLen;
			if(dTLen > dLeft)
				return processed;

			// һ��������Ϣ������ ����BIN dispatcher����.
			ProtocolMemReader r((d+sizeof(HdrType)), dLen);
			if(!proxy_->dispatch(&r))
			{
				ACE_DEBUG((LM_ERROR,"Connection(%s) dispath error\n",remoteAddr_.get_host_addr()));
				return -1;
			}

			d			+= dTLen;
			dLeft		-= dTLen;
			processed	+= dTLen;
		}
		return processed;
	}

	/** Stub events. */
	virtual ProtocolWriter* methodBegin()
	{
		if(getStatus() != Connection::Established)
			return NULL;

		// ����ͷָ��λ��.
		hdr_ = sendBuf_.wr_ptr();
		// ����һ����ʱ��ͷ������.
		HdrType tempHdr = 0;
		fill(&tempHdr, sizeof(HdrType));
		return this;
	}
	virtual void methodEnd()
	{
		if(getStatus() != Connection::Established)
			return;
		// ������Ϣͷ
		*((HdrType*)hdr_) = (HdrType)((sendBuf_.wr_ptr() - hdr_) - sizeof(HdrType));
		// ����aprc����.
		flush();
	}
	/** BIN_ProtocolWriter interface. */
	virtual void write(const void* data, size_t len)
	{
		if(getStatus() != Connection::Established)
			return;
		fill((void*)data, len);
	}

private:
	BIN_PROXY*			proxy_;
	char*				hdr_;
};

#endif//__BINConnection_h__
