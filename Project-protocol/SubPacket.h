#ifndef _SUBPACKET_H
#define _SUBPACKET_H

#include "Packet.h"

#pragma pack(push)
#pragma pack(1)


#define MAXPACKETDATASIZE			1024


//---------------------------------------------------------------
// error
#define PKT_ERROR					0x00000001	//ERROR CODE
struct PKT_ERROR : BTZPacket
{
	short	error;
}

//---------------------------------------------------------------
// 로그인서버....
#define PKT_LOGIN					0x00000002
typedef struct PKT_LOGIN : BTZPacket
{
	char  id[30];
}

#pragma pack(pop)

#endif // !_SUBPACKET_H
