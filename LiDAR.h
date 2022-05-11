/* 
 * File Name: LiDAR.h
 * Developer: Mohammad Tamzeed Moazem, Austin Reichert, Hasaan Saleh
 * Date:      26 April 2022
 * Described: Mbed Library for the Benewake TF-Luna Lidar sensor
 *            configured for the I2C interface
 */

#include "mbed.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//      Definitions
// - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#define TFL_DEF_ADR          0x10   // default I2C address = 16
#define TFL_DEF_FPS          0x64   // default frame-rate = 100fps

// - - - -   Register Names and Numbers   - - - -
#define TFL_DIST_LO          0x00  //R Unit: cm
#define TFL_DIST_HI          0x01  //R
#define TFL_FLUX_LO          0x02  //R
#define TFL_FLUX_HI          0x03  //R
#define TFL_TEMP_LO          0x04  //R Unit: 0.01 Celsius
#define TFL_TEMP_HI          0x05  //R
#define TFL_TICK_LO          0x06  //R Timestamp
#define TFL_TICK_HI          0x07  //R
#define TFL_ERR_LO           0x08  //R
#define TFL_ERR_HI           0x09  //R
#define TFL_VER_REV          0x0A  //R
#define TFL_VER_MIN          0x0B  //R
#define TFL_VER_MAJ          0x0C  //R
#define TFL_SN               0x10

#define TFL_SAVE_SETTINGS    0x20  //W -- Write 0x01 to save
#define TFL_SOFT_RESET       0x21  //W -- Write 0x02 to reboot.
                       // Lidar not accessible during few seconds,
                       // then register value resets automatically
#define TFL_SET_I2C_ADDR     0x22  //W/R -- Range 0x08,0x77.
                       // Must reboot to take effect.
#define TFL_SET_TRIG_MODE    0x23  //W/R -- 0-continuous, 1-trigger
#define TFL_TRIGGER          0x24  //W  --  1-trigger once
#define TFL_ENABLE           0x25  //W/R -- 0-disable, 1-enable
#define TFL_FPS_LO           0x26  //W/R -- lo byte
#define TFL_FPS_HI           0x27  //W/R -- hi byte
#define TFL_SET_LO_PWR       0x28  //W/R -- 0-normal, 1-low power
#define TFL_HARD_RESET       0x29  //W  --  1-restore factory settings

/////// FPS (Low Power Mode) ///////
#define FPS_1                   0x01
#define FPS_2                   0x02
#define FPS_3                   0x03
#define FPS_4                   0x04
#define FPS_5                   0x05
#define FPS_6                   0x06
#define FPS_7                   0x07
#define FPS_8                   0x08
#define FPS_9                   0x09
#define FPS_10                  0x0A

////// FPS (High Power Mode) /////
#define FPS_35                  0x23
#define FPS_50                  0x32
#define FPS_100                 0x64
#define FPS_125                 0x7D
#define FPS_250                 0xFA

class LiDAR{
    public:
        // Constructor & Destructor
        LiDAR(PinName sda, PinName scl);
        ~LiDAR();

        // Initialize LiDAR sensor
        void begin();
        
        // Get distance    
        float get_dist();

        // Get chip temparature
        float get_temp(char c);
        
        // Get strength of the laser
        int get_strength();
        
        // Explicit Device Commands
         void Get_Product_Code(); // Serial Number 
         void Soft_Reset();  // Reset and reboot
         void Hard_Reset();  // Restore factory defaults
         void Set_Frame_Rate(); // Set sampling rate

        private:

        I2C i2c; // I2C master object
        unsigned int _addr; // Slave address holder
        char _reg[1]; // Register value holder
        char _dataArray[14]; // Data holder 
};
