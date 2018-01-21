#pragma once
#include "Queue.h"
class CircleQueue :
	public Queue
{
public:
	CircleQueue();
	virtual ~CircleQueue();

public:
	virtual void Push(char* data);
	virtual char* Pop();

private:
	char* m_data;
	int m_front;
	int m_tail;
};

