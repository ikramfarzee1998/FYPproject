
#include <ESP8266_Lib.h> 
#include <BlynkSimpleShieldEsp8266.h>
#define BLYNK_PRINT Serial


#define EspSerial Serial3
#define ESP8266_BAUD 115200
char auth[] = "oL51mYWB1MoV72_woJthVxvQ0f8JQ_dy";
char ssid[] = "POCO X3 NFC";
char pass[] = "12345ikr";
#define EspSerial Serial3
#define ESP8266_BAUD 115200
ESP8266 wifi(&EspSerial);



void setup()
{
  Serial.begin(115200);
  Serial3.begin(115200);

  delay(10);
  EspSerial.begin(ESP8266_BAUD);
  delay(10);
  Blynk.begin(auth, wifi, ssid, pass);
  Blynk.begin(auth, wifi, ssid, pass,"blynk-cloud.com", 8080);
  
}

void loop()
{
  Blynk.run();
 
}
