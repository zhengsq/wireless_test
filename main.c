
/******************************************************************************************************************************
*******************************************************************************************************************************
ver1.1:
1，取消了垮号，排号，窖号的限制，设置范围00-99
2，更改了上电垮号，排号，窖号设置范围的检测，改为00-99
3，更改了工作时间的设置单位，由 WorkTime(分钟) 改为 WorkTime(*10秒)
4, 缩短了激活唤醒后的显示时间，WorkTime(*10秒)  1-1999 (*10秒)
5, 修正了有时无法唤醒的BUG
6，版本号改为Ver1.1
7, 修正在等待手操器操作的十五秒内，若被手动激活，则无法进入休眠状态
8，增加备份标志Bakuped,避免在无备份情况下恢复无效的参数。
9，缩短激活后，激活灯点亮的时间
10，延长了上电时，“无线温变”的显示时间，同时取消上电强制模块进入休眠状态，便于读取模块参数
11,延长了开,关机长按激活键的时间,由3秒延长到7秒以上.


                                        2012-10-25
ver1.2:
1，版本号改为Ver1.2
2,初始化不改特征码，信道，功率，保持原来的值。
3,增加每1小时自动读参数,并比较(在已备份条件下)ID码,若不同则把备份区ID拷入,并启动写PID指令
4,增加写PID指令0x32;
5,增加手操器写PID指令,
6,增加手操器,键盘恢复备份时,写PID指令.
7,修改了专家指令格式.
3，取消手动关机.
9，更改了Bakuped的定义。
10.增加了低电压自动关机(小于2.6V)
11，备份时，把采样时间，备份采样时间改为10分钟（针对五粮液）
                                         2013-04-08
********************************************************************************************************************************
********************************************************************************************************************************/
#include <io430.h>
#include <in430.h>
#include <intrinsics.h>

#include "Predefined.h"
#include "DefineSPC.h"
#include "InputDo.h"
#include "InitSys.h"
#include "FlashWR.h"
#include "Key.h"
#include "DispDataDo.h"
#include "CalFromTab.h"
#include "CommDo.h"
#include "LcdDriver.h"

void  GoIntoActiveMode(void);
void  GoIntoSleepMode(void);




void SPCInit(void)
{
  
 

 
 ADPowerOn;
 PV[0]=0;
 PV[1]=0;
 PV[2]=0;
  
 SAMP[0]=0;
 SAMP[1]=0;
 SAMP[2]=0; 
  
 CAPTURE_CNT=0;
 CAPTURE_ADD=0;
 CAPTURE_NOP=0; 
 InputSampleOver=0;
 InputChannel=1;
 
 
 P2OUT&=~BIT2;        
 P2OUT&=~BIT1;      
 P2OUT&=~BIT0; 
 
 AutoSendForHander=Off;
 TimeForSentFlag=0;
 AutoWakeFlag=Off;
 WakeSignFlag=Off;
 SendTimes=0;
 
 
 

 
 WriteCommand(0xA4);
 
 WriteCommand(0xAF);
 
 LedAOn;
 LedStuOn;
 LedStart=On;
 LedDelayCount=20;//开机后，灯亮的时间20*60ms
 
 MenuStuNum=0;
 MenuStu=Off;
 CommStatusFlag=0;
 ReportFlag=Off;
 RecoverFlag=Off;
 RefreshAfterRead=Off;
 IDSetFlag=Off;
 ReadIDCount=0;
 
 
if(CeJianHao >999)
            CeJianHao=0; 
if(ZeRenQu >99)
            ZeRenQu=0;
if(BanZuHao >999)
            BanZuHao=0;

if(KuaHao >99)
            KuaHao=0;
if(PaiHao >99)
            PaiHao=0;
if(JiaoHao >99)
            JiaoHao=0;
if(MBChannel>99)
            MBChannel=0;

if(MBPower >7)
            MBPower=7;


if((StandbyTime >1999)||(StandbyTime==0))
                 StandbyTime=1;

if((WorkTime >1999)||(WorkTime ==0))
                 WorkTime=1;
if((ReportChannel>123)||(ReportChannel<100))
                 ReportChannel=100;

if((PVPT[0]>100)||(PVPT[0]<-100))
                     PVPT[0]=0;

if((PVPT[1]>100)||(PVPT[1]<-100))
                     PVPT[1]=0;

if((PVPT[2]>100)||(PVPT[2]<-100))
                     PVPT[2]=0;

 
 
LcdTwoByteWrite(25,Line3,4 ,WXWB);  //无线温变
 
LcdCharWrite(28,Line2,8,VERSION) ; //版本信息ver 1.1M

 //  LcdTwoByteWrite(1,Line3,7 ,BAITEGONGKONG);  //百特工控+空格
  
 //LcdCharWrite(0,Line2,15,FBTC) ;           //FBTC+空格
 
 //delay_ms(1150);//延时时间已调整，改变将影响上电时的模块读取

 delay_ms(1600);//显示及延长模块上电时间，便于读取参数
 
}



void main(void)

{ 
   
   _DINT();                      //关全局中断
   
   WDTCTL=WDTPW+WDTHOLD;         //关看门狗
 
   
   InitSysBasic();
   
   RDFlash(( uchar *)0x200,(uchar *)0x1000,64);

   RDFlash((uchar *)0x280,(uchar *)0x1080,33); 
  
    
   KeyPutStu=Off;
   
   ADPowerOff;
   LedAOff;
   LedStuOff;
   ReportFlag=Off; 
   RecoverFlag=Off;
   
   //MBSleep;//1026
   WirelessStu=Off;
   MBDataReadFlag=Off;
   
   KeyDelayCount=0;
   StuCount=0;
   KeyTestTime=Off;   
   
   OverTime=0;
   /*
   LcdInit();
   WriteCommand(0xA5);
   WriteCommand(0xAE);
   */
   P5DIR=0XFF;
   P5OUT=0;
   
   P3OUT|=BIT1;
   
   KeyTemp=P2IN&0X80;
   
   delay_ms(20);//消抖
   
   if((KeyTemp==0)&&((P2IN&0X80)==0))
    {
      DataTemp=0;
      do
       {
         delay_ms(100);
         DataTemp++;
         if(DataTemp==20)        //按键按压持续6秒以上
                      break;
       }
      while((P2IN&0X80)==0);
      
      if(DataTemp>=20)
       {
        LcdInit();
        LedAOn;
        LcdTwoByteWrite(0,Line3,7 ,BACKUPING);//参数恢复中……
        
        delay_ms(500);
  
        DataRecover888(&StartRAM);    //恢复备份
        
        WRFlash ((uchar *)0x200,(uchar *)0x1000,64);
        delay_ms(10);
        RDFlash ((uchar *)0x200,(uchar *)0x1000,64);
        delay_ms(10);
        WRFlash ((uchar *)0x280,(uchar *)0x1080,33);
        delay_ms(10);
        RDFlash ((uchar *)0x280,(uchar *)0x1080,33);
        delay_ms(10);
        
        //MBDataReadFlag=Off;
        
       }
      
      
    }

  
        InitSysForActive();
                                           
        LcdInit();
                                          
        SPCInit();
                                          
        NormalDisp();
                                           
        StuCount=0;
        WorkTimeSecond=15;
        WBStu=Active;
        
        P2IES=0X80;                //下降沿触发
        P2IFG=0;
        P2IE=0X80;                 //开P2.7中断
        
        P1IFG=0;
        
       
        
        
        
       _EINT();
       
        _NOP();
        _NOP();
        _NOP();
        _NOP();
        _NOP();
        _NOP();
       
       ConfigDataRead(CommSent);
           
       ME1=UTXE0;
       _NOP();
       _NOP();
       CommNum=0;
       U0TXBUF=CommSent[0];
       
  while(1)
   {
     
                 WDTCTL=WDT_ARST_1000;
                 
                  if((InputSampleOver==1)&&(WirelessStu==Off))
                        {
                         
                         if(DataOverflow[InputChannel-1]==0)
                          {
                           
                            switch(InputChannel)
                             {
                               case  1:
                                      PV[0]=CalFromTab(1,&In1Cal00,&In1CalFS)+(signed int)PVPT[0];
                               break;
                               case  2:
                                      PV[1]=CalFromTab(2,&In2Cal00,&In2CalFS)+(signed int)PVPT[1];
                               break;
                               case  3:
                                      PV[2]=CalFromTab(3,&In3Cal00,&In3CalFS)+(signed int)PVPT[2];
                               break;
                               
                             }
                            
                                 
                                  
                          }
                         else
                          {
                            PV[InputChannel-1]=32767;
                          }
                  
                          InputSampleOver=0;
                          CAPTURE_CNT=0;
                          CAPTURE_ADD=0;
                          CAPTURE_NOP=0;
                          TACCTL2=CM_2+CAP;
                          InputChannel++;
                          if(InputChannel==4)
                                     InputChannel=1;
                          //InputChannel=1;//T
                          switch(InputChannel)
                         {
                        case 1:
                                 P2OUT&=~BIT2;        
                                 P2OUT&=~BIT1;      
                                 P2OUT&=~BIT0;     //第一路输入正端
                                 
                                 break;
                        case 2:
                                 P2OUT&=~BIT2;        
                                 P2OUT|=BIT1;      
                                 P2OUT&=~BIT0;     //第二路输入正端
                                 
                                
                                 break;           
                        case 3:
                                 P2OUT|=BIT2;        
                                 P2OUT&=~BIT1;      
                                 P2OUT&=~BIT0;    //第三路输入正端
                               
                                 break;
                        default:
                                  _NOP();
                         }
    
                   }
                  
                  
      
  
   
   
  /*************************************************************/  
    if(KeyTestTime==On)				    //每隔一定时间进行键盘扫描
	 {
	 
	 KeyTestTime=Off;
	 KeyTemp1=P2IN;
	 KeyTemp1&=0x68;				    //读键值
	 if(KeyValue==KeyTemp1)
		 {
		      if(KeyChange==1)
		         {
		         ramstart=&StartRAM;
		         Key(KeyValue);	    //键盘处理
			 }
		      
		 }
          else
		 {
		 KeyValue=KeyTemp1;
		 KeyChange=1;
		 Key30s=750;
			 
		 }
         }
 
  /****************************模块设置处理*********************************/ 
         if(MBDataReadFlag==1)
         {
           
           MBDataReadFlag=Ready;
           
           MBWake;
           WirelessStu=On;
           delay_ms(20);//唤醒需要一段时间
           
           ConfigDataRead(CommSent);
           
           ME1=UTXE0;
           _NOP();
           _NOP();
           CommNum=0;
           U0TXBUF=CommSent[0];
         }
         
         
         if(ConfigFlag==1)
          {
            MBWake;
            WirelessStu=On;
            delay_ms(20);//唤醒需要一段时间
             
            ConfigFlag=0;
            ConfigDataWrite(CommSent,&StartRAM);
            
            ME1=UTXE0;
            _NOP();
            _NOP();
            CommNum=0;
            U0TXBUF=CommSent[0];
          }
  /****************************接收处理*********************************/    
         if(RiEndFlag==1)
	 {

	      CommSentData(CommReceive,CommSent,&StartRAM);
 
              if(SentOrNot==1)
               {
               ME1=UTXE0;                //使能发送
               _NOP();
               _NOP();
               CommNum=0;
               U0TXBUF=CommSent[0];       //正常通讯状态,
                    
                }
              else
               {
                 
                ME1=URXE0;          //使能接收 
                CommNum=0; 
                MBSleep;
                WirelessStu=Off;
               
               }
              
           RiEndFlag=0;
	 }
         
   /*          
      if(AutoWakeFlag==On)
       {
          if((P1IN&0x80)==0)
          {
                  AutoWakeFlag=Off;
                  MBSleep;
                  WirelessStu=Off;
                  LedStuOff;
          }
       }
       
      
       if(AutoSendForHander==On)
       {
          if((P1IN&0x04)==0x04)
          {
                  AutoSendForHander=Off;
                  MBSleep;
                  WirelessStu=Off;
          }
       }
       */
       
      if(TimeForSentFlag==1)
       {
              MBWake;
              WirelessStu=On;
              delay_ms(25);         //唤醒+发送间隔 需要一段时间
              
              CommSent[11]=0x03;
              if(AutoSendForHander==On)
                               CommSent[11]=0x53;
 
              CommNormalData(CommSent,&StartRAM);
  
               ME1=UTXE0;          //使能发送
               _NOP();
               _NOP();
               
               CommNum=0;
               
               U0TXBUF=CommSent[0]; 
               
               TimeForSentFlag=0;
              
              
       }
       
 /****************************发送处理*********************************/ 
	    if(TiEndFlag==1)
	    {
	           uchar k;
                  
                    for(k=0;k<47;k++)
	              {
	                  CommSent[k]=0;
	              }
                 
                   CommNum=0;
		   ME1=URXE0;          //使能接收 
                      
	           TiEndFlag=0;
                   
              
	     }
 /****************************超时处理*********************************/ 
	    if(OverTime==1)					//异常超时处理
	    {

	     uchar k;
			   for(k=0;k<47;k++)
			      {
			      CommSent[k]=0;
                              CommReceive[k]=0;
			      }
	
	  
	    CommNum=0;
            OverTime=0;
            ME1=URXE0;          //使能接收
            MBSleep;             //异常关闭模块
            _NOP();
            _NOP();
            WirelessStu=Off;
              
              
     
	    }
   /******************电池电压AD12转换处理***************************************/  
  
    if(((ADC12IFG&0X0004)!=0)&&(AD12Flag==On))      //两秒采集一次电池信息
      
     {
       
       ADC12IFG=0;
       
       
       ADCSampleTimes+=ADC12MEM2;
       ADCTimes++;
       
       if(ADCTimes==100)
        {
          AD12Flag=Off;
          ADC12CTL0&=~ENC;
          ADC12CTL0&=~REFON;
          
          BatVoltage=(ADCSampleTimes*1.5)/100/4096;
          
          if(BatVoltage >=1.28)
                 {
                   BatStu=3;
                   LowBatTest=0;
                  
                 }
         
          else if((BatVoltage >=1.22)&&(BatVoltage < 1.28)) //锂电池电压低于3.45V
                 {
                   BatStu=2;
                   
                   LowBatTest=0;
                 }
          else if((BatVoltage >=1.15)&&(BatVoltage < 1.22))//锂电池电压低于3.3V
                 {
                   BatStu=1;
                   LowBatTest=0;
                 }
          else if((BatVoltage >=1.00)&&(BatVoltage < 1.15))//锂电池电压低于3.0V
                {
                  BatStu=0;
                  LowBatTest=0; 
                  
                }
          else   //锂电池电压低于2.6V,直接关机
                 {
                   LowBatTest++;
                      if(LowBatTest==20)
                      {
                                        LowBatTest=0;
 
                                          
                                         ADPowerOff;
                                         MBSleep;
                                         WirelessStu=Off;
                                         
                                         LedAOn;
                                         MenuStu=On;
                                         LcdInit();
                                         ClearLcdLine(Line1);
                                         ClearLcdLine(Line2);
                                         ClearLcdLine(Line3);
                                         ClearLcdLine(Line4);
                                         LcdTwoByteWrite(8,Line3,6 ,POWEROFF);//正在关机……
                                         
                                         WDTCTL=WDTPW+WDTHOLD;
                                         
                                         delay_ms(1000);
                                          
                                         LedAOff;
                                         MenuStu=Off;
                                         LedStuOff;
                                        
                                         WriteCommand(0xA5);
                                         WriteCommand(0xAE);
                                         P5DIR=0XFF;
                                         P5OUT=0;
                                         P2OUT&=~BIT2;        
                                         P2OUT&=~BIT1;      
                                         P2OUT&=~BIT0; 
                                         
                                         InitSysForPowerOff();
                                         WBStu=PowerOff; 
       
                                         LPM4;          //关机（深度休眠）
                       
                      }
                 }
         
           //BatStu=3;//针对一次性锂电池       
          
          ADCSampleTimes=0;
          ADCTimes=0;
          
        }
       else
       {
         ADC12CTL0|=ADC12SC+ENC;
       }
       
       
     }
            

     
 

    }
}



#pragma vector=PORT1_VECTOR      //模块下发唤醒中断
__interrupt void Port1Int(void)
 {
   uint i;
  //LedAOn;//t                          
  P1IFG = 0;                           // P1.7 IFG cleared
  i=50;

  while((--i))
 {
    _NOP();
  }
  //delay_ms(10);                            //消抖
  MBWakePort=P1IN&0X84;
  switch(MBWakePort)
   {
     case 0x84:                       //远程查询时/手操器设置时(离开磁性开关)
     case 0x80:                       //1,手操器设置时(未离开磁性开关)  2,远程查询与手操器同时靠近时,远程查询优先
               WirelessStu=On;
               AutoWakeFlag=On;
               //LedAOn;//t
               LedStuOn;
              if(WBStu==Standby)
              {
               TB0DelayCount=3;//3*200ms关闭
               LPM3_EXIT;
                     
              }
              else
               {
                 WakeDelayCount=10;//延时10*60ms
                 WakeDelayFlag=On;
               }
              
     break;

     case 0x00:                       //手操器接近时
              P1IE&=~BIT2;          //关手操器中断
              ReportFlag=On;
              ConfigFlag=1;
              AutoSendForHander=On;
              //LedAOn;//t
              LedStuOn;
               if(WBStu==Standby)
               {
              
                // TB0DelayCount=40;//40*200ms关闭
                 TB0DelayCount=75;//75*200ms关闭
                 LPM3_EXIT;
               }
              else
               {
                 StuCount=0;
                 //WakeDelayCount=130;//延时130*60ms,8秒后自动关闭
                 WakeDelayCount=250;
                 WakeDelayFlag=On;
               }
              
     break;
   }
  
 
   

   
   
   
 }

#pragma vector=PORT2_VECTOR
__interrupt void Port2Int(void)
{
  uint i;
  //LedAOn;//t  
  WDTCTL=WDTPW+WDTHOLD;
  P2IFG = 0;                           // P2.7 IFG cleared
  i=500;

  while((--i))
 {
    _NOP();
  }
  //delay_ms(10);                            //消抖
  KeyTemp=P2IN&0X80;
   
  
  if(KeyTemp==0)
  {
    
    KeyPutStu=On;
    P2IE=0;                                //关闭中断
    KeyDelayCount=0;
        // if((WBStu==PowerOff)||(WBStu==Standby))
       if(WBStu==PowerOff)
         {
           LPM4_EXIT;
           _EINT();
           TBCTL=TBSSEL_1+MC_2;//ACLK,连续模式
           TBCCTL1|=CCIE;
           TBR=0;
           TBCCR1=1966;            //60ms中断一次
           TBCCTL0=0;              //关TBCCR0中断
           
           P2OUT&=~BIT2;        
           P2OUT&=~BIT1;      
           P2OUT&=~BIT0;
          
           LPM3;        //开ACLK
         }
      if(WBStu==Standby)
       {
        //LedAOn;//t 
        TACTL=0;    
        TACCTL0=0;       
        TACCTL1=0;
        TACCTL2=0;
        
        TBCTL=TBSSEL_1+MC_2;//ACLK,连续模式
        TBCCTL1|=CCIE;
        TBR=0;
        TBCCR1=1966;             //60ms中断一次
        TBCCTL0=0;              //关TBCCR0中断 
         
         
       }
  }
 
  
}
/***************************自动唤醒(TimeB0中断)*****************************************************/

/**************************打开AD转换，电池检测，液晶关闭，键盘关闭******************************************************/




#pragma vector=TIMERB0_VECTOR
__interrupt void TimerB0Int (void)
 {
   unsigned long tb0data;
   
   WDTCTL=WDT_ARST_1000;
   
    if(WakeSignFlag==Off)               //待机状态下有收到数据停止计数
    {
              SleepCount++;
              ReadIDCount++;
    }
    
    if(ReadIDCount>=18000)        //1小时左右读一次ID码,
    {
     ReadIDCount=0;
     MBDataReadFlag=On;
     
    }
      
  tb0data=(unsigned long)StandbyTime*300;
  
   if(SleepCount >=tb0data)
   {
   SleepCount=0;
   
   WorkTimeSecond=5;
   LedStart=On;
   LedDelayCount=10;//自动唤醒后，激活灯亮的时间10*60ms
   
   GoIntoActiveMode();
 
   LPM3_EXIT; 
   }
   
   
   if((AutoWakeFlag==On)||(AutoSendForHander==On))
   {
     TB0DelayCount--;
     if(TB0DelayCount==0)
     {
                  MBSleep;
                  WirelessStu=Off;
                  LedStuOff;
                  
                  AutoWakeFlag=Off;
                  ReportFlag=Off;
                  AutoSentFlag=0;
                  WakeSignFlag=Off;
                  
                  TimeForSentFlag=0;
                  
                  if(AutoSendForHander==On)
                  {
                    
                  AutoSendForHander=Off;
                  P1IE|=BIT2;              //开手操器中断    
                  ReportFlag=Off;
                  RecoverFlag=On;
                  ConfigFlag=1;            //恢复正常通道 
                  SleepCount=0;
                  
                  WorkTimeSecond=5;
  
                  LedStart=On;
                  LedDelayCount=10;//等待时间后，自动进入采集信道恢复。激活灯亮的时间10*60ms
                  GoIntoActiveMode();
                  }
                  else
                  {
                   GoIntoSleepMode(); 
                     
                   _EINT();
                   LPM3;
 
                  }
       
       
       
       
     }
     
     
     
   }
   
   
   
   
   
  
  
   
 }


/***************************模式转换(TimeB中断)*****************************************************/

#pragma vector=TIMERB1_VECTOR
__interrupt void TimerB1Int (void)
{
    switch(TBIV)
     {
       case 0x02:                          //TBCCR1 CCIFG
                // LedAOn;//t
                WDTCTL=WDT_ARST_1000;
                if(LedStart==On)
                 {  
                 LedDelayCount--;
                     if(LedDelayCount==0)  
                      {
                       LedDelayCount=0;
                       LedStuOff;           //时间到，关闭激活灯
                       LedStart=Off;
                      }
                 } 
                 if(WakeDelayFlag==On)
                  {
                     
                     WakeDelayCount--;
                     if(WakeDelayCount==0)  //工作状态,延时时间到;
                      {
                           if(DataRefreshFlag==On)//手动激活状态
                             {
                               DataRefreshFlag=Off;
                               NormalDisp();
                             }
                       // LedAOff;//t 
                        LedStuOff;
                        WakeDelayFlag=Off;
                                
                        MBSleep;
                        WirelessStu=Off;
                        AutoWakeFlag=Off;
                        
                           if( AutoSendForHander==On) 
                           {
                            P1IE|=BIT2;      //开手操器中断
                            AutoSendForHander=Off;
                            ReportFlag=Off;
                            RecoverFlag=On;
                            StuCount=0;
                            ConfigFlag=1;            //恢复正常通道 
                           }
                        
                        }
                   
                  }
                                                       
                 TBCCTL1&=~CCIFG;
                 KeyTestTime=On;           //key1-key4间隔扫描时间
                 if((MenuStu==Off)&&(WBStu==Active)&&(ReportFlag==Off))
                 {
                 DispCount++;
                    if(DispCount >=4)
                   {
                   DispCount=0;
                   DispLine++;
                       if(DispLine>=3)
                            DispLine=0;
                        switch(DispLine)
                        {
                          case 0:
                                DigitalRefresh(1,1,PV[0],DataOverflow[0]);
                                break;
                          case 1:
                                DigitalRefresh(1,2,PV[1],DataOverflow[1]);
                                break;
                          case 2:
                                DigitalRefresh(1,3,PV[2],DataOverflow[2]);
                                break;
                       
                       
                         }
                   
                     }
                 }
                 TBCCR1+=1966;                  //60ms中断
                 if(KeyPutStu==On)             //持续按压激活键时间检测    
                  {
                    KeyTemp=P2IN&0X80;
                    if(KeyTemp==0)                //激活键保持按下状态
                     {
                       
                        KeyDelayCount++;
                        StuCount=0;              //激活键保持按下状态时，避免进入休眠模式
                        if(KeyDelayCount >=120)    //长按持续时间:7秒以上
                        {
                         KeyDelayCount=0;
                         KeyPutStu=Off;
                         P2IES=0X80;                //下降沿触发
                         P2IFG=0;
                         P2IE=0X80;                 //开P2.7中断
                           switch(WBStu)
                           {
                            case PowerOff:                         //长按,开机
                              
                                           _NOP();
                                           _NOP();
                                           
                                           
                                           LPM3_EXIT;
                                           
                                           WDTCTL=WDTPW+WDTHOLD;
                                           
                                           InitSysForActive();
                                           
                                           LcdInit();
                                          
                                           SPCInit();
                                          
                                           NormalDisp();
                                           
                                           StuCount=0;
                                           WorkTimeSecond=15;        //开机显示时间延长
                                           WBStu=Active;
                                         
                                           
                                           break;
                            
                          case Standby:                            //长按手动激活
                                     
                                     LedAOn;
                                     LedStart=On;
                                     LedDelayCount=20;//激活后，激活灯亮的时间20*60ms
                                     GoIntoActiveMode();
                                     LcdInit();
                                     NormalDisp();
                                     WorkTimeSecond=WorkTime*5;
                                     
                                   
                                     LPM3_EXIT;
                                     
                                     break;
                          default: 
                                           _NOP();
                                           _NOP();
                                         /* 
                                         ADPowerOff;
                                         MBSleep;
                                         WirelessStu=Off;
                                         
                                         ClearLcdLine(Line1);
                                         ClearLcdLine(Line2);
                                         ClearLcdLine(Line3);
                                         ClearLcdLine(Line4);
                                         LcdTwoByteWrite(8,Line3,6 ,POWEROFF);//正在关机……
                                         
                                         WDTCTL=WDTPW+WDTHOLD;
                                         
                                         delay_ms(1000);
                                          
                                         LedAOff;
                                         LedStuOff;
                                        
                                         WriteCommand(0xA5);
                                         WriteCommand(0xAE);
                                         P5DIR=0XFF;
                                         P5OUT=0;
                                         P2OUT&=~BIT2;        
                                         P2OUT&=~BIT1;      
                                         P2OUT&=~BIT0; 
                                         
                                         InitSysForPowerOff();
                                         WBStu=PowerOff; 
                                         
                                         
                                         
                                         _EINT();
                                         LPM4;          //关机（深度休眠）
                                           */
                                  
                          }
                        }
                        
                     }
                   
                    else
                     {
                      KeyDelayCount=0;
                      KeyPutStu=Off;
                      P2IES=0X80;                //下降沿触发
                      P2IFG=0;
                      P2IE=0X80;                 //开P2.7中断
                      switch(WBStu)
                      {
                      case PowerOff:
                                     LPM3_EXIT;
                                     _EINT();
                                     LedAOff;
                                     LedStuOff;
                                     TBCTL=0;
                                     TBCCTL1=0;
                                     TBR=0;
                                     TBCCR1=0; 
                                     LPM4;
                                     break;
                      case Active: 
                                     //P1DIR|=BIT2;
                                     StuCount=0;                  //重新开始工作状态计时,6秒后开启无线模块
                                     //AutoSentFlag=1;
                                     WorkTimeSecond=WorkTime*5;
                                     LedStuOn;
                                     if((P4OUT&BIT5)==BIT5)//在自动激活状态
                                     {
                                     LedAOn;                   
                                     LcdInit();
                                     NormalDisp();                 //激活显示,在自动激活状态
                                     }
                                     else
                                     {
                                        if((ReportFlag==Off)&&(MenuStu==Off))
                                        {
                                         ReportFlag=Ready;
                                         ClearLcdLine(Line1);
                                         ClearLcdLine(Line2);
                                         ClearLcdLine(Line3);
                                         ClearLcdLine(Line4);
                                         LcdTwoByteWrite(16,Line4,5,REPORT);
                                         
                                         LcdTwoByteWrite(0,Line2,7,CONFIRMPRESSBUTTON);
                                         
                                         LcdOneByteWrite(24,Line1,22,0);/*"C"*/
                                         LcdOneByteWrite(32,Line1,27,0);/*"H"*/
                                         LcdOneByteWrite(40,Line1,2,0);/*"2"*/
                                         LcdOneByteWrite(48,Line1,14,0);/*":"*/
                                         
                                         LcdOneByteWrite(56,Line1,(ReportChannel/100),0);
                                         LcdOneByteWrite(64,Line1,(ReportChannel/10)%10,0);
                                         LcdOneByteWrite(72,Line1,(ReportChannel%10),0);
                                         
                                         
                                         P2IFG=0;                    //避免连续多次点击直接上报的情况出现
                                        }
                                     
                                         else if(ReportFlag==Ready)
                                         { 
                                           ReportFlag=On;
                                           StuCount=0;
                                           ConfigFlag=1;
                                      
                                           ClearLcdLine(Line2);
                                           ClearLcdLine(Line4);
                                           LcdTwoByteWrite(8,Line4,6,REPORTING);
                                           
                                           LcdTwoByteWrite(16,Line2,5,WAITING);
                                       
                                       
                                         }
                                         else
                                         {
                                          _NOP();
                                         }
                                     }
                                     
                                     //LcdInit();
                                   //  NormalDisp();
                                     break;
                      case Standby:                            //手动激活
                                     
                                     
                                     LedAOn;
                                     LedStart=On;
                                     LedDelayCount=20;//激活后，激活灯亮的时间20*60ms
                                     WorkTimeSecond=WorkTime*5;
                                     GoIntoActiveMode();
                           
                                     LcdInit();
                                     NormalDisp();
                                     LPM3_EXIT;
                                     break;
                         
                      }
                       
                        
                     }
                   
                  }
                 break;
      
                   
       case 0x0e:                                  //TBIFG
                 TBCTL&=~TBIFG;
                
                                     if((MenuStu==Off)&&(ReportFlag==Off))
                                     {
                                      AD12Flag=On;    //2秒采集电量信息
                                      ADC12CTL0&=~ENC;
                                      
                                      ADC12CTL0|=REFON;
                                      ADCSampleTimes=0;
                                      ADCTimes=0;
                                      ADC12CTL0|=ADC12SC+ENC;
                                      
                                       switch(BatStu)
                                     {
                                     case 0:
                                              LcdPictureWrite(100,Line4,4,BATSTU0);
                                              break;
                                     case 1:
                                              LcdPictureWrite(100,Line4,4,BATSTU1);
                                              break;
                                     case 2:
                                              LcdPictureWrite(100,Line4,4,BATSTU2);
                                              break;
                                     case 3:
                                              LcdPictureWrite(100,Line4,4,BATSTU3);
                                              break;
                                       }
                                     }
                 
                 if(WBStu==Active)
                 {
                 
                   
                       if((MenuStu==Off)&&(AutoSendForHander==Off)&&(AutoWakeFlag==Off))  
                                                       StuCount++;
                       
                      
                       if(StuCount==3)              //6秒后转入数据处理
                        {
                             LedStuOff;
                             
                             if(RefreshAfterRead==On)//读模块后更新
                             {
                               RefreshAfterRead=Off;
                               NormalDisp();
                             }
                          
                             if(ReportFlag==Ready)  //上报超时自动返回正常显示
                             {
                                ReportFlag=Off;
                                NormalDisp();
                             }
                             
                          
                             if(ConfigStu==On)        //进入配置状态
                             {
                                ConfigStu=Off;
                                ConfigFlag=1;
                             
                             }
                             
                          
                             if((ReportFlag==On)||(RecoverFlag==On))
                             {
                                ReportFlag=Off;
                            
                                NormalDisp(); 
                                ConfigFlag=1;
                            
                             }
                             
                             if((MBDataReadFlag==On)&&(ConfigStu!=1))
                             {
                               
                               MBDataReadFlag=1;
                               
                             }
                          
                        }
                      
                       
                       if(StuCount >= WorkTimeSecond)      //活动模式时间到(worktime*10秒或者10秒)
                   
                        {
                         GoIntoSleepMode();
           
                         _EINT();
                         LPM3;                    //自动进入待机状态
                        }
                 }
                               
                break;
     }
}


/***************************AD处理(TimeA中断)******************************************************/

#pragma   vector=TIMERA1_VECTOR
__interrupt void  ta_compa_int(void)
 {
   
   switch(TAIV)
    {
      
      case 0x02:               //TACCR1 CCIFG
                               //TACCR1=PWMOUT;
               TACCTL1&=~CCIFG;
               if(CommStatusFlag==1)
                 {
                     CommTest++;
                 
                     if(CommTest>=3)                  //15MS
                      {
                       OverTime=1;
	               CommTest=0;
	               CommStatusFlag=0;
                      }
                 }
               break;
      case 0x04:              //TACCR2 CCIFG
               break;
      case 0x0a:             //TAIFG
              
              TACCR1=PWMOUT;
              TACTL &=~TAIFG;
              
              if((CommStatusFlag==0)&&(WirelessStu==Off))
              {
                               if(InputSampleOver==0)
                                {
                                     InputDo();
                                  
                                  
                                }
                               else
                                {
                                  if(TACCTL2_bit.CCIFG==1)
                                    
                                            TACCTL2_bit.CCIFG=0;
                                   
                                  
                                }
                              
               }
             else
              {
               
                if(TACCTL2_bit.CCIFG==1)
                             TACCTL2_bit.CCIFG=0;
                
                 if(CommStatusFlag==1)
                 {
                     CommTest++;
                 
                     if(CommTest>=3)                  //20MS
                      {
                       OverTime=1;
	               CommTest=0;
	               CommStatusFlag=0;
                      }
                 }
              }
              
           
           
               break;
      
    }
   
   
  
    
         
   
 }

/***************************通讯：接收中断******************************************************/
#pragma vector=USART0RX_VECTOR
__interrupt void receive_int(void)
 {
    uchar RiData;
   
    CommStatusFlag=1;
    CommTest=0;
	
    RiData=U0RXBUF;
    CommReceive[CommNum]=RiData;
    CommNum++;
    
      if(WBStu==Standby)
      {
        if(WakeSignFlag==Off)
         {
          WakeSignFlag=On;
          
          TACTL=TASSEL_1+MC_1;  //ACLK,增模式      2013-05-13
          TACCTL1&=~CCIFG;
          TACCTL1=CCIE;
          TAR=0;
          TACCR1=164;          //开5MS中断
         }
      }
    
   
   
      
       if(CommNum==3)
       {
         
        ReceiveNum=CommReceive[2]+5;
         
             
       }
  
    
    if(CommNum >3)
     {
	    if(CommNum==ReceiveNum)
	    {
			
			CommStatusFlag=0;
			RiEndFlag=1;
                        ME1=0;
                       // ME1=UTXE0; 
                        /*
                        if(WBStu==Standby)
                        {
                          //LedAOff;
                          ME1=UTXE0;          //使能发送，
                         
                        }
			*/
                       
	     }
     }
 
 }
   
   
   

/***************************通讯：发送中断******************************************************/
#pragma vector=USART0TX_VECTOR
__interrupt void sent_int(void)
 {
 
    CommStatusFlag=1;
    CommTest=0;
    CommNum++;
   
    
   
      if(CommNum==(SentNum))
	{
	CommStatusFlag=0;
	TiEndFlag=1;
       // ME1=URXE0;          //使能接收
	}
      else
        {
      
        U0TXBUF=CommSent[CommNum]; 
        }
    
    
  
 
 }


void  GoIntoActiveMode(void)//进入正常工作状态
{
  
   LedStuOn;
   StuCount=0;
   ADPowerOn;
    //LedAOn;//test
 
   KeyTestTime=Off;

   SAMP[0]=0;
   SAMP[1]=0;
   SAMP[2]=0; 
  
   CAPTURE_CNT=0;
   CAPTURE_ADD=0;
   CAPTURE_NOP=0; 
   InputSampleOver=0;
   InputChannel=1;
  
   P2OUT&=~BIT2;        
   P2OUT&=~BIT1;      
   P2OUT&=~BIT0; 
 
 
   WBStu=Active;                          
   InitSysForActive(); 
   
              if((AutoWakeFlag==On)||(AutoSendForHander==On))
                 {
                   MBSleep;
                   WirelessStu=Off;
                   WakeDelayFlag=On;
                          if(AutoSendForHander==On)
                           {
                            WakeDelayCount=250;
                           }
                         else
                           {
                            WakeDelayCount=10; 
                           }
                                                              
                 }
  
}


void  GoIntoSleepMode(void)   //进入待机状态
{
                      LedAOff;
                      LedStuOff; 
                      ADPowerOff;
                      
                      StuCount=0;
                      WBStu=Standby;
                      
                      MBSleep;
                      WirelessStu=Off;
                      
                      AutoSentFlag=0;
                      ReportFlag=Off;
                      
                      RiEndFlag=0;
                      TiEndFlag=0;
                      SentOrNot=0;
                      CommStatusFlag=0;
                      CommTest=0;
                      ME1=URXE0;
                      CommNum=0;
 
                      SendTimes=0;
                      TimeForSentFlag=0;
                      P1IE|=BIT2;      //开手操器中断
                      AutoSendForHander=Off;
                      AutoWakeFlag=Off;
                      WakeSignFlag=Off;
                      
                      
                      WriteCommand(0xA5);
                      WriteCommand(0xAE);
                      P5DIR=0XFF;
                      P5OUT=0;
 
                      InitSysForStandby();
                      
                      
                      P2OUT&=~BIT2;        
                      P2OUT&=~BIT1;      
                      P2OUT&=~BIT0;
                      SleepCount=0;
                      
                    /*  以下程序解决偶尔按键唤不醒问题原因：刚按按键就进入休眠状态，P2.7中断来不及打开*/
                      
                      KeyDelayCount=0;
                      KeyPutStu=Off;
                      P2IES=0X80;                //下降沿触发
                      P2IFG=0;
                      P2IE=0X80;                 //开P2.7中断
                   
}







