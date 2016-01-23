#include <string.h>
#include <ctype.h>
#include <SoftwareSerial.h>

#define trigPin 4
#define echoPin 5
#define led 7

const uint8_t req[5]  = {0x00, 0x01, 0x00, 0x11, 0x00};
const uint8_t cap[17] = {0x00, 0x0d, 0x00, 0x11, 0x01, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x32};
const uint8_t ping[9] = {0x00, 0x05, 0x07, 0xd1, 0x00, 0xde, 0xad, 0xbe, 0xef};

// the Bluetooth Shield connects to Pin D9 & D10
SoftwareSerial bt(1,0); // RX, TX

int state = 0;
int flag = 0;
void setup() {
  Serial.begin (9600);
  bt.setTimeout(100);
  bt.begin(9600);
  Serial.println("Arduino - Pebble Test");
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  int i = 0;

  bool is_req = false;
  
  // After connected with Arduino, Pebble sends a 5 bytes request asking for "Phone Version"
  // We make a fake answer to Pebble so that Pebble takes our arduino as an "android phone"
  // For details, check https://github.com/Hexxeh/libpebble

  if(bt.available())
  {
    for(i = 0;i < 5; i++)
    { 
      int sig = bt.read();
      Serial.print((char)sig);
      if(req[i] != sig)
      {
        break;
      }
      is_req = true;
    }  

  }
  if(is_req)
  {
    bt.write(cap, 17);
  }
  bt.write(ping, 9);
  delay(5000);
  
//  long duration, distance;
//  digitalWrite(trigPin, LOW);  // Added this line
//  delayMicroseconds(2); // Added this line
//  digitalWrite(trigPin, HIGH);
////  delayMicroseconds(1000); - Removed this line
//  delayMicroseconds(10); // Added this line
//  digitalWrite(trigPin, LOW);
//  duration = pulseIn(echoPin, HIGH);
//  distance = (duration/2) / 29.1;
//  if (distance < 10) {  // This is where the LED On/Off happens
//    digitalWrite(led,HIGH); // When the Red condition is met, the Green LED should turn off
//  }
//  else {
//    digitalWrite(led,LOW);
//  }
//  if (distance >= 200 || distance <= 0){
//    Serial.println("Out of range");
//  }
//  else {
//    Serial.print(distance);
//    Serial.println(" cm");
//  }
//  delay(500);
}
