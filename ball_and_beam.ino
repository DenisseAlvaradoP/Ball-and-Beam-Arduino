
#include <Servo.h>

const int trigPin = 8;
const int echoPin = 7;
const int servoPin = 10;

Servo servo;

long duration;
float distance;
float setpoint = 20.0; // cm
float error, last_error = 0;
float integral = 0, derivative;
float Kp = 10, Ki = 0, Kd = 2.5;
float output;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  servo.attach(servoPin);
  servo.write(90);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  error = setpoint - distance;
  integral += error;
  derivative = error - last_error;

  output = Kp * error + Ki * integral + Kd * derivative;
  output = constrain(output, -30, 30);
  int servoAngle = 90 + output;
  servoAngle = constrain(servoAngle, 0, 180);
  servo.write(servoAngle);

  last_error = error;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm | Angle: ");
  Serial.println(servoAngle);

  delay(50);
}
