#include <SPI.h>        //SPI library for communicate with the nRF24L01+
#include <RF24.h>       //The main library of the nRF24L01+
#include <Wire.h>       //For communication
#include <I2Cdev.h>     //For communicate with MPU6050
#include <MPU6050.h>    //The main library of the MPU6050

#include <RF24Network.h>

#define ctsPin A3 // Pin for capactitive touch sensor


MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;

//Define packet for the direction (X axis and Y axis)
int data[2];

//Define object from RF24 library - 7 and 8 are a digital pin numbers to which signals CE and CSN are connected.
RF24 radio(7,8);    
RF24Network network(radio);    //include the radio in the network

//Create a pipe addresses for  communication                                    
const uint64_t base00 = 00;  // Address of this node in octal format
const  uint64_t node01 =01;

int ledPin = 5; // pin for the LED


void setup() {
  Serial.begin(9600);
  Wire.begin();
  Serial.println(mpu.testConnection() ? "Connected" : "Connection failed");
  mpu.initialize();              //Initialize the MPU object
  radio.begin();                 //Start the nRF24 communicate     
  network.begin(90, base00);  //(channel, node address)
  radio.setDataRate(RF24_1MBPS);
  pinMode(ledPin, OUTPUT);  
  pinMode(ctsPin, INPUT);
}
 
void loop() {
  int ctsValue = digitalRead(ctsPin);
  if (ctsValue == HIGH){
    digitalWrite(ledPin, HIGH);
    Serial.println("TOUCHED");
    network.update();
    //With this function, the acceleration and gyro values of the axes are taken. 
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    data[0] = map(ax,-17000 , 17000, -1000, 1000 ); //Send X axis data 
    data[1] = map(ay,-17000 , 17000, -1000, 1000);  //Send Y axis data
    delay(500);
    Serial.print(data[0]); 
    Serial.print("\t");
    Serial.print(data[1]);
    Serial.print("\t");
    Serial.println(); 
    RF24NetworkHeader header(node01);     // (Address where the data is going)
    bool s = network.write(header, &data, sizeof(data));   
  }
  else{
    digitalWrite(ledPin,LOW);
    Serial.println("not touched");
  } 
  delay(100); 
}
