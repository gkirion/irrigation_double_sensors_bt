#include <SoftwareSerial.h> 
SoftwareSerial MyBlue(2, 3); // RX | TX 

#define POT_WITH_TRAY A0
#define POT_WITHOUT_TRAY A1
#define POT_WITH_TRAY_POWER 6
#define POT_WITHOUT_TRAY_POWER 7
#define IRRIGATION_SIGNAL 8
#define MAX_SENSOR_VALUE 1023

char irrigation_status; // 1 ON | 0 OFF

void setup() {
  // put your setup code here, to run once:
  pinMode(POT_WITH_TRAY_POWER, OUTPUT);
  pinMode(POT_WITHOUT_TRAY_POWER, OUTPUT);
  pinMode(IRRIGATION_SIGNAL, OUTPUT);
  digitalWrite(POT_WITH_TRAY_POWER, LOW);
  digitalWrite(POT_WITHOUT_TRAY_POWER, LOW);
  digitalWrite(IRRIGATION_SIGNAL, LOW);
  irrigation_status = '0';
  MyBlue.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(POT_WITH_TRAY_POWER, HIGH);
  digitalWrite(POT_WITHOUT_TRAY_POWER, HIGH);
  delay(10);
  float pot_with_tray_moisture = analogRead(POT_WITH_TRAY);
  float pot_without_tray_moisture = analogRead(POT_WITHOUT_TRAY);
  digitalWrite(POT_WITH_TRAY_POWER, LOW);
  digitalWrite(POT_WITHOUT_TRAY_POWER, LOW);
  MyBlue.print("pot with tray,");
  MyBlue.print("moisture: ");
  MyBlue.println(MAX_SENSOR_VALUE - pot_with_tray_moisture);
  MyBlue.print("pot without tray,");
  MyBlue.print("moisture: ");
  MyBlue.println(MAX_SENSOR_VALUE - pot_without_tray_moisture);
  if (MyBlue.available() > 0) {
    char command = MyBlue.read();
    switch (command) {
      case 'S':
        MyBlue.print("irrigation: ");
        MyBlue.println(irrigation_status);
        break;
        
       case '1':
        digitalWrite(IRRIGATION_SIGNAL, HIGH);
        irrigation_status = '1';
        break;

      case '0':
        digitalWrite(IRRIGATION_SIGNAL, LOW);
        irrigation_status = '0';
        break; 

      default:
        break;
    }
  }
  delay(6000);
}
