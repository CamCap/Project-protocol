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

//Write�� �ְ� Read ����� ����

class File
{
public:
	bool FileOpen(string filename);
	void FileClose();
	bool FileWrite(string write);
	bool FileRead(string read); // �̰� ���� ���� ����

public:
	File(string filename);
	~File();

private:
	File() {}

	bool IsFileOpen();

private:
	ofstream m_file;
};


//�̱��� ���� ���
//�ؽ�Ʈ�� �α׸� ������.
//�� ��ø� �з����� ������ ���� �α׸� ����� ������ ��� ����??
//Ŭ���� ���� ������ �͸��� �ٸ� ����� ������?
//�̱����� �̰� �´���? ���� �´� �Ͱ����ѵ� ������ ������...?

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
	time_t     now = time(0); //���� �ð��� time_t Ÿ������ ����
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X : ", &tstruct); // YYYY-MM-DD.HH:mm:ss ������ ��Ʈ��

	return buf;
}