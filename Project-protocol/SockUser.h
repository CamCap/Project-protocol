#pragma once
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
	virtual bool Recv();
	virtual bool Send();
	virtual void ConnectSocket(WinSocket* socket);
//	virtual bool Register(Object* obj);
	virtual void ReleaseUser();// ���� ���� �ʱ�ȭ��
	virtual void DistorySocket(); //���� �ı�

	BOOL RecvGamePacket(int size);
	void PacketProcess(BTZPacket* packet);

	explicit operator HANDLE() { return (HANDLE)(SOCKET)(*m_ovlp); }
	explicit operator SOCKET() { return (SOCKET)(*m_ovlp); }


	//explicit operator WSAOVERLAPPED() { return (WSAOVERLAPPED)(*m_ovlp); }
private:

	void  Lock() { EnterCriticalSection(&m_CriticalSection); }
	void  UnLock() { LeaveCriticalSection(&m_CriticalSection); }

private:
	Overlapped* m_ovlp;
	CircleQueue m_cirque;
	CRITICAL_SECTION m_CriticalSection;
};

