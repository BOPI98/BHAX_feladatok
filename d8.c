#include <stdio.h>
int *h()
{
int a=8;
int *b=&a;
return b;
}

int main()
{ 

int *(*l) () =h;
printf("%d\n",*(*l)());
return 0; 
}

