// libs
#include "STD_TYPES.h"
#include "BIT_MAN.h"
#include "Delay_interface.h"
// MCAL
#include "RCC_interface.h"
#include "DIO_interface.h"
// HAL
#include "Keypad_interface.h"

#define PORT_KP 'A'

void main(void)
{
	/* init clocks */
	RCC_init();

	/* enable clock on port A & C */
	RCC_enablePeriClock(2, 2);
	RCC_enablePeriClock(2, 4);

	/* set pin C13 mode to output 2MHz push-pull */
	DIO_setPinMode('C', 13, 0b0010);

	/* set pin A15 mode to output 2MHz push-pull */
	DIO_setPinMode('A', 8, 0b0010);

	/* set pin C13 value to high (turn off) */
	DIO_setPinVal('C', 13, 1);

	DIO_setPinVal('A', 8, 0);

	/* init keypad */
	KP_init();

	u32 value = 0;

	while (1)
	{
		value = KP_getKey();
		value *= 2000;
		value /= 16;

		DIO_setPinVal('A', 8, 1);
		delay_us(value);

		DIO_setPinVal('A', 8, 0);
		delay_us(2000 - value);
	}
}
