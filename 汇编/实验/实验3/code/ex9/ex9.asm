segment   e9                   
        org   100H
	MOV AX,CS
	MOV DS,AX

BEGIN:
    MOV   AH, 0
    INT   16H
    CMP   AL, 20H
    JE    FINISH
    CALL  OUTPUT
    JMP   BEGIN
FINISH:
    MOV   AH, 4CH
    INT   21H
	
OUTPUT:
    MOV   BX, AX
    MOV   AH, 0
    MOV   CL, 16
    DIV   CL
    MOV   DX, AX
	
    CALL  OUTPUT1
    MOV   DL, ' '
    INT   21H
    MOV   AL, BH
    MOV   AH, 0
    MOV   CL, 16
    DIV   CL
    MOV   DX, AX
	
    CALL  OUTPUT1
    MOV   DL, 13
    INT   21H
    MOV   DL, 10
    INT   21H
	RET
OUTPUT1:
    MOV   AH, 2
    CMP   DL, 10
    JB    NEXT1
    ADD   DL, 7
NEXT1: ADD   DL, 48
    INT   21H
    MOV   DL, DH
    CMP   DL, 10
    JB    NEXT2
    ADD   DL, 7
NEXT2: ADD   DL, 48
    INT   21H
    MOV   DL, 'H'
    INT   21H
	RET
	

   