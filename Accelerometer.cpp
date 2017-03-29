#include "Robot.h"

Accelerometer accel;

void Accelerometer::begin() {
	accelerometer.initialize();
	Serial.println(accelerometer.testConnection() ? "ADXL345 connection successful" : "ADXL345 connection failed");
}

void Accelerometer::update() {
	accelerometer.getAcceleration(&x, &y, &z);
}

int16_t Accelerometer::getX() { return x; }
int16_t Accelerometer::getY() { return y; }
int16_t Accelerometer::getZ() { return z; }
