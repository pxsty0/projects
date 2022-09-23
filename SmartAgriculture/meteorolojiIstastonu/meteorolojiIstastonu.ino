#include <Deneyap_SicaklikNemBasincOlcer.h>
#include <Deneyap_BasincOlcer.h>
#include <Deneyap_ToprakNemiOlcer.h>
#include <Deneyap_UltraviyoleIsikAlgilici.h>
#include <Deneyap_YagmurAlgilama.h>
#include <Deneyap_GercekZamanliSaat.h>
#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include "RGB5050.h"
#include "Tone32.h"

SHT4x TempHum;
SoilMoisture SoilMoisture;
AtmosphericPressure AtmosphericPressure;
UVlight UVlight;
Rain Rain;
RTC RTC;
RGB5050 RGB5050;

float sicaklik;
float nem;
float basinc;
float toprakNem;
float UltraviyoleIsikYogunlugu;
float OrtamIsikYogunlugu;
float yagmurDeger;
String dataString = "";

/*Dosya yazma fonksiyonu */
void writeFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Dosya yaziliyor: %s\n", path);

  File file = fs.open(path, FILE_WRITE);
  if(!file){
    Serial.println("Yazma islemi icin dosya acilamadi");
    return;
  }
  if(file.print(message)){
    Serial.println("Dosya yazildi");
  } else {
    Serial.println("Dosya yazma islemi basarisiz");
  }
  file.close();
}

/*Dosyaya ekleme yapma fonksiyonu */
void appendFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Dosyaya eklendi: %s\n", path);

  File file = fs.open(path, FILE_APPEND);
  if(!file){
    Serial.println("Ekleme islemi icin dosya acilamadi");
    return;
  }
  if(file.print(message)){
    Serial.println("Ekleme islemi basarili");
  } else {
    Serial.println("Ekleme islemi basarisiz");
  }
  file.close();
}

void setup() {
  Serial.begin(115200);
  RGB5050.begin();
  RGB5050.setBrightness(10); 
  pinMode(D15,OUTPUT); // Hoparlör 
  SDCard.begin(); 
  TempHum.begin(0X44);
  SoilMoisture.begin(0x0F);
  UVlight.begin(0x53);
  Rain.begin(0x2E);
  AtmosphericPressure.begin(0x76);
  RTC.begin();
  Wire.setClock(50000);
  UVlight.setMode(LTR390_MODE_ALS); // Ortam ışığını okumaya ayarlanması.  LTR390_MODE_UVS: ultraviyole ışık verisi
  RTC.deviceStart();
  RTC.adjust();
  writeFile(SDCard, "/YeniDosya.txt", "   VERİLER   \r\n");
}

void loop() {
  DateTime now = RTC.now();
  Serial.print("\nTarih:");
  Serial.printf("%02d/%02d/%04d", now.day(), now.month(), now.year());
  Serial.print("\tSaat:");
  Serial.printf("%02d:%02d:%02d", now.hour(), now.minute(), now.second());
  delay(10);
  
  TempHum.measure();
  sicaklik = TempHum.TtoDegC();
  Serial.print("\nSıcaklık: ");
  Serial.print(sicaklik);
  Serial.println(" °C");
  delay(10);

  nem = TempHum.RHtoPercent();
  Serial.print("Bağıl nem: "); 
  Serial.print(nem);
  Serial.println("%");
  delay(10);  

  basinc = AtmosphericPressure.getPressure();
  Serial.print("Basinc: ");
  Serial.println(basinc);
  delay(10);
  
  toprakNem = SoilMoisture.ReadSoilMoisture();
  Serial.print("Toprak Nemi Degeri: ");
  Serial.println(toprakNem);
  delay(10);

  yagmurDeger = Rain.ReadRainAnalog();
  Serial.print("Yagmur Degeri: ");
  Serial.println(yagmurDeger);
  delay(10);

/*UltraviyoleIsikYogunlugu = UVlight.getUVI();  // ultraviyole ışık verisi okunursa
  Serial.print("Ultraviyole Işık Yoğunluğu: ");
  Serial.println(UltraviyoleIsikYogunlugu); */
  
  OrtamIsikYogunlugu = UVlight.getLUX();  // ortam ışık verisi okunursa
  Serial.print("Ortam Işık Yoğunluğu: ");
  Serial.println(OrtamIsikYogunlugu);
  
  if(OrtamIsikYogunlugu < 200){
    tone(D15,500,500,0);
    delay(500);
    tone(D15,800,500,0);
    delay(500);
    Serial.println("\nORTAM IŞIK YOĞUNLUĞU AZ");
    tone(D15,500,500,0);
    delay(500);
    tone(D15,800,500,0);
    delay(500);
    Serial.println("led yanıyor ...");
    dataString += "ORTAM IŞIK YOĞUNLUĞU AZ";
    dataString += "\r\n";
    dataString += "LED YANIYOR";
    dataString += "\r\n";
    dataString += "\r\n";
    dataString += "\r\n";
    RGB5050.setLedColorData(0, 255, 255, 255);
    RGB5050.show();  
  }else{
    RGB5050.setLedColorData(0, 0, 0, 0);
    RGB5050.show();
  }
  delay(10);

  Serial.println("");
  
  dataString += String(now.hour());
  dataString += ":";
  dataString += String(now.minute());
  dataString += ":";
  dataString += String(now.second());
  dataString += "  ";
  dataString += String(now.day());
  dataString += "/";
  dataString += String(now.month());
  dataString += "/";
  dataString += String(now.year());
  dataString += "\r\n";

  dataString += "Sıcaklık: ";
  dataString += String(TempHum.TtoDegC());
  dataString += "\r\n";

  dataString += "Bağıl nem: ";
  dataString += String(TempHum.RHtoPercent());
  dataString += "\r\n";

  dataString += "Basinc: ";
  dataString += String(AtmosphericPressure.getPressure());
  dataString += "\r\n";

  dataString += "Toprak Nemi Degeri: ";
  dataString += String(SoilMoisture.ReadSoilMoisture());
  dataString += "\r\n";

  dataString += "Yagmur Degeri: ";
  dataString += String(Rain.ReadRainAnalog());
  dataString += "\r\n";
  /*
  dataString += "Ultraviyole Işık Yoğunluğu: ";
  dataString += String(UVlight.getUVI());
  dataString += "\r\n"; */
  
  dataString += "Ortam Işık Yuğunluğu: ";
  dataString += String(UVlight.getLUX());
  dataString += "\r\n";
  dataString += "\r\n";
  dataString += "\r\n";

  appendFile(SDCard, "/YeniDosya.txt", dataString.c_str());
  
  delay(1000);
}
