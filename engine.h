#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<algorithm>

#include "Database.h"
#include "Trie.h"
#include "JsonHandler.h"
#include "SearchInfo.h"

//#include "console.h"

using namespace std;

//-----------------------------------
bool searchStopWord(string tmp, Database _data);
void searchData(vector<string>& data, SearchResult& result, Database _data);
vector<string> searchResults(string query, SearchResult& results, Database database);

bool getRange(string tmp, int& num1, int& num2);

//---------HISTORY-------------------------
void History(vector<string>& res, string query);
void clearHistory();

//---------OPTIONs---------------
bool is_accept(char& key);
bool is_Number(char key);
bool is_Word(char key);
string SenFilter(string sen);
void OutputResult(wstring filename, vector<int> pos);
bool checkOperator(string query);
int WordinSen(string sen);