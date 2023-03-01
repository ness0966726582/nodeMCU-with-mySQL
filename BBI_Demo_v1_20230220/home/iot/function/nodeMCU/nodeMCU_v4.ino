/**
   StreamHTTPClient.ino
    Created on: 2023.03.01
    Ness Huang 
  1.已確認-可連接http 取得web資訊
  2.已確認-DHT11取得數值
  2.已確認-可以透過目標的php轉寫參數到指定資料庫
  3.已確認-將iot設備根據id寫入指定行(透過PHP POST到指定內網DB) 
*/

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

ESP8266WiFiMulti WiFiMulti;

/*buzzer*/
const int buzzer_pin = 13;  // Magnet switch D7 -> GPIO 13

/*dht11*/
#include "DHT.h"
#define DHTPIN 5     // 使用PIN5(nodeMCU D1)
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

/*mc-38*/
const int magnet_switch = 5;  // Magnet switch D1 -> GPIO 5

/*soil*/
const int water_switch = 4;  // Water switch D2 -> GPIO 4

/*裝置設置id與參數預設*/
int value1 	= 1;	//設備	id
int value2 	= 1;	//區域	area_id
int value3 	= 1;	//初始值sensor_id
int value4 	= 0;	//初始值buzzer 
int value5 	= 0;	//初始值sensor1
int value6 	= 0;	//初始值sensor2

String id, area_id, sensor_id, buzzer, sensor1, sensor2, postData;

void setup() {

  Serial.begin(115200); 
  Serial.println("Communication Started \n\n");  
  delay(1000);

  Serial.println();
  Serial.println();
  Serial.println();

  pinMode(LED_BUILTIN, OUTPUT);     // initialize built in led on the board
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("Ness-2.4G", "12345678");
  
  dht.begin();//DHT傳感器啟用
  /*buzzer*/
  pinMode(buzzer_pin, OUTPUT);  // initialize the BUZZER pin as an output:
  /*mc-38*/
   pinMode(magnet_switch, INPUT_PULLUP);  // initialize the pushbutton pin as an input:
  /*soil*/
  pinMode(water_switch, INPUT_PULLUP);  // initialize the pushbutton pin as an input:


}
void mybuzzer(){
  if (value4 = 1){
      tone(buzzer_pin, 1000); // Send 1KHz sound signal...
      delay(500);        // ...for 1 sec
      noTone(buzzer_pin);     // Stop sound...
      delay(1000);        // ...for 1sec
      tone(buzzer_pin, 1000); // Send 1KHz sound signal...
      delay(500);        // ...for 1 sec
      noTone(buzzer_pin);     // Stop sound...
      delay(1000);        // ...for 1sec
      tone(buzzer_pin, 1000); // Send 1KHz sound signal...
      delay(500);        // ...for 1 sec
      noTone(buzzer_pin);     // Stop sound...
      delay(1000);        // ...for 1sec
      Serial.println(" BUZZER ALARM");
  }
}

void dht11_getValue(){
  delay(2000);
  float t = dht.readTemperature();    //取得溫度
  float h = dht.readHumidity();       //取得濕度
  
  if (isnan(h) || isnan(t)) {// 判斷是否皆有數值　若異常直接return
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  value5 = t;
  value6 = h;
  if (value5 > 25){
    value4 = 1;
    mybuzzer();
    Serial.print(value5);    
    Serial.println(" - TEMP >= 25");

  }
  else{
      value4 = 0;
      Serial.print(value5);    
      Serial.println(" - TEMP < 25");
  }

  Serial.print(F("Humidity: "));      Serial.print(h);    Serial.print(F("% "));  
  Serial.print(F("Temperature: "));   Serial.print(t);    Serial.println(F("°C "));
}

void mc38_getValue(){
    
  if (digitalRead(magnet_switch) == LOW) {      
    value4 = 0;  value5 = 0;   //BUZZER-OFF /door close    
    Serial.print(value5);    
    Serial.println(" - Switch Closed");    
  }
  else {    
    value4 = 1;  value5 = 1;   //BUZZER-ON /door open
    mybuzzer();
    Serial.print(value5);    
    Serial.println(" - Switch Open");
  }
}

void soil_getvalue(){
  if (digitalRead(water_switch) == HIGH) {      
      value4 = 0;  value5 = 0;   //BUZZER-OFF / NO　Water 
      Serial.print(value5);    
      Serial.println(" - no Water");    
    }
    else {
      value4 = 1;  value5 = 1;   //BUZZER-ON / Water leaking
      mybuzzer();
      Serial.print(value5);    
      Serial.println(" - Water leaking");
    }
}


void loop() {
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {
    
    WiFiClient client;
    HTTPClient http;    // http object of clas HTTPClient

    //傳感器取值1.DHT11(溫/濕) 2.MC-38(門) 3.Soil(水)
    //dht11_getValue();   //mc38_getvalue();   //soil_getvalue();
    switch (value3){
      case 1:
        dht11_getValue();
        break;
      case 2:
        mc38_getValue();
        break;        
      case 3:
        soil_getvalue();
        break;
    }

    // Convert integer variables to string
    id 		    = String(value1);
    area_id 	= String(value2);
    sensor_id = String(value3);  
    buzzer 		= String(value4);   
    sensor1 	= String(value5);   
    sensor2 	= String(value6);    
    postData = "value1=" + id + "&value2=" + area_id + "&value3=" +sensor_id + "&value4=" + buzzer+ "&value5=" + sensor1 + "&value6=" + sensor2;

    //http.begin(client, "----資料庫主機IP----/home/iot/function/nodeMCU/dbupdate.php");

// 使用內網IP ! 
    http.begin(client, "http://10.231.220.20/home/iot/function/nodeMCU/dbupdate.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");            //Specify content-type header

    int httpCode = http.POST(postData);   // Send POST request to php file and store server response code in variable named httpCode
    Serial.println(postData);


    // if connection eatablished then do this
    if (httpCode == 200) { Serial.println("Values uploaded successfully."); Serial.println(httpCode); 
    String webpage = http.getString();    // Get html webpage output and store it in a string
    Serial.println(webpage + "\n"); 
    }

    // if failed to connect then return and restart
    else { 
      Serial.println(httpCode);       
      Serial.println("Failed to upload values. \n"); 
      delay(60000); //一分鐘丟一筆      
      http.end();       
      return; }

    delay(3000); 
    digitalWrite(LED_BUILTIN, LOW);
    delay(3000);
    digitalWrite(LED_BUILTIN, HIGH);

    }
    //delay(1000); //一分鐘丟一筆
}