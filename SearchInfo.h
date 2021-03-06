#pragma once
#include <string>

using namespace std;


enum class SearchType {
	word,
	extension,
	title,
	synonyms,
	cost,
	hashTag
};

class SearchInfo
{
public:
	SearchType searchType;
	wstring syntax;

	int maxCost;
	int minCost;

	SearchInfo(wstring syntax);
	SearchInfo(wstring syntax, SearchType searchType);
	SearchInfo(int minCost, int maxCost);
	SearchInfo(int cost);
};

