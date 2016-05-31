
#ifndef _COMM_DO_H
#define _COMM_DO_H


extern     signed    int       PV[];
extern    signed      char PVPT[];


extern     uchar     CommSent[];
extern     uchar     WBStu;
extern     uchar     BatStu;
extern     uchar     ConfigStu;
extern     uchar     IDSetFlag;
extern     uchar     SentNum;
extern     uchar     SentOrNot; 
extern     uint      StuCount;
extern     uchar     AutoSentFlag;
extern     uchar     SendTimes;
extern     uchar     AutoSendForHander;
extern     uchar     TimeForSentFlag;
extern     uchar     ConfigFlag;
extern     uchar     ReportFlag;
extern     uchar     RecoverFlag;
extern     uchar     DataRefreshFlag;
extern     uchar     RefreshAfterRead;
extern     uint      ReadIDCount;
extern     uchar     MBDataReadFlag;

//extern     uint      TestData;

void  CommSentData(uchar *rxdata,uchar *txdata,uchar *ramppt);

void  CommNormalData(uchar *txdata,uchar *ramppt);

void  ConfigDataWrite(uchar *txdata,uchar *ramppt);

void  ConfigDataRead(uchar *txdata);




uint  CrcCheck(uchar len,uchar *ptr);



#endif