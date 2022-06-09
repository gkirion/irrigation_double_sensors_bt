#include <SoftwareSerial.h> 
SoftwareSerial MyBlue(2, 3); // RX | TX 

#define MAX_SENSOR_VALUE 1023

char irrigation_status; // 1 ON | 0 OFF

void setup() {
  // put your setup code here, to run once:
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  irrigation_status = '0';
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
  MyBlue.print(MAX_SENSOR_VALUE - sensor_1_input);
  MyBlue.print(" ");
  MyBlue.println(MAX_SENSOR_VALUE - sensor_2_input);
  if (MyBlue.available() > 0) {
    char command = MyBlue.read();
    switch (command) {
      case 'S':
        MyBlue.print("irrigation: ");
        MyBlue.println(irrigation_status);
        break;
        
       case '1':
        digitalWrite(8, HIGH);
        irrigation_status = '1';
        break;

      case '0':
        digitalWrite(8, LOW);
        irrigation_status = '0';
        break; 

      default:
        break;
    }
  }
  delay(6000);
}
