#include "Database.h"
#include <filesystem>
#include <fstream>
#include <iostream>

using namespace std::filesystem;
using namespace std;

Database* Database::instance;



Database::Database()
{
	ifstream file(DATA_SAVE_PATH);
	if (!file.good())
	{
		BuildDatabase();
	}
}

Database::~Database()
{
	delete instance;
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

void Database::BuildDatabase()
{
	for (wstring path : GetAllPath())
	{
		files.push_back(FileInfo(path));
	}
}


