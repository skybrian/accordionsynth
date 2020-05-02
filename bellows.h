#include <math.h>
#include <Adafruit_LSM6DS33.h>
#include <Metro.h>
#include <Print.h>

// Determines the speed of rotation of a hinge based on gyroscope readings.
namespace bellows {

const int period = 2;
float gyroDrift;

Adafruit_LSM6DS33 sensor;
Metro updateTicks(period);
sensors_event_t accel;
sensors_event_t gyro;
sensors_event_t temp;
float smoothTilt;
float fusedTilt;

float _measureTilt() {
  float x = accel.acceleration.x; // clockwise accel. Gravity: positive left, negative right
  float y = accel.acceleration.y; // acceleration towards hinge (should be negative due to gravity)
  if (y == 0) {
    if (x>0) {
      return -90;
    } else {
      return 90;
    }
  }
  float degrees =  atan(x/y)*360.0/(2.0*M_PI); // zero is up, degrees clockwise
  if (y>0) {
    return degrees + 180.0;
  } else {
    return degrees;
  }
}

float _measureTiltDelta() {
  return gyro.gyro.z - gyroDrift;
}

float _measureGyroDrift() {
  // Wait for sensor to settle.
  float prev = 0.0;

  while (true) {
    sensor.getEvent(&accel, &gyro, &temp);
    if (abs(gyro.gyro.z - prev) < 0.01) {
         break;
    }
    prev = gyro.gyro.z;
    delay(5);
  }

  // Take average.
  float sum = 0.0;
  for (int i = 0; i < 100; i++) {
    sensor.getEvent(&accel, &gyro, &temp);
    sum += gyro.gyro.z;
    delay(5);
  }
  return sum/100.0;
}

void begin() {
  while (!sensor.begin_I2C()) {
    delay(1);
  }
  delay(50);
  gyroDrift = _measureGyroDrift();
  smoothTilt = _measureTilt();
  fusedTilt = smoothTilt;
}

// Returns true if new data was read.
bool update() {
  if (!updateTicks.check()) {
    return false;
  }

  sensor.getEvent(&accel, &gyro, &temp);
  smoothTilt = smoothTilt * 0.8 + _measureTilt() * 0.2;
  fusedTilt = (fusedTilt + _measureTiltDelta() * 0.3) * 0.99 + smoothTilt * 0.01;
  return true;
}

float pressure() {
  float p = 0.5 -.2 * (fusedTilt - 91.0);
  if (p < 0.5) {
    return 0.5;
  }
  if (p > 1.0) {
    return 1.0;
  }
  return p;
}

void plot(Print& out) {
//    out.print("accelX:"); out.print(accel.acceleration.x);
//    out.print(",accelY:"); out.print(accel.acceleration.y);
//    out.print(",accelZ:"); out.print(accel.acceleration.z);

  //out.print("gyroX:"); out.print(gyro.gyro.x);
  //out.print(",gyroY:"); out.print(gyro.gyro.y);
//  out.print("gyroZ:"); out.print(gyro.gyro.z * 100.0);
//  out.print(",gyroDrift:"); out.print(gyroDrift * 100.0);
//  out.print("tiltDelta:"); out.print(_measureTiltDelta() * 10.0);

//  out.print("tilt:"); out.print(_measureTilt() - 90.0);
//  out.print(",smoothTilt:"); out.print(smoothTilt - 90.0);
  out.print("fusedTilt:"); out.print(0.5 -.2 * (fusedTilt - 91.0));
  out.print(",pressure:"); out.print(pressure());
  out.println();
}

} // end namespace
