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

void print_number(int number) {
  char buffer[6]; // Buffer to hold the string representation of the number
  itoa(number, buffer, 10); // Convert the number to a string
  for (int i = 0; buffer[i] != '\0'; i++) {
    print(buffer[i]); // Print each character of the string
  }
}

int counter = 0;
int print_counter = 0; // Counter for printing every 100ms

void setup() {
  // Configure 16-bit Timer1
  TCCR1A = 0; // Clear Timer1 control register A
  TCCR1B = (1 << CS10); // Set prescaler to CLK/1
  
  // Configure UART
  setup_uart();
}

void loop() {
  counter++;
  delay_ms(20); // Delay for 20 milliseconds
  
  // Increment print_counter every 20 milliseconds
  print_counter++;
  
  // If 100 milliseconds have passed, print the counter value and reset print_counter
  if (print_counter == 5) {
    print_counter = 0; // Reset print_counter
    print_number(counter); // Print the counter value
    print('\n'); // Print a newline character for clarity
  }
}
