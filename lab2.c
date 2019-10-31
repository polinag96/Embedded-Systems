#include <msp430.h>
/**
 * main.c
 */
int main(void)
{
 WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer
 P1DIR |= BIT0; // P1.0 as LED output
 P1DIR &= ~BIT3; // P1.3 as Button input
 P1OUT |= BIT3; // pull-up resistor
 P1REN |= BIT3; // resistor enabled
 while (1){
     if (!(P1IN & BIT3)){ // button pressed
         P1OUT ^= BIT0; // enable LED
     }
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
 P1DIR |= BIT0; // P1.0 as LED output
 P1DIR &= ~BIT3; // P1.3 as Button input
 P1OUT |= BIT3; // pull-up resistor
 P1REN |= BIT3; // resistor enabled
 while (1){
     if (!(P1IN & BIT3)){ // button pressed
  __delay_cycles(10000); // initial delay
while(P1IN & BIT3){ // while the pin is released, do nothing
}
__delay_cycles(10000); // delay on rise to “1”
         	P1OUT ^= BIT0; // enable LED 
     }
 }
 return 0;
}





 
int main(void)
{
 WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer
 P1DIR |= BIT0; // p1.0 led output
 P1DIR &= ~BIT3; // p1.3 button input
 P1REN |= BIT3; // res enabled
 P1OUT |= BIT3; // pull-up res
 P1IE |= BIT3; // enable interrupt
 P1IES |= BIT3; // high-low
 //P1IFG &= ~BIT3; // clear interrupt flag
 __bis_SR_register(LPM4_bits + GIE);
}
#pragma vector = PORT1_VECTOR
__interrupt void Port_1(void) // interrupt function
{
    P1OUT ^= BIT0; // enable led
    P1IFG &= ~BIT3; // clear interrupt
    return;
}




int main(void)
{
 WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer
 P1DIR |= BIT0; // p1.0 led output
 P1DIR &= ~BIT3; // p1.3 button input
 P1REN |= BIT3; // res enabled
 P1OUT |= BIT3; // pull-up res
 P1IE |= BIT3; // enable interrupt
 P1IES |= BIT3; // high-low
 //P1IFG &= ~BIT3; // clear interrupt flag
 __bis_SR_register(LPM4_bits + GIE);
}
#pragma vector = PORT1_VECTOR
__interrupt void Port_1(void)
{
    __delay_cycles(100000); // delay on fall 
    while(!(P1IN & BIT3)){ // when press is released, do nothing
    }
    __delay_cycles(100000); // delay on the rise to “1”
    P1OUT ^= BIT0; // enable led
    P1IFG &= ~BIT3; // clear interrupt
    return;
}



