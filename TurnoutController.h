/*
 * TurnoutController.h
 *
 *  Created on: Mar 8, 2010
 *      Author: frankw
 */

#ifndef TURNOUTCONTROLLER_H_
#define TURNOUTCONTROLLER_H_

#include "SimpleTurnout.h"

class TurnoutController {
private:
	SimpleTurnout turnout;
public:
	TurnoutController(int leftPin, int rightPin);
	void update(long millis);
};

#endif /* TURNOUTCONTROLLER_H_ */
