#include "Robot.h"

Gyro gyro;

void Gyro::begin() {
	if(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G)) {
		Serial.println(F("Could not find a valid MPU6050 sensor, check wiring!"));
	}

	mpu.calibrateGyro();
	mpu.setThreshold(3);
}

void Gyro::update() {
	unsigned long int timeStep = millis() - lastUpdate;

	if(timeStep < 10) {
		delay(10-timeStep);
		timeStep = 10;
	}

	if(timeStep > maxTime)
		maxTime = timeStep;

	Vector norm = mpu.readNormalizeGyro();

	//pitch = pitch + norm.YAxis * timeStep;
	//roll = roll + norm.XAxis * timeStep;
	yaw = yaw + norm.ZAxis * timeStep/1000;

	lastUpdate = millis();
}

float Gyro::getYaw() {
	return yaw;
}
