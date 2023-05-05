#include <RH_ASK.h>

RH_ASK driver;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  driver.init();
}

void loop() {
  uint8_t buf[40];
  uint8_t buflen = sizeof(buf);
  
  if (driver.recv(buf, &buflen)) {
    buf[buflen] = '\0';
    Serial.println((char*)buf);
  }
}
