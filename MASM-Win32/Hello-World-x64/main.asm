TITLE   MASM Tutorial (x64 version)

INCLUDE _header.inc


.DATA
strHelloWorld	BYTE	"Hello World!", 0
cntHelloWorld	QWORD	$ - strHelloWorld - 1


.CODE
main PROC
	MOV RCX, cntHelloWorld
	MOV RDX, OFFSET strHelloWorld
	CALL WriteStringToConsole
	
	CALL GetConsoleDimensions

	PUSH RBX; = Y
	PUSH RAX; = X

	MOV RCX, 02h
_Loop:
	MOV RDX, RCX
	POP RCX
	CALL WriteNewLine
	CALL WriteNumber
	MOV RCX, RDX
	LOOP _Loop

	MOV RCX, EXIT_SUCCESS
	CALL ExitProcess
	RET
main ENDP

END

