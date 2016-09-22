#include "memory.h"


char my_memmove(char * src, char * dest, int length)
{
 int i;
 char * temp;

 for (i=0; i<length; i++)
 {
  *(temp + i) = *(src + i);
 }

 for (i=0; i<length; i++)
 { 
  *(dest + i) = *(temp + i);
 }
 return 0;
}



char my_memzero(char * src, int length)
{
 
  for(int j=0; j<length; j++)
  {
   *(src+j) = 0;
  }
}




char my_reverse(char * src, int length) 
{
 int i = 0;
 char temp;
 while (i < length / 2)
 {
  temp = *(src + i);
  *(src + i) = *(src + length - i - 1);
  *(src + length - i - 1) = temp;
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
