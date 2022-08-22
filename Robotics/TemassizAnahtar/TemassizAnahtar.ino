#include <Deneyap_HareketIsikRenkAlgilayiciMesafeOlcer.h>
#include <Deneyap_5x7LedEkran.h>
#include "RGB5050.h"

APDS9960 Hareket;
DotMatrix LEDMatris;
RGB5050 RGB5050;
                        
void setup() {
  Serial.begin(115200);
  Hareket.begin(0x39);
  LEDMatris.begin(0x0A);
  Hareket.enableProximity(true);
  Hareket.enableGesture(true);
  RGB5050.begin();
  RGB5050.setBrightness(10); 
}

void loop() {    
  uint8_t gesture = Hareket.readGesture();
  if (gesture == APDS9960_DOWN) {
    Serial.println("Asagi");
    RGB5050.setLedColorData(0, 255, 0, 0);
    RGB5050.show(); 
    for (int i = 0; i < 250; i++) {
        LEDMatris.dotrow1(0, 0, 1, 0, 0);
        LEDMatris.dotrow2(0, 0, 1, 0, 0);
        LEDMatris.dotrow3(0, 0, 1, 0, 0);
        LEDMatris.dotrow4(0, 0, 1, 0, 0);
        LEDMatris.dotrow5(1, 1, 1, 1, 1);
        LEDMatris.dotrow6(0, 1, 1, 1, 0);
        LEDMatris.dotrow7(0, 0, 1, 0, 0);
    }
  }
  if (gesture == APDS9960_UP) {
    RGB5050.setLedColorData(0, 255, 255, 0);
    RGB5050.show(); 
    Serial.println("Yukari");
    for (int i = 0; i < 250; i++) {
        LEDMatris.dotrow1(0, 0, 1, 0, 0);
        LEDMatris.dotrow2(0, 1, 1, 1, 0);
        LEDMatris.dotrow3(1, 1, 1, 1, 1);
        LEDMatris.dotrow4(0, 0, 1, 0, 0);
        LEDMatris.dotrow5(0, 0, 1, 0, 0);
        LEDMatris.dotrow6(0, 0, 1, 0, 0);
        LEDMatris.dotrow7(0, 0, 1, 0, 0);
    }
  }
  if (gesture == APDS9960_LEFT) {
    RGB5050.setLedColorData(0, 0, 255, 255);
    RGB5050.show(); 
    Serial.println("Sol");
    for (int i = 0; i < 250; i++) {
        LEDMatris.dotrow1(0, 0, 1, 0, 0);
        LEDMatris.dotrow2(0, 1, 1, 0, 0);
        LEDMatris.dotrow3(1, 1, 1, 1, 1);
        LEDMatris.dotrow4(0, 1, 1, 0, 0);
        LEDMatris.dotrow5(0, 0, 1, 0, 0);
        LEDMatris.dotrow6(0, 0, 0, 0, 0);
        LEDMatris.dotrow7(0, 0, 0, 0, 0);
    }
  }
  if (gesture == APDS9960_RIGHT) {
    RGB5050.setLedColorData(0, 255, 0, 255);
    RGB5050.show(); 
    Serial.println("Sag");
    for (int i = 0; i < 250; i++) {
        LEDMatris.dotrow1(0, 0, 1, 0, 0);
        LEDMatris.dotrow2(0, 0, 1, 1, 0);
        LEDMatris.dotrow3(1, 1, 1, 1, 1);
        LEDMatris.dotrow4(0, 0, 1, 1, 0);
        LEDMatris.dotrow5(0, 0, 1, 0, 0);
        LEDMatris.dotrow6(0, 0, 0, 0, 0);
        LEDMatris.dotrow7(0, 0, 0, 0, 0);
    }
  }
}
