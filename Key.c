#include <io430.h>
#include <in430.h>
#include <intrinsics.h>
#include"Predefined.h"
#include"DispDataDo.h"
#include"LcdDriver.h"
#include"FlashWR.h"
#include "Key.h"


/******************************************************************************
              ��        ��      ��
*******************************************************************************
0����̬��1��������ʾ���������ڣ�����ʱ�䣩

���ƣ�����������
���ƣ����¶ȵ�У
���ƣ����ָ���������
���ƣ����˳�

���ƣ�����������
����0������ ������30��
������������š���31��
������������������32��
������������š���33��

����4������š���34��
����5�����źš���35��
����6�����Ѻš���36��
����7���������ŵ���37��

����8�������书�ʣ�38��
����9�����������ڣ�39��
����A��������ʱ�䣨3A��
��AB)    �޸��ŵ���3B��

��
���ƣ����¶ȵ�У
����0����0���˳�
����1����1������һ������93��94��
����2����2�������������95��96��
����3����3��������������97��98��
(B4)     4: ͬʱ

���ƣ���������ָ�
����0������0���˳�������
����1������1�����ݡ�����
����2����  2���ָ���
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
                         case 0x33:                               //����ţ�����ţ�0-999   ������0-9,����ѯ�ŵ�0-99,���00��99���ź�0��9
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
                                         if(SetDataBit[SetBit]<7)                   //���书��������0-7
                                          {
                                          SetDataBit[SetBit]++;
                                          LcdOneByteWrite(DigitalDspStart+SetBit*8,KeySetLine,SetDataBit[SetBit],1);  
                                          }
                           
                         break;
                         case 0x3B:                                           //�޸��ŵ�������100-123
                                        
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
                                               if(SetDataBit[SetBit]<9)                   //������0-123
                                                 {
                                                 SetDataBit[SetBit]++;
                                                 LcdOneByteWrite(DigitalDspStart+SetBit*8,KeySetLine,SetDataBit[SetBit],1);  
                                                 } 
                                               
                                             }
                                            
                                            
                                          }
                                         
                                        
                         break;
                         
                        
                         
                         case 0x39:
                         case 0x3A:                                                     //������1-1999
                         
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
                               LcdTwoByteWrite(20,Line4,4 ,INPUTALL);//4:ͬ ʱ
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
                                  
                                KeySetLine=Line4;                       //ָ���һ������
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
                                  
                                KeySetLine=Line4;                       //ָ���һ������
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
                                           LcdTwoByteWrite(0,Line4,1,STAR); //���Ǳ�־(���)������
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
                                   LcdTwoByteWrite(0,KeySetLine,1,STAR); //���Ǳ�־(���)ָ��ǰ��
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
                                   case 0x38:                                  //ģ���ŵ� ��ģ�鹦��
                                            if(*ptrint!=KeySetData)
                                             {
                                                *ptrint=KeySetData;
                                                StuCount=0;
                                                ConfigStu=On;//����������ģ��
                                                     
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
                                    
                                    LcdTwoByteWrite(20,Line4,5 ,EXIT0);  //0:�˳�
                                    LcdTwoByteWrite(20,Line3,4 ,INPUT1);//1:����һ
                                    LcdTwoByteWrite(20,Line2,4 ,INPUT2);//2:�����
                                    LcdTwoByteWrite(20,Line1,4 ,INPUT3);//3:������
                                    KeySetLine=Line3;
                                    LcdTwoByteWrite(0,Line3,1,STAR);    
                         
                    
			 break;
                           case   0xF3:
                                    MenuStuNum=0xC0;
                          
                                    ClearLcdLine(Line1);
                                    ClearLcdLine(Line2);
                                    ClearLcdLine(Line3);
                                    ClearLcdLine(Line4);
                                    
                                    LcdTwoByteWrite(16,Line4,5 ,BAKANDRECOVER);//������ָ�
                                    LcdTwoByteWrite(24,Line3,5 ,EXIT0);      //0:�˳�
                                    LcdTwoByteWrite(24,Line2,3 ,BAK1);      //1:����
                                    LcdTwoByteWrite(24,Line1,3 ,RECOVER2);  //2:�ָ�
                                    
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
                                   LcdTwoByteWrite(0,KeySetLine,1 ,NOPCHAR); //����
                                   KeySetData=*ptrint;
                                   switch(MenuStuNum)
                                       {
                                      case 0xA9:
                                      case 0xAA:
                                               SetBit=0;           //����ʱ�䣬����ʱ��Ϊ4λ
                                               break;
                                      case 0xA1:
                                      case 0xA3:
                                               SetBit=1;           //����ţ������Ϊ3λ
                                               break;
                                      case 0xA4:
                                      case 0xA6:
                                      case 0xA7:
                                      case 0xAB:
                                               SetBit=2;           //��ţ��Ѻ�,��ѯ�ŵ�Ϊ2λ���ϱ��ŵ�Ϊ3λ��������Ϊ����λ          
                                                break;
                                      case 0xA2:
                                      case 0xA5:
                                      case 0xA8:  
                                               SetBit=3;           //���������źţ�ģ�鹦��Ϊ1λ
                                               
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
                          case 0xC1:                                            //���ݲ���ֵ
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
                                      LcdTwoByteWrite(0,Line1,1,STAR); //���Ǳ�־(���)��һ�� 
                                     
                         break;
                         case 0xC2:                                         //�ָ�����ֵ
                                      
                           
                                      RDFlash ((uchar *)0x222,(uchar *)0x1022,30);//������������
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
                                      ConfigStu=On;//����������ģ��
                                      IDSetFlag=On;
                                      
                                      
                                      MenuStuNum=0xF4;
                                      MenuDisp();
                                      KeySetLine=Line1;
                                      LcdTwoByteWrite(0,Line1,1,STAR); //���Ǳ�־(���)��һ��
                             
                             
                             
                         break;
                         case 0x93:
                         case 0x95:
                         case 0x97:
                         case 0x99:
                                       MenuStuNum++;
                                       LcdTwoByteWrite(20,Line2,5,INPUTFS);//��������-
                           
                           
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
                                      LcdTwoByteWrite(0,Line1,1,STAR); //���Ǳ�־(���)��һ��    
                                      
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
                                      LcdTwoByteWrite(0,Line1,1,STAR); //���Ǳ�־(���)��һ��
                           
                           
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
                         case 0x3A:                         //����ʱ�䣬����ʱ�䣬���ܵ���0
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
                                    
                                    LcdTwoByteWrite(20,Line4,5 ,EXIT0);  //0:�˳�
                                    LcdTwoByteWrite(20,Line3,4 ,INPUT1);//1:����һ
                                    LcdTwoByteWrite(20,Line2,4 ,INPUT2);//2:�����
                                    LcdTwoByteWrite(20,Line1,4 ,INPUT3);//3:������
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
                                
                                LcdTwoByteWrite(0,Line1,1,STAR);    //���Ǳ�־(���)������
                                    
                                                       
                                  
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
                                
                                LcdTwoByteWrite(0,Line1,1,STAR);    //���Ǳ�־(���)������
                                    
                                                       
                                  
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
     if(MenuStu==On)	   //�˵�����״̬��
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
                                    *(ramstart2+0x12)=10;//����ʱ����绯ΪΪ10
                                    *(ramstart2+0x13)=0;
                                    
                                    *(ramstart2+0x32)=10;//���ݲ���ʱ����绯ΪΪ10
                                    *(ramstart2+0x33)=0;
                                     
                                    ptrchar2=ramstart2+0x82;
                                    ptrchar3=ramstart2+0x92;
                                    
                                    for(bakii=0;bakii<15;bakii++)
                                    {
                                      
                                     *(ptrchar2+bakii)=*(ptrchar3+bakii); 
                                      
                                    }
                                     
                                     
                                  *ramstart2 = Bakuped;//�����ѱ��ݱ�־
   
   
 }



void DataRecover(uchar *ramstart2)
{
 uchar  *ptrchar2,*ptrchar3;
 uchar   bakii;
                         if(*ramstart2==Bakuped)//���ѱ��ݹ�����ָ����еı���ֵ
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
                                  
                                 
                                    
                                    *(ramstart2+0x12)=10;//����ʱ����绯ΪΪ10
                                    *(ramstart2+0x13)=0;
                                    
                                    *(ramstart2+0x14)=1;//��������ʱ����绯ΪΪ1
                                    *(ramstart2+0x15)=0;
                                    
                                    *(ramstart2+0x16)=100;//�����ŵ����绯Ϊ100
                                    *(ramstart2+0x17)=0;
       
                                    
                                    *(ramstart2+0x9E)=0;  //��·����ֵ���绯Ϊ0
                                    *(ramstart2+0x9F)=0;
                                    *(ramstart2+0xA0)=0; 
                                    
                                    if(*ramstart2==Bakuped)//���ѱ��ݹ�����ָ��궨ֵ
                                    {
                                        ptrchar2=ramstart2+0x92;
                                        ptrchar3=ramstart2+0x82;
                                        
                                        for(bakii=0;bakii<12;bakii++)
                                        {
                                          
                                         *(ptrchar2+bakii)=*(ptrchar3+bakii); 
                                          
                                        } 
                                        
                                       
                                    }
                                    
   
 }




