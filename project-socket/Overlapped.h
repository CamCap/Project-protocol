#pragma once
#include "WinSocket.h"
//20180122
//�񵿱�IO�� Overlapped ��ü...
//�ٵ� �̰� ��� ������� ����� �ȳ�������

//wassend�� wasrecv�� socketobject ��ü�� �� ���̰�...

class Overlapped :
	public WinSocket
{
public:
	//socket�� �ƴ� wassocket�� ����
	virtual BOOL CreateSocket(); 
	virtual BOOL DestorySocket();

public:
	operator WSAOVERLAPPED() { return m_ovlp; }
//	operator Overlapped*() { return (SOCKADDR*)&m_addr; }

public:
	Overlapped();
	virtual ~Overlapped();

private:
	WSAOVERLAPPED m_ovlp;
	DWORD m_iotype;
};

