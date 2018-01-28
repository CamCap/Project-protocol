#include "UserContainer.h"

UserContainer* UserContainer::m_instance = NULL;

UserContainer* UserContainer::GetInstance()
{
	if (m_instance == NULL) m_instance = new UserContainer();

	return m_instance;
}

UserContainer::UserContainer()
{
	SockUser* pUser;
	for (int i = 0; i < MAX_USER_COUNT; i++)
	{
		pUser = &m_user[i];
		m_emptyuser[i] = pUser;
	}

	// 임계영역 초기화
	InitializeCriticalSection(&m_cs);
}


UserContainer::~UserContainer()
{
	DeleteCriticalSection(&m_cs);
}

SockUser* UserContainer::Pop_EmptyUser()
{
	//SockUser* pUser = NULL;

	Lock();

	if (m_emptyuser.size() == 0)
	{
		UnLock();
		return NULL;
	}

//	this->m_emptyuser.erase
		
	std::vector<SockUser*>::iterator ituser = m_emptyuser.begin();

	m_emptyuser.erase(ituser);

	UnLock();

	return *ituser;
}

void UserContainer::Push_EmptyUser(SockUser* puser)
{
	if (puser == NULL)
		return;

	Lock();
	
	std::vector<SockUser*>::iterator it = std::find(m_emptyuser.begin(), m_emptyuser.end(), puser);

	if (it != m_emptyuser.end())
	{
		UnLock();
		return;
	}

	m_emptyuser.push_back(puser);

	UnLock();

	return;
}


void UserContainer::Add_CurUser(SOCKET sock, SockUser* puser)
{
	if (puser == NULL)
		return;

	Lock();

	this->m_connectuser[sock] = puser;

	UnLock();

	return;
}

void UserContainer::Remove_CurUser(SOCKET sock)
{
	std::map<SOCKET, SockUser*>::iterator it = this->m_connectuser.find(sock);
	if (it != m_connectuser.end())
	{
		m_connectuser.erase(it);
	}
}