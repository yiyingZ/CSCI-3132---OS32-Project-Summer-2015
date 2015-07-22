//
// Created by Aaron Windsor on 20150715
//
#include <iostream>
#include "FileSystem.h"
#include <assert.h>
#include <algorithm>

using namespace std;

int main() {
    //First test regular File class
    //Here is a regular file named reg with contents blah and 111 perms
    cout<<"###############Test File Class: FileType = 0 (Reg)###############";
    cout<<endl;
    File *regFile = new File("reg","blah",std::vector<bool>{1,1,1});
    cout<<"Test File Class getFileName: ";
    assert("reg"==regFile->getFileName());
    cout<<"1"<<endl;
    cout<<"Test File Class setFileName: ";
    regFile->setFileName("newReg");
    assert("newReg"==regFile->getFileName());
    cout<<"1"<<endl;
    cout<<"Test File Class getFileType: ";
    assert(0==regFile->getFileType());
    cout<<"1"<<endl;
    cout<<"Test File Class setFileType: ";
    regFile->setFileType(1);
    assert(1==regFile->getFileType());
    cout<<"1"<<endl;
    regFile->setFileType(0);
    cout<<"Test File Class getContents: ";
    assert("blah"==regFile->getContents());
    cout<<"1"<<endl;
    cout<<"Test File Class setContents: ";
    regFile->setContents("blah blah");
    assert("blah blah"==regFile->getContents());
    cout<<"1"<<endl;
    std::vector<bool> foo={1,1,1};
    cout<<"Test File Class getPermissions: ";
    assert(foo==regFile->getPermissions());
    cout<<"1"<<endl;
    cout<<"Test File Class setPermissions: ";
    regFile->setPermissions(std::vector<bool>{0,1,1});
    std::vector<bool> bar={0,1,1};
    assert(bar==regFile->getPermissions());cout<<"1"<<endl;
    cout<<"###############Test File Class: FileType = 1 (Dir)###############";
    cout<<endl;
    std::vector<File*> subDir;
    File *dirFile= new File("dirF",subDir,foo);
    cout<<"Test File Class addDirElement: ";
    assert(1==dirFile->addDirElement(regFile));
    cout<<"1"<<endl;
    cout<<"Test File Class getDir: ";
    assert(1==dirFile->getDir().size());
    cout<<"1"<<endl;
    cout<<"Test File Class getDirElement: ";
    File *gdeTest;
    gdeTest = dirFile->getDirElement(regFile->getFileName());
    assert(gdeTest==regFile);
    cout<<"1"<<endl;
    cout<<"Test File Class deleteDirElement: ";
    dirFile->deleteDirElement(regFile->getFileName());
    assert(0==dirFile->getDir().size());
    cout<<"1"<<endl;

    //Second Test FileSystem
    cout<<"####################Test FileSystem Class####################";
    cout<<endl;
    //build single instance of FileSystem for testing (FileSystem follows
    //Singleton design pattern
    FileSystem& fs = FileSystem::getInstance();
    cout<<"Test FileSystem Class fcreate: ";
    std::vector<bool> perms{1,0,0};
    std::string b="blah";std::string bb="blah blah";
    assert(1==fs.fcreate(b,bb,perms));
    cout<<1<<endl;
    cout<<"Test FileSystem Class lisitems: ";
    assert("blah "==fs.listitems());
    cout<<1<<endl;
    cout<<"Test FileSystem Class getCurrDir: ";
    assert("root"==fs.getCurrDir()->getFileName());
    cout<<1<<endl;
    cout<<"Test FileSystem Class fLocate: ";
    assert(fs.fLocate("blah"));
    cout<<1<<endl;
    cout<<"Test FileSystem Class fread: ";
    assert("blah blah" == fs.fread("blah")->getContents());
    cout<<1<<endl;
    cout<<"Test FileSystem Class fwrite: ";
    assert(fs.fwrite("blah"));
    cout<<1<<endl;
    cout<<"Test FileSystem Class dcreate: ";
    int i = fs.dcreate("blahDir");
    assert(fs.fLocate("blahDir")->getFileName()=="blahDir");
    cout<<1<<endl;
    cout<<"Test FileSystem Class renameFile: ";
    assert(1==fs.renameFile("blah","blah2"));
    cout<<1<<endl;
    cout<<"Test FileSystem Class cpher: ";
    std::vector<bool> cpherTest{0,0,0};
    assert(1==fs.chper("blah2",cpherTest));
    cout<<1<<endl;
    cout<<"Test FileSystem Class fdelete: ";
    assert(1==fs.fdelete("blah2"));

    cout<<1<<endl;

    return 0;
}