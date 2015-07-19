//
// Created by Aaron Windsor on 20150715
//

#ifndef CSCI3132GP_FILESYSTEM_H
#define CSCI3132GP_FILESYSTEM_H
#include "File.h"

class FileSystem {
private:
    FileSystem();
    //FileSystem is a singleton so these should be prevented
    FileSystem(FileSystem const&) = delete;
    void operator=(FileSystem const&) = delete;
    //some root directory that nests all other dirs and files
    File* rootDir;
    File* currDir;
public:
    //implements the class as a singleton pattern
    static FileSystem & getInstance()
    {
        static FileSystem instance;
        return instance;
    }
    //build File with filename fn in currdurr & rtn ptr to same
    bool fcreate(std::string fn,std::string c,std::vector<bool> p);
    //list items in Dir -- akin to ls utility on currDir
    std::string listitems();
    //return pointer to current directory so that display can output its name
    File* getCurrDir();
    //blah



    //fread returns pointer to fName if it exists
    //so that display can display its contents,
    //or it can be modified
    //error message o.w.
    File* fread(std::string fName);
    //fwrite returns pointer to fName if it exists
    //so that display can display existing contents
    //make changes, and call fcreate to overwrite existing
    //file
    File* fwrite(std::string fName);
    //create new dir of given dName & returns it, return error if exists
    bool dcreate(std::string dName);
    //search for file from root using dfs, delete File with filename n if it
    //exists (return 1 if successful), return 0 o.w.
    bool fdelete(std::string n);
    //search for file from root using dfs, rename file n to newN and return
    //a 1 if successfull, 0 o.w.
    bool renameFile(std::string n,std::string newN);
    //locate file in dir hierarchy and return pointer to it, used by fread, fwrite, fdelete,
    //renameFile, chper
    File* fLocate(std::string fn);
    File *fLocateHelper(File *f, std::string fn);
    //change fn permissions to p (rwx =777) if file is found (start dfs at
    //rootDir) and return 1, if file not found return 0
    bool chper(std::string fn,std::vector<bool> p);

};
#endif //CSCI3132GP_FILESYSTEM_H



