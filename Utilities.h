/*
 * Utilities.h
 *
 *  Created on: 7 Jul 2015
 *      Author: jturner
 */

#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <iostream>
#include <string>
#include <limits>


enum{
	EXIT,
	CONVERTER_UTILITY,
	ENCRYPTION_UTILITY,
	MOTD_UTILITY,
	PALINDROME_UTILITY,
	CALCULATOR_UTILITY,
	DATE_TIME_UTILITY
};

namespace Utilities {

	class Utilities {
		public:
			Utilities();
			virtual ~Utilities();

			virtual void execute();

		private:
			void displayMenu();
	};

} /* namespace Utilities */

#endif /* UTILITIES_H_ */
