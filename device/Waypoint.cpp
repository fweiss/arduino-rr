/*
 * Location.cpp
 *
 *  Created on: Mar 13, 2010
 *      Author: frankw
 */

#include "Waypoint.h"
#include "WProgram.h"

Waypoint::Waypoint(const char* name, int sensorPin) {
	this->sensorPin = sensorPin;
	this->covered = false;
	this->previousCovered = false;
	this->startMillis = 0;
	this->inThreshold = 512;
	this->outThreshold = 100;
	this->calibrationLevel = 0;
	this->offDelay = 100;
	pinMode(this->sensorPin, INPUT);
}
void Waypoint::update(long millis) {
	previousCovered = covered;
	int value = analogRead(sensorPin);
	//boolean in = value >= inThreshold;
	//boolean out = value < outThreshold;
	boolean in = value > calibrationLevel + 100;
	boolean out = value < calibrationLevel + 80;;
	if (in) {
		startMillis = millis;
		covered = true;
	} else if (out && millis - startMillis > offDelay) {
		covered = false;
	}
}
char Waypoint::isCovered() {
	return this->covered;
}
char Waypoint::beingCovered() {
	return covered && (! previousCovered);
}
char Waypoint::beingUncovered() {
	return (!covered) && previousCovered;
}
void Waypoint::setThresholds(int in, int out) {
	this->inThreshold = in;
	this->outThreshold = out;
}
void Waypoint::calibrate() {
	calibrationLevel = analogRead(sensorPin);
}
void Waypoint::setOffDelay(unsigned long delay) {
	this->offDelay = delay;
}
