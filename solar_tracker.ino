/*
  SINGLE-AXIS SOLAR TRACKING SYSTEM
  Board: Arduino Uno
  Sensors: Two LDRs with 10 kOhm voltage-divider resistors
  Actuator: Servo motor

  Example wiring:
    Left LDR divider junction  -> A0
    Right LDR divider junction -> A1
    Servo signal               -> D9

  LDR divider used here:
    5V ---- LDR ----+---- analog input
                    |
                  10k ohm
                    |
                   GND

  Power the servo from a suitable external regulated supply.
  Connect external supply GND to Arduino GND.
*/

#include <Servo.h>

const byte LEFT_LDR_PIN  = A0;
const byte RIGHT_LDR_PIN = A1;
const byte SERVO_PIN     = 9;

const int MIN_ANGLE = 10;
const int MAX_ANGLE = 170;
const int START_ANGLE = 90;

// With the divider shown above, brighter light normally gives a higher reading.
// Set to -1 if your divider produces lower readings in brighter light.
const int LIGHT_READING_DIRECTION = 1;

// Set to -1 if the servo rotates away from the brighter LDR.
const int SERVO_DIRECTION = 1;

const int TRACKING_DEADBAND = 35;
const unsigned long UPDATE_INTERVAL_MS = 100;

Servo tracker;
int currentAngle = START_ANGLE;
unsigned long lastUpdate = 0;

void setup() {
  Serial.begin(9600);
  tracker.attach(SERVO_PIN);
  tracker.write(currentAngle);
  delay(500);
}

void loop() {
  if (millis() - lastUpdate < UPDATE_INTERVAL_MS) {
    return;
  }
  lastUpdate = millis();

  int leftReading = analogRead(LEFT_LDR_PIN);
  int rightReading = analogRead(RIGHT_LDR_PIN);

  int difference = (leftReading - rightReading) * LIGHT_READING_DIRECTION;

  Serial.print("Left LDR: ");
  Serial.print(leftReading);
  Serial.print(" | Right LDR: ");
  Serial.print(rightReading);
  Serial.print(" | Difference: ");
  Serial.print(difference);
  Serial.print(" | Servo angle: ");
  Serial.println(currentAngle);

  if (difference > TRACKING_DEADBAND) {
    currentAngle += SERVO_DIRECTION;
  } else if (difference < -TRACKING_DEADBAND) {
    currentAngle -= SERVO_DIRECTION;
  }

  currentAngle = constrain(currentAngle, MIN_ANGLE, MAX_ANGLE);
  tracker.write(currentAngle);
}
