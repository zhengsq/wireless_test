#ifndef  _INPUTD0_H
#define  _INPUTD0_H

extern  uint      CAPTURE_ADD; //��׽��ֵ���ܺ�
 
extern  uchar     CAPTURE_CNT; //��׽�Ĵ���
extern  uchar     CAPTURE_NOP;

extern  uint      SAMP[];
extern  uchar     InputSampleOver;
extern  uchar     DataOverflow[];
extern  uchar     InputChannel;



     


 

void InputDo(void);

#endif

