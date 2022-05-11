/* 
 * File Name: LiDAR.h
 * Developer: Mohammad Tamzeed Moazzem, Austin Reichert, Hasaan Saleh
 * Described: Mbed Library for HC-SR04 ultrasonic sensor
 * 
 * This is adopted from https://os.mbed.com/components/HC-SR04/
 */

#ifndef MBED_ULTRASONIC_H
#define MBED_ULTRASONIC_H
 
#include "mbed.h"
 
class Ultrasonic
{
    public:
        /**iniates the class with the specified trigger pin, echo pin, update speed and timeout**/
        Ultrasonic(PinName trigPin, PinName echoPin);
        ~Ultrasonic();

        /** returns the last measured distance**/
        int getCurrentDistance(void);
    private:
        DigitalOut _trig;
        DigitalIn _echo;
        Timer sonar;
};
#endif
