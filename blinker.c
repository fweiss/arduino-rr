#include "WProgram.h"
#include "device/Turnout.h"
#include "TurnoutController.h"
#include "LocomotiveController.h"
#include "AriesController.h"
#include "TwoTrackController.h"
#include "TurnoutGroupController.h"
#include "controller/TaurusController.h"
#include "controller/GeminiController.h"
#include "controller/CouplerTestController.h"

//Turnout turnout("turnout", 40, 41);
//Turnout turnout("turnout", 6, 7);

//TurnoutController controller(6, 7)
//TurnoutController tcController(40, 41);
//LocomotiveController controller(9, 0);
//AriesController aries(3);
//TwoTrackController twoTrack;
//TurnoutGroupController toGroup;
//TaurusController taurus;
//GeminiController gemini;
CouplerTestController controller;

void setup() {
	Serial.begin(9600);	// opens serial port, sets data rate to 9600 bps
	// increase clock speed to eliminate motor buzz
	//TCCR1B &= ~ (1<<CS11);
	//TCCR2B &= ~ (1<<CS22);
	//TCCR2B |=  (1<<CS20);
	TCCR2B = (TCCR2B & 0xF8) | 7; // two track
	//TCCR2B = (TCCR2B & 0xF8) | 1; // aries
	controller.setup();
}
void loop() {
	//controller.update(millis());
	//tcController.update(millis());
	//aries.update(millis());
	//toGroup.update(millis());
	//twoTrack.update(millis());
	//taurus.update(millis());
	//gemini.update(millis());
	controller.update(millis());
}
