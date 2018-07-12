/*
 * AriesController.h
 *
 *  Created on: Mar 14, 2010
 *      Author: frankw
 */

#ifndef ARIESCONTROLLER_H_
#define ARIESCONTROLLER_H_

#include "device/Locomotive.h"
#include "SimpleTurnout.h"
#include "device/TurnoutGroup.h"
#include "device/Waypoint.h"

class AriesController {
private:
	Locomotive locomotive;
	SimpleTurnout turnout;
	TurnoutGroup tog;
	Waypoint waypoint;
	enum State { START, MAIN, MAIN_COMPLETE, SHUNTING, SHUNT_STOP, RETURN_MAIN, REVERSE_STOP, REPOSITION, CLEAR, END };
	State currentState;
	long shuntStartMillis;
	long idleStartMillis;
	long startMillis;
	int waypointCount;
	void setState(State state);
	void setTurnout(int position);
public:
	AriesController(int foo);
	void update(long millis);
};

#endif /* ARIESCONTROLLER_H_ */
