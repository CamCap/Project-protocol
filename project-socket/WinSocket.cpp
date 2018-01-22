#include "stdafx.h"
#include "WinSocket.h"
#include "Log.h"

WinSocket::WinSocket()
{
	m_socket = INVALID_SOCKET;
}

WinSocket::WinSocket(SOCKET sock, sockaddr_in addr)
{
	m_socket = sock;
	CopyMemory(&m_addr, &addr, sizeof(sockaddr_in));
}

WinSocket::~WinSocket()
{
	DestorySocket();
}

BOOL WinSocket::CreateSocket()
{
	m_socket = socket(PF_INET, SOCK_STREAM, 0);

	if (m_socket == INVALID_SOCKET)
	{
		ErrorHandle();
		return false;
	}

	return true;
}

BOOL WinSocket::DestorySocket()
{
	if (m_socket == INVALID_SOCKET) return false;

	if (closesocket(m_socket) == INVALID_SOCKET)
	{
		Log::Instance()->WriteLog(_LOGFILE, "Close Socket Error, Why?");
		return false;
	}

	return true;
}

void WinSocket::SetAdr(ADDRESS_FAMILY family, int addr, u_short port)
{
	memset(&m_addr, 0, sizeof(m_addr));
	m_addr.sin_family = family;
	m_addr.sin_addr.s_addr = addr;
	m_addr.sin_port = port;
}

void WinSocket::SetAdr(sockaddr_in addr)
{
	CopyMemory(&m_socket, &addr, sizeof(sockaddr_in));
}


void WinSocket::ErrorHandle()
{
	char wrtiestr[100];
	sprintf_s(wrtiestr, "WinSocketError Value %d", m_socket);

	Log::Instance()->WriteLog(_LOGFILE, wrtiestr);
}

/*
const WinSocket* const WinSocket::operator= (const SOCKET sock)
{
	//...

	return ~;
}
*/