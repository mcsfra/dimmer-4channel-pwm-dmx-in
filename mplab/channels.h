/* 
 * File:   channels.h
 * Author: marcus
 *
 * Created on 10. September 2014, 21:02
 */

#ifndef CHANNELS_H
#define	CHANNELS_H



typedef struct channelinfo  {
    unsigned char numInts;
    unsigned int  timer[MAXCHANNELS + 1];
    unsigned char bitmask[MAXCHANNELS + 1];
} CHANNELINFO;


extern void initChannels(void);

extern void setChannelValue(unsigned char channel, unsigned char value);

extern unsigned char getChannelValue(unsigned char channel);

extern void doRank(void);
extern void calculateTimerDiffsAndMask(void);

extern inline void swapBuffers(void);

#endif	/* CHANNELS_H */

