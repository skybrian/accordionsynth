#ifndef BUTTON_H_
#define BUTTON_H_

#include "midi.h"

namespace button {

class Debouncer {
public:
  constexpr Debouncer() : interval(5) {}

  bool filter(bool isDown) {
    // debounce
    if (isDown != wasDown) {
      lastChangeTime = millis();
      wasDown = isDown;
    } else if (isDown != playing && ((millis() - lastChangeTime) > interval)) {
      playing = isDown;
    }    

    return playing;    
  }

private:
  unsigned interval;
  bool wasDown = false;
  unsigned long lastChangeTime = 0;
  bool playing = false;  
};

class Button {
public:
  Button(int inputPin, Chord toPlay) : pin(inputPin), ch(toPlay) {}

  void setup() {
      pinMode(pin, INPUT_PULLUP);
  }

  Chord poll() {
    bool isDown = digitalRead(pin)==LOW;
    return debouncer.filter(isDown) ? ch : Chord();    
  }

private:
  int pin;
  Chord ch;
  Debouncer debouncer;
};

} // end namespace
#endif 
