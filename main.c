
/******************************************************************************************************************************
*******************************************************************************************************************************
ver1.1:
1��ȡ���˿�ţ��źţ��Ѻŵ����ƣ����÷�Χ00-99
2���������ϵ��ţ��źţ��Ѻ����÷�Χ�ļ�⣬��Ϊ00-99
3�������˹���ʱ������õ�λ���� WorkTime(����) ��Ϊ WorkTime(*10��)
4, �����˼���Ѻ����ʾʱ�䣬WorkTime(*10��)  1-1999 (*10��)
5, ��������ʱ�޷����ѵ�BUG
6���汾�Ÿ�ΪVer1.1
7, �����ڵȴ��ֲ���������ʮ�����ڣ������ֶ�������޷���������״̬
8�����ӱ��ݱ�־Bakuped,�������ޱ�������»ָ���Ч�Ĳ�����
9�����̼���󣬼���Ƶ�����ʱ��
10���ӳ����ϵ�ʱ���������±䡱����ʾʱ�䣬ͬʱȡ���ϵ�ǿ��ģ���������״̬�����ڶ�ȡģ�����
11,�ӳ��˿�,�ػ������������ʱ��,��3���ӳ���7������.


                                        2012-10-25
ver1.2:
1���汾�Ÿ�ΪVer1.2
2,��ʼ�����������룬�ŵ������ʣ�����ԭ����ֵ��
3,����ÿ1Сʱ�Զ�������,���Ƚ�(���ѱ���������)ID��,����ͬ��ѱ�����ID����,������дPIDָ��
4,����дPIDָ��0x32;
5,�����ֲ���дPIDָ��,
6,�����ֲ���,���ָ̻�����ʱ,дPIDָ��.
7,�޸���ר��ָ���ʽ.
3��ȡ���ֶ��ػ�.
9��������Bakuped�Ķ��塣
10.�����˵͵�ѹ�Զ��ػ�(С��2.6V)
11������ʱ���Ѳ���ʱ�䣬���ݲ���ʱ���Ϊ10���ӣ��������Һ��
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
 LedDelayCount=20;//�����󣬵�����ʱ��20*60ms
 
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

 
 
LcdTwoByteWrite(25,Line3,4 ,WXWB);  //�����±�
 
LcdCharWrite(28,Line2,8,VERSION) ; //�汾��Ϣver 1.1M

 //  LcdTwoByteWrite(1,Line3,7 ,BAITEGONGKONG);  //���ع���+�ո�
  
 //LcdCharWrite(0,Line2,15,FBTC) ;           //FBTC+�ո�
 
 //delay_ms(1150);//��ʱʱ���ѵ������ı佫Ӱ���ϵ�ʱ��ģ���ȡ

 delay_ms(1600);//��ʾ���ӳ�ģ���ϵ�ʱ�䣬���ڶ�ȡ����
 
}



void main(void)

{ 
   
   _DINT();                      //��ȫ���ж�
   
   WDTCTL=WDTPW+WDTHOLD;         //�ؿ��Ź�
 
   
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
   
   delay_ms(20);//����
   
   if((KeyTemp==0)&&((P2IN&0X80)==0))
    {
      DataTemp=0;
      do
       {
         delay_ms(100);
         DataTemp++;
         if(DataTemp==20)        //������ѹ����6������
                      break;
       }
      while((P2IN&0X80)==0);
      
      if(DataTemp>=20)
       {
        LcdInit();
        LedAOn;
        LcdTwoByteWrite(0,Line3,7 ,BACKUPING);//�����ָ��С���
        
        delay_ms(500);
  
        DataRecover888(&StartRAM);    //�ָ�����
        
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
        
        P2IES=0X80;                //�½��ش���
        P2IFG=0;
        P2IE=0X80;                 //��P2.7�ж�
        
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
                                 P2OUT&=~BIT0;     //��һ·��������
                                 
                                 break;
                        case 2:
                                 P2OUT&=~BIT2;        
                                 P2OUT|=BIT1;      
                                 P2OUT&=~BIT0;     //�ڶ�·��������
                                 
                                
                                 break;           
                        case 3:
                                 P2OUT|=BIT2;        
                                 P2OUT&=~BIT1;      
                                 P2OUT&=~BIT0;    //����·��������
                               
                                 break;
                        default:
                                  _NOP();
                         }
    
                   }
                  
                  
      
  
   
   
  /*************************************************************/  
    if(KeyTestTime==On)				    //ÿ��һ��ʱ����м���ɨ��
	 {
	 
	 KeyTestTime=Off;
	 KeyTemp1=P2IN;
	 KeyTemp1&=0x68;				    //����ֵ
	 if(KeyValue==KeyTemp1)
		 {
		      if(KeyChange==1)
		         {
		         ramstart=&StartRAM;
		         Key(KeyValue);	    //���̴���
			 }
		      
		 }
          else
		 {
		 KeyValue=KeyTemp1;
		 KeyChange=1;
		 Key30s=750;
			 
		 }
         }
 
  /****************************ģ�����ô���*********************************/ 
         if(MBDataReadFlag==1)
         {
           
           MBDataReadFlag=Ready;
           
           MBWake;
           WirelessStu=On;
           delay_ms(20);//������Ҫһ��ʱ��
           
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
            delay_ms(20);//������Ҫһ��ʱ��
             
            ConfigFlag=0;
            ConfigDataWrite(CommSent,&StartRAM);
            
            ME1=UTXE0;
            _NOP();
            _NOP();
            CommNum=0;
            U0TXBUF=CommSent[0];
          }
  /****************************���մ���*********************************/    
         if(RiEndFlag==1)
	 {

	      CommSentData(CommReceive,CommSent,&StartRAM);
 
              if(SentOrNot==1)
               {
               ME1=UTXE0;                //ʹ�ܷ���
               _NOP();
               _NOP();
               CommNum=0;
               U0TXBUF=CommSent[0];       //����ͨѶ״̬,
                    
                }
              else
               {
                 
                ME1=URXE0;          //ʹ�ܽ��� 
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
              delay_ms(25);         //����+���ͼ�� ��Ҫһ��ʱ��
              
              CommSent[11]=0x03;
              if(AutoSendForHander==On)
                               CommSent[11]=0x53;
 
              CommNormalData(CommSent,&StartRAM);
  
               ME1=UTXE0;          //ʹ�ܷ���
               _NOP();
               _NOP();
               
               CommNum=0;
               
               U0TXBUF=CommSent[0]; 
               
               TimeForSentFlag=0;
              
              
       }
       
 /****************************���ʹ���*********************************/ 
	    if(TiEndFlag==1)
	    {
	           uchar k;
                  
                    for(k=0;k<47;k++)
	              {
	                  CommSent[k]=0;
	              }
                 
                   CommNum=0;
		   ME1=URXE0;          //ʹ�ܽ��� 
                      
	           TiEndFlag=0;
                   
              
	     }
 /****************************��ʱ����*********************************/ 
	    if(OverTime==1)					//�쳣��ʱ����
	    {

	     uchar k;
			   for(k=0;k<47;k++)
			      {
			      CommSent[k]=0;
                              CommReceive[k]=0;
			      }
	
	  
	    CommNum=0;
            OverTime=0;
            ME1=URXE0;          //ʹ�ܽ���
            MBSleep;             //�쳣�ر�ģ��
            _NOP();
            _NOP();
            WirelessStu=Off;
              
              
     
	    }
   /******************��ص�ѹAD12ת������***************************************/  
  
    if(((ADC12IFG&0X0004)!=0)&&(AD12Flag==On))      //����ɼ�һ�ε����Ϣ
      
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
         
          else if((BatVoltage >=1.22)&&(BatVoltage < 1.28)) //﮵�ص�ѹ����3.45V
                 {
                   BatStu=2;
                   
                   LowBatTest=0;
                 }
          else if((BatVoltage >=1.15)&&(BatVoltage < 1.22))//﮵�ص�ѹ����3.3V
                 {
                   BatStu=1;
                   LowBatTest=0;
                 }
          else if((BatVoltage >=1.00)&&(BatVoltage < 1.15))//﮵�ص�ѹ����3.0V
                {
                  BatStu=0;
                  LowBatTest=0; 
                  
                }
          else   //﮵�ص�ѹ����2.6V,ֱ�ӹػ�
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
                                         LcdTwoByteWrite(8,Line3,6 ,POWEROFF);//���ڹػ�����
                                         
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
       
                                         LPM4;          //�ػ���������ߣ�
                       
                      }
                 }
         
           //BatStu=3;//���һ����﮵��       
          
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



#pragma vector=PORT1_VECTOR      //ģ���·������ж�
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
  //delay_ms(10);                            //����
  MBWakePort=P1IN&0X84;
  switch(MBWakePort)
   {
     case 0x84:                       //Զ�̲�ѯʱ/�ֲ�������ʱ(�뿪���Կ���)
     case 0x80:                       //1,�ֲ�������ʱ(δ�뿪���Կ���)  2,Զ�̲�ѯ���ֲ���ͬʱ����ʱ,Զ�̲�ѯ����
               WirelessStu=On;
               AutoWakeFlag=On;
               //LedAOn;//t
               LedStuOn;
              if(WBStu==Standby)
              {
               TB0DelayCount=3;//3*200ms�ر�
               LPM3_EXIT;
                     
              }
              else
               {
                 WakeDelayCount=10;//��ʱ10*60ms
                 WakeDelayFlag=On;
               }
              
     break;

     case 0x00:                       //�ֲ����ӽ�ʱ
              P1IE&=~BIT2;          //���ֲ����ж�
              ReportFlag=On;
              ConfigFlag=1;
              AutoSendForHander=On;
              //LedAOn;//t
              LedStuOn;
               if(WBStu==Standby)
               {
              
                // TB0DelayCount=40;//40*200ms�ر�
                 TB0DelayCount=75;//75*200ms�ر�
                 LPM3_EXIT;
               }
              else
               {
                 StuCount=0;
                 //WakeDelayCount=130;//��ʱ130*60ms,8����Զ��ر�
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
  //delay_ms(10);                            //����
  KeyTemp=P2IN&0X80;
   
  
  if(KeyTemp==0)
  {
    
    KeyPutStu=On;
    P2IE=0;                                //�ر��ж�
    KeyDelayCount=0;
        // if((WBStu==PowerOff)||(WBStu==Standby))
       if(WBStu==PowerOff)
         {
           LPM4_EXIT;
           _EINT();
           TBCTL=TBSSEL_1+MC_2;//ACLK,����ģʽ
           TBCCTL1|=CCIE;
           TBR=0;
           TBCCR1=1966;            //60ms�ж�һ��
           TBCCTL0=0;              //��TBCCR0�ж�
           
           P2OUT&=~BIT2;        
           P2OUT&=~BIT1;      
           P2OUT&=~BIT0;
          
           LPM3;        //��ACLK
         }
      if(WBStu==Standby)
       {
        //LedAOn;//t 
        TACTL=0;    
        TACCTL0=0;       
        TACCTL1=0;
        TACCTL2=0;
        
        TBCTL=TBSSEL_1+MC_2;//ACLK,����ģʽ
        TBCCTL1|=CCIE;
        TBR=0;
        TBCCR1=1966;             //60ms�ж�һ��
        TBCCTL0=0;              //��TBCCR0�ж� 
         
         
       }
  }
 
  
}
/***************************�Զ�����(TimeB0�ж�)*****************************************************/

/**************************��ADת������ؼ�⣬Һ���رգ����̹ر�******************************************************/




#pragma vector=TIMERB0_VECTOR
__interrupt void TimerB0Int (void)
 {
   unsigned long tb0data;
   
   WDTCTL=WDT_ARST_1000;
   
    if(WakeSignFlag==Off)               //����״̬�����յ�����ֹͣ����
    {
              SleepCount++;
              ReadIDCount++;
    }
    
    if(ReadIDCount>=18000)        //1Сʱ���Ҷ�һ��ID��,
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
   LedDelayCount=10;//�Զ����Ѻ󣬼��������ʱ��10*60ms
   
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
                  P1IE|=BIT2;              //���ֲ����ж�    
                  ReportFlag=Off;
                  RecoverFlag=On;
                  ConfigFlag=1;            //�ָ�����ͨ�� 
                  SleepCount=0;
                  
                  WorkTimeSecond=5;
  
                  LedStart=On;
                  LedDelayCount=10;//�ȴ�ʱ����Զ�����ɼ��ŵ��ָ������������ʱ��10*60ms
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


/***************************ģʽת��(TimeB�ж�)*****************************************************/

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
                       LedStuOff;           //ʱ�䵽���رռ����
                       LedStart=Off;
                      }
                 } 
                 if(WakeDelayFlag==On)
                  {
                     
                     WakeDelayCount--;
                     if(WakeDelayCount==0)  //����״̬,��ʱʱ�䵽;
                      {
                           if(DataRefreshFlag==On)//�ֶ�����״̬
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
                            P1IE|=BIT2;      //���ֲ����ж�
                            AutoSendForHander=Off;
                            ReportFlag=Off;
                            RecoverFlag=On;
                            StuCount=0;
                            ConfigFlag=1;            //�ָ�����ͨ�� 
                           }
                        
                        }
                   
                  }
                                                       
                 TBCCTL1&=~CCIFG;
                 KeyTestTime=On;           //key1-key4���ɨ��ʱ��
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
                 TBCCR1+=1966;                  //60ms�ж�
                 if(KeyPutStu==On)             //������ѹ�����ʱ����    
                  {
                    KeyTemp=P2IN&0X80;
                    if(KeyTemp==0)                //��������ְ���״̬
                     {
                       
                        KeyDelayCount++;
                        StuCount=0;              //��������ְ���״̬ʱ�������������ģʽ
                        if(KeyDelayCount >=120)    //��������ʱ��:7������
                        {
                         KeyDelayCount=0;
                         KeyPutStu=Off;
                         P2IES=0X80;                //�½��ش���
                         P2IFG=0;
                         P2IE=0X80;                 //��P2.7�ж�
                           switch(WBStu)
                           {
                            case PowerOff:                         //����,����
                              
                                           _NOP();
                                           _NOP();
                                           
                                           
                                           LPM3_EXIT;
                                           
                                           WDTCTL=WDTPW+WDTHOLD;
                                           
                                           InitSysForActive();
                                           
                                           LcdInit();
                                          
                                           SPCInit();
                                          
                                           NormalDisp();
                                           
                                           StuCount=0;
                                           WorkTimeSecond=15;        //������ʾʱ���ӳ�
                                           WBStu=Active;
                                         
                                           
                                           break;
                            
                          case Standby:                            //�����ֶ�����
                                     
                                     LedAOn;
                                     LedStart=On;
                                     LedDelayCount=20;//����󣬼��������ʱ��20*60ms
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
                                         LcdTwoByteWrite(8,Line3,6 ,POWEROFF);//���ڹػ�����
                                         
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
                                         LPM4;          //�ػ���������ߣ�
                                           */
                                  
                          }
                        }
                        
                     }
                   
                    else
                     {
                      KeyDelayCount=0;
                      KeyPutStu=Off;
                      P2IES=0X80;                //�½��ش���
                      P2IFG=0;
                      P2IE=0X80;                 //��P2.7�ж�
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
                                     StuCount=0;                  //���¿�ʼ����״̬��ʱ,6���������ģ��
                                     //AutoSentFlag=1;
                                     WorkTimeSecond=WorkTime*5;
                                     LedStuOn;
                                     if((P4OUT&BIT5)==BIT5)//���Զ�����״̬
                                     {
                                     LedAOn;                   
                                     LcdInit();
                                     NormalDisp();                 //������ʾ,���Զ�����״̬
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
                                         
                                         
                                         P2IFG=0;                    //����������ε��ֱ���ϱ����������
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
                      case Standby:                            //�ֶ�����
                                     
                                     
                                     LedAOn;
                                     LedStart=On;
                                     LedDelayCount=20;//����󣬼��������ʱ��20*60ms
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
                                      AD12Flag=On;    //2��ɼ�������Ϣ
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
                       
                      
                       if(StuCount==3)              //6���ת�����ݴ���
                        {
                             LedStuOff;
                             
                             if(RefreshAfterRead==On)//��ģ������
                             {
                               RefreshAfterRead=Off;
                               NormalDisp();
                             }
                          
                             if(ReportFlag==Ready)  //�ϱ���ʱ�Զ�����������ʾ
                             {
                                ReportFlag=Off;
                                NormalDisp();
                             }
                             
                          
                             if(ConfigStu==On)        //��������״̬
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
                      
                       
                       if(StuCount >= WorkTimeSecond)      //�ģʽʱ�䵽(worktime*10�����10��)
                   
                        {
                         GoIntoSleepMode();
           
                         _EINT();
                         LPM3;                    //�Զ��������״̬
                        }
                 }
                               
                break;
     }
}


/***************************AD����(TimeA�ж�)******************************************************/

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

/***************************ͨѶ�������ж�******************************************************/
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
          
          TACTL=TASSEL_1+MC_1;  //ACLK,��ģʽ      2013-05-13
          TACCTL1&=~CCIFG;
          TACCTL1=CCIE;
          TAR=0;
          TACCR1=164;          //��5MS�ж�
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
                          ME1=UTXE0;          //ʹ�ܷ��ͣ�
                         
                        }
			*/
                       
	     }
     }
 
 }
   
   
   

/***************************ͨѶ�������ж�******************************************************/
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
       // ME1=URXE0;          //ʹ�ܽ���
	}
      else
        {
      
        U0TXBUF=CommSent[CommNum]; 
        }
    
    
  
 
 }


void  GoIntoActiveMode(void)//������������״̬
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


void  GoIntoSleepMode(void)   //�������״̬
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
                      P1IE|=BIT2;      //���ֲ����ж�
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
                      
                    /*  ���³�����ż����������������ԭ�򣺸հ������ͽ�������״̬��P2.7�ж���������*/
                      
                      KeyDelayCount=0;
                      KeyPutStu=Off;
                      P2IES=0X80;                //�½��ش���
                      P2IFG=0;
                      P2IE=0X80;                 //��P2.7�ж�
                   
}







