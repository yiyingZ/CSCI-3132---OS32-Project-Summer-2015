/*
 * Utilities.h
 *
 *  Created on: 7 Jul 2015
 *      Author: jturner
 */

#ifndef UTILITIES_H_
#define UTILITIES_H_

namespace Utilities {

	class Utilities {
		public:
			Utilities();
			virtual ~Utilities();

			virtual void execute() = 0;
	};

} /* namespace Utilities */

#endif /* UTILITIES_H_ */
