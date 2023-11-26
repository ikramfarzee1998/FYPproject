#define BLYNK_PRINT Serial
#include <ESP8266_Lib.h> // insert this library 
#include <BlynkSimpleShieldEsp8266.h>
#define BLYNK_TEMPLATE_ID "TMPL6qWHdKIic"
#define BLYNK_TEMPLATE_NAME "Ir Sensor"
#define EspSerial Serial3
#define ESP8266_BAUD 115200
ESP8266 wifi(&EspSerial);
#include <TinyGPS.h>
char auth[] = "oL51mYWB1MoV72_woJthVxvQ0f8JQ_dy";
char ssid[] = "POCO X3 NFC";
char pass[] = "12345ikr";
int stock = 10; 
int sale=0;
bool lowStockNotified = false;       
unsigned int move_index = 1; 
TinyGPS gps;
float lat, lon;
WidgetMap myMap(V0);

  
void irsensor()
{
  int sensorValue = digitalRead(2);

  if (sensorValue == LOW && stock > 0) 
  {
    stock--;
    sale++;
    Blynk.virtualWrite(V3, sale);
    Serial.print("Stock: ");
    Serial.println(stock);
    delay(2000);
  }
  
  if (stock < 3 && !lowStockNotified) 
  { 
    Serial.println("Stock Low"); 
    lowStockNotified = true; 
    Blynk.logEvent("stock_low");
  }
  

  if (stock == 0) 
  { 
    Serial.println("Finish Product");
    Blynk.logEvent("stock_finish");
  }
}

void readGPS() 
{
  while (Serial2.available()) 
  {
    if (gps.encode(Serial2.read())) 
    {
      gps.f_get_position(&lat, &lon);
      Serial.print("Position: ");
      Serial.print("Latitude: ");
      Serial.print(lat, 6);
      Serial.print(",");
      Serial.print("Longitude: ");
      Serial.println(lon, 6);
      Blynk.virtualWrite(V4, String(lat, 6));   
      Blynk.virtualWrite(V5, String(lon, 6));
      myMap.location(move_index, lat, lon, "Vending Machine Location");

    }
  }
}


void setup() 
{
  Serial.begin(115200);
  Serial3.begin(115200);
  delay(10);
  EspSerial.begin(ESP8266_BAUD);
  delay(10);
  Blynk.begin(auth, wifi, ssid, pass);
  Serial2.begin(9600);
  pinMode(2, INPUT); 
}

void loop() 
{
  
  readGPS();
  irsensor();
  Blynk.virtualWrite(V2, String(stock));
  Blynk.virtualWrite(V3, int(sale));
}
