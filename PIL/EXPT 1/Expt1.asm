; Program for addition of two numbers
DATA_SEG 	SEGMENT
	N1	DW 1000H
	N2	DW 2000H
	R	DW 0000H
DATA_SEg	ENDS

CODE_SEG	SEGMENT
		ASSUME CS:CODE_SEG,DS:DATA_SEG
	BEGIN:	MOV AX,DATA_SEG			;Initialize data segment register
		MOV DS,AX

		MOV AX,N1
		MOV BX,N2
		ADD AX,BX
		MOV R,AX

		MOV AX,4CH
		INT 21H
CODE_SEG	ENDS
		END BEGIN
