
#ifndef _KEY_H
#define _KEY_H



extern   uchar     *ptrchar;
extern   uint       *ptrint;
extern   uchar     *ramstart;

extern     uint       CeJianHao;               
extern     uint       ZeRenQu;                  
extern     uint       BanZuHao ;
extern    signed      char PVPT[];

extern     uint       ReportChannel;
/*

extern   uchar      KuaHao;
extern   uchar      PaiHao;
extern   uchar      JiaoHao;
*/
extern  uint      StuCount;
extern  uint      WorkTimeSecond;

extern  uchar      ConfigStu;
extern  uint       StandbyTime;
extern  uint       WorkTime;

extern  uint       MBAddr;
extern  uint       CommAddr;

extern  uchar     MenuStuNum;
extern  uchar     MenuStu;
extern  uchar     MenuStuNum;

extern  uchar     KeyChange;
extern  uint      Key30s;
extern  uint      KeySetData;
extern  uchar     KeySetLine;

extern  uchar     SetBit;
extern  uchar     SetDataBit[];
extern  uchar     IDSetFlag;

extern    uchar const    TZM0[];
extern    uchar const    CEJIANHAO1[];
extern    uchar const    ZERENQU2[];
extern    uchar const    BANZUHAO3[];
extern    uchar const    EXIT0[];
extern    uchar const    KUAHAO4[];
extern    uchar const    PAIHAO5[];
extern    uchar const    JIAOHAO6[];
extern    uchar const    CHANNEL7[];
extern    uchar const    POWER8[];
               

extern    uchar const    SAMPLETIME9[];
extern    uchar const    WORKTIME10[];
extern    uchar const    REPORTCHANNEL11[];

extern    uchar const    SAMPLETIME0[];
extern    uchar const    WORKTIME0[];

extern    uchar const    HFCCSZ[];
extern    uchar const    WLSZ[];
extern    uchar const    YBTX[];
extern    uchar const    EXIT[];
extern    uchar const    UPLAYER[];
extern    uchar const    MIDLAYER[];
extern    uchar const    DOWNLAYER[];
extern    uchar const    STAR[];
extern    uchar const    NOPCHAR[];
extern    uchar const     INPUT1[];
extern    uchar const    INPUT2[];
extern    uchar const    INPUT3[];
extern    uchar const    INPUTALL[];

extern    uchar const    INPUT00[];
extern    uchar const    INPUTFS[];
extern    uchar const    INPUT1ADJUST[];
extern    uchar const    INPUT2ADJUST[];
extern    uchar const    INPUT3ADJUST[];
extern    uchar const    INPUTADJUST[];

extern    uchar const    SLEEPTIME[];
extern    uchar const    WAKETIME[];









extern    uchar const    BAK1[];
extern    uchar const    RECOVER2[];

void           Key(uchar kv);
void     DataDiv(uchar mode,uint *datatemp);
void     DataBak(uchar *ramstart2);
void     DataRecover(uchar *ramstart2);
void     DataRecover888(uchar *ramstart2);

#endif