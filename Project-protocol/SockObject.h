#pragma once
#include "SocketTool.h"
#include "Object.h"
#include "CircleQueue.h"

//20180122
//소켓 통신의 First class
//client인 sockuser와 sever인 sockserver 클래스를 상속할 예정
//sockserver는 server의 소켓을 표현하고, server에 멤버변수가 될 것이고
//wasoverlapped로 표현하는거 잊지말자
//sockuser는 server에 옵저버로 등록될 예정
//wasoverlapped로 표현될 예정

//아 쉬발 맞다 overlapped 클래스도 안만들었다. 만들어야겠네 쉬발...

//가상함수로 모두 recv,send,createsocket,register,DistorySocket를 상속받을 것이다.
//register은 소켓을 사용할 객체에 등록하는걸 말함


class SockObject
{
public:
	virtual bool Recv(char* data) = 0;
	virtual bool Send(char* data) = 0;
	virtual void ConnectSocket(WinSocket* socket) = 0;
	virtual bool Register(Object* obj) = 0;
	virtual void DistorySocket() = 0;

public:
	SockObject();
	virtual ~SockObject();

protected:
	WinSocket m_basesocket;
	CircleQueue m_queue;
};

