#include <Adafruit_NeoPixel.h>

#define N_LEDS 60
#define PIN    1

// Increase Brightness
#define SWITCH 0

// Decrease Brightness
#define SWITCH2 2

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

int trim = 510;              // frequency trim (higher number == slower second speed)
int clockInt = 0;            // digital pin 2 is now interrupt 0
int masterClock = 0;         // counts rising edge clock signals
int seconds = 0;             // variable
int minutes = 0;             // variable
int hours = 0;

int brightness = 16;
int partialBrightness = brightness-brightness/4;
void setup() {
  // initialize the SWITCH pins as inputs.
  pinMode(SWITCH, INPUT);
  pinMode(SWITCH2, INPUT);
  // ...with a pullup
  digitalWrite(SWITCH, HIGH);
  digitalWrite(SWITCH2, HIGH);
  strip.begin();
}

void loop() {
  int j;
  masterClock ++;        // with each clock rise add 1 to masterclock count
  
  if(masterClock == trim/4 || masterClock == trim/3 || masterClock == trim/2 || masterClock == trim){
    // Time Adjuster
    if(!digitalRead(SWITCH2) && !digitalRead(SWITCH)){
       minutes = minutes+1;
    }
    // END Time Adjuster
    // Brightness Adjuster
    if (! digitalRead(SWITCH2)){
      if(brightness > 1){
        brightness = brightness -1;
      }
    }
    if (! digitalRead(SWITCH)){
      if(brightness < 255){
        brightness = brightness +1;
      }
    }
    // End Brightness Adjuster
  }
  
  partialBrightness = brightness-brightness/4;
  uint32_t blue = strip.Color(0, 0, brightness);
  uint32_t red  = strip.Color(brightness, 0, 0);
  uint32_t green  = strip.Color(0, brightness, 0);
  uint32_t teal  = strip.Color(0, partialBrightness, partialBrightness);
  uint32_t yellow  = strip.Color(partialBrightness, partialBrightness, 0); 
  uint32_t purple  = strip.Color(partialBrightness, 0, partialBrightness);
  uint32_t white  = strip.Color(partialBrightness, partialBrightness, partialBrightness);
  

  if(masterClock == trim) // 8mHz reached or 1 seccond elapsed 
  {                         
    seconds ++;          // after one 8mHz cycle add 1 second ;)
    masterClock = 0;     // Reset after 1 second is reached
  }
  if(seconds == N_LEDS)
  {
    minutes ++;          // increment minutes by 1
    seconds = 0;         // reset the seconds variable
  }
  if(minutes == N_LEDS)
  {
    hours ++;            // increment hours by 1
    minutes = 0;         // reset the minutes variable
  }
  if(hours == N_LEDS)
  {
    hours = 0;            // reset the hours variable
  }

  // light the appropriate LED's
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
  
  //clear old seconds place unless it is being used by hours or minutes
  if(seconds-1 != hours && seconds-1 != minutes){
    strip.setPixelColor(seconds-1, 0);
  }
  if(minutes-1 != seconds && minutes-1 != hours){
    strip.setPixelColor(minutes-1, 0);
  }
  if(hours-1 != minutes && hours-1 != seconds){
    strip.setPixelColor(hours-1, 0);
  }
  strip.show();
}
