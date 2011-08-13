#define WRONG_LED 2
#define RIGHT_LED 3
#define SEQUENCE_INTERVAL 400

class Genius { 
private:
  Led wrongLed;
  Led rightLed;  
  Led * gameLeds;
  Button * gameButtons;
  int buttonCount;
  
  int * sequence;
  int sequenceSize;
  int nextSequenceIndex;
  int sequenceInterval;
  
  boolean gameIsOver;
public:  
  
  Genius(Led leds[], Button buttons[], int aButtonCount):
    wrongLed(WRONG_LED),
    rightLed(RIGHT_LED)
  {
    gameLeds = leds;
    gameButtons = buttons;
    buttonCount = aButtonCount;
    
    sequenceInterval = SEQUENCE_INTERVAL;
  }
  
  void start(int seqSize) {
    gameIsOver = false;
    rightLed.turnOff();
    wrongLed.turnOff();
    
    nextSequenceIndex = 0;

    sequenceSize = seqSize;
    sequence = (int*)malloc(sizeof(int)*seqSize);

    for (int i=0; i < seqSize; i++) {
      sequence[i] = random(0,buttonCount);
    }
    
    playSequence(sequence, sequenceSize);
  }
  
  void playSequence(int sequence[], int seqSize) {
    for(int i=0; i < seqSize; i++) {
      int seqLed = sequence[i];
      gameLeds[seqLed].turnOn();
      sequenceWait();
      gameLeds[seqLed].turnOff();
      sequenceWait();
    }
  }
  
  void sequenceWait() {
    delay(sequenceInterval);
  }

  void verifyButtons() {     
    for (int i=0; i < buttonCount; i++) {
      if (gameButtons[i].isPressed()) {
        gameLeds[i].turnOnAndHoldUntilExpired(BUTTON_MIN_DELAY);
      }
      
      if (gameButtons[i].wasPushed()){
        guessNextSequenceLed(i);
      }
      
      if (!gameButtons[i].isPressed()) {
        gameLeds[i].turnOffIsTimeExpired();
      }
    }
    if (gameIsOver) {
      start(sequenceSize);
    }
  }
  
  void guessNextSequenceLed(int next){
    int nextSequence = sequence[nextSequenceIndex++];
    
    if (next != nextSequence){
      gameOver(false);
    }
    if (nextSequenceIndex == sequenceSize) {
      gameOver(true);
    }
  }
  
  void gameOver(boolean won) {
    if (gameIsOver)
      return;
    if (won) {
      rightLed.turnOn();
      sequenceSize++;
    }
    else {
      wrongLed.turnOn();
      if (sequenceSize > 2) {
        sequenceSize--;
      }
    }
      
    delay(2000);
    gameIsOver = true;
  }
};
