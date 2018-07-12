/*
 * LocomotiveController.h
 *
 *  Created on: Mar 8, 2010
 *      Author: frankw
 */

#ifndef LOCOMOTIVECONTROLLER_H_
#define LOCOMOTIVECONTROLLER_H_

#include "device/Locomotive.h"

class LocomotiveController {
private:
	Locomotive locomotive;
	int potPin;
public:
	LocomotiveController(int speedPin, int potPin);
	void update(long millis);
};

#endif /* LOCOMOTIVECONTROLLER_H_ */
