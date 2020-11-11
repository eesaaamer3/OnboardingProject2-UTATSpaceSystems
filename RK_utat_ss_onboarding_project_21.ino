#include <avr/eeprom.h>
#include <avr/io.h>

int value = 0; //will be voltage from pin A0
int temp = 0; //will store temperature in C after conversion

void timer_delay(uint8_t seconds) //my user defined delay function
{
  //
}

void setup()
{
  Serial.begin(9600);
  
  TCNT0= 0x00; //Timer0 set to 0 initially?
  TCCR0 = (0<<WGM00) | (1<<WGM01); //using the compare mode because why not
  
  
  
  
  value = analogRead(A0);
  temp = ((value*4.9)/10);
  
  //in the set up, it'll run this once, so this is for writing the first time
  //in the loop function it will update
  if(temp > 20){
    eeprom_write_byte(0,temp);
  else {
    eeprom_write_byte(2,temp);//what if negative?
  }
}

void loop()
{
  //<insert delay function here
  
  value = analogRead(A0);
  //the value returned by analog read is
  //an int between 0 and 1023, where each increment is 
  //4.9 millivolts/unit
  
  //to get the voltage, by 4.9
  //then based off of the TMP36 datasheet, 
  //I need to divide by 10 mV/C to get the temperature
  
  temp = ((value*4.9)/10);
  
  if(temp > 20){
    eeprom_update_byte(0,temp);
  else {
    eeprom_update_byte(2,temp);//what if negative?
  }
  
} 