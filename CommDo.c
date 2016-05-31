
#include <io430.h>
#include <in430.h>
#include <intrinsics.h>
#include "Predefined.h"
#include "flashWR.h"
#include"DispDataDo.h"
#include "Key.h"
#include "CommDo.h"



/***************************从机MODBUS数据上发格式***************************************************************************************


********************************************************************************************************************************/
                                 
                                     
 union
 {
   uchar  f_byte[4];
   uint   f_int;
   
 }float_byte;
                                    




void  CommSentData(uchar *rxdata,uchar *txdata,uchar *ramppt)

{
 uint  md_crc;
 uchar comii;
  
  
SentOrNot=0;

switch(*(rxdata+1))
 {
   case 0xF0:
            if(*(rxdata+9)==0x30)                         //模块读成功
             {
               *(ramppt+0X1a)=*(rxdata+10);//PID1
               *(ramppt+0X1b)=*(rxdata+11);//PID2
               *(ramppt+0X1c)=*(rxdata+12);//PID3
               *(ramppt+0X1d)=*(rxdata+13);//PID4
               *(ramppt+0X1e)=*(rxdata+14);//UID1
               *(ramppt+0X1f)=*(rxdata+15);//UID2
               
               *(ramppt+0X10)=*(rxdata+17);//模块功率
               
               if(*(rxdata+16)==*(ramppt+0X16))  //非正常关机(信道还未切换回来前就关机)时,开机后恢复查询信道
               {
                 RecoverFlag=On;
               }
               else
               {
               *(ramppt+0X0e)=*(rxdata+16);//模块信道
               RefreshAfterRead=On;
               }
               
               if((MBDataReadFlag==Ready)&&(*ramppt==Bakuped))//定时读且参数已备份才比较
               {
                 
                     MBDataReadFlag=Off;
                     
                     RDFlash ((uchar *)0x222,(uchar *)0x1022,30);//重读备份区数据
                     
                     for(comii=0;comii<6;comii++)
                     {
                             if(*(ramppt+0X1a+comii)!=*(ramppt+0X3a+comii))
                             {
           
                               ConfigStu=On;
                               StuCount=0;
                               IDSetFlag=On;
                               
                               break;
           
                             }
                            
                     }
 
               }
              
          
             }
             else if((*(rxdata+9)==0x31)&&(*(rxdata+10)==0xCC))//模块配置成功，存
             {
              
              
               *(ramppt+0X1a)=*(rxdata+3);//PID1
               *(ramppt+0X1b)=*(rxdata+4);//PID2
               *(ramppt+0X1c)=*(rxdata+5);//PID3
               *(ramppt+0X1d)=*(rxdata+6);//PID4
               *(ramppt+0X1e)=*(rxdata+7);//UID1
               *(ramppt+0X1f)=*(rxdata+8);//UID2
              
               if(ReportFlag==On)
               {
      
                 //ReportFlag=Off;  
                 AutoSentFlag=1;
                 SendTimes=3;               //主动上报次数
                //  SendTimes=1;               //主动上报次数
                 TimeForSentFlag=1;         //主动上报
               }
               else
               {
                 
               if(RecoverFlag==On)
                      RecoverFlag=Off;
               
               WRFlash ((uchar *)0x200,(uchar *)0x1000,64);
               delay_ms(10);
               RDFlash ((uchar *)0x200,(uchar *)0x1000,64);
               }
             // SentOrNot=1;
             // *(txdata+11)=0x03;
             // CommNormalData(txdata,ramppt);
              //AutoSentFlag=1;             //参数配置成功主动上报数据给基站
              //delay_ms(1);
             }
            else if((*(rxdata+9)==0x32)&&(*(rxdata+10)==0xCC))//模块PID配置成功
             {
               *(ramppt+0X1a)=*(rxdata+3);//PID1
               *(ramppt+0X1b)=*(rxdata+4);//PID2
               *(ramppt+0X1c)=*(rxdata+5);//PID3
               *(ramppt+0X1d)=*(rxdata+6);//PID4
               *(ramppt+0X1e)=*(rxdata+7);//UID1
               *(ramppt+0X1f)=*(rxdata+8);//UID2
               
                           
               *(ramppt+0X0e)=*(ramppt+0X2e);       //恢复信道 
               *(ramppt+0X10)=*(ramppt+0X30);       //恢复功率
                
                if(RecoverFlag==On)
                      RecoverFlag=Off;
                if(IDSetFlag==On)
                      IDSetFlag=Off;
                WRFlash ((uchar *)0x200,(uchar *)0x1000,64);
                delay_ms(10);
                RDFlash ((uchar *)0x200,(uchar *)0x1000,64);
                
                
             }
            else  
             {
               
             _NOP();
             }
            
            break;
   case 0x38:
            
              comii=*(rxdata+2);//取出帐长度
              
              md_crc=CrcCheck((comii-9),(rxdata+10));		      //主机读数据crc计算
   
              float_byte.f_byte[0]=*(rxdata+comii+1);

              float_byte.f_byte[1]=*(rxdata+comii+2); 
              
              SentOrNot=1;
             if(md_crc==float_byte.f_int)	           //数据信息区crc值正确
              {
                
                switch(*(rxdata+11))
                 {
                   case 0x03:
                   case 0x53:
                             *(txdata+11)=*(rxdata+11);
                             ReadIDCount=0;
                             MBDataReadFlag=Off;      //正常收发,取消定时读
                             CommNormalData(txdata,ramppt);
                             break;
                   case 0x10:                     //基站写寄存器
                   case 0x60:                     //手操器写寄存器
                     
                             *(ramppt+0x03)=*(rxdata+17);//车间号
                             *(ramppt+0x02)=*(rxdata+18);
                             *(ramppt+0x05)=*(rxdata+19);//责任区
                             *(ramppt+0x04)=*(rxdata+20);
                             *(ramppt+0x07)=*(rxdata+21);//班组区
                             *(ramppt+0x06)=*(rxdata+22);
                                  
                              *(ramppt+0X08)=*(rxdata+24);//垮号
                              *(ramppt+0X0a)=*(rxdata+25);//排号 
                              *(ramppt+0X0c)=*(rxdata+26);//窖号 
       
                              
                              if((*(rxdata+10)==0xBA)&&(*(rxdata+11)==0x60))              //限手操器高级用户改写
                              {
                                      if(*(ramppt+0X16)!=*(rxdata+23))//修改信道
                                                 *(ramppt+0X16)=*(rxdata+23);
                                  
                                      if(*(ramppt+0X0e)!=*(rxdata+27))
                                       {
                                      *(ramppt+0X0e)=*(rxdata+27);//模块信道
                                       ConfigStu=On;
                                       StuCount=0;
                                       }
                                      if(*(ramppt+0X10)!=*(rxdata+28))
                                       {
                                       *(ramppt+0X10)=*(rxdata+28);//模块功率
                                        ConfigStu=On;
                                        StuCount=0;
                                       }
       
                                       if((*(rxdata+29)!=0)||(*(rxdata+30)!=0))
                                       {
                                        *(ramppt+0x13)=*(rxdata+29);//采样周期
                                        *(ramppt+0x12)=*(rxdata+30);

                                       }
                                       if((*(rxdata+31)!=0)||(*(rxdata+32)!=0))
                                       {                            
                                         *(ramppt+0x15)=*(rxdata+31);//持续工作时间
                                         *(ramppt+0x14)=*(rxdata+32);
                                       }
                             
                              }
                             
                             
                             
                             
                             WRFlash ((uchar *)0x200,(uchar *)0x1000,64);
                             delay_ms(10);
                             RDFlash ((uchar *)0x200,(uchar *)0x1000,64);
                            // delay_ms(10);
                             
                             DataRefreshFlag=On;
                             
                             *txdata=0x7E;
                             *(txdata+1)=0x30;
                             *(txdata+2)=0x15;//字节长=总长-5
      
                             *(txdata+3)=0xFF;
                             *(txdata+4)=0xFF;
                             *(txdata+5)=0xFF;
                             *(txdata+6)=0xFF;
                             *(txdata+7)=0xFF;
                             *(txdata+8)=0xFF;    //广播给所有基站
                             *(txdata+9)=0x02;    //转发应答指令
/**********************************************/
                             *(txdata+10)=*(rxdata+10);//0xAB或0xBA

                             *(txdata+11)=*(rxdata+11);//写寄存器功能码0x10或0x60
                             *(txdata+12)=0x10;
                             *(txdata+13)=0x03;       //起始寄存器地址0x1003
                            
                             *(txdata+14)=0x00;
                             *(txdata+15)=*(rxdata+15);//写寄存器的数目
                             
                             *(txdata+16)=*(ramppt+0X1a);
                             *(txdata+17)=*(ramppt+0X1b);
                             *(txdata+18)=*(ramppt+0X1c);
                             *(txdata+19)=*(ramppt+0X1d);
                             *(txdata+20)=*(ramppt+0X1e);
                             *(txdata+21)=*(ramppt+0X1f); 
                             
                            
                             float_byte.f_int=CrcCheck(12,(txdata+10));		      //主机读数据crc计算
   
                             *(txdata+22)=float_byte.f_byte[0];

                             *(txdata+23)=float_byte.f_byte[1]; 
              

/*****************************************************/
                            *(txdata+24)=0xCC;
                            *(txdata+25)=0xCC;
                            SentNum=26;
                            
                            
                            break;
                 case 0x70:
                            switch(*(rxdata+12))
                            {
                            case 0x01:
                              DataBak(ramppt);
                              break;
                            case 0x02:
                              RDFlash ((uchar *)0x222,(uchar *)0x1022,30);//读备份区数据
                              DataRecover(ramppt);
                              ConfigStu=On;
                              StuCount=0;
                              IDSetFlag=On;
                              DataRefreshFlag=On;
                              break;
                            case 0x03:
                              PVPT[0]=*(rxdata+13);
                              PVPT[1]=*(rxdata+14);
                              PVPT[2]=*(rxdata+15);
                              break;
                            case 0x04:
                               //RDFlash ((uchar *)0x222,(uchar *)0x1022,30);//读备份区数据
                               
                               *(ramppt+0X3a)=*(rxdata+13);//PID1
                               *(ramppt+0X3b)=*(rxdata+14);//PID2
                               *(ramppt+0X3c)=*(rxdata+15);//PID3
                               *(ramppt+0X3d)=*(rxdata+16);//PID4
                               *(ramppt+0X3e)=*(rxdata+17);//UID1
                               *(ramppt+0X3f)=*(rxdata+18);//UID2//新的ID码
                               
                               *(ramppt+0X2e)=*(rxdata+19);//模块信道
                               *(ramppt+0X30)=*(rxdata+20);//模块功率
                            
                               ConfigStu=On;
                               StuCount=0;
                               IDSetFlag=On;
                               DataRefreshFlag=On;
                              break;
                            }
                            WRFlash ((uchar *)0x200,(uchar *)0x1000,64);
                            delay_ms(10);
                            RDFlash ((uchar *)0x200,(uchar *)0x1000,64);
                            
                            delay_ms(10);
                            
                            WRFlash ((uchar *)0x280,(uchar *)0x1080,33);
                            delay_ms(10);
                            RDFlash ((uchar *)0x280,(uchar *)0x1080,33);
                           
                            
                              *txdata=0x7E;
                             *(txdata+1)=0x30;
                             *(txdata+2)=0x1a;//字节长=总长-5
      
                             *(txdata+3)=0xFF;
                             *(txdata+4)=0xFF;
                             *(txdata+5)=0xFF;
                             *(txdata+6)=0xFF;
                             *(txdata+7)=0xFF;
                             *(txdata+8)=0xFF;    //广播给所有基站
                             
                             *(txdata+9)=0x02;    //转发应答指令
/**********************************************/
                             *(txdata+10)=0xAB;
                             
                             *(txdata+11)=0x70;
                             
                             *(txdata+12)=*(rxdata+12);
                             
                             *(txdata+13)=*(rxdata+13);    
                             *(txdata+14)=*(rxdata+14);
                             *(txdata+15)=*(rxdata+15);
                             *(txdata+16)=*(rxdata+16);
                             *(txdata+17)=*(rxdata+17);
                             *(txdata+18)=*(rxdata+18);
                             *(txdata+19)=*(rxdata+19);
                             *(txdata+20)=*(rxdata+20);
                             
                             *(txdata+21)=*(ramppt+0X1a);
                             *(txdata+22)=*(ramppt+0X1b);
                             *(txdata+23)=*(ramppt+0X1c);
                             *(txdata+24)=*(ramppt+0X1d);
                             *(txdata+25)=*(ramppt+0X1e);
                             *(txdata+26)=*(ramppt+0X1f); 
                             
                            
                             float_byte.f_int=CrcCheck(17,(txdata+10));		      //主机读数据crc计算
   
                             *(txdata+27)=float_byte.f_byte[0];

                             *(txdata+28)=float_byte.f_byte[1]; 
              

/*****************************************************/
                            *(txdata+29)=0xCC;
                            *(txdata+30)=0xCC;
                            SentNum=31;
                            
                            break;
      
  
                 }
  
                
              }
             else                   //信息区crc校验不正确
              {
                             *txdata=0x7E;
                             *(txdata+1)=0x30;
                             *(txdata+2)=18;     //字节长=总长-5
                            
                             *(txdata+3)=0xFF;
                             *(txdata+4)=0xFF;
                             *(txdata+5)=0xFF;
                             *(txdata+6)=0xFF;
                             *(txdata+7)=0xFF;
                             *(txdata+8)=0xFF;    //广播给所有基站
                             
                             *(txdata+9)=0x02;    //转发应答指令
                          /*****************************************信息区*****************************/
                             *(txdata+10)=0xAB;
                             *(txdata+11)+=0x80;
                             *(txdata+12)=0x04;                   //crc16校验错误
                             
                             *(txdata+13)=*(ramppt+0X1a);          //PID
                             *(txdata+14)=*(ramppt+0X1b);
                             *(txdata+15)=*(ramppt+0X1c);
                             *(txdata+16)=*(ramppt+0X1d);
                             *(txdata+17)=*(ramppt+0X1e);         //UID
                             *(txdata+18)=*(ramppt+0X1f);
                             
                             float_byte.f_int=CrcCheck(9,(txdata+10));		      //主机读数据crc计算
   
                             *(txdata+19)=float_byte.f_byte[0];
                             *(txdata+20)=float_byte.f_byte[1]; 
	                    
                          /*****************************************************************************/
                            *(txdata+21)=0xCC;
                            *(txdata+22)=0xCC;
                            
                            SentNum=23;
              }
               
          
   
   
            break;
   case 0x30:                                                   
            if((*(rxdata+9)==0x01)&&(*(rxdata+10)==0xCC))      //模块主动转发应答（给单片机）
             {
                   if(AutoSentFlag==1)
                    {
                      SendTimes--;
               
                      if(SendTimes==0)
                       {
                          AutoSentFlag=0; 
                          
                          LedStuOff;
                        
                           if((WBStu==Active)&&((P4OUT&BIT5)==0))//手动激活状态
                             {
                             StuCount=0; 
                             WDTCTL=WDTPW+WDTHOLD;
                             
                             NormalDisp();
                             
                             WDTCTL=WDTPW+WDTHOLD;
                             }
                            
                            ReportFlag=Off;
                           
                            if(AutoSendForHander==Off) //在给基站上报参数后立即恢复信道
                             {
                             
                             RecoverFlag=On;
                             delay_ms(600);
                             ConfigFlag=1;            //立即恢复正常通道 
                             }    
                       }
                      else
                       {
                        TimeForSentFlag=1;
                       }
                 
                    }
               
             }
            //LedAOff;
            break;
   
   
 }





   if(SentOrNot==0)
    {
        for(md_crc=0;md_crc<47;md_crc++)
        {
         *(rxdata+md_crc)=0;             //清接收发送数组
        }
     
     
     
    }
    
    
}


void CommNormalData(uchar *txdata,uchar *ramppt)// 主动上传数据
{
  
      *txdata=0x7E;
      *(txdata+1)=0x30;//转发应答
      *(txdata+2)=0x2A;
      
      *(txdata+3)=0xFF;
      *(txdata+4)=0xFF;
      *(txdata+5)=0xFF;
      *(txdata+6)=0xFF;
      *(txdata+7)=0xFF;
      *(txdata+8)=0xFF;    //广播给所有基站
      
      *(txdata+9)=0x02;    //转发应答指令
      /******************************************信息区**********************************************************/
      *(txdata+10)=0xAB;
    //  *(txdata+11)=0x53;//功能码
      *(txdata+12)=0x1E;//字节总数
      
      *(txdata+13)=*(ramppt+0X1a);//PID1
      *(txdata+14)=*(ramppt+0X1b);//PID2
      *(txdata+15)=*(ramppt+0X1c);//PID3
      *(txdata+16)=*(ramppt+0X1d);//PID4
      
      *(txdata+17)=*(ramppt+0X1e);//UID1
      *(txdata+18)=*(ramppt+0X1f);//UID2
      
      
      
      *(txdata+19)=*(ramppt+0x03);   //车间号
      *(txdata+20)=*(ramppt+0x02);
      
      *(txdata+21)=*(ramppt+0x05);   //责任区 
      *(txdata+22)=*(ramppt+0x04);
      
      *(txdata+23)=*(ramppt+0x07);   //班组区    
      *(txdata+24)=*(ramppt+0x06);
      
      
        
      *(txdata+25)=0xFF;
      *(txdata+26)=*(ramppt+0X08);//垮号
      
      *(txdata+27)=*(ramppt+0X0a);//排号  
      *(txdata+28)=*(ramppt+0X0c);//窖号 
      
      *(txdata+29)=*(ramppt+0X0e); //模块信道 
      *(txdata+30)=*(ramppt+0X10); //模块功率 
      
      *(txdata+31)=*(ramppt+0x13);//采样周期
      *(txdata+32)=*(ramppt+0x12);
      
      *(txdata+33)=*(ramppt+0x15);   //持续工作时间
      *(txdata+34)=*(ramppt+0x14);
      
    
      *(txdata+35)=PV[0]>>8;               //上层温度 
      *(txdata+36)=PV[0];
					
      *(txdata+37)=PV[1]>>8;               //中层温度
      *(txdata+38)=PV[1];
					
      *(txdata+39)=PV[2]>>8;                //下层温度
      *(txdata+40)=PV[2];
   
  
      
      *(txdata+41)=0xBA;   //特殊标识
     
      *(txdata+42)=BatStu;//电池状态
        
      float_byte.f_int=CrcCheck(33,txdata+10); 
      
      *(txdata +43)=float_byte.f_byte[0];	        //crc低字节在前
      *(txdata +44)=float_byte.f_byte[1];	        //crc低字节在前
      
      /***************************************信息区***********************************************************/         
      
      
      *(txdata+45)=0xCC;
      *(txdata+46)=0xCC;
      
      
      SentNum=47;
  
  
  
  
}





void  ConfigDataWrite(uchar *txdata,uchar *ramppt)
{
   
      *txdata=0x7E;
      *(txdata+1)=0xF8;
      *(txdata+2)=0x0F;
      
      *(txdata+3)=0x99;
      *(txdata+4)=0x99;
      *(txdata+5)=0x99;
      *(txdata+6)=0x99;
      *(txdata+7)=0x99;
      *(txdata+8)=0x99;
      
      *(txdata+9)=0x31;//写配置指令
      
      *(txdata+10)=*(ramppt+0X1a);
      *(txdata+11)=*(ramppt+0X1b);
      *(txdata+12)=*(ramppt+0X1c);
      *(txdata+13)=*(ramppt+0X1d);     //PID（无法更改）
      *(txdata+14)=*(ramppt+0X1e);  //UID1
      *(txdata+15)=*(ramppt+0X1f);  //UID2   
      
      *(txdata+18)=0xCC;
      *(txdata+19)=0xCC;

      SentNum=20; 
 
      if(ReportFlag==On)
      {
      *(txdata+16)=*(ramppt+0X16); //模块上报信道
      *(txdata+17)=7; //模块功率
      
      }
      else
      {
      *(txdata+16)=*(ramppt+0X0e); //模块信道
      *(txdata+17)=*(ramppt+0X10); //模块功率
              if(IDSetFlag==On)
              {
               *(txdata+2)=0x14;//字节数多5个
               *(txdata+9)=0x32;//写PID配置指令
               
                *(txdata+10)=*(ramppt+0X3a);
                *(txdata+11)=*(ramppt+0X3b);
                *(txdata+12)=*(ramppt+0X3c);
                *(txdata+13)=*(ramppt+0X3d);     //PID（无法更改）
                *(txdata+14)=*(ramppt+0X3e);  //UID1
                *(txdata+15)=*(ramppt+0X3f);  //UID2   
                                 
                *(txdata+16)=*(ramppt+0X2e);       //恢复备份信道 
                *(txdata+17)=*(ramppt+0X30);       //恢复备份功率
               
                *(txdata+18)=0xA2;
                *(txdata+19)=0x2A;
                *(txdata+20)=0x3A;
                *(txdata+21)=0x5B;
                *(txdata+22)=0x4C;//五个固定字节

                *(txdata+23)=0xCC;
                *(txdata+24)=0xCC;
               
                SentNum=25;
              }
      }
      
 

}


void  ConfigDataRead(uchar *txdata)
{
   
      *txdata=0x7E;
      *(txdata+1)=0xF8;
      *(txdata+2)=0x07;
      
      *(txdata+3)=0x99;
      *(txdata+4)=0x99;
      *(txdata+5)=0x99;
      *(txdata+6)=0x99;
      *(txdata+7)=0x99;
      *(txdata+8)=0x99;
      
      *(txdata+9)=0x30;//读配置指令
      
      
      *(txdata+10)=0xCC;
      *(txdata+11)=0xCC;
      
      
      SentNum=12;
 

}

/***********************************************************************
modbus crc校验，采用半字节算法
入口参数：校验的字节数len，数据数组
出口参数：CRC
***********************************************************************/ 
uint const crc_table[16] =
    {
	0x0000, 0xcc01, 0xd801, 0x1400, 0xf001, 0x3c00, 0x2800, 0xe401, 
	0xa001, 0x6c00, 0x7800,0xb401, 0x5000, 0x9c01, 0x8801, 0x4400
    };

uint  CrcCheck(uchar len,uchar *ptr)
{
     uint    crc = 0xffff;
     uchar   crc_L4;

        while( len-- )
        {
            crc_L4 = (uchar)(crc &0x000f);
            crc = crc >> 4;
            crc = crc ^ crc_table[ crc_L4 ^ (*ptr & 0x0f)];
            crc_L4 = (uchar)(crc &0x000f);
            crc = crc >> 4;
            crc = crc ^ crc_table[ crc_L4 ^ (*ptr >> 4)];
            ptr++;  
        }  
	    
		return(crc);
}



