/*
 * TwoTrackController.cpp
 *
 *  Created on: Apr 8, 2010
 *      Author: frankw
 */

#include "WProgram.h"
#include "TwoTrackController.h"

TwoTrackController::TwoTrackController() {
	pinMode(0, INPUT);
	pinMode(6, OUTPUT);
	pinMode(10, OUTPUT);
	pinMode(9, OUTPUT);
}
void TwoTrackController::update(long millis) {
	int freq = analogRead(0) / 128;
	if (freq < 1)
		freq = 1;
	//TCCR2B = (TCCR2B & 0xF8) | (freq & 0x07);
	//Serial.println(freq);

	int speed = analogRead(0) / 4;
	analogWrite(6, speed);
	analogWrite(10, speed);
	analogWrite(9, speed);
}
