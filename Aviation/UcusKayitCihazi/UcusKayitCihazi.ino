#include <Deneyap_GPSveGLONASSkonumBelirleyici.h>
#include <Deneyap_9EksenAtaletselOlcumBirimi.h>
#include <Deneyap_6EksenAtaletselOlcumBirimi.h>
#include <Deneyap_BasincOlcer.h>
#include <Deneyap_DerinlikOlcer.h>
#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

AtmosphericPressure BaroSensor;
TofRangeFinder Mesafe;
LSM6DSM AccGyro;
MAGNETOMETER Magne;
GPS GPS;

String dataString = "";

const char *ssid = "UcusKayitCihazi";              
const char *password = "deneyapkart1a";

WiFiServer server(80);

/*Dosya yazma fonksiyonu */
void writeFile(fs::FS &fs, const char *path, const char *message)
{
  Serial.printf("Dosya yaziliyor: %s\n", path);

  File file = fs.open(path, FILE_WRITE);
  if (!file)
  {
    Serial.println("Yazma islemi icin dosya acilamadi");
    return;
  }
  if (file.print(message))
  {
    Serial.println("Dosya yazildi");
  }
  else
  {
    Serial.println("Dosya yazma islemi basarisiz");
  }
  file.close();
}

/*Dosyaya ekleme yapma fonksiyonu */
void appendFile(fs::FS &fs, const char *path, const char *message)
{
  Serial.printf("Dosyaya eklendi: %s\n", path);

  File file = fs.open(path, FILE_APPEND);
  if (!file)
  {
    Serial.println("Ekleme islemi icin dosya acilamadi");
    return;
  }
  if (file.print(message))
  {
    Serial.println("Ekleme islemi basarili");
  }
  else
  {
    Serial.println("Ekleme islemi basarisiz");
  }
  file.close();
}

void setup()
{
  Serial.begin(115200);
  GPS.begin(0x2F);
  AccGyro.begin();
  Magne.begin(0x60);
  BaroSensor.begin(0x76);
  Mesafe.begin(0x29);
  SDCard.begin();
  writeFile(SDCard, "/YeniDosya.txt", "   VERİLER   \r\n");
  Serial.println();
  Serial.println("Erisim Noktasi (AP) konfigure ediliyor...");      

  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();                                       
  Serial.print("Erisim noktasi IP adresi: "); // 192.168.4.1
  Serial.println(myIP);
  server.begin();

  Serial.println("Server baslatildi");
}

void loop()
{
GPS.readGPS(RMC);

Serial.print("Konum: ");
float lat;
lat = GPS.readLocationLat();
Serial.printf("%.7f", lat);
Serial.print(",");
float lng;
lng = GPS.readLocationLng();
Serial.printf("%.7f\n", lng);

Serial.print("Tarih: ");
int day;
day = GPS.readDay();
Serial.print(day);
Serial.print("/");

int month;
month = GPS.readMonth();
Serial.print(month);
Serial.print("/");

int year;
year = GPS.readYear();
Serial.println(year);

Serial.print("Saat:  ");
int hour;
hour = GPS.readHour();
Serial.print(hour);
Serial.print(":");

int minute;
minute = GPS.readMinute();
Serial.print(minute);
Serial.print(":");

int second;
second = GPS.readSecond();
Serial.println(second);

Serial.println("\nAkselerometre degerleri");
Serial.print("X ekseni: ");
Serial.print(AccGyro.readFloatAccelX());
Serial.print("\tY ekseni: ");
Serial.print(AccGyro.readFloatAccelY());
Serial.print("\tZ ekseni: ");
Serial.println(AccGyro.readFloatAccelZ());
delay(50);

Serial.println("\nGyro degerleri");
Serial.print("X ekseni: ");
Serial.print(AccGyro.readFloatGyroX());
Serial.print("\tY ekseni: ");
Serial.print(AccGyro.readFloatGyroY());
Serial.print("\tZ ekseni: ");
Serial.println(AccGyro.readFloatGyroZ());
delay(50);

Serial.println("\nMagnetometre degerleri");
Serial.print("X ekseni:");
Serial.print(Magne.readMagnetometerX());
Serial.print("\tY ekseni:");
Serial.print(Magne.readMagnetometerY());
Serial.print("\tZ ekseni:");
Serial.println(Magne.readMagnetometerZ());
delay(50);

Serial.println("\nSicaklik degerleri");
Serial.print("Celsius: ");
Serial.print(AccGyro.readTempC());
Serial.print("\tFahrenheit: ");
Serial.println(AccGyro.readTempF());
delay(50);

Serial.print("\nBasinc: ");
Serial.println(BaroSensor.getPressure());
delay(50);

Serial.print("\nUzaklık: ");
Serial.println(Mesafe.ReadDistance());
delay(50);

Serial.println(" ");

dataString += "------------------------------------------------------------";
dataString += "\r\n";
dataString += "Konum: ";
dataString += String(GPS.readLocationLat());
dataString += ",";
dataString += String(GPS.readLocationLng());
dataString += "\r\n";

dataString += "Tarih: ";
dataString += String(GPS.readDay());
dataString += "/";
dataString += String(GPS.readMonth());
dataString += "/";
dataString += String(GPS.readYear());
dataString += "\r\n";

dataString += "Saat: ";
dataString += String(GPS.readHour());
dataString += ":";
dataString += String(GPS.readMinute());
dataString += ":";
dataString += String(GPS.readSecond());
dataString += "\r\n";

dataString += "Akselerometre degerleri: ";
dataString += "X ekseni: ";
dataString += String(AccGyro.readFloatAccelX());

dataString += " Y ekseni: ";
dataString += String(AccGyro.readFloatAccelY());

dataString += " Z ekseni: ";
dataString += String(AccGyro.readFloatAccelZ());
dataString += "\n";
dataString += "\r\n";

dataString += "Gyro degerleri: ";
dataString += "X ekseni: ";
dataString += String(AccGyro.readFloatGyroX());

dataString += " Y ekseni: ";
dataString += String(AccGyro.readFloatGyroY());

dataString += " Z ekseni: ";
dataString += String(AccGyro.readFloatGyroZ());
dataString += "\n";
dataString += "\r\n";

dataString += "Magnetometre degerleri: ";
dataString += "X ekseni: ";
dataString += String(Magne.readMagnetometerX());

dataString += " Y ekseni: ";
dataString += String(Magne.readMagnetometerY());

dataString += " Z ekseni: ";
dataString += String(Magne.readMagnetometerZ());
dataString += "\n";
dataString += "\r\n";

dataString += "Sıcaklık degerleri: ";
dataString += "Celsius: ";
dataString += String(AccGyro.readTempC());

dataString += " Fahrenheit: ";
dataString += String(AccGyro.readTempF());
dataString += "\n";
dataString += "\r\n";

dataString += "Basınç: ";
dataString += String(BaroSensor.getPressure());
dataString += "\r\n";
dataString += "\r\n";

dataString += "Derinlik Ölçer: ";
dataString += String(Mesafe.ReadDistance());
dataString += "\r\n";
dataString += "\r\n";
dataString += "\r\n";
dataString += "\r\n";

appendFile(SDCard, "/YeniDosya.txt", dataString.c_str());

WiFiClient client = server.available();

if(client) {
   String currentLine = "";
       while(client.connected()) 
    {                      
      if(client.available())
      { 
            client.print("Konum:");
            client.print(GPS.readLocationLat());
            client.print(",");
            client.println(GPS.readLocationLng());
            
            client.print("Tarih:");
            client.print(GPS.readDay()); 
            client.print("/");
            client.print(GPS.readMonth()); 
            client.print("/");
            client.println(GPS.readYear()); 

            client.print("Saat:");
            client.print(GPS.readHour()); 
            client.print("/");
            client.print(GPS.readMinute()); 
            client.print("/");
            client.println(GPS.readSecond()); 
            
            client.println("Akselerometre:");
            client.print("X ekseni");
            client.print(AccGyro.readFloatAccelX()); 
            client.print(" Y ekseni");
            client.print(AccGyro.readFloatAccelY()); 
            client.print(" Z ekseni");
            client.println(AccGyro.readFloatAccelZ());  
            
            client.println("Gyro degerleri:");
            client.print("X ekseni");
            client.print(AccGyro.readFloatGyroX()); 
            client.print(" Y ekseni");
            client.print(AccGyro.readFloatGyroY()); 
            client.print(" Z ekseni");
            client.println(AccGyro.readFloatGyroZ());                          
            
            client.println("Magnetometre degerleri:");
            client.print("X ekseni");
            client.print(Magne.readMagnetometerX()); 
            client.print(" Y ekseni");
            client.print(Magne.readMagnetometerY()); 
            client.print(" Z ekseni");
            client.println(Magne.readMagnetometerZ()); 

            client.print("Sicaklik degerleri:");
            client.print("Celsius:");
            client.println(AccGyro.readTempC());
            client.print("Fahrenheit:");
            client.println(AccGyro.readTempF());

            client.print("Basinc:");
            client.println(BaroSensor.getPressure());

            client.print("Derinlik:");
            client.println(Mesafe.ReadDistance());
            client.println(" ");     
    }
   }
    client.stop();
  }
  Serial.println("");
  delay(1000);
}
