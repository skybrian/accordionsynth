#include "midi.h"

#define DEBOUNCE_MS 5

class Button {
public:
  Button(int inputPin, Chord toPlay) : pin(inputPin), ch(toPlay) {}

  void setup() {
      pinMode(pin, INPUT_PULLUP);
  }

  Chord poll() {
    bool isDown = digitalRead(pin)==LOW;
    
    // debounce
    if (isDown != wasDown) {
      lastChangeTime = millis();
      wasDown = isDown;
    } else if (isDown != playing && ((millis() - lastChangeTime) > DEBOUNCE_MS)) {
      playing = isDown;
    }    

    return playing ? ch : Chord();
  }

private:
  int pin;
  Chord ch;
  bool wasDown = false;
  unsigned long lastChangeTime = 0;
  bool playing;
};
