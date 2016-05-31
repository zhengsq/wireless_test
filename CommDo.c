
#include <io430.h>
#include <in430.h>
#include <intrinsics.h>
#include "Predefined.h"
#include "flashWR.h"
#include"DispDataDo.h"
#include "Key.h"
#include "CommDo.h"



/***************************�ӻ�MODBUS�����Ϸ���ʽ***************************************************************************************


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
            if(*(rxdata+9)==0x30)                         //ģ����ɹ�
             {
               *(ramppt+0X1a)=*(rxdata+10);//PID1
               *(ramppt+0X1b)=*(rxdata+11);//PID2
               *(ramppt+0X1c)=*(rxdata+12);//PID3
               *(ramppt+0X1d)=*(rxdata+13);//PID4
               *(ramppt+0X1e)=*(rxdata+14);//UID1
               *(ramppt+0X1f)=*(rxdata+15);//UID2
               
               *(ramppt+0X10)=*(rxdata+17);//ģ�鹦��
               
               if(*(rxdata+16)==*(ramppt+0X16))  //�������ػ�(�ŵ���δ�л�����ǰ�͹ػ�)ʱ,������ָ���ѯ�ŵ�
               {
                 RecoverFlag=On;
               }
               else
               {
               *(ramppt+0X0e)=*(rxdata+16);//ģ���ŵ�
               RefreshAfterRead=On;
               }
               
               if((MBDataReadFlag==Ready)&&(*ramppt==Bakuped))//��ʱ���Ҳ����ѱ��ݲűȽ�
               {
                 
                     MBDataReadFlag=Off;
                     
                     RDFlash ((uchar *)0x222,(uchar *)0x1022,30);//�ض�����������
                     
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
             else if((*(rxdata+9)==0x31)&&(*(rxdata+10)==0xCC))//ģ�����óɹ�����
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
                 SendTimes=3;               //�����ϱ�����
                //  SendTimes=1;               //�����ϱ�����
                 TimeForSentFlag=1;         //�����ϱ�
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
              //AutoSentFlag=1;             //�������óɹ������ϱ����ݸ���վ
              //delay_ms(1);
             }
            else if((*(rxdata+9)==0x32)&&(*(rxdata+10)==0xCC))//ģ��PID���óɹ�
             {
               *(ramppt+0X1a)=*(rxdata+3);//PID1
               *(ramppt+0X1b)=*(rxdata+4);//PID2
               *(ramppt+0X1c)=*(rxdata+5);//PID3
               *(ramppt+0X1d)=*(rxdata+6);//PID4
               *(ramppt+0X1e)=*(rxdata+7);//UID1
               *(ramppt+0X1f)=*(rxdata+8);//UID2
               
                           
               *(ramppt+0X0e)=*(ramppt+0X2e);       //�ָ��ŵ� 
               *(ramppt+0X10)=*(ramppt+0X30);       //�ָ�����
                
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
            
              comii=*(rxdata+2);//ȡ���ʳ���
              
              md_crc=CrcCheck((comii-9),(rxdata+10));		      //����������crc����
   
              float_byte.f_byte[0]=*(rxdata+comii+1);

              float_byte.f_byte[1]=*(rxdata+comii+2); 
              
              SentOrNot=1;
             if(md_crc==float_byte.f_int)	           //������Ϣ��crcֵ��ȷ
              {
                
                switch(*(rxdata+11))
                 {
                   case 0x03:
                   case 0x53:
                             *(txdata+11)=*(rxdata+11);
                             ReadIDCount=0;
                             MBDataReadFlag=Off;      //�����շ�,ȡ����ʱ��
                             CommNormalData(txdata,ramppt);
                             break;
                   case 0x10:                     //��վд�Ĵ���
                   case 0x60:                     //�ֲ���д�Ĵ���
                     
                             *(ramppt+0x03)=*(rxdata+17);//�����
                             *(ramppt+0x02)=*(rxdata+18);
                             *(ramppt+0x05)=*(rxdata+19);//������
                             *(ramppt+0x04)=*(rxdata+20);
                             *(ramppt+0x07)=*(rxdata+21);//������
                             *(ramppt+0x06)=*(rxdata+22);
                                  
                              *(ramppt+0X08)=*(rxdata+24);//���
                              *(ramppt+0X0a)=*(rxdata+25);//�ź� 
                              *(ramppt+0X0c)=*(rxdata+26);//�Ѻ� 
       
                              
                              if((*(rxdata+10)==0xBA)&&(*(rxdata+11)==0x60))              //���ֲ����߼��û���д
                              {
                                      if(*(ramppt+0X16)!=*(rxdata+23))//�޸��ŵ�
                                                 *(ramppt+0X16)=*(rxdata+23);
                                  
                                      if(*(ramppt+0X0e)!=*(rxdata+27))
                                       {
                                      *(ramppt+0X0e)=*(rxdata+27);//ģ���ŵ�
                                       ConfigStu=On;
                                       StuCount=0;
                                       }
                                      if(*(ramppt+0X10)!=*(rxdata+28))
                                       {
                                       *(ramppt+0X10)=*(rxdata+28);//ģ�鹦��
                                        ConfigStu=On;
                                        StuCount=0;
                                       }
       
                                       if((*(rxdata+29)!=0)||(*(rxdata+30)!=0))
                                       {
                                        *(ramppt+0x13)=*(rxdata+29);//��������
                                        *(ramppt+0x12)=*(rxdata+30);

                                       }
                                       if((*(rxdata+31)!=0)||(*(rxdata+32)!=0))
                                       {                            
                                         *(ramppt+0x15)=*(rxdata+31);//��������ʱ��
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
                             *(txdata+2)=0x15;//�ֽڳ�=�ܳ�-5
      
                             *(txdata+3)=0xFF;
                             *(txdata+4)=0xFF;
                             *(txdata+5)=0xFF;
                             *(txdata+6)=0xFF;
                             *(txdata+7)=0xFF;
                             *(txdata+8)=0xFF;    //�㲥�����л�վ
                             *(txdata+9)=0x02;    //ת��Ӧ��ָ��
/**********************************************/
                             *(txdata+10)=*(rxdata+10);//0xAB��0xBA

                             *(txdata+11)=*(rxdata+11);//д�Ĵ���������0x10��0x60
                             *(txdata+12)=0x10;
                             *(txdata+13)=0x03;       //��ʼ�Ĵ�����ַ0x1003
                            
                             *(txdata+14)=0x00;
                             *(txdata+15)=*(rxdata+15);//д�Ĵ�������Ŀ
                             
                             *(txdata+16)=*(ramppt+0X1a);
                             *(txdata+17)=*(ramppt+0X1b);
                             *(txdata+18)=*(ramppt+0X1c);
                             *(txdata+19)=*(ramppt+0X1d);
                             *(txdata+20)=*(ramppt+0X1e);
                             *(txdata+21)=*(ramppt+0X1f); 
                             
                            
                             float_byte.f_int=CrcCheck(12,(txdata+10));		      //����������crc����
   
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
                              RDFlash ((uchar *)0x222,(uchar *)0x1022,30);//������������
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
                               //RDFlash ((uchar *)0x222,(uchar *)0x1022,30);//������������
                               
                               *(ramppt+0X3a)=*(rxdata+13);//PID1
                               *(ramppt+0X3b)=*(rxdata+14);//PID2
                               *(ramppt+0X3c)=*(rxdata+15);//PID3
                               *(ramppt+0X3d)=*(rxdata+16);//PID4
                               *(ramppt+0X3e)=*(rxdata+17);//UID1
                               *(ramppt+0X3f)=*(rxdata+18);//UID2//�µ�ID��
                               
                               *(ramppt+0X2e)=*(rxdata+19);//ģ���ŵ�
                               *(ramppt+0X30)=*(rxdata+20);//ģ�鹦��
                            
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
                             *(txdata+2)=0x1a;//�ֽڳ�=�ܳ�-5
      
                             *(txdata+3)=0xFF;
                             *(txdata+4)=0xFF;
                             *(txdata+5)=0xFF;
                             *(txdata+6)=0xFF;
                             *(txdata+7)=0xFF;
                             *(txdata+8)=0xFF;    //�㲥�����л�վ
                             
                             *(txdata+9)=0x02;    //ת��Ӧ��ָ��
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
                             
                            
                             float_byte.f_int=CrcCheck(17,(txdata+10));		      //����������crc����
   
                             *(txdata+27)=float_byte.f_byte[0];

                             *(txdata+28)=float_byte.f_byte[1]; 
              

/*****************************************************/
                            *(txdata+29)=0xCC;
                            *(txdata+30)=0xCC;
                            SentNum=31;
                            
                            break;
      
  
                 }
  
                
              }
             else                   //��Ϣ��crcУ�鲻��ȷ
              {
                             *txdata=0x7E;
                             *(txdata+1)=0x30;
                             *(txdata+2)=18;     //�ֽڳ�=�ܳ�-5
                            
                             *(txdata+3)=0xFF;
                             *(txdata+4)=0xFF;
                             *(txdata+5)=0xFF;
                             *(txdata+6)=0xFF;
                             *(txdata+7)=0xFF;
                             *(txdata+8)=0xFF;    //�㲥�����л�վ
                             
                             *(txdata+9)=0x02;    //ת��Ӧ��ָ��
                          /*****************************************��Ϣ��*****************************/
                             *(txdata+10)=0xAB;
                             *(txdata+11)+=0x80;
                             *(txdata+12)=0x04;                   //crc16У�����
                             
                             *(txdata+13)=*(ramppt+0X1a);          //PID
                             *(txdata+14)=*(ramppt+0X1b);
                             *(txdata+15)=*(ramppt+0X1c);
                             *(txdata+16)=*(ramppt+0X1d);
                             *(txdata+17)=*(ramppt+0X1e);         //UID
                             *(txdata+18)=*(ramppt+0X1f);
                             
                             float_byte.f_int=CrcCheck(9,(txdata+10));		      //����������crc����
   
                             *(txdata+19)=float_byte.f_byte[0];
                             *(txdata+20)=float_byte.f_byte[1]; 
	                    
                          /*****************************************************************************/
                            *(txdata+21)=0xCC;
                            *(txdata+22)=0xCC;
                            
                            SentNum=23;
              }
               
          
   
   
            break;
   case 0x30:                                                   
            if((*(rxdata+9)==0x01)&&(*(rxdata+10)==0xCC))      //ģ������ת��Ӧ�𣨸���Ƭ����
             {
                   if(AutoSentFlag==1)
                    {
                      SendTimes--;
               
                      if(SendTimes==0)
                       {
                          AutoSentFlag=0; 
                          
                          LedStuOff;
                        
                           if((WBStu==Active)&&((P4OUT&BIT5)==0))//�ֶ�����״̬
                             {
                             StuCount=0; 
                             WDTCTL=WDTPW+WDTHOLD;
                             
                             NormalDisp();
                             
                             WDTCTL=WDTPW+WDTHOLD;
                             }
                            
                            ReportFlag=Off;
                           
                            if(AutoSendForHander==Off) //�ڸ���վ�ϱ������������ָ��ŵ�
                             {
                             
                             RecoverFlag=On;
                             delay_ms(600);
                             ConfigFlag=1;            //�����ָ�����ͨ�� 
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
         *(rxdata+md_crc)=0;             //����շ�������
        }
     
     
     
    }
    
    
}


void CommNormalData(uchar *txdata,uchar *ramppt)// �����ϴ�����
{
  
      *txdata=0x7E;
      *(txdata+1)=0x30;//ת��Ӧ��
      *(txdata+2)=0x2A;
      
      *(txdata+3)=0xFF;
      *(txdata+4)=0xFF;
      *(txdata+5)=0xFF;
      *(txdata+6)=0xFF;
      *(txdata+7)=0xFF;
      *(txdata+8)=0xFF;    //�㲥�����л�վ
      
      *(txdata+9)=0x02;    //ת��Ӧ��ָ��
      /******************************************��Ϣ��**********************************************************/
      *(txdata+10)=0xAB;
    //  *(txdata+11)=0x53;//������
      *(txdata+12)=0x1E;//�ֽ�����
      
      *(txdata+13)=*(ramppt+0X1a);//PID1
      *(txdata+14)=*(ramppt+0X1b);//PID2
      *(txdata+15)=*(ramppt+0X1c);//PID3
      *(txdata+16)=*(ramppt+0X1d);//PID4
      
      *(txdata+17)=*(ramppt+0X1e);//UID1
      *(txdata+18)=*(ramppt+0X1f);//UID2
      
      
      
      *(txdata+19)=*(ramppt+0x03);   //�����
      *(txdata+20)=*(ramppt+0x02);
      
      *(txdata+21)=*(ramppt+0x05);   //������ 
      *(txdata+22)=*(ramppt+0x04);
      
      *(txdata+23)=*(ramppt+0x07);   //������    
      *(txdata+24)=*(ramppt+0x06);
      
      
        
      *(txdata+25)=0xFF;
      *(txdata+26)=*(ramppt+0X08);//���
      
      *(txdata+27)=*(ramppt+0X0a);//�ź�  
      *(txdata+28)=*(ramppt+0X0c);//�Ѻ� 
      
      *(txdata+29)=*(ramppt+0X0e); //ģ���ŵ� 
      *(txdata+30)=*(ramppt+0X10); //ģ�鹦�� 
      
      *(txdata+31)=*(ramppt+0x13);//��������
      *(txdata+32)=*(ramppt+0x12);
      
      *(txdata+33)=*(ramppt+0x15);   //��������ʱ��
      *(txdata+34)=*(ramppt+0x14);
      
    
      *(txdata+35)=PV[0]>>8;               //�ϲ��¶� 
      *(txdata+36)=PV[0];
					
      *(txdata+37)=PV[1]>>8;               //�в��¶�
      *(txdata+38)=PV[1];
					
      *(txdata+39)=PV[2]>>8;                //�²��¶�
      *(txdata+40)=PV[2];
   
  
      
      *(txdata+41)=0xBA;   //�����ʶ
     
      *(txdata+42)=BatStu;//���״̬
        
      float_byte.f_int=CrcCheck(33,txdata+10); 
      
      *(txdata +43)=float_byte.f_byte[0];	        //crc���ֽ���ǰ
      *(txdata +44)=float_byte.f_byte[1];	        //crc���ֽ���ǰ
      
      /***************************************��Ϣ��***********************************************************/         
      
      
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
      
      *(txdata+9)=0x31;//д����ָ��
      
      *(txdata+10)=*(ramppt+0X1a);
      *(txdata+11)=*(ramppt+0X1b);
      *(txdata+12)=*(ramppt+0X1c);
      *(txdata+13)=*(ramppt+0X1d);     //PID���޷����ģ�
      *(txdata+14)=*(ramppt+0X1e);  //UID1
      *(txdata+15)=*(ramppt+0X1f);  //UID2   
      
      *(txdata+18)=0xCC;
      *(txdata+19)=0xCC;

      SentNum=20; 
 
      if(ReportFlag==On)
      {
      *(txdata+16)=*(ramppt+0X16); //ģ���ϱ��ŵ�
      *(txdata+17)=7; //ģ�鹦��
      
      }
      else
      {
      *(txdata+16)=*(ramppt+0X0e); //ģ���ŵ�
      *(txdata+17)=*(ramppt+0X10); //ģ�鹦��
              if(IDSetFlag==On)
              {
               *(txdata+2)=0x14;//�ֽ�����5��
               *(txdata+9)=0x32;//дPID����ָ��
               
                *(txdata+10)=*(ramppt+0X3a);
                *(txdata+11)=*(ramppt+0X3b);
                *(txdata+12)=*(ramppt+0X3c);
                *(txdata+13)=*(ramppt+0X3d);     //PID���޷����ģ�
                *(txdata+14)=*(ramppt+0X3e);  //UID1
                *(txdata+15)=*(ramppt+0X3f);  //UID2   
                                 
                *(txdata+16)=*(ramppt+0X2e);       //�ָ������ŵ� 
                *(txdata+17)=*(ramppt+0X30);       //�ָ����ݹ���
               
                *(txdata+18)=0xA2;
                *(txdata+19)=0x2A;
                *(txdata+20)=0x3A;
                *(txdata+21)=0x5B;
                *(txdata+22)=0x4C;//����̶��ֽ�

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
      
      *(txdata+9)=0x30;//������ָ��
      
      
      *(txdata+10)=0xCC;
      *(txdata+11)=0xCC;
      
      
      SentNum=12;
 

}

/***********************************************************************
modbus crcУ�飬���ð��ֽ��㷨
��ڲ�����У����ֽ���len����������
���ڲ�����CRC
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



