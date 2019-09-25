/*
  MPCNC Keypad Module
  ProMini -> UART -> RAMPS
  
  #Pins
    I2C       SDA - A4, SCL - A5
    TM1640    DIN - D9, SCK - D10
    Joystick  X - A0, Y - A1, Btn - D8
    
  #Keypad Module 
    Matrix 4x6 keys 
    Driver MCP23017 I2C
  
  #Joystick
    PS2 Analog for XY Axis
    Button Fast/Slow move
    
  #Led Module:
   Driver TM1640
   1x 8x8 Matrix (Common Catode)
   1x 4x7 Digits (Common Anode)   
*/
//#include "keypad_4x6.h"
#include "keypad_4x6.h"
#include "joystick.h"
#include "TM16xxLed.h"

#define LOOP_DELAY 500

Keypad_MC17 keyPad(makeKeymap(hexaKeys), rowPins, colPins, KEY_ROWS, KEY_COLS, I2CADDR);

void setup(){
  pinMode(JOY_BTN, INPUT);
  Serial.begin(115200);
  
  Wire.begin();
  keyPad.begin();
  
  ledSetup();
}
 
void loop(){
//-- Keypad events
//  keypadEvent();

//-- Joystick events
//joystick_print();
//joystick_move();

delay(LOOP_DELAY);
}

void keypadEvent(){
  char key = keyPad.getKey();
  byte n = getKeyNum(key);
  
  if (key != NO_KEY){
    //Serial.println(keyName[n]); // Key Name
    Serial.println(keyGcode[n]); // Key GCODE   
  }    
}
