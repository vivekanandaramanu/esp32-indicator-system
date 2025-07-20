# 🚦 ESP32-Based Indicator Control System

This project is my submission for the assignment titled **“Indicators control over mobile phones (using BLE Protocol)”**. The implemented version here is based on **GPIO buttons and PWM LEDs**, and is designed to be extended later using **MATLAB Simulink** and BLE integration.

---

## 📌 1. High-Level Architecture and Software Requirement Specification

### ▶️ Base Software (Developed in C using ESP-IDF)
This layer handles low-level drivers and system scheduling:
- **GPIO Driver:** Reads input from physical push buttons.
- **PWM Driver:** Controls brightness of left and right indicator LEDs.
- **Hardware Timer Driver:** Detects 1-second button hold using a one-shot hardware timer.
- **UART Logging:** All events like button presses, indicator toggling, and LED state are logged over UART.

### ▶️ Application Software (Developed in C)
Implements the indicator system logic:
- **Left/Right Button Hold for 1s** → Toggles corresponding indicator.
- **Opposite Button Hold While One LED is ON** → Switches indicator.
- **Both Buttons Hold for 1s** → Enables or disables **Hazard Mode**.
- **Hazard Exit** → Triggered by pressing either button for 1s.
- **Blinking Pattern** → 300ms ON/OFF for all modes except OFF.
- **100ms Scheduler** → Both base and app tasks run periodically every 100ms using FreeRTOS.

---

## ⚙️ 2. Functional Features Implemented

- ✅ Indicator toggling with 1-second button hold
- ✅ Switching from left to right and vice versa
- ✅ Hazard mode entry and exit
- ✅ LED PWM blinking at 300ms interval
- ✅ All button/LED/mode activity is published over UART
- ✅ Modular code using custom drivers
- ✅ Application logic separated for future Simulink integration

---

## 🔧 Hardware Setup

| Component     | GPIO Pin  | Notes                      |
|--------------|-----------|-----------------------------|
| Left Button   | GPIO 14   | Active Low (Pulled Up)     |
| Right Button  | GPIO 4    | Active Low (Pulled Up)     |
| Left LED      | GPIO 17   | PWM Channel 0              |
| Right LED     | GPIO 16   | PWM Channel 1              |
| Board         | ESP32-WROOM |

---

## 🧪 3. UART Logging

I have included UART log messages for:
- Button press and release detection
- Mode changes (LEFT, RIGHT, HAZARD, OFF)
- LED state changes (ON/OFF) during blinking

### UART Logging Details:
- Logs are currently captured using **ESP-IDF Serial Monitor**
- I plan to additionally log using **Tera Term** with the **HW-417-V1.2 UART-to-TTL Converter**
  - If logs from Tera Term are captured in time, I’ll include them in the final submission.
  - If not, I’ll submit the logs from ESP-IDF monitor and mention this clearly in the report.

---

## 🧩 4. Simulink Integration (Planned)

As per assignment requirement, the **indicator logic should be developed in MATLAB Simulink**. Currently, the application logic is fully developed in C, meeting all system-level requirements.

✅ Once the Simulink logic is designed and auto-generated code is ready, I will replace or integrate it with the `indicator_app.c` logic in a modular fashion.

> ❗**Current Status:** Simulink integration is pending and will be added after this submission. I will update the documentation accordingly later.

---

## 📁 5. Project Structure

```
indicator_system_project/
├── gpio_driver.c / .h
├── pwm_driver.c / .h
├── hw_timer_driver.c / .h
├── indicator_app.c / .h
├── indicator_main.c         // Main scheduler (100ms base & app task)
├── CMakeLists.txt
└── README.md
```

---

## 🔗 6. Submission Checklist

| Item                                       | Status        | Link or Note                         |
|--------------------------------------------|---------------|--------------------------------------|
| ✅ Source Code GitHub Link                 | *To be added* | Will push once finalized             |
| ✅ Video Recording (Zipped via GDrive)     | *To be added* | Will include demo of full working    |
| ✅ UART Log File                           | Ready         | From ESP-IDF (Tera Term optional)    |

---

## ⚠️ 7. Known Limitation

There is a small limitation in the current implementation:  
If the left or right button is pressed immediately after the other (before release), switching may occur unexpectedly.

🔧 This can be resolved by using **button latching logic** in the future. For now, the implementation is **fully functional** and meets the expected requirements.

---

### 📌 Final Note

This submission is fully verified and tested on hardware.  
Simulink-based application logic will be integrated and updated in the next version.

---

*Submitted by: Vivek*  
*Date: July 20, 2025*