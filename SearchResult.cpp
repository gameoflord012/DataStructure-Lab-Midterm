#include "SearchResult.h"

SearchResult::SearchResult(vector<FileInfo> infos)
{
	this->infos = infos;
	for (FileInfo info : infos)
	{
		keys.insert(info.key);
	}
}

SearchResult SearchResult::AND(SearchResult other)
{
	vector<FileInfo> result;
	for (FileInfo info : infos)
	{
		if (other.keys.count(info.key))
		{
			result.push_back(info);
		}
	}

	return SearchResult(result);
}

SearchResult SearchResult::OR(SearchResult other)
{
	vector<FileInfo> result = other.infos;

	for (FileInfo info : infos)
	{
		if (!other.keys.count(info.key))
		{
			result.push_back(info);
		}
	}

	return SearchResult(result);
}

SearchResult SearchResult::EXCLUDE(SearchResult other)
{
	vector<FileInfo> result;

	for (FileInfo info : infos)
	{
		if (!other.keys.count(info.key))
		{
			result.push_back(info);
		}
	}

	return SearchResult(result);
}


