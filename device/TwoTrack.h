/*
 * TwoTrack.h
 *
 *  Created on: Apr 20, 2010
 *      Author: frankw
 */

#ifndef TWOTRACK_H_
#define TWOTRACK_H_

class TwoTrack {
private:
	int speedAPin;
	int dirAPin;
	int speedBPin;
	int dirBPin;
public:
	TwoTrack();
	void update(long millis);
	void setSpeed(int speed);
	void reverse(bool reverse = true);
};

#endif /* TWOTRACK_H_ */
