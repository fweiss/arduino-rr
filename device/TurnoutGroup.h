/*
 * TurnoutGroup.h
 *
 *  Created on: Apr 16, 2010
 *      Author: frankw
 */

#ifndef TURNOUTGROUP_H_
#define TURNOUTGROUP_H_

#include "Turnout.h"

class TurnoutGroup {
private:
	static const unsigned long pulseWidth = 25;
	int a0Pin;
	int a1Pin;
	int a2Pin;
	int enPin;
	int activePosition;
	int activeTurnout;
	unsigned long pulseStart;
	void setAddress(int index);
	bool isActive();
	void activateNextRequest();
	// queue-ness
	void enqueueRequest(int turnout, int position);
	int dequeueRequest(int turnout);
	int findEnqueuedTurnout();
	bool isQueueEmpty();
	void clearQueue();
	int requests[4];
	int positions[4];

	class InnerTurnout;
	class InnerTurnout : public Turnout {
		friend class TurnoutGroup;
	private:
		TurnoutGroup* group;
		int index;
	public:
		void setPosition(int position) {
			group->setPosition(index, position);
		}
	};
	InnerTurnout turnouts[4];
public:
	static const int LEFT = 0;
	static const int RIGHT = 1;
	TurnoutGroup();
	void update(long millis);
	void setPosition(int index, int position);
	Turnout& getTurnout(int index) {
		return turnouts[index];
	}
};

#endif /* TURNOUTGROUP_H_ */
