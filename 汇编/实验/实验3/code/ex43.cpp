#include<stdio.h>
#include<iostream>
using namespace std;

int main()
{
	char s1[100],ans[100],dst[100];

	scanf("%s",s1);

	_asm{
		LEA EDI,dst;
		MOV ECX, 10;
		MOV AL,48;

STORE1:
		STOSB;
		INC AL;
		DEC ECX;
		CMP ECX,0;
		JNZ STORE1;

		MOV ECX, 26;
		MOV AL,65;
STORE2:
		STOSB;
		INC AL;
		DEC ECX;
		CMP ECX,0;
		JNZ STORE2;

		MOV ECX, 26;
		MOV AL,97;
STORE3:
		STOSB;
		INC AL;
		DEC ECX;
		CMP ECX,0;
		JNZ STORE3;
		MOV AL,0;
		STOSB;

		LEA ESI,s1;
		LEA EDI,ans;
		MOV EBX,EDI;
BEGIN:
		CMP [ESI],0;
		JZ END;
		LEA EDI,dst;
		MOV ECX,62;
		LODSB;
		REPNZ SCASB;
		CMP ECX,0;
		JZ BEGIN;
		MOV EDI,EBX;
		DEC ESI;
		MOVSB;
		MOV EBX,EDI;
		JMP BEGIN

END:
		MOV AL,0;
		MOV [EBX],0
	}
	cout<<ans<<endl;
}
