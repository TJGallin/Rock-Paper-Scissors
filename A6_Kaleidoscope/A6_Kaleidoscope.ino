#include <AsyncDelay.h>
#include <Adafruit_CircuitPlayground.h>
const byte switchState = 7;
const byte lbuttonState = 4;
const byte rbuttonState = 5;
volatile byte state = 0;
bool leftButtonPressed;
bool rightButtonPressed;
volatile bool switchFlag = 0;
volatile bool lbuttonFlag = 0;
volatile bool rbuttonFlag = 0;

int brightness[] = {0, 25, 50, 75, 100, 125, 150, 175, 200, 225, 255};
int leds[] = {1, 2, 3, 4, 5, 6, 7, 8, 9}; 
volatile int count = 0;

void setup(void)
{
  pinMode (switchState, INPUT_PULLUP);
  CircuitPlayground.begin();
  Serial.begin(9600);
  attachInterrupt (digitalPinToInterrupt (switchState), switchPressed, CHANGE);
  attachInterrupt (digitalPinToInterrupt (lbuttonState), lbuttonPressed, CHANGE);
  attachInterrupt (digitalPinToInterrupt (rbuttonState), rbuttonPressed, CHANGE);
}

void loop(void)
{
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
  switch (count) {
  case 0:
    rainbowCycle(100, 10);
    Serial.println("rainbowCycle");    
    //randombrightnessCycle(100, 10);
    //Serial.println("randombrightnessCycle");
     delay(1000);
    break;
  case 1:
     randomCycle(10, 10);
     Serial.println("randomCycle");
     delay(200);
    break;
  case 2:
     brightnessCycle(100, 10);
     Serial.println("brightnessCycle");
     delay(200);
    break;
  case 3:
    ledCycle(100, 10);
    Serial.println("ledCycle");
    delay(200);
    break;
  case 4:
     randomledCycle (100, 100);
     Serial.println("randomledCylce");
     delay(200);
     break;
  }
  } else if (switchFlag){
    delay(5);
    digitalWrite(switchState, state);
    switchFlag = 0; 
  }
}

void switchPressed ()
{ 
    CircuitPlayground.clearPixels();
}

void lbuttonPressed  ()
{
  leftButtonPressed = CircuitPlayground.leftButton();
  if (leftButtonPressed && (count >=1)){
    count = count - 1;
    Serial.println(count);
    }
} 

void rbuttonPressed ()
{
  rightButtonPressed = CircuitPlayground.rightButton();
  if (rightButtonPressed && (count <=3)){
      count = count + 1;
      Serial.println(count);
  }
}

void rainbowCycle(int currentSpeed, int stripLen) {
  uint32_t offset = millis() / currentSpeed;
  CircuitPlayground.setBrightness(40);
  for(int i=0; i<10; ++i) {
    CircuitPlayground.setPixelColor(i, CircuitPlayground.colorWheel(((i * 256 / stripLen) + offset) & 255));
    delay(100);
  }
}

void randomCycle(int currentSpeed, int stripLen) {
  uint32_t offset = millis() / currentSpeed;
  CircuitPlayground.setBrightness(40);
  for(int i=0; i<10; i++) {
    int randomColor = random(i);
    CircuitPlayground.setPixelColor(i, CircuitPlayground.colorWheel(((randomColor * 256 / stripLen) + offset) & 255));
    delay(100);
  }
}

void brightnessCycle(int currentSpeed, int stripLen) {
  uint32_t offset = millis() / currentSpeed;
  for(int j=0; j < 10; j++) {
    CircuitPlayground.setBrightness(brightness[j]);
    delay (100);
    for(int i=0; i<10; i++) { // i is the # of LED's activated
      CircuitPlayground.setPixelColor(i, CircuitPlayground.colorWheel(((i * 256 / stripLen) + offset) & 255));
    }
  }
}


void randombrightnessCycle(int currentSpeed, int stripLen) {
  uint32_t offset = millis() / currentSpeed;
  for(int j=0; j < 10; j++) {
    CircuitPlayground.setBrightness(random(brightness[j]));
    delay (100);
    for(int i=0; i<10; i++) { // i is the # of LED's activated
      CircuitPlayground.setPixelColor(i, CircuitPlayground.colorWheel(((i * 256 / stripLen) + offset) & 255));
    }
  }
}


void ledCycle(int currentSpeed, int stripLen) {
  uint32_t offset = millis() / currentSpeed;
  CircuitPlayground.setBrightness(40);
  for(int i=0; i < 10; i++) {
    CircuitPlayground.setPixelColor(leds[i], CircuitPlayground.colorWheel(((i * 256 / stripLen) + offset) & 255));
    delay(200);
    CircuitPlayground.clearPixels();
    delay(100);   
  }
}

void randomledCycle(int currentSpeed, int stripLen) {
  uint32_t offset = millis() / currentSpeed;
  CircuitPlayground.setBrightness(40);
  for(int i=0; i < 10; i++) {
    int randomLED = random(leds[i]);     
    CircuitPlayground.setPixelColor(randomLED, CircuitPlayground.colorWheel(((i * 256 / stripLen) + offset) & 255)); //which LED and color types
    delay(200);
    CircuitPlayground.clearPixels();
    delay(100);
  }
}