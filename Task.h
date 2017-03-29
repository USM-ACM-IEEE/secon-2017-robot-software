#ifndef TASK_H
#define TASK_H

#include "Robot.h"

class Task {
public:
	virtual void setup() = 0;
	virtual void loop() = 0;
};

// Task Stuff
extern int currentTask;
extern Task* tasks[];

#endif
