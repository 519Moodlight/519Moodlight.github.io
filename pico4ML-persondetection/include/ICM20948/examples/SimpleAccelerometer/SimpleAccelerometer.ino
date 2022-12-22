/*
  Arduino LSM9DS1 - Simple Accelerometer

  This example reads the acceleration values from the ICM20948
  sensor and continuously prints them to the Serial Monitor
  or Serial Plotter.

  created 10 Jul 2019
  by Riccardo Rizzo

  This example code is in the public domain.
*/

#include "ICM20948.h"

IMU_EN_SENSOR_TYPE enMotionSensorType;
void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Started");
  if (!ICM20948::imuInit(&enMotionSensorType)) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  Serial.print("Accelerometer sample rate = ");
  Serial.print(1125/(1+8));
  Serial.println(" Hz");
  Serial.println();
  Serial.println("Acceleration in G's");
  Serial.println("X\tY\tZ");
}

void loop() {
  float x, y, z;

  if (ICM20948::dataReady()) {
    ICM20948::icm20948AccelRead(&x, &y, &z);
    const float norm_x = -y;
    const float norm_y = x;
    const float norm_z = -z;
    Serial.print(norm_x);
    Serial.print('\t');
    Serial.print(norm_y);
    Serial.print('\t');
    Serial.println(norm_z);
  }
}
