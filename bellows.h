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
  smoothRot = smoothRot * 0.9 + _measureRotationSpeed() * 0.1;
  return true;
}


const float rampStart = 0.023;

const float pressureCurve[21] = {
  // First part exponential, based on: https://play.golang.org/p/L_x7ktC3tYO
  0, 0.206, 0.266, 0.329, 0.396, 0.466, 0.540, 0.619, 0.702, 0.789, 0.882, // 0 - 0.5
  0.94, 0.96, 0.97, 0.979, 0.985, 0.99, 0.994, 0.997, 0.999, 1.0,
};

float pressure() {
  float x = smoothRot / 5 - rampStart;
  if (x<=0) {
    return 0;
  }
  if (x>=1) {
    return 1;
  }
  int i = (int)(x*20);
  float y0 = pressureCurve[i];
  float y1 = pressureCurve[i+1];
  float slope = (y1-y0)/0.05;
  float mu = x - i / 20.0;
  return slope * mu + y0;
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
