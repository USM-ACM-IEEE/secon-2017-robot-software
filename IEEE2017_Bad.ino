#include "Arduino.h"
#include "libraries/MemoryFree/MemoryFree.h"
#include <Wire.h>
#include "Servo.h"

// RGB Shield
#include "libraries/RGBShield/Adafruit_RGBLCDShield.h"
#include "libraries/RGBShield/utility/Adafruit_MCP23017.h"

// MPU6050
#include "libraries/I2CDev/I2Cdev.h"
#include "libraries/MPU6050/MPU6050_6Axis_MotionApps20.h"

// LCD Panel
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

/******************************************************************************/

// MPU Stuff
MPU6050 mpu;

#define INTERRUPT_PIN 2
#define LED_PIN 13
bool blinkState = false;

// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorFloat gravity;    // [x, y, z]            gravity vector
float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

bool calibrated = false;
float offset[3];

/******************************************************************************/

// Heartbeat
bool led_state = false;

// Game Variables
unsigned long int start_time;
bool started = false;
int stage = 0;

// Performance Analysis
int index = 0;
unsigned int times[5];
unsigned long int time;

// GUI
int gui_x = 0;
int gui_y = 0;
bool gui_s = false;
bool gui_pressed = false;


/******************************************************************************
*******************************************************************************
******************************************************************************/

volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
    mpuInterrupt = true;
}

void mpu_setup() {
	Serial.println(F("Initializing I2C devices..."));
	mpu.initialize();
	pinMode(INTERRUPT_PIN, INPUT);

	Serial.println(F("Testing device connections..."));
	Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));

	Serial.println(F("Initializing DMP..."));
	devStatus = mpu.dmpInitialize();

    if (devStatus == 0) {
        // turn on the DMP, now that it's ready
        Serial.println(F("Enabling DMP..."));
        mpu.setDMPEnabled(true);

        // enable Arduino interrupt detection
        Serial.println(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
        attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
        mpuIntStatus = mpu.getIntStatus();

        // set our DMP Ready flag so the main loop() function knows it's okay to use it
        Serial.println(F("DMP ready! Waiting for first interrupt..."));
        dmpReady = true;

        // get expected DMP packet size for later comparison
        packetSize = mpu.dmpGetFIFOPacketSize();
    } else if (devStatus == 1) {
		Serial.print(F("DMP Initialization failed: initial memory load failed"));
    } else if (devStatus == 2) {
		Serial.print(F("DMP Initialization failed: configuration updates failed"));
	}
}

void mpu_loop() {
    mpuInterrupt = false;
    mpuIntStatus = mpu.getIntStatus();
    fifoCount = mpu.getFIFOCount();

    if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
        mpu.resetFIFO();
        //Serial.println(F("FIFO overflow!"));
    } else if (mpuIntStatus & 0x02) {
        while (fifoCount < packetSize)
			fifoCount = mpu.getFIFOCount();

        mpu.getFIFOBytes(fifoBuffer, packetSize);
    }
}

/******************************************************************************
*******************************************************************************
******************************************************************************/

float fps() {
  float sum = 0;
  int i;

  for(i=0; i<5; i++) {
	  sum += times[i];
  }

  return 1000/(sum/5.0);
}

bool inRange(unsigned long int a, unsigned long int b, unsigned long int c) {
	return (a < b) && (b < c);
}

void gui() {
  uint8_t buttons = lcd.readButtons();

  if (buttons) {
	lcd.clear();
	lcd.setCursor(0,0);

	if (buttons & BUTTON_UP) {
		if(!gui_pressed && gui_y > 0) {
			gui_y--;
		}

		gui_pressed = true;
	}
	if (buttons & BUTTON_DOWN) {
		if(!gui_pressed && gui_y < 10) {
			gui_y++;
		}

		gui_pressed = true;
	}
	if (buttons & BUTTON_SELECT) {
		gui_s = !gui_s;
	}
  } else {
	  gui_pressed = false;
  }

  lcd.setCursor(0, 0);
  switch(gui_y) {
		case 1:
			// RAM Usage
			lcd.print("RAM Usage: ");
			lcd.print(8192-freeMemory());
			lcd.print("B");
			break;
		case 2:
			dumpGyro_LCD();
			break;
  }

  // Uptime
  lcd.setCursor(0, 1);
  lcd.print((millis()/1000)/60);
  lcd.print(":");
  int seconds = (millis()/1000)%60;
  if(seconds < 10) {
	  lcd.print(0);
  }
  lcd.print(seconds);
  lcd.print("  ");

  // FPS
  lcd.setCursor(9, 1);
  lcd.print(fps());
  lcd.print("fps   ");
}


/******************************************************************************
*******************************************************************************
******************************************************************************/

void game_code() {

	unsigned int game_time = millis() - start_time;

	if(inRange(0, game_time, 5000)) {
		if(stage != 1) {
			stage = 1;

			lcd.clear();
			lcd.setCursor(0, 0);
			lcd.print("Stage 1");
		}
	}

	if(inRange(5000, game_time, 10000)) {
		if(stage != 2) {
			stage = 2;

			lcd.clear();
			lcd.setCursor(0, 0);
			lcd.print("Stage 2");
		}
	}

	if(inRange(10000, game_time, 15000)) {
		if(stage != 3) {
			stage = 3;

			lcd.clear();
			lcd.setCursor(0, 0);
			lcd.print("Stage 3");
		}
	}

	if(game_time > 15000) {
		if(stage != 4) {
			stage = 4;

			lcd.clear();
			lcd.setCursor(0, 0);
			lcd.print("Done!");
		}
	}
}

/******************************************************************************
*******************************************************************************
******************************************************************************/

class RobotDrive {
	Servo frontLeft, frontRight, rearLeft, rearRight;

public:
	void begin(int kFrontLeft, int kFrontRight, int kRearLeft, int kRearRight);
	void MecanumDrive_Cartesian(float x, float y, float rotation);
};

void RobotDrive::begin(int kFrontLeft, int kFrontRight, int kRearLeft, int kRearRight)
{
	frontLeft.attach(kFrontLeft);
	frontRight.attach(kFrontRight);
	rearLeft.attach(kRearLeft);
	rearRight.attach(kRearRight);
}

void RobotDrive::MecanumDrive_Cartesian(float x, float y, float rotation) {
	// Generate Vectors
	float fl = x + y + rotation;
	float fr = -x + y - rotation;
	float rl = -x + y + rotation;
	float rr = x + y - rotation;

	// Calculate uS
	int fl_uS = 1500+(fl*500);
	int fr_uS = 1500+(fr*500);
	int rl_uS = 1500+(rl*500);
	int rr_uS = 1500+(rr*500);

	// Send to motors
	frontLeft.writeMicroseconds(fl_uS);
	frontRight.writeMicroseconds(fr_uS);
	rearLeft.writeMicroseconds(rl_uS);
	rearRight.writeMicroseconds(rr_uS);
}

/******************************************************************************
*******************************************************************************
******************************************************************************/

void dumpGyro_Serial() {
	mpu.dmpGetQuaternion(&q, fifoBuffer);
	mpu.dmpGetGravity(&gravity, &q);
	mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

	if(!calibrated) {
		offset[0] = ypr[0] * -180/M_PI;
		offset[1] = ypr[1] * -180/M_PI;
		offset[2] = ypr[2] * -180/M_PI;

		calibrated = true;
	}

	float angle[3], ranged[3], adjusted[3], modded[3], mapped[3];

	for(int i = 0; i<3; i++) {
		angle[i] = ypr[i] * -180/M_PI;
		ranged[i] = map(angle[i], -180, 180, 0, 360);
		adjusted[i] = ranged[i] - offset[i];
		modded[i] = int(adjusted[i]) % 360;
		mapped[i] = map(modded[i], 0, 360, -180, 180);
	}

	Serial.print("ypr\t");
	Serial.print(mapped[0]);
	Serial.print("\t");
	Serial.print(mapped[1]);
	Serial.print("\t");
	Serial.println(mapped[2]);
}

void dumpGyro_LCD() {
	mpu.dmpGetQuaternion(&q, fifoBuffer);
	mpu.dmpGetGravity(&gravity, &q);
	mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

	if(!calibrated) {
		offset[0] = ypr[0] * -180/M_PI;
		offset[1] = ypr[1] * -180/M_PI;
		offset[2] = ypr[2] * -180/M_PI;

		calibrated = true;
	}

	float angle[3], ranged[3], adjusted[3], modded[3], mapped[3];

	for(int i = 0; i<3; i++) {
		angle[i] = ypr[i] * -180/M_PI;
		ranged[i] = map(angle[i], -180, 180, 0, 360);
		adjusted[i] = ranged[i] - offset[i];
		modded[i] = int(adjusted[i]) % 360;
		mapped[i] = map(modded[i], 0, 360, -180, 180);
	}

	lcd.setCursor(0, 0);
	lcd.print("ypr: ");
	lcd.print(int(mapped[0]));
	lcd.print(", ");
	lcd.print(int(mapped[1]));
	lcd.print(", ");
	lcd.print(int(mapped[2]));
	lcd.print("    ");
}

RobotDrive drive;

void setup() {
	// Wire
	Wire.begin();
	Wire.setClock(400000);

	// Serial
	Serial.begin(115200);

	// LCD Panel
	lcd.begin(16, 2);
	
	// MPU
	mpu_setup();

	// Heartbeat
	pinMode(13, OUTPUT);

	drive.begin(9, 10, 11, 12);
}

void turn(int target, float speed) {
	mpu_loop();

	mpu.dmpGetQuaternion(&q, fifoBuffer);
	mpu.dmpGetGravity(&gravity, &q);
	mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

	float offset, angle, ranged, adjusted, modded, mapped, output;

	offset = ypr[0] * -180/M_PI;

	do {
		mpu_loop();

		mpu.dmpGetQuaternion(&q, fifoBuffer);
		mpu.dmpGetGravity(&gravity, &q);
		mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

		angle = ypr[0] * 180/M_PI;
		ranged = map(angle, -180, 180, 0, 360);
		adjusted = ranged - offset;
		modded = int(adjusted) % 360;
		mapped = map(modded, 0, 360, -180, 180);

		lcd.setCursor(0,0);

		output = min(speed*abs(target-mapped), 0.2);

		if(target-mapped > 0) {
			//lcd.print(output);
			drive.MecanumDrive_Cartesian(0, 0, output);
		} else if(target-mapped < 0) {
			//lcd.print(-output);
			drive.MecanumDrive_Cartesian(0, 0, -output);
		}
	} while(abs(target-mapped) > 0);

	drive.MecanumDrive_Cartesian(0, 0, 0);
}

void loop() {
	// Heartbeat Code
	time = millis();
	index = (index + 1) % 5;

	// System Control Loops
	gui();
	mpu_loop();

	// More GUI stuff that should be moved
	if(time < 25000) {
		if(gui_y == 0) {
			lcd.setCursor(0, 0);
			lcd.print("Initializing...");
		}
	} else {
		if(!started && gui_y == 0) {
			lcd.setCursor(0, 0);
			lcd.print("Ready!?          ");

			if(gui_s) {
				gui_s = false;
				started = true;
				start_time = millis();
			}
		}
	}

	if(started) {
		//game_code();
		turn(-90, 0.019);
		//drive.MecanumDrive_Cartesian(0.5, 0, 0);
	}

	if(millis() > 25000) {
		dumpGyro_Serial();
	}

	// Finish up heartbeat
	times[index] = millis() - time;
	led_state = !led_state;
	digitalWrite(13, led_state);
}
