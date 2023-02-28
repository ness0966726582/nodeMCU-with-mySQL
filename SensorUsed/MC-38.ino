/*
  MC-38 Magnetic Sensor Anti-Theft Alarm
  modified on 26 Sep 2020
  by Mohammad Reza Akbari @ Electropeak
  Home
*/


const int magnet_switch = 5;     // Magnet switch D1 -> GPIO 5
const int ledPin =  13;      // LED pin

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(magnet_switch, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  if (digitalRead(magnet_switch) == LOW) {
    Serial.println("Switch Closed");
    digitalWrite(ledPin, HIGH);
    //while (digitalRead(magnet_switch) == LOW) {}
  }
  else {
    digitalWrite(ledPin, LOW);
    Serial.println("Switch Open");
  }
} 
