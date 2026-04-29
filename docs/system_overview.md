# System Overview

This project presents an IoT-based Power Factor Correction (PFC) system using an ESP32 microcontroller and PZEM004T energy monitoring module. The system continuously measures electrical parameters such as voltage, current, power, and power factor in real time.

When the power factor drops below a predefined threshold, the system automatically calculates the required reactive power compensation and activates appropriate capacitor banks (6µF, 10µF, 15µF) using relay control.

A 16x2 LCD provides local real-time display, while integration with the Blynk IoT platform enables remote monitoring of system parameters. The system also includes intelligent features such as no-load detection to avoid unnecessary capacitor switching.

The overall solution improves energy efficiency, reduces power losses, and helps in minimizing electricity bills by maintaining power factor close to unity.
