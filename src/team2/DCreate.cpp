/**
* @author: Chris D'Amours
*/
#include <string>
#include <iostream>
#include <stdlib.h>
#include "command.h"

using namespace std;

/**
* Dcreate class that creates a new directory when the command is executed
*/
class DCreate : public Command {
private: 
	char* dirname;
public:
	/* Dcreate constructor
	* @function name: DCreate
	* @return: void
	* @parameters: string dirname
	*/
	DCreate(string dirname) {
		this->dirname = new char[dirname.length() + 1];
		strcpy(this->dirname, dirname.c_str());
	}
	/* Execute function that creates new directory
	* @function name: execute
	* @return: int
	* @parameters: none
	*/
	int execute() {
		// Checks if there is a specified dirname, and whether it is less than 255 characters long
		if ((unsigned)strlen(this->dirname) < 1 || (unsigned)strlen(this->dirname) > 255)
		{
			cout << "Cannot create directory.\n";
			return 1;
		}
		else {
			char newDirectory[255];
			strcat(newDirectory, "mkdir ");
			strcat(newDirectory, this->dirname);
			system(newDirectory);
			cout << "Directory: " << this->dirname << " created." << "\n";
		}
		return 0;
	}
};
