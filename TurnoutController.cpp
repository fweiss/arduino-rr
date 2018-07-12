/*
 * TurnoutController.cpp
 *
 *  Created on: Mar 8, 2010
 *      Author: frankw
 */

#include "TurnoutController.h"

TurnoutController::TurnoutController(int leftPin, int rightPin)
: turnout("turnout", leftPin, rightPin) {
}
void TurnoutController::update(long millis) {
	long period = millis % 2000;
	if (period == 0) {
		turnout.setPosition(SimpleTurnout::LEFT);
	}
	if (period == 1000)
		turnout.setPosition(SimpleTurnout::RIGHT);
	turnout.update(millis);
}
