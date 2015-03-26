/*
Generic example for the SRF modules 02, 08, 10 and 235.
Only the SRF08 uses the light saensor so when any other 
range finder is used with this code the light reading will 
be a constant value. 
*/

#include <Wire.h>

#define SRF_ADDRESS  0x70        // Address of the SRXX (0xE0 > 1 = 0x70)
#define CMD          (byte)0x00  // Command Register, values of 0 being sent with write have to be masked as a byte to stop them being misinterpreted as NULL this is a bug with arduino 1.0
#define LIGHT_REG    0x01        // Register to read light sensor (SRF08 only)
#define RANGE_REG    0x02        // Register for start of ranging data

byte highByte = 0x00;            // Stores high byte from ranging
byte lowByte = 0x00;             // Stored low byte from ranging

void setup(){
  Serial.begin(9600);                   // Open serial monitor at 9600 baud to see ping results.
  Wire.begin();                               
  delay(100);                           // Waits to make sure everything is powered up before sending or receiving data
  
  int softRev = getSoft(SRF_ADDRESS);   // Calls function to get software revision
  Serial.print("Rev: ");
  Serial.println(softRev);  
  
  //changeAddress(0x70, 0xE6);
}

void loop(){
  
  int rangeData = getRange(SRF_ADDRESS); // Calls a function to get range reading
  
  int lightData = getLight(SRF_ADDRESS); // Call function to get light reading 
  
  Serial.print("Range: ");
  Serial.print(rangeData); 
  Serial.println("cm");
  
  Serial.print("Light: ");
  Serial.print(lightData); 
 
  delay(100);                         // Wait before looping
}

int getRange(int address){            // This function gets a ranging from the SRF08
  
  int range = 0; 
  
  Wire.beginTransmission(address);    // Start communticating with SRF08
  Wire.write(CMD);                    // Send Command Byte
  Wire.write(0x51);                   // Send 0x51 to start a ranging (result in cm)
  Wire.endTransmission();
  
  delay(100);                         // Wait for ranging to be complete (change according to sensor maximum range)
  
  Wire.beginTransmission(address);    // Start communicating with SRFmodule
  Wire.write(RANGEBYTE);              // Call the register for start of ranging data
  Wire.endTransmission();
  
  Wire.requestFrom(address, 2);       // Request 2 bytes from SRF module
  while(Wire.available() < 2);        // Wait for data to arrive
  highByte = Wire.read();             // Get high byte
  lowByte = Wire.read();              // Get low byte

  range = (highByte << 8) + lowByte;  // Put them together
  
  return(range);                      // Returns Range
}

int getLight(int address){            // Function to get light reading
  
  Wire.beginTransmission(address);
  Wire.write(LIGHTBYTE);              // Call register to get light reading
  Wire.endTransmission();
  
  Wire.requestFrom(address, 1);       // Request 1 byte
  while(Wire.available() < 0);        // While byte available
  int lightRead = Wire.read();        // Get light reading
    
  return(lightRead);                  // Returns lightRead
}

int getSoft(int address){             // Function to get software revision
  
  Wire.beginTransmission(address);    // Begin communication with the SRF module
  Wire.write(CMD);                    // Sends the command bit, when this bit is read it returns the software revision
  Wire.endTransmission();
  
  Wire.requestFrom(address, 1);       // Request 1 byte
  while(Wire.available() < 0);        // While byte available
  int software = Wire.read();         // Get byte
    
  return(software);                               
}

// The following code changes the address of a Devantech Ultrasonic Range Finder (SRF02, SRF8 or SRF02)
// Usage: changeAddress(0x70, 0xE6);
// Note: old address must be Arduino compatible (7 bits) and new address must be 8 bits
void changeAddress(byte oldAddress, byte newAddress)
{
  //write the following to the old address: (0xA0, 0xAA, 0xA5, newAddress )
	
  Wire.beginTransmission(oldAddress);
  Wire.write(byte(0x00));
  Wire.write(byte(0xA0));
  Wire.endTransmission();

  Wire.beginTransmission(oldAddress);
  Wire.write(byte(0x00));
  Wire.write(byte(0xAA));
  Wire.endTransmission();

  Wire.beginTransmission(oldAddress);
  Wire.write(byte(0x00));
  Wire.write(byte(0xA5));
  Wire.endTransmission();

  Wire.beginTransmission(oldAddress);
  Wire.write(byte(0x00));
  Wire.write(newAddress);
  Wire.endTransmission();
}


