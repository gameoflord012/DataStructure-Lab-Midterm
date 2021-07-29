#pragma once
#include "FileInfo.h"
#include "Trie.h"
#include <string>
#include <vector>
#include <map>

using namespace std;

class Database
{
public:
	static Database GetInstance();
	static bool FileExists(string path);
	static vector<wstring> GetAllPath(string directory);
	vector<FileInfo> GetResults(wstring word);

private:
	static Database* instance;
	Trie<size_t> infos;

	void BuildSaveData();
	void BuildInfos();
	void LoadInfos();
	Database();
};

