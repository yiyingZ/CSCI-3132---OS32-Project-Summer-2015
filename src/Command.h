#include <string>
#include <vector>

/*
 *	This class provides a common interface for system utilities used by the OS32 system.
 */
class Command {
protected:
	/*
	 * This is protected to stop classes from directly instantiating this class
	 * args contains the tokenized command string used to run this command
	 * the 0th element will be the name of the command, and any other elements will be arguments to the command.
	 */
	Command(std::vector<std::string> args);
public:
	/*
	 * This method executes the utility and should contain all execution logic
	 * Should return EXIT_FAILURE or EXIT_SUCCESS
	 */
	virtual int execute() = 0;
};