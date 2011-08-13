#include <notes.h>
#include "buzzer.h"

#define NOTE_TIME 500

Buzzer buzzer(7);

int notes[] = { 
	NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, 0, NOTE_F5, 0, NOTE_F5, 
	NOTE_C5, NOTE_D5, NOTE_C5, NOTE_D5, 0, NOTE_D5, 0, NOTE_D5,
	NOTE_C5, NOTE_G5, NOTE_F5, NOTE_E5, 0, NOTE_E5, 0, NOTE_E5,
	NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, 0, NOTE_F5, 0, NOTE_F5 
};
int noteCount = sizeof(notes)/sizeof(int);
int currentNote = 0;

void setup()
{
	buzzer.playTone(notes[0], NOTE_TIME);
}

void loop()
{
	if (buzzer.tick() == false) {
		currentNote = (currentNote + 1) % noteCount;
		if (currentNote == 0) {
			delay(1000);
		}
		buzzer.playTone(notes[currentNote], NOTE_TIME);
	}
}
