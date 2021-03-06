#include "stdafx.h"
#include "Log.h"

File::File()
{

}

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
		std::cout << filename << "이 존재하지 않습니다." << std::endl;
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
		std::cout << "파일이 열리지 않음" << std::endl;
		return false;
	}

	m_file << write << std::endl;

	return true;
}

bool File::FileRead(string read)
{
	std::cout << "미구현입니다. 개발자가 만들 필요가 없지만, 그냥 넣어본 메서드입니다." << std::endl;

	return true;
}

bool File::IsFileOpen()
{
	return (m_file.fail() || m_file.bad()) ? false : true;
}

///////////////////////////////

Log* Log::m_instance = NULL;

const std::string currentDateTime() {
	time_t     now = time(NULL);
	struct tm  tstruct;
	char       buf[80];
	localtime_s(&tstruct, &now);

	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

	return buf;
	//	return std::string(logtime);
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

	//	std::pair<string, File> data(filename, file);
	//	m_logmap.insert(data);
	}
	else
	{
		string str(currentDateTime());
		str += log;

		m_logmap[filename].FileWrite(str);
	}
}

void Log::WriteLog(string filename, int errorcdoe)
{
	char errorlog[100];

	sprintf_s(errorlog, "Socket Error Code : %d", errorcdoe);

	WriteLog(filename, errorlog);
}