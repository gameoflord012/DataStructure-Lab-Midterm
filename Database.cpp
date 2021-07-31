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
	if (!FileExists(DATA_BASE_PATH))
	{
		BuildSaveData();
		BuildInfos();
	}
	LoadInfos();
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

SearchResult Database::GetResults(SearchInfo word)
{
	
}

Database Database::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new Database();
	}
	return *instance;
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

void Database::BuildInfos()
{
	Trie<size_t> myInfos;

	for (wstring path : GetAllPath(SAVE_DATA_DIR))
	{
		ifstream file(path);

		json j;
		file >> j;
		FileInfo info = j.get<FileInfo>();

		for (wstring s : info.contentWords)
		{
			myInfos.insert(s, info.key);
		}

		file.close();
	}

	ofstream file(DATA_BASE_PATH);
	json j = myInfos;
	file << j;
	file.close();
}

void Database::LoadInfos()
{
	ifstream file(DATA_BASE_PATH);
	json j;
	file >> j;
	infos = j;
	file.close();
}
