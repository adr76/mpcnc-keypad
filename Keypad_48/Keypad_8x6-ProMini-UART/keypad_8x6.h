#include <Keypad_MC17.h>
#include <Keypad.h>
#include <Wire.h>

#define I2CADDR 0x20
#define KEY_ROWS 6
#define KEY_COLS 8 

#define getKeyNum(x) ((byte)x - 65) // Get Key Number 

byte rowPins[KEY_ROWS] = {0,1,2,3,4,5};
byte colPins[KEY_COLS] = {15,14,13,12,11,10,9,8};

char hexaKeys[KEY_ROWS][KEY_COLS] = { // 48 Keys
  {'A','B','C','D','E','F','G','H'},  //0..7
  {'I','J','K','L','M','N','O','P'},  //8..15
  {'Q','R','S','T','U','V','W','X'},  //16..23
  {'Y','Z','[','z',']','^','_','`'}, //24..31
  {'a','b','c','d','e','f','g','h'},  //32..39
  {'i','j','k','l','m','n','o','p'}   //40..48
};

char* keyGcode[] = {
  "G28 X0 Y0",  "G28 Z0",       "G0 X0 Y0",     "G0 Z0",
  "G90",        "G91",          "G92 X0 Y0",    "G92 Z0",
  "M114",       "M42 P44 S1",   "M42 P44 S255", "M42 P44 S0", 
  "G30",        "G29",          "G33",          "G91\nG0 Z1\nG90",
  "M401",       "M402",         "M999",         "G91\nG0 Z-1\nG90",
  "M112",       "M24",          "M22",          "M84"
};

char* keyName[] = {
  "Home XY",  "Home Z",       "Move X0Y0",   "Move Z0",
  "ABS",      "REL",          "X0 Y0",       "Z0",
  "M114",     "Laser 1%",     "Laser 100%",  "Laser Off", 
  "Z-probe",  "G29",          "G33",         "Z Up",
  "Save XYZ", "Restore XYZ",  "M999",        "Z Down",
  "Kill",     "SD >|",        "SD X",        "Motor Off"
};

byte getKeyRowCol(byte keyNum){
  byte row,col;
  
  if (keyNum < 8) row = 10;
    else if (keyNum > 7 && keyNum < 16) row = 20;
    else if (keyNum > 15 && keyNum < 24) row = 30;
    else if (keyNum > 23 && keyNum < 32) row = 40;
    else if (keyNum > 31 && keyNum < 40) row = 50; 
    else if (keyNum > 39) row = 60;
    
  col = keyNum % KEY_COLS;
  
  return row + col;
}

/* byte keypadEvent( char key){
  byte keyCode; 
  switch(key){
    case '1': // Home XY
      keyCode = 0;
      break;
    case '2': // Home Z
      keyCode = 1;
      break;
    case '3': // Move X0 Y0
      keyCode = 2;
      break;
    case '4': // Move Z0
      keyCode = 3;
      break;
    case '5': // Set ABS coords
      keyCode = 4;
      break;
    case '6': // Set REL coords
      keyCode = 5;
      break;
    case '7': // Set X0 Y0
      keyCode = 6;
      break;
    case '8': // Set Z0
      keyCode = 7;
      break;
    case '9': // Center lines by laser
      keyCode = 8;
      break;
    case '0': // Laser 1%
      keyCode = 9;
      break;
    case 'A': // Laser 100%
      keyCode = 10;
      break;
    case 'B': // Laser Off
      keyCode = 11;
      break;
    case 'C': // Z-probe Point
      keyCode = 12;
      break;
    case 'D': // Z-probe 3Point 
      keyCode = 13;
      break;
    case 'E': // Z-probe Map
      keyCode = 14;
      break;
    case 'F': // Z UP
      keyCode = 15;
      break;
    case 'G': // Save XYZ
      keyCode = 16;
      break;
    case 'H': // Restore XYZ
      keyCode = 17;
      break;
    case 'I': // Error Reset
      keyCode = 18;
      break;
    case 'J': // Z DOWN
      keyCode = 19;
      break;
    case 'K': // Emergency Stop
      keyCode = 20;
      break;
    case 'L': // SD print Start/resume
      keyCode = 21;
      break;
    case 'M': // Release SD card
      keyCode = 22;
      break;
    case 'N': // Motor  Off
      keyCode = 23;
      break;
  }  
  return keyCode;  
} */