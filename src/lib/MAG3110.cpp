/*
mag3110.cpp
libary for using the I2C mag3110 magnetometer

(c) Written by Jeroen Cappaert for NanoSatisfi, August 2012

 - 21 Mar. 2016
 Library modified to work with Arduino Lucky Shield
 by andrea[at]arduino[dot]org
 
*/

#include <Arduino.h>
#include "MAG3110.h"
#include <Wire.h>

//Constructor
MAG3110::MAG3110()
{
  
}



// Configure magnetometer
void MAG3110::begin(void) {
  //CTRL_REG1
  //DR2|DR1|DR0|OS1|OS0|FastRead|Trigger|ActiveMode|
  // 0 | 1 | 1 | 1 | 1 |    0   |   0   |    1     |=dec121
  Wire.beginTransmission(MAG_ADDR);// transmit to device 0x0E
  Wire.write(0x10);                // cntrl register1
  Wire.write(0x79); // Active Mode, 1.25 Hz datarate, 8x oversampling
  Wire.endTransmission();          // stop transmitting
  
  delay(15);
  
  //CTRL_REG2: 
  //AutoMagRst|---|Raw|Mag_Rst|---|---|---|---|
  //    1     | 0 | 0 |   0   | 0 | 0 | 0 | 0 |
  Wire.beginTransmission(MAG_ADDR);// transmit to device 0x0E
  Wire.write(0x11);                // cntrl register2
  Wire.write(0x80);        // Auto resets before each measurement
  Wire.endTransmission();          // stop transmitting
}


// read X value
int MAG3110::readx(void)
{
  int xl, xh;  //define the MSB and LSB
  
  Wire.beginTransmission(MAG_ADDR); // transmit to device 0x0E
  Wire.write(0x01);              // x MSB reg
  Wire.endTransmission();       // stop transmitting
 
  delayMicroseconds(2); //needs at least 1.3us free time between start and stop
  
  Wire.requestFrom(MAG_ADDR, 1); // request 1 byte
  while(Wire.available())    // slave may send less than requested
  { 
    xh = Wire.read(); // receive the byte
  }
  
  delayMicroseconds(2); //needs at least 1.3us free time between start and stop
  
  Wire.beginTransmission(MAG_ADDR); // transmit to device 0x0E
  Wire.write(0x02);              // x LSB reg
  Wire.endTransmission();       // stop transmitting
 
  delayMicroseconds(2); //needs at least 1.3us free time between start and stop
  
  Wire.requestFrom(MAG_ADDR, 1); // request 1 byte
  while(Wire.available())    // slave may send less than requested
  { 
    xl = Wire.read(); // receive the byte
  }
  
  int xout = (xl|(xh << 8)); //concatenate the MSB and LSB
  //return xout;
  if (xout & 0b1000000000000000) 
  {
    return float ((~xout & 0b0111111111111111)+ 1)*(-1) ;
   }
  return float (xout);
}

//read Y value
int MAG3110::ready(void)
{
  int yl, yh;  //define the MSB and LSB
  
  Wire.beginTransmission(MAG_ADDR); // transmit to device 0x0E
  Wire.write(0x03);              // y MSB reg
  Wire.endTransmission();       // stop transmitting
 
  delayMicroseconds(2); //needs at least 1.3us free time between start and stop
  
  Wire.requestFrom(MAG_ADDR, 1); // request 1 byte
  while(Wire.available())    // slave may send less than requested
  { 
    yh = Wire.read(); // receive the byte
  }
  
  delayMicroseconds(2); //needs at least 1.3us free time between start and stop
  
  Wire.beginTransmission(MAG_ADDR); // transmit to device 0x0E
  Wire.write(0x04);              // y LSB reg
  Wire.endTransmission();       // stop transmitting
 
  delayMicroseconds(2); //needs at least 1.3us free time between start and stop
  
  Wire.requestFrom(MAG_ADDR, 1); // request 1 byte
  while(Wire.available())    // slave may send less than requested
  { 
    yl = Wire.read(); // receive the byte
  }

  
  int yout = (yl|(yh << 8)); //concatenate the MSB and LSB
   if (yout & 0b1000000000000000) 
   {
     //float yout1 = ((~yout & 0b0111111111111111)+ 1)*(-1) ; 
     
  
    return float ((~yout & 0b0111111111111111)+ 1)*(-1) ;
   }
  return float (yout);

}

// read Z value
int MAG3110::readz(void)
{
  int zl, zh;  //define the MSB and LSB
  
  Wire.beginTransmission(MAG_ADDR); // transmit to device 0x0E
  Wire.write(0x05);              // z MSB reg
  Wire.endTransmission();       // stop transmitting
 
  delayMicroseconds(2); //needs at least 1.3us free time between start and stop
  
  Wire.requestFrom(MAG_ADDR, 1); // request 1 byte
  while(Wire.available())    // slave may send less than requested
  { 
    zh = Wire.read(); // receive the byte
  }
  
  delayMicroseconds(2); //needs at least 1.3us free time between start and stop
  
  Wire.beginTransmission(MAG_ADDR); // transmit to device 0x0E
  Wire.write(0x06);              // z LSB reg
  Wire.endTransmission();       // stop transmitting
 
  delayMicroseconds(2); //needs at least 1.3us free time between start and stop
  
  Wire.requestFrom(MAG_ADDR, 1); // request 1 byte
  while(Wire.available())    // slave may send less than requested
  { 
    zl = Wire.read(); // receive the byte
  }
  
  int zout = (zl|(zh << 8)); //concatenate the MSB and LSB
  //return zout;
  if (zout & 0b1000000000000000) 
  {
    //float yout1 = ((~yout & 0b0111111111111111)+ 1)*(-1) ; 
    return float ((~zout & 0b0111111111111111)+ 1)*(-1) ;
  }
  return float (zout);
}

MAG3110 mag3110;

