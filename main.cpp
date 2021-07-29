#include "Database.h"
#include "Trie.h"
#include "JsonHandler.h"
#include <iostream>
#include <filesystem>
#include <string>

using namespace std;
using namespace nlohmann;
namespace fs = std::filesystem;


int main()
{
	Database data = Database::GetInstance();	
	vector<FileInfo> infos = data.GetResults(L"Every");	
}