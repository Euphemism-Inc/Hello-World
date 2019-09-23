TITLE   MASM Tutorial (x64 version)

INCLUDE _header.inc


.DATA
OUTPUT_HANDLE	QWORD	0
CharsWritten	QWORD	0
HasWritten		QWORD   0

.CODE
GetConsoleHandle PROC
	handleType EQU <rcx>
	ENTER 0,0

	; switch (handleType) {
		; case STD_INPUT_HANDLE
			;CMP handleType, STD_INPUT_HANDLE
			;JNE GetConsoleHandle_End
				;LEA handleMemLoc, INPUT_HANDLE
				;CALL GetConsoleHandle_
				;JMP GetConsoleHandle_End

		; case STD_OUTPUT_HANDLE
			CMP handleType, STD_OUTPUT_HANDLE
			JNE GetConsoleHandle_End
				LEA handleMemLoc, OUTPUT_HANDLE
				CALL GetConsoleHandle_
				JMP GetConsoleHandle_End
		
		; case STD_ERROR_HANDLE
			;CMP handleType, STD_ERROR_HANDLE
			;JNE GetConsoleHandle_End
				;LEA handleMemLoc, ERROR_HANDLE
				;CALL GetConsoleHandle_
				;JMP GetConsoleHandle_End

		; default
			MOV RAX, 0
	; }

GetConsoleHandle_End:
	LEAVE
	RET
GetConsoleHandle ENDP


GetConsoleHandle_ PROC
	handleType_ EQU <rcx>
	handleMemLoc EQU <rdx>
	ENTER 0,0

	MOV RAX, [handleMemLoc]
	CMP RAX, 0
	JNE GetConsolHandle__End
	
			MOV RCX, handleType_
			CALL GetStdHandle
			MOV [handleMemLoc], RAX

			; if ([handleMemLoc] == -1) {
				CMP RAX, INVALID_HANDLE_VALUE
				JNE GetConsolHandle__End
					CALL GetLastError
					XOR RAX, RAX ; Error code is here
			; }

GetConsolHandle__End:
	LEAVE
	RET
GetConsoleHandle_ ENDP


WriteStringToConsole PROC
	numberOfCharsToWrite EQU <rcx>
	stringPtr EQU <rdx>
	ENTER 0, 0

	; RAX = GetConsoleHandle(STD_OUTPUT_HANDLE)
		PUSH numberOfCharsToWrite
		PUSH stringPtr

		MOV handleType, STD_OUTPUT_HANDLE
		CALL GetConsoleHandle

	; if (RAX == null) {
		CMP RAX, 0
		JNE WriteStringToConsole_Else

		MOV CharsWritten, 0
		MOV HasWritten, 0
		JMP WriteStringToConsole_End
	; } else {
	WriteStringToConsole_Else:
		; HasWritten = WriteConsoleA(hConsoleOutput, *lpBuffer, nNumberOfCharsToWrite, lpNumberOfCharsWritten, lpReserved)
		MOV RCX, RAX
		POP RDX
		POP R8
		LEA R9, CharsWritten
		PUSH 0
		CALL WriteConsoleA

		MOV HasWritten, RAX
	; }

WriteStringToConsole_End:
	; RAX = CharsWritten
	MOV RAX, QWORD PTR CharsWritten
	LEAVE
	RET
WriteStringToConsole ENDP


WriteNewLine PROC
	ENTER 0,0
	PUSH RCX
	PUSH RDX
	
	MOV RCX, 0A0Dh
	PUSH RCX
	MOV RDX, RSP
	MOV RCX, 02h
	CALL WriteStringToConsole
	
	POP RCX ; The newline
	POP RDX
	POP RCX ; original RCX
	LEAVE
	RET
WriteNewLine ENDP


WriteNumber PROC
	number EQU <ecx>
	ENTER 0,0
	PUSH RCX
	PUSH RDX

	;SUB RSP, 010h ;ulong = 64bit, 8byte, 1*push | + 1 * 0x00h = 65bit | 8byte aligned = 010h
	PUSH 0
	PUSH 0
	MOV RDX, RSP
	CALL ULongToString

	MOV RDX, RSP
	MOV RCX, 010h
	CALL WriteStringToConsole

	ADD RSP, 010h
	POP RDX
	POP RCX
	LEAVE
	RET
WriteNumber ENDP


GetConsoleDimensions PROC
	ENTER 0, 0

	; http://stackoverflow.com/questions/6812224/getting-terminal-size-in-c-for-windows
	; CONSOLE_SCREEN_BUFFER_INFO csbi;
	; int columns, rows;

	; GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	; columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	; rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	; Allocate on the Stack - why not?
	SUB RSP, SIZEOF CONSOLE_SCREEN_BUFFER_INFO
	PUSH RSP ; lpConsoleScreenBufferInfo

	; RAX = GetConsoleHandle(STD_OUTPUT_HANDLE)
	MOV handleType, STD_OUTPUT_HANDLE
	CALL GetConsoleHandle

	; if (rax == null)
	CMP RAX, 0
	JNE GetConsoleDimensions_Else1
		MOV RAX, 0 ; X
		MOV RBX, 0 ; Y
		JMP GetConsoleDimensions_End

GetConsoleDimensions_Else1:
	; else
		MOV RCX, RAX ; hConsoleOutput
		POP RDX ; lpConsoleScreenBufferInfo
		PUSH RDX ; Preserve RDX, orig RSP
		CALL GetConsoleScreenBufferInfo

		; if (RAX == 0)
		CMP RAX, 0
		JNE GetConsoleDimensions_Else2
			MOV RAX, 0 ; X
			MOV RBX, 0 ; Y
			JMP GetConsoleDimensions_End
			
	GetConsoleDimensions_Else2:
		; else
		POP RAX ; Orig RSP, ptr to CONSOLE_SCREEN_BUFFER_INFO
		;ASSUME rax:PTR CONSOLE_SCREEN_BUFFER_INFO

		MOVZX RBX, (CONSOLE_SCREEN_BUFFER_INFO PTR [RAX]).srWindow.Right
		MOVZX RCX, (CONSOLE_SCREEN_BUFFER_INFO PTR [RAX]).srWindow.Left
		SUB RBX, RCX
		PUSH RBX
		
		MOVZX RBX, (CONSOLE_SCREEN_BUFFER_INFO PTR [RAX]).srWindow.Bottom
		MOVZX RCX, (CONSOLE_SCREEN_BUFFER_INFO PTR [RAX]).srWindow.Top
		SUB RBX, RCX
		MOV RAX, RBX
		POP RBX
		;ASSUME rax:NOTHING

GetConsoleDimensions_End:
	LEAVE
	RET
GetConsoleDimensions ENDP


END

