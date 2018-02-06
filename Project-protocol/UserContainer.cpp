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
	SCOPE_EXIT(UnLock(););

	if (m_emptyuser.size() == 0)
	{
		//UnLock();
		return NULL;
	}

//	this->m_emptyuser.erase
		
	VECTOR_USER::iterator ituser = m_emptyuser.begin();

	m_emptyuser.erase(ituser);

	//UnLock();

	return *ituser;
}

void UserContainer::Push_EmptyUser(SockUser* puser)
{
	if (puser == NULL)
		return;

	Lock();
	SCOPE_EXIT(UnLock(););
	
	VECTOR_USER::iterator it = std::find(m_emptyuser.begin(), m_emptyuser.end(), puser);

	if (it != m_emptyuser.end())
	{
		//UnLock();
		return;
	}

	m_emptyuser.push_back(puser);

	//UnLock();

	return;
}


void UserContainer::Add_CurUser(SOCKET sock, SockUser* puser)
{
	if (puser == NULL)
		return;

	Lock();

	m_connectuser[sock] = puser;

	UnLock();

	return;
}

void UserContainer::Remove_CurUser(SOCKET sock)
{
	MAP_USER::iterator it = m_connectuser.find(sock);
	if (it != m_connectuser.end())
	{
		m_connectuser.erase(it);
	}
}

void UserContainer::DisConnect(SockUser* pUser)
{
	Lock();

	SCOPE_EXIT(UnLock(););

	if (pUser == NULL || (SOCKET)*pUser == INVALID_SOCKET)
		return;



	//현재 연결된 유저 목록에서 지우고...
	MAP_USER::iterator it = m_connectuser.find((SOCKET)*pUser);

	if (it == m_connectuser.end())
		return;

	m_connectuser.erase(it);

	//소켓 강제 종료
	///다음의 기능은 http://egloos.zum.com/mirine35/v/5057014 참조
	///우아한 종료로 TIMEOUT이 발생할 수 있음. 시나리오는 위를 참조.
	///이 TIMEOUT이 무한 발생(실제로는 240초까지만)하면, 소켓을 사용할 수 없다.
	///이를 위해 closesocket이 대기하는 시간을 조절

	LINGER LingerStruct;
	LingerStruct.l_onoff = 1;
	LingerStruct.l_linger = 0;

	if (setsockopt((SOCKET)*pUser, SOL_SOCKET, SO_LINGER, (char*)&LingerStruct, sizeof(LingerStruct) == SOCKET_ERROR))
	{
		//return;
		ERROR_LOG("Set Socket LINGER Error ");
	}

	//closesocket((SOCKET)*pUser);
	//(SOCKET)*pUser = INVALID_SOCKET;
	pUser->DistorySocket();

}
