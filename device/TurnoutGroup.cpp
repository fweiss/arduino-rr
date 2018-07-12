/*
 * TurnoutGroup.cpp
 *
 *  Created on: Apr 16, 2010
 *      Author: frankw
 */

#include "TurnoutGroup.h"
#include "WProgram.h"


TurnoutGroup::TurnoutGroup() {
	this->a0Pin = 40;
	this->a1Pin = 41;
	this->a2Pin = 42;
	this->enPin = 43;
	pinMode(this->a0Pin, OUTPUT);
	pinMode(this->a1Pin, OUTPUT);
	pinMode(this->a2Pin, OUTPUT);
	pinMode(this->enPin, OUTPUT);
	activeTurnout = 0;
	activePosition = 0;
	pulseStart = 0;
	clearQueue();

	for (int i = 0; i<4; i++) {
		turnouts[i].group = this;
		turnouts[i].index = i;
	}
}
/**
 * Determine if the active request has timed out (completed).
 * If so, check if there are any enqueued requests.
 * If there are, remove one from the queue and make it the new active request.
 * Start the new active request.
 */
void TurnoutGroup::update(long millis) {
	if (!isActive()) {
		if (isQueueEmpty()) {
			digitalWrite(enPin, LOW);
			pulseStart = 0;
		} else {
			activateNextRequest();
		}
	}
}
bool TurnoutGroup::isActive() {
	return pulseStart != 0 && millis() - pulseStart < pulseWidth;
}
void TurnoutGroup::activateNextRequest() {
	if (!isActive() && !isQueueEmpty()) { // safety guard
		activeTurnout = findEnqueuedTurnout();
		activePosition = dequeueRequest(activeTurnout);

		digitalWrite(enPin, LOW); // deglitch to be nice
		setAddress(activeTurnout);
		digitalWrite(a0Pin, activePosition);
		pulseStart = millis();
		digitalWrite(enPin, HIGH);
	}
}
void TurnoutGroup::setAddress(int index) {
	digitalWrite(this->a1Pin, ((index >> 0) & 1) ? HIGH : LOW);
	digitalWrite(this->a2Pin, ((index >> 1) & 1) ? HIGH : LOW);
}
/**
 * Enqueue a request to set the given turnout to the given position.
 * The given request is ignored if an identical request is currently being executed.
 * The given request replaces an existing enqueued request for the identical turnout,
 * regardless if the enqueued request is for a different position.
 *
 * Consequently there can only be four enqueued requests.
 *
 * If there is no active requests, remove an enqueued request, make it the new
 * active request, and start it.
 */
void TurnoutGroup::setPosition(int turnout, int position) {
	if (isActive()) {
		bool match = turnout == activeTurnout && position == activePosition;
		if (match) {
			return;
		}
	}
	enqueueRequest(turnout, position);
	// this is dangerous if update is never called!
	//if (!isActive()) {
	//	activateNextRequest();
	//}
}
// queue-ness
void TurnoutGroup::clearQueue() {
	requests[0] = false;
	requests[1] = false;
	requests[2] = false;
	requests[3] = false;
}
bool TurnoutGroup::isQueueEmpty() {
	return !(requests[0] || requests[1] || requests[2] || requests[3]);
}
void TurnoutGroup::enqueueRequest(int turnout, int position) {
	if (turnout >= 0 && turnout < 4) { // array index guard
		requests[turnout] = true;
		positions[turnout] = position;
	}
}
// returns the position, assumes caller called findEnqueuedTurnout
int TurnoutGroup::dequeueRequest(int turnout) {
	if (turnout >= 0 && turnout < 4) { // array index guard
		requests[turnout] = false;
	}
	return positions[turnout];
}
// order is arbitrary, default is 3, caller should use isQueusEmpty guard
int TurnoutGroup::findEnqueuedTurnout() {
	return requests[0] ? 0 : (requests[1] ? 1 : (requests[2] ? 2 : 3));
}
