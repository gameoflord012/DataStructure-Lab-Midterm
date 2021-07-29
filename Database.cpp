#include "Database.h"
#include "JsonHandler.h"
#include <filesystem>
#include <fstream>
#include <iostream>

using namespace std::filesystem;
using namespace std;

Database* Database::instance;
map<size_t, FileInfo> Database::fileInfos;

Database::Database()
{
	BuildDataSave();
	LoadFileInfos();
}

void Database::LoadFileInfos()
{
	for (wstring path : GetAllPath(SAVE_DATA_DIR))
	{		
		ifstream file(path);
		json j; file >> j;
		file.close();

		FileInfo info = j.get<FileInfo>();
		fileInfos[info.key] = info;
	}
}

vector<wstring> Database::GetAllPath(string directory)
{
	vector<wstring> result;
	for (const auto& entry : directory_iterator(directory))
	{
		result.push_back(entry.path().wstring());
	}
	return result;
}

Database Database::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new Database();
	}
	return *instance;
}

FileInfo Database::GetFileInfo(size_t key)
{		
	if (!fileInfos.count(key))
	{
		throw "FileInfo key not found!";
	}

	return fileInfos[key];
}

void Database::BuildDataSave()
{	
	for (wstring path : GetAllPath(DATA_DIR))
	{
		FileInfo info = FileInfo(path);		
		ofstream file(info.fileDataPath);
		json j = info;
		file << j << endl;
		file.close();
	}
}


