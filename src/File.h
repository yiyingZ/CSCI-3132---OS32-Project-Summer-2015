//
// Created by scotiatide on 17/07/15.
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
    File(std::string fn, std::vector<File *> d, std::string c,
         std::vector<bool> p);

    const std::string &getFileName();

    void setFileName(const std::string &fileName);

    bool getFileType();

    void setFileType(bool fileType);

    std::vector<File *> getDir();

    bool File::addDirElement(File *f);

    bool File::deleteDirElement(File *f);

    std::string &getContents();

    void setContents(const std::string &contents);


    /*
//build File with filename n & rtn ptr to same
File* createFile(std::string n);
//delete File with filename n
void deleteFile(std::string n);
//rename n to newN & rtn ptr to same
File* renameFile(std::string n,std::string newN);
//returns pointer to File with name n
File* modifyFile(std::string n);
//how to implement this??
bool getFileType();
 */
};

#endif //CSCI3132GP_FILE_H
