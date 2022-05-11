/* 
 * File Name: LiDAR.h
 * Developer: Mohammad Tamzeed Moazem
 * Described: Mbed Library for HC-SR04 ultrasonic sensor
 * 
 * This is adopted from https://os.mbed.com/components/HC-SR04/
 */

#include "mbed.h"
#include "ultrasonic.h"

Ultrasonic::Ultrasonic(PinName trigPin, PinName echoPin):_trig(trigPin), _echo(echoPin){}

Ultrasonic::~Ultrasonic(){}

int Ultrasonic::getCurrentDistance(void){
  int dist;
  int correction;
  sonar.reset();
  // measure actual software polling timer delays
  // delay used later in time correction
  // start timer
  sonar.start();
  // min software polling delay to read echo pin
  while (_echo == 2) {
  };
  // stop timer
  sonar.stop();
  // read timer
  correction = sonar.elapsed_time().count();

  _trig = 1;
  sonar.reset();
  wait_us(10.0);
  _trig = 0;

  // wait for echo high
  while (_echo == 0) {
  };
  // echo high, so start timer
  sonar.start();
  // wait for echo low
  while (_echo == 1) {
  };
  // stop timer and read value
  sonar.stop();
  // subtract software overhead timer delay and scale to cm
  dist = (sonar.elapsed_time().count() - correction) / 58.0;

  // Return distance measured in cm
  return dist;
}