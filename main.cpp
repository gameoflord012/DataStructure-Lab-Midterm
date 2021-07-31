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
	SearchResult result = data.GetResults(L"Every").AND(data.GetResults(L"IN"));
	

	for (FileInfo info : result.infos)
	{
		wcout << info.title << " " << info.extension << endl;
	}
}