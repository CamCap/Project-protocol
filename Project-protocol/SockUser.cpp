#include "stdafx.h"
#include "SockUser.h"
#include "Log.h"


SockUser::SockUser()
{
}


SockUser::~SockUser()
{
}


bool SockUser::Recv(char* data)
{
	BOOL result = m_socket->Recv();

	if (result == FALSE)
	{
		ErrorHandle();
		return FALSE;
	}

	return TRUE;
}


void SockUser::ConnectSocket(WinSocket* socket)
{
	if (socket == NULL)
	{
		//Log::Instance()->WriteLog("Project-socket", "SockUser Connect to WinSocket Error");
		SOCKET_ERROR_LOG_WRITE;
		return;
	}
	else
		m_socket = socket;
}
//
//void SockUser::ErrorHandle()
//{
//}
