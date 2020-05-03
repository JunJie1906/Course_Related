#include<stdio.h>
#include<iostream>
using namespace std;

int main()
{
	char s1[100],s2[100],ans[100];
	scanf("%s",s1);
	scanf("%s",s2);

	_asm{
		CLD
		LEA EDI,s2;
		MOV ECX,0FFFFFFFFH;
		xor eax,eax;
		REPNZ SCASB;
		NOT ECX;
		DEC ECX;
		MOV EBX,ECX

		LEA EDI,s1;
		MOV ECX,0FFFFFFFFH;
		xor eax,eax;
		REPNZ SCASB;
		NOT ECX;
		DEC ECX;

		LEA ESI,s1;
		LEA EDI,ans;
		REP MOVSB
		LEA ESI,s2;
		MOV ECX,EBX
		REP MOVSB
		MOV [EDI],0
	}
	printf("%s",ans);
	system("pause");
	return 0;
}
