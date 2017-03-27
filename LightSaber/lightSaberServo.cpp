#include "lightSaberServo.h"

void setupLightsaber(int LIGHTSABER_JOINT, int LIGHTSABER_SWING,Servo &LightSaberJointServo, Servo &LightSaberSwingServo)
{
	pinMode(LIGHTSABER_JOINT, OUTPUT);
	pinMode(LIGHTSABER_SWING, OUTPUT);
	LightSaberJointServo.attach(LIGHTSABER_JOINT);
	LightSaberSwingServo.attach(LIGHTSABER_SWING);
}

void restLightSaber(Servo &LightSaberJointServo, Servo &LightSaberSwingServo)
{

	LightSaberJointServo.write(70);
	delay(400);
	LightSaberSwingServo.write(10);
	delay(400);
	LightSaberJointServo.write(158);
	delay(400);
}

void swingLightSaber(Servo &LightSaberJointServo, Servo &LightSaberSwingServo)
{


	LightSaberJointServo.write(158);
	delay(350);

	restLightSaber(LightSaberJointServo, LightSaberSwingServo);
}

void readyLightSaber(Servo &LightSaberJointServo, Servo &LightSaberSwingServo)
{
	    LightSaberJointServo.write(70);
		delay(250);
		LightSaberSwingServo.write(150);
		delay(350);

		LightSaberJointServo.write(43);
		delay(350);
}
