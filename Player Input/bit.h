#ifndef BIT_H
#define BIT_H

unsigned char SetBit(unsigned char byte, unsigned char bit, unsigned char val) {
	return (val ? byte | (0x01 << bit) : byte & ~(0x01 << bit));
}

unsigned char GetBit(unsigned char byte, unsigned char val) {
	return ((byte & (0x01 << val)) != 0);
}

#endif