//
// Created by Aaron Windsor on 20150715
// Both Regular Files and Directories are Files (same as Linux)
// Regular Files have fileType=0, contents, and dir null, whereas
// Directories have fileTYpe=1, contents null, but dir can hold
// vector of File pointers (the files or directories nested under
// this dir)
//

#ifndef CSCI3132GP_FILE_H
#define CSCI3132GP_FILE_H

#include <string>
#include <vector>


class File {

private:
    std::string fileName;
    //0=file, 1 = dir
    bool fileType;
    //only directories can have vectors of Files
    std::vector<File *> dir;
    std::string contents;
    std::vector<bool> permissions;

public:
    //constructor if file is a regular file
    File(std::string fn, std::string c, std::vector<bool> p);
    //constructor if file is a directory
    File(std::string fn, std::vector<File *> d,std::vector<bool> p);
    std::string &getFileName();
    void setFileName(const std::string &fileName);
    bool getFileType();
    void setFileType(bool fileType);

    std::string &getContents();
    std::vector<File *> getDir();
    bool addDirElement(File *f);
    bool deleteDirElement(File *f);
    void setContents(const std::string &contents);
    void setPermissions(std::vector<bool> p);
};

#endif //CSCI3132GP_FILE_H
