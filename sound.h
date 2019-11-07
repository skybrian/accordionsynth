#include "midi.h"
#include <Audio.h>
#include <AudioStream.h>

namespace sound {

#define WAVE_COUNT 4
const float harmonics[WAVE_COUNT] = {0.5, 1.0, 1.0, 0.05};

class Reed {
public:
  Reed(midi::Note n) : note(n) {
    float mixedAmp = 0;
    for (int i = 0; i < WAVE_COUNT; i++) {
      waves[i].amplitude(harmonics[i]);
      waves[i].frequency(n.frequency() * (i + 1));
      mixedAmp += harmonics[i];
      env[i].attack(20+i*40);
      env[i].decay(0);
      env[i].sustain(1.0);
      env[i].release(20);
    }
    for (int i = 0; i < WAVE_COUNT; i++) {
      mixer.gain(i, harmonics[i]/mixedAmp);
    }
  }

  void begin() {
    for (int i = 0; i < WAVE_COUNT; i++) {
      waves[i].begin(WAVEFORM_SINE);
    }
  }

  void noteOn() {
    for (int i = 0; i < WAVE_COUNT; i++) {
      env[i].noteOn();
    }
  }

  void noteOff() {
    for (int i = 0; i < WAVE_COUNT; i++) {
      env[i].noteOff();
    }
  }

  AudioStream& out() {
    return mixer; 
  }

  midi::Note note;
private:
  AudioSynthWaveform waves[WAVE_COUNT];
  AudioEffectEnvelope env[WAVE_COUNT];
  AudioMixer4 mixer;
  AudioConnection patches[8] = {
    AudioConnection(waves[0], 0, env[0], 0),
    AudioConnection(waves[1], 0, env[1], 0),
    AudioConnection(waves[2], 0, env[2], 0),
    AudioConnection(waves[3], 0, env[3], 0),
    AudioConnection(env[0], 0, mixer, 0),
    AudioConnection(env[1], 0, mixer, 1),
    AudioConnection(env[2], 0, mixer, 2),
    AudioConnection(env[3], 0, mixer, 3),
  };
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
  AudioConnection patches[BANK_SIZE] = {
    AudioConnection(reeds.at[0].out(), 0, mixer, 0),
    AudioConnection(reeds.at[1].out(), 0, mixer, 1),
    AudioConnection(reeds.at[2].out(), 0, mixer, 2),
    AudioConnection(reeds.at[3].out(), 0, mixer, 3),
    AudioConnection(reeds.at[4].out(), 0, mixer, 4),
    AudioConnection(reeds.at[5].out(), 0, mixer, 5),
    AudioConnection(reeds.at[6].out(), 0, mixer, 6),
    AudioConnection(reeds.at[7].out(), 0, mixer, 7),
    AudioConnection(reeds.at[8].out(), 0, mixer, 8),
    AudioConnection(reeds.at[9].out(), 0, mixer, 9),
    AudioConnection(reeds.at[10].out(), 0, mixer, 10),
    AudioConnection(reeds.at[11].out(), 0, mixer, 11),
  };
};

} // namespace
