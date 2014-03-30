neopixel-analog-clock
=====================

Using an [adafruit Gemma](http://learn.adafruit.com/introducing-gemma/introduction) to power 60 [Neopixel LED's](http://learn.adafruit.com/adafruit-neopixel-uberguide) to make a clock.

##**Hardware Configuration**

D1 is configured as an output for the Neopixels

D0 is configured as an input

D2 is configured as an input

##**Features:**

####**Brightness Adjustment**
  Shorting D0 to GND will increase the brightness
  
  Shorting D2 to GND will decrease the brightness
  
####**Time Adjustment**
  Shorting both D0 AND D2 to GND will increment the seconds varible by 1
