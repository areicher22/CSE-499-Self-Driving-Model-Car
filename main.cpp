/*
Written by: Austin Reichert, Mohammad Tamzeed Moazzem, Hasaan Saleh
File purpose: To implement a PID controller which controls the steering angle of a psuedo-FSD car
Modules/Subroutines: 
    - main()
    - pid()

Corresponds to: CSE 499 Final Project
Inputs:
Outputs:
Constraints: 

Sources/References: 
    RM0432 Reference Manual
    Dr.Winikus' CSE-321 Lectures
    Arduino Open Source Libraries
    University of Michigan Control Tutorials: https://ctms.engin.umich.edu/CTMS/index.php?example=Introduction&section=ControlPID
    thingyverse chassis: https://www.thingiverse.com/thing:4892947/files

*/

#include "mbed.h"

float pid(float theta); //function that handles the PID controller calculations
                        //takes in lidar and current servo position as args and outputs new steering angle



// main() runs in its own thread in the OS
int main()
{
    while (true) {

    }
}



