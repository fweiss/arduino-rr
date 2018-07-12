/*
 * TwoTrack.cpp
 *
 *  Created on: Apr 20, 2010
 *      Author: frankw
 */

#include "TwoTrack.h"

#include "WProgram.h"

TwoTrack::TwoTrack() {
	this->speedAPin = 10;
	this->dirAPin = 12;
	this->speedBPin = 9;
	this->dirBPin = 13;
	pinMode(10, OUTPUT);
	pinMode(9, OUTPUT);
	pinMode(dirBPin, OUTPUT);
}
void TwoTrack::update(long millis) {
	//analogWrite(10, speed);
	//analogWrite(9, speed);
}
void TwoTrack::setSpeed(int speed) {
	analogWrite(10, speed);
	analogWrite(9, speed);
}
void TwoTrack::reverse(bool reverse) {
	digitalWrite(dirAPin, reverse ? HIGH: LOW);
}
