/*
 * TaurusController.h
 *
 *  Created on: Apr 20, 2010
 *      Author: frankw
 */

#ifndef GEMINICONTROLLER_H_
#define GEMINICONTROLLER_H_

#include "../device/TurnoutGroup.h"
#include "../device/TwoTrack.h"
#include "../device/Waypoint.h"
#include "../device/Turnout.h"

class GeminiController {
private:
	enum State {
		START,
		AROUND_SHUNT,
		PAUSE_BEFORE_COUPLE,
		COUPLE,
		PAUSE_AFTER_COUPLE,
		TO_MAIN, MAIN,
		TO_YARD,
		TO_UNCOUPLER,
		POSITION_UNCOUPLER,
		PAUSE_BEFORE_UNCOUPLER,
		BACK_UNCOUPLER,
		PAUSE_AFTER_UNCOUPLER,
		RELEASE_UNCOUPLER,
		PARK,
		END
	};
	static const int fullSpeed = 130;
	static const int yardSpeed = 80;
	int state;
	void setState(State state, unsigned long timeout = 3000);
	TurnoutGroup turnouts;
	TwoTrack twoTrack;
	Waypoint outWaypoint;
	Waypoint inWaypoint;
	Waypoint yardWaypoint;
	Waypoint uncouplerWaypoint;
	long runStart;
	unsigned long runDelay;
	int mainCount;
	void begin(State state, unsigned long delay);
	bool expired(unsigned long delay);
	void debugWaypoint();
	Turnout* outTurnout;
	Turnout* inTurnout;
	Turnout* yardTurnout;
	Turnout* shuntTurnout;
	unsigned long deadmanStart;
	unsigned long deadmanDelay;
	void setSpeed(int speed) {
		twoTrack.setSpeed(speed);
	}
	void heartBeat();
public:
	GeminiController();
	void update(long millis);
};

#endif /* GEMINICONTROLLER_H_ */
