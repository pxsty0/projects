#include <Deneyap_HareketIsikRenkAlgilayiciMesafeOlcer.h>
#include <Deneyap_5x7LedEkran.h>

APDS9960 Hareket;
DotMatrix LEDMatris;
                        
void setup() {
  Serial.begin(115200);
  Hareket.begin(0x39);
  LEDMatris.begin(0x0A);
  Hareket.enableProximity(true);
  Hareket.enableGesture(true);
}

void loop() {    
  uint8_t gesture = Hareket.readGesture();
  if (gesture == APDS9960_DOWN) {
    Serial.println("Asagi");
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
