const int stepPin = 9;
const int dirPin = 8;
const int enPin = 13;
void setup() {
  pinMode(stepPin,OUTPUT);
  pinMode(dirPin,OUTPUT);
  pinMode(enPin,OUTPUT);
  digitalWrite(enPin,LOW);
 
}
void loop() {
 
  digitalWrite(dirPin,HIGH);     //  anticlockwise direction
  for(int x = 0; x < 800; x++) {
    digitalWrite(stepPin,HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin,LOW);
    delayMicroseconds(500);
  }
 delay(1000); // One second delay

  digitalWrite(dirPin,LOW);    // clockwise driection
  for(int x = 0; x < 800; x++) {
    digitalWrite(stepPin,HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin,LOW);
    delayMicroseconds(500);
  }
  delay(1000);
 
}
