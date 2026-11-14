# System Architecture

## Hardware layer

- **HC-SR04:** produces an ultrasonic burst and returns an echo pulse.
- **SG90 servo:** changes the sensor's pointing direction.
- **Arduino Uno:** schedules the scan, measures echo duration, controls the servo and buzzer, and formats serial readings.
- **Buzzer:** provides local audible proximity feedback.

## Communication layer

The Uno communicates with the computer over its USB serial interface at 9600 baud. The protocol is intentionally simple and line-oriented:

`<angle_degrees>,<distance_centimetres>\n`

Example:

```text
45,83
46,81
47,79
```

A distance value of 400 indicates that the echo timed out or was outside the configured measurement window.

## Browser layer

- **HTML:** page structure and metric panels.
- **CSS:** dark radar-themed presentation and responsive layout.
- **Web Serial API:** user-authorized USB serial access from Chromium-based browsers.
- **JavaScript:** stream buffering, parsing, status updates, and drawing loop.
- **HTML5 Canvas:** radar rings, angular guides, sweep beam, and target history.

## End-to-end data flow

```text
HC-SR04 -> Arduino Uno -> USB Serial -> Web Serial API -> JavaScript parser
SG90    <- Arduino Uno                                      |
Buzzer  <- Arduino Uno                                      v
                                                   HTML5 Canvas + Readouts
```

## Operating requirements

- A desktop version of Chrome or Edge with Web Serial support.
- User permission to select the serial port. A webpage cannot silently enumerate and open arbitrary COM ports.
- The Arduino Serial Monitor must be closed while the browser owns the serial port.
- Serve the page from localhost or HTTPS for a secure browser context.
