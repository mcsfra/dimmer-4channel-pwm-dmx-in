#include <xc.h>
#include "rs485.h"
#include "fifo.h"


/*
** Baudrate
** Datasheet Page 280
*/

#define MEGAHERTZ 1000000
#define FOSC (8 * MEGAHERTZ)


/*
** Sendet Bufferinhalt
*/



void initRS485(void)  {



    BAUDCONbits.BRG16 = 0;     // Baudratengenerator 8-Bit
    BAUDCONbits.CKTXP = 1;     // polaritaet verdrehen
//    TXSTA1bits.BRGH    = 0;     //
    SPBRG1             = 3;     // Baudrate einstellen
    SPBRGH            = 0;     //

    RCSTA1bits.CREN = 1;

    RCSTA1bits.SPEN = 1;

    PIE1bits.RCIE = 1;
    IPR1bits.RCIP = 1;


}


void sendRS485(void)  {

   // wenn der fifo etwas enthält UND das senderegister leer ist
   // ein byte entnehmen und senden

   if ( !fifoEmpty() && PIR1bits.TX1IF == 1)  {
       TXREG1 = fifoGet();
   }
}


void sendSwitchOn(unsigned char device, unsigned char switchNumber)  {

   unsigned char command = 0xF1;
   unsigned char payload =  (device << 4) || (switchNumber & 0x0F);
   unsigned char checksum = command ^ payload;

   // hier muss ich noch prüfen, ob der Fifo genug platz hat. wenn nicht, sende ich halt nicht.


   fifoPut( command  ); 
   fifoPut( payload  );
   fifoPut( checksum );

}



