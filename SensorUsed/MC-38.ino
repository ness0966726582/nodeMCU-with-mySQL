/*
  MC-38 Magnetic Sensor Anti-Theft Alarm
  modified on 26 Sep 2020
  by Mohammad Reza Akbari @ Electropeak
  Home
*/

const int magnet_switch = 5;  // Magnet switch D1 -> GPIO 5
int val1 = 0;           // 初始值

void setup() {
  pinMode(ledPin, OUTPUT);  // initialize the LED pin as an output:
  pinMode(magnet_switch, INPUT_PULLUP);  // initialize the pushbutton pin as an input:

  Serial.begin(9600);
}

void loop() {
  if (digitalRead(magnet_switch) == LOW) {      
    val1 = 0;
    Serial.print(val1);    Serial.println("Switch Closed");    
  }
  else {    
    val1 = 1;
    Serial.print(val1);    Serial.println("Switch Open");
  }
} 
