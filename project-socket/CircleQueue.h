#pragma once
#include "header.h"
#include "Packet.h"

#define MAX_QUEUE_LENGTH 1024

class CircleQueue 
{
public:
	CircleQueue();
	~CircleQueue();

public:
	void Push(char* data, short size);
	Packet* Pop();
	void InitQueue();
	//bool IsFull();

private:
	char* m_data;
	int m_front;
	int m_tail;
};

