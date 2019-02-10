/* -----------------------------------------------------------------------------------------------------------------------
 LED maximum values need to be defined here. TLC5947 has 12bit PWM channels, meaning the LED values range from 0 to 4095.

 Here we defined two maximum values: maxLED and maxLEDNat, respectively called in the serial monitor by "a" and "b".
 Ideally, one would set up maxLED values to equalise their brithness amonsgt them by the us of a power-meter.
----------------------------------------------------------------------------------------------------------------------- */



const  int  maxR            = 4095;  // Maximal Red LED intensity
const  int  maxRNat         = 4095;  // Maximal Natural Stat Red LED intensity

const  int  maxG            = 4095;  // Maximal Green LED intensity
const  int  maxGNat         = 4095;  // Maximal Natural Stat Green LED intensity

const  int  maxB            = 4095;  // Maximal Blue LED intensity
const  int  maxBNat         = 4095;  // Maximal Natural Stat Blue LED intensity

const  int  maxU            = 4095;  // Maximal UV LED intensity
const  int  maxUNat         = 4095;  // Maximal Natural Stat UV LED intensity
