#include "stdafx.h"
#include "SockUser.h"
#include "Log.h"


SockUser::SockUser()
{
	m_ovlp = new Overlapped();

	m_ovlp->CreateSocket();
	m_cirque.InitQueue();

	InitializeCriticalSection(&m_CriticalSection);
}


SockUser::~SockUser()
{
	DistorySocket();
	SAFE_DELETE(m_ovlp);

	ReleaseUser();

	DeleteCriticalSection(&m_CriticalSection);
}


bool SockUser::Recv()
{
	BOOL result = m_ovlp->Recv();

	if (result == FALSE)
	{
		SOCKET_ERROR_LOG_CODE;
		return FALSE;
	}

	return TRUE;
}

bool SockUser::Send()
{
	//여기 다시 만들자 뭔가 이상하다.

	return TRUE;
}

void SockUser::ConnectSocket(WinSocket* socket)
{
	if (socket == NULL)
	{
		//Log::Instance()->WriteLog("Project-socket", "SockUser Connect to WinSocket Error");
		ERROR_LOG("SockUser Connect to WinSocket Error");
		return;
	}
	else
		*m_ovlp = socket;

}


void SockUser::DistorySocket()
{
	m_ovlp->DestorySocket();
}

BOOL SockUser::RecvGamePacket(int size)
{
	Lock();
	SCOPE_EXIT(UnLock(););

	BTZPacket* packet = NULL;

	if (m_ovlp->PushQueueData(&m_cirque, size) == FALSE)
	{
		//UnLock();
		return FALSE;
	}
	while (true)
	{
		packet = m_cirque.GetPacket();

		if (packet == NULL) return;

		m_cirque.Pop(packet->packet_size);
  	}

	//UnLock();

	PacketProcess(packet);

	return TRUE;
}

void SockUser::PacketProcess(BTZPacket* packet)
{
}


//bool SockUser::Register(Object * obj)
//{
//	return TRUE;
//}
//
//void SockUser::ErrorHandle()
//{
//}
