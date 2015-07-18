//
// Created by Aaron Windsor on 20150715
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

    const std::string &getFileName();

    void setFileName(const std::string &fileName);

    bool getFileType();

    void setFileType(bool fileType);

    std::vector<File *> getDir();

    bool addDirElement(File *f);

    bool deleteDirElement(File *f);

    std::string &getContents();

    void setContents(const std::string &contents);

};

#endif //CSCI3132GP_FILE_H
