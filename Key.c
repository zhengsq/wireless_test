#include <io430.h>
#include <in430.h>
#include <intrinsics.h>
#include"Predefined.h"
#include"DispDataDo.h"
#include"LcdDriver.h"
#include"FlashWR.h"
#include "Key.h"


/******************************************************************************
              菜        单      树
*******************************************************************************
0工作态，1，参数显示（采样周期，工作时间）

（Ｆ１）参数设置
（Ｆ２）温度调校
（Ｆ３）恢复出厂设置
（Ｆ４）退出

（Ｆ１）参数设置
（Ａ0）　退 出　（30）
（Ａ１）车间号　（31）
（Ａ２）责任区　（32）
（Ａ３）班组号　（33）

（Ａ4）　垮号　（34）
（Ａ5）　排号　（35）
（Ａ6）　窖号　（36）
（Ａ7）　网络信道（37）

（Ａ8）　发射功率（38）
（Ａ9）　采样周期（39）
（ＡA）　工作时间（3A）
（AB)    修改信道（3B）

　
（Ｆ２）温度调校
（Ｂ0）　0：退出
（Ｂ1）　1：输入一　　（93，94）
（Ｂ2）　2：输入二　　（95，96）
（Ｂ3）　3：输入三　　（97，98）
(B4)     4: 同时

（Ｆ３）备份与恢复
（Ｃ0）　　0：退出　　　
（Ｃ1）　　1：备份　　　
（Ｃ2）　  2：恢复　
***********************************************************************************

*******************************************************************************/




void Key(uchar kv)
{
  
switch(kv)
{
case key_up:							 /*******************************key_up************************************/
             KeyChange=0;
            
			 switch(MenuStuNum)
			 {
                           /*
			 case 0x00:
                                    MenuStu=On;
                                    MenuStuNum=0x01;
                                    ClearLcdLine(Line1);
                                    ClearLcdLine(Line2);
                                    ClearLcdLine(Line3);
                                    ClearLcdLine(Line4);
                                    
                                  
                                    
                                    LcdTwoByteWrite(4,Line3,5, SAMPLETIME0);
                                    LcdTwoByteWrite(4,Line2,5, WORKTIME0);
                                   
                                    
                                    SetDataDisp(Line3,(signed int)StandbyTime,4);
                                    SetDataDisp(Line2,(signed int)WorkTime,4);
                                    
                         
		
			 break;
                         
                         case 0x01:
                                    NormalDisp();
                                    MenuStuNum=0;
                                    MenuStu=Off;
                                    
                         break;
                         */
                         case 0x31:
                         case 0x32:
                         case 0x33:                               //车间号，班组号，0-999   责任区0-9,　查询信道0-99,垮号00－99，排号0－9
                         case 0x34:
                         case 0x35:
                         case 0x36:  
                         case 0x37:
                         
                                 if(SetDataBit[SetBit] < 9)
                                               {
                                                SetDataBit[SetBit]++;
                                                LcdOneByteWrite(DigitalDspStart+SetBit*8,KeySetLine,SetDataBit[SetBit],1);
                                                }
                                 break;
                        
                   
                         case 0x38:
                                         if(SetDataBit[SetBit]<7)                   //发射功率限制在0-7
                                          {
                                          SetDataBit[SetBit]++;
                                          LcdOneByteWrite(DigitalDspStart+SetBit*8,KeySetLine,SetDataBit[SetBit],1);  
                                          }
                           
                         break;
                         case 0x3B:                                           //修改信道限制在100-123
                                        
                                        if(SetBit==2)
                                         {
                                            
                                                if(SetDataBit[SetBit]<2)                   
                                                 {
                                                 SetDataBit[SetBit]++;
                                                 LcdOneByteWrite(DigitalDspStart+SetBit*8,KeySetLine,SetDataBit[SetBit],1);  
                                                 }
                                          
                                         }
                                         else
                                          {
                                            if(SetDataBit[2]==2)
                                             {
                                                if(SetDataBit[SetBit]<3)                   
                                                 {
                                                 SetDataBit[SetBit]++;
                                                 LcdOneByteWrite(DigitalDspStart+SetBit*8,KeySetLine,SetDataBit[SetBit],1);  
                                                 }
                                             }
                                            else
                                             {
                                               if(SetDataBit[SetBit]<9)                   //限制在0-123
                                                 {
                                                 SetDataBit[SetBit]++;
                                                 LcdOneByteWrite(DigitalDspStart+SetBit*8,KeySetLine,SetDataBit[SetBit],1);  
                                                 } 
                                               
                                             }
                                            
                                            
                                          }
                                         
                                        
                         break;
                         
                        
                         
                         case 0x39:
                         case 0x3A:                                                     //限制在1-1999
                         
                                     if(SetBit==0)
                                      {
                                              if(SetDataBit[SetBit] < 1)
                                               {
                                                SetDataBit[SetBit]++;
                                                LcdOneByteWrite(DigitalDspStart+SetBit*8,KeySetLine,SetDataBit[SetBit],1);
                                                }
                                      }
                                     else
                                      {
                                              if(SetDataBit[SetBit] < 9)
                                               {
                                                SetDataBit[SetBit]++;
                                                LcdOneByteWrite(DigitalDspStart+SetBit*8,KeySetLine,SetDataBit[SetBit],1);
                                                }
                                      }
                                      break;
                       
                         case 0xF1:
                         case 0xF2:
                         case 0xF3:
                         case 0XB0:
                         case 0xB1:
                         case 0xB2:
                         case 0xC0:
                         case 0xC1:
                        
                               MenuStuNum++;
                               LcdTwoByteWrite(0,KeySetLine ,1,NOPCHAR);
                               KeySetLine=KeySetLine-2;
                               LcdTwoByteWrite(0,KeySetLine ,1,STAR);
                               break;      
                         case  0xB3:
                               MenuStuNum++;
                               ClearLcdLine(Line1);
                               ClearLcdLine(Line2);
                               ClearLcdLine(Line3);
                               ClearLcdLine(Line4);
                               LcdTwoByteWrite(20,Line4,4 ,INPUTALL);//4:同 时
                               KeySetLine=Line4;
                               LcdTwoByteWrite(0,KeySetLine ,1,STAR);
                               break;
                             
                         case 0xA0:
                         case 0xA1:
                         case 0xA2:
                         case 0xA3:
                         case 0xA4:
                         case 0xA5:
                         case 0xA6:
                         case 0xA7:
                         case 0xA8:
                         case 0xA9:
                         case 0xAA:
                         
    
                               ptrint++;
                               
                               if(MenuStuNum==0xA3)
                               {
                                ClearLcdLine(Line1);
                                ClearLcdLine(Line2);
                                ClearLcdLine(Line3);
                                ClearLcdLine(Line4);
                                
                                LcdTwoByteWrite(20,Line4,3, KUAHAO4);
                                LcdTwoByteWrite(20,Line3,3, PAIHAO5);
                                LcdTwoByteWrite(20,Line2,3, JIAOHAO6);
                                LcdTwoByteWrite(20,Line1,3, CHANNEL7);
                                LcdTwoByteWrite(0,Line4,1,STAR);    
                                  
                                KeySetLine=Line4;                       //指向第一个参数
                                SetDataDisp(Line4,(signed int)KuaHao,2);
                                SetDataDisp(Line3,(signed int)PaiHao,2);
                                    
                                SetDataDisp(Line2,(signed int)JiaoHao,2);
                                SetDataDisp(Line1,(signed int)MBChannel,2); 
                               }
                               else if(MenuStuNum==0xA7)
                               {
                                ClearLcdLine(Line1);
                                ClearLcdLine(Line2);
                                ClearLcdLine(Line3);
                                ClearLcdLine(Line4);
                                             
                                LcdTwoByteWrite(20,Line4,3, POWER8);
                                LcdTwoByteWrite(20,Line3,3, SAMPLETIME9);
                                LcdTwoByteWrite(20,Line2,3, WORKTIME10);
                                LcdTwoByteWrite(20,Line1,4, REPORTCHANNEL11);
                                LcdTwoByteWrite(0,Line4,1,STAR);
                                  
                                KeySetLine=Line4;                       //指向第一个参数
                                SetDataDisp(Line4,(signed int)MBPower,1);
                                SetDataDisp(Line3,(signed int)StandbyTime,4);
                                SetDataDisp(Line2,(signed int)WorkTime,4);
                                SetDataDisp(Line1,(signed int)ReportChannel,3); 
                               }
                               else
                               {
                               LcdTwoByteWrite(0,KeySetLine,1 ,NOPCHAR);
                               KeySetLine=KeySetLine-2;
                               LcdTwoByteWrite(0,KeySetLine,1 ,STAR);
                               }
                                                     
                               MenuStuNum++;
                          break;          
   
                        
                         }     
                   break;    

case set:					   /***************************key_set********************************************/
             KeyChange=0;
             switch(MenuStuNum)
			 {
			 case 0x00:
			           
			                   MenuStu=On;
					   MenuStuNum=0xF1;
                                           
                                           ClearLcdLine(Line1);
                                           ClearLcdLine(Line2);
                                           ClearLcdLine(Line3);
                                           ClearLcdLine(Line4);
                                           
                                           MenuDisp();
                                            
                                           KeySetLine=Line4;
                                           LcdTwoByteWrite(0,Line4,1,STAR); //五星标志(光标)在四行
				           break;
                         case 0x31:
                         case 0x32:
                         case 0x33:
                         case 0x34:
                         case 0x35:
                         case 0x36:  
                         case 0x37: 
                         case 0x38:
                         case 0x39:  
                         case 0x3a: 
                         case 0x3b:  
                                   if(SetBit<3)
                                   {
                                   SetBit++;
                                   LcdOneByteWrite(DigitalDspStart+(SetBit-1)*8,KeySetLine,SetDataBit[SetBit-1],0);
                                   LcdOneByteWrite(DigitalDspStart+SetBit*8,KeySetLine,SetDataBit[SetBit],1);
                                   
                                   }
                                    else
                                   {
                                   
                                   
                                   LcdOneByteWrite(DigitalDspStart+SetBit*8,KeySetLine,SetDataBit[3],0);
                                   LcdTwoByteWrite(0,KeySetLine,1,STAR); //五星标志(光标)指向当前行
                                   DataDiv(1,&KeySetData);
                                   switch(MenuStuNum)
                                   {
                                   case 0x39:
                                           if(KeySetData!=0)
                                                    *ptrint=KeySetData;
                                            break;
                                   case 0x3A: 
                                              if(KeySetData!=0)
                                                    *ptrint=KeySetData; 
                                              StuCount=0;
                                              WorkTimeSecond=WorkTime*15;
                                              
                                            break;
                                   case 0x31:
                                   case 0x32:
                                   case 0x33:
                                   case 0x34:
                                   case 0x35:
                                   case 0x36: 
                                   case 0x3B:  
                                              *ptrint=KeySetData; 
                                               break;
                                  
                                   case 0x37:
                                   case 0x38:                                  //模块信道 ，模块功率
                                            if(*ptrint!=KeySetData)
                                             {
                                                *ptrint=KeySetData;
                                                StuCount=0;
                                                ConfigStu=On;//需重新配置模块
                                                     
                                             }
                                            break;
                                     
                                   }
                              
                                   
                                   WRFlash ((uchar *)0x200,(uchar *)0x1000,64);
                                   delay_ms(10);
                                   RDFlash ((uchar *)0x200,(uchar *)0x1000,64);
                                   delay_ms(10);
                                   
                                   MenuStuNum=MenuStuNum+0x70;
                                    }
                         break;
                         
                        
                         case 0xF1:
                                    MenuStuNum=0xA1;
                                    ClearLcdLine(Line1);
                                    ClearLcdLine(Line2);
                                    ClearLcdLine(Line3);
                                    ClearLcdLine(Line4);
                                    
                                    LcdTwoByteWrite(20,Line4,5 ,EXIT0);
                                    LcdTwoByteWrite(20,Line3,4, CEJIANHAO1);
                                    LcdTwoByteWrite(20,Line2,4, ZERENQU2);
                                    LcdTwoByteWrite(20,Line1,4, BANZUHAO3);
                                    LcdTwoByteWrite(0,Line3,1,STAR);    
                                    
                                    KeySetLine=Line3;                       
                                    ptrint=&CeJianHao;
                                   
                                    SetDataDisp(Line3,(signed int)CeJianHao,3);
                                    SetDataDisp(Line2,(signed int)ZeRenQu,1);
                                    SetDataDisp(Line1,(signed int)BanZuHao,3);
                                    
			 break;
                         case 0xF2:
                                    MenuStuNum=0xB1;
                          
                                    ClearLcdLine(Line1);
                                    ClearLcdLine(Line2);
                                    ClearLcdLine(Line3);
                                    ClearLcdLine(Line4);
                                    
                                    LcdTwoByteWrite(20,Line4,5 ,EXIT0);  //0:退出
                                    LcdTwoByteWrite(20,Line3,4 ,INPUT1);//1:输入一
                                    LcdTwoByteWrite(20,Line2,4 ,INPUT2);//2:输入二
                                    LcdTwoByteWrite(20,Line1,4 ,INPUT3);//3:输入三
                                    KeySetLine=Line3;
                                    LcdTwoByteWrite(0,Line3,1,STAR);    
                         
                    
			 break;
                           case   0xF3:
                                    MenuStuNum=0xC0;
                          
                                    ClearLcdLine(Line1);
                                    ClearLcdLine(Line2);
                                    ClearLcdLine(Line3);
                                    ClearLcdLine(Line4);
                                    
                                    LcdTwoByteWrite(16,Line4,5 ,BAKANDRECOVER);//备份与恢复
                                    LcdTwoByteWrite(24,Line3,5 ,EXIT0);      //0:退出
                                    LcdTwoByteWrite(24,Line2,3 ,BAK1);      //1:备份
                                    LcdTwoByteWrite(24,Line1,3 ,RECOVER2);  //2:恢复
                                    
                                    KeySetLine=Line3;
                                    LcdTwoByteWrite(0,Line3,1,STAR);    
			 break;
                         case 0xF4:
                         
                               
                                    RDFlash(( uchar *)0x200,(uchar *)0x1000,64);
                                    RDFlash(( uchar *)0x280,(uchar *)0x1080,33); 
                                    
                                                                        
                                    NormalDisp();
                                    MenuStuNum=0;
                                    MenuStu=Off;
                                    StuCount=0;
                                    
                           break;
                         case  0xA1:
                         case  0xA2:
                         case  0xA3:
                         case  0xA4:
                         case  0xA5:
                         case  0xA6:
                         case  0xA7:
                         case  0xA8:
                         case  0xA9:
                         case  0xAA:
                         case  0xAB: 
                                   LcdTwoByteWrite(0,KeySetLine,1 ,NOPCHAR); //清光标
                                   KeySetData=*ptrint;
                                   switch(MenuStuNum)
                                       {
                                      case 0xA9:
                                      case 0xAA:
                                               SetBit=0;           //采样时间，工作时间为4位
                                               break;
                                      case 0xA1:
                                      case 0xA3:
                                               SetBit=1;           //车间号，班组号为3位
                                               break;
                                      case 0xA4:
                                      case 0xA6:
                                      case 0xA7:
                                      case 0xAB:
                                               SetBit=2;           //垮号，窖号,查询信道为2位，上报信道为3位，但可设为后两位          
                                                break;
                                      case 0xA2:
                                      case 0xA5:
                                      case 0xA8:  
                                               SetBit=3;           //责任区，排号，模块功率为1位
                                               
                                               break;
                        
                                        }
                                   
                                   MenuStuNum=MenuStuNum-0x70;
                                   DataDiv(0,&KeySetData);
                                   LcdOneByteWrite(DigitalDspStart+SetBit*8,KeySetLine,SetDataBit[SetBit],1);
                           break;
                        
                    
                          
                         case 0xB1:
                         case 0xB2:
                         case 0xB3:
                         case 0xB4:
                                      
                                      
                                      ClearLcdLine(Line4);
                                      ClearLcdLine(Line3);
                                      ClearLcdLine(Line2);
                                      ClearLcdLine(Line1);
                                      
                                      if(MenuStuNum==0xB1)
                                       {
                                        LcdTwoByteWrite(0,Line4,7 ,INPUT1ADJUST); 
                                       }
                                      else if(MenuStuNum==0xB2)
                                       {
                                        LcdTwoByteWrite(0,Line4,7 ,INPUT2ADJUST); 
                                       }
                                      else if(MenuStuNum==0xB3)
                                       {
                                        LcdTwoByteWrite(0,Line4,7 ,INPUT3ADJUST); 
                                       }
                                      else
                                       {
                                        LcdTwoByteWrite(8,Line4,6 ,INPUTADJUST);
                                       }
                                      
                                      MenuStuNum=0x93+(MenuStuNum-0xB1)*2;         
                                      LcdTwoByteWrite(0,KeySetLine,1 ,NOPCHAR);            
                                      LcdTwoByteWrite(20,Line2,5 ,INPUT00);
                                     
                         break;
                          case 0xC1:                                            //备份参数值
                                      DataBak(ramstart);
                                                                 
                                      WRFlash ((uchar *)0x200,(uchar *)0x1000,64);
                                      delay_ms(10);
                                      RDFlash ((uchar *)0x200,(uchar *)0x1000,64);
                                      delay_ms(10);
                                      
                                      WRFlash ((uchar *)0x280,(uchar *)0x1080,33);
                                      delay_ms(10);
                                      RDFlash ((uchar *)0x280,(uchar *)0x1080,33);
                                      delay_ms(10);
                                      
                                      MenuStuNum=0xF4;
                                      MenuDisp();
                                      KeySetLine=Line1;
                                      LcdTwoByteWrite(0,Line1,1,STAR); //五星标志(光标)在一行 
                                     
                         break;
                         case 0xC2:                                         //恢复参数值
                                      
                           
                                      RDFlash ((uchar *)0x222,(uchar *)0x1022,30);//读备份区数据
                                      DataRecover(ramstart);
                             
                                      WRFlash ((uchar *)0x200,(uchar *)0x1000,64);
                                      delay_ms(10);
                                      RDFlash ((uchar *)0x200,(uchar *)0x1000,64);
                                      delay_ms(10);
                                      WRFlash ((uchar *)0x280,(uchar *)0x1080,33);
                                      delay_ms(10);
                                      RDFlash ((uchar *)0x280,(uchar *)0x1080,33);
                                      delay_ms(10);
                                      
                                      StuCount=0;
                                      ConfigStu=On;//需重新配置模块
                                      IDSetFlag=On;
                                      
                                      
                                      MenuStuNum=0xF4;
                                      MenuDisp();
                                      KeySetLine=Line1;
                                      LcdTwoByteWrite(0,Line1,1,STAR); //五星标志(光标)在一行
                             
                             
                             
                         break;
                         case 0x93:
                         case 0x95:
                         case 0x97:
                         case 0x99:
                                       MenuStuNum++;
                                       LcdTwoByteWrite(20,Line2,5,INPUTFS);//输入满度-
                           
                           
                           break;
                           
                         case 0x94:
                         case 0x96:
                         case 0x98:
                         case 0x9A:  
                                    
                                      MenuStuNum=0xF4;
                                      PVPT[0]=0;
                                      PVPT[1]=0;
                                      PVPT[2]=0;
                                      WRFlash ((uchar *)0x280,(uchar *)0x1080,33);
                                      delay_ms(10);
                                      RDFlash ((uchar *)0x280,(uchar *)0x1080,33);
                                      delay_ms(10);
                                      MenuDisp();
                                      KeySetLine=Line1;
                                      LcdTwoByteWrite(0,Line1,1,STAR); //五星标志(光标)在一行    
                                      
                           break;
                         case 0xA0:
                         case 0xB0:
                         case 0xC0:
                                      MenuStuNum=0xF4;
                                      
                                      WRFlash ((uchar *)0x200,(uchar *)0x1000,64);
                                      delay_ms(10);
                                      RDFlash ((uchar *)0x200,(uchar *)0x1000,64);
                                      delay_ms(10);
                                      MenuDisp();
                                      KeySetLine=Line1;
                                      LcdTwoByteWrite(0,Line1,1,STAR); //五星标志(光标)在一行
                           
                           
                           break;
                         
			 }
			 
break;
case key_down:						/*******************************key_down****************************************/
             KeyChange=0;
			
			 switch(MenuStuNum)
			 {
			 case 0x31:
                         case 0x32:
                         case 0x33:
                         case 0x34:
                         case 0x35:
                         case 0x36:
                         case 0x37:
                         case 0x38:
                         case 0x3B:
                           
                           if(SetDataBit[SetBit]>0)
                           {
                                SetDataBit[SetBit]--;
                                LcdOneByteWrite(DigitalDspStart+SetBit*8,KeySetLine,SetDataBit[SetBit],1);
                           }
                         break;
                         case 0x39:
                         case 0x3A:                         //采样时间，工作时间，不能等于0
                                  if(SetBit==3)
                                  {
                                      if((SetDataBit[0]+SetDataBit[1]+SetDataBit[2])==0)
                                      {
                                          if(SetDataBit[SetBit]>1)
                                          {
                                          SetDataBit[SetBit]--;
                                          LcdOneByteWrite(DigitalDspStart+SetBit*8,KeySetLine,SetDataBit[SetBit],1);
                                          }
                                      
                                      
                                       }
                                      else
                                      {
                                        if(SetDataBit[SetBit]>0)
                                         {
                                         SetDataBit[SetBit]--;
                                         LcdOneByteWrite(DigitalDspStart+SetBit*8,KeySetLine,SetDataBit[SetBit],1);
                                         }
                                        
                                      }
                                      
                                  }
                                  else
                                  {
                                      if(SetDataBit[SetBit]>0)
                                      {
                                       SetDataBit[SetBit]--;
                                       LcdOneByteWrite(DigitalDspStart+SetBit*8,KeySetLine,SetDataBit[SetBit],1);
                                      }
                                  }
                         break;
                         case 0xF2:
                         case 0xF3:
                         case 0xF4: 
                         case 0xB1:
                         case 0xB2:
                         case 0xB3:
                         case 0xC1:
                         case 0xC2:
                                MenuStuNum--;
                                LcdTwoByteWrite(0,KeySetLine,1 ,NOPCHAR);
                                KeySetLine=KeySetLine+2;
                                LcdTwoByteWrite(0,KeySetLine,1 ,STAR);
                               
                         break;      
                         case 0xB4:
                                    MenuStuNum--;
                                    ClearLcdLine(Line1);
                                    ClearLcdLine(Line2);
                                    ClearLcdLine(Line3);
                                    ClearLcdLine(Line4);
                                    
                                    LcdTwoByteWrite(20,Line4,5 ,EXIT0);  //0:退出
                                    LcdTwoByteWrite(20,Line3,4 ,INPUT1);//1:输入一
                                    LcdTwoByteWrite(20,Line2,4 ,INPUT2);//2:输入二
                                    LcdTwoByteWrite(20,Line1,4 ,INPUT3);//3:输入三
                                    KeySetLine=Line1;
                                    LcdTwoByteWrite(0,KeySetLine,1,STAR);    
                         break;
                         
                         case 0xA1:
                         case 0xA2:
                         case 0xA3:
                         case 0xA4:  
                         case 0xA5:
                         case 0xA6:
                         case 0xA7:
                         case 0xA8:
                         case 0xA9:
                         case 0xAA:
                         case 0xAB:
                               ptrint--;
                               if(MenuStuNum==0xA4)
                                {
                                ClearLcdLine(Line1);
                                ClearLcdLine(Line2);
                                ClearLcdLine(Line3);
                                ClearLcdLine(Line4);
                                
                                LcdTwoByteWrite(20,Line4,5 ,EXIT0);
                                LcdTwoByteWrite(20,Line3,4, CEJIANHAO1);
                                LcdTwoByteWrite(20,Line2,4, ZERENQU2);
                                LcdTwoByteWrite(20,Line1,4, BANZUHAO3);
                                
                                LcdTwoByteWrite(0,Line1,1,STAR);    //五星标志(光标)在三行
                                    
                                                       
                                  
                                SetDataDisp(Line3,(signed int)CeJianHao,3);
                                SetDataDisp(Line2,(signed int)ZeRenQu,1);
                                SetDataDisp(Line1,(signed int)BanZuHao,3);
                               
                                KeySetLine=Line1;     
                                }
                               else if(MenuStuNum==0xA8)
                                {
                                ClearLcdLine(Line1);
                                ClearLcdLine(Line2);
                                ClearLcdLine(Line3);
                                ClearLcdLine(Line4);
                                
                                
                                LcdTwoByteWrite(20,Line4,3, KUAHAO4);
                                LcdTwoByteWrite(20,Line3,3, PAIHAO5);
                                LcdTwoByteWrite(20,Line2,3, JIAOHAO6);
                                LcdTwoByteWrite(20,Line1,3, CHANNEL7);
                                
                                LcdTwoByteWrite(0,Line1,1,STAR);    //五星标志(光标)在三行
                                    
                                                       
                                  
                                SetDataDisp(Line4,(signed int)KuaHao,2);
                                SetDataDisp(Line3,(signed int)PaiHao,2);
                                    
                                SetDataDisp(Line2,(signed int)JiaoHao,2);
                                SetDataDisp(Line1,(signed int)MBChannel,2);
                               
                                KeySetLine=Line1;      
                                }
                               else
                                {
                                  
                               LcdTwoByteWrite(0,KeySetLine,1 ,NOPCHAR);
                               KeySetLine=KeySetLine+2;
                               LcdTwoByteWrite(0,KeySetLine,1 ,STAR);
                                
                                }
                               
                              MenuStuNum--; 
                               
                               
                          break;          
 
       
			 }
			 
break;
case no_key:
     if(MenuStu==On)	   //菜单设置状态，
	 {
	     
		  Key30s--;
		  if(Key30s==0)
		  {
		  
		  Key30s=750;
		  KeyChange=0;
                  
                  RDFlash(( uchar *)0x200,(uchar *)0x1000,64);
                  RDFlash(( uchar *)0x280,(uchar *)0x1080,33);
                  
                  NormalDisp();
		  MenuStu=Off;
		  MenuStuNum=0;
		  
		  }
		
	 }
break;
}

}
/*****************************************************************************************************

******************************************************************************************************/


void DataDiv(uchar mode,uint *datatemp)
{
  if(mode==0)
  {
    SetDataBit[0]=(*datatemp)/1000;
    SetDataBit[1]=(*datatemp)/100 %10;
    SetDataBit[2]=(*datatemp)/10 %10;
    SetDataBit[3]=(*datatemp)%10;
     
  }
  else
  {
   *datatemp=SetDataBit[0]*1000+SetDataBit[1]*100 +SetDataBit[2]*10+SetDataBit[3];
    
  }
  
  
  
  
}

void DataBak(uchar *ramstart2)
 {
   uchar  *ptrchar2,*ptrchar3;
   uchar   bakii;
   
                                    ptrchar2=ramstart2+0x22;
                                    ptrchar3=ramstart2+0x02;
                                    
                                    for(bakii=0;bakii<30;bakii++)
                                    {
                                      
                                     *(ptrchar2+bakii)=*(ptrchar3+bakii); 
                                      
                                    }
                                    *(ramstart2+0x12)=10;//采样时间初如化为为10
                                    *(ramstart2+0x13)=0;
                                    
                                    *(ramstart2+0x32)=10;//备份采样时间初如化为为10
                                    *(ramstart2+0x33)=0;
                                     
                                    ptrchar2=ramstart2+0x82;
                                    ptrchar3=ramstart2+0x92;
                                    
                                    for(bakii=0;bakii<15;bakii++)
                                    {
                                      
                                     *(ptrchar2+bakii)=*(ptrchar3+bakii); 
                                      
                                    }
                                     
                                     
                                  *ramstart2 = Bakuped;//创建已备份标志
   
   
 }



void DataRecover(uchar *ramstart2)
{
 uchar  *ptrchar2,*ptrchar3;
 uchar   bakii;
                         if(*ramstart2==Bakuped)//若已备份过，则恢复所有的备份值
                           {
                                    ptrchar2=ramstart2+0x02;
                                    ptrchar3=ramstart2+0x22;
                                    
                                    for(bakii=0;bakii<30;bakii++)
                                    {
                                      
                                     *(ptrchar2+bakii)=*(ptrchar3+bakii); 
                                      
                                    }
                                    
                                    
                                     
                                    ptrchar2=ramstart2+0x92;
                                    ptrchar3=ramstart2+0x82;
                                    
                                    for(bakii=0;bakii<15;bakii++)
                                    {
                                      
                                     *(ptrchar2+bakii)=*(ptrchar3+bakii); 
                                      
                                    } 
  
                           }
  
  
}




void DataRecover888(uchar *ramstart2)
 {
   uchar  *ptrchar2,*ptrchar3;
   uchar   bakii;
                                  
                                 
                                    
                                    *(ramstart2+0x12)=10;//采样时间初如化为为10
                                    *(ramstart2+0x13)=0;
                                    
                                    *(ramstart2+0x14)=1;//持续工作时间初如化为为1
                                    *(ramstart2+0x15)=0;
                                    
                                    *(ramstart2+0x16)=100;//控制信道初如化为100
                                    *(ramstart2+0x17)=0;
       
                                    
                                    *(ramstart2+0x9E)=0;  //三路修正值初如化为0
                                    *(ramstart2+0x9F)=0;
                                    *(ramstart2+0xA0)=0; 
                                    
                                    if(*ramstart2==Bakuped)//若已备份过，则恢复标定值
                                    {
                                        ptrchar2=ramstart2+0x92;
                                        ptrchar3=ramstart2+0x82;
                                        
                                        for(bakii=0;bakii<12;bakii++)
                                        {
                                          
                                         *(ptrchar2+bakii)=*(ptrchar3+bakii); 
                                          
                                        } 
                                        
                                       
                                    }
                                    
   
 }




