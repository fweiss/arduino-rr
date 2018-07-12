/*
 * TaurusController.cpp
 *
 *  Created on: Apr 20, 2010
 *      Author: frankw
 */

#include "TaurusController.h"
#include "WProgram.h"

TaurusController::TaurusController()
: outWaypoint("out", 1), inWaypoint("in", 2), yardWaypoint("yard", 3) {
	setState(START);
	//inWaypoint.setThresholds(500, 400);
	//yardWaypoint.setThresholds(600, 200);
	pinMode(6, OUTPUT);
	outTurnout = &turnouts.getTurnout(0);
	inTurnout = &turnouts.getTurnout(1);
	yardTurnout = &turnouts.getTurnout(2);
	shuntTurnout = &turnouts.getTurnout(3);
}
void TaurusController::setState(State state) {
	this->state = state;
}
void TaurusController::update(long millis) {
	switch (state) {
	case START:
		shuntTurnout->setPosition(turnouts.RIGHT);
		inWaypoint.calibrate();
		outWaypoint.calibrate();
		yardWaypoint.calibrate();
		outTurnout->setPosition(turnouts.RIGHT);
		inTurnout->setPosition(turnouts.LEFT);
		yardTurnout->setPosition(turnouts.RIGHT);
		twoTrack.setSpeed(fullSpeed);
		setState(TO_MAIN);
		break;
	case TO_MAIN:
		debugWaypoint();
		if (outWaypoint.beingUncovered()) {
			outTurnout->setPosition(turnouts.LEFT);
			begin(MAIN, 10000);
			mainCount = 0;
			setState(MAIN);
		}
		break;
	case MAIN:
		if (inWaypoint.beingCovered()) {
			mainCount++;
		}
		if (inWaypoint.beingCovered() && mainCount > 1) {
			inTurnout->setPosition(turnouts.RIGHT);
			yardTurnout->setPosition(turnouts.LEFT);
			twoTrack.reverse();
			twoTrack.setSpeed(yardSpeed);
			begin(TO_YARD, 5000);
			setState(TO_YARD);
		}
		if (expired(MAIN)) {
			twoTrack.setSpeed(0);
			setState(END);
		}
		break;
	case TO_YARD:
		if (yardWaypoint.beingUncovered()) {
			shuntTurnout->setPosition(turnouts.LEFT);
			twoTrack.setSpeed(0);
			setState(END);
		}
		if (expired(TO_YARD)) {
			twoTrack.setSpeed(0);
			setState(END);
		}
	case END:
		debugWaypoint();
		break;
	}
	turnouts.update(millis);
	twoTrack.update(millis);
	outWaypoint.update(millis);
	inWaypoint.update(millis);
	yardWaypoint.update(millis);
}
void TaurusController::begin(State state, unsigned long delay) {
	runDelay = delay;
	runStart = millis();
}
bool TaurusController::expired(State state) {
	return millis() - runStart > runDelay;
}
void TaurusController::debugWaypoint() {
	Waypoint &waypoint = inWaypoint;
	if (waypoint.beingCovered()) {
		digitalWrite(6, HIGH);
	}
	if (waypoint.beingUncovered()) {
		digitalWrite(6, LOW);
	}
}
