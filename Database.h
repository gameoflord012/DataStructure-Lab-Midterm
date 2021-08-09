#pragma once
#include "FileInfo.h"
#include "Trie.h"
#include "SearchResult.h"
#include "SearchInfo.h"
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

class Database
{
public:
	static Database GetInstance();
	SearchResult GetResults(SearchInfo searchInfo);
	bool CointainStopWord(wstring stopWord);
	
private:
	static Database* instance;
	Trie<size_t> searchByWord;
	Trie<size_t> searchByHashtag;
	Trie<size_t> searchByFileType;
	Trie<size_t> searchByTitle;
	map<wstring, set<size_t>> searchByExtension;
	map<size_t, set<size_t>> searchByCost;
	map<string, vector<string>> searchBySynonym;
	set<wstring> stopWords;

	void BuildSaveData();
	void BuildDataStruct();
	void LoadDataStruct();
	static vector<wstring> GetAllPath(string directory);
	static bool FileExists(string path);
	Database();
};

