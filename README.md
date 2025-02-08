Laser Control System with ATtiny85

This project involves creating a precise control system for a high-power Nichia NUBM38 laser module using an ATtiny85 microcontroller. The laser, rated at 75W, is driven at 60V and 3A, and the system is powered by a 6S LiPo battery (~24V). A DC-DC converter boosts the voltage to the required level.


Hardware Overview:

Microcontroller: ATtiny85, chosen for its simplicity and efficiency.

Power Management: A 6S LiPo battery powers the system, monitored by a battery guard.

Voltage Regulation: A DC-DC converter boosts the voltage to 60V at 3A.

Cooling System: The laser’s heatsink temperature is monitored, and a fan, controlled via a MOSFET, adjusts its speed based on temperature.

Modular Mounting: The heatsink and fan are mounted on a gun-like holder, which is connected via a cable and plug to the main control electronics stored in a backpack.


Key Features:

Display: A TM1637 display shows battery voltage and laser temperature, alternating every 10 seconds.

Temperature Control: The fan kicks in at 27°C and reaches full speed at 40°C, managed by a MOSFET and gate driver.

Battery Monitoring: A battery guard prevents over-discharge, ensuring the LiPo battery’s longevity.

Coding: The project avoids the Arduino framework, using PlatformIO and C++ for more direct hardware control. Managing ADCs and PWM without the Arduino libraries was challenging but rewarding, providing better performance and understanding.
