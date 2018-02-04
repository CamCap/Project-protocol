#pragma once
#include "WinSocket.h"
//20180122
//�񵿱�IO�� Overlapped ��ü...
//�ٵ� �̰� ��� ������� ����� �ȳ�������

//wassend�� wasrecv�� socketobject ��ü�� �� ���̰�...

#define IO_RECV 1
#define IO_SEND 2
#define IO_NONE 0

class Overlapped :
	public WinSocket
{
public:
	//socket�� �ƴ� wassocket�� ����
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
	WSABUF recvbuf; // �̷��� WinSocket�� recvbuff�� �ߺ��Ǵµ�?
	//WSABUF sendbuf;
	//char m_sendbuf[MAX_BUFFER]; // ������ WSASend�� ���� ����..�Ф�...�ٸ� ����� ã��;�
};

