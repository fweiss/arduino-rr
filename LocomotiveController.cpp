/*
 * LocomotiveController.cpp
 *
 *  Created on: Mar 8, 2010
 *      Author: frankw
 */

#include "WProgram.h"
#include "LocomotiveController.h"

LocomotiveController::LocomotiveController(int speedPin, int potPin)
: locomotive("locomotive", speedPin, 12) {
	this->potPin = potPin;
	pinMode(potPin, INPUT);
	pinMode(6, OUTPUT);

	pinMode(7, OUTPUT);
	pinMode(1, INPUT);
}
void LocomotiveController::update(long millis) {
	int requestedSpeed = analogRead(potPin) / 4;
	locomotive.setRequestedSpeed(requestedSpeed);
	//locomotive.update(millis);
	//analogWrite(6, 255 - locomotive.getLastSpeed());
	//analogWrite(speedPin, requestedSpeed);
	analogWrite(7, analogRead(potPin) / 4);
}
