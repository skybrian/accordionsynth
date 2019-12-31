#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

#include "midi.h"
using namespace midi;

#include "sound.h"
using namespace sound;

#include "key.h"

const Chord startSong[] = {
  Chord::octave(F2),
  Chord::octave(midi::A2),
  Chord::octave(C2),
  Chord::major(F2)
};

key::Layout middleLayout = {
  {Chord::octave(midi::A2), Chord::octave(E2), Chord::octave(B2), Chord::octave(F2+1)}, // counterbass row
  {Chord::major(F2), Chord::major(C2), Chord::major(G2), Chord::major(D2)} // major chord row
};

key::Layout bottomLayout = {
  {Chord::octave(midi::F2), Chord::octave(C2), Chord::octave(G2), Chord::octave(D2)}, // bass row
  {Chord::minor(F2), Chord::minor(C2), Chord::minor(G2), Chord::minor(D2)} // minor chord row
};

AudioControlSGTL5000 shield;
Bank lowBank(G2);
Bank highBank(E3);
AudioMixer4 mixer;
AudioOutputI2S out;
MidiChannel midiChannel(1);

AudioConnection patches[] = {
  AudioConnection(lowBank.out(), 0, mixer, 0),
  AudioConnection(highBank.out(), 0, mixer, 1),
  AudioConnection(mixer, 0, out, 0),
  AudioConnection(mixer, 0, out, 1),
};

#define LENGTH(x) (sizeof(x)/sizeof(x[0]))

// Don't use pins already in use by audio shield.
const key::ColumnPins botColPins = {36, 35, 34, 33};
const key::RowPins botRowPins = {37, 38};

const key::ColumnPins midColPins = {29, 30, 31, 32};
const key::RowPins midRowPins = {27, 28};

key::Board bottomBoard = key::Board(botColPins, botRowPins);
key::Board middleBoard = key::Board(midColPins, midRowPins);

const int led = 13;

void setup() {
  Serial.begin(9600);
  AudioMemory(20);
  shield.enable();
  shield.volume(0.8);
  bottomBoard.setupPins();
  middleBoard.setupPins();
  pinMode(led, OUTPUT);

  playStartSong(highBank);
  Serial.print("Ready.\nAudio memory used: ");
  Serial.print(AudioMemoryUsageMax());
  Serial.print(" blocks.\nProcessor usage: ");
  Serial.print(AudioProcessorUsageMax());
  Serial.println("%");
}

void playStartSong(Bank& bank) {
  for (unsigned i = 0; i < LENGTH(startSong); i++) {
    Chord ch = startSong[i];
//    ch.printTo(Serial);
//    Serial.println();

    digitalWrite(led, HIGH);
    bank.notesOn(ch);
    delay(300);
    bank.notesOff();
    digitalWrite(led, LOW);
    delay(100);
  }  
}

void loop() {
  Chord next = bottomBoard.poll(bottomLayout) + middleBoard.poll(middleLayout);
  highBank.notesOn(next);
  midiChannel.send(next);
  while (usbMIDI.read()) {} // discard incoming
  delay(1);  
}
