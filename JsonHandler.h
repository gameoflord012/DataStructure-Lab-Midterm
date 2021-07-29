#pragma once
#include "json.hpp"
#include "FileInfo.h"
#include "Trie.h"

using json = nlohmann::json;

void to_json(json& j, const FileInfo& p);
void from_json(const json& j, FileInfo& p);

void to_json(json& j, const Trie<size_t>& trie);
void from_json(const json& j, Trie<size_t>& trie);