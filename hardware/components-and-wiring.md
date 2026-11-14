# Components and Wiring

## Bill of materials

| Component | Qty. | Notes |
|---|---:|---|
| Arduino Uno / compatible | 1 | Main controller |
| HC-SR04 | 1 | Ultrasonic ranging |
| SG90 servo | 1 | Sensor positioning |
| Passive piezo buzzer | 1 | Recommended for variable pitch using `tone()` |
| Breadboard | 1 | Prototyping |
| Male-to-male jumper wires | 1 set | Typical breadboard connections |
| USB cable | 1 | Programming and serial link |
| Regulated 5 V supply | 1 optional/recommended | Servo supply if board 5 V is unstable |

## Pin mapping

| Device | Pin / lead | Arduino Uno |
|---|---|---|
| HC-SR04 | VCC | 5V |
| HC-SR04 | GND | GND |
| HC-SR04 | TRIG | D10 |
| HC-SR04 | ECHO | D11 |
| SG90 | Signal (orange/yellow) | D9 |
| SG90 | VCC (red) | Regulated 5 V |
| SG90 | GND (brown/black) | Common GND |
| Passive buzzer | + | D8 |
| Passive buzzer | - | GND |

## Breadboard and jumper guidance

- Use male-to-male jumpers for Arduino-to-breadboard and module-to-breadboard connections when the modules have pins that fit the breadboard.
- Keep the HC-SR04 VCC and GND connections on the correct rails.
- If a servo connector cannot be inserted reliably into the breadboard, use suitable male-to-female jumpers or a breakout connection rather than forcing it.
- Keep wiring short and secure to reduce intermittent connections.

## Power and safety notes

1. The HC-SR04 can normally be powered from the Uno 5 V rail.
2. A servo may draw current peaks that exceed what is stable from the Uno's USB-powered 5 V rail. If the Uno resets, the servo jitters, or serial communication drops, use a regulated external 5 V supply sized for the servo.
3. When using an external servo supply, connect its GND to Arduino GND. The signal needs a shared reference.
4. Do not connect the external supply's positive terminal to the Uno 5 V rail while USB is connected unless the power path is deliberately designed.
5. Verify polarity before powering the circuit.

## Buzzer type

The sketch varies both beep cadence and tone frequency. A **passive piezo buzzer** is recommended. An active buzzer module often contains its own oscillator and may sound at a nearly fixed pitch even when the Arduino changes the `tone()` frequency. If using an active module, the beep cadence can still vary, but pitch variation may not be audible.

## Approximate signal flow

- Arduino D10 sends the HC-SR04 trigger pulse.
- Arduino D11 reads the echo pulse duration.
- Arduino D9 sends servo position pulses.
- Arduino D8 generates the buzzer tone pattern.
- USB serial sends `angle,distance\n` records to the browser.
