#include "Robot.h"

RobotDrive drive;

void RobotDrive::begin(int kFrontLeft, int kFrontRight, int kRearLeft, int kRearRight)
{
	frontLeft.attach(kFrontLeft);
	frontRight.attach(kFrontRight);
	rearLeft.attach(kRearLeft);
	rearRight.attach(kRearRight);
}

void RobotDrive::MecanumDrive_Cartesian(float x, float y, float rotation) {
	// Generate Vectors
	float fl = x - y - rotation;
	float fr = -x - y + rotation;
	float rl = -x - y - rotation;
	float rr = x - y + rotation;

	// Calculate uS
	int fl_uS = 1500+(fl*500);
	int fr_uS = 1500+(fr*500);
	int rl_uS = 1500+(rl*500);
	int rr_uS = 1500+(rr*500);

	// Send to motors
	frontLeft.writeMicroseconds(fl_uS);
	frontRight.writeMicroseconds(fr_uS);
	rearLeft.writeMicroseconds(rl_uS);
	rearRight.writeMicroseconds(rr_uS);
}

/*****************************************************************************/

TimedDrive_Cartesian::TimedDrive_Cartesian(float x, float y, float z, uint16_t time) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->time = time;
}

void TimedDrive_Cartesian::setup() {
}

void TimedDrive_Cartesian::loop() {
	if(startTime == 0) {
		startTime = millis();
	}

	if(millis()-startTime <= time) {
		drive.MecanumDrive_Cartesian(x, y, z);
	} else {
		startTime = 0;
		drive.MecanumDrive_Cartesian(0, 0, 0);
		currentTask++;
	}
}

/*****************************************************************************/

TimedDrive_Heading::TimedDrive_Heading(float x, float y, int16_t heading, uint16_t time) {
	this->x = x;
	this->y = y;
	this->time = time;
	this->heading = heading;
}

void TimedDrive_Heading::setup() {
}

void TimedDrive_Heading::loop() {
	if(startTime == 0) {
		startTime = millis();
	}

	if(millis()-startTime <= time) {
		int16_t offset = heading - gyro.getYaw();

		float value = 0.1 * offset / abs(offset);

		if(abs(offset) <= 1) {
			value = 0;
		}

		drive.MecanumDrive_Cartesian(x, y, value);
	} else {
		startTime = 0;
		drive.MecanumDrive_Cartesian(0, 0, 0);
		currentTask++;
	}
}

/*****************************************************************************/

TurnAbsolute::TurnAbsolute(int16_t heading, uint16_t time) {
	this->time = time;
	this->heading = heading;
}

void TurnAbsolute::setup() {
}

void TurnAbsolute::loop() {
	if(startTime == 0) {
		startTime = millis();
	}

	if(millis()-startTime <= time) {
		int16_t offset = heading - gyro.getYaw();

		// TODO: Crashes if value is 0.4 or lower...
		float value = 0.5 * offset / abs(offset);

		if(abs(offset) <= 1) {
			startTime = 0;
			drive.MecanumDrive_Cartesian(0, 0, 0);
			currentTask++;
		}

		drive.MecanumDrive_Cartesian(0, 0, value);
	} else {
		startTime = 0;
		drive.MecanumDrive_Cartesian(0, 0, 0);
		currentTask++;
	}
}
