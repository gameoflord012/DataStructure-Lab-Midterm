#include "json.hpp"
#include "Database.h"
#include "FileInfo.h"

using json = nlohmann::json;

namespace ns {
    void to_json(json& j, const FileInfo& p) {
        j = json{ 
            {"extension", p.extension}, 
            {"title", p.title}, 
            {"content", p.content},
            {"words", p.words}
        };
    }

    void from_json(const json& j, FileInfo& p) {
        j.at("extention").get_to(p.extension);
        j.at("title").get_to(p.title);
        j.at("content").get_to(p.content);
        j.at("words").get_to(p.words);
    }
}