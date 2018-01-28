#pragma once
#include <WinSock2.h>
#include "header.h"
#include "Log.h"

#define MAX_BUFFER 1024

//가상함수로 필요한 함수만 만들어놓자
//필요한건...소켓생성,ErrorHandle, DestorySocket
//Bind,Connect(클라이언트용),Accept,Listen,Discoonect은 SocketTool클래스에서 해결한다...
//멤버변수로는 Socket만 있으면 될듯
//이 클래스의 역할은 Socket 변수와 Socket의 생성과 파괴를 객체화

//send버퍼는 따로 만들지는 않겠습니다~. 어짜피 동기라서 send할떄는 필요가 없을 것같네요.


class WinSocket
{
public:
	virtual BOOL CreateSocket();
	virtual BOOL DestorySocket();
	void SetAdr(ADDRESS_FAMILY family, int addr, u_short port);
	void SetAdr(sockaddr_in addr);
	virtual BOOL Recv();
	virtual BOOL Send(char* data, int size);

public:
//	virtual const WinSocket* const operator= (const SOCKET sock);
	operator SOCKET() { return m_socket;}
	operator SOCKADDR*() { return (SOCKADDR*)&m_addr; }
	

public:
	explicit WinSocket();
	explicit WinSocket(SOCKET sock, sockaddr_in addr);
	~WinSocket();
	
protected:
	virtual void ErrorHandle();

	WinSocket(SOCKET) {}

protected:
	SOCKET m_socket;
	sockaddr_in m_addr;
	char m_buff[MAX_BUFFER]; // recv 버퍼
	//
};

