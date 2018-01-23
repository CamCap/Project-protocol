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


	return TRUE;
}
