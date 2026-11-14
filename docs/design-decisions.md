# Design Decisions

## Arduino Uno

The Uno is used as the main controller because the project needs a small number of digital I/O pins, servo control, pulse timing, and USB serial communication. It is sufficient for the scanning and alert logic.

## HC-SR04 and SG90

The HC-SR04 provides low-cost ultrasonic ranging. Mounting it on an SG90 allows measurements at successive angles, creating a scanning effect. The configured range is 15°–165° to avoid relying on the servo's mechanical end stops.

## Browser dashboard instead of Processing

The display is implemented in a single HTML file using Canvas and JavaScript. This avoids requiring a separate Processing installation and makes the interface easier to customize. Web Serial is used because the project is based on a USB-connected Uno.

## Explicit user port selection

The browser requires a user gesture and permission before opening a serial port. The Connect button is intentional; the page does not attempt to bypass browser security or silently select COM5. The user selects the Arduino in the browser device picker.

## Newline-delimited serial protocol

The `angle,distance\n` format is human-readable, easy to inspect, and straightforward to parse in JavaScript. It also avoids relying on custom binary framing.

## Distance-dependent audible alert

The alert escalates as the measured distance decreases. Beep cadence and tone frequency are varied in software. A passive piezo buzzer is specified because an active buzzer may not reproduce the requested frequency changes.

## Non-blocking buzzer timing

The buzzer pattern uses `millis()` state timing instead of long delays. This avoids freezing serial updates during the warning pattern.

## Servo pause with hysteresis

The servo pauses when distance is below 20 cm and resumes early when distance exceeds 25 cm. Separate entry and release thresholds reduce chatter around a single threshold.

## Servo power

A separate regulated 5 V supply is recommended if the servo causes resets or unstable readings. The external supply and Uno must share ground.

## Known trade-offs

- The servo scan is sequential, not simultaneous.
- A single ultrasonic sensor can miss narrow, angled, soft, or acoustically absorbent objects.
- The display uses a simplified polar mapping and should be treated as an indicative visualization.
- The browser needs a supported browser and an explicit serial permission action.
