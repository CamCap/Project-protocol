#pragma once
#include "Overlapped.h"
//Winsock�� Bind,Listen,Accept,Connect,DisConnect���ִ� Ŭ����

class SocketTool
{
public:
	SocketTool();
	~SocketTool();

public:
	BOOL Bind(WinSocket* sock);
	BOOL Connect(WinSocket* sock);
	BOOL Accept(WinSocket* sock);
	BOOL Listen(WinSocket* sock);
	BOOL DisConnect(WinSocket* sock);
};

