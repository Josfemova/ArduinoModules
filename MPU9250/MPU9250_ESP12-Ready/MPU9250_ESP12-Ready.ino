#include "MPU9250_ESP12-Ready.h"

MPU9250 MPU(MPU_ADDRESS, I2C_PORT, I2C_CLOCK);
void setup(){
    Serial.begin(115200);
    bool mpuStat = false;
    if(!mpuStat){
        int res = setupMPU9250(MPU);
        switch (res)
        {
        case -1:
            Serial.println("Error en conexión al mpu");
            abort();
            break;
        case -2:
            Serial.println("Error de hardware en magnetómetro");
            abort();
            break;
        default:
            mpuStat = true;
            break;
        }
    }

}
void loop(){
    updateAccelInfo(MPU);
    Serial.println("Pitch val: ");
    delay(250);
}
