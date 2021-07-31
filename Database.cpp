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
		result.push_back(entry.path().wstring());
	}
	return result;
}

SearchResult Database::GetResults(SearchInfo searchInfo)
{
	vector<FileInfo> result;
	switch (searchInfo.searchType)
	{
	case SearchType::word:
		for (size_t key : searchByWord.getInfos(searchInfo.syntax))
		{ result.push_back(FileInfo::GetFileInfo(key)); }
		break;
	case SearchType::cost:
		break;
	case SearchType::title:
		break;
	case SearchType::extension:
		break;
	case SearchType::hashTag:
		for (size_t key : searchByHashtag.getInfos(searchInfo.syntax))
		{ result.push_back(FileInfo::GetFileInfo(key)); }
		break;
	case SearchType::synonyms:
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
	map<wstring, size_t> extensionSearching;

	for (wstring path : GetAllPath(SAVE_DATA_DIR))
	{
		ifstream file(path);

		json j; file >> j; FileInfo info = j.get<FileInfo>();

		for (wstring s : info.contentWords) { wordSearching.insert(s, info.key); }
		for (wstring s : info.hashtags) { hashtagSearching.insert(s, info.key); }

		file.close();
	}

	ofstream file(DATA_BASE_PATH);

	file << json{ 
		{"searchByWord", wordSearching},
		{"searchByHashtag", hashtagSearching},
		{"searchByExtension", extensionSearching}
	};

	file.close();
}

void Database::LoadDataStruct()
{
	ifstream file(DATA_BASE_PATH);
	json j; file >> j;

	searchByWord = j.at("searchByWord");
	searchByHashtag = j.at("searchByHashtag");
	searchByExtension = j.at("searchByExtension").get<map<wstring, size_t>>();

	file.close();
}
