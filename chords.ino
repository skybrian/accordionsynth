#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

#include "midi.h"
using namespace midi;

#include "sound.h"
using namespace sound;

const Chord song[] = {
  Chord(B2-1),
  Chord::major(B2-1),
  Chord::major(B2-1),
  Chord(F3),
  Chord::major(F3),
  Chord::major(F3),
  Chord(C3),
  Chord::major(C3),
  Chord::major(C3),
  Chord(G3),
  Chord(D3, G3, B3),
  Chord(D3, G3, B3),
};

AudioControlSGTL5000 shield;
Bank bank(B2-1);
AudioOutputI2S out;

AudioConnection patches[] = {
  AudioConnection(bank.mixer, 0, out, 0),
  AudioConnection(bank.mixer, 0, out, 1),
};

#define LENGTH(x) (sizeof(x)/sizeof(x[0]))

void setup() {
  Serial.begin(9600);
  AudioMemory(20);
  shield.enable();
  shield.volume(0.25);
}


void loop() {
  for (unsigned i = 0; i < LENGTH(song); i++) {
    bank.notesOn(song[i]);
    delay(100);
    bank.notesOff();
    delay(300);
  }
}
