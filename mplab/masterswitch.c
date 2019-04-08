#include <xc.h>

#include "shutter.h"
#include "masterswitch.h"
#include "hardware.h"




unsigned char upState = 0;

unsigned char downState = 0;


unsigned int entprellCounter = 0;

void testeMasterTaster(void)  {

// switches inverse logik!

    if ( entprellCounter++ < 200)
        return;

   entprellCounter = 0;
   
   if ( upState == 0 && MASTERSWITCHPORT_UP == 0) {
      masterUpPressed(0);
      upState = 1;
   }


   if ( upState == 1 && MASTERSWITCHPORT_UP == 1)  {
      masterUpReleased(0);
      upState = 0;
   }

   if ( downState == 0 && MASTERSWITCHPORT_DOWN == 0) {
      masterDownPressed(0);
      downState = 1;
   }


   if ( downState == 1 && MASTERSWITCHPORT_DOWN == 1)  {
      masterDownReleased(0);
      downState = 0;
   }


}


