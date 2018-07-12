/*
 * SwitchInput.cpp
 *
 *  Created on: Mar 4, 2010
 *      Author: frankw
 */

#include "SwitchInput.h"
#include "WProgram.h"

SwitchInput::SwitchInput(const char* name, int pin) {
	this->pin = pin;
	pinMode(pin, INPUT);
	this->lastState = digitalRead(pin);
	lastPress = 0;
}
void SwitchInput::update(unsigned long millis) {
	if (lastPress == 0 && digitalRead(pin)) {
		lastPress = millis;
	}
}
int SwitchInput::isClicked() {
	int currentState = digitalRead(pin);
	int transition = currentState != lastState;
	currentState = lastState;
	return transition;
}
