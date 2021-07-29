#include "JsonHandler.h"
#include "FileInfo.h"

void to_json(json& j, const FileInfo& p) {
    j = json{ 
        {"extension", p.extension}, 
        {"title", p.title}, 
        {"content", p.content},
        {"contentWords", p.contentWords},
        {"titleWords", p.title}
    };
}

void from_json(const json& j, FileInfo& p) {
    j.at("extention").get_to(p.extension);
    j.at("title").get_to(p.title);
    j.at("content").get_to(p.content);
    j.at("contentWords").get_to(p.contentWords);
    j.at("titleWords").get_to(p.title);
}
