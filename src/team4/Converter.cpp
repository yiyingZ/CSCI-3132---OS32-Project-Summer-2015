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
		cout << "\t1. Convert from Fahrenheit to Celsius" << endl;
		cout << "\t2. Convert from Celsius to Fahrenheit" << endl;
		cout << "\t3. Convert from feet to meters" << endl;
		cout << "\t4. Convert from meters to feet" << endl;
		cout << "\t5. Convert from lbs to kgs" << endl;
		cout << "\t6. Convert from kgs to lbs" << endl;

		int selection = 0;

		cout << "Enter Selection: ";
		cin >> selection;

		if(checkUserInput()){
			cout << "\nEnter Unit: ";

			double userInput = 0.0;
			double result = 0.0;
			cin >> userInput;

			if(checkUserInput()){

				cout << endl;

				switch(selection){
				case FtoC:
					result = (((userInput * 9) / 5) + 32);
					cout << "F to C: ";
					break;
				case CtoF:
					result = (((userInput - 32) * 5) / 9);
					cout << "C to F: ";
					break;
				case MetersToFeet:
					result = userInput * 3.28;
					cout << "M to Ft: ";
					break;
				case FeetToMeters:
					result = userInput / 3.28;
					cout << "Ft to M: " ;
					break;
				case LbsToKgs:
					result = userInput / 2.2;
					cout << "Lbs to Kgs: ";
					break;
				case KgsToLbs:
					result = userInput * 2.2;
					cout << "Kgs to Lbs: ";
					break;
				default:
					cout << "Error - Please enter a valid conversion selection" << endl;
					break;
				}

				cout << result << endl;

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



} /* namespace Utilities */
