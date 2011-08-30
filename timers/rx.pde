
long freq_counter;
void setup()
{
	Serial.begin(9600);    

	freq_counter=0;

    TIMSK2 &= ~_BV(OCIE2B); 

    OCR2B = 125;
    TCCR2A = 0;
    TCCR2B = _BV(CS21); // set prescaler to 8
    TCNT2 = 0;     
    TIFR2 = _BV(OCF2B);  // clear pending interrupts; 
    TIMSK2 |= _BV(OCIE2B); // enable the compare interrupt

	// expected frequency: 16khz
}

ISR(TIMER2_COMPB_vect)
{
	freq_counter++;
}

void loop()
{
	delay(1000);
	Serial.println(freq_counter);
}
