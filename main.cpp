#include "Database.h"
#include "Trie.h"
#include "JsonHandler.h"
#include "SearchInfo.h"

#include "engine.h"
//#include "console.h"  //not working

using namespace std;
using namespace nlohmann;
namespace fs = std::filesystem;


int main()
{
	Database data = Database::GetInstance();
	vector<int> pos;
	pos.push_back(1);
	pos.push_back(2);

	while (1)
	{
		SearchResult result;
		cout << "0. Exit" << endl << "1. Input query from keyboard" << endl << "2. Clear history" << endl << "OPTION:   ";
		int choice; cin >> choice; cin.ignore();
		if (!choice) break;
		if (choice == 2)
		{
			clearHistory();
			cout << "History has been cleared.................." << endl << endl;
			continue;
		}
		string query;
		cout << "Query:"; getline(cin, query);
		cout << "0. Search" << endl << "1. Show history suggestion" << endl << "OPTION:   ";
		cin >> choice; cin.ignore();
		if (choice) {
			vector<string> res;
			History(res, query);
			cin >> choice; cin.ignore();
			if (choice > res.size() - 1) {
				cout << "Invalid" << endl; choice = 0;
			}
			query = res[choice];
		}
		else
		{
			ofstream output; output.open("history.txt", ios::app);
			output << query << endl;
			output.close();
		}

		searchResults(query, result, data); //SEARCH DATA

		for (FileInfo info : result.GetInfos())
		{
			printf("------------------------------------------------------------\n");
			cout << "OUTPUT: " << endl;
			//TextColor(10);
			wcout << info.title << "." << info.extension << endl;
			//TextColor(7);
			cout << "Score: " << "nan" << endl;
			//OutputResult(L"Search Engine-Data\\Search Engine-Data\\" + info.title + L"." + info.extension, pos);
		}
		printf("==============================================================\n\n");
	}
	return 0;
}

/*SearchResult result =
	data.GetResults(SearchInfo(L"Every")).AND(
	data.GetResults(SearchInfo(L"IN"))).OR(
	data.GetResults(SearchInfo(L"headline", SearchType::hashTag)).OR(
	data.GetResults(SearchInfo(L"txt", SearchType::extension)).OR(
	data.GetResults(SearchInfo(L"testtitle", SearchType::title)).OR(
	data.GetResults(SearchInfo(1, 1000000))
))));*/