#include <xc.h>
#include "dmx.h"
#include "pwm.h"
#include "SETUP.h"
#include "channels.h"
#include "SETUP.h"

/*
** Baudrate
** Datasheet Page 280
*/

#define MEGAHERTZ 1000000
#define FOSC (8 * MEGAHERTZ)




// Hinweis: beim inbetriebnehmen der Aussenlampen stelle ich fest,
// Dass der Dimmer nichts mehr gescheites macht wenn alle 4 Kanaele Voll an sind


unsigned char dmxState; 
unsigned int  currentAdress;

extern unsigned char lastInChainReceived;

extern unsigned char channelLevel[MAXCHANNELS];


void initDMX(void)  {



    BAUDCONbits.BRG16 = 1;     // Baudratengenerator 8-Bit
    BAUDCONbits.CKTXP = 1;     // polaritaet verdrehen
//    TXSTA1bits.BRGH    = 0;     //
    SPBRG1             = 1;     // Baudrate einstellen
    SPBRGH            = 0;     //

    RCSTA1bits.CREN = 1;

    RCSTA1bits.SPEN = 1;

    PIE1bits.RCIE = 1;
    IPR1bits.RCIP = 0;  // Low Priority


    currentAdress = 0;
 
    dmxState      = DMX_NOTSYNCED;

}

unsigned char errflag;
unsigned char received;

unsigned char dummy;

void handleDMX()  {

   /*
   ** error-flag holen ( muss vor dem lesen der eigentlichen date gemacht werden )
   */
   errflag = FERR;

  /*
   ** Das Empfangene Byte holen
   */
   received = RCREG;

   if ((errflag == 1) && ( dmxState == DMX_NOTSYNCED)  )  {
       currentAdress = 0;
       dmxState = DMX_WAITSTART;
       return;
   }

   if ( (dmxState == DMX_WAITSTART) && (received == 0x00))  {

      dmxState = DMX_PAYLOAD;
      return;
   }

   if ( dmxState == DMX_PAYLOAD)  {

      if (currentAdress >= BASEADDRESS &&  currentAdress < BASEADDRESS + MAXCHANNELS)  {
        
          if ( channelLevel[currentAdress-BASEADDRESS] == 0 && received != 0)  {

              dummy = LATA;  // zum Setzen des Breakdowns

          }
#ifdef RELAISMODE
          channelLevel[currentAdress-BASEADDRESS] = (received < 64 ? 0xFA : 0x00);
#else
          channelLevel[currentAdress-BASEADDRESS] = received;
#endif
    // An Interruptüberholern scheint das blitzen am anfang nicht zu liegen. 
    // sowohl die frequenzverringerung als auch die diskriminierung des niedrigen bereichs
    // bringt Nüscht
    //
    // Doch hein Issue in der Datenaufbereitung?
      }


      if (currentAdress ==  BASEADDRESS + MAXCHANNELS)
         lastInChainReceived = 1;

      currentAdress++;

      if ( currentAdress >= 128)
         dmxState = DMX_NOTSYNCED;

   }
}

