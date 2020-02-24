#include <math.h>
#include <Adafruit_LSM6DS33.h>
#include <Metro.h>
#include <Print.h>

// Determines the speed of rotation of a hinge based on gyroscope readings.
namespace bellows {

Adafruit_LSM6DS33 sensor;
Metro updateTicks(5);
sensors_event_t accel;
sensors_event_t gyro;
sensors_event_t temp;
float smoothRot;

float _measureRotationSpeed() {
  float x = gyro.gyro.x;
  float y = gyro.gyro.y;
  float z = gyro.gyro.z;
  return sqrt(x*x + y*y + z*z);
}
  
void begin() {
  while (!sensor.begin_I2C()) {
    delay(1);
  }
}

// Returns true if new data was read.
bool update() {
  if (!updateTicks.check()) {
    return false;
  }
  sensor.getEvent(&accel, &gyro, &temp);
  smoothRot = (smoothRot*4 + _measureRotationSpeed()) * 0.2;
  return true;
}

const float curveBottom = 0.15;
const float curveTop = 0.9;
const float curveEnd = 0.5;
const float curveA = -(curveTop - curveBottom) / (curveEnd*curveEnd);
const float limiterSlope = (1.0-curveTop)/(1.0-curveEnd);

float pressure() {
  float x = smoothRot / 5;
  x -= curveEnd;
  if (x < 0) {
    return curveA * x*x + curveTop;
  }
  return curveTop + limiterSlope * x;
}

void plot(Print& out) {
//    out.print("accelX:"); out.print(accel.acceleration.x);
//    out.print(",accelY:"); out.print(accel.acceleration.y);
//    out.print(",accelZ:"); out.print(accel.acceleration.z);
//    out.print(",");

  out.print("gyroX:"); out.print(gyro.gyro.x);
  out.print(",gyroY:"); out.print(gyro.gyro.y);
  out.print(",gyroZ:"); out.print(gyro.gyro.z);

  out.print(",speed:");
  out.print(smoothRot*2);
  out.print(",pressure:");
  out.print(pressure()*10.0);
  out.println();
}

} // end namespace
