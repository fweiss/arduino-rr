/*
 * CouplerTestController.cpp
 *
 *  Created on: Mar 12, 2011
 *      Author: frankw
 */

#include "CouplerTestController.h"
#include "WProgram.h"

#define NextState(sm) (nextStateName=#sm,(StateMethod)&CouplerTestController::sm)

CouplerTestController::CouplerTestController() {
}
const char* CouplerTestController::getName() {
	return "CouplerTestController";

}
void CouplerTestController::setup() {
	Serial.println(getName());
	currentState = NextState(start);
	currentStateName = nextStateName;
	timeoutStart = millis();
	blinkPeriod = 1000;
	pinLed1 = 7;
	pinLed2 = 6;
	pinMode(pinLed1, OUTPUT);
	pinMode(pinLed2, INPUT);
	outTurnout = &turnouts.getTurnout(0);
	switchTimestamp = 0;
}
void CouplerTestController::update(unsigned long millis) {
	//if (state != END && state != DEADMAN_TIMEOUT && millis - deadmanStart > deadmanTimeout) {
	//	currentState = (Scifi) &CouplerTestController::end_deadman;
	//}
	//BaseController::update(millis);
	StateMethod nextState;
	// run the current state method
	nextState = (StateMethod) (this->*currentState)();
	if (strcmp(currentStateName, nextStateName) != 0) {
		Serial.print("next state: ");
		Serial.println(nextStateName);
	}
	currentStateName = nextStateName;
	currentState = nextState;

	turnouts.update(millis);
}
StateMethod CouplerTestController::start() {
	if (switchPressed(pinLed2, switchTimestamp)) {
		digitalWrite(pinLed1, HIGH);
		timeoutStart = millis();
		//return (StateMethod) &CouplerTestController::going_left;
		return NextState(going_left);
	}
	return NextState(start);
}
StateMethod CouplerTestController::end() {
	return NextState(end);
}
StateMethod CouplerTestController::end_deadman() {
	return NextState(end_deadman);
}
StateMethod CouplerTestController::going_left() {
	if (switchPressed(pinLed2, switchTimestamp)) {
		digitalWrite(pinLed1, LOW);
		outTurnout->setPosition(turnouts.LEFT);
		return NextState(going_right);
	}/*
	if (millis() - timeoutStart > blinkPeriod) {
		timeoutStart = millis();
		digitalWrite(pinLed1, LOW);
		outTurnout->setPosition(turnouts.LEFT);
		return NextState(going_right);
	}*/
	return NextState(going_left);
}
StateMethod CouplerTestController::going_right() {
	if (switchPressed(pinLed2, switchTimestamp)) {
		digitalWrite(pinLed1, HIGH);
		outTurnout->setPosition(turnouts.RIGHT);
		return NextState(going_left);
	}/*
	if (millis() - timeoutStart > blinkPeriod) {
		timeoutStart = millis();
		digitalWrite(pinLed1, HIGH);
		outTurnout->setPosition(turnouts.RIGHT);
		return NextState(going_left);
	}*/
	return NextState(going_right);
}
