TITLE   MASM Tutorial (x86 version)

INCLUDE _header.inc


.DATA
strHelloWorld	BYTE	"Hello World!", 0
cntHelloWorld	DWORD	$ - strHelloWorld - 1


.CODE
main PROC
	
	INVOKE WriteStringToConsole, OFFSET strHelloWorld, cntHelloWorld
	
	exit
main ENDP

END main

