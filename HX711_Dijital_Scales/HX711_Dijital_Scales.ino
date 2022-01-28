#include "HX711.h"

HX711 scale(6, 5); //Çıkış Bacağı Ayarlaması

float calibration_factor = 384;//Kalibrasyon Değeri 384
int units;
int ounces;
#define led 8  //Led Bacağı
  
void setup() {
  Serial.begin(9600);
  Serial.println("HX711 calibration sketch");
  Serial.println("Ağırlıktaki Yükleri Kaldırın");
  Serial.println("Okuma Başladıktan sonra ağırlığı Tartıya Koyun");
  Serial.println("Kalibrasyon faktörünü arttırmak için +' veya + ya basın");
  Serial.println("Kalibrasyon faktörünü azaltmak için - veya z'ye basın");
  pinMode(led,OUTPUT);
  scale.set_scale();
  scale.tare();
}
void ledyak(){ 
    if(ounces>0.4){
    digitalWrite(led,HIGH);
  }
  else{
     digitalWrite(led,LOW);
    }}


void loop() {
  
  scale.set_scale(calibration_factor); 

  Serial.print("Reading: ");
  units = scale.get_units(), 10;
  if (units < 0)
  {
    units = 0.00;
  }
  ounces = units * 0.035274;
  Serial.print(units);
  Serial.print(" grams"); 
  Serial.println();
  delay(150);
  if(units==25){
    digitalWrite(led,HIGH);
  }
  if(Serial.available())
  {
    char temp = Serial.read();
    if(temp == '+' || temp == 'a')
      calibration_factor += 1;
    else if(temp == '-' || temp == 'z')
      calibration_factor -= 1;
  }
     ledyak();
}
