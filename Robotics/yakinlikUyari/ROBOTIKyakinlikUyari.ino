#include <Deneyap_MesafeOlcerIsikAlgilayici.h>
#include "RGB5050.h"
#include "Tone32.h"

ProximityAL Yakinlik;
RGB5050 RGB5050;

uint16_t yakinlikDegeri;

void setup() {
  Serial.begin(115200);
  Yakinlik.begin(0x23);
  RGB5050.begin();
  RGB5050.setBrightness(10);
  pinMode(D0,OUTPUT); 
}

void loop() {
  yakinlikDegeri = Yakinlik.getPSvalue();
  Serial.print("Yakınlık Değeri = ");
  Serial.println(yakinlikDegeri);
  if (yakinlikDegeri > 1000) {
    Serial.println("ÇOK YAKIN");
    RGB5050.setLedColorData(0, 255, 0, 0);
    RGB5050.show();
    tone(D0,500,500,0);
    delay(500);
    tone(D0,800,500,0);
    delay(500);
  }
  else if (yakinlikDegeri < 1000 && yakinlikDegeri > 50) {
    Serial.println("DİKKATT");
    RGB5050.setLedColorData(0, 255, 255, 0);
    RGB5050.show(); 
  }
  else if (yakinlikDegeri < 50) {
    RGB5050.setLedColorData(0, 0, 0, 0);
    RGB5050.show();
    }
  delay(50);
}
