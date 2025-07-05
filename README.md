# _Shift_xd_-is-ThinKing
# ESP32 Luxury Smart Alarm Dashboard

This project is a premium, feature-rich web dashboard for an ESP32-based Smart Alarm system with sleep tracking, mindfulness tools, and fun interactive games.

## 🌟 Features

- ⏰ **Smart Alarm Management**
  - Set and save custom alarm times.
  - Persistent settings stored on the ESP32.

- 🧘 **Mindfulness Mode**
  - Guided breathing exercises using connected lights and buzzer.

- 🎯 **Red Light, Green Light Game**
  - Motion-detection game powered by the PIR sensor.
  - Alerts if user moves during “Red Light”.

- 🛌 **Sleep Tracking**
  - Tracks total sleep duration using PIR motion data.
  - Displays sleep quality analysis on dashboard.

- 🌈 **Luxury UI**
  - Glassmorphism design with gradients and modern fonts.
  - Mobile-responsive layout.

## 📦 Hardware Requirements

| Component          | Pin (ESP32) |
|--------------------|-------------|
| PIR Motion Sensor  | GPIO 13      |
| LDR Sensor         | GPIO 34      |
| Relay (Light)      | GPIO 26      |
| Buzzer             | GPIO 27      |

## 🚀 Setup
1. Flash the ESP32 with the provided firmware.
2. Connect the sensors and actuators according to the pin table.
3. Access the web dashboard from any device on the same network.

## 🌐 Web Dashboard Preview
- Set alarm time and save it.
- Start/stop mindfulness mode.
- Play interactive motion-based games.
- View sleep analytics in real-time.
## Screenshots
![screnshot](https://raw.githubusercontent.com/hardrik1/_Shift_xd_-is-ThinKing/refs/heads/Full-Codes-(-aka-Main)/My%20Imagination.jpg)
## 📜 License
MIT License. Built with ❤️ by _shift_xd_ (Hardrik).

## ⚠️ Notes
- Make sure to configure your WiFi SSID and password in the ESP32 code.
- The `/sleepData` endpoint provides JSON sleep stats.
