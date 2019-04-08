#include <xc.h>
#include "hardware.h"



void initHardware(void)  {

                       // 8MHz internal OscillatorBlock

  OSCCONbits.IDLEN = 0;

  OSCCONbits.IRCF2 = 1;
  OSCCONbits.IRCF1 = 1;
  OSCCONbits.IRCF0 = 0;

  OSCCONbits.SCS1  = 1;
  OSCCONbits.SCS0  = 0;

  /*
  ** I/O
  */

  CM1CON0  = 0;
  CM2CON0  = 0;
//  SSP1CON = 0;

  ANSEL   = 0x00;
  ANSELH  = 0x00;

  LATA    = 0x00;
  PORTA   = 0x00;
  TRISA   = TRISAMASK;              // 8 Mal Ausgang



 // CCP1CON = 0;                       // Comparators OFF
 // ADCON1  = 0x7F;
 // hat das bei diesem chip ne funktion???

  
  PORTB   = 0x00;
  LATB    = 0x00;
//  ANSELB  = 0x00;
  TRISB   = TRISBMASK;

  LATC    = 0x00;
  PORTC   = 0x00;
//  ANSELC  = 0x00;
  TRISC   = TRISCMASK;              


}
