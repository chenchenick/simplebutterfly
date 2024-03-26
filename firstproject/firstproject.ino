#include <Servo.h>

#define trigPin 13
#define echoPin 12
#define led 11
#define led2 10
#define motor 9

Servo myservo;
int pos = 0;

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  myservo.attach(motor);
}

void loop() {
  // Call runMotor which now also checks distance and adjusts speed
  runMotor();

  // Short delay before the next cycle
  delay(50);
}

void runMotor() {
  long duration, distance, motordelay;

  for (pos = 0; pos <= 180; pos += 1) {
    // Update the servo position
    myservo.write(pos);
    
    // Measure distance
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration/2) / 29.1;

    // Check distance and adjust LED and motor delay
    if (distance < 20) {
      digitalWrite(led, HIGH);
      digitalWrite(led2, LOW);
      motordelay = 5; // Faster servo speed
    } else {
      digitalWrite(led, LOW);
      digitalWrite(led2, HIGH);
      motordelay = 15; // Slower servo speed
    }

    // Print the distance
    if (distance >= 200 || distance <= 0) {
      Serial.println("Out of range");
    } else {
      Serial.print(distance);
      Serial.println(" cm");
    }
    
    // Delay according to the current distance
    delay(motordelay);
  }

  for (pos = 180; pos >= 0; pos -= 1) {
    myservo.write(pos);

    // The same distance measurement and speed adjustment logic as above
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration/2) / 29.1;

    if (distance < 20) {
      digitalWrite(led, HIGH);
      digitalWrite(led2, LOW);
      motordelay = 5; // Faster
    } else {
      digitalWrite(led, LOW);
      digitalWrite(led2, HIGH);
      motordelay = 15; // Slower
    }

    if (distance >= 200 || distance <= 0) {
      Serial.println("Out of range");
    } else {
      Serial.print(distance);
      Serial.println(" cm");
    }
    
    delay(motordelay);
  }
}
