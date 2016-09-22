#include <stdio.h>
#include "memory.h"

int main()
{
 char array[32], memozero, memomove, rever;
 char * aptr1 = &array[0], * aptr2 = &array[8], * aptr3 = &array[16];
 
 for(int i=0; i<16; i++)
 {
  *(aptr1 + i) = (31 + i);
 }
  
 memozero = my_memzero((char *)aptr3, 16);
 
 printf("The completely initialized array\n");
 for(int i=0; i<32; i++)
 {
  printf("%d ", array[i]);
 }
 printf("\n");
 printf("Value pointed by pointers\n");
 printf("aptr1 (array[0]): %d\taptr2 (array[8]): %d\taptr3 (array[16]): %d\n", *aptr1, *aptr2, *aptr3);
 
 printf("The reverse of array\n");
 rever = my_reverse ((char *)array, 32);

 //memomove = my_memmove((char *)aptr1, (char *)aptr3, 8);
 
 for(int i=0; i<32; i++)
 {
  printf("%d ", array[i]);
 }
 printf("\n");
 printf("Value pointed by pointers\n");
 printf("aptr1 (array[0]): %d\taptr2 (array[8]): %d\taptr3 (array[16]): %d\n", *aptr1, *aptr2, *aptr3);

}
