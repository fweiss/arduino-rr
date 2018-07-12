/*
 * Turnout.h
 *
 *  Created on: Mar 4, 2010
 *      Author: frankw
 */

#ifndef SIMPLETURNOUT_H_
#define SIMPLETURNOUT_H_

class SimpleTurnout {
private:
	int leftPin;
	int rightPin;
	int position;
	long pulseWidth;
	long pulseStart;
public:
	static const int LEFT = 0;
	static const int RIGHT = 1;
	SimpleTurnout(const char* name, int leftPin, int rightPin);
	void update(long millis);
	void setPosition(int position);
	int getPosition();
};

#endif /* SIMPLETURNOUT_H_ */
