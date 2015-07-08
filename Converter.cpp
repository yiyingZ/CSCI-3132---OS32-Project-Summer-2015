/*
 * Converter.cpp
 *
 *  Created on: 8 Jul 2015
 *      Author: jturner
 */

#include "Converter.h"

using namespace std;

namespace Utilities {

	Converter::Converter() : Utilities(){
		// TODO Auto-generated constructor stub

	}

	Converter::~Converter() {
		// TODO Auto-generated destructor stub
	}

	void Converter::execute(){
		displayMenu();
	}

	void Converter::displayMenu(){

		cout << "::Converter Menu::" << endl;
		cout << "\t1. Convert from Celsius to Fahrenheit" << endl;
		cout << "\t2. Convert from Fahrenheit to Celsius" << endl;
		cout << "\t3. Convert from feet to meters" << endl;
		cout << "\t4. Convert from meters to feet" << endl;
		cout << "\t5. Convert from lbs to kgs" << endl;
		cout << "\t6. Convert from kgs to lbs" << endl;

		int selection = 0;
		cin >> selection;

		if(checkUserInput()){
			cout << "\nEnter Unit: " << endl;

			double userInput = 0.0;
			cin >> userInput;

			if(checkUserInput()){

				switch(selection){
				case FtoC:
					break;
				case CtoF:
					break;
				case MetersToFeet:
					break;
				case FeetToMeters:
					break;
				case LbsToKgs:
					break;
				case KgsToLbs:
					break;
				default:
					cout << "Error - Please enter a valid conversion selection" << endl;
					break;
				}

			}
		}


	}

	bool Converter::checkUserInput(){
		if(!cin){
			cout << "Error - Please Enter Valid Input!" << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max());
			return false;
		}

		return true;
	}

	void Converter::convertFtoC() {
	}

	void Converter::convertCtoF() {
	}

	void Converter::convertFeetToMeters() {
	}

	void Converter::convertMetersToFeet() {
	}

	void Converter::convertLbsToKgs() {
	}

	void Converter::convertKgsToLbs() {
	}

} /* namespace Utilities */
