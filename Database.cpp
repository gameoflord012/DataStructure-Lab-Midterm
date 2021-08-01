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
	vector<size_t> result;
	switch (searchInfo.searchType)
	{
	case SearchType::word: // ==========================================================
		result = searchByWord.getInfos(searchInfo.syntax);
		break;
	case SearchType::cost: // ==========================================================
		for(auto it = searchByCost.lower_bound(searchInfo.minCost), end = searchByCost.upper_bound(searchInfo.maxCost); it != end; it++)
		{ 
			for (size_t key : it->second) result.emplace_back(key);
		}
		break;
	case SearchType::title: // ==========================================================
		result = searchByTitle.getInfos(searchInfo.syntax);
		break;
	case SearchType::extension:	// ==========================================================
		result.assign(searchByExtension[searchInfo.syntax].begin(), searchByExtension[searchInfo.syntax].end());
		break;
	case SearchType::hashTag: // ==========================================================
		result = searchByHashtag.getInfos(searchInfo.syntax);
		break;
	case SearchType::synonyms: // ==========================================================
		break;
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

	for (wstring path : GetAllPath(SAVE_DATA_DIR))
	{
		ifstream file(path);

		json j; file >> j; FileInfo info = j.get<FileInfo>();

		for (wstring s : info.contentWords) { wordSearching   .insert(s, info.key); }
		for (wstring s : info.hashtags)     { hashtagSearching.insert(s, info.key); }
		for (wstring s : info.titleWords)   { titleSearching  .insert(s, info.key); }
		extensionSearching[info.extension].insert(info.key);
		for (size_t cost : info.costs) { costSearching[cost].insert(info.key); }

		file.close();
	}

	ofstream file(DATA_BASE_PATH);

	file << json{
		{"searchByWord", wordSearching},
		{"searchByHashtag", hashtagSearching},
		{"searchByExtension", extensionSearching},
		{"searchByTitle", titleSearching},
		{"searchByCost", costSearching}
	};

	file.close();
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

	file.close();
}
