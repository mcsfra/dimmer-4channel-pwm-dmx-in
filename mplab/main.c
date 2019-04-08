#include <xc.h>        /* XC8 General Include File */

//#include <stdint.h>        /* For uint8_t definition */
//#include <stdbool.h>       /* For true/false definition */

#include "hardware.h"

#include "pwm.h"
#include "dmx.h"
#include "SETUP.h"
#include "channels.h"


/*
 * Version 1.1 - Live November 2015
 * 
 */


volatile unsigned char lastInChainReceived = 0;

unsigned char counterForSimulator = 0;


/*
 *
 */


unsigned char errorCounter = 0;


extern unsigned char channelLevel[MAXCHANNELS];

void main(void)
{

 

  

    initHardware();
    initPwm();
    initChannels();
    initDMX();


    RCONbits.IPEN = 1;

// wiedeer reinnehmen wenn tests rum!
    INTCONbits.GIEH = 1;
 //   INTCONbits.GIEL = 1; Brauch ich nicht.



/*
    channelLevel[0] = 0;
    channelLevel[1] = 0;
    channelLevel[2] = 0;
    channelLevel[3] = 0;

    doRank();
    calculateTimerDiffsAndMask();

    channelLevel[0] = 2;
    channelLevel[1] = 0;
    channelLevel[2] = 0;
    channelLevel[3] = 0;

    doRank();
    calculateTimerDiffsAndMask();

    doRank();
    calculateTimerDiffsAndMask();

    for(;;)
       ;
  */

   


   

    for (;;)  {

/* Das funktionierte zwar so nicht, es hat sich aber gezeigt, dass das flackern weg ist. --> Interrupt schneller machen
      if (PIR1bits.RCIF == 1)  {
          handleDMX();
          PIR1bits.RCIF = 0;
      }
*/

        if (OERR == 1)  {
           
          //  setDMXNotSynced();
            errorCounter++;
             SPEN = 0;
             RCIE = 0;
             initDMX();
        }



        if (lastInChainReceived /*|| counterForSimulator++ == 100 */)  {
            doRank();
            calculateTimerDiffsAndMask();
            lastInChainReceived = 0;
        }
    }


}
