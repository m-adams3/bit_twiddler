#include <stdio.h>
#include <stdint.h>
#include <math.h>

/** @brief converts decimal to custom binary representation
 *
 * converts floats [2.0, -2.0] to custom binary representation 
 * bit position:	[ 16 ][    15    ][14 .. 0]
 * description:		[sign][ones place][decimal]
 * if input is out of valid range, output will contain max allowable value (2 or -2)
 * 
 * @param input - any float
 * @param output - uint16 to store the custom binary representation
 *
 * @return result of conversion [0 valid input] [-1 input out of range]
 */
int decToBin(float input, uint16_t * const output) {
	(*output) = 0;
	int i;

	// set MSB (sign bit)
	if (input < 0) {
	(*output) |= (0x1 << 15);
	input *= -1; //now gain is pos but sign bit still set
	}

	// set ones bit and handle out of range
	if (input >= 2) {
		(*output) |= 0x7FFF;
		return -1;
	}
	else if (input >= 1) {
		(*output) |= (0x1 << 14);
		input -=1;
	}

	// handle fraction if in range (2, -2)
	for (i = 13; i >= 0; i--) {
		input *= 2;
		if (input >= 1) {
			(*output) |= (1 << i);
			input -= 1;
		}
	}

	return 0;
}

/* binary print found here: https://stackoverflow.com/a/3974138 */
void printBits(size_t const size, void const * const ptr)
{
	unsigned char *b = (unsigned char*) ptr;
	unsigned char byte;
	int i, j;
	
	for (i=size-1;i>=0;i--) {
		for (j=7;j>=0;j--) {
			byte = (b[i] >> j) & 1;
			printf("%u", byte);
		}
	}
	puts("");
}

int main(void) {

	int j = 0;
	float gain[11];
	gain[0] = 1.99;
	gain[1] = 1.3763;
	gain[2] = 0.5;
	gain[3] = 0;
	gain[4] = -0.5;
	gain[5] = -1.3763;
	gain[6] = -1.99;
	gain[7] = 2.00;
	gain[8] = 7.84;
	gain[9] = -2.00;
	gain[10] = -7.84;

	int result = 1;

	for (j = 0; j < 11; j++) {
		printf("gain: %f\n", gain[j]);

		uint16_t bin_rep = 0;

		result = decToBin(gain[j], &bin_rep);
		printBits(sizeof(uint16_t), &bin_rep);
		printf("result: %d\n\n", result);
	}
	
	return 0;
}