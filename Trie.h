#pragma once
#include <vector>
#include <string>
#include <map>

using namespace std;

template<typename TInfo>
class Trie
{
public:	
	vector<vector<int>> tree;
	map<int, vector<TInfo>> infos;
	Trie();

	int size();
	void insert(string s, TInfo info);
	vector<TInfo> getInfos(string s);
};

template<typename TInfo>
inline int Trie<TInfo>::size()
{
	return tree.size();
}

template<typename TInfo>
inline Trie<TInfo>::Trie()
{	
	tree.push_back(vector<int>(1024, -1));
}

template<typename TInfo>
inline void Trie<TInfo>::insert(string s, TInfo info)
{
	int currentNode = 0;
	for (int i = 0; i < s.size(); i++)
	{
		char c = tolower(s[i]);

		if (tree[currentNode][c] == -1)
		{
			tree[currentNode][c] = size();
			tree.push_back(vector<int>(1024, -1));
		}

		currentNode = tree[currentNode][s[i]];
	}

	infos[currentNode].push_back(info);
}

template<typename TInfo>
inline vector<TInfo> Trie<TInfo>::getInfos(string s)
{
	int currentNode = 0;
	for (int i = 0; i < s.size(); i++)
	{
		char c = tolower(s[i]);

		if (tree[currentNode][c] == -1)
		{
			return vector<TInfo>();
		}

		currentNode = tree[currentNode][s[i]];
	}

	return infos[currentNode];
}
