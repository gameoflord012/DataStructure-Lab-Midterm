#include "json.hpp"
#include "Database.h"
#include <iostream>
#include <filesystem>
#include <string>

using namespace std;
using namespace nlohmann;
namespace fs = std::filesystem;

int main()
{   
    Database database = Database::GetInstance();
    FileInfo info = database.GetFileInfo(size_t(17525330523994444657));

    wcout << info.key << endl;

    for (wstring word : info.contentWords)
    {
        wcout << word << endl;
    }
}