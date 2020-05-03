 segment   text                    
        org   100H
	MOV AX,CS
	MOV DS,AX
	MOV DX,result
	MOV EBX,9	
	MOV ESI,0
LOOP1:
	CMP ESI,0
	JZ NEXT
	MOV AL,10
	MOV [result+ESI],AL
	INC ESI
NEXT:
	MOV ECX,26
	MOV EAX,97
LOOP2:
	MOV [result+ESI],AL
	INC ESI
	INC EAX
	LOOP LOOP2
	DEC EBX
	CMP EBX,0
	JNZ LOOP1

	MOV AL,'$'
	MOV[result+ESI],AL

	MOV AH,9
	INT 21H
	MOV AH,4CH
	INT 21H

result db 0
