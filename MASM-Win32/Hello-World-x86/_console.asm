TITLE   MASM Tutorial (x86 version)

INCLUDE _header.inc


.DATA
OUTPUT_HANDLE	DWORD	0
CharsWritten	DWORD	0

.CODE
WriteStringToConsole PROC stringPtr:DWORD, numberOfCharsToWrite:DWORD
	PUSHAD

	; if (OUTPUT_HANDLE == 0) {
		MOV EAX, OUTPUT_HANDLE
		CMP EAX, 0
		JNE J1
			INVOKE GetStdHandle, STD_OUTPUT_HANDLE
			MOV OUTPUT_HANDLE, EAX
	; }
J1:

	INVOKE WriteConsoleA, OUTPUT_HANDLE, stringPtr, numberOfCharsToWrite, OFFSET CharsWritten, 0

	MOV CharsWritten, EAX
	
	POPAD
	MOV EAX, CharsWritten
	RET
WriteStringToConsole ENDP



END WriteStringToConsole

