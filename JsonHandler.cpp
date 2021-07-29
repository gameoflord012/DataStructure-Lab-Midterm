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
        {"titleWords", fileInfo.title}
    };
}

void from_json(const json& j, FileInfo& fileInfo) {
    j.at("key").get_to(fileInfo.key);
    j.at("fileDataPath").get_to(fileInfo.fileDataPath);
    j.at("extension").get_to(fileInfo.extension);
    j.at("title").get_to(fileInfo.title);
    j.at("content").get_to(fileInfo.content);
    j.at("contentWords").get_to(fileInfo.contentWords);
    j.at("titleWords").get_to(fileInfo.title);
}
