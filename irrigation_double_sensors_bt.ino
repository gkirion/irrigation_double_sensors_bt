#include <SoftwareSerial.h> 
SoftwareSerial MyBlue(2, 3); // RX | TX 

#define MAX_INT 1023

void setup() {
  // put your setup code here, to run once:
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  MyBlue.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  delay(10);
  float sensor_1_input = analogRead(A0);
  float sensor_2_input = analogRead(A1);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  MyBlue.print("moisture: ");
  MyBlue.print(MAX_INT - sensor_1_input);
  MyBlue.print(" ");
  MyBlue.println(MAX_INT - sensor_2_input);
  delay(6000);
}
