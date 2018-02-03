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

	memset(&m_ovlp, 0, sizeof(WSAOVERLAPPED));
	m_iotype = IO_RECV;

	if (m_socket == INVALID_SOCKET)
	{
//		ErrorHandle();
		return false;
	}

	return TRUE;
}

BOOL Overlapped::DestorySocket()
{
	if (m_socket == INVALID_SOCKET)
		return FALSE;

	shutdown(m_socket, SD_RECEIVE);

	//IOCP¿¡¼­ overlapped¶û iocp ¿¬°á ²÷±â

	return TRUE;
}


BOOL Overlapped::Recv()
{
	if (m_socket == INVALID_SOCKET) return FALSE;

	DWORD recv_bytes = 0;
	DWORD flag = 0;

	int result = WSARecv(m_socket, &recvbuf, 1, &recv_bytes, &flag, &m_ovlp, NULL);

	if (result == SOCKET_ERROR && (ERROR_IO_PENDING != WSAGetLastError()))
	{
		//OutputDebugString("WSARecv Failed!.....................................\n");
		DestorySocket();
		return FALSE;
	}

	return TRUE;
}

BOOL Overlapped::Send(char* data, int size)
{
	if (m_socket == INVALID_SOCKET) return FALSE;

	sendbuf.buf = data;
	sendbuf.len = size;

	int result = WSASend(m_socket,  );

	return TRUE;
}


