#include <vector>
#include "FileInfo.h"
#include <set>

using namespace std;

#pragma once
class SearchResult
{
public:
	SearchResult();
	SearchResult(const vector<size_t> &infos);
	SearchResult(const set<size_t> &infos);
	SearchResult AND(const SearchResult &other);
	SearchResult OR(const SearchResult &other);
	SearchResult EXCLUDE(const SearchResult &other);
	vector<FileInfo> GetInfos();

private:
	set<size_t> keys;
};

