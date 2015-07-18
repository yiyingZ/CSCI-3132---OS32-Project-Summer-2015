//
// Created by Aaron Windsor on 20150715
//
#include <string>
#include "FileSystem.h"
#include 'File.h"


/*
 * Constructor
 */
FileSystem::FileSystem(string n) {
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
    currDir.addDirElement(f);
    return f;
}




/*
 * function: fLocate
 * recursively search directories starting with root for file with
 * name fn. If it exists return pointer to it
 */
File *FileSystem::fLocate(std::string fn) {
    File *temp = rootDir;
    return fLocateHelper(rootDir);
}

File* fLocateHelper(File *f){
    if(f->getFileName())
    return f;
}

/*
 * function: fread
 *  needs to search directories starting at root
 *  for File with name fName, and return a pointer to that File
 *  if it exists, return a void pointer o.w.
 *
 */
File *FileSystem::fread(std::string fName) {
    currDir
    return nullptr;
}

/*
 * function: fwrite
 *
 */
File *FileSystem::fwrite(std::string fName) {
    return nullptr;
}

/*
 * function: dcreate
 * needs to check that File has fileType 1 before it does anything
 * and if so build a new file (with fileType 1) and add it to currDir's
 * vector of File pointers
 */
File *FileSystem::dcreate(std::string dName) {
    return nullptr;
}

/*
 * function: currdir
 *
 */
File *FileSystem::currdir() {
    return currDir;
}

/*
 * function: fdelete
 * must remove pointer to file from Dir's vector of files
 */
bool FileSystem::fdelete(std::string n) {
    return 0;
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
 *
 */
std::string FileSystem::listitems() {

    File* temp = currDir->getDir();

}


bool FileSystem::chper(std::string fn, int p) {
    return false;
}

std::string FileSystem::getDirContents() {
    return std::basic_string < char, char_traits<_CharT>, allocator < _CharT >> ();
}
