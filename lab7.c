#include <msp430.h>
/**
 * main.c
 */
long int temp;
int main(void)
{
 WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer
 ADC10CTL0 = ADC10ON + ADC10IE; // adc10 on, intr enab, repeat single channel conversion
 ADC10CTL1 |= INCH_3; //input a1
 ADC10AE0 |= BIT3; // P1.3 ADC INPUT TO MCU
 CCTL0 = CCIE;
 CCR0 = 213; // 150 Hz, 32k/150Hz
 TACTL = TASSEL_1 + MC_1; // aclk, up mode
 // UART AND SMCLK CONFIG
 if(CALBC1_1MHZ==0xFF)
 {
     while(1);
 }
 DCOCTL = 0;
 BCSCTL1 = CALBC1_1MHZ;                    // Set DCO
 DCOCTL = CALDCO_1MHZ;
 P1SEL = BIT1 + BIT2 ;                     // P1.1 = RXD, P1.2=TXD
 P1SEL2 = BIT1 + BIT2;
 UCA0CTL1 |= UCSSEL_2;                     // SMCLK
 UCA0BR0 = 8;                              // 1MHz 115200
 UCA0BR1 = 0;                              // 1MHz 115200
 UCA0MCTL = UCBRS2 + UCBRS0;               // Modulation UCBRSx = 5
 UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
 IE2 |= UCA0RXIE;                          // Enable USCI_A0 RX interrupt
 for (;;){
     __bis_SR_register(CPUOFF + GIE);
 }
}
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_A0(void){
    ADC10CTL0 |= ENC + ADC10SC ; // sampling and convr start
}
// ADC CONVERSION
#pragma vector = ADC10_VECTOR
__interrupt void ADC10_ISR(void){
     temp = ADC10MEM; // save old 8bit-8bit data to mem
     temp = temp>>8; // shift to right by 8 bits
     while (!(IFG2 & UCA0TXIFG));      // USCI_A0 TX buffer ready?
     UCA0TXBUF = temp; // send MSB byte
     while (!(IFG2 & UCA0TXIFG));      // USCI_A0 TX buffer ready?
     UCA0TXBUF = ADC10MEM; // send LSB byte
}
// Echo back RXed character, confirm TX buffer is ready first
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void){
    if (UCA0RXBUF == 'a'){
    }
}
