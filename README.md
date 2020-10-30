# LEDmatrix-timetable
A time table/reminder system for classrooms - [See Project](https://marjerie.github.io/projects/TT)

A device that displays the time table, time, temperature (in Celsius), date, day and month. 
This device is specially designed for classrooms. 
A real-time clock (RTC) module which comprises of a DS3231 IC, an EPROM to store memory and Lithium button battery to provide power to the module is used. 
This handy module keeps accurate time using a tiny coin-cell, and is very simple to connect to your Arduino project. 
A driver library allows your program to easily set or read the time and date. 
We control the four 8×8 LED Matrix using the MAX7219 driver and the Arduino board. 
The IC is capable of driving 64 individual LEDs while using only 3 wires for communication with the Arduino,
and what’s more we can daisy chain multiple drivers and matrixes and still use the same 3 wires.
