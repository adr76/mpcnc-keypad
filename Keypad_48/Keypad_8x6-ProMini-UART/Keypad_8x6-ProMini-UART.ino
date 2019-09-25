/*
  MPCNC Keypad Module
  ProMini -> UART -> RAMPS
  
  #Pins
    MCP23017 I2C    SDA - A4, SCL - A5
    MAX7219         CS - 10, DIN - 11, CLK - D13
    Joystick        X - A0, Y - A1,   Btn - D8
    
  #Keypad Module 
    Matrix 48keys 6 rows x 8 cols
    Driver MCP23017 I2C
  
  #Joystick
    PS2 Analog for XY Axis
    Button Fast/Slow move
    
  #Led Module:
    MAX7219 3x 7Seg 8Digit module
   
*/
//#include "keypad_4x6.h"
#include "keypad_8x6.h"
//#include "joystick.h"

#define LOOP_DELAY 500

Keypad_MC17 keyPad(makeKeymap(hexaKeys), rowPins, colPins, KEY_ROWS, KEY_COLS, I2CADDR);

void setup(){
  //pinMode(JOY_BTN, INPUT);
  Serial.begin(115200);
  
  Wire.begin();
  keyPad.begin();
}
 
void loop(){
//-- Keypad events
//  keypadEvent();

//-- Joystick events
//joystick_print();
//joystick_move();

//delay(LOOP_DELAY);
}

void keypadEvent(){
  char key = keyPad.getKey();
  byte n = getKeyNum(key);
  
  if (key != NO_KEY){
    Serial.println(key); // Key Name
    //Serial.println(getKeyRowCol(n)); // Key Name
    //Serial.println(keyName[n]); // Key Name
    //Serial.println(keyGcode[n]); // Key GCODE   
  }    
}
