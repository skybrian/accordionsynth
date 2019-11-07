#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

#include "midi.h"
using namespace midi;

#include "sound.h"
using namespace sound;

const Chord song[] = {
  Chord::octave(B2-1),
  Chord::major(B2-1),
  Chord::major(B2-1),
  Chord::octave(F2),
  Chord::major(F2),
  Chord::major(F2),
  Chord::octave(C2),
  Chord::major(C2),
  Chord::major(C2),
  Chord::octave(G2),
  Chord::major(G2),
  Chord::major(G2),
};

AudioControlSGTL5000 shield;
Bank lowBank(G2);
Bank highBank(E3);
AudioMixer4 mixer;
AudioOutputI2S out;

AudioConnection patches[] = {
  AudioConnection(lowBank.mixer, 0, mixer, 0),
  AudioConnection(highBank.mixer, 0, mixer, 1),
  AudioConnection(mixer, 0, out, 0),
  AudioConnection(mixer, 0, out, 1),
};

#define LENGTH(x) (sizeof(x)/sizeof(x[0]))

void playSong(Bank& bank) {
  for (unsigned i = 0; i < LENGTH(song); i++) {
    auto ch = song[i];
//    ch.printTo(Serial);
//    Serial.println();
    bank.notesOn(ch);
    delay(150);
    bank.notesOff();
    delay(250);
  }  
}

void setup() {
  Serial.begin(9600);
  AudioMemory(40);
  shield.enable();
  shield.volume(0.25);
}

void loop() {
  //playSong(lowBank);
  playSong(highBank);
}
