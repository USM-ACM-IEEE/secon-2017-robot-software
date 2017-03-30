#ifndef GYRO_H
#define GYRO_H

#include "Robot.h"
#include "libraries/MPU6050/MPU6050.h"

class Gyro {
	MPU6050 mpu;

	bool initialized = false;
	float yaw, pitch, roll;
	unsigned long int lastUpdate, maxTime;

public:
	void begin();

	void update();
	float getYaw();
};

extern Gyro gyro;

#endif
