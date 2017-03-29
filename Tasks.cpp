#include "Robot.h"

int currentTask = 0;

Task* tasks[] = {
	// Startup
	new FirstTask,

	// Stage 1
	new Forward1,
	new Sweep1,
	new Sweep2,

	// Cleanup
	new LastTask
};

/******************************************************************************
*******************************************************************************
******************************************************************************/

void Forward1::setup() {
}

void Forward1::loop() {
	if(startTime == 0) {
		startTime = millis();
	}

	if(millis()-startTime <= 1600) {
		drive.MecanumDrive_Cartesian(0, 0.5, 0);
	} else {
		startTime = 0;
		drive.MecanumDrive_Cartesian(0, 0, 0);
		currentTask++;
	}
}

/******************************************************************************
*******************************************************************************
******************************************************************************/

void Sweep1::setup() {
}

void Sweep1::loop() {
	if(startTime == 0) {
		startTime = millis();
	}

	if(millis()-startTime <= 500) {
		drive.MecanumDrive_Cartesian(0.35, 0.2, 0);
	} else {
		startTime = 0;
		drive.MecanumDrive_Cartesian(0, 0, 0);
		currentTask++;
	}
}

/******************************************************************************
*******************************************************************************
******************************************************************************/

void Sweep2::setup() {
}

void Sweep2::loop() {
	if(startTime == 0) {
		startTime = millis();
	}

	if(millis()-startTime <= 1000) {
		drive.MecanumDrive_Cartesian(-0.35, 0.2, 0);
	} else {
		startTime = 0;
		drive.MecanumDrive_Cartesian(0, 0, 0);
		currentTask++;
	}
}

/******************************************************************************
*******************************************************************************
******************************************************************************/

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
	currentTask = 0;
}
