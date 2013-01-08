#define BR_1 4
#define BR_2 5
#define BL_1 6
#define BL_2 7
#define TR_1 8
#define TR_2 9
#define TL_1 10
#define TL_2 11

class Wheel {
	int bit0;
	int bit1;
public:
	Wheel(int aBit0, int aBit1):bit0(aBit0), bit1(aBit1) {
		pinMode(bit0, OUTPUT);
		pinMode(bit1, OUTPUT);
	}

	void clockwise() {
		digitalWrite(bit0, HIGH);
		digitalWrite(bit1, LOW);
	}

	void counterclockwise() {
		digitalWrite(bit0, LOW);
		digitalWrite(bit1, HIGH);
	}

	void stop() {
		digitalWrite(bit0, LOW);
		digitalWrite(bit1, LOW);

	}
};

/*
TL[]--------[]TR
  |   ardui  |
  |   btries |
BL[]--------[]BR
*/

Wheel TL(TL_1,TL_2);
Wheel TR(TR_1,TR_2);
Wheel BL(BL_1,BL_2);
Wheel BR(BR_1,BR_2);

void setup()  {
	/*
	Serial.begin(9600);

	*/
	TL.clockwise();
}

void loop()  {
} 
