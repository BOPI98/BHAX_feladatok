%{
#include <stdio.h>
int a=0;
%}
%option noyywrap
%%
[[:digit:]]+ {
a++;
}
[[:alpha:]][[:print:]]*
%%
int main(void)
{
yylex();
printf("%d szám db: \n",a);

return 0;
}
