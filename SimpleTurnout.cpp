/*
 * Turnout is a two-channel output
 * output a pulse to switch the state.
 *
 *  Created on: Mar 4, 2010
 *      Author: frankw
 */

#include "SimpleTurnout.h"
#include "WProgram.h"

SimpleTurnout::SimpleTurnout(const char* name, int leftPin, int rightPin) {
	this->leftPin = leftPin;
	this->rightPin = rightPin;
	this->pulseWidth = 25;
	this->pulseStart = 0;
	pinMode(this->leftPin, OUTPUT);
	pinMode(this->rightPin, OUTPUT);
}
void SimpleTurnout::setPosition(int position) {
	if (this->position != position) {
		this->position = position;
		this->pulseStart = millis();
	}
}
int SimpleTurnout::getPosition() {
	return this->position;
}
void SimpleTurnout::update(long millis) {
	int pin = position == LEFT ? leftPin : rightPin;
	boolean timedOut = millis - pulseStart > pulseWidth;
	if (timedOut) {
		digitalWrite(pin, LOW);
		pulseStart = 0;
	} else {
		digitalWrite(pin, HIGH);
	}
}
