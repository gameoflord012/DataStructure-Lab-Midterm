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
    FileInfo info = database.GetFileInfo(size_t(10771591575676645745));

    wcout << info.title << endl;
    wcout << info.content << endl;
}