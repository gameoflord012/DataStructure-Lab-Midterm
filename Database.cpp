#include "Database.h"
#include "JsonHandler.h"
#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>

using namespace std::filesystem;
using namespace std;

Database* Database::instance;

#define WSTRING_2_STRING(x) (string(x.begin(), x.end()))
#define STRING_2_WSTRING(x) (wstring(x.begin(), x.end()))

Database::Database()
{
	if (!FileExists(DATA_BASE_PATH))
	{
		BuildSaveData();
		BuildDataStruct();
	}
	LoadDataStruct();
}

vector<wstring> Database::GetAllPath(string directory)
{
	vector<wstring> result;
	for (const auto& entry : directory_iterator(directory))
	{
		result.emplace_back(entry.path().wstring());
	}
	return result;
}

SearchResult Database::GetResults(SearchInfo searchInfo)
{
	set<size_t> result;
	switch (searchInfo.searchType)
	{
	case SearchType::word: // ==========================================================
		result = searchByWord.getInfos(searchInfo.syntax);
		break;
	case SearchType::cost: // ==========================================================
		for(auto it = searchByCost.lower_bound(searchInfo.minCost), end = searchByCost.upper_bound(searchInfo.maxCost); it != end; it++)
		{ 
			for (size_t key : it->second) result.insert(key);
		}
		break;
	case SearchType::title: // ==========================================================
		result = searchByTitle.getInfos(searchInfo.syntax);
		break;
	case SearchType::extension:	// ==========================================================
		result.insert(searchByExtension[searchInfo.syntax].begin(), searchByExtension[searchInfo.syntax].end());
		break;
	case SearchType::hashTag: // ==========================================================
		result = searchByHashtag.getInfos(searchInfo.syntax);
		break;
	case SearchType::synonyms: // ==========================================================
	{
		SearchResult finalResult = SearchResult();
		for (string synonym : searchBySynonym[WSTRING_2_STRING(searchInfo.syntax)])
		{
			finalResult = finalResult.OR(GetResults(SearchInfo(STRING_2_WSTRING(synonym), SearchType::word)));
			cout << synonym << endl;
		}
		return finalResult;
	}		
	default:
		break;
	}

	return SearchResult(result);
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

void Database::BuildDataStruct()
{
	Trie<size_t> wordSearching;
	Trie<size_t> hashtagSearching;
	Trie<size_t> titleSearching;
	map<wstring, set<size_t>> extensionSearching;
	map<size_t, set<size_t>> costSearching;
	map<string, vector<string>> synonymSearching;

	for (wstring path : GetAllPath(SAVE_DATA_DIR))
	{
		ifstream file(path);

		json j; file >> j; FileInfo info = j.get<FileInfo>();

		for (wstring s : info.contentWords) { wordSearching   .insert(s, info.key); }
		for (wstring s : info.hashtags)     { hashtagSearching.insert(s, info.key); }
		for (wstring s : info.titleWords)   { 
			titleSearching  .insert(s, info.key); 
		}
		for (size_t cost : info.costs) { costSearching[cost]  .insert(info.key); }
		extensionSearching[info.extension].insert(info.key);

		file.close();
	}	

	ifstream fileIn(SYNONYM_DATA_PATH);

	while (!fileIn.eof())
	{
		json j; 
		try
		{
			fileIn >> j;
		}
		catch(...)
		{
			break;
		}

		string word = j.at("word");
		vector<string> synonyms = j.at("synonyms");
		for (string synonyms : synonyms) synonymSearching[word].push_back(synonyms);
	}

	fileIn.close();

	ofstream fileOut(DATA_BASE_PATH);

	fileOut << json{
		{"searchByWord", wordSearching},
		{"searchByHashtag", hashtagSearching},
		{"searchByExtension", extensionSearching},
		{"searchByTitle", titleSearching},
		{"searchByCost", costSearching},
		{"searchBySynonym", synonymSearching}
	};

	fileOut.close();
}

void Database::LoadDataStruct()
{
	ifstream file(DATA_BASE_PATH);
	json j; file >> j;

	searchByWord = j.at("searchByWord");
	searchByHashtag = j.at("searchByHashtag");
	searchByTitle = j.at("searchByTitle");
	searchByExtension = j.at("searchByExtension").get<map<wstring, set<size_t>>>();
	searchByCost = j.at("searchByCost").get<map<size_t, set<size_t>>>();
	searchBySynonym = j.at("searchBySynonym").get<map<string, vector<string>>>();

	file.close();
}
