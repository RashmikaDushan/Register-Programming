#include <avr/io.h>
#include <avr/interrupt.h>
#include <Arduino.h>

volatile uint16_t counter = 0;

ISR(TIMER1_OVF_vect)
{
  TCNT1 = 65519; // Timer Preloading
  // Handle The 1ms Timer Interrupt
  //...
  counter++;
}

// void delay_ms(uint16_t ms)
// {
//   counter = 0;
//   while (counter < ms)
//   {
//     // Wait
//   }
// }

void delay_us(uint16_t us)
{
  counter = 0;
  while (counter < us)
  {
    // Wait
  }
}

void setup()
{
  TCCR1A = 0;           // Init Timer1
  TCCR1B = 0;           // Init Timer1
  TCCR1B |= 0b00000001;  // No prescaller
  TCNT1 = 65519;        // Timer Preloading
  TIMSK1 |= 0b00000001;  // Enable Timer Overflow Interrupt
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}
void loop()
{
  Serial.println("Start");
  digitalWrite(LED_BUILTIN, HIGH);
  delay_us(1000);
  Serial.println("end");
  digitalWrite(LED_BUILTIN, LOW);
  delay_us(1000);
}