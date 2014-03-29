#include <Adafruit_NeoPixel.h>

#define N_LEDS 12
#define PIN    1

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

int clockInt = 0;            // digital pin 2 is now interrupt 0
int masterClock = 0;         // counts rising edge clock signals
int seconds = 0;             // variable
int minutes = 0;             // variable
int hours = 0;

void setup() {
  strip.begin();
}

void loop() {
  int j;
  uint32_t blue = strip.Color(0, 0, 16);
  uint32_t red  = strip.Color(16, 0, 0);
  uint32_t green  = strip.Color(0, 16, 0);
  uint32_t teal  = strip.Color(0, 12, 12);
  uint32_t yellow  = strip.Color(12, 12, 0); 
  uint32_t purple  = strip.Color(12, 0, 12);
  uint32_t white  = strip.Color(12, 12, 12);
  
  masterClock ++;        // with each clock rise add 1 to masterclock count
  if(masterClock == 1599) // 8mHz reached or 1 seccond elapsed 
  {                         
    seconds ++;          // after one 8mHz cycle add 1 second ;)
    masterClock = 0;     // Reset after 1 second is reached
  }
   
  if(seconds == 12)
  {
    minutes ++;          // increment minutes by 1
    seconds = 0;         // reset the seconds variable
  }
  if(minutes == 12)
  {
    hours ++;            // increment hours by 1
    minutes = 0;         // reset the minutes variable
  }
  if(hours == 12)
  {
    hours = 0;            // reset the hours variable
  }
  for(j=0; j<= 12; j++) strip.setPixelColor(j, 0);
  if(minutes == hours && seconds == hours){
    strip.setPixelColor(seconds, white);
  }else if(seconds == minutes){
    strip.setPixelColor(seconds, purple);
    strip.setPixelColor(hours, green);
  }else if(seconds == hours){
    strip.setPixelColor(minutes, red);
    strip.setPixelColor(hours, teal);
  }else if(minutes == hours){
    strip.setPixelColor(minutes, yellow);
    strip.setPixelColor(seconds, blue);
  }
  else{
    strip.setPixelColor(seconds, blue);
    strip.setPixelColor(minutes, red);
    strip.setPixelColor(hours, green);
  }
  strip.show();
}
