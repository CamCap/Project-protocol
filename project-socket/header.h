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
#define ERROR_LOG(X) Log::Instance()->WriteLog(_LOGFILE, X); //여기를 매개변수에 구애받지 않고 만들 수 있는 방법이 없을까?
#define SAFE_DELETE(p) { if((p)) delete (p); (p) = NULL; }
#define SAFE_DELETE_ARR(p) { if((p)) delete[] (p); (p) = NULL; }