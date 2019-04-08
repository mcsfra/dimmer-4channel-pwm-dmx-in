#include <xc.h>
#include "pwm.h"
#include "SETUP.h"
#include "channels.h"

/*
 * Version 1.0
 */

//#define MAXCHANNELS 4

extern CHANNELINFO *pCIRead;


void pwmStepA(void);
void pwmStepB(void);


void initPwm(void)  {

    unsigned  char i;

    INTCONbits.TMR0IF = 0;

    T0CON              = 0b10000001;

    INTCON2bits.TMR0IP = 1;   // Timer 0 Interrupt Priority : HIGH
    INTCONbits.TMR0IE  = 1;   // Timer 0 Interupt Enable

    INTCONbits.GIEH    = 1;  // High Prio Interupts enable
    INTCONbits.GIEL    = 1;  // Low Prio Interupts enable

    INTCONbits.PEIE    = 1;  // Peripherals Interupts Enable
}


/*
 * Variablen Global allokiert; schnellerer Zugriff möglich
 */

unsigned char intCount = 0;
unsigned int  tTmp;

volatile unsigned char dummy1;


#ifndef INVERT_MODE

void pwmStep(void)  {

    tTmp = pCIRead -> timer[intCount]; 

    TMR0H = ((tTmp >> 8) & 0xFF);
    TMR0L = (tTmp & 0xFF);

    if (intCount == 0)  {
      //  swapBuffers();
        PORTC = pCIRead -> bitmask[intCount];
    }
    else  {
        PORTC &= ~(pCIRead -> bitmask[intCount]);
    }

    if (intCount >= pCIRead -> numInts )  {

        swapBuffers();
        intCount = 0;

    }
    else  {

      intCount++;
    }
}
#else
void pwmStep(void)  {

    tTmp = pCIRead -> timer[intCount]; 

    TMR0H = ((tTmp >> 8) & 0xFF);
    TMR0L = (tTmp & 0xFF);

    if (intCount == 0)  {
      //  swapBuffers();
        PORTC = ~pCIRead -> bitmask[intCount];
    }
    else  {
        PORTC |= (pCIRead -> bitmask[intCount]);
    }

    if (intCount >= pCIRead -> numInts )  {

        swapBuffers();
        intCount = 0;

    }
    else  {

      intCount++;
    }
}

#endif

/*
 ** Pointerarithmetik vermeiden; schneller werden
 ** Es zeigt sich, dass dennoch nix gespart wird.

 */

extern CHANNELINFO ci1;
extern CHANNELINFO ci2;




