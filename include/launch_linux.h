#include <cstdlib>

void load_dosbox(std::string newDosboxPath, std::string newKeenPath, std::string newKeenExecutable, std::string newArguments){

    std::string arguments = "./"+newKeenPath+"/"+newKeenExecutable+" "+newArguments;
    std::string command = "dosbox "+ arguments;
    //command = "dosbox ";
    std::system(command.c_str());
}

