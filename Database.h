#pragma once
#include "FileInfo.h"
#include <string>
#include <vector>

using namespace std;


class Database
{
public:
	vector<FileInfo> files;

	static vector<std::wstring> GetAllPath();
	static Database GetInstance();
	~Database();

private:
	static Database* instance;
	void BuildDatabase();
	Database();
};

