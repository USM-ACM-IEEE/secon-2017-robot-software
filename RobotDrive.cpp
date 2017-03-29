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
	float fl = x + y + rotation;
	float fr = -x + y - rotation;
	float rl = -x + y + rotation;
	float rr = x + y - rotation;

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

//void turn(int target, float speed) {
//
//	float offset, angle, ranged, adjusted, modded, mapped, output;
//
//	offset = ypr[0] * -180/M_PI;
//
//	do {
//		angle = ypr[0] * 180/M_PI;
//		ranged = map(angle, -180, 180, 0, 360);
//		adjusted = ranged - offset;
//		modded = int(adjusted) % 360;
//		mapped = map(modded, 0, 360, -180, 180);
//
//		lcd.setCursor(0,0);
//
//		output = min(speed*abs(target-mapped), 0.2);
//
//		if(target-mapped > 0) {
//			//lcd.print(output);
//			drive.MecanumDrive_Cartesian(0, 0, output);
//		} else if(target-mapped < 0) {
//			//lcd.print(-output);
//			drive.MecanumDrive_Cartesian(0, 0, -output);
//		}
//	} while(abs(target-mapped) > 0);
//
//	drive.MecanumDrive_Cartesian(0, 0, 0);
//}
