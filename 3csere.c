#include <stdio.h>	//alapvető input,output
int main()
{
int a=3,b=5;		//előre megadott két egész szám
printf("Eredeti: a: %i b: %i\n",a,b);	//kiiratás a és b eredeti értékével
a=a+b;
b=a-b;
a=a-b;
printf("Csere: a: %i b: %i\n",a,b);	//kiiratás csere után
return 0;
}
