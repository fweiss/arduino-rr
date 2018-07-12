#include "Blink.h"
#include "WProgram.h"

Blink::Blink(int pin, int period) {
	this->pin = pin;
	this->period = period;
	pinMode(pin, OUTPUT);

}
//Blink::~Blink() {
//	// TODO Auto-generated destructor stub
//}
void Blink::update(long millis) {
	long res = millis % period;
	boolean on = res > (period / 2);
	digitalWrite(pin, on ? HIGH : LOW);
}
