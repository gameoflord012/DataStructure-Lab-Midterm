//#include "Database.h"
//#include "Trie.h"
//#include "JsonHandler.h"
//#include "SearchInfo.h"

#include "display.h"

using namespace std;
using namespace nlohmann;
namespace fs = std::filesystem;

int old_display(Database data);
// function display
int main()
{
	Database data = Database::GetInstance();
	display display(data);

	//old_display(data);
	return 0;
}





//-------OLD_DISPLAY---------
int old_display(Database data)
{
#pragma region Belong to Nhat
	//Database data = Database::GetInstance();

	for (;;)
	{  //options for user input
		SearchResult result;
		cout << "1. Input query from keyboard." << endl << "2. Clear history." << endl;
		cout << "0. Exit!" << endl << "OPTION > ";
		int choice; cin >> choice; cin.ignore();
		
		if (!choice) break;
		else if (choice == 2)
		{
			clearHistory();
			TextColor(10);
			cout << "History has been cleared...............!!!" << endl << endl;
			TextColor(7);
			continue;
		}
		// color of function
		string query;
		cout << "Query > "; getline(cin, query);
		cout << "0. Search." << endl << "1. History suggestion." << endl << "OPTION > ";
		cin >> choice; cin.ignore();
		if (choice) {
			vector<string> res;
			History(res, query, -1);
			cout << "\nCHOICE > \n";
			cin >> choice; cin.ignore();
			if (choice > res.size() - 1) {
				TextColor(10);
				cout << "Invalid!!!!!!!!" << endl; choice = 0;
				TextColor(7);
			}
			query = res[choice];
		}
		//save result 
		else
		{
			ofstream output; output.open("history.txt", ios::app);
			output << query << endl;
			output.close();
		}
		vector<string> tmp;
		tmp = searchResults(query, result, data); //SEARCH DATA
		for (FileInfo info : result.GetInfos())
		{
			// interface shaping and coloring
			printf("@-------------------------------------------------------------@\n");
			TextColor(11);
			wcout << L"Title: ";
			TextColor(7);
			TextColor(10);
			wcout << info.title << "." << info.extension << endl;
			TextColor(11);
			cout << "Result: " << endl;
			TextColor(7);
			OutputResult(info.content, tmp);
			printf("@-------------------------------------------------------------@\n\n");
		}
	}
	return 0;
}
