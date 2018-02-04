#include "stdafx.h"
#include "CircleQueue.h"


CircleQueue::CircleQueue()
	:m_front(0), m_tail(0)
{
	m_data = new char[MAX_QUEUE_LENGTH];
}


CircleQueue::~CircleQueue()
{
	SAFE_DELETE_ARR(m_data);
}

//front가 max_queue_length를 넘으려고 할 때, 큐를 초기화
void CircleQueue::InitQueue()
{
	int size = m_front - m_tail;
	if (size >= MAX_QUEUE_LENGTH)
	{
		m_front = m_tail = 0;
		return;
	}

	memcpy(&m_data[0], &m_data[m_front], size);

	m_tail = 0;
	m_front = size;
}

//데이터 삽입
//주의할 점은 front가 max_queue_length를 넘었을 떄
void CircleQueue::Push(char* data, short size)
{
	if (size == 0) return;
	if (size > MAX_QUEUE_LENGTH) return;

	if ((m_front + size) > MAX_QUEUE_LENGTH)
	{
		InitQueue();
	}
	
	memcpy(&m_data[m_front], data, size);
	m_front += size;
	
	return;
}


//패킷 사이즈만큼 빼자 ㅇㅅㅇ
Packet* CircleQueue::Pop()
{
	Packet* packet = NULL;
	int packetsize = 0;
	int size = m_front - m_tail;

	packet = ((Packet*)&m_data[m_front]);
	packetsize = packet->packet_size;

	if (packetsize < sizeof(Packet)) return NULL;
	if (size < packetsize) return NULL;

	return packet;
}