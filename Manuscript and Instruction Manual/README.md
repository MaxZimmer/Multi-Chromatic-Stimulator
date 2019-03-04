<p align="right"><img src="https://github.com/BadenLab/Zebrafish-visual-space-model/blob/master/Images/Logo.png" width="300"/>
<h1 align="center">Instruction Manual</h1></p>
<h1 align="center">Multi-Chromatic Stimulator</h1>
<h4 align="center">An OpenSource LED stimulator for visual and optogenetics stimulation in combination with 2-photon recording</h4>
<p align="center"><h6 align="right">by M.J.Y. Zimmermann, A.M. Chagas, P. Bartel, T. Baden</h6></p>

This project is licensed under the [GNU General Public License v3.0](https://github.com/MaxZimmer/Multi-Chromatic-Stimulator/blob/master/LICENSE)

***

- [Overview](#Overview)
- [Assembling the Stimulator](#Assembling-the-Stimulator)
- [OpenSpritzer can deliver neurotransmitters with millisecond precision to control neural activity](#Openspritzer-in-neuroscience-experiments.)
- [OpenSpritzer is suitable for delivering infectious agents including viral delivery of opsins for optogenetics](#Openspritzer-for-microinjection-of-infectious-agents)


***

## Overview
<img align="right" width="325" height="225" src="https://github.com/MaxZimmer/Multi-Chromatic-Stimulator/blob/master/Images/Components.png">
This document contains detailed assembly instructions, a software guideline to customize stimuli, and includes a parts list. The Arduino code and 3D printing files (SCAD and STL) can be downloaded [here](https://github.com/MaxZimmer/Multi-Chromatic-Stimulator/tree/master/3D%20Designs/Stimulator), and further modified to fit customise purposes. The aim of this device is to finely control LEDs used in combination with a 2-photon microscope.
The device consists of a custom-designed PCB, an [ESP32 development board](https://learn.adafruit.com/adafruit-huzzah32-esp32-feather) (or an Arduino Nano if the stimulator does not need to be combined with a 2 photon microscope), a [LED driver](https://learn.adafruit.com/tlc5947-tlc59711-pwm-led-driver-breakout/overview) and various off-the-shelf components.


## Assembling the stimulator

<p align="center"><h4 align="left">1 – Obtaining the custom-designed PCB</h4></p>
<img align="right" width="325" height="225" src="https://github.com/MaxZimmer/Multi-Chromatic-Stimulator/blob/master/Images/Scematics.png">
From the GitHub repository, one can find the [gerber.zip folder](https://github.com/MaxZimmer/Multi-Chromatic-Stimulator/tree/master/PCB/Stimulator) needed to order the PCB to any manufacturer company (i.e. https://jlcpcb.com). Ordering a minimum of 5 units should not cost more than £10. Gerber files were designed with [KiCad 5.0](http://kicad-pcb.org/). Schematics and PCB footprint can be downloaded and modified from the same repository if need be.


****

<p align="center"><h4 align="left">2 – Soldering the custom-designed PCB</h4></p>
<img align="left" width="325" height="225" src="https://github.com/MaxZimmer/Multi-Chromatic-Stimulator/blob/master/Images/PCB01.png">
The board is self-explanatory. On the left, two options are available, one for the Arduino (close rows) the other for the ESP (spread rows). There is no need to solder more JST pins that the number of LED required for the desired stimulator. The two resistors at the bottom are a voltage divider for the ESP32 only (There’s no need to solder any resistor here if the Arduino option is chosen). ESP32 unlike Arduino Nano, works on a 3.3V logic; no higher tension should be sent to this board. Since most TTL deliver 5V pulses, we selected a 220/470Ω divider to bring a 5V blanking signal into a 3.3V input. Depending on the blanking signal generator used, this divider can be modified to fit one’s personal design or bypassed by only bridging the 220Ω resistor.
## Supplementary Figure S3 TESSA PICTURE
The Adafruit TLC5947 LED driver is a constant current driver configured by default to set the current level at 15mA per channel, which is virtually safe for any LED. However, one can operate at different current by replacing the on-board reference resistor with a through hole resistor. The driver is capable to deliver up to 30mA, the graph below shows the relationship between resistance and output current.
<img align="right" width="325" height="225" src="https://github.com/MaxZimmer/Multi-Chromatic-Stimulator/blob/master/Images/reference%20resistor%20vs%20output%20current.png">

****





<p align="center"><h4 align="left">3 – Mounting the potentiometer</h4></p>
<img align="right" width="325" height="225" src="https://github.com/MaxZimmer/Multi-Chromatic-Stimulator/blob/master/Images/Potentiometer%20PCB.png">
In order to finely adjust each LED power, we added multiple-turn trimmer potentiometers to our design. A simple solution is to manufacture the appropriate PCB board (We provide multiple options on the [GitHub repository](https://github.com/MaxZimmer/Multi-Chromatic-Stimulator/tree/master/PCB/Potentiometer%20Mounts)). Otherwise, one can make its own little PCB by using a solderable board. 
Each potentiometer connects its ClockWise (pin 3) to the LED (+) stimulator JST pin; and its Base (pin 2) to the LED (+) leg. The LED (-) stimulator JST pin connects the LED (-) leg directly.








ESP32 driver : https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers

Arduino core for ESP32 chip https://github.com/espressif/arduino-esp32#using-through-arduino-ide


<img align="center" src="https://github.com/MaxZimmer/Multi-Chromatic-Stimulator/blob/master/Images/Visual%20Stimulator.png" width="1000"/>
<img align="center" src="https://github.com/MaxZimmer/Multi-Chromatic-Stimulator/blob/master/Images/Schematics.png" width="1000"/>


</p>
