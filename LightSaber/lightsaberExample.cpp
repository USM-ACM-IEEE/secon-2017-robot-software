#include "Arduino.h"
#include "LightSaber/lightSaberServo.h"


Servo LightSaberJointServo;
Servo LightSaberSwingServo;
#define joint_pin 7
#define swingarm_pin 8


void setup()
{
// Add your initialization code here
	setupLightsaber(joint_pin, swingarm_pin,LightSaberJointServo, LightSaberSwingServo);
}

// The loop function is called in an endless loop
void loop()
{
//Add your repeated code here

	delay(2000);
	readyLightSaber(LightSaberJointServo, LightSaberSwingServo);
	delay(2000);

	swingLightSaber(LightSaberJointServo, LightSaberSwingServo);



}



