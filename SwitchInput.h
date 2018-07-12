/*
 * SwitchInput.h
 *
 *  Created on: Mar 4, 2010
 *      Author: frankw
 */

#ifndef SWITCHINPUT_H_
#define SWITCHINPUT_H_

class SwitchInput {
private:
	int pin;
	long lastPress;
	int lastState;
	static const int debounce = 10;
public:
	SwitchInput(const char* name, int pin);
	void update(unsigned long millis);
	int isClicked();
};

#endif /* SWITCHINPUT_H_ */
