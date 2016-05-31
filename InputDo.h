#ifndef  _INPUTD0_H
#define  _INPUTD0_H

extern  uint      CAPTURE_ADD; //捕捉的值的总和
 
extern  uchar     CAPTURE_CNT; //捕捉的次数
extern  uchar     CAPTURE_NOP;

extern  uint      SAMP[];
extern  uchar     InputSampleOver;
extern  uchar     DataOverflow[];
extern  uchar     InputChannel;



     


 

void InputDo(void);

#endif

