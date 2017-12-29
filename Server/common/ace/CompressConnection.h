#ifndef __COMPRESS_CONNECTION__
#define __COMPRESS_CONNECTION__
#include "config.h"


/** ����TCP��˫����������.

	Connection ��һ�� ACE_Event_Handler �� һ�� ACE_SOCK_Stream���Լ����պͷ�
	�����ݵ�buffer(ACE_MessageBlock)���ϵ�һ��ʵ�ֻ����Ļ���TCP socket���ӵ���
	�緢�ͺͽ������ݵĹ��ܡ�

	@par ���ӵĳ�ʼ��.
	Connection �����Ϊ������ ACE_Acceptor �� ACE_Connector ����ʹ��.
	����ͨ��һ�� ACE_Acceptor ��Ϊ�������ӵĹ����࣬�����ͳ�ʼ��һ�� Connection��
	Ҳ����ͨ��һ�� ACE_Connector ��������һ�� Connection��

	@par ����״̬.
	ÿ��Connection�������ŵ�ǰ��״̬�������Ӷ��󱻴�����Ĭ��״̬Ϊ Unestablished��
	���ͨ�� ACE_Acceptor �� ACE_Connector ��Ч�������Ӻ�״̬���л��� Established��
	��ʹ�ù����г����κδ������Ӷ�������Ч�����л�����Ӧ��״̬��ֻ���� Established
	״̬�£����Ӳſ�����Чʹ��.ʹ���ſ���ͨ�� getStatus() ����õ�ǰ��״̬������
	�ж����ӵ�ǰ�Ƿ���Ч.

	@par ���ݷ���.
	ʹ����������õ��� fillSendBuffer() ��sendbuffer������ݣ�Ȼ����� flushSendBuffer
	�����õ���ʹ���žݽ���һ�η��͡�ʹ���߿��Զ�ε��� fillSendBuffer() ˳����
	�����ݡ�flushSendBuffer()���ú��ܱ�֤����һ������Ч����ȥ�ˣ������û�з���
	�����ݣ�Connection ���� reactor ע���д�¼������ڿ�д�¼�����ʱ�ٴν���
	����.

	@par ���ݽ���.
	ʹ������Ҫ���������� handleReceived() ������������ܵ������ݣ��������������
	�ݴ�С���ظ� Connection�� Connection �����recvbuffer���й���.
*/
class CompressConnection : public ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_NULL_SYNCH>
{
public:

	/** ���캯��.
		@param rbSize ����buffer��С.
		@param sbSize ����buffer��С.
	*/
	CompressConnection(size_t rbSize = 0XFFFFFF, size_t sbSize = 0XFFFFFF);

	/** ��������. */
	virtual ~CompressConnection();

	/** ���ӵĵ�ǰ״̬. */
	enum Status
	{
		/** ��ͨ��connect��accept������Ч����.
			����Ψһ��ʾ���ӿ���ʹ�õ�״̬.
		*/
		Established,
		/** ���ӳ�ʼ״̬����δͨ��connect��accept������Ч����. */
		Unestablished,
		/** ����buffer���. */
		RBOverflow,
		/** ����buffer���. */
		SBOverflow,
		/** recv����. errno�б����˶�Ӧ�Ĵ����. */
		RecvFailed,
		/** send����. errno�б����˶�Ӧ�Ĵ����. */
		SendFailed,
		/** ����ͨ��close�����ӹر�. */
		LocalClosed,
		/** Զ���Ѿ��ر�����. */
		RemoteClosed,
		/** �Խ��ܵ�����Ϣ������ִ���. */
		MsgProcFailed,
	};
	/** ������ӵ�ǰ��״̬. */
	Status getStatus()						{ return status_; }
	/** ������ӵ�ǰ״̬�����ַ���. */
	const char* getStatusDesc();
	/** ������ӵ�ǰ��errno. */
	int getErrno()							{ return errno_; }
	/** ���������ӵ�socket stream. (ACE_Acceptor �� ACE_Connector) */
	/** ��ñ������ӵ�ַ. */
	const ACE_INET_Addr& getLocalAddr()		{ return localAddr_; }
	/** ���Զ�����ӵ�ַ. */
	const ACE_INET_Addr& getRemoteAddr()	{ return remoteAddr_; }
	/** �����������ܶ�ȡ�ֽ���. */
	ACE_UINT64 getTotalReadBytes()			{ return totalRBytes_; }
	/** ������������д���ֽ���. */
	ACE_UINT64 getTotalWriteBytes()			{ return totalWBytes_; }

	/** ������ͨ�� ACEConnector �� ACE_Acceptor ��Ч����.
		�˺�����Ҫ�����������ӽ���һЩ��Ҫ�ĳ�ʼ������, ֮��������ӵ�״̬������
		�� Established.
		@return 0��ʾ�ɹ���-1��ʾʧ��(ʧ�ܺ�����close)
	*/
	virtual int open (void * = 0);

	/** �����رմ�����.
		�˺������ú����ӵ�״̬������ΪLocalClosed.
	*/
	virtual int close (u_long flags = 0);

	/**	��������䵽send buffer���ȴ�����������.
		���Զ�ε������������Ȼ��һ���Ե��� flushSendBuffer���з���.
		@param data ����ָ��.
		@param size ���ݴ�С.
	*/
	virtual void fill(void* data, size_t size);

	/** ����ǰ��sendbuffer�е����ݽ���һ�η���. 
		�˺����᳢��һ�η��ͣ����û�óɹ������ע���д�¼����ȴ���������.
	*/
	virtual void flush();
	
	/** �������������յ������¼�.
		��������Ҫ��������ӿڣ�������յ������ݣ���������������ݴ�С���ء�
		@param data ����ָ��.
		@param size ���ݴ�С.
		@return ���ش����˶�������. -1��ʾ���ִ���.
	*/
	virtual int handleReceived(void* data, size_t size) { return size; }
	
public:
	/** ACE_Event_Handler Interface. */
	virtual int handle_input(ACE_HANDLE fd);
	/** ACE_Event_Handler Interface. */
	virtual int handle_output(ACE_HANDLE fd);
	/** ACE_Event_Handler Interface. */
	virtual int handle_close(ACE_HANDLE handle, ACE_Reactor_Mask close_mask);
protected:
	/** ����ǰ������. */
	void compress();
	bool tryRecved();
	void clear();
	
	Status					status_;		///< ��ǰ������״̬.
	int						errno_;			///< ��ǰ�Ĵ����.
	ACE_INET_Addr			localAddr_;		///< �������ӵ�ַ.
	ACE_INET_Addr			remoteAddr_;	///< Զ�����ӵ�ַ.
	ACE_Message_Block		flushBuf_;		///< ����buffer.
	ACE_Message_Block		sendBuf_;		///< ����buffer.
	ACE_Message_Block		recvGzipBuf_;		///< ����buffer.
	ACE_Message_Block		sendGzipBuf_;		///< ����buffer.
	ACE_Message_Block		recvBuf_;		///< ����buffer.
	ACE_UINT64				totalRBytes_;	///< ��������ܶ�ȡ�ֽ���.
	ACE_UINT64				totalWBytes_;	///< ���������д���ֽ���.
};

#endif//__SVC_EventHandler_h__