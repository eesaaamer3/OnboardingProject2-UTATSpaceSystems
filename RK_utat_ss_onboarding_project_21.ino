#include <avr/eeprom.h>
#include <avr/io.h>

float value = 0; //will be voltage from pin A0
float temp = 0; //will store temperature in C after conversion

void timer_delay(uint8_t seconds) //my user defined delay function
{
  TCNT1= 0; //Timer1 set to 0 initially?
  TCCR1A = (0<<WGM13) | (1<<WGM12) | (0<<WGM11) | (0<<WGM10); //CTC mode, assuming the rest are 0 by default? 
  TCCR1B = (1<<CS10) | (0<<CS11) | (1<<CS12); //sets prescaler to 1024
  
  OCR1A = (seconds/(1/15625));
  //number of ticks in order to get to seconds
  //for 3 seconds, it should return 46875
  //that is if my math is correct, and that first number is 
  //based off of the prescalar that TCCR1B is set to 
  
  
  //at this point the timer should reset on its own 
  //because its in CTC mode, function returns here 
  
}

void setup()
{
  Serial.begin(9600);
   
  value = analogRead(A0);
  temp = round(((value/1024)*5 - 0.5)/0.01);
  
  //in the set up, it'll run this once, so this is for writing the first time
  //in the loop function it will update
  if(temp > 20){
    eeprom_write_byte((uint8_t*)0,temp);
  } else {
    eeprom_write_byte((uint8_t*)2,temp);//what if negative?
  }
}

void loop()
{
  //<insert delay function here
  timer_delay(3); 
  
  value = analogRead(A0);
  //the value returned by analog read is
  //an int between 0 and 1023, where each increment is 
  //4.9 millivolts/unit
  
  //to get the voltage, by 4.9
  //then based off of the TMP36 datasheet, 
  //I need to divide by 10 mV/C to get the temperature
  
  temp = round(((value/1024)*5 - 0.5)/0.01);
  
  
  if(temp > 20){
    eeprom_update_byte((uint8_t*)0,temp);
  } else {
    eeprom_update_byte((uint8_t*)2,temp);//what if negative?
  }
  
  //FOR TESTING:
  uint8_t temptest0 = eeprom_read_byte((uint8_t*)0);
  uint8_t temptest2 = eeprom_read_byte((uint8_t*)2);
  Serial.print("in address 0: ");
  Serial.println(temptest0);
  Serial.print("in address 2: ");
  Serial.println(temptest2);
 
  
} 