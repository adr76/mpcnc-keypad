#include <Keypad_MC17.h>
#include <Keypad.h>
#include <Wire.h>

#define I2CADDR 0x20
#define KEY_ROWS 6
#define KEY_COLS 4

#define getKeyNum(x) ((byte)x - 65) // Get Key Number 

byte hexaKeys[KEY_ROWS][KEY_COLS] = {
  {'A','B','C','D'}, // 'A' -> DEC 65
  {'E','F','G','H'},
  {'I','J','K','L'},
  {'M','N','O','P'},
  {'Q','R','S','T'},
  {'U','V','W','X'}  // 'X' -> DEC 88
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

byte rowPins[KEY_ROWS] = {5,4,3,2,1,0};
byte colPins[KEY_COLS] = {9,8,7,6};

/* 
Keypad_MC17 keyPad(makeKeymap(hexaKeys), rowPins, colPins, KEY_ROWS, KEY_COLS, I2CADDR);

void keypadRun(){
  Wire.begin();
  keyPad.begin();
}

void keypadEvent(){
  char key = keyPad.getKey();
  byte n = keyNum(key);
  
  if (key != NO_KEY){
    Serial.println(keyName[n]);     
  }    
}

void keypadPrintKey(){
  char key = keyPad.getKey();
  
  if (key != NO_KEY){
    Serial.print("Key: ");
    Serial.print(key);
    Serial.print("\tDEC ");
    Serial.print(key, DEC);
    Serial.print("\tNum ");
    Serial.println(keyNum(key));     
  }    
} */