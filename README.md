# 🚦 ESP32 Indicator Control System

This project is my assignment submission titled **“Indicators Control Over Mobile Phones (using BLE Protocol)”**.  
Although BLE and Simulink integration are planned as per the assignment scope, the current working version is entirely implemented in **C using GPIO inputs, PWM outputs, and UART logs**. The logic is tested on real hardware and behaves as expected.

---

## 👤 Submitted By

- **Name:** Uppula Vivekananda Raman  
- **Institute:** Sreenidhi Institute of Science and Technology  
- **Submission Date:** 21-07-2025

---

## 📁 Repository & Resources

- 🔗 **GitHub Repo:** [esp32-indicator-system](https://github.com/vivekanandaramanu/esp32-indicator-system)
- 📹 **Demo Video (Google Drive):** [Working Demo](https://drive.google.com/file/d/1q4hKbzImOk4m6uuVi8Ycv6JALjvGyG4a/view?usp=sharing)
- 📄 **UART Logs:** [`indicator_log.txt`](indicator_log.txt)  
  (Captured using **Tera Term** and **HW-417-V1.2 UART-to-TTL Converter**)

---

## 🧠 Project Overview

The goal is to build a modular indicator control system similar to a real vehicle, using:

- **2 Buttons**: Left & Right Inputs (GPIO)
- **2 LEDs**: Representing Left & Right Indicators (PWM Controlled)
- **1 ESP32 Board**: Core processing using hardware timers and FreeRTOS
- **UART**: For publishing real-time logs about all button presses, LED states, and mode transitions.

> The project uses edge detection and 1-second hold detection using a **hardware timer** (not software debouncing), making the system more accurate and scalable.

---

## 🔧 Features Implemented

- ✅ 1-second hold toggles LEFT / RIGHT indicators
- ✅ Pressing opposite button switches indicator.
- ✅ Hazard Mode ON: Both buttons held for 1 second
- ✅ Hazard Mode OFF: Press either button again for 1 second
- ✅ LED Blinking Interval: 300ms ON/OFF
- ✅ 100ms scheduler using **FreeRTOS** base and app tasks
- ✅ UART logging of all key events (button press, mode change, LED status)
- ✅ TTL-based UART logging enabled via **HW-417-V1.2** with **Tera Term**

---

## 🧱 Software Layers

### ▶️ Base Layer (in C using ESP-IDF)

- `gpio_driver.c/h` – handles push button input
- `pwm_driver.c/h` – controls LED brightness with PWM (LED on Status)
- `hw_timer_driver.c/h` – sets up hardware timer for 1-second hold detection
- `indicator_main.c` – scheduler with 100ms FreeRTOS tasks
- `CMakeLists.txt` – build file

### ▶️ Application Logic (in C)

- `indicator_app.c/h` contains core logic:
  - Handles mode switching, hazard toggling, and LED blinking
  - Modular enough to integrate with Simulink later

---

## 🔌 Hardware Used

| Component        | GPIO Pin | Description                   |
|------------------|----------|-------------------------------|
| Left Button      | GPIO 14  | Active Low, 1-second hold     |
| Right Button     | GPIO 4   | Active Low, 1-second hold     |
| Left LED         | GPIO 17  | Controlled via PWM (Channel 0)|
| Right LED        | GPIO 16  | Controlled via PWM (Channel 1)|
| UART Logging     | TX/RX    | TTL Logging via HW-417-V1.2   |

---

## 🧪 UART Logging

Logging was captured in two ways:
- ESP-IDF serial monitor (for development/debug)
- Tera Term (final logs, submitted as per assignment)

Logger Used:
- **HW-417-V1.2 UART-to-TTL converter**
- Real-time logs were saved from Tera Term and exported to `indicator_log.txt`

---

## 📌 Simulink Integration (Planned)

As per the requirement, indicator control logic is expected to be developed in **MATLAB Simulink**, auto-code generated, and integrated into base software.

> ✅ I have completed the entire logic in C and structured it in a modular way so that Simulink integration can be done easily later.  
This part is **pending** and **will be added in the next version**.

---

## 📦 Folder Structure
esp32-indicator-system/
├── gpio_driver.c/h
├── pwm_driver.c/h
├── hw_timer_driver.c/h
├── indicator_app.c/h
├── indicator_main.c
├── CMakeLists.txt
├── indicator_log.txt // UART logs from Tera Term
└── README.md


---

## ⚠️ Known Limitation

Currently, if you press one button and immediately press the other before releasing the first, the logic may unintentionally switch indicators.

📌 This can be improved later using a **button latching mechanism**, which is not yet implemented.

---

## ✅ Summary

- The assignment meets all **functional requirements**.
- The code is **tested** and **working** on ESP32 hardware.
- Logs are published via UART and captured cleanly using TTL module.
- BLE and Simulink-based control are **planned for the next version**.

---

*Submitted by: Uppula Vivekananda Raman*  
*Sreenidhi Institute of Science and Technology*  
*Date: 21-07-2025*
