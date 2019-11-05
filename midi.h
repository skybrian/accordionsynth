#ifndef MIDI_H_
#define MIDI_H_

#include <cstdint>

// Some basic music theory, defined using midi note values.

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

// Octave number in constants increments at C.
// See: https://en.wikipedia.org/wiki/Scientific_pitch_notation
// Midi charts may label notes differently!

constexpr Note A0 = Note(21);

constexpr Note C1 = A0 + 3;
constexpr Note D1 = C1 + 2;
constexpr Note E1 = D1 + 2;

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

// 128 bits would cover the entire MIDI range, but just using 64 will do.

constexpr Note ChordBase = E1;
constexpr Note ChordLimit = ChordBase + 64;

class Chord {
private:
  uint64_t bits;
  
  static constexpr uint64_t toBit(Note n) {
    return ((uint64_t)1) << (n - ChordBase);
  }

public:
  constexpr Chord() : bits(0) {}
  constexpr Chord(Note n) : bits(toBit(n)) {}
  constexpr Chord(Note n1, Note n2) : bits(toBit(n1) | toBit(n2)) {}
  constexpr Chord(Note n1, Note n2, Note n3) : bits(toBit(n1) | toBit(n2) | toBit(n3)) {}

  constexpr static Chord major(Note n) {
    return Chord(n, n + 4, n + 7);
  }

  constexpr bool has(Note n) {
    return (Chord(n).bits & bits) != 0;
  }
};

} // namespace
#endif
