#include "encryption.h"
#include <string>
using namespace std;

Encryption::Encryption() : key("Here is a default key") {}

Encryption::Encryption(char* keyIn) : key(keyIn) {}

int Encryption::execute(char* filename)
{
	std::string* oldString = inFile(filename);
	int outString;
	
	outString = encrypt(oldString, filename);

	delete(oldString);
	return 0;
}

string* Encryption::inFile(char* filename)
{
	std::ifstream fileIn(filename);
	std::string* oldString = new string(std::istreambuf_iterator<char>(fileIn),
									 std::istreambuf_iterator<char>());
	fileIn.close();
	return oldString;
}


int Encryption::encrypt(string* input, char* filename)
{
	std::ofstream out(filename);
	for(int i = 0; i < input->size(); i++)
	{
		out << (char) (((*input)[i]) ^ key[i % key.size()]);
	}
	out.close();
	return 0;
}

int main()
{
	Encryption encryptor("All that is needed to create a very secure password here is to use something quite long that no one is expecting.  As long as this keeps going for a while there will be no repeating codes, except well, any time some characters repeate.");
	encryptor.execute("testFile.txt");
	return EXIT_SUCCESS;
}