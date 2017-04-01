#include <Wire.h>
#include "i2c.h"

#include "i2c_MAG3110.h"
MAG3110 mag3110;


void setup()
{
    Serial.begin(115200);

    Serial.print("Probe MAG3310: ");
    if (mag3110.initialize())  Serial.println("Sensor found!");
    else
    {
        Serial.println("Sensor missing");
        while(1) {};
    }
}
float xyz_uT[3];
float xyz_uF[3];

float oldMeasurement;
float newMeasurement;

int i = 0;
void loop()
{
    mag3110.getMeasurement(xyz_uT);   
    xyz_uF[0]+=xyz_uT[0];
    xyz_uF[1]+=xyz_uT[1];
    xyz_uF[2]+=xyz_uT[2];
    i++;

    if (i>19)
    {
        xyz_uT[0]=xyz_uF[0]/20;
        xyz_uT[1]=xyz_uF[1]/20;
        xyz_uT[2]=xyz_uF[2]/20;
    
        Serial.print(" X: ");
        Serial.print(xyz_uT[0],2);
        Serial.print(" \tY: ");
        Serial.print(xyz_uT[1],2);
        Serial.print(" \tZ: ");
        Serial.print(xyz_uT[2],2);
        Serial.println("");

        xyz_uF[0]= 0;
        xyz_uF[1] = 0;
        xyz_uF[2] = 0;
        i = 0;

        newMeasurement = xyz_uT[0];
    }
    oldMeasurement = xyz_uT[0];

    if ((newMeasurement - oldMeasurement) >8)
    {
      Serial.println("LightSaber Found");
    }
    
    delay(50);
}

/**<

Program size:
A1.0.5: 7144b
A1.5.7: 6860b
A1.6.3: 6766b / 493b
 */
