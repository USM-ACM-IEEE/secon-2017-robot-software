#ifndef ROBOTDRIVE_H
#define ROBOTDRIVE_H

#include "Robot.h"


class RobotDrive {
	Servo frontLeft, frontRight, rearLeft, rearRight;

public:
	void begin(int kFrontLeft, int kFrontRight, int kRearLeft, int kRearRight);
	void MecanumDrive_Cartesian(float x, float y, float rotation);
};

void turn(int target, float speed);

extern RobotDrive drive;

#endif
