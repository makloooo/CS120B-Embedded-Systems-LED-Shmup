#ifndef SHIFT_REG_H
#define SHIFT_REG_H

#define SHIFT_PORT PORTA

// Ensure SHIFT_PORT is setup as output (0xFF)
void transmit_data_ch(unsigned char data) {
	int i;
	for (i = 7; i >= 0; --i) {
		// Sets SRCLR to 1 allowing data to be set
		// Also clears SRCLK in preparation of sending data
		SHIFT_PORT = 0x08;
		// set SER = next bit of data to be sent.
		SHIFT_PORT |= ((data >>i) & 0x01);
		// set SRCLK = 1. Rising edge shifts next bit of data into shift register.
		SHIFT_PORT |= 0x04;
	}
	// set RCLK = 1. Rising edge copies data from the "Shift" register into the "Storage" register
	SHIFT_PORT |= 0x02;
	// clears all lines for a new transmission
	SHIFT_PORT = 0x00;
}

// Ensure SHIFT_PORT is setup as output (0xFF)
void transmit_data_sh(unsigned short data) {
	int i;
	for (i = 15; i >= 0; --i) {
		// Sets SRCLR to 1 allowing data to be set
		// Also clears SRCLK in preparation of sending data
		SHIFT_PORT = 0x08;
		// set SER = next bit of data to be sent.
		SHIFT_PORT |= ((data >>i) & 0x01);
		// set SRCLK = 1. Rising edge shifts next bit of data into shift register.
		SHIFT_PORT |= 0x04;
	}
	// set RCLK = 1. Rising edge copies data from the "Shift" register into the "Storage" register
	SHIFT_PORT |= 0x02;
	// clears all lines for a new transmission
	SHIFT_PORT = 0x00;
}

#endif