/* 
 * File:   rs485.h
 * Author: marcus
 *
 * Created on 31. Juli 2014, 21:33
 */

#ifndef __DMX_H__
#define	__DMX_H__

#define DMX_NOTSYNCED 0x00
#define DMX_WAITSTART 0x01
#define DMX_PAYLOAD	  0x02


extern void initDMX(void);

extern void handleDMX(void);

extern void setDMXNotSynced(void);





#endif	/* RS485_H */

