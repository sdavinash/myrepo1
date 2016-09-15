#include "hw1.h"

char reverse_string(char * str, int length) 
{
	int i = 0;
	char temp;
	while (i < length / 2)
	{
		temp = *(str + i);
		*(str + i) = *(str + length - i - 1);
		*(str + length - i - 1) = temp;
		i++;
	}
	if (i == (length/2)) 
	{
		return 0;
	}
	else 
	{
		return -1;

	}
}
