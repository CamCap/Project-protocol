#pragma once
#include "WinSocket.h"
//20180122
//�񵿱�IO�� Overlapped ��ü...
//�ٵ� �̰� ��� ������� ����� �ȳ�������

//wassend�� wasrecv�� socketobject ��ü�� �� ���̰�...
//�޾Ƽ� packetȭ�ϴ°� �ʿ��ҵ�.
#define IO_NONE 0
#define IO_RECV 1
#define IO_SEND 2

class Overlapped :
	public WinSocket
{
public:
	//socket�� �ƴ� wassocket�� ����
	virtual BOOL CreateSocket(); 
	virtual BOOL DestorySocket();
	virtual BOOL Recv();
	virtual BOOL Send(char* data, int size);

public:
	explicit operator WSAOVERLAPPED() { return m_ovlp; }
//	operator Overlapped*() { return (SOCKADDR*)&m_addr; }

public:
	Overlapped();
	virtual ~Overlapped();

private:
	WSAOVERLAPPED m_ovlp;
	DWORD m_iotype;
	WSABUF recvbuf; // �̷��� WinSocket�� recvbuff�� �ߺ��Ǵµ�?
	WSABUF sendbuf;
};

