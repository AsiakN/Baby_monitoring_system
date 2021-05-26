//#include <SoftwareSerial.h>

//SoftwareSerial mySerial(2,3);

int tempSensor = A0; 
void setup() {
  // put your setup code here, to run once:
  pinMode(tempSensor, INPUT);
  Serial.begin(9600);
  delay(2000);
  /*
  Serial.begin(115200);
  
  while(!Serial){
    ;
    }

  Serial.println("Goodnight moon!");
  mySerial.begin(384000);
  mySerial.println("Hello world?");
  */
}
float tempValue;
void loop() {
  // put your main code here, to run repeatedly:
 tempValue = analogRead(tempSensor);
 Serial.println(tempValue);
// tempValue = (tempValue*3000)/ 1023;
// float temperature = tempValue * 0.1; 
// Serial.print("T: ");
// //Serial.println(tempValue);
// Serial.println(temperature); 
// delay(2000);
}
