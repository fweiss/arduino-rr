/*
 * BaseController.cpp
 *
 *  Created on: Mar 12, 2011
 *      Author: frankw
 */

#include "BaseController.h"
#include "WProgram.h"

BaseController::BaseController() {
}
const char* BaseController::getName() {
	return "BaseController";
}
void BaseController::setup() {
	Serial.println(getName());
	setState(START);
}
void BaseController::setState(State state, unsigned long timeout) {
	deadmanTimeout = timeout;
	deadmanStart = millis();
	this->state = state;
	Serial.print("state ");Serial.print(state);Serial.print(": at ");Serial.print(millis());Serial.print(": for ");Serial.println(timeout);
}
void BaseController::update(unsigned long millis) {
	if (state != END && state != DEADMAN_TIMEOUT && millis - deadmanStart > deadmanTimeout) {
		setState(DEADMAN_TIMEOUT, 0);
	}
}
void BaseController::heartbeat() {
	deadmanStart = millis();
}
/**
 * Tests if the given pin/state has been pressed.
 * This assumes that there is no actual switch bounce, but has been observed even with the
 * motor sheild switches which supposably have hysterisis to avoid bounc.
 * FIXME: add timer to debounce
 */
bool BaseController::switchPressed(int pin, unsigned long& state) {
	bool sample = digitalRead(pin);
	bool timeout = millis() - state > 100;
	bool answer = ! sample && timeout;
	if ( ! sample) {
		state = millis();
	}
	return answer;
}
