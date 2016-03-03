/*
  ledstrip.cpp - Library for controlling leds over a wire
  Created by Philippe Hervier Feb 2016.
*/
#include "Marlin.h"

#if ENABLED(LEDSTRIP)

#include "ledstrip.h"
#include <FastLED.h>


CRGB leds[LEDSTRIP_NLED];
CRGB colorSaved[LEDSTRIP_NSEGMENT+1];

boolean initialized = false;

#if ENABLED(LEDSTRIP_EXCHANGE_RV)
byte SendColorsOnLedstrip (int grn, int red, int blu,byte segment, byte power) {
#else
byte SendColorsOnLedstrip (int red, int grn, int blu,byte segment, byte power) {
#endif
   #if ! defined(LEDSTRIP_PIN)
    return LEDSTRIP_NOLEDSPIN;
   #endif
   #if ! defined(LEDSTRIP_NLED)
    return LEDSTRIP_NONLEDS;
   #endif
   #if ! defined(LEDSTRIP_NSEGMENT)
    #define LEDSTRIP_NSEGMENT 1
   #endif
   if (segment > LEDSTRIP_NSEGMENT || segment < 0)
     return  LEDSTRIP_BADSEGMENT;

   
   if (!initialized){
    //memset8( leds, 0, LEDSTRIP_NLED * sizeof(CRGB));
    FastLED.addLeds<LEDSTRIP_TYPE, LEDSTRIP_PIN, RGB>(leds, LEDSTRIP_NLED);
    FastLED.clear();
    colorSaved[0]=CRGB::Linen;
    for (int i=1;i<=LEDSTRIP_NSEGMENT;i++)
      colorSaved[i]=CRGB::Seashell;
    
    initialized = true;
   }

   // update saved color 
     if (red>=0)
       colorSaved[segment].red  = red;
     if (grn>=0)
       colorSaved[segment].green= grn;
     if (blu>=0)
       colorSaved[segment].blue = blu;
   
   byte updtend = (segment>0) ? LEDSTRIP_NLED/LEDSTRIP_NSEGMENT : LEDSTRIP_NLED ;
   byte updshift = (segment>0) ? (segment-1) : 0;
   byte j;

   if (red+grn+blu<=3){  // no color change use the saved color or black
     if (power==LED_POWERON){
      for(byte i = 0; i < updtend; i++) 
       leds[i+(updshift*updtend)]=colorSaved[segment];
     } else if (power==LED_POWEROFF){
      for(byte i = 0; i < updtend; i++) 
       leds[i+(updshift*updtend)]=CRGB::Black;

     } else if (power==LED_POWERHALF){
      for(byte i = 0; i < updtend; i++) 
       leds[i+(updshift*updtend)]=(i%2)? colorSaved[segment]:CRGB::Black;
     } else
       return LEDSTRIP_NOACTION;
   } else {
     for(byte i = 0; i < updtend; i++) { 
      j=i+(updshift*updtend);
       if (red>=0)
         leds[j].red  = red;
       if (grn>=0)
         leds[j].green= grn;
       if (blu>=0)
         leds[j].blue = blu;
     }
   }
   FastLED.show();

   return LEDSTRIP_OK;

}

#endif //LEDSTRIP

