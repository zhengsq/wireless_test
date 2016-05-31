#include <io430.h>
//#include <in430.h>
#include <intrinsics.h>
#include"Predefined.h"
#include"LcdDriver.h"

/***********************************************************
NT7534驱动程序
************************************************************/




uchar const ComTable[]={3,2,1,0,7,6,5,4,};

void CheckBusy (void)
{
  uchar CheckTime=0;
  while(CheckTime<3)
   {
  IOPortIn;
  LcdCommand;
  ClrLcdCS;
  LcdRead;
  LcdNRW;
  if((P5IN&0x80)==0)
            CheckTime=3;       //Status Busy =1 , wait...
  CheckTime++;
  SetLcdCS;
  IOPortOut;
   }
}

void WriteCommand( uchar CommandByte )
{
         CheckBusy();
         LcdCommand;
         ClrLcdCS;
         
         P5OUT=CommandByte;
         LcdWrite;
         LcdNRW;
         SetLcdCS;
}

void WriteData( uchar DataByte )
{
         CheckBusy();
         LcdData;
         ClrLcdCS;
         
         P5OUT=DataByte;
         LcdWrite;
         LcdNRW;
         SetLcdCS;
         
}
/*
Uchar ReadData( void )
{
         CheckBusy();
         IOPortIn;
         SetLcdA0;
         ClrLcdCS;
         ClrLcdRD;
         SetLcdWR;
         return P5IN;
}
*/


void LcdClear( void )
{
         uint i,j;
         WriteCommand(0x40);      //Set Display Start Line = com0
         for(i=0;i<8;i++)
         {
                 WriteCommand(0xB0|ComTable[i]); //Set Page Address
                 WriteCommand(0x10);      //Set Column Address = 0
                 WriteCommand(0x00);      //Colum from 0 -> 132 auto add
                 for(j=0;j<132;j++)
                 {
                         WriteData( 0 );
                 }
         }
}

void LcdInit( void )
{
         LcdResetON;
         delay_us(100);
         LcdResetOff;
         delay_us(100);
         WriteCommand(0xE2);
         delay_us(100);
         
         WriteCommand(0xA2);      //1/64 Duty 1/9 Bias
         WriteCommand(0x2C);      //
         delay_us(100);
         WriteCommand(0x2E);
         delay_us(100);
         WriteCommand(0x2F);
         delay_us(100);
          
         WriteCommand(0xA0);      //ADC select   --> right
         WriteCommand(0xC0);      //com1 --> com64
         
         WriteCommand(0x81);      //Sets V0
         WriteCommand(0x30);      //内部电位器调节对比度
         WriteCommand(0x23);      //
         WriteCommand(0xA6);      //Normal Display (not reverse dispplay)
         WriteCommand(0xA4);      //Entire Display Disable
        
         LcdClear();
         WriteCommand(0xAF);      //Display ON
                        
         WriteCommand(0x40);      //Set Display Start Line = com0
         WriteCommand(0xB0);      //Set Page Address = 0
         WriteCommand(0x10);      //Set Column Address 4 higher bits = 0
         WriteCommand(0x01);      //Set Column Address 4 lower bits = 1 , from IC SEG1 -> SEG129
}

//显示ASICC字符的函数

void LcdCharWrite(uchar col,uchar page,uchar datanum ,uchar  const *datappt)
 {
        uchar i,j;
         
         WriteCommand((page&0x07)|0xB0);            //Set Page Address
         WriteCommand( ((col+4)>>4) | 0x10);       //Set Column Address High Byte
         WriteCommand( (col+4)&0x0F );            //Low Byte   Colum from 8 -> 120 auto add

         for(j=0;j<datanum;j++)
          {
               for(i=0;i<8;i++)
               {
                WriteData( datappt[i+16*j] );
               }
          }
         
         page--;                                        //下半字符page+1
         
         WriteCommand((page&0x07)|0xB0);                     //Set Page Address
         WriteCommand( ((col+4) >> 4) | 0x10);              //Set Column Address High Byte
         WriteCommand( (col+4) & 0x0F );                    //Low Byte   Colum from 8 -> 120 auto add
         
        for(j=0;j<datanum;j++)
          {
               for(i=0;i<8;i++)
               {
                WriteData( datappt[i+8+16*j] );
               }
          }
         
        
 }

void LcdOneByteWrite(signed char col2,uchar page2,uchar order2,uchar keystu)
{
         uchar i2;
         uint x2;
         
         x2 = order2*0x10;                           //每个16 byte
         WriteCommand((page2&0x07)|0xB0);   //Set Page Address
         WriteCommand( ((col2+8)>>4) | 0x10);       //Set Column Address High Byte
         WriteCommand( (col2+8)&0x0F );            //Low Byte   Colum from 8 -> 120 auto add


         for(i2=0;i2<8;i2++)
         {
                 WriteData( CharCode[x2] );
                 x2++;
         }
         page2--;                                        //下半字符page+1
        
         WriteCommand((page2&0x07)|0xB0);        //Set Page Address
         WriteCommand( ((col2+8) >> 4) | 0x10);              //Set Column Address High Byte
         WriteCommand( (col2+8) & 0x0F );                    //Low Byte   Colum from 8 -> 120 auto add
        
         for(i2=0;i2<8;i2++)
         {
                 WriteData( CharCode[x2]+keystu );
                 x2++;
         }
         page2--;                                  //写完一个字符page还原
}

void LcdTwoByteWrite(uchar col3,uchar page3,uchar datanum3 ,uchar  const *datappt3)
{
         uchar i3,j3;
         
         WriteCommand((page3&0x07)|0xB0);            //Set Page Address
         WriteCommand( ((col3+8)>>4) | 0x10);       //Set Column Address High Byte
         WriteCommand( (col3+8)&0x0F );            //Low Byte   Colum from 8 -> 120 auto add

         for(j3=0;j3<datanum3;j3++)
          {
               for(i3=0;i3<16;i3++)
               {
                WriteData( datappt3[i3+32*j3] );
               }
          }
         
         page3--;                                        //下半字符page+1
         
         WriteCommand((page3&0x07)|0xB0);        //Set Page Address
         WriteCommand( ((col3+8) >> 4) | 0x10);              //Set Column Address High Byte
         WriteCommand( (col3+8) & 0x0F );                    //Low Byte   Colum from 8 -> 120 auto add
         
        for(j3=0;j3<datanum3;j3++)
          {
               for(i3=0;i3<16;i3++)
               {
                WriteData( datappt3[i3+16+32*j3] );
               }
          }
         
        
}

void ClearLcdLine(uchar page4)
 {
   uchar i4;
        WriteCommand((page4&0x07)|0xB0);   //Set Page Address
        WriteCommand( 0x10);             //Set Column Address High Byte
        WriteCommand( 0x00 );            //Low Byte   Colum from 8 -> 120 auto add
        
               for(i4=0;i4<132;i4++)
               {
                WriteData( 0 );
               }
               
        page4--;
        
        WriteCommand((page4&0x07)|0xB0);   //Set Page Address
        WriteCommand( 0x10);             //Set Column Address High Byte
        WriteCommand( 0x00 );            //Low Byte   Colum from 8 -> 120 auto add
        
               for(i4=0;i4<132;i4++)
               {
                WriteData( 0 );
               }
   
 }
void  LcdPictureWrite(uchar col5,uchar page5,uchar len5 ,uchar  const *datappt5)
 {
     uchar i5;
     
         
        
         WriteCommand((page5&0x07)|0xB0);   //Set Page Address
         WriteCommand( ((col5+8)>>4) | 0x10);       //Set Column Address High Byte
         WriteCommand( (col5+8)&0x0F );            //Low Byte   Colum from 8 -> 120 auto add

         len5=len5*8;
         for(i5=0;i5<len5;i5++)
         {
                 WriteData( datappt5[i5] );
                 i5++;
         }
   
 }

void LcdDigitalWrite(uchar col6,uchar page6,uchar order6)
{
         uchar i6;
         uint x6;
         
         x6 = order6*16;                           //每个8 byte
         WriteCommand((page6&0x07)|0xB0);   //Set Page Address
         WriteCommand( (col6 >>4) | 0x10);       //Set Column Address High Byte
         WriteCommand( col6 & 0x0F );            //Low Byte   Colum from 8 -> 120 auto add


         for(i6=0;i6<8;i6++)
         {
                 WriteData( DIGITAL[x6]|0xC0 );
                 x6++;
         }
         
         page6--;
         WriteCommand((page6&0x07)|0xB0);   //Set Page Address
         WriteCommand( (col6 >>4) | 0x10);       //Set Column Address High Byte
         WriteCommand( col6 & 0x0F );            //Low Byte   Colum from 8 -> 120 auto add
        
         for(i6=0;i6<8;i6++)
         {
                 WriteData( DIGITAL[x6]|0x18 );
                 x6++;
         }
         
         
}

void LcdBoardWrite(uchar col7,uchar page7)
{
         uchar i7;
         
         WriteCommand((page7&0x07)|0xB0);        //Set Page Address
         WriteCommand( (col7 >>4) | 0x10);       //Set Column Address High Byte
         WriteCommand( col7 & 0x0F );            //Low Byte   Colum from 8 -> 120 auto add


         for(i7=0;i7<2;i7++)
         {
                 WriteData( 0xFF);
                 
         }
         
         page7--;
         WriteCommand((page7&0x07)|0xB0);        //Set Page Address
         WriteCommand( (col7 >>4) | 0x10);       //Set Column Address High Byte
         WriteCommand( col7 & 0x0F );            //Low Byte   Colum from 8 -> 120 auto add
        
         for(i7=0;i7<2;i7++)
         {
                 WriteData(0xF8 );
                 
         }
  
  
  
  
  
}
