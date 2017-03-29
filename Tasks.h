#ifndef TASKS_H
#define TASKS_H

#include "Robot.h"

class FirstTask : public Task {
	void setup();
	void loop();
};

class LastTask : public Task {
	void setup();
	void loop();
};

#endif
