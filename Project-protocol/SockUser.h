#pragma once
#include "header.h"
#include "SockObject.h"

////2018.01.22
////Client ���� ��ü
////���� ���� ��ü���Լ� ������ �ް� recv, send�Ѵ�.
////�������������� ���� ��ü���� �����ޱ�
//overlapped Ŭ�������� ������ �ϴ�....

class SockUser
	:public SockObject
{
public:
	SockUser();
	~SockUser();

public:
	virtual bool Recv(char* data);
	virtual bool Send(char* data);
	virtual void CreateSocket();
	virtual bool Register(Object* obj);
	virtual void DistorySocket();

private:

	void ErrorHandle();

private:
//	WinSocket* m_recvsock;
//	WinSocket* m_sendsock;

	Queue* m_cirque;
};

