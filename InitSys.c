
#include <io430.h>
#include <in430.h>
#include <intrinsics.h>
#include "Predefined.h"
#include "InitSys.h"


void InitSysBasic(void)
{
/*********************************************************************/    
  
    BCSCTL2  =0x88;                //MCLK=SMCLK=XT2CLK=2mhz
  /********************I/O*********************************************/ 
         
    P1DIR=0x73;                //p1.3为PQTest。P1.2为磁性开关，P1.7为下发唤醒
    P1IE=0;
   
    P1OUT&=~BIT5;
   
    P2DIR=0X17;                //BIT7(KEY),BIT6(KEY1),BIT5(KEY2),BIT3(KEY4),BIT4(ADPOWER)
    P2IES=0X80;                //下降沿触发
    P2IFG=0;
    P2IE=0X80;                 //开P2.7中断
    
     
    P3DIR=0XDF;                  //BIT5=RXD
    P3SEL |=(BIT4+BIT5);         //BIT4=TXD,BIT5=RXD
    
    
    
   
    P4DIR=0XFF;                   //BIT0-BIT5=LCD CTR  
    P4OUT&=~BIT7;
    
    P5DIR=0XFF;
 
   
    P6DIR=0XFB;                    //BIT2=BatTest9IN),BIT3=SLEEP(OUT);
   
  /*************************flash*****************************************/ 
  
  FCTL2=FWKEY+FN2+FSSEL_1;               //MCLK/5=(2000000)/5=400KHZ

}





void InitSysForStandby(void)
{
    
    
    //P1SEL|=BIT5;                //TACCR0输出
    P1SEL&=~BIT6;
    P1OUT&=~BIT6;
    
    P1IES=0x04;                   //p1.2下降沿触发,p1.7上升沿触发
    P1IFG=0;
    P1IE=0X84;                 //开P1.7,p1.2中断，下发唤醒中断
    
    P2DIR|=BIT6+BIT5+BIT3; 
    P2OUT&=~( BIT6+BIT5+BIT3); 
    
    //P4SEL|=BIT7;               //TBCLK IN
    P6SEL&=~BIT2;              //BIT2=AD2
    
    P1SEL&=~BIT4;
    P1DIR&=~BIT4;
    //P1DIR&=~BIT2;
 
 /****************************TA***********************************/  
    TACTL=0;    //ACLK,增模式
    TACCTL0=0;       //翻转输出
    TACCTL1=0;
    TACCTL2=0;
                      
    TAR=0; 
   // TACCR0=164;          //输出周期10ms的脉冲作为TB的时钟
     /****************************TB***********************************/                  
    TBCTL=TBSSEL_1+MC_1;  //ACLK,增模式
    TBCCTL0=CCIE;
    TBCCTL1=0;           //关TBCCR1中断
    TBCCR0=6553;        //0.2秒中断
    TBR=0;
    
    
    /**************ADC12*************************************/ 
    ADC12CTL0&=~ENC;
    ADC12CTL0 = 0;                                  
    ADC12CTL1 =0;            
    ADC12MCTL2=0;                                       
    ADC12IE =0;                                          
     
    /**************UART*************************************/ 
   // U0BR1=0;
   // U0BR0=0x03;                //U0BR1*256+U0BR0=32768/9600=3;
    //U0CTL=CHAR;               //8位停止位，无校验，1个停止位
    //U0TCTL=SSEL0;              //ACLK
   //ME1=URXE0+UTXE0;          //使能
   ME1=URXE0;          //使能接收
   IE1=URXIE0+UTXIE0;        //开接收中断
    
    
    
}






void InitSysForPowerOff(void)
 {
    P1IE=0;//模块下发唤醒不起作用
    P1DIR&=~BIT4;
    //P1DIR&=~BIT2;
   
    P1SEL&=~BIT6;
    P1OUT&=~BIT6;         //输出低电平
    
    P1SEL&=~BIT3;
    P1SEL&=~BIT4;
    
    P6SEL&=~BIT2;                  //BIT2=AD2
    
    P2DIR|=BIT6+BIT5+BIT3; 
    P2OUT&=~( BIT6+BIT5+BIT3); 
    /*****************************TA***********************************/ 
    TACTL=0;    
    TACCTL0=0;       
    TACCTL1=0;
    TACCTL2=0;
    /****************************TB***********************************/
    TBCTL=0;
    TBCCTL1=0;
    TBCCTL0=0;
    TBCCTL2=0;              //关闭监听中断
    TBR=0;
    TBCCR1=0;  
   /********************************AD12*********************************************/       
    ADC12CTL0&=~ENC;
    ADC12CTL0 = 0;                                  
    ADC12CTL1 =0;            
    ADC12MCTL2=0;                                       
    ADC12IE =0;        
    


  /******************************UART**************************************/  
    ME1=0;                //关闭发送，接收
    IE1=0;                //关闭发送，接收中断
    
 }

void InitSysForActive(void)
 {
  
    P1SEL|=(BIT6+BIT4+BIT3);   //BIT3=Q_IN(TA2),BIT4=SMCLK,BIT6=PWM(TA1)
    P1SEL|=BIT4;
    P1DIR|=BIT4;
    //P1DIR|=BIT2;
    P1IES=0x04;                   //p1.2下降沿触发,p1.7上升沿触发
    P1IFG=0;
    P1IE=0X84;                 //开P1.7,p1.2中断，下发唤醒中断
    
    P2DIR=0X17;
    
    P6SEL|=BIT2;                  //BIT2=AD2
 /*****************************TA***********************************/  
    TACTL=TASSEL_2+MC_1+TAIE;        //Fta=SMCLK=2MHz;MODE=UP;
    TACCTL0=0;
    TACCTL1=OUTMOD_6;                 //TOGGLE-SET
    TACCTL2=CM_2+CAP;                 //下降沿捕获            
    TACCR0=PWM_TIME;
    TACCR1=PWMOUT;
    TAR=0; 
  /****************************TB***************************************/
    TBCTL=TBSSEL_1+MC_2+TBIE;//ACLK,连续模式
    TBCCTL1=CCIE;
    TBCCTL2=0;              //关闭监听中断
    TBCCTL0=0;
    TBR=0;
    TBCCR1=1966;            //60ms中断一次  
 
/********************************AD12*********************************************/

    ADC12CTL0 = ADC12ON+MSC+SHT0_2+REFON;   
   // ADC12CTL0 = ADC12ON+MSC+SHT0_2; // Setup ADC12
    ADC12CTL1 =CSTARTADD_2+ SHP+ADC12SSEL_3+CONSEQ_0;            // A2输入，smclk,单通道多次
    ADC12MCTL2 = INCH_2 +SREF_1;                                        //REF:VREF+---AVSS,A2,
 // ADC12IE = 0x0004;                                           // Enable ADC12IFG.2
  
 /******************************UART**************************************/
 
   U0BR1=0;
   U0BR0=0xd0;                //U0BR1*256+U0BR0=2000000/9600=208;
   U0CTL=CHAR;               //8位停止位，无校验，1个停止位
   U0TCTL=SSEL1;              //SMCLK
   //ME1=URXE0+UTXE0;          //使能
   ME1=URXE0;          //使能
   IE1=URXIE0+UTXIE0;        //开中断
     
  
   
  

 
 }
