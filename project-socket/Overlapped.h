#pragma once
#include "WinSocket.h"
#include "CircleQueue.h"
//20180122
//비동기IO인 Overlapped 객체...
//근데 이거 어떻게 만드는지 기억이 안남ㅋㅋㅋ

//wassend랑 wasrecv는 socketobject 객체가 할 것이고...

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
	//socket이 아닌 wassocket을 쓰자
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
	//char m_sendbuf[MAX_BUFFER]; // 순전히 WSASend를 위한 버퍼..ㅠㅠ...다른 방법을 찾고싶어
};

