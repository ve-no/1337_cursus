#include <unistd.h>

void putcvvcv(char c)
{
	write(1, &c, 1);
}

void print_bits(unsigned char octet)
{
	int	i = 128;
	unsigned char 	bit;

	while (i--)
	{

		bit = (octet >> i & 1) + '0';
		write(1, &bit, 1);
	}
}
