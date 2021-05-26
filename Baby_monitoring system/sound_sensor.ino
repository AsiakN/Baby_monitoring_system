
int sensorPin = 2; 
int ledPin = 3; 
int buzzerPin = 9; 
int thresholdVal = 550; 
int val = 0;

void setup() {
  pinMode(sensorPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
  // put your setup code here, to run once:

}

void loop() {
  val = analogRead(sensorPin);
  Serial.println(val);
  if (val >= thresholdVal){
     digitalWrite(ledPin, HIGH);
     tone(buzzerPin, 2000);
     delay(1000);
     
    }
  else{
     digitalWrite(ledPin, LOW);
     noTone(buzzerPin);
    }
  // put your main code here, to run repeatedly:

}
