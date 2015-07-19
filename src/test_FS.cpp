#include <iostream>
#include "FileSystem.h"
#include <assert.h>
#include <stdio.h>
#include <string>


using namespace std;

int main() {
    //######################Test File Class##############################
    //First test File class
    //Here is a regular file named reg with contents blah and 111 perms
    File *regFile = new File("reg","blah",std::vector<bool>{1,1,1});
    cout<<"Test getFileName: ";
    assert("reg"==regFile->getFileName());
    cout<<"1"<<endl;
    cout<<"Test setFileName: ";
    regFile->setFileName("newReg");
    assert("newReg"==regFile->getFileName());
    cout<<"1"<<endl;

    //Here is a dir file named myDir currently with no nested files or dirs
    //and 111 permissions
    //File(std::string fn, std::vector<File *> d,std::vector<bool> p);
    //build single instance of FileSystem for testing
    FileSystem& fs = FileSystem::getInstance();
    //create blah file
    std::vector<bool> perms{1,0,0};
    std::string b="blah";std::string bb="blah blah";
    fs.fcreate(b,bb,perms);
    //fs.dcreate("blah");
    return 0;
}