#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <iostream>
#include "FileSystem.h"
#include "Utilities.h"

namespace Utilities {

	class Encryption : public Utilities
	{
	public:
		Encryption() {};
		~Encryption() {}
		void execute();
	private:
		File* getFile();
		int encrypt(File* file, std::string* key);
	};

}
#endif