#include <xc.h>         /* XC8 General Include File */
//#include <stdint.h>         /* For uint8_t definition */
//#include <stdbool.h>        /* For true/false definition */

#include "dmx.h"
#include "pwm.h"



/* 
** High-priority service
*/

void interrupt high_isr(void)  {
  
   /*
    * PWM Ausgabe
    */
   if ( INTCONbits.T0IF == 1)  {  
        INTCONbits.T0IF = 0;
        pwmStep();
   }
}



/*
** Low prio Interrupt
*/

void low_priority interrupt low_isr(void)  {

    /*
     * DMX- Eingangsdatenstrom
     */

    if (PIR1bits.RCIF == 1)  {
        handleDMX();
        PIR1bits.RCIF = 0;
    }

}