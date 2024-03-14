#include <avr/io.h>
#include <avr/interrupt.h>
#include <Arduino.h>

uint16_t counter;

ISR(TIMER1_OVF_vect)
{
  TCNT1 = 49535; // Timer Preloading
  // Handle The 1ms Timer Interrupt
  //...
  counter++;
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

void delay_ms(uint16_t ms){
  counter = 0;
  while(counter<ms){
    // wait
  }
}
 
void setup()
{
  TCCR1A = 0;           // Init Timer1
  TCCR1B = 0;           // Init Timer1
  TCCR1B |= 0b00000001;  // No prescaller
  TCNT1 = 49535;        // Timer Preloading
  TIMSK1 |= 0b00000001;  // Enable Timer Overflow Interrupt
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}
void loop()
{
  Serial.println("Start");
  delay_ms(2000);
  Serial.println("end");
  delay_ms(2000);
}