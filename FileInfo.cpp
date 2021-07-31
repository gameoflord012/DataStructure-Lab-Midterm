#include "FileInfo.h"
#include "JsonHandler.h"
#include <fstream>
#include <filesystem>
#include <sstream>
#include <regex>

using namespace std::filesystem;
using namespace std;

FileInfo::FileInfo()
{
}

string FileInfo::GetPath(size_t key)
{
	return SAVE_DATA_DIR + to_string(key) + ".txt";
}

FileInfo FileInfo::GetFileInfo(size_t key)
{
	ifstream file(GetPath(key));
	json j;
	file >> j;
	file.close();
	return j;
}

FileInfo::FileInfo(wstring pathInfo)
{
	ifstream file(pathInfo);

	if (!file.good())
	{
		throw "Database file not found";
	}

	key = GetKey(pathInfo);
	fileDataPath = GetPath(key);
	extension = path(pathInfo).extension();
	title = path(pathInfo).filename().replace_extension();
	content = GetContent(file);
	contentWords = GetWords(content, L"[a-z]+");
	titleWords = GetWords(title, L"[a-z]+");

	file.close();
}

vector<wstring> FileInfo::GetWords(wstring content, wstring regexSyntax)
{
	wregex rg(regexSyntax);
	wsmatch sm;
	regex_match(content, sm, rg, regex_constants::match_default);

	vector<wstring> result;

	while (regex_search(content, sm, rg)) {
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