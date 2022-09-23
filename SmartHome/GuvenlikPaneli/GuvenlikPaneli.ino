#include <Deneyap_DokunmatikTusTakimi.h>
#include <Deneyap_SicaklikNemOlcer.h>
#include <Deneyap_HareketAlgilama.h>
#include <Deneyap_OLED.h>
#include "RGB5050.h"
#include "Tone32.h"

OLED OLED;
TempHum TempHum;
Gesture Gesture;
Keypad Keypad;
RGB5050 RGB5050;

void IsPassCorrect();
void resetPass();

int password[] = {0, 3, 0, 3};
int inputvalue[4];
int ArrayIndex = 0;

void setup() {
  Serial.begin(115200);
  RGB5050.begin();
  RGB5050.setBrightness(10);
  TempHum.begin(0x70);
  Gesture.begin(0x32);
  Keypad.begin(0x0E);
  OLED.begin(0x7A);
  OLED.clearDisplay();
  Wire.setClock(50000);
  pinMode(D15,OUTPUT); //hoparlör
}

void loop() {
  float Tempvalue = TempHum.getTempValue();
  Serial.print("Sıcaklık = ");
  Serial.print(Tempvalue);
  OLED.setTextXY(1, 0);
  OLED.putString("Sicaklik: ");
  OLED.setTextXY(1, 10);
  OLED.putFloat(Tempvalue);

  float Humvalue = TempHum.getHumValue();
  Serial.print("°C   Nem = %");
  Serial.println(Humvalue);
  OLED.setTextXY(0, 0);
  OLED.putString("Nem: ");
  OLED.setTextXY(0, 5);
  OLED.putFloat(Humvalue);
  
  bool gestureDurum = Gesture.readGesture();
  
  int keyword = Keypad.KeypadRead();
  
  if (gestureDurum == 1) {
    Serial.println("Hareket ALGILANDI");
    OLED.setTextXY(2, 0);
    OLED.putString("Hareket ALGLANDI");
    OLED.setTextXY(3, 0);
    OLED.putString("sifre giriniz");

    if (keyword != 0xFF) {
      inputvalue[ArrayIndex] = keyword;
      ArrayIndex++;
      switch (ArrayIndex) {
      case 1:
        Serial.print("*");
        OLED.setTextXY(4, 0);
        OLED.putString("*         ");
        break;
      case 2:
        Serial.print("*");
        OLED.setTextXY(4, 1);
        OLED.putString("*        ");
        break;
      case 3:
        Serial.print("*");
        OLED.setTextXY(4, 2);
        OLED.putString("*        ");
        break;
      case 4:
        Serial.print("*");
        OLED.setTextXY(4, 3);
        OLED.putString("*        ");
        IsPassCorrect();
        ArrayIndex = 0;
        resetPass();
        break;
      }
    }
  }  else {
    RGB5050.setLedColorData(0, 0, 0, 0);
    RGB5050.show();
    OLED.setTextXY(2, 0);
    OLED.putString("                ");
  }
}

void IsPassCorrect(){   // Şifre doğru mu ?
  if (password[0] == inputvalue[0] && password[1] == inputvalue[1] && password[2] == inputvalue[2] && password[3] == inputvalue[3]) { // şifre doğru ise
    Serial.println(" şifre doğru");
    OLED.setTextXY(4, 0);
    OLED.putString("sifre dogru");
    delay(1000);
  } else {
    Serial.println(" şifre yanlış");
    RGB5050.setLedColorData(0, 0, 0, 255);
    RGB5050.show();
    OLED.setTextXY(4, 0);
    OLED.putString("sifre yanlis");
    tone(D15,500,500,0);
    delay(500);
    tone(D15,800,500,0);
    delay(500);
    }
}

void resetPass(){   // Girilen şifre dizisinin sıfırlanması
    inputvalue[0] = NULL; 
    inputvalue[1] = NULL;
    inputvalue[2] = NULL;
    inputvalue[3] = NULL;
    Serial.println(" yeniden şifre giriniz "); 
    OLED.setTextXY(4, 0);
    OLED.putString("tekrar      "); 
}
