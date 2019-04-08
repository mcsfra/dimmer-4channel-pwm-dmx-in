/* 
 * File:   hardware.h
 * Author: marcus
 *
 * Created on 23. March 2014, 19:02
 */

#ifndef __HARDWARE_H__
#define	__HARDWARE_H__


/*
 *    SPI kommunikation mit meinem "grossen" master
 */






#define TRISAMASK   0b00000111


#define TRISBMASK   0b00100111
#define TRISCMASK   0b00000000



extern void initHardware(void);

// extern void sleep(void);



#endif	/* HARDWARE_H */

