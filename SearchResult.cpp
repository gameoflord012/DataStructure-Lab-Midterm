#include "SearchResult.h"

SearchResult::SearchResult(const vector<size_t> &keys)
{
	for (size_t key : keys) this->keys.insert(key);
}

SearchResult::SearchResult(const set<size_t>& keys)
{
	for (size_t key : keys) this->keys.insert(key);
}

SearchResult SearchResult::AND(const SearchResult &other)
{
	set<size_t> result;
	for (size_t key : keys)
	{
		if (other.keys.count(key))
		{
			result.insert(key);
		}
	}

	return SearchResult(result);
}

SearchResult SearchResult::OR(const SearchResult &other)
{
	set<size_t> result = other.keys;
	result.insert(other.keys.begin(), other.keys.end());
	return SearchResult(result);
}

SearchResult SearchResult::EXCLUDE(const SearchResult &other)
{
	set<size_t> result = keys;
	for (size_t key : other.keys)
	{
		result.erase(key);
	}
	return SearchResult(result);
}

vector<FileInfo> SearchResult::GetInfos()
{
	vector<FileInfo> result;
	for (size_t key : keys) result.push_back(FileInfo::GetFileInfo(key));
	return result;
}


