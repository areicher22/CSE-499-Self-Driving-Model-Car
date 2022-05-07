/* 
 * File Name: LiDAR.cpp
 * Developer: Mohammad Tamzeed Moazem
 * Date:      26 April 2022
 * Described: Mbed Library for the Benewake TF-Luna Lidar sensor
 *            configured for the I2C interface
 * 
 * Default settings for the TF-Luna are:
 *    0x10  -  default slave device I2C address `TFL_DEF_ADR`
 *    100Hz  - default data frame-rate `TFL_DEF_FPS`
 *
 */

#include "mbed.h"
#include "LiDAR.h"
#include <cstdio>

// Constructor
LiDAR::LiDAR(PinName sda, PinName scl):i2c(sda, scl){
    _addr = TFL_DEF_ADR<<1; // Shifting Slave address 1 bit and set to _addr 
}

// Destructor
LiDAR::~LiDAR(){}

// Initialize the LiDAR to be used
void LiDAR:: begin(){

    i2c.frequency(100000); // Set I2C frequency
    Hard_Reset(); // Restore LiDAR to factory defaults
    wait_us(1000000); 

    _reg[0]={TFL_FPS_LO}; 
    _dataArray[0]= {FPS_125};  
    i2c.write(_addr, _reg, 1, true); // Load to register value
    i2c.write(_addr, _dataArray, 1, false); // Load sampling rate value
    
    printf("TF-Luna LiDAR\nLiDAR is ready to use.\n");
    printf("S/N: ");
    Get_Product_Code(); // Get the serial number
    printf("\n");
}

// Returns distance from object in cm
float LiDAR::get_dist(){
    _reg[0] = {TFL_DIST_LO};
    i2c.write(_addr, _reg, 1, true); // Write to register value to slave address
    i2c.read(_addr, _dataArray, 1, false); // Read data from register of slave address

    return (float)_dataArray[0]; // Return distance in cm
}

// Returns chip temperature in Fahrenheit or Celsius
float LiDAR::get_temp(char c){
    float temp;
    _reg[0] = {TFL_TEMP_LO};
    i2c.write(_addr, _reg, 1, true); // Write to register value to slave address
    i2c.read(_addr, _dataArray, 1, false); // Read data from register of slave address

    if(c == 'F'){
        temp = (((float)_dataArray[0]*9)/5)+32.0; // Get temperature of the chip and convert it into fahrenheit
    }
    else{
        temp = (float)_dataArray[0]; // Get temperature of the chip in celsius
    }

    return temp; // Return tempurature
}

// Returns LiDAR laser strength
int LiDAR::get_strength(){
    _reg[0] = {TFL_FLUX_LO};
    i2c.write(_addr, _reg, 1, true); // Write to register value to slave address
    i2c.read(_addr, _dataArray, 1, false); // Read data from register of slave address

    return (int)_dataArray[0]; // Return laser strength value
}

// Prints LiDAR product code
void LiDAR::Get_Product_Code(){
    _reg[0]={TFL_SN};
    i2c.write(_addr, _reg, 1, true); // Write to register value to slave address
    i2c.read(_addr, _dataArray, 14); // Read data from register of slave address

    for (int i=0; i<14; i++) {
        printf("%c", _dataArray[i]);
    }
}

// Restarts the LiDAR
void LiDAR::Soft_Reset(){
    _reg[0] = {TFL_SOFT_RESET};
    _dataArray[0] = {0x02};
    i2c.write(_addr, _reg, 1, true); // Write to register value to slave address
    i2c.write(_addr, _dataArray, 1, false); // Read data from register of slave address
}

// Restores to factory defaults
void LiDAR::Hard_Reset(){
    _reg[0] = {TFL_HARD_RESET};
    _dataArray[0] = {0x01};
    i2c.write(_addr, _reg, 1, true); // Write to register value to slave address
    i2c.write(_addr, _dataArray, 1, false); // Write data from register of slave address
}

// Set LiDAR sampling rate. By default 100Hz
void LiDAR::Set_Frame_Rate(){
    _reg[0] = {TFL_FPS_LO};
    _dataArray[0] = {FPS_125};
    i2c.write(_addr, _reg, 1, true); // Write to register value to slave address
    i2c.write(_addr, _dataArray, 1, false); // Write data from register of slave address
}