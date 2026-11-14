# Testing Checklist and Observations

Record actual outcomes after testing the assembled hardware. Do not mark a test as passed until it has been performed.

## Pre-power checks

- [ ] Confirm HC-SR04 VCC/GND polarity.
- [ ] Confirm TRIG is D10 and ECHO is D11.
- [ ] Confirm servo signal is D9.
- [ ] Confirm buzzer signal is D8.
- [ ] Confirm all grounds are common.
- [ ] If an external servo supply is used, verify voltage, polarity, and common ground.
- [ ] Check that the sensor and servo mount are mechanically secure.

## Arduino checks

- [ ] Select Arduino Uno and the correct COM port in Arduino IDE.
- [ ] Compile and upload `src/ultrasonic_radar.ino`.
- [ ] Verify servo sweep from approximately 15° to 165° and back.
- [ ] Verify that the serial stream uses `angle,distance` lines at 9600 baud.
- [ ] Verify readings at several known distances using a ruler.
- [ ] Verify out-of-range / no-echo handling.
- [ ] Verify the servo pauses when a target is below 20 cm.
- [ ] Verify the servo resumes when the target moves beyond 25 cm or the hold timeout expires.
- [ ] Verify the buzzer is silent above 50 cm.
- [ ] Verify slow beeps from 21–50 cm.
- [ ] Verify faster, higher-pitched beeps from 11–20 cm (passive buzzer).
- [ ] Verify continuous warning at 10 cm or less.

## Browser checks

- [ ] Open `web/index.html` from localhost in Chrome or Edge.
- [ ] Click Connect Arduino and select the correct serial port.
- [ ] Confirm that the browser receives readings.
- [ ] Confirm angle and distance readouts update.
- [ ] Confirm the green sweep follows the reported angle.
- [ ] Confirm close-object markers appear on the radar.
- [ ] Confirm the connection status changes after connect/disconnect.
- [ ] Confirm Arduino Serial Monitor is closed while the browser is connected.

## Test record

| Test date | Browser / OS | Supply arrangement | Test object / distance | Expected result | Actual result |
|---|---|---|---|---|---|
| To be recorded | To be recorded | To be recorded | To be recorded | To be recorded | Pending |

## Issues / observations

Record servo jitter, unstable distance readings, missed reflections, browser errors, or power resets here after testing.

- Observation 1: Pending hardware validation.
- Observation 2: Pending hardware validation.
