#pragma once
#include <Windows.h>
#include <winsock2.h>
#include <process.h>
#include "WinSocket.h"
#define MAX_WORKER_THREAD 5

////20180123
////IOCP Ŭ����
///WSAStart�� IOCP�� �����ϰ� ���, Bind,LIsten,Accept���� �Ѵ�.
///���� �����带 �����쿡 ����Ͽ�, IOCP�� �����Ѵ�.

class IOCP
{
public:

	BOOL CreateIOCP(); //IOCP�� ��������
	void CleanUp();

	void ReleaseIOCP();

	void SetEndIOCP() { m_isend = TRUE; }
	BOOL IsEndIOCP() { return m_isend; }


	BOOL RegisterCompletionPort(WinSocket* lpPerSocketContext);
	BOOL GetCompletionStatus(DWORD* pOutCompletionKey, LPDWORD pdwOutBytesTransferred, WSAOVERLAPPED** pOutOverlapped, int* pErrCode = NULL, DWORD dwWaitingTime = INFINITE);
	BOOL PostCompletionStatus(DWORD CompleitonKey, DWORD dwBytesTransferred = 0, WSAOVERLAPPED* pOverlapped = NULL, int* pErrCode = NULL);



public:
	IOCP();
	~IOCP();

private:
	BOOL CreateListenSocket();

	void CreateIOCPThread();

	void  Lock() { EnterCriticalSection(&m_criticalsection); }
	void  UnLock() { LeaveCriticalSection(&m_criticalsection); }

private:
	HANDLE m_handle;
	SYSTEM_INFO m_system;
	WinSocket m_serverSock;

	CRITICAL_SECTION  m_criticalsection;

	HANDLE    m_threads[MAX_WORKER_THREAD];
	BYTE      m_threadcount;

	BOOL          m_isend;
};

