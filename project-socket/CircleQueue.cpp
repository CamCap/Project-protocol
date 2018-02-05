
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
BOOL CircleQueue::Push(char* data, short size)
{
	if (size == 0) return FALSE;
	if (size > MAX_QUEUE_LENGTH) return FALSE;

	if ((m_front + size) > MAX_QUEUE_LENGTH)
	{
		InitQueue();
	}
	
	memcpy(&m_data[m_front], data, size);
	m_front += size;
	
	return TRUE;
}


//패킷 사이즈만큼 빼자 ㅇㅅㅇ
//중요한걸 잊었네
//m_front부터 시작해서 packet으로 변환한다고 해서 그게 제대로 됬을리가 없음
//m_front+packetsize > 
BTZPacket* CircleQueue::GetPacket()
{
	BTZPacket* packet = NULL;
	int packetsize = 0;
	int size = m_front - m_tail;

	packet = ((BTZPacket*)&m_data[m_front]);
	packetsize = packet->packet_size;

	if (packetsize < sizeof(BTZPacket)) return NULL;
	if (size < packetsize) return NULL;

//	m_tail += packetsize;

	return packet;
}

void CircleQueue::Pop(int size)
{
	int pre = m_tail;
	m_tail += size;
}
