#ifndef SHIFT_REG_H
#define SHIFT_REG_H

// Ensure 'port' is setup as output (0xFF)
void transmit_char(volatile uint8_t *port, unsigned char data) {
	int i;
	for (i = 7; i >= 0; --i) {
		// Sets SRCLR to 1 allowing data to be set
		// Also clears SRCLK in preparation of sending data
		*port = 0x08;
		// set SER = next bit of data to be sent.
		*port |= ((data >>i) & 0x01);
		// set SRCLK = 1. Rising edge shifts next bit of data into shift register.
		*port |= 0x04;
	}
	// set RCLK = 1. Rising edge copies data from the "Shift" register into the "Storage" register
	*port |= 0x02;
	// clears all lines for a new transmission
	*port = 0x00;
}

// Ensure 'port' is setup as output (0xFF)
void transmit_short(volatile uint8_t *port, unsigned short data) {
	int i;
	for (i = 15; i >= 0; --i) {
		// Sets SRCLR to 1 allowing data to be set
		// Also clears SRCLK in preparation of sending data
		*port = 0x08;
		// set SER = next bit of data to be sent.
		*port |= ((data >>i) & 0x01);
		// set SRCLK = 1. Rising edge shifts next bit of data into shift register.
		*port |= 0x04;
	}
	// set RCLK = 1. Rising edge copies data from the "Shift" register into the "Storage" register
	*port |= 0x02;
	// clears all lines for a new transmission
	*port = 0x00;
}

#endif