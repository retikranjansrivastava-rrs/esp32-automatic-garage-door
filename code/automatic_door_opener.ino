 /*
 * Automatic Door Opener using ESP8266 NodeMCU
 * Ultrasonic Sensor + Servo Motor
 *
 * Original reference: newbiely.com
 * Modified and used for academic project purpose
 */

#include <Servo.h>

// Pin definitions
#define TRIG_PIN  D1   // Ultrasonic Sensor TRIG
#define ECHO_PIN  D2   // Ultrasonic Sensor ECHO
#define SERVO_PIN D7   // Servo Motor signal pin

#define DISTANCE_THRESHOLD 50  // Distance in centimeters

Servo servo;  // Servo object

float duration_us;
float distance_cm;

void setup() {
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  servo.attach(SERVO_PIN);
  servo.write(0);  // Door initially closed
}

void loop() {
  // Send ultrasonic pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read echo time
  duration_us = pulseIn(ECHO_PIN, HIGH);

  // Calculate distance
  distance_cm = 0.017 * duration_us;

  // Door control logic
  if (distance_cm > 0 && distance_cm < DISTANCE_THRESHOLD) {
    servo.write(90);   // Open door
  } else {
    servo.write(0);    // Close door
  }

  // Serial output
  Serial.print("Distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  delay(500);
}
