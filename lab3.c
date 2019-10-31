#include <msp430.h>
/**
 * main.c
 */
int main(void)
{
 WDTCTL = WDTPW +WDTHOLD;  // Stop Watchdog Timer
 P1DIR |= 0x13; // P1.0,1 and P1.4 outputs
 P1SEL |= 0x11;  // P1.0,4 ACLK, SMCLK
 while(1)
 {
     P1OUT |= 0x02; // P1.1 = 1
    P1OUT &= ~0x02; // P1.1 = 0
 }
 return 0;
}



#include <msp430.h>
/**
 * main.c
 */
int main(void)
{
 WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer
 P1DIR |=0x13;
 P1SEL |= 0x11;
 BCSCTL1 |= DIVA_1;// ACLK/2
 BCSCTL2 |= DIVS_2;// SMCLK/4
 while(1)
 {
     P1OUT |=0x02;
     P1OUT &=~0x02;
 }
 return 0;
}




#include <msp430.h>
/**
 * main.c
 */
int main(void)
{
 WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer
 P1DIR &= ~BIT3;
 P1REN |=BIT3;
 P1OUT |=BIT3;
 P1IE |=BIT3;
 P1IES |=BIT3;
 P1DIR |=0x13;
 P1SEL |= 0x11;
 BCSCTL1 |= DIVA_1;// ACLK/2
 BCSCTL2 |= DIVS_2;// SMCLK/4
 __bis_SR_register(LPM4_bits+GIE);
 while(1)
 {
     P1OUT |=0x02;
     P1OUT &=~0x02;
 }
 return 0;
}
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void){
    P1IFG &= ~BIT3; // reset interrupt
    __bic_SR_register_on_exit(LPM4_bits); // exit LPM
    return;
}
