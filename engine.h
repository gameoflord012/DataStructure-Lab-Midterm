#pragma region Belong to Nhat

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<algorithm>

#include "console.h" 

#include "Database.h"
#include "Trie.h"
#include "JsonHandler.h"
#include "SearchInfo.h"

using namespace std;

//--------------ENGINE---------------
// search and cout result
void searchData(vector<string>& data, SearchResult& result, Database _data);
vector<string> searchResults(string query, SearchResult& results, Database database);

bool getRange(string tmp, int& num1, int& num2);

//---------HISTORY-------------------------
// print searching history ...
int History(vector<string>& res, string query, int choice);
void clearHistory();

//---------OPTIONs---------------
// 1- query
// 2- history
//3 -clean screen
// exits
bool is_accept(char& key);
bool is_Number(char key);
bool is_Word(char key);
string SentenceFilter(string sen);
void OutputResult(wstring filename, vector<string> word);