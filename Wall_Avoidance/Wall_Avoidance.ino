#include "math.h"

// Motors
const int ford = 9;  // orange
const int back = 6;  // blue
const int left = 5;  // black
const int right = 3; // yellow

// Ultrasound sensor
const int triggerPin = 12;
const int echoPin = 13;

void setup() {
  Serial.begin(9600);

  // Initialize motors
  pinMode(ford, OUTPUT);
  pinMode(back, OUTPUT);
  pinMode(left, OUTPUT);
  pinMode(right, OUTPUT);

  // Start off straight, but parked
  drive(0.0);
  turn(0.0);

  // Start ultrasonic sensor
  pinMode(11, OUTPUT);
  digitalWrite(11, HIGH);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);


  // Give time to power on car, remove hands
  delay(3000);
}

void loop() {
  // Drive forward until we hit something?
  forward();

  unsigned int clear_front = 0;
  unsigned int clear_right = 0;

  while(clear_front==0 && clear_right==0) {
    clear_front = look_forward();
    clear_right = look_right();
  }

  if(clear_right == 1) {
    fix_right();
  }

  if(clear_front == 1) {
    fix_forward();
  }
}

// Watch out in front of you!
unsigned int look_forward() {
  long duration, cm;

// The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
// Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);           // get rid of delay()
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(5);           // get rid of delay()
  digitalWrite(triggerPin, LOW);

// duration of HIGH pulse
  duration = pulseIn(echoPin, HIGH);
  
// Speed of sound = 340 m/s = 29 us/cm
// Divide by two (parallax of sensor)
  cm = duration / 29 / 2;

  if (cm < 10) {
    return 1; // too close!
  }
  else {
    return 0; // we're good
  }
}

// Checks to the right of the car
unsigned int look_right() {
  if (analogRead(A5)==0) {
    return 1; // too close!
  }
  else {
    return 0; // we're good
  }
}

// Take a 3point left turn
void fix_forward() {}

// Swivel to the left slightly
void fix_right() {}


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

