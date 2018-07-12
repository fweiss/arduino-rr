/*
 * CouplerTestController.h
 *
 *  Created on: Mar 12, 2011
 *      Author: frankw
 */

#ifndef COUPLERTESTCONTROLLER_H_
#define COUPLERTESTCONTROLLER_H_

#include "BaseController.h"
#include "../device/Turnout.h"
#include "../device/TurnoutGroup.h"

class CouplerTestController: public BaseController {
public:
	CouplerTestController();
	virtual const char* getName();
	virtual void setup();
	virtual void update(unsigned long millis);
	StateMethod currentState;
	const char* nextStateName;
	const char* currentStateName;

	StateMethod start();
	StateMethod end();
	StateMethod end_deadman();
	StateMethod going_left();
	StateMethod going_right();

private:
	int pinLed1;
	int pinLed2;
	unsigned long timeoutStart;
	unsigned long blinkPeriod;
	TurnoutGroup turnouts;
	Turnout* outTurnout;
	unsigned long switchTimestamp;
};

#endif /* COUPLERTESTCONTROLLER_H_ */
