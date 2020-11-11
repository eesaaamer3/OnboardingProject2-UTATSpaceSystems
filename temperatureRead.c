#include <avr/eeprom.h>

int val = 0;
int celsius = 0;
volatile unsigned int overflow;
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
  celsius = map(((analogRead(A0) - 20) * 3.04), 0, 1023, -40, 125);
  if(celsius >= 20){
    Serial.print("storing it in a specific memory");          
    Serial.println(celsius);			// debug value*/
    
  }
  else{
    Serial.print("storing it in another memory");          
    Serial.println(celsius);			// debug value*/
  }
    
}