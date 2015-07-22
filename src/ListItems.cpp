/*
 * test.cpp
 *
 *  Created on: Jul 21, 2015
 *      Author: ArnoldBocor
 */

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
 *  Created on: Jul 17, 2015
 *      Author: Arnold Zoundi - B00584876
 */

#include<iostream>
#include<string>
#include<sstream>
#include "Command.h"
#include "dirent.h"

using namespace std;

class ListItems:public Command{

public:

	//constructor
	ListItems(){

	}

	/**
	 * Iterate through the files and directories and print their names to stdout
	 */
	int execute(){

		DIR *dir;
		string oneDot=".";
		string twoDot="..";
		struct dirent *ent;
		if((dir = opendir(".")) != NULL){

			while((ent = readdir(dir)) != NULL){

				if(ent->d_name != oneDot && ent->d_name != twoDot)
				cout<<ent->d_name<<"\n";
			}

			closedir(dir);

			return 1;

		}


		 return 0;

	}


};


/**
 * Sample demo
 */
//int main(int argc, const char * argv[]){
//
//	Command* command = new ListItems();
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







