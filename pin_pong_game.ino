#include "LedControl.h"
LedControl aman = LedControl(9, 11, 10, 1);          // create an instance of a Matrix

int column = 0, row = 8;                       // decide where the ball will start
int directionX = 1, directionY = 1;                    // make sure it heads from left to right first
int paddle1 = 5, paddle1Val;                           // Pot pin and value
int movement_interval = 150;
int counter = 0;

void setup() {
  aman.shutdown(0, false);
  aman.setIntensity(0, 10);                         // Set the brightness to a medium values
  randomSeed(analogRead(0));
  oops();
}
void oops() {
  for (int x = 0; x < 3; x++) {
    aman.clearDisplay(0);
    delay(250);
    for (int y = 0; y < 8; y++) {
      aman.setRow(0, y, 255);
    }
    delay(200);
  }
  counter = 0;
  movement_interval = 250;
  column = 0;
  row = random(8);
  displayDashAndDot();
}

void displayDashAndDot() {
  aman.clearDisplay(0);
  aman.setLed(0, column, row, HIGH);
  aman.setLed(0, 7, paddle1Val, HIGH);
  aman.setLed(0, 7, paddle1Val + 1, HIGH);
  aman.setLed(0, 7, paddle1Val + 2, HIGH);
  if (!(counter % 10)) {
    movement_interval -= 5;
  }
  delay(movement_interval);
}

void loop() {
  paddle1Val = analogRead(paddle1);
  paddle1Val = map(paddle1Val, 0, 1024, 0, 6);
  if (column == 6 && (paddle1Val == row ||
                      paddle1Val + 1 == row || paddle1Val + 2 == row)) {
    directionX = -1;
  }
  if (column == 0) {
    directionX = 1;
  }
  if (row == 7) {
    directionY = -1;
  }
  if (row == 0) {
    directionY = 1;
  }
  if (column == 7) {
    oops();
  }
  column += directionX;
  row += directionY;
  displayDashAndDot();
  counter++;
}
