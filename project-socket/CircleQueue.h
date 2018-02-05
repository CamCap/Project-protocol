#ifndef _CIRCLEQUEUE_H
#define _CIRCLEQUEUE_H


#include "Packet.h"
#include "header.h"

#define MAX_QUEUE_LENGTH 1024


class CircleQueue 
{
public:
	CircleQueue();
	~CircleQueue();

public:
	BOOL Push(char* data, short size);
	BTZPacket* GetPacket();
	void Pop(int size);
	void InitQueue();
	//bool IsFull();

private:
	char* m_data;
	int m_front;
	int m_tail;
};

#endif //  
