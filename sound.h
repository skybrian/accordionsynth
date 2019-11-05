#include "midi.h"
#include <Audio.h>
#include <AudioStream.h>

namespace sound {

class Reed {
public:
  Reed(midi::Note n) : note(n) {
    wave.amplitude(1.0);
    wave.frequency(n.frequency());
    env.sustain(1.0);
    env.release(10);
  }

  void begin() {
    wave.begin(WAVEFORM_SAWTOOTH);    
  }

  void noteOn() {
    env.noteOn();
  }

  void noteOff() {
    env.noteOff();
  }

  AudioEffectEnvelope env;
  midi::Note note;
private:
  AudioSynthWaveform wave;
  AudioConnection patch = AudioConnection(wave, 0, env, 0);
};

#if !defined(__ARM_ARCH_7EM__)
#error "BigMixer not implemented for this platform"
#endif

#define MIXER_SIZE 12

class BigMixer : public AudioStream
{
public:
  BigMixer() : AudioStream(MIXER_SIZE, inputQueueArray) {
    for (int i=0; i<MIXER_SIZE; i++) {
      multiplier[i] = 65536;
    }
  }

  virtual void update(void);

  void gain(unsigned int channel, float gain) {
    if (channel >= MIXER_SIZE) return;
    if (gain > 32767.0f) gain = 32767.0f;
    else if (gain < -32767.0f) gain = -32767.0f;
    multiplier[channel] = gain * 65536.0f; // TODO: proper roundoff?
  }
  
private:
  int32_t multiplier[MIXER_SIZE];
  audio_block_t *inputQueueArray[MIXER_SIZE];
};

#define BANK_SIZE MIXER_SIZE

struct ReedBank {
  Reed at[BANK_SIZE];
};

class Bank {
private:
  static ReedBank makeReeds(midi::Note n) {
    ReedBank reeds = {{
      Reed(n), Reed(n+1), Reed(n+2), Reed(n+3), Reed(n+4), Reed(n+5),
      Reed(n+6), Reed(n+7), Reed(n+8), Reed(n+9), Reed(n+10), Reed(n+11)
    }};
    return reeds;
  }

public:
  Bank(midi::Note n) : reeds(makeReeds(n)) {
    for (int i = 0; i < BANK_SIZE; i++) {
      reeds.at[i].begin();
    }
  }

  void notesOn(midi::Chord chord) {
    int noteCount = 0;
    for (int i = 0; i<BANK_SIZE; i++) {
      if (chord.has(reeds.at[i].note)) {
        reeds.at[i].noteOn();
        noteCount++;
      } else {
        reeds.at[i].noteOff();
      }
    }
    if (noteCount > 0) {
      float gain = 0.8/noteCount;
      for (int i = 0; i<BANK_SIZE; i++) {
        mixer.gain(i, gain);
      }
    }
  }

  void notesOff() {
    notesOn(midi::Chord());
  }
  
  BigMixer mixer;
private:
  ReedBank reeds;
  AudioConnection patch1 = AudioConnection(reeds.at[0].env, 0, mixer, 0);
  AudioConnection patch2 = AudioConnection(reeds.at[1].env, 0, mixer, 1);
  AudioConnection patch3 = AudioConnection(reeds.at[2].env, 0, mixer, 2);
  AudioConnection patch4 = AudioConnection(reeds.at[3].env, 0, mixer, 3);
  AudioConnection patch5 = AudioConnection(reeds.at[4].env, 0, mixer, 4);
  AudioConnection patch6 = AudioConnection(reeds.at[5].env, 0, mixer, 5);
  AudioConnection patch7 = AudioConnection(reeds.at[6].env, 0, mixer, 6);
  AudioConnection patch8 = AudioConnection(reeds.at[7].env, 0, mixer, 7);
  AudioConnection patch9 = AudioConnection(reeds.at[8].env, 0, mixer, 8);
  AudioConnection patch10 = AudioConnection(reeds.at[9].env, 0, mixer, 9);
  AudioConnection patch11 = AudioConnection(reeds.at[10].env, 0, mixer, 10);
  AudioConnection patch12 = AudioConnection(reeds.at[11].env, 0, mixer, 11);
};

} // namespace
