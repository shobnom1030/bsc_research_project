#include <OneWire.h>
#include <DallasTemperature.h>

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define BLYNK_TEMPLATE_ID "TMPL69xI5ztrj"
#define BLYNK_TEMPLATE_NAME "IoT Based Smart Health Monitoring System"
#define BLYNK_AUTH_TOKEN "L_byGfUIDHd0vZ0sBxaA9rlFbvWISfD9"

#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Realme8";
char pass[] = "25802580";
int depth =20;

BlynkTimer timer;



#define ONE_WIRE_BUS D3 // DS18B20 on arduino pin2 corresponds to D4 on physical board "D4 pin on the ndoemcu Module"
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);
float temp;



void setup() 
{
  lcd.begin(16,2);
  lcd.init();   // initializing the LCD
  lcd.backlight(); // Enable or Turn On the backlight 
  lcd.clear();
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  DS18B20.begin();
  timer.setInterval(1000L, getSendData);
}

void loop()
{
  timer.run(); // Initiates SimpleTimer
  Blynk.run();
}

/***************************************************
 * Send Sensor data to Blynk
 **************************************************/
void getSendData()
{
  DS18B20.requestTemperatures(); 
  temp = DS18B20.getTempCByIndex(0); // Celcius
  Serial.println(temp);
  Blynk.virtualWrite(V1, temp); //virtual pin V3
  
    ////////////////// lcd////////////
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Temp = ");
    lcd.print(temp);
    lcd.print("C");
    delay(1000);
    lcd.clear();


}
