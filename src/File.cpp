//
// Created by Aaron Windsor on 20150715
//
#include "File.h"

#include <string>

using namespace std;

/*
 * Constructor for file that is regular type
 * takes in fileName, assigns fileType=0, sets dir as nullptr,
 * sets contents to whatever
 * string is sent in as c, and populates permissions by
 */
File::File(std::string fn,std::string c,std::vector<bool> p){
    fileName=fn; fileType=0;contents=c;permissions=p;
    //initialize for blah reason
    dir=std::vector<File*>{};
}

/*
 * Constructor for file that is directory type
 * takes in fileName, assigns fileType=1, sets vector of files (dir's that
 * have this dir as root), sets contents null, and populates permissions by p
 */
File::File(std::string fn,std::vector<File*> d,std::vector<bool> p){
    fileName=fn;fileType=1;dir=d;contents= "";permissions=p;
}
/*
 * function: getFileName
 * simple function that returns fileName of this File
 */
const std::string &File::getFileName() {
    return fileName;
}
/*
 * function: setFileName
 * simple function that sets fileName to param f
 */
void File::setFileName(const std::string &f) {
    fileName=f;
}
/*
 * function: getFileType
 * simple function that returns fileType
 * 0=reg file, 1 = directory
 */
bool File::getFileType() {
    return fileType;
}
/*
 * function: setFileType
 * simple function that sets fileType to param f
 */
void File::setFileType(bool f) {
    fileType=f;
}
/*
 * function: getDir
 * simple function that returns vector of File's
 * representing sub directory for this directory
 * if reg file = nullptr always
 */
std::vector<File *> File::getDir() {
    return std::vector<File *>();
}
/*
 * function: addDirElement
 * add's file to end of directory vector
 * returns 1 if successful (f successfully added),
 * returns 0 o.w.
 */
bool File::addDirElement(File* f){
   dir.push_back(f);
   return 1;
}
/*
 * function: deleteDirElement
 * delete's element from dir that matches f
 * returns 1 if successful (found an f and killed it),
 * returns 0 o.w.
 */
bool File::deleteDirElement(File* f){
    bool test=false;
    if (!dir.empty()){
        for(int i=0;i<dir.size();i++){
            if(dir[i]->getFileName()==f->getFileName()){
                test=true;
                dir.erase(dir.begin()+i);
            }
        }
    }
    return test;
}
/*
 * function: getContents
 * simple function that returns file contents as string
 */
std::string &File::getContents() {
    return contents;
}
/*
 * function: setContents
 * simple function that replaces file's existing contents with c
 */
void File::setContents(const std::string &c) {
    contents=c;
}
/*
 * function: setContents
 * simple function that replaces file's existing contents with c
 */
void File::setPermissions(std::vector<bool> p) {
   permissions=p;
}
