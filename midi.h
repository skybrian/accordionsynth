#include <cstdint>
#include <math.h>

namespace midi {

class Note {
public:
  constexpr Note(const unsigned char midiNoteNumber) : num(midiNoteNumber) {}
    
  constexpr Note operator +(const unsigned char offset) const {
    return Note(num + offset);
  }

  constexpr Note operator -(const unsigned char offset) const {
    return Note(num - offset);
  }

  constexpr signed char operator -(const Note other) const {
    return num - other.num;
  }

  bool operator <(const Note other) const {
    return num < other.num;
  }

  bool operator <=(const Note other) const {
    return num <= other.num;
  }

  float frequency() const;
  
private:
  unsigned char num;  
};

// Octave number increments at C.
// See: https://en.wikipedia.org/wiki/Scientific_pitch_notation
// Midi charts may label notes differently!

constexpr Note A0 = Note(21);
constexpr Note A1 = A0 + 12;

constexpr Note A2 = A1 + 12;
constexpr Note B2 = A2 + 2;
constexpr Note C3 = B2 + 1;
constexpr Note D3 = C3 + 2;
constexpr Note E3 = D3 + 2;
constexpr Note F3 = E3 + 1;
constexpr Note G3 = F3 + 2;
constexpr Note A3 = G3 + 2;
constexpr Note B3 = A3 + 2;
constexpr Note C4 = B3 + 1;

constexpr Note A4 = A3 + 12;

constexpr Note ChordBase = A0;
constexpr Note ChordLimit = A0 + 64;

class Chord {
public:
  constexpr Chord(Note n) : bits(((uint64_t)1) << (n - ChordBase)) {}

  constexpr Chord operator &(const Chord other) const {
    return Chord(bits & other.bits);
  }

  constexpr Chord(uint64_t bitset) : bits(bitset) {};

  constexpr bool has(Note n) {
    return (Chord(n).bits & bits) != 0;
  }

private:
  uint64_t bits;  
};

constexpr Chord Silent = Chord{0};

} // namespace
