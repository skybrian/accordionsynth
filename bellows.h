#include <math.h>
#include <Adafruit_LSM6DS33.h>
#include <Metro.h>
#include <Print.h>

// Determines the speed of rotation of a hinge based on gyroscope readings.
// 
class Bellows {
  private:
  Adafruit_LSM6DS33 sensor;
  sensors_event_t accel;
  sensors_event_t gyro;
  sensors_event_t temp;
  float smoothRot;
  
  public:
  void begin() {
    while (!sensor.begin_I2C()) {
      delay(1);
    }
  }

  // Returns speed after reading new data.
  float update() {
    sensor.getEvent(&accel, &gyro, &temp);
    smoothRot = (smoothRot*4 + _measureRotationSpeed()) * 0.2;
    return smoothRot / 5.0;
  }

  float _measureRotationSpeed() {
    float x = gyro.gyro.x;
    float y = gyro.gyro.y;
    float z = gyro.gyro.z;
    return sqrt(x*x + y*y + z*z);
  }

  void plot(Print& out) {
//    out.print("accelX:"); out.print(accel.acceleration.x);
//    out.print(",accelY:"); out.print(accel.acceleration.y);
//    out.print(",accelZ:"); out.print(accel.acceleration.z);
//    out.print(",");

    out.print("gyroX:"); out.print(gyro.gyro.x);
    out.print(",gyroY:"); out.print(gyro.gyro.y);
    out.print(",gyroZ:"); out.print(gyro.gyro.z);
  }
};
