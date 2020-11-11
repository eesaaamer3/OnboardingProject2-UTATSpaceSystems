#include <avr/eeprom.h>

int val = 0;
float celsius = 0;
volatile unsigned int overflow;
uint8_t finalCel = 0;
ISR(TIMER1_COMPA_vect){
  overflow++;
  //Serial.println(overflow);
  PORTD ^= 0b10000000;
  
}

void timer_delay(uint8_t seconds){
  TCCR1A = 0b00000000; //clear timer on compare mode
  TCCR1B = 0b00001101; //prescaler to 4seconds
  OCR1A = 15624; //for three seconds
  TIMSK1 = 0b00000010; //corresponding to OCR1A
  overflow = 0;
  while(overflow < seconds){
    sei();
  } 
}

void setup(){
  
  Serial.begin(9600); //init serial monitor connection
  //configuring timer1 (turn on timer)
  DDRD = 0b100000000;
  PORTD = 0b000000100; //pin 7 
  
}
  
void loop(){  
   timer_delay(3);
   val = analogRead(A0);  // read the input pin
  //convert the analog signal to c using map()
  double temp = (double)val/1024;
  temp = temp * 5;//the 5 volt 
  temp = temp - 0.5; // offset of 0.5 volt
  //now temp is our voltage value
  celsius = temp /0.01;
  finalCel = round(celsius); // if the value is neg, finalCel = 256-Cel
  
  if(celsius >= 20){
    Serial.print("storing it in memory 0: ");
    eeprom_update_byte((uint8_t*)0,finalCel);
    Serial.println(eeprom_read_byte((uint8_t*)0));			// debug value*/
    
  }
  else{
    Serial.print("storing it in memory 46: "); 
  
    //updating
    eeprom_update_byte((uint8_t*)46,finalCel);
    //dealing with negative temps
    if(eeprom_read_byte((uint8_t*)46) > 125){
      int tempcel = (int)eeprom_read_byte((uint8_t*)46) - 257;
      Serial.println(tempcel);			// debug value*/
    }
  }
    
}