#include <winalleg.h>
#include <windows.h>

void load_dosbox(string newPath, string newArguments){
    ShellExecute(NULL, "open", newPath.c_str(), newArguments.c_str(), NULL, SW_SHOWDEFAULT);
}
