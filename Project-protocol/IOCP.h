#pragma once
#include <process.h>
#include "UserContainer.h"
#include "Log.h"
#include "SocketTool.h"
#include "Overlapped.h"
#define MAX_WORKER_THREAD 5

////20180123
////IOCP 클래스
///WSAStart와 IOCP를 생성하고 등록, Bind,LIsten,Accept까지 한다.
///물론 스레드를 윈도우에 등록하여, IOCP와 연결한다.

class IOCP
{
public:

	BOOL CreateIOCP(); //IOCP를 생성하자
	void CleanUp();

	void ReleaseIOCP();

	void SetEndIOCP() { m_isend = TRUE; }
	BOOL IsEndIOCP() { return m_isend; }


	BOOL RegisterCompletionPort(SockUser* lpPerSocketContext);
	BOOL GetCompletionStatus(LPDWORD pdwOutBytesTransferred, DWORD* pOutCompletionKey, WSAOVERLAPPED** pOutOverlapped, int* pErrCode = NULL, DWORD dwWaitingTime = INFINITE);
	BOOL PostCompletionStatus(DWORD CompleitonKey, DWORD dwBytesTransferred = 0, WSAOVERLAPPED* pOverlapped = NULL, int* pErrCode = NULL);

public:
	static IOCP* GetInstance();

public:
	IOCP();
	~IOCP();

private:
	//BOOL CreateListenSocket();

	void CreateIOCPThread();

	void  Lock() { EnterCriticalSection(&m_criticalsection); }
	void  UnLock() { LeaveCriticalSection(&m_criticalsection); }

private:
	HANDLE m_handle;
	SYSTEM_INFO m_system;
	WinSocket m_serverSock;

	CRITICAL_SECTION  m_criticalsection;

	HANDLE m_threads[MAX_WORKER_THREAD];
	HANDLE m_acceptthread;
	DWORD m_threadcount;

	BOOL m_isend;

private:
	static IOCP* m_instance;
};

