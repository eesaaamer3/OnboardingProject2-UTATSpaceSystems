#include <avr/eeprom.h>

int sensorPin = 0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  
  float initReading = analogRead(sensorPin);
  
  float voltReading = ((initReading /1024) * 5) - 0.5;
  
  float tempReading = round(voltReading / 0.01);
  // Serial.print(tempReading);
  
  if (tempReading < 20) {
    eeprom_write_byte((uint8_t *)0, tempReading);
  } else if (tempReading > 20) {
    eeprom_write_byte((uint8_t *)2, tempReading);
  }
 
  
}