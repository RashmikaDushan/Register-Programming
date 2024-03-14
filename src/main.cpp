#include <avr/io.h>
#include <Arduino.h>

void setup_uart() {
  // Set baud rate to 9600
  UBRR0H = 0;
  UBRR0L = 103;
  
  // Enable receiver and transmitter
  UCSR0B = (1 << RXEN0) | (1 << TXEN0);
  
  // Set frame format: 8 data bits, 1 stop bit
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void delay_us(uint16_t us) {
  // Configure Timer1 for microsecond delay
  TCNT1 = 0; // Reset Timer1 counter
  
  // Calculate the number of timer ticks needed for the given microseconds
  uint16_t ticks = us * 16;
  while (TCNT1 < ticks) {
    // Wait
  }
}

void delay_ms(uint16_t ms) {
  for (uint16_t i = 0; i < ms; ++i) {
    delay_us(1000); // Delay 1 millisecond
  }
}

void print(char byte) {
  // Wait for empty transmit buffer
  while (!(UCSR0A & (1 << UDRE0)));
  
  // Put data into buffer, sends the data
  UDR0 = byte;
}

void setup() {
  // Configure 16-bit Timer1
  TCCR1A = 0; // Clear Timer1 control register A
  TCCR1B = (1 << CS10); // Set prescaler to CLK/1
  
  // Configure UART
  setup_uart();
}

void loop() {
  print('H');
  delay_ms(1000); // Delay for 1 second
  print('L');
  delay_ms(1000); // Delay for 1 second
}
