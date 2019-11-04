#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

#include "midi.h"
using namespace midi;

const Note scale[] = {
  C3, D3, E3, F3, G3, midi::A3, B3, C4,
};

const Chord major[] = {
  Chord(B2-1) & Chord(D3) & Chord(F3),
//  {F3, midi::A3, C3},
//  {C3, E3, G3},
//  {G3, B3, D3}
};

AudioControlSGTL5000 shield;
AudioSynthWaveform wave[4];
AudioEffectEnvelope env[4];
AudioMixer4 mixer;
AudioOutputI2S out;

AudioConnection patches[] = {
  AudioConnection(wave[0], 0, env[0], 0),
  AudioConnection(wave[1], 0, env[1], 0),
  AudioConnection(wave[2], 0, env[2], 0),
  AudioConnection(wave[3], 0, env[3], 0),

  AudioConnection(env[0], 0, mixer, 0),  
  AudioConnection(env[1], 0, mixer, 1),  
  AudioConnection(env[2], 0, mixer, 2),  
  AudioConnection(env[3], 0, mixer, 3),

  AudioConnection(mixer, 0, out, 0),
  AudioConnection(mixer, 0, out, 1),  
};

void setup() {
  Serial.begin(9600);
  AudioMemory(20);

  for(int i = 0; i < 4; i++) {
    wave[i].amplitude(1.0);
    wave[i].frequency(scale[i].frequency());
    wave[i].begin(WAVEFORM_SAWTOOTH);

    env[i].sustain(1.0);
    env[i].release(10);
    
    mixer.gain(i, 0.2);
  }
  
  shield.enable();
  shield.volume(0.25);
}

#define LENGTH(x) (sizeof(x)/sizeof(x[0]))

void loop() {
  for (unsigned i = 0; i < LENGTH(env); i++) {
    env[i].noteOn();
    delay(200);
    env[i].noteOff();
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
