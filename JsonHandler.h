#pragma once
#include "json.hpp"
#include "FileInfo.h"
#include "Database.h"

using json = nlohmann::json;

void to_json(json& j, const FileInfo& p);
void from_json(const json& j, FileInfo& p);

void to_json(json& j, const Database& p);
void from_json(const json& j, Database& p);