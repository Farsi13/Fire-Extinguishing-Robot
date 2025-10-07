#include <Servo.h>

Servo myservo;
int pos = 0;

int motorR1 = 3;
int motorR2 = 5;
int motorL1 = 6;
int motorL2 = 11;

int f_left = A2;
int f_left_data;
int f_front = A1;
int f_front_data;
int f_right = A0;
int f_right_data;

int pump = 2;

void setup() {
  Serial.begin(9600);
  pinMode(f_left, INPUT);
  pinMode(f_front, INPUT);
  pinMode(f_right, INPUT);
  pinMode(pump, OUTPUT);
  digitalWrite(pump, HIGH);

  pinMode(motorR1, OUTPUT);
  pinMode(motorR2, OUTPUT);
  pinMode(motorL1, OUTPUT);
  pinMode(motorL2, OUTPUT);

  myservo.attach(10);
  myservo.write(90);
}

void loop() {
  f_front_data = analogRead(f_front);
  f_left_data = analogRead(f_left);
  f_right_data = analogRead(f_right);

  Serial.println(f_front_data);
  Serial.println(f_left_data);
  Serial.println(f_right_data);
  Serial.println("-----------------------------------");

  if (f_front_data < 600) {
    frowerd();
    delay(300);
    digitalWrite(pump, HIGH);
  }

  if (f_front_data < 100) {
    digitalWrite(pump, LOW);
    stop();
    delay(2000);

    for (pos = 65; pos <= 135; pos += 1) {
      myservo.write(pos);
      delay(15);
    }
    for (pos = 135; pos >= 65; pos -= 1) {
      myservo.write(pos);
      delay(15);
    }
    for (pos = 65; pos <= 135; pos += 1) {
      myservo.write(pos);
      delay(15);
    }
    for (pos = 135; pos >= 65; pos -= 1) {
      myservo.write(pos);
      delay(15);
    }
    myservo.write(90);
  }

  if (f_left_data < 600) {
    digitalWrite(pump, HIGH);
    left();
  }

  if (f_right_data < 600) {
    digitalWrite(pump, HIGH);
    right();
  }

  if (f_front_data > 600 && f_right_data > 600 && f_left_data > 600) {
    digitalWrite(pump, HIGH);
    stop();
  }
  delay(100);
}

void frowerd() {
  analogWrite(motorR1, 100);
  analogWrite(motorR2, 0);
  analogWrite(motorL1, 100);
  analogWrite(motorL2, 0);
}

void left() {
  analogWrite(motorR1, 0);
  analogWrite(motorR2, 150);
  analogWrite(motorL1, 150);
  analogWrite(motorL2, 0);
}

void right() {
  analogWrite(motorR1, 150);
  analogWrite(motorR2, 0);
  analogWrite(motorL1, 0);
  analogWrite(motorL2, 150);
}

void stop() {
  analogWrite(motorR1, 0);
  analogWrite(motorR2, 0);
  analogWrite(motorL1, 0);
  analogWrite(motorL2, 0);
}
