#ifndef psx_controller_h
#define psx_controller_h

#include "Arduino.h"

// Button Hex Representations:
#define psxLeft		0x0001 
#define psxDown		0x0002
#define psxRight	0x0004
#define psxUp		0x0008
#define psxStrt		0x0010
#define psxSlct		0x0080

#define psxSqu		0x0100
#define psxX		0x0200
#define psxO		0x0400
#define psxTri		0x0800
#define psxR1		0x1000
#define psxL1		0x2000
#define psxR2		0x4000
#define psxL2		0x8000


class PSXController
{
	public:
		PSXController();
		void setupPins(byte , byte , byte , byte , byte, byte, byte );		// (Data Pin #, CMND Pin #, ATT Pin #, CLK Pin #, err pin #, ack pin #, Delay)
															
		void set(short buttons);
		byte tick();
		
	private:
		void ack();
		byte shift(byte _dataOut);

		byte _dataPin;
		byte _cmndPin;
		byte _attPin;
		byte _clockPin;
		byte _ackPin;
		byte _errPin;
		
		byte _delay;
		byte _i;
		boolean _temp;
		byte _dataIn;
		
		byte _data1;
		byte _data2;
		unsigned int _dataOut;
};

#endif  // psx_controller_h
