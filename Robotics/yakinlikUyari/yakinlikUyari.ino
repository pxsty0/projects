/*  yakinlikUyari
 *  Bu uygulamada Deneyap Mesafe Ölçer&Işık Algılayıcı ve Deneyap Hoparlör kullanılmıştır.
 *  
 *  Yakınlık mesafesi okunup seri port ekranına yazdırmaktadır. Yakınlık mesafesi çok yakın ise uyarı sesi çalmaktadır ve Deneyap Geliştirme Kartlarındaki dahili adreslenebilir RGBLED kırmızı yanmaktadır. 
 *  Yakınlık mesafesi yakın ise RGBLED sarı yanmaktadır. 
*/
#include <Deneyap_MesafeOlcerIsikAlgilayici.h>  // Deneyap Mesafe Ölçer&Işık Algılayıcı kütüphanesi eklenmesi

ProximityAL ProximityAL;  // ProximityAL için class tanımlanması

void setup() {
  Serial.begin(115200);     // Seri haberleşme başlatılması
  ProximityAL.begin(0x23);  // begin(slaveAdress) fonksiyonu ile cihazların haberleşmesi başlatılması
  pinMode(DAC1, OUTPUT);    // hoparlör için çıkış pini ayarlanması
}

void loop() {
  uint16_t ProximityState = ProximityAL.getPSvalue();  // Yakınlık mesafenin okunması
  Serial.print("Yakınlık Değeri = ");
  Serial.println(ProximityState);  // Yakınlık mesafenin seri port ekranına yazdırılması
  if (ProximityState > 1000) {     // Yakınlık mesafesi çok yakın ise
    Serial.println("ÇOK YAKIN");
    tone(DAC1, 500, 500);  // uyarı sesi çalması
    delay(500);
    tone(DAC1, 800, 500);
    delay(500);
    neopixelWrite(RGBLED, 255, 0, 0);  // RGBLED'in kırmızı yanması
    tone(DAC1, 500, 500);
    delay(500);
    tone(DAC1, 800, 500);
    delay(500);
  } else if (ProximityState < 1000 && ProximityState > 50) {  // Yakınlık mesafesi yakın ise
    Serial.println("DİKKAT");
    neopixelWrite(RGBLED, 255, 255, 0);  // RGBLED'in sarı yanması
  } else if (ProximityState < 50) {      // Yakınlık mesafesi uzak ise
    neopixelWrite(RGBLED, 0, 0, 0);      // RGBLED'in yanmaması
  }
  delay(50);
}
