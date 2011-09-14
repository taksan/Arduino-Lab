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

	int16_t get() {
		return angle;
	}
private:
	int16_t angle;
};


