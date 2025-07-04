#include <Servo.h>

// Pin config
const int gasSensorPin = A0;
const int relayPin = 8;       // Exhaust fan via relay
const int buzzerPin = 9;
const int gasThreshold = 300;

Servo gasRegulatorServo;      // Servo to turn off regulator

void setup() {
  pinMode(gasSensorPin, INPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  gasRegulatorServo.attach(10);     // Connect servo to pin 10
  gasRegulatorServo.write(0);       // Initial position (regulator ON)

  digitalWrite(relayPin, LOW);      // Fan OFF
  digitalWrite(buzzerPin, LOW);     // Buzzer OFF

  Serial.begin(9600);
  Serial.println("Gas Leakage Detector with Servo & Exhaust Fan");
}

void loop() {
  int gasValue = analogRead(gasSensorPin);
  Serial.print("Gas Sensor Value: ");
  Serial.println(gasValue);

  if (gasValue > gasThreshold) {
    Serial.println("⚠️ Gas Detected!");

    digitalWrite(buzzerPin, HIGH);      // Buzzer ON
    digitalWrite(relayPin, HIGH);       // Fan ON

    gasRegulatorServo.write(90);        // Rotate servo to close regulator
    delay(500);                         // Small delay for servo to move
  } else {
    digitalWrite(buzzerPin, LOW);       // Buzzer OFF
    digitalWrite(relayPin, LOW);        // Fan OFF

    gasRegulatorServo.write(0);         // Reset servo position
  }

  delay(500);
}
