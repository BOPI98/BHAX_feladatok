#include <stdio.h>

int x(int a,int b)  {return a+b;}
int y(int a,int b) {return a*b;}


int (*asd(int c)) ()
{
if(c) return x;
else return y;
}

int (*v(int c)) (int a, int b)
{
return asd(c);
}

int main()
{
int *(*z(int)) (int,int)=v;
printf("%d\n",z(0) (5,5));

return 0;
}
