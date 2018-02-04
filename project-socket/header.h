#include <iostream>
#include "Log.h"
#include <stdio.h>
#include <memory>
#include <WinSock2.h>

using std::cout;
using std::cin;
using std::endl;

#define _LOGFILE "Sokcet Error Log"
#define ListenQueue 10

//소켓단위보다는 유저단위에서 로그를 남기자.
#define SOCKET_ERROR_LOG_WRITE Log::Instance()->WriteLog(_LOGFILE, WSAGetLastError());