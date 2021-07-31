#include <vector>
#include "FileInfo.h"
#include <set>

using namespace std;

#pragma once
class SearchResult
{
public:
	vector<FileInfo> infos;
	SearchResult(vector<FileInfo> infos);
	SearchResult AND(SearchResult other);
	SearchResult OR(SearchResult other);
	SearchResult EXCLUDE(SearchResult other);

private:
	set<size_t> keys;
};

