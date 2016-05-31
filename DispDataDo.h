#ifndef _DSPDATA_DO_H
#define _DSPDATA_DO_H


extern     uchar   DataOverflow[];
extern     uchar  MenuStu;
extern     signed    int   PV[];
extern     const   uchar  CSSZ[];
extern     const   uchar  WDTX[];
extern     const   uchar  BAKANDRECOVER[];
extern     const   uchar  EXIT0[];

extern     const  uchar   UNITANDKUAHAO[];
extern     const  uchar   UNITANDPAIHAO[];
extern     const  uchar   UNITANDJIAOHAO[];

extern     const  uchar  BATSTU3[];
extern     const  uchar  WXXH[];
extern     const  uchar  STAR[];
extern     const  uchar  BROK[];
extern     const  uchar  HOVL[];
extern     const  uchar  LOVL[];

extern     uint       StandbyTime;

extern     uint       CeJianHao;               
extern     uint       ZeRenQu;                  
extern     uint       BanZuHao ;                 
extern     uint       KuaHao;
extern     uint       PaiHao;
extern     uint       JiaoHao;
extern     uint      MBPower ;                    
extern     uint      MBChannel;                 

void   DigitalRefresh(uchar point,uchar page,signed int datax,uchar sta);
void   MenuDisp(void);
void   NormalDisp(void);
void   SetDataDisp(uchar line,signed int  datax,uchar datanum);
#endif