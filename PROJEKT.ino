#include "DHT.h"
#include <LiquidCrystal.h>

int DHT11_PIN = 13;
int DiodaWoda_PIN = 7;
int PoziomWody_PIN = A2;
int WilGleby_PIN = A1;
int Fotorezystor_PIN= A0;

int RELAY_FAN = 10;
int RELAY_WATER = 8;
int RELAY_BULB = 9;
int RELAY_GRZALKA = 6;

LiquidCrystal lcd(12,11,5,4,3,2);
DHT dht;
 
void setup()
{
  Serial.begin(9600);
  dht.setup(DHT11_PIN);
  pinMode(DiodaWoda_PIN, OUTPUT);
  pinMode(RELAY_FAN, OUTPUT);
  pinMode(RELAY_WATER, OUTPUT);
  pinMode(RELAY_BULB, OUTPUT);
  pinMode(RELAY_GRZALKA, OUTPUT);
}
 
void loop()
{
  int wilgotnosc = dht.getHumidity();
  int wilg;
  if(wilgotnosc>0)
  wilg = wilgotnosc;
  
  int temperatura = dht.getTemperature();
  int temp;
  if(temperatura>0)
  temp=temperatura;
  
  // temperatura i wilgotnosc
  if (dht.getStatusString() == "OK") {
    lcd.begin(16, 2);
    lcd.print("Wilg: ");
    lcd.print(wilgotnosc);
    lcd.print(" %RH");
    lcd.setCursor(0,1);
    lcd.print("Temp: ");
    lcd.print(temperatura);
    lcd.print(" *C");
    if(temp>25)
      digitalWrite(RELAY_FAN, LOW);
    else
      digitalWrite(RELAY_FAN, HIGH); 
   if(temp<20)
      digitalWrite(RELAY_GRZALKA, HIGH);
   else
      digitalWrite(RELAY_GRZALKA, LOW);   
  }

// poziom wody, wilgotnosc i podlewanie gleby 
  int  WilGleby = analogRead(WilGleby_PIN)/10;
  int  PoziomWody = analogRead(PoziomWody_PIN);

  if(PoziomWody<350){
    digitalWrite(DiodaWoda_PIN, HIGH);
    digitalWrite(RELAY_WATER, HIGH);
  }
  else{
    digitalWrite(DiodaWoda_PIN, LOW);
    if(WilGleby<50)
    digitalWrite(RELAY_WATER, LOW);
    else
    digitalWrite(RELAY_WATER, HIGH);
  }

   float swiatlo = analogRead(Fotorezystor_PIN);      //odczytanie wartości z A1
    if(swiatlo<1004)
      digitalWrite(RELAY_BULB, LOW);
    else
      digitalWrite(RELAY_BULB, HIGH);


    Serial.print("Temp: ");
    Serial.print(temp);
    Serial.print(" Wilg: ");
    Serial.print(wilg);
    Serial.print(" Poziom cieczy: ");
    Serial.print(PoziomWody);
    Serial.print(" Wilg gleby: ");
    Serial.print(WilGleby);
    Serial.print(" Swiatlo: ");
    Serial.println(swiatlo);
  delay(1000);
}
