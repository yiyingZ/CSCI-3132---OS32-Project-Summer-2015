/*
 * Testing file created by Yiying Zhang
 */
#include "Menu.h"
#include "Parser.h"
#include "UI.h"
#include "unittesting.h"
#include <iostream>
#include <string>
#include <cstring>

#define MAX_LEN (80)
using namespace std;

int main(){
	char pass[MAX_LEN];

	/*
		 * Test for UI
		 * Tests include:
		 * 		1. println()
		 * 		2. print()
		 * 		3. read()
		 * 		4. readLine()
		 */
		UI::println("Test println");
		UI::print("Test print");

		UI::println("no new line.");
		// enter a string
		    UI::println("Enter a string:");
		    std::string s = UI::read<std::string>();
		    UI::println(s);

		// enter an int
		   UI::println("Enter an int:");
		   int x = UI::read<int>();
		   //UI::println(std::to_string(x));

		UI *uiTest = new UI;
		assertNotNull("UI object should not be NULL\n", uiTest);
		uiTest->startUI();

		cin >> pass;
		if (strcmp(pass, "N") == 0){
			cout << "Parser tests failed" << endl;
			exit(EXIT_FAILURE);
		}
	/*
	 * Test for Menu
	 * Tests include:
	 * 		1. printOptions()
	 */
	/* Create a Menu object */
	Menu mainMenu
	            {"main",
	                {
	                        {"User Commands", {}},
	                        {"Utilties", {
	                                {"Encryption", {}},
	                                {"Calculator", {}},
	                                {"Message of the Day", {}},
	                                {"Converter", {}},
	                                {"Date and Time", {}},
	                                {"Palindrome Checker", {}},
	                                {"Exit Checker", {}},
	                        }},
	                        {"Shutdown", {}}
	                }
	            };
	/* Test printOptions function */
	assertNotNull("Menu object should not be NULL\n", &mainMenu);
	mainMenu.printOptions();
	cout << "\nTest passed? (Y/N) ";
	cin >> pass;
	if (strcmp(pass, "N") == 0){
		cout << "Menu tests failed" << endl;
		exit(EXIT_FAILURE);
	}
	// End of Menu Testing

	/*
	 * Test for Parser
	 * Tests include:
	 * 		1. parsing()
	 * 		2. displayToken()
	 *
	 * We have to use displayToken() to test parsing()
	 * because the result of parsing() will affect the output of displayToken()
	 */
	parser *parserTest = new parser();
	assertNotNull("Parser object should not be NULL\n", parserTest);
	string testStr = "This is a test string";
	parserTest->parsing(testStr);
	parserTest->displayToken();

	cout << "\nTest passed? (Y/N) ";
	cin >> pass;
	if (strcmp(pass, "N") == 0){
		cout << "Parser tests failed" << endl;
		exit(EXIT_FAILURE);
	}
	// End of Parser Testing

	return 0;
}
