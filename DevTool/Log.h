#pragma once
#include <map>
#include <fstream>
#include <string>
#include <iostream>
#include <ctime>
using std::ofstream;
using std::string;
using std::map;
using std::iterator;

//Write만 있고 Read 기능은 없음

class File
{
public:
	bool FileOpen(string filename);
	void FileClose();
	bool FileWrite(string write);
	bool FileRead(string read); // 이건 만들 생각 없음

public:
	File(string filename);
	~File();

private:
	File() {}

	bool IsFileOpen();

private:
	ofstream m_file;
};


//싱글톤 패턴 사용
//텍스트에 로그를 저장함.
//아 잠시만 분류별로 파일을 만들어서 로그를 남기고 싶은데 어떻게 하지??
//클래스 별로 나누는 것말고 다른 방법이 없을까?
//싱글톤이 이게 맞던가? 대충 맞는 것같긴한데 에러가 뜰지도...?

class Log
{
public:
	static Log* Instance();

public:
	void WriteLog(string filename, string log);

public:
	Log();
	~Log();

private:


private:
	static Log* m_instance;
	std::map<string, File> m_logmap;
};

Log* Log::m_instance = NULL;

const std::string currentDateTime() {
	time_t     now = time(0); //현재 시간을 time_t 타입으로 저장
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X : ", &tstruct); // YYYY-MM-DD.HH:mm:ss 형태의 스트링

	return buf;
}