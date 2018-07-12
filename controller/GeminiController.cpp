/*
 * TaurusController.cpp
 *
 *  Created on: Apr 20, 2010
 *      Author: frankw
 */

#include "GeminiController.h"
#include "WProgram.h"

GeminiController::GeminiController()
: outWaypoint("out", 1), inWaypoint("in", 2), yardWaypoint("yard", 3), uncouplerWaypoint("uncouple", 4) {
	setState(START);
	//inWaypoint.setThresholds(500, 400);
	//yardWaypoint.setThresholds(600, 200);
	pinMode(6, OUTPUT);
	outTurnout = &turnouts.getTurnout(0);
	inTurnout = &turnouts.getTurnout(1);
	yardTurnout = &turnouts.getTurnout(2);
	shuntTurnout = &turnouts.getTurnout(3);
	uncouplerWaypoint.setOffDelay(0);
}
void GeminiController::setState(State state, unsigned long timeout) {
	this->deadmanDelay = timeout;
	this->deadmanStart = millis();
	this->state = state;
	Serial.print(state);
	Serial.print(": ");
	Serial.println(timeout);
}
void GeminiController::heartBeat()	{
	deadmanStart = millis();
}
void GeminiController::update(long millis) {
	static const int fullSpeed = 110;
	static const int yardSpeed = 50;
	int coupleSpeed = 30;
	if (millis - deadmanStart > deadmanDelay) {
		state = END;
	}
	switch (state) {
	case START:
		shuntTurnout->setPosition(turnouts.LEFT);
		inWaypoint.calibrate();
		outWaypoint.calibrate();
		yardWaypoint.calibrate();
		outTurnout->setPosition(turnouts.RIGHT);
		inTurnout->setPosition(turnouts.LEFT);
		yardTurnout->setPosition(turnouts.RIGHT);
		twoTrack.setSpeed(yardSpeed);
		setState(AROUND_SHUNT, 10000);
		break;
	case AROUND_SHUNT:
		if (yardWaypoint.beingUncovered()) {
			setSpeed(0);
			setState(PAUSE_BEFORE_COUPLE);
		}
		break;
	case PAUSE_BEFORE_COUPLE:
		if (expired(500)) {
			shuntTurnout->setPosition(turnouts.RIGHT);
			twoTrack.reverse(true);
			setSpeed(coupleSpeed+10);
			setState(COUPLE, 15000);
		}
		break;
	case COUPLE:
		if (uncouplerWaypoint.beingCovered()) {
			setSpeed(0);
			setState(PAUSE_AFTER_COUPLE);
		}
		break;
	case PAUSE_AFTER_COUPLE:
		if (expired(1000)) {
			twoTrack.reverse(false);
			setSpeed(yardSpeed);
			setState(TO_MAIN, 15000);
		}
		break;
	case TO_MAIN:
		debugWaypoint();
		if (yardWaypoint.beingCovered()) {
			heartBeat();
		}
		if (outWaypoint.beingUncovered()) {
			setSpeed(fullSpeed-10);
			outTurnout->setPosition(turnouts.LEFT);
			mainCount = 0;
			setState(MAIN, 12000);
		}
		break;
	case MAIN:
		if (inWaypoint.beingCovered()) {
			mainCount++;
			heartBeat();
		}
		if (inWaypoint.beingCovered() && mainCount > 1) {
			inTurnout->setPosition(turnouts.RIGHT);
			yardTurnout->setPosition(turnouts.LEFT);
			twoTrack.reverse();
			twoTrack.setSpeed(yardSpeed);
			setState(TO_YARD, 10000);
		}
		break;
	case TO_YARD:
		if (yardWaypoint.beingCovered()) {
			shuntTurnout->setPosition(turnouts.RIGHT);
			setSpeed(coupleSpeed);
			setState(TO_UNCOUPLER, 10000);
		}
		break;
	case TO_UNCOUPLER:
		if (uncouplerWaypoint.beingUncovered()) {
			setState(PAUSE_BEFORE_UNCOUPLER);
		}
		break;
	case POSITION_UNCOUPLER:
		if (expired(550)) {
			twoTrack.setSpeed(0);
			setState(PAUSE_BEFORE_UNCOUPLER);
		}
		break;
	case PAUSE_BEFORE_UNCOUPLER:
		if (expired(700)) {
			setSpeed(coupleSpeed);
			twoTrack.reverse(false);
			setState(BACK_UNCOUPLER);
		}
		break;
	case BACK_UNCOUPLER:
		if (expired(950)) {
			setSpeed(0);
			setState(PAUSE_AFTER_UNCOUPLER, 2000);
		}
		break;
	case PAUSE_AFTER_UNCOUPLER:
		if (expired(500)) {
			twoTrack.reverse(true);
			setSpeed(yardSpeed);
			setState(PARK, 6000);
		}
		break;
	case PARK:
		if (expired(2700)) {
			setSpeed(0);
			setState(END);
		}
		break;
	case END:
		twoTrack.setSpeed(0);
		debugWaypoint();
		break;
	}
	turnouts.update(millis);
	twoTrack.update(millis);
	outWaypoint.update(millis);
	inWaypoint.update(millis);
	yardWaypoint.update(millis);
	uncouplerWaypoint.update(millis);
}
void GeminiController::begin(State state, unsigned long delay) {
	runDelay = delay;
	runStart = millis();
}
bool GeminiController::expired(unsigned long delay) {
	return millis() - deadmanStart > delay;
}
void GeminiController::debugWaypoint() {
	Waypoint &waypoint = outWaypoint;
	if (waypoint.beingCovered()) {
		digitalWrite(6, HIGH);
	}
	if (waypoint.beingUncovered()) {
		digitalWrite(6, LOW);
	}
}
