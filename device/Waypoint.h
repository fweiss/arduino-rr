/*
 * Location.h
 *
 *  Created on: Mar 13, 2010
 *      Author: frankw
 */

#ifndef LOCATION_H_
#define LOCATION_H_

class Waypoint {
private:
	int sensorPin;
	char previousCovered;
	char covered;
	unsigned long startMillis;
	unsigned long offDelay;
	int inThreshold;
	int outThreshold;
	int calibrationLevel;
public:
	Waypoint(const char* name, int sensorPin);
	void update(long millis);
	char isCovered();
	char beingCovered();
	char beingUncovered();
	void setThresholds(int in, int out);
	void calibrate();
	void setOffDelay(unsigned long delay);
};

#endif /* LOCATION_H_ */
