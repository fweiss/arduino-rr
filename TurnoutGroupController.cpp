/*
 * TurnoutGroupController.cpp
 *
 *  Created on: Apr 9, 2010
 *      Author: frankw
 */

#include "WProgram.h"
#include "TurnoutGroupController.h"

TurnoutGroupController::TurnoutGroupController() {
	//pinMode(40, OUTPUT);
	//pinMode(41, OUTPUT);
	//pinMode(42, OUTPUT);
	//pinMode(43, OUTPUT);
	select = 0;
	start = 0;
	delay = 1000;
}
void TurnoutGroupController::update(long millis) {
	/*
	digitalWrite(40, ((select >> 0) & 1) ? HIGH : LOW);
	digitalWrite(41, ((select >> 1) & 1) ? HIGH : LOW);
	digitalWrite(42, ((select >> 2) & 1) ? HIGH : LOW);
	select++;
	digitalWrite(43, HIGH);
	delay(25);
	digitalWrite(43, LOW);
	delay(975);
	*/
	boolean timeout = millis - start > delay;
	if (timeout) {
		int turnoutIndex = (select >> 1) % 4;
		int p1 = TurnoutGroup::LEFT;
		int p2 = TurnoutGroup::RIGHT;
		int position = (select & 0x01) ? p1 : p2;
		select++;
		turnout.setPosition(turnoutIndex, position);
		int n1 = (turnoutIndex + 1) % 4;
		int n2 = position;
		//turnout.setPosition(n1, n2);
		start = millis;
	}
	turnout.update(millis);
}
