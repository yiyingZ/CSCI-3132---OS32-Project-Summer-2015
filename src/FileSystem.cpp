//
// Created by Aaron Windsor on 20150715
//
#include <string>
#include <sstream>
#include "FileSystem.h"
#include 'File.h"

/*
 * Constructor
 */
FileSystem::FileSystem(std::string n) {
    fs=n;
    //start user at rootDir
    currDir=rootDir;
}
/*
 * function: fcreate
 * function builds a new file with these params, add its to current
 * Directory, and returns a pointer to the file
 */
File *FileSystem::fcreate(std::string fn, std::string c, std::vector<bool> p) {
    File *f;
    f = new File(fn,c,p);
    bool temp = currDir->addDirElement(f);
    if(temp==1)
        return f;
    else
        return nullptr;
}
/*
 * function: fLocate
 * recursively search directories starting with root for file with
 * name fn. If it exists return pointer to it
 */
File *FileSystem::fLocate(std::string fn) {
    File *temp = rootDir;
    return fLocateHelper(rootDir,fn);
}
/*
 * function: fLocateHelper
 * performs recursive DFS on file pointer sent in
 */
File * FileSystem::fLocateHelper(File *f, std::string fn) {
    if (f->getFileType() == 0) {
        if (f->getFileName() == fn)
            return f;
    }
    if(f->getFileType()==1){
        for(int j=0;j<f->getDir().size();j++){
            std::vector<File*> temp1 = f->getDir();
            File * temp2 = temp1[j];
            fLocateHelper(temp2,fn);
        }
    }
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
 * needs to check that File has fileType 1 before it does anything
 * and if so build a new file (with fileType 1) and add it to currDir's
 * vector of File pointers
 */
void FileSystem::dcreate(std::string dName) {
    std::vector<File *> blank;
    std::vector<bool> perms{1,1,1};
    File *newChild = new File(dName,blank,perms);
    currDir->addDirElement(newChild);
}

/*
 * function: currdir
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
    File *temp = fLocate(n);
    File *parent = getCurrDir();
    parent->deleteDirElement(temp);

}

/*
 * function: renameFile
 *  must reset currDir=rootDir after dfs
 */
bool FileSystem::renameFile(std::string n, std::string newN) {
    return 0;
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


bool FileSystem::chper(std::string fn, int p) {
    return false;
}

