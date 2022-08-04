#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <TimeLib.h>
#include <WidgetRTC.h>

BlynkTimer timer;
WidgetRTC rtc;
char auth[] = "kZ9PSQhSp84YhZ-t5fPYS0bFE2OL_hs_";
char ssid[] = "Honkai impact";
char pass[] = "29112002";
// BlynkTimer timer;
WidgetLCD lcd(V1);
int IN1 = D2;
int IN2 = D3;
int EN = D5;

void clockDisplay()
{
  String currentTime = String(hour()) + ":" + minute() + ":" + second();
  String currentDate = String(day()) + " " + month() + " " + year();
  Serial.print("Current time: ");
  Serial.print(currentTime);
  Serial.print(" ");
  Serial.print(currentDate);
  Serial.println();

  
  Blynk.virtualWrite(V1, currentTime);
  Blynk.virtualWrite(V2, currentDate);
}

BLYNK_CONNECTED() {
  rtc.begin();
}
void setup() {
  Serial.begin (9600);
  Blynk.begin(auth, ssid, pass);
  setSyncInterval(10 * 60); 
  timer.setInterval(10000L, clockDisplay);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(EN,OUTPUT);
  lcd.clear();
  lcd.print(0,0,"Xin chao");
 
}

void loop() 
{
  Blynk.run();
  timer.run();
}

BLYNK_WRITE(V0)
{
  int value= param.asInt();
  int pot =analogRead(value);
  int tocdo =map(value,0,1023,0,255);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(EN,value);
  
}
/*BLYNK_WRITE(V3)
{
  Serial.print("Got a value: ");
  Serial.println(param.asStr());
}*/
