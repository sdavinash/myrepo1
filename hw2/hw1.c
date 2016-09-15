#include "hw1.h"

char reverse_string(char * str, int length) 
{
	int index = 0;
	char temp;
	while (index<length / 2)
	{
		temp = *(str + index);
		*(str + index) = *(str + length - index - 1);
		*(str + length - index - 1) = temp;
		index++;
	}
	if (index == (length/2)) 
	{
		return 0;
	}
	else 
	{
		return -1;

	}
}
