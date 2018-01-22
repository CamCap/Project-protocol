#pragma once
#include "header.h"
#include "SockObject.h"

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
	virtual void CreateSocket();
	virtual bool Register(Object* obj);
	virtual void DistorySocket();

private:

	void ErrorHandle();

private:
//	WinSocket* m_recvsock;
//	WinSocket* m_sendsock;

	Queue* m_cirque;
};

