/*
 * ListItems.cpp
 *
 * This class is use to print the list the of files and directories in the path provided
 * by the user. It takes the path and print the names of the current files and directories
 * in it.
 *
 * This class is very dependent on the file structure implemented by the Kernel Group 1.
 * I might make some changes depending on what this group implemented.
 *
 * This class will also be altered to respect the design guidelines by extending the command
 * class.
 *
 * The solution designed for this command works with both Windows and Linux file structure.
 *
 * A cross platform solution can be implemented but will be heavily dependent on Third party libraries.
 *
 *  Created on: Jul 17, 2015
 *      Author: Arnold Zoundi - B00584876
 */

#include<iostream>
#include<string>
#include<sstream>
#include"Command.h"
#include "dirent.h"

using namespace std;

class ListItems : public Command{

private:
	char* pathname;

public:

	ListItems(string pathname){

		this->pathname = new char[pathname.length() + 1];
		strcpy(this->pathname, pathname.c_str()); //use strcpy_s when compiling with visual studio. No change if using eclipse

	}

	/**
	 * Iterate through the files and directories and print their names to stdout
	 */
	int execute(){

		DIR *dir;
		string oneDot=".";
		string twoDot="..";
		struct dirent *ent;
		if((dir = opendir(this->pathname))){

			while((ent = readdir(dir)) != NULL){

				if(ent->d_name != oneDot && ent->d_name != twoDot)
				cout<<ent->d_name<<"\n";
			}

			closedir(dir);

			return 1;

		}else{
			cout<<"Could not find Directory\n";
			return 0;
		}

	}

};


/**
 * Sample demo
 */
//int main(int argc, const char * argv[]){
//
//	Command* command = new ListItems(argv[1]);
//
//	//make sure path name was provided
//	if(argc != 2){
//
//		cout<<"Usage: program_name path_name\n";
//		return 0;
//
//	}
//
//	//call execute to display list of files
//	if(command->execute()){
//		cout<<"\nSuccess\n";
//
//	}else{
//		cout<<"\nFailure\n";
//	}
//
//	return 0;
//}



