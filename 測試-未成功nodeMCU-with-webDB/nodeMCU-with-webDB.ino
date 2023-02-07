/**
   StreamHTTPClient.ino

    Created on: 2023.02.07
  Ness Huang 
  1.已確認-可連接http 取得web資訊
  2.已確認-可以透過目標的php轉寫參數到指定資料庫
  3.待確認-將iot設備根據id寫入指定行 
*/

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

ESP8266WiFiMulti WiFiMulti;

int id = 1;    //iot設備ID
int val = 25;
int val2 = 55;

String sendval, sendval2, postData;

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
}

void loop() {
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {
    
    WiFiClient client;

    HTTPClient http;    // http object of clas HTTPClient

    // Convert integer variables to string
    sendval = String(val);  
    sendval2 = String(val2);    
    postData = "sendval=" + sendval + "&sendval2=" + sendval2;

    http.begin(client, "http://ness-pj001.000webhostapp.com/dbwrite.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");            //Specify content-type header

    int httpCode = http.POST(postData);   // Send POST request to php file and store server response code in variable named httpCode
    Serial.println("Values are, sendval = " + sendval + " and sendval2 = "+sendval2 );


    // if connection eatablished then do this
    if (httpCode == 200) { Serial.println("Values uploaded successfully."); Serial.println(httpCode); 
    String webpage = http.getString();    // Get html webpage output and store it in a string
    Serial.println(webpage + "\n"); 
    }

    // if failed to connect then return and restart

    else { 
      Serial.println(httpCode);       Serial.println("Failed to upload values. \n");       http.end();       return; }


    delay(3000); 
    digitalWrite(LED_BUILTIN, LOW);
    delay(3000);
    digitalWrite(LED_BUILTIN, HIGH);

    //val+=1; val2+=10; // Incrementing value of variables
    }

}
