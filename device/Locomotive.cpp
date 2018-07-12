/*
 * Locomotive.cpp
 *
 *  Created on: Mar 6, 2010
 *      Author: frankw
 */

#include "Locomotive.h"
#include "WProgram.h"

Locomotive::Locomotive(const char* name, int speedPin, int directionPin) {
	this->speedPin = speedPin;
	this->directionPin = directionPin;
	this->requestedSpeed = 0.;
	this->lastSpeed = 0.;
	this->lastTime = 0;
	// millis per unit speed adjustment
	this->startDelta = 128.;
	this->stopDelta = 2.;
	pinMode(this->speedPin, OUTPUT);
	pinMode(this->directionPin, OUTPUT);
	this->mode = RUN;
}
void Locomotive::update(long millis) {
	float stallStartSpeed = 100.0;
	float nextSpeed = 0.;
	float deltaTime = (float) (millis - lastTime);
	if (mode == STOP) {
		requestedSpeed = 0.;
	}
	if (lastSpeed < requestedSpeed) {
		if (lastSpeed == 0) {
			nextSpeed = stallStartSpeed;
		} else {
			nextSpeed = min(requestedSpeed, lastSpeed + deltaTime / startDelta);
		}
	} else if (lastSpeed > requestedSpeed) {
		nextSpeed = max(requestedSpeed, lastSpeed - deltaTime / stopDelta);
	} else {
		nextSpeed = lastSpeed;
	}
	analogWrite(speedPin, (int) nextSpeed);
	lastSpeed = nextSpeed;
	lastTime = millis;
}
void Locomotive::setDirection(Direction direction) {
	digitalWrite(directionPin, (direction == REVERSE) ? HIGH : LOW);
}
void Locomotive::setRequestedSpeed(int speed) {
	this->requestedSpeed = (float) speed;
}
int Locomotive::getLastSpeed() {
	return (int) this->lastSpeed;
}
void Locomotive::stop() {
	setRequestedSpeed(0);
}
