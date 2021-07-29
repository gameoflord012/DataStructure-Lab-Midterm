#include "FileInfo.h"
#include <fstream>
#include <filesystem>

using namespace std::filesystem;
using namespace std;

FileInfo::FileInfo(wstring filePath)
{
	ifstream file(filePath);

	if (!file.good())
	{
		throw "Database file not found";
	}

	extension = path(filePath).extension().wstring();
	file.close();
}