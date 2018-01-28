#pragma once
#include "SockUser.h"
#include <vector>
#include <Windows.h>
#include <map>
#include <string>
#include <algorithm>

#define MAX_USER_COUNT 500

//20180124
//SockUser�� �̸� �����ϰ� Pop�� Push�� ���ؼ� �����Ѵ�.
//���߽�����(Accept,WorkThreadAPI)���� �� ��ü�� ������ Push,Pop�� �Ͼ�״� CS�� ������


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

//	SockUser* FindUser()

public:
	UserContainer();
	~UserContainer();

private:
	
	void  Lock() { EnterCriticalSection(&m_cs); }
	void  UnLock() { LeaveCriticalSection(&m_cs); }

private:
	std::vector<SockUser*> m_emptyuser;
	std::map<SOCKET, SockUser*> m_connectuser;
	CRITICAL_SECTION m_cs;

	SockUser m_user[MAX_USER_COUNT];

private:
	static UserContainer* m_instance;
};

