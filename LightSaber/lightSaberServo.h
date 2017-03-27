#include "Arduino.h"
#include "Servo.h"

/*SETUP FUNCTION*/
void setupLightsaber(int LIGHTSABER_JOINT, int LIGHTSABER_SWING,Servo &LightSaberJointServo, Servo &LightSaberSwingServo);

/*SET LIGHTSABER TO REST*/
void restLightSaber(Servo &LightSaberJointServo, Servo &LightSaberSwingServo);

/*SWING LIGHTSABER*/
void swingLightSaber(Servo &LightSaberJointServo, Servo &LightSaberSwingServo);

/*READY LIGHTSABER*/
void readyLightSaber(Servo &LightSaberJointServo, Servo &LightSaberSwingServo);



