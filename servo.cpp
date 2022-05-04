  #include "mbed.h"
  #include <iostream>
  #include <string>
  #include <cstdio>
  #include <iterator>

    void fan();     // enables wipers
  
  PwmOut servo1(PB_8);       // servo motor set at pb_8

  int main() {
      
      RCC -> AHB2ENR |= 0x6;        // Enable port B, C

      GPIOB -> MODER |= 0x40000;    // 01 output
      GPIOB -> MODER &= ~(0x80000); // pin 9

      GPIOC -> MODER |= 0x50040;    // output mode 8/9 0101 0000 0000 0100 0000
      GPIOC -> MODER &= ~(0xA0080); // pin 6/8/9


        servo1.period_ms(20);       // set the duty cycle of servo to 20ms (period)

      while(1) {                    // run forever
        fan();
        thread_sleep_for(50);       // sleep for 50sec to account for bounce
      }


}

void fan() {
    float off;
    for(off = 0.0000; off < 0.0010; off += 0.0001) {           // right
            servo1.pulsewidth(0.0010 + off);                   // servo position determined by a pulsewidth between 1-2ms
            thread_sleep_for(15);                              // 50ms time between movements, enlarge for slower speed, shrink for faster
    }
    for(off = 0.0010; off > 0.0000; off -= 0.0001) {           // left
            servo1.pulsewidth(0.0010 + off);                   // servo position determined by a pulsewidth between 1-2ms
            thread_sleep_for(15);
    }                                          // reset flag after run
}
