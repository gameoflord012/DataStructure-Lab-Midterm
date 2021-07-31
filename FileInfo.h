#pragma once
#include <string>
#include <vector>

using namespace std;

class FileInfo
{
public:

	size_t key;
	string fileDataPath;
	wstring extension;
	wstring title;
	wstring content;
	vector<wstring> titleWords;
	vector<wstring> contentWords;
	vector<wstring> hashTags;

	FileInfo(wstring filePath);
	FileInfo();

	static string GetPath(size_t key);
	static FileInfo GetFileInfo(size_t key);

private:
	wstring GetContent(std::ifstream& fileStream);
	vector<wstring> GetWords(wstring content, wstring regexSyntax);
	size_t GetKey(wstring stringToHash);
};

