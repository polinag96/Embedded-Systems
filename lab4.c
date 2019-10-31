int main(void)
{
WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer
P1DIR |= BIT0;
CCTL0 = CCIE;
CCR0 = 16000;
TACTL = TASSEL_1 + MC_1; // aclk, up-mode
__bis_SR_register(LPM0_bits + GIE);
return 0;
}
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_A0(void){
    P1OUT ^= BIT0;

}


#include <msp430.h>
/**
 * main.c
 */
unsigned int old_TA1CCR0=0;
int tDif=0;
int main(void)
{
WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer
P1DIR |= BIT0;
P2SEL |= BIT3;
TA1CTL |= TASSEL_1 + MC_2; // aclk
TA1CCTL0|=CM_1 +CCIS_1+CAP+CCIE;
__bis_SR_register(LPM0_bits + GIE);
return 0;
}
#pragma vector = TIMER1_A0_VECTOR
__interrupt void Timer0_A0(void){
    P1OUT ^= BIT0;
    tDif=TA1CCR0-old_TA1CCR0;
    if(tDif<0){
        tDif=0xFFFF+tDif;
    }
    old_TA1CCR0=TA1CCR0;
}



#include <msp430.h>
/**
 * main.c
 */
int main(void)
{
WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer
P1DIR |=BIT2;
P1SEL |= BIT2;
TA0CCR0 = 8000;
TA0CCTL1 = OUTMOD_6; //toggle/set
TA0CCR1 = 2000;
TA0CTL = TASSEL_1 + MC_1; // aclk, upmode

__bis_SR_register(LPM0_bits + GIE);
return 0;
}
