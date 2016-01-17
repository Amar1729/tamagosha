const int ford = 9;  // orange
const int back = 6;  // blue
const int left = 5;  // black
const int right = 3; // yellow

#include "math.h"

void setup() {
  Serial.begin(9600);
  
  pinMode(ford, OUTPUT);
  pinMode(back, OUTPUT);
  pinMode(left, OUTPUT);
  pinMode(right, OUTPUT);

  // Start off straight, but parked
  drive(0.0);
  turn(0.0);

  // Give time to power on car, move hands
  //delay(3000);
}

void loop() {
/*
  // Forward for a bit
  drive(0.4);
  delay(1000);
  drive(0.0);
  delay(500);
  drive(-0.4);
  delay(1000);
  drive(0.0);
  delay(1000);

  drive(0.7);
  delay(800);
*/

  //drive(0.2);
  //turn(0.8);

  //turn(1.0);
  turn(0.6);
  delay(500);
  turn(1);
  delay(500);
  turn(0.6);
  delay(500);
  turn(0.0);
  delay(500);
  
  turn(-0.5);
  turn(-0.1);
  delay(500);
  turn(0.0);
  delay(500);

  //Circle(3);
  
  
}

// dir:   [-1.0, +1.0]
// represents backward/forward in sign
// represents magnitude of speed
void drive(float dir) {
  // Backward
  if (dir < 0.0) {
    analogWrite( back, abs(dir)*255 );
    analogWrite( ford, 0 );
  }
  // Forward
  else if (dir > 0.0) {
    analogWrite( ford, dir*255 );
    analogWrite( back, 0 );
  }
  // Stop
  else /*(dir == 0.0)*/ {
    analogWrite(ford, 0);
    analogWrite(back, 0);
  }
}

// dir:   [-1.0, +1.0]
// represents left/right in sign
// represents magnitude of turn (?)
//
// Turn() not complete: function should
//     end by turning back to straight
void turn(float dir) {
  // Left
  if (dir < 0.0) {
    analogWrite(left, abs(dir)*255);
    analogWrite(right, 0);
    //delay(); //based on |dir|
    //turn(0.0);
  }
  // Right
  else if(dir > 0.0) {
    analogWrite(right, dir*255);
    analogWrite(left, 0);
    //delay(); //based on |dir|
    //turn(0.0);
  }
  // Straight
  else /*(dir == 0.0)*/ {
    analogWrite(left, 0);
    analogWrite(right,0);
  }
}

void Circle(double radius) {
  double r = 1 / (1+exp(-1*radius));
  turn(r);
  drive(0.4);
  delay(1000);
  turn(0.0);
  drive(0.0);
}

