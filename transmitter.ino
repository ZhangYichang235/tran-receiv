#include <Wire.h>
#include <RTClib.h>
#include <RH_ASK.h>

RTC_DS3231 rtc;
RH_ASK driver;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Wire.begin();
  rtc.begin();
  driver.init();
  
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, setting time...");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void loop() {
  DateTime now = rtc.now();

  const char* timestamp_format = "%02d:%02d:%02d";
  char timestamp[8];
  sprintf(timestamp, timestamp_format, now.hour(), now.minute(), now.second());

  const char* message = ";Viking Industries;5;";
  char data[40];
  sprintf(data, "%s%s", timestamp, message);
  
  driver.send((uint8_t*)data, strlen(data));
  driver.waitPacketSent();
  
  Serial.println(data);
  
  delay(1000);
}
