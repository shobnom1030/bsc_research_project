//TECHATRONIC.COM
// BLYNK LIBRARY
// https://github.com/blynkkk/blynk-library
// ESP8266 LIBRARY
// https://github.com/ekstrand/ESP8266wifi
// Arduino-MAX30100 LIBRARY
// https://github.com/oxullo/Arduino-MAX30100
// SimpleTimer LIBRARY
// https://github.com/jfturcot/SimpleTimer

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);



#define BLYNK_TEMPLATE_ID "TMPL69xI5ztrj"
#define BLYNK_TEMPLATE_NAME "IoT Based Smart Health Monitoring System"
#define BLYNK_AUTH_TOKEN "L_byGfUIDHd0vZ0sBxaA9rlFbvWISfD9"

#define BLYNK_PRINT Serial

#include <Wire.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "MAX30100_PulseOximeter.h"
#include <SimpleTimer.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
// BPM GAUGE CONNECT V2
// SP02 GAUGE CONNECT V3


char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Realme8";
char pass[] = "25802580";         // Your WiFi Password.

#define REPORTING_PERIOD_MS   3000

PulseOximeter pox;
uint32_t tsLastReport = 0;
void onBeatDetected()
{
;
}

BlynkTimer timer;

void setup()
{
  lcd.begin(16,2);
  lcd.init();   // initializing the LCD
  lcd.backlight(); // Enable or Turn On the backlight 
  lcd.clear();
Serial.begin(115200);

Blynk.begin(auth, ssid, pass);
Serial.print("Initializing pulse oximeter..");
if (!pox.begin()) {
Serial.println("FAILED");
for (;;);
} else {
Serial.println("SUCCESS");
digitalWrite(1, HIGH);
}
pox.setIRLedCurrent(MAX30100_LED_CURR_24MA);
// Register a callback for the beat detection
pox.setOnBeatDetectedCallback(onBeatDetected);
timer.setInterval(3000L, getSendData);
}
void loop()
{
timer.run(); // Initiates SimpleTimer
Blynk.run();

lcd.setCursor(0,0);
lcd.print("BPM:");
lcd.print(pox.getHeartRate());
lcd.setCursor(0,1);
lcd.print("SpO2:");
lcd.print(pox.getSpO2());

// Make sure to call update as fast as possible
pox.update();
if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
// to android cell phone application
Serial.print("BPM:");
Serial.print(pox.getHeartRate());
//blue.println("\n");
Serial.print("  SpO2:");
Serial.print(pox.getSpO2());
Serial.print("%");
Serial.println("\n");



Blynk.virtualWrite(V2, pox.getHeartRate() );
Blynk.virtualWrite(V3, pox.getSpO2());
tsLastReport = millis();


}
}
void getSendData()
{
}
