#include <SPI.h>      //SPI library for communication with the nRF24L01+
#include "RF24.h"  //The main library of the nRF24L01+
//#include <Servo.h> // servo library
#include <RF24Network.h>


RF24 radio (7,8); // CE,CSN
RF24Network network(radio);      // Include the radio in the network
const uint16_t node01 = 01;   // Address of our node in Octal format ( 04,031, etc)
const uint16_t base00 = 00;    // Address of the other node in Octal format

//Servo myServoo;
int LED1 = 6;
int LED2 = 5;
int LED3 = 4;
int LED4 = 3;
int LED5 = 2;


//Define packet for the direction (X axis and Y axis)
int data[2];

boolean t1,t2,t3,t4,n= false;
int g1,g2,g3,g4;

void setup()
{
Serial.begin(9600);
SPI.begin();
//myServoo.attach(4);
radio.begin();                    //Start the nRF24 communicate            
network.begin(90,node01);   
radio.setDataRate(RF24_2MBPS);
pinMode(LED1, OUTPUT);
pinMode(LED2, OUTPUT);
pinMode(LED3, OUTPUT);
pinMode(LED4, OUTPUT);
pinMode(LED5, OUTPUT);
}

void loop() {
   network.update();
  //===== Receiving =====//
  while( network.available() )
  {     // Is there any incoming data?
     RF24NetworkHeader header; // Read the incoming data
     network.read(header, &data, sizeof(data)); 
     digitalWrite(LED1, HIGH);
    Serial.print(data[0]); 
    Serial.print("\t");
    Serial.print(data[1]);
    Serial.print("\t");
    Serial.println(); 
  

    
    
    if (data[0]<-90 && data[1]<-200)
      {
       t1=!t1;
       digitalWrite(LED3, LOW);
       digitalWrite(LED4, LOW);
       digitalWrite(LED5, LOW);
      }
    else if(data[0]<-100 && data[1]>700){
        t2=!t2;
        digitalWrite(LED2, LOW);
        digitalWrite(LED4, LOW);
        digitalWrite(LED5, LOW);
      }
   else if(data[0]>0 && data[1]<-800  ){
        t3=!t3;
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);
        digitalWrite(LED5, LOW);
     }
   else if(data[0]>800 && data[1]<0){
        t4=!t4;
       digitalWrite(LED2, LOW);
       digitalWrite(LED3, LOW);
       digitalWrite(LED4, LOW); 
     }
   else{
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, LOW);
      digitalWrite(LED5, LOW);
      delay(0);
    }    



      if(t1==true){
           digitalWrite(LED2, HIGH);
        }     
      else {
           digitalWrite(LED2, LOW);
        }

      
      if(t2==true){
           digitalWrite(LED3, HIGH);
        }     
      else {
           digitalWrite(LED3, LOW);
        }

      if(t3==true){
           digitalWrite(LED4, HIGH);
        }     
      else {
           digitalWrite(LED4, LOW);
        }

      if(t4==true){
           digitalWrite(LED5, HIGH);
        }     
      else {
           digitalWrite(LED5, LOW);
        }  
    


          
}
 

}
