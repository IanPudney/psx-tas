#include "psx-controller.h"

PSXController::PSXController()
{
}

void PSXController::ack() {
	digitalWrite(_ackPin, LOW);
	delayMicroseconds(10);  // arbitrary number, might be wrong
	digitalWrite(_ackPin, HIGH);
}

byte PSXController::tick() {
	// Wait for an attention signal.
	while(!digitalRead(_attPin));
	while(digitalRead(_attPin));

	byte cmnd_val = shift(0xFF);
	if(cmnd_val != 0x1) {
		// We got a command that wasn't start?
		for(int i = 0; i < 6; ++i) {
			digitalWrite(_errPin, HIGH);
			delay(200);
			digitalWrite(_errPin, LOW);
			delay(200);
		}
		delay(1000);
		return cmnd_val;
	}
	ack();

	cmnd_val = shift(0x41);  // code for digital controller
	if(cmnd_val != 0x42) {
		// We got a command that wasn't read?
		for(int i = 0; i < 3; ++i) {
			digitalWrite(_errPin, HIGH);
			delay(200);
			digitalWrite(_errPin, LOW);
			delay(200);
		}
		delay(1000);
		return cmnd_val;
	}
	ack();

	shift(0x5A);  // data start
	ack();
	shift(~_data1);
	ack();
	shift(~_data2);
	return 0;
}

byte PSXController::shift(byte _dataOut)
{
	_temp = 0;
	_dataIn = 0;

	for (_i = 0; _i <= 7; _i++)
	{	
		// wait for clock to go low
		while(digitalRead(_clockPin));

		if ( (_dataOut) & (1 << (7 - _i)) ) digitalWrite(_dataPin, HIGH);	// Writes out the _dataOut bits
		else digitalWrite(_dataPin, LOW);
		
		// wait for clock to go high
		while(!digitalRead(_clockPin));

		_temp = digitalRead(_cmndPin);					// Reads the cmnd pin
		if (_temp)
		{
			_dataIn = _dataIn | (B10000000 >> (7 - _i));		// Shifts the read data into _dataIn
		}
		
	}
	return _dataIn;
}


void PSXController::setupPins(byte dataPin, byte cmndPin, byte attPin, byte clockPin, byte errPin, byte ackPin, byte delay)
{
	pinMode(dataPin, OUTPUT);
	digitalWrite(dataPin, HIGH);
	_dataPin = dataPin;

	pinMode(cmndPin, INPUT);
	_cmndPin = cmndPin;
	digitalWrite(_cmndPin, HIGH);

	pinMode(attPin, INPUT);
	_attPin = attPin;
	digitalWrite(_attPin, HIGH);

	pinMode(clockPin, INPUT);
	_clockPin = clockPin;
	digitalWrite(_clockPin, HIGH);

	pinMode(errPin, OUTPUT);
	_errPin = errPin;
	digitalWrite(_errPin, LOW);

	pinMode(ackPin, OUTPUT);
	_ackPin = ackPin;
	digitalWrite(_ackPin, HIGH);
	
	_delay = delay;
}


void PSXController::set(short buttons)
{
	delay(1000);
	_data1 = buttons;
	_data2 = (buttons >> 8);
}
