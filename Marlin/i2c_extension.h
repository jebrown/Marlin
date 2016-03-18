/*
  i2c_extension.h
  Library header file for addon library
 */


#if ENABLED(I2CTEMP_SENSOR)

  
  float i2cReadTemp();

  float i2cReadDie();

  String i2cTempStatus();
  
#endif

