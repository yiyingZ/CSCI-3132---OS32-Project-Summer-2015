/*
 * Utilities.cpp
 *
 *  Created on: 7 Jul 2015
 *      Author: jturner
 *
 *
 *  The Utilities class design has changed from what was initially discussed after review of the project specifications
 *
 *	The Utilities class should be instantiated first with a reference to the UI and Process management and execute() run
 *	to display the menu.
 *
 *	Note: No memory needs to be used with the base Utility execute() task as it will be using the referenced
 *	UI to display a menu and take user input for selection and no process is scheduled.
 *
 *	The user may then select which Utility to run, which will be then be returned as a Utilities* of selected Utility type. (eg converter, calculator etc..)
 *
 *	This Utilities* will then be passed to the kernel for scheduling and execution, then returning to the UI.
 */

#include "Utilities.h"
#include "Converter.h"
#include "encryption.h"

using namespace std;

namespace Utilities {

	Utilities::Utilities() {
		//TODO Add reference to constructor for UI and Kernel for process scheduling and execution.

	}

	Utilities::~Utilities() {
		// TODO Auto-generated destructor stub
	}


	/**
	 * Menu for utilities to be run as specified in the project documentation.
	 *
	 * Function will eventually instantiate Utility objects of different types and return them to what needs it.
	 *
	 * eg:
	 *
	 * 		Utility* util = new Converter();
	 *
	 */
	Utilities* Utilities::displayMenu(){

		int runUtil = -1;

		Utilities* util = NULL;

		cout << "\n\n::Utilities Menu::" << endl;
		cout << "1. Converter Utility" << endl;
		cout << "2. Encryption Utility" << endl;
		cout << "3. Message of the day Utility" << endl;
		cout << "4. Palindrome Utility" << endl;
		cout << "5. Calculator Utility" << endl;
		cout << "6. Display system date/time" << endl;
		cout << "0. Quit" << endl;
		cout << "\nEnter Utility to run (1-6, 0 to Quit): ";

		cin >> runUtil;

		if(!cin){
			cout << "Error - Please enter a valid menu selection" << endl;
			runUtil = -1;

			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else{

			switch(runUtil){
				case CONVERTER_UTILITY:

					util = new Converter();

					break;
				case ENCRYPTION_UTILITY:

					break;
				case MOTD_UTILITY:

					cout << "motd" << endl;
					break;
				case PALINDROME_UTILITY:


					break;
				case CALCULATOR_UTILITY:


					break;
				case DATE_TIME_UTILITY:

					break;

				case EXIT:
					util = NULL;
					cout << "Exiting Utilites!" << endl;
					break;
				default:
					cout << "Error - Please enter a valid menu selection" << endl;
					runUtil = -1;
					break;
			}

			return util;
		}

	}

	/**
	 *
	 * Virtual function execute that will be overridden by other objects and will return which ever instantiated object to UI or Kernel (which ever needs it)
	 *
	 */
	 void Utilities::execute(){
		 Utilities* util;

		 while(util != NULL){
			 util = displayMenu();

			 if(util != NULL){
				 util->execute();
			 }
		 }

		 //This will be replaced with reference to the Kernel and the pointer "util" passed for scheduling and execution
		 /*if(util != NULL){
			 util->execute();
		 }*/


		 //TODO need access to the memory management system in order to pass the pointer to the created utility object
	}



} /* namespace Utilities */
