#include <stdio.h>
#include <signal.h>
void jelkezelo()
{
printf(" Valami\n");
}
int main()
{
while(1)
{
if(signal(SIGINT, jelkezelo)==SIG_IGN)
    signal(SIGINT, SIG_IGN);
}

}
