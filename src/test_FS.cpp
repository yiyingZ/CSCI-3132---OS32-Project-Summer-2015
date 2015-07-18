#include <iostream>
#include "FileSystem.h"
#include <string>

using namespace std;

int main() {
    //build single instance of FileSystem for testing
    FileSystem& fs = FileSystem::getInstance();
    //create blah file
    std::vector<bool> perms{1,0,0};
    std::string b="blah";std::string bb="blah blah";
    fs.fcreate(b,bb,perms);
    //fs.dcreate("blah");
    return 0;
}