/**
* @author: Chris D'Amours
*/
#include <string>
#include <iostream>
#include <stdlib.h>
#include "command.h"
//#include "OS32Memory.h"

using namespace std;

/**
* Fcreate class that creates a new file when the command is executed
*/
class FCreate : public Command {
private:
  	char* filename;
public:
	/* Fcreate constructor
	* @function name: FCreate
	* @return: void
	* @parameters: string filename
	*/
	FCreate(string filename) {
		this->filename = new char[filename.length() + 1];
		strcpy(this->filename, filename.c_str());
	}
	/* Execute function that creates new file
	* @function name: execute
	* @return: int
	* @parameters: none
	*/
	int execute() {
		// Checks if there is a specified filename, and whether it is less than 255 characters long
		if ((unsigned)strlen(this->filename) < 1 || (unsigned)strlen(this->filename) > 255)
		{
			cout << "Cannot create file.\n";
			return 1;
		}
		else {
			//OS32Memory *mem = new OS32Memory();
			char newFile[255];
			strcat(newFile, "touch ");
			strcat(newFile, this->filename);
			system(newFile);
			//double fs = mem.findFileSize(filename);
			//mem.updateMemConfig(fs);
			cout << "File: " << filename << " created." << "\n";
		}
		return 0;
	}	
};
