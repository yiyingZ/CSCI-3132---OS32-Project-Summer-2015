#include <string>

/*
 *	This class provides a common interface for system and external utilities used by the OS32 system.
 */
class Command {
protected:
	/*
	 * This is protected to stop classes from directly instantiating this class
	 * argc = number of arguments
	 * argv = list of arguments
	 */
	Command(int argc, std::string **argv);
public:
	/*
	 * This method executes the utility and should contain all execution logic
	 * Should return EXIT_FAILURE or EXIT_SUCCESS
	 */
	virtual int execute() = 0;
};