#include "WProgram.h"
extern "C" void __cxa_pure_virtual()
{
    // Do nothing or print an error message.
}
int main(void)
{
	init();
	setup();
	for (;;) {
		loop();
	}
	return 0;
}
