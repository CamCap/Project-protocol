#include "IOCP.h"
#include "Log.h"

DWORD WINAPI Accept(LPVOID pAcceptOL);

IOCP::IOCP()
{
}


IOCP::~IOCP()
{
}


BOOL IOCP::CreateIOCP()
{
	WSADATA             wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		Log::Instance()->WriteLog("Project-socket", "WASStartup error");
		return FALSE;
	}


	m_handle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);

	if (m_handle == NULL)
	{
		Log::Instance()->WriteLog("Project-socket", "create IOCP handle error");
		return FALSE;
	}

	CreateIOCPThread();


	return true;
}

void IOCP::CleanUP()
{
}

void IOCP::CreateIOCPThread()
{
	GetSystemInfo(&m_system);


	m_threadcount = m_system.dwNumberOfProcessors * 2;
	//*2인 이유는 프로세서의 2배까지 프로세스를 생성가능하다더라.
	DWORD threadid = 0;

	for (char i = 0; i < m_threadcount; i++)
	{
		m_threads[i] = CreateThread(NULL, 0, Accept, this, 0, &threadid);

		if (m_threads[i] == NULL)
		{
			Log::Instance()->WriteLog("Project-socket", "Thread Create Fail");
		}
	}

}



DWORD WINAPI Accept(LPVOID pAcceptOL)
{
	WinSocket socket;
	if (socket.CreateSocket() == FALSE)
	{
		Log::Instance()->WriteLog("Project-socket", "Accept Socket Create Fail");
		return 0;
	}


	socket.SetAdr(AF_INET, htons(30000), htonl(INADDR_ANY));


}