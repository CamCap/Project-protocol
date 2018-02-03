#pragma once
#include "SockObject.h"
#include "CircleQueue.h"

////2018.01.22
////Client 소켓 객체
////서버 소켓 객체에게서 소켓을 받고 recv, send한다.
////옵저버패턴으로 서버 객체에게 관리받기
//overlapped 클래스부터 만들자 일단....

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

