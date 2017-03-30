#include "Robot.h"


/******************************************************************************
*******************************************************************************
******************************************************************************/

int currentTask = 0;

Task* tasks[] = {
	// Startup
	new FirstTask,

	// Stage 1 Positioning
	new TimedDrive_Cartesian(0, 0.4, 0, 2000),		// Move Forward To Circuit
	new TimedDrive_Cartesian(0.35, 0.2, 0, 500),	// Move Right
	new TimedDrive_Cartesian(-0.35, 0.2, 0, 1000),	// Move Left
	new TimedDrive_Cartesian(0, 0.4, 0, 2000),		// Press On Circuit
	// Check circuit and display

	// Stage 2 Positioning
	new TimedDrive_Cartesian(0, -0.4, 0, 500),		// Move Backwards Out of Circuit
	new TimedDrive_Cartesian(0.5, 0.2, 0, 2000),	// Move Over To Corner
	new TimedDrive_Cartesian(0.2, -0.4, 0, 1300),		// Move Backwards To Lightsaber
	// Do stuff with "force" and lightsaber

	// Stage 3 Positioning
	//new TimedDrive_Cartesian(0.1, -0.2, 0, 1000),	// Move Over To Corner
	//new TimedDrive_Cartesian(-0.2, -0.1, 0, 1000),	// Move Over To Knob
	// Move Back
	// Move Over Slightly
	// Move onto knob
	// Do stuff with knob

	// Stage 4 Positioning
	//new TimedDrive_Cartesian(0, 0.2, 0, 200),		// Move off of knob
	//new TimedDrive_Cartesian(0.1, -0.2, 0, 1000),	// Move Over To Corner


	// Cleanup
	new LastTask
};

/******************************************************************************
*******************************************************************************
******************************************************************************/

void FirstTask::setup() {
	// LED's and Buttons
	pinMode(25, OUTPUT);
	pinMode(27, INPUT);
	digitalWrite(27, HIGH);
}


void FirstTask::loop() {
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
