#pragma once
#include "Overlapped.h"
//Winsock에 Bind,Listen,Accept,Connect,DisConnect해주는 클래스

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

