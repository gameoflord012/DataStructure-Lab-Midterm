#pragma once
#include "FileInfo.h"
#include <string>
#include <vector>
#include <map>

using namespace std;

class Database
{
public:
	map<size_t, FileInfo> fileInfos;

	static Database GetInstance();
	static bool FileExists(string path);
	static vector<std::wstring> GetAllPath(string directory);

	FileInfo GetFileInfo(size_t key);

	Database();
	Database(const Database&);

private:
	static Database* instance;

	Database(map<size_t, FileInfo> fileInfos);

	static void BuildSaveData();
	static Database* LoadDatabase(string path);
	static void BuildDataBase();
};

