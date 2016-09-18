#include <ServoTimer2.h>
#include <SerialDebug.h>

#define Servo ServoTimer2

class BotMoveAction {
	Servo * motor;
	int angle;
	uint32_t expiration; 
	uint32_t delay;
public:
	char name[10];
	BotMoveAction() { }

	void set(const char* name, Servo * motor, int angle, int delay) {
		this->expiration = 0;
		this->motor = motor;
		this->angle = angle;
		this->delay = delay;
		sprintf(this->name, "%s", name);
	}

	uint32_t getDelay() {
		return delay;
	}

	void execute() {
		if (expiration > 0) return;
		SerialDebug::println("executing [%s] angle: %d", name, angle);
		motor->write(angle);
		this->expiration = millis() + delay;
	}

	bool isExpired() {
		if (expiration == 0) return false;
		return millis() > expiration;
	}
};

class MoveQueue {
	BotMoveAction moveQueue[10];
	int queueIni, queueEnd;
public:
	MoveQueue() {
		queueIni = 0;
		queueEnd = 0;
	}

	bool hasElements() {
		return queueIni != queueEnd;
	}

	void add(const char * name, Servo * m, int angle, int delay) {
		int n = (queueEnd + 1) % 10;
		if (n == queueEnd)//queue full
			return;

		SerialDebug::println("[%d] adding [%s] angle: %d delay:%d", queueEnd, name, angle, delay);
		moveQueue[queueEnd].set(name, m, angle, delay);
		queueEnd = n;
	}

	void dequeue() {
		if (!hasElements()) // queue empty
			return;
		queueIni = (queueIni + 1) % 10;
	}

	BotMoveAction * head() {
		if (!hasElements())
			return NULL;
		return &(moveQueue[queueIni]);
	}

	void clear() {
		queueIni = queueEnd = 0;
	}
};

