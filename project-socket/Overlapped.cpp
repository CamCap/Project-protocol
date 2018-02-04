#include "stdafx.h"
#include "Overlapped.h"


Overlapped::Overlapped()
{
	m_RecvOverlapped.buf.buf = m_buff;
	m_RecvOverlapped.buf.len = MAX_BUFFER;
	m_RecvOverlapped.io_type = IO_RECV;

	m_SendOverlapped.io_type = IO_SEND;

	InitializeCriticalSection(&m_CriticalSection);
}


Overlapped::~Overlapped()
{
}

BOOL Overlapped::CreateSocket()
{
	memset(&m_RecvOverlapped, 0, sizeof(PER_IO_OVERLAPPED));
	m_socket = WSASocket(PF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	
	if (m_socket == INVALID_SOCKET)
		return FALSE;

	return TRUE;
}

BOOL Overlapped::DestorySocket()
{
	if (m_socket == INVALID_SOCKET) return FALSE;

	shutdown(m_socket, SD_SEND);

	m_RecvOverlapped.io_type = IO_NONE;

	//IOCP�� PostComponent�� ��

	return TRUE;
}

BOOL Overlapped::Recv()
{
	if (m_socket == INVALID_SOCKET) return FALSE;
	//if (m_ovlp.hEvent == NULL) return FALSE;
	if (m_RecvOverlapped.io_type == IO_NONE) return FALSE;

	DWORD dwflag = 0;
	DWORD dwrecvbyte = 0;

	int result = WSARecv(m_socket, &m_RecvOverlapped.buf, 1, &dwrecvbyte, &dwflag, &m_RecvOverlapped, NULL);

	if (result == SOCKET_ERROR && (WSAGetLastError() == ERROR_IO_PENDING))
	{
		return FALSE;
	}

	m_RecvOverlapped.io_type = IO_RECV;

	return TRUE;
}

BOOL Overlapped::Send(Packet* packet)
{
	if (m_socket == INVALID_SOCKET) return FALSE;
	//if (m_ovlp.hEvent == NULL) return FALSE;

	DWORD dwflag = 0;
	DWORD dwsendbyte = 0;

	//���۷� �ٲ���ϴµ�...
	//sendbuf.buf = GetSendBuff(packet);
	m_SendOverlapped.buf.buf = (char*)packet;
	m_SendOverlapped.buf.len = packet->packet_size;

	////sendbuf�� �ٲ����...�̰� buff�� �ΰ��� �ʳ�?
	int result = WSASend(m_socket, &m_SendOverlapped.buf, 1, &dwsendbyte, dwflag, &m_SendOverlapped, NULL);

	if (result == SOCKET_ERROR && (WSAGetLastError() == ERROR_IO_PENDING))
	{
		return FALSE;
	}

	m_SendOverlapped.io_type = IO_SEND;

	return TRUE;
}


//
//char* Overlapped::GetSendBuff(Packet* packet)
//{
//	if(m_iotype == IO_SEND)
//
//	return sendbuf;
//}