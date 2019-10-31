#include <msp430.h>
unsigned int count = 0;
void printString(char *text)
{
    unsigned int i = 0;
    while(text[i] != '\0') // do while the string isn’t empty
    {
        while (!(IFG2&UCA0TXIFG));      // Check if TX is ongoing
        UCA0TXBUF = text[i];            // TX=char by char of the string by location         
 I++; // increment location
    }
}
void printNumber(unsigned int num) // int to string conversion
{
    char buf[6];
    char *str = &buf[5];
    *str = '\0';
    do
    {
        unsigned long m = num;
        num /= 10;
        char c = (m - 10 * num) + '0';
        *--str = c;
    } while(num);
    printString(str); // call print string function
}
int main(void)
{
    WDTCTL = WDTPW + WDTHOLD; //Stop WDT

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
    // BUTTON 
    P1DIR &= ~BIT3; // p1.3 button input
    P1REN |= BIT3; // res enabled
    P1OUT |= BIT3; // pull-up res
    P1IE |= BIT3; // enable interrupt
    P1IES |= BIT3; // high-low*/
    __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0, interrupts enabled
}
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void){
    Count++; // increment count on each button press
    printString("Button has been pressed "); // call conversion functions
    printNumber(count);
    printString(" times ");
    P1IFG &= ~BIT3; // clear the flag
}
// Echo back RXed character, confirm TX buffer is ready first
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void) // this doesn’t do anything
{
    while (!(IFG2 & UCA0TXIFG));                // USCI_A0 TX buffer ready?
}





#include <msp430.h>
unsigned int count = 0;
void printString(char *text)
{
    unsigned int i = 0;
    while(text[i] != '\0') // do while the string isn’t empty
    {
        while (!(IFG2&UCA0TXIFG));      // Check if TX is ongoing
        UCA0TXBUF = text[i];            // TX=char by char of the string by location         
 I++; // increment location
    }
}
void printNumber(unsigned int num) // int to string conversion
{
    char buf[6];
    char *str = &buf[5];
    *str = '\0';
    do
    {
        unsigned long m = num;
        num /= 10;
        char c = (m - 10 * num) + '0';
        *--str = c;
    } while(num);
    printString(str); // call print string function
}
 
 
int main(void)
{
    WDTCTL = WDTPW + WDTHOLD; //Stop WDT
 
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
 
    P1DIR &= ~BIT3; // p1.3 button input
    P1REN |= BIT3; // res enabled
    P1OUT |= BIT3; // pull-up res
    P1IE |= BIT3; // enable interrupt
    P1IES |= BIT3; // high-low*/
 
    __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0, interrupts enabled
 
}
 
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void){
    __delay_cycles(100000); // debouncing
    while (!(P1IN & BIT3)){}
    __delay_cycles(100000);
    Count++; // increment count each time button is pressed
    P1IFG &= ~BIT3; // clear flag
}

// Echo back RXed character, confirm TX buffer is ready first
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void){
    while (!(IFG2 & UCA0TXIFG));                // USCI_A0 TX buffer ready?
    if (UCA0RXBUF == 'q'){ // is Rx a q?
        printString("Button has been pressed "); // call conversion functions
        printNumber(count);
        printString(" times ");
    }
}






#include <msp430.h>
unsigned int count = 0;

void printString(char *text)
{
    unsigned int i = 0;
    while(text[i] != '\0') // do while the string isn’t empty
    {
        while (!(IFG2&UCA0TXIFG));      // Check if TX is ongoing
        UCA0TXBUF = text[i];            // TX=char by char of the string by location         
 I++; // increment location
    }
}
void printNumber(unsigned int num) // int to string conversion
{
    char buf[6];
    char *str = &buf[5];
    *str = '\0';
    do
    {
        unsigned long m = num;
        num /= 10;
        char c = (m - 10 * num) + '0';
        *--str = c;
    } while(num);
    printString(str); // call print string function
}

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD; //Stop WDT
    if(CALBC1_1MHZ==0xFF)
    {
        while(1);
    }
    P1SEL = BIT1 + BIT2 ;                     // P1.1 = RXD, P1.2=TXD
    P1SEL2 = BIT1 + BIT2;
    UCA0CTL1 |= UCSSEL_1;                     // ACLK
    UCA0BR0 = 3;                              // 32kHz 9600, divisor=3
    UCA0BR1 = 0;                              // 32kHz 9600
    UCA0MCTL = UCBRS_0+UCBRS_1;               // Modulation UCBRSx = 3
    UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
    IE2 |= UCA0RXIE;                          // Enable USCI_A0 RX interrupt

    P1DIR &= ~BIT3; // p1.3 button input
    P1REN |= BIT3; // res enabled
    P1OUT |= BIT3; // pull-up res
    P1IE |= BIT3; // enable interrupt
    P1IES |= BIT3; // high-low*/

    __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3, interrupts enabled
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void){
    __delay_cycles(100000); // debouncing
    while (!(P1IN & BIT3)){}
    __delay_cycles(100000);
    Count++; // increment count each time button is pressed
    P1IFG &= ~BIT3; // clear flag
}

// Echo back RXed character, confirm TX buffer is ready first
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void){
    while (!(IFG2 & UCA0TXIFG));                // USCI_A0 TX buffer ready?
    if (UCA0RXBUF == 'q'){
        printString("Button has been pressed "); // call conversion functions
        printNumber(count);
        printString(" times ");
    }
}
// To do the bonus, we used command mine on putty to access the bluetooth module’s configurations and set putty’s baud rate to 9600. We set the baud rate to 9600 using “SU,9600” and reboot device.
