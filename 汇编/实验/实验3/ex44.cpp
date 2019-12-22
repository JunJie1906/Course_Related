#include<stdio.h>
#include<iostream>
using namespace std;

int main()
{
	char c,ans[404];
	int n=10;
	scanf("%s",&c);
	scanf("%d",&n);

	_asm{
		CLD;
		MOV AL,c;
		MOV ECX,n;
		LEA	EDI,ans;
		REP STOSB;
		MOV AL,0;
		STOSB;
	}
	cout<<ans<<endl;
}
