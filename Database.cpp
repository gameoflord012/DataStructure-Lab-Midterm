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
	BuildDataSave();
}

vector<wstring> Database::GetAllPath()
{
	vector<wstring> result;
	for (const auto& entry : directory_iterator(DATA_DIR))
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

void Database::BuildDataSave()
{	
	for (wstring path : GetAllPath())
	{
		FileInfo info = FileInfo(path);		
		ofstream file(info.fileDataPath);
		json j = info;
		file << j << endl;
		file.close();
	}
}


