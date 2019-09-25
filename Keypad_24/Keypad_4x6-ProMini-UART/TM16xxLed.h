// TM1640 Led Display
// Arduino: LED Matrix Editor 
// http://xantorohara.github.io/led-matrix-editor/
// http://xantorohara.blogspot.ru/2015/09/arduino-led-matrix-editor.html

#include <TM1640.h>
#include <TM16xxMatrix.h>
#include "TM16xxFont.h"

TM1640 module(9, 10);  // (DIN, CLK)
TM16xxMatrix matrix(&module, 16, 8); // (&object, nCols, nRows)

#define IMAGES ROWS_RIGHT // DIGITS LETERS SIGNS - MatrixFont.h
const int IMAGES_LEN = sizeof(IMAGES)/8;
  
void setMatrix(uint64_t image) {
  for (int i = 0; i < 8; i++) {
    byte row = (image >> i * 8) & 0xFF;
    for (int j = 0; j < 8; j++) {
      matrix.setPixel(j, i, bitRead(row, j));
    }
  }
}

void setAllDigit(uint64_t image) {
  for (int dig = 0; dig < 4; dig++) {
    byte group = (image >> dig * 8) & 0xFF;
    for (int seg = 0; seg < 8; seg++) {
      bool state = bitRead(group, seg);
      matrix.setPixel(seg+8, dig, state);
    }
  }
}

void setDigit(byte data, byte digit) {
  for (int i = 0; i < 8; i++) {
    boolean state = (data & 1) ? HIGH : LOW;
    matrix.setPixel(8+i, digit-1, state);
    data >>= 1;
  }
}

void ledSetup(){
  module.setupDisplay(true,0); //Set intensity (0-7)
  module.clearDisplay();
  matrix.setAll(false); // clear all
    
  //## Matrix Led - comm catode
  //(col[0-7], row[0-7], on/off)
  //matrix.setPixel(0, 0, true); 
  //setMatrix(M_A); 

  //## Digit Led - comm anode
  //(seg[8-15], digit[0-3], on/off)
  //matrix.setPixel(8, 0, true);  
  //setDigit(TM16XX_NUMBER_FONT[15], 1); // (segments, digit[1-4])
  setAllDigit(0x000000003f3f0671); // hex data set all digits
}