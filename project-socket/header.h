#include <iostream>
#include "Log.h"
#include <stdio.h>
#include <memory>
#include <WinSock2.h>

using std::cout;
using std::cin;
using std::endl;

#define _LOGFILE "Project-Protocol"
#define ListenQueue 10

#define SOCKET_ERROR_LOG_CODE Log::Instance()->WriteLog(_LOGFILE, WSAGetLastError());
#define ERROR_LOG(X) Log::Instance()->WriteLog(_LOGFILE, X); //���⸦ �Ű������� ���ֹ��� �ʰ� ���� �� �ִ� ����� ������?
#define SAFE_DELETE(p) { if((p)) delete (p); (p) = NULL; }
#define SAFE_DELETE_ARR(p) { if((p)) delete[] (p); (p) = NULL; }