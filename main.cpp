/*
 * File Name: main.cpp
 * Developer: Mohammad Tamzeed Moazzem, Austin Reichert, Hasaan Saleh
 *
 */

#include "LiDAR.h"
#include "mbed.h"
#include "ultrasonic.h"
#include <cstdio>

#define MIN 1000
#define MID 1500
#define MAX 2000
#define STEP 30
#define TIME 100 // Time delay between steps in milliseconds

// void servo_move(int value);

// LiDAR object initialization
LiDAR lidar(PB_9, PB_8);

// Ultrasonic sensor object initialization
Ultrasonic left_sonar(PD_7, PD_6);

// Ultrasonic sensor object initialization
Ultrasonic right_sonar(PD_5, PD_4);

// DigitalIn object initialization
DigitalIn check(PA_3);

// DigitalOut object initialization
DigitalOut motor(PC_8);

// PwmOut object initialization
PwmOut servo(PD_15);

float lider_dist = 0.0;
float left_sonar_dist = 0.0;
float right_sonar_dist = 0.0;

// main() runs in its own thread in the OS
int main() {
  // LiDAR initialization to use
  lidar.begin();

  motor = 0;

  // Servo period set to 20 millisecond
  servo.period_ms(20);

  while (true) {
    if (check == 1) {
      lider_dist = lidar.get_dist();
      printf("%f\n", lider_dist);

      if (lider_dist < 20) {
        left_sonar_dist = left_sonar.getCurrentDistance();
        right_sonar_dist = right_sonar.getCurrentDistance();
        servo = 1;

        if (right_sonar_dist >= left_sonar_dist) {

          for (int i = MIN; i <= MAX; i += STEP) {
            servo.pulsewidth_us(i);
            wait_us(TIME * 200);
          }
        }
        if (left_sonar_dist > right_sonar_dist) {
          for (int i = MAX; i >= MIN; i -= STEP) {
            servo.pulsewidth_us(i);
            wait_us(TIME * 200);
          }
        }
        servo = 0;

      } else {
        motor = 1;
      }
    }
  }
  return 0;
}
