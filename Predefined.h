#ifndef _DEFINE_ALL_H
#define _DEFINE_ALL_H


#define  uchar  unsigned char
#define  uint   unsigned int

#define  Ready         0x5A
#define  ChangeCH      0xAA
#define  On            0x55
#define  Off           0x11
#define  Bakuped       0xA9


#define  Active       1
#define  PowerOff     2
#define  Standby      3

/*************************无线模块相关***********************************/
#define  MBSleep         (P6OUT&=~BIT3)
#define  MBWake          (P6OUT|=BIT3)



/***********************LCD***************************************************/
#define  Point0          0
#define  Point1          1
#define  Point2          2
#define  Point3          3 


#define  Line1           1
#define  Line2           3
#define  Line3           5
#define  Line4           7


#define  ADPowerOn          P2OUT&=~BIT4
#define  ADPowerOff         P2OUT|=BIT4

#define  LedAOn          P4OUT&=~BIT5   //LCD
#define  LedAOff         P4OUT|=BIT5    

#define  LedStuOn        P3OUT&=~BIT0   //LED状态指示灯
#define  LedStuOff       P3OUT|=BIT0

#define  LcdRead         P4OUT&=~BIT4;P4OUT|=BIT3
#define  LcdWrite        P4OUT|=BIT4;P4OUT&=~BIT3
#define  LcdNRW          P4OUT|=BIT4;P4OUT|=BIT3

#define  LcdData         P4OUT|=BIT2
#define  LcdCommand      P4OUT&=~BIT2

#define  SetLcdCS        P4OUT|=BIT1
#define  ClrLcdCS        P4OUT&=~BIT1

#define  LcdResetOff     P4OUT|=BIT0
#define  LcdResetON      P4OUT&=~BIT0
#define  IOPortIn        P5DIR=0X00
#define  IOPortOut       P5DIR=0Xff

/******************************************************************************/




/***********************************************
按键值定义
************************************************/
#define  no_key        0x68
#define  key_up        0x48
#define  key_down      0x28
#define  set           0x60



#define  PWM_TIME        0x3000   //周期5MS
#define  PWMOUT          0x2000


#define  CPU_F ((double)2000000)
#define  delay_us(x)  __delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define  delay_ms(x)  __delay_cycles((long)(CPU_F*(double)x/1000.0))


#define   DigitalDspStart   72
#endif




