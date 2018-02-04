#pragma once
#include "SockObject.h"
#include "CircleQueue.h"

////2018.01.22
////Client ���� ��ü
////���� ���� ��ü���Լ� ������ �ް� recv, send�Ѵ�.
////�������������� ���� ��ü���� �����ޱ�
//overlapped Ŭ�������� ������ �ϴ�....

class SockUser
	:public SockObject
{
public:
	SockUser();
	~SockUser();

public:
	virtual bool Recv(char* data);
	virtual bool Send(char* data);
	virtual void ConnectSocket(WinSocket* socket);
	virtual bool Register(Object* obj);
	virtual void DistorySocket();

	explicit operator HANDLE() { return (HANDLE)(SOCKET)(*m_socket); }

private:

	//void ErrorHandle();

private:
	WinSocket* m_socket;
//	WinSocket* m_sendsock;

	CircleQueue m_cirque;
};

