/*
 * TurnoutGroupController.h
 *
 *  Created on: Apr 9, 2010
 *      Author: frankw
 */

#ifndef TURNOUTGROUPCONTROLLER_H_
#define TURNOUTGROUPCONTROLLER_H_

#include "device/TurnoutGroup.h"

class TurnoutGroupController {
private:
	TurnoutGroup turnout;
	int select;
	long start;
	long delay;
public:
	TurnoutGroupController();
	void update(long millis);
};

#endif /* TURNOUTGROUPCONTROLLER_H_ */
