
/* FRAME kind */
#define FRAME_DATA 0x0000
#define FRAME_ACK  0x0001
#define FRAME_NAK  0x0003

boolean double_check(unsigned short *);
boolean bit_check(unsigned char *);

/*  NEW DATA Frame
	DATA Frame
    +====================================+===========+========+
    | SEQ (5bs) | ACK (5bs) | KIND (2bs) | DATA(256) | CRC(4) |
    +====================================+===========+========+

	ACK/NAK Frame using odd check
	+====================================+
	| CHECK(1b) | ACK (5bs) | KIND (2bs) |
	+====================================+

	ACK/NAK Frame using double check
	+=====================================+=====================================+
	| Unused(1b) | ACK (5bs) | KIND (2bs) | Unused(1b) | ACK (5bs) | KIND (2bs) |
	+=====================================+=====================================+

*/


/*  
    DATA Frame
    +=========+========+========+===============+========+
    | KIND(1) | SEQ(1) | ACK(1) | DATA(240~256) | CRC(4) |
    +=========+========+========+===============+========+

    ACK Frame
    +=========+========+========+
    | KIND(1) | ACK(1) | CRC(4) |
    +=========+========+========+

    NAK Frame
    +=========+========+========+
    | KIND(1) | ACK(1) | CRC(4) |
    +=========+========+========+
*/


