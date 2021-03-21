#ifndef MPU9250_PRE_H
#define MPU9250_PRE_H

#include <Arduino.h>
#include <MPU9250.h>
#include <quaternionFilters.h>

#define I2C_CLOCK 400000
#define I2C_PORT Wire
#define MPU_ADDRESS 0x68 //0x69

//utilidades
#define PITCH MPU.pitch
#define YAW MPU.yaw
#define ROLL MPU.roll
#define ACELER_X MPU.ax
#define ACELER_Y MPU.ay
 
int setupMPU9250(MPU9250& MPU);
void updateAccelInfo(MPU9250& MPU);



#endif
