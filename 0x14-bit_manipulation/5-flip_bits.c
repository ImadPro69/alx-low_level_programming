#include "main.h"

/**
 * flip_bits - returns the number of bits you would need to flip
 * @n: first number
 * @m: second number
 *
 * Return: number of bits to flip
 */
unsigned int flip_bits(unsigned long int n, unsigned long int m)
{
	unsigned long int xor_result = n ^ m; /* XOR of n and m */
	unsigned int count = 0;

	while (xor_result)
	{
		count += xor_result & 1; /* increment count if the rightmost bit is 1 */
		xor_result >>= 1; /* shift xor_result right by 1 bit */
	}

	return (count);
}

