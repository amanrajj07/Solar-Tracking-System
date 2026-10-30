# Solar Tracking System (Single Axis)

Arduino Uno based single-axis solar tracker using two LDRs and a servo motor.

## Hardware assumed by this implementation
- Arduino Uno
- 2 LDRs
- 2 x 10 kΩ resistors (one voltage divider per LDR)
- 1 hobby servo motor suitable for the panel's weight
- Breadboard and jumper wires
- External regulated 5 V supply for the servo, sized for the servo's current

**Important:** This implementation assumes two LDRs and the voltage-divider wiring below. If your original prototype used a different arrangement, adjust the pin assignments/wiring before use.

## Wiring

For EACH LDR voltage divider:
- Connect one LDR leg to 5 V.
- Connect the other LDR leg to the analog input (left: A0, right: A1).
- Connect a 10 kΩ resistor from that analog-input junction to GND.

Servo:
- Signal wire -> D9
- Servo V+ -> external regulated 5 V supply
- Servo GND -> external supply GND
- Arduino GND -> external supply GND (common ground)

Do not power a loaded servo from the Uno's 5 V pin. Secure the panel and servo mechanically before testing.

## Upload
1. Open `src/solar_tracker.ino` in Arduino IDE.
2. Select **Arduino Uno** and the correct port.
3. Confirm the wiring matches the diagram above.
4. Upload the sketch.
5. Open Serial Monitor at 9600 baud to view both LDR readings.

## Calibration
- Cover the left LDR and then the right LDR to confirm the readings change as expected.
- With the wiring above, brighter light should normally produce a higher analog reading.
- If the servo moves away from the brighter side, change `SERVO_DIRECTION` from `1` to `-1`.
- If the readings are reversed because your divider is wired differently, change `LIGHT_READING_DIRECTION` from `1` to `-1`.
- Adjust `TRACKING_DEADBAND` to stop small movements caused by noise.
- Adjust `MIN_ANGLE` and `MAX_ANGLE` to suit your mechanical limits.

## What the project demonstrates
- LDR-based light sensing
- Analog input on Arduino Uno
- Servo motor positioning
- Basic single-axis solar tracking

## Repository note
This is a working reference implementation reconstructed from the project details supplied (Arduino Uno, single-axis, LDR, servo). It is not claimed to be the exact original diploma-project source code. Add your own project photographs and update any hardware details to match the prototype you actually built.
