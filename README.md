# ESP32 Indicator System

## 📌 Project Title
**Indicators Control Over Mobile Phones (using BLE Protocol)**

## 👤 Author Information
- **Name:** Uppula Vivekananda Raman  
- **Institute:** Sreenidhi Institute of Science and Technology, Hyderabad.  
- **Submission Date:** 21-07-2025  

## 📁 Repository
- **GitHub Link:** [ESP32 Indicator System](https://github.com/vivekanandaramanu/esp32-indicator-system)

## 🎥 Demonstration Video
- **Google Drive Link:** [Working Demo Video (Zipped)](https://drive.google.com/file/d/1q4hKbzImOk4m6uuVi8Ycv6JALjvGyG4a/view?usp=sharing)

## 📝 UART Log File (via TTL Logger)
- **UART Log File:** [`indicator_log.txt`](indicator_log.txt)
- **Logger Used:** HW-417-V1.2 USB-to-TTL module  
- **Tool Used:** Tera Term for real-time monitoring and log export

---

## 🛠️ Project Overview

The ESP32-based Indicator System simulates vehicle turn and hazard indicators with button inputs and LED outputs. It includes logic for left/right toggle, hazard mode activation/deactivation, and logs all events via UART.

### ✅ Functional Requirements Implemented

- Left / Right LED toggle on 1-second button press
- Hazard mode activation with simultaneous 1-second press of both buttons
- Hazard mode exit by holding either button again for 1 second
- 300ms ON/OFF LED blinking for active indicators
- 100ms scheduler for task execution
- UART logs for:
  - Button presses
  - LED status
  - Indicator mode transitions

### 🔧 Hardware Used

- ESP32-WROOM board
- 2 push buttons (GPIO 14 and 4)
- 2 LEDs (GPIO 17 and 16)
- HW-417-V1.2 USB-to-TTL module for UART logging

### 🧱 Software Architecture

- Modular C drivers for GPIO, PWM, Hardware Timer
- Application logic isolated in `indicator_app.c`
- Simulink-based logic integration (planned for future)
- Scheduler using FreeRTOS tasks (100ms)

### 📌 Note on Simulink
The MATLAB Simulink integration is pending and will be added later. Current version uses C logic directly.

---

## 📂 Folder Structure

```
esp32-indicator-system/
├── gpio_driver.c/h
├── pwm_driver.c/h
├── hw_timer_driver.c/h
├── indicator_app.c/h
├── indicator_main.c
├── indicator_log.txt
└── README.md
```

---

## 📦 Future Enhancements

- MATLAB Simulink integration for application logic
- BLE communication for remote indicator control (per assignment scope)
- Button latching mechanism to improve edge detection robustness

---

## 📣 Acknowledgements

All testing was done manually and logs were saved via TTL module using Tera Term. The system behaves as expected with minor edge-case limitations noted in the documentation.
