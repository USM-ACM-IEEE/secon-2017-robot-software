#ifndef TASKS_H
#define TASKS_H

#include "Robot.h"

class FirstTask : public Task {
	void setup();
	void loop();
};

class Forward1 : public Task {
	long int startTime = 0;

	void setup();
	void loop();
};

class Sweep1 : public Task {
	long int startTime = 0;

	void setup();
	void loop();
};

class Sweep2 : public Task {
	long int startTime = 0;

	void setup();
	void loop();
};

class LastTask : public Task {
	void setup();
	void loop();
};

#endif
