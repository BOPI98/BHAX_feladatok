#include <stdio.h>

int main ()
{

int a=1;//1

int *b = &a;//2

int &r =a;

printf("a=%i\n",a);
return 0;
}
