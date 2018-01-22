#pragma once
class Queue
{
public:
	virtual	~Queue();

public:
	virtual void Push(char* data) = 0;
	virtual char* Pop() = 0;
};

