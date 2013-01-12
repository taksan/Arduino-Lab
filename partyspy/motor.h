class Motor {
    int bit0;
    int bit1;
public:
    Motor(int aBit0, int aBit1):bit0(aBit0), bit1(aBit1) {
        pinMode(bit0, OUTPUT);
        pinMode(bit1, OUTPUT);
    }   

    void clockwise() {
        digitalWrite(bit0, LOW);
        digitalWrite(bit1, HIGH);
    }   

    
    void counterclockwise() {
        digitalWrite(bit0, HIGH);
        digitalWrite(bit1, LOW);
    }   

    void stop() {
        digitalWrite(bit0, LOW);
        digitalWrite(bit1, LOW);

    }   
};
