//89 notes
int all_notes[] = {
31,
33,
35,
37,
39,
41,
44,
46,
49,
52,
55,
58,
62,
65,
69,
73,
78,
82,
87,
93,
98,
104,
110,
117,
123,
131,
139,
147,
156,
165,
175,
185,
196,
208,
220,
233,
247,
262,
277,
294,
311,
330,
349,
370,
392,
415,
440,
466,
494,
523,
554,
587,
622,
659,
698,
740,
784,
831,
880,
932,
988,
1047,
1109,
1175,
1245,
1319,
1397,
1480,
1568,
1661,
1760,
1865,
1976,
2093,
2217,
2349,
2489,
2637,
2794,
2960,
3136,
3322,
3520,
3729,
3951,
4186,
4435,
4699,
4978
};

void setup() {
// initialize serial communication:
  Serial.begin(9600);

  // Initialize range sensor-pertinent values
  pinMode(11, OUTPUT);
  digitalWrite(11, HIGH);
  avg = 0;

// Initialize speaker-pertinent values
  pinMode(4, OUTPUT); //buzzer

  // This should be modified so only certain parts
  //  will play when we want them to ... ?
  //sing the tunes
  for (int NOTE = 0; NOTE < 89; NOTE++)
  {
      Serial.print(all_notes[NOTE]);
      buzz(4, all_notes[NOTE], 20);
      delay(6);
      buzz(4, all_notes[NOTE], 20);
      delay(50);
  }
}

void loop()
{
}

void buzz(int targetPin, long frequency, long length) {
  digitalWrite(13, HIGH);
  long delayValue = 1000000 / frequency / 2; // calculate the delay value between transitions
  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
  //// there are two phases to each cycle
  long numCycles = frequency * length / 1000; // calculate the number of cycles for proper timing
  //// multiply frequency, which is really cycles per second, by the number of seconds to
  //// get the total number of cycles to produce
  for (long i = 0; i < numCycles; i++) { // for the calculated length of time...
    digitalWrite(targetPin, HIGH); // write the buzzer pin high to push out the diaphram
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(targetPin, LOW); // write the buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue); // wait again or the calculated delay value
  }
  digitalWrite(13, LOW);
}
