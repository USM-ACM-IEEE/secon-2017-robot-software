#include "Robot.h"

void setup() {
	// Wire
	Wire.begin();
	Wire.setClock(400000);

	// Serial
	Serial.begin(115200);

	// Classes
	gui.begin();
	gyro.begin();
	drive.begin(9, 10, 11, 12);

	// Heartbeat
	pinMode(23, OUTPUT);

	// Run all task setups
	do tasks[currentTask++]->setup();
		while(currentTask != 0);
}


unsigned long frameStartTime;
void loop() {
	// Start Heartbeat
	frameStartTime = millis();

	// System Calls
	gyro.update();
	gui.update();

	// Run Current Task
	tasks[currentTask]->loop();

	// Finish Heartbeat
	digitalWrite(23, !digitalRead(23));
}
