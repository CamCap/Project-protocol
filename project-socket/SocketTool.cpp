#include "stdafx.h"
#include "SocketTool.h"


SocketTool::SocketTool()
{
}


SocketTool::~SocketTool()
{
	
}

BOOL SocketTool::Bind(WinSocket* sock)
{
	if (bind((SOCKET)*sock, (SOCKADDR*)sock, sizeof(sockaddr_in)))
	{
		Log::Instance()->WriteLog(_LOGFILE, "Bind Error");
		return false;
	}
	else
		Log::Instance()->WriteLog(_LOGFILE, "Bind Success");


	return true;
}


BOOL SocketTool::Accept(WinSocket* sock)
{
	int size = sizeof(SOCKADDR_IN);

	if (accept((SOCKET)*sock, (sockaddr*)sock, &size) == INVALID_SOCKET)
	{
		Log::Instance()->WriteLog(_LOGFILE, "Acceprt Error!");
		return false;
	}
	else
		Log::Instance()->WriteLog(_LOGFILE, "Accept Success");

	//ACCEPT�� �����ϸ� ��� WinSocket ��ü�� ��������??
	//�װ��� ���⼭ �� �ʿ�� ����. SocketTool�� �ܼ��� Accept�� ���ְ�, �װ���� WinSocket��ü�� ����ִ�.

	return true;
}

BOOL SocketTool::Connect(WinSocket* sock)
{
	if (connect((SOCKET)*sock, (sockaddr*)sock, sizeof(SOCKADDR_IN)) == INVALID_SOCKET)
	{
		Log::Instance()->WriteLog(_LOGFILE, "Connect Error!");
		return false;
	}
	else
		Log::Instance()->WriteLog(_LOGFILE, "Connect Success");

	return true;
}


BOOL SocketTool::Listen(WinSocket* sock)
{
	if (listen((SOCKET)*sock, ListenQueue) == INVALID_SOCKET)
	{
		Log::Instance()->WriteLog(_LOGFILE, "Listen Error!");
		return false;
	}
	else
		Log::Instance()->WriteLog(_LOGFILE, "Listen Error");

	return true;
}

BOOL SocketTool::DisConnect(WinSocket* sock)
{
	sock->DestorySocket();
	//�̰� ���� �ǹ̰� �ֳ�? �ϴ� �׳� sockclose��Ŵ;

	return true;
}
