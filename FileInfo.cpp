#include "FileInfo.h"
#include <fstream>
#include <filesystem>
#include <sstream>
#include <regex>

using namespace std::filesystem;
using namespace std;

FileInfo::FileInfo()
{
}

FileInfo::FileInfo(wstring pathInfo)
{
	ifstream file(pathInfo);

	if (!file.good())
	{
		throw "Database file not found";
	}

	key = GetKey(pathInfo);
	fileDataPath = SAVE_DATA_DIR + to_string(key) + ".txt";
	extension = path(pathInfo).extension();
	title = path(pathInfo).filename().replace_extension();
	content = GetContent(file);
	contentWords = GetWords(content);
	titleWords = GetWords(title);

	file.close();
}

vector<wstring> FileInfo::GetWords(wstring content)
{	
	wregex wordOnly(L"[a-z]+");
	wsmatch sm;	
	regex_match(content, sm, wordOnly, regex_constants::match_default);

	vector<wstring> result;

	while (regex_search(content, sm, wordOnly)) {
		for (auto x : sm)
		{
			result.push_back(x);
		}
		content = sm.suffix().str();
	}

	return result;
}

wstring FileInfo::GetContent(std::ifstream& fileStream)
{
	stringstream stream;
	stream << fileStream.rdbuf();
	string str = stream.str();
	return wstring(str.begin(), str.end());	
}

size_t FileInfo::GetKey(wstring stringToHash)
{
	std::hash<std::wstring> string_hash;
	return string_hash(stringToHash);
}
