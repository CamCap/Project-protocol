#pragma once
#include "WinSocket.h"
//20180122
//비동기IO인 Overlapped 객체...
//근데 이거 어떻게 만드는지 기억이 안남ㅋㅋㅋ

//wassend랑 wasrecv는 socketobject 객체가 할 것이고...

#define IO_RECV 1
#define IO_SEND 2
#define IO_NONE 0

class Overlapped :
	public WinSocket
{
public:
	//socket이 아닌 wassocket을 쓰자
	virtual BOOL CreateSocket(); 
	virtual BOOL DestorySocket();
	virtual BOOL Recv();
	virtual BOOL Send(Packet* packet);

	//virtual BOOL Send(c)
public:
	explicit operator WSAOVERLAPPED() { return m_ovlp; }
//	operator Overlapped*() { return (SOCKADDR*)&m_addr; }

public:
	Overlapped();
	virtual ~Overlapped();

private:

	//char* GetSendBuff(Packet* packet);

private:
	WSAOVERLAPPED m_ovlp;
	DWORD m_iotype;
	WSABUF recvbuf; // 이러면 WinSocket의 recvbuff랑 중복되는데?
	//WSABUF sendbuf;
	//char m_sendbuf[MAX_BUFFER]; // 순전히 WSASend를 위한 버퍼..ㅠㅠ...다른 방법을 찾고싶어
};

