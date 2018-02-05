#pragma once
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
	virtual bool Recv();
	virtual bool Send();
	virtual void ConnectSocket(WinSocket* socket);
//	virtual bool Register(Object* obj);
	virtual void ReleaseUser();// 유저 정보 초기화용
	virtual void DistorySocket();

	explicit operator HANDLE() { return (HANDLE)(SOCKET)(*m_ovlp); }
	explicit operator SOCKET() { return (SOCKET)(*m_ovlp); }

	//explicit operator WSAOVERLAPPED() { return (WSAOVERLAPPED)(*m_ovlp); }
private:


private:
	Overlapped* m_ovlp;
	CircleQueue m_cirque;
};

