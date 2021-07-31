#include "SearchInfo.h"

SearchInfo::SearchInfo(wstring syntax)
{
	this->searchType = SearchType::word;
	this->syntax = syntax;
}

SearchInfo::SearchInfo(wstring syntax, SearchType searchType)
{
	this->searchType = searchType;
	this->syntax = syntax;
}

SearchInfo::SearchInfo(int minCost, int maxCost)
{
	this->searchType = SearchType::cost;
	this->minCost = minCost;
	this->maxCost = maxCost;
}

SearchInfo::SearchInfo(int cost)
{
	this->searchType = SearchType::cost;
	this->minCost = cost;
	this->maxCost = cost;
}
