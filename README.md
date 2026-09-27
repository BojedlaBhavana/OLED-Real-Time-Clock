# OLED RTC Digital & Analog Clock

A real-time clock project using an OLED display and DS3231 RTC module.
The clock automatically switches between digital and analog display modes.

## Features

- Real-time digital clock
- Analog clock display
- Automatic mode switching every 3 seconds
- Date display in digital mode
- Loading/booting screen
- Smooth OLED refresh
- Accurate timekeeping using DS3231 RTC
- I2C communication

## Components Used

- Arduino-compatible microcontroller
- 0.96-inch OLED Display (128x64)
- DS3231 RTC Module
- Breadboard
- Jumper Wires
- USB Cable

## Software & Libraries

- Arduino IDE
- C/C++
- Adafruit GFX Library
- Adafruit SSD1306 Library
- RTClib
- Wire Library

## Working

The DS3231 RTC module provides the current time and date to the
microcontroller through I2C communication.

The microcontroller processes the time information and displays it
on the 128x64 OLED screen.

The display automatically switches between:

1. Digital Clock
2. Analog Clock

The mode changes every 3 seconds.

## Digital Mode

The digital mode displays:

- Hours
- Minutes
- Seconds
- Date

Example:

```text
12:30:45
2026-09-27