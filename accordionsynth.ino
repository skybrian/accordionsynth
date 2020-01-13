#include <Audio.h>
#include <Metro.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

#include "midi.h"
using namespace midi;

#include "sound.h"
using namespace sound;

#include "key.h"

const Chord startSong[] = {
  Chord(F3),
  Chord(midi::A3),
  Chord(C4),
  Chord::majorUp(F3)
};

// Uses notes from E3 to D#4
key::Layout highStradella = {{
  {Chord(midi::A3), Chord(E3), Chord(B3), Chord(F3+1)}, // counterbass row
  {Chord(F3), Chord(C4), Chord(G3), Chord(D4)}, // bass row
  {Chord::majorUp(F3), Chord::majorDown(C4), Chord::majorUp(G3), Chord::majorDown(D4)}, // major chord row
  {Chord::minorUp(F3), Chord::minorMid(C4), Chord::minorUp(G3), Chord::minorDown(D4)} // minor chord row
}};

// Uses bass notes from G1-F#2, chords E3 to D#4
key::Layout lowStradella = {{
  {Chord(midi::A1), Chord(E2), Chord(C2-1), Chord(F2+1)}, // counterbass row
  {Chord(F2), Chord(C2), Chord(G1), Chord(D2)}, // bass row
  {Chord::majorUp(F3), Chord::majorDown(C4), Chord::majorUp(G3), Chord::majorDown(D4)}, // major chord row
  {Chord::minorUp(F3), Chord::minorMid(C4), Chord::minorUp(G3), Chord::minorDown(D4)} // minor chord row
}};

AudioControlSGTL5000 shield;
Bank bank(G1);
AudioFilterBiquad filter;
AudioOutputI2S out;
MidiChannel midiChannel(1);

AudioConnection patches[] = {
  AudioConnection(bank.out(), 0, filter, 0),
  AudioConnection(filter, 0, out, 0),
  AudioConnection(filter, 0, out, 1)
};

#define LENGTH(x) (sizeof(x)/sizeof(x[0]))

// Don't use pins already in use by audio shield.
// We have two boards with different column-enabling pins.
const key::ColumnPins botColPins = {36, 35, 34, 33};
const key::ColumnPins midColPins = {29, 30, 31, 32};

// Read all the same rows for both, but half the rows won't work for each board.
const key::RowPins rowPins = {27, 37, 28, 38};

key::Board bottomBoard = key::Board(botColPins, rowPins);
key::Board middleBoard = key::Board(midColPins, rowPins);

const int led = 13;

const int audioMemory = 20;

void setup() {
  Serial.begin(9600);
  AudioMemory(audioMemory);
  filter.setLowpass(0, 2000, 0.7071);
  filter.setLowpass(1, 2000, 0.7071);
  shield.enable();
  shield.volume(0.8);
  bottomBoard.setupPins();
  middleBoard.setupPins();
  pinMode(led, OUTPUT);

  playStartSong(bank);
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

Metro cpuInterval(10*1000);

void checkProcessorUsage() {
  if (cpuInterval.check()) {
    int usage = AudioProcessorUsageMax();
    if (usage > 90) {
      Serial.print("Processor usage: ");
      Serial.print(usage);
      Serial.print("% Max memory: ");
      Serial.print(AudioMemoryUsageMax());
      Serial.print(" of ");
      Serial.println(audioMemory);
      AudioProcessorUsageMaxReset();
    }
    cpuInterval.reset();
  }
}

key::Layout layout = lowStradella;

void loop() {
  Chord next = bottomBoard.poll(layout) + middleBoard.poll(layout);
  bank.notesOn(next);
  midiChannel.send(next);
  while (usbMIDI.read()) {} // discard incoming
  checkProcessorUsage();
  delay(1);
}
