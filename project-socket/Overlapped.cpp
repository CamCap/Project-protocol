#include "stdafx.h"
#include "Overlapped.h"


Overlapped::Overlapped()
{
}


Overlapped::~Overlapped()
{
}

BOOL Overlapped::CreateSocket()
{
	this->m_socket = WSASocket(PF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	
	if (m_socket == INVALID_SOCKET)
	{
		ErrorHandle();
		return false;
	}

	return TRUE;
}

BOOL Overlapped::DestorySocket()
{
	if (m_socket == INVALID_SOCKET) return false;

	if (closesocket(m_socket) == INVALID_SOCKET)
	{
		//Log::Instance()->WriteLog(_LOGFILE, "Close Socket Error, Why?");
		return false;
	}

	return TRUE;
}

BOOL Overlapped::Recv()
{
	WSABUF
	if (m_socket == INVALID_SOCKET) return false;

	int reuslt = WSARecv(m_socket, m_buff, )
}
