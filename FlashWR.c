/********************************************************************
*********************************************************************
flash block read and flash block write
*********************************************************************
*********************************************************************/

#include <io430.h>
#include <in430.h>

#include <intrinsics.h>
#include"Predefined.h"
#include "FlashWR.h"


void WRFlash (uchar *ram_ptr, uchar *flash_ptr,uchar wr_num)
{
 
 uchar i;
 
 WDTCTL=WDTPW+WDTHOLD;
  _DINT();
 
  
// while(FCTL3&BUSY)
//            _NOP();
 
 FCTL1=FWKEY+ERASE;  //segment erase mode
 
 FCTL3=FWKEY;        //unlock flash
 
 
 
 *flash_ptr=0;        //start segment erase
 
// while(FCTL3&BUSY)  //wait 
//   _NOP(); 
 //FCTL1=FWKEY+WRT+BLKWRT;
 //while(FCTL3_bit.BUSY==0);
 FCTL1=FWKEY+WRT;   // write mode
 for (i=0;i<wr_num;i++)  // write para_value[] 
    {
       
      *flash_ptr++=*ram_ptr++;
     // while(FCTL3_bit.WAIT==0);
       //while(FCTL3&BUSY);
       
    }
 //FCTL1_bit.BLKWRT=0;
 
 FCTL1=FWKEY;      //reset flash
 
// while(FCTL3&BUSY)
//   _NOP();


 FCTL3=FWKEY+LOCK;  //lock flash
 
 WDTCTL=WDT_ARST_1000;
 
// delay_ms(10);
 
 _EINT();
}


void RDFlash ( uchar *ram_ptr, uchar *flash_ptr,uchar rd_num)
{
 
  uchar i,j;
  
 j=3;
 while(--j)
 {
 if((FCTL3&BUSY)==0)
              break;//wait
   
 }
 for(i=0;i<rd_num;i++)          // read flash
 {
   *ram_ptr++=*flash_ptr++;
 
 j=3;
 while(--j)
 {
 if((FCTL3&BUSY)==0)
              break;//wait
   
 }
  
   
 }
 
 //delay_ms(50);
}
 



