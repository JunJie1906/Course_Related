#include<stdio.h>
#include<iostream>
using namespace std;

int main()
{
	char c,ans[404];
	int n;
	scanf("%c",&c);
	scanf("%d",&n);

	_asm{
		LEA EDI,ans;
		MOV AL,c;
		MOV ECX,n;
		CALL SUB1
	}
	cout<<ans<<endl;
	return 0;

	_asm{
SUB1:
		REP STOSB;
		MOV AL,0;
		STOSB;
		ret
	}
}
