#ifndef _COLOR_LED_H_
#define _COLOR_LED_H_
int pwmActiveAll(void);
int pwmInactiveAll(void);
int pwmSetDuty(int dutyCycle, int pwmIndex);
int pwmSetPeriod(int Period, int pwmIndex);
int pwmSetPercent(int percent, int ledColor);
int pwmStartAll(void);
int pwmLedInit(void);
int colorled_on(void);
int colorled_off(void);
int colorled_off(void);
int colorled_OnOff(void)
#endif
