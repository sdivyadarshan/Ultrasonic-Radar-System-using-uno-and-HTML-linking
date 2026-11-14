# Algorithm and Control Logic

## 1. Scan sequence

1. Initialize serial communication at 9600 baud.
2. Configure HC-SR04 trigger/echo pins, buzzer output, and attach the servo.
3. Move the servo through the configured scan range from 15° to 165°.
4. At each angle, allow a short settling interval, trigger the ultrasonic sensor, measure the echo pulse, and convert pulse duration to centimetres.
5. Transmit the angle and distance as one newline-terminated serial record.
6. Update the buzzer state according to the measured distance.
7. If distance is below 20 cm, hold the servo at that angle and sample repeatedly for up to one second. Resume early if the distance becomes greater than 25 cm.
8. Scan back from 165° to 15° and repeat.

## 2. Distance calculation

The HC-SR04 echo pulse duration represents the round-trip travel time of the sound wave. The sketch uses the approximate speed of sound in air:

`distance_cm = echo_duration_us × 0.0343 / 2`

Division by two accounts for the outward and return paths. If no echo is received before the timeout, the sketch reports 400 cm as an out-of-range sentinel.

## 3. Buzzer state table

| Measured distance | Alert behaviour |
|---|---|
| Greater than 50 cm | Silent |
| 21–50 cm | 900 Hz, short beep followed by a longer pause |
| 11–20 cm | 1400 Hz, faster beep cadence |
| 10 cm or less | Continuous 2000 Hz tone |

A passive piezo buzzer is required to hear the intended pitch variation. The Arduino code updates the beep timing using `millis()` rather than inserting long alert delays, allowing serial readings to continue.

## 4. Servo pause / release logic

- Enter the hold state when a scan reading is below 20 cm.
- Keep the servo at the current angle for up to 1000 ms.
- Take another reading approximately every 60 ms and send it to the dashboard.
- Exit the hold state early when distance exceeds 25 cm.
- The 20 cm entry and 25 cm release thresholds provide hysteresis, reducing rapid state switching near one boundary.

## 5. Web dashboard

1. The user presses Connect Arduino.
2. The browser's Web Serial device picker asks the user to choose an authorized serial device.
3. JavaScript opens the port at 9600 baud.
4. Incoming text is buffered until a newline is received.
5. Each valid `angle,distance` line updates the live readouts, sweep direction, and object marker.
6. HTML5 Canvas draws the radar grid, angular lines, sweep beam, and fading object markers.

## 6. Important interpretation

This is a rotating ultrasonic range scanner with a radar-style screen. It does not transmit or receive radio-frequency radar signals, and it does not establish an object's full shape or exact coordinates.
