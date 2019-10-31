#include <msp430.h>
int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  ADC10CTL0 = ADC10SHT_2 + ADC10ON + ADC10IE; // ADC10ON, interrupt enabled
  ADC10CTL1 = INCH_3;                       // input A1
  ADC10AE0 |= BIT3;                         // PA.1 ADC option select
  P1DIR |= 0x01;                            // Set P1.0 to output direction
  for (;;)
  {
    ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
    __bis_SR_register(CPUOFF + GIE);        // LPM0, ADC10_ISR will force exit
  }
}
// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
    if (ADC10MEM < 238)
      P1OUT &= ~0x01;                       // Clear P1.0 LED off
    else
      P1OUT |= 0x01;                        // Set P1.0 LED on
    __bic_SR_register_on_exit(CPUOFF);
    return;
  }





#include <msp430.h>
int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  ADC10CTL0 = ADC10ON + ADC10IE; // ADC10ON, interrupt enabled
  ADC10CTL1 = INCH_3 + CONSEQ_2;                       // input A1
  ADC10AE0 |= BIT3;                         // PA.1 ADC option select
  P1DIR |= 0x01;                            // Set P1.0 to output direction
  ADC10CTL0 |= ENC + ADC10SC + MSC;             // Sampling and conversion start
  __bis_SR_register(CPUOFF + GIE);        // LPM0, ADC10_ISR will force exit
}
// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
    if (ADC10MEM < 238)
      P1OUT &= ~0x01;                       // Clear P1.0 LED off
    else
      P1OUT |= 0x01;                        // Set P1.0 LED on
    return;
  }





#include <msp430.h>
int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  ADC10CTL0 = ADC10SHT_2 + ADC10ON + ADC10IE; // ADC10ON, interrupt enabled
  ADC10CTL1 = INCH_3;                       // input A1
  ADC10AE0 |= BIT3;                         // PA.1 ADC option select
  CCTLO0 = CCIE;  
  CCR0 = 125; // 125Hz
  TACL = TASSEL_1 + MC_1; // aclk, up
  P1DIR |= 0x01;                            // Set P1.0 to output direction
  for (;;)
  {
    __bis_SR_register(CPUOFF + GIE);        // LPM0, ADC10_ISR will force exit
  }
}
// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
    if (ADC10MEM < 238)
      P1OUT &= ~0x01;                       // Clear P1.0 LED off
    else
      P1OUT |= 0x01;                        // Set P1.0 LED on
    __bic_SR_register_on_exit(CPUOFF);
    return;
  }
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_A0(void){
 ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
}
