
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

//front�� max_queue_length�� �������� �� ��, ť�� �ʱ�ȭ
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

//������ ����
//������ ���� front�� max_queue_length�� �Ѿ��� ��
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


//��Ŷ �����ŭ ���� ������
//�߿��Ѱ� �ؾ���
//m_front���� �����ؼ� packet���� ��ȯ�Ѵٰ� �ؼ� �װ� ����� �������� ����
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
