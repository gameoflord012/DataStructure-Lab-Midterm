#pragma once
#include <string>

using namespace std;

 

class SearchInfo
{
public:
	enum class SearchType {
		word,
		extension,
		title,
		synonyms,
		cost,
		hashTag
	};

	SearchType searchType;
	wstring syntax;

	int maxCost;
	int minCost;

	SearchInfo(wstring syntax, SearchType searchType);
	SearchInfo(int minCost, int maxCost);
	SearchInfo(int cost);
};

