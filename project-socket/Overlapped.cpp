#include "stdafx.h"
#include "Overlapped.h"


Overlapped::Overlapped()
{
	recvbuf.buf = m_buff;
	recvbuf.len = MAX_BUFFER;

	//sendbuf.bu
	//sendbuf.len = MAX_BUFFER;
}


Overlapped::~Overlapped()
{
}

BOOL Overlapped::CreateSocket()
{
	memset(&m_ovlp, 0, sizeof(WSAOVERLAPPED));
	m_socket = WSASocket(PF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	
	if (m_socket == INVALID_SOCKET)
		return FALSE;

	return TRUE;
}

BOOL Overlapped::DestorySocket()
{
	if (m_socket == INVALID_SOCKET) return FALSE;

	shutdown(m_socket, SD_SEND);

	m_iotype = IO_NONE;

	//IOCP랑 PostComponent할 것

	return TRUE;
}

BOOL Overlapped::Recv()
{
	if (m_socket == INVALID_SOCKET) return FALSE;
	if (m_ovlp.hEvent == NULL) return FALSE;

	DWORD dwflag = 0;
	DWORD dwrecvbyte = 0;

	int result = WSARecv(m_socket, &recvbuf, 1, &dwrecvbyte, &dwflag, &m_ovlp, NULL);

	if (result == SOCKET_ERROR && (WSAGetLastError() == ERROR_IO_PENDING))
	{
		return FALSE;
	}

	m_iotype = IO_RECV;

	return TRUE;
}

BOOL Overlapped::Send(Packet* packet)
{
	if (m_socket == INVALID_SOCKET) return FALSE;
	if (m_ovlp.hEvent == NULL) return FALSE;

	DWORD dwflag = 0;
	DWORD dwsendbyte = 0;

	//버퍼로 바꿔야하는데...
	//sendbuf.buf = GetSendBuff(packet);
	//sendbuf.len = packet->packet_size;

	////sendbuf로 바꿔야해...이거 buff가 두개지 않냐?
	int result = WSASend(m_socket, &sendbuf, 1, &dwsendbyte, dwflag, &m_ovlp, NULL);

	if (result == SOCKET_ERROR && (WSAGetLastError() == ERROR_IO_PENDING))
	{
		return FALSE;
	}

	m_iotype == IO_SEND;

	return TRUE;
}
//
//char* Overlapped::GetSendBuff(Packet* packet)
//{
//	if(m_iotype == IO_SEND)
//
//	return sendbuf;
//}