/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************

  This example shows how to send values to the Blynk App,
  when there is a widget, attached to the Virtual Pin and it
  is set to some frequency

  Project setup in the app:
    Value Display widget attached to V5. Set any reading
    frequency (i.e. 1 second)
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
//#include <TonePlayer.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "uNoSIEP-MbeunaRTsxRBt2EdEBuEIoBV";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "AndroidAP45C3";
char pass[] = "hntk1818";


float sensorData= 0.0; 
//float temperature = 0.0;
int buzzer = 5; 
int ledPin = 4; 
int microphoneSensor = 3; 
int pulseSensor = A0;
//int threshold = 30;
boolean sound; 
int LedVButton = 0; // default = off state for virtual button

// Use Virtual pin 5 for uptime display
#define PIN_UPTIME V5

BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, millis() / 1000);
  //Blynk.virtualWrite(V1, millis()/1000);
}


void setup()
{
  // Debug console
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
  timer.setInterval(1000L, myTimerEvent);
  pinMode(microphoneSensor, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(pulseSensor, INPUT);
}


BLYNK_READ(V5) //Blynk app has something on V5
{
  sensorData = map(analogRead(A0), 0, 1023, 0,350); //reading the sensor on A0
  //temperature = (sensorData*3000*0.1)/ 1023;
  Blynk.virtualWrite(V5, sensorData); //sending to Blynk
  Serial.print(sensorData);
}


void noiseDetection()
{  
  sound = digitalRead(microphoneSensor);
  if (sound == HIGH){
    Blynk.notify("Baby is crying");
    Blynk.email("wisdom.mahami@acity.edu.gh", "Baby Alert", "Baby is crying!");
    Serial.println(sound);
    }
  else{
    Serial.println(sound);
    }
 }

void pulseAlert(){
  if (sensorData > 40){
     buzzerAlert();
    }
  else {
    nobuzzerAlert();
    }
  }

  BLYNK_WRITE(V3)
{
  // Get the state of the VButton
  LedVButton = param.asInt();
  
  // What happens here, is that relayControl routine gets called with the value from the VButton (0 or 1)
  // Also send the type of pressed button, 0 for virtual, 1 for physical
 // LedControl(LedVButton, 0)
}
WidgetLED led1(D4);


void LedControl()
{
     if(LedVButton == 1) // Virtual button set to on
    {
      digitalWrite(ledPin, HIGH);
      //relayState = 1;
    }
    else
    {
      digitalWrite(ledPin, LOW);
      //relayState = 0;
    }
 }



void loop()
 {
  
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}

void buzzerAlert()
 {
   tone(buzzer,5000);
   delay(1000);
 }

void nobuzzerAlert()
 {
    noTone(buzzer);
 }
