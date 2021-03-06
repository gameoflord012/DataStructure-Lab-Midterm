#pragma once
#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;

template<typename TInfo>
class Trie
{
public:	
	vector<map<int, int>> tree;
	map<int, set<TInfo>> infos;
	Trie();

	int size();
	void insert(wstring s, TInfo info);
	set<TInfo> getInfos(wstring s);
};

template<typename TInfo>
inline int Trie<TInfo>::size()
{
	return (int)tree.size();
}

template<typename TInfo>
inline Trie<TInfo>::Trie()
{	
	tree.emplace_back(map<int, int>());
}

template<typename TInfo>
inline void Trie<TInfo>::insert(wstring s, TInfo info)
{
	int currentNode = 0;
	for (int i = 0; i < s.size(); i++)
	{
		char c = tolower(s[i]);

		if (tree[currentNode].count(c) == 0)
		{
			tree[currentNode][c] = size();
			tree.emplace_back(map<int, int>());
		}

		currentNode = tree[currentNode][c];
	}

	infos[currentNode].insert(info);
}

template<typename TInfo>
inline set<TInfo> Trie<TInfo>::getInfos(wstring s)
{
	int currentNode = 0;
	for (int i = 0; i < s.size(); i++)
	{
		wchar_t c = tolower(s[i]);

		if (tree[currentNode].count(c) == 0)
		{
			return set<TInfo>();
		}

		currentNode = tree[currentNode][c];
	}

	return infos[currentNode];	
}
