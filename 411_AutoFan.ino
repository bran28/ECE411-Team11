#include <Wire.h>
#include "SSD1306.h"
#include "SSD1306Wire.h"
#include <math.h>


SSD1306 display(0x3c, 14, 15); //OLED display setup

const int analogPin = A0; //TMP36 Data Pin
const int Relay = 21; //Relay Pin



 //Temperature Values
int RawValue= 0;
float voltage = 0;
float tempC = 0;
float tempF = 0;


const int buttonPin = A5;  // choose the input pin (for a pushbutton)
int buttonState = 0;     // variable for reading the pin status
boolean lastButton = LOW; //Push button
boolean relayOn = false; // Push button trick


void setup(){

  //OLED Setup
 display.setFont(ArialMT_Plain_24);
 Serial.begin(115200);

  display.init();
  
  
  pinMode (13, OUTPUT); //Yellow LED 
  pinMode (12, OUTPUT); //Green LED 
  pinMode (27, OUTPUT); //Red LED 
  pinMode(Relay, OUTPUT); //Relay 

  
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  
}
 
void loop(){
display.clear(); 
RawValue = analogRead(analogPin);

// converting that reading to voltage, for 3.3v arduino use 3.3
  voltage = RawValue/1024.0;
 

// now print out the temperature
  tempC = (voltage - 0.5)* 100;  //converting from 10 mv per degree wit 500 mV offset
 
 // now convert to Fahrenheit
  tempF = (tempC * 9.0 / 5.0) + 32.0;


Serial.print("Raw Value = " ); // shows pre-scaled value
Serial.print(RawValue);
Serial.print("\t milli volts = "); // shows the voltage measured
Serial.print(voltage,0); // 
//Serial.print("\t Temperature in C = ");
//Serial.print(tempC,1);
Serial.print("\t Temperature in F = ");
Serial.println(tempF,1);



//OLED Message on Screen
  String message = "";
  message += tempF;
  String message1 = message + "°F";
  display.drawString(0, 0, message1);
  display.display();
 delay(1000);

if (tempF < 70) //when temp is below 35 degrees
  {
  digitalWrite(13, LOW); //yellow led is off
  digitalWrite(12, HIGH); //green led is on
  digitalWrite(27, LOW); //red led is off

   digitalWrite(Relay, LOW);
   Serial.print("Low");


   // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  Serial.println(buttonState);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH && lastButton == LOW) {
    // turn relay/fan on:
    relayOn = !relayOn;
    lastButton = HIGH;
    //digitalWrite(Relay, HIGH);
   Serial.print("High");
  } else {
    // turn relay/fan off:
    lastButton = buttonState;
    //if (buttonState == LOW){
    digitalWrite(Relay, relayOn);
   Serial.print("Low");
    }
  
  }
else if (tempF > 75) //when temp is above 40 degrees
{
  digitalWrite(13, LOW); //yellow led is off
  digitalWrite(12, LOW); //green led is on
  digitalWrite(27, HIGH); //red led is off
  
   digitalWrite(Relay, HIGH);
   Serial.print("High");
   
   
}
   else //when between 70-75 degrees
{
  digitalWrite(13, HIGH); //yellow led is on
  digitalWrite(12, LOW); //green led is off
  digitalWrite(27, LOW); //red led is off
     }

     
  

    
    
 
 
}
