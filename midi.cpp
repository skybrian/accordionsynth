#include <math.h>

#include "midi.h"
using namespace midi;

float Note::frequency() const {
  return 27.5 * powf(2, (num - A0.num) / 12.0);
}
