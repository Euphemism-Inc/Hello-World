

;STD_INPUT_HANDLE	EQU	-10		; Not Needed
STD_OUTPUT_HANDLE	EQU	-11
;STD_ERROR_HANDLE	EQU	-12		; Not Needed


GetStdHandle PROTO, nStdHandle:DWORD
; HANDLE WINAPI GetStdHandle(
;    _In_  DWORD nStdHandle							; STD_OUTPUT_HANDLE, etc..
; );


WriteConsoleA PROTO, hConsoleOutput:DWORD, lpBuffer:DWORD, nNumberOfCharsToWrite:DWORD, lpNumberOfCharsWritten:DWORD, lpReserved:DWORD
; WriteConsole(
;    _In_        HANDLE hConsoleOutput,				; OUTPUT STREAM -> STD_OUTPUT_HANDLE's handle, received from GetStdHandle
;    _In_        const VOID *lpBuffer,				; PTR to the BYTE string, null terminated
;    _In_        DWORD nNumberOfCharsToWrite,		; Number of chars to write - thus the length of the string, minus the '0'
;    _Out_       LPDWORD lpNumberOfCharsWritten,	; PTR to a DWORD in memory that will contain the number of chars written after execution
;    _Reserved_  LPVOID lpReserved					; Reserved and must be null...
; );



WriteStringToConsole PROTO, stringPtr:DWORD, numberOfCharsToWrite:DWORD