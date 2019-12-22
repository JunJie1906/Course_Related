#include<stdio.h>
#include<iostream>
using namespace std;

int main()
{
	char s1[200],s2[100];
	int index;
	scanf("%s",s1);
	scanf("%s",s2);

	_asm{
		
		LEA EDI,s2;

		//get len(s2) and push it in EBX
		MOV EBX,0;
		XOR ECX,ECX;
		DEC ECX
		MOV AL,0
		REPNE SCASB
		NOT ECX
		DEC ECX
		MOV EBX,ECX
		//start position
		MOV EDX,0;
		
BEGIN:
		CLD
		LEA ESI,s1;
		LEA EDI,s2;
		
		ADD ESI,EDX;

		//check if s1 to the end
		MOV AL,0
		CMP AL,[ESI]
		JZ END1

		XOR ECX,ECX;
		DEC ECX

		REPE CMPSB
		NOT ECX
		DEC ECX
		CMP ECX,EBX
		JZ END
		INC EDX
		JMP BEGIN
END:
		MOV index,EDX;
		JMP FINAL;
END1:
		MOV index,-1;
FINAL:

	}
	cout<<index<<endl;
}
