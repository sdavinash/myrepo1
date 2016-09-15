#include<stdio.h>
#include "hw1.h"
#include<string.h>
#include<stdint.h>

int main()
{
char mychar;
int myint;
float myfloat;
double mydouble;
short myshort;
long mylong;
long int mylongint;
long long mylonglong;
char * mychar1;
int * myint1;
float * myfloat1;
void * myvoid1;


printf("Size of Char is %lu \n",(unsigned long) sizeof(mychar));
printf("Size of int is %lu \n",(unsigned long) sizeof(myint));
printf("Size of float is %lu \n",(unsigned long) sizeof(myfloat));
printf("Size of double is %lu \n",(unsigned long) sizeof(mydouble));
printf("Size of short is %lu \n",(unsigned long) sizeof(myshort));
printf("Size of long is %lu \n",(unsigned long) sizeof(mylong));
printf("Size of long int is %lu \n",(unsigned long) sizeof(mylongint));
printf("Size of long long is %lu \n",(unsigned long) sizeof(mylonglong));
printf("Size of int8_t is %lu \n",(unsigned long) sizeof(int8_t));
printf("Size of uint8_t is %lu \n", (unsigned long) sizeof(uint8_t));

printf("Size of int16_t is %lu \n",(unsigned long) sizeof(int16_t));
printf("Size of int32_t is %lu \n",(unsigned long) sizeof(int32_t));

printf("Size of Char* is %lu \n",(unsigned long) sizeof(mychar1));
printf("Size of int* is %lu \n",(unsigned long) sizeof(myint1));
printf("Size of float* is %lu \n",(unsigned long) sizeof(myfloat1));
printf("Size of void* is %lu \n",(unsigned long) sizeof(myvoid1));

printf("Size of int8_t* is %lu \n" ,(unsigned long) sizeof(int8_t *));
printf("Size of int16_t* is %lu \n" ,(unsigned long) sizeof(int16_t *));
printf("Size of int32_t* is %lu \n" ,(unsigned long) sizeof(int32_t *));

 int len=0, i=0;
 char revstring, string[100];

 printf("Please enter the string \n");
 scanf("%99[^\n]",string);
 len = strlen(string);
 
 revstring = reverse_string((char *) string, len);

 if(!revstring)
 {
  printf("the reverse string is: %s\n", string);
 }
 else
 {
 printf("wrong string or invalid length");}
 return 0;
}
