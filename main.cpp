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
	FileInfo info = database.GetFileInfo(size_t(17525330523994444657));

	Trie<int> trie;
	trie.insert("salalalla", 2);
	trie.insert("salalalla", 3);

	trie.insert("salalalla2", 4);
	trie.insert("salalalla2", 5);

	vector<int> infos = trie.getInfos("salalalla2");
	for (int info : infos)
	{
		cout << info << endl;
	}

	/*wcout << info.key << endl;

	for (wstring word : info.contentWords)
	{
		wcout << word << endl;
	}*/
}