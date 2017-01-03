#include <cstdlib>

void load_dosbox(std::string newPath, std::string newArguments){

    std::string command = "dosbox "+ newArguments;
    //command = "dosbox ";
    std::system(command.c_str());
}

