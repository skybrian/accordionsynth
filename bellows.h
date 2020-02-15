#include <math.h>
#include <Adafruit_MSA301.h>
#include <Metro.h>
#include <Print.h>

const float accelGravity = 1990.0;

// Determines the angle of a hinge based on accelerometer readings.
// 
class Bellows {
  private:
  Adafruit_MSA301 accel;
  float prevAngle; // Clockwise, 0 is up, in degrees.
  float prevVelo; // Clockwise, degrees/millisecond.
  elapsedMillis prevDelta; // Time since last reading.
  
  public:
  void begin() {
    accel.begin();
    accel.read();
    prevAngle = _measureAngle();
    prevVelo = 0;
    prevDelta = 0;
  }

  // Returns speed after reading new data.
  float update() {
    if (prevDelta < 1) return speed();
    
    int delta = prevDelta;
    accel.read();
    prevDelta = 0;

    float predictedVelo = prevVelo;
    float predictedAngle = prevAngle;
    float measuredAngle = _measureAngle();
    float smoothAngle = 0.8 * predictedAngle + 0.2 * measuredAngle;

    float calculatedVelo = (smoothAngle - prevAngle) / delta;
    float smoothVelo = 0.95 * predictedVelo + 0.05 * calculatedVelo; 

//    float tangentGravity = sin(smoothAngle) * accelGravity;
//    float measuredAccel = accel.z - tangentGravity;
    
    prevAngle = smoothAngle;
    prevVelo = smoothVelo;

    return speed();
  }

  void plot(Print& out) {
//    out.print(accel.x);
//    out.print(", ");
//    out.print(accel.z);
//    out.print(", ");
    out.print(prevAngle);
    out.print(", ");
    out.print(speed()*1000.0);
    out.println();      
  }

  // Returns previous estimate of speed in degrees/second. (Positive in either direction.)
  float speed() {
    if (prevVelo >= 0) {
      return prevVelo;
    } else {
      return -prevVelo;
    }    
  }

  // Find the angle assuming all acceleration is due to gravity.
  // Result is degress from vertical; positive is clockwise.
  float _measureAngle() {
    // accel.x is acceleration away from center. (Should be negative due to gravity.)
    // accel.z is clockwise acceleration (tangent to circle).
    if (accel.x == 0) {
      if (accel.z > 0) {
        return 90;
      } else {
        return -90;
      }
    }
    return atan(-1.0*accel.z/accel.x)*360.0/2.0*M_PI;
  }
};
