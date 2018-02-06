#pragma once
#include "SockUser.h"
#include <vector>
#include <Windows.h>
#include <map>
#include <string>
#include <algorithm>
//#include <WinSock2.h>

#define MAX_USER_COUNT 500

//20180124
//SockUser를 미리 생성하고 Pop과 Push를 통해서 관리한다.
//다중스레드(Accept,WorkThreadAPI)에서 이 객체에 임의의 Push,Pop이 일어날테니 CS를 만들자

typedef std::vector<SockUser*> VECTOR_USER;
typedef std::map<SOCKET, SockUser*> MAP_USER;

class UserContainer
{
public:
	static UserContainer* GetInstance();

public:
//	BOOL ReigsterUser(SockUser user)

	SockUser* Pop_EmptyUser();
	void Push_EmptyUser(SockUser* puser);

	void Add_CurUser(SOCKET sock, SockUser* puser);
	void Remove_CurUser(SOCKET sock);

	void DisConnect(SockUser* pUser);
//	SockUser* FindUser()

public:
	UserContainer();
	~UserContainer();

private:
	
	void  Lock() { EnterCriticalSection(&m_cs); }
	void  UnLock() { LeaveCriticalSection(&m_cs); }

private:
	VECTOR_USER m_emptyuser;
	MAP_USER m_connectuser;

	CRITICAL_SECTION m_cs;

	SockUser m_user[MAX_USER_COUNT];

private:
	static UserContainer* m_instance;
};

