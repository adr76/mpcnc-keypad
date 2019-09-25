/* file CustomKeypad_MC17 Feb 2/13
||@file CustomKeypad.pde
|| @version 1.0
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Demonstrates changing the keypad size and key values.
|| #
    Use with I2C i/o G. D. (Joe) Young Feb 28/12

    Use with MCP23008 I2C i/o G. D. (Joe) Young Jul 29/12
    Use with MCP23016 I2C i/o G. D. (Joe) Young Feb 2/13
    Use with MCP23017 I2C i/o G. D. (Joe) Young May 19/14
*/
#include <Keypad_MC17.h>
#include <Keypad.h>        // GDY120705
#include <Wire.h>

#define I2CADDR 0x20

const byte ROWS = 6; //four rows
const byte COLS = 4; //five columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'B','A','C','K'},
  {'P','-','+','/'},
  {'7','8','9','X'},
  {'4','5','6','E'},
  {'1','2','3','F'},
  {'0','#','.','='}
};
byte rowPins[ROWS] = {0, 1, 2, 3, 4 ,5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 7, 8, 9}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad_MC17 customKeypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS, I2CADDR); 

void setup(){
//  Wire.begin( );
  customKeypad.begin( );        // GDY120705
  Serial.begin(115200);
}
  
void loop(){
  char customKey = customKeypad.getKey();
  
  if (customKey != NO_KEY){
    Serial.println(customKey);
  }
}
