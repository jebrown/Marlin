  /*
  i2c_extension.cpp
  Library header file for addon library
 */

#include "marlin.h"


#if ENABLED(I2CTEMP_SENSOR)

#include "i2c_extension.h"

#include <Wire.h>

#include <Adafruit_TMP007.h>

#if ENABLED(I2CTEMP_SENSOR_ADDRESS)
  Adafruit_TMP007 tmp007(I2CTEMP_SENSOR_ADDRESS);
#else
  Adafruit_TMP007 tmp007;
#endif

  boolean hasbegan = false;
  byte    previous_twcr =0;

  void resume_I2C(){
    // verify LCD_PINS_ENABLE ==0 not to interfere with LCD ?
   #if ENABLED(ULTRA_LCD) 
     digitalWrite(LCD_PINS_ENABLE, LOW);
     //very experimental TWI end
     if (previous_twcr !=0)
      TWCR=previous_twcr;
   #endif
  }

void suspend_I2C(){
   #if ENABLED(ULTRA_LCD) // put back the SCL AND SCA pin to output
      //SERIAL_ECHOPAIR("TWCR : ", TWCR);
      //SERIAL_ECHOPAIR(" TWCR i : ", _BV(TWEN) | _BV(TWIE) | _BV(TWEA));
      // release TWI hardware
      // reverse enable twi module, acks, and twi interrupt
      //     TWCR = _BV(TWEN) | _BV(TWIE) | _BV(TWEA);
      previous_twcr=TWCR;
      TWCR=0;
      #ifdef __AVR_ATmega2560__
          //  pin 20, 21 SDA, SCL for ATmega2560          
          // SERIAL_ECHOLN(" Put SDA SCL in out mode");
          pinMode(20,OUTPUT);
          pinMode(21,OUTPUT);
          digitalWrite(20, LOW);
          digitalWrite(21, LOW);
       #endif
    #endif
}



  float i2cReadTmp007(byte Ttype){
   float objtemp=NAN;

   resume_I2C();
   
   if (!hasbegan){
    hasbegan =  tmp007.begin();
   }
     if (hasbegan){
      switch(Ttype){
       case 1:
        objtemp = tmp007.readObjTempC();
        break;
       case 2:
        objtemp = tmp007.readDieTempC();
        break;
      }
      if (objtemp==NAN){
        hasbegan = false;
      } 
     }

     suspend_I2C();
   return objtemp;
  }

  float i2cReadTemp(){
      return i2cReadTmp007(1);
  }

  float i2cReadDie(){
       return i2cReadTmp007(1);
  }
 

  String i2cTempStatus(){
    return String( "I2C 0007 detect " + String(hasbegan)+ " LCDEn "+ String( LCD_PINS_ENABLE ) + " = " + String(digitalRead(LCD_PINS_ENABLE)));
  }
  
#endif

