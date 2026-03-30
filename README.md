---
project_id: P2508PE-01
title: Desktop Clock
owner: personal
status: COMPLETED
ideation_date: 2025-09-03
domain: "- physical"
subdomains: "- electrical"
repository: "[https://github.com/Sudharsshan/ESP8266-Desktop-clock-using-P10-LED-module.git](https://github.com/Sudharsshan/ESP8266-Desktop-clock-using-P10-LED-module.git)"
hardware: "true"
tags:
  - electrical
  - hardware
  - p10
  - project
---


# Introduction

- A big desktop clock using #P10 LED panel and #ESP8266 NodeMCU V1.0.

# Requirements

- ESP8266
- P10 LED MODULE
- 255W ATX POWER SUPPLY
- JUMPER WIRES
- BREADBOARD
- SWITCH
- Laptop/Desktop & internet

# Procedure


- Firstly check if the power supply that you are about to use for the #P10  are capable of supplying 5V@5A. Else, it will cause the #PSU (Power Supply Unit) to trigger it's overcurrent state and trip.
- Measure the voltages of the #PSU's output and ensure it is not more than 5.1V.
- Next, go to the link pasted in the metadata table above and grab the .ino file, launch it in Arduino IDE.
- Ensure your IDE has #ESP8266 boards installed via a url, google for that url, which gives a list of boards like #ESP32 & #ESP8266 .
- Then connect your #NodeMCU AKA #ESP8266  and flash the program into it.
- Connect the #GPIO pins of the #ESP8266  as per the guidelines given in the repo inside the .ino code file, since this code is an inheritance of the original code, that's been modified to display time and date.
- Once connected, configure your WiFi SSID and Password, and flash the program, and remove the USB plug from the board.
- Now power the board directly from the 5V rail of the #PSU you have chosen for powering the #P10 .
- Once it's powered, it shall take a moment to configure the system time and once done, it will display the current time and date as shown in the screenshots below.

# Images

![20250424_134312](https://github.com/user-attachments/assets/2a0667be-9a52-4504-9b9d-7cec14946974)

![PXL_20250424_134402391 PORTRAIT ORIGINAL](https://github.com/user-attachments/assets/a88e2f09-279b-4201-8db5-a79bc7f965ca)

## Pin Connections
![PXL_20250424_145900729 PORTRAIT](https://github.com/user-attachments/assets/33f0696d-c7b6-4284-907b-dd39a2b50f39)

# Credits

Original source code : [busel7 ](https://github.com/busel7/DMDESP/blob/master/examples/TeksDiamdanJalan/TeksDiamdanJalan.ino)
