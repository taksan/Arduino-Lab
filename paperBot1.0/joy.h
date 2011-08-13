class Angle {
public:
	Angle() {
		angle = 0;
	}
	void inc() {
		set(angle+1);
	}

	void dec() {
		set(angle-1);
	}

	void set(int anAngle) {
		angle = anAngle;
		if (angle > 180)
			angle = 180;
		if (angle < 0)
			angle = 0;
	}

	int get() {
		return angle;
	}
private:
	int angle;
};

class Joy {
public:
	Joy(){
		nunchuck = new Nunchuck();
		nunchuck->begin();
	}

	void update() {
		nunchuck->update();
	}

	boolean upJoy() {
		return nunchuck->readJoyY() == 255;
	}

	boolean downJoy() {
		return nunchuck->readJoyY() == 0;
	}

	boolean leftJoy() {
		return nunchuck->readJoyX() == 0;
	}

	boolean rightJoy() {
		return nunchuck->readJoyX() == 255;
	}

	boolean cPressed() {
		return nunchuck->cPressed();
	}

	boolean zPressed() {
		return nunchuck->zPressed();
	}

private:
	Nunchuck * nunchuck;
};

