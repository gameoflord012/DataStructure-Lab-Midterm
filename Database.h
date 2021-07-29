#pragma once
#include "FileInfo.h"
#include <string>
#include <vector>
#include <map>

using namespace std;


class Database
{
public:
	static vector<std::wstring> GetAllPath(string directory);
	static Database GetInstance();
	static FileInfo GetFileInfo(size_t key);

private:
	static Database* instance;
	static void BuildDataSave();
	static map<size_t, FileInfo> fileInfos;
	static void LoadFileInfos();
	Database();
};

