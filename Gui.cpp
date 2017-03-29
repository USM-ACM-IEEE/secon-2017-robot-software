#include "Robot.h"

Gui gui;

void Gui::begin() {
	lcd.begin(16, 2);

	lcd.setCursor(0, 0);
	lcd.print(display[0]);

	lcd.setCursor(0, 1);
	lcd.print(display[1]);
}

void Gui::test(int col, int row, char val) {
	display[row][col] = val;
}

void Gui::update() {
	for(int row = 0; row < 2; row++) {
		for(int col = 0; col < 16; col++) {
			if(current[row][col] != display[row][col]) {
				current[row][col] = display[row][col];

				lcd.setCursor(col, row);
				lcd.print(current[row][col]);
			}
		}
	}
}
