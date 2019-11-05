#include "midi.h"
#include <Audio.h>

namespace sound {

class Reed {
public:
  Reed(midi::Note n) {
    wave.amplitude(1.0);
    wave.frequency(n.frequency());
    wave.begin(WAVEFORM_SAWTOOTH);
    env.sustain(1.0);
    env.release(10);
  }

  void noteOn() {
    env.noteOn();
  }

  void noteOff() {
    env.noteOff();
  }

  AudioEffectEnvelope env;
private:
  AudioSynthWaveform wave;
  AudioConnection patch = AudioConnection(wave, 0, env, 0);
};

} // namespace
