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

