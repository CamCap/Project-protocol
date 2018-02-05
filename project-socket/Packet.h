
//패킷의 부모만 구현~
//자세한 패킷은 project-protocol에서~
#ifndef  _PACKET_H_
#define _PACKET_H_

#include <Windows.h>

struct BTZPacket
{
public:
	DWORD packet_id;
	DWORD packet_size;
};


#endif // ! _PACKET_H_
