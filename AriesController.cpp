/*
 * AriesController.cpp
 *
 *  Created on: Mar 14, 2010
 *      Author: frankw
 *
 * Original Locomotive speeds were based on a prescaler setting of 1. Subsequently, a setting
 * of 7 was found to provide better low speed control and "insulated section" crossover, while
 * maintaining low noise emission.
 */

#include "WProgram.h"
#include "AriesController.h"

AriesController::AriesController(int foo)
: locomotive("locomotive", 9, 13), turnout("turnout", 44, 45), waypoint("main", 1) {
	this->shuntStartMillis = 0;
	this->idleStartMillis = 0;
	this->currentState = START;
	//pinMode(6, OUTPUT);
}
void AriesController::setState(State state) {
	currentState = state;
}
void AriesController::update(long millis) {
	switch (currentState) {
	case START:
		setTurnout(SimpleTurnout::RIGHT);
		locomotive.setDirection(Locomotive::FORWARD);
		locomotive.setRequestedSpeed(150);
		waypointCount = 0;
		setState(MAIN);
		break;
	case MAIN:
		if (waypoint.beingCovered()) {
			waypointCount++;
		}
		if (waypointCount > 1) {
			locomotive.setRequestedSpeed(80);
			setState(MAIN_COMPLETE);
		}
		break;
	case MAIN_COMPLETE:
		if (waypoint.beingCovered()) {
			setTurnout(SimpleTurnout::LEFT);
			locomotive.setRequestedSpeed(28);
			shuntStartMillis = millis;
			setState(SHUNTING);
		}
		break;
	case SHUNTING:
		if (millis - shuntStartMillis > 1000) {
			locomotive.stop();
			idleStartMillis = millis;
			setState(SHUNT_STOP);
		}
		break;
	case SHUNT_STOP:
		if (millis - idleStartMillis > 2000) {
			locomotive.setDirection(Locomotive::REVERSE);
			locomotive.setRequestedSpeed(50);
			setState(RETURN_MAIN);
		}
		break;
	case RETURN_MAIN:
		if (waypoint.beingUncovered()) {
			locomotive.stop();
			setTurnout(SimpleTurnout::RIGHT);
			startMillis = millis;
			setState(REVERSE_STOP);
		}
		break;
	case REVERSE_STOP:
		if (millis - startMillis > 1000) {
			locomotive.setDirection(Locomotive::FORWARD);
			locomotive.setRequestedSpeed(50);
			setState(CLEAR);
		}
		break;
	case CLEAR:
		if (waypoint.beingUncovered()) {
			startMillis = millis;
			setState(REPOSITION);
		}
		break;
	case REPOSITION:
		if (millis - startMillis > 2000) {
			locomotive.stop();
			setState(END);
		}
		break;
	case END:
		break;
	default:
		break;
	}
	turnout.update(millis);
	tog.update(millis);
	locomotive.update(millis);
	waypoint.update(millis);
	//analogWrite(6, analogRead(1) / 4);
	//digitalWrite(6, waypoint.isCovered());
	//digitalWrite(6, waypoint.beingCovered());
}
void AriesController::setTurnout(int position) {
	//turnout.setPosition(position);
	tog.setPosition(1, position);
}
