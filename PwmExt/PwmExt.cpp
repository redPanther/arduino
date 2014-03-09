#include <TimerOne.h>

//-- Update the TICKER_MAX and _STEP to 16 16 or 32 8 or 64 4 for performance vs colors available
#define TICKER_MAX 64
#define TICKER_STEP 4

//-- May have to tweak the timer based on number SR's
#define PwmExt_TIMER_DELAY 350

//--- Pin connected to ST_CP of 74HC595
static uint8_t PwmExt_latchPin = 10;
//--- Pin connected to SH_CP of 74HC595
static uint8_t PwmExt_clockPin = 13;
//--- Pin connected to DS of 74HC595
static uint8_t PwmExt_dataPin = 11;

//--- Used for faster latching
static int PwmExt_latchPinPORTB = PwmExt_latchPin - 8;

//number of multiplex - set to zero for no multiplexing in this example
static int PwmExt_groundMax = 0;  

//number of Shift Registers - set to 1 for this example
static uint8_t PwmExt_srcount = 1;
static int PwmExt_portsCount = PwmExt_srcount * 8;

//--- ready for 10 SR's
byte PwmExt_srvals[] ={
  0,0,0,0,0,0,0,0,0,0
};

int PwmExt_ticker = 0;
int PwmExt_groundAt = 255;

//--- setup for 10 SR's .. no multiplexing ...
// actually should be SR Count * 8 * multiplexing count (1 based) .. this is just an example for easy usage
byte PwmExt_srPins[80] = {
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0
};

// --- when using common anode led/display values must be inverted
// set 1 if port is inverted.
byte PwmExt_invertSrPort[80] = {
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0
};


// predifined funcs
byte PwmExt_spi_transfer(byte);
void PwmExt_Process();

// --------------------------------------------
void PwmExt_write(int port, byte val){
  PwmExt_srPins[port] = PwmExt_invertSrPort[port] == 0 ? val : (byte)~val;  
}

// --------------------------------------------
void PwmExt_portInvertEnable(int port) {
	PwmExt_invertSrPort[port]=1;
}

// --------------------------------------------
void PwmExt_portInvertDisable(int port) {
	PwmExt_invertSrPort[port]=0;
}

// --------------------------------------------
void PwmExt_setup( int srcount ) {
	PwmExt_srcount = srcount;
	PwmExt_portsCount = PwmExt_srcount * 8;

	// setup pin modes
	pinMode(PwmExt_latchPin, OUTPUT);
	pinMode(PwmExt_clockPin, OUTPUT);
	pinMode(PwmExt_dataPin, OUTPUT);

	// set pins to low
	digitalWrite(PwmExt_latchPin,LOW);
	digitalWrite(PwmExt_dataPin,LOW);
	digitalWrite(PwmExt_clockPin,LOW);
	
	// setup SPI
	byte clr;
	SPCR |= ( (1<<SPE) | (1<<MSTR) ); // enable SPI as master
	//SPCR |= ( (1<<SPR1) | (1<<SPR0) ); // set prescaler bits
	SPCR &= ~( (1<<SPR1) | (1<<SPR0) ); // clear prescaler bits
	clr=SPSR; // clear SPI status reg
	clr=SPDR; // clear SPI data reg
	SPSR |= (1<<SPI2X); // set prescaler bits
	//SPSR &= ~(1<<SPI2X); // clear prescaler bits

	delay(10);

	Timer1.initialize( PwmExt_TIMER_DELAY ); // Timer for updating pwm pins
	Timer1.attachInterrupt(PwmExt_Process);
}


// --------------------------------------------
byte PwmExt_spi_transfer(byte data)
{
	SPDR = data;			  // Start the transmission
	loop_until_bit_is_set(SPSR, SPIF);
	return SPDR;			  // return the received byte, we don't need that
}


// --------------------------------------------
void PwmExt_Process() {

	PwmExt_ticker++;
	if( PwmExt_ticker > TICKER_MAX )
		PwmExt_ticker = 0;
	int myPos = PwmExt_ticker * TICKER_STEP;

	PwmExt_groundAt++;
	if( PwmExt_groundAt > PwmExt_groundMax )
		PwmExt_groundAt = 0;

	int myLev = 0;

	for ( int iSR = 0 ; iSR < PwmExt_srcount ; iSR++) {
		byte currVal = 0;

		for( int i = 0 ; i < 8 ; i++ ){ 
			myLev = 0;
			if (PwmExt_srPins[(i+(8*iSR))+(PwmExt_groundAt*PwmExt_portsCount)] > myPos)
				myLev = 1;
			bitWrite(currVal,i,myLev );
		}

		PwmExt_srvals[iSR] = currVal;
	}

	// latch Off
	bitClear(PORTB,PwmExt_latchPinPORTB);

	// transfer data via SPI
	for ( int iSR = PwmExt_srcount - 1 ; iSR >= 0 ; iSR--){
		PwmExt_spi_transfer(PwmExt_srvals[iSR]);
	}

	// latch On
	bitSet(PORTB,PwmExt_latchPinPORTB);
}

// ----------------------------------------
int PwmExt_getMaxPorts() {
	return PwmExt_portsCount;
}


// ----------------------------------------
void PwmExt_allTo(int val, int delayval){
	for (int i = 0 ; i < PwmExt_portsCount; i++) {
		PwmExt_write (i, val);
		if( delayval > 0 )
			delay(delayval);
	}
}


// ----------------------------------------
void PwmExt_allOff(){
  PwmExt_allTo(0,0);
}

// ----------------------------------------
void PwmExt_allOn(){
  PwmExt_allTo(255,0);
}
