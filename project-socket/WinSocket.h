#pragma once
#include <WinSock2.h>
#include "header.h"
#include "Log.h"

#define MAX_BUFFER 1024

//�����Լ��� �ʿ��� �Լ��� ��������
//�ʿ��Ѱ�...���ϻ���,ErrorHandle, DestorySocket
//Bind,Connect(Ŭ���̾�Ʈ��),Accept,Listen,Discoonect�� SocketToolŬ�������� �ذ��Ѵ�...
//��������δ� Socket�� ������ �ɵ�
//�� Ŭ������ ������ Socket ������ Socket�� ������ �ı��� ��üȭ

//send���۴� ���� �������� �ʰڽ��ϴ�~. ��¥�� ����� send�ҋ��� �ʿ䰡 ���� �Ͱ��׿�.


class WinSocket
{
public:
	virtual BOOL CreateSocket();
	virtual BOOL DestorySocket();
	void SetAdr(ADDRESS_FAMILY family, int addr, u_short port);
	void SetAdr(sockaddr_in addr);
	virtual BOOL Recv();
	virtual BOOL Send(char* data, int size);

public:
//	virtual const WinSocket* const operator= (const SOCKET sock);
	operator SOCKET() { return m_socket;}
	operator SOCKADDR*() { return (SOCKADDR*)&m_addr; }
	

public:
	explicit WinSocket();
	explicit WinSocket(SOCKET sock, sockaddr_in addr);
	~WinSocket();
	
protected:
	virtual void ErrorHandle();

	WinSocket(SOCKET) {}

protected:
	SOCKET m_socket;
	sockaddr_in m_addr;
	char m_buff[MAX_BUFFER]; // recv ����
	//
};

