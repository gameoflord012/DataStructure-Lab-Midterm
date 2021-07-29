#include "json.hpp"
#include "Database.h"
#include "Trie.h"
#include <iostream>
#include <filesystem>
#include <string>

using namespace std;
using namespace nlohmann;
namespace fs = std::filesystem;

int main()
{
	Database database = Database::GetInstance();
	vector<FileInfo> infos = database.GetResults(L"DOCKED");
}