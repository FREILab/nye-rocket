New Year's Eve Sustainable Rocket Project
=========================================
December 2025, FREILab, Germany


Collection of Information, Tasks etc. for this project.
Please feel free to edit.

Description:
------------
We want to build tiny rockets, that can be put on the cork of a bottle of sparkling wine.
Thus, the gas pressure in the bottle will propel the rocket. Different versions may be built to obtain rockets of different difficulty levels, so that beginners and pros may join the project and have fun. 

There rocket may have one or several of these features:
- LEDs that glow during the flight of the rocket
- a buzzer that makes sound during the flight
- some confetti may be released during the flight that will be illuminated by LEDs from the rocket 
- an accelerometer to detect the launch of the rocket
- a motor with a propeller to speed the rocket (when used without a bottle of sparkling wine, or in addition to it)
- others? please feel free to add...

The shape of the rocket:
- You may use a rocket housing to be created with a 3D-Printer
- Alternatively, two PCBs in the shape of a rocket can be put together perpendicularly, to achieve a 3D shape.
- A prototype may be created with the laser cutter to check the feasibility of the two-PCB-version.

Electronics:
------------
- we may use a tiny battery, a rechargeable battery (LiPo/Li/NiMH), a super-cap or standard capacitors
- to recharge the rocket, an external charger may be used
- as an accelerometer, we can use this: https://www.mouser.de/ProductDetail/MEMSIC/MXC4005XC?qs=RcG8xmE7yp3iyYgWLmAtUw%3D%3D
- alternatively, we may use some mass (e.g. the battery) to open/close a contact during acceleration.
- to obtain higher voltages (needed for some LED-types), we can use a square wave signal from the MCU to drive a step-up converter, consisting of a FET (may be omitted, if the output driver of the MCU is strong enough), one choke, one capacitor. To control the output voltage two resistors are needed in addition.
- Marc Ihle has many devices of the MSP430G2210IDR that can be used for free for this project. A JTAG-emulator is available to program the devices.
  This MCU needs ultra low power (thus, needs no power switch), has a comparator that can be used to e.g. control a step-up converter
  to keep the luminance constant over the whole battery voltage range.



Schedule:
- New Year's Eve 2025 is approaching rapidly! So let's keep the project(s) small enough for this year. PCBs should be ordered not later than on 2025/12/22 (assuming they are ordered in China).




