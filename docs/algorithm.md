# Control Algorithm

1. Initialize ESP32, sensors, LCD, and Wi-Fi
2. Read voltage, current, and power factor from PZEM004T
3. Check load condition:

   * If no load → set PF = 1.00, no correction
4. If PF < threshold:

   * Calculate required compensation
   * Activate corresponding capacitor via relay
5. Wait for stabilization time
6. Recalculate PF
7. Adjust capacitor combination if needed
8. Display data on LCD
9. Send data to Blynk cloud
10. Repeat continuously
