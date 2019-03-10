#include <stdio.h>
#include <stdlib.h>
int sum(int a,int b)
{
return a+b;
}
int mul(int a, int b)
{
return a*b;
}
int (*asd(int c))()
{
if(c) return sum;
else return mul;
}
int (*v(int c))(int a,int b) //9
{
return asd(c);
}
int main()
{

int *(*z(int))(int,int) = v;  //10
printf("%d\n",z(0)(5,5));
return 0;
}
