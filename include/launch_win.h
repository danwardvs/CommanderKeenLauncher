#include <winalleg.h>
#include <windows.h>
#include <string>

void load_dosbox(std::string newDosboxPath, std::string newKeenPath, std::string newKeenExecutable, std::string newArguments){

    std::string arguments=".\\" + newKeenPath + "\\" + newKeenExecutable + " " + newArguments;
    std::cout<<arguments;
    ShellExecute(NULL, "open", newDosboxPath.c_str(), arguments.c_str(), NULL, SW_SHOWDEFAULT);
}
