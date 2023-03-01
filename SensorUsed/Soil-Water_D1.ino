/*
  Soil sensor switch module 
*/

const int water_switch = 4;  // Water switch D1 -> GPIO 4
//const int water_switch = 5;  // Water switch D1 -> GPIO 5

const int buzzer = 13;  // Magnet switch D7 -> GPIO 13

int val1 = 0;           // 初始值

void setup() {
  pinMode(buzzer, OUTPUT);  // initialize the LED pin as an output:
  pinMode(water_switch, INPUT_PULLUP);  // initialize the pushbutton pin as an input:

  Serial.begin(9600);
}

void mybuzzer(){
  if (val1 = 1){
      tone(buzzer, 1000); // Send 1KHz sound signal...
      delay(500);        // ...for 1 sec
      noTone(buzzer);     // Stop sound...
      delay(1000);        // ...for 1sec
      Serial.println(" BUZZER ALARM");
  }
}

void loop() {
  if (digitalRead(water_switch) == HIGH) {      
    val1 = 0;     
    Serial.print(val1);    
    Serial.println(" - no Water");    
  }
  else {    
    val1 = 1;         //door open
    mybuzzer();
    Serial.print(val1);    
    Serial.println(" - Water leaking");
  }
} 