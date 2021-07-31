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
	vector<wstring> hashtags;
	vector<size_t> costs;

	FileInfo(wstring filePath);
	FileInfo();

	static string GetPath(size_t key);
	static FileInfo GetFileInfo(size_t key);

private:
	wstring CombineWords(std::vector<std::wstring> hashtagsWithTag);
	wstring GetContent(std::ifstream& fileStream);
	vector<wstring> GetWords(wstring content, wstring regexSyntax);
	vector<size_t> GetNumbers(wstring content);
	size_t GetKey(wstring stringToHash);
};

