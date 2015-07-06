#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <iostream>
#include <fstream>

class Encryption
{
public:
	Encryption();
	Encryption(char* keyIn);
	int execute(char* filename);
private:
	std::string* inFile(char* filename);
	int encrypt(std::string* input, char* filename);
	std::string key;
};

#endif