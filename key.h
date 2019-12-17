#include "midi.h"
using namespace midi;

#include "button.h"

// A keyboard matrix decoder that outputs chords.

namespace key {

// Number of output pins.
// Each output pin represents a column. When set to LOW, the keys in that column can be read.
// (Any other pin state should work to disable the column.)
const unsigned columnCount = 4;

// Number of input pins.
// Each input pin represents a row. Reading the pin returns returns LOW if the button is pressed in the enabled column.
const unsigned rowCount = 2;

typedef uint8_t ColumnPins[columnCount];
typedef uint8_t RowPins[rowCount];

// A Layout contains the Chord to play for each key.
typedef Chord Layout[rowCount][columnCount];

// A keyboard matrix circuit that's connected via the given pins.
class Board {
public:
  constexpr Board(const uint8_t (&colPins)[columnCount], const uint8_t (&rowPins)[rowCount]) : cols(colPins), rows(rowPins) {};
 
  void setupPins() const {
    for (unsigned c = 0; c < columnCount; c++) {
      pinMode(cols[c], INPUT);
    }
    for (unsigned r = 0; r < rowCount; r++) {
      pinMode(rows[r], INPUT_PULLUP);
    }
  }

  // Poll each key and return a chord that's the combination of all currently pressed keys.
  Chord poll(Layout& layout) {
    Chord out = Chord();
    for (unsigned c = 0; c < columnCount; c++) {
      uint8_t colPin = cols[c];
      
      // Pull other side of diodes in this column to LOW.
      pinMode(colPin, OUTPUT);
      digitalWrite(colPin, LOW);

      // Wait for signal to settle to avoid "ghost key" in the first row.
      delayMicroseconds(1);

      // Scan the keys in this column.
      for (unsigned r = 0; r < rowCount; r++) {
        uint8_t rowPin = rows[r];
        // The pin will be pulled low if it's connected to the column pin via this key's switch and diode.
        bool pressed = digitalRead(rowPin) == LOW;
        pressed = debouncers[r][c].filter(pressed);
        if (pressed) {
//          Serial.print("key pressed: c=");
//          Serial.print(c);
//          Serial.print(", r=");
//          Serial.println(r);
          Chord buttonChord = layout[r][c];
          out = out + buttonChord;
        }
      }
      
      // Disable current flow through diodes in this column; other side could be anything.
      digitalWrite(colPin, HIGH);
      pinMode(colPin, INPUT);
    }
    return out;
  }
private:
  const uint8_t (&cols)[columnCount];
  const uint8_t (&rows)[rowCount];
  button::Debouncer debouncers[rowCount][columnCount];
};

} // end namespace
