#include "stdafx.h"
#include "SockUser.h"
#include "Log.h"


SockUser::SockUser()
{
	m_ovlp = new Overlapped();

	m_ovlp->CreateSocket();
	m_cirque.InitQueue();
}


SockUser::~SockUser()
{
	m_ovlp->DestorySocket();

	SAFE_DELETE(m_ovlp);

	ReleaseUser();
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
	Packet* packet = (Packet*)m_cirque.Pop();
	
	memcpy(m_sendbuf, packet, packet->packet_size);
	
	BOOL result = m_ovlp->Send(packet);

	if (result == FALSE)
	{
		SOCKET_ERROR_LOG_CODE;
		return FALSE;
	}

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

void SockUser::ReleaseUser()
{
	
}

void SockUser::DistorySocket()
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
