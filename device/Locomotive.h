/*
 * Locomotive.h
 *
 *  Created on: Mar 6, 2010
 *      Author: frankw
 */

#ifndef LOCOMOTIVE_H_
#define LOCOMOTIVE_H_

class Locomotive {
private:
	int speedPin;
	int directionPin;
	float requestedSpeed;
	float lastSpeed;
	unsigned long lastTime;
	unsigned long startDelta;
	unsigned long stopDelta;
	int mode;
public:
	enum Direction { FORWARD = 0, REVERSE = 1 };
	Locomotive(const char* name, int speedPin, int directionPin);
	void setDirection(Direction direction);
	void setRequestedSpeed(int speed);
	void update(long millis);
	int getLastSpeed();
	static const int RUN = 0;
	static const int STOP = 1;
	void stop();
};

#endif /* LOCOMOTIVE_H_ */
