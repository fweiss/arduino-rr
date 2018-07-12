/*
 * BaseController.h
 *
 *  Created on: Mar 12, 2011
 *      Author: frankw
 */

#ifndef BASECONTROLLER_H_
#define BASECONTROLLER_H_

// kind of cheap-ass forward typedef
class BaseController;
typedef void (BaseController::*z)(void);
typedef z (BaseController::*StateMethod)(void);

class BaseController {
public:
	enum State { START, END, DEADMAN_TIMEOUT };
	int state;
	unsigned long deadmanTimeout;
	unsigned long deadmanStart;
	void setState(State state, unsigned long timeout = 10000);
public:
	BaseController();
	virtual const char* getName();
	virtual void setup();
	virtual void update(unsigned long millis);
	void heartbeat();
	bool switchPressed(int pin, unsigned long& state);
};

#endif /* BASECONTROLLER_H_ */
