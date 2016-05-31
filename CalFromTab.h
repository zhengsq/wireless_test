#ifndef _CAL_FROM_TAB_H
#define _CAL_FROM_TAB_H

 

extern  uchar     DataOverflow[];
extern  uint      In1OldCal,In2OldCal,In3OldCal;
extern  uint         SAMP[3];
extern  uchar     MenuStuNum;
// extern   uint      In1Cal00;
 //extern   uint      In1CalFS;
//extern  uint      In2Cal00;
//extern  uint      In2CalFS;
//extern  uint      In3Cal00;
//extern  uint      In3CalFS;

signed int   CalFromTab(uchar input_ch,uint *incal00,uint *incalfs);
signed long  SearchTab(signed int p00,uchar *overflow00);

#endif