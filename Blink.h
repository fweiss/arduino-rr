#ifndef BLINK_H_
#define BLINK_H_

class Blink {
private:
	int pin;
	int period;
public:
	Blink(int pin, int rate);
	//virtual ~Blink();
	void update(long millis);
};

#endif /* BLINK_H_ */
