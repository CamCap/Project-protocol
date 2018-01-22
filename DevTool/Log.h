#pragma once
#include <map>
#include <fstream>
#include <string>
#include <iostream>
#include <utility>
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
	File();
	File(string filename);
	~File();

private:

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

