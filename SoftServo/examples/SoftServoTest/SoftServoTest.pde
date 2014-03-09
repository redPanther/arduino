#include <SoftServo.h>

SoftServo servo(9,600,2400,800,95);


void setup(void) 
{
  Serial.begin(9600);
  Serial.println("SoftServo test"); Serial.println("");

  servo.write(0);
  delay(1000);
  servo.write(180);
  delay(1000);
  servo.write(90);
  Serial.println("let's go");
  delay(1000);
}

void loop(void) 
{
  servo.write(0);
  delay(1000);
  servo.write(45);
  delay(1000);
  servo.write(90);
  delay(1000);
  servo.write(135);
  delay(1000);
  servo.write(180);
  delay(1000);
  servo.write(135);
  delay(1000);
  servo.write(90);
  delay(1000);
  servo.write(45);
  delay(1000);
 
}