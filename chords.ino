#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

#include "midi.h"
using namespace midi;

#include "sound.h"
using namespace sound;

const Chord major[] = {
  Chord::major(B2-1),
//  {F3, midi::A3, C3},
//  {C3, E3, G3},
//  {G3, B3, D3}
};

AudioControlSGTL5000 shield;
Reed reeds[] = {
  Reed(C3),
  Reed(E3),
  Reed(F3),
  Reed(G3),
};
AudioMixer4 mixer;
AudioOutputI2S out;

AudioConnection patches[] = {
  AudioConnection(reeds[0].env, 0, mixer, 0),  
  AudioConnection(reeds[1].env, 0, mixer, 1),  
  AudioConnection(reeds[2].env, 0, mixer, 2),  
  AudioConnection(reeds[3].env, 0, mixer, 3),

  AudioConnection(mixer, 0, out, 0),
  AudioConnection(mixer, 0, out, 1),  
};

#define LENGTH(x) (sizeof(x)/sizeof(x[0]))

void setup() {
  Serial.begin(9600);
  AudioMemory(20);

  float reedGain = 0.8/LENGTH(reeds);
  for(unsigned i = 0; i < LENGTH(reeds); i++) {    
    mixer.gain(i, reedGain);
  }
  
  shield.enable();
  shield.volume(0.25);
}


void loop() {
  for (unsigned i = 0; i < LENGTH(reeds); i++) {
    reeds[i].noteOn();
    delay(200);
    reeds[i].noteOff();
    delay(200);    
  }
  
//  for (unsigned int i = 0; i < LENGTH(major); i++) {
//    wave1.frequency((major[i][0]-12).frequency());    
//    wave2.frequency(major[i][1].frequency());
//    wave3.frequency(major[i][2].frequency());
//
//    wave2.amplitude(0);
//    wave3.amplitude(0);
//
//    env.noteOn();
//    delay(200);
//    env.noteOff();
//    delay(200);    
//
//    wave1.frequency(major[i][0].frequency());    
//    wave2.amplitude(1.0);
//    wave3.amplitude(1.0);
//
//    env.noteOn();
//    delay(200);
//    env.noteOff();
//    delay(200);        
//  }
}
