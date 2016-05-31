
#include <io430.h>
#include <in430.h>
#include "Predefined.h"
#include "CalFromTab.h"

/*pt1000(OK)*/
signed int const tb_pt1000[35]=
 {-100,-2440,-50,-1250,0,0,50,1230,100,2500,150,3724,200,4955,250,6210,300,7418,350,8651,400,9833,450,11052,500,12238,670,16280,840,20246,
  1000,23915,1180,28121,32767};


/*(原始曲线)

signed int const tb_pt1000[35]=
 {-100,-2440,-50,-1220,0,0,50,1217,100,2432,150,3644,200,4855,250,6063,300,7268,350,8471,400,9673,450,10872,500,12068,670,16120,840,20146,
  1000,23915,1180,28121,32767};
*/
/*
signed int const tb_pt1000[35]=
 {-100,-2440,-50,-1220,0,0,50,1200,100,2432,150,3624,200,4855,250,6063,300,7290,350,8500,400,9685,450,10900,500,12120,670,16250,840,20266,
  1000,23915,1180,28321,32767};

*/
	/*			                      
signed int const tb_pt1000[25]={
              
                -1999,-8055,-1465,-5801,-952,-3720,-505,-1954,
                 -180,-692,-17,-66,0,0,1,3,
                109,416,396,1505,864,3256,1000,3760,32767};*/
  
				                





/********************************************************************************************************************


**********************************************************************************************************************/

signed int CalFromTab(uchar input_ch,uint *incal00,uint *incalfs)

{
uchar      *overflow;
//uint       incal00,incalfs,old_cal;
uint      old_cal;
signed   long    cal_temp,ktemp1,ktemp2; 
float   temp00,temp01;
       

        switch(input_ch)
         {
           case  1:
                 //incal00=In1Cal00;
	         //incalfs=In1CalFS;
                   
	         overflow=&DataOverflow[0];
	         old_cal=In1OldCal;
                 break;
           case  2:
                 //incal00=In2Cal00;
	         //incalfs=In2CalFS;
           
	         overflow=&DataOverflow[1];
	         old_cal=In2OldCal;
                 break;
           case  3:
                // incal00=In3Cal00;
	        // incalfs=In3CalFS;
           
	         overflow=&DataOverflow[2];
	         old_cal=In3OldCal;
                 break;
         }

	

	 //ktemp0=SAMP[0];
	 ktemp1=SAMP[0];
	 ktemp2=SAMP[1];
       
	
		 // cal_temp=2*ktemp2-ktemp1;
         
		 cal_temp=2*ktemp2-ktemp1+((ktemp1-ktemp2)*ktemp1/(*incal00))/6;
			  
                 if((MenuStuNum==0x93)&&(input_ch==1))
                  {
                    *incal00=(uint)cal_temp;
                   // *(incal00+2)=SAMP[0];
                    //*(incal00+4)=SAMP[1];                 
                  }
                 if((MenuStuNum==0x95)&&(input_ch==2))
                  {
                    *incal00=(uint)cal_temp;
                  } 
                 if((MenuStuNum==0x97)&&(input_ch==3))
                  {
                    *incal00=(uint)cal_temp;
                  }
                 if((MenuStuNum==0x94)&&(input_ch==1))
                  {
                    *incalfs=(uint)cal_temp;
                   // *(incalfs+2)=SAMP[0];
                    //*(incalfs+4)=SAMP[1];                
                  }
                 if((MenuStuNum==0x96)&&(input_ch==2))
                  {
                    *incalfs=(uint)cal_temp;
                  } 
                 if((MenuStuNum==0x98)&&(input_ch==3))
                  {
                    *incalfs=(uint)cal_temp;
                  }
                 
                 if(MenuStuNum==0x99)
                   {
                    *incal00=(uint)cal_temp;
                   }
                   
           
                 if(MenuStuNum==0x9A)
                  {
                   *incalfs=(uint)cal_temp;
                  }
   	
         //*incalfs=0xafeb;
         //*incal00=0x8387;
                
	 temp01=(float)((*incalfs)-(*incal00));
	 
	 temp01=(cal_temp-(*incal00))/temp01;  //百分比
	 
	 cal_temp=(signed  long)(temp01*23915.0);
	 
	 //cal_temp=12238;	//t
	      

			   cal_temp=SearchTab((signed int)cal_temp,overflow);
			   
			   if(*overflow==0)
			   {
		
				
				 temp01=(float)(old_cal-cal_temp);
                                 
		            if((temp01 >-5.01)&&(temp01<=5.01)) 
		        
				 {
				   temp00=(old_cal*3+cal_temp)/4.0;				 //小信号变化滤波
				   
				  // temp00=(old_cal*+cal_temp)/2.0;	
				   old_cal=(signed long)temp00;
				  // *old_cal=cal_temp;
				   //DSP[0]=0xfe;
				 }
				 else
				 {

			  	//temp00=(*old_cal+(float)cal_temp)/2.0;			//大信号变化不滤波		
				//*old_cal=cal_temp;
				// DSP[1]=0xfe;
				 temp00=cal_temp;
				 old_cal=cal_temp;
				} 
				   
			

				//temp00=cal_temp;

		 		
				//temp01=(adjust[3]-adjust[1])/(adjust[2]-adjust[0]);
         		       //cal_temp=(temp00-adjust[0])*temp01+adjust[1]+0.5;
			 }
			 
			   	
				return((signed int)cal_temp);

			
 


}

/********************************************************************************************************************


**********************************************************************************************************************/     
signed long   SearchTab(signed int p00,uchar *overflow00)

{
    uchar   i,j;
    float    temp1,temp2,temp3,temp4;
    signed int   const  *cal_p ;
    
	
    cal_p=tb_pt1000;	            
	
	                              //指向第一个脉冲值

	j=0;
	i=0;
		 do
		 {
			   cal_p=cal_p+1;
		       if(p00 < (*cal_p))
		       {
		         j++;
				 break;
			   }
			   else
			   {
			     i++;
			     cal_p=cal_p+1;
			   }
			   
		 }
		  while((*cal_p)!=32767);

      if(j==0)
	   {
	   *overflow00=2;		   //H.0FL
	    temp4=1180;
	   }
	   else if(i==0)
	   {			          //L.OFL
	   *overflow00=3;
	   temp4=-100;
	   }
	   else
	   {
	   *overflow00=0;             

	  
	   temp1=*(cal_p-1);				
	   temp2=*(cal_p-2);
       temp3=*(cal_p-3); 

	   
	  
       temp4=(float)(*cal_p)-temp2;	
	   	  
       temp1=(temp1-temp3)/temp4;

       temp4=((float)p00-temp2)*temp1+temp3;

	   if(temp4 > 0.1)
	       temp4=temp4+0.5;

	   if(temp4 <-0.1)
	   	   temp4=temp4-0.5;
	   
	   }
	   return((signed long)temp4);
		
}		