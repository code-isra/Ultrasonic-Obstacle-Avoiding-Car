/*
  Obstacle Avoidance Robot
  ------------------------
  Uses an ultrasonic sensor (HC-SR04) to detect obstacles
  and controls two DC motors via L298 motor driver.

  Author: Isra
  Date: 21 Jan, 2026
*/

#define ENA 10      // Motor A speed control
#define IN1 9       // Motor A direction
#define IN2 8
#define IN3 7       // Motor B direction
#define IN4 6
#define ENB 5       // Motor B speed control

#define TRIG_PIN A14
#define ECHO_PIN A15

int duration;
int distance;
const int SAFE_DISTANCE = 30; // cm

void setup() {
  Serial.begin(9600);

  // Motor pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Ultrasonic sensor pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  distance = measureDistance();
  Serial.println(distance);

  if (distance < SAFE_DISTANCE) {
    avoidObstacle();
  } else {
    moveForward();
  }
}

// ---------------- FUNCTIONS ---------------- //

int measureDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  return duration / 58.2; // Convert to cm
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 80);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 80);
}

void avoidObstacle() {
  // Move backward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 80);
  analogWrite(ENB, 80);
  delay(1000);

  // Stop
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  delay(500);

  // Turn right
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 180);
  analogWrite(ENB, 180);
  delay(800);
}