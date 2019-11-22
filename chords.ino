#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

#include "midi.h"
using namespace midi;

#include "sound.h"
using namespace sound;

#include "key.h"

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

key::Layout stradella_major = {
  {Chord::octave(midi::A2), Chord::octave(E2), Chord::octave(B2)},
  {Chord::octave(F2), Chord::octave(C2), Chord::octave(G2)},
  {Chord::major(F2), Chord::major(C2), Chord::major(G2)},
};

key::Layout stradella_minor = {
  {Chord::octave(F2), Chord::octave(C2), Chord::octave(G2)},
  {Chord::major(F2), Chord::major(C2), Chord::major(G2)},
  {Chord::minor(F2), Chord::minor(C2), Chord::minor(G2)},
};

AudioControlSGTL5000 shield;
Bank lowBank(G2);
Bank highBank(E3);
AudioMixer4 mixer;
AudioOutputI2S out;

AudioConnection patches[] = {
  AudioConnection(lowBank.out(), 0, mixer, 0),
  AudioConnection(highBank.out(), 0, mixer, 1),
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


// Don't use pins already in use by audio shield.
const key::ColumnPins colPins = {18, 19, 9};
const key::RowPins rowPins = {16, 17, 14}; // 13 used, 15 is volume
key::Board keyboard = key::Board(colPins, rowPins);

void setup() {
  Serial.begin(9600);
  AudioMemory(40);
  shield.enable();
  shield.volume(0.25);
  //Serial.println("setting up pins");
  keyboard.setupPins();
  Serial.println("Ready.");
}

void loop() {
  
//  Chord ch = Chord();
//  for (unsigned i = 0; i < LENGTH(buttons); i++) {
//    ch = ch + buttons[i].poll();    
//  }
//  highBank.notesOn(ch);

  Chord next = keyboard.poll(stradella_major);
  highBank.notesOn(next);
  delay(1);  
}
