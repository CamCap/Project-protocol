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
	recv(m_socket,)

	return TRUE;
}


void SockUser::ConnectSocket(WinSocket* socket)
{
	if (socket == NULL)
	{
		Log::Instance()->WriteLog("Project-socket", "SockUser Connect to WinSocket Error");
		return;
	}
	else
		m_socket = socket;
}
