#include "Robot.h"

void FirstTask::setup() {
	// LED's and Buttons
	pinMode(25, OUTPUT);
	pinMode(27, INPUT);
	digitalWrite(27, HIGH);

	Serial.println("Set up task 1");
}


void FirstTask::loop() {
	Serial.println("Running Task 1");

	if(millis() % 1000 < 500) {
		digitalWrite(25, HIGH);
	} else {
		digitalWrite(25, LOW);
	}

	if(!digitalRead(27)) {
		digitalWrite(25, HIGH);
		currentTask++;
	}
}

/******************************************************************************
*******************************************************************************
******************************************************************************/

void LastTask::setup() {
	currentTask = 0;
}

void LastTask::loop() {
	Serial.println("No more tasks!");
}
