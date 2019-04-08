/* 
 * File:   pwm.h
 * Author: marcus
 *
 * Created on 10. September 2014, 19:48
 */

#ifndef PWM_H
#define	PWM_H

extern void initPwm(void);
extern void handlePwm(void);
extern void pwmStep(void);

extern unsigned char channelValue[];

extern void pwmOn(unsigned char bitmask);
extern void pwmOff(unsigned char bitmask);



#endif	/* PWM_H */

