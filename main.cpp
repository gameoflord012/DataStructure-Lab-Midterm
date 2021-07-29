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
    for (auto file : database.files)
    {
        wcout << file.extension << endl;
    }
}