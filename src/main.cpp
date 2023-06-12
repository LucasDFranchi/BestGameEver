#include <Arduino.h>
#include <MailSystem.h>

void setup() {
  MailSystem m;
  Serial.begin(9600);
}

void loop() {
  Serial.write("Banana\n");
  delay(1000);
  // put your main code here, to run repeatedly:
}