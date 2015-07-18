#include "encryption.h"

#include <string>
#include <sstream>
using namespace std;
using namespace Utilities;

void Encryption::execute()
{	
	string key;
	File* inFile = getFile();
	if(inFile == nullptr || inFile->getFileType())
	{
		return;
	}
	cout << "Enter a password or phrase." << endl;
	cin >> key;
	encrypt(inFile, &key);
	return;
}

File* Encryption::getFile()
{
	string filename;
	FileSystem& fs = FileSystem::getInstance();
	cout << "Enter a file to Encrypt/Decrypt:" << endl;
	cin >> filename;

	File* file = new File(filename, "Some text to be put in to the file", { true, true, true }); // fs.fLocate(filename);
	if(file == nullptr || file->getFileType())
	{
		cout << "No such file exists." << endl;
	}
	
	return file;
}


int Encryption::encrypt(File* file, string* key)
{
	string input = file->getContents();
	stringstream outstream;
	for(size_t i = 0; i < input.size(); i++)
	{
		outstream << (char) (input[i] ^ (*key)[i % key->size()]);
	}
	file->setContents(outstream.str());

	return 0;
}

int main()
{
	FileSystem& fs = FileSystem::getInstance();
	Encryption x;
	// fs.fcreate("file", "some text inside here", { true, true, true });
	x.execute();
	// system("pause");
	return EXIT_SUCCESS;
}