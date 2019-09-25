#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

int pinCS = 9; // Din 11, CLK 13
int nHorDisp = 4;
int nVerDisp = 1;

Max72xxPanel matrix = Max72xxPanel(pinCS, nHorDisp, nVerDisp);

String tape = "Hellow word!"; // текст, который будет плыть
int wait = 50; // время между крайними перемещениями букв

int spacer = 1; // расстояние между буквами
int width = 5 + spacer; // размер шрифта

void setup() {
    matrix.setIntensity(0); // яркость   
    for (int i = 0 ; i < nHorDisp; i++) matrix.setRotation(i, 1); //Set display rotation  
}

void loop() {
    for ( int i = 0 ; i < width * tape.length() + matrix.width() - 1 - spacer; i++ ) {
        matrix.fillScreen(LOW);

        int letter = i / width;
        int x = (matrix.width() - 1) - i % width;
        int y = (matrix.height() - 8) / 2; // center the text vertically

        while ( x + width - spacer >= 0 && letter >= 0 ) {
            if ( letter < tape.length() ) {
                matrix.drawChar(x, y, tape[letter], HIGH, LOW, 1);
            }
            letter--;
            x -= width;
        }

        matrix.write();
        delay(wait);
    }
}
