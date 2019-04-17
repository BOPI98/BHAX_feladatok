#include <iostream>
#include <ctype.h> 
#include <time.h>
#include <string>
using namespace std;

char t[9][9]=	{{' ',' ',' ',' ',' ',' ',' ',' ',' '},
		{' ',' ',' ',' ',' ',' ',' ',' ',' '},
		{' ',' ',' ',' ',' ',' ',' ',' ',' '},
		{' ',' ',' ',' ',' ',' ',' ',' ',' '},
		{' ',' ',' ',' ',' ',' ',' ',' ',' '},
		{' ',' ',' ',' ',' ',' ',' ',' ',' '},
		{' ',' ',' ',' ',' ',' ',' ',' ',' '},
		{' ',' ',' ',' ',' ',' ',' ',' ',' '},
		{' ',' ',' ',' ',' ',' ',' ',' ',' '}};

void kiir()
{
cout<<"     ";
for(int a=0;a<9;a++) {cout<<a+1<<"   ";}
cout<<endl;
cout<<"   -------------------------------------"<<endl;
for(int i=0;i<9;i++)
	{
	
	cout<<i+1<<"  |";	
	for(int j=0;j<9;j++) {cout<<" "<<t[i][j]<<" "<<"|";}
	cout<<endl;
	
	cout<<"   -------------------------------------"<<endl;
	}
}

int main()
{

string b;
int s,o;
while(cin)
{
getline(cin,b);

if(b.length()==3 && isdigit(b[0]) && b[0]!=0 && isdigit(b[2]) && b[2]!=0 && b[1]==' ') 
	{
	s=b[0]; o=b[2];
	cout<<"Írd be a számot!: ";
	getline(cin,b);
	if(isdigit(b[0]) && b.length()==1 && b[0]!='0') 
		{
		t[s][o]=b[0]; 
		cout<<t[1][1]<<endl;
		}
	else cout<<"helytelen input"<<endl;
	}
else if(b=="feladom") return 0;
else if(b=="a") kiir();
else if(b=="help") cout<<"Cella kiválasztáshoz írd be a sorszámot, majd az oszlopszámot space-szel elválasztva (pl: 1 2)"<<endl;
else cout<<"helytelen input"<<endl;
}

}
