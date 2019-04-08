#include <xc.h>
#include "SETUP.h"
#include "channels.h"

/*
 * Version 1.0 Septtember 2014
 * Dimmen funktioniert, allerdings mit Flicker
 */


/*
** Die Kanalwerte
*/
unsigned char channelLevel[MAXCHANNELS];

static unsigned char channelRank[MAXCHANNELS];

/*
unsigned int  timer[2][MAXCHANNELS + 1];
unsigned char bitmasks[2][MAXCHANNELS + 1];
unsigned int  numInts[2]; 
*/

unsigned char readIndex  = 0;
unsigned char writeIndex = 1;

CHANNELINFO ci1;
CHANNELINFO ci2;

CHANNELINFO *pCIRead;
CHANNELINFO *pCIWrite;
CHANNELINFO *pCITmp;

/*
** Klar: Bringt das Ganze in einen definierten Anfangszustand
*/

void initChannels()  {
    
    unsigned char i; 
    
    for (i = 0; i < MAXCHANNELS; i++)  {
        channelLevel[i] = 10;
    }

    pCIRead  = &ci1;
    pCIWrite = &ci2;

    pCIRead  -> numInts = MAXCHANNELS;
    pCIWrite -> numInts = MAXCHANNELS;

}

/*
** Tauscht die Puffer
*/

volatile unsigned char syncLock = 0;
volatile unsigned char updated  = 0;


/*
**
*/

unsigned int swapCount = 0;

inline void swapBuffers()  {


    if (syncLock == 1 || updated == 0)
        return;

    updated = 0; 

    swapCount++; 

    pCITmp   = pCIRead; 
    pCIRead  = pCIWrite; 
    pCIWrite = pCITmp;

}








/*
** Ranking berechnen
*/

void doRank(void )   {

   unsigned char i, j;

   for ( i = 0; i < MAXCHANNELS; i++)
       channelRank[i] = 0;				// iteration 4 rank aud j wird sonst überschrieben.

   for ( i = 0; i < MAXCHANNELS-1; i++)  {

      for ( j = i + 1; j < MAXCHANNELS;j++)  {

          if (channelLevel[i] > channelLevel[j])     
            channelRank[i]++;
          else
            channelRank[j]++;  // iteration 3: rank mus auf beiden seiten erhöht werden.
      }
   }
}


/*
** Berechnet  die Timerabstände basierend auf den sortieren kanalhelligkeiten
*/


/*
 * Wenn ich eine pwmauflösungsverbesserung haben möchte ist das der richtige ort. (23.03.2015)
 */

#define PWMSTEP   16
#define PELOAD100HZ 0xF63C


void calculateTimerDiffsAndMask()  {

   unsigned char i;
   unsigned char i2;
   unsigned int sumTimers;

   unsigned char pivot[MAXCHANNELS];

   for (i = 0; i < MAXCHANNELS; i++)  {
      pivot[channelRank[i]] = i;
   }
   

   syncLock = 1;   // Sperre, ab jetzt wird das schattenregister aufgebaut.

   pCIWrite -> numInts = MAXCHANNELS;

   /*
   ** Nur kanaele einschalten, die auch einen lichtwert haben
   */

   pCIWrite -> bitmask[0] = 0x00;
   for ( i = 0; i < MAXCHANNELS; i++)  {
       if (  channelLevel[i] > 0)
          pCIWrite -> bitmask[0] |= (1 << i);    // einschaltvektor
       else  {
          pCIWrite -> numInts--;                 // kanal 0, also weniger interrupts nötig
       }
   }

   /*
   ** Berechnen der Zeitintervalle
   */

   i2 = 0;
   for ( i = 0; i < MAXCHANNELS; i++)  {

       if ( channelLevel[pivot[i]] == 0)  {
            continue;
       }

       if ( i == 0 )  {
          pCIWrite -> timer[i2] = channelLevel[pivot[i]] * PWMSTEP;
       }
       else  {
          pCIWrite -> timer[i2] = (channelLevel[pivot[i]] - channelLevel[pivot[i-1]]) * PWMSTEP;
       }

       pCIWrite -> bitmask[i2+1] = (1 << pivot[i]);

       /*
       ** Behandlen gleicher kanalwerte
       */

       while ((i < (MAXCHANNELS - 1)) && (channelLevel[pivot[i]] == channelLevel[pivot[i+1]] ) )  {
             pCIWrite -> bitmask[i2+1] |= (1 << pivot[i+1]);
             i++;
             pCIWrite -> numInts--;
       }

       i2++;
   }

   /*
   ** "Auffüllen"
   */

   sumTimers = 0;
   for ( i = 0; i < i2; i++)  {
      sumTimers += pCIWrite -> timer[i];
   }

   pCIWrite -> timer[i2] = (0x00ff * PWMSTEP) - sumTimers;

   for ( i = 0; i < MAXCHANNELS + 1; i++)  {
       pCIWrite -> timer[i] = 0xFFFF - pCIWrite -> timer[i];
   }

   syncLock = 0;
   updated  = 1;
}


