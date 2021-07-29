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

	FileInfo(wstring filePath);

private:
	wstring GetContent(std::ifstream& fileStream);
	vector<wstring> GetWords(wstring content);
	size_t GetKey(wstring stringToHash);
};

