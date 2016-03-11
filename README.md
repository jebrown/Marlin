# Marlin 3D Printer Firmware For Delta Geeetech G2S G2S PRO RichCattel Branch
<img align="top" width=175 src="Documentation/Logo/g2spro.jpg" />
<img align="top" width=175 src="Documentation/Logo/Marlin%20Logo%20GitHub.png" />

## Specific version (slightly) modified for easy use on G2 G2S printer
__No garantee whatsoever – use with caution!__
 
 Compiled and tested on a G2S PRO. Last version of 07 march 2016.

This specific branch contains all the modifications made on the RC3 version of Marlin plus a port of the RichCattel version of Marlin with very  nice functionalities for auto calibration of Delta printers :
https://groups.google.com/forum/#!topic/deltabot/SrmxHMxdgBE[1-25]

As the G30 code was already taken in marlin (by a one shot z-probe test), I have given to the auto calibration the code G40.

"G40" works nicely with a test of height with Zprobe in 7 points

"G40 A"  which should make the entire calibration 

Two new parameters have been added to G40 :
I : maximum number of iteration (by default 100)
P : target precision (by default 0.03 mm)

 
This firmware supports M665 A B C (but it is not to modify tower angles as original RichCattel version but diagonal rod length).
To support all parameters of auto calibration I have added to M665 D E F parameters to adjust tower angle and I J K to adjust tower radius.

NONE OF THESE PARAMETERS ARE SAVED IN EEPROM, THEY SHOUD BE REENTERED AT EACH BOOT OR PUTIN THE SOURCE CODE :
in configuration.h :

  // Diagonal rod length adjustment
  // parameters maybe change by gcode M665 A B C
    - #define DELTA_DIAGONAL_ROD_TRIM_TOWER_1 0.0
    - #define DELTA_DIAGONAL_ROD_TRIM_TOWER_2 0.0
    - #define DELTA_DIAGONAL_ROD_TRIM_TOWER_3 0.0
 
  // Diagonal radius length adjustment
  // parameters maybe change by gcode M665 D E F (specific)
    - #define DELTA_RADIUS_TRIM_TOWER_1 0.0
    - #define DELTA_RADIUS_TRIM_TOWER_2 0.0
    - #define DELTA_RADIUS_TRIM_TOWER_3 0.0
    
  // Diagonal angle length adjustment
  // parameters maybe change by gcode M665 I J K (specific)
    - #define DELTA_ANGLE_TRIM_TOWER_1 0.0
    - #define DELTA_ANGLE_TRIM_TOWER_2 0.0
    - #define DELTA_ANGLE_TRIM_TOWER_3 0.0
   ?

Main modification merged from the main branch :

- modifications on pins_ULTIMAKER.h 

- add Geeetech thermistor table as 14 in thermistortables.h

- Modfication of DEFAULT_STEPPER_DEACTIVE_TIME SD_FINISHED_STEPPERRELEASE SD_FINISHED_RELEASECOMMAND in Configuration_adv.h

- - add DELTA_DIAGONAL_ROD_TRIM_TOWER_X in Configuration.h

- modify M401 and M402 in marlin_main.cpp to be blocking for use in gcode scripts (not a bug but usefull)

- modify gcode_G29() in marlin_main.cpp (not a bug) to avoid unpredictable behavior if z_probe is not deployed. (If the probe should not deployed correctly between probes there may be yet some unpredictable behavior)

- modify gcode_T() in marlin_main.cpp to supress a bug in use of G29 AND two extruders

- modify default_version.h to change build name to "1.1.0-RC3 mod G2S"

- modification on DELTA_CALIBRATION_MENU : add submenu for the choice of final height, modify command for low speed on final move

- add of LEDSTRIP support with Fastled library, modification of M150 GCODE, add of a specific LCD menu

- correction of M503 for M665 parameters

 Further description may be found on the [forum](http://3dprinters.proboards.com/board/3/geeetech-g2-g2s-pro).

 
 Additional documentation on Marlin can be found in [the  wiki](https://github.com/MarlinFirmware/Marlin/wiki/Main-Page).

## Release Candidate -- Marlin 1.1.0-RC3 - 01 December 2015

__Not for production use – use with caution!__

Previously tagged versions of Marlin are not recommended. However, the latest patches to the Marlin 1.0 series can be found in the [1.0.x](https://github.com/MarlinFirmware/Marlin/tree/1.0.x) branch.

[This branch, "RC"](https://github.com/MarlinFirmware/Marlin/tree/RC), is our current pre-release candidate.

Future development takes place in the [MarlinDev repository](https://github.com/MarlinFirmware/MarlinDev/).

## Recent Changes
RC3 - 01 Dec 2015
      A number of language sensitive strings have been revised
      Formatting of the LCD display has been improved to handle negative coordinates better
      Various compiler-related issues have been corrected

RC2 - 29 Sep 2015
      File styling reverted
      LCD update frequency reduced

RC1 - 19 Sep 2015
      Published for testing

## Submitting Patches
Proposed patches should be submitted as a Pull Request against the [RCBugFix](https://github.com/MarlinFirmware/Marlin/tree/RCBugFix) branch
Note: Do not propose added features. Patches to the Release Candidate are limited to corrections of coding errors for the functions that have been implemented.
Please follow the proper style. Pull requests containing styling errors will have to be reworked.



## Current Status: Testing

Please test this firmware and inform us of any issues where it fails to perform in a manner consistent with the designed functionality.

[![Coverity Scan Build Status](https://scan.coverity.com/projects/2224/badge.svg)](https://scan.coverity.com/projects/2224)
[![Travis Build Status](https://travis-ci.org/MarlinFirmware/MarlinDev.svg)](https://travis-ci.org/MarlinFirmware/MarlinDev)

##### [RepRap.org Wiki Page](http://reprap.org/wiki/Marlin)

## Contact

__Google Hangout:__ <a href="https://plus.google.com/hangouts/_/gxn3wrea5gdhoo223yimsiforia" target="_blank">. Hangout</a> We have a hangout every 2 weeks. Search the issue list for "Hangout" and you will see what time and date the next event is going on.

## Credits

The current Marlin dev team consists of:

 - Andreas Hardtung [@AnHardt] - Deutsch, English
 - Scott Lahteine [@thinkyhead] - English
 - [@Wurstnase] - Deutsch, English
 - F. Malpartida [@fmalpartida] - English, Spanish
 - [@CONSULitAS] - Deutsch, English
 - [@maverikou]
 - Chris Palmer [@nophead]
 - [@paclema]
 - Edward Patel [@epatel] - Swedish, English
 - Erik van der Zalm [@ErikZalm]
 - David Braam [@daid]
 - Bernhard Kubicek [@bkubicek]
 - Richard Wackerbarth [@Wackerbarth] - English
 - Roxanne Neufeld [@Roxy-3DPrintBoard] - English

More features have been added by:
  - Alberto Cotronei [@MagoKimbra]
  - Lampmaker,
  - Bradley Feldman,
  - and others...

## License

Marlin is published under the [GPL license](/LICENSE) because we believe in open development. The GPL comes with both rights and obligations. Whether you use Marlin firmware as the driver for your open or closed-source product, you must keep Marlin open, and you must provide your compatible Marlin source code to end users upon request. The most straightforward way to comply with the Marlin license is to make a fork of Marlin on Github, perform your modifications, and direct users to your modified fork.

While we can't prevent the use of this code in products (3D printers, CNC, etc.) that are closed source or crippled by a patent, we would prefer that you choose another firmware or, better yet, make your own.

[![Flattr this git repo](http://api.flattr.com/button/flattr-badge-large.png)](https://flattr.com/submit/auto?user_id=ErikZalm&url=https://github.com/MarlinFirmware/Marlin&title=Marlin&language=&tags=github&category=software)
