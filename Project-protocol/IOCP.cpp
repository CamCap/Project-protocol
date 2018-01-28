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
	//*2�� ������ ���μ����� 2����� ���μ����� ���������ϴٴ���.


	DWORD threadid = 0;


	for (DWORD i = 0; i < m_threadcount; i++)
	{
//		CreateThread()

		m_threads[i] = CreateThread(NULL, 0, WorkThread, this, 0, &threadid);

		//WorkThread������.
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

	// �Ҵ�� ����ü�� ������ IOCP�� �����Ѵ�. 
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
// [IN] dequeue �� IOCP �ڵ�
HANDLE CompletionPort,
 
// [OUT] I/O ���꿡 ���ؼ� ���ŵ� ����Ʈ ���̸� ������ ������ ������
LPDWORD lpNumberOfBytes,          
 
// [OUT] completion key �� ������ ������. CreateloCompletionPort() ȣ�⶧ ������ ��
PULONG_PTR lpCompletionKey,      
 
// [OUT] �񵿱� IO ������ ȣ��� �� ������ OVERLAPPED ����ü �ּ�
LPOVERLAPPED* lpOverlapped,
 
// [IN] ��� �ð�, ���ð��� ���������� �Ϸ� ��Ŷ�� �߻����� ������
// FALSE�� ���ϵǰ� lpOverlapped�� NULL�� ���õȴ�.
// INFINITE �� �����Ǹ� ���� ���ϵ��� �ʴ´�.
// 0 �� �����Ǹ� ��� ���ϵȴ�.
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
		//�����߻��ÿ� �α� Ŭ�������� �α׸� ����
		//Log::Instance()->WriteLog("Project-socket", "Accept Socket Create Fail");
		return 0;
	}


	listen_socket.SetAdr(AF_INET, htons(30000), htonl(INADDR_ANY));


	if (tool.Bind(&listen_socket) == FALSE)
	{
		//���� �α״� Bind���� �� ����
		tool.DisConnect(&listen_socket);
		return 0;
		//	Log::Instance()->WriteLog("Project-socket", "Socket Bind Error");
	}

	int send_size;
	int send_len = sizeof(send_size);


	//listen_socket�� Send buffer�� �ɼ��� Ȯ���ϱ����� �Լ�
	if (getsockopt((SOCKET)listen_socket, SOL_SOCKET, SO_SNDBUF, (char *)&send_size, &send_len) != SOCKET_ERROR)
	{
		send_size *= 100; //send buffer ũ�⸦ �� 100���?
		if (setsockopt((SOCKET)listen_socket, SOL_SOCKET, SO_SNDBUF, (char*)&send_size, sizeof(send_len)) == SOCKET_ERROR)
		{
			//setscokopt�� �������� ��

			Log::Instance()->WriteLog("Project-socket", "connect fail1");
		}
	}
	else // getsockopt ���н�
	{
		Log::Instance()->WriteLog("Project-socket", "connect faile2");
	}

	if (tool.Listen(&listen_socket) == FALSE)
	{
		tool.DisConnect(&listen_socket);
		return 0;
	}


	//accept �ݺ�
	while (1)
	{
		if (tool.Accept(&listen_socket) == FALSE)
		{
			tool.DisConnect(&listen_socket);
			continue;
		}

		//Aceept�� ������ �Ŀ�...

		SockUser* user = UserContainer::GetInstance()->Pop_EmptyUser();
		user->ConnectSocket(&listen_socket);

		UserContainer::GetInstance()->Add_CurUser(listen_socket, user);

		//�� SockUser�� ��� ����ؾߵǴµ� � ��ü�� �������...

		//socket�� IOCP�� ���
		IOCP::GetInstance()->RegisterCompletionPort(user);
	}
}


DWORD WINAPI WorkThread(LPVOID pOL)
{

	IOCP* iocp = IOCP::GetInstance();

	iocp->GetCompletionStatus()

	return 0;
}