#include "SearchInfo.h"

SearchInfo::SearchInfo(wstring syntax)
{
	this->searchType = SearchType::word;
	this->syntax = syntax;
}
// search information string
SearchInfo::SearchInfo(wstring syntax, SearchType searchType)
{
	this->searchType = searchType;
	this->syntax = syntax;
}
// search information cost
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
