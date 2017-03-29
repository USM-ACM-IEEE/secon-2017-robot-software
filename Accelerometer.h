#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include "Robot.h"
#include "libraries/I2CDev/I2Cdev.h"
#include "libraries/ADXL345/ADXL345.h"

class Accelerometer {
	ADXL345 accelerometer = ADXL345(0x1D);

	int16_t x, y, z;
public:
	void begin();
	void update();

	int16_t getX();
	int16_t getY();
	int16_t getZ();
};

extern Accelerometer accel;

#endif
