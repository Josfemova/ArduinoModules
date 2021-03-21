#include "MPU9250_ESP12-Ready.h"

int setupMPU9250(MPU9250& MPU){
  Wire.begin();
  delay(1000);
  
  //Lee un registro del MPU para confirmar si el mismo está comunicado. en caso de que no
  //el byte que retorna la lectura de registro es 0xFF
  byte c = MPU.readByte(MPU_ADDRESS, WHO_AM_I_MPU9250);
  
  if (c == 0x71) // WHO_AM_I debe ser 0x71
  {
    MPU.MPU9250SelfTest(MPU.selfTest);
    MPU.calibrateMPU9250(MPU.gyroBias, MPU.accelBias);
    MPU.initMPU9250();
    byte d = MPU.readByte(AK8963_ADDRESS, WHO_AM_I_AK8963);
    if (d != 0x48) // WHO_AM_I debe ser 0x48 si el magnetómetro sirve
      return -2; //indica error de manetómetro
    else{
      MPU.initAK8963(MPU.factoryMagCalibration);
      MPU.getAres();
      MPU.getGres();
      MPU.getMres();
    }
  }else{
    //indica falla general
    return -1;
  }
}
void updateAccelInfo(MPU9250& MPU){
  if (MPU.readByte(MPU_ADDRESS, INT_STATUS) & 0x01)
  {
    MPU.readAccelData(MPU.accelCount);
    MPU.readGyroData(MPU.gyroCount);
    MPU.readMagData(MPU.magCount);
    
    //valor de aceleración en g's (fracciones de valor de la gravedad)
    MPU.ax = (float)MPU.accelCount[0] * MPU.aRes; // - MPU.accelBias[0];
    MPU.ay = (float)MPU.accelCount[1] * MPU.aRes; // - MPU.accelBias[1];
    MPU.az = (float)MPU.accelCount[2] * MPU.aRes; // - MPU.accelBias[2];

    // calcula valor en grados por segundo
    MPU.gx = (float)MPU.gyroCount[0] * MPU.gRes;
    MPU.gy = (float)MPU.gyroCount[1] * MPU.gRes;
    MPU.gz = (float)MPU.gyroCount[2] * MPU.gRes;

    //valor en miliGauss
    MPU.mx = (float)MPU.magCount[0] * MPU.mRes
               * MPU.factoryMagCalibration[0] - MPU.magBias[0];
    MPU.my = (float)MPU.magCount[1] * MPU.mRes
               * MPU.factoryMagCalibration[1] - MPU.magBias[1];
    MPU.mz = (float)MPU.magCount[2] * MPU.mRes
               * MPU.factoryMagCalibration[2] - MPU.magBias[2];
  }
  // antes de leer cuartenion
  MPU.updateTime();

  MahonyQuaternionUpdate(MPU.ax, MPU.ay, MPU.az, MPU.gx * DEG_TO_RAD,
                         MPU.gy * DEG_TO_RAD, MPU.gz * DEG_TO_RAD, MPU.my,
                         MPU.mx, MPU.mz, MPU.deltat);

  MPU.yaw   = atan2(2.0f * (*(getQ()+1) * *(getQ()+2) + *getQ()* *(getQ()+3)),
                    *getQ() * *getQ() + *(getQ()+1) * *(getQ()+1) - *(getQ()+2)
                    * *(getQ()+2) - *(getQ()+3) * *(getQ()+3));

  MPU.pitch = -asin(2.0f * (*(getQ()+1) * *(getQ()+3) - *getQ()* *(getQ()+2)));

  MPU.roll  = atan2(2.0f * (*getQ() * *(getQ()+1) + *(getQ()+2)
                    * *(getQ()+3)), *getQ() * *getQ() - *(getQ()+1)
                    * *(getQ()+1) - *(getQ()+2) * *(getQ()+2) + *(getQ()+3)
                    * *(getQ()+3));

  MPU.pitch *= RAD_TO_DEG;
  MPU.yaw   *= RAD_TO_DEG;

  // Ajustado a la declinación de Cartago 2,6 °
  // - http://www.ngdc.noaa.gov/geomag-web/#declination
  // Pueden utilizar un celular para calibrar el valor. El 0 es el norte.
  MPU.yaw  += 6;
  MPU.roll *= RAD_TO_DEG;
}
