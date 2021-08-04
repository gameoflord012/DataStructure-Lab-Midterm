#include "JsonHandler.h"
#include "FileInfo.h"
#include "Database.h"
#include <iostream>

void to_json(json& j, const FileInfo& fileInfo) {
    j = json{ 
        {"key", fileInfo.key},
        {"fileDataPath", fileInfo.fileDataPath},
        {"extension", fileInfo.extension},
        {"title", fileInfo.title}, 
        {"content", fileInfo.content},
        {"contentWords", fileInfo.contentWords},
        {"titleWords", fileInfo.titleWords},
        {"hashtags", fileInfo.hashtags},
        {"costs", fileInfo.costs}
    };
}

void from_json(const json& j, FileInfo& fileInfo) {
    j.at("key").get_to(fileInfo.key);
    j.at("fileDataPath").get_to(fileInfo.fileDataPath);
    j.at("extension").get_to(fileInfo.extension);
    j.at("title").get_to(fileInfo.title);
    j.at("content").get_to(fileInfo.content);
    j.at("contentWords").get_to(fileInfo.contentWords);
    j.at("titleWords").get_to(fileInfo.titleWords);
    j.at("hashtags").get_to(fileInfo.hashtags);
    j.at("costs").get_to(fileInfo.costs);
}

void to_json(json& j, const Trie<size_t>& trie)
{
    j = json{
        {"tree", trie.tree},
        {"infos", trie.infos}
    };
}

void from_json(const json& j, Trie<size_t>& trie) {
    j.at("tree").get_to(trie.tree);
    j.at("infos").get_to(trie.infos);
}

void to_json(json& j, const map<size_t, set<size_t>>& myMap)
{
    for (auto& [key, value] : myMap)
    {
        j.push_back({ to_string(key), value });
    }
}

void from_json(const json& j, map<size_t, set<size_t>>& myMap)
{
    for (auto it = j.begin(); it != j.end(); ++it)
    {
        myMap[stoull(it.key())] = it.value().get<set<size_t>>();
    }
}
