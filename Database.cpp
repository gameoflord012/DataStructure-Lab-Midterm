#include "Database.h"
#include "JsonHandler.h"
#include <filesystem>
#include <fstream>
#include <iostream>

using namespace std::filesystem;
using namespace std;

Database* Database::instance;

Database::Database()
{

}

Database::Database(const Database& database)
{
	fileInfos = database.fileInfos;
}

Database::Database(map<size_t, FileInfo> fileInfos)
{
	this->fileInfos = fileInfos;
}

void Database::BuildDataBase()
{
	map<size_t, FileInfo> infos;
	for (wstring path : GetAllPath(SAVE_DATA_DIR))
	{		
		ifstream file(path);
		json j; file >> j;
		file.close();

		FileInfo info = j.get<FileInfo>();
		infos[info.key] = info;
	}

	ofstream file(DATA_BASE_PATH);
	json j = Database(infos);
	file << j;
	file.close();
}

Database* Database::LoadDatabase(string path)
{
	ifstream file(path);
	json j; 
	file >> j;
	file.close();
	return new Database(j.get<Database>());
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
		if (!FileExists(DATA_BASE_PATH))
		{
			// BuildSaveData();
			BuildDataBase();
		}
		instance = LoadDatabase(DATA_BASE_PATH);
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

bool Database::FileExists(string path)
{
	ifstream file(DATA_BASE_PATH);
	return file.good();
	file.close();
}

void Database::BuildSaveData()
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


