#ifndef ROBOTDRIVE_H
#define ROBOTDRIVE_H

#include "Robot.h"
#include "Task.h"

class RobotDrive {
	Servo frontLeft, frontRight, rearLeft, rearRight;

  public:
	void begin(int kFrontLeft, int kFrontRight, int kRearLeft, int kRearRight);
	void MecanumDrive_Cartesian(float x, float y, float rotation);
};

extern RobotDrive drive;

/*****************************************************************************/

class TimedDrive_Cartesian : public Task {
	long int startTime = 0;

	float x, y, z;
	uint16_t time;

  public:
	TimedDrive_Cartesian(float x, float y, float z, uint16_t time);

	void setup();
	void loop();
};

/*****************************************************************************/

class TimedDrive_Heading : public Task {
	long int startTime = 0;

	float x, y;
	uint16_t time;
	int16_t heading;

  public:
	TimedDrive_Heading(float x, float y, int16_t heading, uint16_t time);

	void setup();
	void loop();
};

/*****************************************************************************/

class TurnAbsolute : public Task {
	long int startTime = 0;

	uint16_t time;
	int16_t heading;

  public:
	TurnAbsolute(int16_t heading, uint16_t time);

	void setup();
	void loop();
};

#endif
