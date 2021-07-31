#pragma once
#include "FileInfo.h"
#include "Trie.h"
#include "SearchResult.h"
#include "SearchInfo.h"
#include <string>
#include <vector>
#include <map>

using namespace std;

class Database
{
public:
	static Database GetInstance();
	SearchResult GetResults(SearchInfo searchInfo);
	
private:
	static Database* instance;
	Trie<size_t> searchByWord;
	Trie<size_t> searchByHashtag;
	Trie<size_t> searchByFileType;
	map<wstring, size_t> searchByExtension;

	void BuildSaveData();
	void BuildDataStruct();
	void LoadDataStruct();
	static vector<wstring> GetAllPath(string directory);
	static bool FileExists(string path);
	Database();
};

