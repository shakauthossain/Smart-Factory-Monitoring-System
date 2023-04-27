#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "********************"
#define BLYNK_DEVICE_NAME "*******************************"
#define BLYNK_AUTH_TOKEN "************************"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <dht.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>

#define dht_apin 14 
#define mq2 36
#define mq135 39

int lpg = 0;
int co2 = 0;
int t,h;

char auth[] = "**********************************";
char ssid[] = "*******************";
char pass[] = "***********************";

dht DHT;

#define OLED_SDA 21
#define OLED_SCL 22
Adafruit_SH1106 display(21, 22);

BlynkTimer timer;

void setup(){
 
  Serial.begin(115200);
  delay(500);
  Blynk.begin(auth, ssid, pass);
  
  pinMode(dht_apin, INPUT);
  pinMode(mq2, INPUT);
  pinMode(mq135, INPUT);

  display.begin(SH1106_SWITCHCAPVCC, 0x3C); 
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(35, 10);
  display.print("Smart");
  display.setCursor(30, 40);
  display.print("Factory");
  display.display();
  delay(2000);
  display.clearDisplay();

}

void sendSensor(){
  DHT.read11(dht_apin);
  h = DHT.humidity;
  t = DHT.temperature;
  Serial.print("Current humidity = ");
  Serial.print(h);
  Serial.print("%  ");
  Serial.print("temperature = ");
  Serial.print(t); 
  Serial.println("C  ");

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.print("Temp:");
  display.println(t);
  display.setCursor(0, 20);
  display.print("Humi:");
  display.println(h);
  display.setCursor(0, 30);
  display.print("LPG:");
  display.println(lpg);
  display.setCursor(0, 40);
  display.print("Alcohol:");
  display.println(co2);
  display.display();

  lpg = analogRead(mq2);
  co2 = analogRead(mq135);
  
  Blynk.virtualWrite(V1, h); 
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V2, lpg);
  Blynk.virtualWrite(V3, co2); 
}

void loop(){
  Blynk.run();
  timer.run();
  sendSensor();
  delay(2000);

}
