#pragma once
#include "header.h"

class CircleQueue 
{
public:
	CircleQueue();
	virtual ~CircleQueue();

public:
	void InitQueue();
	void Push(char* data, short size);
	char* Pop();

private:
	char* m_data;
	int m_front;
	int m_tail;
};

