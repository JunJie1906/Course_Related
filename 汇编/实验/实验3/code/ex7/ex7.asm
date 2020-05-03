 segment   text                    
        org   100H
	MOV AX,CS
	MOV DS,AX

    MOV DX,INFOR1
    MOV AH,09H
    INT 21H

    MOV AH,01H
    INT 21H
    
    SUB AL,30H

    MOV BL,AL

    MOV DX,INFOR2
    MOV AH,09H
    INT 21H
 
    MOV AH,01H
    INT 21H
    
    SUB AL,30H
	
	PUSH AX
    MOV DX,INFOR3
    MOV AH,09H
    INT 21H
	POP AX
	
	PUSH AX
	MOV DL,BL
	ADD DL,AL
	ADD DL,30H
	MOV AH,2
	INT 21H
	POP AX
	
	PUSH AX
    MOV DX,INFOR4
    MOV AH,09H
    INT 21H
	POP AX

	MOV DL,BL
	SUB DL,AL
	ADD DL,30H
	MOV AH,2
	INT 21H
	
	MOV AH,4CH
    INT 21H




INFOR1 DB 'input a number:$'
INFOR2 DB 0AH,0DH,'input another number:$'
INFOR3 DB 0AH,0DH,'sum is:$'
INFOR4 DB 0AH,0DH,'sub is:$'