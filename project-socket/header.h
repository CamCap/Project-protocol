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

//���ϴ������ٴ� ������������ �α׸� ������.
#define SOCKET_ERROR_LOG_WRITE Log::Instance()->WriteLog(_LOGFILE, WSAGetLastError());