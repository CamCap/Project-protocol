#pragma once
#include "WinSocket.h"
#include "CircleQueue.h"
//20180122
//�񵿱�IO�� Overlapped ��ü...
//�ٵ� �̰� ��� ������� ����� �ȳ�������

//wassend�� wasrecv�� socketobject ��ü�� �� ���̰�...

#define IO_RECV 1
#define IO_SEND 2
#define IO_NONE 0

//class CircleQueue;

struct PER_IO_OVERLAPPED : public WSAOVERLAPPED 
{
	DWORD io_type;
	WSABUF buf;
};

class Overlapped :
	public WinSocket
{
public:
	//socket�� �ƴ� wassocket�� ����
	virtual BOOL CreateSocket(); 
	virtual BOOL DestorySocket();
	virtual BOOL Recv();
	virtual BOOL Send(BTZPacket* packet);

	BOOL PushQueueData(CircleQueue* queue, int size);

	//virtual BOOL Send(c)
public:
//	explicit operator WSAOVERLAPPED() { return (WSAOVERLAPPED)m_ovlp; }
//	operator Overlapped*() { return (SOCKADDR*)&m_addr; }

	void operator =(WinSocket* socket) { m_socket = (SOCKET)*socket; }
	//operator WSAOVERLAPPED() {return (WSAOVERLAPPED)m_}

public:
	Overlapped();
	virtual ~Overlapped();

private:

	//char* GetSendBuff(Packet* packet);

private:
	PER_IO_OVERLAPPED m_SendOverlapped;
	PER_IO_OVERLAPPED m_RecvOverlapped;

	char m_sendbuf[MAX_BUFFER];
	//WSABUF sendbuf;
	//char m_sendbuf[MAX_BUFFER]; // ������ WSASend�� ���� ����..�Ф�...�ٸ� ����� ã��;�
};

