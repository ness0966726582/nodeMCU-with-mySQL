/**
   StreamHTTPClient.ino
    Created on: 2023.02.13
    Ness Huang 
  1.已確認-可連接http 取得web資訊
  2.已確認-DHT11取得數值
  2.已確認-可以透過目標的php轉寫參數到指定資料庫
  3.已確認-將iot設備根據id寫入指定行(需透過dbwrite-dht11.php POST到指定db) 

	資訊包含: id,area_id,val1,val2
*/

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

ESP8266WiFiMulti WiFiMulti;

/*dht11_v1
1.取得傳感器數值 - OK
2.更新資料庫指定欄位資訊(updat) - 尚未完成
*/
#include "DHT.h"
#define DHTPIN 5     // 使用PIN5(nodeMCU D1)
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

/*裝置設置id與參數預設*/
int id = 1;     //iot設備ID
int area = 1;   //區域唯一編號
int val1 = 0;    //初始值
int val2 = 0;   //初始值

String nodeMCU_id, area_id, sendval1, sendval2, postData;

void setup() {

  //
  Serial.begin(115200); 
  Serial.println("Communication Started \n\n");  
  delay(1000);

  Serial.println();
  Serial.println();
  Serial.println();
  
  pinMode(LED_BUILTIN, OUTPUT);     // initialize built in led on the board

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("Ness-2.4G", "12345678");

  //DHT傳感器啟用
  dht.begin();
}

void dht11_getValue(){
  delay(2000);
  float t = dht.readTemperature();    //取得溫度
  float h = dht.readHumidity();       //取得濕度
  
  // Check DHT11是否異常:必須皆有數值
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    
    return;
  }

  val1 = t;
  val2 = h;
  Serial.print(F("Humidity: "));      Serial.print(h);    Serial.print(F("% "));  
  Serial.print(F("Temperature: "));   Serial.print(t);    Serial.println(F("°C "));
}

void loop() {
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {
    
    WiFiClient client;
    HTTPClient http;    // http object of clas HTTPClient

    //DHT傳感器程式碼
    dht11_getValue();    

    // Convert integer variables to string
    nodeMCU_id = String(id);
    area_id = String(area);
    sendval1  = String(val1);  
    sendval2 = String(val2);    
    postData = "nodeMCU_id=" + nodeMCU_id + "&area_id=" + area_id + "&sendval1=" + sendval1 + "&sendval2=" + sendval2;

    http.begin(client, "http://ness-pj001.000webhostapp.com/dbwrite-dht11.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");            //Specify content-type header

    int httpCode = http.POST(postData);   // Send POST request to php file and store server response code in variable named httpCode
    Serial.println("nodeMCU_id = " + nodeMCU_id + "&area_id=" + area_id + "sendval1 = " + sendval1 + " and sendval2 = "+sendval2 );


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

    }

}
