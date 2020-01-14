#ifndef MIDI_H_
#define MIDI_H_

#include <cstdint>
#include "Print.h"
#include "MIDIUSB.h"

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

  constexpr unsigned char toMidiNumber() const {
    return num;
  }

  constexpr const char* const name() {
    return names[num % 12];
  }

  constexpr int octave() {
    return (num / 12) -1;
  }

  constexpr Note toOctaveFrom(Note base) const {
    int remainder = ((num + 144) - base.num) % 12;
    return Note(base + (unsigned char)remainder);
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

  static constexpr const char* const names[] = 
     { "C", "C#", "D", "D#","E", "F", "F#", "G", "G#", "A", "A#", "B" };  
};

// Octave number in constants increments at C.
// See: https://en.wikipedia.org/wiki/Scientific_pitch_notation
// Midi charts may label notes differently!

constexpr Note A0 = Note(21);
constexpr Note G1 = A0 + 10;
constexpr Note A1 = G1 + 2;
// constexpr Note B1 = A1 + 2; // B1 conflicts with teensy macro

constexpr Note C2 = A1 + 3;
constexpr Note D2 = C2 + 2;
constexpr Note E2 = D2 + 2;
constexpr Note F2 = E2 + 1;
constexpr Note G2 = F2 + 2;
constexpr Note A2 = G2 + 2;
constexpr Note B2 = A2 + 2;

constexpr Note C3 = B2 + 1;
constexpr Note D3 = C3 + 2;
constexpr Note E3 = D3 + 2;
constexpr Note F3 = E3 + 1;
constexpr Note G3 = F3 + 2;
constexpr Note A3 = G3 + 2;
constexpr Note B3 = A3 + 2;
constexpr Note C4 = B3 + 1;
constexpr Note D4 = C4 + 2;
constexpr Note E4 = D4 + 2;

constexpr Note A4 = A3 + 12;

// 128 bits would cover the entire MIDI range, but just using 64 will do.

constexpr Note ChordBase = G1;
constexpr Note ChordLimit = ChordBase + 64;

class Chord {
private:
  uint64_t bits;
  
  static constexpr uint64_t toBit(Note n) {
    return ((uint64_t)1) << (n - ChordBase);
  }

  static constexpr uint64_t octaveBits(Note n) {
    Note low = n.toOctaveFrom(ChordBase);
    return toBit(low) | toBit(low + 12) | toBit(low + 24);
  }

  constexpr Chord(uint64_t bitset) : bits(bitset) {}
public:
  constexpr Chord() : bits(0) {}
  constexpr Chord(Note n) : bits(toBit(n)) {}
  constexpr Chord(Note n1, Note n2) : bits(toBit(n1) | toBit(n2)) {}
  constexpr Chord(Note n1, Note n2, Note n3) : bits(toBit(n1) | toBit(n2) | toBit(n3)) {}

  constexpr Chord static octave(Note n) {
    return Chord(octaveBits(n));
  }

  constexpr static Chord majorUp(Note n) {
    return Chord(toBit(n) | toBit(n + 4) | toBit(n + 7));
  }

  constexpr static Chord majorDown(Note n) {
    return Chord(toBit(n) | toBit(n - 8) | toBit(n - 5));
  }

  constexpr static Chord majorMid(Note n) {
    return Chord(toBit(n) | toBit(n + 4) | toBit(n - 5));
  }

  constexpr static Chord minorUp(Note n) {
    return Chord(toBit(n) | toBit(n + 3) | toBit(n + 7));
  }

  constexpr static Chord minorDown(Note n) {
    return Chord(toBit(n) | toBit(n - 9) | toBit(n - 5));
  }

  constexpr static Chord minorMid(Note n) {
    return Chord(toBit(n) | toBit(n + 3) | toBit(n - 5));
  }

  // Returns the union of the notes in both chords.
  constexpr Chord operator +(const Chord other) const {
    return Chord(bits | other.bits);
  }

  constexpr bool has(Note n) {
    return (Chord(n).bits & bits) != 0;
  }

  void printTo(Print& out) {
    out.print("Chord(");
    int notes = 0;
    for (Note n = ChordBase ; n < ChordLimit; n = n + 1) {
      if (has(n)) {
          if (notes>0) {
            out.print(", ");
          }
          out.print(n.name());
          out.print(n.octave());
          notes++;
      }
    }
    out.print(")");
  }
};

class MidiChannel {
private:
  int chan;
  Chord prev;
public:
  constexpr MidiChannel(int channel) : chan(channel) {}

  void send(Chord next) {
    for (Note n = ChordBase; n < ChordLimit; n = n + 1) {
        if (next.has(n) && !prev.has(n)) {
          usbMIDI.sendNoteOn(n.toMidiNumber(), 99, chan);
        } else if (prev.has(n) && !next.has(n)) {
          usbMIDI.sendNoteOff(n.toMidiNumber(), 0, chan);
        }
    }
    prev = next;
  }
};

} // namespace
#endif
