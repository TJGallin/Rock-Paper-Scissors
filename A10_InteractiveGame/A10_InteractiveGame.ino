#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>
const byte lbuttonState = 4;
const byte rbuttonState = 5;
const byte switchState = 7;
volatile bool switchFlag = 0;
volatile bool lbuttonFlag = 0;
volatile bool rbuttonFlag = 0;
volatile bool AysncFlag = 0;
volatile byte state = 0;
AsyncDelay delay_1s;
float tempF;
int value;
bool leftButtonPressed;
bool rightButtonPressed;
float midi[127];
int A_four = 440; 
int count0 = 0;
int count1 = 0;
int count2 = 0;

const uint8_t spPOSITIVE[]  PROGMEM = {0x02,0xF0,0x3E,0xA5,0x45,0x45,0x57,0x5A,0xB0,0xEA,0x15,0xA4,0x56,0xAA,0xA6,0x35,0x57,0x90,0xCA,0x54,0x3A,0xA7,0x3C,0x41,0x8E,0x5B,0x61,0x92,0x69,0x87,0x23,0xAA,0xFC,0xC4,0xC4,0x56,0x05,0x20,0x81,0x8D,0x94,0x5D,0xAC,0x21,0xAA,0x6E,0x56,0x32,0x49,0x8A,0x99,0x6D,0x3A,0xE9,0xE0,0x2E,0x1E,0xB6,0xAA,0x15,0x4D,0x98,0xB8,0xC5,0x22,0x32,0x08,0xE5,0xEE,0x22,0xB2,0x41,0x01,0x57,0xB2,0x19,0x60,0x33,0xB5,0x92,0x54,0x66,0x52,0x13,0xB5,0x47,0x3D,0x9C,0xA1,0x67,0x34,0x6E,0x43,0xF7,0xCC,0x99,0x31,0x3B,0xCD,0xCD,0x91,0x56,0xE4,0x9C,0xB0,0x14,0xE3,0xA6,0xAE,0xBB,0xDD,0x5A,0xAD,0x9A,0x39,0xF7,0x41,0x40,0xB3,0x6A,0xFF,0x5A,0x39,0x55,0x79,0x05};
const uint8_t spNEGATIVE[]  PROGMEM = {0x26,0x2E,0x4C,0x24,0xCC,0x13,0xC5,0x32,0x14,0x49,0xD0,0x9C,0xA4,0x9B,0x92,0x25,0xC9,0x33,0x9C,0x6E,0x46,0x32,0x94,0x91,0x7B,0x2C,0x3E,0xD1,0x74,0x21,0x6E,0xD1,0xF8,0x84,0xCB,0x26,0x9B,0x7B,0xE3,0x13,0x4C,0x93,0xE8,0x9D,0xAB,0x46,0x30,0x4A,0x41,0x44,0xCE,0x22,0x49,0xD7,0x06,0x16,0xB5,0x7A,0x64,0xDD,0x15,0x87,0x8A,0xE2,0x95,0x75,0xA3,0xD0,0x13,0xB5,0x56,0xDA,0x94,0x70,0x75,0xD4,0x26,0x9D,0x50,0xEE,0x2E,0x22,0x1B,0x0C,0xB0,0xA8,0x85,0x03,0x16,0x0B,0x0D,0xED,0x16,0x4E,0x5A,0x16,0xBB,0xB4,0xC3,0x2A,0xA5,0x57,0x9D,0x32,0x74,0x27,0x1C,0x59,0x73,0xC2,0xD2,0x8D,0x70,0x65,0xCE,0x76,0x4B,0x33,0x22,0xE5,0x39,0xCB,0x2D,0xD5,0x93,0xA5,0xD5,0x2C,0x33,0x67,0x23,0x5A,0x5A,0x35,0xC5,0x5C,0x55,0x88,0xA9,0x35,0x36,0xF3,0x70,0xA9,0xA9,0xAA,0x98,0x00,0x4D,0x9B,0xFC,0x75,0x51,0x39};
const uint8_t spSTOP[]      PROGMEM = {0x08,0xF8,0x92,0x8D,0x00,0x5F,0x89,0x32,0xE0,0x6B,0x35,0x01,0x7C,0xAD,0x2A,0x80,0xEF,0x55,0x04,0xF0,0xA3,0x08,0x01,0xBE,0x13,0x46,0xA0,0x50,0xEE,0x2E,0x22,0x1B,0x1C,0xB0,0x8D,0xD5,0x70,0x9B,0xCE,0x10,0xB3,0x4E,0x27,0xCC,0xB1,0x3D,0x59,0x33,0x9F,0x38,0xC7,0xA9,0x74,0xD3,0x7D,0xB3,0x51,0xA4,0x58,0x9D,0xC9,0xB9,0x51,0x23,0x94,0xBB,0x8B,0xC8,0x06,0x00,0x60,0x80,0x57,0x96,0x04,0xC8,0xCE,0x1D,0x01,0x79,0x84,0x22,0xC0,0x3B,0xF7,0xFF,0x09,0x61,0x15,0x49,0x75,0x65};


long randNumber;

int song[6][2] = {
    {55, 100},
    {55, 100},
    {57, 100},
    {55, 100},  
    {60, 100},  
    {59, 100}, 
//  {127, 200},  // 127 will result in a frequency too high for the speaker to play, resulting in silence. You can use this as a "rest" or blank space in your melody
  };

int song1[12][2] = {
    {55, 50},
    {55, 50},
    {57, 50},
    {55, 50},  
    {60, 50},  
    {59, 50}, 
    {55, 50},
    {55, 50},
    {57, 50},
    {55, 50},  
    {60, 50},  
    {59, 50}, 
//  {127, 200},  // 127 will result in a frequency too high for the speaker to play, resulting in silence. You can use this as a "rest" or blank space in your melody
  };
int song2[12][2] = {
    {49, 50},
    {49, 50},
    {50, 50},
    {51, 50},  
    {52, 50},  
    {53, 50}, 
    {54, 50},
    {55, 50},
    {57, 50},
    {57, 50},  
    {58, 50},  
    {59, 50}, 
  } ; 

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
  delay_1s.start(2000, AsyncDelay::MILLIS);
  generateMIDI();
  pinMode (switchState, INPUT_PULLUP);
  attachInterrupt (digitalPinToInterrupt (switchState), switchPressed, CHANGE);
  attachInterrupt (digitalPinToInterrupt (lbuttonState), lbuttonPressed, CHANGE);
  attachInterrupt (digitalPinToInterrupt (rbuttonState), rbuttonPressed, CHANGE);
}



void loop() {
  int walue = CircuitPlayground.readCap(6);
  walue = map(walue, 0, 1023, 0, 50);
  Serial.print(walue);
  Serial.print(" ");
  Serial.print(count0);
  Serial.print(" ");
  Serial.println(count1);

   if (rbuttonFlag){
    delay(5);
    digitalWrite(rbuttonState, state);
    rbuttonFlag = 0; 
  }
  
  if (lbuttonFlag){
    delay(5);
    digitalWrite(lbuttonState, state);
    lbuttonFlag = 0; 
  }
  
  if ((digitalRead (switchState) == HIGH)) {
 switch (count0) {
  case 0:
    CircuitPlayground.clearPixels();
    CircuitPlayground.setPixelColor (9, 255,   0,   0);

    delay(200);
  break;
  case 1:
    CircuitPlayground.clearPixels();
    CircuitPlayground.setPixelColor (7, 20, 100,   0);

    delay(200);
  break;
  case 2:
    CircuitPlayground.clearPixels();
    CircuitPlayground.setPixelColor (5, 255, 255, 255);

 
    delay(200);
  break;
}
}
//randombrightnessCycle(10, 10);
pinPressed ();

if ((digitalRead (switchState) == HIGH) && (walue > 40)) {
 switch (count1) {
  case 0:
    CircuitPlayground.setPixelColor (0, 100,   25,   10);
    delay(200);
  break;
  case 1:
   
    CircuitPlayground.setPixelColor (2, 100,   110,   0);
    delay(200);
  break;
  case 2:
    CircuitPlayground.setPixelColor (4, 155, 255, 255);
    delay(200);
  break;
}
}

if (walue > 40 ) {
Serial.println("loading");
pin2 ();
delay(1000);
}

if (walue > 40 && (digitalRead (switchState) == HIGH)) {
 switch (count2) {
  case 0:
  CircuitPlayground.speaker.say(spSTOP);
   Serial.println("Tie");
   delay (200);
   song11 ();
  break;
  case 1:
    CircuitPlayground.speaker.say(spNEGATIVE);
    Serial.println("Not Win");
    delay (200);
    song12 ();
  break;
  case 2:
   CircuitPlayground.speaker.say(spPOSITIVE);
  Serial.println("Win");
  delay (200);
  song13 ();
  break;
}
}
 
 }


void pinPressed ()
{
  if(CircuitPlayground.readCap(6) > 500){
    randNumber = random(3);
    Serial.println(randNumber);
    count1 = randNumber; 
    Serial.print("count1: ");
    Serial.println(count1);
    AysncFlag = 1;
    delay(200);
  } else {
    delay (5);
  }
}

void pin2 ()
{
  if ((count0 == 0) && (count1 == 0)){
    count2 = 0;
} else if (count0 == 1 && count1 == 1){
  count2 = 0;
} else if ((count0 == 2) && (count1 == 2)){
 count2 = 0;
} else if ((count0 == 0) && (count1 == 1)){
	count2 = 1;
} else if ((count0 == 1) && (count1 == 2)){
count2 = 1;
} else if ((count0 == 2) && (count1 == 0)){
count2 = 1;
} else if ((count0 == 0) && (count1 == 2)){
count2 = 2;
} else if ((count0 == 1) && (count1 == 0)){
count2 = 2;
} else if ((count0 == 2) && (count1 == 1)) {
count2 = 2;
}
AysncFlag = 0;
}
void switchPressed ()
{
  if (digitalRead(switchState) == LOW) {
   Serial.println("NightTime Mode");
   CircuitPlayground.clearPixels();
   if(CircuitPlayground.readCap(6) > 500){
   delay(5);
   } 
  } else if (digitalRead(switchState) == HIGH) {
    Serial.println("DayTime Mode");
    CircuitPlayground.clearPixels();
  }


}

void lbuttonPressed  ()
{
  leftButtonPressed = CircuitPlayground.leftButton();
  if (leftButtonPressed && (count0 >=1)){
    count0 = count0 - 1;
   
  }
} 

void rbuttonPressed ()
{
  rightButtonPressed = CircuitPlayground.rightButton();
  if (rightButtonPressed && (count0 <=1)){
      count0 = count0 + 1;
      
  }
}

void song11 ()
{
     for(int i = 0; i < sizeof(song) / sizeof(song[0]); i++) // Calculate how many rows are in the array using: sizeof(song) / sizeof(song[0])
  {
    CircuitPlayground.playTone(midi[song[i][0]], song[i][1]); // firste one is the note, second one is the row
  }
}

void song12 ()
{
     for(int i = 0; i < sizeof(song) / sizeof(song1[0]); i++) // Calculate how many rows are in the array using: sizeof(song) / sizeof(song[0])
  {
    CircuitPlayground.playTone(midi[song1[i][0]], song1[i][1]); // firste one is the note, second one is the row
  }
}

void song13 ()
{
     for(int i = 0; i < sizeof(song) / sizeof(song2[0]); i++) // Calculate how many rows are in the array using: sizeof(song) / sizeof(song[0])
  {
    CircuitPlayground.playTone(midi[song2[i][0]], song2[i][1]); // firste one is the note, second one is the row
  }
}

void generateMIDI()
{
  for (int x = 0; x < 127; ++x)
  {
    midi[x] = (A_four / 32.0) * pow(2.0, ((x - 9.0) / 12.0));
    Serial.println(midi[x]);
  }
}