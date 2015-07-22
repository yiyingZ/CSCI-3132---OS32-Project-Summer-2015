#include <string>

/*
 *	This class provides a common interface for system and extenral utilities used by the OS32 system.
 */
class Command {
public:
	/*
	 * This method executes the utility and should contain all execution logic
	 * Should return EXIT_FAILURE or EXIT_SUCCESS
	 */
	virtual int execute() = 0;
};

class HelpMe : public Command {
public:
	int execute();
};

class FCreate : public Command {
	std::string filename;
public:
	FCreate(std::string filename) : filename(filename) {}
	int execute();
};

class FRead : public Command {
public:
	int execute();
};

class FWrite : public Command {
public:
	int execute();
};

class DCreate : public Command {
	std::string filename;
public:
	DCreate(std::string filename) : filename(filename) {}
	int execute();
};

class CurrDir : public Command {
public:
	CurrDir();
	int execute();
};

class ListItems : public Command {
public:
	ListItems();
	int execute();
};

class ChPer : public Command {
	std::string filename;
	std::string permissions;
public:
	ChPer(std::string filename, std::string permissions) : filename(filename), permissions(permissions) {}
	int execute();
};