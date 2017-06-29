/*
  Row-Column Scanning an 8x8 LED matrix with X-Y input

 This example controls an 8x8 LED matrix using two analog inputs

 created 27 May 2009
 modified 30 Aug 2011
 by Tom Igoe

 This example works for the Lumex  LDM-24488NI Matrix. See
 http://sigma.octopart.com/140413/datasheet/Lumex-LDM-24488NI.pdf
 for the pin connections

 For other LED cathode column matrixes, you should only need to change
 the pin numbers in the row[] and column[] arrays

 rows are the anodes
 cols are the cathodes
 ---------

 Pin numbers:
 Matrix:
 * Digital pins 2 through 13,
 * analog pins 2 through 5 used as digital 16 through 19
 Potentiometers:
 * center pins are attached to analog pins 0 and 1, respectively
 * side pins attached to +5V and ground, respectively.

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/RowColumnScanning

 see also http://www.tigoe.net/pcomp/code/category/arduinowiring/514 for more
 */


// 2-dimensional array of row pin numbers:
const int row[8] = {
  // 2, 7, 19, 5, 13, 18, 12, 16
  9, 4, 10, 6, 17, 11, 16, 13
};

// 2-dimensional array of column pin numbers:
const int col[8] = {
  // 5, 15, 14, 8, 12, 7, 3, 2
  5, 15, 14, 8, 12, 7, 3, 2
};

// 2-dimensional array of pixels:
int pixels[8][8];

void setup() {

    for (int thisPin = 0; thisPin < 8; thisPin++) {
        pinMode(col[thisPin], OUTPUT);
        pinMode(row[thisPin], OUTPUT);

        digitalWrite(col[thisPin], LOW);
        digitalWrite(row[thisPin], HIGH);
    }


    initMatrix();

    pixels[1][1] = HIGH;
    refreshScreen();

delay(300);
    initMatrix();
    pixels[7][1] = HIGH;
    refreshScreen();
}

void initMatrix() {
    // initialize the pixel matrix:
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            pixels[x][y] = LOW;
        }
    }
}

void loop() {

    setPixels4();
    refreshScreen();
}

void animateUpload() {

}

int uploadImage[5][8] = {
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {1, 1, 0, 0, 0, 0, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
};

void setPixels4() {

    int startRow = 4;

    for (int thisCol = 0; thisCol < 8; thisCol++) {
        for (int thisRow = 0; thisRow < 8; thisRow++) {
            if (thisRow < startRow) {
                pixels[thisRow][thisCol] = 0;
            } else {
                pixels[thisRow][thisCol] = uploadImage[thisRow - startRow][thisCol];
            }
        }
    }
}

void refreshScreen() {
    for (int thisRow = 0; thisRow < 8; thisRow++) {

        digitalWrite(col[thisRow], LOW);
        digitalWrite(row[thisRow], HIGH);

        for (int thisCol = 0; thisCol < 8; thisCol++) {

            int pixelValue = pixels[thisRow][thisCol];

            if (pixelValue == HIGH) {
                digitalWrite(col[thisCol], HIGH);
                digitalWrite(row[thisRow], LOW);
            }
        }

    }
}
