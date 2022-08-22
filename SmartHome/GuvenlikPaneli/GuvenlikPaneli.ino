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
        Serial.printf("*", inputvalue[0]);
        OLED.setTextXY(4, 0);
        OLED.putString("*         ");
        break;
      case 2:
        Serial.printf("*", inputvalue[1]);
        OLED.setTextXY(4, 1);
        OLED.putString("*        ");
        break;
      case 3:
        Serial.printf("*", inputvalue[2]);
        OLED.setTextXY(4, 2);
        OLED.putString("*        ");
        break;
      case 4:
        Serial.printf("*", inputvalue[3]);
        OLED.setTextXY(4, 3);
        OLED.putString("*        ");
        ArrayIndex = 0;
        Serial.println("tekrar");
        OLED.setTextXY(4, 0);
        OLED.putString("tekrar      ");
        break;
      }
    }
    if (password[0] == inputvalue[0] && password[1] == inputvalue[1] && password[2] == inputvalue[2] && password[3] == inputvalue[3]) { // şifre doğru ise
      Serial.println("şifre doğru");
      OLED.setTextXY(4, 0);
      OLED.putString("sifre dogru");
      delay(500);
      inputvalue[0] = 0;
      inputvalue[1] = 0;
      inputvalue[2] = 0;
      inputvalue[3] = 0;
      noTone(D0, 0);
    } else {
      /*delay(3000); // 3sn  delay(30000); 30sn*/
      RGB5050.setLedColorData(0, 255, 0, 0);
      RGB5050.show();
      tone(D0, 500, 500, 0);
    }
  } else {
    RGB5050.setLedColorData(0, 0, 0, 0);
    RGB5050.show();
    Serial.println("#################");
    OLED.setTextXY(2, 0);
    OLED.putString("                ");
  }
}
