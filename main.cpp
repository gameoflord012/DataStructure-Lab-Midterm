#include "Database.h"
#include "Trie.h"
#include "JsonHandler.h"
#include "SearchInfo.h"
#include <iostream>
#include <filesystem>
#include <string>

using namespace std;
using namespace nlohmann;
namespace fs = std::filesystem;


int main()
{
	Database data = Database::GetInstance();	
	SearchResult result = 
		data.GetResults(SearchInfo(L"Every")).AND(
		data.GetResults(SearchInfo(L"IN"))).OR(
		data.GetResults(SearchInfo(L"headline", SearchType::hashTag)).OR(
		data.GetResults(SearchInfo(L"txt", SearchType::extension))
	));
	

	for (FileInfo info : result.GetInfos())
	{
		wcout << info.title << " " << info.extension << endl;
	}
}