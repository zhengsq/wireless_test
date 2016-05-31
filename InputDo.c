
#include <io430.h>
#include <in430.h>
#include <intrinsics.h>

#include "Predefined.h"
#include "InputDo.h"
#include "LcdDriver.h"


void InputDo(void)
 {
   uint temp1;
   signed   long  temp,temp2,temp3;
   uchar k;

  

      
      
      temp1=TACCR2;
      
      
       if(TACCTL2_bit.CCIFG==1)
    {
         TACCTL2_bit.CCIFG=0;//Çå²¶×½±êÖ¾
      
      
          
          
          
           if((CAPTURE_CNT%37)>=7)
       // if((CAPTURE_CNT%67)>=7)
                {
            
                    CAPTURE_ADD+=temp1;
                    
                    if(CAPTURE_ADD>=0XFF00)
                        {
                            CAPTURE_ADD=0xff00;
              
                        }
                 }
         
          CAPTURE_CNT++; 
          
         if(CAPTURE_CNT >= 74)  
       //  if(CAPTURE_CNT >= 134) 
          {
                 CAPTURE_CNT=0;
                 InputSampleOver=1;
                 TACCTL2=0;
          }
         
          if((CAPTURE_CNT%37)==0)
       // if((CAPTURE_CNT%67)==0)
          {
            
           CAPTURE_NOP=0;
            switch(CAPTURE_CNT/37)
       // switch(CAPTURE_CNT/67)
           
             {
               case 0:
                      k=1;
                      if((CAPTURE_ADD > 0XBF00)||(CAPTURE_ADD < 0X7500))
                      {
                          
                       DataOverflow[InputChannel-1]=1;
        
                      }
                     
                     
                      break;
                      
               case 1:
                      k=0;
                      P2OUT|=BIT0;            //¸º¶ËµçÆ½
                      
                      if((CAPTURE_ADD > 0XBF00)||(CAPTURE_ADD< 0X7500))
                      {
                          
                       DataOverflow[InputChannel-1]=1;
                       
     
                      }
                      else
                      {
                        
                       DataOverflow[InputChannel-1]=0; 
                        
                      }
                      
                     break;
               
               default:
                      _NOP();
             }
           
            if(DataOverflow[InputChannel-1]==1)
            {
              InputSampleOver=1;
              TACCTL2=0;
              CAPTURE_NOP=0;
              CAPTURE_CNT=0;//1215
              
               
            }
           else
           {
            temp2=(signed long)SAMP[k];
            
            temp3=(signed long)CAPTURE_ADD;
            
            temp=temp2-temp3;
            
             if((temp>=-15L)&&(temp<=15L))
            
           
            	  {
            	  	            	  	
                  temp=(temp2*4+temp3)/5;//·ÀÖ¹Ìø×Ö
                 // temp=(temp2+temp3)/2;//·ÀÖ¹Ìø×Ö
                  
                  SAMP[k]=(unsigned int)temp;
                  }
            else  
                  {
                  SAMP[k]=(unsigned int)CAPTURE_ADD;
                  
                  }
           }
           
           
           
            CAPTURE_ADD=0;
            
            
            
     
          }
         
    }
       else
    {
          
          CAPTURE_NOP++;
          if(CAPTURE_NOP==20)
           {
               
               DataOverflow[InputChannel-1]=1;
               InputSampleOver=1;
               TACCTL2=0;
               CAPTURE_NOP=0;
               CAPTURE_CNT=0;//1215
               CAPTURE_ADD=0;
           }
        
     }
        
       
        // CAPTURE_CNT++;
         
  
  }
   
   
 
