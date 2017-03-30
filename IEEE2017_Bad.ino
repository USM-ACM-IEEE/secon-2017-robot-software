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
	accel.begin();
	drive.begin(9, 10, 11, 12);

	// Heartbeat
	pinMode(23, OUTPUT);

	// Run all task setups
	do tasks[currentTask++]->setup();
		while(currentTask != 0);
}


unsigned long frameStartTime;

int16_t max_x, max_y, max_z;

void loop() {
	// Start Heartbeat
	frameStartTime = millis();

	// System Calls
	gyro.update();
	accel.update();
	gui.update();

	// Run Current Task
	tasks[currentTask]->loop();

	//gui.showNumber(gyro.getYaw());

	if(accel.getX() > max_x || accel.getY() > max_y || accel.getZ() > max_z) {
		Serial.print(accel.getX());
		Serial.print("\t");
		Serial.print(accel.getY());
		Serial.print("\t");
		Serial.print(accel.getZ());
		Serial.println();
	}

	if(accel.getX() > max_x)
		max_x = accel.getX();
	if(accel.getY() > max_y)
		max_y = accel.getY();
	if(accel.getZ() > max_z)
		max_z = accel.getZ();

	// Finish Heartbeat
	digitalWrite(23, !digitalRead(23));
}
