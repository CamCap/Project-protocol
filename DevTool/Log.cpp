#include "Log.h"

File::File(string filename)
{
	FileOpen(filename);
}

File::~File()
{
	FileClose();
}

bool File::FileOpen(string filename)
{
	m_file.open(filename, std::ios::app);

	if (!IsFileOpen()) {
		std::cout << filename << "�� �������� �ʽ��ϴ�." << std::endl;
		return false;
	}

	return true;
}

void File::FileClose()
{
	if (!IsFileOpen())
		return;

	m_file.close();
}

bool File::FileWrite(string write)
{
	if (!IsFileOpen())
	{
		std::cout << "������ ������ ����" << std::endl;
		return false;
	}

	m_file << write << std::endl;
}

bool File::FileRead(string read)
{
	std::cout << "�̱����Դϴ�. �����ڰ� ���� �ʿ䰡 ������, �׳� �־ �޼����Դϴ�." << std::endl;

	return true;
}

bool File::IsFileOpen()
{
	return (m_file.fail() || m_file.bad()) ? false : true;
}

////////////////////////


Log::Log()
{
}


Log::~Log()
{
}

Log* Log::Instance()
{
	if (m_instance == NULL)
		m_instance = new Log();

	return m_instance;
}

void Log::WriteLog(string filename, string log)
{
	if (m_logmap.find(filename) == m_logmap.end())
	{
		File file(filename);

		std::pair<string, File> data(filename, file);
		m_logmap.insert(data);
	}
	else
	{
		string str(currentDateTime());
		str += log;

		m_logmap[filename].FileWrite(str);
	}
}

