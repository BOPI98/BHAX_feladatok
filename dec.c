#include <stdio.h>

void v(int a)
{
printf("A %i binarisan: ",a);
int i=0,bin[]={0,0,0,0,0,0,0,0};
while(a>0)
{

//printf("%i",a%2);
bin[i]=a%2;

a=a/2;
i++;

}
i--;
for(;i>=0;i--)
{

printf("%i",bin[i]);

}

}

int main()
{
int be;
scanf("%i",&be);

v(be);
printf("\n");
return 0;

}
