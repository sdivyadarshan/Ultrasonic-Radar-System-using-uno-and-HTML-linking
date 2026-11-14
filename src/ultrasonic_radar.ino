/*
  Project: Arduino Uno Ultrasonic Radar System with HTML Dashboard
  Board: Arduino Uno
  Sensor: HC-SR04
  Actuator: SG90 servo
  Alert: Passive piezo buzzer (tone variation supported)

  Pin map:
    HC-SR04 TRIG -> D10
    HC-SR04 ECHO -> D11
    SG90 signal  -> D9
    Buzzer       -> D8
    Common GND   -> GND

  Serial protocol at 9600 baud:
    angle,distance_cm\n

  Behaviour:
    - Sweeps from 15 to 165 degrees and back.
    - Pauses at a direction when an object is closer than 20 cm.
    - During the pause, rechecks for up to 1 second and resumes early
      if the object moves beyond 25 cm.
    - Buzzer pattern changes with distance without long blocking delays.

  Note: Use a suitable regulated 5 V supply for the servo if required.
  Connect external supply GND to Arduino GND.
*/

#include <Servo.h>

Servo radarServo;

const byte TRIG_PIN = 10;
const byte ECHO_PIN = 11;
const byte SERVO_PIN = 9;
const byte BUZZER_PIN = 8;

const int MIN_ANGLE = 15;
const int MAX_ANGLE = 165;
const int CLOSE_HOLD_THRESHOLD_CM = 20;
const int RELEASE_THRESHOLD_CM = 25;
const unsigned long HOLD_TIME_MS = 1000;
const unsigned long HOLD_SAMPLE_INTERVAL_MS = 60;

int getDistanceCm() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  const unsigned long duration = pulseIn(ECHO_PIN, HIGH, 30000UL);

  if (duration == 0) {
    return 400; // No echo / out of range sentinel for the dashboard.
  }

  return (int)(duration * 0.0343f / 2.0f);
}

void sendReading(int angle, int distanceCm) {
  Serial.print(angle);
  Serial.print(',');
  Serial.println(distanceCm);
}

// Non-blocking alert pattern. A passive piezo buzzer is required for
// meaningful pitch variation with tone(). Active buzzer modules may
// sound at a fixed pitch regardless of the tone frequency.
void updateBuzzer(int distanceCm) {
  static unsigned long lastToggleMs = 0;
  static bool buzzerOn = false;
  static int previousBand = -1;

  int band;
  unsigned int frequency;
  unsigned long beepOnMs;
  unsigned long beepOffMs;

  if (distanceCm > 50) {
    band = 0;
    frequency = 0;
    beepOnMs = 0;
    beepOffMs = 0;
  } else if (distanceCm > 20) {
    band = 1;
    frequency = 900;
    beepOnMs = 80;
    beepOffMs = 420;
  } else if (distanceCm > 10) {
    band = 2;
    frequency = 1400;
    beepOnMs = 80;
    beepOffMs = 120;
  } else {
    band = 3;
    frequency = 2000;
    beepOnMs = 1;
    beepOffMs = 0;
  }

  if (band != previousBand) {
    previousBand = band;
    lastToggleMs = millis();
    buzzerOn = false;

    if (band == 0) {
      noTone(BUZZER_PIN);
      return;
    }

    if (band == 3) {
      tone(BUZZER_PIN, frequency);
      buzzerOn = true;
      return;
    }

    tone(BUZZER_PIN, frequency);
    buzzerOn = true;
    return;
  }

  if (band == 0) {
    noTone(BUZZER_PIN);
    return;
  }

  if (band == 3) {
    if (!buzzerOn) {
      tone(BUZZER_PIN, frequency);
      buzzerOn = true;
    }
    return;
  }

  const unsigned long now = millis();
  const unsigned long interval = buzzerOn ? beepOnMs : beepOffMs;

  if (now - lastToggleMs >= interval) {
    lastToggleMs = now;
    buzzerOn = !buzzerOn;

    if (buzzerOn) {
      tone(BUZZER_PIN, frequency);
    } else {
      noTone(BUZZER_PIN);
    }
  }
}

void scanAtAngle(int angle) {
  radarServo.write(angle);
  delay(25); // Allow the servo to move before taking the measurement.

  int distanceCm = getDistanceCm();
  sendReading(angle, distanceCm);
  updateBuzzer(distanceCm);

  if (distanceCm < CLOSE_HOLD_THRESHOLD_CM) {
    const unsigned long holdStart = millis();
    unsigned long lastSample = holdStart;

    while (millis() - holdStart < HOLD_TIME_MS) {
      updateBuzzer(distanceCm);

      if (millis() - lastSample >= HOLD_SAMPLE_INTERVAL_MS) {
        lastSample = millis();
        distanceCm = getDistanceCm();
        sendReading(angle, distanceCm);
        updateBuzzer(distanceCm);

        if (distanceCm > RELEASE_THRESHOLD_CM) {
          break;
        }
      }
    }
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(TRIG_PIN, LOW);
  noTone(BUZZER_PIN);

  radarServo.attach(SERVO_PIN);
  radarServo.write(MIN_ANGLE);
  delay(300);
}

void loop() {
  for (int angle = MIN_ANGLE; angle <= MAX_ANGLE; angle++) {
    scanAtAngle(angle);
  }

  for (int angle = MAX_ANGLE; angle >= MIN_ANGLE; angle--) {
    scanAtAngle(angle);
  }
}
