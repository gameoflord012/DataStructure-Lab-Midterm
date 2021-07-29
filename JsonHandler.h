#pragma once
#include "json.hpp"
#include "FileInfo.h"

using json = nlohmann::json;

void to_json(json& j, const FileInfo& p);
void from_json(const json& j, FileInfo& p);