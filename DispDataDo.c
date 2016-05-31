
#include <io430.h>
#include <in430.h>
#include "Predefined.h"
//#include "DefineSPC.h"
#include "DispDataDo.h"
#include"LcdDriver.h"






  
 
  
  




  
 
  



void ThreeByteRefresh(uchar col,uchar num,uchar (*lcdptr)[112],uchar *dataptr)
{
  uchar i,j;
  
for(j=0;j<num;j++)
{
  
     for(i=0;i<24;i++)
      {
      lcdptr[0][col+i+j*48]=dataptr[i+j*48]; 
      lcdptr[1][col+i+j*48]=dataptr[i+24+j*48];
      }
  
} 
  
 
  
  
}

void   SetDataDisp(uchar line,signed int  datax,uchar datanum)
 {
   uchar  k2,col1,page1;
   
   page1=line;
   col1=72;
   
   k2=datax/1000;
   if(datanum<4)
    {
    LcdOneByteWrite(col1,page1,46,0); 
    }
   else
    {
   LcdOneByteWrite(col1,page1,k2,0); 
    }
   col1=col1+8;
   k2=datax/100 %10;
   if(datanum<3)
    {
    LcdOneByteWrite(col1,page1,46,0);
    }
   else
    {
    LcdOneByteWrite(col1,page1,k2,0);
    }
   col1=col1+8;
   k2=datax/10 %10;
   LcdOneByteWrite(col1,page1,k2,0);
   col1=col1+8;
   k2=datax%10;         //个位
   LcdOneByteWrite(col1,page1,k2,0);
   
   
 }

void   DigitalRefresh(uchar point,uchar channel,signed int datax,uchar sta)

{
  uchar  k1,col2,page2;
  
  switch(channel)
   {
     case 1:
          page2=Line3;
     break;
     case 2:
          page2=Line2;
     break;
          
     case 3:
          page2=Line1;
     break;
   }
  
 /* 
  LcdOneByteWrite((-8),page2,46,0);
  LcdOneByteWrite(0,page2,46,0);
  LcdOneByteWrite(8,page2,46,0);
  LcdOneByteWrite(16,page2,46,0);
  LcdOneByteWrite(24,page2,46,0);
  LcdOneByteWrite(32,page2,46,0);
  LcdOneByteWrite(40,page2,46,0);
  */
                                   //清数字显示区
  
  col2=0;                        //起始列
 
  
 switch(sta)
  {
 case 1:
          LcdOneByteWrite((-8),page2,46,0);
          LcdOneByteWrite(0,page2,46,0);
          LcdTwoByteWrite(8,page2,2 ,BROK);
 break;
 case 2:
          LcdOneByteWrite((-8),page2,46,0);
          LcdOneByteWrite(0,page2,46,0);
          LcdTwoByteWrite(8,page2,2 ,HOVL);
 break;
 case 3:
          LcdOneByteWrite((-8),page2,46,0);
          LcdOneByteWrite(0,page2,46,0);
          LcdTwoByteWrite(8,page2,2 ,LOVL);
 break;    
 default:
 
  if(datax <0)
  {
   LcdOneByteWrite((-8),page2,11,0);//'-'
   //col2=col2+8;
   datax=-datax;
  }
  else
  {
   LcdOneByteWrite((-8),page2,46,0); 
  }
  
  k1=datax/1000;
  
  if(k1!=0)
  {
   LcdOneByteWrite(col2,page2,k1,0); 
   
  }
  else
  {
    if(point==3)
    {
   LcdOneByteWrite(col2,page2,0,0);
   
    }
    else
    {
   LcdOneByteWrite(col2,page2,46,0);  
    }
  }
  col2=col2+8;
  
  if(point==3)
  {
   LcdOneByteWrite(col2,page2,18,0); //小数点
   col2=col2+8;
  }
  
  k1=datax/100 %10;
  if(k1!=0)
  {
   LcdOneByteWrite(col2,page2,k1,0); 
   
  }
  else
  {
    if((point >= 2)||(datax > 999))
    {
      LcdOneByteWrite(col2,page2,0,0);
      
    }
    else
    {
      LcdOneByteWrite(col2,page2,46,0);
    }
  }
  col2=col2+8;
  
  if(point==2)
   {

   LcdOneByteWrite(col2,page2,18,0); //小数点
   col2=col2+8;
   }
  
  k1=datax/10 %10;
  LcdOneByteWrite(col2,page2,k1,0);
  col2=col2+8;
  
  if(point==1)
  {
   LcdOneByteWrite(col2,page2,18,0); //小数点
   col2=col2+8;
  }
  k1=datax%10;         //个位
  LcdOneByteWrite(col2,page2,k1,0);
  


  }
  
}



void MenuDisp(void)
{
                                           ClearLcdLine(Line1);
                                           ClearLcdLine(Line2);
                                           ClearLcdLine(Line3);
                                           ClearLcdLine(Line4);
                                           
                                           LcdTwoByteWrite(20,Line4,4 ,CSSZ);//参数设置
                                           LcdTwoByteWrite(20,Line3,4 ,WDTX);//温度调校
                                           LcdTwoByteWrite(20,Line2,5 ,BAKANDRECOVER);//备份与恢复
                                           LcdTwoByteWrite(20,Line1,5 ,EXIT0);//退 出
                                           
                                           
                                           
                                           
                                           
}

void NormalDisp(void)
{
  
  uchar kkk;
                                           
                                           ClearLcdLine(Line4);
                                           
                                           LcdPictureWrite(100,Line4,4,BATSTU3);
                                           
                                           LcdBoardWrite(2,Line4);    //边界
                                           
                                           kkk=CeJianHao/100;
                                           LcdDigitalWrite(4,Line4,kkk);   //车间号***
                                           kkk=CeJianHao/10%10;
                                           LcdDigitalWrite(12,Line4,kkk);
                                           kkk=CeJianHao%10;
                                           LcdDigitalWrite(20,Line4,kkk);
                                           
                                           LcdBoardWrite(28,Line4);//边界
                                           LcdDigitalWrite(30,Line4,ZeRenQu);//责任区*
                                           LcdBoardWrite(38,Line4);//边界
                                           
                                           kkk=BanZuHao/100;  
                                           LcdDigitalWrite(40,Line4,kkk);    //班组号***
                                           kkk=BanZuHao/10%10;
                                           LcdDigitalWrite(48,Line4,kkk);
                                           kkk=BanZuHao%10;
                                           LcdDigitalWrite(56,Line4,kkk);
                                           
                                           LcdBoardWrite(64,Line4);//边界
                                           
                                           
                                           LcdBoardWrite(70,Line4);//边界
                                            
                                           kkk=MBChannel/10;
                                           LcdDigitalWrite(72,Line4,kkk);    //通道号***
                                           kkk=MBChannel%10;
                                           LcdDigitalWrite(80,Line4,kkk);
                                           LcdBoardWrite(88,Line4);//边界
                                         
                                           
                                           ClearLcdLine(Line1);
                                           ClearLcdLine(Line2);
                                           ClearLcdLine(Line3);
                                           
                                           LcdTwoByteWrite(48,Line3,4 ,UNITANDKUAHAO);   //℃++垮
                                           LcdTwoByteWrite(48,Line2,4 ,UNITANDPAIHAO);   //℃++排
                                           LcdTwoByteWrite(48,Line1,4 ,UNITANDJIAOHAO);  //℃++窖
                            
                                           
                                           kkk=KuaHao/10;
                                           LcdOneByteWrite(80,Line3,kkk,0);
                                           kkk=KuaHao%10;
                                           LcdOneByteWrite(88,Line3,kkk,0);
                                           
                                           kkk=PaiHao/10;
                                           LcdOneByteWrite(80,Line2,kkk,0);
                                           kkk=PaiHao%10;
                                           LcdOneByteWrite(88,Line2,kkk,0);
                                           
                                                                      
                                           kkk=JiaoHao/10;
                                           LcdOneByteWrite(80,Line1,kkk,0);
                                           kkk=JiaoHao%10;
                                           LcdOneByteWrite(88,Line1,kkk,0);
                                           
                                           DigitalRefresh(Point1,1,PV[0],DataOverflow[0]);
                                           DigitalRefresh(Point1,2,PV[1],DataOverflow[1]);
                                           DigitalRefresh(Point1,3,PV[2],DataOverflow[2]);
                                           
                                           
                               
                                           
                                           
  
}