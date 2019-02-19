#include <msp430.h> 

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	            // stop watchdog timer

	P1OUT &= ~BIT0;                         // Clear P1.0 output latch for a defined power-on state
	P1DIR |= BIT0;                          // Set P1.0 to output direction

	TA0CTL = TASSEL_2 + ID_3 + MC_1 + TACLR;
	                                        // Sets timer source to SMCLK, internal
	                                        // divider to internal clock to 8, sets
	                                        // clock to up mode, and clears the clock
	TA0CCR0 = 0x8000;                       //
	TA0CCTL0 |= CCIE;                       // Capture/compare interrupt enabled

	
	_BIS_SR(LPM0_bits + GIE);               // Sets the processor to low processor mode
	                                        // and enables global interrupts

	return 0;
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void timer0_a_interrupt(void){
    P1OUT ^= BIT0;                          // Toggles the state of P1.0
}
