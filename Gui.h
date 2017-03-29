#ifndef GUI_H
#define GUI_H

#include "Robot.h"
#include "libraries/RGBShield/Adafruit_RGBLCDShield.h"
#include "libraries/RGBShield/utility/Adafruit_MCP23017.h"

class Gui {
	Adafruit_RGBLCDShield lcd;

	char current[2][17] = {"                ", "                "};
	char display[2][17] = {"                ", "                "};

	public:
		void begin();
		void update();
		void test(int col, int row, char val);
};

extern Gui gui;

#endif
