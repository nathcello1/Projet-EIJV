#include <ArduinoBLE.h>
#include <math.h>
#include "rgb_lcd.h"
#include <Wire.h>

BLEService environmentalService("180D");
BLECharacteristic BLEcoeur("2A37", BLERead | BLENotify, 1);

BLEService temperatureService("181A");
BLECharacteristic BLEtemperature("2A6E", BLERead | BLENotify, 4);

#define buzzer 2
#define CapteurVibration 1
#define TEMPERATURE A1
#define CapteurBattement A0
#define Button 3

rgb_lcd lcd;

const int colorR = 255;
const int colorG = 0;
const int colorB = 0;

const int B = 4275;
const int R0 = 100000;

int AncienneMesureCoeur = 0;
long DerniereMesureSeconde = 0;
long DerniereMesureSecondeLCD = 0;

int EtatVibration = 0;
int Decompte = 10;

void setup() {
  Serial.begin(9600);

  pinMode(CapteurVibration, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(Button, INPUT);

  lcd.begin(16, 2);
  lcd.setRGB(colorR, colorG, colorB);

  lcd.setCursor(0, 0);
  lcd.print("Bienvenue!");
  lcd.setCursor(0, 1);
  lcd.print("Initialisation...");
  delay(3000);
  lcd.clear();

  if (!BLE.begin()) {
    lcd.setCursor(0, 0);
    lcd.print("Erreur BLE");
    while (1)
      ;
  }

  BLE.setLocalName("BLE Nathcello");

  environmentalService.addCharacteristic(BLEcoeur);
  BLE.addService(environmentalService);

  temperatureService.addCharacteristic(BLEtemperature);
  BLE.addService(temperatureService);

  BLE.advertise();

  lcd.setCursor(0, 0);
  lcd.print("BLE Pret");
  delay(2000);
  lcd.clear();
}

void loop() {
  BLEDevice central = BLE.central();

  lcd.setCursor(0, 0);
  lcd.print("Non connecte");

  if (central) {
    lcd.clear();
    lcd.print("Connecte");

    delay(2000);
    lcd.clear();

    while (central.connected()) {
      long MesureActuelleSeconde = millis();

      if (MesureActuelleSeconde - DerniereMesureSeconde >= 200) {
        DerniereMesureSeconde = MesureActuelleSeconde;
        LectureCoeur();
        LectureVibration();
        LectureTemperature();
      }

      if (MesureActuelleSeconde - DerniereMesureSecondeLCD >= 1000) {
        DerniereMesureSecondeLCD = MesureActuelleSeconde;
        affichageLCD();
      }
    }
    lcd.clear();
    lcd.print("Deconnecte");
    delay(3000);
    lcd.clear();
  }
}

void affichageLCD() {
  int MesureCoeur = analogRead(CapteurBattement);
  int MesureCoeurMap = map(MesureCoeur, 0, 1023, 0, 120);

  int reading = analogRead(TEMPERATURE);
  float voltage = reading * 3.3 / 1024.0;
  float R = 1023.0 / reading - 1.0;
  R = R0 * R;
  float temperature = 1.0 / (log(R / R0) / B + 1 / 298.15) - 273.15;

  lcd.setCursor(0, 0);
  lcd.clear();
  lcd.print("Frequence = ");
  lcd.print(MesureCoeurMap);

  lcd.setCursor(0, 1);
  lcd.print("Temp = ");
  lcd.print(temperature);
  lcd.print("C");
}

void LectureCoeur() {
  int MesureCoeur = analogRead(CapteurBattement);
  int MesureCoeurMap = map(MesureCoeur, 0, 1023, 0, 120);

  if (MesureCoeurMap != AncienneMesureCoeur) {
    uint8_t BLEcoeurArray = { static_cast<uint8_t>(MesureCoeurMap) };

    BLEcoeur.writeValue(BLEcoeurArray);
    AncienneMesureCoeur = MesureCoeurMap;
  }
}

void LectureVibration() {
  EtatVibration = digitalRead(CapteurVibration);
  int etatButton = digitalRead(Button);
  if (EtatVibration == HIGH) {
    digitalWrite(buzzer, LOW);
  } else {
    Decompte = 10;
    while (Decompte >= 0) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Chute detecte :");
      lcd.setCursor(0, 1);
      lcd.print("Alerte dans: ");
      lcd.print(Decompte);

      delay(1000);
      Decompte--;

      etatButton = digitalRead(Button);
      if (etatButton == HIGH) {
        lcd.clear();
        return;
      }
    }

    if (Decompte < 0) {
      while (digitalRead(Button) != HIGH) {
        digitalWrite(buzzer, HIGH);
        delay(100);
        digitalWrite(buzzer, LOW);
        delay(100);
      }
      digitalWrite(buzzer, LOW);
      lcd.clear();
    }
  }
}

void LectureTemperature() {
  int reading = analogRead(TEMPERATURE);
  float voltage = reading * 3.3 / 1024.0;
  float R = 1023.0 / reading - 1.0;
  R = R0 * R;
  float temperature = 1.0 / (log(R / R0) / B + 1 / 298.15) - 273.15;

  union {
    float floatValue;
    uint8_t tempArray[4];
  } tempUnion;

  tempUnion.floatValue = temperature;

  BLEtemperature.writeValue(tempUnion.tempArray, 4);
}
