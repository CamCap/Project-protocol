#pragma once
#include "WinSocket.h"
#include "Queue.h"
#include "Object.h"

//20180122
//���� ����� First class
//client�� sockuser�� sever�� sockserver Ŭ������ ����� ����
//sockserver�� server�� ������ ǥ���ϰ�, server�� ��������� �� ���̰�
//wasoverlapped�� ǥ���ϴ°� ��������
//sockuser�� server�� �������� ��ϵ� ����
//wasoverlapped�� ǥ���� ����

//�� ���� �´� overlapped Ŭ������ �ȸ������. �����߰ڳ� ����...

//�����Լ��� ��� recv,send,createsocket,register,DistorySocket�� ��ӹ��� ���̴�.
//register�� ������ ����� ��ü�� ����ϴ°� ����


class SockObject
{
public:
	virtual bool Recv(char* data) = 0;
	virtual bool Send(char* data) = 0;
	virtual void CreateSocket() = 0;
	virtual bool Register(Object* obj) = 0;
	virtual void DistorySocket() = 0;

public:
	SockObject();
	virtual ~SockObject();

protected:
	WinSocket m_basesocket;
	Queue* m_queue;
};

