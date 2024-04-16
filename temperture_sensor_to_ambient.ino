//#include <M5Stack.h>
#include <M5StickCPlus.h>
#include <WiFi.h>
#include <Ambient.h>
//#include "Adafruit_Si7021.h"
#include <OneWire.h>//温度表示確認用DS18B20用
#include <DallasTemperature.h>//温度表示確認用DS18B20用
#define SENSER_BIT    9      // 精度の設定bit

  //温度表示確認用DS18B20用(1)
#define ONE_WIRE_BUS 32 // データ(黄)で使用するポート番号

OneWire oneWire(ONE_WIRE_BUS);//DS18B20用
DallasTemperature sensorsds(&oneWire);//温度表示確認用DS18B20用

DeviceAddress temp1 = {0x28,0xF4,0x97,0x96,0xF0,0x1,0x3C,0xEA};//orenge 個々のアドレスチェック要
DeviceAddress temp2 = {0x28,0xB8,0xF5,0x96,0xF0,0x1,0x3C,0x70};//blue 個々のアドレスチェック要
DeviceAddress temp3 = {0x28,0x59,0x73,0x96,0xF0,0x1,0x3C,0x39};//brown


const char* ssid ="tokuitenwifi";
const char* password = "tt2023wfp116";

WiFiClient client;
Ambient ambient;

unsigned int channelId = 45848;
const char* writeKey = "eca583f868caeea9";

//Adafruit_Si7021 sensor = Adafruit_Si7021();

void setup(void){
  M5.begin();
  Serial.begin(9600); //温度表示確認用DS18B20用
  
  sensorsds.setResolution(SENSER_BIT);//温度表示確認用DS18B20用
  pinMode(ONE_WIRE_BUS,INPUT);
 
  WiFi.begin(ssid,password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    M5.Lcd.print("_");
  }
  M5.Lcd.print("\r\nWiFi connected\r\nIP address:");
  M5.Lcd.println(WiFi.localIP());
  ambient.begin(channelId,writeKey,&client);

  //if(!sensor.begin()){
   // M5.Lcd.println("Did not find Si7032 sensor");
   // while(true){
   //   delay(0);
   // }
  //}

 
}

void loop(void){
  //float temp = sensor.readTemperature();
  //float humid = sensor.readHumidity();
  //M5.Lcd.printf("temp:%.2f,humid:%2f\r\n",temp,humid);


  //温度表示確認用DS18B20用(1)
  sensorsds.requestTemperatures();              // 温度取得要求
  M5.Lcd.println(sensorsds.getTempC(temp1));  //温度1の取得&シリアル送信
  M5.Lcd.println(sensorsds.getTempC(temp2));  //温度2の取得&シリアル送信
  M5.Lcd.println(sensorsds.getTempC(temp3));  //温度3の取得&シリアル送信
  
  int t1 = sensorsds.getTempC(temp1);
  int t2 = sensorsds.getTempC(temp2);
  int t3 = sensorsds.getTempC(temp3);

    
 // ambient.set(1,temp);
  ambient.set(1,t1);
  ambient.set(2,t2);
  ambient.set(3,t3);
  ambient.send();
  delay(1000*5);
}