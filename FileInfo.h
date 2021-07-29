#pragma once
#include <string>
#include <vector>
using namespace std;

class FileInfo
{
public:
	wstring extension;
	wstring title;
	wstring content;
	vector<wstring> words;

	FileInfo(wstring filePath);
};

