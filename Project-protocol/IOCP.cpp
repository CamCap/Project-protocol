#include "IOCP.h"

DWORD WINAPI Accept(LPVOID pAcceptOL);
DWORD WINAPI WorkThread(LPVOID pOL);

IOCP* IOCP::m_instance = NULL;

IOCP* IOCP::GetInstance()
{
	if (m_instance == NULL) new IOCP();

	return m_instance;
}


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


	InitializeCriticalSection(&m_criticalsection);

	m_handle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);

	if (m_handle == NULL)
	{
		Log::Instance()->WriteLog("Project-socket", "create IOCP handle error");
		CleanUp();
		return FALSE;
	}

	CreateIOCPThread();


	return true;
}

void IOCP::CleanUp()
{
}

void IOCP::CreateIOCPThread()
{
	GetSystemInfo(&m_system);


	m_threadcount = m_system.dwNumberOfProcessors * 2;
	//*2인 이유는 프로세서의 2배까지 프로세스를 생성가능하다더라.


	DWORD threadid = 0;


	for (DWORD i = 0; i < m_threadcount; i++)
	{
//		CreateThread()

		m_threads[i] = CreateThread(NULL, 0, WorkThread, this, 0, &threadid);

		//WorkThread만들자.
		if (m_threads[i] == NULL)
		{
			Log::Instance()->WriteLog("Project-socket", "Thread Create Fail");
		}
	}

	m_acceptthread = CreateThread(NULL, 0, Accept, this, 0, &threadid);

}

BOOL IOCP::RegisterCompletionPort(SockUser* lpPerSocketContext)
{
	if (lpPerSocketContext == NULL)
	{
		return FALSE;
	}

	Lock();

	// 할당된 구조체와 소켓을 IOCP와 연결한다. 
	if (!CreateIoCompletionPort((HANDLE)lpPerSocketContext, m_handle, (DWORD)lpPerSocketContext, 0))
	{
		char errcode[100];
		wsprintf(errcode, "RegisterCompletionPort Error : %d", WSAGetLastError());
		Log::Instance()->WriteLog("Project-socket", errcode);
		
		UnLock();
		return FALSE;
	}

	UnLock();

	return TRUE;
}

BOOL IOCP::GetCompletionStatus(LPDWORD pdwOutBytesTransferred, DWORD * pOutCompletionKey, WSAOVERLAPPED ** pOutOverlapped, int * pErrCode, DWORD dwWaitingTime)
{
	/*BOOL GetQueuedCompletionStatus(
// [IN] dequeue 할 IOCP 핸들
HANDLE CompletionPort,
 
// [OUT] I/O 연산에 의해서 수신된 바이트 길이를 저장할 정수형 포인터
LPDWORD lpNumberOfBytes,          
 
// [OUT] completion key 를 저장할 포인터. CreateloCompletionPort() 호출때 지정한 값
PULONG_PTR lpCompletionKey,      
 
// [OUT] 비동기 IO 연산이 호출될 때 지정된 OVERLAPPED 구조체 주소
LPOVERLAPPED* lpOverlapped,
 
// [IN] 대기 시간, 대기시간이 지날때까지 완료 패킷이 발생하지 않으면
// FALSE가 리턴되고 lpOverlapped는 NULL로 셋팅된다.
// INFINITE 가 지정되면 절대 리턴되지 않는다.
// 0 이 지정되면 즉시 리턴된다.
DWORD dwMilliseconds
*/

	BOOL result = GetQueuedCompletionStatus(m_handle, pdwOutBytesTransferred, pOutCompletionKey,

	return result;
}

/////////////////////////////////////////////////////////////////////////////////////////

DWORD WINAPI Accept(LPVOID pAcceptOL)
{
	WinSocket listen_socket;
	SocketTool tool;


	if (listen_socket.CreateSocket() == FALSE)
	{
		//에러발생시에 로그 클래스에서 로그를 남김
		//Log::Instance()->WriteLog("Project-socket", "Accept Socket Create Fail");
		return 0;
	}


	listen_socket.SetAdr(AF_INET, htons(30000), htonl(INADDR_ANY));


	if (tool.Bind(&listen_socket) == FALSE)
	{
		//에러 로그는 Bind에서 할 것임
		tool.DisConnect(&listen_socket);
		return 0;
		//	Log::Instance()->WriteLog("Project-socket", "Socket Bind Error");
	}

	int send_size;
	int send_len = sizeof(send_size);


	//listen_socket의 Send buffer의 옵션을 확인하기위한 함수
	if (getsockopt((SOCKET)listen_socket, SOL_SOCKET, SO_SNDBUF, (char *)&send_size, &send_len) != SOCKET_ERROR)
	{
		send_size *= 100; //send buffer 크기를 왜 100배로?
		if (setsockopt((SOCKET)listen_socket, SOL_SOCKET, SO_SNDBUF, (char*)&send_size, sizeof(send_len)) == SOCKET_ERROR)
		{
			//setscokopt에 실패했을 때

			Log::Instance()->WriteLog("Project-socket", "connect fail1");
		}
	}
	else // getsockopt 실패시
	{
		Log::Instance()->WriteLog("Project-socket", "connect faile2");
	}

	if (tool.Listen(&listen_socket) == FALSE)
	{
		tool.DisConnect(&listen_socket);
		return 0;
	}


	//accept 반복
	while (1)
	{
		if (tool.Accept(&listen_socket) == FALSE)
		{
			tool.DisConnect(&listen_socket);
			continue;
		}

		//Aceept를 성공한 후에...

		SockUser* user = UserContainer::GetInstance()->Pop_EmptyUser();
		user->ConnectSocket(&listen_socket);

		UserContainer::GetInstance()->Add_CurUser(listen_socket, user);

		//이 SockUser를 어디에 등록해야되는데 어떤 객체에 등록하지...

		//socket을 IOCP에 등록
		IOCP::GetInstance()->RegisterCompletionPort(user);
	}
}


DWORD WINAPI WorkThread(LPVOID pOL)
{

	IOCP* iocp = IOCP::GetInstance();

	iocp->GetCompletionStatus()

	return 0;
}