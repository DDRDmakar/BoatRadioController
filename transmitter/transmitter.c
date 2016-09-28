// MCU = Attiny13
// uint8_t = unsigned char ( 8 bit )

#include <avr/io.h>
#include <util/delay.h>

#define F_CPU = 1000000UL // Processor speed = 1 MHz

// + PORTB |= _BV ( 0 );
// - PORTB &= ~_BV ( 0 );
#define trans_p PORTB |= _BV ( 0 );
#define trans_n PORTB &= ~_BV ( 0 );
const unsigned int bit_time = 1000; // Time of one bit transmission ( microseconds )

void main ( void )
{
	uint8_t speed, steer; // 1 byte
	
	def_pins();
	
	while ( 1 )
	{
		speed = read_speed();
		steer = read_steer();
		transmit ( speed, steer );
		_delay_ms ( 1000 ); // wait 1 second
	}
}

void def_pins ( void )
{
	DDRB = 0x01;
	PORTB = 0x00;
	
	// TODO define ADC
}

uint8_t read_speed ( void )
{
	// TODO code here
	return 228;
}

uint8_t read_steer ( void )
{
	// TODO code here
	return 228;
}

void transmit ( uint8_t b1, uint8_t b2 )
{
	// ### Transmission start
	// Verification
	
	static uint8_t i, control_sum;
	
	for ( i = 0; i < 2; ++ i )
	{
		trans_p;
		_delay_us ( bit_time );
		trans_n;
		_delay_us ( bit_time );
	}
	
	// ### Byte transmission
	
	for ( i = 0; i < 8; ++ i )
	{
		if ( b1 & ( 1 << i ) ) trans_p;
		else trans_n;
		
		_delay_us ( bit_time );
	}
	
	for ( i = 0; i < 8; ++ i )
	{
		if ( b2 & ( 1 << i ) ) trans_p;
		else trans_n;
		
		_delay_us ( bit_time );
	}
	
	// ### Control sum
	
	control_sum = b1 + b2;
	
	for ( i = 0; i < 8; ++ i )
	{
		if ( control_sum & ( 1 << i ) ) trans_p;
		else trans_n;
		
		_delay_us ( bit_time );
	}
}
