#include <SoftwareSerial.h> 
SoftwareSerial MyBlue(2, 3); // RX | TX 

#define PLACE_1_NAME "pot with tray"
#define PLACE_2_NAME "pot without tray"

#define PLACE_1_SENSOR_INPUT A0
#define PLACE_2_SENSOR_INPUT A1

#define PLACE_1_SENSOR_POWER 6
#define PLACE_2_SENSOR_POWER 7

#define PLACE_1_IRRIGATION_SIGNAL 8
#define PLACE_2_IRRIGATION_SIGNAL 9

#define MAX_SENSOR_VALUE 1023

char place_1_irrigation_status, place_2_irrigation_status; // 1 ON | 0 OFF

void setup() {
  // put your setup code here, to run once:
  pinMode(PLACE_1_SENSOR_POWER, OUTPUT);
  pinMode(PLACE_2_SENSOR_POWER, OUTPUT);
  pinMode(PLACE_1_IRRIGATION_SIGNAL, OUTPUT);
  pinMode(PLACE_2_IRRIGATION_SIGNAL, OUTPUT);
  
  digitalWrite(PLACE_1_SENSOR_POWER, LOW);
  digitalWrite(PLACE_2_SENSOR_POWER, LOW);
  digitalWrite(PLACE_1_IRRIGATION_SIGNAL, LOW);
  digitalWrite(PLACE_2_IRRIGATION_SIGNAL, LOW);
  
  place_1_irrigation_status = '0';
  place_2_irrigation_status = '0';
  MyBlue.begin(9600);
}

void loop() {

  // receive commands
  if (MyBlue.available() > 0) {
    String input = MyBlue.readStringUntil('\n');
    input = input.substring(0, input.length() - 1); // strip carriage return
    int split_index = input.indexOf(',');
    String place = input.substring(0, split_index);
    char command = input.charAt(split_index + 1);
    
    if (place.equals(PLACE_1_NAME)) {
       
       switch (command) {
      
         case '1':
          digitalWrite(PLACE_1_IRRIGATION_SIGNAL, HIGH);
          place_1_irrigation_status = '1';
          break;
  
        case '0':
          digitalWrite(PLACE_1_IRRIGATION_SIGNAL, LOW);
          place_1_irrigation_status = '0';
          break; 
  
        default:
          break;
      }
      
    } 
    else if (place.equals(PLACE_2_NAME)) {
      
       switch (command) {
      
         case '1':
          digitalWrite(PLACE_2_IRRIGATION_SIGNAL, HIGH);
          place_2_irrigation_status = '1';
          break;
  
        case '0':
          digitalWrite(PLACE_2_IRRIGATION_SIGNAL, LOW);
          place_2_irrigation_status = '0';
          break; 
  
        default:
          break;
      }
      
    }
  }

  // read sensors
  digitalWrite(PLACE_1_SENSOR_POWER, HIGH);
  digitalWrite(PLACE_2_SENSOR_POWER, HIGH);
  delay(10);
  float place_1_moisture = analogRead(PLACE_1_SENSOR_INPUT);
  float place_2_moisture = analogRead(PLACE_2_SENSOR_INPUT);
  digitalWrite(PLACE_1_SENSOR_POWER, LOW);
  digitalWrite(PLACE_2_SENSOR_POWER, LOW);

  // send sensors values and irrigation status
  MyBlue.print(PLACE_1_NAME);
  MyBlue.print(",");
  MyBlue.print(MAX_SENSOR_VALUE - place_1_moisture);
  MyBlue.print(",");
  MyBlue.println(place_1_irrigation_status);
  
  MyBlue.print(PLACE_2_NAME);
  MyBlue.print(",");
  MyBlue.print(MAX_SENSOR_VALUE - place_2_moisture);
  MyBlue.print(",");
  MyBlue.println(place_2_irrigation_status);
  
  delay(6000);
}
