/* -----------------------------------------------------------------------------------------------------------------------
 LED maximum values need to be defined here. TLC5947 has 12bit PWM channels, meaning the LED values range from 0 to 4095.

 Here we defined two maximum values: maxLED and maxLEDNat, respectively called in the serial monitor by "a" and "b".
 Ideally, one would set up maxLED values to equalise their brithness amonsgt them by the us of a power-meter.
----------------------------------------------------------------------------------------------------------------------- */



const  int  max_LED1            = 4095;  // First LED maximum intensity
const  int  min_LED1            = 2000;  // First LED minimum intensity

const  int  max_LED2            = 4095;  // Second LED maximum intensity
const  int  min_LED2            = 2000;  // Second LED minimum intensity

const  int  max_LED3            = 4095;  // Third LED maximum intensity
const  int  min_LED3            = 2000;  // Third LED minimum intensity

const  int  max_LED4            = 4095;  // Fourth LED maximum intensity
const  int  min_LED4            = 2000;  // Fourth LED minimum intensity
