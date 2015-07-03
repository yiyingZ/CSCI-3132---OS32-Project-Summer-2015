#include <string>

/*
 *	This class represents the process scheduler of the OS32 system
 */
class Scheduler {
private:
	// This holds a reference to the singleton instance of this class
	static Scheduler * instance;
	// Hides the contructor to maintain Singleton pattern
	Scheduler();
public:
	/*
	 *	This method returns a reference to the Singleton instance of this class
	 */
	static Scheduler * getInstance();

	/*
	 *	This method performs a system call with the given command string of utility and arguments
	 *  It will return the return code of the Command it executes, or EXIT_FAILURE if no valid command is found.
	 */
	int systemCall(std::string cmd_string);
};

// initializes the static singleton member as null
Scheduler * Scheduler::instance = NULL;