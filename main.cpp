#include "json.hpp"
#include <iostream>
#include <filesystem>
#include <string>


using namespace std;
using namespace nlohmann;
namespace fs = std::filesystem;

int main()
{   
    cout << DATA_DIR << endl;
    string path = DATA_DIR;
    for (const auto& entry : fs::directory_iterator(path))
        std::cout << entry.path() << std::endl;
}