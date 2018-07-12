/*
 * TaurusController.h
 *
 *  Created on: Apr 20, 2010
 *      Author: frankw
 */

#ifndef TAURUSCONTROLLER_H_
#define TAURUSCONTROLLER_H_

#include "../device/TurnoutGroup.h"
#include "../device/TwoTrack.h"
#include "../device/Waypoint.h"
#include "../device/Turnout.h"

class TaurusController {
private:
	enum State { START, TO_MAIN, MAIN, TO_YARD, END};
	static const int fullSpeed = 130;
	static const int yardSpeed = 80;
	int state;
	void setState(State state);
	TurnoutGroup turnouts;
	TwoTrack twoTrack;
	Waypoint outWaypoint;
	Waypoint inWaypoint;
	Waypoint yardWaypoint;
	long runStart;
	unsigned long runDelay;
	int mainCount;
	void begin(State state, unsigned long delay);
	bool expired(State state);
	void debugWaypoint();
	Turnout* outTurnout;
	Turnout* inTurnout;
	Turnout* yardTurnout;
	Turnout* shuntTurnout;
public:
	TaurusController();
	void update(long millis);
};

#endif /* TAURUSCONTROLLER_H_ */
