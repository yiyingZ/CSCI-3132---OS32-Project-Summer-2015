//
// Created by Aaron Windsor on 20150715
//
#include <sstream>
#include <iostream>
#include "FileSystem.h"

/*
 * Constructor
 */
FileSystem::FileSystem() {
    //initialize root directory
    std::vector<bool> rootPerm{1,1,1};
    std::vector<File*> dir;
    rootDir = new File("root",dir,rootPerm);
    currDir=rootDir;
}
/*
 * function: fcreate
 * function builds a new file with these params, add its to current
 * Directory, and bool of whether file was successfully added or not
 * 0=no, 1=yes
 */
bool FileSystem::fcreate(std::string fn, std::string c, std::vector<bool> p) {
    File *f = new File(fn,c,p);
    return currDir->addDirElement(f);
}
/*
 * function: fLocate
 * recursively search directories starting with root for file with
 * name fn. If it exists return pointer to it
 */
File *FileSystem::fLocate(std::string fn) {
    return rootDir->getDirElement(fn);

    //int helper=0;
    //return fLocateHelper(rootDir,fn,helper);
}
/*
 * function: fread
 *  returns pointer to the File that client wants to read
 *  which then can have its contents read using getContents
 *  (implemented this way as utility group wanted to just have
 *  a pointer to play with)
 *
 */
File *FileSystem::fread(std::string fName) {
    return fLocate(fName);
}
/*
 * function: fwrite
 *  returns pointer to the File that client wants to write
 *  which then can have its contents written to using setContents
 *  (implemented this way as utility group wanted to just have
 *  a pointer to play with)
 *
 */
File *FileSystem::fwrite(std::string fName) {
    return fLocate(fName);
}
/*
 * function: dcreate
 * build a new file (with fileType 1) and add it to currDir's
 * vector of File pointers
 */
bool FileSystem::dcreate(std::string dName) {
    std::vector<File *> blank;
    std::vector<bool> perms{1,1,1};
    File *newChild = new File(dName,blank,perms);
    if(currDir->addDirElement(newChild))
        return 1;
    else
        return 0;
}

/*
 * function: getCurrDir
 * simple self explanatory function
 *
 */
File *FileSystem::getCurrDir() {
    return currDir;
}
/*
 * function: fdelete
 * removes pointer to file from Dir's vector of files
 */
bool FileSystem::fdelete(std::string n) {
    if(rootDir->deleteDirElement(n))
        return 1;
    else
        return 0;
}
/*
 * function: renameFile (self explanatory)
 */
bool FileSystem::renameFile(std::string n, std::string newN) {
    fLocate(n)->setFileName(newN);
    return 1;

}

/*
 * function: listitems
 * store contents of current directory as string and returns that
 * akin to ls utility for Linux
 *
 */
std::string FileSystem::listitems() {

    std::vector<File*> temp = currDir->getDir();
    std::stringstream outp;
    for(int i=0;i<temp.size();i++){
        outp<<temp[i]->getFileName();
        outp<<" ";
    }
    return outp.str();
}

/*
 * function: chper
 * change permissions on file fn to p and return a 1
 * if can't find file or change permissions, return 0
 */
bool FileSystem::chper(std::string fn,std::vector<bool> p) {
    File *f = fLocate(fn);
    f->setPermissions(p);
    return 1;

}

