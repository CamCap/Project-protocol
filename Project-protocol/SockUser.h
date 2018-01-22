#pragma once
#include "WinSocket.h"
#include "header.h"

class SockUser
{
public:
	SockUser();
	~SockUser();

public:
	BOOL Bind();
	BOOL Listen();
	BOOL Accept();

private:

	void ErrorHandle();

private:
	WinSocket* m_recvsock;
	WinSocket* m_sendsock;

};

