// ================================
// Power Factor Correction (Demo Version)
// Full implementation available on request
// ================================

#include <PZEM004Tv30.h>

// PZEM connection (ESP32 UART)
PZEM004Tv30 pzem(Serial2, 16, 17);

// Relay pins
const int relayPins[3] = {25, 26, 27};

// Capacitor values (uF)
const float capValues_uF[3] = {6.0, 10.0, 15.0};

const float frequency = 50.0;
const float pi = 3.14159;

void setup() {
  Serial.begin(115200);

  for (int i = 0; i < 3; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], LOW);
  }

  Serial.println("PFC System Initialized");
}

void loop() {
  float voltage = pzem.voltage();
  float current = pzem.current();
  float power   = pzem.power();
  float pf      = pzem.pf();

  // Basic validation
  if (isnan(voltage) || isnan(current) || isnan(power) || isnan(pf)) {
    Serial.println("Sensor Error");
    return;
  }

  Serial.println("------ Readings ------");
  Serial.print("Voltage: "); Serial.println(voltage);
  Serial.print("Current: "); Serial.println(current);
  Serial.print("Power  : "); Serial.println(power);
  Serial.print("PF     : "); Serial.println(pf);

  // No-load condition
  if (power < 5.0) {
    Serial.println("No Load Detected → PF = 1.00");
    for (int i = 0; i < 3; i++)
      digitalWrite(relayPins[i], LOW);
    delay(2000);
    return;
  }

  // If PF already good
  if (pf >= 0.98) {
    Serial.println("PF OK → No correction needed");
    for (int i = 0; i < 3; i++)
      digitalWrite(relayPins[i], LOW);
    delay(2000);
    return;
  }

  // ============================
  // Core PFC Calculation Logic
  // ============================
  float angle = acos(constrain(pf, 0.05, 1.0));
  float Q = power * tan(angle);

  float C_required = Q / (2 * pi * frequency * voltage * voltage);
  float C_required_uF = C_required * 1e6;

  Serial.print("Required Capacitance: ");
  Serial.print(C_required_uF);
  Serial.println(" uF");

  // ============================
  // Capacitor Selection Logic
  // ============================
  bool capSelected = false;
  float C_added = 0;

  for (int i = 0; i < 3; i++) {
    if (!capSelected && capValues_uF[i] >= C_required_uF) {
      digitalWrite(relayPins[i], HIGH);
      Serial.print("Activated Capacitor: ");
      Serial.print(capValues_uF[i]);
      Serial.println(" uF");

      capSelected = true;
      C_added = capValues_uF[i];
    } else {
      digitalWrite(relayPins[i], LOW);
    }
  }

  // ============================
  // Corrected PF Calculation
  // ============================
  float Q_new = Q - (2 * pi * frequency * voltage * voltage * C_added * 1e-6);
  if (Q_new < 0) Q_new = 0;

  float corrected_pf = cos(atan(Q_new / power));

  Serial.print("Corrected PF: ");
  Serial.println(corrected_pf);

  Serial.println("----------------------");

  delay(4000);
}

/*
====================================================
NOTE:
This is a simplified version of the project.

Removed in public version:
- Blynk IoT integration
- WiFi credentials
- LCD display handling
- Advanced relay optimization logic

For full implementation, feel free to contact.
====================================================
*/
