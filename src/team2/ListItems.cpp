/*
 * ListItems.cpp
 *
 * This class is use to print the list the of files and directories in the current directory.
 * It takes the path and print the names of the current files and directories in it.
 *
 * This class is very dependent on the file structure implemented by the Kernel Group 1.
 * I might make some changes depending on what this group implemented.
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

	/*
	 * Constructor
	 */
	ListItems(){

	}

	/**
	 * Iterate through the files and directories in the current directory
	 *  and print their names to stdout
	 */
	int execute(){

		//create pointer to directory
		DIR *dir;
		string oneDot=".";
		string twoDot="..";

		//Initialize dirent structure
		struct dirent *ent;

		//Open current directory, iterate through it and display the files and folders names.
		if((dir = opendir(".")) != NULL){

			//Iterate until there is no more item left in the current directory
			while((ent = readdir(dir)) != NULL){

				//Do not display dotted names
				if(ent->d_name != oneDot && ent->d_name != twoDot)
				cout<<ent->d_name<<"\n";

			}

			//Close the current directory
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







